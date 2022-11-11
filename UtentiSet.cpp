#include "stdafx.h"
#include "Endox.h"
#include "UtentiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CUtentiSet, CBaseSet)

CUtentiSet::CUtentiSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4;
}

CString CUtentiSet::GetDefaultSQL()
{
	return "UTENTI";
}

void CUtentiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Username", m_sUsername, 255);
		RFX_Long(pFX, "ID_Gruppo", m_lIDGruppo);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CUtentiSet::SetEmpty()
{
	m_lID = 0;
	m_sUsername = "";
	m_lIDGruppo = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CUtentiSet::CreateNew()
{
	return (CBaseSet*)new CUtentiSet;
}

void CUtentiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CUtentiSet* pUtentiSet = (CUtentiSet*)pOriginalSet;

	if (!pUtentiSet->IsOpen() || pUtentiSet->IsFieldDirty(&pUtentiSet->m_sUsername) || bCopyAll)
		m_sUsername = pUtentiSet->m_sUsername;
	if (!pUtentiSet->IsOpen() || pUtentiSet->IsFieldDirty(&pUtentiSet->m_lIDGruppo) || bCopyAll)
		m_lIDGruppo = pUtentiSet->m_lIDGruppo;
	if (!pUtentiSet->IsOpen() || pUtentiSet->IsFieldDirty(&pUtentiSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pUtentiSet->m_bEliminato;
}

void CUtentiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CUtentiSet* pOV = (CUtentiSet*)pOldValues;
	CUtentiSet* pNV = (CUtentiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Username", pOV, &pOV->m_sUsername, pNV, &pNV->m_sUsername);
	sp.Execute("ID_Gruppo", pOV, &pOV->m_lIDGruppo, pNV, &pNV->m_lIDGruppo);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CUtentiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CUtentiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CUtentiSet::DeleteRecordset");
	}
	return bReturn;
}

CString CUtentiSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	/*strNewFilter.MakeUpper();

	if (strNewFilter.IsEmpty())
	{
		strNewFilter = "ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("ELIMINATO") == -1)
			strNewFilter += " AND ELIMINATO=0";
	}*/

	return CBaseSet::SetBaseFilter(strNewFilter);
}

CString CUtentiSet::GetUsername(long lID)
{
	CString sReturn = "";

	CString sFilter;
	sFilter.Format("ID=%li", lID);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CUtentiSet::GetUsername"))
	{
		if (!IsEOF())
			sReturn = m_sUsername;

		CloseRecordset("CUtentiSet::GetUsername");
	}

	return sReturn;
}

long CUtentiSet::GetIdGruppo(long lID)
{
	long lReturn = 0;

	CString sFilter;
	sFilter.Format("ID=%li", lID);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CUtentiSet::GetIdGruppo"))
	{
		if (!IsEOF())
			lReturn = m_lIDGruppo;

		CloseRecordset("CUtentiSet::GetIdGruppo");
	}

	return lReturn;
}

long CUtentiSet::GetIDFromUsername(CString sUsername)
{
	long lReturn = 0;

	sUsername.Trim();
	sUsername.Replace("'", "''");

	if (!sUsername.IsEmpty())
	{
		CString sFilter;
		sFilter.Format("USERNAME='%s'", sUsername);

		SetOpenFilter(sFilter);
		if (OpenRecordset("CUtentiSet::GetIDFromUsername"))
		{
			if (!IsEOF())
				lReturn = m_lID;

			CloseRecordset("CUtentiSet::GetIDFromUsername");
		}
	}

	return lReturn;
}

long CUtentiSet::FleuryTrans(CString sUsername)
{
	long lReturn = 0;

	sUsername.Trim();
	sUsername.Replace("'", "''");

	if (!sUsername.IsEmpty())
	{
		CString sFilter;
		sFilter.Format("USERNAME = '%s'", sUsername);

		SetOpenFilter(sFilter);
		if (OpenRecordset("CUtentiSet::FleuryTrans"))
		{
			if (IsEOF())
			{
				if (AddNewRecordset("CUtentiSet::FleuryTrans"))
				{
					m_sUsername = sUsername;

					if (UpdateRecordset("CUtentiSet::FleuryTrans"))
						lReturn = GetLastAdd();
				}
			}
			else
			{
				lReturn = m_lID;
			}

			CloseRecordset("CUtentiSet::FleuryTrans");
		}
	}

	return lReturn;
}