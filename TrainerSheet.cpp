#include "stdafx.h"
#include "TrainerSheet.h"
#include "resource.h"
#include "NoteTrainerSettings.h"


CRowInfo::CRowInfo(int index, int height, BOOL visible, int line)
	: CObject()
	, Index(index)
	, Height(height)
	, Visible(visible)
	, Line(line)
	, Top(-1)
{

}

CTrainerSheet::CTrainerSheet(void)
	: m_bInitialize(FALSE)
{
	
}


CTrainerSheet::~CTrainerSheet(void)
{
	CRowInfo* pRow = nullptr;
	for(INT_PTR i=0;i<m_arrRowInfos.GetCount();i++)
	{
		pRow = (CRowInfo*)m_arrRowInfos.GetAt(i);
		if(pRow)
			delete pRow;
	}
}

void CTrainerSheet::DrawItem(LPDRAWITEMSTRUCT lpDrawStruct)
{
	if(!m_bInitialize)
		OnInitialize();

	CDC *pDc = CDC::FromHandle(lpDrawStruct->hDC);
	CRect rcDraw = CRect(lpDrawStruct->rcItem);
	UINT nWidth = rcDraw.Width();
	UINT nHeight = rcDraw.Height();
	UINT nRowHeight = 0;
	UINT nKeyTop = 0;
	UINT nKeyHeight = 0;
	if(pDc)
	{
		//Draw window background
		CBrush brBackground;
		brBackground.CreateSolidBrush(CNoteTrainerSettings::GetInstance()->m_clrBackground);
		pDc->SelectObject(brBackground);
		pDc->FillRect(rcDraw, &brBackground);
		//Draw sheet background
		CRect rcSheet;
		rcSheet.left = rcDraw.left;
		rcSheet.top = rcDraw.top + (rcDraw.Height()/2)-(CNoteTrainerSettings::GetInstance()->m_nSheetHeight/2);
		rcSheet.right = rcDraw.right;
		rcSheet.bottom = rcSheet.top + CNoteTrainerSettings::GetInstance()->m_nSheetHeight;
		CBrush brSheetBackground;
		brSheetBackground.CreateSolidBrush(CNoteTrainerSettings::GetInstance()->m_clrSheetBackground);
		pDc->SelectObject(brSheetBackground);
		pDc->FillRect(rcSheet, &brSheetBackground);

		//Draw sheet border
		if(CNoteTrainerSettings::GetInstance()->m_nSheetBorderWidth > 0)
		{
			CPen penSheetBorder;
			penSheetBorder.CreatePen(PS_SOLID, CNoteTrainerSettings::GetInstance()->m_nSheetBorderWidth, CNoteTrainerSettings::GetInstance()->m_clrSheetBorderColor);
			pDc->SelectObject(penSheetBorder);
			pDc->Rectangle(rcSheet);
		}
		//Draw sheet contents
		rcSheet.DeflateRect(CNoteTrainerSettings::GetInstance()->m_nSheetPadding, CNoteTrainerSettings::GetInstance()->m_nSheetPadding, CNoteTrainerSettings::GetInstance()->m_nSheetPadding, CNoteTrainerSettings::GetInstance()->m_nSheetPadding);
		nRowHeight = CNoteTrainerSettings::GetInstance()->m_nSheetHeight/(m_arrRowInfos.GetCount()+1);
		for(INT_PTR nRow=0;nRow<m_arrRowInfos.GetCount();nRow++)
		{
			CRowInfo* pRowInfo = (CRowInfo*)m_arrRowInfos.GetAt(nRow);
			if(pRowInfo)
			{
				pRowInfo->Height = nRowHeight;
				pRowInfo->Top = rcSheet.top + (nRow*nRowHeight);
				if(pRowInfo->Visible)
				{
					if(pRowInfo->Line != 0)
					{
						CPen penLine;
						penLine.CreatePen(PS_SOLID, CNoteTrainerSettings::GetInstance()->m_nLineWidth, CNoteTrainerSettings::GetInstance()->m_clrLine);
						pDc->SelectObject(penLine);
						pDc->MoveTo(rcSheet.left, pRowInfo->Top);
						pDc->LineTo(rcSheet.right, pRowInfo->Top);
					}
					else
					{
					}
				}
				else
				{
				
				}
			}
		}
	}
}

void CTrainerSheet::OnInitialize()
{
	if(!m_bInitialize)
	{
		//Create row infos
		

		LOGFONT lf = {0};
		ZeroMemory(&lf, sizeof(LOGFONT));
		CFont* pFont = GetFont();
		if(pFont)
		{
			pFont->GetLogFont(&lf);
			lf.lfHeight = 72;
			if(m_font.CreateFontIndirect(&lf))
				SetFont(&m_font);
		}

		m_dcSol.CreateCompatibleDC(CDC::FromHandle(::GetDC(0)));
		HBITMAP hBmpSolKey = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_SOL_KEY));
		if(hBmpSolKey)
		{
			m_dcSol.SelectObject(hBmpSolKey);
		}
		m_dcFa.CreateCompatibleDC(CDC::FromHandle(::GetDC(0)));
		HBITMAP hBmpFaKey = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_FA_KEY));
		if(hBmpFaKey)
		{
			m_dcFa.SelectObject(hBmpFaKey);
		}
		//
		m_bInitialize = TRUE;
	}
}