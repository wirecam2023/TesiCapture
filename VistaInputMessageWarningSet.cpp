#include "stdafx.h"
#include "Endox.h"
#include "VistaInputMessageWarningSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaInputMessageWarningSet, CBaseSet)

CVistaInputMessageWarningSet::CVistaInputMessageWarningSet()
: CBaseSet(NULL, "VIEW")
{
	SetBaseFilter("");

	SetSortRecord("id,storetime");

	m_nFields = 6;

}

CVistaInputMessageWarningSet::~CVistaInputMessageWarningSet()
{
}

CString CVistaInputMessageWarningSet::GetDefaultSQL()
{
	return "VIEW_EXT_INPUTMSG_WARNINGS";
}

void CVistaInputMessageWarningSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "id", m_lId);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "messageId", m_sMessageId, 50);		
		RFX_Text(pFX, "appSender", m_sAppSender, 50);		
		RFX_Text(pFX, "storeTime", m_sStoreTime, 14);
		RFX_Text(pFX, "encodedMessage", m_sEncodedMessage, 10000000);
		RFX_Text(pFX, "warningMessage", m_sWarningMessage, 10000000);
		
	}
}

