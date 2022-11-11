#include "stdafx.h"
#include "Endox.h"
#include "PdfDatiAggiuntiviSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CPdfDatiAggiuntiviSet, CAMBaseSet)

CPdfDatiAggiuntiviSet::CPdfDatiAggiuntiviSet(CDatabase* pDatabase)
: CAMBaseSet(pDatabase)
{
	m_lIDPdf = 0;
	m_sRappresentazioneXml = "";

	m_nFields = 3;
}

void CPdfDatiAggiuntiviSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "IDPdf", m_lIDPdf);	
	RFX_Text(pFX, "RappresentazioneXml", m_sRappresentazioneXml, 1000000);
	RFX_Text(pFX, "B64MimeFirmato", m_sB64MimeFirmato, 10000000);
}

CString CPdfDatiAggiuntiviSet::GetDefaultSQL()
{
	return "PDF_DatiAggiuntivi";
}