#pragma once

#define WM_DESTROY_TOOLBAR_CHILD         WM_USER + 0x100

class CToolBarChild;

class CToolbarChildDlg : public CDialog
{
public:
	enum ToolbarChild_Orientation
	{
		left,
		top,
		bottom,
		right
	};

	CToolbarChildDlg(ToolbarChild_Orientation orientation, 
			            UINT iToolbarID, 
						UINT iBitmapNormalID, 
						UINT iBitmapDisabledID, 
						CWnd* pParentWnd);
	~CToolbarChildDlg(void);

	BOOL Create();

	VOID ViewWithTransiction(UINT percTransparency);
	VOID ResizeDlg(POINT* pPoint);

	BOOL m_bToolbarDestroying;

private:
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	VOID StartTransitionEffect();
	VOID SetTransparency(UINT percentage);

	DLGTEMPLATE m_DialogTemplate;
	CString m_strCaption;
	WORD m_wFontSize;

	UINT m_iToolbarID;
	UINT m_iBitmapNormalID;
	UINT m_iBitmapDisabledID;

	ToolbarChild_Orientation m_orientation;
	CToolBarChild* m_pToolbar;
};