#include "stdafx.h"
#include "Endox.h"
#include "ProtocolloEsamiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CProtocolloEsamiSet, CBaseSet)

CProtocolloEsamiSet::CProtocolloEsamiSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 7;
}

void CProtocolloEsamiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDESAME", m_lIDEsame);
		RFX_Long(pFX, "IDPROTOCOLLO", m_lIDProtocollo);
		RFX_Long(pFX, "IDCOLONNA", m_lIDColonna);
		RFX_Long(pFX, "ORDINE", m_lOrdine);
		RFX_Text(pFX, "VALORE", m_sValore, 255);
		RFX_Bool(pFX, "ELIMINATO", m_bEliminato);
	}
}

CString CProtocolloEsamiSet::GetDefaultSQL()
{
	return "PROTOCOLLO_ESAMI";
}

void CProtocolloEsamiSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_lIDProtocollo = 0;
	m_lIDColonna = 0;
	m_lOrdine = 0;
	m_sValore = "";
	m_bEliminato = FALSE;
}

CBaseSet* CProtocolloEsamiSet::CreateNew()
{
	return (CBaseSet*)new CProtocolloEsamiSet;
}

void CProtocolloEsamiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CProtocolloEsamiSet* pSet = (CProtocolloEsamiSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pSet->m_lIDEsame;
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

void CProtocolloEsamiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CProtocolloEsamiSet* pOV = (CProtocolloEsamiSet*)pOldValues;
	CProtocolloEsamiSet* pNV = (CProtocolloEsamiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDESAME", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("IDPROTOCOLLO", pOV, &pOV->m_lIDProtocollo, pNV, &pNV->m_lIDProtocollo);
	sp.Execute("IDCOLONNA", pOV, &pOV->m_lIDColonna, pNV, &pNV->m_lIDColonna);
	sp.Execute("ORDINE", pOV, &pOV->m_lOrdine, pNV, &pNV->m_lOrdine);
	sp.Execute("VALORE", pOV, &pOV->m_sValore, pNV, &pNV->m_sValore);
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CProtocolloEsamiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CProtocolloEsamiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CProtocolloEsamiSet::DeleteRecordset");
	}
	return bReturn;
}

CString CProtocolloEsamiSet::SetBaseFilter(const CString &strFilter)
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

void CProtocolloEsamiSet::AddEdtRow(long lIDEsame, long lIDProtocollo, long lIDColonna, long lOrdine, CString sValore)
{
	CString sFilter;
	sFilter.Format("IDESAME=%li AND IDPROTOCOLLO=%li AND IDCOLONNA=%li AND ORDINE=%li", lIDEsame, lIDProtocollo, lIDColonna, lOrdine);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CProtocolloEsamiSet::AddEdtRow"))
	{
		if (IsEOF())
		{
			if (AddNewRecordset("CProtocolloEsamiSet::AddEdtRow"))
			{
				m_lIDEsame = lIDEsame;
				m_lIDProtocollo = lIDProtocollo;
				m_lIDColonna = lIDColonna;
				m_lOrdine = lOrdine;
				m_sValore = sValore;

				UpdateRecordset("CProtocolloEsamiSet::AddEdtRow");
			}
		}
		else
		{
			if (EditRecordset("CProtocolloEsamiSet::AddEdtRow"))
			{
				m_sValore = sValore;

				UpdateRecordset("CProtocolloEsamiSet::AddEdtRow");
			}
		}

		CloseRecordset("CProtocolloEsamiSet::AddEdtRow");
	}
}

void CProtocolloEsamiSet::DelRows(long lIDEsame, long lIDProtocollo, long lPrimoOrdineDaCancellare)
{
	CString sFilter;
	sFilter.Format("IDESAME=%li AND IDPROTOCOLLO=%li AND ORDINE>=%li", lIDEsame, lIDProtocollo, lPrimoOrdineDaCancellare);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CProtocolloEsamiSet::DelRows"))
	{
		while (!IsEOF())
		{
			DeleteRecordset("CProtocolloEsamiSet::DelRows");
			MoveNext();
		}

		CloseRecordset("CProtocolloEsamiSet::DelRows");
	}
}

BOOL CProtocolloEsamiSet::HasRows(long lIDEsame, long lIDProtocollo)
{
	BOOL bReturn = FALSE;

	if ((lIDEsame > 0) && (lIDProtocollo > 0))
	{
		CString sFilter;
		sFilter.Format("IDESAME=%li AND IDPROTOCOLLO=%li", lIDEsame, lIDProtocollo);

		SetOpenFilter(sFilter);
		if (OpenRecordset("CProtocolloEsamiSet::HasRows"))
		{
			bReturn = !IsEOF();
			CloseRecordset("CProtocolloEsamiSet::HasRows");
		}
	}

	return bReturn;
}

/*
void CProtocolloEsamiSet::DelAllProt(long lIDProtocollo)
{
	CString sFilter;
	sFilter.Format("IDPROTOCOLLO=%li", lIDProtocollo);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CProtocolloEsamiSet::DelAllProt"))
	{
		while (!IsEOF())
		{
			DeleteRecordset("CProtocolloEsamiSet::DelAllProt");
			MoveNext();
		}

		CloseRecordset("CProtocolloEsamiSet::DelAllProt");
	}
}

void CProtocolloEsamiSet::DelAllColo(long lIDProtocollo, long lIDColonna)
{
	CString sFilter;
	sFilter.Format("IDPROTOCOLLO=%li AND IDCOLONNA=%li", lIDProtocollo, lIDColonna);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CProtocolloEsamiSet::DelAllColo"))
	{
		while (!IsEOF())
		{
			DeleteRecordset("CProtocolloEsamiSet::DelAllColo");
			MoveNext();
		}

		CloseRecordset("CProtocolloEsamiSet::DelAllColo");
	}
}

void CProtocolloEsamiSet::DelAllOrdi(long lIDProtocollo, long lOrdine)
{
	CString sFilter;
	sFilter.Format("IDPROTOCOLLO=%li AND ORDINE=%li", lIDProtocollo, lOrdine);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CProtocolloEsamiSet::DelAllOrdi"))
	{
		while (!IsEOF())
		{
			DeleteRecordset("CProtocolloEsamiSet::DelAllOrdi");
			MoveNext();
		}

		CloseRecordset("CProtocolloEsamiSet::DelAllOrdi");
	}
}

long CProtocolloEsamiSet::GetNextOrdine(long lIDProtocollo)
{
	long lReturn = 0;

	CString sFilter;
	sFilter.Format("IDPROTOCOLLO=%li", lIDProtocollo);

	SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
	SetOpenFilter(sFilter);
	SetSortRecord("ORDINE DESC");
	if (OpenRecordset("CProtocolloEsamiSet::GetNextOrdine"))
	{
		if (!IsEOF())
			lReturn = m_lOrdine;

		CloseRecordset("CProtocolloEsamiSet::GetNextOrdine");
	}

	return lReturn + 1;
}
*/