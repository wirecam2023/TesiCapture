#include "stdafx.h"
#include "Endox.h"
#include "DynFormSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CDynFormSet, CBaseSet)

CDynFormSet::CDynFormSet()
	: CBaseSet(&m_lID, "ID")
{
	m_lID = 0;
	m_lIDVersione = 0;
	m_sNome = "";
	m_lOrdine = 0;
	m_lAlbum = 0;
	m_bVisualizzaSempre = TRUE;
	m_bEliminato = FALSE;

	m_nFields = 7;
	SetBaseFilter("");
}

CDynFormSet::~CDynFormSet(void)
{
}

CString CDynFormSet::GetDefaultSQL()
{
	return "DYNFORM";
}

void CDynFormSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDVersione", m_lIDVersione);
		RFX_Text(pFX, "Nome", m_sNome, 255);
		RFX_Long(pFX, "Ordine", m_lOrdine);
		RFX_Long(pFX, "Album", m_lAlbum);
		RFX_Bool(pFX, "VisualizzaSempre", m_bVisualizzaSempre);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CDynFormSet::CreateNew()
{
	return (CBaseSet*)new CDynFormSet;
}

void CDynFormSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CDynFormSet* pDynFormSet = (CDynFormSet*)pOriginalSet;

	if (!pDynFormSet->IsOpen() || pDynFormSet->IsFieldDirty(&pDynFormSet->m_lIDVersione) || bCopyAll)
		m_lIDVersione = pDynFormSet->m_lIDVersione;
	if (!pDynFormSet->IsOpen() || pDynFormSet->IsFieldDirty(&pDynFormSet->m_sNome) || bCopyAll)
		m_sNome = pDynFormSet->m_sNome;
	if (!pDynFormSet->IsOpen() || pDynFormSet->IsFieldDirty(&pDynFormSet->m_lOrdine) || bCopyAll)
		m_lOrdine = pDynFormSet->m_lOrdine;
	if (!pDynFormSet->IsOpen() || pDynFormSet->IsFieldDirty(&pDynFormSet->m_lAlbum) || bCopyAll)
		m_lAlbum = pDynFormSet->m_lAlbum;
	if (!pDynFormSet->IsOpen() || pDynFormSet->IsFieldDirty(&pDynFormSet->m_bVisualizzaSempre) || bCopyAll)
		m_bVisualizzaSempre = pDynFormSet->m_bVisualizzaSempre;
	if (!pDynFormSet->IsOpen() || pDynFormSet->IsFieldDirty(&pDynFormSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pDynFormSet->m_bEliminato;
}

void CDynFormSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CDynFormSet* pOV = (CDynFormSet*)pOldValues;
	CDynFormSet* pNV = (CDynFormSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDVersione", pOV, &pOV->m_lIDVersione, pNV, &pNV->m_lIDVersione);
	sp.Execute("Nome", pOV, &pOV->m_sNome, pNV, &pNV->m_sNome);
	sp.Execute("Ordine", pOV, &pOV->m_lOrdine, pNV, &pNV->m_lOrdine);
	sp.Execute("Album", pOV, &pOV->m_lAlbum, pNV, &pNV->m_lAlbum);
	sp.Execute("VisualizzaSempre", pOV, &pOV->m_bVisualizzaSempre, pNV, &pNV->m_bVisualizzaSempre);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CDynFormSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CDynFormSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CDynFormSet::DeleteRecordset");
	}
	return bReturn;
}

CString CDynFormSet::SetBaseFilter(const CString &strFilter)
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