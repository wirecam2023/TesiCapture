#ifndef _SETUPUNITATCPDLG_H_
#define _SETUPUNITATCPDLG_H_
#include "afxcmn.h"
#include "afxwin.h"

class CSetupUnitaTCPDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetupUnitaTCPDlg)

public:

	CSetupUnitaTCPDlg(CWnd* pParent);
	virtual ~CSetupUnitaTCPDlg();

	enum { IDD = IDD_SETUP_UNITA_TCP };

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

#endif /* _SETUPUNITATCPDLG_H_ */