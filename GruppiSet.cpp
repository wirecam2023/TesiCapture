#include "stdafx.h"
#include "Endox.h"
#include "GruppiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGruppiSet, CBaseSet)

CGruppiSet::CGruppiSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

CString CGruppiSet::GetDefaultSQL()
{
	return "GRUPPI";
}

void CGruppiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Nome", m_sNome, 50);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CGruppiSet::SetEmpty()
{
	m_lID = 0;
	m_sNome = "";
	m_lUO = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CGruppiSet::CreateNew()
{
	return (CBaseSet*)new CGruppiSet;
}

void CGruppiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CGruppiSet* pSet = (CGruppiSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNome) || bCopyAll)
		m_sNome = pSet->m_sNome;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CGruppiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CGruppiSet* pOV = (CGruppiSet*)pOldValues;
	CGruppiSet* pNV = (CGruppiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Nome", pOV, &pOV->m_sNome, pNV, &pNV->m_sNome);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CGruppiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CGruppiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CGruppiSet::DeleteRecordset");
	}
	return bReturn;
}

CString CGruppiSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	/*strNewFilter.MakeUpper();

	if (strNewFilter.IsEmpty())
	{
		strNewFilter = "ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("ELIMINATO") == -1)
			strNewFilter += " AND ELIMINATO=0";
	}*/

	return CBaseSet::SetBaseFilter(strNewFilter);
}

long CGruppiSet::GetUO(long lID)
{
	long lReturn = 0;

	CString sFilter;
	sFilter.Format("ID=%li", lID);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CGruppiSet::GetUO"))
	{
		if (!IsEOF())
			lReturn = m_lUO;
		
		CloseRecordset("CGruppiSet::GetUO");
	}

	return lReturn;
}

void CGruppiSet::SetUO(long lID, long lUO)
{
	CString sFilter;
	sFilter.Format("ID=%li", lID);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CGruppiSet::SetUO"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CGruppiSet::SetUO"))
			{
				m_lUO = lUO;
				UpdateRecordset("CGruppiSet::SetUO");
			}
		}
		
		CloseRecordset("CGruppiSet::SetUO");
	}
}

CString CGruppiSet::GetDescrizione(long lID)
{
	CString sReturn = "";

	CString sFilter;
	sFilter.Format("ID=%li", lID);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CGruppiSet::GetDescrizione"))
	{
		if (!IsEOF())
			sReturn = m_sNome;

		CloseRecordset("CGruppiSet::GetDescrizione");
	}

	return sReturn;
}

long CGruppiSet::GetIDFromNome(CString sNome)
{
	long lReturn = 0;

	CString sFilter;
	sFilter.Format("NOME='%s'", sNome);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CGruppiSet::GetIDFromNome"))
	{
		if (!IsEOF())
			lReturn = m_lID;

		CloseRecordset("CGruppiSet::GetIDFromNome");
	}

	return lReturn;
}

long CGruppiSet::GetUOFromNome(CString sNome)
{
	long lReturn = 0;

	CString sFilter;
	sFilter.Format("NOME='%s'", sNome);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CGruppiSet::GetUOFromNome"))
	{
		if (!IsEOF())
			lReturn = m_lUO;

		CloseRecordset("CGruppiSet::GetUOFromNome");
	}

	return lReturn;
}