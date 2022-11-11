#ifndef _XMLVIEWERDLG_H_
#define _XMLVIEWERDLG_H_

#include "EsamiView.h"
#include "BrowserCtrl.h"

class CXmlViewerDlg : public CEndoxResizableDlg
{
	DECLARE_DYNAMIC(CXmlViewerDlg)

public:

	CXmlViewerDlg(CWnd* pParent, CString message, CString errorMessage, CStringList &warningList);
	virtual ~CXmlViewerDlg();

	enum { IDD = IDD_XML_VIEWER };

private:

	CString m_sFileName, m_sErrorMessage;
	CStringList m_warningList;
	CButtonLocalize m_ctrlBtnChiudi;
	CBrowserCtrl m_ctrlBrowser;

	CListCtrlLocalize m_ctrlWarningList;
	CEdit m_ctrlErrors;	

	CStaticLocalize m_ctrlStatic1, m_ctrlStatic2, m_ctrlStatic3, m_ctrlStatic4;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

};

#endif /* _XMLVIEWERDLG_H_ */