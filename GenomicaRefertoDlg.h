#pragma once

#include "TXTextControl23.h"
#include "TXButtonBar23.h"
#include "EditDynFormToolbar.h"
#include "GenomicaRicercaVarianteForm.h"

class CGenomicaRefertoDlg : public CDialog
{
	DECLARE_DYNAMIC(CGenomicaRefertoDlg)

public:
	CGenomicaRefertoDlg(CWnd* pParent, CEsamiView* m_pEsamiView);
	virtual ~CGenomicaRefertoDlg();

	enum { IDD = IDD_GENOMICA_REFERTO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	
	afx_msg void OnBnClickedBtnGenera();
	afx_msg void OnBnClickedBtnAnnulla();
	afx_msg void OnBnClickedBtnSalva();
	afx_msg void OnBnClickedBtnSu();
	afx_msg void OnBnClickedBtnGiu();
	afx_msg void OnBnClickedBtnRimuove();

	afx_msg void OnBnClickedBtnRtfNewTable();
	afx_msg void OnBnClickedBtnRtfMakeUpper();
	afx_msg void OnBnClickedBtnRtfMakeNormal();
	afx_msg void OnBnClickedBtnRtfMakeLower();
	afx_msg void OnBnClickedBtnRtfFont();//Julio - BUG 4392 Edicao de texto
	afx_msg void OnBnClickedBtnRtfImage();//Julio - BUG 4392 Edicao de texto

	afx_msg void OnNMDblclkListVarianti(NMHDR *pNMHDR, LRESULT *pResult);

	LRESULT ProccessVarianteFilter(WPARAM wParam, LPARAM lParam);

	LRESULT OnKeyboardPress(WPARAM wParam, LPARAM lParam);	//Julio BUG 3457 - Texter
	void SearchAndReplaceTexterPhrase(CString sFrase);		// Marvel Carvalho - Bug 3457 (FIX) TEXTER
	void ApplyTexterPhrase(long p_lIDFrase);				// Marvel Carvalho - Bug 3457 (FIX) TEXTER	
	
	CString CreateRTFTable(CString sTitle, long lRows, long lCols, CString* sValArray);

	DECLARE_MESSAGE_MAP()	
public:

	void RiempiLista();				
	void RiempiCombo();
	void UnselectAll();
	
	void OrdernaVarianti(); 	
	// Julio BUG 3791 - Melhoria frases resultado laudo genomica	
	void OrdenaVariantiPerTipo();
	void OrdenaVariantiPerPositivita();
	//
	void LoadLastReport();
	
	CString CalculateResult(long lIDSezioni);	
	CString GetResultText();  // Julio BUG 3791 - Melhoria frases resultado laudo genomica
	CString GetComplementText(); // Julio BUG 3791 - Melhoria frases resultado laudo genomica
	void GetComplementTextInParts(); // Julio - Ajustes para apresentação Sírio
	void GetOtherTexts(); // Julio - Ajustes para apresentação Fleury
	//
	void InputSectionWithGroupedValues(long lIDSezione);

	/// Variables ///
	void ChiediVariabili(CString& sTXT);
	void ChiediVariabiliCombo(CString& sTXT);
	void ChiediVariabiliSpeciale(CString& sTXT);
	void ChiediVariabiliTabelle(CString& sTXT);
	CString ChiediValoriSpeciale(CString sVariabili);
	void SostituisciVariabili(CString& sRTF, CString& sTXT);	
	///-----------///

	CButtonLocalize m_ctrlButtonGenera;
	CButtonLocalize m_ctrlButtonAnnulla;
	CButtonLocalize m_ctrlButtonSalva;
	CButtonLocalize m_ctrlButtonSu;
	CButtonLocalize m_ctrlButtonGiu;
	CButtonLocalize m_ctrlButtonRimuove;

	CListCtrl m_ctrlListVarianti;
	CListCtrl m_ctrlListVariantiSelezionate;

	CTXButtonBar23Ex m_ctrlButtonBar;
	CEditDynFormToolbar m_ctrlToolbar;
	CTXTextControl23Ex m_ctrlTextControl;
	CTXTextControl23Ex m_ctrlTextControlHide;
	CTXTextControl23Ex m_ctrlTextControlHide2;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CStaticLocalize m_ctrlStatic4;
	CStaticLocalize m_ctrlStatic5;
	CStaticLocalize m_ctrlStatic6;
	
	CComboBox m_ctrlComboTipoEsame;
	CComboBox m_ctrlComboMateriale;


private:
	CEsamiView* m_pEsamiView;

	CStatic m_ctrlStaticRicercaForm;
	CGenomicaRicercaVarianteForm* m_pRicercaForm;

	struct VARIABLES
	{
		long lIDItem;
		CString sVariable;
		CString sValue;
	};

	CList<VARIABLES*> m_listVariables;

	//Julio BUG 3791 - Melhoria frases resultado laudo genomica
	struct VARIANTE
	{
		long lID;
		long lIDTipo;
		long lIDPatogenicita;
		BOOL bPositivita;
	};
	
	CList<CList<VARIANTE>*> m_listVarianti;
	//

	long m_lIDEsame;
};
