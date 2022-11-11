#ifndef __COMMON_H__
	#define __COMMON_H__

#include <iostream>
#include <Windows.h>	// Marvel Carvalho - Bug 3457 (FIX) TEXTER
#include <Winuser.h>	// Marvel Carvalho - Bug 3457 (FIX) TEXTER

class CCodificaRegionaleExSet;
class CComboBoxSet;
class CCupWorkListManager;
class CMstOrganoSet;
class CTipoEsameSet;
class CInviantiSet;
class CBaseSet;
class CComboTransSet;
class CProcedureICD9Set;
class CDiagnosiICD9Set;
class CTXTextControl23Ex;

extern UINT MSG_SELECT_BMP;
extern UINT MSG_ELABOR_BMP;
extern UINT MSG_XPLAY_CLOSE;

extern UINT MSG_XCAP_MSG_NUOVOMONITORAGGIO;
extern UINT MSG_XCAP_MSG_NUOVAPROVETTA;

extern int g_nBlackLev;
extern int g_nWhiteLev;
extern int g_nLastUse;
extern int g_nContrastMinLev[4];
extern int g_nContrastMaxLev[4];
extern int g_nBrightnessLev;

extern CString g_sReportFaceName;
extern int	g_nReportSize;
extern BOOL	g_bReportUnderline;
extern BOOL	g_bReportBold;
extern BOOL	g_bReportItalic;

extern void RegisterPrivateMessage();

extern void SetGlobalVariables();

extern void ConvertInValidStringSQL(CString* pStr);

extern CString AddStringWithoutRepeatition(CString strDestination, CString strSource);

extern void DDX_BreathTestHP	(CDataExchange* pDX, int nIDC, float& fValue, CRecordset* pRecordSet);
extern void DDX_Date			(CDataExchange* pDX, int nIDC, long& value, int nType = 0);
extern void DDX_DateMask		(CDataExchange* pDX, int nIDC, long& value, CRecordset* pRecordSet);
extern void DDX_DateMask		(CDataExchange* pDX, int nIDC, CString& value, CRecordset* pRecordSet);
extern void DDX_DateTimeMask	(CDataExchange* pDX, int nIDC, long& value, CRecordset* pRecordSet);
extern void DDX_DateTimePersMask(CDataExchange* pDX, int nIDC, int nModalita, long& value, CRecordset* pRecordSet);
extern void DDX_DatePicker		(CDataExchange* pDX, int nIDC, long& value, int nType = 0);
extern void DDX_YearEx			(CDataExchange* pDX, int nIDC, long& value);
extern void DDX_Combo(CDataExchange* pDX, int nIDC, long& value, long lComboDefine);
extern void DDX_Organo			(CDataExchange* pDX, int nIDC, long& lOrgano);
extern void DDX_Regione			(CDataExchange* pDX, int nIDC, long& value);
extern void DDX_ProcedureICD9	(CDataExchange* pDX, int nIDC, long& value, int provenienza);
extern void DDX_DiagnosiICD9	(CDataExchange* pDX, int nIDC, long& value, int provenienza);
extern void DDX_Accessori		(CDataExchange* pDX, int nIDC, long& value);
extern void DDX_Studi			(CDataExchange* pDX, int nIDC, long& value, CRecordset* pRecordSet);

extern void DDX_FieldCombo(CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet, long lComboDefine);
extern void DDX_FieldDate			(CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet);
extern void DDX_FieldDateEta(CDataExchange* pDX, int nIDC, long& value, CPazientiSet* pRecordSet); // Sandro 05/11/2013 //
extern void DDX_FieldTipoEsameCombo	(CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet);
extern void DDX_FieldTipoEsameEdit	(CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet);
extern void DDX_FieldOperatoriCombo	(CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet);
extern void DDX_FieldOperatoriEdit(CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet);
extern void DDX_FieldInfermieriCombo(CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet);
extern void DDX_FieldInfermieriEdit (CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet);
extern void DDX_FieldInviantiCombo(CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet, long lProvenienza);
extern void DDX_FieldInviantiEdit(CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet, long lProvenienza);
extern void DDX_FieldSedeEsame		(CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet);
extern void DDX_FieldComboTransCombo(CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet, CComboTransSet* pDataSourceRecordSet);
extern void DDX_FieldComboTransEdit (CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet, CComboTransSet* pDataSourceRecordSet);
extern void DDX_FieldProvenienzaCombo(CDataExchange* pDX, int nIDC, long& value, long& valueOldProvenienza, CBaseSet* pRecordSet);
extern void DDX_FieldProvenienzaEdit(CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet);

extern void ComponiRicercaArray		(CStringArray* pLista, CString strComplete);
extern void ComponiRicercaCognomeNome(CString *strFilter, CBaseSet* pSet, CString* pStr, CString strLabel);
extern void ComponiRicercaCheckSND	(CString& strFilter, CBaseSet* pSet, long* pLong, CString strLabel);
extern void ComponiRicercaEx(CString *strFilter, CString strRicerca, CString strLabel, BOOL bAggiungiSegni, BOOL bNumber);
extern void ComponiRicercaLong		(CString *strFilter, CBaseSet* pSet, long* pLong, CString strLabel, short mode, CString strOperator);
extern void ComponiRicercaRadio		(CString* strFilter, CBaseSet* pSet, void* pLong, int nByte, CString strLabel, short mode);
extern void ComponiRicercaRadioEx	(CString *strFilter, CString strParam, CString strLabel);
extern void ComponiRicercaRange		(CString* strFilter, float f1, float f2, CString strLabel);
extern void ComponiRicercaRange		(CString* strFilter, int n1, int n2, CString strLabel);
extern void ComponiRicercaSesso		(CString& strFilter, CBaseSet* pSet, void* pVoid, CString strLabel, short mode);
extern void ComponiRicercaShort		(CString& strFilter, CBaseSet* pSet, short* 	pInt, 	CString strLabel, short mode, BOOL bZero = FALSE);
extern void ComponiRicercaString	(CString *strFilter, CBaseSet* pSet, CString* pStr, CString strLabel, short mode);
extern void ComponiRicercaFromSpecialString(CString* pFilter, CString str, CString strLabel, CString strOperator);
extern void ComponiRicercaFromEx(CString *strFilter, CString *pStrFrom, CString strRicerca, CString strTable, long lTable, CString strField, CString strJoinField, BOOL bAggiungiSegni, BOOL bNumber);

// Sandro 15/04/2009 --> //
static CString strOperators[2] = { "AND", "OR" };

#define OPER_AND 0
#define OPER_OR 1
#define OPER_AND_SPEC 2
#define OPER_OR_SPEC 3

#define MODE_UGUALE 100
#define MODE_LIKE0 200
#define MODE_LIKE1 300
#define MODE_LIKE2 400

extern void ComponiRicercaNewLong  (CString *pStrFrom, CString *pStrWhere, CString strTable, long lTable, CString strJoinField, CString strWhereField,    long lValue,   long lOperator, long lMode);
extern void ComponiRicercaNewString(CString *pStrFrom, CString *pStrWhere, CString strTable, long lTable, CString strJoinField, CString strWhereField, CString strValue, long lOperator, long lMode, BOOL bMakeUpper);
// <-- Sandro 15/04/2009 //

// Sandro 26/01/2010 --> //
#define STATO_TEMP -1			// temporanea di Endox - l'interfacciamento non la considera //
#define STATO_ANNULLATA 0		// richiesta cancellata prima che questa fosse acquisita //
#define STATO_PRENOTATA 1		// è stata inviata e non ancora acquisita //
#define STATO_ACQUISITA 2		// entra nell'archivio di metafora //
#define STATO_INLAVORAZIONE 3	// almeno uno dei campioni è in fase di lavorazione //
#define STATO_REFERTATA 4		// emesso il referto istologico //
#define STATO_SCARTATA 5		// errori nella richiesta //
#define STATO_RIREFERTATA 6		// il referto istologico è stato modificato o integrato //
// <-- Sandro 26/01/2010 //

// Sandro 30/05/2011 --> //
#define DATA_ORA 0
#define SOLO_DATA 1
#define SOLO_ORA 2
#define DATA_ORA_FULL 3 //to return yyyyMMddHHmmss as str_ricerca
// <-- Sandro 30/05/2011 //

// Sandro 04/06/2013 --> //
#define OPZIONALE_PAZIENTI_CRONICI 147
// <-- Sandro 04/06/2013 //

// Sandro 17/04/2015 --> //
#define LPC_STATO_NONPRESENTATA -40
#define LPC_STATO_NONEROGATA -30
#define LPC_STATO_REFERTATA -20
#define LPC_STATO_EROGATA -15
#define LPC_STATO_INCORSO -10
#define LPC_STATO_ACCETTATA 0
#define LPC_STATO_PRENOTATA 10
//Julio 20/02/2018 --> //
#define LPC_STATO_FLEURY_TRASFERITO_CENTRALIZZAZIONE 17
//Gabriel BUG 6225 - Lista DO
#define LPC_STATO_RICONVOCATO -50

extern void RiempiComboStatiWorklist(CComboBox* pComboBox, long lStatoDaSelezionare, BOOL bFastFichaWorklist);
extern long GetStatoRichiestaLong(CString sStato);
extern CString GetStatoRichiestaString(CString sStato);
// <-- Sandro 17/04/2015 //

extern BOOL MakeStringText(CString &strText, CString strLabel, CString strSeparator);
extern BOOL MakeStringText(CString &strText, CBaseSet* pSet, short* pCampo, CString strLabel, CString strSeparator);
extern BOOL MakeStringText(CString &strText, CBaseSet* pSet, long* pCampo, CString strLabel, CString strSeparator);
extern BOOL MakeStringText(CString &strText, CBaseSet* pSet, float* pCampo, CString strLabel, CString strSeparator);
extern BOOL MakeStringText(CString &strText, CBaseSet* pSet, CString* pCampo, CString strLabel, CString strSeparator);
extern BOOL MakeStringTextTrento(CString &strText, CString strCampo, CString strLabel, CString strSeparator);
extern BOOL MakeStringDate(CString &strText, CBaseSet* pSet, long* pCampo, CString strLabel, CString strSeparator);
extern BOOL MakeStringMedico(CString &strText, CBaseSet* pSet, long* pCampo, CString strLabel, CString strSeparator);
extern BOOL MakeStringInfermiere(CString &strText, CBaseSet* pSet, long* pCampo, CString strLabel, CString strSeparator);
extern BOOL MakeStringInviatoDa(CString &strText, CBaseSet* pSet, long* pCampo, CString strLabel, CString strSeparator, long lProvenienza);
extern BOOL MakeStringProvenienza(CString &strText, CBaseSet* pSet, long* pCampo, CString strLabel, CString strSeparator);
extern BOOL MakeStringSesso(CString &strText, CBaseSet* pSet, long* pCampo, CString strLabel, CString strSeparator);
extern BOOL MakeStringIdEsame(CString &strText, CBaseSet* pSet, long* pCampo, CString strLabel, CString strSeparator);

extern CString GetPrivateProfileString( LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszDefault, LPCTSTR lpszFileName );
extern BOOL WritePrivateProfileInt( LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue, LPCTSTR lpszFileName  );

extern long ConvertMaskString2Date(CString strDateTime);

// Sandro Gallina - 15/07/2004 //
extern BOOL PazienteSetFind(CPazientiSet *pSet, long lCode);

// Sandro 02/08/2012 // cancella il file originale SOLO se quello di destinazione è uguale, quindi SOLO se è sicuro che la copia sia perfetta //
extern BOOL DeleteFileSecure(const CString& sFileToDelete, const CString& sFileToCompare);

// Sandro Gallina - 18/04/2005 //
extern BOOL DeleteDirectory(CString strPath);
extern BOOL DeleteDirectoryNoSub(CString strPath);
extern BOOL DeleteAllFilesOnDirectory(CString strPath);
extern BOOL DeleteDirectoryProgress(CString strPath, CProgressCtrl &ctrlProgress);

// verifica se esiste un dato percorso e se non lo trova tenta di crearlo //
extern BOOL VerificaPercorso(CString strPath, BOOL bVerbose = TRUE);

// verifica se il percorso esiste e se si riesce a scriverci dentro - usato all'avvio del software //
extern BOOL VerificaPercorsoSistemaEndox(CString strPath);

// verifica lo spazio libero nel percorso //
extern BOOL VerificaPercorsoSpazioLibero(CString strPath);

// ritorna l'ID dell'interfaccia operatore da caricare (in base al tipo esame che gli passo e l'utente attualmente loggato in Endox) //
extern long GetIDVersione(long lTipoEsame);

///
///
///
#define COLOR_BLACK		0
#define	COLOR_WHITE		255

#define	AUTO			0
#define	PEAK			1

#define	AUTOMATIC_CONTRAST		1
#define	MANUAL_CONTRAST			2

extern void ScambiaDib(CDib** pDibSorg, CDib** pDibDest);
extern void DoContrast(int l_bin, int h_bin, CRect rect, CDib* pDibSorg, CDib* pDibDest, CDib* pDibRoi);
extern void ContrastPreview(int l_bin, int h_bin, CDib* pDib, LPLOGPALETTE  pOrgPal, LPLOGPALETTE  pLogPal);

extern void DoContrastRGB(int BlackLev, int WhiteLev, CRect rect,CDib* pDibSorg, CDib* pDibDest, CDib* pDibRoi);
extern void ContrastPreviewRGB(int BlackLev, int WhiteLev, CDib* pSourceDib, CDib* pDestDib);

extern void DoContrastRGB(int MinR, int MaxR, int MinG, int MaxG, int MinB, int MaxB, CRect rect,CDib* pDibSorg, CDib* pDibDest, CDib* pDibRoi);
extern void ContrastPreviewRGB	(int MinR, int MaxR, int MinG, int MaxG, int MinB, int MaxB, CDib* pSourceDib, CDib* pDestDib);

extern void BrightnessPreview(int bin, CDib* pDib, LPLOGPALETTE  pOrgPal, LPLOGPALETTE  pLogPal);
extern void DoBrightness(int bin, CDib* pDibSorg, CDib* pDibDest, CDib* pDibRoi);
extern void DoBrightnessRGB(int bin, CDib* pDibSorg, CDib* pDibDest, CDib* pDibRoi);
///
///
///

extern void Enhance(CDib** pDib);
extern BOOL Filter(CDib** pDib, int nFilter, int nCicli);
extern int GenericFilterInt_8bits(CDib* pDib, CDib* pDibWork, int FilterType);
extern int GenericFilterInt_24bits(CDib* pDib, CDib* pDibWork, int FilterType);

#define szParamData "Param.Today"
#define szParamDataLarga "Param.Today.Large"
#define szParamOra "Param.Hour"

typedef struct
{  
	long m_lID;
	CString m_sCodice;
	CString m_sDescrizione;
	long m_lIDTipoEsame;
	long m_lCampoCL;
	long m_lOrdine;
} STRUCT_CHECKLIST;

typedef struct
{
	long lID;
	long lIDChecklist;
	long lIDPadre;
	CString sTitolo;
	CString sTestoRtf;
	CString sTestoTxt;
	long lNumeroVariabili;
	long lIDDiagnosi;
	CString sDiagnosiCodice;
	CString sDiagnosiDescrizione;
	BOOL bItemAlmenoUno;
	BOOL bItemPiuDiUno;
} STRUCT_CHECKLISTITEM;

typedef struct
{
	long lID;
	char szDescrizione[256];
	long lTipo;
	BOOL bValoreModificabile;
} STRUCT_COLONNE;

typedef struct
{
	char szFichaItem[51];
	char szCodice[51];
	char szDescrizione[4001];
	BOOL bStessaUO;
} STRUCT_FICHA_ITEM;

typedef struct
{
	long lIDOrig;
	long lIDDest;
} STRUCT_COPPIA_LONG;

// Sandro 24/04/2012 //
extern CString GetStringCampoLiberoDatabase(long lContenuto);

// nuove funzioni per vecchio trasferimento immagini //

extern int CalcSpaces(CImgManager* pImgManager, CExamIDList* pListExamID, double* pDiskAvaible, double* pSpaceRequired);
extern CString GetVolumeName();

//

extern CString GetStatoText(long lStato);

//

extern BOOL IsBisestile(int iYear);
extern long GetDateTimeDifferenceInHoursFromLongs(long lData1, long lData2);
extern long GetDateTimeDifferenceInMinutesFromLongs(long lData1, long lData2); //Julio 10/08/2018
extern BOOL GetDateDifference(long lData1, long lData2, long* pYears, long* pMonths, long* pDays);
extern CString GetStringEta(long lDataNascita, long lDataEsame, long lFormato); //Gabriel BUG 6225 - Lista DO
extern CString GetStringOreDifferenza(long lDataInizio, long lDataFine, BOOL bSoloMinuti);

//

extern BOOL GetPrinterDevice(LPTSTR pszPrinterName, HGLOBAL *phDevNames, HGLOBAL *phDevMode);
extern BOOL LoadPrinterSettingsFromNumber(long lPrinterToUse, HGLOBAL *pDevNames, HGLOBAL *pDevMode);

//

extern CString GetTextPattern(long lPattern);

extern CString GetTextTumoriMelanociticiBenigni1(long lID);
extern CString GetTextTumoriMelanociticiMaligni1(long lID);

extern CString GetTextTumoriNonMelanociticiLesioniEpiteliali(long lID);
extern CString GetTextTumoriNonMelanociticiLesioniVascolari(long lID);

extern CString GetTextTumoriMelanociticiBenigni2(long lID);
extern CString GetTextTumoriMelanociticiMaligni2(long lID);

//

extern DWORD GetUpdatedPrivileges();

//

extern BOOL GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

// Sandro 28/05/2013 //

extern CString GetContatoreAnnuale(long lTipoEsame);
extern CString GetContatoreAnnualeNoIncrement(long lTipoEsame);

extern CString GetCodicePrenotazione(long lTipoEsame);

// Sandro 05/12/2013 //

extern CString DecodeCitta(CString sCAP, CString sCitta, CString sProvincia);
extern CString DecodeSesso(long lSesso);

// Sandro 09/12/2013 //

extern INT_PTR TimerMessageBox(CString sMainMessage, UINT uidTitleMessage = IDS_ACHTUNG, UINT uidBtnOKMessage = IDS_OK, UINT uidBtnCancelMessage = IDS_CANCEL, long lTimerPartenza = theApp.m_lCountdownPartenza);

extern BOOL FleuryUserCodeCheck();
extern BOOL FleuryGetHealthProfessional(); //Julio Login SEGU
extern BOOL ReplaceImmagineFirmaFromHEX(CString sInput); //Julio Login SEGU
extern BOOL FleuryPossoModificare(CString& sMessaggio, CString sRicovero, CString sCodEsame);
extern BOOL FleuryPossoStampare(CString& sMessaggio, CString sRicovero, CString sCodEsame);
extern BOOL EnviaAnulaLiberaLaudo(CString& sMessaggio, CString sCodEsame, CString sMotivo);// Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
extern BOOL FleuryCercaFicha(CString sFicha, CString& sErrore, CString& sServer, CString& sUO, CString& sEndpointRemoteCommunication);
extern BOOL FleuryCercaItensDaFicha(CString sFicha, CString& sErrore, CString& sServer, CString& sUO, CString& sEndpointRemoteCommunication, long& lArrayCount);
extern BOOL FleuryGetPazienteEsame(CWnd *pParent, CEsamiView *pEsamiView, CString sEndpoint, CString sFicha, CString& sErrore, long& lIDPaziente, long& lIDEsame, BOOL bRecursive = TRUE);
extern BOOL FleuryGetImagemAltraSede(CWnd *pParent, CEsamiView *pEsamiView, long lIDImg);
extern BOOL FleuryGetImagensAltraSede(CWnd *pParent, CEsamiView *pEsamiView);
extern BOOL FleuryGetDocsAltraSede(long lIDEsame, BOOL bInviareCarestream);
extern BOOL FleurySetEsameTrasferitoAltraSede(CString sEndpoint, CString sFicha, CString& sErrore);
extern void DoPtBrReplacement(CString& sText); //Julio 6/12/2017
extern BOOL FleuryIsUserADoctor(); //Julio BUG 6385

// Sandro 26/10/2015 //

extern long GetStampaImmaginiIDHeader();
extern long GetStampaImmaginiIDFooter();

// Sandro 04/12/2015 //

extern CString ComponiStringaConnessione(BOOL bIsOracle, const CString &sOracleDriver, const CString &sServerDBQ, const CString &sUsername, const CString &sPassword);

extern void StartProcess(CString sProcess);

// Sandro 24/10/2016 //

extern BOOL RegistryGetValue(HKEY hk, const char* pszKey, const char* pszValue, DWORD dwType, BYTE* pData, DWORD dwSize);
extern CString RegistryGetStringValue(HKEY hKey, CString sSubKey, CString sValue);

// Sandro 17/02/2017 //

extern long GetUserIDForLockSuperlock();

// Sandro 06/07/2017 //

extern int ContaFilesPostAcquisizione(long lIDPaziente, long lIDEsame);
extern void FleuryApriConsulta(CString sFicha);
extern void FleuryApriConsulta2(CString sFicha);
extern void FleuryAssessoriaMedica(CString sFicha);
extern void OpenURLOnChrome(CString sURL); //Julio Login SEGU
extern CString GetBase64StringFromString(CString sInput);
extern void UpdateDatiRemoti(CEsamiSet* pEsamiSet);
extern void XWriteLogTime(CString sLog, DWORD dwMsecParz, DWORD dwMsecTot);
extern void ImpersonateStart(long lIDEsame, long lIDPaziente, long lIDUtente);
extern void ImpersonateStop(long lIDEsame, long lIDPaziente);

//

extern BOOL CheckIfMainDBIsOnline(); //Julio BUG 3456 - Contingencia

enum FORM_LIST
{
	sub_abitudini,
	sub_chirurgici,
	sub_endoscopici,
	sub_familiarita,
	sub_indagini,
	sub_malattie,
	edt_progressivo,
	edt_dataesame,
	cmb_tipoesame,
	edt_progressivoanno,
	edt_codiceprenotazione,
	cmb_medico1,
	cmb_medico2,
	edt_medico_ricerca,
	cmb_infermiere1,
	cmb_infermiere2,
	sub_inviante,
	edt_camera,
	edt_indicazioni,
	edt_farmacotrial,
	edt_premedicazioni,
	sub_terapiainatto,
	sub_osservazioni,
	edt_diagnostiche,
	edt_terapeutiche,
	sub_diagnosi,
	edt_condottofino,
	edt_valutazione,
	edt_complicanze,
	edt_complicanzeprovvedimenti,
	edt_complicanzeterapia,
	edt_complicanzeesito,
	edt_tipovisita,
	edt_quadro,
	edt_durata,
	edt_prossimo,
	edt_studio,
	edt_guarigione,
	edt_difficolta,
	sub_regione,
	edt_terapiaconsigliata,
	edt_strumenti,
	edt_accessori,
	edt_note,
	sub_istopatologia,
	sub_referto,
	edt_riferimento,

	// Sandro 17/09/2014 // non aggiungere nulla prima di edt_libero000, please //

	edt_libero000,
	edt_libero001,
	edt_libero002,
	edt_libero003,
	edt_libero004,
	edt_libero005,
	edt_libero006,
	edt_libero007,
	edt_libero008,
	edt_libero009,
	edt_libero010,
	edt_libero011,
	edt_libero012,
	edt_libero013,
	edt_libero014,
	edt_libero015,
	edt_libero016,
	edt_libero017,
	edt_libero018,
	edt_libero019,
	edt_libero020,
	edt_libero021,
	edt_libero022,
	edt_libero023,
	edt_libero024,
	edt_libero025,
	edt_libero026,
	edt_libero027,
	edt_libero028,
	edt_libero029,
	edt_libero030,
	edt_libero031,
	edt_libero032,
	edt_libero033,
	edt_libero034,
	edt_libero035,
	edt_libero036,
	edt_libero037,
	edt_libero038,
	edt_libero039,
	edt_libero040,
	edt_libero041,
	edt_libero042,
	edt_libero043,
	edt_libero044,
	edt_libero045,
	edt_libero046,
	edt_libero047,
	edt_libero048,
	edt_libero049,
	edt_libero050,
	edt_libero051,
	edt_libero052,
	edt_libero053,
	edt_libero054,
	edt_libero055,
	edt_libero056,
	edt_libero057,
	edt_libero058,
	edt_libero059,
	edt_libero060,
	edt_libero061,
	edt_libero062,
	edt_libero063,
	edt_libero064,
	edt_libero065,
	edt_libero066,
	edt_libero067,
	edt_libero068,
	edt_libero069,
	edt_libero070,
	edt_libero071,
	edt_libero072,
	edt_libero073,
	edt_libero074,
	edt_libero075,
	edt_libero076,
	edt_libero077,
	edt_libero078,
	edt_libero079,
	edt_libero080,
	edt_libero081,
	edt_libero082,
	edt_libero083,
	edt_libero084,
	edt_libero085,
	edt_libero086,
	edt_libero087,
	edt_libero088,
	edt_libero089,
	edt_libero090,
	edt_libero091,
	edt_libero092,
	edt_libero093,
	edt_libero094,
	edt_libero095,
	edt_libero096,
	edt_libero097,
	edt_libero098,
	edt_libero099,
	edt_liberortf000,
	edt_liberortf001,
	edt_liberortf002,
	edt_liberortf003,
	edt_liberortf004,
	edt_liberortf005,
	edt_liberortf006,
	edt_liberortf007,
	edt_liberortf008,
	edt_liberortf009,
	edt_liberortf010,
	edt_liberortf011,
	edt_liberortf012,
	edt_liberortf013,
	edt_liberortf014,
	edt_liberortf015,
	edt_liberortf016,
	edt_liberortf017,
	edt_liberortf018,
	edt_liberortf019,
	edt_liberocl000,
	edt_liberocl001,
	edt_liberocl002,
	edt_liberocl003,
	edt_liberocl004,
	edt_liberocl005,
	edt_liberocl006,
	edt_liberocl007,
	edt_liberocl008,
	edt_liberocl009,
	edt_liberocl010,
	edt_liberocl011,
	edt_liberocl012,
	edt_liberocl013,
	edt_liberocl014,
	edt_liberocl015,
	edt_liberocl016,
	edt_liberocl017,
	edt_liberocl018,
	edt_liberocl019,
	edt_liberodataora000,
	edt_liberodataora001,
	edt_liberodataora002,
	edt_liberodataora003,
	edt_liberodataora004,
	edt_liberodataora005,
	edt_liberodataora006,
	edt_liberodataora007,
	edt_liberodataora008,
	edt_liberodataora009,
	edt_liberodataora010,
	edt_liberodataora011,
	edt_liberodataora012,
	edt_liberodataora013,
	edt_liberodataora014,
	edt_liberodataora015,
	edt_liberodataora016,
	edt_liberodataora017,
	edt_liberodataora018,
	edt_liberodataora019,
	btn_liberotastostampa000,
	btn_liberotastostampa001,
	btn_liberotastostampa002,
	btn_liberotastostampa003,
	btn_liberotastostampa004,
	btn_liberotastostampa005,
	btn_liberotastostampa006,
	btn_liberotastostampa007,
	btn_liberotastostampa008,
	btn_liberotastostampa009,
	btn_liberotastostampa010,
	btn_liberotastostampa011,
	btn_liberotastostampa012,
	btn_liberotastostampa013,
	btn_liberotastostampa014,
	btn_liberotastostampa015,
	btn_liberotastostampa016,
	btn_liberotastostampa017,
	btn_liberotastostampa018,
	btn_liberotastostampa019,
	btn_liberotastobrowser000,
	btn_liberotastobrowser001,
	btn_liberotastobrowser002,
	btn_liberotastobrowser003,
	btn_liberotastobrowser004,
	btn_liberotastobrowser005,
	btn_liberotastobrowser006,
	btn_liberotastobrowser007,
	btn_liberotastobrowser008,
	btn_liberotastobrowser009,
	btn_liberotastobrowser010,
	btn_liberotastobrowser011,
	btn_liberotastobrowser012,
	btn_liberotastobrowser013,
	btn_liberotastobrowser014,
	btn_liberotastobrowser015,
	btn_liberotastobrowser016,
	btn_liberotastobrowser017,
	btn_liberotastobrowser018,
	btn_liberotastobrowser019,
	btn_liberotastoeseguibile000,
	btn_liberotastoeseguibile001,
	btn_liberotastoeseguibile002,
	btn_liberotastoeseguibile003,
	btn_liberotastoeseguibile004,
	btn_liberotastoeseguibile005,
	btn_liberotastoeseguibile006,
	btn_liberotastoeseguibile007,
	btn_liberotastoeseguibile008,
	btn_liberotastoeseguibile009,
	btn_liberotastoeseguibile010,
	btn_liberotastoeseguibile011,
	btn_liberotastoeseguibile012,
	btn_liberotastoeseguibile013,
	btn_liberotastoeseguibile014,
	btn_liberotastoeseguibile015,
	btn_liberotastoeseguibile016,
	btn_liberotastoeseguibile017,
	btn_liberotastoeseguibile018,
	btn_liberotastoeseguibile019,
	edt_integrazioni,
	sub_monitoraggio_oriz,
	edt_anestesista,
	sub_rao,
	sub_consensoinformato,
	sub_legenda1,
	sub_legenda2,
	edt_sedeesame,
	edt_salaesame,
	sub_codificadiagnosiesame,
	sub_legenda3,
	sub_esamipregressi,
	edt_inviante1,
	edt_inviante2,
	edt_inviante3,
	edt_inviante_i,
	edt_inviante_e,
	edt_paziente_medicocurante,
	sub_anatomiapatologica,
	edt_anatomiapatologicanote,
	sub_anatomiapatologicaprest,
	edt_anatomiapatologicarefer,
	edt_anatomiapatologicarefer_rtf,
	sub_anatomiapatologicatasti,
	edt_anatomiapatologicasugger1,
	edt_anatomiapatologicasugger2,
	edt_organosedeprevista,
	edt_organosederaggiunta,

	sub_allergie,
	sub_pacemaker,
	sub_portatorepacemaker,
	sub_anticoagulanti,
	sub_antiaggreganti,
	sub_regione5righe,
	sub_codificadiagnosiesame5righe,

	edt_fumo,
	edt_caffe,
	edt_sigarette,
	edt_farmaci,
	edt_alcool,
	edt_assunzione,
	edt_superalcolici,
	sub_bmi,
	sub_volume,

	sub_terapiainatto_testo,
	sub_fluoroscopia,
	sub_accessori5righe,
	sub_monitoraggio_vert,

	sub_istopatologia5righe,

	cmb_complicanzeimmediate,
	cmb_complicanzetardive,
	cmb_pulizia,
	cmb_causenoncompletamento,
	cmb_tolleranza,
	cmb_conclusioniscreening,
	cmb_conclusionicolon,
	cmb_diagnosifinale,
	sub_necassospedaliera,
	edt_premedposologia,
	cmb_altreanomalie,

	edt_mst_complicanze1,
	edt_mst_complicanze2,
	edt_mst_complicanze3,

	btn_chiusuraesame,
	btn_convalida,

	sub_breathtest_hp,
	sub_sospensione,
	sub_procedureicd9,
	sub_diagnosiicd9,

	edt_codesame,

	sub_puntipaziente,

	edt_tempochiusura,
	edt_tempoconvalida,
	edt_codicericovero,
	edt_assiden,
	edt_codalfa,

	edt_pressione,

	edt_barcodericovero,

	btn_videocapsula,

	edt_esamestrumentale_orainizio,
	edt_esamestrumentale_orafine,
	edt_esamestrumentale_durataoreminuti,
	edt_esamestrumentale_duratasolominuti,

	sub_pazienticronici_terapia,
	edt_pazienticronici_score_hb,
	edt_pazienticronici_score_s,

	sub_tabellaebus,
	sub_studio,

	edt_utente_inserimentoesame,

	edt_data_referto_istologico,
	sub_presenzalesioneCCR,
	edt_numerototalepolipi,

	sub_bostonscore,
	edt_temporetrazione,

	sub_istopatologia5righe_plus,

	btn_centralerefertazione,
	btn_carestream,

	// queste form mostrano in maschera le informazioni che rimangono nella tabella ext_ordini o dicomWorklist
	edt_integrazioneCodiceUrgenza,

	//rima 16007 nuova form diagnosi icd9
	sub_diagnosiicd9ex,
	sub_diagnosifinaliicd9ex,

	//Simone RIMA 16052 - Campi etichetta
	sub_etichetta000,
	sub_etichetta001,
	sub_etichetta002,
	sub_etichetta003,
	sub_etichetta004,
	sub_etichetta005,
	sub_etichetta006,
	sub_etichetta007,
	sub_etichetta008,
	sub_etichetta009,
	sub_etichetta010,
	sub_etichetta011,
	sub_etichetta012,
	sub_etichetta013,
	sub_etichetta014,
	sub_etichetta015,
	sub_etichetta016,
	sub_etichetta017,
	sub_etichetta018,
	sub_etichetta019,
	sub_etichetta020,
	sub_etichetta021,
	sub_etichetta022,
	sub_etichetta023,
	sub_etichetta024,
	sub_etichetta025,
	sub_etichetta026,
	sub_etichetta027,
	sub_etichetta028,
	sub_etichetta029,
	sub_etichetta030,
	sub_etichetta031,
	sub_etichetta032,
	sub_etichetta033,
	sub_etichetta034,
	sub_etichetta035,
	sub_etichetta036,
	sub_etichetta037,
	sub_etichetta038,
	sub_etichetta039,

	//Simone - tasti chiusura fase
	btn_liberotastochiusurafase000,
	btn_liberotastochiusurafase001,
	btn_liberotastochiusurafase002,
	btn_liberotastochiusurafase003,
	btn_liberotastochiusurafase004,
	btn_liberotastochiusurafase005,
	btn_liberotastochiusurafase006,
	btn_liberotastochiusurafase007,
	btn_liberotastochiusurafase008,
	btn_liberotastochiusurafase009,
	btn_liberotastochiusurafase010,
	btn_liberotastochiusurafase011,
	btn_liberotastochiusurafase012,
	btn_liberotastochiusurafase013,
	btn_liberotastochiusurafase014,
	btn_liberotastochiusurafase015,
	btn_liberotastochiusurafase016,
	btn_liberotastochiusurafase017,
	btn_liberotastochiusurafase018,
	btn_liberotastochiusurafase019,

	//Simone - Checklist a griglia
	sub_gridcl000,
	sub_gridcl001,
	sub_gridcl002,
	sub_gridcl003,
	sub_gridcl004,
	sub_gridcl005,
	sub_gridcl006,
	sub_gridcl007,
	sub_gridcl008,
	sub_gridcl009,
	sub_gridcl010,
	sub_gridcl011,
	sub_gridcl012,
	sub_gridcl013,
	sub_gridcl014,
	sub_gridcl015,
	sub_gridcl016,
	sub_gridcl017,
	sub_gridcl018,
	sub_gridcl019,
	sub_gridcl020,
	sub_gridcl021,
	sub_gridcl022,
	sub_gridcl023,
	sub_gridcl024,
	sub_gridcl025,
	sub_gridcl026,
	sub_gridcl027,
	sub_gridcl028,
	sub_gridcl029,
	sub_gridcl030,
	sub_gridcl031,
	sub_gridcl032,
	sub_gridcl033,
	sub_gridcl034,
	sub_gridcl035,
	sub_gridcl036,
	sub_gridcl037,
	sub_gridcl038,
	sub_gridcl039,

	cmb_esameurgente, // Sandro 20/06/2016 // RIMA 16001 RN20 //
	sub_codiciclassificazionediagnostica,
	sub_cardio_prima,
	sub_cardio_durante,
	sub_cardio_dopo,

	edt_esame_coniugato,
	sub_centraledistampa,
	sub_mielogramma,
	//Julio - Genomica
	btn_refertogenomica,
	btn_libera_laudo, // Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
	//Luiz - 13/05/2019 - P3 - Atualiza nome/sobrenome Médico - Inclui Médicos solicitantes
	edt_medico2,
	edt_medico3,
	edt_medico4,
	
	edt_paziente_passaporto,	//Julio - BUG 3285 - Adequação de laudos(extra)
	edt_paziente_doc1,			//Julio - BUG 3285 - Adequação de laudos(extra)
	edt_paziente_doc2,			//Julio - BUG 3285 - Adequação de laudos(extra)

	edt_refertointegrato_macro,     //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
	edt_refertointegrato_diag,      //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
	edt_refertointegrato_firma,     //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture

	sub_schemi_anatomichi, // Marvel Carvalho - BUG 4308 Esquemas Anatômicos Fleury
	
	btn_invia_altra_unita, //Gabriel - TCP

	// [...] continuare ad aggiungere qui sopra [...] //

	// lasciare questi 9 sempre ultimi --> //
	btn_codificadiagnosiesame5righe,
	btn_osservazioni,
	btn_diagnostiche,
	btn_terapeutiche,	
	btn_diagnosi,
	btn_codificadiagnosiesame,
	btn_complicanze1,
	btn_complicanze2,
	btn_complicanze3,
	// <-- lasciare questi 9 sempre ultimi //

	form_list_total
};

#define SUB_ABITUDINI					10000
#define SUB_CHIRURGICI					10001
#define SUB_ENDOSCOPICI					10002
#define SUB_FAMILIARITA					10003
#define SUB_INDAGINI					10004
#define SUB_MALATTIE					10005
#define EDT_PROGRESSIVO					10007
#define EDT_DATAESAME					10008
#define CMB_TIPOESAME					10009
#define EDT_PROGRESSIVOANNO				10010
#define CMB_MEDICO1						10011
#define CMB_MEDICO2						10012
#define CMB_INFERMIERE1					10013
#define CMB_INFERMIERE2					10014
#define SUB_INVIANTE					10015
#define EDT_CAMERA						10016
#define EDT_INDICAZIONI					10018
#define EDT_FARMACOTRIAL				10019
#define EDT_PREMEDICAZIONI				10020
#define SUB_TERAPIAINATTO				10021
#define SUB_OSSERVAZIONI				10022
#define EDT_DIAGNOSTICHE				10023
#define EDT_TERAPEUTICHE				10024
#define SUB_DIAGNOSI					10025
#define EDT_CONDOTTOFINO				10026
#define EDT_VALUTAZIONE					10027
#define EDT_COMPLICANZE					10028
#define EDT_COMPLICANZEPROVVEDIMENTI	10034
#define EDT_COMPLICANZETERAPIA			10029
#define EDT_COMPLICANZEESITO			10035
#define EDT_TIPOVISITA					10030
#define EDT_QUADRO						10031
#define EDT_DURATA						10032
#define EDT_PROSSIMO					10033
#define EDT_STUDIO						10036
#define EDT_GUARIGIONE					10037
#define EDT_DIFFICOLTA					10038
#define SUB_REGIONE						10039
#define EDT_TERAPIACONSIGLIATA			10040
#define EDT_STRUMENTI					10041
#define EDT_ACCESSORI					10042
#define EDT_NOTE						10043
#define SUB_ISTOPATOLOGIA				10044
#define SUB_REFERTO						10045
#define EDT_RIFERIMENTO					10046
#define EDT_LIBERO000					10047
#define EDT_LIBERO001					10048
#define EDT_LIBERO002					10049
#define EDT_LIBERO003					10050
#define EDT_LIBERO004					10051
#define EDT_LIBERO005					10052
#define EDT_INTEGRAZIONI				10053
#define BTN_OSSERVAZIONI				10054
#define BTN_DIAGNOSTICHE				10055
#define BTN_TERAPEUTICHE				10056
#define BTN_DIAGNOSI					10057
#define SUB_MONITORAGGIO_ORIZ			10058
#define EDT_ANESTESISTA					10059
#define SUB_RAO							10060
#define SUB_CONSENSOINFORMATO			10061
#define SUB_LEGENDA1					10062
#define SUB_LEGENDA2					10063
#define EDT_SEDEESAME					10064
#define EDT_LIBERO006					10066
#define EDT_LIBERO007					10067
#define EDT_LIBERO008					10068
#define EDT_LIBERO009					10069
#define EDT_LIBERO010					10070
#define EDT_LIBERO011					10071
#define EDT_LIBERO012					10072
#define EDT_LIBERO013					10073
#define EDT_LIBERO014					10074
#define EDT_LIBERO015					10075
#define EDT_LIBERO016					10076
#define EDT_LIBERO017					10077
#define EDT_LIBERO018					10078
#define EDT_LIBERO019					10079
#define SUB_CODIFICADIAGNOSIESAME		10080
#define BTN_CODIFICADIAGNOSIESAME		10081
#define SUB_LEGENDA3					10082
#define SUB_ESAMIPREGRESSI				10083
#define EDT_INVIANTE1					10084
#define EDT_INVIANTE2					10085
#define EDT_INVIANTE3					10086
#define SUB_ANATOMIAPATOLOGICA			10087
#define EDT_ANATOMIAPATOLOGICANOTE		10088
#define SUB_ANATOMIAPATOLOGICAPREST		10089
#define EDT_ANATOMIAPATOLOGICAREFER		10090
#define SUB_ANATOMIAPATOLOGICATASTI		10091
#define EDT_ANATOMIAPATOLOGICASUGGER1	10093
#define EDT_LIBERO020					10094
#define EDT_LIBERO021					10095
#define EDT_LIBERO022					10096
#define EDT_LIBERO023					10097
#define EDT_LIBERO024					10098
#define EDT_LIBERO025					10099
#define EDT_LIBERO026					10100
#define EDT_LIBERO027					10101
#define EDT_LIBERO028					10102
#define EDT_LIBERO029					10103
#define EDT_LIBERO030					10104
#define EDT_LIBERO031					10105
#define EDT_LIBERO032					10106
#define EDT_LIBERO033					10107
#define EDT_LIBERO034					10108
#define EDT_LIBERO035					10109
#define EDT_LIBERO036					10110
#define EDT_LIBERO037					10111
#define EDT_LIBERO038					10112
#define EDT_LIBERO039					10113
#define EDT_LIBERO040					10114
#define EDT_LIBERO041					10115
#define EDT_LIBERO042					10116
#define EDT_LIBERO043					10117
#define EDT_LIBERO044					10118
#define EDT_LIBERO045					10119
#define EDT_LIBERO046					10120
#define EDT_LIBERO047					10121
#define EDT_LIBERO048					10122
#define EDT_LIBERO049					10123
#define EDT_ORGANOSEDEPREVISTA			10124
#define EDT_ORGANOSEDERAGGIUNTA			10125
#define SUB_ISTOPATOLOGIA5RIGHE			10126
#define SUB_ALLERGIE					10225
#define SUB_PACEMAKER					10226
#define EDT_ANATOMIAPATOLOGICASUGGER2	10228
#define EDT_SALAESAME					10229
#define EDT_ANATOMIAPATOLOGICAREFER_RTF	10230
#define EDT_LIBERORTF000				10234
#define EDT_LIBERORTF001				10235
#define EDT_LIBERORTF002				10236
#define EDT_LIBERORTF003				10237
#define EDT_LIBERORTF004				10238
#define EDT_LIBERORTF005				10239
#define EDT_LIBERORTF006				10240
#define EDT_LIBERORTF007				10241
#define EDT_LIBERORTF008				10242
#define EDT_LIBERORTF009				10243
#define SUB_PORTATOREPACEMAKER			10244
#define SUB_ANTICOAGULANTI				10245
#define SUB_ANTIAGGREGANTI				10246
#define SUB_REGIONE5RIGHE				10247
#define SUB_CODIFICADIAGNOSIESAME5RIGHE	10248
#define BTN_CODIFICADIAGNOSIESAME5RIGHE	10249
#define EDT_FUMO						10250
#define EDT_CAFFE						10251
#define EDT_SIGARETTE					10252
#define EDT_FARMACI						10253
#define EDT_ALCOOL						10254
#define EDT_ASSUNZIONE					10255
#define EDT_SUPERALCOLICI				10256
#define SUB_BMI							10257
#define SUB_TERAPIAINATTO_TESTO			10258
#define SUB_FLUOROSCOPIA				10259
#define SUB_ACCESSORI5RIGHE				10260
#define SUB_MONITORAGGIO_VERT			10261
#define BTN_CONVALIDA					10262
#define EDT_INVIANTE_I					10263
#define EDT_INVIANTE_E					10264

// screening //
#define CMB_COMPLICANZEIMMEDIATE		10267
#define CMB_COMPLICANZETARDIVE			10268
#define	CMB_PULIZIA						10269
#define	CMB_CAUSENONCOMPLETAMENTO		10270
#define	CMB_TOLLERANZA					10271 
#define	CMB_CONCLUSIONISCREENING		10272
#define	CMB_CONCLUSIONICOLON			10273
#define SUB_NECASSOSPEDALIERA			10274
#define EDT_PREMEDPOSOLOGIA				10275

#define BTN_CHIUSURAESAME				10276
#define EDT_LIBEROCL000					10277
#define EDT_LIBEROCL001					10278
#define EDT_LIBEROCL002					10279
#define EDT_LIBEROCL003					10280
#define EDT_LIBEROCL004					10281
#define EDT_LIBEROCL005					10282
#define EDT_LIBEROCL006					10283
#define EDT_LIBEROCL007					10284
#define EDT_LIBEROCL008					10285
#define EDT_LIBEROCL009					10286

#define BTN_COMPLICANZE1				10287
#define BTN_COMPLICANZE2				10288
#define BTN_COMPLICANZE3				10289
#define EDT_MST_COMPLICANZE1			10290
#define EDT_MST_COMPLICANZE2			10291
#define EDT_MST_COMPLICANZE3			10292

#define SUB_BREATHTEST_HP				10293

#define EDT_LIBERO050					10294
#define EDT_LIBERO051					10295
#define EDT_LIBERO052					10296
#define EDT_LIBERO053					10297
#define EDT_LIBERO054					10298
#define EDT_LIBERO055					10299
#define EDT_LIBERO056					10300
#define EDT_LIBERO057					10301
#define EDT_LIBERO058					10302
#define EDT_LIBERO059					10303

#define	CMB_DIAGNOSIFINALE				10304

#define EDT_LIBERORTF010				10305
#define EDT_LIBERORTF011				10306
#define EDT_LIBERORTF012				10307
#define EDT_LIBERORTF013				10308
#define EDT_LIBERORTF014				10309
#define EDT_LIBERORTF015				10310
#define EDT_LIBERORTF016				10311
#define EDT_LIBERORTF017				10312
#define EDT_LIBERORTF018				10313
#define EDT_LIBERORTF019				10314

#define EDT_LIBEROCL010					10315
#define EDT_LIBEROCL011					10316
#define EDT_LIBEROCL012					10317
#define EDT_LIBEROCL013					10318
#define EDT_LIBEROCL014					10319
#define EDT_LIBEROCL015					10320
#define EDT_LIBEROCL016					10321
#define EDT_LIBEROCL017					10322
#define EDT_LIBEROCL018					10323
#define EDT_LIBEROCL019					10324

#define EDT_LIBERODATAORA000			10325
#define EDT_LIBERODATAORA001			10326
#define EDT_LIBERODATAORA002			10327
#define EDT_LIBERODATAORA003			10328
#define EDT_LIBERODATAORA004			10329
#define EDT_LIBERODATAORA005			10330
#define EDT_LIBERODATAORA006			10331
#define EDT_LIBERODATAORA007			10332
#define EDT_LIBERODATAORA008			10333
#define EDT_LIBERODATAORA009			10334
#define EDT_LIBERODATAORA010			10335
#define EDT_LIBERODATAORA011			10336
#define EDT_LIBERODATAORA012			10337
#define EDT_LIBERODATAORA013			10338
#define EDT_LIBERODATAORA014			10339
#define EDT_LIBERODATAORA015			10340
#define EDT_LIBERODATAORA016			10341
#define EDT_LIBERODATAORA017			10342
#define EDT_LIBERODATAORA018			10343
#define EDT_LIBERODATAORA019			10344

#define SUB_SOSPENSIONE					10345

#define SUB_PROCEDUREICD9				10346
#define SUB_DIAGNOSIICD9				10347

#define EDT_LIBERO060					10348
#define EDT_LIBERO061					10349
#define EDT_LIBERO062					10350
#define EDT_LIBERO063					10351
#define EDT_LIBERO064					10352
#define EDT_LIBERO065					10353
#define EDT_LIBERO066					10354
#define EDT_LIBERO067					10355
#define EDT_LIBERO068					10356
#define EDT_LIBERO069					10357
#define EDT_LIBERO070					10358
#define EDT_LIBERO071					10359
#define EDT_LIBERO072					10360
#define EDT_LIBERO073					10361
#define EDT_LIBERO074					10362
#define EDT_LIBERO075					10363
#define EDT_LIBERO076					10364
#define EDT_LIBERO077					10365
#define EDT_LIBERO078					10366
#define EDT_LIBERO079					10367
#define EDT_LIBERO080					10368
#define EDT_LIBERO081					10369
#define EDT_LIBERO082					10370
#define EDT_LIBERO083					10371
#define EDT_LIBERO084					10372
#define EDT_LIBERO085					10373
#define EDT_LIBERO086					10374
#define EDT_LIBERO087					10375
#define EDT_LIBERO088					10376
#define EDT_LIBERO089					10377
#define EDT_LIBERO090					10378
#define EDT_LIBERO091					10379
#define EDT_LIBERO092					10380
#define EDT_LIBERO093					10381
#define EDT_LIBERO094					10382
#define EDT_LIBERO095					10383
#define EDT_LIBERO096					10384
#define EDT_LIBERO097					10385
#define EDT_LIBERO098					10386
#define EDT_LIBERO099					10387

#define EDT_CODESAME					10388

#define SUB_PUNTIPAZIENTE				10389

#define EDT_TEMPOCHIUSURA				10390
#define EDT_TEMPOCONVALIDA				10391
#define EDT_CODICERICOVERO				10392

#define EDT_ASSIDEN						10393

#define	EDT_PRESSIONE					10401

#define EDT_BARCODERICOVERO				10404

#define BTN_VIDEOCAPSULA				10405

#define EDT_ESAMESTRUMENTALE_ORAINIZIO			10407
#define EDT_ESAMESTRUMENTALE_ORAFINE			10408
#define EDT_ESAMESTRUMENTALE_DURATAOREMINUTI	10409
#define EDT_ESAMESTRUMENTALE_DURATASOLOMINUTI	10410

#define BTN_LIBEROTASTOSTAMPA000				10412
#define BTN_LIBEROTASTOSTAMPA001				10413
#define BTN_LIBEROTASTOSTAMPA002				10414
#define BTN_LIBEROTASTOSTAMPA003				10415
#define BTN_LIBEROTASTOSTAMPA004				10416
#define BTN_LIBEROTASTOSTAMPA005				10417
#define BTN_LIBEROTASTOSTAMPA006				10418
#define BTN_LIBEROTASTOSTAMPA007				10419
#define BTN_LIBEROTASTOSTAMPA008				10420
#define BTN_LIBEROTASTOSTAMPA009				10421
#define BTN_LIBEROTASTOSTAMPA010				10422
#define BTN_LIBEROTASTOSTAMPA011				10423
#define BTN_LIBEROTASTOSTAMPA012				10424
#define BTN_LIBEROTASTOSTAMPA013				10425
#define BTN_LIBEROTASTOSTAMPA014				10426
#define BTN_LIBEROTASTOSTAMPA015				10427
#define BTN_LIBEROTASTOSTAMPA016				10428
#define BTN_LIBEROTASTOSTAMPA017				10429
#define BTN_LIBEROTASTOSTAMPA018				10430
#define BTN_LIBEROTASTOSTAMPA019				10431
#define BTN_LIBEROTASTOBROWSER000				10432
#define BTN_LIBEROTASTOBROWSER001				10433
#define BTN_LIBEROTASTOBROWSER002				10434
#define BTN_LIBEROTASTOBROWSER003				10435
#define BTN_LIBEROTASTOBROWSER004				10436
#define BTN_LIBEROTASTOBROWSER005				10437
#define BTN_LIBEROTASTOBROWSER006				10438
#define BTN_LIBEROTASTOBROWSER007				10439
#define BTN_LIBEROTASTOBROWSER008				10440
#define BTN_LIBEROTASTOBROWSER009				10441
#define BTN_LIBEROTASTOBROWSER010				10442
#define BTN_LIBEROTASTOBROWSER011				10443
#define BTN_LIBEROTASTOBROWSER012				10444
#define BTN_LIBEROTASTOBROWSER013				10445
#define BTN_LIBEROTASTOBROWSER014				10446
#define BTN_LIBEROTASTOBROWSER015				10447
#define BTN_LIBEROTASTOBROWSER016				10448
#define BTN_LIBEROTASTOBROWSER017				10449
#define BTN_LIBEROTASTOBROWSER018				10450
#define BTN_LIBEROTASTOBROWSER019				10451
#define BTN_LIBEROTASTOESEGUIBILE000			10452
#define BTN_LIBEROTASTOESEGUIBILE001			10453
#define BTN_LIBEROTASTOESEGUIBILE002			10454
#define BTN_LIBEROTASTOESEGUIBILE003			10455
#define BTN_LIBEROTASTOESEGUIBILE004			10456
#define BTN_LIBEROTASTOESEGUIBILE005			10457
#define BTN_LIBEROTASTOESEGUIBILE006			10458
#define BTN_LIBEROTASTOESEGUIBILE007			10459
#define BTN_LIBEROTASTOESEGUIBILE008			10460
#define BTN_LIBEROTASTOESEGUIBILE009			10461
#define BTN_LIBEROTASTOESEGUIBILE010			10462
#define BTN_LIBEROTASTOESEGUIBILE011			10463
#define BTN_LIBEROTASTOESEGUIBILE012			10464
#define BTN_LIBEROTASTOESEGUIBILE013			10465
#define BTN_LIBEROTASTOESEGUIBILE014			10466
#define BTN_LIBEROTASTOESEGUIBILE015			10467
#define BTN_LIBEROTASTOESEGUIBILE016			10468
#define BTN_LIBEROTASTOESEGUIBILE017			10469
#define BTN_LIBEROTASTOESEGUIBILE018			10470
#define BTN_LIBEROTASTOESEGUIBILE019			10471

#define SUB_PAZIENTICRONICI_TERAPIA				10472
#define	EDT_PAZIENTICRONICI_SCORE_HB			10473
#define	EDT_PAZIENTICRONICI_SCORE_S				10474
#define SUB_TABELLAEBUS							10475
#define EDT_PAZIENTE_MEDICOCURANTE				10476
#define SUB_STUDIO								10477

#define EDT_CODALFA								10478
#define EDT_UTENTE_INSERIMENTOESAME				10479
#define EDT_CODICEPRENOTAZIONE					10480

#define EDT_DATAREFERTOISTOLOGICO				10481
#define SUB_PRESENZALESIONECCR					10482
#define EDT_NUMEROTOTALEPOLIPI					10483

#define SUB_BOSTONSCORE							10484
#define EDT_TEMPORETRAZIONE						10485

#define EDT_MEDICO_RICERCA						10487

#define SUB_ISTOPATOLOGIA5RIGHE_PLUS			10489

#define CMB_ALTREANOMALIE						10490

#define EDT_INTEGRAZIONECODICEURGENZA			10494

#define SUB_DIAGNOSIICD9EX						10496
#define BTN_CENTRALEREFERTAZIONE				10497
#define SUB_DIAGNOSIFINALEICD9EX				10498

#define SUB_ETICHETTA000						10500
#define SUB_ETICHETTA001						10501
#define SUB_ETICHETTA002						10502
#define SUB_ETICHETTA003						10503
#define SUB_ETICHETTA004						10504
#define SUB_ETICHETTA005						10505
#define SUB_ETICHETTA006						10506
#define SUB_ETICHETTA007						10507
#define SUB_ETICHETTA008						10508
#define SUB_ETICHETTA009						10509
#define SUB_ETICHETTA010						10510
#define SUB_ETICHETTA011						10511
#define SUB_ETICHETTA012						10512
#define SUB_ETICHETTA013						10513
#define SUB_ETICHETTA014						10514
#define SUB_ETICHETTA015						10515
#define SUB_ETICHETTA016						10516
#define SUB_ETICHETTA017						10517
#define SUB_ETICHETTA018						10518
#define SUB_ETICHETTA019						10519
#define SUB_ETICHETTA020						10520
#define SUB_ETICHETTA021						10521
#define SUB_ETICHETTA022						10522
#define SUB_ETICHETTA023						10523
#define SUB_ETICHETTA024						10524
#define SUB_ETICHETTA025						10525
#define SUB_ETICHETTA026						10526
#define SUB_ETICHETTA027						10527
#define SUB_ETICHETTA028						10528
#define SUB_ETICHETTA029						10529
#define SUB_ETICHETTA030						10530
#define SUB_ETICHETTA031						10531
#define SUB_ETICHETTA032						10532
#define SUB_ETICHETTA033						10533
#define SUB_ETICHETTA034						10534
#define SUB_ETICHETTA035						10535
#define SUB_ETICHETTA036						10536
#define SUB_ETICHETTA037						10537
#define SUB_ETICHETTA038						10538
#define SUB_ETICHETTA039						10539

#define BTN_LIBEROTASTOCHIUSURAFASE000			10540
#define BTN_LIBEROTASTOCHIUSURAFASE001			10541
#define BTN_LIBEROTASTOCHIUSURAFASE002			10542
#define BTN_LIBEROTASTOCHIUSURAFASE003			10543
#define BTN_LIBEROTASTOCHIUSURAFASE004			10544
#define BTN_LIBEROTASTOCHIUSURAFASE005			10545
#define BTN_LIBEROTASTOCHIUSURAFASE006			10546
#define BTN_LIBEROTASTOCHIUSURAFASE007			10547
#define BTN_LIBEROTASTOCHIUSURAFASE008			10548
#define BTN_LIBEROTASTOCHIUSURAFASE009			10549
#define BTN_LIBEROTASTOCHIUSURAFASE010			10550
#define BTN_LIBEROTASTOCHIUSURAFASE011			10551
#define BTN_LIBEROTASTOCHIUSURAFASE012			10552
#define BTN_LIBEROTASTOCHIUSURAFASE013			10553
#define BTN_LIBEROTASTOCHIUSURAFASE014			10554
#define BTN_LIBEROTASTOCHIUSURAFASE015			10555
#define BTN_LIBEROTASTOCHIUSURAFASE016			10556
#define BTN_LIBEROTASTOCHIUSURAFASE017			10557
#define BTN_LIBEROTASTOCHIUSURAFASE018			10558
#define BTN_LIBEROTASTOCHIUSURAFASE019			10559

#define SUB_GRIDCL000							10560
#define SUB_GRIDCL001							10561
#define SUB_GRIDCL002							10562
#define SUB_GRIDCL003							10563
#define SUB_GRIDCL004							10564
#define SUB_GRIDCL005							10565
#define SUB_GRIDCL006							10566
#define SUB_GRIDCL007							10567
#define SUB_GRIDCL008							10568
#define SUB_GRIDCL009							10569
#define SUB_GRIDCL010							10570
#define SUB_GRIDCL011							10571
#define SUB_GRIDCL012							10572
#define SUB_GRIDCL013							10573
#define SUB_GRIDCL014							10574
#define SUB_GRIDCL015							10575
#define SUB_GRIDCL016							10576
#define SUB_GRIDCL017							10577
#define SUB_GRIDCL018							10578
#define SUB_GRIDCL019							10579
#define SUB_GRIDCL020							10580
#define SUB_GRIDCL021							10581
#define SUB_GRIDCL022							10582
#define SUB_GRIDCL023							10583
#define SUB_GRIDCL024							10584
#define SUB_GRIDCL025							10585
#define SUB_GRIDCL026							10586
#define SUB_GRIDCL027							10587
#define SUB_GRIDCL028							10588
#define SUB_GRIDCL029							10589
#define SUB_GRIDCL030							10590
#define SUB_GRIDCL031							10591
#define SUB_GRIDCL032							10592
#define SUB_GRIDCL033							10593
#define SUB_GRIDCL034							10594
#define SUB_GRIDCL035							10595
#define SUB_GRIDCL036							10596
#define SUB_GRIDCL037							10597
#define SUB_GRIDCL038							10598
#define SUB_GRIDCL039							10599

#define CMB_ESAMEURGENTE						10600
#define BTN_CARESTREAM							10601
#define SUB_CODICICLASSIFICAZIONEDIAGNOSTICA	10602
#define SUB_VOLUME								10603
#define SUB_CARDIO_PRIMA						10604
#define SUB_CARDIO_DURANTE						10605
#define SUB_CARDIO_DOPO							10606

#define EDT_ESAME_CONIUGATO						10607
#define SUB_CENTRALEDISTAMPA					10608
#define SUB_MIELOGRAMMA							10609
#define BTN_REFERTOGENOMICA						10610 //Julio - Genomica
#define BTN_LIBERA_LAUDO                        10611 // Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
//Luiz - 13/05/2019 - P3 - Atualiza nome/sobrenome Médico - Inclui Médicos solicitantes
#define EDT_MEDICO2                             10612
#define EDT_MEDICO3                             10613
#define EDT_MEDICO4                             10614
//

#define EDT_PAZIENTE_PASSAPORTO					10615	//Julio - BUG 3285 - Adequação de laudos
#define EDT_PAZIENTE_DOC1						10616	//Julio - BUG 3285 - Adequação de laudos
#define EDT_PAZIENTE_DOC2						10617	//Julio - BUG 3285 - Adequação de laudos

#define EDT_REFERTOINTEGRATO_MACRO				10618   //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
#define EDT_REFERTOINTEGRATO_DIAG				10619   //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
#define EDT_REFERTOINTEGRATO_FIRMA				10620   //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture

#define SUB_SCHEMI_ANATOMICHI					10621   // Marvel Carvalho - BUG 4308 Esquemas Anatômicos Fleury

#define BTN_INVIAALTRAUNITA						10622	//Gabriel - TCP
//


typedef struct Form_Caract
{
	long lID;
	CString sDescrizione;

	long lMinA;
	long lMaxA;

	long lMinL;
	long lMaxL;

	BOOL bEndox;
	BOOL bImageNT;

} FORM_CARACT;
extern FORM_CARACT g_FormCaract[form_list_total];

//

// Marvel Carvalho - Bug 3457 (FIX) TEXTER
int CStringFindLastIndexOf(const CString& strFullText, const CString& strThingToLookFor);
void pressKey(WORD key);
CString cleanFinalDoubleParInRTF(CString p_strRTF);

// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#1 - dual screen)
// Marvel Carvalho - Bug 5503 Eliminar popup "exame sem imagens" na DO
void DoPopupImgWithSecondScreenConfiguration(CWnd* pParent, CEsamiView* pEsamiView, CString p_sWhichDlg, CString p_sTargetScreen, BOOL p_bAutomatedMode, long lPaziente, long lEsame, long lID, int iType, BOOL p_bIsAlbumGlobal);
void CenterWndInSecondScreen(CWnd* const pWnd, BOOL bMaximize = TRUE); //Gabriel BUG 6225 - Lista DO
void CenterWndInFirstScreen(CWnd* const pWnd, BOOL bMaximize = TRUE); //Gabriel BUG 6225 - Lista DO
void Maximize(HWND hWnd, HMONITOR hMonitor); //Gabriel BUG 6225 - Lista DO
// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnesi)
void AppendTextToEditCtrl(CEdit& edit, LPCTSTR pszText);

void TraceAndLog(CString sMessage, long lTime = -1); //Julio facilitando o log durante o DEBUG

BOOL CreateLogFolderIfNotExists(CString p_strPath);

void TrySetCustomListOrder(CString sCustomOrder, CListCtrl* pListCtrl); //Gabriel BUG 6225 - Lista DO FIX

#endif /* __COMMON_H__ */
