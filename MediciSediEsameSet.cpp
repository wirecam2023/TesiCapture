#include "stdafx.h"
#include "Endox.h"
#include "MediciSediEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMediciSediEsameSet, CBaseSet)

CMediciSediEsameSet::CMediciSediEsameSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

void CMediciSediEsameSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDMedico", m_lIDMedico);
		RFX_Long(pFX, "IDSede", m_lIDSede);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CString CMediciSediEsameSet::GetDefaultSQL()
{
	return "EMediciSediEsame";
}

void CMediciSediEsameSet::SetEmpty()
{
	m_lID = 0;
	m_lIDMedico = 0;
	m_lIDSede = 0;
	m_bEliminato = FALSE;
}

//
CBaseSet* CMediciSediEsameSet::CreateNew()
{
	return (CBaseSet*)new CMediciSediEsameSet;
}

void CMediciSediEsameSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CMediciSediEsameSet* pSet = (CMediciSediEsameSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDMedico) || bCopyAll)
		m_lIDMedico = pSet->m_lIDMedico;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDSede) || bCopyAll)
		m_lIDSede = pSet->m_lIDSede;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CMediciSediEsameSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CMediciSediEsameSet* pOV = (CMediciSediEsameSet*)pOldValues;
	CMediciSediEsameSet* pNV = (CMediciSediEsameSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDMedico", pOV, &pOV->m_lIDMedico, pNV, &pNV->m_lIDMedico);
	sp.Execute("IDSede", pOV, &pOV->m_lIDSede, pNV, &pNV->m_lIDSede);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CMediciSediEsameSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CMediciSediEsameSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CMediciSediEsameSet::DeleteRecordset");
	}
	return bReturn;
}

CString CMediciSediEsameSet::SetBaseFilter(const CString &strFilter)
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

void CMediciSediEsameSet::AddRow(long lIDMedico, long lIDSede)
{
	CString sFilter;
	sFilter.Format("IDMedico=%li AND IDSede=%li", lIDMedico, lIDSede);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CMediciSediEsameSet::AddRow"))
	{
		if (IsEOF())
		{
			if (AddNewRecordset("CMediciSediEsameSet::AddRow"))
			{
				m_lIDMedico = lIDMedico;
				m_lIDSede = lIDSede;
				UpdateRecordset("CMediciSediEsameSet::AddRow");
			}
		}

		CloseRecordset("CMediciSediEsameSet::AddRow");
	}
}

void CMediciSediEsameSet::DelRow(long lIDMedico, long lIDSede)
{
	CString sFilter;
	sFilter.Format("IDMedico=%li AND IDSede=%li", lIDMedico, lIDSede);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CMediciSediEsameSet::DelRow"))
	{
		if (!IsEOF())
			DeleteRecordset("CMediciSediEsameSet::DelRow");

		CloseRecordset("CMediciSediEsameSet::DelRow");
	}
}