#include "stdafx.h"
#include "Endox.h"
#include "SedeSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMstSediSet, CBaseSet)

CMstSediSet::CMstSediSet()
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	m_lContatore	= 0;
	m_lOrgano		= 0;
	m_lPadre		= 0;
	m_sDescrizione	= "";
	m_bEliminato    = FALSE;

	m_nFields = 6;
	SetBaseFilter("");
}

CString CMstSediSet::GetDefaultSQL()
{
	return "EMSTSEDI";
}

void CMstSediSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long (pFX, "Contatore",		m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Long (pFX, "Organo",		m_lOrgano);
		RFX_Long (pFX, "Padre",			m_lPadre);
		RFX_Text (pFX, "Descrizione",	m_sDescrizione,	255);
		RFX_Text (pFX, "ExtCode",		m_sCodiceIntegrazione,	50);
		RFX_Bool (pFX, "Eliminato",     m_bEliminato);
	}
}

void CMstSediSet::SetEmpty()
{
	m_lOrgano		= 0;
	m_lPadre		= 0;
	m_sDescrizione	= "";
	m_sCodiceIntegrazione = "";
	m_bEliminato    = FALSE;
}

CBaseSet* CMstSediSet::CreateNew()
{
	return (CBaseSet*)new CMstSediSet;
}

void CMstSediSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CMstSediSet* pSedeSet = (CMstSediSet*)pOriginalSet;

	if (!pSedeSet->IsOpen() || pSedeSet->IsFieldDirty(&pSedeSet->m_lOrgano) || bCopyAll)
		m_lOrgano = pSedeSet->m_lOrgano;
	if (!pSedeSet->IsOpen() || pSedeSet->IsFieldDirty(&pSedeSet->m_lPadre) || bCopyAll)
		m_lPadre = pSedeSet->m_lPadre;
	if (!pSedeSet->IsOpen() || pSedeSet->IsFieldDirty(&pSedeSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSedeSet->m_sDescrizione;
	if (!pSedeSet->IsOpen() || pSedeSet->IsFieldDirty(&pSedeSet->m_sCodiceIntegrazione) || bCopyAll)
		m_sCodiceIntegrazione = pSedeSet->m_sCodiceIntegrazione;
	if (!pSedeSet->IsOpen() || pSedeSet->IsFieldDirty(&pSedeSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSedeSet->m_bEliminato;
}

void CMstSediSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CMstSediSet* pOV = (CMstSediSet*)pOldValues;
	CMstSediSet* pNV = (CMstSediSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Organo", pOV, &pOV->m_lOrgano, pNV, &pNV->m_lOrgano);
	sp.Execute("Padre", pOV, &pOV->m_lPadre, pNV, &pNV->m_lPadre);
	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("ExtCode", pOV, &pOV->m_sCodiceIntegrazione, pNV, &pNV->m_sCodiceIntegrazione);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CMstSediSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CMstSediSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CMstSediSet::DeleteRecordset");
	}
	return bReturn;
}

CString CMstSediSet::SetBaseFilter(const CString &strFilter)
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

CString CMstSediSet::GetCodiceIntegrazione(int id)
{
	CString sReturn = "";

	CString filter;
	filter.Format("contatore=%li", id);

	SetOpenFilter(filter);

	if (OpenRecordset("CMstSediSet::GetCodiceIntegrazione"))
	{
		if (!IsEOF())
		{
			sReturn = m_sCodiceIntegrazione;
		}

		CloseRecordset("CMstSediSet::GetCodiceIntegrazione");
	}

	return sReturn;
}