#include "stdafx.h"
#include "Endox.h"
#include "EsamiCodiciClassDiagnostSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEsamiCodiciClassDiagnostSet, CBaseSet)

CEsamiCodiciClassDiagnostSet::CEsamiCodiciClassDiagnostSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

CString CEsamiCodiciClassDiagnostSet::GetDefaultSQL()
{
	return "ESAMICODICICLASSDIAGNOST";
}

void CEsamiCodiciClassDiagnostSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_lIDCodiciClassificazioneDiag = 0;
	m_bEliminato = FALSE;
}

void CEsamiCodiciClassDiagnostSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDESAME", m_lIDEsame);
		RFX_Long(pFX, "IDCODICICLASSIFICAZIONEDIAG", m_lIDCodiciClassificazioneDiag);
		RFX_Bool(pFX, "ELIMINATO", m_bEliminato);
	}
}

CBaseSet* CEsamiCodiciClassDiagnostSet::CreateNew()
{
	return (CBaseSet*)new CEsamiCodiciClassDiagnostSet;
}

void CEsamiCodiciClassDiagnostSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEsamiCodiciClassDiagnostSet* pEsamiAccessoriSet = (CEsamiCodiciClassDiagnostSet*)pOriginalSet;

	if (!pEsamiAccessoriSet->IsOpen() || pEsamiAccessoriSet->IsFieldDirty(&pEsamiAccessoriSet->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pEsamiAccessoriSet->m_lIDEsame;
	if (!pEsamiAccessoriSet->IsOpen() || pEsamiAccessoriSet->IsFieldDirty(&pEsamiAccessoriSet->m_lIDCodiciClassificazioneDiag) || bCopyAll)
		m_lIDCodiciClassificazioneDiag = pEsamiAccessoriSet->m_lIDCodiciClassificazioneDiag;
	if (!pEsamiAccessoriSet->IsOpen() || pEsamiAccessoriSet->IsFieldDirty(&pEsamiAccessoriSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pEsamiAccessoriSet->m_bEliminato;
}

void CEsamiCodiciClassDiagnostSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEsamiCodiciClassDiagnostSet* pOV = (CEsamiCodiciClassDiagnostSet*)pOldValues;
	CEsamiCodiciClassDiagnostSet* pNV = (CEsamiCodiciClassDiagnostSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDESAME", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("IDCODICICLASSIFICAZIONEGIAG", pOV, &pOV->m_lIDCodiciClassificazioneDiag, pNV, &pNV->m_lIDCodiciClassificazioneDiag);
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CEsamiCodiciClassDiagnostSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CEsamiCodiciClassDiagnostSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CEsamiCodiciClassDiagnostSet::DeleteRecordset");
	}
	return bReturn;
}

CString CEsamiCodiciClassDiagnostSet::SetBaseFilter(const CString &strFilter)
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

void CEsamiCodiciClassDiagnostSet::AddRecord(long lIDEsame, long lIDCodiciClassificazioneDiag)
{
	CString sFilter;
	sFilter.Format("IDESAME=%li AND IDCODICICLASSIFICAZIONEDIAG=%li", lIDEsame, lIDCodiciClassificazioneDiag);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CEsamiCodiciClassDiagnostSet::AddRecord"))
	{
		if (IsEOF())
		{
			if (AddNewRecordset("CEsamiCodiciClassDiagnostSet::AddRecord"))
			{
				m_lIDEsame = lIDEsame;
				m_lIDCodiciClassificazioneDiag = lIDCodiciClassificazioneDiag;

				UpdateRecordset("CEsamiCodiciClassDiagnostSet::AddRecord");
			}
		}

		CloseRecordset("CEsamiCodiciClassDiagnostSet::AddRecord");
	}
}

void CEsamiCodiciClassDiagnostSet::DelRecord(long lIDEsame, long lIDCodiciClassificazioneDiag)
{
	CString sFilter;
	sFilter.Format("IDESAME=%li AND IDCODICICLASSIFICAZIONEDIAG=%li", lIDEsame, lIDCodiciClassificazioneDiag);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CEsamiCodiciClassDiagnostSet::DelRecord"))
	{
		if (!IsEOF())
			DeleteRecordset("CEsamiCodiciClassDiagnostSet::DelRecord");

		CloseRecordset("CEsamiCodiciClassDiagnostSet::DelRecord");
	}
}
