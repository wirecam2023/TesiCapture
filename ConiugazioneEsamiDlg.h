#ifndef _CONIUGAZIONEESAMIDLG_H_
	#define _CONIUGAZIONEESAMIDLG_H_

#include "Common.h"

class CExtOrdiniSet;

class CConiugazioneEsamiDlg : public CDialog
{

	DECLARE_DYNAMIC(CConiugazioneEsamiDlg)

public:

	CConiugazioneEsamiDlg(CWnd* pParent, CEsamiView* pEsamiView, CList<STRUCT_FICHA_ITEM> *pListFichaItem, CString sActUO, CString sActFichaItem);
	virtual ~CConiugazioneEsamiDlg();

	enum { IDD = IDD_CONIUGAZIONE_ESAMI };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnEsci();
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);

private:

	void SelectEntry(long lIDExtOrdini, long lIDPaziente);
	BOOL SelectEntryFasePreliminare(CExtOrdiniSet* pSetExtOrdini);
	void SelectEntryFaseImportazioneEsame(long lIDExtOrdini, long lIDPaziente, CExtOrdiniSet* pSetExtOrdini, long lUO);

	BOOL CampiObbligatoriValorizzati(long lIDExtOrdini);
	void UpdateDataFromWorklist(long lIDExtOrdini, long lIDPaziente, CEsamiSet* pEsamiSet);
	void UpdateDatiEsame(long lIDPaziente, long lIDEsame, long lIDExtOrdini, CExtOrdiniSet* pSetExtOrdini, long lUO);
	void UpdateWithExamID(long lIDEsame, CExtOrdiniSet* pSetExtOrdini);

	//

	CButtonLocalize m_ctrlBtnEsci;

	CListCtrl m_ctrlList;

	//

	CEsamiView* m_pEsamiView;

	CList<STRUCT_FICHA_ITEM> *m_pListFichaItem;

	CString m_sActUO;
	CString m_sActFichaItem;

};

#endif /* _CONIUGAZIONEESAMIDLG_H_ */