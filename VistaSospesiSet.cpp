#include "stdafx.h"
#include "Endox.h"
#include "VistaSospesiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaSospesiSet, CBaseSet)

CVistaSospesiSet::CVistaSospesiSet()
	: CBaseSet(NULL, "VIEW")
{
	SetEmpty();
	SetSortRecord("IDPaziente, IDEsame");

	m_nFields = 10;
}

CString CVistaSospesiSet::GetDefaultSQL()
{
	return "VistaSospesi";
}

void CVistaSospesiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "IDPaziente", m_lIDPaziente);
	RFX_Text(pFX, "Cognome", m_sCognome, 50);
	RFX_Text(pFX, "Nome", m_sNome, 50);
	RFX_Long(pFX, "NatoIlCustom", m_lNatoIlCustom);
	RFX_Long(pFX, "IDEsame", m_lIDEsame);
	RFX_Text(pFX, "TipoEsame", m_sTipoEsame, 255);
	RFX_Long(pFX, "Data", m_lData);
	RFX_Long(pFX, "DataScadenzaSospensione", m_lDataScadenzaSospensione);
	RFX_Text(pFX, "Motivo", m_sMotivo, 4000);
	RFX_Text(pFX, "MotivoSospensione", m_sMotivoSospensione, 4000);
}

void CVistaSospesiSet::SetEmpty()
{
	m_lIDPaziente = 0;
	m_sCognome = "";
	m_sNome = "";
	m_lNatoIlCustom = 0;
	m_lIDEsame = 0;
	m_sTipoEsame = "";
	m_lData = 0;
	m_lDataScadenzaSospensione = 0;
	m_sMotivo = "";
	m_sMotivoSospensione = "";
}