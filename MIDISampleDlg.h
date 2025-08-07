
// MIDISampleDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include <mmeapi.h>
#include "afxcmn.h"
#include "TrainerSheet.h"

class CMidiInputThread;
// CMIDISampleDlg dialog
class CMIDISampleDlg : public CDialogEx
{
// Construction
public:
	CMIDISampleDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CMIDISampleDlg();
	void OnMidiMessage(HMIDIIN hMidiIn,UINT wMsg, DWORD_PTR dwParam1, DWORD_PTR dwParam2);
// Dialog Data
	enum { IDD = IDD_MIDISAMPLE_DIALOG };
	
	afx_msg void OnCbnSelchangeComboMidiInputDevices();
	afx_msg void OnCbnSelchangeComboMidiOutputDevices();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnClearLog();
	afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD_PTR dwData);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();
private:
	void InitializeDevices();
	void CloseDevices();
	void UninitializeDevices();
	static void CALLBACK MidiInProc(HMIDIIN hMidiIn,UINT wMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2);
	static BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam);
	void ArrangControls(UINT nTabIndex = 0);
// Implementation
protected:
	DECLARE_MESSAGE_MAP()
private:
	typedef struct MidiDeviceInfo_
	{
		TCHAR Name[MAXPNAMELEN+1];
		UINT Id;
	} MidiDeviceInfo;
	UINT m_nTabIndex;
	CFont m_FontBold;
	CHAR m_szMidiBuffer[1025];
	HICON m_hIcon;
	BOOL m_bRecording;
	CComboBox m_cboMidiInputDevices;
	CEdit m_edtMidiStreamLogs;
	CComboBox m_cboMidiOutputDevices;
	CButton m_btnStart;
	CButton m_btnStop;
	HMIDIIN m_hMidiInputDevice;
	HMIDIOUT m_hMidiOutputDevice;
	CMidiInputThread* m_pMidiInputThread;
	CPtrArray m_arrInputDeviceInfos;
	CPtrArray m_arrOutputDeviceInfos;
	CButton m_btnClearTraceLogs;
	CTrainerSheet m_TrainerSheet;
public:
	CButton m_btnTrainerSettings;
	CButton m_btnNoteTraining;
	CButton m_btnMidiTracing;
	afx_msg void OnBnClickedBtnMidiTracing();
	afx_msg void OnBnClickedBtnNoteTraining();
	afx_msg void OnBnClickedBtnTrainerSettings();
};
