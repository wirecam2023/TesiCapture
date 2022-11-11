#include "stdafx.h"
#include "Endox.h"
#include "InterventiEndoscopiciSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CInterventiEndoscopiciSet, CBaseSet)

CInterventiEndoscopiciSet::CInterventiEndoscopiciSet()
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

CString CInterventiEndoscopiciSet::GetDefaultSQL()
{
	return "EINTERVENTIENDOSCOPICI";
}

void CInterventiEndoscopiciSet::SetEmpty()
{
	m_lContatore			= 0;
	m_lEsame				= 0;
	m_lClasse				= 0;
	m_sIntervento			= "";
	m_lIDEsameRiferimento	= 0;
	m_bEliminato			= FALSE;
}

void CInterventiEndoscopiciSet::CopyFieldFrom(CInterventiEndoscopiciSet* pSet)
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
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDEsameRiferimento))
		m_lIDEsameRiferimento = pSet->m_lIDEsameRiferimento;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bEliminato))
		m_bEliminato = pSet->m_bEliminato;

	if (IsOpen())
	{
		SetFieldNull (NULL, FALSE);
		SetFieldDirty(NULL, TRUE);
	}
}

void CInterventiEndoscopiciSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Contatore", m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "Esame",				m_lEsame);
		RFX_Long(pFX, "Classe",				m_lClasse);
		RFX_Text(pFX, "Intervento",			m_sIntervento,	3999);
		RFX_Long(pFX, "IDEsameRiferimento", m_lIDEsameRiferimento);
		RFX_Bool(pFX, "Eliminato",			m_bEliminato);
	}
}

CBaseSet* CInterventiEndoscopiciSet::CreateNew()
{
	return (CBaseSet*)new CInterventiEndoscopiciSet;
}

void CInterventiEndoscopiciSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CInterventiEndoscopiciSet* pSet = (CInterventiEndoscopiciSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lEsame) || bCopyAll)
		m_lEsame = pSet->m_lEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lClasse) || bCopyAll)
		m_lClasse = pSet->m_lClasse;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sIntervento) || bCopyAll)
		m_sIntervento = pSet->m_sIntervento;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEsameRiferimento) || bCopyAll)
		m_lIDEsameRiferimento = pSet->m_lIDEsameRiferimento;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CInterventiEndoscopiciSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CInterventiEndoscopiciSet* pOV = (CInterventiEndoscopiciSet*)pOldValues;
	CInterventiEndoscopiciSet* pNV = (CInterventiEndoscopiciSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Esame", pOV, &pOV->m_lEsame, pNV, &pNV->m_lEsame);
	sp.Execute("Classe", pOV, &pOV->m_lClasse, pNV, &pNV->m_lClasse);
	sp.Execute("Intervento", pOV, &pOV->m_sIntervento, pNV, &pNV->m_sIntervento);
	sp.Execute("IDEsameRiferimento", pOV, &pOV->m_lIDEsameRiferimento, pNV, &pNV->m_lIDEsameRiferimento);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CInterventiEndoscopiciSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CInterventiEndoscopiciSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CInterventiEndoscopiciSet::DeleteRecordset");
	}
	return bReturn;
}

CString CInterventiEndoscopiciSet::SetBaseFilter(const CString &strFilter)
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