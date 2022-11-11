#include "stdafx.h"
#include "Endox.h"
#include "ListaSnomedSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CListaSnomedSet, CBaseSet)

CListaSnomedSet::CListaSnomedSet()
	: CBaseSet(NULL, "VIEW") // è una vista //
{
	SetEmpty();
	SetSortRecord("IDPAZIENTE, IDESAME");

	m_nFields = 5;
}

CListaSnomedSet::~CListaSnomedSet()
{
}

void CListaSnomedSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "IDPaziente", m_lIDPaziente);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDEsame",		m_lIDEsame);
		RFX_Long(pFX, "Data",			m_lData);
		RFX_Text(pFX, "Codici",			m_sCodici,		 36);
		RFX_Text(pFX, "Descrizioni",	m_sDescrizioni,	366);
	}
}

CString CListaSnomedSet::GetDefaultSQL()
{
	return "ELISTASNOMED";
}

void CListaSnomedSet::SetEmpty()
{
	m_lIDPaziente = 0;
	m_lIDEsame = 0;
	m_lData = 0;
	m_sCodici = "";
	m_sDescrizioni = "";
}