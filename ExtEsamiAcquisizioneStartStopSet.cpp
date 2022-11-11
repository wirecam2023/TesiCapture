#include "stdafx.h"
#include "Endox.h"
#include "ExtEsamiAcquisizioneStartStopSet.h"
#include "CustomDate.h"

#include "DLL_Imaging\h\AmLogin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CExtEsamiAcquisizioneStartStopSet, CBaseSet)

CExtEsamiAcquisizioneStartStopSet::CExtEsamiAcquisizioneStartStopSet()
: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_nFields = 7;
}

CString CExtEsamiAcquisizioneStartStopSet::GetDefaultSQL()
{
	return "EXT_ESAMI_ACQ_STARTSTOP";
}

void CExtEsamiAcquisizioneStartStopSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDEsame", m_lIDEsame);		
		RFX_Text(pFX, "DataOra", m_sDataOra, 14);
		RFX_Long(pFX, "IDUtente", m_lIDUtente);
		RFX_Long(pFX, "Fase", (long&) m_lFase);		
		RFX_Long(pFX, "Eseguito", m_lEseguito);
		RFX_Text(pFX, "Esito", m_sEsito, 2000000);
	}
}

void CExtEsamiAcquisizioneStartStopSet::SetEmpty()
{
	m_lID = 0;
	m_lIDEsame = 0;	
	m_sDataOra = "";
	m_lIDUtente = 0;
	m_lFase = FaseAcquisizione::start;
	m_lEseguito = IntegrationSendStatus::notSent;
	m_sEsito = "";
}

CBaseSet* CExtEsamiAcquisizioneStartStopSet::CreateNew()
{
	return (CBaseSet*)new CExtEsamiAcquisizioneStartStopSet;
}

void CExtEsamiAcquisizioneStartStopSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CExtEsamiAcquisizioneStartStopSet* pSet = (CExtEsamiAcquisizioneStartStopSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pSet->m_lIDEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDataOra) || bCopyAll)
		m_sDataOra = pSet->m_sDataOra;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDUtente) || bCopyAll)
		m_lIDUtente = pSet->m_lIDUtente;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lFase) || bCopyAll)
		m_lFase = pSet->m_lFase;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lEseguito) || bCopyAll)
		m_lEseguito = pSet->m_lEseguito;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sEsito) || bCopyAll)
		m_sEsito = pSet->m_sEsito;
}

void CExtEsamiAcquisizioneStartStopSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CExtEsamiAcquisizioneStartStopSet* pOV = (CExtEsamiAcquisizioneStartStopSet*)pOldValues;
	CExtEsamiAcquisizioneStartStopSet* pNV = (CExtEsamiAcquisizioneStartStopSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("IDEsame", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("DataOra", pOV, &pOV->m_sDataOra, pNV, &pNV->m_sDataOra);
	sp.Execute("IDUtente", pOV, &pOV->m_lIDUtente, pNV, &pNV->m_lIDUtente);
	sp.Execute("Fase", pOV, (long*)&pOV->m_lFase, pNV, (long*)&pNV->m_lFase);
	sp.Execute("Eseguito", pOV, &pOV->m_lEseguito, pNV, &pNV->m_lEseguito);
	sp.Execute("Esito", pOV, &pOV->m_sEsito, pNV, &pNV->m_sEsito);
}

BOOL CExtEsamiAcquisizioneStartStopSet::DeleteRecordset(const CString &strCommento)
{
	return TRUE;
}

void CExtEsamiAcquisizioneStartStopSet::StartAcquisizione(long lExamId)
{
	ASSERT((lExamId > 0));	

	CBaseSet::SetOpenFilter("ID=0");
	if (OpenRecordset("CExtEsamiAcquisizioneStartStopSet::StartAcquisizione"))
	{
		if (AddNewRecordset("CExtEsamiAcquisizioneStartStopSet::StartAcquisizione"))
		{
			m_lIDEsame = lExamId;
			m_sDataOra = CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M00");
			AMLogin_GetUserID(&m_lIDUtente);
			m_lFase = FaseAcquisizione::start;

			UpdateRecordset("CExtEsamiAcquisizioneStartStopSet::StartAcquisizione");
		}

		CloseRecordset("CExtEsamiAcquisizioneStartStopSet::StartAcquisizione");
	}
}

void CExtEsamiAcquisizioneStartStopSet::StopAcquisizione(long lExamId)
{
	ASSERT((lExamId > 0));

	CBaseSet::SetOpenFilter("ID=0");
	if (OpenRecordset("CExtEsamiAcquisizioneStartStopSet::StopAcquisizione"))
	{
		if (AddNewRecordset("CExtEsamiAcquisizioneStartStopSet::StopAcquisizione"))
		{
			m_lIDEsame = lExamId;
			m_sDataOra = CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M00");
			AMLogin_GetUserID(&m_lIDUtente);
			m_lFase = FaseAcquisizione::stop;

			UpdateRecordset("CExtEsamiAcquisizioneStartStopSet::StopAcquisizione");
		}

		CloseRecordset("CExtEsamiAcquisizioneStartStopSet::StopAcquisizione");
	}
}
