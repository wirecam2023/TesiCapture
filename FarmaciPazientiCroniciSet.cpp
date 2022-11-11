#include "stdafx.h"
#include "Endox.h"
#include "FarmaciPazientiCroniciSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CFarmaciPazientiCroniciSet, CBaseSet)

CFarmaciPazientiCroniciSet::CFarmaciPazientiCroniciSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

CString CFarmaciPazientiCroniciSet::GetDefaultSQL()
{
	return "FarmaciPazientiCronici";
}

void CFarmaciPazientiCroniciSet::SetEmpty()
{
	m_lID = 0;
	m_sDescrizione = "";
	m_lUO = 0;
	m_bEliminato = FALSE;
}

void CFarmaciPazientiCroniciSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CFarmaciPazientiCroniciSet::CreateNew()
{
	return (CBaseSet*)new CFarmaciPazientiCroniciSet;
}

void CFarmaciPazientiCroniciSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CFarmaciPazientiCroniciSet* pSet = (CFarmaciPazientiCroniciSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CFarmaciPazientiCroniciSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CFarmaciPazientiCroniciSet* pOV = (CFarmaciPazientiCroniciSet*)pOldValues;
	CFarmaciPazientiCroniciSet* pNV = (CFarmaciPazientiCroniciSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CFarmaciPazientiCroniciSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CFarmaciPazientiCroniciSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CFarmaciPazientiCroniciSet::DeleteRecordset");
	}
	return bReturn;
}

CString CFarmaciPazientiCroniciSet::SetBaseFilter(const CString &strFilter)
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
		
BOOL CFarmaciPazientiCroniciSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

void CFarmaciPazientiCroniciSet::Add(CString sDescrizione)
{
	if (OpenRecordset("CFarmaciPazientiCroniciSet::Add"))
	{
		if (AddNewRecordset("CFarmaciPazientiCroniciSet::Add"))
		{
		    m_sDescrizione = sDescrizione;
			UpdateRecordset("CFarmaciPazientiCroniciSet::Add");
		}

		CloseRecordset("CFarmaciPazientiCroniciSet::Add");
	}
}

void CFarmaciPazientiCroniciSet::Edt(long lID, CString sDescrizione)
{
	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CFarmaciPazientiCroniciSet::Edt"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CFarmaciPazientiCroniciSet::Edt"))
			{
				m_sDescrizione = sDescrizione;
				UpdateRecordset("CFarmaciPazientiCroniciSet::Edt");
			}
		}

		CloseRecordset("CFarmaciPazientiCroniciSet::Edt");
	}
}

void CFarmaciPazientiCroniciSet::Del(long lID)
{
	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CFarmaciPazientiCroniciSet::Del"))
	{
		if (!IsEOF())
			DeleteRecordset("CFarmaciPazientiCroniciSet::Del");

		CloseRecordset("CFarmaciPazientiCroniciSet::Del");
	}
}

CString CFarmaciPazientiCroniciSet::GetDescrizione(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
	SetOpenFilter(strFilter);
	if (OpenRecordset("CFarmaciPazientiCroniciSet::GetDescrizione"))
	{
		if (!IsEOF())
			sReturn = m_sDescrizione;

		CloseRecordset("CFarmaciPazientiCroniciSet::GetDescrizione");
	}

	return sReturn;
}