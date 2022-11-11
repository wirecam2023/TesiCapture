#include "stdafx.h"
#include "Endox.h"
#include "ExtOrdiniSet.h"

#include "Common.h"
#include "ListaPrenotazioniCupDlg.h"
#include "UOSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CExtOrdiniSet, CBaseSet)

CExtOrdiniSet::CExtOrdiniSet()
	: CBaseSet(&m_lID, "ID")
{
	SetBaseFilter("");
	SetEmpty();

	m_bColumnsTCP = CheckColumnExists("EXT_ORDINI", "ORDERNUMBERCORRELATI") && CheckColumnExists("EXT_ORDINI", "STATOTCP");
	m_nFields = 66 - (m_bColumnsTCP ? 0 : 2); //Gabriel - TCP
}

CString CExtOrdiniSet::GetDefaultSQL()
{
	return "EXT_ORDINI";
}

void CExtOrdiniSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "ID", m_lID);
	if (m_nFields > 1)
	{
		RFX_Text(pFX, "OrderNumber", m_sOrderNumber, 50);
		RFX_Text(pFX, "DataEsame", m_sDataEsame, 14);
		RFX_Text(pFX, "Provenienza", m_sProvenienza, 50);
		RFX_Text(pFX, "CodiceAgenda", m_sCodiceAgenda, 50);
		RFX_Text(pFX, "Note", m_sNote, 3999);
		RFX_Text(pFX, "CodiceRepartoInviante", m_sCodiceRepartoInviante, 50);
		RFX_Text(pFX, "CodiceMedicoInviante", m_sCodiceMedicoInviante, 50);
		RFX_Text(pFX, "MedicoInviante", m_sMedicoInviante, 255);
		RFX_Text(pFX, "Nosologico", m_sNosologico, 50);
		RFX_Text(pFX, "Urgenza", m_sUrgenza, 50);
		RFX_Long(pFX, "IDEsameIns", m_lIDEsameIns);
		RFX_Bool(pFX, "Trasferito", m_bTrasferito);
		RFX_Text(pFX, "IDProvetta", m_sIDProvetta, 50);
		RFX_Bool(pFX, "AcqSegnalata", m_bAcqSegnalata);
		RFX_Bool(pFX, "ErogazioneSegnalata", m_bErogazioneSegnalata);
		RFX_Bool(pFX, "AppuntamentoSegnalato", m_bAppuntamentoSegnalato);
		RFX_Bool(pFX, "Eliminato", m_bEliminato);
		RFX_Text(pFX, "AssIden", m_sAssIden, 50);
		RFX_Text(pFX, "Cognome", m_sCognome, 255); // 50
		RFX_Text(pFX, "Cognome2", m_sCognome2, 255); // 50
		RFX_Text(pFX, "Nome", m_sNome, 255); // 50
		RFX_Long(pFX, "DataNascitaCustom", m_lDataNascitaCustom);
		RFX_Text(pFX, "DataNascita", m_sDataNascita, 8);
		RFX_Long(pFX, "IstatNascita", m_lIstatNascita);
		RFX_Text(pFX, "ComuneNascita", m_sComuneNascita, 50);
		RFX_Text(pFX, "IndirizzoResidenza", m_sIndirizzoResidenza, 255);
		RFX_Long(pFX, "IstatResidenza", m_lIstatResidenza);
		RFX_Text(pFX, "ComuneResidenza", m_sComuneResidenza, 255); // 50
		RFX_Text(pFX, "CapResidenza", m_sCapResidenza, 5);
		RFX_Text(pFX, "Telefono1", m_sTelefono1, 50);
		RFX_Text(pFX, "Telefono2", m_sTelefono2, 50);
		RFX_Text(pFX, "Cellulare1", m_sCellulare1, 50);
		RFX_Text(pFX, "Cellulare2", m_sCellulare2, 50);
		RFX_Text(pFX, "CodiceFiscale", m_sCodiceFiscale, 16);
		RFX_Text(pFX, "CodiceSanitario", m_sCodiceSanitario, 50);
		RFX_Text(pFX, "CodiceSTP", m_sCodiceSTP, 50);
		RFX_Text(pFX, "CodiceTEAM", m_sCodiceTEAM, 50);
		RFX_Text(pFX, "CodiceIstAssicurativa", m_sCodiceIstAssicurativa, 50);
		RFX_Long(pFX, "Sesso", m_lSesso);
		RFX_Long(pFX, "Asl", m_lAsl);
		RFX_Text(pFX, "CodiceMedicoCurante", m_sCodiceMedicoCurante, 50);
		RFX_Text(pFX, "MedicoCurante", m_sMedicoCurante, 255); // 50
		RFX_Text(pFX, "CodiceCittadinanza", m_sCodiceCittadinanza, 50);
		RFX_Text(pFX, "Cittadinanza", m_sCittadinanza, 50);
		RFX_Text(pFX, "DataRichiesta", m_sDataRichiesta, 14);
		RFX_Text(pFX, "RepartoInviante", m_sRepartoInviante, 255);
		RFX_Text(pFX, "Provincia", m_sProvincia, 50);
		RFX_Long(pFX, "StatoAccettazione", m_lStatoAccettazione);
		RFX_Text(pFX, "UO", m_sUO, 50);
		RFX_Text(pFX, "IDEpisodioRicovero", m_sIDEpisodioRicovero, 50);
		RFX_Text(pFX, "DataRicovero", m_sDataRicovero, 50);
		RFX_Bool(pFX, "CertificazioneMEF", m_bCertificazioneMEF);
		RFX_Bool(pFX, "CertificazioneSISS", m_bCertificazioneSISS);
		RFX_Text(pFX, "CodAlfa", m_sCodAlfa, 50);
		RFX_Text(pFX, "UlssResidenza", m_sUlssResidenza, 10);
		RFX_Text(pFX, "QuesitoDiagnostico", m_sQuesitoDiagnostico, 4000);
		// RFX_Bool(pFX, "IMPORTING", m_bImporting);
		RFX_Long(pFX, "IDMOTIVO", m_lIDMotivo);
		//Luiz - 13/05/2019 - P3 - Atualiza nome/sobrenome Médico - Inclui Médicos solicitantes
		RFX_Text(pFX, "MedicoInviante2", m_sMedicoInviante2, 255);
		RFX_Text(pFX, "MedicoInviante3", m_sMedicoInviante3, 255);
		RFX_Text(pFX, "MedicoInviante4", m_sMedicoInviante4, 255);
		RFX_Text(pFX, "IdentificazionePassaporto", m_sIdentificazionePassaporto, 50); //Julio - BUG 3285 - Adequação de laudos
		RFX_Text(pFX, "IdentificazioneDoc_1", m_sIdentificazioneDoc1, 50);			  //Julio - BUG 3285 - Adequação de laudos
		RFX_Text(pFX, "IdentificazioneDoc_2", m_sIdentificazioneDoc2, 50);			  //Julio - BUG 3285 - Adequação de laudos
		
		//Gabriel - TCP
		if (m_bColumnsTCP)
		{
			RFX_Text(pFX, "ORDERNUMBERCORRELATI", m_sOrderNumberCorrelati, 50);
			RFX_Long(pFX, "STATOTCP", m_lStatoTCP);
		}
	}
}

void CExtOrdiniSet::SetEmpty()
{
	m_lID = 0;
	m_sOrderNumber = "";
	m_sDataEsame = "";
	m_sProvenienza = "";
	m_sCodiceAgenda = "";
	m_sNote = "";
	m_sCodiceRepartoInviante = "";
	m_sCodiceMedicoInviante = "";
	m_sMedicoInviante = "";
	m_sNosologico = "";
	m_sUrgenza = "";
	m_lIDEsameIns = 0;
	m_bTrasferito = FALSE;
	m_sIDProvetta = "";
	m_bAcqSegnalata = FALSE;
	m_bErogazioneSegnalata = FALSE;
	m_bAppuntamentoSegnalato = FALSE;
	m_bEliminato = FALSE;
	m_sAssIden = "";
	m_sCognome = "";
	m_sCognome2 = "";
	m_sNome = "";
	m_lDataNascitaCustom = 0;
	m_sDataNascita = "";
	m_lIstatNascita = 0;
	m_sComuneNascita = "";
	m_sIndirizzoResidenza = "";
	m_lIstatResidenza = 0;
	m_sComuneResidenza = "";
	m_sCapResidenza = "";
	m_sTelefono1 = "";
	m_sTelefono2 = "";
	m_sCellulare1 = "";
	m_sCellulare2 = "";
	m_sCodiceFiscale = "";
	m_sCodiceSanitario = "";
	m_sCodiceSTP = "";
	m_sCodiceTEAM = "";
	m_lSesso = 0;
	m_lAsl = 0;
	m_sCodiceMedicoCurante = "";
	m_sMedicoCurante = "";
	m_sCodiceCittadinanza = "";
	m_sCittadinanza = "";
	m_sDataRichiesta = "";
	m_sRepartoInviante = "";
	m_sProvincia = "";
	m_lStatoAccettazione = LPC_STATO_ACCETTATA;
	m_sUO = "";
	m_sIDEpisodioRicovero = "";
	m_sDataRicovero = "";
	m_bCertificazioneMEF = FALSE;
	m_bCertificazioneSISS = FALSE;
	m_sCodAlfa = "";
	m_sUlssResidenza = "";
	m_sQuesitoDiagnostico = "";
	// m_bImporting = FALSE;
	m_sCodiceIstAssicurativa = "";
	m_lIDMotivo = 0;
	//Luiz - 13/05/2019 - P3 - Atualiza nome/sobrenome Médico - Inclui Médicos solicitantes
	m_sMedicoInviante2 = "";
	m_sMedicoInviante3 = "";
	m_sMedicoInviante4 = "";

	m_sIdentificazionePassaporto = ""; //Julio - BUG 3285 - Adequação de laudos
	m_sIdentificazioneDoc1 = "";	   //Julio - BUG 3285 - Adequação de laudos
	m_sIdentificazioneDoc2 = "";	   //Julio - BUG 3285 - Adequação de laudos

	m_sOrderNumberCorrelati = ""; //Gabriel - TCP
	m_lStatoTCP = 0; //Gabriel - TCP
}

CBaseSet* CExtOrdiniSet::CreateNew()
{
	return (CBaseSet*)new CExtOrdiniSet;
}

void CExtOrdiniSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CExtOrdiniSet* pSet = (CExtOrdiniSet*)pOriginalSet;

	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sOrderNumber) || bCopyAll)
		m_sOrderNumber = pSet->m_sOrderNumber;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDataEsame) || bCopyAll)
		m_sDataEsame = pSet->m_sDataEsame;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sProvenienza) || bCopyAll)
		m_sProvenienza = pSet->m_sProvenienza;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodiceAgenda) || bCopyAll)
		m_sCodiceAgenda = pSet->m_sCodiceAgenda;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNote) || bCopyAll)
		m_sNote = pSet->m_sNote;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodiceRepartoInviante) || bCopyAll)
		m_sCodiceRepartoInviante = pSet->m_sCodiceRepartoInviante;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodiceMedicoInviante) || bCopyAll)
		m_sCodiceMedicoInviante = pSet->m_sCodiceMedicoInviante;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sMedicoInviante) || bCopyAll)
		m_sMedicoInviante = pSet->m_sMedicoInviante;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNosologico) || bCopyAll)
		m_sNosologico = pSet->m_sNosologico;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sUrgenza) || bCopyAll)
		m_sUrgenza = pSet->m_sUrgenza;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDEsameIns) || bCopyAll)
		m_lIDEsameIns = pSet->m_lIDEsameIns;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bTrasferito) || bCopyAll)
		m_bTrasferito = pSet->m_bTrasferito;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sIDProvetta) || bCopyAll)
		m_sIDProvetta = pSet->m_sIDProvetta;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bAcqSegnalata) || bCopyAll)
		m_bAcqSegnalata = pSet->m_bAcqSegnalata;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bErogazioneSegnalata) || bCopyAll)
		m_bErogazioneSegnalata = pSet->m_bErogazioneSegnalata;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bAppuntamentoSegnalato) || bCopyAll)
		m_bAppuntamentoSegnalato = pSet->m_bAppuntamentoSegnalato;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pSet->m_bEliminato;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sAssIden) || bCopyAll)
		m_sAssIden = pSet->m_sAssIden;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCognome) || bCopyAll)
		m_sCognome = pSet->m_sCognome;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCognome2) || bCopyAll)
		m_sCognome2 = pSet->m_sCognome2;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sNome) || bCopyAll)
		m_sNome = pSet->m_sNome;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lDataNascitaCustom) || bCopyAll)
		m_lDataNascitaCustom = pSet->m_lDataNascitaCustom;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDataNascita) || bCopyAll)
		m_sDataNascita = pSet->m_sDataNascita;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIstatNascita) || bCopyAll)
		m_lIstatNascita = pSet->m_lIstatNascita;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sComuneNascita) || bCopyAll)
		m_sComuneNascita = pSet->m_sComuneNascita;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sIndirizzoResidenza) || bCopyAll)
		m_sIndirizzoResidenza = pSet->m_sIndirizzoResidenza;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIstatResidenza) || bCopyAll)
		m_lIstatResidenza = pSet->m_lIstatResidenza;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sComuneResidenza) || bCopyAll)
		m_sComuneResidenza = pSet->m_sComuneResidenza;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCapResidenza) || bCopyAll)
		m_sCapResidenza = pSet->m_sCapResidenza;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTelefono1) || bCopyAll)
		m_sTelefono1 = pSet->m_sTelefono1;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sTelefono2) || bCopyAll)
		m_sTelefono2 = pSet->m_sTelefono2;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCellulare1) || bCopyAll)
		m_sCellulare1 = pSet->m_sCellulare1;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCellulare2) || bCopyAll)
		m_sCellulare2 = pSet->m_sCellulare2;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodiceFiscale) || bCopyAll)
		m_sCodiceFiscale = pSet->m_sCodiceFiscale;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodiceSanitario) || bCopyAll)
		m_sCodiceSanitario = pSet->m_sCodiceSanitario;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodiceSTP) || bCopyAll)
		m_sCodiceSTP = pSet->m_sCodiceSTP;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodiceTEAM) || bCopyAll)
		m_sCodiceTEAM = pSet->m_sCodiceTEAM;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lSesso) || bCopyAll)
		m_lSesso = pSet->m_lSesso;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lAsl) || bCopyAll)
		m_lAsl = pSet->m_lAsl;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodiceMedicoCurante) || bCopyAll)
		m_sCodiceMedicoCurante = pSet->m_sCodiceMedicoCurante;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sMedicoCurante) || bCopyAll)
		m_sMedicoCurante = pSet->m_sMedicoCurante;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodiceCittadinanza) || bCopyAll)
		m_sCodiceCittadinanza = pSet->m_sCodiceCittadinanza;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCittadinanza) || bCopyAll)
		m_sCittadinanza = pSet->m_sCittadinanza;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDataRichiesta) || bCopyAll)
		m_sDataRichiesta = pSet->m_sDataRichiesta;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sRepartoInviante) || bCopyAll)
		m_sRepartoInviante = pSet->m_sRepartoInviante;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sProvincia) || bCopyAll)
		m_sProvincia = pSet->m_sProvincia;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lStatoAccettazione) || bCopyAll)
		m_lStatoAccettazione = pSet->m_lStatoAccettazione;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sUO) || bCopyAll)
		m_sUO = pSet->m_sUO;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sIDEpisodioRicovero) || bCopyAll)
		m_sIDEpisodioRicovero = pSet->m_sIDEpisodioRicovero;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sDataRicovero) || bCopyAll)
		m_sDataRicovero = pSet->m_sDataRicovero;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bCertificazioneMEF) || bCopyAll)
		m_bCertificazioneMEF = pSet->m_bCertificazioneMEF;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bCertificazioneSISS) || bCopyAll)
		m_bCertificazioneSISS = pSet->m_bCertificazioneSISS;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodAlfa) || bCopyAll)
		m_sCodAlfa = pSet->m_sCodAlfa;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sUlssResidenza) || bCopyAll)
		m_sUlssResidenza = pSet->m_sUlssResidenza;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sQuesitoDiagnostico) || bCopyAll)
		m_sQuesitoDiagnostico = pSet->m_sQuesitoDiagnostico;
	/* if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_bImporting) || bCopyAll)
		m_bImporting = pSet->m_bImporting; */
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sCodiceIstAssicurativa) || bCopyAll)
		m_sCodiceIstAssicurativa = pSet->m_sCodiceIstAssicurativa;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lIDMotivo) || bCopyAll)
		m_lIDMotivo = pSet->m_lIDMotivo;
	//Luiz - 13/05/2019 - P3 - Atualiza nome/sobrenome Médico - Inclui Médicos solicitantes
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sMedicoInviante2) || bCopyAll)
		m_sMedicoInviante2 = pSet->m_sMedicoInviante2;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sMedicoInviante3) || bCopyAll)
		m_sMedicoInviante3 = pSet->m_sMedicoInviante3;
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sMedicoInviante4) || bCopyAll)
		m_sMedicoInviante4 = pSet->m_sMedicoInviante4;

	//Julio - BUG 3285 - Adequação de laudos
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sIdentificazionePassaporto) || bCopyAll)
		m_sIdentificazionePassaporto = pSet->m_sIdentificazionePassaporto;
	//Julio - BUG 3285 - Adequação de laudos
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sIdentificazioneDoc1) || bCopyAll)
		m_sIdentificazioneDoc1 = pSet->m_sIdentificazioneDoc1;
	//Julio - BUG 3285 - Adequação de laudos
	if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sIdentificazioneDoc2) || bCopyAll)
		m_sIdentificazioneDoc2 = pSet->m_sIdentificazioneDoc2;

	//Gabriel - TCP
	if (m_bColumnsTCP)
	{
		if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_sOrderNumberCorrelati) || bCopyAll)
			m_sOrderNumberCorrelati = pSet->m_sOrderNumberCorrelati;
		if (!pSet->IsOpen() || pSet->IsFieldDirty(&pSet->m_lStatoTCP) || bCopyAll)
			m_lStatoTCP = pSet->m_lStatoTCP;
	}
}

void CExtOrdiniSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CExtOrdiniSet* pOV = (CExtOrdiniSet*)pOldValues;
	CExtOrdiniSet* pNV = (CExtOrdiniSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento);

	//sp.Execute("ID", pOV, &pOV->m_lID, pNV, &pNV->m_lID);
	sp.Execute("OrderNumber", pOV, &pOV->m_sOrderNumber, pNV, &pNV->m_sOrderNumber);
	sp.Execute("DataEsame", pOV, &pOV->m_sDataEsame, pNV, &pNV->m_sDataEsame);
	sp.Execute("Provenienza", pOV, &pOV->m_sProvenienza, pNV, &pNV->m_sProvenienza);
	sp.Execute("CodiceAgenda", pOV, &pOV->m_sCodiceAgenda, pNV, &pNV->m_sCodiceAgenda);
	sp.Execute("Note", pOV, &pOV->m_sNote, pNV, &pNV->m_sNote);
	sp.Execute("CodiceRepartoInviante", pOV, &pOV->m_sCodiceRepartoInviante, pNV, &pNV->m_sCodiceRepartoInviante);
	sp.Execute("CodiceMedicoInviante", pOV, &pOV->m_sCodiceMedicoInviante, pNV, &pNV->m_sCodiceMedicoInviante);
	sp.Execute("MedicoInviante", pOV, &pOV->m_sMedicoInviante, pNV, &pNV->m_sMedicoInviante);
	sp.Execute("Nosologico", pOV, &pOV->m_sNosologico, pNV, &pNV->m_sNosologico);
	sp.Execute("Urgenza", pOV, &pOV->m_sUrgenza, pNV, &pNV->m_sUrgenza);
	sp.Execute("IDEsameIns", pOV, &pOV->m_lIDEsameIns, pNV, &pNV->m_lIDEsameIns);
	sp.Execute("Trasferito", pOV, &pOV->m_bTrasferito, pNV, &pNV->m_bTrasferito);
	sp.Execute("IDProvetta", pOV, &pOV->m_sIDProvetta, pNV, &pNV->m_sIDProvetta);
	sp.Execute("AcqSegnalata", pOV, &pOV->m_bAcqSegnalata, pNV, &pNV->m_bAcqSegnalata);
	sp.Execute("ErogazioneSegnalata", pOV, &pOV->m_bErogazioneSegnalata, pNV, &pNV->m_bErogazioneSegnalata);
	sp.Execute("AppuntamentoSegnalato", pOV, &pOV->m_bAppuntamentoSegnalato, pNV, &pNV->m_bAppuntamentoSegnalato);
	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
	sp.Execute("AssIden", pOV, &pOV->m_sAssIden, pNV, &pNV->m_sAssIden);
	sp.Execute("Cognome", pOV, &pOV->m_sCognome, pNV, &pNV->m_sCognome);
	sp.Execute("Cognome2", pOV, &pOV->m_sCognome2, pNV, &pNV->m_sCognome2);
	sp.Execute("Nome", pOV, &pOV->m_sNome, pNV, &pNV->m_sNome);
	sp.Execute("DataNascitaCustom", pOV, &pOV->m_lDataNascitaCustom, pNV, &pNV->m_lDataNascitaCustom);
	sp.Execute("DataNascita", pOV, &pOV->m_sDataNascita, pNV, &pNV->m_sDataNascita);
	sp.Execute("IstatNascita", pOV, &pOV->m_lIstatNascita, pNV, &pNV->m_lIstatNascita);
	sp.Execute("ComuneNascita", pOV, &pOV->m_sComuneNascita, pNV, &pNV->m_sComuneNascita);
	sp.Execute("IndirizzoResidenza", pOV, &pOV->m_sIndirizzoResidenza, pNV, &pNV->m_sIndirizzoResidenza);
	sp.Execute("IstatResidenza", pOV, &pOV->m_lIstatResidenza, pNV, &pNV->m_lIstatResidenza);
	sp.Execute("ComuneResidenza", pOV, &pOV->m_sComuneResidenza, pNV, &pNV->m_sComuneResidenza);
	sp.Execute("CapResidenza", pOV, &pOV->m_sCapResidenza, pNV, &pNV->m_sCapResidenza);
	sp.Execute("Telefono1", pOV, &pOV->m_sTelefono1, pNV, &pNV->m_sTelefono1);
	sp.Execute("Telefono2", pOV, &pOV->m_sTelefono2, pNV, &pNV->m_sTelefono2);
	sp.Execute("Cellulare1", pOV, &pOV->m_sCellulare1, pNV, &pNV->m_sCellulare1);
	sp.Execute("Cellulare2", pOV, &pOV->m_sCellulare2, pNV, &pNV->m_sCellulare2);
	sp.Execute("CodiceFiscale", pOV, &pOV->m_sCodiceFiscale, pNV, &pNV->m_sCodiceFiscale);
	sp.Execute("CodiceSanitario", pOV, &pOV->m_sCodiceSanitario, pNV, &pNV->m_sCodiceSanitario);
	sp.Execute("CodiceSTP", pOV, &pOV->m_sCodiceSTP, pNV, &pNV->m_sCodiceSTP);
	sp.Execute("CodiceTEAM", pOV, &pOV->m_sCodiceTEAM, pNV, &pNV->m_sCodiceTEAM);
	sp.Execute("Sesso", pOV, &pOV->m_lSesso, pNV, &pNV->m_lSesso);
	sp.Execute("Asl", pOV, &pOV->m_lAsl, pNV, &pNV->m_lAsl);
	sp.Execute("CodiceMedicoCurante", pOV, &pOV->m_sCodiceMedicoCurante, pNV, &pNV->m_sCodiceMedicoCurante);
	sp.Execute("MedicoCurante", pOV, &pOV->m_sMedicoCurante, pNV, &pNV->m_sMedicoCurante);
	sp.Execute("CodiceCittadinanza", pOV, &pOV->m_sCodiceCittadinanza, pNV, &pNV->m_sCodiceCittadinanza);
	sp.Execute("Cittadinanza", pOV, &pOV->m_sCittadinanza, pNV, &pNV->m_sCittadinanza);
	sp.Execute("DataRichiesta", pOV, &pOV->m_sDataRichiesta, pNV, &pNV->m_sDataRichiesta);
	sp.Execute("RepartoInviante", pOV, &pOV->m_sRepartoInviante, pNV, &pNV->m_sRepartoInviante);
	sp.Execute("Provincia", pOV, &pOV->m_sProvincia, pNV, &pNV->m_sProvincia);
	sp.Execute("StatoAccettazione", pOV, &pOV->m_lStatoAccettazione, pNV, &pNV->m_lStatoAccettazione);
	sp.Execute("UO", pOV, &pOV->m_sUO, pNV, &pNV->m_sUO);
	sp.Execute("IDEpisodioRicovero", pOV, &pOV->m_sIDEpisodioRicovero, pNV, &pNV->m_sIDEpisodioRicovero);
	sp.Execute("DataRicovero", pOV, &pOV->m_sDataRicovero, pNV, &pNV->m_sDataRicovero);
	sp.Execute("CertificazioneMEF", pOV, &pOV->m_bCertificazioneMEF, pNV, &pNV->m_bCertificazioneMEF);
	sp.Execute("CertificazioneSISS", pOV, &pOV->m_bCertificazioneSISS, pNV, &pNV->m_bCertificazioneSISS);
	sp.Execute("CodAlfa", pOV, &pOV->m_sCodAlfa, pNV, &pNV->m_sCodAlfa);
	sp.Execute("UlssResidenza", pOV, &pOV->m_sUlssResidenza, pNV, &pNV->m_sUlssResidenza);
	sp.Execute("QuesitoDiagnostico", pOV, &pOV->m_sQuesitoDiagnostico, pNV, &pNV->m_sQuesitoDiagnostico);
	// sp.Execute("IMPORTING", pOV, &pOV->m_bImporting, pNV, &pNV->m_bImporting);
	sp.Execute("CODICEISTASSICURATIVA", pOV, &pOV->m_sCodiceIstAssicurativa, pNV, &pNV->m_sCodiceIstAssicurativa);
	sp.Execute("IDMOTIVO", pOV, &pOV->m_lIDMotivo, pNV, &pNV->m_lIDMotivo);
	//Luiz - 13/05/2019 - P3 - Atualiza nome/sobrenome Médico - Inclui Médicos solicitantes
	sp.Execute("MedicoInviante2", pOV, &pOV->m_sMedicoInviante2, pNV, &pNV->m_sMedicoInviante2);
	sp.Execute("MedicoInviante3", pOV, &pOV->m_sMedicoInviante3, pNV, &pNV->m_sMedicoInviante3);
	sp.Execute("MedicoInviante4", pOV, &pOV->m_sMedicoInviante4, pNV, &pNV->m_sMedicoInviante4);
	
	sp.Execute("IdentificazionePassaporto", pOV, &pOV->m_sIdentificazionePassaporto, pNV, &pNV->m_sIdentificazionePassaporto);	//Julio - BUG 3285 - Adequação de laudos
	sp.Execute("IdentificazioneDoc_1", pOV, &pOV->m_sIdentificazioneDoc1, pNV, &pNV->m_sIdentificazioneDoc1);					//Julio - BUG 3285 - Adequação de laudos
	sp.Execute("IdentificazioneDoc_2", pOV, &pOV->m_sIdentificazioneDoc2, pNV, &pNV->m_sIdentificazioneDoc2);					//Julio - BUG 3285 - Adequação de laudos
	
	//Gabriel - TCP
	if (m_bColumnsTCP)
	{
		sp.Execute("ORDERNUMBERCORRELATI", pOV, &pOV->m_sOrderNumberCorrelati, pNV, &pNV->m_sOrderNumberCorrelati); //Gabriel - TCP
		sp.Execute("STATOTCP", pOV, &pOV->m_lStatoTCP, pNV, &pNV->m_lStatoTCP); //Gabriel - TCP
	}
		
}

BOOL CExtOrdiniSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CExtOrdiniSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CExtOrdiniSet::DeleteRecordset");
	}
	return bReturn;
}

CString CExtOrdiniSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	CString strUO;
	strUO.Format("UO='%s'", CUOSet().GetCodiceIntegrazione(theApp.m_lUO, TRUE));
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

/* BOOL CExtOrdiniSet::UpdateRecordset(const CString &strCommento)
{
	if (m_nEditMode == addnew)
		m_lUO = theApp.m_lUO;

	return CBaseSet::UpdateRecordset(strCommento);
} */

BOOL CExtOrdiniSet::IsExtOrdiniRequest(long idEsame)
{
	BOOL bReturn = FALSE;
	CString filter;
	filter.Format("idEsameIns = %li", idEsame);

	SetOpenFilter(filter);

	if (OpenRecordset("CExtOrdiniSet::IsExtOrdiniRequest"))
	{
		if (!IsEOF())
			bReturn = TRUE;

		CloseRecordset("CExtOrdiniSet::IsExtOrdiniRequest");
	}
	
	return bReturn;
}

CString CExtOrdiniSet::GetAssiden(long lID)
{
	CString sReturn = "";

	CString sFilter;
	if (lID < 0)
		sFilter.Format("ID=%li", -lID);
	else
		sFilter.Format("ID=%li", lID);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CExtOrdiniSet::GetAssiden"))
	{
		if (!IsEOF())
			sReturn = m_sAssIden;

		CloseRecordset("CExtOrdiniSet::GetAssiden");
	}

	return sReturn;
}

void CExtOrdiniSet::GetDataFromFichaItem(CString sFichaItem, long &lID, long& lIDEsameIns)
{
	lID = 0;
	lIDEsameIns = 0;

	sFichaItem.Replace("'", "''");
	sFichaItem.Trim();

	CString sFilter;
	sFilter.Format("ORDERNUMBER='%s'", sFichaItem);

	SetBaseFilter("(UO='' OR UO<>'')");
	SetOpenFilter(sFilter);
	if (OpenRecordset("CExtOrdiniSet::GetIDEsameInsFromFichaItem"))
	{
		if (!IsEOF())
		{
			lID = m_lID;

			if (!IsFieldNull(&m_lIDEsameIns))
				lIDEsameIns = m_lIDEsameIns;
		}

		CloseRecordset("CExtOrdiniSet::GetIDEsameInsFromFichaItem");
	}
}

CString CExtOrdiniSet::GetPriorityFromID(long lIDEsame)
{
	CString sReturn = "";
	CString filter;
	filter.Format("idEsameIns=%li", lIDEsame);

	SetOpenFilter(filter);

	if (OpenRecordset("CExtOrdiniSet::GetPriorityFromID"))
	{
		if (!IsEOF())
		{
			sReturn = m_sUrgenza;

			if (theApp.m_bPersonalizzazioniBrasileSirio)
			{
				long lTemp = atol(sReturn);
				switch (lTemp)
				{
				case 1:
				{
					sReturn = theApp.GetMessageString(IDS_URGENZA_SIRIO_1);
					break;
				}
				case 3:
				{
					sReturn = theApp.GetMessageString(IDS_URGENZA_SIRIO_3);
					break;
				}
				case 7:
				{
					sReturn = theApp.GetMessageString(IDS_URGENZA_SIRIO_7);
					break;
				}
				case 8:
				{
					sReturn = theApp.GetMessageString(IDS_URGENZA_SIRIO_8);
					break;
				}
				}
			}
		}

		CloseRecordset("CExtOrdiniSet::GetPriorityFromID");
	}

	return sReturn;
}

BOOL CExtOrdiniSet::SetStatoRichiesta(const long lIDEsame, const long lStato)
{
	BOOL bReturn = FALSE;

	CString filter;
	filter.Format("idEsameIns = %li", lIDEsame);

	SetOpenFilter(filter);

	if (OpenRecordset("CExtOrdiniSet::SetStatoRichiesta"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CExtOrdiniSet::SetStatoRichiesta"))
			{
				m_lStatoAccettazione = lStato;

				if (UpdateRecordset("CExtOrdiniSet::SetStatoRichiesta"))
					bReturn = TRUE;
			}
		}

		CloseRecordset("CExtOrdiniSet::SetStatoRichiesta");
	}

	return bReturn;
}

//Gabriel BUG 6225 - Lista DO
long CExtOrdiniSet::GetOrdineId(long lIdEsame)
{
	long lReturn = 0;

	CString sFilter;
	sFilter.Format("IDESAMEINS=%li", lIdEsame);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CExtOrdiniSet::GetOrdineId"))
	{
		if (!IsEOF())
			lReturn = m_lID;

		CloseRecordset("CExtOrdiniSet::GetOrdineId");
	}

	return lReturn;
}