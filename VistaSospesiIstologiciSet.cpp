#include "stdafx.h"
#include "Endox.h"
#include "VistaSospesiIstologiciSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaSospesiIstologiciSet, CBaseSet)

CVistaSospesiIstologiciSet::CVistaSospesiIstologiciSet()
	: CBaseSet(NULL, "VIEW")  // è una vista //
{
	SetSortRecord("DATA");

	SetEmpty();

	m_nFields = 10;
}

CString CVistaSospesiIstologiciSet::GetDefaultSQL()
{
	return "VistaSospesiIstologiciP";
}

void CVistaSospesiIstologiciSet::SetEmpty()
{
	m_lIDPaziente = 0;
	m_lIDEsame = 0;
	m_sCognome = "";
	m_sNome = "";
	m_lNatoIlCustom = 0;
	m_lData = 0;
	m_sDescrizioneEsame = "";
	m_lMedico = 0;
	m_sCognomeMedico = "";
	m_sNomeMedico = "";
}

void CVistaSospesiIstologiciSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "IDPaziente", m_lIDPaziente);
	RFX_Long(pFX, "IDEsame", m_lIDEsame);
	RFX_Text(pFX, "Cognome", m_sCognome, 50);
	RFX_Text(pFX, "Nome", m_sNome, 50);
	RFX_Long(pFX, "NatoIlCustom", m_lNatoIlCustom);
	RFX_Long(pFX, "Data", m_lData);
	RFX_Text(pFX, "DescrizioneEsame", m_sDescrizioneEsame, 255);
	RFX_Long(pFX, "Medico", m_lMedico);
	RFX_Text(pFX, "CognomeMedico", m_sCognomeMedico, 50);
	RFX_Text(pFX, "NomeMedico", m_sNomeMedico, 50);
}