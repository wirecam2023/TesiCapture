#include "stdafx.h"
#include "Endox.h"
#include "EndoGridCLDatiEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEndoGridCLDatiEsameSet, CBaseSet)

CEndoGridCLDatiEsameSet::CEndoGridCLDatiEsameSet(CDatabase* pDatabase)
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 9;
}

void CEndoGridCLDatiEsameSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_lIDParametro = 0;
	m_bDatoBool = FALSE;
	m_lDatoInt = 0;
	m_fDatoFloat = 0.0;
	m_sDatoStringa = "";
	m_lColore = -1;
	m_bEliminato = FALSE;
}

void CEndoGridCLDatiEsameSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, _T("ID"), m_lID);

	if (m_nFields > 1)
	{
		RFX_Long(pFX, _T("IDESAME"), m_lIDEsame);
		RFX_Long(pFX, _T("IDPARAMETRO"), m_lIDParametro);
		RFX_Bool(pFX, _T("DATOBOOL"), m_bDatoBool);
		RFX_Long(pFX, _T("DATOINT"), m_lDatoInt);
		RFX_Single(pFX, _T("DATOFLOAT"), m_fDatoFloat);
		RFX_Text(pFX, _T("DATOSTRINGA"), m_sDatoStringa, 1024);
		RFX_Long(pFX, _T("COLORE"), m_lColore);
		RFX_Bool(pFX, _T("ELIMINATO"), m_bEliminato);
	}
}

CString CEndoGridCLDatiEsameSet::GetDefaultSQL()
{
	return _T("GRIDCL_DATIESAME");
}

BOOL CEndoGridCLDatiEsameSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CEndoGridCLDatiEsameSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CEndoGridCLDatiEsameSet::DeleteRecordset");
	}
	return bReturn;
}

CString CEndoGridCLDatiEsameSet::SetBaseFilter(const CString &strFilter)
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

BOOL CEndoGridCLDatiEsameSet::UpdateRecordset(const CString &strCommento)
{
	return CBaseSet::UpdateRecordset(strCommento);
}

CBaseSet* CEndoGridCLDatiEsameSet::CreateNew()
{
	return (CBaseSet*)new CEndoGridCLDatiEsameSet;
}

void CEndoGridCLDatiEsameSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEndoGridCLDatiEsameSet* pSet = (CEndoGridCLDatiEsameSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pSet->m_lIDEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDParametro) || bCopyAll)
		m_lIDParametro = pSet->m_lIDParametro;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bDatoBool) || bCopyAll)
		m_bDatoBool = pSet->m_bDatoBool;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lDatoInt) || bCopyAll)
		m_lDatoInt = pSet->m_lDatoInt;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fDatoFloat) || bCopyAll)
		m_fDatoFloat = pSet->m_fDatoFloat;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDatoStringa) || bCopyAll)
		m_sDatoStringa = pSet->m_sDatoStringa;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lColore) || bCopyAll)
		m_lColore = pSet->m_lColore;	
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CEndoGridCLDatiEsameSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEndoGridCLDatiEsameSet* pOV = (CEndoGridCLDatiEsameSet*)pOldValues;
	CEndoGridCLDatiEsameSet* pNV = (CEndoGridCLDatiEsameSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDESAME", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("IDPARAMETRO", pOV, &pOV->m_lIDParametro, pNV, &pNV->m_lIDParametro);
	sp.Execute("DATOBOOL", pOV, &pOV->m_bDatoBool, pNV, &pNV->m_bDatoBool);
	sp.Execute("DATOINT", pOV, &pOV->m_lDatoInt, pNV, &pNV->m_lDatoInt);
	sp.Execute("DATOFLOAT", pOV, &pOV->m_fDatoFloat, pNV, &pNV->m_fDatoFloat);
	sp.Execute("DATOSTRINGA", pOV, &pOV->m_sDatoStringa, pNV, &pNV->m_sDatoStringa);
	sp.Execute("COLORE", pOV, &pOV->m_lColore, pNV, &pNV->m_lColore);
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}