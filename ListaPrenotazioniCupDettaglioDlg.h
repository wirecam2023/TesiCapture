#pragma once

#include "EndoxResizableDlg.h"
#include "CupWorkListManager.h"
#include "VistaExtPrestazioniSet.h"

class CEsamiView;

class CListaPrenotazioniCupDettaglioDlg : public CEndoxResizableDlg
{

public:

	CListaPrenotazioniCupDettaglioDlg(CWnd* pParent, CEsamiView* pEsamiView, long lIdOrdine);
	~CListaPrenotazioniCupDettaglioDlg();

	enum { IDD = IDD_LISTA_PRENOTAZIONI_DETTAGLIO };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
	
	void RiempiDatiOrdine();
	void RiempiPrestazioni();
	
	CButtonLocalize m_ctrlButtonOK;
	CListCtrlLocalize m_ctrlListOrdini, m_ctrlListPrestazioni;
	CStaticLocalize m_ctrlStaticPrestazioni;

	CEsamiView*	m_pEsamiView;
	long m_lIdOrdine;

};