#include "stdafx.h"
#include "Endox.h"
#include "TutorialFilesSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CTutorialFilesSet, CBaseSet)

CTutorialFilesSet::CTutorialFilesSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();
	
	m_nFields = 4;
}

CString CTutorialFilesSet::GetDefaultSQL()
{
	return "TutorialFiles";
}

void CTutorialFilesSet::SetEmpty()
{
	m_lID = 0;
	m_sDescrizione = "";
	m_sIndirizzoCompleto = "";
	m_bEliminato = FALSE;
}

void CTutorialFilesSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		RFX_Text(pFX, "IndirizzoCompleto", m_sIndirizzoCompleto, 255);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CTutorialFilesSet::CreateNew()
{
	return (CBaseSet*)new CTutorialFilesSet;
}

void CTutorialFilesSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CTutorialFilesSet* pSet = (CTutorialFilesSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sIndirizzoCompleto) || bCopyAll)
		m_sIndirizzoCompleto = pSet->m_sIndirizzoCompleto;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CTutorialFilesSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CTutorialFilesSet* pOV = (CTutorialFilesSet*)pOldValues;
	CTutorialFilesSet* pNV = (CTutorialFilesSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("IndirizzoCompleto", pOV, &pOV->m_sIndirizzoCompleto, pNV, &pNV->m_sIndirizzoCompleto);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CTutorialFilesSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CTutorialFilesSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CTutorialFilesSet::DeleteRecordset");
	}
	return bReturn;
}

CString CTutorialFilesSet::SetBaseFilter(const CString &strFilter)
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
		
long CTutorialFilesSet::Add(CString sDescrizione, CString sIndirizzo)
{
	long lReturn = 0;

	if (OpenRecordset("CTutorialFilesSet::Add"))
	{
		if (AddNewRecordset("CTutorialFilesSet::Add"))
		{
			m_sDescrizione = sDescrizione;
			m_sIndirizzoCompleto = sIndirizzo;

			if (UpdateRecordset("CTutorialFilesSet::Add"))
				lReturn = GetLastAdd();
		}

		CloseRecordset("CTutorialFilesSet::Add");
	}

	return lReturn;
}

void CTutorialFilesSet::Edt(long lID, CString sDescrizione, CString sIndirizzo)
{
	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CTutorialFilesSet::Edt"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CTutorialFilesSet::Edt"))
			{
				m_sDescrizione = sDescrizione;
				m_sIndirizzoCompleto = sIndirizzo;
				UpdateRecordset("CTutorialFilesSet::Edt");
			}
		}

		CloseRecordset("CComboRAOSet::EdtPrestazione");
	}
}

BOOL CTutorialFilesSet::Del(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CTutorialFilesSet::Del"))
	{
		if (!IsEOF())
			bReturn = DeleteRecordset("CTutorialFilesSet::Del");

		CloseRecordset("CTutorialFilesSet::Del");
	}

	return bReturn;
}

CString CTutorialFilesSet::GetIndirizzoCompleto(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CTutorialFilesSet::GetIndirizzoCompleto"))
	{
		if (!IsEOF())
			sReturn = m_sIndirizzoCompleto;

		CloseRecordset("CTutorialFilesSet::GetIndirizzoCompleto");
	}

	return sReturn;
}
