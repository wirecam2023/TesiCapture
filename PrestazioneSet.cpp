#include "stdafx.h"
#include "Endox.h"
#include "PrestazioneSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CPrestazioneSet, CBaseSet)

CPrestazioneSet::CPrestazioneSet()
	: CBaseSet(NULL, "VIEW") // è una vista //
{
	SetSortRecord("CODICENAZIONALE");
	SetEmpty();

	m_nFields = 5;
}

CString CPrestazioneSet::GetDefaultSQL()
{
	return "";
}

void CPrestazioneSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Text(pFX, "CodiceNazionale", m_sCodice, 10);
	RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
	RFX_Long(pFX, "SumQuantita", m_lSumQuantita);
	RFX_Text(pFX, "Inviante1", m_sInviante1, 50);
	RFX_Text(pFX, "Inviante2", m_sInviante2, 4000);
}

void CPrestazioneSet::SetEmpty()
{
	m_sCodice = "";
	m_sDescrizione = "";
	m_lSumQuantita = 0;
	m_sInviante1 = "";
	m_sInviante2 = "";
}