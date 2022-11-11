#ifndef _ANATOMIAPATOLOGICAFORM_H_
	#define _ANATOMIAPATOLOGICAFORM_H_

#include "SubForm.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "AnatomiaPatologicaListCtrl.h"

class CAnatomiaPatologicaForm : public CEndoxDynForm
{

public:

	CAnatomiaPatologicaForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView);
	~CAnatomiaPatologicaForm();

	// enum { IDD = IDD_SUBFORM_ANATOMIAPATOLOGICA };

	static void CreateFormEx(UINT nID, CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco);
	static BOOL CreateFormEx(UINT nID, CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, CAnatomiaPatologicaForm** pForm);

	CString GetField(int nSubItem);
	long GetNumRows();
	void StampaTutteLeRighe(); // Sandro 19/09/2013 // RAS 20130099 //

	CAnatomiaPatologicaListCtrl m_ctrlList;

protected:

	void DoDataExchange(CDataExchange* pDX);
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL OnInitDialog();

	afx_msg void OnBnClickedRadio();
	afx_msg void OnBnClickedGruppi();
	afx_msg void OnBnClickedNew();
	afx_msg void OnBnClickedEdt();
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedStampaTutti();
	afx_msg void OnBnClickedNewSearch();
	afx_msg void OnBnClickedDelSearch();

	afx_msg void OnLvnItemChangedList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemChangedListSearch(NMHDR *pNMHDR, LRESULT *pResult);

	LRESULT OnFormLoad(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormReadOnly(WPARAM wParam, LPARAM lParam);
	LRESULT OnFormSearchNew(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:

	void RiempiLista();
	static void StampaRiga(long lRecord, CEsamiView* pEsamiView);

	long GetContenuto();
	BOOL CampoObbligatorioValido();

	CEsamiView* m_pEsamiView;

	WPARAM m_wpReadOnly;

	BOOL m_bEsameOK;

	CImageList m_ctrlImageList;
	CListCtrl m_ctrlListSearch;

	CButtonLocalize m_ctrlRadioNo;
	CButtonLocalize m_ctrlRadioSi;
	CButtonLocalize m_ctrlButtonGruppi;
	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonEdt;
	CButtonLocalize m_ctrlButtonDel;
	CButtonLocalize m_ctrlButtonStampaTutti;
	CButtonLocalize m_ctrlBtnNewSearch;
	CButtonLocalize m_ctrlBtnDelSearch;
	CButtonLocalize m_ctrlBtnRadioAnd;
	CButtonLocalize m_ctrlBtnRadioOr;

	CStaticLocalize m_ctrlStaticPrelievi;

	int m_nSearchMode;
};

#endif /* _ANATOMIAPATOLOGICAFORM_H_ */