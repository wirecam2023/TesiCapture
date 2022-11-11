#ifndef _THUMBCTRL_H_
	#define _THUMBCTRL_H_

#include "DLL_Imaging\h\imglist.h"

typedef CList<int, int&> CThumbIDList;

class CThumbCtrl : public CListCtrl
{
public:

	CThumbCtrl();
	
	void CalcImageSpacing();
	BOOL DeleteItem(int nItem);
	CString GetDescription(int nIndex);
	CThumbIDList* GetSelectedThumb() { return &m_listSelected; };
	void SetMessageDest(CWnd* pParentWnd, CEsamiView* pEsamiView);
	void SetThumbs(CImgList* pList);
	void SelectAll();
	void DeselectAll();

protected:

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

private:

	void RefreshItemBitmap(long lItem);
	
	CThumbIDList m_listSelected;
	CImgList* m_pImgList;
	CImageList m_tctrlImageList;

	CWnd* m_pParentWnd;
	CEsamiView* m_pEsamiView;
};

#endif /* _THUMBCTRL_H_ */