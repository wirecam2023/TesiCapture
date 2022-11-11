#include "stdafx.h"
#include "Endox.h"
#include "MalattieSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMalattieSet, CBaseSet)

CMalattieSet::CMalattieSet()
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

CString CMalattieSet::GetDefaultSQL()
{
	return "EMALATTIE";
}

void CMalattieSet::SetEmpty()
{
	m_lContatore = 0;
	m_lEsame = 0;
	m_sMalattia = "";
	m_lClasse = 0;
	m_lEpisodi = 0;
	m_bEliminato = FALSE;
}

void CMalattieSet::CopyFieldFrom(CMalattieSet* pSet)
{
	SetEmpty();

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lContatore))
		m_lContatore	= pSet->m_lContatore;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lEsame))
		m_lEsame	= pSet->m_lEsame;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sMalattia))
		m_sMalattia = pSet->m_sMalattia.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lClasse))
		m_lClasse = pSet->m_lClasse;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lEpisodi))
		m_lEpisodi = pSet->m_lEpisodi;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bEliminato))
		m_bEliminato = pSet->m_bEliminato;

	if (IsOpen())
	{
		SetFieldNull (NULL, FALSE);
		SetFieldDirty(NULL, TRUE);
	}
}

void CMalattieSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long (pFX, "Contatore", m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Long (pFX, "Esame", m_lEsame);
		RFX_Text (pFX, "Malattia", m_sMalattia, 3999);
		RFX_Long (pFX, "Classe", m_lClasse);
		RFX_Long (pFX, "Episodi", m_lEpisodi);
		RFX_Bool (pFX, "Eliminato", m_bEliminato);
	}
}

void CMalattieSet::GetFieldText(CString& sReturn, long lEsame)
{
	CString strFilter;
	strFilter.Format("Esame=%li", lEsame);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CMalattieSet::GetFieldText"))
	{
		while(!IsEOF())
		{
			if (!sReturn.IsEmpty())
				sReturn += "\n";

			sReturn += m_sMalattia;

			MoveNext();
		}
		CloseRecordset("CMalattieSet::GetFieldText");
	}
}

CBaseSet* CMalattieSet::CreateNew()
{
	return (CBaseSet*)new CMalattieSet;
}

void CMalattieSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CMalattieSet* pMalattieSet = (CMalattieSet*)pOriginalSet;

	if (!pMalattieSet->IsOpen() || pMalattieSet->IsFieldDirty(&pMalattieSet->m_lEsame) || bCopyAll)
		m_lEsame = pMalattieSet->m_lEsame;
	if (!pMalattieSet->IsOpen() || pMalattieSet->IsFieldDirty(&pMalattieSet->m_sMalattia) || bCopyAll)
		m_sMalattia = pMalattieSet->m_sMalattia;
	if (!pMalattieSet->IsOpen() || pMalattieSet->IsFieldDirty(&pMalattieSet->m_lClasse) || bCopyAll)
		m_lClasse = pMalattieSet->m_lClasse;
	if (!pMalattieSet->IsOpen() || pMalattieSet->IsFieldDirty(&pMalattieSet->m_lEpisodi) || bCopyAll)
		m_lEpisodi = pMalattieSet->m_lEpisodi;
	if (!pMalattieSet->IsOpen() || pMalattieSet->IsFieldDirty(&pMalattieSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pMalattieSet->m_bEliminato;
}

void CMalattieSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CMalattieSet* pOV = (CMalattieSet*)pOldValues;
	CMalattieSet* pNV = (CMalattieSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Esame", pOV, &pOV->m_lEsame, pNV, &pNV->m_lEsame);
	sp.Execute("Malattia", pOV, &pOV->m_sMalattia, pNV, &pNV->m_sMalattia);
	sp.Execute("Classe", pOV, &pOV->m_lClasse, pNV, &pNV->m_lClasse);
	sp.Execute("Episodi", pOV, &pOV->m_lEpisodi, pNV, &pNV->m_lEpisodi);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CMalattieSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CMalattieSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CMalattieSet::DeleteRecordset");
	}
	return bReturn;
}

CString CMalattieSet::SetBaseFilter(const CString &strFilter)
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