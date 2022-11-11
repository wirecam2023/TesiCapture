#pragma once

#include "EndoxResizableDlg.h"
#include "ListSortableCtrl.h"
#include "WorkListManager.h"

class CCupWorkListManager;
class CEsamiView;

class CListaPrenotazioniCupDicomDlg : public CEndoxResizableDlg
{

public:

	CListaPrenotazioniCupDicomDlg(CWnd* pParent, CEsamiView* pEsamiView);
	~CListaPrenotazioniCupDicomDlg();

	enum { IDD = IDD_LISTA_PRENOTAZIONI_CUP_DICOM };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
	
	void RiempiListe();
	
	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlButtonRefresh;
	CListSortableCtrl m_ctrlListCup;
	CListSortableCtrl m_ctrlListDicom;

	CEsamiView*	m_pEsamiView;
	CCupWorkListManager* m_pWorkListManagerCup;
	CWorkListManager* m_pWorkListManagerDicom;

public:
	afx_msg void OnNMDblclkListCup(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListDicom(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedAggiorna();
	afx_msg void OnBnClickedCancel();
};