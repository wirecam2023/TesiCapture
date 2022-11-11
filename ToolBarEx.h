#pragma once

#include "ToolbarChildDlg.h"

class CToolBarEx : public CToolBar
{
	DECLARE_DYNAMIC(CToolBarEx)

public:
	CToolBarEx();
	virtual ~CToolBarEx();

	void Attach(UINT id, CWnd* pParentWnd);
	void AttachEx(UINT id, CWnd* pParentWnd);

	BOOL LoadTCToolBar(UINT iBitmapNormalID, UINT iBitmapDisabledID);
	void DeleteButton(UINT id, BOOL bDeleteSeparatorAfter = FALSE);

	void AddChildToolbar(UINT iParentButtonID, 
			                CToolbarChildDlg::ToolbarChild_Orientation orientation,
			                UINT iToolbarChildID, 
							UINT iBitmapNormalID, 
							UINT iBitmapDisabledID);

	BOOL LoadToolBar(UINT iResourceName);
	BOOL LoadToolBar(LPCTSTR lpszResourceName);

protected:

	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual LRESULT OnUpdateCommandUI(WPARAM wParam, LPARAM lParam) { return 0; }
	virtual LRESULT OnToolbarPressButton(WPARAM wParam, LPARAM lParam) { return 0; }
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	afx_msg BOOL OnToolTipNotify(UINT nID, NMHDR* pNMHDR, LRESULT* pResult);
	LRESULT OnDestroyToolbarChild(WPARAM wParam, LPARAM lParam);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCommandUI();
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()

	COLORREF m_rgbColorMask;
	BOOL CreateChildToolbar(UINT nParentID);

private:

	BOOL SetTCToolBar(UINT uToolBarType, UINT uToolBar);
	BOOL CreateChildToolbar(CPoint point);
	void DestroyChildToolbar();

	CImageList m_ImageList;
	CImageList m_HotImageList;
	CImageList m_DisabledImageList;

	CToolbarChildDlg* m_pChildToolbarDlg;

	class CToolCmdUI : public CCmdUI
	{
	public:
		virtual void Enable(BOOL bOn);
		virtual void SetCheck(int nCheck);
		virtual void SetText(LPCTSTR lpszText);
	};

	struct tagChildToolbar
	{
		UINT iParentButtonID;
		CToolbarChildDlg::ToolbarChild_Orientation orientation;
		UINT iToolbarChildID;
		UINT iBitmapNormalID;
		UINT iBitmapDisabledID;
	};
	CList<tagChildToolbar> m_listChildToolbars;
};
