#include "stdafx.h"
#include "Endox.h"
#include "EsamiImmaginiAudiologia.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEsamiImmaginiAudiologia, CBaseSet)

CEsamiImmaginiAudiologia::CEsamiImmaginiAudiologia()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 5;

}

CString CEsamiImmaginiAudiologia::GetDefaultSQL()
{
	return "ESAMI_IMMAGINIAUDIOLOGIA";
}

void CEsamiImmaginiAudiologia::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_lIDImmagine = 0;
	m_sTipo = "";
	m_bEliminato = FALSE;
}

void CEsamiImmaginiAudiologia::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDEsame", m_lIDEsame);
		RFX_Long(pFX, "IDImmagine", m_lIDImmagine);
		RFX_Text(pFX, "Tipo", m_sTipo, 50);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CEsamiImmaginiAudiologia::CreateNew()
{
	return (CBaseSet*)new CEsamiImmaginiAudiologia();
}

void CEsamiImmaginiAudiologia::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEsamiImmaginiAudiologia* pSet = (CEsamiImmaginiAudiologia*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pSet->m_lIDEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDImmagine) || bCopyAll)
		m_lIDImmagine = pSet->m_lIDImmagine;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTipo) || bCopyAll)
		m_sTipo = pSet->m_sTipo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CEsamiImmaginiAudiologia::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEsamiImmaginiAudiologia* pOV = (CEsamiImmaginiAudiologia*)pOldValues;
	CEsamiImmaginiAudiologia* pNV = (CEsamiImmaginiAudiologia*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDEsame", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("IDImmagine", pOV, &pOV->m_lIDImmagine, pNV, &pNV->m_lIDImmagine);
	sp.Execute("Tipo", pOV, &pOV->m_sTipo, pNV, &pNV->m_sTipo);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CEsamiImmaginiAudiologia::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CEsamiImmaginiAudiologia::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CEsamiImmaginiAudiologia::DeleteRecordset");
	}
	return bReturn;
}

CString CEsamiImmaginiAudiologia::SetBaseFilter(const CString &strFilter)
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