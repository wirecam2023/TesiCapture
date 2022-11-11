#pragma once

class CEndoGridTheme : public CXTPPropertyGridCoolTheme
{
public:
	CEndoGridTheme(CXTPPropertyGrid* pGrid);
	~CEndoGridTheme(void);

	virtual COLORREF GetItemBackColor(CXTPPropertyGridItem* pItem, BOOL bValuePart);

protected:
	virtual void DrawItem(PDRAWITEMSTRUCT lpDrawItemStruct);
};
