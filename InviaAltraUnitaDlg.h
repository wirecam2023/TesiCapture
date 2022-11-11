#pragma once
#ifndef _INVIAALTRAUNITADLG_H_
#define _INVIAALTRAUNITADLG_H_

#include "ExtListBox.h"
#include "MyListBox.h"

class CInviaAltraUnitaDlg : public CDialog
{
	DECLARE_DYNAMIC(CInviaAltraUnitaDlg)

public:
	CInviaAltraUnitaDlg(CEsamiView* pEsamiView);   // standard constructor
	virtual ~CInviaAltraUnitaDlg();

	enum { IDD = IDD_INVIAALTRAUNITA };

	CString m_strRicerca;

	BOOL m_bCleanContent;

	long GetSelectedUnita();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnUnitaClean();
	afx_msg void OnBnClickedOK();
	afx_msg void OnBnClickedCancel();
	void SetUnitaSelected();

	afx_msg void OnDestroy();
	afx_msg void OnLbnDblclkLista();
	afx_msg void OnMediciRefresh();
	afx_msg void OnSelchangeLista();

private:
	void RiempiListaUnita(CString sFilter);
	//

	long m_lID;
	long m_lSelectedUnita;
	CString m_sDescrizione;

	CExtListBox m_ctrlLista;

	CEsamiView* m_pEsamiView;

	int m_lSavedPosition;

	int m_nItemPressed;
	int m_nItemCount;

	CButtonLocalize m_ctrlButtonClean;
	CButtonLocalize m_ctrlButtonEsc;
	CButtonLocalize m_ctrlButtonOK;

	BOOL m_bMenu;

	CString m_sUnitaSearch;

public:
	afx_msg void OnEnChangeEditSearchUnita();
	afx_msg void OnBnClickedCleanSearchUnita();
};

#endif /* _INVIAALTRAUNITADLG_H_ */