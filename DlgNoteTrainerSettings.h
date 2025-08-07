#pragma once
#include "afxwin.h"
#include "ColorPreviewLabel.h"
#include "afxcmn.h"

// CDlgNoteTrainerSettings dialog
class CNoteTrainerSettings;

class CDlgNoteTrainerSettings : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgNoteTrainerSettings)

public:
	CDlgNoteTrainerSettings(CWnd* pParent = NULL, CNoteTrainerSettings* pSettings = nullptr);   // standard constructor
	virtual ~CDlgNoteTrainerSettings();

// Dialog Data
	enum { IDD = IDD_DLG_TRAINER_SETTINGS };
	DECLARE_MESSAGE_MAP()
private:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog() override;
private:
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnChooseColorBackground();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdtSheetHeight();
	afx_msg void OnBnClickedBtnChooseColorSheetBackground();
	afx_msg void OnEnChangeEdtSheetBorderWidth();
	afx_msg void OnBnClickedBtnChooseColorSheetBorder();
	afx_msg void OnEnChangeEdtSheetPadding();
	afx_msg void OnBnClickedBtnChooseColorLine();
	afx_msg void OnEnChangeEdtLineWidth();
private:
	CNoteTrainerSettings* m_pOriginSettings;
	CNoteTrainerSettings* m_pEditSettings;
	CColorPreviewLabel m_sttColorPreviewBackground;
	CEdit m_edtSheetHeight;
	CSpinButtonCtrl m_spinSheetHeight;
	CColorPreviewLabel m_sttColorPreviewSheetBackground;
	CSpinButtonCtrl m_spinSheetBorderWidth;
	CEdit m_edtSheetBorderWidth;
	CColorPreviewLabel m_sttColorPreviewSheetBorder;
	CSpinButtonCtrl m_spinSheetPadding;
	CEdit m_edtSheetPadding;
	CColorPreviewLabel m_sttColorPreviewLine;
	CEdit m_edtLineWidth;
	CSpinButtonCtrl m_spinLineWidth;
	CButton m_chbNote1;
	CButton m_chbNote2;
	CButton m_chbNote3;
	CButton m_chbNote4;
	CButton m_chbNote5;
	CButton m_chbNoteUpper1;
	CButton m_chbNoteUpper2;
	CButton m_chbNoteUpper3;
	CButton m_chbNoteLower1;
	CButton m_chbNoteLower2;
	CButton m_chbNoteLower3;
public:
	afx_msg void OnBnClickedCheckLower3();
	afx_msg void OnBnClickedCheckLower2();
	afx_msg void OnBnClickedCheckLower1();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheckUpper1();
	afx_msg void OnBnClickedCheckUpper2();
	afx_msg void OnBnClickedCheckUpper3();
	afx_msg void OnBnClickedRadioBassClef();
	afx_msg void OnBnClickedRadioTrebleClef();
};
