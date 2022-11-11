#include "stdafx.h"
#include "Endox.h"
#include "UOUtenteSet.h"

#include "UOSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CUOUtenteSet, CBaseSet)

CUOUtenteSet::CUOUtenteSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

CString CUOUtenteSet::GetDefaultSQL()
{
	return "UO_Utente";
}

void CUOUtenteSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDUO", m_lIDUO);
		RFX_Long(pFX, "IDUtente", m_lIDUtente);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CUOUtenteSet::SetEmpty()
{
	m_lID = 0;
	m_lIDUO = 0;
	m_lIDUtente = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CUOUtenteSet::CreateNew()
{
	return (CBaseSet*)new CUOUtenteSet;
}

void CUOUtenteSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CUOUtenteSet* pSet = (CUOUtenteSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDUO) || bCopyAll)
		m_lIDUO = pSet->m_lIDUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDUtente) || bCopyAll)
		m_lIDUtente = pSet->m_lIDUtente;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CUOUtenteSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CUOUtenteSet* pOV = (CUOUtenteSet*)pOldValues;
	CUOUtenteSet* pNV = (CUOUtenteSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDUO", pOV, &pOV->m_lIDUO, pNV, &pNV->m_lIDUO);
	sp.Execute("IDUtente", pOV, &pOV->m_lIDUtente, pNV, &pNV->m_lIDUtente);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CUOUtenteSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CUOUtenteSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CUOUtenteSet::DeleteRecordset");
	}
	return bReturn;
}

CString CUOUtenteSet::SetBaseFilter(const CString &strFilter)
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

long CUOUtenteSet::ContaUOUtente(long lIDUtente)
{
	long lReturn = 0;

	CString sFilter;
	sFilter.Format("IDUtente=%li", lIDUtente);

	SetOpenFilter(sFilter);

	if (OpenRecordset("CUOUtenteSet::ContaUOUtente"))
	{
		while (!IsEOF())
		{
			lReturn++;
			MoveNext();
		}

		CloseRecordset("CUOUtenteSet::ContaUOUtente");
	}

	return lReturn;
}

void CUOUtenteSet::VerificaUODefault(long lIDUtente)
{
	CString sFilter;
	sFilter.Format("IDUtente=%li", lIDUtente);

	SetOpenFilter(sFilter);

	if (OpenRecordset("CUOUtenteSet::VerificaUODefault"))
	{
		if (IsEOF())
		{
			CUOSet setTemp;
			if (setTemp.OpenRecordset("CUOUtenteSet::VerificaUODefault"))
			{
				while(!setTemp.IsEOF())
				{
					if (AddNewRecordset("CUOUtenteSet::VerificaUODefault"))
					{
						m_lIDUO = setTemp.m_lID;
						m_lIDUtente = lIDUtente;

						UpdateRecordset("CUOUtenteSet::VerificaUODefault");
					}

					setTemp.MoveNext();
				}

				setTemp.CloseRecordset("CUOUtenteSet::VerificaUODefault");
			}
		}

		CloseRecordset("CUOUtenteSet::VerificaUODefault");
	}
}
