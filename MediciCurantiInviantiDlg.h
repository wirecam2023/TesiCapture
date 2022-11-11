#ifndef _MEDICICURANTIINVIANTIDLG_H_
	#define _MEDICICURANTIINVIANTIDLG_H_

#include "ExtListBox.h"

class CEsamiView;
class CMediciCurantiInviantiSet;

class CMediciCurantiInviantiDlg : public CDialog
{

public:

	CMediciCurantiInviantiDlg(CWnd* pParent, long lCurantiInvianti, BOOL bMenu);
	virtual ~CMediciCurantiInviantiDlg();

	enum { IDD = IDD_MEDICI };

	long m_lContatore;
	CString m_sCognome;
	CString m_sNome;
	CString m_sTitolo;
	CString m_sVia;
	CString m_sCitta;
	CString m_sProvincia;
	CString m_sTelefono;
	CString m_sEmail;
	CString m_sLogin;
	CString m_sCodiceFiscale;
	CString m_sCodiceIntegrazione;
	BOOL m_bSpeciale;

	CString m_sRicerca;
	CString m_sRicercaView;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnMediciNew();
	afx_msg void OnMediciEdt();
	afx_msg void OnMediciDel();
	afx_msg void OnMediciSave();
	afx_msg void OnMediciUndo();

	afx_msg void OnLbnDblclkLista();
	afx_msg void OnSelchangeLista();
	afx_msg void OnBtnOr();
	afx_msg void OnBnClickedBtnCerca();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnBnClickedButtonGenera();
	afx_msg void OnEnChangeLogin();
	afx_msg void OnEnKillfocusLogin();
	afx_msg void OnEnSetfocusLogin();

private:

	BOOL CanBeInserted(long lContatore);
	void RiempiListaMedici(CString sCampoRicerca = "");

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
	CButtonLocalize m_ctrlChkSpeciale;

	CExtListBox m_ctrlLista;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CStaticLocalize m_ctrlStatic4;
	CStaticLocalize m_ctrlStatic5;
	CStaticLocalize m_ctrlStatic6;
	CStaticLocalize m_ctrlStatic7;
	CStaticLocalize m_ctrlStatic8;
	CStaticLocalize m_ctrlStatic9;
	CStaticLocalize m_ctrlStatic10;
	CStaticLocalize m_ctrlStatic11;
	CStaticLocalize m_ctrlStaticRic;	
};

#endif /* _MEDICICURANTIINVIANTIDLG_H_ */