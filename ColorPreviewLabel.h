#pragma once
#include "afxwin.h"

class CColorPreviewLabel : public CStatic
{
public:
	CColorPreviewLabel(COLORREF color = 0);
	virtual ~CColorPreviewLabel(void);
	void SetColor(COLORREF color);
	COLORREF GetColor();

	DECLARE_MESSAGE_MAP()
protected:
	void Initialize();
	void DrawItem(LPDRAWITEMSTRUCT lpDrawStruct) override;
	afx_msg void OnDestroy();
	afx_msg void OnLButtonUp(UINT nFlag, CPoint point);
private:
	BOOL m_bInitilized;
	COLORREF m_color;
};

