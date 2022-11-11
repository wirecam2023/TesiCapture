#ifndef _MAINFRAME_H_
	#define _MAINFRAME_H_

class CMainFrame : public CFrameWnd
{

protected:

	CMainFrame();
	virtual ~CMainFrame();

	DECLARE_DYNCREATE(CMainFrame)

public:

	static int s_nDimX;
	static int s_nDimY;

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	HACCEL GetAccelTable() { return m_hAccelTable; }

protected: 

    CStatusBar m_wndStatusBar;
    CToolBar m_wndToolBar;

protected:

	afx_msg LRESULT OnHelp(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnXcapMsgNuovoMonitoraggio(WPARAM, LPARAM);
	afx_msg LRESULT OnXcapMsgNuovaProvetta(WPARAM, LPARAM);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg BOOL OnHelpInfo(HELPINFO* lpHelpInfo);
	// virtual void HtmlHelp(DWORD_PTR dwData, UINT nCmd = 0x000F); // Sandro 10/02/2015 VS2013 //
    virtual void OnClose();

	DECLARE_MENUXP()
	DECLARE_MESSAGE_MAP()

};

#endif /* _MAINFRAME_H_ */