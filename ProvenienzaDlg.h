#ifndef _PROVENIENZADLG_H_
	#define _PROVENIENZADLG_H_

#include "ExtListBox.h"

class CProvenienzaDlg : public CDialog
{

public:

	CProvenienzaDlg(CWnd* pParent, BOOL bSearching=FALSE);
	virtual ~CProvenienzaDlg();

	enum { IDD = IDD_PROVENIENZA };

	long m_lId;
	CString m_sDescrizione;
	CString m_sCodiceEsterno;
	long m_lIdProvenienzaEndox;
	CComboBox m_ctrlCmbProvenienza;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnProvenienzaNew();
	afx_msg void OnProvenienzaEdt();
	afx_msg void OnProvenienzaDel();
	afx_msg void OnProvenienzaSave();
	afx_msg void OnProvenienzaUndo();

	afx_msg void OnLbnDblclkLista();
	afx_msg void OnSelchangeLista();	

	//afx_msg void OnBnClickedButtonGenera();
	//afx_msg void OnEnChangeLogin();
	//afx_msg void OnEnKillfocusLogin();
	//afx_msg void OnEnSetfocusLogin();

	// LRESULT OnWMUser(WPARAM wParam, LPARAM lParam); // è na pazzia... //

private:

	BOOL CanBeInserted(long lContatore);
	void RiempiListaProvenienza();

	//

	BOOL m_bAddNew;
	BOOL m_bModify;
	BOOL m_bOrPressed;
	BOOL m_bRicercaAttivata;
	BOOL m_bUserFocus;
	BOOL m_bValidUser;

	int m_iItemCount;
	int m_iItemPressed;
	int m_iSavedPosition;


	//

	long m_lCurantiInvianti;
	BOOL m_bMenu;

	//

	CEdit m_ctrlDescrizione;
	CEdit m_ctrlCodice;

	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonEdt;
	CButtonLocalize m_ctrlButtonDel;
	CButtonLocalize m_ctrlButtonSave;
	CButtonLocalize m_ctrlButtonUndo;
	CButtonLocalize m_ctrlButtonOK;	

	CListCtrl m_ctrlLista;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;	
	CStaticLocalize m_ctrlStatic3;
	CStaticLocalize m_ctrlStatic4;

	BOOL m_bSearching;

public:	

	CList<long> m_idProvenienzaList;
	CStringList m_descProvenienzaList;

	afx_msg void OnLvnItemchangedLista(NMHDR *pNMHDR, LRESULT *pResult);
};

#endif /* _PROVENIENZADLG_H_ */