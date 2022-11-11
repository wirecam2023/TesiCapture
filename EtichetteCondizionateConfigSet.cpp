#include "stdafx.h"
#include "Endox.h"
#include "EtichetteCondizionateConfigSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEtichetteCondizionateConfigSet, CBaseSet)

CEtichetteCondizionateConfigSet::CEtichetteCondizionateConfigSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 7;
}

CString CEtichetteCondizionateConfigSet::GetDefaultSQL()
{
	return "ETICHETTECONDCONFIG";
}

void CEtichetteCondizionateConfigSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDCAMPOCONDIZIONATO", m_lIDCampoCondizionato);
		RFX_Long(pFX, "IDSCELTA", m_lIDScelta);
		RFX_Long(pFX, "IDRISULTATO", m_lIDRisultato);
		RFX_Text(pFX, "RISULTATOTXT", m_sRisultatoTxt, 4000);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "ELIMINATO", m_bEliminato);
	}
}

void CEtichetteCondizionateConfigSet::SetEmpty()
{
	m_lID = 0;
	m_lIDCampoCondizionato = 0;
	m_lIDScelta = 0;
	m_lIDRisultato = 0;
	m_sRisultatoTxt = "";
	m_lUO = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CEtichetteCondizionateConfigSet::CreateNew()
{
	return (CBaseSet*)new CEtichetteCondizionateConfigSet;
}

void CEtichetteCondizionateConfigSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEtichetteCondizionateConfigSet* pSet = (CEtichetteCondizionateConfigSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDCampoCondizionato) || bCopyAll)
		m_lIDCampoCondizionato = pSet->m_lIDCampoCondizionato;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDScelta) || bCopyAll)
		m_lIDScelta = pSet->m_lIDScelta;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDRisultato) || bCopyAll)
		m_lIDRisultato = pSet->m_lIDRisultato;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sRisultatoTxt) || bCopyAll)
		m_sRisultatoTxt = pSet->m_sRisultatoTxt;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CEtichetteCondizionateConfigSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEtichetteCondizionateConfigSet* pOV = (CEtichetteCondizionateConfigSet*)pOldValues;
	CEtichetteCondizionateConfigSet* pNV = (CEtichetteCondizionateConfigSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDCAMPOCONDIZIONATO", pOV, &pOV->m_lIDCampoCondizionato, pNV, &pNV->m_lIDCampoCondizionato);
	sp.Execute("IDSCELTA", pOV, &pOV->m_lIDScelta, pNV, &pNV->m_lIDScelta);
	sp.Execute("IDRISULTATO", pOV, &pOV->m_lIDRisultato, pNV, &pNV->m_lIDRisultato);
	sp.Execute("RISULTATOTXT", pOV, &pOV->m_sRisultatoTxt, pNV, &pNV->m_sRisultatoTxt);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CEtichetteCondizionateConfigSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CEtichetteCondizionateConfigSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CEtichetteCondizionateConfigSet::DeleteRecordset");
	}
	return bReturn;
}

CString CEtichetteCondizionateConfigSet::SetBaseFilter(const CString &strFilter)
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

BOOL CEtichetteCondizionateConfigSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

