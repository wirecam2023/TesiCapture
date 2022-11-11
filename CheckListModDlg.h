#ifndef _CHECKLISTMODDLG_H_
	#define _CHECKLISTMODDLG_H_

#include "Common.h"

class CCheckListModDlg : public CDialog
{

	DECLARE_DYNAMIC(CCheckListModDlg)

public:

	CCheckListModDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CCheckListModDlg();

	enum { IDD = IDD_CHECKLIST_MOD_DLG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnNew();
	afx_msg void OnBnClickedBtnEdt();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnClone();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnUndo();
	afx_msg void OnBnClickedBtnNewExam();
	afx_msg void OnBnClickedBtnDelExam();
	afx_msg void OnBnClickedBtnNewEl1();
	afx_msg void OnBnClickedBtnNewEl2();
	afx_msg void OnBnClickedBtnNewEl3();
	afx_msg void OnBnClickedBtnEdtEl();
	afx_msg void OnBnClickedBtnDelEl();
	afx_msg void OnBnClickedBtnUp();
	afx_msg void OnBnClickedBtnDn();
	afx_msg void OnBnClickedBtnCopy();
	afx_msg void OnBnClickedBtnPaste();
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListExam(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);

private:

	void CaricaDati();
	void DeselezionaTutti();
	void RiempiAlbero(long lIDItemToSelect);
	HTREEITEM RiempiAlberoSub(HTREEITEM hRoot, long lIDPadre, long lIDItemToSelect);
	void RiempiLista();
	void RiempiListaExam();
	void SalvaAlbero();
	void SalvaAlberoSub(long lIDPadreOrig, long lIDPadreDest, CList<STRUCT_COPPIA_LONG>* pIDsList);
	void SalvaEsami();
	void SetReadOnly(BOOL bReadOnly);

	// --- //

	BOOL m_bCloning;
	long m_lCloningID;

	long m_lIDCheckList;
	long m_lIDCheckListItem;
	long m_lIDCheckListItemPadre;
	long m_lIDCheckListItemSiblingPrev;
	long m_lIDCheckListItemSiblingNext;

	long m_lIDItemCopiato;

	// --- //

	CButton m_ctrlCheck1;
	CButton m_ctrlCheck2;

	CButtonLocalize m_ctrlBtnNew;
	CButtonLocalize m_ctrlBtnEdt;
	CButtonLocalize m_ctrlBtnDel;
	CButtonLocalize m_ctrlBtnClone;
	CButtonLocalize m_ctrlBtnSave;
	CButtonLocalize m_ctrlBtnUndo;
	CButtonLocalize m_ctrlBtnNewExam;
	CButtonLocalize m_ctrlBtnDelExam;
	CButtonLocalize m_ctrlBtnNewEl1;
	CButtonLocalize m_ctrlBtnNewEl2;
	CButtonLocalize m_ctrlBtnNewEl3;
	CButtonLocalize m_ctrlBtnEdtEl;
	CButtonLocalize m_ctrlBtnDelEl;
	CButtonLocalize m_ctrlBtnUp;
	CButtonLocalize m_ctrlBtnDn;
	CButtonLocalize m_ctrlBtnCopy;
	CButtonLocalize m_ctrlBtnPaste;
	CButtonLocalize m_ctrlBtnOK;

	CComboBox m_ctrlCombo;
	CComboBox m_ctrlComboCampo;
	CComboBox m_ctrlComboOrdine;

	CListCtrlLocalize m_ctrlList;
	CListCtrlLocalize m_ctrlListExam;

	CEdit m_ctrlEditCod;
	CEdit m_ctrlEditDesc;

	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;
	CStaticLocalize m_ctrlStatic03;
	CStaticLocalize m_ctrlStatic04;
	CStaticLocalize m_ctrlStatic05;
	CStaticLocalize m_ctrlStatic06;
	CStaticLocalize m_ctrlStatic07;
	CStaticLocalize m_ctrlStatic08;

	CTreeCtrl m_ctrlTree;

	//

	CList<long> m_listExamToDelete;
	CList<STRUCT_CHECKLISTITEM> m_listChecklistItem;
	CEsamiView* m_pEsamiView;

};

#endif /* _CHECKLISTMODDLG_H_ */