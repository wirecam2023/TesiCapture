#include "stdafx.h"
#include "ComboPrestazioni.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CComboPrestazioni, CBaseSet)

//Julio - BUG 3365 - MAMOGUS 
CComboPrestazioni::CComboPrestazioni() 
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4; 
}

CString CComboPrestazioni::GetDefaultSQL()
{
	return "COMBOPRESTAZIONI";
}

void CComboPrestazioni::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "CODICEPRESTAZIONE1", m_sCodicePrestazione1, 50);
		RFX_Text(pFX, "CODICEPRESTAZIONE2", m_sCodicePrestazione2, 50);
		RFX_Bool(pFX, "ELIMINATO", m_bEliminato);
	}
}

void CComboPrestazioni::SetEmpty()
{
	m_lID = 0;	
	m_sCodicePrestazione1 = "";
	m_sCodicePrestazione2 = "";
	m_bEliminato = FALSE;
}

CBaseSet* CComboPrestazioni::CreateNew()
{
	 return (CBaseSet*)new CComboPrestazioni;
}

void CComboPrestazioni::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CComboPrestazioni* pSet = (CComboPrestazioni*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodicePrestazione1) || bCopyAll)
		m_sCodicePrestazione1 = pSet->m_sCodicePrestazione1;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodicePrestazione2) || bCopyAll)
		m_sCodicePrestazione2 = pSet->m_sCodicePrestazione2;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
}

void CComboPrestazioni::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CComboPrestazioni* pOV = (CComboPrestazioni*)pOldValues;
	CComboPrestazioni* pNV = (CComboPrestazioni*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("CODICEPRESTAZIONE1", pOV, &pOV->m_sCodicePrestazione1, pNV, &pNV->m_sCodicePrestazione1);
	sp.Execute("CODICEPRESTAZIONE2", pOV, &pOV->m_sCodicePrestazione2, pNV, &pNV->m_sCodicePrestazione2);
	sp.Execute("ELIMINATO", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

CString CComboPrestazioni::SetBaseFilter(const CString &strFilter)
{
	CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	return CBaseSet::SetBaseFilter(strNewFilter);
}

void CComboPrestazioni::GetComboList(CString sCodicePrestazione, CList<CString>* listResult)
{			
	CString sFilter;
	sFilter.Format("ELIMINATO=0 AND (CODICEPRESTAZIONE1='%s' OR CODICEPRESTAZIONE2='%s')", sCodicePrestazione, sCodicePrestazione);

	SetOpenFilter(sFilter);

	if (OpenRecordset("CComboPrestazioni::GetComboList"))
	{
		while (!IsEOF())
		{
			if (m_sCodicePrestazione1 == sCodicePrestazione)
				listResult->AddTail(m_sCodicePrestazione2);
			
			if (m_sCodicePrestazione2 == sCodicePrestazione)
				listResult->AddTail(m_sCodicePrestazione1);
			
			MoveNext();
		}		
		CloseRecordset("CComboPrestazioni::GetComboList");
	}	
}