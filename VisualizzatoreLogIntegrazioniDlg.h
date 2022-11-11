#ifndef _VISUALIZZATORELOGINTEGRAZIONIDLG_H_
#define _VISUALIZZATORELOGINTEGRAZIONIDLG_H_

#include "EndoxResizableDlg.h"
#include "ListSortableCtrl.h"

class CVisualizzatoreLogIntegrazioniDlg : public CEndoxResizableDlg
{
	DECLARE_DYNAMIC(CVisualizzatoreLogIntegrazioniDlg)

public:

	CVisualizzatoreLogIntegrazioniDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CVisualizzatoreLogIntegrazioniDlg();

	enum { IDD = IDD_LOGINTEGRAZIONI };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()

private:
	
	void RemoveAll(BOOL changedCombo=FALSE);
	void RiempiLista(BOOL changedCombo = FALSE);
	void RiempiListaInput();
	void RiempiListaReferti();

	BOOL IsOracleConnection();

	void CheckComboTipo();

	CString RimuoviDoppiSpazi(CString input);
	CString GetDataOraFrom();
	CString GetDataOraTo();
	void ShowMenu();
	//

	afx_msg void RiprocessaMessaggio();

	CEsamiView* m_pEsamiView;

	CStaticLocalize m_ctrlStatic1, m_ctrlStatic2, m_ctrlStatic3, m_ctrlStatic4;
	CStaticLocalize m_ctrlStatic5, m_ctrlStatic6, m_ctrlStatic7, m_ctrlStatic8, m_ctrlStatic9;
	CButtonLocalize m_ctrlBtnChiudi;
	CListSortableCtrl m_ctrlListIntegrazioni;

	CComboBox m_ctrlMsgType;
	CDateTimeCtrl m_ctrlDateFrom, m_ctrlTimeFrom;
	CDateTimeCtrl m_ctrlDateTo, m_ctrlTimeTo;

	CEdit m_ctrlEditFilter;

	CList<long> m_listErrored;
	CList<long> m_listWarned;
	CList<long> m_listInProgress;
	CList<long> m_listSent;

	CString m_sPreviousFilter;
	int m_lPreviousComboValue;

	int m_iColumn;

public:
	afx_msg void OnCbnSelchangeComboList();
	afx_msg void OnDtnDatetimechangeDateFrom(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeTimeFrom(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeDateTo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeTimeTo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListMessages(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnNMDblclkListMessages(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedRefresh();
};

#endif /* _VISUALIZZATORELOGINTEGRAZIONIDLG_H_ */