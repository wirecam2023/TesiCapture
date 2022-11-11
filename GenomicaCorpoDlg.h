#pragma once

#include "TXTextControl23.h"
#include "TXButtonBar23.h"
#include "EditDynFormToolbar.h"
#include "GenomicaRicercaVarianteForm.h"

class CGenomicaCorpoDlg : public CDialog
{
	DECLARE_DYNAMIC(CGenomicaCorpoDlg)

public:
	CGenomicaCorpoDlg(CWnd* pParent, CEsamiView* m_pEsamiView);
	virtual ~CGenomicaCorpoDlg();

	enum { IDD = IDD_GENOMICA_CORPO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();

	afx_msg void OnLvnItemchangedListVarianti(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListSezioni(NMHDR *pNMHDR, LRESULT *pResult);	
	//afx_msg void OnBnClickedBtnNew();
	afx_msg void OnBnClickedBtnEdt();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnUndo();
	afx_msg void OnBnClickedBtnRtfNewTable();
	afx_msg void OnBnClickedBtnRtfMakeUpper();
	afx_msg void OnBnClickedBtnRtfMakeNormal();
	afx_msg void OnBnClickedBtnRtfMakeLower();	
	afx_msg void OnBnClickedBtnRtfFont();//Julio - BUG 4392 Edicao de texto

	LRESULT ProccessVarianteFilter(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()	

	CEsamiView* m_pEsamiView;

public:
	void RiempiLista();	
	void CaricaDati();
	void EditDialog(BOOL bEdit);
	void UnselectAll();
	void CaricaSuggerimenti();

	/// Variables ///
	void ChiediVariabiliSpeciale(CString& sTXT);
	CString ChiediValoriSpeciale(CString sVariabili);	
	void SostituisciVariabili(CString& sRTF, CString& sTXT);
	///-----------///

	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonEdit;
	CButtonLocalize m_ctrlButtonDelete;
	CButtonLocalize m_ctrlButtonSave;
	CButtonLocalize m_ctrlButtonUndo;
	CButtonLocalize m_ctrlButtonCancel;	

	CListCtrl m_ctrlListVarianti;
	CListCtrl m_ctrlListSezioni;

	CTXButtonBar23Ex m_ctrlButtonBar;
	CEditDynFormToolbar m_ctrlToolbar;
	CTXTextControl23Ex m_ctrlTextControl;	
	CTXTextControl23Ex m_ctrlTextControlHide;

	long m_lIDSezioneSelected;
	long m_lIDVarianteSelected;

private:
	CStatic m_ctrlStaticRicercaForm;
	CGenomicaRicercaVarianteForm* m_pRicercaForm;

	struct VARIABLES
	{
		long lIDItem;
		CString sVariable;
		CString sValue;
	};
	
	CList<VARIABLES*> m_listVariables;
};
