#include "stdafx.h"
#include "Endox.h"
#include "VistaEsamiPerWLSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaEsamiPerWLSet, CBaseSet)

CVistaEsamiPerWLSet::CVistaEsamiPerWLSet()
	: CBaseSet(NULL, "VIEW")
{
	SetSortRecord("CONTATORE");

	m_lContatore = 0;
	m_sDescrizione = "";
	m_sDataEsame = "";
	m_sMedico = "";
	m_sSalaEsame = "";
	m_bSuperLocked = FALSE;

	m_nFields = 6;
}

CString CVistaEsamiPerWLSet::GetDefaultSQL()
{
	return "VISTA_ESAMI_PER_WL";
}

void CVistaEsamiPerWLSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Contatore",	m_lContatore);
	RFX_Text(pFX, "Descrizione", m_sDescrizione, 255);
	RFX_Text(pFX, "DataEsame", m_sDataEsame, 14);
	RFX_Text(pFX, "Medico", m_sMedico, 50);
	RFX_Text(pFX, "SalaEsame", m_sSalaEsame, 50);
	RFX_Bool(pFX, "SuperLocked", m_bSuperLocked);
	
}

void CVistaEsamiPerWLSet::SetEmpty()
{
	m_lContatore = 0;
	m_sDescrizione = "";
	m_sDataEsame = "";
	m_sMedico = "";
	m_sSalaEsame = "";
	m_bSuperLocked = FALSE;
}