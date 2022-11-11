#include "stdafx.h"
#include "Endox.h"
#include "ProvenienzaSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CProvenienzaSet, CAMBaseSet)

CProvenienzaSet::CProvenienzaSet()
	: CBaseSet(&m_lId, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

CString CProvenienzaSet::GetDefaultSQL()
{
	return "PROVENIENZA";
}

void CProvenienzaSet::DoFieldExchange(CFieldExchange* pFX)
{
	CAMBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lId);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "DESCRIZIONE", m_sDescrizione, 255);
		RFX_Text(pFX, "CODICEPROVENIENZAEST", m_sCodice, 50);
		RFX_Long(pFX, "IDPROVENIENZAENDOX", m_lIdProvenienzaEndox);
		RFX_Bool(pFX, "APERTURA_PSM_DOLO", m_bAperturaPSMDolo);
		RFX_Bool(pFX, "ELIMINATO", m_bEliminato);
	}
}

void CProvenienzaSet::SetEmpty()
{
	m_lId = 0;
	m_sDescrizione = "";
	m_sCodice = "";
	m_lIdProvenienzaEndox = -1;
	m_bAperturaPSMDolo = FALSE;
	m_bEliminato = FALSE;
}

CBaseSet* CProvenienzaSet::CreateNew()
{
	return (CBaseSet*)new CProvenienzaSet;
}

void CProvenienzaSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CProvenienzaSet* pSet = (CProvenienzaSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodice) || bCopyAll)
		m_sCodice = pSet->m_sCodice;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIdProvenienzaEndox) || bCopyAll)
		m_lIdProvenienzaEndox = pSet->m_lIdProvenienzaEndox;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bAperturaPSMDolo) || bCopyAll)
		m_bAperturaPSMDolo = pSet->m_bAperturaPSMDolo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CProvenienzaSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CProvenienzaSet* pOV = (CProvenienzaSet*)pOldValues;
	CProvenienzaSet* pNV = (CProvenienzaSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("DESCRIZIONE", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("CODICEPROVENIENZAEST", pOV, &pOV->m_sCodice, pNV, &pNV->m_sCodice);
	sp.Execute("IDPROVENIENZAENDOX", pOV, &pOV->m_lIdProvenienzaEndox, pNV, &pNV->m_lIdProvenienzaEndox);
	sp.Execute("APERTURA_PSM_DOLO", pOV, &pOV->m_bAperturaPSMDolo, pNV, &pNV->m_bAperturaPSMDolo);
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}
		
BOOL CProvenienzaSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CProvenienzaSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CProvenienzaSet::DeleteRecordset");
	}
	return bReturn;
}

CString CProvenienzaSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	if (strNewFilter.IsEmpty())
	{
		strNewFilter = "ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("ELIMINATO=") < 0)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}
		
BOOL CProvenienzaSet::UpdateRecordset(const CString &strCommento)
{
	return CBaseSet::UpdateRecordset(strCommento);
}

long CProvenienzaSet::GetInternoEsterno(long idProvenienza)
{
	long lReturn = -1;

	CString filter = "";
	filter.Format("ID=%li", idProvenienza);
	SetOpenFilter(filter);

	if (OpenRecordset("CProvenienzaSet::GetInternoEsterno"))
	{
		if (!IsEOF())
		{
			lReturn = m_lIdProvenienzaEndox;
		}

		CloseRecordset("CProvenienzaSet::GetInternoEsterno");
	}

	return lReturn;
}

CString CProvenienzaSet::GetCodiceIntegrazione(long idProvenienza)
{
	CString sReturn = "";

	CString filter = "";
	filter.Format("ID=%li", idProvenienza);
	SetOpenFilter(filter);

	if (OpenRecordset("CProvenienzaSet::GetInternoEsterno"))
	{
		if (!IsEOF())
		{
			sReturn = m_sCodice;
		}

		CloseRecordset("CProvenienzaSet::GetInternoEsterno");
	}

	return sReturn;
}

CString CProvenienzaSet::GetDescrizione(long idProvenienza)
{
	CString sReturn = "";

	CString filter = "";
	filter.Format("ID=%li", idProvenienza);
	SetOpenFilter(filter);

	if (OpenRecordset("CProvenienzaSet::GetInternoEsterno"))
	{
		if (!IsEOF())
		{
			sReturn = m_sDescrizione;
		}

		CloseRecordset("CProvenienzaSet::GetInternoEsterno");
	}

	return sReturn;
}

long CProvenienzaSet::GetIdFromValue(CString value)
{
	long lReturn = -1;

	CString filter = "";
	filter.Format("DESCRIZIONE='%s'", value);
	SetOpenFilter(filter);

	if (OpenRecordset("CProvenienzaSet::GetInternoEsterno"))
	{
		if (!IsEOF())
		{
			lReturn = m_lId;
		}

		CloseRecordset("CProvenienzaSet::GetInternoEsterno");
	}

	return lReturn;
}

BOOL CProvenienzaSet::PSMRequired(long idProvenienza)
{
	BOOL bReturn = -1;

	CString filter = "";
	filter.Format("ID=%li", idProvenienza);
	SetOpenFilter(filter);

	if (OpenRecordset("CProvenienzaSet::PSMRequired"))
	{
		if (!IsEOF())
		{
			bReturn = m_bAperturaPSMDolo;
		}

		CloseRecordset("CProvenienzaSet::PSMRequired");
	}

	return bReturn;
}

long CProvenienzaSet::GetFirst(int InternoEsterno)
{
	long lReturn = -1;

	CString filter = "";
	filter.Format("IDPROVENIENZAENDOX=%li", InternoEsterno);
	SetOpenFilter(filter);

	if (OpenRecordset("CProvenienzaSet::GetFirst"))
	{
		if (!IsEOF())
		{
			lReturn = m_lId;
		}

		CloseRecordset("CProvenienzaSet::GetFirst");
	}

	return lReturn;
}