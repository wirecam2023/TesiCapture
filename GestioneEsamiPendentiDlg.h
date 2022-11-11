#ifndef _GESTIONEESAMIPENDENTIDLG_H_
	#define _GESTIONEESAMIPENDENTIDLG_H_

#include "ListSortableCtrl.h"
#include "MaskEdit.h"
#include "OsservazioniListCtrl.h"
#include "QueryUtility.h"

class CGestioneEsamiPendentiDlg : public CResizableDialog, public CQueryUtility
{
	DECLARE_DYNAMIC(CGestioneEsamiPendentiDlg)

public:

	CGestioneEsamiPendentiDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CGestioneEsamiPendentiDlg();

	enum { IDD = IDD_GESTIONE_ESAMI_PENDENTI };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnAggiorna();
	afx_msg void OnBnClickedBtnEsci();
	afx_msg void OnBnClickedBtnStampa();
	afx_msg void OnCbnSelchangeComboData();
	afx_msg void OnCbnSelchangeComboMedico();
	afx_msg void OnCbnSelchangeComboUO();
	afx_msg void OnNMCustomdrawList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);

	// Marvel Carvalho | BUG 3780 - TesiCapture Melhoria Filtro Esami Pendenti
	void ThisFilterFieldsSave();
	void ThisFilterFieldsRestore();

	CString FormatDate(CString sDate); //Gabriel BUG 6225 - Lista DO FIX
	CString FormatTime(CString sDate); //Gabriel BUG 6225 - Lista DO FIX

private:

	void RiempiComboMedici();
	void RiempiComboUO();

	//

	CButtonLocalize m_ctrlBtnAggiorna;
	CButtonLocalize m_ctrlBtnEsci;
	CButtonLocalize m_ctrlBtnStampa;

	CComboBox m_ctrlComboData;
	CComboBox m_ctrlComboMedico;
	CComboBox m_ctrlComboUO;

	// COsservazioniListCtrl m_ctrlList;
	CListSortableCtrl m_ctrlList;

	CMaskEdit m_ctrlDataFine;
	CMaskEdit m_ctrlDataIniz;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CStaticLocalize m_ctrlStatic4;
	CStaticLocalize m_ctrlStatic5;

	//

	CEsamiView* m_pEsamiView;

	// Sandro 08/06/2015 //

	CList<long> m_listIDToHighlightYellow;
	CList<long> m_listIDToHighlightOrange;
	CList<long> m_listIDToHighlightRed;

	int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
};

#endif /* _GESTIONEESAMIPENDENTIDLG_H_ */