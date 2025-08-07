#pragma once


// CDlgTrainerSettings dialog

class CDlgTrainerSettings : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTrainerSettings)

public:
	CDlgTrainerSettings(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgTrainerSettings();

// Dialog Data
	enum { IDD = IDD_DLG_TRAINER_SETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
