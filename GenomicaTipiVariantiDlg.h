#pragma once

#include "TXTextControl23.h"
#include "TXButtonBar23.h"
#include "EditDynFormToolbar.h"

class CGenomicaTipiVariantiDlg : public CDialog
{
	DECLARE_DYNAMIC(CGenomicaTipiVariantiDlg)

public:
	CGenomicaTipiVariantiDlg(CWnd* pParent);
	virtual ~CGenomicaTipiVariantiDlg();

	enum { IDD = IDD_GENOMICA_TIPIVARIANTIGENETICHE };

protected:

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
	
	afx_msg void OnBnClickedBtnRtfNewTable();
	afx_msg void OnBnClickedBtnRtfMakeUpper();
	afx_msg void OnBnClickedBtnRtfMakeNormal();
	afx_msg void OnBnClickedBtnRtfMakeLower();
	afx_msg void OnBnClickedBtnRtfFont();//Julio - BUG 4392 Edicao de texto

	DECLARE_MESSAGE_MAP()
private:

	void RiempiLista();
	void CaricaDati();
	void EditDialog(BOOL bEdit);
	void UnselectAll();


	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonEdit;
	CButtonLocalize m_ctrlButtonDelete;
	CButtonLocalize m_ctrlButtonSave;
	CButtonLocalize m_ctrlButtonUndo;
	CButtonLocalize m_ctrlButtonCancel;

	CListCtrl m_ctrlList;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;

	CButtonLocalize m_ctrlButtonObbligatorioCodice;
	CButtonLocalize m_ctrlButtonObbligatorioAlterazione;
	CButtonLocalize m_ctrlButtonObbligatorioTrascrizione;
	CButtonLocalize m_ctrlButtonFraseRisultatoRemovibile;

	CTXButtonBar23Ex m_ctrlButtonBar;
	CEditDynFormToolbar m_ctrlToolbar;
	CTXTextControl23Ex m_ctrlTextControl;

	long m_lIDSelected;	
};
