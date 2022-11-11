#include "stdafx.h"
#include "Endox.h"
#include "ExtPatientEventSet.h"

#include "CustomDate.h"
#include "DLL_Imaging\h\AmLogin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CExtPatientEventSet, CBaseSet)

CExtPatientEventSet::CExtPatientEventSet() :
CBaseSet(&m_lId, "ID")
{
	SetEmpty();

	m_nFields = 5;
	SetBaseFilter("");
}

CExtPatientEventSet::~CExtPatientEventSet()
{
}

CString CExtPatientEventSet::GetDefaultSQL()
{
	return "ext_patientevent";
}

void CExtPatientEventSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lId);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "patientId", m_lPatientId);
		RFX_Long(pFX, "eventType", m_lEventType);
		RFX_Text(pFX, "dateTime", m_sDateTime, 14);
		RFX_Long(pFX, "userId", m_lUserId);
	}
}

void CExtPatientEventSet::SetEmpty()
{
	m_lId = 0;
	m_lPatientId = 0;
	m_lEventType = 0;
	m_sDateTime = "";
	m_lUserId = 0;
}

CBaseSet* CExtPatientEventSet::CreateNew()
{
	return (CBaseSet*) new CExtPatientEventSet;
}

void CExtPatientEventSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CExtPatientEventSet* pSet = (CExtPatientEventSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lPatientId) || bCopyAll)
		m_lPatientId = pSet->m_lPatientId;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lEventType) || bCopyAll)
		m_lEventType = pSet->m_lEventType;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDateTime) || bCopyAll)
		m_sDateTime = pSet->m_sDateTime;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lUserId) || bCopyAll)
		m_lUserId = pSet->m_lUserId;
}

void CExtPatientEventSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CExtPatientEventSet* pOV = (CExtPatientEventSet*)pOldValues;
	CExtPatientEventSet* pNV = (CExtPatientEventSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	sp.Execute("patientId", pOV, &pOV->m_lPatientId, pNV, &pNV->m_lPatientId);
	sp.Execute("eventType", pOV, &pOV->m_lEventType, pNV, &pNV->m_lEventType);
	sp.Execute("dateTime", pOV, &pOV->m_sDateTime, pNV, &pNV->m_sDateTime);
	sp.Execute("userId", pOV, &pOV->m_lUserId, pNV, &pNV->m_lUserId);
}

BOOL CExtPatientEventSet::AddEvent(long patientId, long eventType)
{
	BOOL bReturn = FALSE;	

	SetOpenFilter("ID = 0");
	if (OpenRecordset("CExtPatientEventSet::AddEvent"))
	{
		if (AddNewRecordset("CExtPatientEventSet::AddEvent"))
		{
			m_lPatientId = patientId;
			m_sDateTime = CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M%S");
			AMLogin_GetUserID(&m_lUserId);
			m_lEventType = eventType;

			if (UpdateRecordset("CExtPatientEventSet::AddEvent"))
				bReturn = TRUE;
		}

		CloseRecordset("CExtPatientEventSet::AddEvent");
	}

	return bReturn;
}