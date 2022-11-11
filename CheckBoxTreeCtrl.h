#pragma once

class CCheckBoxTreeCtrl : public CTreeCtrl
{

public:

	CCheckBoxTreeCtrl(void);
	~CCheckBoxTreeCtrl(void);

	BOOL GetCheckEnabled(_In_ HTREEITEM hItem) const;
	BOOL SetCheckEnabled(_In_ HTREEITEM hItem, _In_ BOOL bEnabled);

	BOOL GetCheck(_In_ HTREEITEM hItem) const;
	BOOL SetCheck(_In_ HTREEITEM hItem, _In_ BOOL fCheck);

	void SetNotificationCheckMessage(UINT iMessage);
	UINT GetNotificationCheckMessage();

	HTREEITEM GetItemFromData(DWORD_PTR dwData, HTREEITEM hItemParent = NULL);

	UINT GetCheckedItemCount(HTREEITEM hItemParent = NULL);

protected:

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()

	virtual void PreSubclassWindow();

private:

	CImageList* GetImageList(_In_ int nImageList) const;
	CImageList* SetImageList(_In_ CImageList* pImageList, _In_ int nImageList);

	BOOL GetItemImage(_In_ HTREEITEM hItem, _Out_ int& nImage, _Out_ int& nSelectedImage) const;
	BOOL SetItemImage(_In_ HTREEITEM hItem, _In_ int nImage, _In_ int nSelectedImage);

	UINT GetItemState(_In_ HTREEITEM hItem, _In_ UINT nStateMask) const;
	BOOL SetItemState(_In_ HTREEITEM hItem, _In_ UINT nState, _In_ UINT nStateMask);

	CImageList m_imageList;
	UINT m_iMessage;

};
