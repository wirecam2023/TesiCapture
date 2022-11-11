#ifndef _UODLG_H_
	#define _UODLG_H_

#include "ExtListBox.h"

class CUODlg : public CDialog
{

public:

	CUODlg(CWnd* pParent);
	virtual ~CUODlg();

	enum { IDD = IDD_UO };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnUONew();
	afx_msg void OnUOEdt();
	afx_msg void OnUODel();
	afx_msg void OnUOSave();
	afx_msg void OnUOUndo();

	afx_msg void OnLbnDblclkLista();
	afx_msg void OnSelchangeLista();	

	//afx_msg void OnBnClickedButtonGenera();
	//afx_msg void OnEnChangeLogin();
	//afx_msg void OnEnKillfocusLogin();
	//afx_msg void OnEnSetfocusLogin();

	// LRESULT OnWMUser(WPARAM wParam, LPARAM lParam); // è na pazzia... //

private:

	long m_lID;
	CString m_sDescrizione;
	CString m_sCodiceEsterno;

	//

	BOOL CanBeInserted(long lContatore);
	void RiempiListaUO();

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

	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonEdt;
	CButtonLocalize m_ctrlButtonDel;
	CButtonLocalize m_ctrlButtonSave;
	CButtonLocalize m_ctrlButtonUndo;
	CButtonLocalize m_ctrlButtonOK;

	CExtListBox m_ctrlLista;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;	
	CStaticLocalize m_ctrlStatic3;

};

#endif /* _UODLG_H_ */