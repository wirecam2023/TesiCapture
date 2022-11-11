#include "stdafx.h"
#include "Endox.h"
#include "AgendeSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CAgendeSet, CBaseSet)

CAgendeSet::CAgendeSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 5;
}

CString CAgendeSet::GetDefaultSQL()
{
	return "AGENDE";
}

void CAgendeSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		RFX_Text(pFX, "CodiceIntegrazione", m_sCodiceIntegrazione, 50);
		RFX_Long(pFX, "IDSALA", m_lIDSala);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CAgendeSet::SetEmpty()
{
	m_lID = 0;
	m_sDescrizione = "";
	m_sCodiceIntegrazione = "";
	m_lIDSala = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CAgendeSet::CreateNew()
{
	return (CBaseSet*)new CAgendeSet;
}

void CAgendeSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CAgendeSet* pSet = (CAgendeSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodiceIntegrazione) || bCopyAll)
	m_sCodiceIntegrazione = pSet->m_sCodiceIntegrazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDSala) || bCopyAll)
		m_lIDSala = pSet->m_lIDSala;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CAgendeSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CAgendeSet* pOV = (CAgendeSet*)pOldValues;
	CAgendeSet* pNV = (CAgendeSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("CodiceIntegrazione", pOV, &pOV->m_sCodiceIntegrazione, pNV, &pNV->m_sCodiceIntegrazione);
	sp.Execute("IDSALA", pOV, &pOV->m_lIDSala, pNV, &pNV->m_lIDSala);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CAgendeSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CAgendeSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CAgendeSet::DeleteRecordset");
	}
	return bReturn;
}

CString CAgendeSet::SetBaseFilter(const CString &strFilter)
{
	CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	if (strNewFilter.IsEmpty())
	{
		strNewFilter = "ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("ELIMINATO=") < 0)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}

BOOL CAgendeSet::UpdateRecordset(const CString &strCommento)
{
	return CBaseSet::UpdateRecordset(strCommento);
}

CString CAgendeSet::GetCodiceIntegrazioneFromIdSala(int lIDSala)
{
	CString sReturn = "";

	CString sFilter;
	sFilter.Format("idSala=%li", lIDSala);

	SetOpenFilter(sFilter);
	SetSortRecord("ID DESC");

	if (OpenRecordset("CSaleEsameSet::GetCodiceSedeEstFromIdSala"))
	{
		if (!IsEOF())
			sReturn = m_sCodiceIntegrazione;

		CloseRecordset("CSaleEsameSet::GetCodiceSedeEstFromIdSala");
	}

	return sReturn;
}

/*CString CSaleEsameSet::GetCodiceSedeEstFromIdSede(int lIDSede)
{
CString sReturn = "";

CString sFilter;
sFilter.Format("idSede=%li", lIDSede);

SetOpenFilter(sFilter);
if (OpenRecordset("CSaleEsameSet::GetCodiceSedeEstFromIdSala"))
{
if (!IsEOF())
sReturn = m_sCodiceIntegrazione;

CloseRecordset("CSaleEsameSet::GetCodiceSedeEstFromIdSala");
}

return sReturn;
}*/
