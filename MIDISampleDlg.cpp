
// MIDISampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MIDISample.h"
#include "MIDISampleDlg.h"
#include "afxdialogex.h"
#include "MidiInputThread.h"
#include <Dbt.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib, "winmm.lib")

CMIDISampleDlg::CMIDISampleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMIDISampleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hMidiInputDevice = NULL;
	m_hMidiOutputDevice = NULL;
	m_pMidiInputThread = NULL;
	ZeroMemory(&m_szMidiBuffer, 1025*sizeof(CHAR));
	m_bRecording = FALSE;
}

CMIDISampleDlg::~CMIDISampleDlg()
{
	if(NULL != m_pMidiInputThread)
	{
		m_pMidiInputThread->Stop();
		WaitForSingleObject(m_pMidiInputThread->m_hThread, INFINITE);
		delete m_pMidiInputThread;
		m_pMidiInputThread = NULL;
	}
}

void CMIDISampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MIDI_INPUT_DEVICES, m_cboMidiInputDevices);
	DDX_Control(pDX, IDC_COMBO_MIDI_OUTPUT_DEVICES, m_cboMidiOutputDevices);
	DDX_Control(pDX, IDC_BTN_START, m_btnStart);
	DDX_Control(pDX, IDC_BTN_STOP, m_btnStop);
	DDX_Control(pDX, IDC_EDT_MIDI_LOGS, m_edtMidiStreamLogs);
	DDX_Control(pDX, IDC_BTN_CLEAR_LOG, m_btnClearTraceLogs);
	DDX_Control(pDX, IDC_BTN_TRAINER_SETTINGS, m_btnTrainerSettings);
	DDX_Control(pDX, IDC_BTN_NOTE_TRAINING, m_btnNoteTraining);
	DDX_Control(pDX, IDC_BTN_MIDI_TRACING, m_btnMidiTracing);
}

BEGIN_MESSAGE_MAP(CMIDISampleDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_DEVICECHANGE()
	ON_CBN_SELCHANGE(IDC_COMBO_MIDI_INPUT_DEVICES, &CMIDISampleDlg::OnCbnSelchangeComboMidiInputDevices)
	ON_CBN_SELCHANGE(IDC_COMBO_MIDI_OUTPUT_DEVICES, &CMIDISampleDlg::OnCbnSelchangeComboMidiOutputDevices)
	ON_BN_CLICKED(IDC_BTN_START, &CMIDISampleDlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, &CMIDISampleDlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_CLEAR_LOG, &CMIDISampleDlg::OnBnClickedBtnClearLog)
	ON_BN_CLICKED(IDC_BTN_MIDI_TRACING, &CMIDISampleDlg::OnBnClickedBtnMidiTracing)
	ON_BN_CLICKED(IDC_BTN_NOTE_TRAINING, &CMIDISampleDlg::OnBnClickedBtnNoteTraining)
END_MESSAGE_MAP()


BOOL CMIDISampleDlg::OnDeviceChange(UINT nEventType, DWORD_PTR dwData)
{
	if(nEventType == DBT_DEVNODES_CHANGED && m_bRecording == FALSE)
	{
		CloseDevices();
		UninitializeDevices();
		InitializeDevices();
	}

	return CDialogEx::OnDeviceChange(nEventType, dwData);
}

BOOL CMIDISampleDlg::EnumChildProc(HWND hwnd, LPARAM lParam)
{
	CMIDISampleDlg* pCMIDISampleDlg = (CMIDISampleDlg*)lParam;
	if(pCMIDISampleDlg != NULL)
	{
		CWnd *temp = CWnd::FromHandle(hwnd);
		if(temp != nullptr)
		{
			if(temp->GetWindowContextHelpId() != 0)
			{
				if(temp->GetWindowContextHelpId() == pCMIDISampleDlg->m_nTabIndex)
					temp->ShowWindow(SW_SHOW);
				else
					temp->ShowWindow(SW_HIDE);
			}
		}
	}
	return TRUE;
}

// CMIDISampleDlg message handlers
void CMIDISampleDlg::ArrangControls(UINT nTabIndex)
{
	CRect rcClient;
	CRect rcControl;
	GetClientRect(rcClient);
	rcClient.NormalizeRect();
	rcClient.top = 100;
	rcClient.NormalizeRect();
	rcClient.top += 20;
	rcClient.DeflateRect(4,4,4,4);
	rcControl = rcClient;
	rcControl.top = rcControl.bottom-40;
	rcControl.left = rcControl.right - 100;
	m_btnClearTraceLogs.MoveWindow(rcControl);
	m_btnTrainerSettings.MoveWindow(rcControl);
	rcControl = rcClient;
	rcControl.right = rcControl.right-110;
	m_edtMidiStreamLogs.MoveWindow(rcControl);
	if(m_TrainerSheet.GetSafeHwnd() == NULL)
	{
		m_TrainerSheet.Create(NULL, WS_CHILD | WS_BORDER | SS_OWNERDRAW, rcControl, this);
		m_TrainerSheet.SetWindowContextHelpId(2);
	}

	m_nTabIndex = nTabIndex;
	EnumChildWindows(GetSafeHwnd(), &CMIDISampleDlg::EnumChildProc, (LPARAM)this);
}

BOOL CMIDISampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	LOGFONT lf={0};
	GetFont()->GetLogFont(&lf);
	lf.lfWeight = FW_BOLD;
	m_FontBold.CreateFontIndirect(&lf);

	m_edtMidiStreamLogs.SetWindowContextHelpId(1);
	m_btnClearTraceLogs.SetWindowContextHelpId(1);
	m_btnTrainerSettings.SetWindowContextHelpId(2);

	InitializeDevices();
	m_btnMidiTracing.SetFont(&m_FontBold);
	ArrangControls(1);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMIDISampleDlg::OnDestroy()
{
	CloseDevices();
	UninitializeDevices();
	if(m_FontBold.GetSafeHandle())
		m_FontBold.DeleteObject();

	if(m_TrainerSheet.GetSafeHwnd())
		m_TrainerSheet.DestroyWindow();

	CDialogEx::OnDestroy();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMIDISampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMIDISampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMIDISampleDlg::InitializeDevices()
{
	m_cboMidiInputDevices.ResetContent();
	m_cboMidiOutputDevices.ResetContent();
	m_arrInputDeviceInfos.RemoveAll();

	UINT nNumDevices = midiInGetNumDevs();
	MMRESULT res = MMSYSERR_NOERROR;
	MIDIINCAPS inDeviceCap = {0};
	for(UINT nDev=0;nDev<nNumDevices;nDev++)
	{
		ZeroMemory(&inDeviceCap, sizeof(inDeviceCap));
		res = midiInGetDevCaps(nDev, &inDeviceCap, sizeof(inDeviceCap));
		if(res == MMSYSERR_NOERROR)
		{
			MidiDeviceInfo* pNewDeviceInfo = new MidiDeviceInfo;
			ZeroMemory(pNewDeviceInfo, sizeof(MidiDeviceInfo));
			pNewDeviceInfo->Id = nDev;
			StrCpyN(pNewDeviceInfo->Name, inDeviceCap.szPname, MAXPNAMELEN);
			m_arrInputDeviceInfos.Add(pNewDeviceInfo);
			int nIndex = m_cboMidiInputDevices.AddString(inDeviceCap.szPname);
			if(nIndex != CB_ERR)
				m_cboMidiInputDevices.SetItemDataPtr(nIndex, pNewDeviceInfo);
		}
		else
		{
			m_cboMidiInputDevices.AddString(_T("-"));
		}
	}

	nNumDevices = midiOutGetNumDevs();
	MIDIOUTCAPS outDeviceCap = {0};
	m_arrOutputDeviceInfos.RemoveAll();
	for(UINT nDev=0;nDev<nNumDevices;nDev++)
	{
		ZeroMemory(&outDeviceCap, sizeof(outDeviceCap));
		res = midiOutGetDevCaps(nDev, &outDeviceCap, sizeof(outDeviceCap));
		if(res == MMSYSERR_NOERROR)
		{
			MidiDeviceInfo* pNewDeviceInfo = new MidiDeviceInfo;
			ZeroMemory(pNewDeviceInfo, sizeof(MidiDeviceInfo));
			pNewDeviceInfo->Id = nDev;
			StrCpyN(pNewDeviceInfo->Name, inDeviceCap.szPname, MAXPNAMELEN);
			m_arrOutputDeviceInfos.Add(pNewDeviceInfo);
			int nIndex = m_cboMidiOutputDevices.AddString(outDeviceCap.szPname);
			if (nIndex != CB_ERR)
				m_cboMidiOutputDevices.SetItemDataPtr(nIndex, pNewDeviceInfo);
		}
		else
		{
			m_cboMidiOutputDevices.AddString(_T("-"));
		}
	}
}

void CMIDISampleDlg::CloseDevices()
{
	MMRESULT res = MMSYSERR_NOERROR;
	if(m_hMidiInputDevice != NULL)
	{
		if(m_bRecording)
		{
			res = midiInStop(m_hMidiInputDevice);
		}
		if(res == MMSYSERR_NOERROR)
		{
			m_bRecording = FALSE;
			res = midiInClose(m_hMidiInputDevice);
			if(res == MMSYSERR_NOERROR)
			{
				m_hMidiInputDevice = NULL;
				m_btnStop.EnableWindow(FALSE);
				m_cboMidiInputDevices.EnableWindow(TRUE);
				m_cboMidiOutputDevices.EnableWindow(TRUE);
				m_btnStart.EnableWindow(TRUE);
				m_btnNoteTraining.EnableWindow(FALSE);
				OnBnClickedBtnMidiTracing();
			}
		}
		else
		{
			AfxMessageBox(_T("Cannot stop input device"), MB_ICONERROR);
		}
	}

	if(m_hMidiOutputDevice != NULL)
	{
		res = midiOutClose(m_hMidiOutputDevice);
		if(res == MMSYSERR_NOERROR)
		{
			m_hMidiOutputDevice = NULL;
		}
	}
}

void CMIDISampleDlg::UninitializeDevices()
{
	MidiDeviceInfo* pDeviceInfo = nullptr;
	for(INT_PTR i=0;i<m_arrInputDeviceInfos.GetCount();i++)
	{
		pDeviceInfo = (MidiDeviceInfo*)m_arrInputDeviceInfos.GetAt(i);
		if(pDeviceInfo != nullptr)
			delete pDeviceInfo;
	}
	m_arrInputDeviceInfos.RemoveAll();

	for(INT_PTR i=0;i<m_arrOutputDeviceInfos.GetCount();i++)
	{
		pDeviceInfo = (MidiDeviceInfo*)m_arrOutputDeviceInfos.GetAt(i);
		if(pDeviceInfo != nullptr)
			delete pDeviceInfo;
	}
	m_arrOutputDeviceInfos.RemoveAll();
}

void CMIDISampleDlg::MidiInProc(HMIDIIN hMidiIn, UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
	CMIDISampleDlg* pCMIDISampleDlg = (CMIDISampleDlg*)dwInstance;
	if(nullptr != pCMIDISampleDlg)
		pCMIDISampleDlg->OnMidiMessage(hMidiIn, wMsg, dwParam1, dwParam2);
}

void CMIDISampleDlg::OnMidiMessage(HMIDIIN hMidiIn,UINT wMsg, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
	TRACE("%s\n", __FUNCTION__);
	switch (wMsg)
	{
	case MIM_DATA:
	{
		TRACE("MIM_DATA\n");

		DWORD_PTR dwMidiMessage = dwParam1;
		DWORD_PTR dwTimestamp = dwParam2;
		WORD wHiWord = HIWORD(dwMidiMessage);
		WORD wLoWord = LOWORD(dwMidiMessage);
		BYTE midiData2 = LOBYTE(wHiWord);
		BYTE midiData1 = HIBYTE(wLoWord);
		BYTE midiStatus = LOBYTE(wLoWord);


		CString strCurrentLog;
		CString strNewLog;
		m_edtMidiStreamLogs.GetWindowText(strCurrentLog);
		if(strCurrentLog.GetLength() > 0)
			strCurrentLog += _T("\r\n");
		strNewLog.Format(_T("MIM_DATA: midiStatus = %d(0x%X), midiData1=%d(0x%X), midiData2 = %d(0x%X), dwTimestamp = %I64d"), midiStatus, midiStatus, midiData1, midiData1, midiData2, midiData2, dwTimestamp);
		strCurrentLog += strNewLog;
		m_edtMidiStreamLogs.SetWindowText(strCurrentLog);

		if(m_hMidiOutputDevice != NULL)
		{
			MMRESULT res = midiOutShortMsg(m_hMidiOutputDevice, dwMidiMessage);
		}
	}
	case MIM_OPEN:
		TRACE("MIM_OPEN\n");
		break;
	case MIM_CLOSE:
		TRACE("MIM_CLOSE\n");
		break;
	case MIM_ERROR:
		TRACE("MIM_ERROR\n");
		break;
	case MIM_LONGDATA:
		TRACE("MIM_LONGDATA\n");
		break;
	case MIM_LONGERROR:
		TRACE("MIM_LONGERROR\n");
		break;
	case MIM_MOREDATA:
		TRACE("MIM_MOREDATA\n");
		break;
	case MOM_CLOSE:
		TRACE("MOM_CLOSE\n");
		break;
	case MOM_DONE:
		TRACE("MOM_DONE\n");
		break;
	case MOM_OPEN:
		TRACE("MOM_OPEN\n");
		break;
	case MOM_POSITIONCB:
		TRACE("MOM_POSITIONCB\n");
		break;
	default:
		break;
	}
}

void CMIDISampleDlg::OnCbnSelchangeComboMidiInputDevices()
{
	int nSelIndex = m_cboMidiInputDevices.GetCurSel();
	m_btnStart.EnableWindow(nSelIndex != CB_ERR);
}


void CMIDISampleDlg::OnCbnSelchangeComboMidiOutputDevices()
{
	
}


void CMIDISampleDlg::OnBnClickedBtnStart()
{
	int nIndex = m_cboMidiInputDevices.GetCurSel();
	MidiDeviceInfo* pInputDeviceInfo = nullptr;
	m_edtMidiStreamLogs.SetWindowText(_T(""));
	if(nIndex != CB_ERR)
		pInputDeviceInfo = (MidiDeviceInfo*)m_cboMidiInputDevices.GetItemDataPtr(nIndex);
	if(pInputDeviceInfo != nullptr)
	{
		MMRESULT res = midiInOpen(&m_hMidiInputDevice, pInputDeviceInfo->Id, reinterpret_cast<DWORD_PTR>(&CMIDISampleDlg::MidiInProc), reinterpret_cast<DWORD_PTR>(this), CALLBACK_FUNCTION | MIDI_IO_STATUS);
		if(res == MMSYSERR_NOERROR && m_hMidiInputDevice != NULL)
		{
			nIndex = m_cboMidiOutputDevices.GetCurSel();
			if(nIndex != CB_ERR)
			{
				MidiDeviceInfo* pOutputDeviceInfo = (MidiDeviceInfo*)m_cboMidiOutputDevices.GetItemDataPtr(nIndex);
				if(pOutputDeviceInfo != nullptr)
				{
					res = midiOutOpen(&m_hMidiOutputDevice, m_cboMidiOutputDevices.GetCurSel(), NULL, NULL, CALLBACK_NULL);
				}
			}

			MIDIHDR midiHeader = {0};
			midiHeader.lpData = m_szMidiBuffer;
			midiHeader.dwBufferLength = 1024;
			res = midiInPrepareHeader(m_hMidiInputDevice, &midiHeader, sizeof(midiHeader));
			if(res == MMSYSERR_NOERROR)
			{
				res = midiInAddBuffer(m_hMidiInputDevice, &midiHeader, sizeof(midiHeader));
				if(res == MMSYSERR_NOERROR)
				{
					res = midiInStart(m_hMidiInputDevice);
					if(res == MMSYSERR_NOERROR)
					{
						m_btnStop.EnableWindow(TRUE);
						m_cboMidiInputDevices.EnableWindow(FALSE);
						m_cboMidiOutputDevices.EnableWindow(FALSE);
						m_btnStart.EnableWindow(FALSE);
						m_bRecording = TRUE;
						m_btnNoteTraining.EnableWindow(TRUE);
					}
					else
					{
						CloseDevices();
					}
				}
			}
		}
		else
		{
			AfxMessageBox(_T("Cannot open MIDI input device"), MB_ICONERROR);
		}
	}
	else
	{
		AfxMessageBox(_T("Cannot obtain device information"), MB_ICONERROR);
	}
}


void CMIDISampleDlg::OnBnClickedBtnStop()
{
	CloseDevices();
}


void CMIDISampleDlg::OnBnClickedBtnClearLog()
{
	m_edtMidiStreamLogs.SetWindowText(_T(""));
}

void CMIDISampleDlg::OnBnClickedBtnMidiTracing()
{
	m_btnMidiTracing.SetFont(&m_FontBold);
	m_btnNoteTraining.SetFont(GetFont());
	ArrangControls(1);
}


void CMIDISampleDlg::OnBnClickedBtnNoteTraining()
{
	m_btnNoteTraining.SetFont(&m_FontBold);
	m_btnMidiTracing.SetFont(GetFont());
	ArrangControls(2);
}
