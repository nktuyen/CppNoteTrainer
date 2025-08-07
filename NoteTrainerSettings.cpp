#include "stdafx.h"
#include "NoteTrainerSettings.h"

CNoteTrainerSettings* CNoteTrainerSettings::GetInstance()
{
	static CNoteTrainerSettings* pInstance = nullptr;
	if(pInstance == nullptr)
		pInstance = new CNoteTrainerSettings();
	return pInstance;
}


const int LineIndexes[11] = {-3,-2,-1,1,2,3,4,5,6,7,8};

CNoteTrainerSettings::CNoteTrainerSettings(void)
{
	m_clrBackground = DEF_COLOR_BACKGROUND;
	m_nSheetHeight = DEF_HEIGHT_SHEET;
	m_clrSheetBackground = DEF_COLOR_SHEET_BACKGROUND;
	m_nSheetBorderWidth = DEF_WIDTH_SHEET_BORDER;
	m_clrSheetBorderColor = DEF_COLOR_SHEET_BORDER;
	m_nSheetPadding = DEF_PADDING_SHEET;
	m_clrLine = DEF_COLOR_LINE;
	m_nLineWidth = DEF_LINE_WIDTH;
	m_nClef = TREBBLE_CLEF;
}


CNoteTrainerSettings::~CNoteTrainerSettings(void)
{
}

void CNoteTrainerSettings::Initialize()
{
	SetLineVisible(1, TRUE);
	SetLineVisible(2, TRUE);
	SetLineVisible(3, TRUE);
	SetLineVisible(4, TRUE);
	SetLineVisible(5, TRUE);
}

void CNoteTrainerSettings::SetLineVisible(int index, BOOL bVisible)
{
	m_MapVisibility[index] = bVisible;
}

BOOL CNoteTrainerSettings::GetLineVisible(int index)
{
	BOOL bVisible = FALSE;
	if(m_MapVisibility.Lookup(index, bVisible))
		return bVisible;
	return FALSE;
}

CNoteTrainerSettings* CNoteTrainerSettings::Clone()
{
	CNoteTrainerSettings* pNewSettings = new CNoteTrainerSettings();
	pNewSettings->Copy(this);
	return pNewSettings;
}

BOOL CNoteTrainerSettings::Copy(CNoteTrainerSettings* pOther)
{
	if(nullptr == pOther)
		return FALSE;

	this->m_clrBackground = pOther->m_clrBackground;
	this->m_nSheetHeight = pOther->m_nSheetHeight;
	this->m_clrSheetBackground = pOther->m_clrSheetBackground;
	this->m_nSheetBorderWidth = pOther->m_nSheetBorderWidth;
	this->m_clrSheetBorderColor = pOther->m_clrSheetBorderColor;
	this->m_nSheetPadding = pOther->m_nSheetPadding;
	this->m_clrLine = pOther->m_clrLine;
	this->m_nLineWidth = pOther->m_nLineWidth;
	this->m_nClef = pOther->m_nClef;
	//Copy visibility map
	this->m_MapVisibility.RemoveAll();
	POSITION p=pOther->m_MapVisibility.GetStartPosition();
	int index = -1;
	BOOL bVisible = FALSE;
	while (p)
	{
		pOther->m_MapVisibility.GetNextAssoc(p, index, bVisible);
		this->m_MapVisibility.SetAt(index, bVisible);
	}
	//
	return TRUE;
}