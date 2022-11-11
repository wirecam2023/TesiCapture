#include "stdafx.h"
#include "Endox.h"
#include "PdfSissSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CPdfSissSet, CAMBaseSet)

CPdfSissSet::CPdfSissSet(CDatabase* pDatabase)
	: CAMBaseSet(pDatabase)
{
	m_lIDPdf = 0;
	m_lTentativi = 0;
	m_lSizeDocumento = 0;
	m_bProcessato = FALSE;
	m_bAnnullativo = FALSE;

	m_nFields = 20;
}

void CPdfSissSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "IDPdf", m_lIDPdf);
	RFX_Text(pFX, "CognomeMedico", m_sCognomeMedico, 50);
	RFX_Text(pFX, "NomeMedico", m_sNomeMedico, 50);
	RFX_Text(pFX, "CodiceFiscaleMedico", m_sCodiceFiscaleMedico, 50);
	RFX_Text(pFX, "Autorizzazione", m_sAutorizzazione, 10*1024*1024);
	RFX_Text(pFX, "AutorizzazioneFormato", m_sAutorizzazioneFormato, 50);
	RFX_Text(pFX, "AutorizzazioneFirmato", m_sAutorizzazioneFirmato, 50);
	RFX_Text(pFX, "AutorizzazioneVersione", m_sAutorizzazioneVersione, 50);
	RFX_Text(pFX, "Documento", m_sDocumento, 10*1024*1024);
	RFX_Text(pFX, "DocumentoFormato", m_sDocumentoFormato, 50);
	RFX_Text(pFX, "DocumentoFirmato", m_sDocumentoFirmato, 50);
	RFX_Text(pFX, "DocumentoMarcato", m_sDocumentoMarcato, 50);
	RFX_Text(pFX, "HashDocumento", m_sHashDocumento, 255);
	RFX_Text(pFX, "AlgoritmoHash", m_sAlgoritmoHash, 50);
	RFX_Long(pFX, "SizeDocumento", m_lSizeDocumento);
	RFX_Bool(pFX, "Annullativo", m_bAnnullativo);
	RFX_Long(pFX, "Tentativi", m_lTentativi);
	RFX_Text(pFX, "Errore", m_sErrore, 255);
	RFX_Bool(pFX, "Processato", m_bProcessato);
	RFX_Text(pFX, "DataOraDocumento", m_sDataOraDocumento, 14);
}

CString CPdfSissSet::GetDefaultSQL()
{
	return "PDF_SISS";
}