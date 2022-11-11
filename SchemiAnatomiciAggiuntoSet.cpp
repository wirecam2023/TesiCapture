// Marvel Carvalho - BUG 4308 Esquemas Anatomicos Fleury

#include "stdafx.h"
#include "Endox.h"
#include "SchemiAnatomiciAggiuntoSet.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CSchemiAnatomiciAggiuntoSet, CBaseSet)

CSchemiAnatomiciAggiuntoSet::CSchemiAnatomiciAggiuntoSet()
: CBaseSet(&m_lCONTATORE, "CONTATORE")
{
	SetBaseFilter("ELIMINATO=0");
	SetEmpty();

	m_nFields = 6;
}

CString CSchemiAnatomiciAggiuntoSet::GetDefaultSQL()
{
	return "SCHEMI_ANATOMICI_AGGIUNTO";
}

void CSchemiAnatomiciAggiuntoSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "CONTATORE", m_lCONTATORE);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "CONTATORE_EESAMI", m_lCONTATORE_EESAMI);
		RFX_Long(pFX, "ID_SCHEMI_ANATOMICI", m_lID_SCHEMI_ANATOMICI);
		RFX_Text(pFX, "DESCRIZIONE", m_sDESCRIZIONE, 50);
		RFX_Long(pFX, "STATO", m_lSTATO);
		RFX_Bool(pFX, "ELIMINATO", m_bEliminato);
	}
}

void CSchemiAnatomiciAggiuntoSet::SetEmpty()
{
	m_lCONTATORE = 0;
	m_lCONTATORE_EESAMI = 0;
	m_lID_SCHEMI_ANATOMICI = 0;
	m_sDESCRIZIONE = "";
	m_lSTATO = 0;
	m_bEliminato = FALSE;
}

CBaseSet* CSchemiAnatomiciAggiuntoSet::CreateNew()
{
	return (CBaseSet*)new CSchemiAnatomiciAggiuntoSet;
}

void CSchemiAnatomiciAggiuntoSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CSchemiAnatomiciAggiuntoSet* pSet = (CSchemiAnatomiciAggiuntoSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lCONTATORE_EESAMI) || bCopyAll)
		m_lCONTATORE_EESAMI = pSet->m_lCONTATORE_EESAMI;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lID_SCHEMI_ANATOMICI) || bCopyAll)
		m_lID_SCHEMI_ANATOMICI = pSet->m_lID_SCHEMI_ANATOMICI;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDESCRIZIONE) || bCopyAll)
		m_sDESCRIZIONE = pSet->m_sDESCRIZIONE;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lSTATO) || bCopyAll)
		m_lSTATO = pSet->m_lSTATO;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CSchemiAnatomiciAggiuntoSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CSchemiAnatomiciAggiuntoSet* pOV = (CSchemiAnatomiciAggiuntoSet*)pOldValues;
	CSchemiAnatomiciAggiuntoSet* pNV = (CSchemiAnatomiciAggiuntoSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("CONTATORE_EESAMI", pOV, &pOV->m_lCONTATORE_EESAMI, pNV, &pNV->m_lCONTATORE_EESAMI);
	sp.Execute("ID_SCHEMI_ANATOMICI", pOV, &pOV->m_lID_SCHEMI_ANATOMICI, pNV, &pNV->m_lID_SCHEMI_ANATOMICI);
	sp.Execute("DESCRIZIONE", pOV, &pOV->m_sDESCRIZIONE, pNV, &pNV->m_sDESCRIZIONE);
	sp.Execute("STATO", pOV, &pOV->m_lSTATO, pNV, &pNV->m_lSTATO);
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CSchemiAnatomiciAggiuntoSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset(strCommento))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset(strCommento);
	}
	return bReturn;
}


CString CSchemiAnatomiciAggiuntoSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	//CString strUO;
	//strUO.Format("UO=%li", theApp.m_lUO);
	if (strNewFilter.IsEmpty())
	{
		//strNewFilter = strUO + " AND ELIMINATO=0";
		strNewFilter = "ELIMINATO=0";
	}
	else
	{
		//if (strNewFilter.Find("UO=") < 0)
		//	strNewFilter += " AND " + strUO;

		if (strNewFilter.Find("ELIMINATO=") < 0)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}
		
BOOL CSchemiAnatomiciAggiuntoSet::UpdateRecordset(const CString &strCommento)
{
	//if (m_nEditMode == addnew)
	//	m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
}

BOOL CSchemiAnatomiciAggiuntoSet::Find(long lID)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("CONTATORE=%li", m_lCONTATORE);
	SetOpenFilter(strFilter);
	if (OpenRecordset("CSchemiAnatomiciAggiuntoSet::Find"))
	{
		if (!IsEOF())
		{
			bReturn = TRUE;
			//DoFieldExchange();
		}
		CloseRecordset("CSchemiAnatomiciAggiuntoSet::Find");
	}
	return bReturn;
}
