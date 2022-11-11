#pragma once

class CColorItemListBox : public CListBox
{
	DECLARE_DYNAMIC(CColorItemListBox)

public:
	CColorItemListBox(void);
	~CColorItemListBox(void);

	void SetItemColor(DWORD_PTR dwItemData, COLORREF clColor);

protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);


	struct tagCOLOR
	{
		DWORD_PTR dwItemData;
		COLORREF clColor;
	};
	CList<tagCOLOR> m_listColor;
};