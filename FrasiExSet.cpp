#include "stdafx.h"
#include "Endox.h"
#include "FrasiExSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CFrasiExSet, CBaseSet)

CFrasiExSet::CFrasiExSet()
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	m_lContatore = 0;
	m_lTipoEsame = 0;
	m_lFamiglia = 0;
	m_lPadre = 0;
	m_sTitolo = "";
	m_sDescrizione = "";
	m_bEliminato = FALSE;

	m_nFields = 7;
	SetBaseFilter("");
}

void CFrasiExSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Contatore",   m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "TipoEsame",   m_lTipoEsame);
		RFX_Long(pFX, "Famiglia",    m_lFamiglia);
		RFX_Long(pFX, "Padre",       m_lPadre);
		RFX_Text(pFX, "Titolo",      m_sTitolo, 3999);
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 3999);
		RFX_Bool(pFX, "Eliminato",   m_bEliminato);
	}
}

CString CFrasiExSet::GetDefaultSQL()
{
	return "EFRASIEX";
}

void CFrasiExSet::SetEmpty()
{
	m_lContatore = 0;
	m_lTipoEsame = 0;
	m_lFamiglia = 0;
	m_lPadre = 0;
	m_sTitolo = "";
	m_sDescrizione = "";
	m_bEliminato = FALSE;
}

CBaseSet* CFrasiExSet::CreateNew()
{
	return (CBaseSet*)new CFrasiExSet;
}

void CFrasiExSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CFrasiExSet* pFrasiExSet = (CFrasiExSet*)pOriginalSet;

	if (!pFrasiExSet->IsOpen() || pFrasiExSet->IsFieldDirty(&pFrasiExSet->m_lTipoEsame) || bCopyAll)
		m_lTipoEsame = pFrasiExSet->m_lTipoEsame;
	if (!pFrasiExSet->IsOpen() || pFrasiExSet->IsFieldDirty(&pFrasiExSet->m_lFamiglia) || bCopyAll)
		m_lFamiglia = pFrasiExSet->m_lFamiglia;
	if (!pFrasiExSet->IsOpen() || pFrasiExSet->IsFieldDirty(&pFrasiExSet->m_lPadre) || bCopyAll)
		m_lPadre = pFrasiExSet->m_lPadre;
	if (!pFrasiExSet->IsOpen() || pFrasiExSet->IsFieldDirty(&pFrasiExSet->m_sTitolo) || bCopyAll)
		m_sTitolo = pFrasiExSet->m_sTitolo;
	if (!pFrasiExSet->IsOpen() || pFrasiExSet->IsFieldDirty(&pFrasiExSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pFrasiExSet->m_sDescrizione;
	if (!pFrasiExSet->IsOpen() || pFrasiExSet->IsFieldDirty(&pFrasiExSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pFrasiExSet->m_bEliminato;
}

void CFrasiExSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CFrasiExSet* pOV = (CFrasiExSet*)pOldValues;
	CFrasiExSet* pNV = (CFrasiExSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("TipoEsame", pOV, &pOV->m_lTipoEsame, pNV, &pNV->m_lTipoEsame);
	sp.Execute("Famiglia", pOV, &pOV->m_lFamiglia, pNV, &pNV->m_lFamiglia);
	sp.Execute("Padre", pOV, &pOV->m_lPadre, pNV, &pNV->m_lPadre);
	sp.Execute("Titolo", pOV, &pOV->m_sTitolo, pNV, &pNV->m_sTitolo);
	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CFrasiExSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CFrasiExSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CFrasiExSet::DeleteRecordset");
	}
	return bReturn;
}

CString CFrasiExSet::SetBaseFilter(const CString &strFilter)
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