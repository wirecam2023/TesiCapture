#include "stdafx.h"
#include "Endox.h"
#include "RicercaProcTeraSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CRicercaProcTeraSet, CBaseSet)

CRicercaProcTeraSet::CRicercaProcTeraSet()
	: CBaseSet(NULL, "VIEW") // è una vista //
{
	SetSortRecord("DESCR1");

	m_sDescr1 = "";
	m_lLevel2 = 0;
	m_sDescr2 = "";

	m_nFields = 3;
}

void CRicercaProcTeraSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Text (pFX, "Descr1",	m_sDescr1, 255);
	RFX_Long (pFX, "Level2",	m_lLevel2);
	RFX_Text (pFX, "Descr2",	m_sDescr2, 255);
}

CString CRicercaProcTeraSet::GetDefaultSQL()
{
	return "RICERCAPROCTERA";
}

void CRicercaProcTeraSet::SetEmpty()
{
	m_sDescr1 = "";
	m_lLevel2 = 0;
	m_sDescr2 = "";
}