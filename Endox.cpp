#include "stdafx.h"
#include "Endox.h"

#include <GdiPlus.h>
#include <io.h>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include "DLL_Imaging\h\AmBurn.h"
#include "DLL_Imaging\h\AmImgBackup.h"
#include "DLL_Imaging\h\AMLogin.h"

#include "TesiImagingActivate\TesiImagingGenuineSoftware.h"

#include "AccessDlg.h"
#include "BaseSet.h"
#include "CalibList.h"
#include "Common.h"
#include "EsamiDoc.h"
#include "EsamiView.h"
#include "ExportDlg.h"
#include "ImageDlg.h"
#include "ImageSimpleDlg.h"
#include "LicenseDlg.h"
#include "LogFileWriter.h"
#include "MainFrm.h"
#include "MediciSet.h"
#include "PasswordDlg.h"
#include "PdfAnteprimaDlg.h"
#include "SediEsameSet.h"
#include "ShowDbQueriesDlg.h"
#include "UOSet.h"
#include "VistaEsamiPendentiSet.h"
#include "TabellaForm.h"
#include "TXTextControl23.h"
#include "TXButtonBar23.h"
#include "TXRuler23.h"
#include "TXStatusBar23.h"
#include "ModalityWorklistSCP.h"
#include "WorkstationDicomWorklistConfSet.h"

using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEndoxApp theApp;

BEGIN_MESSAGE_MAP(CEndoxApp, CWinApp)
END_MESSAGE_MAP()

CEndoxApp::CEndoxApp()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//Gabriel BUG 6225 - Lista DO
	m_lInstanceCountCImageSimple2Dlg = 0;	// controla a qtd de instancias, necessário para garantir apenas uma
	m_lInstanceCountCImageDlg = 0;			// controla a qtd de instancias, necessário para garantir apenas uma

	m_fEtichette00 = 1.0f;
	m_fEtichette01 = 1.5f;
	m_fEtichette02 = 1.00f;
	m_fEtichette03 = 1.00f;

	m_bCheckRep = FALSE;
	m_bCheckImm = FALSE;
	m_sEditRep = "C:\\";
	m_sEditImm = "C:\\";

	m_sExportFolder = "C:\\";

	m_nQFactorExp = 50;
	m_nExpFormat = 0;

	m_sStoreScpPorta = "50000";
	m_sStoreScpExecOnReceptionExe = "MoveFile.exe";
	m_sStoreScpExecOnReceptionParameters = "";

	m_sDirProg = "C:\\Endox";
	m_sDirTemp = m_sDirProg + "\\TEMP";
    m_sDirTempAcq = "";
    m_sDirTempAcq2 = "";
	m_sPathImageOD = ""; 

	m_sFileCalib = m_sDirProg + "\\MicroImage\\Calib.dat";
	m_sFileConfig = m_sDirProg + "\\EndoxPro.cfg";
	m_sConnStrContigencia = ""; //Julio BUG 3456 - Contingencia

	m_pAccessWnd = NULL;
	m_pShowDbQueriesWnd = NULL;

	m_lUO = 0;

	m_nApplication = -1;
	m_bCanAcquire = FALSE;
	m_bSoloAutoImport = FALSE;
	m_bSoloDicom = FALSE;

	m_sEseguiComando = "";
	m_sAgendaIndex = "";

	//

	m_lSaltaControlloVersione = 0;
	m_lIDSedeEsameDefault = 0;
	m_sSalaEsameDefault = "";

	m_bNomenclatore = TRUE;
	m_nFieldToFilterOnTransfer = -1;
	m_sFilterOnTransfer = "";

	m_sVersione = "";
	m_sNumBuild = "";
	m_sDataBuild = "";

	m_dwPrivileges = 0xFFFFFFFF;
	m_sUtenteLoggato = "";

	m_bConfigure = FALSE; // Sandro 22/03/2010 - durante installazione di Endox //

	m_bPubblicazioneAuto = FALSE;
	m_sPercorsoTemporaneoWEB = "C:\\";
	m_sInterfacciaWebTo = "";
	m_sInterfacciaWebFrom = "";
	m_sInterfacciaWebSupplier = "";
	m_bConsultazioneWEB = FALSE;

	//m_bRobotAttivo = FALSE;
	//m_sRimageAddress = "";
	//m_iRimagePort = 0;
	//m_sRimageMergeFilesPath = "";
	//m_sRimageLabelFile_patient = "";
	//m_sRimageLabelFile_backup = "";
	//m_bRimageSimulateBurning = FALSE;
	//m_sRimageExportFolder = "";

	m_bCanWriteCD = FALSE;
	m_bCanWriteDVD = FALSE;
	m_lBackupDeviceID = -1;
	m_sBackupDevicePath = "";

	m_iIEBrightness = 0;
	m_iIEContrastRMin = 0;
	m_iIEContrastRMax = 255;
	m_iIEContrastGMin = 0;
	m_iIEContrastGMax = 255;
	m_iIEContrastBMin = 0;
	m_iIEContrastBMax = 255;

	m_nInterfacciaPrenotazione = prenotazioni_none;
	m_bLocalInit = FALSE;

	m_pListCalib = NULL;

	m_lIDPrintingWorklist = 0;

	m_lLoginMode = 0; // 0 normale, 1 utente windows, 2 con richiesta della password //
	m_sLoginServer = "";
	m_bLoginDropDomain = FALSE;
	m_sNomeImpianto = "PRINCIPALE";

	m_lDcmStoreMode = 0;

	m_bSaveCompleteLog = FALSE;
	m_sSaveCompleteLogIpDb = "";
	m_sSaveCompleteLogIpImm = "";
	m_lSaveCompleteLogDays = 10;
	m_lSaveCompleteLogThreshold = 500;

	m_enumScannerConnectionType = ScannerConnectionType::twain;

	m_bShowDbQueries = FALSE;
	m_lShowDbQueriesThreshold = 500;

	m_sCodiceDispositivoDefault = "";

	m_sPercorsoOrigineDemoAliar = "";
	m_sPercorsoDestinazioneDemoAliar = "";

	//////////////////////////////////////////
	// letti dalla tabella "Configurazioni" //
	//////////////////////////////////////////

	m_bAlbumImmaginiUsaListaCommenti = FALSE;
	m_bAlbumImmaginiCommentoNonEditabile = FALSE;
	m_bArchivioImmaginiThreadImport = TRUE;
	m_bAssidenKey = TRUE;
	m_bCentraleControlloQualita = FALSE;
	m_bCentraleRefertazione = FALSE;
	m_bCentraleStampa = FALSE;
	m_lCentraleStampaCodiceUnita = 0;
	m_sCodiceUnitaFleury = "";
	m_bNoConiugazione = FALSE;
	m_bCheckListClickElementoSeleziona = FALSE;
	m_bCheckListComponiSequenzialmente = FALSE;
	m_bChiusuraEsameAccodaStampaImmagini = FALSE;
	m_bChiusuraEsameDoppiaConferma = FALSE;
	m_bChiusuraEsameLogoutAuto = FALSE;
	m_bChiusuraEsameSoloConPrestazioniPrincipali = FALSE;
	m_bChiusuraProgrammaConferma = FALSE;
	m_bCodificaRegionaleEliminaDuplicati = FALSE;
	m_lControlloQualitaPercentuale = 0;
	m_sControlloQualitaUnidade = "";
	m_sControlloQualitaRegional = "";
	m_sControlloQualitaMarca = "";
	m_bDemoAliar = FALSE;
	m_bDermoxAcquisizioneDiretta = FALSE;
	m_bDermoxAcqDirettaMantieniCopiaBackup = TRUE;
	m_bDermoxMostraCalibSuAlbum = TRUE;
	m_bDisattivaFrecceSpostamentoPazienti = FALSE;
	m_bInserisciPrenotazione = TRUE;
	m_bIntegrazionePacsAttiva = FALSE;
	m_bIntegrazionePacsSincrona = FALSE;
	m_bInterfacciaDMS = FALSE;
	m_bInterfacciaMetafora = FALSE;
	m_bInterfacciaWeb = FALSE;
	m_bIstopatologiaMostraLettera = FALSE;
	m_bLockServerAttivo = FALSE;
	m_bLoginMultiploUtente = TRUE;
	m_bMediciDescrizioneLibera = FALSE;
	m_bMostraCodiceEsame = TRUE;
	m_bMostraMenuDatabasesRemoti = FALSE;
	m_bMostraNumeroEsamiPerSede = FALSE;
	m_bMostraPazienteInCuraDalDirettore = FALSE;
	m_bMostraSecondoCognome = FALSE;
	m_bMostraSoloAnnoInterventiChirurgici = FALSE;
	m_bMostraSoloAnnoInterventiEndoscopici = FALSE;
	m_bMostraTastoUnificazioneAnagrafiche = TRUE;
	m_bNominativoSuExportImmagini = FALSE;
	m_bNumeriSuImmaginiAlbum = FALSE;
	m_bNumeriSuImmagineSagoma = TRUE;
	m_bOldAlbumMode = TRUE;
	m_bPazienteInternoDefault = TRUE;
	// m_bPazientiUsaVista = FALSE;
	m_bPdfEliminazionePasswordCriptata = FALSE;
	m_bPDFImmaginiCrea = FALSE;
	m_bPDFImmaginiNonCompresse = FALSE;
	m_bPDFIncorporaFonts = FALSE;
	m_bPDFInibisciCopia = FALSE;
	m_bPDFInibisciStampa = FALSE;
	m_bPDFNonProtetti = FALSE;
	m_bPersonalizzazioniBrasileCamargo = FALSE;
	m_bPersonalizzazioniBrasileEinstein = FALSE;
	m_bPersonalizzazioniBrasileFleury = FALSE;
	m_bPersonalizzazioniBrasileSirio = FALSE;
	m_bPrenotazioniCup = FALSE;
	m_lPrenotazioniCupFocus = 0;
	m_bPrenotazioniDicom = FALSE;
	m_bProgressivoEsamePerSede = FALSE;
	m_bRefertazioneLogoutAuto = FALSE;
	m_bRefertazioneUsaChecklist = FALSE;
	m_bRefertazioneUsaFrasiRTF = FALSE;
	m_bRefertazioneUsaFrasiStandard = TRUE;
	m_bReopenAcquisition = FALSE;
	m_bRiaperturaEsameSoloAmministratore = FALSE;
	m_bRicercaChiediConteggio = FALSE;
	m_bRicercaChiediSoloPazienti = FALSE;
	m_bRicettaPerAP = FALSE;
	m_bRicettaPerAP_psm = FALSE;
	m_bRicettaCodebarObbligatori = TRUE;
	m_bSalvaSoloUltimeImmaginiStampate = FALSE;
	m_bSospesiIstologiciNascondiVerificati = FALSE;
	m_bStampaBordiNeriImmagini = TRUE;
	m_bStampaCommentoDentroImmagini = TRUE;
	m_bStampaImmaginiUsaHFPerUO = TRUE;
	m_bStampaSelezionaAutomaticaImmaginiStampate = FALSE;
	m_bStoricoImago = FALSE;
	m_bTastoStampaReportStampaSempre = FALSE;
	m_bUOVisualizzaAngoloAltoDestra = FALSE;
	m_bUsaProntuario = FALSE;
	m_bAttivaRicoveri = FALSE;
	m_bAttivaPS = FALSE;

	m_bMostraScoreMonitoraggio = TRUE;
	m_bUsaScoreDiGlasgow = FALSE;

	m_fSogliaBreathTestHP = 5.0f;

	m_nArchivioImmaginiFormato = image_tiff;
	m_nArchivioImmaginiQualita = 100;
	m_nArchivioImmaginiSogliaAvviso = 10; // 10% di spazio libero rispetto alla dimensione totale del disco //
	m_nArchivioImmaginiSogliaBlocco = 5; // 5% di spazio libero rispetto alla dimensione totale del disco //
	m_nArchivioMiniatureQualita = 100;
	m_nFormatoPagina = FORMATO_REPORT_A4;
	m_nTesiAtdNetPorta = 0;

	m_lBackupDVD = 0;
	m_lBloccoReferto = 24;
	m_lChiusuraEsameRitardoInvioOre = 0;
	m_lChiusuraEsameRitardoInvioMinuti = 0;
	m_lCodificaRegionaleMostraCodice = 0;
	m_lCountdownPartenza = 5;
	m_lIDEsameFirmaDisattivata = 0;
	m_lInterfacciaPathox = 0;
	m_lMaxIdRange = 0;
	m_lMinIdRange = 0;
	m_lModalitaCaricamentoCampiDefault = 0;
	m_lModificaReferto = 0;
	m_lMostraEtaPaziente = 1;
	m_lOpzionalePazientiCronici = 0;
	m_lPDFQualitaImmaginiCompresse = 80;
	m_lPressioneMinimaValoreMinimo = 30;
	m_lPressioneMinimaValoreMassimo = 100;
	m_lPressioneMassimaValoreMinimo = 50;
	m_lPressioneMassimaValoreMassimo = 200;
	m_lRefertoAllineamentoTestoDefault = 3; // testo giustificato //
	m_lRicercaCodiceEsame = 0;
	m_lRicettaMaxItems = 8;

	m_sBarCodeFontName = "";
	m_sControlloOrtograficoPathDizionarioUtente = "";
	m_sEmissioneRefertoUrl = "";
	m_sEsportaFilmatiPerVisoreWebSuPath = "";
	m_sLockServerIndirizzo = "";
	m_lLockServerPorta = 0;
	m_sNomeProgramma = "ENDOX";
	m_sNomeProgrammaCertificazione = "Sistemi informativi per l'endoscopia";
	m_sPazientiTabella = "EPAZIENTI";
	// m_sPazientiVista = "VISTAPAZIENTI";
	// m_sPazientiVistaOrdinamento = "DataUltimoEsame, Contatore DESC";
	m_sPdfEliminazionePassword = "12345678";
	m_sPercorsoAllegatiPaz = "";
	m_sPercorsoAllegatiEsa = "";
	m_sPercorsoPDF = "";
	m_sPercorsoReportsConsensoInformato = "";
	m_sQueryMan = "";
	m_sSmartCardPin = "";
	m_sTesiAtdNetIndirizzo = "";
	m_sTestiConcatenatiSeparatore = " + ";
	m_sNoteReperibilitaDefault = "";

	m_bFleuryProgrammaConsultaNuovo = FALSE;

	//

	m_enumFirmaDigitale = sign_disabled;
	m_bFirmaDigitaleChiudiComped = FALSE;
	m_bFirmaDigitaleDebug = FALSE;
	m_bFirmaDigitaleAnteprimaMostra = TRUE;
	m_bFirmaDigitaleSmartcardUgualeMedico1 = FALSE;
	m_bFirmaDigitaleSmartcardUgualeUtenteEndox = FALSE;
	m_lFirmaDigitaleStampa = 1;
	m_sFirmaDigitaleTemplatesPath = "";
	m_sFirmaDigitaleReportAnnullamento = "";
	m_bSISSRichiediMarcaTemporale = FALSE;
	m_bSISSGeneraSempreDAO = FALSE;
	m_bSISSMostraMenuDisattivaFirma = FALSE;
	m_sRicetteEngeneeringExe = "";

	m_lOpenIntoMonitor = 0;

	m_bTextControlCopiaIncollaRimuoviFormattazione = TRUE;
	
	m_bRicercaUOLimitata = FALSE; // Luiz 08/02/2019 - P3 - Dependendo da Configuração (Ricerca UO limitata), impedir que itens de outra especialidade na conjugacao
	//m_bConfermareGliEsamiSenzaAttaccamentoOImmagini = FALSE; // Luiz 11/02/2019 - P3 - Dependendo da Configuração (Confermare Gli Esami Senza Attaccamento O Immagini), confirma salvar/assinar exames sem anexos ou imagens 
	m_bFaseExtraAmarradoAoSuperlock = TRUE; // Luiz 27/03/2019 - P3 - Dependendo da Configuração (Fase Extra Amarrado Ao Superlock), obriga que seja realizada sequencia salvar/assinar antes de protocolar e desfazer protocolar antes de desfazer salvar/assinar
	m_bSelezionaMedicoRichiedente = FALSE; //Gabriel - P3
	/////////////////////////////////////////////////
	/////////////////////////////////////////////////
	/////////////////////////////////////////////////

	int i;

	for(i = 0; i < NUM_FIELD_ANAM; i++)
	{
		m_bAnamVisi[i] = TRUE;
		m_bAnamAuto[i] = TRUE;
	}

	for(i = 0; i < NUM_LABEL_TESTO; i++)
	{
		m_bComboActive[i] = TRUE;
		m_bComboMultipleSel[i] = TRUE;
		m_bComboSingleLine[i] = FALSE;
		m_bComboUppercase[i] = FALSE;
		m_bComboNumerico[i]	= FALSE;
		m_sLabelText[i] = "";		
		m_bCopy[i] = FALSE;
		m_lIdCampoRelazionato[i] = 0;
		m_lIdCampoRelazionatoRtf[i] = 0;
	}

	for(i = 0; i < NUM_LABEL_TESTO_RTF; i++)
	{
		m_sLabelTextRtf[i] = "";
		m_bCopyRtf[i] = FALSE;
	}

	for(i = 0; i < NUM_LABEL_TESTO_CL; i++)
	{
		m_sLabelTextCL[i] = "";
		m_bCopyCL[i] = FALSE;
		m_bAlarmCL[i] = FALSE;
		m_sParoleChiaveCL[i] = "";
	}

	for(i = 0; i < NUM_LABEL_DATAORA; i++)
	{
		m_sLabelDate[i] = "";
		m_bCopyDate[i] = FALSE;
		m_iRadioDate[i] = 0;
	}

	for(i = 0; i < NUM_LABEL_TASTO_STAMPA; i++)
	{
		m_sLabelTastoStampa[i] = "";
		m_sTastoStampaFile[i] = "";
		m_bTastoStampaCheck[i] = TRUE;
	}

	for(i = 0; i < NUM_LABEL_TASTO_BROWSER; i++)
	{
		m_sLabelTastoBrowser[i] = "";
		m_sTastoBrowserIndirizzo[i] = "";
	}

	for(i = 0; i < NUM_LABEL_TASTO_EXEC; i++)
	{
		m_sLabelTastoEseguibile[i] = "";
		m_sTastoEseguibileFile[i] = "";
	}

	for (i = 0; i < NUM_LABEL_TASTO_CHIUSURAFASE; i++)
	{
		m_sLabelTastoChiusuraFase[i] = "";
		m_lIdFaseTastoChiusuraFase[i] = 0;		
	}

	for (i = 0; i < NUM_LABEL_ETICHETTE; i++)
	{
		m_sLabelTextEtichette[i] = "";
	}

	for (i = 0; i < NUM_LABEL_GRIDCL; i++)
	{
		m_sLabelTextGridCL[i] = "";
		m_listGridCLGruppiAssociati[i].RemoveAll();
	}		

	m_lLastGridCLVersion = 0;

	m_sBostonScore[0] = "0";
	m_sBostonScore[1] = "1";
	m_sBostonScore[2] = "2";
	m_sBostonScore[3] = "3";
	m_sBostonScore[4] = "4";
	m_sBostonScore[5] = "5";
	m_sBostonScore[6] = "6";
	m_sBostonScore[7] = "7";
	m_sBostonScore[8] = "8";
	m_sBostonScore[9] = "9";

	m_bStampaImmaginiStampaCommenti = TRUE;
	m_bStampaImmaginiStampaDatiPaziente = TRUE;
	m_bStampaImmaginiStampaNumero = FALSE;
	m_nStampaImmaginiDistanzaImmagini = 0;
	m_nStampaImmaginiTipoDiStampa = 3;
	m_lIDStampanteImmagini = Printer_Immagini;
	m_lStampaImmaginiIDHeaderGlobal = 0;
	m_lStampaImmaginiIDHeaderLocal = 0;
	m_lStampaImmaginiIDFooterGlobal = 0;
	m_lStampaImmaginiIDFooterLocal = 0;
	m_sStampaImmaginiSiglePerStampaOrizzontale = ""; //Gabriel BUG 6303
	m_sSpermaEsameSiglePerGenerazioneGrafici = ""; //Gabriel BUG 5533

	m_bLoadingInterface = FALSE;

	m_nProgramMode = NOTHING_MODE;
	m_nQuanteImmaginiPerPagina[0] = 1;
	m_nQuanteImmaginiPerPagina[1] = 2;
	m_nQuanteImmaginiPerPagina[2] = 4;
	m_nQuanteImmaginiPerPagina[3] = 6;

	m_lOnlyThisFrame = -1;

	m_sAnamText[0] = "Fumo";
	m_sAnamText[1] = "Sigarette";
	m_sAnamText[2] = "Caffè";
	m_sAnamText[3] = "Alcool";
	m_sAnamText[4] = "Alcolici";
	m_sAnamText[5] = "Farmaci";
	m_sAnamText[6] = "Assunzione";
	m_sAnamText[7] = "Peso (kg)";
	m_sAnamText[8] = "Altezza (cm)";
	m_sAnamText[9] = "BMI";
	m_sAnamText[10] = "BSA";

	m_sHeaderPrintImage = " Tesi Imaging ";

	m_color[0] = RGB(178,   0,   0); // ROSSO
	m_color[1] = RGB(178, 133,   0); // GIALLO
	m_color[2] = RGB(110, 150,  20); // VERDE
	m_color[3] = RGB(54,  129, 161); // CIANO
	m_color[4] = RGB(54,   39, 171); // BLU
	m_color[5] = RGB(137,  39, 181); // VIOLA
	// m_colorFrame = RGB(0,  70, 213); // colore celeste delle etichette dei frames

	m_colorSfondo[0] = RGB(255, 220, 210); // ROSSO
	m_colorSfondo[1] = RGB(250, 250, 200); // GIALLO
	m_colorSfondo[2] = RGB(220, 255, 220); // VERDE
	m_colorSfondo[3] = RGB(200, 250, 250); // CIANO
	m_colorSfondo[4] = RGB(220, 220, 255); // BLU
	m_colorSfondo[5] = RGB(250, 200, 250); // VIOLA

	m_colorVisualizzazioneAperto = RGB(110, 150, 20);
	m_colorVisualizzazioneApertoSfondo = RGB(220, 255, 220);
	m_colorVisualizzazioneChiuso = RGB(110, 150, 20);
	m_colorVisualizzazioneChiusoSfondo = RGB(220, 255, 220);
	m_colorVisualizzazioneFirmato = RGB(110, 150, 20);
	m_colorVisualizzazioneFirmatoSfondo = RGB(220, 255, 220);
	m_colorAggiuntaPaziente = RGB(178, 0, 0);
	m_colorAggiuntaPazienteSfondo = RGB(255, 220, 210);
	m_colorModificaPaziente = RGB(178, 133, 0);
	m_colorModificaPazienteSfondo = RGB(250, 250, 200);
	m_colorAggiuntaEsame = RGB(178, 0, 0);
	m_colorAggiuntaEsameSfondo = RGB(255, 220, 210);
	m_colorModificaEsame = RGB(178, 133, 0);
	m_colorModificaEsameSfondo = RGB(250, 250, 200);
	m_colorRicercaPaziente = RGB(54, 39, 171);
	m_colorRicercaPazienteSfondo = RGB(220, 220, 255);
	m_colorRicercaEsame = RGB(54, 39, 171);
	m_colorRicercaEsameSfondo = RGB(220, 220, 255);
	m_colorVisualizzazioneInArchiviazione = RGB(255, 255, 255);
	m_colorVisualizzazioneInArchiviazioneSfondo = RGB(0, 0, 0);
	m_colorVisualizzazioneArchiviato = RGB(0, 0, 0);
	m_colorVisualizzazioneArchiviatoSfondo = RGB(255, 255, 255);
	m_colorStreamingAttivo = RGB(0, 0, 0);
	m_colorStreamingAttivoSfondo = RGB(255, 255, 255);
	m_colorStreamingConnesso = RGB(0, 0, 0);
	m_colorStreamingConnessoSfondo = RGB(255, 255, 255);

	m_pSetPazienti = NULL;
	m_pSetEsami = NULL;

	m_bVisAbilita	=	FALSE;
	m_bVisAbilitaMonitor =	FALSE;
	m_sVisIp		=	"0.0.0.0";
	m_lVisPorta		=	0;
	m_sVisPortaMonitor = "";

	m_bIntegrazioneGestioneRichiesteAcquisite = FALSE;
	m_bIntegrazioneInvioImmaginiBinarie = FALSE;
	m_bIntegrazioneInvioRefertiAnnullati = FALSE;
	m_bIntegrazioneInvioRefertiDalFiller = FALSE;

	m_sHttpServerRicercaFicha = "";
	m_sHttpServerRichiestaInfoUser = "";
	m_sHttpServerRichiestaUserSignature = "";
	m_sHttpServerRichiestaModificaStampa = "";
	m_sHttpServerRichiestaUnidade = "";
	m_sHttpServerRichiestaLaudos = "";

	m_sTabellaEcocardioFormulaBSA.Format("0.007184 * (%s%s%s ^ 0.425) * (%s%s%s ^ 0.725)",
		                                 _SPREADSHEET_FORMULA_SEPARATOR,
		                                 _SPREADSHEET_WEIGHT_NAME,
										 _SPREADSHEET_FORMULA_SEPARATOR,
										 _SPREADSHEET_FORMULA_SEPARATOR,
		                                 _SPREADSHEET_HEIGHT_NAME,
										 _SPREADSHEET_FORMULA_SEPARATOR);
	m_sTabellaEcocardioTabs = "200;400;600;800;";

	// Sandro 17/07/2015 // RIMA 15052 //
	m_sRefertoIntegratoRtf = "";
	m_sRefertoIntegratoTxt = "";

	// Sandro 07/12/2015 // RIMA 15135 //
	m_sPassedConnectionString = "";
	m_sPassedDescription = "";
	m_sPassedUsername = "";
	m_sPassedPassword = "";
	m_sPassedUO = "";

	// Sandro 02/09/2015 // demo //
	m_sPassedUsername = "";

	m_bVitalSignIntegrazioneAttiva = FALSE;
	m_sVitalSignWebServiceEndpoint = "";

	m_bUsaUtenteLoggatoComeMedicoDefault = TRUE;
	m_bPrestazioniReadOnly = FALSE;

	m_bMantieniImmaginiSelezionateAlLogout = FALSE;
	m_listUserGroups.RemoveAll();
	m_listUserPhases.RemoveAll();
	m_nMonitoraggioDoloreDefault = 0;

	m_bEsameFirmatoDigitalmenteAlmenoUnaVolta = FALSE;

	m_lIdRobotDefault = 0;
	m_bChiusuraFaseLogin = FALSE;

	m_bMonitoraggioPermettiCopia = FALSE;

	m_bDicomWorklistActive = FALSE;
	m_sDicomWorklistAet = "";
	m_lDicomWorklistPort = 0;
	m_bDicomWorklistLog = FALSE;

	//Julio 13/11/2107
	m_sLaudoRtfExameAnteriorEndpoint = "";
	//Julio 12/03/2018
	m_bMenuUsaCarestreamExamesPendentes = FALSE;
	m_bMenuUsaTextboxBuscaExame = FALSE;
	m_bUsaLaudoProvisorio = FALSE;
	m_sHttpPathVisorPacsWeb = "";
	//Julio 17/08/2018
	m_bLoadPrinterSettings = TRUE;
	//Julio 22/10/2018
	m_bImpersonated = FALSE;
	m_lImpersonatedID = 0;
	m_sImpersonatedUsername = "";
	
	m_sHttpServerAnulaLiberaLaudo = "";// Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
	m_sPrestazione = "";// Luiz - 02/05/2019 - P3 - Checkbox "Mostrar todas" - checklist laudo
	m_bPossuiConjugados = FALSE;// Luiz - 07/05/2019 - P3 - Desconjuga exames - ESAMIINTEGRATI

	m_bContingencia = FALSE; //Julio BUG 3456 - Contingencia
	m_bCapturaContinua = FALSE; //Julio (FIX) BUG 3361 - Captura continua

	//Julio - BUG 4392 Edicao de texto
	m_bRtfUsaConfigurazioniTabelle = FALSE;
	m_bRtfUsaConfigurazioniFont = FALSE;
	m_bRtfUsaConfigurazioniImmagini = FALSE;
	//

	m_bUsaComboPrestazioni = FALSE; //Julio - BUG 4392 Edicao de texto

	// Marvel Carvalho | BUG 3759 - TesiCapture Melhoria Filtro Worklist
	// defaults das variáveis usadas para armazenar os filtros do usuário da tela da worklist
	m_default_LISTAPRENOTAZIONICUP_HasFilter = false;
	m_default_LISTAPRENOTAZIONICUP_CODICERICOVERO = "";
	m_default_LISTAPRENOTAZIONICUP_NUMORDINE = "";
	m_default_LISTAPRENOTAZIONICUP_CODPAZIENTE = "";
	m_default_LISTAPRENOTAZIONICUP_COGNOME = "";
	m_default_LISTAPRENOTAZIONICUP_NOME = "";
	m_default_LISTAPRENOTAZIONICUP_COMBODATA = 1;		// giorno corrente
	m_default_LISTAPRENOTAZIONICUP_DATAINIZ = "00/00/0000";
	m_default_LISTAPRENOTAZIONICUP_DATAFINE = "00/00/0000";
	m_default_LISTAPRENOTAZIONICUP_COMBOUNIDADE = 0;
	m_default_LISTAPRENOTAZIONICUP_COMBOSTATO = 1;		// Medico 2 - Firma 3
	m_default_LISTAPRENOTAZIONICUP_COMBOPROVENIENZA = 0;
	m_default_LISTAPRENOTAZIONICUP_CHKFILTERDATA = false;
	m_default_LISTAPRENOTAZIONICUP_COMBOREGIONAL = 0;
	m_default_LISTAPRENOTAZIONICUP_COMBOSEDE = 0;
	m_default_LISTAPRENOTAZIONICUP_COMBOSALA = 0;
	m_default_LISTAPRENOTAZIONICUP_COMBOMARCA = 0;

	// Marvel Carvalho | BUG 3780 - TesiCapture Melhoria Filtro Esami Pendenti
	// variáveis para armazenar os filtros do usuário da tela esami pendenti
	m_default_GESTIONEESAMIPENDENTI_HasFilter  = false;
	m_default_GESTIONEESAMIPENDENTI_COMBODATA = 1; // giorno corrente
	m_default_GESTIONEESAMIPENDENTI_DATAINIZ = 0;
	m_default_GESTIONEESAMIPENDENTI_DATAFINE = 0;

	m_default_GESTIONEESAMIPENDENTI_COMBOUO = 0;
	m_default_GESTIONEESAMIPENDENTI_COMBOMEDICO = 0;

	m_bUsaIDSegu = FALSE; //Julio Login SEGU

	m_sIndirizziMailReconvocazione = ""; //Gabriel BUG 6225 - Lista DO
	m_bRefertoMostraEtaPazienteTitolo = FALSE; //Gabriel BUG 6225 - Lista DO
	m_bImportazioneAutomaticaRicetta = FALSE; //Gabriel BUG 6225 - Lista DO
	m_bUsaTexterAsRTF = FALSE;

	m_sHttpServerSubstituicaoResultado = ""; //Gabriel - P3
	m_sHttpServerProtocoloXXI = ""; //Gabriel - P3

	m_bUsaCapturaScannerTGrabber = FALSE; //Gabriel BUG 7749 - Capturar imagens via xtwain utilizando pedal USB
	m_bAtivaP3 = FALSE; //Gabriel - Chave para ativar P3
	m_bAtivaListaDO = FALSE; //Gabriel - Chave para ativar Lista DO
	m_bAtivaTCP = FALSE; //Gabriel - TCP
	m_sSiglasTCP = ""; //Gabriel - TCP
	m_bUsaNovaCapturaContinua = FALSE; //Gabriel BUG 7768 - Continuous capture problem
	m_sEsamiPendentiOrdineColonna = "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10"; //Gabriel BUG 6225 - Lista DO FIX
	m_lEsamiPendentiColonnaOrdinare = 0; //Gabriel BUG 6225 - Lista DO FIX
	m_bAbreImgTelaCheia = FALSE; //Gabriel BUG 6225 - Lista DO FIX

	m_bAtivaEspermograma = FALSE; //Gabriel - Chave para ativar Espermograma V2
}

CEndoxApp::~CEndoxApp()
{
	DestroyShowDbQueriesDialog();

	if (m_pListCalib)
	{
		m_pListCalib->DeleteContents();
		delete m_pListCalib;
		m_pListCalib = NULL;
	}

    if (m_pAccessWnd != NULL)
	{
        m_pAccessWnd->DestroyWindow();
        delete m_pAccessWnd;
        m_pAccessWnd = NULL;
    }

	if (m_dbEndox.IsOpen())
		m_dbEndox.Close();
}

CString CEndoxApp::GetMessageString(const UINT idString, const Localized_Modules module)
{
	CString strReturn, strITA;
	strITA.LoadString(idString);
	if (AMLocalize_GetGenericMessage(module, idString, strITA, &strReturn))
	{
		strReturn.Replace("\\n", "\n");
		strReturn.Replace("\\r", "\r");
		strReturn.Replace("\\t", "\t");
	}
	else
		strReturn.Empty();

	return strReturn;
}

void CEndoxApp::LocalizeDialog(CWnd* pDialog, const UINT idDialog, const CString& strDialog, const Localized_Modules module)
{
	CWnd* pWnd = pDialog->GetWindow(GW_CHILD);
	while (pWnd)
	{
		AMLOCALIZE_MESSAGEPARAM param;
		param.idForm = idDialog;
		param.pFormDescription = &strDialog;
		param.module = module;
		pWnd->SendMessage(AMLOCALIZE_MSG, 0, (LPARAM)&param);
		pWnd = pWnd->GetWindow(GW_HWNDNEXT);
	}

	CString strOldCaption, strNewCaption;
	pDialog->GetWindowText(strOldCaption);
	if (AMLocalize_GetDialogCaption(module, idDialog, strOldCaption, &strNewCaption))
		pDialog->SetWindowText(strNewCaption);
}

BOOL CEndoxApp::InitInstance() 
{
	TRACE0("-> InitInstance()\n");

	if FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED))
	{
		AfxMessageBoxEndo("CoInitializeEx(null)");
		return FALSE;
	}

	//
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	//
	char szTemp[1024];
	DWORD dwBufSize = 1024;
	if ((GetComputerName(szTemp, &dwBufSize)) && (dwBufSize > 0))
		m_sNomeComputer.Format("%s", szTemp);

	TCHAR szModuleName[MAX_PATH];
    GetModuleFileName(AfxGetInstanceHandle(), szModuleName, sizeof(szModuleName));

    CString strExeName = CString(m_pszExeName) + ".exe";

    m_sDirProg = CString(szModuleName);
    m_sDirProg = m_sDirProg.Left(m_sDirProg.GetLength() - strExeName.GetLength() - 1);

	m_sDirTemp = m_sDirProg + "\\TEMP";

	m_sFileCalib = m_sDirProg + "\\MicroImage\\Calib.dat";

    m_sFileConfig = m_sDirProg + "\\EndoxPro.cfg";
	
    m_pAccessWnd = new CAccessDlg;

    AfxEnableControlContainer();
    RegisterPrivateMessage();

    LoadStdProfileSettings();
    LoadSetting();

	SetFont();

	if (!AMLocalize_Init("Endox", m_nLanguage))
		AfxMessageBoxEndo("AMLocalize ERROR!", MB_ICONSTOP);
	else
		m_bLocalInit = TRUE;

#ifdef _DEBUG

	// Sandro 27/11/2014 // carico nel dictionary TUTTA la string table //

	if (m_bLocalInit)
	{
		for (int i = 0; i < 16000; i++)
		{
			CString str;
			if ((str.LoadString(i) != 0) && !str.IsEmpty())
			{
				GetMessageString(i);

				if (str.GetLength() > 254)
				{
					CString sErrrr;
					sErrrr.Format("%d è lunga %d caratteri!\n\n%s", i, str.GetLength(), str);

					AfxMessageBox(sErrrr);
				}
			}
		}
	}

#endif

	// Sandro 22/03/2010 - l'installazione di Endox mi apre la schermata di "Setup Programma" //
	CString strCmdLine(m_lpCmdLine);
	strCmdLine.Trim();
	strCmdLine.MakeUpper();
	if (strCmdLine == "-CONFIGURE")
	{
		m_bConfigure = TRUE;
	}
	else
	{
		// Sandro 07/12/2015 // RIMA 15135 // provo a spostare un po' prima questa parte... //

		for (int i = 1; i < __argc; i++)
		{
			LPCTSTR pszParam = __targv[i];

			BOOL bLast = ((i + 1) == __argc);
			if (pszParam[0] == '-' || pszParam[0] == '/' || pszParam[0] == '\\')
				++pszParam;

			CString sX(pszParam);
			if (sX.GetLength() > 2)
			{
				if (sX.Left(2).CompareNoCase("C:") == 0)
				{
					m_sPassedConnectionString = sX.Right(sX.GetLength() - 2);
					m_sPassedConnectionString.Trim();
				}
				else if (sX.Left(2).CompareNoCase("D:") == 0)
				{
					m_sPassedDescription = sX.Right(sX.GetLength() - 2);
					m_sPassedDescription.Trim();
					m_sPassedDescription.MakeUpper();
				}
				else if (sX.Left(2).CompareNoCase("U:") == 0)
				{
					m_sPassedUsername = sX.Right(sX.GetLength() - 2);
					m_sPassedUsername.Trim();
				}
				else if (sX.Left(2).CompareNoCase("P:") == 0)
				{
					m_sPassedPassword = sX.Right(sX.GetLength() - 2);
					m_sPassedPassword.Trim();
				}
				else if (sX.Left(2).CompareNoCase("O:") == 0)
				{
					m_sPassedUO = sX.Right(sX.GetLength() - 2);
					m_sPassedUO.Trim();
				}
			}
		}
	}

#ifdef _LOG_DB
	MessageBoxEndo(NULL, GetMessageString(IDS_DBLOG_ACTIVATED), GetMessageString(IDS_ACHTUNG), MB_OK | MB_ICONWARNING);
	CLogFileWriter::Get()->OpenLogFile("DbLog.txt");
#endif // _LOG_DB //

	// qui dovrei aprire il DB --> // 
	try
	{
		BOOL bDBOpened = FALSE;

		if (m_sPassedConnectionString.IsEmpty())
			bDBOpened = m_dbEndox.OpenDirect(m_sFileConfig);
		else
			bDBOpened = m_dbEndox.OpenEx(m_sPassedConnectionString, CDatabase::noOdbcDialog); // Sandro 07/12/2015 // RIMA 15135 //
		

		if (bDBOpened)
		{
			// Sandro 21/05/2013 //
			if (!m_dbEndox.CheckTableExists("EPAZIENTI") || !m_dbEndox.CheckTableExists("EESAMI") || !m_dbEndox.CheckTableExists("IMMAGINI"))
			{
				if (m_dbEndox.IsOpen())
					m_dbEndox.Close();

				CDBException* pEx = new CDBException();
				// pEx->m_strError = GetMessageString(IDS_ESAMIDOC_ERR_DATABASE);
				throw pEx;
			}

			// Sandro 22/03/2010 - durante installazione di Endox //
			if (m_bConfigure)
			{
				CreateFile(	m_sDirProg + "\\ConnectDB.OK",
							GENERIC_WRITE,
							0,
							NULL,
							CREATE_ALWAYS,
							FILE_ATTRIBUTE_NORMAL,
							NULL);
			}
		}
		else
		{						
			CDBException* pEx = new CDBException();
			pEx->m_strError = GetMessageString(IDS_ESAMIDOC_ERR_DATABASE);
			throw pEx;
		}
	}
	catch(CDBException* pEx)
	{		
		//Julio BUG 3456 - Contingencia		
		BOOL bSuccess = FALSE;
		
		if (!m_sConnStrContigencia.IsEmpty())
		{
			bSuccess = m_dbEndox.OpenEx(m_sConnStrContigencia, CDatabase::noOdbcDialog);

			if (bSuccess)
			{				
				if (!m_dbEndox.CheckTableExists("EPAZIENTI") || !m_dbEndox.CheckTableExists("EESAMI") || !m_dbEndox.CheckTableExists("IMMAGINI"))
				{
					if (m_dbEndox.IsOpen())
						m_dbEndox.Close();

					bSuccess = FALSE;
				}
				else
					bSuccess = TRUE;
			
			}			
		}

		if (!bSuccess)
		{				
			DestroyAccessDialog();
			DestroyShowDbQueriesDialog();

			if (m_bConfigure)
			{
				// Sandro 22/03/2010 - durante installazione di Endox //
				Amdbx_ConfigDatabase(m_sFileConfig);
			}
			else
			{
				if (!pEx->m_strError.IsEmpty())
					pEx->ReportError();
				AfxMessageBoxEndo(GetMessageString(IDS_ESAMIDOC_ERR_CONFIG_APP));

				if (CPasswordDlg(NULL, GetMessageString(IDS_PASSWORD_DATABASE), "1qaz2wsx3edc").DoModal() == IDOK)
					Amdbx_ConfigDatabase(m_sFileConfig);
			}
			pEx->Delete();

			return FALSE;
		}
		//
	}
	// <-- qui dovrei aprire il DB //

	if (m_lIDSedeEsameDefault == 0) // provo a riprendere l'ID partendo dalla vecchia stringa //
		m_lIDSedeEsameDefault = CSediEsameSet().GetID(GetPrivateProfileString(szSettings, szSedeEsameDefaultOld, "", m_sFileConfig));

	// lettura calibrazioni //
	CFile f;
	CFileException e;
	m_pListCalib = new CCalibList;
	m_pListCalib->DeleteContents();
	m_pListCalib->m_strFileName = m_sFileCalib;
	if (!f.Open(m_pListCalib->m_strFileName, CFile::modeRead, &e))
	{
		char szError[1024];
		e.GetErrorMessage(szError, 1023);

		CString sMessage;
		sMessage.Format(GetMessageString(IDS_CALIB_ERROR), szError);
		AfxMessageBoxEndo(sMessage);

		m_pListCalib->NewCalib();

		// Sandro 23/10/2014 //
		if (_access(m_sFileCalib, 00) != 0)
			m_pListCalib->WriteDisk();
	}
	else
	{
		f.Close();
		m_pListCalib->ReadDisk();
	}
	// --- //

	SetGlobalVariables();

	if (AlreadyLiving())
	{
		PosOnTop();
		return FALSE;
	}
	else
	{
		if (!Live())
		{
			if (!m_sPassedConnectionString.IsEmpty())
				AfxMessageBoxEndo("!Live");
		}
	}

	TRACE0(" -> AMLogin_EnableLocalization\n");
	AMLogin_EnableLocalization(GetMessageString, LocalizeDialog);

	//TRACE0(" -> AmImgBackup_EnableLocalization\n");
	//AmImgBackup_EnableLocalization(GetMessageString, LocalizeDialog);

	// protezione software //
	if (CTesiImagingGenuineSoftware::Get()->Verify("ENDOX", (CDatabase*)&m_dbEndox))
	{
		BYTE szBuffer[8];
		CTesiImagingGenuineSoftware::Get()->GetActivations(szBuffer);

		///// Primo byte - Programma /////////////////////////////////////
		// 0x08 --> EndoxPro e derivati vari                            //
		// nel caso in cui viene modificato qualcosa mettere a posto    //
		// anche il costruttore di CLicenseDlg un pò più sotto          //
		//////////////////////////////////////////////////////////////////

		if (szBuffer[0] != 0x08)
		{
			AfxMessageBoxEndo(GetMessageString(IDS_ERROR_DB_PROTECTION), MB_ICONSTOP);
			return FALSE;
		}

		///// Secondo byte - Sottoprogramma //////////////////////////////
		// 0x01 (bit 0) --> Endox                                       //
		// 0x04 (bit 2) --> Cardiox                                     //
		// 0x08 (bit 3) --> ImageNT                                     //
		// 0x10 (bit 4) --> Dermox                                      //
		// nel caso in cui viene modificato qualcosa mettere a posto    //
		// anche il costruttore di CLicenseDlg un pò più sotto          //
		//////////////////////////////////////////////////////////////////

		if ((szBuffer[1] == 0x00) || (szBuffer[1] == 0xFF))
		{
			AfxMessageBoxEndo(GetMessageString(IDS_ERROR_DB_PROTECTION), MB_ICONSTOP);
			return FALSE;
		}
		else
		{
			if ((szBuffer[1] & 0x01) != 0) // EndoxPro
			{
				m_nApplication = PRG_ENDOX;
			}
			else
			{
				if ((szBuffer[1] & 0x04) != 0) // Cardiox
				{
					m_nApplication = PRG_CARDIOX;
				}
				else
				{
					if ((szBuffer[1] & 0x08) != 0) // ImageNT
					{
						m_nApplication = PRG_IMAGENT;
					}
					else
					{
						if ((szBuffer[1] & 0x10) != 0) // Dermox
						{
							m_nApplication = PRG_DERMOX;
						}
						else
						{
							AfxMessageBoxEndo(GetMessageString(IDS_ERROR_DB_PROTECTION), MB_ICONSTOP);
							return FALSE;
						}
					}
				}
			}
		}

		///// Terzo byte - Attivazioni hardware - 3D attiva tutto /////////////////////////////////////
		// 0x01 //   1 // bit 0 // Stazione di acquisizione                                          //
		// 0x02 //   2 // bit 1 //                                                                   //
		// 0x04 //   4 // bit 2 // Nomenclatore presente                                             //
		// 0x08 //   8 // bit 3 //                                                                   //
		// 0x10 //  16 // bit 4 // Gestione Clean Track                                              //
		// 0x20 //  32 // bit 5 // SOLO acquisizione Dicom (no telecamera xCap)                      //
		// 0x40 //  64 // bit 6 // SOLO acquisizione import immagini automatico (no telecamera xCap) //
		// 0x80 // 128 // bit 7 //                                                                   //
		// nel caso in cui viene modificato qualcosa mettere a posto                                 //
		// anche il costruttore di CLicenseDlg un pò più sotto                                       //
		///////////////////////////////////////////////////////////////////////////////////////////////

		if ((szBuffer[2] & 0x01) != 0) // Stazione di acquisizione //
			m_bCanAcquire = TRUE;
		else
			m_bCanAcquire = FALSE;

		if ((szBuffer[2] & 0x04) != 0) // Nomenclatore presente //
			m_bNomenclatore = TRUE;
		else
			m_bNomenclatore = FALSE;

		if ((szBuffer[2] & 0x20) != 0) // SOLO acquisizione Dicom (no telecamera xCap) //
			m_bSoloDicom = TRUE;
		else
			m_bSoloDicom = FALSE;

		if ((szBuffer[2] & 0x40) != 0) // SOLO acquisizione import immagini automatico (no telecamera xCap) //
			m_bSoloAutoImport = TRUE;
		else
			m_bSoloAutoImport = FALSE;
	}
	else
	{
		if (!m_bConfigure)
		{
			DestroyAccessDialog();

			// Viene passata la maschera dei bit usati da Endox (in pratica è come se tutte le attivazioni fossero attivate)
			//                Primo byte                       Secondo byte                                          Terzo byte
			CLicenseDlg dlg((((ULONGLONG)0x08) << (8 * 0)) + (((ULONGLONG)0x01 + 0x10 + 0x08 + 0x04) << (8 * 1)) + (((ULONGLONG)0x1 + 0x04 + 0x08 + 0x10 + 0x20 + 0x40) << (8 * 2)));
			dlg.DoModal();

			// AfxMessageBoxEndo(GetMessageString(IDS_ERROR_DB_PROTECTION), MB_ICONSTOP);
			return FALSE;
		}
	}

	/*#ifdef _LOG_DB
		CLogFileWriter::Get()->WriteLogLine(" -> AMBurn_Initialize");
	#endif*/
	TRACE0(" -> AMBurn_Initialize\n");
	if (AMBurn_Initialize() == TRUE)
	{
		/*#ifdef _LOG_DB
			CLogFileWriter::Get()->WriteLogLine("-> AMBURN: inizializzazione riuscita");
		#endif*/
		TRACE0("-> AMBURN: inizializzazione riuscita\n");

		tagDEVICE* pDevice = NULL;

		if (AMBurn_GetSystemDevice(&pDevice) == TRUE)
		{
			while(pDevice != NULL)
			{
				/*#ifdef _LOG_DB
					CString strTemp;
					strTemp.Format("   trovato %s - CD: %s - DVD: %s\n", pDevice->szName, pDevice->bCD == TRUE ? "sì" : "no", pDevice->bDVD == TRUE ? "sì" : "no");
					CLogFileWriter::Get()->WriteLogLine(strTemp);
				#endif*/

				TRACE3("   trovato %s - CD: %s - DVD: %s\n", pDevice->szName, pDevice->bCD == TRUE ? "sì" : "no", pDevice->bDVD == TRUE ? "sì" : "no");

				if (pDevice->bCD == TRUE)
					m_bCanWriteCD = TRUE;
				if (pDevice->bDVD == TRUE)
				{
					m_bCanWriteDVD = TRUE;

					m_lBackupDeviceID = pDevice->lID;
					m_sBackupDevicePath = CString(pDevice->szLetter) + ":\\";
				}

				m_listTransferDevice.AddTail(*pDevice);
				pDevice = pDevice->pNextDevice;
			}
		}
		
		AMBurn_Finalize();
	}
	else
	{
		/*#ifdef _LOG_DB
			CLogFileWriter::Get()->WriteLogLine("-> AMBURN: inizializzazione FALLITA!");
		#endif*/
		TRACE0("-> AMBURN: inizializzazione FALLITA!\n");
	}

	/////////
	// --- //
	/////////

	/*
	// EnableHtmlHelp(); // Sandro 10/02/2015 VS2013 //
	free((void*)m_pszHelpFilePath);

	m_pszHelpFilePath = _tcsdup(CString(m_sDirProg + "\\" + m_sNomeProgramma + ".chm"));
	*/

    CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(IDR_MAINFRAME, RUNTIME_CLASS(CEsamiDoc), RUNTIME_CLASS(CMainFrame), RUNTIME_CLASS(CEsamiView));

    AddDocTemplate(pDocTemplate);

	// Sandro 04/08/2016 // RIMA 16037.RN10 //

	m_bDicomWorklistActive = CWorkstationDicomWorklistConfSet().GetWorkstationState(m_sDicomWorklistAet, m_lDicomWorklistPort, m_bDicomWorklistLog);
	if (m_bDicomWorklistActive)
	{
		if (!CModalityWorklistSCP::Get()->Start(m_sDicomWorklistAet, m_lDicomWorklistPort, m_bDicomWorklistLog))
			theApp.AfxMessageBoxEndo(IDS_ERROR_MODALITYWORKLISTSCP_START);
	}

	//

	OnFileNew();
	if (m_pMainWnd == NULL)
		return FALSE;

	// Leggo queste configurazioni qui perché qui so che la UO è popolata

	CString sIdRobotDefault;
	sIdRobotDefault.Format("%s UO %li", szIdRobotDefault, theApp.m_lUO);
	m_lIdRobotDefault = GetPrivateProfileInt(szSettings, sIdRobotDefault, 0, m_sFileConfig);

	CString sCodiceDispVSDefault;
	sCodiceDispVSDefault.Format("%s UO %li", szCodiceDispositivoDefault, theApp.m_lUO);
	m_sCodiceDispositivoDefault = GetPrivateProfileString(szSettings, sCodiceDispVSDefault, "", m_sFileConfig);

	//
	return TRUE;
}

void CEndoxApp::DestroyAccessDialog()
{
	if (m_pAccessWnd)
	{
		m_pAccessWnd->DestroyWindow();
		delete m_pAccessWnd;
		m_pAccessWnd = NULL;
	}
}

void CEndoxApp::DestroyShowDbQueriesDialog()
{
	if (m_pShowDbQueriesWnd != NULL)
	{
		m_pShowDbQueriesWnd->DestroyWindow();
		delete m_pShowDbQueriesWnd;
		m_pShowDbQueriesWnd = NULL;
	}
}

INT CEndoxApp::ExitInstance()
{
	TRACE0("-> ExitInstance()\n");

	//
	if (m_bDicomWorklistActive)
		CModalityWorklistSCP::Get()->Stop();

	//
	GdiplusShutdown(m_gdiplusToken);

	//
	if (m_bLocalInit)
		AMLocalize_Finalize("Endox");

#ifdef _LOG_DB
	CLogFileWriter::Get()->CloseLogFile();
#endif // _LOG_DB //

	SaveSetting();
	CoUninitialize();
	Dead();

	return CWinApp::ExitInstance();
}

int CEndoxApp::Run()
{
#ifndef _DEBUG

	int iReturn = 0;

	try
	{
		iReturn = CWinApp::Run();
	}
	catch(...)
	{
		if (m_bSaveCompleteLog)
			CLogFileWriter::Get()->WriteLogLine0("CRASH !!!!!");
	}

	return iReturn;

#else

	return CWinApp::Run();

#endif
}

void CEndoxApp::LoadSetting() 
{
	TRACE0("-> LoadSetting()\n");

	m_nLanguage = (languages)GetPrivateProfileInt(szSettings, "Language", 0, m_sFileConfig);

	m_bAutoDeselect = GetPrivateProfileInt(szSettings, "Auto deselect", 0, m_sFileConfig);

	CImageDlg::m_nShowMode = GetPrivateProfileInt(szSettings, szShowImage, 2, m_sFileConfig);
	CImageSimpleDlg::m_nShowMode = GetPrivateProfileInt(szSettings, szShowImageSimple, 2, m_sFileConfig);
	CPdfAnteprimaDlg::m_lDefaultZoomValue = (long)GetPrivateProfileInt(szSettings, szPdfAnteprimaDefaultZoomValue, 100, m_sFileConfig);

	m_sEseguiComando = GetPrivateProfileString(szSettings, szEseguiComando, "\"C:\\Programmi\\Internet Explorer\\iexplore.exe\" http://www.tesi.mi.it/", m_sFileConfig);
	m_sAgendaIndex = GetPrivateProfileString(szSettings, szAgendaIndex, "", m_sFileConfig);

	m_lSaltaControlloVersione = GetPrivateProfileInt(szSettings, szSaltaControlloVersione, 0, m_sFileConfig);
	m_lIDSedeEsameDefault = GetPrivateProfileInt(szSettings, szIDSedeEsameDefault, 0, m_sFileConfig);
	m_sSalaEsameDefault = GetPrivateProfileString(szSettings, szSalaEsameDefault, "", m_sFileConfig);

	m_nFieldToFilterOnTransfer = GetPrivateProfileInt(szSettings, szFieldToFilterOnTransfer, -1, m_sFileConfig);
	m_sFilterOnTransfer = GetPrivateProfileString(szSettings, szFilterOnTransfer, "", m_sFileConfig);

	m_sDirTempAcq = GetPrivateProfileString(szSettings, szDirTempAcq, "", m_sFileConfig);
	m_sDirTempAcq2 = GetPrivateProfileString(szSettings, szDirTempAcq2, "", m_sFileConfig);
	m_sPathImageOD = GetPrivateProfileString(szSettings, szODPath, "X:", m_sFileConfig);

	m_sBadgeReaderAddress = GetPrivateProfileString(szSettings, szBadgeReaderAddress, "",    m_sFileConfig);
	m_nBadgeReaderPort    = GetPrivateProfileInt   (szSettings, szBadgeReaderPort,    10001, m_sFileConfig);
	m_nBadgeReaderTimeout = GetPrivateProfileInt   (szSettings, szBadgeReaderTimeout, 5,     m_sFileConfig);
	m_bSkipBadge =		   (GetPrivateProfileInt   (szSettings, szSkipBadge,		  0,     m_sFileConfig) == 1);

	m_bTerminalServer =	   (GetPrivateProfileInt   (szSettings, szTerminalServer,	  0,     m_sFileConfig) == 1);

	m_bSaveCompleteLog = (GetPrivateProfileInt(szSettings, szSaveCompleteLog, 0, m_sFileConfig) != 0);
	m_sSaveCompleteLogIpDb = GetPrivateProfileString(szSettings, szSaveCompleteLogIpDb, "", m_sFileConfig);
	m_sSaveCompleteLogIpImm = GetPrivateProfileString(szSettings, szSaveCompleteLogIpImm, "", m_sFileConfig);
	m_lSaveCompleteLogDays = GetPrivateProfileInt(szSettings, szSaveCompleteLogDays, 10, m_sFileConfig);
	m_lSaveCompleteLogThreshold = GetPrivateProfileInt(szSettings, szSaveCompleteLogThreshold, 500, m_sFileConfig);

	m_enumScannerConnectionType = (ScannerConnectionType)GetPrivateProfileInt(szSettings, szTipoScannerCollegato, ScannerConnectionType::twain, m_sFileConfig);

	m_bShowDbQueries = (GetPrivateProfileInt(szSettings, szShowDbQueries, 0, m_sFileConfig) != 0);
	m_lShowDbQueriesThreshold = GetPrivateProfileInt(szSettings, szShowDbQueriesThreshold, 500, m_sFileConfig);

	m_lWorklistFattoreIngrandimento = GetPrivateProfileInt(szSettings, szWorklistFattoreIngrandimento, 100, m_sFileConfig);
	m_lWorklistStatoDaSelezionare = GetPrivateProfileInt(szSettings, szWorklistStatoDaSelezionare, LPC_STATO_ACCETTATA, m_sFileConfig);

	if (m_lWorklistFattoreIngrandimento < 100)
		m_lWorklistFattoreIngrandimento = 100;
	if (m_lWorklistFattoreIngrandimento > 500)
		m_lWorklistFattoreIngrandimento = 500;

	g_nLastUse = GetPrivateProfileInt(szContrastElaboration, szLastUse, 0, m_sFileConfig);
	g_nContrastMinLev[0] = GetPrivateProfileInt(szContrastElaboration, szBlackLevInt, 0, m_sFileConfig);
	g_nContrastMaxLev[0] = GetPrivateProfileInt(szContrastElaboration, szWhiteLevInt, 255, m_sFileConfig);
	g_nContrastMinLev[1] = GetPrivateProfileInt(szContrastElaboration, szBlackLevR, 0, m_sFileConfig);
	g_nContrastMaxLev[1] = GetPrivateProfileInt(szContrastElaboration, szWhiteLevR, 255, m_sFileConfig);
	g_nContrastMinLev[2] = GetPrivateProfileInt(szContrastElaboration, szBlackLevG, 0, m_sFileConfig);
	g_nContrastMaxLev[2] = GetPrivateProfileInt(szContrastElaboration, szWhiteLevG, 255, m_sFileConfig);
	g_nContrastMinLev[3] = GetPrivateProfileInt(szContrastElaboration, szBlackLevB, 0, m_sFileConfig);
	g_nContrastMaxLev[3] = GetPrivateProfileInt(szContrastElaboration, szWhiteLevB, 255, m_sFileConfig);
	g_nBlackLev = GetPrivateProfileInt(szContrastElaboration, szBlackLev, 0, m_sFileConfig);
	g_nWhiteLev = GetPrivateProfileInt(szContrastElaboration, szWhiteLev, 255, m_sFileConfig);

	g_nBrightnessLev = GetPrivateProfileInt(szBrightnessElaboration,szBrightLev,	0, m_sFileConfig);

	g_sReportFaceName = GetPrivateProfileString(szReport, szReportFaceName,	"Tahoma", m_sFileConfig);
	g_nReportSize = GetPrivateProfileInt(szReport, szReportSize, 10, m_sFileConfig);
	g_bReportUnderline = GetPrivateProfileInt(szReport, szReportUnderline, 0, m_sFileConfig) > 0 ? TRUE : FALSE;
	g_bReportBold = GetPrivateProfileInt(szReport, szReportBold, 0, m_sFileConfig) > 0 ? TRUE : FALSE;
	g_bReportItalic = GetPrivateProfileInt(szReport, szReportItalic, 0, m_sFileConfig) > 0 ? TRUE : FALSE;

	// m_nTypePrintImage = GetPrivateProfileInt(szPrintPage, szTypePrint, 3,  m_sFileConfig);
	m_lStampaImmaginiIDHeaderLocal = GetPrivateProfileInt(szPrintPage, szIDHeader, 0, m_sFileConfig);
	m_lStampaImmaginiIDFooterLocal = GetPrivateProfileInt(szPrintPage, szIDFooter, 0, m_sFileConfig);
	// m_bPrintComment = GetPrivateProfileInt(szPrintPage, szPrintComment,	 TRUE, m_sFileConfig);
	// m_bPrintPatientData = GetPrivateProfileInt(szPrintPage, szPrintPatientData,	TRUE, m_sFileConfig);
	// m_nDistanzaImmagini = GetPrivateProfileInt(szPrintPage, szPrintSeparaImmagini, 0, m_sFileConfig);

	m_sHeaderPrintImage = GetPrivateProfileString(szPrintPage, szHeaderPrint, " " + m_sNomeProgramma + " - Tesi Imaging ", m_sFileConfig);

	m_fEtichette00 = (float)atof(GetPrivateProfileString(szEtichette, szMargineX, "1.0", m_sFileConfig));
	m_fEtichette01 = (float)atof(GetPrivateProfileString(szEtichette, szMargineY, "1.5", m_sFileConfig));
	m_fEtichette02 = (float)atof(GetPrivateProfileString(szEtichette, szScalaX, "1.00", m_sFileConfig));
	m_fEtichette03 = (float)atof(GetPrivateProfileString(szEtichette, szScalaY, "1.00", m_sFileConfig));

	m_bCheckRep = GetPrivateProfileInt(szPercorsi, szCheckRep, 0, m_sFileConfig);
	m_bCheckImm = GetPrivateProfileInt(szPercorsi, szCheckImm, 0, m_sFileConfig);
	m_sEditRep = GetPrivateProfileString(szPercorsi, szEditRep, "C:\\", m_sFileConfig);
	m_sEditImm = GetPrivateProfileString(szPercorsi, szEditImm, "C:\\", m_sFileConfig);
	m_sExportFolder = GetPrivateProfileString(szPercorsi, szExportFolder, "C:\\", m_sFileConfig);
	
	m_nQFactorExp = GetPrivateProfileInt(szOptions, szQFactorExp, 50, m_sFileConfig);
	m_nExpFormat = GetPrivateProfileInt(szOptions, szExpFormat, 0, m_sFileConfig);

	m_sStoreScpPorta = GetPrivateProfileString(szPercorsi, szStoreScpPorta, "50000", m_sFileConfig);
	m_sStoreScpExecOnReceptionExe = GetPrivateProfileString(szPercorsi, szStoreScpExecOnReceptionExe, "MoveFile.exe", m_sFileConfig);
	m_sStoreScpExecOnReceptionParameters = GetPrivateProfileString(szPercorsi, szStoreScpExecOnReceptionParameters, "", m_sFileConfig);

	// Opzione visualizzazione remoto //
	m_bVisAbilita = GetPrivateProfileInt(szSettings, szVRAbilita, 0, m_sFileConfig);
	m_bVisAbilitaMonitor = GetPrivateProfileInt(szSettings, szVRAbilitaMonitor, 0, m_sFileConfig);
	m_sVisIp = GetPrivateProfileString(szSettings, szVRIP, "0.0.0.0", m_sFileConfig);
	m_lVisPorta = GetPrivateProfileInt(szSettings, szVRPorta, 0, m_sFileConfig);
	m_sVisPortaMonitor = GetPrivateProfileString(szSettings, szVRPortaMonitor, "", m_sFileConfig);

	m_sPathVLC = GetPrivateProfileString(szSettings, szPathVLC, "", m_sFileConfig);
	m_iUseVLC = GetPrivateProfileInt(szSettings, szVLC, 0, m_sFileConfig);
	m_sPathTCMS = GetPrivateProfileString(szSettings, szPathTCMS, "", m_sFileConfig);
	m_iUseTCMS = GetPrivateProfileInt(szSettings, szTCMS, 0, m_sFileConfig);

	m_sSMTP = GetPrivateProfileString(szSettings, szSMTP,"smtp.tesi.mi.it", m_sFileConfig);

	m_nSMTPLogin = GetPrivateProfileInt(szSettings, szSMTPLogin,0, m_sFileConfig);
	m_strSMTPUser = GetPrivateProfileString(szSettings, szSMTPUser,"", m_sFileConfig);
	m_strSMTPPassword = GetPrivateProfileString(szSettings, szSMTPPassword,"", m_sFileConfig);

	m_sRicetteEngeneeringExe = GetPrivateProfileString(szSettings, szEngeneeringRicetteExe, "", m_sFileConfig);

	m_lOpenIntoMonitor = GetPrivateProfileInt(szSettings, szOpenIntoMonitor, 0, m_sFileConfig);
	
	m_sConnStrContigencia = GetPrivateProfileString(szODBCSettings, szDSNContingencia, "", m_sFileConfig); //Julio BUG 3456 - Contingencia	
	/*if (m_sConnStrContigencia.IsEmpty())
		WritePrivateProfileString(szODBCSettings, szDSNContingencia, "driver={sql server};server=SVW12MRMTESI\\SQLEXPRESS,17001;uid=sa;pwd=N@utilus2015;database=TESICAPTURE", m_sFileConfig); //Julio BUG 3456 - Contingencia*/
	// --- //

	m_iIEBrightness = GetPrivateProfileInt(szImageElaboration, szImageElaborationBrightness, 0, m_sFileConfig);
	if (m_iIEBrightness < -255)
		m_iIEBrightness = -255;
	if (m_iIEBrightness > 255)
		m_iIEBrightness = 255;

	m_iIEContrastRMin = GetPrivateProfileInt(szImageElaboration, szImageElaborationContrastRMin, 0, m_sFileConfig);
	if (m_iIEContrastRMin < 0)
		m_iIEContrastRMin = 0;
	if (m_iIEContrastRMin > 255)
		m_iIEContrastRMin = 255;

	m_iIEContrastRMax = GetPrivateProfileInt(szImageElaboration, szImageElaborationContrastRMax, 255, m_sFileConfig);
	if (m_iIEContrastRMax < 0)
		m_iIEContrastRMax = 0;
	if (m_iIEContrastRMax > 255)
		m_iIEContrastRMax = 255;

	m_iIEContrastGMin = GetPrivateProfileInt(szImageElaboration, szImageElaborationContrastGMin, 0, m_sFileConfig);
	if (m_iIEContrastGMin < 0)
		m_iIEContrastGMin = 0;
	if (m_iIEContrastGMin > 255)
		m_iIEContrastGMin = 255;

	m_iIEContrastGMax = GetPrivateProfileInt(szImageElaboration, szImageElaborationContrastGMax, 255, m_sFileConfig);
	if (m_iIEContrastGMax < 0)
		m_iIEContrastGMax = 0;
	if (m_iIEContrastGMax > 255)
		m_iIEContrastGMax = 255;

	m_iIEContrastBMin = GetPrivateProfileInt(szImageElaboration, szImageElaborationContrastBMin, 0, m_sFileConfig);
	if (m_iIEContrastBMin < 0)
		m_iIEContrastBMin = 0;
	if (m_iIEContrastBMin > 255)
		m_iIEContrastBMin = 255;

	m_iIEContrastBMax = GetPrivateProfileInt(szImageElaboration, szImageElaborationContrastBMax, 255, m_sFileConfig);
	if (m_iIEContrastBMax < 0)
		m_iIEContrastBMax = 0;
	if (m_iIEContrastBMax > 255)
		m_iIEContrastBMax = 255;
}

void CEndoxApp::SaveSetting() 
{
	CString strTemp;

	TRACE0("-> SaveSetting()\n");

	WritePrivateProfileInt(szSettings, "Language", (int)m_nLanguage, m_sFileConfig);

	WritePrivateProfileInt(szSettings, "Auto deselect", m_bAutoDeselect, m_sFileConfig);

	WritePrivateProfileInt(szSettings, szShowImage, CImageDlg::m_nShowMode, m_sFileConfig);
	WritePrivateProfileInt(szSettings, szShowImageSimple, CImageSimpleDlg::m_nShowMode, m_sFileConfig);
	WritePrivateProfileInt(szSettings, szPdfAnteprimaDefaultZoomValue, (int)CPdfAnteprimaDlg::m_lDefaultZoomValue, m_sFileConfig);

	WritePrivateProfileString(szSettings, szDirTempAcq, m_sDirTempAcq, m_sFileConfig);
	WritePrivateProfileString(szSettings, szDirTempAcq2, m_sDirTempAcq2, m_sFileConfig);
	WritePrivateProfileString(szSettings, szODPath, m_sPathImageOD, m_sFileConfig);

	WritePrivateProfileString(szSettings, szEseguiComando, m_sEseguiComando, m_sFileConfig);
	WritePrivateProfileString(szSettings, szAgendaIndex, m_sAgendaIndex, m_sFileConfig);

	WritePrivateProfileInt	 (szSettings, szSaltaControlloVersione, m_lSaltaControlloVersione, m_sFileConfig);
	WritePrivateProfileInt	 (szSettings, szIDSedeEsameDefault, m_lIDSedeEsameDefault, m_sFileConfig);
	WritePrivateProfileString(szSettings, szSalaEsameDefault, m_sSalaEsameDefault, m_sFileConfig);

	WritePrivateProfileString(szSettings, szBadgeReaderAddress, m_sBadgeReaderAddress,	m_sFileConfig);
	WritePrivateProfileInt   (szSettings, szBadgeReaderPort,    m_nBadgeReaderPort,		m_sFileConfig);
	WritePrivateProfileInt   (szSettings, szBadgeReaderTimeout, m_nBadgeReaderTimeout,	m_sFileConfig);
	WritePrivateProfileInt   (szSettings, szSkipBadge,			(m_bSkipBadge ? 1 : 0),	m_sFileConfig);

	WritePrivateProfileInt   (szSettings, szTerminalServer,		(m_bTerminalServer ? 1 : 0), m_sFileConfig);

	WritePrivateProfileInt   (szSettings, szSaveCompleteLog, (m_bSaveCompleteLog ? 1 : 0), m_sFileConfig);
	WritePrivateProfileString(szSettings, szSaveCompleteLogIpDb, m_sSaveCompleteLogIpDb, m_sFileConfig);
	WritePrivateProfileString(szSettings, szSaveCompleteLogIpImm, m_sSaveCompleteLogIpImm, m_sFileConfig);
	WritePrivateProfileInt   (szSettings, szSaveCompleteLogDays, m_lSaveCompleteLogDays, m_sFileConfig);
	WritePrivateProfileInt   (szSettings, szSaveCompleteLogThreshold, m_lSaveCompleteLogThreshold, m_sFileConfig);

	WritePrivateProfileInt(szSettings, szTipoScannerCollegato, m_enumScannerConnectionType, m_sFileConfig);

	WritePrivateProfileInt(szSettings, szShowDbQueries, (m_bShowDbQueries ? 1 : 0), m_sFileConfig);
	WritePrivateProfileInt(szSettings, szShowDbQueriesThreshold, m_lShowDbQueriesThreshold, m_sFileConfig);

	WritePrivateProfileInt(szSettings, szWorklistFattoreIngrandimento, m_lWorklistFattoreIngrandimento, m_sFileConfig);
	WritePrivateProfileInt(szSettings, szWorklistStatoDaSelezionare, m_lWorklistStatoDaSelezionare, m_sFileConfig);

	WritePrivateProfileInt(szContrastElaboration, szLastUse, g_nLastUse, m_sFileConfig);
	WritePrivateProfileInt(szContrastElaboration, szBlackLevInt, g_nContrastMinLev[0], m_sFileConfig);
	WritePrivateProfileInt(szContrastElaboration, szWhiteLevInt, g_nContrastMaxLev[0], m_sFileConfig);
	WritePrivateProfileInt(szContrastElaboration, szBlackLevR, g_nContrastMinLev[1], m_sFileConfig);
	WritePrivateProfileInt(szContrastElaboration, szWhiteLevR, g_nContrastMaxLev[1], m_sFileConfig);
	WritePrivateProfileInt(szContrastElaboration, szBlackLevG, g_nContrastMinLev[2], m_sFileConfig);
	WritePrivateProfileInt(szContrastElaboration, szWhiteLevG, g_nContrastMaxLev[2], m_sFileConfig);
	WritePrivateProfileInt(szContrastElaboration, szBlackLevB, g_nContrastMinLev[3], m_sFileConfig);
	WritePrivateProfileInt(szContrastElaboration, szWhiteLevB, g_nContrastMaxLev[3], m_sFileConfig);
	WritePrivateProfileInt(szContrastElaboration, szBlackLev, g_nBlackLev, m_sFileConfig);
	WritePrivateProfileInt(szContrastElaboration, szWhiteLev, g_nWhiteLev, m_sFileConfig);

	WritePrivateProfileInt(szBrightnessElaboration, szBrightLev, g_nBrightnessLev, m_sFileConfig);
	
	WritePrivateProfileString(szReport, szReportFaceName, g_sReportFaceName, m_sFileConfig);
	WritePrivateProfileInt(szReport, szReportSize, g_nReportSize, m_sFileConfig);
	WritePrivateProfileInt(szReport, szReportUnderline, (g_bReportUnderline == FALSE ? 0 : 1), m_sFileConfig);
	WritePrivateProfileInt(szReport, szReportBold, (g_bReportBold == FALSE ? 0 : 1), m_sFileConfig);
	WritePrivateProfileInt(szReport, szReportItalic, (g_bReportItalic == FALSE ? 0 : 1), m_sFileConfig);

	// stampa immagini...
	// WritePrivateProfileInt(szPrintPage, szTypePrint, m_nTypePrintImage, m_sFileConfig);
	WritePrivateProfileInt(szPrintPage, szIDHeader, m_lStampaImmaginiIDHeaderLocal, m_sFileConfig);
	WritePrivateProfileInt(szPrintPage, szIDFooter, m_lStampaImmaginiIDFooterLocal, m_sFileConfig);
	// WritePrivateProfileInt(szPrintPage, szPrintComment, m_bPrintComment, m_sFileConfig);
	// WritePrivateProfileInt(szPrintPage, szPrintPatientData, m_bPrintPatientData, m_sFileConfig);
	// WritePrivateProfileInt(szPrintPage, szPrintSeparaImmagini, m_nDistanzaImmagini, m_sFileConfig);

	strTemp.Format("%.1f", m_fEtichette00);
	WritePrivateProfileString(szEtichette, szMargineX, strTemp, m_sFileConfig);
	strTemp.Format("%.1f", m_fEtichette01);
	WritePrivateProfileString(szEtichette, szMargineY, strTemp, m_sFileConfig);
	strTemp.Format("%.2f", m_fEtichette02);
	WritePrivateProfileString(szEtichette, szScalaX, strTemp, m_sFileConfig);
	strTemp.Format("%.2f", m_fEtichette03);
	WritePrivateProfileString(szEtichette, szScalaY, strTemp, m_sFileConfig);

	// Sandro Gallina - 18/03/2004 -->
	WritePrivateProfileInt(szPercorsi, szCheckRep, m_bCheckRep, m_sFileConfig);
	WritePrivateProfileInt(szPercorsi, szCheckImm, m_bCheckImm, m_sFileConfig);
	WritePrivateProfileString(szPercorsi, szEditRep, m_sEditRep, m_sFileConfig);
	WritePrivateProfileString(szPercorsi, szEditImm, m_sEditImm, m_sFileConfig);

	WritePrivateProfileString(szPercorsi, szExportFolder, m_sExportFolder, m_sFileConfig);
	// <-- Sandro Gallina - 18/03/2004

	WritePrivateProfileInt(szOptions, szQFactorExp, m_nQFactorExp, m_sFileConfig);
	WritePrivateProfileInt(szOptions, szExpFormat, m_nExpFormat, m_sFileConfig);

	WritePrivateProfileString(szPercorsi, szStoreScpPorta, m_sStoreScpPorta, m_sFileConfig);
	WritePrivateProfileString(szPercorsi, szStoreScpExecOnReceptionExe, m_sStoreScpExecOnReceptionExe, m_sFileConfig);
	WritePrivateProfileString(szPercorsi, szStoreScpExecOnReceptionParameters, m_sStoreScpExecOnReceptionParameters, m_sFileConfig);

	// Opzione visualizzazione remoto //
	WritePrivateProfileInt(szSettings, szVRAbilita, m_bVisAbilita, m_sFileConfig);
	WritePrivateProfileString(szSettings, szVRIP, m_sVisIp, m_sFileConfig);
	WritePrivateProfileInt(szSettings, szVRPorta, m_lVisPorta, m_sFileConfig);
	WritePrivateProfileInt(szSettings, szVRAbilitaMonitor, m_bVisAbilitaMonitor, m_sFileConfig);
	WritePrivateProfileString(szSettings, szVRPortaMonitor, m_sVisPortaMonitor, m_sFileConfig);

	// mail //
	WritePrivateProfileString(szSettings, szSMTP, m_sSMTP, m_sFileConfig);
	WritePrivateProfileInt(szSettings, szSMTPLogin, m_nSMTPLogin, m_sFileConfig);
	WritePrivateProfileString(szSettings, szSMTPUser, m_strSMTPUser, m_sFileConfig);
	WritePrivateProfileString(szSettings, szSMTPPassword, m_strSMTPPassword, m_sFileConfig);

	WritePrivateProfileString(szSettings, szEngeneeringRicetteExe, m_sRicetteEngeneeringExe, m_sFileConfig);

	WritePrivateProfileInt(szSettings, szOpenIntoMonitor, m_lOpenIntoMonitor, m_sFileConfig);

	// vlc tcms //
	WritePrivateProfileString(szSettings, szPathVLC, m_sPathVLC, m_sFileConfig);
	WritePrivateProfileInt(szSettings, szVLC, m_iUseVLC, m_sFileConfig);
	WritePrivateProfileString(szSettings, szPathTCMS, m_sPathTCMS, m_sFileConfig);
	WritePrivateProfileInt(szSettings, szTCMS,m_iUseTCMS, m_sFileConfig);
 
	// --- //
	WritePrivateProfileInt(szImageElaboration, szImageElaborationBrightness, m_iIEBrightness, m_sFileConfig);
	WritePrivateProfileInt(szImageElaboration, szImageElaborationContrastRMin, m_iIEContrastRMin, m_sFileConfig);
	WritePrivateProfileInt(szImageElaboration, szImageElaborationContrastRMax, m_iIEContrastRMax, m_sFileConfig);
	WritePrivateProfileInt(szImageElaboration, szImageElaborationContrastGMin, m_iIEContrastGMin, m_sFileConfig);
	WritePrivateProfileInt(szImageElaboration, szImageElaborationContrastGMax, m_iIEContrastGMax, m_sFileConfig);
	WritePrivateProfileInt(szImageElaboration, szImageElaborationContrastBMin, m_iIEContrastBMin, m_sFileConfig);
	WritePrivateProfileInt(szImageElaboration, szImageElaborationContrastBMax, m_iIEContrastBMax, m_sFileConfig);	
}

void CEndoxApp::GetPrivateProfileFont(LPCSTR szSec, LOGFONT* plf, int DimHeight)
{
	plf->lfHeight = GetPrivateProfileInt(szSec, szHeight, DimHeight, m_sFileConfig);
	plf->lfWeight = GetPrivateProfileInt(szSec, szWeight, 400, m_sFileConfig);
	plf->lfItalic = (BYTE)GetPrivateProfileInt(szSec, szItalic, 0, m_sFileConfig);
	plf->lfUnderline = (BYTE)GetPrivateProfileInt(szSec, szUnderline, 0, m_sFileConfig);
	plf->lfPitchAndFamily = (BYTE)GetPrivateProfileInt(szSec, szPitchAndFamily, 49, m_sFileConfig); //VARIABLE_PITCH | FF_ROMAN);
	CString strFont = GetPrivateProfileString(szSec, szFaceName, "Courier New", m_sFileConfig);
	strcpy_s(plf->lfFaceName, strFont);
}

void CEndoxApp::WritePrivateProfileFont(LPCSTR szSec, const LOGFONT* plf, LOGFONT* plfOld)
{
	WritePrivateProfileInt(szSec, szHeight, plf->lfHeight, m_sFileConfig);
	WritePrivateProfileInt(szSec, szWeight, plf->lfWeight, m_sFileConfig);
	WritePrivateProfileInt(szSec, szItalic, plf->lfItalic, m_sFileConfig);
	WritePrivateProfileInt(szSec, szUnderline, plf->lfUnderline, m_sFileConfig);
	WritePrivateProfileInt(szSec, szPitchAndFamily, plf->lfPitchAndFamily, m_sFileConfig);
	WritePrivateProfileString(szSec, szFaceName, (LPCSTR)plf->lfFaceName, m_sFileConfig);
}

BOOL CALLBACK EndoxEnumProc(HWND hWnd, LPARAM lParam)
{
	CHAR szBuffer[MAX_PATH];
	ZeroMemory(szBuffer, MAX_PATH * sizeof(CHAR));
	::GetWindowText(hWnd, szBuffer, MAX_PATH);

	if (strstr(szBuffer, _TESIIMAGING_PREFIX) != NULL)
	{
		if (!::IsIconic(hWnd))
			PostMessage(hWnd, WM_SYSCOMMAND, SC_MINIMIZE, NULL);

		PostMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE, NULL);

		return FALSE;
	}

	return TRUE;
}

VOID CEndoxApp::PosOnTop()
{
#if 0
	CString strTitle = GetAppTitle(0);
	strTitle = CString(" - ") + strTitle;
	HWND hWnd = FindWindow(strTitle, NULL);
	if ((hWnd != NULL) &&
		(hWnd != INVALID_HANDLE_VALUE)) {
		if (!::IsIconic(hWnd))
			PostMessage(hWnd, 
						WM_SYSCOMMAND, 
						SC_MINIMIZE, NULL);

			PostMessage(hWnd, 
						WM_SYSCOMMAND, 
						SC_RESTORE, NULL);

		}
#else

	HANDLE hEnumMutex = CreateMutex(NULL,
									FALSE,
									"EnumMutex");

	DWORD dwWaitResult = WaitForSingleObject(hEnumMutex, 500L);
 
    switch (dwWaitResult) 
    {
        case WAIT_OBJECT_0: 
            __try { 
					BOOL bContinue = TRUE;
					while (bContinue) {
						bContinue = EnumWindows(EndoxEnumProc, NULL);
					}
            } 
            __finally { 
                if (!ReleaseMutex(hEnumMutex)) 
                { 
                   AfxMessageBoxEndo("ReleaseMutex");
                } 
            } 
		break;
    }

	CloseHandle(hEnumMutex);

#endif
	
}

BOOL CEndoxApp::AlreadyLiving()
{
	// Sandro 15/03/2017 // connessione in mobilità... //

	if (!m_sPassedConnectionString.IsEmpty())
		return FALSE;

	//

	if ((m_hMutexLive != NULL) &&
		(m_hMutexLive != INVALID_HANDLE_VALUE))
		 return TRUE;

	m_hMutexLive = OpenMutex(MUTEX_ALL_ACCESS,
							 FALSE,
							 _ENDOX_MUTEX);

	if ((m_hMutexLive != NULL) &&
		(m_hMutexLive != INVALID_HANDLE_VALUE))
		 return TRUE;

	return FALSE;
}

BOOL CEndoxApp::Live()
{
	/* Sandro 15/03/2017 // connessione in mobilità... //

	if (!m_sPassedConnectionString.IsEmpty())
	{
		m_hMutexLive = OpenMutex(MUTEX_ALL_ACCESS,
			FALSE,
			_ENDOX_MUTEX);
	}

	*/

	m_hMutexLive = CreateMutex(NULL,
							   TRUE,
							   _ENDOX_MUTEX);

	if ((m_hMutexLive == INVALID_HANDLE_VALUE) ||
		(m_hMutexLive == NULL))
		return FALSE;

	return TRUE;
}

VOID CEndoxApp::Dead()
{
	CloseHandle(m_hMutexLive);
	m_hMutexLive = NULL;
}

CString CEndoxApp::GetAppTitle(long lFormatStyle)
{
	CString sReturn = "";

	ReadExeData();

	switch(lFormatStyle)
	{
		case 0: // USADO NA Classe: CEsamiView | Métodos: ChiudiFase_CambioUtente(), ChiudiFase_CambioUtente(), OnInitialUpdate(), RicaricaDatiDopoCambioUO(), Logout()
		{
			sReturn = CString(_TESIIMAGING_PREFIX) + " " + m_sNomeProgramma + " " + m_sVersioneFull + " - ";

			//

			m_sUtenteLoggato.Trim();
			if (!m_sUtenteLoggato.IsEmpty())
			{
				CString sUser;
				sUser.Format("%s: %s - ", GetMessageString(IDS_UTENTE), m_sUtenteLoggato);
				sUser.MakeUpper();

				sReturn += sUser;
			}

			//

			if (!m_bUOVisualizzaAngoloAltoDestra)
			{
				if (CUOSet().ExistMoreThanOneUO())
				{
					CString sUOTemp = CUOSet().GetDescrizione(m_lUO);
					sUOTemp.Trim();

					if (!sUOTemp.IsEmpty())
					{
						CString sUO;
						sUO.Format("%s: %s - ", GetMessageString(IDS_UO), sUOTemp);
						sUO.MakeUpper();

						sReturn += sUO;
					}
				}
			}

			//

			if (theApp.m_bPersonalizzazioniBrasileCamargo || m_bPersonalizzazioniBrasileEinstein || m_bPersonalizzazioniBrasileFleury || m_bPersonalizzazioniBrasileSirio)
			{
				long lUserID = 0;
				AMLogin_GetUserID(&lUserID);

				long lIDMedico = CMediciSet().GetContatoreFromUserID(lUserID);

				if (CVistaEsamiPendentiSet().MedicoHasEsamiAperti(lIDMedico))
					sReturn += GetMessageString(IDS_PRESENTI_ESAMI_DA_CHIUDERE) + " - ";
			}

			//

			break;
		}
		case 1: // USADO NO CAboutBoxDlg::OnInitDialog()
		{
			if (!m_sNumBuild.IsEmpty() && !m_sDataBuild.IsEmpty())
				sReturn = m_sNomeProgramma + " " + m_sVersione + "." + m_sNumBuild + " (" + m_sDataBuild + ") - Copyright © 2020 by...";
			else
				sReturn = m_sNomeProgramma + " " + m_sVersione + " - Copyright © 2020 by...";

			break;
		}
		case 2: // USADO NO CPdfStampaDlg::OnTimer()
		{
			sReturn = m_sNomeProgramma + " " + m_sVersione + " - " + GetMessageString(IDS_PRINTING);
			break;
		}
		case 3: // USADO NO CEsamiView::OnInitialUpdate()
		{
			int nPoint = m_sVersione.ReverseFind('.');
			if (nPoint > 0)
				sReturn = m_sVersione.Left(nPoint);
			else
				sReturn = m_sVersione;
			break;
		}
		default:
		{
			sReturn = CString(_TESIIMAGING_PREFIX) + " " + m_sNomeProgramma + " " + m_sVersione + " -";
			break;
		}
	}

	return sReturn;
}

void CEndoxApp::ReadExeData()
{
	m_sVersione = "";
	m_sNumBuild = "";
	m_sDataBuild = "";

	BYTE*	pVersionInfo;
	char	szModuleName[255];
	UINT	nLen;
	int		nSize;
	CString	strFileVersion = "";
	CString	strFileData = "";
	ULONG	nHandle = 0;

	if (GetModuleFileName(AfxGetInstanceHandle(), szModuleName, sizeof(szModuleName)) <= 0)
		return;

	if ((nSize = GetFileVersionInfoSize(szModuleName, &nHandle)) <= 0)
		return;

	pVersionInfo = new BYTE[nSize+2];

	if (!GetFileVersionInfo(szModuleName, nHandle, nSize, pVersionInfo))
	{
		delete pVersionInfo;
		return;
	}

	short *pSubBlock = NULL;
	nLen = 0;

	if (!VerQueryValue(pVersionInfo, "\\VarFileInfo\\Translation", (void**) &pSubBlock, &nLen))
	{
		delete pVersionInfo;
		return;
	}
	 
	CString strPv;
	strPv.Format("\\StringFileInfo\\%04x%04x\\ProductVersion", pSubBlock[0], pSubBlock[1]);

	short *pFileVersion = NULL;
	nLen = 0;

	//Preleva le informazioni su n. versione
	if (!VerQueryValue(pVersionInfo, strPv.GetBuffer(strPv.GetLength()), (void **) &pFileVersion, &nLen))
	{
		delete pVersionInfo;
		return;
	}
	strFileVersion = CString((unsigned char*)pFileVersion);	
	m_sVersioneFull = strFileVersion;

	int iTemp = strFileVersion.Find('.');
	int iTempPrev;
	if (iTemp >= 0)
	{
		m_sVersione = strFileVersion.Left(iTemp);
		iTempPrev = iTemp + 1;

		iTemp = strFileVersion.Find('.', iTempPrev);
		if (iTemp >= 0)
		{
			m_sVersione += "." + strFileVersion.Mid(iTempPrev, iTemp - iTempPrev);
			iTempPrev = iTemp + 1;

			iTemp = strFileVersion.Find('.', iTempPrev);
			if (iTemp >= 0)
			{
				m_sVersione += "." + strFileVersion.Mid(iTempPrev, iTemp - iTempPrev);
				iTempPrev = iTemp + 1;

				m_sNumBuild.Format("%d", atoi(strFileVersion.Right(strFileVersion.GetLength() - iTempPrev)));
			}
			else
			{
				m_sVersione += "." + strFileVersion.Right(strFileVersion.GetLength() - iTempPrev);

				m_sNumBuild = "0";
			}
		}
	}

	CString strSb;
	// strSb.Format("\\StringFileInfo\\%04x%04x\\BuildDate", pSubBlock[0], pSubBlock[1]);
	strSb.Format("\\StringFileInfo\\%04x%04x\\PrivateBuild", pSubBlock[0], pSubBlock[1]);

	*pFileVersion = NULL;
	nLen = 0;

	//Preleva le informazioni su data release
	if (!VerQueryValue(pVersionInfo, strSb.GetBuffer(strSb.GetLength()), (void **) &pFileVersion, &nLen))
	{
		delete pVersionInfo;
		return;
	}

	strFileData = CString((unsigned char*)pFileVersion);
	if (strFileData.GetLength() == 10)
	{
		// m_sDataBuild.Format("%s/%s/%s", strFileData.Right(2), strFileData.Mid(5, 2), strFileData.Left(4));
		m_sDataBuild = strFileData;
	}

	delete pVersionInfo;
}

void CEndoxApp::SetFont()
{
	LOGFONT lf;

	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf.lfEscapement = 0;
	memcpy(lf.lfFaceName, CString("TAHOMA").GetBuffer(LF_FACESIZE), LF_FACESIZE);
	lf.lfItalic = FALSE;
	lf.lfOrientation = 0;
	lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
	lf.lfPitchAndFamily = FF_DONTCARE;
	lf.lfQuality = CLEARTYPE_QUALITY;
	lf.lfStrikeOut = FALSE;
	lf.lfUnderline = FALSE;

	// font per disegno interfaccia operatore
	lf.lfWeight = FW_BOLD;
	lf.lfWidth = 5;
	lf.lfHeight = 12;
	m_fontReport.CreateFontIndirect(&lf);

	// font della dimensione base
	lf.lfWeight = FW_NORMAL;
	lf.lfWidth = 6;
	lf.lfHeight = 16;
	m_fontNormal.CreateFontIndirect(&lf);

	// font bold della dimensione base
	lf.lfWeight = FW_BOLD;
	m_fontBold.CreateFontIndirect(&lf);

	// font bold grande
	lf.lfWidth = 7;
	lf.lfHeight = 18;
	m_fontBig.CreateFontIndirect(&lf);

	// font heavy grande grande
	lf.lfWeight = FW_HEAVY;
	lf.lfWidth = 8;
	lf.lfHeight = 24;
	m_fontBigBig.CreateFontIndirect(&lf);
}

int CEndoxApp::AfxMessageBoxEndo(UINT nIDText, UINT nType)
{
	return AfxMessageBoxEndo(GetMessageString(nIDText), nType);
}

int CEndoxApp::AfxMessageBoxEndo(LPCTSTR lpszText, UINT nType)
{
	CString sType = "";
	switch(nType & 7) // 0000 0000 0000 0111 binario //
	{
		case MB_OK:
		{
			sType = "MB_OK";
			break;
		}
		case MB_OKCANCEL:
		{
			sType = "MB_OKCANCEL";
			break;
		}
		case MB_ABORTRETRYIGNORE:
		{
			sType = "MB_ABORTRETRYIGNORE";
			break;
		}
		case MB_YESNOCANCEL:
		{
			sType = "MB_YESNOCANCEL";
			break;
		}
		case MB_YESNO:
		{
			sType = "MB_YESNO";
			break;
		}
		case MB_RETRYCANCEL:
		{
			sType = "MB_RETRYCANCEL";
			break;
		}
		case MB_CANCELTRYCONTINUE:
		{
			sType = "MB_CANCELTRYCONTINUE";
			break;
		}
		default:
		{
			sType.Format("%d", nType);
			break;
		}
	}

	CString sMessage(lpszText);
	sMessage.Replace('\r', ' ');
	sMessage.Replace('\n', ' ');
	sMessage.Trim();
	while(sMessage.Find("  ") > 0)
		sMessage.Replace("  ", " ");

	CString sLog;
	sLog.Format("MESSAGEBOX -> %s -> %s", sMessage, sType);
	CLogFileWriter::Get()->WriteLogLine0(sLog);

	//

	int iReturn = AfxMessageBox(lpszText, nType);

	CString sReturn = "";
	switch(iReturn)
	{
		case IDABORT:
		{
			sReturn = "IDABORT";
			break;
		}
		case IDCANCEL:
		{
			sReturn = "IDCANCEL";
			break;
		}
		case IDIGNORE:
		{
			sReturn = "IDIGNORE";
			break;
		}
		case IDNO:
		{
			sReturn = "IDNO";
			break;
		}
		case IDOK:
		{
			sReturn = "IDOK";
			break;
		}
		case IDRETRY:
		{
			sReturn = "IDRETRY";
			break;
		}
		case IDYES:
		{
			sReturn = "IDYES";
			break;
		}
		default:
		{
			sReturn.Format("%d", iReturn);
			break;
		}
	}

	CLogFileWriter::Get()->WriteLogLine0("MESSAGEBOX CLICKEDBTN -> " + sReturn + "\r\n");

	//

	return iReturn;
}

int CEndoxApp::MessageBoxEndo(UINT nIDText, UINT nIDCaption, UINT uType)
{
	if (nIDCaption == NULL)
		return MessageBoxEndo(GetMessageString(nIDText), NULL, uType);

	return MessageBoxEndo(GetMessageString(nIDText), GetMessageString(nIDCaption), uType);
}

int CEndoxApp::MessageBoxEndo(LPCSTR lpText, LPCSTR lpCaption, UINT uType)
{
	CString sType = "";
	switch(uType & 7) // 0000 0000 0000 0111 binario //
	{
		case MB_OK:
		{
			sType = "MB_OK";
			break;
		}
		case MB_OKCANCEL:
		{
			sType = "MB_OKCANCEL";
			break;
		}
		case MB_ABORTRETRYIGNORE:
		{
			sType = "MB_ABORTRETRYIGNORE";
			break;
		}
		case MB_YESNOCANCEL:
		{
			sType = "MB_YESNOCANCEL";
			break;
		}
		case MB_YESNO:
		{
			sType = "MB_YESNO";
			break;
		}
		case MB_RETRYCANCEL:
		{
			sType = "MB_RETRYCANCEL";
			break;
		}
		case MB_CANCELTRYCONTINUE:
		{
			sType = "MB_CANCELTRYCONTINUE";
			break;
		}
		default:
		{
			sType.Format("%d", uType);
			break;
		}
	}

	CString sMessage(lpText);
	sMessage.Replace('\r', ' ');
	sMessage.Replace('\n', ' ');
	while(sMessage.Find("  ") > 0)
		sMessage.Replace("  ", " ");

	CString sLog;
	sLog.Format("MESSAGEBOX -> %s -> %s", sMessage, sType);
	CLogFileWriter::Get()->WriteLogLine0(sLog);

	//

	int iReturn = MessageBox(NULL, lpText, lpCaption, uType);

	CString sReturn = "";
	switch(iReturn)
	{
		case IDABORT:
		{
			sReturn = "IDABORT";
			break;
		}
		case IDCANCEL:
		{
			sReturn = "IDCANCEL";
			break;
		}
		case IDIGNORE:
		{
			sReturn = "IDIGNORE";
			break;
		}
		case IDNO:
		{
			sReturn = "IDNO";
			break;
		}
		case IDOK:
		{
			sReturn = "IDOK";
			break;
		}
		case IDRETRY:
		{
			sReturn = "IDRETRY";
			break;
		}
		case IDYES:
		{
			sReturn = "IDYES";
			break;
		}
		default:
		{
			sReturn.Format("%d", iReturn);
			break;
		}
	}

	CLogFileWriter::Get()->WriteLogLine0("MESSAGEBOX CLICKEDBTN -> " + sReturn + "\r\n");

	//

	return iReturn;
}

CString CEndoxApp::GetServerDate()
{	
	CString sReturn;
	sReturn.Format("%04d%02d%02d000000", COleDateTime::GetCurrentTime().GetYear(), COleDateTime::GetCurrentTime().GetMonth(), COleDateTime::GetCurrentTime().GetDay());

	if (theApp.m_dbEndox.IsOpen() && theApp.m_dbEndox.CheckTableExists("AM_GETSERVERDATE"))
	{
		CAMBaseSet set(&theApp.m_dbEndox);

		try
		{
			set.Open(CRecordset::snapshot, "SELECT DATA FROM AM_GETSERVERDATE", CRecordset::readOnly);
			set.GetFieldValue("DATA", sReturn);
		}
		catch (CDBException* pEx)
		{
			pEx->ReportError();
			pEx->Delete();
		}
		catch (CMemoryException* pEx)
		{
			pEx->ReportError();
			pEx->Delete();
		}

		if (set.IsOpen())
			set.Close();
	}

	return sReturn;
}