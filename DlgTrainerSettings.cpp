// DlgTrainerSettings.cpp : implementation file
//

#include "stdafx.h"
#include "MIDISample.h"
#include "DlgTrainerSettings.h"
#include "afxdialogex.h"


// CDlgTrainerSettings dialog

IMPLEMENT_DYNAMIC(CDlgTrainerSettings, CDialogEx)

CDlgTrainerSettings::CDlgTrainerSettings(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTrainerSettings::IDD, pParent)
{

}

CDlgTrainerSettings::~CDlgTrainerSettings()
{
}

void CDlgTrainerSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTrainerSettings, CDialogEx)
END_MESSAGE_MAP()


// CDlgTrainerSettings message handlers
