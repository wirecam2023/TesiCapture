#include "stdafx.h"
#include "Endox.h"
#include "ExtOrdiniAllegatiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CExtOrdiniAllegatiSet, CBaseSet)

CExtOrdiniAllegatiSet::CExtOrdiniAllegatiSet()
: CBaseSet(NULL, "VIEW")
{
	SetSortRecord("IDRICHIESTA");

	m_nFields = 4;
}

CExtOrdiniAllegatiSet::~CExtOrdiniAllegatiSet()
{
}

CString CExtOrdiniAllegatiSet::GetDefaultSQL()
{
	return "EXT_ORDINI_ALLEGATI";
}

void CExtOrdiniAllegatiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDRichiesta", m_lIDRichiesta);
		RFX_Text(pFX, "path", m_sPath, 4000);	
		RFX_Text(pFX, "descrizione", m_sDescrizione, 255);
	}
}