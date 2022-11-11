#include "stdafx.h"
#include "Endox.h"
#include "DiagnosiSet.h"

#include "MstOrganoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CDiagnosiSet, CBaseSet)

CDiagnosiSet::CDiagnosiSet()
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

CString CDiagnosiSet::GetDefaultSQL()
{
	return "EDiagnosi";
}

void CDiagnosiSet::SetEmpty()
{
	m_lContatore	= 0;
	m_lEsame		= 0;
	m_lOrgano		= -1;
	m_sSede			= "";
	m_sDiagnosi		= "";
	m_bEliminato    = FALSE;
}

void CDiagnosiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long (pFX, "Contatore",		m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Long (pFX, "Esame",			m_lEsame);
		RFX_Long (pFX, "Organo",		m_lOrgano);
		RFX_Text (pFX, "Sede",			m_sSede,		 255);
		RFX_Text (pFX, "Diagnosi",		m_sDiagnosi,	3999);
		RFX_Bool (pFX, "Eliminato",     m_bEliminato);
	}
}

void CDiagnosiSet::CopyFieldFrom(CDiagnosiSet* pSet)
{
	SetEmpty();

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lContatore))
		m_lContatore = pSet->m_lContatore;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lEsame))
		m_lEsame = pSet->m_lEsame;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lOrgano))
		m_lOrgano = pSet->m_lOrgano;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sSede))
		m_sSede = pSet->m_sSede.Left(255);
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

CBaseSet* CDiagnosiSet::CreateNew()
{
	return (CBaseSet*)new CDiagnosiSet;
}

void CDiagnosiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CDiagnosiSet* pDiagnosiSet = (CDiagnosiSet*)pOriginalSet;

	if (!pDiagnosiSet->IsOpen() || pDiagnosiSet->IsFieldDirty(&pDiagnosiSet->m_lEsame) || bCopyAll)
		m_lEsame = pDiagnosiSet->m_lEsame;
	if (!pDiagnosiSet->IsOpen() || pDiagnosiSet->IsFieldDirty(&pDiagnosiSet->m_lOrgano) || bCopyAll)
		m_lOrgano = pDiagnosiSet->m_lOrgano;
	if (!pDiagnosiSet->IsOpen() || pDiagnosiSet->IsFieldDirty(&pDiagnosiSet->m_sSede) || bCopyAll)
		m_sSede = pDiagnosiSet->m_sSede;
	if (!pDiagnosiSet->IsOpen() || pDiagnosiSet->IsFieldDirty(&pDiagnosiSet->m_sDiagnosi) || bCopyAll)
		m_sDiagnosi = pDiagnosiSet->m_sDiagnosi;
	if (!pDiagnosiSet->IsOpen() || pDiagnosiSet->IsFieldDirty(&pDiagnosiSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pDiagnosiSet->m_bEliminato;
}

CString CDiagnosiSet::GetDiagnosi(long lEsame)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Esame=%li", lEsame);

	SetBaseFilter(strFilter);
	SetSortRecord("Contatore");

	if (OpenRecordset("CDiagnosiSet::GetDiagnosi"))
	{
		CMstOrganoSet setOrg;

		while(!IsEOF())
		{
			if (!strReturn.IsEmpty())
				strReturn += "\n";

			strReturn += setOrg.GetFieldText(m_lOrgano);

			if (!m_sSede.IsEmpty())
				strReturn += (" " + m_sSede);

			if (!m_sDiagnosi.IsEmpty())
				strReturn += (": " + m_sDiagnosi);

			MoveNext();
		}

		CloseRecordset("CDiagnosiSet::GetDiagnosi");
	}

	return strReturn;
}

void CDiagnosiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CDiagnosiSet* pOV = (CDiagnosiSet*)pOldValues;
	CDiagnosiSet* pNV = (CDiagnosiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Esame", pOV, &pOV->m_lEsame, pNV, &pNV->m_lEsame);
	sp.Execute("Organo", pOV, &pOV->m_lOrgano, pNV, &pNV->m_lOrgano);
	sp.Execute("Sede", pOV, &pOV->m_sSede, pNV, &pNV->m_sSede);
	sp.Execute("Diagnosi", pOV, &pOV->m_sDiagnosi, pNV, &pNV->m_sDiagnosi);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CDiagnosiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CDiagnosiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CDiagnosiSet::DeleteRecordset");
	}
	return bReturn;
}

CString CDiagnosiSet::SetBaseFilter(const CString &strFilter)
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