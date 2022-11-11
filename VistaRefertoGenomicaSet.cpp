#include "stdafx.h"
#include "Endox.h"
#include "VistaRefertoGenomicaSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define REFERTO_IDESAME					"RefertoIDEsame"
#define REFERTO_BASITOTALI				"RefertoBasiTotali"
#define REFERTO_COPERTURAMEDIA			"RefertoCoperturaMedia"
#define REFERTO_COPERTURAPERCENTUALE	"RefertoCoperturaPercentuale"
#define REFERTO_UTENTE					"RefertoUtente"
#define REFERTO_DATAORA					"RefertoDataOra"
#define TIPOREFERTO_CODICE				"TipoRefertoCodice"
#define TIPOREFERTO_TITOLO				"TipoRefertoTitolo"
#define TIPOREFERTO_RTF001				"TipoRefertoRTF001"
#define TIPOREFERTO_RTF002				"TipoRefertoRTF002"
#define TIPOREFERTO_RTF003				"TipoRefertoRTF003"
#define TIPOREFERTO_RTF004				"TipoRefertoRTF004"
#define TIPOREFERTO_RTF005				"TipoRefertoRTF005"
#define TIPOREFERTO_RTF006				"TipoRefertoRTF006"
#define TIPOREFERTO_RTF007				"TipoRefertoRTF007"
#define TIPOREFERTO_RTF008				"TipoRefertoRTF008"
#define TIPOREFERTO_RTF009				"TipoRefertoRTF009"
#define TIPOREFERTO_RTF010				"TipoRefertoRTF010"
#define TIPOMATERIALE_CODICE			"TipoMaterialeCodice"
#define TIPOMATERIALE_DESCRIZIONE		"TipoMaterialeDescrizione"
#define TIPOMATERIALE_RTF001			"TipoMaterialeRTF001"

IMPLEMENT_DYNAMIC(CVistaRefertoGenomicaSet, CBaseSet)

CVistaRefertoGenomicaSet::CVistaRefertoGenomicaSet()
: CBaseSet(NULL, "VIEW")
{
	SetEmpty();
	SetSortRecord("");

	m_nFields = 21;
}

CString CVistaRefertoGenomicaSet::GetDefaultSQL()
{
	return "VISTA_REFERTOGENOMICA";
}

void CVistaRefertoGenomicaSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, REFERTO_IDESAME,				m_lRefertoIDEsame);
	RFX_Text(pFX, REFERTO_BASITOTALI,			m_sRefertoBasiTotali,			50);
	RFX_Text(pFX, REFERTO_COPERTURAMEDIA,		m_sRefertoCoperturaMedia,		50);
	RFX_Text(pFX, REFERTO_COPERTURAPERCENTUALE,	m_sRefertoCoperturaPercentuale, 50);
	RFX_Text(pFX, REFERTO_UTENTE,				m_sRefertoUtente,				50);
	RFX_Text(pFX, REFERTO_DATAORA,				m_sRefertoDataOra,				14);
	RFX_Text(pFX, TIPOREFERTO_CODICE,			m_sTipoRefertoCodice,			50);
	RFX_Text(pFX, TIPOREFERTO_TITOLO,			m_sTipoRefertoTitolo,			_TEXT_CONTROL_FIELD_LIMIT);
	RFX_Text(pFX, TIPOREFERTO_RTF001,			m_sTipoRefertoRTF001,			_TEXT_CONTROL_FIELD_LIMIT);
	RFX_Text(pFX, TIPOREFERTO_RTF002,			m_sTipoRefertoRTF002,			_TEXT_CONTROL_FIELD_LIMIT);
	RFX_Text(pFX, TIPOREFERTO_RTF003,			m_sTipoRefertoRTF003,			_TEXT_CONTROL_FIELD_LIMIT);
	RFX_Text(pFX, TIPOREFERTO_RTF004,			m_sTipoRefertoRTF004,			_TEXT_CONTROL_FIELD_LIMIT);
	RFX_Text(pFX, TIPOREFERTO_RTF005,			m_sTipoRefertoRTF005,			_TEXT_CONTROL_FIELD_LIMIT);
	RFX_Text(pFX, TIPOREFERTO_RTF006,			m_sTipoRefertoRTF006,			_TEXT_CONTROL_FIELD_LIMIT);
	RFX_Text(pFX, TIPOREFERTO_RTF007,			m_sTipoRefertoRTF007,			_TEXT_CONTROL_FIELD_LIMIT);
	RFX_Text(pFX, TIPOREFERTO_RTF008,			m_sTipoRefertoRTF008,			_TEXT_CONTROL_FIELD_LIMIT);
	RFX_Text(pFX, TIPOREFERTO_RTF009,			m_sTipoRefertoRTF009,			_TEXT_CONTROL_FIELD_LIMIT);
	RFX_Text(pFX, TIPOREFERTO_RTF010,			m_sTipoRefertoRTF010,			_TEXT_CONTROL_FIELD_LIMIT);
	RFX_Text(pFX, TIPOMATERIALE_CODICE,			m_sTipoMaterialeCodice,			50);
	RFX_Text(pFX, TIPOMATERIALE_DESCRIZIONE,	m_sTipoMaterialeDescrizione,	255);
	RFX_Text(pFX, TIPOMATERIALE_RTF001,			m_sTipoMaterialeRTF001,			_TEXT_CONTROL_FIELD_LIMIT);
}

void CVistaRefertoGenomicaSet::SetEmpty()
{
	m_lRefertoIDEsame = 0;
	m_sRefertoBasiTotali = "";
	m_sRefertoCoperturaMedia = "";
	m_sRefertoCoperturaPercentuale = "";
	m_sRefertoUtente = "";
	m_sRefertoDataOra = "";
	m_sTipoRefertoCodice = "";
	m_sTipoRefertoTitolo = "";
	m_sTipoRefertoRTF001 = "";
	m_sTipoRefertoRTF002 = "";
	m_sTipoRefertoRTF003 = "";
	m_sTipoRefertoRTF004 = "";
	m_sTipoRefertoRTF005 = "";
	m_sTipoRefertoRTF006 = "";
	m_sTipoRefertoRTF007 = "";
	m_sTipoRefertoRTF008 = "";
	m_sTipoRefertoRTF009 = "";
	m_sTipoRefertoRTF010 = "";
	m_sTipoMaterialeCodice = "";
	m_sTipoMaterialeDescrizione = "";
	m_sTipoMaterialeRTF001 = "";
}

CString CVistaRefertoGenomicaSet::TryGetVaule(long lIDEsame, CString sColumn)
{
	CString sResult = sColumn;

	CString sFilter;
	sFilter.Format("%s=%li", REFERTO_IDESAME, lIDEsame);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CVistaRefertoGenomicaSet::TryGetVaule"))
	{		
		if (sColumn == REFERTO_IDESAME)
			sResult.Format("%li", m_lRefertoIDEsame);
		else if (sColumn == REFERTO_BASITOTALI)
			sResult = m_sRefertoBasiTotali;
		else if (sColumn == REFERTO_COPERTURAMEDIA)
			sResult = m_sRefertoCoperturaMedia;
		else if (sColumn == REFERTO_COPERTURAPERCENTUALE)
			sResult = m_sRefertoCoperturaPercentuale;
		else if (sColumn == REFERTO_UTENTE)
			sResult = m_sRefertoUtente;
		else if (sColumn == REFERTO_DATAORA)
			sResult = m_sRefertoDataOra;
		else if (sColumn == TIPOREFERTO_CODICE)
			sResult = m_sTipoRefertoCodice;
		else if (sColumn == TIPOREFERTO_TITOLO)
			sResult = m_sTipoRefertoTitolo;
		else if (sColumn == TIPOREFERTO_RTF001)
			sResult = m_sTipoRefertoRTF001;
		else if (sColumn == TIPOREFERTO_RTF002)
			sResult = m_sTipoRefertoRTF002;
		else if (sColumn == TIPOREFERTO_RTF003)
			sResult = m_sTipoRefertoRTF003;
		else if (sColumn == TIPOREFERTO_RTF004)
			sResult = m_sTipoRefertoRTF004;
		else if (sColumn == TIPOREFERTO_RTF005)
			sResult = m_sTipoRefertoRTF005;
		else if (sColumn == TIPOREFERTO_RTF006)
			sResult = m_sTipoRefertoRTF006;
		else if (sColumn == TIPOREFERTO_RTF007)
			sResult = m_sTipoRefertoRTF007;
		else if (sColumn == TIPOREFERTO_RTF008)
			sResult = m_sTipoRefertoRTF008;
		else if (sColumn == TIPOREFERTO_RTF009)
			sResult = m_sTipoRefertoRTF009;
		else if (sColumn == TIPOREFERTO_RTF010)
			sResult = m_sTipoRefertoRTF010;
		else if (sColumn == TIPOMATERIALE_CODICE)
			sResult = m_sTipoMaterialeCodice;
		else if (sColumn == TIPOMATERIALE_DESCRIZIONE)
			sResult = m_sTipoMaterialeDescrizione;
		else if (sColumn == TIPOMATERIALE_RTF001)
			sResult = m_sTipoMaterialeRTF001;

		CloseRecordset("CVistaRefertoGenomicaSet::TryGetVaule");
	}
	return sResult;
}