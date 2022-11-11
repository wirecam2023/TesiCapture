#include "stdafx.h"
#include "Endox.h"
#include "FrasiNewSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CFrasiNewSet, CBaseSet)

CFrasiNewSet::CFrasiNewSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 7;
}

void CFrasiNewSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "PrePost", m_lPrePost);
		RFX_Long(pFX, "Padre", m_lPadre);
		RFX_Text(pFX, "Titolo", m_sTitolo, 255);
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 3999);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CString CFrasiNewSet::GetDefaultSQL()
{
	return "EFRASINEW";
}

void CFrasiNewSet::SetEmpty()
{
	m_lID = 0;
	m_lPrePost = 0;
	m_lPadre = 0;
	m_sTitolo = "";
	m_sDescrizione = "";
	m_lUO = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CFrasiNewSet::CreateNew()
{
	return (CBaseSet*)new CFrasiNewSet;
}

void CFrasiNewSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CFrasiNewSet* pSet = (CFrasiNewSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lPrePost) || bCopyAll)
		m_lPrePost = pSet->m_lPrePost;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lPadre) || bCopyAll)
		m_lPadre = pSet->m_lPadre;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTitolo) || bCopyAll)
		m_sTitolo = pSet->m_sTitolo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CFrasiNewSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CFrasiNewSet* pOV = (CFrasiNewSet*)pOldValues;
	CFrasiNewSet* pNV = (CFrasiNewSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("PrePost", pOV, &pOV->m_lPrePost, pNV, &pNV->m_lPrePost);
	sp.Execute("Padre", pOV, &pOV->m_lPadre, pNV, &pNV->m_lPadre);
	sp.Execute("Titolo", pOV, &pOV->m_sTitolo, pNV, &pNV->m_sTitolo);
	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CFrasiNewSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CFrasiNewSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CFrasiNewSet::DeleteRecordset");
	}
	return bReturn;
}

CString CFrasiNewSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	CString strUO;
	strUO.Format("UO=%li", theApp.m_lUO);
	if (strNewFilter.IsEmpty())
	{
		strNewFilter = strUO + " AND ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("UO=") < 0)
			strNewFilter += " AND " + strUO;

		if (strNewFilter.Find("ELIMINATO=") < 0)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}
		
BOOL CFrasiNewSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}
