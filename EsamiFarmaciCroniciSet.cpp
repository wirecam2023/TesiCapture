#include "stdafx.h"
#include "Endox.h"
#include "EsamiFarmaciCroniciSet.h"

#include "CronicitaPazienteDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEsamiFarmaciCroniciSet, CBaseSet)

CEsamiFarmaciCroniciSet::CEsamiFarmaciCroniciSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 5;
}

CString CEsamiFarmaciCroniciSet::GetDefaultSQL()
{
	return "EEsamiFarmaciCronici";
}

void CEsamiFarmaciCroniciSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_lIDFarmaco = 0;
	m_lFase = 0;
	m_bEliminato = FALSE;
}

void CEsamiFarmaciCroniciSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long (pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDEsame", m_lIDEsame);
		RFX_Long(pFX, "IDFarmaco", m_lIDFarmaco);
		RFX_Long(pFX, "Fase", m_lFase);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CEsamiFarmaciCroniciSet::CreateNew()
{
	return (CBaseSet*)new CEsamiFarmaciCroniciSet;
}

void CEsamiFarmaciCroniciSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEsamiFarmaciCroniciSet* pSet = (CEsamiFarmaciCroniciSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pSet->m_lIDEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDFarmaco) || bCopyAll)
		m_lIDFarmaco = pSet->m_lIDFarmaco;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lFase) || bCopyAll)
		m_lFase = pSet->m_lFase;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CEsamiFarmaciCroniciSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEsamiFarmaciCroniciSet* pOV = (CEsamiFarmaciCroniciSet*)pOldValues;
	CEsamiFarmaciCroniciSet* pNV = (CEsamiFarmaciCroniciSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDEsame", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("IDFarmaco", pOV, &pOV->m_lIDFarmaco, pNV, &pNV->m_lIDFarmaco);
	sp.Execute("Fase", pOV, &pOV->m_lFase, pNV, &pNV->m_lFase);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CEsamiFarmaciCroniciSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CEsamiFarmaciCroniciSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CEsamiFarmaciCroniciSet::DeleteRecordset");
	}
	return bReturn;
}

CString CEsamiFarmaciCroniciSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	if (strNewFilter.IsEmpty() == TRUE)
	{
		strNewFilter = "ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("ELIMINATO") == -1)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}

void CEsamiFarmaciCroniciSet::AddRow(long lIDEsame, long lIDFarmaco, long lFase)
{
	SetOpenFilter("ID=0");
	if (OpenRecordset("CEsamiFarmaciCroniciSet::AddRow"))
	{
		if (AddNewRecordset("CEsamiFarmaciCroniciSet::AddRow"))
		{
			m_lIDEsame = lIDEsame;
			m_lIDFarmaco = lIDFarmaco;
			m_lFase = lFase;

			UpdateRecordset("CEsamiFarmaciCroniciSet::AddRow");
		}

		CloseRecordset("CEsamiFarmaciCroniciSet::AddRow");
	}
}

void CEsamiFarmaciCroniciSet::CloneAllRows(long lIDEsameOld, long lIDEsameNew)
{
	CString sFilter;
	sFilter.Format("IDEsame=%li", lIDEsameOld);
	SetOpenFilter(sFilter);

	if (OpenRecordset("CEsamiFarmaciCroniciSet::CloneAllRows"))
	{
		while(!IsEOF())
		{
			if ((m_lFase == FARMACO_INIZIO) || (m_lFase == FARMACO_CONTINUA))
				CEsamiFarmaciCroniciSet().AddRow(lIDEsameNew, m_lIDFarmaco, FARMACO_CONTINUA);

			MoveNext();
		}

		CloseRecordset("CEsamiFarmaciCroniciSet::CloneAllRows");
	}
}

void CEsamiFarmaciCroniciSet::DelAllRows(long lIDEsame)
{
	CString sFilter;
	sFilter.Format("IDEsame=%li", lIDEsame);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CEsamiFarmaciCroniciSet::DelAllRows"))
	{
		while(!IsEOF())
		{
			DeleteRecordset("CEsamiFarmaciCroniciSet::DelAllRows");
			MoveNext();
		}

		CloseRecordset("CEsamiFarmaciCroniciSet::DelAllRows");
	}
}

long CEsamiFarmaciCroniciSet::GetFase(long lIDEsame, long lIDFarmaco)
{
	long lReturn = FARMACO_NIENTE;

	if (lIDEsame > 0)
	{
		CString sFilter;
		sFilter.Format("IDEsame=%li AND IDFarmaco=%li", lIDEsame, lIDFarmaco);

		SetOpenFilter(sFilter);
		if (OpenRecordset("CEsamiFarmaciCroniciSet::GetFase"))
		{
			if (!IsEOF())
				lReturn = m_lFase;

			CloseRecordset("CEsamiFarmaciCroniciSet::GetFase");
		}
	}

	return lReturn;
}
