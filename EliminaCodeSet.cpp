#include "stdafx.h"
#include "Endox.h"
#include "EliminaCodeSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEliminaCodeSet, CBaseSet)

CEliminaCodeSet::CEliminaCodeSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 11;
}

CEliminaCodeSet::~CEliminaCodeSet(void)
{
}

CString CEliminaCodeSet::GetDefaultSQL()
{
	return "EliminaCode";
}

void CEliminaCodeSet::SetEmpty()
{
	m_lID = 0;
	m_sData = "";
	m_sSala = "";
	m_sCodice = "";
	m_lColoreBackR = 0;
	m_lColoreBackG = 0;
	m_lColoreBackB = 0;
	m_lColoreForeR = 255;
	m_lColoreForeG = 255;
	m_lColoreForeB = 255;
	m_bEliminato = FALSE;
}

void CEliminaCodeSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Data", m_sData, 8);
		RFX_Text(pFX, "Sala", m_sSala, 50);
		RFX_Text(pFX, "Codice", m_sCodice, 50);
		RFX_Long(pFX, "ColoreBackR", m_lColoreBackR);
		RFX_Long(pFX, "ColoreBackG", m_lColoreBackG);
		RFX_Long(pFX, "ColoreBackB", m_lColoreBackB);
		RFX_Long(pFX, "ColoreForeR", m_lColoreForeR);
		RFX_Long(pFX, "ColoreForeG", m_lColoreForeG);
		RFX_Long(pFX, "ColoreForeB", m_lColoreForeB);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CEliminaCodeSet::CreateNew()
{
	return (CBaseSet*)new CEliminaCodeSet;
}

void CEliminaCodeSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEliminaCodeSet* pSet = (CEliminaCodeSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sData) || bCopyAll)
		m_sData = pSet->m_sData;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sSala) || bCopyAll)
		m_sSala = pSet->m_sSala;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodice) || bCopyAll)
		m_sCodice = pSet->m_sCodice;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lColoreBackR) || bCopyAll)
		m_lColoreBackR = pSet->m_lColoreBackR;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lColoreBackG) || bCopyAll)
		m_lColoreBackG = pSet->m_lColoreBackG;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lColoreBackB) || bCopyAll)
		m_lColoreBackB = pSet->m_lColoreBackB;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lColoreForeR) || bCopyAll)
		m_lColoreForeR = pSet->m_lColoreForeR;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lColoreForeG) || bCopyAll)
		m_lColoreForeG = pSet->m_lColoreForeG;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lColoreForeB) || bCopyAll)
		m_lColoreForeB = pSet->m_lColoreForeB;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CEliminaCodeSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEliminaCodeSet* pOV = (CEliminaCodeSet*)pOldValues;
	CEliminaCodeSet* pNV = (CEliminaCodeSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Data", pOV, &pOV->m_sData, pNV, &pNV->m_sData);
	sp.Execute("Sala", pOV, &pOV->m_sSala, pNV, &pNV->m_sSala);
	sp.Execute("Codice", pOV, &pOV->m_sCodice, pNV, &pNV->m_sCodice);
	sp.Execute("ColoreBackR", pOV, &pOV->m_lColoreBackR, pNV, &pNV->m_lColoreBackR);
	sp.Execute("ColoreBackG", pOV, &pOV->m_lColoreBackG, pNV, &pNV->m_lColoreBackG);
	sp.Execute("ColoreBackB", pOV, &pOV->m_lColoreBackB, pNV, &pNV->m_lColoreBackB);
	sp.Execute("ColoreForeR", pOV, &pOV->m_lColoreForeR, pNV, &pNV->m_lColoreForeR);
	sp.Execute("ColoreForeG", pOV, &pOV->m_lColoreForeG, pNV, &pNV->m_lColoreForeG);
	sp.Execute("ColoreForeB", pOV, &pOV->m_lColoreForeB, pNV, &pNV->m_lColoreForeB);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CEliminaCodeSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CEliminaCodeSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CEliminaCodeSet::DeleteRecordset");
	}
	return bReturn;
}

CString CEliminaCodeSet::SetBaseFilter(const CString &strFilter)
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
		
/* BOOL CEliminaCodeSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
} */
