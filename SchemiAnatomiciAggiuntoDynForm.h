#ifndef _SCHEMIANATOMICIAGGIUNTODYNFORM_H_
	#define _SCHEMIANATOMICIAGGIUNTODYNFORM_H_

#include "DLL_Imaging\h\AMEditComboListCtrl.h"

#include "EndoxDynForm.h"
#include "SchemiAnatomiciSet.h"
#include "SchemiAnatomiciAggiuntoSet.h"
#include "ListSortableCtrl.h"

class CSchemiAnatomiciAggiuntoDynForm : public CEndoxDynForm
{

public:

	CSchemiAnatomiciAggiuntoDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView);
	CSchemiAnatomiciAggiuntoDynForm(CWnd* pParent, CEsamiView* pEsamiView);
	~CSchemiAnatomiciAggiuntoDynForm();

	enum { IDD = IDD_SUBFORM_SCHEMI_ANATOMICI_AGGIUNTO };

	static void CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco);

protected:
	 
	void DoDataExchange(CDataExchange* pDX);
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL OnInitDialog();
	void OnSize(UINT nType, int cx, int cy);

	LRESULT OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormClone(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormLoad(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReadOnly(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReset(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSave(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSearchNew(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bAltered;										// controla se houve alteração no forma, se sim precisa salvar ou senão as alterações serão perdidas

	// USADOS PARA CONTROLAR OS RECORDSETS (DATABASE)
	CSchemiAnatomiciSet         m_setSchemiAnatomici;
	CSchemiAnatomiciAggiuntoSet m_setSchemiAnatomiciAggiunto;

	// USADOS PARA CONTROLAR OS GRIDS
	CAMEditComboListCtrl m_ctrlListGridSchemiAnatomici;          // Binded to [SCHEMI_ANATOMICI]
	CAMEditComboListCtrl m_ctrlListGridSchemiAnatomiciAggiunto;	 // Binded to [SCHEMI_ANATOMICI_AGGIUNTO]

	// USADOS PARA PREENCHER OS GRIDS
	void ListGridSchemiAnatomiciRiempi();
	long m_lCurrentSchemiAnatomici;
	long ListGridSchemiAnatomiciGetIDSelected();
	//void ListGridSchemiAnatomiciUpdateActual(long p_lIDSelected);

	CString ConvertSchemiAnatomiciAggiuntoStatoToString(long p_lSTATO);
	long ConvertSchemiAnatomiciAggiuntoStatoToLong(CString p_sSTATO);
	CString CalculateNewSequenceDescrizioneName();

	// USADOS PARA PREENCHER OS GRIDS
	void ListGridSchemiAnatomiciAggiuntoRiempi(long p_lCONTATORE_EESAMI);
	void ListGridSchemiAnatomiciAggiuntoSetSizeToAllColumns();
	long m_lCurrentSchemiAnatomiciAggiunto;
	int ListGridSchemiAnatomiciAggiuntoGetIDSelected(long* p_lContatoreSchemiAggiuntoToEdit, long* p_lIDSchemiAnatomici);
	void ListGridSchemiAnatomiciAggiuntoSaveAllToDatabase();
	CString ListGridSchemiAnatomiciAggiuntoGetAcao(long* p_lID, int p_nRowNumber);

	void ListGridSetItemFocus(CAMEditComboListCtrl* p_pThisList, int iRow);
	void ListGridSetDBControl(CAMEditComboListCtrl* p_pThisList, int p_iRow, CString p_strDBControl);
	void ListGridSetRowColor(CAMEditComboListCtrl* p_pThisList, int p_iRow);
	int ListGridGetColumnsCount(CAMEditComboListCtrl* p_pThisList);
	
	// USADO PARA INDICAR O ESQUEMA SELECIONADO (NO GRID) / A LABEL SELECIONADA (NO GRID)
	// ?? CSchemiAnatomici* m_pSchemiAnatomiciActual;   // CWnd Class Base
	// ??CSchemiAnatomiciEtichette* m_pSchemiAnatomiciEtichetteActual;   // CWnd Class Base

	long m_lIDESAMI;    // usado para identificar o tipo (ou sigla) do exame atual via tabelas: [ETipoEsame INNER JOIN UO ON ETipoEsame.UO = UO.ID]

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	BOOL m_bReadOnly;

public:
	afx_msg void OnNMClickListSad(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListSad(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnNMClickListSaa(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListSaa(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnEdt();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnNMRClickListSaa(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedHlp();

};

#endif /* _SCHEMIANATOMICIAGGIUNTODYNFORM_H_ */