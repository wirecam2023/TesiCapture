#ifndef __ENDOX_H__
	#define __ENDOX_H__

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"

#include "define.h"
#include "DLL_Imaging\h\AmBurn.h"

#include "EsamiSet.h"
#include "PazientiSet.h"

class CAccessDlg;
class CCalibList;
class CShowDbQueriesDlg;

#define szDirTempAcq		"ACQ - Percorso remoto"
#define szDirTempAcq2		"ACQ - Percorso copia immagini remote"
#define szODPath			"OD Path"
#define szAgendaIndex		"AgendaIndexPage"

#define szSettings 			"Settings"

#define szShowImage			"ModeShowImage"
#define szShowImageSimple	"ModeShowImageSimple"
#define szPdfAnteprimaDefaultZoomValue "PdfAnteprimaDefaultZoomValue"

#define szLastUse			"LastUse"
#define szBlackLevInt		"BlackLevInt"
#define szWhiteLevInt		"WhiteLevInt"
#define szBlackLevR			"BlackLevR"
#define szWhiteLevR			"WhiteLevR"
#define szBlackLevG			"BlackLevG"
#define szWhiteLevG			"WhiteLevG"
#define szBlackLevB			"BlackLevB"
#define szWhiteLevB			"WhiteLevB"

#define szReport			"Report - Impostazioni di default"
#define szReportFaceName	"Font"
#define szReportSize		"Dimensione"
#define szReportUnderline	"Sottolineato"
#define szReportBold		"Grassetto"
#define szReportItalic		"Corsivo"

#define szHeight 			"Height"
#define szWeight 			"Weight"
#define szItalic 			"Italic"
#define szUnderline 		"Underline"
#define szFaceName 			"FaceName"
#define szPitchAndFamily	"PitchAndFamily"

#define szPrintPage			"PrintPageImages"
#define szHeaderPrint		"HeaderPrint"
#define szIDHeader			"IDHeaderPrintable"
#define szIDFooter			"IDFooterPrintable"

#define szOptions			"Options"
#define szQFactorExp		"ExporQFactor"
#define szExpFormat			"ExporFormat"

#define szStoreScpPorta						"Porta StoreScp"
#define szStoreScpExecOnReceptionExe		"StoreScp ExecOnReception Exe"
#define szStoreScpExecOnReceptionParameters	"StoreScp ExecOnReception ExeParameters"

#define szEtichette			"Impostazioni della stampa etichette"
#define szMargineX			"Margine X"
#define szMargineY			"Margine Y"
#define szScalaX			"Scala X"
#define szScalaY			"Scala Y"

#define szPercorsi			"Percorsi di default"
#define szCheckRep			"CheckRep"
#define szCheckImm			"CheckImm"
#define szEditRep			"EditRep"
#define szEditImm			"EditImm"
#define szExportFolder		"ExportFolder"

#define szEseguiComando		"Riga di comando"

#define szFieldToFilterOnTransfer "Campo Da Filtrare Trasferimento"
#define szFilterOnTransfer        "Campo Da Non Trasferire"

#define szContrastElaboration	"Contrast Elaboration"
#define szBlackLev				"Black Lev"
#define szWhiteLev				"White Lev"
#define szBrightLev				"Bright Lev"

#define szBrightnessElaboration "Brightness Elaboration"
#define szSaltaControlloVersione "Salta Controllo Versione"
#define szIDSedeEsameDefault	"ID sede esame"
#define szSedeEsameDefaultOld	"Sede esame stazione"
#define szSalaEsameDefault		"Sala esame stazione"

#define szBadgeReaderAddress    "BadgeReaderAddress"
#define szBadgeReaderPort       "BadgeReaderPort"
#define szBadgeReaderTimeout    "BadgeReaderTimeout"
#define szSkipBadge				"CanSkipBadge"

#define szTerminalServer		"Terminal Server"

#define szVRAbilita				"Visualizzazione Remoto - Abilita"
#define szVRIP					"Visualizzazione Remoto - IP"
#define szVRPorta				"Visualizzazione Remoto - Porta"
#define szVRAbilitaMonitor		"Visualizzazione Remoto - Abilita Monitor"
#define szVRPortaMonitor		"Visualizzazione Remoto - Porta Monitor"

#define szVLC					"UseVLC"
#define szPathVLC				"PathVLC"

#define szTCMS					"UseTCMS"
#define szPathTCMS				"PathTCMS"

#define szSaveCompleteLog			"Save complete LOG"
#define szSaveCompleteLogIpDb		"Save complete LOG - IP DB server"
#define szSaveCompleteLogIpImm		"Save complete LOG - IP IMM server"
#define szSaveCompleteLogDays		"Save complete LOG - Days to keep"
#define szSaveCompleteLogThreshold	"Save complete LOG - Threshold (msec)"

#define szWorklistFattoreIngrandimento "Worklist - Fattore ingrandimento"
#define szWorklistStatoDaSelezionare   "Worklist - Stato da selezionare"

#define szShowDbQueries				"Show DB Queries"
#define szShowDbQueriesThreshold	"Show DB Queries Threshold (msec)"

#define szSMTP "SMTP"
#define szSMTPLogin "SMTPLogin"
#define szSMTPUser "SMTPUser"
#define szSMTPPassword "SMTPPassword"

#define szEngeneeringRicetteExe "EngeneeringRicetteExe"

#define szOpenIntoMonitor "OpenIntoMonitor"

#define szDSNContingencia "DSN Contingencia" //Julio BUG 3456 - Contingencia
#define szODBCSettings "ODBC Settings" //Julio BUG 3456 - Contingencia

#define szImageElaboration "Image Elaboration On Printing"
#define szImageElaborationBrightness "Brightness"
#define szImageElaborationContrastRMin "Contrast Red Min"
#define szImageElaborationContrastRMax "Contrast Red Max"
#define szImageElaborationContrastGMin "Contrast Green Min"
#define szImageElaborationContrastGMax "Contrast Green Max"
#define szImageElaborationContrastBMin "Contrast Blue Min"
#define szImageElaborationContrastBMax "Contrast Blue Max"

#define szTipoScannerCollegato		   "TipoScannerCollegato" //0: twain, 1: integrazione con scambio messaggi

#define szCodiceDispositivoDefault		"Codice dispositivo default"

#define szPercorsoOrigineDemoAliar      "Demo Aliar - Percorso Origine"
#define szPercorsoDestinazioneDemoAliar "Demo Aliar - Percorso Destinazione"

#define szIdRobotDefault				"Id Robot default"

#define PRG_CARDIOX 0
#define PRG_ENDOX 1
#define PRG_IMAGENT 2
#define PRG_DERMOX 3

#define FORMATO_REPORT_A4        0
#define FORMATO_REPORT_LEGAL     1
#define FORMATO_REPORT_LETTER    2
#define FORMATO_REPORT_EXCLUSIVE 3
#define FORMATO_REPORT_A4_LANDSCAPE 4 //Gabriel BUG 6303

struct tagCOMUNI
{
	long m_lID;
	CString m_sComune;
	CString m_sProvincia;
	CString m_sCAP;
};

struct tagMEDICICURANTIINVIANTI
{
	long m_lContatore;
	CString m_sTitolo;
	CString m_sCognome;
	CString m_sNome;
};

struct tagRicettaElement
{
	long m_lID;
	long m_lQuantita;
	CString m_sDescrizione;
};

struct tagRicettaFarmElement
{
	long m_lID;
	CString m_sNome;
	CString m_sPrincipioAttivo;
	CString m_sDescrizione;
};

struct worklistField
{
	CString sTitolo;
	CString sNomeColonna;
	long lDimensioneStampaPerc;
};

class CEndoxApp : public CWinApp
{

public:

	CEndoxApp();
	virtual ~CEndoxApp();

    virtual BOOL InitInstance();
    virtual INT ExitInstance();

	virtual int Run();

	enum WorkListType
	{
		prenotazioni_worklistdicom,
		prenotazioni_none,
		prenotazioni_cup,
		prenotazioni_cup_dicom,
		prenotazioni_DMS
	};	

protected:

	DECLARE_MESSAGE_MAP()

public:

	static CString GetMessageString(const UINT idString, const Localized_Modules module = module_endox);
	static void LocalizeDialog(CWnd* pDialog, const UINT idDialog, const CString& strDialog, const Localized_Modules module = module_endox);

	BOOL AlreadyLiving();
	void Dead();
	void DestroyAccessDialog();
	void DestroyShowDbQueriesDialog();
	CString GetAppTitle(long lFormatStyle);
    void GetPrivateProfileFont(LPCSTR szSec, LOGFONT* plf, int DimHeight);
	BOOL Live();
    void LoadSetting();
	void PosOnTop();
	void ReadExeData();
    void SaveSetting();
    void WritePrivateProfileFont(LPCSTR szSec, const LOGFONT* plf, LOGFONT* plfOld);
	CString GetServerDate();

	//////////////////////////////////////////
	// letti dalla tabella "Configurazioni" //
	//////////////////////////////////////////

	BOOL m_bAlbumImmaginiUsaListaCommenti;
	BOOL m_bAlbumImmaginiCommentoNonEditabile;
	BOOL m_bArchivioImmaginiThreadImport;
	BOOL m_bAssidenKey;
	BOOL m_bCentraleControlloQualita;
	BOOL m_bCentraleRefertazione;
	BOOL m_bCentraleStampa;
	long m_lCentraleStampaCodiceUnita;
	CString m_sCodiceUnitaFleury;
	BOOL m_bNoConiugazione;
	BOOL m_bCheckListClickElementoSeleziona;
	BOOL m_bCheckListComponiSequenzialmente;
	BOOL m_bChiusuraEsameAccodaStampaImmagini;
	BOOL m_bChiusuraEsameDoppiaConferma;
	BOOL m_bChiusuraEsameLogoutAuto;
	BOOL m_bChiusuraEsameSoloConPrestazioniPrincipali;
	BOOL m_bChiusuraProgrammaConferma;
	BOOL m_bCodificaRegionaleEliminaDuplicati;
	long m_lControlloQualitaPercentuale;
	CString m_sControlloQualitaUnidade;
	CString m_sControlloQualitaRegional;
	CString m_sControlloQualitaMarca;
	BOOL m_bDemoAliar;
	BOOL m_bDermoxAcquisizioneDiretta;
	BOOL m_bDermoxAcqDirettaMantieniCopiaBackup;
	BOOL m_bDermoxMostraCalibSuAlbum;
	BOOL m_bDisattivaFrecceSpostamentoPazienti;
	BOOL m_bInserisciPrenotazione;
	BOOL m_bIntegrazionePacsAttiva;
	BOOL m_bIntegrazionePacsSincrona;
	BOOL m_bInterfacciaDMS;
	BOOL m_bInterfacciaMetafora;
	BOOL m_bInterfacciaWeb;
	BOOL m_bIstopatologiaMostraLettera; // Sandro 05/11/2013 // RAS 20130163 //
	BOOL m_bLockServerAttivo;
	BOOL m_bLoginMultiploUtente;
	BOOL m_bMediciDescrizioneLibera;
	BOOL m_bMostraCodiceEsame;
	BOOL m_bMostraMenuDatabasesRemoti; // Sandro 27/11/2015 // RIMA 15135 //
	BOOL m_bMostraNumeroEsamiPerSede; // Sandro 14/01/2014 // RAS 20140006 //
	BOOL m_bMostraPazienteInCuraDalDirettore; // Sandro 23/07/2015 // RAS 20150048 //
	BOOL m_bMostraSecondoCognome;
	BOOL m_bMostraSoloAnnoInterventiChirurgici;
	BOOL m_bMostraSoloAnnoInterventiEndoscopici;
	BOOL m_bMostraTastoUnificazioneAnagrafiche;
	BOOL m_bNominativoSuExportImmagini;
	BOOL m_bNumeriSuImmaginiAlbum;
	BOOL m_bNumeriSuImmagineSagoma;
	BOOL m_bPazienteInternoDefault;
	BOOL m_bPdfEliminazionePasswordCriptata;
	BOOL m_bPDFImmaginiCrea;
	BOOL m_bPDFImmaginiNonCompresse;
	BOOL m_bPDFIncorporaFonts;
	BOOL m_bPDFInibisciCopia;
	BOOL m_bPDFInibisciStampa;
	BOOL m_bPDFNonProtetti;
	BOOL m_bPersonalizzazioniBrasileCamargo;
	BOOL m_bAtivaTCP; //BUG 9527 - Felipe (NewTCP)
	BOOL m_bPersonalizzazioniBrasileEinstein;
	BOOL m_bPersonalizzazioniBrasileFleury;
	BOOL m_bPersonalizzazioniBrasileSirio;
	BOOL m_bPrenotazioniCup;
	long m_lPrenotazioniCupFocus;
	BOOL m_bPrenotazioniDicom;
	BOOL m_bProgressivoEsamePerSede;
	BOOL m_bRefertazioneLogoutAuto;
	BOOL m_bRefertazioneUsaChecklist;
	BOOL m_bRefertazioneUsaFrasiRTF;
	BOOL m_bRefertazioneUsaFrasiStandard;
	BOOL m_bReopenAcquisition;
	BOOL m_bRiaperturaEsameSoloAmministratore;
	BOOL m_bRicercaChiediConteggio;
	BOOL m_bRicercaChiediSoloPazienti;
	BOOL m_bRicettaPerAP;
	BOOL m_bRicettaPerAP_psm;
	BOOL m_bRicettaCodebarObbligatori;
	BOOL m_bSalvaSoloUltimeImmaginiStampate;
	BOOL m_bSospesiIstologiciNascondiVerificati;
	BOOL m_bStampaBordiNeriImmagini;
	BOOL m_bStampaCommentoDentroImmagini;
	BOOL m_bStampaImmaginiUsaHFPerUO; // Sandro 26/10/2015 //
	BOOL m_bStampaSelezionaAutomaticaImmaginiStampate;
	BOOL m_bStoricoImago;
	BOOL m_bTastoStampaReportStampaSempre;
	BOOL m_bUOVisualizzaAngoloAltoDestra;
	BOOL m_bUsaProntuario;
	BOOL m_bUsaTexterAsRTF;		// Marvel Carvalho - Bug 3457 (FIX) TEXTER

	CString m_sGenomicaModeloTabela1;
	CString m_sGenomicaModeloTabela2;
	CString m_sGenomicaModeloTabela3;
	CString m_sGenomicaModeloTabela4;
	CString m_sGenomicaModeloTabela5;

	//Gestione ricoveri
	BOOL m_bAttivaRicoveri;
	//Gestione pronto soccorso
	BOOL m_bAttivaPS;

	BOOL m_bMostraScoreMonitoraggio;
	BOOL m_bUsaScoreDiGlasgow;

	float m_fSogliaBreathTestHP;

	int m_nArchivioImmaginiFormato;
	int m_nArchivioImmaginiQualita;
	int m_nArchivioImmaginiSogliaAvviso;
	int m_nArchivioImmaginiSogliaBlocco;
	int m_nArchivioMiniatureQualita;
	int m_nFormatoPagina;
	int m_nTesiAtdNetPorta;

	long m_lBackupDVD;
	long m_lBloccoReferto;
	long m_lChiusuraEsameRitardoInvioOre;
	long m_lChiusuraEsameRitardoInvioMinuti;
	long m_lCodificaRegionaleMostraCodice;
	long m_lCountdownPartenza;
	long m_lIDEsameFirmaDisattivata;
	long m_lInterfacciaPathox;
	long m_lMaxIdRange;
	long m_lMinIdRange;
	long m_lModalitaCaricamentoCampiDefault;
	long m_lModificaReferto;
	long m_lMostraEtaPaziente;
	long m_lOpzionalePazientiCronici;
	long m_lPDFQualitaImmaginiCompresse;			// Sandro 20/09/2013 // RAS 20130112 //
	long m_lPressioneMinimaValoreMinimo;
	long m_lPressioneMinimaValoreMassimo;
	long m_lPressioneMassimaValoreMinimo;
	long m_lPressioneMassimaValoreMassimo;
	long m_lRefertoAllineamentoTestoDefault;
	BOOL m_bRefertoMarcaVariabiliAnnullati;		// Julio 29/08/2018
	long m_lRicercaCodiceEsame;
	long m_lRicettaMaxItems;
	long m_lLockServerPorta;
	long m_lOpenIntoMonitor;

	//Rect dello schermo di lavoro
	CRect m_rectDesk;

	CString m_sBarCodeFontName;
	CString m_sControlloOrtograficoPathDizionarioUtente;
	CString m_sEmissioneRefertoUrl;
	CString m_sEsportaFilmatiPerVisoreWebSuPath;
	CString m_sLockServerIndirizzo;
	CString m_sNomeProgramma;
	CString m_sNomeProgrammaCertificazione;
	CString m_sPazientiTabella;
	// CString m_sPazientiVista;
    // CString m_sPazientiVistaOrdinamento;
	CString m_sPdfEliminazionePassword;
	CString m_sPercorsoAllegatiPaz;
	CString m_sPercorsoAllegatiEsa;
	CString m_sPercorsoPDF;
	CString m_sPercorsoReportsConsensoInformato;
	CString m_sQueryMan;
	CString m_sSmartCardPin;
	CString m_sTesiAtdNetIndirizzo;
	CString m_sTestiConcatenatiSeparatore;
	CString m_sRicetteEngeneeringExe;
	CString m_sNoteReperibilitaDefault;

	BOOL m_bFleuryProgrammaConsultaNuovo;

	enum FirmaDigitaleType
	{
		sign_disabled = 0,
		sign_comped
	};
	FirmaDigitaleType m_enumFirmaDigitale;

	BOOL m_bFirmaDigitaleChiudiComped;
	BOOL m_bFirmaDigitaleDebug;
	BOOL m_bFirmaDigitaleAnteprimaMostra;
	BOOL m_bFirmaDigitaleSmartcardUgualeMedico1;
	BOOL m_bFirmaDigitaleSmartcardUgualeUtenteEndox;
	long m_lFirmaDigitaleStampa;
	CString m_sFirmaDigitaleTemplatesPath;
	CString m_sFirmaDigitaleReportAnnullamento;
	BOOL m_bSISSRichiediMarcaTemporale;
	BOOL m_bSISSGeneraSempreDAO;
	BOOL m_bSISSMostraMenuDisattivaFirma;

	BOOL m_bTextControlCopiaIncollaRimuoviFormattazione;
	BOOL m_bRicercaUOLimitata; // Luiz - 08/02/2019 - P3 - Dependendo da Configuração (Ricerca UO limitata), impedir que itens de outra especialidade na conjugacao 
	BOOL m_bConfermareGliEsamiSenzaAttaccamentoOImmagini; // Luiz - 11/02/2019 - P3 - Dependendo da Configuração (Confermare Gli Esami Senza Attaccamento O Immagini), confirma salvar/assinar exames sem anexos ou imagens 
	BOOL m_bFaseExtraAmarradoAoSuperlock; // Luiz - 27/03/2019 - P3 - Dependendo da Configuração (Fase Extra Amarrado Ao Superlock), obriga que seja realizada sequencia salvar/assinar antes de protocolar e desfazer protocolar antes de desfazer salvar/assinar

	BOOL m_bSelezionaMedicoRichiedente; //Gabriel - P3
	ScannerConnectionType m_enumScannerConnectionType;

	/////////
	// --- //
	/////////

	BOOL m_bAnamVisi[NUM_FIELD_ANAM];
	BOOL m_bAnamAuto[NUM_FIELD_ANAM];
	BOOL m_bAutoDeselect;
	BOOL m_bCanAcquire;
	BOOL m_bCanWriteCD;
	BOOL m_bCanWriteDVD;
	BOOL m_bCheckImm;
	BOOL m_bCheckRep;
	BOOL m_bComboActive[NUM_LABEL_TESTO];
	BOOL m_bComboMultipleSel[NUM_LABEL_TESTO];
	BOOL m_bComboSingleLine[NUM_LABEL_TESTO];
	BOOL m_bComboUppercase[NUM_LABEL_TESTO];
	BOOL m_bComboNumerico[NUM_LABEL_TESTO];
	BOOL m_bCopy[NUM_LABEL_TESTO];
	BOOL m_lIdCampoRelazionato[NUM_LABEL_TESTO];
	BOOL m_bCopyRtf[NUM_LABEL_TESTO_RTF];
	BOOL m_lIdCampoRelazionatoRtf[NUM_LABEL_TESTO];
	BOOL m_bCopyCL[NUM_LABEL_TESTO_CL];
	BOOL m_bCopyDate[NUM_LABEL_DATAORA];
	BOOL m_bTastoStampaCheck[NUM_LABEL_TASTO_STAMPA];
	BOOL m_bConfigure; // Sandro 22/03/2010 - durante installazione di Endox //
	//ras 20130126 - Check list con alarm
	BOOL m_bAlarmCL[NUM_LABEL_TESTO_CL];
	CString m_sParoleChiaveCL[NUM_LABEL_TESTO_CL];

	int m_iRadioDate[NUM_LABEL_DATAORA];

	CString m_sTastoBrowserIndirizzo[NUM_LABEL_TASTO_BROWSER];
	CString m_sTastoEseguibileFile[NUM_LABEL_TASTO_EXEC];
	CString m_sTastoStampaFile[NUM_LABEL_TASTO_STAMPA];

	long m_lIdFaseTastoChiusuraFase[NUM_LABEL_TASTO_CHIUSURAFASE];	

	long m_lIDStampanteImmagini;
	long m_lIDPrintingWorklist;
	long m_lStampaImmaginiIDHeaderGlobal; // Sandro 26/10/2015 // Header per UO //
	long m_lStampaImmaginiIDHeaderLocal;  // Sandro 26/10/2015 // Header per stazione //
	long m_lStampaImmaginiIDFooterGlobal; // Sandro 26/10/2015 // Footer per UO //
	long m_lStampaImmaginiIDFooterLocal;  // Sandro 26/10/2015 // Footer per stazione //
	BOOL m_bConsultazioneWEB;
	BOOL m_bLoadingInterface;
	BOOL m_bNomenclatore;
	BOOL m_bPubblicazioneAuto;
	BOOL m_bSkipBadge;
	BOOL m_bSoloAutoImport;
	BOOL m_bSoloDicom;
	BOOL m_bStampaImmaginiStampaCommenti;
	BOOL m_bStampaImmaginiStampaDatiPaziente;
	BOOL m_bStampaImmaginiStampaNumero;
	BOOL m_bTerminalServer;

	//RIMAGE - viene calcolato in avvio con query su tabella ROBOT
	BOOL	m_bRobotAttivo;
	//CString m_sRimageAddress;
	//int		m_iRimagePort;
	//CString m_sRimageMergeFilesPath;
	//CString m_sRimageLabelFile_patient;
	//CString m_sRimageLabelFile_backup;
	//BOOL	m_bRimageSimulateBurning;
	//CString m_sRimageExportFolder;

	BOOL m_bSaveCompleteLog;
	CString m_sSaveCompleteLogIpDb;
	CString m_sSaveCompleteLogIpImm;
	long m_lSaveCompleteLogDays;
	long m_lSaveCompleteLogThreshold;

	BOOL m_bShowDbQueries;
	long m_lShowDbQueriesThreshold;

	long m_lWorklistFattoreIngrandimento;
	long m_lWorklistStatoDaSelezionare;

	float m_fEtichette00;
	float m_fEtichette01;
	float m_fEtichette02;
	float m_fEtichette03;

	int m_nApplication; // 0 Endox // 2 Cardiox // ? ImageNT //
	int m_nBadgeReaderPort;
	int m_nBadgeReaderTimeout;
	
	int m_nExpFormat;
	int m_nFieldToFilterOnTransfer;
	int m_nProgramMode;
	int m_nQFactorExp;
	int m_nQuanteImmaginiPerPagina[4];
	int m_nStampaImmaginiDistanzaImmagini;
	int m_nStampaImmaginiTipoDiStampa;
	CString m_sStampaImmaginiSiglePerStampaOrizzontale; //Gabriel BUG 6303
	CString m_sSpermaEsameSiglePerGenerazioneGrafici; //Gabriel BUG 5533

	long m_lOnlyThisFrame;

	long m_lBackupDeviceID;
	long m_lLoginMode;
	long m_lUO;
	
	CString m_sNomeComputer;
	CString m_sAgendaIndex;
	CString m_sAnamText[NUM_FIELD_ANAM];
	CString m_sBackupDevicePath;
	CString m_sLoginServer;

	CString m_sBadgeReaderAddress;

	CString m_sDataBuild;

    CString m_sDirProg;
    CString m_sDirTemp;
    CString m_sDirTempAcq;
    CString m_sDirTempAcq2;
    CString m_sPathImageOD;

	CString m_sFileCalib;
    CString m_sFileConfig;

	CString	m_sEditImm;
	CString	m_sEditRep;
	CString m_sEseguiComando;
	CString	m_sExportFolder;
	CString m_sFilterOnTransfer;
	CString m_sHeaderPrintImage;
	CString m_sInterfacciaWebFrom;
	CString m_sInterfacciaWebSupplier;
	CString m_sInterfacciaWebTo;

	CString m_sLabelText[NUM_LABEL_TESTO];
	CString m_sLabelTextEtichette[NUM_LABEL_ETICHETTE];
	CString m_sLabelTextRtf[NUM_LABEL_TESTO_RTF];
	CString m_sLabelTextCL[NUM_LABEL_TESTO_CL];
	CString m_sLabelDate[NUM_LABEL_DATAORA];
	CString m_sLabelTastoStampa[NUM_LABEL_TASTO_STAMPA];
	CString m_sLabelTastoBrowser[NUM_LABEL_TASTO_BROWSER];
	CString m_sLabelTastoEseguibile[NUM_LABEL_TASTO_EXEC];
	CString m_sLabelTastoChiusuraFase[NUM_LABEL_TASTO_CHIUSURAFASE];
	
	CString m_sLabelTextGridCL[NUM_LABEL_GRIDCL];
	long	m_lLastGridCLVersion;
	CList<long> m_listGridCLGruppiAssociati[NUM_LABEL_GRIDCL];

	CString m_sBostonScore[10];

	CString m_sNomeImpianto;
	CString m_sNumBuild;
	CString m_sPercorsoTemporaneoWEB;
	long	m_lSaltaControlloVersione;
	long	m_lIDSedeEsameDefault;
	CString m_sSalaEsameDefault;
	CString m_sUtenteLoggato;
	CString m_sVersione;
	CString m_sVersioneFull;

	CString m_sStoreScpPorta;
	CString m_sStoreScpExecOnReceptionExe;
	CString m_sStoreScpExecOnReceptionParameters;

	long m_lDcmStoreMode;

	CString m_sSMTP;

	//
	int m_iIEBrightness;
	int m_iIEContrastRMin;
	int m_iIEContrastRMax;
	int m_iIEContrastGMin;
	int m_iIEContrastGMax;
	int m_iIEContrastBMin;
	int m_iIEContrastBMax;

	// Visualizzazione remota immagini //
	BOOL m_bVisAbilita;
	BOOL m_bVisAbilitaMonitor;
	CString m_sVisIp;
	long m_lVisPorta;
	CString m_sVisPortaMonitor;
	int m_iPrevInput;

    CAccessDlg* m_pAccessWnd;
	CShowDbQueriesDlg* m_pShowDbQueriesWnd;

	CAMBaseDB m_dbEndox;
	CCalibList* m_pListCalib;

	languages m_nLanguage;

	COLORREF m_color[6];
	COLORREF m_colorSfondo[6];
	COLORREF m_colorPazienteSfondo;
	COLORREF m_colorStato;
	COLORREF m_colorStatoSfondo;

	/* Gestione colori stato */
	COLORREF m_colorVisualizzazioneAperto;
	COLORREF m_colorVisualizzazioneApertoSfondo;
	COLORREF m_colorVisualizzazioneChiuso;
	COLORREF m_colorVisualizzazioneChiusoSfondo;
	COLORREF m_colorVisualizzazioneFirmato;
	COLORREF m_colorVisualizzazioneFirmatoSfondo;
	COLORREF m_colorAggiuntaPaziente;
	COLORREF m_colorAggiuntaPazienteSfondo;
	COLORREF m_colorModificaPaziente;
	COLORREF m_colorModificaPazienteSfondo;
	COLORREF m_colorAggiuntaEsame;
	COLORREF m_colorAggiuntaEsameSfondo;
	COLORREF m_colorModificaEsame;
	COLORREF m_colorModificaEsameSfondo;
	COLORREF m_colorRicercaPaziente;
	COLORREF m_colorRicercaPazienteSfondo;
	COLORREF m_colorRicercaEsame;
	COLORREF m_colorRicercaEsameSfondo;
	COLORREF m_colorVisualizzazioneArchiviato;
	COLORREF m_colorVisualizzazioneArchiviatoSfondo;
	COLORREF m_colorVisualizzazioneInArchiviazione;
	COLORREF m_colorVisualizzazioneInArchiviazioneSfondo;
	COLORREF m_colorStreamingAttivo;
	COLORREF m_colorStreamingAttivoSfondo;
	COLORREF m_colorStreamingConnesso;
	COLORREF m_colorStreamingConnessoSfondo;
	
	// ---- //

	DWORD m_dwPrivileges;

	HANDLE m_hMutexLive;

	CFont m_fontBigBig;
	CFont m_fontBig;
	CFont m_fontBold;
	CFont m_fontNormal;
	CFont m_fontReport;

	CList<tagDEVICE> m_listTransferDevice;

	CList<tagCOMUNI> m_listComuni;
	CList<tagMEDICICURANTIINVIANTI> m_listMediciCuranti;
	CList<tagMEDICICURANTIINVIANTI> m_listMediciInvianti;
	CList<tagRicettaElement> m_listGruppiPrestazioni;
	CList<tagRicettaElement> m_listGruppiFarmaci;
	CList<tagRicettaElement> m_listVociPrestazioni;
	CList<tagRicettaFarmElement> m_listVociFarmaci;

	WorkListType m_nInterfacciaPrenotazione;

	CPazientiSet* m_pSetPazienti;
	CEsamiSet* m_pSetEsami;

	BOOL m_iUseTCMS;
	CString m_sPathVLC;
	int m_iUseVLC;
	CString m_sPathTCMS;

	BOOL m_nSMTPLogin;
	CString m_strSMTPUser;
	CString m_strSMTPPassword;

	BOOL m_bIntegrazioneGestioneRichiesteAcquisite;
	BOOL m_bIntegrazioneInvioImmaginiBinarie;
	BOOL m_bIntegrazioneInvioRefertiAnnullati;
	BOOL m_bIntegrazioneInvioRefertiDalFiller;

	CString m_sHttpServerRicercaFicha;
	CString m_sHttpServerRicercaItensDaFicha;
	CString m_sHttpServerRichiestaInfoUser;
	CString m_sHttpServerRichiestaUserSignature;
	CString m_sHttpServerRichiestaModificaStampa;
	CString m_sHttpServerRichiestaUnidade;
	CString m_sHttpServerRichiestaLaudos;

	CString m_sTabellaEcocardioFormulaBSA;
	CString m_sTabellaEcocardioTabs;

	BOOL m_bDisabilitaEsamiPazientiSenzaAssiden;

	BOOL m_bLoginDropDomain;
	BOOL m_bOldAlbumMode;

	//

	CList<worklistField> m_worklistFields;

	// Sandro 17/07/2015 // RIMA 15052 //
	CString m_sRefertoIntegratoRtf;
	CString m_sRefertoIntegratoTxt;

	// Sandro 07/12/2015 // RIMA 15135 //
	CString m_sPassedConnectionString;
	CString m_sPassedDescription;
	CString m_sPassedUsername;
	CString m_sPassedPassword;
	CString m_sPassedUO;

	//Simone 01/01/2015
	BOOL	m_bVitalSignIntegrazioneAttiva;
	CString m_sVitalSignWebServiceEndpoint;
	CString m_sCodiceDispositivoDefault;

	//Simone 22/02/2016
	BOOL m_bUsaUtenteLoggatoComeMedicoDefault;

	//Simone - RIMA 15144
	BOOL m_bPrestazioniReadOnly;

	CString m_sPercorsoOrigineDemoAliar;
	CString m_sPercorsoDestinazioneDemoAliar;

	//Simone RIMA 16052
	BOOL m_bMantieniImmaginiSelezionateAlLogout;
	CStringList m_listUserGroups;
	CList<long> m_listUserPhases;
	int m_nMonitoraggioDoloreDefault;

	//16093
	BOOL m_bEsameFirmatoDigitalmenteAlmenoUnaVolta;

	//RIMAGE 16095
	long m_lIdRobotDefault;

	//RIMA 16093 - Humanitas
	BOOL m_bChiusuraFaseLogin;

	//Simone - RIMA 16097
	BOOL m_bMonitoraggioPermettiCopia;

	// Sandro 18/07/2014 //

	int AfxMessageBoxEndo(UINT nIDText, UINT nType = MB_OK);
	int AfxMessageBoxEndo(LPCTSTR lpszText, UINT nType = MB_OK);
	int MessageBoxEndo(LPCSTR lpText, LPCSTR lpCaption = NULL, UINT uType = MB_OK);
	int MessageBoxEndo(UINT nIDText, UINT nIDCaption = NULL, UINT uType = MB_OK);

	BOOL m_bDicomWorklistActive;
	CString m_sDicomWorklistAet;
	long m_lDicomWorklistPort;
	BOOL m_bDicomWorklistLog;

	//


	//

	// datiCentraleStampa m_structDatiCentraleStampa;

	//Julio 13/11/2017
	CString m_sLaudoRtfExameAnteriorEndpoint;

	//Julio 12/03/2018
	BOOL m_bMenuUsaCarestreamExamesPendentes;
	BOOL m_bMenuUsaTextboxBuscaExame;
	CString m_sHttpPathVisorPacsWeb;
	BOOL m_bUsaLaudoProvisorio;

	//Julio 17/08/2018
	BOOL m_bLoadPrinterSettings;

	//Julio 22/10/2018
	BOOL m_bImpersonated;
	long m_lImpersonatedID;
	CString m_sImpersonatedUsername;

	//Julio 13/11/2018
	BOOL m_bUsaMedicoLogadoNaPesquisaSalvar;
	BOOL m_bUsaMedicoLogadoNaPesquisaAssinar;

	//Julio 01/02/2019
	BOOL m_bMedidasBiometricasUsaCodeValue;

	// Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo 
	CString m_sHttpServerAnulaLiberaLaudo;
	// Luiz - 02/05/2019 - P3 - Checkbox "Mostrar todas" - checklist laudo
	CString m_sPrestazione;
	// Luiz - 07/05/2019 - P3 - Desconjuga exames - ESAMIINTEGRATI
	BOOL m_bPossuiConjugados;

	//Julio 06/02/2019
	CString m_sPathValoresReferencia;
	BOOL m_bUsaModuloGenomica;		// Julio genomica	
	BOOL m_bContingencia; //Julio BUG 3456 - Contingencia	
	CString m_sConnStrContigencia; //Julio BUG 3456 - Contingencia
	BOOL m_bCapturaContinua; //Julio (FIX) BUG 3361 - Captura continua

	BOOL m_bShowAlertaEdicaoConcorrente; // Marvel BUG 4092 - concorrência na edição de laudos // --Referto - apresenta msg popup alerta quando houver edição concorrente

	//Julio - BUG 4392 Edicao de texto
	BOOL m_bRtfUsaConfigurazioniTabelle;
	BOOL m_bRtfUsaConfigurazioniFont;
	BOOL m_bRtfUsaConfigurazioniImmagini;
	//

	//Julio - BUG 3365 - MAMOGUS
	BOOL m_bUsaComboPrestazioni;
	//

	// Marvel Carvalho | BUG 3759 - TesiCapture Melhoria Filtro Worklist
	// variáveis para armazenar os filtros do usuário da tela da worklist
	BOOL    m_default_LISTAPRENOTAZIONICUP_HasFilter;
	CString	m_default_LISTAPRENOTAZIONICUP_CODICERICOVERO;
	CString	m_default_LISTAPRENOTAZIONICUP_NUMORDINE;
	CString	m_default_LISTAPRENOTAZIONICUP_CODPAZIENTE;
	CString	m_default_LISTAPRENOTAZIONICUP_COGNOME;
	CString	m_default_LISTAPRENOTAZIONICUP_NOME;
	int     m_default_LISTAPRENOTAZIONICUP_COMBODATA;
	CString	m_default_LISTAPRENOTAZIONICUP_DATAINIZ;
	CString	m_default_LISTAPRENOTAZIONICUP_DATAFINE;
	int     m_default_LISTAPRENOTAZIONICUP_COMBOUNIDADE;
	int     m_default_LISTAPRENOTAZIONICUP_COMBOSTATO;
	int     m_default_LISTAPRENOTAZIONICUP_COMBOPROVENIENZA;
	BOOL    m_default_LISTAPRENOTAZIONICUP_CHKFILTERDATA;
	int     m_default_LISTAPRENOTAZIONICUP_COMBOREGIONAL;
	int     m_default_LISTAPRENOTAZIONICUP_COMBOSEDE;
	int     m_default_LISTAPRENOTAZIONICUP_COMBOSALA;
	int     m_default_LISTAPRENOTAZIONICUP_COMBOMARCA;

	// Marvel Carvalho | BUG 3780 - TesiCapture Melhoria Filtro Esami Pendenti
	// variáveis para armazenar os filtros do usuário da tela esami pendenti
	BOOL m_default_GESTIONEESAMIPENDENTI_HasFilter;
	int  m_default_GESTIONEESAMIPENDENTI_COMBODATA;
	long m_default_GESTIONEESAMIPENDENTI_DATAINIZ;
	long m_default_GESTIONEESAMIPENDENTI_DATAFINE;
	long m_default_GESTIONEESAMIPENDENTI_COMBOUO;
	long m_default_GESTIONEESAMIPENDENTI_COMBOMEDICO;

	// Marvel Carvalho - BUG 4308 Esquemas Anatômicos Fleury
	CString m_sPercorsoSCHEMI_ANATOMICI;

	// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnesi)
	CString m_sTabAnamnesiInReferto;

	// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#1 - dual screen)
	CString m_sConfigFormRefertoBtnImgOpenWhat;
	CString m_sConfigFormRefertoBtnImgOpenWhere;
	BOOL    m_bConfigFormRefertoBtnImgAutomated;
	
	long    m_lInstanceCountCImageDlg; //Gabriel BUG 6225 - Lista DO
	long    m_lInstanceCountCImageSimple2Dlg; //Gabriel BUG 6225 - Lista DO

	CString m_sConfigFormAlbumImgBtnImgOpenWhere;
	
	// Marvel Carvalho - BUG 4621 Pop up central de laudos
	BOOL m_bPopupCentralDeLaudos;

	// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
	CString m_sLastSearchMedico1;

	BOOL m_bUsaIDSegu; //Julio Login SEGU

	CString m_sIndirizziMailReconvocazione; //Gabriel BUG 6225 - Lista DO

	BOOL m_bRefertoMostraEtaPazienteTitolo; //Gabriel BUG 6225 - Lista DO

	BOOL m_bImportazioneAutomaticaRicetta; //Gabriel BUG 6225 - Lista DO

	CString m_sHttpServerSubstituicaoResultado; //Gabriel - P3
	CString m_sHttpServerProtocoloXXI; //Gabriel - P3

	BOOL m_bUsaCapturaScannerTGrabber; //Gabriel BUG 7749 - Capturar imagens via xtwain utilizando pedal USB
	BOOL m_bAtivaListaDO; //Gabriel - Chave para ativar Lista DO
	BOOL m_bAtivaP3; //Gabriel - Chave para ativar P3
	
	CString m_sSiglasTCP; //Gabriel - TCP
	
	BOOL m_bUsaNovaCapturaContinua; //Gabriel BUG 7768 - Continuous capture problem

	CString m_sEsamiPendentiOrdineColonna; //Gabriel BUG 6225 - Lista DO FIX
	long m_lEsamiPendentiColonnaOrdinare; //Gabriel BUG 6225 - Lista DO FIX
	BOOL m_bAbreImgTelaCheia; //Gabriel BUG 6225 - Lista DO FIX

	BOOL m_bAtivaEspermograma; //Gabriel - BUG 5533 V2
private:

	void SetFont();

	BOOL m_bLocalInit;

	ULONG_PTR m_gdiplusToken;

};

extern CEndoxApp theApp;

#endif  /* __ENDOX_H__ */