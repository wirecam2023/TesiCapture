#ifndef _STREAMINGLISTDLG_H_
	#define _STREAMINGLISTDLG_H_

#include "afxcmn.h"
#include "afxwin.h"

class CStreamingListDlg : public CDialog
{
	DECLARE_DYNAMIC(CStreamingListDlg)

public:

	CStreamingListDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CStreamingListDlg();

	enum { IDD = IDD_STREAMINGLIST_DLG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnCms();
	afx_msg void OnBnClickedBtnOpen();

	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);

private:

	void RiempiLista();
	void VlcManager(CString sSource);

	CButtonLocalize m_ctrlBtnCms;
	CButtonLocalize m_ctrlBtnOpen;
	CButtonLocalize m_ctrlBtnOK;
	CListCtrlLocalize m_ctrlList;

	CEsamiView* m_pEsamiView;
	
};

#endif /* _STREAMINGLISTDLG_H_ */