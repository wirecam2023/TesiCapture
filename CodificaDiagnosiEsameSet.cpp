#include "stdafx.h"
#include "Endox.h"
#include "CodificaDiagnosiEsameSet.h"

#include "MstOrganoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCodificaDiagnosiEsameSet, CBaseSet)

CCodificaDiagnosiEsameSet::CCodificaDiagnosiEsameSet()
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

CString CCodificaDiagnosiEsameSet::GetDefaultSQL()
{
	return "CodificaDiagnosiEsame";
}

void CCodificaDiagnosiEsameSet::SetEmpty()
{
	m_lContatore = 0;
	m_lEsame = 0;
	m_lOrgano = -1;
	m_sSede = "";
	m_sDiagnosiEsame = "";
	m_bEliminato = FALSE;
}

void CCodificaDiagnosiEsameSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long (pFX, "Contatore",		m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Long (pFX, "Esame",			m_lEsame);
		RFX_Long (pFX, "Organo",		m_lOrgano);
		RFX_Text (pFX, "Sede",			m_sSede,		   255);
		RFX_Text (pFX, "DiagnosiEsame",	m_sDiagnosiEsame, 3999);
		RFX_Bool (pFX, "Eliminato",     m_bEliminato);
	}
}

void CCodificaDiagnosiEsameSet::CopyFieldFrom(CCodificaDiagnosiEsameSet* pSet)
{
	SetEmpty();

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lContatore))
		m_lContatore = pSet->m_lContatore;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lEsame))
		m_lEsame = pSet->m_lEsame;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lOrgano))
		m_lOrgano = pSet->m_lOrgano;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sSede))
		m_sSede = pSet->m_sSede.Left(255);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sDiagnosiEsame))
		m_sDiagnosiEsame = pSet->m_sDiagnosiEsame.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bEliminato))
		m_bEliminato = pSet->m_bEliminato;
	
	if (IsOpen())
	{
		SetFieldNull (NULL, FALSE);
		SetFieldDirty(NULL, TRUE);
	}
}

CString CCodificaDiagnosiEsameSet::GetStringForQuery(long lIDEsame)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Esame=%li", lIDEsame);

	SetOpenFilter(strFilter);
	SetSortRecord("Contatore");

	if (OpenRecordset("CCodificaDiagnosiEsameSet::GetStringForQuery"))
	{
		if (!IsEOF())
		{
			CMstOrganoSet setOrgani;

			strReturn = "\r\n\r\n" + theApp.GetMessageString(IDS_QUERYDLG_EXAM_42);

			while(!IsEOF())
			{
				strReturn += "\r\n- " + setOrgani.GetFieldText(m_lOrgano) + " (" + m_sSede + ") --> " + m_sDiagnosiEsame;

				MoveNext();
			}
		}

		CloseRecordset("CCodificaDiagnosiEsameSet::GetStringForQuery");
	}

	return strReturn;
}

CBaseSet* CCodificaDiagnosiEsameSet::CreateNew()
{
	return (CBaseSet*)new CCodificaDiagnosiEsameSet;
}

void CCodificaDiagnosiEsameSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CCodificaDiagnosiEsameSet* pCodificaDiagnosiEsameSet = (CCodificaDiagnosiEsameSet*)pOriginalSet;

	if (!pCodificaDiagnosiEsameSet->IsOpen() || pCodificaDiagnosiEsameSet->IsFieldDirty(&pCodificaDiagnosiEsameSet->m_lEsame) || bCopyAll)
		m_lEsame = pCodificaDiagnosiEsameSet->m_lEsame;
	if (!pCodificaDiagnosiEsameSet->IsOpen() || pCodificaDiagnosiEsameSet->IsFieldDirty(&pCodificaDiagnosiEsameSet->m_lOrgano) || bCopyAll)
		m_lOrgano = pCodificaDiagnosiEsameSet->m_lOrgano;
	if (!pCodificaDiagnosiEsameSet->IsOpen() || pCodificaDiagnosiEsameSet->IsFieldDirty(&pCodificaDiagnosiEsameSet->m_sSede) || bCopyAll)
		m_sSede = pCodificaDiagnosiEsameSet->m_sSede;
	if (!pCodificaDiagnosiEsameSet->IsOpen() || pCodificaDiagnosiEsameSet->IsFieldDirty(&pCodificaDiagnosiEsameSet->m_sDiagnosiEsame) || bCopyAll)
		m_sDiagnosiEsame = pCodificaDiagnosiEsameSet->m_sDiagnosiEsame;
	if (!pCodificaDiagnosiEsameSet->IsOpen() || pCodificaDiagnosiEsameSet->IsFieldDirty(&pCodificaDiagnosiEsameSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pCodificaDiagnosiEsameSet->m_bEliminato;
}

void CCodificaDiagnosiEsameSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CCodificaDiagnosiEsameSet* pOV = (CCodificaDiagnosiEsameSet*)pOldValues;
	CCodificaDiagnosiEsameSet* pNV = (CCodificaDiagnosiEsameSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Esame", pOV, &pOV->m_lEsame, pNV, &pNV->m_lEsame);
	sp.Execute("Organo", pOV, &pOV->m_lOrgano, pNV, &pNV->m_lOrgano);
	sp.Execute("Sede", pOV, &pOV->m_sSede, pNV, &pNV->m_sSede);
	sp.Execute("DiagnosiEsame", pOV, &pOV->m_sDiagnosiEsame, pNV, &pNV->m_sDiagnosiEsame);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CCodificaDiagnosiEsameSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CCodificaDiagnosiEsameSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CCodificaDiagnosiEsameSet::DeleteRecordset");
	}
	return bReturn;
}

CString CCodificaDiagnosiEsameSet::SetBaseFilter(const CString &strFilter)
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

CString CCodificaDiagnosiEsameSet::GetCodificaDiagnosiEsame(long lIDEsame)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Esame=%li", lIDEsame);

	SetBaseFilter(strFilter);
	SetSortRecord("Contatore");

	if (OpenRecordset("CCodificaDiagnosiEsameSet::GetCodificaDiagnosiEsame"))
	{
		while(!IsEOF())
		{
			if (!strReturn.IsEmpty())
				strReturn += " \n";

			strReturn += CMstOrganoSet().GetFieldText(m_lOrgano);

			if (!m_sSede.IsEmpty())
				strReturn += (" " + m_sSede);

			if (!m_sDiagnosiEsame.IsEmpty())
				strReturn += (": " + m_sDiagnosiEsame);

			MoveNext();
		}

		CloseRecordset("CCodificaDiagnosiEsameSet::GetCodificaDiagnosiEsame");
	}

	return strReturn;
}
