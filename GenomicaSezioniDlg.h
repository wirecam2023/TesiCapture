#pragma once

#include "TXTextControl23.h"
#include "TXButtonBar23.h"
#include "EditDynFormToolbar.h"


class CGenomicaSezioniDlg : public CDialog
{
	DECLARE_DYNAMIC(CGenomicaSezioniDlg)

public:
	CGenomicaSezioniDlg(CWnd* pParent);
	virtual ~CGenomicaSezioniDlg();

	enum { IDD = IDD_GENOMICA_SEZIONI };

protected:
	
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();

	afx_msg void OnLvnItemchangedListSezione(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListTipiReferto(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedBtnNew();
	afx_msg void OnBnClickedBtnEdt();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnUndo();
	afx_msg void OnBnClickedBtnSu();
	afx_msg void OnBnClickedBtnGiu();

	afx_msg void OnBnClickedBtnRtfNewTable();
	afx_msg void OnBnClickedBtnRtfMakeUpper();
	afx_msg void OnBnClickedBtnRtfMakeNormal();
	afx_msg void OnBnClickedBtnRtfMakeLower();
	afx_msg void OnBnClickedBtnRtfFont();//Julio - BUG 4392 Edicao de texto

	DECLARE_MESSAGE_MAP()
private:

	void RiempiListaSezioni();
	void RiempiListaTipiReferto();

	void RiempiCombo();
	void RiempiComboUnselectAll();
	void CaricaDati();
	
	void EditDialog(BOOL bEdit);
	void UnselectAll();

	int GetOrdineFromSelectedListSezione(
		long* p_lIDPrevious, long* p_lIDSelected, long* p_lIDNext,
		int* p_iOrdinePrevious, int* p_iOrdineSelected, int* p_iOrdineNext,
		int p_iMovement
		);

	CString m_ctrlListBoxTipoVariante_GetStringVari();


	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonEdit;
	CButtonLocalize m_ctrlButtonDelete;
	CButtonLocalize m_ctrlButtonSave;
	CButtonLocalize m_ctrlButtonUndo;
	CButtonLocalize m_ctrlButtonCancel;
	CButtonLocalize m_ctrlButtonSu;
	CButtonLocalize m_ctrlButtonGiu;
	CButtonLocalize m_ctrlButtonRisultato;

	CComboBox m_ctrlComboTipoVariante;
	
	CListCtrl m_ctrlListTipiReferto;
	CListCtrl m_ctrlListSezione;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;	
	CStaticLocalize m_ctrlStatic3;

	CTXButtonBar23Ex m_ctrlButtonBar;
	CEditDynFormToolbar m_ctrlToolbar;
	CTXTextControl23Ex m_ctrlTextControl;

	CTXButtonBar23Ex m_ctrlButtonBar2;
	CEditDynFormToolbar m_ctrlToolbar2;
	CTXTextControl23Ex m_ctrlTextControl2;

	long m_lIdTipoRefertoSelected;
	long m_lIdSezioniSelected;


public:
	afx_msg void OnBnClickedBtnSelect();
};
