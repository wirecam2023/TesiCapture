#include "stdafx.h"
#include "Endox.h"
#include "InterventiChirurgiciSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CInterventiChirurgiciSet, CBaseSet)

CInterventiChirurgiciSet::CInterventiChirurgiciSet()
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 5;
}

CString CInterventiChirurgiciSet::GetDefaultSQL()
{
	return "EINTERVENTICHIRURGICI";
}

void CInterventiChirurgiciSet::SetEmpty()
{
	m_lContatore = 0;
	m_lEsame = 0;
	m_lClasse = 0;
	m_sIntervento = "";
	m_bEliminato = FALSE;
}

void CInterventiChirurgiciSet::CopyFieldFrom(CInterventiChirurgiciSet* pSet)
{
	SetEmpty();

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lContatore))
		m_lContatore = pSet->m_lContatore;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lEsame))
		m_lEsame = pSet->m_lEsame;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lClasse))
		m_lClasse = pSet->m_lClasse;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sIntervento))
		m_sIntervento = pSet->m_sIntervento.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bEliminato))
		m_bEliminato = pSet->m_bEliminato;

	if (IsOpen())
	{
		SetFieldNull (NULL, FALSE);
		SetFieldDirty(NULL, TRUE);
	}
}

void CInterventiChirurgiciSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long (pFX, "Contatore", m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Long (pFX, "Esame", m_lEsame);
		RFX_Long (pFX, "Classe", m_lClasse);
		RFX_Text (pFX, "Intervento", m_sIntervento,	3999);
		RFX_Bool (pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CInterventiChirurgiciSet::CreateNew()
{
	return (CBaseSet*)new CInterventiChirurgiciSet;
}

void CInterventiChirurgiciSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CInterventiChirurgiciSet* pInterventiChirurgiciSet = (CInterventiChirurgiciSet*)pOriginalSet;

	if (!pInterventiChirurgiciSet->IsOpen() || pInterventiChirurgiciSet->IsFieldDirty(&pInterventiChirurgiciSet->m_lEsame) || bCopyAll)
		m_lEsame = pInterventiChirurgiciSet->m_lEsame;
	if (!pInterventiChirurgiciSet->IsOpen() || pInterventiChirurgiciSet->IsFieldDirty(&pInterventiChirurgiciSet->m_lClasse) || bCopyAll)
		m_lClasse = pInterventiChirurgiciSet->m_lClasse;
	if (!pInterventiChirurgiciSet->IsOpen() || pInterventiChirurgiciSet->IsFieldDirty(&pInterventiChirurgiciSet->m_sIntervento) || bCopyAll)
		m_sIntervento = pInterventiChirurgiciSet->m_sIntervento;
	if (!pInterventiChirurgiciSet->IsOpen() || pInterventiChirurgiciSet->IsFieldDirty(&pInterventiChirurgiciSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pInterventiChirurgiciSet->m_bEliminato;
}

void CInterventiChirurgiciSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CInterventiChirurgiciSet* pOV = (CInterventiChirurgiciSet*)pOldValues;
	CInterventiChirurgiciSet* pNV = (CInterventiChirurgiciSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Esame", pOV, &pOV->m_lEsame, pNV, &pNV->m_lEsame);
	sp.Execute("Classe", pOV, &pOV->m_lClasse, pNV, &pNV->m_lClasse);
	sp.Execute("Intervento", pOV, &pOV->m_sIntervento, pNV, &pNV->m_sIntervento);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CInterventiChirurgiciSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CInterventiChirurgiciSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CInterventiChirurgiciSet::DeleteRecordset");
	}
	return bReturn;
}

CString CInterventiChirurgiciSet::SetBaseFilter(const CString &strFilter)
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