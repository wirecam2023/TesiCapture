#include "stdafx.h"
#include "Endox.h"
#include "EsamiIntegratiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEsamiIntegratiSet, CBaseSet)

CEsamiIntegratiSet::CEsamiIntegratiSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_bColumnsTCP = CheckColumnExists("EsamiIntegrati", "IsTCP"); //Gabriel - TCP

	m_nFields = m_bColumnsTCP ? 5 : 4;
}

CString CEsamiIntegratiSet::GetDefaultSQL()
{
	return "EsamiIntegrati";
}

void CEsamiIntegratiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDEsamePrincipale", m_lIDEsamePrincipale);
		RFX_Long(pFX, "IDEsameSecondario", m_lIDEsameSecondario);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
		if (m_bColumnsTCP)
			RFX_Bool(pFX, "IsTCP", m_bIsTCP);
	}
}

void CEsamiIntegratiSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsamePrincipale = 0;
	m_lIDEsameSecondario = 0;
	m_bEliminato = FALSE;
	m_bIsTCP = FALSE;
}

CBaseSet* CEsamiIntegratiSet::CreateNew()
{
	return (CBaseSet*)new CEsamiIntegratiSet;
}

void CEsamiIntegratiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEsamiIntegratiSet* pSet = (CEsamiIntegratiSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEsamePrincipale) || bCopyAll)
		m_lIDEsamePrincipale = pSet->m_lIDEsamePrincipale;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEsameSecondario) || bCopyAll)
		m_lIDEsameSecondario = pSet->m_lIDEsameSecondario;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
	if (m_bColumnsTCP){
		if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bIsTCP) || bCopyAll)
			m_bIsTCP = pSet->m_bIsTCP;
	}
}

void CEsamiIntegratiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEsamiIntegratiSet* pOV = (CEsamiIntegratiSet*)pOldValues;
	CEsamiIntegratiSet* pNV = (CEsamiIntegratiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDEsamePrincipale", pOV, &pOV->m_lIDEsamePrincipale, pNV, &pNV->m_lIDEsamePrincipale);
	sp.Execute("IDEsameSecondario", pOV, &pOV->m_lIDEsameSecondario, pNV, &pNV->m_lIDEsameSecondario);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
	if (m_bColumnsTCP)
		sp.Execute("IsTCP", pOV, &pOV->m_bIsTCP, pNV, &pNV->m_bIsTCP);
}

BOOL CEsamiIntegratiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CEsamiIntegratiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CEsamiIntegratiSet::DeleteRecordset");
	}
	return bReturn;
}

CString CEsamiIntegratiSet::SetBaseFilter(const CString &strFilter)
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

void CEsamiIntegratiSet::AddRecord(long lIDPrincipale, long lIDSecondario, BOOL bIsTCP)
{
	if ((lIDPrincipale > 0) && (lIDSecondario > 0))
	{
		CString sFilter;
		sFilter.Format("IDEsamePrincipale=%li AND IDEsameSecondario=%li", lIDPrincipale, lIDSecondario);

		SetOpenFilter(sFilter);
		if (OpenRecordset("CEsamiIntegratiSet::AddRecord"))
		{
			if (IsEOF())
			{
				if (AddNewRecordset("CEsamiIntegratiSet::AddRecord"))
				{
					m_lIDEsamePrincipale = lIDPrincipale;
					m_lIDEsameSecondario = lIDSecondario;
					if (m_bColumnsTCP)
						m_bIsTCP = bIsTCP;

					UpdateRecordset("CEsamiIntegratiSet::AddRecord");
				}
			}
			CloseRecordset("CEsamiIntegratiSet::AddRecord");
		}
	}
}

void CEsamiIntegratiSet::DelRecord(long lIDPrincipale, long lIDSecondario)
{
	if ((lIDPrincipale > 0) && (lIDSecondario > 0))
	{
		CString sFilter;
		sFilter.Format("IDEsamePrincipale=%li AND IDEsameSecondario=%li", lIDPrincipale, lIDSecondario);

		SetOpenFilter(sFilter);
		if (OpenRecordset("CEsamiIntegratiSet::DelRecord"))
		{
			if (!IsEOF())
				DeleteRecordset("CEsamiIntegratiSet::DelRecord");

			CloseRecordset("CEsamiIntegratiSet::DelRecord");
		}
	}
}

BOOL CEsamiIntegratiSet::ExistsRecord(long lIDPrincipale, long lIDSecondario)
{
	BOOL bReturn = FALSE;

	if ((lIDPrincipale > 0) && (lIDSecondario > 0))
	{
		CString sFilter;
		sFilter.Format("IDEsamePrincipale=%li AND IDEsameSecondario=%li", lIDPrincipale, lIDSecondario);

		SetOpenFilter(sFilter);
		if (OpenRecordset("CEsamiIntegratiSet::ExistsRecord"))
		{
			bReturn = !IsEOF();
			CloseRecordset("CEsamiIntegratiSet::ExistsRecord");
		}
	}

	return bReturn;
}
