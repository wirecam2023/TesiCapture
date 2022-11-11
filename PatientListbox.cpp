#include "stdafx.h"
#include "Endox.h"
#include "PatientListbox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CPatientListBox, CListBox)

CPatientListBox::CPatientListBox()
{
}

CPatientListBox::~CPatientListBox()
{
}

BEGIN_MESSAGE_MAP(CPatientListBox, CListBox)	
	ON_WM_DESTROY()
END_MESSAGE_MAP()

int CPatientListBox::AddString(LPCTSTR lpszItem)
{
	return AddString(lpszItem, RGB_BLACK, RGB_WHITE);
}

int CPatientListBox::AddString(LPCTSTR lpszItem, COLORREF fgColor, COLORREF bgColor)
{
	LISTBOX_COLOR* pInfo = new LISTBOX_COLOR;

	strcpy_s(pInfo->strText, strlen(lpszItem) + 1, lpszItem);
	pInfo->fgColor = fgColor; 
	pInfo->bgColor = bgColor;

	int nReturn = CListBox::AddString(pInfo->strText);
	SetItemDataPtr(nReturn, pInfo);

	return nReturn;
}

int CPatientListBox::DeleteString(UINT nIndex)
{
	LISTBOX_COLOR* pList = (LISTBOX_COLOR*)GetItemDataPtr(nIndex);
	delete pList;
	pList = NULL;

	return CListBox::DeleteString(nIndex);
}

int CPatientListBox::InsertString(int nIndex, LPCTSTR lpszItem)
{
	return InsertString(nIndex, lpszItem, RGB_BLACK, RGB_WHITE);
}

int CPatientListBox::InsertString(int nIndex, LPCTSTR lpszItem, COLORREF fgColor, COLORREF bgColor)
{
	LISTBOX_COLOR* pInfo = new LISTBOX_COLOR;

	strcpy_s(pInfo->strText, strlen(lpszItem) + 1, lpszItem);
	pInfo->fgColor = fgColor; 
	pInfo->bgColor = bgColor;

	int nReturn = CListBox::InsertString(nIndex, pInfo->strText);
	SetItemDataPtr(nReturn, pInfo);

	return nReturn;
}

int CPatientListBox::SetItemData(int index, DWORD value)
{
	if (index >= GetCount())
		return LB_ERR;

	LISTBOX_COLOR* pInfo = (LISTBOX_COLOR*) GetItemDataPtr(index);
	pInfo->iValue = value;

	return LB_OKAY;
}

DWORD CPatientListBox::GetItemData(int index)
{
	if (index >= GetCount())
		return -1;

	LISTBOX_COLOR* pInfo = (LISTBOX_COLOR*) GetItemDataPtr(index);
	return pInfo->iValue;
}

void CPatientListBox::GetText(int index, CString &value)
{
	ASSERT(index < GetCount());

	LISTBOX_COLOR* pInfo = (LISTBOX_COLOR*) GetItemDataPtr(index);
	value = pInfo->strText;
}

void CPatientListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	ASSERT(lpDrawItemStruct->CtlType == ODT_LISTBOX);
	LISTBOX_COLOR* pListBox = (LISTBOX_COLOR*)GetItemDataPtr(lpDrawItemStruct->itemID);
	ASSERT(NULL != pListBox);
	CDC dc;

	dc.Attach(lpDrawItemStruct->hDC);

	// Save these value to restore them when done drawing.
	COLORREF crOldTextColor = dc.GetTextColor();
	COLORREF crOldBkColor = dc.GetBkColor();

	// If this item is selected, set the background color 
	// and the text color to appropriate values. Also, erase
	// rect by filling it with the background color.
	if ((lpDrawItemStruct->itemAction | ODA_SELECT) && (lpDrawItemStruct->itemState & ODS_SELECTED))
	{
		dc.SetTextColor(pListBox->bgColor);
		dc.SetBkColor(pListBox->fgColor);
		dc.FillSolidRect(&lpDrawItemStruct->rcItem, pListBox->fgColor);		
	}
	else
	{
		dc.SetTextColor(pListBox->fgColor);
		dc.SetBkColor(pListBox->bgColor);
		dc.FillSolidRect(&lpDrawItemStruct->rcItem, pListBox->bgColor);
	}

	lpDrawItemStruct->rcItem.left += 5;
	// Draw the text.
	dc.DrawText(pListBox->strText, strlen(pListBox->strText), &lpDrawItemStruct->rcItem, DT_WORDBREAK);	

	// Reset the background color and the text color back to their
	// original values.
	dc.SetTextColor(crOldTextColor);
	dc.SetBkColor(crOldBkColor);

	dc.Detach(); 
}

void CPatientListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your code to determine the size of specified item
	ASSERT(lpMeasureItemStruct->CtlType == ODT_LISTBOX);

	CString strText("&#00;");
	GetText(lpMeasureItemStruct->itemID, strText);
	ASSERT(TRUE != strText.IsEmpty());
	CRect rect;
	GetItemRect(lpMeasureItemStruct->itemID, &rect);

	CDC* pDC = GetDC(); 
	lpMeasureItemStruct->itemHeight = pDC->DrawText(strText, -1, rect, 
	DT_WORDBREAK | DT_CALCRECT); 
	ReleaseDC(pDC);
} 

void CPatientListBox::OnDestroy() 
{
	CListBox::OnDestroy();

	int nCount = GetCount();
	for(int i=0; i<nCount; i++)
	{
		LISTBOX_COLOR* pList = (LISTBOX_COLOR*)GetItemDataPtr(i);
		delete pList;
		pList = NULL;
	}
}