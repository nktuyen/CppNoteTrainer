#include "stdafx.h"
#include "ColorPreviewLabel.h"


CColorPreviewLabel::CColorPreviewLabel(COLORREF color)
	:CStatic()
	,m_color(color)
	,m_bInitilized(FALSE)
{

}


CColorPreviewLabel::~CColorPreviewLabel(void)
{
}


void CColorPreviewLabel::SetColor(COLORREF color)
{
	if(!m_bInitilized)
		Initialize();
	m_color = color;
	if(GetSafeHwnd())
		Invalidate();
}

COLORREF CColorPreviewLabel::GetColor()
{
	return m_color;
}

BEGIN_MESSAGE_MAP(CColorPreviewLabel, CStatic)
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

void CColorPreviewLabel::DrawItem(LPDRAWITEMSTRUCT lpDrawStruct)
{
	if(!m_bInitilized)
		Initialize();
	CBrush br;
	br.CreateSolidBrush(m_color);
	::FillRect(lpDrawStruct->hDC, CRect(lpDrawStruct->rcItem), (HBRUSH)br.GetSafeHandle());
	br.DeleteObject();
}


void CColorPreviewLabel::OnDestroy()
{
	CStatic::OnDestroy();
}

void CColorPreviewLabel::Initialize()
{
	if(!m_bInitilized)
	{
		if(GetSafeHwnd())
		{
			ModifyStyle(0, SS_OWNERDRAW);
		}
		m_bInitilized = TRUE;
	}
}

void CColorPreviewLabel::OnLButtonUp(UINT nFlag, CPoint point)
{
	CStatic::OnLButtonUp(nFlag, point);
}