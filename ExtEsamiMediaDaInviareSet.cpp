#include "stdafx.h"
#include "Endox.h"

#include "ExtEsamiMediaDaInviareSet.h"
#include "CustomDate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CExtEsamiMediaDaInviareSet, CBaseSet)

CExtEsamiMediaDaInviareSet::CExtEsamiMediaDaInviareSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 6;
}

CString CExtEsamiMediaDaInviareSet::GetDefaultSQL()
{
	return "EXT_ESAMI_MEDIADAINVIARE";
}

void CExtEsamiMediaDaInviareSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDEsame", m_lIDEsame);
		RFX_Text(pFX, "DataOra", m_sDataOra, 14);
		RFX_Long(pFX, "TipoMedia", m_lTipoMedia);
		RFX_Long(pFX, "Eseguito", m_lEseguito);
		RFX_Text(pFX, "Esito", m_sEsito, 2000000);
	}
}

void CExtEsamiMediaDaInviareSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;
	m_sDataOra = "";
	m_lTipoMedia = -1;
	m_lEseguito = IntegrationSendStatus::notSent;
	m_sEsito = "";
}

CBaseSet* CExtEsamiMediaDaInviareSet::CreateNew()
{
	return (CBaseSet*)new CExtEsamiMediaDaInviareSet;
}

void CExtEsamiMediaDaInviareSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CExtEsamiMediaDaInviareSet* pEsamiMI = (CExtEsamiMediaDaInviareSet*)pOriginalSet;

	if (!pEsamiMI->IsOpen() || pEsamiMI->IsFieldDirty(&pEsamiMI->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pEsamiMI->m_lIDEsame;
	if (!pEsamiMI->IsOpen() || pEsamiMI->IsFieldDirty(&pEsamiMI->m_sDataOra) || bCopyAll)
		m_sDataOra = pEsamiMI->m_sDataOra;
	if (!pEsamiMI->IsOpen() || pEsamiMI->IsFieldDirty(&pEsamiMI->m_lTipoMedia) || bCopyAll)
		m_lTipoMedia = pEsamiMI->m_lTipoMedia;
	if (!pEsamiMI->IsOpen() || pEsamiMI->IsFieldDirty(&pEsamiMI->m_lEseguito) || bCopyAll)
		m_lEseguito = pEsamiMI->m_lEseguito;
	if (!pEsamiMI->IsOpen() || pEsamiMI->IsFieldDirty(&pEsamiMI->m_sEsito) || bCopyAll)
		m_sEsito = pEsamiMI->m_sEsito;
	
}

void CExtEsamiMediaDaInviareSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CExtEsamiMediaDaInviareSet* pOV = (CExtEsamiMediaDaInviareSet*)pOldValues;
	CExtEsamiMediaDaInviareSet* pNV = (CExtEsamiMediaDaInviareSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("m_lIDEsame", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("DataOra", pOV, &pOV->m_sDataOra, pNV, &pNV->m_sDataOra);
	sp.Execute("TipoMedia", pOV, &pOV->m_lTipoMedia, pNV, &pNV->m_lTipoMedia);
	sp.Execute("Eseguito", pOV, &pOV->m_lEseguito, pNV, &pNV->m_lEseguito);
	sp.Execute("Esito", pOV, &pOV->m_sEsito, pNV, &pNV->m_sEsito);
}

BOOL CExtEsamiMediaDaInviareSet::DeleteRecordset(const CString &strCommento)
{
	return TRUE;
}

BOOL CExtEsamiMediaDaInviareSet::InsertExam(long examId, long mediaType)
{
	BOOL bReturn = FALSE;

	if (OpenRecordset("CExtEsamiMediaDaInviareSet::InsertExam"))
	{
		if (AddNewRecordset("CExtEsamiMediaDaInviareSet::InsertExam"))
		{
			m_lIDEsame = examId;
			m_sDataOra = CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M00");
			m_lTipoMedia = mediaType;
			if (UpdateRecordset("CExtEsamiMediaDaInviareSet::InsertExam"))
				bReturn = TRUE;

		}
		CloseRecordset("CExtEsamiMediaDaInviareSet::InsertExam");
	}

	return bReturn;
}