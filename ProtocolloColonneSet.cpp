#include "stdafx.h"
#include "Endox.h"
#include "ProtocolloColonneSet.h"

#include "ProtocolloValoriDefaultSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CProtocolloColonneSet, CBaseSet)

CProtocolloColonneSet::CProtocolloColonneSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 7;
}

void CProtocolloColonneSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDPROTOCOLLO", m_lIDProtocollo);
		RFX_Long(pFX, "ORDINE", m_lOrdine);
		RFX_Text(pFX, "DESCRIZIONE", m_sDescrizione, 255);
		RFX_Long(pFX, "TIPO", m_lTipo);
		RFX_Bool(pFX, "VALORIMODIFICABILI", m_bValoriModificabili);
		RFX_Bool(pFX, "ELIMINATO", m_bEliminato);
	}
}

CString CProtocolloColonneSet::GetDefaultSQL()
{
	return "PROTOCOLLO_COLONNE";
}

void CProtocolloColonneSet::SetEmpty()
{
	m_lID = 0;
	m_lIDProtocollo = 0;
	m_lOrdine = 0;
	m_sDescrizione = "";
	m_lTipo = 0;
	m_bValoriModificabili = FALSE;
	m_bEliminato = FALSE;
}

CBaseSet* CProtocolloColonneSet::CreateNew()
{
	return (CBaseSet*)new CProtocolloColonneSet;
}

void CProtocolloColonneSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CProtocolloColonneSet* pSet = (CProtocolloColonneSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDProtocollo) || bCopyAll)
		m_lIDProtocollo = pSet->m_lIDProtocollo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lOrdine) || bCopyAll)
		m_lOrdine = pSet->m_lOrdine;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lTipo) || bCopyAll)
		m_lTipo = pSet->m_lTipo;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bValoriModificabili) || bCopyAll)
		m_bValoriModificabili = pSet->m_bValoriModificabili;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CProtocolloColonneSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CProtocolloColonneSet* pOV = (CProtocolloColonneSet*)pOldValues;
	CProtocolloColonneSet* pNV = (CProtocolloColonneSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDPROTOCOLLO", pOV, &pOV->m_lIDProtocollo, pNV, &pNV->m_lIDProtocollo);
	sp.Execute("ORDINE", pOV, &pOV->m_lOrdine, pNV, &pNV->m_lOrdine);
	sp.Execute("DESCRIZIONE", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	sp.Execute("TIPO", pOV, &pOV->m_lTipo, pNV, &pNV->m_lTipo);
	sp.Execute("VALORIMODIFICABILI", pOV, &pOV->m_bValoriModificabili, pNV, &pNV->m_bValoriModificabili);
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CProtocolloColonneSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CProtocolloColonneSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CProtocolloColonneSet::DeleteRecordset");
	}
	return bReturn;
}

CString CProtocolloColonneSet::SetBaseFilter(const CString &strFilter)
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

long CProtocolloColonneSet::AddRow(long lIDProtocollo, CString sDescrizione, long lTipo, BOOL bValoriModificabili)
{
	long lOrdine = 1;
	long lReturn = 0;

	CString sTempFilter;
	sTempFilter.Format("IDPROTOCOLLO = %li", lIDProtocollo);
	SetOpenFilter(sTempFilter);
	SetSortRecord("ORDINE DESC");
	if (OpenRecordset("CProtocolloColonneSet::AddRow"))
	{
		if (!IsEOF())
			lOrdine = m_lOrdine + 1;

		if (AddNewRecordset("CProtocolloColonneSet::AddRow"))
		{
			m_lIDProtocollo = lIDProtocollo;
			m_lOrdine = lOrdine;
			m_sDescrizione = sDescrizione;
			m_lTipo = lTipo;
			m_bValoriModificabili = bValoriModificabili;

			if (UpdateRecordset("CProtocolloColonneSet::AddRow"))
				lReturn = GetLastAdd();
		}

		CloseRecordset("CProtocolloColonneSet::AddRow");
	}

	//

	return lReturn;
}

void CProtocolloColonneSet::EdtRow(long lID, CString sDescrizione, long lTipo, BOOL bValoriModificabili)
{
	CString sFilter;
	sFilter.Format("ID=%li", lID);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CProtocolloColonneSet::EdtRow"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CProtocolloColonneSet::EdtRow"))
			{
				m_sDescrizione = sDescrizione;
				m_lTipo = lTipo;
				m_bValoriModificabili = bValoriModificabili;
				UpdateRecordset("CProtocolloColonneSet::EdtRow");
			}
		}

		CloseRecordset("CProtocolloColonneSet::EdtRow");
	}
}

void CProtocolloColonneSet::DelRow(long lID)
{
	CString sFilter;
	sFilter.Format("ID=%li", lID);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CProtocolloColonneSet::DelRow"))
	{
		if (!IsEOF())
		{
			long lIDProt = m_lIDProtocollo;

			if (DeleteRecordset("CProtocolloColonneSet::DelRow"))
				CProtocolloValoriDefaultSet().DelAllColo(lIDProt, lID);
		}

		CloseRecordset("CProtocolloColonneSet::DelRow");
	}
}

void CProtocolloColonneSet::EdtOrder(long lID, long lOrdine)
{
	CString sFilter;
	sFilter.Format("ID=%li", lID);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CProtocolloColonneSet::EdtOrder"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CProtocolloColonneSet::EdtOrder"))
			{
				m_lOrdine = lOrdine;
				UpdateRecordset("CProtocolloColonneSet::EdtOrder");
			}
		}

		CloseRecordset("CProtocolloColonneSet::EdtOrder");
	}
}

void CProtocolloColonneSet::DelAllProt(long lIDProtocollo)
{
	CString sFilter;
	sFilter.Format("IDPROTOCOLLO=%li", lIDProtocollo);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CProtocolloColonneSet::DelAllProt"))
	{
		while (!IsEOF())
		{
			DeleteRecordset("CProtocolloColonneSet::DelAllProt");
			MoveNext();
		}

		CloseRecordset("CProtocolloColonneSet::DelAllProt");
	}
}

long CProtocolloColonneSet::FleuryTrans(long lIDProtocollo, CString sDescrizione)
{
	long lReturn = 0;

	sDescrizione.Trim();
	sDescrizione.Replace("'", "''");

	if ((lIDProtocollo > 0) && (!sDescrizione.IsEmpty()))
	{
		CString sFilter;
		sFilter.Format("IDPROTOCOLLO = %li AND DESCRIZIONE = '%s'", lIDProtocollo, sDescrizione);
		SetOpenFilter(sFilter);
		if (OpenRecordset("CProtocolloColonneSet::FleuryTrans"))
		{
			if (!IsEOF())
				lReturn = m_lID;

			CloseRecordset("CProtocolloColonneSet::FleuryTrans");
		}
	}

	return lReturn;
}