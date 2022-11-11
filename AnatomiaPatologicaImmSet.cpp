#include "stdafx.h"
#include "Endox.h"
#include "AnatomiaPatologicaImmSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CAnatomiaPatologicaImmSet, CBaseSet)

CAnatomiaPatologicaImmSet::CAnatomiaPatologicaImmSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

CString CAnatomiaPatologicaImmSet::GetDefaultSQL()
{
	return "AnatomiaPatologicaImm";
}

void CAnatomiaPatologicaImmSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_sPercorso = "";
	m_bEliminato = FALSE;
}

void CAnatomiaPatologicaImmSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDEsame", m_lIDEsame);
		RFX_Text(pFX, "Percorso", m_sPercorso, 255);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CAnatomiaPatologicaImmSet::CreateNew()
{
	return (CBaseSet*)new CAnatomiaPatologicaImmSet;
}

void CAnatomiaPatologicaImmSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CAnatomiaPatologicaImmSet* pSet = (CAnatomiaPatologicaImmSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pSet->m_lIDEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sPercorso) || bCopyAll)
		m_sPercorso = pSet->m_sPercorso;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CAnatomiaPatologicaImmSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CAnatomiaPatologicaImmSet* pOV = (CAnatomiaPatologicaImmSet*)pOldValues;
	CAnatomiaPatologicaImmSet* pNV = (CAnatomiaPatologicaImmSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDEsame", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("Percorso", pOV, &pOV->m_sPercorso, pNV, &pNV->m_sPercorso);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CAnatomiaPatologicaImmSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CAnatomiaPatologicaImmSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CAnatomiaPatologicaImmSet::DeleteRecordset");
	}
	return bReturn;
}

CString CAnatomiaPatologicaImmSet::SetBaseFilter(const CString &strFilter)
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