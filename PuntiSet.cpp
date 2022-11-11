#include "stdafx.h"
#include "Endox.h"
#include "PuntiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CPuntiSet, CBaseSet)

CPuntiSet::CPuntiSet()
	: CBaseSet(&m_lID, "ID")
{
	m_lID = 0;
	m_lIDOrgano = 0;
	m_lX = 0;
	m_lY = 0;
	m_bEliminato = FALSE;

	m_nFields = 5;
	SetBaseFilter("");
}

CString CPuntiSet::GetDefaultSQL()
{
	return "Punti";
}

void CPuntiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDOrgano", m_lIDOrgano);
		RFX_Long(pFX, "X", m_lX);
		RFX_Long(pFX, "Y", m_lY);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CPuntiSet::SetEmpty()
{
	m_lID = 0;
	m_lIDOrgano = 0;
	m_lX = 0;
	m_lY = 0;
	m_bEliminato = FALSE;
}

BOOL CPuntiSet::GetDatiPunto(long lIDPunto, long &lIDOrgano, long &lX, long &lY)
{
	BOOL bReturn = FALSE;

	if (lIDPunto > 0)
	{
		CString strFilter;
		strFilter.Format("ID=%li", lIDPunto);

		SetOpenFilter(strFilter);
		if (OpenRecordset("CPuntiSet::GetDatiPunto") == TRUE)
		{
			if ((IsBOF() == FALSE) && (IsEOF() == FALSE))
			{
				lIDOrgano = m_lIDOrgano;
				lX = m_lX;
				lY = m_lY;

				bReturn = TRUE;
			}

			CloseRecordset("CPuntiSet::GetDatiPunto");
		}
	}

	return bReturn;
}

long CPuntiSet::SetDatiPunto(long lIDPunto, long lIDOrgano, long lX, long lY)
{
	// Sandro 10/07/2013 //

	long lReturn = 0;

	if (lIDPunto > 0)
	{
		CString strFilter;
		strFilter.Format("ID=%li", lIDPunto);

		SetOpenFilter(strFilter);
		if (OpenRecordset("CPuntiSet::SetDatiPunto"))
		{
			if (!IsEOF())
			{
				if (EditRecordset("CPuntiSet::SetDatiPunto"))
				{
					m_lX = lX;
					m_lY = lY;

					if (UpdateRecordset("CPuntiSet::SetDatiPunto"))
						lReturn = lIDPunto;
				}
			}

			CloseRecordset("CPuntiSet::SetDatiPunto");
		}
	}
	else
	{
		if (OpenRecordset("CPuntiSet::SetDatiPunto"))
		{
			if (AddNewRecordset("CPuntiSet::SetDatiPunto"))
			{
				m_lIDOrgano = lIDOrgano;
				m_lX = lX;
				m_lY = lY;

				if (UpdateRecordset("CPuntiSet::SetDatiPunto"))
					lReturn = GetLastAdd();
			}

			CloseRecordset("CPuntiSet::SetDatiPunto");
		}
	}

	return lReturn;
}

CBaseSet* CPuntiSet::CreateNew()
{
	return (CBaseSet*)new CPuntiSet;
}

void CPuntiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CPuntiSet* pPuntiSet = (CPuntiSet*)pOriginalSet;

	if (!pPuntiSet->IsOpen() || pPuntiSet->IsFieldDirty(&pPuntiSet->m_lIDOrgano) || bCopyAll)
		m_lIDOrgano = pPuntiSet->m_lIDOrgano;
	if (!pPuntiSet->IsOpen() || pPuntiSet->IsFieldDirty(&pPuntiSet->m_lX) || bCopyAll)
		m_lX = pPuntiSet->m_lX;
	if (!pPuntiSet->IsOpen() || pPuntiSet->IsFieldDirty(&pPuntiSet->m_lY) || bCopyAll)
		m_lY = pPuntiSet->m_lY;
	if (!pPuntiSet->IsOpen() || pPuntiSet->IsFieldDirty(&pPuntiSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pPuntiSet->m_bEliminato;
}

void CPuntiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CPuntiSet* pOV = (CPuntiSet*)pOldValues;
	CPuntiSet* pNV = (CPuntiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDOrgano", pOV, &pOV->m_lIDOrgano, pNV, &pNV->m_lIDOrgano);
	sp.Execute("X", pOV, &pOV->m_lX, pNV, &pNV->m_lX);
	sp.Execute("Y", pOV, &pOV->m_lY, pNV, &pNV->m_lY);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CPuntiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CPuntiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CPuntiSet::DeleteRecordset");
	}
	return bReturn;
}

CString CPuntiSet::SetBaseFilter(const CString &strFilter)
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