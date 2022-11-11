#include "stdafx.h"
#include "Endox.h"
#include "InviantiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CInviantiSet, CBaseSet)

CInviantiSet::CInviantiSet(CString strTable)
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 9;

	m_strTable = strTable;
}

CString CInviantiSet::GetDefaultSQL()
{
	CString strTmp = m_strTable;

	strTmp.MakeUpper();

	return strTmp;
}

void CInviantiSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Contatore", m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 50);
		RFX_Text(pFX, "Telefono", m_sTelefono, 50);
		RFX_Text(pFX, "Fax", m_sFax, 50);
		RFX_Text(pFX, "Email", m_sEmail, 50);
		RFX_Long(pFX, "IdCentroDiCosto", m_lIdCentroDiCosto);
		RFX_Text(pFX, "CodiceIntegrazione", m_sCodiceIntegrazione, 50);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CInviantiSet::SetEmpty()
{
	m_lContatore = 0;
	m_sDescrizione = "";
	m_sTelefono = "";
	m_sFax = "";
	m_sEmail = "";
	m_lIdCentroDiCosto = 0;
	m_sCodiceIntegrazione = "";
	m_lUO = 0;
	m_bEliminato = FALSE;
}

CString CInviantiSet::GetFieldText(long lContatore)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Contatore=%li", lContatore);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CInviantiSet::GetFieldText"))
	{
		if (!IsEOF())
			strReturn = m_sDescrizione;

		CloseRecordset("CInviantiSet::GetFieldText");
	}

	return strReturn;
}

CBaseSet* CInviantiSet::CreateNew()
{
	return (CBaseSet*)new CInviantiSet;
}

void CInviantiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CInviantiSet* pSet = (CInviantiSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTelefono) || bCopyAll)
		m_sTelefono = pSet->m_sTelefono;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sFax) || bCopyAll)
		m_sFax = pSet->m_sFax;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sEmail) || bCopyAll)
		m_sEmail = pSet->m_sEmail;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIdCentroDiCosto) || bCopyAll)
		m_lIdCentroDiCosto = pSet->m_lIdCentroDiCosto;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodiceIntegrazione) || bCopyAll)
		m_sCodiceIntegrazione = pSet->m_sCodiceIntegrazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CInviantiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CInviantiSet* pOV = (CInviantiSet*)pOldValues;
	CInviantiSet* pNV = (CInviantiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("Telefono", pOV, &pOV->m_sTelefono, pNV, &pNV->m_sTelefono);
	sp.Execute("Fax", pOV, &pOV->m_sFax, pNV, &pNV->m_sFax);
	sp.Execute("Email", pOV, &pOV->m_sEmail, pNV, &pNV->m_sEmail);
	sp.Execute("IdCentroDiCosto", pOV, &pOV->m_lIdCentroDiCosto, pNV, &pNV->m_lIdCentroDiCosto);
	sp.Execute("CodiceIntegrazione", pOV, &pOV->m_sCodiceIntegrazione, pNV, &pNV->m_sCodiceIntegrazione);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CInviantiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CInviantiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CInviantiSet::DeleteRecordset");
	}
	return bReturn;
}

CString CInviantiSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	CString strUO;
	strUO.Format("UO=%li", theApp.m_lUO);
	if (strNewFilter.IsEmpty())
	{
		strNewFilter = strUO + " AND ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("UO=") < 0)
			strNewFilter += " AND " + strUO;

		if (strNewFilter.Find("ELIMINATO=") < 0)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}
		
BOOL CInviantiSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}
