#include "stdafx.h"
#include "Endox.h"
#include "EsamiDoc.h"

#include "DLL_Imaging\h\AmDes.h"
#include "DLL_Imaging\h\AMLogin.h"
#include "DLL_Imaging\h\AmRemoteStruct.h"
#include "DLL_Imaging\h\ImgArchive.h"

#include "AccessDlg.h"
#include "ArchiviBackupDlg.h"
#include "Common.h"
#include "ConfigurazioniInterfacceSet.h"
#include "ErroriEsterniSet.h"
#include "FasiEsameGruppiSet.h"
#include "GruppiSet.h"
#include "LockManager.h"
#include "PasswordDlg.h"
#include "PdfUtilInterface.h"
#include "RobotSet.h"
#include "SediEsameSet.h"
#include "SetupDlg.h"
#include "SetupServiziSet.h"
#include "SetupSet.h"
#include "UOSet.h"
#include "UOUtenteDlg.h"
#include "UOUtenteSet.h"
#include "UtentiSet.h"
#include "VistaGruppiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CEsamiDoc, CDocument)

BEGIN_MESSAGE_MAP(CEsamiDoc, CDocument)
END_MESSAGE_MAP()

CEsamiDoc::CEsamiDoc()
{
}

CEsamiDoc::~CEsamiDoc()
{
	m_PazientiSet.CloseRecordset("CEsamiDoc::~CEsamiDoc");
	m_EsamiSet.CloseRecordset("CEsamiDoc::~CEsamiDoc");

	CLockManager::Get()->Finalize();
}

BOOL CEsamiDoc::OnNewDocument()
{
	BOOL bReturn = TRUE;

	try
	{
		if (!CDocument::OnNewDocument())
			return FALSE;

		SetTitle("");

		theApp.DestroyAccessDialog();

		AMLogin_SetAvailableRights(AMLogin_Permissions::add_patient     |
		                           AMLogin_Permissions::modify_patient  |
		                           AMLogin_Permissions::delete_patient  |
		                           AMLogin_Permissions::add_exam        |
		                           AMLogin_Permissions::modify_exam     |
		                           AMLogin_Permissions::delete_exam     |
		                           AMLogin_Permissions::view_image      |
		                           AMLogin_Permissions::modify_image    |
		                           AMLogin_Permissions::view_report     |
		                           AMLogin_Permissions::modify_report   |
		                           AMLogin_Permissions::printout        |
		                           AMLogin_Permissions::exportout       |
		                           AMLogin_Permissions::statistics      |
		                           AMLogin_Permissions::configurations  |
								   AMLogin_Permissions::personalizable_01 | // amministratore del software //
								   AMLogin_Permissions::personalizable_03 | // fa vedere sempre tutti i tabs dell'esame //
								   //AMLogin_Permissions::personalizable_05 | // permette di CONVALIDARE l'esame //
								   AMLogin_Permissions::personalizable_06 | // attiva o meno l'accesso allo streaming //
								   AMLogin_Permissions::personalizable_07 | // consente di accedere a nomenclatore e statistiche esami //
								   //AMLogin_Permissions::personalizable_08 | // permette di CHIUDERE l'esame //
								   AMLogin_Permissions::personalizable_09 | // permette di accedere alle "sedi esterne" // RIMA 15135 //
								   AMLogin_Permissions::personalizable_10); // presonificação //
		AMLogin_SetPrivilegeDescription(AMLogin_Permissions::personalizable_01, theApp.GetMessageString(IDS_PERMISSION_ADMINISTRATION));
		AMLogin_SetPrivilegeDescription(AMLogin_Permissions::personalizable_03, theApp.GetMessageString(IDS_PERMISSION_PARTIALVIEW));
		//AMLogin_SetPrivilegeDescription(AMLogin_Permissions::personalizable_05, theApp.GetMessageString(IDS_PERMISSION_CONVALIDA_ESAME));
		AMLogin_SetPrivilegeDescription(AMLogin_Permissions::personalizable_06, theApp.GetMessageString(IDS_PERMISSION_STREAMING));
		AMLogin_SetPrivilegeDescription(AMLogin_Permissions::personalizable_07, theApp.GetMessageString(IDS_PERMISSION_STATISTICHE));
		//AMLogin_SetPrivilegeDescription(AMLogin_Permissions::personalizable_08, theApp.GetMessageString(IDS_PERMISSION_CHIUSURA_ESAME));
		AMLogin_SetPrivilegeDescription(AMLogin_Permissions::personalizable_09, theApp.GetMessageString(IDS_PERMISSION_SEDI_ESTERNE));
		AMLogin_SetPrivilegeDescription(AMLogin_Permissions::personalizable_10, theApp.GetMessageString(IDS_PERMISSION_PERSONIFICATION));

		// Sandro 21/02/2012 // leggo SOLO quello che serve ad AmLogin perché qui la UO è ancora 0 (zero) //
		LeggiConfigurazioneStep1();

		// Sandro 26/02/2013 // 
		if ((theApp.m_lMinIdRange <= 0) || (theApp.m_lMinIdRange > 99999999))
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_RECORDADDSP_ERROR1));
			bReturn = FALSE;
		}
		else
		{
			if ((theApp.m_lMaxIdRange <= theApp.m_lMinIdRange) || (theApp.m_lMaxIdRange > 99999999))
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_RECORDADDSP_ERROR2));
				bReturn = FALSE;
			}
		}

		//
		if (bReturn)
		{
			if (theApp.m_sPassedUsername.IsEmpty())
			{
				#ifdef _DEBUG	
					bReturn = AMLogin_Login(
								theApp.m_sUtenteLoggato,
								theApp.m_sNomeComputer,
								theApp.m_sNomeImpianto,
								"DEBUG_VERSION",
								&theApp.m_dbEndox,
								theApp.m_lLoginMode,
								theApp.m_sLoginServer,
								theApp.m_bLoginDropDomain,
								FALSE,
								tesiimaging);
				#else
					try
					{
						if (theApp.m_bConfigure) // Sandro 22/03/2010 - durante installazione di Endox //
							bReturn = TRUE;
						else
							bReturn = AMLogin_Login(
										theApp.m_sUtenteLoggato, 
										theApp.m_sNomeComputer, 
										theApp.m_sNomeImpianto, 
										theApp.GetMessageString(IDS_SYSTEM_ACCESS), 
										&theApp.m_dbEndox, 
										theApp.m_lLoginMode,
										theApp.m_sLoginServer,
										theApp.m_bLoginDropDomain,
										FALSE,
										tesiimaging);
					}
					catch(...)
					{
						theApp.AfxMessageBoxEndo("AmLogin");
					}
				#endif
			}
			else
			{
				bReturn = AMLogin_Login_Auto(
					theApp.m_sPassedUsername,
					theApp.m_sPassedPassword,
					theApp.m_sNomeComputer,
					theApp.m_sNomeImpianto,
					theApp.GetMessageString(IDS_SYSTEM_ACCESS),
					&theApp.m_dbEndox,
					theApp.m_lLoginMode,
					theApp.m_sLoginServer,
					theApp.m_bLoginDropDomain,
					tesiimaging
					);
			}
		}		

		if (bReturn)
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
						while(!setUOUtente.IsEOF())
						{
							setUOUtente.DeleteRecordset("CEsamiDoc::OnNewDocument");
							setUOUtente.MoveNext();
						}

						setUOUtente.CloseRecordset("CEsamiDoc::OnNewDocument");
					}

					POSITION posGroups = listGroups.GetHeadPosition();
					while(posGroups != NULL)
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
						while(!setUOUtente.IsEOF())
						{
							setUOUtente.DeleteRecordset("CEsamiDoc::OnNewDocument");
							setUOUtente.MoveNext();
						}

						setUOUtente.CloseRecordset("CEsamiDoc::OnNewDocument");
					}

					POSITION posGroups = listGroups.GetHeadPosition();
					while(posGroups != NULL)
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

			if (theApp.m_bConfigure)
			{
				theApp.m_lUO = 1;
			}
			else if (theApp.m_bCentraleStampa) // Sandro 15/11/2016 //
			{
				theApp.m_lUO = 26;
			}
			else
			{
				// Sandro 21/04/2017 // BUG 390 //
				theApp.m_lUO = CUOSet().GetIDFromDescrizione(theApp.m_sPassedUO);

				//
				if (theApp.m_lUO <= 0)
				{
					CUOUtenteDlg dlg(NULL, lUserID);
					dlg.DoModal();
				}
			}

			if (theApp.m_lUO <= 0)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_NESSUNA_UO));
				theApp.m_lIDEsameFirmaDisattivata = 0;
				AMLogin_Logout();
				theApp.m_lUO = 0; // Sandro 16/11/2015 // RAS 201500080 //
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

				//
				if (!LeggiConfigurazioniEImpostaSoftware())
					return FALSE;

				//

				//16052 Simone - Carico la lista dei gruppi a cui appartiene l'utente e i privilegi sulle fasi. Deve essere fatto qui per il FleuryUserCodeCheck() del cazzo
				LoadUserGroups();
				LoadEnabledPhaseForUser();

				//Julio Login SEGU
				if (theApp.m_bPersonalizzazioniBrasileFleury && (theApp.m_sUtenteLoggato != "SAT") && (theApp.m_sUtenteLoggato != "ADMINISTRATOR") && !FleuryGetHealthProfessional() /*!FleuryUserCodeCheck()*/)
					return FALSE;										
				
			}
		}
		else
		{
			theApp.m_lIDEsameFirmaDisattivata = 0;
			AMLogin_Logout();
			theApp.m_lUO = 0; // Sandro 16/11/2015 // RAS 201500080 //
		}

		CLockManager::Get()->Initialize();

		if (!CLockManager::Get()->LockUser(theApp.m_sUtenteLoggato))
		{
			theApp.DestroyAccessDialog();
			return FALSE;
		}
	}
	catch(CDBException* pEx)
	{
		theApp.DestroyAccessDialog();

		pEx->ReportError();
		pEx->Delete();		

		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAMIDOC_ERR_CONFIG_APP));

		if (CPasswordDlg(NULL, theApp.GetMessageString(IDS_PASSWORD_DATABASE), "1qaz2wsx3edc").DoModal() == IDOK)
			Amdbx_ConfigDatabase(theApp.m_sFileConfig);

		return FALSE;
	}

	if (bReturn && !theApp.m_pAccessWnd)
		theApp.m_pAccessWnd = new CAccessDlg;	

	return bReturn;
}

void CEsamiDoc::OnCloseDocument()
{
	CLockManager::Get()->UnlockUser(theApp.m_sUtenteLoggato);

	if (theApp.m_lUO > 0)
	{
		// SetBoolValue("Pazienti UsaVista", theApp.m_bPazientiUsaVista);
		SetStringValue("Pazienti Tabella", theApp.m_sPazientiTabella);
		// SetStringValue("Pazienti Vista", theApp.m_sPazientiVista);
		// SetStringValue("Pazienti Vista Ordinamento", theApp.m_sPazientiVistaOrdinamento);

		// Sandro 28/02/2014 //
		// SetStringValue("Percorso allegati paziente", theApp.m_sPercorsoAllegatiPaz);
		// SetStringValue("Percorso allegati esame", theApp.m_sPercorsoAllegatiEsa);
		// SetStringValue("Percorso PDF", theApp.m_sPercorsoPDF);
	}

	CDocument::OnCloseDocument();
}

BOOL CEsamiDoc::LeggiConfigurazioniEImpostaSoftware()
{
	// Sandro 21/02/2012 // ora che la UO è impostata correttamente leggo tutto il resto dalla tabella "Configurazioni" //
	LeggiConfigurazioneStep2();

	// Sandro 21/02/2012 // ora che la UO è impostata correttamente leggo tutto dalla tabella "ConfigurazioniInterfacce" //
	LeggiConfigurazioneStep3();

	// Sandro 26/01/2014 // RAS 20130198 // se non criptata, cripto la password per la cancellazione dei pdf //
	if (!theApp.m_bPdfEliminazionePasswordCriptata)
	{
		char szCryptedPasswordTemp[255];
		if (AmDes_Crypt(szCryptedPasswordTemp, 254, theApp.m_sPdfEliminazionePassword))
		{
			CString sTemp = szCryptedPasswordTemp;
			theApp.m_bPdfEliminazionePasswordCriptata = TRUE;

			SetBoolValue("PDF - Eliminazione - Password criptata", theApp.m_bPdfEliminazionePasswordCriptata);
			SetStringValue("PDF - Eliminazione - Password", sTemp);
		}
	}
	else
	{
		char szDecryptedPasswordTemp[255];
		if (AmDes_Decrypt(szDecryptedPasswordTemp, 254, theApp.m_sPdfEliminazionePassword.GetBuffer(), theApp.m_sPdfEliminazionePassword.GetLength()))
		{
			theApp.m_sPdfEliminazionePassword.ReleaseBuffer();
			theApp.m_sPdfEliminazionePassword = szDecryptedPasswordTemp;
		}
		else
		{
			theApp.m_sPdfEliminazionePassword.ReleaseBuffer();
		}
	}

	// Sandro 24/11/2014 //

	CErroriEsterniSet setEE;
	setEE.SetOpenFilter("Errore<>0");
	if (setEE.OpenRecordset("CEsamiDoc::OnNewDocument"))
	{
		CString sErrore = "";

		while (!setEE.IsEOF())
		{
			if (!sErrore.IsEmpty())
				sErrore += "\n";

			CString sServizio = "";
			switch (setEE.m_lIDServizio)
			{
				case 1:
				{
					sServizio = "EndoxServer";
					break;
				}
				default:
				{
					ASSERT(FALSE);

					sServizio.Format("%li", setEE.m_lIDServizio);
					break;
				}
			}
			sErrore += sServizio + " --> " + setEE.m_sMessaggio;

			setEE.MoveNext();
		}

		setEE.CloseRecordset("CEsamiDoc::OnNewDocument");

		TRACE(sErrore + "\n");
#ifndef _DEBUG
		if (!sErrore.IsEmpty())
			theApp.MessageBoxEndo(sErrore);
#endif
	}

	/////////////////////////////////////////////////////////////////////////
	// Sandro 11/04/2012 // verifico che TUTTI i percorsi siano scrivibili //
	/////////////////////////////////////////////////////////////////////////

	BOOL bAccessError = FALSE;
	BOOL bOpenPathConfig = FALSE;

	// cartella di Endox //
	if (VerificaPercorsoSistemaEndox(theApp.m_sDirProg))
	{
		if (!VerificaPercorsoSpazioLibero(theApp.m_sDirProg))
			bAccessError = TRUE;
	}
	else
	{
		bAccessError = TRUE;
	}

	// cartella TEMP //
	if (VerificaPercorsoSistemaEndox(theApp.m_sDirTemp))
	{
		if (!VerificaPercorsoSpazioLibero(theApp.m_sDirTemp))
			bAccessError = TRUE;
	}
	else
	{
		bAccessError = TRUE;
	}

	// Sandro 20/10/2016 //
	if (!theApp.m_bCentraleStampa)
	{
		// percorso immagini //
		char szPathImm[MAX_PATH];
		char szPathMin[MAX_PATH];
		if (CImgArchive(&theApp.m_dbEndox).GetArchivePrimary(szPathImm, szPathMin, MAX_PATH))
		{
			if (VerificaPercorsoSistemaEndox(szPathImm))
			{
				if (!VerificaPercorsoSpazioLibero(szPathImm))
				{
					bAccessError = TRUE;
					bOpenPathConfig = TRUE;
				}
			}
			else
			{
				bAccessError = TRUE;
				bOpenPathConfig = TRUE;
			}
		}
		else
		{
			theApp.AfxMessageBoxEndo(IDS_NESSUN_ARCHIVIO_PRIMARIO, MB_ICONSTOP);

			bAccessError = TRUE;
			bOpenPathConfig = TRUE;
		}

		// percorso PDF //
		if (!theApp.m_sPercorsoPDF.IsEmpty())
		{
			if (theApp.m_sPercorsoPDF.CompareNoCase(szPathImm) != 0)
			{
				if (VerificaPercorsoSistemaEndox(theApp.m_sPercorsoPDF))
				{
					if (!VerificaPercorsoSpazioLibero(theApp.m_sPercorsoPDF))
					{
						bAccessError = TRUE;
						bOpenPathConfig = TRUE;
					}
				}
				else
				{
					bAccessError = TRUE;
					bOpenPathConfig = TRUE;
				}
			}
		}

		// percorso allegati paziente //
		if (!theApp.m_sPercorsoAllegatiPaz.IsEmpty())
		{
			if (theApp.m_sPercorsoAllegatiPaz.CompareNoCase(szPathImm) != 0)
			{
				if (VerificaPercorsoSistemaEndox(theApp.m_sPercorsoAllegatiPaz))
				{
					if (!VerificaPercorsoSpazioLibero(theApp.m_sPercorsoAllegatiPaz))
					{
						bAccessError = TRUE;
						bOpenPathConfig = TRUE;
					}
				}
				else
				{
					bAccessError = TRUE;
					bOpenPathConfig = TRUE;
				}
			}
		}

		// percorso allegati esame //
		if (!theApp.m_sPercorsoAllegatiEsa.IsEmpty())
		{
			if (theApp.m_sPercorsoAllegatiEsa.CompareNoCase(szPathImm) != 0)
			{
				if (VerificaPercorsoSistemaEndox(theApp.m_sPercorsoAllegatiEsa))
				{
					if (!VerificaPercorsoSpazioLibero(theApp.m_sPercorsoAllegatiEsa))
					{
						bAccessError = TRUE;
						bOpenPathConfig = TRUE;
					}
				}
				else
				{
					bAccessError = TRUE;
					bOpenPathConfig = TRUE;
				}
			}
		}

		// verifico la presenza della cartella RGL, se necessario //
		if (theApp.m_bInterfacciaMetafora || (theApp.m_lInterfacciaPathox > 0))
		{
			if (!VerificaPercorsoSistemaEndox(theApp.m_sDirProg + "\\RGL"))
				bAccessError = TRUE;
		}

		// Sandro 01/04/2015 //
		if (!CPdfUtilInterface::Get()->Verify())
		{
			bAccessError = TRUE;
			bOpenPathConfig = FALSE;
		}

		//Simone 18/07/2016 - RIMA 16095
		theApp.m_bRobotAttivo = FALSE;

		CRobotSet robotSet;
		if (robotSet.OpenRecordset("CEsamiDoc::OnNewDocument"))
		{
			if (!robotSet.IsEOF())
				theApp.m_bRobotAttivo = TRUE;

			robotSet.CloseRecordset("CEsamiDoc::OnNewDocument");
		}
	}
	//

	// EndoxPro.cfg //
	if (!WritePrivateProfileString(szSettings, "ProvaSolaLettura", "Prova1234567890", theApp.m_sFileConfig) || !WritePrivateProfileString(szSettings, "ProvaSolaLettura", "ProvaProvaProva", theApp.m_sFileConfig))
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PERCORSO_CFG), MB_ICONSTOP);
		bAccessError = TRUE;
	}

	if (bOpenPathConfig)
	{
		if (CPasswordDlg(NULL, theApp.GetMessageString(IDS_PASSWORD_PERCORSI), "1qaz2wsx3edc").DoModal() == IDOK)
			CArchiviBackupDlg(NULL, this).DoModal();
	}

	//
	return !bAccessError;
}

void CEsamiDoc::LeggiConfigurazioneStep1()
{
	// leggo SOLO quello che serve ad AmLogin perché qui la UO è ancora 0 (zero) // 

	GetBoolValue("Stampa immagini - Usa header e footer per UO", theApp.m_bStampaImmaginiUsaHFPerUO); // Sandro 26/10/2015 //

	GetBoolValue("UO - Visualizza", theApp.m_bUOVisualizzaAngoloAltoDestra);

	GetLongValue("Login - Mode", theApp.m_lLoginMode);
	GetBoolValue("Disabilita inserimento esami pazienti senza assiden", theApp.m_bDisabilitaEsamiPazientiSenzaAssiden);
	GetLongValue("MaxIdRange", theApp.m_lMaxIdRange);
	GetLongValue("MinIdRange", theApp.m_lMinIdRange);

	GetStringValue("Login - Server", theApp.m_sLoginServer);
	GetStringValue("Nome impianto", theApp.m_sNomeImpianto);

	GetBoolValue("Login - Rimuovi dominio", theApp.m_bLoginDropDomain);

	GetBoolValue("Centrale di stampa", theApp.m_bCentraleStampa);
	GetLongValue("Centrale di stampa - Codice unita", theApp.m_lCentraleStampaCodiceUnita);

	GetStringValue("Codice unita Fleury", theApp.m_sCodiceUnitaFleury);
	if (theApp.m_sCodiceUnitaFleury.IsEmpty())
		theApp.AfxMessageBoxEndo(IDS_CODICEUNITA_VUOTO);

	GetBoolValue("No coniugazione", theApp.m_bNoConiugazione);

	GetStringValue("Percorso allegati paziente", theApp.m_sPercorsoAllegatiPaz);

	GetBoolValue("Text control - copia incolla rimuovi formattazione", theApp.m_bTextControlCopiaIncollaRimuoviFormattazione);
	GetBoolValue("Ricerca UO limitata", theApp.m_bRicercaUOLimitata); // Luiz 08/02/2019 - P3 - Dependendo da Configuração (Ricerca UO limitata), impedir que itens de outra especialidade na conjugacao 
	//GetBoolValue("Confermare Gli Esami Senza Attaccamento O Immagini", theApp.m_bConfermareGliEsamiSenzaAttaccamentoOImmagini); // Luiz 11/02/2019 - P3 - Dependendo da Configuração (Confermare Gli Esami Senza Attaccamento O Immagini), confirma salvar/assinar exames sem anexos ou imagens 
	GetBoolValue("Fase Extra Amarrado Ao Superlock", theApp.m_bFaseExtraAmarradoAoSuperlock); // Luiz 27/03/2019 - P3 - Dependendo da Configuração (Fase Extra Amarrado Ao Superlock), obriga que seja realizada sequencia salvar/assinar antes de protocolar e desfazer protocolar antes de desfazer salvar/assinar
	//

	CConfigurazioniInterfacceSet setInterfacce;
	setInterfacce.GetBoolValue("Vital Sign - Integrazione attiva", theApp.m_bVitalSignIntegrazioneAttiva);
	setInterfacce.GetStringValue("Vital Sign - Webservice endpoint", theApp.m_sVitalSignWebServiceEndpoint);
}

void CEsamiDoc::LeggiConfigurazioneStep2()
{
	BOOL bFalse = FALSE;
	GetBoolValue("DisableTriggersLog", bFalse);

	// --- //
	GetBoolValue("Confermare Gli Esami Senza Attaccamento O Immagini", theApp.m_bConfermareGliEsamiSenzaAttaccamentoOImmagini); // Luiz 11/02/2019 - P3 - Dependendo da Configuração (Confermare Gli Esami Senza Attaccamento O Immagini), confirma salvar/assinar exames sem anexos ou imagens 
	GetBoolValue("Album immagini - Old mode", theApp.m_bOldAlbumMode);
	GetBoolValue("Album immagini - Usa lista commenti", theApp.m_bAlbumImmaginiUsaListaCommenti);
	GetBoolValue("Album immagini - Commento non editabile", theApp.m_bAlbumImmaginiCommentoNonEditabile);
	GetBoolValue("Archivio Immagini - Thread Import", theApp.m_bArchivioImmaginiThreadImport);
	GetBoolValue("Assiden Key", theApp.m_bAssidenKey);
	GetBoolValue("Centrale controllo qualità", theApp.m_bCentraleControlloQualita);
	GetBoolValue("Centrale di refertazione", theApp.m_bCentraleRefertazione);
	GetBoolValue("Checklist - Click elemento seleziona check", theApp.m_bCheckListClickElementoSeleziona);
	GetBoolValue("Checklist - Componi sequenzialmente", theApp.m_bCheckListComponiSequenzialmente);
	// GetBoolValue("Checklist - Salva selezione", theApp.m_bCheckListSalvaSelezione);
	GetBoolValue("Chiusura esame - Accoda stampa immagini", theApp.m_bChiusuraEsameAccodaStampaImmagini);
	GetBoolValue("Chiusura esame - Doppia conferma", theApp.m_bChiusuraEsameDoppiaConferma);
	GetBoolValue("Chiusura esame - Logout automatico", theApp.m_bChiusuraEsameLogoutAuto);
	GetBoolValue("Chiusura esame - Permetti solo con prestazioni principali", theApp.m_bChiusuraEsameSoloConPrestazioniPrincipali);
	GetBoolValue("Chiusura programma - Conferma", theApp.m_bChiusuraProgrammaConferma);
	GetBoolValue("Codifica regionale - Elimina duplicati", theApp.m_bCodificaRegionaleEliminaDuplicati);
	GetLongValue("Controllo qualita - Percentuale", theApp.m_lControlloQualitaPercentuale);
	GetStringValue("Controllo qualita - Unidade", theApp.m_sControlloQualitaUnidade);
	GetStringValue("Controllo qualita - Regional", theApp.m_sControlloQualitaRegional);
	GetStringValue("Controllo qualita - Marca", theApp.m_sControlloQualitaMarca);
	GetBoolValue("Demo Aliar", theApp.m_bDemoAliar);
	GetBoolValue("Dermox - Acquisizione diretta", theApp.m_bDermoxAcquisizioneDiretta);
	GetBoolValue("Dermox - Acq diretta mantieni copia backup", theApp.m_bDermoxAcqDirettaMantieniCopiaBackup);
	GetBoolValue("Dermox - Mostra calibrazione", theApp.m_bDermoxMostraCalibSuAlbum);	
	GetBoolValue("Disattiva frecce spostamento pazienti", theApp.m_bDisattivaFrecceSpostamentoPazienti);
	GetBoolValue("Inserisci prenotazione in salvataggio esame", theApp.m_bInserisciPrenotazione);
	GetBoolValue("Integrazione PACS - Attiva", theApp.m_bIntegrazionePacsAttiva);
	GetBoolValue("Integrazione PACS - Sincrona", theApp.m_bIntegrazionePacsSincrona);
	GetBoolValue("Interfaccia DMS", theApp.m_bInterfacciaDMS);
	GetBoolValue("Interfaccia Metafora", theApp.m_bInterfacciaMetafora);
	GetBoolValue("Interfaccia WinlabWEB", theApp.m_bInterfacciaWeb);
	GetBoolValue("Istopatologia - Mostra lettera", theApp.m_bIstopatologiaMostraLettera);
	GetBoolValue("Lock Server Attivo", theApp.m_bLockServerAttivo);
	GetBoolValue("Login Multiplo Utente", theApp.m_bLoginMultiploUtente);
	GetBoolValue("Medici - Attiva descrizione libera", theApp.m_bMediciDescrizioneLibera);
	GetBoolValue("Mostra codice esame", theApp.m_bMostraCodiceEsame);
	GetBoolValue("Mostra menu databases remoti", theApp.m_bMostraMenuDatabasesRemoti);
	GetBoolValue("Mostra numero esami per sede", theApp.m_bMostraNumeroEsamiPerSede);
	GetBoolValue("Mostra paziente in cura dal direttore", theApp.m_bMostraPazienteInCuraDalDirettore);
	GetBoolValue("Mostra secondo cognome", theApp.m_bMostraSecondoCognome);
	GetBoolValue("Mostra solo anno - Interventi chirurgici", theApp.m_bMostraSoloAnnoInterventiChirurgici);
	GetBoolValue("Mostra solo anno - Interventi endoscopici", theApp.m_bMostraSoloAnnoInterventiEndoscopici);
	GetBoolValue("Mostra tasto unificazione anagrafiche", theApp.m_bMostraTastoUnificazioneAnagrafiche);
	GetBoolValue("NominativoSuExportImmagini", theApp.m_bNominativoSuExportImmagini);
	GetBoolValue("NumeriSuImmaginiAlbum", theApp.m_bNumeriSuImmaginiAlbum);
	GetBoolValue("NumeriSuImmagineSagoma", theApp.m_bNumeriSuImmagineSagoma);
	GetBoolValue("Paziente interno", theApp.m_bPazienteInternoDefault);
	// GetBoolValue("Pazienti UsaVista", theApp.m_bPazientiUsaVista);
	GetBoolValue("PDF - Eliminazione - Password criptata", theApp.m_bPdfEliminazionePasswordCriptata);
	GetBoolValue("PDF Immagini", theApp.m_bPDFImmaginiCrea);
	GetBoolValue("PDF - Immagini non compresse", theApp.m_bPDFImmaginiNonCompresse);
	GetBoolValue("PDF - Incorpora fonts", theApp.m_bPDFIncorporaFonts);
	GetBoolValue("PDF - Inibita copia", theApp.m_bPDFInibisciCopia);
	GetBoolValue("PDF - Inibita stampa", theApp.m_bPDFInibisciStampa);
	GetBoolValue("PDF - Non protetti", theApp.m_bPDFNonProtetti);
	GetBoolValue("Ativa TCP", theApp.m_bAtivaTCP); //BUG 9527 - Felipe (NewTCP)
	GetBoolValue("Personalizzazioni Brasile Camargo", theApp.m_bPersonalizzazioniBrasileCamargo);
	GetBoolValue("Personalizzazioni Brasile Einstein", theApp.m_bPersonalizzazioniBrasileEinstein);
	GetBoolValue("Personalizzazioni Brasile Fleury", theApp.m_bPersonalizzazioniBrasileFleury);
	GetBoolValue("Personalizzazioni Brasile Sirio", theApp.m_bPersonalizzazioniBrasileSirio);
	GetBoolValue("Prenotazioni CUP", theApp.m_bPrenotazioniCup);
	GetLongValue("Prenotazioni CUP - Focus", theApp.m_lPrenotazioniCupFocus);
	GetBoolValue("Prenotazioni DICOM", theApp.m_bPrenotazioniDicom);
	GetBoolValue("Progressivo esame - Per sede", theApp.m_bProgressivoEsamePerSede);
	GetBoolValue("Refertazione - Logout automatico", theApp.m_bRefertazioneLogoutAuto);
	GetBoolValue("Refertazione - Usa checklist", theApp.m_bRefertazioneUsaChecklist);
	GetBoolValue("Refertazione - Usa frasi RTF", theApp.m_bRefertazioneUsaFrasiRTF);
	GetBoolValue("Refertazione - Usa frasi standard", theApp.m_bRefertazioneUsaFrasiStandard);
	GetBoolValue("Riapertura esame - Solo amministratore", theApp.m_bRiaperturaEsameSoloAmministratore);
	GetBoolValue("Ricerca - Chiedi conteggio", theApp.m_bRicercaChiediConteggio);
	GetBoolValue("Ricerca - Chiedi solo pazienti", theApp.m_bRicercaChiediSoloPazienti);
	GetBoolValue("Ricetta per AP", theApp.m_bRicettaPerAP);
	GetBoolValue("Ricetta per AP - PSM", theApp.m_bRicettaPerAP_psm);
	GetBoolValue("Ricetta - Codici a barre obbligatori", theApp.m_bRicettaCodebarObbligatori);
	GetBoolValue("Salva solo ultime immagini stampate", theApp.m_bSalvaSoloUltimeImmaginiStampate);
	GetBoolValue("Sospesi istologici - Nascondi verificati", theApp.m_bSospesiIstologiciNascondiVerificati);
	GetBoolValue("Stampa bordi neri", theApp.m_bStampaBordiNeriImmagini);
	GetBoolValue("Stampa commento dentro", theApp.m_bStampaCommentoDentroImmagini);
	GetBoolValue("Stampa immagini - Stampa commenti", theApp.m_bStampaImmaginiStampaCommenti);
	GetBoolValue("Stampa immagini - Stampa dati paziente", theApp.m_bStampaImmaginiStampaDatiPaziente);
	GetBoolValue("Stampa immagini - Stampa numero", theApp.m_bStampaImmaginiStampaNumero);
	GetBoolValue("Stampa - Selezione automatica immagini stampate", theApp.m_bStampaSelezionaAutomaticaImmaginiStampate);
	GetBoolValue("Storico Imago", theApp.m_bStoricoImago);
	GetBoolValue("Tasto stampa report - Stampa sempre", theApp.m_bTastoStampaReportStampaSempre);
	GetBoolValue("Usa Prontuario", theApp.m_bUsaProntuario);

	GetBoolValue("Int Gestione ordini acquisiti", theApp.m_bIntegrazioneGestioneRichiesteAcquisite);
	GetBoolValue("Int Invio immagini binarie", theApp.m_bIntegrazioneInvioImmaginiBinarie);
	GetBoolValue("Int Invio referti annullati", theApp.m_bIntegrazioneInvioRefertiAnnullati);
	GetBoolValue("Int Invio referti del filler", theApp.m_bIntegrazioneInvioRefertiDalFiller);

	//

	GetBoolValue("Attiva Ricoveri", theApp.m_bAttivaRicoveri);
	GetBoolValue("Attiva Pronto Soccorso", theApp.m_bAttivaPS);
	
	GetBoolValue("Monitoraggio - Mostra score", theApp.m_bMostraScoreMonitoraggio);
	GetBoolValue("Monitoraggio - Usa Score Di Glasgow", theApp.m_bUsaScoreDiGlasgow);

	GetFloatValue("Soglia Breath Test HP", theApp.m_fSogliaBreathTestHP);

	//

	GetIntValue("Archivio Immagini - Formato", theApp.m_nArchivioImmaginiFormato);
	GetIntValue("Archivio Immagini - Qualita", theApp.m_nArchivioImmaginiQualita);
	GetIntValue("Archivio Immagini - Soglia avviso", theApp.m_nArchivioImmaginiSogliaAvviso);
	GetIntValue("Archivio Immagini - Soglia blocco", theApp.m_nArchivioImmaginiSogliaBlocco);
	GetIntValue("Archivio Miniature - Qualita", theApp.m_nArchivioMiniatureQualita);
	GetIntValue("Formato pagina", theApp.m_nFormatoPagina);
	GetIntValue("Stampa immagini - Distanza immagini", theApp.m_nStampaImmaginiDistanzaImmagini);
	GetIntValue("Stampa immagini - Tipo di stampa", theApp.m_nStampaImmaginiTipoDiStampa);
	GetIntValue("TESIATDNET - Porta", theApp.m_nTesiAtdNetPorta);

	//

	GetLongValue("Backup DVD", theApp.m_lBackupDVD);
	GetLongValue("Blocco referto", theApp.m_lBloccoReferto);
	GetLongValue("Chiusura esame - Ritardo invio (ore)", theApp.m_lChiusuraEsameRitardoInvioOre);
	GetLongValue("Chiusura esame - Ritardo invio (minuti)", theApp.m_lChiusuraEsameRitardoInvioMinuti);
	GetLongValue("Codifica regionale - Mostra codice", theApp.m_lCodificaRegionaleMostraCodice);
	GetLongValue("Countdown - Partenza", theApp.m_lCountdownPartenza);
	GetLongValue("Interfaccia Pathox", theApp.m_lInterfacciaPathox);
	GetLongValue("Modalita caricamento valori default", theApp.m_lModalitaCaricamentoCampiDefault);
	GetLongValue("Modifica referto", theApp.m_lModificaReferto);
	GetLongValue("Mostra età paziente", theApp.m_lMostraEtaPaziente);
	GetLongValue("Numero stampante immagini", theApp.m_lIDStampanteImmagini);
	GetLongValue("OPZIONALE - Pazienti cronici", theApp.m_lOpzionalePazientiCronici);
	GetLongValue("PDF - Qualita immagini compresse", theApp.m_lPDFQualitaImmaginiCompresse);
	GetLongValue("Pressione minima - Valore minimo", theApp.m_lPressioneMinimaValoreMinimo);
	GetLongValue("Pressione minima - Valore massimo", theApp.m_lPressioneMinimaValoreMassimo);
	GetLongValue("Pressione massima - Valore minimo", theApp.m_lPressioneMassimaValoreMinimo);
	GetLongValue("Pressione massima - Valore massimo", theApp.m_lPressioneMassimaValoreMassimo);
	GetLongValue("Referto - Allineamento testo default", theApp.m_lRefertoAllineamentoTestoDefault);
	GetBoolValue("Referto - Marca Variabili Annullati", theApp.m_bRefertoMarcaVariabiliAnnullati);	
	GetLongValue("Ricerca - Codice esame", theApp.m_lRicercaCodiceEsame);
	GetLongValue("Ricetta - Max Items", theApp.m_lRicettaMaxItems);
	GetLongValue("Stampa immagini - ID Header", theApp.m_lStampaImmaginiIDHeaderGlobal);
	GetLongValue("Stampa immagini - ID Footer", theApp.m_lStampaImmaginiIDFooterGlobal);
	GetStringValue("Stampa immagini - Sigle per Stampa Orizzontale", theApp.m_sStampaImmaginiSiglePerStampaOrizzontale); //Gabriel BUG 6303
	GetStringValue("Sperma esame - Sigle per Generazione de Grafici", theApp.m_sSpermaEsameSiglePerGenerazioneGrafici); //Gabriel BUG 5533

	GetLongValueServizi("LockListenPort", theApp.m_lLockServerPorta);

	//

	GetStringValue("BarCode Font Name", theApp.m_sBarCodeFontName);
	GetStringValue("Controllo ortografico - Path dizionario utente", theApp.m_sControlloOrtograficoPathDizionarioUtente);
	GetStringValue("Emissione Referto Url", theApp.m_sEmissioneRefertoUrl);
	GetStringValue("Esporta filmati per visore web su path", theApp.m_sEsportaFilmatiPerVisoreWebSuPath);
	GetStringValueServizi("LockListenServer", theApp.m_sLockServerIndirizzo);	
	GetStringValue("Nome programma", theApp.m_sNomeProgramma);
	GetStringValue("Nome programma - Certificazione", theApp.m_sNomeProgrammaCertificazione);
	GetStringValue("Pazienti Tabella", theApp.m_sPazientiTabella);
	// GetStringValue("Pazienti Vista", theApp.m_sPazientiVista);
	// GetStringValue("Pazienti Vista Ordinamento", theApp.m_sPazientiVistaOrdinamento);
	GetStringValue("PDF - Eliminazione - Password", theApp.m_sPdfEliminazionePassword);
	
	GetStringValue("Percorso allegati esame", theApp.m_sPercorsoAllegatiEsa);
	GetStringValue("Percorso PDF", theApp.m_sPercorsoPDF);
	GetStringValue("Percorso reports consenso informato", theApp.m_sPercorsoReportsConsensoInformato);
	GetStringValue("QueryMan", theApp.m_sQueryMan);
	GetStringValue("TESIATDNET - Indirizzo", theApp.m_sTesiAtdNetIndirizzo);
	GetStringValue("Testi concatenati - Separatore", theApp.m_sTestiConcatenatiSeparatore);
	GetStringValue("Note reperibilita default", theApp.m_sNoteReperibilitaDefault);

	GetBoolValue("Fleury - Programa consulta novo", theApp.m_bFleuryProgrammaConsultaNuovo);

	//

	GetLongValue("Firma digitale", (long&)theApp.m_enumFirmaDigitale);
	GetBoolValue("Firma digitale - Debug", theApp.m_bFirmaDigitaleDebug);
	GetBoolValue("Firma digitale - Chiudi Comped", theApp.m_bFirmaDigitaleChiudiComped);
	GetBoolValue("Firma digitale - Mostra anteprima", theApp.m_bFirmaDigitaleAnteprimaMostra);
	GetBoolValue("Firma digitale - Smartcard = Medico 1", theApp.m_bFirmaDigitaleSmartcardUgualeMedico1);
	GetBoolValue("Firma digitale - Smartcard = Utente Endox", theApp.m_bFirmaDigitaleSmartcardUgualeUtenteEndox);
	GetLongValue("Firma digitale - Stampa", theApp.m_lFirmaDigitaleStampa);
	GetStringValue("Firma digitale - Templates Path", theApp.m_sFirmaDigitaleTemplatesPath);
	GetStringValue("Firma digitale - Report annullamento", theApp.m_sFirmaDigitaleReportAnnullamento);
	GetBoolValue("Siss - richiedi marca temporale", theApp.m_bSISSRichiediMarcaTemporale);
	GetBoolValue("Siss - genera sempre DAO", theApp.m_bSISSGeneraSempreDAO);
	GetBoolValue("Siss - mostra menu disattiva firma", theApp.m_bSISSMostraMenuDisattivaFirma);

	// --- //

	GetLongValue("Colore - visualizzazione aperto", (long&)theApp.m_colorVisualizzazioneAperto);
	GetLongValue("Colore - visualizzazione aperto sfondo", (long&)theApp.m_colorVisualizzazioneApertoSfondo);
	GetLongValue("Colore - visualizzazione chiuso", (long&)theApp.m_colorVisualizzazioneChiuso);
	GetLongValue("Colore - visualizzazione chiuso sfondo", (long&)theApp.m_colorVisualizzazioneChiusoSfondo);
	GetLongValue("Colore - visualizzazione firmato", (long&)theApp.m_colorVisualizzazioneFirmato);
	GetLongValue("Colore - visualizzazione firmato sfondo", (long&)theApp.m_colorVisualizzazioneFirmatoSfondo);
	GetLongValue("Colore - aggiunta paziente", (long&)theApp.m_colorAggiuntaPaziente);
	GetLongValue("Colore - aggiunta paziente sfondo", (long&)theApp.m_colorAggiuntaPazienteSfondo);
	GetLongValue("Colore - modifica paziente", (long&)theApp.m_colorModificaPaziente);
	GetLongValue("Colore - modifica paziente sfondo", (long&)theApp.m_colorModificaPazienteSfondo);
	GetLongValue("Colore - aggiunta esame", (long&)theApp.m_colorAggiuntaEsame);
	GetLongValue("Colore - aggiunta esame sfondo", (long&)theApp.m_colorAggiuntaEsameSfondo);
	GetLongValue("Colore - modifica esame", (long&)theApp.m_colorModificaEsame);
	GetLongValue("Colore - modifica esame sfondo", (long&)theApp.m_colorModificaEsameSfondo);
	GetLongValue("Colore - ricerca paziente", (long&)theApp.m_colorRicercaPaziente);
	GetLongValue("Colore - ricerca paziente sfondo", (long&)theApp.m_colorRicercaPazienteSfondo);
	GetLongValue("Colore - ricerca esame", (long&)theApp.m_colorRicercaEsame);
	GetLongValue("Colore - ricerca esame sfondo", (long&)theApp.m_colorRicercaEsameSfondo);
	GetLongValue("Colore - non sbloccabile", (long&)theApp.m_colorVisualizzazioneArchiviato);
	GetLongValue("Colore - non sbloccabile sfondo", (long&)theApp.m_colorVisualizzazioneArchiviatoSfondo);
	GetLongValue("Colore - in archiviazione", (long&)theApp.m_colorVisualizzazioneInArchiviazione);
	GetLongValue("Colore - in archiviazione sfondo", (long&)theApp.m_colorVisualizzazioneInArchiviazioneSfondo);
	GetLongValue("Colore - streaming attivo", (long&)theApp.m_colorStreamingAttivo);
	GetLongValue("Colore - streaming attivo sfondo", (long&)theApp.m_colorStreamingAttivoSfondo);
	GetLongValue("Colore - streaming connesso", (long&)theApp.m_colorStreamingConnesso);
	GetLongValue("Colore - streaming connesso sfondo", (long&)theApp.m_colorStreamingConnessoSfondo);

	GetStringValue("Login - Http server ricerca ficha", theApp.m_sHttpServerRicercaFicha);
	GetStringValue("Login - Http server ricerca itens ficha", theApp.m_sHttpServerRicercaItensDaFicha);
	GetStringValue("Login - Http server richiesta info user", theApp.m_sHttpServerRichiestaInfoUser);
	GetStringValue("Login - Http server richiesta user signature", theApp.m_sHttpServerRichiestaUserSignature);
	GetStringValue("Login - Http server richiesta modifica-stampa", theApp.m_sHttpServerRichiestaModificaStampa);
	GetStringValue("Login - Http server richiesta Unidade", theApp.m_sHttpServerRichiestaUnidade);
	GetStringValue("Login - Http server richiesta Laudos", theApp.m_sHttpServerRichiestaLaudos);
	GetStringValue("Login - Http server Anula libera laudo", theApp.m_sHttpServerAnulaLiberaLaudo); // Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo

	GetStringValue("Tabella ecocardio - formula BSA", theApp.m_sTabellaEcocardioFormulaBSA);
	GetStringValue("Tabella ecocardio - tabulazioni", theApp.m_sTabellaEcocardioTabs);

	GetBoolValue("Usa utente loggato come medico default", theApp.m_bUsaUtenteLoggatoComeMedicoDefault);
	GetBoolValue("Prestazioni form read-only", theApp.m_bPrestazioniReadOnly);		
	
	GetBoolValue("Monitoraggio - Permetti copia da precedente", theApp.m_bMonitoraggioPermettiCopia);

	//Julio 13/11/2017
	GetStringValue("Referto - LaudoRtfExameAnterior Endpoint", theApp.m_sLaudoRtfExameAnteriorEndpoint);
	//Julio 12/03/2018
	GetBoolValue("Menu - Usa Carestream e Exames Pendentes", theApp.m_bMenuUsaCarestreamExamesPendentes);
	GetBoolValue("Menu - Usa Textbox Busca Exame", theApp.m_bMenuUsaTextboxBuscaExame);	
	GetStringValue("Menu - Path Visor Pacs Web", theApp.m_sHttpPathVisorPacsWeb);
	GetBoolValue("Usa Laudo Provisorio", theApp.m_bUsaLaudoProvisorio);

	GetBoolValue("Pesquisa - Usa Medico Logado Salvar", theApp.m_bUsaMedicoLogadoNaPesquisaSalvar);
	GetBoolValue("Pesquisa - Usa Medico Logado Assinar", theApp.m_bUsaMedicoLogadoNaPesquisaAssinar);
	
	//Julio 01/02/2019
	GetBoolValue("Medidas Biometricas - Usa Code Value", theApp.m_bMedidasBiometricasUsaCodeValue);
	//Julio 06/02/2019
	GetStringValue("Referto - Path Rtf Valores de Referencia", theApp.m_sPathValoresReferencia);
	GetBoolValue("Usa modulo genomica", theApp.m_bUsaModuloGenomica); // Julio genomica
	// --- //
	
	//Julio (FIX) BUG 3361 - Captura continua
	GetBoolValue("Usa captura continua", theApp.m_bCapturaContinua);

	// Marvel BUG 4092 - concorrência na edição de laudos
	GetBoolValue("Referto - apresenta msg popup alerta quando houver edição concorrente", theApp.m_bShowAlertaEdicaoConcorrente);

	//Julio - BUG 4392 Edicao de texto
	GetBoolValue("Rtf usa configurazioni tabelle", theApp.m_bRtfUsaConfigurazioniTabelle);
	GetBoolValue("Rtf usa configurazioni font", theApp.m_bRtfUsaConfigurazioniFont);
	GetBoolValue("Rtf usa configurazioni immagini", theApp.m_bRtfUsaConfigurazioniImmagini);
	//

	// Marvel Carvalho - BUG 4308 Esquemas Anatômicos Fleury
	GetStringValue("Percorso SCHEMI ANATOMICI", theApp.m_sPercorsoSCHEMI_ANATOMICI);

	// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnesi)
	GetStringValue("Tab Anamnesi in referto", theApp.m_sTabAnamnesiInReferto);

	// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#1 - dual screen)
	GetStringValue("Referto - Botao Img abre qual dlg", theApp.m_sConfigFormRefertoBtnImgOpenWhat);
	GetStringValue("Referto - Botao Img abre dlg onde", theApp.m_sConfigFormRefertoBtnImgOpenWhere);
	GetBoolValue  ("Referto - Botao Img automatizado",  theApp.m_bConfigFormRefertoBtnImgAutomated);
	GetStringValue("AlbumIMG - Botao Img abre dlg onde", theApp.m_sConfigFormAlbumImgBtnImgOpenWhere);
	
	// Marvel Carvalho - BUG 4621 Pop up central de laudos
	GetBoolValue("Referto - apresenta msg popup enviar para central de laudos", theApp.m_bPopupCentralDeLaudos);

	// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
	theApp.m_sLastSearchMedico1 = "";

	//Julio - BUG 4392 Edicao de texto
	GetBoolValue("Usa combo prestazioni", theApp.m_bUsaComboPrestazioni);
	//
	
	//Julio BUG 3456 - Contingencia
	GetBoolValue("Contingencia", theApp.m_bContingencia); 
	if (theApp.m_bContingencia)
		theApp.m_sNomeProgramma = theApp.GetMessageString(IDS_NOMEPROGRAMMA_CONTINGENZA);
	//
	
	GetBoolValue("Usa RTF no Texter", theApp.m_bUsaTexterAsRTF);	// Marvel Carvalho - Bug 3457 (FIX) TEXTER

	GetStringValue("Genomica - Modelo Tabela 1", theApp.m_sGenomicaModeloTabela1);
	GetStringValue("Genomica - Modelo Tabela 2", theApp.m_sGenomicaModeloTabela2);
	GetStringValue("Genomica - Modelo Tabela 3", theApp.m_sGenomicaModeloTabela3);
	GetStringValue("Genomica - Modelo Tabela 4", theApp.m_sGenomicaModeloTabela4);
	GetStringValue("Genomica - Modelo Tabela 5", theApp.m_sGenomicaModeloTabela5);

	GetBoolValue("Usa IDSegu", theApp.m_bUsaIDSegu); //Julio Login SEGU
	
	GetStringValue("Indirizzi Mail Riconvocazione", theApp.m_sIndirizziMailReconvocazione); //Gabriel BUG 6225 - Lista DO
	GetBoolValue("Referto - Mostra età paziente nel titolo", theApp.m_bRefertoMostraEtaPazienteTitolo); //Gabriel BUG 6225 - Lista DO
	GetBoolValue("Importazione automatica ricetta", theApp.m_bImportazioneAutomaticaRicetta); //Gabriel BUG 6225 - Lista DO

	GetStringValue("Referto - Http server substituicao resultado", theApp.m_sHttpServerSubstituicaoResultado); //Gabriel - P3
	GetStringValue("Referto - Http server protocolo XXI", theApp.m_sHttpServerProtocoloXXI); //Gabriel - P3
	GetBoolValue("Stampa - Seleziona medico inviante", theApp.m_bSelezionaMedicoRichiedente); //Gabriel - P3
	
	GetBoolValue("Usa Captura Scanner com TGrabber", theApp.m_bUsaCapturaScannerTGrabber); //Gabriel BUG 7749 - Capturar imagens via xtwain utilizando pedal USB
	GetBoolValue("Ativa P3", theApp.m_bAtivaP3); //Gabriel - Chave para ativar P3
	GetBoolValue("Ativa Lista DO", theApp.m_bAtivaListaDO); //Gabriel - Chave para ativar Lista DO
	GetBoolValue("Ativa TCP", theApp.m_bAtivaTCP); //Gabriel - TCP
	GetStringValue("Siglas TCP", theApp.m_sSiglasTCP); //Gabriel - TCP
	GetBoolValue("Usa nova captura continua", theApp.m_bUsaNovaCapturaContinua); //Gabriel BUG 7768 - Continuous capture problem
	GetStringValue("Tela exames pendentes - Ordem das colunas", theApp.m_sEsamiPendentiOrdineColonna); //Gabriel BUG 6225 - Lista DO FIX
	GetLongValue("Tela exames pendentes - Coluna de ordenação", theApp.m_lEsamiPendentiColonnaOrdinare); //Gabriel BUG 6225 - Lista DO FIX
	GetBoolValue("AlbumIMG - Abre imagem tela cheia", theApp.m_bAbreImgTelaCheia); //Gabriel BUG 6225 - Lista DO FIX
	
	GetBoolValue("Ativa Espermograma", theApp.m_bAtivaEspermograma); //Gabriel - BUG 5533 V2

	//GetBoolValue("No coniugazione", theApp.m_bNoConiugazione);

	if (theApp.m_nArchivioImmaginiSogliaAvviso < 0)
		theApp.m_nArchivioImmaginiSogliaAvviso = 0;
	if (theApp.m_nArchivioImmaginiSogliaAvviso > 100)
		theApp.m_nArchivioImmaginiSogliaAvviso = 100;

	if (theApp.m_nArchivioImmaginiSogliaBlocco < 0)
		theApp.m_nArchivioImmaginiSogliaBlocco = 0;
	if (theApp.m_nArchivioImmaginiSogliaBlocco > 100)
		theApp.m_nArchivioImmaginiSogliaBlocco = 100;

	if (theApp.m_nArchivioImmaginiSogliaBlocco > theApp.m_nArchivioImmaginiSogliaAvviso)
		theApp.m_nArchivioImmaginiSogliaBlocco = theApp.m_nArchivioImmaginiSogliaAvviso;

	// Sandro 20/09/2013 // RAS 20130112 //

	if (theApp.m_lPDFQualitaImmaginiCompresse < 0)
		theApp.m_lPDFQualitaImmaginiCompresse = 0;
	if (theApp.m_lPDFQualitaImmaginiCompresse > 100)
		theApp.m_lPDFQualitaImmaginiCompresse = 100;

	// Sandro 12/07/2016 //

	if (theApp.m_lControlloQualitaPercentuale < 0)
		theApp.m_lControlloQualitaPercentuale = 0;
	if (theApp.m_lControlloQualitaPercentuale > 100)
		theApp.m_lControlloQualitaPercentuale = 100;

	// --- //
	
	else if (theApp.m_bPrenotazioniCup && theApp.m_bPrenotazioniDicom) // se è attiva Dicom + CUP, lista prenotazioni doppia //
		theApp.m_nInterfacciaPrenotazione = CEndoxApp::prenotazioni_cup_dicom;
	else if (theApp.m_bPrenotazioniCup)
		theApp.m_nInterfacciaPrenotazione = CEndoxApp::prenotazioni_cup;
	else if (theApp.m_bPrenotazioniDicom)
		theApp.m_nInterfacciaPrenotazione = CEndoxApp::prenotazioni_worklistdicom;
	else if (theApp.m_bInterfacciaDMS)
		theApp.m_nInterfacciaPrenotazione = CEndoxApp::prenotazioni_DMS;
	else
		theApp.m_nInterfacciaPrenotazione = CEndoxApp::prenotazioni_none;

	// --- //

	theApp.m_sHeaderPrintImage = GetPrivateProfileString(szPrintPage, szHeaderPrint, " " + theApp.m_sNomeProgramma + " - Tesi Imaging ", theApp.m_sFileConfig);

	//

	if (theApp.m_bDemoAliar)
	{
		theApp.m_sPercorsoOrigineDemoAliar = GetPrivateProfileString(szSettings, szPercorsoOrigineDemoAliar, "", theApp.m_sFileConfig);

		if (theApp.m_sPercorsoOrigineDemoAliar.IsEmpty())
		{
			CString sErrorMessage;
			sErrorMessage.Format(theApp.GetMessageString(IDS_VALORIZZA_PERCORSO_ENDOXPROCFG), szPercorsoOrigineDemoAliar);
			theApp.AfxMessageBoxEndo(sErrorMessage);
		}
		else
		{
			if (theApp.m_sPercorsoOrigineDemoAliar.Right(1) == '\\')
				theApp.m_sPercorsoOrigineDemoAliar = theApp.m_sPercorsoOrigineDemoAliar.Left(theApp.m_sPercorsoOrigineDemoAliar.GetLength() - 1);

			if (!VerificaPercorsoSistemaEndox(theApp.m_sPercorsoOrigineDemoAliar))
			{
				CString sErrorMessage;
				sErrorMessage.Format(theApp.GetMessageString(IDS_PERCORSO_NONVALIDO_ENDOXPROCFG), szPercorsoOrigineDemoAliar);
				theApp.AfxMessageBoxEndo(sErrorMessage);
			}
		}

		WritePrivateProfileString(szSettings, szPercorsoOrigineDemoAliar, theApp.m_sPercorsoOrigineDemoAliar, theApp.m_sFileConfig);

		///

		theApp.m_sPercorsoDestinazioneDemoAliar = GetPrivateProfileString(szSettings, szPercorsoDestinazioneDemoAliar, "", theApp.m_sFileConfig);

		if (theApp.m_sPercorsoDestinazioneDemoAliar.IsEmpty())
		{
			CString sErrorMessage;
			sErrorMessage.Format(theApp.GetMessageString(IDS_VALORIZZA_PERCORSO_ENDOXPROCFG), szPercorsoDestinazioneDemoAliar);
			theApp.AfxMessageBoxEndo(sErrorMessage);
		}
		else
		{
			if (theApp.m_sPercorsoDestinazioneDemoAliar.Right(1) == '\\')
				theApp.m_sPercorsoDestinazioneDemoAliar = theApp.m_sPercorsoDestinazioneDemoAliar.Left(theApp.m_sPercorsoDestinazioneDemoAliar.GetLength() - 1);

			if (!VerificaPercorsoSistemaEndox(theApp.m_sPercorsoDestinazioneDemoAliar))
			{
				CString sErrorMessage;
				sErrorMessage.Format(theApp.GetMessageString(IDS_PERCORSO_NONVALIDO_ENDOXPROCFG), szPercorsoDestinazioneDemoAliar);
				theApp.AfxMessageBoxEndo(sErrorMessage);
			}
		}

		WritePrivateProfileString(szSettings, szPercorsoDestinazioneDemoAliar, theApp.m_sPercorsoDestinazioneDemoAliar, theApp.m_sFileConfig);

	}

	GetBoolValue("Logout mantieni selezione immagini", theApp.m_bMantieniImmaginiSelezionateAlLogout);
	GetIntValue("Monitoraggio - Scala dolore default", theApp.m_nMonitoraggioDoloreDefault);

	GetBoolValue("Chiusura fase - login", theApp.m_bChiusuraFaseLogin);

	// Sandro 28/10/2016 //
#ifndef _DEBUG
	if (theApp.m_bCentraleStampa)
	{
		theApp.m_sHttpServerRichiestaUnidade.Trim();
		if (theApp.m_sHttpServerRichiestaUnidade.IsEmpty())
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CONFIGURAZIONEVUOTA) + "\r\nLogin - Http server richiesta Unidade");

		theApp.m_sHttpServerRichiestaLaudos.Trim();
		if (theApp.m_sHttpServerRichiestaLaudos.IsEmpty())
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CONFIGURAZIONEVUOTA) + "\r\nLogin - Http server richiesta Laudos");
	}
#endif
}

void CEsamiDoc::LeggiConfigurazioneStep3()
{
	CConfigurazioniInterfacceSet setInterfacce;

	setInterfacce.GetBoolValue("WEB - Pubblicazione automatica", theApp.m_bPubblicazioneAuto);
	setInterfacce.GetStringValue("WEB - Percorso temporaneo", theApp.m_sPercorsoTemporaneoWEB);
	setInterfacce.GetStringValue("WEB - To", theApp.m_sInterfacciaWebTo);
	setInterfacce.GetStringValue("WEB - From", theApp.m_sInterfacciaWebFrom);
	setInterfacce.GetStringValue("WEB - Supplier", theApp.m_sInterfacciaWebSupplier);
	setInterfacce.GetBoolValue("WEB - Consultazione", theApp.m_bConsultazioneWEB);

	setInterfacce.GetLongValue("DCM - StoreMode", theApp.m_lDcmStoreMode); // 0 - Nessuno, 1 - Solo immagini stampate, 2 - Tutte le immagini e i video acquisiti
}

void CEsamiDoc::GetBoolValue(CString sVoce, BOOL& bValore)
{
	CSetupSet setSetup;
	setSetup.SetOpenFilter("VOCE LIKE '%" + sVoce + "%'");
	setSetup.SetSortRecord("VOCE");
	if (setSetup.OpenRecordset("CEsamiDoc::GetBoolValue"))
	{
		if (setSetup.IsEOF())
		{
			if (setSetup.AddNewRecordset("CEsamiDoc::GetBoolValue"))
			{
				setSetup.m_sVoce = sVoce;
				setSetup.m_sValore = (bValore == TRUE ? "1" : "0");
				setSetup.UpdateRecordset("CEsamiDoc::GetBoolValue");
			}
		}
		else
		{
			bValore = (atol(setSetup.m_sValore) == 1 ? TRUE : FALSE);
		}

		setSetup.CloseRecordset("CEsamiDoc::GetBoolValue");
	}
}

void CEsamiDoc::GetFloatValue(CString sVoce, float& fValore)
{
	CSetupSet setSetup;
	setSetup.SetOpenFilter("Voce='" + sVoce + "'");
	setSetup.SetSortRecord("Voce");
	if (setSetup.OpenRecordset("CEsamiDoc::GetIntValue"))
	{
		if (setSetup.IsEOF())
		{
			if (setSetup.AddNewRecordset("CEsamiDoc::GetIntValue"))
			{
				setSetup.m_sVoce = sVoce;
				setSetup.m_sValore.Format("%.1f", fValore);
				setSetup.UpdateRecordset("CEsamiDoc::GetIntValue");
			}
		}
		else
		{
			fValore = (float)atof(setSetup.m_sValore);
		}

		setSetup.CloseRecordset("CEsamiDoc::GetIntValue");
	}
}

void CEsamiDoc::GetIntValue(CString sVoce, int& iValore)
{
	CSetupSet setSetup;
	setSetup.SetOpenFilter("Voce='" + sVoce + "'");
	setSetup.SetSortRecord("Voce");
	if (setSetup.OpenRecordset("CEsamiDoc::GetIntValue"))
	{
		if (setSetup.IsEOF())
		{
			if (setSetup.AddNewRecordset("CEsamiDoc::GetIntValue"))
			{
				setSetup.m_sVoce = sVoce;
				setSetup.m_sValore.Format("%d", iValore);
				setSetup.UpdateRecordset("CEsamiDoc::GetIntValue");
			}
		}
		else
		{
			iValore = atoi(setSetup.m_sValore);
		}

		setSetup.CloseRecordset("CEsamiDoc::GetIntValue");
	}
}

void CEsamiDoc::GetLongValue(CString sVoce, long& lValore)
{
	CSetupSet setSetup;
	setSetup.SetOpenFilter("Voce='" + sVoce + "'");
	setSetup.SetSortRecord("Voce");
	if (setSetup.OpenRecordset("CEsamiDoc::GetLongValue"))
	{
		if (setSetup.IsEOF())
		{
			if (setSetup.AddNewRecordset("CEsamiDoc::GetLongValue"))
			{
				setSetup.m_sVoce = sVoce;
				setSetup.m_sValore.Format("%li", lValore);
				setSetup.UpdateRecordset("CEsamiDoc::GetLongValue");
			}
		}
		else
		{
			lValore = atol(setSetup.m_sValore);
		}

		setSetup.CloseRecordset("CEsamiDoc::GetLongValue");
	}
}

void CEsamiDoc::GetStringValue(CString sVoce, CString& sValore)
{
	CSetupSet setSetup;
	setSetup.SetOpenFilter("Voce='" + sVoce + "'");
	setSetup.SetSortRecord("Voce");
	if (setSetup.OpenRecordset("CEsamiDoc::GetStringValue"))
	{
		if (setSetup.IsEOF())
		{
			if (setSetup.AddNewRecordset("CEsamiDoc::GetStringValue"))
			{
				setSetup.m_sVoce = sVoce;
				setSetup.m_sValore = sValore;
				setSetup.UpdateRecordset("CEsamiDoc::GetStringValue");
			}
		}
		else
		{
			sValore = setSetup.m_sValore;
		}

		setSetup.CloseRecordset("CEsamiDoc::GetStringValue");
	}
}

void CEsamiDoc::GetStringValueServizi(CString sVoce, CString& sValore)
{
	CSetupServiziSet setSetupServizi;
	setSetupServizi.SetOpenFilter("Parametro='" + sVoce + "'");
	setSetupServizi.SetSortRecord("Parametro");
	if (setSetupServizi.OpenRecordset("CEsamiDoc::GetStringValueServizi"))
	{
		if (setSetupServizi.IsEOF())
			sValore = "";
		else
			sValore = setSetupServizi.m_sValore;

		setSetupServizi.CloseRecordset("CEsamiDoc::GetStringValueServizi");
	}
}

void CEsamiDoc::GetLongValueServizi(CString sVoce, long& lValore)
{
	CSetupServiziSet setSetupServizi;
	setSetupServizi.SetOpenFilter("Parametro='" + sVoce + "'");
	setSetupServizi.SetSortRecord("Parametro");
	if (setSetupServizi.OpenRecordset("CEsamiDoc::GetLongValueServizi"))
	{
		if (setSetupServizi.IsEOF())
			lValore = 0;
		else
			lValore = atol(setSetupServizi.m_sValore);

		setSetupServizi.CloseRecordset("CEsamiDoc::GetLongValueServizi");
	}
}

void CEsamiDoc::SetBoolValue(CString sVoce, BOOL& bValore)
{
	CSetupSet setSetup;
	setSetup.SetOpenFilter("Voce='" + sVoce + "'");
	setSetup.SetSortRecord("Voce");
	if (setSetup.OpenRecordset("CEsamiDoc::SetBoolValue"))
	{
		if (setSetup.IsEOF())
			setSetup.AddNewRecordset("CEsamiDoc::SetBoolValue");
		else
			setSetup.EditRecordset("CEsamiDoc::SetBoolValue");

		setSetup.m_sVoce = sVoce;
		setSetup.m_sValore = (bValore ? "1" : "0");
		setSetup.UpdateRecordset("CEsamiDoc::SetBoolValue");

		setSetup.CloseRecordset("CEsamiDoc::SetBoolValue");
	}
}

void CEsamiDoc::SetIntValue(CString sVoce, int& iValore)
{
	CSetupSet setSetup;
	setSetup.SetOpenFilter("Voce='" + sVoce + "'");
	setSetup.SetSortRecord("Voce");
	if (setSetup.OpenRecordset("CEsamiDoc::SetIntValue"))
	{
		if (setSetup.IsEOF())
			setSetup.AddNewRecordset("CEsamiDoc::SetIntValue");
		else
			setSetup.EditRecordset("CEsamiDoc::SetIntValue");

		setSetup.m_sVoce = sVoce;
		setSetup.m_sValore.Format("%d", iValore);
		setSetup.UpdateRecordset("CEsamiDoc::SetIntValue");

		setSetup.CloseRecordset("CEsamiDoc::SetIntValue");
	}
}

void CEsamiDoc::SetStringValue(CString sVoce, CString& sValore)
{	
	CSetupSet setSetup;
	setSetup.SetOpenFilter("Voce='" + sVoce + "'");
	setSetup.SetSortRecord("Voce");
	if (setSetup.OpenRecordset("CEsamiDoc::SetStringValue"))
	{
		if (setSetup.IsEOF())
			setSetup.AddNewRecordset("CEsamiDoc::SetStringValue");
		else
			setSetup.EditRecordset("CEsamiDoc::SetStringValue");

		setSetup.m_sVoce = sVoce;
		setSetup.m_sValore = sValore;
		setSetup.UpdateRecordset("CEsamiDoc::SetStringValue");

		setSetup.CloseRecordset("CEsamiDoc::SetStringValue");
	}
}

void CEsamiDoc::SetLongValue(CString sVoce, long& iValore)
{
	CSetupSet setSetup;
	setSetup.SetOpenFilter("Voce='" + sVoce + "'");
	setSetup.SetSortRecord("Voce");
	if (setSetup.OpenRecordset("CEsamiDoc::SetIntValue"))
	{
		if (setSetup.IsEOF())
			setSetup.AddNewRecordset("CEsamiDoc::SetIntValue");
		else
			setSetup.EditRecordset("CEsamiDoc::SetIntValue");

		setSetup.m_sVoce = sVoce;
		setSetup.m_sValore.Format("%d", iValore);
		setSetup.UpdateRecordset("CEsamiDoc::SetIntValue");

		setSetup.CloseRecordset("CEsamiDoc::SetIntValue");
	}
}

void CEsamiDoc::OnSalvaConfigurazioneIntegrazioniGenerale()
{
	long lUO = theApp.m_lUO;
	theApp.m_lUO = 0;

	SetLongValue("Login - Mode", theApp.m_lLoginMode);
	SetBoolValue("Disabilita inserimento esami pazienti senza assiden", theApp.m_bDisabilitaEsamiPazientiSenzaAssiden);

	theApp.m_lUO = lUO;
}

void CEsamiDoc::OnSalvaConfigurazioneIntegrazioneVitalSign()
{
	long lUO = theApp.m_lUO;
	theApp.m_lUO = 0;

	CConfigurazioniInterfacceSet setInterfacce;
	setInterfacce.SetBoolValue("Vital Sign - Integrazione attiva", theApp.m_bVitalSignIntegrazioneAttiva);
	setInterfacce.SetStringValue("Vital Sign - Webservice endpoint", theApp.m_sVitalSignWebServiceEndpoint);

	theApp.m_lUO = lUO;
}

void CEsamiDoc::OnSalvaConfigurazioneIntegrazioniUO()
{
	SetStringValue("TESIATDNET - Indirizzo", theApp.m_sTesiAtdNetIndirizzo);
	SetIntValue("TESIATDNET - Porta", theApp.m_nTesiAtdNetPorta);

	SetBoolValue("Lock Server Attivo", theApp.m_bLockServerAttivo);

	CConfigurazioniInterfacceSet setInterfacce;
	setInterfacce.SetLongValue("DCM - StoreMode", theApp.m_lDcmStoreMode); // 0 - Nessuno, 1 - Solo immagini stampate, 2 - Tutte le immagini e i video acquisiti

	SetLongValue("Firma digitale", (long&)theApp.m_enumFirmaDigitale);

	SetBoolValue("Prenotazioni CUP", theApp.m_bPrenotazioniCup);
	SetLongValue("Prenotazioni CUP - Focus", theApp.m_lPrenotazioniCupFocus);
	SetBoolValue("Prenotazioni DICOM", theApp.m_bPrenotazioniDicom);

	SetStringValue("QueryMan", theApp.m_sQueryMan);

	SetStringValue("Login - Http server ricerca ficha", theApp.m_sHttpServerRicercaFicha);
	SetStringValue("Login - Http server ricerca itens ficha", theApp.m_sHttpServerRicercaItensDaFicha);
	SetStringValue("Login - Http server richiesta info user", theApp.m_sHttpServerRichiestaInfoUser);
	SetStringValue("Login - Http server richiesta user signature", theApp.m_sHttpServerRichiestaUserSignature);
	SetStringValue("Login - Http server richiesta modifica-stampa", theApp.m_sHttpServerRichiestaModificaStampa);
	SetStringValue("Login - Http server richiesta Unidade", theApp.m_sHttpServerRichiestaUnidade);
	SetStringValue("Login - Http server richiesta Laudos", theApp.m_sHttpServerRichiestaLaudos);
	SetStringValue("Login - Http server Anula libera laudo", theApp.m_sHttpServerAnulaLiberaLaudo); // Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo

}

void CEsamiDoc::OnSalvaConfigurazioneFasi()
{
	SetBoolValue("Chiusura fase - login", theApp.m_bChiusuraFaseLogin);
}

void CEsamiDoc::LoadUserGroups()
{
	theApp.m_listUserGroups.RemoveAll();

	CStringList listUserGroups;
	switch (theApp.m_lLoginMode)
	{
		case 0:
		{
			long lUserID;
			AMLogin_GetUserID(&lUserID);
			long lIDGruppo = CUtentiSet().GetIdGruppo(lUserID);
			listUserGroups.AddTail(CGruppiSet().GetDescrizione(lIDGruppo));
			break;
		}
		case 1:
		case 2:
		{
			AMLogin_GetUserGroups(&listUserGroups);
			break;
		}
		case 3:
		case 4:
		{
			AMLogin_GetUserGroups_Net(&listUserGroups);
			break;
		}
		default:
		{
			break;
		}
	}

	// Sandro 10/03/2017 // metto in lista SOLO i gruppi della UO attuale //
	POSITION pos = listUserGroups.GetHeadPosition();
	while (pos != NULL)
	{
		CString sGroup = listUserGroups.GetAt(pos);

		if (CGruppiSet().GetUOFromNome(sGroup) == theApp.m_lUO)
			theApp.m_listUserGroups.AddTail(sGroup);

		listUserGroups.GetNext(pos);
	}
}

void CEsamiDoc::LoadEnabledPhaseForUser()
{
	theApp.m_listUserPhases.RemoveAll();

	POSITION pos = theApp.m_listUserGroups.GetHeadPosition();
	while (pos)
	{
		CString sNomeGruppo = theApp.m_listUserGroups.GetNext(pos);
		long idGruppo = CGruppiSet().GetIDFromNome(sNomeGruppo);

		//Estraggo le fasi gestibili da questo gruppo
		CFasiEsameGruppiSet set;
		CString sFilter;
		sFilter.Format("IDGRUPPO=%li", idGruppo);
		set.SetOpenFilter(sFilter);
		if (set.OpenRecordset("CEsamiDoc::LoadEnabledPhaseForUser"))
		{
			while (!set.IsEOF())
			{
				if (theApp.m_listUserPhases.Find(set.m_lIDFase) == NULL)
					theApp.m_listUserPhases.AddTail(set.m_lIDFase);

				set.MoveNext();
			}

			set.CloseRecordset("CEsamiDoc::LoadEnabledPhaseForUser");
		}
	}
}