#include "stdafx.h"
#include "Endox.h"
#include "RicercaIndicazioniSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CRicercaIndicazioniSet, CBaseSet)

CRicercaIndicazioniSet::CRicercaIndicazioniSet()
	: CBaseSet(NULL, "VIEW") // è una vista //
{
	SetSortRecord("DESCR1");

	m_sDescr1 = "";
	m_sDescr2 = "";

	m_nFields = 2;
}

void CRicercaIndicazioniSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Text (pFX, "Descr1",	m_sDescr1, 255);
	RFX_Text (pFX, "Descr2",	m_sDescr2, 255);
}

CString CRicercaIndicazioniSet::GetDefaultSQL()
{
	/*
	SELECT DISTINCT tab1.descrizione AS descr1, tab2.descrizione AS descr2
	FROM emstindicazioni tab1 LEFT OUTER JOIN emstindicazioni tab2 ON tab1.contatore = tab2.padre
	WHERE tab1.padre = 0
	ORDER BY descr1, descr2
	*/

	return "RICERCAINDICAZIONI";
}

void CRicercaIndicazioniSet::SetEmpty()
{
	m_sDescr1 = "";
	m_sDescr2 = "";
}