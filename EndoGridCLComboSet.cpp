#include "stdafx.h"
#include "EndoGridCLComboSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEndoGridCLComboSet, CBaseSet)

CEndoGridCLComboSet::CEndoGridCLComboSet(void)
: CBaseSet(&m_lId, "ID")
{	

	m_lId = 0;
	m_lIdparametro = 0;
	m_sDescrizione = "";
	m_bEliminato = FALSE;

	SetBaseFilter("");

	m_nFields = 4;
}

CEndoGridCLComboSet::~CEndoGridCLComboSet(void)
{
}

void CEndoGridCLComboSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, "ID", m_lId);
	RFX_Long(pFX, "IDPARAMETRO", m_lIdparametro);
	RFX_Text(pFX, "DESCRIZIONE", m_sDescrizione);
	RFX_Bool(pFX, "ELIMINATO", m_bEliminato);
}

CString CEndoGridCLComboSet::GetDefaultSQL()
{
	return _T("GRIDCL_COMBO");
}

BOOL CEndoGridCLComboSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CEndoGridCLVersionSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CEndoGridCLVersionSet::DeleteRecordset");
	}
	return bReturn;
}

CString CEndoGridCLComboSet::SetBaseFilter(const CString &strFilter)
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

BOOL CEndoGridCLComboSet::UpdateRecordset(const CString &strCommento)
{
	return CBaseSet::UpdateRecordset(strCommento);
}

CBaseSet* CEndoGridCLComboSet::CreateNew()
{
	return (CBaseSet*)new CEndoGridCLComboSet;
}

void CEndoGridCLComboSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEndoGridCLComboSet* pSet = (CEndoGridCLComboSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIdparametro) || bCopyAll)
		m_lIdparametro = pSet->m_lIdparametro;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CEndoGridCLComboSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEndoGridCLComboSet* pOV = (CEndoGridCLComboSet*)pOldValues;
	CEndoGridCLComboSet* pNV = (CEndoGridCLComboSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDPARAMETRO", pOV, &pOV->m_lIdparametro, pNV, &pNV->m_lIdparametro);
	sp.Execute("DESCRIZIONE", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}