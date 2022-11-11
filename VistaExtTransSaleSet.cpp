#include "stdafx.h"
#include "Endox.h"
#include "VistaExtTransSaleSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaExtTransSaleSet, CBaseSet)

CVistaExtTransSaleSet::CVistaExtTransSaleSet()
	: CBaseSet(NULL, "VIEW")
{
	SetEmpty();
	SetSortRecord("");

	m_nFields = 5;
}

CString CVistaExtTransSaleSet::GetDefaultSQL()
{
	return "VISTAEXTTRANSSALE";
}

void CVistaExtTransSaleSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "idSalaEndox", m_lidSalaEndox);
	RFX_Long(pFX, "idSedeEndox", m_lidSedeEndox);
	RFX_Text(pFX, "codiceSedeEst", m_sCodiceSalaEst, 50);
	RFX_Text(pFX, "descrizione", m_sDescrizione, 50);
	RFX_Long(pFX, "idUO", m_lUO);
}

void CVistaExtTransSaleSet::SetEmpty()
{
	m_lidSalaEndox = 0;
	m_lidSedeEndox = 0;
	m_sCodiceSalaEst = "";
	m_sDescrizione = "";
	m_lUO = 0;
}

