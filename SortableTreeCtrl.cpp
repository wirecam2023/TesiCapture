#include "stdafx.h"
#include "SortableTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSortableTreeCtrl::CSortableTreeCtrl(void)
{
}

CSortableTreeCtrl::~CSortableTreeCtrl(void)
{
}

BOOL CSortableTreeCtrl::MoveSelectedUp()
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem == NULL)
		return FALSE;

	HTREEITEM hItemPrev = GetPrevSiblingItem(hItem);
	if (hItemPrev == NULL)
		return FALSE;

	HTREEITEM hItemPrevPrev = GetPrevSiblingItem(hItemPrev);
	if (hItemPrevPrev == NULL)
		hItemPrevPrev = TVI_FIRST;

	HTREEITEM hItemInserted = InsertItem(GetItemText(hItem),
		GetParentItem(hItem),
		hItemPrevPrev);
	SetItemData(hItemInserted, GetItemData(hItem));
	SelectItem(hItemInserted);

	HTREEITEM hChildItem = GetChildItem(hItem);
	while (hChildItem)
	{
		HTREEITEM hChildItemInserted = InsertItem(GetItemText(hChildItem),
			hItemInserted,
			TVI_LAST);

		SetItemData(hChildItemInserted, GetItemData(hChildItem));
		hChildItem = GetNextSiblingItem(hChildItem);
	}

	Expand(hItemInserted, TVE_EXPAND);
	DeleteItem(hItem);
	return TRUE;
}

BOOL CSortableTreeCtrl::MoveSelectedDown()
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem == NULL)
		return FALSE;

	HTREEITEM hItemNext = GetNextSiblingItem(hItem);
	if (hItemNext == NULL)
		return FALSE;

	HTREEITEM hItemInserted = InsertItem(GetItemText(hItem),
		GetParentItem(hItem),
		hItemNext);
	SetItemData(hItemInserted, GetItemData(hItem));
	SelectItem(hItemInserted);

	HTREEITEM hChildItem = GetChildItem(hItem);
	while (hChildItem)
	{
		HTREEITEM hChildItemInserted = InsertItem(GetItemText(hChildItem),
			hItemInserted,
			TVI_LAST);

		SetItemData(hChildItemInserted, GetItemData(hChildItem));
		hChildItem = GetNextSiblingItem(hChildItem);
	}

	Expand(hItemInserted, TVE_EXPAND);
	DeleteItem(hItem);
	return TRUE;
}