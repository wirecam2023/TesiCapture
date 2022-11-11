#pragma once

#include "EndoxResizableDlg.h"
#include "DMSWorkListManager.h"

class CEsamiView;

class CListaPrenotazioniDMSDlg : public CEndoxResizableDlg
{

public:

	CListaPrenotazioniDMSDlg(CWnd* pParent, CEsamiView* pEsamiView);
	~CListaPrenotazioniDMSDlg();

	enum { IDD = IDD_LISTA_PRENOTAZIONI_DMS };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	afx_msg void OnDblClkList(NMHDR* pNMHDR, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()
	
	void RiempiLista(CString sCodVet);
	
	CListCtrlLocalize m_ctrlList;

	CEsamiView*	m_pEsamiView;
	CDMSWorkListManager* m_pWorkListManager;

};