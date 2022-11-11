#include "stdafx.h"
#include "Endox.h"
#include "ListaCodificaDiagnosiEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CListaCodificaDiagnosiEsameSet, CBaseSet)

CListaCodificaDiagnosiEsameSet::CListaCodificaDiagnosiEsameSet()
	: CBaseSet(NULL, "VIEW") // è una vista //
{
	SetEmpty();
	SetSortRecord("IDPAZIENTE, IDESAME");

	m_nFields = 6;
}

CListaCodificaDiagnosiEsameSet::~CListaCodificaDiagnosiEsameSet()
{
}

void CListaCodificaDiagnosiEsameSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "IDPaziente", m_lIDPaziente);
	if (m_nFields > 1)
	{
		RFX_Long(pFX, "IDEsame",	m_lIDEsame);
		RFX_Long(pFX, "Data",		m_lData);
		RFX_Text(pFX, "Organo",		m_sOrgano,		 255);
		RFX_Text(pFX, "Sede",		m_sSede,		 255);
		RFX_Text(pFX, "Diagnosi",	m_sDiagnosi,	3999);
	}
}

CString CListaCodificaDiagnosiEsameSet::GetDefaultSQL()
{
	return "ELISTACODIFICADIAGNOSIESAME";
}

void CListaCodificaDiagnosiEsameSet::SetEmpty()
{
	m_lIDPaziente = 0;
	m_lIDEsame = 0;
	m_lData = 0;
	m_sOrgano = "";
	m_sSede = "";
	m_sDiagnosi = "";
}