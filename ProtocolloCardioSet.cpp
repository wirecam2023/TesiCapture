#include "stdafx.h"
#include "Endox.h"
#include "ProtocolloCardioSet.h"

#include "ProtocolloColonneSet.h"
#include "ProtocolloValoriDefaultSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CProtocolloCardioSet, CBaseSet)

CProtocolloCardioSet::CProtocolloCardioSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 5;
}

void CProtocolloCardioSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "DESCRIZIONE", m_sDescrizione, 255);
		RFX_Long(pFX, "FASE", m_lFase);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "ELIMINATO", m_bEliminato);
	}
}

CString CProtocolloCardioSet::GetDefaultSQL()
{
	return "PROTOCOLLO_CARDIO";
}

void CProtocolloCardioSet::SetEmpty()
{
	m_lID = 0;
	m_sDescrizione = "";
	m_lFase = 0;
	m_lUO = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CProtocolloCardioSet::CreateNew()
{
	return (CBaseSet*)new CProtocolloCardioSet;
}

void CProtocolloCardioSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CProtocolloCardioSet* pSet = (CProtocolloCardioSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lFase) || bCopyAll)
		m_lFase = pSet->m_lFase;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CProtocolloCardioSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CProtocolloCardioSet* pOV = (CProtocolloCardioSet*)pOldValues;
	CProtocolloCardioSet* pNV = (CProtocolloCardioSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("DESCRIZIONE", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("FASE", pOV, &pOV->m_lFase, pNV, &pNV->m_lFase);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CProtocolloCardioSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CProtocolloCardioSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CProtocolloCardioSet::DeleteRecordset");
	}
	return bReturn;
}

CString CProtocolloCardioSet::SetBaseFilter(const CString &strFilter)
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
		
BOOL CProtocolloCardioSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

long CProtocolloCardioSet::AddRow(CString sDescrizione, long lFase)
{
	long lReturn = 0;

	SetOpenFilter("ID=0");
	if (OpenRecordset("CProtocolloCardioSet::AddRow"))
	{
		if (AddNewRecordset("CProtocolloCardioSet::AddRow"))
		{
			m_sDescrizione = sDescrizione;
			m_lFase = lFase;

			if (UpdateRecordset("CProtocolloCardioSet::AddRow"))
				lReturn = GetLastAdd();
		}

		CloseRecordset("CProtocolloCardioSet::AddRow");
	}

	return lReturn;
}

void CProtocolloCardioSet::EdtRow(long lID, CString sDescrizione)
{
	CString sFilter;
	sFilter.Format("ID=%li", lID);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CProtocolloCardioSet::EdtRow"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CProtocolloCardioSet::EdtRow"))
			{
				m_sDescrizione = sDescrizione;
				UpdateRecordset("CProtocolloCardioSet::EdtRow");
			}
		}

		CloseRecordset("CProtocolloCardioSet::EdtRow");
	}
}

void CProtocolloCardioSet::DelRow(long lID)
{
	CString sFilter;
	sFilter.Format("ID=%li", lID);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CProtocolloCardioSet::DelRow"))
	{
		if (!IsEOF())
		{
			if (DeleteRecordset("CProtocolloCardioSet::DelRow"))
			{
				CProtocolloColonneSet().DelAllProt(lID);
				CProtocolloValoriDefaultSet().DelAllProt(lID);
			}
		}

		CloseRecordset("CProtocolloCardioSet::DelRow");
	}
}

long CProtocolloCardioSet::GetIDFromFase(long lFase)
{
	long lReturn = 0;

	CString sFilter;
	sFilter.Format("FASE=%li", lFase);

	SetOpenFilter(sFilter);
	SetSortRecord("ID DESC");
	if (OpenRecordset("CProtocolloCardioSet::GetIDFromFase"))
	{
		if (!IsEOF())
			lReturn = m_lID;

		CloseRecordset("CProtocolloCardioSet::GetIDFromFase");
	}

	return lReturn;
}

long CProtocolloCardioSet::FleuryTrans(CString sDescrizione)
{
	long lReturn = 0;

	sDescrizione.Trim();
	sDescrizione.Replace("'", "''");

	if (!sDescrizione.IsEmpty())
	{
		CString sFilter;
		sFilter.Format("DESCRIZIONE = '%s' AND FASE = 0", sDescrizione);
		SetOpenFilter(sFilter);
		if (OpenRecordset("CProtocolloCardioSet::FleuryTrans"))
		{
			if (!IsEOF())
				lReturn = m_lID;

			CloseRecordset("CProtocolloCardioSet::FleuryTrans");
		}
	}

	return lReturn;
}