#ifndef _LIVELLIURGENZADLG_H_
#define _LIVELLIURGENZADLG_H_

#include "ExtListBox.h"

class CLivelliUrgenzaDlg : public CDialog
{

public:

	CLivelliUrgenzaDlg(CWnd* pParent);
	virtual ~CLivelliUrgenzaDlg();

	enum { IDD = IDD_LIVELLIURGENZA };

	long m_lId;
	CString m_sCodiceEsterno;
	long m_lLivelloUrgenzaEndox;
	CComboBoxLocalize m_ctrlCmbLivelloUrgenza;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnLivelloUrgenzaNew();
	afx_msg void OnLivelloUrgenzaEdt();
	afx_msg void OnLivelloUrgenzaDel();
	afx_msg void OnLivelloUrgenzaSave();
	afx_msg void OnLivelloUrgenzaUndo();

	afx_msg void OnLbnDblclkLista();
	afx_msg void OnSelchangeLista();

	//afx_msg void OnBnClickedButtonGenera();
	//afx_msg void OnEnChangeLogin();
	//afx_msg void OnEnKillfocusLogin();
	//afx_msg void OnEnSetfocusLogin();

	// LRESULT OnWMUser(WPARAM wParam, LPARAM lParam); // è na pazzia... //

private:

	BOOL CanBeInserted(long lContatore);
	void RiempiListaUrgenze();

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

	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonEdt;
	CButtonLocalize m_ctrlButtonDel;
	CButtonLocalize m_ctrlButtonSave;
	CButtonLocalize m_ctrlButtonUndo;
	CButtonLocalize m_ctrlButtonOK;

	CExtListBox m_ctrlLista;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;

};

#endif /* _LIVELLIURGENZADLG_H_ */