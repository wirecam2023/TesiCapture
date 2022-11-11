#include "stdafx.h"
#include "Endox.h"
#include "SaleEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CSaleEsameSet, CBaseSet)

CSaleEsameSet::CSaleEsameSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 5;
}

CString CSaleEsameSet::GetDefaultSQL()
{
	return "SaleEsame";
}

void CSaleEsameSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
		//RFX_Text(pFX, "CodiceIntegrazione", m_sCodiceIntegrazione, 50);
		RFX_Long(pFX, "IdSede", m_lIDSede);
		RFX_Long(pFX, "UO", m_lUO);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

void CSaleEsameSet::SetEmpty()
{
	m_lID = 0;
	m_sDescrizione = "";
	//m_sCodiceIntegrazione = "";
	m_lIDSede = 0;
	m_lUO = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CSaleEsameSet::CreateNew()
{
	return (CBaseSet*)new CSaleEsameSet;
}

void CSaleEsameSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CSaleEsameSet* pSet = (CSaleEsameSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDescrizione) || bCopyAll)
		m_sDescrizione = pSet->m_sDescrizione;
	/*if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodiceIntegrazione) || bCopyAll)
		m_sCodiceIntegrazione = pSet->m_sCodiceIntegrazione;*/
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDSede) || bCopyAll)
		m_lIDSede = pSet->m_lIDSede;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUO) || bCopyAll)
		m_lUO = pSet->m_lUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CSaleEsameSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CSaleEsameSet* pOV = (CSaleEsameSet*)pOldValues;
	CSaleEsameSet* pNV = (CSaleEsameSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Descrizione", pOV, &pOV->m_sDescrizione, pNV, &pNV->m_sDescrizione);
	//sp.Execute("CodiceIntegrazione", pOV, &pOV->m_sCodiceIntegrazione, pNV, &pNV->m_sCodiceIntegrazione);
	sp.Execute("IdSede", pOV, &pOV->m_lIDSede, pNV, &pNV->m_lIDSede);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CSaleEsameSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CSaleEsameSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CSaleEsameSet::DeleteRecordset");
	}
	return bReturn;
}

CString CSaleEsameSet::SetBaseFilter(const CString &strFilter)
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
		
BOOL CSaleEsameSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

// Sandro 15/04/2014 //
long CSaleEsameSet::GetIDSala(CString sDescrizione)
{
	long lReturn = 0;

	sDescrizione.Replace("'", "''");

	CString sFilter;
	sFilter.Format("Descrizione='%s'", sDescrizione);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CSaleEsameSet::GetID"))
	{
		if (!IsEOF())
			lReturn = m_lID;

		CloseRecordset("CSaleEsameSet::GetID");
	}

	return lReturn;
}

long CSaleEsameSet::GetIdSalaFromIdSede(int lIDSede)
{
	long lReturn = 0;

	CString sFilter;
	sFilter.Format("idSede=%li", lIDSede);

	SetOpenFilter(sFilter);
	SetSortRecord("ID DESC");

	if (OpenRecordset("CSaleEsameSet::GetIdSalaFromIdSede"))
	{
		if (!IsEOF())
			lReturn = m_lID;

		CloseRecordset("CSaleEsameSet::GetIdSalaFromIdSede");
	}

	return lReturn;
}

/*CString CSaleEsameSet::GetCodiceSedeEstFromIdSede(int lIDSede)
{
	CString sReturn = "";

	CString sFilter;
	sFilter.Format("idSede=%li", lIDSede);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CSaleEsameSet::GetCodiceSedeEstFromIdSala"))
	{
		if (!IsEOF())
			sReturn = m_sCodiceIntegrazione;

		CloseRecordset("CSaleEsameSet::GetCodiceSedeEstFromIdSala");
	}

	return sReturn;
}*/
