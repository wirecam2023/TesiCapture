#ifndef _CAMPIOBBLIGATORIDLG_H_
	#define _CAMPIOBBLIGATORIDLG_H_
#include "afxcmn.h"

class CCampiObbligatoriDlg : public CDialog
{
	DECLARE_DYNAMIC(CCampiObbligatoriDlg)

public:

	CCampiObbligatoriDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CCampiObbligatoriDlg();

	enum { IDD = IDD_CAMPI_OBBLIGATORI };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnNuovo();
	afx_msg void OnBnClickedBtnModifica();
	afx_msg void OnBnClickedBtnCancella();

	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);

private:

	void RiempiLista();
	static int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

	CEsamiView* m_pEsamiView;

	CButtonLocalize m_ctrlBtnNew;
	CButtonLocalize m_ctrlBtnEdt;
	CButtonLocalize m_ctrlBtnDel;
	CButtonLocalize m_ctrlBtnExit;
	CListCtrlLocalize m_ctrlList;

};

#endif /* _CAMPIOBBLIGATORIDLG_H_ */