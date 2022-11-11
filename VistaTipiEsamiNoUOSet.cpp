#include "stdafx.h"
#include "Endox.h"
#include "VistaTipiEsamiNoUOSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaTipiEsamiNoUOSet, CBaseSet)

CVistaTipiEsamiNoUOSet::CVistaTipiEsamiNoUOSet()
	: CBaseSet(NULL, "VIEW")
{
	SetEmpty();
	SetSortRecord("DescrizioneUO, DescrizioneTipoEsame, Contatore");

	m_nFields = 4;
}

CString CVistaTipiEsamiNoUOSet::GetDefaultSQL()
{
	return "VistaTipiEsamiNoUO";
}

void CVistaTipiEsamiNoUOSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Contatore",	m_lContatore);
	RFX_Text(pFX, "DescrizioneUO", m_sDescrizioneUO, 255);
	RFX_Text(pFX, "DescrizioneTipoEsame", m_sDescrizioneTipoEsame, 255);
	RFX_Long(pFX, "UO", m_lUO);
}

void CVistaTipiEsamiNoUOSet::SetEmpty()
{
	m_lContatore = 0;
	m_sDescrizioneUO = "";
	m_sDescrizioneTipoEsame = "";
	m_lUO = 0;
}