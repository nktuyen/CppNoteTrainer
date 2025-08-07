#pragma once

#define DEF_COLOR_BACKGROUND			RGB(255, 255, 255)
#define DEF_HEIGHT_SHEET				428
#define DEF_COLOR_SHEET_BACKGROUND		RGB(250, 250, 200)
#define DEF_WIDTH_SHEET_BORDER			1
#define DEF_COLOR_SHEET_BORDER			RGB(255, 0, 0)
#define DEF_PADDING_SHEET				10
#define DEF_COLOR_LINE					RGB(0, 0, 255)
#define DEF_LINE_WIDTH					2
#define TREBBLE_CLEF					0
#define	BASS_CLEF						1


class CNoteTrainerSettings
{
private:
	CNoteTrainerSettings(void);
public:
	virtual ~CNoteTrainerSettings(void);
	static CNoteTrainerSettings* GetInstance();
	static void DeleteInstance();
	void Initialize();
	CNoteTrainerSettings* Clone();
	BOOL Copy(CNoteTrainerSettings* pOther);
	BOOL GetLineVisible(int index);
	void SetLineVisible(int index, BOOL bVisible);
public:
	COLORREF m_clrBackground;
	UINT m_nSheetHeight;
	COLORREF m_clrSheetBackground;
	UINT m_nSheetBorderWidth;
	COLORREF m_clrSheetBorderColor;
	UINT m_nSheetPadding;
	COLORREF m_clrLine;
	UINT m_nLineWidth;
	UINT m_nClef;
private:
	CMap<int,int, BOOL, BOOL> m_MapVisibility;
};

