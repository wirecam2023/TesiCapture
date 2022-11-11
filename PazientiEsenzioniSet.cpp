#include "stdafx.h"
#include "Endox.h"
#include "PazientiEsenzioniSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CPazientiEsenzioniSet, CBaseSet)

CPazientiEsenzioniSet::CPazientiEsenzioniSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 5;
}

void CPazientiEsenzioniSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDPaziente", m_lIDPaziente);
		RFX_Long(pFX, "IDEsenzione", m_lIDEsenzione);
		RFX_Text(pFX, "DataScadenza", m_sDataScadenza);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CString CPazientiEsenzioniSet::GetDefaultSQL()
{
	return "EPazientiEsenzioni";
}

void CPazientiEsenzioniSet::SetEmpty()
{
	m_lID = 0;
	m_lIDPaziente = 0;
	m_lIDEsenzione = 0;
	m_sDataScadenza = "";
	m_bEliminato = FALSE;
}

CBaseSet* CPazientiEsenzioniSet::CreateNew()
{
	return (CBaseSet*)new CPazientiEsenzioniSet;
}

void CPazientiEsenzioniSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CPazientiEsenzioniSet* pSet = (CPazientiEsenzioniSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDPaziente) || bCopyAll)
		m_lIDPaziente = pSet->m_lIDPaziente;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEsenzione) || bCopyAll)
		m_lIDEsenzione = pSet->m_lIDEsenzione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDataScadenza) || bCopyAll)
		m_sDataScadenza = pSet->m_sDataScadenza;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CPazientiEsenzioniSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CPazientiEsenzioniSet* pOV = (CPazientiEsenzioniSet*)pOldValues;
	CPazientiEsenzioniSet* pNV = (CPazientiEsenzioniSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDPaziente", pOV, &pOV->m_lIDPaziente, pNV, &pNV->m_lIDPaziente);
	sp.Execute("IDEsenzione", pOV, &pOV->m_lIDEsenzione, pNV, &pNV->m_lIDEsenzione);
	sp.Execute("DataScadenza", pOV, &pOV->m_sDataScadenza, pNV, &pNV->m_sDataScadenza);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CPazientiEsenzioniSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CPazientiEsenzioniSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CPazientiEsenzioniSet::DeleteRecordset");
	}
	return bReturn;
}

CString CPazientiEsenzioniSet::SetBaseFilter(const CString &strFilter)
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

BOOL CPazientiEsenzioniSet::InsertEsenzione(const long idPaziente, const long idEsenzione, const CString dataScadenza)
{
	CString filter;
	filter.Format("idpaziente = %li and idesenzione = %li", idPaziente, idEsenzione);
	SetOpenFilter(filter);

	if (OpenRecordset("CPazientiEsenzioniSet::InsertEsenzione"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CPazientiEsenzioniSet::InsertEsenzione"))
			{
				m_sDataScadenza = dataScadenza;
				UpdateRecordset("CPazientiEsenzioniSet::InsertEsenzione");
			}
		}
		else
		{
			if (AddNewRecordset("CPazientiEsenzioniSet::InsertEsenzione"))
			{
				m_lIDPaziente = idPaziente;
				m_lIDEsenzione = idEsenzione;
				m_sDataScadenza = dataScadenza;
				UpdateRecordset("CPazientiEsenzioniSet::InsertEsenzione");
			}
		}

		CloseRecordset("CPazientiEsenzioniSet::InsertEsenzione");
	}

	return TRUE;
}