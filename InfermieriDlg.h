#ifndef _INFERMIERIDLG_H_
	#define _INFERMIERIDLG_H_

#include "ExtListBox.h"

class CEsamiView;

class CInfermieriDlg : public CDialog
{

public:

	CInfermieriDlg(CEsamiView* pEsamiView, BOOL bMenu);
	virtual ~CInfermieriDlg();

	enum { IDD = IDD_INFERMIERI };

	long m_lID;
	CString m_sTitolo;
	CString m_sCognome;
	CString m_sNome;
	CString m_sMatricola;
	CString m_sIndirizzo;
	CString m_sCitta;
	CString m_sProvincia;
	CString m_sTelefono;

	CExtListBox		m_ctrlLista;

	CEsamiView*		m_pEsamiView; 

	int				m_lSavedPosition;
	BOOL			m_bAddNew;
	BOOL			m_bModify;

	BOOL            m_bOrPressed;
	BOOL            m_bRicercaAttivata;

	CString         m_strRicerca;
	CString         m_strRicercaView;
	
	int             m_nItemSelected;
	int             m_nItemCount;

	void RiempiListaInfermieri();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	afx_msg void OnInfermieriDelete();
	afx_msg void OnInfermieriModify();
	afx_msg void OnInfermieriNew();
	afx_msg void OnInfermieriRefresh();
	afx_msg void OnInfermieriUpdate();
	afx_msg void OnLbnDblclkLista();
	afx_msg void OnSelchangeLista();
	afx_msg void OnBtnOr();
	DECLARE_MESSAGE_MAP()

private:

	BOOL CanBeInserted(long lContatore);
	void RiempiComboUsers();
	BOOL m_bMenu;

	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonMod;
	CButtonLocalize m_ctrlButtonDel;
	CButtonLocalize m_ctrlButtonUpd;
	CButtonLocalize m_ctrlButtonRefresh;
	CButtonLocalize m_ctrlButtonExit;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CStaticLocalize m_ctrlStatic4;
	CStaticLocalize m_ctrlStatic5;
	CStaticLocalize m_ctrlStatic6;
	CStaticLocalize m_ctrlStatic7;
	CStaticLocalize m_ctrlStatic8;

	CComboBox m_ctrlComboUser;
};

#endif /* _INFERMIERIDLG_H_ */