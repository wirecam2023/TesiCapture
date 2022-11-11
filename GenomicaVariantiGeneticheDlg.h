#pragma once
#include "GenomicaRicercaVarianteForm.h"

class CGenomicaVariantiGeneticheDlg : public CDialog
{
	DECLARE_DYNAMIC(CGenomicaVariantiGeneticheDlg)

public:
	CGenomicaVariantiGeneticheDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CGenomicaVariantiGeneticheDlg();

	enum { IDD = IDD_GENOMICA_VARIANTIGENETICHE };

protected:
	CEsamiView* m_pEsamiView;

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();

	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnNew();
	afx_msg void OnBnClickedBtnEdt();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnUndo();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCbnSelchange();	

	LRESULT ProccessVarianteFilter(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

public:
	
	void RiempiLista();
	void RiempiCombos();
	void CaricaDati();
	void EditDialog(BOOL bEdit);
	void UnselectAll();


	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonEdit;
	CButtonLocalize m_ctrlButtonDelete;
	CButtonLocalize m_ctrlButtonSave;
	CButtonLocalize m_ctrlButtonUndo;
	CButtonLocalize m_ctrlButtonCancel;

	CComboBox m_ctrlComboPatogenicita;
	CComboBox m_ctrlComboTipoVariante;
	CComboBox m_ctrlComboTipoAlterazione;

	CListCtrl m_ctrlList;

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

	long m_lIDSelected;	
	long m_lIDTipoVarianteSelected;
	long m_lIDTipoAlterazioneSelected;
	BOOL m_bMarcaObbligatori;

private:
	BOOL VerificaCampiObbligatori();

	CStatic m_ctrlStaticRicercaForm;
	CGenomicaRicercaVarianteForm* m_pRicercaForm;
};