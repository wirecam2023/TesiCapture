#include "stdafx.h"
#include "ColorItemListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CColorItemListBox, CListBox)

CColorItemListBox::CColorItemListBox(void)
{
}

CColorItemListBox::~CColorItemListBox(void)
{
}

void CColorItemListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if ((int)lpDrawItemStruct->itemID < 0)
		return;

	TRACE("CColorItemListBox::DrawItem %li\n", lpDrawItemStruct->itemID);

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	COLORREF crText = RGB(0, 0, 0);
	COLORREF crNorm = RGB(0, 0, 0);

	for (INT_PTR i = 0; i < m_listColor.GetCount(); i++)
	{
		if (m_listColor.GetAt(m_listColor.FindIndex(i)).dwItemData == lpDrawItemStruct->itemData)
		{
			crNorm = m_listColor.GetAt(m_listColor.FindIndex(i)).clColor;
			break;
		}
	}

	COLORREF crHilite = RGB(255 - GetRValue(crNorm), 255 - GetGValue(crNorm), 255 - GetBValue(crNorm));

	// If item has been selected, draw the highlight rectangle using the item's color.
	if ((lpDrawItemStruct->itemState & ODS_SELECTED) &&
		(lpDrawItemStruct->itemAction & (ODA_SELECT | ODA_DRAWENTIRE | ODA_FOCUS)))
	{
		CBrush brush(::GetSysColor(COLOR_HIGHLIGHT));
		pDC->FillRect(&lpDrawItemStruct->rcItem, &brush);
		crText = RGB(255, 255, 255);
	}
	else
	{
		CBrush brush(crNorm > 0 ? crNorm : ::GetSysColor(COLOR_WINDOW));
		pDC->FillRect(&lpDrawItemStruct->rcItem, &brush);
	}

	// If item has focus, draw the focus rect.
	if ((lpDrawItemStruct->itemAction & ODA_FOCUS) && (lpDrawItemStruct->itemState & ODS_FOCUS))
		pDC->DrawFocusRect(&lpDrawItemStruct->rcItem);

	// If item does not have focus, redraw (erase) the focus rect.
	if ((lpDrawItemStruct->itemAction & ODA_FOCUS) && !(lpDrawItemStruct->itemState & ODS_FOCUS))
		pDC->DrawFocusRect(&lpDrawItemStruct->rcItem);

	// Set the background mode to TRANSPARENT to draw the text.
	int nBkMode = pDC->SetBkMode(TRANSPARENT);

	// If the item's color information is set, use the highlight color
	// gray text color, or normal color for the text.
	/*
	if (lpDrawItemStruct->itemState & ODS_SELECTED)
	crText = pDC->SetTextColor(crHilite);
	else if (lpDrawItemStruct->itemState & ODS_DISABLED)
	crText = pDC->SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
	else
	crText = pDC->SetTextColor(crNorm);*/

	// Else the item's color information is not set, so use the
	// system colors for the text.
	/*
	else
	{
	if (lpDrawItemStruct->itemState & ODS_SELECTED)
	crText = pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
	else if (lpDrawItemStruct->itemState & ODS_DISABLED)
	crText = pDC->SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
	else
	crText = pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
	}*/

	// Get and display item text.
	CString sText;
	GetText(lpDrawItemStruct->itemID, sText);
	CRect rect = lpDrawItemStruct->rcItem;

	// Setup the text format.
	UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER;
	if (GetStyle() & LBS_USETABSTOPS)
		nFormat |= DT_EXPANDTABS;

	COLORREF clColorOld = pDC->SetTextColor(crText);

	// Calculate the rectangle size before drawing the text.
	pDC->DrawText(sText, -1, &rect, nFormat | DT_CALCRECT);
	pDC->DrawText(sText, -1, &rect, nFormat);

	pDC->SetTextColor(clColorOld);
	pDC->SetBkMode(nBkMode);
}

void CColorItemListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	lpMeasureItemStruct->itemHeight = ::GetSystemMetrics(SM_CYMENUCHECK);
}

int CColorItemListBox::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{
	return 0;
}

void CColorItemListBox::SetItemColor(DWORD_PTR dwItemData, COLORREF clColor)
{
	for (INT_PTR i = 0; i < m_listColor.GetCount(); i++)
	{
		if (m_listColor.GetAt(m_listColor.FindIndex(i)).dwItemData == dwItemData)
		{
			m_listColor.RemoveAt(m_listColor.FindIndex(i));
			break;
		}
	}

	tagCOLOR tc;
	tc.dwItemData = dwItemData;
	tc.clColor = clColor;
	m_listColor.AddTail(tc);
}