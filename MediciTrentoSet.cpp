#include "stdafx.h"
#include "Endox.h"
#include "MediciTrentoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMediciTrentoSet, CBaseSet)

CMediciTrentoSet::CMediciTrentoSet()
	: CBaseSet(NULL, "") // non è una tabella nostra //
{
	SetEmpty();

	m_nFields = 19;
}

void CMediciTrentoSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "COD_VER", m_lCOD_VER);
	RFX_Text(pFX, "COD_MEDICO_MG", m_sCOD_MEDICO_MG, 50);
	RFX_Text(pFX, "COD_FISCALE_MMG", m_sCOD_FISCALE_MMG, 50);
	RFX_Text(pFX, "MEDICO_MG", m_sMEDICO_MG, 255);
	RFX_Long(pFX, "COD_VER_COMUNE_RESIDENZA_MMG", m_lCOD_VER_COMUNE_RESIDENZA_MMG);
	RFX_Text(pFX, "COD_COMUNE_RESIDENZA_MMG", m_sCOD_COMUNE_RESIDENZA_MMG, 50);
	RFX_Text(pFX, "INDIRIZZO_RESIDENZA_MMG", m_sINDIRIZZO_RESIDENZA_MMG, 255);
	RFX_Text(pFX, "CAP_RESIDENZA_MMG", m_sCAP_RESIDENZA_MMG, 50);
	RFX_Text(pFX, "COD_DISTRETTO_AMBITO_MMG", m_sCOD_DISTRETTO_AMBITO_MMG, 50);
	RFX_Text(pFX, "INDIRIZZO_AMBULATORIO_MMG", m_sINDIRIZZO_AMBULATORIO_MMG, 255);
	RFX_Text(pFX, "CAP_AMBULATORIO_MMG", m_sCAP_AMBULATORIO_MMG, 50);
	RFX_Long(pFX, "COD_VER_COMUNE_AMBULATORIO_MMG", m_lCOD_VER_COMUNE_AMBULATORIO_MMG);
	RFX_Text(pFX, "COD_COMUNE_AMBULATORIO_MMG", m_sCOD_COMUNE_AMBULATORIO_MMG, 50);
	RFX_Text(pFX, "COD_TIPO_MEDICO_MG", m_sCOD_TIPO_MEDICO_MG, 50);
	RFX_Long(pFX, "ASSISTITI_MMG", m_lASSISTITI_MMG);
	RFX_Text(pFX, "DATA_INSERIMENTO", m_sDATA_INSERIMENTO);
	RFX_Text(pFX, "DATA_VARIAZIONE", m_sDATA_VARIAZIONE);
	RFX_Text(pFX, "DATA_CESSAZIONE", m_sDATA_CESSAZIONE, 50);
	RFX_Text(pFX, "NOTE", m_sNOTE, 255);
}

void CMediciTrentoSet::SetEmpty()
{
	m_lCOD_VER = 0;
	m_sCOD_MEDICO_MG = "";
	m_sCOD_FISCALE_MMG = "";
	m_sMEDICO_MG = "";
	m_lCOD_VER_COMUNE_RESIDENZA_MMG = 0;
	m_sCOD_COMUNE_RESIDENZA_MMG = "";
	m_sINDIRIZZO_RESIDENZA_MMG = "";
	m_sCAP_RESIDENZA_MMG = "";
	m_sCOD_DISTRETTO_AMBITO_MMG = "";
	m_sINDIRIZZO_AMBULATORIO_MMG = "";
	m_sCAP_AMBULATORIO_MMG = "";
	m_lCOD_VER_COMUNE_AMBULATORIO_MMG = 0;
	m_sCOD_COMUNE_AMBULATORIO_MMG = "";
	m_sCOD_TIPO_MEDICO_MG = "";
	m_lASSISTITI_MMG = 0;
	m_sDATA_INSERIMENTO = "";
	m_sDATA_VARIAZIONE = "";
	m_sDATA_CESSAZIONE = "";
	m_sNOTE = "";
}

CString CMediciTrentoSet::GetDefaultSQL()
{
	return "TD_MEDICO_MG";
}

void CMediciTrentoSet::GetFieldText(CString strContatore, CString& strNominativo, CString& strTelefono, CString& strIndirizzo)
{
	strNominativo = "";
	strTelefono = "";
	strIndirizzo = "";

	if ((strContatore.GetLength() > 0) && (strContatore != " "))
	{
		SetOpenFilter("COD_MEDICO_MG=" + strContatore);
		if (OpenRecordset("CMediciTrentoSet::GetFieldText"))
		{
			if (!IsEOF())
			{
				strNominativo = m_sMEDICO_MG;
				strTelefono = "";
				strIndirizzo = m_sINDIRIZZO_AMBULATORIO_MMG;
			}

			CloseRecordset("CMediciTrentoSet::GetFieldText");
		}
	}
}