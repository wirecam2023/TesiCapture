#pragma once

#include "EndoxResizableDlg.h"
#include "ListWorklistCtrl.h"
#include "MaskEdit.h"
#include "QueryUtility.h"
#include "TXTextControl23.h"

class CCupWorkListManager;
class CEsamiView;

class CListaPrenotazioniCupDlg : public CEndoxResizableDlg, public CQueryUtility
{

public:

	CListaPrenotazioniCupDlg(CWnd* pParent, CEsamiView* pEsamiView, long lIDExtOrdiniAutoImport, CString sFicha = "");
	~CListaPrenotazioniCupDlg();

	enum { IDD = IDD_LISTA_PRENOTAZIONI_CUP };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnAggiorna();
	afx_msg void OnBnClickedImportALL();
	afx_msg void OnCbnSelchangeComboStato();
	afx_msg void OnCbnSelchangeComboSede();
	afx_msg void OnCbnSelchangeComboSala();
	afx_msg void OnCbnSelchangeComboProvenienza();
	afx_msg void OnCbnSelchangeComboUnidade();
	afx_msg void OnCbnSelchangeComboRegional();
	afx_msg void OnCbnSelchangeComboMarca();
	afx_msg void OnDblClkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMRClickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnDettagli();
	afx_msg void OnVediEsame();
	afx_msg void OnAnnullaIP();
	afx_msg void OnNonPresentato();
	afx_msg void OnPresentato();
	afx_msg void OnStart();
	afx_msg void OnBnClickedCambiaUO();
	afx_msg void OnBnClickedChkFilterData();
	afx_msg void OnBnClickedStampa();
	afx_msg void OnBnClickedPrintList();
	afx_msg void OnCbnSelchangeComboData();

private:

	// Marvel Carvalho | BUG 3759 - TesiCapture Melhoria Filtro Worklist
	BOOL RiempiLista(CString sCodiceRicovero, CString sNumeroOrdine, CString sCodicePaziente, CString sCognome, CString sNome);
	LRESULT OnGestioneCursore(WPARAM wparam, LPARAM lparam);
	void RiempiComboSedi();
	void RiempiComboSale();
	void EnableFields(BOOL bEnable);
	void VediDettagliRichiestaSelezionata();
	BOOL StartEsameSelezionato();
	void GoToEsameSelezionato();
	void AnnullaIPSelezionato();
	BOOL IsEsameAnnullabile();
	void SetNonPresentato();
	void AnnullaNonPresentato();
	
	// Marvel Carvalho | BUG 3759 - TesiCapture Melhoria Filtro Worklist
	void ThisFilterFieldsSave();
	void ThisFilterFieldsRestore();
	BOOL UpdateFiltering();
	void ConfirmDoingTheExame();
	void CheckComboPrestazioni(POSITION pos); //Julio - BUG 3365 - MAMOGUS
	void CheckFoglioRiferimento(POSITION pos); //Gabriel BUG 6225 - Lista DO
	
	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlButtonRefresh;
	CButtonLocalize m_ctrlBtnCambiaUO;
	CButtonLocalize m_ctrlButtonStampa;
	CButtonLocalize m_ctrlButtonPrintList;
	CButtonLocalize m_ctrlChkFilterData;
	CComboBox m_ctrlComboStato;
	CComboBox m_ctrlComboSede;
	CComboBox m_ctrlComboSala;
	CComboBox m_ctrlComboProvenienza;
	CComboBox m_ctrlComboData;
	CComboBox m_ctrlComboUnidade;
	CComboBox m_ctrlComboRegional;
	CComboBox m_ctrlComboMarca;
	CListWorklistCtrl m_ctrlList;
	CMaskEdit m_ctrlDataFine;
	CMaskEdit m_ctrlDataIniz;
	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CStaticLocalize m_ctrlStatic4;
	CStaticLocalize m_ctrlStatic5;
	CStaticLocalize m_ctrlStatic6;
	CStaticLocalize m_ctrlStatic7;
	CStaticLocalize m_ctrlStatic8;
	CStaticLocalize m_ctrlStatic9;
	CStaticLocalize m_ctrlStatic097;
	CStaticLocalize m_ctrlStatic098;
	CStaticLocalize m_ctrlStatic099;
	CStaticLocalize m_ctrlStaticStato;
	CStaticLocalize m_ctrlStaticProvenienza;
	CStaticLocalize m_ctrlStaticSede;
	CStaticLocalize m_ctrlStaticSala;

	CTXTextControl23Ex m_ctrlTextControlHide;

	//

	CEsamiView*	m_pEsamiView;
	CCupWorkListManager* m_pWorkListManager;

	CFont m_fontWorklist;

	long m_lNumeroUOUtente;
	long m_lIDExtOrdiniAutoImport;

	BOOL m_bInitializing;

	BOOL m_bFieldsEnabled;

	//Julio 22/01/2018 Abrir direto em uma ficha especifica
	CString m_sFichaPreviamenteSelecionada;

	BOOL m_bIsExiting; // Julio (FIX) BUG 3759 - TesiCapture Melhoria Filtro Worklist

};