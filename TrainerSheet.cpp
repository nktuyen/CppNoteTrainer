#include "stdafx.h"
#include "TrainerSheet.h"
#include "resource.h"

CRowInfo::CRowInfo(int index, int height, BOOL visible, BOOL line)
	: CObject()
	, Index(index)
	, Height(height)
	, Visible(visible)
	, IsLine(line)
{

}

CTrainerSheet::CTrainerSheet(void)
	: m_bInitialize(FALSE)
{
	m_clrBackground = RGB(255, 255, 255);
	m_szSheetSize.SetSize(0, 300);
	m_nPenWidth = 2;
	m_nMaxRows = 11;
	m_nPadding = 10;
	m_clrSheetBorder = RGB(0, 255, 0);
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
	rcDraw.DeflateRect(m_nPadding, m_nPadding, m_nPadding, m_nPadding);
	UINT nWidth = rcDraw.Width();
	UINT nHeight = rcDraw.Height();
	UINT nNoteHeight = 0;
	UINT nKeyTop = 0;
	UINT nKeyHeight = 0;
	if(pDc)
	{
		pDc->FillRect(rcDraw, &m_brBackground);
		pDc->SetBkMode(TRANSPARENT);
		pDc->SelectObject(m_penSheetBorder);
		CRect rcSheet;
		rcSheet.left = rcDraw.left;
		rcSheet.top = rcDraw.top + (rcDraw.Height()/2)-(m_szSheetSize.cy/2);
		rcSheet.right = rcDraw.right;
		rcSheet.bottom = rcSheet.top + m_szSheetSize.cy;
		rcSheet.DeflateRect(m_nPadding, m_nPadding, m_nPadding, m_nPadding);
		nNoteHeight = m_szSheetSize.cy/(m_nMaxRows*2);
		pDc->Rectangle(rcSheet);
		for(UINT nRow=0;nRow<(m_nMaxRows*2);nRow++)
		{
			CRowInfo* pRowInfo =(CRowInfo*) m_arrRowInfos.GetAt(nRow);
			if(pRowInfo != NULL)
			{
				if(pRowInfo->Visible && pRowInfo->IsLine)
				{
					nKeyHeight +=pRowInfo->Height;
					if(nKeyTop == 0)
						nKeyTop = nRow*nKeyHeight;
				}
			}
		}
		//pDc->StretchBlt(rcSheet.left, rcDraw.top+nKeyTop-nNoteHeight*1, 64, nKeyHeight+nNoteHeight*1, &m_dcSol, 0, 0, 64, 128,  SRCCOPY);

		for(UINT nRow=0;nRow<(m_nMaxRows*2);nRow++)
		{
			CRowInfo* pRowInfo =(CRowInfo*) m_arrRowInfos.GetAt(nRow);
			if(pRowInfo != NULL)
			{
				pDc->SelectObject(m_penSheetBorder);
				rcSheet.top+=pRowInfo->Height;
				rcSheet.bottom = rcSheet.top + pRowInfo->Height;
				pDc->MoveTo(rcSheet.left, rcSheet.top);
				pDc->LineTo(rcSheet.right, rcSheet.top);


				if(pRowInfo->Visible)
				{
					if(pRowInfo->IsLine)
						pDc->SelectObject(m_penVisibleLines);
					else
						pDc->SelectObject(m_penVisibleLines2);
				}
				else
				{
					pDc->SelectObject(m_penInvisibleLines);
				}
				pDc->MoveTo(rcSheet.left+10, rcSheet.top);
				pDc->LineTo(rcSheet.right, rcSheet.top);
			}
		}
	}
}

void CTrainerSheet::OnInitialize()
{
	if(!m_bInitialize)
	{
		UINT nNoteHeight = m_szSheetSize.cy/(m_nMaxRows*2);
		for(int index=0;index<(int)(m_nMaxRows*2);index++)
		{
			BOOL bVisible = FALSE;
			if(index >= 10 && index <= 20)
				bVisible = TRUE;
			m_arrRowInfos.Add(new CRowInfo(index, nNoteHeight, bVisible, index%2!=0));
		}

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
		m_brBackground.CreateSolidBrush(m_clrBackground);

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

		m_penVisibleLines.CreatePen(PS_SOLID, m_nPenWidth, RGB(0,0,0));
		m_penVisibleLines2.CreatePen(PS_DASH, 1, RGB(255,0,0));
		m_penInvisibleLines.CreatePen(PS_SOLID, m_nPenWidth, m_clrBackground);
		m_penSheetBorder.CreatePen(PS_SOLID, m_nPenWidth, m_clrSheetBorder);
		//
		m_bInitialize = TRUE;
	}
}