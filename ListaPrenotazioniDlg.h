#pragma once

#include "EndoxResizableDlg.h"
#include "WorkListManager.h"

class CEsamiView;

class CListaPrenotazioniDlg : public CEndoxResizableDlg
{

public:

	CListaPrenotazioniDlg(CWnd* pParent, CEsamiView* pEsamiView);
	~CListaPrenotazioniDlg();

	enum { IDD = IDD_LISTA_PRENOTAZIONI };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	afx_msg void OnAggiorna();
	afx_msg void OnCbnSelchangeComboSede();
	afx_msg void OnDblClkList(NMHDR* pNMHDR, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()
	
	void RiempiLista();
	
	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlButtonRefresh;
	CListCtrl m_ctrlList;

	CEsamiView*	m_pEsamiView;
	CWorkListManager* m_pWorkListManager;

private:

	CComboBox m_ctrlComboSede;

};