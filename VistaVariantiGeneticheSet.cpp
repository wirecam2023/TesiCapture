#include "stdafx.h"
#include "Endox.h"
#include "VistaVariantiGeneticheSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define VARIANTE_ID					"VarianteID"
#define VARIANTE_TITOLO				"VarianteTitolo"
#define VARIANTE_CODICE				"VarianteCodice"
#define VARIANTE_TRASCRIZIONE		"VarianteTrascrizione"
#define VARIANTE_CROMOSSOMA			"VarianteCromossoma"
#define VARIANTE_GENE				"VarianteGene"
#define VARIANTE_POSIZIONE			"VariantePosizione"
#define VARIANTE_HGVSC				"VarianteHGVSc"
#define VARIANTE_HGVSP				"VarianteHGVSp"
#define TIPOVARIANTE_CODICE			"TipoVarianteCodice"
#define TIPOVARIANTE_DESCRIZIONE	"TipoVarianteDescrizione"
#define TIPOVARIANTE_RTF001			"TipoVarianteRTF001"
#define PATOGENICITA_CODICE			"PatogenicitaCodice"
#define PATOGENICITA_DESCRIZIONE	"PatogenicitaDescrizione"
#define PATOGENICITA_POSITIVITA		"PatogenicitaPositivita"
#define TIPOALTERAZIONE_CODICE		"TipoAlterazioneCodice"
#define TIPOALTERAZIONE_DESCRIZIONE	"TipoAlterazioneDescrizione"

IMPLEMENT_DYNAMIC(CVistaVariantiGeneticheSet, CBaseSet)

CVistaVariantiGeneticheSet::CVistaVariantiGeneticheSet()
: CBaseSet(NULL, "VIEW")
{
	SetEmpty();
	SetSortRecord("");

	m_nFields = 17;
}

CString CVistaVariantiGeneticheSet::GetDefaultSQL()
{
	return "VISTA_VARIANTIGENETICHE";
}

void CVistaVariantiGeneticheSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, VARIANTE_ID,					m_lVarianteID);
	RFX_Text(pFX, VARIANTE_TITOLO,				m_sVarianteTitolo,				255);
	RFX_Text(pFX, VARIANTE_CODICE,				m_sVarianteCodice,				50);
	RFX_Text(pFX, VARIANTE_TRASCRIZIONE,		m_sVarianteTrascrizione,		255);
	RFX_Text(pFX, VARIANTE_CROMOSSOMA,			m_sVarianteCromossoma,			255);
	RFX_Text(pFX, VARIANTE_GENE,				m_sVarianteGene,				255);
	RFX_Text(pFX, VARIANTE_POSIZIONE,			m_sVariantePosizione,			255);
	RFX_Text(pFX, VARIANTE_HGVSC,				m_sVarianteHGVSc,				50);
	RFX_Text(pFX, VARIANTE_HGVSP,				m_sVarianteHGVSp,				50);
	RFX_Text(pFX, TIPOVARIANTE_CODICE,			m_sTipoVarianteCodice,			50);
	RFX_Text(pFX, TIPOVARIANTE_DESCRIZIONE,		m_sTipoVarianteDescrizione,		255);
	RFX_Text(pFX, TIPOVARIANTE_RTF001,			m_sTipoVarianteRTF001,			_TEXT_CONTROL_FIELD_LIMIT);
	RFX_Text(pFX, PATOGENICITA_CODICE,			m_sPatogenicitaCodice,			50);
	RFX_Text(pFX, PATOGENICITA_DESCRIZIONE,		m_sPatogenicitaDescrizione,		255);
	RFX_Bool(pFX, PATOGENICITA_POSITIVITA,		m_bPatogenicitaPositivita);
	RFX_Text(pFX, TIPOALTERAZIONE_CODICE,		m_sTipiAlterazioneCodice,		50);
	RFX_Text(pFX, TIPOALTERAZIONE_DESCRIZIONE,	m_sTipiAlterazioneDescrizione,	255);		
}

void CVistaVariantiGeneticheSet::SetEmpty()
{
	m_lVarianteID = 0;
	m_sVarianteTitolo = "";
	m_sVarianteCodice = "";
	m_sVarianteTrascrizione = "";
	m_sVarianteCromossoma = "";
	m_sVarianteGene = "";
	m_sVariantePosizione = "";
	m_sVarianteHGVSc = "";
	m_sVarianteHGVSp = "";
	m_sTipoVarianteCodice = "";
	m_sTipoVarianteDescrizione = "";
	m_sTipoVarianteRTF001 = "";
	m_sPatogenicitaCodice = "";
	m_sPatogenicitaDescrizione = "";
	m_bPatogenicitaPositivita = FALSE;
	m_sTipiAlterazioneCodice = "";
	m_sTipiAlterazioneDescrizione = "";
}

CString CVistaVariantiGeneticheSet::TryGetVaule(long lIDVariante, CString sColumn)
{
	CString sResult = sColumn;

	CString sFilter;
	sFilter.Format("%s=%li", VARIANTE_ID, lIDVariante);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CVistaVariantiGeneticheSet::TryGetVaule"))
	{
		if (sColumn == VARIANTE_ID)
			sResult.Format("%li", m_lVarianteID);
		else if (sColumn == VARIANTE_TITOLO)
			sResult = m_sVarianteTitolo;
		else if (sColumn == VARIANTE_CODICE)
			sResult = m_sVarianteCodice;
		else if (sColumn == VARIANTE_TRASCRIZIONE)
			sResult = m_sVarianteTrascrizione;
		else if (sColumn == VARIANTE_CROMOSSOMA)
			sResult = m_sVarianteCromossoma;
		else if (sColumn == VARIANTE_GENE)
			sResult = m_sVarianteGene;
		else if (sColumn == VARIANTE_POSIZIONE)
			sResult = m_sVariantePosizione;
		else if (sColumn == VARIANTE_HGVSC)
			sResult = m_sVarianteHGVSc;
		else if (sColumn == VARIANTE_HGVSP)
			sResult = m_sVarianteHGVSp;
		else if (sColumn == TIPOVARIANTE_CODICE)
			sResult = m_sTipoVarianteCodice;
		else if (sColumn == TIPOVARIANTE_DESCRIZIONE)
			sResult = m_sTipoVarianteDescrizione;
		else if (sColumn == TIPOVARIANTE_RTF001)
			sResult = m_sTipoVarianteRTF001;
		else if (sColumn == PATOGENICITA_CODICE)
			sResult = m_sPatogenicitaCodice;
		else if (sColumn == PATOGENICITA_DESCRIZIONE)
			sResult = m_sPatogenicitaDescrizione;
		else if (sColumn == PATOGENICITA_POSITIVITA)
			sResult = sColumn; //NAO VOU RETORNAR UM BOLEANO
		else if (sColumn == TIPOALTERAZIONE_CODICE)
			sResult = m_sTipiAlterazioneCodice;
		else if (sColumn == TIPOALTERAZIONE_DESCRIZIONE)
			sResult = m_sTipiAlterazioneDescrizione;

		CloseRecordset("CVistaVariantiGeneticheSet::TryGetVaule");
	}			
	return sResult;
}