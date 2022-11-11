#include "stdafx.h"
#include "Endox.h"
#include "TipiEsamiProgressivoAnnualeSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CTipiEsamiProgressivoAnnualeSet, CBaseSet)

CTipiEsamiProgressivoAnnualeSet::CTipiEsamiProgressivoAnnualeSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

CString CTipiEsamiProgressivoAnnualeSet::GetDefaultSQL()
{
	return "TipiEsamiProgressivoAnnuale";
}

void CTipiEsamiProgressivoAnnualeSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDSede", m_lIDSede);
		RFX_Long(pFX, "IDTipoEsame", m_lIDTipoEsame);
		RFX_Long(pFX, "ContatoreAnnuale", m_lContatoreAnnuale);
		RFX_Long(pFX, "Anno", m_lAnno);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CTipiEsamiProgressivoAnnualeSet::SetEmpty()
{
	m_lID = 0;
	m_lIDSede = 0;
	m_lIDTipoEsame = 0;
	m_lContatoreAnnuale = 0;
	m_lAnno = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CTipiEsamiProgressivoAnnualeSet::CreateNew()
{
	return (CBaseSet*)new CTipiEsamiProgressivoAnnualeSet;
}

void CTipiEsamiProgressivoAnnualeSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CTipiEsamiProgressivoAnnualeSet* pSet = (CTipiEsamiProgressivoAnnualeSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDSede) || bCopyAll)
		m_lIDSede = pSet->m_lIDSede;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDTipoEsame) || bCopyAll)
		m_lIDTipoEsame = pSet->m_lIDTipoEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lContatoreAnnuale) || bCopyAll)
		m_lContatoreAnnuale = pSet->m_lContatoreAnnuale;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lAnno) || bCopyAll)
		m_lAnno = pSet->m_lAnno;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CTipiEsamiProgressivoAnnualeSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CTipiEsamiProgressivoAnnualeSet* pOV = (CTipiEsamiProgressivoAnnualeSet*)pOldValues;
	CTipiEsamiProgressivoAnnualeSet* pNV = (CTipiEsamiProgressivoAnnualeSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDSede", pOV, &pOV->m_lIDSede, pNV, &pNV->m_lIDSede);
	sp.Execute("IDTipoEsame", pOV, &pOV->m_lIDTipoEsame, pNV, &pNV->m_lIDTipoEsame);
	sp.Execute("ContatoreAnnuale", pOV, &pOV->m_lContatoreAnnuale, pNV, &pNV->m_lContatoreAnnuale);
	sp.Execute("Anno", pOV, &pOV->m_lAnno, pNV, &pNV->m_lAnno);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CTipiEsamiProgressivoAnnualeSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CTipiEsamiProgressivoAnnualeSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CTipiEsamiProgressivoAnnualeSet::DeleteRecordset");
	}
	return bReturn;
}

CString CTipiEsamiProgressivoAnnualeSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	if (strNewFilter.IsEmpty())
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