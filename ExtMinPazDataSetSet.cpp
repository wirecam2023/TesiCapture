#include "stdafx.h"
#include "Endox.h"
#include "ExtMinPazDataSetSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CExtMinPazDataSetSet, CBaseSet)

CExtMinPazDataSetSet::CExtMinPazDataSetSet()
	: CBaseSet(NULL, "VIEW")
{
	SetSortRecord("ID");

	m_bCognome = FALSE;
	m_bCognome2 = FALSE;
	m_bNome = FALSE;
	m_bDataNascita = FALSE;
	m_bIstatNascita = FALSE;
	m_bIndirizzoResidenza = FALSE;
	m_bIstatResidenza = FALSE;
	m_bCapResidenza = FALSE;
	m_bTelefono1 = FALSE;
	m_bTelefono2 = FALSE;
	m_bCellulare1 = FALSE;
	m_bCellulare2 = FALSE;
	m_bCodiceFiscale = FALSE;
	m_bCodiceSanitario = FALSE;
	m_bSesso = FALSE;

	m_nFields = 15;
}

CString CExtMinPazDataSetSet::GetDefaultSQL()
{
	return "Ext_MinPazDataSet";
}

void CExtMinPazDataSetSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Bool(pFX, "Cognome", m_bCognome);
	RFX_Bool(pFX, "Cognome2", m_bCognome2);
	RFX_Bool(pFX, "Nome", m_bNome);
	RFX_Bool(pFX, "DataNascita", m_bDataNascita);
	RFX_Bool(pFX, "IstatNascita", m_bIstatNascita);
	RFX_Bool(pFX, "IndirizzoResidenza", m_bIndirizzoResidenza);
	RFX_Bool(pFX, "IstatResidenza", m_bIstatResidenza);
	RFX_Bool(pFX, "CapResidenza", m_bCapResidenza);
	RFX_Bool(pFX, "Telefono1", m_bTelefono1);
	RFX_Bool(pFX, "Telefono2", m_bTelefono2);
	RFX_Bool(pFX, "Cellulare1", m_bCellulare1);
	RFX_Bool(pFX, "Cellulare2", m_bCellulare2);
	RFX_Bool(pFX, "CodiceFiscale", m_bCodiceFiscale);
	RFX_Bool(pFX, "CodiceSanitario", m_bCodiceSanitario);
	RFX_Bool(pFX, "Sesso", m_bSesso);
}

void CExtMinPazDataSetSet::SetEmpty()
{
	m_bCognome = FALSE;
	m_bCognome2 = FALSE;
	m_bNome = FALSE;
	m_bDataNascita = FALSE;
	m_bIstatNascita = FALSE;
	m_bIndirizzoResidenza = FALSE;
	m_bIstatResidenza = FALSE;
	m_bCapResidenza = FALSE;
	m_bTelefono1 = FALSE;
	m_bTelefono2 = FALSE;
	m_bCellulare1 = FALSE;
	m_bCellulare2 = FALSE;
	m_bCodiceFiscale = FALSE;
	m_bCodiceSanitario = FALSE;
	m_bSesso = FALSE;
}