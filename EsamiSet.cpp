#include "stdafx.h"
#include "Endox.h"
#include "EsamiSet.h"

#include "DLL_Imaging\h\AMLogin.h"

#include "Common.h"
#include "CustomDate.h"
#include "DistrettiSediEsamiSet.h"
#include "EsamiChiusiSet.h"
#include "EsamiControlloQualitaSet.h"
#include "EsamiConvalidatiSet.h"
#include "EsamiRefertazioneRemotaSet.h"
#include "EsamiSbloccatiSet.h"
#include "EsamiView.h"
#include "ExtOrdiniSet.h"
#include "FirmaMotivoSostituzioneDlg.h"
#include "ListaPrenotazioniCupDlg.h"
#include "MainFrm.h"
#include "MediciSet.h"
#include "PazientiSet.h"
#include "PdfManager.h"
#include "RefertoForm.h"
#include "UOSet.h"
#include "UtentiSet.h"
#include "VistaEsamiPendentiSet.h"
#include "RiconvocazioneSet.h" //Gabriel BUG 6225 - Lista DO

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEsamiSet, CBaseSet)

CEsamiSet::CEsamiSet(BOOL bDefaultFieldSet)
	: CBaseSet(&m_lContatore, "CONTATORE"),
	  m_setEP(bDefaultFieldSet)
{
	SetBaseFilter("");
	SetEmpty();

	m_bDefaultFieldSet = bDefaultFieldSet;
	m_bUpdatingAPStato = FALSE;
	m_bColumnsP3 = CheckColumnExists("EESAMI", "HYPERLOCKED") && CheckColumnExists("EESAMI", "IDUTENTEHYPERLOCK") && CheckColumnExists("EESAMI", "DATAORAHYPERLOCK");
	m_bColumnsTCP = CheckColumnExists("EESAMI", "STATOINVIOALTRAUNITA"); //Gabriel - TCP

	m_nFields = 236 - (m_bColumnsP3 ? 0 : 3) - (m_bColumnsTCP ? 0 : 5); //Gabriel - TCP
}

void CEsamiSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Contatore", m_lContatore);
	if (m_nFields == 2)
	{
		RFX_Long(pFX, "IDVersione", m_lIDVersione);
	}
	else if (m_nFields > 2)
	{
		RFX_Text(pFX,	"Ricovero",						m_sRicovero,						  50);
		RFX_Text(pFX,	"CodEsame",						m_sCodEsame,						3999);
		RFX_Long(pFX,	"Paziente",						m_lPaziente);
		RFX_Long(pFX,	"IDEsame",						m_lIDEsame);
		RFX_Long(pFX,	"Data",							m_lData);
		RFX_Long(pFX,	"Medico",						m_lMedico);
		RFX_Text(pFX,	"MedicoLibero",					m_sMedicoLibero,					 255);
		RFX_Long(pFX,	"Assistente",					m_lAssistente);
		RFX_Text(pFX,	"AssistenteLibero",				m_sAssistenteLibero,				 255);
		RFX_Text(pFX,	"Anestesista",					m_sAnestesista,						 255);
		RFX_Long(pFX,	"Infermiere1",					m_lInfermiere1);
		RFX_Long(pFX,	"Infermiere2",					m_lInfermiere2);
		RFX_Text(pFX,	"Terapia",						m_sTerapia,							3999);
		RFX_Long(pFX,	"DataControllo",				m_lDataControllo);
		RFX_Long(pFX,	"Durata",						m_lDurata);
		RFX_Long(pFX,	"Difficolta",					m_lDifficolta);
		RFX_Text(pFX,	"Conclusioni",					m_sConclusioni,						3999);
		RFX_Text(pFX,	"Integrazioni",					m_sIntegrazioni,					3999);
		RFX_Text(pFX,	"Appunti",						m_sAppunti,							3999);
		RFX_Text(pFX,	"Indicazioni",					m_sIndicazioni,						3999);
		RFX_Text(pFX,	"FarmacoTrial",					m_sFarmacoTrial,					3999);
		RFX_Text(pFX,	"Studio",						m_sStudio,							3999);
		RFX_Text(pFX,	"TipoVisita",					m_sTipoVisita,						3999);
		RFX_Long(pFX,	"IdPremedicazione",				m_lIdPremedicazione);
		RFX_Text(pFX,	"Premedicazioni",				m_sPremedicazioni,					3999);
		RFX_Text(pFX,	"Strumenti",					m_sStrumenti,						3999);
		RFX_Text(pFX,	"Accessori",					m_sAccessori,						3999);
		RFX_Text(pFX,	"ProgressivoAnno",				m_sProgressivoAnno,					3999);
		RFX_Text(pFX,	"CodicePrenotazione",			m_sCodicePrenotazione,				  50);
		RFX_Text(pFX,	"Valutazione",					m_sValutazione,						3999);
		RFX_Text(pFX,	"ComplicanzeOld",				m_sComplicanzeOld,					3999);
		RFX_Text(pFX,	"Guarigione",					m_sGuarigione,						3999);
		RFX_Text(pFX,	"Quadro",						m_sQuadro,							3999);
		RFX_Text(pFX,	"Metodo",						m_sMetodo,							3999);
		RFX_Text(pFX,	"Estensione",					m_sEstensione,						3999);
		RFX_Text(pFX,	"ProcTerapeutiche",				m_sProcTerapeutiche,				3999);
		RFX_Text(pFX,	"ProcDiagnostiche",				m_sProcDiagnostiche,				3999);
		RFX_Text(pFX,	"MstComplicanze1",				m_sMstComplicanze1,					3999);
		RFX_Text(pFX,	"MstComplicanze2",				m_sMstComplicanze2,					3999);
		RFX_Text(pFX,	"MstComplicanze3",				m_sMstComplicanze3,					3999);
		RFX_Long(pFX,	"Provenienza",					m_lProvenienza);
		RFX_Long(pFX,	"Inviante",						m_lInviante);
		RFX_Long(pFX,	"Camera",						m_lCamera);
		RFX_Text(pFX,	"InvMedico",					m_sInvMedico,						3999);
		RFX_Long(pFX,	"IdInvMedico",					m_lInvMedico);
		RFX_Long(pFX,	"Fumo",							m_lFumo);
		RFX_Long(pFX,	"Sigarette",					m_lSigarette);
		RFX_Long(pFX,	"Caffe",						m_lCaffe);
		RFX_Long(pFX,	"Alcool",						m_lAlcool);
		RFX_Long(pFX,	"Superalcolici",				m_lSuperAlcolici);
		RFX_Text(pFX,	"Den_Farmaci",					m_sDenFarmaci,						3999);
		RFX_Long(pFX,	"Assunzione",					m_lAssunzione);
		RFX_Single(pFX, "Peso",							m_fPeso);
		RFX_Single(pFX, "Altezza",						m_fAltezza);
		RFX_Single(pFX, "BMI",							m_fBMI);
		RFX_Single(pFX, "MISURAA",						m_fMisuraA);
		RFX_Single(pFX, "MISURAB",						m_fMisuraB);
		RFX_Single(pFX, "MISURAC",						m_fMisuraC);
		RFX_Single(pFX, "VOLUME",						m_fVolume);
		RFX_Single(pFX, "BSA",							m_fBSA);
		RFX_Text(pFX,	"Complicanze1", m_sComplicanze1, 255);
		RFX_Text(pFX,	"Complicanze2",					m_sComplicanze2,					 255);
		RFX_Text(pFX,	"Complicanze3",					m_sComplicanze3,					 255);
		RFX_Long(pFX,	"IDVersione",					m_lIDVersione);
		RFX_Text(pFX,	"NoteMonitoraggio",				m_sNoteMonitoraggio,				3999);
		RFX_Long(pFX,	"InfermiereMonitoraggio",		m_lInfermiereMonitoraggio);
		RFX_Long(pFX,	"Ospedale",						m_lOspedale);
		RFX_Int(pFX,	"CodiceRAO",					m_nCodiceRAO);
		RFX_Bool(pFX,	"Concordanza",					m_bConcordanza);
		RFX_Int(pFX,	"CodiceRAOSpec",				m_nCodiceRAOSpec);
		RFX_Int(pFX,	"ConsensoInformato",			m_iConsensoInformato);
		RFX_Text(pFX,	"NoteConsensoInformato",		m_sNoteConsensoInformato,			 255);
		RFX_Int(pFX,	"Allergie",						m_iAllergie);
		RFX_Text(pFX,	"DescrizioneAllergie",			m_sDescrizioneAllergie,				 255);
		RFX_Int(pFX,	"Pacemaker",					m_iPacemaker);
		RFX_Text(pFX,	"DescrizionePacemaker",			m_sDescrizionePacemaker,			 255);
		RFX_Int(pFX,	"Anticoagulanti",				m_iAnticoagulanti);
		RFX_Text(pFX,	"DescrizioneAnticoagulanti",	m_sDescrizioneAnticoagulanti,		 255);
		RFX_Int(pFX,	"Antiaggreganti",				m_iAntiaggreganti);
		RFX_Text(pFX,	"DescrizioneAntiaggreganti",	m_sDescrizioneAntiaggreganti,		 255);
		RFX_Int(pFX,	"BreathTestHP",					m_iBreathTestHP);
		RFX_Single(pFX, "BreathTestHPVal1",				m_fBreathTestHPVal1);
		RFX_Single(pFX, "BreathTestHPVal2",				m_fBreathTestHPVal2);
		RFX_Single(pFX, "BreathTestHPDiff",				m_fBreathTestHPDiff);
		RFX_Long(pFX,	"IDSedeEsame",					m_lIDSedeEsame);
		RFX_Text(pFX,	"SalaEsame",					m_sSalaEsame,						 255);
		RFX_Long(pFX,	"TipoDegenzaInterno",			m_lTipoDegenzaInterno);
		RFX_Long(pFX,	"TipoDegenzaEsterno",			m_lTipoDegenzaEsterno);
		RFX_Long(pFX,	"FluoroscopiaMinuti",			m_lFluoroscopiaMinuti);
		RFX_Long(pFX,	"FluoroscopiaSecondi",			m_lFluoroscopiaSecondi);
		RFX_Single(pFX,	"FluoroscopiaDose",				m_fFluoroscopiaDose);
		RFX_Bool(pFX,	"Firmato",                      m_bFirmato);								// Davide - Firma digitale
		RFX_Bool(pFX,	"Locked",						m_bLocked);
		RFX_Long(pFX,	"idUtenteLock",					m_lIdUtenteLock);
		RFX_Text(pFX,	"DataOraLock",					m_sDataOraLock,						  50);
		RFX_Long(pFX,	"idSedePrevista",				m_lIDSedePrevista);							// Gli ID delle sedi servono per gli interfacciamenti, NON RIMUOVERE!
		RFX_Text(pFX,	"SedePrevista",					m_sSedePrevista,					  50);
		RFX_Long(pFX,	"idSedeRaggiunta",				m_lIDSedeRaggiunta);						// Gli ID delle sedi servono per gli interfacciamenti, NON RIMUOVERE!
		RFX_Text(pFX,	"SedeRaggiunta",				m_sSedeRaggiunta,					  50);
		RFX_Text(pFX,	"APDataInvio",					m_sAPDataInvio,						  14);
		RFX_Text(pFX,	"APOperInvio",					m_sAPOperInvio,						  50);
		RFX_Text(pFX,	"APDataAnnullamento",			m_sAPDataAnnullamento,				  14);
		RFX_Text(pFX,	"APOperAnnullamento",			m_sAPOperAnnullamento,				  50);
		RFX_Text(pFX,	"APDataRicezione",				m_sAPDataRicezione,					  14);
		RFX_Text(pFX,	"APDataConferma",				m_sAPDataConferma,					  14);
		RFX_Text(pFX,	"APOperConferma",				m_sAPOperConferma,					  50);
		RFX_Long(pFX,	"APStato",						m_lAPStato);
		RFX_Text(pFX,	"APMotivazioneRifiuto",			m_sAPMotivazioneRifiuto,			 255);
		RFX_Text(pFX,	"APDescrizioneRichiesta",		m_sAPDescrizioneRichiesta,			3999);
		RFX_Text(pFX,	"APRispostaCodificata",			m_sAPRispostaCodificata,			   8);
		RFX_Text(pFX,	"APRispostaLibera",				m_sAPRispostaLibera,				_TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX,	"APRefertoPDF",					m_sAPRefertoPDF,					 255);
		RFX_Text(pFX,	"APSuggerimenti1",				m_sAPSuggerimenti1,					3999);
		RFX_Text(pFX,	"APSuggerimenti2",				m_sAPSuggerimenti2,					3999);
		RFX_Text(pFX,	"APIDRichiesta",				m_sAPIDRichiesta,					  20);
		RFX_Int(pFX,	"APSpedireRitirare",			m_nAPSpedireRitirare);
		RFX_Bool(pFX,	"APRefertato",					m_bAPRefertato);
		RFX_Bool(pFX,	"APVerificato",					m_bAPVerificato);
		RFX_Int(pFX,	"APVerificatoMedico",			m_nAPVerificatoMedico);
		RFX_Bool(pFX,	"APSpeditoRitirato",			m_bAPSpeditoRitirato);
		RFX_Text(pFX,	"APDataVerificato",				m_sAPDataVerificato,				  14);
		RFX_Text(pFX,	"APDataSpeditoRitirato",		m_sAPDataSpeditoRitirato,			  14);
		RFX_Text(pFX,	"APProvenienza",				m_sAPProvenienza,					   9);
		RFX_Text(pFX,	"APConvenzione",				m_sAPConvenzione,					   9);
		RFX_Text(pFX,	"APIndirizzo",					m_sAPIndirizzo,						 255);
		RFX_Int(pFX,	"APEseguitiPrelievi",			m_nAPEseguitiPrelievi);
		RFX_Long(pFX,	"APIdRicetta",					m_lAPIdRicetta);
		RFX_Text(pFX,	"APGroupNumber",				m_sAPGroupNumber,					  50);
		RFX_Long(pFX,	"IDComplicanzeImmediate",		m_lIDComplicanzeImmediate);
		RFX_Long(pFX,	"IDComplicanzeTardive",			m_lIDComplicanzeTardive);
		RFX_Long(pFX,	"IDPulizia",					m_lIDPulizia);
		RFX_Long(pFX,	"IDCausaNonCompleto",			m_lIDCausaNonCompleto);
		RFX_Bool(pFX,	"NecAssistenzaOspedaliera",		m_bNecAssistenzaOspedaliera);
		RFX_Long(pFX,	"IDTolleranza",					m_lIDTolleranza);
		RFX_Text(pFX,	"PremedPosologia",				m_sPremedPosologia,					3999);
		RFX_Long(pFX,	"IDConclusioniScreening",		m_lIDConclusioniScreening);
		RFX_Long(pFX,	"IDConclusioniColon",			m_lIDConclusioniColon);
		RFX_Long(pFX,	"IDAltreAnomalie",				m_lIDAltreAnomalie);
		RFX_Bool(pFX,	"SuperLocked",					m_bSuperLocked);
		RFX_Long(pFX,	"idUtenteSuperLock",			m_lIdUtenteSuperLock);
		RFX_Text(pFX,	"DataOraSuperLock",				m_sDataOraSuperLock,				  50);
		RFX_Text(pFX,	"DataOraSuperLockPrimo",		m_sDataOraSuperLockPrimo,			  50);
		RFX_Bool(pFX,	"InviatoScreening",				m_bInviatoScreening);
		RFX_Long(pFX,	"idDiagnosiFinale",				m_lIDDiagnosiFinale);
		RFX_Int(pFX,	"Sospeso",						m_iSospeso);
		RFX_Long(pFX,	"DataScadenzaSospensione",		m_lDataScadenzaSospensione);
		RFX_Text(pFX,	"MotivoSospensione",			m_sMotivoSospensione,				3999);
		RFX_Text(pFX,	"DataOraAcquisizione",			m_sDataOraAcquisizione,				  50);
		RFX_Text(pFX,	"TempoConvalida",				m_sTempoConvalida,					  50);
		RFX_Text(pFX,	"TempoChiusura",				m_sTempoChiusura,					  50);
		RFX_Long(pFX,	"CustomDataOraInizioAcq",		m_lCustomDataOraInizioAcq);
		RFX_Long(pFX,	"CustomDataOraFineAcq",			m_lCustomDataOraFineAcq);
		RFX_Text(pFX,	"PressioneSanguigna1",			m_sPressione1,						  10);
		RFX_Text(pFX,	"PressioneSanguigna2",			m_sPressione2,						  10);

		RFX_Bool(pFX,	"InviatoInps",					m_bInviatoInps);
		RFX_Long(pFX,	"InpsDataInizio",				m_lInpsDataInizio);
		RFX_Long(pFX,	"InpsDataFine",					m_lInpsDataFine);
		RFX_Int(pFX,	"InpsTipo",						m_iInpsTipo);
		RFX_Text(pFX,	"InpsNote",						m_sInpsNote,						 255);
		RFX_Text(pFX,	"InpsCognome",					m_sInpsCognome,						  50);
		RFX_Text(pFX,	"InpsVia",						m_sInpsVia,							 150);
		RFX_Text(pFX,	"InpsCap",						m_sInpsCap,							   5);
		RFX_Text(pFX,	"InpsComune",					m_sInpsComune,						  50);
		RFX_Text(pFX,	"InpsProvincia",				m_sInpsProvincia,					   5);
		RFX_Text(pFX,	"InpsIdAnnullamento",			m_sInpsIdAnnullamento,				  50);
		RFX_Text(pFX,	"InpsNumeroProtocollo",			m_sInpsNumeroProtocollo,			  50);

		RFX_Bool(pFX,	"SissOscuramento10",			m_bSissOscuramento10);
		RFX_Bool(pFX,	"SissOscuramento20",			m_bSissOscuramento20);
		RFX_Bool(pFX,	"SissOscuramento30",			m_bSissOscuramento30);
		RFX_Bool(pFX,	"SissOscuramento40",			m_bSissOscuramento40);
		RFX_Bool(pFX,	"SissOscuramento50",			m_bSissOscuramento50);
		RFX_Bool(pFX,	"SissOscuramento50Bloccato",	m_bSissOscuramento50Bloccato);
		RFX_Bool(pFX,	"SissAutorizzazioneConsultaz",  m_bSissAutorizzazioneConsultaz);
		RFX_Text(pFX,	"SissNoteReperibilita",			m_sSissNoteReperibilita,			 255);

		RFX_Text(pFX,	"IdEpisodioRicovero",			m_sIdEpisodioRicovero,				  50);
		RFX_Long(pFX,	"DataRicoveroCustom",			m_lDataRicoveroCustom);

		RFX_Long(pFX,	"IDMalattiaCronica",			m_lIDMalattiaCronica);
		RFX_Bool(pFX,	"RecordSenzaAccesso",			m_bRecordSenzaAccesso);

		RFX_Text(pFX,	"PazientiCroniciScoreHB",		m_sPazientiCroniciScoreHB,			  50);
		RFX_Text(pFX,	"PazientiCroniciScoreS",		m_sPazientiCroniciScoreS,			  50);

		RFX_Long(pFX,	"IDStudio",						m_lIDStudio);
		RFX_Long(pFX,	"DataStudio",					m_lDataStudio);

		RFX_Long(pFX,	"IDUtenteInserimentoEsame",		m_lIDUtenteInserimentoEsame);

		RFX_Long(pFX,	"DataRefertoIstologico",		m_lDataRefertoIstologico);
		RFX_Bool(pFX,	"PresenzaLesioneSospettaCCR",	m_bPresenzaLesioneSospettaCCR);
		RFX_Long(pFX,	"NumeroTotalePolipi",			m_lNumeroTotalePolipi);		

		RFX_Long(pFX,	"BostonScoreDx",				m_lBostonScoreDx);
		RFX_Long(pFX,	"BostonScoreMid",				m_lBostonScoreMid);
		RFX_Long(pFX,	"BostonScoreSx",				m_lBostonScoreSx);
		RFX_Long(pFX,	"TempoRetrazione",				m_lTempoRetrazione);

		RFX_Text(pFX,	"EsenzioneDaIntegrazione",		m_sEsenzioneDaIntegrazione, 50);
		RFX_Bool(pFX,	"PagamentoRicevuto",			m_bPagamentoRicevuto);

		RFX_Bool(pFX,   "EsameNonSbloccabile",			m_bNonSbloccabile);

		RFX_Text(pFX,	"RefertoTestoRtf",				m_sRefertoTestoRtf,					_TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX,	"RefertoTestoTxt",				m_sRefertoTestoTxt,					_TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX,	"RefertoTestoHtml",				m_sRefertoTestoHtml,				_TEXT_CONTROL_FIELD_LIMIT);
		RFX_Text(pFX,	"RefertoDataOra",				m_sRefertoDataOra,					  14);
		RFX_Long(pFX,	"RefertoRedattore",				m_lRefertoRedattore);
		RFX_Bool(pFX,	"RefertoScaduto",				m_bRefertoScaduto);
		RFX_Long(pFX,	"RefertoStato",					m_lRefertoStato);

		RFX_Bool(pFX,	"ChiusuraBloccataDaInteg",	    m_bChiusuraBloccataDaIntegrazione);

		RFX_Long(pFX,	"LivelloUrgenza",				m_lLivelloUrgenza);
		RFX_Long(pFX,	"FrazioneEiezione",				m_lFrazioneEiezione);
		RFX_Long(pFX,	"IdProvenienzaNew",				m_lIdProvenienzaNew);
		RFX_Long(pFX,	"STATOINVIOCENTRALEREFERTAZ",	m_lStatoInvioCentraleRefertaz);
		RFX_Long(pFX,	"STATOINVIOCONTROLLOQUALITA",	m_lStatoInvioControlloQualita);

		RFX_Long(pFX,	"VERSIONEGRIDCL",				m_lVersioneGridCL);

		RFX_Text(pFX,	"QUESITODIAGNOSTICO",			m_sQuesitoDiagnostico, 3999);		
		RFX_Text(pFX,	"QUESITODIAGNOSTICOCODIFICATO", m_sQuesitoDiagnosticoCodificato, 50);

		RFX_Long(pFX,	"IDULTIMACHECKLISTUSATA",		m_lIDUltimaChecklistUsata);

		RFX_Text(pFX,	"FCMASSIMA",					m_sFCMassima,					  50);
		RFX_Text(pFX,	"FCSUBMASSIMA",					m_sFCSubmassima,				  50);
		RFX_Long(pFX,	"IDPROTOCOLLOUSATO",			m_lIDProtocolloUsato);

		RFX_Text(pFX,	"REFERTOCONIUGATOPRINCIPALE",	m_sRefertoConiugatoPrincipale,	  50);
		RFX_Text(pFX,	"REFERTOCONIUGATOSECONDARIO",	m_sRefertoConiugatoSecondario,	  50);
		RFX_Bool(pFX,	"REFERTOCONIUGATOALTRAUO",		m_bRefertoConiugatoAltraUO);
		RFX_Bool(pFX,	"REFERTOCONIUGATOIMPORTATO",	m_bRefertoConiugatoImportato);

		RFX_Text(pFX,	"FLEURYTRASFERITO",				m_sFleuryTrasferito,			  50);
		RFX_Text(pFX,	"FLEURYENDPOINTREMOTO",			m_sFleuryEndpointRemoto,		1024);

		RFX_Bool(pFX,	"Eliminato",					m_bEliminato);
		RFX_Long(pFX,	"UO",							m_lUO);
		//Luiz - 13/05/2019 - P3 - Atualiza nome/sobrenome Médico - Inclui Médicos solicitantes
		RFX_Text(pFX,   "InvMedico2",                   m_sInvMedico2, 3999);
		RFX_Long(pFX,   "IdInvMedico2",                 m_lInvMedico2);
		RFX_Text(pFX,   "InvMedico3",                   m_sInvMedico3, 3999);
		RFX_Long(pFX,   "IdInvMedico3",                 m_lInvMedico3);
		RFX_Text(pFX,   "InvMedico4",                   m_sInvMedico4, 3999);
		RFX_Long(pFX,   "IdInvMedico4",                 m_lInvMedico4); 
		
		//Gabriel - P3
		if (m_bColumnsP3)
		{
			RFX_Bool(pFX, "HyperLocked", m_bHyperLocked);
			RFX_Long(pFX, "IdUtenteHyperLock", m_lIdUtenteHyperLock);
			RFX_Text(pFX, "DataOraHyperLock", m_sDataOraHyperLock, 50);
		}
		//Gabriel - TCP
		if (m_bColumnsTCP)
		{
			RFX_Long(pFX, "STATOINVIOALTRAUNITA", m_lStatoInvioAltraUnita);
			RFX_Text(pFX, "CODESAMECORRELATI", m_sCodesameCorrelati, 50);
			RFX_Text(pFX, "RefertoTestoCorrelatiRtf", m_sRefertoTestoCorrelatiRtf, _TEXT_CONTROL_FIELD_LIMIT);
			RFX_Text(pFX, "RefertoTestoCorrelatiTxt", m_sRefertoTestoCorrelatiTxt, _TEXT_CONTROL_FIELD_LIMIT);
			RFX_Text(pFX, "RefertoTestoCorrelatiHtml", m_sRefertoTestoCorrelatiHtml, _TEXT_CONTROL_FIELD_LIMIT);
		}

	}
}

CString CEsamiSet::GetDefaultSQL()
{
	return m_bDefaultFieldSet ? "EEsamiValoriDefault" : "EEsami";
}

void CEsamiSet::SetEmpty()
{
	m_lContatore = 0;
	m_sRicovero = "";
	m_sCodEsame = "";
	m_lPaziente = 0;
	m_lIDEsame = 0;
	m_lData = 0;
	m_lMedico = 0;
	m_sMedicoLibero = "";
	m_lAssistente = 0;
	m_sAssistenteLibero = "";
	m_sAnestesista = "";
	m_lInfermiere1 = 0;
	m_lInfermiere2 = 0;
	m_sTerapia = "";
	m_lDataControllo = 0;
	m_lDurata = 0;
	m_lDifficolta = 0;
	m_sConclusioni = "";
	m_sIntegrazioni = "";
	m_sAppunti = "";
	m_sIndicazioni = "";
	m_sFarmacoTrial = "";
	m_sStudio = "";
	m_sTipoVisita = "";
	m_sPremedicazioni = "";
	m_lIdPremedicazione = 0;
	m_sStrumenti = "";
	m_sAccessori = "";
	m_sProgressivoAnno = "";
	m_sCodicePrenotazione = "";
	m_sValutazione = "";
	m_sComplicanzeOld = "";
	m_sGuarigione = "";
	m_sQuadro = "";
	m_sMetodo = "";
	m_sEstensione = "";
	m_sProcTerapeutiche = "";
	m_sProcDiagnostiche = "";
	m_sMstComplicanze1 = "";
	m_sMstComplicanze2 = "";
	m_sMstComplicanze3 = "";
	m_lProvenienza = -1;
	m_lInviante = 0;
	m_lCamera = 0;
	m_sInvMedico = "";
	m_lInvMedico = 0;
	m_lFumo = 0;
	m_lSigarette = 0;
	m_lCaffe = 0;
	m_lAlcool = 0;
	m_lSuperAlcolici = 0;
	m_sDenFarmaci = "";
	m_lAssunzione = 0;
	m_fPeso = 0.0f;
	m_fAltezza = 0.0f;
	m_fBMI = 0.0f;
	m_fMisuraA = 0.0f;
	m_fMisuraB = 0.0f;
	m_fMisuraC = 0.0f;
	m_fVolume = 0.0f;
	m_fBSA = 0.0f;
	m_sComplicanze1 = "";
	m_sComplicanze2 = "";
	m_sComplicanze3 = "";
	m_lIDVersione = 0;
	m_sNoteMonitoraggio = "";
	m_lInfermiereMonitoraggio = 0;
	m_lOspedale = 0;
	m_nCodiceRAO = 0;
	m_bConcordanza = TRUE;
	m_nCodiceRAOSpec = 0;
	m_iConsensoInformato = -1;
	m_sNoteConsensoInformato = "";
	m_iAllergie = -1;
	m_sDescrizioneAllergie = "";
	m_iPacemaker = -1;
	m_sDescrizionePacemaker = "";
	m_iAnticoagulanti = -1;
	m_sDescrizioneAnticoagulanti = "";
	m_iAntiaggreganti = -1;
	m_sDescrizioneAntiaggreganti = "";
	m_iBreathTestHP = 0;
	m_fBreathTestHPVal1 = -100.0f;
	m_fBreathTestHPVal2 = -100.0f;
	m_fBreathTestHPDiff = -100.0f;
	m_lIDSedeEsame = 0;
	m_sSalaEsame = "";
	m_lTipoDegenzaInterno = 0;
	m_lTipoDegenzaEsterno = 0;
	m_lFluoroscopiaMinuti= 0;
	m_lFluoroscopiaSecondi = 0;
	m_fFluoroscopiaDose = 0.0f;
	m_bFirmato = FALSE;
	m_bLocked = FALSE;
	m_lIdUtenteLock = 0;
	m_sDataOraLock = "";
	m_lIDSedePrevista = 0;		// gli ID delle sedi servono per gli interfacciamenti, NON RIMUOVERE!
	m_sSedePrevista = "";
	m_lIDSedeRaggiunta = 0;		// gli ID delle sedi servono per gli interfacciamenti, NON RIMUOVERE!
	m_sSedeRaggiunta = "";

	m_sAPDataInvio = "";
	m_sAPOperInvio = "";
	m_sAPDataAnnullamento = "";
	m_sAPOperAnnullamento = "";
	m_sAPDataRicezione = "";
	m_sAPDataConferma = "";
	m_sAPOperConferma = "";
	m_lAPStato = STATO_TEMP;
	m_sAPMotivazioneRifiuto = "";
	m_sAPDescrizioneRichiesta = "";
	m_sAPRispostaCodificata = "";
	m_sAPRispostaLibera = "";
	m_sAPRefertoPDF = "";
	m_sAPSuggerimenti1 = "";
	m_sAPSuggerimenti2 = "";
	m_sAPIDRichiesta = "";
	m_nAPSpedireRitirare = 0;
	m_bAPRefertato = FALSE;
	m_bAPVerificato = FALSE;
	m_nAPVerificatoMedico = 0;
	m_bAPSpeditoRitirato = FALSE;
	m_sAPDataVerificato = "";
	m_sAPDataSpeditoRitirato = "";
	m_sAPProvenienza = "";
	m_sAPConvenzione = "";
	m_sAPIndirizzo = "";
	m_nAPEseguitiPrelievi = -1;
	m_lAPIdRicetta = -1;
	m_sAPGroupNumber = "";

	m_lIDComplicanzeImmediate = -1;
	m_lIDComplicanzeTardive = -1;
	m_lIDPulizia = -1;
	m_lIDCausaNonCompleto = -1;
	m_bNecAssistenzaOspedaliera = FALSE;
	m_lIDTolleranza = -1;
	m_sPremedPosologia = "";
	m_lIDConclusioniScreening = -1;
	m_lIDConclusioniColon = -1;
	m_lIDAltreAnomalie = -1;
	m_bSuperLocked = FALSE;
	m_lIdUtenteSuperLock = 0;
	m_sDataOraSuperLock = "";
	m_sDataOraSuperLockPrimo = "";
	m_bInviatoScreening = FALSE;
	m_lIDDiagnosiFinale = -1;
	m_iSospeso = -1;
	m_lDataScadenzaSospensione = 0;
	m_sMotivoSospensione = "";
	m_sDataOraAcquisizione = "";
	m_sTempoConvalida = "";
	m_sTempoChiusura = "";
	m_lCustomDataOraInizioAcq = 0;
	m_lCustomDataOraFineAcq = 0;
	m_sPressione1 = "";
	m_sPressione2 = "";

	m_bInviatoInps = FALSE;
	m_lInpsDataInizio = 0;
	m_lInpsDataFine = 0;
	m_iInpsTipo = 0;
	m_sInpsNote = "";
	m_sInpsCognome = "";
	m_sInpsVia = "";
	m_sInpsCap = "";
	m_sInpsComune = "";
	m_sInpsProvincia = "";
	m_sInpsIdAnnullamento = "";
	m_sInpsNumeroProtocollo = "";

	m_bSissOscuramento10 = FALSE;
	m_bSissOscuramento20 = FALSE;
	m_bSissOscuramento30 = FALSE;
	m_bSissOscuramento40 = FALSE;
	m_bSissOscuramento50 = FALSE;
	m_bSissOscuramento50Bloccato = FALSE;
	m_bSissAutorizzazioneConsultaz = TRUE;
	m_sSissNoteReperibilita = "";

	m_sIdEpisodioRicovero = "";
	m_lDataRicoveroCustom = 0;

	m_lIDMalattiaCronica = 0;
	m_bRecordSenzaAccesso = FALSE;

	m_sPazientiCroniciScoreHB = "";
	m_sPazientiCroniciScoreS = "";

	m_lIDStudio = 0;
	m_lDataStudio = 0;

	m_lIDUtenteInserimentoEsame = 0;
	m_lDataRefertoIstologico = 0;
	m_bPresenzaLesioneSospettaCCR = FALSE;
	m_lNumeroTotalePolipi = 0;

	m_lBostonScoreDx = -1;
	m_lBostonScoreMid = -1;
	m_lBostonScoreSx = -1;
	m_lTempoRetrazione = 0;

	m_sEsenzioneDaIntegrazione = "";
	m_bPagamentoRicevuto = FALSE;

	m_bNonSbloccabile = FALSE;

	m_sRefertoTestoRtf = "";
	m_sRefertoTestoTxt = "";
	m_sRefertoTestoHtml = "";
	m_sRefertoDataOra = "";
	m_lRefertoRedattore = 0;
	m_bRefertoScaduto = FALSE;
	m_lRefertoStato = 0;

	m_bChiusuraBloccataDaIntegrazione = FALSE;

	m_lLivelloUrgenza = 0;
	m_lFrazioneEiezione = 0;
	m_lIdProvenienzaNew = 0;
	m_lStatoInvioCentraleRefertaz = StatoInvioCentraleRefertazione::crNonInviare;
	m_lStatoInvioControlloQualita = StatoInvioControlloQualita::cqNonInviare;
	m_lVersioneGridCL = 0;

	m_sQuesitoDiagnostico = "";
	m_sQuesitoDiagnosticoCodificato = "";

	m_lIDUltimaChecklistUsata = 0;

	m_sFCMassima = "";
	m_sFCSubmassima = "";
	m_lIDProtocolloUsato = 0;

	m_sRefertoConiugatoPrincipale = "";
	m_sRefertoConiugatoSecondario = "";
	m_bRefertoConiugatoAltraUO = FALSE;
	m_bRefertoConiugatoImportato = FALSE;

	m_sFleuryTrasferito = "";
	m_sFleuryEndpointRemoto = "";

	m_bEliminato = FALSE;
	m_lUO = 0;

	//
	m_lNumEsame = 0;
	m_bStessoDistretto = TRUE;

	//Luiz - 13/05/2019 - P3 - Atualiza nome/sobrenome Médico - Inclui Médicos solicitantes
	m_sInvMedico2 = "";
	m_lInvMedico2 = 0;
	m_sInvMedico3 = "";
	m_lInvMedico3 = 0;
	m_sInvMedico4 = "";
	m_lInvMedico4 = 0;
	//
	m_setEP.SetEmpty();
	m_setEM.SetEmpty();
	
	//Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
	m_setRI.SetEmpty();	
	//Gabriel - P3
	m_bHyperLocked = FALSE;
	m_lIdUtenteHyperLock = 0;
	m_sDataOraHyperLock = "";
	
	//Gabriel - TCP
	m_lStatoInvioAltraUnita = StatoInvioAltraUnita::auNonInviare; 
	m_sCodesameCorrelati = "";
	m_sRefertoTestoCorrelatiRtf = "";
	m_sRefertoTestoCorrelatiTxt = "";
	m_sRefertoTestoCorrelatiHtml = "";
}

void CEsamiSet::CopyFieldFrom(CEsamiSet* pSet, BOOL bEmpty)
{
	if (bEmpty)
		SetEmpty();
	
	if (m_nFields == 2)
	{
		if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lContatore))
			m_lContatore = pSet->m_lContatore;
		if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDVersione))
			m_lIDVersione = pSet->m_lIDVersione;

		return;
	}

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lContatore))
		m_lContatore	= pSet->m_lContatore;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sRicovero))
		m_sRicovero	= pSet->m_sRicovero.Left(50);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sCodEsame))
		m_sCodEsame	= pSet->m_sCodEsame.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDEsame))
		m_lIDEsame = pSet->m_lIDEsame;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lMedico))
		m_lMedico = pSet->m_lMedico;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sMedicoLibero))
		m_sMedicoLibero = pSet->m_sMedicoLibero;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lAssistente))
		m_lAssistente = pSet->m_lAssistente;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sAssistenteLibero))
		m_sAssistenteLibero = pSet->m_sAssistenteLibero;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sAnestesista))
		m_sAnestesista = pSet->m_sAnestesista;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lInfermiere1))
		m_lInfermiere1 = pSet->m_lInfermiere1;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lInfermiere2))
		m_lInfermiere2 = pSet->m_lInfermiere2;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lPaziente))
		m_lPaziente = pSet->m_lPaziente;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lData))
		m_lData = pSet->m_lData;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sAppunti))
		m_sAppunti = pSet->m_sAppunti;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sConclusioni))
		m_sConclusioni	= pSet->m_sConclusioni;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sIntegrazioni))
		m_sIntegrazioni	= pSet->m_sIntegrazioni;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTerapia))
		m_sTerapia	= pSet->m_sTerapia.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDataControllo))
		m_lDataControllo	= pSet->m_lDataControllo;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDurata))
		m_lDurata	= pSet->m_lDurata;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDifficolta))
		m_lDifficolta = pSet->m_lDifficolta;
	
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sEstensione))
		m_sEstensione= pSet->m_sEstensione.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sMetodo))
		m_sMetodo	= pSet->m_sMetodo.Left(3999);

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lProvenienza))
		m_lProvenienza= pSet->m_lProvenienza;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lInviante))
		m_lInviante	= pSet->m_lInviante;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lCamera))
		m_lCamera	= pSet->m_lCamera;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sInvMedico))
		m_sInvMedico	= pSet->m_sInvMedico.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lInvMedico))
		m_lInvMedico	= pSet->m_lInvMedico;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sIndicazioni))
		m_sIndicazioni = pSet->m_sIndicazioni.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sFarmacoTrial))
		m_sFarmacoTrial = pSet->m_sFarmacoTrial.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sStudio))
		m_sStudio = pSet->m_sStudio.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTipoVisita))
		m_sTipoVisita = pSet->m_sTipoVisita.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIdPremedicazione))
		m_lIdPremedicazione = pSet->m_lIdPremedicazione;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sPremedicazioni))
		m_sPremedicazioni = pSet->m_sPremedicazioni.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sStrumenti))
		m_sStrumenti = pSet->m_sStrumenti.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sAccessori))
		m_sAccessori = pSet->m_sAccessori.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sProgressivoAnno))
		m_sProgressivoAnno = pSet->m_sProgressivoAnno.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sCodicePrenotazione))
		m_sCodicePrenotazione = pSet->m_sCodicePrenotazione.Left(50);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sValutazione))
		m_sValutazione = pSet->m_sValutazione.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sComplicanzeOld))
		m_sComplicanzeOld = pSet->m_sComplicanzeOld.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sGuarigione))
		m_sGuarigione = pSet->m_sGuarigione.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sQuadro))
		m_sQuadro = pSet->m_sQuadro.Left(3999);

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sProcDiagnostiche))
		m_sProcDiagnostiche = pSet->m_sProcDiagnostiche;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sProcTerapeutiche))
		m_sProcTerapeutiche = pSet->m_sProcTerapeutiche;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sMstComplicanze1))
		m_sMstComplicanze1 = pSet->m_sMstComplicanze1;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sMstComplicanze2))
		m_sMstComplicanze2 = pSet->m_sMstComplicanze2;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sMstComplicanze3))
		m_sMstComplicanze3 = pSet->m_sMstComplicanze3;
	
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lFumo))
		m_lFumo = pSet->m_lFumo;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lSigarette))
		m_lSigarette = pSet->m_lSigarette;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lCaffe))
		m_lCaffe = pSet->m_lCaffe;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lAlcool))
		m_lAlcool = pSet->m_lAlcool;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lSuperAlcolici))
		m_lSuperAlcolici = pSet->m_lSuperAlcolici;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sDenFarmaci))
		m_sDenFarmaci = pSet->m_sDenFarmaci.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lAssunzione))
		m_lAssunzione = pSet->m_lAssunzione;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_fPeso))
		m_fPeso = pSet->m_fPeso;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_fAltezza))
		m_fAltezza = pSet->m_fAltezza;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_fBMI))
		m_fBMI = pSet->m_fBMI;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_fMisuraA))
		m_fMisuraA = pSet->m_fMisuraA;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_fMisuraB))
		m_fMisuraB = pSet->m_fMisuraB;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_fMisuraC))
		m_fMisuraC = pSet->m_fMisuraC;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_fVolume))
		m_fVolume = pSet->m_fVolume;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_fBSA))
		m_fBSA = pSet->m_fBSA;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sComplicanze1))
		m_sComplicanze1 = pSet->m_sComplicanze1;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sComplicanze2))
		m_sComplicanze2 = pSet->m_sComplicanze2;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sComplicanze3))
		m_sComplicanze3 = pSet->m_sComplicanze3;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDVersione))
		m_lIDVersione = pSet->m_lIDVersione;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sNoteMonitoraggio))
		m_sNoteMonitoraggio = pSet->m_sNoteMonitoraggio;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lInfermiereMonitoraggio))
		m_lInfermiereMonitoraggio = pSet->m_lInfermiereMonitoraggio;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lOspedale))
		m_lOspedale = pSet->m_lOspedale;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_nCodiceRAO))
		m_nCodiceRAO = pSet->m_nCodiceRAO;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bConcordanza))
		m_bConcordanza = pSet->m_bConcordanza;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_nCodiceRAOSpec))
		m_nCodiceRAOSpec = pSet->m_nCodiceRAOSpec;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_iConsensoInformato))
		m_iConsensoInformato = pSet->m_iConsensoInformato;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sNoteConsensoInformato))
		m_sNoteConsensoInformato = pSet->m_sNoteConsensoInformato;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_iAllergie))
		m_iAllergie = pSet->m_iAllergie;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sDescrizioneAllergie))
		m_sDescrizioneAllergie = pSet->m_sDescrizioneAllergie;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_iPacemaker))
		m_iPacemaker = pSet->m_iPacemaker;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sDescrizionePacemaker))
		m_sDescrizionePacemaker = pSet->m_sDescrizionePacemaker;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_iAnticoagulanti))
		m_iAnticoagulanti = pSet->m_iAnticoagulanti;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sDescrizioneAnticoagulanti))
		m_sDescrizioneAnticoagulanti = pSet->m_sDescrizioneAnticoagulanti;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_iAntiaggreganti))
		m_iAntiaggreganti = pSet->m_iAntiaggreganti;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sDescrizioneAntiaggreganti))
		m_sDescrizioneAntiaggreganti = pSet->m_sDescrizioneAntiaggreganti;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_iBreathTestHP))
		m_iBreathTestHP = pSet->m_iBreathTestHP;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_fBreathTestHPVal1))
		m_fBreathTestHPVal1 = pSet->m_fBreathTestHPVal1;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_fBreathTestHPVal2))
		m_fBreathTestHPVal2 = pSet->m_fBreathTestHPVal2;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_fBreathTestHPDiff))
		m_fBreathTestHPDiff = pSet->m_fBreathTestHPDiff;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDSedeEsame))
		m_lIDSedeEsame = pSet->m_lIDSedeEsame;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sSalaEsame))
		m_sSalaEsame = pSet->m_sSalaEsame;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lTipoDegenzaInterno))
		m_lTipoDegenzaInterno = pSet->m_lTipoDegenzaInterno;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lTipoDegenzaEsterno))
		m_lTipoDegenzaEsterno = pSet->m_lTipoDegenzaEsterno;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lFluoroscopiaMinuti))
		m_lFluoroscopiaMinuti = pSet->m_lFluoroscopiaMinuti;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lFluoroscopiaSecondi))
		m_lFluoroscopiaSecondi = pSet->m_lFluoroscopiaSecondi;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_fFluoroscopiaDose))
		m_fFluoroscopiaDose = pSet->m_fFluoroscopiaDose;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bFirmato)) // Davide - Firma digitale
		m_bFirmato = pSet->m_bFirmato;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bLocked))
		m_bLocked = pSet->m_bLocked;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIdUtenteLock))
		m_lIdUtenteLock = pSet->m_lIdUtenteLock;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sDataOraLock))
		m_sDataOraLock = pSet->m_sDataOraLock;
	//Gli ID delle sedi servono per gli interfacciamenti, NON RIMUOVERE!
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDSedePrevista))
		m_lIDSedePrevista = pSet->m_lIDSedePrevista;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sSedePrevista))
		m_sSedePrevista = pSet->m_sSedePrevista;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDSedeRaggiunta))
		m_lIDSedeRaggiunta = pSet->m_lIDSedeRaggiunta;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sSedeRaggiunta))
		m_sSedeRaggiunta = pSet->m_sSedeRaggiunta;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sAPDataInvio))
		m_sAPDataInvio = pSet->m_sAPDataInvio;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sAPOperInvio))
		m_sAPOperInvio = pSet->m_sAPOperInvio;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sAPDataAnnullamento))
		m_sAPDataAnnullamento = pSet->m_sAPDataAnnullamento;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sAPOperAnnullamento))
		m_sAPOperAnnullamento = pSet->m_sAPOperAnnullamento;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sAPDataRicezione))
		m_sAPDataRicezione = pSet->m_sAPDataRicezione;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sAPDataConferma))
		m_sAPDataConferma = pSet->m_sAPDataConferma;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sAPOperConferma))
		m_sAPOperConferma = pSet->m_sAPOperConferma;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lAPStato))
		m_lAPStato = pSet->m_lAPStato;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sAPMotivazioneRifiuto))
		m_sAPMotivazioneRifiuto = pSet->m_sAPMotivazioneRifiuto;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sAPDescrizioneRichiesta))
		m_sAPDescrizioneRichiesta = pSet->m_sAPDescrizioneRichiesta;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sAPRispostaCodificata))
		m_sAPRispostaCodificata = pSet->m_sAPRispostaCodificata;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sAPRispostaLibera))
		m_sAPRispostaLibera = pSet->m_sAPRispostaLibera;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sAPRefertoPDF))
		m_sAPRefertoPDF = pSet->m_sAPRefertoPDF;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sAPSuggerimenti1))
		m_sAPSuggerimenti1 = pSet->m_sAPSuggerimenti1;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sAPSuggerimenti2))
		m_sAPSuggerimenti2 = pSet->m_sAPSuggerimenti2;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sAPIDRichiesta))
		m_sAPIDRichiesta = pSet->m_sAPIDRichiesta;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_nAPSpedireRitirare))
		m_nAPSpedireRitirare = pSet->m_nAPSpedireRitirare;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bAPRefertato))
		m_bAPRefertato = pSet->m_bAPRefertato;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bAPVerificato))
		m_bAPVerificato = pSet->m_bAPVerificato;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_nAPVerificatoMedico))
		m_nAPVerificatoMedico = pSet->m_nAPVerificatoMedico;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bAPSpeditoRitirato))
		m_bAPSpeditoRitirato = pSet->m_bAPSpeditoRitirato;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sAPDataVerificato))
		m_sAPDataVerificato = pSet->m_sAPDataVerificato;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sAPDataSpeditoRitirato))
		m_sAPDataSpeditoRitirato = pSet->m_sAPDataSpeditoRitirato;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sAPProvenienza))
		m_sAPProvenienza = pSet->m_sAPProvenienza;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sAPConvenzione))
		m_sAPConvenzione = pSet->m_sAPConvenzione;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sAPIndirizzo))
		m_sAPIndirizzo = pSet->m_sAPIndirizzo;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_nAPEseguitiPrelievi))
		m_nAPEseguitiPrelievi = pSet->m_nAPEseguitiPrelievi;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lAPIdRicetta))
		m_lAPIdRicetta = pSet->m_lAPIdRicetta;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sAPGroupNumber))
		m_sAPGroupNumber = pSet->m_sAPGroupNumber;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDComplicanzeImmediate))
		m_lIDComplicanzeImmediate = pSet->m_lIDComplicanzeImmediate;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDComplicanzeTardive))
		m_lIDComplicanzeTardive = pSet->m_lIDComplicanzeTardive;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDPulizia))
		m_lIDPulizia = pSet->m_lIDPulizia;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDCausaNonCompleto))
		m_lIDCausaNonCompleto = pSet->m_lIDCausaNonCompleto;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bNecAssistenzaOspedaliera))
		m_bNecAssistenzaOspedaliera = pSet->m_bNecAssistenzaOspedaliera;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDTolleranza))
		m_lIDTolleranza = pSet->m_lIDTolleranza;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sPremedPosologia))
		m_sPremedPosologia = pSet->m_sPremedPosologia;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDConclusioniScreening))
		m_lIDConclusioniScreening = pSet->m_lIDConclusioniScreening;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDConclusioniColon))
		m_lIDConclusioniColon = pSet->m_lIDConclusioniColon;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDAltreAnomalie))
		m_lIDAltreAnomalie = pSet->m_lIDAltreAnomalie;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bSuperLocked))
		m_bSuperLocked = pSet->m_bSuperLocked;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIdUtenteSuperLock))
		m_lIdUtenteSuperLock = pSet->m_lIdUtenteSuperLock;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sDataOraSuperLock))
		m_sDataOraSuperLock = pSet->m_sDataOraSuperLock;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sDataOraSuperLockPrimo))
		m_sDataOraSuperLockPrimo = pSet->m_sDataOraSuperLockPrimo;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bInviatoScreening))
		m_bInviatoScreening = pSet->m_bInviatoScreening;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDDiagnosiFinale))
		m_lIDDiagnosiFinale = pSet->m_lIDDiagnosiFinale;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_iSospeso))
		m_iSospeso = pSet->m_iSospeso;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDataScadenzaSospensione))
		m_lDataScadenzaSospensione = pSet->m_lDataScadenzaSospensione;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sMotivoSospensione))
		m_sMotivoSospensione = pSet->m_sMotivoSospensione;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sDataOraAcquisizione))
		m_sDataOraAcquisizione = pSet->m_sDataOraAcquisizione;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTempoConvalida))
		m_sTempoConvalida = pSet->m_sTempoConvalida;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sTempoChiusura))
		m_sTempoChiusura = pSet->m_sTempoChiusura;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lCustomDataOraInizioAcq))
		m_lCustomDataOraInizioAcq = pSet->m_lCustomDataOraInizioAcq;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lCustomDataOraFineAcq))
		m_lCustomDataOraFineAcq = pSet->m_lCustomDataOraFineAcq;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sPressione1))
		m_sPressione1 = pSet->m_sPressione1;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sPressione2))
		m_sPressione2 = pSet->m_sPressione2;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bInviatoInps))
		m_bInviatoInps = pSet->m_bInviatoInps;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lInpsDataInizio))
		m_lInpsDataInizio = pSet->m_lInpsDataInizio;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lInpsDataFine))
		m_lInpsDataFine = pSet->m_lInpsDataFine;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_iInpsTipo))
		m_iInpsTipo = pSet->m_iInpsTipo;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sInpsNote))
		m_sInpsNote = pSet->m_sInpsNote;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sInpsCognome))
		m_sInpsCognome = pSet->m_sInpsCognome;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sInpsVia))
		m_sInpsVia = pSet->m_sInpsVia;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sInpsCap))
		m_sInpsCap = pSet->m_sInpsCap;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sInpsComune))
		m_sInpsComune = pSet->m_sInpsComune;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sInpsProvincia))
		m_sInpsProvincia = pSet->m_sInpsProvincia;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sInpsIdAnnullamento))
		m_sInpsIdAnnullamento = pSet->m_sInpsIdAnnullamento;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sInpsNumeroProtocollo))
		m_sInpsNumeroProtocollo = pSet->m_sInpsNumeroProtocollo;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bSissOscuramento10))
		m_bSissOscuramento10 = pSet->m_bSissOscuramento10;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bSissOscuramento20))
		m_bSissOscuramento20 = pSet->m_bSissOscuramento20;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bSissOscuramento30))
		m_bSissOscuramento30 = pSet->m_bSissOscuramento30;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bSissOscuramento40))
		m_bSissOscuramento40 = pSet->m_bSissOscuramento40;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bSissOscuramento50))
		m_bSissOscuramento50 = pSet->m_bSissOscuramento50;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bSissOscuramento50Bloccato))
		m_bSissOscuramento50Bloccato = pSet->m_bSissOscuramento50Bloccato;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bSissAutorizzazioneConsultaz))
		m_bSissAutorizzazioneConsultaz = pSet->m_bSissAutorizzazioneConsultaz;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sSissNoteReperibilita))
		m_sSissNoteReperibilita = pSet->m_sSissNoteReperibilita;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sIdEpisodioRicovero))
		m_sIdEpisodioRicovero = pSet->m_sIdEpisodioRicovero;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDataRicoveroCustom))
		m_lDataRicoveroCustom = pSet->m_lDataRicoveroCustom;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDMalattiaCronica))
		m_lIDMalattiaCronica = pSet->m_lIDMalattiaCronica;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bRecordSenzaAccesso))
		m_bRecordSenzaAccesso = pSet->m_bRecordSenzaAccesso;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sPazientiCroniciScoreHB))
		m_sPazientiCroniciScoreHB = pSet->m_sPazientiCroniciScoreHB;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sPazientiCroniciScoreS))
		m_sPazientiCroniciScoreS = pSet->m_sPazientiCroniciScoreS;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDStudio))
		m_lIDStudio = pSet->m_lIDStudio;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDataStudio))
		m_lDataStudio = pSet->m_lDataStudio;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDUtenteInserimentoEsame))
		m_lIDUtenteInserimentoEsame = pSet->m_lIDUtenteInserimentoEsame;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lDataRefertoIstologico))
		m_lDataRefertoIstologico = pSet->m_lDataRefertoIstologico;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bPresenzaLesioneSospettaCCR))
		m_bPresenzaLesioneSospettaCCR = pSet->m_bPresenzaLesioneSospettaCCR;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lNumeroTotalePolipi))
		m_lNumeroTotalePolipi = pSet->m_lNumeroTotalePolipi;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lBostonScoreDx))
		m_lBostonScoreDx = pSet->m_lBostonScoreDx;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lBostonScoreMid))
		m_lBostonScoreMid = pSet->m_lBostonScoreMid;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lBostonScoreSx))
		m_lBostonScoreSx = pSet->m_lBostonScoreSx;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lTempoRetrazione))
		m_lTempoRetrazione = pSet->m_lTempoRetrazione;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sEsenzioneDaIntegrazione))
		m_sEsenzioneDaIntegrazione = pSet->m_sEsenzioneDaIntegrazione;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bPagamentoRicevuto))
		m_bPagamentoRicevuto = pSet->m_bPagamentoRicevuto;
	
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bNonSbloccabile))
		m_bNonSbloccabile = pSet->m_bNonSbloccabile;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sRefertoTestoRtf))
		m_sRefertoTestoRtf = pSet->m_sRefertoTestoRtf;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sRefertoTestoTxt))
		m_sRefertoTestoTxt = pSet->m_sRefertoTestoTxt;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sRefertoTestoHtml))
		m_sRefertoTestoHtml = pSet->m_sRefertoTestoHtml;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sRefertoDataOra))
		m_sRefertoDataOra = pSet->m_sRefertoDataOra;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lRefertoRedattore))
		m_lRefertoRedattore = pSet->m_lRefertoRedattore;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bRefertoScaduto))
		m_bRefertoScaduto = pSet->m_bRefertoScaduto;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lRefertoStato))
		m_lRefertoStato = pSet->m_lRefertoStato;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bChiusuraBloccataDaIntegrazione))
		m_bChiusuraBloccataDaIntegrazione = pSet->m_bChiusuraBloccataDaIntegrazione;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lLivelloUrgenza))
		m_lLivelloUrgenza = pSet->m_lLivelloUrgenza;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lFrazioneEiezione))
		m_lFrazioneEiezione = pSet->m_lFrazioneEiezione;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIdProvenienzaNew))
		m_lIdProvenienzaNew = pSet->m_lIdProvenienzaNew;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lStatoInvioCentraleRefertaz))
		m_lStatoInvioCentraleRefertaz = pSet->m_lStatoInvioCentraleRefertaz;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lStatoInvioControlloQualita))
		m_lStatoInvioControlloQualita = pSet->m_lStatoInvioControlloQualita;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lVersioneGridCL))
		m_lVersioneGridCL = pSet->m_lVersioneGridCL;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sQuesitoDiagnostico))
		m_sQuesitoDiagnostico = pSet->m_sQuesitoDiagnostico;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sQuesitoDiagnosticoCodificato))
		m_sQuesitoDiagnosticoCodificato = pSet->m_sQuesitoDiagnosticoCodificato;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDUltimaChecklistUsata))
		m_lIDUltimaChecklistUsata = pSet->m_lIDUltimaChecklistUsata;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sFCMassima))
		m_sFCMassima = pSet->m_sFCMassima;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sFCSubmassima))
		m_sFCSubmassima = pSet->m_sFCSubmassima;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIDProtocolloUsato))
		m_lIDProtocolloUsato = pSet->m_lIDProtocolloUsato;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sRefertoConiugatoPrincipale))
		m_sRefertoConiugatoPrincipale = pSet->m_sRefertoConiugatoPrincipale;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sRefertoConiugatoSecondario))
		m_sRefertoConiugatoSecondario = pSet->m_sRefertoConiugatoSecondario;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bRefertoConiugatoAltraUO))
		m_bRefertoConiugatoAltraUO = pSet->m_bRefertoConiugatoAltraUO;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bRefertoConiugatoImportato))
		m_bRefertoConiugatoImportato = pSet->m_bRefertoConiugatoImportato;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sFleuryTrasferito))
		m_sFleuryTrasferito = pSet->m_sFleuryTrasferito;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sFleuryEndpointRemoto))
		m_sFleuryEndpointRemoto = pSet->m_sFleuryEndpointRemoto;

	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bEliminato))
		m_bEliminato = pSet->m_bEliminato;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lUO))
		m_lUO = pSet->m_lUO;

	//Luiz - 13/05/2019 - P3 - Atualiza nome/sobrenome Médico - Inclui Médicos solicitantes
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sInvMedico2))
	m_sInvMedico2 = pSet->m_sInvMedico2.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lInvMedico2))
	m_lInvMedico2 = pSet->m_lInvMedico2;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sInvMedico3))
	m_sInvMedico3 = pSet->m_sInvMedico3.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lInvMedico3))
	m_lInvMedico3 = pSet->m_lInvMedico3;
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sInvMedico4))
	m_sInvMedico4 = pSet->m_sInvMedico4.Left(3999);
	if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lInvMedico4))
	m_lInvMedico4 = pSet->m_lInvMedico4; 

	//Gabriel - P3
	if (m_bColumnsP3)
	{
		if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_bHyperLocked))
			m_bHyperLocked = pSet->m_bHyperLocked;
		if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lIdUtenteHyperLock))
			m_lIdUtenteHyperLock = pSet->m_lIdUtenteHyperLock;
		if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sDataOraHyperLock))
			m_sDataOraHyperLock = pSet->m_sDataOraHyperLock;
	}

	//Gabriel - TCP
	if (m_bColumnsTCP)
	{
		if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_lStatoInvioAltraUnita))
			m_lStatoInvioAltraUnita = pSet->m_lStatoInvioAltraUnita;
		if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sCodesameCorrelati))
			m_sCodesameCorrelati = pSet->m_sCodesameCorrelati;
		if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sRefertoTestoCorrelatiRtf))
			m_sRefertoTestoCorrelatiRtf = pSet->m_sRefertoTestoCorrelatiRtf;
		if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sRefertoTestoCorrelatiTxt))
			m_sRefertoTestoCorrelatiTxt = pSet->m_sRefertoTestoCorrelatiTxt;
		if (!pSet->IsOpen() || !pSet->IsFieldNull(&pSet->m_sRefertoTestoCorrelatiHtml))
			m_sRefertoTestoCorrelatiHtml = pSet->m_sRefertoTestoCorrelatiHtml;
	}
	
	if (bEmpty && IsOpen())
	{
		SetFieldNull(NULL, FALSE);
		SetFieldDirty(NULL, TRUE);
	}

	m_setEP.CopyFieldFrom(&pSet->m_setEP, bEmpty);
	m_setEM.CopyFieldFrom(&pSet->m_setEM, bEmpty);		
	m_setRI.CopyFieldFrom(&pSet->m_setRI, bEmpty); //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
}

void CEsamiSet::SetFieldNull(void* pv, BOOL bNull)
{
	CBaseSet::SetFieldNull(pv, bNull);

	if (pv == NULL)
	{
		m_setEP.SetFieldNull(NULL, bNull);
		m_setEM.SetFieldNull(NULL, bNull);
		m_setRI.SetFieldNull(NULL, bNull); //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
	}
}

BOOL CEsamiSet::AddNewRecordset(const CString &strCommento)
{
	BOOL bReturn = CBaseSet::AddNewRecordset(strCommento);

	if (bReturn)
	{
		bReturn = m_setEP.AddNewRecordset(strCommento);
		if (!bReturn)
			NoEditRecordset(strCommento);
	}

	if (bReturn)
	{
		bReturn = m_setEM.AddNewRecordset(strCommento);
		if (!bReturn)
			NoEditRecordset(strCommento);
	}

	return bReturn;
}

BOOL CEsamiSet::CloseRecordset(const CString &strCommento)
{
	BOOL bReturn = CBaseSet::CloseRecordset(strCommento);
	m_setEP.CloseRecordset(strCommento);
	m_setEM.CloseRecordset(strCommento);
	m_setRI.CloseRecordset(strCommento); //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture

	return bReturn;
}

BOOL CEsamiSet::EditRecordset(const CString &strCommento)
{
	BOOL bReturn = CBaseSet::EditRecordset(strCommento);

	if (bReturn)
	{
		bReturn = m_setEP.EditRecordset(strCommento);
		if (!bReturn)
			NoEditRecordset(strCommento);
	}

	if (bReturn)
	{
		bReturn = m_setEM.EditRecordset(strCommento);
		if (!bReturn)
			NoEditRecordset(strCommento);
	}

	if (bReturn) //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
	{
		bReturn = m_setRI.EditRecordset(strCommento);
		if (!bReturn)
			NoEditRecordset(strCommento);
	}

	return bReturn;
}

BOOL CEsamiSet::NoEditRecordset(const CString &strCommento)
{
	BOOL bReturn = CBaseSet::NoEditRecordset(strCommento);
	m_setEP.NoEditRecordset(strCommento);
	m_setEM.NoEditRecordset(strCommento);
	m_setRI.NoEditRecordset(strCommento);  //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture

	return bReturn;
}

BOOL CEsamiSet::OpenRecordset(const CString &strCommento)
{
	BOOL bReturn = CBaseSet::OpenRecordset(strCommento);

	if (bReturn)
	{
		CString strTemp;
		strTemp.Format("IDEsame=%li", m_lContatore);

		m_setEP.SetOpenFilter(strTemp);
		bReturn = m_setEP.OpenRecordset(strCommento);
		if (!bReturn)
		{
			CloseRecordset(strCommento);
		}
		else
		{
			if (!IsEOF() && m_setEP.IsEOF())
			{
				bReturn = FALSE;
				if (m_setEP.AddNewRecordset(strCommento))
				{
					m_setEP.m_lIDEsame = m_lContatore;
					bReturn = m_setEP.UpdateRecordset(strCommento);
				}

				if (!bReturn)
					CloseRecordset(strCommento);
			}
		}

		m_setEM.SetOpenFilter(strTemp);
		bReturn = m_setEM.OpenRecordset(strCommento);
		if (!bReturn)
		{
			CloseRecordset(strCommento);
		}
		else
		{
			if (!IsEOF() && m_setEM.IsEOF())
			{
				bReturn = FALSE;
				if (m_setEM.AddNewRecordset(strCommento))
				{
					m_setEM.m_lIDESAME = m_lContatore;
					bReturn = m_setEM.UpdateRecordset(strCommento);
				}

				if (!bReturn)
					CloseRecordset(strCommento);
			}
		}

		//Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
		m_setRI.SetOpenFilter(strTemp);
		bReturn = m_setRI.OpenRecordset(strCommento);
		if (!bReturn)
		{
			CloseRecordset(strCommento);
		}
		else
		{
			if (!IsEOF() && m_setRI.IsEOF())
			{
				bReturn = FALSE;
				if (m_setRI.AddNewRecordset(strCommento))
				{
					m_setRI.m_lIDEsame = m_lContatore;
					bReturn = m_setRI.UpdateRecordset(strCommento);
				}

				if (!bReturn)
					CloseRecordset(strCommento);
			}
		}
	}

	return bReturn;
}

BOOL CEsamiSet::RecordsetReOpen(BOOL &bError, const CString &strFilter, const CString &strSort, const CString &strCommento)
{
	BOOL bReturn = CBaseSet::RecordsetReOpen(bError, strFilter, strSort, strCommento);

	if (bReturn)
	{
		CString strTemp;
		strTemp.Format("IDEsame=%li", m_lContatore);

		m_setEP.SetOpenFilter(strTemp);
		bReturn = m_setEP.OpenRecordset(strCommento);
		if (bReturn)
		{
			if (!IsEOF() && m_setEP.IsEOF())
			{
				bReturn = FALSE;
				if (m_setEP.AddNewRecordset(strCommento))
				{
					m_setEP.m_lIDEsame = m_lContatore;
					bReturn = m_setEP.UpdateRecordset(strCommento);
				}
			}
		}

		m_setEM.SetOpenFilter(strTemp);
		bReturn = m_setEM.OpenRecordset(strCommento);
		if (bReturn)
		{
			if (!IsEOF() && m_setEM.IsEOF())
			{
				bReturn = FALSE;
				if (m_setEM.AddNewRecordset(strCommento))
				{
					m_setEM.m_lIDESAME = m_lContatore;
					bReturn = m_setEM.UpdateRecordset(strCommento);
				}
			}
		}

		//Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
		m_setRI.SetOpenFilter(strTemp);
		bReturn = m_setRI.OpenRecordset(strCommento);
		if (bReturn)
		{
			if (!IsEOF() && m_setRI.IsEOF())
			{
				bReturn = FALSE;
				if (m_setRI.AddNewRecordset(strCommento))
				{
					m_setRI.m_lIDEsame = m_lContatore;
					bReturn = m_setRI.UpdateRecordset(strCommento);
				}
			}
		}
	}
	else
	{
		m_setEP.SetEmpty();
		m_setEM.SetEmpty();
		m_setRI.SetEmpty(); //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
	}

	return bReturn;
}

BOOL CEsamiSet::RefreshRecordset()
{
	BOOL bReturn = CBaseSet::RefreshRecordset();

	if (bReturn)
		bReturn = m_setEP.RefreshRecordset();
	if (bReturn)
		bReturn = m_setEM.RefreshRecordset();
	if (bReturn)
		bReturn = m_setRI.RefreshRecordset(); //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture

	return bReturn;
}

BOOL CEsamiSet::GotoExam(long lContatore)
{
	CString strQuery;
	strQuery.Format("SELECT CONTATORE FROM EESAMI WHERE (%s) AND (%s) ORDER BY %s",
		            GetOpenFilter(),
					GetBaseFilter(),
					GetSortRecord());

	CRecordset set(&theApp.m_dbEndox);
	long lPosition = 0;

	try
	{
		set.Open(CRecordset::snapshot, strQuery, CRecordset::readOnly);
		while (!set.IsEOF())
		{
			CString strContatore;
			set.GetFieldValue("CONTATORE", strContatore);
			
			if (atol(strContatore) == lContatore)
				break;

			lPosition++;
			set.MoveNext();
		}
	}
	catch (CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
		return FALSE;
	}
		
	if (set.IsOpen())
		set.Close();

	m_lNumEsame = lPosition + 1;
	SetAbsolutePosition(m_lNumEsame);

	if (m_lContatore != lContatore)
		return FALSE;

	//

	CString strTemp;
	strTemp.Format("IDEsame=%li", m_lContatore);

	BOOL bContinue;

	m_setEP.SetOpenFilter(strTemp);
	if (m_setEP.IsOpen())
		bContinue = m_setEP.RequeryRecordset();
	else
		bContinue = m_setEP.OpenRecordset("CEsamiSet::GotoExam");
	if (bContinue)
	{
		if (!IsEOF() && m_setEP.IsEOF())
		{
			if (m_setEP.AddNewRecordset("CEsamiSet::GotoExam"))
			{
				m_setEP.m_lIDEsame = m_lContatore;
				m_setEP.UpdateRecordset("CEsamiSet::GotoExam");
			}
		}
	}

	m_setEM.SetOpenFilter(strTemp);
	if (m_setEM.IsOpen())
		bContinue = m_setEM.RequeryRecordset();
	else
		bContinue = m_setEM.OpenRecordset("CEsamiSet::GotoExam");
	if (bContinue)
	{
		if (!IsEOF() && m_setEM.IsEOF())
		{
			if (m_setEM.AddNewRecordset("CEsamiSet::GotoExam"))
			{
				m_setEM.m_lIDESAME = m_lContatore;
				m_setEM.UpdateRecordset("CEsamiSet::GotoExam");
			}
		}
	}

	//Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
	m_setRI.SetOpenFilter(strTemp);
	if (m_setRI.IsOpen())
		bContinue = m_setRI.RequeryRecordset();
	else
		bContinue = m_setRI.OpenRecordset("CEsamiSet::GotoExam");
	if (bContinue)
	{
		if (!IsEOF() && m_setRI.IsEOF())
		{
			if (m_setRI.AddNewRecordset("CEsamiSet::GotoExam"))
			{
				m_setRI.m_lIDEsame = m_lContatore;
				m_setRI.UpdateRecordset("CEsamiSet::GotoExam");
			}
		}
	}

	return TRUE;
}

void CEsamiSet::MoveFirst()
{
	VERIFY(m_nEditMode == 0);
	CBaseSet::MoveFirst();

	if (m_setEP.GetEditMode() == 0)
	{
		CString strTemp;
		strTemp.Format("IDEsame=%li", m_lContatore);

		BOOL bContinue;

		m_setEP.SetOpenFilter(strTemp);
		if (m_setEP.IsOpen())
			bContinue = m_setEP.RequeryRecordset();
		else
			bContinue = m_setEP.OpenRecordset("CEsamiSet::GotoExam");
		if (bContinue)
		{
			if (!IsEOF() && m_setEP.IsEOF())
			{
				if (m_setEP.AddNewRecordset("CEsamiSet::MoveFirst"))
				{
					m_setEP.m_lIDEsame = m_lContatore;
					m_setEP.UpdateRecordset("CEsamiSet::MoveFirst");
					m_setEP.NoEditRecordset("CEsamiSet::MoveFirst");
				}
			}
		}
	}

	if (m_setEM.GetEditMode() == 0)
	{
		CString strTemp;
		strTemp.Format("IDEsame=%li", m_lContatore);

		BOOL bContinue;

		m_setEM.SetOpenFilter(strTemp);
		if (m_setEM.IsOpen())
			bContinue = m_setEM.RequeryRecordset();
		else
			bContinue = m_setEM.OpenRecordset("CEsamiSet::GotoExam");
		if (bContinue)
		{
			if (!IsEOF() && m_setEM.IsEOF())
			{
				if (m_setEM.AddNewRecordset("CEsamiSet::MoveFirst"))
				{
					m_setEM.m_lIDESAME = m_lContatore;
					m_setEM.UpdateRecordset("CEsamiSet::MoveFirst");
					m_setEM.NoEditRecordset("CEsamiSet::MoveFirst");
				}
			}
		}
	}

	//Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
	if (m_setRI.GetEditMode() == 0)
	{
		CString strTemp;
		strTemp.Format("IDEsame=%li", m_lContatore);

		BOOL bContinue;

		m_setRI.SetOpenFilter(strTemp);
		if (m_setRI.IsOpen())
			bContinue = m_setRI.RequeryRecordset();
		else
			bContinue = m_setRI.OpenRecordset("CEsamiSet::GotoExam");
		if (bContinue)
		{
			if (!IsEOF() && m_setRI.IsEOF())
			{
				if (m_setRI.AddNewRecordset("CEsamiSet::MoveFirst"))
				{
					m_setRI.m_lIDEsame = m_lContatore;
					m_setRI.UpdateRecordset("CEsamiSet::MoveFirst");
					m_setRI.NoEditRecordset("CEsamiSet::MoveFirst");
				}
			}
		}
	}
}

void CEsamiSet::MovePrev()
{
	VERIFY(m_nEditMode == 0);
	CBaseSet::MovePrev();

	if (m_setEP.GetEditMode() == 0)
	{
		CString strTemp;
		strTemp.Format("IDEsame=%li", m_lContatore);

		m_setEP.SetOpenFilter(strTemp);

		BOOL bContinue;
		if (m_setEP.IsOpen())
			bContinue = m_setEP.RequeryRecordset();
		else
			bContinue = m_setEP.OpenRecordset("CEsamiSet::GotoExam");

		if (bContinue)
		{
			if (!IsEOF() && m_setEP.IsEOF())
			{
				if (m_setEP.AddNewRecordset("CEsamiSet::MovePrev"))
				{
					m_setEP.m_lIDEsame = m_lContatore;
					m_setEP.UpdateRecordset("CEsamiSet::MovePrev");
					m_setEP.NoEditRecordset("CEsamiSet::MovePrev");
				}
			}
		}
	}

	if (m_setEM.GetEditMode() == 0)
	{
		CString strTemp;
		strTemp.Format("IDEsame=%li", m_lContatore);

		m_setEM.SetOpenFilter(strTemp);

		BOOL bContinue;
		if (m_setEM.IsOpen())
			bContinue = m_setEM.RequeryRecordset();
		else
			bContinue = m_setEM.OpenRecordset("CEsamiSet::GotoExam");

		if (bContinue)
		{
			if (!IsEOF() && m_setEM.IsEOF())
			{
				if (m_setEM.AddNewRecordset("CEsamiSet::MovePrev"))
				{
					m_setEM.m_lIDESAME = m_lContatore;
					m_setEM.UpdateRecordset("CEsamiSet::MovePrev");
					m_setEM.NoEditRecordset("CEsamiSet::MovePrev");
				}
			}
		}
	}
	
	//Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
	if (m_setRI.GetEditMode() == 0)
	{
		CString strTemp;
		strTemp.Format("IDEsame=%li", m_lContatore);

		m_setRI.SetOpenFilter(strTemp);

		BOOL bContinue;
		if (m_setRI.IsOpen())
			bContinue = m_setRI.RequeryRecordset();
		else
			bContinue = m_setRI.OpenRecordset("CEsamiSet::GotoExam");

		if (bContinue)
		{
			if (!IsEOF() && m_setEM.IsEOF())
			{
				if (m_setRI.AddNewRecordset("CEsamiSet::MovePrev"))
				{
					m_setRI.m_lIDEsame = m_lContatore;
					m_setRI.UpdateRecordset("CEsamiSet::MovePrev");
					m_setRI.NoEditRecordset("CEsamiSet::MovePrev");
				}
			}
		}
	}
}

void CEsamiSet::MoveNext()
{
	VERIFY(m_nEditMode == 0);
	CBaseSet::MoveNext();

	if (m_setEP.GetEditMode() == 0)
	{
		CString strTemp;
		strTemp.Format("IDEsame=%li", m_lContatore);

		m_setEP.SetOpenFilter(strTemp);

		BOOL bContinue;
		if (m_setEP.IsOpen())
			bContinue = m_setEP.RequeryRecordset();
		else
			bContinue = m_setEP.OpenRecordset("CEsamiSet::GotoExam");

		if (bContinue)
		{
			if (!IsEOF() && m_setEP.IsEOF())
			{
				if (m_setEP.AddNewRecordset("CEsamiSet::MoveNext"))
				{
					m_setEP.m_lIDEsame = m_lContatore;
					m_setEP.UpdateRecordset("CEsamiSet::MoveNext");
					m_setEP.NoEditRecordset("CEsamiSet::MoveNext");
				}
			}
		}
	}

	if (m_setEM.GetEditMode() == 0)
	{
		CString strTemp;
		strTemp.Format("IDEsame=%li", m_lContatore);

		m_setEM.SetOpenFilter(strTemp);

		BOOL bContinue;
		if (m_setEM.IsOpen())
			bContinue = m_setEM.RequeryRecordset();
		else
			bContinue = m_setEM.OpenRecordset("CEsamiSet::GotoExam");

		if (bContinue)
		{
			if (!IsEOF() && m_setEM.IsEOF())
			{
				if (m_setEM.AddNewRecordset("CEsamiSet::MoveNext"))
				{
					m_setEM.m_lIDESAME = m_lContatore;
					m_setEM.UpdateRecordset("CEsamiSet::MoveNext");
					m_setEM.NoEditRecordset("CEsamiSet::MoveNext");
				}
			}
		}
	}
	
	//Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
	if (m_setRI.GetEditMode() == 0)
	{
		CString strTemp;
		strTemp.Format("IDEsame=%li", m_lContatore);

		m_setRI.SetOpenFilter(strTemp);

		BOOL bContinue;
		if (m_setRI.IsOpen())
			bContinue = m_setRI.RequeryRecordset();
		else
			bContinue = m_setRI.OpenRecordset("CEsamiSet::GotoExam");

		if (bContinue)
		{
			if (!IsEOF() && m_setRI.IsEOF())
			{
				if (m_setRI.AddNewRecordset("CEsamiSet::MoveNext"))
				{
					m_setRI.m_lIDEsame = m_lContatore;
					m_setRI.UpdateRecordset("CEsamiSet::MoveNext");
					m_setRI.NoEditRecordset("CEsamiSet::MoveNext");
				}
			}
		}
	}
}

void CEsamiSet::MoveLast()
{
	CBaseSet::MoveLast();

	if (m_setEP.GetEditMode() == 0)
	{
		CString strTemp;
		strTemp.Format("IDEsame=%li", m_lContatore);

		m_setEP.SetOpenFilter(strTemp);

		BOOL bContinue;
		if (m_setEP.IsOpen())
			bContinue = m_setEP.RequeryRecordset();
		else
			bContinue = m_setEP.OpenRecordset("CEsamiSet::GotoExam");

		if (bContinue)
		{
			if (!IsEOF() && m_setEP.IsEOF())
			{
				if (m_setEP.AddNewRecordset("CEsamiSet::MoveLast"))
				{
					m_setEP.m_lIDEsame = m_lContatore;
					m_setEP.UpdateRecordset("CEsamiSet::MoveLast");
					m_setEP.NoEditRecordset("CEsamiSet::MoveLast");
				}
			}
		}
	}

	if (m_setEM.GetEditMode() == 0)
	{
		CString strTemp;
		strTemp.Format("IDEsame=%li", m_lContatore);

		m_setEM.SetOpenFilter(strTemp);

		BOOL bContinue;
		if (m_setEM.IsOpen())
			bContinue = m_setEM.RequeryRecordset();
		else
			bContinue = m_setEM.OpenRecordset("CEsamiSet::GotoExam");

		if (bContinue)
		{
			if (!IsEOF() && m_setEM.IsEOF())
			{
				if (m_setEM.AddNewRecordset("CEsamiSet::MoveLast"))
				{
					m_setEM.m_lIDESAME = m_lContatore;
					m_setEM.UpdateRecordset("CEsamiSet::MoveLast");
					m_setEM.NoEditRecordset("CEsamiSet::MoveLast");
				}
			}
		}
	}
	
	//Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
	if (m_setRI.GetEditMode() == 0)
	{
		CString strTemp;
		strTemp.Format("IDEsame=%li", m_lContatore);

		m_setRI.SetOpenFilter(strTemp);

		BOOL bContinue;
		if (m_setRI.IsOpen())
			bContinue = m_setRI.RequeryRecordset();
		else
			bContinue = m_setRI.OpenRecordset("CEsamiSet::GotoExam");

		if (bContinue)
		{
			if (!IsEOF() && m_setRI.IsEOF())
			{
				if (m_setRI.AddNewRecordset("CEsamiSet::MoveLast"))
				{
					m_setRI.m_lIDEsame = m_lContatore;
					m_setRI.UpdateRecordset("CEsamiSet::MoveLast");
					m_setRI.NoEditRecordset("CEsamiSet::MoveLast");
				}
			}
		}
	}
}

long CEsamiSet::GetLastPatientExam(long lIDPaziente)
{
	long lReturn = 0;

	CString sFilter;
	sFilter.Format("Paziente=%li", lIDPaziente);

	SetBaseFilter("(RecordSenzaAccesso=0 OR RecordSenzaAccesso=1)");
	SetOpenFilter(sFilter);
	SetSortRecord("Data, Contatore");

	if (OpenRecordset("CEsamiSet::GetLastPatientExam"))
	{
		if (!IsEOF())
		{
			MoveLast();
			lReturn = m_lContatore;
		}

		CloseRecordset("CEsamiSet::GetLastPatientExam");
	}

	return lReturn;
}

long CEsamiSet::GetPaziente(long lIDEsame)
{
	long lReturn = 0;

	CString sFilter;
	sFilter.Format("Contatore=%li", lIDEsame);

	SetOpenFilter(sFilter);
	if (OpenRecordset("CEsamiSet::GetPaziente"))
	{
		if (!IsEOF())
			lReturn = m_lPaziente;

		CloseRecordset("CEsamiSet::GetPaziente");
	}

	return lReturn;
}

long CEsamiSet::GetUO(long lIDEsame)
{
	long lReturn = 0;

	CString sFilter;
	sFilter.Format("Contatore=%li", lIDEsame);

	SetBaseFilter("(UO=0 OR UO>0)");
	SetOpenFilter(sFilter);
	if (OpenRecordset("CEsamiSet::GetUO"))
	{
		if (!IsEOF())
			lReturn = m_lUO;

		CloseRecordset("CEsamiSet::GetUO");
	}

	return lReturn;
}

int CEsamiSet::GetEditMode()
{
	return m_nEditMode;
}

CBaseSet* CEsamiSet::CreateNew()
{
	return (CBaseSet*)new CEsamiSet;
}

void CEsamiSet::CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll)
{
	CEsamiSet* pEsamiSet = (CEsamiSet*)pOriginalSet;

	if (m_nFields == 2 || pOriginalSet->m_nFields == 2)
	{
		if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lIDVersione) || bCopyAll)
			m_lIDVersione = pEsamiSet->m_lIDVersione;
		return;
	}

	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sRicovero) || bCopyAll)
		m_sRicovero = pEsamiSet->m_sRicovero;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sCodEsame) || bCopyAll)
		m_sCodEsame = pEsamiSet->m_sCodEsame;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lPaziente) || bCopyAll)
		m_lPaziente = pEsamiSet->m_lPaziente;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lIDEsame) || bCopyAll)
		m_lIDEsame = pEsamiSet->m_lIDEsame;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lData) || bCopyAll)
		m_lData = pEsamiSet->m_lData;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lMedico) || bCopyAll)
		m_lMedico = pEsamiSet->m_lMedico;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sMedicoLibero) || bCopyAll)
		m_sMedicoLibero = pEsamiSet->m_sMedicoLibero;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lAssistente) || bCopyAll)
		m_lAssistente = pEsamiSet->m_lAssistente;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sAssistenteLibero) || bCopyAll)
		m_sAssistenteLibero = pEsamiSet->m_sAssistenteLibero;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sAnestesista) || bCopyAll)
		m_sAnestesista = pEsamiSet->m_sAnestesista;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lInfermiere1) || bCopyAll)
		m_lInfermiere1 = pEsamiSet->m_lInfermiere1;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lInfermiere2) || bCopyAll)
		m_lInfermiere2 = pEsamiSet->m_lInfermiere2;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sTerapia) || bCopyAll)
		m_sTerapia = pEsamiSet->m_sTerapia;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lDataControllo) || bCopyAll)
		m_lDataControllo = pEsamiSet->m_lDataControllo;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lDurata) || bCopyAll)
		m_lDurata = pEsamiSet->m_lDurata;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lDifficolta) || bCopyAll)
		m_lDifficolta = pEsamiSet->m_lDifficolta;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sConclusioni) || bCopyAll)
		m_sConclusioni = pEsamiSet->m_sConclusioni;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sIntegrazioni) || bCopyAll)
		m_sIntegrazioni = pEsamiSet->m_sIntegrazioni;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sAppunti) || bCopyAll)
		m_sAppunti = pEsamiSet->m_sAppunti;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sIndicazioni) || bCopyAll)
		m_sIndicazioni = pEsamiSet->m_sIndicazioni;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sFarmacoTrial) || bCopyAll)
		m_sFarmacoTrial = pEsamiSet->m_sFarmacoTrial;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sStudio) || bCopyAll)
		m_sStudio = pEsamiSet->m_sStudio;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sTipoVisita) || bCopyAll)
		m_sTipoVisita = pEsamiSet->m_sTipoVisita;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lIdPremedicazione) || bCopyAll)
		m_lIdPremedicazione = pEsamiSet->m_lIdPremedicazione;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sPremedicazioni) || bCopyAll)
		m_sPremedicazioni = pEsamiSet->m_sPremedicazioni;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sStrumenti) || bCopyAll)
		m_sStrumenti = pEsamiSet->m_sStrumenti;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sAccessori) || bCopyAll)
		m_sAccessori = pEsamiSet->m_sAccessori;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sProgressivoAnno) || bCopyAll)
		m_sProgressivoAnno = pEsamiSet->m_sProgressivoAnno;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sCodicePrenotazione) || bCopyAll)
		m_sCodicePrenotazione = pEsamiSet->m_sCodicePrenotazione;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sValutazione) || bCopyAll)
		m_sValutazione = pEsamiSet->m_sValutazione;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sComplicanzeOld) || bCopyAll)
		m_sComplicanzeOld = pEsamiSet->m_sComplicanzeOld;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sGuarigione) || bCopyAll)
		m_sGuarigione = pEsamiSet->m_sGuarigione;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sQuadro) || bCopyAll)
		m_sQuadro = pEsamiSet->m_sQuadro;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sMetodo) || bCopyAll)
		m_sMetodo = pEsamiSet->m_sMetodo;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sEstensione) || bCopyAll)
		m_sEstensione = pEsamiSet->m_sEstensione;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sProcTerapeutiche) || bCopyAll)
		m_sProcTerapeutiche = pEsamiSet->m_sProcTerapeutiche;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sProcDiagnostiche) || bCopyAll)
		m_sProcDiagnostiche = pEsamiSet->m_sProcDiagnostiche;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sMstComplicanze1) || bCopyAll)
		m_sMstComplicanze1 = pEsamiSet->m_sMstComplicanze1;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sMstComplicanze2) || bCopyAll)
		m_sMstComplicanze2 = pEsamiSet->m_sMstComplicanze2;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sMstComplicanze3) || bCopyAll)
		m_sMstComplicanze3 = pEsamiSet->m_sMstComplicanze3;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lProvenienza) || bCopyAll)
		m_lProvenienza = pEsamiSet->m_lProvenienza;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lInviante) || bCopyAll)
		m_lInviante = pEsamiSet->m_lInviante;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lCamera) || bCopyAll)
		m_lCamera = pEsamiSet->m_lCamera;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sInvMedico) || bCopyAll)
		m_sInvMedico = pEsamiSet->m_sInvMedico;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lInvMedico) || bCopyAll)
		m_lInvMedico = pEsamiSet->m_lInvMedico;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lFumo) || bCopyAll)
		m_lFumo = pEsamiSet->m_lFumo;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lSigarette) || bCopyAll)
		m_lSigarette = pEsamiSet->m_lSigarette;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lCaffe) || bCopyAll)
		m_lCaffe = pEsamiSet->m_lCaffe;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lAlcool) || bCopyAll)
		m_lAlcool = pEsamiSet->m_lAlcool;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lSuperAlcolici) || bCopyAll)
		m_lSuperAlcolici = pEsamiSet->m_lSuperAlcolici;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sDenFarmaci) || bCopyAll)
		m_sDenFarmaci = pEsamiSet->m_sDenFarmaci;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lAssunzione) || bCopyAll)
		m_lAssunzione = pEsamiSet->m_lAssunzione;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_fPeso) || bCopyAll)
		m_fPeso = pEsamiSet->m_fPeso;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_fAltezza) || bCopyAll)
		m_fAltezza = pEsamiSet->m_fAltezza;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_fBMI) || bCopyAll)
		m_fBMI = pEsamiSet->m_fBMI;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_fMisuraA) || bCopyAll)
		m_fMisuraA = pEsamiSet->m_fMisuraA;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_fMisuraB) || bCopyAll)
		m_fMisuraB = pEsamiSet->m_fMisuraB;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_fMisuraC) || bCopyAll)
		m_fMisuraC = pEsamiSet->m_fMisuraC;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_fVolume) || bCopyAll)
		m_fVolume = pEsamiSet->m_fVolume;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_fBSA) || bCopyAll)
		m_fBSA = pEsamiSet->m_fBSA;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sComplicanze1) || bCopyAll)
		m_sComplicanze1 = pEsamiSet->m_sComplicanze1;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sComplicanze2) || bCopyAll)
		m_sComplicanze2 = pEsamiSet->m_sComplicanze2;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sComplicanze3) || bCopyAll)
		m_sComplicanze3 = pEsamiSet->m_sComplicanze3;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lIDVersione) || bCopyAll)
		m_lIDVersione = pEsamiSet->m_lIDVersione;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sNoteMonitoraggio) || bCopyAll)
		m_sNoteMonitoraggio = pEsamiSet->m_sNoteMonitoraggio;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lInfermiereMonitoraggio) || bCopyAll)
		m_lInfermiereMonitoraggio = pEsamiSet->m_lInfermiereMonitoraggio;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lOspedale) || bCopyAll)
		m_lOspedale = pEsamiSet->m_lOspedale;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_nCodiceRAO) || bCopyAll)
		m_nCodiceRAO = pEsamiSet->m_nCodiceRAO;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_bConcordanza) || bCopyAll)
		m_bConcordanza = pEsamiSet->m_bConcordanza;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_nCodiceRAOSpec) || bCopyAll)
		m_nCodiceRAOSpec = pEsamiSet->m_nCodiceRAOSpec;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_iConsensoInformato) || bCopyAll)
		m_iConsensoInformato = pEsamiSet->m_iConsensoInformato;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sNoteConsensoInformato) || bCopyAll)
		m_sNoteConsensoInformato = pEsamiSet->m_sNoteConsensoInformato;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_iAllergie) || bCopyAll)
		m_iAllergie = pEsamiSet->m_iAllergie;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sDescrizioneAllergie) || bCopyAll)
		m_sDescrizioneAllergie = pEsamiSet->m_sDescrizioneAllergie;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_iPacemaker) || bCopyAll)
		m_iPacemaker = pEsamiSet->m_iPacemaker;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sDescrizionePacemaker) || bCopyAll)
		m_sDescrizionePacemaker = pEsamiSet->m_sDescrizionePacemaker;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_iAnticoagulanti) || bCopyAll)
		m_iAnticoagulanti = pEsamiSet->m_iAnticoagulanti;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sDescrizioneAnticoagulanti) || bCopyAll)
		m_sDescrizioneAnticoagulanti = pEsamiSet->m_sDescrizioneAnticoagulanti;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_iAntiaggreganti) || bCopyAll)
		m_iAntiaggreganti = pEsamiSet->m_iAntiaggreganti;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sDescrizioneAntiaggreganti) || bCopyAll)
		m_sDescrizioneAntiaggreganti = pEsamiSet->m_sDescrizioneAntiaggreganti;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_iBreathTestHP) || bCopyAll)
		m_iBreathTestHP = pEsamiSet->m_iBreathTestHP;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_fBreathTestHPVal1) || bCopyAll)
		m_fBreathTestHPVal1 = pEsamiSet->m_fBreathTestHPVal1;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_fBreathTestHPVal2) || bCopyAll)
		m_fBreathTestHPVal2 = pEsamiSet->m_fBreathTestHPVal2;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_fBreathTestHPDiff) || bCopyAll)
		m_fBreathTestHPDiff = pEsamiSet->m_fBreathTestHPDiff;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lIDSedeEsame) || bCopyAll)
		m_lIDSedeEsame = pEsamiSet->m_lIDSedeEsame;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sSalaEsame) || bCopyAll)
		m_sSalaEsame = pEsamiSet->m_sSalaEsame;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lTipoDegenzaInterno) || bCopyAll)
		m_lTipoDegenzaInterno = pEsamiSet->m_lTipoDegenzaInterno;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lTipoDegenzaEsterno) || bCopyAll)
		m_lTipoDegenzaEsterno = pEsamiSet->m_lTipoDegenzaEsterno;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lFluoroscopiaMinuti) || bCopyAll)
		m_lFluoroscopiaMinuti = pEsamiSet->m_lFluoroscopiaMinuti;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lFluoroscopiaSecondi) || bCopyAll)
		m_lFluoroscopiaSecondi = pEsamiSet->m_lFluoroscopiaSecondi;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_fFluoroscopiaDose) || bCopyAll)
		m_fFluoroscopiaDose = pEsamiSet->m_fFluoroscopiaDose;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_bFirmato) || bCopyAll) // Davide - Firma digitale
		m_bFirmato = pEsamiSet->m_bFirmato;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_bLocked) || bCopyAll)
		m_bLocked = pEsamiSet->m_bLocked;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lIdUtenteLock) || bCopyAll)
		m_lIdUtenteLock = pEsamiSet->m_lIdUtenteLock;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sDataOraLock) || bCopyAll)
		m_sDataOraLock = pEsamiSet->m_sDataOraLock;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lIDSedePrevista) || bCopyAll) // gli ID delle sedi servono per gli interfacciamenti, NON RIMUOVERE!
		m_lIDSedePrevista = pEsamiSet->m_lIDSedePrevista;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sSedePrevista) || bCopyAll)
		m_sSedePrevista = pEsamiSet->m_sSedePrevista;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lIDSedeRaggiunta) || bCopyAll) // gli ID delle sedi servono per gli interfacciamenti, NON RIMUOVERE!
		m_lIDSedeRaggiunta = pEsamiSet->m_lIDSedeRaggiunta;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sSedeRaggiunta) || bCopyAll)
		m_sSedeRaggiunta = pEsamiSet->m_sSedeRaggiunta;

	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sAPDataInvio) || bCopyAll)
		m_sAPDataInvio = pEsamiSet->m_sAPDataInvio;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sAPOperInvio) || bCopyAll)
		m_sAPOperInvio = pEsamiSet->m_sAPOperInvio;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sAPDataAnnullamento) || bCopyAll)
		m_sAPDataAnnullamento = pEsamiSet->m_sAPDataAnnullamento;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sAPOperAnnullamento) || bCopyAll)
		m_sAPOperAnnullamento = pEsamiSet->m_sAPOperAnnullamento;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sAPDataRicezione) || bCopyAll)
		m_sAPDataRicezione = pEsamiSet->m_sAPDataRicezione;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sAPDataConferma) || bCopyAll)
		m_sAPDataConferma = pEsamiSet->m_sAPDataConferma;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sAPOperConferma) || bCopyAll)
		m_sAPOperConferma = pEsamiSet->m_sAPOperConferma;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lAPStato) || bCopyAll)
		m_lAPStato = pEsamiSet->m_lAPStato;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sAPMotivazioneRifiuto) || bCopyAll)
		m_sAPMotivazioneRifiuto = pEsamiSet->m_sAPMotivazioneRifiuto;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sAPDescrizioneRichiesta) || bCopyAll)
		m_sAPDescrizioneRichiesta = pEsamiSet->m_sAPDescrizioneRichiesta;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sAPRispostaCodificata) || bCopyAll)
		m_sAPRispostaCodificata = pEsamiSet->m_sAPRispostaCodificata;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sAPRispostaLibera) || bCopyAll)
		m_sAPRispostaLibera = pEsamiSet->m_sAPRispostaLibera;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sAPRefertoPDF) || bCopyAll)
		m_sAPRefertoPDF = pEsamiSet->m_sAPRefertoPDF;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sAPSuggerimenti1) || bCopyAll)
		m_sAPSuggerimenti1 = pEsamiSet->m_sAPSuggerimenti1;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sAPSuggerimenti2) || bCopyAll)
		m_sAPSuggerimenti2 = pEsamiSet->m_sAPSuggerimenti2;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sAPIDRichiesta) || bCopyAll)
		m_sAPIDRichiesta = pEsamiSet->m_sAPIDRichiesta;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_nAPSpedireRitirare) || bCopyAll)
		m_nAPSpedireRitirare = pEsamiSet->m_nAPSpedireRitirare;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_bAPRefertato) || bCopyAll)
		m_bAPRefertato = pEsamiSet->m_bAPRefertato;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_bAPVerificato) || bCopyAll)
		m_bAPVerificato = pEsamiSet->m_bAPVerificato;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_nAPVerificatoMedico) || bCopyAll)
		m_nAPVerificatoMedico = pEsamiSet->m_nAPVerificatoMedico;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_bAPSpeditoRitirato) || bCopyAll)
		m_bAPSpeditoRitirato = pEsamiSet->m_bAPSpeditoRitirato;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sAPDataVerificato) || bCopyAll)
		m_sAPDataVerificato = pEsamiSet->m_sAPDataVerificato;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sAPDataSpeditoRitirato) || bCopyAll)
		m_sAPDataSpeditoRitirato = pEsamiSet->m_sAPDataSpeditoRitirato;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sAPProvenienza) || bCopyAll)
		m_sAPProvenienza = pEsamiSet->m_sAPProvenienza;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sAPConvenzione) || bCopyAll)
		m_sAPConvenzione = pEsamiSet->m_sAPConvenzione;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sAPIndirizzo) || bCopyAll)
		m_sAPIndirizzo = pEsamiSet->m_sAPIndirizzo;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_nAPEseguitiPrelievi) || bCopyAll)
		m_nAPEseguitiPrelievi = pEsamiSet->m_nAPEseguitiPrelievi;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lAPIdRicetta) || bCopyAll)
		m_lAPIdRicetta = pEsamiSet->m_lAPIdRicetta;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sAPGroupNumber) || bCopyAll)
		m_sAPGroupNumber = pEsamiSet->m_sAPGroupNumber;

	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lIDComplicanzeImmediate) || bCopyAll)
		m_lIDComplicanzeImmediate = pEsamiSet->m_lIDComplicanzeImmediate;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lIDComplicanzeTardive) || bCopyAll)
		m_lIDComplicanzeTardive = pEsamiSet->m_lIDComplicanzeTardive;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lIDPulizia) || bCopyAll)
		m_lIDPulizia = pEsamiSet->m_lIDPulizia;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lIDCausaNonCompleto) || bCopyAll)
		m_lIDCausaNonCompleto = pEsamiSet->m_lIDCausaNonCompleto;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_bNecAssistenzaOspedaliera) || bCopyAll)
		m_bNecAssistenzaOspedaliera = pEsamiSet->m_bNecAssistenzaOspedaliera;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lIDTolleranza) || bCopyAll)
		m_lIDTolleranza = pEsamiSet->m_lIDTolleranza;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sPremedPosologia) || bCopyAll)
		m_sPremedPosologia = pEsamiSet->m_sPremedPosologia;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lIDConclusioniScreening) || bCopyAll)
		m_lIDConclusioniScreening = pEsamiSet->m_lIDConclusioniScreening;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lIDConclusioniColon) || bCopyAll)
		m_lIDConclusioniColon = pEsamiSet->m_lIDConclusioniColon;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lIDAltreAnomalie) || bCopyAll)
		m_lIDAltreAnomalie = pEsamiSet->m_lIDAltreAnomalie;

	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_bSuperLocked) || bCopyAll)
		m_bSuperLocked = pEsamiSet->m_bSuperLocked;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lIdUtenteSuperLock) || bCopyAll)
		m_lIdUtenteSuperLock = pEsamiSet->m_lIdUtenteSuperLock;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sDataOraSuperLock) || bCopyAll)
		m_sDataOraSuperLock = pEsamiSet->m_sDataOraSuperLock;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sDataOraSuperLockPrimo) || bCopyAll)
		m_sDataOraSuperLockPrimo = pEsamiSet->m_sDataOraSuperLockPrimo;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_bInviatoScreening) || bCopyAll)
		m_bInviatoScreening = pEsamiSet->m_bInviatoScreening;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lIDDiagnosiFinale) || bCopyAll)
		m_lIDDiagnosiFinale = pEsamiSet->m_lIDDiagnosiFinale;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_iSospeso) || bCopyAll)
		m_iSospeso = pEsamiSet->m_iSospeso;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lDataScadenzaSospensione) || bCopyAll)
		m_lDataScadenzaSospensione = pEsamiSet->m_lDataScadenzaSospensione;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sMotivoSospensione) || bCopyAll)
		m_sMotivoSospensione = pEsamiSet->m_sMotivoSospensione;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sDataOraAcquisizione) || bCopyAll)
		m_sDataOraAcquisizione = pEsamiSet->m_sDataOraAcquisizione;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sTempoConvalida) || bCopyAll)
		m_sTempoConvalida = pEsamiSet->m_sTempoConvalida;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sTempoChiusura) || bCopyAll)
		m_sTempoChiusura = pEsamiSet->m_sTempoChiusura;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lCustomDataOraInizioAcq) || bCopyAll)
		m_lCustomDataOraInizioAcq = pEsamiSet->m_lCustomDataOraInizioAcq;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lCustomDataOraFineAcq) || bCopyAll)
		m_lCustomDataOraFineAcq = pEsamiSet->m_lCustomDataOraFineAcq;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sPressione1) || bCopyAll)
		m_sPressione1 = pEsamiSet->m_sPressione1;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sPressione2) || bCopyAll)
		m_sPressione2 = pEsamiSet->m_sPressione2;

	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_bInviatoInps) || bCopyAll)
		m_bInviatoInps = pEsamiSet->m_bInviatoInps;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lInpsDataInizio) || bCopyAll)
		m_lInpsDataInizio = pEsamiSet->m_lInpsDataInizio;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lInpsDataFine) || bCopyAll)
		m_lInpsDataFine = pEsamiSet->m_lInpsDataFine;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_iInpsTipo) || bCopyAll)
		m_iInpsTipo = pEsamiSet->m_iInpsTipo;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sInpsNote) || bCopyAll)
		m_sInpsNote = pEsamiSet->m_sInpsNote;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sInpsCognome) || bCopyAll)
		m_sInpsCognome = pEsamiSet->m_sInpsCognome;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sInpsVia) || bCopyAll)
		m_sInpsVia = pEsamiSet->m_sInpsVia;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sInpsCap) || bCopyAll)
		m_sInpsCap = pEsamiSet->m_sInpsCap;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sInpsComune) || bCopyAll)
		m_sInpsComune = pEsamiSet->m_sInpsComune;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sInpsProvincia) || bCopyAll)
		m_sInpsProvincia = pEsamiSet->m_sInpsProvincia;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sInpsIdAnnullamento) || bCopyAll)
		m_sInpsIdAnnullamento = pEsamiSet->m_sInpsIdAnnullamento;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sInpsNumeroProtocollo) || bCopyAll)
		m_sInpsNumeroProtocollo = pEsamiSet->m_sInpsNumeroProtocollo;

	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_bSissOscuramento10) || bCopyAll)
		m_bSissOscuramento10 = pEsamiSet->m_bSissOscuramento10;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_bSissOscuramento20) || bCopyAll)
		m_bSissOscuramento20 = pEsamiSet->m_bSissOscuramento20;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_bSissOscuramento30) || bCopyAll)
		m_bSissOscuramento30 = pEsamiSet->m_bSissOscuramento30;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_bSissOscuramento40) || bCopyAll)
		m_bSissOscuramento40 = pEsamiSet->m_bSissOscuramento40;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_bSissOscuramento50) || bCopyAll)
		m_bSissOscuramento50 = pEsamiSet->m_bSissOscuramento50;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_bSissOscuramento50Bloccato) || bCopyAll)
		m_bSissOscuramento50Bloccato = pEsamiSet->m_bSissOscuramento50Bloccato;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_bSissAutorizzazioneConsultaz) || bCopyAll)
		m_bSissAutorizzazioneConsultaz = pEsamiSet->m_bSissAutorizzazioneConsultaz;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sSissNoteReperibilita) || bCopyAll)
		m_sSissNoteReperibilita = pEsamiSet->m_sSissNoteReperibilita;

	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sIdEpisodioRicovero) || bCopyAll)
		m_sIdEpisodioRicovero = pEsamiSet->m_sIdEpisodioRicovero;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lDataRicoveroCustom) || bCopyAll)
		m_lDataRicoveroCustom = pEsamiSet->m_lDataRicoveroCustom;

	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lIDMalattiaCronica) || bCopyAll)
		m_lIDMalattiaCronica = pEsamiSet->m_lIDMalattiaCronica;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_bRecordSenzaAccesso) || bCopyAll)
		m_bRecordSenzaAccesso = pEsamiSet->m_bRecordSenzaAccesso;

	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sPazientiCroniciScoreHB) || bCopyAll)
		m_sPazientiCroniciScoreHB = pEsamiSet->m_sPazientiCroniciScoreHB;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sPazientiCroniciScoreS) || bCopyAll)
		m_sPazientiCroniciScoreS = pEsamiSet->m_sPazientiCroniciScoreS;

	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lIDStudio) || bCopyAll)
		m_lIDStudio = pEsamiSet->m_lIDStudio;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lDataStudio) || bCopyAll)
		m_lDataStudio = pEsamiSet->m_lDataStudio;

	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lIDUtenteInserimentoEsame) || bCopyAll)
		m_lIDUtenteInserimentoEsame = pEsamiSet->m_lIDUtenteInserimentoEsame;

	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lDataRefertoIstologico) || bCopyAll)
		m_lDataRefertoIstologico = pEsamiSet->m_lDataRefertoIstologico;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_bPresenzaLesioneSospettaCCR) || bCopyAll)
		m_bPresenzaLesioneSospettaCCR = pEsamiSet->m_bPresenzaLesioneSospettaCCR;		
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lNumeroTotalePolipi) || bCopyAll)
		m_lNumeroTotalePolipi = pEsamiSet->m_lNumeroTotalePolipi;		

	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lBostonScoreDx) || bCopyAll)
		m_lBostonScoreDx = pEsamiSet->m_lBostonScoreDx;		
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lBostonScoreMid) || bCopyAll)
		m_lBostonScoreMid = pEsamiSet->m_lBostonScoreMid;		
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lBostonScoreSx) || bCopyAll)
		m_lBostonScoreSx = pEsamiSet->m_lBostonScoreSx;		
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lTempoRetrazione) || bCopyAll)
		m_lTempoRetrazione = pEsamiSet->m_lTempoRetrazione;	

	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sEsenzioneDaIntegrazione) || bCopyAll)
		m_sEsenzioneDaIntegrazione = pEsamiSet->m_sEsenzioneDaIntegrazione;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_bPagamentoRicevuto) || bCopyAll)
		m_bPagamentoRicevuto = pEsamiSet->m_bPagamentoRicevuto;

	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_bNonSbloccabile) || bCopyAll)
		m_bNonSbloccabile = pEsamiSet->m_bNonSbloccabile;

	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sRefertoTestoRtf) || bCopyAll)
		m_sRefertoTestoRtf = pEsamiSet->m_sRefertoTestoRtf;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sRefertoTestoTxt) || bCopyAll)
		m_sRefertoTestoTxt = pEsamiSet->m_sRefertoTestoTxt;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sRefertoTestoHtml) || bCopyAll)
		m_sRefertoTestoHtml = pEsamiSet->m_sRefertoTestoHtml;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sRefertoDataOra) || bCopyAll)
		m_sRefertoDataOra = pEsamiSet->m_sRefertoDataOra;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lRefertoRedattore) || bCopyAll)
		m_lRefertoRedattore = pEsamiSet->m_lRefertoRedattore;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_bRefertoScaduto) || bCopyAll)
		m_bRefertoScaduto = pEsamiSet->m_bRefertoScaduto;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lRefertoStato) || bCopyAll)
		m_lRefertoStato = pEsamiSet->m_lRefertoStato;

	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_bChiusuraBloccataDaIntegrazione) || bCopyAll)
		m_bChiusuraBloccataDaIntegrazione = pEsamiSet->m_bChiusuraBloccataDaIntegrazione;

	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lLivelloUrgenza) || bCopyAll)
		m_lLivelloUrgenza = pEsamiSet->m_lLivelloUrgenza;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lFrazioneEiezione) || bCopyAll)
		m_lFrazioneEiezione = pEsamiSet->m_lFrazioneEiezione;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lIdProvenienzaNew) || bCopyAll)
		m_lIdProvenienzaNew = pEsamiSet->m_lIdProvenienzaNew;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lStatoInvioCentraleRefertaz) || bCopyAll)
		m_lStatoInvioCentraleRefertaz = pEsamiSet->m_lStatoInvioCentraleRefertaz;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lStatoInvioControlloQualita) || bCopyAll)
		m_lStatoInvioControlloQualita = pEsamiSet->m_lStatoInvioControlloQualita;

	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lVersioneGridCL) || bCopyAll)
		m_lVersioneGridCL = pEsamiSet->m_lVersioneGridCL;

	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sQuesitoDiagnostico) || bCopyAll)
		m_sQuesitoDiagnostico = pEsamiSet->m_sQuesitoDiagnostico;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sQuesitoDiagnosticoCodificato) || bCopyAll)
		m_sQuesitoDiagnosticoCodificato = pEsamiSet->m_sQuesitoDiagnosticoCodificato;

	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lIDUltimaChecklistUsata) || bCopyAll)
		m_lIDUltimaChecklistUsata = pEsamiSet->m_lIDUltimaChecklistUsata;

	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sFCMassima) || bCopyAll)
		m_sFCMassima = pEsamiSet->m_sFCMassima;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sFCSubmassima) || bCopyAll)
		m_sFCSubmassima = pEsamiSet->m_sFCSubmassima;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lIDProtocolloUsato) || bCopyAll)
		m_lIDProtocolloUsato = pEsamiSet->m_lIDProtocolloUsato;

	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sRefertoConiugatoPrincipale) || bCopyAll)
		m_sRefertoConiugatoPrincipale = pEsamiSet->m_sRefertoConiugatoPrincipale;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sRefertoConiugatoSecondario) || bCopyAll)
		m_sRefertoConiugatoSecondario = pEsamiSet->m_sRefertoConiugatoSecondario;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_bRefertoConiugatoAltraUO) || bCopyAll)
		m_bRefertoConiugatoAltraUO = pEsamiSet->m_bRefertoConiugatoAltraUO;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_bRefertoConiugatoImportato) || bCopyAll)
		m_bRefertoConiugatoImportato = pEsamiSet->m_bRefertoConiugatoImportato;

	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sFleuryTrasferito) || bCopyAll)
		m_sFleuryTrasferito = pEsamiSet->m_sFleuryTrasferito;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sFleuryEndpointRemoto) || bCopyAll)
		m_sFleuryEndpointRemoto = pEsamiSet->m_sFleuryEndpointRemoto;

	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_bEliminato) || bCopyAll)
		m_bEliminato = pEsamiSet->m_bEliminato;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lUO) || bCopyAll)
		m_lUO = pEsamiSet->m_lUO;
	//Luiz - 13/05/2019 - P3 - Atualiza nome/sobrenome Médico - Inclui Médicos solicitantes
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sInvMedico2) || bCopyAll)
	m_sInvMedico2 = pEsamiSet->m_sInvMedico2;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lInvMedico2) || bCopyAll)
	m_lInvMedico2 = pEsamiSet->m_lInvMedico2;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sInvMedico3) || bCopyAll)
	m_sInvMedico3 = pEsamiSet->m_sInvMedico3;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lInvMedico3) || bCopyAll)
	m_lInvMedico3 = pEsamiSet->m_lInvMedico3;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sInvMedico4) || bCopyAll)
	m_sInvMedico4 = pEsamiSet->m_sInvMedico4;
	if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lInvMedico4) || bCopyAll)
	m_lInvMedico4 = pEsamiSet->m_lInvMedico4;

	//Gabriel - P3
	if (m_bColumnsP3)
	{
		if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_bHyperLocked) || bCopyAll)
			m_bHyperLocked = pEsamiSet->m_bHyperLocked;
		if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lIdUtenteHyperLock) || bCopyAll)
			m_lIdUtenteHyperLock = pEsamiSet->m_lIdUtenteHyperLock;
		if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sDataOraHyperLock) || bCopyAll)
			m_sDataOraHyperLock = pEsamiSet->m_sDataOraHyperLock;
	}
	
	//Gabriel - TCP
	if (m_bColumnsTCP)
	{
		if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_lStatoInvioAltraUnita) || bCopyAll)
			m_lStatoInvioAltraUnita = pEsamiSet->m_lStatoInvioAltraUnita;
		if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sCodesameCorrelati) || bCopyAll)
			m_sCodesameCorrelati = pEsamiSet->m_sCodesameCorrelati;
		if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sRefertoTestoCorrelatiRtf) || bCopyAll)
			m_sRefertoTestoCorrelatiRtf = pEsamiSet->m_sRefertoTestoCorrelatiRtf;
		if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sRefertoTestoCorrelatiTxt) || bCopyAll)
			m_sRefertoTestoCorrelatiTxt = pEsamiSet->m_sRefertoTestoCorrelatiTxt;
		if (!pEsamiSet->IsOpen() || pEsamiSet->IsFieldDirty(&pEsamiSet->m_sRefertoTestoCorrelatiHtml) || bCopyAll)
			m_sRefertoTestoCorrelatiHtml = pEsamiSet->m_sRefertoTestoCorrelatiHtml;
	}
	
	m_lNumEsame = pEsamiSet->m_lNumEsame;
}

void CEsamiSet::SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento)
{
	CEsamiSet* pOV = (CEsamiSet*)pOldValues;
	CEsamiSet* pNV = (CEsamiSet*)pNewValues;

	CWriteLogLineSet sp(GetTableName(), GetIdentityString(), GetIdentityLong(), sCommento); 

	if (pOldValues->m_nFields == 2 || pNewValues->m_nFields == 2)
	{
		sp.Execute("IDVersione", pOV, &pOV->m_lIDVersione, pNV, &pNV->m_lIDVersione);
		return;
	}

	sp.Execute("Ricovero", pOV, &pOV->m_sRicovero, pNV, &pNV->m_sRicovero);
	sp.Execute("CodEsame", pOV, &pOV->m_sCodEsame, pNV, &pNV->m_sCodEsame);
	sp.Execute("Paziente", pOV, &pOV->m_lPaziente, pNV, &pNV->m_lPaziente);
	sp.Execute("IDEsame", pOV, &pOV->m_lIDEsame, pNV, &pNV->m_lIDEsame);
	sp.Execute("Data", pOV, &pOV->m_lData, pNV, &pNV->m_lData);
	sp.Execute("Medico", pOV, &pOV->m_lMedico, pNV, &pNV->m_lMedico);
	sp.Execute("MedicoLibero", pOV, &pOV->m_sMedicoLibero, pNV, &pNV->m_sMedicoLibero);
	sp.Execute("Assistente", pOV, &pOV->m_lAssistente, pNV, &pNV->m_lAssistente);
	sp.Execute("AssistenteLibero", pOV, &pOV->m_sAssistenteLibero, pNV, &pNV->m_sAssistenteLibero);
	sp.Execute("Anestesista", pOV, &pOV->m_sAnestesista, pNV, &pNV->m_sAnestesista);
	sp.Execute("Infermiere1", pOV, &pOV->m_lInfermiere1, pNV, &pNV->m_lInfermiere1);
	sp.Execute("Infermiere2", pOV, &pOV->m_lInfermiere2, pNV, &pNV->m_lInfermiere2);
	sp.Execute("Terapia", pOV, &pOV->m_sTerapia, pNV, &pNV->m_sTerapia);
	sp.Execute("DataControllo", pOV, &pOV->m_lDataControllo, pNV, &pNV->m_lDataControllo);
	sp.Execute("Durata", pOV, &pOV->m_lDurata, pNV, &pNV->m_lDurata);
	sp.Execute("Difficolta", pOV, &pOV->m_lDifficolta, pNV, &pNV->m_lDifficolta);
	sp.Execute("Conclusioni", pOV, &pOV->m_sConclusioni, pNV, &pNV->m_sConclusioni);
	sp.Execute("Integrazioni", pOV, &pOV->m_sIntegrazioni, pNV, &pNV->m_sIntegrazioni);
	sp.Execute("Appunti", pOV, &pOV->m_sAppunti, pNV, &pNV->m_sAppunti);
	sp.Execute("Indicazioni", pOV, &pOV->m_sIndicazioni, pNV, &pNV->m_sIndicazioni);
	sp.Execute("FarmacoTrial", pOV, &pOV->m_sFarmacoTrial, pNV, &pNV->m_sFarmacoTrial);
	sp.Execute("Studio", pOV, &pOV->m_sStudio, pNV, &pNV->m_sStudio);
	sp.Execute("TipoVisita", pOV, &pOV->m_sTipoVisita, pNV, &pNV->m_sTipoVisita);
	sp.Execute("IdPremedicazione", pOV, &pOV->m_lIdPremedicazione, pNV, &pNV->m_lIdPremedicazione);
	sp.Execute("Premedicazioni", pOV, &pOV->m_sPremedicazioni, pNV, &pNV->m_sPremedicazioni);
	sp.Execute("Strumenti", pOV, &pOV->m_sStrumenti, pNV, &pNV->m_sStrumenti);
	sp.Execute("Accessori", pOV, &pOV->m_sAccessori, pNV, &pNV->m_sAccessori);
	sp.Execute("ProgressivoAnno", pOV, &pOV->m_sProgressivoAnno, pNV, &pNV->m_sProgressivoAnno);
	sp.Execute("CodicePrenotazione", pOV, &pOV->m_sCodicePrenotazione, pNV, &pNV->m_sCodicePrenotazione);
	sp.Execute("Valutazione", pOV, &pOV->m_sValutazione, pNV, &pNV->m_sValutazione);
	sp.Execute("ComplicanzeOld", pOV, &pOV->m_sComplicanzeOld, pNV, &pNV->m_sComplicanzeOld);
	sp.Execute("Guarigione", pOV, &pOV->m_sGuarigione, pNV, &pNV->m_sGuarigione);
	sp.Execute("Quadro", pOV, &pOV->m_sQuadro, pNV, &pNV->m_sQuadro);
	sp.Execute("Metodo", pOV, &pOV->m_sMetodo, pNV, &pNV->m_sMetodo);
	sp.Execute("Estensione", pOV, &pOV->m_sEstensione, pNV, &pNV->m_sEstensione);
	sp.Execute("ProcTerapeutiche", pOV, &pOV->m_sProcTerapeutiche, pNV, &pNV->m_sProcTerapeutiche);
	sp.Execute("ProcDiagnostiche", pOV, &pOV->m_sProcDiagnostiche, pNV, &pNV->m_sProcDiagnostiche);
	sp.Execute("MstComplicanze1", pOV, &pOV->m_sMstComplicanze1, pNV, &pNV->m_sMstComplicanze1);
	sp.Execute("MstComplicanze2", pOV, &pOV->m_sMstComplicanze2, pNV, &pNV->m_sMstComplicanze2);
	sp.Execute("MstComplicanze3", pOV, &pOV->m_sMstComplicanze3, pNV, &pNV->m_sMstComplicanze3);
	sp.Execute("Provenienza", pOV, &pOV->m_lProvenienza, pNV, &pNV->m_lProvenienza);
	sp.Execute("Inviante", pOV, &pOV->m_lInviante, pNV, &pNV->m_lInviante);
	sp.Execute("Camera", pOV, &pOV->m_lCamera, pNV, &pNV->m_lCamera);
	sp.Execute("InvMedico", pOV, &pOV->m_sInvMedico, pNV, &pNV->m_sInvMedico);
	sp.Execute("IdInvMedico", pOV, &pOV->m_lInvMedico, pNV, &pNV->m_lInvMedico);
	sp.Execute("Fumo", pOV, &pOV->m_lFumo, pNV, &pNV->m_lFumo);
	sp.Execute("Sigarette", pOV, &pOV->m_lSigarette, pNV, &pNV->m_lSigarette);
	sp.Execute("Caffe", pOV, &pOV->m_lCaffe, pNV, &pNV->m_lCaffe);
	sp.Execute("Alcool", pOV, &pOV->m_lAlcool, pNV, &pNV->m_lAlcool);
	sp.Execute("SuperAlcolici", pOV, &pOV->m_lSuperAlcolici, pNV, &pNV->m_lSuperAlcolici);
	sp.Execute("Den_Farmaci", pOV, &pOV->m_sDenFarmaci, pNV, &pNV->m_sDenFarmaci);
	sp.Execute("Assunzione", pOV, &pOV->m_lAssunzione, pNV, &pNV->m_lAssunzione);
	sp.Execute("Peso", pOV, &pOV->m_fPeso, pNV, &pNV->m_fPeso);
	sp.Execute("Altezza", pOV, &pOV->m_fAltezza, pNV, &pNV->m_fAltezza);
	sp.Execute("BMI", pOV, &pOV->m_fBMI, pNV, &pNV->m_fBMI);
	sp.Execute("MISURAA", pOV, &pOV->m_fMisuraA, pNV, &pNV->m_fMisuraA);
	sp.Execute("MISURAB", pOV, &pOV->m_fMisuraB, pNV, &pNV->m_fMisuraB);
	sp.Execute("MISURAC", pOV, &pOV->m_fMisuraC, pNV, &pNV->m_fMisuraC);
	sp.Execute("VOLUME", pOV, &pOV->m_fVolume, pNV, &pNV->m_fVolume);
	sp.Execute("BSA", pOV, &pOV->m_fBSA, pNV, &pNV->m_fBSA);
	sp.Execute("Complicanze1", pOV, &pOV->m_sComplicanze1, pNV, &pNV->m_sComplicanze1);
	sp.Execute("Complicanze2", pOV, &pOV->m_sComplicanze2, pNV, &pNV->m_sComplicanze2);
	sp.Execute("Complicanze3", pOV, &pOV->m_sComplicanze3, pNV, &pNV->m_sComplicanze3);
	sp.Execute("IDVersione", pOV, &pOV->m_lIDVersione, pNV, &pNV->m_lIDVersione);
	sp.Execute("NoteMonitoraggio", pOV, &pOV->m_sNoteMonitoraggio, pNV, &pNV->m_sNoteMonitoraggio);
	sp.Execute("InfermiereMonitoraggio", pOV, &pOV->m_lInfermiereMonitoraggio, pNV, &pNV->m_lInfermiereMonitoraggio);
	sp.Execute("Ospedale", pOV, &pOV->m_lOspedale, pNV, &pNV->m_lOspedale);
	sp.Execute("CodiceRAO", pOV, &pOV->m_nCodiceRAO, pNV, &pNV->m_nCodiceRAO);
	sp.Execute("Concordanza", pOV, &pOV->m_bConcordanza, pNV, &pNV->m_bConcordanza);
	sp.Execute("CodiceRAOSpec", pOV, &pOV->m_nCodiceRAOSpec, pNV, &pNV->m_nCodiceRAOSpec);
	sp.Execute("ConsensoInformato", pOV, &pOV->m_iConsensoInformato, pNV, &pNV->m_iConsensoInformato);
	sp.Execute("NoteConsensoInformato", pOV, &pOV->m_sNoteConsensoInformato, pNV, &pNV->m_sNoteConsensoInformato);
	sp.Execute("Allergie", pOV, &pOV->m_iAllergie, pNV, &pNV->m_iAllergie);
	sp.Execute("DescrizioneAllergie", pOV, &pOV->m_sDescrizioneAllergie, pNV, &pNV->m_sDescrizioneAllergie);
	sp.Execute("Pacemaker", pOV, &pOV->m_iPacemaker, pNV, &pNV->m_iPacemaker);
	sp.Execute("DescrizionePacemaker", pOV, &pOV->m_sDescrizionePacemaker, pNV, &pNV->m_sDescrizionePacemaker);
	sp.Execute("Anticoagulanti", pOV, &pOV->m_iAnticoagulanti, pNV, &pNV->m_iAnticoagulanti);
	sp.Execute("DescrizioneAnticoagulanti", pOV, &pOV->m_sDescrizioneAnticoagulanti, pNV, &pNV->m_sDescrizioneAnticoagulanti);
	sp.Execute("Antiaggreganti", pOV, &pOV->m_iAntiaggreganti, pNV, &pNV->m_iAntiaggreganti);
	sp.Execute("DescrizioneAntiaggreganti", pOV, &pOV->m_sDescrizioneAntiaggreganti, pNV, &pNV->m_sDescrizioneAntiaggreganti);
	sp.Execute("BreathTestHP", pOV, &pOV->m_iBreathTestHP, pNV, &pNV->m_iBreathTestHP);
	sp.Execute("BreathTestHPVal1", pOV, &pOV->m_fBreathTestHPVal1, pNV, &pNV->m_fBreathTestHPVal1);
	sp.Execute("BreathTestHPVal2", pOV, &pOV->m_fBreathTestHPVal2, pNV, &pNV->m_fBreathTestHPVal2);
	sp.Execute("BreathTestHPDiff", pOV, &pOV->m_fBreathTestHPDiff, pNV, &pNV->m_fBreathTestHPDiff);
	sp.Execute("IDSedeEsame", pOV, &pOV->m_lIDSedeEsame, pNV, &pNV->m_lIDSedeEsame);
	sp.Execute("SalaEsame", pOV, &pOV->m_sSalaEsame, pNV, &pNV->m_sSalaEsame);
	sp.Execute("TipoDegenzaInterno", pOV, &pOV->m_lTipoDegenzaInterno, pNV, &pNV->m_lTipoDegenzaInterno);
	sp.Execute("TipoDegenzaEsterno", pOV, &pOV->m_lTipoDegenzaEsterno, pNV, &pNV->m_lTipoDegenzaEsterno);
	sp.Execute("FluoroscopiaMinuti", pOV, &pOV->m_lFluoroscopiaMinuti, pNV, &pNV->m_lFluoroscopiaMinuti);
	sp.Execute("FluoroscopiaSecondi", pOV, &pOV->m_lFluoroscopiaSecondi, pNV, &pNV->m_lFluoroscopiaSecondi);
	sp.Execute("FluoroscopiaDose", pOV, &pOV->m_fFluoroscopiaDose, pNV, &pNV->m_fFluoroscopiaDose);
	sp.Execute("Firmato", pOV, &pOV->m_bFirmato, pNV, &pNV->m_bFirmato); // Davide - Firma digitale
	sp.Execute("Locked", pOV, &pOV->m_bLocked, pNV, &pNV->m_bLocked);
	sp.Execute("idUtenteLock", pOV, &pOV->m_lIdUtenteLock, pNV, &pNV->m_lIdUtenteLock);
	sp.Execute("DataOraLock", pOV, &pOV->m_sDataOraLock, pNV, &pNV->m_sDataOraLock);
	sp.Execute("IDSedePrevista", pOV, &pOV->m_lIDSedePrevista, pNV, &pNV->m_lIDSedePrevista); // gli ID delle sedi servono per gli interfacciamenti, NON RIMUOVERE!
	sp.Execute("SedePrevista", pOV, &pOV->m_sSedePrevista, pNV, &pNV->m_sSedePrevista);
	sp.Execute("IDSedeRaggiunta", pOV, &pOV->m_lIDSedeRaggiunta, pNV, &pNV->m_lIDSedeRaggiunta); // gli ID delle sedi servono per gli interfacciamenti, NON RIMUOVERE!
	sp.Execute("SedeRaggiunta", pOV, &pOV->m_sSedeRaggiunta, pNV, &pNV->m_sSedeRaggiunta);

	sp.Execute("APDataInvio", pOV, &pOV->m_sAPDataInvio, pNV, &pNV->m_sAPDataInvio);
	sp.Execute("APOperInvio", pOV, &pOV->m_sAPOperInvio, pNV, &pNV->m_sAPOperInvio);
	sp.Execute("APDataAnnullamento", pOV, &pOV->m_sAPDataAnnullamento, pNV, &pNV->m_sAPDataAnnullamento);
	sp.Execute("APOperAnnullamento", pOV, &pOV->m_sAPOperAnnullamento, pNV, &pNV->m_sAPOperAnnullamento);
	sp.Execute("APDataRicezione", pOV, &pOV->m_sAPDataRicezione, pNV, &pNV->m_sAPDataRicezione);
	sp.Execute("APDataConferma", pOV, &pOV->m_sAPDataConferma, pNV, &pNV->m_sAPDataConferma);
	sp.Execute("APOperConferma", pOV, &pOV->m_sAPOperConferma, pNV, &pNV->m_sAPOperConferma);
	sp.Execute("APStato", pOV, &pOV->m_lAPStato, pNV, &pNV->m_lAPStato);
	sp.Execute("APMotivazioneRifiuto", pOV, &pOV->m_sAPMotivazioneRifiuto, pNV, &pNV->m_sAPMotivazioneRifiuto);
	sp.Execute("APDescrizioneRichiesta", pOV, &pOV->m_sAPDescrizioneRichiesta, pNV, &pNV->m_sAPDescrizioneRichiesta);
	sp.Execute("APRispostaCodificata", pOV, &pOV->m_sAPRispostaCodificata, pNV, &pNV->m_sAPRispostaCodificata);
	sp.Execute("APRispostaLibera", pOV, &pOV->m_sAPRispostaLibera, pNV, &pNV->m_sAPRispostaLibera);
	sp.Execute("APRefertoPDF", pOV, &pOV->m_sAPRefertoPDF, pNV, &pNV->m_sAPRefertoPDF);
	sp.Execute("APSuggerimenti1", pOV, &pOV->m_sAPSuggerimenti1, pNV, &pNV->m_sAPSuggerimenti1);
	sp.Execute("APSuggerimenti2", pOV, &pOV->m_sAPSuggerimenti2, pNV, &pNV->m_sAPSuggerimenti2);
	sp.Execute("APIDRichiesta", pOV, &pOV->m_sAPIDRichiesta, pNV, &pNV->m_sAPIDRichiesta);
	sp.Execute("APSpedireRitirare", pOV, &pOV->m_nAPSpedireRitirare, pNV, &pNV->m_nAPSpedireRitirare);
	sp.Execute("APRefertato", pOV, &pOV->m_bAPRefertato, pNV, &pNV->m_bAPRefertato);
	sp.Execute("APVerificato", pOV, &pOV->m_bAPVerificato, pNV, &pNV->m_bAPVerificato);
	sp.Execute("APVerificatoMedico", pOV, &pOV->m_nAPVerificatoMedico, pNV, &pNV->m_nAPVerificatoMedico);
	sp.Execute("APSpeditoRitirato", pOV, &pOV->m_bAPSpeditoRitirato, pNV, &pNV->m_bAPSpeditoRitirato);
	sp.Execute("APDataVerificato", pOV, &pOV->m_sAPDataVerificato, pNV, &pNV->m_sAPDataVerificato);
	sp.Execute("APDataSpeditoRitirato", pOV, &pOV->m_sAPDataSpeditoRitirato, pNV, &pNV->m_sAPDataSpeditoRitirato);
	sp.Execute("APProvenienza", pOV, &pOV->m_sAPProvenienza, pNV, &pNV->m_sAPProvenienza);
	sp.Execute("APConvenzione", pOV, &pOV->m_sAPConvenzione, pNV, &pNV->m_sAPConvenzione);
	sp.Execute("APIndirizzo", pOV, &pOV->m_sAPIndirizzo, pNV, &pNV->m_sAPIndirizzo);
	sp.Execute("APEseguitiPrelievi", pOV, &pOV->m_nAPEseguitiPrelievi, pNV, &pNV->m_nAPEseguitiPrelievi);
	sp.Execute("APIdRicetta", pOV, &pOV->m_lAPIdRicetta, pNV, &pNV->m_lAPIdRicetta);
	sp.Execute("APGroupNumber", pOV, &pOV->m_sAPGroupNumber, pNV, &pNV->m_sAPGroupNumber);

	sp.Execute("IdComplicanzeImmediate", pOV, &pOV->m_lIDComplicanzeImmediate, pNV, &pNV->m_lIDComplicanzeImmediate);
	sp.Execute("IdComplicanzeTardive", pOV, &pOV->m_lIDComplicanzeTardive, pNV, &pNV->m_lIDComplicanzeTardive);
	sp.Execute("IdPulizia", pOV, &pOV->m_lIDPulizia, pNV, &pNV->m_lIDPulizia);
	sp.Execute("IdCausaNonCompleto", pOV, &pOV->m_lIDCausaNonCompleto, pNV, &pNV->m_lIDCausaNonCompleto);
	sp.Execute("NecAssistenzaOspedaliera", pOV, &pOV->m_bNecAssistenzaOspedaliera, pNV, &pNV->m_bNecAssistenzaOspedaliera);
	sp.Execute("IdTolleranza", pOV, &pOV->m_lIDTolleranza, pNV, &pNV->m_lIDTolleranza);
	sp.Execute("PremedPosologia", pOV, &pOV->m_sPremedPosologia, pNV, &pNV->m_sPremedPosologia);
	sp.Execute("IdConclusioniScreening", pOV, &pOV->m_lIDConclusioniScreening, pNV, &pNV->m_lIDConclusioniScreening);
	sp.Execute("IdConclusioniColon", pOV, &pOV->m_lIDConclusioniColon, pNV, &pNV->m_lIDConclusioniColon);
	sp.Execute("IdAltreAnomalie", pOV, &pOV->m_lIDAltreAnomalie, pNV, &pNV->m_lIDAltreAnomalie);

	sp.Execute("SuperLocked", pOV, &pOV->m_bSuperLocked, pNV, &pNV->m_bSuperLocked);
	sp.Execute("idUtenteSuperLock", pOV, &pOV->m_lIdUtenteSuperLock, pNV, &pNV->m_lIdUtenteSuperLock);
	sp.Execute("DataOraSuperLock", pOV, &pOV->m_sDataOraSuperLock, pNV, &pNV->m_sDataOraSuperLock);
	sp.Execute("DataOraSuperLockPrimo", pOV, &pOV->m_sDataOraSuperLockPrimo, pNV, &pNV->m_sDataOraSuperLockPrimo);
	sp.Execute("InviantoScreening", pOV, &pOV->m_bInviatoScreening, pNV, &pNV->m_bInviatoScreening);
	sp.Execute("IDDiagnosiFinale", pOV, &pOV->m_lIDDiagnosiFinale, pNV, &pNV->m_lIDDiagnosiFinale);
	sp.Execute("Sospeso", pOV, &pOV->m_iSospeso, pNV, &pNV->m_iSospeso);
	sp.Execute("DataScadenzaSospensione", pOV, &pOV->m_lDataScadenzaSospensione, pNV, &pNV->m_lDataScadenzaSospensione);
	sp.Execute("MotivoSospensione", pOV, &pOV->m_sMotivoSospensione, pNV, &pNV->m_sMotivoSospensione);
	sp.Execute("DataOraAcquisizione", pOV, &pOV->m_sDataOraAcquisizione, pNV, &pNV->m_sDataOraAcquisizione);
	sp.Execute("TempoConvalida", pOV, &pOV->m_sTempoConvalida, pNV, &pNV->m_sTempoConvalida);
	sp.Execute("TempoChiusura", pOV, &pOV->m_sTempoChiusura, pNV, &pNV->m_sTempoChiusura);
	sp.Execute("CustomDataOraInizioAcq", pOV, &pOV->m_lCustomDataOraInizioAcq, pNV, &pNV->m_lCustomDataOraInizioAcq);
	sp.Execute("CustomDataOraFineAcq", pOV, &pOV->m_lCustomDataOraFineAcq, pNV, &pNV->m_lCustomDataOraFineAcq);
	sp.Execute("PressioneSanguigna1", pOV, &pOV->m_sPressione1, pNV, &pNV->m_sPressione1);
	sp.Execute("PressioneSanguigna2", pOV, &pOV->m_sPressione2, pNV, &pNV->m_sPressione2);

	sp.Execute("InviatoInps", pOV, &pOV->m_bInviatoInps, pNV, &pNV->m_bInviatoInps);
	sp.Execute("InpsDataInizio", pOV, &pOV->m_lInpsDataInizio, pNV, &pNV->m_lInpsDataInizio);
	sp.Execute("InpsDataFine", pOV, &pOV->m_lInpsDataFine, pNV, &pNV->m_lInpsDataFine);
	sp.Execute("InpsTipo", pOV, &pOV->m_iInpsTipo, pNV, &pNV->m_iInpsTipo);
	sp.Execute("InpsNote", pOV, &pOV->m_sInpsNote, pNV, &pNV->m_sInpsNote);
	sp.Execute("InpsCognome", pOV, &pOV->m_sInpsCognome, pNV, &pNV->m_sInpsCognome);
	sp.Execute("InpsVia", pOV, &pOV->m_sInpsVia, pNV, &pNV->m_sInpsVia);
	sp.Execute("InpsCap", pOV, &pOV->m_sInpsCap, pNV, &pNV->m_sInpsCap);
	sp.Execute("InpsComune", pOV, &pOV->m_sInpsComune, pNV, &pNV->m_sInpsComune);
	sp.Execute("InpsProvincia", pOV, &pOV->m_sInpsProvincia, pNV, &pNV->m_sInpsProvincia);
	sp.Execute("InpsIdAnnullamento", pOV, &pOV->m_sInpsIdAnnullamento, pNV, &pNV->m_sInpsIdAnnullamento);
	sp.Execute("InpsNumeroProtocollo", pOV, &pOV->m_sInpsNumeroProtocollo, pNV, &pNV->m_sInpsNumeroProtocollo);

	sp.Execute("SissOscuramento10", pOV, &pOV->m_bSissOscuramento10, pNV, &pNV->m_bSissOscuramento10);
	sp.Execute("SissOscuramento20", pOV, &pOV->m_bSissOscuramento20, pNV, &pNV->m_bSissOscuramento20);
	sp.Execute("SissOscuramento30", pOV, &pOV->m_bSissOscuramento30, pNV, &pNV->m_bSissOscuramento30);
	sp.Execute("SissOscuramento40", pOV, &pOV->m_bSissOscuramento40, pNV, &pNV->m_bSissOscuramento40);
	sp.Execute("SissOscuramento50", pOV, &pOV->m_bSissOscuramento50, pNV, &pNV->m_bSissOscuramento50);
	sp.Execute("SissOscuramento50Bloccato", pOV, &pOV->m_bSissOscuramento50Bloccato, pNV, &pNV->m_bSissOscuramento50Bloccato);
	sp.Execute("SissAutorizzazioneConsultaz", pOV, &pOV->m_bSissAutorizzazioneConsultaz, pNV, &pNV->m_bSissAutorizzazioneConsultaz);
	sp.Execute("SissNoteReperibilita", pOV, &pOV->m_sSissNoteReperibilita, pNV, &pNV->m_sSissNoteReperibilita);

	sp.Execute("IdEpisodioRicovero", pOV, &pOV->m_sIdEpisodioRicovero, pNV, &pNV->m_sIdEpisodioRicovero);
	sp.Execute("DataRicoveroCustom", pOV, &pOV->m_lDataRicoveroCustom, pNV, &pNV->m_lDataRicoveroCustom);

	sp.Execute("IDMalattiaCronica", pOV, &pOV->m_lIDMalattiaCronica, pNV, &pNV->m_lIDMalattiaCronica);
	sp.Execute("RecordSenzaAccesso", pOV, &pOV->m_bRecordSenzaAccesso, pNV, &pNV->m_bRecordSenzaAccesso);

	sp.Execute("PazientiCroniciScoreHB", pOV, &pOV->m_sPazientiCroniciScoreHB, pNV, &pNV->m_sPazientiCroniciScoreHB);
	sp.Execute("PazientiCroniciScoreS", pOV, &pOV->m_sPazientiCroniciScoreS, pNV, &pNV->m_sPazientiCroniciScoreS);

	sp.Execute("IDStudio", pOV, &pOV->m_lIDStudio, pNV, &pNV->m_lIDStudio);
	sp.Execute("DataStudio", pOV, &pOV->m_lDataStudio, pNV, &pNV->m_lDataStudio);

	sp.Execute("IDUtenteInserimentoEsame", pOV, &pOV->m_lIDUtenteInserimentoEsame, pNV, &pNV->m_lIDUtenteInserimentoEsame);

	sp.Execute("DataRefertoIstologico", pOV, &pOV->m_lDataRefertoIstologico, pNV, &pNV->m_lDataRefertoIstologico);
	sp.Execute("PresenzaLesioneSospettaCCR", pOV, &pOV->m_bPresenzaLesioneSospettaCCR, pNV, &pNV->m_bPresenzaLesioneSospettaCCR);
	sp.Execute("NumeroTotalePolipi", pOV, &pOV->m_lNumeroTotalePolipi, pNV, &pNV->m_lNumeroTotalePolipi);	

	sp.Execute("BostonScoreDx", pOV, &pOV->m_lBostonScoreDx, pNV, &pNV->m_lBostonScoreDx);	
	sp.Execute("BostonScoreMid", pOV, &pOV->m_lBostonScoreMid, pNV, &pNV->m_lBostonScoreMid);	
	sp.Execute("BostonScoreSx", pOV, &pOV->m_lBostonScoreSx, pNV, &pNV->m_lBostonScoreSx);	
	sp.Execute("TempoRetrazione", pOV, &pOV->m_lTempoRetrazione, pNV, &pNV->m_lTempoRetrazione);

	sp.Execute("EsenzioneDaIntegrazione", pOV, &pOV->m_sEsenzioneDaIntegrazione, pNV, &pNV->m_sEsenzioneDaIntegrazione);
	sp.Execute("PagamentoRicevuto", pOV, &pOV->m_bPagamentoRicevuto, pNV, &pNV->m_bPagamentoRicevuto);

	sp.Execute("EsameNonSbloccabile", pOV, &pOV->m_bNonSbloccabile, pNV, &pNV->m_bNonSbloccabile);

	sp.Execute("RefertoTestoRtf", pOV, &pOV->m_sRefertoTestoRtf, pNV, &pNV->m_sRefertoTestoRtf);
	sp.Execute("RefertoTestoTxt", pOV, &pOV->m_sRefertoTestoTxt, pNV, &pNV->m_sRefertoTestoTxt);
	sp.Execute("RefertoTestoHtml", pOV, &pOV->m_sRefertoTestoHtml, pNV, &pNV->m_sRefertoTestoHtml);
	sp.Execute("RefertoDataOra", pOV, &pOV->m_sRefertoDataOra, pNV, &pNV->m_sRefertoDataOra);
	sp.Execute("RefertoRedattore", pOV, &pOV->m_lRefertoRedattore, pNV, &pNV->m_lRefertoRedattore);
	sp.Execute("RefertoScaduto", pOV, &pOV->m_bRefertoScaduto, pNV, &pNV->m_bRefertoScaduto);
	sp.Execute("RefertoStato", pOV, &pOV->m_lRefertoStato, pNV, &pNV->m_lRefertoStato);

	sp.Execute("ChiusuraBloccataDaInteg", pOV, &pOV->m_bChiusuraBloccataDaIntegrazione, pNV, &pNV->m_bChiusuraBloccataDaIntegrazione);

	sp.Execute("LivelloUrgenza", pOV, &pOV->m_lLivelloUrgenza, pNV, &pNV->m_lLivelloUrgenza);
	sp.Execute("FrazioneEiezione", pOV, &pOV->m_lFrazioneEiezione, pNV, &pNV->m_lFrazioneEiezione);
	sp.Execute("IdProvenienzaNew", pOV, &pOV->m_lIdProvenienzaNew, pNV, &pNV->m_lIdProvenienzaNew);
	sp.Execute("STATOINVIOCENTRALEREFERTAZ", pOV, &pOV->m_lStatoInvioCentraleRefertaz, pNV, &pNV->m_lStatoInvioCentraleRefertaz);
	sp.Execute("STATOINVIOCONTROLLOQUALITA", pOV, &pOV->m_lStatoInvioControlloQualita, pNV, &pNV->m_lStatoInvioControlloQualita);

	sp.Execute("VERSIONEGRIDCL", pOV, &pOV->m_lVersioneGridCL, pNV, &pNV->m_lVersioneGridCL);

	sp.Execute("QUESITODIAGNOSTICO", pOV, &pOV->m_sQuesitoDiagnostico, pNV, &pNV->m_sQuesitoDiagnostico);
	sp.Execute("QUESITODIAGNOSTICOCODIFICATO", pOV, &pOV->m_sQuesitoDiagnosticoCodificato, pNV, &pNV->m_sQuesitoDiagnosticoCodificato);

	sp.Execute("IDULTIMACHECKLISTUSATA", pOV, &pOV->m_lIDUltimaChecklistUsata, pNV, &pNV->m_lIDUltimaChecklistUsata);

	sp.Execute("FCMASSIMA", pOV, &pOV->m_sFCMassima, pNV, &pNV->m_sFCMassima);
	sp.Execute("FCSUBMASSIMA", pOV, &pOV->m_sFCSubmassima, pNV, &pNV->m_sFCSubmassima);
	sp.Execute("IDPROTOCOLLOUSATO", pOV, &pOV->m_lIDProtocolloUsato, pNV, &pNV->m_lIDProtocolloUsato);

	sp.Execute("REFERTOCONIUGATOPRINCIPALE", pOV, &pOV->m_sRefertoConiugatoPrincipale, pNV, &pNV->m_sRefertoConiugatoPrincipale);
	sp.Execute("REFERTOCONIUGATOSECONDARIO", pOV, &pOV->m_sRefertoConiugatoSecondario, pNV, &pNV->m_sRefertoConiugatoSecondario);
	sp.Execute("REFERTOCONIUGATOALTRAUO", pOV, &pOV->m_bRefertoConiugatoAltraUO, pNV, &pNV->m_bRefertoConiugatoAltraUO);
	sp.Execute("REFERTOCONIUGATOIMPORTATO", pOV, &pOV->m_bRefertoConiugatoImportato, pNV, &pNV->m_bRefertoConiugatoImportato);

	sp.Execute("FLEURYTRASFERITO", pOV, &pOV->m_sFleuryTrasferito, pNV, &pNV->m_sFleuryTrasferito);
	sp.Execute("FLEURYENDPOINTREMOTO", pOV, &pOV->m_sFleuryEndpointRemoto, pNV, &pNV->m_sFleuryEndpointRemoto);

	sp.Execute("Eliminato", pOV, &pOV->m_bEliminato, pNV, &pNV->m_bEliminato);
	sp.Execute("UO", pOV, &pOV->m_lUO, pNV, &pNV->m_lUO);
	//Luiz - 13/05/2019 - P3 - Atualiza nome/sobrenome Médico - Inclui Médicos solicitantes
	sp.Execute("InvMedico2", pOV, &pOV->m_sInvMedico2, pNV, &pNV->m_sInvMedico2);
	sp.Execute("IdInvMedico2", pOV, &pOV->m_lInvMedico2, pNV, &pNV->m_lInvMedico2);
	sp.Execute("InvMedico3", pOV, &pOV->m_sInvMedico3, pNV, &pNV->m_sInvMedico3);
	sp.Execute("IdInvMedico3", pOV, &pOV->m_lInvMedico3, pNV, &pNV->m_lInvMedico3);
	sp.Execute("InvMedico4", pOV, &pOV->m_sInvMedico4, pNV, &pNV->m_sInvMedico4);
	sp.Execute("IdInvMedico4", pOV, &pOV->m_lInvMedico4, pNV, &pNV->m_lInvMedico4);
	//Gabriel - P3
	if (m_bColumnsP3)
	{
		sp.Execute("HyperLocked", pOV, &pOV->m_bHyperLocked, pNV, &pNV->m_bHyperLocked);
		sp.Execute("IdUtenteHyperLock", pOV, &pOV->m_lIdUtenteHyperLock, pNV, &pNV->m_lIdUtenteHyperLock);
		sp.Execute("DataOraHyperLock", pOV, &pOV->m_sDataOraHyperLock, pNV, &pNV->m_sDataOraHyperLock);
	}
	
	//Gabriel - TCP
	if (m_bColumnsTCP)
	{
		sp.Execute("STATOINVIOALTRAUNITA", pOV, &pOV->m_lStatoInvioAltraUnita, pNV, &pNV->m_lStatoInvioAltraUnita);
		sp.Execute("CODESAMECORRELATI", pOV, &pOV->m_sCodesameCorrelati, pNV, &pNV->m_sCodesameCorrelati);
		sp.Execute("REFERTOTESTOCORRELATIRTF", pOV, &pOV->m_sRefertoTestoCorrelatiRtf, pNV, &pNV->m_sRefertoTestoCorrelatiRtf);
		sp.Execute("REFERTOTESTOCORRELATITXT", pOV, &pOV->m_sRefertoTestoCorrelatiTxt, pNV, &pNV->m_sRefertoTestoCorrelatiTxt);
		sp.Execute("REFERTOTESTOCORRELATIHTML", pOV, &pOV->m_sRefertoTestoCorrelatiHtml, pNV, &pNV->m_sRefertoTestoCorrelatiHtml);
	}
		
}

BOOL CEsamiSet::DeleteRecordset(const CString &strCommento)
{
	ASSERT(IsOpen() && !IsEOF() && !IsBOF());

	BOOL bReturn = FALSE;
	if (EditRecordset("CEsamiSet::DeleteRecordset"))
	{
		m_bEliminato = TRUE;
		bReturn = UpdateRecordset("CEsamiSet::DeleteRecordset");

		// Sandro 16/05/2014 // cambio lo stato dell'eventuale relativo record nella worklist //
		if (bReturn)
		{
			CString sFilter;
			sFilter.Format("IDEsameIns=%li", m_lContatore);

			CExtOrdiniSet().SetStatoRichiesta(m_lContatore, LPC_STATO_NONEROGATA);			
		}
	}
	return bReturn;
}

CString CEsamiSet::SetBaseFilter(const CString &strFilter)
{
    CString strNewFilter = strFilter;
	strNewFilter.MakeUpper();

	CString strUO;
	strUO.Format("UO=%li", theApp.m_lUO);
	if (strNewFilter.IsEmpty())
	{
		strNewFilter = "RECORDSENZAACCESSO=0 AND " + strUO + " AND ELIMINATO=0";
	}
	else
	{
		if (strNewFilter.Find("RECORDSENZAACCESSO=") < 0)
			strNewFilter += " AND RECORDSENZAACCESSO=0";

		if (strNewFilter.Find("UO=") < 0)
			strNewFilter += " AND " + strUO;

		if (strNewFilter.Find("ELIMINATO=") < 0)
			strNewFilter += " AND ELIMINATO=0";
	}

	return CBaseSet::SetBaseFilter(strNewFilter);
}
		
BOOL CEsamiSet::UpdateRecordset(const CString &strCommento)
{
	//
	int nEditMode = m_nEditMode;

	//
	if (nEditMode == addnew)
	{
		m_lUO = theApp.m_lUO;
	}
	else
	{
		// Sandro 02/05/2013 // RAS 20130078 //

		if (theApp.m_bInterfacciaMetafora || (theApp.m_lInterfacciaPathox > 0))
		{
			CString sFilter;
			sFilter.Format("Contatore=%li", m_lContatore);

			CEsamiSet setEsamiTemp;
			setEsamiTemp.SetOpenFilter(sFilter);
			if (setEsamiTemp.OpenRecordset("CEsamiSet::UpdateRecordset"))
			{
				if (!setEsamiTemp.IsEOF())
				{
					if (m_lContatore == setEsamiTemp.m_lContatore)
					{
						if (!m_bUpdatingAPStato)
							m_lAPStato = setEsamiTemp.m_lAPStato;
						m_sAPMotivazioneRifiuto = setEsamiTemp.m_sAPMotivazioneRifiuto;
						m_sAPRispostaCodificata = setEsamiTemp.m_sAPRispostaCodificata;
						m_sAPRispostaLibera = setEsamiTemp.m_sAPRispostaLibera;
						m_sAPRefertoPDF = setEsamiTemp.m_sAPRefertoPDF;
						if (m_bWaitingForGroupNumber)
							m_sAPGroupNumber = setEsamiTemp.m_sAPGroupNumber;
					}
				}

				setEsamiTemp.CloseRecordset("CEsamiSet::UpdateRecordset");
			}
		}
	}

	//
	BOOL bReturn = CBaseSet::UpdateRecordset(strCommento);

	//
	if (bReturn)
	{
		if (nEditMode == addnew)
		{
			m_setEP.m_lIDEsame = GetLastAdd();
			m_setEM.m_lIDESAME = GetLastAdd();
			m_setRI.m_lIDEsame = GetLastAdd(); //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
		}

		m_setEP.UpdateRecordset(strCommento);
		m_setEM.UpdateRecordset(strCommento);
		m_setRI.UpdateRecordset(strCommento); //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
	}
	else
	{
		NoEditRecordset(strCommento);
	}

	//
	CPazientiSet().UpdateDataUltimoEsame(m_lPaziente);

	// Sandro 04/03/2013 // RAS 20130027 //
	if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury || theApp.m_bPersonalizzazioniBrasileSirio)
		((CMainFrame*)AfxGetMainWnd())->GetActiveDocument()->SetTitle(theApp.GetAppTitle(0));

	//
	return bReturn;
}

BOOL CEsamiSet::UpdateRecordsetAPStato(const CString &strCommento, BOOL waitingForGroupNumber)
{
	BOOL bReturn = FALSE;

	m_bUpdatingAPStato = TRUE;
	m_bWaitingForGroupNumber = waitingForGroupNumber;
	bReturn = UpdateRecordset(strCommento);
	m_bWaitingForGroupNumber = FALSE;
	m_bUpdatingAPStato = FALSE;

	return bReturn;
}

BOOL CEsamiSet::ResetVersionID()
{
	UINT iFieldsOld = m_nFields;
	m_nFields = 2;

	SetOpenFilter("IDVersione <> 1");
	if (OpenRecordset("CEsamiSet::ResetVersionID"))
	{
		while(!IsEOF())
		{
			if (EditRecordset("CEsamiSet::ResetVersionID"))
			{
				m_lIDVersione = 1;
				UpdateRecordset("CEsamiSet::ResetVersionID");
			}

			MoveNext();
		}

		CloseRecordset("CEsamiSet::ResetVersionID");
	}

	m_nFields = iFieldsOld;
	return TRUE;
}

CString CEsamiSet::GetDataEsame(long lIDEsame)
{
	CString strReturn = "";

	CString strFilter;
	strFilter.Format("Contatore=%li", lIDEsame);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CEsamiSet::GetDataEsame"))
	{
		if (!IsEOF() && !IsFieldNull(&m_lData) && (m_lData > 0))
			strReturn = CCustomDate(m_lData).GetDate("%d/%m/%Y");

		CloseRecordset("CEsamiSet::GetDataEsame");
	}

	return strReturn;
}

long CEsamiSet::GetTipoEsame(long lContatore)
{
	long lReturn = 0;

	CString strFilter;
	strFilter.Format("Contatore=%li", lContatore);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CEsamiSet::GetTipoEsame"))
	{
		if (!IsEOF())
			lReturn = m_lIDEsame;

		CloseRecordset("CEsamiSet::GetTipoEsame");
	}

	return lReturn;
}

CString CEsamiSet::GetNumeroProtocolloINPS(long lContatore)
{
	CString sReturn = "";

	CString strFilter;
	strFilter.Format("Contatore=%li", lContatore);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CEsamiSet::GetNumeroProtocolloINPS"))
	{
		if (!IsEOF())
			sReturn = m_sInpsNumeroProtocollo;

		CloseRecordset("CEsamiSet::GetNumeroProtocolloINPS");
	}

	return sReturn;
}

BOOL CEsamiSet::EsameSbloccabile(long lContatore)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("Contatore=%li", lContatore);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CEsamiSet::EsameSbloccabile"))
	{
		if (!IsEOF())
			bReturn = !m_bNonSbloccabile;

		CloseRecordset("CEsamiSet::EsameSbloccabile");
	}

	return bReturn;
}

BOOL CEsamiSet::ConvalidaEsame(CString sTime)
{
	BOOL bReturn = FALSE;

	if (EditRecordset("CEsamiSet::ConvalidaEsame"))
	{
		m_bLocked = TRUE;

		/*
		if (theApp.m_bFirmaDigitale) // Davide - Firma digitale
			m_bFirmato = TRUE;
		*/

		//Julio 22/10/2018
		if (theApp.m_bImpersonated)		
			m_lIdUtenteLock = theApp.m_lImpersonatedID;					
		else
			m_lIdUtenteLock = GetUserIDForLockSuperlock();
		//

		m_sDataOraLock = sTime;

		CCustomDate customStart = CCustomDate(m_lData);
		COleDateTime start = COleDateTime(customStart.GetYear(), customStart.GetMonth(), customStart.GetDay(), customStart.GetHour(), customStart.GetMinute(), 0);
		COleDateTime stop = COleDateTime(atoi(m_sDataOraLock.Left(4)),
											atoi(m_sDataOraLock.Mid(4,2)),
											atoi(m_sDataOraLock.Mid(6,2)),
											atoi(m_sDataOraLock.Mid(8,2)),
											atoi(m_sDataOraLock.Mid(10,2)),
											0); // Non serve gestire i secondi qui perchè dataesame non li gestisce
		COleDateTimeSpan timeDiff = stop - start;

		CString result;
		result.Format("%li:%li:%li", timeDiff.GetDays(), timeDiff.GetHours(), timeDiff.GetMinutes());
		m_sTempoConvalida = result;

		if (UpdateRecordset("CEsamiSet::ConvalidaEsame"))
		{
			// inserisco una riga nella tabella EXT_ESAMI_CONVALIDATI //
			CEsamiConvalidatiSet().InserisciRecord(m_lContatore, m_lIdUtenteLock);

			//Gabriel BUG 6225 - Lista DO
			if (theApp.m_bAtivaListaDO)
			{
				CRiconvocazioneSet riconvocazioneSet;
				riconvocazioneSet.SetEliminato(riconvocazioneSet.GetIdFromIdEsame(m_lContatore));
			}
			
			bReturn = TRUE;
		}
	}
	ImpersonateStop(m_lContatore, m_lPaziente); //Julio 22/10/2018
	return bReturn;
}

BOOL CEsamiSet::AnnullaConvalidaEsame()
{
	if (EditRecordset("CEsamiSet::ConvalidaEsame"))
	{
		m_bLocked = FALSE;
		m_lIdUtenteLock = 0;
		m_sDataOraLock = "";
		m_bInviatoScreening = FALSE;
		m_sTempoConvalida = "";
		UpdateRecordset("CEsamiSet::ConvalidaEsame");
	}

	return TRUE;
}

BOOL CEsamiSet::ChiudiEsame(CString sCloseTime, CRefertoForm* pRefertoForm)
{
	if (EditRecordset("CEsamiSet::ChiudiEsame"))
	{
		m_bSuperLocked = TRUE;

		if (theApp.m_enumFirmaDigitale != CEndoxApp::sign_disabled)
			m_bFirmato = TRUE;

		m_lIdUtenteSuperLock = GetUserIDForLockSuperlock();

		// Sandro 06/12/2012 // premendo il tasto "stampa referto" nella toolbar esame con la firma digitale attiva, si arrivava qui con sCloseTime vuoto //
		if (sCloseTime.IsEmpty())
		{
			CTime now = CTime::GetCurrentTime();
			sCloseTime = now.Format("%Y%m%d%H%M%S");
		}

		m_sDataOraSuperLock = sCloseTime;

		if (m_sDataOraSuperLockPrimo.IsEmpty())
			m_sDataOraSuperLockPrimo = m_sDataOraSuperLock;

		CCustomDate customStart = CCustomDate(m_lData);
		COleDateTime start = COleDateTime(customStart.GetYear(), customStart.GetMonth(), customStart.GetDay(), customStart.GetHour(), customStart.GetMinute(), 0);
		COleDateTime stop = COleDateTime(atoi(m_sDataOraSuperLock.Left(4)),
											atoi(m_sDataOraSuperLock.Mid(4,2)),
											atoi(m_sDataOraSuperLock.Mid(6,2)),
											atoi(m_sDataOraSuperLock.Mid(8,2)),
											atoi(m_sDataOraSuperLock.Mid(10,2)),
											0); // non serve gestire i secondi perchè dataesame non li gestisce
		COleDateTimeSpan timeDiff = stop - start;

		CString result;
		result.Format("%li:%li:%li", timeDiff.GetDays(), timeDiff.GetHours(), timeDiff.GetMinutes());
		m_sTempoChiusura = result;

		// Luiz - 26/02/2019 - P3 - Fleury, realiza qualidade no endoxserver - fechamento status exame
		if (!theApp.m_bPersonalizzazioniBrasileFleury)
		{
			// Sandro 12/07/2016 //
			switch (theApp.m_lControlloQualitaPercentuale)
			{
			case 0:
			{
				// nessun controllo qualità //
				m_lStatoInvioControlloQualita = StatoInvioControlloQualita::cqNonInviare;
				break;
			}
			case 100:
			{
				// vanno tutti al controllo qualità //
				m_lStatoInvioControlloQualita = StatoInvioControlloQualita::cqDaInviare;
				break;
			}
			default:
			{
				// faccio calcolo probabilistico :-) //
				srand((unsigned)time(NULL));
				rand(); rand(); rand(); rand();

				int nRand = rand();
				double dRand = (((double)nRand) * 100.0) / ((double)RAND_MAX);
				long lRand = (long)dRand;

				if (lRand <= theApp.m_lControlloQualitaPercentuale)
					m_lStatoInvioControlloQualita = StatoInvioControlloQualita::cqDaInviare;
				else
					m_lStatoInvioControlloQualita = StatoInvioControlloQualita::cqNonInviare;

				break;
			}
			}

			if (m_lStatoInvioControlloQualita == StatoInvioControlloQualita::cqDaInviare)
			{
				// inserisco una riga nella tabella EXT_ESAMI_CONTROLLOQUALITA //
				long userId;
				AMLogin_GetUserID(&userId);
				CEsamiControlloQualitaSet().InserisciRecord(m_lContatore, userId);
			}
		}
		// Sandro 01/03/2017 //

		if ((theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury) && (pRefertoForm != NULL))
		{
			long lSelStart = pRefertoForm->m_ctrlTextControl.GetSelStart();
			long lSelLength = pRefertoForm->m_ctrlTextControl.GetSelLength();

			pRefertoForm->m_ctrlTextControl.SetSelStart(0);
			pRefertoForm->m_ctrlTextControl.SetSelLength(-1);

			//m_sRefertoTestoHtml = pRefertoForm->m_ctrlTextControl.GetHTMLSelText();

			pRefertoForm->m_ctrlTextControl.SetSelStart(lSelStart);
			pRefertoForm->m_ctrlTextControl.SetSelLength(lSelLength);
		}

		//

		UpdateRecordset("CEsamiSet::ChiudiEsame");

		// 31/10/2013 Simone
		// Flaggo la richiesta come refertata sulla worklist se esiste
		CExtOrdiniSet().SetStatoRichiesta(m_lContatore, LPC_STATO_REFERTATA);		
	}

	////Julio BUG 3456 - Contingencia
	//if (theApp.m_bContingencia && CheckIfMainDBIsOnline())
	//{
	//	AfxMessageBox(theApp.GetMessageString(IDS_CONTINGENZA_MESSAGE));
	//	AfxGetMainWnd()->PostMessage(WM_CLOSE);
	//}

	//Gabriel BUG 6225 - Lista DO
	if (theApp.m_bAtivaListaDO)
	{
		CRiconvocazioneSet riconvocazioneSet;
		riconvocazioneSet.SetEliminato(riconvocazioneSet.GetIdFromIdEsame(m_lContatore));
	}
	
	return TRUE;
}

BOOL CEsamiSet::ChiudiEsameIntegrato(long lIDEsame, CString sCloseTime)
{
	CString sFilter;
	sFilter.Format("Contatore=%li", lIDEsame);

	SetBaseFilter("(UO=0 OR UO>0)");
	SetOpenFilter(sFilter);
	if (OpenRecordset("CEsamiSet::ChiudiEsameIntegrato"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CEsamiSet::ChiudiEsameIntegrato"))
			{
				m_bSuperLocked = TRUE;

				if (theApp.m_enumFirmaDigitale != CEndoxApp::sign_disabled)
					m_bFirmato = TRUE;

				//m_lIdUtenteSuperLock = GetUserIDForLockSuperlock();
				if (theApp.m_bImpersonated)
					m_lIdUtenteSuperLock = theApp.m_lImpersonatedID;
				else
					m_lIdUtenteSuperLock = GetUserIDForLockSuperlock();
				//

				// Sandro 06/12/2012 // premendo il tasto "stampa referto" nella toolbar esame con la firma digitale attiva, si arrivava qui con sCloseTime vuoto //
				if (sCloseTime.IsEmpty())
				{
					CTime now = CTime::GetCurrentTime();
					sCloseTime = now.Format("%Y%m%d%H%M%S");
				}

				m_sDataOraSuperLock = sCloseTime;

				if (m_sDataOraSuperLockPrimo.IsEmpty())
					m_sDataOraSuperLockPrimo = m_sDataOraSuperLock;

				CCustomDate customStart = CCustomDate(m_lData);
				COleDateTime start = COleDateTime(customStart.GetYear(), customStart.GetMonth(), customStart.GetDay(), customStart.GetHour(), customStart.GetMinute(), 0);
				COleDateTime stop = COleDateTime(atoi(m_sDataOraSuperLock.Left(4)),
					atoi(m_sDataOraSuperLock.Mid(4, 2)),
					atoi(m_sDataOraSuperLock.Mid(6, 2)),
					atoi(m_sDataOraSuperLock.Mid(8, 2)),
					atoi(m_sDataOraSuperLock.Mid(10, 2)),
					0); // non serve gestire i secondi perchè dataesame non li gestisce
				COleDateTimeSpan timeDiff = stop - start;

				m_sTempoChiusura.Format("%li:%li:%li", timeDiff.GetDays(), timeDiff.GetHours(), timeDiff.GetMinutes());

				// Sandro 23/07/2015 //

				CTime DataAttuale = CTime::GetCurrentTime();

				//Gabriel - TCP
				if (theApp.m_bAtivaTCP && !m_sCodesameCorrelati.IsEmpty())
				{
					CString sFilterConiugato;
					sFilterConiugato.Format("CODESAME='%s'", m_sCodesameCorrelati);

					CEsamiSet setEsameConiugato;
					setEsameConiugato.SetBaseFilter("(UO=0 OR UO>0)");
					setEsameConiugato.SetOpenFilter(sFilterConiugato);

					if (setEsameConiugato.OpenRecordset("CEsamiView::ChiudiEsame"))
					{
						if (!setEsameConiugato.IsEOF())
						{
							if (setEsameConiugato.EditRecordset("CEsamiView::ChiudiEsame"))
							{
								setEsameConiugato.m_sRefertoTestoCorrelatiRtf = m_sRefertoTestoRtf;
								setEsameConiugato.m_sRefertoTestoCorrelatiTxt = m_sRefertoTestoTxt;
								setEsameConiugato.m_sRefertoTestoCorrelatiHtml = m_sRefertoTestoHtml;

								setEsameConiugato.UpdateRecordset("CEsamiView::ChiudiEsame");
							}

							setEsameConiugato.CloseRecordset("CEsamiView::ChiudiEsame");
						}
					}
				}

				//Gabriel - TCP FIX
				if (!theApp.m_bAtivaTCP || m_sCodesameCorrelati.IsEmpty())
				{
					m_sRefertoTestoRtf = theApp.m_sRefertoIntegratoRtf;
					m_sRefertoTestoTxt = theApp.m_sRefertoIntegratoTxt;
				}

				// m_sRefertoTestoHtml = ;
				m_sRefertoDataOra = DataAttuale.Format("%Y%m%d%H%M%S");
				AMLogin_GetUserID(&m_lRefertoRedattore);
				m_bRefertoScaduto = FALSE;

				if (!m_bLocked) // Julio - Bug 4268 equivoco assinar e salvar em Laudo Conjugado
				{
					// Luiz - 06/02/2019 - P3 - Itens conjugados devem ter o botão Salvar valorizado
					m_bLocked = TRUE;
					m_lIdUtenteLock = m_lIdUtenteSuperLock;
					m_sDataOraLock = m_sDataOraSuperLock;
				}

				if (UpdateRecordset("CEsamiSet::ChiudiEsameIntegrato"))
				{
					// 31/10/2013 Simone
					// Flaggo la richiesta come refertata sulla worklist se esiste
					CExtOrdiniSet().SetStatoRichiesta(m_lContatore, LPC_STATO_REFERTATA);
				}
			}
		}

		CloseRecordset("CEsamiSet::ChiudiEsameIntegrato");
	}

	return TRUE;
}

BOOL CEsamiSet::FlaggaEsameInviareCentraleRefertazione()
{
	if (EditRecordset("CEsamiSet::FlaggaEsameInviareCentraleRefertazione"))
	{
		m_bSuperLocked = TRUE;

		m_lIdUtenteSuperLock = GetUserIDForLockSuperlock();

		m_sDataOraSuperLock = CTime::GetCurrentTime().Format("%Y%m%d%H%M%S");

		if (m_sDataOraSuperLockPrimo.IsEmpty())
			m_sDataOraSuperLockPrimo = m_sDataOraSuperLock;

		CCustomDate customStart = CCustomDate(m_lData);
		COleDateTime start = COleDateTime(customStart.GetYear(), customStart.GetMonth(), customStart.GetDay(), customStart.GetHour(), customStart.GetMinute(), 0);
		COleDateTime stop = COleDateTime(atoi(m_sDataOraSuperLock.Left(4)),
			atoi(m_sDataOraSuperLock.Mid(4, 2)),
			atoi(m_sDataOraSuperLock.Mid(6, 2)),
			atoi(m_sDataOraSuperLock.Mid(8, 2)),
			atoi(m_sDataOraSuperLock.Mid(10, 2)),
			0); // non serve gestire i secondi perchè dataesame non li gestisce
		COleDateTimeSpan timeDiff = stop - start;

		CString result;
		result.Format("%02li:%02li:%02li", timeDiff.GetDays(), timeDiff.GetHours(), timeDiff.GetMinutes());
		m_sTempoChiusura = result;

		m_lStatoInvioCentraleRefertaz = StatoInvioCentraleRefertazione::crDaInviare;

		UpdateRecordset("CEsamiSet::FlaggaEsameInviareCentraleRefertazione");

		// Flaggo la richiesta come refertata sulla worklist se esiste
		CExtOrdiniSet().SetStatoRichiesta(m_lContatore, LPC_STATO_REFERTATA);
	}

	return TRUE;
}

BOOL CEsamiSet::SbloccaEsame(CWnd* pParent)
{
	BOOL bContinua = TRUE;

	// Sandro 20/01/2014 // RAS 20130207 // chiedo subito il motivo per cui sto riaprendo l'esame //

	CPdfManager pmTemp;
	CPdfList plTemp;

	CFirmaMotivoSostituzioneDlg dlg(pParent);
	if (theApp.m_enumFirmaDigitale != CEndoxApp::sign_disabled)
	{
		if (pmTemp.GetPdf(m_lContatore, &plTemp))
		{
			if (plTemp.GetCount() > 0)
			{
				POSITION pos = plTemp.GetHeadPosition();
				while(pos != NULL)
				{
					PDF pdfTemp = plTemp.GetAt(pos);

					if (!pdfTemp.bSospeso && !pdfTemp.bAnnullato && !pdfTemp.bEliminato && pdfTemp.bFirmato && (pdfTemp.ptTipo == pdftype_report))
					{
						bContinua = (dlg.DoModal() == IDOK);
						break;
					}

					plTemp.GetNext(pos);
				}
			}
		}
	}

	//

	if (bContinua)
	{
		if (EditRecordset("CEsamiSet::AnnullaChiusuraEsame"))
		{
			m_bSuperLocked = FALSE;
			m_bFirmato = FALSE; // Davide - Firma digitale
			m_lIdUtenteSuperLock = 0;
			m_sDataOraSuperLock = "";
			m_bInviatoScreening = FALSE;
			m_sTempoChiusura = "";
			if (m_lStatoInvioCentraleRefertaz != StatoInvioCentraleRefertazione::crInviato)
				m_lStatoInvioCentraleRefertaz = StatoInvioCentraleRefertazione::crNonInviare;
			if (m_lStatoInvioControlloQualita != StatoInvioControlloQualita::cqInviato)
				m_lStatoInvioControlloQualita = StatoInvioControlloQualita::cqNonInviare;
			if (UpdateRecordset("CEsamiSet::AnnullaChiusuraEsame"))
			{
				CEsamiRefertazioneRemotaSet().EliminaRecord(m_lContatore, "CEsamiSet::AnnullaChiusuraEsame");

				if (theApp.m_enumFirmaDigitale != CEndoxApp::sign_disabled)
				{
					// Sandro 20/01/2014 // RAS 20130207 // sospendo tutti i documenti firmati //

					POSITION pos = plTemp.GetHeadPosition();
					while(pos != NULL)
					{
						PDF pdfTemp = plTemp.GetAt(pos);

						if (!pdfTemp.bSospeso && !pdfTemp.bAnnullato && !pdfTemp.bEliminato && pdfTemp.bFirmato && (pdfTemp.ptTipo == pdftype_report))
							pmTemp.SetPdfSospesoMotivo(pdfTemp.lID, m_lPaziente, m_lContatore, theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, dlg.GetMotivo());

						plTemp.GetNext(pos);
					}
				}
			}

			// 31/10/2013 Simone
			// Flaggo la richiesta come refertata sulla worklist se esiste

			CExtOrdiniSet().SetStatoRichiesta(m_lContatore, LPC_STATO_INCORSO);

			// Davide - Sirio Libanes
			long lUserID = 0;
			AMLogin_GetUserID(&lUserID);
			CEsamiSbloccatiSet().InserisciRecord(m_lContatore, lUserID);
		}
	}

	return TRUE;
}

BOOL CEsamiSet::AnnullaChiusura(CWnd* pParent, const long lIDEsameChiuso)
{
	BOOL bContinua = TRUE;

	if (EditRecordset("CEsamiSet::AnnullaChiusuraEsame"))
	{
		m_bSuperLocked = FALSE;
		m_bFirmato = FALSE; // Davide - Firma digitale
		m_lIdUtenteSuperLock = 0;
		m_sDataOraSuperLock = "";
		m_bInviatoScreening = FALSE;
		m_sTempoChiusura = "";
		UpdateRecordset("CEsamiSet::AnnullaChiusuraEsame");
		
		// 31/10/2013 Simone
		// Flaggo la richiesta come refertata sulla worklist se esiste
		CExtOrdiniSet().SetStatoRichiesta(m_lContatore, LPC_STATO_INCORSO);

	}

	//Rimuovo la riga di chiusura e il pdf
	int pdfId = CEsamiChiusiSet().GetPdfIdFromId(lIDEsameChiuso);

	//Annulla chiusura esame
	CEsamiChiusiSet().RemoveFromExam(lIDEsameChiuso);

	//Cancello il pdf
	CPdfManager().SetPdfEliminato(pdfId, m_lPaziente, m_lContatore, theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer);

	return TRUE;
}

BOOL CEsamiSet::IsRefertoUpdatable()
{
	if (IsOpen())
	{
		if (theApp.m_nProgramMode & ADD_RECORD_ESAMI)
			return TRUE; // sto aggiungendo un nuovo esame //
	
		if (!IsEOF())
		{
			if (!m_bRefertoScaduto)
			{
				if (theApp.m_lBloccoReferto > 0)
				{
					if (m_sRefertoDataOra.IsEmpty())
						return TRUE;

					CTime tDataReferto(atoi(m_sRefertoDataOra.Left(4)), atoi(m_sRefertoDataOra.Mid(4, 2)), atoi(m_sRefertoDataOra.Mid(6, 2)), atoi(m_sRefertoDataOra.Mid(8, 2)), atoi(m_sRefertoDataOra.Mid(10, 2)), atoi(m_sRefertoDataOra.Mid(12, 2)));
					CTime tDataAttuale = CTime::GetCurrentTime();
					CTimeSpan tsDataDiff = tDataAttuale - tDataReferto;

					if ((tsDataDiff.GetTotalHours() < 0) || (tsDataDiff.GetTotalHours() >= theApp.m_lBloccoReferto))
					{
						// non posso più modificarlo quindi lo segno come scaduto //

						BOOL bEsamiModify = theApp.m_nProgramMode & ADD_RECORD_ESAMI || theApp.m_nProgramMode & MODIFY_RECORD_ESAMI;

						BOOL bDoUpdate = FALSE;
						if (!bEsamiModify) // (m_nEditMode == CRecordset::noMode)
							bDoUpdate = EditRecordset("CEsamiSet::IsRefertoUpdatable");

						m_bRefertoScaduto = TRUE;

						if (bDoUpdate)
							UpdateRecordset("CEsamiSet::IsRefertoUpdatable");

						switch (theApp.m_lModificaReferto)
						{
							case 0:
							{
								return FALSE;
							}
							case 1: // modificabile solo dal redattore //
							{
								long lCurUser;
								AMLogin_GetUserID(&lCurUser);
								return(lCurUser == m_lRefertoRedattore);
							}
							case 2: // modificabile solo dall'amministratore //
							{
								long lCurUser;
								AMLogin_GetUserID(&lCurUser);
								return(theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_01);
							}
							case 3: // modificabile dal redattore o dall'amministratore //
							{
								long lCurUser;
								AMLogin_GetUserID(&lCurUser);
								return((lCurUser == m_lRefertoRedattore) || (theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_01));
							}
							default:
							{
								ASSERT(FALSE);
								return FALSE;
							}
						}
					}
				}
			}

			switch (theApp.m_lModificaReferto)
			{
				case 0:
				{
					return (!m_bRefertoScaduto);
				}
				case 1: // modificabile solo dal redattore //
				{
					long lCurUser;
					AMLogin_GetUserID(&lCurUser);
					return((!m_bRefertoScaduto) || (lCurUser == m_lRefertoRedattore));
				}
				case 2: // modificabile solo dall'amministratore //
				{
					long lCurUser;
					AMLogin_GetUserID(&lCurUser);
					return((!m_bRefertoScaduto) || (theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_01));
				}
				case 3: // modificabile dal redattore o dall'amministratore //
				{
					long lCurUser;
					AMLogin_GetUserID(&lCurUser);
					return((!m_bRefertoScaduto) || (lCurUser == m_lRefertoRedattore) || (theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_01));
				}
				default:
				{
					ASSERT(FALSE);
					return FALSE;
				}
			}
		}
	}

	return FALSE;
}

void CEsamiSet::SetReferto(const CString &sRefertoRtf, const CString &sRefertoTxt, const CString &sRefertoHtml)
{
	if (IsRefertoUpdatable())
	{
		CTime tDataAttuale = CTime::GetCurrentTime();

		if (IsOpen())
		{
			if (!IsEOF() || (theApp.m_nProgramMode & ADD_RECORD_ESAMI)) // se sto inserendo il primo esame ad un paziente nuovo sono in EOF //
			{
				BOOL bEsamiModify = theApp.m_nProgramMode & ADD_RECORD_ESAMI || theApp.m_nProgramMode & MODIFY_RECORD_ESAMI;

				BOOL bDoUpdate = FALSE;
				if (!bEsamiModify)
					bDoUpdate = EditRecordset("CEsamiSet::SetReferto");

				m_sRefertoTestoRtf = sRefertoRtf;
				m_sRefertoTestoTxt = sRefertoTxt;
				m_sRefertoTestoHtml = sRefertoHtml;
				m_sRefertoDataOra = tDataAttuale.Format("%Y%m%d%H%M%S");
				AMLogin_GetUserID(&m_lRefertoRedattore);
				m_bRefertoScaduto = FALSE;

				//

				// m_sAPDescrizioneRichiesta = sAPDescrizioneRichiesta;
				m_sConclusioni = "";

				//

				if (bDoUpdate)
					UpdateRecordset("CEsamiSet::SetReferto");
			}
		}
	}
}

BOOL CEsamiSet::GetChiusuraBloccataDaIntegrazione(long lContatore)
{
	BOOL bReturn = FALSE;

	CString strFilter;
	strFilter.Format("Contatore=%li", lContatore);

	SetOpenFilter(strFilter);
	if (OpenRecordset("CEsamiSet::GetChiusuraBloccataDaIntegrazione"))
	{
		if (!IsEOF())
			bReturn = m_bChiusuraBloccataDaIntegrazione;

		CloseRecordset("CEsamiSet::GetChiusuraBloccataDaIntegrazione");
	}

	return bReturn;
}

BOOL CEsamiSet::SetChiusuraBloccataDaIntegrazione()
{
	if (EditRecordset("CEsamiSet::SetChiusuraBloccataDaIntegrazione"))
	{
		m_bChiusuraBloccataDaIntegrazione = TRUE;
		UpdateRecordset("CEsamiSet::SetChiusuraBloccataDaIntegrazione");
	}

	return TRUE;
}

void CEsamiSet::SetIDProtocolloUsato(long lContatore, long lIDProtocolloUsato)
{
	if (lContatore > 0)
	{
		CString sFilter;
		sFilter.Format("CONTATORE=%li", lContatore);

		SetOpenFilter(sFilter);
		if (OpenRecordset("CEsamiSet::SetIDProtocolloUsato"))
		{
			if (!IsEOF())
			{
				if (EditRecordset("CEsamiSet::SetIDProtocolloUsato"))
				{
					m_lIDProtocolloUsato = lIDProtocolloUsato;
					UpdateRecordset("CEsamiSet::SetIDProtocolloUsato");
				}
			}

			CloseRecordset("CEsamiSet::SetIDProtocolloUsato");
		}
	}
}

BOOL CEsamiSet::IsConiugatoPrincipale(long lID)
{
	BOOL bReturn = FALSE;

	CString sFilter;
	sFilter.Format("CONTATORE=%li", lID);
	SetOpenFilter(sFilter);
	if (OpenRecordset("CEsamiSet::IsConiugatoPrincipale"))
	{
		if(!IsEOF())
			if (m_sRefertoConiugatoPrincipale.GetLength() > 0)
				bReturn = (m_sCodEsame.CompareNoCase(m_sRefertoConiugatoPrincipale) == 0);

		CloseRecordset("CEsamiSet::IsConiugatoPrincipale");
	}

	return bReturn;
}

BOOL CEsamiSet::IsConiugatoSecondario(long lID)
{
	BOOL bReturn = FALSE;

	CString sFilter;
	sFilter.Format("CONTATORE=%li", lID);
	SetOpenFilter(sFilter);
	if (OpenRecordset("CEsamiSet::IsConiugatoSecondario"))
	{
		if (!IsEOF())
			if (m_sRefertoConiugatoSecondario.GetLength() > 0)
				bReturn = (m_sCodEsame.CompareNoCase(m_sRefertoConiugatoSecondario) == 0);

		CloseRecordset("CEsamiSet::IsConiugatoSecondario");
	}

	return bReturn;
}

BOOL CEsamiSet::IsConiugatoPrincipaleSecondario(CString sFichaItem)
{
	BOOL bReturn = FALSE;

	sFichaItem.Replace("'", "''");
	sFichaItem.Trim();

	if (!sFichaItem.IsEmpty())
	{
		CString sFilter;
		sFilter.Format("(REFERTOCONIUGATOPRINCIPALE LIKE '%s' OR REFERTOCONIUGATOSECONDARIO LIKE '%s')", sFichaItem, sFichaItem);

		SetOpenFilter(sFilter);
		if (OpenRecordset("CEsamiSet::IsConiugatoPrincipaleSecondario"))
		{
			bReturn = !IsEOF();
			CloseRecordset("CEsamiSet::IsConiugatoPrincipaleSecondario");
		}
	}
	return bReturn;
}

void CEsamiSet::SetConiugatoPrincipaleSecondario(CString sFichaItemPrincipale, CString sFichaItemSecondario, BOOL bAltraUO)
{
	CString sFilter;
	SetBaseFilter("(UO=0 OR UO>0)");

	sFichaItemPrincipale.Replace("'", "''");
	sFichaItemPrincipale.Trim();

	sFichaItemSecondario.Replace("'", "''");
	sFichaItemSecondario.Trim();

	//

	sFilter.Format("CODESAME LIKE '%s'", sFichaItemPrincipale);
	SetOpenFilter(sFilter);
	if (OpenRecordset("CEsamiSet::SetConiugatoPrincipaleSecondario"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CEsamiSet::SetConiugatoPrincipaleSecondario"))
			{
				m_sRefertoConiugatoPrincipale = sFichaItemPrincipale;
				m_sRefertoConiugatoSecondario = sFichaItemSecondario;
				m_bRefertoConiugatoAltraUO = bAltraUO;

				UpdateRecordset("CEsamiSet::SetConiugatoPrincipaleSecondario");
			}
		}

		CloseRecordset("CEsamiSet::SetConiugatoPrincipaleSecondario");
	}

	//

	sFilter.Format("CODESAME LIKE '%s'", sFichaItemSecondario);
	SetOpenFilter(sFilter);
	if (OpenRecordset("CEsamiSet::SetConiugatoPrincipaleSecondario"))
	{
		if (!IsEOF())
		{
			if (EditRecordset("CEsamiSet::SetConiugatoPrincipaleSecondario"))
			{
				m_sRefertoConiugatoPrincipale = sFichaItemPrincipale;
				m_sRefertoConiugatoSecondario = sFichaItemSecondario;
				m_bRefertoConiugatoAltraUO = bAltraUO;

				// Sandro 18/11/2016 // nel caso che siamo nella stessa UO il "secondario" lo imposto come già chiuso dall'utente che sta facendo la coniugazione //
				if (!bAltraUO)
				{
					m_bLocked = TRUE;
					m_lIdUtenteLock = GetUserIDForLockSuperlock();
					m_sDataOraLock = CTime::GetCurrentTime().Format("%Y%m%d%H%M%S");
				}

				//
				UpdateRecordset("CEsamiSet::SetConiugatoPrincipaleSecondario");
			}
		}

		CloseRecordset("CEsamiSet::SetConiugatoPrincipaleSecondario");
	}
}

void CEsamiSet::Desconjugar(CString sFichaItemPrincipale, CString sFichaItemSecondario)
{
	CString sFilter;
	SetBaseFilter("(UO=0 OR UO>0)");	

	//
	// Marvel BUG 4090 - desconjugação de laudos (tela principal do Tesicapture)
	CEsamiSet esamiPrimario;
	sFilter.Format("CODESAME LIKE '%s'", sFichaItemPrincipale);
	esamiPrimario.SetOpenFilter(sFilter);
	if (esamiPrimario.OpenRecordset("CEsamiSet::Desconjugar"))
	{
		if (!esamiPrimario.IsEOF())
		{
			if (esamiPrimario.EditRecordset("CEsamiSet::Desconjugar"))
			{
				esamiPrimario.m_sRefertoConiugatoPrincipale = "";
				esamiPrimario.m_sRefertoConiugatoSecondario = "";
				esamiPrimario.m_bRefertoConiugatoAltraUO = FALSE;

				esamiPrimario.UpdateRecordset("CEsamiSet::Desconjugar");
			}			
		}

		esamiPrimario.CloseRecordset("CEsamiSet::Desconjugar");
	}

	//
	// Marvel BUG 4090 - desconjugação de laudos (tela principal do Tesicapture)
	CEsamiSet esamiSecundario;
	sFilter.Format("CODESAME LIKE '%s'", sFichaItemSecondario);
	esamiSecundario.SetOpenFilter(sFilter);
	if (esamiSecundario.OpenRecordset("CEsamiSet::Desconjugar"))
	{
		if (!esamiSecundario.IsEOF())
		{
			if (esamiSecundario.EditRecordset("CEsamiSet::Desconjugar"))
			{
				esamiSecundario.m_sRefertoConiugatoPrincipale = "";
				esamiSecundario.m_sRefertoConiugatoSecondario = "";
				esamiSecundario.m_bRefertoConiugatoAltraUO = FALSE;
								
				esamiSecundario.UpdateRecordset("CEsamiSet::Desconjugar");
			}
		}

		esamiSecundario.CloseRecordset("CEsamiSet::Desconjugar");
	}
}
//Gabriel - P3
void CEsamiSet::ProtocoloXXI(CString sTime)
{
	if (EditRecordset("CEsamiSet::ProtocoloXXI"))
	{
		// Sandro 06/12/2012 // premendo il tasto "stampa referto" nella toolbar esame con la firma digitale attiva, si arrivava qui con sCloseTime vuoto //
		if (sTime.IsEmpty())
		{
			CTime now = CTime::GetCurrentTime();
			sTime = now.Format("%Y%m%d%H%M%S");
		}

		m_sDataOraHyperLock = sTime;
		m_bHyperLocked = TRUE;
		m_lIdUtenteHyperLock = GetUserIDForLockSuperlock();

		UpdateRecordset("CEsamiSet::ProtocoloXXI");
	}
}

BOOL CEsamiSet::AnnullaProtocoloXXI()
{
	if (EditRecordset("CEsamiSet::AnnullaProtocoloXXI"))
	{
		m_bHyperLocked = FALSE;
		m_lIdUtenteHyperLock = 0;
		m_sDataOraHyperLock = "";
		UpdateRecordset("CEsamiSet::AnnullaProtocoloXXI");
	}

	return TRUE;
}

void CEsamiSet::GetMediciRichiedente(CString& sMedico, long& lArrayCount)
{
	CString sFilter;
	lArrayCount = 0;

	CEsamiSet esamiSet;
	sFilter.Format("CONTATORE = %li", m_lContatore);
	esamiSet.SetOpenFilter(sFilter);

	if (esamiSet.OpenRecordset("CEsamiSet::GetMediciRichiedente"))
	{
		if (!esamiSet.IsEOF())
		{
			if (!esamiSet.m_sInvMedico.IsEmpty())
			{
				sMedico += m_sInvMedico + "|";
				lArrayCount++;
			}
			if (!esamiSet.m_sInvMedico2.IsEmpty())
			{
				sMedico += m_sInvMedico2 + "|";
				lArrayCount++;
			}
			if (!esamiSet.m_sInvMedico3.IsEmpty())
			{
				sMedico += m_sInvMedico3 + "|";
				lArrayCount++;
			}
			if (!esamiSet.m_sInvMedico4.IsEmpty())
			{
				sMedico += m_sInvMedico4 + "|";
				lArrayCount++;
			}
		}

		esamiSet.CloseRecordset("CEsamiSet::GetMediciRichiedente");
	}
}

//Gabriel - TCP
BOOL CEsamiSet::FlaggaEsameInviaAltraUnita()
{
	if (EditRecordset("CEsamiSet::FlaggaEsameInviaAltraUnita"))
	{
		m_bSuperLocked = TRUE;

		m_lIdUtenteSuperLock = GetUserIDForLockSuperlock();

		m_sDataOraSuperLock = CTime::GetCurrentTime().Format("%Y%m%d%H%M%S");

		if (m_sDataOraSuperLockPrimo.IsEmpty())
			m_sDataOraSuperLockPrimo = m_sDataOraSuperLock;

		CCustomDate customStart = CCustomDate(m_lData);
		COleDateTime start = COleDateTime(customStart.GetYear(), customStart.GetMonth(), customStart.GetDay(), customStart.GetHour(), customStart.GetMinute(), 0);
		COleDateTime stop = COleDateTime(atoi(m_sDataOraSuperLock.Left(4)),
			atoi(m_sDataOraSuperLock.Mid(4, 2)),
			atoi(m_sDataOraSuperLock.Mid(6, 2)),
			atoi(m_sDataOraSuperLock.Mid(8, 2)),
			atoi(m_sDataOraSuperLock.Mid(10, 2)),
			0); // non serve gestire i secondi perchè dataesame non li gestisce
		COleDateTimeSpan timeDiff = stop - start;

		CString result;
		result.Format("%02li:%02li:%02li", timeDiff.GetDays(), timeDiff.GetHours(), timeDiff.GetMinutes());
		m_sTempoChiusura = result;

		m_lStatoInvioAltraUnita = StatoInvioAltraUnita::auDaInviare;

		UpdateRecordset("CEsamiSet::FlaggaEsameInviaAltraUnita");

		// Flaggo la richiesta come refertata sulla worklist se esiste
		CExtOrdiniSet().SetStatoRichiesta(m_lContatore, LPC_STATO_REFERTATA);
	}
	
	CExtOrdiniSet ordiniCorrelati;
	CString sFilter;
	sFilter.Format("ORDERNUMBER LIKE '%s'", m_sCodesameCorrelati);
	ordiniCorrelati.SetOpenFilter(sFilter);
	if (ordiniCorrelati.OpenRecordset("CEsamiSet::FlaggaEsameInviaAltraUnita"))
	{
		if (!ordiniCorrelati.IsEOF())
		{
			if (ordiniCorrelati.EditRecordset("CEsamiSet::FlaggaEsameInviaAltraUnita"))
			{
				ordiniCorrelati.m_bTrasferito = TRUE;

				ordiniCorrelati.UpdateRecordset("CEsamiSet::FlaggaEsameInviaAltraUnita");
			}
		}

		ordiniCorrelati.CloseRecordset("CEsamiSet::FlaggaEsameInviaAltraUnita");
	}

	return TRUE;
}

//Gabriel - TCP
long CEsamiSet::GetContatore(CString sCodesame)
{
	long lReturn = 0;

	SetBaseFilter("(UO=0 OR UO>0)");

	CString sFilter;
	sFilter.Format("ELIMINATO = 0 AND CODESAME='%s'", sCodesame);

	SetOpenFilter(sFilter);

	if (OpenRecordset("CEsamiSet::GetContatore"))
	{
		if (!IsEOF())
		{
			lReturn = m_lContatore;
		}

		CloseRecordset("CEsamiSet::GetContatore");
	}

	return lReturn;
}