#include "stdafx.h"
#include "Endox.h"
#include "VistaSnomedSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaSnomedSet, CBaseSet)

CVistaSnomedSet::CVistaSnomedSet()
	: CBaseSet(NULL, "VIEW")
{
	SetSortRecord("Codice");

	SetEmpty();

	m_nFields = 2;
}

CString CVistaSnomedSet::GetDefaultSQL()
{
	return "VistaSnomed";
}

void CVistaSnomedSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Text(pFX, "Codice",	m_sCodice, 10);
	RFX_Text(pFX, "Descrizione", m_sDescrizione, 120);
}

void CVistaSnomedSet::SetEmpty()
{
	m_sCodice = "";
	m_sDescrizione = "";
}