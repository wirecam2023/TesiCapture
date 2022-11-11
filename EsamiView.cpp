#include "stdafx.h"
#include "Endox.h"
#include "EsamiView.h"
#include <io.h>

#include "DLL_Imaging\h\AmLogin.h"
#include "DLL_Imaging\h\AmTesiSign.h"
#include "DLL_Imaging\h\ImgArchive.h"

#include "LibStreaming.h"

#include "AccessDlg.h"
#include "AgendeSet.h"
#include "AlbumConfrontoDermoxDlg.h"
#include "AlbumConfrontoDlg.h"
#include "AlbumEsameDlg.h"
#include "AlbumForm.h"
#include "AnatomiaPatologicaDlg.h"
#include "AnatomiaPatologicaForm.h"
#include "AnatomiaPatologicaSet.h"
#include "AnatomiaPatologicaTastiForm.h"
#include "BostonScoreSet.h"
#include "CambiaVersioneProgressivoAnnoDlg.h"
#include "CampiObbligatoriSet.h"
#include "CittadinanzaTrentoSet.h"
#include "CodificaRegionaleExBulkSet.h"
#include "CodificaRegionaleGruppiBulkSet.h"
#include "ComboConfigSet.h"
#include "ComuniBulkSet.h"
#include "ComuniSet.h"
#include "CupWorkListManager.h"
#include "CronicitaCambiaDlg.h"
#include "CronicitaPazienteDlg.h"
#include "CustomDate.h"
#include "DBVersionSet.h"
#include "DiagnosiEsamiSet.h"
#include "DigitalSignUtil.h"
#include "DisplayHelper.h"
#include "DistrettiSediEsamiSet.h"
#include "DocManager.h"
#include "DocumentiDlg.h"
#include "DynFormSet.h"
#include "ElemReportSet.h"
#include "EndoGridCLGruppiUtenteSet.h"
#include "EndoGridCLViewVersionUOSet.h"
#include "EndoxBar.h"
#include "EsamiChiusiSet.h"
#include "EsamiDoc.h"
#include "EsamiFarmaciCroniciSet.h"
#include "EsamiFasiChiuseSet.h"
#include "EsamiIntegratiSet.h" // Luiz - 07/05/2019 - P3 - Desconjuga exames - ESAMIINTEGRATI
#include "EsamiNonErogatiSet.h"
#include "EsamiSet.h"
#include "EspelliDlg.h"
#include "EtichetteSet.h"
#include "ExportDlg.h"
//#include "ExtComboPrestazioni.h" // Luiz - 12/08/2019 - P4 - Permite envio de exames MAMOGUS de acordo com opção do usuário
#include "ExtOrdiniCampiAggiuntiviSet.h"
#include "ExtOrdiniEsenzioniSet.h"
#include "ExtOrdiniSet.h"
#include "ExtPatientEventSet.h"
#include "ExtPrestazioniSet.h"
#include "FarmaciBulkSet.h"
#include "FarmaciGruppiRicBulkSet.h"
#include "FasiEsameSet.h"
#include "FieldDlg.h"
#include "FileBmp.h"
#include "FirmaMotivoSostituzioneDlg.h"
#include "GestioneEsamiPendentiDlg.h"
#include "GetCodeDlg.h"
#include "GetCodeFiscDlg.h"
#include "IntestazioneNewDlg.h"
#include "InvianteDynForm.h"
#include "IstologiaTotForm.h"
#include "IstologiaTotForm5Righe.h"
#include "IstologiaTotForm5RighePlus.h"
#include "JoinEsamiSet.h"
#include "ListaOsservazioniDlg.h"
#include "ListaPrenotazioniDlg.h"
#include "ListaPrenotazioniCupDlg.h"
#include "ListaPrenotazioniCupDicomDlg.h"
#include "ListaPrenotazioniDMSDlg.h"
#include "LockManager.h"
#include "LogFileWriter.h"
#include "MalattieCronicheSet.h"
#include "MediciCurantiInviantiBulkSet.h"
#include "MediciSet.h"
#include "MediciTrentoSet.h"
#include "MmSystem.h"
#include "ModelessDlg.h"
#include "MonitoraggioBaseDynForm.h"
#include "MosaicDlg.h"
#include "MotivoDlg.h"
#include "NumeroCopieStampaDlg.h"
#include "PacsArchiver.h"
#include "PazientiDlg.h"
#include "PazientiEsenzioniSet.h"
#include "PazientiStoricoSet.h"
#include "PdfAnteprimaDlg.h"
#include "PdfManager.h"
#include "PdfStampaDlg.h"
#include "PdfUtilInterface.h"
#include "ProvenienzaSet.h"
#include "QueryCountDlg.h"
#include "QueryDlg.h"
#include "QueryDoubleDlg.h"
#include "QueryOnlyPatiensDlg.h"
#include "ReadyReportResultWaitingDlg.h"
#include "RefertoDlg.h"
#include "RefertoForm.h"
#include "ReportsDefaultSet.h"
#include "ReportsEtichetteSet.h"
#include "ReportsMacroDettSet.h"
#include "ReportsMacroSet.h"
#include "ReportsMacroUseDlg.h"
#include "RichiesteAnatomiaPatologicaDlg.h"
#include "SaleEsameSet.h"
#include "SearchTypeDlg.h"
#include "SediEsameSet.h"
#include "SelezioneDispositivoVSDlg.h"
#include "SetupDlg.h"
#include "ShowDbQueriesDlg.h"
#include "SmartCardPinDlg.h"
#include "SorgentiStreamingSet.h"
#include "TipoEsameNew.h"
#include "TipoEsameSet.h"
#include "UOSet.h"
#include "UOUtenteDlg.h"
#include "UOUtenteSet.h"
#include "VistaCampiObbligatoriFasiNewSet.h"
#include "VistaEsamiConPrestazioniPrincipaliSet.h"
#include "VistaEsamiPendentiSet.h"
#include "VistaExtPrestazioniSet.h"
#include "VistaGruppiSet.h"
#include "VitalSignDispositiviSet.h"
#include "VitalSignManager.h"
#include "VitalSignMisurazioniHeaderSet.h"
#include "WaitRemoteThreadDlg.h"
#include "WebDeployer.h"
#include "WorkListManager.h"
#include "xrclient\xrclient.h"
#include "TutorialFilesSet.h"
#include "ModalityWorklistSCP.h"
#include "WaitFleuryTransferitoDlg.h"
#include "SelectNumeroFichaDlg.h"
#include "GenomicaRefertoDlg.h" // Julio Genomica
#include "UtentiSet.h"
#include "ExtComboPrestazioni.h" //Julio - BUG 3365 - MAMOGUS
#include "VistaComboPrestazioni.h" //Julio - BUG 3365 - MAMOGUS
#include "ComboPrestazioni.h" //Julio - BUG 3365 - MAMOGUS
#include "RiconvocazioneSet.h" //Gabriel BUG 6225 - Lista DO
#include "ImageDlg.h" //Gabriel BUG 6225 - Lista DO

#define FILTRO_SOLO_ESAMI_ONLYPATIENTS		-3	// Sandro 29/08/2013 // RAS 20130121 //
#define FILTRO_PAZIENTI_ESAMI_ONLYPATIENTS	-2	// Sandro 29/08/2013 // RAS 20130121 //
#define FILTRO_SOLO_ESAMI					-1
#define FILTRO_PAZIENTI_ESAMI				 0
#define FILTRO_SOLO_PAZIENTI				 1

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL m_bRicercaDiretta = FALSE;

IMPLEMENT_DYNCREATE(CEsamiView, CResizableFormView)

CEsamiView::CEsamiView()
	: CResizableFormView(CEsamiView::IDD),
	m_ctrlStaticFrameStato(&theApp.m_colorStatoSfondo)
{
	m_pWndExport = NULL;

	m_pPazientiSet = NULL;
	m_pEsamiSet = NULL;

	m_pFormImmagini = NULL;
	for (int i = 0; i < form_list_total; i++)
		m_pDynForm[i] = NULL;

	m_bReadOnly = FALSE;
	m_bValoriDefault = FALSE;

	m_pQueryDlg = NULL;
	m_pSospesiIstologiciDlg = NULL;

	CFileBmp::m_pEsamiView = this;

	m_pPatientBar = NULL;
	m_pExamBar = NULL;

	m_pImgManager = NULL;
	m_pDocManager = NULL;

	m_hDevMode = NULL;
	m_hDevNames = NULL;

	m_lPrevVers = -1;
	m_lIDTipoEsameAutoInsert = -1;

	m_brushSfondoPaziente.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
	m_brushSfondoStato.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));

	m_sCognomeRicercaAnagCen = "";
	m_sNomeRicercaAnagCen = "";
	m_sDataNascitaRicercaCen = "";
	m_sSessoRicercaAnagCen = "";
	m_sCodiceFiscaleRicercaAnagCen = "";

	m_lLocalImagesSelected = 0;
	m_lLocalMultiPageTiffSelected = 0;

	m_lNumDocumentsPatient = 0;
	m_lNumDocumentsPatientOffset = 0;

	m_lNumDocumentsExam = 0;
	m_lNumDocumentsExamOffset = 0;

	m_lNumDocumentsExamCarestream = 0;
	m_lNumDocumentsExamCarestreamOffset = 0;

	m_sFleuryFicha = "";
	m_sFleuryItem = "";

	// Sandro 15/07/2014 //
	if (theApp.m_bSaveCompleteLog)
	{
#ifndef _DEBUG
		CString sMsbBox = theApp.GetMessageString(IDS_COMPLETELOG_ACTIVATED);
		sMsbBox.Trim();

		if (!sMsbBox.IsEmpty())
			theApp.AfxMessageBoxEndo(sMsbBox, MB_OK | MB_ICONINFORMATION);
#endif

		VerificaPercorso(theApp.m_sDirProg + "\\LOGCOMPLETO");

		// Sandro 31/07/2014 // eventualmente cancello i "vecchi" files di log //
		if (theApp.m_lSaveCompleteLogDays > 0)
		{
			CString strWildCard = theApp.m_sDirProg + "\\LOGCOMPLETO\\*.*";

			CFileFind finder;
			BOOL bWorking = finder.FindFile(strWildCard);

			while (bWorking)
			{
				bWorking = finder.FindNextFile();

				if (finder.IsDots())
					continue;

				if (finder.IsDirectory())
					continue;

				BOOL bDelete = TRUE;

				CString sFile = finder.GetFileName();
				if (
					isdigit(sFile[0]) &&
					isdigit(sFile[1]) &&
					isdigit(sFile[2]) &&
					isdigit(sFile[3]) &&
					sFile[4] == '_' &&
					isdigit(sFile[5]) &&
					isdigit(sFile[6]) &&
					sFile[7] == '_' &&
					isdigit(sFile[8]) &&
					isdigit(sFile[9]) &&
					sFile[10] == '.'
					)
				{
					int nYear = atoi(sFile.Left(4));
					int nMonth = atoi(sFile.Mid(5, 2));
					int nDay = atoi(sFile.Mid(8, 2));

					COleDateTime odtFile(nYear, nMonth, nDay, 0, 0, 0);
					if (odtFile.m_status == COleDateTime::valid)
					{
						COleDateTimeSpan odtsDiff = COleDateTime::GetCurrentTime() - odtFile;

						if (abs(odtsDiff.GetDays()) <= theApp.m_lSaveCompleteLogDays)
						{
							// il file è ancora "giovine", non lo elimino //
							bDelete = FALSE;
						}
					}
				}

				if (bDelete)
				{
					CString sFileToDelete = theApp.m_sDirProg + "\\LOGCOMPLETO\\" + finder.GetFileName();
					SetFileAttributes(sFileToDelete, FILE_ATTRIBUTE_NORMAL);
					DeleteFile(sFileToDelete);
				}
			}

			finder.Close();
		}
	}

	// Sandro 11/11/2010 //
	if (theApp.m_bShowDbQueries)
	{
		theApp.m_pShowDbQueriesWnd = new CShowDbQueriesDlg(this);
		theApp.m_pShowDbQueriesWnd->CreateModelessDialog(this);
	}

	// che ne dici SILVANO se inizializziamo le variabili di classe ?!? //
	m_lIDPrenotazione = 0;

	//
	m_bBurning = FALSE;
	m_bImporting = FALSE;
	m_bPrinting = FALSE;
	m_bRimage = FALSE;

	//

	// m_pReportElementList = NULL;

	m_bMonitoraggioAttivo = FALSE;
	m_lIDHeaderMisurazioniInCorso = 0;

	//

	m_bVisualizzaTastoCaricaImmagini = FALSE;

	m_pImageDlg = NULL; //Gabriel BUG 6225 - Lista DO

	m_lStreamingState = StreamingStatus::disabled;
}

CEsamiView::~CEsamiView()
{
	OnDestroyQueryWnd(NULL, NULL);
	OnDestroySospesiIstologiciWnd(NULL, NULL);

	if (m_pPatientBar != NULL)
		delete m_pPatientBar;

	if (m_pExamBar != NULL)
		delete m_pExamBar;

	if (m_pWndExport)
	{
		m_pWndExport->DestroyWindow();

		delete m_pWndExport;
		m_pWndExport = NULL;
	}

	if (m_pFormImmagini != NULL)
	{
		delete m_pFormImmagini;
		m_pFormImmagini = NULL;
	}
	for (int i = 0; i < form_list_total; i++)
	{
		if (m_pDynForm[i] != NULL)
		{
			delete m_pDynForm[i];
			m_pDynForm[i] = NULL;
		}
	}

	CFileBmp::DeleteListSelected(ALL_IMAGES);
	CFileBmp::m_pEsamiView = NULL;

	if (m_pImgManager != NULL)
	{
		delete m_pImgManager;
		m_pImgManager = NULL;
	}
	if (m_pDocManager != NULL)
	{
		delete m_pDocManager;
		m_pDocManager = NULL;
	}

	// if (m_pReportElemSet)
	//	delete m_pReportElemSet;

	m_brushSfondoPaziente.DeleteObject();
	m_brushSfondoStato.DeleteObject();

	//Simone RIMA 16002
	// Fermo il thread
	if (theApp.m_bCanAcquire)
	{
		/*SetEvent(m_hEventExitStreamingStateThread);

		EnterCriticalSection(&m_streamingStateThreadCS);
		LeaveCriticalSection(&m_streamingStateThreadCS);
		DeleteCriticalSection(&m_streamingStateThreadCS);

		CloseHandle(m_hEventExitStreamingStateThread);*/
	}

	//

}

BEGIN_MESSAGE_MAP(CEsamiView, CResizableFormView)

	ON_WM_ACTIVATE()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_CHAR()

	ON_BN_CLICKED(IDC_PAZIENTE_FIRST, OnPazienteFirst)
	ON_BN_CLICKED(IDC_PAZIENTE_PREV, OnPazientePrev)
	ON_BN_CLICKED(IDC_PAZIENTE_GOTO, OnPazienteGoto)
	ON_BN_CLICKED(IDC_PAZIENTE_NEXT, OnPazienteNext)
	ON_BN_CLICKED(IDC_PAZIENTE_LAST, OnPazienteLast)
	ON_BN_CLICKED(IDC_PAZIENTE_NEW, OnPazienteNew)
	ON_BN_CLICKED(IDC_PAZIENTE_MODIFY, OnPazienteModify)
	ON_BN_CLICKED(IDC_PAZIENTE_DEL, OnPazienteDelete)
	ON_BN_CLICKED(IDC_PAZIENTE_QUERY_DEF, OnPazienteQuery)
	ON_BN_CLICKED(IDC_PAZIENTE_QUERY_APP, OnApplicaQuery)
	ON_BN_CLICKED(IDC_PAZIENTE_UNDO, OnPazienteRefresh)
	ON_BN_CLICKED(IDC_ICON_ALLERGIE, OnClickIconAllergie)
	ON_BN_CLICKED(IDC_ICON_SEGNALATO, OnClickIconSegnalato)
	ON_BN_CLICKED(IDC_DATI_PAZIENTE, OnBnClickedDatiPaziente)
	ON_BN_CLICKED(IDC_PAZIENTE_PRENOTAZIONE, OnPrenotazione)
	ON_BN_CLICKED(IDC_PAZIENTE_ALBUM, OnAlbum)
	ON_BN_CLICKED(IDC_BTN_CONCLUSIONI, OnBtnConclusioni)
	ON_BN_CLICKED(IDC_PAZIENTE_CRONICO, OnBtnPazienteCronico)
	ON_BN_CLICKED(IDC_BTN_COMANDO, OnBtnComando)
	ON_BN_CLICKED(IDC_LISTA_PRENOTAZIONI, OnListaPrenotazioni)
	ON_BN_CLICKED(IDC_PAZIENTE_ALLEGATI, OnPazienteAllegati)
	ON_BN_CLICKED(IDC_FICHA, OnFleuryFicha)
	ON_BN_CLICKED(IDC_FICHA2, OnFleuryFicha2)
	ON_BN_CLICKED(IDC_ASSESSORIA, OnFleuryAssessoria)
	ON_BN_CLICKED(IDC_ESAME_FIRST, OnEsameFirst)
	ON_BN_CLICKED(IDC_ESAME_PREV, OnEsamePrev)
	ON_BN_CLICKED(IDC_ESAME_NEXT, OnEsameNext)
	ON_BN_CLICKED(IDC_ESAME_LAST, OnEsameLast)
	ON_BN_CLICKED(IDC_ESAME_NEW, OnEsameNew)
	ON_BN_CLICKED(IDC_ESAME_MODIFY, OnEsameModify)
	ON_BN_CLICKED(IDC_ESAME_DEL, OnEsameDelete)
	ON_BN_CLICKED(IDC_ESAME_UPDATE, OnEsameUpdate)
	ON_BN_CLICKED(IDC_ESAME_UNDO, OnEsameRefresh)
	ON_BN_CLICKED(IDC_ESAME_QUERY_DEF, OnEsameQuery)
	ON_BN_CLICKED(IDC_ESAME_QUERY_APP, OnApplicaQuery)
	ON_BN_CLICKED(IDC_ESAME_ALBUM, OnAlbumConfronto)
	ON_BN_CLICKED(IDC_TOOLBAR_STAMPAREPORT, OnToolbarStampaReport)
	ON_BN_CLICKED(IDC_TOOLBAR_STAMPAREPORTMACRO, OnToolbarStampaReportMacro)
	ON_BN_CLICKED(IDC_ESAME_ALLEGATI, OnEsameAllegati)
	ON_BN_CLICKED(IDC_ESAME_ALLEGATICARESTREAM, OnEsameAllegatiCarestream)
	ON_BN_CLICKED(IDC_BTN_SHOW, OnBnClickedBtnShow)
	ON_BN_CLICKED(IDC_BTN_HIDE, OnBnClickedBtnHide)
	ON_BN_CLICKED(IDC_BTN_IMMAGINI, OnBnClickedBtnImmagini)
	ON_BN_CLICKED(IDC_BTN_MON_STOP, OnBnClickedBtnMonStop)

	ON_COMMAND_RANGE(0, 65535, OnCommand)
	ON_UPDATE_COMMAND_UI_RANGE(0, 65535, OnUpdateUI)

	ON_MESSAGE(EM_DESTROY_QUERY_WND, OnDestroyQueryWnd)
	ON_MESSAGE(EM_DESTROY_SOSPESIISTOLOGICI_WND, OnDestroySospesiIstologiciWnd)

	ON_MESSAGE(EM_HIDE_QUERY_WND, OnHideQueryWnd)
	ON_MESSAGE(EM_HIDE_SOSPESIISTOLOGICI_WND, OnHideSospesiIstologiciWnd)

	ON_MESSAGE(EM_RELOAD_QUERY_WND, OnReloadQueryWnd)

	ON_MESSAGE(EPM_THREAD_IMPORT_SETPOS, OnThreadImportSetPos)
	ON_MESSAGE(EPM_THREAD_RIMAGE_SETPOS, OnThreadRimageSetPos)
	ON_MESSAGE(EPM_THREAD_RIMAGE_ON, OnThreadRimageOn)
	ON_MESSAGE(EPM_THREAD_RIMAGE_OFF, OnThreadRimageOff)

	ON_MESSAGE(EPM_THREAD_STARTMONITORAGGIO, OnThreadStartMonitoraggio)

	ON_EN_CHANGE(IDC_EDIT_FLEURYFICHA, &CEsamiView::OnEnChangeEditFleuryficha)
	ON_EN_CHANGE(IDC_EDIT_FLEURYITEM, &CEsamiView::OnEnChangeEditFleuryitem)

END_MESSAGE_MAP()

void CEsamiView::DoDataExchange(CDataExchange* pDX)
{
	CResizableFormView::DoDataExchange(pDX);

	//

	DDX_Control(pDX, IDC_STATIC_PAZIENTE, m_ctrlStaticPaziente);
	DDX_Control(pDX, IDC_LABEL_PAZIENTE_00, m_ctrlPatientLabel00);
	DDX_Control(pDX, IDC_LABEL_PAZIENTE_01, m_ctrlPatientLabel01);
	DDX_Control(pDX, IDC_LABEL_PAZIENTE_02, m_ctrlPatientLabel02);
	DDX_Control(pDX, IDC_LABEL_PAZIENTE_03, m_ctrlPatientLabel03);
	DDX_Control(pDX, IDC_LABEL_PAZIENTE_04, m_ctrlPatientLabel04);
	DDX_Control(pDX, IDC_LABEL_PAZIENTE_05, m_ctrlPatientLabel05);
	DDX_Control(pDX, IDC_LABEL_PAZIENTE_06, m_ctrlPatientLabel06);
	DDX_Control(pDX, IDC_LABEL_PAZIENTE_07, m_ctrlPatientLabel07);
	DDX_Control(pDX, IDC_LABEL_PAZIENTE_08, m_ctrlPatientLabel08);
	DDX_Control(pDX, IDC_STATIC_NUMESAME, m_ctrlStaticExamNum);

	DDX_Control(pDX, IDC_GRUPPO_ESAME, m_ctrlGruppoEsame);
	DDX_Control(pDX, IDC_SUBFORM_ALBUM, m_ctrlSubFormAlbum);
	DDX_Control(pDX, IDC_SUBFORM_ESAME, m_ctrlSubFormEsame);
	DDX_Control(pDX, IDC_SUBFORM_3, m_ctrlSubForm3);

	DDX_Control(pDX, IDC_BTN_HIDE, m_ctrlBtnHide);
	DDX_Control(pDX, IDC_BTN_SHOW, m_ctrlBtnShow);
	DDX_Control(pDX, IDC_BTN_IMMAGINI, m_ctrlBtnImmagini);

	DDX_Control(pDX, IDC_BTN_MON_STOP, m_ctrlBtnStopMonitoraggio);

	//Julio 09/03/2018
	if (theApp.m_bPersonalizzazioniBrasileFleury)
	{
		DDX_Control(pDX, IDC_EDIT_FLEURYFICHA, m_ctrlEditFleuryFicha);
		DDX_Text(pDX, IDC_EDIT_FLEURYITEM, m_sFleuryItem);
	}
	//

	if (!pDX->m_bSaveAndValidate)
	{
		// Sandro 09/06/2015 // RIMA 15040 //
		if (theApp.m_bPersonalizzazioniBrasileSirio)
		{
			DDX_FieldText(pDX, IDC_PAZIENTE_FISCALE, m_pEsamiSet->m_sRicovero, m_pEsamiSet->GetRecordset());
			DDX_FieldText(pDX, IDC_PAZIENTE_SANITARIO, m_pPazientiSet->m_sAssIden, m_pPazientiSet->GetRecordset());
		}
		else
		{
			DDX_FieldText(pDX, IDC_PAZIENTE_FISCALE, m_pPazientiSet->m_sCodFisc, m_pPazientiSet->GetRecordset());
			DDX_FieldText(pDX, IDC_PAZIENTE_SANITARIO, m_pPazientiSet->m_sCodSanit, m_pPazientiSet->GetRecordset());
		}

		// Sandro 20/11/2013 // RAS 20130186 //
		if (theApp.m_bMostraSecondoCognome)
		{
			CString sCognome = m_pPazientiSet->m_sCognome + " " + m_pPazientiSet->m_sCognome2;
			sCognome.Trim();
			SetDlgItemText(IDC_PAZIENTE_COGNOME, sCognome);
		}
		else
		{
			DDX_FieldText(pDX, IDC_PAZIENTE_COGNOME, m_pPazientiSet->m_sCognome, m_pPazientiSet->GetRecordset());
		}

		DDX_FieldText(pDX, IDC_PAZIENTE_NOME, m_pPazientiSet->m_sNome, m_pPazientiSet->GetRecordset());

		if (!m_pPazientiSet->IsFieldNull(&m_pPazientiSet->m_lSessoPaz))
		{
			switch (m_pPazientiSet->m_lSessoPaz)
			{
			case -1:
				SetDlgItemText(IDC_PAZIENTE_SESSO, theApp.GetMessageString(IDS_PAZIENTIDLG_ND));
				break;
			case 0:
				SetDlgItemText(IDC_PAZIENTE_SESSO, theApp.GetMessageString(IDS_PAZIENTIDLG_MALE));
				break;
			case 1:
				SetDlgItemText(IDC_PAZIENTE_SESSO, theApp.GetMessageString(IDS_PAZIENTIDLG_FEMALE));
				break;
			case 2:
				SetDlgItemText(IDC_PAZIENTE_SESSO, theApp.GetMessageString(IDS_PAZIENTIDLG_AMBIGOUS));
				break;
			case 3:
				SetDlgItemText(IDC_PAZIENTE_SESSO, theApp.GetMessageString(IDS_PAZIENTIDLG_NOTAPPLICABLE));
				break;
			case 4:
				SetDlgItemText(IDC_PAZIENTE_SESSO, theApp.GetMessageString(IDS_PAZIENTIDLG_OTHER));
				break;
			default:
				SetDlgItemText(IDC_PAZIENTE_SESSO, theApp.GetMessageString(IDS_PAZIENTIDLG_ND));
				break;
			}
		}
		else
			SetDlgItemText(IDC_PAZIENTE_SESSO, "");

		// Sandro 30/12/2013 // RAS 20130169 //

		CString sTelefono = "";

		m_pPazientiSet->m_sTelefono1.Trim();
		m_pPazientiSet->m_sTelefono2.Trim();
		m_pPazientiSet->m_sCellulare1.Trim();
		m_pPazientiSet->m_sCellulare2.Trim();

		if (!m_pPazientiSet->m_sTelefono1.IsEmpty())
			sTelefono = m_pPazientiSet->m_sTelefono1;

		if (!m_pPazientiSet->m_sTelefono2.IsEmpty())
		{
			if (!sTelefono.IsEmpty())
				sTelefono += " - ";

			sTelefono += m_pPazientiSet->m_sTelefono2;
		}

		if (!m_pPazientiSet->m_sCellulare1.IsEmpty())
		{
			if (!sTelefono.IsEmpty())
				sTelefono += " - ";

			sTelefono += m_pPazientiSet->m_sCellulare1;
		}

		if (!m_pPazientiSet->m_sCellulare2.IsEmpty())
		{
			if (!sTelefono.IsEmpty())
				sTelefono += " - ";

			sTelefono += m_pPazientiSet->m_sCellulare2;
		}

		DDX_Text(pDX, IDC_PAZIENTE_TELEFONO, sTelefono);

		//

		DDX_FieldDateEta(pDX, IDC_PAZIENTE_NATOIL, m_pPazientiSet->m_lNatoIlCustom, m_pPazientiSet);

		DDX_FieldText(pDX, IDC_PAZIENTE_NATOA, m_pPazientiSet->m_sNatoA, m_pPazientiSet->GetRecordset());
	}

	if (!pDX->m_bSaveAndValidate)
	{
		m_bPazientiPrev = FALSE;
		m_bPazientiNext = TRUE;
		m_bPazientiIsNull = !m_pPazientiSet->IsOpen() || m_pPazientiSet->IsBOF() || m_pPazientiSet->IsEOF();
		m_bPazientiValid = !m_bPazientiIsNull || theApp.m_nProgramMode & ADD_RECORD_PAZIENTI;
		m_bPazientiModify = theApp.m_nProgramMode & ADD_RECORD_PAZIENTI || theApp.m_nProgramMode & MODIFY_RECORD_PAZIENTI;
		m_bPazientiBusy = m_bPazientiModify || theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI;

		m_bEsamiPrev = FALSE;
		m_bEsamiNext = FALSE;
		m_bEsamiIsNull = !m_pEsamiSet->IsOpen() || m_pEsamiSet->IsBOF() || m_pEsamiSet->IsEOF();
		m_bEsamiValid = !m_bEsamiIsNull || theApp.m_nProgramMode & ADD_RECORD_ESAMI;
		m_bEsamiModify = theApp.m_nProgramMode & ADD_RECORD_ESAMI || theApp.m_nProgramMode & MODIFY_RECORD_ESAMI;
		m_bEsamiBusy = m_bEsamiModify || theApp.m_nProgramMode & FILTER_RECORD_ESAMI;

		m_bFilterBusy = theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI || theApp.m_nProgramMode & FILTER_RECORD_ESAMI;

		if (theApp.m_nProgramMode == NOTHING_MODE)
		{
			if (!m_pPazientiSet->IsBOF())
			{
				m_pPazientiSet->MovePrev();
				m_bPazientiPrev = !m_pPazientiSet->IsBOF();
				m_pPazientiSet->MoveNext();
			}
		}

		if (m_pEsamiSet->m_lNumEsame > 1)
			m_bEsamiPrev = TRUE;
		if (m_pEsamiSet->m_lNumEsame < m_pPazientiSet->m_lTotEsami)
			m_bEsamiNext = TRUE;

		CString strEsame = "";
		if (theApp.m_nProgramMode & ADD_RECORD_ESAMI || theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
			strEsame = theApp.GetMessageString(IDS_ESAMIVIEW_EXAM_NUM_1);
		else
			strEsame.Format(theApp.GetMessageString(IDS_ESAMIVIEW_EXAM_NUM_2), m_pEsamiSet->m_lNumEsame, m_pPazientiSet->m_lTotEsami);
		SetDlgItemText(IDC_NUMESAME, strEsame);

		// Sandro 31/10/2013 // RAS 20130165 //

		CRect rectFramePaziente = CRect(0, 0, 0, 0);
		if (::IsWindow(m_ctrlPatientLabel00))
		{
			m_ctrlPatientLabel00.GetWindowRect(rectFramePaziente);
			ScreenToClient(rectFramePaziente);
		}

		//Julio BUG 3456 - Contingencia
		if (theApp.m_bContingencia)
			theApp.m_colorPazienteSfondo = RGB(209, 0, 0); // RED
		else
			theApp.m_colorPazienteSfondo = CTipoEsameSet().GetSfondo(m_pEsamiSet->m_lIDEsame);
		//

		m_brushSfondoPaziente.DeleteObject();
		m_brushSfondoPaziente.CreateSolidBrush(theApp.m_colorPazienteSfondo);

		InvalidateRect(rectFramePaziente, FALSE);

		//
		UpdateFrameStato();
	}

	// Sandro Gallina - 27/01/2004 --> //
	CString strTemp;
	if (m_pPazientiSet->IsFieldNull(&m_pPazientiSet->m_lContatore) == FALSE)
		strTemp.Format(theApp.GetMessageString(IDS_ESAMIVIEW_PATIENT_NUM_1), m_pPazientiSet->m_lContatore);
	else
		strTemp = theApp.GetMessageString(IDS_ESAMIVIEW_PATIENT_NUM_2);

	if (m_pPazientiSet->m_bPazienteDelDirettore == TRUE) // confronto con TRUE perchè in inserimento/ricerca vale 2 //
		strTemp += " " + theApp.GetMessageString(IDS_DIRETTORE);

	SetDlgItemText(IDC_LABEL_PAZIENTE_00, strTemp);
	// <-- Sandro Gallina - 27/01/2004 //

	if (m_pEsamiSet != NULL)
	{
		switch (theApp.m_nApplication)
		{
		case PRG_CARDIOX:
		case PRG_ENDOX:
		case PRG_DERMOX:
		{
			GetDlgItem(IDC_LABEL_STATO_NEW1)->ShowWindow(SW_HIDE);

			if (theApp.m_sPassedConnectionString.IsEmpty())
			{
				if (theApp.m_bMostraCodiceEsame)
				{
					if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lData))
						SetDlgItemText(IDC_LABEL_STATO_NEW2, CTipoEsameSet().GetSigla(m_pEsamiSet->m_lIDEsame) + " " + theApp.GetMessageString(IDS_DEL) + " " + CCustomDate(m_pEsamiSet->m_lData).GetDate("%d/%m/%Y"));
					else
						SetDlgItemText(IDC_LABEL_STATO_NEW2, CTipoEsameSet().GetSigla(m_pEsamiSet->m_lIDEsame));

					// Qui ci va il conteggio degli esami dell'anno
					long lCurrentYear = COleDateTime::GetCurrentTime().GetYear();
					CString sCurrentYear;
					sCurrentYear.Format("%li", lCurrentYear);

					// Prendo gli esami dal 01/01 al 31/12 dell'anno in corso
					CCustomDate dateFrom(lCurrentYear, 1, 1, 0, 0, 0);
					CCustomDate dateTo(lCurrentYear, 12, 31, 0, 23, 59);

					CString sQuery;

					// Sandro 14/01/2014 // RAS 20140006 //
					if (theApp.m_bMostraNumeroEsamiPerSede)
						sQuery.Format("SELECT COUNT(*) AS CONTEGGIO FROM EESAMI WHERE DATA>=%li AND DATA<=%li AND IDSedeEsame=%li AND UO=%li AND ELIMINATO=0", dateFrom.GetDate(), dateTo.GetDate(), theApp.m_lIDSedeEsameDefault, theApp.m_lUO);
					else
						sQuery.Format("SELECT COUNT(*) AS CONTEGGIO FROM EESAMI WHERE DATA>=%li AND DATA<=%li AND UO=%li AND ELIMINATO=0", dateFrom.GetDate(), dateTo.GetDate(), theApp.m_lUO);

					CString sNumEsami = "";
					try
					{
						CRecordset setCount(&theApp.m_dbEndox);

						setCount.Open(CRecordset::snapshot, sQuery, CRecordset::readOnly);
						setCount.GetFieldValue("CONTEGGIO", sNumEsami);
						setCount.Close();
					}
					catch (CDBException* pEx)
					{
						pEx->Delete();
					}

					if (sNumEsami.IsEmpty())
						SetDlgItemText(IDC_LABEL_STATO_NEW3, "");
					else
						SetDlgItemText(IDC_LABEL_STATO_NEW3, sNumEsami + " " + theApp.GetMessageString(IDS_ESAMIVIEW_ESAMIEFF) + " " + sCurrentYear);
				}
				else
				{
					SetDlgItemText(IDC_LABEL_STATO_NEW2, CTipoEsameSet().GetDescrizione(m_pEsamiSet->m_lIDEsame));

					if (m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lData))
					{
						SetDlgItemText(IDC_LABEL_STATO_NEW3, "");
					}
					else
					{
						CCustomDate dateEsame(m_pEsamiSet->m_lData);
						SetDlgItemText(IDC_LABEL_STATO_NEW3, theApp.GetMessageString(IDS_DEL) + " " + dateEsame.GetDate("%d/%m/%Y"));
					}
				}
			}
			else
			{
				// Sandro 07/12/2015 // RIMA 15135 //

				if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lData))
					SetDlgItemText(IDC_LABEL_STATO_NEW2, CTipoEsameSet().GetSigla(m_pEsamiSet->m_lIDEsame) + " " + theApp.GetMessageString(IDS_DEL) + " " + CCustomDate(m_pEsamiSet->m_lData).GetDate("%d/%m/%Y"));
				else
					SetDlgItemText(IDC_LABEL_STATO_NEW2, CTipoEsameSet().GetSigla(m_pEsamiSet->m_lIDEsame));

				SetDlgItemText(IDC_LABEL_STATO_NEW3, theApp.m_sPassedDescription);
			}

			/* Segnalazione del blocco automatico del referto */
			GetDlgItem(IDC_LABEL_STATO_NEW1)->ShowWindow(SW_HIDE);
			if (theApp.m_lBloccoReferto > 0)
			{
				if (!m_pEsamiSet->m_bLocked && !m_pEsamiSet->m_bSuperLocked && !m_pEsamiSet->IsRefertoUpdatable())
				{
					SetDlgItemText(IDC_LABEL_STATO_NEW1, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_365));
					GetDlgItem(IDC_LABEL_STATO_NEW1)->ShowWindow(SW_SHOW);
				}
			}

			break;
		}
		case PRG_IMAGENT:
		{
			GetDlgItem(IDC_LABEL_STATO_NEW1)->ShowWindow(SW_HIDE);

			SetDlgItemText(IDC_LABEL_STATO_NEW2, theApp.GetMessageString(IDS_IMAGENT_TAB_1));

			if (m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lData))
			{
				SetDlgItemText(IDC_LABEL_STATO_NEW3, "");
			}
			else
			{
				CCustomDate dateEsame(m_pEsamiSet->m_lData);
				SetDlgItemText(IDC_LABEL_STATO_NEW3, theApp.GetMessageString(IDS_DEL) + " " + dateEsame.GetDate("%d/%m/%Y"));
			}
			break;
		}
		}
	}
	else
	{
		SetDlgItemText(IDC_LABEL_STATO_NEW1, "");
		SetDlgItemText(IDC_LABEL_STATO_NEW2, "");
		SetDlgItemText(IDC_LABEL_STATO_NEW3, "");
	}

	// indicazione della UO //
	if (theApp.m_bUOVisualizzaAngoloAltoDestra)
		SetDlgItemText(IDC_LABEL_STATO_NEW4, CUOSet().GetDescrizione(theApp.m_lUO));
	else
		SetDlgItemText(IDC_LABEL_STATO_NEW4, "");

	DDX_Control(pDX, IDC_STATIC_FRAMESTATO, m_ctrlStaticFrameStato);
	DDX_Control(pDX, IDC_PROGRESS_IMPORT, m_ctrlProgressImport);

	// Sandro 07/03/2013 // paziente del direttore mi impone di ridisegnare le static per aggiornare il colore (da nero a rosso e viceversa) //
	GetDlgItem(IDC_LABEL_PAZIENTE_01)->RedrawWindow();
	GetDlgItem(IDC_LABEL_PAZIENTE_02)->RedrawWindow();
	GetDlgItem(IDC_LABEL_PAZIENTE_03)->RedrawWindow();
	GetDlgItem(IDC_LABEL_PAZIENTE_04)->RedrawWindow();
	GetDlgItem(IDC_LABEL_PAZIENTE_05)->RedrawWindow();
	GetDlgItem(IDC_LABEL_PAZIENTE_06)->RedrawWindow();
	GetDlgItem(IDC_LABEL_PAZIENTE_07)->RedrawWindow();
	GetDlgItem(IDC_LABEL_PAZIENTE_08)->RedrawWindow();
	GetDlgItem(IDC_PAZIENTE_FISCALE)->RedrawWindow();
	GetDlgItem(IDC_PAZIENTE_SANITARIO)->RedrawWindow();
	GetDlgItem(IDC_PAZIENTE_COGNOME)->RedrawWindow();
	GetDlgItem(IDC_PAZIENTE_NOME)->RedrawWindow();
	GetDlgItem(IDC_PAZIENTE_SESSO)->RedrawWindow();
	GetDlgItem(IDC_PAZIENTE_TELEFONO)->RedrawWindow();
	GetDlgItem(IDC_PAZIENTE_NATOIL)->RedrawWindow();
	GetDlgItem(IDC_PAZIENTE_NATOA)->RedrawWindow();

	// Sandro 17/07/2015 //
	DDX_Control(pDX, IDC_TEXTCONTROL, m_ctrlTextControlView);
	m_ctrlTextControlView.SendMessage(WM_USER + 1013, 1, 0); // così NON carica i font dalla stampante predefinita perché in certi casi dava RTF filter error... //

}

void CEsamiView::UpdateFrameStato()
{
	CRect rectFrameStato = CRect(0, 0, 0, 0);
	if (::IsWindow(m_ctrlStaticFrameStato))
	{
		m_ctrlStaticFrameStato.GetWindowRect(rectFrameStato);
		ScreenToClient(rectFrameStato);
	}

	if (theApp.m_nProgramMode == NOTHING_MODE)
	{
		SetReadOnly(TRUE);

		//Julio BUG 3456 - Contingencia
		if (theApp.m_bContingencia)
		{
			theApp.m_colorStato = RGB(255, 255, 255);	 // WHITE
			theApp.m_colorStatoSfondo = RGB(209, 0, 0);  // RED
			SetDlgItemText(IDC_LABEL_STATO, theApp.GetMessageString(IDS_NOMEPROGRAMMA_CONTINGENZA));
		}
		else if (m_lStreamingState > 0) //
		{
			switch (m_lStreamingState)
			{
			case StreamingStatus::enabled:
			{
				theApp.m_colorStato = theApp.m_colorStreamingAttivo;
				theApp.m_colorStatoSfondo = theApp.m_colorStreamingAttivoSfondo;
				SetDlgItemText(IDC_LABEL_STATO, theApp.GetMessageString(IDS_ESAMIVIEW_STATE_14));
				break;
			}
			case StreamingStatus::connected:
			{
				theApp.m_colorStato = theApp.m_colorStreamingConnesso;
				theApp.m_colorStatoSfondo = theApp.m_colorStreamingConnessoSfondo;
				SetDlgItemText(IDC_LABEL_STATO, theApp.GetMessageString(IDS_ESAMIVIEW_STATE_15));
				break;
			}
			default:
				break;
			}
		}
		else
		{
			if (m_bMonitoraggioAttivo == TRUE)
			{
				theApp.m_colorStato = RGB(255, 255, 255);		// WHITE	
				theApp.m_colorStatoSfondo = RGB(100, 100, 100); // GRAY
				SetDlgItemText(IDC_LABEL_STATO, theApp.GetMessageString(IDS_ESAMIVIEW_STATE_16));
			}
			else
			{
				if (m_pEsamiSet->m_bFirmato == TRUE) // Sandro 19/11/2013 // confronto con TRUE, e non per sbaglio //
				{
					theApp.m_colorStato = theApp.m_colorVisualizzazioneFirmato;
					theApp.m_colorStatoSfondo = theApp.m_colorVisualizzazioneFirmatoSfondo;
					SetDlgItemText(IDC_LABEL_STATO, theApp.GetMessageString(IDS_ESAMIVIEW_STATE_9));
				}
				else
				{
					if (theApp.m_enumFirmaDigitale != CEndoxApp::sign_disabled)
					{
						theApp.m_colorStato = theApp.m_colorVisualizzazioneAperto;
						theApp.m_colorStatoSfondo = theApp.m_colorVisualizzazioneApertoSfondo;
						SetDlgItemText(IDC_LABEL_STATO, theApp.GetMessageString(IDS_ESAMIVIEW_STATE_10));
					}
					else
					{
						//Julio 28/11/2017 Centralizacao
						if (m_pEsamiSet->m_sFleuryTrasferito.IsEmpty() || m_pEsamiSet->m_sFleuryTrasferito == "-1")
						{
							if (m_pEsamiSet->m_bSuperLocked == TRUE) // Sandro 19/11/2013 // confronto con TRUE, e non per sbaglio //
							{
								theApp.m_colorStato = theApp.m_colorVisualizzazioneChiuso;
								theApp.m_colorStatoSfondo = theApp.m_colorVisualizzazioneChiusoSfondo;

								if (m_pEsamiSet->m_lStatoInvioCentraleRefertaz > 0)
									SetDlgItemText(IDC_LABEL_STATO, theApp.GetMessageString(IDS_ESAMIVIEW_STATE_17));
								//Gabriel - TCP
								else if (m_pEsamiSet->m_lStatoInvioAltraUnita > 0 && theApp.m_bAtivaTCP)
									SetDlgItemText(IDC_LABEL_STATO, theApp.GetMessageString(IDS_ESAMIVIEW_STATE_18));
								else
									SetDlgItemText(IDC_LABEL_STATO, theApp.GetMessageString(IDS_ESAMIVIEW_STATE_11));
							}
							else
							{
								theApp.m_colorStato = theApp.m_colorVisualizzazioneAperto;
								theApp.m_colorStatoSfondo = theApp.m_colorVisualizzazioneApertoSfondo;
								SetDlgItemText(IDC_LABEL_STATO, theApp.GetMessageString(IDS_ESAMIVIEW_STATE_1));
							}
						}
						else
						{
							theApp.m_colorStato = RGB(255, 255, 255);	// WHITE
							theApp.m_colorStatoSfondo = RGB(139, 0, 0);	// DARK RED

							CString sErrore, sServer, sUO, sEndpointRemoteCommunication;
							CString sFicha = m_pEsamiSet->m_sCodEsame;
							CString sLabel;
							if (FleuryCercaFicha(sFicha, sErrore, sServer, sUO, sEndpointRemoteCommunication))
							{
								sLabel.Format("EXAME NA UNIDADE %s", sServer);
								if (m_pEsamiSet->m_sFleuryTrasferito != sServer || m_pEsamiSet->m_sFleuryEndpointRemoto != sEndpointRemoteCommunication)
								{
									m_pEsamiSet->m_sFleuryTrasferito = sServer;
									m_pEsamiSet->m_sFleuryEndpointRemoto = sEndpointRemoteCommunication;
									m_pEsamiSet->UpdateRecordset("CEsamiView::UpdateFrameStato");
								}
							}
							else
							{
								sLabel.Format("EXAME NA UNIDADE %s", m_pEsamiSet->m_sFleuryTrasferito);
							}


							SetDlgItemText(IDC_LABEL_STATO, sLabel);

						}
						//
					}
				}
			}
		}

		//Marvel BUG 4014 Parte 5 - Reclassificacao Variantes | Exibir exame flagado
		if (m_pEsamiSet->m_setEP.m_sTesto093.MakeUpper() == "RECLASSIFICACAO VARIANTES")
		{
			theApp.m_colorStato = RGB(0, 0, 0);				// BLACK
			theApp.m_colorStatoSfondo = RGB(153, 153, 255);	// LIGHT PURPLE
			SetDlgItemText(IDC_LABEL_STATO, theApp.GetMessageString(IDS_STATO_GENOMICA_VARIANTE_RECLASSIFICATA));
		}

		m_brushSfondoStato.DeleteObject();
		m_brushSfondoStato.CreateSolidBrush(theApp.m_colorStatoSfondo);

		InvalidateRect(rectFrameStato, FALSE);
	}
	else
	{
		if (m_lStreamingState > 0)
		{
			switch (m_lStreamingState)
			{
			case StreamingStatus::enabled:
			{
				theApp.m_colorStato = theApp.m_colorStreamingAttivo;
				theApp.m_colorStatoSfondo = theApp.m_colorStreamingAttivoSfondo;
				SetDlgItemText(IDC_LABEL_STATO, theApp.GetMessageString(IDS_ESAMIVIEW_STATE_14));
				break;
			}
			case StreamingStatus::connected:
			{
				theApp.m_colorStato = theApp.m_colorStreamingConnesso;
				theApp.m_colorStatoSfondo = theApp.m_colorStreamingConnessoSfondo;
				SetDlgItemText(IDC_LABEL_STATO, theApp.GetMessageString(IDS_ESAMIVIEW_STATE_15));
				break;
			}
			default:
				break;
			}
		}
		else
		{
			if (m_bMonitoraggioAttivo == TRUE)
			{
				theApp.m_colorStato = RGB(255, 255, 255);		// WHITE
				theApp.m_colorStatoSfondo = RGB(100, 100, 100);	// GRAY
				SetDlgItemText(IDC_LABEL_STATO, theApp.GetMessageString(IDS_ESAMIVIEW_STATE_16));

				m_brushSfondoStato.DeleteObject();
				m_brushSfondoStato.CreateSolidBrush(theApp.m_colorStatoSfondo);

				InvalidateRect(rectFrameStato, FALSE);
			}
			else
			{
				if (theApp.m_nProgramMode & ADD_RECORD_PAZIENTI)
				{
					theApp.m_colorStato = theApp.m_colorAggiuntaPaziente;
					theApp.m_colorStatoSfondo = theApp.m_colorAggiuntaPazienteSfondo;

					m_brushSfondoStato.DeleteObject();
					m_brushSfondoStato.CreateSolidBrush(theApp.m_colorStatoSfondo);

					InvalidateRect(rectFrameStato, FALSE);

					SetDlgItemText(IDC_LABEL_STATO, theApp.GetMessageString(IDS_ESAMIVIEW_STATE_2));
				}
				else if (theApp.m_nProgramMode & MODIFY_RECORD_PAZIENTI)
				{
					theApp.m_colorStato = theApp.m_colorModificaPaziente;
					theApp.m_colorStatoSfondo = theApp.m_colorModificaPazienteSfondo;

					m_brushSfondoStato.DeleteObject();
					m_brushSfondoStato.CreateSolidBrush(theApp.m_colorStatoSfondo);

					InvalidateRect(rectFrameStato, FALSE);

					SetDlgItemText(IDC_LABEL_STATO, theApp.GetMessageString(IDS_ESAMIVIEW_STATE_3));
				}
				else if (theApp.m_nProgramMode & ADD_RECORD_ESAMI)
				{
					SetReadOnly(FALSE);

					theApp.m_colorStato = theApp.m_colorAggiuntaEsame;
					theApp.m_colorStatoSfondo = theApp.m_colorAggiuntaEsameSfondo;

					m_brushSfondoStato.DeleteObject();
					m_brushSfondoStato.CreateSolidBrush(theApp.m_colorStatoSfondo);

					InvalidateRect(rectFrameStato, FALSE);

					SetDlgItemText(IDC_LABEL_STATO, theApp.GetMessageString(IDS_ESAMIVIEW_STATE_4));
				}
				else if (theApp.m_nProgramMode & MODIFY_RECORD_ESAMI)
				{
					SetReadOnly(FALSE);

					theApp.m_colorStato = theApp.m_colorModificaEsame;
					theApp.m_colorStatoSfondo = theApp.m_colorModificaEsameSfondo;

					m_brushSfondoStato.DeleteObject();
					m_brushSfondoStato.CreateSolidBrush(theApp.m_colorStatoSfondo);

					InvalidateRect(rectFrameStato, FALSE);

					SetDlgItemText(IDC_LABEL_STATO, theApp.GetMessageString(IDS_ESAMIVIEW_STATE_5));
				}
				else if (theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI)
				{
					if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
					{
						SetReadOnly(FALSE);

						theApp.m_colorStato = theApp.m_colorRicercaEsame;
						theApp.m_colorStatoSfondo = theApp.m_colorRicercaEsameSfondo;

						m_brushSfondoStato.DeleteObject();
						m_brushSfondoStato.CreateSolidBrush(theApp.m_colorStatoSfondo);

						InvalidateRect(rectFrameStato, FALSE);

						SetDlgItemText(IDC_LABEL_STATO, theApp.GetMessageString(IDS_ESAMIVIEW_STATE_6));
					}
					else
					{
						theApp.m_colorStato = theApp.m_colorRicercaPaziente;
						theApp.m_colorStatoSfondo = theApp.m_colorRicercaPazienteSfondo;

						m_brushSfondoStato.DeleteObject();
						m_brushSfondoStato.CreateSolidBrush(theApp.m_colorStatoSfondo);

						InvalidateRect(rectFrameStato, FALSE);

						SetDlgItemText(IDC_LABEL_STATO, theApp.GetMessageString(IDS_ESAMIVIEW_STATE_7));
					}
				}
				else if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				{
					SetReadOnly(FALSE);

					theApp.m_colorStato = theApp.m_colorRicercaEsame;
					theApp.m_colorStatoSfondo = theApp.m_colorRicercaEsameSfondo;

					m_brushSfondoStato.DeleteObject();
					m_brushSfondoStato.CreateSolidBrush(theApp.m_colorStatoSfondo);

					InvalidateRect(rectFrameStato, FALSE);

					SetDlgItemText(IDC_LABEL_STATO, theApp.GetMessageString(IDS_ESAMIVIEW_STATE_8));
				}
			}
		}
	}
}

void CEsamiView::AssociaRecordset()
{
	m_pPazientiSet = &((CEsamiDoc*)m_pDocument)->m_PazientiSet;
	m_pPazientiSet->SetBaseFilter("");
	/* if (theApp.m_bPazientiUsaVista)
	m_pPazientiSet->SetSortRecord(theApp.m_sPazientiVistaOrdinamento);
	else */
	m_pPazientiSet->SetSortRecord("Contatore");
	theApp.m_pSetPazienti = m_pPazientiSet;

	m_pEsamiSet = &((CEsamiDoc*)m_pDocument)->m_EsamiSet;
	m_pEsamiSet->SetBaseFilter(""); // riaggiorna il filtro con la UO attuale //
	m_pEsamiSet->SetSortRecord("Paziente, Data, Contatore");
	theApp.m_pSetEsami = m_pEsamiSet;
}

void CEsamiView::LeggiEtichette()
{
	CComboConfigSet setComboConfig;
	CEtichetteSet setEtichette;

	//

	setEtichette.SetOpenFilter("Tipo = 'TEXT_ANAM'");
	if (setEtichette.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setEtichette.IsEOF())
		{
			if ((setEtichette.m_lIndice >= 0) && (setEtichette.m_lIndice < NUM_FIELD_ANAM))
				theApp.m_sAnamText[setEtichette.m_lIndice] = setEtichette.m_sLabel;

			setEtichette.MoveNext();
		}
		setEtichette.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setEtichette.SetOpenFilter("Tipo = 'TESTO'");
	if (setEtichette.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setEtichette.IsEOF())
		{
			if ((setEtichette.m_lIndice >= 0) && (setEtichette.m_lIndice < NUM_LABEL_TESTO))
			{
				theApp.m_sLabelText[setEtichette.m_lIndice] = setEtichette.m_sLabel;
				theApp.m_lIdCampoRelazionato[setEtichette.m_lIndice] = setEtichette.m_lIdCampoRelazionato;
			}

			setEtichette.MoveNext();
		}
		setEtichette.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setEtichette.SetOpenFilter("Tipo = 'TESTO_RTF'");
	if (setEtichette.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setEtichette.IsEOF())
		{
			if ((setEtichette.m_lIndice >= 0) && (setEtichette.m_lIndice < NUM_LABEL_TESTO_RTF))
			{
				theApp.m_sLabelTextRtf[setEtichette.m_lIndice] = setEtichette.m_sLabel;
				theApp.m_lIdCampoRelazionatoRtf[setEtichette.m_lIndice] = setEtichette.m_lIdCampoRelazionato;
			}

			setEtichette.MoveNext();
		}
		setEtichette.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setEtichette.SetOpenFilter("Tipo = 'TESTO_CL'");
	if (setEtichette.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setEtichette.IsEOF())
		{
			if ((setEtichette.m_lIndice >= 0) && (setEtichette.m_lIndice < NUM_LABEL_TESTO_CL))
				theApp.m_sLabelTextCL[setEtichette.m_lIndice] = setEtichette.m_sLabel;

			setEtichette.MoveNext();
		}
		setEtichette.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setEtichette.SetOpenFilter("Tipo = 'DATAORA_TESTO'");
	if (setEtichette.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setEtichette.IsEOF())
		{
			if ((setEtichette.m_lIndice >= 0) && (setEtichette.m_lIndice < NUM_LABEL_DATAORA))
				theApp.m_sLabelDate[setEtichette.m_lIndice] = setEtichette.m_sLabel;

			setEtichette.MoveNext();
		}
		setEtichette.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setEtichette.SetOpenFilter("Tipo = 'TASTI_STAMPA_TESTO'");
	if (setEtichette.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setEtichette.IsEOF())
		{
			if ((setEtichette.m_lIndice >= 0) && (setEtichette.m_lIndice < NUM_LABEL_TASTO_STAMPA))
				theApp.m_sLabelTastoStampa[setEtichette.m_lIndice] = setEtichette.m_sLabel;

			setEtichette.MoveNext();
		}
		setEtichette.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setEtichette.SetOpenFilter("Tipo = 'TASTI_BROWSER_TESTO'");
	if (setEtichette.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setEtichette.IsEOF())
		{
			if ((setEtichette.m_lIndice >= 0) && (setEtichette.m_lIndice < NUM_LABEL_TASTO_BROWSER))
				theApp.m_sLabelTastoBrowser[setEtichette.m_lIndice] = setEtichette.m_sLabel;

			setEtichette.MoveNext();
		}
		setEtichette.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setEtichette.SetOpenFilter("Tipo = 'TASTI_ESEGUIBILE_TESTO'");
	if (setEtichette.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setEtichette.IsEOF())
		{
			if ((setEtichette.m_lIndice >= 0) && (setEtichette.m_lIndice < NUM_LABEL_TASTO_EXEC))
				theApp.m_sLabelTastoEseguibile[setEtichette.m_lIndice] = setEtichette.m_sLabel;

			setEtichette.MoveNext();
		}
		setEtichette.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setComboConfig.SetOpenFilter("Configurazione = 'ACTIVE'");
	if (setComboConfig.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setComboConfig.IsEOF())
		{
			if ((setComboConfig.m_lTabella >= 0) && (setComboConfig.m_lTabella < NUM_LABEL_TESTO))
				theApp.m_bComboActive[setComboConfig.m_lTabella] = setComboConfig.m_lParametroNum;

			setComboConfig.MoveNext();
		}
		setComboConfig.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setComboConfig.SetOpenFilter("Configurazione = 'MULTIPLESEL'");
	if (setComboConfig.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setComboConfig.IsEOF())
		{
			if ((setComboConfig.m_lTabella >= 0) && (setComboConfig.m_lTabella < NUM_LABEL_TESTO))
				theApp.m_bComboMultipleSel[setComboConfig.m_lTabella] = setComboConfig.m_lParametroNum;

			setComboConfig.MoveNext();
		}
		setComboConfig.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setComboConfig.SetOpenFilter("Configurazione = 'SINGLELINE'");
	if (setComboConfig.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setComboConfig.IsEOF())
		{
			if ((setComboConfig.m_lTabella >= 0) && (setComboConfig.m_lTabella < NUM_LABEL_TESTO))
				theApp.m_bComboSingleLine[setComboConfig.m_lTabella] = setComboConfig.m_lParametroNum;

			setComboConfig.MoveNext();
		}
		setComboConfig.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setComboConfig.SetOpenFilter("Configurazione = 'UPPERCASE'");
	if (setComboConfig.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setComboConfig.IsEOF())
		{
			if ((setComboConfig.m_lTabella >= 0) && (setComboConfig.m_lTabella < NUM_LABEL_TESTO))
				theApp.m_bComboUppercase[setComboConfig.m_lTabella] = setComboConfig.m_lParametroNum;

			setComboConfig.MoveNext();
		}
		setComboConfig.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setComboConfig.SetOpenFilter("Configurazione = 'NUMERIC'");
	if (setComboConfig.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setComboConfig.IsEOF())
		{
			if ((setComboConfig.m_lTabella >= 0) && (setComboConfig.m_lTabella < NUM_LABEL_TESTO))
				theApp.m_bComboNumerico[setComboConfig.m_lTabella] = setComboConfig.m_lParametroNum;

			setComboConfig.MoveNext();
		}
		setComboConfig.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setComboConfig.SetOpenFilter("Configurazione = 'COPY'");
	if (setComboConfig.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setComboConfig.IsEOF())
		{
			if ((setComboConfig.m_lTabella >= 0) && (setComboConfig.m_lTabella < NUM_LABEL_TESTO))
				theApp.m_bCopy[setComboConfig.m_lTabella] = setComboConfig.m_lParametroNum;

			setComboConfig.MoveNext();
		}
		setComboConfig.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setComboConfig.SetOpenFilter("Configurazione = 'COPY_RTF'");
	if (setComboConfig.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setComboConfig.IsEOF())
		{
			if ((setComboConfig.m_lTabella >= 0) && (setComboConfig.m_lTabella < NUM_LABEL_TESTO_RTF))
				theApp.m_bCopyRtf[setComboConfig.m_lTabella] = setComboConfig.m_lParametroNum;

			setComboConfig.MoveNext();
		}
		setComboConfig.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setComboConfig.SetOpenFilter("Configurazione = 'COPY_CL'");
	if (setComboConfig.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setComboConfig.IsEOF())
		{
			if ((setComboConfig.m_lTabella >= 0) && (setComboConfig.m_lTabella < NUM_LABEL_TESTO_CL))
				theApp.m_bCopyCL[setComboConfig.m_lTabella] = setComboConfig.m_lParametroNum;

			setComboConfig.MoveNext();
		}
		setComboConfig.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setComboConfig.SetOpenFilter("Configurazione = 'COPY_DATE'");
	if (setComboConfig.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setComboConfig.IsEOF())
		{
			if ((setComboConfig.m_lTabella >= 0) && (setComboConfig.m_lTabella < NUM_LABEL_DATAORA))
				theApp.m_bCopyDate[setComboConfig.m_lTabella] = setComboConfig.m_lParametroNum;

			setComboConfig.MoveNext();
		}
		setComboConfig.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setComboConfig.SetOpenFilter("Configurazione = 'ALARM_CL'");
	if (setComboConfig.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setComboConfig.IsEOF())
		{
			if ((setComboConfig.m_lTabella >= 0) && (setComboConfig.m_lTabella < NUM_LABEL_TESTO_CL))
				theApp.m_bAlarmCL[setComboConfig.m_lTabella] = setComboConfig.m_lParametroNum;

			setComboConfig.MoveNext();
		}
		setComboConfig.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setComboConfig.SetOpenFilter("Configurazione = 'PAROLECHIAVE_CL'");
	if (setComboConfig.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setComboConfig.IsEOF())
		{
			if ((setComboConfig.m_lTabella >= 0) && (setComboConfig.m_lTabella < NUM_LABEL_TESTO_CL))
				theApp.m_sParoleChiaveCL[setComboConfig.m_lTabella] = setComboConfig.m_sParametroStr;

			setComboConfig.MoveNext();
		}
		setComboConfig.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setComboConfig.SetOpenFilter("Configurazione = 'DATAORA_TIPO'");
	if (setComboConfig.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setComboConfig.IsEOF())
		{
			if ((setComboConfig.m_lTabella >= 0) && (setComboConfig.m_lTabella < NUM_LABEL_DATAORA))
				theApp.m_iRadioDate[setComboConfig.m_lTabella] = setComboConfig.m_lParametroNum;

			setComboConfig.MoveNext();
		}
		setComboConfig.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setComboConfig.SetOpenFilter("Configurazione = 'TASTOSTAMPA_FILE'");
	if (setComboConfig.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setComboConfig.IsEOF())
		{
			if ((setComboConfig.m_lTabella >= 0) && (setComboConfig.m_lTabella < NUM_LABEL_TASTO_STAMPA))
				theApp.m_sTastoStampaFile[setComboConfig.m_lTabella] = setComboConfig.m_sParametroStr;

			setComboConfig.MoveNext();
		}
		setComboConfig.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setComboConfig.SetOpenFilter("Configurazione = 'TASTOSTAMPA_CHECK'");
	if (setComboConfig.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setComboConfig.IsEOF())
		{
			if ((setComboConfig.m_lTabella >= 0) && (setComboConfig.m_lTabella < NUM_LABEL_TASTO_STAMPA))
				theApp.m_bTastoStampaCheck[setComboConfig.m_lTabella] = setComboConfig.m_lParametroNum;

			setComboConfig.MoveNext();
		}
		setComboConfig.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setComboConfig.SetOpenFilter("Configurazione = 'TASTOBROWSER_INDIRIZZO'");
	if (setComboConfig.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setComboConfig.IsEOF())
		{
			if ((setComboConfig.m_lTabella >= 0) && (setComboConfig.m_lTabella < NUM_LABEL_TASTO_BROWSER))
				theApp.m_sTastoBrowserIndirizzo[setComboConfig.m_lTabella] = setComboConfig.m_sParametroStr;

			setComboConfig.MoveNext();
		}
		setComboConfig.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setComboConfig.SetOpenFilter("Configurazione = 'TASTOESEGUIBILE_FILE'");
	if (setComboConfig.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setComboConfig.IsEOF())
		{
			if ((setComboConfig.m_lTabella >= 0) && (setComboConfig.m_lTabella < NUM_LABEL_TASTO_EXEC))
				theApp.m_sTastoEseguibileFile[setComboConfig.m_lTabella] = setComboConfig.m_sParametroStr;

			setComboConfig.MoveNext();
		}
		setComboConfig.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setComboConfig.SetOpenFilter("Configurazione = 'VISI_ANAM'");
	if (setComboConfig.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setComboConfig.IsEOF())
		{
			if ((setComboConfig.m_lTabella >= 0) && (setComboConfig.m_lTabella < NUM_FIELD_ANAM))
				theApp.m_bAnamVisi[setComboConfig.m_lTabella] = setComboConfig.m_lParametroNum;

			setComboConfig.MoveNext();
		}
		setComboConfig.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setComboConfig.SetOpenFilter("Configurazione = 'AUTO_ANAM'");
	if (setComboConfig.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setComboConfig.IsEOF())
		{
			if ((setComboConfig.m_lTabella >= 0) && (setComboConfig.m_lTabella < NUM_FIELD_ANAM))
				theApp.m_bAnamAuto[setComboConfig.m_lTabella] = setComboConfig.m_lParametroNum;

			setComboConfig.MoveNext();
		}
		setComboConfig.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setEtichette.SetOpenFilter("Tipo = 'ETICHETTA'");
	if (setEtichette.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setEtichette.IsEOF())
		{
			if ((setEtichette.m_lIndice >= 0) && (setEtichette.m_lIndice < NUM_LABEL_ETICHETTE))
				theApp.m_sLabelTextEtichette[setEtichette.m_lIndice] = setEtichette.m_sLabel;

			setEtichette.MoveNext();
		}
		setEtichette.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setEtichette.SetOpenFilter("Tipo = 'TASTOCHIUSURAFASE'");
	if (setEtichette.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setEtichette.IsEOF())
		{
			if ((setEtichette.m_lIndice >= 0) && (setEtichette.m_lIndice < NUM_LABEL_TASTO_CHIUSURAFASE))
				theApp.m_sLabelTastoChiusuraFase[setEtichette.m_lIndice] = setEtichette.m_sLabel;

			setEtichette.MoveNext();
		}
		setEtichette.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	setComboConfig.SetOpenFilter("Configurazione = 'TASTOCHIUSURAFASE_IDFASE'");
	if (setComboConfig.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setComboConfig.IsEOF())
		{
			if ((setComboConfig.m_lTabella >= 0) && (setComboConfig.m_lTabella < NUM_LABEL_TASTO_CHIUSURAFASE))
				theApp.m_lIdFaseTastoChiusuraFase[setComboConfig.m_lTabella] = setComboConfig.m_lParametroNum;

			setComboConfig.MoveNext();
		}
		setComboConfig.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	setEtichette.SetOpenFilter("Tipo = 'GRIDCL'");
	if (setEtichette.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setEtichette.IsEOF())
		{
			if ((setEtichette.m_lIndice >= 0) && (setEtichette.m_lIndice < NUM_LABEL_GRIDCL))
			{
				theApp.m_sLabelTextGridCL[setEtichette.m_lIndice] = setEtichette.m_sLabel;

				//Per ogni griglia devo caricare la lista dei gruppi associati
				CString sFilter;
				sFilter.Format("IDETICHETTA_GRIDCL=%li", setEtichette.m_lContatore);
				CEndoGridCLGruppiUtenteSet CLGruppiSet;
				CLGruppiSet.SetOpenFilter(sFilter);

				if (CLGruppiSet.OpenRecordset("CEsamiView::LeggiEtichette"))
				{
					while (!CLGruppiSet.IsEOF())
					{
						theApp.m_listGridCLGruppiAssociati[setEtichette.m_lIndice].AddTail(CLGruppiSet.m_lIDGruppo);

						CLGruppiSet.MoveNext();
					}

					CLGruppiSet.CloseRecordset("CEsamiView::LeggiEtichette");
				}
			}

			setEtichette.MoveNext();
		}
		setEtichette.CloseRecordset("CEsamiView::LeggiEtichette");
	}

	//

	//
	//
	//

	CFieldDlg::m_strFieldEndox[anamnesi_fumo].sCombo = theApp.m_sAnamText[0];
	CFieldDlg::m_strFieldEndox[anamnesi_sigarette].sCombo = theApp.m_sAnamText[1];
	CFieldDlg::m_strFieldEndox[anamnesi_caffe].sCombo = theApp.m_sAnamText[2];
	CFieldDlg::m_strFieldEndox[anamnesi_alcol].sCombo = theApp.m_sAnamText[3];
	CFieldDlg::m_strFieldEndox[anamnesi_superalcolici].sCombo = theApp.m_sAnamText[4];
	CFieldDlg::m_strFieldEndox[anamnesi_farmaci].sCombo = theApp.m_sAnamText[5];
	CFieldDlg::m_strFieldEndox[anamnesi_assunzione].sCombo = theApp.m_sAnamText[6];
	CFieldDlg::m_strFieldEndox[anamnesi_peso].sCombo = theApp.m_sAnamText[7];
	CFieldDlg::m_strFieldEndox[anamnesi_altezza].sCombo = theApp.m_sAnamText[8];
	CFieldDlg::m_strFieldEndox[anamnesi_bmi].sCombo = theApp.m_sAnamText[9];
	CFieldDlg::m_strFieldEndox[anamnesi_bsa].sCombo = theApp.m_sAnamText[10];

	CFieldDlg::m_strFieldEndox[libero_000].sCombo = theApp.m_sLabelText[0];
	CFieldDlg::m_strFieldEndox[libero_001].sCombo = theApp.m_sLabelText[1];
	CFieldDlg::m_strFieldEndox[libero_002].sCombo = theApp.m_sLabelText[2];
	CFieldDlg::m_strFieldEndox[libero_003].sCombo = theApp.m_sLabelText[3];
	CFieldDlg::m_strFieldEndox[libero_004].sCombo = theApp.m_sLabelText[4];
	CFieldDlg::m_strFieldEndox[libero_005].sCombo = theApp.m_sLabelText[5];
	CFieldDlg::m_strFieldEndox[libero_006].sCombo = theApp.m_sLabelText[6];
	CFieldDlg::m_strFieldEndox[libero_007].sCombo = theApp.m_sLabelText[7];
	CFieldDlg::m_strFieldEndox[libero_008].sCombo = theApp.m_sLabelText[8];
	CFieldDlg::m_strFieldEndox[libero_009].sCombo = theApp.m_sLabelText[9];
	CFieldDlg::m_strFieldEndox[libero_010].sCombo = theApp.m_sLabelText[10];
	CFieldDlg::m_strFieldEndox[libero_011].sCombo = theApp.m_sLabelText[11];
	CFieldDlg::m_strFieldEndox[libero_012].sCombo = theApp.m_sLabelText[12];
	CFieldDlg::m_strFieldEndox[libero_013].sCombo = theApp.m_sLabelText[13];
	CFieldDlg::m_strFieldEndox[libero_014].sCombo = theApp.m_sLabelText[14];
	CFieldDlg::m_strFieldEndox[libero_015].sCombo = theApp.m_sLabelText[15];
	CFieldDlg::m_strFieldEndox[libero_016].sCombo = theApp.m_sLabelText[16];
	CFieldDlg::m_strFieldEndox[libero_017].sCombo = theApp.m_sLabelText[17];
	CFieldDlg::m_strFieldEndox[libero_018].sCombo = theApp.m_sLabelText[18];
	CFieldDlg::m_strFieldEndox[libero_019].sCombo = theApp.m_sLabelText[19];
	CFieldDlg::m_strFieldEndox[libero_020].sCombo = theApp.m_sLabelText[20];
	CFieldDlg::m_strFieldEndox[libero_021].sCombo = theApp.m_sLabelText[21];
	CFieldDlg::m_strFieldEndox[libero_022].sCombo = theApp.m_sLabelText[22];
	CFieldDlg::m_strFieldEndox[libero_023].sCombo = theApp.m_sLabelText[23];
	CFieldDlg::m_strFieldEndox[libero_024].sCombo = theApp.m_sLabelText[24];
	CFieldDlg::m_strFieldEndox[libero_025].sCombo = theApp.m_sLabelText[25];
	CFieldDlg::m_strFieldEndox[libero_026].sCombo = theApp.m_sLabelText[26];
	CFieldDlg::m_strFieldEndox[libero_027].sCombo = theApp.m_sLabelText[27];
	CFieldDlg::m_strFieldEndox[libero_028].sCombo = theApp.m_sLabelText[28];
	CFieldDlg::m_strFieldEndox[libero_029].sCombo = theApp.m_sLabelText[29];
	CFieldDlg::m_strFieldEndox[libero_030].sCombo = theApp.m_sLabelText[30];
	CFieldDlg::m_strFieldEndox[libero_031].sCombo = theApp.m_sLabelText[31];
	CFieldDlg::m_strFieldEndox[libero_032].sCombo = theApp.m_sLabelText[32];
	CFieldDlg::m_strFieldEndox[libero_033].sCombo = theApp.m_sLabelText[33];
	CFieldDlg::m_strFieldEndox[libero_034].sCombo = theApp.m_sLabelText[34];
	CFieldDlg::m_strFieldEndox[libero_035].sCombo = theApp.m_sLabelText[35];
	CFieldDlg::m_strFieldEndox[libero_036].sCombo = theApp.m_sLabelText[36];
	CFieldDlg::m_strFieldEndox[libero_037].sCombo = theApp.m_sLabelText[37];
	CFieldDlg::m_strFieldEndox[libero_038].sCombo = theApp.m_sLabelText[38];
	CFieldDlg::m_strFieldEndox[libero_039].sCombo = theApp.m_sLabelText[39];
	CFieldDlg::m_strFieldEndox[libero_040].sCombo = theApp.m_sLabelText[40];
	CFieldDlg::m_strFieldEndox[libero_041].sCombo = theApp.m_sLabelText[41];
	CFieldDlg::m_strFieldEndox[libero_042].sCombo = theApp.m_sLabelText[42];
	CFieldDlg::m_strFieldEndox[libero_043].sCombo = theApp.m_sLabelText[43];
	CFieldDlg::m_strFieldEndox[libero_044].sCombo = theApp.m_sLabelText[44];
	CFieldDlg::m_strFieldEndox[libero_045].sCombo = theApp.m_sLabelText[45];
	CFieldDlg::m_strFieldEndox[libero_046].sCombo = theApp.m_sLabelText[46];
	CFieldDlg::m_strFieldEndox[libero_047].sCombo = theApp.m_sLabelText[47];
	CFieldDlg::m_strFieldEndox[libero_048].sCombo = theApp.m_sLabelText[48];
	CFieldDlg::m_strFieldEndox[libero_049].sCombo = theApp.m_sLabelText[49];
	CFieldDlg::m_strFieldEndox[libero_050].sCombo = theApp.m_sLabelText[50];
	CFieldDlg::m_strFieldEndox[libero_051].sCombo = theApp.m_sLabelText[51];
	CFieldDlg::m_strFieldEndox[libero_052].sCombo = theApp.m_sLabelText[52];
	CFieldDlg::m_strFieldEndox[libero_053].sCombo = theApp.m_sLabelText[53];
	CFieldDlg::m_strFieldEndox[libero_054].sCombo = theApp.m_sLabelText[54];
	CFieldDlg::m_strFieldEndox[libero_055].sCombo = theApp.m_sLabelText[55];
	CFieldDlg::m_strFieldEndox[libero_056].sCombo = theApp.m_sLabelText[56];
	CFieldDlg::m_strFieldEndox[libero_057].sCombo = theApp.m_sLabelText[57];
	CFieldDlg::m_strFieldEndox[libero_058].sCombo = theApp.m_sLabelText[58];
	CFieldDlg::m_strFieldEndox[libero_059].sCombo = theApp.m_sLabelText[59];
	CFieldDlg::m_strFieldEndox[libero_060].sCombo = theApp.m_sLabelText[60];
	CFieldDlg::m_strFieldEndox[libero_061].sCombo = theApp.m_sLabelText[61];
	CFieldDlg::m_strFieldEndox[libero_062].sCombo = theApp.m_sLabelText[62];
	CFieldDlg::m_strFieldEndox[libero_063].sCombo = theApp.m_sLabelText[63];
	CFieldDlg::m_strFieldEndox[libero_064].sCombo = theApp.m_sLabelText[64];
	CFieldDlg::m_strFieldEndox[libero_065].sCombo = theApp.m_sLabelText[65];
	CFieldDlg::m_strFieldEndox[libero_066].sCombo = theApp.m_sLabelText[66];
	CFieldDlg::m_strFieldEndox[libero_067].sCombo = theApp.m_sLabelText[67];
	CFieldDlg::m_strFieldEndox[libero_068].sCombo = theApp.m_sLabelText[68];
	CFieldDlg::m_strFieldEndox[libero_069].sCombo = theApp.m_sLabelText[69];
	CFieldDlg::m_strFieldEndox[libero_070].sCombo = theApp.m_sLabelText[70];
	CFieldDlg::m_strFieldEndox[libero_071].sCombo = theApp.m_sLabelText[71];
	CFieldDlg::m_strFieldEndox[libero_072].sCombo = theApp.m_sLabelText[72];
	CFieldDlg::m_strFieldEndox[libero_073].sCombo = theApp.m_sLabelText[73];
	CFieldDlg::m_strFieldEndox[libero_074].sCombo = theApp.m_sLabelText[74];
	CFieldDlg::m_strFieldEndox[libero_075].sCombo = theApp.m_sLabelText[75];
	CFieldDlg::m_strFieldEndox[libero_076].sCombo = theApp.m_sLabelText[76];
	CFieldDlg::m_strFieldEndox[libero_077].sCombo = theApp.m_sLabelText[77];
	CFieldDlg::m_strFieldEndox[libero_078].sCombo = theApp.m_sLabelText[78];
	CFieldDlg::m_strFieldEndox[libero_079].sCombo = theApp.m_sLabelText[79];
	CFieldDlg::m_strFieldEndox[libero_080].sCombo = theApp.m_sLabelText[80];
	CFieldDlg::m_strFieldEndox[libero_081].sCombo = theApp.m_sLabelText[81];
	CFieldDlg::m_strFieldEndox[libero_082].sCombo = theApp.m_sLabelText[82];
	CFieldDlg::m_strFieldEndox[libero_083].sCombo = theApp.m_sLabelText[83];
	CFieldDlg::m_strFieldEndox[libero_084].sCombo = theApp.m_sLabelText[84];
	CFieldDlg::m_strFieldEndox[libero_085].sCombo = theApp.m_sLabelText[85];
	CFieldDlg::m_strFieldEndox[libero_086].sCombo = theApp.m_sLabelText[86];
	CFieldDlg::m_strFieldEndox[libero_087].sCombo = theApp.m_sLabelText[87];
	CFieldDlg::m_strFieldEndox[libero_088].sCombo = theApp.m_sLabelText[88];
	CFieldDlg::m_strFieldEndox[libero_089].sCombo = theApp.m_sLabelText[89];
	CFieldDlg::m_strFieldEndox[libero_090].sCombo = theApp.m_sLabelText[90];
	CFieldDlg::m_strFieldEndox[libero_091].sCombo = theApp.m_sLabelText[91];
	CFieldDlg::m_strFieldEndox[libero_092].sCombo = theApp.m_sLabelText[92];
	CFieldDlg::m_strFieldEndox[libero_093].sCombo = theApp.m_sLabelText[93];
	CFieldDlg::m_strFieldEndox[libero_094].sCombo = theApp.m_sLabelText[94];
	CFieldDlg::m_strFieldEndox[libero_095].sCombo = theApp.m_sLabelText[95];
	CFieldDlg::m_strFieldEndox[libero_096].sCombo = theApp.m_sLabelText[96];
	CFieldDlg::m_strFieldEndox[libero_097].sCombo = theApp.m_sLabelText[97];
	CFieldDlg::m_strFieldEndox[libero_098].sCombo = theApp.m_sLabelText[98];
	CFieldDlg::m_strFieldEndox[libero_099].sCombo = theApp.m_sLabelText[99];

	if (!theApp.m_sLabelTextRtf[0].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_rtf_000_fisso].sCombo = theApp.m_sLabelTextRtf[0] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_rtf_000_grande].sCombo = theApp.m_sLabelTextRtf[0] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextRtf[1].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_rtf_001_fisso].sCombo = theApp.m_sLabelTextRtf[1] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_rtf_001_grande].sCombo = theApp.m_sLabelTextRtf[1] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextRtf[2].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_rtf_002_fisso].sCombo = theApp.m_sLabelTextRtf[2] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_rtf_002_grande].sCombo = theApp.m_sLabelTextRtf[2] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextRtf[3].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_rtf_003_fisso].sCombo = theApp.m_sLabelTextRtf[3] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_rtf_003_grande].sCombo = theApp.m_sLabelTextRtf[3] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextRtf[4].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_rtf_004_fisso].sCombo = theApp.m_sLabelTextRtf[4] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_rtf_004_grande].sCombo = theApp.m_sLabelTextRtf[4] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextRtf[5].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_rtf_005_fisso].sCombo = theApp.m_sLabelTextRtf[5] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_rtf_005_grande].sCombo = theApp.m_sLabelTextRtf[5] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextRtf[6].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_rtf_006_fisso].sCombo = theApp.m_sLabelTextRtf[6] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_rtf_006_grande].sCombo = theApp.m_sLabelTextRtf[6] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextRtf[7].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_rtf_007_fisso].sCombo = theApp.m_sLabelTextRtf[7] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_rtf_007_grande].sCombo = theApp.m_sLabelTextRtf[7] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextRtf[8].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_rtf_008_fisso].sCombo = theApp.m_sLabelTextRtf[8] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_rtf_008_grande].sCombo = theApp.m_sLabelTextRtf[8] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextRtf[9].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_rtf_009_fisso].sCombo = theApp.m_sLabelTextRtf[9] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_rtf_009_grande].sCombo = theApp.m_sLabelTextRtf[9] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextRtf[10].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_rtf_010_fisso].sCombo = theApp.m_sLabelTextRtf[10] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_rtf_010_grande].sCombo = theApp.m_sLabelTextRtf[10] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextRtf[11].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_rtf_011_fisso].sCombo = theApp.m_sLabelTextRtf[11] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_rtf_011_grande].sCombo = theApp.m_sLabelTextRtf[11] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextRtf[12].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_rtf_012_fisso].sCombo = theApp.m_sLabelTextRtf[12] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_rtf_012_grande].sCombo = theApp.m_sLabelTextRtf[12] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextRtf[13].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_rtf_013_fisso].sCombo = theApp.m_sLabelTextRtf[13] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_rtf_013_grande].sCombo = theApp.m_sLabelTextRtf[13] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextRtf[14].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_rtf_014_fisso].sCombo = theApp.m_sLabelTextRtf[14] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_rtf_014_grande].sCombo = theApp.m_sLabelTextRtf[14] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextRtf[15].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_rtf_015_fisso].sCombo = theApp.m_sLabelTextRtf[15] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_rtf_015_grande].sCombo = theApp.m_sLabelTextRtf[15] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextRtf[16].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_rtf_016_fisso].sCombo = theApp.m_sLabelTextRtf[16] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_rtf_016_grande].sCombo = theApp.m_sLabelTextRtf[16] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextRtf[17].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_rtf_017_fisso].sCombo = theApp.m_sLabelTextRtf[17] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_rtf_017_grande].sCombo = theApp.m_sLabelTextRtf[17] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextRtf[18].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_rtf_018_fisso].sCombo = theApp.m_sLabelTextRtf[18] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_rtf_018_grande].sCombo = theApp.m_sLabelTextRtf[18] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextRtf[19].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_rtf_019_fisso].sCombo = theApp.m_sLabelTextRtf[19] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_rtf_019_grande].sCombo = theApp.m_sLabelTextRtf[19] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}

	if (!theApp.m_sLabelTextCL[0].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_cl_000_fisso].sCombo = theApp.m_sLabelTextCL[0] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_cl_000_grande].sCombo = theApp.m_sLabelTextCL[0] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextCL[1].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_cl_001_fisso].sCombo = theApp.m_sLabelTextCL[1] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_cl_001_grande].sCombo = theApp.m_sLabelTextCL[1] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextCL[2].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_cl_002_fisso].sCombo = theApp.m_sLabelTextCL[2] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_cl_002_grande].sCombo = theApp.m_sLabelTextCL[2] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextCL[3].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_cl_003_fisso].sCombo = theApp.m_sLabelTextCL[3] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_cl_003_grande].sCombo = theApp.m_sLabelTextCL[3] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextCL[4].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_cl_004_fisso].sCombo = theApp.m_sLabelTextCL[4] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_cl_004_grande].sCombo = theApp.m_sLabelTextCL[4] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextCL[5].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_cl_005_fisso].sCombo = theApp.m_sLabelTextCL[5] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_cl_005_grande].sCombo = theApp.m_sLabelTextCL[5] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextCL[6].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_cl_006_fisso].sCombo = theApp.m_sLabelTextCL[6] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_cl_006_grande].sCombo = theApp.m_sLabelTextCL[6] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextCL[7].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_cl_007_fisso].sCombo = theApp.m_sLabelTextCL[7] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_cl_007_grande].sCombo = theApp.m_sLabelTextCL[7] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextCL[8].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_cl_008_fisso].sCombo = theApp.m_sLabelTextCL[8] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_cl_008_grande].sCombo = theApp.m_sLabelTextCL[8] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextCL[9].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_cl_009_fisso].sCombo = theApp.m_sLabelTextCL[9] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_cl_009_grande].sCombo = theApp.m_sLabelTextCL[9] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextCL[10].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_cl_010_fisso].sCombo = theApp.m_sLabelTextCL[10] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_cl_010_grande].sCombo = theApp.m_sLabelTextCL[10] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextCL[11].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_cl_011_fisso].sCombo = theApp.m_sLabelTextCL[11] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_cl_011_grande].sCombo = theApp.m_sLabelTextCL[11] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextCL[12].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_cl_012_fisso].sCombo = theApp.m_sLabelTextCL[12] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_cl_012_grande].sCombo = theApp.m_sLabelTextCL[12] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextCL[13].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_cl_013_fisso].sCombo = theApp.m_sLabelTextCL[13] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_cl_013_grande].sCombo = theApp.m_sLabelTextCL[13] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextCL[14].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_cl_014_fisso].sCombo = theApp.m_sLabelTextCL[14] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_cl_014_grande].sCombo = theApp.m_sLabelTextCL[14] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextCL[15].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_cl_015_fisso].sCombo = theApp.m_sLabelTextCL[15] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_cl_015_grande].sCombo = theApp.m_sLabelTextCL[15] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextCL[16].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_cl_016_fisso].sCombo = theApp.m_sLabelTextCL[16] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_cl_016_grande].sCombo = theApp.m_sLabelTextCL[16] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextCL[17].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_cl_017_fisso].sCombo = theApp.m_sLabelTextCL[17] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_cl_017_grande].sCombo = theApp.m_sLabelTextCL[17] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextCL[18].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_cl_018_fisso].sCombo = theApp.m_sLabelTextCL[18] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_cl_018_grande].sCombo = theApp.m_sLabelTextCL[18] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}
	if (!theApp.m_sLabelTextCL[19].IsEmpty())
	{
		CFieldDlg::m_strFieldEndox[libero_cl_019_fisso].sCombo = theApp.m_sLabelTextCL[19] + theApp.GetMessageString(IDS_TESTOFISSO);
		CFieldDlg::m_strFieldEndox[libero_cl_019_grande].sCombo = theApp.m_sLabelTextCL[19] + theApp.GetMessageString(IDS_TESTOLUNGO);
	}

	CFieldDlg::m_strFieldEndox[libero_dataora_000].sCombo = theApp.m_sLabelDate[0];
	CFieldDlg::m_strFieldEndox[libero_dataora_001].sCombo = theApp.m_sLabelDate[1];
	CFieldDlg::m_strFieldEndox[libero_dataora_002].sCombo = theApp.m_sLabelDate[2];
	CFieldDlg::m_strFieldEndox[libero_dataora_003].sCombo = theApp.m_sLabelDate[3];
	CFieldDlg::m_strFieldEndox[libero_dataora_004].sCombo = theApp.m_sLabelDate[4];
	CFieldDlg::m_strFieldEndox[libero_dataora_005].sCombo = theApp.m_sLabelDate[5];
	CFieldDlg::m_strFieldEndox[libero_dataora_006].sCombo = theApp.m_sLabelDate[6];
	CFieldDlg::m_strFieldEndox[libero_dataora_007].sCombo = theApp.m_sLabelDate[7];
	CFieldDlg::m_strFieldEndox[libero_dataora_008].sCombo = theApp.m_sLabelDate[8];
	CFieldDlg::m_strFieldEndox[libero_dataora_009].sCombo = theApp.m_sLabelDate[9];
	CFieldDlg::m_strFieldEndox[libero_dataora_010].sCombo = theApp.m_sLabelDate[10];
	CFieldDlg::m_strFieldEndox[libero_dataora_011].sCombo = theApp.m_sLabelDate[11];
	CFieldDlg::m_strFieldEndox[libero_dataora_012].sCombo = theApp.m_sLabelDate[12];
	CFieldDlg::m_strFieldEndox[libero_dataora_013].sCombo = theApp.m_sLabelDate[13];
	CFieldDlg::m_strFieldEndox[libero_dataora_014].sCombo = theApp.m_sLabelDate[14];
	CFieldDlg::m_strFieldEndox[libero_dataora_015].sCombo = theApp.m_sLabelDate[15];
	CFieldDlg::m_strFieldEndox[libero_dataora_016].sCombo = theApp.m_sLabelDate[16];
	CFieldDlg::m_strFieldEndox[libero_dataora_017].sCombo = theApp.m_sLabelDate[17];
	CFieldDlg::m_strFieldEndox[libero_dataora_018].sCombo = theApp.m_sLabelDate[18];
	CFieldDlg::m_strFieldEndox[libero_dataora_019].sCombo = theApp.m_sLabelDate[19];

	// --- //

	for (int i = 0; i < NUM_LABEL_GRIDCL; i++)
	{
		CFieldDlg::m_strFieldEndox[esame_gridcl000 + i].sCombo = theApp.m_sLabelTextGridCL[i];
	}

	// --- //

	//

	g_FormCaract[edt_libero000].sDescrizione = theApp.m_sLabelText[0];
	g_FormCaract[edt_libero001].sDescrizione = theApp.m_sLabelText[1];
	g_FormCaract[edt_libero002].sDescrizione = theApp.m_sLabelText[2];
	g_FormCaract[edt_libero003].sDescrizione = theApp.m_sLabelText[3];
	g_FormCaract[edt_libero004].sDescrizione = theApp.m_sLabelText[4];
	g_FormCaract[edt_libero005].sDescrizione = theApp.m_sLabelText[5];
	g_FormCaract[edt_libero006].sDescrizione = theApp.m_sLabelText[6];
	g_FormCaract[edt_libero007].sDescrizione = theApp.m_sLabelText[7];
	g_FormCaract[edt_libero008].sDescrizione = theApp.m_sLabelText[8];
	g_FormCaract[edt_libero009].sDescrizione = theApp.m_sLabelText[9];
	g_FormCaract[edt_libero010].sDescrizione = theApp.m_sLabelText[10];
	g_FormCaract[edt_libero011].sDescrizione = theApp.m_sLabelText[11];
	g_FormCaract[edt_libero012].sDescrizione = theApp.m_sLabelText[12];
	g_FormCaract[edt_libero013].sDescrizione = theApp.m_sLabelText[13];
	g_FormCaract[edt_libero014].sDescrizione = theApp.m_sLabelText[14];
	g_FormCaract[edt_libero015].sDescrizione = theApp.m_sLabelText[15];
	g_FormCaract[edt_libero016].sDescrizione = theApp.m_sLabelText[16];
	g_FormCaract[edt_libero017].sDescrizione = theApp.m_sLabelText[17];
	g_FormCaract[edt_libero018].sDescrizione = theApp.m_sLabelText[18];
	g_FormCaract[edt_libero019].sDescrizione = theApp.m_sLabelText[19];
	g_FormCaract[edt_libero020].sDescrizione = theApp.m_sLabelText[20];
	g_FormCaract[edt_libero021].sDescrizione = theApp.m_sLabelText[21];
	g_FormCaract[edt_libero022].sDescrizione = theApp.m_sLabelText[22];
	g_FormCaract[edt_libero023].sDescrizione = theApp.m_sLabelText[23];
	g_FormCaract[edt_libero024].sDescrizione = theApp.m_sLabelText[24];
	g_FormCaract[edt_libero025].sDescrizione = theApp.m_sLabelText[25];
	g_FormCaract[edt_libero026].sDescrizione = theApp.m_sLabelText[26];
	g_FormCaract[edt_libero027].sDescrizione = theApp.m_sLabelText[27];
	g_FormCaract[edt_libero028].sDescrizione = theApp.m_sLabelText[28];
	g_FormCaract[edt_libero029].sDescrizione = theApp.m_sLabelText[29];
	g_FormCaract[edt_libero030].sDescrizione = theApp.m_sLabelText[30];
	g_FormCaract[edt_libero031].sDescrizione = theApp.m_sLabelText[31];
	g_FormCaract[edt_libero032].sDescrizione = theApp.m_sLabelText[32];
	g_FormCaract[edt_libero033].sDescrizione = theApp.m_sLabelText[33];
	g_FormCaract[edt_libero034].sDescrizione = theApp.m_sLabelText[34];
	g_FormCaract[edt_libero035].sDescrizione = theApp.m_sLabelText[35];
	g_FormCaract[edt_libero036].sDescrizione = theApp.m_sLabelText[36];
	g_FormCaract[edt_libero037].sDescrizione = theApp.m_sLabelText[37];
	g_FormCaract[edt_libero038].sDescrizione = theApp.m_sLabelText[38];
	g_FormCaract[edt_libero039].sDescrizione = theApp.m_sLabelText[39];
	g_FormCaract[edt_libero040].sDescrizione = theApp.m_sLabelText[40];
	g_FormCaract[edt_libero041].sDescrizione = theApp.m_sLabelText[41];
	g_FormCaract[edt_libero042].sDescrizione = theApp.m_sLabelText[42];
	g_FormCaract[edt_libero043].sDescrizione = theApp.m_sLabelText[43];
	g_FormCaract[edt_libero044].sDescrizione = theApp.m_sLabelText[44];
	g_FormCaract[edt_libero045].sDescrizione = theApp.m_sLabelText[45];
	g_FormCaract[edt_libero046].sDescrizione = theApp.m_sLabelText[46];
	g_FormCaract[edt_libero047].sDescrizione = theApp.m_sLabelText[47];
	g_FormCaract[edt_libero048].sDescrizione = theApp.m_sLabelText[48];
	g_FormCaract[edt_libero049].sDescrizione = theApp.m_sLabelText[49];
	g_FormCaract[edt_libero050].sDescrizione = theApp.m_sLabelText[50];
	g_FormCaract[edt_libero051].sDescrizione = theApp.m_sLabelText[51];
	g_FormCaract[edt_libero052].sDescrizione = theApp.m_sLabelText[52];
	g_FormCaract[edt_libero053].sDescrizione = theApp.m_sLabelText[53];
	g_FormCaract[edt_libero054].sDescrizione = theApp.m_sLabelText[54];
	g_FormCaract[edt_libero055].sDescrizione = theApp.m_sLabelText[55];
	g_FormCaract[edt_libero056].sDescrizione = theApp.m_sLabelText[56];
	g_FormCaract[edt_libero057].sDescrizione = theApp.m_sLabelText[57];
	g_FormCaract[edt_libero058].sDescrizione = theApp.m_sLabelText[58];
	g_FormCaract[edt_libero059].sDescrizione = theApp.m_sLabelText[59];
	g_FormCaract[edt_libero060].sDescrizione = theApp.m_sLabelText[60];
	g_FormCaract[edt_libero061].sDescrizione = theApp.m_sLabelText[61];
	g_FormCaract[edt_libero062].sDescrizione = theApp.m_sLabelText[62];
	g_FormCaract[edt_libero063].sDescrizione = theApp.m_sLabelText[63];
	g_FormCaract[edt_libero064].sDescrizione = theApp.m_sLabelText[64];
	g_FormCaract[edt_libero065].sDescrizione = theApp.m_sLabelText[65];
	g_FormCaract[edt_libero066].sDescrizione = theApp.m_sLabelText[66];
	g_FormCaract[edt_libero067].sDescrizione = theApp.m_sLabelText[67];
	g_FormCaract[edt_libero068].sDescrizione = theApp.m_sLabelText[68];
	g_FormCaract[edt_libero069].sDescrizione = theApp.m_sLabelText[69];
	g_FormCaract[edt_libero070].sDescrizione = theApp.m_sLabelText[70];
	g_FormCaract[edt_libero071].sDescrizione = theApp.m_sLabelText[71];
	g_FormCaract[edt_libero072].sDescrizione = theApp.m_sLabelText[72];
	g_FormCaract[edt_libero073].sDescrizione = theApp.m_sLabelText[73];
	g_FormCaract[edt_libero074].sDescrizione = theApp.m_sLabelText[74];
	g_FormCaract[edt_libero075].sDescrizione = theApp.m_sLabelText[75];
	g_FormCaract[edt_libero076].sDescrizione = theApp.m_sLabelText[76];
	g_FormCaract[edt_libero077].sDescrizione = theApp.m_sLabelText[77];
	g_FormCaract[edt_libero078].sDescrizione = theApp.m_sLabelText[78];
	g_FormCaract[edt_libero079].sDescrizione = theApp.m_sLabelText[79];
	g_FormCaract[edt_libero080].sDescrizione = theApp.m_sLabelText[80];
	g_FormCaract[edt_libero081].sDescrizione = theApp.m_sLabelText[81];
	g_FormCaract[edt_libero082].sDescrizione = theApp.m_sLabelText[82];
	g_FormCaract[edt_libero083].sDescrizione = theApp.m_sLabelText[83];
	g_FormCaract[edt_libero084].sDescrizione = theApp.m_sLabelText[84];
	g_FormCaract[edt_libero085].sDescrizione = theApp.m_sLabelText[85];
	g_FormCaract[edt_libero086].sDescrizione = theApp.m_sLabelText[86];
	g_FormCaract[edt_libero087].sDescrizione = theApp.m_sLabelText[87];
	g_FormCaract[edt_libero088].sDescrizione = theApp.m_sLabelText[88];
	g_FormCaract[edt_libero089].sDescrizione = theApp.m_sLabelText[89];
	g_FormCaract[edt_libero090].sDescrizione = theApp.m_sLabelText[90];
	g_FormCaract[edt_libero091].sDescrizione = theApp.m_sLabelText[91];
	g_FormCaract[edt_libero092].sDescrizione = theApp.m_sLabelText[92];
	g_FormCaract[edt_libero093].sDescrizione = theApp.m_sLabelText[93];
	g_FormCaract[edt_libero094].sDescrizione = theApp.m_sLabelText[94];
	g_FormCaract[edt_libero095].sDescrizione = theApp.m_sLabelText[95];
	g_FormCaract[edt_libero096].sDescrizione = theApp.m_sLabelText[96];
	g_FormCaract[edt_libero097].sDescrizione = theApp.m_sLabelText[97];
	g_FormCaract[edt_libero098].sDescrizione = theApp.m_sLabelText[98];
	g_FormCaract[edt_libero099].sDescrizione = theApp.m_sLabelText[99];

	g_FormCaract[edt_liberortf000].sDescrizione = theApp.m_sLabelTextRtf[0];
	g_FormCaract[edt_liberortf001].sDescrizione = theApp.m_sLabelTextRtf[1];
	g_FormCaract[edt_liberortf002].sDescrizione = theApp.m_sLabelTextRtf[2];
	g_FormCaract[edt_liberortf003].sDescrizione = theApp.m_sLabelTextRtf[3];
	g_FormCaract[edt_liberortf004].sDescrizione = theApp.m_sLabelTextRtf[4];
	g_FormCaract[edt_liberortf005].sDescrizione = theApp.m_sLabelTextRtf[5];
	g_FormCaract[edt_liberortf006].sDescrizione = theApp.m_sLabelTextRtf[6];
	g_FormCaract[edt_liberortf007].sDescrizione = theApp.m_sLabelTextRtf[7];
	g_FormCaract[edt_liberortf008].sDescrizione = theApp.m_sLabelTextRtf[8];
	g_FormCaract[edt_liberortf009].sDescrizione = theApp.m_sLabelTextRtf[9];
	g_FormCaract[edt_liberortf010].sDescrizione = theApp.m_sLabelTextRtf[10];
	g_FormCaract[edt_liberortf011].sDescrizione = theApp.m_sLabelTextRtf[11];
	g_FormCaract[edt_liberortf012].sDescrizione = theApp.m_sLabelTextRtf[12];
	g_FormCaract[edt_liberortf013].sDescrizione = theApp.m_sLabelTextRtf[13];
	g_FormCaract[edt_liberortf014].sDescrizione = theApp.m_sLabelTextRtf[14];
	g_FormCaract[edt_liberortf015].sDescrizione = theApp.m_sLabelTextRtf[15];
	g_FormCaract[edt_liberortf016].sDescrizione = theApp.m_sLabelTextRtf[16];
	g_FormCaract[edt_liberortf017].sDescrizione = theApp.m_sLabelTextRtf[17];
	g_FormCaract[edt_liberortf018].sDescrizione = theApp.m_sLabelTextRtf[18];
	g_FormCaract[edt_liberortf019].sDescrizione = theApp.m_sLabelTextRtf[19];

	g_FormCaract[edt_liberocl000].sDescrizione = theApp.m_sLabelTextCL[0];
	g_FormCaract[edt_liberocl001].sDescrizione = theApp.m_sLabelTextCL[1];
	g_FormCaract[edt_liberocl002].sDescrizione = theApp.m_sLabelTextCL[2];
	g_FormCaract[edt_liberocl003].sDescrizione = theApp.m_sLabelTextCL[3];
	g_FormCaract[edt_liberocl004].sDescrizione = theApp.m_sLabelTextCL[4];
	g_FormCaract[edt_liberocl005].sDescrizione = theApp.m_sLabelTextCL[5];
	g_FormCaract[edt_liberocl006].sDescrizione = theApp.m_sLabelTextCL[6];
	g_FormCaract[edt_liberocl007].sDescrizione = theApp.m_sLabelTextCL[7];
	g_FormCaract[edt_liberocl008].sDescrizione = theApp.m_sLabelTextCL[8];
	g_FormCaract[edt_liberocl009].sDescrizione = theApp.m_sLabelTextCL[9];
	g_FormCaract[edt_liberocl010].sDescrizione = theApp.m_sLabelTextCL[10];
	g_FormCaract[edt_liberocl011].sDescrizione = theApp.m_sLabelTextCL[11];
	g_FormCaract[edt_liberocl012].sDescrizione = theApp.m_sLabelTextCL[12];
	g_FormCaract[edt_liberocl013].sDescrizione = theApp.m_sLabelTextCL[13];
	g_FormCaract[edt_liberocl014].sDescrizione = theApp.m_sLabelTextCL[14];
	g_FormCaract[edt_liberocl015].sDescrizione = theApp.m_sLabelTextCL[15];
	g_FormCaract[edt_liberocl016].sDescrizione = theApp.m_sLabelTextCL[16];
	g_FormCaract[edt_liberocl017].sDescrizione = theApp.m_sLabelTextCL[17];
	g_FormCaract[edt_liberocl018].sDescrizione = theApp.m_sLabelTextCL[18];
	g_FormCaract[edt_liberocl019].sDescrizione = theApp.m_sLabelTextCL[19];

	g_FormCaract[edt_liberodataora000].sDescrizione = theApp.m_sLabelDate[0];
	g_FormCaract[edt_liberodataora001].sDescrizione = theApp.m_sLabelDate[1];
	g_FormCaract[edt_liberodataora002].sDescrizione = theApp.m_sLabelDate[2];
	g_FormCaract[edt_liberodataora003].sDescrizione = theApp.m_sLabelDate[3];
	g_FormCaract[edt_liberodataora004].sDescrizione = theApp.m_sLabelDate[4];
	g_FormCaract[edt_liberodataora005].sDescrizione = theApp.m_sLabelDate[5];
	g_FormCaract[edt_liberodataora006].sDescrizione = theApp.m_sLabelDate[6];
	g_FormCaract[edt_liberodataora007].sDescrizione = theApp.m_sLabelDate[7];
	g_FormCaract[edt_liberodataora008].sDescrizione = theApp.m_sLabelDate[8];
	g_FormCaract[edt_liberodataora009].sDescrizione = theApp.m_sLabelDate[9];
	g_FormCaract[edt_liberodataora010].sDescrizione = theApp.m_sLabelDate[10];
	g_FormCaract[edt_liberodataora011].sDescrizione = theApp.m_sLabelDate[11];
	g_FormCaract[edt_liberodataora012].sDescrizione = theApp.m_sLabelDate[12];
	g_FormCaract[edt_liberodataora013].sDescrizione = theApp.m_sLabelDate[13];
	g_FormCaract[edt_liberodataora014].sDescrizione = theApp.m_sLabelDate[14];
	g_FormCaract[edt_liberodataora015].sDescrizione = theApp.m_sLabelDate[15];
	g_FormCaract[edt_liberodataora016].sDescrizione = theApp.m_sLabelDate[16];
	g_FormCaract[edt_liberodataora017].sDescrizione = theApp.m_sLabelDate[17];
	g_FormCaract[edt_liberodataora018].sDescrizione = theApp.m_sLabelDate[18];
	g_FormCaract[edt_liberodataora019].sDescrizione = theApp.m_sLabelDate[19];

	g_FormCaract[btn_liberotastostampa000].sDescrizione = theApp.m_sLabelTastoStampa[0];
	g_FormCaract[btn_liberotastostampa001].sDescrizione = theApp.m_sLabelTastoStampa[1];
	g_FormCaract[btn_liberotastostampa002].sDescrizione = theApp.m_sLabelTastoStampa[2];
	g_FormCaract[btn_liberotastostampa003].sDescrizione = theApp.m_sLabelTastoStampa[3];
	g_FormCaract[btn_liberotastostampa004].sDescrizione = theApp.m_sLabelTastoStampa[4];
	g_FormCaract[btn_liberotastostampa005].sDescrizione = theApp.m_sLabelTastoStampa[5];
	g_FormCaract[btn_liberotastostampa006].sDescrizione = theApp.m_sLabelTastoStampa[6];
	g_FormCaract[btn_liberotastostampa007].sDescrizione = theApp.m_sLabelTastoStampa[7];
	g_FormCaract[btn_liberotastostampa008].sDescrizione = theApp.m_sLabelTastoStampa[8];
	g_FormCaract[btn_liberotastostampa009].sDescrizione = theApp.m_sLabelTastoStampa[9];
	g_FormCaract[btn_liberotastostampa010].sDescrizione = theApp.m_sLabelTastoStampa[10];
	g_FormCaract[btn_liberotastostampa011].sDescrizione = theApp.m_sLabelTastoStampa[11];
	g_FormCaract[btn_liberotastostampa012].sDescrizione = theApp.m_sLabelTastoStampa[12];
	g_FormCaract[btn_liberotastostampa013].sDescrizione = theApp.m_sLabelTastoStampa[13];
	g_FormCaract[btn_liberotastostampa014].sDescrizione = theApp.m_sLabelTastoStampa[14];
	g_FormCaract[btn_liberotastostampa015].sDescrizione = theApp.m_sLabelTastoStampa[15];
	g_FormCaract[btn_liberotastostampa016].sDescrizione = theApp.m_sLabelTastoStampa[16];
	g_FormCaract[btn_liberotastostampa017].sDescrizione = theApp.m_sLabelTastoStampa[17];
	g_FormCaract[btn_liberotastostampa018].sDescrizione = theApp.m_sLabelTastoStampa[18];
	g_FormCaract[btn_liberotastostampa019].sDescrizione = theApp.m_sLabelTastoStampa[19];

	g_FormCaract[btn_liberotastobrowser000].sDescrizione = theApp.m_sLabelTastoBrowser[0];
	g_FormCaract[btn_liberotastobrowser001].sDescrizione = theApp.m_sLabelTastoBrowser[1];
	g_FormCaract[btn_liberotastobrowser002].sDescrizione = theApp.m_sLabelTastoBrowser[2];
	g_FormCaract[btn_liberotastobrowser003].sDescrizione = theApp.m_sLabelTastoBrowser[3];
	g_FormCaract[btn_liberotastobrowser004].sDescrizione = theApp.m_sLabelTastoBrowser[4];
	g_FormCaract[btn_liberotastobrowser005].sDescrizione = theApp.m_sLabelTastoBrowser[5];
	g_FormCaract[btn_liberotastobrowser006].sDescrizione = theApp.m_sLabelTastoBrowser[6];
	g_FormCaract[btn_liberotastobrowser007].sDescrizione = theApp.m_sLabelTastoBrowser[7];
	g_FormCaract[btn_liberotastobrowser008].sDescrizione = theApp.m_sLabelTastoBrowser[8];
	g_FormCaract[btn_liberotastobrowser009].sDescrizione = theApp.m_sLabelTastoBrowser[9];
	g_FormCaract[btn_liberotastobrowser010].sDescrizione = theApp.m_sLabelTastoBrowser[10];
	g_FormCaract[btn_liberotastobrowser011].sDescrizione = theApp.m_sLabelTastoBrowser[11];
	g_FormCaract[btn_liberotastobrowser012].sDescrizione = theApp.m_sLabelTastoBrowser[12];
	g_FormCaract[btn_liberotastobrowser013].sDescrizione = theApp.m_sLabelTastoBrowser[13];
	g_FormCaract[btn_liberotastobrowser014].sDescrizione = theApp.m_sLabelTastoBrowser[14];
	g_FormCaract[btn_liberotastobrowser015].sDescrizione = theApp.m_sLabelTastoBrowser[15];
	g_FormCaract[btn_liberotastobrowser016].sDescrizione = theApp.m_sLabelTastoBrowser[16];
	g_FormCaract[btn_liberotastobrowser017].sDescrizione = theApp.m_sLabelTastoBrowser[17];
	g_FormCaract[btn_liberotastobrowser018].sDescrizione = theApp.m_sLabelTastoBrowser[18];
	g_FormCaract[btn_liberotastobrowser019].sDescrizione = theApp.m_sLabelTastoBrowser[19];

	g_FormCaract[btn_liberotastoeseguibile000].sDescrizione = theApp.m_sLabelTastoEseguibile[0];
	g_FormCaract[btn_liberotastoeseguibile001].sDescrizione = theApp.m_sLabelTastoEseguibile[1];
	g_FormCaract[btn_liberotastoeseguibile002].sDescrizione = theApp.m_sLabelTastoEseguibile[2];
	g_FormCaract[btn_liberotastoeseguibile003].sDescrizione = theApp.m_sLabelTastoEseguibile[3];
	g_FormCaract[btn_liberotastoeseguibile004].sDescrizione = theApp.m_sLabelTastoEseguibile[4];
	g_FormCaract[btn_liberotastoeseguibile005].sDescrizione = theApp.m_sLabelTastoEseguibile[5];
	g_FormCaract[btn_liberotastoeseguibile006].sDescrizione = theApp.m_sLabelTastoEseguibile[6];
	g_FormCaract[btn_liberotastoeseguibile007].sDescrizione = theApp.m_sLabelTastoEseguibile[7];
	g_FormCaract[btn_liberotastoeseguibile008].sDescrizione = theApp.m_sLabelTastoEseguibile[8];
	g_FormCaract[btn_liberotastoeseguibile009].sDescrizione = theApp.m_sLabelTastoEseguibile[9];
	g_FormCaract[btn_liberotastoeseguibile010].sDescrizione = theApp.m_sLabelTastoEseguibile[10];
	g_FormCaract[btn_liberotastoeseguibile011].sDescrizione = theApp.m_sLabelTastoEseguibile[11];
	g_FormCaract[btn_liberotastoeseguibile012].sDescrizione = theApp.m_sLabelTastoEseguibile[12];
	g_FormCaract[btn_liberotastoeseguibile013].sDescrizione = theApp.m_sLabelTastoEseguibile[13];
	g_FormCaract[btn_liberotastoeseguibile014].sDescrizione = theApp.m_sLabelTastoEseguibile[14];
	g_FormCaract[btn_liberotastoeseguibile015].sDescrizione = theApp.m_sLabelTastoEseguibile[15];
	g_FormCaract[btn_liberotastoeseguibile016].sDescrizione = theApp.m_sLabelTastoEseguibile[16];
	g_FormCaract[btn_liberotastoeseguibile017].sDescrizione = theApp.m_sLabelTastoEseguibile[17];
	g_FormCaract[btn_liberotastoeseguibile018].sDescrizione = theApp.m_sLabelTastoEseguibile[18];
	g_FormCaract[btn_liberotastoeseguibile019].sDescrizione = theApp.m_sLabelTastoEseguibile[19];

	// --- //

	g_FormCaract[edt_fumo].sDescrizione = theApp.m_sAnamText[0];
	g_FormCaract[edt_caffe].sDescrizione = theApp.m_sAnamText[2];
	g_FormCaract[edt_sigarette].sDescrizione = theApp.m_sAnamText[1];
	g_FormCaract[edt_farmaci].sDescrizione = theApp.m_sAnamText[5];
	g_FormCaract[edt_alcool].sDescrizione = theApp.m_sAnamText[3];
	g_FormCaract[edt_assunzione].sDescrizione = theApp.m_sAnamText[6];
	g_FormCaract[edt_superalcolici].sDescrizione = theApp.m_sAnamText[4];

	// --- //

	for (int i = 0; i < NUM_LABEL_ETICHETTE; i++)
	{
		g_FormCaract[sub_etichetta000 + i].sDescrizione = theApp.m_sLabelTextEtichette[i];
	}

	// --- //

	for (int i = 0; i < NUM_LABEL_TASTO_CHIUSURAFASE; i++)
	{
		g_FormCaract[btn_liberotastochiusurafase000 + i].sDescrizione = theApp.m_sLabelTastoChiusuraFase[i];
	}

	// --- //

	for (int i = 0; i < NUM_LABEL_GRIDCL; i++)
	{
		g_FormCaract[sub_gridcl000 + i].sDescrizione = theApp.m_sLabelTextGridCL[i];
	}

	// --- //

	CBostonScoreSet setBS;
	if (setBS.OpenRecordset("CEsamiView::LeggiEtichette"))
	{
		while (!setBS.IsEOF())
		{
			if ((setBS.m_lValore >= 0) && (setBS.m_lValore <= 9))
				theApp.m_sBostonScore[setBS.m_lValore] = setBS.m_sFraseStampata;

			setBS.MoveNext();
		}

		setBS.CloseRecordset("CEsamiView::LeggiEtichette");
	}
}

void CEsamiView::ScriviEtichette()
{
	for (int i = 0; i < NUM_FIELD_ANAM; i++)
	{
		CString sFilter;
		sFilter.Format("Tipo = 'TEXT_ANAM' AND Indice = %li", i);

		CEtichetteSet setEtichette;
		setEtichette.SetOpenFilter(sFilter);
		if (setEtichette.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setEtichette.IsEOF())
				setEtichette.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setEtichette.EditRecordset("CEsamiView::ScriviEtichette");

			setEtichette.m_sTipo = "TEXT_ANAM";
			setEtichette.m_lIndice = i;
			setEtichette.m_sLabel = theApp.m_sAnamText[i].Left(3999);
			setEtichette.UpdateRecordset("CEsamiView::ScriviEtichette");

			setEtichette.CloseRecordset("CEsamiView::ScriviEtichette");
		}
	}

	for (int i = 0; i < NUM_LABEL_TESTO; i++)
	{
		CString sFilter;
		sFilter.Format("Tipo = 'TESTO' AND Indice = %li", i);

		CEtichetteSet setEtichette;
		setEtichette.SetOpenFilter(sFilter);
		if (setEtichette.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setEtichette.IsEOF())
				setEtichette.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setEtichette.EditRecordset("CEsamiView::ScriviEtichette");

			setEtichette.m_sTipo = "TESTO";
			setEtichette.m_lIndice = i;
			setEtichette.m_sLabel = theApp.m_sLabelText[i].Left(50);
			setEtichette.m_lIdCampoRelazionato = theApp.m_lIdCampoRelazionato[i];
			setEtichette.UpdateRecordset("CEsamiView::ScriviEtichette");

			setEtichette.CloseRecordset("CEsamiView::ScriviEtichette");
		}
	}

	for (int i = 0; i < NUM_LABEL_TESTO_RTF; i++)
	{
		CString sFilter;
		sFilter.Format("Tipo = 'TESTO_RTF' AND Indice = %li", i);

		CEtichetteSet setEtichette;
		setEtichette.SetOpenFilter(sFilter);
		if (setEtichette.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setEtichette.IsEOF())
				setEtichette.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setEtichette.EditRecordset("CEsamiView::ScriviEtichette");

			setEtichette.m_sTipo = "TESTO_RTF";
			setEtichette.m_lIndice = i;
			setEtichette.m_sLabel = theApp.m_sLabelTextRtf[i].Left(50);
			setEtichette.m_lIdCampoRelazionato = theApp.m_lIdCampoRelazionatoRtf[i];
			setEtichette.UpdateRecordset("CEsamiView::ScriviEtichette");

			setEtichette.CloseRecordset("CEsamiView::ScriviEtichette");
		}
	}

	for (int i = 0; i < NUM_LABEL_TESTO_CL; i++)
	{
		CString sFilter;
		sFilter.Format("Tipo = 'TESTO_CL' AND Indice = %li", i);

		CEtichetteSet setEtichette;
		setEtichette.SetOpenFilter(sFilter);
		if (setEtichette.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setEtichette.IsEOF())
				setEtichette.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setEtichette.EditRecordset("CEsamiView::ScriviEtichette");

			setEtichette.m_sTipo = "TESTO_CL";
			setEtichette.m_lIndice = i;
			setEtichette.m_sLabel = theApp.m_sLabelTextCL[i].Left(50);
			setEtichette.UpdateRecordset("CEsamiView::ScriviEtichette");

			setEtichette.CloseRecordset("CEsamiView::ScriviEtichette");
		}
	}

	for (int i = 0; i < NUM_LABEL_DATAORA; i++)
	{
		CString sFilter;
		sFilter.Format("Tipo='DATAORA_TESTO' AND Indice=%li", i);

		CEtichetteSet setEtichette;
		setEtichette.SetOpenFilter(sFilter);
		if (setEtichette.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setEtichette.IsEOF())
				setEtichette.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setEtichette.EditRecordset("CEsamiView::ScriviEtichette");

			setEtichette.m_sTipo = "DATAORA_TESTO";
			setEtichette.m_lIndice = i;
			setEtichette.m_sLabel = theApp.m_sLabelDate[i].Left(50);
			setEtichette.UpdateRecordset("CEsamiView::ScriviEtichette");

			setEtichette.CloseRecordset("CEsamiView::ScriviEtichette");
		}
	}

	for (int i = 0; i < NUM_LABEL_TASTO_STAMPA; i++)
	{
		CString sFilter;
		sFilter.Format("Tipo='TASTI_STAMPA_TESTO' AND Indice=%li", i);

		CEtichetteSet setEtichette;
		setEtichette.SetOpenFilter(sFilter);
		if (setEtichette.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setEtichette.IsEOF())
				setEtichette.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setEtichette.EditRecordset("CEsamiView::ScriviEtichette");

			setEtichette.m_sTipo = "TASTI_STAMPA_TESTO";
			setEtichette.m_lIndice = i;
			setEtichette.m_sLabel = theApp.m_sLabelTastoStampa[i].Left(50);
			setEtichette.UpdateRecordset("CEsamiView::ScriviEtichette");

			setEtichette.CloseRecordset("CEsamiView::ScriviEtichette");
		}
	}

	for (int i = 0; i < NUM_LABEL_TASTO_BROWSER; i++)
	{
		CString sFilter;
		sFilter.Format("Tipo='TASTI_BROWSER_TESTO' AND Indice=%li", i);

		CEtichetteSet setEtichette;
		setEtichette.SetOpenFilter(sFilter);
		if (setEtichette.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setEtichette.IsEOF())
				setEtichette.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setEtichette.EditRecordset("CEsamiView::ScriviEtichette");

			setEtichette.m_sTipo = "TASTI_BROWSER_TESTO";
			setEtichette.m_lIndice = i;
			setEtichette.m_sLabel = theApp.m_sLabelTastoBrowser[i].Left(50);
			setEtichette.UpdateRecordset("CEsamiView::ScriviEtichette");

			setEtichette.CloseRecordset("CEsamiView::ScriviEtichette");
		}
	}

	for (int i = 0; i < NUM_LABEL_TASTO_EXEC; i++)
	{
		CString sFilter;
		sFilter.Format("Tipo='TASTI_ESEGUIBILE_TESTO' AND Indice=%li", i);

		CEtichetteSet setEtichette;
		setEtichette.SetOpenFilter(sFilter);
		if (setEtichette.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setEtichette.IsEOF())
				setEtichette.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setEtichette.EditRecordset("CEsamiView::ScriviEtichette");

			setEtichette.m_sTipo = "TASTI_ESEGUIBILE_TESTO";
			setEtichette.m_lIndice = i;
			setEtichette.m_sLabel = theApp.m_sLabelTastoEseguibile[i].Left(50);
			setEtichette.UpdateRecordset("CEsamiView::ScriviEtichette");

			setEtichette.CloseRecordset("CEsamiView::ScriviEtichette");
		}
	}

	for (int i = 0; i < NUM_LABEL_TESTO; i++)
	{
		CComboConfigSet setComboConfig;
		CString sFilter;

		//

		sFilter.Format("Configurazione = 'ACTIVE' AND Tabella = %li", i);
		setComboConfig.SetOpenFilter(sFilter);
		if (setComboConfig.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setComboConfig.IsEOF())
				setComboConfig.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setComboConfig.EditRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.m_sConfigurazione = "ACTIVE";
			setComboConfig.m_lTabella = i;
			setComboConfig.m_lParametroNum = theApp.m_bComboActive[i];
			setComboConfig.UpdateRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.CloseRecordset("CEsamiView::ScriviEtichette");
		}

		//

		sFilter.Format("Configurazione = 'MULTIPLESEL' AND Tabella = %li", i);
		setComboConfig.SetOpenFilter(sFilter);
		if (setComboConfig.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setComboConfig.IsEOF())
				setComboConfig.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setComboConfig.EditRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.m_sConfigurazione = "MULTIPLESEL";
			setComboConfig.m_lTabella = i;
			setComboConfig.m_lParametroNum = theApp.m_bComboMultipleSel[i];
			setComboConfig.UpdateRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.CloseRecordset("CEsamiView::ScriviEtichette");
		}

		//

		sFilter.Format("Configurazione = 'SINGLELINE' AND Tabella = %li", i);
		setComboConfig.SetOpenFilter(sFilter);
		if (setComboConfig.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setComboConfig.IsEOF())
				setComboConfig.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setComboConfig.EditRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.m_sConfigurazione = "SINGLELINE";
			setComboConfig.m_lTabella = i;
			setComboConfig.m_lParametroNum = theApp.m_bComboSingleLine[i];
			setComboConfig.UpdateRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.CloseRecordset("CEsamiView::ScriviEtichette");
		}

		//

		sFilter.Format("Configurazione = 'UPPERCASE' AND Tabella = %li", i);
		setComboConfig.SetOpenFilter(sFilter);
		if (setComboConfig.OpenRecordset("Archivio ComboBox"))
		{
			if (setComboConfig.IsEOF())
				setComboConfig.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setComboConfig.EditRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.m_sConfigurazione = "UPPERCASE";
			setComboConfig.m_lTabella = i;
			setComboConfig.m_lParametroNum = theApp.m_bComboUppercase[i];
			setComboConfig.UpdateRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.CloseRecordset("CEsamiView::ScriviEtichette");
		}

		//

		sFilter.Format("Configurazione = 'NUMERIC' AND Tabella = %li", i);
		setComboConfig.SetOpenFilter(sFilter);
		if (setComboConfig.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setComboConfig.IsEOF())
				setComboConfig.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setComboConfig.EditRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.m_sConfigurazione = "NUMERIC";
			setComboConfig.m_lTabella = i;
			setComboConfig.m_lParametroNum = theApp.m_bComboNumerico[i];
			setComboConfig.UpdateRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.CloseRecordset("CEsamiView::ScriviEtichette");
		}
	}

	for (int i = 0; i < NUM_FIELD_ANAM; i++)
	{
		CComboConfigSet setComboConfig;
		CString sFilter;

		//

		sFilter.Format("Configurazione = 'VISI_ANAM' AND Tabella = %li", i);
		setComboConfig.SetOpenFilter(sFilter);
		if (setComboConfig.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setComboConfig.IsEOF())
				setComboConfig.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setComboConfig.EditRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.m_sConfigurazione = "VISI_ANAM";
			setComboConfig.m_lTabella = i;
			setComboConfig.m_lParametroNum = theApp.m_bAnamVisi[i];
			setComboConfig.UpdateRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.CloseRecordset("CEsamiView::ScriviEtichette");
		}

		//

		sFilter.Format("Configurazione = 'AUTO_ANAM' AND Tabella = %li", i);
		setComboConfig.SetOpenFilter(sFilter);
		if (setComboConfig.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setComboConfig.IsEOF())
				setComboConfig.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setComboConfig.EditRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.m_sConfigurazione = "AUTO_ANAM";
			setComboConfig.m_lTabella = i;
			setComboConfig.m_lParametroNum = theApp.m_bAnamAuto[i];
			setComboConfig.UpdateRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.CloseRecordset("CEsamiView::ScriviEtichette");
		}
	}

	for (int i = 0; i < NUM_LABEL_TESTO; i++)
	{
		CString sFilter;
		sFilter.Format("Configurazione='COPY' AND Tabella=%li", i);

		CComboConfigSet setComboConfig;
		setComboConfig.SetOpenFilter(sFilter);
		if (setComboConfig.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setComboConfig.IsEOF())
				setComboConfig.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setComboConfig.EditRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.m_sConfigurazione = "COPY";
			setComboConfig.m_lTabella = i;
			setComboConfig.m_lParametroNum = theApp.m_bCopy[i];
			setComboConfig.UpdateRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.CloseRecordset("CEsamiView::ScriviEtichette");
		}
	}

	for (int i = 0; i < NUM_LABEL_TESTO_RTF; i++)
	{
		CString sFilter;
		sFilter.Format("Configurazione='COPY_RTF' AND Tabella=%li", i);

		CComboConfigSet setComboConfig;
		setComboConfig.SetOpenFilter(sFilter);
		if (setComboConfig.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setComboConfig.IsEOF())
				setComboConfig.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setComboConfig.EditRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.m_sConfigurazione = "COPY_RTF";
			setComboConfig.m_lTabella = i;
			setComboConfig.m_lParametroNum = theApp.m_bCopyRtf[i];
			setComboConfig.UpdateRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.CloseRecordset("CEsamiView::ScriviEtichette");
		}
	}

	for (int i = 0; i < NUM_LABEL_TESTO_CL; i++)
	{
		CString sFilter;
		sFilter.Format("Configurazione='COPY_CL' AND Tabella=%li", i);

		CComboConfigSet setComboConfig;
		setComboConfig.SetOpenFilter(sFilter);
		if (setComboConfig.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setComboConfig.IsEOF())
				setComboConfig.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setComboConfig.EditRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.m_sConfigurazione = "COPY_CL";
			setComboConfig.m_lTabella = i;
			setComboConfig.m_lParametroNum = theApp.m_bCopyCL[i];
			setComboConfig.UpdateRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.CloseRecordset("CEsamiView::ScriviEtichette");
		}
	}

	for (int i = 0; i < NUM_LABEL_DATAORA; i++)
	{
		CString sFilter;
		sFilter.Format("Configurazione='COPY_DATE' AND Tabella=%li", i);

		CComboConfigSet setComboConfig;
		setComboConfig.SetOpenFilter(sFilter);
		if (setComboConfig.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setComboConfig.IsEOF())
				setComboConfig.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setComboConfig.EditRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.m_sConfigurazione = "COPY_DATE";
			setComboConfig.m_lTabella = i;
			setComboConfig.m_lParametroNum = theApp.m_bCopyDate[i];
			setComboConfig.UpdateRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.CloseRecordset("CEsamiView::ScriviEtichette");
		}
	}

	for (int i = 0; i < NUM_LABEL_TESTO_CL; i++)
	{
		CString sFilter;
		sFilter.Format("Configurazione='ALARM_CL' AND Tabella=%li", i);

		CComboConfigSet setComboConfig;
		setComboConfig.SetOpenFilter(sFilter);
		if (setComboConfig.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setComboConfig.IsEOF())
				setComboConfig.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setComboConfig.EditRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.m_sConfigurazione = "ALARM_CL";
			setComboConfig.m_lTabella = i;
			setComboConfig.m_lParametroNum = theApp.m_bAlarmCL[i];
			setComboConfig.UpdateRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.CloseRecordset("CEsamiView::ScriviEtichette");
		}
	}

	for (int i = 0; i < NUM_LABEL_TESTO_CL; i++)
	{
		CString sFilter;
		sFilter.Format("Configurazione='PAROLECHIAVE_CL' AND Tabella=%li", i);

		CComboConfigSet setComboConfig;
		setComboConfig.SetOpenFilter(sFilter);
		if (setComboConfig.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setComboConfig.IsEOF())
				setComboConfig.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setComboConfig.EditRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.m_sConfigurazione = "PAROLECHIAVE_CL";
			setComboConfig.m_lTabella = i;
			setComboConfig.m_sParametroStr = theApp.m_sParoleChiaveCL[i];
			setComboConfig.UpdateRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.CloseRecordset("CEsamiView::ScriviEtichette");
		}
	}

	for (int i = 0; i < NUM_LABEL_DATAORA; i++)
	{
		CString sFilter;
		sFilter.Format("Configurazione='DATAORA_TIPO' AND Tabella=%li", i);

		CComboConfigSet setComboConfig;
		setComboConfig.SetOpenFilter(sFilter);
		if (setComboConfig.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setComboConfig.IsEOF())
				setComboConfig.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setComboConfig.EditRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.m_sConfigurazione = "DATAORA_TIPO";
			setComboConfig.m_lTabella = i;
			setComboConfig.m_lParametroNum = theApp.m_iRadioDate[i];
			setComboConfig.UpdateRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.CloseRecordset("CEsamiView::ScriviEtichette");
		}
	}

	for (int i = 0; i < NUM_LABEL_TASTO_STAMPA; i++)
	{
		CString sFilter;
		sFilter.Format("Configurazione='TASTOSTAMPA_FILE' AND Tabella=%li", i);

		CComboConfigSet setComboConfig;
		setComboConfig.SetOpenFilter(sFilter);
		if (setComboConfig.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setComboConfig.IsEOF())
				setComboConfig.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setComboConfig.EditRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.m_sConfigurazione = "TASTOSTAMPA_FILE";
			setComboConfig.m_lTabella = i;
			setComboConfig.m_sParametroStr = theApp.m_sTastoStampaFile[i];
			setComboConfig.UpdateRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.CloseRecordset("CEsamiView::ScriviEtichette");
		}
	}

	for (int i = 0; i < NUM_LABEL_TASTO_STAMPA; i++)
	{
		CString sFilter;
		sFilter.Format("Configurazione='TASTOSTAMPA_CHECK' AND Tabella=%li", i);

		CComboConfigSet setComboConfig;
		setComboConfig.SetOpenFilter(sFilter);
		if (setComboConfig.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setComboConfig.IsEOF())
				setComboConfig.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setComboConfig.EditRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.m_sConfigurazione = "TASTOSTAMPA_CHECK";
			setComboConfig.m_lTabella = i;
			setComboConfig.m_lParametroNum = theApp.m_bTastoStampaCheck[i];
			setComboConfig.UpdateRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.CloseRecordset("CEsamiView::ScriviEtichette");
		}
	}

	for (int i = 0; i < NUM_LABEL_TASTO_BROWSER; i++)
	{
		CString sFilter;
		sFilter.Format("Configurazione='TASTOBROWSER_INDIRIZZO' AND Tabella=%li", i);

		CComboConfigSet setComboConfig;
		setComboConfig.SetOpenFilter(sFilter);
		if (setComboConfig.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setComboConfig.IsEOF())
				setComboConfig.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setComboConfig.EditRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.m_sConfigurazione = "TASTOBROWSER_INDIRIZZO";
			setComboConfig.m_lTabella = i;
			setComboConfig.m_sParametroStr = theApp.m_sTastoBrowserIndirizzo[i];
			setComboConfig.UpdateRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.CloseRecordset("CEsamiView::ScriviEtichette");
		}
	}

	for (int i = 0; i < NUM_LABEL_TASTO_EXEC; i++)
	{
		CString sFilter;
		sFilter.Format("Configurazione='TASTOESEGUIBILE_FILE' AND Tabella=%li", i);

		CComboConfigSet setComboConfig;
		setComboConfig.SetOpenFilter(sFilter);
		if (setComboConfig.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setComboConfig.IsEOF())
				setComboConfig.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setComboConfig.EditRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.m_sConfigurazione = "TASTOESEGUIBILE_FILE";
			setComboConfig.m_lTabella = i;
			setComboConfig.m_sParametroStr = theApp.m_sTastoEseguibileFile[i];
			setComboConfig.UpdateRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.CloseRecordset("CEsamiView::ScriviEtichette");
		}
	}

	for (int i = 0; i < NUM_LABEL_ETICHETTE; i++)
	{
		CString sFilter;
		sFilter.Format("Tipo = 'ETICHETTA' AND Indice = %li", i);

		CEtichetteSet setEtichette;
		setEtichette.SetOpenFilter(sFilter);
		if (setEtichette.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setEtichette.IsEOF())
				setEtichette.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setEtichette.EditRecordset("CEsamiView::ScriviEtichette");

			setEtichette.m_sTipo = "ETICHETTA";
			setEtichette.m_lIndice = i;
			setEtichette.m_sLabel = theApp.m_sLabelTextEtichette[i].Left(50);
			setEtichette.UpdateRecordset("CEsamiView::ScriviEtichette");

			setEtichette.CloseRecordset("CEsamiView::ScriviEtichette");
		}
	}

	for (int i = 0; i < NUM_LABEL_TASTO_CHIUSURAFASE; i++)
	{
		CString sFilter;
		sFilter.Format("Tipo = 'TASTOCHIUSURAFASE' AND Indice = %li", i);

		CEtichetteSet setEtichette;
		setEtichette.SetOpenFilter(sFilter);
		if (setEtichette.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setEtichette.IsEOF())
				setEtichette.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setEtichette.EditRecordset("CEsamiView::ScriviEtichette");

			setEtichette.m_sTipo = "TASTOCHIUSURAFASE";
			setEtichette.m_lIndice = i;
			setEtichette.m_sLabel = theApp.m_sLabelTastoChiusuraFase[i].Left(50);
			setEtichette.UpdateRecordset("CEsamiView::ScriviEtichette");

			setEtichette.CloseRecordset("CEsamiView::ScriviEtichette");
		}
	}

	for (int i = 0; i < NUM_LABEL_TASTO_CHIUSURAFASE; i++)
	{
		CString sFilter;
		sFilter.Format("Configurazione='TASTOCHIUSURAFASE_IDFASE' AND Tabella=%li", i);

		CComboConfigSet setComboConfig;
		setComboConfig.SetOpenFilter(sFilter);
		if (setComboConfig.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setComboConfig.IsEOF())
				setComboConfig.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setComboConfig.EditRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.m_sConfigurazione = "TASTOCHIUSURAFASE_IDFASE";
			setComboConfig.m_lTabella = i;
			setComboConfig.m_lParametroNum = theApp.m_lIdFaseTastoChiusuraFase[i];
			setComboConfig.UpdateRecordset("CEsamiView::ScriviEtichette");

			setComboConfig.CloseRecordset("CEsamiView::ScriviEtichette");
		}
	}

	for (int i = 0; i < NUM_LABEL_GRIDCL; i++)
	{
		CString sFilter;
		sFilter.Format("Tipo = 'GRIDCL' AND Indice = %li", i);

		CEtichetteSet setEtichette;
		setEtichette.SetOpenFilter(sFilter);
		if (setEtichette.OpenRecordset("CEsamiView::ScriviEtichette"))
		{
			if (setEtichette.IsEOF())
				setEtichette.AddNewRecordset("CEsamiView::ScriviEtichette");
			else
				setEtichette.EditRecordset("CEsamiView::ScriviEtichette");

			setEtichette.m_sTipo = "GRIDCL";
			setEtichette.m_lIndice = i;
			setEtichette.m_sLabel = theApp.m_sLabelTextGridCL[i].Left(50);
			setEtichette.UpdateRecordset("CEsamiView::ScriviEtichette");

			setEtichette.CloseRecordset("CEsamiView::ScriviEtichette");
		}
	}

}

void CEsamiView::OnInitialUpdate()
{
	theApp.m_nProgramMode = NOTHING_MODE;

	((CEsamiDoc*)m_pDocument)->SetTitle(theApp.GetAppTitle(0));

	//

	InitToolbar();

	EnableToolTips(TRUE);

	AssociaRecordset();

	m_pPazientiSet->OpenRecordset("CEsamiView::OnInitialUpdate", TRUE, TRUE);

	CString strFilter;
	strFilter.Format("Paziente=%li", m_pPazientiSet->m_lContatore);
	m_pEsamiSet->SetBaseFilter(""); // <-- Sandro: aggiunto per il filtro di Padova //
	m_pEsamiSet->SetOpenFilter(strFilter);
	m_pEsamiSet->OpenRecordset("CEsamiView::OnInitialUpdate");

	LeggiEtichette();

	CResizableFormView::OnInitialUpdate();

	// Sandro 27/02/2013 // verifico che la stazione sia associata ad una sede //

	BOOL bOpenSetup = FALSE;
	if (theApp.m_lIDSedeEsameDefault <= 0)
	{
		bOpenSetup = TRUE;
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_SEDEESAME_MANCANTE));
	}

	// Sandro 22/03/2010 - l'installazione di Endox mi apre la schermata di "Setup Programma" //

	if (theApp.m_bConfigure || bOpenSetup)
	{
		theApp.DestroyAccessDialog();
		theApp.DestroyShowDbQueriesDialog();

		CSetupDlg dlg(this);
		dlg.DoModal();
		AfxGetMainWnd()->PostMessage(WM_CLOSE);
		return;
	}

	// Sandro 05/05/2010 - controllo che il DB sia della versione giusta per questo eseguibile //
#ifdef _BETA
	theApp.m_lSaltaControlloVersione = 1;
#endif
	if (theApp.m_lSaltaControlloVersione <= 0)
	{
		CString strSWVersion = theApp.GetAppTitle(3);
		CString strDBVersion = CDBVersionSet().GetDBVersion();

		if (strSWVersion != strDBVersion)
		{
			theApp.DestroyAccessDialog();

			CString strMessage;
			strMessage.Format(theApp.GetMessageString(IDS_DB_VERSION_ERROR), strSWVersion, strDBVersion);
			theApp.MessageBoxEndo(strMessage, theApp.GetMessageString(IDS_ACHTUNG), MB_OK | MB_ICONSTOP);

			AfxGetMainWnd()->PostMessage(WM_CLOSE);
			return;
		}
	}
	else
	{
		// decremento il numero di volte per le quali vado a saltare il controllo della versione //

		if (theApp.m_lSaltaControlloVersione > 100)
			theApp.m_lSaltaControlloVersione = 100; // <-- sistema anti-furbo... posso evitarlo max 100 volte //

		theApp.m_lSaltaControlloVersione--;
		WritePrivateProfileInt(szSettings, szSaltaControlloVersione, theApp.m_lSaltaControlloVersione, theApp.m_sFileConfig);
	}

	//
	m_ctrlGruppoEsame.m_pEsamiView = this;

	// Sandro 20/10/2016 //

	if (theApp.m_bCentraleStampa)
	{
		GetDlgItem(IDC_LABEL_PAZIENTE_00)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LABEL_PAZIENTE_01)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_PAZIENTE_FISCALE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LABEL_PAZIENTE_02)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_PAZIENTE_SANITARIO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LABEL_PAZIENTE_03)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_PAZIENTE_COGNOME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LABEL_PAZIENTE_04)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_PAZIENTE_NOME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LABEL_PAZIENTE_05)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_PAZIENTE_SESSO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LABEL_PAZIENTE_06)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_PAZIENTE_TELEFONO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LABEL_PAZIENTE_07)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_PAZIENTE_NATOIL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LABEL_PAZIENTE_08)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_PAZIENTE_NATOA)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_FRAMESTATO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LABEL_STATO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LABEL_STATO_NEW1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LABEL_STATO_NEW2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LABEL_STATO_NEW3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LABEL_STATO_NEW4)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_NUMESAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_NUMESAME)->ShowWindow(SW_HIDE);

		// GetDlgItem(IDC_GRUPPO_ESAME)->ShowWindow(SW_HIDE);

		// Sandro 11/11/2016 //

		CRect rectTemp;
		CRect rectNew;

		//

		GetDlgItem(IDC_SUBFORM_3)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);

		rectNew.top = 0;
		rectNew.left = 0;
		rectNew.bottom = rectTemp.bottom;
		rectNew.right = rectTemp.right;
		GetDlgItem(IDC_SUBFORM_3)->SetWindowPos(NULL, rectNew.left, rectNew.top, rectNew.Width(), rectNew.Height(), SWP_NOOWNERZORDER);

		//

		AddAnchor(IDC_SUBFORM_3, CSize(0, 0), CSize(100, 100));
	}
	else
	{
		AddAnchor(IDC_BAR_ESAME, CSize(0, 0), CSize(0, 100));
		// AddAnchor(IDC_GRUPPO_ESAME, CSize(0, 0), CSize(100, 100)); // Sandro 11/07/2013 // ridisegno tabctrl con problemi da VS2012 //
		AddAnchor(IDC_FRAME_GRUPPO_ESAME, CSize(0, 0), CSize(100, 100)); // Sandro 11/07/2013 // ridisegno tabctrl con problemi da VS2012 //
		AddAnchor(IDC_SUBFORM_3, CSize(0, 0), CSize(100, 100));
		AddAnchor(IDC_SUBFORM_ESAME, CSize(0, 0), CSize(50, 100));
		AddAnchor(IDC_SUBFORM_ALBUM, CSize(50, 0), CSize(100, 100));
		AddAnchor(IDC_LABEL_PAZIENTE_00, CSize(0, 0), CSize(100, 0));
		AddAnchor(IDC_LABEL_STATO, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_LABEL_STATO_MONITORAGGIO, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_LABEL_STATO_NEW1, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_LABEL_MON_PAZIENTE, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_LABEL_STATO_NEW2, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_LABEL_MON_DISPOSITIVO, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_LABEL_STATO_NEW3, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_LABEL_STATO_NEW4, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_BTN_MON_STOP, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_PROGRESS_IMPORT, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_STATIC_FRAMESTATO, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_LABEL_PAZIENTE_01, CSize(0, 0), CSize(10, 0));
		AddAnchor(IDC_LABEL_PAZIENTE_02, CSize(0, 0), CSize(10, 0));
		AddAnchor(IDC_PAZIENTE_FISCALE, CSize(10, 0), CSize(25, 0));
		AddAnchor(IDC_PAZIENTE_SANITARIO, CSize(10, 0), CSize(25, 0));
		AddAnchor(IDC_LABEL_PAZIENTE_03, CSize(25, 0), CSize(35, 0));
		AddAnchor(IDC_LABEL_PAZIENTE_04, CSize(25, 0), CSize(35, 0));
		AddAnchor(IDC_PAZIENTE_COGNOME, CSize(35, 0), CSize(50, 0));
		AddAnchor(IDC_PAZIENTE_NOME, CSize(35, 0), CSize(50, 0));
		AddAnchor(IDC_LABEL_PAZIENTE_05, CSize(50, 0), CSize(60, 0));
		AddAnchor(IDC_LABEL_PAZIENTE_06, CSize(50, 0), CSize(60, 0));
		AddAnchor(IDC_PAZIENTE_SESSO, CSize(60, 0), CSize(75, 0));
		AddAnchor(IDC_PAZIENTE_TELEFONO, CSize(60, 0), CSize(75, 0));
		AddAnchor(IDC_LABEL_PAZIENTE_07, CSize(75, 0), CSize(85, 0));
		AddAnchor(IDC_LABEL_PAZIENTE_08, CSize(75, 0), CSize(85, 0));
		AddAnchor(IDC_PAZIENTE_NATOIL, CSize(85, 0), CSize(100, 0));
		AddAnchor(IDC_PAZIENTE_NATOA, CSize(85, 0), CSize(100, 0));
		AddAnchor(IDC_BTN_HIDE, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_BTN_SHOW, CSize(100, 0), CSize(100, 0));
		AddAnchor(IDC_BTN_IMMAGINI, CSize(100, 0), CSize(100, 0));
	}

	m_pImgManager = new CImgManager(theApp.m_sPathImageOD, &theApp.m_dbEndox);
	if (theApp.m_nApplication == PRG_CARDIOX)
	{
		m_pImgManager->SetThumbStoreSize(CSize(HSIZE_PAL / 2, VSIZE_PAL / 2));
		m_pImgManager->SetThumbRetrieveSize(CSize(HSIZE_PAL / 2, VSIZE_PAL / 2));
	}
	else
	{
		m_pImgManager->SetThumbStoreSize(CSize(HSIZE_PAL / 4, VSIZE_PAL / 4));
		m_pImgManager->SetThumbRetrieveSize(CSize(HSIZE_PAL / 4, VSIZE_PAL / 4));
	}
	m_pImgManager->SetImageExt(CString(EXT_IMG).Right(3));
	m_pImgManager->SetThumbExt(CString(EXT_WIN).Right(3));

	m_pImgManager->SetMovieBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_FILM)), RGB(255, 255, 255));				// WHITE
	m_pImgManager->SetTiffBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_TIFF)), RGB(255, 255, 255));				// WHITE
	m_pImgManager->SetPrintBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_PRINT)), RGB(255, 0, 0), bottomright);		// RED
	m_pImgManager->SetSelectBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_SELEZIONE)), RGB(0, 255, 0), topleft);	// NEON GREEN
	m_pImgManager->SetDicomBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DICOM_IMM)), RGB(255, 255, 255));			// WHITE
	m_pImgManager->SetDicomMovieBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DICOM_FILM)), RGB(255, 255, 255));	// WHITE
	m_pImgManager->SetCIBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_ICON_CI)), RGB(255, 255, 255));				// WHITE
	m_pImgManager->SetImageQuality(theApp.m_nArchivioImmaginiQualita, theApp.m_nArchivioMiniatureQualita, 100);

	m_pDocManager = new CMyDocManager();

	GetDlgItem(IDC_LABEL_PAZIENTE_00)->SetFont(&theApp.m_fontBig);
	GetDlgItem(IDC_GRUPPO_ESAME)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_PAZIENTE_FISCALE)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_PAZIENTE_SANITARIO)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_PAZIENTE_COGNOME)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_PAZIENTE_NOME)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_PAZIENTE_SESSO)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_PAZIENTE_TELEFONO)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_PAZIENTE_NATOIL)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_PAZIENTE_NATOA)->SetFont(&theApp.m_fontBold);

	CAlbumForm::CreateFormEx(&m_ctrlGruppoEsame, &m_ctrlSubFormAlbum, &m_pFormImmagini, this);

	theApp.LocalizeDialog(this, CEsamiView::IDD, "EsamiView");

	// nascondo le voci di menù non necessarie //
	switch (theApp.m_nApplication)
	{
	case PRG_IMAGENT:
	{
		NascondiMenuImageNT();
		break;
	}
	default:
	{
		NascondiMenuEndox();
		break;
	}
	}

	//

	// Nacondo voci non più funzionanti
	CMenu* pMainMenu = AfxGetMainWnd()->GetMenu();
	CMenu* pMenuFile = pMainMenu->GetSubMenu(0);
	pMenuFile->DeleteMenu(ID_FILE_INQUIERO_1, MF_BYCOMMAND); // Teleconsulto operatore //
	pMenuFile->DeleteMenu(ID_FILE_INQUIERO_2, MF_BYCOMMAND); // Teleconsulto client //
	//

	//#ifndef _DEBUG

	// carico in memoria la lista dei comuni //
	CComuniBulkSet().CaricaInMemoria();

	// carico in memoria la lista dei medici curanti //
	CMediciCurantiInviantiBulkSet(MEDICI_CURANTI).CaricaInMemoria();

	// carico in memoria la lista dei medici invianti //
	CMediciCurantiInviantiBulkSet(MEDICI_INVIANTI).CaricaInMemoria();

	// carico in memoria i gruppi di prestazioni regionali //
	CCodificaRegionaleGruppiBulkSet().CaricaInMemoria();

	// carico in memoria i gruppi dei farmaci per la ricetta //
	CFarmaciGruppiRicBulkSet().CaricaInMemoria();

	// carico in memoria il tariffario regionale //
	CCodificaRegionaleExBulkSet().CaricaInMemoria();

	// carico in memoria i farmaci //
	CFarmaciBulkSet().CaricaInMemoria();

	// carico in memoria i campi della worklist //
	if (theApp.m_bPrenotazioniCup)
		CCupWorkListManager::LoadIntoMemory();

	//#endif

	/* Leggo le informazioni passate dalla riga di comando per andare, eventualmente, al paziente ricercato
	if (g_strCmdLine.IsEmpty() == FALSE)
	{
	int nTmp;
	CString strTmp;

	long lPaziente;

	strTmp = "Paziente";
	g_strCmdLine.TrimRight();
	nTmp = g_strCmdLine.Find(strTmp);

	if (nTmp >= 0)
	{
	nTmp += (strTmp.GetLength() + 1);
	lPaziente = atol(g_strCmdLine.Right(g_strCmdLine.GetLength() - nTmp));
	if (RicercaCodicePaziente(lPaziente, 0, FALSE, FALSE) == TRUE)
	{
	MovePazientiAndEsami(NULL, TRUE, TRUE);
	}
	else
	{
	strTmp.Format(theApp.GetMessageString(IDS_ESAMIVIEW_PATIENTID_NOT_FOUND), lPaziente);
	theApp.AfxMessageBoxEndo(strTmp);

	MoveRecord(ID_RECORD_LAST);
	}
	}
	else
	{
	MoveRecord(ID_RECORD_LAST);
	}
	}
	else
	{
	MoveRecord(ID_RECORD_LAST);
	}
	*/

	if (!theApp.m_bCentraleStampa)
	{
		MoveRecord(ID_RECORD_LAST);

		GetDlgItem(IDC_LABEL_STATO)->SetFont(&theApp.m_fontBig, TRUE);
		GetDlgItem(IDC_LABEL_STATO_NEW1)->SetFont(&theApp.m_fontBig, TRUE);
		GetDlgItem(IDC_LABEL_STATO_NEW2)->SetFont(&theApp.m_fontBig, TRUE);
		GetDlgItem(IDC_LABEL_STATO_NEW3)->SetFont(&theApp.m_fontBig, TRUE);
		GetDlgItem(IDC_LABEL_STATO_NEW4)->SetFont(&theApp.m_fontBig, TRUE);

		GetDlgItem(IDC_STATIC_NUMESAME)->SetFont(&theApp.m_fontBold, TRUE);
		GetDlgItem(IDC_NUMESAME)->SetFont(&theApp.m_fontBold, TRUE);

		m_pWndExport = new CExportDlg(this, this);
		if (m_pWndExport != NULL)
			m_pWndExport->PostCreate(this, this);
	}
	else
	{
		m_ctrlGruppoEsame.InsertItem(theApp.GetMessageString(IDS_CENTRALEDISTAMPA), 0, 0);
		m_ctrlGruppoEsame.SetCurSel(0);
		m_ctrlGruppoEsame.MostraSubform();
	}

	//Simone - seleziono su quale monitor mi apro
	CDisplayHelper::GetDisplayWorkRect(&theApp.m_rectDesk, theApp.m_lOpenIntoMonitor);
	//AfxGetMainWnd()->SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right, theApp.m_rectDesk.bottom, SWP_NOOWNERZORDER);
	AfxGetMainWnd()->SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER);
	AfxGetMainWnd()->PostMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
	//

	//Simone 20/07/2016
	//Scrivo qui così sono apposto
	WritePrivateProfileInt("xcap", "top", theApp.m_rectDesk.top, theApp.m_sFileConfig);
	WritePrivateProfileInt("xcap", "left", theApp.m_rectDesk.left, theApp.m_sFileConfig);
	WritePrivateProfileInt("xcap", "bottom", theApp.m_rectDesk.bottom, theApp.m_sFileConfig);
	WritePrivateProfileInt("xcap", "right", theApp.m_rectDesk.right, theApp.m_sFileConfig);
	//

	m_bRicercaDiretta = FALSE;

	// Sandro 17/07/2015 //

	m_ctrlTextControlView.ResetContents();
	m_ctrlTextControlView.SetText(theApp.GetMessageString(IDS_REFERTO_ALTRO_ITEM));

	m_ctrlTextControlView.SetSelStart(0);
	m_ctrlTextControlView.SetSelLength(-1);

	theApp.m_sRefertoIntegratoRtf = m_ctrlTextControlView.GetRTFSelText();
	theApp.m_sRefertoIntegratoTxt = m_ctrlTextControlView.GetSelText();

	//

	if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
		SetTimer(0xEEE, 5000, NULL);

	if (theApp.m_bVitalSignIntegrazioneAttiva)
		VerificaSeMonitoraggiInCorsoStazione();

	//Simone RIMA 16002
	// Se la stazione è di acquisizione, parte il processo che verifica periodicamente lo stato dello streaming
	if (theApp.m_bCanAcquire)
	{
		m_streamingThreadState.pEsamiView = this;
		m_streamingThreadState.hWndParent = GetSafeHwnd();
		//AfxBeginThread(OnThreadGetStreamingState, &m_streamingThreadState, THREAD_BASE_PRIORITY_MIN);
	}

	// AfxMessageBox(theApp.GetMessageString(IDS_US_REFERTATO_DA));
	if (theApp.m_bMenuUsaTextboxBuscaExame)
	{
		GetDlgItem(IDC_EDIT_FLEURYFICHA)->SetFocus();
		m_ctrlEditFleuryFicha.Init();
		m_ctrlEditFleuryFicha.SetMode(_MODE_STANDARD_);
	}
}

UINT CEsamiView::OnThreadGetStreamingState(LPVOID pParam)
{
	tagStreamingStateTHREAD* param = (tagStreamingStateTHREAD*)pParam;

	param->pEsamiView->m_hEventExitStreamingStateThread = ::CreateEvent(NULL, FALSE, FALSE, "EventExitStreamingStateThread");
	InitializeCriticalSection(&param->pEsamiView->m_streamingStateThreadCS);

	//Carico la library
#ifdef _DEBUG	
	CString libName = "LibStreamingD.dll";
#else
	CString libName = "LibStreaming.dll";
#endif

	//GESTIONE DI DEBUG
	/*while (TRUE)
	{
	if (WaitForSingleObject(param->pEsamiView->m_hEventExitStreamingStateThread, 10000) == WAIT_OBJECT_0)
	break;

	switch (param->pEsamiView->m_lStreamingState)
	{
	case 0:
	param->pEsamiView->m_lStreamingState = StreamingStatus::enabled;
	break;

	case 1:
	param->pEsamiView->m_lStreamingState = StreamingStatus::connected;
	break;

	case 2:
	param->pEsamiView->m_lStreamingState = StreamingStatus::disabled;
	break;
	}

	TRACE("StreamingStateThread!\n");

	param->pEsamiView->UpdateFrameStato();
	}*/
	//

	HMODULE hModule = ::LoadLibrary(libName);

	if (hModule == NULL)
	{
		theApp.AfxMessageBoxEndo(libName + " error!", MB_ICONSTOP);
		return -1;
	}

	LibStreaming_GetStreamingState_PTR LibStreaming_GetStreamingState = (LibStreaming_GetStreamingState_PTR)::GetProcAddress(hModule, _LibStreaming_GetStreamingState_FUNCTION);
	if (LibStreaming_GetStreamingState == NULL)
	{
		theApp.AfxMessageBoxEndo(libName + " error!", MB_ICONSTOP);
		return -1; // FALSE;
	}

	//	
	EnterCriticalSection(&param->pEsamiView->m_streamingStateThreadCS);

	while (TRUE)
	{
		if (WaitForSingleObject(param->pEsamiView->m_hEventExitStreamingStateThread, 10000) == WAIT_OBJECT_0)
			break;

		switch (LibStreaming_GetStreamingState())
		{
		case 0:
			param->pEsamiView->m_lStreamingState = StreamingStatus::disabled;
			break;

		case 1:
			param->pEsamiView->m_lStreamingState = StreamingStatus::enabled;
			break;

		case 2:
			param->pEsamiView->m_lStreamingState = StreamingStatus::connected;
			break;
		}

		TRACE("StreamingStateThread!\n");

		param->pEsamiView->UpdateFrameStato();
	}

	::FreeLibrary(hModule);

	LeaveCriticalSection(&param->pEsamiView->m_streamingStateThreadCS);

	return 0;
}

BOOL CEsamiView::UpdateData(BOOL bSaveAndValidate)
{
	BOOL bResult = CResizableFormView::UpdateData(bSaveAndValidate);

	if (m_pFormImmagini)
		m_pFormImmagini->UpdateData(bSaveAndValidate);

	for (int i = 0; i < form_list_total; i++)
		if (m_pDynForm[i] != NULL)
			m_pDynForm[i]->UpdateData(bSaveAndValidate);

	return bResult;
}

BOOL CEsamiView::MoveRecord(UINT nIDMoveCommand)
{
	MovePazientiAndEsami(nIDMoveCommand, TRUE, TRUE);

	// Marvel BUG 4090 - desconjugação de laudos (tela principal do Tesicapture) 
	theApp.m_nProgramMode = NOTHING_MODE;

	return TRUE;
}

void CEsamiView::MovePazientiAndEsami(UINT nIDMoveCommand, BOOL bMoveEsami, BOOL bRefreshSubForm)
{
	//16052 Simone - Carico l'id versione maggiore per questa UO
	theApp.m_lLastGridCLVersion = CEndoGridCLViewVersionUOSet().GetLastGridVersion(theApp.m_lUO);

	if ((m_pPazientiSet->IsBOF() == FALSE) && (m_pPazientiSet->IsEOF() == FALSE))
	{
		MovePazientiRecordset(nIDMoveCommand);

		m_lNumDocumentsPatient = 0;
		if (!m_pPazientiSet->IsFieldNull(&m_pPazientiSet->m_lContatore))
		{
			// Sandro 04/01/2014 // RAS 20130175 //
			// m_pDocManager->SetCurrentID(m_pPazientiSet->m_lContatore, 90000000 + m_pPazientiSet->m_lContatore);
			m_lNumDocumentsPatient = m_pDocManager->GetAttachedDocNumberPatient(m_pPazientiSet->m_lContatore);
		}

		//Simone 24/02/2016 - RAS 20160008
		// A volte, spostandosi di paziente, le toolbar non vengono correttamente aggiornate.
		//	In questo modo forzo il ridisegno
		if (m_pExamBar)
			m_pExamBar->Invalidate();

		if (m_pPatientBar)
			m_pPatientBar->Invalidate();

		//
	}

	if (m_pPazientiSet->IsBOF() || m_pPazientiSet->IsEOF())
	{
		m_pPazientiSet->SetEmpty();
		m_pEsamiSet->SetEmpty();

		ResetForm();

		UpdateData(FALSE);
	}
	else
	{
		if (bRefreshSubForm)
		{
			if (bMoveEsami)
			{
				FiltraEsami();

				OnEsamiMove(ID_RECORD_LAST);
			}
			else
			{
				OnEsamiMove(NULL);
			}
		}
	}

	//
	if (m_pPazientiSet->m_bDeceduto == TRUE)
	{
		CString temp;
		GetDlgItem(IDC_LABEL_PAZIENTE_00)->GetWindowText(temp);
		temp += " " + theApp.GetMessageString(IDS_DECEDUTO);
		GetDlgItem(IDC_LABEL_PAZIENTE_00)->SetWindowText(temp);

		if (!m_pPazientiSet->IsFieldNull(&m_pPazientiSet->m_lDataDecesso) && m_pPazientiSet->m_lDataDecesso >= 0)
		{
			temp += " " + theApp.GetMessageString(IDS_IL) + " " + CCustomDate(m_pPazientiSet->m_lDataDecesso).GetDate("%d/%m/%Y");
			GetDlgItem(IDC_LABEL_PAZIENTE_00)->SetWindowText(temp);
		}

		GetDlgItem(IDC_LABEL_PAZIENTE_00)->SetFont(&theApp.m_fontBig);

		OnPazienteRefresh();
	}
}

void CEsamiView::StopRemotePlay()
{
	if (theApp.m_bVisAbilita)
	{
		HMODULE hModule;
#ifdef _DEBUG
		hModule = ::LoadLibrary("xrclientd.dll");
#else
		hModule = ::LoadLibrary("xrclient.dll");
#endif

		// XRClient //
		STOPPLAYPTR XRClient_StopPlay;
		GETERROROCCURREDPTR XRClient_GetErrorOccurred;
		ENABLEVIDEOOUTPUTPTR XRClient_EnableVideoOutput;

		if (hModule)
		{
			XRClient_StopPlay = (STOPPLAYPTR)GetProcAddress(hModule, "StopPlay");
			XRClient_GetErrorOccurred = (GETERROROCCURREDPTR)GetProcAddress(hModule, "GetErrorOccurred");
			XRClient_EnableVideoOutput = (ENABLEVIDEOOUTPUTPTR)GetProcAddress(hModule, "EnableVideoOutput");

			if (XRClient_StopPlay && !XRClient_StopPlay(theApp.m_sVisIp, theApp.m_lVisPorta))
			{
				TCHAR szError[2048];
				ZeroMemory(szError, sizeof(TCHAR) * 2048);
				XRClient_GetErrorOccurred(szError);
				CString sError;
				sError.Format(theApp.GetMessageString(IDS_ERRORE_REMOTO), szError);
				theApp.AfxMessageBoxEndo(sError);
			}

			if (theApp.m_bVisAbilitaMonitor && XRClient_EnableVideoOutput && !XRClient_EnableVideoOutput(theApp.m_sVisPortaMonitor, theApp.m_iPrevInput))
			{
				TCHAR szError[2048];
				ZeroMemory(szError, sizeof(char) * 2048);
				XRClient_GetErrorOccurred(szError);
				CString sError;
				sError.Format(theApp.GetMessageString(IDS_ERRORE_REMOTO), szError);
				theApp.AfxMessageBoxEndo(sError);
			}

			FreeLibrary(hModule);
		}
	}
}

BOOL CEsamiView::MovePazientiRecordset(UINT nIDMoveCommand)
{
	BOOL bResult = TRUE;

	switch (nIDMoveCommand)
	{
	case ID_RECORD_PREV:
	{
		StopRemotePlay();

		if (m_pPazientiSet->IsBOF() == FALSE)
			m_pPazientiSet->MovePrev();

		if (m_pPazientiSet->IsBOF() == FALSE)
			break;
	}

	case ID_RECORD_FIRST:
	{
		StopRemotePlay();

		m_pPazientiSet->RequeryRecordset();

		if ((m_pPazientiSet->IsBOF() == TRUE) || (m_pPazientiSet->IsEOF() == TRUE))
			bResult = FALSE;
		else
			m_pPazientiSet->MoveFirst();

		break;
	}

	case ID_RECORD_NEXT:
	{
		StopRemotePlay();

		if (m_pPazientiSet->IsEOF() == FALSE)
			m_pPazientiSet->MoveNext();

		if (m_pPazientiSet->IsEOF() == FALSE)
			break;
	}

	case ID_RECORD_LAST:
	{
		StopRemotePlay();

		m_pPazientiSet->RequeryRecordset();

		if ((m_pPazientiSet->IsBOF() == TRUE) || (m_pPazientiSet->IsEOF() == TRUE))
			bResult = FALSE;
		else
			m_pPazientiSet->MoveLast();

		break;
	}
	}

	return bResult;
}

BOOL CEsamiView::MoveEsamiRecordset(UINT nIDMoveCommand)
{
	VERIFY(m_pEsamiSet->GetEditMode() == 0);
	BOOL bResult = TRUE;

	// Marvel BUG 4090 - desconjugação de laudos (tela principal do Tesicapture) 
	/*if (theApp.m_nProgramMode & DO_NOT_MOVE_RECORD)
	{
	int numEsame = m_pEsamiSet->m_lNumEsame;
	m_pEsamiSet->RequeryRecordset();
	m_pEsamiSet->MoveFirst();

	for (int i = 1; i < numEsame; i++)
	{
	m_pEsamiSet->MoveNext();
	}
	}
	else
	{*/
	switch (nIDMoveCommand)
	{

	case ID_RECORD_PREV:
	{
		if (!m_pEsamiSet->IsBOF())
		{
			m_pEsamiSet->MovePrev();
			m_pEsamiSet->m_lNumEsame--;
		}

		if (!m_pEsamiSet->IsBOF())
			break;

		bResult = FALSE;
	}

	case ID_RECORD_FIRST:
	{
		m_pEsamiSet->RequeryRecordset();

		if (m_pEsamiSet->IsBOF() || m_pEsamiSet->IsEOF())
		{
			bResult = FALSE;
		}
		else
		{
			m_pEsamiSet->MoveFirst();
			m_pEsamiSet->m_lNumEsame = 1;
		}

		break;
	}

	case ID_RECORD_NEXT:
	{
		if (!m_pEsamiSet->IsEOF())
		{
			m_pEsamiSet->MoveNext();
			m_pEsamiSet->m_lNumEsame++;
		}

		if (!m_pEsamiSet->IsEOF())
			break;

		bResult = FALSE;
	}

	case ID_RECORD_LAST:
	{
		m_pEsamiSet->RequeryRecordset();

		if (m_pEsamiSet->IsBOF() || m_pEsamiSet->IsEOF())
		{
			bResult = FALSE;
		}
		else
		{
			m_pEsamiSet->MoveLast();
			m_pEsamiSet->m_lNumEsame = m_pPazientiSet->m_lTotEsami;
		}

		break;
	}

	//15/07/2015
	default:
	{
		int numEsame = m_pEsamiSet->m_lNumEsame;
		m_pEsamiSet->RequeryRecordset();
		m_pEsamiSet->MoveFirst();

		for (int i = 1; i < numEsame; i++)
		{
			m_pEsamiSet->MoveNext();
		}

		break;
	}
	}
	//}

	m_lNumDocumentsExam = 0;
	m_lNumDocumentsExamCarestream = 0;
	if (!m_pPazientiSet->IsFieldNull(&m_pPazientiSet->m_lContatore) && !m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lContatore))
		RefreshNumDocumentsExam();//Gabriel BUG 6225 - Lista DO

	// controllo se l'esame fa parte del mio distretto //
	if (!m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		m_pEsamiSet->m_bStessoDistretto = CDistrettiSediEsamiSet().GetStessoDistretto(m_pEsamiSet->m_lIDSedeEsame);

	//
	GetDlgItem(IDC_EDIT_FLEURYFICHA)->SetWindowText("");
	return bResult;
}

void CEsamiView::OnPazienteFirst()
{
	MovePazientiAndEsami(ID_RECORD_FIRST, TRUE, TRUE);
}

void CEsamiView::OnPazientePrev()
{
	MovePazientiAndEsami(ID_RECORD_PREV, TRUE, TRUE);
}

#define RICERCA_PAZIENTE_CONTATORE 0
#define RICERCA_PAZIENTE_CODESAME 1
#define RICERCA_PAZIENTE_ASSIDEN 2
#define RICERCA_PAZIENTE_CODICERICOVERO 3
#define RICERCA_PAZIENTE_FICHA 4

void CEsamiView::OnPazienteGoto()
{
	CGetCodeDlg dlg(this);
	if (dlg.DoModal() == IDOK)
	{
		switch (theApp.m_lRicercaCodiceEsame)
		{
		case RICERCA_PAZIENTE_CONTATORE:
		{
			RicercaCodicePaziente(dlg.m_lCode, 0, FALSE, TRUE);
			MovePazientiAndEsami(NULL, TRUE, TRUE);
			break;
		}
		case RICERCA_PAZIENTE_CODESAME:
		{
			BOOL bOK = (RicercaCodicePazienteCodEsameEx(dlg.m_sCode) > 0);
			MovePazientiAndEsami(NULL, !bOK, TRUE);
			break;
		}
		case RICERCA_PAZIENTE_ASSIDEN:
		{
			RicercaCodicePazienteAssiden(dlg.m_sCode);
			MovePazientiAndEsami(NULL, TRUE, TRUE);
			break;
		}
		case RICERCA_PAZIENTE_CODICERICOVERO:
		{
			BOOL bOK = RicercaCodicePazienteCodiceRicovero(dlg.m_sCode);
			MovePazientiAndEsami(NULL, !bOK, TRUE);
			break;
		}
		case RICERCA_PAZIENTE_FICHA:
		{
			CString sFicha = "";
			BOOL bAskBefore = TRUE;

			switch (dlg.m_sCode.Trim().GetLength())
			{
			case 10:
			{
				BOOL bOK = TRUE;
				if (dlg.m_sCode2.Trim().GetLength() == 0)
				{
					BOOL bOK = RicercaCodicePazienteCodiceRicovero(dlg.m_sCode, FALSE);
					if (!bOK)
					{
						CString sErrore;
						CString sServer;
						CString sUO;
						CString sEndpointRemoteCommunication;
						long lArrayCount;

						sFicha = dlg.m_sCode;

						if (FleuryCercaItensDaFicha(sFicha, sErrore, sServer, sUO, sEndpointRemoteCommunication, lArrayCount))
						{
							if (lArrayCount > 0)
							{
								long lArrayPos = 0;
								CString* sArray = new CString[lArrayCount];

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
								if (lArrayCount != 1)
								{
									CSelectNumeroFichaDlg selectDlg(this, sArray, lArrayCount);
									if (selectDlg.DoModal() == IDOK)
									{
										int iSpacePos = selectDlg.m_sSelectedFicha.Find(" ");
										sFicha = selectDlg.m_sSelectedFicha.Mid(0, iSpacePos).Trim();
										bAskBefore = FALSE;
									}
									else
									{
										sFicha = "";
									}
								}
								else
								{
									int iSpacePos = CString(sArray[0]).Find(" ");
									sFicha = CString(sArray[0]).Mid(0, iSpacePos).Trim();
									bAskBefore = FALSE;
								}
								sArray = NULL;
								delete(sArray);
							}
							else
							{
								sFicha = "";
								theApp.AfxMessageBoxEndo("Ficha não encontrada, por favor tente também usando um item");
							}
						}
						else
						{
							theApp.AfxMessageBoxEndo("Ficha não encontrada, por favor tente também usando um item");
						}
					}
					else
						MovePazientiAndEsami(NULL, !bOK, TRUE);
					break;
				}
				else
				{
					for (int i = 0; i < 10; i++)
					{
						if (!isdigit(dlg.m_sCode[i]))
						{
							bOK = FALSE;
							break;
						}
					}
					for (int i = 0; i < dlg.m_sCode2.GetLength(); i++)
					{
						if (!isdigit(dlg.m_sCode2[i]))
						{
							bOK = FALSE;
							break;
						}
					}
					if (bOK)
					{
						if (dlg.m_sCode2.GetLength() >= 4)
						{
							dlg.m_sCode2 = dlg.m_sCode2.Left(2);
						}
						else
						{
							dlg.m_sCode2.Replace("0", "");
						}
						sFicha.Format("%s_%s_0", dlg.m_sCode, dlg.m_sCode2);
					}
				}
				break;
			}

			case 14:
			{
				BOOL bOK = TRUE;

				for (int i = 0; i < 14; i++)
				{
					if ((i == 10) || (i == 12))
					{
						if (dlg.m_sCode[i] != '_')
						{
							bOK = FALSE;
							break;
						}
					}
					else
					{
						if (!isdigit(dlg.m_sCode[i]))
						{
							bOK = FALSE;
							break;
						}
					}
				}

				if (bOK)
					sFicha = dlg.m_sCode;

				break;
			}
			case 15:
			{
				BOOL bOK = TRUE;

				for (int i = 0; i < 15; i++)
				{
					if ((i == 10) || (i == 13))
					{
						if (dlg.m_sCode[i] != '_')
						{
							bOK = FALSE;
							break;
						}
					}
					else
					{
						if (!isdigit(dlg.m_sCode[i]))
						{
							bOK = FALSE;
							break;
						}
					}
				}

				if (bOK)
					sFicha = dlg.m_sCode;

				break;
			}
			case 16:
			{
				BOOL bOK = TRUE;

				for (int i = 0; i < 16; i++)
				{
					if (!isdigit(dlg.m_sCode[i]))
					{
						bOK = FALSE;
						break;
					}
				}

				if (bOK)
				{
					int iItem = atoi(dlg.m_sCode.Mid(12, 2));
					if (iItem > 0)
						sFicha.Format("%s_%d_0", dlg.m_sCode.Left(10), iItem);
				}

				break;
			}
			}

			if (!sFicha.IsEmpty())
			{
				if (dlg.bCheckStatus)
				{
					CString sErrore;
					CString sServer;
					CString sUO;
					CString sEndpointRemoteCommunication;

					if (FleuryCercaFicha(sFicha, sErrore, sServer, sUO, sEndpointRemoteCommunication))
					{
						CString sMessage;
						sMessage.Format("Ficha %s (%s) se encontra na unidade %s", sFicha, sUO, sServer);
						theApp.AfxMessageBoxEndo(sMessage);
					}
					else
					{
						if (sErrore.IsEmpty())
						{
							CString sMessage;
							sMessage.Format("Ficha %s (%s) se encontra na unidade %s", sFicha, sUO, sServer);
							theApp.AfxMessageBoxEndo(sMessage);
						}
						else
							theApp.AfxMessageBoxEndo("Desculpe, não foi possivel obter o status da ficha " + sFicha);
					}
					break;
				}
				else
				{
					OnFleuryCentralizacao(sFicha, bAskBefore);
				}
			}
			break;
		}
		default:
		{
			ASSERT(FALSE);
			break;
		}
		}
	}
}

void CEsamiView::OnFleuryCentralizacao(CString sFicha, BOOL bAskBefore)
{
	long lReturn = RicercaCodicePazienteCodEsameEx(sFicha);

	if (lReturn == 0 && theApp.m_bContingencia) //Julio BUG 3456 - Contingencia
	{
		//Julio Modeless
		CWaitFleuryTransferitoDlg* splashDlg = NULL;
		splashDlg = new CWaitFleuryTransferitoDlg();
		splashDlg->CreateModelessDialog(this);
		//

		CString sErrore;
		CString sServer;
		CString sUO;
		CString sEndpointRemoteCommunication;

		if (FleuryCercaFicha(sFicha, sErrore, sServer, sUO, sEndpointRemoteCommunication))
		{
			/*BOOL bOK = RicercaCodicePazienteCodEsameEx(sFicha);
			MovePazientiAndEsami(NULL, !bOK, TRUE);*/

			CListaPrenotazioniCupDlg dlg(this, this, 0, sFicha.Left(10));
			dlg.DoModal();
		}
		else
		{
			if (sErrore.IsEmpty())
			{
				CString sMessage = theApp.GetMessageString(IDS_FLEURY_ERROR_030);
				sMessage.Format(sMessage, sFicha);
				theApp.AfxMessageBoxEndo(sMessage);
			}
			else
				theApp.AfxMessageBoxEndo(sErrore);
		}

		//Julio 27/11/2017 Modeless
		splashDlg->ShowWindow(SW_HIDE);
		splashDlg->DestroyWindow();
		splashDlg = NULL;

		delete splashDlg;
		//

		return;
	}

	switch (lReturn)
	{
	case 0:
	{
		// esame non trovato nel DB (oppure c'è in locale ma già trasferito presso altra sede Fleury) //
		CString sMessage;
		CString sItem = sFicha;
		sItem.Replace(sItem.Left(11), "");
		sItem.Replace("_", "0");
		sMessage.Format(theApp.GetMessageString(IDS_CERCARE_FICHA_IN_ALTRE_SEDI), sFicha.Left(10), sItem);

		if (theApp.AfxMessageBoxEndo(sMessage, MB_YESNO) == IDYES)
		{
			//Julio Modeless
			CWaitFleuryTransferitoDlg* splashDlg = NULL;
			splashDlg = new CWaitFleuryTransferitoDlg();
			splashDlg->CreateModelessDialog(this);
			//

			DWORD time0 = timeGetTime();
			XWriteLogTime("RICERCA_PAZIENTE_FICHA " + sFicha + " INIZIO", 0, 0);

			CString sErrore;
			CString sServer;
			CString sUO;
			CString sEndpointRemoteCommunication;

			DWORD time2 = timeGetTime();
			if (FleuryCercaFicha(sFicha, sErrore, sServer, sUO, sEndpointRemoteCommunication))
			{
				XWriteLogTime("   FleuryCercaFicha", timeGetTime() - time2, timeGetTime() - time0);

				if (sUO.CompareNoCase(CUOSet().GetCodiceIntegrazione(theApp.m_lUO, FALSE)) == 0)
				{
					if (sServer == theApp.m_sCodiceUnitaFleury)
					{
						//CString sMesErr;
						//sMesErr.Format(theApp.GetMessageString(IDS_FLEURY_ERROR_029), sFicha);
						//theApp.AfxMessageBoxEndo(sMesErr);
						CListaPrenotazioniCupDlg dlg(this, this, 0, sFicha.Left(10));
						dlg.DoModal();

						//Julio 27/11/2017 Modeless
						splashDlg->ShowWindow(SW_HIDE);
						splashDlg->DestroyWindow();
						splashDlg = NULL;
						delete splashDlg;


						return;
					}
					else
					{
						long lIDPaziente = 0;
						long lIDEsame = 0;

						DWORD time3 = timeGetTime();
						if (FleuryGetPazienteEsame(this, this, sEndpointRemoteCommunication, sFicha, sErrore, lIDPaziente, lIDEsame))
						{
							if (sErrore == "FROM WORKLIST")
							{
								if (FleurySetEsameTrasferitoAltraSede(sEndpointRemoteCommunication, sFicha, sErrore))
								{
									CListaPrenotazioniCupDlg dlg(this, this, 0, sFicha.Left(10));
									dlg.DoModal();

									//Julio 27/11/2017 Modeless
									splashDlg->ShowWindow(SW_HIDE);
									splashDlg->DestroyWindow();
									splashDlg = NULL;
									delete splashDlg;

									return;
								}
							}

							XWriteLogTime("   FleuryGetPazienteEsame", timeGetTime() - time3, timeGetTime() - time0);

							if ((lIDPaziente > 0) && (lIDEsame > 0))
							{
								CString sErrore2 = "";

								DWORD time4 = timeGetTime();
								if (FleurySetEsameTrasferitoAltraSede(sEndpointRemoteCommunication, sFicha, sErrore2))
								{
									XWriteLogTime("   FleurySetEsameTrasferitoAltraSede", timeGetTime() - time4, timeGetTime() - time0);

									DWORD time5 = timeGetTime();
									BOOL bOK = RicercaCodicePaziente(lIDPaziente, lIDEsame, FALSE, FALSE);
									XWriteLogTime("   RicercaCodicePaziente", timeGetTime() - time5, timeGetTime() - time0);

									DWORD time6 = timeGetTime();
									MovePazientiAndEsami(NULL, !bOK, TRUE);
									XWriteLogTime("   MovePazientiAndEsami", timeGetTime() - time6, timeGetTime() - time0);

									// Sandro 17/07/2017 // importo le immagini...

									AfxBeginThread(CopyImagesFromRemotePath, this);
								}
								else
								{
									XWriteLogTime("   FleurySetEsameTrasferitoAltraSede", timeGetTime() - time4, timeGetTime() - time0);

									CString sFilterDel;
									sFilterDel.Format("CONTATORE = %li", lIDEsame);

									CEsamiSet setExamDel;
									setExamDel.SetOpenFilter(sFilterDel);
									if (setExamDel.OpenRecordset("OnPazienteGoto"))
									{
										if (!setExamDel.IsEOF())
											setExamDel.DeleteRecordset("OnPazienteGoto");

										setExamDel.CloseRecordset("OnPazienteGoto");
									}
								}

								if (!sErrore2.IsEmpty())
									theApp.AfxMessageBoxEndo(sErrore2);
							}
						}
						else
						{
							XWriteLogTime("   FleuryGetPazienteEsame", timeGetTime() - time3, timeGetTime() - time0);

							if (!sErrore.IsEmpty())//Julio 3/12/2017 nao importar exame se deu erro
							{
								theApp.AfxMessageBoxEndo(sErrore);
								sErrore = theApp.GetMessageString(IDS_FLEURY_ERROR_028);

								if (lIDEsame > 0)
								{
									CString sFilter;
									CEsamiSet setExa3;
									sFilter.Format("CONTATORE = %li", lIDEsame);
									setExa3.SetOpenFilter(sFilter);

									if (setExa3.OpenRecordset("FleuryGetPazienteEsame"))
									{
										if (setExa3.EditRecordset("FleuryGetPazienteEsame"))
										{
											setExa3.m_bEliminato = TRUE;
											if (!setExa3.UpdateRecordset("FleuryGetPazienteEsame"))
												theApp.AfxMessageBoxEndo(sErrore);
										}
										else
										{
											theApp.AfxMessageBoxEndo(sErrore);
										}
										setExa3.CloseRecordset("FleuryGetPazienteEsame");
									}
									else
									{
										theApp.AfxMessageBoxEndo(sErrore);
									}
								}
							}
						}
					}
				}
				else
				{
					//Julio 27/11/2017 : alterar a uo automaticamente
					CString sMessage;

					sMessage.Format(theApp.GetMessageString(IDS_ESAMIVIEW_EXAMCODESAMEFOUND_DIFFERENTEXTERNALUO), sFicha, sServer, sUO);
					if (theApp.AfxMessageBoxEndo(sMessage, MB_YESNO) == IDYES)
					{
						long lPrevUO = theApp.m_lUO;
						long lUserID;
						AMLogin_GetUserID(&lUserID);

						CUOUtenteDlg(this, lUserID).DoModal();

						if (theApp.m_lUO <= 0)
						{
							theApp.AfxMessageBoxEndo("Ocorreu um erro ao tentar alterar a unidade operativa");
							theApp.m_lUO = lPrevUO;
						}
						else
						{
							BeginWaitCursor();
							RicaricaDatiDopoCambioUO();
							OnPazienteLast();
							EndWaitCursor();
						}
					}
				}
			}
			else
			{
				XWriteLogTime("   FleuryCercaFicha", timeGetTime() - time2, timeGetTime() - time0);

				if (sErrore.IsEmpty())
				{
					CString sMessage = theApp.GetMessageString(IDS_FLEURY_ERROR_030);
					sMessage.Format(sMessage, sFicha);
					theApp.AfxMessageBoxEndo(sMessage);
				}
				else
					theApp.AfxMessageBoxEndo(sErrore);
			}

			XWriteLogTime("RICERCA_PAZIENTE_FICHA " + sFicha + " FINE", 0, timeGetTime() - time0);

			//Julio 27/11/2017 Modeless
			splashDlg->ShowWindow(SW_HIDE);
			splashDlg->DestroyWindow();
			splashDlg = NULL;
			delete splashDlg;
			//
		}
		break;
	}
	case 1:
	{
		DWORD time2 = timeGetTime();
		MovePazientiAndEsami(NULL, FALSE, TRUE);
		XWriteLogTime("   MovePazientiAndEsami", timeGetTime() - time2, 0);

		break;
	}
	}
}

void CEsamiView::OnPazienteNext()
{
	MovePazientiAndEsami(ID_RECORD_NEXT, TRUE, TRUE);
}

void CEsamiView::OnPazienteLast()
{
	MovePazientiAndEsami(ID_RECORD_LAST, TRUE, TRUE);
}

void CEsamiView::RicaricaDatiDopoCambioUO()
{

	//16052 Simone - Carico la lista dei gruppi a cui appartiene l'utente e i privilegi sulle fasi. Deve essere fatto qui per il FleuryUserCodeCheck() del cazzo
	((CEsamiDoc*)m_pDocument)->LoadUserGroups();
	((CEsamiDoc*)m_pDocument)->LoadEnabledPhaseForUser();


	//Julio Login SEGU
	if (theApp.m_bPersonalizzazioniBrasileFleury && (theApp.m_sUtenteLoggato != "SAT") && (theApp.m_sUtenteLoggato != "ADMINISTRATOR") && !FleuryGetHealthProfessional()/*!FleuryUserCodeCheck()*/)
	{
		AMLogin_Logout();
		theApp.m_lUO = 0; // Sandro 16/11/2015 // RAS 201500080 //
		AfxGetMainWnd()->PostMessage(WM_CLOSE);
	}


	// Sandro 26/11/2014 //
	CSediEsameSet().VerificaSedeDefault();

	// Sandro 23/03/2016 //
	if (theApp.m_lLoginMode > 0)
	{
		theApp.m_dwPrivileges = GetUpdatedPrivileges();
		AMLogin_SetUserPermission(theApp.m_dwPrivileges);
	}

	AssociaRecordset();

	// Sandro 10/12/2013 //
	MovePazientiAndEsami(NULL, TRUE, TRUE);

	((CEsamiDoc*)m_pDocument)->SetTitle(theApp.GetAppTitle(0));

	//

	if (GetDocument()->LeggiConfigurazioniEImpostaSoftware())
	{
		LeggiEtichette();

		//

		if (m_pImgManager != NULL)
		{
			delete m_pImgManager;
			m_pImgManager = NULL;
		}

		m_pImgManager = new CImgManager(theApp.m_sPathImageOD, &theApp.m_dbEndox);
		if (theApp.m_nApplication == PRG_CARDIOX)
		{
			m_pImgManager->SetThumbStoreSize(CSize(HSIZE_PAL / 2, VSIZE_PAL / 2));
			m_pImgManager->SetThumbRetrieveSize(CSize(HSIZE_PAL / 2, VSIZE_PAL / 2));
		}
		else
		{
			m_pImgManager->SetThumbStoreSize(CSize(HSIZE_PAL / 4, VSIZE_PAL / 4));
			m_pImgManager->SetThumbRetrieveSize(CSize(HSIZE_PAL / 4, VSIZE_PAL / 4));
		}
		m_pImgManager->SetImageExt(CString(EXT_IMG).Right(3));
		m_pImgManager->SetThumbExt(CString(EXT_WIN).Right(3));

		m_pImgManager->SetMovieBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_FILM)), RGB(255, 255, 255));				// WHITE
		m_pImgManager->SetTiffBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_TIFF)), RGB(255, 255, 255));				// WHITE
		m_pImgManager->SetPrintBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_PRINT)), RGB(255, 0, 0), bottomright);		// RED
		m_pImgManager->SetSelectBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_SELEZIONE)), RGB(0, 255, 0), topleft);	// NEON GREEN
		m_pImgManager->SetDicomBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DICOM_IMM)), RGB(255, 255, 255));			// WHITE
		m_pImgManager->SetDicomMovieBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DICOM_FILM)), RGB(255, 255, 255));	// WHITE
		m_pImgManager->SetCIBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_ICON_CI)), RGB(255, 255, 255));				// WHITE
		m_pImgManager->SetImageQuality(theApp.m_nArchivioImmaginiQualita, theApp.m_nArchivioMiniatureQualita, 100);

		//

		if (m_pDocManager != NULL)
		{
			delete m_pDocManager;
			m_pDocManager = NULL;
		}

		m_pDocManager = new CMyDocManager();

		// carico in memoria la lista dei comuni //
		CComuniBulkSet().CaricaInMemoria();

		// carico in memoria la lista dei medici curanti //
		CMediciCurantiInviantiBulkSet(MEDICI_CURANTI).CaricaInMemoria();

		// carico in memoria la lista dei medici invianti //
		CMediciCurantiInviantiBulkSet(MEDICI_INVIANTI).CaricaInMemoria();

		// carico in memoria i gruppi di prestazioni regionali //
		CCodificaRegionaleGruppiBulkSet().CaricaInMemoria();

		// carico in memoria i gruppi dei farmaci per la ricetta //
		CFarmaciGruppiRicBulkSet().CaricaInMemoria();

		// carico in memoria il tariffario regionale //
		CCodificaRegionaleExBulkSet().CaricaInMemoria();

		// carico in memoria i farmaci //
		CFarmaciBulkSet().CaricaInMemoria();

		// carico in memoria i campi della worklist //
		if (theApp.m_bPrenotazioniCup)
			CCupWorkListManager::LoadIntoMemory();

		MoveRecord(ID_RECORD_LAST);

		GetDlgItem(IDC_LABEL_STATO)->SetFont(&theApp.m_fontBig, TRUE);
		GetDlgItem(IDC_LABEL_STATO_NEW1)->SetFont(&theApp.m_fontBig, TRUE);
		GetDlgItem(IDC_LABEL_STATO_NEW2)->SetFont(&theApp.m_fontBig, TRUE);
		GetDlgItem(IDC_LABEL_STATO_NEW3)->SetFont(&theApp.m_fontBig, TRUE);
		GetDlgItem(IDC_LABEL_STATO_NEW4)->SetFont(&theApp.m_fontBig, TRUE);
	}
	else
	{
		AfxGetMainWnd()->PostMessage(WM_CLOSE);
	}
}

BOOL CEsamiView::RicercaCodicePaziente(long lPaziente, long lEsame, BOOL bSafeValue, BOOL bVerbose)
{
	CPazientiSet setPazienti;

	if (bSafeValue)
		setPazienti.CopyFieldFrom(m_pPazientiSet);

	if (m_pPazientiSet->RequeryRecordset())
	{
		if (PazienteSetFind(m_pPazientiSet, lPaziente))
		{
			if ((bSafeValue && lEsame == 0) || RicercaContatoreEsame(lEsame, bSafeValue))
			{
				if (bSafeValue)
					m_pPazientiSet->CopyFieldFrom(&setPazienti);

				return TRUE;
			}
		}
		else
		{
			if (bVerbose)
			{
				CString strTmp;
				strTmp.Format(theApp.GetMessageString(IDS_ESAMIVIEW_PATIENTID_NOT_FOUND), lPaziente);
				theApp.AfxMessageBoxEndo(strTmp);
			}
		}
	}
	else
	{
		m_pPazientiSet->OpenRecordset("CEsamiView::RicercaCodicePaziente", TRUE, TRUE);
	}

	return FALSE;
}

// ritorna:
// -3 --> errore durante il posizionamento sull'esame trovato
// -2 --> esame trovato ma appartenente ad altra UO
// -1 --> esame trovato ma eliminato
//  0 --> esame non trovato nel DB
//  1 --> tutto OK
long CEsamiView::RicercaCodicePazienteCodEsameEx(CString sCodEsame)
{
	long lReturn = 0;

	sCodEsame.Replace("'", "''");
	sCodEsame.MakeUpper();

	CEsamiSet setEsami;
	setEsami.SetBaseFilter("(ELIMINATO = 0 OR ELIMINATO = 1) AND UO > 0");
	setEsami.SetOpenFilter("UPPER(CodEsame) LIKE '" + sCodEsame + "'");
	setEsami.SetSortRecord("CONTATORE DESC");
	if (setEsami.OpenRecordset("CEsamiView::RicercaCodicePazienteCodEsame"))
	{
		if (!setEsami.IsEOF())
		{
			if (setEsami.m_bEliminato)
			{
				CString sError;
				sError.Format(theApp.GetMessageString(IDS_ESAMIVIEW_EXAMCODESAME_DELETED), sCodEsame);
				theApp.AfxMessageBoxEndo(sError);

				lReturn = -1;
			}
			else if (setEsami.m_lUO != theApp.m_lUO)
			{
				CString sError;
				sError.Format(theApp.GetMessageString(IDS_ESAMIVIEW_EXAMCODESAME_DIFFERENT_UO), sCodEsame, CUOSet().GetDescrizione(setEsami.m_lUO));
				theApp.AfxMessageBoxEndo(sError);

				lReturn = -2;
			}
			else
			{
				if (!setEsami.m_sFleuryTrasferito.IsEmpty() && setEsami.m_sFleuryTrasferito != "-1")
				{
					// se l'esame è già stato trasferito presso altra sede del Fleury faccio finta di non trovarlo in locale così mi chiede di riportarlo qui //
					lReturn = 0;
				}
				else
				{
					if (!RicercaCodicePaziente(setEsami.m_lPaziente, setEsami.m_lContatore, FALSE, TRUE))
					{
						CString sError;
						sError.Format(theApp.GetMessageString(IDS_ESAMIVIEW_EXAMCODESAME_NOT_FOUND), sCodEsame);
						theApp.AfxMessageBoxEndo(sError);

						lReturn = -3;
					}
					else
					{
						lReturn = 1;
					}
				}
			}
		}

		setEsami.CloseRecordset("CEsamiView::RicercaCodicePazienteCodEsame");
	}

	return lReturn;
}

BOOL CEsamiView::RicercaCodicePazienteAssiden(CString sAssiden)
{
	BOOL bReturn = FALSE;

	sAssiden.Replace("'", "''");
	sAssiden.MakeUpper();

	CString sFilter = "UPPER(Assiden) LIKE '" + sAssiden + "' AND Eliminato=0";

	CPazientiSet setPazAct;
	setPazAct.SetOpenFilter(sFilter);
	if (setPazAct.OpenRecordset("CEsamiView::RicercaCodicePazienteAssiden"))
	{
		long lIDPaziente = 0;

		//

		if (!setPazAct.IsEOF())
			lIDPaziente = setPazAct.m_lContatore;

		//

		if (lIDPaziente <= 0)
		{
			// ricerca su tabella storico //

			CPazientiStoricoSet setPazStor;
			setPazStor.SetOpenFilter(sFilter);
			if (setPazStor.OpenRecordset("CEsamiView::RicercaCodicePazienteAssiden"))
			{
				if (!setPazStor.IsEOF())
					lIDPaziente = setPazStor.m_lIdPaziente;

				setPazStor.CloseRecordset("CEsamiView::RicercaCodicePazienteAssiden");
			}
		}

		//

		if (lIDPaziente > 0)
			bReturn = RicercaCodicePaziente(lIDPaziente, 0, FALSE, TRUE);

		//

		setPazAct.CloseRecordset("CEsamiView::RicercaCodicePazienteAssiden");
	}

	if (!bReturn)
	{
		CString sError;
		sError.Format(theApp.GetMessageString(IDS_ESAMIVIEW_PATIENTASSIDEN_NOT_FOUND), sAssiden);
		theApp.AfxMessageBoxEndo(sError);
	}

	return bReturn;
}

BOOL CEsamiView::RicercaCodicePazienteCodiceRicovero(CString sCodiceRicovero, BOOL bShowError)
{
	BOOL bReturn = FALSE;

	sCodiceRicovero.Replace("'", "''");
	sCodiceRicovero.MakeUpper();

	// Sandro 06/07/2015 // RIMA 15052.2 //
	if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury)
		sCodiceRicovero = sCodiceRicovero.Left(10);

	CEsamiSet setEsami;
	setEsami.SetOpenFilter("UPPER(Ricovero) LIKE '" + sCodiceRicovero + "' AND Eliminato=0");
	if (setEsami.OpenRecordset("CEsamiView::RicercaCodicePazienteAssiden"))
	{
		if (!setEsami.IsEOF())
			bReturn = RicercaCodicePaziente(setEsami.m_lPaziente, setEsami.m_lContatore, FALSE, TRUE);

		setEsami.CloseRecordset("CEsamiView::RicercaCodicePazienteAssiden");
	}

	if (!bReturn && bShowError)
	{
		CString sError;
		sError.Format(theApp.GetMessageString(IDS_ESAMIVIEW_PATIENTCODRIC_NOT_FOUND), sCodiceRicovero);
		theApp.AfxMessageBoxEndo(sError);
	}

	return bReturn;
}

BOOL CEsamiView::RicercaContatoreEsame(long lContatore, BOOL bSafeValue)
{
	CEsamiSet TempEsami;

	if (bSafeValue)
		TempEsami.CopyFieldFrom(m_pEsamiSet);

	BOOL bContinue = TRUE;

	/*#ifdef _LOG_DB
	CLogFileWriter::Get()->WriteLogLine("   FiltraEsami()");
	#endif // _LOG_DB //*/
	FiltraEsami();

	if (lContatore > 0)
	{
		if (!m_pEsamiSet->GotoExam(lContatore) || m_pEsamiSet->m_lContatore != lContatore)
		{
			ASSERT(FALSE);
			MoveEsamiRecordset(ID_RECORD_LAST);

			if (lContatore > 0)
			{
				while (bContinue && !m_pEsamiSet->IsBOF() && (m_pEsamiSet->m_lContatore != lContatore))
					bContinue = MoveEsamiRecordset(ID_RECORD_PREV);
			}

			if (m_pEsamiSet->IsBOF())
				MoveEsamiRecordset(ID_RECORD_FIRST);
		}
	}
	else
	{
		MoveEsamiRecordset(ID_RECORD_LAST);
	}

	if (lContatore != 0)
	{
		if (m_pEsamiSet->IsBOF() || m_pEsamiSet->m_lContatore != lContatore)
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_BASEFORM_ERR_DELETED));
			return FALSE;
		}
	}

	if (bSafeValue)
		m_pEsamiSet->CopyFieldFrom(&TempEsami);

	return TRUE;
}

void CEsamiView::NascondiMenuEndox()
{
	CMenu* pMainMenu = AfxGetMainWnd()->GetMenu();
	if (pMainMenu != NULL)
	{
		CMenu* pMenuFile = pMainMenu->GetSubMenu(0); // File //
		CMenu* pMenuEsameCorrente = pMainMenu->GetSubMenu(1); // Esame corrente //
		CMenu* pMenuGestione = pMainMenu->GetSubMenu(2); // Gestione //
		CMenu* pMenuArchivi = pMainMenu->GetSubMenu(3); // Archivi //
		CMenu* pMenuSalaIntegrata = pMainMenu->GetSubMenu(4); // Connessione remota //
		CMenu* pMenuOpzioni = pMainMenu->GetSubMenu(5); // Opzioni //
		CMenu* pMenuTutorialFiles = pMainMenu->GetSubMenu(6);
		CMenu* pMenuHelp = pMainMenu->GetSubMenu(7); // ? (Help) //

		if (theApp.m_bCentraleStampa)
		{
			pMainMenu->DeleteMenu(4, MF_BYPOSITION);
			pMainMenu->DeleteMenu(3, MF_BYPOSITION);
			pMainMenu->DeleteMenu(2, MF_BYPOSITION);
			pMainMenu->DeleteMenu(1, MF_BYPOSITION);

			if (pMenuFile != NULL)
				NascondiMenuEndoxFile(pMenuFile);

			if (pMenuOpzioni != NULL)
				NascondiMenuEndoxOpzioni(pMenuOpzioni);

			if (pMenuTutorialFiles != NULL)
			{
				pMenuTutorialFiles->DeleteMenu(0, MF_BYPOSITION);

				BOOL bDeleteTF = TRUE;
				CTutorialFilesSet setTempTF;
				if (setTempTF.OpenRecordset("CEsamiView::NascondiMenuEndox"))
				{
					long lMy = 0;
					while (!setTempTF.IsEOF())
					{
						pMenuTutorialFiles->InsertMenu(lMy, MF_BYPOSITION, MENU_TUTORIAL_FILES + setTempTF.m_lID, setTempTF.m_sDescrizione);

						bDeleteTF = FALSE;
						lMy++;
						setTempTF.MoveNext();
					}

					setTempTF.CloseRecordset("CEsamiView::NascondiMenuEndox");
				}
				if (bDeleteTF)
					pMainMenu->DeleteMenu(6, MF_BYPOSITION); // Tutorial //
			}

			if (pMenuHelp != NULL)
				pMenuHelp->DeleteMenu(ID_HELP, MF_BYCOMMAND);
		}
		else
		{
			//////////
			// FILE //
			//////////

			if (pMenuFile != NULL)
				NascondiMenuEndoxFile(pMenuFile);

			////////////////////
			// ESAME CORRENTE //
			////////////////////

			if (pMenuEsameCorrente != NULL)
			{
				pMenuEsameCorrente->AppendMenu(MF_SEPARATOR, -1);

				CMenu newMenuChiusuraFase;
				newMenuChiusuraFase.CreateMenu();

				CMenu newMenuAnnullaChiusuraFase;
				newMenuAnnullaChiusuraFase.CreateMenu();

				CString sFilter;

				//Julio Ordem Fechamento/Desbloqueio de fases
				CFasiEsameSet fasiEsameSet;
				fasiEsameSet.SetSortRecord("ID DESC");
				if (fasiEsameSet.OpenRecordset("CEsamiView::NascondiMenuEndox"))
				{
					while (!fasiEsameSet.IsEOF())
					{
						newMenuChiusuraFase.AppendMenu(MF_STRING, fasiEsameSet.m_lID + FASI_ESAME, fasiEsameSet.m_sDescrizione);
						fasiEsameSet.MoveNext();
					}

					fasiEsameSet.CloseRecordset("CEsamiView::NascondiMenuEndox");
				}
				fasiEsameSet.SetSortRecord("ID ASC");
				if (fasiEsameSet.OpenRecordset("CEsamiView::NascondiMenuEndox"))
				{
					while (!fasiEsameSet.IsEOF())
					{
						newMenuAnnullaChiusuraFase.AppendMenu(MF_STRING, fasiEsameSet.m_lID + FASI_ESAME + 1000, fasiEsameSet.m_sDescrizione);
						fasiEsameSet.MoveNext();
					}

					fasiEsameSet.CloseRecordset("CEsamiView::NascondiMenuEndox");
				}
				//


				TCHAR szBuffer[255];

				//CHIUSURA			
				strcpy_s(szBuffer, theApp.GetMessageString(IDS_CHIUSURA_FASE));

				MENUITEMINFO menuiteminfoChiusura;
				menuiteminfoChiusura.cbSize = sizeof(MENUITEMINFO);
				menuiteminfoChiusura.fMask = MIIM_ID | MIIM_FTYPE | MIIM_STRING | MIIM_SUBMENU;
				menuiteminfoChiusura.wID = -1;
				menuiteminfoChiusura.fType = MFT_STRING;
				menuiteminfoChiusura.cch = 255;
				menuiteminfoChiusura.dwTypeData = szBuffer;
				menuiteminfoChiusura.hSubMenu = newMenuChiusuraFase.Detach();
				pMenuEsameCorrente->InsertMenuItem(pMenuEsameCorrente->GetMenuItemCount(), &menuiteminfoChiusura, TRUE);

				//ANNULLA CHIUSURA			
				strcpy_s(szBuffer, theApp.GetMessageString(IDS_ANNULLA_CHIUSURA_FASE));

				MENUITEMINFO menuiteminfoAnnullaChiusura;
				menuiteminfoAnnullaChiusura.cbSize = sizeof(MENUITEMINFO);
				menuiteminfoAnnullaChiusura.fMask = MIIM_ID | MIIM_FTYPE | MIIM_STRING | MIIM_SUBMENU;
				menuiteminfoAnnullaChiusura.wID = -1;
				menuiteminfoAnnullaChiusura.fType = MFT_STRING;
				menuiteminfoAnnullaChiusura.cch = 255;
				menuiteminfoAnnullaChiusura.dwTypeData = szBuffer;
				menuiteminfoAnnullaChiusura.hSubMenu = newMenuAnnullaChiusuraFase.Detach();
				pMenuEsameCorrente->InsertMenuItem(pMenuEsameCorrente->GetMenuItemCount(), &menuiteminfoAnnullaChiusura, TRUE);
			}

			//////////////
			// GESTIONE //
			//////////////

			if (pMenuGestione != NULL)
			{
				NascondiMenuEndoxGestione(pMenuGestione);

				// se vuoto cancello completamente il menu gestione //
				if (pMenuGestione->GetMenuItemCount() == 0)
					pMainMenu->DeleteMenu(1, MF_BYPOSITION);
			}

			/////////////
			// ARCHIVI //
			/////////////

			if (pMenuArchivi != NULL)
				NascondiMenuEndoxArchivi(pMenuArchivi);

			/////////////
			// OPZIONI //
			/////////////

			if (pMenuOpzioni != NULL)
				NascondiMenuEndoxOpzioni(pMenuOpzioni);

			////////////////////////
			// CONNESSIONE REMOTA //
			////////////////////////

			BOOL bDeleteCR = TRUE;
			CSorgentiStreamingSet setTempCR;
			if (setTempCR.OpenRecordset("CEsamiView::NascondiMenuEndox"))
			{
				if (!setTempCR.IsEOF())
					bDeleteCR = FALSE;

				setTempCR.CloseRecordset("CEsamiView::NascondiMenuEndox");
			}
			if ((bDeleteCR) || !(theApp.m_dwPrivileges & AMLogin_Permissions::modify_image ? TRUE : FALSE))
				pMainMenu->DeleteMenu(ID_CONNESSIONEREMOTA, MF_BYCOMMAND); // Connessione remota //

			//////////////
			// TUTORIAL //
			//////////////

			if (pMenuTutorialFiles != NULL)
			{
				pMenuTutorialFiles->DeleteMenu(0, MF_BYPOSITION);

				BOOL bDeleteTF = TRUE;
				CTutorialFilesSet setTempTF;
				if (setTempTF.OpenRecordset("CEsamiView::NascondiMenuEndox"))
				{
					long lMy = 0;
					while (!setTempTF.IsEOF())
					{
						pMenuTutorialFiles->InsertMenu(lMy, MF_BYPOSITION, MENU_TUTORIAL_FILES + setTempTF.m_lID, setTempTF.m_sDescrizione);

						bDeleteTF = FALSE;
						lMy++;
						setTempTF.MoveNext();
					}

					setTempTF.CloseRecordset("CEsamiView::NascondiMenuEndox");
				}
				if (bDeleteTF)
					pMainMenu->DeleteMenu(6, MF_BYPOSITION); // Tutorial //
			}
		}
	}
}

void CEsamiView::NascondiMenuEndoxFile(CMenu* pMenu)
{
	if (theApp.m_bCentraleStampa)
	{
		pMenu->DeleteMenu(15, MF_BYPOSITION);

		pMenu->DeleteMenu(ID_INFO_USER, MF_BYCOMMAND);
		pMenu->DeleteMenu(ID_FILE_CAMBIOUO, MF_BYCOMMAND);
		pMenu->DeleteMenu(ID_FILE_CAMBIOPASSWORDELIMINAZIONEPDF, MF_BYCOMMAND);
		pMenu->DeleteMenu(ID_FILE_STAMPAIMMAGINI, MF_BYCOMMAND);
		pMenu->DeleteMenu(ID_FILE_ANTEPRIMAIMMAGINI, MF_BYCOMMAND);
		pMenu->DeleteMenu(ID_FILE_STAMPAREPORT, MF_BYCOMMAND);
		pMenu->DeleteMenu(ID_FILE_ANTEPRIMAREPORT, MF_BYCOMMAND);
		pMenu->DeleteMenu(ID_FILE_STAMPAETICHETTE, MF_BYCOMMAND);

#ifndef _DEBUG
		pMenu->DeleteMenu(ID_FILE_INTESTAZIONEREFERTO, MF_BYCOMMAND);
#endif

		pMenu->DeleteMenu(ID_FILE_IMPOSTAPAGINA, MF_BYCOMMAND);
		pMenu->DeleteMenu(ID_FILE_SELTWAIN, MF_BYCOMMAND);
		pMenu->DeleteMenu(ID_FILE_INQUIERO_1, MF_BYCOMMAND);
		pMenu->DeleteMenu(ID_FILE_INQUIERO_2, MF_BYCOMMAND);
	}
	else
	{
		// Sandro 10/11/2010 - RAS 20100132 //
		// PRIMA aggiungo le nuove voci per la stampa delle etichette //

		CMenu* pMenuEtichette = pMenu->GetSubMenu(15); // Stampa etichette //
		if (pMenuEtichette != NULL)
		{
			if (!RiempiMenuEndoxFileEtichette(pMenuEtichette))
				pMenu->DeleteMenu(15, MF_BYPOSITION);
		}

		// DOPO eventualmente cancello le altre voci superflue //

		if (!CUOSet().ExistMoreThanOneUO())
			pMenu->DeleteMenu(ID_FILE_CAMBIOUO, MF_BYCOMMAND); // Cambio UO... //

		if (!theApp.m_bCanAcquire)
			pMenu->DeleteMenu(ID_FILE_SELTWAIN, MF_BYCOMMAND); // Seleziona sorgente TWAIN... //

		pMenu->DeleteMenu(ID_FILE_STAMPAETICHETTE, MF_BYCOMMAND); // Stampa etichette... //
	}

	NascondiSeparatori(pMenu);
}

BOOL CEsamiView::RiempiMenuEndoxFileEtichette(CMenu* pMenu)
{
	long l = 0;

	CReportsEtichetteSet setRepEti;
	if (setRepEti.OpenRecordset("CEsamiView::NascondiMenuEndoxFile"))
	{
		while (!setRepEti.IsEOF())
		{
			pMenu->InsertMenu(l, MF_BYPOSITION, MENU_STAMPA_ETICHETTE + setRepEti.m_lID, setRepEti.m_sDescrizioneMenu);

			l++;
			setRepEti.MoveNext();
		}
		setRepEti.CloseRecordset("CEsamiView::NascondiMenuEndoxFile");
	}

	NascondiSeparatori(pMenu);
	return (l > 0);
}

void CEsamiView::NascondiMenuEndoxGestione(CMenu* pMenu)
{
	if (!theApp.m_bNomenclatore)
		pMenu->DeleteMenu(ID_GESTIONE_NOMENCLATORE, MF_BYCOMMAND);

	if (!theApp.m_bInterfacciaMetafora && (theApp.m_lInterfacciaPathox <= 0))
		pMenu->DeleteMenu(ID_GESTIONE_SOSPESIISTOLOGICI, MF_BYCOMMAND);

	pMenu->DeleteMenu(ID_GESTIONE_LISTASOSPESI, MF_BYCOMMAND);

	if (!theApp.m_bPersonalizzazioniBrasileEinstein)
		pMenu->DeleteMenu(ID_GESTIONE_VISUALIZZATORELOGIMPORTAZIONECASI, MF_BYCOMMAND);

	if (!theApp.m_bPersonalizzazioniBrasileSirio)
		pMenu->DeleteMenu(ID_GESTIONE_INVIAVIDEO, MF_BYCOMMAND);

	if (!theApp.m_bMostraMenuDatabasesRemoti || !theApp.m_sPassedConnectionString.IsEmpty())
		pMenu->DeleteMenu(ID_GESTIONE_ACCESSOSEDIESTERNE, MF_BYCOMMAND);

	//	if (!theApp.m_bPersonalizzazioniBrasileFleury || !m_pEsamiSet->IsConiugatoPrincipaleSecondario(m_pEsamiSet->m_sCodEsame))
	//	pMenu->DeleteMenu(ID_ESAMECORRENTE_DESCONJUGARITENS, MF_BYCOMMAND);

	NascondiSeparatori(pMenu);
}

void CEsamiView::NascondiMenuEndoxArchivi(CMenu* pMenuNew)
{
	CMenu* pPazientiCroniciMenu = pMenuNew->GetSubMenu(0);			// Pazienti cronici //
	CMenu* pEsamiPrestazioniOrganiMenu = pMenuNew->GetSubMenu(1);	// Esami, prestazioni, organi //
	CMenu* pFrasiMenu = pMenuNew->GetSubMenu(2);					// Frasi //
	CMenu* pStrumentiAccessoriMenu = pMenuNew->GetSubMenu(3);		// Strumenti e accessori //
	CMenu* pEtichetteMenu = pMenuNew->GetSubMenu(4);				// Etichette //
	CMenu* pFarmaciMenu = pMenuNew->GetSubMenu(5);					// Farmaci //
	CMenu* pTabelleMstMenu = pMenuNew->GetSubMenu(6);				// Tabelle MST //
	CMenu* pIcd9Menu = pMenuNew->GetSubMenu(7);						// ICD9 //
	CMenu* pScreeningMenu = pMenuNew->GetSubMenu(8);				// Screening //
	CMenu* pRicetteMenu = pMenuNew->GetSubMenu(9);					// Ricette //
	CMenu* pReportsMacroMenu = pMenuNew->GetSubMenu(10);			// Reports e macro di stampa //
	CMenu* pVariMenu = pMenuNew->GetSubMenu(11);					// Vari //
	// - //
	CMenu* pPersonaleMenu = pMenuNew->GetSubMenu(13);				// Personale //
	CMenu* pInviantiMenu = pMenuNew->GetSubMenu(14);				// Invianti //
	// - //
	CMenu* pBackupMenu = pMenuNew->GetSubMenu(16);					// Backup //

	CMenu* pGenomicaMenu = pMenuNew->GetSubMenu(24);				// Genomica // //Julio BUG 3249
	//

	if (theApp.m_lOpzionalePazientiCronici != OPZIONALE_PAZIENTI_CRONICI)
		pMenuNew->DeleteMenu(0, MF_BYPOSITION); // Pazienti cronici //

	//

	if (pFrasiMenu != NULL)
	{
		if (!theApp.m_bRefertazioneUsaFrasiRTF)
			pFrasiMenu->DeleteMenu(ID_ARCHIVI_FRASIRTF, MF_BYCOMMAND);

		if (!theApp.m_bRefertazioneUsaFrasiStandard)
			pFrasiMenu->DeleteMenu(ID_ARCHIVI_FRASISTANDARD, MF_BYCOMMAND);
	}

	//

	if (pTabelleMstMenu != NULL)
	{
		pTabelleMstMenu->DeleteMenu(ID_ARCHIVI_MST_OSSERVAZIONI_1, MF_BYCOMMAND); // Osservazioni (1)... //
		pTabelleMstMenu->DeleteMenu(ID_ARCHIVI_MST_OSSERVAZIONI_2, MF_BYCOMMAND); // Osservazioni (2)... //
		pTabelleMstMenu->DeleteMenu(ID_ARCHIVI_MST_OSSERVAZIONI_3, MF_BYCOMMAND); // Osservazioni (3)... //

		NascondiSeparatori(pTabelleMstMenu);
	}

	//

	if (pVariMenu != NULL)
	{
		if (theApp.m_nApplication == PRG_DERMOX)
			pVariMenu->DeleteMenu(ID_VARI_BOSTONSCORE, MF_BYCOMMAND); // Boston score... //
		else
			pVariMenu->DeleteMenu(ID_VARI_DIAGNOSIISTOLOGICA, MF_BYCOMMAND); // Diagnosi istologica... //

		if (theApp.m_bPersonalizzazioniBrasileFleury && !(theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_01))
			pVariMenu->DeleteMenu(ID_ARCHIVI_CHECKLIST, MF_BYCOMMAND); // Luiz - 11/03/2019 - P3 - Restringe acesso a construção de Checklist (fleury) somente para administradores

		NascondiSeparatori(pVariMenu);
	}

	//

	if (pBackupMenu != NULL)
	{
		switch (theApp.m_lBackupDVD)
		{
		case 0:
		{
			// pBackupMenu->DeleteMenu(ID_ARCHIVI_OCCUPAZIONEGIORNALIERA, MF_BYCOMMAND); // Occupazione giornaliera... //
			pBackupMenu->DeleteMenu(ID_ARCHIVI_BACKUPDATI, MF_BYCOMMAND); // Backup dati... //
			break;
		}
		case 1:
		{
			pBackupMenu->DeleteMenu(ID_ARCHIVI_TRASFERIMPARZIALE, MF_BYCOMMAND); // Trasferimento H.D. -> O.D. Scheda... //
			pBackupMenu->DeleteMenu(ID_ARCHIVI_TRASFERIMTOTALE, MF_BYCOMMAND); // Trasferimento H.D. -> O.D. Totale... //
			pBackupMenu->DeleteMenu(ID_ARCHIVI_ESPELLI_OD, MF_BYCOMMAND); // Espelli disco removibile //
			break;
		}
		case 2:
		{
			pBackupMenu->DeleteMenu(ID_ARCHIVI_TRASFERIMPARZIALE, MF_BYCOMMAND); // Trasferimento H.D. -> O.D. Scheda... //
			pBackupMenu->DeleteMenu(ID_ARCHIVI_TRASFERIMTOTALE, MF_BYCOMMAND); // Trasferimento H.D. -> O.D. Totale... //
			pBackupMenu->DeleteMenu(ID_ARCHIVI_ESPELLI_OD, MF_BYCOMMAND); // Espelli disco removibile //
			break;
		}
		}

		NascondiSeparatori(pBackupMenu);
	}

	//
	if (!theApp.m_bPersonalizzazioniBrasileEinstein)
		pMenuNew->DeleteMenu(ID_ARCHIVI_IMPORTACASO, MF_BYCOMMAND);

	// Sandro 14/07/2015 //
	if (!theApp.m_bPersonalizzazioniBrasileCamargo && !theApp.m_bPersonalizzazioniBrasileFleury)
	{
		pMenuNew->DeleteMenu(ID_ARCHIVI_ESAMEINTEGRATO, MF_BYCOMMAND);
		pMenuNew->DeleteMenu(ID_ARCHIVI_PARAMETRITABELLAECOCARDIOGRAFIA, MF_BYCOMMAND);
	}

	// Sandro 27/10/2015 // Commentato da Simone
	//pMenuNew->DeleteMenu(ID_ARCHIVI_COMMENTIIMMAGINI, MF_BYCOMMAND);

	//Julio BUG 3249
	if (!theApp.m_bUsaModuloGenomica)
		pMenuNew->DeleteMenu(24, MF_BYPOSITION);


	NascondiSeparatori(pMenuNew);
}

void CEsamiView::NascondiMenuEndoxOpzioni(CMenu* pMenu)
{
	if (theApp.m_bCentraleStampa)
	{
		pMenu->DeleteMenu(ID_OPTION_ORGAN, MF_BYCOMMAND);
		pMenu->DeleteMenu(ID_OPTION_CALIB, MF_BYCOMMAND);
		pMenu->DeleteMenu(ID_OPTION_ACQ, MF_BYCOMMAND);
		pMenu->DeleteMenu(ID_OPTION_WEB, MF_BYCOMMAND);
		pMenu->DeleteMenu(ID_OPZIONI_SETUPCOLORI, MF_BYCOMMAND);
		pMenu->DeleteMenu(ID_OPZIONI_INTEGRAZIONI, MF_BYCOMMAND);
		pMenu->DeleteMenu(ID_OPTION_OPERATOR, MF_BYCOMMAND);
		pMenu->DeleteMenu(ID_OPTION_REPORT, MF_BYCOMMAND);
		pMenu->DeleteMenu(ID_OPTION_CAMPIOBBLIGATORI, MF_BYCOMMAND);
		pMenu->DeleteMenu(ID_OPZIONI_SETUPDATABASESREMOTI, MF_BYCOMMAND);
	}
	else
	{
		if (theApp.m_nApplication == PRG_DERMOX)
			pMenu->DeleteMenu(ID_OPTION_ORGAN, MF_BYCOMMAND);

		if (!theApp.m_bInterfacciaWeb)
			pMenu->DeleteMenu(ID_OPTION_WEB, MF_BYCOMMAND);

		if (theApp.m_nApplication != PRG_DERMOX)
			pMenu->DeleteMenu(ID_OPTION_CALIB, MF_BYCOMMAND);

		if (!theApp.m_bSISSMostraMenuDisattivaFirma)
			pMenu->DeleteMenu(ID_OPZIONI_DISATTIVAFIRMAPERQUESTOESAME, MF_BYCOMMAND);

		if (!theApp.m_bMostraMenuDatabasesRemoti || !theApp.m_sPassedConnectionString.IsEmpty())
			pMenu->DeleteMenu(ID_OPZIONI_SETUPDATABASESREMOTI, MF_BYCOMMAND);
	}

	NascondiSeparatori(pMenu);
}

void CEsamiView::NascondiMenuImageNT()
{
	CMenu* pMainMenu = AfxGetMainWnd()->GetMenu();
	if (pMainMenu != NULL)
	{
		CMenu* pMenuFile = pMainMenu->GetSubMenu(0); // File //
		CMenu* pMenuGestion = pMainMenu->GetSubMenu(1); // Gestione //
		CMenu* pMenuArchivi = pMainMenu->GetSubMenu(2); // Archivi //
		CMenu* pMenuOpzioni = pMainMenu->GetSubMenu(4); // Opzioni //
		CMenu* pMenuHelp = pMainMenu->GetSubMenu(5); // ? (Help) //

		//////////
		// FILE //
		//////////

		if (pMenuFile != NULL)
			NascondiMenuImageNTFile(pMenuFile);

		//////////////
		// GESTIONE //
		//////////////

		if (pMenuGestion != NULL)
		{
			NascondiMenuImageNTGestione(pMenuGestion);

			// se vuoto cancello completamente il menu gestione //
			if (pMenuGestion->GetMenuItemCount() == 0)
				pMainMenu->DeleteMenu(1, MF_BYPOSITION);
		}

		/////////////
		// ARCHIVI //
		/////////////

		if (pMenuArchivi != NULL)
			NascondiMenuImageNTArchivi(pMenuArchivi);

		/////////////
		// OPZIONI //
		/////////////

		if (pMenuOpzioni != NULL)
			NascondiMenuImageNTOpzioni(pMenuOpzioni);

		////////////////////////
		// CONNESSIONE REMOTA //
		////////////////////////

		BOOL bDelete = TRUE;
		CSorgentiStreamingSet setTemp;
		if (setTemp.OpenRecordset("CEsamiView::NascondiMenuImageNT"))
		{
			if (!setTemp.IsEOF())
				bDelete = FALSE;

			setTemp.CloseRecordset("CEsamiView::NascondiMenuImageNT");
		}
		if ((bDelete) || !(theApp.m_dwPrivileges & AMLogin_Permissions::modify_image ? TRUE : FALSE))
			pMainMenu->DeleteMenu(ID_CONNESSIONEREMOTA, MF_BYCOMMAND); // Connessione remota //
	}
}

void CEsamiView::NascondiMenuImageNTFile(CMenu* pMenu)
{
	pMenu->DeleteMenu(ID_FILE_STAMPAETICHETTE, MF_BYCOMMAND); // Stampa etichette... //

	if (!theApp.m_bCanAcquire)
		pMenu->DeleteMenu(ID_FILE_SELTWAIN, MF_BYCOMMAND); // Seleziona sorgente TWAIN... //

	pMenu->DeleteMenu(ID_FILE_INQUIERO_1, MF_BYCOMMAND); // Teleconsulto operatore //
	pMenu->DeleteMenu(ID_FILE_INQUIERO_2, MF_BYCOMMAND); // Teleconsulto client //

	NascondiSeparatori(pMenu);
}

void CEsamiView::NascondiMenuImageNTGestione(CMenu* pMenu)
{
	pMenu->DeleteMenu(ID_GESTIONE_NOMENCLATORE, MF_BYCOMMAND);
	pMenu->DeleteMenu(ID_GESTIONE_STATISTICHEESAMI, MF_BYCOMMAND);

	pMenu->DeleteMenu(ID_GESTIONE_SOSPESIISTOLOGICI, MF_BYCOMMAND);

	pMenu->DeleteMenu(ID_GESTIONE_LISTASOSPESI, MF_BYCOMMAND);

	NascondiSeparatori(pMenu);
}

void CEsamiView::NascondiMenuImageNTArchivi(CMenu* pMenu)
{
	CMenu* pMstMenu = pMenu->GetSubMenu(5); // Tabelle MST //
	if (pMstMenu != NULL)
	{
		pMstMenu->DeleteMenu(ID_ARCHIVI_MST_OSSERVAZIONI, MF_BYCOMMAND); // Osservazioni... //
		pMstMenu->DeleteMenu(ID_ARCHIVI_MST_OSSERVAZIONI_1, MF_BYCOMMAND); // Osservazioni (1)... //
		pMstMenu->DeleteMenu(ID_ARCHIVI_MST_OSSERVAZIONI_2, MF_BYCOMMAND); // Osservazioni (2)... //
		pMstMenu->DeleteMenu(ID_ARCHIVI_MST_OSSERVAZIONI_3, MF_BYCOMMAND); // Osservazioni (3)... //
		pMstMenu->DeleteMenu(ID_ARCHIVI_MST_PROCDIAGNOSTICHE, MF_BYCOMMAND); // Procedure diagnostiche... //
		pMstMenu->DeleteMenu(ID_ARCHIVI_MST_PROCTERAPEUTICHE, MF_BYCOMMAND); // Procedure terapeutiche... //
		pMstMenu->DeleteMenu(ID_ARCHIVI_MST_DIAGNOSI, MF_BYCOMMAND); // Diagnosi... //
		pMstMenu->DeleteMenu(ID_ARCHIVI_MST_CODDIAGNOSIESAME, MF_BYCOMMAND); // Codifica diagnosi esame... //

		pMstMenu->DeleteMenu(ID_ARCHIVI_MST_COMPLICANZE1, MF_BYCOMMAND);
		pMstMenu->DeleteMenu(ID_ARCHIVI_MST_COMPLICANZE2, MF_BYCOMMAND);
		pMstMenu->DeleteMenu(ID_ARCHIVI_MST_COMPLICANZE3, MF_BYCOMMAND);

		NascondiSeparatori(pMstMenu);
	}

	pMenu->DeleteMenu(ID_ARCHIVI_ORGANISEDI, MF_BYCOMMAND); // Organi e sedi... //
	pMenu->DeleteMenu(ID_ARCHIVI_CODIFICAREGIONALE, MF_BYCOMMAND); // Codifica prestazioni... //
	pMenu->DeleteMenu(ID_ARCHIVI_GRUPPIPRESTAZIONI, MF_BYCOMMAND); // Gruppi di prestazioni... //
	pMenu->DeleteMenu(ID_ARCHIVI_GRUPPIPRESTAZIONI_RICETTA, MF_BYCOMMAND); // Gruppi di prestazioni per ricetta... //
	pMenu->DeleteMenu(ID_ARCHIVI_TIPIPRELIEVI, MF_BYCOMMAND); // Tipi di prelievi... //
	pMenu->DeleteMenu(ID_ARCHIVI_PROCEDUREPRELIEVI, MF_BYCOMMAND); // Procedure prelievi... //
	pMenu->DeleteMenu(ID_ARCHIVI_GRUPPIPRELIEVI, MF_BYCOMMAND); // Gruppi di prelievi... //
	pMenu->DeleteMenu(ID_VARI_DIAGNOSIISTOLOGICA, MF_BYCOMMAND); // Diagnosi istologica... //
	pMenu->DeleteMenu(ID_VARI_BOSTONSCORE, MF_BYCOMMAND); // Boston score... //
	pMenu->DeleteMenu(ID_ARCHIVI_MALATTIECRONICHE, MF_BYCOMMAND); // Malattie croniche... //
	pMenu->DeleteMenu(ID_ARCHIVI_ESAMI, MF_BYCOMMAND); // Tipi d'esame... //
	pMenu->DeleteMenu(ID_ARCHIVI_STRUMENTI, MF_BYCOMMAND); // Strumenti... //
	pMenu->DeleteMenu(ID_ARCHIVI_ETICHETTE_ANAMNESI, MF_BYCOMMAND); // Etichette anamnesi... //
	pMenu->DeleteMenu(ID_ARCHIVI_PRONTFARMACEUTICO, MF_BYCOMMAND); // Prontuario farmaceutico... //
	pMenu->DeleteMenu(ID_ARCHIVI_PRONTFARMACEUTICO_RICETTA, MF_BYCOMMAND); // Gruppi di farmaci per ricetta... //

	pMenu->DeleteMenu(ID_ARCHIVI_INVIANTI_INT, MF_BYCOMMAND); // Reparti interni... //
	pMenu->DeleteMenu(ID_ARCHIVI_INVIANTI_EXT, MF_BYCOMMAND); // Provenienza esterni... //

	switch (theApp.m_lBackupDVD)
	{
	case 0:
	{
		pMenu->DeleteMenu(ID_ARCHIVI_OCCUPAZIONEGIORNALIERA, MF_BYCOMMAND); // Occupazione giornaliera... //
		pMenu->DeleteMenu(ID_ARCHIVI_BACKUPDATI, MF_BYCOMMAND); // Backup dati... //
		break;
	}
	case 1:
	{
		pMenu->DeleteMenu(ID_ARCHIVI_TRASFERIMPARZIALE, MF_BYCOMMAND); // Trasferimento H.D. -> O.D. Scheda... //
		pMenu->DeleteMenu(ID_ARCHIVI_TRASFERIMTOTALE, MF_BYCOMMAND); // Trasferimento H.D. -> O.D. Totale... //
		pMenu->DeleteMenu(ID_ARCHIVI_ESPELLI_OD, MF_BYCOMMAND); // Espelli disco removibile //
		break;
	}
	case 2:
	{
		pMenu->DeleteMenu(ID_ARCHIVI_TRASFERIMPARZIALE, MF_BYCOMMAND); // Trasferimento H.D. -> O.D. Scheda... //
		pMenu->DeleteMenu(ID_ARCHIVI_TRASFERIMTOTALE, MF_BYCOMMAND); // Trasferimento H.D. -> O.D. Totale... //
		pMenu->DeleteMenu(ID_ARCHIVI_ESPELLI_OD, MF_BYCOMMAND); // Espelli disco removibile //
		break;
	}
	}

	pMenu->DeleteMenu(ID_ARCHIVI_SALVAVALORIDEFAULT, MF_BYCOMMAND); // Salva valori di default //

	NascondiSeparatori(pMenu);
}

void CEsamiView::NascondiMenuImageNTOpzioni(CMenu* pMenu)
{
	pMenu->DeleteMenu(ID_OPTION_CALIB, MF_BYCOMMAND);

	pMenu->DeleteMenu(ID_OPTION_WEB, MF_BYCOMMAND);

	NascondiSeparatori(pMenu);
}

void CEsamiView::NascondiSeparatori(CMenu* pMenu)
{
	MENUITEMINFO menuInfo;

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// elimino le voci senza dicitura (così modificando il dictionary posso nascondere delle voci :-D) //
	/////////////////////////////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < pMenu->GetMenuItemCount(); i++)
	{
		menuInfo.cbSize = sizeof(MENUITEMINFO);
		menuInfo.dwTypeData = NULL;
		menuInfo.fMask = MIIM_FTYPE | MIIM_STRING;
		if (pMenu->GetMenuItemInfo(i, &menuInfo, TRUE))
		{
			if (menuInfo.fType == MFT_STRING)
			{
				if (menuInfo.cch == 0)
				{
					// abbiamo una stringa di 0 caratteri, la elimino //
					pMenu->DeleteMenu(i, MF_BYPOSITION);
					i--;
				}
			}
		}
	}

	/////////////////////////////////
	// cancello i separatori doppi //
	/////////////////////////////////

	UINT iPrev = -1;
	UINT iCurr = -1;

	for (int i = 0; i < pMenu->GetMenuItemCount(); i++)
	{
		menuInfo.cbSize = sizeof(MENUITEMINFO);
		menuInfo.fMask = MIIM_FTYPE;
		if (pMenu->GetMenuItemInfo(i, &menuInfo, TRUE))
		{
			if (menuInfo.fType == MFT_SEPARATOR)
			{
				iPrev = iCurr;
				iCurr = i;

				if (iCurr - iPrev == 1)
				{
					// abbiamo due separatori attaccati, ne cancello uno //
					pMenu->DeleteMenu(iCurr, MF_BYPOSITION);
					iCurr--;
					i--;
				}
			}
		}
	}

	////////////////////////////////////////////////////////
	// cancello l'ultima voce del menù se è un separatore //
	////////////////////////////////////////////////////////

	menuInfo.cbSize = sizeof(MENUITEMINFO);
	menuInfo.fMask = MIIM_FTYPE;
	if (pMenu->GetMenuItemInfo(pMenu->GetMenuItemCount() - 1, &menuInfo, TRUE))
	{
		if (menuInfo.fType == MFT_SEPARATOR)
			pMenu->DeleteMenu(pMenu->GetMenuItemCount() - 1, MF_BYPOSITION);
	}
}

void CEsamiView::OnPazienteNew()
{
	if (theApp.m_nProgramMode == NOTHING_MODE)
	{
		if (m_PazTempSet.OpenRecordset("CEsamiView::OnPazienteNew"))
		{
			theApp.m_nProgramMode |= ADD_RECORD_PAZIENTI;

			m_PazTempSet.SetEmpty();
			m_pPazientiSet->SetEmpty();
			m_pEsamiSet->SetEmpty();

			if (m_PazTempSet.IsOpen())
				m_PazTempSet.SetFieldNull(NULL, TRUE);
			if (m_pPazientiSet->IsOpen())
				m_pPazientiSet->SetFieldNull(NULL, TRUE);
			if (m_pEsamiSet->IsOpen())
				m_pEsamiSet->SetFieldNull(NULL, TRUE);

			ResetForm();

			if (m_pFormImmagini)
				m_pFormImmagini->ResetAlbum();

			UpdateData(FALSE);

			CPazientiDlg dlgPaz(this, this, &m_PazTempSet, PAZ_ADDN);
			if (dlgPaz.DoModal() == IDOK)
			{
				OnPazienteUpdate();
				if (theApp.m_bConsultazioneWEB && m_pPazientiSet->m_sLogin != "")
				{
					CWebDeployer webCreator(&theApp.m_dbEndox);
					webCreator.DeployPatient(&theApp.m_sPercorsoTemporaneoWEB, &theApp.m_sInterfacciaWebTo, &theApp.m_sInterfacciaWebFrom, m_pPazientiSet, WD_OPERAZIONE_NEW);
					webCreator.DeployPasswordPatient(&theApp.m_sPercorsoTemporaneoWEB, &theApp.m_sInterfacciaWebTo, &theApp.m_sInterfacciaWebFrom, m_pPazientiSet->m_lContatore, m_pPazientiSet->m_sLogin);
				}
			}
			else
				OnPazienteRefresh();
		}
	}
}

void CEsamiView::OnPazienteModify()
{
	if (theApp.m_nProgramMode == NOTHING_MODE)
	{
		long lLockedPatient = m_pPazientiSet->m_lContatore;
		if (CLockManager::Get()->LockPatientAndAllExams(lLockedPatient))
		{
			CString strFilter;
			strFilter.Format("Contatore=%li", m_pPazientiSet->m_lContatore);
			m_PazTempSet.SetOpenFilter(strFilter);
			if (m_PazTempSet.OpenRecordset("CEsamiView::OnPazienteModify"))
			{
				theApp.m_nProgramMode |= MODIFY_RECORD_PAZIENTI;

				UpdateData(FALSE);

				CPazientiDlg dlgPaz(this, this, &m_PazTempSet, PAZ_EDIT);
				if (dlgPaz.DoModal() == IDOK)
				{
					OnPazienteUpdate();
					if (theApp.m_bConsultazioneWEB && m_pPazientiSet->m_sLogin != "")
					{
						CWebDeployer webCreator(&theApp.m_dbEndox);
						webCreator.DeployPatient(&theApp.m_sPercorsoTemporaneoWEB, &theApp.m_sInterfacciaWebTo, &theApp.m_sInterfacciaWebFrom, m_pPazientiSet, WD_OPERAZIONE_MODIFY);
					}

				}
				else
				{
					OnPazienteRefresh();
				}
			}

			CLockManager::Get()->UnlockPatientAndAllExams(lLockedPatient);
		}
	}
}

BOOL CEsamiView::VerifyDuplicated(CString strTitle)
{
	int nResult = IDCANCEL;
	long lCurPazCode = 0;
	long lCurExamCode = 0;
	CPazientiSet QueryPazientiSet;
	CJoinEsamiSet QueryEsamiSet;

	CString strToVerify = "";
	CString strBuffer;

	if (!m_PazTempSet.IsFieldNull(&m_PazTempSet.m_sCodFisc))
	{
		if (!m_PazTempSet.IsFieldNull(&m_PazTempSet.m_sCodFisc))
		{
			strBuffer = m_PazTempSet.m_sCodFisc;
			strBuffer.TrimLeft();
			strBuffer.TrimRight();

			ConvertInValidStringSQL(&strBuffer);

			strToVerify = "CodFisc LIKE '" + strBuffer + "'";
		}
	}
	else
	{
		if (!m_PazTempSet.IsFieldNull(&m_PazTempSet.m_sCodiceRicovero))
		{
			if (!m_PazTempSet.IsFieldNull(&m_PazTempSet.m_sCodiceRicovero))
			{
				strBuffer = m_PazTempSet.m_sCodiceRicovero;
				strBuffer.TrimLeft();
				strBuffer.TrimRight();

				ConvertInValidStringSQL(&strBuffer);

				strToVerify = "CodiceRicovero LIKE '" + strBuffer + "'";
			}
		}
		else
		{
			if (!m_PazTempSet.IsFieldNull(&m_PazTempSet.m_sIdEpisodioRicovero))
			{
				if (!m_PazTempSet.IsFieldNull(&m_PazTempSet.m_sIdEpisodioRicovero))
				{
					strBuffer = m_PazTempSet.m_sIdEpisodioRicovero;
					strBuffer.TrimLeft();
					strBuffer.TrimRight();

					ConvertInValidStringSQL(&strBuffer);

					strToVerify = "IdEpisodioRicovero LIKE '" + strBuffer + "'";
				}
			}
			else
			{
				if (!m_PazTempSet.IsFieldNull(&m_PazTempSet.m_sCognome))
				{
					strBuffer = m_PazTempSet.m_sCognome;
					strBuffer.TrimLeft();
					strBuffer.TrimRight();

					ConvertInValidStringSQL(&strBuffer);

					strToVerify = "Cognome LIKE '" + strBuffer + "%'";
				}

				if (!m_PazTempSet.IsFieldNull(&m_PazTempSet.m_sNome))
				{
					if (!strToVerify.IsEmpty())
						strToVerify += " AND ";

					strBuffer = m_PazTempSet.m_sNome;
					strBuffer.TrimLeft();
					strBuffer.TrimRight();

					ConvertInValidStringSQL(&strBuffer);

					strToVerify += "Nome LIKE '%" + strBuffer + "%'";
				}
			}
		}
	}

	QueryPazientiSet.SetOpenFilter(strToVerify);
	//QueryPazientiSet.SetSortRecord("Contatore");
	QueryPazientiSet.SetSortRecord("Cognome, Nome, NatoIlCustom");
	//theApp.AfxMessageBoxEndo(QueryPazientiSet.GetQuery());
	QueryPazientiSet.OpenRecordset("CEsamiView::VerifyDuplicated");

	if (QueryPazientiSet.IsEOF())
		return FALSE;

	/////

	CQueryDlg dlg(this, TRUE, strTitle);

	dlg.m_lRelazione = SOLO_PAZIENTI;
	dlg.m_strPazFilter = strToVerify;
	dlg.m_strEsameFrom = "";
	dlg.m_strEsameWhere = "";
	dlg.m_pPazientiSet = &QueryPazientiSet;
	dlg.m_pJoinEsamiSet = &QueryEsamiSet;
	dlg.m_bCercaPaziente = TRUE;

	nResult = dlg.DoModal();

	QueryPazientiSet.CloseRecordset("CEsamiView::VerifyDuplicated");
	QueryEsamiSet.CloseRecordset("CEsamiView::VerifyDuplicated");

	lCurPazCode = dlg.m_lCurrentPri;
	lCurExamCode = dlg.m_lCurrentSec;

	if (nResult == IDOK)
	{
		if (!dlg.m_bAddNew)
		{
			RicercaCodicePaziente(lCurPazCode, lCurExamCode, FALSE, TRUE);
			MovePazientiAndEsami(NULL, TRUE, TRUE);

			/*if (RicercaCodicePaziente(lCurPazCode, lCurExamCode, FALSE, TRUE))
			MovePazientiAndEsami(NULL, FALSE, TRUE);
			else
			MovePazientiAndEsami(NULL, TRUE, TRUE);*/

			m_PazTempSet.CloseRecordset("CEsamiView::VerifyDuplicated");
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		OnPazienteRefresh();
		m_PazTempSet.CloseRecordset("CEsamiView::VerifyDuplicated");
		return TRUE;
	}

	m_PazTempSet.CloseRecordset("CEsamiView::VerifyDuplicated");
	return TRUE;
}

void CEsamiView::OnPazienteUpdate()
{
	// Marvel BUG 4090 - desconjugação de laudos (tela principal do Tesicapture) 
	// Correção de crash no na desconjugação de laudos
	//if (m_PazTempSet.m_lContatore <= 0)
	//	return;

	if (theApp.m_nProgramMode & ADD_RECORD_PAZIENTI || theApp.m_nProgramMode & MODIFY_RECORD_PAZIENTI)
	{
		if (theApp.m_nProgramMode & ADD_RECORD_PAZIENTI)
		{
			OnPazienteUpdateEndox();
		}
		else
		{
			//UPDATE
			CPazientiSet TempPazienti;
			TempPazienti.CopyFieldFrom(&m_PazTempSet);

			m_PazTempSet.EditRecordset("CEsamiView::OnPazienteUpdate");
			m_PazTempSet.CopyFieldFrom(&TempPazienti);
			//StatoAPC istruisce l'eventuale servizio ASINCRONO sul come gestire l'anagrafica in questione 
			//(0 ok, 1 da notificare inserimento, 2 da notificare modifica, 3 da notificare id di endox)
			if (m_PazTempSet.m_lStatoAPC != 1)
			{
				m_PazTempSet.m_lStatoAPC = 2;
			}
			m_PazTempSet.SetFieldDirty(&m_PazTempSet.m_lContatore, FALSE);

			if (m_PazTempSet.UpdateRecordset("CEsamiView::OnPazienteUpdate") == FALSE)
			{
				m_PazTempSet.NoEditRecordset("CEsamiView::OnPazienteUpdate");
			}


			/* if (theApp.m_bPazientiUsaVista)
			{
			long lTemp = m_pPazientiSet->m_lContatore;
			m_pPazientiSet->RequeryRecordset();
			PazienteSetFind(m_pPazientiSet, lTemp);
			} */

			CExtPatientEventSet().AddEvent(m_pPazientiSet->m_lContatore, updatePatient);

			MoveRecord(NULL);
			UpdateData(FALSE);

			// Marvel BUG 4090 - desconjugação de laudos (tela principal do Tesicapture) 
			//theApp.m_nProgramMode = NOTHING_MODE;
		}
	}
}

void CEsamiView::OnPazienteUpdateEndox()
{
	if (!VerifyDuplicated())
	{
		CPazientiSet TempPazienti;

		m_PazTempSet.CloseRecordset("CEsamiView::OnPazienteUpdate"); // lo faccio perchè il copyfield mi becca certi campi come null che invece non lo sono proprio!!! //
		TempPazienti.CopyFieldFrom(&m_PazTempSet);
		m_PazTempSet.OpenRecordset("CEsamiView::OnPazienteUpdate"); // vedi due righe sopra //

		if (m_PazTempSet.AddNewRecordset("CEsamiView::OnPazienteUpdate"))
		{
			m_PazTempSet.CopyFieldFrom(&TempPazienti);

			if (m_PazTempSet.UpdateRecordset("CEsamiView::OnPazienteUpdate") == TRUE)
			{
				RicercaCodicePaziente(m_PazTempSet.GetLastAdd(), 0, FALSE, TRUE);
				MovePazientiAndEsami(NULL, TRUE, TRUE);

				CExtPatientEventSet().AddEvent(m_PazTempSet.GetLastAdd(), addNewPatient);
			}
			else
			{
				m_pPazientiSet->RefreshRecordset();
			}
		}

	}
}

void CEsamiView::OnPazienteRefresh()
{
	if (theApp.m_nProgramMode & ADD_RECORD_PAZIENTI || theApp.m_nProgramMode & MODIFY_RECORD_PAZIENTI || theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI || theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		m_PazTempSet.CloseRecordset("CEsamiView::OnPazienteRefresh");
		m_pPazientiSet->RefreshRecordset();

		if (theApp.m_nProgramMode & ADD_RECORD_PAZIENTI)
		{
			MoveRecord(NULL);
			theApp.m_nProgramMode = NOTHING_MODE;
		}
		else
		{
			MovePazientiAndEsami(NULL, FALSE, TRUE);
			theApp.m_nProgramMode = NOTHING_MODE;
			m_pEsamiSet->RefreshRecordset();
			OnEsamiMove(NULL);
		}
	}
}

void CEsamiView::DeleteEsamiEndox()
{
	FiltraEsami();

	if (m_pEsamiSet->IsEOF() == FALSE)
		m_pEsamiSet->MoveLast();

	while (m_pEsamiSet->IsBOF() == FALSE)
	{
		// OnEsameDelete();		
		m_pEsamiSet->DeleteRecordset("CEsamiView::DeleteEsamiEndox");

		// m_pEsamiSet->RequeryRecordset();
		m_pEsamiSet->MovePrev();
	}

	m_pEsamiSet->RequeryRecordset();
}

void CEsamiView::AnnullaCampiPaziente()
{
	if (m_pPazientiSet->IsOpen())
		m_pPazientiSet->SetFieldNull(NULL, TRUE);

	for (int i = 0; i < form_list_total; i++)
		if (m_pDynForm[i] != NULL)
			m_pDynForm[i]->SendMessage(MSG_FORM_ANNULLAPAZIENTE);
}

void CEsamiView::AnnullaCampiEsame()
{
	if (m_pEsamiSet->IsOpen())
		m_pEsamiSet->SetFieldNull(NULL, TRUE);

	for (int i = 0; i < form_list_total; i++)
		if (m_pDynForm[i] != NULL)
			m_pDynForm[i]->SendMessage(MSG_FORM_ANNULLAESAME);
}

void CEsamiView::ResetForm()
{
	for (int i = 0; i < form_list_total; i++)
		if (m_pDynForm[i] != NULL)
			m_pDynForm[i]->SendMessage(MSG_FORM_RESET);

	UpdateData(FALSE);
}

void CEsamiView::CloneForm(long lContatoreOrigine)
{
	for (int i = 0; i < form_list_total; i++)
	{
		if (m_pDynForm[i] != NULL)
			m_pDynForm[i]->SendMessage(MSG_FORM_CLONE, NULL, (LPARAM)lContatoreOrigine);
	}

	UpdateData(FALSE);
}

void CEsamiView::LoadForm()
{
	for (int i = 0; i < form_list_total; i++)
		if (m_pDynForm[i] != NULL)
			m_pDynForm[i]->SendMessage(MSG_FORM_LOAD);
}

void CEsamiView::SaveForm()
{
	for (int i = 0; i < form_list_total; i++)
		if (m_pDynForm[i] != NULL)
			m_pDynForm[i]->SendMessage(MSG_FORM_SAVE);
}

BOOL CEsamiView::Logout(BOOL bMoveEsami)
{
	//Julio 03/08/2018
	if (theApp.m_bMenuUsaTextboxBuscaExame)
	{
		m_ctrlEditFleuryFicha.RemoveSearchAll();

		int iArraySize = sizeof(m_arrayFleuryFichaItem) / sizeof(m_arrayFleuryFichaItem[0]);
		for (int i = 0; i < iArraySize; i++)
			m_arrayFleuryFichaItem[i] = "";

		m_sFleuryFicha = "";
		m_sFleuryItem = "";

		GetDlgItem(IDC_EDIT_FLEURYFICHA)->SetWindowText("");
		GetDlgItem(IDC_EDIT_FLEURYITEM)->SetWindowText("");
	}
	//
	if (theApp.m_nProgramMode != NOTHING_MODE)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAMIVIEW_LOGOUT), MB_ICONSTOP);
		return TRUE;
	}

	//Simone RIMA16052 - Salvo la selezione prima del logout, in modo da poter in seguio ripristinarla
	int indexImmaginiSelezionate = 0;

	CObSelect** tempSelectedList = new CObSelect * [CFileBmp::m_listSelected.GetCount()];
	for (POSITION pos = CFileBmp::GetFirstSelectedPos(); pos != NULL;)
	{
		CObSelect* pSel = CFileBmp::GetNextSelected(pos);

		tempSelectedList[indexImmaginiSelezionate] = new CObSelect();
		tempSelectedList[indexImmaginiSelezionate]->m_lID = pSel->m_lID;
		tempSelectedList[indexImmaginiSelezionate]->m_strDescription = pSel->m_strDescription;
		tempSelectedList[indexImmaginiSelezionate]->m_bConfirmed = pSel->m_bConfirmed;
		tempSelectedList[indexImmaginiSelezionate]->m_strDvdLabel = pSel->m_strDvdLabel;
		tempSelectedList[indexImmaginiSelezionate]->m_bCI = pSel->m_bCI;
		tempSelectedList[indexImmaginiSelezionate]->m_iType = pSel->m_iType;

		indexImmaginiSelezionate++;
	}

	// if (theApp.m_bUserManagement)
	// AMStandBy_Stop();

	BOOL bReturn = FALSE;

	theApp.m_lIDEsameFirmaDisattivata = 0;
	AMLogin_Logout();
	theApp.m_lUO = 0; // Sandro 16/11/2015 // RAS 201500080 //
	if (theApp.m_lLoginMode == 1 || theApp.m_lLoginMode == 2)
	{
		if (AMLogin_Login(
			theApp.m_sUtenteLoggato,
			theApp.m_sNomeComputer,
			theApp.m_sNomeImpianto,
			theApp.GetMessageString(IDS_SYSTEM_ACCESS),
			&theApp.m_dbEndox,
			2, //Nel caso di logout in Single Sign-On, l'accesso conseguente deve essere fatto con la richiesta di utente e password
			theApp.m_sLoginServer,
			theApp.m_bLoginDropDomain,
			!bMoveEsami, // Sandro 02/04/2015 // se non mi muovo è il logout automatico (per la refertazione o per la chiusura dell'esame) //
			tesiimaging))
		{
			theApp.m_sUtenteLoggato = AMLogin_GetUsername();

			AMLogin_GetUserPermission(&theApp.m_dwPrivileges);

			long lUserID = 0;
			AMLogin_GetUserID(&lUserID);

			// Sandro 26/11/2014 //
			CUOSet().VerificaUODefault();

			//
			CStringList listGroups;
			if (((theApp.m_lLoginMode == 1) || (theApp.m_lLoginMode == 2)) && (lUserID > 0))
			{
				if (AMLogin_GetUserGroups(&listGroups))
				{
					CUOUtenteSet setUOUtente;

					CString strFilter;
					strFilter.Format("IDUtente=%li", lUserID);

					setUOUtente.SetOpenFilter(strFilter);
					if (setUOUtente.OpenRecordset("CEsamiDoc::OnNewDocument"))
					{
						while (!setUOUtente.IsEOF())
						{
							setUOUtente.DeleteRecordset("CEsamiDoc::OnNewDocument");
							setUOUtente.MoveNext();
						}

						setUOUtente.CloseRecordset("CEsamiDoc::OnNewDocument");
					}

					POSITION posGroups = listGroups.GetHeadPosition();
					while (posGroups != NULL)
					{
						long lUserUO = CVistaGruppiSet().GetUO(listGroups.GetAt(posGroups));

						if (lUserUO > 0)
						{
							setUOUtente.SetOpenFilter("IDUtente=0");
							if (setUOUtente.OpenRecordset("CEsamiDoc::OnNewDocument"))
							{
								if (setUOUtente.AddNewRecordset("CEsamiDoc::OnNewDocument"))
								{
									setUOUtente.m_lIDUO = lUserUO;
									setUOUtente.m_lIDUtente = lUserID;

									setUOUtente.UpdateRecordset("CEsamiDoc::OnNewDocument");
								}

								setUOUtente.CloseRecordset("CEsamiDoc::OnNewDocument");
							}
						}

						listGroups.GetNext(posGroups);
					}
				}
			}

			CUOUtenteDlg dlg(this, lUserID);
			dlg.DoModal();

			if (theApp.m_lUO <= 0)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_NESSUNA_UO));
				theApp.m_lIDEsameFirmaDisattivata = 0;
				AMLogin_Logout();
				theApp.m_lUO = 0; // Sandro 16/11/2015 // RAS 201500080 //
				AfxGetMainWnd()->PostMessage(WM_CLOSE);
				bReturn = FALSE;
			}
			else
			{
				// Sandro 26/11/2014 //
				CSediEsameSet().VerificaSedeDefault();

				// Sandro 23/03/2016 //
				if (theApp.m_lLoginMode > 0)
				{
					theApp.m_dwPrivileges = GetUpdatedPrivileges();
					AMLogin_SetUserPermission(theApp.m_dwPrivileges);
				}

				AssociaRecordset();
				MovePazientiAndEsami(NULL, TRUE, TRUE);
				bReturn = TRUE;
			}

			((CEsamiDoc*)m_pDocument)->SetTitle(theApp.GetAppTitle(0));
		}
		else
		{
			AfxGetMainWnd()->PostMessage(WM_CLOSE);
		}
	}
	else if (theApp.m_lLoginMode == 3 || theApp.m_lLoginMode == 4)
	{
		if (AMLogin_Login(
			theApp.m_sUtenteLoggato,
			theApp.m_sNomeComputer,
			theApp.m_sNomeImpianto,
			theApp.GetMessageString(IDS_SYSTEM_ACCESS),
			&theApp.m_dbEndox,
			4, //Nel caso di logout in Single Sign-On, l'accesso conseguente deve essere fatto con la richiesta di utente e password
			theApp.m_sLoginServer,
			theApp.m_bLoginDropDomain,
			!bMoveEsami, // Sandro 02/04/2015 // se non mi muovo è il logout automatico (per la refertazione o per la chiusura dell'esame) //
			tesiimaging))
		{
			theApp.m_sUtenteLoggato = AMLogin_GetUsername();

			AMLogin_GetUserPermission(&theApp.m_dwPrivileges);

			long lUserID = 0;
			AMLogin_GetUserID(&lUserID);

			// Sandro 26/11/2014 //
			CUOSet().VerificaUODefault();

			//
			CStringList listGroups;
			if (((theApp.m_lLoginMode == 3) || (theApp.m_lLoginMode == 4)) && (lUserID > 0))
			{
				if (AMLogin_GetUserGroups_Net(&listGroups))
				{
					CUOUtenteSet setUOUtente;

					CString strFilter;
					strFilter.Format("IDUtente=%li", lUserID);

					setUOUtente.SetOpenFilter(strFilter);
					if (setUOUtente.OpenRecordset("CEsamiDoc::OnNewDocument"))
					{
						while (!setUOUtente.IsEOF())
						{
							setUOUtente.DeleteRecordset("CEsamiDoc::OnNewDocument");
							setUOUtente.MoveNext();
						}

						setUOUtente.CloseRecordset("CEsamiDoc::OnNewDocument");
					}

					POSITION posGroups = listGroups.GetHeadPosition();
					while (posGroups != NULL)
					{
						CString gruppo = listGroups.GetAt(posGroups);
						long lUserUO = CVistaGruppiSet().GetUO(gruppo);

						if (lUserUO > 0)
						{
							setUOUtente.SetOpenFilter("IDUtente=0");
							if (setUOUtente.OpenRecordset("CEsamiDoc::OnNewDocument"))
							{
								if (setUOUtente.AddNewRecordset("CEsamiDoc::OnNewDocument"))
								{
									setUOUtente.m_lIDUO = lUserUO;
									setUOUtente.m_lIDUtente = lUserID;

									setUOUtente.UpdateRecordset("CEsamiDoc::OnNewDocument");
								}

								setUOUtente.CloseRecordset("CEsamiDoc::OnNewDocument");
							}
						}

						listGroups.GetNext(posGroups);
					}
				}
			}

			CUOUtenteDlg dlg(this, lUserID);
			dlg.DoModal();

			if (theApp.m_lUO <= 0)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_NESSUNA_UO));
				theApp.m_lIDEsameFirmaDisattivata = 0;
				AMLogin_Logout();
				theApp.m_lUO = 0; // Sandro 16/11/2015 // RAS 201500080 //
				AfxGetMainWnd()->PostMessage(WM_CLOSE);
				bReturn = FALSE;
			}
			else
			{
				// Sandro 26/11/2014 //
				CSediEsameSet().VerificaSedeDefault();

				// Sandro 23/03/2016 //
				if (theApp.m_lLoginMode > 0)
				{
					theApp.m_dwPrivileges = GetUpdatedPrivileges();
					AMLogin_SetUserPermission(theApp.m_dwPrivileges);
				}

				AssociaRecordset();
				MovePazientiAndEsami(NULL, TRUE, TRUE);
				bReturn = TRUE;
			}

			((CEsamiDoc*)m_pDocument)->SetTitle(theApp.GetAppTitle(0));
		}
		else
		{
			AfxGetMainWnd()->PostMessage(WM_CLOSE);
		}
	}
	else
	{
		if (AMLogin_Login(
			theApp.m_sUtenteLoggato,
			theApp.m_sNomeComputer,
			theApp.m_sNomeImpianto,
			theApp.GetMessageString(IDS_SYSTEM_ACCESS),
			&theApp.m_dbEndox,
			theApp.m_lLoginMode,
			theApp.m_sLoginServer,
			theApp.m_bLoginDropDomain,
			!bMoveEsami, // Sandro 02/04/2015 // se non mi muovo è il logout automatico (per la refertazione o per la chiusura dell'esame) //
			tesiimaging))
		{
			theApp.m_sUtenteLoggato = AMLogin_GetUsername();

			AMLogin_GetUserPermission(&theApp.m_dwPrivileges);

			long lUserID = 0;
			AMLogin_GetUserID(&lUserID);

			// Sandro 26/11/2014 //
			CUOSet().VerificaUODefault();

			//
			CUOUtenteDlg dlg(this, lUserID);
			dlg.DoModal();

			if (theApp.m_lUO <= 0)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_NESSUNA_UO));
				theApp.m_lIDEsameFirmaDisattivata = 0;
				AMLogin_Logout();
				theApp.m_lUO = 0; // Sandro 16/11/2015 // RAS 201500080 //
				AfxGetMainWnd()->PostMessage(WM_CLOSE);
				bReturn = FALSE;
			}
			else
			{
				// Sandro 26/11/2014 //
				CSediEsameSet().VerificaSedeDefault();

				// Sandro 23/03/2016 //
				if (theApp.m_lLoginMode > 0)
				{
					theApp.m_dwPrivileges = GetUpdatedPrivileges();
					AMLogin_SetUserPermission(theApp.m_dwPrivileges);
				}

				AssociaRecordset();

				// Sandro 10/12/2013 //
				MovePazientiAndEsami(NULL, bMoveEsami, TRUE);

				((CEsamiDoc*)m_pDocument)->SetTitle(theApp.GetAppTitle(0));

				//
				bReturn = TRUE;
			}
		}
		else
		{
			AfxGetMainWnd()->PostMessage(WM_CLOSE);
		}
	}

	if (bReturn)
	{
		//16052 Simone - Carico la lista dei gruppi a cui appartiene l'utente e i privilegi sulle fasi. Deve essere fatto qui per il FleuryUserCodeCheck() del cazzo	
		((CEsamiDoc*)m_pDocument)->LoadUserGroups();
		((CEsamiDoc*)m_pDocument)->LoadEnabledPhaseForUser();


		//Julio Login SEGU
		if (theApp.m_bPersonalizzazioniBrasileFleury && theApp.m_sUtenteLoggato != "SAT" && theApp.m_sUtenteLoggato != "ADMINISTRATOR" && !FleuryGetHealthProfessional()/*!FleuryUserCodeCheck()*/)
			bReturn = FALSE;

	}

	//Ripristino le immagini precedentemente selezionate selezionate
	if (bReturn && theApp.m_bMantieniImmaginiSelezionateAlLogout)
	{
		for (int h = 0; h < indexImmaginiSelezionate; h++)
			CFileBmp::NewSelected(tempSelectedList[h]->m_lID, FALSE, tempSelectedList[h]->m_iType, tempSelectedList[h]->m_strDescription, m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore, tempSelectedList[h]->m_bConfirmed, tempSelectedList[h]->m_strDvdLabel, tempSelectedList[h]->m_bCI);

		m_pFormImmagini->AfterMoveEsame(FALSE);
	}

	//In ogni caso pulisco la memoria
	for (int h = 0; h < indexImmaginiSelezionate; h++)
		delete(tempSelectedList[h]);

	delete(tempSelectedList);

	return bReturn;
}

void CEsamiView::OnPazienteDelete()
{
	if (theApp.m_nProgramMode == NOTHING_MODE)
	{
		long lLockedPatient = m_pPazientiSet->m_lContatore;
		if (CLockManager::Get()->LockPatientAndAllExams(lLockedPatient))
		{
			if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAMIVIEW_DELETE_PAT_CONFIRM), MB_YESNO | MB_ICONEXCLAMATION | MB_DEFBUTTON2) == IDNO)
			{
				CLockManager::Get()->UnlockPatientAndAllExams(lLockedPatient);
				return;
			}
			if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAMIVIEW_DELETE_PAT_CONFIRM_2), MB_YESNO | MB_ICONSTOP | MB_DEFBUTTON1) == IDYES)
			{
				CLockManager::Get()->UnlockPatientAndAllExams(lLockedPatient);
				return;
			}

			long lPaziente = m_pPazientiSet->m_lContatore;
			m_pPazientiSet->MoveNext();
			if (m_pPazientiSet->IsEOF())
			{
				// sto cancellando l'ultimo paziente --> mi segno il numero del penultimo //
				m_pPazientiSet->MoveLast();
				m_pPazientiSet->MovePrev();
				if (!m_pPazientiSet->IsBOF())
					lPaziente = m_pPazientiSet->m_lContatore;
				m_pPazientiSet->MoveLast();
			}
			else
			{
				lPaziente = m_pPazientiSet->m_lContatore;
				m_pPazientiSet->MovePrev();
			}

			DeleteEsamiEndox();
			m_pPazientiSet->DeleteRecordset("CEsamiView::OnPazienteDelete");

			RicercaCodicePaziente(lPaziente, 0, FALSE, FALSE);
			MovePazientiAndEsami(NULL, TRUE, TRUE);

			CLockManager::Get()->UnlockPatientAndAllExams(lLockedPatient);
		}
	}
}

// #define __PROVA__

void CEsamiView::OnPazienteQuery()
{
	OnDestroyQueryWnd(NULL, NULL);

	if (theApp.m_nProgramMode == NOTHING_MODE || theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		if (m_PazTempSet.OpenRecordset("CEsamiView::OnPazienteQuery"))
		{
			theApp.m_nProgramMode |= FILTER_RECORD_PAZIENTI;

			m_PazTempSet.SetFieldNull(NULL, TRUE);
			AnnullaCampiPaziente();

			if (!(theApp.m_nProgramMode & FILTER_RECORD_ESAMI))
				AnnullaCampiEsame();

			UpdateData(FALSE);

			m_PazTempSet.m_lSessoPaz = -1;
			CPazientiDlg dlgPaz(this, this, &m_PazTempSet, PAZ_SRCH);
			dlgPaz.DoModal();
			if (dlgPaz.m_bSearchNow)
				OnApplicaQuery();

			// Sandro 05/05/2010 - RIMA 10-028.1 //
			if (m_bRicercaDiretta)
			{
#ifdef __PROVA__
				theApp.AfxMessageBoxEndo("EEE");
#endif
				OnPazienteRefresh();
#ifdef __PROVA__
				theApp.AfxMessageBoxEndo("FFF");
#endif
				m_bRicercaDiretta = FALSE;
			}
		}
	}
	else
	{
		if ((theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI) != 0)
		{
			CPazientiDlg dlgPaz(this, this, &m_PazTempSet, PAZ_SRCH);
			dlgPaz.DoModal();
			if (dlgPaz.m_bSearchNow)
			{
				// Sandro 11/08/2010 //
				OnApplicaQuery();
			}

			// Sandro 05/05/2010 - RIMA 10-028.1 //
			if (m_bRicercaDiretta)
			{
				OnPazienteRefresh();
				m_bRicercaDiretta = FALSE;
			}
		}
	}
}

void CEsamiView::ComposeFilter(CString& strFilter)
{
	ComponiRicercaString(&strFilter, &m_PazTempSet, &m_PazTempSet.m_sCodFisc, "CodFisc", 0);
	ComponiRicercaString(&strFilter, &m_PazTempSet, &m_PazTempSet.m_sCodSanit, "CodSanit", 0);

	// Sandro 06/02/2014 // Ricerca anche lettere accentate... //
	ComponiRicercaCognomeNome(&strFilter, &m_PazTempSet, &m_PazTempSet.m_sCognome, "Cognome");
	ComponiRicercaCognomeNome(&strFilter, &m_PazTempSet, &m_PazTempSet.m_sNome, "Nome");

	ComponiRicercaSesso(strFilter, &m_PazTempSet, &m_PazTempSet.m_lSessoPaz, "Sesso", 0);

	// Sandro 23/07/2013 //
	ComponiRicercaLong(&strFilter, &m_PazTempSet, &m_PazTempSet.m_lNatoIlCustom, "NatoIlCustom", 0, "AND");
	/* if (!m_PazTempSet.m_sNatoIlCustom.IsEmpty())
	{
	if (!strFilter.IsEmpty())
	strFilter += " AND ";

	strFilter += m_PazTempSet.m_sNatoIlCustom;
	}
	*/

	ComponiRicercaString(&strFilter, &m_PazTempSet, &m_PazTempSet.m_sNatoA, "NatoA", 0);
	ComponiRicercaString(&strFilter, &m_PazTempSet, &m_PazTempSet.m_sProfessione, "Professione", 3);

	ComponiRicercaString(&strFilter, &m_PazTempSet, &m_PazTempSet.m_sMedicoCurante, "MedicoCurante", 0);
	ComponiRicercaString(&strFilter, &m_PazTempSet, &m_PazTempSet.m_sMedicoTel, "MedicoTel", 0);
	ComponiRicercaString(&strFilter, &m_PazTempSet, &m_PazTempSet.m_sMedicoIndirizzo, "MedicoIndirizzo", 0);

	ComponiRicercaString(&strFilter, &m_PazTempSet, &m_PazTempSet.m_sVia, "Via", 1);
	ComponiRicercaString(&strFilter, &m_PazTempSet, &m_PazTempSet.m_sCitta, "Citta", 1);
	ComponiRicercaString(&strFilter, &m_PazTempSet, &m_PazTempSet.m_sCAP, "CAP", 0);
	ComponiRicercaString(&strFilter, &m_PazTempSet, &m_PazTempSet.m_sProvincia, "Provincia", 0);
	ComponiRicercaString(&strFilter, &m_PazTempSet, &m_PazTempSet.m_sTelefono1, "Telefono1", 0);
	ComponiRicercaString(&strFilter, &m_PazTempSet, &m_PazTempSet.m_sTelefono2, "Telefono2", 0);
	ComponiRicercaString(&strFilter, &m_PazTempSet, &m_PazTempSet.m_sFax, "Fax", 0);
	ComponiRicercaString(&strFilter, &m_PazTempSet, &m_PazTempSet.m_sCellulare1, "Cellulare1", 0);
	ComponiRicercaString(&strFilter, &m_PazTempSet, &m_PazTempSet.m_sCellulare2, "Cellulare2", 0);
	ComponiRicercaString(&strFilter, &m_PazTempSet, &m_PazTempSet.m_sEmail, "Email", 0);
	ComponiRicercaString(&strFilter, &m_PazTempSet, &m_PazTempSet.m_sDenSegnalato, "DenSegnalato", 0);
	ComponiRicercaString(&strFilter, &m_PazTempSet, &m_PazTempSet.m_sCodiceCliente, "CodiceCliente", 1);
	ComponiRicercaString(&strFilter, &m_PazTempSet, &m_PazTempSet.m_sCognome2, "Cognome2", 1);
	ComponiRicercaString(&strFilter, &m_PazTempSet, &m_PazTempSet.m_sNominativoPadre, "NominativoPadre", 1);
	ComponiRicercaString(&strFilter, &m_PazTempSet, &m_PazTempSet.m_sNominativoMadre, "NominativoMadre", 1);

	ComponiRicercaLong(&strFilter, &m_PazTempSet, &m_PazTempSet.m_lDataDecesso, "DataDecesso", 0, "AND");

	if (!m_PazTempSet.m_sFiltroExtra.IsEmpty())
	{
		strFilter.Trim();

		if (strFilter.IsEmpty())
			strFilter = m_PazTempSet.m_sFiltroExtra;
		else
			strFilter += " AND " + m_PazTempSet.m_sFiltroExtra;
	}
}

void CEsamiView::OnApplicaQuery()
{
	BOOL bConteggio = FALSE;

	theApp.m_dbEndox.SetQueryTimeout(1800);

	// Sandro 11/03/2011 // RAS 20110057 //
	if (theApp.m_bRicercaChiediConteggio)
	{
		switch (CQueryCountDlg(this).DoModal())
		{
		case 222: // OnBnClickedBtnClassic //
		{
			bConteggio = FALSE;
			break;
		}
		case 333: // OnBnClickedBtnCount //
		{
			bConteggio = TRUE;
			break;
		}
		default:
		{
			theApp.m_dbEndox.SetQueryTimeout(15);
			OnPazienteRefresh();
			return;
			break;
		}
		}
	}

	if (!bConteggio)
	{
		if (m_pQueryDlg)
		{
			m_pQueryDlg->SendMessage(EM_SHOW_QUERY_WND);
		}
		else
		{
			CPazientiSet* pQueryPazientiSet = new CPazientiSet;
			CJoinEsamiSet* pQueryEsamiSet = new CJoinEsamiSet;
			CString strPazientiFilter;
			CString strEsamiFrom = "";
			CString strEsamiWhere = "";
			UINT nIDErrorString = 0;
			long lSearchType = FILTRO_PAZIENTI_ESAMI;

			m_pQueryDlg = new CQueryDlg(this, FALSE, "");

			// Calcolo che tipo di ricerca devo effettuare...
			//   -1 = tipo filtro specificato: esami
			//    0 = tipo filtro specificato: pazienti ed esami
			//    1 = tipo filtro specificato: pazienti
			if (theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI)
			{
				lSearchType++;

				// Costruzione filtro di ricerca per i pazienti...
				ComposeFilter(strPazientiFilter);
			}

			//trick
			int provenienza = m_pEsamiSet->m_lProvenienza;
			UpdateData(TRUE);
			m_pEsamiSet->m_lProvenienza = provenienza;

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
			{
				lSearchType--;
				for (int i = 0; i < form_list_total; i++)
					if (m_pDynForm[i] != NULL)
						m_pDynForm[i]->SendMessage(MSG_FORM_SEARCHNEW, (WPARAM)&strEsamiWhere, (LPARAM)&strEsamiFrom);

				CString strUO;
				strUO.Format("EESAMI.UO=%li", theApp.m_lUO);
				if (strEsamiWhere.IsEmpty())
					strEsamiWhere = strUO;
				else
					strEsamiWhere += " AND " + strUO;
			}

#ifdef _DEBUG
			CString strMessageBox;
			strMessageBox.Format("---------- ---------- ---------- ---------- ----------\n\nFILTRO PAZIENTI\n\n%s\n\n---------- ---------- ---------- ---------- ----------\n\nFILTRO ESAMI\n\n%s\n\n---------- ---------- ---------- ---------- ----------\n\nFROM ESAMI\n\n%s\n\n---------- ---------- ---------- ---------- ----------", strPazientiFilter, strEsamiWhere, strEsamiFrom);
			theApp.AfxMessageBoxEndo(strMessageBox);
#endif

			// Sandro 29/08/2013 // RAS 20130121 //
			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
			{
				BOOL bSoloPazienti = FALSE;

				if (theApp.m_bRicercaChiediSoloPazienti)
				{
					switch (CQueryOnlyPatiensDlg(this).DoModal())
					{
					case 222: // OnBnClickedBtnClassic //
					{
						bSoloPazienti = FALSE;
						break;
					}
					case 333: // OnBnClickedBtnOnlyPatiens //
					{
						bSoloPazienti = TRUE;
						break;
					}
					default:
					{
						theApp.m_dbEndox.SetQueryTimeout(15);
						OnPazienteRefresh();
						return;
						break;
					}
					}
				}

				if (bSoloPazienti)
					lSearchType -= 2;
			}

			// Impostazioni comuni a tutti gli stati del programma...
			m_pQueryDlg->m_lRelazione = lSearchType;
			m_pQueryDlg->m_pPazientiSet = pQueryPazientiSet;
			m_pQueryDlg->m_pJoinEsamiSet = pQueryEsamiSet;
			m_pQueryDlg->m_strPazFilter = strPazientiFilter;
			m_pQueryDlg->m_strEsameFrom = strEsamiFrom;
			m_pQueryDlg->m_strEsameWhere = strEsamiWhere;
			m_pQueryDlg->m_bCercaPaziente = FALSE;

			// if (!theApp.m_bPazientiUsaVista)
			pQueryPazientiSet->SetSortRecord("Cognome, Nome");
			pQueryEsamiSet->SetSortRecord("EEsami.Data");

			switch (lSearchType)
			{
			case FILTRO_SOLO_PAZIENTI:
			{
				pQueryPazientiSet->SetOpenFilter(strPazientiFilter);
				//theApp.AfxMessageBoxEndo(pQueryPazientiSet->GetQuery());
				pQueryPazientiSet->OpenRecordset("CEsamiView::OnApplicaQuery");

				if (strPazientiFilter.IsEmpty())
				{
					nIDErrorString = IDS_RICERCA_NO_FIELDS;
				}
				else
				{
					if (pQueryPazientiSet->IsOpen() && !pQueryPazientiSet->IsBOF() && !pQueryPazientiSet->IsEOF())
						m_pQueryDlg->CreateModelessDialog(this);
					else
						nIDErrorString = IDS_RICERCA_NO_RESULTS;
				}
				break;
			}
			case FILTRO_PAZIENTI_ESAMI:
			{
				pQueryPazientiSet->SetOpenFilter(strPazientiFilter);
				pQueryPazientiSet->OpenRecordset("CEsamiView::OnApplicaQuery");

				pQueryEsamiSet->SetFromWhere(strEsamiFrom, strEsamiWhere);
				pQueryEsamiSet->OpenRecordset("CEsamiView::OnApplicaQuery");

				if (strPazientiFilter.IsEmpty() && strEsamiWhere.IsEmpty())
				{
					nIDErrorString = IDS_RICERCA_NO_FIELDS;
				}
				else
				{
					if (pQueryPazientiSet->IsOpen() && !pQueryPazientiSet->IsBOF() && !pQueryPazientiSet->IsEOF() && pQueryEsamiSet->IsOpen() && !pQueryEsamiSet->IsBOF() && !pQueryEsamiSet->IsEOF())
						m_pQueryDlg->CreateModelessDialog(this);
					else
						nIDErrorString = IDS_RICERCA_NO_RESULTS;
				}
				break;
			}
			case FILTRO_SOLO_ESAMI:
			{
				pQueryEsamiSet->SetFromWhere(strEsamiFrom, strEsamiWhere);
				pQueryEsamiSet->OpenRecordset("CEsamiView::OnApplicaQuery");

				if (strEsamiWhere.IsEmpty())
				{
					nIDErrorString = IDS_RICERCA_NO_FIELDS;
				}
				else
				{
					if (pQueryEsamiSet->IsOpen() && !pQueryEsamiSet->IsBOF() && !pQueryEsamiSet->IsEOF())
						m_pQueryDlg->CreateModelessDialog(this);
					else
						nIDErrorString = IDS_RICERCA_NO_RESULTS_EXAM;
				}
				break;
			}
			case FILTRO_PAZIENTI_ESAMI_ONLYPATIENTS:
			case FILTRO_SOLO_ESAMI_ONLYPATIENTS:
			{
				pQueryPazientiSet->SetOpenFilter(strPazientiFilter);
				pQueryPazientiSet->OpenRecordset("CEsamiView::OnApplicaQuery");

				pQueryEsamiSet->SetFromWhere(strEsamiFrom, strEsamiWhere);
				pQueryEsamiSet->OpenRecordset("CEsamiView::OnApplicaQuery");

				if (strPazientiFilter.IsEmpty() && strEsamiWhere.IsEmpty())
				{
					nIDErrorString = IDS_RICERCA_NO_FIELDS;
				}
				else
				{
					if (pQueryPazientiSet->IsOpen() && !pQueryPazientiSet->IsBOF() && !pQueryPazientiSet->IsEOF() && pQueryEsamiSet->IsOpen() && !pQueryEsamiSet->IsBOF() && !pQueryEsamiSet->IsEOF())
						m_pQueryDlg->CreateModelessDialog(this);
					else
						nIDErrorString = IDS_RICERCA_NO_RESULTS;
				}
				break;
			}
			default:
			{
				ASSERT(FALSE);
				break;
			}
			}

			if (nIDErrorString == 0)
				OnPazienteRefresh();

			if (nIDErrorString != 0 || m_pQueryDlg->m_lTotale == 0)
			{
				if (nIDErrorString)
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(nIDErrorString), (nIDErrorString == IDS_RICERCA_NO_FIELDS) ? MB_ICONSTOP : MB_ICONINFORMATION);

				SendMessage(EM_DESTROY_QUERY_WND);
			}

			if (m_bRicercaDiretta && nIDErrorString != 0)
				PostMessage(WM_COMMAND, IDC_PAZIENTE_QUERY_DEF);
			else
				m_bRicercaDiretta = FALSE;
		}
	}
	else
	{
		long lSearchType = FILTRO_PAZIENTI_ESAMI;

		// per sicurezza distruggo la finestra di ricerca //
		SendMessage(EM_DESTROY_QUERY_WND);

		//
		CString strPazientiFilter;
		CString strEsamiFrom = "";
		CString strEsamiWhere = "";

		// Calcolo che tipo di ricerca devo effettuare...
		//   -1 = tipo filtro specificato: esami
		//    0 = tipo filtro specificato: pazienti ed esami
		//    1 = tipo filtro specificato: pazienti
		if (theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI)
		{
			lSearchType++;

			// Costruzione filtro di ricerca per i pazienti...
			ComposeFilter(strPazientiFilter);
		}

		//
		UpdateData(TRUE);

		//
		if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
		{
			lSearchType--;
			for (int i = 0; i < form_list_total; i++)
				if (m_pDynForm[i] != NULL)
					m_pDynForm[i]->SendMessage(MSG_FORM_SEARCHNEW, (WPARAM)&strEsamiWhere, (LPARAM)&strEsamiFrom);

			CString strUO;
			strUO.Format("EESAMI.UO=%li", theApp.m_lUO);
			if (strEsamiWhere.IsEmpty())
				strEsamiWhere = strUO;
			else
				strEsamiWhere += " AND " + strUO;
		}

#ifdef _DEBUG
		CString strMessageBox;
		strMessageBox.Format("---------- ---------- ---------- ---------- ----------\n\nFILTRO PAZIENTI\n\n%s\n\n---------- ---------- ---------- ---------- ----------\n\nFILTRO ESAMI\n\n%s\n\n---------- ---------- ---------- ---------- ----------\n\nFROM ESAMI\n\n%s\n\n---------- ---------- ---------- ---------- ----------", strPazientiFilter, strEsamiWhere, strEsamiFrom);
		theApp.AfxMessageBoxEndo(strMessageBox);
#endif

		switch (lSearchType)
		{
		case FILTRO_SOLO_ESAMI_ONLYPATIENTS:
		case FILTRO_PAZIENTI_ESAMI_ONLYPATIENTS:
		{
			break;
		}
		case FILTRO_SOLO_ESAMI:
		case FILTRO_PAZIENTI_ESAMI:
		{
			CJoinEsamiSet setTemp;
			setTemp.SetFromWhere(strEsamiFrom, strEsamiWhere);

			CString strQuery;
			strQuery.Format("SELECT COUNT(*) AS CONTEGGIO FROM ((%s WHERE %s AND EESAMI.ELIMINATO=0) A INNER JOIN EPAZIENTI ON A.PAZIENTE=EPAZIENTI.CONTATORE AND EPAZIENTI.ELIMINATO=0)", setTemp.GetDefaultSQL(), strEsamiWhere);

			CRecordset setCount(&theApp.m_dbEndox);

			DWORD timeOpen = timeGetTime();
			setCount.Open(CRecordset::snapshot, strQuery, CRecordset::readOnly);

			if (theApp.m_bSaveCompleteLog)
				CLogFileWriter::Get()->WriteLogLine0_DB(timeGetTime() - timeOpen, strQuery, "CEsamiView::OnApplicaQuery");

			if (theApp.m_pShowDbQueriesWnd != NULL)
				theApp.m_pShowDbQueriesWnd->WriteLine(timeGetTime() - timeOpen, strQuery, "CEsamiView::OnApplicaQuery");

			if (!setCount.IsEOF())
			{
				CString strCount;
				setCount.GetFieldValue("CONTEGGIO", strCount);

				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_FOUNDED_EXAMS) + strCount);
			}

			if (setCount.IsOpen())
				setCount.Close();

			OnPazienteRefresh();

			break;
		}
		case FILTRO_SOLO_PAZIENTI:
		{
			CString strQuery;
			if (!strPazientiFilter.IsEmpty())
				strQuery.Format("SELECT COUNT(*) AS CONTEGGIO FROM EPAZIENTI WHERE %s AND EPAZIENTI.ELIMINATO=0", strPazientiFilter);
			else
				strQuery.Format("SELECT COUNT(*) AS CONTEGGIO FROM EPAZIENTI WHERE EPAZIENTI.ELIMINATO=0");

			CRecordset setCount(&theApp.m_dbEndox);

			DWORD timeOpen = timeGetTime();
			setCount.Open(CRecordset::snapshot, strQuery, CRecordset::readOnly);

			if (theApp.m_bSaveCompleteLog)
				CLogFileWriter::Get()->WriteLogLine0_DB(timeGetTime() - timeOpen, strQuery, "CEsamiView::OnApplicaQuery");

			if (theApp.m_pShowDbQueriesWnd != NULL)
				theApp.m_pShowDbQueriesWnd->WriteLine(timeGetTime() - timeOpen, strQuery, "CEsamiView::OnApplicaQuery");

			if (!setCount.IsEOF())
			{
				CString strCount;
				setCount.GetFieldValue("CONTEGGIO", strCount);

				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_FOUNDED_PATIENTS) + strCount);
			}

			if (setCount.IsOpen())
				setCount.Close();

			OnPazienteRefresh();

			break;
		}
		default:
		{
			ASSERT(FALSE);
			break;
		}
		}
	}

	theApp.m_dbEndox.SetQueryTimeout(15);
}

BOOL CEsamiView::OnEsamiMove(UINT nIDMoveCommand, BOOL bDeleteSelectedImages)
{
	BOOL bReturn = FALSE;

	//Gabriel BUG 6225 - Lista DO
	if (theApp.m_lInstanceCountCImageDlg > 0 && m_pImageDlg != NULL)
	{
		m_pImageDlg->SendMessage(EPM_EXAMCHANGED);
		m_pImageDlg = NULL;
	}

	// Sandro 14/12/2015 // RIMA 15135 //

	if (!theApp.m_sPassedConnectionString.IsEmpty())
	{
		m_bVisualizzaTastoCaricaImmagini = FALSE;
		//m_bVisualizzaTastoCaricaImmagini = TRUE;
	}
	//

	if (!m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
	{
		bReturn = MoveEsamiRecordset(nIDMoveCommand);
	}

	if (m_pEsamiSet->IsBOF() || m_pEsamiSet->IsEOF())
	{
		m_pEsamiSet->SetEmpty();

		if (m_pEsamiSet->IsOpen())
		{
			m_pEsamiSet->SetFieldNull(NULL, TRUE);
		}

		CaricaInterfaccia(-1);
	}
	else
	{
		CaricaInterfaccia(max(m_pEsamiSet->m_lIDVersione, 1));
	}

	// Marvel BUG 4090 - desconjugação de laudos (tela principal do Tesicapture) 
	// TODO: Warnig!!! at this point [m_pEsamiSet->IsOpen()] might be closed, need to study a way to make it better

	//Simone 09/06/2016
	//	Qui mi sembra il punto più adatto per caricare la lista delle fasi chiuse
	RicaricaDatiAssociatiAllEsame();
	LoadForm();

	UpdateData(FALSE);

	if (m_pFormImmagini)
	{
		m_pFormImmagini->AfterMoveEsame(bDeleteSelectedImages);
	}

	// Sandro 05/08/2016 // RIMA 16037.RN10 //
	UpdateModalityWorklistSCP();

	// Marvel BUG 4090 - desconjugação de laudos (tela principal do Tesicapture) 
	theApp.m_nProgramMode = NOTHING_MODE;

	return bReturn;
}

void CEsamiView::OnEsameFirst()
{
	OnEsamiMove(ID_RECORD_FIRST);
}

void CEsamiView::OnEsameLast()
{
	OnEsamiMove(ID_RECORD_LAST);
}

void CEsamiView::OnEsameNext()
{
	OnEsamiMove(ID_RECORD_NEXT);
}

void CEsamiView::OnEsamePrev()
{
	OnEsamiMove(ID_RECORD_PREV);
}

void CEsamiView::EsameNew(long lTipoEsame, long lIDVersione)
{
	if (theApp.m_nProgramMode == NOTHING_MODE)
	{
		BOOL bCloneForm = FALSE;
		CEsamiSet TempEsami;
		if (!m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
		{
			bCloneForm = TRUE;
			TempEsami.CopyFieldFrom(m_pEsamiSet);

			m_pEsamiSet->SetEmpty();
			m_pEsamiSet->SetFieldNull(NULL, FALSE);

			if (theApp.m_bAnamAuto[0])
				m_pEsamiSet->m_lFumo = TempEsami.m_lFumo;
			if (theApp.m_bAnamAuto[1])
				m_pEsamiSet->m_lSigarette = TempEsami.m_lSigarette;
			if (theApp.m_bAnamAuto[2])
				m_pEsamiSet->m_lCaffe = TempEsami.m_lCaffe;
			if (theApp.m_bAnamAuto[3])
				m_pEsamiSet->m_lAlcool = TempEsami.m_lAlcool;
			if (theApp.m_bAnamAuto[4])
				m_pEsamiSet->m_lSuperAlcolici = TempEsami.m_lSuperAlcolici;
			if (theApp.m_bAnamAuto[5])
				m_pEsamiSet->m_sDenFarmaci = TempEsami.m_sDenFarmaci;
			if (theApp.m_bAnamAuto[6])
				m_pEsamiSet->m_lAssunzione = TempEsami.m_lAssunzione;
			if (theApp.m_bAnamAuto[7])
				m_pEsamiSet->m_fPeso = TempEsami.m_fPeso;
			if (theApp.m_bAnamAuto[8])
				m_pEsamiSet->m_fAltezza = TempEsami.m_fAltezza;
			if (theApp.m_bAnamAuto[9])
				m_pEsamiSet->m_fBMI = TempEsami.m_fBMI;
			if (theApp.m_bAnamAuto[10])
				m_pEsamiSet->m_fBSA = TempEsami.m_fBSA;

			if (TempEsami.m_iAllergie > 0)
			{
				m_pEsamiSet->m_iAllergie = TempEsami.m_iAllergie;
				m_pEsamiSet->m_sDescrizioneAllergie = TempEsami.m_sDescrizioneAllergie;
			}
			if (TempEsami.m_iPacemaker > 0)
			{
				m_pEsamiSet->m_iPacemaker = TempEsami.m_iPacemaker;
				m_pEsamiSet->m_sDescrizionePacemaker = TempEsami.m_sDescrizionePacemaker;
			}
			if (TempEsami.m_iAnticoagulanti > 0)
			{
				m_pEsamiSet->m_iAnticoagulanti = TempEsami.m_iAnticoagulanti;
				m_pEsamiSet->m_sDescrizioneAnticoagulanti = TempEsami.m_sDescrizioneAnticoagulanti;
			}
			if (TempEsami.m_iAntiaggreganti > 1)
			{
				m_pEsamiSet->m_iAntiaggreganti = TempEsami.m_iAntiaggreganti;
				m_pEsamiSet->m_sDescrizioneAntiaggreganti = TempEsami.m_sDescrizioneAntiaggreganti;
			}

			// campi personalizzabili (testo) //

			if (theApp.m_bCopy[0])
				m_pEsamiSet->m_setEP.m_sTesto000 = TempEsami.m_setEP.m_sTesto000;
			if (theApp.m_bCopy[1])
				m_pEsamiSet->m_setEP.m_sTesto001 = TempEsami.m_setEP.m_sTesto001;
			if (theApp.m_bCopy[2])
				m_pEsamiSet->m_setEP.m_sTesto002 = TempEsami.m_setEP.m_sTesto002;
			if (theApp.m_bCopy[3])
				m_pEsamiSet->m_setEP.m_sTesto003 = TempEsami.m_setEP.m_sTesto003;
			if (theApp.m_bCopy[4])
				m_pEsamiSet->m_setEP.m_sTesto004 = TempEsami.m_setEP.m_sTesto004;
			if (theApp.m_bCopy[5])
				m_pEsamiSet->m_setEP.m_sTesto005 = TempEsami.m_setEP.m_sTesto005;
			if (theApp.m_bCopy[6])
				m_pEsamiSet->m_setEP.m_sTesto006 = TempEsami.m_setEP.m_sTesto006;
			if (theApp.m_bCopy[7])
				m_pEsamiSet->m_setEP.m_sTesto007 = TempEsami.m_setEP.m_sTesto007;
			if (theApp.m_bCopy[8])
				m_pEsamiSet->m_setEP.m_sTesto008 = TempEsami.m_setEP.m_sTesto008;
			if (theApp.m_bCopy[9])
				m_pEsamiSet->m_setEP.m_sTesto009 = TempEsami.m_setEP.m_sTesto009;
			if (theApp.m_bCopy[10])
				m_pEsamiSet->m_setEP.m_sTesto010 = TempEsami.m_setEP.m_sTesto010;
			if (theApp.m_bCopy[11])
				m_pEsamiSet->m_setEP.m_sTesto011 = TempEsami.m_setEP.m_sTesto011;
			if (theApp.m_bCopy[12])
				m_pEsamiSet->m_setEP.m_sTesto012 = TempEsami.m_setEP.m_sTesto012;
			if (theApp.m_bCopy[13])
				m_pEsamiSet->m_setEP.m_sTesto013 = TempEsami.m_setEP.m_sTesto013;
			if (theApp.m_bCopy[14])
				m_pEsamiSet->m_setEP.m_sTesto014 = TempEsami.m_setEP.m_sTesto014;
			if (theApp.m_bCopy[15])
				m_pEsamiSet->m_setEP.m_sTesto015 = TempEsami.m_setEP.m_sTesto015;
			if (theApp.m_bCopy[16])
				m_pEsamiSet->m_setEP.m_sTesto016 = TempEsami.m_setEP.m_sTesto016;
			if (theApp.m_bCopy[17])
				m_pEsamiSet->m_setEP.m_sTesto017 = TempEsami.m_setEP.m_sTesto017;
			if (theApp.m_bCopy[18])
				m_pEsamiSet->m_setEP.m_sTesto018 = TempEsami.m_setEP.m_sTesto018;
			if (theApp.m_bCopy[19])
				m_pEsamiSet->m_setEP.m_sTesto019 = TempEsami.m_setEP.m_sTesto019;
			if (theApp.m_bCopy[20])
				m_pEsamiSet->m_setEP.m_sTesto020 = TempEsami.m_setEP.m_sTesto020;
			if (theApp.m_bCopy[21])
				m_pEsamiSet->m_setEP.m_sTesto021 = TempEsami.m_setEP.m_sTesto021;
			if (theApp.m_bCopy[22])
				m_pEsamiSet->m_setEP.m_sTesto022 = TempEsami.m_setEP.m_sTesto022;
			if (theApp.m_bCopy[23])
				m_pEsamiSet->m_setEP.m_sTesto023 = TempEsami.m_setEP.m_sTesto023;
			if (theApp.m_bCopy[24])
				m_pEsamiSet->m_setEP.m_sTesto024 = TempEsami.m_setEP.m_sTesto024;
			if (theApp.m_bCopy[25])
				m_pEsamiSet->m_setEP.m_sTesto025 = TempEsami.m_setEP.m_sTesto025;
			if (theApp.m_bCopy[26])
				m_pEsamiSet->m_setEP.m_sTesto026 = TempEsami.m_setEP.m_sTesto026;
			if (theApp.m_bCopy[27])
				m_pEsamiSet->m_setEP.m_sTesto027 = TempEsami.m_setEP.m_sTesto027;
			if (theApp.m_bCopy[28])
				m_pEsamiSet->m_setEP.m_sTesto028 = TempEsami.m_setEP.m_sTesto028;
			if (theApp.m_bCopy[29])
				m_pEsamiSet->m_setEP.m_sTesto029 = TempEsami.m_setEP.m_sTesto029;
			if (theApp.m_bCopy[30])
				m_pEsamiSet->m_setEP.m_sTesto030 = TempEsami.m_setEP.m_sTesto030;
			if (theApp.m_bCopy[31])
				m_pEsamiSet->m_setEP.m_sTesto031 = TempEsami.m_setEP.m_sTesto031;
			if (theApp.m_bCopy[32])
				m_pEsamiSet->m_setEP.m_sTesto032 = TempEsami.m_setEP.m_sTesto032;
			if (theApp.m_bCopy[33])
				m_pEsamiSet->m_setEP.m_sTesto033 = TempEsami.m_setEP.m_sTesto033;
			if (theApp.m_bCopy[34])
				m_pEsamiSet->m_setEP.m_sTesto034 = TempEsami.m_setEP.m_sTesto034;
			if (theApp.m_bCopy[35])
				m_pEsamiSet->m_setEP.m_sTesto035 = TempEsami.m_setEP.m_sTesto035;
			if (theApp.m_bCopy[36])
				m_pEsamiSet->m_setEP.m_sTesto036 = TempEsami.m_setEP.m_sTesto036;
			if (theApp.m_bCopy[37])
				m_pEsamiSet->m_setEP.m_sTesto037 = TempEsami.m_setEP.m_sTesto037;
			if (theApp.m_bCopy[38])
				m_pEsamiSet->m_setEP.m_sTesto038 = TempEsami.m_setEP.m_sTesto038;
			if (theApp.m_bCopy[39])
				m_pEsamiSet->m_setEP.m_sTesto039 = TempEsami.m_setEP.m_sTesto039;
			if (theApp.m_bCopy[40])
				m_pEsamiSet->m_setEP.m_sTesto040 = TempEsami.m_setEP.m_sTesto040;
			if (theApp.m_bCopy[41])
				m_pEsamiSet->m_setEP.m_sTesto041 = TempEsami.m_setEP.m_sTesto041;
			if (theApp.m_bCopy[42])
				m_pEsamiSet->m_setEP.m_sTesto042 = TempEsami.m_setEP.m_sTesto042;
			if (theApp.m_bCopy[43])
				m_pEsamiSet->m_setEP.m_sTesto043 = TempEsami.m_setEP.m_sTesto043;
			if (theApp.m_bCopy[44])
				m_pEsamiSet->m_setEP.m_sTesto044 = TempEsami.m_setEP.m_sTesto044;
			if (theApp.m_bCopy[45])
				m_pEsamiSet->m_setEP.m_sTesto045 = TempEsami.m_setEP.m_sTesto045;
			if (theApp.m_bCopy[46])
				m_pEsamiSet->m_setEP.m_sTesto046 = TempEsami.m_setEP.m_sTesto046;
			if (theApp.m_bCopy[47])
				m_pEsamiSet->m_setEP.m_sTesto047 = TempEsami.m_setEP.m_sTesto047;
			if (theApp.m_bCopy[48])
				m_pEsamiSet->m_setEP.m_sTesto048 = TempEsami.m_setEP.m_sTesto048;
			if (theApp.m_bCopy[49])
				m_pEsamiSet->m_setEP.m_sTesto049 = TempEsami.m_setEP.m_sTesto049;
			if (theApp.m_bCopy[50])
				m_pEsamiSet->m_setEP.m_sTesto050 = TempEsami.m_setEP.m_sTesto050;
			if (theApp.m_bCopy[51])
				m_pEsamiSet->m_setEP.m_sTesto051 = TempEsami.m_setEP.m_sTesto051;
			if (theApp.m_bCopy[52])
				m_pEsamiSet->m_setEP.m_sTesto052 = TempEsami.m_setEP.m_sTesto052;
			if (theApp.m_bCopy[53])
				m_pEsamiSet->m_setEP.m_sTesto053 = TempEsami.m_setEP.m_sTesto053;
			if (theApp.m_bCopy[54])
				m_pEsamiSet->m_setEP.m_sTesto054 = TempEsami.m_setEP.m_sTesto054;
			if (theApp.m_bCopy[55])
				m_pEsamiSet->m_setEP.m_sTesto055 = TempEsami.m_setEP.m_sTesto055;
			if (theApp.m_bCopy[56])
				m_pEsamiSet->m_setEP.m_sTesto056 = TempEsami.m_setEP.m_sTesto056;
			if (theApp.m_bCopy[57])
				m_pEsamiSet->m_setEP.m_sTesto057 = TempEsami.m_setEP.m_sTesto057;
			if (theApp.m_bCopy[58])
				m_pEsamiSet->m_setEP.m_sTesto058 = TempEsami.m_setEP.m_sTesto058;
			if (theApp.m_bCopy[59])
				m_pEsamiSet->m_setEP.m_sTesto059 = TempEsami.m_setEP.m_sTesto059;
			if (theApp.m_bCopy[60])
				m_pEsamiSet->m_setEP.m_sTesto060 = TempEsami.m_setEP.m_sTesto060;
			if (theApp.m_bCopy[61])
				m_pEsamiSet->m_setEP.m_sTesto061 = TempEsami.m_setEP.m_sTesto061;
			if (theApp.m_bCopy[62])
				m_pEsamiSet->m_setEP.m_sTesto062 = TempEsami.m_setEP.m_sTesto062;
			if (theApp.m_bCopy[63])
				m_pEsamiSet->m_setEP.m_sTesto063 = TempEsami.m_setEP.m_sTesto063;
			if (theApp.m_bCopy[64])
				m_pEsamiSet->m_setEP.m_sTesto064 = TempEsami.m_setEP.m_sTesto064;
			if (theApp.m_bCopy[65])
				m_pEsamiSet->m_setEP.m_sTesto065 = TempEsami.m_setEP.m_sTesto065;
			if (theApp.m_bCopy[66])
				m_pEsamiSet->m_setEP.m_sTesto066 = TempEsami.m_setEP.m_sTesto066;
			if (theApp.m_bCopy[67])
				m_pEsamiSet->m_setEP.m_sTesto067 = TempEsami.m_setEP.m_sTesto067;
			if (theApp.m_bCopy[68])
				m_pEsamiSet->m_setEP.m_sTesto068 = TempEsami.m_setEP.m_sTesto068;
			if (theApp.m_bCopy[69])
				m_pEsamiSet->m_setEP.m_sTesto069 = TempEsami.m_setEP.m_sTesto069;
			if (theApp.m_bCopy[70])
				m_pEsamiSet->m_setEP.m_sTesto070 = TempEsami.m_setEP.m_sTesto070;
			if (theApp.m_bCopy[71])
				m_pEsamiSet->m_setEP.m_sTesto071 = TempEsami.m_setEP.m_sTesto071;
			if (theApp.m_bCopy[72])
				m_pEsamiSet->m_setEP.m_sTesto072 = TempEsami.m_setEP.m_sTesto072;
			if (theApp.m_bCopy[73])
				m_pEsamiSet->m_setEP.m_sTesto073 = TempEsami.m_setEP.m_sTesto073;
			if (theApp.m_bCopy[74])
				m_pEsamiSet->m_setEP.m_sTesto074 = TempEsami.m_setEP.m_sTesto074;
			if (theApp.m_bCopy[75])
				m_pEsamiSet->m_setEP.m_sTesto075 = TempEsami.m_setEP.m_sTesto075;
			if (theApp.m_bCopy[76])
				m_pEsamiSet->m_setEP.m_sTesto076 = TempEsami.m_setEP.m_sTesto076;
			if (theApp.m_bCopy[77])
				m_pEsamiSet->m_setEP.m_sTesto077 = TempEsami.m_setEP.m_sTesto077;
			if (theApp.m_bCopy[78])
				m_pEsamiSet->m_setEP.m_sTesto078 = TempEsami.m_setEP.m_sTesto078;
			if (theApp.m_bCopy[79])
				m_pEsamiSet->m_setEP.m_sTesto079 = TempEsami.m_setEP.m_sTesto079;
			if (theApp.m_bCopy[80])
				m_pEsamiSet->m_setEP.m_sTesto080 = TempEsami.m_setEP.m_sTesto080;
			if (theApp.m_bCopy[81])
				m_pEsamiSet->m_setEP.m_sTesto081 = TempEsami.m_setEP.m_sTesto081;
			if (theApp.m_bCopy[82])
				m_pEsamiSet->m_setEP.m_sTesto082 = TempEsami.m_setEP.m_sTesto082;
			if (theApp.m_bCopy[83])
				m_pEsamiSet->m_setEP.m_sTesto083 = TempEsami.m_setEP.m_sTesto083;
			if (theApp.m_bCopy[84])
				m_pEsamiSet->m_setEP.m_sTesto084 = TempEsami.m_setEP.m_sTesto084;
			if (theApp.m_bCopy[85])
				m_pEsamiSet->m_setEP.m_sTesto085 = TempEsami.m_setEP.m_sTesto085;
			if (theApp.m_bCopy[86])
				m_pEsamiSet->m_setEP.m_sTesto086 = TempEsami.m_setEP.m_sTesto086;
			if (theApp.m_bCopy[87])
				m_pEsamiSet->m_setEP.m_sTesto087 = TempEsami.m_setEP.m_sTesto087;
			if (theApp.m_bCopy[88])
				m_pEsamiSet->m_setEP.m_sTesto088 = TempEsami.m_setEP.m_sTesto088;
			if (theApp.m_bCopy[89])
				m_pEsamiSet->m_setEP.m_sTesto089 = TempEsami.m_setEP.m_sTesto089;
			if (theApp.m_bCopy[90])
				m_pEsamiSet->m_setEP.m_sTesto090 = TempEsami.m_setEP.m_sTesto090;
			if (theApp.m_bCopy[91])
				m_pEsamiSet->m_setEP.m_sTesto091 = TempEsami.m_setEP.m_sTesto091;
			if (theApp.m_bCopy[92])
				m_pEsamiSet->m_setEP.m_sTesto092 = TempEsami.m_setEP.m_sTesto092;
			if (theApp.m_bCopy[93])
				m_pEsamiSet->m_setEP.m_sTesto093 = TempEsami.m_setEP.m_sTesto093;
			if (theApp.m_bCopy[94])
				m_pEsamiSet->m_setEP.m_sTesto094 = TempEsami.m_setEP.m_sTesto094;
			if (theApp.m_bCopy[95])
				m_pEsamiSet->m_setEP.m_sTesto095 = TempEsami.m_setEP.m_sTesto095;
			if (theApp.m_bCopy[96])
				m_pEsamiSet->m_setEP.m_sTesto096 = TempEsami.m_setEP.m_sTesto096;
			if (theApp.m_bCopy[97])
				m_pEsamiSet->m_setEP.m_sTesto097 = TempEsami.m_setEP.m_sTesto097;
			if (theApp.m_bCopy[98])
				m_pEsamiSet->m_setEP.m_sTesto098 = TempEsami.m_setEP.m_sTesto098;
			if (theApp.m_bCopy[99])
				m_pEsamiSet->m_setEP.m_sTesto099 = TempEsami.m_setEP.m_sTesto099;

			// campi personalizzabili (RTF) //

			if (theApp.m_bCopyRtf[0])
			{
				m_pEsamiSet->m_setEP.m_sTestoRtf000 = TempEsami.m_setEP.m_sTestoRtf000;
				m_pEsamiSet->m_setEP.m_sTestoTxt000 = TempEsami.m_setEP.m_sTestoTxt000;
			}
			if (theApp.m_bCopyRtf[1])
			{
				m_pEsamiSet->m_setEP.m_sTestoRtf001 = TempEsami.m_setEP.m_sTestoRtf001;
				m_pEsamiSet->m_setEP.m_sTestoTxt001 = TempEsami.m_setEP.m_sTestoTxt001;
			}
			if (theApp.m_bCopyRtf[2])
			{
				m_pEsamiSet->m_setEP.m_sTestoRtf002 = TempEsami.m_setEP.m_sTestoRtf002;
				m_pEsamiSet->m_setEP.m_sTestoTxt002 = TempEsami.m_setEP.m_sTestoTxt002;
			}
			if (theApp.m_bCopyRtf[3])
			{
				m_pEsamiSet->m_setEP.m_sTestoRtf003 = TempEsami.m_setEP.m_sTestoRtf003;
				m_pEsamiSet->m_setEP.m_sTestoTxt003 = TempEsami.m_setEP.m_sTestoTxt003;
			}
			if (theApp.m_bCopyRtf[4])
			{
				m_pEsamiSet->m_setEP.m_sTestoRtf004 = TempEsami.m_setEP.m_sTestoRtf004;
				m_pEsamiSet->m_setEP.m_sTestoTxt004 = TempEsami.m_setEP.m_sTestoTxt004;
			}
			if (theApp.m_bCopyRtf[5])
			{
				m_pEsamiSet->m_setEP.m_sTestoRtf005 = TempEsami.m_setEP.m_sTestoRtf005;
				m_pEsamiSet->m_setEP.m_sTestoTxt005 = TempEsami.m_setEP.m_sTestoTxt005;
			}
			if (theApp.m_bCopyRtf[6])
			{
				m_pEsamiSet->m_setEP.m_sTestoRtf006 = TempEsami.m_setEP.m_sTestoRtf006;
				m_pEsamiSet->m_setEP.m_sTestoTxt006 = TempEsami.m_setEP.m_sTestoTxt006;
			}
			if (theApp.m_bCopyRtf[7])
			{
				m_pEsamiSet->m_setEP.m_sTestoRtf007 = TempEsami.m_setEP.m_sTestoRtf007;
				m_pEsamiSet->m_setEP.m_sTestoTxt007 = TempEsami.m_setEP.m_sTestoTxt007;
			}
			if (theApp.m_bCopyRtf[8])
			{
				m_pEsamiSet->m_setEP.m_sTestoRtf008 = TempEsami.m_setEP.m_sTestoRtf008;
				m_pEsamiSet->m_setEP.m_sTestoTxt008 = TempEsami.m_setEP.m_sTestoTxt008;
			}
			if (theApp.m_bCopyRtf[9])
			{
				m_pEsamiSet->m_setEP.m_sTestoRtf009 = TempEsami.m_setEP.m_sTestoRtf009;
				m_pEsamiSet->m_setEP.m_sTestoTxt009 = TempEsami.m_setEP.m_sTestoTxt009;
			}
			if (theApp.m_bCopyRtf[10])
			{
				m_pEsamiSet->m_setEP.m_sTestoRtf010 = TempEsami.m_setEP.m_sTestoRtf010;
				m_pEsamiSet->m_setEP.m_sTestoTxt010 = TempEsami.m_setEP.m_sTestoTxt010;
			}
			if (theApp.m_bCopyRtf[11])
			{
				m_pEsamiSet->m_setEP.m_sTestoRtf011 = TempEsami.m_setEP.m_sTestoRtf011;
				m_pEsamiSet->m_setEP.m_sTestoTxt011 = TempEsami.m_setEP.m_sTestoTxt011;
			}
			if (theApp.m_bCopyRtf[12])
			{
				m_pEsamiSet->m_setEP.m_sTestoRtf012 = TempEsami.m_setEP.m_sTestoRtf012;
				m_pEsamiSet->m_setEP.m_sTestoTxt012 = TempEsami.m_setEP.m_sTestoTxt012;
			}
			if (theApp.m_bCopyRtf[13])
			{
				m_pEsamiSet->m_setEP.m_sTestoRtf013 = TempEsami.m_setEP.m_sTestoRtf013;
				m_pEsamiSet->m_setEP.m_sTestoTxt013 = TempEsami.m_setEP.m_sTestoTxt013;
			}
			if (theApp.m_bCopyRtf[14])
			{
				m_pEsamiSet->m_setEP.m_sTestoRtf014 = TempEsami.m_setEP.m_sTestoRtf014;
				m_pEsamiSet->m_setEP.m_sTestoTxt014 = TempEsami.m_setEP.m_sTestoTxt014;
			}
			if (theApp.m_bCopyRtf[15])
			{
				m_pEsamiSet->m_setEP.m_sTestoRtf015 = TempEsami.m_setEP.m_sTestoRtf015;
				m_pEsamiSet->m_setEP.m_sTestoTxt015 = TempEsami.m_setEP.m_sTestoTxt015;
			}
			if (theApp.m_bCopyRtf[16])
			{
				m_pEsamiSet->m_setEP.m_sTestoRtf016 = TempEsami.m_setEP.m_sTestoRtf016;
				m_pEsamiSet->m_setEP.m_sTestoTxt016 = TempEsami.m_setEP.m_sTestoTxt016;
			}
			if (theApp.m_bCopyRtf[17])
			{
				m_pEsamiSet->m_setEP.m_sTestoRtf017 = TempEsami.m_setEP.m_sTestoRtf017;
				m_pEsamiSet->m_setEP.m_sTestoTxt017 = TempEsami.m_setEP.m_sTestoTxt017;
			}
			if (theApp.m_bCopyRtf[18])
			{
				m_pEsamiSet->m_setEP.m_sTestoRtf018 = TempEsami.m_setEP.m_sTestoRtf018;
				m_pEsamiSet->m_setEP.m_sTestoTxt018 = TempEsami.m_setEP.m_sTestoTxt018;
			}
			if (theApp.m_bCopyRtf[19])
			{
				m_pEsamiSet->m_setEP.m_sTestoRtf019 = TempEsami.m_setEP.m_sTestoRtf019;
				m_pEsamiSet->m_setEP.m_sTestoTxt019 = TempEsami.m_setEP.m_sTestoTxt019;
			}

			// campi personalizzabili (checklist) //

			if (theApp.m_bCopyCL[0])
			{
				m_pEsamiSet->m_setEP.m_sTestoCLRtf000 = TempEsami.m_setEP.m_sTestoCLRtf000;
				m_pEsamiSet->m_setEP.m_sTestoCLTxt000 = TempEsami.m_setEP.m_sTestoCLTxt000;
			}
			if (theApp.m_bCopyCL[1])
			{
				m_pEsamiSet->m_setEP.m_sTestoCLRtf001 = TempEsami.m_setEP.m_sTestoCLRtf001;
				m_pEsamiSet->m_setEP.m_sTestoCLTxt001 = TempEsami.m_setEP.m_sTestoCLTxt001;
			}
			if (theApp.m_bCopyCL[2])
			{
				m_pEsamiSet->m_setEP.m_sTestoCLRtf002 = TempEsami.m_setEP.m_sTestoCLRtf002;
				m_pEsamiSet->m_setEP.m_sTestoCLTxt002 = TempEsami.m_setEP.m_sTestoCLTxt002;
			}
			if (theApp.m_bCopyCL[3])
			{
				m_pEsamiSet->m_setEP.m_sTestoCLRtf003 = TempEsami.m_setEP.m_sTestoCLRtf003;
				m_pEsamiSet->m_setEP.m_sTestoCLTxt003 = TempEsami.m_setEP.m_sTestoCLTxt003;
			}
			if (theApp.m_bCopyCL[4])
			{
				m_pEsamiSet->m_setEP.m_sTestoCLRtf004 = TempEsami.m_setEP.m_sTestoCLRtf004;
				m_pEsamiSet->m_setEP.m_sTestoCLTxt004 = TempEsami.m_setEP.m_sTestoCLTxt004;
			}
			if (theApp.m_bCopyCL[5])
			{
				m_pEsamiSet->m_setEP.m_sTestoCLRtf005 = TempEsami.m_setEP.m_sTestoCLRtf005;
				m_pEsamiSet->m_setEP.m_sTestoCLTxt005 = TempEsami.m_setEP.m_sTestoCLTxt005;
			}
			if (theApp.m_bCopyCL[6])
			{
				m_pEsamiSet->m_setEP.m_sTestoCLRtf006 = TempEsami.m_setEP.m_sTestoCLRtf006;
				m_pEsamiSet->m_setEP.m_sTestoCLTxt006 = TempEsami.m_setEP.m_sTestoCLTxt006;
			}
			if (theApp.m_bCopyCL[7])
			{
				m_pEsamiSet->m_setEP.m_sTestoCLRtf007 = TempEsami.m_setEP.m_sTestoCLRtf007;
				m_pEsamiSet->m_setEP.m_sTestoCLTxt007 = TempEsami.m_setEP.m_sTestoCLTxt007;
			}
			if (theApp.m_bCopyCL[8])
			{
				m_pEsamiSet->m_setEP.m_sTestoCLRtf008 = TempEsami.m_setEP.m_sTestoCLRtf008;
				m_pEsamiSet->m_setEP.m_sTestoCLTxt008 = TempEsami.m_setEP.m_sTestoCLTxt008;
			}
			if (theApp.m_bCopyCL[9])
			{
				m_pEsamiSet->m_setEP.m_sTestoCLRtf009 = TempEsami.m_setEP.m_sTestoCLRtf009;
				m_pEsamiSet->m_setEP.m_sTestoCLTxt009 = TempEsami.m_setEP.m_sTestoCLTxt009;
			}
			if (theApp.m_bCopyCL[10])
			{
				m_pEsamiSet->m_setEP.m_sTestoCLRtf010 = TempEsami.m_setEP.m_sTestoCLRtf010;
				m_pEsamiSet->m_setEP.m_sTestoCLTxt010 = TempEsami.m_setEP.m_sTestoCLTxt010;
			}
			if (theApp.m_bCopyCL[11])
			{
				m_pEsamiSet->m_setEP.m_sTestoCLRtf011 = TempEsami.m_setEP.m_sTestoCLRtf011;
				m_pEsamiSet->m_setEP.m_sTestoCLTxt011 = TempEsami.m_setEP.m_sTestoCLTxt011;
			}
			if (theApp.m_bCopyCL[12])
			{
				m_pEsamiSet->m_setEP.m_sTestoCLRtf012 = TempEsami.m_setEP.m_sTestoCLRtf012;
				m_pEsamiSet->m_setEP.m_sTestoCLTxt012 = TempEsami.m_setEP.m_sTestoCLTxt012;
			}
			if (theApp.m_bCopyCL[13])
			{
				m_pEsamiSet->m_setEP.m_sTestoCLRtf013 = TempEsami.m_setEP.m_sTestoCLRtf013;
				m_pEsamiSet->m_setEP.m_sTestoCLTxt013 = TempEsami.m_setEP.m_sTestoCLTxt013;
			}
			if (theApp.m_bCopyCL[14])
			{
				m_pEsamiSet->m_setEP.m_sTestoCLRtf014 = TempEsami.m_setEP.m_sTestoCLRtf014;
				m_pEsamiSet->m_setEP.m_sTestoCLTxt014 = TempEsami.m_setEP.m_sTestoCLTxt014;
			}
			if (theApp.m_bCopyCL[15])
			{
				m_pEsamiSet->m_setEP.m_sTestoCLRtf015 = TempEsami.m_setEP.m_sTestoCLRtf015;
				m_pEsamiSet->m_setEP.m_sTestoCLTxt015 = TempEsami.m_setEP.m_sTestoCLTxt015;
			}
			if (theApp.m_bCopyCL[16])
			{
				m_pEsamiSet->m_setEP.m_sTestoCLRtf016 = TempEsami.m_setEP.m_sTestoCLRtf016;
				m_pEsamiSet->m_setEP.m_sTestoCLTxt016 = TempEsami.m_setEP.m_sTestoCLTxt016;
			}
			if (theApp.m_bCopyCL[17])
			{
				m_pEsamiSet->m_setEP.m_sTestoCLRtf017 = TempEsami.m_setEP.m_sTestoCLRtf017;
				m_pEsamiSet->m_setEP.m_sTestoCLTxt017 = TempEsami.m_setEP.m_sTestoCLTxt017;
			}
			if (theApp.m_bCopyCL[18])
			{
				m_pEsamiSet->m_setEP.m_sTestoCLRtf018 = TempEsami.m_setEP.m_sTestoCLRtf018;
				m_pEsamiSet->m_setEP.m_sTestoCLTxt018 = TempEsami.m_setEP.m_sTestoCLTxt018;
			}
			if (theApp.m_bCopyCL[19])
			{
				m_pEsamiSet->m_setEP.m_sTestoCLRtf019 = TempEsami.m_setEP.m_sTestoCLRtf019;
				m_pEsamiSet->m_setEP.m_sTestoCLTxt019 = TempEsami.m_setEP.m_sTestoCLTxt019;
			}

			// campi personalizzabili (data) //

			if (theApp.m_bCopyDate[0])
				m_pEsamiSet->m_setEP.m_lDataOra000 = TempEsami.m_setEP.m_lDataOra000;
			if (theApp.m_bCopyDate[1])
				m_pEsamiSet->m_setEP.m_lDataOra001 = TempEsami.m_setEP.m_lDataOra001;
			if (theApp.m_bCopyDate[2])
				m_pEsamiSet->m_setEP.m_lDataOra002 = TempEsami.m_setEP.m_lDataOra002;
			if (theApp.m_bCopyDate[3])
				m_pEsamiSet->m_setEP.m_lDataOra003 = TempEsami.m_setEP.m_lDataOra003;
			if (theApp.m_bCopyDate[4])
				m_pEsamiSet->m_setEP.m_lDataOra004 = TempEsami.m_setEP.m_lDataOra004;
			if (theApp.m_bCopyDate[5])
				m_pEsamiSet->m_setEP.m_lDataOra005 = TempEsami.m_setEP.m_lDataOra005;
			if (theApp.m_bCopyDate[6])
				m_pEsamiSet->m_setEP.m_lDataOra006 = TempEsami.m_setEP.m_lDataOra006;
			if (theApp.m_bCopyDate[7])
				m_pEsamiSet->m_setEP.m_lDataOra007 = TempEsami.m_setEP.m_lDataOra007;
			if (theApp.m_bCopyDate[8])
				m_pEsamiSet->m_setEP.m_lDataOra008 = TempEsami.m_setEP.m_lDataOra008;
			if (theApp.m_bCopyDate[9])
				m_pEsamiSet->m_setEP.m_lDataOra009 = TempEsami.m_setEP.m_lDataOra009;
			if (theApp.m_bCopyDate[10])
				m_pEsamiSet->m_setEP.m_lDataOra010 = TempEsami.m_setEP.m_lDataOra010;
			if (theApp.m_bCopyDate[11])
				m_pEsamiSet->m_setEP.m_lDataOra011 = TempEsami.m_setEP.m_lDataOra011;
			if (theApp.m_bCopyDate[12])
				m_pEsamiSet->m_setEP.m_lDataOra012 = TempEsami.m_setEP.m_lDataOra012;
			if (theApp.m_bCopyDate[13])
				m_pEsamiSet->m_setEP.m_lDataOra013 = TempEsami.m_setEP.m_lDataOra013;
			if (theApp.m_bCopyDate[14])
				m_pEsamiSet->m_setEP.m_lDataOra014 = TempEsami.m_setEP.m_lDataOra014;
			if (theApp.m_bCopyDate[15])
				m_pEsamiSet->m_setEP.m_lDataOra015 = TempEsami.m_setEP.m_lDataOra015;
			if (theApp.m_bCopyDate[16])
				m_pEsamiSet->m_setEP.m_lDataOra016 = TempEsami.m_setEP.m_lDataOra016;
			if (theApp.m_bCopyDate[17])
				m_pEsamiSet->m_setEP.m_lDataOra017 = TempEsami.m_setEP.m_lDataOra017;
			if (theApp.m_bCopyDate[18])
				m_pEsamiSet->m_setEP.m_lDataOra018 = TempEsami.m_setEP.m_lDataOra018;
			if (theApp.m_bCopyDate[19])
				m_pEsamiSet->m_setEP.m_lDataOra019 = TempEsami.m_setEP.m_lDataOra019;

			// Sandro 09/10/2013 //
			m_pEsamiSet->m_lIDStudio = TempEsami.m_lIDStudio;
			m_pEsamiSet->m_lDataStudio = TempEsami.m_lDataStudio;

		}
		else
		{
			m_pEsamiSet->SetEmpty();
			m_pEsamiSet->SetFieldNull(NULL, FALSE);
		}

		m_pEsamiSet->SetFieldNull(&m_pEsamiSet->m_lPaziente, FALSE);
		m_pEsamiSet->m_lPaziente = m_pPazientiSet->m_lContatore;

		m_pEsamiSet->m_lNumEsame = m_pPazientiSet->m_lTotEsami;
		m_pEsamiSet->m_lData = CCustomDate(TRUE, TRUE).GetDate();

		m_pEsamiSet->m_lIDEsame = lTipoEsame;
		m_pEsamiSet->m_lIDVersione = lIDVersione;

		//16052 Simone - versione checklist a griglia
		//	Alla creazione di un nuovo esame, setto la versione della griglia da utilizzare
		m_pEsamiSet->m_lVersioneGridCL = theApp.m_lLastGridCLVersion;

		m_pEsamiSet->m_lIDSedeEsame = theApp.m_lIDSedeEsameDefault;
		m_pEsamiSet->m_sSalaEsame = theApp.m_sSalaEsameDefault;
		m_pEsamiSet->m_sSalaEsame.MakeUpper();

		// Dati di RICOVERO //
		m_pEsamiSet->m_lProvenienza = theApp.m_bPazienteInternoDefault ? 0 : 1;
		if (m_pPazientiSet->IsFieldNull(&m_pPazientiSet->m_sCodiceRicovero) || m_pPazientiSet->m_sCodiceRicovero == "")
			m_pEsamiSet->m_sRicovero.Format("%li", m_lIDPrenotazione);
		else
			m_pEsamiSet->m_sRicovero = m_pPazientiSet->m_sCodiceRicovero;
		if (m_pPazientiSet->IsFieldNull(&m_pPazientiSet->m_sIdEpisodioRicovero) || m_pPazientiSet->m_sIdEpisodioRicovero == "")
			m_pEsamiSet->m_sIdEpisodioRicovero.Format("");
		else
			m_pEsamiSet->m_sIdEpisodioRicovero = m_pPazientiSet->m_sIdEpisodioRicovero;
		if (m_pPazientiSet->IsFieldNull(&m_pPazientiSet->m_lDataRicoveroCustom) || m_pPazientiSet->m_lDataRicoveroCustom == 0)
			m_pEsamiSet->m_lDataRicoveroCustom = 0;
		else
			m_pEsamiSet->m_lDataRicoveroCustom = m_pPazientiSet->m_lDataRicoveroCustom;
		if (!m_pPazientiSet->IsFieldNull(&m_pPazientiSet->m_lIdRepartoDegenza) && m_pPazientiSet->m_lIdRepartoDegenza > 0)
		{
			m_pEsamiSet->m_lInviante = m_pPazientiSet->m_lIdRepartoDegenza;
			m_pEsamiSet->m_lProvenienza = INTERNO;
		}
		else
		{
			if (theApp.m_bPazienteInternoDefault == FALSE)
			{
				m_pEsamiSet->m_lInviante = m_pPazientiSet->m_lMedicoCurante;
				m_pEsamiSet->m_lProvenienza = ESTERNO;
			}
		}

		// Sandro 20/12/2013 //
		m_pEsamiSet->m_sInvMedico = m_pPazientiSet->m_sMedicoCurante;

		// Sandro 20/12/2013 // RAS 20130172 //
		AMLogin_GetUserID(&m_pEsamiSet->m_lIDUtenteInserimentoEsame);

		//Simone 02/02/2016 - RIMA 16007
		if (theApp.m_bUsaUtenteLoggatoComeMedicoDefault)
		{
			int idMedico = CMediciSet().GetContatoreFromUserID(m_pEsamiSet->m_lIDUtenteInserimentoEsame);
			if (idMedico > 0)
				m_pEsamiSet->m_lMedico = idMedico;
		}
		//

		theApp.m_nProgramMode |= ADD_RECORD_ESAMI;

		RicaricaDatiAssociatiAllEsame();
		LoadForm();
		if (bCloneForm)
			CloneForm(TempEsami.m_lContatore);

		UpdateData(FALSE);
	}
}

void CEsamiView::OnEsameNew()
{
	/* Simone 14/03/2013
	// Nel caso di creazione manuale dell'esame, segnalo il paziente come "utilizzato"
	CPazientiSet pazientiSet;
	CString filter;
	filter.Format("contatore = %li", m_pPazientiSet->m_lContatore);
	pazientiSet.SetOpenFilter(filter);

	if (pazientiSet.OpenRecordset("CEsamiView::OnEsameNew"))
	{
	if (pazientiSet.EditRecordset("CEsamiView::OnEsameNew"))
	{
	pazientiSet.m_lStatoAPC = 4;
	pazientiSet.UpdateRecordset("CEsamiView::OnEsameNew");
	}

	pazientiSet.CloseRecordset("CEsamiView::OnEsameNew");
	}*/

	CExtPatientEventSet().AddEvent(m_pPazientiSet->m_lContatore, usePatient);

	OnEsameNewEndox();
}

void CEsamiView::OnEsameNewCup()
{
	//Davide 20170717 - tentativo velocizzazione worklist
	//OnEsameLast();
	MoveEsamiRecordset(ID_RECORD_LAST);
	//

	CCustomDate dateOggi(TRUE, FALSE);
	CCustomDate dateUltimoEsame(m_pEsamiSet->m_lData);

	CTipoEsameNewDlg dlg(this, this, FALSE, TRUE, 0);
	if (m_lIDTipoEsameAutoInsert > 0)
	{
		// Modifica interfaccia in base al tipo d'esame --> //
		CaricaInterfaccia(-1);
		dlg.SetTipoEsame(m_lIDTipoEsameAutoInsert);
	}
	else
	{
		// Modifica interfaccia in base al tipo d'esame --> //
		CaricaInterfaccia(-1);
		if (dlg.DoModal() != IDOK)
		{
			theApp.m_nProgramMode |= ADD_RECORD_ESAMI;
			OnEsameRefresh();
			return;
		}
	}

	long lTipoEsame = dlg.GetTipoEsame();
	long lIDVersione = GetIDVersione(lTipoEsame);

	CaricaInterfaccia(lIDVersione);
	// <-- Modifica interfaccia in base al tipo d'esame //

	EsameNew(lTipoEsame, lIDVersione);

	// caricamento campi default //
	CEsamiSet ProfilesSet(TRUE);

	CString strFilter;
	strFilter.Format("IDESAME=%li", m_pEsamiSet->m_lIDEsame);
	ProfilesSet.SetOpenFilter(strFilter);
	if (ProfilesSet.OpenRecordset("CEsamiView::OnEsameNew"))
	{
		if (!ProfilesSet.IsEOF())
		{
			// Azzeramento dei campi che non sono logicamente corretti da assegnare al nuovo esame
			ProfilesSet.SetFieldNull(&ProfilesSet.m_lContatore);
			ProfilesSet.SetFieldNull(&ProfilesSet.m_lPaziente);
			ProfilesSet.SetFieldNull(&ProfilesSet.m_lData);
			ProfilesSet.SetFieldNull(&ProfilesSet.m_lMedico);
			ProfilesSet.SetFieldNull(&ProfilesSet.m_lAssistente);
			ProfilesSet.SetFieldNull(&ProfilesSet.m_lInfermiere1);
			ProfilesSet.SetFieldNull(&ProfilesSet.m_lInfermiere2);
			ProfilesSet.SetFieldNull(&ProfilesSet.m_sProgressivoAnno);
			ProfilesSet.SetFieldNull(&ProfilesSet.m_sCodicePrenotazione);
			ProfilesSet.SetFieldNull(&ProfilesSet.m_lIDVersione);

			m_pEsamiSet->CopyFieldFrom(&ProfilesSet, FALSE);
			UpdateData(FALSE);
		}

		ProfilesSet.CloseRecordset("CEsamiView::OnEsameNew");
	}

	// azzero il form delle immagini //
	if (m_pFormImmagini)
		m_pFormImmagini->ResetAlbum();
}

void CEsamiView::OnEsameNewEndox()
{
	OnEsameLast();

	CCustomDate dateOggi(TRUE, FALSE);
	CCustomDate dateUltimoEsame(m_pEsamiSet->m_lData);

	CTipoEsameNewDlg dlg(this, this, FALSE, TRUE, 0);
	if (m_lIDTipoEsameAutoInsert > 0)
	{
		// Prima controllo che l'esame già non sia stato inserito //
		while (dateOggi.GetDate("%Y%m%d") == dateUltimoEsame.GetDate("%Y%m%d"))
		{
			CString strPren;
			strPren.Format("%li", m_lIDPrenotazione);

			// MAZZ The Emperor 20100626: imponiamo che il valore "-1" non venga considerato come valore di prenotazione valido 
			// per permettere l'inserimento di esami da prenotazioni inserite con dicomworklist
			if (m_lIDPrenotazione != -1 && ((strPren == m_pEsamiSet->m_sRicovero) || (m_lIDTipoEsameAutoInsert == m_pEsamiSet->m_lIDEsame)))
			{
				// trovato //
				// OnEsameModify();
				return;
			}

			if (!OnEsamiMove(ID_RECORD_PREV))
			{
				// non ci sono altri esami precedenti //
				break;
			}

			dateUltimoEsame.SetDate(m_pEsamiSet->m_lData);
		}
		OnEsameLast();

		// Modifica interfaccia in base al tipo d'esame --> //
		CaricaInterfaccia(-1);
		dlg.SetTipoEsame(m_lIDTipoEsameAutoInsert);
	}
	else
	{
		// Faccio il controllo della data //
		if (dateOggi.GetDate("%Y%m%d") == dateUltimoEsame.GetDate("%Y%m%d"))
		{
			if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAMIVIEW_EXAM_ALREADY_PRESENT), MB_YESNO) != IDYES)
				return;
		}

		// Modifica interfaccia in base al tipo d'esame --> //
		CaricaInterfaccia(-1);
		if (dlg.DoModal() != IDOK)
		{
			theApp.m_nProgramMode |= ADD_RECORD_ESAMI;
			OnEsameRefresh();
			return;
		}
	}

	long lTipoEsame = dlg.GetTipoEsame();
	long lIDVersione = GetIDVersione(lTipoEsame);

	CaricaInterfaccia(lIDVersione);
	// <-- Modifica interfaccia in base al tipo d'esame //

	if (theApp.m_lModalitaCaricamentoCampiDefault == 0) // i valori di default vengono caricati PRIMA di copiare i dati dall'esame precedente //
		CaricaCampiDefault();

	EsameNew(lTipoEsame, lIDVersione);

	if (theApp.m_lModalitaCaricamentoCampiDefault == 1) // i valori di default vengono caricati DOPO aver copiato i dati dall'esame precedente //
		CaricaCampiDefault();

	// azzero il form delle immagini //
	if (m_pFormImmagini)
		m_pFormImmagini->ResetAlbum();

}

void CEsamiView::InsertNewEsame(long lTipoEsame)
{
	long lIDVersione = GetIDVersione(lTipoEsame);

	CaricaInterfaccia(lIDVersione);
	// <-- Modifica interfaccia in base al tipo d'esame //

	EsameNew(lTipoEsame, lIDVersione);
	if (!m_bValoriDefault)
		OnEsameUpdate();
}

void CEsamiView::OnEsameAllegati()
{
	CDocumentiDlg dlg(this, this, FALSE, FALSE, FALSE);
	dlg.DoModal();

	// Sandro 04/01/2014 // RAS 20130175 //
	RefreshNumDocumentsExam();//Gabriel BUG 6225 - Lista DO
}

void CEsamiView::OnEsameAllegatiCarestream()
{
	CDocumentiDlg dlg(this, this, FALSE, TRUE, FALSE);
	dlg.DoModal();

	// Sandro 04/01/2014 // RAS 20130175 //
	RefreshNumDocumentsExam();//Gabriel BUG 6225 - Lista DO
}

void CEsamiView::OnEsameDelete()
{
	if (theApp.m_nProgramMode == NOTHING_MODE)
	{
		// Sandro 23/06/2017 //
		if ((theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury) && (!m_pEsamiSet->m_sFleuryTrasferito.IsEmpty() && m_pEsamiSet->m_sFleuryTrasferito != "-1"))
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAME_TRASFERITO) + " " + m_pEsamiSet->m_sFleuryTrasferito + ".");
			return;
		}

		// m_lLockedPatient = m_pEsamiSet->m_lPaziente;
		m_lLockedExam = m_pEsamiSet->m_lContatore;
		if (CLockManager::Get()->LockExam(m_lLockedExam))
		{
			if (!m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
			{
				if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_BASEFORM_CONFIRM_EXAM_DEL), MB_ICONEXCLAMATION | MB_DEFBUTTON2 | MB_YESNO) == IDNO)
				{
					CLockManager::Get()->UnlockExam(m_lLockedExam);
					return;
				}

				if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_BASEFORM_CONFIRM_EXAM_DEL_2), MB_ICONSTOP | MB_DEFBUTTON1 | MB_YESNO) == IDYES)
				{
					CLockManager::Get()->UnlockExam(m_lLockedExam);
					return;
				}

				if (m_pEsamiSet->DeleteRecordset("CEsamiView::EsameDelete"))
				{
					m_pEsamiSet->m_lNumEsame--;
					m_pPazientiSet->m_lTotEsami--;

					CString sMotivo = "";

					CMotivoDlg dlg(this, "L'esame è stato cancellato", "Inserire un motivo per la mancata erogazione", FALSE);
					if (dlg.DoModal() == IDOK)
						sMotivo = dlg.GetMotivo();

					//Qui l'esame va aggiunto alla lista dei non erogati
					long userId;
					AMLogin_GetUserID(&userId);
					CEsamiNonErogatiSet().InserisciRecord(m_lLockedExam, userId, sMotivo);

					MovePazientiAndEsami(NULL, TRUE, TRUE);
					OnEsamiMove(NULL);
				}
			}

			CLockManager::Get()->UnlockExam(m_lLockedExam);
		}
	}

	UpdateData(FALSE);
}

BOOL CEsamiView::EsameModify()
{
	// m_lLockedPatient = m_pEsamiSet->m_lPaziente;
	m_lLockedExam = m_pEsamiSet->m_lContatore;
	if (CLockManager::Get()->LockExam(m_lLockedExam))
	{
		BOOL bOK = FALSE;

		if (theApp.m_nProgramMode == NOTHING_MODE)
		{
			theApp.m_nProgramMode |= MODIFY_RECORD_ESAMI;
			bOK = TRUE;
		}

		m_pEsamiSet->RefreshRecordset();
		// Davide Humanitas
		RicaricaDatiAssociatiAllEsame();
		LoadForm();
		//
		UpdateData(FALSE);

		return bOK;
	}

	return FALSE;
}

void CEsamiView::OnEsameModify()
{
	BOOL bModifica = TRUE;

	CString sMessaggio = "";
	if (theApp.m_bPersonalizzazioniBrasileFleury)
	{
		// Sandro 23/06/2017 //
		if (!m_pEsamiSet->m_sFleuryTrasferito.IsEmpty())
		{
			// Julio 22/11/2017 //
			if (m_pEsamiSet->m_sFleuryTrasferito == "-1")
			{
				if (m_pEsamiSet->m_bSuperLocked)
					bModifica = FleuryPossoModificare(sMessaggio, m_pEsamiSet->m_sRicovero, m_pEsamiSet->m_sCodEsame);
			}
			else
			{
				bModifica = FALSE;
				sMessaggio = theApp.GetMessageString(IDS_ESAME_TRASFERITO) + " " + m_pEsamiSet->m_sFleuryTrasferito + ".";
			}
		}
		else
		{
			if (m_pEsamiSet->m_bSuperLocked)
				bModifica = FleuryPossoModificare(sMessaggio, m_pEsamiSet->m_sRicovero, m_pEsamiSet->m_sCodEsame);
		}
	}

	if (!bModifica)
	{
		theApp.AfxMessageBoxEndo(sMessaggio);
		return;
	}

	EsameModify();

	/* metto il fuoco sul primo elemento //
	int nCurSel = m_ctrlGruppoEsame.GetCurSel();
	if (nCurSel >= 0)
	{
	if (CBaseForm* pForm = m_ctrlGruppoEsame.GetSelectedBaseForm())
	{
	TRACE("CEsamiView::OnEsameModify -> SetFocusOnFirst prima\n");
	SetFocus();
	pForm->SetFocusOnFirst();
	TRACE("CEsamiView::OnEsameModify -> SetFocusOnFirst dopo\n");
	}
	}
	*/
}

BOOL CEsamiView::EsameUpdateClassic()
{
	BOOL bOK = FALSE;

	UpdateData(TRUE);
	if (m_pEsamiSet->m_lIDEsame <= 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_BASEFORM_NEED_EXAM_TYPE));
		return FALSE;
	}

	if (theApp.m_nProgramMode & ADD_RECORD_ESAMI)
	{
		// Sandro 04/05/2012 // se inseriscono un certo esame e lo cambiano subito mi "calcolo" al momento del salvataggio l'interfaccia corretta in base a quanto selezionato nella combo del tipo esame //
		long lIDTipoEsame = m_pEsamiSet->m_lIDEsame;
		long lIDSedeEsame = m_pEsamiSet->m_lIDSedeEsame;
		CString sSalaEsame = m_pEsamiSet->m_sSalaEsame;
		long idInviante = m_pEsamiSet->m_lInviante;
		long lIDMedico1 = m_pEsamiSet->m_lMedico; //Julio Medico1

		// Sandro 11/09/2013 // per copiare i farmaci dei pazienti cronici //
		long lIDEsameOld = 0;
		if (theApp.m_lOpzionalePazientiCronici == OPZIONALE_PAZIENTI_CRONICI)
			if (m_pDynForm[sub_pazienticronici_terapia] == NULL)
				lIDEsameOld = CEsamiSet().GetLastPatientExam(m_pPazientiSet->m_lContatore);

		//
		if (m_pEsamiSet->AddNewRecordset("CEsamiView::EsameUpdate"))
		{
			UpdateData(TRUE);

			// PAZIENTE //
			m_pEsamiSet->m_lPaziente = m_pPazientiSet->m_lContatore;

			// IDESAME // Sandro 18/05/2012 // se non c'è la combo del tipo esame nell'interfaccia il campo IDEsame a questo punto rimane nullo //
			if (m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lIDEsame) || (m_pEsamiSet->m_lIDEsame <= 0))
				m_pEsamiSet->m_lIDEsame = lIDTipoEsame;

			// DATA //
			if (!m_pEsamiSet->IsFieldDirty(&m_pEsamiSet->m_lData) || (m_pEsamiSet->m_lData == 0))
				m_pEsamiSet->m_lData = CCustomDate(TRUE, TRUE).GetDate();

			// PROGRESSIVOANNO //
			m_pEsamiSet->m_sProgressivoAnno = GetContatoreAnnuale(m_pEsamiSet->m_lIDEsame);

			//16052 Simone - versione checklist a griglia
			//	Alla creazione di un nuovo esame, setto la versione della griglia da utilizzare
			m_pEsamiSet->m_lVersioneGridCL = theApp.m_lLastGridCLVersion;

			// CODICEPRENOTAZIONE //
			m_pEsamiSet->m_sCodicePrenotazione = GetCodicePrenotazione(m_pEsamiSet->m_lIDEsame);

			// IDVERSIONE //
			m_pEsamiSet->m_lIDVersione = GetIDVersione(m_pEsamiSet->m_lIDEsame);

			// IDSEDEESAME //
			m_pEsamiSet->m_lIDSedeEsame = lIDSedeEsame;

			// SALAESAME //
			m_pEsamiSet->m_sSalaEsame = sSalaEsame;

			//INVIANTE
			m_pEsamiSet->m_lInviante = idInviante;

			// Sandro 05/06/2013 // RIMA 13070 //
			if (theApp.m_lOpzionalePazientiCronici == OPZIONALE_PAZIENTI_CRONICI)
				m_pEsamiSet->m_lIDMalattiaCronica = CTipoEsameSet().GetIDCronicita(m_pEsamiSet->m_lIDEsame);

			///BUG --> POPOLARE QUI I CAMPI PERSONALIZZABILI DA WL
			if (m_lIDPrenotazione > 0)
				UpdateDataFromWorklist();

			m_pEsamiSet->m_lMedico = lIDMedico1; //Julio Medico1

			// Sandro 20/12/2013 // RAS 20130172 //
			AMLogin_GetUserID(&m_pEsamiSet->m_lIDUtenteInserimentoEsame);

			//
			m_pEsamiSet->m_lNumEsame = m_pPazientiSet->m_lTotEsami + 1;
			if (m_pEsamiSet->UpdateRecordset("CEsamiView::EsameUpdate"))
			{
				m_pPazientiSet->m_lTotEsami++;
				bOK = TRUE;
			}
			else
			{
				m_pEsamiSet->RefreshRecordset();
			}
		}

		if (bOK)
		{
			m_pEsamiSet->RequeryRecordset();

			/* if (theApp.m_bPazientiUsaVista)
			{
			MoveEsamiRecordset(ID_RECORD_LAST);
			SaveForm();

			RicercaCodicePaziente(m_pPazientiSet->m_lContatore, 0, FALSE, TRUE);
			MovePazientiAndEsami(NULL, TRUE, TRUE);
			}
			else */
			{
				MoveEsamiRecordset(ID_RECORD_LAST);
				SaveForm();
			}

			// Sandro 11/09/2013 // se non c'è la form visibile copio "a mano" i farmaci per i pazienti cronici nel nuovo esame appena inserito //
			if (theApp.m_lOpzionalePazientiCronici == OPZIONALE_PAZIENTI_CRONICI)
				if (m_pDynForm[sub_pazienticronici_terapia] == NULL)
					CEsamiFarmaciCroniciSet().CloneAllRows(lIDEsameOld, m_pEsamiSet->m_lContatore);
		}

		theApp.m_nProgramMode = NOTHING_MODE;
		OnEsamiMove(NULL);

		// Sandro 05/06/2013 // RIMA 13070 //
		if (theApp.m_lOpzionalePazientiCronici == OPZIONALE_PAZIENTI_CRONICI)
		{
			long lIDCronicita = CTipoEsameSet().GetIDCronicita(m_pEsamiSet->m_lIDEsame);

			if (lIDCronicita > 0)
			{
				if (m_pPazientiSet->m_lIDMalattiaCronica == 0)
				{
					// il paziente non era ancora "cronico", chiedo conferma per farcelo diventare //

					CString sMessage;
					sMessage.Format(theApp.GetMessageString(IDS_CRONICITA_NUOVA), CMalattieCronicheSet().GetDescrizione(lIDCronicita));

					if (theApp.AfxMessageBoxEndo(sMessage, MB_YESNO | MB_ICONSTOP) == IDYES)
					{
						if (m_pPazientiSet->EditRecordset("CEsamiView::EsameUpdateClassic"))
						{
							m_pPazientiSet->m_lIDMalattiaCronica = lIDCronicita;

							m_pPazientiSet->UpdateRecordset("CEsamiView::EsameUpdateClassic");
						}
					}
				}
				else if (m_pPazientiSet->m_lIDMalattiaCronica != lIDCronicita)
				{
					// il paziente è stato associato ad una cronicità differente, chiedo se mantenere la sua precedente o passare alla nuova //

					CCronicitaCambiaDlg dlg(this, m_pPazientiSet->m_lIDMalattiaCronica, lIDCronicita);
					dlg.DoModal();

					if (m_pPazientiSet->m_lIDMalattiaCronica != dlg.GetResult())
					{
						if (m_pPazientiSet->EditRecordset("CEsamiView::EsameUpdateClassic"))
						{
							m_pPazientiSet->m_lIDMalattiaCronica = dlg.GetResult();

							m_pPazientiSet->UpdateRecordset("CEsamiView::EsameUpdateClassic");
						}
					}
				}
			}
		}
	}
	else
	{
		if (theApp.m_nProgramMode & MODIFY_RECORD_ESAMI)
		{
			//
			if (SaveEsami())
			{
				SaveForm();

				bOK = TRUE;
			}

			//
			if (bOK)
			{
				theApp.m_nProgramMode = NOTHING_MODE;

				CLockManager::Get()->UnlockExam(m_lLockedExam);

				// Sandro 31/01/2012 //
				OnEsamiMove(NULL, FALSE);
			}
		}
	}

	return bOK;
}

BOOL CEsamiView::EsameUpdateDefault()
{
	BOOL bOK = FALSE;

	UpdateData(TRUE);

	CEsamiSet ProfilesSet(TRUE);

	CString strFilter;
	strFilter.Format("IDESAME = %li", m_pEsamiSet->m_lIDEsame);
	ProfilesSet.SetOpenFilter(strFilter);
	if (ProfilesSet.OpenRecordset("CEsamiView::EsameUpdateDefault"))
	{
		if (ProfilesSet.IsEOF())
		{
			if (ProfilesSet.AddNewRecordset("CEsamiView::EsameUpdateDefault"))
			{
				ProfilesSet.CopyFieldFrom(m_pEsamiSet);
				ProfilesSet.SetFieldNull(&ProfilesSet.m_lContatore);

				ProfilesSet.UpdateRecordset("CEsamiView::EsameUpdateDefault");
			}
		}
		else
		{
			if (ProfilesSet.EditRecordset("CEsamiView::EsameUpdateDefault"))
			{
				long lContatore = ProfilesSet.m_lContatore;
				ProfilesSet.CopyFieldFrom(m_pEsamiSet);
				ProfilesSet.m_lContatore = lContatore;

				ProfilesSet.UpdateRecordset("CEsamiView::EsameUpdateDefault");
			}
		}

		ProfilesSet.CloseRecordset("CEsamiView::EsameUpdateDefault");
	}

	OnEsameRefresh();

	return bOK;
}

void CEsamiView::EvidenziaCampiObbligatoriFasi()
{
	int i;

	CString strFilter;
	//strFilter.Format("(IDTipoEsame=-1 OR IDTipoEsame=%li) AND (Provenienza=-1 OR Provenienza=%li)", m_pEsamiSet->m_lIDEsame, m_pEsamiSet->m_lProvenienza);
	//Andiamo a legare alla nuova provenienza
	strFilter.Format("(IDTipoEsame=-1 OR IDTipoEsame=%li) AND (IDPROVENIENZA=%li)", m_pEsamiSet->m_lIDEsame, m_pEsamiSet->m_lIdProvenienzaNew);

	CVistaCampiObbligatoriFasiNewSet setObbligatori;
	setObbligatori.SetOpenFilter(strFilter);

	for (i = 0; i < form_list_total; i++)
	{
		if (m_pDynForm[i] != NULL)
			m_pDynForm[i]->EvidenziaCampoObbligatorioEx(0);
	}

	//Simone 20/01/2016
	//	Prima di tutto verifico i campi sempre obbligatori
	//
	// 1. Nuova provenienza
	//
	if ((m_pDynForm[sub_inviante] != NULL))
	{
		m_pDynForm[sub_inviante]->EvidenziaCampoObbligatorioEx(CFasiEsameSet().GetColor(1));
	}


	if (setObbligatori.OpenRecordset("CEsamiView::EvidenziaCampiObbligatori"))
	{
		while (!setObbligatori.IsEOF())
		{
			for (i = 0; i < form_list_total; i++)
			{
				if ((m_pDynForm[i] != NULL) && (g_FormCaract[m_pDynForm[i]->GetContenuto()].lID == setObbligatori.m_lCampo))
				{
					COLORREF colorObbligatorio = CFasiEsameSet().GetColor(setObbligatori.m_lIDFaseNew);

					m_pDynForm[i]->EvidenziaCampoObbligatorioEx(colorObbligatorio);

					switch (setObbligatori.m_lCampo)
					{
					case SUB_OSSERVAZIONI:
					{
						if (m_pDynForm[btn_osservazioni] != NULL)
							m_pDynForm[btn_osservazioni]->EvidenziaCampoObbligatorioEx(colorObbligatorio);
						break;
					}
					case EDT_DIAGNOSTICHE:
					{
						if (m_pDynForm[btn_diagnostiche] != NULL)
							m_pDynForm[btn_diagnostiche]->EvidenziaCampoObbligatorioEx(colorObbligatorio);
						break;
					}
					case EDT_TERAPEUTICHE:
					{
						if (m_pDynForm[btn_terapeutiche] != NULL)
							m_pDynForm[btn_terapeutiche]->EvidenziaCampoObbligatorioEx(colorObbligatorio);
						break;
					}
					case SUB_DIAGNOSI:
					{
						if (m_pDynForm[btn_diagnosi] != NULL)
							m_pDynForm[btn_diagnosi]->EvidenziaCampoObbligatorioEx(colorObbligatorio);
						break;
					}
					case SUB_CODIFICADIAGNOSIESAME:
					{
						if (m_pDynForm[btn_codificadiagnosiesame] != NULL)
							m_pDynForm[btn_codificadiagnosiesame]->EvidenziaCampoObbligatorioEx(colorObbligatorio);
						break;
					}
					case SUB_CODIFICADIAGNOSIESAME5RIGHE:
					{
						if (m_pDynForm[btn_codificadiagnosiesame5righe] != NULL)
							m_pDynForm[btn_codificadiagnosiesame5righe]->EvidenziaCampoObbligatorioEx(colorObbligatorio);
						break;
					}
					case EDT_MST_COMPLICANZE1:
					{
						if (m_pDynForm[btn_complicanze1] != NULL)
							m_pDynForm[btn_complicanze1]->EvidenziaCampoObbligatorioEx(colorObbligatorio);
						break;
					}
					case EDT_MST_COMPLICANZE2:
					{
						if (m_pDynForm[btn_complicanze2] != NULL)
							m_pDynForm[btn_complicanze2]->EvidenziaCampoObbligatorioEx(colorObbligatorio);
						break;
					}
					case EDT_MST_COMPLICANZE3:
					{
						if (m_pDynForm[btn_complicanze3] != NULL)
							m_pDynForm[btn_complicanze3]->EvidenziaCampoObbligatorioEx(colorObbligatorio);
						break;
					}
					}

					break;
				}
			}
			setObbligatori.MoveNext();
		}
		setObbligatori.CloseRecordset("CEsamiView::EvidenziaCampiObbligatori");
	}
}

BOOL CEsamiView::VerificaCampiObbligatoriFase(long lIDFase)
{
	BOOL bError = FALSE;

	//Simone 20/01/2016
	//	Prima di tutto verifico i campi sempre obbligatori
	//
	// 1. Nuova provenienza, questa deve essere sempre compilata
	//
	if ((m_pDynForm[sub_inviante] != NULL))
	{
		if (!m_pDynForm[sub_inviante]->CampoObbligatorioValido())
		{
			CString strErrore;
			strErrore.Format("Campo %s obbligatorio per il completamento della fase %s", g_FormCaract[sub_inviante].sDescrizione, CFasiEsameSet().GetDescrizione(lIDFase));
			theApp.AfxMessageBoxEndo(strErrore);

			return FALSE;
		}
	}

	//Simone 08/06/2016
	//	La verifica dei campi obbligatori non è più legata alla chiusura. Commento il controllo sullo stampato
	//if (m_pEsamiSet->m_bStampato != TRUE) // Sandro // provo così perchè, quando nullo, m_bStampato è uguale a 2 //
	//{
	CString strFilter;
	//strFilter.Format("(IDTipoEsame=-1 OR IDTipoEsame=%li) AND (Provenienza=-1 OR Provenienza=%li) AND Fase=%li", m_pEsamiSet->m_lIDEsame, m_pEsamiSet->m_lProvenienza, lFase);
	//Andiamo a legare la query alla nuova provenienza
	strFilter.Format("(IDTipoEsame=-1 OR IDTipoEsame=%li) AND (IDPROVENIENZA=%li) and (IDFASENEW=%li)", m_pEsamiSet->m_lIDEsame, m_pEsamiSet->m_lIdProvenienzaNew, lIDFase);

	CVistaCampiObbligatoriFasiNewSet setObbligatori;
	setObbligatori.SetOpenFilter(strFilter);

	if (setObbligatori.OpenRecordset("CEsamiView::VerificaCampiObbligatoriFase"))
	{
		while (!setObbligatori.IsEOF())
		{
			BOOL bFound = FALSE;
			for (int i = 0; i < form_list_total; i++)
			{
				if ((m_pDynForm[i] != NULL) && (g_FormCaract[m_pDynForm[i]->GetContenuto()].lID == setObbligatori.m_lCampo))
				{
					bFound = TRUE;

					if (!m_pDynForm[i]->CampoObbligatorioValido())
						bError = TRUE;

					break;
				}
			}
			if (!bFound)
			{
				bError = FALSE;
				// bError = TRUE;
			}

			if (bError)
			{
				int z;
				for (z = 0; z < form_list_total; z++)
				{
					if (g_FormCaract[z].lID == setObbligatori.m_lCampo)
						break;
				}

				CString strErrore;
				strErrore.Format("Campo %s obbligatorio per il completamento della fase %s", g_FormCaract[z].sDescrizione, CFasiEsameSet().GetDescrizione(lIDFase));
				theApp.AfxMessageBoxEndo(strErrore);

				break;
			}

			setObbligatori.MoveNext();
		}
		setObbligatori.CloseRecordset("CEsamiView::VerificaCampiObbligatoriFase");
	}

	/*if (!bError)
	{
	if (m_pEsamiSet->GetEditMode() == 0 CRecordset::noMode)
	{
	if (m_pEsamiSet->EditRecordset("CEsamiView::VerificaCampiObbligatoriFase"))
	{
	m_pEsamiSet->m_bStampato = TRUE;
	m_pEsamiSet->UpdateRecordset("CEsamiView::VerificaCampiObbligatoriFase");
	}
	}
	else
	{
	m_pEsamiSet->m_bStampato = TRUE;
	}
	}*/
	//}

	return(!bError);
}

void CEsamiView::OnEsameUpdate()
{
	if (m_pDynForm[sub_inviante] != NULL)
	{
		if (!((CInvianteDynForm*)m_pDynForm[sub_inviante])->HasValue())
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PROVENIENZA_OBBLIGATORIA));
			return;
		}
	}

	//
	BOOL bUpdatePrenotazione = FALSE;
	if ((theApp.m_nProgramMode & ADD_RECORD_ESAMI) && (theApp.m_nInterfacciaPrenotazione != CEndoxApp::prenotazioni_none) && (m_lIDPrenotazione > 0) && !m_bValoriDefault)
		bUpdatePrenotazione = TRUE;

	// Sandro 04/04/2014 //
	BOOL bInsertPrenotazione = FALSE;
	if ((theApp.m_nProgramMode & ADD_RECORD_ESAMI) && !bUpdatePrenotazione && theApp.m_bInserisciPrenotazione && !m_bValoriDefault)
		bInsertPrenotazione = TRUE;

	long idEsame = -1;

	//
	if (theApp.m_nProgramMode & ADD_RECORD_ESAMI || theApp.m_nProgramMode & MODIFY_RECORD_ESAMI)
	{
		if (theApp.m_nProgramMode & ADD_RECORD_ESAMI)
		{
			if (m_bValoriDefault)
				EsameUpdateDefault();
			else
				EsameUpdateClassic();

			idEsame = m_pEsamiSet->GetLastAdd();
		}
		else
		{
			if (m_bValoriDefault)
				EsameUpdateDefault();
			else
				EsameUpdateClassic();

			idEsame = m_pEsamiSet->m_lContatore;
		}
	}
	UpdateData(FALSE);

	if (bUpdatePrenotazione)
	{
		CWorkListManager* pWorkListManager = CWorkListManager::Create(this);  // new
		pWorkListManager->UpdateWithExamID(m_lIDPrenotazione, m_pEsamiSet->m_lContatore);
		delete pWorkListManager;
	}
	m_lIDPrenotazione = -1;

	// Sandro //
	if (bInsertPrenotazione)
	{
		CExtOrdiniSet setTemp;
		setTemp.SetOpenFilter("ID=0");
		if (setTemp.OpenRecordset("CEsamiView::OnEsameUpdate"))
		{
			if (setTemp.AddNewRecordset("CEsamiView::OnEsameUpdate"))
			{
				setTemp.m_sOrderNumber.Format("ENDOX%08li", idEsame);

				m_pEsamiSet->EditRecordset("CEsamiView::OnEsameUpdate");
				m_pEsamiSet->m_sCodEsame = setTemp.m_sOrderNumber;
				m_pEsamiSet->UpdateRecordset("CEsamiView::OnEsameUpdate");

				setTemp.m_sDataEsame = CCustomDate(m_pEsamiSet->m_lData).GetDate("%Y%m%d%H%M");

				//Simone - RIMA 15157
				//	Devo utilizzare la nuova provenienza
				setTemp.m_sProvenienza = CProvenienzaSet().GetCodiceIntegrazione(m_pEsamiSet->m_lIdProvenienzaNew);

				if (!m_pEsamiSet->m_sSalaEsame.IsEmpty())
				{
					long lIDSala = CSaleEsameSet().GetIDSala(m_pEsamiSet->m_sSalaEsame);

					if (lIDSala > 0)
						setTemp.m_sCodiceAgenda = CAgendeSet().GetCodiceIntegrazioneFromIdSala(lIDSala);
				}
				if (setTemp.m_sCodiceAgenda.IsEmpty())
				{
					long lIDSala = CSaleEsameSet().GetIdSalaFromIdSede(theApp.m_lIDSedeEsameDefault);
					setTemp.m_sCodiceAgenda = CAgendeSet().GetCodiceIntegrazioneFromIdSala(lIDSala);
				}

				setTemp.m_sNote = m_pEsamiSet->m_sCodicePrenotazione;

				// setTemp.m_sCodiceRepartoInviante = ;

				// setTemp.m_sCodiceMedicoInviante = ;

				// setTemp.m_sMedicoInviante = ;

				// setTemp.m_sNosologico = ;

				setTemp.m_sUrgenza = "R";

				setTemp.m_lIDEsameIns = idEsame;

				setTemp.m_bTrasferito = TRUE;

				// setTemp.m_sIDProvetta = ;

				setTemp.m_bAcqSegnalata = FALSE;

				setTemp.m_bErogazioneSegnalata = FALSE;

				setTemp.m_bAppuntamentoSegnalato = FALSE;

				setTemp.m_bEliminato = FALSE;

				setTemp.m_sAssIden = m_pPazientiSet->m_sAssIden;

				setTemp.m_sCognome = m_pPazientiSet->m_sCognome;

				setTemp.m_sCognome2 = m_pPazientiSet->m_sCognome2;

				setTemp.m_sNome = m_pPazientiSet->m_sNome;

				setTemp.m_lDataNascitaCustom = m_pPazientiSet->m_lNatoIlCustom;

				setTemp.m_sDataNascita = CCustomDate(m_pPazientiSet->m_lNatoIlCustom).GetDate("%Y%m%d");

				setTemp.m_lIstatNascita = m_pPazientiSet->m_lIDComuneNascita;

				setTemp.m_sComuneNascita = m_pPazientiSet->m_sNatoA;

				setTemp.m_sIndirizzoResidenza = m_pPazientiSet->m_sVia;

				setTemp.m_lIstatResidenza = m_pPazientiSet->m_lIDComune;

				setTemp.m_sComuneResidenza = m_pPazientiSet->m_sCitta;

				setTemp.m_sCapResidenza = m_pPazientiSet->m_sCAP;

				setTemp.m_sTelefono1 = m_pPazientiSet->m_sTelefono1;

				setTemp.m_sTelefono2 = m_pPazientiSet->m_sTelefono2;

				setTemp.m_sCellulare1 = m_pPazientiSet->m_sCellulare1;

				setTemp.m_sCellulare2 = m_pPazientiSet->m_sCellulare2;

				setTemp.m_sCodiceFiscale = m_pPazientiSet->m_sCodFisc;

				setTemp.m_sCodiceSanitario = m_pPazientiSet->m_sCodSanit;

				setTemp.m_lSesso = m_pPazientiSet->m_lSessoPaz;

				// setTemp.m_lAsl = ;

				// setTemp.m_sCodiceMedicoCurante = ;

				// setTemp.m_sMedicoCurante = ;

				// setTemp.m_sCodiceCittadinanza = ;

				// setTemp.m_sCittadinanza = ;

				setTemp.m_sDataRichiesta = CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M00");

				// setTemp.m_sRepartoInviante = ;

				// setTemp.m_sProvincia = ;

				setTemp.m_lStatoAccettazione = LPC_STATO_INCORSO;

				setTemp.m_sUO = CUOSet().GetCodiceIntegrazione(theApp.m_lUO, FALSE);

				// setTemp.m_sIDEpisodioRicovero = ;

				// setTemp.m_sDataRicovero = ;

				setTemp.m_bCertificazioneMEF = FALSE;

				setTemp.m_bCertificazioneSISS = FALSE;

				// setTemp.m_sCodAlfa = ;

				// setTemp.m_sUlssResidenza = ;

				// setTemp.m_sQuesitoDiagnostico = ;

				//

				if (setTemp.UpdateRecordset("CEsamiView::OnEsameUpdate"))
				{
					/* Sandro & Simone // 03/07/2015 // commento perchè non serve, anzi...
					CExtPrestazioniSet setTeeemp;
					setTeeemp.SetOpenFilter("ID=0");
					if (setTeeemp.OpenRecordset("CEsamiView::OnEsameUpdate"))
					{
					if (setTeeemp.AddNewRecordset("CEsamiView::OnEsameUpdate"))
					{
					setTeeemp.m_lIDOrdine = setTemp.GetLastAdd();

					setTeeemp.m_sIDPrestazione = setTemp.m_sOrderNumber;

					// setTeeemp.m_sCodicePrestazione = ;

					setTeeemp.m_sDescrizionePrestazione = CTipoEsameSet().GetDescrizione(m_pEsamiSet->m_lIDEsame);

					// setTeeemp.m_sNote = ;

					setTeeemp.m_lQuantita = 1;

					setTeeemp.m_bEliminato = FALSE;

					setTeeemp.m_sDataRichiesta = setTemp.m_sDataRichiesta;

					// setTeeemp.m_sNumeroRicetta = ;

					setTeeemp.UpdateRecordset("CEsamiView::OnEsameUpdate");
					}

					setTeeemp.CloseRecordset("CEsamiView::OnEsameUpdate");
					}
					*/
				}
			}

			setTemp.CloseRecordset("CEsamiView::OnEsameUpdate");
		}
	}

	// Sandro 05/08/2016 // RIMA 16037.RN10 //
	UpdateModalityWorklistSCP();

	//
	m_bValoriDefault = FALSE;
}

BOOL CEsamiView::OnEsameUpdateCup()
{
	BOOL bReturn = EsameUpdateClassic();

	UpdateData(FALSE);

	m_lIDPrenotazione = -1;

	m_bValoriDefault = FALSE;

	return bReturn;
}

BOOL CEsamiView::EsameRefreshSoft()
{
	// Marvel BUG 4092 - concorrência na edição de laudos
	// REFRESH recordset of pazient + esami

	BOOL bResult = FALSE;

	CString sPrevDataOra = m_pEsamiSet->m_sRefertoDataOra;
	long lPrevRedatore = m_pEsamiSet->m_lRefertoRedattore;

	m_pEsamiSet->RefreshRecordset();
	m_pPazientiSet->RefreshRecordset();


	if (sPrevDataOra != m_pEsamiSet->m_sRefertoDataOra || lPrevRedatore != m_pEsamiSet->m_lRefertoRedattore)
	{
		bResult = TRUE;
	}

	FormatMsgGotRefertoRefreshWithUpdate(bResult);

	return bResult;
}

BOOL CEsamiView::EsameRefresh()
{
	BOOL bOK = FALSE;

	if (theApp.m_nProgramMode & ADD_RECORD_ESAMI || theApp.m_nProgramMode & MODIFY_RECORD_ESAMI || theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		/* metto il fuoco sul primo elemento per evitare strani comportamenti di CExtEdit
		int nCurSel = m_ctrlGruppoEsame.GetCurSel();
		if (nCurSel >= 0)
		{
		if (CBaseForm* pForm = m_ctrlGruppoEsame.GetSelectedBaseForm())
		{
		TRACE("CEsamiView::EsameRefresh -> SetFocusOnFirst prima\n");
		pForm->SetFocusOnFirst();
		TRACE("CEsamiView::EsameRefresh -> SetFocusOnFirst dopo\n");
		}
		}
		*/

		if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
		{
			m_pPazientiSet->RefreshRecordset();

			//MovePazientiAndEsami(NULL, FALSE, TRUE);

			theApp.m_nProgramMode &= ~FILTER_RECORD_PAZIENTI;
		}

		theApp.m_nProgramMode &= ~ADD_RECORD_ESAMI;
		theApp.m_nProgramMode &= ~MODIFY_RECORD_ESAMI;
		theApp.m_nProgramMode &= ~FILTER_RECORD_ESAMI;

		m_pEsamiSet->RefreshRecordset();

		OnEsamiMove(NULL);

		bOK = TRUE;
	}

	m_lIDPrenotazione = -1;
	return bOK;
}

void CEsamiView::OnEsameRefresh()
{
	if (m_bValoriDefault)
	{
		EsameRefresh();
		CLockManager::Get()->UnlockExam(m_lLockedExam);

		m_bValoriDefault = FALSE;
	}
	else
	{
		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ANNULLA_MODIFICHE), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			EsameRefresh();
			CLockManager::Get()->UnlockExam(m_lLockedExam);
		}
	}
}

void CEsamiView::OnEsameQuery()
{
	OnDestroyQueryWnd(NULL, NULL);

	if (theApp.m_nProgramMode == NOTHING_MODE || theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI)
	{
		CaricaInterfaccia(1);

		if (!(theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI))
			AnnullaCampiPaziente();

		AnnullaCampiEsame();

		theApp.m_nProgramMode |= FILTER_RECORD_ESAMI;

		m_pEsamiSet->m_lIDSedeEsame = theApp.m_lIDSedeEsameDefault;
		m_pEsamiSet->m_sSalaEsame = theApp.m_sSalaEsameDefault;

		UpdateData(FALSE);

		/* metto il fuoco sul primo elemento
		int nCurSel = m_ctrlGruppoEsame.GetCurSel();
		if (nCurSel >= 0)
		{
		if (CBaseForm* pForm = m_ctrlGruppoEsame.GetSelectedBaseForm())
		{
		TRACE("CEsamiView::OnEsameQuery -> SetFocusOnFirst prima\n");
		SetFocus();
		pForm->SetFocusOnFirst();
		TRACE("CEsamiView::OnEsameQuery -> SetFocusOnFirst dopo\n");
		}
		}
		*/
	}
}

int CEsamiView::TrasferimentoImmagini(BOOL bVerbose)
{
	int nResult = ERROR_NOTHING;

	if (!m_bPazientiBusy && !m_bEsamiBusy)
	{
		BeginWaitCursor();

		// imposto gli ID all'image manager //
		m_pImgManager->SetCurrentIDs(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);

		// chiedo eventuale conferma per procedere //
		if (bVerbose)
			if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_BASEFORM_CONFIRM_TRANSFER), MB_YESNO) == IDNO)
				return ERROR_NOTHING;

		// controllo che l'esame non sia già stato trasferito //
		CString strLabel;
		if (m_pImgManager->IsExamConfirmed(strLabel))
		{
			if (bVerbose)
			{
				CString strError;
				strError.Format(theApp.GetMessageString(IDS_BASEFORM_JUST_TRANSFER), strLabel);
				theApp.AfxMessageBoxEndo(strError);
			}

			return ERROR_NOTHING;
		}

		// controllo che l'esame abbia immagini //
		CImgIDList listImageID;
		m_pImgManager->GetImgIDList(&listImageID);
		if (listImageID.GetCount() == 0)
		{
			if (bVerbose)
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_BASEFORM_NO_IMAGE));

			return ERROR_NOTHING;
		}

		// verifico che il disco per il backup sia inserito ed eventualmente lo faccio inserire //
		strLabel = GetVolumeName();
		while (strLabel.IsEmpty())
		{
			CEspelliDlg	dlg(this, "");

			if (dlg.DoModal() == IDCANCEL)
				return ERROR_CRASH_DISK;  // non é stata trovata l'etichetta del volume o errore disco //

			strLabel = GetVolumeName();
		}

		// creo PAT_EXAM e CExamIDList e li la valorizzo //
		PAT_EXAM structPatExam;
		m_pImgManager->GetCurrentIDs(structPatExam.lPatientID, structPatExam.lExamID);
		CExamIDList listExamID;
		listExamID.AddHead(structPatExam);

		// calcolo lo spazio disponibile e quello necessario //
		double fDiskAvaible = 0;
		double fSpaceRequired = 0;
		CalcSpaces(m_pImgManager, &listExamID, &fDiskAvaible, &fSpaceRequired);

		// verifico se lo spazio è sufficiente per l'esame //
		if (fSpaceRequired > fDiskAvaible)
		{
			CString strMessage;
			strMessage.Format("SPAZIO NECESSARIO: %li Kbyte\nSPAZIO DISPONIBILE: %li Kbyte\n\nSpazio non sufficiente per archiviare ulteriori esami. Cambiare disco.", (DWORD)(fSpaceRequired / 1024.0f), (DWORD)(fDiskAvaible / 1024.0f));
			theApp.AfxMessageBoxEndo(strMessage);

			nResult = ERROR_FULL_DISK; // disco pieno //
		}

		// copio i files dell'esame poi li imposto come trasferiti e poi come confermati //
		if (nResult == ERROR_NOTHING)
		{
			if (m_pImgManager->CopyExamsImage(&listExamID, theApp.m_sPathImageOD, NULL, NULL, NULL))
			{
				if (m_pImgManager->SetImageTransferred(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, &listExamID, strLabel))
					if (m_pImgManager->SetImageConfirm(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, &listExamID)) // <-- le cancella lui le immagini da HD //
						nResult = listImageID.GetCount(); // tutto OK! //
			}
		}

		EndWaitCursor();
	}
	else
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAMIVIEW_BUSY));
	}

	return nResult;
}

void CEsamiView::OnPrenotazione()
{
	CString strParam;
	strParam.Format("?endox=true&cognome=%s&nome=%s&codfisc=%s", m_pPazientiSet->m_sCognome, m_pPazientiSet->m_sNome, m_pPazientiSet->m_sCodFisc);

	WORD res;

	if (!theApp.m_sAgendaIndex.IsEmpty())
	{
		BeginWaitCursor();
		res = WinExec(theApp.m_sAgendaIndex + strParam, SW_SHOW);
		EndWaitCursor();

		if (res < 32)
		{
			if (res == 0)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAMIVEW_ERR_EXEC_1));
				return;
			}
			if (res == ERROR_BAD_FORMAT)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAMIVEW_ERR_EXEC_2));
				return;
			}
			if (res == ERROR_FILE_NOT_FOUND)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAMIVEW_ERR_EXEC_3));
				return;
			}
			if (res == ERROR_PATH_NOT_FOUND)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAMIVEW_ERR_EXEC_4));
				return;
			}
		}
	}
}

void CEsamiView::OnAlbum()
{
	if (theApp.m_bPersonalizzazioniBrasileSirio)
	{
		CGestioneEsamiPendentiDlg(this, this).DoModal();
	}
	else
	{
		if (theApp.m_bStoricoImago)
		{
			// 11/07/2011 - Il pulsante viene modificato dandogli la funzionalità di apertura dell'album del paziente
			CAlbumEsameDlg(this, this, TRUE).DoModal();
		}
		else
		{
			CMosaicDlg(this, this).DoModal();
		}
	}
}

void CEsamiView::OnAlbumConfronto()
{
	if (theApp.m_nApplication == PRG_DERMOX)
	{
		CAlbumConfrontoDermoxDlg dlg(this, this, CPoint(-1, -1));
		dlg.DoModal();
	}
	else
	{
		CAlbumConfrontoDlg dlg(this, this);
		dlg.DoModal();
	}
}

void CEsamiView::OnDraw(CDC* pDC)
{
	static BOOL bFirstShow = TRUE;

	if (bFirstShow)
	{
		if (::IsWindow(GetSafeHwnd()))
		{
			bFirstShow = FALSE;

			if (theApp.m_pAccessWnd)
			{
				theApp.m_pAccessWnd->DestroyWindow();
				delete theApp.m_pAccessWnd;
				theApp.m_pAccessWnd = NULL;
			}
		}
	}
}

void CEsamiView::SetReadOnly(BOOL bReadOnly)
{
	if (bReadOnly != m_bReadOnly)
		m_bReadOnly = bReadOnly;

	if (m_pFormImmagini != NULL)
		m_pFormImmagini->SendMessage(MSG_FORM_READONLY, (WPARAM)bReadOnly);

	for (int i = 0; i < form_list_total; i++)
		if (m_pDynForm[i] != NULL)
			m_pDynForm[i]->SendMessage(MSG_FORM_READONLY, (WPARAM)bReadOnly);
}


void CEsamiView::FormatMsgGotRefertoRefreshWithUpdate(BOOL p_bFillMessage) {
	// Marvel BUG 4092 - concorrência na edição de laudos
	// se encontrado uma versão mais atual (alerta usuário que a versão mais recente foi recuperada)

	m_sMsgGotRefertoRefreshWithUpdate = "";

	if (!p_bFillMessage) {
		return;
	}

	CString sPrevDataOra = m_pEsamiSet->m_sRefertoDataOra;
	long lPrevRedatore = m_pEsamiSet->m_lRefertoRedattore;

	BOOL bIsMedici = true;
	CString strPrevRedatore = CMediciSet().GetCognomeNomeFromUserID(lPrevRedatore);
	if (strPrevRedatore.IsEmpty())
	{
		bIsMedici = false;
		strPrevRedatore = CUtentiSet().GetUsername(lPrevRedatore);
		if (strPrevRedatore.IsEmpty()) {
			strPrevRedatore.Format("id = '%d'", lPrevRedatore);
		}
	}

	CTime auxDt(atoi(sPrevDataOra.Left(4)),
		atoi(sPrevDataOra.Mid(4, 2)),
		atoi(sPrevDataOra.Mid(6, 2)),
		atoi(sPrevDataOra.Mid(8, 2)),
		atoi(sPrevDataOra.Mid(10, 2)),
		atoi(sPrevDataOra.Mid(12, 2)));

	CString strPrevDataOra = auxDt.Format("%d/%m/%Y %H:%M:%S");

	m_sMsgGotRefertoRefreshWithUpdate.Format(
		"Recuperada última atualização deste laudo:\nredigido por : %s '%s'\ndata / hora : %sh",
		(bIsMedici ? "médico(a)" : "usuário(a)"),
		strPrevRedatore,
		strPrevDataOra);
}

void CEsamiView::OnEsameReferto()
{
	BOOL bEsameAdding = theApp.m_nProgramMode & ADD_RECORD_ESAMI;
	if (!bEsameAdding)
		if ((m_pEsamiSet->IsBOF()) && (m_pEsamiSet->IsEOF()))  // TODO: && parece estranho
			return;

	if (theApp.m_bPersonalizzazioniBrasileFleury)
	{
		CString sMessaggio = "";
		BOOL bModifica = FleuryPossoModificare(sMessaggio, m_pEsamiSet->m_sRicovero, m_pEsamiSet->m_sCodEsame);
		if (!bModifica)
		{
			theApp.AfxMessageBoxEndo(sMessaggio);
			return;
		}

		//mitigaçao de vulnerabilidade do TesiLock
		bModifica = FALSE;
		CString sFilter;
		sFilter.Format("Contatore=%li", m_pEsamiSet->m_lContatore);
		CEsamiSet setEsame;
		setEsame.SetOpenFilter(sFilter);
		if (setEsame.OpenRecordset(""))
		{
			if (!setEsame.IsEOF())
				bModifica = !(setEsame.m_bSuperLocked || setEsame.m_bNonSbloccabile);
			setEsame.CloseRecordset("");
		}
		if (!bModifica)
		{
			theApp.AfxMessageBoxEndo(IDS_BASEFORM_REPORT_MOD1);
			return;
		}
		//
	}
	// Sandro 20/11/2013 // RAS 20130187 //
	BOOL bContinue = TRUE;
	if (theApp.m_bRefertazioneLogoutAuto)
		bContinue = Logout(FALSE);

	if (bContinue)
	{
		if (m_pEsamiSet->IsRefertoUpdatable())
		{
			// ANTES DE PERMITIR A EDIÇÃO... PEGA A ULTIMA ATUALIZAÇÃO (SE HOUVER)
			BOOL bHasCHanged = EsameRefreshSoft();	// Marvel BUG 4092 - concorrência na edição de laudos

			// m_lLockedPatient = m_pEsamiSet->m_lPaziente;
			m_lLockedExam = m_pEsamiSet->m_lContatore;
			if (CLockManager::Get()->LockExam(m_lLockedExam))
			{
				/* Sandro 29/09/2016 // RIMA 16037 Fleury //

				if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury)
				{

				}

				*/

				CRefertoExDlg dlg(this, this);
				dlg.DoModal();

				if (m_pDynForm[sub_anatomiapatologica] != NULL)
					m_pDynForm[sub_anatomiapatologica]->UpdateData(FALSE); // SendMessage(MSG_FORM_LOAD);
				if (m_pDynForm[sub_anatomiapatologicaprest] != NULL)
					m_pDynForm[sub_anatomiapatologicaprest]->UpdateData(FALSE); // SendMessage(MSG_FORM_LOAD);

				CLockManager::Get()->UnlockExam(m_lLockedExam);
			}
		}
		else
		{
			CString sRedattore = CMediciSet().GetCognomeNomeFromUserID(m_pEsamiSet->m_lRefertoRedattore);
			if (sRedattore.IsEmpty())
			{
				theApp.AfxMessageBoxEndo(IDS_BASEFORM_REPORT_MOD1);
			}
			else
			{
				sRedattore.MakeUpper();

				CString sMsg;
				sMsg.Format(theApp.GetMessageString(IDS_BASEFORM_REPORT_MOD2), sRedattore);
				theApp.AfxMessageBoxEndo(sMsg);
			}
		}
	}
}

void CEsamiView::OnEsameRefertoGenomica()
{
	BOOL bEsameAdding = theApp.m_nProgramMode & ADD_RECORD_ESAMI;
	if (!bEsameAdding)
		if ((m_pEsamiSet->IsBOF()) && (m_pEsamiSet->IsEOF()))
			return;

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
	// Sandro 20/11/2013 // RAS 20130187 //
	BOOL bContinue = TRUE;
	if (theApp.m_bRefertazioneLogoutAuto)
		bContinue = Logout(FALSE);

	if (bContinue)
	{
		if (m_pEsamiSet->IsRefertoUpdatable())
		{
			// ANTES DE PERMITIR A EDIÇÃO... PEGA A ULTIMA ATUALIZAÇÃO (SE HOUVER)
			BOOL bHasCHanged = EsameRefreshSoft();	// Marvel BUG 4092 - concorrência na edição de laudos

			m_lLockedExam = m_pEsamiSet->m_lContatore;
			if (CLockManager::Get()->LockExam(m_lLockedExam))
			{
				CGenomicaRefertoDlg dlg(this, this);
				dlg.DoModal();

				if (m_pDynForm[sub_anatomiapatologica] != NULL)
					m_pDynForm[sub_anatomiapatologica]->UpdateData(FALSE); // SendMessage(MSG_FORM_LOAD);
				if (m_pDynForm[sub_anatomiapatologicaprest] != NULL)
					m_pDynForm[sub_anatomiapatologicaprest]->UpdateData(FALSE); // SendMessage(MSG_FORM_LOAD);

				CLockManager::Get()->UnlockExam(m_lLockedExam);
			}
		}
		else
		{
			CString sRedattore = CMediciSet().GetCognomeNomeFromUserID(m_pEsamiSet->m_lRefertoRedattore);
			if (sRedattore.IsEmpty())
			{
				theApp.AfxMessageBoxEndo(IDS_BASEFORM_REPORT_MOD1);
			}
			else
			{
				sRedattore.MakeUpper();

				CString sMsg;
				sMsg.Format(theApp.GetMessageString(IDS_BASEFORM_REPORT_MOD2), sRedattore);
				theApp.AfxMessageBoxEndo(sMsg);
			}
		}
	}
}

void CEsamiView::OnClickIconAllergie()
{
	if (theApp.m_bMenuUsaCarestreamExamesPendentes)
		OnCommandMenuGestioneEsamiPendenti();

	else
	{
		CString strSegnalato = "";
		CString strCL = "";

		CString strTestiCL[NUM_LABEL_TESTO_CL];
		strTestiCL[0] = m_pEsamiSet->m_setEP.m_sTestoCLTxt000.Trim().MakeUpper();
		strTestiCL[1] = m_pEsamiSet->m_setEP.m_sTestoCLTxt001.Trim().MakeUpper();
		strTestiCL[2] = m_pEsamiSet->m_setEP.m_sTestoCLTxt002.Trim().MakeUpper();
		strTestiCL[3] = m_pEsamiSet->m_setEP.m_sTestoCLTxt003.Trim().MakeUpper();
		strTestiCL[4] = m_pEsamiSet->m_setEP.m_sTestoCLTxt004.Trim().MakeUpper();
		strTestiCL[5] = m_pEsamiSet->m_setEP.m_sTestoCLTxt005.Trim().MakeUpper();
		strTestiCL[6] = m_pEsamiSet->m_setEP.m_sTestoCLTxt006.Trim().MakeUpper();
		strTestiCL[7] = m_pEsamiSet->m_setEP.m_sTestoCLTxt007.Trim().MakeUpper();
		strTestiCL[8] = m_pEsamiSet->m_setEP.m_sTestoCLTxt008.Trim().MakeUpper();
		strTestiCL[9] = m_pEsamiSet->m_setEP.m_sTestoCLTxt009.Trim().MakeUpper();
		strTestiCL[10] = m_pEsamiSet->m_setEP.m_sTestoCLTxt010.Trim().MakeUpper();
		strTestiCL[11] = m_pEsamiSet->m_setEP.m_sTestoCLTxt011.Trim().MakeUpper();
		strTestiCL[12] = m_pEsamiSet->m_setEP.m_sTestoCLTxt012.Trim().MakeUpper();
		strTestiCL[13] = m_pEsamiSet->m_setEP.m_sTestoCLTxt013.Trim().MakeUpper();
		strTestiCL[14] = m_pEsamiSet->m_setEP.m_sTestoCLTxt014.Trim().MakeUpper();
		strTestiCL[15] = m_pEsamiSet->m_setEP.m_sTestoCLTxt015.Trim().MakeUpper();
		strTestiCL[16] = m_pEsamiSet->m_setEP.m_sTestoCLTxt016.Trim().MakeUpper();
		strTestiCL[17] = m_pEsamiSet->m_setEP.m_sTestoCLTxt017.Trim().MakeUpper();
		strTestiCL[18] = m_pEsamiSet->m_setEP.m_sTestoCLTxt018.Trim().MakeUpper();
		strTestiCL[19] = m_pEsamiSet->m_setEP.m_sTestoCLTxt019.Trim().MakeUpper();

		for (int i = 0; i < NUM_LABEL_TESTO_CL; i++)
		{
			CStringList paroleChiaveList;
			CString paroleChiave = theApp.m_sParoleChiaveCL[i].MakeUpper();

			int nTokenPos = 0;
			CString strToken = paroleChiave.Tokenize(";", nTokenPos);


			while (!strToken.IsEmpty())
			{
				paroleChiaveList.AddTail(strToken);
				strToken = paroleChiave.Tokenize(";", nTokenPos);
			}

			CString temp = theApp.m_sLabelTextCL[i];

			//Se c'è scritto qualcosa nella checklist
			if (theApp.m_bAlarmCL[i] && strTestiCL[i].GetLength() > 0)
			{
				//Controllo se quello che c'è scritto è una parola chiave, in quel caso non mostro l'alert
				for (POSITION pos = paroleChiaveList.GetHeadPosition(); pos;)
				{
					CString strParola = paroleChiaveList.GetNext(pos);
					if (strTestiCL[i] == strParola)
					{
						temp = "";
						break;
					}

				}

				if (!temp.IsEmpty())
					if (strCL.IsEmpty())
						strCL = temp;
					else
						strCL += ", " + temp;
			}
		}

		if (!strCL.IsEmpty())
			strSegnalato += theApp.GetMessageString(IDS_ESAMIVIEW_CLCOMPILATE) + strCL + "\n\n";

		if (m_pEsamiSet != NULL && m_pEsamiSet->m_iAllergie > 0)
			strSegnalato += theApp.GetMessageString(IDS_ESAMIVIEW_MSG_15) + "\n" + m_pEsamiSet->m_sDescrizioneAllergie;

		theApp.AfxMessageBoxEndo(strSegnalato); // ATTENZIONE!\n\nIl paziente è allergico a //
	}
}

void CEsamiView::OnClickIconSegnalato()
{
	if (theApp.m_bMenuUsaCarestreamExamesPendentes)
	{
		OnBnClickedBtnViewPacs();
	}
	else
	{
		CString strSegnalato = theApp.GetMessageString(IDS_ESAMIVIEW_MSG_10) + "\n\n";

		if (m_pPazientiSet != NULL)
		{
			CString strTemp = "";

			if (!m_pPazientiSet->m_sDenSegnalato.IsEmpty())
				strTemp.Format("%s\n%s\n\n", theApp.GetMessageString(IDS_ESAMIVIEW_MSG_11), m_pPazientiSet->m_sDenSegnalato);

			strSegnalato += strTemp;
		}

		if ((m_pEsamiSet != NULL) && (!m_pEsamiSet->IsEOF()))
		{
			CString strTemp;

			strTemp = "";
			if (m_pEsamiSet->m_iPacemaker > 0)
				strTemp.Format("%s\n\n", theApp.GetMessageString(IDS_ESAMIVIEW_MSG_12));
			strSegnalato += strTemp;

			strTemp = "";
			if (m_pEsamiSet->m_iAnticoagulanti > 0)
				strTemp.Format("%s\n\n", theApp.GetMessageString(IDS_ESAMIVIEW_MSG_13));
			strSegnalato += strTemp;

			strTemp = "";
			if (m_pEsamiSet->m_iAntiaggreganti > 1)
				strTemp.Format("%s\n\n", theApp.GetMessageString(IDS_ESAMIVIEW_MSG_14));
			strSegnalato += strTemp;
		}

		theApp.AfxMessageBoxEndo(strSegnalato, MB_ICONSTOP);
	}
}

void CEsamiView::OnBtnConclusioni()
{
	CListaOsservazioniDlg dlg(this, this, m_pPazientiSet->m_lContatore, m_pPazientiSet->m_sCognome + " " + m_pPazientiSet->m_sNome, FALSE);
	dlg.DoModal();
}

void CEsamiView::OnBtnPazienteCronico()
{
	CCronicitaPazienteDlg dlg(this, this, m_pPazientiSet);
	dlg.DoModal();
}

void CEsamiView::OnBtnComando()
{
	WORD res;

	if (theApp.m_sEseguiComando.IsEmpty() == FALSE)
	{
		BeginWaitCursor();
		res = WinExec(theApp.m_sEseguiComando, SW_SHOW);
		EndWaitCursor();

		if (res < 32)
		{
			if (res == 0)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAMIVEW_ERR_EXEC_1));
				return;
			}
			if (res == ERROR_BAD_FORMAT)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAMIVEW_ERR_EXEC_2));
				return;
			}
			if (res == ERROR_FILE_NOT_FOUND)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAMIVEW_ERR_EXEC_3));
				return;
			}
			if (res == ERROR_PATH_NOT_FOUND)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAMIVEW_ERR_EXEC_4));
				return;
			}
		}
	}
}

void CEsamiView::OnListaPrenotazioni()
{
	//CListaPrenotazioniCupDlg dlg(this, this, 0, "1690149515");
	//dlg.DoModal();
	//return;
	switch (theApp.m_nInterfacciaPrenotazione)
	{
	case CEndoxApp::prenotazioni_cup:
	{
		CListaPrenotazioniCupDlg dlg(this, this, 0);
		dlg.DoModal();
		break;
	}
	case CEndoxApp::prenotazioni_cup_dicom:
	{
		CListaPrenotazioniCupDicomDlg dlg(this, this);
		dlg.DoModal();
		break;
	}
	case CEndoxApp::prenotazioni_DMS:
	{
		CListaPrenotazioniDMSDlg dlg(this, this);
		dlg.DoModal();
		break;
	}
	default:
	{
		CListaPrenotazioniDlg dlg(this, this);
		dlg.DoModal();
		break;
	}
	}
}

void CEsamiView::OnPazienteAllegati()
{
	CDocumentiDlg dlg(this, this, TRUE, FALSE, FALSE);
	dlg.DoModal();

	// Sandro 04/01/2014 // RAS 20130175 //
	m_lNumDocumentsPatient = m_pDocManager->GetAttachedDocNumberPatient(m_pPazientiSet->m_lContatore);
}

void CEsamiView::OnFleuryFicha()
{
	if (theApp.m_bFleuryProgrammaConsultaNuovo)
		FleuryApriConsulta2(m_pEsamiSet->m_sRicovero);
	else
		FleuryApriConsulta(m_pEsamiSet->m_sCodEsame);
}

void CEsamiView::OnFleuryFicha2()
{
	FleuryApriConsulta2(m_pEsamiSet->m_sRicovero);
}

void CEsamiView::OnFleuryAssessoria()
{
	FleuryAssessoriaMedica(m_pEsamiSet->m_sRicovero);
}

HBRUSH CEsamiView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hBrush = CResizableFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_LABEL_STATO:
	case IDC_LABEL_STATO_NEW1:
	case IDC_LABEL_STATO_NEW2:
	case IDC_LABEL_STATO_NEW3:
	case IDC_LABEL_STATO_NEW4:
	{
		pDC->SetTextColor(theApp.m_colorStato);

		pDC->SetBkColor(theApp.m_colorStatoSfondo);
		return m_brushSfondoStato;

		break;
	}
	case IDC_LABEL_STATO_MONITORAGGIO:
	case IDC_LABEL_MON_PAZIENTE:
	case IDC_LABEL_MON_DISPOSITIVO:
	{
		pDC->SetTextColor(RGB(255, 255, 255));	// WHITE

		pDC->SetBkColor(RGB(100, 100, 100));	// GRAY
		return m_brushSfondoStato;

		break;
	}
	case IDC_LABEL_PAZIENTE_01:
	case IDC_LABEL_PAZIENTE_02:
	case IDC_LABEL_PAZIENTE_03:
	case IDC_LABEL_PAZIENTE_04:
	case IDC_LABEL_PAZIENTE_05:
	case IDC_LABEL_PAZIENTE_06:
	case IDC_LABEL_PAZIENTE_07:
	case IDC_LABEL_PAZIENTE_08:
	case IDC_PAZIENTE_FISCALE:
	case IDC_PAZIENTE_SANITARIO:
	case IDC_PAZIENTE_COGNOME:
	case IDC_PAZIENTE_NOME:
	case IDC_PAZIENTE_SESSO:
	case IDC_PAZIENTE_TELEFONO:
	case IDC_PAZIENTE_NATOIL:
	case IDC_PAZIENTE_NATOA:
		// case IDC_EDIT_ASSIDEN:		// Sandro 31/10/2013 // RAS 20130161 //
		// case IDC_STATIC_PAZIENTE:	// Sandro 31/10/2013 // RAS 20130161 //
		// case IDC_STATIC_PAZIENTE_DECEDUTO:
	{
		if (m_pPazientiSet->m_bPazienteDelDirettore == TRUE || (theApp.m_bDisabilitaEsamiPazientiSenzaAssiden && (m_pPazientiSet->IsFieldNull(&m_pPazientiSet->m_sAssIden) || m_pPazientiSet->m_sAssIden == ""))) // confronto con TRUE perchè in inserimento/ricerca vale 2 //
			pDC->SetTextColor(theApp.m_color[0]);

		pDC->SetBkColor(theApp.m_colorPazienteSfondo);
		return m_brushSfondoPaziente;

		break;
	}
	}

	return hBrush;
}

void CEsamiView::OnBnClickedDatiPaziente()
{
	CString strFilter;
	strFilter.Format("Contatore=%li", m_pPazientiSet->m_lContatore);
	m_PazTempSet.SetOpenFilter(strFilter);
	if (m_PazTempSet.OpenRecordset("CEsamiView::OnBnClickedDatiPaziente"))
	{
		CPazientiDlg dlgPaz(this, this, &m_PazTempSet, PAZ_SHOW);
		dlgPaz.DoModal();
		m_PazTempSet.CloseRecordset("CEsamiView::OnBnClickedDatiPaziente");
	}
}

void CEsamiView::OnUpdateUI(CCmdUI* pCmdUI)
{
	if (pCmdUI == NULL)
		return;

	switch (pCmdUI->m_nID)
	{

		///////////////////
		// menù di endox //
		///////////////////

	case ID_FILE_LOGOUT:
	{
		pCmdUI->Enable(!m_bBurning && !m_bImporting && !m_bPrinting);
		break;
	}
	case ID_FILE_CHANGEPASSWORD:
	{
		pCmdUI->Enable(!m_bPrinting);
		break;
	}
	case ID_INFO_USER:
	{
#ifndef _DEBUG
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_03 ? TRUE : FALSE);
#endif
		break;
	}
	case ID_FILE_GESTIONEUTENTI:
	{
		pCmdUI->Enable(TRUE);// !m_bPrinting && (theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_01));
		break;
	}
	case ID_FILE_ASSOCIAZIONEUTENTIUNITAOPERATIVE:
	{
		pCmdUI->Enable(!m_bPrinting && (theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_01));
		break;
	}
	case ID_FILE_CAMBIOUO:
	{
		pCmdUI->Enable(!m_bBurning && !m_bImporting && !m_bEsamiBusy && !m_bPazientiBusy);
		break;
	}
	case ID_FILE_CAMBIOPASSWORDELIMINAZIONEPDF:
	{
		pCmdUI->Enable((theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_01));
		break;
	}
	case ID_FILE_STAMPAIMMAGINI:
	{
		pCmdUI->Enable(!m_bImporting && (theApp.m_dwPrivileges & AMLogin_Permissions::printout) && m_pEsamiSet->m_bStessoDistretto && m_bEsamiValid && !m_bEsamiBusy && !m_bPazientiBusy); // Sandro // 03/01/2011 //
		break;
	}
	case ID_FILE_ANTEPRIMAIMMAGINI:
	{
		pCmdUI->Enable(!m_bImporting && (theApp.m_dwPrivileges & AMLogin_Permissions::printout) && m_pEsamiSet->m_bStessoDistretto && m_bEsamiValid && !m_bEsamiBusy && !m_bPazientiBusy); // Sandro // 03/01/2011 //
		break;
	}
	case ID_FILE_STAMPAREPORT:
	{
		pCmdUI->Enable(!m_bImporting && (theApp.m_dwPrivileges & AMLogin_Permissions::printout) && m_pEsamiSet->m_bStessoDistretto && m_bEsamiValid && !m_bEsamiBusy && !m_bPazientiBusy); // Sandro // 03/01/2011 //
		break;
	}
	case ID_FILE_ANTEPRIMAREPORT:
	{
		pCmdUI->Enable(!m_bImporting && (theApp.m_dwPrivileges & AMLogin_Permissions::printout) && m_pEsamiSet->m_bStessoDistretto && m_bEsamiValid && !m_bEsamiBusy && !m_bPazientiBusy); // Sandro // 03/01/2011 //
		break;
	}
	case ID_FILE_STAMPAETICHETTE:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::printout);
		break;
	}
	case ID_FILE_INTESTAZIONEREFERTO:
	{
		pCmdUI->Enable(!m_bPrinting && (theApp.m_dwPrivileges & AMLogin_Permissions::configurations));
		break;
	}
	case ID_FILE_IMPOSTAPAGINA:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_FILE_SELTWAIN:
	{
		pCmdUI->Enable(theApp.m_bCanAcquire && m_bEsamiValid && !m_bEsamiBusy && !m_bPazientiBusy && (theApp.m_dwPrivileges & AMLogin_Permissions::modify_image));
		break;
	}
	case ID_FILE_INQUIERO_1:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_01);
		break;
	}
	case ID_FILE_INQUIERO_2:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_01);
		break;
	}
	case ID_APP_EXIT:
	{
		pCmdUI->Enable(!m_bBurning && !m_bImporting && !m_bPrinting);
		break;
	}

	//MENU Esame corrente
	/* case ID_FILE_ANNULLACONVALIDAESAMECORRENTE:
	{
	pCmdUI->Enable(((theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_01) || (theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_05)) && m_bEsamiValid && m_pEsamiSet->m_bStessoDistretto && m_pEsamiSet->m_bLocked); // && !m_pEsamiSet->m_bNonSbloccabile); // tengo menu attivo ma mostro messagebox quando lo clicco //
	break;
	} */
	/* case ID_FILE_ANNULLACHIUSURAESAMECORRENTE:
	{
	pCmdUI->Enable(((theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_01) || (theApp.m_listUserPhases.Find(CO_FASE_CHIUSURA_STAMPA) != NULL)) && m_bEsamiValid && m_pEsamiSet->m_bStessoDistretto && m_pEsamiSet->m_bSuperLocked); // && !m_pEsamiSet->m_bNonSbloccabile); // tengo menu attivo ma mostro messagebox quando lo clicco //
	break;
	} */
	case ID_FILE_SPOSTAESAME:
	{
		pCmdUI->Enable(!m_bImporting && (theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_01) && m_bEsamiValid && !m_bEsamiBusy && !m_bPazientiBusy);
		break;
	}
	case ID_ARCHIVI_IMPORTACASO:
	{
		// Sandro 13/01/2017 // richiesta telefonica e via mail di Paron Pilotto //
		// pCmdUI->Enable(!m_bImporting && (theApp.m_listUserPhases.Find(CO_FASE_CHIUSURA_STAMPA) != NULL) && m_bEsamiValid && !m_bEsamiBusy && !m_bPazientiBusy);
		pCmdUI->Enable(!m_bImporting && m_bEsamiValid && !m_bEsamiBusy && !m_bPazientiBusy);
		break;
	}
	case ID_ARCHIVI_ESAMEINTEGRATO:
	{
		pCmdUI->Enable(!m_bImporting && (theApp.m_listUserPhases.Find(CO_FASE_CHIUSURA_STAMPA) != NULL) && m_bEsamiValid && !m_bEsamiBusy && !m_bPazientiBusy);
		break;
	}
	case ID_ARCHIVI_STOREPACSIMAGE:
	{
		pCmdUI->Enable(!m_bImporting && (theApp.m_listUserPhases.Find(CO_FASE_CHIUSURA_STAMPA) != NULL) && m_bEsamiValid && !m_bEsamiBusy && !m_bPazientiBusy && m_pFormImmagini->GetSelectedCount() > 0);
		break;
	}

	case ID_GESTIONE_NOMENCLATORE:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_07 ? TRUE : FALSE);
		break;
	}
	case ID_GESTIONE_STATISTICHEESAMI:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_07 ? TRUE : FALSE);
		break;
	}
	case ID_GESTIONE_VISUALIZZASTAMPE:
	{
		break;
	}
	case ID_GESTIONE_SOSPESIISTOLOGICI:
	{
		pCmdUI->Enable(!theApp.m_bTerminalServer);
		break;
	}
	case ID_GESTIONE_VISUALIZZATORELOG:
	{
		break;
	}
	case ID_GESTIONE_LOGSINTETICO:
	{
		pCmdUI->Enable(m_bEsamiValid);
		break;
	}
	case ID_GESTIONE_VISUALIZZATORELOGIMPORTAZIONECASI:
	{
		pCmdUI->Enable(theApp.m_listUserPhases.Find(CO_FASE_CHIUSURA_STAMPA) != NULL ? TRUE : FALSE);
		break;
	}
	case ID_GESTIONE_ITENSFICHA:
	{
		pCmdUI->Enable((theApp.m_bPersonalizzazioniBrasileFleury && theApp.m_lRicercaCodiceEsame == RICERCA_PAZIENTE_FICHA) ? TRUE : FALSE);
		//pCmdUI->Enable(TRUE);			
		break;
	}
	case ID_GESTIONE_STATISTICHE:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_07 ? TRUE : FALSE);
		break;
	}
	case ID_GESTIONE_CONFIGSTATISTICHE:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_GESTIONE_ESAMIPENDENTI:
	{
		pCmdUI->Enable(!m_bImporting && !m_bEsamiBusy && !m_bPazientiBusy);
		break;
	}
	case ID_GESTIONE_SCREENING:
	{
		pCmdUI->Enable(!m_bImporting && !m_bEsamiBusy && !m_bPazientiBusy);
		break;
	}
	case ID_GESTIONE_LOGINTEGRAZIONI:
	{
		pCmdUI->Enable(!m_bImporting && !m_bEsamiBusy && !m_bPazientiBusy);
		break;
	}
	case ID_GESTIONE_INVIAVIDEO:
	{
		pCmdUI->Enable((theApp.m_listUserPhases.Find(CO_FASE_CHIUSURA_STAMPA) != NULL) && m_bEsamiValid && m_pEsamiSet->m_bStessoDistretto && m_pEsamiSet->m_bSuperLocked);
		break;
	}
	case ID_GESTIONE_PERSONIFICAR:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_10);
		break;
	}
	case ID_ESAMECORRENTE_DESCONJUGARITENS:
	{
		// Luiz - 07/05/2019 - P3 - Desconjuga exames - ESAMIINTEGRATI
		theApp.m_bPossuiConjugados = RefertoPrincipale(m_pEsamiSet->m_lContatore);
		pCmdUI->Enable((m_pEsamiSet->m_sRefertoConiugatoPrincipale.IsEmpty() && !theApp.m_bPossuiConjugados) ? FALSE : TRUE);
		break;
	}
	case ID_GESTIONE_ACCESSOSEDIESTERNE:
	{
		pCmdUI->Enable((theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_09) && !m_bBurning && !m_bImporting && !m_bPazientiBusy && !m_bEsamiBusy);
		break;
	}

	case ID_ARCHIVI_ORGANISEDI:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_CODIFICAREGIONALE:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_GRUPPIPRESTAZIONI:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_GRUPPIPRESTAZIONI_RICETTA:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_TIPIPRELIEVI:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_PROCEDUREPRELIEVI:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_GRUPPIPRELIEVI:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_VARI_DIAGNOSIISTOLOGICA:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_VARI_MEDIDASBIOMETRICAS:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	// Marvel Carvalho - BUG 4308 Esquemas Anatômicos Fleury
	case ID_VARI_SCHEMIANATOMICIRECORD:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	// Marvel Carvalho - BUG 4308 Esquemas Anatômicos Fleury
	case ID_VARI_SCHEMIANATOMICIADD:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	// Marvel Carvalho - BUG 4308 Esquemas Anatômicos Fleury
	case ID_VARI_SCHEMIANATOMICIEDIT:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_VARI_BOSTONSCORE:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_VARI_CODICIDICLASSIFICAZIONEDIAGNOSTICA:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_VARI_PROTOCOLLI:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_MALATTIECRONICHE:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_ESAMI:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ESAMI_FASI:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_FRASIRTF:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_FRASISTANDARD:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_FRASIPOSTESAME:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_MST_INDICAZIONI:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_MST_OSSERVAZIONI:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_MST_OSSERVAZIONI_1:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_MST_OSSERVAZIONI_2:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_MST_OSSERVAZIONI_3:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_MST_PROCDIAGNOSTICHE:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_MST_PROCTERAPEUTICHE:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_MST_DIAGNOSI:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_MST_CODDIAGNOSIESAME:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_MST_COMPLICANZE1:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_MST_COMPLICANZE2:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_MST_COMPLICANZE3:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_ALTRETABELLE:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_STRUMENTI:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_ETICHETTE_ANAMNESI:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_ETICHETTE:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_PRONTFARMACEUTICO:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_PRONTFARMACEUTICO_RICETTA:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_FARMACI_FARMACIPAZIENTICRONICI:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_CHECKLIST:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_ESENZIONERICETTA:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_PROCEDUREICD9:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_GRUPPIDIPROCEDUREICD9:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_GRUPPIDIDIAGNOSIICD9:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_ASSICD9:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_REPORTSDEFAULT:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_MACRODISTAMPA:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_MEDICI:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_INFERMIERI:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_INVIANTI_INT:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_INVIANTI_EXT:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_TRASFERIMPARZIALE:
	{
		pCmdUI->Enable(!m_bImporting && (theApp.m_dwPrivileges & AMLogin_Permissions::configurations));
		break;
	}
	case ID_ARCHIVI_TRASFERIMTOTALE:
	{
		pCmdUI->Enable(!m_bImporting && (theApp.m_dwPrivileges & AMLogin_Permissions::configurations));
		break;
	}
	case ID_ARCHIVI_ESPELLI_OD:
	{
		pCmdUI->Enable(!m_bImporting && (theApp.m_dwPrivileges & AMLogin_Permissions::configurations));
		break;
	}
	case ID_ARCHIVI_OCCUPAZIONEGIORNALIERA:
	{
		pCmdUI->Enable(!m_bImporting && (theApp.m_dwPrivileges & AMLogin_Permissions::configurations));
		break;
	}
	case ID_ARCHIVI_BACKUPDATI:
	{
		pCmdUI->Enable(!m_bBurning && !m_bImporting && !m_bRimage && (theApp.m_dwPrivileges & AMLogin_Permissions::configurations));
		break;
	}
	case ID_ARCHIVI_MEDICICURANTI:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_MEDICIINVIANTI:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_SALVAVALORIDEFAULT:
	{
		pCmdUI->Enable(!m_bImporting && (theApp.m_dwPrivileges & AMLogin_Permissions::configurations) && !m_bPazientiIsNull && !m_bEsamiBusy && !m_bPazientiBusy && (theApp.m_dwPrivileges & AMLogin_Permissions::add_exam));
		break;
	}
	case ID_ARCHIVI_PARAMETRITABELLAECOCARDIOGRAFIA:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_ARCHIVI_COMMENTIIMMAGINI:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}

	case ID_OPZIONI_INTEGRAZIONI:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}

	case ID_ROUTING_AUDIO:
	{
		pCmdUI->Enable(theApp.m_bCanAcquire);
		break;
	}
	case ID_ROUTING_VIDEO:
	{
		pCmdUI->Enable(theApp.m_bCanAcquire);
		break;
	}
	case ID_STREAMING_ATTIVAZIONEUTENTI:
	{
		pCmdUI->Enable(theApp.m_bCanAcquire);
		break;
	}
	case ID_CONNESSIONEREMOTA:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_06);
		break;
	}

	case ID_OPTION_ORGAN:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_OPTION_CALIB:
	{
		break;
	}
	case ID_OPTION_SETUP:
	{
		pCmdUI->Enable(!m_bImporting && !m_bPrinting && (theApp.m_dwPrivileges & AMLogin_Permissions::configurations));
		break;
	}
	case ID_OPTION_PATHS:
	{
		pCmdUI->Enable(!m_bImporting && !m_bPrinting && (theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_01));
		break;
	}
	case ID_OPTION_ACQ:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_01);
		break;
	}
	case ID_OPTION_WEB:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_01);
		break;
	}
	case ID_SETUP_DBASE:
	{
		pCmdUI->Enable(!m_bImporting && !m_bPrinting && (theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_01));
		break;
	}
	case ID_OPTION_OPERATOR:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_OPTION_REPORT:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_OPTION_CAMPIOBBLIGATORI:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::configurations);
		break;
	}
	case ID_OPZIONI_DISATTIVAFIRMAPERQUESTOESAME:
	{
		pCmdUI->Enable(m_bEsamiValid && (!m_pEsamiSet->m_bSuperLocked) && (!theApp.m_bEsameFirmatoDigitalmenteAlmenoUnaVolta));
		break;
	}
	case ID_OPZIONI_SETUPDATABASESREMOTI:
	{
		pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_01);
		break;
	}
	case ID_HELP:
	{
		break;
	}
	case ID_APP_ABOUT:
	{
		break;
	}
	case ID_OPZIONI_SETUPCOLORI:
	{
		pCmdUI->Enable(TRUE);
		break;
	}

	///////////////////////////////
	// toolbar paziente di endox //
	///////////////////////////////

	case IDC_PAZIENTE_FIRST:
	{
		pCmdUI->Enable(!m_bImporting && m_bPazientiPrev && !m_bPazientiBusy && !m_bEsamiBusy && !theApp.m_bDisattivaFrecceSpostamentoPazienti && !theApp.m_bMenuUsaTextboxBuscaExame);
		break;
	}
	case IDC_PAZIENTE_PREV:
	{
		pCmdUI->Enable(!m_bImporting && m_bPazientiPrev && !m_bPazientiBusy && !m_bEsamiBusy && !theApp.m_bDisattivaFrecceSpostamentoPazienti && !theApp.m_bMenuUsaTextboxBuscaExame);
		break;
	}
	case IDC_PAZIENTE_GOTO:
	{
		pCmdUI->Enable(!m_bImporting && (m_bPazientiPrev || m_bPazientiNext) && !m_bPazientiBusy && !m_bEsamiBusy && !theApp.m_bMenuUsaTextboxBuscaExame);
		break;
	}
	case IDC_PAZIENTE_GOTO_TRENTO:
	{
		pCmdUI->Enable(!m_bImporting && (m_bPazientiPrev || m_bPazientiNext) && !m_bPazientiBusy && !m_bEsamiBusy);
		break;
	}
	case IDC_PAZIENTE_NEXT:
	{
		pCmdUI->Enable(!m_bImporting && m_bPazientiNext && !m_bPazientiBusy && !m_bEsamiBusy && !theApp.m_bDisattivaFrecceSpostamentoPazienti && !theApp.m_bMenuUsaTextboxBuscaExame);
		break;
	}
	case IDC_PAZIENTE_LAST:
	{
		pCmdUI->Enable(!m_bImporting && m_bPazientiNext && !m_bPazientiBusy && !m_bEsamiBusy && !theApp.m_bDisattivaFrecceSpostamentoPazienti && !theApp.m_bMenuUsaTextboxBuscaExame);
		break;
	}

	case IDC_DATI_PAZIENTE:
	{
		pCmdUI->Enable(m_bPazientiValid && !m_bPazientiBusy && !m_bEsamiBusy);
		break;
	}

	case IDC_PAZIENTE_NEW:
	{
		pCmdUI->Enable(!m_bImporting && !m_bPazientiBusy && !m_bEsamiBusy && theApp.m_dwPrivileges & AMLogin_Permissions::add_patient);
		break;
	}
	case IDC_PAZIENTE_MODIFY:
	{
		pCmdUI->Enable(m_bPazientiValid && !m_bPazientiBusy && !m_bEsamiBusy && theApp.m_dwPrivileges & AMLogin_Permissions::modify_patient);
		break;
	}
	case IDC_PAZIENTE_DEL:
	{
		pCmdUI->Enable(!m_bImporting && m_bPazientiValid && !m_bPazientiBusy && !m_bEsamiBusy && theApp.m_dwPrivileges & AMLogin_Permissions::delete_patient);
		break;
	}

	case IDC_PAZIENTE_QUERY_DEF:
	{
		pCmdUI->Enable(!m_bImporting && (theApp.m_nProgramMode == NOTHING_MODE) || (theApp.m_nProgramMode & FILTER_RECORD_ESAMI) || (theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI));
		break;
	}
	case IDC_PAZIENTE_QUERY_APP:
	{
		pCmdUI->Enable(!m_bImporting && (theApp.m_nProgramMode != ADD_RECORD_PAZIENTI) && (theApp.m_nProgramMode != ADD_RECORD_ESAMI) && (theApp.m_nProgramMode != MODIFY_RECORD_PAZIENTI) && (theApp.m_nProgramMode != MODIFY_RECORD_ESAMI) && ((m_bFilterBusy) || (m_pQueryDlg != NULL)));
		break;
	}
	case IDC_PAZIENTE_UNDO:
	{
		pCmdUI->Enable(!m_bImporting && (theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI));
		break;
	}

	case IDC_ICON_ALLERGIE:
	{
		if (!theApp.m_bMenuUsaCarestreamExamesPendentes) //ICON_ALLERGIE -> ICON_EXAMESPENDENTES
		{

			CString strTestiCL[NUM_LABEL_TESTO_CL];
			strTestiCL[0] = m_pEsamiSet->m_setEP.m_sTestoCLTxt000.Trim().MakeUpper();
			strTestiCL[1] = m_pEsamiSet->m_setEP.m_sTestoCLTxt001.Trim().MakeUpper();
			strTestiCL[2] = m_pEsamiSet->m_setEP.m_sTestoCLTxt002.Trim().MakeUpper();
			strTestiCL[3] = m_pEsamiSet->m_setEP.m_sTestoCLTxt003.Trim().MakeUpper();
			strTestiCL[4] = m_pEsamiSet->m_setEP.m_sTestoCLTxt004.Trim().MakeUpper();
			strTestiCL[5] = m_pEsamiSet->m_setEP.m_sTestoCLTxt005.Trim().MakeUpper();
			strTestiCL[6] = m_pEsamiSet->m_setEP.m_sTestoCLTxt006.Trim().MakeUpper();
			strTestiCL[7] = m_pEsamiSet->m_setEP.m_sTestoCLTxt007.Trim().MakeUpper();
			strTestiCL[8] = m_pEsamiSet->m_setEP.m_sTestoCLTxt008.Trim().MakeUpper();
			strTestiCL[9] = m_pEsamiSet->m_setEP.m_sTestoCLTxt009.Trim().MakeUpper();
			strTestiCL[10] = m_pEsamiSet->m_setEP.m_sTestoCLTxt010.Trim().MakeUpper();
			strTestiCL[11] = m_pEsamiSet->m_setEP.m_sTestoCLTxt011.Trim().MakeUpper();
			strTestiCL[12] = m_pEsamiSet->m_setEP.m_sTestoCLTxt012.Trim().MakeUpper();
			strTestiCL[13] = m_pEsamiSet->m_setEP.m_sTestoCLTxt013.Trim().MakeUpper();
			strTestiCL[14] = m_pEsamiSet->m_setEP.m_sTestoCLTxt014.Trim().MakeUpper();
			strTestiCL[15] = m_pEsamiSet->m_setEP.m_sTestoCLTxt015.Trim().MakeUpper();
			strTestiCL[16] = m_pEsamiSet->m_setEP.m_sTestoCLTxt016.Trim().MakeUpper();
			strTestiCL[17] = m_pEsamiSet->m_setEP.m_sTestoCLTxt017.Trim().MakeUpper();
			strTestiCL[18] = m_pEsamiSet->m_setEP.m_sTestoCLTxt018.Trim().MakeUpper();
			strTestiCL[19] = m_pEsamiSet->m_setEP.m_sTestoCLTxt019.Trim().MakeUpper();

			BOOL bSegnalatoChecklist = FALSE;
			for (int i = 0; i < NUM_LABEL_TESTO_CL; i++)
			{
				CStringList paroleChiaveList;
				CString paroleChiave = theApp.m_sParoleChiaveCL[i].MakeUpper();

				int nTokenPos = 0;
				CString strToken = paroleChiave.Tokenize(";", nTokenPos);

				while (!strToken.IsEmpty())
				{
					paroleChiaveList.AddTail(strToken);
					strToken = paroleChiave.Tokenize(";", nTokenPos);
				}

				//Se c'è scritto qualcosa nella checklist
				if (theApp.m_bAlarmCL[i] && strTestiCL[i].GetLength() > 0)
				{
					bSegnalatoChecklist = TRUE;

					//Controllo se quello che c'è scritto è una parola chiave, in quel caso non mostro l'alert
					for (POSITION pos = paroleChiaveList.GetHeadPosition(); pos;)
					{
						CString strParola = paroleChiaveList.GetNext(pos);
						if (strTestiCL[i] == strParola)
						{
							bSegnalatoChecklist = FALSE;
							break;
						}

					}
				}
			}

			if ((m_pEsamiSet != NULL) && (!m_pEsamiSet->IsBOF()) && (!m_pEsamiSet->IsEOF()))
				pCmdUI->Enable(((!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_iAllergie)) && (m_pEsamiSet->m_iAllergie > 0)) || bSegnalatoChecklist);
			else
				pCmdUI->Enable(FALSE);
		}
		else
		{
			pCmdUI->Enable(TRUE);
		}

		break;
	}
	case IDC_ICON_SEGNALATO:
	{
		if (!theApp.m_bMenuUsaCarestreamExamesPendentes) //ICON_SEGNALATO -> ICON_CARESTREAM
		{
			BOOL bSegnalatoPaz = FALSE;
			BOOL bSegnalatoEsa = FALSE;

			if ((m_pPazientiSet != NULL) && (!m_pPazientiSet->IsBOF()) && (!m_pPazientiSet->IsEOF()))
				bSegnalatoPaz = !m_pPazientiSet->m_sDenSegnalato.IsEmpty();

			if ((m_pEsamiSet != NULL) && (!m_pEsamiSet->IsBOF()) && (!m_pEsamiSet->IsEOF()))
				bSegnalatoEsa = (((!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_iPacemaker)) && (m_pEsamiSet->m_iPacemaker > 0)) || ((!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_iAnticoagulanti)) && (m_pEsamiSet->m_iAnticoagulanti > 0)) || ((!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_iAntiaggreganti)) && (m_pEsamiSet->m_iAntiaggreganti > 1)));

			pCmdUI->Enable(bSegnalatoPaz || bSegnalatoEsa);
		}
		else
		{
			pCmdUI->Enable(TRUE);
		}

		break;
	}

	case IDC_PAZIENTE_PRENOTAZIONE:
	{
		pCmdUI->Enable(!m_bImporting && m_bPazientiValid && !m_bPazientiBusy && !m_bEsamiBusy && !theApp.m_sAgendaIndex.IsEmpty());
		break;
	}
	case IDC_BTN_CONCLUSIONI:
	{
		pCmdUI->Enable(!m_bImporting && m_bPazientiValid && !m_bPazientiBusy && !m_bEsamiBusy);
		break;
	}
	case IDC_PAZIENTE_CRONICO:
	{
		pCmdUI->Enable(!m_bImporting && m_bPazientiValid && !m_bPazientiBusy && !m_bEsamiBusy && (theApp.m_dwPrivileges & AMLogin_Permissions::modify_patient) && (m_pPazientiSet->m_lIDMalattiaCronica > 0));
		break;
	}

	case IDC_PAZIENTE_ALBUM:
	{
		if (theApp.m_bPersonalizzazioniBrasileSirio)
			pCmdUI->Enable(!m_bImporting && !m_bEsamiBusy && !m_bPazientiBusy);
		else
			pCmdUI->Enable(!m_bImporting && !m_bPazientiBusy && !m_bEsamiBusy && theApp.m_dwPrivileges & AMLogin_Permissions::view_image);
		break;
	}

	case IDC_LISTA_PRENOTAZIONI:
	{
		pCmdUI->Enable(!m_bImporting && !m_bPazientiBusy && !m_bEsamiBusy && !theApp.m_bTerminalServer && theApp.m_nInterfacciaPrenotazione != CEndoxApp::prenotazioni_none);
		break;
	}

	case IDC_PAZIENTE_ALLEGATI:
	{
		BOOL bEnable = m_bPazientiValid && !m_bPazientiBusy;

		pCmdUI->Enable(bEnable);

		if (bEnable && (m_lNumDocumentsPatient > 0))
		{
			CString strOut;
			strOut.Format("%li ", m_lNumDocumentsPatient);

			CRect rectProva;
			pCmdUI->m_pOther->GetWindowRect(rectProva);
			pCmdUI->m_pOther->ScreenToClient(rectProva);
			rectProva.DeflateRect(4, 4);

			// Sandro 06/07/2015 //
			rectProva.OffsetRect(m_lNumDocumentsPatientOffset, 0);

			//
			CDC* pDC = pCmdUI->m_pOther->GetDC();

			// memorizzo impostazioni precedenti //
			CFont* pOldFont = (CFont*)pDC->SelectObject(&theApp.m_fontBold);
			COLORREF crOldColor1 = pDC->SetBkColor(RGB(255, 255, 0));	// LIGHT YELLOW
			COLORREF crOldColor2 = pDC->SetTextColor(RGB(255, 0, 0));	// RED

			// disegno il numero sopra al tasto //
			pDC->DrawText(strOut, rectProva, DT_VCENTER | DT_RIGHT | DT_SINGLELINE);

			// ripristino gli oggetti precedentemente salvati //
			pDC->SetTextColor(crOldColor2);
			pDC->SetBkColor(crOldColor1);
			pDC->SelectObject(pOldFont);

			//
			pCmdUI->m_pOther->ReleaseDC(pDC);
		}

		break;
	}
	case IDC_FICHA:
	{
		pCmdUI->Enable(!m_bPazientiBusy && /*!m_bEsamiBusy &&*/ theApp.m_dwPrivileges & AMLogin_Permissions::view_image);
		break;
	}
	case IDC_ASSESSORIA:
	{
		pCmdUI->Enable(!m_bPazientiBusy && /*!m_bEsamiBusy &&*/ theApp.m_dwPrivileges & AMLogin_Permissions::view_image);
		break;
	}

	/////////////////////////////////
	// toolbar paziente di bolzANO //
	/////////////////////////////////

	case IDC_BTN_COMANDO:
	{
		pCmdUI->Enable(!m_bPazientiBusy && !m_bEsamiBusy && !theApp.m_bTerminalServer);
		break;
	}

	////////////////////////////
	// toolbar esame di endox //
	////////////////////////////

	case IDC_ESAME_FIRST:
	{
		pCmdUI->Enable(!m_bImporting && m_bEsamiPrev && !m_bPazientiBusy && !m_bEsamiBusy);
		break;
	}
	case IDC_ESAME_PREV:
	{
		pCmdUI->Enable(!m_bImporting && m_bEsamiPrev && !m_bPazientiBusy && !m_bEsamiBusy);
		break;
	}
	case IDC_ESAME_NEXT:
	{
		pCmdUI->Enable(!m_bImporting && m_bEsamiNext && !m_bPazientiBusy && !m_bEsamiBusy);
		break;
	}
	case IDC_ESAME_LAST:
	{
		pCmdUI->Enable(!m_bImporting && m_bEsamiNext && !m_bPazientiBusy && !m_bEsamiBusy);
		break;
	}

	case IDC_ESAME_NEW:
	{
		BOOL bEnable = !m_bImporting && !m_bPazientiIsNull && !m_bEsamiBusy && !m_bPazientiBusy && (theApp.m_dwPrivileges & AMLogin_Permissions::add_exam);

		if (theApp.m_bDisabilitaEsamiPazientiSenzaAssiden && (m_pPazientiSet->IsFieldNull(&m_pPazientiSet->m_sAssIden) || m_pPazientiSet->m_sAssIden == ""))
			bEnable = FALSE;

		if (m_pPazientiSet->m_bDeceduto == TRUE)
			bEnable = FALSE;

		pCmdUI->Enable(bEnable);
		break;
	}
	case IDC_ESAME_MODIFY:
	{
		pCmdUI->Enable(m_bEsamiValid && !m_bEsamiBusy && !m_bPazientiBusy && (theApp.m_dwPrivileges & AMLogin_Permissions::modify_exam) && m_pEsamiSet->m_bStessoDistretto);
		break;
	}
	case IDC_ESAME_DEL:
	{
		pCmdUI->Enable(!m_bBurning && !m_bImporting && m_bEsamiValid && !m_bEsamiBusy && !m_bPazientiBusy && (theApp.m_dwPrivileges & AMLogin_Permissions::delete_exam) && m_pEsamiSet->m_bStessoDistretto && !m_pEsamiSet->m_bSuperLocked);
		break;
	}
	case IDC_ESAME_UPDATE:
	{
		pCmdUI->Enable(m_bEsamiValid && m_bEsamiModify);
		break;
	}
	case IDC_ESAME_UNDO:
	{
		pCmdUI->Enable((m_bEsamiValid && m_bEsamiBusy) || (theApp.m_nProgramMode & FILTER_RECORD_ESAMI));
		break;
	}

	case IDC_ESAME_QUERY_DEF:
	{
		pCmdUI->Enable(!m_bImporting && (theApp.m_nProgramMode == NOTHING_MODE || (theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI))) && theApp.m_dwPrivileges & AMLogin_Permissions::statistics);
		break;
	}
	case IDC_ESAME_QUERY_APP:
	{
		pCmdUI->Enable(!m_bImporting && (theApp.m_nProgramMode != ADD_RECORD_PAZIENTI) && (theApp.m_nProgramMode != ADD_RECORD_ESAMI) && (theApp.m_nProgramMode != MODIFY_RECORD_PAZIENTI) && (theApp.m_nProgramMode != MODIFY_RECORD_ESAMI) && (m_bFilterBusy || (m_pQueryDlg != NULL)));
		break;
	}

	case IDC_ESAME_ALBUM:
	{
		pCmdUI->Enable(!m_bImporting && m_bEsamiValid && !m_bEsamiBusy && !m_bPazientiBusy && theApp.m_dwPrivileges & AMLogin_Permissions::view_image);
		break;
	}

	case IDC_TOOLBAR_STAMPAREPORT:
	{
		pCmdUI->Enable(!m_bImporting && !m_bEsamiIsNull && (theApp.m_dwPrivileges & AMLogin_Permissions::printout));
		break;
	}
	case IDC_TOOLBAR_STAMPAREPORTMACRO:
	{
		pCmdUI->Enable(!m_bImporting && !m_bEsamiIsNull && (theApp.m_dwPrivileges & AMLogin_Permissions::printout));
		break;
	}
	case IDC_ESAME_ALLEGATI:
	{
		BOOL bEnable = m_bPazientiValid && !m_bPazientiBusy && m_bEsamiValid && !m_bEsamiBusy;
		pCmdUI->Enable(bEnable);

		if (bEnable && (m_lNumDocumentsExam > 0))
		{
			CString strOut;
			strOut.Format("%li", m_lNumDocumentsExam);

			CRect rectProva;
			pCmdUI->m_pOther->GetWindowRect(rectProva);
			pCmdUI->m_pOther->ScreenToClient(rectProva);
			rectProva.DeflateRect(4, 4);

			// Sandro 06/07/2015 // RIMA 15052.4 //
			rectProva.OffsetRect(0, m_lNumDocumentsExamOffset);

			//
			CDC* pDC = pCmdUI->m_pOther->GetDC();

			// memorizzo impostazioni precedenti //
			CFont* pOldFont = (CFont*)pDC->SelectObject(&theApp.m_fontBold);
			COLORREF crOldColor1 = pDC->SetBkColor(RGB(255, 255, 0));	// LIGHT YELLOW
			COLORREF crOldColor2 = pDC->SetTextColor(RGB(255, 0, 0));	// RED

			// disegno il numero sopra al tasto //
			pDC->DrawText(strOut, rectProva, DT_BOTTOM | DT_CENTER | DT_SINGLELINE);

			// ripristino gli oggetti precedentemente salvati //
			pDC->SetTextColor(crOldColor2);
			pDC->SetBkColor(crOldColor1);
			pDC->SelectObject(pOldFont);

			//
			pCmdUI->m_pOther->ReleaseDC(pDC);
		}

		break;
	}
	case IDC_ESAME_ALLEGATICARESTREAM:
	{
		BOOL bEnable = m_bPazientiValid && !m_bPazientiBusy && m_bEsamiValid && !m_bEsamiBusy;
		pCmdUI->Enable(bEnable);

		if (bEnable && (m_lNumDocumentsExamCarestream > 0))
		{
			CString strOut;
			strOut.Format("%li", m_lNumDocumentsExamCarestream);

			CRect rectProva;
			pCmdUI->m_pOther->GetWindowRect(rectProva);
			pCmdUI->m_pOther->ScreenToClient(rectProva);
			rectProva.DeflateRect(4, 4);

			// Sandro 06/07/2015 // RIMA 15052.4 //
			rectProva.OffsetRect(0, m_lNumDocumentsExamCarestreamOffset);

			//
			CDC* pDC = pCmdUI->m_pOther->GetDC();

			// memorizzo impostazioni precedenti //
			CFont* pOldFont = (CFont*)pDC->SelectObject(&theApp.m_fontBold);
			COLORREF crOldColor1 = pDC->SetBkColor(RGB(255, 191, 0));   // YELLOW EGG
			COLORREF crOldColor2 = pDC->SetTextColor(RGB(255, 0, 0));	// RED

			// disegno il numero sopra al tasto //
			pDC->DrawText(strOut, rectProva, DT_BOTTOM | DT_CENTER | DT_SINGLELINE);

			// ripristino gli oggetti precedentemente salvati //
			pDC->SetTextColor(crOldColor2);
			pDC->SetBkColor(crOldColor1);
			pDC->SelectObject(pOldFont);

			//
			pCmdUI->m_pOther->ReleaseDC(pDC);
		}

		break;
	}

	///////////////////
	// toolbar album //
	///////////////////

	case IDC_IMM_FIRST:
	{
		pCmdUI->Enable(m_pFormImmagini->m_nDiapoPage > 0);
		break;
	}
	case IDC_IMM_PREV:
	{
		pCmdUI->Enable(m_pFormImmagini->m_nDiapoPage > 0);
		break;
	}
	case IDC_IMM_NEXT:
	{
		pCmdUI->Enable((m_pFormImmagini->m_nDiapoPage >= 0) && (m_pFormImmagini->m_nDiapoPage < (m_pFormImmagini->m_nMaxDiapo / m_pFormImmagini->m_nNumMaxBmp)));
		break;
	}
	case IDC_IMM_LAST:
	{
		pCmdUI->Enable((m_pFormImmagini->m_nDiapoPage >= 0) && (m_pFormImmagini->m_nDiapoPage < (m_pFormImmagini->m_nMaxDiapo / m_pFormImmagini->m_nNumMaxBmp)));
		break;
	}
	case IDC_IMM_DISK:
	{
		pCmdUI->Enable(!m_bImporting && (theApp.m_bCanAcquire || theApp.m_bSoloDicom || theApp.m_bSoloAutoImport) && m_bEsamiValid && !m_bEsamiBusy && !m_bPazientiBusy && (theApp.m_dwPrivileges & AMLogin_Permissions::modify_image) && m_pEsamiSet->m_bStessoDistretto && !m_pEsamiSet->m_bSuperLocked);
		break;
	}
	case IDC_IMM_SCAN:
	{
		pCmdUI->Enable(!m_bImporting && (theApp.m_bCanAcquire || theApp.m_bSoloDicom || theApp.m_bSoloAutoImport) && m_bEsamiValid && !m_bEsamiBusy && !m_bPazientiBusy && (theApp.m_dwPrivileges & AMLogin_Permissions::modify_image) && m_pEsamiSet->m_bStessoDistretto && !m_pEsamiSet->m_bSuperLocked);
		break;
	}
	case IDC_IMM_ACQ:
	{
		if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury)
			pCmdUI->Enable(!m_bBurning && !m_bImporting && (theApp.m_bCanAcquire || theApp.m_bSoloDicom || theApp.m_bSoloAutoImport) && m_bEsamiValid && !m_bEsamiBusy && !m_bPazientiBusy && (theApp.m_dwPrivileges & AMLogin_Permissions::modify_image) && m_pEsamiSet->m_bStessoDistretto && !m_pEsamiSet->m_bSuperLocked); // Sandro 02/11/2016 // tolgo "&& !m_pEsamiSet->m_bLocked &&" (richiesta telefonica di Pilotto per il Fleury) //
		else
			pCmdUI->Enable(!m_bBurning && !m_bImporting && (theApp.m_bCanAcquire || theApp.m_bSoloDicom || theApp.m_bSoloAutoImport) && m_bEsamiValid && !m_bEsamiBusy && !m_bPazientiBusy && (theApp.m_dwPrivileges & AMLogin_Permissions::modify_image) && m_pEsamiSet->m_bStessoDistretto && !m_pEsamiSet->m_bLocked && !m_pEsamiSet->m_bSuperLocked);
		break;
	}
	case IDC_IMM_MULTIPAGE:
	{
		pCmdUI->Enable(!m_bImporting && theApp.m_bCanAcquire && m_bEsamiValid && !m_bEsamiBusy && !m_bPazientiBusy && (theApp.m_dwPrivileges & AMLogin_Permissions::modify_image) && m_pEsamiSet->m_bStessoDistretto && !m_pEsamiSet->m_bSuperLocked); // Sandro 03/07/2014 // tolgo "&& !m_pEsamiSet->m_bLocked &&" (vedi RAS 20140026) //
		break;
	}
	case IDC_IMM_ASS:
	{
		if (theApp.m_nApplication == PRG_DERMOX)
			pCmdUI->Enable(FALSE);
		else
			pCmdUI->Enable(!m_bImporting && m_bEsamiValid && !m_bEsamiBusy && !m_bPazientiBusy && (theApp.m_dwPrivileges & AMLogin_Permissions::modify_image) && m_pEsamiSet->m_bStessoDistretto);
		break;
	}
	case IDC_IMM_SELECT:
	{
		pCmdUI->Enable(m_bEsamiValid && !m_bEsamiBusy && !m_bPazientiBusy && theApp.m_dwPrivileges & AMLogin_Permissions::view_image);
		break;
	}
	case IDC_IMM_UNSELECT:
	{
		pCmdUI->Enable(m_bEsamiValid && !m_bEsamiBusy && !m_bPazientiBusy && theApp.m_dwPrivileges & AMLogin_Permissions::view_image);
		break;
	}
	case IDC_IMM_PREVIEW:
	{
		pCmdUI->Enable(!m_bImporting && (theApp.m_dwPrivileges & AMLogin_Permissions::printout) && m_pEsamiSet->m_bStessoDistretto && m_bEsamiValid && !m_bEsamiBusy && !m_bPazientiBusy); // Sandro // 03/01/2011 //
		break;
	}
	case IDC_IMM_DEL:
	{
		//Gabriel BUG 7768 - Continuous capture problem FIX
		if (theApp.m_bUsaNovaCapturaContinua)
			pCmdUI->Enable(m_bEsamiValid && !m_bEsamiBusy && !m_bPazientiBusy && (theApp.m_dwPrivileges & AMLogin_Permissions::modify_image) && m_pEsamiSet->m_bStessoDistretto && !m_pEsamiSet->m_bLocked && !m_pEsamiSet->m_bSuperLocked);
		else
			pCmdUI->Enable(!m_bImporting && m_bEsamiValid && !m_bEsamiBusy && !m_bPazientiBusy && (theApp.m_dwPrivileges & AMLogin_Permissions::modify_image) && m_pEsamiSet->m_bStessoDistretto && !m_pEsamiSet->m_bLocked && !m_pEsamiSet->m_bSuperLocked);
		break;
	}
	case IDC_IMM_ALBUM:
	{
		pCmdUI->Enable(!m_bImporting && m_bEsamiValid && !m_bEsamiBusy && !m_bPazientiBusy && theApp.m_dwPrivileges & AMLogin_Permissions::view_image);
		break;
	}
	case IDC_IMM_REORDER:
	{
		pCmdUI->Enable(!m_bImporting && m_bEsamiValid && !m_bEsamiBusy && !m_bPazientiBusy && theApp.m_dwPrivileges);
		break;
	}
	//Gabriel - TCP
	case ID_OPZIONI_SETUPUNITATCP:
	{
		if (theApp.m_bPersonalizzazioniBrasileFleury)
			pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_01 && m_pEsamiSet->m_lUO == 7 && theApp.m_bAtivaTCP);
		break;
	}

	case ID_ESAMECORRENTE_RECONVOCAZIONE:
	{
		if (theApp.m_bPersonalizzazioniBrasileFleury)
			pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_01 && theApp.m_bAtivaListaDO);
		break;
	}

	case ID_GESTIONE_FLUSSODISTATO:
	{
		if (theApp.m_bPersonalizzazioniBrasileFleury)
			pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_01 && theApp.m_bAtivaListaDO);
		break;
	}

	///
	///
	///

	default:
	{
		// Sandro 10/11/2010 - RAS 20100132 //
		if ((pCmdUI->m_nID > MENU_STAMPA_ETICHETTE) && (pCmdUI->m_nID < MENU_TUTORIAL_FILES))
			pCmdUI->Enable(theApp.m_dwPrivileges & AMLogin_Permissions::printout);

		// Sandro 20/06/2016 - RIMA 16001 //
		if ((pCmdUI->m_nID > MENU_TUTORIAL_FILES) && (pCmdUI->m_nID < FASI_ESAME))
			pCmdUI->Enable(TRUE);

		break;
	}
	}

	//Julio Ordem Fechamento/Desbloqueio de fases
	if (pCmdUI->m_nID > FASI_ESAME + 1000) //newMenuAnnullaChiusuraFase
	{
		int idFase = pCmdUI->m_nID - (FASI_ESAME + 1000);
		pCmdUI->Enable(
			m_listIDFasiChiuse.Find(idFase) != NULL
			&& m_bEsamiValid
			&& m_pEsamiSet->m_bStessoDistretto
			&& !m_bPazientiBusy
			&& !m_bEsamiBusy
			&& theApp.m_listUserPhases.Find(idFase) != NULL
			&& m_pEsamiSet->m_sFleuryTrasferito.IsEmpty());


#ifdef _DEBUG //Esse debug ignora o bloqueio que poderia acontecer se o usuario atual nao tivesse permissao de grupo
		pCmdUI->Enable(m_listIDFasiChiuse.Find(idFase) != NULL && m_bEsamiValid && m_pEsamiSet->m_bStessoDistretto && !m_bPazientiBusy && !m_bEsamiBusy && m_pEsamiSet->m_sFleuryTrasferito.IsEmpty());
#endif 
	}
	else if (pCmdUI->m_nID > FASI_ESAME) //newMenuChiusuraFase
	{
		int idFase = pCmdUI->m_nID - FASI_ESAME;
		pCmdUI->Enable(
			m_listIDFasiChiuse.Find(idFase) == NULL
			&& m_bEsamiValid
			&& m_pEsamiSet->m_bStessoDistretto
			&& !m_bPazientiBusy
			&& !m_bEsamiBusy
			&& theApp.m_listUserPhases.Find(idFase) != NULL
			&& m_pEsamiSet->m_sFleuryTrasferito.IsEmpty());

#ifdef _DEBUG //Esse debug ignora o bloqueio que poderia acontecer se o usuario atual nao tivesse permissao de grupo
		pCmdUI->Enable(m_listIDFasiChiuse.Find(idFase) == NULL && m_bEsamiValid && m_pEsamiSet->m_bStessoDistretto && !m_bPazientiBusy && !m_bEsamiBusy && m_pEsamiSet->m_sFleuryTrasferito.IsEmpty());
#endif 
	}
	//
}

void CEsamiView::OnToolbarStampaReport()
{
	// Sandro 29/09/2016 // RIMA 16037 Fleury //

	if (theApp.m_bPersonalizzazioniBrasileFleury && CEsamiSet().IsConiugatoSecondario(m_pEsamiSet->m_lContatore))
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_STAMPA_IMMAGINI_ERRORE_5));
		return;
	}

	BOOL bStampa = TRUE;

	CString sMessaggio = "";
	if (theApp.m_bPersonalizzazioniBrasileFleury)
		if (m_pEsamiSet->m_bSuperLocked)
			bStampa = FleuryPossoStampare(sMessaggio, m_pEsamiSet->m_sRicovero, m_pEsamiSet->m_sCodEsame);

	if (!bStampa)
	{
		theApp.AfxMessageBoxEndo(sMessaggio);
		return;
	}

	// Sandro 27/02/2014 // richiesta Paron Pilotto //
	if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
	{
		if (m_pEsamiSet->m_bSuperLocked != TRUE)
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAME_NON_CHIUSO));
			return;
		}
	}

	// controllo di essere in visualizzazione //
	if (theApp.m_nProgramMode != NOTHING_MODE)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_SAVE_BEFORE_PRINT));
		return;
	}

	// controllo se l'esame fa parte del mio distretto //
	if (!m_pEsamiSet->m_bStessoDistretto)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_REFERTO_NOTPRINTABLE));
		return;
	}

	// controllo se tutti i campi obbligatori sono validi //
	if (!VerificaCampiObbligatoriFase(CO_FASE_CHIUSURA_STAMPA))
		return;

	// --> Davide/Sandro - Firma digitale
	if (theApp.m_enumFirmaDigitale != CEndoxApp::sign_disabled)
	{
		OnToolbarStampaReportFirmaDigitale("", 0);
		return;
	}

	// Sandro 26/11/2013 //
	BOOL bProcedi = FALSE;
	if (theApp.m_bTastoStampaReportStampaSempre)
		bProcedi = TRUE;
	else
		bProcedi = !OnCommandMenuGestioneVisualizzaStampe(FALSE); // se esistono dei PDF nell'esame mostro quelli così non genero nuove stampe inutilmente //

	if (bProcedi)
	{
		// Sandro 04/08/2014 // modifica per Battaglia //
		if (theApp.m_enumFirmaDigitale != CEndoxApp::sign_disabled)
		{
			OnToolbarStampaReportFirmaDigitale("", 0);
			return;
		}

		BOOL bPrinted = FALSE;

		if ((m_pEsamiSet != NULL) && (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lIDEsame)))
		{
			CString strFilter;

			CReportsDefaultSet setRepDef;
			setRepDef.SetSortRecord("ID");

			BOOL bStampaImmagini = FALSE;
			long lStampaImmaginiCopie = 0;

			// Sandro 18/06/2015 // controllo se devo stampare anche le immagini //

			strFilter.Format("SedeEsame='%s' AND TipoEsame=%li AND Report = 'IMMAGINI'", CSediEsameSet().GetDescrizione(theApp.m_lIDSedeEsameDefault, TRUE), m_pEsamiSet->m_lIDEsame);
			setRepDef.SetOpenFilter(strFilter);
			if (setRepDef.OpenRecordset("CEsamiView::OnToolbarStampaReport"))
			{
				if (!setRepDef.IsEOF())
				{
					bStampaImmagini = TRUE;
					lStampaImmaginiCopie = setRepDef.m_lCopie;
				}
				setRepDef.CloseRecordset("CEsamiView::OnToolbarStampaReport");
			}

			// controllo se esistono dei reports di default associati all'esame //

			strFilter.Format("SedeEsame='%s' AND TipoEsame=%li AND Report <> 'IMMAGINI'", CSediEsameSet().GetDescrizione(theApp.m_lIDSedeEsameDefault, TRUE), m_pEsamiSet->m_lIDEsame);
			setRepDef.SetOpenFilter(strFilter);
			if (setRepDef.OpenRecordset("CEsamiView::OnToolbarStampaReport"))
			{
				CList<STRUCT_STAMPA_CUMULATIVA> listStampaCumulativa;

				while (!setRepDef.IsEOF())
				{
					// controllo se è definito il report di default //
					if (!setRepDef.m_sReport.IsEmpty())
					{
						STRUCT_STAMPA structStampa;
						if (SelezionaFileReport(&structStampa, setRepDef.m_sReport))
						{
							//
							BeginWaitCursor();

							m_listIDStampate.RemoveAll();

							CString sPdfFileComplete = "";
							if (CreateHaruPdfReportFile(sPdfFileComplete, &structStampa, FALSE, ""))
							{
								// se necessario archivio la copia del pdf //

								if (structStampa.m_bArchivePDFCopy)
									ArchiviaPdf(pdftype_report, &sPdfFileComplete, structStampa.m_sReportFileOriginal, FALSE, FALSE, structStampa.m_bFitToPage, 0, 0);

								// Sandro 29/05/2014 // contrassegno le immagini stampate //

								if (m_listIDStampate.GetCount() > 0)
									m_pImgManager->SetPrintedImages(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, theApp.m_bSalvaSoloUltimeImmaginiStampate, &m_listIDStampate);

								// aggiungo il pdf in coda di stampa cumulativa //

								STRUCT_STAMPA_CUMULATIVA ssc;
								ssc.m_sRptFile = structStampa.m_sReportFileOriginal;
								ssc.m_sPdfFile = sPdfFileComplete;
								ssc.m_lPrinterToUse = structStampa.m_lPrinterToUse;
								ssc.m_lCopies = setRepDef.m_lCopie;
								ssc.m_bFitToPage = structStampa.m_bFitToPage;

								listStampaCumulativa.AddTail(ssc);
							}
							m_listIDStampate.RemoveAll();

							//
							EndWaitCursor();
						}

						// tutto ok //
						bPrinted = TRUE;
					}

					setRepDef.MoveNext();
				}
				setRepDef.CloseRecordset("CEsamiView::OnToolbarStampaReport");

				// Sandro 18/06/2015 // aggiungo anche la stampa delle immagini //

				if (bStampaImmagini)
				{
					// Sandro 26/11/2013 //
					if ((m_pFormImmagini != NULL) && (CFileBmp::CountPrinterList(LOCAL_IMAGES) == 0) && theApp.m_bStampaSelezionaAutomaticaImmaginiStampate)
						m_pFormImmagini->SelectAlreadyPrintedImages();

					// riempio la lista delle immagini da stampare //
					long lSelectedImm = CFileBmp::FillImagesPrinterList(LOCAL_IMAGES);

					// controllo che siano state selezionate le immagini //
					if (lSelectedImm > 0)
					{
						// controllo che l'utente corrente abbia il diritto di stampare le immagini //
						if ((theApp.m_dwPrivileges & AMLogin_Permissions::printout) != 0)
						{
							//
							BeginWaitCursor();

							// creo il PDF //
							m_listIDStampate.RemoveAll();

							CString sPdfFileComplete = CreateHaruPdfImageFile(m_pEsamiSet->m_sCodEsame);
							if (!sPdfFileComplete.IsEmpty())
							{
								// se necessario archivio la copia del pdf //
								if (theApp.m_bPDFImmaginiCrea)
									ArchiviaPdf(pdftype_images, &sPdfFileComplete, "", FALSE, FALSE, TRUE, 0, 0);

								// Sandro 29/05/2014 // contrassegno le immagini stampate //
								if (m_listIDStampate.GetCount() > 0)
									m_pImgManager->SetPrintedImages(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, theApp.m_bSalvaSoloUltimeImmaginiStampate, &m_listIDStampate);

								// aggiungo il pdf in coda di stampa cumulativa //

								STRUCT_STAMPA_CUMULATIVA ssc;
								ssc.m_sRptFile = theApp.GetMessageString(IDS_STAMPA_IMMAGINI);
								ssc.m_sPdfFile = sPdfFileComplete;
								ssc.m_lPrinterToUse = theApp.m_lIDStampanteImmagini;
								ssc.m_lCopies = lStampaImmaginiCopie;
								ssc.m_bFitToPage = TRUE;

								listStampaCumulativa.AddTail(ssc);
							}
							m_listIDStampate.RemoveAll();

							//
							EndWaitCursor();

							// tutto ok //
							bPrinted = TRUE;
						}
					}
				}

				// Sandro 01/04/2015 // RIMA 15008 //

				POSITION pos = listStampaCumulativa.GetHeadPosition();
				while (pos != NULL)
				{
					// prima stampo tutti i reports senza una stampante predefinita associata //

					STRUCT_STAMPA_CUMULATIVA ssc = listStampaCumulativa.GetNext(pos);

					if (ssc.m_lPrinterToUse == Printer_ChiediStampante)
					{
						CPdfStampaDlg(this, ssc.m_sRptFile, ssc.m_sPdfFile, FALSE, 0, ssc.m_lCopies, ssc.m_bFitToPage).DoModal();
						DeleteFile(ssc.m_sPdfFile);
					}
				}

				for (int i = Printer_Immagini; i <= Printer_Report9; i++)
				{
					// per ognuna delle 10 stampanti predefinite mi creo una lista dei reports da accorpare, tenendo in considerazione anche il numero di copie da stampare //

					CStringList listPdfInputFiles;

					POSITION pos = listStampaCumulativa.GetHeadPosition();
					while (pos != NULL)
					{
						STRUCT_STAMPA_CUMULATIVA ssc = listStampaCumulativa.GetNext(pos);

						if (ssc.m_lPrinterToUse == i)
						{
							if (ssc.m_lCopies <= 0)
							{
								CNumeroCopieStampaDlg dlgTemp(this, ssc.m_sRptFile);
								if (dlgTemp.DoModal() == IDOK)
									for (int j = 0; j < dlgTemp.GetNumeroCopie(); j++)
										listPdfInputFiles.AddTail(ssc.m_sPdfFile);
							}
							else
							{
								for (int j = 0; j < ssc.m_lCopies; j++)
									listPdfInputFiles.AddTail(ssc.m_sPdfFile);
							}
						}
					}

					// se ci sono reports da stampare su questa stampante predefinita procedo //

					if (listPdfInputFiles.GetCount() > 0)
					{
						SYSTEMTIME timeLocal;
						::GetLocalTime(&timeLocal);

						CString sFinalFileName;
						sFinalFileName.Format("%s\\%02d_%04d%02d%02d%02d%02d%02d.pdf", theApp.m_sDirTemp, i, timeLocal.wYear, timeLocal.wMonth, timeLocal.wDay, timeLocal.wHour, timeLocal.wMinute, timeLocal.wSecond);

						// accorpo tutto all'interno di un unico grande pdf //

						if (CPdfUtilInterface::Get()->Merge(&listPdfInputFiles, sFinalFileName))
						{
							/* #ifdef _DEBUG
							// anteprima dell'unico grande pdf //
							CPdfAnteprimaDlg(this, sFinalFileName, ANTEPRIMADLG_SEMPLICE).DoModal();
							#else */
							// stampo l'unico grande pdf //
							CPdfStampaDlg(this, "", sFinalFileName, FALSE, i, 1, FALSE).DoModal();
							// #endif
						}

						// cancello i file dei "pdf singoli" //

						POSITION posTmp = listPdfInputFiles.GetHeadPosition();
						while (posTmp != NULL)
						{
							CString sFileToDelete = listPdfInputFiles.GetNext(posTmp);
							DeleteFile(sFileToDelete);
						}

						// cancello il file del "pdf cumulativo" //

						DeleteFile(sFinalFileName);
					}
				}
			}

			// Sandro 18/06/2015 // faccio l'eventuale stampa delle immagini solo nel caso in cui nulla sia stato stampato prima (altrimenti le immagini sono già andate anche quelle e non serve ristamparle) //
			if (!bPrinted && bStampaImmagini)
			{
				AnteprimaStampaImmagini(STAMPA, LOCAL_IMAGES, lStampaImmaginiCopie);
				bPrinted = TRUE;
			}

			// se per qualsiasi motivo non ho stampato nulla lancio la stampa report "classico" //
			if (!bPrinted)
			{
				//
				STRUCT_STAMPA structStampa;
				if (SelezionaFileReport(&structStampa))
				{
					//
					BeginWaitCursor();

					m_listIDStampate.RemoveAll();

					CString sPdfFileComplete = "";
					if (CreateHaruPdfReportFile(sPdfFileComplete, &structStampa, FALSE, ""))
					{
						if (CPdfStampaDlg(this, structStampa.m_sReportFileOriginal, sPdfFileComplete, FALSE, structStampa.m_lPrinterToUse, 0, structStampa.m_bFitToPage).DoModal() == IDOK)
						{
							if (structStampa.m_bArchivePDFCopy)
								ArchiviaPdf(pdftype_report, &sPdfFileComplete, structStampa.m_sReportFileOriginal, FALSE, FALSE, structStampa.m_bFitToPage, 0, 0);

							// Sandro 29/05/2014 // contrassegno le immagini stampate //
							if (m_listIDStampate.GetCount() > 0)
								m_pImgManager->SetPrintedImages(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, theApp.m_bSalvaSoloUltimeImmaginiStampate, &m_listIDStampate);
						}

						DeleteFile(sPdfFileComplete);
					}
					m_listIDStampate.RemoveAll();

					//
					EndWaitCursor();
				}
			}
		}
		else
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_REFERTO_NOTPRINTABLE));
		}
	}

	// Sandro 02/04/2015 // per sicurezza faccio un altro giro per cancellare tutti i pdf //
	CPdfUtilInterface::Get()->DeleteAllPdf(theApp.m_sDirTemp);

	// Sandro 07/03/2011 // deseleziono le immagini //
	if (theApp.m_bAutoDeselect)
		CFileBmp::DeleteListSelected(LOCAL_IMAGES);

	// Sandro 26/11/2013 // devo refreshare l'album, ora che contrassegno le immagini stampate //
	m_pFormImmagini->SendMessage(MSG_AFTER_ELABIMAGE, (WPARAM)FALSE);
}

void CEsamiView::OnToolbarStampaReportFirmaDigitale(CString sReportDaFirmare, long lCopieDaStampare)
{
	if (theApp.m_bPersonalizzazioniBrasileFleury && CEsamiSet().IsConiugatoSecondario(m_pEsamiSet->m_lContatore))
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_STAMPA_IMMAGINI_ERRORE_5));
		return;
	}

	BeginWaitCursor();

	switch (theApp.m_enumFirmaDigitale)
	{
	case CEndoxApp::sign_comped:
	{
		if (!m_pEsamiSet->m_bFirmato)
		{
			theApp.m_sSmartCardPin = "";

			if (AmTesiSign_Initialize() != NoError)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_1), MB_ICONSTOP);
				return;
			}

			if (AmTesiSign_ReadSmartCard() != NoError)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DIGITAL_SIGN_ERROR_2), MB_ICONSTOP);
				AmTesiSign_Finalize();
				return;
			}

			// Sandro 01/03/2013 //
			INT_PTR iReturn = IDCANCEL;
			CSmartCardPinDlg dlg(this);
			do
			{
				iReturn = dlg.DoModal();
				if (iReturn == IDCANCEL)
					break;
			} while (AmTesiSign_ReadCertificate(dlg.m_strPin) != NoError);

			if (iReturn == IDCANCEL)
			{
				AmTesiSign_Finalize();
				return;
			}

			theApp.m_sSmartCardPin = dlg.m_strPin;

			long lIdPdf = -1;

			if (sReportDaFirmare.IsEmpty())
			{
				// controllo se esistono dei reports di default associati all'esame //
				CString strFilter;
				strFilter.Format("SedeEsame='%s' AND TipoEsame=%li AND Report<>'IMMAGINI'", CSediEsameSet().GetDescrizione(theApp.m_lIDSedeEsameDefault, TRUE), m_pEsamiSet->m_lIDEsame);

				CReportsDefaultSet setRepDef;
				setRepDef.SetOpenFilter(strFilter);
				setRepDef.SetSortRecord("ID");
				if (setRepDef.OpenRecordset("CEsamiView::OnToolbarStampaReportFirmaDigitale"))
				{
					if (!setRepDef.IsEOF())
					{
						// controllo se è definito il report di default //
						if (!setRepDef.m_sReport.IsEmpty())
						{
							STRUCT_STAMPA structStampa;
							if (SelezionaFileReport(&structStampa, setRepDef.m_sReport))
							{
								//
								BeginWaitCursor();

								m_listIDStampate.RemoveAll();

								CString sPdfFileComplete = "";
								if (CreateHaruPdfReportFile(sPdfFileComplete, &structStampa, FALSE, ""))
								{
									// Sandro 04/02/2014 // RAS 20130201 //

									long lOper = 0x555; // solo firma senza stampa //

									if (theApp.m_bFirmaDigitaleAnteprimaMostra)
									{
										lOper = CPdfAnteprimaDlg(this, this, sPdfFileComplete, ANTEPRIMADLG_FIRMA).DoModal();

										CLogFileWriter::Get()->WriteLogLine0("Firma004");
									}
									else
									{
										switch (theApp.m_lFirmaDigitaleStampa)
										{
										case 0: // non stampa mai //
										{
											// lOper = 0x555; // solo firma senza stampa //
											break;
										}
										case 1: // stampa sempre //
										{
											lOper = 0x777; // firma e stampa //
											break;
										}
										default: // chiede se stampare o meno //
										{
											if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_STAMPARE_REFERTO), MB_YESNO | MB_ICONQUESTION) == IDYES)
												lOper = 0x777; // firma e stampa //
											// else
											// lOper = 0x555; // solo firma senza stampa //

											break;
										}
										}
									}

									//

									switch (lOper)
									{
									case 0x555: // solo firma senza stampa //
									case 0x777: // firma e stampa //
									{
										long lIDPdfCheSostituisce = 0;
										long lVersioneReferto = 0;

										CLogFileWriter::Get()->WriteLogLine0("Firma005");

										CPdfManager().GetDatiUltimoPdfFirmatoIDVersioneReferto(m_pEsamiSet->m_lContatore, lIDPdfCheSostituisce, lVersioneReferto);

										CLogFileWriter::Get()->WriteLogLine0("Firma006");

										lVersioneReferto++;

										CString cleanPdfFile = "";

										lIdPdf = ArchiviaPdf(pdftype_report, &sPdfFileComplete, structStampa.m_sReportFileOriginal, TRUE, FALSE, structStampa.m_bFitToPage, lVersioneReferto, lIDPdfCheSostituisce);

										CLogFileWriter::Get()->WriteLogLine0("Firma007");

										if ((lIdPdf > 0) && (lIDPdfCheSostituisce > 0))
											CPdfManager().SetPdfSospeso(lIDPdfCheSostituisce, m_pPazientiSet->m_lContatore, m_pEsamiSet->m_lContatore, theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, TRUE);

										CLogFileWriter::Get()->WriteLogLine0("Firma008");

										if ((lIdPdf > 0) && (lOper == 0x777))
										{
											BOOL bStampa = TRUE;

											CString sMessaggio = "";
											if (theApp.m_bPersonalizzazioniBrasileFleury)
												bStampa = FleuryPossoStampare(sMessaggio, m_pEsamiSet->m_sRicovero, m_pEsamiSet->m_sCodEsame);

											if (bStampa)
												CPdfStampaDlg(this, structStampa.m_sReportFileOriginal, sPdfFileComplete, FALSE, structStampa.m_lPrinterToUse, lCopieDaStampare, structStampa.m_bFitToPage).DoModal();
											else
												theApp.AfxMessageBoxEndo(sMessaggio);
										}

										CLogFileWriter::Get()->WriteLogLine0("Firma009");

										// Sandro 29/05/2014 // contrassegno le immagini stampate //
										if (m_listIDStampate.GetCount() > 0)
											m_pImgManager->SetPrintedImages(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, theApp.m_bSalvaSoloUltimeImmaginiStampate, &m_listIDStampate);

										CLogFileWriter::Get()->WriteLogLine0("Firma010");

										break;
									}
									}

									DeleteFile(sPdfFileComplete);
								}
								m_listIDStampate.RemoveAll();

								//
								EndWaitCursor();
							}
						}
					}

					setRepDef.CloseRecordset("CEsamiView::OnToolbarStampaReportFirmaDigitale");
				}
			}

			if (lIdPdf < 0)
			{
				STRUCT_STAMPA structStampa;

				BOOL bContinue = FALSE;
				if (!sReportDaFirmare.IsEmpty())
					bContinue = SelezionaFileReport(&structStampa, sReportDaFirmare);
				else
					bContinue = SelezionaFileReport(&structStampa);

				if (bContinue)
				{
					//
					BeginWaitCursor();

					m_listIDStampate.RemoveAll();

					CString sPdfFileComplete = "";
					if (CreateHaruPdfReportFile(sPdfFileComplete, &structStampa, FALSE, ""))
					{
						// Sandro 04/02/2014 // RAS 20130201 //

						long lOper = 0x555; // solo firma senza stampa //

						if (theApp.m_bFirmaDigitaleAnteprimaMostra)
						{
							lOper = CPdfAnteprimaDlg(this, this, sPdfFileComplete, ANTEPRIMADLG_FIRMA).DoModal();

							CLogFileWriter::Get()->WriteLogLine0("Firma011");
						}
						else
						{
							switch (theApp.m_lFirmaDigitaleStampa)
							{
							case 0: // non stampa mai //
							{
								// lOper = 0x555; // solo firma senza stampa //
								break;
							}
							case 1: // stampa sempre //
							{
								lOper = 0x777; // firma e stampa //
								break;
							}
							default: // chiede se stampare o meno //
							{
								if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_STAMPARE_REFERTO), MB_YESNO | MB_ICONQUESTION) == IDYES)
									lOper = 0x777; // firma e stampa //
								// else
								// lOper = 0x555; // solo firma senza stampa //

								break;
							}
							}
						}

						//

						switch (lOper)
						{
						case 0x555: // solo firma senza stampa //
						case 0x777: // firma e stampa //
						{
							long lIDPdfCheSostituisce = 0;
							long lVersioneReferto = 0;

							CLogFileWriter::Get()->WriteLogLine0("Firma012");

							CPdfManager().GetDatiUltimoPdfFirmatoIDVersioneReferto(m_pEsamiSet->m_lContatore, lIDPdfCheSostituisce, lVersioneReferto);

							CLogFileWriter::Get()->WriteLogLine0("Firma013");

							lVersioneReferto++;

							CString cleanPdfFile = "";

							lIdPdf = ArchiviaPdf(pdftype_report, &sPdfFileComplete, structStampa.m_sReportFileOriginal, TRUE, FALSE, structStampa.m_bFitToPage, lVersioneReferto, lIDPdfCheSostituisce);

							CLogFileWriter::Get()->WriteLogLine0("Firma014");

							if ((lIdPdf > 0) && (lIDPdfCheSostituisce > 0))
								CPdfManager().SetPdfSospeso(lIDPdfCheSostituisce, m_pPazientiSet->m_lContatore, m_pEsamiSet->m_lContatore, theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, TRUE);

							CLogFileWriter::Get()->WriteLogLine0("Firma015");

							if ((lIdPdf > 0) && (lOper == 0x777))
							{
								BOOL bStampa = TRUE;

								CString sMessaggio = "";
								if (theApp.m_bPersonalizzazioniBrasileFleury)
									bStampa = FleuryPossoStampare(sMessaggio, m_pEsamiSet->m_sRicovero, m_pEsamiSet->m_sCodEsame);

								if (bStampa)
									CPdfStampaDlg(this, structStampa.m_sReportFileOriginal, sPdfFileComplete, FALSE, structStampa.m_lPrinterToUse, lCopieDaStampare, structStampa.m_bFitToPage).DoModal();
								else
									theApp.AfxMessageBoxEndo(sMessaggio);
							}

							CLogFileWriter::Get()->WriteLogLine0("Firma016");

							// Sandro 29/05/2014 // contrassegno le immagini stampate //
							if (m_listIDStampate.GetCount() > 0)
								m_pImgManager->SetPrintedImages(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, theApp.m_bSalvaSoloUltimeImmaginiStampate, &m_listIDStampate);

							CLogFileWriter::Get()->WriteLogLine0("Firma017");

							break;
						}
						}

						DeleteFile(sPdfFileComplete);
					}
					m_listIDStampate.RemoveAll();

					//
					EndWaitCursor();
				}
			}

			CLogFileWriter::Get()->WriteLogLine0("Firma018");

			AmTesiSign_Finalize();

			CLogFileWriter::Get()->WriteLogLine0("Firma019");

			if (lIdPdf > 0)
			{
				// inserisco una riga nella tabella EXT_ESAMI_CHIUSI //
				CEsamiChiusiSet().InserisciRecord(m_pEsamiSet->m_lContatore, lIdPdf, -1, GetUserIDForLockSuperlock(), "NW");

				// chiudo l'esame //
				m_pEsamiSet->ChiudiEsame(m_sDataOraChiusura, (CRefertoForm*)m_pDynForm[sub_referto]);

				// archivio su pacs //
				CPacsArchiver pa;
				pa.Archive(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore, lIdPdf);

				// aggiorno l'interfaccia //
				UpdateData(FALSE);
			}
		}
		else
		{
			OnCommandMenuGestioneVisualizzaStampe(TRUE);
		}

		return;
		break;
	}
	}

	EndWaitCursor();
	// <-- Davide/Sandro - Firma digitale
}

void CEsamiView::OnToolbarStampaReportMacro()
{
	// Sandro 29/09/2016 // RIMA 16037 Fleury //

	BOOL bStampa = TRUE;

	CString sMessaggio = "";
	if (theApp.m_bPersonalizzazioniBrasileFleury)
		if (m_pEsamiSet->m_bSuperLocked)
			bStampa = FleuryPossoStampare(sMessaggio, m_pEsamiSet->m_sRicovero, m_pEsamiSet->m_sCodEsame);

	if (!bStampa)
	{
		theApp.AfxMessageBoxEndo(sMessaggio);
		return;
	}

	// Sandro 27/02/2014 // richiesta Paron Pilotto //
	if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
	{
		if (m_pEsamiSet->m_bSuperLocked != TRUE)
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAME_NON_CHIUSO));
			return;
		}
	}

	// controllo di essere in visualizzazione //
	if (theApp.m_nProgramMode != NOTHING_MODE)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_SAVE_BEFORE_PRINT));
		return;
	}

	// controllo se l'esame fa parte del mio distretto //
	if (!m_pEsamiSet->m_bStessoDistretto)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_REFERTO_NOTPRINTABLE));
		return;
	}

	// controllo se tutti i campi obbligatori sono validi //
	if (!VerificaCampiObbligatoriFase(CO_FASE_CHIUSURA_STAMPA))
		return;

	CReportsMacroUseDlg dlg(this);
	if (dlg.DoModal() == IDOK)
	{
		CString strFilter;
		strFilter.Format("IDMacro=%li", dlg.GetIDMacro());

		CReportsMacroDettSet setReports;
		setReports.SetOpenFilter(strFilter);
		setReports.SetSortRecord("ID");
		if (setReports.OpenRecordset("CEsamiView::OnToolbarStampaReportMacro"))
		{
			CList<STRUCT_STAMPA_CUMULATIVA> listStampaCumulativa;

			CString sReportDaFirmare = CReportsMacroSet().GetReportDaFirmare(dlg.GetIDMacro());

			while (!setReports.IsEOF())
			{
				if (!setReports.m_sReport.IsEmpty())
				{
					// Sandro 30/04/2014 //

					CString sReportTemp = "";

					int n1 = setReports.m_sReport.ReverseFind('\\');
					int n2 = setReports.m_sReport.ReverseFind('.');

					if ((n1 > 0) && (n2 > n1))
						sReportTemp = setReports.m_sReport.Mid(n1 + 1, (n2 - n1) - 1);
					else
						sReportTemp = setReports.m_sReport;

					if ((theApp.m_enumFirmaDigitale != CEndoxApp::sign_disabled) && !sReportDaFirmare.IsEmpty() && !sReportTemp.IsEmpty() && (sReportDaFirmare.CompareNoCase(sReportTemp) == 0) && !m_pEsamiSet->m_bSuperLocked)
					{
						// firma digitale //
						OnToolbarStampaReportFirmaDigitale(setReports.m_sReport, setReports.m_lCopie);
					}
					else
					{
						// stampa "normale" //
						STRUCT_STAMPA structStampa;
						if (SelezionaFileReport(&structStampa, setReports.m_sReport))
						{
							//
							BeginWaitCursor();

							m_listIDStampate.RemoveAll();

							CString sPdfFileComplete = "";
							if (CreateHaruPdfReportFile(sPdfFileComplete, &structStampa, FALSE, ""))
							{
								// se necessario archivio la copia del pdf //

								if (structStampa.m_bArchivePDFCopy)
									ArchiviaPdf(pdftype_report, &sPdfFileComplete, structStampa.m_sReportFileOriginal, FALSE, FALSE, structStampa.m_bFitToPage, 0, 0);

								// contrassegno le immagini stampate //

								if (m_listIDStampate.GetCount() > 0)
									m_pImgManager->SetPrintedImages(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, theApp.m_bSalvaSoloUltimeImmaginiStampate, &m_listIDStampate);

								// aggiungo il pdf in coda di stampa cumulativa //

								STRUCT_STAMPA_CUMULATIVA ssc;
								ssc.m_sRptFile = structStampa.m_sReportFileOriginal;
								ssc.m_sPdfFile = sPdfFileComplete;
								ssc.m_lPrinterToUse = structStampa.m_lPrinterToUse;
								ssc.m_lCopies = setReports.m_lCopie;
								ssc.m_bFitToPage = structStampa.m_bFitToPage;

								listStampaCumulativa.AddTail(ssc);
							}
							m_listIDStampate.RemoveAll();

							//
							EndWaitCursor();
						}
					}
				}

				setReports.MoveNext();
			}

			setReports.CloseRecordset("CEsamiView::OnToolbarStampaReportMacro");

			// Sandro 01/04/2015 // RIMA 15008 //

			POSITION pos = listStampaCumulativa.GetHeadPosition();
			while (pos != NULL)
			{
				// prima stampo tutti i reports senza una stampante predefinita associata //

				STRUCT_STAMPA_CUMULATIVA ssc = listStampaCumulativa.GetNext(pos);

				if (ssc.m_lPrinterToUse == 0)
				{
					CPdfStampaDlg(this, ssc.m_sRptFile, ssc.m_sPdfFile, FALSE, 0, ssc.m_lCopies, ssc.m_bFitToPage).DoModal();
					DeleteFile(ssc.m_sPdfFile);
				}
			}

			for (int i = 1; i < 10; i++)
			{
				// per ognuna delle 9 stampanti predefinite, mi creo una lista dei reports da accorpare, tenendo in considerazione anche il numero di copie da stampare //

				CStringList listPdfInputFiles;

				POSITION pos = listStampaCumulativa.GetHeadPosition();
				while (pos != NULL)
				{
					STRUCT_STAMPA_CUMULATIVA ssc = listStampaCumulativa.GetNext(pos);

					if (ssc.m_lPrinterToUse == i)
					{
						if (ssc.m_lCopies <= 0)
						{
							CNumeroCopieStampaDlg dlgTemp(this, ssc.m_sRptFile);
							if (dlgTemp.DoModal() == IDOK)
								for (int j = 0; j < dlgTemp.GetNumeroCopie(); j++)
									listPdfInputFiles.AddTail(ssc.m_sPdfFile);
						}
						else
						{
							for (int j = 0; j < ssc.m_lCopies; j++)
								listPdfInputFiles.AddTail(ssc.m_sPdfFile);
						}
					}
				}

				// se ci sono reports da stampare su questa stampante predefinita procedo //

				if (listPdfInputFiles.GetCount() > 0)
				{
					SYSTEMTIME timeLocal;
					::GetLocalTime(&timeLocal);

					CString sFinalFileName;
					sFinalFileName.Format("%s\\%02d_%04d%02d%02d%02d%02d%02d.pdf", theApp.m_sDirTemp, i, timeLocal.wYear, timeLocal.wMonth, timeLocal.wDay, timeLocal.wHour, timeLocal.wMinute, timeLocal.wSecond);

					// accorpo tutto all'interno di un unico grande pdf //

					if (CPdfUtilInterface::Get()->Merge(&listPdfInputFiles, sFinalFileName))
					{
						// stampo l'unico grande pdf //

#ifdef _DEBUG
						CPdfAnteprimaDlg(this, this, sFinalFileName, ANTEPRIMADLG_SEMPLICE).DoModal();
#else
						CPdfStampaDlg(this, "", sFinalFileName, FALSE, i, 1, FALSE).DoModal();
#endif
					}

					// cancello i file dei "pdf singoli" //

					POSITION posTmp = listPdfInputFiles.GetHeadPosition();
					while (posTmp != NULL)
					{
						CString sFileToDelete = listPdfInputFiles.GetNext(posTmp);
						DeleteFile(sFileToDelete);
					}

					// cancello il file del "pdf cumulativo" //

					DeleteFile(sFinalFileName);
				}
			}
		}

		// Sandro 05/02/2014 // stampo anche le immagini, se necessario //
		long lStampaImmaginiCopie = CReportsMacroSet().GetImmaginiCopie(dlg.GetIDMacro());
		if (lStampaImmaginiCopie >= 0) // valore negativo --> no stampa; 0 --> chiede quante copie; valore positivo --> numero di copie da stampare //
			AnteprimaStampaImmagini(STAMPA, LOCAL_IMAGES, lStampaImmaginiCopie);

		// Sandro 19/09/2013 // RAS 20130099 //
		long lStampaEtichetteIstopatologiaCopie = CReportsMacroSet().GetEtichetteIstopatologiaCopie(dlg.GetIDMacro());
		if (lStampaEtichetteIstopatologiaCopie >= 0) // negativo --> no stampa; 0 --> chiede quante copie; positivo --> numero di copie da stampare //
		{
			if (m_pDynForm[sub_anatomiapatologica] != NULL)
			{
				CAnatomiaPatologicaForm* pAnatomiaPatologicaForm = (CAnatomiaPatologicaForm*)m_pDynForm[sub_anatomiapatologica];
				pAnatomiaPatologicaForm->StampaTutteLeRighe();
			}

			if (m_pDynForm[sub_istopatologia] != NULL)
			{
				CIstologiaTotForm* pIstologiaTotForm = (CIstologiaTotForm*)m_pDynForm[sub_istopatologia];
				pIstologiaTotForm->StampaTutteLeRighe();
			}

			if (m_pDynForm[sub_istopatologia5righe] != NULL)
			{
				CIstologiaTotForm5Righe* pIstologiaTotForm5Righe = (CIstologiaTotForm5Righe*)m_pDynForm[sub_istopatologia5righe];
				pIstologiaTotForm5Righe->StampaTutteLeRighe();
			}

			if (m_pDynForm[sub_istopatologia5righe_plus] != NULL)
			{
				CIstologiaTotForm5RighePlus* pIstologiaTotForm5RighePlus = (CIstologiaTotForm5RighePlus*)m_pDynForm[sub_istopatologia5righe_plus];
				pIstologiaTotForm5RighePlus->StampaTutteLeRighe();
			}
		}
	}

	// Sandro 02/04/2015 // per sicurezza faccio un altro giro per cancellare tutti i pdf //
	CPdfUtilInterface::Get()->DeleteAllPdf(theApp.m_sDirTemp);

	// Sandro 07/03/2011 // deseleziono le immagini //
	if (theApp.m_bAutoDeselect)
		CFileBmp::DeleteListSelected(LOCAL_IMAGES);

	// Sandro 26/11/2013 // devo refreshare l'album, ora che contrassegno le immagini stampate //
	m_pFormImmagini->SendMessage(MSG_AFTER_ELABIMAGE, (WPARAM)FALSE);
}

LRESULT CEsamiView::OnDestroyQueryWnd(WPARAM, LPARAM)
{
	if (m_pQueryDlg)
	{
		if (m_pQueryDlg->GetSafeHwnd())
			m_pQueryDlg->DestroyWindow();

		delete m_pQueryDlg;
		m_pQueryDlg = NULL;
	}

	return 0;
}

LRESULT CEsamiView::OnHideQueryWnd(WPARAM, LPARAM)
{
	if (m_pQueryDlg)
		m_pQueryDlg->ShowWindow(SW_HIDE);

	return 1;
}

LRESULT CEsamiView::OnDestroySospesiIstologiciWnd(WPARAM, LPARAM)
{
	if (m_pSospesiIstologiciDlg)
	{
		if (m_pSospesiIstologiciDlg->GetSafeHwnd())
			m_pSospesiIstologiciDlg->DestroyWindow();

		delete m_pSospesiIstologiciDlg;
		m_pSospesiIstologiciDlg = NULL;
	}

	return 0;
}

LRESULT CEsamiView::OnHideSospesiIstologiciWnd(WPARAM, LPARAM)
{
	if (m_pSospesiIstologiciDlg)
		m_pSospesiIstologiciDlg->ShowWindow(SW_HIDE);

	return 1;
}

LRESULT CEsamiView::OnReloadQueryWnd(WPARAM, LPARAM)
{
	OnHideQueryWnd(NULL, NULL);
	OnApplicaQuery();

	return 0;
}

UINT CEsamiView::CopyImagesFromRemotePath(LPVOID pParam)
{
	CEsamiView* pEsamiView = (CEsamiView*)pParam;

	if (FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)))
		return 0;

	// visualizzo la barra di avanzamento //
	int nPos = 0;
	pEsamiView->SendMessage(EPM_THREAD_IMPORT_SETPOS, nPos, 0);

	//

	CList<tagRemoteFile> listFiles;
	pEsamiView->m_pImgManager->GetRemoteFilesPathList(&listFiles);

	int iNumFileActual = 0;
	int iNumFilesTotal = listFiles.GetCount();

	POSITION pos = listFiles.GetHeadPosition();
	while (pos != NULL)
	{
		tagRemoteFile tagTemp = listFiles.GetAt(pos);

		int iLastSlashLocaleMin = tagTemp.sLocalFileMin.ReverseFind('\\');
		if (iLastSlashLocaleMin > 0)
		{
			CString sPathLocaleMin = tagTemp.sLocalFileMin.Left(iLastSlashLocaleMin);
			if (VerificaPercorso(sPathLocaleMin, FALSE))
			{
				if (CopyFile(tagTemp.sRemoteFileMin, tagTemp.sLocalFileMin, FALSE))
				{
					//Julio 4/12/2017 nao importar imm automaticamente
					/*int iLastSlashLocaleImm = tagTemp.sLocalFileImm.ReverseFind('\\');
					if (iLastSlashLocaleImm > 0)
					{
					CString sPathLocaleImm = tagTemp.sLocalFileImm.Left(iLastSlashLocaleImm);
					if (VerificaPercorso(sPathLocaleImm, FALSE))
					{
					if (CopyFile(tagTemp.sRemoteFileImm, tagTemp.sLocalFileImm, FALSE))
					pEsamiView->m_pImgManager->SetImmagineDiscoH(tagTemp.lID);
					}
					}*/
				}
			}
		}

		// aggiorno lo stato di avanzamento //
		iNumFileActual++;
		nPos = (int)((((double)iNumFileActual / (double)iNumFilesTotal) * (double)100) + (double)0.5);
		pEsamiView->SendMessage(EPM_THREAD_IMPORT_SETPOS, (WPARAM)nPos, 0);

		//
		listFiles.GetNext(pos);
	}

	//

	if (nPos < 100)
		pEsamiView->SendMessage(EPM_THREAD_IMPORT_SETPOS, (WPARAM)100, 0);

	//

	::CoUninitialize();

	return 0;
}

LRESULT CEsamiView::OnThreadImportSetPos(WPARAM wParam, LPARAM lParam)
{
	int nPos = (int)wParam;

	if (nPos <= 0)
	{
		m_bImporting = TRUE;

		m_ctrlProgressImport.SetRange32(0, 100);
		m_ctrlProgressImport.SetPos(0);

		GetDlgItem(IDC_LABEL_STATO_NEW4)->ShowWindow(SW_HIDE);
		m_ctrlProgressImport.ShowWindow(SW_SHOW);
	}
	else if (nPos >= 100)
	{
		m_ctrlProgressImport.SetPos(100);
		Sleep(1000);

		m_ctrlProgressImport.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LABEL_STATO_NEW4)->ShowWindow(SW_SHOW);

		m_bImporting = FALSE;
	}
	else
	{
		m_ctrlProgressImport.SetPos(nPos);
	}

	if (m_pFormImmagini != NULL)
		m_pFormImmagini->AfterMoveEsame(FALSE, TRUE);

	return 0;
}

LRESULT CEsamiView::OnThreadRimageSetPos(WPARAM wParam, LPARAM lParam)
{
	int nPos = (int)wParam;

	if (nPos <= 0)
	{
		m_bBurning = TRUE;

		m_ctrlProgressImport.SetRange32(0, 100);
		m_ctrlProgressImport.SetPos(0);

		GetDlgItem(IDC_LABEL_STATO_NEW4)->ShowWindow(SW_HIDE);
		m_ctrlProgressImport.ShowWindow(SW_SHOW);
	}
	else if (nPos >= 100)
	{
		m_ctrlProgressImport.SetPos(100);
		Sleep(1000);

		m_ctrlProgressImport.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LABEL_STATO_NEW4)->ShowWindow(SW_SHOW);

		m_bBurning = FALSE;
	}
	else
	{
		m_ctrlProgressImport.SetPos(nPos);
	}

	/*if (m_pFormImmagini != NULL)
	m_pFormImmagini->AfterMoveEsame(FALSE, TRUE);*/

	return 0;
}

LRESULT CEsamiView::OnThreadRimageOn(WPARAM wParam, LPARAM lParam)
{
	m_bRimage = TRUE;

	return 0;
}

LRESULT CEsamiView::OnThreadRimageOff(WPARAM wParam, LPARAM lParam)
{
	m_bRimage = FALSE;

	return 0;
}

void CEsamiView::InitToolbar()
{
	if (m_pPatientBar != NULL)
	{
		delete m_pPatientBar;
		m_pPatientBar = NULL;
	}

	if (!theApp.m_bCentraleStampa)
	{
		m_pPatientBar = new CEndoxBar();
		if (theApp.m_bPersonalizzazioniBrasileSirio)
			m_pPatientBar->CreateEx(this, GetDlgItem(IDC_BAR_PAZIENTE), IDR_BAR_PAZIENTE_AA, IDB_BAR_PAZIENTE_BR, IDB_BAR_PAZIENTE_BR_UP, IDB_BAR_PAZIENTE_BR_BW);
		else if (theApp.m_bMenuUsaCarestreamExamesPendentes)
		{
			if (theApp.m_bMenuUsaTextboxBuscaExame)
				m_pPatientBar->CreateEx(this, GetDlgItem(IDC_BAR_PAZIENTE), IDR_BAR_PAZIENTE_AA, IDB_BAR_PAZIENTE_FL, IDB_BAR_PAZIENTE_FL_UP, IDB_BAR_PAZIENTE_FL_BW);
			else
				m_pPatientBar->CreateEx(this, GetDlgItem(IDC_BAR_PAZIENTE), IDR_BAR_PAZIENTE_AA, IDB_BAR_PAZIENTE_PEP, IDB_BAR_PAZIENTE_PEP_UP, IDB_BAR_PAZIENTE_AA_BW);
		}
		else
			m_pPatientBar->CreateEx(this, GetDlgItem(IDC_BAR_PAZIENTE), IDR_BAR_PAZIENTE_AA, IDB_BAR_PAZIENTE_AA, IDB_BAR_PAZIENTE_AA_UP, IDB_BAR_PAZIENTE_AA_BW);

		long lRemovedButtons = 0;
		if (theApp.m_sAgendaIndex.IsEmpty())
		{
			m_pPatientBar->DeleteButton(IDC_PAZIENTE_PRENOTAZIONE);
			lRemovedButtons++;
		}
		if (theApp.m_nInterfacciaPrenotazione == CEndoxApp::prenotazioni_none)
		{
			m_pPatientBar->DeleteButton(IDC_LISTA_PRENOTAZIONI);
			lRemovedButtons++;
		}
		m_lNumDocumentsPatientOffset = -(43 * lRemovedButtons);
	}

	//

	if (m_pExamBar != NULL)
	{
		delete m_pExamBar;
		m_pExamBar = NULL;
	}

	if (!theApp.m_bCentraleStampa)
	{
		m_pExamBar = new CEndoxBar();
		if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury)
		{
			m_pExamBar->CreateEx(this, GetDlgItem(IDC_BAR_ESAME), IDR_BAR_ESAME_FL, IDB_BAR_ESAME_FL, IDB_BAR_ESAME_FL_UP, IDB_BAR_ESAME_FL_BW);
			m_lNumDocumentsExamOffset = -39;
			m_lNumDocumentsExamCarestreamOffset = 0;

			// #ifndef _DEBUG
			if (GetSystemMetrics(SM_CYSCREEN) < 800)
				// #endif
			{
				m_pExamBar->DeleteButton(IDC_ESAME_FIRST);
				m_lNumDocumentsExamOffset = -78;
				m_lNumDocumentsExamCarestreamOffset = -39;
			}
		}
		else
		{
			m_pExamBar->CreateEx(this, GetDlgItem(IDC_BAR_ESAME), IDR_BAR_ESAME_AA, IDB_BAR_ESAME_AA, IDB_BAR_ESAME_AA_UP, IDB_BAR_ESAME_AA_BW);
		}
	}

	//

	if (!theApp.m_bPersonalizzazioniBrasileFleury)
	{
		m_pPatientBar->DeleteButton(IDC_FICHA);
		m_pPatientBar->DeleteButton(IDC_FICHA2);
		m_pPatientBar->DeleteButton(IDC_ASSESSORIA);
	}
	if (theApp.m_bMenuUsaTextboxBuscaExame)
	{
		GetDlgItem(IDC_EDIT_FLEURYFICHA)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_FLEURYFICHA)->SetFont(&theApp.m_fontBig, TRUE);
		GetDlgItem(IDC_EDIT_FLEURYITEM)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_FLEURYITEM)->SetFont(&theApp.m_fontBig, TRUE);
	}

	//Julio Este botão serve somente para teste
	m_pPatientBar->DeleteButton(IDC_FICHA2);
}

void CEsamiView::OnSize(UINT nType, int cx, int cy)
{
	CResizableFormView::OnSize(nType, cx, cy);

	// Sandro 11/07/2013 // ridisegno tabctrl con problemi da VS2012 //
	if (IsWindow(m_ctrlGruppoEsame))
	{
		CRect rectTemp;
		GetDlgItem(IDC_FRAME_GRUPPO_ESAME)->GetWindowRect(&rectTemp);
		// m_ctrlGruppoEsame.SetWindowPos(NULL, 0, 0, rectTemp.Width(), rectTemp.Height(), SWP_NOMOVE | SWP_NOZORDER);

		ScreenToClient(rectTemp);
		m_ctrlGruppoEsame.SetWindowPos(NULL, rectTemp.left, rectTemp.top, rectTemp.Width(), rectTemp.Height(), SWP_NOZORDER);
	}
	//

	if (m_pFormImmagini)
		m_pFormImmagini->SendMessage(EPM_RESIZE_FORM);

	for (int i = 0; i < form_list_total; i++)
		if (m_pDynForm[i] != NULL)
			m_pDynForm[i]->SendMessage(EPM_RESIZE_FORM);
}

void CEsamiView::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 0xEEE:
	{
		KillTimer(0xEEE);

		if (theApp.m_bSaveCompleteLog)
		{
			if (!theApp.m_sSaveCompleteLogIpDb.IsEmpty())
				CLogFileWriter::Get()->WriteLogLine0_Ping(theApp.m_sSaveCompleteLogIpDb);

			if (!theApp.m_sSaveCompleteLogIpImm.IsEmpty())
				CLogFileWriter::Get()->WriteLogLine0_Ping(theApp.m_sSaveCompleteLogIpImm);
		}

		SetTimer(0xEEE, 5000, NULL);

		break;
	}
	case TIMER_CHECK_MONITORAGGIO:
		CheckMonitoraggioInCorso();
		break;
	}
}

BOOL CEsamiView::FiltraEsami()
{
	BOOL bError = FALSE;

	CString strFilter;
	strFilter.Format("Paziente=%li", m_pPazientiSet->m_lContatore);

	m_pEsamiSet->CloseRecordset("CEsamiView::FiltraEsami");
	m_pEsamiSet->SetOpenFilter(strFilter);
	m_pEsamiSet->OpenRecordset("CEsamiView::FiltraEsami");

	if (!m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
	{
		CString strQuery;
		strQuery.Format("SELECT COUNT(*) AS CONTEGGIO FROM EESAMI WHERE (%s) AND (%s)",
			m_pEsamiSet->GetOpenFilter(),
			m_pEsamiSet->GetBaseFilter());
		CRecordset set(&theApp.m_dbEndox);
		set.Open(CRecordset::snapshot, strQuery, CRecordset::readOnly);
		if (!set.IsEOF())
		{
			CString strCount;
			set.GetFieldValue("CONTEGGIO", strCount);
			m_pPazientiSet->m_lTotEsami = atol(strCount);
		}
		set.Close();
	}
	else
	{
		m_pPazientiSet->m_lTotEsami = 0;
	}

	return bError;
}

BOOL CEsamiView::SaveEsami()
{
	m_pEsamiSet->RefreshRecordset();

	if (m_pEsamiSet->EditRecordset("CEsamiView::SaveEsami"))
	{
		long lIDEsameOLD = m_pEsamiSet->m_lIDEsame;
		UpdateData(TRUE);
		long lIDEsameNEW = m_pEsamiSet->m_lIDEsame;

		// Sandro 04/05/2012 // l'utente ha cambiato il tipo di esame... forse devo modificare anche IDVersione (interfaccia operatore) e ProgressivoAnno //
		if (lIDEsameOLD != lIDEsameNEW)
		{
			CCambiaVersioneProgressivoAnnoDlg dlgCVPA(this, lIDEsameOLD, lIDEsameNEW, m_pEsamiSet->m_lIDVersione, m_pEsamiSet->m_sProgressivoAnno);
			dlgCVPA.DoModal();

			m_pEsamiSet->m_lIDVersione = dlgCVPA.GetNewIDVersione();
			m_pEsamiSet->m_sProgressivoAnno = dlgCVPA.GetNewProgressivoAnno();
		}

		if (!m_pEsamiSet->UpdateRecordset("CEsamiView::SaveEsami"))
		{
			m_pEsamiSet->NoEditRecordset("CEsamiView::SaveEsami");
			return FALSE;
		}
	}

	return TRUE;
}

void CEsamiView::CaricaInterfaccia(long lVersione)
{
	// se sono in visualizzazione remota, il cambio di paziente o esame deve oscurare lo schermo remoto //
	if (theApp.m_bVisAbilita)
	{
		HMODULE hModule;
#ifdef _DEBUG
		hModule = ::LoadLibrary("xrclientd.dll");
#else
		hModule = ::LoadLibrary("xrclient.dll");
#endif

		// XRClient //
		STOPPLAYPTR XRClient_StopPlay;
		ENABLEVIDEOOUTPUTPTR XRClient_EnableVideoOutput;
		GETERROROCCURREDPTR XRClient_GetErrorOccurred;

		if (hModule)
		{
			XRClient_StopPlay = (STOPPLAYPTR)GetProcAddress(hModule, "StopPlay");
			XRClient_GetErrorOccurred = (GETERROROCCURREDPTR)GetProcAddress(hModule, "GetErrorOccurred");
			XRClient_EnableVideoOutput = (ENABLEVIDEOOUTPUTPTR)GetProcAddress(hModule, "EnableVideoOutput");
		}

		if (theApp.m_iPrevInput > 0)
		{
			if (theApp.m_bVisAbilitaMonitor && XRClient_EnableVideoOutput && !XRClient_EnableVideoOutput(theApp.m_sVisPortaMonitor, theApp.m_iPrevInput))
			{
				TCHAR szError[2048];
				ZeroMemory(szError, sizeof(char) * 2048);
				XRClient_GetErrorOccurred(szError);
				CString sError;
				sError.Format(theApp.GetMessageString(IDS_ERRORE_REMOTO), szError);
				theApp.AfxMessageBoxEndo(sError);
			}
		}

		if (hModule)
			FreeLibrary(hModule);
	}

	// --- //

	theApp.m_bLoadingInterface = TRUE;

	BeginWaitCursor();

	// Sandro 07/01/2013 // RAS 20120185 //

	if (!m_pEsamiSet->m_bStessoDistretto)
		if (CTipoEsameSet().IsPrivato(m_pEsamiSet->m_lIDEsame))
			lVersione = -1;

	//

	if (lVersione != m_lPrevVers)
	{
		m_lPrevVers = lVersione;

		m_ctrlGruppoEsame.DeleteAllItems();
		m_ctrlBtnHide.ShowWindow(SW_HIDE);
		m_ctrlBtnShow.ShowWindow(SW_HIDE);

		if (lVersione > 0)
		{
			CString sFilter;
			sFilter.Format("IDVersione=%li", lVersione);

			CDynFormSet setDynForm;
			setDynForm.SetOpenFilter(sFilter);
			if (setDynForm.OpenRecordset("CEsamiView::CaricaInterfaccia"))
			{
				while (setDynForm.IsEOF() == FALSE)
				{
					if (theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_03)
					{
						m_ctrlGruppoEsame.InsertItem(setDynForm.m_sNome, setDynForm.m_lID, setDynForm.m_lAlbum);
					}
					else
					{
						if (setDynForm.m_bVisualizzaSempre)
							m_ctrlGruppoEsame.InsertItem(setDynForm.m_sNome, setDynForm.m_lID, setDynForm.m_lAlbum);
					}

					setDynForm.MoveNext();
				}

				setDynForm.CloseRecordset("CEsamiView::CaricaInterfaccia");
			}
		}

		if (m_ctrlGruppoEsame.GetItemCount() > 0)
		{
			m_ctrlGruppoEsame.SetCurSel(0);
			m_ctrlGruppoEsame.MostraSubform();
		}
	}
	else
	{
		// Sandro 14/12/2015 // RIMA 15135 //

		if (m_bVisualizzaTastoCaricaImmagini)
		{
			if (m_ctrlGruppoEsame.GetItemCount() > 0)
				m_ctrlGruppoEsame.MostraSubform();
		}
	}

	//EvidenziaCampiObbligatori();
	EvidenziaCampiObbligatoriFasi(); //Evidenzia i campi obbligatori per le nuove fasi

	//

	EndWaitCursor();

	theApp.m_bLoadingInterface = FALSE;
}

void CEsamiView::OnEsameNewAuto(long lIDTipoEsame, long lIDPrenotazione)
{
	m_lIDTipoEsameAutoInsert = lIDTipoEsame;
	m_lIDPrenotazione = lIDPrenotazione;
	OnEsameNew();
	m_lIDTipoEsameAutoInsert = -1;
}

void CEsamiView::OnEsameNewAutoCup(long lIDTipoEsame, long lIDPrenotazione)
{
	m_lIDTipoEsameAutoInsert = lIDTipoEsame;
	m_lIDPrenotazione = lIDPrenotazione;
	OnEsameNewCup();
	m_lIDTipoEsameAutoInsert = -1;
}

void CEsamiView::InserisciNuovoMonitoraggio()
{
	OnEsameModify();

	CMonitoraggioBaseDynForm* m_pMonitoraggioDynForm = NULL;

	if (m_pDynForm[sub_monitoraggio_oriz] != NULL)
		m_pMonitoraggioDynForm = (CMonitoraggioBaseDynForm*)m_pDynForm[sub_monitoraggio_oriz];

	if (m_pDynForm[sub_monitoraggio_vert] != NULL)
		m_pMonitoraggioDynForm = (CMonitoraggioBaseDynForm*)m_pDynForm[sub_monitoraggio_vert];

	if (m_pMonitoraggioDynForm)
		m_pMonitoraggioDynForm->AggiungiRiga();

	OnEsameUpdate();
}

void CEsamiView::InserisciNuovaProvetta()
{
	CAnatomiaPatologicaDlg dlg(this, this);
	dlg.DoModal();
}

void CEsamiView::OnBnClickedBtnShow()
{
	m_ctrlBtnShow.SetCheck(BST_UNCHECKED);
	m_ctrlBtnShow.ShowWindow(SW_HIDE);

	if (m_pFormImmagini != NULL)
	{
		CBaseForm* pForm = m_ctrlGruppoEsame.GetSelectedBaseForm();
		if (pForm != NULL)
		{
			// nascondo i controlli nella zona dell'album //
			POSITION pos = pForm->m_listControls.GetHeadPosition();
			while (pos != NULL)
			{
				CEndoxStatic* pStatic = pForm->m_listControls.GetAt(pos);

				if (pStatic->m_bOnAlbumZone)
					pStatic->ShowWindow(SW_HIDE);

				pForm->m_listControls.GetNext(pos);
			}

			// ridimensiono il form portandolo alla dimensione di m_ctrlSubFormEsame //
			CRect rectTemp;
			m_ctrlSubFormEsame.GetWindowRect(rectTemp);
			pForm->m_bLockResize = TRUE;
			pForm->SetWindowPos(NULL, 0, 0, rectTemp.Width(), rectTemp.Height(), SWP_NOMOVE | SWP_NOZORDER);
			pForm->m_pParentFrame = &m_ctrlSubFormEsame;
			pForm->m_bLockResize = FALSE;

			// mostro l'album delle immagini //
			m_pFormImmagini->ShowWindow(SW_SHOW);

			// cambio lo stato di visualizzazione dell'album nel form //
			pForm->InvertShowAlbumState();
		}
	}

	m_ctrlBtnHide.SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	m_ctrlBtnHide.ShowWindow(SW_SHOW);

	if (m_bVisualizzaTastoCaricaImmagini)
	{
		m_ctrlBtnImmagini.ShowWindow(SW_SHOW);
		m_ctrlBtnImmagini.SetWindowPos(&this->wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	}
	else
	{
		m_ctrlBtnImmagini.ShowWindow(SW_HIDE);
	}
}

void CEsamiView::OnBnClickedBtnHide()
{
	m_ctrlBtnHide.SetCheck(BST_UNCHECKED);
	m_ctrlBtnHide.ShowWindow(SW_HIDE);

	if (m_pFormImmagini != NULL)
	{
		CBaseForm* pForm = m_ctrlGruppoEsame.GetSelectedBaseForm();
		if (pForm != NULL)
		{
			// mostro i controlli nella zona dell'album //
			POSITION pos = pForm->m_listControls.GetHeadPosition();
			while (pos != NULL)
			{
				CEndoxStatic* pStatic = pForm->m_listControls.GetAt(pos);

				if (pStatic->m_bOnAlbumZone)
					pStatic->ShowWindow(SW_SHOW);

				pForm->m_listControls.GetNext(pos);
			}

			// ridimensiono il form portandolo alla dimensione di m_ctrlSubForm3 //
			CRect rectTemp;
			m_ctrlSubForm3.GetWindowRect(rectTemp);
			pForm->m_bLockResize = TRUE;
			pForm->SetWindowPos(NULL, 0, 0, rectTemp.Width(), rectTemp.Height(), SWP_NOMOVE | SWP_NOZORDER);
			pForm->m_pParentFrame = &m_ctrlSubForm3;
			pForm->m_bLockResize = FALSE;

			// nascondo l'album delle immagini //
			m_pFormImmagini->ShowWindow(SW_HIDE);

			// cambio lo stato di visualizzazione dell'album nel form //
			pForm->InvertShowAlbumState();
		}
	}

	m_ctrlBtnShow.SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	m_ctrlBtnShow.ShowWindow(SW_SHOW);

	m_ctrlBtnImmagini.ShowWindow(SW_HIDE);
}

void CEsamiView::OnBnClickedBtnImmagini()
{
	BeginWaitCursor();
	m_ctrlBtnImmagini.SetCheck(BST_UNCHECKED);

	m_bVisualizzaTastoCaricaImmagini = FALSE;
	m_ctrlBtnImmagini.ShowWindow(SW_HIDE);

	if (m_pFormImmagini)
		m_pFormImmagini->AfterMoveEsame();

	EndWaitCursor();
}

HANDLE CEsamiView::CopyHandle(HANDLE h)
{
	// Return a handle to a copy of the data
	// that the passed handle was for.
	if (!h) return NULL;
	DWORD   dwLen = GlobalSize(h);
	HANDLE hCopy = GlobalAlloc(GHND, dwLen);
	if (hCopy)
	{
		BYTE* lpCopy = (BYTE*)GlobalLock(hCopy);
		BYTE* lp = (BYTE*)GlobalLock(h);
		CopyMemory(lpCopy, lp, dwLen);
		GlobalUnlock(hCopy);
		GlobalUnlock(h);
	}
	return hCopy;
}

BOOL CEsamiView::SelezionaFileReport(STRUCT_STAMPA* pStruct)
{
	BOOL bReturn = FALSE;

	CFileDialog FileDlg(TRUE, NULL, NULL, OFN_READONLY | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, "Report (*.rpt)|*.rpt|Tutti i file|*.*|", this, 0, FALSE);
	FileDlg.GetOFN().lpstrInitialDir = theApp.m_sEditRep;
	if (FileDlg.DoModal() == IDOK)
		bReturn = SelezionaFileReport(pStruct, FileDlg.GetPathName());

	return bReturn;
}

BOOL CEsamiView::SelezionaFileReport(STRUCT_STAMPA* pStruct, CString sFile)
{
	BOOL bReturn = FALSE;

	pStruct->m_bArchivePDFCopy = FALSE;
	pStruct->m_lImagePrinting = 0;
	pStruct->m_lImageToPrint = 0;
	pStruct->m_lOrganPrinting = 0;
	pStruct->m_lOrganToPrint = 0;
	pStruct->m_lPrinterToUse = Printer_ChiediStampante;
	pStruct->m_bFitToPage = FALSE;
	pStruct->m_listImmaginiStampa.RemoveAll();
	pStruct->m_listPuntiStampa.RemoveAll();
	pStruct->m_sReportFileOriginal = sFile;
	pStruct->m_sReportFilePrinting = sFile;

	// controllo che il file sia accessibile e leggibile //
	if (_access(pStruct->m_sReportFileOriginal, 04) == 0)
	{
		// se necessario salvo il percorso del file utilizzato //
		if (!theApp.m_bCheckRep)
		{
			int iLastSlash = pStruct->m_sReportFileOriginal.ReverseFind('\\');

			if (iLastSlash > -1)
			{
				theApp.m_sEditRep = pStruct->m_sReportFileOriginal.Left(iLastSlash);
				WritePrivateProfileString(szPercorsi, szEditRep, theApp.m_sEditRep, theApp.m_sFileConfig);
			}
		}

		// provo a copiare il report in locale per velocizzare le operazioni di anteprima e stampa //
		if (pStruct->m_sReportFileOriginal.CompareNoCase(theApp.m_sDirTemp + "\\temp.rpx") != 0)
		{
			DeleteFile(theApp.m_sDirTemp + "\\temp.rpx");
			if (CopyFile(pStruct->m_sReportFileOriginal, theApp.m_sDirTemp + "\\temp.rpx", TRUE))
				pStruct->m_sReportFilePrinting = theApp.m_sDirTemp + "\\temp.rpx";
		}

		// leggo dal report se devo creare anche la copia PDF //
		pStruct->m_bArchivePDFCopy = (BOOL)GetPrivateProfileInt("Page", "CopiaPDF", 0, pStruct->m_sReportFilePrinting);

		// Sandro 26/11/2013 //
		if ((m_pFormImmagini != NULL) && (CFileBmp::CountPrinterList(LOCAL_IMAGES) == 0) && theApp.m_bStampaSelezionaAutomaticaImmaginiStampate)
			m_pFormImmagini->SelectAlreadyPrintedImages();

		// leggo dal report il numero di immagini contenute e riempio la lista CFileBmp::m_listPrinter //
		long lImmTemp = ContaImmagini(pStruct->m_sReportFilePrinting);
		pStruct->m_lImageToPrint = CFileBmp::FillImagesPrinterList(LOCAL_IMAGES, lImmTemp);

		// leggo dal report il numero di organi contenuti e sistemo tutte le liste (immagini e punti) //
		long lOrgTemp = CaricaImmaginiPunti(pStruct);
		pStruct->m_lOrganToPrint = min(lOrgTemp, ContaOrgani(pStruct->m_sReportFilePrinting));

		// leggo dal report la stampante di default in cui stampare //
		pStruct->m_lPrinterToUse = GetPrivateProfileInt("Page", "IDStampante", Printer_ChiediStampante, pStruct->m_sReportFilePrinting);

		// leggo dal report se stampare adattando il PDF al foglio //
		pStruct->m_bFitToPage = (BOOL)GetPrivateProfileInt("Page", "FitToPage", 0, pStruct->m_sReportFilePrinting);

		//
		bReturn = TRUE;
	}

	return bReturn;
}

void CEsamiView::StoreImmOnPacs()
{
	if (m_pFormImmagini)
		m_pFormImmagini->StoreImmOnPacs();
}

CList<reportElement*>* CEsamiView::AddElementToDocument(LPCTSTR chiave, LPCTSTR valore, CList<reportElement*>* reportElementList)
{
	return NULL;

	/*
	if (m_pReportElementList == NULL)
	return NULL;

	reportElement *temp = new reportElement();
	sprintf_s(temp->chiave, "%s", chiave);
	temp->lenValore = strlen(valore);
	temp->valore = new char[temp->lenValore + 1];
	ZeroMemory(temp->valore, sizeof(char) * temp->lenValore + 1);
	strcpy_s(temp->valore, temp->lenValore + 1, valore);

	if (reportElementList == NULL)
	{
	m_pReportElementList->AddTail(temp);
	}
	else
	{
	reportElementList->AddTail(temp);
	}

	if (temp->subelementsList == NULL)
	temp->subelementsList = new CList<reportElement*>();

	return temp->subelementsList;
	*/
}

CEsamiDoc* CEsamiView::GetDocument()
{
	return (CEsamiDoc*)m_pDocument;
}

//MESSAGGI MONITORAGGIO
LRESULT CEsamiView::OnThreadStartMonitoraggio(WPARAM wParam, LPARAM lParam)
{
	MonitoringPhase fase = (MonitoringPhase)wParam;

	CSelezioneDispositivoVSDlg dispDlg;
	dispDlg.DoModal();

	if (dispDlg.m_lIdDispositivo > 0)
	{
		BeginWaitCursor();

		m_sNomeDispositivoMonitoraggio = dispDlg.m_sNomeDispositivoMonitoraggio;

		//1. Chiamata a VitalSign che restituisce l'id della sessione	
		CString idSessione = "";
		if (AvviaSessioneMonitoraggio(dispDlg.m_lIdDispositivo, &idSessione, fase))
		{
			//2. Aggiorno la riga del monitoraggio su db, indicando il nome della stazione che lo sta effettuando il monitoraggio e l'id della sessione
			if (InsertHeaderMonitoraggioIdSessione(idSessione, dispDlg.m_lIdDispositivo, fase))
			{
				//3. Se tutto va a buon fine, aggiorno l'interfaccia
				m_bMonitoraggioAttivo = TRUE;

				//Imposto l'interfaccia
				ShowStatoEsame(SW_HIDE);
				ShowStatoMonitoraggio(SW_SHOW);

				UpdateFrameStato();

				//4. Faccio partire un timer che controlla se è terminato il monitoraggio facendo query su db
				SetTimer(TIMER_CHECK_MONITORAGGIO, 3000, NULL);
			}
		}

		EndWaitCursor();
	}
	else
	{
		m_lIDHeaderMisurazioniInCorso = 0;
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_STARTMON_NODISP));
	}


	return 0;
}

void CEsamiView::OnBnClickedBtnMonStop()
{
	//Modalità 1 - monitoraggio terminato da interfaccia di Endox.
	m_ctrlBtnStopMonitoraggio.SetCheck(BST_UNCHECKED);

	ChiudiMonitoraggioInCorso();

}

void CEsamiView::ShowStatoEsame(BOOL show)
{
	//GetDlgItem(IDC_LABEL_STATO)->ShowWindow(show); //Utilizzo questo per scrivere MONITORAGGIO IN CORSO
	GetDlgItem(IDC_LABEL_STATO_NEW1)->ShowWindow(show);
	GetDlgItem(IDC_LABEL_STATO_NEW2)->ShowWindow(show);
	GetDlgItem(IDC_LABEL_STATO_NEW3)->ShowWindow(show);
	GetDlgItem(IDC_LABEL_STATO_NEW4)->ShowWindow(show);
}

void CEsamiView::ShowStatoMonitoraggio(BOOL show)
{
	//GetDlgItem(IDC_LABEL_STATO_MONITORAGGIO)->SetFont(&theApp.m_fontBig, TRUE); //Utilizzo IDC_LABEL_STATO per scrivere MONITORAGGIO IN CORSO
	GetDlgItem(IDC_BTN_MON_STOP)->SetFont(&theApp.m_fontBig, TRUE);

	//GetDlgItem(IDC_LABEL_STATO_MONITORAGGIO)->ShowWindow(show); //Utilizzo IDC_LABEL_STATO per scrivere MONITORAGGIO IN CORSO
	GetDlgItem(IDC_BTN_MON_STOP)->ShowWindow(show);

	//Recupero nome paziente da id monitoraggio
	long idEsame = CVitalSignMisurazioniHeaderSet().GetIdEsame(m_lIDHeaderMisurazioniInCorso);
	long idPaziente = CEsamiSet().GetPaziente(idEsame);
	GetDlgItem(IDC_LABEL_MON_PAZIENTE)->SetWindowText(CPazientiSet().GetCognomeNome(idPaziente));
	GetDlgItem(IDC_LABEL_MON_PAZIENTE)->SetFont(&theApp.m_fontNormal, TRUE);
	GetDlgItem(IDC_LABEL_MON_PAZIENTE)->ShowWindow(show);

	//Setto nome dispositivo
	GetDlgItem(IDC_LABEL_MON_DISPOSITIVO)->SetWindowText(m_sNomeDispositivoMonitoraggio);
	GetDlgItem(IDC_LABEL_MON_DISPOSITIVO)->SetFont(&theApp.m_fontNormal, TRUE);
	GetDlgItem(IDC_LABEL_MON_DISPOSITIVO)->ShowWindow(show);

	UpdateFrameStato();
}

void CEsamiView::CheckMonitoraggioInCorso()
{
	BOOL bIncorso = IsMonitoraggioInCorso(m_lIDHeaderMisurazioniInCorso);

	if (!bIncorso)
		ChiudiMonitoraggioInCorso();
}

void CEsamiView::ChiudiMonitoraggioInCorso()
{
	BeginWaitCursor();

	//1. Killo il timer
	KillTimer(TIMER_CHECK_MONITORAGGIO);

	//3. Chiudo monitoraggio su db
	if (UpdateMonitoraggioTerminato(m_lIDHeaderMisurazioniInCorso))
	{
		//4. Chiudo monitoraggio su vital sign
		if (!ChiudiSessioneMonitoraggioInCorso())
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_STOP_VITALSIGN_ERROR));

		//5. Reimposto l'interfaccia
		m_bMonitoraggioAttivo = FALSE;
		m_lIDHeaderMisurazioniInCorso = 0;
		m_sNomeDispositivoMonitoraggio = "";

		ShowStatoMonitoraggio(SW_HIDE);
		ShowStatoEsame(SW_SHOW);

		UpdateFrameStato();

		if (m_pDynForm[sub_monitoraggio_oriz] != NULL)
		{
			CMonitoraggioBaseDynForm* temp = (CMonitoraggioBaseDynForm*)m_pDynForm[sub_monitoraggio_oriz];
			temp->Reload();
		}

		if (m_pDynForm[sub_monitoraggio_vert] != NULL)
		{
			CMonitoraggioBaseDynForm* temp = (CMonitoraggioBaseDynForm*)m_pDynForm[sub_monitoraggio_vert];
			temp->Reload();
		}
	}

	EndWaitCursor();

}

void CEsamiView::VerificaSeMonitoraggiInCorsoStazione()
{
	long idDispositivo = 0;

	m_bMonitoraggioAttivo = StazioneHaMonitoraggiPreInCorso(&m_lIDHeaderMisurazioniInCorso, &idDispositivo);

	if (m_bMonitoraggioAttivo)
	{
		m_sNomeDispositivoMonitoraggio = CVitalSignDispositiviSet().GetDescrizione(idDispositivo);

		//Imposto l'interfaccia
		ShowStatoEsame(SW_HIDE);
		ShowStatoMonitoraggio(SW_SHOW);

		UpdateFrameStato();

		//Faccio partire un timer che controlla se è terminato il monitoraggio facendo query su db
		SetTimer(TIMER_CHECK_MONITORAGGIO, 3000, NULL);
	}
}

BOOL CEsamiView::InsertHeaderMonitoraggioIdSessione(CString idSessione, long idDispositivo, MonitoringPhase fase)
{
	BOOL bReturn = FALSE;

	CVitalSignMisurazioniHeaderSet set;

	if (set.OpenRecordset("CEsamiView::UpdateMonitoraggioIdSessione"))
	{
		if (set.AddNewRecordset("CEsamiView::UpdateMonitoraggioIdSessione"))
		{
			set.m_sIDSessioneVitalSign = idSessione;
			set.m_sNomeStazione = theApp.m_sNomeComputer;
			set.m_lIDDispositivo = idDispositivo;
			set.m_lIDEsame = m_pEsamiSet->m_lContatore;
			set.m_lFase = fase;

			if (set.UpdateRecordset("CEsamiView::UpdateMonitoraggioIdSessione"))
			{
				m_lIDHeaderMisurazioniInCorso = set.GetLastAdd();
				bReturn = TRUE;
			}
			else
				theApp.AfxMessageBoxEndo("Errore aggiornamento dati monitoraggio");
		}

		set.CloseRecordset("CEsamiView::UpdateMonitoraggioIdSessione");
	}


	return bReturn;
}

BOOL CEsamiView::UpdateMonitoraggioTerminato(long lIDHeaderMisurazioni)
{
	BOOL bReturn = FALSE;

	CString filter;
	filter.Format("ID=%li", lIDHeaderMisurazioni);

	CVitalSignMisurazioniHeaderSet set;
	set.SetOpenFilter(filter);

	if (set.OpenRecordset("CEsamiView::UpdateMonitoraggioTerminato"))
	{
		if (!set.IsEOF())
		{
			if (set.EditRecordset("CEsamiView::UpdateMonitoraggioTerminato"))
			{
				set.m_bTerminato = TRUE;

				if (set.UpdateRecordset("CEsamiView::UpdateMonitoraggioTerminato"))
					bReturn = TRUE;
				else
					theApp.AfxMessageBoxEndo("Errore aggiornamento dati monitoraggio");
			}
		}

		set.CloseRecordset("CEsamiView::UpdateMonitoraggioTerminato");
	}


	return bReturn;
}

BOOL CEsamiView::IsMonitoraggioInCorso(long lIDHeaderMisurazioni)
{
	BOOL bReturn = TRUE;

	CString filter;
	filter.Format("ID=%li", lIDHeaderMisurazioni);

	CVitalSignMisurazioniHeaderSet set;
	set.SetOpenFilter(filter);

	if (set.OpenRecordset("CEsamiView::IsMonitoraggioInCorso"))
	{
		if (!set.IsEOF())
		{
			if (set.m_bTerminato)
				bReturn = FALSE;
		}

		set.CloseRecordset("CEsamiView::IsMonitoraggioInCorso");
	}


	return bReturn;
}

BOOL CEsamiView::StazioneHaMonitoraggiPreInCorso(long* lIDHeaderMisurazioni, long* idDispositivo)
{
	BOOL bReturn = FALSE;

	CString filter;
	filter.Format("FASE=%li and IDSESSIONEVITALSIGN is not null and NOMESTAZIONE = '%s' and TERMINATO=0", MonitoringPhase::pre, theApp.m_sNomeComputer);

	CVitalSignMisurazioniHeaderSet set;
	set.SetOpenFilter(filter);
	set.SetSortRecord("id desc");

	if (set.OpenRecordset("CEsamiView::StazioneHaMonitoraggiPreInCorso"))
	{
		if (!set.IsEOF())
		{
			bReturn = TRUE;
			*lIDHeaderMisurazioni = set.m_lID;
			*idDispositivo = set.m_lIDDispositivo;
		}

		set.CloseRecordset("CEsamiView::StazioneHaMonitoraggiPreInCorso");
	}


	return bReturn;
}

BOOL CEsamiView::AvviaSessioneMonitoraggio(int idDispositivo, CString* pIdSessione, MonitoringPhase fase)
{
	CVitalSignManager vsManager(this);
	if (vsManager.StartSession(idDispositivo, pIdSessione, fase))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CEsamiView::ChiudiSessioneMonitoraggioInCorso()
{
	CString idSessione = "";

	CString filter;
	filter.Format("id=%li", m_lIDHeaderMisurazioniInCorso);

	CVitalSignMisurazioniHeaderSet set;
	set.SetOpenFilter(filter);

	if (set.OpenRecordset("CEsamiView::AvviaSessioneMonitoraggio"))
	{
		if (!set.IsEOF())
		{
			idSessione = set.m_sIDSessioneVitalSign;
		}

		set.CloseRecordset("CEsamiView::AvviaSessioneMonitoraggio");
	}

	CVitalSignManager vsManager(this);
	if (vsManager.StopSession(idSessione))
		return TRUE;

	return FALSE;
}

void CEsamiView::UpdateDataFromWorklist()
{
	CString strFilter;
	strFilter.Format("IDRichiesta=%li", m_lIDPrenotazione);

	CExtOrdiniCampiAggiuntiviSet setTemp;
	setTemp.SetOpenFilter(strFilter);
	if (setTemp.OpenRecordset("CEsamiView::EsameNew"))
	{
		while (!setTemp.IsEOF())
		{
			setTemp.m_sTabella.MakeUpper();
			setTemp.m_sCampo.MakeUpper();

			if (setTemp.m_sTabella == "EESAMIPERSONALIZZABILI")
			{
				if (setTemp.m_sCampo == "TESTO000")
					m_pEsamiSet->m_setEP.m_sTesto000 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO001")
					m_pEsamiSet->m_setEP.m_sTesto001 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO002")
					m_pEsamiSet->m_setEP.m_sTesto002 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO003")
					m_pEsamiSet->m_setEP.m_sTesto003 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO004")
					m_pEsamiSet->m_setEP.m_sTesto004 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO005")
					m_pEsamiSet->m_setEP.m_sTesto005 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO006")
					m_pEsamiSet->m_setEP.m_sTesto006 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO007")
					m_pEsamiSet->m_setEP.m_sTesto007 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO008")
					m_pEsamiSet->m_setEP.m_sTesto008 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO009")
					m_pEsamiSet->m_setEP.m_sTesto009 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO010")
					m_pEsamiSet->m_setEP.m_sTesto010 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO011")
					m_pEsamiSet->m_setEP.m_sTesto011 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO012")
					m_pEsamiSet->m_setEP.m_sTesto012 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO013")
					m_pEsamiSet->m_setEP.m_sTesto013 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO014")
					m_pEsamiSet->m_setEP.m_sTesto014 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO015")
					m_pEsamiSet->m_setEP.m_sTesto015 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO016")
					m_pEsamiSet->m_setEP.m_sTesto016 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO017")
					m_pEsamiSet->m_setEP.m_sTesto017 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO018")
					m_pEsamiSet->m_setEP.m_sTesto018 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO019")
					m_pEsamiSet->m_setEP.m_sTesto019 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO020")
					m_pEsamiSet->m_setEP.m_sTesto020 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO021")
					m_pEsamiSet->m_setEP.m_sTesto021 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO022")
					m_pEsamiSet->m_setEP.m_sTesto022 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO023")
					m_pEsamiSet->m_setEP.m_sTesto023 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO024")
					m_pEsamiSet->m_setEP.m_sTesto024 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO025")
					m_pEsamiSet->m_setEP.m_sTesto025 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO026")
					m_pEsamiSet->m_setEP.m_sTesto026 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO027")
					m_pEsamiSet->m_setEP.m_sTesto027 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO028")
					m_pEsamiSet->m_setEP.m_sTesto028 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO029")
					m_pEsamiSet->m_setEP.m_sTesto029 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO030")
					m_pEsamiSet->m_setEP.m_sTesto030 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO031")
					m_pEsamiSet->m_setEP.m_sTesto031 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO032")
					m_pEsamiSet->m_setEP.m_sTesto032 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO033")
					m_pEsamiSet->m_setEP.m_sTesto033 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO034")
					m_pEsamiSet->m_setEP.m_sTesto034 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO035")
					m_pEsamiSet->m_setEP.m_sTesto035 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO036")
					m_pEsamiSet->m_setEP.m_sTesto036 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO037")
					m_pEsamiSet->m_setEP.m_sTesto037 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO038")
					m_pEsamiSet->m_setEP.m_sTesto038 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO039")
					m_pEsamiSet->m_setEP.m_sTesto039 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO040")
					m_pEsamiSet->m_setEP.m_sTesto040 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO041")
					m_pEsamiSet->m_setEP.m_sTesto041 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO042")
					m_pEsamiSet->m_setEP.m_sTesto042 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO043")
					m_pEsamiSet->m_setEP.m_sTesto043 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO044")
					m_pEsamiSet->m_setEP.m_sTesto044 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO045")
					m_pEsamiSet->m_setEP.m_sTesto045 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO046")
					m_pEsamiSet->m_setEP.m_sTesto046 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO047")
					m_pEsamiSet->m_setEP.m_sTesto047 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO048")
					m_pEsamiSet->m_setEP.m_sTesto048 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO049")
					m_pEsamiSet->m_setEP.m_sTesto049 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO050")
					m_pEsamiSet->m_setEP.m_sTesto050 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO051")
					m_pEsamiSet->m_setEP.m_sTesto051 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO052")
					m_pEsamiSet->m_setEP.m_sTesto052 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO053")
					m_pEsamiSet->m_setEP.m_sTesto053 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO054")
					m_pEsamiSet->m_setEP.m_sTesto054 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO055")
					m_pEsamiSet->m_setEP.m_sTesto055 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO056")
					m_pEsamiSet->m_setEP.m_sTesto056 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO057")
					m_pEsamiSet->m_setEP.m_sTesto057 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO058")
					m_pEsamiSet->m_setEP.m_sTesto058 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO059")
					m_pEsamiSet->m_setEP.m_sTesto059 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO060")
					m_pEsamiSet->m_setEP.m_sTesto060 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO061")
					m_pEsamiSet->m_setEP.m_sTesto061 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO062")
					m_pEsamiSet->m_setEP.m_sTesto062 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO063")
					m_pEsamiSet->m_setEP.m_sTesto063 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO064")
					m_pEsamiSet->m_setEP.m_sTesto064 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO065")
					m_pEsamiSet->m_setEP.m_sTesto065 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO066")
					m_pEsamiSet->m_setEP.m_sTesto066 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO067")
					m_pEsamiSet->m_setEP.m_sTesto067 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO068")
					m_pEsamiSet->m_setEP.m_sTesto068 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO069")
					m_pEsamiSet->m_setEP.m_sTesto069 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO070")
					m_pEsamiSet->m_setEP.m_sTesto070 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO071")
					m_pEsamiSet->m_setEP.m_sTesto071 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO072")
					m_pEsamiSet->m_setEP.m_sTesto072 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO073")
					m_pEsamiSet->m_setEP.m_sTesto073 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO074")
					m_pEsamiSet->m_setEP.m_sTesto074 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO075")
					m_pEsamiSet->m_setEP.m_sTesto075 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO076")
					m_pEsamiSet->m_setEP.m_sTesto076 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO077")
					m_pEsamiSet->m_setEP.m_sTesto077 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO078")
					m_pEsamiSet->m_setEP.m_sTesto078 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO079")
					m_pEsamiSet->m_setEP.m_sTesto079 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO080")
					m_pEsamiSet->m_setEP.m_sTesto080 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO081")
					m_pEsamiSet->m_setEP.m_sTesto081 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO082")
					m_pEsamiSet->m_setEP.m_sTesto082 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO083")
					m_pEsamiSet->m_setEP.m_sTesto083 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO084")
					m_pEsamiSet->m_setEP.m_sTesto084 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO085")
					m_pEsamiSet->m_setEP.m_sTesto085 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO086")
					m_pEsamiSet->m_setEP.m_sTesto086 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO087")
					m_pEsamiSet->m_setEP.m_sTesto087 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO088")
					m_pEsamiSet->m_setEP.m_sTesto088 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO089")
					m_pEsamiSet->m_setEP.m_sTesto089 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO090")
					m_pEsamiSet->m_setEP.m_sTesto090 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO091")
					m_pEsamiSet->m_setEP.m_sTesto091 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO092")
					m_pEsamiSet->m_setEP.m_sTesto092 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO093")
					m_pEsamiSet->m_setEP.m_sTesto093 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO094")
					m_pEsamiSet->m_setEP.m_sTesto094 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO095")
					m_pEsamiSet->m_setEP.m_sTesto095 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO096")
					m_pEsamiSet->m_setEP.m_sTesto096 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO097")
					m_pEsamiSet->m_setEP.m_sTesto097 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO098")
					m_pEsamiSet->m_setEP.m_sTesto098 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTO099")
					m_pEsamiSet->m_setEP.m_sTesto099 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTORTF000")
					m_pEsamiSet->m_setEP.m_sTestoRtf000 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT000")
				{
					m_pEsamiSet->m_setEP.m_sTestoTxt000 = setTemp.m_sValore;
					m_pEsamiSet->m_setEP.SetFieldNull(&m_pEsamiSet->m_setEP.m_sTestoRtf000);
				}
				if (setTemp.m_sCampo == "TESTORTF001")
					m_pEsamiSet->m_setEP.m_sTestoRtf001 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT001")
				{
					m_pEsamiSet->m_setEP.m_sTestoTxt001 = setTemp.m_sValore;
					m_pEsamiSet->m_setEP.SetFieldNull(&m_pEsamiSet->m_setEP.m_sTestoRtf001);
				}
				if (setTemp.m_sCampo == "TESTORTF002")
					m_pEsamiSet->m_setEP.m_sTestoRtf002 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT002")
				{
					m_pEsamiSet->m_setEP.m_sTestoTxt002 = setTemp.m_sValore;
					m_pEsamiSet->m_setEP.SetFieldNull(&m_pEsamiSet->m_setEP.m_sTestoRtf002);
				}
				if (setTemp.m_sCampo == "TESTORTF003")
					m_pEsamiSet->m_setEP.m_sTestoRtf003 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT003")
				{
					m_pEsamiSet->m_setEP.m_sTestoTxt003 = setTemp.m_sValore;
					m_pEsamiSet->m_setEP.SetFieldNull(&m_pEsamiSet->m_setEP.m_sTestoRtf003);
				}
				if (setTemp.m_sCampo == "TESTORTF004")
					m_pEsamiSet->m_setEP.m_sTestoRtf004 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT004")
				{
					m_pEsamiSet->m_setEP.m_sTestoTxt004 = setTemp.m_sValore;
					m_pEsamiSet->m_setEP.SetFieldNull(&m_pEsamiSet->m_setEP.m_sTestoRtf004);
				}
				if (setTemp.m_sCampo == "TESTORTF005")
					m_pEsamiSet->m_setEP.m_sTestoRtf005 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT005")
				{
					m_pEsamiSet->m_setEP.m_sTestoTxt005 = setTemp.m_sValore;
					m_pEsamiSet->m_setEP.SetFieldNull(&m_pEsamiSet->m_setEP.m_sTestoRtf005);
				}
				if (setTemp.m_sCampo == "TESTORTF006")
					m_pEsamiSet->m_setEP.m_sTestoRtf006 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT006")
				{
					m_pEsamiSet->m_setEP.m_sTestoTxt006 = setTemp.m_sValore;
					m_pEsamiSet->m_setEP.SetFieldNull(&m_pEsamiSet->m_setEP.m_sTestoRtf006);
				}
				if (setTemp.m_sCampo == "TESTORTF007")
					m_pEsamiSet->m_setEP.m_sTestoRtf007 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT007")
				{
					m_pEsamiSet->m_setEP.m_sTestoTxt007 = setTemp.m_sValore;
					m_pEsamiSet->m_setEP.SetFieldNull(&m_pEsamiSet->m_setEP.m_sTestoRtf007);
				}
				if (setTemp.m_sCampo == "TESTORTF008")
					m_pEsamiSet->m_setEP.m_sTestoRtf008 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT008")
				{
					m_pEsamiSet->m_setEP.m_sTestoTxt008 = setTemp.m_sValore;
					m_pEsamiSet->m_setEP.SetFieldNull(&m_pEsamiSet->m_setEP.m_sTestoRtf008);
				}
				if (setTemp.m_sCampo == "TESTORTF009")
					m_pEsamiSet->m_setEP.m_sTestoRtf009 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT009")
				{
					m_pEsamiSet->m_setEP.m_sTestoTxt009 = setTemp.m_sValore;
					m_pEsamiSet->m_setEP.SetFieldNull(&m_pEsamiSet->m_setEP.m_sTestoRtf009);
				}
				if (setTemp.m_sCampo == "TESTORTF010")
					m_pEsamiSet->m_setEP.m_sTestoRtf009 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT010")
				{
					m_pEsamiSet->m_setEP.m_sTestoTxt010 = setTemp.m_sValore;
					m_pEsamiSet->m_setEP.SetFieldNull(&m_pEsamiSet->m_setEP.m_sTestoRtf010);
				}
				if (setTemp.m_sCampo == "TESTORTF011")
					m_pEsamiSet->m_setEP.m_sTestoRtf010 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT011")
				{
					m_pEsamiSet->m_setEP.m_sTestoTxt011 = setTemp.m_sValore;
					m_pEsamiSet->m_setEP.SetFieldNull(&m_pEsamiSet->m_setEP.m_sTestoRtf011);
				}
				if (setTemp.m_sCampo == "TESTORTF012")
					m_pEsamiSet->m_setEP.m_sTestoRtf011 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT012")
				{
					m_pEsamiSet->m_setEP.m_sTestoTxt012 = setTemp.m_sValore;
					m_pEsamiSet->m_setEP.SetFieldNull(&m_pEsamiSet->m_setEP.m_sTestoRtf012);
				}
				if (setTemp.m_sCampo == "TESTORTF013")
					m_pEsamiSet->m_setEP.m_sTestoRtf012 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT013")
				{
					m_pEsamiSet->m_setEP.m_sTestoTxt013 = setTemp.m_sValore;
					m_pEsamiSet->m_setEP.SetFieldNull(&m_pEsamiSet->m_setEP.m_sTestoRtf013);
				}
				if (setTemp.m_sCampo == "TESTORTF014")
					m_pEsamiSet->m_setEP.m_sTestoRtf013 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT014")
				{
					m_pEsamiSet->m_setEP.m_sTestoTxt014 = setTemp.m_sValore;
					m_pEsamiSet->m_setEP.SetFieldNull(&m_pEsamiSet->m_setEP.m_sTestoRtf014);
				}
				if (setTemp.m_sCampo == "TESTORTF015")
					m_pEsamiSet->m_setEP.m_sTestoRtf015 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT015")
				{
					m_pEsamiSet->m_setEP.m_sTestoTxt015 = setTemp.m_sValore;
					m_pEsamiSet->m_setEP.SetFieldNull(&m_pEsamiSet->m_setEP.m_sTestoRtf015);
				}
				if (setTemp.m_sCampo == "TESTORTF016")
					m_pEsamiSet->m_setEP.m_sTestoRtf016 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT016")
				{
					m_pEsamiSet->m_setEP.m_sTestoTxt016 = setTemp.m_sValore;
					m_pEsamiSet->m_setEP.SetFieldNull(&m_pEsamiSet->m_setEP.m_sTestoRtf016);
				}
				if (setTemp.m_sCampo == "TESTORTF017")
					m_pEsamiSet->m_setEP.m_sTestoRtf017 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT017")
				{
					m_pEsamiSet->m_setEP.m_sTestoTxt017 = setTemp.m_sValore;
					m_pEsamiSet->m_setEP.SetFieldNull(&m_pEsamiSet->m_setEP.m_sTestoRtf017);
				}
				if (setTemp.m_sCampo == "TESTORTF018")
					m_pEsamiSet->m_setEP.m_sTestoRtf018 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT018")
				{
					m_pEsamiSet->m_setEP.m_sTestoTxt018 = setTemp.m_sValore;
					m_pEsamiSet->m_setEP.SetFieldNull(&m_pEsamiSet->m_setEP.m_sTestoRtf018);
				}
				if (setTemp.m_sCampo == "TESTORTF019")
					m_pEsamiSet->m_setEP.m_sTestoRtf019 = setTemp.m_sValore;
				if (setTemp.m_sCampo == "TESTOTXT019")
				{
					m_pEsamiSet->m_setEP.m_sTestoTxt019 = setTemp.m_sValore;
					m_pEsamiSet->m_setEP.SetFieldNull(&m_pEsamiSet->m_setEP.m_sTestoRtf019);
				}
			}

			if (setTemp.m_sTabella == "EPAZIENTI")
			{
				CPazientiSet pazientiSet;
				CString filter;
				filter.Format("CONTATORE = %li", m_pEsamiSet->m_lPaziente);
				pazientiSet.SetOpenFilter(filter);
				if (pazientiSet.OpenRecordset("CEsamiView::EsameNew"))
				{
					if (pazientiSet.EditRecordset("CEsamiView::EsameNew"))
					{
						if (setTemp.m_sCampo == "MEDICOTEL")
							pazientiSet.m_sMedicoTel = setTemp.m_sValore;
						if (setTemp.m_sCampo == "CODICECLIENTE")
							pazientiSet.m_sCodiceCliente = setTemp.m_sValore;
						if (setTemp.m_sCampo == "ULSSRESIDENZA")
							pazientiSet.m_sUlssResidenza = setTemp.m_sValore;

						pazientiSet.UpdateRecordset("CEsamiView::EsameNew");
					}

					pazientiSet.CloseRecordset("CEsamiView::EsameNew");
				}
			}

			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CEsamiView::EsameNew");

		UpdateData(FALSE);
	}
}

void CEsamiView::RicaricaDatiAssociatiAllEsame()
{
	//FASI CHIUSE
	m_listIDFasiChiuse.RemoveAll();

	if (m_pEsamiSet == NULL || m_pEsamiSet->m_lContatore <= 0)
		return;

	//Gabriel - P3

	//Aggiungo chiusura e convalida
	if (m_pEsamiSet->m_bLocked)
		m_listIDFasiChiuse.AddTail(CO_FASE_CONVALIDA);

	if (m_pEsamiSet->m_bSuperLocked)
		m_listIDFasiChiuse.AddTail(CO_FASE_CHIUSURA_STAMPA);

	//Gabriel - P3
	if (theApp.m_bAtivaP3)
	{
		if (m_pEsamiSet->m_bHyperLocked)
			m_listIDFasiChiuse.AddTail(CO_FASE_LIBERA_LAUDO);
	}

	//16093
	// Verifico se l'esame è mai stato firmato digitalmente
	long lIDPrecedente = 0;
	CString sDataPrecedente = "";
	CString sMotivoPrecedente = "";
	CPdfManager().GetDatiUltimoPdfFirmato(m_pEsamiSet->m_lContatore, lIDPrecedente, sDataPrecedente, sMotivoPrecedente);
	theApp.m_bEsameFirmatoDigitalmenteAlmenoUnaVolta = (lIDPrecedente > 0 ? TRUE : FALSE);

}

BOOL CEsamiView::IsFaseChiusa(long lIDFase)
{
	POSITION pos = m_listIDFasiChiuse.Find(lIDFase);

	if (pos)
		return TRUE;
	else
		return FALSE;
}

void CEsamiView::ChiudiFase(long lIDFase)
{
	OnCommandChiudiFase(lIDFase);
}

// Metodo che viene chiamato dal Menu e dal pulsante
void CEsamiView::ConvalidaEsame()
{
	BeginWaitCursor();

	BOOL bExit = FALSE;

	if (!bExit)
	{
		CTime now = CTime::GetCurrentTime();
		m_sDataOraConvalida = now.Format("%Y%m%d%H%M%S");
		m_pEsamiSet->m_sDataOraLock = now.Format("%Y%m%d%H%M%S");

		if (theApp.m_enumFirmaDigitale != CEndoxApp::sign_disabled)
		{
			OnToolbarStampaReport();
		}
		else
		{
			// if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CONVALIDA_CONFERMA), MB_YESNO) == IDYES)
			{
				BOOL bOK = m_pEsamiSet->ConvalidaEsame(m_sDataOraConvalida);
				UpdateData(FALSE);

				// Sandro 11/07/2017 //
				if (bOK && !m_pEsamiSet->m_sFleuryEndpointRemoto.IsEmpty())
					UpdateDatiRemoti(m_pEsamiSet);
			}
		}
	}

	m_sDataOraConvalida = "";

	RicaricaDatiAssociatiAllEsame();
	MovePazientiAndEsami(NULL, FALSE, TRUE);

	EndWaitCursor();
}

void CEsamiView::ChiudiEsame()
{
	
	if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury)
	{
		if (CEsamiSet().IsConiugatoPrincipale(m_pEsamiSet->m_lContatore))
		{
			CString sMessage;
			sMessage.Format(theApp.GetMessageString(IDS_FLEURY_CHIUSURAESAMECONIUGATO), m_pEsamiSet->m_sRefertoConiugatoSecondario);

			theApp.AfxMessageBoxEndo(sMessage);
		}
		else if (CEsamiSet().IsConiugatoSecondario(m_pEsamiSet->m_lContatore))
		{
			if (!theApp.m_bAtivaTCP || m_pEsamiSet->m_sCodesameCorrelati.IsEmpty())
			{
				CString sMessage;
				sMessage.Format(theApp.GetMessageString(IDS_FLEURY_CHIUSURAESAMECONIUGATOSECOND), m_pEsamiSet->m_sRefertoConiugatoPrincipale);

				theApp.AfxMessageBoxEndo(sMessage);

				return;
			}
		}
	}

	BeginWaitCursor();

	BOOL bExit = FALSE;

	// Simone RAS 20160005

	if (CAnatomiaPatologicaSet().HasMaterials(m_pEsamiSet->m_lContatore) && m_pEsamiSet->m_lAPStato < STATO_PRENOTATA)
	{
		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_AP_NONINVIATA_CHIUSURA), MB_YESNO) == IDYES)
		{
			if (m_pDynForm[sub_anatomiapatologicatasti] != NULL)
				if (!((CAnatomiaPatologicaTastiForm*)m_pDynForm[sub_anatomiapatologicatasti])->InviaRichiestaProc())
					bExit = TRUE;
		}
	}

	// Sandro 28/08/2012 // modifica per cancellazione esame Einstein //

	if (!bExit)
	{
		if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury || theApp.m_bPersonalizzazioniBrasileSirio)
		{
			if (!CRegioneSet().ExamHasPrestazioniNonNormate(m_pEsamiSet->m_lContatore))
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAME_ANNULLATO));
				bExit = TRUE;
			}
		}
	}

	// Sandro 03/04/2015 // RIMA 15008 //

	if (!bExit)
	{
		if (theApp.m_bChiusuraEsameSoloConPrestazioniPrincipali)
		{
			if (!CVistaEsamiConPrestazioniPrincipaliSet().TrovaEsame(m_pEsamiSet->m_lContatore))
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAME_NOPRESTAZIONIPRINCIPALI));
				bExit = TRUE;
			}
		}
	}

	if (!bExit)
	{
		if (theApp.m_bPersonalizzazioniBrasileFleury || theApp.m_lRicercaCodiceEsame == RICERCA_PAZIENTE_FICHA)
		{
			CString sErrore, sPlaceHolder;
			if (FleuryCercaFicha(m_pEsamiSet->m_sCodEsame, sErrore, sPlaceHolder, sPlaceHolder, sPlaceHolder))
			{

			}
			else
			{
				if (!sErrore.IsEmpty())
				{
					theApp.AfxMessageBoxEndo(sErrore);
				}
				theApp.AfxMessageBoxEndo(IDS_ESAME_ANNULLATO);
				bExit = TRUE;
			}
		}
	}
	//Julio 11/08/2018 
	if (!bExit)
	{
		if (theApp.m_bPersonalizzazioniBrasileFleury)
		{
			CString sMessaggio = "";
			BOOL bModifica = FleuryPossoModificare(sMessaggio, m_pEsamiSet->m_sRicovero, m_pEsamiSet->m_sCodEsame);
			if (!bModifica)
			{
				theApp.AfxMessageBoxEndo(sMessaggio);
				bExit = TRUE;
			}
		}
	}
	//

	if (!bExit)
	{
		//Julio 4/12/2017 centralizacao Fleury tras todas as imagens que faltam para o pdf poder ser gerado
		if (theApp.m_bPersonalizzazioniBrasileFleury || theApp.m_lRicercaCodiceEsame == RICERCA_PAZIENTE_FICHA)
		{
			FleuryGetImagensAltraSede(this, this);
			FleuryGetDocsAltraSede(m_pEsamiSet->m_lContatore, TRUE);
			FleuryGetDocsAltraSede(m_pEsamiSet->m_lContatore, FALSE);
		}
		//
		CTime now = CTime::GetCurrentTime();
		m_sDataOraChiusura = now.Format("%Y%m%d%H%M%S");
		m_pEsamiSet->m_sDataOraSuperLock = now.Format("%Y%m%d%H%M%S");

		if (m_pEsamiSet->m_sDataOraSuperLockPrimo.IsEmpty())
			m_pEsamiSet->m_sDataOraSuperLockPrimo = m_pEsamiSet->m_sDataOraSuperLock;

		//Gabriel - TCP
		BOOL bIsEsameCorrelato = FALSE;
		long lIdEsameCorrelato;
		if (theApp.m_bAtivaTCP && !m_pEsamiSet->m_sCodesameCorrelati.IsEmpty())
		{
			CString sFilterConiugato;
			sFilterConiugato.Format("CODESAME='%s'", m_pEsamiSet->m_sCodesameCorrelati);

			CEsamiSet setEsameConiugato;
			setEsameConiugato.SetBaseFilter("(UO=0 OR UO>0)");
			setEsameConiugato.SetOpenFilter(sFilterConiugato);

			if (setEsameConiugato.OpenRecordset("CEsamiView::ChiudiEsame"))
			{
				if (!setEsameConiugato.IsEOF())
				{
					bIsEsameCorrelato = TRUE;
					lIdEsameCorrelato = setEsameConiugato.m_lIDEsame;
				}

				setEsameConiugato.CloseRecordset("CEsamiView::ChiudiEsame");
			}
		}

		long lClosedExamId = 0; //Julio - BUG 3365 - MAMOGUS

		if (theApp.m_enumFirmaDigitale != CEndoxApp::sign_disabled)
		{
			OnToolbarStampaReport();
		}
		else
		{
			if (theApp.m_bInterfacciaDMS)
			{
				//
				BeginWaitCursor();

				// inserisco una riga nella tabella EXT_ESAMI_CHIUSI //
				CEsamiChiusiSet().InserisciRecord(m_pEsamiSet->m_lContatore, 999999999, 999999999, GetUserIDForLockSuperlock(), "NW");

				// chiudo l'esame //
				BOOL bOK = m_pEsamiSet->ChiudiEsame(m_sDataOraChiusura, (CRefertoForm*)m_pDynForm[sub_referto]);

				// aggiorno l'interfaccia //
				UpdateData(FALSE);

				// Sandro 11/07/2017 //
				if (bOK && !m_pEsamiSet->m_sFleuryEndpointRemoto.IsEmpty())
					UpdateDatiRemoti(m_pEsamiSet);

				//
				EndWaitCursor();
			}
			else
			{
				BOOL bContinue = TRUE;

				if (theApp.m_bChiusuraEsameLogoutAuto)
					bContinue = Logout(FALSE);

				if (bContinue)
				{
		

					if (theApp.m_bChiusuraEsameDoppiaConferma)
					{
						if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CHIUSURA_CONFERMA2), MB_YESNO) == IDNO)
						{
							lClosedExamId = bIsEsameCorrelato ? OnChiudiEsameCorrelati(lIdEsameCorrelato) : OnChiudiEsame();
							UpdateData(FALSE);
						}
					}
					else
					{
						lClosedExamId = bIsEsameCorrelato ? OnChiudiEsameCorrelati(lIdEsameCorrelato) : OnChiudiEsame();

						UpdateData(FALSE);
					}
					/*		if (theApp.m_listUserPhases.Find(CO_FASE_CHIUSURA_STAMPA) != NULL)
							{

							}
							else
							{
								theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMPOSSIBILE_CHIUDERE));
							}*/
				}
			}
		}




		// Sandro 21/10/2016 // RIMA 16037 //
		if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury)
		{
			if (CEsamiSet().IsConiugatoPrincipale(m_pEsamiSet->m_lContatore))
			{
				CString sFilterConiugato;
				sFilterConiugato.Format("CODESAME='%s'", m_pEsamiSet->m_sRefertoConiugatoSecondario);

				CEsamiSet setEsameConiugato;
				setEsameConiugato.SetBaseFilter("(UO=0 OR UO>0)");
				setEsameConiugato.SetOpenFilter(sFilterConiugato);

				if (setEsameConiugato.OpenRecordset("CEsamiView::ChiudiEsame"))
				{
					if (!setEsameConiugato.IsEOF())
					{
						// inserisco una riga nella tabella EXT_ESAMI_CHIUSI //
						CEsamiChiusiSet().InserisciRecord(setEsameConiugato.m_lContatore, -1, -1, GetUserIDForLockSuperlock(), "NW");

						// chiudo l'esame //
						CEsamiSet().ChiudiEsameIntegrato(setEsameConiugato.m_lContatore, m_sDataOraChiusura);
					}

					setEsameConiugato.CloseRecordset("CEsamiView::ChiudiEsame");
				}
			}
		}
		//Julio - BUG 3365 - MAMOGUS
		if (theApp.m_bUsaComboPrestazioni)
		{
			//O exame precisa ser conjugado primario para que enviemos o RE 
			//CString sPrestazione = CVistaComboPrestazioni().GetCodicePrestazione(m_pEsamiSet->m_sRicovero);
			CString sPrestazione = CExtPrestazioniSet().GetCodice(m_pEsamiSet->m_sCodEsame);

			//verifica se o exame atual tem um combo em sua sigla 
			CList<CString> listCombo;
			CComboPrestazioni().GetComboList(sPrestazione, &listCombo);
			//

			//Em caso positivo
			if (listCombo.GetCount() > 0)
			{
				for (POSITION pos = listCombo.GetHeadPosition(); pos;)
				{
					//loop pelas siglas que fazem combo com a sigla do exame inserido
					CString sPrestazioneCombo = listCombo.GetNext(pos);

					//Verifica se existe algum outro exame na ext_ordini com o mesmo nosologico e com uma das outras siglas do combo
					if (CVistaComboPrestazioni().ExamHasCombo(m_pEsamiSet->m_sRicovero, sPrestazioneCombo))
					{
						//Pergunta ao usuario se ele quer enviar este laudo
						if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_FLEURY_CHIUSURAESAMEMAMOGUS), MB_YESNO) == IDYES)
						{
							long lIDExt = CExtComboPrestazioni().Insert(m_pEsamiSet->m_lContatore, CExtComboPrestazioni::Tipo::Report, lClosedExamId);

							//Avisa o usuario que ocorreu um erro e qual procedimento ele deve fazer
							if (lIDExt <= 0)
								theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_FLEURY_CHIUSURAESAMEMAMOGUS_ERRO1));
							else
								break;
						}
					}
				}
			}
		}
		

		//Julio 25/09/2018  - Pdf imagens perde referencia na ext_esami_chiusi quando exame assinado em mobilidade
		/*if (theApp.m_bPersonalizzazioniBrasileFleury)
		{
		CPdfList plEsame;
		CPdfManager().GetPdf(m_pEsamiSet->m_lContatore, &plEsame);

		PDF pdfImagem;
		PDF pdfLaudo;

		BOOL bI1 = TRUE;
		BOOL bL1 = TRUE;

		POSITION pos = plEsame.GetHeadPosition();
		while (pos != NULL)
		{
		PDF pdfTemp = plEsame.GetAt(pos);

		if (pdfTemp.ptTipo == pdftype_images)
		{
		if (bI1)
		{
		pdfImagem = plEsame.GetAt(pos);
		bI1 = FALSE;
		}

		else if (pdfTemp.lVersione > pdfImagem.lVersione)
		pdfImagem = plEsame.GetAt(pos);
		}
		if (pdfTemp.ptTipo == pdftype_report)
		{
		if (bL1)
		{
		pdfLaudo = plEsame.GetAt(pos);
		bL1 = FALSE;
		}

		else if (pdfTemp.lVersione > pdfLaudo.lVersione)
		pdfLaudo = plEsame.GetAt(pos);
		}
		plEsame.GetNext(pos);
		}

		CEsamiChiusiSet().UpdateRecord(m_pEsamiSet->m_lContatore, pdfLaudo.lID, pdfImagem.lID, GetUserIDForLockSuperlock());
		}*/
		//

		m_sDataOraChiusura = "";

		RicaricaDatiAssociatiAllEsame();
		MovePazientiAndEsami(NULL, FALSE, TRUE);
	}

	EndWaitCursor();

	//Julio BUG 3456 - Contingencia
	if (theApp.m_bContingencia && CheckIfMainDBIsOnline())
	{
		AfxMessageBox(theApp.GetMessageString(IDS_CONTINGENZA_MESSAGE));
		AfxGetMainWnd()->PostMessage(WM_CLOSE);
	}
}

BOOL CEsamiView::ChiudiFase_CambioUtente(long lIDFase)
{
	BOOL bReturn = FALSE;

	if (theApp.m_lLoginMode == 3 || theApp.m_lLoginMode == 4)
	{
		if (AMLogin_Login(
			theApp.m_sUtenteLoggato,
			theApp.m_sNomeComputer,
			theApp.m_sNomeImpianto,
			theApp.GetMessageString(IDS_SYSTEM_ACCESS),
			&theApp.m_dbEndox,
			4, //Nel caso di logout in Single Sign-On, l'accesso conseguente deve essere fatto con la richiesta di utente e password
			theApp.m_sLoginServer,
			theApp.m_bLoginDropDomain,
			TRUE, // Sandro 02/04/2015 // se non mi muovo è il logout automatico (per la refertazione o per la chiusura dell'esame) //
			tesiimaging))
		{
			theApp.m_sUtenteLoggato = AMLogin_GetUsername();

			AMLogin_GetUserPermission(&theApp.m_dwPrivileges);

			long lUserID = 0;
			AMLogin_GetUserID(&lUserID);

			// Sandro 26/11/2014 //
			// CUOSet().VerificaUODefault();

			//
			CStringList listGroups;
			if (lUserID > 0)
			{
				if (AMLogin_GetUserGroups_Net(&listGroups))
				{
					BOOL bUOFound = FALSE;

					CUOUtenteSet setUOUtente;
					CString strFilter;
					strFilter.Format("IDUtente=%li", lUserID);

					setUOUtente.SetOpenFilter(strFilter);

					//1. Verifico che tra i gruppi ci sia quello che cerco
					POSITION posGroups = listGroups.GetHeadPosition();
					while (posGroups != NULL)
					{
						CString gruppo = listGroups.GetAt(posGroups);
						long lUserUO = CVistaGruppiSet().GetUO(gruppo);

						if (lUserUO == theApp.m_lUO)
						{
							bUOFound = TRUE;
							break;
						}

						listGroups.GetNext(posGroups);
					}

					if (bUOFound)
					{
						//2. Proseguo con il login										
						if (setUOUtente.OpenRecordset("CEsamiView::ChiudiFase_CambioUtente"))
						{
							while (!setUOUtente.IsEOF())
							{
								setUOUtente.DeleteRecordset("CEsamiView::ChiudiFase_CambioUtente");
								setUOUtente.MoveNext();
							}

							setUOUtente.CloseRecordset("CEsamiView::ChiudiFase_CambioUtente");
						}

						POSITION posGroups = listGroups.GetHeadPosition();
						while (posGroups != NULL)
						{
							CString gruppo = listGroups.GetAt(posGroups);
							long lUserUO = CVistaGruppiSet().GetUO(gruppo);

							if (lUserUO > 0)
							{
								setUOUtente.SetOpenFilter("IDUtente=0");
								if (setUOUtente.OpenRecordset("CEsamiView::ChiudiFase_CambioUtente"))
								{
									if (setUOUtente.AddNewRecordset("CEsamiView::ChiudiFase_CambioUtente"))
									{
										setUOUtente.m_lIDUO = lUserUO;
										setUOUtente.m_lIDUtente = lUserID;

										setUOUtente.UpdateRecordset("CEsamiView::ChiudiFase_CambioUtente");
									}

									setUOUtente.CloseRecordset("CEsamiView::ChiudiFase_CambioUtente");
								}
							}

							listGroups.GetNext(posGroups);
						}

						theApp.m_dwPrivileges = GetUpdatedPrivileges();
						AMLogin_SetUserPermission(theApp.m_dwPrivileges);

						((CEsamiDoc*)m_pDocument)->LoadUserGroups();
						((CEsamiDoc*)m_pDocument)->LoadEnabledPhaseForUser();

						//3. Devo verificare che l'utente che ha fatto il login possa gestire la fase
						if (theApp.m_listUserPhases.Find(lIDFase))
						{
							((CEsamiDoc*)m_pDocument)->SetTitle(theApp.GetAppTitle(0));
							bReturn = TRUE;
						}
						else
						{
							theApp.AfxMessageBoxEndo("L'utente non è abilitato alla gestione della fase " + CFasiEsameSet().GetDescrizione(lIDFase) + ".\r\nL'operazione verrà annullata.");
						}
					}
					else
						theApp.AfxMessageBoxEndo("L'utente non appartiene all'unità operativa " + CUOSet().GetDescrizione(theApp.m_lUO) + ".\r\nL'operazione verrà annullata.");
				}
			}
		}
		else
		{
			AfxGetMainWnd()->PostMessage(WM_CLOSE);
		}
	}
	else
	{
		if (AMLogin_Login(
			theApp.m_sUtenteLoggato,
			theApp.m_sNomeComputer,
			theApp.m_sNomeImpianto,
			theApp.GetMessageString(IDS_SYSTEM_ACCESS),
			&theApp.m_dbEndox,
			theApp.m_lLoginMode,
			theApp.m_sLoginServer,
			theApp.m_bLoginDropDomain,
			TRUE,
			tesiimaging))
		{
			theApp.m_sUtenteLoggato = AMLogin_GetUsername();

			AMLogin_GetUserPermission(&theApp.m_dwPrivileges);

			long lUserID = 0;
			AMLogin_GetUserID(&lUserID);

			//
			//dopo il login verifico che l'utente possa agire sulla UO attuale
			BOOL bUOFound = FALSE;

			CString strFilter;
			strFilter.Format("IDUtente=%li", lUserID);

			CUOUtenteSet setUOUtente;
			setUOUtente.SetOpenFilter(strFilter);
			setUOUtente.SetSortRecord("IDUO");
			if (setUOUtente.OpenRecordset("CEsamiView::ChiudiFase_CambioUtente"))
			{
				while (!setUOUtente.IsEOF())
				{
					if (setUOUtente.m_lIDUO == theApp.m_lUO)
					{
						bUOFound = TRUE;
						break;
					}

					setUOUtente.MoveNext();
				}

				setUOUtente.CloseRecordset("CEsamiView::ChiudiFase_CambioUtente");
			}


			if (bUOFound)
			{
				//Non va fatto per loginMode 0
				//theApp.m_dwPrivileges = GetUpdatedPrivileges();
				//AMLogin_SetUserPermission(theApp.m_dwPrivileges);				

				((CEsamiDoc*)m_pDocument)->LoadUserGroups();
				((CEsamiDoc*)m_pDocument)->LoadEnabledPhaseForUser();

				//3. Devo verificare che l'utente che ha fatto il login possa gestire la fase
				if (theApp.m_listUserPhases.Find(lIDFase))
				{
					((CEsamiDoc*)m_pDocument)->SetTitle(theApp.GetAppTitle(0));
					bReturn = TRUE;
				}
				else
				{
					theApp.AfxMessageBoxEndo("L'utente non è abilitato alla gestione della fase " + CFasiEsameSet().GetDescrizione(lIDFase) + ".\r\nL'operazione verrà annullata.");
				}
			}
			else
				theApp.AfxMessageBoxEndo("L'utente non appartiene all'unità operativa " + CUOSet().GetDescrizione(theApp.m_lUO) + ".\r\nL'operazione verrà annullata.");
		}
		else
		{
			AfxGetMainWnd()->PostMessage(WM_CLOSE);
		}
	}

	return bReturn;
}

void CEsamiView::UpdateModalityWorklistSCP()
{
	CModalityWorklistSCP::Get()->Clear();
	// CDicomReceiverManager::Get()->ResetCurrentPatient();

	if (theApp.m_bDicomWorklistActive)
	{
		if (!m_pPazientiSet->IsOpen() || m_pPazientiSet->IsBOF() || m_pPazientiSet->IsEOF())
			return;

		if (!m_pEsamiSet->IsOpen() || m_pEsamiSet->IsBOF() || m_pEsamiSet->IsEOF())
			return;

#ifndef _DEBUG
		if (m_pEsamiSet->m_bSuperLocked)
			return;
#endif

		char szSex[2];
		strcpy_s(szSex, "O");
		if (m_pPazientiSet->m_lSessoPaz == 0)
			strcpy_s(szSex, "M");
		if (m_pPazientiSet->m_lSessoPaz == 1)
			strcpy_s(szSex, "F");

		TCHAR szPatientId[MAX_PATH];
		if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury)
			sprintf_s(szPatientId, "%s", m_pEsamiSet->m_sCodEsame);
		else
			sprintf_s(szPatientId, "%li", m_pPazientiSet->m_lContatore);

		TCHAR szAccessionNumber[MAX_PATH];
		sprintf_s(szAccessionNumber, "%li", m_pEsamiSet->m_lContatore);

		TCHAR szBirthDate[9];
		strcpy_s(szBirthDate, CCustomDate(m_pPazientiSet->m_lNatoIlCustom).GetDate("%Y%m%d"));

		TCHAR szExamDate[15];
		strcpy_s(szExamDate, CCustomDate(m_pEsamiSet->m_lData).GetDate("%Y%m%d%H%M00"));

		char szAltezza[16];
		if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_fAltezza) && (m_pEsamiSet->m_fAltezza > 0))
			sprintf_s(szAltezza, "%.2f", m_pEsamiSet->m_fAltezza);
		else
			strcpy_s(szAltezza, "");

		char szPeso[16];
		if (!m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_fPeso) && (m_pEsamiSet->m_fPeso > 0))
			sprintf_s(szPeso, "%.2f", m_pEsamiSet->m_fPeso);
		else
			strcpy_s(szPeso, "");

		CModalityWorklistSCP::Get()->SetPatient(szPatientId,
			m_pPazientiSet->m_sCognome,
			m_pPazientiSet->m_sNome,
			szBirthDate,
			szSex,
			m_pEsamiSet->m_lIDEsame,
			CTipoEsameSet().GetDescrizione(m_pEsamiSet->m_lIDEsame),
			szExamDate,
			szAccessionNumber,
			szAltezza,
			szPeso,
			CMediciSet().GetFieldFirmaFromContatore(m_pEsamiSet->m_lMedico, 0),
			CExtPrestazioniSet().GetDescrizione(m_pEsamiSet->m_sCodEsame),
			m_pEsamiSet->m_sInvMedico
		);

		// CDicomReceiverManager::Get()->SetCurrentPatient(m_pExam->m_idpaziente, m_pExam->m_id);
	}
}


void CEsamiView::OnEnChangeEditFleuryficha()
{
	CString sFichaBefore = m_sFleuryFicha;
	GetDlgItem(IDC_EDIT_FLEURYFICHA)->GetWindowText(m_sFleuryFicha);
	CString sFichaAfter = m_sFleuryFicha;

	CString sItemBefore = m_sFleuryItem;
	GetDlgItem(IDC_EDIT_FLEURYITEM)->GetWindowText(m_sFleuryItem);
	CString sItemAfter = m_sFleuryItem;

	if (sFichaBefore == sFichaAfter && sItemBefore == sItemAfter)
		OnEnChangeEditFleuryEnterPressed();
}

void CEsamiView::OnEnChangeEditFleuryitem()
{
	CString sFichaBefore = m_sFleuryFicha;
	GetDlgItem(IDC_EDIT_FLEURYFICHA)->GetWindowText(m_sFleuryFicha);
	m_sFleuryFicha = m_sFleuryFicha.Trim();
	CString sFichaAfter = m_sFleuryFicha;

	CString sItemBefore = m_sFleuryItem;
	GetDlgItem(IDC_EDIT_FLEURYITEM)->GetWindowText(m_sFleuryItem);
	m_sFleuryItem = m_sFleuryItem.Trim();
	CString sItemAfter = m_sFleuryItem;

	if (sFichaBefore == sFichaAfter && sItemBefore == sItemAfter)
		OnEnChangeEditFleuryEnterPressed();
}

void CEsamiView::AddFleuryFichaToEditBox(CString sFicha)
{
	int iArraySize = sizeof(m_arrayFleuryFichaItem) / sizeof(m_arrayFleuryFichaItem[0]);

	int iArrayLength = 0;
	for (int i = 0; i < iArraySize; i++)
		if (!m_arrayFleuryFichaItem[i].IsEmpty())
			iArrayLength++;

	BOOL bFichaExists = FALSE;
	for (int i = 0; i < iArraySize - 1; i++)
		if (m_arrayFleuryFichaItem[i] == sFicha)
			bFichaExists = TRUE;

	if (!bFichaExists)
	{
		if (iArrayLength < iArraySize)
		{
			m_arrayFleuryFichaItem[iArrayLength] = sFicha;
		}
		else
		{
			for (int i = 0; i < iArraySize - 1; i++)
				m_arrayFleuryFichaItem[i] = m_arrayFleuryFichaItem[i + 1];

			m_arrayFleuryFichaItem[iArraySize - 1] = sFicha;
		}

		m_ctrlEditFleuryFicha.RemoveSearchAll();
		for (int i = 0; i < iArraySize; i++)
		{
			if (!m_arrayFleuryFichaItem[i].IsEmpty())
				m_ctrlEditFleuryFicha.AddSearchString(m_arrayFleuryFichaItem[i]);
		}
	}
}

void CEsamiView::OnEnChangeEditFleuryEnterPressed()
{
	switch (theApp.m_lRicercaCodiceEsame)
	{
	case RICERCA_PAZIENTE_CONTATORE:
	{
		AddFleuryFichaToEditBox(m_sFleuryFicha);
		RicercaCodicePaziente(atol(m_sFleuryFicha), 0, FALSE, TRUE);
		MovePazientiAndEsami(NULL, TRUE, TRUE);
		break;
	}
	case RICERCA_PAZIENTE_CODESAME:
	{
		AddFleuryFichaToEditBox(m_sFleuryFicha);
		BOOL bOK = (RicercaCodicePazienteCodEsameEx(m_sFleuryFicha) > 0);
		MovePazientiAndEsami(NULL, !bOK, TRUE);
		break;
	}
	case RICERCA_PAZIENTE_ASSIDEN:
	{
		AddFleuryFichaToEditBox(m_sFleuryFicha);
		RicercaCodicePazienteAssiden(m_sFleuryFicha);
		MovePazientiAndEsami(NULL, TRUE, TRUE);
		break;
	}
	case RICERCA_PAZIENTE_CODICERICOVERO:
	{
		AddFleuryFichaToEditBox(m_sFleuryFicha);
		BOOL bOK = RicercaCodicePazienteCodiceRicovero(m_sFleuryFicha);
		MovePazientiAndEsami(NULL, !bOK, TRUE);
		break;
	}
	case RICERCA_PAZIENTE_FICHA:
	{
		CString sFicha = "";
		BOOL bAskBefore = TRUE;

		switch (m_sFleuryFicha.Trim().GetLength())
		{
		case 10:
		{
			BOOL bOK = TRUE;
			if (m_sFleuryItem.Trim().GetLength() == 0)
			{
				sFicha = m_sFleuryFicha;
				BOOL bOK = RicercaCodicePazienteCodiceRicovero(m_sFleuryFicha, FALSE);
				if (!bOK)
				{
					CString sErrore;
					CString sServer;
					CString sUO;
					CString sEndpointRemoteCommunication;
					long lArrayCount;

					sFicha = m_sFleuryFicha;

					if (FleuryCercaItensDaFicha(sFicha, sErrore, sServer, sUO, sEndpointRemoteCommunication, lArrayCount))
					{
						if (lArrayCount > 0)
						{
							long lArrayPos = 0;
							CString* sArray = new CString[lArrayCount];

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
							if (lArrayCount != 1)
							{
								CSelectNumeroFichaDlg selectDlg(this, sArray, lArrayCount);
								if (selectDlg.DoModal() == IDOK)
								{
									int iSpacePos = selectDlg.m_sSelectedFicha.Find(" ");
									sFicha = selectDlg.m_sSelectedFicha.Mid(0, iSpacePos).Trim();
									bAskBefore = FALSE;
								}
								else
								{
									sFicha = "";
								}
							}
							else
							{
								int iSpacePos = CString(sArray[0]).Find(" ");
								sFicha = CString(sArray[0]).Mid(0, iSpacePos).Trim();
								bAskBefore = FALSE;
							}
							sArray = NULL;
							delete(sArray);
						}
						else
						{
							sFicha = "";
							theApp.AfxMessageBoxEndo("Ficha não encontrada, por favor tente também usando um item");
						}
					}
					else
					{
						theApp.AfxMessageBoxEndo("Ficha não encontrada, por favor tente também usando um item");
					}
				}
				else
				{
					MovePazientiAndEsami(NULL, !bOK, TRUE);
					AddFleuryFichaToEditBox(sFicha.Trim());
					sFicha = "";
				}

				break;
			}
			else
			{
				for (int i = 0; i < 10; i++)
				{
					if (!isdigit(m_sFleuryFicha[i]))
					{
						bOK = FALSE;
						break;
					}
				}
				for (int i = 0; i < m_sFleuryItem.GetLength(); i++)
				{
					if (!isdigit(m_sFleuryItem[i]))
					{
						bOK = FALSE;
						break;
					}
				}
				if (bOK)
				{
					if (m_sFleuryItem.GetLength() >= 4)
					{
						m_sFleuryItem = m_sFleuryItem.Left(2);
					}
					else
					{
						m_sFleuryItem.Replace("0", "");
					}
					sFicha.Format("%s_%s_0", m_sFleuryFicha, m_sFleuryItem);
				}
			}
			break;
		}

		case 14:
		{
			BOOL bOK = TRUE;

			for (int i = 0; i < 14; i++)
			{
				if ((i == 10) || (i == 12))
				{
					if (m_sFleuryFicha[i] != '_')
					{
						bOK = FALSE;
						break;
					}
				}
				else
				{
					if (!isdigit(m_sFleuryFicha[i]))
					{
						bOK = FALSE;
						break;
					}
				}
			}

			if (bOK)
				sFicha = m_sFleuryFicha;

			break;
		}
		case 15:
		{
			BOOL bOK = TRUE;

			for (int i = 0; i < 15; i++)
			{
				if ((i == 10) || (i == 13))
				{
					if (m_sFleuryFicha[i] != '_')
					{
						bOK = FALSE;
						break;
					}
				}
				else
				{
					if (!isdigit(m_sFleuryFicha[i]))
					{
						bOK = FALSE;
						break;
					}
				}
			}

			if (bOK)
				sFicha = m_sFleuryFicha;

			break;
		}
		case 16:
		{
			BOOL bOK = TRUE;

			for (int i = 0; i < 16; i++)
			{
				if (!isdigit(m_sFleuryFicha[i]))
				{
					bOK = FALSE;
					break;
				}
			}

			if (bOK)
			{
				int iItem = atoi(m_sFleuryFicha.Mid(12, 2));
				if (iItem > 0)
					sFicha.Format("%s_%d_0", m_sFleuryFicha.Left(10), iItem);
			}

			break;
		}
		}

		if (!sFicha.IsEmpty())
		{
			OnFleuryCentralizacao(sFicha.Trim(), bAskBefore);
		}
		AddFleuryFichaToEditBox(sFicha.Trim());
		break;
	}
	}
	GetDlgItem(IDC_EDIT_FLEURYFICHA)->SetWindowText("");
	GetDlgItem(IDC_EDIT_FLEURYITEM)->SetWindowText("");
}

void CEsamiView::OnBnClickedBtnViewPacs()
{
	CString sAccessionNumber = "";
	switch (m_pEsamiSet->m_sCodEsame.GetLength())
	{
	case 14:
	{
		sAccessionNumber = m_pEsamiSet->m_sCodEsame.Left(10) + "000" + m_pEsamiSet->m_sCodEsame.Mid(11, 1) + "00";
		break;
	}
	case 15:
	{
		sAccessionNumber = m_pEsamiSet->m_sCodEsame.Left(10) + "00" + m_pEsamiSet->m_sCodEsame.Mid(11, 2) + "00";
		break;
	}
	default:
	{
		ASSERT(FALSE);

		sAccessionNumber = m_pEsamiSet->m_sCodEsame;
		break;
	}
	}

	// chiamata a carestream //
	CString sURL;
	//sURL.Format("https://pacs.fleury.com.br/?user_name=tesi&password=t$s!2016&accession_number=%s&signout=false&key_images=true", sAccessionNumber);
	sURL.Format(theApp.m_sHttpPathVisorPacsWeb, sAccessionNumber);

	if (!sURL.IsEmpty())
	{
		USES_CONVERSION;
		if (IsValidURL(NULL, T2W(sURL), 0) == S_OK)
		{
			CString sChromeExe = RegistryGetStringValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\chrome.exe", "");

			if (sChromeExe.IsEmpty())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CHROMENONTROVATO));

				ShellExecute(NULL, "open", sURL, NULL, NULL, SW_SHOWMAXIMIZED);
			}
			else
			{
				char szProcess[4096];
				sprintf_s(szProcess, "%s --app=\"%s\"", sChromeExe, sURL);

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
					LocalFree(lpMsgBuf);
				}
				else
				{
					CloseHandle(pi.hProcess);
					CloseHandle(pi.hThread);
				}
			}
		}
		else
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_URLNONVALIDA));
		}
	}
	else
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_URLNONASSOCIATA));
	}
}

// Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
void CEsamiView::LiberaLaudo()
{
	BeginWaitCursor();

	BOOL bExit = FALSE;

	if (!bExit)
	{
		if (theApp.m_bPersonalizzazioniBrasileFleury && !CRegioneSet().ExamHasPrestazioniNonNormate(m_pEsamiSet->m_lContatore))
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAME_ANNULLATO));
			bExit = TRUE;
		}
	}
	if (!bExit)
	{
		if (theApp.m_bChiusuraEsameSoloConPrestazioniPrincipali)
		{
			if (!CVistaEsamiConPrestazioniPrincipaliSet().TrovaEsame(m_pEsamiSet->m_lContatore))
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAME_NOPRESTAZIONIPRINCIPALI));
				bExit = TRUE;
			}
		}
	}
	if (!bExit)
	{
		if (theApp.m_bPersonalizzazioniBrasileFleury || theApp.m_lRicercaCodiceEsame == RICERCA_PAZIENTE_FICHA)
		{
			CString sErrore, sPlaceHolder;
			if (FleuryCercaFicha(m_pEsamiSet->m_sCodEsame, sErrore, sPlaceHolder, sPlaceHolder, sPlaceHolder))
			{
			}
			else
			{
				if (!sErrore.IsEmpty())
				{
					theApp.AfxMessageBoxEndo(sErrore);
				}
				theApp.AfxMessageBoxEndo(IDS_ESAME_ANNULLATO);
				bExit = TRUE;
			}
		}
	}
	if (!bExit)
	{
		if (theApp.m_bPersonalizzazioniBrasileFleury)
		{
			CString sMessaggio = "";
			BOOL bModifica = FleuryPossoModificare(sMessaggio, m_pEsamiSet->m_sRicovero, m_pEsamiSet->m_sCodEsame);
			if (!bModifica)
			{
				theApp.AfxMessageBoxEndo(sMessaggio);
				bExit = TRUE;
			}
		}
	}
	if (!bExit)
	{
		if (theApp.m_bPersonalizzazioniBrasileFleury)
		{
			if (CEsamiSet().IsConiugatoPrincipale(m_pEsamiSet->m_lContatore))
			{
				CString sFilterConiugato;
				sFilterConiugato.Format("CODESAME='%s'", m_pEsamiSet->m_sRefertoConiugatoSecondario);

				CEsamiSet setEsameConiugato;
				setEsameConiugato.SetBaseFilter("(UO=0 OR UO>0)");
				setEsameConiugato.SetOpenFilter(sFilterConiugato);

				if (setEsameConiugato.OpenRecordset("CEsamiView::ChiudiEsame"))
				{
					if (!setEsameConiugato.IsEOF())
					{
						CEsamiChiusiSet().InserisciRecord(setEsameConiugato.m_lContatore, -1, -1, GetUserIDForLockSuperlock(), "NW");
						CEsamiSet().ChiudiEsameIntegrato(setEsameConiugato.m_lContatore, m_sDataOraChiusura);
					}
					setEsameConiugato.CloseRecordset("CEsamiView::ChiudiEsame");
				}
			}
		}
		m_sDataOraChiusura = "";
		RicaricaDatiAssociatiAllEsame();
		MovePazientiAndEsami(NULL, FALSE, TRUE);
	}
	EndWaitCursor();
}

// Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
BOOL CEsamiView::RefertoPrincipale(long lContatore)
{
	// Luiz - 07/05/2019 - P3 - Desconjuga exames - ESAMIINTEGRATI
	BOOL bRetorno = FALSE;
	CString sFilter;
	CEsamiIntegratiSet setEsamiIntegrati;

	sFilter.Format("IDESAMEPRINCIPALE = '%d' AND ELIMINATO = 0", lContatore);
	setEsamiIntegrati.SetOpenFilter(sFilter);
	if (setEsamiIntegrati.OpenRecordset("CEsamiView::OnUpdateUIDesconjuga") && !setEsamiIntegrati.IsEOF())
		bRetorno = TRUE;

	setEsamiIntegrati.CloseRecordset("CEsamiView::OnUpdateUIDesconjuga");
	return bRetorno;
}

// Luiz - 18/07/2019 - P3 - Verifica presença de conjugação N-N ESAMIINTEGRATI
BOOL CEsamiView::RefertoPrincipaleSecondario(long lContatore)
{
	BOOL bRetorno = FALSE;
	CString sFilter;
	CEsamiIntegratiSet setEsamiIntegrati;

	sFilter.Format("(IDESAMEPRINCIPALE = '%d' OR IDESAMESECONDARIO = '%d') AND ELIMINATO = 0", lContatore, lContatore);
	setEsamiIntegrati.SetOpenFilter(sFilter);
	if (setEsamiIntegrati.OpenRecordset("CEsamiView::RefertoPrincipaleSecondario") && !setEsamiIntegrati.IsEOF())
		bRetorno = TRUE;

	setEsamiIntegrati.CloseRecordset("CEsamiView::RefertoPrincipaleSecondario");
	return bRetorno;
}

///Gabriel BUG 6303 - 12/01/2021 - Retorna a sigla do exame
CString CEsamiView::GetSiglaPrestazione()
{
	CString sReturn = "";

	CExtPrestazioniSet setPrest;

	CString sFilter;
	sFilter.Format("IDPRESTAZIONE LIKE '%s'", m_pEsamiSet->m_sCodEsame);
	setPrest.SetOpenFilter(sFilter);

	if (setPrest.OpenRecordset("CEsamiView::GetSiglaPrestazione"))
	{
		if (!setPrest.IsEOF())
			sReturn = setPrest.m_sCodicePrestazione;

		setPrest.CloseRecordset("CEsamiView::GetSiglaPrestazione");
	}

	return sReturn;
}

//Gabriel BUG 6225 - Lista DO
void CEsamiView::RefreshNumDocumentsExam()
{
	m_lNumDocumentsExam = m_pDocManager->GetAttachedDocNumberExam(m_pEsamiSet->m_lContatore, DOCUMENTS_NOT_EXPORT);
	m_lNumDocumentsExamCarestream = m_pDocManager->GetAttachedDocNumberExam(m_pEsamiSet->m_lContatore, DOCUMENTS_ONLY_EXPORT);
}

//Gabriel BUG 6225 - Lista DO
BOOL CEsamiView::BloccaEsameRiconvocazione()
{
	CString sFilter;
	CRiconvocazioneSet setRiconvocazione;

	sFilter.Format("IDESAME = %li AND ELIMINATO = 0 AND (BLOCCAESAME = 1 OR PASSIVODEREFERTO = 0)", m_pEsamiSet->m_lContatore);
	setRiconvocazione.SetOpenFilter(sFilter);

	if (setRiconvocazione.OpenRecordset("CEsamiView::EsameRiconvocato"))
	{
		if (!setRiconvocazione.IsEOF())
			return TRUE;

		setRiconvocazione.CloseRecordset("CEsamiView::EsameRiconvocato");
	}

	return FALSE;
}

void CEsamiView::OnEsameAllegatiCentralizzazione()
{
	CDocumentiDlg dlg(this, this, FALSE, FALSE, TRUE);
	dlg.DoModal();

	// Sandro 04/01/2014 // RAS 20130175 //
	RefreshNumDocumentsExam();//Gabriel BUG 6225 - Lista DO
}

//Gabriel - TCP
BOOL CEsamiView::IsTCP()
{
	CList<CString> sSiglasList;
	CString str = _T(theApp.m_sSiglasTCP);

	int nTokenPos = 0;
	CString strToken = str.Tokenize(_T(";"), nTokenPos);

	while (!strToken.IsEmpty())
	{
		sSiglasList.AddTail(strToken);
		strToken = str.Tokenize(_T(";"), nTokenPos);
	}

	for (int i = 0; i < sSiglasList.GetCount(); i++)
	{
		if (sSiglasList.GetAt(sSiglasList.FindIndex(i)) == GetSiglaPrestazione())
		{
			return TRUE;
			break;
		}
	}

	return FALSE;
}