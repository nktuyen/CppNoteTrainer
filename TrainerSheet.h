#pragma once
#include "afxwin.h"

class CRowInfo : public CObject
{
public:
	CRowInfo(int index=-1, int height=1, BOOL visible = FALSE, BOOL line = FALSE);
	virtual ~CRowInfo() {;}

	int Index;
	int Height;
	BOOL Visible;
	BOOL IsLine;
};


class CTrainerSheet : public CStatic
{
public:
	CTrainerSheet(void);
	virtual ~CTrainerSheet(void);
private:
	void OnInitialize();
	void DrawItem(LPDRAWITEMSTRUCT) override;
private:
	CFont m_font;
	BOOL m_bInitialize;
	COLORREF m_clrBackground;
	COLORREF m_clrSheetBorder;
	CPen m_penSheetBorder;
	CBrush m_brBackground;
	CDC m_dcSol;
	CDC m_dcFa;
	CSize m_szSheetSize;
	UINT m_nMaxRows;
	UINT m_nPadding;
	CPen m_penVisibleLines;
	CPen m_penInvisibleLines;
	CPen m_penVisibleLines2;
	UINT m_nPenWidth;
	CObArray m_arrRowInfos;
};

