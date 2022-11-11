#include "stdafx.h"
#include "Endox.h"
#include "VitalSignMisurazioniDetailSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVitalSignMisurazioniDetailSet, CBaseSet)

CVitalSignMisurazioniDetailSet::CVitalSignMisurazioniDetailSet()
: CBaseSet(&m_lID, "ID")
{
	SetEmpty();
	SetSortRecord("ID");
	SetBaseFilter("");

	m_nFields = 9;
}

CString CVitalSignMisurazioniDetailSet::GetDefaultSQL()
{
	return "VITALSIGN_MISURAZIONI_DETAIL";
}

void CVitalSignMisurazioniDetailSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	RFX_Text(pFX, "IDVITALSIGN", m_sVitalSignId, 255);
	RFX_Long(pFX, "IDHEADER", m_lIDHeader);
	RFX_Text(pFX, "ORA", m_sOra, 8);
	RFX_Text(pFX, "FC", m_sFC);
	RFX_Text(pFX, "PA", m_sPA);
	RFX_Text(pFX, "SAT", m_sSat);
	RFX_Text(pFX, "NOTE", m_sNote, 1000000);
	RFX_Bool(pFX, "ELIMINATO", m_bEliminato);
}

void CVitalSignMisurazioniDetailSet::SetEmpty()
{
	m_lID = 0;
	m_sVitalSignId = "";
	m_lIDHeader = 0;
	m_sOra = "";
	m_sFC = "";
	m_sPA = "";
	m_sSat = "";
	m_sNote = "";
	m_bEliminato = FALSE;
}

CBaseSet* CVitalSignMisurazioniDetailSet::CreateNew()
{
	return (CBaseSet*)new CVitalSignMisurazioniDetailSet;
}

void CVitalSignMisurazioniDetailSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CVitalSignMisurazioniDetailSet* pSet = (CVitalSignMisurazioniDetailSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sVitalSignId) || bCopyAll)
		m_sVitalSignId = pSet->m_sVitalSignId;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDHeader) || bCopyAll)
		m_lIDHeader = pSet->m_lIDHeader;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sOra) || bCopyAll)
		m_sOra = pSet->m_sOra;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFC) || bCopyAll)
		m_sFC = pSet->m_sFC;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sPA) || bCopyAll)
		m_sPA = pSet->m_sPA;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sSat) || bCopyAll)
		m_sSat = pSet->m_sSat;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNote) || bCopyAll)
		m_sNote = pSet->m_sNote;	
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CVitalSignMisurazioniDetailSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CVitalSignMisurazioniDetailSet* pOV = (CVitalSignMisurazioniDetailSet*)pOldValues;
	CVitalSignMisurazioniDetailSet* pNV = (CVitalSignMisurazioniDetailSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);
	
	sp.Execute("IDVITALSIGN", pOV, &pOV->m_sVitalSignId, pNV, &pNV->m_sVitalSignId);
	sp.Execute("IDHEADER", pOV, &pOV->m_lIDHeader, pNV, &pNV->m_lIDHeader);
	sp.Execute("ORA", pOV, &pOV->m_sOra, pNV, &pNV->m_sOra);
	sp.Execute("FC", pOV, &pOV->m_sFC, pNV, &pNV->m_sFC);
	sp.Execute("PA", pOV, &pOV->m_sPA, pNV, &pNV->m_sPA);
	sp.Execute("SAT", pOV, &pOV->m_sSat, pNV, &pNV->m_sSat);
	sp.Execute("NOTE", pOV, &pOV->m_sNote, pNV, &pNV->m_sNote);	
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CVitalSignMisurazioniDetailSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CVitalSignMisurazioniHeaderSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CVitalSignMisurazioniHeaderSet::DeleteRecordset");
	}
	return bReturn;
}

CString CVitalSignMisurazioniDetailSet::SetBaseFilter(const CString &strFilter)
{
	CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	if (strNewFilter.IsEmpty() == TRUE)
	{
		strNewFilter = "ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("ELIMINATO") == -1)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}