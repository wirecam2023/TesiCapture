#ifndef _OPERATORIDLG_H_
	#define _OPERATORIDLG_H_

#include "ExtListBox.h"
#include "MyListBox.h"

class CEsamiView;
class CMediciSet;

// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
#define _NONE_MODE_     0
#define _RICERCA_MODE_  1
#define _EDIT_MODE_     2
#define _MODIFICA_MODE_ 3
#define _NEW_MODE_      4 
#define _RICARICA_MODE_ 5
#define _UPDATE_MODE_   6
#define _SELECTED_MODE_ 7
#define _ELIMINA_MODE_  8
#define _NOT_SELECTED_MODE_ 9
// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1

class COperatoriDlg : public CDialog
{

public:

	COperatoriDlg(CEsamiView* pEsamiView, BOOL bMenu, long p_lLastValue = -1); // Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
	
	virtual ~COperatoriDlg();	

	enum { IDD = IDD_OPERATORI };

	CString m_strRicerca;
	CString m_strRicercaView;

	CString m_sTitolo;
	CString m_sCognome;
	CString m_sNome;
	CString m_sVia;
	CString m_sCitta;
	CString m_sProvincia;
	CString m_sTelefono;
	BOOL m_bCleanContent;// Luiz - 19/06/2019 - P3 - Melhoria do processo de busca
	long m_lLastMedico1; // Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
	int m_iStatusMode;   // Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	//afx_msg void OnBnClickedChkLibero();
	afx_msg void OnBtnOr();
	afx_msg void OnMediciClean(); // Luiz - 19/06/2019 - P3 - Melhoria do processo de busca

	// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
	afx_msg void OnBnClickedOK();
	afx_msg void OnBnClickedCancel();
	void SetMedicoSelected();
	void SetLastMedico();
	void SetButtonsShowOrHide(const int p_iContext);
	BOOLEAN m_bAlowListUpdate = TRUE;
	// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	afx_msg void OnLbnDblclkLista();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMediciDelete();
	afx_msg void OnMediciModify();
	afx_msg void OnMediciNew();
	afx_msg void OnMediciRefresh();
	afx_msg void OnMediciUpdate();
	afx_msg void OnPaint();
	afx_msg void OnSelchangeLista();

private:

	BOOL CanBeInserted(long lContatore);

	void RiempiComboUsers();
	void RiempiListaMedici(CString sFilter);
	void RiempiListaSedi();

	void SelezionaSedi(long lContatoreMedico);
	//

	long m_lID;
	CString m_sCodice;
	int m_iLibero;
	CString m_sCodiceFiscale;
	CString m_sFirma0;
	CString m_sFirma1;
	CString m_sFirma2;
	CString m_sFirma3;
	CString m_sFirma4;
	CString m_sFirma5;
	CString m_sFirma6;
	CString m_sFirma7;
	CString m_sFirma8;
	CString	m_sFirma9;

	//

	CButtonLocalize m_ctrlChkLibero;

	CComboBox m_ctrlComboUser;

	CExtListBox m_ctrlLista;

	CEsamiView* m_pEsamiView;

	int m_lSavedPosition;
	BOOL m_bAddNew;
	BOOL m_bModify;

	BOOL m_bOrPressed;
	BOOL m_bRicercaAttivata;


	int m_nItemPressed;
	int m_nItemCount;


	//

	CStaticLocalize m_ctrlStatic00;
	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;
	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CStaticLocalize m_ctrlStatic4;
	CStaticLocalize m_ctrlStatic5;
	CStaticLocalize m_ctrlStatic6;
	CStaticLocalize m_ctrlStatic7;
	CStaticLocalize m_ctrlStatic8;
	CStaticLocalize m_ctrlStatic10;
	CStaticLocalize m_ctrlStatic11;
	CStaticLocalize m_ctrlStaticRic;

	CButtonLocalize m_ctrlButtonNew;    // BOTÃO NUOVO (INCLUSÃO DE MÉDICO)
	CButtonLocalize m_ctrlButtonEdt;	// BOTÃO MODIFICA (ALTERAÇÃO DE MÉDICO)
	CButtonLocalize m_ctrlButtonDel;	// BOTÃO ELIMINA (DELETA REGISTRO DE MÉDICO)
	CButtonLocalize m_ctrlButtonSave;	// BOTÃO SALVA (INCLUSÃO / ALTERAÇÃO DE MÉDICO)
	CButtonLocalize m_ctrlButtonUndo;	// BOTÃO ANULA (UNDO DA AÇÃO MODIFICA/NEW)
	CButtonLocalize m_ctrlButtonClean;  // BOTÃO RESET (LIMPA)        // Luiz - 19/06/2019 - P3 - Melhoria do processo de busca
	CButtonLocalize m_ctrlButtonEsc;    // BOTÃO ESCI (CANCEL)      // Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
	CButtonLocalize m_ctrlButtonOK;     // BOTÃO OK (SALVA/CONFIRMA)  // Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1

	CMyListBox m_ctrlListSedi;

	BOOL m_bMenu;

	BYTE* m_pBitmapBuffer;
	DWORD m_dwBitmapBufferLength;
	
	//

	CString m_sMediciSearch;

public:
	afx_msg void OnEnChangeEditSearchmedici();
	CString GetCurrentUtentiMedici();
	long GetIDUtenteEndoxFromMediciID(long lID);
	//afx_msg void OnBnClickedMediciNuovo2();
	afx_msg void OnBnClickedCleanSearchmedici();	// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
};

#endif /* _OPERATORIDLG_H_ */