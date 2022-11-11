#include "stdafx.h"
#include "Endox.h"
#include "ListaPrestazioniCupSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CListaPrestazioniCupSet, CBaseSet)

CListaPrestazioniCupSet::CListaPrestazioniCupSet()
	: CBaseSet(&m_lContatore, "contatore")
{
	SetEmpty();
	m_nFields = 5;
}

CString CListaPrestazioniCupSet::GetDefaultSQL()
{
	return "ListaPrestazioniCup";
}

void CListaPrestazioniCupSet::SetEmpty()
{
	m_lContatore = 0;
	m_sOrderNumber = "";
	m_sRequestNumber = "";
	m_lIdPrestazioneEndox = 0;
	m_lQuantita = 0;
}

void CListaPrestazioniCupSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "contatore", m_lContatore);
	RFX_Text(pFX, "orderNumber", m_sOrderNumber, 50);
	RFX_Text(pFX, "requestNumber", m_sRequestNumber, 50);
	RFX_Long(pFX, "idPrestazioneEndox", m_lIdPrestazioneEndox);
	RFX_Long(pFX, "Quantita", m_lQuantita);
}

void CListaPrestazioniCupSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CListaPrestazioniCupSet* pListaPrestazioniCupSet = (CListaPrestazioniCupSet*)pOriginalSet;

	if (!pListaPrestazioniCupSet->IsOpen() || pListaPrestazioniCupSet->IsFieldDirty(&pListaPrestazioniCupSet->m_sOrderNumber) || bCopyAll)
		m_sOrderNumber = pListaPrestazioniCupSet->m_sOrderNumber;
	if (!pListaPrestazioniCupSet->IsOpen() || pListaPrestazioniCupSet->IsFieldDirty(&pListaPrestazioniCupSet->m_sRequestNumber) || bCopyAll)
		m_sRequestNumber = pListaPrestazioniCupSet->m_sRequestNumber;
	if (!pListaPrestazioniCupSet->IsOpen() || pListaPrestazioniCupSet->IsFieldDirty(&pListaPrestazioniCupSet->m_sRequestNumber) || bCopyAll)
		m_sRequestNumber = pListaPrestazioniCupSet->m_sRequestNumber;
	if (!pListaPrestazioniCupSet->IsOpen() || pListaPrestazioniCupSet->IsFieldDirty(&pListaPrestazioniCupSet->m_lQuantita) || bCopyAll)
		m_lQuantita = pListaPrestazioniCupSet->m_lQuantita;
}

BOOL CListaPrestazioniCupSet::DeleteRecordset(const CString &strCommento)
{
	return TRUE;
}

CString CListaPrestazioniCupSet::SetBaseFilter(const CString &strFilter)
{
	return CBaseSet::SetBaseFilter("");
}