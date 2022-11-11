#include "stdafx.h"
#include "Endox.h"
#include "VistaExtPrestazioniSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CVistaExtPrestazioniSet, CBaseSet)

CVistaExtPrestazioniSet::CVistaExtPrestazioniSet()
	: CBaseSet(NULL, "VIEW")  // è una vista //
{
	SetBaseFilter("");
	SetSortRecord("ID");

	SetEmpty();

	m_nFields = 15;
}

CString CVistaExtPrestazioniSet::GetDefaultSQL()
{
	return "VISTA_EXT_PRESTAZIONI";
}

void CVistaExtPrestazioniSet::SetEmpty()
{
	m_lId = -1;
	m_lIdOrdine = -1;
	m_sIdPrestazione = "";
	m_sCodicePrestazione = "";
	m_sDescrizionePrestazione = "";
	m_sNote = "";
	m_lQuantita = -1;
	m_bEliminato = FALSE;
	m_sCodiceNazionale = "";
	m_sCodiceRegionale = "";
	m_sDescrizioneEndox = "";
	m_sTipoEsame = "";
	m_sSiglaTipoEsame = "";
	m_lIdTipoEsameEndox = -1;
	m_lIdPrestazioneEndox = -1;
}

void CVistaExtPrestazioniSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "id", m_lId);
	RFX_Long(pFX, "IdOrdine", m_lIdOrdine);
	RFX_Text(pFX, "IdPrestazione", m_sIdPrestazione);
	RFX_Text(pFX, "CodicePrestazionePrevista", m_sCodicePrestazione);
	RFX_Text(pFX, "DescrizionePrestazione", m_sDescrizionePrestazione);
	RFX_Text(pFX, "Note", m_sNote, 3999);
	RFX_Long(pFX, "Quantita", m_lQuantita);
	RFX_Bool(pFX, "Eliminato", m_bEliminato);
	RFX_Text(pFX, "CodiceNazionale", m_sCodiceNazionale);
	RFX_Text(pFX, "CodiceRegionale", m_sCodiceRegionale);
	RFX_Text(pFX, "Descrizione", m_sDescrizioneEndox);
	RFX_Text(pFX, "TipoEsame", m_sTipoEsame);
	RFX_Text(pFX, "SiglaTipoEsame", m_sSiglaTipoEsame);
	RFX_Long(pFX, "IdTipoEsameEndox", m_lIdTipoEsameEndox);
	RFX_Long(pFX, "IdPrestazioneEndox", m_lIdPrestazioneEndox);
}

CString CVistaExtPrestazioniSet::SetBaseFilter(const CString &strFilter)
{
	CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	CString strUO;
	strUO.Format("UO=%li", theApp.m_lUO);
	if (strNewFilter.IsEmpty())
	{
		strNewFilter = strUO + " AND ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("UO=") < 0)
			strNewFilter += " AND " + strUO;

		if (strNewFilter.Find("ELIMINATO=") < 0)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}

CString CVistaExtPrestazioniSet::GetIdPrestazione(long idPrestazione)
{
	CString codice = "";

	CString filter;
	filter.Format("id = %li", idPrestazione);
	SetOpenFilter(filter);

	if (OpenRecordset("CVistaExtPrestazioniSet::GetIdPrestazione"))
	{
		if (!IsEOF())
			codice = m_sIdPrestazione;

		CloseRecordset("CVistaExtPrestazioniSet::GetIdPrestazione");
	}

	return codice;
}