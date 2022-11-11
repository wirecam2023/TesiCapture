#include "stdafx.h"
#include "Endox.h"
#include "DynVersioneSet.h"

#include "CustomDate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CDynVersioneSet, CBaseSet)

CDynVersioneSet::CDynVersioneSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 5;
}

CDynVersioneSet::~CDynVersioneSet(void)
{
}

CString CDynVersioneSet::GetDefaultSQL()
{
	return "DYNVERSIONE";
}

void CDynVersioneSet::SetEmpty()
{
	m_lID = 0;
	m_lDataOra = 0;
	m_lIDTipoEsame = 0;
	m_lUO = 0;
	m_bEliminato = FALSE;
}

void CDynVersioneSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "DataOra", m_lDataOra);
		RFX_Long(pFX, "IDTipoEsame", m_lIDTipoEsame);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CDynVersioneSet::CreateNew()
{
	return (CBaseSet*)new CDynVersioneSet;
}

void CDynVersioneSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CDynVersioneSet* pSet = (CDynVersioneSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lDataOra) || bCopyAll)
		m_lDataOra = pSet->m_lDataOra;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDTipoEsame) || bCopyAll)
		m_lIDTipoEsame = pSet->m_lIDTipoEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CDynVersioneSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CDynVersioneSet* pOV = (CDynVersioneSet*)pOldValues;
	CDynVersioneSet* pNV = (CDynVersioneSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("DataOra", pOV, &pOV->m_lDataOra, pNV, &pNV->m_lDataOra);
	sp.Execute("IDTipoEsame", pOV, &pOV->m_lIDTipoEsame, pNV, &pNV->m_lIDTipoEsame);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}


BOOL CDynVersioneSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CDynVersioneSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CDynVersioneSet::DeleteRecordset");
	}
	return bReturn;
}

CString CDynVersioneSet::SetBaseFilter(const CString &strFilter)
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
		
BOOL CDynVersioneSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
	{
		m_lDataOra = CCustomDate(TRUE, TRUE).GetDate();
		m_lUO = theApp.m_lUO;
	}

	return CBaseSet::UpdateRecordset(strCommento);
}
