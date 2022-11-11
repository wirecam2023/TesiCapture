#include "stdafx.h"
#include "Endox.h"
#include "InputMessageSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CInputMessageSet, CBaseSet)

CInputMessageSet::CInputMessageSet()
: CBaseSet(NULL, "VIEW")
{
	SetBaseFilter("");

	SetSortRecord("storetime,appsender");	

	m_nFields = 8;

}

CInputMessageSet::~CInputMessageSet()
{
}

CString CInputMessageSet::GetDefaultSQL()
{
	return "EXT_INPUTMSG";
}

void CInputMessageSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Id", m_lId);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "storeTime", m_sStoreTime, 50);
		RFX_Text(pFX, "messageId", m_sMessageId, 50);
		RFX_Text(pFX, "appSender", m_sAppSender, 50);
		RFX_Text(pFX, "encodedMessage", m_sEncodedMessage, 10000000);
		RFX_Text(pFX, "SynchronousResponse", m_sSynchronousMessage, 10000000);
		RFX_Text(pFX, "ErrorMessage", m_sErrorMessage, 10000000);
		RFX_Bool(pFX, "Errored", m_bErrored);		
	}
}

