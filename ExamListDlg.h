#pragma once

#include "EndoxResizableDlg.h"
#include "EsamiSet.h"
#include "VistaEsamiPerWLSet.h"

class CExamListDlg : public CEndoxResizableDlg
{
public:
	CExamListDlg(CWnd* pParent, CVistaEsamiPerWLSet* esamiSet, long* contatore);
	~CExamListDlg();

	enum { IDD = IDD_EXAMLIST};

	int m_iOperation;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()
	
	void RiempiLista();
	
	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlButtonAnnulla;
	CListCtrl m_ctrlList;

	CEsamiView*	m_pEsamiView;
	CVistaEsamiPerWLSet*	m_pEsamiSet;
	long *m_pContatore;

public:
	afx_msg void OnLvnItemchangedExamList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedNuovo();
	afx_msg void OnNMDblclkExamList(NMHDR *pNMHDR, LRESULT *pResult);
};