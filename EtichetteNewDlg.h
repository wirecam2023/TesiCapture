#pragma once

#include "MyResizableDialog.h"

class CEtichetteNewDlg : public CResizableDialog
{

	DECLARE_DYNAMIC(CEtichetteNewDlg)

#define _NUMERO_TAB_ET 16

public:
	CEtichetteNewDlg(CWnd* pParent = NULL);
	~CEtichetteNewDlg();

	enum { IDD = IDD_ETICHETTE_NEW };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnDestroy();
	//virtual void OnOK();

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnTcnSelchangingTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);

private:
	void LoadTab(int index);

	CMyResizableDialog*	m_pForms[_NUMERO_TAB_ET];
	CTabCtrlLocalize	m_ctrlTab;
	long				m_lTab;
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};

