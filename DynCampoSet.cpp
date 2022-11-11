#include "stdafx.h"
#include "Endox.h"
#include "DynCampoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CDynCampoSet, CBaseSet)

CDynCampoSet::CDynCampoSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");

	m_lID = 0;
	m_lIDForm = 0;
	m_lContenuto = 0;
	m_lX = 0;
	m_lY = 0;
	m_lL = 0;
	m_lA = 0;
	m_lColore = 0;
	m_lTabOrder = 0;
	//m_lIDFaseBlocco = 0;
	m_lIDFaseBlocco = 0;
	m_bEliminato = FALSE;

	m_nFields = 11;
}

CDynCampoSet::~CDynCampoSet(void)
{
}

CString CDynCampoSet::GetDefaultSQL()
{
	return "DYNCAMPO";
}

void CDynCampoSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDForm", m_lIDForm);
		RFX_Long(pFX, "Contenuto", m_lContenuto);
		RFX_Long(pFX, "X", m_lX);
		RFX_Long(pFX, "Y", m_lY);
		RFX_Long(pFX, "L", m_lL);
		RFX_Long(pFX, "A", m_lA);
		RFX_Long(pFX, "Colore", m_lColore);
		RFX_Long(pFX, "TabOrder", m_lTabOrder);
		//RFX_Long(pFX, "MomentoBlocco", m_lIDFaseBlocco);
		RFX_Long(pFX, "IDFASEBLOCCO", m_lIDFaseBlocco);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CDynCampoSet::CreateNew()
{
	return (CBaseSet*)new CDynCampoSet;
}

void CDynCampoSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CDynCampoSet* pDynCampoSet = (CDynCampoSet*)pOriginalSet;

	if (!pDynCampoSet->IsOpen() || pDynCampoSet->IsFieldDirty(&pDynCampoSet->m_lIDForm) || bCopyAll)
		m_lIDForm = pDynCampoSet->m_lIDForm;
	if (!pDynCampoSet->IsOpen() || pDynCampoSet->IsFieldDirty(&pDynCampoSet->m_lContenuto) || bCopyAll)
		m_lContenuto = pDynCampoSet->m_lContenuto;
	if (!pDynCampoSet->IsOpen() || pDynCampoSet->IsFieldDirty(&pDynCampoSet->m_lX) || bCopyAll)
		m_lX = pDynCampoSet->m_lX;
	if (!pDynCampoSet->IsOpen() || pDynCampoSet->IsFieldDirty(&pDynCampoSet->m_lY) || bCopyAll)
		m_lY = pDynCampoSet->m_lY;
	if (!pDynCampoSet->IsOpen() || pDynCampoSet->IsFieldDirty(&pDynCampoSet->m_lL) || bCopyAll)
		m_lL = pDynCampoSet->m_lL;
	if (!pDynCampoSet->IsOpen() || pDynCampoSet->IsFieldDirty(&pDynCampoSet->m_lA) || bCopyAll)
		m_lA = pDynCampoSet->m_lA;
	if (!pDynCampoSet->IsOpen() || pDynCampoSet->IsFieldDirty(&pDynCampoSet->m_lColore) || bCopyAll)
		m_lColore = pDynCampoSet->m_lColore;
	if (!pDynCampoSet->IsOpen() || pDynCampoSet->IsFieldDirty(&pDynCampoSet->m_lTabOrder) || bCopyAll)
		m_lTabOrder = pDynCampoSet->m_lTabOrder;
	/*if (!pDynCampoSet->IsOpen() || pDynCampoSet->IsFieldDirty(&pDynCampoSet->m_lIDFaseBlocco) || bCopyAll)
		m_lIDFaseBlocco = pDynCampoSet->m_lIDFaseBlocco;*/
	if (!pDynCampoSet->IsOpen() || pDynCampoSet->IsFieldDirty(&pDynCampoSet->m_lIDFaseBlocco) || bCopyAll)
		m_lIDFaseBlocco = pDynCampoSet->m_lIDFaseBlocco;
	if (!pDynCampoSet->IsOpen() || pDynCampoSet->IsFieldDirty(&pDynCampoSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pDynCampoSet->m_bEliminato;
}

void CDynCampoSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CDynCampoSet* pOV = (CDynCampoSet*)pOldValues;
	CDynCampoSet* pNV = (CDynCampoSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDForm", pOV, &pOV->m_lIDForm, pNV, &pNV->m_lIDForm);
	sp.Execute("Contenuto", pOV, &pOV->m_lContenuto, pNV, &pNV->m_lContenuto);
	sp.Execute("X", pOV, &pOV->m_lX, pNV, &pNV->m_lX);
	sp.Execute("Y", pOV, &pOV->m_lY, pNV, &pNV->m_lY);
	sp.Execute("L", pOV, &pOV->m_lL, pNV, &pNV->m_lL);
	sp.Execute("A", pOV, &pOV->m_lA, pNV, &pNV->m_lA);
	sp.Execute("Colore", pOV, &pOV->m_lColore, pNV, &pNV->m_lColore);
	sp.Execute("TabOrder", pOV, &pOV->m_lTabOrder, pNV, &pNV->m_lTabOrder);
	//sp.Execute("MomentoBlocco", pOV, &pOV->m_lIDFaseBlocco, pNV, &pNV->m_lIDFaseBlocco);
	sp.Execute("IDFASEBLOCCO", pOV, &pOV->m_lIDFaseBlocco, pNV, &pNV->m_lIDFaseBlocco);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CDynCampoSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CDynCampoSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		BOOL aaa = CAMBaseSet::IsFieldNull(&m_bEliminato);
		bReturn = UpdateRecordset("CDynCampoSet::DeleteRecordset");
	}
	return bReturn;
}

CString CDynCampoSet::SetBaseFilter(const CString &strFilter)
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