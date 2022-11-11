#include "stdafx.h"
#include "CustomDate.h"
#include "Endox.h"
#include "ExtEsameMediciRichiedenteSet.h"

#include "DLL_Imaging\h\AmLogin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CExtEsameMediciRichiedenteSet, CBaseSet)

CExtEsameMediciRichiedenteSet::CExtEsameMediciRichiedenteSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

CString CExtEsameMediciRichiedenteSet::GetDefaultSQL()
{
	return "EXT_ESAME_MEDICI_RICHIEDENTE";
}

void CExtEsameMediciRichiedenteSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDESAME", m_lIDEsame);		
		RFX_Text(pFX, "DATAORA", m_sDataOra, 14);
		RFX_Long(pFX, "IDUTENTE", m_lIDUtente);
		RFX_Long(pFX, "ESEGUITO", m_lEseguito);
		RFX_Text(pFX, "ESITO", m_sEsito, 2000000);
	}
}

void CExtEsameMediciRichiedenteSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_lIDUtente = 0;
	m_lEseguito = 0;
	m_sEsito = "";
	m_sDataOra = "";
}

CBaseSet* CExtEsameMediciRichiedenteSet::CreateNew()
{
	return (CBaseSet*)new CExtEsameMediciRichiedenteSet;
}

void CExtEsameMediciRichiedenteSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CExtEsameMediciRichiedenteSet* pSet = (CExtEsameMediciRichiedenteSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pSet->m_lIDEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDUtente) || bCopyAll)
		m_lIDUtente = pSet->m_lIDUtente;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDataOra) || bCopyAll)
		m_sDataOra = pSet->m_sDataOra;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lEseguito) || bCopyAll)
		m_lEseguito = pSet->m_lEseguito;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sEsito) || bCopyAll)
		m_sEsito = pSet->m_sEsito;
}

void CExtEsameMediciRichiedenteSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CExtEsameMediciRichiedenteSet* pOV = (CExtEsameMediciRichiedenteSet*)pOldValues;
	CExtEsameMediciRichiedenteSet* pNV = (CExtEsameMediciRichiedenteSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDESAME", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("IDUTENTE", pOV, &pOV->m_lIDUtente, pNV, &pNV->m_lIDUtente);
	sp.Execute("ESEGUITO", pOV, &pOV->m_lEseguito, pNV, &pNV->m_lEseguito);
	sp.Execute("DATAORA", pOV, &pOV->m_sDataOra, pNV, &pNV->m_sDataOra);
	sp.Execute("ESITO", pOV, &pOV->m_sEsito, pNV, &pNV->m_sEsito);
}

BOOL CExtEsameMediciRichiedenteSet::DeleteRecordset(const CString &strCommento)
{
	return TRUE;
}

CString CExtEsameMediciRichiedenteSet::SetBaseFilter(const CString &strFilter)
{
	CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	return CBaseSet::SetBaseFilter(strNewFilter);
}

long CExtEsameMediciRichiedenteSet::Insert(long lIDEsame)
{
	long lReturn = 0;

	if (OpenRecordset("CExtEsameMediciRichiedenteSet::Insert"))
	{
		if (AddNewRecordset("CExtEsameMediciRichiedenteSet::Insert"))
		{
			m_lIDEsame = lIDEsame;
			m_sDataOra = CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M00");
			AMLogin_GetUserID(&m_lIDUtente);
			m_lEseguito = 0;
			m_sEsito = ""; 

			if (UpdateRecordset("CExtEsameMediciRichiedenteSet::Insert"))
				lReturn = GetLastAdd();
		}

		CloseRecordset("CExtEsameMediciRichiedenteSet::Insert");
	}
	return lReturn;
}