#pragma once
#include "afxwin.h"

class CRowInfo : public CObject
{
public:
	CRowInfo(int index=-1, int height=1, BOOL visible = FALSE, int line = 0);
	virtual ~CRowInfo() {;}

	int Index;
	int Height;
	BOOL Visible;
	int Line;
	int Top;
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
	CDC m_dcSol;
	CDC m_dcFa;
	CObArray m_arrRowInfos;
};

