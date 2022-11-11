#include "stdafx.h"
#include "Endox.h"
#include "ExtEsamiFasiChiuseSet.h"

#include "DLL_Imaging\h\AmLogin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CExtEsamiFasiChiuseSet, CBaseSet)

CExtEsamiFasiChiuseSet::CExtEsamiFasiChiuseSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 4; // Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
}

CString CExtEsamiFasiChiuseSet::GetDefaultSQL()
{
	return "EXT_ESAMI_FASICHIUSE";
}

void CExtEsamiFasiChiuseSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDFASECHIUSA", m_lIDFaseChiusa);		
		RFX_Long(pFX, "ESEGUITO", m_lEseguito);
		RFX_Text(pFX, "ESITO", m_sEsito); // Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
	}
}

void CExtEsamiFasiChiuseSet::SetEmpty()
{
	m_lID = 0;
	m_lIDFaseChiusa = 0;	
	m_lEseguito = 0;
	m_sEsito; // Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
}

CBaseSet* CExtEsamiFasiChiuseSet::CreateNew()
{
	return (CBaseSet*)new CExtEsamiFasiChiuseSet;
}

void CExtEsamiFasiChiuseSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CExtEsamiFasiChiuseSet* pSet = (CExtEsamiFasiChiuseSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDFaseChiusa) || bCopyAll)
		m_lIDFaseChiusa = pSet->m_lIDFaseChiusa;	
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lEseguito) || bCopyAll)
		m_lEseguito = pSet->m_lEseguito;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sEsito) || bCopyAll) // Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
		m_sEsito = pSet->m_sEsito;
}

void CExtEsamiFasiChiuseSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CExtEsamiFasiChiuseSet* pOV = (CExtEsamiFasiChiuseSet*)pOldValues;
	CExtEsamiFasiChiuseSet* pNV = (CExtEsamiFasiChiuseSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDFASECHIUSA", pOV, &pOV->m_lIDFaseChiusa, pNV, &pNV->m_lIDFaseChiusa);	
	sp.Execute("ESEGUITO", pOV, &pOV->m_lEseguito, pNV, &pNV->m_lEseguito);
	sp.Execute("ESITO", pOV, &pOV->m_sEsito, pNV, &pNV->m_sEsito); // Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
}

BOOL CExtEsamiFasiChiuseSet::DeleteRecordset(const CString &strCommento)
{
	return TRUE;
}

CString CExtEsamiFasiChiuseSet::SetBaseFilter(const CString &strFilter)
{
	CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	return CBaseSet::SetBaseFilter(strNewFilter);
}

long CExtEsamiFasiChiuseSet::Insert(long lIDEsame, long lIDFaseChiusa)
{
	long lReturn = 0;

	if (OpenRecordset("CExtEsamiFasiChiuseSet::Insert"))
	{
		if (AddNewRecordset("CExtEsamiFasiChiuseSet::Insert"))
		{
			lReturn = m_lIDFaseChiusa = lIDFaseChiusa;
			m_sEsito = ""; // Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo

			UpdateRecordset("CExtEsamiFasiChiuseSet::Insert");
		}

		CloseRecordset("CExtEsamiFasiChiuseSet::Insert");
	}

	return lReturn;
}

// Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
void CExtEsamiFasiChiuseSet::DelecaoLogicaExt(long lIDFaseChiusa)
{
	ASSERT(lIDFaseChiusa > 0);

	CString filter;
	filter.Format("IDFaseChiusa=%li", lIDFaseChiusa);

	CExtEsamiFasiChiuseSet set;
	set.SetOpenFilter(filter);
	try
	{
		if (set.OpenRecordset("CEsamiFasiChiuseSet::DelecaoLogicaExt"))
		{
			if (!set.IsEOF())
			{

				if (set.EditRecordset("CEsamiFasiChiuseSet::DelecaoLogicaExt"))
				{
					AMLogin_GetUserID(&m_lIDUtente);
					set.m_lEseguito = 4;
					set.m_sEsito = "TesiCapture-Substituição de laudo solicitada.";
					set.UpdateRecordset("CEsamiFasiChiuseSet::DelecaoLogicaExt");
				}
			}
			CloseRecordset("CEsamiFasiChiuseSet::DelecaoLogicaExt");
		}
	}
	catch (...)
	{
		theApp.AfxMessageBoxEndo("Erro ao anular Liberação de Laudo(EXT).");
	}
}