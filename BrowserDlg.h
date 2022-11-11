#ifndef _BROWSERDLG_H_
	#define _BROWSERDLG_H_

#include "BrowserCtrl.h"

class CBrowserDlg : public CResizableDialog
{
	DECLARE_DYNAMIC(CBrowserDlg)

public:

	CBrowserDlg(CString strURL, CWnd* pParentWnd = NULL);

	enum { IDD = IDD_BROWSER };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnSize(UINT nType, int cx, int cy);

private:

	static UINT Thread(LPVOID lpParam);

	CBrowserCtrl m_ctrlBrowser;
	CStatic m_ctrlBrowserCtrl;
	CString m_strURL;

};

#endif /* _BROWSERDLG_H_ */