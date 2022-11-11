#include "stdafx.h"
#include "Endox.h"
#include "TabellaEsamiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CTabellaEsamiSet, CBaseSet)

CTabellaEsamiSet::CTabellaEsamiSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 5;
}

CString CTabellaEsamiSet::GetDefaultSQL()
{
	return "TabellaEsami";
}

void CTabellaEsamiSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_lIDParametro = 0;
	m_fValore = 0;
	m_bEliminato = FALSE;
}

void CTabellaEsamiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDEsame", m_lIDEsame);
		RFX_Long(pFX, "IDParametro", m_lIDParametro);
		RFX_Single(pFX, "Valore", m_fValore);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CTabellaEsamiSet::CreateNew()
{
	return (CBaseSet*)new CTabellaEsamiSet;
}

void CTabellaEsamiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CTabellaEsamiSet* pSet = (CTabellaEsamiSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pSet->m_lIDEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDParametro) || bCopyAll)
		m_lIDParametro = pSet->m_lIDParametro;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_fValore) || bCopyAll)
		m_fValore = pSet->m_fValore;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

BOOL CTabellaEsamiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CTabellaEsamiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CTabellaEsamiSet::DeleteRecordset");
	}
	return bReturn;
}

CString CTabellaEsamiSet::SetBaseFilter(const CString &strFilter)
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

void CTabellaEsamiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CTabellaEsamiSet* pOV = (CTabellaEsamiSet*)pOldValues;
	CTabellaEsamiSet* pNV = (CTabellaEsamiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDEsame", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("IDParametro", pOV, &pOV->m_lIDParametro, pNV, &pNV->m_lIDParametro);
	sp.Execute("Valore", pOV, &pOV->m_fValore, pNV, &pNV->m_fValore);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

long CTabellaEsamiSet::AddRow(long lIDEsame, long lIDParametro, float fValore)
{
	long lReturn = 0;

	SetOpenFilter("ID = 0");
	if (OpenRecordset("CTabellaEsamiSet::AddRow"))
	{
		if (AddNewRecordset("CTabellaEsamiSet::AddRow"))
		{
			m_lIDEsame = lIDEsame;
			m_lIDParametro = lIDParametro;
			m_fValore = fValore;

			if (UpdateRecordset("CTabellaEsamiSet::AddRow"))
				lReturn = GetLastAdd();
		}

		CloseRecordset("CTabellaEsamiSet::AddRow");
	}

	return lReturn;
}