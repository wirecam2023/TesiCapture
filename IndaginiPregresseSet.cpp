#include "stdafx.h"
#include "Endox.h"
#include "IndaginiPregresseSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CIndaginiPregresseSet, CBaseSet)

CIndaginiPregresseSet::CIndaginiPregresseSet()
	: CBaseSet(&m_lContatore, "CONTATORE")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 5;
}

CString CIndaginiPregresseSet::GetDefaultSQL()
{
	return "EINDAGINIPREGRESSE";
}

void CIndaginiPregresseSet::SetEmpty()
{
	m_lContatore = 0;
	m_lEsame = 0;
	m_lPatologico = 0;
	m_sIndagine = "";
	m_bEliminato = FALSE;
}

void CIndaginiPregresseSet::CopyFieldFrom(CIndaginiPregresseSet* pSet)
{
	SetEmpty();

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lContatore))
		m_lContatore	= pSet->m_lContatore;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lEsame))
		m_lEsame	= pSet->m_lEsame;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lPatologico))
		m_lPatologico = pSet->m_lPatologico;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sIndagine))
		m_sIndagine = pSet->m_sIndagine.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bEliminato))
		m_bEliminato = pSet->m_bEliminato;

	if (IsOpen())
	{
		SetFieldNull (NULL, FALSE);
		SetFieldDirty(NULL, TRUE);
	}
}

void CIndaginiPregresseSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long (pFX, "Contatore", m_lContatore);
	if (m_nFields > 1)
	{
		RFX_Long (pFX, "Esame", m_lEsame);
		RFX_Long (pFX, "Patologico", m_lPatologico);
		RFX_Text (pFX, "Indagine", m_sIndagine, 3999);
		RFX_Bool (pFX, "Eliminato", m_bEliminato);
	}
}

CBaseSet* CIndaginiPregresseSet::CreateNew()
{
	return (CBaseSet*)new CIndaginiPregresseSet;
}

void CIndaginiPregresseSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CIndaginiPregresseSet* pIndaginiPregresseSet = (CIndaginiPregresseSet*)pOriginalSet;

	if (!pIndaginiPregresseSet->IsOpen() || pIndaginiPregresseSet->IsFieldDirty(&pIndaginiPregresseSet->m_lEsame) || bCopyAll)
		m_lEsame = pIndaginiPregresseSet->m_lEsame;
	if (!pIndaginiPregresseSet->IsOpen() || pIndaginiPregresseSet->IsFieldDirty(&pIndaginiPregresseSet->m_lPatologico) || bCopyAll)
		m_lPatologico = pIndaginiPregresseSet->m_lPatologico;
	if (!pIndaginiPregresseSet->IsOpen() || pIndaginiPregresseSet->IsFieldDirty(&pIndaginiPregresseSet->m_sIndagine) || bCopyAll)
		m_sIndagine = pIndaginiPregresseSet->m_sIndagine;
	if (!pIndaginiPregresseSet->IsOpen() || pIndaginiPregresseSet->IsFieldDirty(&pIndaginiPregresseSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pIndaginiPregresseSet->m_bEliminato;
}

void CIndaginiPregresseSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CIndaginiPregresseSet* pOV = (CIndaginiPregresseSet*)pOldValues;
	CIndaginiPregresseSet* pNV = (CIndaginiPregresseSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("Esame", pOV, &pOV->m_lEsame, pNV, &pNV->m_lEsame);
	sp.Execute("Patologico", pOV, &pOV->m_lPatologico, pNV, &pNV->m_lPatologico);
	sp.Execute("Indagine", pOV, &pOV->m_sIndagine, pNV, &pNV->m_sIndagine);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
}

BOOL CIndaginiPregresseSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CIndaginiPregresseSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CIndaginiPregresseSet::DeleteRecordset");
	}
	return bReturn;
}

CString CIndaginiPregresseSet::SetBaseFilter(const CString &strFilter)
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