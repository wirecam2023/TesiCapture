#include "stdafx.h"
#include "Endox.h"
#include "VistaOutputMessageSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaOutputMessageSet, CBaseSet)

CVistaOutputMessageSet::CVistaOutputMessageSet()
: CBaseSet(NULL, "VIEW")
{
	SetBaseFilter("");

	SetSortRecord("storetime,appreceiver");

	m_nFields = 12;

}

CVistaOutputMessageSet::~CVistaOutputMessageSet()
{
}

CString CVistaOutputMessageSet::GetDefaultSQL()
{
	return "VIEW_EXT_OUTPUTMESSAGES_ALL";
}

void CVistaOutputMessageSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Text(pFX, "MessageId", m_sMessageId, 50);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "appReceiver", m_sAppReceiver, 50);
		RFX_Text(pFX, "rawMessage", m_sRawMessage, 10000000);
		RFX_Text(pFX, "storeTime", m_sStoreTime, 50);
		RFX_Text(pFX, "Response", m_sResponseMessage, 10000000);
		RFX_Text(pFX, "ErrorMessage", m_sErrorMessage, 10000000);
		RFX_Bool(pFX, "Error", m_bErrored);
		RFX_Text(pFX, "EndoxTable", m_sEndoxTable, 50);
		RFX_Text(pFX, "TableKey", m_sTableKey, 50);	
		RFX_Long(pFX, "KeyValue", m_lKeyValue);
		RFX_Text(pFX, "FlagName", m_sFlagName, 50);
		RFX_Long(pFX, "FlagValue", m_lFlagValue);
	}
}

