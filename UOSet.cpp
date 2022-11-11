#include "stdafx.h"
#include "Endox.h"
#include "UOSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CUOSet, CBaseSet)

CUOSet::CUOSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

CString CUOSet::GetDefaultSQL()
{
	return "UO";
}

void CUOSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		RFX_Text(pFX, "CodiceIntegrazione", m_sCodiceIntegrazione, 50);
		RFX_Text(pFX, "UsernameResponsabile", m_sUsernameResponsabile, 50);
		RFX_Bool(pFX, "FastFichaWorklist", m_bFastFichaWorklist);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CUOSet::SetEmpty()
{
	m_lID = 0;
	m_sDescrizione = "";
	m_sCodiceIntegrazione = "";
	m_sUsernameResponsabile = "";
	m_bFastFichaWorklist = FALSE;
	m_bEliminato = FALSE;
}

CBaseSet* CUOSet::CreateNew()
{
	return (CBaseSet*)new CUOSet;
}

void CUOSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CUOSet* pSet = (CUOSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodiceIntegrazione) || bCopyAll)
		m_sCodiceIntegrazione = pSet->m_sCodiceIntegrazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sUsernameResponsabile) || bCopyAll)
		m_sUsernameResponsabile = pSet->m_sUsernameResponsabile;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bFastFichaWorklist) || bCopyAll)
		m_bFastFichaWorklist = pSet->m_bFastFichaWorklist;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CUOSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CUOSet* pOV = (CUOSet*)pOldValues;
	CUOSet* pNV = (CUOSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("CodiceIntegrazione", pOV, &pOV->m_sCodiceIntegrazione, pNV, &pNV->m_sCodiceIntegrazione);
	sp.Execute("UsernameResponsabile", pOV, &pOV->m_sUsernameResponsabile, pNV, &pNV->m_sUsernameResponsabile);
	sp.Execute("FastFichaWorklist", pOV, &pOV->m_bFastFichaWorklist, pNV, &pNV->m_bFastFichaWorklist);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CUOSet::ExistMoreThanOneUO()
{
	BOOL bReturn = FALSE;

	if (OpenRecordset("CUOSet::ExistMoreThanOneUO"))
	{
		long lRows = 0;

		while (!IsEOF())
		{
			lRows++;

			if (lRows > 1)
			{
				bReturn = TRUE;
				break;
			}

			MoveNext();
		}

		CloseRecordset("CUOSet::ExistMoreThanOneUO");
	}

	return bReturn;
}

CString CUOSet::GetCodiceIntegrazione(long lID, BOOL bForQuery)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);
	SetOpenFilter(strFilter);
	if (OpenRecordset("CUOSet::GetCodiceIntegrazione"))
	{
		if (!IsEOF())
		{
			sReturn = m_sCodiceIntegrazione;
			sReturn.Trim();

			if (bForQuery)
				sReturn.Replace("'", "''");
		}

		CloseRecordset("CUOSet::GetCodiceIntegrazione");
	}

	return sReturn;
}

CString CUOSet::GetUsernameResponsabile(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);
	SetOpenFilter(strFilter);
	if (OpenRecordset("CUOSet::GetUsernameResponsabile"))
	{
		if (!IsEOF())
			sReturn = m_sUsernameResponsabile;

		CloseRecordset("CUOSet::GetUsernameResponsabile");
	}

	return sReturn;
}

BOOL CUOSet::GetFastFichaWorklist(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);
	SetOpenFilter(strFilter);
	if (OpenRecordset("CUOSet::GetUsernameResponsabile"))
	{
		if (!IsEOF())
			bReturn = m_bFastFichaWorklist;

		CloseRecordset("CUOSet::GetUsernameResponsabile");
	}

	return bReturn;
}

CString CUOSet::GetDescrizione(long lID)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("ID=%li", lID);
	SetOpenFilter(strFilter);
	if (OpenRecordset("CUOSet::GetDescrizione"))
	{
		if (!IsEOF())
			sReturn = m_sDescrizione;

		CloseRecordset("CUOSet::GetDescrizione");
	}

	return sReturn;
}

long CUOSet::GetIDFromDescrizione(CString sDescrizione)
{
	long lReturn = 0;

	sDescrizione.Trim();
	if (!sDescrizione.IsEmpty())
	{
		sDescrizione.Replace("'", "''");

		CString sFilter;
		sFilter.Format("DESCRIZIONE='%s'", sDescrizione);

		SetOpenFilter(sFilter);
		if (OpenRecordset("CUOSet::GetIDFromDescrizione"))
		{
			if (!IsEOF())
				lReturn = m_lID;

			CloseRecordset("CUOSet::GetIDFromDescrizione");
		}
	}

	return lReturn;
}

long CUOSet::GetUOFromCodiceIntegrazione(CString sCodiceIntegrazione)
{
	long lReturn = 0;

	sCodiceIntegrazione.Trim();
	sCodiceIntegrazione.Replace("'", "''");

	if (!sCodiceIntegrazione.IsEmpty())
	{
		CString sFilter;
		sFilter.Format("CODICEINTEGRAZIONE = '%s'", sCodiceIntegrazione);

		SetOpenFilter(sFilter);
		if (OpenRecordset("CUOSet::GetUOFromCodiceIntegrazione"))
		{
			if (!IsEOF())
				lReturn = m_lID;

			CloseRecordset("CUOSet::GetUOFromCodiceIntegrazione");
		}
	}

	return lReturn;
}

BOOL CUOSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CUOSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CUOSet::DeleteRecordset");
	}
	return bReturn;
}

CString CUOSet::SetBaseFilter(const CString &strFilter)
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

void CUOSet::VerificaUODefault()
{
	if (OpenRecordset("CUOSet::VerificaUODefault"))
	{
		if (IsEOF())
		{
			if (AddNewRecordset("CUOSet::VerificaUODefault"))
			{
				m_sDescrizione = "DEFAULT";

				UpdateRecordset("CUOSet::VerificaUODefault");
			}
		}

		CloseRecordset("CUOSet::VerificaUODefault");
	}
}
