#include "stdafx.h"
#include "Endox.h"
#include "CheckBoxTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CCheckBoxTreeCtrl::CCheckBoxTreeCtrl(void)
{
	m_iMessage = 0;
}

CCheckBoxTreeCtrl::~CCheckBoxTreeCtrl(void)
{
}

BEGIN_MESSAGE_MAP(CCheckBoxTreeCtrl, CTreeCtrl)

	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()

END_MESSAGE_MAP()

void CCheckBoxTreeCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
}

void CCheckBoxTreeCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	UINT uFlags = 0;
	HTREEITEM hItem = HitTest(point, &uFlags);

	if (hItem)
	{
		if (uFlags & TVHT_ONITEMICON)
		{
			int nImage, nSelectedImage;
			if (GetItemImage(hItem, nImage, nSelectedImage))
			{
				switch (nImage)
				{
				case 0:
					SetItemImage(hItem, 1, 1);
					break;

				case 1:
					SetItemImage(hItem, 0, 0);
					break;
				}
			}
		}
		else if (uFlags & TVHT_ONITEMLABEL)
		{
			CTreeCtrl::OnLButtonDown(nFlags, point);

			if (theApp.m_bCheckListClickElementoSeleziona && GetCheckEnabled(hItem))
				SetCheck(hItem, !GetCheck(hItem));
		}
		else
			CTreeCtrl::OnLButtonDown(nFlags, point);

		SelectItem(hItem);
	}
	else
		CTreeCtrl::OnLButtonDown(nFlags, point);
}

void CCheckBoxTreeCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CCheckBoxTreeCtrl::PreSubclassWindow()
{
	CTreeCtrl::PreSubclassWindow();

	m_imageList.Create(16, 16, ILC_COLOR32, 7, 1);

	HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON_TREE_UNCHECK);
	m_imageList.Add(hIcon);
	DeleteObject(hIcon);

	hIcon = AfxGetApp()->LoadIcon(IDI_ICON_TREE_CHECK);
	m_imageList.Add(hIcon);
	DeleteObject(hIcon);

	hIcon = AfxGetApp()->LoadIcon(IDI_ICON_TREE_NOCHECK);
	m_imageList.Add(hIcon);
	DeleteObject(hIcon);

	SetImageList(&m_imageList, TVSIL_NORMAL);
	SetImageList(&m_imageList, TVSIL_STATE);
}

BOOL CCheckBoxTreeCtrl::GetCheck(_In_ HTREEITEM hItem) const
{
	int nImage, nSelectedImage;
	if (!GetItemImage(hItem, nImage, nSelectedImage))
		return FALSE;

	return (nImage == 1);
}

BOOL CCheckBoxTreeCtrl::SetCheck(_In_ HTREEITEM hItem, _In_ BOOL fCheck)
{
	return SetItemImage(hItem, fCheck ? 1 : 0, fCheck ? 1 : 0);
}

BOOL CCheckBoxTreeCtrl::GetCheckEnabled(_In_ HTREEITEM hItem) const
{
	int nImage, nSelectedImage;
	if (!GetItemImage(hItem, nImage, nSelectedImage))
		return FALSE;

	return (nImage != 2);
}

BOOL CCheckBoxTreeCtrl::SetCheckEnabled(_In_ HTREEITEM hItem, _In_ BOOL bEnabled)
{
	if (GetCheckEnabled(hItem) == bEnabled)
		return TRUE;

	return SetItemImage(hItem, bEnabled ? 0 : 2, bEnabled ? 0 : 2);
}

HTREEITEM CCheckBoxTreeCtrl::GetItemFromData(DWORD_PTR dwData, HTREEITEM hItemParent)
{
	HTREEITEM hItem = (hItemParent == NULL) ? GetRootItem() : hItemParent;
	HTREEITEM hItemReturn = NULL;

	while (hItem)
	{
		if (GetItemData(hItem) == dwData)
		{
			hItemReturn = hItem;
			break;
		}

		if (HTREEITEM hItemChild = GetChildItem(hItem))
		{
			HTREEITEM hItemNew = GetItemFromData(dwData, hItemChild);
			if (hItemNew != NULL)
			{
				hItemReturn = hItemNew;
				break;
			}
		}

		if (hItemReturn != NULL)
			break;

		hItem = GetNextSiblingItem(hItem);
	}

	return hItemReturn;
}

UINT CCheckBoxTreeCtrl::GetCheckedItemCount(HTREEITEM hItemParent)
{
	HTREEITEM hItem = (hItemParent == NULL) ? GetRootItem() : hItemParent;
	UINT iReturn = 0;

	while (hItem)
	{
		if (GetCheck(hItem))
			iReturn++;

		if (HTREEITEM hItemChild = GetChildItem(hItem))
			iReturn += GetCheckedItemCount(hItemChild);

		hItem = GetNextSiblingItem(hItem);
	}

	return iReturn;
}

CImageList* CCheckBoxTreeCtrl::GetImageList(_In_ int nImageList) const
{
	return CTreeCtrl::GetImageList(nImageList);
}

CImageList* CCheckBoxTreeCtrl::SetImageList(_In_ CImageList* pImageList, _In_ int nImageList)
{
	return CTreeCtrl::SetImageList(pImageList, nImageList);
}

BOOL CCheckBoxTreeCtrl::GetItemImage(_In_ HTREEITEM hItem, _Out_ int& nImage, _Out_ int& nSelectedImage) const
{
	return CTreeCtrl::GetItemImage(hItem, nImage, nSelectedImage);
}

BOOL CCheckBoxTreeCtrl::SetItemImage(_In_ HTREEITEM hItem, _In_ int nImage, _In_ int nSelectedImage)
{
	BOOL bReturn = FALSE;

	int nImagePrec, nSelectedImagePrec;
	GetItemImage(hItem, nImagePrec, nSelectedImagePrec);

	bReturn = CTreeCtrl::SetItemImage(hItem, nImage, nSelectedImage);
	if (bReturn && (nImagePrec != nImage) && (m_iMessage > 0) && (nImage != 2))
		GetParent()->SendMessage(m_iMessage, (WPARAM)hItem, (LPARAM)0);

	return bReturn;
}

UINT CCheckBoxTreeCtrl::GetItemState(_In_ HTREEITEM hItem, _In_ UINT nStateMask) const
{
	return CTreeCtrl::GetItemState(hItem, nStateMask);
}

BOOL CCheckBoxTreeCtrl::SetItemState(_In_ HTREEITEM hItem, _In_ UINT nState, _In_ UINT nStateMask)
{
	return CTreeCtrl::SetItemState(hItem, nState, nStateMask);
}

void CCheckBoxTreeCtrl::SetNotificationCheckMessage(UINT iMessage)
{
	m_iMessage = iMessage;
}

UINT CCheckBoxTreeCtrl::GetNotificationCheckMessage()
{
	return m_iMessage;
}
