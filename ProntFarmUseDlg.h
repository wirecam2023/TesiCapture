#ifndef _PRONTFARMUSEDLG_H_
	#define _PRONTFARMUSEDLG_H_

#include "TXTextControl23.h"

class CEsamiView;

class CProntFarmUseDlg : public CDialog
{
	DECLARE_DYNAMIC(CProntFarmUseDlg)

public:

	CProntFarmUseDlg(CWnd* pParent, CEsamiView* pEsamiView, BOOL bSingleSelection);

	enum { IDD = IDD_PRONTFARMUSE };

	CString GetFarmaci();
	void SetFarmaci(CString strFarmaci);

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnAggiungi();
	afx_msg void OnBnClickedBtnAzzera();
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLbnSelchangeList00();
	afx_msg void OnLvnItemchangedList02(NMHDR *pNMHDR, LRESULT *pResult);

private:

	CListBox m_ctrlList00;
	CListCtrl m_ctrlList02;

	CString m_strFarmaci;

	CButtonLocalize m_ctrlButtonCancel;
	CButtonLocalize m_ctrlButtonDelsel;
	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlBtnAggiungi;
	CButtonLocalize m_ctrlBtnAzzera;
	CButtonLocalize m_ctrlBtnReset;

	CStaticLocalize m_ctrlStatic00;

	CTXTextControl23Ex m_ctrlTextControl;

	BOOL m_bSingleSelection;

	CEsamiView* m_pEsamiView;

public:
	afx_msg void OnEnChangeEditRicerca();
};

#endif /* _PRONTFARMUSEDLG_H_ */