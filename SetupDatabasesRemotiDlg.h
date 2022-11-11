#ifndef _SETUPDATABASESREMOTIDLG_H_
	#define _SETUPDATABASESREMOTIDLG_H_
#include "afxcmn.h"
#include "afxwin.h"

class CSetupDatabasesRemotiDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetupDatabasesRemotiDlg)

public:

	CSetupDatabasesRemotiDlg(CWnd* pParent);
	virtual ~CSetupDatabasesRemotiDlg();

	enum { IDD = IDD_SETUP_DATABASES_REMOTI };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnChiudi();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnEdt();
	afx_msg void OnBnClickedBtnNew();

	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);

private:

	void RiempiLista(long lIDToSel);

	//

	CButtonLocalize m_ctrlBtnChiudi;
	CButtonLocalize m_ctrlBtnDel;
	CButtonLocalize m_ctrlBtnEdt;
	CButtonLocalize m_ctrlBtnNew;

	CListCtrl m_ctrlList;

	//

	BOOL m_bIsOracle;

};

#endif /* _SETUPDATABASESREMOTIDLG_H_ */