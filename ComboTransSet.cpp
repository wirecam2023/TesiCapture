#include "stdafx.h"
#include "Endox.h"
#include "ComboTransSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CComboTransSet, CBaseSet)

CComboTransSet::CComboTransSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();
	SetSortRecord("EXTCODE, DESCRIZIONE");

	m_nFields = 5;
}

void CComboTransSet::SetEmpty()
{
	m_lID			= 0;
	m_sDescrizione	= "";
	m_sExtCode		= "";
	m_lUO = 0;
	m_bEliminato    = FALSE;
}

void CComboTransSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 50);
		RFX_Text(pFX, "ExtCode", m_sExtCode, 50);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

long CComboTransSet::Add(CString sDescrizione, CString sExtCode)
{
	long lReturn = 0;

	if (OpenRecordset("CComboTransSet::Add"))
	{
		if (AddNewRecordset("CComboTransSet::Add"))
		{
			m_sDescrizione	=	sDescrizione;
			m_sExtCode		=	sExtCode;

			if (UpdateRecordset("CComboTransSet::Add"))
				lReturn = GetLastAdd();
		}

		CloseRecordset("CComboTransSet::Add");
	}

	return lReturn;
}

void CComboTransSet::Edt(long lID, CString sDescrizione, CString sExtCode)
{
	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CComboTransSet::Edt"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CComboTransSet::Edt"))
			{
				m_sDescrizione	=	sDescrizione;
				m_sExtCode		=	sExtCode;
				UpdateRecordset("CComboTransSet::Edt");
			}
		}

		CloseRecordset("CComboTransSet::Edt");
	}

	SetOpenFilter("");
}

BOOL CComboTransSet::Del(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("ID=%li", lID);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CComboTransSet::Del"))
	{
		if (!IsEOF())
			bReturn = DeleteRecordset("CComboTransSet::Del");

		CloseRecordset("CComboTransSet::Del");
	}

	SetOpenFilter("");

	return bReturn;
}

void CComboTransSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CComboTransSet* pSet = (CComboTransSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sExtCode) || bCopyAll)
		m_sExtCode = pSet->m_sExtCode;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

BOOL CComboTransSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CComboTransSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CComboTransSet::DeleteRecordset");
	}
	return bReturn;
}

CString CComboTransSet::SetBaseFilter(const CString &strFilter)
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

BOOL CComboTransSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

void CComboTransSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CComboTransSet* pOV = (CComboTransSet*)pOldValues;
	CComboTransSet* pNV = (CComboTransSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("ExtCode", pOV, &pOV->m_sExtCode, pNV, &pNV->m_sExtCode);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

CString CComboTransSet::GetDescrizione(long lID)
{
	CString sReturn = "";

	CString sFilter;
	sFilter.Format("ID=%li", lID);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CComboTransSet::GetDescrizione"))
	{
		if (!IsEOF())
			sReturn = m_sDescrizione;

		CloseRecordset("CComboTransSet::GetDescrizione");
	}

	return sReturn;
}