#ifndef _FRASINEWUSEDLG_H_
	#define _FRASINEWUSEDLG_H_

#include "SediTreeCtrl.h"
#include "afxwin.h"

class CFrasiNewUseDlg : public CDialog
{
	DECLARE_DYNAMIC(CFrasiNewUseDlg)

public:

	CFrasiNewUseDlg(CWnd* pParent, CString sTitolo, long lPrePost, CString strValue);
	virtual ~CFrasiNewUseDlg();

	enum { IDD = IDD_FRASINEW_USE };

	CString GetValue();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnInserisci();
	afx_msg void OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);

private:

	void RiempiListaFigli(HTREEITEM hPadre, long lPadre);
	void RiempiListaFrasi();

	CSediTreeCtrl m_ctrlTree;

	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnInserisci;
	CButtonLocalize m_ctrlBtnOk;

	CEdit m_ctrlText;

	CString m_sTitolo;
	long m_lPrePost;
	CString m_strValue;
};

#endif /* _FRASINEWUSEDLG_H_ */