#include "stdafx.h"
#include "Endox.h"
#include "ExtVideocapsuleSet.h"
#include "CustomDate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CExtEsamiVideocapsulaSet, CBaseSet)

CExtEsamiVideocapsulaSet::CExtEsamiVideocapsulaSet()
: CBaseSet(&m_lId, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

CString CExtEsamiVideocapsulaSet::GetDefaultSQL()
{
	return "EXT_ESAMI_VIDEOCAPSULA";
}

void CExtEsamiVideocapsulaSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lId);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IdEsame", m_lIdEsame);
		RFX_Long(pFX, "IdUtente", m_lIdUtente);
		RFX_Text(pFX, "DataOra", m_sDataOra, 14);
		RFX_Bool(pFX, "Eseguito", m_bEseguito);
		RFX_Text(pFX, "Esito", m_sEsito, 2000000);
	}
}

void CExtEsamiVideocapsulaSet::SetEmpty()
{
	m_lId=0;
	m_lIdEsame=0;
	m_lIdUtente=0;
	m_sDataOra="";
	m_bEseguito=FALSE;
	m_sEsito="";
}

CBaseSet* CExtEsamiVideocapsulaSet::CreateNew()
{
	return (CBaseSet*)new CExtEsamiVideocapsulaSet;
}

void CExtEsamiVideocapsulaSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CExtEsamiVideocapsulaSet* pExtVideocapsule = (CExtEsamiVideocapsulaSet*)pOriginalSet;

	if (!pExtVideocapsule->IsOpen() || pExtVideocapsule->IsFieldDirty(&pExtVideocapsule->m_lIdEsame) || bCopyAll)
		m_lIdEsame = pExtVideocapsule->m_lIdEsame;
	if (!pExtVideocapsule->IsOpen() || pExtVideocapsule->IsFieldDirty(&pExtVideocapsule->m_lIdUtente) || bCopyAll)
		m_lIdUtente = pExtVideocapsule->m_lIdUtente;
	if (!pExtVideocapsule->IsOpen() || pExtVideocapsule->IsFieldDirty(&pExtVideocapsule->m_sDataOra) || bCopyAll)
		m_sDataOra = pExtVideocapsule->m_sDataOra;
	if (!pExtVideocapsule->IsOpen() || pExtVideocapsule->IsFieldDirty(&pExtVideocapsule->m_bEseguito) || bCopyAll)
		m_bEseguito = pExtVideocapsule->m_bEseguito;
	if (!pExtVideocapsule->IsOpen() || pExtVideocapsule->IsFieldDirty(&pExtVideocapsule->m_sEsito) || bCopyAll)
		m_sEsito = pExtVideocapsule->m_sEsito;
}

void CExtEsamiVideocapsulaSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CExtEsamiVideocapsulaSet* pOV = (CExtEsamiVideocapsulaSet*)pOldValues;
	CExtEsamiVideocapsulaSet* pNV = (CExtEsamiVideocapsulaSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IdEsame", pOV, &pOV->m_lIdEsame, pNV, &pNV->m_lIdEsame);
	sp.Execute("IdUtente", pOV, &pOV->m_lIdUtente, pNV, &pNV->m_lIdUtente);
	sp.Execute("DataOra", pOV, &pOV->m_sDataOra, pNV, &pNV->m_sDataOra);	
	sp.Execute("Eseguito", pOV, &pOV->m_bEseguito, pNV, &pNV->m_bEseguito);
	sp.Execute("Esito", pOV, &pOV->m_sEsito, pNV, &pNV->m_sEsito);
}

CString CExtEsamiVideocapsulaSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	return CBaseSet::SetBaseFilter(strNewFilter);
}

BOOL CExtEsamiVideocapsulaSet::DeleteRecordset(const CString &strCommento)
{
	return TRUE;
}

long CExtEsamiVideocapsulaSet::InserisciRecord(	long idEsame,
											long idUtenteInvio)
{
	ASSERT(idEsame > 0 && idUtenteInvio > 0);

	CBaseSet::SetBaseFilter("");

	if (OpenRecordset("CExtEsamiVideocapsulaSet::InserisciRecord"))
	{
		if (AddNewRecordset("CExtEsamiVideocapsulaSet::InserisciRecord"))
		{
			m_lIdEsame = idEsame;
			m_lIdUtente = idUtenteInvio;
			CCustomDate	DataOggi(TRUE, TRUE);
			m_sDataOra = DataOggi.GetDate("%Y%m%d%H%M00");			

			UpdateRecordset("CExtEsamiVideocapsulaSet::InserisciRecord");
		}

		CloseRecordset("CExtEsamiVideocapsulaSet::InserisciRecord");
	}

	return GetLastAdd();
}
