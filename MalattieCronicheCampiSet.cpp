#include "stdafx.h"
#include "Endox.h"
#include "MalattieCronicheCampiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMalattieCronicheCampiSet, CBaseSet)

CMalattieCronicheCampiSet::CMalattieCronicheCampiSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

CString CMalattieCronicheCampiSet::GetDefaultSQL()
{
	return "MalattieCronicheCampi";
}

void CMalattieCronicheCampiSet::SetEmpty()
{
	m_lID = 0;
	m_lIDMalattia = 0;
	m_lIDCampo = 0;
	m_lTipoCampo = 0;
	m_lOrdine = 0;
	m_bEliminato = FALSE;
}

void CMalattieCronicheCampiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDMalattia", m_lIDMalattia);
		RFX_Long(pFX, "IDCampo", m_lIDCampo);
		RFX_Long(pFX, "TipoCampo", m_lTipoCampo);
		RFX_Long(pFX, "Ordine", m_lOrdine);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CMalattieCronicheCampiSet::CreateNew()
{
	return (CBaseSet*)new CMalattieCronicheCampiSet;
}

void CMalattieCronicheCampiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CMalattieCronicheCampiSet* pSet = (CMalattieCronicheCampiSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDMalattia) || bCopyAll)
		m_lIDMalattia = pSet->m_lIDMalattia;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDCampo) || bCopyAll)
		m_lIDCampo = pSet->m_lIDCampo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lTipoCampo) || bCopyAll)
		m_lTipoCampo = pSet->m_lTipoCampo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lOrdine) || bCopyAll)
		m_lOrdine = pSet->m_lOrdine;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CMalattieCronicheCampiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CMalattieCronicheCampiSet* pOV = (CMalattieCronicheCampiSet*)pOldValues;
	CMalattieCronicheCampiSet* pNV = (CMalattieCronicheCampiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDMalattia", pOV, &pOV->m_lIDMalattia, pNV, &pNV->m_lIDMalattia);
	sp.Execute("IDCampo", pOV, &pOV->m_lIDCampo, pNV, &pNV->m_lIDCampo);
	sp.Execute("TipoCampo", pOV, &pOV->m_lTipoCampo, pNV, &pNV->m_lTipoCampo);
	sp.Execute("Ordine", pOV, &pOV->m_lOrdine, pNV, &pNV->m_lOrdine);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CMalattieCronicheCampiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CMalattieCronicheCampiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CMalattieCronicheCampiSet::DeleteRecordset");
	}
	return bReturn;
}

CString CMalattieCronicheCampiSet::SetBaseFilter(const CString &strFilter)
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

// ritorna l'ordine per l'inserimento del nuovo record //
long CMalattieCronicheCampiSet::GetNextOrdine(long lIDMalattia)
{
	long lReturn = 0;

	CString sFilter;
	sFilter.Format("IDMalattia=%li", lIDMalattia);

	SetOpenFilter(sFilter);
	SetSortRecord("Ordine DESC");
	if (OpenRecordset("CMalattieCronicheCampiSet::GetNextOrdine"))
	{
		if (!IsEOF())
			lReturn = m_lOrdine + 1;

		CloseRecordset("CMalattieCronicheCampiSet::GetNextOrdine");
	}

	return lReturn;
}

// imposta l'ordine per un dato record //
void CMalattieCronicheCampiSet::SetOrdine(long lID, long lOrdine)
{
	CString sFilter;
	sFilter.Format("ID=%li", lID);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CMalattieCronicheCampiSet::SetOrdine"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CMalattieCronicheCampiSet::SetOrdine"))
			{
				m_lOrdine = lOrdine;

				UpdateRecordset("CMalattieCronicheCampiSet::SetOrdine");
			}
		}

		CloseRecordset("CMalattieCronicheCampiSet::SetOrdine");
	}
}
