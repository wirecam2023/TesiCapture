#include "stdafx.h"
#include "Endox.h"
#include "TerapieSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CTerapieSet, CBaseSet)

CTerapieSet::CTerapieSet()
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 8;
}

CString CTerapieSet::GetDefaultSQL()
{
	return "ETERAPIE";
}

void CTerapieSet::SetEmpty()
{
	m_lContatore = 0;
	m_lEsame = 0;
	m_sTerapia = "";
	m_lDurata = 0;
	m_sDurata = "";
	m_lDose = 0;
	m_sDose = "";
	m_bEliminato = FALSE;
}

void CTerapieSet::CopyFieldFrom(CTerapieSet* pSet)
{
	SetEmpty();

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lContatore))
		m_lContatore	= pSet->m_lContatore;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lEsame))
		m_lEsame	= pSet->m_lEsame;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTerapia))
		m_sTerapia = pSet->m_sTerapia.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDurata))
		m_lDurata = pSet->m_lDurata;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sDurata))
		m_sDurata = pSet->m_sDurata;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDose))
		m_lDose = pSet->m_lDose;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sDose))
		m_sDose = pSet->m_sDose.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bEliminato))
		m_bEliminato = pSet->m_bEliminato;

	if (IsOpen())
	{
		SetFieldNull (NULL, FALSE);
		SetFieldDirty(NULL, TRUE);
	}
}

void CTerapieSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long (pFX, "Contatore",		m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Long (pFX, "Esame",			m_lEsame);
		RFX_Text (pFX, "Terapia",		m_sTerapia, 3999);
		RFX_Long (pFX, "Durata",		m_lDurata);
		RFX_Text (pFX, "DurataTesto",	m_sDurata, 3999);
		RFX_Long (pFX, "Dose",			m_lDose);
		RFX_Text (pFX, "DoseTesto",		m_sDose, 3999);
		RFX_Bool (pFX, "Eliminato",     m_bEliminato);
	}
}

CBaseSet* CTerapieSet::CreateNew()
{
	return (CBaseSet*)new CTerapieSet;
}

void CTerapieSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CTerapieSet* pTerapieSet = (CTerapieSet*)pOriginalSet;

	if (!pTerapieSet->IsOpen() || pTerapieSet->IsFieldDirty(&pTerapieSet->m_lEsame) || bCopyAll)
		m_lEsame = pTerapieSet->m_lEsame;
	if (!pTerapieSet->IsOpen() || pTerapieSet->IsFieldDirty(&pTerapieSet->m_sTerapia) || bCopyAll)
		m_sTerapia = pTerapieSet->m_sTerapia;
	if (!pTerapieSet->IsOpen() || pTerapieSet->IsFieldDirty(&pTerapieSet->m_lDurata) || bCopyAll)
		m_lDurata = pTerapieSet->m_lDurata;
	if (!pTerapieSet->IsOpen() || pTerapieSet->IsFieldDirty(&pTerapieSet->m_sDurata) || bCopyAll)
		m_sDurata = pTerapieSet->m_sDurata;
	if (!pTerapieSet->IsOpen() || pTerapieSet->IsFieldDirty(&pTerapieSet->m_lDose) || bCopyAll)
		m_lDose = pTerapieSet->m_lDose;
	if (!pTerapieSet->IsOpen() || pTerapieSet->IsFieldDirty(&pTerapieSet->m_sDose) || bCopyAll)
		m_sDose = pTerapieSet->m_sDose;
	if (!pTerapieSet->IsOpen() || pTerapieSet->IsFieldDirty(&pTerapieSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pTerapieSet->m_bEliminato;
}

void CTerapieSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CTerapieSet* pOV = (CTerapieSet*)pOldValues;
	CTerapieSet* pNV = (CTerapieSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Esame", pOV, &pOV->m_lEsame, pNV, &pNV->m_lEsame);
	sp.Execute("Terapia", pOV, &pOV->m_sTerapia, pNV, &pNV->m_sTerapia);
	sp.Execute("Durata", pOV, &pOV->m_lDurata, pNV, &pNV->m_lDurata);
	sp.Execute("DurataTesto", pOV, &pOV->m_sDurata, pNV, &pNV->m_sDurata);
	sp.Execute("Dose", pOV, &pOV->m_lDose, pNV, &pNV->m_lDose);
	sp.Execute("DoseTesto", pOV, &pOV->m_sDose, pNV, &pNV->m_sDose);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}


BOOL CTerapieSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CTerapieSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CTerapieSet::DeleteRecordset");
	}
	return bReturn;
}

CString CTerapieSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	if (strNewFilter.IsEmpty())
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