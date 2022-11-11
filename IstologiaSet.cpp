#include "stdafx.h"
#include "Endox.h"
#include "IstologiaSet.h"

#include "IstologiaTipiSet.h"
#include "MstOrganoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CIstologiaSet, CBaseSet)

CIstologiaSet::CIstologiaSet()
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 9;
}

CString CIstologiaSet::GetDefaultSQL()
{
	return "EISTOLOGIA";
}

void CIstologiaSet::SetEmpty()
{
	m_lContatore = 0;
	m_lEsame = 0;
	m_lTipo = 0;
	m_lOrgano = -1;
	m_sSede = "";
	m_sProvette = "";
	m_lProcedura = 0;
	m_sDiagnosi = "";
	m_bEliminato = FALSE;
}

void CIstologiaSet::CopyFieldFrom(CIstologiaSet* pSet)
{
	SetEmpty();

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lContatore))
		m_lContatore = pSet->m_lContatore;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lEsame))
		m_lEsame = pSet->m_lEsame;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lTipo))
		m_lTipo = pSet->m_lTipo;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lOrgano))
		m_lOrgano = pSet->m_lOrgano;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sSede))
		m_sSede = pSet->m_sSede.Left(50);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sProvette))
		m_sProvette = pSet->m_sProvette.Left(10);
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

void CIstologiaSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Contatore", m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "Esame", m_lEsame);
		RFX_Long(pFX, "Tipo", m_lTipo);
		RFX_Long(pFX, "Organo", m_lOrgano);
		RFX_Text(pFX, "Sede", m_sSede, 50);
		RFX_Text(pFX, "Provette", m_sProvette, 50);
		RFX_Long(pFX, "Procedura", m_lProcedura);
		RFX_Text(pFX, "Diagnosi", m_sDiagnosi, 3999);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
	}
}

CString CIstologiaSet::GetEseguitoPrelievo(long lEsame)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Esame=%li", lEsame);

	SetOpenFilter(strFilter);
	OpenRecordset("CIstologiaSet::GetFieldText");
	if (!IsEOF())
		strReturn = theApp.GetMessageString(IDS_ESEGUITOPRELIEVO);
	CloseRecordset("CIstologiaSet::GetFieldText");

	return strReturn;
}

void CIstologiaSet::GetFieldText(CString& sReturn, long lEsame)
{
	CString strFilter;
	strFilter.Format("Esame=%li", lEsame);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CIstologiaSet::GetFieldText"))
	{
		while(!IsEOF())
		{
			if (!sReturn.IsEmpty())
				sReturn += "\n";

			sReturn += CIstologiaTipiSet().GetDescrizione(m_lTipo) + " " + CMstOrganoSet().GetFieldText(m_lOrgano) + " " + m_sSede + " " + m_sDiagnosi;

			MoveNext();
		}
		CloseRecordset("CIstologiaSet::GetFieldText");
	}
}

CBaseSet* CIstologiaSet::CreateNew()
{
	return (CBaseSet*)new CIstologiaSet;
}

void CIstologiaSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CIstologiaSet* pIstologiaSet = (CIstologiaSet*)pOriginalSet;

	if (!pIstologiaSet->IsOpen() || pIstologiaSet->IsFieldDirty(&pIstologiaSet->m_lEsame) || bCopyAll)
		m_lEsame = pIstologiaSet->m_lEsame;
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

void CIstologiaSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CIstologiaSet* pOV = (CIstologiaSet*)pOldValues;
	CIstologiaSet* pNV = (CIstologiaSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Esame", pOV, &pOV->m_lEsame, pNV, &pNV->m_lEsame);
	sp.Execute("Tipo", pOV, &pOV->m_lTipo, pNV, &pNV->m_lTipo);
	sp.Execute("Organo", pOV, &pOV->m_lOrgano, pNV, &pNV->m_lOrgano);
	sp.Execute("Sede", pOV, &pOV->m_sSede, pNV, &pNV->m_sSede);
	sp.Execute("Provette", pOV, &pOV->m_sProvette, pNV, &pNV->m_sProvette);
	sp.Execute("Procedura", pOV, &pOV->m_lProcedura, pNV, &pNV->m_lProcedura);
	sp.Execute("Diagnosi", pOV, &pOV->m_sDiagnosi, pNV, &pNV->m_sDiagnosi);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CIstologiaSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CIstologiaSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CIstologiaSet::DeleteRecordset");
	}
	return bReturn;
}

CString CIstologiaSet::SetBaseFilter(const CString &strFilter)
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