#include "stdafx.h"
#include "Endox.h"
#include "ProtocolloValoriDefaultSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CProtocolloValoriDefaultSet, CBaseSet)

CProtocolloValoriDefaultSet::CProtocolloValoriDefaultSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

void CProtocolloValoriDefaultSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDPROTOCOLLO", m_lIDProtocollo);
		RFX_Long(pFX, "IDCOLONNA", m_lIDColonna);
		RFX_Long(pFX, "ORDINE", m_lOrdine);
		RFX_Text(pFX, "VALORE", m_sValore, 255);
		RFX_Bool(pFX, "ELIMINATO", m_bEliminato);
	}
}

CString CProtocolloValoriDefaultSet::GetDefaultSQL()
{
	return "PROTOCOLLO_VALORIDEFAULT";
}

void CProtocolloValoriDefaultSet::SetEmpty()
{
	m_lID = 0;
	m_lIDProtocollo = 0;
	m_lIDColonna = 0;
	m_lOrdine = 0;
	m_sValore = "";
	m_bEliminato = FALSE;
}

CBaseSet* CProtocolloValoriDefaultSet::CreateNew()
{
	return (CBaseSet*)new CProtocolloValoriDefaultSet;
}

void CProtocolloValoriDefaultSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CProtocolloValoriDefaultSet* pSet = (CProtocolloValoriDefaultSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDProtocollo) || bCopyAll)
		m_lIDProtocollo = pSet->m_lIDProtocollo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDColonna) || bCopyAll)
		m_lIDColonna = pSet->m_lIDColonna;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lOrdine) || bCopyAll)
		m_lOrdine = pSet->m_lOrdine;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sValore) || bCopyAll)
		m_sValore = pSet->m_sValore;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CProtocolloValoriDefaultSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CProtocolloValoriDefaultSet* pOV = (CProtocolloValoriDefaultSet*)pOldValues;
	CProtocolloValoriDefaultSet* pNV = (CProtocolloValoriDefaultSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDPROTOCOLLO", pOV, &pOV->m_lIDProtocollo, pNV, &pNV->m_lIDProtocollo);
	sp.Execute("IDCOLONNA", pOV, &pOV->m_lIDColonna, pNV, &pNV->m_lIDColonna);
	sp.Execute("ORDINE", pOV, &pOV->m_lOrdine, pNV, &pNV->m_lOrdine);
	sp.Execute("VALORE", pOV, &pOV->m_sValore, pNV, &pNV->m_sValore);
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CProtocolloValoriDefaultSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CProtocolloValoriDefaultSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CProtocolloValoriDefaultSet::DeleteRecordset");
	}
	return bReturn;
}

CString CProtocolloValoriDefaultSet::SetBaseFilter(const CString &strFilter)
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

void CProtocolloValoriDefaultSet::AddEdtRow(long lIDProtocollo, long lIDColonna, long lOrdine, CString sValore)
{
	CString sFilter;
	sFilter.Format("IDPROTOCOLLO=%li AND IDCOLONNA=%li AND ORDINE=%li", lIDProtocollo, lIDColonna, lOrdine);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CProtocolloValoriDefaultSet::AddEdtRow"))
	{
		if (IsEOF())
		{
			if (AddNewRecordset("CProtocolloValoriDefaultSet::AddEdtRow"))
			{
				m_lIDProtocollo = lIDProtocollo;
				m_lIDColonna = lIDColonna;
				m_lOrdine = lOrdine;
				m_sValore = sValore;

				UpdateRecordset("CProtocolloValoriDefaultSet::AddEdtRow");
			}
		}
		else
		{
			if (EditRecordset("CProtocolloValoriDefaultSet::AddEdtRow"))
			{
				m_sValore = sValore;

				UpdateRecordset("CProtocolloValoriDefaultSet::AddEdtRow");
			}
		}

		CloseRecordset("CProtocolloValoriDefaultSet::AddEdtRow");
	}
}

void CProtocolloValoriDefaultSet::DelAllProt(long lIDProtocollo)
{
	CString sFilter;
	sFilter.Format("IDPROTOCOLLO=%li", lIDProtocollo);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CProtocolloValoriDefaultSet::DelAllProt"))
	{
		while (!IsEOF())
		{
			DeleteRecordset("CProtocolloValoriDefaultSet::DelAllProt");
			MoveNext();
		}

		CloseRecordset("CProtocolloValoriDefaultSet::DelAllProt");
	}
}

void CProtocolloValoriDefaultSet::DelAllColo(long lIDProtocollo, long lIDColonna)
{
	CString sFilter;
	sFilter.Format("IDPROTOCOLLO=%li AND IDCOLONNA=%li", lIDProtocollo, lIDColonna);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CProtocolloValoriDefaultSet::DelAllColo"))
	{
		while (!IsEOF())
		{
			DeleteRecordset("CProtocolloValoriDefaultSet::DelAllColo");
			MoveNext();
		}

		CloseRecordset("CProtocolloValoriDefaultSet::DelAllColo");
	}
}

void CProtocolloValoriDefaultSet::DelAllOrdi(long lIDProtocollo, long lOrdine)
{
	CString sFilter;
	sFilter.Format("IDPROTOCOLLO=%li AND ORDINE=%li", lIDProtocollo, lOrdine);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CProtocolloValoriDefaultSet::DelAllOrdi"))
	{
		while (!IsEOF())
		{
			DeleteRecordset("CProtocolloValoriDefaultSet::DelAllOrdi");
			MoveNext();
		}

		CloseRecordset("CProtocolloValoriDefaultSet::DelAllOrdi");
	}
}

long CProtocolloValoriDefaultSet::GetNextOrdine(long lIDProtocollo)
{
	long lReturn = 0;

	CString sFilter;
	sFilter.Format("IDPROTOCOLLO=%li", lIDProtocollo);

	SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
	SetOpenFilter(sFilter);
	SetSortRecord("ORDINE DESC");
	if (OpenRecordset("CProtocolloValoriDefaultSet::GetNextOrdine"))
	{
		if (!IsEOF())
			lReturn = m_lOrdine;

		CloseRecordset("CProtocolloValoriDefaultSet::GetNextOrdine");
	}

	return lReturn + 1;
}