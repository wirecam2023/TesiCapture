#include "stdafx.h"
#include "Endox.h"
#include "GruppiPrelieviOldItemSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGruppiPrelieviOldItemSet, CBaseSet)

CGruppiPrelieviOldItemSet::CGruppiPrelieviOldItemSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 9;
}

CString CGruppiPrelieviOldItemSet::GetDefaultSQL()
{
	return "GRUPPIPRELIEVIOLDITEM";
}

void CGruppiPrelieviOldItemSet::SetEmpty()
{
	m_lID = 0;
	m_lIDGruppoOld = 0;
	m_lTipo = 0;
	m_lOrgano = 0;
	m_sSede = "";
	m_sProvette = "";
	m_lProcedura = 0;
	m_sDiagnosi = "";
	m_bEliminato = FALSE;
}

void CGruppiPrelieviOldItemSet::CopyFieldFrom(CGruppiPrelieviOldItemSet* pSet)
{
	SetEmpty();

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lID))
		m_lID = pSet->m_lID;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDGruppoOld))
		m_lIDGruppoOld = pSet->m_lIDGruppoOld;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lTipo))
		m_lTipo = pSet->m_lTipo;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lOrgano))
		m_lOrgano = pSet->m_lOrgano;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sSede))
		m_sSede = pSet->m_sSede.Left(49);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sProvette))
		m_sProvette = pSet->m_sProvette.Left(49);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lProcedura))
		m_lProcedura = pSet->m_lProcedura;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sDiagnosi))
		m_sDiagnosi = pSet->m_sDiagnosi.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bEliminato))
		m_bEliminato = pSet->m_bEliminato;
	
	if (IsOpen())
	{
		SetFieldNull (NULL, FALSE);
		SetFieldDirty(NULL, TRUE);
	}
}

void CGruppiPrelieviOldItemSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDGruppoOld", m_lIDGruppoOld);
		RFX_Long(pFX, "Tipo", m_lTipo);
		RFX_Long(pFX, "Organo", m_lOrgano);
		RFX_Text(pFX, "Sede", m_sSede, 50);
		RFX_Text(pFX, "Provette", m_sProvette, 50);
		RFX_Long(pFX, "Procedura", m_lProcedura);
		RFX_Text(pFX, "Diagnosi", m_sDiagnosi, 3999);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CGruppiPrelieviOldItemSet::CreateNew()
{
	return (CBaseSet*)new CGruppiPrelieviOldItemSet;
}

void CGruppiPrelieviOldItemSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CGruppiPrelieviOldItemSet* pIstologiaSet = (CGruppiPrelieviOldItemSet*)pOriginalSet;

	if (!pIstologiaSet->IsOpen() || pIstologiaSet->IsFieldDirty(&pIstologiaSet->m_lIDGruppoOld) || bCopyAll)
		m_lIDGruppoOld = pIstologiaSet->m_lIDGruppoOld;
	if (!pIstologiaSet->IsOpen() || pIstologiaSet->IsFieldDirty(&pIstologiaSet->m_lTipo) || bCopyAll)
		m_lTipo = pIstologiaSet->m_lTipo;
	if (!pIstologiaSet->IsOpen() || pIstologiaSet->IsFieldDirty(&pIstologiaSet->m_lOrgano) || bCopyAll)
		m_lOrgano = pIstologiaSet->m_lOrgano;
	if (!pIstologiaSet->IsOpen() || pIstologiaSet->IsFieldDirty(&pIstologiaSet->m_sSede) || bCopyAll)
		m_sSede = pIstologiaSet->m_sSede;
	if (!pIstologiaSet->IsOpen() || pIstologiaSet->IsFieldDirty(&pIstologiaSet->m_sProvette) || bCopyAll)
		m_sProvette = pIstologiaSet->m_sProvette;
	if (!pIstologiaSet->IsOpen() || pIstologiaSet->IsFieldDirty(&pIstologiaSet->m_lProcedura) || bCopyAll)
		m_lProcedura = pIstologiaSet->m_lProcedura;
	if (!pIstologiaSet->IsOpen() || pIstologiaSet->IsFieldDirty(&pIstologiaSet->m_sDiagnosi) || bCopyAll)
		m_sDiagnosi = pIstologiaSet->m_sDiagnosi;
	if (!pIstologiaSet->IsOpen() || pIstologiaSet->IsFieldDirty(&pIstologiaSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pIstologiaSet->m_bEliminato;
}

void CGruppiPrelieviOldItemSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CGruppiPrelieviOldItemSet* pOV = (CGruppiPrelieviOldItemSet*)pOldValues;
	CGruppiPrelieviOldItemSet* pNV = (CGruppiPrelieviOldItemSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDGruppoOld", pOV, &pOV->m_lIDGruppoOld, pNV, &pNV->m_lIDGruppoOld);
	sp.Execute("Tipo", pOV, &pOV->m_lTipo, pNV, &pNV->m_lTipo);
	sp.Execute("Organo", pOV, &pOV->m_lOrgano, pNV, &pNV->m_lOrgano);
	sp.Execute("Sede", pOV, &pOV->m_sSede, pNV, &pNV->m_sSede);
	sp.Execute("Provette", pOV, &pOV->m_sProvette, pNV, &pNV->m_sProvette);
	sp.Execute("Procedura", pOV, &pOV->m_lProcedura, pNV, &pNV->m_lProcedura);
	sp.Execute("Diagnosi", pOV, &pOV->m_sDiagnosi, pNV, &pNV->m_sDiagnosi);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CGruppiPrelieviOldItemSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CGruppiPrelieviOldItemSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CGruppiPrelieviOldItemSet::DeleteRecordset");
	}
	return bReturn;
}

CString CGruppiPrelieviOldItemSet::SetBaseFilter(const CString &strFilter)
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