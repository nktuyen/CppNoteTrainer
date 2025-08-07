// DlgNoteTrainerSettings.cpp : implementation file
//

#include "stdafx.h"
#include "MIDISample.h"
#include "DlgNoteTrainerSettings.h"
#include "afxdialogex.h"
#include "NoteTrainerSettings.h"

// CDlgNoteTrainerSettings dialog

IMPLEMENT_DYNAMIC(CDlgNoteTrainerSettings, CDialogEx)

CDlgNoteTrainerSettings::CDlgNoteTrainerSettings(CWnd* pParent /*=NULL*/, CNoteTrainerSettings* pSettings)
	: CDialogEx(CDlgNoteTrainerSettings::IDD, pParent)
	,m_pOriginSettings(pSettings)
	,m_pEditSettings(nullptr)
{
	if(nullptr != m_pOriginSettings)
		m_pEditSettings = m_pOriginSettings->Clone();
}

CDlgNoteTrainerSettings::~CDlgNoteTrainerSettings()
{
	if(nullptr != m_pEditSettings)
		delete m_pEditSettings;
}

void CDlgNoteTrainerSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STT_COLOR_PREVIEW_BACKGROUND, m_sttColorPreviewBackground);
	DDX_Control(pDX, IDC_EDT_SHEET_HEIGHT, m_edtSheetHeight);
	DDX_Control(pDX, IDC_SPIN_SHEET_HEIGHT, m_spinSheetHeight);
	DDX_Control(pDX, IDC_STT_COLOR_PREVIEW_SHEET_BACKGROUND, m_sttColorPreviewSheetBackground);
	DDX_Control(pDX, IDC_SPIN_SHEET_BORDER_WIDTH, m_spinSheetBorderWidth);
	DDX_Control(pDX, IDC_EDT_SHEET_BORDER_WIDTH, m_edtSheetBorderWidth);
	DDX_Control(pDX, IDC_STT_COLOR_PREVIEW_SHEET_BORDER, m_sttColorPreviewSheetBorder);
	DDX_Control(pDX, IDC_SPIN_SHEET_PADDDING, m_spinSheetPadding);
	DDX_Control(pDX, IDC_EDT_SHEET_PADDING, m_edtSheetPadding);
	DDX_Control(pDX, IDC_STT_COLOR_PREVIEW_SLINE, m_sttColorPreviewLine);
	DDX_Control(pDX, IDC_EDT_LINE_WIDTH, m_edtLineWidth);
	DDX_Control(pDX, IDC_SPIN_LINE_WIDTH, m_spinLineWidth);
	DDX_Control(pDX, IDC_CHECK1, m_chbNote1);
	DDX_Control(pDX, IDC_CHECK2, m_chbNote2);
	DDX_Control(pDX, IDC_CHECK3, m_chbNote3);
	DDX_Control(pDX, IDC_CHECK4, m_chbNote4);
	DDX_Control(pDX, IDC_CHECK5, m_chbNote5);
	DDX_Control(pDX, IDC_CHECK_UPPER1, m_chbNoteUpper1);
	DDX_Control(pDX, IDC_CHECK_UPPER2, m_chbNoteUpper2);
	DDX_Control(pDX, IDC_CHECK_UPPER3, m_chbNoteUpper3);
	DDX_Control(pDX, IDC_CHECK_LOWER1, m_chbNoteLower1);
	DDX_Control(pDX, IDC_CHECK_LOWER2, m_chbNoteLower2);
	DDX_Control(pDX, IDC_CHECK_LOWER3, m_chbNoteLower3);
}


BEGIN_MESSAGE_MAP(CDlgNoteTrainerSettings, CDialogEx)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_CHOOSE_COLOR_BACKGROUND, &CDlgNoteTrainerSettings::OnBnClickedBtnChooseColorBackground)
	ON_BN_CLICKED(IDOK, &CDlgNoteTrainerSettings::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDT_SHEET_HEIGHT, &CDlgNoteTrainerSettings::OnEnChangeEdtSheetHeight)
	ON_BN_CLICKED(IDC_BTN_CHOOSE_COLOR_SHEET_BACKGROUND, &CDlgNoteTrainerSettings::OnBnClickedBtnChooseColorSheetBackground)
	ON_EN_CHANGE(IDC_EDT_SHEET_BORDER_WIDTH, &CDlgNoteTrainerSettings::OnEnChangeEdtSheetBorderWidth)
	ON_BN_CLICKED(IDC_BTN_CHOOSE_COLOR_SHEET_BORDER, &CDlgNoteTrainerSettings::OnBnClickedBtnChooseColorSheetBorder)
	ON_EN_CHANGE(IDC_EDT_SHEET_PADDING, &CDlgNoteTrainerSettings::OnEnChangeEdtSheetPadding)
	ON_BN_CLICKED(IDC_BTN_CHOOSE_COLOR_LINE, &CDlgNoteTrainerSettings::OnBnClickedBtnChooseColorLine)
	ON_EN_CHANGE(IDC_EDT_LINE_WIDTH, &CDlgNoteTrainerSettings::OnEnChangeEdtLineWidth)
	ON_BN_CLICKED(IDC_CHECK_LOWER3, &CDlgNoteTrainerSettings::OnBnClickedCheckLower3)
	ON_BN_CLICKED(IDC_CHECK_LOWER2, &CDlgNoteTrainerSettings::OnBnClickedCheckLower2)
	ON_BN_CLICKED(IDC_CHECK_LOWER1, &CDlgNoteTrainerSettings::OnBnClickedCheckLower1)
	ON_BN_CLICKED(IDC_CHECK1, &CDlgNoteTrainerSettings::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CDlgNoteTrainerSettings::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CDlgNoteTrainerSettings::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CDlgNoteTrainerSettings::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &CDlgNoteTrainerSettings::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK_UPPER1, &CDlgNoteTrainerSettings::OnBnClickedCheckUpper1)
	ON_BN_CLICKED(IDC_CHECK_UPPER2, &CDlgNoteTrainerSettings::OnBnClickedCheckUpper2)
	ON_BN_CLICKED(IDC_CHECK_UPPER3, &CDlgNoteTrainerSettings::OnBnClickedCheckUpper3)
	ON_BN_CLICKED(IDC_RADIO_BASS_CLEF, &CDlgNoteTrainerSettings::OnBnClickedRadioBassClef)
	ON_BN_CLICKED(IDC_RADIO_TREBLE_CLEF, &CDlgNoteTrainerSettings::OnBnClickedRadioTrebleClef)
END_MESSAGE_MAP()


BOOL CDlgNoteTrainerSettings::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_spinSheetHeight.SetBuddy(&m_edtSheetHeight);
	m_spinSheetHeight.SetRange(100, DEF_HEIGHT_SHEET);
	m_spinSheetBorderWidth.SetBuddy(&m_edtSheetBorderWidth);
	m_spinSheetBorderWidth.SetRange(0,10);
	m_spinSheetPadding.SetBuddy(&m_edtSheetPadding);
	m_spinSheetPadding.SetRange(0,100);
	m_spinLineWidth.SetBuddy(&m_edtLineWidth);

	m_spinLineWidth.SetRange(1,10);
	if(m_pEditSettings != nullptr)
	{
		m_sttColorPreviewBackground.SetColor(m_pEditSettings->m_clrBackground);
		SetDlgItemInt(IDC_EDT_SHEET_HEIGHT, m_pEditSettings->m_nSheetHeight);
		m_sttColorPreviewSheetBackground.SetColor(m_pEditSettings->m_clrSheetBackground);
		SetDlgItemInt(IDC_EDT_SHEET_BORDER_WIDTH, m_pEditSettings->m_nSheetBorderWidth);
		m_sttColorPreviewSheetBorder.SetColor(m_pEditSettings->m_clrSheetBorderColor);
		SetDlgItemInt(IDC_EDT_SHEET_PADDING, m_pEditSettings->m_nSheetPadding);
		m_sttColorPreviewLine.SetColor(m_pEditSettings->m_clrLine);
		SetDlgItemInt(IDC_EDT_LINE_WIDTH, m_pEditSettings->m_nLineWidth);	

		if(m_pEditSettings->GetLineVisible(-3))
			m_chbNoteLower3.SetCheck(BST_CHECKED);
		if (m_pEditSettings->GetLineVisible(-2))
			m_chbNoteLower2.SetCheck(BST_CHECKED);
		if(m_pEditSettings->GetLineVisible(-1))
			m_chbNoteLower1.SetCheck(BST_CHECKED);
		if(m_pEditSettings->GetLineVisible(1))
			m_chbNote1.SetCheck(BST_CHECKED);
		if(m_pEditSettings->GetLineVisible(2))
			m_chbNote2.SetCheck(BST_CHECKED);
		if(m_pEditSettings->GetLineVisible(3))
			m_chbNote3.SetCheck(BST_CHECKED);
		if(m_pEditSettings->GetLineVisible(4))
			m_chbNote4.SetCheck(BST_CHECKED);
		if(m_pEditSettings->GetLineVisible(5))
			m_chbNote5.SetCheck(BST_CHECKED);
		if(m_pEditSettings->GetLineVisible(6))
			m_chbNoteUpper1.SetCheck(BST_CHECKED);
		if (m_pEditSettings->GetLineVisible(7))
			m_chbNoteUpper2.SetCheck(BST_CHECKED);
		if(m_pEditSettings->GetLineVisible(8))
			m_chbNoteUpper3.SetCheck(BST_CHECKED);

		if(m_pEditSettings->m_nClef == TREBBLE_CLEF)
		{
			CheckDlgButton(IDC_RADIO_TREBLE_CLEF, BST_CHECKED);
			CheckDlgButton(IDC_RADIO_BASS_CLEF, BST_UNCHECKED);
		}
		else if(m_pEditSettings->m_nClef == BASS_CLEF)
		{
			CheckDlgButton(IDC_RADIO_BASS_CLEF, BST_CHECKED);
			CheckDlgButton(IDC_RADIO_TREBLE_CLEF, BST_UNCHECKED);
		}
	}

	return TRUE;
}

void CDlgNoteTrainerSettings::OnDestroy()
{
	CDialogEx::OnDestroy();
}

void CDlgNoteTrainerSettings::OnBnClickedBtnChooseColorBackground()
{
	CColorDialog dlgColor(m_pEditSettings->m_clrBackground);
	if(dlgColor.DoModal()!=IDOK)
		return;
	if(m_pEditSettings != nullptr)
	{
		m_pEditSettings->m_clrBackground = dlgColor.GetColor();
	}
	m_sttColorPreviewBackground.SetColor(m_pEditSettings->m_clrBackground);

}


void CDlgNoteTrainerSettings::OnBnClickedOk()
{
	if(m_pEditSettings != nullptr)
	{
		int nState = IsDlgButtonChecked(IDC_RADIO_TREBLE_CLEF);
		if(nState == BST_CHECKED)
			m_pEditSettings->m_nClef = TREBBLE_CLEF;
		else
			m_pEditSettings->m_nClef = BASS_CLEF;

		nState = IsDlgButtonChecked(IDC_CHECK_LOWER3);
		if(nState == BST_CHECKED)
			m_pEditSettings->SetLineVisible(-3, TRUE);

		nState = IsDlgButtonChecked(IDC_CHECK_LOWER2);
		if(nState == BST_CHECKED)
			m_pEditSettings->SetLineVisible(-2, TRUE);

		nState = IsDlgButtonChecked(IDC_CHECK_LOWER1);
		if(nState == BST_CHECKED)
			m_pEditSettings->SetLineVisible(-1, TRUE);

		nState = IsDlgButtonChecked(IDC_CHECK1);
		if(nState == BST_CHECKED)
			m_pEditSettings->SetLineVisible(1, TRUE);

		nState = IsDlgButtonChecked(IDC_CHECK2);
		if(nState == BST_CHECKED)
			m_pEditSettings->SetLineVisible(2, TRUE);

		nState = IsDlgButtonChecked(IDC_CHECK3);
		if(nState == BST_CHECKED)
			m_pEditSettings->SetLineVisible(3, TRUE);

		nState = IsDlgButtonChecked(IDC_CHECK4);
		if(nState == BST_CHECKED)
			m_pEditSettings->SetLineVisible(4, TRUE);

		nState = IsDlgButtonChecked(IDC_CHECK5);
		if(nState == BST_CHECKED)
			m_pEditSettings->SetLineVisible(5, TRUE);

		nState = IsDlgButtonChecked(IDC_CHECK_UPPER1);
		if(nState == BST_CHECKED)
			m_pEditSettings->SetLineVisible(6, TRUE);

		nState = IsDlgButtonChecked(IDC_CHECK_UPPER1);
		if(nState == BST_CHECKED)
			m_pEditSettings->SetLineVisible(6, TRUE);

		nState = IsDlgButtonChecked(IDC_CHECK_UPPER2);
		if(nState == BST_CHECKED)
			m_pEditSettings->SetLineVisible(7, TRUE);

		nState = IsDlgButtonChecked(IDC_CHECK_UPPER3);
		if(nState == BST_CHECKED)
			m_pEditSettings->SetLineVisible(8, TRUE);
	}


	if(nullptr != m_pOriginSettings)
		m_pOriginSettings->Copy(m_pEditSettings);
	CDialogEx::OnOK();
}


void CDlgNoteTrainerSettings::OnEnChangeEdtSheetHeight()
{
	CString strValue;
	m_edtSheetHeight.GetWindowText(strValue);
	int nValue = 0;
	StrToIntEx(strValue, STIF_DEFAULT, &nValue);
	if(m_pEditSettings != nullptr)
	{
		m_pEditSettings->m_nSheetHeight = nValue;
	}
}


void CDlgNoteTrainerSettings::OnBnClickedBtnChooseColorSheetBackground()
{
	CColorDialog dlgColor(m_pEditSettings->m_clrSheetBackground);
	if(dlgColor.DoModal()!=IDOK)
		return;
	if(m_pEditSettings != nullptr)
	{
		m_pEditSettings->m_clrSheetBackground = dlgColor.GetColor();
	}
	m_sttColorPreviewSheetBackground.SetColor(m_pEditSettings->m_clrSheetBackground);
}


void CDlgNoteTrainerSettings::OnEnChangeEdtSheetBorderWidth()
{
	CString strValue;
	m_edtSheetBorderWidth.GetWindowText(strValue);
	int nValue = 0;
	StrToIntEx(strValue, STIF_DEFAULT, &nValue);
	if(m_pEditSettings != nullptr)
	{
		m_pEditSettings->m_nSheetBorderWidth = nValue;
	}
}


void CDlgNoteTrainerSettings::OnBnClickedBtnChooseColorSheetBorder()
{
	CColorDialog dlgColor(m_pEditSettings->m_clrSheetBorderColor);
	if(dlgColor.DoModal()!=IDOK)
		return;
	if(m_pEditSettings != nullptr)
	{
		m_pEditSettings->m_clrSheetBorderColor = dlgColor.GetColor();
	}
	m_sttColorPreviewSheetBackground.SetColor(m_pEditSettings->m_clrSheetBorderColor);
}


void CDlgNoteTrainerSettings::OnEnChangeEdtSheetPadding()
{
	CString strValue;
	m_edtSheetPadding.GetWindowText(strValue);
	int nValue = 0;
	StrToIntEx(strValue, STIF_DEFAULT, &nValue);
	if(m_pEditSettings != nullptr)
	{
		m_pEditSettings->m_nSheetPadding = nValue;
	}
}


void CDlgNoteTrainerSettings::OnBnClickedBtnChooseColorLine()
{
	CColorDialog dlgColor(m_pEditSettings->m_clrLine);
	if(dlgColor.DoModal()!=IDOK)
		return;
	if(m_pEditSettings != nullptr)
	{
		m_pEditSettings->m_clrLine = dlgColor.GetColor();
	}
	m_sttColorPreviewLine.SetColor(m_pEditSettings->m_clrLine);
}


void CDlgNoteTrainerSettings::OnEnChangeEdtLineWidth()
{
	CString strValue;
	m_edtLineWidth.GetWindowText(strValue);
	int nValue = 0;
	StrToIntEx(strValue, STIF_DEFAULT, &nValue);
	if(m_pEditSettings != nullptr)
	{
		m_pEditSettings->m_nLineWidth = nValue;
	}
}

void CDlgNoteTrainerSettings::OnBnClickedCheckLower3()
{
	int nState = m_chbNoteLower3.GetCheck();
	if(nState == BST_CHECKED)
	{
		int nStateLower2 = m_chbNoteLower2.GetCheck();
		int nStateLower1 = m_chbNoteLower1.GetCheck();
		if(nStateLower2 != BST_CHECKED)
			m_chbNoteLower2.SetCheck(BST_CHECKED);
		if(nStateLower1 != BST_CHECKED)
			m_chbNoteLower1.SetCheck(BST_CHECKED);
	}
	else if(nState == BST_UNCHECKED)
	{
	}
}


void CDlgNoteTrainerSettings::OnBnClickedCheckLower2()
{
	int nState = m_chbNoteLower2.GetCheck();
	if(nState == BST_CHECKED)
	{
		int nStateLower1 = m_chbNoteLower1.GetCheck();
		if(nStateLower1 != BST_CHECKED)
			m_chbNoteLower1.SetCheck(BST_CHECKED);
	}
	else if(nState == BST_UNCHECKED)
	{
		int nStateLower3 = m_chbNoteLower3.GetCheck();
		if(nStateLower3 != BST_UNCHECKED)
			m_chbNoteLower3.SetCheck(BST_UNCHECKED);
	}
}


void CDlgNoteTrainerSettings::OnBnClickedCheckLower1()
{
	int nState = m_chbNoteLower1.GetCheck();
	if(nState == BST_CHECKED)
	{
	}
	else if(nState == BST_UNCHECKED)
	{
		int nStateLower3 = m_chbNoteLower3.GetCheck();
		if(nStateLower3 != BST_UNCHECKED)
			m_chbNoteLower3.SetCheck(BST_UNCHECKED);
		int nStateLower2 = m_chbNoteLower2.GetCheck();
		if(nStateLower2 != BST_UNCHECKED)
			m_chbNoteLower2.SetCheck(BST_UNCHECKED);
	}
}


void CDlgNoteTrainerSettings::OnBnClickedCheck1()
{
	int nState = m_chbNote1.GetCheck();
	if(nState == BST_CHECKED)
	{
	}
	else if(nState == BST_UNCHECKED)
	{
	}
}


void CDlgNoteTrainerSettings::OnBnClickedCheck2()
{
	int nState = m_chbNote2.GetCheck();
	if(nState == BST_CHECKED)
	{
	}
	else if(nState == BST_UNCHECKED)
	{
	}
}


void CDlgNoteTrainerSettings::OnBnClickedCheck3()
{
	int nState = m_chbNote3.GetCheck();
	if(nState == BST_CHECKED)
	{
	}
	else if(nState == BST_UNCHECKED)
	{
	}
}


void CDlgNoteTrainerSettings::OnBnClickedCheck4()
{
	int nState = m_chbNote4.GetCheck();
	if(nState == BST_CHECKED)
	{
	}
	else if(nState == BST_UNCHECKED)
	{
	}
}


void CDlgNoteTrainerSettings::OnBnClickedCheck5()
{
	int nState = m_chbNote5.GetCheck();
	if(nState == BST_CHECKED)
	{
	}
	else if(nState == BST_UNCHECKED)
	{
	}
}


void CDlgNoteTrainerSettings::OnBnClickedCheckUpper1()
{
	int nState = m_chbNoteUpper1.GetCheck();
	if(nState == BST_CHECKED)
	{
	}
	else if(nState == BST_UNCHECKED)
	{
	}
}


void CDlgNoteTrainerSettings::OnBnClickedCheckUpper2()
{
	int nState = m_chbNoteUpper2.GetCheck();
	if(nState == BST_CHECKED)
	{
	}
	else if(nState == BST_UNCHECKED)
	{
	}
}


void CDlgNoteTrainerSettings::OnBnClickedCheckUpper3()
{
	int nState = m_chbNoteUpper3.GetCheck();
	if(nState == BST_CHECKED)
	{
	}
	else if(nState == BST_UNCHECKED)
	{
	}
}


void CDlgNoteTrainerSettings::OnBnClickedRadioBassClef()
{
	int nState = IsDlgButtonChecked(IDC_RADIO_BASS_CLEF);
	if(nState == BST_CHECKED)
		CheckDlgButton(IDC_RADIO_TREBLE_CLEF, BST_UNCHECKED);
	else if(nState == BST_UNCHECKED)
		CheckDlgButton(IDC_RADIO_TREBLE_CLEF, BST_CHECKED);
}


void CDlgNoteTrainerSettings::OnBnClickedRadioTrebleClef()
{
	int nState = IsDlgButtonChecked(IDC_RADIO_TREBLE_CLEF);
	if(nState == BST_CHECKED)
		CheckDlgButton(IDC_RADIO_BASS_CLEF, BST_UNCHECKED);
	else if(nState == BST_UNCHECKED)
		CheckDlgButton(IDC_RADIO_BASS_CLEF, BST_CHECKED);
}
