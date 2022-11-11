#include "stdafx.h"
#include "Endox.h"
#include "EtichetteSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEtichetteSet, CBaseSet)

CEtichetteSet::CEtichetteSet()
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 7;
}

CString CEtichetteSet::GetDefaultSQL()
{
	return "EETICHETTE";
}

void CEtichetteSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "CONTATORE", m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "TIPO", m_sTipo, 255);
		RFX_Long(pFX, "INDICE", m_lIndice);
		RFX_Text(pFX, "LABEL", m_sLabel, 3999);
		RFX_Long(pFX, "IDCAMPORELAZIONATO", m_lIdCampoRelazionato);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "ELIMINATO", m_bEliminato);
	}
}

void CEtichetteSet::SetEmpty()
{
	m_lContatore = 0;
	m_lIndice = 0;
	m_sTipo = "";
	m_sLabel = "";
	m_lIdCampoRelazionato = 0;
	m_lUO = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CEtichetteSet::CreateNew()
{
	return (CBaseSet*)new CEtichetteSet;
}

void CEtichetteSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEtichetteSet* pSet = (CEtichetteSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIndice) || bCopyAll)
		m_lIndice = pSet->m_lIndice;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTipo) || bCopyAll)
		m_sTipo = pSet->m_sTipo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sLabel) || bCopyAll)
		m_sLabel = pSet->m_sLabel;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIdCampoRelazionato) || bCopyAll)
		m_lIdCampoRelazionato = pSet->m_lIdCampoRelazionato;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CEtichetteSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEtichetteSet* pOV = (CEtichetteSet*)pOldValues;
	CEtichetteSet* pNV = (CEtichetteSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("TIPO", pOV, &pOV->m_sTipo, pNV, &pNV->m_sTipo);
	sp.Execute("INDICE", pOV, &pOV->m_lIndice, pNV, &pNV->m_lIndice);
	sp.Execute("LABEL", pOV, &pOV->m_sLabel, pNV, &pNV->m_sLabel);
	sp.Execute("IDCAMPORELAZIONATO", pOV, &pOV->m_lIdCampoRelazionato, pNV, &pNV->m_lIdCampoRelazionato);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CEtichetteSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CEtichetteSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CEtichetteSet::DeleteRecordset");
	}
	return bReturn;
}

CString CEtichetteSet::SetBaseFilter(const CString &strFilter)
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
		
BOOL CEtichetteSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

CString CEtichetteSet::GetLabel(CString tipo, int indice)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("tipo='%s' and indice=%li", tipo, indice);
	SetOpenFilter(strFilter);

	if (OpenRecordset("CEtichetteSet::GetLabel"))
	{
		if (!IsEOF())
			sReturn = m_sLabel;

		CloseRecordset("CEtichetteSet::GetLabel");
	}

	if (sReturn == "")
		sReturn.Format("%s_%li", tipo, indice);

	return sReturn;
}

long CEtichetteSet::GetId(CString tipo, int indice)
{
	long lReturn = 0;

	CString strFilter;
	strFilter.Format("tipo='%s' and indice=%li", tipo, indice);
	SetOpenFilter(strFilter);

	if (OpenRecordset("CEtichetteSet::GetLabel"))
	{
		if (!IsEOF())
			lReturn = m_lContatore;

		CloseRecordset("CEtichetteSet::GetLabel");
	}	

	return lReturn;
}