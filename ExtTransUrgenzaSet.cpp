#include "stdafx.h"
#include "Endox.h"
#include "ExtTransUrgenzaSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CExtTransUrgenzaSet, CAMBaseSet)

CExtTransUrgenzaSet::CExtTransUrgenzaSet()
: CBaseSet(&m_lId, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

CString CExtTransUrgenzaSet::GetDefaultSQL()
{
	return "EXT_TRANSURGENZA";
}

void CExtTransUrgenzaSet::DoFieldExchange(CFieldExchange* pFX)
{
	CAMBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "id", m_lId);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "codiceintegrazione", m_sCodiceIntegrazione, 50);
		RFX_Long(pFX, "LivelloUrgenza", m_lLivelloUrgenza);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CExtTransUrgenzaSet::SetEmpty()
{
	m_lId = 0;
	m_sCodiceIntegrazione = "";
	m_lLivelloUrgenza = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CExtTransUrgenzaSet::CreateNew()
{
	return (CBaseSet*)new CExtTransUrgenzaSet;
}

void CExtTransUrgenzaSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CExtTransUrgenzaSet* pSet = (CExtTransUrgenzaSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodiceIntegrazione) || bCopyAll)
		m_sCodiceIntegrazione = pSet->m_sCodiceIntegrazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lLivelloUrgenza) || bCopyAll)
		m_lLivelloUrgenza = pSet->m_lLivelloUrgenza;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CExtTransUrgenzaSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CExtTransUrgenzaSet* pOV = (CExtTransUrgenzaSet*)pOldValues;
	CExtTransUrgenzaSet* pNV = (CExtTransUrgenzaSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("codiceIntegrazione", pOV, &pOV->m_sCodiceIntegrazione, pNV, &pNV->m_sCodiceIntegrazione);
	sp.Execute("livelloUrgenza", pOV, &pOV->m_lLivelloUrgenza, pNV, &pNV->m_lLivelloUrgenza);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CExtTransUrgenzaSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CExtTransUrgenzaSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CExtTransUrgenzaSet::DeleteRecordset");
	}
	return bReturn;
}

CString CExtTransUrgenzaSet::SetBaseFilter(const CString &strFilter)
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

BOOL CExtTransUrgenzaSet::UpdateRecordset(const CString &strCommento)
{
	return CBaseSet::UpdateRecordset(strCommento);
}

long CExtTransUrgenzaSet::GetPriorityFromCode(CString code)
{
	long lReturn = 0;

	CString strFilter = "";
	strFilter.Format("codiceIntegrazione='%s'", code);
	SetOpenFilter(strFilter);

	if (OpenRecordset("CExtTransUrgenzaSet::GetPriorityFromCode"))
	{
		if (!IsEOF())
			lReturn = m_lLivelloUrgenza;

		CloseRecordset("CExtTransUrgenzaSet::GetPriorityFromCode");
	}

	return lReturn;
}