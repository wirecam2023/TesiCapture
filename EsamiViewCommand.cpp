#include "stdafx.h"
#include "Endox.h"
#include "EsamiView.h"

#include <io.h>

#include "DLL_Imaging\h\AMLogin.h"
#include "DLL_Imaging\h\AmPDFCreatorHaru.h"
#include "DLL_Imaging\h\AmPDFManager.h"
#include "DLL_Imaging\h\AMTesiSign.h"
#include "DLL_Imaging\h\ExamService.h"
#include "DLL_Imaging\h\ChiusuraFaseEndox.h"

#include "AboutBoxDlg.h"
#include "AccessoriDlg.h"
#include "AccessoSediEsterneDlg.h"
#include "AlbumForm.h"
#include "ArchiviBackupDlg.h"
#include "ArchivioStampeDlg.h"
#include "AssociazioniICD9Dlg.h"
#include "BackupDatiDlg.h"
#include "BackupDatiDoppiaCopiaDlg.h"
#include "BostonScoreMessagesDlg.h"
#include "BrowserDlg.h"
#include "CalibDlg.h"
#include "CambioPasswordDlg.h"
#include "CampiObbligatoriDlg.h"
#include "CentriDiCostoDlg.h"
#include "CheckListModDlg.h"
#include "CodificaRegionaleExBulkSet.h"
#include "CodificaRegionaleExDlg.h"
#include "CodificaRegionaleGruppiBulkSet.h"
#include "CodificaRegionaleGruppiDlg.h"
#include "ComboAltreAnomalieSet.h"
#include "ComboCauseNonCompletamentoSet.h"
#include "ComboComplicanzeSet.h"
#include "ComboConclusioniScreeningSet.h"
#include "ComboConclusioniColonSet.h"
#include "ComboDiagnosiFinaleSet.h"
#include "ComboPuliziaSet.h"
#include "ComboTolleranzaSet.h"
#include "ComboTransConfigDlg.h"
#include "CommentiImmaginiModDlg.h"
#include "ComuniBulkSet.h"
#include "CupWorkListManager.h"
#include "CustomDate.h"
#include "DermoxAcqSetupDlg.h"
#include "DiagnosiICD9Dlg.h"
#include "DiagnosiIstologicheDlg.h"
#include "DisegnaOperatorDlg.h"
#include "DocManager.h"
#include "DocumentiDlg.h"
#include "DosiMonitoraggioDlg.h"
#include "EsameIntegratoDlg.h"
#include "EsamiDoc.h"
#include "EsamiFasiChiuseSet.h"
#include "EsamiIntegratiSet.h" // Luiz - 07/05/2019 - P3 - Desconjuga exames - ESAMIINTEGRATI
#include "EsamiSet.h"
#include "EtichetteAnamnesiDlg.h"
#include "EtichetteNewDlg.h"
#include "ExtEsameMediciRichiedenteSet.h" // Luiz - 13/05/2019 - P3 - Atualiza nome/sobrenome Médico - Inclui Médicos solicitantes
#include "ExtEsamiFasiChiuseSet.h"
#include "ExtEsamiMediaDaInviareSet.h"
#include "FarmaciBulkSet.h"
#include "FarmaciGruppiRicBulkSet.h"
#include "FarmaciGruppiRicDlg.h"
#include "FarmaciMonitoraggioDlg.h"
#include "FarmaciPazientiCroniciDlg.h"
#include "FasiConfigDlg.h"
#include "FasiEsameSet.h"
#include "FileBmp.h"
#include "FrasiDlg.h"
#include "FrasiPostEsameDlg.h"
#include "FrasiRtfDlg.h"
#include "GestioneEsamiPendentiDlg.h"
#include "GruppiDiagnosiICD9ModDlg.h"
#include "GruppiPrelieviModDlg.h"
#include "GruppiPrelieviOldModDlg.h"
#include "GruppiPrestazioniModDlg.h"
#include "GruppiProcedureICD9ModDlg.h"
#include "ImportaCasoDlg.h"
#include "InfermieriDlg.h"
#include "IntegrazioniConfigurazioneModDlg.h"
#include "IntestazioneNewDlg.h"
#include "InviantiDlg.h"
#include "IstopatologiaProcedureDlg.h"
#include "IstopatologiaTipiDlg.h"
#include "MalattieCronicheDlg.h"
#include "MeasurementsMappingDlg.h"
#include "SchemiAnatomiciRecordDlg.h" // Marvel Carvalho - BUG 4308 Esquemas Anatômicos Fleury
#include "SchemiAnatomiciEditDlg.h" // Marvel Carvalho - BUG 4308 Esquemas Anatômicos Fleury
#include "SchemiAnatomiciAggiuntoDynForm.h" // Marvel Carvalho - BUG 4308 Esquemas Anatômicos Fleury
#include "MediciCurantiInviantiBulkSet.h"
#include "MediciCurantiInviantiDlg.h"
#include "MediciSet.h" // Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
#include "ModelessDlg.h"
#include "ModStatoColoreDlg.h"
#include "MstCodificaDiagnosiEsameModDlg.h"
#include "MstComplicanze1ModDlg.h"
#include "MstComplicanze2ModDlg.h"
#include "MstComplicanze3ModDlg.h"
#include "MstDiagnosiModDlg.h"
#include "MstIndicazioniModDlg.h"
#include "MstOsservazioniModDlg.h"
#include "MstProcedureDiagnosticheModDlg.h"
#include "MstProcedureTerapeuticheModDlg.h"
#include "NomenclatoreDlg.h"
#include "ObSelect.h"
#include "OccupazioneGiornalieraDlg.h"
#include "OperatoriDlg.h"
#include "OrganiSediDlg.h"
#include "OrganShowDlg.h"
#include "ParametriTabellaDlg.h"
#include "PasswordDlg.h"
#include "PazientiSet.h"
#include "PdfAnteprimaDlg.h"
#include "PdfCreator.h"
#include "PdfManager.h"
#include "PdfStampaDlg.h"
#include "ProcedureICD9Dlg.h"
#include "ProntFarmModDlg.h"
#include "RAODlg.h"
#include "ReportDlg.h"
#include "ReportsDefaultModDlg.h"
#include "ReportsEtichetteSet.h"
#include "ReportsMacroModDlg.h"
#include "RichiesteAnatomiaPatologicaDlg.h"
#include "RichiesteAnatomiaPatologicaPaviaDlg.h"
#include "SediEsameSet.h"
#include "SelezioneAnnoDlg.h"
#include "SetupDatabasesRemotiDlg.h"
#include "SetupDlg.h"
#include "SetupInterfacciaWEB.h"
#include "StampaDlg.h"
#include "StampaEtichetteDlg.h"
#include "StatisticheEsamiDlg.h"
#include "StreamingListDlg.h"
#include "StrumentiDlg.h"
#include "StudiDlg.h"
#include "TabComboDlg.h"
#include "TipoEsameDlg.h"
#include "TipoEsameSet.h"
#include "TrasferimentoDlg.h"
#include "UOSet.h"
#include "UOUtenteDlg.h"
#include "UuOoGruppiDlg.h"
#include "UuOoUtentiDlg.h"
#include "VistaEsamiPendentiSet.h"
#include "VisualizzatoreLogDlg.h"
#include "VisualizzatoreLogIntegrazioniDlg.h"
#include "Volume.h"
#include "WebDeployer.h"
#include "EsamiChiusiSet.h"
#include "TutorialFilesSet.h"
#include "CheckListElModDlg.h"
#include "ModCodiciClassifDiagDlg.h"
#include "ProtocolliModDlg.h"
#include "SelectNumeroFichaDlg.h"
#include "ExtPrestazioniSet.h"
#include "UtentiSet.h"
#include "MainFrm.h"
#include "GenomicaPatogenicitaDlg.h" // Julio BUG 3249
#include "GenomicaTipiVariantiDlg.h" // Julio BUG 3249
#include "GenomicaTipiAlterazioniDlg.h" // Julio BUG 3249
#include "GenomicaVariantiGeneticheDlg.h" // Julio BUG 3249
#include "GenomicaSezioniDlg.h" // Julio BUG 3249
#include "GenomicaTipiMaterialiDlg.h" // Julio BUG 3249
#include "GenomicaTipiRefertoDlg.h" // Julio BUG 3249
#include "GenomicaCorpoDlg.h" // Julio BUG 3249
#include "GenomicaFrasiRisultatoDlg.h" // Julio BUG 3249
#include "FoglioRiferimentoDlg.h" //Gabriel BUG 6225 - Lista DO
#include "FlussoDiStatoDlg.h" //Gabriel BUG 6225 - Lista DO
#include "RiconvocazioneDlg.h" //Gabriel BUG 6225 - Lista DO
#include "SetupUnitaTCPDlg.h" //Gabriel - TCP
#include "MeasurementsCalculationDlg.h" //Gabriel - BUG 5533 V2 - Cálculo medidas biométricas
#include "MeasurementsRulesDlg.h" //Gabriel - BUG 5533 V2 - Regras medidas biométricas

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////

void CEsamiView::OnCommand(UINT nID)
{
	switch(nID)
	{
		///////////////////
		// menù di endox //
		///////////////////

		case ID_FILE_LOGOUT:
		{
			if (theApp.m_bTerminalServer && (theApp.m_lLoginMode == 0))
				AfxGetMainWnd()->PostMessage(WM_CLOSE);
			else
				OnCommandFileLogout();
			break;

		}
		case ID_FILE_CHANGEPASSWORD:
		{
			OnCommandFileChangePassword();
			break;
		}
		case ID_INFO_USER:
		{
			OnCommandInfoUser();
			break;
		}
		case ID_FILE_GESTIONEUTENTI:
		{
			OnCommandFileGestioneUtenti();
			break;
		}
		case ID_FILE_ASSOCIAZIONEUTENTIUNITAOPERATIVE:
		{
			OnCommandFileAssociazioneUtentiUnitaOperative();
			break;
		}
		case ID_FILE_CAMBIOUO:
		{
			OnCommandFileCambioUO();
			break;
		}
		case ID_FILE_CAMBIOPASSWORDELIMINAZIONEPDF:
		{
			OnCommandFileCambioPasswordEliminazionePdf();
			break;
		}
		case ID_FILE_STAMPAIMMAGINI:
		{
			OnCommandMenuFileStampaImmagini();
			break;
		}
		case ID_FILE_ANTEPRIMAIMMAGINI:
		{
			OnCommandMenuFileAnteprimaImmagini();
			break;
		}
		case ID_FILE_STAMPAREPORT:
		{
			OnCommandMenuFileStampaReport();
			break;
		}
		case ID_FILE_ANTEPRIMAREPORT:
		{
			OnCommandMenuFileAnteprimaReport();
			break;
		}
		case ID_FILE_STAMPAETICHETTE:
		{
			OnCommandMenuFileStampaEtichette();
			break;
		}
		case ID_FILE_INTESTAZIONEREFERTO:
		{
			OnCommandMenuFileIntestazioneReferto();
			break;
		}
		case ID_FILE_IMPOSTAPAGINA:
		{
			OnCommandMenuFileImpostaPagina();
			break;
		}
		case ID_FILE_SELTWAIN:
		{
			OnCommandMenuFileSelTwain();
			break;
		}
		case ID_FILE_INQUIERO_1:
		{
			OnCommandFileInquiero1();
			break;
		}
		case ID_FILE_INQUIERO_2:
		{
			OnCommandFileInquiero2();
			break;
		}
		case ID_FILE_SPOSTAESAME:
		{
			OnCommandFileSpostaEsame();
			break;
		}
		case ID_APP_EXIT:
		{
			AfxGetMainWnd()->PostMessage(WM_CLOSE);
			break;
		}

		case ID_GESTIONE_NOMENCLATORE:
		{
			OnCommandMenuGestioneNomenclatore();
			break;
		}
		case ID_GESTIONE_STATISTICHEESAMI:
		{
			OnCommandMenuGestioneStatisticheEsami();
			break;
		}
		case ID_GESTIONE_VISUALIZZASTAMPE:
		{
			OnCommandMenuGestioneVisualizzaStampe(TRUE);
			break;
		}
		case ID_GESTIONE_SOSPESIISTOLOGICI:
		{
			OnCommandMenuGestioneSospesiIstologici();
			break;
		}
		case ID_GESTIONE_VISUALIZZATORELOG:
		{
			OnCommandMenuGestioneVisualizzatoreLog();
			break;
		}
		case ID_GESTIONE_LOGSINTETICO:
		{
			OnCommandMenuGestioneLogSintetico();
			break;
		}
		case ID_GESTIONE_VISUALIZZATORELOGIMPORTAZIONECASI:
		{
			OnCommandMenuGestioneVisualizzatoreLogImportazioneCasi();
			break;
		}
		case ID_GESTIONE_STATISTICHE:
		{
			OnCommandMenuGestioneStatistiche();
			break;
		}
		case ID_GESTIONE_CONFIGSTATISTICHE:
		{
			OnCommandMenuGestioneConfigStatistiche();
			break;
		}
		case ID_GESTIONE_ESAMIPENDENTI:
		{
			OnCommandMenuGestioneEsamiPendenti();
			break;
		}		
		case ID_GESTIONE_LOGINTEGRAZIONI:
		{
			OnCommandMenuGestioneLogIntegrazioni();
			break;
		}
		case ID_GESTIONE_INVIAVIDEO:
		{
			OnCommandMenuGestioneInviaVideo();
			break;
		}
		case ID_GESTIONE_ACCESSOSEDIESTERNE:
		{
			OnCommandMenuGestioneAccessoSediEsterne();
			break;
		}
		case ID_GESTIONE_ITENSFICHA:
		{
			OnCommandMenuGestioneItensFicha();
			break;
		}
		case ID_GESTIONE_PERSONIFICAR:
		{
			OnCommandMenuGestionePersonificacao();
			break;
		}
		//Gabriel BUG 6225 - Lista DO
		case ID_GESTIONE_FLUSSODISTATO:
		{
			OnCommandMenuGestioneFlussoDiStato();
			break;
		}
		case ID_ESAMECORRENTE_DESCONJUGARITENS:
		{
			OnCommandMenuGestioneDesconjugarItens();
			break;
		}
		case ID_ARCHIVI_ORGANISEDI:
		{
			OnCommandMenuArchiviOrganiSedi();
			break;
		}

		case ID_ARCHIVI_CENTRIDICOSTO:
		{
			OnCommandMenuArchiviCentriDiCosto();
			break;
		}

		case ID_ARCHIVI_CODIFICAREGIONALE:
		{
			OnCommandMenuArchiviCodificaRegionale();
			break;
		}
		case ID_ARCHIVI_GRUPPIPRESTAZIONI:
		{
			OnCommandMenuArchiviGruppiPrestazioni();
			break;
		}
		case ID_ARCHIVI_GRUPPIPRESTAZIONI_RICETTA:
		{
			OnCommandMenuArchiviGruppiPrestazioniRicetta();
			break;
		}
		case ID_ARCHIVI_TIPIPRELIEVI:
		{
			OnCommandMenuArchiviTipiPrelievi();
			break;
		}
		case ID_ARCHIVI_PROCEDUREPRELIEVI:
		{
			OnCommandMenuArchiviProcedurePrelievi();
			break;
		}
		case ID_ARCHIVI_GRUPPIPRELIEVI:
		{
			OnCommandMenuArchiviGruppiPrelievi();
			break;
		}
		case ID_VARI_DIAGNOSIISTOLOGICA:
		{
			OnCommandMenuVariDiagnosiIstologica();
			break;
		}
		case ID_VARI_BOSTONSCORE:
		{
			OnCommandMenuVariBostonScore();
			break;
		}
		case ID_VARI_CODICIDICLASSIFICAZIONEDIAGNOSTICA:
		{
			OnCommandMenuVariCodiciClassificazioneDiagnostica();
			break;
		}
		case ID_VARI_PROTOCOLLI:
		{
			OnCommandMenuVariProtocolli();
			break;
		}
		case ID_VARI_MEDIDASBIOMETRICAS:
		{
			OnCommandMenuVariMedidasBiometricas();
			break;
		}
		// Marvel Carvalho - BUG 4308 Esquemas Anatômicos Fleury
		case ID_VARI_SCHEMIANATOMICIRECORD:
		{
			OnCommandMenuVariSchemiAnatomiciRecord();
			break;
		}
		//Gabriel BUG 6225 - Lista DO
		case ID_VARI_FOGLIORIFERIMENTO:
		{
			if (theApp.m_bAtivaListaDO)
				OnCommandMenuVariFoglioRiferimento();
			break;
		}
		//Gabriel - BUG 5533 V2 - Cálculos medidas biométricas
		case ID_VARI_CALCOLOMEDIDASBIOMETRICAS:
		{
			if (theApp.m_bAtivaEspermograma)
				OnCommandMenuVariCalcoloMedidasBiometricas();
			break;
		}
		//Gabriel - BUG 5533 V2 - Regras medidas biométricas
		case ID_VARI_REGOLEMEDIDASBIOMETRICAS:
		{
			if (theApp.m_bAtivaEspermograma)
				OnCommandMenuVariRegoleMedidasBiometricas();
			break;
		}
		case ID_ARCHIVI_MALATTIECRONICHE:
		{
			OnCommandMenuArchiviMalattieCroniche();
			break;
		}
		case ID_ARCHIVI_ESAMI:
		{
			OnCommandMenuArchiviEsami();
			break;
		}
		case ID_ESAMI_FASI:
		{
			OnCommandMenuEsamiFasi();
			break;
		}
		case ID_ARCHIVI_FRASIRTF:
		{
			OnCommandMenuArchiviFrasiRTF();
			break;
		}
		case ID_ARCHIVI_FRASISTANDARD:
		{
			OnCommandMenuArchiviFrasiStandard();
			break;
		}
		case ID_ARCHIVI_FRASIPOSTESAME:
		{
			OnCommandMenuArchiviFrasiPostEsame();
			break;
		}
		case ID_ARCHIVI_MST_INDICAZIONI:
		{
			OnCommandMenuArchiviMstIndicazioni();
			break;
		}
		case ID_ARCHIVI_MST_OSSERVAZIONI:
		{
			OnCommandMenuArchiviMstOsservazioni();
			break;
		}
		case ID_ARCHIVI_MST_PROCDIAGNOSTICHE:
		{
			OnCommandMenuArchiviMstProcDiagnostiche();
			break;
		}
		case ID_ARCHIVI_MST_PROCTERAPEUTICHE:
		{
			OnCommandMenuArchiviMstProcTerapeutiche();
			break;
		}
		case ID_ARCHIVI_MST_DIAGNOSI:
		{
			OnCommandMenuArchiviMstDiagnosi();
			break;
		}
		case ID_ARCHIVI_MST_CODDIAGNOSIESAME:
		{
			OnCommandMenuArchiviMstCodificaDiagnosiEsame();
			break;
		}
		case ID_ARCHIVI_MST_COMPLICANZE1:
		{
			OnCommandMenuArchiviMstComplicanze1();
			break;
		}
		case ID_ARCHIVI_MST_COMPLICANZE2:
		{
			OnCommandMenuArchiviMstComplicanze2();
			break;
		}
		case ID_ARCHIVI_MST_COMPLICANZE3:
		{
			OnCommandMenuArchiviMstComplicanze3();
			break;
		}
		case ID_ARCHIVI_ALTRETABELLE:
		{
			OnCommandMenuArchiviAltreTabelle();
			break;
		}
		case ID_ARCHIVI_STRUMENTI:
		{
			OnCommandMenuArchiviStrumenti();
			break;
		}
		case ID_ARCHIVI_ETICHETTE_ANAMNESI:
		{
			OnCommandMenuArchiviEtichetteAnamnesi();
			break;
		}
		case ID_ARCHIVI_ETICHETTE:
		{
			OnCommandMenuArchiviEtichette();
			break;
		}
		case ID_ARCHIVI_PRONTFARMACEUTICO:
		{
			OnCommandMenuArchiviProntuarioFarmaceutico();
			break;
		}
		case ID_ARCHIVI_PRONTFARMACEUTICO_RICETTA:
		{
			OnCommandMenuArchiviProntuarioFarmaceuticoRicetta();
			break;
		}
		case ID_ARCHIVI_RAO:
		{
			OnCommandMenuArchiviRAO();
			break;
		}
		case ID_ARCHIVI_STUDI:
		{
			OnCommandMenuArchiviStudi();
			break;
		}
		case ID_ARCHIVI_REPORTSDEFAULT:
		{
			OnCommandMenuArchiviReportsDefault();
			break;
		}
		case ID_ARCHIVI_MACRODISTAMPA:
		{
			OnCommandMenuArchiviMacroDiStampa();
			break;
		}
		case ID_ARCHIVI_MEDICI:
		{
			OnCommandMenuArchiviMedici();
			break;
		}
		case ID_ARCHIVI_MEDICICURANTI:
		{
			OnCommandMenuArchiviMediciCuranti();
			break;
		}
		case ID_ARCHIVI_MEDICIINVIANTI:
		{
			OnCommandMenuArchiviMediciInvianti();
			break;
		}
		case ID_ARCHIVI_INFERMIERI:
		{
			OnCommandMenuArchiviInfermieri();
			break;
		}
		case ID_ARCHIVI_INVIANTI_INT:
		{
			OnCommandMenuArchiviInviantiInt();
			break;
		}
		case ID_ARCHIVI_INVIANTI_EXT:
		{
			OnCommandMenuArchiviInviantiExt();
			break;
		}
		case ID_ARCHIVI_TRASFERIMPARZIALE:
		{
			OnCommandMenuArchiviTrasferimParziale();
			break;
		}
		case ID_ARCHIVI_TRASFERIMTOTALE:
		{
			OnCommandMenuArchiviTrasferimTotale();
			break;
		}
		case ID_ARCHIVI_ESPELLI_OD:
		{
			OnCommandMenuArchiviEjectVolume();
			break;
		}
		case ID_ARCHIVI_OCCUPAZIONEGIORNALIERA:
		{
			OnCommandMenuArchiviOccupazioneGiornaliera();
			break;
		}
		case ID_ARCHIVI_BACKUPDATI:
		{
			switch(theApp.m_lBackupDVD)
			{
				case 1:
				{
					OnCommandMenuArchiviBackupDati();
					break;
				}
				case 2:
				{
					OnCommandMenuArchiviBackupDatiDoppiaCopia();
					break;
				}
			}
			break;
		}
		case ID_ARCHIVI_SALVAVALORIDEFAULT:
		{
			OnCommandMenuArchiviSalvaValoriDefault();
			break;
		}
		case ID_ARCHIVI_IMPORTACASO:
		{
			OnCommandMenuArchiviImportaCaso();
			break;
		}
		case ID_ARCHIVI_ESAMEINTEGRATO:
		{
			OnCommandMenuArchiviEsameIntegrato();
			break;
		}
		case ID_ARCHIVI_PARAMETRITABELLAECOCARDIOGRAFIA:
		{
			OnCommandMenuArchiviParametriTabellaEcocardiografia();
			break;
		}
		case ID_ARCHIVI_COMMENTIIMMAGINI:
		{
			OnCommandMenuArchiviCommentiImmagini();
			break;
		}
		case ID_ARCHIVI_STOREPACSIMAGE:
		{
			OnCommandMenuArchiviStorePacsImage();
			break;
		}
		case ID_ARCHIVI_PROCEDUREICD9:
		{
			OnCommandMenuArchiviProcedureICD9();
			break;
		}
		case ID_ARCHIVI_GRUPPIDIPROCEDUREICD9:
		{
			OnCommandMenuArchiviGruppiProcedureICD9();
			break;
		}
		case ID_ARCHIVI_DIAGNOSIICD9:
		{
			OnCommandMenuArchiviDiagnosiICD9();
			break;
		}
		case ID_ARCHIVI_GRUPPIDIDIAGNOSIICD9:
		{
			OnCommandMenuArchiviGruppiDiagnosiICD9();
			break;
		}
		case ID_ARCHIVI_ASSOCIAZIONIICD9:
		{
			OnCommandMenuArchiviAssociazioniICD9();
			break;
		}
		case ID_GENOMICA_PATOGENICITA://Julio BUG 3249
		{
			OnCommandMenuArchiviPatogenicita();
			break;
		}
		case ID_GENOMICA_TIPIVARIANTIGENETICHE://Julio BUG 3249
		{
			OnCommandMenuArchiviTipiVariantiGenetiche();
			break;
		}
		case ID_GENOMICA_TIPIALTERAZIONI://Julio BUG 3249
		{
			OnCommandMenuArchiviTipiAlterazioni();
			break;
		}
		case ID_GENOMICA_VARIANTIGENETICHE://Julio BUG 3249
		{
			OnCommandMenuArchiviVariantiGenetiche();
			break;
		}
		case ID_GENOMICA_SEZIONIREFERTO://Julio BUG 3249
		{
			OnCommandMenuArchiviSezioniReferto();
			break;
		}
		case ID_GENOMICA_TIPIREFERTO://Julio BUG 3249
		{
			OnCommandMenuArchivTipiReferto();
			break;
		}
		case ID_GENOMICA_CORPOREFERTO://Julio BUG 3249
		{
			OnCommandMenuArchiviCorpoReferto();
			break;
		}
		case ID_GENOMICA_TIPIMATERIALI://Julio BUG 3249
		{
			OnCommandMenuArchiviTipiMateriali();
			break;
		}
		case ID_GENOMICA_FRASIRISULTATO://Julio BUG 3249
		{
			OnCommandMenuArchiviFrasiRisultato();
			break;
		}
		//SALA INTEGRATA
		case ID_ROUTING_AUDIO:
		{		
			OnCommandMenuRoutingAudio();
			break;
		}
		case ID_ROUTING_VIDEO:
		{			
			OnCommandMenuRoutingVideo();
			break;
		}
		case ID_STREAMING_ATTIVAZIONEUTENTI:
		{
			OnCommandMenuAttivazioneUtenti();
			break;
		}
		case ID_CONNESSIONEREMOTA:
		{
			OnCommandMenuConnessioneRemota();
			break;
		}

		case ID_OPZIONI_INTEGRAZIONI:
		{
			OnCommandMenuArchiviIntegrazioni();
			break;
		}		
		case ID_OPTION_ORGAN:
		{
			OnCommandMenuOpzioniOrgani();
			break;
		}
		case ID_OPTION_CALIB:
		{
			OnCommandMenuOpzioniCalib();
			break;
		}
		case ID_OPTION_SETUP:
		{
			OnCommandMenuOpzioniSetup();
			break;
		}
		case ID_OPTION_PATHS:
		{
			OnCommandMenuArchiviBackup();
			break;
		}
		case ID_OPTION_ACQ:
		{
			OnCommandMenuOpzioniAcquisizione();
			break;
		}
		case ID_OPTION_WEB:
		{
			OnCommandMenuOpzioniInterfacciaWEB();
			break;
		}
		case ID_SETUP_DBASE:
		{
			OnCommandSetupDbase();
			break;
		}
		case ID_OPTION_OPERATOR:
		{
			OnCommandMenuOpzioniDisegnaOperator();
			break;
		}
		case ID_OPTION_REPORT:
		{
			OnCommandMenuOpzioniDisegnaReport();
			break;
		}
		case ID_OPTION_CAMPIOBBLIGATORI:
		{
			OnCommandMenuOpzioniCampiObbligatori();
			break;
		}
		case ID_OPZIONI_DISATTIVAFIRMAPERQUESTOESAME:
		{
			OnCommandMenuOpzioniDisattivaFirmaPerQuestoEsame();
			break;
		}
		case ID_OPZIONI_SETUPDATABASESREMOTI:
		{
			OnCommandMenuOpzioniSetupDatabasesRemoti();
			break;
		}
		case ID_HELP:
		{
			AfxGetMainWnd()->SendMessage(WM_MY_HELP);
			break;
		}
		case ID_APP_ABOUT:
		{
			CAboutBoxDlg().DoModal();
			break;
		}
		case ID_ARCHIVI_ACCESSORI:
		{
			OnCommandMenuArchiviAccessori();
			break;
		}
		case ID_ARCHIVI_FARMACIMONITORAGGIO:
		{
			OnCommandMenuArchiviFarmaciMonitoraggio();
			break;
		}
		case ID_FARMACI_FARMACIPAZIENTICRONICI:
		{
			OnCommandMenuArchiviFarmaciPazientiCronici();
			break;
		}
		case ID_ARCHIVI_CHECKLIST:
		{
			OnCommandMenuArchiviCheckList();
			break;
		}
		case ID_ARCHIVI_ESENZIONERICETTA:
		{
			OnCommandMenuArchiviEsenzioneRicetta();
			break;
		}
		case ID_ARCHIVI_DOSIMONITORAGGIO:
		{
			OnCommandMenuArchiviDosiMonitoraggio();
			break;
		}
		case ID_ARCHIVI_COMPLICANZEIMMEDIATE:
		{
			OnCommandMenuArchiviComplicanzeImmediate();
			break;
		}
		case ID_ARCHIVI_COMPLICANZETARDIVE:
		{
			OnCommandMenuArchiviComplicanzeTardive();
			break;
		}
		case ID_ARCHIVI_PULIZIA:
		{
			OnCommandMenuArchiviPulizia();
			break;
		}
		case ID_ARCHIVI_CAUSENONCOMPLETEZZA:
		{
			OnCommandMenuArchiviCauseNonCompletamento();
			break;
		}
		case ID_ARCHIVI_TOLLERANZA:
		{
			OnCommandMenuArchiviTolleranza();
			break;
		}
		case ID_ARCHIVI_CONCLUSIONICOLON:
		{
			OnCommandMenuArchiviConclusioniColon();
			break;
		}
		case ID_ARCHIVI_CONCLUSIONISCREENING:
		{
			OnCommandMenuArchiviConclusioniScreening();
			break;
		}
		case ID_ARCHIVI_DIAGNOSIFINALE:
		{
			OnCommandMenuArchiviDiagnosiFinale();
			break;
		}
		case ID_ARCHIVI_ALTREANOMALIE:
		{
			OnCommandMenuArchiviAltreAnomalie();
			break;
		}
		case ID_REPERTI_ASPETTOMACRO:
		{
			OnCommandMenuArchiviRepAspettoMacro();
			break;
		}
		case ID_REPERTI_GRADODISPLASIA:
		{
			OnCommandMenuArchiviRepGradoDisplasia();
			break;
		}
		case ID_REPERTI_ISTOLOGIA:
		{
			OnCommandMenuArchiviRepIstologia();
			break;
		}
		case ID_REPERTI_NOTIZIETERAPIA:
		{
			OnCommandMenuArchiviRepNotizieTerapia();
			break;
		}
		case ID_REPERTI_REGIONE:
		{
			OnCommandMenuArchiviRepRegione();
			break;
		}
		case ID_REPERTI_TECNICA:
		{
			OnCommandMenuArchiviRepTecnica();
			break;
		}
		case ID_REPERTI_TIPILESIONE:
		{
			OnCommandMenuArchiviRepTipoLesione();
			break;
		}
		case ID_REPERTI_TRATTAMENTO:
		{
			OnCommandMenuArchiviRepTrattamento();
			break;
		}		
		case ID_OPZIONI_SETUPCOLORI:
		{
			OnCommandSetupColori();
			break;
		}
		// Luiz - 13/05/2019 - P3 - Atualiza nome/sobrenome Médico e Paciente - Inclui Médicos solicitantes
		case ID_ATUALIZA_MEDICO_SOLICITANTE:
		{
			//LuizMEDICOSOLINIBIDO OnCommandAtualizaMedicoSolicitante();
			break;
		}
		//Gabriel BUG 6225 - Lista DO
		case ID_ESAMECORRENTE_RECONVOCAZIONE:
		{
			OnCommandMenuEsameCorrenteReconvocazione();
			break;
		}
		//Gabriel - TCP
		case ID_OPZIONI_SETUPUNITATCP:
		{
			if (theApp.m_bAtivaTCP)
				OnCommandMenuOpzioniSetupUnitaTCP();
			break;
		}
		default:
		{
			if ((nID > MENU_STAMPA_ETICHETTE) && (nID < MENU_TUTORIAL_FILES))
			{
				// Sandro 22/10/2015 // su richiesta di Petardo carico il numero delle stampe dalle impostazioni della stampante associata al report //

				CString sRptFile = CReportsEtichetteSet().GetReportFile(nID - MENU_STAMPA_ETICHETTE);
				long lNumeroCopie = 0;

				// provo a precaricare il report //

				BOOL bContinue = FALSE;
				STRUCT_STAMPA structStampa;
				if (!sRptFile.IsEmpty())
					bContinue = SelezionaFileReport(&structStampa, sRptFile);

				// vedo se il report è associato ad una stampante predefinita //

				if (bContinue)
				{
					HGLOBAL hDevNames = NULL;
					HGLOBAL hDevMode = NULL;
					if (LoadPrinterSettingsFromNumber(structStampa.m_lPrinterToUse, &hDevNames, &hDevMode))
					{
						// se becco l'impostazione della stampante mi carico il numero di copie impostate //

						LPDEVMODE lpDevMode = (LPDEVMODE)::GlobalLock(hDevMode);

						if (lpDevMode != NULL)
							lNumeroCopie = lpDevMode->dmCopies;

						::GlobalUnlock(hDevMode);
					}
				}

				// procedo con la stampa //
				long lPdfId = 0;
				AnteprimaStampaReport(STAMPA, VERIFICA_NO, sRptFile, FALSE, lNumeroCopie, &lPdfId,"");
			}

			// Sandro 20/06/2016 // RIMA 16001 //
			if ((nID > MENU_TUTORIAL_FILES) && (nID < FASI_ESAME))
			{
				long lIDTutorialFile = nID - MENU_TUTORIAL_FILES;
				CString sTutorialFile = CTutorialFilesSet().GetIndirizzoCompleto(lIDTutorialFile);

				if ((long)ShellExecute(NULL, "open", sTutorialFile, NULL, NULL, SW_SHOWMAXIMIZED) == ERROR_FILE_NOT_FOUND)
					theApp.AfxMessageBoxEndo("File " + sTutorialFile + " " + theApp.GetMessageString(IDS_NOT_FOUND), MB_ICONSTOP);
			}

			break;
		}
	}

    //Sopra i 62000 ho le fasi dell'esame
	if (nID > FASI_ESAME + 1000)
	{        
        //tasti disattiva chiusura
		int idFase = nID - (FASI_ESAME + 1000);
		OnCommandAnnullaChiudiFase(idFase);
	}
	else if (nID > FASI_ESAME)
	{
        //tasti chiusura
		int idFase = nID - FASI_ESAME;
		OnCommandChiudiFase(idFase);
	}
}

/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////

void CEsamiView::OnCommandFileLogout()
{
	Logout(TRUE);
}

void CEsamiView::OnCommandFileChangePassword()
{
	AMLogin_ChangePassword(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto);
}

void CEsamiView::OnCommandInfoUser()
{
	AMLogin_ViewUserRights();
}

void CEsamiView::OnCommandFileGestioneUtenti()
{
	AMLogin_AdministrationDlg(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto);
}

void CEsamiView::OnCommandFileAssociazioneUtentiUnitaOperative()
{
	if (theApp.m_lLoginMode == 0)
		CUuOoUtentiDlg(this).DoModal();
	else
		CUuOoGruppiDlg(this).DoModal();
}

// Sandro 15/05/2015 //
void CEsamiView::OnCommandFileCambioUO()
{
	if (theApp.m_nProgramMode != NOTHING_MODE)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAMIVIEW_LOGOUT), MB_ICONSTOP);
		return;
	}

	//
	BeginWaitCursor();

	// Sandro 26/11/2014 //
	CUOSet().VerificaUODefault();

	//
	long lUserID = 0;
	AMLogin_GetUserID(&lUserID);
	CUOUtenteDlg dlg(this, lUserID);
	dlg.DoModal();

	if (theApp.m_lUO <= 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_NESSUNA_UO));
		theApp.m_lIDEsameFirmaDisattivata = 0;
		AMLogin_Logout();
		theApp.m_lUO = 0; // Sandro 16/11/2015 // RAS 201500080 //
		AfxGetMainWnd()->PostMessage(WM_CLOSE);
		return;
	}

	// Sandro 13/10/2015 // sposto tutto in una nuova funzione...
	RicaricaDatiDopoCambioUO();

	//
	EndWaitCursor();
}

void CEsamiView::OnCommandFileCambioPasswordEliminazionePdf()
{
	CCambioPasswordDlg(this).DoModal();
}

void CEsamiView::OnCommandMenuFileStampaImmagini() 
{
	if (theApp.m_bPersonalizzazioniBrasileFleury && !m_pEsamiSet->m_sFleuryTrasferito.IsEmpty() || m_pEsamiSet->m_lStatoInvioCentraleRefertaz > 0) //Julio 04/05/2018
	{
		theApp.AfxMessageBoxEndo("A operação não pode ser realizada pois o exame não se encontra na unidade atual");
		return;
	}

	BOOL bStampa = TRUE;

	CString sMessaggio = "";
	if (theApp.m_bPersonalizzazioniBrasileFleury)
		bStampa = FleuryPossoStampare(sMessaggio, m_pEsamiSet->m_sRicovero, m_pEsamiSet->m_sCodEsame);

	if (bStampa)
		AnteprimaStampaImmagini(STAMPA, LOCAL_IMAGES, 1);
	else
		theApp.AfxMessageBoxEndo(sMessaggio);
}

void CEsamiView::OnCommandMenuFileAnteprimaImmagini() 
{
	if (theApp.m_bPersonalizzazioniBrasileFleury && !m_pEsamiSet->m_sFleuryTrasferito.IsEmpty() || m_pEsamiSet->m_lStatoInvioCentraleRefertaz > 0) //Julio 04/05/2018
	{
		theApp.AfxMessageBoxEndo("A operação não pode ser realizada pois o exame não se encontra na unidade atual");
		return;
	}

	AnteprimaStampaImmagini(ANTEPRIMA, LOCAL_IMAGES, 1);
}

void CEsamiView::OnCommandMenuFileStampaReport() 
{
	// Sandro 27/02/2014 // richiesta Paron Pilotto //
	if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
	{
		if (theApp.m_bPersonalizzazioniBrasileFleury && !m_pEsamiSet->m_sFleuryTrasferito.IsEmpty() || m_pEsamiSet->m_lStatoInvioCentraleRefertaz > 0) //Julio 04/05/2018
		{
			theApp.AfxMessageBoxEndo("A operação não pode ser realizada pois o exame não se encontra na unidade atual");
			return;
		}
		
		if (m_pEsamiSet->m_bSuperLocked != TRUE && !theApp.m_bUsaLaudoProvisorio) //Julio 13/03/2018
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAME_NON_CHIUSO));
			return;
		}
	}

	
	//Julio 17/08/2018 - se e laudo provisorio o usuario tem que escolher qual a impressora
	if (theApp.m_bUsaLaudoProvisorio) 
		theApp.m_bLoadPrinterSettings = FALSE;
	
	long lPdfId = 0;	
	AnteprimaStampaReport(STAMPA, VERIFICA_SI, "", FALSE, 0, &lPdfId,""); // <-- chiede il report //
	
	theApp.m_bLoadPrinterSettings = TRUE;
}

void CEsamiView::OnCommandMenuFileAnteprimaReport() 
{
	if (theApp.m_bPersonalizzazioniBrasileFleury && !m_pEsamiSet->m_sFleuryTrasferito.IsEmpty() || m_pEsamiSet->m_lStatoInvioCentraleRefertaz > 0) //Julio 04/05/2018
	{
		theApp.AfxMessageBoxEndo("A operação não pode ser realizada pois o exame não se encontra na unidade atual");
		return;
	}

	// Sandro 27/02/2014 // richiesta Paron Pilotto //
	if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
	{
		if (m_pEsamiSet->m_bSuperLocked != TRUE && !theApp.m_bUsaLaudoProvisorio) //Julio 13/03/2018
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAME_NON_CHIUSO));
			return;
		}
	}

	//
	long lPdfId = 0;
	AnteprimaStampaReport(ANTEPRIMA, VERIFICA_SI, "", FALSE, 0, &lPdfId,""); // <-- chiede il report //
}

void CEsamiView::OnCommandMenuFileStampaEtichette()
{
	long lPdfId = 0;
	AnteprimaStampaReport(STAMPA, VERIFICA_NO, theApp.m_sEditRep + "\\Indirizzi.rpa", FALSE, 1, &lPdfId,"");
}

void CEsamiView::OnCommandMenuFileIntestazioneReferto()
{
	CIntestazioneNewDlg dlg(this, this);
	dlg.DoModal();
}

void CEsamiView::OnCommandMenuFileImpostaPagina() 
{
	CStampaDlg dlg(this, this);
	
	if (dlg.DoModal() == IDOK)
		theApp.SaveSetting();
}

void CEsamiView::OnCommandMenuFileSelTwain() 
{
	TCHAR szProcess[1024];
	sprintf_s(szProcess, 
			"%s\\xTwain\\xTwain.exe", // xTAIUAN //
			theApp.m_sDirProg);

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(NULL, szProcess, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		LPVOID lpMsgBuf;
		if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL))
			theApp.AfxMessageBoxEndo((LPCTSTR)lpMsgBuf);
		else
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_NOT_DEFINED));
		LocalFree( lpMsgBuf );
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

void CEsamiView::OnCommandFileInquiero1()
{
	CBrowserDlg dlg("http://www.tesi.mi.it/Tesi/AreaServizi/TeleConsultoOpe2.html", this);
	dlg.DoModal();
}

void CEsamiView::OnCommandFileInquiero2()
{
	CBrowserDlg dlg("http://www.tesi.mi.it/Tesi/AreaServizi/TeleConsultoClient2.html", this);
	dlg.DoModal();
}


void CEsamiView::OnCommandFileSpostaEsame()
{
	// Luiz - 25/02/2019 - P3 - Exigir senha para acesso ao menu
	if (CPasswordDlg(this, theApp.GetMessageString(IDS_PASSWORD_SETUP), "nautilus").DoModal() == IDOK)
	{
		if ((m_pEsamiSet != NULL) && (m_pEsamiSet->IsOpen()) && (!m_pEsamiSet->IsBOF()) && (!m_pEsamiSet->IsEOF()))
		{
			if (theApp.MessageBoxEndo(theApp.GetMessageString(IDS_ESAMIVIEW_SPOSTAESAME_1), theApp.GetMessageString(IDS_ACHTUNG), MB_YESNO | MB_ICONSTOP) == IDYES)
			{
				long lIDEsame = m_pEsamiSet->m_lContatore;

				long lIDPazienteOld = m_pPazientiSet->m_lContatore;
				OnPazienteNew();
				long lIDPazienteNew = m_pPazientiSet->m_lContatore;

				if ((lIDPazienteOld > 0) && (lIDPazienteNew > 0) && (lIDPazienteOld != lIDPazienteNew))
				{
					// sposto i documenti allegati all'esame //
					AmDocManager_MoveDocExam(theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, lIDPazienteOld, lIDPazienteNew, lIDEsame);

					// sposto i PDF allegati //
					CPdfManager pdfManager;
					pdfManager.MovePdfEx(lIDPazienteOld, lIDPazienteNew, lIDEsame);

					// sposto immagini e filmati //
					m_pImgManager->MoveImg(lIDPazienteOld, lIDEsame, lIDPazienteNew);

					// sposto i record degli esami //
					CString strFilter;
					strFilter.Format("Contatore=%li", lIDEsame);

					CEsamiSet setEsami;
					setEsami.SetOpenFilter(strFilter);
					if (setEsami.OpenRecordset("CEsamiView::OnCommandFileSpostaEsame"))
					{
						if (!setEsami.IsEOF())
						{
							if (setEsami.EditRecordset("CEsamiView::OnCommandFileSpostaEsame"))
							{
								setEsami.m_lPaziente = lIDPazienteNew;
								setEsami.UpdateRecordset("CEsamiView::OnCommandFileSpostaEsame");

								RicercaCodicePaziente(lIDPazienteNew, 0, FALSE, TRUE);
								MovePazientiAndEsami(NULL, TRUE, TRUE);
							}
						}

						setEsami.CloseRecordset("CEsamiView::OnCommandFileSpostaEsame");
					}

					// e che facciamo con le familiarità che sono legate direttamente al paziente ?!? //
				}
			}
		}
	}
}

void CEsamiView::OnCommandMenuGestioneNomenclatore()
{
	CNomenclatoreDlg dlg(this, this);
	dlg.DoModal();
}

void CEsamiView::OnCommandMenuGestioneStatisticheEsami()
{
	CSelezioneAnnoDlg dlg1(this);
	if (dlg1.DoModal() == IDOK)
	{
		CString strMessage;
		strMessage.Format(theApp.GetMessageString(IDS_CONFERMA_STATISTICA_ANNO), dlg1.GetAnno());

		if (theApp.AfxMessageBoxEndo(strMessage, MB_YESNO) == IDYES)
		{
			CStatisticheEsamiDlg dlg2(this, dlg1.GetAnno());
			dlg2.DoModal();
		}
	}
}

BOOL CEsamiView::OnCommandMenuGestioneVisualizzaStampe(BOOL bShowErrors)
{
	CPdfManager PdfManager;
	BOOL bReturn = FALSE;
	if (!PdfManager.IsInitialize())
	{
		if (bShowErrors)
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PDFMANAGER_ERROR));
		return FALSE;
	}

	CPdfList listPdf;
	PdfManager.GetPdf(m_pEsamiSet->m_lContatore, &listPdf);

	CList<CArchivioStampeDlg::tagPDFVIEW> listViewPdf;
	for(POSITION pos = listPdf.GetHeadPosition(); pos;)
	{
		PDF pdf = listPdf.GetNext(pos);

		CString strDescription;
		switch(pdf.ptTipo)
		{
			case pdftype_report:
			{
				// if (theApp.m_bPDFVisualizzaNomeReport) // Sandro 12/03/2015 //
				{
					CString sNomeReferto = CString(pdf.szNote);

					// elimino l'estensione //
					int nPos = sNomeReferto.ReverseFind('.');
					if (nPos > 0)
						sNomeReferto = sNomeReferto.Left(nPos);

					// cerco la barra "/" //
					nPos = sNomeReferto.ReverseFind('/');

					// se non trovo la barra "/" allora cerco la barra "\" //
					if (nPos < 0)
						nPos = sNomeReferto.ReverseFind('\\');

					// tolgo tutta la parte iniziale del percorso //
					if (nPos >= 0)
						sNomeReferto = sNomeReferto.Mid(nPos + 1, sNomeReferto.GetLength() - nPos);

					//
					sNomeReferto.MakeUpper();
					sNomeReferto.Trim();
			
					//
					if (pdf.bAnnullato)
					{
						if (!sNomeReferto.IsEmpty())
							strDescription.Format("%s - %s", theApp.GetMessageString(IDS_PDF_TYPE_2), sNomeReferto);
						else
							strDescription = theApp.GetMessageString(IDS_PDF_TYPE_2);
					}
					else if (pdf.bSospeso)
					{
						if (!sNomeReferto.IsEmpty())
							strDescription.Format("%s - %s", theApp.GetMessageString(IDS_PDF_TYPE_7), sNomeReferto);
						else
							strDescription = theApp.GetMessageString(IDS_PDF_TYPE_7);
					}
					else if (pdf.bFirmato)
					{
						if (pdf.lIDPdfCheSostituisce > 0)
						{
							if (!sNomeReferto.IsEmpty())
								strDescription.Format("%s - %s", theApp.GetMessageString(IDS_PDF_TYPE_5), sNomeReferto);
							else
								strDescription = theApp.GetMessageString(IDS_PDF_TYPE_5);
						}
						else
						{
							if (!sNomeReferto.IsEmpty())
								strDescription.Format("%s - %s", theApp.GetMessageString(IDS_PDF_TYPE_1), sNomeReferto);
							else
								strDescription = theApp.GetMessageString(IDS_PDF_TYPE_1);
						}
					}
					else
					{
						if (!sNomeReferto.IsEmpty())
							strDescription = sNomeReferto;
						else
							strDescription = theApp.GetMessageString(IDS_PDF_TYPE_3);
					}
				}
				/* else // Sandro 12/03/2015 //
				{
					if (pdf.bAnnullato)
					{
						strDescription = theApp.GetMessageString(IDS_PDF_TYPE_2);
					}
					else if (pdf.bSospeso)
					{
						strDescription = theApp.GetMessageString(IDS_PDF_TYPE_7);
					}
					else if (pdf.bFirmato)
					{
						if (pdf.lIDPdfCheSostituisc > 0)
							strDescription = theApp.GetMessageString(IDS_PDF_TYPE_5);
						else
							strDescription = theApp.GetMessageString(IDS_PDF_TYPE_1);
					}
					else
					{
						strDescription = theApp.GetMessageString(IDS_PDF_TYPE_3);
					}
				} */
				break;
			}
			case pdftype_images:
			{
				strDescription = theApp.GetMessageString(IDS_PDF_TYPE_4);

				if (pdf.lInviareACarestream > 0)
					strDescription += " (CARESTREAM)";

#ifdef _DEBUG
				CString sNoteee = CString(pdf.szNote);
				sNoteee.Trim();
				if (!sNoteee.IsEmpty())
					strDescription += " (" + sNoteee + ")";
#endif
				break;
			}
			case pdftype_report_annullativo:
			{
				// if (theApp.m_bPDFVisualizzaNomeReport) // Sandro 12/03/2015 //
				{
					CString sNomeReferto = CString(pdf.szNote);

					// elimino l'estensione //
					int nPos = sNomeReferto.ReverseFind('.');
					if (nPos > 0)
						sNomeReferto = sNomeReferto.Left(nPos);

					// cerco la barra "/" //
					nPos = sNomeReferto.ReverseFind('/');

					// se non trovo la barra "/" allora cerco la barra "\" //
					if (nPos < 0)
						nPos = sNomeReferto.ReverseFind('\\');

					// tolgo tutta la parte iniziale del percorso //
					if (nPos >= 0)
						sNomeReferto = sNomeReferto.Mid(nPos + 1, sNomeReferto.GetLength() - nPos);

					//
					sNomeReferto.MakeUpper();
					sNomeReferto.Trim();
			
					//
					if (!sNomeReferto.IsEmpty())
						strDescription.Format("%s - %s", theApp.GetMessageString(IDS_PDF_TYPE_6), sNomeReferto);
					else
						strDescription = theApp.GetMessageString(IDS_PDF_TYPE_6);
				}
				/* else // Sandro 12/03/2015 //
				{
					strDescription = theApp.GetMessageString(IDS_PDF_TYPE_6);
				} */
				break;
			}
			case pdftype_report_allegato:
			{
				CString sNomeReferto = CString(pdf.szNote);

				// elimino l'estensione //
				int nPos = sNomeReferto.ReverseFind('.');
				if (nPos > 0)
					sNomeReferto = sNomeReferto.Left(nPos);

				// cerco la barra "/" //
				nPos = sNomeReferto.ReverseFind('/');

				// se non trovo la barra "/" allora cerco la barra "\" //
				if (nPos < 0)
					nPos = sNomeReferto.ReverseFind('\\');

				// tolgo tutta la parte iniziale del percorso //
				if (nPos >= 0)
					sNomeReferto = sNomeReferto.Mid(nPos + 1, sNomeReferto.GetLength() - nPos);

				//
				sNomeReferto.MakeUpper();
				sNomeReferto.Trim();

				//
				if (pdf.bAnnullato)
				{
					if (!sNomeReferto.IsEmpty())
						strDescription.Format("%s - %s", theApp.GetMessageString(IDS_PDF_TYPE_2), sNomeReferto);
					else
						strDescription = theApp.GetMessageString(IDS_PDF_TYPE_2);
				}
				else if (pdf.bSospeso)
				{
					if (!sNomeReferto.IsEmpty())
						strDescription.Format("%s - %s", theApp.GetMessageString(IDS_PDF_TYPE_7), sNomeReferto);
					else
						strDescription = theApp.GetMessageString(IDS_PDF_TYPE_7);
				}
				else if (pdf.bFirmato)
				{
					/*
					if (pdf.lIDPdfCheSostituisc > 0)
					{
						if (!sNomeReferto.IsEmpty())
							strDescription.Format("%s - %s", theApp.GetMessageString(IDS_PDF_TYPE_5), sNomeReferto);
						else
							strDescription = theApp.GetMessageString(IDS_PDF_TYPE_5);
					}
					else
					{
					*/
						if (!sNomeReferto.IsEmpty())
							strDescription.Format("%s - %s", theApp.GetMessageString(IDS_PDF_TYPE_8), sNomeReferto);
						else
							strDescription = theApp.GetMessageString(IDS_PDF_TYPE_8);
					// }
				}
				else
				{
					if (!sNomeReferto.IsEmpty())
						strDescription = sNomeReferto;
					else
						strDescription = theApp.GetMessageString(IDS_PDF_TYPE_3);
				}
				break;
			}
			default:
			{
				ASSERT(FALSE);
				break;
			}
		}

		CArchivioStampeDlg::tagPDFVIEW pdfView;
		pdfView.lID = pdf.lID;
		CString strDate(pdf.szData);
		sprintf_s(pdfView.szData, 
			    "%s/%s/%s %s:%s:%s",
				strDate.Mid( 6, 2), 
				strDate.Mid( 4, 2), 
				strDate.Mid( 0, 4), 
				strDate.Mid( 8, 2), 
				strDate.Mid(10, 2), 
				strDate.Mid(12, 2));
		pdfView.ptTipo = pdf.ptTipo;
		strcpy_s(pdfView.szNote, strDescription);
		strcpy_s(pdfView.szFile, pdf.szFile);
		pdfView.bFitToPage = pdf.bFitToPage;
		pdfView.bFirmato = pdf.bFirmato;
		pdfView.bSospeso = pdf.bSospeso;
		pdfView.bAnnullato = pdf.bAnnullato;
		pdfView.bCriptato = pdf.bCriptato;
		strcpy_s(pdfView.szDisco, pdf.szDisco);
		strcpy_s(pdfView.szPercorsoFileRemoto, pdf.szPercorsoFileRemoto);
		listViewPdf.AddTail(pdfView);
	}

	if (listViewPdf.GetCount() == 0)
	{
		if (bShowErrors)
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAMIVIEW_PRINT_NOT_FOUND));
		return FALSE;
	}

	CString strTitle;
	strTitle.Format("%s %s (%s) - %s %s %s", 
		            m_pPazientiSet->m_sCognome, 
					m_pPazientiSet->m_sNome, 
					CCustomDate(m_pPazientiSet->m_lNatoIlCustom).GetDate("%d/%m/%Y"), 
					CTipoEsameSet().GetDescrizione(m_pEsamiSet->m_lIDEsame), 
					theApp.GetMessageString(IDS_DEL),
					CCustomDate(m_pEsamiSet->m_lData).GetDate("%d/%m/%Y"));

	CArchivioStampeDlg dlg(this, this, &listViewPdf, strTitle, TRUE);
	if (dlg.DoModal() == 0x333)
	{
		// firmo il documento per l'annullamento //

		switch(theApp.m_enumFirmaDigitale)
		{
			case CEndoxApp::sign_comped:
			{
				AnnullaDocumentiFirmati(m_pEsamiSet->m_lContatore);
				break;
			}
			default:
			{
				theApp.AfxMessageBoxEndo("Operazione non supportata nella modalità attiva");
				break;
			}
		}

		// riapro il dialog con l'archivio dei referti //

		OnCommandMenuGestioneVisualizzaStampe(bShowErrors);
	}

	return TRUE;
}

void CEsamiView::OnCommandMenuGestioneSospesiIstologici()
{
	if (theApp.m_nProgramMode != NOTHING_MODE)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_SAVE_BEFORE_VIEW));
		return;
	}

	if (m_pSospesiIstologiciDlg)
	{
		m_pSospesiIstologiciDlg->SendMessage(EM_SHOW_SOSPESIISTOLOGICI_WND);
	}
	else
	{
		m_pSospesiIstologiciDlg = new CRichiesteAnatomiaPatologicaDlg(this, this);

		CRichiesteAnatomiaPatologicaDlg *pDlg = (CRichiesteAnatomiaPatologicaDlg*)m_pSospesiIstologiciDlg;
		pDlg->CreateModelessDialog(this);
		pDlg->SendMessage(EM_SHOW_SOSPESIISTOLOGICI_WND);
	}
}

void CEsamiView::OnCommandMenuGestioneVisualizzatoreLog()
{
	CVisualizzatoreLogDlg dlg(this, this, FALSE);
	dlg.DoModal();
}

void CEsamiView::OnCommandMenuGestioneLogSintetico()
{
	char szProcess[4096];
	sprintf_s(szProcess, "%s\\LogSintetico.exe \"%s\" \"%s\"", theApp.m_sDirProg, theApp.m_dbEndox.GetDecryptedConnectionString(), m_pEsamiSet->m_sCodEsame);

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(NULL, szProcess, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		LPVOID lpMsgBuf;
		if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL))
			theApp.AfxMessageBoxEndo(CString((LPCTSTR)lpMsgBuf) + "\n" + theApp.m_sDirProg + "\\LogSintetico.exe");
		else
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_NOT_DEFINED) + "\n" + theApp.m_sDirProg + "\\LogSintetico.exe");
		LocalFree(lpMsgBuf);
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

void CEsamiView::OnCommandMenuGestioneVisualizzatoreLogImportazioneCasi()
{
	CVisualizzatoreLogDlg dlg(this, this, TRUE);
	dlg.DoModal();
}

void CEsamiView::OnCommandMenuGestioneStatistiche()
{
	CString sIndirizzo = theApp.m_sQueryMan + "Interrogazioni.aspx";

	/* Sandro 27/06/2012
	CBrowserDlg dlg(indirizzo, this);
	dlg.DoModal();
	*/

	ShellExecute(NULL, "open", sIndirizzo, NULL, NULL, SW_SHOWMAXIMIZED);
}

void CEsamiView::OnCommandMenuGestioneConfigStatistiche()
{
	if (CPasswordDlg(NULL, theApp.GetMessageString(IDS_PASSWORD_STATISTICHE), "nautilus").DoModal() == IDOK)
	{
		CString sIndirizzo = theApp.m_sQueryMan + "TipiInterrogazioni.aspx";

		/* Sandro 27/06/2012
		CBrowserDlg dlg(indirizzo, this);
		dlg.DoModal();
		*/

		ShellExecute(NULL, "open", sIndirizzo, NULL, NULL, SW_SHOWMAXIMIZED);
	}
}

void CEsamiView::OnCommandMenuGestioneEsamiPendenti()
{
	CGestioneEsamiPendentiDlg(this, this).DoModal();
}

void CEsamiView::OnCommandMenuGestioneLogIntegrazioni()
{
	CVisualizzatoreLogIntegrazioniDlg(this, this).DoModal();
}

void CEsamiView::OnCommandMenuGestioneInviaVideo()
{
	CImgList listImg;
	int nImages = m_pImgManager->GetImgList(&listImg);
	/*if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
		CLogFileWriter::Get()->WriteLogLine0_ImmRetrieve(timeGetTime() - timeForLog, m_lPaziente, m_lEsame, nImages, "CImageDlg::OnInitDialog");*/

	int videoCounter = 0;
	POSITION pos = listImg.GetHeadPosition();
	while (pos != NULL)
	{
		IMG imgTemp = listImg.GetNext(pos);
		if ((imgTemp.type == _movie_))
		{			
			videoCounter++;
		}
	}

	if (videoCounter > 0)
	{
		if (!CExtEsamiMediaDaInviareSet().InsertExam(m_pEsamiSet->m_lContatore, _movie_))		
			theApp.AfxMessageBoxEndo(IDS_VIDEOINVIATOERROR);		
		else
			theApp.AfxMessageBoxEndo(IDS_VIDEOINVIATO);
	}
	else
		theApp.AfxMessageBoxEndo(IDS_NOVIDEO);
}

void CEsamiView::OnCommandMenuGestioneAccessoSediEsterne()
{
	CAccessoSediEsterneDlg(this).DoModal();
}

//Julio 09/02/2018
void CEsamiView::OnCommandMenuGestioneItensFicha()
{
	if (theApp.m_lRicercaCodiceEsame == 4)
	{
		CString sErrore;
		CString sServer;
		CString sUO;
		CString sEndpointRemoteCommunication;
		long lArrayCount;

		CString sFicha = m_pEsamiSet->m_sRicovero;

		if (FleuryCercaItensDaFicha(sFicha, sErrore, sServer, sUO, sEndpointRemoteCommunication, lArrayCount))
		{
			if (lArrayCount > 0)
			{
				long lArrayPos = 0;
				CString *sArray = new CString[lArrayCount];

				int pos = 0;
				CString resToken;

				resToken = sEndpointRemoteCommunication.Tokenize(";", pos);
				sArray[lArrayPos] = resToken;
				lArrayPos++;

				while (resToken != _T(""))
				{
					resToken = sEndpointRemoteCommunication.Tokenize(";", pos);
					if (resToken != _T(""))
					{
						sArray[lArrayPos] = resToken;
						lArrayPos++;
					}
				}

				CSelectNumeroFichaDlg selectDlg(this, sArray, lArrayCount);
				if (selectDlg.DoModal() == IDOK)
				{
					int iSpacePos = selectDlg.m_sSelectedFicha.Find(" ");
					sFicha = selectDlg.m_sSelectedFicha.Mid(0, iSpacePos).Trim();
				}
				else
				{
					sFicha = "";
				}

				sArray = NULL;
				delete(sArray);
			}
			else
			{
				sFicha = "";
			}
		}
		if (!sFicha.IsEmpty())
		{
			if (RicercaCodicePazienteCodEsameEx(sFicha) > 0)
			{			
				MovePazientiAndEsami(NULL, TRUE, TRUE);
			}
			else
			{
				OnFleuryCentralizacao(sFicha);
			}
		}
	}
}

//Julio 02/03/2018
void CEsamiView::OnCommandMenuGestioneDesconjugarItens()
{
	BOOL bDesconjugadoOK = FALSE;	// Marvel BUG 4090 - desconjugação de laudos (tela principal do Tesicapture) 

	// Luiz - 07/05/2019 - P3 - Desconjuga exames - ESAMIINTEGRATI

	if (theApp.m_bPossuiConjugados) //Se foi conjugado many-to-many
	{
		long lContatoreConjugacao = m_pEsamiSet->m_lContatore;
		CString sFilter;
		CEsamiIntegratiSet setEsamiIntegrati;

		sFilter.Format("IDESAMEPRINCIPALE = '%d' AND ELIMINATO = 0", lContatoreConjugacao); //procuro por exames em que o exame atual é o principal

		setEsamiIntegrati.SetOpenFilter(sFilter);
		if (setEsamiIntegrati.OpenRecordset("CEsamiView::DesconjugaIntegrati"))
		{
			if (setEsamiIntegrati.IsEOF()) //se o exame atual não é o principal de nada, aviso para o usuario selecionar o exame correto.
			{
				theApp.AfxMessageBoxEndo("A desconjugação deve ser realizada pelo exame principal.");
			}
			else
			{
				if (!m_pEsamiSet->m_bSuperLocked) //verifico se o exame principal já é desbloqueado
				{
					CString sMessage;
					sMessage.Format(theApp.GetMessageString(IDS_CONFIRMA_DESCONJUGA_INTEGRATI));

					if (theApp.AfxMessageBoxEndo(sMessage, MB_YESNO) == IDYES)
					{
						while (!setEsamiIntegrati.IsEOF()) //desconjugo todos os exames que tem ele como principal
						{
							setEsamiIntegrati.DeleteRecordset("CEsamiView::DesconjugaIntegrati");
							setEsamiIntegrati.MoveNext();
						}
						theApp.AfxMessageBoxEndo("Exames desconjugados com sucesso.");

						bDesconjugadoOK = TRUE; // Marvel BUG 4090 - desconjugação de laudos (tela principal do Tesicapture) 
					}
				}
				else //se o exame principal não é desbloqueado
				{
					theApp.AfxMessageBoxEndo("É necessário que o exame esteja desbloqueado antes que seja desconjugado.");
				}
			}

			setEsamiIntegrati.CloseRecordset("CEsamiView::DesconjugaIntegrati");
		}
	}

	//Se foi conjugado one-to-one
	if (m_pEsamiSet->m_sCodEsame == m_pEsamiSet->m_sRefertoConiugatoPrincipale) //verifico se o exame atual é o exame principal
	{
		if (!m_pEsamiSet->m_bSuperLocked)
		{
			CString sFicha1 = m_pEsamiSet->m_sRefertoConiugatoPrincipale;
			CString sFicha2 = m_pEsamiSet->m_sRefertoConiugatoSecondario;

			CString sSigla1;
			CString sSigla2;

			CString sFilter;
			CExtPrestazioniSet setPrest;

			sFilter.Format("IDPRESTAZIONE LIKE '%s'", sFicha1);
			setPrest.SetOpenFilter(sFilter);
			if (setPrest.OpenRecordset("CEsamiView::OnCommandMenuGestioneDesconjugarItens") && !setPrest.IsEOF())
			{
				sSigla1 = setPrest.m_sCodicePrestazione;
				setPrest.CloseRecordset("CEsamiView::OnCommandMenuGestioneDesconjugarItens");
			}

			sFilter.Format("IDPRESTAZIONE LIKE '%s'", sFicha2);
			setPrest.SetOpenFilter(sFilter);
			if (setPrest.OpenRecordset("CEsamiView::OnCommandMenuGestioneDesconjugarItens") && !setPrest.IsEOF())
			{
				sSigla2 = setPrest.m_sCodicePrestazione;
				setPrest.CloseRecordset("CEsamiView::OnCommandMenuGestioneDesconjugarItens");
			}

			CString sMessage;
			sMessage.Format(theApp.GetMessageString(IDS_CONFIRMA_DESCONJUGA), sFicha1, sSigla1, sFicha2, sSigla2);


			if (theApp.AfxMessageBoxEndo(sMessage, MB_YESNO) == IDYES)
			{
				m_pEsamiSet->Desconjugar(sFicha1, sFicha2);
				theApp.AfxMessageBoxEndo("Exames desconjugados com sucesso");

				bDesconjugadoOK = TRUE; // Marvel BUG 4090 - desconjugação de laudos (tela principal do Tesicapture) 
			}
		}
		else //se o exame atual nao está desbloqueado peço o desbloqueio primeiro
		{
			theApp.AfxMessageBoxEndo("É necessário que o exame esteja desbloqueado antes que seja desconjugado.");
		}
	}
	else //se o exame atual não é o exame principal
	{
		if (!theApp.m_bPossuiConjugados)
		{
			CString sMensagem;
			sMensagem.Format("A desconjugação deve ser realizada pelo exame principal (%s).", m_pEsamiSet->m_sRefertoConiugatoPrincipale);
			theApp.AfxMessageBoxEndo(sMensagem);
		}
	}

	// Marvel BUG 4090 - desconjugação de laudos (tela principal do Tesicapture) 
	if (bDesconjugadoOK) {
		theApp.m_bPossuiConjugados = FALSE; //removo a flag apos o desconjugamento
	}
}

// Julio 22/10/2018
void CEsamiView::OnCommandMenuGestionePersonificacao()
{
	if (theApp.m_bImpersonated)
	{
		ImpersonateStop(m_pEsamiSet->m_lContatore, m_pEsamiSet->m_lPaziente);
	}
	else
	{

		COperatoriDlg op = COperatoriDlg(this, FALSE);
		op.DoModal();

		long lIDUtente = op.GetIDUtenteEndoxFromMediciID(atol(op.m_strRicerca));
		ImpersonateStart(m_pEsamiSet->m_lContatore, m_pEsamiSet->m_lPaziente, lIDUtente);
	}
}

//Gabriel BUG 6225 - Lista DO
void CEsamiView::OnCommandMenuGestioneFlussoDiStato()
{
	CFlussoDiStatoDlg(this, this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviOrganiSedi()
{
	COrganiSediDlg(this, this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviCentriDiCosto()
{
	CCentriDiCostoDlg(this, this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviCodificaRegionale() 
{
	CCodificaRegionaleExDlg(this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviGruppiPrestazioni()
{
	CGruppiPrestazioniModDlg(this, this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviGruppiPrestazioniRicetta()
{
	CCodificaRegionaleGruppiDlg(this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviTipiPrelievi()
{
	CIstopatologiaTipiDlg(this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviProcedurePrelievi()
{
	CIstopatologiaProcedureDlg(this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviGruppiPrelievi()
{
	if (theApp.m_bInterfacciaMetafora)
	{
		CGruppiPrelieviModDlg(this).DoModal();
	}
	else
	{
		CGruppiPrelieviOldModDlg(this).DoModal();
	}
}

void CEsamiView::OnCommandMenuVariDiagnosiIstologica()
{
	CDiagnosiIstologicheDlg(this).DoModal();
}

void CEsamiView::OnCommandMenuVariBostonScore()
{
	CBostonScoreMessagesDlg(this).DoModal();
}

void CEsamiView::OnCommandMenuVariCodiciClassificazioneDiagnostica()
{
	CModCodiciClassifDiagDlg(this).DoModal();
}

void CEsamiView::OnCommandMenuVariProtocolli()
{
	CProtocolliModDlg(this).DoModal();
}

void CEsamiView::OnCommandMenuVariMedidasBiometricas()
{
	CMeasurementsMappingDlg(this).DoModal();
}

// Marvel Carvalho - BUG 4308 Esquemas Anatômicos Fleury
void CEsamiView::OnCommandMenuVariSchemiAnatomiciRecord()
{
	CSchemiAnatomiciRecordDlg(this, this).DoModal();
}

//Gabriel BUG 6225 - Lista DO
void CEsamiView::OnCommandMenuVariFoglioRiferimento()
{
	CFoglioRiferimentoDlg dlg(this);
	dlg.DoModal();
}

//Gabriel - BUG 5533 V2 - Cálculos medidas biométricas
void CEsamiView::OnCommandMenuVariCalcoloMedidasBiometricas()
{
	CMeasurementsCalculationDlg dlg(this);
	dlg.DoModal();
}

//Gabriel - BUG 5533 V2 - Regras medidas biométricas
void CEsamiView::OnCommandMenuVariRegoleMedidasBiometricas()
{
	CMeasurementsRulesDlg dlg(this);
	dlg.DoModal();
}

void CEsamiView::OnCommandMenuArchiviEsami() 
{
	CTipoEsameDlg(this).DoModal();
}

void CEsamiView::OnCommandMenuEsamiFasi()
{
	CFasiConfigDlg(this).DoModal();
	((CEsamiDoc*)m_pDocument)->LoadEnabledPhaseForUser();
	MovePazientiAndEsami(NULL, FALSE, TRUE);
}

void CEsamiView::OnCommandMenuArchiviFrasiRTF()
{
	CFrasiRtfDlg(this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviFrasiStandard() 
{
	CFrasiExDlg(this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviFrasiPostEsame()
{
	CFrasiPostEsameDlg(this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviMstIndicazioni()
{
	CMstIndicazioniModDlg(this, this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviMstOsservazioni()
{
	CMstOsservazioniModDlg(this, this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviMstProcDiagnostiche()
{
	CMstProcedureDiagnosticheModDlg(this, this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviMstProcTerapeutiche()
{
	CMstProcedureTerapeuticheModDlg(this, this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviMstDiagnosi()
{
	CMstDiagnosiModDlg(this, this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviMstCodificaDiagnosiEsame()
{
	CMstCodificaDiagnosiEsameModDlg(this, this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviMstComplicanze1()
{
	CMstComplicanze1ModDlg(this, this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviMstComplicanze2()
{
	CMstComplicanze2ModDlg(this, this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviMstComplicanze3()
{
	CMstComplicanze3ModDlg(this, this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviAltreTabelle() 
{
	CTabComboDlg(this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviStrumenti()
{
	CStrumentiDlg(this, this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviEtichetteAnamnesi() 
{
	if (CEtichetteAnamnesiDlg(this).DoModal() == IDOK)
	{
		BeginWaitCursor();
		ScriviEtichette();
		EndWaitCursor();
	}
}

void CEsamiView::OnCommandMenuArchiviEtichette() 
{
	if (CEtichetteNewDlg(this).DoModal() == IDOK)
	{
		BeginWaitCursor();
		ScriviEtichette();
		EndWaitCursor(); 
	}
}

void CEsamiView::OnCommandMenuArchiviProntuarioFarmaceutico()
{
	CProntFarmModDlg(this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviProntuarioFarmaceuticoRicetta()
{
	CFarmaciGruppiRicDlg(this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviRAO() 
{
	CRAODlg(this).DoModal();	
}

void CEsamiView::OnCommandMenuArchiviStudi()
{
	CStudiDlg(this).DoModal();	
}

void CEsamiView::OnCommandMenuArchiviReportsDefault()
{
	CReportsDefaultModDlg(this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviMacroDiStampa()
{
	CReportsMacroModDlg(this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviMalattieCroniche()
{
	CMalattieCronicheDlg(this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviMedici() 
{
	COperatoriDlg(this, BOOL_FROMMENU).DoModal();
}

void CEsamiView::OnCommandMenuArchiviMediciCuranti() 
{
	CMediciCurantiInviantiDlg(this, MEDICI_CURANTI, BOOL_FROMMENU).DoModal();	
}

void CEsamiView::OnCommandMenuArchiviMediciInvianti()
{
	CMediciCurantiInviantiDlg(this, MEDICI_INVIANTI, BOOL_FROMMENU).DoModal();	
}

void CEsamiView::OnCommandMenuArchiviImportaCaso()
{
	CImportaCasoDlg(this, this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviEsameIntegrato()
{
	//Julio BUG 6385
	if (!FleuryIsUserADoctor())
		return;

	CEsameIntegratoDlg(this, this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviParametriTabellaEcocardiografia()
{
	CParametriTabellaDlg(this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviCommentiImmagini()
{
	CCommentiImmaginiModDlg(this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviInfermieri() 
{
	if (theApp.m_lIDSedeEsameDefault <= 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_SEDEESAME_NONDEFINITA));
	}
	else
	{
		CInfermieriDlg dlg(this, BOOL_FROMMENU);
		dlg.DoModal();
	}
}

void CEsamiView::OnCommandMenuArchiviInviantiInt() 
{
	CInviantiDlg(this, BOOL_INTERNI, BOOL_FROMMENU).DoModal();
}

void CEsamiView::OnCommandMenuArchiviInviantiExt() 
{
	CInviantiDlg(this, BOOL_ESTERNI, BOOL_FROMMENU).DoModal();
}

void CEsamiView::OnCommandMenuArchiviTrasferimParziale() 
{
	if (!m_bPazientiBusy && !m_bEsamiBusy)
	{
		if (theApp.m_nProgramMode == NOTHING_MODE)
		{
			BOOL bContinue = FALSE;
			CString strErrorToShow = "";
			int nResult = ERROR_NOTHING;

			switch(nResult = TrasferimentoImmagini(TRUE))
			{
				case ERROR_CRASH_DISK: // Errore Disco
					strErrorToShow	= "Errore nel disco destinazione. Si desidera riprovare?";
					bContinue = TRUE;
					break;
				
				case ERROR_FULL_DISK: // Disco pieno
					strErrorToShow	= "Spazio nel disco esaurito. E' necessario sostituirlo. Si desidera proseguire?";
					bContinue = TRUE;
					break;
				
				case ERROR_CRASH_DB: // Errore Database
					strErrorToShow	= "Si è verificato un errore critico nel database. Non è possibile continuare...";
					bContinue = TRUE;
					break;
				
				case ERROR_CRASH_MEMORY:
					strErrorToShow	= "Memoria esaurita. Liberare memoria e continuare...";
					bContinue = TRUE;
					break;

				case ERROR_NOTHING:
					strErrorToShow = "";
					bContinue = FALSE;
					break;

				default:
					strErrorToShow = "Operazione conclusa...";
					bContinue = TRUE;
					break;
			}
			
			if (bContinue)
			{
				theApp.AfxMessageBoxEndo(strErrorToShow);
				OnEsamiMove(NULL);
			}
		}
	}
	else
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAMIVIEW_BUSY));
	}
}

void CEsamiView::OnCommandMenuArchiviTrasferimTotale() 
{
	if (!m_bPazientiBusy && !m_bEsamiBusy)
	{
		CString strBuffer;
		CString strOldSort = ""; 
		CString strOldFilter = ""; 
		MSG msg;
		int nResult;
		CString strErrorToShow;
		BOOL bAskToContinue;
		BOOL bEscape;
		int nTotImgCopied = 0;
		int nTotRecCopied = 0;
		CString strLastEsame	= ""; 
		CString strLastPaziente = ""; 
		CCustomDate EsDate;
		CString strFinalBuffer = "";

		CTrasferimentoDlg dlgAsk;
		if (dlgAsk.DoModal() == IDOK)
		{
			// creo la finestra di riepilogo //
			CModelessDlg dlg(this, IDS_MODELESS_TITLE_2);
			dlg.CreateModeless(this);

			// creo la condizione //
			CString strCond;
			if (dlgAsk.m_bTrasferimentoParziale && theApp.m_nFieldToFilterOnTransfer >= 0 && theApp.m_nFieldToFilterOnTransfer <= 5 && !theApp.m_sFilterOnTransfer.IsEmpty())
			{
				// "Testo%i IS NULL" serve per Oracle, ma funziona anche per gli altri RDBMS
				strCond.Format(" AND (Testo%i <> '%s' OR Testo%i IS NULL)", theApp.m_nFieldToFilterOnTransfer + 15, theApp.m_sFilterOnTransfer, theApp.m_nFieldToFilterOnTransfer + 15);
			}
			
			// costruisco il filtro //
			strBuffer.Format("(Data >= %li) AND (Data <= %li)", dlgAsk.m_DataDa, dlgAsk.m_DataA);

			// salvo le vecchie impostazioni //
			strOldSort	 = m_pEsamiSet->GetSortRecord();
			strOldFilter = m_pEsamiSet->GetOpenFilter();

			// imposto le nuove //
			m_pEsamiSet->SetSortRecord("Data");
			m_pEsamiSet->SetOpenFilter(strBuffer + strCond);

			// riapro recordset //
			if (m_pEsamiSet->OpenRecordset("CEsamiView::OnMenuArchiviTrasferimTotale"))
			{
				while(!m_pEsamiSet->IsEOF())
				{   
					CString strTempLabel;
					m_pImgManager->SetCurrentIDs(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);
					if (!m_pImgManager->IsExamConfirmed(strTempLabel))
					{
						CCustomDate Date(m_pEsamiSet->m_lData);

						CString strInfo;
						strInfo.Format("Esame %li del %s", m_pEsamiSet->m_lContatore, Date.GetDate("%d/%m/%Y"));
						dlg.SetInfo(strInfo);

						while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
						{
							TranslateMessage(&msg);
							DispatchMessage(&msg);
						}
			
						if (dlg.m_bStop)
							break;

						switch(nResult = TrasferimentoImmagini(FALSE))
						{
							case ERROR_CRASH_DISK: // Errore Disco
								strErrorToShow	= "Errore nel disco destinazione. Si desidera riprovare?";
								bAskToContinue	= TRUE;
								bEscape			= TRUE;
								break;
							
							case ERROR_FULL_DISK: // Disco pieno
								strErrorToShow	= "Spazio nel disco esaurito. E' necessario sostituirlo. Si desidera proseguire?";
								bAskToContinue	= TRUE;
								bEscape			= TRUE;
								break;
							
							case ERROR_CRASH_DB: // Errore Database
								strErrorToShow	= "Si è verificato un errore critico nel database. Non è possibile continuare...";
								bAskToContinue	= FALSE;
								bEscape			= TRUE;
								break;
							
							case ERROR_CRASH_MEMORY:
								strErrorToShow	= "Memoria esaurita. Liberare memoria e continuare...";
								bAskToContinue	= FALSE;
								bEscape			= TRUE;
								break;

							case ERROR_NOTHING:
								strErrorToShow	= "";
								bAskToContinue	= FALSE;
								bEscape			= FALSE;
								break;

							default:
								nTotRecCopied  += 1;
								nTotImgCopied  += nResult;
								
								strErrorToShow	= "";
								bAskToContinue	= FALSE;
								bEscape			= FALSE;
						}

						if (bEscape)
						{
							CString strDatiEsame =	"Ultima scheda: " + strLastEsame + "\ndel: " + EsDate.GetDate("%d/%m/%Y") + "\ndel paziente: " + strLastPaziente;

							if (bAskToContinue)
							{
								if (theApp.AfxMessageBoxEndo(strErrorToShow, MB_YESNO) == IDYES)
									continue;

								theApp.AfxMessageBoxEndo(strDatiEsame);
							}
							else
							{
								theApp.AfxMessageBoxEndo(strErrorToShow + "\n\n" + strDatiEsame);
							}
						
							break;
						}
					
						strLastEsame.Format("%li", m_pEsamiSet->m_lContatore);
						strLastPaziente.Format("%li", m_pEsamiSet->m_lPaziente);
						EsDate.SetDate(m_pEsamiSet->m_lData);
					}

					m_pEsamiSet->MoveNext();
				}
		
				m_pEsamiSet->CloseRecordset("CEsamiView::OnMenuArchiviTrasferimTotale");
			}

			strFinalBuffer.Format(theApp.GetMessageString(IDS_BASEFORM_FINAL_MSG), nTotRecCopied, nTotImgCopied);

	   		dlg.DestroyWindow();

			theApp.AfxMessageBoxEndo(strFinalBuffer);

			// ripristina la vecchia configurazione
			m_pEsamiSet->SetSortRecord(strOldSort);
			m_pEsamiSet->SetOpenFilter(strOldFilter);

			MoveRecord(NULL);
		}
	}
	else
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAMIVIEW_BUSY));
	}
}

void CEsamiView::OnCommandMenuArchiviEjectVolume() 
{
	CString strDisk;
	
	strDisk = theApp.m_sPathImageOD;

	if (strDisk.Find("\\\\") < 0)
		EjectThisDisk(strDisk);
}

void CEsamiView::OnCommandMenuArchiviOccupazioneGiornaliera()
{
	COccupazioneGiornalieraDlg dlg(this, this);
	dlg.DoModal();
}

void CEsamiView::OnCommandMenuArchiviBackupDati()
{
	CBackupDatiDlg dlg(this, this);
	dlg.DoModal();
}

void CEsamiView::OnCommandMenuArchiviBackupDatiDoppiaCopia()
{
	CBackupDatiDoppiaCopiaDlg dlg(this, this);
	dlg.DoModal();
}

void CEsamiView::OnCommandMenuArchiviBackup()
{
	if (CPasswordDlg(this, theApp.GetMessageString(IDS_PASSWORD_PERCORSI), "1qaz2wsx3edc").DoModal() == IDOK)
		CArchiviBackupDlg(this, GetDocument()).DoModal();
}

void CEsamiView::OnCommandMenuArchiviSalvaValoriDefault()
{
	m_bValoriDefault = TRUE;
	OnEsameNew();
}

void CEsamiView::OnCommandMenuArchiviStorePacsImage()
{
	StoreImmOnPacs();
}

void CEsamiView::OnCommandMenuArchiviComplicanzeImmediate()
{
	CComboComplicanzeSet set(FALSE);
	CComboTransConfigDlg dlg(this, this, &set, theApp.GetMessageString(IDS_COMPLICANZE_IMMEDIATE));
	dlg.DoModal();	
}

void CEsamiView::OnCommandMenuArchiviComplicanzeTardive()
{
	CComboComplicanzeSet set(TRUE);
	CComboTransConfigDlg dlg(this, this, &set, theApp.GetMessageString(IDS_COMPLICANZE_TARDIVE));
	dlg.DoModal();
}

void CEsamiView::OnCommandMenuArchiviPulizia() 
{
	CComboPuliziaSet set;
	CComboTransConfigDlg dlg(this, this, &set, theApp.GetMessageString(IDS_PULIZIA));
	dlg.DoModal();	
}

void CEsamiView::OnCommandMenuArchiviCauseNonCompletamento() 
{
	CComboCauseNonCompletamentoSet set;
	CComboTransConfigDlg dlg(this, this, &set, theApp.GetMessageString(IDS_CAUSENONCOMPLETAMENTO));
	dlg.DoModal();	
}

void CEsamiView::OnCommandMenuArchiviTolleranza() 
{
	CComboTolleranzaSet set;
	CComboTransConfigDlg dlg(this, this, &set, theApp.GetMessageString(IDS_TOLLERANZA));
	dlg.DoModal();	
}

void CEsamiView::OnCommandMenuArchiviConclusioniColon() 
{
	CComboConclusioniColonSet set;
	CComboTransConfigDlg dlg(this, this, &set, theApp.GetMessageString(IDS_CONCLUSIONICOLON));
	dlg.DoModal();	
}

void CEsamiView::OnCommandMenuArchiviConclusioniScreening() 
{
	CComboConclusioniScreeningSet set;
	CComboTransConfigDlg dlg(this, this, &set, theApp.GetMessageString(IDS_CONCLUSIONISCREENING));
	dlg.DoModal();	
}

void CEsamiView::OnCommandMenuArchiviDiagnosiFinale() 
{
	CComboDiagnosiFinaleSet set;
	CComboTransConfigDlg dlg(this, this, &set, theApp.GetMessageString(IDS_DIAGNOSIFINALE));
	dlg.DoModal();	
}

void CEsamiView::OnCommandMenuArchiviAltreAnomalie()
{
	CComboAltreAnomalieSet set;
	CComboTransConfigDlg(this, this, &set, theApp.GetMessageString(IDS_CMB_ALTREANOMALIE)).DoModal();
}

void CEsamiView::OnCommandMenuArchiviRepAspettoMacro() 
{
}

void CEsamiView::OnCommandMenuArchiviRepGradoDisplasia() 
{
}

void CEsamiView::OnCommandMenuArchiviRepIstologia() 
{
}

void CEsamiView::OnCommandMenuArchiviRepNotizieTerapia()
{
}

void CEsamiView::OnCommandMenuArchiviRepRegione() 
{
}

void CEsamiView::OnCommandMenuArchiviRepTecnica() 
{
}

void CEsamiView::OnCommandMenuArchiviRepTipoLesione() 
{
}

void CEsamiView::OnCommandMenuArchiviRepTrattamento() 
{
}

void CEsamiView::OnCommandMenuArchiviProcedureICD9() 
{
	CProcedureICD9Dlg dlg(this);
	dlg.DoModal();
}

void CEsamiView::OnCommandMenuArchiviGruppiProcedureICD9()
{
	CGruppiProcedureICD9ModDlg dlg(this, this);
	dlg.DoModal();
}

void CEsamiView::OnCommandMenuArchiviDiagnosiICD9()
{
	CDiagnosiICD9Dlg dlg(this);
	dlg.DoModal();
}

void CEsamiView::OnCommandMenuArchiviGruppiDiagnosiICD9()
{
	CGruppiDiagnosiICD9ModDlg dlg(this, this);
	dlg.DoModal();
}

void CEsamiView::OnCommandMenuArchiviAssociazioniICD9()
{
	CAssociazioniICD9Dlg dlg(this);
	dlg.DoModal();
}

// Julio BUG 3249
void CEsamiView::OnCommandMenuArchiviPatogenicita()
{
	CGenomicaPatogenicitaDlg dlg(this);
	dlg.DoModal();
}

// Julio BUG 3249
void CEsamiView::OnCommandMenuArchiviTipiVariantiGenetiche()
{
	CGenomicaTipiVariantiDlg dlg(this);
	dlg.DoModal();
}

// Julio BUG 3249
void CEsamiView::OnCommandMenuArchiviTipiAlterazioni()
{
	CGenomicaTipiAlterazioniDlg dlg(this);
	dlg.DoModal();
}

// Julio BUG 3249
void CEsamiView::OnCommandMenuArchiviVariantiGenetiche()
{
	CGenomicaVariantiGeneticheDlg dlg(this, this);
	dlg.DoModal();
}

// Julio BUG 3249
void CEsamiView::OnCommandMenuArchiviSezioniReferto()
{
	CGenomicaSezioniDlg dlg(this);
	dlg.DoModal();
}

// Julio BUG 3249
void CEsamiView::OnCommandMenuArchivTipiReferto()
{
	CGenomicaTipiRefertoDlg dlg(this);
	dlg.DoModal();
}

// Julio BUG 3249
void CEsamiView::OnCommandMenuArchiviCorpoReferto()
{
	CGenomicaCorpoDlg dlg(this, this);
	dlg.DoModal();
}

// Julio BUG 3249
void CEsamiView::OnCommandMenuArchiviTipiMateriali()
{
	CGenomicaTipiMaterialiDlg dlg(this);
	dlg.DoModal();
}

// Julio BUG 3249
void CEsamiView::OnCommandMenuArchiviFrasiRisultato()
{
	CGenomicaFrasiRisultatoDlg dlg(this);
	dlg.DoModal();
}

void CEsamiView::OnCommandMenuArchiviIntegrazioni()
{
	if (CPasswordDlg(this, theApp.GetMessageString(IDS_PASSWORD_INTEGRAZIONI), "nautilus").DoModal() == IDOK)
		CIntegrazioniConfigurazioneModDlg(this, this).DoModal();
}

void CEsamiView::OnCommandMenuConnessioneRemota()
{
	CStreamingListDlg dlg(this, this);
	dlg.DoModal();
}

void CEsamiView::OnCommandMenuOpzioniOrgani() 
{
	COrganShowDlg dlg(this, this);
	dlg.DoModal();
}

void CEsamiView::OnCommandMenuOpzioniCalib()
{
	CCalibDlg dlgCal(this, this, theApp.m_pListCalib);
	dlgCal.DoModal();
}

void CEsamiView::OnCommandMenuOpzioniSetup()
{
	if (CPasswordDlg(this, theApp.GetMessageString(IDS_PASSWORD_SETUP), "nautilus").DoModal() == IDOK)
		if (CSetupDlg(this).DoModal() == IDOK)
			theApp.SaveSetting();
}

void CEsamiView::OnCommandMenuOpzioniAcquisizione()
{
	// Sandro 27/11/2015 //
	CString sPWD = "1qaz2wsx3edc";

	//
	if (CPasswordDlg(this, theApp.GetMessageString(IDS_PASSWORD_ACQUISIZIONE), sPWD).DoModal() == IDOK)
	{
		if (theApp.m_nApplication == PRG_DERMOX)
		{
			CDermoxAcqSetupDlg(this).DoModal();
		}
		else
		{
			WritePrivateProfileInt("xcap", "Language", theApp.m_nLanguage, theApp.m_sFileConfig);
			WritePrivateProfileString("xcap", "usemovie", "1", theApp.m_sFileConfig);

			WritePrivateProfileInt("xcap", "top", theApp.m_rectDesk.top, theApp.m_sFileConfig);
			WritePrivateProfileInt("xcap", "left", theApp.m_rectDesk.left, theApp.m_sFileConfig);
			WritePrivateProfileInt("xcap", "bottom", theApp.m_rectDesk.bottom, theApp.m_sFileConfig);
			WritePrivateProfileInt("xcap", "right", theApp.m_rectDesk.right, theApp.m_sFileConfig);

			TCHAR szProcess[1024];
			sprintf_s(szProcess, "%s\\xCap\\xCap.exe -s %s", theApp.m_sDirProg, theApp.m_sFileConfig);

			STARTUPINFO si;
			PROCESS_INFORMATION pi;

			ZeroMemory(&si, sizeof(si));
			si.cb = sizeof(si);
			ZeroMemory(&pi, sizeof(pi));

			if (!CreateProcess(NULL, szProcess, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
			{
				LPVOID lpMsgBuf;
				if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL))
					theApp.AfxMessageBoxEndo((LPCTSTR)lpMsgBuf);
				else
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_NOT_DEFINED));
				LocalFree( lpMsgBuf );
			}
			WaitForSingleObject(pi.hProcess, INFINITE);
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
		}
	}
}

void CEsamiView::OnCommandMenuOpzioniInterfacciaWEB()
{
	if (CPasswordDlg(this, theApp.GetMessageString(IDS_PASSWORD_INTERFACCIAWEB), "nautilus").DoModal() == IDOK)
	{
		CSetupInterfacciaWEB dlg(this, this);
		dlg.DoModal();
	}
}

void CEsamiView::OnCommandSetupDbase()
{
	if (CPasswordDlg(this, theApp.GetMessageString(IDS_PASSWORD_DATABASE), "1qaz2wsx3edc").DoModal() == IDOK)
		Amdbx_ConfigDatabase(theApp.m_sFileConfig);
}

void CEsamiView::OnCommandMenuOpzioniDisegnaOperator()
{
    CDisegnaOperatorDlg(this, this).DoModal();
}

void CEsamiView::OnCommandMenuOpzioniDisegnaReport() 
{
    CReportDlg(this, this).DoModal();
}

void CEsamiView::OnCommandMenuOpzioniCampiObbligatori()
{
	CCampiObbligatoriDlg(this, this).DoModal();
}

void CEsamiView::OnCommandMenuOpzioniDisattivaFirmaPerQuestoEsame()
{
	CString sMessage;
	sMessage.Format(theApp.GetMessageString(IDS_CONFERMA_DISATTIVAFIRMA), theApp.m_sUtenteLoggato);

	if (theApp.AfxMessageBoxEndo(sMessage, MB_YESNO | MB_ICONSTOP) == IDYES)
		theApp.m_lIDEsameFirmaDisattivata = m_pEsamiSet->m_lContatore;
}

void CEsamiView::OnCommandMenuOpzioniSetupDatabasesRemoti()
{
#ifndef _DEBUG
	if (CPasswordDlg(this, theApp.GetMessageString(IDS_PASSWORD_SETUPDATABASESREMOTI), "nautilus").DoModal() == IDOK)
#endif
		CSetupDatabasesRemotiDlg(this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviAccessori()
{
	CAccessoriDlg(this, TRUE).DoModal();
}

void CEsamiView::OnCommandMenuArchiviFarmaciMonitoraggio()
{
	CFarmaciMonitoraggioDlg(this, TRUE).DoModal();
}

void CEsamiView::OnCommandMenuArchiviFarmaciPazientiCronici()
{
	CFarmaciPazientiCroniciDlg(this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviCheckList()
{
	CCheckListModDlg(this, this).DoModal();
}

void CEsamiView::OnCommandMenuArchiviEsenzioneRicetta()
{
}

void CEsamiView::OnCommandMenuArchiviDosiMonitoraggio()
{
	CDosiMonitoraggioDlg(this, TRUE).DoModal();
}

void CEsamiView::OnCommandSetupColori()
{
	CModStatoColoreDlg(this).DoModal();

	GetDocument()->SetLongValue("Colore - visualizzazione aperto", (long&)theApp.m_colorVisualizzazioneAperto);
	GetDocument()->SetLongValue("Colore - visualizzazione aperto sfondo", (long&)theApp.m_colorVisualizzazioneApertoSfondo);
	GetDocument()->SetLongValue("Colore - visualizzazione chiuso", (long&)theApp.m_colorVisualizzazioneChiuso);
	GetDocument()->SetLongValue("Colore - visualizzazione chiuso sfondo", (long&)theApp.m_colorVisualizzazioneChiusoSfondo);
	GetDocument()->SetLongValue("Colore - visualizzazione firmato", (long&)theApp.m_colorVisualizzazioneFirmato);
	GetDocument()->SetLongValue("Colore - visualizzazione firmato sfondo", (long&)theApp.m_colorVisualizzazioneFirmatoSfondo);
	GetDocument()->SetLongValue("Colore - aggiunta paziente", (long&)theApp.m_colorAggiuntaPaziente);
	GetDocument()->SetLongValue("Colore - aggiunta paziente sfondo", (long&)theApp.m_colorAggiuntaPazienteSfondo);
	GetDocument()->SetLongValue("Colore - modifica paziente", (long&)theApp.m_colorModificaPaziente);
	GetDocument()->SetLongValue("Colore - modifica paziente sfondo", (long&)theApp.m_colorModificaPazienteSfondo);
	GetDocument()->SetLongValue("Colore - aggiunta esame", (long&)theApp.m_colorAggiuntaEsame);
	GetDocument()->SetLongValue("Colore - aggiunta esame sfondo", (long&)theApp.m_colorAggiuntaEsameSfondo);
	GetDocument()->SetLongValue("Colore - modifica esame", (long&)theApp.m_colorModificaEsame);
	GetDocument()->SetLongValue("Colore - modifica esame sfondo", (long&)theApp.m_colorModificaEsameSfondo);
	GetDocument()->SetLongValue("Colore - ricerca paziente", (long&)theApp.m_colorRicercaPaziente);
	GetDocument()->SetLongValue("Colore - ricerca paziente sfondo", (long&)theApp.m_colorRicercaPazienteSfondo);
	GetDocument()->SetLongValue("Colore - ricerca esame", (long&)theApp.m_colorRicercaEsame);
	GetDocument()->SetLongValue("Colore - ricerca esame sfondo", (long&)theApp.m_colorRicercaEsameSfondo);
	GetDocument()->SetLongValue("Colore - non sbloccabile", (long&)theApp.m_colorVisualizzazioneArchiviato);
	GetDocument()->SetLongValue("Colore - non sbloccabile sfondo", (long&)theApp.m_colorVisualizzazioneArchiviatoSfondo);
	GetDocument()->SetLongValue("Colore - in archiviazione", (long&)theApp.m_colorVisualizzazioneInArchiviazione);
	GetDocument()->SetLongValue("Colore - in archiviazione sfondo", (long&)theApp.m_colorVisualizzazioneInArchiviazioneSfondo);
	GetDocument()->SetLongValue("Colore - streaming attivo", (long&)theApp.m_colorStreamingAttivo);
	GetDocument()->SetLongValue("Colore - streaming attivo sfondo", (long&)theApp.m_colorStreamingAttivoSfondo);
	GetDocument()->SetLongValue("Colore - streaming connesso", (long&)theApp.m_colorStreamingConnesso);
	GetDocument()->SetLongValue("Colore - streaming connesso sfondo", (long&)theApp.m_colorStreamingConnessoSfondo);

}

void CEsamiView::OnCommandMenuRoutingVideo()
{
	BeginWaitCursor();
	// StartProcess(theApp.m_sVideoRoutingCmd);
	EndWaitCursor();
}

void CEsamiView::OnCommandMenuRoutingAudio()
{
	BeginWaitCursor();
	// StartProcess(theApp.m_sAudioRoutingCmd);
	EndWaitCursor();
}

void CEsamiView::OnCommandMenuAttivazioneUtenti()
{
	BeginWaitCursor();
	// StartProcess(theApp.m_sAttivazioneUtentiStreamingCmd);
	EndWaitCursor();
}

void CEsamiView::OnCommandChiudiFase(long lIDFase)
{
	//CString message;
	//message.Format(theApp.GetMessageString(IDS_CHIUSURA_FASE_CONFERMA), CFasiEsameSet().GetDescrizione(lIDFase));
	//if (VerificaCampiObbligatoriFase(lIDFase) && theApp.AfxMessageBoxEndo(message, MB_YESNO) == IDYES)
	//{	
	
		//Julio - BUG 3735 - Alteração do botão SALVAR LAUDO  
		if ((lIDFase == CO_FASE_CHIUSURA_STAMPA)
			&& (theApp.m_bConfermareGliEsamiSenzaAttaccamentoOImmagini && theApp.m_bPersonalizzazioniBrasileFleury))
		{		
			// não verificar pasta amarela - documentos não serão exportados
			// int iTotalAnexos = m_pDocManager->GetAttachedDocNumberExam(m_pEsamiSet->m_lContatore, DOCUMENTS_NOT_EXPORT); 
			int iTotalAnexos = m_pDocManager->GetAttachedDocNumberExam(m_pEsamiSet->m_lContatore, DOCUMENTS_ONLY_EXPORT);

			CImgList listImg;
			if (m_pImgManager->GetImgList(&listImg) == 0 && iTotalAnexos == 0)
			{
				if (theApp.MessageBoxEndo(theApp.GetMessageString(IDS_FLEURY_CONFERMA_ESAMI_SENZA_ATTACCA_IMMAGI), theApp.GetMessageString(IDS_ACHTUNG), MB_YESNO | MB_ICONEXCLAMATION) != IDYES)
					return;
			}
		}

		if (lIDFase == CO_FASE_CONVALIDA)
		{
			//Gabriel BUG 6225 - Lista DO
			if (theApp.m_bAtivaListaDO)
			{
				if (BloccaEsameRiconvocazione())
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_RICONVOCAZIONE_ESAMEBLOCCATO));
					return;
				}
			}
			
			ConvalidaEsame();
		}
		else if (lIDFase == CO_FASE_CHIUSURA_STAMPA)
		{			
			//Gabriel BUG 6225 - Lista DO
			if (theApp.m_bAtivaListaDO)
			{
				if (BloccaEsameRiconvocazione())
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_RICONVOCAZIONE_ESAMEBLOCCATO));
					return;
				}
			}

			if (theApp.m_bPersonalizzazioniBrasileFleury && !m_pEsamiSet->m_bLocked) //Julio 03/02/2018
				ConvalidaEsame();

			ChiudiEsame();
		}
		// Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
		else if (lIDFase == CO_FASE_LIBERA_LAUDO)
		{
			if (theApp.m_bAtivaP3)
			{
				if (theApp.m_bPersonalizzazioniBrasileFleury && (theApp.m_bFaseExtraAmarradoAoSuperlock && m_pEsamiSet->m_bLocked && m_pEsamiSet->m_bSuperLocked) || !theApp.m_bFaseExtraAmarradoAoSuperlock)
				{
					CString sFilter;
					CEsamiIntegratiSet setEsamiIntegrati;
					CEsamiSet setEsami;

					//Produzione e archiviazione pdf
					//long lIDPdf = GeneraPdfFase(lIDFase);
					//LiberaLaudo();
					BeginWaitCursor();

					if (CEsamiSet().IsConiugatoSecondario(m_pEsamiSet->m_lContatore) || ExameSecundario(m_pEsamiSet->m_lContatore))
						theApp.AfxMessageBoxEndo("A liberação de laudo deve ser realizada pelo exame principal.");

					if (theApp.m_bAtivaP3)
						FechaProtocoloXXI(m_pEsamiSet->m_sRicovero, m_pEsamiSet->m_sCodEsame); //Gabriel - P3

					/* Faz o protocolo XXI das fichas conjugadas
					theApp.m_bPossuiConjugados = RefertoPrincipale(m_pEsamiSet->m_lContatore);

					if (theApp.m_bPossuiConjugados)
					{
					if (m_pEsamiSet->m_bSuperLocked)
					{
					sFilter.Format("IDESAMEPRINCIPALE = '%d' AND ELIMINATO = 0", m_pEsamiSet->m_lContatore);
					setEsamiIntegrati.SetOpenFilter(sFilter);
					if (setEsamiIntegrati.OpenRecordset("CEsamiView::FechaFaseEsamiIntegrati"))
					{
					if (setEsamiIntegrati.IsEOF())
					{
					theApp.AfxMessageBoxEndo("A liberação de laudo deve ser realizada pelo exame principal.");
					}
					else
					{
					while (!setEsamiIntegrati.IsEOF())
					{
					CString sFilter;
					CEsamiSet setEsameSecundario;
					sFilter.Format("CONTATORE = %li AND ELIMINATO = 0", setEsamiIntegrati.m_lIDEsameSecondario);
					setEsameSecundario.SetOpenFilter(sFilter);
					if (setEsameSecundario.OpenRecordset("CEsamiView::FechaProtocoloXXIEsamiIntegrati"))
					{
					if (!setEsameSecundario.IsEOF())
					FechaProtocoloXXI(setEsameSecundario.m_sRicovero,setEsameSecundario.m_sCodEsame);

					setEsameSecundario.CloseRecordset("CEsamiView::FechaProtocoloXXIEsamiIntegrati");
					}

					setEsamiIntegrati.MoveNext();
					}
					}
					setEsamiIntegrati.CloseRecordset("CEsamiView::FechaFaseEsamiIntegrati");
					}
					}
					else
					{
					theApp.AfxMessageBoxEndo("É necessário que o exame esteja desbloqueado antes da liberação de fase.");
					}
					}

					if (m_pEsamiSet->m_sCodEsame == m_pEsamiSet->m_sRefertoConiugatoPrincipale)
					{
					if (m_pEsamiSet->m_bSuperLocked)
					{
					sFilter.Format("CODESAME <> '%s' AND REFERTOCONIUGATOPRINCIPALE = '%s' AND ELIMINATO = 0", m_pEsamiSet->m_sCodEsame, m_pEsamiSet->m_sCodEsame);
					setEsami.SetOpenFilter(sFilter);
					if (setEsami.OpenRecordset("CEsamiView::FechaFaseEsami"))
					{
					if (setEsami.IsEOF())
					{
					theApp.AfxMessageBoxEndo("A liberação de laudo deve ser realizada pelo exame principal.");
					}
					else
					{
					while (!setEsami.IsEOF())
					{
					FechaProtocoloXXI(setEsami.m_sRicovero,setEsami.m_sCodEsame);
					setEsami.MoveNext();
					}
					}
					setEsami.CloseRecordset("CEsamiView::FechaFaseEsami");
					}
					}
					else
					{
					theApp.AfxMessageBoxEndo("É necessário que o exame esteja desbloqueado antes que a fase seja finalizada.");
					}
					}

					if ((theApp.m_bPossuiConjugados) || (m_pEsamiSet->m_sCodEsame == m_pEsamiSet->m_sRefertoConiugatoPrincipale))
					{
					theApp.AfxMessageBoxEndo("Fases de exames finalizadas com sucesso.");
					}
					else
					{
					theApp.AfxMessageBoxEndo("Fase de exames finalizada com sucesso.");
					}
					*/
					RicaricaDatiAssociatiAllEsame();
					MovePazientiAndEsami(NULL, FALSE, TRUE);
					EndWaitCursor();
				}
				else
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_FASE_DEPENDENTE));
				}
			}
			else
			{
				//Produzione e archiviazione pdf
				long lIDPdf = GeneraPdfFase(lIDFase);

				BeginWaitCursor();

				//Aggiunta alla tabella fasichiuse
				long idFaseChiusa = CEsamiFasiChiuseSet().Insert(m_pEsamiSet->m_lContatore, lIDFase, lIDPdf);

				//Aggiunta alla tabella ext
				if (idFaseChiusa > 0)
					CExtEsamiFasiChiuseSet().Insert(m_pEsamiSet->m_lContatore, idFaseChiusa);

				//Ricarico le fasi chiuse
				RicaricaDatiAssociatiAllEsame();
				MovePazientiAndEsami(NULL, FALSE, TRUE);

				EndWaitCursor();
			}
		}
	//}
}

//Gabriel - P3
BOOL CEsamiView::FechaProtocoloXXI(CString sRicovero, CString sCodEsame)
{
	//Gabriel - P3
	BOOL bRetorno = FALSE;
	if (!sRicovero.IsEmpty() && !sCodEsame.IsEmpty())
	{
		int n1 = sCodEsame.Find("_");
		if (n1 > 0)
		{
			int n2 = sCodEsame.Find("_", n1 + 1);
			if (n2 > 0)
			{
				CString sItem = sCodEsame.Mid(n1 + 1);
				sItem.Replace("_", "0");
				
				CString sSiglaUtente = "";

				long lUserID;
				AMLogin_GetUserID(&lUserID);
				if (CMediciSet().GetContatoreFromUserID(lUserID) > 0)
				{
					sSiglaUtente = CMediciSet().GetCodiceFromUserID(lUserID);
				}
				else
				{
					// se non sono un medico uso il 3L3N della Tesi //
					sSiglaUtente = CString("EQT496").Left(3);
				}

				if (sSiglaUtente.GetLength() > 0)
				{
					//Chamo a API do protocolo XXI
					chiusuraFaseEndoxRequest request;
					sprintf_s(request.szSiglaUsuarioSistema, sSiglaUtente);
					sprintf_s(request.szIdFase, "3");
					sprintf_s(request.szFicha, sRicovero);
					sprintf_s(request.szItem, sItem);
					
					CChiusuraFaseEndoxService chiusuraFaseEndoxService(theApp.m_sHttpServerProtocoloXXI);
					chiusuraFaseEndoxResponse response = chiusuraFaseEndoxService.chiusuraFaseEndox(request);

					if (strcmp(response.szMessage, "") != 0) //Verifico se a chamada não retornou erros
					{
						CString message;
						message.Format("%s", response.szMessage);
						theApp.AfxMessageBoxEndo(message);
						AMLogin_Logout();
						theApp.m_lUO = 0;
						bRetorno = FALSE;
					}

					CTime now = CTime::GetCurrentTime();
					m_pEsamiSet->ProtocoloXXI(now.Format("%Y%m%d%H%M%S"));
					bRetorno = TRUE;
				}
			}
		}
	}

	return bRetorno;
}

BOOL CEsamiView::ExameSecundario(long lExam)
{
	CString sFilter;
	CEsamiIntegratiSet setEsamiIntegrati;
	BOOL bRetorno = FALSE;

	sFilter.Format("IDESAMESECONDARIO = '%d' AND ELIMINATO = 0", lExam);
	setEsamiIntegrati.SetOpenFilter(sFilter);
	if (setEsamiIntegrati.OpenRecordset("CEsamiView::ExameSecundario"))
		if (!setEsamiIntegrati.IsEOF())
			bRetorno = TRUE;

	setEsamiIntegrati.CloseRecordset("CEsamiView::ExameSecundario");
	return bRetorno;
}

void CEsamiView::OnCommandAnnullaChiudiFase(long lIDFase)
{	
	CString message;
	message.Format(theApp.GetMessageString(IDS_RIAPERTURA_FASE_CONFERMA), CFasiEsameSet().GetDescrizione(lIDFase));
	if (theApp.AfxMessageBoxEndo(message, MB_YESNO) == IDYES)
	{
		//Julio 11/08/2018
		if (theApp.m_bPersonalizzazioniBrasileFleury)
		{
			CString sMessaggio = "";
			BOOL bModifica = FleuryPossoModificare(sMessaggio, m_pEsamiSet->m_sRicovero, m_pEsamiSet->m_sCodEsame);
			if (!bModifica)
			{
				theApp.AfxMessageBoxEndo(sMessaggio);
				return;
			}
		}
		//
		if (lIDFase == CO_FASE_CONVALIDA)
		{
			// Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
			if (CEsamiFasiChiuseSet().FaseAbertaExame(m_pEsamiSet->m_lContatore, CO_FASE_LIBERA_LAUDO))
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PENDENCIA_FECHAR_FASE));
				return;
			}

			//Julio - removendo este bloco pois no fleury sempre usaremos o metodo FleuryPossoModificare
			/*if (!CEsamiSet().EsameSbloccabile(m_pEsamiSet->m_lContatore))
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAMEBLOCCATO));
				MovePazientiAndEsami(NULL, FALSE, TRUE);
				return;
			}*/

			if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CONVALIDA_ANNULLA), MB_YESNO) == IDYES)
			{
				m_pEsamiSet->AnnullaConvalidaEsame();
				UpdateData(FALSE);
			}
		}
		else if (lIDFase == CO_FASE_CHIUSURA_STAMPA)
		{
			// Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
			if (CEsamiFasiChiuseSet().FaseAbertaExame(m_pEsamiSet->m_lContatore, CO_FASE_LIBERA_LAUDO))
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PENDENCIA_FECHAR_FASE));
				return;
			}

			//Julio - removendo este bloco pois no fleury sempre usaremos o metodo FleuryPossoModificare
			/*if (!CEsamiSet().EsameSbloccabile(m_pEsamiSet->m_lContatore))
			{
				theApp.AfxMessageBoxEndo(IDS_ESAMEBLOCCATO);
				MovePazientiAndEsami(NULL, FALSE, TRUE);
				return;
			}*/

			if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury)
			{
				if (m_pEsamiSet->m_lIdUtenteSuperLock != GetUserIDForLockSuperlock())
				{
					if (!(theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_01))
					{
						theApp.AfxMessageBoxEndo(IDS_RIAPERTURAESAME_SOLOAMMINISTRATOREOPROPRIETARIO);
						return;
					}
				}
			}
			else
			{
				BOOL bPuoSoloAmministratore = FALSE;
				if ((theApp.m_lChiusuraEsameRitardoInvioOre > 0) && theApp.m_bRiaperturaEsameSoloAmministratore)
				{
					CCustomDate dateNow(TRUE, TRUE);

					CCustomDate datePrimaChiusura;
					if (m_pEsamiSet->m_sDataOraSuperLockPrimo.IsEmpty())
						datePrimaChiusura.SetDateTime(m_pEsamiSet->m_sDataOraSuperLock);
					else
						datePrimaChiusura.SetDateTime(m_pEsamiSet->m_sDataOraSuperLockPrimo);

					if (GetDateTimeDifferenceInHoursFromLongs(dateNow.GetDate(), datePrimaChiusura.GetDate()) >= theApp.m_lChiusuraEsameRitardoInvioOre)
						bPuoSoloAmministratore = TRUE;
				}

				if (bPuoSoloAmministratore && !(theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_01))
				{
					theApp.AfxMessageBoxEndo(IDS_RIAPERTURAESAME_SOLOAMMINISTRATORE);
					return;
				}
				//Julio 10/08/2018
				if ((theApp.m_lChiusuraEsameRitardoInvioMinuti > 0) && theApp.m_bRiaperturaEsameSoloAmministratore)
				{
					CCustomDate dateNow(TRUE, TRUE);

					CCustomDate datePrimaChiusura;
					if (m_pEsamiSet->m_sDataOraSuperLockPrimo.IsEmpty())
						datePrimaChiusura.SetDateTime(m_pEsamiSet->m_sDataOraSuperLock);
					else
						datePrimaChiusura.SetDateTime(m_pEsamiSet->m_sDataOraSuperLockPrimo);

					if (GetDateTimeDifferenceInMinutesFromLongs(dateNow.GetDate(), datePrimaChiusura.GetDate()) >= theApp.m_lChiusuraEsameRitardoInvioMinuti)
						bPuoSoloAmministratore = TRUE;
				}

				if (bPuoSoloAmministratore && !(theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_01))
				{
					theApp.AfxMessageBoxEndo(IDS_RIAPERTURAESAME_SOLOAMMINISTRATORE);
					return;
				}
				//
			}

			if (theApp.AfxMessageBoxEndo(theApp.m_enumFirmaDigitale == CEndoxApp::sign_disabled ? IDS_CHIUSURA_ANNULLA : IDS_CHIUSURA_ANNULLAFIRMA, MB_YESNO) == IDYES)
			{
				// Sandro 30/03/2016 //

				if (theApp.m_lChiusuraEsameRitardoInvioOre > 0 || theApp.m_lChiusuraEsameRitardoInvioMinuti > 0)
				{
					//Se è attivato l'invio differito, se esiste una precedente chiusura non ancora gestita dall'integrazione, annullo la chiusura eliminando il pdf
					//	altrimenti sblocco l'esame nella maniera tipici alimentando anche ext_esami_sbloccati
					CString sFilterTeeemp;
					sFilterTeeemp.Format("IDEsame=%li AND Eseguito=0", m_pEsamiSet->m_lContatore);

					CEsamiChiusiSet setTeeemp;
					setTeeemp.SetOpenFilter(sFilterTeeemp);
					setTeeemp.SetSortRecord("ID DESC");
					if (setTeeemp.OpenRecordset("CEsamiView::OnCommandFileAnnullaChiusuraEsameCorrente"))
					{
						if (setTeeemp.IsEOF())
						{
							m_pEsamiSet->SbloccaEsame(this);
						}
						else
						{
							m_pEsamiSet->AnnullaChiusura(this, setTeeemp.m_lID);
						}

						setTeeemp.CloseRecordset("CEsamiView::OnCommandFileAnnullaChiusuraEsameCorrente");
					}
				}
				else
				{
					m_pEsamiSet->SbloccaEsame(this);
				}


				//

				UpdateData(FALSE);
			}
		}
		// Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
		else if (lIDFase == CO_FASE_LIBERA_LAUDO)
		{
			//Julio - removendo este bloco pois no fleury sempre usaremos o metodo FleuryPossoModificare
			/*if (!CEsamiSet().EsameSbloccabile(m_pEsamiSet->m_lContatore))
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAMEBLOCCATO));
				MovePazientiAndEsami(NULL, FALSE, TRUE);
				return;
			}*/
			if (theApp.m_bAtivaP3)
			{
				if (theApp.m_bPersonalizzazioniBrasileFleury && (theApp.m_bFaseExtraAmarradoAoSuperlock && m_pEsamiSet->m_bLocked && m_pEsamiSet->m_bSuperLocked) || !theApp.m_bFaseExtraAmarradoAoSuperlock)
				{
					if (!(theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_01))
					{
						theApp.AfxMessageBoxEndo(IDS_RIAPERTURAESAME_SOLOAMMINISTRATOREOPROPRIETARIO);
						return;
					}
					else
					{
						if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ANULA_LIBERA_LAUDO), MB_YESNO) == IDYES)
						{
							CString sFilter;

							if (CEsamiSet().IsConiugatoSecondario(m_pEsamiSet->m_lContatore) || ExameSecundario(m_pEsamiSet->m_lContatore))
								theApp.AfxMessageBoxEndo("A substituição de laudo deve ser realizada pelo exame principal.");

							sFilter.Format("IDESAME=%li AND IDFASE=%li AND ELIMINATO = 0", m_pEsamiSet->m_lContatore, lIDFase);

							AnulaFaseEConjugados(lIDFase);
							UpdateData(FALSE);
						}
					}
				}
			}
		}
		else
		{

			BeginWaitCursor();

			long lIDPDf = 0;

			//Ricerca ed elimina la riga della fasechiusa
			CString sFilter;
			sFilter.Format("IDESAME=%li AND IDFASE=%li", m_pEsamiSet->m_lContatore, lIDFase);

			CEsamiFasiChiuseSet set;
			set.SetOpenFilter(sFilter);

			if (set.OpenRecordset("CEsamiView::OnCommandAnnullaChiudiFase"))
			{
				if (!set.IsEOF())
				{
					lIDPDf = set.m_lIDPdf;

					set.DeleteRecordset("CEsamiView::OnCommandAnnullaChiudiFase");
				}

				set.CloseRecordset("CEsamiView::OnCommandAnnullaChiudiFase");
			}

			//Setta il pdf a eliminato
			//Cancello il pdf
			if (lIDPDf > 0)
				CPdfManager().SetPdfEliminato(lIDPDf, m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore, theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer);

			EndWaitCursor();
		}

		BeginWaitCursor();

		RicaricaDatiAssociatiAllEsame();		
		MovePazientiAndEsami(NULL, FALSE, TRUE);

		EndWaitCursor();
	}
}
// Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
CString CEsamiView::ComboSelecionaMotivo()
{
	long lArrayCount = 0;
	long lArrayPos = 0;
	CString sRetorno = "";

	CComboBoxSet setComboBox(CMB_ESA_MOTIVOCANCEL);
	setComboBox.SetSortRecord("Testo");

	if (setComboBox.OpenRecordset("ComboSelecionaMotivo"))
	{
		lArrayCount = setComboBox.GetRecordCount();
		if (lArrayCount > 0)
		{
			CString *sArray = new CString[lArrayCount];

			while (!setComboBox.IsEOF())
			{
				sArray[lArrayPos] = setComboBox.m_sTesto;
				setComboBox.MoveNext();
				lArrayPos++;
			}

			CSelectNumeroFichaDlg selectDlg(this, "SELECIONE UM MOTIVO", sArray, lArrayCount);

			if (selectDlg.DoModal() == IDOK)
			{
				sRetorno = selectDlg.m_sSelectedFicha;
			}
		}
		setComboBox.CloseRecordset("ComboSelecionaMotivo");
	}
	return sRetorno;
}

void CEsamiView::AnulaFaseEConjugados(long lIDFase)
{
	CString sMessaggio = "";
	CString sFilter = "";
	BOOL bModifica = TRUE;
	CString sMotivo = "";
	sMotivo = ComboSelecionaMotivo();

	if (sMotivo.IsEmpty())
	{
		theApp.AfxMessageBoxEndo("Operação cancelada.");
		return;
	}
	else
	{
		if (EnviaAnulaLiberaLaudo(sMessaggio, m_pEsamiSet->m_sCodEsame, sMotivo))
		{
			/*
			try
			{
				long idEsamiFasiChiuse = CEsamiFasiChiuseSet().DelecaoLogicaComMotivo(m_pEsamiSet->m_lContatore, lIDFase, sMotivo);
				CExtEsamiFasiChiuseSet().DelecaoLogicaExt(idEsamiFasiChiuse);
			}
			catch (...)
			{
				theApp.AfxMessageBoxEndo("Erro ao anular Liberação de laudo.");
				return;
			}
			*/
			
			m_pEsamiSet->AnnullaProtocoloXXI();
			/* Faz a substituição de resultados para fichas conjugadas
			theApp.m_bPossuiConjugados = RefertoPrincipale(m_pEsamiSet->m_lContatore);
			if (theApp.m_bPossuiConjugados)
			{
				CEsamiIntegratiSet setEsamiIntegrati;
				CEsamiSet setEsami;
				sFilter.Format("IDESAMEPRINCIPALE = '%d' AND ELIMINATO = 0", m_pEsamiSet->m_lContatore);
				setEsamiIntegrati.SetOpenFilter(sFilter);
				if (setEsamiIntegrati.OpenRecordset("CEsamiView::AnulaFaseEsamiIntegrati"))
				{
					if (setEsamiIntegrati.IsEOF())
					{
						theApp.AfxMessageBoxEndo("A substituição de laudo deve ser realizada pelo exame principal.");
					}
					else
					{
						m_pEsamiSet->AnnullaProtocoloXXI();

						while (!setEsamiIntegrati.IsEOF())
						{
							sFilter.Format("CONTATORE = %d AND ELIMINATO = 0", setEsamiIntegrati.m_lIDEsameSecondario);
							setEsami.SetOpenFilter(sFilter);
							if (setEsami.OpenRecordset("CEsamiView::AnulaFaseEsamiEsamiIntegrati"))
							{
								if (!setEsami.IsEOF())
								{
									if (EnviaAnulaLiberaLaudo(sMessaggio, setEsami.m_sCodEsame, sMotivo))
									{
										try
										{
											setEsami.AnnullaProtocoloXXI();
											setEsamiIntegrati.MoveNext();
										}
										catch (...)
										{
											theApp.AfxMessageBoxEndo("Erro ao anular Liberação de laudo.");
											return;
										}
									}
									else
									{
										theApp.AfxMessageBoxEndo(sMessaggio);
										return;
									}
								}
								else
								{
									theApp.AfxMessageBoxEndo("A substituição de laudo deve ser realizada pelo exame principal.");
									return;
								}
							}
							setEsami.CloseRecordset("CEsamiView::AnulaFaseEsamiEsamiIntegrati");
						}
					}
					setEsamiIntegrati.CloseRecordset("CEsamiView::AnulaFaseEsamiIntegrati");
				}
			}

			if (m_pEsamiSet->m_sCodEsame == m_pEsamiSet->m_sRefertoConiugatoPrincipale)
			{
				if (m_pEsamiSet->m_bSuperLocked)
				{
					CEsamiSet setEsami;
					sFilter.Format("CODESAME <> '%s' AND REFERTOCONIUGATOPRINCIPALE = '%s' AND ELIMINATO = 0", m_pEsamiSet->m_sCodEsame, m_pEsamiSet->m_sCodEsame);
					setEsami.SetOpenFilter(sFilter);
					if (setEsami.OpenRecordset("CEsamiView::AnulaFaseEsami"))
					{
						if (setEsami.IsEOF())
						{
							theApp.AfxMessageBoxEndo("A substituição de laudo deve ser realizada pelo exame principal.");
							return;
						}
						else
						{
							m_pEsamiSet->AnnullaProtocoloXXI();

							while (!setEsami.IsEOF())
							{
								if (EnviaAnulaLiberaLaudo(sMessaggio, setEsami.m_sCodEsame, sMotivo))
								{
									try
									{
										setEsami.AnnullaProtocoloXXI();
										setEsami.MoveNext();
									}
									catch (...)
									{
										theApp.AfxMessageBoxEndo("Erro ao anular Liberação de laudo.");
										return;
									}
								}
								else
								{
									theApp.AfxMessageBoxEndo(sMessaggio);
									return;
								}
							}
						}
						setEsami.CloseRecordset("CEsamiView::AnulaFaseEsami");
					}
				}
				else
				{
					theApp.AfxMessageBoxEndo("É necessário que o exame esteja desbloqueado antes que seja anulado.");
				}
			}

			if ((theApp.m_bPossuiConjugados) || (m_pEsamiSet->m_sCodEsame == m_pEsamiSet->m_sRefertoConiugatoPrincipale))
			{
				theApp.AfxMessageBoxEndo("Fases de exames anuladas com sucesso.");
			}
			else
			{
			*/
			theApp.AfxMessageBoxEndo("Fase de exames anulada com sucesso.");
		}
		else
		{
			theApp.AfxMessageBoxEndo(sMessaggio);
			return;
		}
	}
}

// Luiz - 13/05/2019 - P3 - Atualiza nome/sobrenome Médico - Inclui Médicos solicitantes
void CEsamiView::OnCommandAtualizaMedicoSolicitante()
{
	BeginWaitCursor();

	try
	{
		long lIdExt = CExtEsameMediciRichiedenteSet().Insert(m_pEsamiSet->m_lContatore);
		if (lIdExt > 0)
			theApp.AfxMessageBoxEndo("Exame cadastrado para atualização.");
		else
			theApp.AfxMessageBoxEndo("Erro na marcação de médico solicitante.");
	}
	catch (...)
	{
		theApp.AfxMessageBoxEndo("Erro ao cadastrar exame para atualização de médico solicitante.");
	}

	EndWaitCursor();
}

//Gabriel BUG 6225 - Lista DO
void CEsamiView::OnCommandMenuEsameCorrenteReconvocazione()
{
	CRiconvocazioneDlg dlg(this, this);
	dlg.DoModal();
}

//Gabriel - P3
BOOL CEsamiView::SubstituicaoResultado(CString sMotivo)
{
	BOOL bReturn = FALSE;
	CString sMessaggio = "";
	CString sRicovero, sCodEsame;
	sRicovero = m_pEsamiSet->m_sRicovero;
	sCodEsame = m_pEsamiSet->m_sCodEsame;

	if (!sRicovero.IsEmpty() && !sCodEsame.IsEmpty())
	{
		int n1 = sCodEsame.Find("_");
		if (n1 > 0)
		{
			int n2 = sCodEsame.Find("_", n1 + 1);
			if (n2 > 0)
			{
				CString sItem = sCodEsame.Mid(n1 + 1);
				sItem.Replace("_", "0");

				CString sSiglaUtente = "";

				long lUserID;
				AMLogin_GetUserID(&lUserID);
				if (CMediciSet().GetContatoreFromUserID(lUserID) > 0)
				{
					sSiglaUtente = CMediciSet().GetCodiceFromUserID(lUserID);
				}
				else
				{
					// se non sono un medico uso il 3L3N della Tesi //
					sSiglaUtente = CString("EQT496").Left(3);
				}

				if (sSiglaUtente.GetLength() > 0)
				{
					//Chamo a API da substituição de resultado
					examReplaceRequest request;
					sprintf_s(request.szFicha, sRicovero);
					sprintf_s(request.szItem, sItem);
					sprintf_s(request.szSiglaUsuarioSistema, sSiglaUtente);
					sprintf_s(request.szIdSistema, "1"); // sempre 1, è endox //

					CExamService SubstituicaoService(theApp.m_sHttpServerSubstituicaoResultado);
					examResponse response = SubstituicaoService.SubstituirResultado(request, theApp.m_sHttpServerSubstituicaoResultado);

					if (strcmp(response.szCodigoDeErro, "0") == 0)
					{
						bReturn = (_strcmpi(response.szPodeAlterar, "true") == 0);
						if (!bReturn)
						{
							sMessaggio = theApp.GetMessageString(IDS_FLEURY_ERROR_004);
							return bReturn;
						}
					}
					else
					{
						sMessaggio = theApp.GetMessageString(IDS_FLEURY_ERROR_006) + "\n\n" + CString(response.szCodigoDeErro);
						theApp.AfxMessageBoxEndo(sMessaggio);
						return bReturn;
					}
					bReturn = TRUE;
				}
			}
		}
	}

	return bReturn;
}

//Gabriel - TCP
void CEsamiView::OnCommandMenuOpzioniSetupUnitaTCP()
{
	CSetupUnitaTCPDlg(this).DoModal();
}