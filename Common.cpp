#include "stdafx.h"
#include "Endox.h"
#include "common.h"

#include <io.h>
#include <direct.h>
#include <GdiPlus.h>
#include <math.h>
#include <windowsx.h>
#include <errno.h>
#include <atlstr.h>
#include <stdio.h>

#include "DLL_Imaging\h\AmBase64.h"
#include "DLL_Imaging\h\AMLogin.h"
#include "DLL_Imaging\h\ExamService.h"
#include "DLL_Imaging\h\FindFichaService.h"
#include "DLL_Imaging\h\GetPatientExamDataService.h"
#include "DLL_Imaging\h\ImgArchive.h"
#include "DLL_Imaging\h\SetExamOtherLocationService.h"
#include "DLL_Imaging\h\UserService.h"
#include "DLL_Imaging\h\WriteValuesIntoDBService.h"

#include "CentriDiCostoSet.h"
#include "CodiciClassificazioneDiagnosticaSet.h"
#include "CodificaRegionaleExSet.h"
#include "ComboBoxSet.h"
#include "ComboTransSet.h"
#include "CupWorkListManager.h"
#include "CustomDate.h"
#include "Define.h"
#include "DiagnosiEsamiSet.h"
#include "DiagnosiICD9Set.h"
#include "Dib.h"
#include "DocManager.h"
#include "DynVersioneSet.h"
#include "EliminaCodeSet.h"
#include "EsamiAccettatiSet.h"
#include "EsamiChiusiSet.h"
#include "EsamiCodiciClassDiagnostSet.h"
#include "EsamiView.h"
#include "ExamListDlg.h"
#include "ExtMinPazDataSetSet.h"
#include "ExtOrdiniAllegatiSet.h"
#include "ExtOrdiniDiagnosiICD9Set.h"
#include "ExtOrdiniOperatoriSet.h"
#include "ExtOrdiniProcedureICD9Set.h"
#include "ExtOrdiniSet.h"
#include "ExtPatientEventSet.h"
#include "ExtTransUrgenzaSet.h"
#include "FieldDlg.h"
#include "FleurySceltaRiaperturaDlg.h"
#include "InfermieriSet.h"
#include "InsertLogAcquisizioneSPSet.h"
#include "InviantiSet.h"
#include "LogFileWriter.h"
#include "MaskEdit.h"
#include "MediciSet.h"
#include "MessageBoxTimerDlg.h"
#include "MMSystem.h"
#include "MstOrganoSet.h"
#include "PazientiSet.h"
#include "PdfManager.h"
#include "PrinterSettings.h"
#include "ProcedureEsamiSet.h"
#include "ProcedureICD9Set.h"
#include "ProtocolloCardioSet.h"
#include "ProtocolloColonneSet.h"
#include "ProtocolloEsamiSet.h"
#include "ProvenienzaSet.h"
#include "QueryDlg.h"
#include "RegioneSet.h"
#include "SediEsameSet.h"
#include "ShowDbQueriesDlg.h"
#include "TabellaEsamiSet.h"
#include "TabellaParametriSet.h"
#include "TabellaStruttureSet.h"
#include "TipiEsamiProgressivoAnnualeSet.h"
#include "TipoEsameNew.h"
#include "TipoEsameSet.h"
#include "UOSet.h"
#include "UtentiSet.h"
#include "UXTheme.h"
#include "VistaEsamiPerWLSet.h"
#include "VistaExtPrestazioniSet.h"
#include "VistaGruppiSet.h"
#include "Volume.h"
#include "WaitFleuryTransferitoDlg.h"
#include "PdfManager.h"
#include "ExtOrdiniCampiAggiuntiviSet.h"
#include "RecordAddSP.h"
#include "MainFrm.h"
#include "WriteLogLineSPSet.h"
#include "CommonCLR.h"

#include "MonitorScreens.h" //Gabriel BUG 6225 - Lista DO
#include "Monitor.h" //Gabriel BUG 6225 - Lista DO
#include "MonitorDC.h" //Gabriel BUG 6225 - Lista DO
#include "ImageDlg.h" //Gabriel BUG 6225 - Lista DO
#include "ImageSimple2Dlg.h" //Gabriel BUG 6225 - Lista DO

using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT MSG_SELECT_BMP;
UINT MSG_ELABOR_BMP;
UINT MSG_XPLAY_CLOSE;

UINT MSG_XCAP_MSG_NUOVOMONITORAGGIO = 0;
UINT MSG_XCAP_MSG_NUOVAPROVETTA = 0;

int	g_nBlackLev;
int	g_nWhiteLev;
int g_nLastUse;
int	g_nContrastMinLev[4];
int	g_nContrastMaxLev[4];
int g_nBrightnessLev;

CString g_sReportFaceName;
int		g_nReportSize;
BOOL	g_bReportUnderline;
BOOL	g_bReportBold;
BOOL	g_bReportItalic;

FORM_CARACT g_FormCaract[form_list_total];

void SetGlobalVariables()
{
	g_nBlackLev = 0;
	g_nWhiteLev = 255;
	g_nBrightnessLev = 0;

	/////////////////
	// --- --- --- //
	/////////////////

	for (int x = 0; x < form_list_total; x++)
	{
		g_FormCaract[x].lID = 0;
		g_FormCaract[x].sDescrizione = "";
		g_FormCaract[x].lMinA = 0;
		g_FormCaract[x].lMaxA = 0;
		g_FormCaract[x].lMinL = 0;
		g_FormCaract[x].lMaxL = 0;
		g_FormCaract[x].bEndox = FALSE;
		g_FormCaract[x].bImageNT = FALSE;
	}

	g_FormCaract[sub_abitudini].lID = SUB_ABITUDINI;
	g_FormCaract[sub_abitudini].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_79);
	g_FormCaract[sub_abitudini].lMinA = 10;
	g_FormCaract[sub_abitudini].lMaxA = 26;
	g_FormCaract[sub_abitudini].lMinL = 2;
	g_FormCaract[sub_abitudini].lMaxL = 8;
	g_FormCaract[sub_abitudini].bEndox = TRUE;
	g_FormCaract[sub_abitudini].bImageNT = TRUE;

	g_FormCaract[sub_chirurgici].lID = SUB_CHIRURGICI;
	g_FormCaract[sub_chirurgici].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_80);
	g_FormCaract[sub_chirurgici].lMinA = 6;
	g_FormCaract[sub_chirurgici].lMaxA = 26;
	g_FormCaract[sub_chirurgici].lMinL = 2;
	g_FormCaract[sub_chirurgici].lMaxL = 8;
	g_FormCaract[sub_chirurgici].bEndox = TRUE;
	g_FormCaract[sub_chirurgici].bImageNT = TRUE;

	g_FormCaract[sub_endoscopici].lID = SUB_ENDOSCOPICI;
	g_FormCaract[sub_endoscopici].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_81);
	g_FormCaract[sub_endoscopici].lMinA = 6;
	g_FormCaract[sub_endoscopici].lMaxA = 26;
	g_FormCaract[sub_endoscopici].lMinL = 2;
	g_FormCaract[sub_endoscopici].lMaxL = 8;
	g_FormCaract[sub_endoscopici].bEndox = TRUE;
	g_FormCaract[sub_endoscopici].bImageNT = FALSE;

	g_FormCaract[sub_familiarita].lID = SUB_FAMILIARITA;
	g_FormCaract[sub_familiarita].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_82);
	g_FormCaract[sub_familiarita].lMinA = 6;
	g_FormCaract[sub_familiarita].lMaxA = 26;
	g_FormCaract[sub_familiarita].lMinL = 2;
	g_FormCaract[sub_familiarita].lMaxL = 8;
	g_FormCaract[sub_familiarita].bEndox = TRUE;
	g_FormCaract[sub_familiarita].bImageNT = TRUE;

	g_FormCaract[sub_indagini].lID = SUB_INDAGINI;
	g_FormCaract[sub_indagini].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_83);
	g_FormCaract[sub_indagini].lMinA = 6;
	g_FormCaract[sub_indagini].lMaxA = 26;
	g_FormCaract[sub_indagini].lMinL = 2;
	g_FormCaract[sub_indagini].lMaxL = 8;
	g_FormCaract[sub_indagini].bEndox = TRUE;
	g_FormCaract[sub_indagini].bImageNT = TRUE;

	g_FormCaract[sub_malattie].lID = SUB_MALATTIE;
	g_FormCaract[sub_malattie].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_84);
	g_FormCaract[sub_malattie].lMinA = 6;
	g_FormCaract[sub_malattie].lMaxA = 26;
	g_FormCaract[sub_malattie].lMinL = 2;
	g_FormCaract[sub_malattie].lMaxL = 8;
	g_FormCaract[sub_malattie].bEndox = TRUE;
	g_FormCaract[sub_malattie].bImageNT = TRUE;

	g_FormCaract[edt_progressivo].lID = EDT_PROGRESSIVO;
	g_FormCaract[edt_progressivo].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_11);
	g_FormCaract[edt_progressivo].lMinA = 2;
	g_FormCaract[edt_progressivo].lMaxA = 2;
	g_FormCaract[edt_progressivo].lMinL = 1;
	g_FormCaract[edt_progressivo].lMaxL = 4;
	g_FormCaract[edt_progressivo].bEndox = TRUE;
	g_FormCaract[edt_progressivo].bImageNT = FALSE;

	g_FormCaract[edt_dataesame].lID = EDT_DATAESAME;
	g_FormCaract[edt_dataesame].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_13);
	g_FormCaract[edt_dataesame].lMinA = 2;
	g_FormCaract[edt_dataesame].lMaxA = 2;
	g_FormCaract[edt_dataesame].lMinL = 1;
	g_FormCaract[edt_dataesame].lMaxL = 4;
	g_FormCaract[edt_dataesame].bEndox = TRUE;
	g_FormCaract[edt_dataesame].bImageNT = TRUE;

	g_FormCaract[cmb_tipoesame].lID = CMB_TIPOESAME;
	g_FormCaract[cmb_tipoesame].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_12);
	g_FormCaract[cmb_tipoesame].lMinA = 2;
	g_FormCaract[cmb_tipoesame].lMaxA = 2;
	g_FormCaract[cmb_tipoesame].lMinL = 1;
	g_FormCaract[cmb_tipoesame].lMaxL = 4;
	g_FormCaract[cmb_tipoesame].bEndox = TRUE;
	g_FormCaract[cmb_tipoesame].bImageNT = FALSE;

	g_FormCaract[edt_progressivoanno].lID = EDT_PROGRESSIVOANNO;
	g_FormCaract[edt_progressivoanno].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_70);
	g_FormCaract[edt_progressivoanno].lMinA = 2;
	g_FormCaract[edt_progressivoanno].lMaxA = 2;
	g_FormCaract[edt_progressivoanno].lMinL = 1;
	g_FormCaract[edt_progressivoanno].lMaxL = 4;
	g_FormCaract[edt_progressivoanno].bEndox = TRUE;
	g_FormCaract[edt_progressivoanno].bImageNT = TRUE;

	g_FormCaract[edt_codiceprenotazione].lID = EDT_CODICEPRENOTAZIONE;
	g_FormCaract[edt_codiceprenotazione].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_500);
	g_FormCaract[edt_codiceprenotazione].lMinA = 2;
	g_FormCaract[edt_codiceprenotazione].lMaxA = 2;
	g_FormCaract[edt_codiceprenotazione].lMinL = 1;
	g_FormCaract[edt_codiceprenotazione].lMaxL = 4;
	g_FormCaract[edt_codiceprenotazione].bEndox = TRUE;
	g_FormCaract[edt_codiceprenotazione].bImageNT = TRUE;

	g_FormCaract[cmb_medico1].lID = CMB_MEDICO1;
	g_FormCaract[cmb_medico1].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_14);
	g_FormCaract[cmb_medico1].lMinA = 2;
	g_FormCaract[cmb_medico1].lMaxA = 2;
	g_FormCaract[cmb_medico1].lMinL = 1;
	g_FormCaract[cmb_medico1].lMaxL = 4;
	g_FormCaract[cmb_medico1].bEndox = TRUE;
	g_FormCaract[cmb_medico1].bImageNT = TRUE;

	g_FormCaract[cmb_medico2].lID = CMB_MEDICO2;
	g_FormCaract[cmb_medico2].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_15);
	g_FormCaract[cmb_medico2].lMinA = 2;
	g_FormCaract[cmb_medico2].lMaxA = 2;
	g_FormCaract[cmb_medico2].lMinL = 1;
	g_FormCaract[cmb_medico2].lMaxL = 4;
	g_FormCaract[cmb_medico2].bEndox = TRUE;
	g_FormCaract[cmb_medico2].bImageNT = TRUE;

	g_FormCaract[edt_medico_ricerca].lID = EDT_MEDICO_RICERCA;
	g_FormCaract[edt_medico_ricerca].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_517);
	g_FormCaract[edt_medico_ricerca].lMinA = 2;
	g_FormCaract[edt_medico_ricerca].lMaxA = 2;
	g_FormCaract[edt_medico_ricerca].lMinL = 1;
	g_FormCaract[edt_medico_ricerca].lMaxL = 4;
	g_FormCaract[edt_medico_ricerca].bEndox = TRUE;
	g_FormCaract[edt_medico_ricerca].bImageNT = TRUE;

	g_FormCaract[cmb_infermiere1].lID = CMB_INFERMIERE1;
	g_FormCaract[cmb_infermiere1].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_46);
	g_FormCaract[cmb_infermiere1].lMinA = 2;
	g_FormCaract[cmb_infermiere1].lMaxA = 2;
	g_FormCaract[cmb_infermiere1].lMinL = 1;
	g_FormCaract[cmb_infermiere1].lMaxL = 4;
	g_FormCaract[cmb_infermiere1].bEndox = TRUE;
	g_FormCaract[cmb_infermiere1].bImageNT = TRUE;

	g_FormCaract[cmb_infermiere2].lID = CMB_INFERMIERE2;
	g_FormCaract[cmb_infermiere2].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_47);
	g_FormCaract[cmb_infermiere2].lMinA = 2;
	g_FormCaract[cmb_infermiere2].lMaxA = 2;
	g_FormCaract[cmb_infermiere2].lMinL = 1;
	g_FormCaract[cmb_infermiere2].lMaxL = 4;
	g_FormCaract[cmb_infermiere2].bEndox = TRUE;
	g_FormCaract[cmb_infermiere2].bImageNT = TRUE;

	g_FormCaract[sub_inviante].lID = SUB_INVIANTE;
	g_FormCaract[sub_inviante].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_85);
	g_FormCaract[sub_inviante].lMinA = 2;
	g_FormCaract[sub_inviante].lMaxA = 2;
	g_FormCaract[sub_inviante].lMinL = 1;
	g_FormCaract[sub_inviante].lMaxL = 4;
	g_FormCaract[sub_inviante].bEndox = TRUE;
	g_FormCaract[sub_inviante].bImageNT = FALSE;

	g_FormCaract[edt_camera].lID = EDT_CAMERA;
	g_FormCaract[edt_camera].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_18);
	g_FormCaract[edt_camera].lMinA = 2;
	g_FormCaract[edt_camera].lMaxA = 2;
	g_FormCaract[edt_camera].lMinL = 1;
	g_FormCaract[edt_camera].lMaxL = 4;
	g_FormCaract[edt_camera].bEndox = TRUE;
	g_FormCaract[edt_camera].bImageNT = FALSE;

	g_FormCaract[edt_indicazioni].lID = EDT_INDICAZIONI;
	g_FormCaract[edt_indicazioni].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_32);
	g_FormCaract[edt_indicazioni].lMinA = 2;
	g_FormCaract[edt_indicazioni].lMaxA = 26;
	g_FormCaract[edt_indicazioni].lMinL = 1;
	g_FormCaract[edt_indicazioni].lMaxL = 8;
	g_FormCaract[edt_indicazioni].bEndox = TRUE;
	g_FormCaract[edt_indicazioni].bImageNT = TRUE;

	g_FormCaract[edt_farmacotrial].lID = EDT_FARMACOTRIAL;
	g_FormCaract[edt_farmacotrial].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_33);
	g_FormCaract[edt_farmacotrial].lMinA = 2;
	g_FormCaract[edt_farmacotrial].lMaxA = 2;
	g_FormCaract[edt_farmacotrial].lMinL = 1;
	g_FormCaract[edt_farmacotrial].lMaxL = 4;
	g_FormCaract[edt_farmacotrial].bEndox = TRUE;
	g_FormCaract[edt_farmacotrial].bImageNT = FALSE;

	g_FormCaract[edt_premedicazioni].lID = EDT_PREMEDICAZIONI;
	g_FormCaract[edt_premedicazioni].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_37);
	g_FormCaract[edt_premedicazioni].lMinA = 2;
	g_FormCaract[edt_premedicazioni].lMaxA = 2;
	g_FormCaract[edt_premedicazioni].lMinL = 1;
	g_FormCaract[edt_premedicazioni].lMaxL = 8;
	g_FormCaract[edt_premedicazioni].bEndox = TRUE;
	g_FormCaract[edt_premedicazioni].bImageNT = FALSE;

	g_FormCaract[sub_terapiainatto].lID = SUB_TERAPIAINATTO;
	g_FormCaract[sub_terapiainatto].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_86);
	g_FormCaract[sub_terapiainatto].lMinA = 5;
	g_FormCaract[sub_terapiainatto].lMaxA = 26;
	g_FormCaract[sub_terapiainatto].lMinL = 2;
	g_FormCaract[sub_terapiainatto].lMaxL = 8;
	g_FormCaract[sub_terapiainatto].bEndox = TRUE;
	g_FormCaract[sub_terapiainatto].bImageNT = FALSE;

	g_FormCaract[sub_terapiainatto_testo].lID = SUB_TERAPIAINATTO_TESTO;
	g_FormCaract[sub_terapiainatto_testo].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_316);
	g_FormCaract[sub_terapiainatto_testo].lMinA = 5;
	g_FormCaract[sub_terapiainatto_testo].lMaxA = 26;
	g_FormCaract[sub_terapiainatto_testo].lMinL = 2;
	g_FormCaract[sub_terapiainatto_testo].lMaxL = 8;
	g_FormCaract[sub_terapiainatto_testo].bEndox = TRUE;
	g_FormCaract[sub_terapiainatto_testo].bImageNT = FALSE;

	g_FormCaract[sub_osservazioni].lID = SUB_OSSERVAZIONI;
	g_FormCaract[sub_osservazioni].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_87);
	g_FormCaract[sub_osservazioni].lMinA = 7;
	g_FormCaract[sub_osservazioni].lMaxA = 26;
	g_FormCaract[sub_osservazioni].lMinL = 2;
	g_FormCaract[sub_osservazioni].lMaxL = 8;
	g_FormCaract[sub_osservazioni].bEndox = TRUE;
	g_FormCaract[sub_osservazioni].bImageNT = FALSE;

	g_FormCaract[edt_diagnostiche].lID = EDT_DIAGNOSTICHE;
	g_FormCaract[edt_diagnostiche].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_25);
	g_FormCaract[edt_diagnostiche].lMinA = 3;
	g_FormCaract[edt_diagnostiche].lMaxA = 26;
	g_FormCaract[edt_diagnostiche].lMinL = 1;
	g_FormCaract[edt_diagnostiche].lMaxL = 8;
	g_FormCaract[edt_diagnostiche].bEndox = TRUE;
	g_FormCaract[edt_diagnostiche].bImageNT = FALSE;

	g_FormCaract[edt_terapeutiche].lID = EDT_TERAPEUTICHE;
	g_FormCaract[edt_terapeutiche].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_26);
	g_FormCaract[edt_terapeutiche].lMinA = 3;
	g_FormCaract[edt_terapeutiche].lMaxA = 26;
	g_FormCaract[edt_terapeutiche].lMinL = 1;
	g_FormCaract[edt_terapeutiche].lMaxL = 8;
	g_FormCaract[edt_terapeutiche].bEndox = TRUE;
	g_FormCaract[edt_terapeutiche].bImageNT = FALSE;

	g_FormCaract[sub_diagnosi].lID = SUB_DIAGNOSI;
	g_FormCaract[sub_diagnosi].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_88);
	g_FormCaract[sub_diagnosi].lMinA = 7;
	g_FormCaract[sub_diagnosi].lMaxA = 26;
	g_FormCaract[sub_diagnosi].lMinL = 2;
	g_FormCaract[sub_diagnosi].lMaxL = 8;
	g_FormCaract[sub_diagnosi].bEndox = TRUE;
	g_FormCaract[sub_diagnosi].bImageNT = FALSE;

	g_FormCaract[edt_condottofino].lID = EDT_CONDOTTOFINO;
	g_FormCaract[edt_condottofino].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_30);
	g_FormCaract[edt_condottofino].lMinA = 2;
	g_FormCaract[edt_condottofino].lMaxA = 2;
	g_FormCaract[edt_condottofino].lMinL = 1;
	g_FormCaract[edt_condottofino].lMaxL = 8;
	g_FormCaract[edt_condottofino].bEndox = TRUE;
	g_FormCaract[edt_condottofino].bImageNT = FALSE;

	g_FormCaract[edt_valutazione].lID = EDT_VALUTAZIONE;
	g_FormCaract[edt_valutazione].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_42);
	g_FormCaract[edt_valutazione].lMinA = 2;
	g_FormCaract[edt_valutazione].lMaxA = 2;
	g_FormCaract[edt_valutazione].lMinL = 1;
	g_FormCaract[edt_valutazione].lMaxL = 4;
	g_FormCaract[edt_valutazione].bEndox = TRUE;
	g_FormCaract[edt_valutazione].bImageNT = FALSE;

	g_FormCaract[edt_complicanze].lID = EDT_COMPLICANZE;
	g_FormCaract[edt_complicanze].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_43);
	g_FormCaract[edt_complicanze].lMinA = 2;
	g_FormCaract[edt_complicanze].lMaxA = 26;
	g_FormCaract[edt_complicanze].lMinL = 1;
	g_FormCaract[edt_complicanze].lMaxL = 8;
	g_FormCaract[edt_complicanze].bEndox = TRUE;
	g_FormCaract[edt_complicanze].bImageNT = FALSE;

	g_FormCaract[edt_complicanzeprovvedimenti].lID = EDT_COMPLICANZEPROVVEDIMENTI;
	g_FormCaract[edt_complicanzeprovvedimenti].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_74);
	g_FormCaract[edt_complicanzeprovvedimenti].lMinA = 2;
	g_FormCaract[edt_complicanzeprovvedimenti].lMaxA = 26;
	g_FormCaract[edt_complicanzeprovvedimenti].lMinL = 1;
	g_FormCaract[edt_complicanzeprovvedimenti].lMaxL = 8;
	g_FormCaract[edt_complicanzeprovvedimenti].bEndox = TRUE;
	g_FormCaract[edt_complicanzeprovvedimenti].bImageNT = FALSE;

	g_FormCaract[edt_complicanzeterapia].lID = EDT_COMPLICANZETERAPIA;
	g_FormCaract[edt_complicanzeterapia].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_73);
	g_FormCaract[edt_complicanzeterapia].lMinA = 2;
	g_FormCaract[edt_complicanzeterapia].lMaxA = 26;
	g_FormCaract[edt_complicanzeterapia].lMinL = 1;
	g_FormCaract[edt_complicanzeterapia].lMaxL = 8;
	g_FormCaract[edt_complicanzeterapia].bEndox = TRUE;
	g_FormCaract[edt_complicanzeterapia].bImageNT = FALSE;

	g_FormCaract[edt_complicanzeesito].lID = EDT_COMPLICANZEESITO;
	g_FormCaract[edt_complicanzeesito].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_75);
	g_FormCaract[edt_complicanzeesito].lMinA = 2;
	g_FormCaract[edt_complicanzeesito].lMaxA = 26;
	g_FormCaract[edt_complicanzeesito].lMinL = 1;
	g_FormCaract[edt_complicanzeesito].lMaxL = 8;
	g_FormCaract[edt_complicanzeesito].bEndox = TRUE;
	g_FormCaract[edt_complicanzeesito].bImageNT = FALSE;

	g_FormCaract[edt_tipovisita].lID = EDT_TIPOVISITA;
	g_FormCaract[edt_tipovisita].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_35);
	g_FormCaract[edt_tipovisita].lMinA = 2;
	g_FormCaract[edt_tipovisita].lMaxA = 2;
	g_FormCaract[edt_tipovisita].lMinL = 1;
	g_FormCaract[edt_tipovisita].lMaxL = 4;
	g_FormCaract[edt_tipovisita].bEndox = TRUE;
	g_FormCaract[edt_tipovisita].bImageNT = FALSE;

	g_FormCaract[edt_quadro].lID = EDT_QUADRO;
	g_FormCaract[edt_quadro].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_45);
	g_FormCaract[edt_quadro].lMinA = 2;
	g_FormCaract[edt_quadro].lMaxA = 2;
	g_FormCaract[edt_quadro].lMinL = 1;
	g_FormCaract[edt_quadro].lMaxL = 4;
	g_FormCaract[edt_quadro].bEndox = TRUE;
	g_FormCaract[edt_quadro].bImageNT = FALSE;

	g_FormCaract[edt_durata].lID = EDT_DURATA;
	g_FormCaract[edt_durata].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_23);
	g_FormCaract[edt_durata].lMinA = 2;
	g_FormCaract[edt_durata].lMaxA = 2;
	g_FormCaract[edt_durata].lMinL = 1;
	g_FormCaract[edt_durata].lMaxL = 4;
	g_FormCaract[edt_durata].bEndox = TRUE;
	g_FormCaract[edt_durata].bImageNT = FALSE;

	g_FormCaract[edt_prossimo].lID = EDT_PROSSIMO;
	g_FormCaract[edt_prossimo].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_29);
	g_FormCaract[edt_prossimo].lMinA = 2;
	g_FormCaract[edt_prossimo].lMaxA = 2;
	g_FormCaract[edt_prossimo].lMinL = 1;
	g_FormCaract[edt_prossimo].lMaxL = 4;
	g_FormCaract[edt_prossimo].bEndox = TRUE;
	g_FormCaract[edt_prossimo].bImageNT = FALSE;

	g_FormCaract[edt_studio].lID = EDT_STUDIO;
	g_FormCaract[edt_studio].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_34);
	g_FormCaract[edt_studio].lMinA = 2;
	g_FormCaract[edt_studio].lMaxA = 2;
	g_FormCaract[edt_studio].lMinL = 1;
	g_FormCaract[edt_studio].lMaxL = 8;
	g_FormCaract[edt_studio].bEndox = TRUE;
	g_FormCaract[edt_studio].bImageNT = FALSE;

	g_FormCaract[edt_guarigione].lID = EDT_GUARIGIONE;
	g_FormCaract[edt_guarigione].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_44);
	g_FormCaract[edt_guarigione].lMinA = 2;
	g_FormCaract[edt_guarigione].lMaxA = 2;
	g_FormCaract[edt_guarigione].lMinL = 1;
	g_FormCaract[edt_guarigione].lMaxL = 8;
	g_FormCaract[edt_guarigione].bEndox = TRUE;
	g_FormCaract[edt_guarigione].bImageNT = FALSE;

	g_FormCaract[edt_difficolta].lID = EDT_DIFFICOLTA;
	g_FormCaract[edt_difficolta].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_24);
	g_FormCaract[edt_difficolta].lMinA = 2;
	g_FormCaract[edt_difficolta].lMaxA = 2;
	g_FormCaract[edt_difficolta].lMinL = 1;
	g_FormCaract[edt_difficolta].lMaxL = 4;
	g_FormCaract[edt_difficolta].bEndox = TRUE;
	g_FormCaract[edt_difficolta].bImageNT = FALSE;

	g_FormCaract[sub_regione].lID = SUB_REGIONE;
	g_FormCaract[sub_regione].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_89);
	g_FormCaract[sub_regione].lMinA = 5;
	g_FormCaract[sub_regione].lMaxA = 26;
	g_FormCaract[sub_regione].lMinL = 2;
	g_FormCaract[sub_regione].lMaxL = 16;
	g_FormCaract[sub_regione].bEndox = TRUE;
	g_FormCaract[sub_regione].bImageNT = FALSE;

	g_FormCaract[edt_terapiaconsigliata].lID = EDT_TERAPIACONSIGLIATA;
	g_FormCaract[edt_terapiaconsigliata].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_20);
	g_FormCaract[edt_terapiaconsigliata].lMinA = 2;
	g_FormCaract[edt_terapiaconsigliata].lMaxA = 26;
	g_FormCaract[edt_terapiaconsigliata].lMinL = 1;
	g_FormCaract[edt_terapiaconsigliata].lMaxL = 8;
	g_FormCaract[edt_terapiaconsigliata].bEndox = TRUE;
	g_FormCaract[edt_terapiaconsigliata].bImageNT = FALSE;

	g_FormCaract[edt_strumenti].lID = EDT_STRUMENTI;
	g_FormCaract[edt_strumenti].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_38);
	g_FormCaract[edt_strumenti].lMinA = 2;
	g_FormCaract[edt_strumenti].lMaxA = 26;
	g_FormCaract[edt_strumenti].lMinL = 1;
	g_FormCaract[edt_strumenti].lMaxL = 8;
	g_FormCaract[edt_strumenti].bEndox = TRUE;
	g_FormCaract[edt_strumenti].bImageNT = FALSE;

	g_FormCaract[edt_accessori].lID = EDT_ACCESSORI;
	g_FormCaract[edt_accessori].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_39);
	g_FormCaract[edt_accessori].lMinA = 2;
	g_FormCaract[edt_accessori].lMaxA = 26;
	g_FormCaract[edt_accessori].lMinL = 1;
	g_FormCaract[edt_accessori].lMaxL = 8;
	g_FormCaract[edt_accessori].bEndox = TRUE;
	g_FormCaract[edt_accessori].bImageNT = FALSE;

	g_FormCaract[edt_note].lID = EDT_NOTE;
	g_FormCaract[edt_note].sDescrizione = theApp.GetMessageString(IDS_NOTE);
	g_FormCaract[edt_note].lMinA = 2;
	g_FormCaract[edt_note].lMaxA = 26;
	g_FormCaract[edt_note].lMinL = 1;
	g_FormCaract[edt_note].lMaxL = 16;
	g_FormCaract[edt_note].bEndox = TRUE;
	g_FormCaract[edt_note].bImageNT = FALSE;

	g_FormCaract[sub_istopatologia].lID = SUB_ISTOPATOLOGIA;
	g_FormCaract[sub_istopatologia].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_90);
	g_FormCaract[sub_istopatologia].lMinA = 6;
	g_FormCaract[sub_istopatologia].lMaxA = 25;
	g_FormCaract[sub_istopatologia].lMinL = 2;
	g_FormCaract[sub_istopatologia].lMaxL = 16;
	g_FormCaract[sub_istopatologia].bEndox = TRUE;
	g_FormCaract[sub_istopatologia].bImageNT = FALSE;

	g_FormCaract[sub_referto].lID = SUB_REFERTO;
	g_FormCaract[sub_referto].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_91);
	g_FormCaract[sub_referto].lMinA = 10;
	g_FormCaract[sub_referto].lMaxA = 26;
	g_FormCaract[sub_referto].lMinL = 2;
	g_FormCaract[sub_referto].lMaxL = 16;
	g_FormCaract[sub_referto].bEndox = TRUE;
	g_FormCaract[sub_referto].bImageNT = TRUE;

	g_FormCaract[edt_riferimento].lID = EDT_RIFERIMENTO;
	g_FormCaract[edt_riferimento].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_76);
	g_FormCaract[edt_riferimento].lMinA = 2;
	g_FormCaract[edt_riferimento].lMaxA = 26;
	g_FormCaract[edt_riferimento].lMinL = 1;
	g_FormCaract[edt_riferimento].lMaxL = 8;
	g_FormCaract[edt_riferimento].bEndox = TRUE;
	g_FormCaract[edt_riferimento].bImageNT = FALSE;

	g_FormCaract[edt_libero000].lID = EDT_LIBERO000;
	g_FormCaract[edt_libero000].sDescrizione = theApp.m_sLabelText[0];
	g_FormCaract[edt_libero000].lMinA = 2;
	g_FormCaract[edt_libero000].lMaxA = 26;
	g_FormCaract[edt_libero000].lMinL = 1;
	g_FormCaract[edt_libero000].lMaxL = 8;
	g_FormCaract[edt_libero000].bEndox = TRUE;
	g_FormCaract[edt_libero000].bImageNT = TRUE;

	g_FormCaract[edt_libero001].lID = EDT_LIBERO001;
	g_FormCaract[edt_libero001].sDescrizione = theApp.m_sLabelText[1];
	g_FormCaract[edt_libero001].lMinA = 2;
	g_FormCaract[edt_libero001].lMaxA = 26;
	g_FormCaract[edt_libero001].lMinL = 1;
	g_FormCaract[edt_libero001].lMaxL = 8;
	g_FormCaract[edt_libero001].bEndox = TRUE;
	g_FormCaract[edt_libero001].bImageNT = TRUE;

	g_FormCaract[edt_libero002].lID = EDT_LIBERO002;
	g_FormCaract[edt_libero002].sDescrizione = theApp.m_sLabelText[2];
	g_FormCaract[edt_libero002].lMinA = 2;
	g_FormCaract[edt_libero002].lMaxA = 26;
	g_FormCaract[edt_libero002].lMinL = 1;
	g_FormCaract[edt_libero002].lMaxL = 8;
	g_FormCaract[edt_libero002].bEndox = TRUE;
	g_FormCaract[edt_libero002].bImageNT = TRUE;

	g_FormCaract[edt_libero003].lID = EDT_LIBERO003;
	g_FormCaract[edt_libero003].sDescrizione = theApp.m_sLabelText[3];
	g_FormCaract[edt_libero003].lMinA = 2;
	g_FormCaract[edt_libero003].lMaxA = 26;
	g_FormCaract[edt_libero003].lMinL = 1;
	g_FormCaract[edt_libero003].lMaxL = 8;
	g_FormCaract[edt_libero003].bEndox = TRUE;
	g_FormCaract[edt_libero003].bImageNT = TRUE;

	g_FormCaract[edt_libero004].lID = EDT_LIBERO004;
	g_FormCaract[edt_libero004].sDescrizione = theApp.m_sLabelText[4];
	g_FormCaract[edt_libero004].lMinA = 2;
	g_FormCaract[edt_libero004].lMaxA = 26;
	g_FormCaract[edt_libero004].lMinL = 1;
	g_FormCaract[edt_libero004].lMaxL = 8;
	g_FormCaract[edt_libero004].bEndox = TRUE;
	g_FormCaract[edt_libero004].bImageNT = TRUE;

	g_FormCaract[edt_libero005].lID = EDT_LIBERO005;
	g_FormCaract[edt_libero005].sDescrizione = theApp.m_sLabelText[5];
	g_FormCaract[edt_libero005].lMinA = 2;
	g_FormCaract[edt_libero005].lMaxA = 26;
	g_FormCaract[edt_libero005].lMinL = 1;
	g_FormCaract[edt_libero005].lMaxL = 8;
	g_FormCaract[edt_libero005].bEndox = TRUE;
	g_FormCaract[edt_libero005].bImageNT = TRUE;

	g_FormCaract[edt_libero006].lID = EDT_LIBERO006;
	g_FormCaract[edt_libero006].sDescrizione = theApp.m_sLabelText[6];
	g_FormCaract[edt_libero006].lMinA = 2;
	g_FormCaract[edt_libero006].lMaxA = 26;
	g_FormCaract[edt_libero006].lMinL = 1;
	g_FormCaract[edt_libero006].lMaxL = 8;
	g_FormCaract[edt_libero006].bEndox = TRUE;
	g_FormCaract[edt_libero006].bImageNT = TRUE;

	g_FormCaract[edt_libero007].lID = EDT_LIBERO007;
	g_FormCaract[edt_libero007].sDescrizione = theApp.m_sLabelText[7];
	g_FormCaract[edt_libero007].lMinA = 2;
	g_FormCaract[edt_libero007].lMaxA = 26;
	g_FormCaract[edt_libero007].lMinL = 1;
	g_FormCaract[edt_libero007].lMaxL = 8;
	g_FormCaract[edt_libero007].bEndox = TRUE;
	g_FormCaract[edt_libero007].bImageNT = TRUE;

	g_FormCaract[edt_libero008].lID = EDT_LIBERO008;
	g_FormCaract[edt_libero008].sDescrizione = theApp.m_sLabelText[8];
	g_FormCaract[edt_libero008].lMinA = 2;
	g_FormCaract[edt_libero008].lMaxA = 26;
	g_FormCaract[edt_libero008].lMinL = 1;
	g_FormCaract[edt_libero008].lMaxL = 8;
	g_FormCaract[edt_libero008].bEndox = TRUE;
	g_FormCaract[edt_libero008].bImageNT = TRUE;

	g_FormCaract[edt_libero009].lID = EDT_LIBERO009;
	g_FormCaract[edt_libero009].sDescrizione = theApp.m_sLabelText[9];
	g_FormCaract[edt_libero009].lMinA = 2;
	g_FormCaract[edt_libero009].lMaxA = 26;
	g_FormCaract[edt_libero009].lMinL = 1;
	g_FormCaract[edt_libero009].lMaxL = 8;
	g_FormCaract[edt_libero009].bEndox = TRUE;
	g_FormCaract[edt_libero009].bImageNT = TRUE;

	g_FormCaract[edt_libero010].lID = EDT_LIBERO010;
	g_FormCaract[edt_libero010].sDescrizione = theApp.m_sLabelText[10];
	g_FormCaract[edt_libero010].lMinA = 2;
	g_FormCaract[edt_libero010].lMaxA = 26;
	g_FormCaract[edt_libero010].lMinL = 1;
	g_FormCaract[edt_libero010].lMaxL = 8;
	g_FormCaract[edt_libero010].bEndox = TRUE;
	g_FormCaract[edt_libero010].bImageNT = TRUE;

	g_FormCaract[edt_libero011].lID = EDT_LIBERO011;
	g_FormCaract[edt_libero011].sDescrizione = theApp.m_sLabelText[11];
	g_FormCaract[edt_libero011].lMinA = 2;
	g_FormCaract[edt_libero011].lMaxA = 26;
	g_FormCaract[edt_libero011].lMinL = 1;
	g_FormCaract[edt_libero011].lMaxL = 8;
	g_FormCaract[edt_libero011].bEndox = TRUE;
	g_FormCaract[edt_libero011].bImageNT = TRUE;

	g_FormCaract[edt_libero012].lID = EDT_LIBERO012;
	g_FormCaract[edt_libero012].sDescrizione = theApp.m_sLabelText[12];
	g_FormCaract[edt_libero012].lMinA = 2;
	g_FormCaract[edt_libero012].lMaxA = 26;
	g_FormCaract[edt_libero012].lMinL = 1;
	g_FormCaract[edt_libero012].lMaxL = 8;
	g_FormCaract[edt_libero012].bEndox = TRUE;
	g_FormCaract[edt_libero012].bImageNT = TRUE;

	g_FormCaract[edt_libero013].lID = EDT_LIBERO013;
	g_FormCaract[edt_libero013].sDescrizione = theApp.m_sLabelText[13];
	g_FormCaract[edt_libero013].lMinA = 2;
	g_FormCaract[edt_libero013].lMaxA = 26;
	g_FormCaract[edt_libero013].lMinL = 1;
	g_FormCaract[edt_libero013].lMaxL = 8;
	g_FormCaract[edt_libero013].bEndox = TRUE;
	g_FormCaract[edt_libero013].bImageNT = TRUE;

	g_FormCaract[edt_libero014].lID = EDT_LIBERO014;
	g_FormCaract[edt_libero014].sDescrizione = theApp.m_sLabelText[14];
	g_FormCaract[edt_libero014].lMinA = 2;
	g_FormCaract[edt_libero014].lMaxA = 26;
	g_FormCaract[edt_libero014].lMinL = 1;
	g_FormCaract[edt_libero014].lMaxL = 8;
	g_FormCaract[edt_libero014].bEndox = TRUE;
	g_FormCaract[edt_libero014].bImageNT = TRUE;

	g_FormCaract[edt_libero015].lID = EDT_LIBERO015;
	g_FormCaract[edt_libero015].sDescrizione = theApp.m_sLabelText[15];
	g_FormCaract[edt_libero015].lMinA = 2;
	g_FormCaract[edt_libero015].lMaxA = 26;
	g_FormCaract[edt_libero015].lMinL = 1;
	g_FormCaract[edt_libero015].lMaxL = 8;
	g_FormCaract[edt_libero015].bEndox = TRUE;
	g_FormCaract[edt_libero015].bImageNT = TRUE;

	g_FormCaract[edt_libero016].lID = EDT_LIBERO016;
	g_FormCaract[edt_libero016].sDescrizione = theApp.m_sLabelText[16];
	g_FormCaract[edt_libero016].lMinA = 2;
	g_FormCaract[edt_libero016].lMaxA = 26;
	g_FormCaract[edt_libero016].lMinL = 1;
	g_FormCaract[edt_libero016].lMaxL = 8;
	g_FormCaract[edt_libero016].bEndox = TRUE;
	g_FormCaract[edt_libero016].bImageNT = TRUE;

	g_FormCaract[edt_libero017].lID = EDT_LIBERO017;
	g_FormCaract[edt_libero017].sDescrizione = theApp.m_sLabelText[17];
	g_FormCaract[edt_libero017].lMinA = 2;
	g_FormCaract[edt_libero017].lMaxA = 26;
	g_FormCaract[edt_libero017].lMinL = 1;
	g_FormCaract[edt_libero017].lMaxL = 8;
	g_FormCaract[edt_libero017].bEndox = TRUE;
	g_FormCaract[edt_libero017].bImageNT = TRUE;

	g_FormCaract[edt_libero018].lID = EDT_LIBERO018;
	g_FormCaract[edt_libero018].sDescrizione = theApp.m_sLabelText[18];
	g_FormCaract[edt_libero018].lMinA = 2;
	g_FormCaract[edt_libero018].lMaxA = 26;
	g_FormCaract[edt_libero018].lMinL = 1;
	g_FormCaract[edt_libero018].lMaxL = 8;
	g_FormCaract[edt_libero018].bEndox = TRUE;
	g_FormCaract[edt_libero018].bImageNT = TRUE;

	g_FormCaract[edt_libero019].lID = EDT_LIBERO019;
	g_FormCaract[edt_libero019].sDescrizione = theApp.m_sLabelText[19];
	g_FormCaract[edt_libero019].lMinA = 2;
	g_FormCaract[edt_libero019].lMaxA = 26;
	g_FormCaract[edt_libero019].lMinL = 1;
	g_FormCaract[edt_libero019].lMaxL = 8;
	g_FormCaract[edt_libero019].bEndox = TRUE;
	g_FormCaract[edt_libero019].bImageNT = TRUE;

	g_FormCaract[edt_libero020].lID = EDT_LIBERO020;
	g_FormCaract[edt_libero020].sDescrizione = theApp.m_sLabelText[20];
	g_FormCaract[edt_libero020].lMinA = 2;
	g_FormCaract[edt_libero020].lMaxA = 26;
	g_FormCaract[edt_libero020].lMinL = 1;
	g_FormCaract[edt_libero020].lMaxL = 8;
	g_FormCaract[edt_libero020].bEndox = TRUE;
	g_FormCaract[edt_libero020].bImageNT = FALSE;

	g_FormCaract[edt_libero021].lID = EDT_LIBERO021;
	g_FormCaract[edt_libero021].sDescrizione = theApp.m_sLabelText[21];
	g_FormCaract[edt_libero021].lMinA = 2;
	g_FormCaract[edt_libero021].lMaxA = 26;
	g_FormCaract[edt_libero021].lMinL = 1;
	g_FormCaract[edt_libero021].lMaxL = 8;
	g_FormCaract[edt_libero021].bEndox = TRUE;
	g_FormCaract[edt_libero021].bImageNT = FALSE;

	g_FormCaract[edt_libero022].lID = EDT_LIBERO022;
	g_FormCaract[edt_libero022].sDescrizione = theApp.m_sLabelText[22];
	g_FormCaract[edt_libero022].lMinA = 2;
	g_FormCaract[edt_libero022].lMaxA = 26;
	g_FormCaract[edt_libero022].lMinL = 1;
	g_FormCaract[edt_libero022].lMaxL = 8;
	g_FormCaract[edt_libero022].bEndox = TRUE;
	g_FormCaract[edt_libero022].bImageNT = FALSE;

	g_FormCaract[edt_libero023].lID = EDT_LIBERO023;
	g_FormCaract[edt_libero023].sDescrizione = theApp.m_sLabelText[23];
	g_FormCaract[edt_libero023].lMinA = 2;
	g_FormCaract[edt_libero023].lMaxA = 26;
	g_FormCaract[edt_libero023].lMinL = 1;
	g_FormCaract[edt_libero023].lMaxL = 8;
	g_FormCaract[edt_libero023].bEndox = TRUE;
	g_FormCaract[edt_libero023].bImageNT = FALSE;

	g_FormCaract[edt_libero024].lID = EDT_LIBERO024;
	g_FormCaract[edt_libero024].sDescrizione = theApp.m_sLabelText[24];
	g_FormCaract[edt_libero024].lMinA = 2;
	g_FormCaract[edt_libero024].lMaxA = 26;
	g_FormCaract[edt_libero024].lMinL = 1;
	g_FormCaract[edt_libero024].lMaxL = 8;
	g_FormCaract[edt_libero024].bEndox = TRUE;
	g_FormCaract[edt_libero024].bImageNT = FALSE;

	g_FormCaract[edt_libero025].lID = EDT_LIBERO025;
	g_FormCaract[edt_libero025].sDescrizione = theApp.m_sLabelText[25];
	g_FormCaract[edt_libero025].lMinA = 2;
	g_FormCaract[edt_libero025].lMaxA = 26;
	g_FormCaract[edt_libero025].lMinL = 1;
	g_FormCaract[edt_libero025].lMaxL = 8;
	g_FormCaract[edt_libero025].bEndox = TRUE;
	g_FormCaract[edt_libero025].bImageNT = FALSE;

	g_FormCaract[edt_libero026].lID = EDT_LIBERO026;
	g_FormCaract[edt_libero026].sDescrizione = theApp.m_sLabelText[26];
	g_FormCaract[edt_libero026].lMinA = 2;
	g_FormCaract[edt_libero026].lMaxA = 26;
	g_FormCaract[edt_libero026].lMinL = 1;
	g_FormCaract[edt_libero026].lMaxL = 8;
	g_FormCaract[edt_libero026].bEndox = TRUE;
	g_FormCaract[edt_libero026].bImageNT = FALSE;

	g_FormCaract[edt_libero027].lID = EDT_LIBERO027;
	g_FormCaract[edt_libero027].sDescrizione = theApp.m_sLabelText[27];
	g_FormCaract[edt_libero027].lMinA = 2;
	g_FormCaract[edt_libero027].lMaxA = 26;
	g_FormCaract[edt_libero027].lMinL = 1;
	g_FormCaract[edt_libero027].lMaxL = 8;
	g_FormCaract[edt_libero027].bEndox = TRUE;
	g_FormCaract[edt_libero027].bImageNT = FALSE;

	g_FormCaract[edt_libero028].lID = EDT_LIBERO028;
	g_FormCaract[edt_libero028].sDescrizione = theApp.m_sLabelText[28];
	g_FormCaract[edt_libero028].lMinA = 2;
	g_FormCaract[edt_libero028].lMaxA = 26;
	g_FormCaract[edt_libero028].lMinL = 1;
	g_FormCaract[edt_libero028].lMaxL = 8;
	g_FormCaract[edt_libero028].bEndox = TRUE;
	g_FormCaract[edt_libero028].bImageNT = FALSE;

	g_FormCaract[edt_libero029].lID = EDT_LIBERO029;
	g_FormCaract[edt_libero029].sDescrizione = theApp.m_sLabelText[29];
	g_FormCaract[edt_libero029].lMinA = 2;
	g_FormCaract[edt_libero029].lMaxA = 26;
	g_FormCaract[edt_libero029].lMinL = 1;
	g_FormCaract[edt_libero029].lMaxL = 8;
	g_FormCaract[edt_libero029].bEndox = TRUE;
	g_FormCaract[edt_libero029].bImageNT = FALSE;

	g_FormCaract[edt_libero030].lID = EDT_LIBERO030;
	g_FormCaract[edt_libero030].sDescrizione = theApp.m_sLabelText[30];
	g_FormCaract[edt_libero030].lMinA = 2;
	g_FormCaract[edt_libero030].lMaxA = 26;
	g_FormCaract[edt_libero030].lMinL = 1;
	g_FormCaract[edt_libero030].lMaxL = 8;
	g_FormCaract[edt_libero030].bEndox = TRUE;
	g_FormCaract[edt_libero030].bImageNT = FALSE;

	g_FormCaract[edt_libero031].lID = EDT_LIBERO031;
	g_FormCaract[edt_libero031].sDescrizione = theApp.m_sLabelText[31];
	g_FormCaract[edt_libero031].lMinA = 2;
	g_FormCaract[edt_libero031].lMaxA = 26;
	g_FormCaract[edt_libero031].lMinL = 1;
	g_FormCaract[edt_libero031].lMaxL = 8;
	g_FormCaract[edt_libero031].bEndox = TRUE;
	g_FormCaract[edt_libero031].bImageNT = FALSE;

	g_FormCaract[edt_libero032].lID = EDT_LIBERO032;
	g_FormCaract[edt_libero032].sDescrizione = theApp.m_sLabelText[32];
	g_FormCaract[edt_libero032].lMinA = 2;
	g_FormCaract[edt_libero032].lMaxA = 26;
	g_FormCaract[edt_libero032].lMinL = 1;
	g_FormCaract[edt_libero032].lMaxL = 8;
	g_FormCaract[edt_libero032].bEndox = TRUE;
	g_FormCaract[edt_libero032].bImageNT = FALSE;

	g_FormCaract[edt_libero033].lID = EDT_LIBERO033;
	g_FormCaract[edt_libero033].sDescrizione = theApp.m_sLabelText[33];
	g_FormCaract[edt_libero033].lMinA = 2;
	g_FormCaract[edt_libero033].lMaxA = 26;
	g_FormCaract[edt_libero033].lMinL = 1;
	g_FormCaract[edt_libero033].lMaxL = 8;
	g_FormCaract[edt_libero033].bEndox = TRUE;
	g_FormCaract[edt_libero033].bImageNT = FALSE;

	g_FormCaract[edt_libero034].lID = EDT_LIBERO034;
	g_FormCaract[edt_libero034].sDescrizione = theApp.m_sLabelText[34];
	g_FormCaract[edt_libero034].lMinA = 2;
	g_FormCaract[edt_libero034].lMaxA = 26;
	g_FormCaract[edt_libero034].lMinL = 1;
	g_FormCaract[edt_libero034].lMaxL = 8;
	g_FormCaract[edt_libero034].bEndox = TRUE;
	g_FormCaract[edt_libero034].bImageNT = FALSE;

	g_FormCaract[edt_libero035].lID = EDT_LIBERO035;
	g_FormCaract[edt_libero035].sDescrizione = theApp.m_sLabelText[35];
	g_FormCaract[edt_libero035].lMinA = 2;
	g_FormCaract[edt_libero035].lMaxA = 26;
	g_FormCaract[edt_libero035].lMinL = 1;
	g_FormCaract[edt_libero035].lMaxL = 8;
	g_FormCaract[edt_libero035].bEndox = TRUE;
	g_FormCaract[edt_libero035].bImageNT = FALSE;

	g_FormCaract[edt_libero036].lID = EDT_LIBERO036;
	g_FormCaract[edt_libero036].sDescrizione = theApp.m_sLabelText[36];
	g_FormCaract[edt_libero036].lMinA = 2;
	g_FormCaract[edt_libero036].lMaxA = 26;
	g_FormCaract[edt_libero036].lMinL = 1;
	g_FormCaract[edt_libero036].lMaxL = 8;
	g_FormCaract[edt_libero036].bEndox = TRUE;
	g_FormCaract[edt_libero036].bImageNT = FALSE;

	g_FormCaract[edt_libero037].lID = EDT_LIBERO037;
	g_FormCaract[edt_libero037].sDescrizione = theApp.m_sLabelText[37];
	g_FormCaract[edt_libero037].lMinA = 2;
	g_FormCaract[edt_libero037].lMaxA = 26;
	g_FormCaract[edt_libero037].lMinL = 1;
	g_FormCaract[edt_libero037].lMaxL = 8;
	g_FormCaract[edt_libero037].bEndox = TRUE;
	g_FormCaract[edt_libero037].bImageNT = FALSE;

	g_FormCaract[edt_libero038].lID = EDT_LIBERO038;
	g_FormCaract[edt_libero038].sDescrizione = theApp.m_sLabelText[38];
	g_FormCaract[edt_libero038].lMinA = 2;
	g_FormCaract[edt_libero038].lMaxA = 26;
	g_FormCaract[edt_libero038].lMinL = 1;
	g_FormCaract[edt_libero038].lMaxL = 8;
	g_FormCaract[edt_libero038].bEndox = TRUE;
	g_FormCaract[edt_libero038].bImageNT = FALSE;

	g_FormCaract[edt_libero039].lID = EDT_LIBERO039;
	g_FormCaract[edt_libero039].sDescrizione = theApp.m_sLabelText[39];
	g_FormCaract[edt_libero039].lMinA = 2;
	g_FormCaract[edt_libero039].lMaxA = 26;
	g_FormCaract[edt_libero039].lMinL = 1;
	g_FormCaract[edt_libero039].lMaxL = 8;
	g_FormCaract[edt_libero039].bEndox = TRUE;
	g_FormCaract[edt_libero039].bImageNT = FALSE;

	g_FormCaract[edt_libero040].lID = EDT_LIBERO040;
	g_FormCaract[edt_libero040].sDescrizione = theApp.m_sLabelText[40];
	g_FormCaract[edt_libero040].lMinA = 2;
	g_FormCaract[edt_libero040].lMaxA = 26;
	g_FormCaract[edt_libero040].lMinL = 1;
	g_FormCaract[edt_libero040].lMaxL = 8;
	g_FormCaract[edt_libero040].bEndox = TRUE;
	g_FormCaract[edt_libero040].bImageNT = FALSE;

	g_FormCaract[edt_libero041].lID = EDT_LIBERO041;
	g_FormCaract[edt_libero041].sDescrizione = theApp.m_sLabelText[41];
	g_FormCaract[edt_libero041].lMinA = 2;
	g_FormCaract[edt_libero041].lMaxA = 26;
	g_FormCaract[edt_libero041].lMinL = 1;
	g_FormCaract[edt_libero041].lMaxL = 8;
	g_FormCaract[edt_libero041].bEndox = TRUE;
	g_FormCaract[edt_libero041].bImageNT = FALSE;

	g_FormCaract[edt_libero042].lID = EDT_LIBERO042;
	g_FormCaract[edt_libero042].sDescrizione = theApp.m_sLabelText[42];
	g_FormCaract[edt_libero042].lMinA = 2;
	g_FormCaract[edt_libero042].lMaxA = 26;
	g_FormCaract[edt_libero042].lMinL = 1;
	g_FormCaract[edt_libero042].lMaxL = 8;
	g_FormCaract[edt_libero042].bEndox = TRUE;
	g_FormCaract[edt_libero042].bImageNT = FALSE;

	g_FormCaract[edt_libero043].lID = EDT_LIBERO043;
	g_FormCaract[edt_libero043].sDescrizione = theApp.m_sLabelText[43];
	g_FormCaract[edt_libero043].lMinA = 2;
	g_FormCaract[edt_libero043].lMaxA = 26;
	g_FormCaract[edt_libero043].lMinL = 1;
	g_FormCaract[edt_libero043].lMaxL = 8;
	g_FormCaract[edt_libero043].bEndox = TRUE;
	g_FormCaract[edt_libero043].bImageNT = FALSE;

	g_FormCaract[edt_libero044].lID = EDT_LIBERO044;
	g_FormCaract[edt_libero044].sDescrizione = theApp.m_sLabelText[44];
	g_FormCaract[edt_libero044].lMinA = 2;
	g_FormCaract[edt_libero044].lMaxA = 26;
	g_FormCaract[edt_libero044].lMinL = 1;
	g_FormCaract[edt_libero044].lMaxL = 8;
	g_FormCaract[edt_libero044].bEndox = TRUE;
	g_FormCaract[edt_libero044].bImageNT = FALSE;

	g_FormCaract[edt_libero045].lID = EDT_LIBERO045;
	g_FormCaract[edt_libero045].sDescrizione = theApp.m_sLabelText[45];
	g_FormCaract[edt_libero045].lMinA = 2;
	g_FormCaract[edt_libero045].lMaxA = 26;
	g_FormCaract[edt_libero045].lMinL = 1;
	g_FormCaract[edt_libero045].lMaxL = 8;
	g_FormCaract[edt_libero045].bEndox = TRUE;
	g_FormCaract[edt_libero045].bImageNT = FALSE;

	g_FormCaract[edt_libero046].lID = EDT_LIBERO046;
	g_FormCaract[edt_libero046].sDescrizione = theApp.m_sLabelText[46];
	g_FormCaract[edt_libero046].lMinA = 2;
	g_FormCaract[edt_libero046].lMaxA = 26;
	g_FormCaract[edt_libero046].lMinL = 1;
	g_FormCaract[edt_libero046].lMaxL = 8;
	g_FormCaract[edt_libero046].bEndox = TRUE;
	g_FormCaract[edt_libero046].bImageNT = FALSE;

	g_FormCaract[edt_libero047].lID = EDT_LIBERO047;
	g_FormCaract[edt_libero047].sDescrizione = theApp.m_sLabelText[47];
	g_FormCaract[edt_libero047].lMinA = 2;
	g_FormCaract[edt_libero047].lMaxA = 26;
	g_FormCaract[edt_libero047].lMinL = 1;
	g_FormCaract[edt_libero047].lMaxL = 8;
	g_FormCaract[edt_libero047].bEndox = TRUE;
	g_FormCaract[edt_libero047].bImageNT = FALSE;

	g_FormCaract[edt_libero048].lID = EDT_LIBERO048;
	g_FormCaract[edt_libero048].sDescrizione = theApp.m_sLabelText[48];
	g_FormCaract[edt_libero048].lMinA = 2;
	g_FormCaract[edt_libero048].lMaxA = 26;
	g_FormCaract[edt_libero048].lMinL = 1;
	g_FormCaract[edt_libero048].lMaxL = 8;
	g_FormCaract[edt_libero048].bEndox = TRUE;
	g_FormCaract[edt_libero048].bImageNT = FALSE;

	g_FormCaract[edt_libero049].lID = EDT_LIBERO049;
	g_FormCaract[edt_libero049].sDescrizione = theApp.m_sLabelText[49];
	g_FormCaract[edt_libero049].lMinA = 2;
	g_FormCaract[edt_libero049].lMaxA = 26;
	g_FormCaract[edt_libero049].lMinL = 1;
	g_FormCaract[edt_libero049].lMaxL = 8;
	g_FormCaract[edt_libero049].bEndox = TRUE;
	g_FormCaract[edt_libero049].bImageNT = FALSE;

	g_FormCaract[edt_libero050].lID = EDT_LIBERO050;
	g_FormCaract[edt_libero050].sDescrizione = theApp.m_sLabelText[50];
	g_FormCaract[edt_libero050].lMinA = 2;
	g_FormCaract[edt_libero050].lMaxA = 26;
	g_FormCaract[edt_libero050].lMinL = 1;
	g_FormCaract[edt_libero050].lMaxL = 8;
	g_FormCaract[edt_libero050].bEndox = TRUE;
	g_FormCaract[edt_libero050].bImageNT = FALSE;

	g_FormCaract[edt_libero051].lID = EDT_LIBERO051;
	g_FormCaract[edt_libero051].sDescrizione = theApp.m_sLabelText[51];
	g_FormCaract[edt_libero051].lMinA = 2;
	g_FormCaract[edt_libero051].lMaxA = 26;
	g_FormCaract[edt_libero051].lMinL = 1;
	g_FormCaract[edt_libero051].lMaxL = 8;
	g_FormCaract[edt_libero051].bEndox = TRUE;
	g_FormCaract[edt_libero051].bImageNT = FALSE;

	g_FormCaract[edt_libero052].lID = EDT_LIBERO052;
	g_FormCaract[edt_libero052].sDescrizione = theApp.m_sLabelText[52];
	g_FormCaract[edt_libero052].lMinA = 2;
	g_FormCaract[edt_libero052].lMaxA = 26;
	g_FormCaract[edt_libero052].lMinL = 1;
	g_FormCaract[edt_libero052].lMaxL = 8;
	g_FormCaract[edt_libero052].bEndox = TRUE;
	g_FormCaract[edt_libero052].bImageNT = FALSE;

	g_FormCaract[edt_libero053].lID = EDT_LIBERO053;
	g_FormCaract[edt_libero053].sDescrizione = theApp.m_sLabelText[53];
	g_FormCaract[edt_libero053].lMinA = 2;
	g_FormCaract[edt_libero053].lMaxA = 26;
	g_FormCaract[edt_libero053].lMinL = 1;
	g_FormCaract[edt_libero053].lMaxL = 8;
	g_FormCaract[edt_libero053].bEndox = TRUE;
	g_FormCaract[edt_libero053].bImageNT = FALSE;

	g_FormCaract[edt_libero054].lID = EDT_LIBERO054;
	g_FormCaract[edt_libero054].sDescrizione = theApp.m_sLabelText[54];
	g_FormCaract[edt_libero054].lMinA = 2;
	g_FormCaract[edt_libero054].lMaxA = 26;
	g_FormCaract[edt_libero054].lMinL = 1;
	g_FormCaract[edt_libero054].lMaxL = 8;
	g_FormCaract[edt_libero054].bEndox = TRUE;
	g_FormCaract[edt_libero054].bImageNT = FALSE;

	g_FormCaract[edt_libero055].lID = EDT_LIBERO055;
	g_FormCaract[edt_libero055].sDescrizione = theApp.m_sLabelText[55];
	g_FormCaract[edt_libero055].lMinA = 2;
	g_FormCaract[edt_libero055].lMaxA = 26;
	g_FormCaract[edt_libero055].lMinL = 1;
	g_FormCaract[edt_libero055].lMaxL = 8;
	g_FormCaract[edt_libero055].bEndox = TRUE;
	g_FormCaract[edt_libero055].bImageNT = FALSE;

	g_FormCaract[edt_libero056].lID = EDT_LIBERO056;
	g_FormCaract[edt_libero056].sDescrizione = theApp.m_sLabelText[56];
	g_FormCaract[edt_libero056].lMinA = 2;
	g_FormCaract[edt_libero056].lMaxA = 26;
	g_FormCaract[edt_libero056].lMinL = 1;
	g_FormCaract[edt_libero056].lMaxL = 8;
	g_FormCaract[edt_libero056].bEndox = TRUE;
	g_FormCaract[edt_libero056].bImageNT = FALSE;

	g_FormCaract[edt_libero057].lID = EDT_LIBERO057;
	g_FormCaract[edt_libero057].sDescrizione = theApp.m_sLabelText[57];
	g_FormCaract[edt_libero057].lMinA = 2;
	g_FormCaract[edt_libero057].lMaxA = 26;
	g_FormCaract[edt_libero057].lMinL = 1;
	g_FormCaract[edt_libero057].lMaxL = 8;
	g_FormCaract[edt_libero057].bEndox = TRUE;
	g_FormCaract[edt_libero057].bImageNT = FALSE;

	g_FormCaract[edt_libero058].lID = EDT_LIBERO058;
	g_FormCaract[edt_libero058].sDescrizione = theApp.m_sLabelText[58];
	g_FormCaract[edt_libero058].lMinA = 2;
	g_FormCaract[edt_libero058].lMaxA = 26;
	g_FormCaract[edt_libero058].lMinL = 1;
	g_FormCaract[edt_libero058].lMaxL = 8;
	g_FormCaract[edt_libero058].bEndox = TRUE;
	g_FormCaract[edt_libero058].bImageNT = FALSE;

	g_FormCaract[edt_libero059].lID = EDT_LIBERO059;
	g_FormCaract[edt_libero059].sDescrizione = theApp.m_sLabelText[59];
	g_FormCaract[edt_libero059].lMinA = 2;
	g_FormCaract[edt_libero059].lMaxA = 26;
	g_FormCaract[edt_libero059].lMinL = 1;
	g_FormCaract[edt_libero059].lMaxL = 8;
	g_FormCaract[edt_libero059].bEndox = TRUE;
	g_FormCaract[edt_libero059].bImageNT = FALSE;

	g_FormCaract[edt_libero060].lID = EDT_LIBERO060;
	g_FormCaract[edt_libero060].sDescrizione = theApp.m_sLabelText[60];
	g_FormCaract[edt_libero060].lMinA = 2;
	g_FormCaract[edt_libero060].lMaxA = 26;
	g_FormCaract[edt_libero060].lMinL = 1;
	g_FormCaract[edt_libero060].lMaxL = 8;
	g_FormCaract[edt_libero060].bEndox = TRUE;
	g_FormCaract[edt_libero060].bImageNT = FALSE;

	g_FormCaract[edt_libero061].lID = EDT_LIBERO061;
	g_FormCaract[edt_libero061].sDescrizione = theApp.m_sLabelText[61];
	g_FormCaract[edt_libero061].lMinA = 2;
	g_FormCaract[edt_libero061].lMaxA = 26;
	g_FormCaract[edt_libero061].lMinL = 1;
	g_FormCaract[edt_libero061].lMaxL = 8;
	g_FormCaract[edt_libero061].bEndox = TRUE;
	g_FormCaract[edt_libero061].bImageNT = FALSE;

	g_FormCaract[edt_libero062].lID = EDT_LIBERO062;
	g_FormCaract[edt_libero062].sDescrizione = theApp.m_sLabelText[62];
	g_FormCaract[edt_libero062].lMinA = 2;
	g_FormCaract[edt_libero062].lMaxA = 26;
	g_FormCaract[edt_libero062].lMinL = 1;
	g_FormCaract[edt_libero062].lMaxL = 8;
	g_FormCaract[edt_libero062].bEndox = TRUE;
	g_FormCaract[edt_libero062].bImageNT = FALSE;

	g_FormCaract[edt_libero063].lID = EDT_LIBERO063;
	g_FormCaract[edt_libero063].sDescrizione = theApp.m_sLabelText[63];
	g_FormCaract[edt_libero063].lMinA = 2;
	g_FormCaract[edt_libero063].lMaxA = 26;
	g_FormCaract[edt_libero063].lMinL = 1;
	g_FormCaract[edt_libero063].lMaxL = 8;
	g_FormCaract[edt_libero063].bEndox = TRUE;
	g_FormCaract[edt_libero063].bImageNT = FALSE;

	g_FormCaract[edt_libero064].lID = EDT_LIBERO064;
	g_FormCaract[edt_libero064].sDescrizione = theApp.m_sLabelText[64];
	g_FormCaract[edt_libero064].lMinA = 2;
	g_FormCaract[edt_libero064].lMaxA = 26;
	g_FormCaract[edt_libero064].lMinL = 1;
	g_FormCaract[edt_libero064].lMaxL = 8;
	g_FormCaract[edt_libero064].bEndox = TRUE;
	g_FormCaract[edt_libero064].bImageNT = FALSE;

	g_FormCaract[edt_libero065].lID = EDT_LIBERO065;
	g_FormCaract[edt_libero065].sDescrizione = theApp.m_sLabelText[65];
	g_FormCaract[edt_libero065].lMinA = 2;
	g_FormCaract[edt_libero065].lMaxA = 26;
	g_FormCaract[edt_libero065].lMinL = 1;
	g_FormCaract[edt_libero065].lMaxL = 8;
	g_FormCaract[edt_libero065].bEndox = TRUE;
	g_FormCaract[edt_libero065].bImageNT = FALSE;

	g_FormCaract[edt_libero066].lID = EDT_LIBERO066;
	g_FormCaract[edt_libero066].sDescrizione = theApp.m_sLabelText[66];
	g_FormCaract[edt_libero066].lMinA = 2;
	g_FormCaract[edt_libero066].lMaxA = 26;
	g_FormCaract[edt_libero066].lMinL = 1;
	g_FormCaract[edt_libero066].lMaxL = 8;
	g_FormCaract[edt_libero066].bEndox = TRUE;
	g_FormCaract[edt_libero066].bImageNT = FALSE;

	g_FormCaract[edt_libero067].lID = EDT_LIBERO067;
	g_FormCaract[edt_libero067].sDescrizione = theApp.m_sLabelText[67];
	g_FormCaract[edt_libero067].lMinA = 2;
	g_FormCaract[edt_libero067].lMaxA = 26;
	g_FormCaract[edt_libero067].lMinL = 1;
	g_FormCaract[edt_libero067].lMaxL = 8;
	g_FormCaract[edt_libero067].bEndox = TRUE;
	g_FormCaract[edt_libero067].bImageNT = FALSE;

	g_FormCaract[edt_libero068].lID = EDT_LIBERO068;
	g_FormCaract[edt_libero068].sDescrizione = theApp.m_sLabelText[68];
	g_FormCaract[edt_libero068].lMinA = 2;
	g_FormCaract[edt_libero068].lMaxA = 26;
	g_FormCaract[edt_libero068].lMinL = 1;
	g_FormCaract[edt_libero068].lMaxL = 8;
	g_FormCaract[edt_libero068].bEndox = TRUE;
	g_FormCaract[edt_libero068].bImageNT = FALSE;

	g_FormCaract[edt_libero069].lID = EDT_LIBERO069;
	g_FormCaract[edt_libero069].sDescrizione = theApp.m_sLabelText[69];
	g_FormCaract[edt_libero069].lMinA = 2;
	g_FormCaract[edt_libero069].lMaxA = 26;
	g_FormCaract[edt_libero069].lMinL = 1;
	g_FormCaract[edt_libero069].lMaxL = 8;
	g_FormCaract[edt_libero069].bEndox = TRUE;
	g_FormCaract[edt_libero069].bImageNT = FALSE;

	g_FormCaract[edt_libero070].lID = EDT_LIBERO070;
	g_FormCaract[edt_libero070].sDescrizione = theApp.m_sLabelText[70];
	g_FormCaract[edt_libero070].lMinA = 2;
	g_FormCaract[edt_libero070].lMaxA = 26;
	g_FormCaract[edt_libero070].lMinL = 1;
	g_FormCaract[edt_libero070].lMaxL = 8;
	g_FormCaract[edt_libero070].bEndox = TRUE;
	g_FormCaract[edt_libero070].bImageNT = FALSE;

	g_FormCaract[edt_libero071].lID = EDT_LIBERO071;
	g_FormCaract[edt_libero071].sDescrizione = theApp.m_sLabelText[71];
	g_FormCaract[edt_libero071].lMinA = 2;
	g_FormCaract[edt_libero071].lMaxA = 26;
	g_FormCaract[edt_libero071].lMinL = 1;
	g_FormCaract[edt_libero071].lMaxL = 8;
	g_FormCaract[edt_libero071].bEndox = TRUE;
	g_FormCaract[edt_libero071].bImageNT = FALSE;

	g_FormCaract[edt_libero072].lID = EDT_LIBERO072;
	g_FormCaract[edt_libero072].sDescrizione = theApp.m_sLabelText[72];
	g_FormCaract[edt_libero072].lMinA = 2;
	g_FormCaract[edt_libero072].lMaxA = 26;
	g_FormCaract[edt_libero072].lMinL = 1;
	g_FormCaract[edt_libero072].lMaxL = 8;
	g_FormCaract[edt_libero072].bEndox = TRUE;
	g_FormCaract[edt_libero072].bImageNT = FALSE;

	g_FormCaract[edt_libero073].lID = EDT_LIBERO073;
	g_FormCaract[edt_libero073].sDescrizione = theApp.m_sLabelText[73];
	g_FormCaract[edt_libero073].lMinA = 2;
	g_FormCaract[edt_libero073].lMaxA = 26;
	g_FormCaract[edt_libero073].lMinL = 1;
	g_FormCaract[edt_libero073].lMaxL = 8;
	g_FormCaract[edt_libero073].bEndox = TRUE;
	g_FormCaract[edt_libero073].bImageNT = FALSE;

	g_FormCaract[edt_libero074].lID = EDT_LIBERO074;
	g_FormCaract[edt_libero074].sDescrizione = theApp.m_sLabelText[74];
	g_FormCaract[edt_libero074].lMinA = 2;
	g_FormCaract[edt_libero074].lMaxA = 26;
	g_FormCaract[edt_libero074].lMinL = 1;
	g_FormCaract[edt_libero074].lMaxL = 8;
	g_FormCaract[edt_libero074].bEndox = TRUE;
	g_FormCaract[edt_libero074].bImageNT = FALSE;

	g_FormCaract[edt_libero075].lID = EDT_LIBERO075;
	g_FormCaract[edt_libero075].sDescrizione = theApp.m_sLabelText[75];
	g_FormCaract[edt_libero075].lMinA = 2;
	g_FormCaract[edt_libero075].lMaxA = 26;
	g_FormCaract[edt_libero075].lMinL = 1;
	g_FormCaract[edt_libero075].lMaxL = 8;
	g_FormCaract[edt_libero075].bEndox = TRUE;
	g_FormCaract[edt_libero075].bImageNT = FALSE;

	g_FormCaract[edt_libero076].lID = EDT_LIBERO076;
	g_FormCaract[edt_libero076].sDescrizione = theApp.m_sLabelText[76];
	g_FormCaract[edt_libero076].lMinA = 2;
	g_FormCaract[edt_libero076].lMaxA = 26;
	g_FormCaract[edt_libero076].lMinL = 1;
	g_FormCaract[edt_libero076].lMaxL = 8;
	g_FormCaract[edt_libero076].bEndox = TRUE;
	g_FormCaract[edt_libero076].bImageNT = FALSE;

	g_FormCaract[edt_libero077].lID = EDT_LIBERO077;
	g_FormCaract[edt_libero077].sDescrizione = theApp.m_sLabelText[77];
	g_FormCaract[edt_libero077].lMinA = 2;
	g_FormCaract[edt_libero077].lMaxA = 26;
	g_FormCaract[edt_libero077].lMinL = 1;
	g_FormCaract[edt_libero077].lMaxL = 8;
	g_FormCaract[edt_libero077].bEndox = TRUE;
	g_FormCaract[edt_libero077].bImageNT = FALSE;

	g_FormCaract[edt_libero078].lID = EDT_LIBERO078;
	g_FormCaract[edt_libero078].sDescrizione = theApp.m_sLabelText[78];
	g_FormCaract[edt_libero078].lMinA = 2;
	g_FormCaract[edt_libero078].lMaxA = 26;
	g_FormCaract[edt_libero078].lMinL = 1;
	g_FormCaract[edt_libero078].lMaxL = 8;
	g_FormCaract[edt_libero078].bEndox = TRUE;
	g_FormCaract[edt_libero078].bImageNT = FALSE;

	g_FormCaract[edt_libero079].lID = EDT_LIBERO079;
	g_FormCaract[edt_libero079].sDescrizione = theApp.m_sLabelText[79];
	g_FormCaract[edt_libero079].lMinA = 2;
	g_FormCaract[edt_libero079].lMaxA = 26;
	g_FormCaract[edt_libero079].lMinL = 1;
	g_FormCaract[edt_libero079].lMaxL = 8;
	g_FormCaract[edt_libero079].bEndox = TRUE;
	g_FormCaract[edt_libero079].bImageNT = FALSE;

	g_FormCaract[edt_libero080].lID = EDT_LIBERO080;
	g_FormCaract[edt_libero080].sDescrizione = theApp.m_sLabelText[80];
	g_FormCaract[edt_libero080].lMinA = 2;
	g_FormCaract[edt_libero080].lMaxA = 26;
	g_FormCaract[edt_libero080].lMinL = 1;
	g_FormCaract[edt_libero080].lMaxL = 8;
	g_FormCaract[edt_libero080].bEndox = TRUE;
	g_FormCaract[edt_libero080].bImageNT = FALSE;

	g_FormCaract[edt_libero081].lID = EDT_LIBERO081;
	g_FormCaract[edt_libero081].sDescrizione = theApp.m_sLabelText[81];
	g_FormCaract[edt_libero081].lMinA = 2;
	g_FormCaract[edt_libero081].lMaxA = 26;
	g_FormCaract[edt_libero081].lMinL = 1;
	g_FormCaract[edt_libero081].lMaxL = 8;
	g_FormCaract[edt_libero081].bEndox = TRUE;
	g_FormCaract[edt_libero081].bImageNT = FALSE;

	g_FormCaract[edt_libero082].lID = EDT_LIBERO082;
	g_FormCaract[edt_libero082].sDescrizione = theApp.m_sLabelText[82];
	g_FormCaract[edt_libero082].lMinA = 2;
	g_FormCaract[edt_libero082].lMaxA = 26;
	g_FormCaract[edt_libero082].lMinL = 1;
	g_FormCaract[edt_libero082].lMaxL = 8;
	g_FormCaract[edt_libero082].bEndox = TRUE;
	g_FormCaract[edt_libero082].bImageNT = FALSE;

	g_FormCaract[edt_libero083].lID = EDT_LIBERO083;
	g_FormCaract[edt_libero083].sDescrizione = theApp.m_sLabelText[83];
	g_FormCaract[edt_libero083].lMinA = 2;
	g_FormCaract[edt_libero083].lMaxA = 26;
	g_FormCaract[edt_libero083].lMinL = 1;
	g_FormCaract[edt_libero083].lMaxL = 8;
	g_FormCaract[edt_libero083].bEndox = TRUE;
	g_FormCaract[edt_libero083].bImageNT = FALSE;

	g_FormCaract[edt_libero084].lID = EDT_LIBERO084;
	g_FormCaract[edt_libero084].sDescrizione = theApp.m_sLabelText[84];
	g_FormCaract[edt_libero084].lMinA = 2;
	g_FormCaract[edt_libero084].lMaxA = 26;
	g_FormCaract[edt_libero084].lMinL = 1;
	g_FormCaract[edt_libero084].lMaxL = 8;
	g_FormCaract[edt_libero084].bEndox = TRUE;
	g_FormCaract[edt_libero084].bImageNT = FALSE;

	g_FormCaract[edt_libero085].lID = EDT_LIBERO085;
	g_FormCaract[edt_libero085].sDescrizione = theApp.m_sLabelText[85];
	g_FormCaract[edt_libero085].lMinA = 2;
	g_FormCaract[edt_libero085].lMaxA = 26;
	g_FormCaract[edt_libero085].lMinL = 1;
	g_FormCaract[edt_libero085].lMaxL = 8;
	g_FormCaract[edt_libero085].bEndox = TRUE;
	g_FormCaract[edt_libero085].bImageNT = FALSE;

	g_FormCaract[edt_libero086].lID = EDT_LIBERO086;
	g_FormCaract[edt_libero086].sDescrizione = theApp.m_sLabelText[86];
	g_FormCaract[edt_libero086].lMinA = 2;
	g_FormCaract[edt_libero086].lMaxA = 26;
	g_FormCaract[edt_libero086].lMinL = 1;
	g_FormCaract[edt_libero086].lMaxL = 8;
	g_FormCaract[edt_libero086].bEndox = TRUE;
	g_FormCaract[edt_libero086].bImageNT = FALSE;

	g_FormCaract[edt_libero087].lID = EDT_LIBERO087;
	g_FormCaract[edt_libero087].sDescrizione = theApp.m_sLabelText[87];
	g_FormCaract[edt_libero087].lMinA = 2;
	g_FormCaract[edt_libero087].lMaxA = 26;
	g_FormCaract[edt_libero087].lMinL = 1;
	g_FormCaract[edt_libero087].lMaxL = 8;
	g_FormCaract[edt_libero087].bEndox = TRUE;
	g_FormCaract[edt_libero087].bImageNT = FALSE;

	g_FormCaract[edt_libero088].lID = EDT_LIBERO088;
	g_FormCaract[edt_libero088].sDescrizione = theApp.m_sLabelText[88];
	g_FormCaract[edt_libero088].lMinA = 2;
	g_FormCaract[edt_libero088].lMaxA = 26;
	g_FormCaract[edt_libero088].lMinL = 1;
	g_FormCaract[edt_libero088].lMaxL = 8;
	g_FormCaract[edt_libero088].bEndox = TRUE;
	g_FormCaract[edt_libero088].bImageNT = FALSE;

	g_FormCaract[edt_libero089].lID = EDT_LIBERO089;
	g_FormCaract[edt_libero089].sDescrizione = theApp.m_sLabelText[89];
	g_FormCaract[edt_libero089].lMinA = 2;
	g_FormCaract[edt_libero089].lMaxA = 26;
	g_FormCaract[edt_libero089].lMinL = 1;
	g_FormCaract[edt_libero089].lMaxL = 8;
	g_FormCaract[edt_libero089].bEndox = TRUE;
	g_FormCaract[edt_libero089].bImageNT = FALSE;

	g_FormCaract[edt_libero090].lID = EDT_LIBERO090;
	g_FormCaract[edt_libero090].sDescrizione = theApp.m_sLabelText[90];
	g_FormCaract[edt_libero090].lMinA = 2;
	g_FormCaract[edt_libero090].lMaxA = 26;
	g_FormCaract[edt_libero090].lMinL = 1;
	g_FormCaract[edt_libero090].lMaxL = 8;
	g_FormCaract[edt_libero090].bEndox = TRUE;
	g_FormCaract[edt_libero090].bImageNT = FALSE;

	g_FormCaract[edt_libero091].lID = EDT_LIBERO091;
	g_FormCaract[edt_libero091].sDescrizione = theApp.m_sLabelText[91];
	g_FormCaract[edt_libero091].lMinA = 2;
	g_FormCaract[edt_libero091].lMaxA = 26;
	g_FormCaract[edt_libero091].lMinL = 1;
	g_FormCaract[edt_libero091].lMaxL = 8;
	g_FormCaract[edt_libero091].bEndox = TRUE;
	g_FormCaract[edt_libero091].bImageNT = FALSE;

	g_FormCaract[edt_libero092].lID = EDT_LIBERO092;
	g_FormCaract[edt_libero092].sDescrizione = theApp.m_sLabelText[92];
	g_FormCaract[edt_libero092].lMinA = 2;
	g_FormCaract[edt_libero092].lMaxA = 26;
	g_FormCaract[edt_libero092].lMinL = 1;
	g_FormCaract[edt_libero092].lMaxL = 8;
	g_FormCaract[edt_libero092].bEndox = TRUE;
	g_FormCaract[edt_libero092].bImageNT = FALSE;

	g_FormCaract[edt_libero093].lID = EDT_LIBERO093;
	g_FormCaract[edt_libero093].sDescrizione = theApp.m_sLabelText[93];
	g_FormCaract[edt_libero093].lMinA = 2;
	g_FormCaract[edt_libero093].lMaxA = 26;
	g_FormCaract[edt_libero093].lMinL = 1;
	g_FormCaract[edt_libero093].lMaxL = 8;
	g_FormCaract[edt_libero093].bEndox = TRUE;
	g_FormCaract[edt_libero093].bImageNT = FALSE;

	g_FormCaract[edt_libero094].lID = EDT_LIBERO094;
	g_FormCaract[edt_libero094].sDescrizione = theApp.m_sLabelText[94];
	g_FormCaract[edt_libero094].lMinA = 2;
	g_FormCaract[edt_libero094].lMaxA = 26;
	g_FormCaract[edt_libero094].lMinL = 1;
	g_FormCaract[edt_libero094].lMaxL = 8;
	g_FormCaract[edt_libero094].bEndox = TRUE;
	g_FormCaract[edt_libero094].bImageNT = FALSE;

	g_FormCaract[edt_libero095].lID = EDT_LIBERO095;
	g_FormCaract[edt_libero095].sDescrizione = theApp.m_sLabelText[95];
	g_FormCaract[edt_libero095].lMinA = 2;
	g_FormCaract[edt_libero095].lMaxA = 26;
	g_FormCaract[edt_libero095].lMinL = 1;
	g_FormCaract[edt_libero095].lMaxL = 8;
	g_FormCaract[edt_libero095].bEndox = TRUE;
	g_FormCaract[edt_libero095].bImageNT = FALSE;

	g_FormCaract[edt_libero096].lID = EDT_LIBERO096;
	g_FormCaract[edt_libero096].sDescrizione = theApp.m_sLabelText[96];
	g_FormCaract[edt_libero096].lMinA = 2;
	g_FormCaract[edt_libero096].lMaxA = 26;
	g_FormCaract[edt_libero096].lMinL = 1;
	g_FormCaract[edt_libero096].lMaxL = 8;
	g_FormCaract[edt_libero096].bEndox = TRUE;
	g_FormCaract[edt_libero096].bImageNT = FALSE;

	g_FormCaract[edt_libero097].lID = EDT_LIBERO097;
	g_FormCaract[edt_libero097].sDescrizione = theApp.m_sLabelText[97];
	g_FormCaract[edt_libero097].lMinA = 2;
	g_FormCaract[edt_libero097].lMaxA = 26;
	g_FormCaract[edt_libero097].lMinL = 1;
	g_FormCaract[edt_libero097].lMaxL = 8;
	g_FormCaract[edt_libero097].bEndox = TRUE;
	g_FormCaract[edt_libero097].bImageNT = FALSE;

	g_FormCaract[edt_libero098].lID = EDT_LIBERO098;
	g_FormCaract[edt_libero098].sDescrizione = theApp.m_sLabelText[98];
	g_FormCaract[edt_libero098].lMinA = 2;
	g_FormCaract[edt_libero098].lMaxA = 26;
	g_FormCaract[edt_libero098].lMinL = 1;
	g_FormCaract[edt_libero098].lMaxL = 8;
	g_FormCaract[edt_libero098].bEndox = TRUE;
	g_FormCaract[edt_libero098].bImageNT = FALSE;

	g_FormCaract[edt_libero099].lID = EDT_LIBERO099;
	g_FormCaract[edt_libero099].sDescrizione = theApp.m_sLabelText[99];
	g_FormCaract[edt_libero099].lMinA = 2;
	g_FormCaract[edt_libero099].lMaxA = 26;
	g_FormCaract[edt_libero099].lMinL = 1;
	g_FormCaract[edt_libero099].lMaxL = 8;
	g_FormCaract[edt_libero099].bEndox = TRUE;
	g_FormCaract[edt_libero099].bImageNT = FALSE;

	g_FormCaract[edt_liberortf000].lID = EDT_LIBERORTF000;
	g_FormCaract[edt_liberortf000].sDescrizione = theApp.m_sLabelTextRtf[0];
	g_FormCaract[edt_liberortf000].lMinA = 2;
	g_FormCaract[edt_liberortf000].lMaxA = 26;
	g_FormCaract[edt_liberortf000].lMinL = 1;
	g_FormCaract[edt_liberortf000].lMaxL = 8;
	g_FormCaract[edt_liberortf000].bEndox = TRUE;
	g_FormCaract[edt_liberortf000].bImageNT = FALSE;

	g_FormCaract[edt_liberortf001].lID = EDT_LIBERORTF001;
	g_FormCaract[edt_liberortf001].sDescrizione = theApp.m_sLabelTextRtf[1];
	g_FormCaract[edt_liberortf001].lMinA = 2;
	g_FormCaract[edt_liberortf001].lMaxA = 26;
	g_FormCaract[edt_liberortf001].lMinL = 1;
	g_FormCaract[edt_liberortf001].lMaxL = 8;
	g_FormCaract[edt_liberortf001].bEndox = TRUE;
	g_FormCaract[edt_liberortf001].bImageNT = FALSE;

	g_FormCaract[edt_liberortf002].lID = EDT_LIBERORTF002;
	g_FormCaract[edt_liberortf002].sDescrizione = theApp.m_sLabelTextRtf[2];
	g_FormCaract[edt_liberortf002].lMinA = 2;
	g_FormCaract[edt_liberortf002].lMaxA = 26;
	g_FormCaract[edt_liberortf002].lMinL = 1;
	g_FormCaract[edt_liberortf002].lMaxL = 8;
	g_FormCaract[edt_liberortf002].bEndox = TRUE;
	g_FormCaract[edt_liberortf002].bImageNT = FALSE;

	g_FormCaract[edt_liberortf003].lID = EDT_LIBERORTF003;
	g_FormCaract[edt_liberortf003].sDescrizione = theApp.m_sLabelTextRtf[3];
	g_FormCaract[edt_liberortf003].lMinA = 2;
	g_FormCaract[edt_liberortf003].lMaxA = 26;
	g_FormCaract[edt_liberortf003].lMinL = 1;
	g_FormCaract[edt_liberortf003].lMaxL = 8;
	g_FormCaract[edt_liberortf003].bEndox = TRUE;
	g_FormCaract[edt_liberortf003].bImageNT = FALSE;

	g_FormCaract[edt_liberortf004].lID = EDT_LIBERORTF004;
	g_FormCaract[edt_liberortf004].sDescrizione = theApp.m_sLabelTextRtf[4];
	g_FormCaract[edt_liberortf004].lMinA = 2;
	g_FormCaract[edt_liberortf004].lMaxA = 26;
	g_FormCaract[edt_liberortf004].lMinL = 1;
	g_FormCaract[edt_liberortf004].lMaxL = 8;
	g_FormCaract[edt_liberortf004].bEndox = TRUE;
	g_FormCaract[edt_liberortf004].bImageNT = FALSE;

	g_FormCaract[edt_liberortf005].lID = EDT_LIBERORTF005;
	g_FormCaract[edt_liberortf005].sDescrizione = theApp.m_sLabelTextRtf[5];
	g_FormCaract[edt_liberortf005].lMinA = 2;
	g_FormCaract[edt_liberortf005].lMaxA = 26;
	g_FormCaract[edt_liberortf005].lMinL = 1;
	g_FormCaract[edt_liberortf005].lMaxL = 8;
	g_FormCaract[edt_liberortf005].bEndox = TRUE;
	g_FormCaract[edt_liberortf005].bImageNT = FALSE;

	g_FormCaract[edt_liberortf006].lID = EDT_LIBERORTF006;
	g_FormCaract[edt_liberortf006].sDescrizione = theApp.m_sLabelTextRtf[6];
	g_FormCaract[edt_liberortf006].lMinA = 2;
	g_FormCaract[edt_liberortf006].lMaxA = 26;
	g_FormCaract[edt_liberortf006].lMinL = 1;
	g_FormCaract[edt_liberortf006].lMaxL = 8;
	g_FormCaract[edt_liberortf006].bEndox = TRUE;
	g_FormCaract[edt_liberortf006].bImageNT = FALSE;

	g_FormCaract[edt_liberortf007].lID = EDT_LIBERORTF007;
	g_FormCaract[edt_liberortf007].sDescrizione = theApp.m_sLabelTextRtf[7];
	g_FormCaract[edt_liberortf007].lMinA = 2;
	g_FormCaract[edt_liberortf007].lMaxA = 26;
	g_FormCaract[edt_liberortf007].lMinL = 1;
	g_FormCaract[edt_liberortf007].lMaxL = 8;
	g_FormCaract[edt_liberortf007].bEndox = TRUE;
	g_FormCaract[edt_liberortf007].bImageNT = FALSE;

	g_FormCaract[edt_liberortf008].lID = EDT_LIBERORTF008;
	g_FormCaract[edt_liberortf008].sDescrizione = theApp.m_sLabelTextRtf[8];
	g_FormCaract[edt_liberortf008].lMinA = 2;
	g_FormCaract[edt_liberortf008].lMaxA = 26;
	g_FormCaract[edt_liberortf008].lMinL = 1;
	g_FormCaract[edt_liberortf008].lMaxL = 8;
	g_FormCaract[edt_liberortf008].bEndox = TRUE;
	g_FormCaract[edt_liberortf008].bImageNT = FALSE;

	g_FormCaract[edt_liberortf009].lID = EDT_LIBERORTF009;
	g_FormCaract[edt_liberortf009].sDescrizione = theApp.m_sLabelTextRtf[9];
	g_FormCaract[edt_liberortf009].lMinA = 2;
	g_FormCaract[edt_liberortf009].lMaxA = 26;
	g_FormCaract[edt_liberortf009].lMinL = 1;
	g_FormCaract[edt_liberortf009].lMaxL = 8;
	g_FormCaract[edt_liberortf009].bEndox = TRUE;
	g_FormCaract[edt_liberortf009].bImageNT = FALSE;

	g_FormCaract[edt_liberortf010].lID = EDT_LIBERORTF010;
	g_FormCaract[edt_liberortf010].sDescrizione = theApp.m_sLabelTextRtf[10];
	g_FormCaract[edt_liberortf010].lMinA = 2;
	g_FormCaract[edt_liberortf010].lMaxA = 26;
	g_FormCaract[edt_liberortf010].lMinL = 1;
	g_FormCaract[edt_liberortf010].lMaxL = 8;
	g_FormCaract[edt_liberortf010].bEndox = TRUE;
	g_FormCaract[edt_liberortf010].bImageNT = FALSE;

	g_FormCaract[edt_liberortf011].lID = EDT_LIBERORTF011;
	g_FormCaract[edt_liberortf011].sDescrizione = theApp.m_sLabelTextRtf[11];
	g_FormCaract[edt_liberortf011].lMinA = 2;
	g_FormCaract[edt_liberortf011].lMaxA = 26;
	g_FormCaract[edt_liberortf011].lMinL = 1;
	g_FormCaract[edt_liberortf011].lMaxL = 8;
	g_FormCaract[edt_liberortf011].bEndox = TRUE;
	g_FormCaract[edt_liberortf011].bImageNT = FALSE;

	g_FormCaract[edt_liberortf012].lID = EDT_LIBERORTF012;
	g_FormCaract[edt_liberortf012].sDescrizione = theApp.m_sLabelTextRtf[12];
	g_FormCaract[edt_liberortf012].lMinA = 2;
	g_FormCaract[edt_liberortf012].lMaxA = 26;
	g_FormCaract[edt_liberortf012].lMinL = 1;
	g_FormCaract[edt_liberortf012].lMaxL = 8;
	g_FormCaract[edt_liberortf012].bEndox = TRUE;
	g_FormCaract[edt_liberortf012].bImageNT = FALSE;

	g_FormCaract[edt_liberortf013].lID = EDT_LIBERORTF013;
	g_FormCaract[edt_liberortf013].sDescrizione = theApp.m_sLabelTextRtf[13];
	g_FormCaract[edt_liberortf013].lMinA = 2;
	g_FormCaract[edt_liberortf013].lMaxA = 26;
	g_FormCaract[edt_liberortf013].lMinL = 1;
	g_FormCaract[edt_liberortf013].lMaxL = 8;
	g_FormCaract[edt_liberortf013].bEndox = TRUE;
	g_FormCaract[edt_liberortf013].bImageNT = FALSE;

	g_FormCaract[edt_liberortf014].lID = EDT_LIBERORTF014;
	g_FormCaract[edt_liberortf014].sDescrizione = theApp.m_sLabelTextRtf[14];
	g_FormCaract[edt_liberortf014].lMinA = 2;
	g_FormCaract[edt_liberortf014].lMaxA = 26;
	g_FormCaract[edt_liberortf014].lMinL = 1;
	g_FormCaract[edt_liberortf014].lMaxL = 8;
	g_FormCaract[edt_liberortf014].bEndox = TRUE;
	g_FormCaract[edt_liberortf014].bImageNT = FALSE;

	g_FormCaract[edt_liberortf015].lID = EDT_LIBERORTF015;
	g_FormCaract[edt_liberortf015].sDescrizione = theApp.m_sLabelTextRtf[15];
	g_FormCaract[edt_liberortf015].lMinA = 2;
	g_FormCaract[edt_liberortf015].lMaxA = 26;
	g_FormCaract[edt_liberortf015].lMinL = 1;
	g_FormCaract[edt_liberortf015].lMaxL = 8;
	g_FormCaract[edt_liberortf015].bEndox = TRUE;
	g_FormCaract[edt_liberortf015].bImageNT = FALSE;

	g_FormCaract[edt_liberortf016].lID = EDT_LIBERORTF016;
	g_FormCaract[edt_liberortf016].sDescrizione = theApp.m_sLabelTextRtf[16];
	g_FormCaract[edt_liberortf016].lMinA = 2;
	g_FormCaract[edt_liberortf016].lMaxA = 26;
	g_FormCaract[edt_liberortf016].lMinL = 1;
	g_FormCaract[edt_liberortf016].lMaxL = 8;
	g_FormCaract[edt_liberortf016].bEndox = TRUE;
	g_FormCaract[edt_liberortf016].bImageNT = FALSE;

	g_FormCaract[edt_liberortf017].lID = EDT_LIBERORTF017;
	g_FormCaract[edt_liberortf017].sDescrizione = theApp.m_sLabelTextRtf[17];
	g_FormCaract[edt_liberortf017].lMinA = 2;
	g_FormCaract[edt_liberortf017].lMaxA = 26;
	g_FormCaract[edt_liberortf017].lMinL = 1;
	g_FormCaract[edt_liberortf017].lMaxL = 8;
	g_FormCaract[edt_liberortf017].bEndox = TRUE;
	g_FormCaract[edt_liberortf017].bImageNT = FALSE;

	g_FormCaract[edt_liberortf018].lID = EDT_LIBERORTF018;
	g_FormCaract[edt_liberortf018].sDescrizione = theApp.m_sLabelTextRtf[18];
	g_FormCaract[edt_liberortf018].lMinA = 2;
	g_FormCaract[edt_liberortf018].lMaxA = 26;
	g_FormCaract[edt_liberortf018].lMinL = 1;
	g_FormCaract[edt_liberortf018].lMaxL = 8;
	g_FormCaract[edt_liberortf018].bEndox = TRUE;
	g_FormCaract[edt_liberortf018].bImageNT = FALSE;

	g_FormCaract[edt_liberortf019].lID = EDT_LIBERORTF019;
	g_FormCaract[edt_liberortf019].sDescrizione = theApp.m_sLabelTextRtf[19];
	g_FormCaract[edt_liberortf019].lMinA = 2;
	g_FormCaract[edt_liberortf019].lMaxA = 26;
	g_FormCaract[edt_liberortf019].lMinL = 1;
	g_FormCaract[edt_liberortf019].lMaxL = 8;
	g_FormCaract[edt_liberortf019].bEndox = TRUE;
	g_FormCaract[edt_liberortf019].bImageNT = FALSE;

	g_FormCaract[edt_liberocl000].lID = EDT_LIBEROCL000;
	g_FormCaract[edt_liberocl000].sDescrizione = theApp.m_sLabelTextCL[0];
	g_FormCaract[edt_liberocl000].lMinA = 2;
	g_FormCaract[edt_liberocl000].lMaxA = 26;
	g_FormCaract[edt_liberocl000].lMinL = 1;
	g_FormCaract[edt_liberocl000].lMaxL = 8;
	g_FormCaract[edt_liberocl000].bEndox = TRUE;
	g_FormCaract[edt_liberocl000].bImageNT = FALSE;

	g_FormCaract[edt_liberocl001].lID = EDT_LIBEROCL001;
	g_FormCaract[edt_liberocl001].sDescrizione = theApp.m_sLabelTextCL[1];
	g_FormCaract[edt_liberocl001].lMinA = 2;
	g_FormCaract[edt_liberocl001].lMaxA = 26;
	g_FormCaract[edt_liberocl001].lMinL = 1;
	g_FormCaract[edt_liberocl001].lMaxL = 8;
	g_FormCaract[edt_liberocl001].bEndox = TRUE;
	g_FormCaract[edt_liberocl001].bImageNT = FALSE;

	g_FormCaract[edt_liberocl002].lID = EDT_LIBEROCL002;
	g_FormCaract[edt_liberocl002].sDescrizione = theApp.m_sLabelTextCL[2];
	g_FormCaract[edt_liberocl002].lMinA = 2;
	g_FormCaract[edt_liberocl002].lMaxA = 26;
	g_FormCaract[edt_liberocl002].lMinL = 1;
	g_FormCaract[edt_liberocl002].lMaxL = 8;
	g_FormCaract[edt_liberocl002].bEndox = TRUE;
	g_FormCaract[edt_liberocl002].bImageNT = FALSE;

	g_FormCaract[edt_liberocl003].lID = EDT_LIBEROCL003;
	g_FormCaract[edt_liberocl003].sDescrizione = theApp.m_sLabelTextCL[3];
	g_FormCaract[edt_liberocl003].lMinA = 2;
	g_FormCaract[edt_liberocl003].lMaxA = 26;
	g_FormCaract[edt_liberocl003].lMinL = 1;
	g_FormCaract[edt_liberocl003].lMaxL = 8;
	g_FormCaract[edt_liberocl003].bEndox = TRUE;
	g_FormCaract[edt_liberocl003].bImageNT = FALSE;

	g_FormCaract[edt_liberocl004].lID = EDT_LIBEROCL004;
	g_FormCaract[edt_liberocl004].sDescrizione = theApp.m_sLabelTextCL[4];
	g_FormCaract[edt_liberocl004].lMinA = 2;
	g_FormCaract[edt_liberocl004].lMaxA = 26;
	g_FormCaract[edt_liberocl004].lMinL = 1;
	g_FormCaract[edt_liberocl004].lMaxL = 8;
	g_FormCaract[edt_liberocl004].bEndox = TRUE;
	g_FormCaract[edt_liberocl004].bImageNT = FALSE;

	g_FormCaract[edt_liberocl005].lID = EDT_LIBEROCL005;
	g_FormCaract[edt_liberocl005].sDescrizione = theApp.m_sLabelTextCL[5];
	g_FormCaract[edt_liberocl005].lMinA = 2;
	g_FormCaract[edt_liberocl005].lMaxA = 26;
	g_FormCaract[edt_liberocl005].lMinL = 1;
	g_FormCaract[edt_liberocl005].lMaxL = 8;
	g_FormCaract[edt_liberocl005].bEndox = TRUE;
	g_FormCaract[edt_liberocl005].bImageNT = FALSE;

	g_FormCaract[edt_liberocl006].lID = EDT_LIBEROCL006;
	g_FormCaract[edt_liberocl006].sDescrizione = theApp.m_sLabelTextCL[6];
	g_FormCaract[edt_liberocl006].lMinA = 2;
	g_FormCaract[edt_liberocl006].lMaxA = 26;
	g_FormCaract[edt_liberocl006].lMinL = 1;
	g_FormCaract[edt_liberocl006].lMaxL = 8;
	g_FormCaract[edt_liberocl006].bEndox = TRUE;
	g_FormCaract[edt_liberocl006].bImageNT = FALSE;

	g_FormCaract[edt_liberocl007].lID = EDT_LIBEROCL007;
	g_FormCaract[edt_liberocl007].sDescrizione = theApp.m_sLabelTextCL[7];
	g_FormCaract[edt_liberocl007].lMinA = 2;
	g_FormCaract[edt_liberocl007].lMaxA = 26;
	g_FormCaract[edt_liberocl007].lMinL = 1;
	g_FormCaract[edt_liberocl007].lMaxL = 8;
	g_FormCaract[edt_liberocl007].bEndox = TRUE;
	g_FormCaract[edt_liberocl007].bImageNT = FALSE;

	g_FormCaract[edt_liberocl008].lID = EDT_LIBEROCL008;
	g_FormCaract[edt_liberocl008].sDescrizione = theApp.m_sLabelTextCL[8];
	g_FormCaract[edt_liberocl008].lMinA = 2;
	g_FormCaract[edt_liberocl008].lMaxA = 26;
	g_FormCaract[edt_liberocl008].lMinL = 1;
	g_FormCaract[edt_liberocl008].lMaxL = 8;
	g_FormCaract[edt_liberocl008].bEndox = TRUE;
	g_FormCaract[edt_liberocl008].bImageNT = FALSE;

	g_FormCaract[edt_liberocl009].lID = EDT_LIBEROCL009;
	g_FormCaract[edt_liberocl009].sDescrizione = theApp.m_sLabelTextCL[9];
	g_FormCaract[edt_liberocl009].lMinA = 2;
	g_FormCaract[edt_liberocl009].lMaxA = 26;
	g_FormCaract[edt_liberocl009].lMinL = 1;
	g_FormCaract[edt_liberocl009].lMaxL = 8;
	g_FormCaract[edt_liberocl009].bEndox = TRUE;
	g_FormCaract[edt_liberocl009].bImageNT = FALSE;

	g_FormCaract[edt_liberocl010].lID = EDT_LIBEROCL010;
	g_FormCaract[edt_liberocl010].sDescrizione = theApp.m_sLabelTextCL[10];
	g_FormCaract[edt_liberocl010].lMinA = 2;
	g_FormCaract[edt_liberocl010].lMaxA = 26;
	g_FormCaract[edt_liberocl010].lMinL = 1;
	g_FormCaract[edt_liberocl010].lMaxL = 8;
	g_FormCaract[edt_liberocl010].bEndox = TRUE;
	g_FormCaract[edt_liberocl010].bImageNT = FALSE;

	g_FormCaract[edt_liberocl011].lID = EDT_LIBEROCL011;
	g_FormCaract[edt_liberocl011].sDescrizione = theApp.m_sLabelTextCL[11];
	g_FormCaract[edt_liberocl011].lMinA = 2;
	g_FormCaract[edt_liberocl011].lMaxA = 26;
	g_FormCaract[edt_liberocl011].lMinL = 1;
	g_FormCaract[edt_liberocl011].lMaxL = 8;
	g_FormCaract[edt_liberocl011].bEndox = TRUE;
	g_FormCaract[edt_liberocl011].bImageNT = FALSE;

	g_FormCaract[edt_liberocl012].lID = EDT_LIBEROCL012;
	g_FormCaract[edt_liberocl012].sDescrizione = theApp.m_sLabelTextCL[12];
	g_FormCaract[edt_liberocl012].lMinA = 2;
	g_FormCaract[edt_liberocl012].lMaxA = 26;
	g_FormCaract[edt_liberocl012].lMinL = 1;
	g_FormCaract[edt_liberocl012].lMaxL = 8;
	g_FormCaract[edt_liberocl012].bEndox = TRUE;
	g_FormCaract[edt_liberocl012].bImageNT = FALSE;

	g_FormCaract[edt_liberocl013].lID = EDT_LIBEROCL013;
	g_FormCaract[edt_liberocl013].sDescrizione = theApp.m_sLabelTextCL[13];
	g_FormCaract[edt_liberocl013].lMinA = 2;
	g_FormCaract[edt_liberocl013].lMaxA = 26;
	g_FormCaract[edt_liberocl013].lMinL = 1;
	g_FormCaract[edt_liberocl013].lMaxL = 8;
	g_FormCaract[edt_liberocl013].bEndox = TRUE;
	g_FormCaract[edt_liberocl013].bImageNT = FALSE;

	g_FormCaract[edt_liberocl014].lID = EDT_LIBEROCL014;
	g_FormCaract[edt_liberocl014].sDescrizione = theApp.m_sLabelTextCL[14];
	g_FormCaract[edt_liberocl014].lMinA = 2;
	g_FormCaract[edt_liberocl014].lMaxA = 26;
	g_FormCaract[edt_liberocl014].lMinL = 1;
	g_FormCaract[edt_liberocl014].lMaxL = 8;
	g_FormCaract[edt_liberocl014].bEndox = TRUE;
	g_FormCaract[edt_liberocl014].bImageNT = FALSE;

	g_FormCaract[edt_liberocl015].lID = EDT_LIBEROCL015;
	g_FormCaract[edt_liberocl015].sDescrizione = theApp.m_sLabelTextCL[15];
	g_FormCaract[edt_liberocl015].lMinA = 2;
	g_FormCaract[edt_liberocl015].lMaxA = 26;
	g_FormCaract[edt_liberocl015].lMinL = 1;
	g_FormCaract[edt_liberocl015].lMaxL = 8;
	g_FormCaract[edt_liberocl015].bEndox = TRUE;
	g_FormCaract[edt_liberocl015].bImageNT = FALSE;

	g_FormCaract[edt_liberocl016].lID = EDT_LIBEROCL016;
	g_FormCaract[edt_liberocl016].sDescrizione = theApp.m_sLabelTextCL[16];
	g_FormCaract[edt_liberocl016].lMinA = 2;
	g_FormCaract[edt_liberocl016].lMaxA = 26;
	g_FormCaract[edt_liberocl016].lMinL = 1;
	g_FormCaract[edt_liberocl016].lMaxL = 8;
	g_FormCaract[edt_liberocl016].bEndox = TRUE;
	g_FormCaract[edt_liberocl016].bImageNT = FALSE;

	g_FormCaract[edt_liberocl017].lID = EDT_LIBEROCL017;
	g_FormCaract[edt_liberocl017].sDescrizione = theApp.m_sLabelTextCL[17];
	g_FormCaract[edt_liberocl017].lMinA = 2;
	g_FormCaract[edt_liberocl017].lMaxA = 26;
	g_FormCaract[edt_liberocl017].lMinL = 1;
	g_FormCaract[edt_liberocl017].lMaxL = 8;
	g_FormCaract[edt_liberocl017].bEndox = TRUE;
	g_FormCaract[edt_liberocl017].bImageNT = FALSE;

	g_FormCaract[edt_liberocl018].lID = EDT_LIBEROCL018;
	g_FormCaract[edt_liberocl018].sDescrizione = theApp.m_sLabelTextCL[18];
	g_FormCaract[edt_liberocl018].lMinA = 2;
	g_FormCaract[edt_liberocl018].lMaxA = 26;
	g_FormCaract[edt_liberocl018].lMinL = 1;
	g_FormCaract[edt_liberocl018].lMaxL = 8;
	g_FormCaract[edt_liberocl018].bEndox = TRUE;
	g_FormCaract[edt_liberocl018].bImageNT = FALSE;

	g_FormCaract[edt_liberocl019].lID = EDT_LIBEROCL019;
	g_FormCaract[edt_liberocl019].sDescrizione = theApp.m_sLabelTextCL[19];
	g_FormCaract[edt_liberocl019].lMinA = 2;
	g_FormCaract[edt_liberocl019].lMaxA = 26;
	g_FormCaract[edt_liberocl019].lMinL = 1;
	g_FormCaract[edt_liberocl019].lMaxL = 8;
	g_FormCaract[edt_liberocl019].bEndox = TRUE;
	g_FormCaract[edt_liberocl019].bImageNT = FALSE;

	g_FormCaract[edt_liberodataora000].lID = EDT_LIBERODATAORA000;
	g_FormCaract[edt_liberodataora000].sDescrizione = theApp.m_sLabelDate[0];
	g_FormCaract[edt_liberodataora000].lMinA = 2;
	g_FormCaract[edt_liberodataora000].lMaxA = 2;
	g_FormCaract[edt_liberodataora000].lMinL = 1;
	g_FormCaract[edt_liberodataora000].lMaxL = 4;
	g_FormCaract[edt_liberodataora000].bEndox = TRUE;
	g_FormCaract[edt_liberodataora000].bImageNT = FALSE;

	g_FormCaract[edt_liberodataora001].lID = EDT_LIBERODATAORA001;
	g_FormCaract[edt_liberodataora001].sDescrizione = theApp.m_sLabelDate[1];
	g_FormCaract[edt_liberodataora001].lMinA = 2;
	g_FormCaract[edt_liberodataora001].lMaxA = 2;
	g_FormCaract[edt_liberodataora001].lMinL = 1;
	g_FormCaract[edt_liberodataora001].lMaxL = 4;
	g_FormCaract[edt_liberodataora001].bEndox = TRUE;
	g_FormCaract[edt_liberodataora001].bImageNT = FALSE;

	g_FormCaract[edt_liberodataora002].lID = EDT_LIBERODATAORA002;
	g_FormCaract[edt_liberodataora002].sDescrizione = theApp.m_sLabelDate[2];
	g_FormCaract[edt_liberodataora002].lMinA = 2;
	g_FormCaract[edt_liberodataora002].lMaxA = 2;
	g_FormCaract[edt_liberodataora002].lMinL = 1;
	g_FormCaract[edt_liberodataora002].lMaxL = 4;
	g_FormCaract[edt_liberodataora002].bEndox = TRUE;
	g_FormCaract[edt_liberodataora002].bImageNT = FALSE;

	g_FormCaract[edt_liberodataora003].lID = EDT_LIBERODATAORA003;
	g_FormCaract[edt_liberodataora003].sDescrizione = theApp.m_sLabelDate[3];
	g_FormCaract[edt_liberodataora003].lMinA = 2;
	g_FormCaract[edt_liberodataora003].lMaxA = 2;
	g_FormCaract[edt_liberodataora003].lMinL = 1;
	g_FormCaract[edt_liberodataora003].lMaxL = 4;
	g_FormCaract[edt_liberodataora003].bEndox = TRUE;
	g_FormCaract[edt_liberodataora003].bImageNT = FALSE;

	g_FormCaract[edt_liberodataora004].lID = EDT_LIBERODATAORA004;
	g_FormCaract[edt_liberodataora004].sDescrizione = theApp.m_sLabelDate[4];
	g_FormCaract[edt_liberodataora004].lMinA = 2;
	g_FormCaract[edt_liberodataora004].lMaxA = 2;
	g_FormCaract[edt_liberodataora004].lMinL = 1;
	g_FormCaract[edt_liberodataora004].lMaxL = 4;
	g_FormCaract[edt_liberodataora004].bEndox = TRUE;
	g_FormCaract[edt_liberodataora004].bImageNT = FALSE;

	g_FormCaract[edt_liberodataora005].lID = EDT_LIBERODATAORA005;
	g_FormCaract[edt_liberodataora005].sDescrizione = theApp.m_sLabelDate[5];
	g_FormCaract[edt_liberodataora005].lMinA = 2;
	g_FormCaract[edt_liberodataora005].lMaxA = 2;
	g_FormCaract[edt_liberodataora005].lMinL = 1;
	g_FormCaract[edt_liberodataora005].lMaxL = 4;
	g_FormCaract[edt_liberodataora005].bEndox = TRUE;
	g_FormCaract[edt_liberodataora005].bImageNT = FALSE;

	g_FormCaract[edt_liberodataora006].lID = EDT_LIBERODATAORA006;
	g_FormCaract[edt_liberodataora006].sDescrizione = theApp.m_sLabelDate[6];
	g_FormCaract[edt_liberodataora006].lMinA = 2;
	g_FormCaract[edt_liberodataora006].lMaxA = 2;
	g_FormCaract[edt_liberodataora006].lMinL = 1;
	g_FormCaract[edt_liberodataora006].lMaxL = 4;
	g_FormCaract[edt_liberodataora006].bEndox = TRUE;
	g_FormCaract[edt_liberodataora006].bImageNT = FALSE;

	g_FormCaract[edt_liberodataora007].lID = EDT_LIBERODATAORA007;
	g_FormCaract[edt_liberodataora007].sDescrizione = theApp.m_sLabelDate[7];
	g_FormCaract[edt_liberodataora007].lMinA = 2;
	g_FormCaract[edt_liberodataora007].lMaxA = 2;
	g_FormCaract[edt_liberodataora007].lMinL = 1;
	g_FormCaract[edt_liberodataora007].lMaxL = 4;
	g_FormCaract[edt_liberodataora007].bEndox = TRUE;
	g_FormCaract[edt_liberodataora007].bImageNT = FALSE;

	g_FormCaract[edt_liberodataora008].lID = EDT_LIBERODATAORA008;
	g_FormCaract[edt_liberodataora008].sDescrizione = theApp.m_sLabelDate[8];
	g_FormCaract[edt_liberodataora008].lMinA = 2;
	g_FormCaract[edt_liberodataora008].lMaxA = 2;
	g_FormCaract[edt_liberodataora008].lMinL = 1;
	g_FormCaract[edt_liberodataora008].lMaxL = 4;
	g_FormCaract[edt_liberodataora008].bEndox = TRUE;
	g_FormCaract[edt_liberodataora008].bImageNT = FALSE;

	g_FormCaract[edt_liberodataora009].lID = EDT_LIBERODATAORA009;
	g_FormCaract[edt_liberodataora009].sDescrizione = theApp.m_sLabelDate[9];
	g_FormCaract[edt_liberodataora009].lMinA = 2;
	g_FormCaract[edt_liberodataora009].lMaxA = 2;
	g_FormCaract[edt_liberodataora009].lMinL = 1;
	g_FormCaract[edt_liberodataora009].lMaxL = 4;
	g_FormCaract[edt_liberodataora009].bEndox = TRUE;
	g_FormCaract[edt_liberodataora009].bImageNT = FALSE;

	g_FormCaract[edt_liberodataora010].lID = EDT_LIBERODATAORA010;
	g_FormCaract[edt_liberodataora010].sDescrizione = theApp.m_sLabelDate[10];
	g_FormCaract[edt_liberodataora010].lMinA = 2;
	g_FormCaract[edt_liberodataora010].lMaxA = 2;
	g_FormCaract[edt_liberodataora010].lMinL = 1;
	g_FormCaract[edt_liberodataora010].lMaxL = 4;
	g_FormCaract[edt_liberodataora010].bEndox = TRUE;
	g_FormCaract[edt_liberodataora010].bImageNT = FALSE;

	g_FormCaract[edt_liberodataora011].lID = EDT_LIBERODATAORA011;
	g_FormCaract[edt_liberodataora011].sDescrizione = theApp.m_sLabelDate[11];
	g_FormCaract[edt_liberodataora011].lMinA = 2;
	g_FormCaract[edt_liberodataora011].lMaxA = 2;
	g_FormCaract[edt_liberodataora011].lMinL = 1;
	g_FormCaract[edt_liberodataora011].lMaxL = 4;
	g_FormCaract[edt_liberodataora011].bEndox = TRUE;
	g_FormCaract[edt_liberodataora011].bImageNT = FALSE;

	g_FormCaract[edt_liberodataora012].lID = EDT_LIBERODATAORA012;
	g_FormCaract[edt_liberodataora012].sDescrizione = theApp.m_sLabelDate[12];
	g_FormCaract[edt_liberodataora012].lMinA = 2;
	g_FormCaract[edt_liberodataora012].lMaxA = 2;
	g_FormCaract[edt_liberodataora012].lMinL = 1;
	g_FormCaract[edt_liberodataora012].lMaxL = 4;
	g_FormCaract[edt_liberodataora012].bEndox = TRUE;
	g_FormCaract[edt_liberodataora012].bImageNT = FALSE;

	g_FormCaract[edt_liberodataora013].lID = EDT_LIBERODATAORA013;
	g_FormCaract[edt_liberodataora013].sDescrizione = theApp.m_sLabelDate[13];
	g_FormCaract[edt_liberodataora013].lMinA = 2;
	g_FormCaract[edt_liberodataora013].lMaxA = 2;
	g_FormCaract[edt_liberodataora013].lMinL = 1;
	g_FormCaract[edt_liberodataora013].lMaxL = 4;
	g_FormCaract[edt_liberodataora013].bEndox = TRUE;
	g_FormCaract[edt_liberodataora013].bImageNT = FALSE;

	g_FormCaract[edt_liberodataora014].lID = EDT_LIBERODATAORA014;
	g_FormCaract[edt_liberodataora014].sDescrizione = theApp.m_sLabelDate[14];
	g_FormCaract[edt_liberodataora014].lMinA = 2;
	g_FormCaract[edt_liberodataora014].lMaxA = 2;
	g_FormCaract[edt_liberodataora014].lMinL = 1;
	g_FormCaract[edt_liberodataora014].lMaxL = 4;
	g_FormCaract[edt_liberodataora014].bEndox = TRUE;
	g_FormCaract[edt_liberodataora014].bImageNT = FALSE;

	g_FormCaract[edt_liberodataora015].lID = EDT_LIBERODATAORA015;
	g_FormCaract[edt_liberodataora015].sDescrizione = theApp.m_sLabelDate[15];
	g_FormCaract[edt_liberodataora015].lMinA = 2;
	g_FormCaract[edt_liberodataora015].lMaxA = 2;
	g_FormCaract[edt_liberodataora015].lMinL = 1;
	g_FormCaract[edt_liberodataora015].lMaxL = 4;
	g_FormCaract[edt_liberodataora015].bEndox = TRUE;
	g_FormCaract[edt_liberodataora015].bImageNT = FALSE;

	g_FormCaract[edt_liberodataora016].lID = EDT_LIBERODATAORA016;
	g_FormCaract[edt_liberodataora016].sDescrizione = theApp.m_sLabelDate[16];
	g_FormCaract[edt_liberodataora016].lMinA = 2;
	g_FormCaract[edt_liberodataora016].lMaxA = 2;
	g_FormCaract[edt_liberodataora016].lMinL = 1;
	g_FormCaract[edt_liberodataora016].lMaxL = 4;
	g_FormCaract[edt_liberodataora016].bEndox = TRUE;
	g_FormCaract[edt_liberodataora016].bImageNT = FALSE;

	g_FormCaract[edt_liberodataora017].lID = EDT_LIBERODATAORA017;
	g_FormCaract[edt_liberodataora017].sDescrizione = theApp.m_sLabelDate[17];
	g_FormCaract[edt_liberodataora017].lMinA = 2;
	g_FormCaract[edt_liberodataora017].lMaxA = 2;
	g_FormCaract[edt_liberodataora017].lMinL = 1;
	g_FormCaract[edt_liberodataora017].lMaxL = 4;
	g_FormCaract[edt_liberodataora017].bEndox = TRUE;
	g_FormCaract[edt_liberodataora017].bImageNT = FALSE;

	g_FormCaract[edt_liberodataora018].lID = EDT_LIBERODATAORA018;
	g_FormCaract[edt_liberodataora018].sDescrizione = theApp.m_sLabelDate[18];
	g_FormCaract[edt_liberodataora018].lMinA = 2;
	g_FormCaract[edt_liberodataora018].lMaxA = 2;
	g_FormCaract[edt_liberodataora018].lMinL = 1;
	g_FormCaract[edt_liberodataora018].lMaxL = 4;
	g_FormCaract[edt_liberodataora018].bEndox = TRUE;
	g_FormCaract[edt_liberodataora018].bImageNT = FALSE;

	g_FormCaract[edt_liberodataora019].lID = EDT_LIBERODATAORA019;
	g_FormCaract[edt_liberodataora019].sDescrizione = theApp.m_sLabelDate[19];
	g_FormCaract[edt_liberodataora019].lMinA = 2;
	g_FormCaract[edt_liberodataora019].lMaxA = 2;
	g_FormCaract[edt_liberodataora019].lMinL = 1;
	g_FormCaract[edt_liberodataora019].lMaxL = 4;
	g_FormCaract[edt_liberodataora019].bEndox = TRUE;
	g_FormCaract[edt_liberodataora019].bImageNT = FALSE;

	g_FormCaract[btn_liberotastostampa000].lID = BTN_LIBEROTASTOSTAMPA000;
	g_FormCaract[btn_liberotastostampa000].sDescrizione = theApp.m_sLabelTastoStampa[0];
	g_FormCaract[btn_liberotastostampa000].lMinA = 2;
	g_FormCaract[btn_liberotastostampa000].lMaxA = 3;
	g_FormCaract[btn_liberotastostampa000].lMinL = 1;
	g_FormCaract[btn_liberotastostampa000].lMaxL = 8;
	g_FormCaract[btn_liberotastostampa000].bEndox = TRUE;
	g_FormCaract[btn_liberotastostampa000].bImageNT = FALSE;

	g_FormCaract[btn_liberotastostampa001].lID = BTN_LIBEROTASTOSTAMPA001;
	g_FormCaract[btn_liberotastostampa001].sDescrizione = theApp.m_sLabelTastoStampa[1];
	g_FormCaract[btn_liberotastostampa001].lMinA = 2;
	g_FormCaract[btn_liberotastostampa001].lMaxA = 3;
	g_FormCaract[btn_liberotastostampa001].lMinL = 1;
	g_FormCaract[btn_liberotastostampa001].lMaxL = 8;
	g_FormCaract[btn_liberotastostampa001].bEndox = TRUE;
	g_FormCaract[btn_liberotastostampa001].bImageNT = FALSE;

	g_FormCaract[btn_liberotastostampa002].lID = BTN_LIBEROTASTOSTAMPA002;
	g_FormCaract[btn_liberotastostampa002].sDescrizione = theApp.m_sLabelTastoStampa[2];
	g_FormCaract[btn_liberotastostampa002].lMinA = 2;
	g_FormCaract[btn_liberotastostampa002].lMaxA = 3;
	g_FormCaract[btn_liberotastostampa002].lMinL = 1;
	g_FormCaract[btn_liberotastostampa002].lMaxL = 8;
	g_FormCaract[btn_liberotastostampa002].bEndox = TRUE;
	g_FormCaract[btn_liberotastostampa002].bImageNT = FALSE;

	g_FormCaract[btn_liberotastostampa003].lID = BTN_LIBEROTASTOSTAMPA003;
	g_FormCaract[btn_liberotastostampa003].sDescrizione = theApp.m_sLabelTastoStampa[3];
	g_FormCaract[btn_liberotastostampa003].lMinA = 2;
	g_FormCaract[btn_liberotastostampa003].lMaxA = 3;
	g_FormCaract[btn_liberotastostampa003].lMinL = 1;
	g_FormCaract[btn_liberotastostampa003].lMaxL = 8;
	g_FormCaract[btn_liberotastostampa003].bEndox = TRUE;
	g_FormCaract[btn_liberotastostampa003].bImageNT = FALSE;

	g_FormCaract[btn_liberotastostampa004].lID = BTN_LIBEROTASTOSTAMPA004;
	g_FormCaract[btn_liberotastostampa004].sDescrizione = theApp.m_sLabelTastoStampa[4];
	g_FormCaract[btn_liberotastostampa004].lMinA = 2;
	g_FormCaract[btn_liberotastostampa004].lMaxA = 3;
	g_FormCaract[btn_liberotastostampa004].lMinL = 1;
	g_FormCaract[btn_liberotastostampa004].lMaxL = 8;
	g_FormCaract[btn_liberotastostampa004].bEndox = TRUE;
	g_FormCaract[btn_liberotastostampa004].bImageNT = FALSE;

	g_FormCaract[btn_liberotastostampa005].lID = BTN_LIBEROTASTOSTAMPA005;
	g_FormCaract[btn_liberotastostampa005].sDescrizione = theApp.m_sLabelTastoStampa[5];
	g_FormCaract[btn_liberotastostampa005].lMinA = 2;
	g_FormCaract[btn_liberotastostampa005].lMaxA = 3;
	g_FormCaract[btn_liberotastostampa005].lMinL = 1;
	g_FormCaract[btn_liberotastostampa005].lMaxL = 8;
	g_FormCaract[btn_liberotastostampa005].bEndox = TRUE;
	g_FormCaract[btn_liberotastostampa005].bImageNT = FALSE;

	g_FormCaract[btn_liberotastostampa006].lID = BTN_LIBEROTASTOSTAMPA006;
	g_FormCaract[btn_liberotastostampa006].sDescrizione = theApp.m_sLabelTastoStampa[6];
	g_FormCaract[btn_liberotastostampa006].lMinA = 2;
	g_FormCaract[btn_liberotastostampa006].lMaxA = 3;
	g_FormCaract[btn_liberotastostampa006].lMinL = 1;
	g_FormCaract[btn_liberotastostampa006].lMaxL = 8;
	g_FormCaract[btn_liberotastostampa006].bEndox = TRUE;
	g_FormCaract[btn_liberotastostampa006].bImageNT = FALSE;

	g_FormCaract[btn_liberotastostampa007].lID = BTN_LIBEROTASTOSTAMPA007;
	g_FormCaract[btn_liberotastostampa007].sDescrizione = theApp.m_sLabelTastoStampa[7];
	g_FormCaract[btn_liberotastostampa007].lMinA = 2;
	g_FormCaract[btn_liberotastostampa007].lMaxA = 3;
	g_FormCaract[btn_liberotastostampa007].lMinL = 1;
	g_FormCaract[btn_liberotastostampa007].lMaxL = 8;
	g_FormCaract[btn_liberotastostampa007].bEndox = TRUE;
	g_FormCaract[btn_liberotastostampa007].bImageNT = FALSE;

	g_FormCaract[btn_liberotastostampa008].lID = BTN_LIBEROTASTOSTAMPA008;
	g_FormCaract[btn_liberotastostampa008].sDescrizione = theApp.m_sLabelTastoStampa[8];
	g_FormCaract[btn_liberotastostampa008].lMinA = 2;
	g_FormCaract[btn_liberotastostampa008].lMaxA = 3;
	g_FormCaract[btn_liberotastostampa008].lMinL = 1;
	g_FormCaract[btn_liberotastostampa008].lMaxL = 8;
	g_FormCaract[btn_liberotastostampa008].bEndox = TRUE;
	g_FormCaract[btn_liberotastostampa008].bImageNT = FALSE;

	g_FormCaract[btn_liberotastostampa009].lID = BTN_LIBEROTASTOSTAMPA009;
	g_FormCaract[btn_liberotastostampa009].sDescrizione = theApp.m_sLabelTastoStampa[9];
	g_FormCaract[btn_liberotastostampa009].lMinA = 2;
	g_FormCaract[btn_liberotastostampa009].lMaxA = 3;
	g_FormCaract[btn_liberotastostampa009].lMinL = 1;
	g_FormCaract[btn_liberotastostampa009].lMaxL = 8;
	g_FormCaract[btn_liberotastostampa009].bEndox = TRUE;
	g_FormCaract[btn_liberotastostampa009].bImageNT = FALSE;

	g_FormCaract[btn_liberotastostampa010].lID = BTN_LIBEROTASTOSTAMPA010;
	g_FormCaract[btn_liberotastostampa010].sDescrizione = theApp.m_sLabelTastoStampa[10];
	g_FormCaract[btn_liberotastostampa010].lMinA = 2;
	g_FormCaract[btn_liberotastostampa010].lMaxA = 3;
	g_FormCaract[btn_liberotastostampa010].lMinL = 1;
	g_FormCaract[btn_liberotastostampa010].lMaxL = 8;
	g_FormCaract[btn_liberotastostampa010].bEndox = TRUE;
	g_FormCaract[btn_liberotastostampa010].bImageNT = FALSE;

	g_FormCaract[btn_liberotastostampa011].lID = BTN_LIBEROTASTOSTAMPA011;
	g_FormCaract[btn_liberotastostampa011].sDescrizione = theApp.m_sLabelTastoStampa[11];
	g_FormCaract[btn_liberotastostampa011].lMinA = 2;
	g_FormCaract[btn_liberotastostampa011].lMaxA = 3;
	g_FormCaract[btn_liberotastostampa011].lMinL = 1;
	g_FormCaract[btn_liberotastostampa011].lMaxL = 8;
	g_FormCaract[btn_liberotastostampa011].bEndox = TRUE;
	g_FormCaract[btn_liberotastostampa011].bImageNT = FALSE;

	g_FormCaract[btn_liberotastostampa012].lID = BTN_LIBEROTASTOSTAMPA012;
	g_FormCaract[btn_liberotastostampa012].sDescrizione = theApp.m_sLabelTastoStampa[12];
	g_FormCaract[btn_liberotastostampa012].lMinA = 2;
	g_FormCaract[btn_liberotastostampa012].lMaxA = 3;
	g_FormCaract[btn_liberotastostampa012].lMinL = 1;
	g_FormCaract[btn_liberotastostampa012].lMaxL = 8;
	g_FormCaract[btn_liberotastostampa012].bEndox = TRUE;
	g_FormCaract[btn_liberotastostampa012].bImageNT = FALSE;

	g_FormCaract[btn_liberotastostampa013].lID = BTN_LIBEROTASTOSTAMPA013;
	g_FormCaract[btn_liberotastostampa013].sDescrizione = theApp.m_sLabelTastoStampa[13];
	g_FormCaract[btn_liberotastostampa013].lMinA = 2;
	g_FormCaract[btn_liberotastostampa013].lMaxA = 3;
	g_FormCaract[btn_liberotastostampa013].lMinL = 1;
	g_FormCaract[btn_liberotastostampa013].lMaxL = 8;
	g_FormCaract[btn_liberotastostampa013].bEndox = TRUE;
	g_FormCaract[btn_liberotastostampa013].bImageNT = FALSE;

	g_FormCaract[btn_liberotastostampa014].lID = BTN_LIBEROTASTOSTAMPA014;
	g_FormCaract[btn_liberotastostampa014].sDescrizione = theApp.m_sLabelTastoStampa[14];
	g_FormCaract[btn_liberotastostampa014].lMinA = 2;
	g_FormCaract[btn_liberotastostampa014].lMaxA = 3;
	g_FormCaract[btn_liberotastostampa014].lMinL = 1;
	g_FormCaract[btn_liberotastostampa014].lMaxL = 8;
	g_FormCaract[btn_liberotastostampa014].bEndox = TRUE;
	g_FormCaract[btn_liberotastostampa014].bImageNT = FALSE;

	g_FormCaract[btn_liberotastostampa015].lID = BTN_LIBEROTASTOSTAMPA015;
	g_FormCaract[btn_liberotastostampa015].sDescrizione = theApp.m_sLabelTastoStampa[15];
	g_FormCaract[btn_liberotastostampa015].lMinA = 2;
	g_FormCaract[btn_liberotastostampa015].lMaxA = 3;
	g_FormCaract[btn_liberotastostampa015].lMinL = 1;
	g_FormCaract[btn_liberotastostampa015].lMaxL = 8;
	g_FormCaract[btn_liberotastostampa015].bEndox = TRUE;
	g_FormCaract[btn_liberotastostampa015].bImageNT = FALSE;

	g_FormCaract[btn_liberotastostampa016].lID = BTN_LIBEROTASTOSTAMPA016;
	g_FormCaract[btn_liberotastostampa016].sDescrizione = theApp.m_sLabelTastoStampa[16];
	g_FormCaract[btn_liberotastostampa016].lMinA = 2;
	g_FormCaract[btn_liberotastostampa016].lMaxA = 3;
	g_FormCaract[btn_liberotastostampa016].lMinL = 1;
	g_FormCaract[btn_liberotastostampa016].lMaxL = 8;
	g_FormCaract[btn_liberotastostampa016].bEndox = TRUE;
	g_FormCaract[btn_liberotastostampa016].bImageNT = FALSE;

	g_FormCaract[btn_liberotastostampa017].lID = BTN_LIBEROTASTOSTAMPA017;
	g_FormCaract[btn_liberotastostampa017].sDescrizione = theApp.m_sLabelTastoStampa[17];
	g_FormCaract[btn_liberotastostampa017].lMinA = 2;
	g_FormCaract[btn_liberotastostampa017].lMaxA = 3;
	g_FormCaract[btn_liberotastostampa017].lMinL = 1;
	g_FormCaract[btn_liberotastostampa017].lMaxL = 8;
	g_FormCaract[btn_liberotastostampa017].bEndox = TRUE;
	g_FormCaract[btn_liberotastostampa017].bImageNT = FALSE;

	g_FormCaract[btn_liberotastostampa018].lID = BTN_LIBEROTASTOSTAMPA018;
	g_FormCaract[btn_liberotastostampa018].sDescrizione = theApp.m_sLabelTastoStampa[18];
	g_FormCaract[btn_liberotastostampa018].lMinA = 2;
	g_FormCaract[btn_liberotastostampa018].lMaxA = 3;
	g_FormCaract[btn_liberotastostampa018].lMinL = 1;
	g_FormCaract[btn_liberotastostampa018].lMaxL = 8;
	g_FormCaract[btn_liberotastostampa018].bEndox = TRUE;
	g_FormCaract[btn_liberotastostampa018].bImageNT = FALSE;

	g_FormCaract[btn_liberotastostampa019].lID = BTN_LIBEROTASTOSTAMPA019;
	g_FormCaract[btn_liberotastostampa019].sDescrizione = theApp.m_sLabelTastoStampa[19];
	g_FormCaract[btn_liberotastostampa019].lMinA = 2;
	g_FormCaract[btn_liberotastostampa019].lMaxA = 3;
	g_FormCaract[btn_liberotastostampa019].lMinL = 1;
	g_FormCaract[btn_liberotastostampa019].lMaxL = 8;
	g_FormCaract[btn_liberotastostampa019].bEndox = TRUE;
	g_FormCaract[btn_liberotastostampa019].bImageNT = FALSE;

	g_FormCaract[btn_liberotastobrowser000].lID = BTN_LIBEROTASTOBROWSER000;
	g_FormCaract[btn_liberotastobrowser000].sDescrizione = theApp.m_sLabelTastoBrowser[0];
	g_FormCaract[btn_liberotastobrowser000].lMinA = 2;
	g_FormCaract[btn_liberotastobrowser000].lMaxA = 3;
	g_FormCaract[btn_liberotastobrowser000].lMinL = 1;
	g_FormCaract[btn_liberotastobrowser000].lMaxL = 8;
	g_FormCaract[btn_liberotastobrowser000].bEndox = TRUE;
	g_FormCaract[btn_liberotastobrowser000].bImageNT = FALSE;

	g_FormCaract[btn_liberotastobrowser001].lID = BTN_LIBEROTASTOBROWSER001;
	g_FormCaract[btn_liberotastobrowser001].sDescrizione = theApp.m_sLabelTastoBrowser[1];
	g_FormCaract[btn_liberotastobrowser001].lMinA = 2;
	g_FormCaract[btn_liberotastobrowser001].lMaxA = 3;
	g_FormCaract[btn_liberotastobrowser001].lMinL = 1;
	g_FormCaract[btn_liberotastobrowser001].lMaxL = 8;
	g_FormCaract[btn_liberotastobrowser001].bEndox = TRUE;
	g_FormCaract[btn_liberotastobrowser001].bImageNT = FALSE;

	g_FormCaract[btn_liberotastobrowser002].lID = BTN_LIBEROTASTOBROWSER002;
	g_FormCaract[btn_liberotastobrowser002].sDescrizione = theApp.m_sLabelTastoBrowser[2];
	g_FormCaract[btn_liberotastobrowser002].lMinA = 2;
	g_FormCaract[btn_liberotastobrowser002].lMaxA = 3;
	g_FormCaract[btn_liberotastobrowser002].lMinL = 1;
	g_FormCaract[btn_liberotastobrowser002].lMaxL = 8;
	g_FormCaract[btn_liberotastobrowser002].bEndox = TRUE;
	g_FormCaract[btn_liberotastobrowser002].bImageNT = FALSE;

	g_FormCaract[btn_liberotastobrowser003].lID = BTN_LIBEROTASTOBROWSER003;
	g_FormCaract[btn_liberotastobrowser003].sDescrizione = theApp.m_sLabelTastoBrowser[3];
	g_FormCaract[btn_liberotastobrowser003].lMinA = 2;
	g_FormCaract[btn_liberotastobrowser003].lMaxA = 3;
	g_FormCaract[btn_liberotastobrowser003].lMinL = 1;
	g_FormCaract[btn_liberotastobrowser003].lMaxL = 8;
	g_FormCaract[btn_liberotastobrowser003].bEndox = TRUE;
	g_FormCaract[btn_liberotastobrowser003].bImageNT = FALSE;

	g_FormCaract[btn_liberotastobrowser004].lID = BTN_LIBEROTASTOBROWSER004;
	g_FormCaract[btn_liberotastobrowser004].sDescrizione = theApp.m_sLabelTastoBrowser[4];
	g_FormCaract[btn_liberotastobrowser004].lMinA = 2;
	g_FormCaract[btn_liberotastobrowser004].lMaxA = 3;
	g_FormCaract[btn_liberotastobrowser004].lMinL = 1;
	g_FormCaract[btn_liberotastobrowser004].lMaxL = 8;
	g_FormCaract[btn_liberotastobrowser004].bEndox = TRUE;
	g_FormCaract[btn_liberotastobrowser004].bImageNT = FALSE;

	g_FormCaract[btn_liberotastobrowser005].lID = BTN_LIBEROTASTOBROWSER005;
	g_FormCaract[btn_liberotastobrowser005].sDescrizione = theApp.m_sLabelTastoBrowser[5];
	g_FormCaract[btn_liberotastobrowser005].lMinA = 2;
	g_FormCaract[btn_liberotastobrowser005].lMaxA = 3;
	g_FormCaract[btn_liberotastobrowser005].lMinL = 1;
	g_FormCaract[btn_liberotastobrowser005].lMaxL = 8;
	g_FormCaract[btn_liberotastobrowser005].bEndox = TRUE;
	g_FormCaract[btn_liberotastobrowser005].bImageNT = FALSE;

	g_FormCaract[btn_liberotastobrowser006].lID = BTN_LIBEROTASTOBROWSER006;
	g_FormCaract[btn_liberotastobrowser006].sDescrizione = theApp.m_sLabelTastoBrowser[6];
	g_FormCaract[btn_liberotastobrowser006].lMinA = 2;
	g_FormCaract[btn_liberotastobrowser006].lMaxA = 3;
	g_FormCaract[btn_liberotastobrowser006].lMinL = 1;
	g_FormCaract[btn_liberotastobrowser006].lMaxL = 8;
	g_FormCaract[btn_liberotastobrowser006].bEndox = TRUE;
	g_FormCaract[btn_liberotastobrowser006].bImageNT = FALSE;

	g_FormCaract[btn_liberotastobrowser007].lID = BTN_LIBEROTASTOBROWSER007;
	g_FormCaract[btn_liberotastobrowser007].sDescrizione = theApp.m_sLabelTastoBrowser[7];
	g_FormCaract[btn_liberotastobrowser007].lMinA = 2;
	g_FormCaract[btn_liberotastobrowser007].lMaxA = 3;
	g_FormCaract[btn_liberotastobrowser007].lMinL = 1;
	g_FormCaract[btn_liberotastobrowser007].lMaxL = 8;
	g_FormCaract[btn_liberotastobrowser007].bEndox = TRUE;
	g_FormCaract[btn_liberotastobrowser007].bImageNT = FALSE;

	g_FormCaract[btn_liberotastobrowser008].lID = BTN_LIBEROTASTOBROWSER008;
	g_FormCaract[btn_liberotastobrowser008].sDescrizione = theApp.m_sLabelTastoBrowser[8];
	g_FormCaract[btn_liberotastobrowser008].lMinA = 2;
	g_FormCaract[btn_liberotastobrowser008].lMaxA = 3;
	g_FormCaract[btn_liberotastobrowser008].lMinL = 1;
	g_FormCaract[btn_liberotastobrowser008].lMaxL = 8;
	g_FormCaract[btn_liberotastobrowser008].bEndox = TRUE;
	g_FormCaract[btn_liberotastobrowser008].bImageNT = FALSE;

	g_FormCaract[btn_liberotastobrowser009].lID = BTN_LIBEROTASTOBROWSER009;
	g_FormCaract[btn_liberotastobrowser009].sDescrizione = theApp.m_sLabelTastoBrowser[9];
	g_FormCaract[btn_liberotastobrowser009].lMinA = 2;
	g_FormCaract[btn_liberotastobrowser009].lMaxA = 3;
	g_FormCaract[btn_liberotastobrowser009].lMinL = 1;
	g_FormCaract[btn_liberotastobrowser009].lMaxL = 8;
	g_FormCaract[btn_liberotastobrowser009].bEndox = TRUE;
	g_FormCaract[btn_liberotastobrowser009].bImageNT = FALSE;

	g_FormCaract[btn_liberotastobrowser010].lID = BTN_LIBEROTASTOBROWSER010;
	g_FormCaract[btn_liberotastobrowser010].sDescrizione = theApp.m_sLabelTastoBrowser[10];
	g_FormCaract[btn_liberotastobrowser010].lMinA = 2;
	g_FormCaract[btn_liberotastobrowser010].lMaxA = 3;
	g_FormCaract[btn_liberotastobrowser010].lMinL = 1;
	g_FormCaract[btn_liberotastobrowser010].lMaxL = 8;
	g_FormCaract[btn_liberotastobrowser010].bEndox = TRUE;
	g_FormCaract[btn_liberotastobrowser010].bImageNT = FALSE;

	g_FormCaract[btn_liberotastobrowser011].lID = BTN_LIBEROTASTOBROWSER011;
	g_FormCaract[btn_liberotastobrowser011].sDescrizione = theApp.m_sLabelTastoBrowser[11];
	g_FormCaract[btn_liberotastobrowser011].lMinA = 2;
	g_FormCaract[btn_liberotastobrowser011].lMaxA = 3;
	g_FormCaract[btn_liberotastobrowser011].lMinL = 1;
	g_FormCaract[btn_liberotastobrowser011].lMaxL = 8;
	g_FormCaract[btn_liberotastobrowser011].bEndox = TRUE;
	g_FormCaract[btn_liberotastobrowser011].bImageNT = FALSE;

	g_FormCaract[btn_liberotastobrowser012].lID = BTN_LIBEROTASTOBROWSER012;
	g_FormCaract[btn_liberotastobrowser012].sDescrizione = theApp.m_sLabelTastoBrowser[12];
	g_FormCaract[btn_liberotastobrowser012].lMinA = 2;
	g_FormCaract[btn_liberotastobrowser012].lMaxA = 3;
	g_FormCaract[btn_liberotastobrowser012].lMinL = 1;
	g_FormCaract[btn_liberotastobrowser012].lMaxL = 8;
	g_FormCaract[btn_liberotastobrowser012].bEndox = TRUE;
	g_FormCaract[btn_liberotastobrowser012].bImageNT = FALSE;

	g_FormCaract[btn_liberotastobrowser013].lID = BTN_LIBEROTASTOBROWSER013;
	g_FormCaract[btn_liberotastobrowser013].sDescrizione = theApp.m_sLabelTastoBrowser[13];
	g_FormCaract[btn_liberotastobrowser013].lMinA = 2;
	g_FormCaract[btn_liberotastobrowser013].lMaxA = 3;
	g_FormCaract[btn_liberotastobrowser013].lMinL = 1;
	g_FormCaract[btn_liberotastobrowser013].lMaxL = 8;
	g_FormCaract[btn_liberotastobrowser013].bEndox = TRUE;
	g_FormCaract[btn_liberotastobrowser013].bImageNT = FALSE;

	g_FormCaract[btn_liberotastobrowser014].lID = BTN_LIBEROTASTOBROWSER014;
	g_FormCaract[btn_liberotastobrowser014].sDescrizione = theApp.m_sLabelTastoBrowser[14];
	g_FormCaract[btn_liberotastobrowser014].lMinA = 2;
	g_FormCaract[btn_liberotastobrowser014].lMaxA = 3;
	g_FormCaract[btn_liberotastobrowser014].lMinL = 1;
	g_FormCaract[btn_liberotastobrowser014].lMaxL = 8;
	g_FormCaract[btn_liberotastobrowser014].bEndox = TRUE;
	g_FormCaract[btn_liberotastobrowser014].bImageNT = FALSE;

	g_FormCaract[btn_liberotastobrowser015].lID = BTN_LIBEROTASTOBROWSER015;
	g_FormCaract[btn_liberotastobrowser015].sDescrizione = theApp.m_sLabelTastoBrowser[15];
	g_FormCaract[btn_liberotastobrowser015].lMinA = 2;
	g_FormCaract[btn_liberotastobrowser015].lMaxA = 3;
	g_FormCaract[btn_liberotastobrowser015].lMinL = 1;
	g_FormCaract[btn_liberotastobrowser015].lMaxL = 8;
	g_FormCaract[btn_liberotastobrowser015].bEndox = TRUE;
	g_FormCaract[btn_liberotastobrowser015].bImageNT = FALSE;

	g_FormCaract[btn_liberotastobrowser016].lID = BTN_LIBEROTASTOBROWSER016;
	g_FormCaract[btn_liberotastobrowser016].sDescrizione = theApp.m_sLabelTastoBrowser[16];
	g_FormCaract[btn_liberotastobrowser016].lMinA = 2;
	g_FormCaract[btn_liberotastobrowser016].lMaxA = 3;
	g_FormCaract[btn_liberotastobrowser016].lMinL = 1;
	g_FormCaract[btn_liberotastobrowser016].lMaxL = 8;
	g_FormCaract[btn_liberotastobrowser016].bEndox = TRUE;
	g_FormCaract[btn_liberotastobrowser016].bImageNT = FALSE;

	g_FormCaract[btn_liberotastobrowser017].lID = BTN_LIBEROTASTOBROWSER017;
	g_FormCaract[btn_liberotastobrowser017].sDescrizione = theApp.m_sLabelTastoBrowser[17];
	g_FormCaract[btn_liberotastobrowser017].lMinA = 2;
	g_FormCaract[btn_liberotastobrowser017].lMaxA = 3;
	g_FormCaract[btn_liberotastobrowser017].lMinL = 1;
	g_FormCaract[btn_liberotastobrowser017].lMaxL = 8;
	g_FormCaract[btn_liberotastobrowser017].bEndox = TRUE;
	g_FormCaract[btn_liberotastobrowser017].bImageNT = FALSE;

	g_FormCaract[btn_liberotastobrowser018].lID = BTN_LIBEROTASTOBROWSER018;
	g_FormCaract[btn_liberotastobrowser018].sDescrizione = theApp.m_sLabelTastoBrowser[18];
	g_FormCaract[btn_liberotastobrowser018].lMinA = 2;
	g_FormCaract[btn_liberotastobrowser018].lMaxA = 3;
	g_FormCaract[btn_liberotastobrowser018].lMinL = 1;
	g_FormCaract[btn_liberotastobrowser018].lMaxL = 8;
	g_FormCaract[btn_liberotastobrowser018].bEndox = TRUE;
	g_FormCaract[btn_liberotastobrowser018].bImageNT = FALSE;

	g_FormCaract[btn_liberotastobrowser019].lID = BTN_LIBEROTASTOBROWSER019;
	g_FormCaract[btn_liberotastobrowser019].sDescrizione = theApp.m_sLabelTastoBrowser[19];
	g_FormCaract[btn_liberotastobrowser019].lMinA = 2;
	g_FormCaract[btn_liberotastobrowser019].lMaxA = 3;
	g_FormCaract[btn_liberotastobrowser019].lMinL = 1;
	g_FormCaract[btn_liberotastobrowser019].lMaxL = 8;
	g_FormCaract[btn_liberotastobrowser019].bEndox = TRUE;
	g_FormCaract[btn_liberotastobrowser019].bImageNT = FALSE;

	g_FormCaract[btn_liberotastoeseguibile000].lID = BTN_LIBEROTASTOESEGUIBILE000;
	g_FormCaract[btn_liberotastoeseguibile000].sDescrizione = theApp.m_sLabelTastoEseguibile[0];
	g_FormCaract[btn_liberotastoeseguibile000].lMinA = 2;
	g_FormCaract[btn_liberotastoeseguibile000].lMaxA = 3;
	g_FormCaract[btn_liberotastoeseguibile000].lMinL = 1;
	g_FormCaract[btn_liberotastoeseguibile000].lMaxL = 8;
	g_FormCaract[btn_liberotastoeseguibile000].bEndox = TRUE;
	g_FormCaract[btn_liberotastoeseguibile000].bImageNT = FALSE;

	g_FormCaract[btn_liberotastoeseguibile001].lID = BTN_LIBEROTASTOESEGUIBILE001;
	g_FormCaract[btn_liberotastoeseguibile001].sDescrizione = theApp.m_sLabelTastoEseguibile[1];
	g_FormCaract[btn_liberotastoeseguibile001].lMinA = 2;
	g_FormCaract[btn_liberotastoeseguibile001].lMaxA = 3;
	g_FormCaract[btn_liberotastoeseguibile001].lMinL = 1;
	g_FormCaract[btn_liberotastoeseguibile001].lMaxL = 8;
	g_FormCaract[btn_liberotastoeseguibile001].bEndox = TRUE;
	g_FormCaract[btn_liberotastoeseguibile001].bImageNT = FALSE;

	g_FormCaract[btn_liberotastoeseguibile002].lID = BTN_LIBEROTASTOESEGUIBILE002;
	g_FormCaract[btn_liberotastoeseguibile002].sDescrizione = theApp.m_sLabelTastoEseguibile[2];
	g_FormCaract[btn_liberotastoeseguibile002].lMinA = 2;
	g_FormCaract[btn_liberotastoeseguibile002].lMaxA = 3;
	g_FormCaract[btn_liberotastoeseguibile002].lMinL = 1;
	g_FormCaract[btn_liberotastoeseguibile002].lMaxL = 8;
	g_FormCaract[btn_liberotastoeseguibile002].bEndox = TRUE;
	g_FormCaract[btn_liberotastoeseguibile002].bImageNT = FALSE;

	g_FormCaract[btn_liberotastoeseguibile003].lID = BTN_LIBEROTASTOESEGUIBILE003;
	g_FormCaract[btn_liberotastoeseguibile003].sDescrizione = theApp.m_sLabelTastoEseguibile[3];
	g_FormCaract[btn_liberotastoeseguibile003].lMinA = 2;
	g_FormCaract[btn_liberotastoeseguibile003].lMaxA = 3;
	g_FormCaract[btn_liberotastoeseguibile003].lMinL = 1;
	g_FormCaract[btn_liberotastoeseguibile003].lMaxL = 8;
	g_FormCaract[btn_liberotastoeseguibile003].bEndox = TRUE;
	g_FormCaract[btn_liberotastoeseguibile003].bImageNT = FALSE;

	g_FormCaract[btn_liberotastoeseguibile004].lID = BTN_LIBEROTASTOESEGUIBILE004;
	g_FormCaract[btn_liberotastoeseguibile004].sDescrizione = theApp.m_sLabelTastoEseguibile[4];
	g_FormCaract[btn_liberotastoeseguibile004].lMinA = 2;
	g_FormCaract[btn_liberotastoeseguibile004].lMaxA = 3;
	g_FormCaract[btn_liberotastoeseguibile004].lMinL = 1;
	g_FormCaract[btn_liberotastoeseguibile004].lMaxL = 8;
	g_FormCaract[btn_liberotastoeseguibile004].bEndox = TRUE;
	g_FormCaract[btn_liberotastoeseguibile004].bImageNT = FALSE;

	g_FormCaract[btn_liberotastoeseguibile005].lID = BTN_LIBEROTASTOESEGUIBILE005;
	g_FormCaract[btn_liberotastoeseguibile005].sDescrizione = theApp.m_sLabelTastoEseguibile[5];
	g_FormCaract[btn_liberotastoeseguibile005].lMinA = 2;
	g_FormCaract[btn_liberotastoeseguibile005].lMaxA = 3;
	g_FormCaract[btn_liberotastoeseguibile005].lMinL = 1;
	g_FormCaract[btn_liberotastoeseguibile005].lMaxL = 8;
	g_FormCaract[btn_liberotastoeseguibile005].bEndox = TRUE;
	g_FormCaract[btn_liberotastoeseguibile005].bImageNT = FALSE;

	g_FormCaract[btn_liberotastoeseguibile006].lID = BTN_LIBEROTASTOESEGUIBILE006;
	g_FormCaract[btn_liberotastoeseguibile006].sDescrizione = theApp.m_sLabelTastoEseguibile[6];
	g_FormCaract[btn_liberotastoeseguibile006].lMinA = 2;
	g_FormCaract[btn_liberotastoeseguibile006].lMaxA = 3;
	g_FormCaract[btn_liberotastoeseguibile006].lMinL = 1;
	g_FormCaract[btn_liberotastoeseguibile006].lMaxL = 8;
	g_FormCaract[btn_liberotastoeseguibile006].bEndox = TRUE;
	g_FormCaract[btn_liberotastoeseguibile006].bImageNT = FALSE;

	g_FormCaract[btn_liberotastoeseguibile007].lID = BTN_LIBEROTASTOESEGUIBILE007;
	g_FormCaract[btn_liberotastoeseguibile007].sDescrizione = theApp.m_sLabelTastoEseguibile[7];
	g_FormCaract[btn_liberotastoeseguibile007].lMinA = 2;
	g_FormCaract[btn_liberotastoeseguibile007].lMaxA = 3;
	g_FormCaract[btn_liberotastoeseguibile007].lMinL = 1;
	g_FormCaract[btn_liberotastoeseguibile007].lMaxL = 8;
	g_FormCaract[btn_liberotastoeseguibile007].bEndox = TRUE;
	g_FormCaract[btn_liberotastoeseguibile007].bImageNT = FALSE;

	g_FormCaract[btn_liberotastoeseguibile008].lID = BTN_LIBEROTASTOESEGUIBILE008;
	g_FormCaract[btn_liberotastoeseguibile008].sDescrizione = theApp.m_sLabelTastoEseguibile[8];
	g_FormCaract[btn_liberotastoeseguibile008].lMinA = 2;
	g_FormCaract[btn_liberotastoeseguibile008].lMaxA = 3;
	g_FormCaract[btn_liberotastoeseguibile008].lMinL = 1;
	g_FormCaract[btn_liberotastoeseguibile008].lMaxL = 8;
	g_FormCaract[btn_liberotastoeseguibile008].bEndox = TRUE;
	g_FormCaract[btn_liberotastoeseguibile008].bImageNT = FALSE;

	g_FormCaract[btn_liberotastoeseguibile009].lID = BTN_LIBEROTASTOESEGUIBILE009;
	g_FormCaract[btn_liberotastoeseguibile009].sDescrizione = theApp.m_sLabelTastoEseguibile[9];
	g_FormCaract[btn_liberotastoeseguibile009].lMinA = 2;
	g_FormCaract[btn_liberotastoeseguibile009].lMaxA = 3;
	g_FormCaract[btn_liberotastoeseguibile009].lMinL = 1;
	g_FormCaract[btn_liberotastoeseguibile009].lMaxL = 8;
	g_FormCaract[btn_liberotastoeseguibile009].bEndox = TRUE;
	g_FormCaract[btn_liberotastoeseguibile009].bImageNT = FALSE;

	g_FormCaract[btn_liberotastoeseguibile010].lID = BTN_LIBEROTASTOESEGUIBILE010;
	g_FormCaract[btn_liberotastoeseguibile010].sDescrizione = theApp.m_sLabelTastoEseguibile[10];
	g_FormCaract[btn_liberotastoeseguibile010].lMinA = 2;
	g_FormCaract[btn_liberotastoeseguibile010].lMaxA = 3;
	g_FormCaract[btn_liberotastoeseguibile010].lMinL = 1;
	g_FormCaract[btn_liberotastoeseguibile010].lMaxL = 8;
	g_FormCaract[btn_liberotastoeseguibile010].bEndox = TRUE;
	g_FormCaract[btn_liberotastoeseguibile010].bImageNT = FALSE;

	g_FormCaract[btn_liberotastoeseguibile011].lID = BTN_LIBEROTASTOESEGUIBILE011;
	g_FormCaract[btn_liberotastoeseguibile011].sDescrizione = theApp.m_sLabelTastoEseguibile[11];
	g_FormCaract[btn_liberotastoeseguibile011].lMinA = 2;
	g_FormCaract[btn_liberotastoeseguibile011].lMaxA = 3;
	g_FormCaract[btn_liberotastoeseguibile011].lMinL = 1;
	g_FormCaract[btn_liberotastoeseguibile011].lMaxL = 8;
	g_FormCaract[btn_liberotastoeseguibile011].bEndox = TRUE;
	g_FormCaract[btn_liberotastoeseguibile011].bImageNT = FALSE;

	g_FormCaract[btn_liberotastoeseguibile012].lID = BTN_LIBEROTASTOESEGUIBILE012;
	g_FormCaract[btn_liberotastoeseguibile012].sDescrizione = theApp.m_sLabelTastoEseguibile[12];
	g_FormCaract[btn_liberotastoeseguibile012].lMinA = 2;
	g_FormCaract[btn_liberotastoeseguibile012].lMaxA = 3;
	g_FormCaract[btn_liberotastoeseguibile012].lMinL = 1;
	g_FormCaract[btn_liberotastoeseguibile012].lMaxL = 8;
	g_FormCaract[btn_liberotastoeseguibile012].bEndox = TRUE;
	g_FormCaract[btn_liberotastoeseguibile012].bImageNT = FALSE;

	g_FormCaract[btn_liberotastoeseguibile013].lID = BTN_LIBEROTASTOESEGUIBILE013;
	g_FormCaract[btn_liberotastoeseguibile013].sDescrizione = theApp.m_sLabelTastoEseguibile[13];
	g_FormCaract[btn_liberotastoeseguibile013].lMinA = 2;
	g_FormCaract[btn_liberotastoeseguibile013].lMaxA = 3;
	g_FormCaract[btn_liberotastoeseguibile013].lMinL = 1;
	g_FormCaract[btn_liberotastoeseguibile013].lMaxL = 8;
	g_FormCaract[btn_liberotastoeseguibile013].bEndox = TRUE;
	g_FormCaract[btn_liberotastoeseguibile013].bImageNT = FALSE;

	g_FormCaract[btn_liberotastoeseguibile014].lID = BTN_LIBEROTASTOESEGUIBILE014;
	g_FormCaract[btn_liberotastoeseguibile014].sDescrizione = theApp.m_sLabelTastoEseguibile[14];
	g_FormCaract[btn_liberotastoeseguibile014].lMinA = 2;
	g_FormCaract[btn_liberotastoeseguibile014].lMaxA = 3;
	g_FormCaract[btn_liberotastoeseguibile014].lMinL = 1;
	g_FormCaract[btn_liberotastoeseguibile014].lMaxL = 8;
	g_FormCaract[btn_liberotastoeseguibile014].bEndox = TRUE;
	g_FormCaract[btn_liberotastoeseguibile014].bImageNT = FALSE;

	g_FormCaract[btn_liberotastoeseguibile015].lID = BTN_LIBEROTASTOESEGUIBILE015;
	g_FormCaract[btn_liberotastoeseguibile015].sDescrizione = theApp.m_sLabelTastoEseguibile[15];
	g_FormCaract[btn_liberotastoeseguibile015].lMinA = 2;
	g_FormCaract[btn_liberotastoeseguibile015].lMaxA = 3;
	g_FormCaract[btn_liberotastoeseguibile015].lMinL = 1;
	g_FormCaract[btn_liberotastoeseguibile015].lMaxL = 8;
	g_FormCaract[btn_liberotastoeseguibile015].bEndox = TRUE;
	g_FormCaract[btn_liberotastoeseguibile015].bImageNT = FALSE;

	g_FormCaract[btn_liberotastoeseguibile016].lID = BTN_LIBEROTASTOESEGUIBILE016;
	g_FormCaract[btn_liberotastoeseguibile016].sDescrizione = theApp.m_sLabelTastoEseguibile[16];
	g_FormCaract[btn_liberotastoeseguibile016].lMinA = 2;
	g_FormCaract[btn_liberotastoeseguibile016].lMaxA = 3;
	g_FormCaract[btn_liberotastoeseguibile016].lMinL = 1;
	g_FormCaract[btn_liberotastoeseguibile016].lMaxL = 8;
	g_FormCaract[btn_liberotastoeseguibile016].bEndox = TRUE;
	g_FormCaract[btn_liberotastoeseguibile016].bImageNT = FALSE;

	g_FormCaract[btn_liberotastoeseguibile017].lID = BTN_LIBEROTASTOESEGUIBILE017;
	g_FormCaract[btn_liberotastoeseguibile017].sDescrizione = theApp.m_sLabelTastoEseguibile[17];
	g_FormCaract[btn_liberotastoeseguibile017].lMinA = 2;
	g_FormCaract[btn_liberotastoeseguibile017].lMaxA = 3;
	g_FormCaract[btn_liberotastoeseguibile017].lMinL = 1;
	g_FormCaract[btn_liberotastoeseguibile017].lMaxL = 8;
	g_FormCaract[btn_liberotastoeseguibile017].bEndox = TRUE;
	g_FormCaract[btn_liberotastoeseguibile017].bImageNT = FALSE;

	g_FormCaract[btn_liberotastoeseguibile018].lID = BTN_LIBEROTASTOESEGUIBILE018;
	g_FormCaract[btn_liberotastoeseguibile018].sDescrizione = theApp.m_sLabelTastoEseguibile[18];
	g_FormCaract[btn_liberotastoeseguibile018].lMinA = 2;
	g_FormCaract[btn_liberotastoeseguibile018].lMaxA = 3;
	g_FormCaract[btn_liberotastoeseguibile018].lMinL = 1;
	g_FormCaract[btn_liberotastoeseguibile018].lMaxL = 8;
	g_FormCaract[btn_liberotastoeseguibile018].bEndox = TRUE;
	g_FormCaract[btn_liberotastoeseguibile018].bImageNT = FALSE;

	g_FormCaract[btn_liberotastoeseguibile019].lID = BTN_LIBEROTASTOESEGUIBILE019;
	g_FormCaract[btn_liberotastoeseguibile019].sDescrizione = theApp.m_sLabelTastoEseguibile[19];
	g_FormCaract[btn_liberotastoeseguibile019].lMinA = 2;
	g_FormCaract[btn_liberotastoeseguibile019].lMaxA = 3;
	g_FormCaract[btn_liberotastoeseguibile019].lMinL = 1;
	g_FormCaract[btn_liberotastoeseguibile019].lMaxL = 8;
	g_FormCaract[btn_liberotastoeseguibile019].bEndox = TRUE;
	g_FormCaract[btn_liberotastoeseguibile019].bImageNT = FALSE;

	g_FormCaract[edt_integrazioni].lID = EDT_INTEGRAZIONI;
	g_FormCaract[edt_integrazioni].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_21);
	g_FormCaract[edt_integrazioni].lMinA = 2;
	g_FormCaract[edt_integrazioni].lMaxA = 26;
	g_FormCaract[edt_integrazioni].lMinL = 1;
	g_FormCaract[edt_integrazioni].lMaxL = 8;
	g_FormCaract[edt_integrazioni].bEndox = TRUE;
	g_FormCaract[edt_integrazioni].bImageNT = FALSE;

	g_FormCaract[sub_monitoraggio_oriz].lID = SUB_MONITORAGGIO_ORIZ;
	g_FormCaract[sub_monitoraggio_oriz].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_92);
	g_FormCaract[sub_monitoraggio_oriz].lMinA = 4;
	g_FormCaract[sub_monitoraggio_oriz].lMaxA = 26;
	g_FormCaract[sub_monitoraggio_oriz].lMinL = 2;
	g_FormCaract[sub_monitoraggio_oriz].lMaxL = 16;
	g_FormCaract[sub_monitoraggio_oriz].bEndox = TRUE;
	g_FormCaract[sub_monitoraggio_oriz].bImageNT = FALSE;

	g_FormCaract[sub_monitoraggio_vert].lID = SUB_MONITORAGGIO_VERT;
	g_FormCaract[sub_monitoraggio_vert].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_318);
	g_FormCaract[sub_monitoraggio_vert].lMinA = 4;
	g_FormCaract[sub_monitoraggio_vert].lMaxA = 26;
	g_FormCaract[sub_monitoraggio_vert].lMinL = 2;
	g_FormCaract[sub_monitoraggio_vert].lMaxL = 16;
	g_FormCaract[sub_monitoraggio_vert].bEndox = TRUE;
	g_FormCaract[sub_monitoraggio_vert].bImageNT = FALSE;

	g_FormCaract[edt_anestesista].lID = EDT_ANESTESISTA;
	g_FormCaract[edt_anestesista].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_77);
	g_FormCaract[edt_anestesista].lMinA = 2;
	g_FormCaract[edt_anestesista].lMaxA = 2;
	g_FormCaract[edt_anestesista].lMinL = 1;
	g_FormCaract[edt_anestesista].lMaxL = 4;
	g_FormCaract[edt_anestesista].bEndox = TRUE;
	g_FormCaract[edt_anestesista].bImageNT = FALSE;

	g_FormCaract[sub_rao].lID = SUB_RAO;
	g_FormCaract[sub_rao].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_93);
	g_FormCaract[sub_rao].lMinA = 4;
	g_FormCaract[sub_rao].lMaxA = 6;
	g_FormCaract[sub_rao].lMinL = 1;
	g_FormCaract[sub_rao].lMaxL = 8;
	g_FormCaract[sub_rao].bEndox = TRUE;
	g_FormCaract[sub_rao].bImageNT = FALSE;

	g_FormCaract[sub_consensoinformato].lID = SUB_CONSENSOINFORMATO;
	g_FormCaract[sub_consensoinformato].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_94);
	g_FormCaract[sub_consensoinformato].lMinA = 5;
	g_FormCaract[sub_consensoinformato].lMaxA = 6;
	g_FormCaract[sub_consensoinformato].lMinL = 1;
	g_FormCaract[sub_consensoinformato].lMaxL = 8;
	g_FormCaract[sub_consensoinformato].bEndox = TRUE;
	g_FormCaract[sub_consensoinformato].bImageNT = FALSE;

	g_FormCaract[sub_legenda1].lID = SUB_LEGENDA1;
	g_FormCaract[sub_legenda1].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_95);
	g_FormCaract[sub_legenda1].lMinA = 1;
	g_FormCaract[sub_legenda1].lMaxA = 26;
	g_FormCaract[sub_legenda1].lMinL = 1;
	g_FormCaract[sub_legenda1].lMaxL = 16;
	g_FormCaract[sub_legenda1].bEndox = TRUE;
	g_FormCaract[sub_legenda1].bImageNT = FALSE;

	g_FormCaract[sub_legenda2].lID = SUB_LEGENDA2;
	g_FormCaract[sub_legenda2].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_96);
	g_FormCaract[sub_legenda2].lMinA = 1;
	g_FormCaract[sub_legenda2].lMaxA = 26;
	g_FormCaract[sub_legenda2].lMinL = 1;
	g_FormCaract[sub_legenda2].lMaxL = 16;
	g_FormCaract[sub_legenda2].bEndox = TRUE;
	g_FormCaract[sub_legenda2].bImageNT = FALSE;

	g_FormCaract[edt_sedeesame].lID = EDT_SEDEESAME;
	g_FormCaract[edt_sedeesame].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_98);
	g_FormCaract[edt_sedeesame].lMinA = 2;
	g_FormCaract[edt_sedeesame].lMaxA = 2;
	g_FormCaract[edt_sedeesame].lMinL = 1;
	g_FormCaract[edt_sedeesame].lMaxL = 4;
	g_FormCaract[edt_sedeesame].bEndox = TRUE;
	g_FormCaract[edt_sedeesame].bImageNT = FALSE;

	g_FormCaract[edt_salaesame].lID = EDT_SALAESAME;
	g_FormCaract[edt_salaesame].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_298);
	g_FormCaract[edt_salaesame].lMinA = 2;
	g_FormCaract[edt_salaesame].lMaxA = 2;
	g_FormCaract[edt_salaesame].lMinL = 1;
	g_FormCaract[edt_salaesame].lMaxL = 4;
	g_FormCaract[edt_salaesame].bEndox = TRUE;
	g_FormCaract[edt_salaesame].bImageNT = FALSE;

	g_FormCaract[sub_codificadiagnosiesame].lID = SUB_CODIFICADIAGNOSIESAME;
	g_FormCaract[sub_codificadiagnosiesame].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_100);
	g_FormCaract[sub_codificadiagnosiesame].lMinA = 7;
	g_FormCaract[sub_codificadiagnosiesame].lMaxA = 26;
	g_FormCaract[sub_codificadiagnosiesame].lMinL = 2;
	g_FormCaract[sub_codificadiagnosiesame].lMaxL = 8;
	g_FormCaract[sub_codificadiagnosiesame].bEndox = TRUE;
	g_FormCaract[sub_codificadiagnosiesame].bImageNT = FALSE;

	g_FormCaract[sub_legenda3].lID = SUB_LEGENDA3;
	g_FormCaract[sub_legenda3].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_97);
	g_FormCaract[sub_legenda3].lMinA = 1;
	g_FormCaract[sub_legenda3].lMaxA = 26;
	g_FormCaract[sub_legenda3].lMinL = 1;
	g_FormCaract[sub_legenda3].lMaxL = 16;
	g_FormCaract[sub_legenda3].bEndox = TRUE;
	g_FormCaract[sub_legenda3].bImageNT = FALSE;

	g_FormCaract[sub_esamipregressi].lID = SUB_ESAMIPREGRESSI;
	g_FormCaract[sub_esamipregressi].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_101);
	g_FormCaract[sub_esamipregressi].lMinA = 6;
	g_FormCaract[sub_esamipregressi].lMaxA = 26;
	g_FormCaract[sub_esamipregressi].lMinL = 2;
	g_FormCaract[sub_esamipregressi].lMaxL = 8;
	g_FormCaract[sub_esamipregressi].bEndox = TRUE;
	g_FormCaract[sub_esamipregressi].bImageNT = TRUE;

	g_FormCaract[edt_inviante1].lID = EDT_INVIANTE1;
	g_FormCaract[edt_inviante1].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_112);
	g_FormCaract[edt_inviante1].lMinA = 2;
	g_FormCaract[edt_inviante1].lMaxA = 2;
	g_FormCaract[edt_inviante1].lMinL = 1;
	g_FormCaract[edt_inviante1].lMaxL = 4;
	g_FormCaract[edt_inviante1].bEndox = TRUE;
	g_FormCaract[edt_inviante1].bImageNT = FALSE;

	g_FormCaract[edt_inviante2].lID = EDT_INVIANTE2;
	g_FormCaract[edt_inviante2].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_113);
	g_FormCaract[edt_inviante2].lMinA = 2;
	g_FormCaract[edt_inviante2].lMaxA = 2;
	g_FormCaract[edt_inviante2].lMinL = 1;
	g_FormCaract[edt_inviante2].lMaxL = 4;
	g_FormCaract[edt_inviante2].bEndox = TRUE;
	g_FormCaract[edt_inviante2].bImageNT = FALSE;

	g_FormCaract[edt_inviante3].lID = EDT_INVIANTE3;
	g_FormCaract[edt_inviante3].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_114);
	g_FormCaract[edt_inviante3].lMinA = 2;
	g_FormCaract[edt_inviante3].lMaxA = 2;
	g_FormCaract[edt_inviante3].lMinL = 1;
	g_FormCaract[edt_inviante3].lMaxL = 4;
	g_FormCaract[edt_inviante3].bEndox = TRUE;
	g_FormCaract[edt_inviante3].bImageNT = FALSE;

	g_FormCaract[sub_anatomiapatologica].lID = SUB_ANATOMIAPATOLOGICA;
	g_FormCaract[sub_anatomiapatologica].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_302);
	g_FormCaract[sub_anatomiapatologica].lMinA = 6;
	g_FormCaract[sub_anatomiapatologica].lMaxA = 26;
	g_FormCaract[sub_anatomiapatologica].lMinL = 2;
	g_FormCaract[sub_anatomiapatologica].lMaxL = 16;
	g_FormCaract[sub_anatomiapatologica].bEndox = TRUE;
	g_FormCaract[sub_anatomiapatologica].bImageNT = FALSE;

	g_FormCaract[edt_anatomiapatologicanote].lID = EDT_ANATOMIAPATOLOGICANOTE;
	g_FormCaract[edt_anatomiapatologicanote].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_117);
	g_FormCaract[edt_anatomiapatologicanote].lMinA = 2;
	g_FormCaract[edt_anatomiapatologicanote].lMaxA = 8;
	g_FormCaract[edt_anatomiapatologicanote].lMinL = 1;
	g_FormCaract[edt_anatomiapatologicanote].lMaxL = 16;
	g_FormCaract[edt_anatomiapatologicanote].bEndox = TRUE;
	g_FormCaract[edt_anatomiapatologicanote].bImageNT = FALSE;

	g_FormCaract[sub_anatomiapatologicaprest].lID = SUB_ANATOMIAPATOLOGICAPREST;
	g_FormCaract[sub_anatomiapatologicaprest].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_118);
	g_FormCaract[sub_anatomiapatologicaprest].lMinA = 4;
	g_FormCaract[sub_anatomiapatologicaprest].lMaxA = 26;
	g_FormCaract[sub_anatomiapatologicaprest].lMinL = 2;
	g_FormCaract[sub_anatomiapatologicaprest].lMaxL = 16;
	g_FormCaract[sub_anatomiapatologicaprest].bEndox = TRUE;
	g_FormCaract[sub_anatomiapatologicaprest].bImageNT = FALSE;

	g_FormCaract[edt_anatomiapatologicarefer].lID = EDT_ANATOMIAPATOLOGICAREFER;
	g_FormCaract[edt_anatomiapatologicarefer].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_119);
	g_FormCaract[edt_anatomiapatologicarefer].lMinA = 3;
	g_FormCaract[edt_anatomiapatologicarefer].lMaxA = 26;
	g_FormCaract[edt_anatomiapatologicarefer].lMinL = 1;
	g_FormCaract[edt_anatomiapatologicarefer].lMaxL = 16;
	g_FormCaract[edt_anatomiapatologicarefer].bEndox = TRUE;
	g_FormCaract[edt_anatomiapatologicarefer].bImageNT = FALSE;

	g_FormCaract[edt_anatomiapatologicarefer_rtf].lID = EDT_ANATOMIAPATOLOGICAREFER_RTF;
	g_FormCaract[edt_anatomiapatologicarefer_rtf].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_301);
	g_FormCaract[edt_anatomiapatologicarefer_rtf].lMinA = 3;
	g_FormCaract[edt_anatomiapatologicarefer_rtf].lMaxA = 26;
	g_FormCaract[edt_anatomiapatologicarefer_rtf].lMinL = 1;
	g_FormCaract[edt_anatomiapatologicarefer_rtf].lMaxL = 16;
	g_FormCaract[edt_anatomiapatologicarefer_rtf].bEndox = TRUE;
	g_FormCaract[edt_anatomiapatologicarefer_rtf].bImageNT = FALSE;

	g_FormCaract[sub_anatomiapatologicatasti].lID = SUB_ANATOMIAPATOLOGICATASTI;
	g_FormCaract[sub_anatomiapatologicatasti].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_120);
	g_FormCaract[sub_anatomiapatologicatasti].lMinA = 3;
	g_FormCaract[sub_anatomiapatologicatasti].lMaxA = 6;
	g_FormCaract[sub_anatomiapatologicatasti].lMinL = 2;
	g_FormCaract[sub_anatomiapatologicatasti].lMaxL = 8;
	g_FormCaract[sub_anatomiapatologicatasti].bEndox = TRUE;
	g_FormCaract[sub_anatomiapatologicatasti].bImageNT = FALSE;

	g_FormCaract[edt_anatomiapatologicasugger1].lID = EDT_ANATOMIAPATOLOGICASUGGER1;
	g_FormCaract[edt_anatomiapatologicasugger1].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_129);
	g_FormCaract[edt_anatomiapatologicasugger1].lMinA = 3;
	g_FormCaract[edt_anatomiapatologicasugger1].lMaxA = 8;
	g_FormCaract[edt_anatomiapatologicasugger1].lMinL = 1;
	g_FormCaract[edt_anatomiapatologicasugger1].lMaxL = 16;
	g_FormCaract[edt_anatomiapatologicasugger1].bEndox = TRUE;
	g_FormCaract[edt_anatomiapatologicasugger1].bImageNT = FALSE;

	g_FormCaract[edt_anatomiapatologicasugger2].lID = EDT_ANATOMIAPATOLOGICASUGGER2;
	g_FormCaract[edt_anatomiapatologicasugger2].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_297);
	g_FormCaract[edt_anatomiapatologicasugger2].lMinA = 3;
	g_FormCaract[edt_anatomiapatologicasugger2].lMaxA = 8;
	g_FormCaract[edt_anatomiapatologicasugger2].lMinL = 1;
	g_FormCaract[edt_anatomiapatologicasugger2].lMaxL = 16;
	g_FormCaract[edt_anatomiapatologicasugger2].bEndox = TRUE;
	g_FormCaract[edt_anatomiapatologicasugger2].bImageNT = FALSE;

	g_FormCaract[edt_organosedeprevista].lID = EDT_ORGANOSEDEPREVISTA;
	g_FormCaract[edt_organosedeprevista].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_479);
	g_FormCaract[edt_organosedeprevista].lMinA = 2;
	g_FormCaract[edt_organosedeprevista].lMaxA = 2;
	g_FormCaract[edt_organosedeprevista].lMinL = 1;
	g_FormCaract[edt_organosedeprevista].lMaxL = 4;
	g_FormCaract[edt_organosedeprevista].bEndox = TRUE;
	g_FormCaract[edt_organosedeprevista].bImageNT = FALSE;

	g_FormCaract[edt_organosederaggiunta].lID = EDT_ORGANOSEDERAGGIUNTA;
	g_FormCaract[edt_organosederaggiunta].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_480);
	g_FormCaract[edt_organosederaggiunta].lMinA = 2;
	g_FormCaract[edt_organosederaggiunta].lMaxA = 2;
	g_FormCaract[edt_organosederaggiunta].lMinL = 1;
	g_FormCaract[edt_organosederaggiunta].lMaxL = 4;
	g_FormCaract[edt_organosederaggiunta].bEndox = TRUE;
	g_FormCaract[edt_organosederaggiunta].bImageNT = FALSE;

	g_FormCaract[sub_allergie].lID = SUB_ALLERGIE;
	g_FormCaract[sub_allergie].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_292);
	g_FormCaract[sub_allergie].lMinA = 4;
	g_FormCaract[sub_allergie].lMaxA = 6;
	g_FormCaract[sub_allergie].lMinL = 1;
	g_FormCaract[sub_allergie].lMaxL = 8;
	g_FormCaract[sub_allergie].bEndox = TRUE;
	g_FormCaract[sub_allergie].bImageNT = FALSE;

	g_FormCaract[sub_pacemaker].lID = SUB_PACEMAKER;
	g_FormCaract[sub_pacemaker].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_293);
	g_FormCaract[sub_pacemaker].lMinA = 5;
	g_FormCaract[sub_pacemaker].lMaxA = 6;
	g_FormCaract[sub_pacemaker].lMinL = 1;
	g_FormCaract[sub_pacemaker].lMaxL = 8;
	g_FormCaract[sub_pacemaker].bEndox = TRUE;
	g_FormCaract[sub_pacemaker].bImageNT = FALSE;

	g_FormCaract[sub_portatorepacemaker].lID = SUB_PORTATOREPACEMAKER;
	g_FormCaract[sub_portatorepacemaker].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_303);
	g_FormCaract[sub_portatorepacemaker].lMinA = 4;
	g_FormCaract[sub_portatorepacemaker].lMaxA = 6;
	g_FormCaract[sub_portatorepacemaker].lMinL = 1;
	g_FormCaract[sub_portatorepacemaker].lMaxL = 8;
	g_FormCaract[sub_portatorepacemaker].bEndox = TRUE;
	g_FormCaract[sub_portatorepacemaker].bImageNT = FALSE;

	g_FormCaract[sub_anticoagulanti].lID = SUB_ANTICOAGULANTI;
	g_FormCaract[sub_anticoagulanti].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_304);
	g_FormCaract[sub_anticoagulanti].lMinA = 4;
	g_FormCaract[sub_anticoagulanti].lMaxA = 6;
	g_FormCaract[sub_anticoagulanti].lMinL = 1;
	g_FormCaract[sub_anticoagulanti].lMaxL = 8;
	g_FormCaract[sub_anticoagulanti].bEndox = TRUE;
	g_FormCaract[sub_anticoagulanti].bImageNT = FALSE;

	g_FormCaract[sub_antiaggreganti].lID = SUB_ANTIAGGREGANTI;
	g_FormCaract[sub_antiaggreganti].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_305);
	g_FormCaract[sub_antiaggreganti].lMinA = 4;
	g_FormCaract[sub_antiaggreganti].lMaxA = 6;
	g_FormCaract[sub_antiaggreganti].lMinL = 1;
	g_FormCaract[sub_antiaggreganti].lMaxL = 8;
	g_FormCaract[sub_antiaggreganti].bEndox = TRUE;
	g_FormCaract[sub_antiaggreganti].bImageNT = FALSE;

	g_FormCaract[sub_regione5righe].lID = SUB_REGIONE5RIGHE;
	g_FormCaract[sub_regione5righe].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_306);
	g_FormCaract[sub_regione5righe].lMinA = 8;
	g_FormCaract[sub_regione5righe].lMaxA = 26;
	g_FormCaract[sub_regione5righe].lMinL = 2;
	g_FormCaract[sub_regione5righe].lMaxL = 8;
	g_FormCaract[sub_regione5righe].bEndox = TRUE;
	g_FormCaract[sub_regione5righe].bImageNT = FALSE;

	g_FormCaract[sub_codificadiagnosiesame5righe].lID = SUB_CODIFICADIAGNOSIESAME5RIGHE;
	g_FormCaract[sub_codificadiagnosiesame5righe].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_307);
	g_FormCaract[sub_codificadiagnosiesame5righe].lMinA = 8;
	g_FormCaract[sub_codificadiagnosiesame5righe].lMaxA = 26;
	g_FormCaract[sub_codificadiagnosiesame5righe].lMinL = 2;
	g_FormCaract[sub_codificadiagnosiesame5righe].lMaxL = 8;
	g_FormCaract[sub_codificadiagnosiesame5righe].bEndox = TRUE;
	g_FormCaract[sub_codificadiagnosiesame5righe].bImageNT = FALSE;

	g_FormCaract[edt_fumo].lID = EDT_FUMO;
	g_FormCaract[edt_fumo].sDescrizione = theApp.m_sAnamText[0];
	g_FormCaract[edt_fumo].lMinA = 2;
	g_FormCaract[edt_fumo].lMaxA = 26;
	g_FormCaract[edt_fumo].lMinL = 1;
	g_FormCaract[edt_fumo].lMaxL = 16;
	g_FormCaract[edt_fumo].bEndox = TRUE;
	g_FormCaract[edt_fumo].bImageNT = FALSE;

	g_FormCaract[edt_caffe].lID = EDT_CAFFE;
	g_FormCaract[edt_caffe].sDescrizione = theApp.m_sAnamText[2];
	g_FormCaract[edt_caffe].lMinA = 2;
	g_FormCaract[edt_caffe].lMaxA = 26;
	g_FormCaract[edt_caffe].lMinL = 1;
	g_FormCaract[edt_caffe].lMaxL = 16;
	g_FormCaract[edt_caffe].bEndox = TRUE;
	g_FormCaract[edt_caffe].bImageNT = FALSE;

	g_FormCaract[edt_sigarette].lID = EDT_SIGARETTE;
	g_FormCaract[edt_sigarette].sDescrizione = theApp.m_sAnamText[1];
	g_FormCaract[edt_sigarette].lMinA = 2;
	g_FormCaract[edt_sigarette].lMaxA = 26;
	g_FormCaract[edt_sigarette].lMinL = 1;
	g_FormCaract[edt_sigarette].lMaxL = 16;
	g_FormCaract[edt_sigarette].bEndox = TRUE;
	g_FormCaract[edt_sigarette].bImageNT = FALSE;

	g_FormCaract[edt_farmaci].lID = EDT_FARMACI;
	g_FormCaract[edt_farmaci].sDescrizione = theApp.m_sAnamText[5];
	g_FormCaract[edt_farmaci].lMinA = 2;
	g_FormCaract[edt_farmaci].lMaxA = 26;
	g_FormCaract[edt_farmaci].lMinL = 1;
	g_FormCaract[edt_farmaci].lMaxL = 16;
	g_FormCaract[edt_farmaci].bEndox = TRUE;
	g_FormCaract[edt_farmaci].bImageNT = FALSE;

	g_FormCaract[edt_alcool].lID = EDT_ALCOOL;
	g_FormCaract[edt_alcool].sDescrizione = theApp.m_sAnamText[3];
	g_FormCaract[edt_alcool].lMinA = 2;
	g_FormCaract[edt_alcool].lMaxA = 26;
	g_FormCaract[edt_alcool].lMinL = 1;
	g_FormCaract[edt_alcool].lMaxL = 16;
	g_FormCaract[edt_alcool].bEndox = TRUE;
	g_FormCaract[edt_alcool].bImageNT = FALSE;

	g_FormCaract[edt_assunzione].lID = EDT_ASSUNZIONE;
	g_FormCaract[edt_assunzione].sDescrizione = theApp.m_sAnamText[6];
	g_FormCaract[edt_assunzione].lMinA = 2;
	g_FormCaract[edt_assunzione].lMaxA = 26;
	g_FormCaract[edt_assunzione].lMinL = 1;
	g_FormCaract[edt_assunzione].lMaxL = 16;
	g_FormCaract[edt_assunzione].bEndox = TRUE;
	g_FormCaract[edt_assunzione].bImageNT = FALSE;

	g_FormCaract[edt_superalcolici].lID = EDT_SUPERALCOLICI;
	g_FormCaract[edt_superalcolici].sDescrizione = theApp.m_sAnamText[4];
	g_FormCaract[edt_superalcolici].lMinA = 2;
	g_FormCaract[edt_superalcolici].lMaxA = 26;
	g_FormCaract[edt_superalcolici].lMinL = 1;
	g_FormCaract[edt_superalcolici].lMaxL = 16;
	g_FormCaract[edt_superalcolici].bEndox = TRUE;
	g_FormCaract[edt_superalcolici].bImageNT = FALSE;

	g_FormCaract[sub_bmi].lID = SUB_BMI;
	g_FormCaract[sub_bmi].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_315);
	g_FormCaract[sub_bmi].lMinA = 2;
	g_FormCaract[sub_bmi].lMaxA = 26;
	g_FormCaract[sub_bmi].lMinL = 1;
	g_FormCaract[sub_bmi].lMaxL = 16;
	g_FormCaract[sub_bmi].bEndox = TRUE;
	g_FormCaract[sub_bmi].bImageNT = FALSE;

	g_FormCaract[sub_volume].lID = SUB_VOLUME;
	g_FormCaract[sub_volume].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_584);
	g_FormCaract[sub_volume].lMinA = 2;
	g_FormCaract[sub_volume].lMaxA = 26;
	g_FormCaract[sub_volume].lMinL = 1;
	g_FormCaract[sub_volume].lMaxL = 16;
	g_FormCaract[sub_volume].bEndox = TRUE;
	g_FormCaract[sub_volume].bImageNT = FALSE;

	g_FormCaract[sub_fluoroscopia].lID = SUB_FLUOROSCOPIA;
	g_FormCaract[sub_fluoroscopia].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_320);
	g_FormCaract[sub_fluoroscopia].lMinA = 2;
	g_FormCaract[sub_fluoroscopia].lMaxA = 26;
	g_FormCaract[sub_fluoroscopia].lMinL = 1;
	g_FormCaract[sub_fluoroscopia].lMaxL = 16;
	g_FormCaract[sub_fluoroscopia].bEndox = TRUE;
	g_FormCaract[sub_fluoroscopia].bImageNT = FALSE;

	g_FormCaract[sub_accessori5righe].lID = SUB_ACCESSORI5RIGHE;
	g_FormCaract[sub_accessori5righe].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_317);
	g_FormCaract[sub_accessori5righe].lMinA = 8;
	g_FormCaract[sub_accessori5righe].lMaxA = 26;
	g_FormCaract[sub_accessori5righe].lMinL = 2;
	g_FormCaract[sub_accessori5righe].lMaxL = 16;
	g_FormCaract[sub_accessori5righe].bEndox = TRUE;
	g_FormCaract[sub_accessori5righe].bImageNT = FALSE;

	g_FormCaract[btn_convalida].lID = BTN_CONVALIDA;
	g_FormCaract[btn_convalida].sDescrizione = theApp.GetMessageString(IDS_BTN_CONVALIDA);
	g_FormCaract[btn_convalida].lMinA = 1;
	g_FormCaract[btn_convalida].lMaxA = 2;
	g_FormCaract[btn_convalida].lMinL = 1;
	g_FormCaract[btn_convalida].lMaxL = 16;
	g_FormCaract[btn_convalida].bEndox = TRUE;
	g_FormCaract[btn_convalida].bImageNT = FALSE;

	g_FormCaract[sub_istopatologia5righe].lID = SUB_ISTOPATOLOGIA5RIGHE;
	g_FormCaract[sub_istopatologia5righe].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_99);
	g_FormCaract[sub_istopatologia5righe].lMinA = 8;
	g_FormCaract[sub_istopatologia5righe].lMaxA = 25;
	g_FormCaract[sub_istopatologia5righe].lMinL = 2;
	g_FormCaract[sub_istopatologia5righe].lMaxL = 16;
	g_FormCaract[sub_istopatologia5righe].bEndox = TRUE;
	g_FormCaract[sub_istopatologia5righe].bImageNT = FALSE;

	g_FormCaract[sub_istopatologia5righe_plus].lID = SUB_ISTOPATOLOGIA5RIGHE_PLUS;
	g_FormCaract[sub_istopatologia5righe_plus].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_520);
	g_FormCaract[sub_istopatologia5righe_plus].lMinA = 6;
	g_FormCaract[sub_istopatologia5righe_plus].lMaxA = 25;
	g_FormCaract[sub_istopatologia5righe_plus].lMinL = 2;
	g_FormCaract[sub_istopatologia5righe_plus].lMaxL = 16;
	g_FormCaract[sub_istopatologia5righe_plus].bEndox = TRUE;
	g_FormCaract[sub_istopatologia5righe_plus].bImageNT = FALSE;

	g_FormCaract[edt_inviante_i].lID = EDT_INVIANTE_I;
	g_FormCaract[edt_inviante_i].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_334);
	g_FormCaract[edt_inviante_i].lMinA = 2;
	g_FormCaract[edt_inviante_i].lMaxA = 2;
	g_FormCaract[edt_inviante_i].lMinL = 1;
	g_FormCaract[edt_inviante_i].lMaxL = 8;
	g_FormCaract[edt_inviante_i].bEndox = TRUE;
	g_FormCaract[edt_inviante_i].bImageNT = FALSE;

	g_FormCaract[edt_inviante_e].lID = EDT_INVIANTE_E;
	g_FormCaract[edt_inviante_e].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_335);
	g_FormCaract[edt_inviante_e].lMinA = 2;
	g_FormCaract[edt_inviante_e].lMaxA = 2;
	g_FormCaract[edt_inviante_e].lMinL = 1;
	g_FormCaract[edt_inviante_e].lMaxL = 8;
	g_FormCaract[edt_inviante_e].bEndox = TRUE;
	g_FormCaract[edt_inviante_e].bImageNT = FALSE;

	g_FormCaract[edt_paziente_medicocurante].lID = EDT_PAZIENTE_MEDICOCURANTE;
	g_FormCaract[edt_paziente_medicocurante].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_10);
	g_FormCaract[edt_paziente_medicocurante].lMinA = 2;
	g_FormCaract[edt_paziente_medicocurante].lMaxA = 2;
	g_FormCaract[edt_paziente_medicocurante].lMinL = 1;
	g_FormCaract[edt_paziente_medicocurante].lMaxL = 8;
	g_FormCaract[edt_paziente_medicocurante].bEndox = TRUE;
	g_FormCaract[edt_paziente_medicocurante].bImageNT = FALSE;

	g_FormCaract[cmb_complicanzeimmediate].lID = CMB_COMPLICANZEIMMEDIATE;
	g_FormCaract[cmb_complicanzeimmediate].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_356);
	g_FormCaract[cmb_complicanzeimmediate].lMinA = 2;
	g_FormCaract[cmb_complicanzeimmediate].lMaxA = 2;
	g_FormCaract[cmb_complicanzeimmediate].lMinL = 1;
	g_FormCaract[cmb_complicanzeimmediate].lMaxL = 4;
	g_FormCaract[cmb_complicanzeimmediate].bEndox = TRUE;
	g_FormCaract[cmb_complicanzeimmediate].bImageNT = TRUE;

	g_FormCaract[cmb_complicanzetardive].lID = CMB_COMPLICANZETARDIVE;
	g_FormCaract[cmb_complicanzetardive].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_357);
	g_FormCaract[cmb_complicanzetardive].lMinA = 2;
	g_FormCaract[cmb_complicanzetardive].lMaxA = 2;
	g_FormCaract[cmb_complicanzetardive].lMinL = 1;
	g_FormCaract[cmb_complicanzetardive].lMaxL = 4;
	g_FormCaract[cmb_complicanzetardive].bEndox = TRUE;
	g_FormCaract[cmb_complicanzetardive].bImageNT = TRUE;

	g_FormCaract[cmb_pulizia].lID = CMB_PULIZIA;
	g_FormCaract[cmb_pulizia].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_358);
	g_FormCaract[cmb_pulizia].lMinA = 2;
	g_FormCaract[cmb_pulizia].lMaxA = 2;
	g_FormCaract[cmb_pulizia].lMinL = 1;
	g_FormCaract[cmb_pulizia].lMaxL = 4;
	g_FormCaract[cmb_pulizia].bEndox = TRUE;
	g_FormCaract[cmb_pulizia].bImageNT = TRUE;

	g_FormCaract[cmb_causenoncompletamento].lID = CMB_CAUSENONCOMPLETAMENTO;
	g_FormCaract[cmb_causenoncompletamento].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_359);
	g_FormCaract[cmb_causenoncompletamento].lMinA = 2;
	g_FormCaract[cmb_causenoncompletamento].lMaxA = 2;
	g_FormCaract[cmb_causenoncompletamento].lMinL = 1;
	g_FormCaract[cmb_causenoncompletamento].lMaxL = 4;
	g_FormCaract[cmb_causenoncompletamento].bEndox = TRUE;
	g_FormCaract[cmb_causenoncompletamento].bImageNT = TRUE;

	g_FormCaract[cmb_tolleranza].lID = CMB_TOLLERANZA;
	g_FormCaract[cmb_tolleranza].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_360);
	g_FormCaract[cmb_tolleranza].lMinA = 2;
	g_FormCaract[cmb_tolleranza].lMaxA = 2;
	g_FormCaract[cmb_tolleranza].lMinL = 1;
	g_FormCaract[cmb_tolleranza].lMaxL = 4;
	g_FormCaract[cmb_tolleranza].bEndox = TRUE;
	g_FormCaract[cmb_tolleranza].bImageNT = TRUE;

	g_FormCaract[cmb_conclusioniscreening].lID = CMB_CONCLUSIONISCREENING;
	g_FormCaract[cmb_conclusioniscreening].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_361);
	g_FormCaract[cmb_conclusioniscreening].lMinA = 2;
	g_FormCaract[cmb_conclusioniscreening].lMaxA = 2;
	g_FormCaract[cmb_conclusioniscreening].lMinL = 1;
	g_FormCaract[cmb_conclusioniscreening].lMaxL = 4;
	g_FormCaract[cmb_conclusioniscreening].bEndox = TRUE;
	g_FormCaract[cmb_conclusioniscreening].bImageNT = TRUE;

	g_FormCaract[cmb_conclusionicolon].lID = CMB_CONCLUSIONICOLON;
	g_FormCaract[cmb_conclusionicolon].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_362);
	g_FormCaract[cmb_conclusionicolon].lMinA = 2;
	g_FormCaract[cmb_conclusionicolon].lMaxA = 2;
	g_FormCaract[cmb_conclusionicolon].lMinL = 1;
	g_FormCaract[cmb_conclusionicolon].lMaxL = 4;
	g_FormCaract[cmb_conclusionicolon].bEndox = TRUE;
	g_FormCaract[cmb_conclusionicolon].bImageNT = TRUE;

	g_FormCaract[cmb_diagnosifinale].lID = CMB_DIAGNOSIFINALE;
	g_FormCaract[cmb_diagnosifinale].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_378);
	g_FormCaract[cmb_diagnosifinale].lMinA = 2;
	g_FormCaract[cmb_diagnosifinale].lMaxA = 2;
	g_FormCaract[cmb_diagnosifinale].lMinL = 1;
	g_FormCaract[cmb_diagnosifinale].lMaxL = 4;
	g_FormCaract[cmb_diagnosifinale].bEndox = TRUE;
	g_FormCaract[cmb_diagnosifinale].bImageNT = TRUE;

	g_FormCaract[sub_necassospedaliera].lID = SUB_NECASSOSPEDALIERA;
	g_FormCaract[sub_necassospedaliera].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_505);
	g_FormCaract[sub_necassospedaliera].lMinA = 1;
	g_FormCaract[sub_necassospedaliera].lMaxA = 2;
	g_FormCaract[sub_necassospedaliera].lMinL = 1;
	g_FormCaract[sub_necassospedaliera].lMaxL = 8;
	g_FormCaract[sub_necassospedaliera].bEndox = TRUE;
	g_FormCaract[sub_necassospedaliera].bImageNT = FALSE;

	g_FormCaract[edt_premedposologia].lID = EDT_PREMEDPOSOLOGIA;
	g_FormCaract[edt_premedposologia].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_364);
	g_FormCaract[edt_premedposologia].lMinA = 2;
	g_FormCaract[edt_premedposologia].lMaxA = 2;
	g_FormCaract[edt_premedposologia].lMinL = 1;
	g_FormCaract[edt_premedposologia].lMaxL = 8;
	g_FormCaract[edt_premedposologia].bEndox = TRUE;
	g_FormCaract[edt_premedposologia].bImageNT = FALSE;

	g_FormCaract[cmb_altreanomalie].lID = CMB_ALTREANOMALIE;
	g_FormCaract[cmb_altreanomalie].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_569);
	g_FormCaract[cmb_altreanomalie].lMinA = 2;
	g_FormCaract[cmb_altreanomalie].lMaxA = 2;
	g_FormCaract[cmb_altreanomalie].lMinL = 1;
	g_FormCaract[cmb_altreanomalie].lMaxL = 4;
	g_FormCaract[cmb_altreanomalie].bEndox = TRUE;
	g_FormCaract[cmb_altreanomalie].bImageNT = FALSE;

	g_FormCaract[btn_chiusuraesame].lID = BTN_CHIUSURAESAME;
	g_FormCaract[btn_chiusuraesame].sDescrizione = theApp.GetMessageString(IDS_BTN_CHIUSURAESAME);
	g_FormCaract[btn_chiusuraesame].lMinA = 1;
	g_FormCaract[btn_chiusuraesame].lMaxA = 2;
	g_FormCaract[btn_chiusuraesame].lMinL = 1;
	g_FormCaract[btn_chiusuraesame].lMaxL = 16;
	g_FormCaract[btn_chiusuraesame].bEndox = TRUE;
	g_FormCaract[btn_chiusuraesame].bImageNT = FALSE;

	g_FormCaract[edt_mst_complicanze1].lID = EDT_MST_COMPLICANZE1;
	g_FormCaract[edt_mst_complicanze1].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_366);
	g_FormCaract[edt_mst_complicanze1].lMinA = 3;
	g_FormCaract[edt_mst_complicanze1].lMaxA = 26;
	g_FormCaract[edt_mst_complicanze1].lMinL = 1;
	g_FormCaract[edt_mst_complicanze1].lMaxL = 8;
	g_FormCaract[edt_mst_complicanze1].bEndox = TRUE;
	g_FormCaract[edt_mst_complicanze1].bImageNT = FALSE;

	g_FormCaract[edt_mst_complicanze2].lID = EDT_MST_COMPLICANZE2;
	g_FormCaract[edt_mst_complicanze2].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_367);
	g_FormCaract[edt_mst_complicanze2].lMinA = 3;
	g_FormCaract[edt_mst_complicanze2].lMaxA = 26;
	g_FormCaract[edt_mst_complicanze2].lMinL = 1;
	g_FormCaract[edt_mst_complicanze2].lMaxL = 8;
	g_FormCaract[edt_mst_complicanze2].bEndox = TRUE;
	g_FormCaract[edt_mst_complicanze2].bImageNT = FALSE;

	g_FormCaract[edt_mst_complicanze3].lID = EDT_MST_COMPLICANZE3;
	g_FormCaract[edt_mst_complicanze3].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_368);
	g_FormCaract[edt_mst_complicanze3].lMinA = 3;
	g_FormCaract[edt_mst_complicanze3].lMaxA = 26;
	g_FormCaract[edt_mst_complicanze3].lMinL = 1;
	g_FormCaract[edt_mst_complicanze3].lMaxL = 8;
	g_FormCaract[edt_mst_complicanze3].bEndox = TRUE;
	g_FormCaract[edt_mst_complicanze3].bImageNT = FALSE;

	g_FormCaract[sub_breathtest_hp].lID = SUB_BREATHTEST_HP;
	g_FormCaract[sub_breathtest_hp].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_375);
	g_FormCaract[sub_breathtest_hp].lMinA = 4;
	g_FormCaract[sub_breathtest_hp].lMaxA = 6;
	g_FormCaract[sub_breathtest_hp].lMinL = 1;
	g_FormCaract[sub_breathtest_hp].lMaxL = 8;
	g_FormCaract[sub_breathtest_hp].bEndox = TRUE;
	g_FormCaract[sub_breathtest_hp].bImageNT = FALSE;

	g_FormCaract[sub_sospensione].lID = SUB_SOSPENSIONE;
	g_FormCaract[sub_sospensione].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_382);
	g_FormCaract[sub_sospensione].lMinA = 4;
	g_FormCaract[sub_sospensione].lMaxA = 26;
	g_FormCaract[sub_sospensione].lMinL = 1;
	g_FormCaract[sub_sospensione].lMaxL = 8;
	g_FormCaract[sub_sospensione].bEndox = TRUE;
	g_FormCaract[sub_sospensione].bImageNT = FALSE;

	g_FormCaract[sub_procedureicd9].lID = SUB_PROCEDUREICD9;
	g_FormCaract[sub_procedureicd9].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_386);
	g_FormCaract[sub_procedureicd9].lMinA = 7;
	g_FormCaract[sub_procedureicd9].lMaxA = 26;
	g_FormCaract[sub_procedureicd9].lMinL = 2;
	g_FormCaract[sub_procedureicd9].lMaxL = 16;
	g_FormCaract[sub_procedureicd9].bEndox = TRUE;
	g_FormCaract[sub_procedureicd9].bImageNT = FALSE;

	g_FormCaract[sub_diagnosiicd9].lID = SUB_DIAGNOSIICD9;
	g_FormCaract[sub_diagnosiicd9].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_387);
	g_FormCaract[sub_diagnosiicd9].lMinA = 7;
	g_FormCaract[sub_diagnosiicd9].lMaxA = 26;
	g_FormCaract[sub_diagnosiicd9].lMinL = 2;
	g_FormCaract[sub_diagnosiicd9].lMaxL = 16;
	g_FormCaract[sub_diagnosiicd9].bEndox = TRUE;
	g_FormCaract[sub_diagnosiicd9].bImageNT = FALSE;

	g_FormCaract[edt_codesame].lID = EDT_CODESAME;
	g_FormCaract[edt_codesame].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_413);
	g_FormCaract[edt_codesame].lMinA = 2;
	g_FormCaract[edt_codesame].lMaxA = 2;
	g_FormCaract[edt_codesame].lMinL = 1;
	g_FormCaract[edt_codesame].lMaxL = 8;
	g_FormCaract[edt_codesame].bEndox = TRUE;
	g_FormCaract[edt_codesame].bImageNT = TRUE;

	g_FormCaract[sub_puntipaziente].lID = SUB_PUNTIPAZIENTE;
	g_FormCaract[sub_puntipaziente].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_414);
	g_FormCaract[sub_puntipaziente].lMinA = 4;
	g_FormCaract[sub_puntipaziente].lMaxA = 26;
	g_FormCaract[sub_puntipaziente].lMinL = 2;
	g_FormCaract[sub_puntipaziente].lMaxL = 16;
	g_FormCaract[sub_puntipaziente].bEndox = TRUE;
	g_FormCaract[sub_puntipaziente].bImageNT = FALSE;

	g_FormCaract[edt_tempochiusura].lID = EDT_TEMPOCHIUSURA;
	g_FormCaract[edt_tempochiusura].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_415);
	g_FormCaract[edt_tempochiusura].lMinA = 2;
	g_FormCaract[edt_tempochiusura].lMaxA = 2;
	g_FormCaract[edt_tempochiusura].lMinL = 1;
	g_FormCaract[edt_tempochiusura].lMaxL = 4;
	g_FormCaract[edt_tempochiusura].bEndox = TRUE;
	g_FormCaract[edt_tempochiusura].bImageNT = TRUE;

	g_FormCaract[edt_tempoconvalida].lID = EDT_TEMPOCONVALIDA;
	g_FormCaract[edt_tempoconvalida].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_416);
	g_FormCaract[edt_tempoconvalida].lMinA = 2;
	g_FormCaract[edt_tempoconvalida].lMaxA = 2;
	g_FormCaract[edt_tempoconvalida].lMinL = 1;
	g_FormCaract[edt_tempoconvalida].lMaxL = 4;
	g_FormCaract[edt_tempoconvalida].bEndox = TRUE;
	g_FormCaract[edt_tempoconvalida].bImageNT = TRUE;

	g_FormCaract[edt_codicericovero].lID = EDT_CODICERICOVERO;
	g_FormCaract[edt_codicericovero].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_417);
	g_FormCaract[edt_codicericovero].lMinA = 2;
	g_FormCaract[edt_codicericovero].lMaxA = 2;
	g_FormCaract[edt_codicericovero].lMinL = 1;
	g_FormCaract[edt_codicericovero].lMaxL = 4;
	g_FormCaract[edt_codicericovero].bEndox = TRUE;
	g_FormCaract[edt_codicericovero].bImageNT = TRUE;

	g_FormCaract[edt_barcodericovero].lID = EDT_BARCODERICOVERO;
	g_FormCaract[edt_barcodericovero].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_467);
	g_FormCaract[edt_barcodericovero].lMinA = 2;
	g_FormCaract[edt_barcodericovero].lMaxA = 2;
	g_FormCaract[edt_barcodericovero].lMinL = 1;
	g_FormCaract[edt_barcodericovero].lMaxL = 4;
	g_FormCaract[edt_barcodericovero].bEndox = TRUE;
	g_FormCaract[edt_barcodericovero].bImageNT = TRUE;

	g_FormCaract[edt_assiden].lID = EDT_ASSIDEN;
	g_FormCaract[edt_assiden].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_418);
	g_FormCaract[edt_assiden].lMinA = 2;
	g_FormCaract[edt_assiden].lMaxA = 2;
	g_FormCaract[edt_assiden].lMinL = 1;
	g_FormCaract[edt_assiden].lMaxL = 8;
	g_FormCaract[edt_assiden].bEndox = TRUE;
	g_FormCaract[edt_assiden].bImageNT = TRUE;

	g_FormCaract[edt_codalfa].lID = EDT_CODALFA;
	g_FormCaract[edt_codalfa].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_494);
	g_FormCaract[edt_codalfa].lMinA = 2;
	g_FormCaract[edt_codalfa].lMaxA = 2;
	g_FormCaract[edt_codalfa].lMinL = 1;
	g_FormCaract[edt_codalfa].lMaxL = 8;
	g_FormCaract[edt_codalfa].bEndox = TRUE;
	g_FormCaract[edt_codalfa].bImageNT = TRUE;

	g_FormCaract[edt_pressione].lID = EDT_PRESSIONE;
	g_FormCaract[edt_pressione].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_442);
	g_FormCaract[edt_pressione].lMinA = 2;
	g_FormCaract[edt_pressione].lMaxA = 2;
	g_FormCaract[edt_pressione].lMinL = 1;
	g_FormCaract[edt_pressione].lMaxL = 4;
	g_FormCaract[edt_pressione].bEndox = TRUE;
	g_FormCaract[edt_pressione].bImageNT = FALSE;

	g_FormCaract[btn_videocapsula].lID = BTN_VIDEOCAPSULA;
	g_FormCaract[btn_videocapsula].sDescrizione = theApp.GetMessageString(IDS_BTN_VIDEOCAPSULA);
	g_FormCaract[btn_videocapsula].lMinA = 1;
	g_FormCaract[btn_videocapsula].lMaxA = 2;
	g_FormCaract[btn_videocapsula].lMinL = 1;
	g_FormCaract[btn_videocapsula].lMaxL = 16;
	g_FormCaract[btn_videocapsula].bEndox = TRUE;
	g_FormCaract[btn_videocapsula].bImageNT = FALSE;

	g_FormCaract[edt_esamestrumentale_orainizio].lID = EDT_ESAMESTRUMENTALE_ORAINIZIO;
	g_FormCaract[edt_esamestrumentale_orainizio].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_458);
	g_FormCaract[edt_esamestrumentale_orainizio].lMinA = 2;
	g_FormCaract[edt_esamestrumentale_orainizio].lMaxA = 2;
	g_FormCaract[edt_esamestrumentale_orainizio].lMinL = 2;
	g_FormCaract[edt_esamestrumentale_orainizio].lMaxL = 8;
	g_FormCaract[edt_esamestrumentale_orainizio].bEndox = TRUE;
	g_FormCaract[edt_esamestrumentale_orainizio].bImageNT = FALSE;

	g_FormCaract[edt_esamestrumentale_orafine].lID = EDT_ESAMESTRUMENTALE_ORAFINE;
	g_FormCaract[edt_esamestrumentale_orafine].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_459);
	g_FormCaract[edt_esamestrumentale_orafine].lMinA = 2;
	g_FormCaract[edt_esamestrumentale_orafine].lMaxA = 2;
	g_FormCaract[edt_esamestrumentale_orafine].lMinL = 2;
	g_FormCaract[edt_esamestrumentale_orafine].lMaxL = 8;
	g_FormCaract[edt_esamestrumentale_orafine].bEndox = TRUE;
	g_FormCaract[edt_esamestrumentale_orafine].bImageNT = FALSE;

	g_FormCaract[edt_esamestrumentale_durataoreminuti].lID = EDT_ESAMESTRUMENTALE_DURATAOREMINUTI;
	g_FormCaract[edt_esamestrumentale_durataoreminuti].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_460);
	g_FormCaract[edt_esamestrumentale_durataoreminuti].lMinA = 2;
	g_FormCaract[edt_esamestrumentale_durataoreminuti].lMaxA = 2;
	g_FormCaract[edt_esamestrumentale_durataoreminuti].lMinL = 2;
	g_FormCaract[edt_esamestrumentale_durataoreminuti].lMaxL = 8;
	g_FormCaract[edt_esamestrumentale_durataoreminuti].bEndox = TRUE;
	g_FormCaract[edt_esamestrumentale_durataoreminuti].bImageNT = FALSE;

	g_FormCaract[edt_esamestrumentale_duratasolominuti].lID = EDT_ESAMESTRUMENTALE_DURATASOLOMINUTI;
	g_FormCaract[edt_esamestrumentale_duratasolominuti].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_461);
	g_FormCaract[edt_esamestrumentale_duratasolominuti].lMinA = 2;
	g_FormCaract[edt_esamestrumentale_duratasolominuti].lMaxA = 2;
	g_FormCaract[edt_esamestrumentale_duratasolominuti].lMinL = 2;
	g_FormCaract[edt_esamestrumentale_duratasolominuti].lMaxL = 8;
	g_FormCaract[edt_esamestrumentale_duratasolominuti].bEndox = TRUE;
	g_FormCaract[edt_esamestrumentale_duratasolominuti].bImageNT = FALSE;

	g_FormCaract[sub_pazienticronici_terapia].lID = SUB_PAZIENTICRONICI_TERAPIA;
	g_FormCaract[sub_pazienticronici_terapia].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_484);
	g_FormCaract[sub_pazienticronici_terapia].lMinA = 2;
	g_FormCaract[sub_pazienticronici_terapia].lMaxA = 10;
	g_FormCaract[sub_pazienticronici_terapia].lMinL = 2;
	g_FormCaract[sub_pazienticronici_terapia].lMaxL = 8;
	g_FormCaract[sub_pazienticronici_terapia].bEndox = TRUE;
	g_FormCaract[sub_pazienticronici_terapia].bImageNT = FALSE;

	g_FormCaract[edt_pazienticronici_score_hb].lID = EDT_PAZIENTICRONICI_SCORE_HB;
	g_FormCaract[edt_pazienticronici_score_hb].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_485);
	g_FormCaract[edt_pazienticronici_score_hb].lMinA = 2;
	g_FormCaract[edt_pazienticronici_score_hb].lMaxA = 2;
	g_FormCaract[edt_pazienticronici_score_hb].lMinL = 1;
	g_FormCaract[edt_pazienticronici_score_hb].lMaxL = 4;
	g_FormCaract[edt_pazienticronici_score_hb].bEndox = TRUE;
	g_FormCaract[edt_pazienticronici_score_hb].bImageNT = FALSE;

	g_FormCaract[edt_pazienticronici_score_s].lID = EDT_PAZIENTICRONICI_SCORE_S;
	g_FormCaract[edt_pazienticronici_score_s].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_486);
	g_FormCaract[edt_pazienticronici_score_s].lMinA = 2;
	g_FormCaract[edt_pazienticronici_score_s].lMaxA = 2;
	g_FormCaract[edt_pazienticronici_score_s].lMinL = 1;
	g_FormCaract[edt_pazienticronici_score_s].lMaxL = 4;
	g_FormCaract[edt_pazienticronici_score_s].bEndox = TRUE;
	g_FormCaract[edt_pazienticronici_score_s].bImageNT = FALSE;

	g_FormCaract[sub_tabellaebus].lID = SUB_TABELLAEBUS;
	g_FormCaract[sub_tabellaebus].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_487);
	g_FormCaract[sub_tabellaebus].lMinA = 2;
	g_FormCaract[sub_tabellaebus].lMaxA = 10;
	g_FormCaract[sub_tabellaebus].lMinL = 2;
	g_FormCaract[sub_tabellaebus].lMaxL = 8;
	g_FormCaract[sub_tabellaebus].bEndox = TRUE;
	g_FormCaract[sub_tabellaebus].bImageNT = FALSE;

	g_FormCaract[sub_studio].lID = SUB_STUDIO;
	g_FormCaract[sub_studio].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_488);
	g_FormCaract[sub_studio].lMinA = 4;
	g_FormCaract[sub_studio].lMaxA = 10;
	g_FormCaract[sub_studio].lMinL = 2;
	g_FormCaract[sub_studio].lMaxL = 8;
	g_FormCaract[sub_studio].bEndox = TRUE;
	g_FormCaract[sub_studio].bImageNT = FALSE;

	g_FormCaract[edt_utente_inserimentoesame].lID = EDT_UTENTE_INSERIMENTOESAME;
	g_FormCaract[edt_utente_inserimentoesame].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_496);
	g_FormCaract[edt_utente_inserimentoesame].lMinA = 2;
	g_FormCaract[edt_utente_inserimentoesame].lMaxA = 2;
	g_FormCaract[edt_utente_inserimentoesame].lMinL = 1;
	g_FormCaract[edt_utente_inserimentoesame].lMaxL = 4;
	g_FormCaract[edt_utente_inserimentoesame].bEndox = TRUE;
	g_FormCaract[edt_utente_inserimentoesame].bImageNT = FALSE;

	g_FormCaract[edt_data_referto_istologico].lID = EDT_DATAREFERTOISTOLOGICO;
	g_FormCaract[edt_data_referto_istologico].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_501);
	g_FormCaract[edt_data_referto_istologico].lMinA = 1;
	g_FormCaract[edt_data_referto_istologico].lMaxA = 2;
	g_FormCaract[edt_data_referto_istologico].lMinL = 1;
	g_FormCaract[edt_data_referto_istologico].lMaxL = 8;
	g_FormCaract[edt_data_referto_istologico].bEndox = TRUE;
	g_FormCaract[edt_data_referto_istologico].bImageNT = FALSE;

	g_FormCaract[sub_presenzalesioneCCR].lID = SUB_PRESENZALESIONECCR;
	g_FormCaract[sub_presenzalesioneCCR].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_503);
	g_FormCaract[sub_presenzalesioneCCR].lMinA = 1;
	g_FormCaract[sub_presenzalesioneCCR].lMaxA = 2;
	g_FormCaract[sub_presenzalesioneCCR].lMinL = 1;
	g_FormCaract[sub_presenzalesioneCCR].lMaxL = 4;
	g_FormCaract[sub_presenzalesioneCCR].bEndox = TRUE;
	g_FormCaract[sub_presenzalesioneCCR].bImageNT = FALSE;

	g_FormCaract[edt_numerototalepolipi].lID = EDT_NUMEROTOTALEPOLIPI;
	g_FormCaract[edt_numerototalepolipi].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_506);
	g_FormCaract[edt_numerototalepolipi].lMinA = 1;
	g_FormCaract[edt_numerototalepolipi].lMaxA = 2;
	g_FormCaract[edt_numerototalepolipi].lMinL = 1;
	g_FormCaract[edt_numerototalepolipi].lMaxL = 4;
	g_FormCaract[edt_numerototalepolipi].bEndox = TRUE;
	g_FormCaract[edt_numerototalepolipi].bImageNT = FALSE;

	g_FormCaract[sub_bostonscore].lID = SUB_BOSTONSCORE;
	g_FormCaract[sub_bostonscore].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_508);
	g_FormCaract[sub_bostonscore].lMinA = 4;
	g_FormCaract[sub_bostonscore].lMaxA = 8;
	g_FormCaract[sub_bostonscore].lMinL = 4;
	g_FormCaract[sub_bostonscore].lMaxL = 8;
	g_FormCaract[sub_bostonscore].bEndox = TRUE;
	g_FormCaract[sub_bostonscore].bImageNT = FALSE;

	g_FormCaract[edt_temporetrazione].lID = EDT_TEMPORETRAZIONE;
	g_FormCaract[edt_temporetrazione].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_514);
	g_FormCaract[edt_temporetrazione].lMinA = 2;
	g_FormCaract[edt_temporetrazione].lMaxA = 2;
	g_FormCaract[edt_temporetrazione].lMinL = 1;
	g_FormCaract[edt_temporetrazione].lMaxL = 4;
	g_FormCaract[edt_temporetrazione].bEndox = TRUE;
	g_FormCaract[edt_temporetrazione].bImageNT = FALSE;

	g_FormCaract[edt_integrazioneCodiceUrgenza].lID = EDT_INTEGRAZIONECODICEURGENZA;
	g_FormCaract[edt_integrazioneCodiceUrgenza].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_574);
	g_FormCaract[edt_integrazioneCodiceUrgenza].lMinA = 2;
	g_FormCaract[edt_integrazioneCodiceUrgenza].lMaxA = 2;
	g_FormCaract[edt_integrazioneCodiceUrgenza].lMinL = 1;
	g_FormCaract[edt_integrazioneCodiceUrgenza].lMaxL = 8;
	g_FormCaract[edt_integrazioneCodiceUrgenza].bEndox = TRUE;
	g_FormCaract[edt_integrazioneCodiceUrgenza].bImageNT = TRUE;

	g_FormCaract[sub_diagnosiicd9ex].lID = SUB_DIAGNOSIICD9EX;
	g_FormCaract[sub_diagnosiicd9ex].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_577);
	g_FormCaract[sub_diagnosiicd9ex].lMinA = 6;
	g_FormCaract[sub_diagnosiicd9ex].lMaxA = 26;
	g_FormCaract[sub_diagnosiicd9ex].lMinL = 2;
	g_FormCaract[sub_diagnosiicd9ex].lMaxL = 8;
	g_FormCaract[sub_diagnosiicd9ex].bEndox = TRUE;
	g_FormCaract[sub_diagnosiicd9ex].bImageNT = FALSE;

	g_FormCaract[btn_centralerefertazione].lID = BTN_CENTRALEREFERTAZIONE;
	g_FormCaract[btn_centralerefertazione].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_578);
	g_FormCaract[btn_centralerefertazione].lMinA = 1;
	g_FormCaract[btn_centralerefertazione].lMaxA = 26;
	g_FormCaract[btn_centralerefertazione].lMinL = 2;
	g_FormCaract[btn_centralerefertazione].lMaxL = 16;
	g_FormCaract[btn_centralerefertazione].bEndox = TRUE;
	g_FormCaract[btn_centralerefertazione].bImageNT = FALSE;

	g_FormCaract[btn_carestream].lID = BTN_CARESTREAM;
	g_FormCaract[btn_carestream].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_581);
	g_FormCaract[btn_carestream].lMinA = 1;
	g_FormCaract[btn_carestream].lMaxA = 26;
	g_FormCaract[btn_carestream].lMinL = 2;
	g_FormCaract[btn_carestream].lMaxL = 16;
	g_FormCaract[btn_carestream].bEndox = TRUE;
	g_FormCaract[btn_carestream].bImageNT = FALSE;

	//Simone RIMA 16052
	for (int i = 0; i < NUM_LABEL_ETICHETTE; i++)
	{
		g_FormCaract[sub_etichetta000 + i].lID = SUB_ETICHETTA000 + i;
		g_FormCaract[sub_etichetta000 + i].sDescrizione = theApp.m_sLabelTextEtichette[i];
		g_FormCaract[sub_etichetta000 + i].lMinA = 1;
		g_FormCaract[sub_etichetta000 + i].lMaxA = 4;
		g_FormCaract[sub_etichetta000 + i].lMinL = 1;
		g_FormCaract[sub_etichetta000 + i].lMaxL = 16;
		g_FormCaract[sub_etichetta000 + i].bEndox = TRUE;
		g_FormCaract[sub_etichetta000 + i].bImageNT = FALSE;
	}

	g_FormCaract[sub_diagnosifinaliicd9ex].lID = SUB_DIAGNOSIFINALEICD9EX;
	g_FormCaract[sub_diagnosifinaliicd9ex].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_579);
	g_FormCaract[sub_diagnosifinaliicd9ex].lMinA = 6;
	g_FormCaract[sub_diagnosifinaliicd9ex].lMaxA = 26;
	g_FormCaract[sub_diagnosifinaliicd9ex].lMinL = 2;
	g_FormCaract[sub_diagnosifinaliicd9ex].lMaxL = 8;
	g_FormCaract[sub_diagnosifinaliicd9ex].bEndox = TRUE;
	g_FormCaract[sub_diagnosifinaliicd9ex].bImageNT = FALSE;

	//Simone RIMA 16052
	for (int i = 0; i < NUM_LABEL_TASTO_CHIUSURAFASE; i++)
	{
		g_FormCaract[btn_liberotastochiusurafase000 + i].lID = BTN_LIBEROTASTOCHIUSURAFASE000 + i;
		g_FormCaract[btn_liberotastochiusurafase000 + i].sDescrizione = theApp.m_sLabelTastoChiusuraFase[i];
		g_FormCaract[btn_liberotastochiusurafase000 + i].lMinA = 1;
		g_FormCaract[btn_liberotastochiusurafase000 + i].lMaxA = 4;
		g_FormCaract[btn_liberotastochiusurafase000 + i].lMinL = 1;
		g_FormCaract[btn_liberotastochiusurafase000 + i].lMaxL = 16;
		g_FormCaract[btn_liberotastochiusurafase000 + i].bEndox = TRUE;
		g_FormCaract[btn_liberotastochiusurafase000 + i].bImageNT = FALSE;
	}

	//Simone RIMA 16052
	for (int i = 0; i < NUM_LABEL_GRIDCL; i++)
	{
		g_FormCaract[sub_gridcl000 + i].lID = SUB_GRIDCL000 + i;
		g_FormCaract[sub_gridcl000 + i].sDescrizione = theApp.m_sLabelTextGridCL[i];
		g_FormCaract[sub_gridcl000 + i].lMinA = 1;
		g_FormCaract[sub_gridcl000 + i].lMaxA = 26;
		g_FormCaract[sub_gridcl000 + i].lMinL = 1;
		g_FormCaract[sub_gridcl000 + i].lMaxL = 16;
		g_FormCaract[sub_gridcl000 + i].bEndox = TRUE;
		g_FormCaract[sub_gridcl000 + i].bImageNT = FALSE;
	}

	g_FormCaract[cmb_esameurgente].lID = CMB_ESAMEURGENTE;
	g_FormCaract[cmb_esameurgente].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_580);
	g_FormCaract[cmb_esameurgente].lMinA = 2;
	g_FormCaract[cmb_esameurgente].lMaxA = 2;
	g_FormCaract[cmb_esameurgente].lMinL = 1;
	g_FormCaract[cmb_esameurgente].lMaxL = 4;
	g_FormCaract[cmb_esameurgente].bEndox = TRUE;
	g_FormCaract[cmb_esameurgente].bImageNT = FALSE;

	g_FormCaract[sub_codiciclassificazionediagnostica].lID = SUB_CODICICLASSIFICAZIONEDIAGNOSTICA;
	g_FormCaract[sub_codiciclassificazionediagnostica].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_583);
	g_FormCaract[sub_codiciclassificazionediagnostica].lMinA = 2;
	g_FormCaract[sub_codiciclassificazionediagnostica].lMaxA = 26;
	g_FormCaract[sub_codiciclassificazionediagnostica].lMinL = 1;
	g_FormCaract[sub_codiciclassificazionediagnostica].lMaxL = 16;
	g_FormCaract[sub_codiciclassificazionediagnostica].bEndox = TRUE;
	g_FormCaract[sub_codiciclassificazionediagnostica].bImageNT = FALSE;

	g_FormCaract[sub_cardio_prima].lID = SUB_CARDIO_PRIMA;
	g_FormCaract[sub_cardio_prima].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_585);
	g_FormCaract[sub_cardio_prima].lMinA = 6;
	g_FormCaract[sub_cardio_prima].lMaxA = 26;
	g_FormCaract[sub_cardio_prima].lMinL = 4;
	g_FormCaract[sub_cardio_prima].lMaxL = 16;
	g_FormCaract[sub_cardio_prima].bEndox = TRUE;
	g_FormCaract[sub_cardio_prima].bImageNT = FALSE;

	g_FormCaract[sub_cardio_durante].lID = SUB_CARDIO_DURANTE;
	g_FormCaract[sub_cardio_durante].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_586);
	g_FormCaract[sub_cardio_durante].lMinA = 6;
	g_FormCaract[sub_cardio_durante].lMaxA = 26;
	g_FormCaract[sub_cardio_durante].lMinL = 4;
	g_FormCaract[sub_cardio_durante].lMaxL = 16;
	g_FormCaract[sub_cardio_durante].bEndox = TRUE;
	g_FormCaract[sub_cardio_durante].bImageNT = FALSE;

	g_FormCaract[sub_cardio_dopo].lID = SUB_CARDIO_DOPO;
	g_FormCaract[sub_cardio_dopo].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_587);
	g_FormCaract[sub_cardio_dopo].lMinA = 6;
	g_FormCaract[sub_cardio_dopo].lMaxA = 26;
	g_FormCaract[sub_cardio_dopo].lMinL = 4;
	g_FormCaract[sub_cardio_dopo].lMaxL = 16;
	g_FormCaract[sub_cardio_dopo].bEndox = TRUE;
	g_FormCaract[sub_cardio_dopo].bImageNT = FALSE;

	g_FormCaract[edt_esame_coniugato].lID = EDT_ESAME_CONIUGATO;
	g_FormCaract[edt_esame_coniugato].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_588);
	g_FormCaract[edt_esame_coniugato].lMinA = 2;
	g_FormCaract[edt_esame_coniugato].lMaxA = 4;
	g_FormCaract[edt_esame_coniugato].lMinL = 1;
	g_FormCaract[edt_esame_coniugato].lMaxL = 4;
	g_FormCaract[edt_esame_coniugato].bEndox = TRUE;
	g_FormCaract[edt_esame_coniugato].bImageNT = FALSE;

	g_FormCaract[sub_centraledistampa].lID = SUB_CENTRALEDISTAMPA;
	g_FormCaract[sub_centraledistampa].sDescrizione = "";
	g_FormCaract[sub_centraledistampa].lMinA = 26;
	g_FormCaract[sub_centraledistampa].lMaxA = 26;
	g_FormCaract[sub_centraledistampa].lMinL = 16;
	g_FormCaract[sub_centraledistampa].lMaxL = 16;
	g_FormCaract[sub_centraledistampa].bEndox = TRUE;
	g_FormCaract[sub_centraledistampa].bImageNT = FALSE;

	g_FormCaract[sub_mielogramma].lID = SUB_MIELOGRAMMA;
	g_FormCaract[sub_mielogramma].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_589);
	g_FormCaract[sub_mielogramma].lMinA = 10;
	g_FormCaract[sub_mielogramma].lMaxA = 26;
	g_FormCaract[sub_mielogramma].lMinL = 4;
	g_FormCaract[sub_mielogramma].lMaxL = 16;
	g_FormCaract[sub_mielogramma].bEndox = TRUE;
	g_FormCaract[sub_mielogramma].bImageNT = FALSE;

	// sono differenti questi, lasciare così //
	g_FormCaract[btn_osservazioni].lID = BTN_OSSERVAZIONI;
	g_FormCaract[btn_diagnostiche].lID = BTN_DIAGNOSTICHE;
	g_FormCaract[btn_terapeutiche].lID = BTN_TERAPEUTICHE;
	g_FormCaract[btn_diagnosi].lID = BTN_DIAGNOSI;
	g_FormCaract[btn_codificadiagnosiesame].lID = BTN_CODIFICADIAGNOSIESAME;
	g_FormCaract[btn_codificadiagnosiesame5righe].lID = BTN_CODIFICADIAGNOSIESAME5RIGHE;
	g_FormCaract[btn_complicanze1].lID = BTN_COMPLICANZE1;
	g_FormCaract[btn_complicanze2].lID = BTN_COMPLICANZE2;
	g_FormCaract[btn_complicanze3].lID = BTN_COMPLICANZE3;

	//Luiz - 13/05/2019 - P3 - Atualiza nome/sobrenome Médico - Inclui Médicos solicitantes
	g_FormCaract[edt_medico2].lID = EDT_MEDICO2;
	g_FormCaract[edt_medico2].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_MEDICO2);
	g_FormCaract[edt_medico2].lMinA = 2;
	g_FormCaract[edt_medico2].lMaxA = 2;
	g_FormCaract[edt_medico2].lMinL = 1;
	g_FormCaract[edt_medico2].lMaxL = 8;
	g_FormCaract[edt_medico2].bEndox = TRUE;
	g_FormCaract[edt_medico2].bImageNT = FALSE;

	g_FormCaract[edt_medico3].lID = EDT_MEDICO3;
	g_FormCaract[edt_medico3].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_MEDICO3);
	g_FormCaract[edt_medico3].lMinA = 2;
	g_FormCaract[edt_medico3].lMaxA = 2;
	g_FormCaract[edt_medico3].lMinL = 1;
	g_FormCaract[edt_medico3].lMaxL = 8;
	g_FormCaract[edt_medico3].bEndox = TRUE;
	g_FormCaract[edt_medico3].bImageNT = FALSE;

	g_FormCaract[edt_medico4].lID = EDT_MEDICO4;
	g_FormCaract[edt_medico4].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_MEDICO4);
	g_FormCaract[edt_medico4].lMinA = 2;
	g_FormCaract[edt_medico4].lMaxA = 2;
	g_FormCaract[edt_medico4].lMinL = 1;
	g_FormCaract[edt_medico4].lMaxL = 8;
	g_FormCaract[edt_medico4].bEndox = TRUE;
	g_FormCaract[edt_medico4].bImageNT = FALSE;

	//Julio - BUG 3285 - Adequação de laudos (extra)
	g_FormCaract[edt_paziente_passaporto].lID = EDT_PAZIENTE_PASSAPORTO;
	g_FormCaract[edt_paziente_passaporto].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_PAZIENTE_PASSAPORTO);
	g_FormCaract[edt_paziente_passaporto].lMinA = 2;
	g_FormCaract[edt_paziente_passaporto].lMaxA = 2;
	g_FormCaract[edt_paziente_passaporto].lMinL = 1;
	g_FormCaract[edt_paziente_passaporto].lMaxL = 8;
	g_FormCaract[edt_paziente_passaporto].bEndox = TRUE;
	g_FormCaract[edt_paziente_passaporto].bImageNT = FALSE;

	//Julio - BUG 3285 - Adequação de laudos (extra)
	g_FormCaract[edt_paziente_doc1].lID = EDT_PAZIENTE_DOC1;
	g_FormCaract[edt_paziente_doc1].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_PAZIENTE_DOC1);
	g_FormCaract[edt_paziente_doc1].lMinA = 2;
	g_FormCaract[edt_paziente_doc1].lMaxA = 2;
	g_FormCaract[edt_paziente_doc1].lMinL = 1;
	g_FormCaract[edt_paziente_doc1].lMaxL = 8;
	g_FormCaract[edt_paziente_doc1].bEndox = TRUE;
	g_FormCaract[edt_paziente_doc1].bImageNT = FALSE;

	//Julio - BUG 3285 - Adequação de laudos (extra)
	g_FormCaract[edt_paziente_doc2].lID = EDT_PAZIENTE_DOC2;
	g_FormCaract[edt_paziente_doc2].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_PAZIENTE_DOC2);
	g_FormCaract[edt_paziente_doc2].lMinA = 2;
	g_FormCaract[edt_paziente_doc2].lMaxA = 2;
	g_FormCaract[edt_paziente_doc2].lMinL = 1;
	g_FormCaract[edt_paziente_doc2].lMaxL = 8;
	g_FormCaract[edt_paziente_doc2].bEndox = TRUE;
	g_FormCaract[edt_paziente_doc2].bImageNT = FALSE;

	//Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
	g_FormCaract[edt_refertointegrato_macro].lID = EDT_REFERTOINTEGRATO_MACRO;
	g_FormCaract[edt_refertointegrato_macro].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_REFERTOINTEGRATO_MACRO);
	g_FormCaract[edt_refertointegrato_macro].lMinA = 1;
	g_FormCaract[edt_refertointegrato_macro].lMaxA = 26;
	g_FormCaract[edt_refertointegrato_macro].lMinL = 1;
	g_FormCaract[edt_refertointegrato_macro].lMaxL = 16;
	g_FormCaract[edt_refertointegrato_macro].bEndox = TRUE;
	g_FormCaract[edt_refertointegrato_macro].bImageNT = FALSE;

	//Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
	g_FormCaract[edt_refertointegrato_diag].lID = EDT_REFERTOINTEGRATO_DIAG;
	g_FormCaract[edt_refertointegrato_diag].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_REFERTOINTEGRATO_DIAG);
	g_FormCaract[edt_refertointegrato_diag].lMinA = 1;
	g_FormCaract[edt_refertointegrato_diag].lMaxA = 26;
	g_FormCaract[edt_refertointegrato_diag].lMinL = 1;
	g_FormCaract[edt_refertointegrato_diag].lMaxL = 16;
	g_FormCaract[edt_refertointegrato_diag].bEndox = TRUE;
	g_FormCaract[edt_refertointegrato_diag].bImageNT = FALSE;

	//Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
	g_FormCaract[edt_refertointegrato_firma].lID = EDT_REFERTOINTEGRATO_FIRMA;
	g_FormCaract[edt_refertointegrato_firma].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_REFERTOINTEGRATO_FIRMA);
	g_FormCaract[edt_refertointegrato_firma].lMinA = 2;
	g_FormCaract[edt_refertointegrato_firma].lMaxA = 2;
	g_FormCaract[edt_refertointegrato_firma].lMinL = 1;
	g_FormCaract[edt_refertointegrato_firma].lMaxL = 8;
	g_FormCaract[edt_refertointegrato_firma].bEndox = TRUE;
	g_FormCaract[edt_refertointegrato_firma].bImageNT = FALSE;

	// Marvel Carvalho - BUG 4308 Esquemas Anatômicos Fleury
	g_FormCaract[sub_schemi_anatomichi].lID = SUB_SCHEMI_ANATOMICHI;
	g_FormCaract[sub_schemi_anatomichi].sDescrizione = theApp.GetMessageString(IDS_SCHEMI_ANATOMICI_EDIT);
	g_FormCaract[sub_schemi_anatomichi].lMinA = 1;
	g_FormCaract[sub_schemi_anatomichi].lMaxA = 26;
	g_FormCaract[sub_schemi_anatomichi].lMinL = 1;
	g_FormCaract[sub_schemi_anatomichi].lMaxL = 16;
	g_FormCaract[sub_schemi_anatomichi].bEndox = TRUE;
	g_FormCaract[sub_schemi_anatomichi].bImageNT = FALSE;

	/////////////////
	// --- --- --- //
	/////////////////

	for (int y = 0; y < endox_report_field_num_total; y++)
	{
		CFieldDlg::m_strFieldEndox[y].lID = -1;
		CFieldDlg::m_strFieldEndox[y].sCombo = "";
		CFieldDlg::m_strFieldEndox[y].sReport = "";
		CFieldDlg::m_strFieldEndox[y].bEndox = FALSE;
		CFieldDlg::m_strFieldEndox[y].bImageNT = FALSE;
	}

	CFieldDlg::m_strFieldEndox[paziente_progressivo].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_progressivo].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_00);
	CFieldDlg::m_strFieldEndox[paziente_progressivo].sReport = "Anagrafico.X"; // Progressivo paziente
	CFieldDlg::m_strFieldEndox[paziente_progressivo].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_progressivo].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_codicefiscale].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_codicefiscale].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_09);
	CFieldDlg::m_strFieldEndox[paziente_codicefiscale].sReport = "Anagrafico.I"; // Codice fiscale
	CFieldDlg::m_strFieldEndox[paziente_codicefiscale].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_codicefiscale].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_codicefiscale_largo].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_codicefiscale_largo].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_130);
	CFieldDlg::m_strFieldEndox[paziente_codicefiscale_largo].sReport = "Anagrafico.CodFiscLargo"; // Codice fiscale largo
	CFieldDlg::m_strFieldEndox[paziente_codicefiscale_largo].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_codicefiscale_largo].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_codicesanitario].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_codicesanitario].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_49);
	CFieldDlg::m_strFieldEndox[paziente_codicesanitario].sReport = "Anagrafico.J"; // Codice sanitario
	CFieldDlg::m_strFieldEndox[paziente_codicesanitario].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_codicesanitario].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_cognome].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_cognome].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_01);
	CFieldDlg::m_strFieldEndox[paziente_cognome].sReport = "Anagrafico.A"; // Cognome
	CFieldDlg::m_strFieldEndox[paziente_cognome].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_cognome].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_nome].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_nome].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_02);
	CFieldDlg::m_strFieldEndox[paziente_nome].sReport = "Anagrafico.B"; // Nome
	CFieldDlg::m_strFieldEndox[paziente_nome].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_nome].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_nominativo_cn].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_nominativo_cn].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_115);
	CFieldDlg::m_strFieldEndox[paziente_nominativo_cn].sReport = "Anagrafico.Nominativo"; // Nominativo (cognome + nome)
	CFieldDlg::m_strFieldEndox[paziente_nominativo_cn].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_nominativo_cn].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_nominativo_nc].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_nominativo_nc].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_388);
	CFieldDlg::m_strFieldEndox[paziente_nominativo_nc].sReport = "Anagrafico.NominativoNC"; // Nominativo (nome + cognome)
	CFieldDlg::m_strFieldEndox[paziente_nominativo_nc].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_nominativo_nc].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_sesso].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_sesso].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_50);
	CFieldDlg::m_strFieldEndox[paziente_sesso].sReport = "Anagrafico.K"; // Sesso
	CFieldDlg::m_strFieldEndox[paziente_sesso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_sesso].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_natoil].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_natoil].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_03);
	CFieldDlg::m_strFieldEndox[paziente_natoil].sReport = "Anagrafico.C"; // Nato il
	CFieldDlg::m_strFieldEndox[paziente_natoil].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_natoil].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_natoa].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_natoa].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_51);
	CFieldDlg::m_strFieldEndox[paziente_natoa].sReport = "Anagrafico.M"; // Nato a
	CFieldDlg::m_strFieldEndox[paziente_natoa].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_natoa].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_professione].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_professione].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_52);
	CFieldDlg::m_strFieldEndox[paziente_professione].sReport = "Anagrafico.N"; // Professione
	CFieldDlg::m_strFieldEndox[paziente_professione].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_professione].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_via].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_via].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_04);
	CFieldDlg::m_strFieldEndox[paziente_via].sReport = "Anagrafico.D"; // Via
	CFieldDlg::m_strFieldEndox[paziente_via].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_via].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_citta].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_citta].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_06);
	CFieldDlg::m_strFieldEndox[paziente_citta].sReport = "Anagrafico.F"; // Città
	CFieldDlg::m_strFieldEndox[paziente_citta].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_citta].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_cap].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_cap].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_05);
	CFieldDlg::m_strFieldEndox[paziente_cap].sReport = "Anagrafico.E"; // CAP
	CFieldDlg::m_strFieldEndox[paziente_cap].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_cap].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_provincia].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_provincia].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_07);
	CFieldDlg::m_strFieldEndox[paziente_provincia].sReport = "Anagrafico.G"; // Provincia
	CFieldDlg::m_strFieldEndox[paziente_provincia].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_provincia].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_recapito].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_recapito].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_122);
	CFieldDlg::m_strFieldEndox[paziente_recapito].sReport = "Anagrafico.Recapito"; // Recapito
	CFieldDlg::m_strFieldEndox[paziente_recapito].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_recapito].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_telefono1].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_telefono1].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_08);
	CFieldDlg::m_strFieldEndox[paziente_telefono1].sReport = "Anagrafico.H"; // Telefono 1
	CFieldDlg::m_strFieldEndox[paziente_telefono1].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_telefono1].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_telefono2].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_telefono2].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_55);
	CFieldDlg::m_strFieldEndox[paziente_telefono2].sReport = "Anagrafico.Q"; // Telefono 2
	CFieldDlg::m_strFieldEndox[paziente_telefono2].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_telefono2].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_fax].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_fax].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_56);
	CFieldDlg::m_strFieldEndox[paziente_fax].sReport = "Anagrafico.R"; // Fax
	CFieldDlg::m_strFieldEndox[paziente_fax].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_fax].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_cellulare1].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_cellulare1].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_57);
	CFieldDlg::m_strFieldEndox[paziente_cellulare1].sReport = "Anagrafico.S"; // Cellulare 1
	CFieldDlg::m_strFieldEndox[paziente_cellulare1].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_cellulare1].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_cellulare2].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_cellulare2].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_58);
	CFieldDlg::m_strFieldEndox[paziente_cellulare2].sReport = "Anagrafico.T"; // Cellulare 2
	CFieldDlg::m_strFieldEndox[paziente_cellulare2].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_cellulare2].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_email].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_email].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_59);
	CFieldDlg::m_strFieldEndox[paziente_email].sReport = "Anagrafico.U"; // Email
	CFieldDlg::m_strFieldEndox[paziente_email].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_email].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_medicocurante].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_medicocurante].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_10);
	CFieldDlg::m_strFieldEndox[paziente_medicocurante].sReport = "Anagrafico.L"; // Medico curante
	CFieldDlg::m_strFieldEndox[paziente_medicocurante].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_medicocurante].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_medicotelefono].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_medicotelefono].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_60);
	CFieldDlg::m_strFieldEndox[paziente_medicotelefono].sReport = "Anagrafico.V"; // Telefono medico curante
	CFieldDlg::m_strFieldEndox[paziente_medicotelefono].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_medicotelefono].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_medicoindirizzo].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_medicoindirizzo].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_61);
	CFieldDlg::m_strFieldEndox[paziente_medicoindirizzo].sReport = "Anagrafico.W"; // Indirizzo medico curante
	CFieldDlg::m_strFieldEndox[paziente_medicoindirizzo].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_medicoindirizzo].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_medicoemail].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_medicoemail].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_466);
	CFieldDlg::m_strFieldEndox[paziente_medicoemail].sReport = "Anagrafico.MedicoEmail"; // Email medico curante
	CFieldDlg::m_strFieldEndox[paziente_medicoemail].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_medicoemail].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_dasegnalare].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_dasegnalare].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_62);
	CFieldDlg::m_strFieldEndox[paziente_dasegnalare].sReport = "Anagrafico.Y"; // Da segnalare
	CFieldDlg::m_strFieldEndox[paziente_dasegnalare].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_dasegnalare].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_codicecliente].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_codicecliente].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_131);
	CFieldDlg::m_strFieldEndox[paziente_codicecliente].sReport = "Anagrafico.CodiceCliente";
	CFieldDlg::m_strFieldEndox[paziente_codicecliente].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_codicecliente].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_cognome2].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_cognome2].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_132);
	CFieldDlg::m_strFieldEndox[paziente_cognome2].sReport = "Anagrafico.Cognome2";
	CFieldDlg::m_strFieldEndox[paziente_cognome2].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_cognome2].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_nominativopadre].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_nominativopadre].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_133);
	CFieldDlg::m_strFieldEndox[paziente_nominativopadre].sReport = "Anagrafico.NominativoPadre";
	CFieldDlg::m_strFieldEndox[paziente_nominativopadre].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_nominativopadre].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_nominativomadre].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_nominativomadre].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_134);
	CFieldDlg::m_strFieldEndox[paziente_nominativomadre].sReport = "Anagrafico.NominativoMadre";
	CFieldDlg::m_strFieldEndox[paziente_nominativomadre].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_nominativomadre].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_eta].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_eta].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_327);
	CFieldDlg::m_strFieldEndox[paziente_eta].sReport = "Anagrafico.EtaPaziente";
	CFieldDlg::m_strFieldEndox[paziente_eta].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_eta].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_eta_soloanni].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_eta_soloanni].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_435);
	CFieldDlg::m_strFieldEndox[paziente_eta_soloanni].sReport = "Anagrafico.EtaPazienteSoloAnni";
	CFieldDlg::m_strFieldEndox[paziente_eta_soloanni].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_eta_soloanni].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_indirizzoricetta].lID = -1;
	CFieldDlg::m_strFieldEndox[paziente_indirizzoricetta].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_389);
	CFieldDlg::m_strFieldEndox[paziente_indirizzoricetta].sReport = "Anagrafico.IndirizzoRicetta";
	CFieldDlg::m_strFieldEndox[paziente_indirizzoricetta].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_indirizzoricetta].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_assiden].lID = EDT_ASSIDEN;
	CFieldDlg::m_strFieldEndox[paziente_assiden].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_418);
	CFieldDlg::m_strFieldEndox[paziente_assiden].sReport = "Paziente.Assiden";
	CFieldDlg::m_strFieldEndox[paziente_assiden].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_assiden].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[paziente_codalfa].lID = EDT_CODALFA;
	CFieldDlg::m_strFieldEndox[paziente_codalfa].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_494);
	CFieldDlg::m_strFieldEndox[paziente_codalfa].sReport = "Paziente.CodAlfa";
	CFieldDlg::m_strFieldEndox[paziente_codalfa].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_codalfa].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[anamnesi_fumo].lID = -1;
	CFieldDlg::m_strFieldEndox[anamnesi_fumo].sReport = "Anamnesi.Fumo"; // Fumo
	CFieldDlg::m_strFieldEndox[anamnesi_fumo].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[anamnesi_fumo].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[anamnesi_sigarette].lID = -1;
	CFieldDlg::m_strFieldEndox[anamnesi_sigarette].sReport = "Anamnesi.Sigarette"; // Sigarette
	CFieldDlg::m_strFieldEndox[anamnesi_sigarette].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[anamnesi_sigarette].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[anamnesi_alcol].lID = -1;
	CFieldDlg::m_strFieldEndox[anamnesi_alcol].sReport = "Anamnesi.Alcool"; // Alcool
	CFieldDlg::m_strFieldEndox[anamnesi_alcol].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[anamnesi_alcol].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[anamnesi_superalcolici].lID = -1;
	CFieldDlg::m_strFieldEndox[anamnesi_superalcolici].sReport = "Anamnesi.Superalcolici"; // Superalcolici
	CFieldDlg::m_strFieldEndox[anamnesi_superalcolici].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[anamnesi_superalcolici].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[anamnesi_caffe].lID = -1;
	CFieldDlg::m_strFieldEndox[anamnesi_caffe].sReport = "Anamnesi.Caffe"; // Caffè
	CFieldDlg::m_strFieldEndox[anamnesi_caffe].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[anamnesi_caffe].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[anamnesi_farmaci].lID = SUB_ABITUDINI;
	CFieldDlg::m_strFieldEndox[anamnesi_farmaci].sReport = "Anamnesi.Farmaci"; // Farmaci
	CFieldDlg::m_strFieldEndox[anamnesi_farmaci].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[anamnesi_farmaci].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[anamnesi_assunzione].lID = -1;
	CFieldDlg::m_strFieldEndox[anamnesi_assunzione].sReport = "Anamnesi.Assunzione"; // Assunzione
	CFieldDlg::m_strFieldEndox[anamnesi_assunzione].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[anamnesi_assunzione].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[anamnesi_peso].lID = -1;
	CFieldDlg::m_strFieldEndox[anamnesi_peso].sReport = "Anamnesi.Peso";
	CFieldDlg::m_strFieldEndox[anamnesi_peso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[anamnesi_peso].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[anamnesi_altezza].lID = -1;
	CFieldDlg::m_strFieldEndox[anamnesi_altezza].sReport = "Anamnesi.Altezza";
	CFieldDlg::m_strFieldEndox[anamnesi_altezza].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[anamnesi_altezza].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[anamnesi_bmi].lID = -1;
	CFieldDlg::m_strFieldEndox[anamnesi_bmi].sReport = "Anamnesi.BMI";
	CFieldDlg::m_strFieldEndox[anamnesi_bmi].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[anamnesi_bmi].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[anamnesi_bsa].lID = -1;
	CFieldDlg::m_strFieldEndox[anamnesi_bsa].sReport = "Anamnesi.BSA";
	CFieldDlg::m_strFieldEndox[anamnesi_bsa].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[anamnesi_bsa].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_progressivo].lID = EDT_PROGRESSIVO;
	CFieldDlg::m_strFieldEndox[preliminari_progressivo].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_11);
	CFieldDlg::m_strFieldEndox[preliminari_progressivo].sReport = "Scheda.Progressivo"; // Progressivo esame
	CFieldDlg::m_strFieldEndox[preliminari_progressivo].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_progressivo].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[preliminari_data].lID = EDT_DATAESAME;
	CFieldDlg::m_strFieldEndox[preliminari_data].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_13);
	CFieldDlg::m_strFieldEndox[preliminari_data].sReport = "Scheda.Data"; // data esame
	CFieldDlg::m_strFieldEndox[preliminari_data].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_data].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_data_eng].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_data_eng].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_438);
	CFieldDlg::m_strFieldEndox[preliminari_data_eng].sReport = "Scheda.DataEng"; // data esame, formato mm/dd/yyyy //
	CFieldDlg::m_strFieldEndox[preliminari_data_eng].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_data_eng].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_ora].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_ora].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_337);
	CFieldDlg::m_strFieldEndox[preliminari_ora].sReport = "Scheda.Ora"; // ora esame
	CFieldDlg::m_strFieldEndox[preliminari_ora].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_ora].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_tipoesame].lID = CMB_TIPOESAME;
	CFieldDlg::m_strFieldEndox[preliminari_tipoesame].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_12);
	CFieldDlg::m_strFieldEndox[preliminari_tipoesame].sReport = "Scheda.Tipo"; // Tipo esame
	CFieldDlg::m_strFieldEndox[preliminari_tipoesame].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_tipoesame].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[preliminari_tipoesame_codice].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_tipoesame_codice].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_299);
	CFieldDlg::m_strFieldEndox[preliminari_tipoesame_codice].sReport = "Scheda.CodiceTipoEsame"; // Codice del tipo esame
	CFieldDlg::m_strFieldEndox[preliminari_tipoesame_codice].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_tipoesame_codice].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[preliminari_tipoesame_colore].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_tipoesame_colore].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_492);
	CFieldDlg::m_strFieldEndox[preliminari_tipoesame_colore].sReport = "Scheda.ColoreTipoEsame"; // Colore del tipo esame
	CFieldDlg::m_strFieldEndox[preliminari_tipoesame_colore].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_tipoesame_colore].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[preliminari_sedeesame].lID = EDT_SEDEESAME;
	CFieldDlg::m_strFieldEndox[preliminari_sedeesame].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_124);
	CFieldDlg::m_strFieldEndox[preliminari_sedeesame].sReport = "Scheda.SedeEsame"; // Sede esame
	CFieldDlg::m_strFieldEndox[preliminari_sedeesame].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_sedeesame].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[preliminari_salaesame].lID = EDT_SALAESAME;
	CFieldDlg::m_strFieldEndox[preliminari_salaesame].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_298);
	CFieldDlg::m_strFieldEndox[preliminari_salaesame].sReport = "Scheda.SalaEsame"; // Sala esame
	CFieldDlg::m_strFieldEndox[preliminari_salaesame].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_salaesame].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[preliminari_progressivoannuale].lID = EDT_PROGRESSIVOANNO;
	CFieldDlg::m_strFieldEndox[preliminari_progressivoannuale].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_70);
	CFieldDlg::m_strFieldEndox[preliminari_progressivoannuale].sReport = "Scheda.ProgressivoPerAnno"; // Progressivo per anno
	CFieldDlg::m_strFieldEndox[preliminari_progressivoannuale].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_progressivoannuale].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_codiceprenotazione].lID = EDT_CODICEPRENOTAZIONE;
	CFieldDlg::m_strFieldEndox[preliminari_codiceprenotazione].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_500);
	CFieldDlg::m_strFieldEndox[preliminari_codiceprenotazione].sReport = "Scheda.CodicePrenotazione"; // Codice prenotazione
	CFieldDlg::m_strFieldEndox[preliminari_codiceprenotazione].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_codiceprenotazione].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_internoesterno].lID = SUB_INVIANTE;
	CFieldDlg::m_strFieldEndox[preliminari_internoesterno].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_16);
	CFieldDlg::m_strFieldEndox[preliminari_internoesterno].sReport = "Scheda.Provenienza"; // Provenienza
	CFieldDlg::m_strFieldEndox[preliminari_internoesterno].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_internoesterno].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[preliminari_inviante1].lID = EDT_INVIANTE1;
	CFieldDlg::m_strFieldEndox[preliminari_inviante1].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_112);
	CFieldDlg::m_strFieldEndox[preliminari_inviante1].sReport = "Scheda.Inviante1";
	CFieldDlg::m_strFieldEndox[preliminari_inviante1].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_inviante1].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[preliminari_inviante2].lID = EDT_INVIANTE2;
	CFieldDlg::m_strFieldEndox[preliminari_inviante2].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_113);
	CFieldDlg::m_strFieldEndox[preliminari_inviante2].sReport = "Scheda.Inviante2";
	CFieldDlg::m_strFieldEndox[preliminari_inviante2].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_inviante2].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[preliminari_inviante3].lID = EDT_INVIANTE3;
	CFieldDlg::m_strFieldEndox[preliminari_inviante3].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_114);
	CFieldDlg::m_strFieldEndox[preliminari_inviante3].sReport = "Scheda.Inviante3";
	CFieldDlg::m_strFieldEndox[preliminari_inviante3].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_inviante3].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[preliminari_inviante_codice].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_inviante_codice].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_300);
	CFieldDlg::m_strFieldEndox[preliminari_inviante_codice].sReport = "Scheda.CodiceInviante";
	CFieldDlg::m_strFieldEndox[preliminari_inviante_codice].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_inviante_codice].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[preliminari_medico1].lID = CMB_MEDICO1;
	CFieldDlg::m_strFieldEndox[preliminari_medico1].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_14);
	CFieldDlg::m_strFieldEndox[preliminari_medico1].sReport = "Scheda.Medico"; // Medico 1
	CFieldDlg::m_strFieldEndox[preliminari_medico1].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_medico1].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma0].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma0].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_338);
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma0].sReport = "Scheda.Medico.Firma0";
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma0].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma0].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma1].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma1].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_339);
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma1].sReport = "Scheda.Medico.Firma1";
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma1].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma1].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma2].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma2].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_340);
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma2].sReport = "Scheda.Medico.Firma2";
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma2].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma2].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma3].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma3].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_341);
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma3].sReport = "Scheda.Medico.Firma3";
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma3].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma3].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma4].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma4].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_342);
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma4].sReport = "Scheda.Medico.Firma4";
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma4].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma4].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma5].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma5].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_343);
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma5].sReport = "Scheda.Medico.Firma5";
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma5].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma5].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma6].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma6].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_344);
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma6].sReport = "Scheda.Medico.Firma6";
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma6].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma6].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma7].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma7].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_345);
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma7].sReport = "Scheda.Medico.Firma7";
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma7].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma7].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma8].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma8].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_346);
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma8].sReport = "Scheda.Medico.Firma8";
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma8].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma8].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma9].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma9].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_347);
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma9].sReport = "Scheda.Medico.Firma9";
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma9].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_medico1_firma9].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_medico1_immaginefirma].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_medico1_immaginefirma].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_544);
	CFieldDlg::m_strFieldEndox[preliminari_medico1_immaginefirma].sReport = "ImmagineFirma.Medico1";
	CFieldDlg::m_strFieldEndox[preliminari_medico1_immaginefirma].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_medico1_immaginefirma].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[preliminari_medico2].lID = CMB_MEDICO2;
	CFieldDlg::m_strFieldEndox[preliminari_medico2].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_15);
	CFieldDlg::m_strFieldEndox[preliminari_medico2].sReport = "Scheda.Assistente"; // Medico 2
	CFieldDlg::m_strFieldEndox[preliminari_medico2].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_medico2].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma0].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma0].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_422);
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma0].sReport = "Scheda.Assistente.Firma0";
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma0].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma0].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma1].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma1].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_423);
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma1].sReport = "Scheda.Assistente.Firma1";
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma1].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma1].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma2].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma2].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_424);
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma2].sReport = "Scheda.Assistente.Firma2";
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma2].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma2].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma3].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma3].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_425);
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma3].sReport = "Scheda.Assistente.Firma3";
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma3].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma3].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma4].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma4].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_426);
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma4].sReport = "Scheda.Assistente.Firma4";
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma4].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma4].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma5].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma5].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_427);
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma5].sReport = "Scheda.Assistente.Firma5";
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma5].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma5].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma6].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma6].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_428);
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma6].sReport = "Scheda.Assistente.Firma6";
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma6].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma6].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma7].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma7].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_429);
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma7].sReport = "Scheda.Assistente.Firma7";
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma7].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma7].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma8].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma8].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_430);
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma8].sReport = "Scheda.Assistente.Firma8";
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma8].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma8].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma9].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma9].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_431);
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma9].sReport = "Scheda.Assistente.Firma9";
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma9].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_medico2_firma9].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_medico2_immaginefirma].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_medico2_immaginefirma].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_545);
	CFieldDlg::m_strFieldEndox[preliminari_medico2_immaginefirma].sReport = "ImmagineFirma.Medico2";
	CFieldDlg::m_strFieldEndox[preliminari_medico2_immaginefirma].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_medico2_immaginefirma].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[preliminari_infermiere1].lID = CMB_INFERMIERE1;
	CFieldDlg::m_strFieldEndox[preliminari_infermiere1].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_46);
	CFieldDlg::m_strFieldEndox[preliminari_infermiere1].sReport = "Infermiere1"; // Infermiere 1
	CFieldDlg::m_strFieldEndox[preliminari_infermiere1].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_infermiere1].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_infermiere1_matricola].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_infermiere1_matricola].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_464);
	CFieldDlg::m_strFieldEndox[preliminari_infermiere1_matricola].sReport = "Infermiere1.Matricola"; // Matricola Infermiere 1
	CFieldDlg::m_strFieldEndox[preliminari_infermiere1_matricola].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_infermiere1_matricola].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_infermiere2].lID = CMB_INFERMIERE2;
	CFieldDlg::m_strFieldEndox[preliminari_infermiere2].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_47);
	CFieldDlg::m_strFieldEndox[preliminari_infermiere2].sReport = "Infermiere2"; // Infermiere 2
	CFieldDlg::m_strFieldEndox[preliminari_infermiere2].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_infermiere2].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_infermiere2_matricola].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_infermiere2_matricola].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_465);
	CFieldDlg::m_strFieldEndox[preliminari_infermiere2_matricola].sReport = "Infermiere2.Matricola"; // Matricola Infermiere 2
	CFieldDlg::m_strFieldEndox[preliminari_infermiere2_matricola].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_infermiere2_matricola].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_anestesista].lID = EDT_ANESTESISTA;
	CFieldDlg::m_strFieldEndox[preliminari_anestesista].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_77);
	CFieldDlg::m_strFieldEndox[preliminari_anestesista].sReport = "Scheda.Anestesista"; // Anestesista
	CFieldDlg::m_strFieldEndox[preliminari_anestesista].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_anestesista].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[preliminari_camera].lID = EDT_CAMERA;
	CFieldDlg::m_strFieldEndox[preliminari_camera].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_18);
	CFieldDlg::m_strFieldEndox[preliminari_camera].sReport = "Scheda.Camera"; // Camera
	CFieldDlg::m_strFieldEndox[preliminari_camera].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_camera].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[preliminari_indicazioni].lID = EDT_INDICAZIONI;
	CFieldDlg::m_strFieldEndox[preliminari_indicazioni].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_32);
	CFieldDlg::m_strFieldEndox[preliminari_indicazioni].sReport = "Scheda.Indicazioni"; // Indicazioni
	CFieldDlg::m_strFieldEndox[preliminari_indicazioni].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_indicazioni].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_indicazioni_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[preliminari_indicazioni_grande].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_354);
	CFieldDlg::m_strFieldEndox[preliminari_indicazioni_grande].sReport = "Scheda.IndicazioniLungo"; // Indicazioni Lungo
	CFieldDlg::m_strFieldEndox[preliminari_indicazioni_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_indicazioni_grande].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[preliminari_farmacotrial].lID = EDT_FARMACOTRIAL;
	CFieldDlg::m_strFieldEndox[preliminari_farmacotrial].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_33);
	CFieldDlg::m_strFieldEndox[preliminari_farmacotrial].sReport = "Scheda.FarmacoTrial"; // Farmaco trial
	CFieldDlg::m_strFieldEndox[preliminari_farmacotrial].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_farmacotrial].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[preliminari_premedicazioni].lID = EDT_PREMEDICAZIONI;
	CFieldDlg::m_strFieldEndox[preliminari_premedicazioni].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_37);
	CFieldDlg::m_strFieldEndox[preliminari_premedicazioni].sReport = "Scheda.Premedicazioni"; // Premedicazioni
	CFieldDlg::m_strFieldEndox[preliminari_premedicazioni].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_premedicazioni].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[esame_procdiag_fisso].lID = EDT_DIAGNOSTICHE;
	CFieldDlg::m_strFieldEndox[esame_procdiag_fisso].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_25);
	CFieldDlg::m_strFieldEndox[esame_procdiag_fisso].sReport = "Scheda.ProcDiag"; // Procedure diagnostiche
	CFieldDlg::m_strFieldEndox[esame_procdiag_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esame_procdiag_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[esame_procdiag_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[esame_procdiag_grande].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_328);
	CFieldDlg::m_strFieldEndox[esame_procdiag_grande].sReport = "Scheda.ProcDiagGrande"; // Procedure diagnostiche
	CFieldDlg::m_strFieldEndox[esame_procdiag_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esame_procdiag_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[esame_proctera_fisso].lID = EDT_TERAPEUTICHE;
	CFieldDlg::m_strFieldEndox[esame_proctera_fisso].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_26);
	CFieldDlg::m_strFieldEndox[esame_proctera_fisso].sReport = "Scheda.ProcTera"; // Procedure terapeutiche
	CFieldDlg::m_strFieldEndox[esame_proctera_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esame_proctera_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[esame_proctera_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[esame_proctera_grande].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_329);
	CFieldDlg::m_strFieldEndox[esame_proctera_grande].sReport = "Scheda.ProcTeraGrande"; // Procedure terapeutiche
	CFieldDlg::m_strFieldEndox[esame_proctera_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esame_proctera_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[esame_condottofino].lID = EDT_CONDOTTOFINO;
	CFieldDlg::m_strFieldEndox[esame_condottofino].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_30);
	CFieldDlg::m_strFieldEndox[esame_condottofino].sReport = "Scheda.Estensione"; // Esame condotto fino
	CFieldDlg::m_strFieldEndox[esame_condottofino].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esame_condottofino].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[esame_firma_smartcard_utente].lID = -1;
	CFieldDlg::m_strFieldEndox[esame_firma_smartcard_utente].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_326);
	CFieldDlg::m_strFieldEndox[esame_firma_smartcard_utente].sReport = "Scheda.UtenteSmartCard";
	CFieldDlg::m_strFieldEndox[esame_firma_smartcard_utente].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esame_firma_smartcard_utente].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[esami_firma_smartcard_numero].lID = -1;
	CFieldDlg::m_strFieldEndox[esami_firma_smartcard_numero].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_462);
	CFieldDlg::m_strFieldEndox[esami_firma_smartcard_numero].sReport = "Scheda.NumeroSmartCard";
	CFieldDlg::m_strFieldEndox[esami_firma_smartcard_numero].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esami_firma_smartcard_numero].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[esami_firma_smartcard_entecertificato].lID = -1;
	CFieldDlg::m_strFieldEndox[esami_firma_smartcard_entecertificato].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_463);
	CFieldDlg::m_strFieldEndox[esami_firma_smartcard_entecertificato].sReport = "Scheda.EnteSmartCard";
	CFieldDlg::m_strFieldEndox[esami_firma_smartcard_entecertificato].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esami_firma_smartcard_entecertificato].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[esame_firma_sostituzione_motivo].lID = -1;
	CFieldDlg::m_strFieldEndox[esame_firma_sostituzione_motivo].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_454);
	CFieldDlg::m_strFieldEndox[esame_firma_sostituzione_motivo].sReport = "Scheda.FirmaMotivoSostituzione";
	CFieldDlg::m_strFieldEndox[esame_firma_sostituzione_motivo].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esame_firma_sostituzione_motivo].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[esame_firma_annullamento_idprecedente].lID = -1;
	CFieldDlg::m_strFieldEndox[esame_firma_annullamento_idprecedente].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_455);
	CFieldDlg::m_strFieldEndox[esame_firma_annullamento_idprecedente].sReport = "Scheda.FirmaAnnullamentoIdPrecedente";
	CFieldDlg::m_strFieldEndox[esame_firma_annullamento_idprecedente].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esame_firma_annullamento_idprecedente].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[esame_firma_annullamento_dataprecedente].lID = -1;
	CFieldDlg::m_strFieldEndox[esame_firma_annullamento_dataprecedente].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_456);
	CFieldDlg::m_strFieldEndox[esame_firma_annullamento_dataprecedente].sReport = "Scheda.FirmaAnnullamentoDataPrecedente";
	CFieldDlg::m_strFieldEndox[esame_firma_annullamento_dataprecedente].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esame_firma_annullamento_dataprecedente].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[esame_firma_annullamento_motivo].lID = -1;
	CFieldDlg::m_strFieldEndox[esame_firma_annullamento_motivo].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_457);
	CFieldDlg::m_strFieldEndox[esame_firma_annullamento_motivo].sReport = "Scheda.FirmaAnnullamentoMotivo";
	CFieldDlg::m_strFieldEndox[esame_firma_annullamento_motivo].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esame_firma_annullamento_motivo].bImageNT = FALSE;

	/*
	CFieldDlg::m_strFieldEndox[esame_firma_versione_referto].lID = -1;
	CFieldDlg::m_strFieldEndox[esame_firma_versione_referto].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_499);
	CFieldDlg::m_strFieldEndox[esame_firma_versione_referto].sReport = "Scheda.FirmaVersioneReferto";
	CFieldDlg::m_strFieldEndox[esame_firma_versione_referto].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esame_firma_versione_referto].bImageNT = FALSE;
	*/

	CFieldDlg::m_strFieldEndox[altridati_valutazione].lID = EDT_VALUTAZIONE;
	CFieldDlg::m_strFieldEndox[altridati_valutazione].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_42);
	CFieldDlg::m_strFieldEndox[altridati_valutazione].sReport = "Scheda.ValutazioneEsame"; // Valutazione
	CFieldDlg::m_strFieldEndox[altridati_valutazione].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[altridati_valutazione].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[altridati_prossimocontrollo].lID = EDT_PROSSIMO;
	CFieldDlg::m_strFieldEndox[altridati_prossimocontrollo].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_29);
	CFieldDlg::m_strFieldEndox[altridati_prossimocontrollo].sReport = "Scheda.DataControllo"; // Prossimo controllo
	CFieldDlg::m_strFieldEndox[altridati_prossimocontrollo].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[altridati_prossimocontrollo].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[altridati_complicanze].lID = EDT_COMPLICANZE;
	CFieldDlg::m_strFieldEndox[altridati_complicanze].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_43);
	CFieldDlg::m_strFieldEndox[altridati_complicanze].sReport = "Scheda.Complicanze"; // Complicanze
	CFieldDlg::m_strFieldEndox[altridati_complicanze].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[altridati_complicanze].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[altridati_provvedimenti].lID = EDT_COMPLICANZEPROVVEDIMENTI;
	CFieldDlg::m_strFieldEndox[altridati_provvedimenti].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_74);
	CFieldDlg::m_strFieldEndox[altridati_provvedimenti].sReport = "Scheda.ComplicanzeProvvedimenti"; // Provvedimenti
	CFieldDlg::m_strFieldEndox[altridati_provvedimenti].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[altridati_provvedimenti].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[altridati_terapia].lID = EDT_COMPLICANZETERAPIA;
	CFieldDlg::m_strFieldEndox[altridati_terapia].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_73);
	CFieldDlg::m_strFieldEndox[altridati_terapia].sReport = "Scheda.ComplicanzeTerapia"; // Terapia complicanze
	CFieldDlg::m_strFieldEndox[altridati_terapia].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[altridati_terapia].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[altridati_esito].lID = EDT_COMPLICANZEESITO;
	CFieldDlg::m_strFieldEndox[altridati_esito].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_75);
	CFieldDlg::m_strFieldEndox[altridati_esito].sReport = "Scheda.ComplicanzeEsito"; // Esito complicanze
	CFieldDlg::m_strFieldEndox[altridati_esito].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[altridati_esito].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[altridati_tipovisita].lID = EDT_TIPOVISITA;
	CFieldDlg::m_strFieldEndox[altridati_tipovisita].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_35);
	CFieldDlg::m_strFieldEndox[altridati_tipovisita].sReport = "Scheda.NumeroControllo"; // Visita di tipo
	CFieldDlg::m_strFieldEndox[altridati_tipovisita].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[altridati_tipovisita].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[altridati_studio].lID = EDT_STUDIO;
	CFieldDlg::m_strFieldEndox[altridati_studio].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_34);
	CFieldDlg::m_strFieldEndox[altridati_studio].sReport = "Scheda.Studio"; // Studio
	CFieldDlg::m_strFieldEndox[altridati_studio].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[altridati_studio].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[altridati_quadro].lID = EDT_QUADRO;
	CFieldDlg::m_strFieldEndox[altridati_quadro].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_45);
	CFieldDlg::m_strFieldEndox[altridati_quadro].sReport = "Scheda.Quadro"; // Quadro
	CFieldDlg::m_strFieldEndox[altridati_quadro].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[altridati_quadro].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[altridati_guarigione].lID = EDT_GUARIGIONE;
	CFieldDlg::m_strFieldEndox[altridati_guarigione].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_44);
	CFieldDlg::m_strFieldEndox[altridati_guarigione].sReport = "Scheda.Guarigione"; // Guarigione
	CFieldDlg::m_strFieldEndox[altridati_guarigione].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[altridati_guarigione].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[altridati_durata].lID = EDT_DURATA;
	CFieldDlg::m_strFieldEndox[altridati_durata].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_23);
	CFieldDlg::m_strFieldEndox[altridati_durata].sReport = "Scheda.Durata"; // Durata esame
	CFieldDlg::m_strFieldEndox[altridati_durata].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[altridati_durata].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[altridati_difficolta].lID = EDT_DIFFICOLTA;
	CFieldDlg::m_strFieldEndox[altridati_difficolta].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_24);
	CFieldDlg::m_strFieldEndox[altridati_difficolta].sReport = "Scheda.Difficolta"; // Difficoltà esame
	CFieldDlg::m_strFieldEndox[altridati_difficolta].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[altridati_difficolta].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[altridati_terapiaconsigliata].lID = EDT_TERAPIACONSIGLIATA;
	CFieldDlg::m_strFieldEndox[altridati_terapiaconsigliata].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_20);
	CFieldDlg::m_strFieldEndox[altridati_terapiaconsigliata].sReport = "Scheda.Terapia"; // Terapia consigliata
	CFieldDlg::m_strFieldEndox[altridati_terapiaconsigliata].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[altridati_terapiaconsigliata].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[altridati_strumenti].lID = EDT_STRUMENTI;
	CFieldDlg::m_strFieldEndox[altridati_strumenti].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_38);
	CFieldDlg::m_strFieldEndox[altridati_strumenti].sReport = "Scheda.Strumenti"; // Strumenti
	CFieldDlg::m_strFieldEndox[altridati_strumenti].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[altridati_strumenti].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[altridati_accessori].lID = EDT_ACCESSORI;
	CFieldDlg::m_strFieldEndox[altridati_accessori].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_39);
	CFieldDlg::m_strFieldEndox[altridati_accessori].sReport = "Scheda.Accessori"; // Accessori
	CFieldDlg::m_strFieldEndox[altridati_accessori].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[altridati_accessori].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[altridati_note].lID = EDT_NOTE;
	CFieldDlg::m_strFieldEndox[altridati_note].sCombo = theApp.GetMessageString(IDS_NOTE);
	CFieldDlg::m_strFieldEndox[altridati_note].sReport = "Scheda.Appunti"; // Note
	CFieldDlg::m_strFieldEndox[altridati_note].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[altridati_note].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[altridati_biopsie].lID = -1;
	CFieldDlg::m_strFieldEndox[altridati_biopsie].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_78);
	CFieldDlg::m_strFieldEndox[altridati_biopsie].sReport = "Scheda.Biopsie"; // Eseguita biopsia
	CFieldDlg::m_strFieldEndox[altridati_biopsie].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[altridati_biopsie].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[referto_referto_fisso].lID = SUB_REFERTO;
	CFieldDlg::m_strFieldEndox[referto_referto_fisso].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_22);
	CFieldDlg::m_strFieldEndox[referto_referto_fisso].sReport = "Scheda.Referto"; // Referto di dimensioni fisse
	CFieldDlg::m_strFieldEndox[referto_referto_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[referto_referto_fisso].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[referto_referto_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[referto_referto_grande].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_182);
	CFieldDlg::m_strFieldEndox[referto_referto_grande].sReport = "Scheda.RefertoGrande"; // Referto che si può anche ingrandire
	CFieldDlg::m_strFieldEndox[referto_referto_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[referto_referto_grande].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[libero_riferimento].lID = EDT_RIFERIMENTO;
	CFieldDlg::m_strFieldEndox[libero_riferimento].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_76);
	CFieldDlg::m_strFieldEndox[libero_riferimento].sReport = "Scheda.Riferimento"; // Riferimento
	CFieldDlg::m_strFieldEndox[libero_riferimento].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_riferimento].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_000].lID = EDT_LIBERO000;
	CFieldDlg::m_strFieldEndox[libero_000].sReport = "Scheda.Testo15"; // Campo libero 1
	CFieldDlg::m_strFieldEndox[libero_000].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_000].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[libero_001].lID = EDT_LIBERO001;
	CFieldDlg::m_strFieldEndox[libero_001].sReport = "Scheda.Testo16"; // Campo libero 2
	CFieldDlg::m_strFieldEndox[libero_001].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_001].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[libero_002].lID = EDT_LIBERO002;
	CFieldDlg::m_strFieldEndox[libero_002].sReport = "Scheda.Testo17"; // Campo libero 3
	CFieldDlg::m_strFieldEndox[libero_002].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_002].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[libero_003].lID = EDT_LIBERO003;
	CFieldDlg::m_strFieldEndox[libero_003].sReport = "Scheda.Testo18"; // Campo libero 4
	CFieldDlg::m_strFieldEndox[libero_003].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_003].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[libero_004].lID = EDT_LIBERO004;
	CFieldDlg::m_strFieldEndox[libero_004].sReport = "Scheda.Testo19"; // Campo libero 5
	CFieldDlg::m_strFieldEndox[libero_004].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_004].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[libero_005].lID = EDT_LIBERO005;
	CFieldDlg::m_strFieldEndox[libero_005].sReport = "Scheda.Testo20"; // Campo libero 6
	CFieldDlg::m_strFieldEndox[libero_005].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_005].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[libero_006].lID = EDT_LIBERO006;
	CFieldDlg::m_strFieldEndox[libero_006].sReport = "Scheda.Testo21"; // Campo libero 7
	CFieldDlg::m_strFieldEndox[libero_006].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_006].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[libero_007].lID = EDT_LIBERO007;
	CFieldDlg::m_strFieldEndox[libero_007].sReport = "Scheda.Testo22"; // Campo libero 8
	CFieldDlg::m_strFieldEndox[libero_007].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_007].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[libero_008].lID = EDT_LIBERO008;
	CFieldDlg::m_strFieldEndox[libero_008].sReport = "Scheda.Testo23"; // Campo libero 9
	CFieldDlg::m_strFieldEndox[libero_008].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_008].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[libero_009].lID = EDT_LIBERO009;
	CFieldDlg::m_strFieldEndox[libero_009].sReport = "Scheda.Testo24"; // Campo libero 10
	CFieldDlg::m_strFieldEndox[libero_009].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_009].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[libero_010].lID = EDT_LIBERO010;
	CFieldDlg::m_strFieldEndox[libero_010].sReport = "Scheda.Testo25"; // Campo libero 11
	CFieldDlg::m_strFieldEndox[libero_010].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_010].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[libero_011].lID = EDT_LIBERO011;
	CFieldDlg::m_strFieldEndox[libero_011].sReport = "Scheda.Testo26"; // Campo libero 12
	CFieldDlg::m_strFieldEndox[libero_011].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_011].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[libero_012].lID = EDT_LIBERO012;
	CFieldDlg::m_strFieldEndox[libero_012].sReport = "Scheda.Testo27"; // Campo libero 13
	CFieldDlg::m_strFieldEndox[libero_012].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_012].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[libero_013].lID = EDT_LIBERO013;
	CFieldDlg::m_strFieldEndox[libero_013].sReport = "Scheda.Testo28"; // Campo libero 14
	CFieldDlg::m_strFieldEndox[libero_013].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_013].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[libero_014].lID = EDT_LIBERO014;
	CFieldDlg::m_strFieldEndox[libero_014].sReport = "Scheda.Testo29"; // Campo libero 15
	CFieldDlg::m_strFieldEndox[libero_014].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_014].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[libero_015].lID = EDT_LIBERO015;
	CFieldDlg::m_strFieldEndox[libero_015].sReport = "Scheda.Testo30"; // Campo libero 16
	CFieldDlg::m_strFieldEndox[libero_015].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_015].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[libero_016].lID = EDT_LIBERO016;
	CFieldDlg::m_strFieldEndox[libero_016].sReport = "Scheda.Testo31"; // Campo libero 17
	CFieldDlg::m_strFieldEndox[libero_016].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_016].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[libero_017].lID = EDT_LIBERO017;
	CFieldDlg::m_strFieldEndox[libero_017].sReport = "Scheda.Testo32"; // Campo libero 18
	CFieldDlg::m_strFieldEndox[libero_017].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_017].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[libero_018].lID = EDT_LIBERO018;
	CFieldDlg::m_strFieldEndox[libero_018].sReport = "Scheda.Testo33"; // Campo libero 19
	CFieldDlg::m_strFieldEndox[libero_018].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_018].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[libero_019].lID = EDT_LIBERO019;
	CFieldDlg::m_strFieldEndox[libero_019].sReport = "Scheda.Testo34"; // Campo libero 20
	CFieldDlg::m_strFieldEndox[libero_019].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_019].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[libero_020].lID = EDT_LIBERO020;
	CFieldDlg::m_strFieldEndox[libero_020].sReport = "Scheda.Testo35"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_020].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_020].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_021].lID = EDT_LIBERO021;
	CFieldDlg::m_strFieldEndox[libero_021].sReport = "Scheda.Testo36"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_021].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_021].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_022].lID = EDT_LIBERO022;
	CFieldDlg::m_strFieldEndox[libero_022].sReport = "Scheda.Testo37"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_022].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_022].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_023].lID = EDT_LIBERO023;
	CFieldDlg::m_strFieldEndox[libero_023].sReport = "Scheda.Testo38"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_023].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_023].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_024].lID = EDT_LIBERO024;
	CFieldDlg::m_strFieldEndox[libero_024].sReport = "Scheda.Testo39"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_024].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_024].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_025].lID = EDT_LIBERO025;
	CFieldDlg::m_strFieldEndox[libero_025].sReport = "Scheda.Testo40"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_025].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_025].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_026].lID = EDT_LIBERO026;
	CFieldDlg::m_strFieldEndox[libero_026].sReport = "Scheda.Testo41"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_026].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_026].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_027].lID = EDT_LIBERO027;
	CFieldDlg::m_strFieldEndox[libero_027].sReport = "Scheda.Testo42"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_027].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_027].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_028].lID = EDT_LIBERO028;
	CFieldDlg::m_strFieldEndox[libero_028].sReport = "Scheda.Testo43"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_028].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_028].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_029].lID = EDT_LIBERO029;
	CFieldDlg::m_strFieldEndox[libero_029].sReport = "Scheda.Testo44"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_029].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_029].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_030].lID = EDT_LIBERO030;
	CFieldDlg::m_strFieldEndox[libero_030].sReport = "Scheda.Testo45"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_030].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_030].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_031].lID = EDT_LIBERO031;
	CFieldDlg::m_strFieldEndox[libero_031].sReport = "Scheda.Testo46"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_031].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_031].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_032].lID = EDT_LIBERO032;
	CFieldDlg::m_strFieldEndox[libero_032].sReport = "Scheda.Testo47"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_032].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_032].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_033].lID = EDT_LIBERO033;
	CFieldDlg::m_strFieldEndox[libero_033].sReport = "Scheda.Testo48"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_033].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_033].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_034].lID = EDT_LIBERO034;
	CFieldDlg::m_strFieldEndox[libero_034].sReport = "Scheda.Testo49"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_034].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_034].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_035].lID = EDT_LIBERO035;
	CFieldDlg::m_strFieldEndox[libero_035].sReport = "Scheda.Testo50"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_035].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_035].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_036].lID = EDT_LIBERO036;
	CFieldDlg::m_strFieldEndox[libero_036].sReport = "Scheda.Testo51"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_036].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_036].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_037].lID = EDT_LIBERO037;
	CFieldDlg::m_strFieldEndox[libero_037].sReport = "Scheda.Testo52"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_037].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_037].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_038].lID = EDT_LIBERO038;
	CFieldDlg::m_strFieldEndox[libero_038].sReport = "Scheda.Testo53"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_038].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_038].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_039].lID = EDT_LIBERO039;
	CFieldDlg::m_strFieldEndox[libero_039].sReport = "Scheda.Testo54"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_039].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_039].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_040].lID = EDT_LIBERO040;
	CFieldDlg::m_strFieldEndox[libero_040].sReport = "Scheda.Testo55"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_040].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_040].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_041].lID = EDT_LIBERO041;
	CFieldDlg::m_strFieldEndox[libero_041].sReport = "Scheda.Testo56"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_041].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_041].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_042].lID = EDT_LIBERO042;
	CFieldDlg::m_strFieldEndox[libero_042].sReport = "Scheda.Testo57"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_042].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_042].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_043].lID = EDT_LIBERO043;
	CFieldDlg::m_strFieldEndox[libero_043].sReport = "Scheda.Testo58"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_043].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_043].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_044].lID = EDT_LIBERO044;
	CFieldDlg::m_strFieldEndox[libero_044].sReport = "Scheda.Testo59"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_044].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_044].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_045].lID = EDT_LIBERO045;
	CFieldDlg::m_strFieldEndox[libero_045].sReport = "Scheda.Testo60"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_045].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_045].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_046].lID = EDT_LIBERO046;
	CFieldDlg::m_strFieldEndox[libero_046].sReport = "Scheda.Testo61"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_046].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_046].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_047].lID = EDT_LIBERO047;
	CFieldDlg::m_strFieldEndox[libero_047].sReport = "Scheda.Testo62"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_047].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_047].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_048].lID = EDT_LIBERO048;
	CFieldDlg::m_strFieldEndox[libero_048].sReport = "Scheda.Testo63"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_048].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_048].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_049].lID = EDT_LIBERO049;
	CFieldDlg::m_strFieldEndox[libero_049].sReport = "Scheda.Testo64"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_049].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_049].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_050].lID = EDT_LIBERO050;
	CFieldDlg::m_strFieldEndox[libero_050].sReport = "Scheda.Testo65"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_050].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_050].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_051].lID = EDT_LIBERO051;
	CFieldDlg::m_strFieldEndox[libero_051].sReport = "Scheda.Testo66"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_051].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_051].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_052].lID = EDT_LIBERO052;
	CFieldDlg::m_strFieldEndox[libero_052].sReport = "Scheda.Testo67"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_052].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_052].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_053].lID = EDT_LIBERO053;
	CFieldDlg::m_strFieldEndox[libero_053].sReport = "Scheda.Testo68"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_053].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_053].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_054].lID = EDT_LIBERO054;
	CFieldDlg::m_strFieldEndox[libero_054].sReport = "Scheda.Testo69"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_054].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_054].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_055].lID = EDT_LIBERO055;
	CFieldDlg::m_strFieldEndox[libero_055].sReport = "Scheda.Testo70"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_055].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_055].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_056].lID = EDT_LIBERO056;
	CFieldDlg::m_strFieldEndox[libero_056].sReport = "Scheda.Testo71"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_056].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_056].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_057].lID = EDT_LIBERO057;
	CFieldDlg::m_strFieldEndox[libero_057].sReport = "Scheda.Testo72"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_057].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_057].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_058].lID = EDT_LIBERO058;
	CFieldDlg::m_strFieldEndox[libero_058].sReport = "Scheda.Testo73"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_058].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_058].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_059].lID = EDT_LIBERO059;
	CFieldDlg::m_strFieldEndox[libero_059].sReport = "Scheda.Testo74"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_059].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_059].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_060].lID = EDT_LIBERO060;
	CFieldDlg::m_strFieldEndox[libero_060].sReport = "Scheda.Testo75"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_060].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_060].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_061].lID = EDT_LIBERO061;
	CFieldDlg::m_strFieldEndox[libero_061].sReport = "Scheda.Testo76"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_061].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_061].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_062].lID = EDT_LIBERO062;
	CFieldDlg::m_strFieldEndox[libero_062].sReport = "Scheda.Testo77"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_062].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_062].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_063].lID = EDT_LIBERO063;
	CFieldDlg::m_strFieldEndox[libero_063].sReport = "Scheda.Testo78"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_063].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_063].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_064].lID = EDT_LIBERO064;
	CFieldDlg::m_strFieldEndox[libero_064].sReport = "Scheda.Testo79"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_064].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_064].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_065].lID = EDT_LIBERO065;
	CFieldDlg::m_strFieldEndox[libero_065].sReport = "Scheda.Testo80"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_065].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_065].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_066].lID = EDT_LIBERO066;
	CFieldDlg::m_strFieldEndox[libero_066].sReport = "Scheda.Testo81"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_066].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_066].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_067].lID = EDT_LIBERO067;
	CFieldDlg::m_strFieldEndox[libero_067].sReport = "Scheda.Testo82"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_067].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_067].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_068].lID = EDT_LIBERO068;
	CFieldDlg::m_strFieldEndox[libero_068].sReport = "Scheda.Testo83"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_068].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_068].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_069].lID = EDT_LIBERO069;
	CFieldDlg::m_strFieldEndox[libero_069].sReport = "Scheda.Testo84"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_069].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_069].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_070].lID = EDT_LIBERO070;
	CFieldDlg::m_strFieldEndox[libero_070].sReport = "Scheda.Testo85"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_070].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_070].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_071].lID = EDT_LIBERO071;
	CFieldDlg::m_strFieldEndox[libero_071].sReport = "Scheda.Testo86"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_071].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_071].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_072].lID = EDT_LIBERO072;
	CFieldDlg::m_strFieldEndox[libero_072].sReport = "Scheda.Testo87"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_072].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_072].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_073].lID = EDT_LIBERO073;
	CFieldDlg::m_strFieldEndox[libero_073].sReport = "Scheda.Testo88"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_073].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_073].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_074].lID = EDT_LIBERO074;
	CFieldDlg::m_strFieldEndox[libero_074].sReport = "Scheda.Testo89"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_074].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_074].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_075].lID = EDT_LIBERO075;
	CFieldDlg::m_strFieldEndox[libero_075].sReport = "Scheda.Testo90"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_075].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_075].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_076].lID = EDT_LIBERO076;
	CFieldDlg::m_strFieldEndox[libero_076].sReport = "Scheda.Testo91"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_076].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_076].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_077].lID = EDT_LIBERO077;
	CFieldDlg::m_strFieldEndox[libero_077].sReport = "Scheda.Testo92"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_077].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_077].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_078].lID = EDT_LIBERO078;
	CFieldDlg::m_strFieldEndox[libero_078].sReport = "Scheda.Testo93"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_078].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_078].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_079].lID = EDT_LIBERO079;
	CFieldDlg::m_strFieldEndox[libero_079].sReport = "Scheda.Testo94"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_079].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_079].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_080].lID = EDT_LIBERO080;
	CFieldDlg::m_strFieldEndox[libero_080].sReport = "Scheda.Testo95"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_080].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_080].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_081].lID = EDT_LIBERO081;
	CFieldDlg::m_strFieldEndox[libero_081].sReport = "Scheda.Testo96"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_081].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_081].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_082].lID = EDT_LIBERO082;
	CFieldDlg::m_strFieldEndox[libero_082].sReport = "Scheda.Testo97"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_082].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_082].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_083].lID = EDT_LIBERO083;
	CFieldDlg::m_strFieldEndox[libero_083].sReport = "Scheda.Testo98"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_083].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_083].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_084].lID = EDT_LIBERO084;
	CFieldDlg::m_strFieldEndox[libero_084].sReport = "Scheda.Testo99"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_084].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_084].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_085].lID = EDT_LIBERO085;
	CFieldDlg::m_strFieldEndox[libero_085].sReport = "Scheda.Testo100"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_085].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_085].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_086].lID = EDT_LIBERO086;
	CFieldDlg::m_strFieldEndox[libero_086].sReport = "Scheda.Testo101"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_086].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_086].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_087].lID = EDT_LIBERO087;
	CFieldDlg::m_strFieldEndox[libero_087].sReport = "Scheda.Testo102"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_087].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_087].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_088].lID = EDT_LIBERO088;
	CFieldDlg::m_strFieldEndox[libero_088].sReport = "Scheda.Testo103"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_088].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_088].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_089].lID = EDT_LIBERO089;
	CFieldDlg::m_strFieldEndox[libero_089].sReport = "Scheda.Testo104"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_089].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_089].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_090].lID = EDT_LIBERO090;
	CFieldDlg::m_strFieldEndox[libero_090].sReport = "Scheda.Testo105"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_090].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_090].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_091].lID = EDT_LIBERO091;
	CFieldDlg::m_strFieldEndox[libero_091].sReport = "Scheda.Testo106"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_091].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_091].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_092].lID = EDT_LIBERO092;
	CFieldDlg::m_strFieldEndox[libero_092].sReport = "Scheda.Testo107"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_092].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_092].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_093].lID = EDT_LIBERO093;
	CFieldDlg::m_strFieldEndox[libero_093].sReport = "Scheda.Testo108"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_093].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_093].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_094].lID = EDT_LIBERO094;
	CFieldDlg::m_strFieldEndox[libero_094].sReport = "Scheda.Testo109"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_094].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_094].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_095].lID = EDT_LIBERO095;
	CFieldDlg::m_strFieldEndox[libero_095].sReport = "Scheda.Testo110"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_095].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_095].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_096].lID = EDT_LIBERO096;
	CFieldDlg::m_strFieldEndox[libero_096].sReport = "Scheda.Testo111"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_096].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_096].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_097].lID = EDT_LIBERO097;
	CFieldDlg::m_strFieldEndox[libero_097].sReport = "Scheda.Testo112"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_097].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_097].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_098].lID = EDT_LIBERO098;
	CFieldDlg::m_strFieldEndox[libero_098].sReport = "Scheda.Testo113"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_098].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_098].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_099].lID = EDT_LIBERO099;
	CFieldDlg::m_strFieldEndox[libero_099].sReport = "Scheda.Testo114"; // Campo libero 
	CFieldDlg::m_strFieldEndox[libero_099].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_099].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_000_fisso].lID = EDT_LIBERORTF000;
	CFieldDlg::m_strFieldEndox[libero_rtf_000_fisso].sReport = "Scheda.TestoRtf01Fisso";
	CFieldDlg::m_strFieldEndox[libero_rtf_000_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_000_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_000_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_rtf_000_grande].sReport = "Scheda.TestoRtf01Lungo";
	CFieldDlg::m_strFieldEndox[libero_rtf_000_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_000_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_001_fisso].lID = EDT_LIBERORTF001;
	CFieldDlg::m_strFieldEndox[libero_rtf_001_fisso].sReport = "Scheda.TestoRtf02Fisso";
	CFieldDlg::m_strFieldEndox[libero_rtf_001_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_001_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_001_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_rtf_001_grande].sReport = "Scheda.TestoRtf02Lungo";
	CFieldDlg::m_strFieldEndox[libero_rtf_001_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_001_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_002_fisso].lID = EDT_LIBERORTF002;
	CFieldDlg::m_strFieldEndox[libero_rtf_002_fisso].sReport = "Scheda.TestoRtf03Fisso";
	CFieldDlg::m_strFieldEndox[libero_rtf_002_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_002_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_002_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_rtf_002_grande].sReport = "Scheda.TestoRtf03Lungo";
	CFieldDlg::m_strFieldEndox[libero_rtf_002_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_002_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_003_fisso].lID = EDT_LIBERORTF003;
	CFieldDlg::m_strFieldEndox[libero_rtf_003_fisso].sReport = "Scheda.TestoRtf04Fisso";
	CFieldDlg::m_strFieldEndox[libero_rtf_003_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_003_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_003_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_rtf_003_grande].sReport = "Scheda.TestoRtf04Lungo";
	CFieldDlg::m_strFieldEndox[libero_rtf_003_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_003_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_004_fisso].lID = EDT_LIBERORTF004;
	CFieldDlg::m_strFieldEndox[libero_rtf_004_fisso].sReport = "Scheda.TestoRtf05Fisso";
	CFieldDlg::m_strFieldEndox[libero_rtf_004_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_004_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_004_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_rtf_004_grande].sReport = "Scheda.TestoRtf05Lungo";
	CFieldDlg::m_strFieldEndox[libero_rtf_004_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_004_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_005_fisso].lID = EDT_LIBERORTF005;
	CFieldDlg::m_strFieldEndox[libero_rtf_005_fisso].sReport = "Scheda.TestoRtf06Fisso";
	CFieldDlg::m_strFieldEndox[libero_rtf_005_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_005_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_005_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_rtf_005_grande].sReport = "Scheda.TestoRtf06Lungo";
	CFieldDlg::m_strFieldEndox[libero_rtf_005_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_005_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_006_fisso].lID = EDT_LIBERORTF006;
	CFieldDlg::m_strFieldEndox[libero_rtf_006_fisso].sReport = "Scheda.TestoRtf07Fisso";
	CFieldDlg::m_strFieldEndox[libero_rtf_006_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_006_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_006_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_rtf_006_grande].sReport = "Scheda.TestoRtf07Lungo";
	CFieldDlg::m_strFieldEndox[libero_rtf_006_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_006_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_007_fisso].lID = EDT_LIBERORTF007;
	CFieldDlg::m_strFieldEndox[libero_rtf_007_fisso].sReport = "Scheda.TestoRtf08Fisso";
	CFieldDlg::m_strFieldEndox[libero_rtf_007_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_007_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_007_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_rtf_007_grande].sReport = "Scheda.TestoRtf08Lungo";
	CFieldDlg::m_strFieldEndox[libero_rtf_007_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_007_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_008_fisso].lID = EDT_LIBERORTF008;
	CFieldDlg::m_strFieldEndox[libero_rtf_008_fisso].sReport = "Scheda.TestoRtf09Fisso";
	CFieldDlg::m_strFieldEndox[libero_rtf_008_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_008_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_008_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_rtf_008_grande].sReport = "Scheda.TestoRtf09Lungo";
	CFieldDlg::m_strFieldEndox[libero_rtf_008_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_008_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_009_fisso].lID = EDT_LIBERORTF009;
	CFieldDlg::m_strFieldEndox[libero_rtf_009_fisso].sReport = "Scheda.TestoRtf10Fisso";
	CFieldDlg::m_strFieldEndox[libero_rtf_009_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_009_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_009_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_rtf_009_grande].sReport = "Scheda.TestoRtf10Lungo";
	CFieldDlg::m_strFieldEndox[libero_rtf_009_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_009_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_010_fisso].lID = EDT_LIBERORTF010;
	CFieldDlg::m_strFieldEndox[libero_rtf_010_fisso].sReport = "Scheda.TestoRtf11Fisso";
	CFieldDlg::m_strFieldEndox[libero_rtf_010_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_010_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_010_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_rtf_010_grande].sReport = "Scheda.TestoRtf11Lungo";
	CFieldDlg::m_strFieldEndox[libero_rtf_010_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_010_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_011_fisso].lID = EDT_LIBERORTF011;
	CFieldDlg::m_strFieldEndox[libero_rtf_011_fisso].sReport = "Scheda.TestoRtf12Fisso";
	CFieldDlg::m_strFieldEndox[libero_rtf_011_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_011_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_011_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_rtf_011_grande].sReport = "Scheda.TestoRtf12Lungo";
	CFieldDlg::m_strFieldEndox[libero_rtf_011_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_011_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_012_fisso].lID = EDT_LIBERORTF012;
	CFieldDlg::m_strFieldEndox[libero_rtf_012_fisso].sReport = "Scheda.TestoRtf13Fisso";
	CFieldDlg::m_strFieldEndox[libero_rtf_012_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_012_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_012_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_rtf_012_grande].sReport = "Scheda.TestoRtf13Lungo";
	CFieldDlg::m_strFieldEndox[libero_rtf_012_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_012_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_013_fisso].lID = EDT_LIBERORTF013;
	CFieldDlg::m_strFieldEndox[libero_rtf_013_fisso].sReport = "Scheda.TestoRtf14Fisso";
	CFieldDlg::m_strFieldEndox[libero_rtf_013_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_013_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_013_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_rtf_013_grande].sReport = "Scheda.TestoRtf14Lungo";
	CFieldDlg::m_strFieldEndox[libero_rtf_013_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_013_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_014_fisso].lID = EDT_LIBERORTF014;
	CFieldDlg::m_strFieldEndox[libero_rtf_014_fisso].sReport = "Scheda.TestoRtf15Fisso";
	CFieldDlg::m_strFieldEndox[libero_rtf_014_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_014_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_014_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_rtf_014_grande].sReport = "Scheda.TestoRtf15Lungo";
	CFieldDlg::m_strFieldEndox[libero_rtf_014_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_014_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_015_fisso].lID = EDT_LIBERORTF015;
	CFieldDlg::m_strFieldEndox[libero_rtf_015_fisso].sReport = "Scheda.TestoRtf16Fisso";
	CFieldDlg::m_strFieldEndox[libero_rtf_015_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_015_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_015_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_rtf_015_grande].sReport = "Scheda.TestoRtf16Lungo";
	CFieldDlg::m_strFieldEndox[libero_rtf_015_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_015_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_016_fisso].lID = EDT_LIBERORTF016;
	CFieldDlg::m_strFieldEndox[libero_rtf_016_fisso].sReport = "Scheda.TestoRtf17Fisso";
	CFieldDlg::m_strFieldEndox[libero_rtf_016_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_016_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_016_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_rtf_016_grande].sReport = "Scheda.TestoRtf17Lungo";
	CFieldDlg::m_strFieldEndox[libero_rtf_016_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_016_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_017_fisso].lID = EDT_LIBERORTF017;
	CFieldDlg::m_strFieldEndox[libero_rtf_017_fisso].sReport = "Scheda.TestoRtf18Fisso";
	CFieldDlg::m_strFieldEndox[libero_rtf_017_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_017_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_017_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_rtf_017_grande].sReport = "Scheda.TestoRtf18Lungo";
	CFieldDlg::m_strFieldEndox[libero_rtf_017_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_017_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_018_fisso].lID = EDT_LIBERORTF018;
	CFieldDlg::m_strFieldEndox[libero_rtf_018_fisso].sReport = "Scheda.TestoRtf19Fisso";
	CFieldDlg::m_strFieldEndox[libero_rtf_018_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_018_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_018_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_rtf_018_grande].sReport = "Scheda.TestoRtf19Lungo";
	CFieldDlg::m_strFieldEndox[libero_rtf_018_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_018_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_019_fisso].lID = EDT_LIBERORTF019;
	CFieldDlg::m_strFieldEndox[libero_rtf_019_fisso].sReport = "Scheda.TestoRtf20Fisso";
	CFieldDlg::m_strFieldEndox[libero_rtf_019_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_019_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_rtf_019_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_rtf_019_grande].sReport = "Scheda.TestoRtf20Lungo";
	CFieldDlg::m_strFieldEndox[libero_rtf_019_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_rtf_019_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_000_fisso].lID = EDT_LIBEROCL000;
	CFieldDlg::m_strFieldEndox[libero_cl_000_fisso].sReport = "Scheda.TestoCL01Fisso";
	CFieldDlg::m_strFieldEndox[libero_cl_000_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_000_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_000_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_cl_000_grande].sReport = "Scheda.TestoCL01Lungo";
	CFieldDlg::m_strFieldEndox[libero_cl_000_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_000_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_001_fisso].lID = EDT_LIBEROCL001;
	CFieldDlg::m_strFieldEndox[libero_cl_001_fisso].sReport = "Scheda.TestoCL02Fisso";
	CFieldDlg::m_strFieldEndox[libero_cl_001_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_001_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_001_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_cl_001_grande].sReport = "Scheda.TestoCL02Lungo";
	CFieldDlg::m_strFieldEndox[libero_cl_001_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_001_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_002_fisso].lID = EDT_LIBEROCL002;
	CFieldDlg::m_strFieldEndox[libero_cl_002_fisso].sReport = "Scheda.TestoCL03Fisso";
	CFieldDlg::m_strFieldEndox[libero_cl_002_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_002_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_002_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_cl_002_grande].sReport = "Scheda.TestoCL03Lungo";
	CFieldDlg::m_strFieldEndox[libero_cl_002_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_002_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_003_fisso].lID = EDT_LIBEROCL003;
	CFieldDlg::m_strFieldEndox[libero_cl_003_fisso].sReport = "Scheda.TestoCL04Fisso";
	CFieldDlg::m_strFieldEndox[libero_cl_003_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_003_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_003_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_cl_003_grande].sReport = "Scheda.TestoCL04Lungo";
	CFieldDlg::m_strFieldEndox[libero_cl_003_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_003_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_004_fisso].lID = EDT_LIBEROCL004;
	CFieldDlg::m_strFieldEndox[libero_cl_004_fisso].sReport = "Scheda.TestoCL05Fisso";
	CFieldDlg::m_strFieldEndox[libero_cl_004_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_004_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_004_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_cl_004_grande].sReport = "Scheda.TestoCL05Lungo";
	CFieldDlg::m_strFieldEndox[libero_cl_004_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_004_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_005_fisso].lID = EDT_LIBEROCL005;
	CFieldDlg::m_strFieldEndox[libero_cl_005_fisso].sReport = "Scheda.TestoCL06Fisso";
	CFieldDlg::m_strFieldEndox[libero_cl_005_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_005_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_005_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_cl_005_grande].sReport = "Scheda.TestoCL06Lungo";
	CFieldDlg::m_strFieldEndox[libero_cl_005_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_005_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_006_fisso].lID = EDT_LIBEROCL006;
	CFieldDlg::m_strFieldEndox[libero_cl_006_fisso].sReport = "Scheda.TestoCL07Fisso";
	CFieldDlg::m_strFieldEndox[libero_cl_006_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_006_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_006_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_cl_006_grande].sReport = "Scheda.TestoCL07Lungo";
	CFieldDlg::m_strFieldEndox[libero_cl_006_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_006_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_007_fisso].lID = EDT_LIBEROCL007;
	CFieldDlg::m_strFieldEndox[libero_cl_007_fisso].sReport = "Scheda.TestoCL08Fisso";
	CFieldDlg::m_strFieldEndox[libero_cl_007_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_007_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_007_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_cl_007_grande].sReport = "Scheda.TestoCL08Lungo";
	CFieldDlg::m_strFieldEndox[libero_cl_007_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_007_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_008_fisso].lID = EDT_LIBEROCL008;
	CFieldDlg::m_strFieldEndox[libero_cl_008_fisso].sReport = "Scheda.TestoCL09Fisso";
	CFieldDlg::m_strFieldEndox[libero_cl_008_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_008_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_008_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_cl_008_grande].sReport = "Scheda.TestoCL09Lungo";
	CFieldDlg::m_strFieldEndox[libero_cl_008_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_008_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_009_fisso].lID = EDT_LIBEROCL009;
	CFieldDlg::m_strFieldEndox[libero_cl_009_fisso].sReport = "Scheda.TestoCL10Fisso";
	CFieldDlg::m_strFieldEndox[libero_cl_009_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_009_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_009_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_cl_009_grande].sReport = "Scheda.TestoCL10Lungo";
	CFieldDlg::m_strFieldEndox[libero_cl_009_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_009_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_010_fisso].lID = EDT_LIBEROCL010;
	CFieldDlg::m_strFieldEndox[libero_cl_010_fisso].sReport = "Scheda.TestoCL11Fisso";
	CFieldDlg::m_strFieldEndox[libero_cl_010_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_010_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_010_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_cl_010_grande].sReport = "Scheda.TestoCL11Lungo";
	CFieldDlg::m_strFieldEndox[libero_cl_010_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_010_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_011_fisso].lID = EDT_LIBEROCL011;
	CFieldDlg::m_strFieldEndox[libero_cl_011_fisso].sReport = "Scheda.TestoCL12Fisso";
	CFieldDlg::m_strFieldEndox[libero_cl_011_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_011_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_011_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_cl_011_grande].sReport = "Scheda.TestoCL12Lungo";
	CFieldDlg::m_strFieldEndox[libero_cl_011_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_011_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_012_fisso].lID = EDT_LIBEROCL012;
	CFieldDlg::m_strFieldEndox[libero_cl_012_fisso].sReport = "Scheda.TestoCL13Fisso";
	CFieldDlg::m_strFieldEndox[libero_cl_012_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_012_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_012_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_cl_012_grande].sReport = "Scheda.TestoCL13Lungo";
	CFieldDlg::m_strFieldEndox[libero_cl_012_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_012_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_013_fisso].lID = EDT_LIBEROCL013;
	CFieldDlg::m_strFieldEndox[libero_cl_013_fisso].sReport = "Scheda.TestoCL14Fisso";
	CFieldDlg::m_strFieldEndox[libero_cl_013_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_013_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_013_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_cl_013_grande].sReport = "Scheda.TestoCL14Lungo";
	CFieldDlg::m_strFieldEndox[libero_cl_013_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_013_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_014_fisso].lID = EDT_LIBEROCL014;
	CFieldDlg::m_strFieldEndox[libero_cl_014_fisso].sReport = "Scheda.TestoCL15Fisso";
	CFieldDlg::m_strFieldEndox[libero_cl_014_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_014_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_014_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_cl_014_grande].sReport = "Scheda.TestoCL15Lungo";
	CFieldDlg::m_strFieldEndox[libero_cl_014_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_014_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_015_fisso].lID = EDT_LIBEROCL015;
	CFieldDlg::m_strFieldEndox[libero_cl_015_fisso].sReport = "Scheda.TestoCL16Fisso";
	CFieldDlg::m_strFieldEndox[libero_cl_015_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_015_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_015_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_cl_015_grande].sReport = "Scheda.TestoCL16Lungo";
	CFieldDlg::m_strFieldEndox[libero_cl_015_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_015_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_016_fisso].lID = EDT_LIBEROCL016;
	CFieldDlg::m_strFieldEndox[libero_cl_016_fisso].sReport = "Scheda.TestoCL17Fisso";
	CFieldDlg::m_strFieldEndox[libero_cl_016_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_016_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_016_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_cl_016_grande].sReport = "Scheda.TestoCL17Lungo";
	CFieldDlg::m_strFieldEndox[libero_cl_016_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_016_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_017_fisso].lID = EDT_LIBEROCL017;
	CFieldDlg::m_strFieldEndox[libero_cl_017_fisso].sReport = "Scheda.TestoCL18Fisso";
	CFieldDlg::m_strFieldEndox[libero_cl_017_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_017_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_017_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_cl_017_grande].sReport = "Scheda.TestoCL18Lungo";
	CFieldDlg::m_strFieldEndox[libero_cl_017_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_017_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_018_fisso].lID = EDT_LIBEROCL018;
	CFieldDlg::m_strFieldEndox[libero_cl_018_fisso].sReport = "Scheda.TestoCL19Fisso";
	CFieldDlg::m_strFieldEndox[libero_cl_018_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_018_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_018_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_cl_018_grande].sReport = "Scheda.TestoCL19Lungo";
	CFieldDlg::m_strFieldEndox[libero_cl_018_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_018_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_019_fisso].lID = EDT_LIBEROCL019;
	CFieldDlg::m_strFieldEndox[libero_cl_019_fisso].sReport = "Scheda.TestoCL20Fisso";
	CFieldDlg::m_strFieldEndox[libero_cl_019_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_019_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_cl_019_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[libero_cl_019_grande].sReport = "Scheda.TestoCL20Lungo";
	CFieldDlg::m_strFieldEndox[libero_cl_019_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_cl_019_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_dataora_000].lID = EDT_LIBERODATAORA000;
	CFieldDlg::m_strFieldEndox[libero_dataora_000].sReport = "LiberoDataOra000";
	CFieldDlg::m_strFieldEndox[libero_dataora_000].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_dataora_000].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_dataora_001].lID = EDT_LIBERODATAORA001;
	CFieldDlg::m_strFieldEndox[libero_dataora_001].sReport = "LiberoDataOra001";
	CFieldDlg::m_strFieldEndox[libero_dataora_001].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_dataora_001].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_dataora_002].lID = EDT_LIBERODATAORA002;
	CFieldDlg::m_strFieldEndox[libero_dataora_002].sReport = "LiberoDataOra002";
	CFieldDlg::m_strFieldEndox[libero_dataora_002].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_dataora_002].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_dataora_003].lID = EDT_LIBERODATAORA003;
	CFieldDlg::m_strFieldEndox[libero_dataora_003].sReport = "LiberoDataOra003";
	CFieldDlg::m_strFieldEndox[libero_dataora_003].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_dataora_003].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_dataora_004].lID = EDT_LIBERODATAORA004;
	CFieldDlg::m_strFieldEndox[libero_dataora_004].sReport = "LiberoDataOra004";
	CFieldDlg::m_strFieldEndox[libero_dataora_004].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_dataora_004].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_dataora_005].lID = EDT_LIBERODATAORA005;
	CFieldDlg::m_strFieldEndox[libero_dataora_005].sReport = "LiberoDataOra005";
	CFieldDlg::m_strFieldEndox[libero_dataora_005].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_dataora_005].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_dataora_006].lID = EDT_LIBERODATAORA006;
	CFieldDlg::m_strFieldEndox[libero_dataora_006].sReport = "LiberoDataOra006";
	CFieldDlg::m_strFieldEndox[libero_dataora_006].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_dataora_006].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_dataora_007].lID = EDT_LIBERODATAORA007;
	CFieldDlg::m_strFieldEndox[libero_dataora_007].sReport = "LiberoDataOra007";
	CFieldDlg::m_strFieldEndox[libero_dataora_007].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_dataora_007].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_dataora_008].lID = EDT_LIBERODATAORA008;
	CFieldDlg::m_strFieldEndox[libero_dataora_008].sReport = "LiberoDataOra008";
	CFieldDlg::m_strFieldEndox[libero_dataora_008].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_dataora_008].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_dataora_009].lID = EDT_LIBERODATAORA009;
	CFieldDlg::m_strFieldEndox[libero_dataora_009].sReport = "LiberoDataOra009";
	CFieldDlg::m_strFieldEndox[libero_dataora_009].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_dataora_009].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_dataora_010].lID = EDT_LIBERODATAORA010;
	CFieldDlg::m_strFieldEndox[libero_dataora_010].sReport = "LiberoDataOra010";
	CFieldDlg::m_strFieldEndox[libero_dataora_010].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_dataora_010].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_dataora_011].lID = EDT_LIBERODATAORA011;
	CFieldDlg::m_strFieldEndox[libero_dataora_011].sReport = "LiberoDataOra011";
	CFieldDlg::m_strFieldEndox[libero_dataora_011].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_dataora_011].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_dataora_012].lID = EDT_LIBERODATAORA012;
	CFieldDlg::m_strFieldEndox[libero_dataora_012].sReport = "LiberoDataOra012";
	CFieldDlg::m_strFieldEndox[libero_dataora_012].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_dataora_012].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_dataora_013].lID = EDT_LIBERODATAORA013;
	CFieldDlg::m_strFieldEndox[libero_dataora_013].sReport = "LiberoDataOra013";
	CFieldDlg::m_strFieldEndox[libero_dataora_013].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_dataora_013].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_dataora_014].lID = EDT_LIBERODATAORA014;
	CFieldDlg::m_strFieldEndox[libero_dataora_014].sReport = "LiberoDataOra014";
	CFieldDlg::m_strFieldEndox[libero_dataora_014].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_dataora_014].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_dataora_015].lID = EDT_LIBERODATAORA015;
	CFieldDlg::m_strFieldEndox[libero_dataora_015].sReport = "LiberoDataOra015";
	CFieldDlg::m_strFieldEndox[libero_dataora_015].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_dataora_015].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_dataora_016].lID = EDT_LIBERODATAORA016;
	CFieldDlg::m_strFieldEndox[libero_dataora_016].sReport = "LiberoDataOra016";
	CFieldDlg::m_strFieldEndox[libero_dataora_016].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_dataora_016].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_dataora_017].lID = EDT_LIBERODATAORA017;
	CFieldDlg::m_strFieldEndox[libero_dataora_017].sReport = "LiberoDataOra017";
	CFieldDlg::m_strFieldEndox[libero_dataora_017].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_dataora_017].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_dataora_018].lID = EDT_LIBERODATAORA018;
	CFieldDlg::m_strFieldEndox[libero_dataora_018].sReport = "LiberoDataOra018";
	CFieldDlg::m_strFieldEndox[libero_dataora_018].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_dataora_018].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_dataora_019].lID = EDT_LIBERODATAORA019;
	CFieldDlg::m_strFieldEndox[libero_dataora_019].sReport = "LiberoDataOra019";
	CFieldDlg::m_strFieldEndox[libero_dataora_019].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_dataora_019].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[libero_integrazioni].lID = EDT_INTEGRAZIONI;
	CFieldDlg::m_strFieldEndox[libero_integrazioni].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_21);
	CFieldDlg::m_strFieldEndox[libero_integrazioni].sReport = "Scheda.Integrazioni"; // Integrazioni
	CFieldDlg::m_strFieldEndox[libero_integrazioni].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[libero_integrazioni].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_codificadiagnosi_fisso].lID = SUB_CODIFICADIAGNOSIESAME;
	CFieldDlg::m_strFieldEndox[form_codificadiagnosi_fisso].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_100);
	CFieldDlg::m_strFieldEndox[form_codificadiagnosi_fisso].sReport = "Codifica diagnosi esame";
	CFieldDlg::m_strFieldEndox[form_codificadiagnosi_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_codificadiagnosi_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_codificadiagnosi_grande].lID = SUB_CODIFICADIAGNOSIESAME5RIGHE;
	CFieldDlg::m_strFieldEndox[form_codificadiagnosi_grande].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_330);
	CFieldDlg::m_strFieldEndox[form_codificadiagnosi_grande].sReport = "Codifica diagnosi esame Grande";
	CFieldDlg::m_strFieldEndox[form_codificadiagnosi_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_codificadiagnosi_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_codificaregionale_fisso].lID = SUB_REGIONE;
	CFieldDlg::m_strFieldEndox[form_codificaregionale_fisso].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_89);
	CFieldDlg::m_strFieldEndox[form_codificaregionale_fisso].sReport = "Codifica regionale";
	CFieldDlg::m_strFieldEndox[form_codificaregionale_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_codificaregionale_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_codificaregionale_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[form_codificaregionale_grande].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_331);
	CFieldDlg::m_strFieldEndox[form_codificaregionale_grande].sReport = "Codifica regionale Grande";
	CFieldDlg::m_strFieldEndox[form_codificaregionale_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_codificaregionale_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_codificaregionale_desc_fisso].lID = -1;
	CFieldDlg::m_strFieldEndox[form_codificaregionale_desc_fisso].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_295);
	CFieldDlg::m_strFieldEndox[form_codificaregionale_desc_fisso].sReport = "Codifica regionale - Descrizione";
	CFieldDlg::m_strFieldEndox[form_codificaregionale_desc_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_codificaregionale_desc_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_codificaregionale_desc_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[form_codificaregionale_desc_grande].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_332);
	CFieldDlg::m_strFieldEndox[form_codificaregionale_desc_grande].sReport = "Codifica regionale - Descrizione Grande";
	CFieldDlg::m_strFieldEndox[form_codificaregionale_desc_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_codificaregionale_desc_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_diagnosi_fisso].lID = SUB_DIAGNOSI;
	CFieldDlg::m_strFieldEndox[form_diagnosi_fisso].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_88);
	CFieldDlg::m_strFieldEndox[form_diagnosi_fisso].sReport = "Diagnosi";
	CFieldDlg::m_strFieldEndox[form_diagnosi_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_diagnosi_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_diagnosi_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[form_diagnosi_grande].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_352);
	CFieldDlg::m_strFieldEndox[form_diagnosi_grande].sReport = "Diagnosi Grande";
	CFieldDlg::m_strFieldEndox[form_diagnosi_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_diagnosi_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_indaginipregresse].lID = SUB_INDAGINI;
	CFieldDlg::m_strFieldEndox[form_indaginipregresse].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_83);
	CFieldDlg::m_strFieldEndox[form_indaginipregresse].sReport = "Indagini pregresse";
	CFieldDlg::m_strFieldEndox[form_indaginipregresse].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_indaginipregresse].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[form_pregressiesamistrumentali].lID = SUB_ESAMIPREGRESSI;
	CFieldDlg::m_strFieldEndox[form_pregressiesamistrumentali].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_101);
	CFieldDlg::m_strFieldEndox[form_pregressiesamistrumentali].sReport = "Esami pregressi";
	CFieldDlg::m_strFieldEndox[form_pregressiesamistrumentali].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_pregressiesamistrumentali].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[form_interventichirurgici].lID = SUB_CHIRURGICI;
	CFieldDlg::m_strFieldEndox[form_interventichirurgici].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_80);
	CFieldDlg::m_strFieldEndox[form_interventichirurgici].sReport = "Interventi chirurgici";
	CFieldDlg::m_strFieldEndox[form_interventichirurgici].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_interventichirurgici].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[form_interventiendoscopici].lID = SUB_ENDOSCOPICI;
	CFieldDlg::m_strFieldEndox[form_interventiendoscopici].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_81);
	CFieldDlg::m_strFieldEndox[form_interventiendoscopici].sReport = "Interventi endoscopici";
	CFieldDlg::m_strFieldEndox[form_interventiendoscopici].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_interventiendoscopici].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_istologia_fisso].lID = SUB_ISTOPATOLOGIA;
	CFieldDlg::m_strFieldEndox[form_istologia_fisso].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_90);
	CFieldDlg::m_strFieldEndox[form_istologia_fisso].sReport = "Patologia";
	CFieldDlg::m_strFieldEndox[form_istologia_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_istologia_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_istologia_fisso_plus].lID = SUB_ISTOPATOLOGIA5RIGHE_PLUS;
	CFieldDlg::m_strFieldEndox[form_istologia_fisso_plus].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_518);
	CFieldDlg::m_strFieldEndox[form_istologia_fisso_plus].sReport = "Patologia Plus";
	CFieldDlg::m_strFieldEndox[form_istologia_fisso_plus].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_istologia_fisso_plus].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_istologia_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[form_istologia_grande].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_333);
	CFieldDlg::m_strFieldEndox[form_istologia_grande].sReport = "Patologia Grande";
	CFieldDlg::m_strFieldEndox[form_istologia_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_istologia_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_istologia_grande_plus].lID = -1;
	CFieldDlg::m_strFieldEndox[form_istologia_grande_plus].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_519);
	CFieldDlg::m_strFieldEndox[form_istologia_grande_plus].sReport = "Patologia Grande Plus";
	CFieldDlg::m_strFieldEndox[form_istologia_grande_plus].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_istologia_grande_plus].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_familiarita].lID = SUB_FAMILIARITA;
	CFieldDlg::m_strFieldEndox[form_familiarita].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_82);
	CFieldDlg::m_strFieldEndox[form_familiarita].sReport = "Familiarita";
	CFieldDlg::m_strFieldEndox[form_familiarita].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_familiarita].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[form_osservazioni_fisso].lID = SUB_OSSERVAZIONI;
	CFieldDlg::m_strFieldEndox[form_osservazioni_fisso].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_87);
	CFieldDlg::m_strFieldEndox[form_osservazioni_fisso].sReport = "Osservazioni";
	CFieldDlg::m_strFieldEndox[form_osservazioni_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_osservazioni_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_osservazioni_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[form_osservazioni_grande].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_353);
	CFieldDlg::m_strFieldEndox[form_osservazioni_grande].sReport = "Osservazioni Grande";
	CFieldDlg::m_strFieldEndox[form_osservazioni_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_osservazioni_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_malattieprecedenti].lID = SUB_MALATTIE;
	CFieldDlg::m_strFieldEndox[form_malattieprecedenti].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_84);
	CFieldDlg::m_strFieldEndox[form_malattieprecedenti].sReport = "Malattie";
	CFieldDlg::m_strFieldEndox[form_malattieprecedenti].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_malattieprecedenti].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[form_monitoraggio_orizzontale].lID = SUB_MONITORAGGIO_ORIZ;
	CFieldDlg::m_strFieldEndox[form_monitoraggio_orizzontale].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_92);
	CFieldDlg::m_strFieldEndox[form_monitoraggio_orizzontale].sReport = "Monitoraggio";
	CFieldDlg::m_strFieldEndox[form_monitoraggio_orizzontale].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_monitoraggio_orizzontale].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_monitoraggio_verticale].lID = SUB_MONITORAGGIO_VERT;
	CFieldDlg::m_strFieldEndox[form_monitoraggio_verticale].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_318);
	CFieldDlg::m_strFieldEndox[form_monitoraggio_verticale].sReport = "MonitoraggioVerticale";
	CFieldDlg::m_strFieldEndox[form_monitoraggio_verticale].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_monitoraggio_verticale].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_monitoraggio_verticale_new].lID = -1;
	CFieldDlg::m_strFieldEndox[form_monitoraggio_verticale_new].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_318) + " NEW";
	CFieldDlg::m_strFieldEndox[form_monitoraggio_verticale_new].sReport = "MonitoraggioVerticaleNew";
	CFieldDlg::m_strFieldEndox[form_monitoraggio_verticale_new].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_monitoraggio_verticale_new].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_monitoraggio_farmaci].lID = -1;
	CFieldDlg::m_strFieldEndox[form_monitoraggio_farmaci].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_348);
	CFieldDlg::m_strFieldEndox[form_monitoraggio_farmaci].sReport = "Monitoraggio.Farmaci";
	CFieldDlg::m_strFieldEndox[form_monitoraggio_farmaci].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_monitoraggio_farmaci].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_monitoraggio_infermiere].lID = -1;
	CFieldDlg::m_strFieldEndox[form_monitoraggio_infermiere].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_497);
	CFieldDlg::m_strFieldEndox[form_monitoraggio_infermiere].sReport = "Monitoraggio.Infermiere";
	CFieldDlg::m_strFieldEndox[form_monitoraggio_infermiere].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_monitoraggio_infermiere].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_monitoraggio_note].lID = -1;
	CFieldDlg::m_strFieldEndox[form_monitoraggio_note].sCombo = theApp.GetMessageString(IDS_NOTE_MONITORAGGIO);
	CFieldDlg::m_strFieldEndox[form_monitoraggio_note].sReport = "Monitoraggio.Note";
	CFieldDlg::m_strFieldEndox[form_monitoraggio_note].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_monitoraggio_note].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_terapiainatto].lID = SUB_TERAPIAINATTO;
	CFieldDlg::m_strFieldEndox[form_terapiainatto].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_86);
	CFieldDlg::m_strFieldEndox[form_terapiainatto].sReport = "Terapie";
	CFieldDlg::m_strFieldEndox[form_terapiainatto].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_terapiainatto].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_codificaregionale_5righe].lID = SUB_REGIONE5RIGHE;
	CFieldDlg::m_strFieldEndox[form_codificaregionale_5righe].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_306);
	CFieldDlg::m_strFieldEndox[form_codificaregionale_5righe].sReport = "Codifica regionale 5 Righe";
	CFieldDlg::m_strFieldEndox[form_codificaregionale_5righe].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_codificaregionale_5righe].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_fluoroscopia].lID = SUB_FLUOROSCOPIA;
	CFieldDlg::m_strFieldEndox[form_fluoroscopia].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_320);
	CFieldDlg::m_strFieldEndox[form_fluoroscopia].sReport = "Fluoroscopia";
	CFieldDlg::m_strFieldEndox[form_fluoroscopia].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_fluoroscopia].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_accessori].lID = SUB_ACCESSORI5RIGHE;
	CFieldDlg::m_strFieldEndox[form_accessori].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_317);
	CFieldDlg::m_strFieldEndox[form_accessori].sReport = "Accessori";
	CFieldDlg::m_strFieldEndox[form_accessori].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_accessori].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[subanatomia_campioni].lID = SUB_ANATOMIAPATOLOGICA;
	CFieldDlg::m_strFieldEndox[subanatomia_campioni].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_302);
	CFieldDlg::m_strFieldEndox[subanatomia_campioni].sReport = "Anatomia.Campioni";
	CFieldDlg::m_strFieldEndox[subanatomia_campioni].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[subanatomia_campioni].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[subanatomia_inviorichiesta].lID = SUB_ANATOMIAPATOLOGICATASTI;
	CFieldDlg::m_strFieldEndox[subanatomia_inviorichiesta].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_120);
	CFieldDlg::m_strFieldEndox[subanatomia_inviorichiesta].sReport = "Anatomia.InvioRichiesta";
	CFieldDlg::m_strFieldEndox[subanatomia_inviorichiesta].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[subanatomia_inviorichiesta].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[subanatomia_idcampione].lID = -1;
	CFieldDlg::m_strFieldEndox[subanatomia_idcampione].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_125);
	CFieldDlg::m_strFieldEndox[subanatomia_idcampione].sReport = "Anatomia.IDCampione";
	CFieldDlg::m_strFieldEndox[subanatomia_idcampione].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[subanatomia_idcampione].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[subanatomia_tipo].lID = -1;
	CFieldDlg::m_strFieldEndox[subanatomia_tipo].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_126);
	CFieldDlg::m_strFieldEndox[subanatomia_tipo].sReport = "Anatomia.Tipo";
	CFieldDlg::m_strFieldEndox[subanatomia_tipo].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[subanatomia_tipo].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[subanatomia_intervento].lID = -1;
	CFieldDlg::m_strFieldEndox[subanatomia_intervento].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_127);
	CFieldDlg::m_strFieldEndox[subanatomia_intervento].sReport = "Anatomia.Intervento";
	CFieldDlg::m_strFieldEndox[subanatomia_intervento].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[subanatomia_intervento].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[subanatomia_nrcampione].lID = -1;
	CFieldDlg::m_strFieldEndox[subanatomia_nrcampione].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_128);
	CFieldDlg::m_strFieldEndox[subanatomia_nrcampione].sReport = "Anatomia.NrCampione";
	CFieldDlg::m_strFieldEndox[subanatomia_nrcampione].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[subanatomia_nrcampione].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[subanatomia_notecampione].lID = -1;
	CFieldDlg::m_strFieldEndox[subanatomia_notecampione].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_231);
	CFieldDlg::m_strFieldEndox[subanatomia_notecampione].sReport = "Anatomia.NoteCampione";
	CFieldDlg::m_strFieldEndox[subanatomia_notecampione].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[subanatomia_notecampione].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[subanatomia_suggerimenti1_fisso].lID = -1;
	CFieldDlg::m_strFieldEndox[subanatomia_suggerimenti1_fisso].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_129);
	CFieldDlg::m_strFieldEndox[subanatomia_suggerimenti1_fisso].sReport = "Anatomia.Suggerimenti";
	CFieldDlg::m_strFieldEndox[subanatomia_suggerimenti1_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[subanatomia_suggerimenti1_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[subanatomia_suggerimenti1_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[subanatomia_suggerimenti1_grande].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_350);
	CFieldDlg::m_strFieldEndox[subanatomia_suggerimenti1_grande].sReport = "Anatomia.SuggerimentiGrande";
	CFieldDlg::m_strFieldEndox[subanatomia_suggerimenti1_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[subanatomia_suggerimenti1_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[subanatomia_suggerimenti2].lID = -1;
	CFieldDlg::m_strFieldEndox[subanatomia_suggerimenti2].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_297);
	CFieldDlg::m_strFieldEndox[subanatomia_suggerimenti2].sReport = "Anatomia.Suggerimenti2";
	CFieldDlg::m_strFieldEndox[subanatomia_suggerimenti2].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[subanatomia_suggerimenti2].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[subanatomia_spedireritirare].lID = -1;
	CFieldDlg::m_strFieldEndox[subanatomia_spedireritirare].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_261);
	CFieldDlg::m_strFieldEndox[subanatomia_spedireritirare].sReport = "Anatomia.SpedireRitirare";
	CFieldDlg::m_strFieldEndox[subanatomia_spedireritirare].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[subanatomia_spedireritirare].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[subanatomia_indirizzoalternativo].lID = -1;
	CFieldDlg::m_strFieldEndox[subanatomia_indirizzoalternativo].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_262);
	CFieldDlg::m_strFieldEndox[subanatomia_indirizzoalternativo].sReport = "Anatomia.IndirizzoAlternativo";
	CFieldDlg::m_strFieldEndox[subanatomia_indirizzoalternativo].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[subanatomia_indirizzoalternativo].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[subanatomia_note].lID = -1;
	CFieldDlg::m_strFieldEndox[subanatomia_note].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_264);
	CFieldDlg::m_strFieldEndox[subanatomia_note].sReport = "Anatomia.Note";
	CFieldDlg::m_strFieldEndox[subanatomia_note].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[subanatomia_note].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[subistologia_riga].lID = -1;
	CFieldDlg::m_strFieldEndox[subistologia_riga].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_336);
	CFieldDlg::m_strFieldEndox[subistologia_riga].sReport = "Istologia.Riga";
	CFieldDlg::m_strFieldEndox[subistologia_riga].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[subistologia_riga].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[subistologia_tipo].lID = -1;
	CFieldDlg::m_strFieldEndox[subistologia_tipo].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_321);
	CFieldDlg::m_strFieldEndox[subistologia_tipo].sReport = "Istologia.Tipo";
	CFieldDlg::m_strFieldEndox[subistologia_tipo].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[subistologia_tipo].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[subistologia_organo].lID = -1;
	CFieldDlg::m_strFieldEndox[subistologia_organo].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_322);
	CFieldDlg::m_strFieldEndox[subistologia_organo].sReport = "Istologia.Organo";
	CFieldDlg::m_strFieldEndox[subistologia_organo].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[subistologia_organo].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[subistologia_sede].lID = -1;
	CFieldDlg::m_strFieldEndox[subistologia_sede].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_323);
	CFieldDlg::m_strFieldEndox[subistologia_sede].sReport = "Istologia.Sede";
	CFieldDlg::m_strFieldEndox[subistologia_sede].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[subistologia_sede].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[subistologia_numero].lID = -1;
	CFieldDlg::m_strFieldEndox[subistologia_numero].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_324);
	CFieldDlg::m_strFieldEndox[subistologia_numero].sReport = "Istologia.Numero";
	CFieldDlg::m_strFieldEndox[subistologia_numero].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[subistologia_numero].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[subistologia_procedura].lID = -1;
	CFieldDlg::m_strFieldEndox[subistologia_procedura].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_521);
	CFieldDlg::m_strFieldEndox[subistologia_procedura].sReport = "Istologia.Procedura";
	CFieldDlg::m_strFieldEndox[subistologia_procedura].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[subistologia_procedura].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[subistologia_diagnosi].lID = -1;
	CFieldDlg::m_strFieldEndox[subistologia_diagnosi].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_325);
	CFieldDlg::m_strFieldEndox[subistologia_diagnosi].sReport = "Istologia.Diagnosi";
	CFieldDlg::m_strFieldEndox[subistologia_diagnosi].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[subistologia_diagnosi].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_allergie].lID = SUB_ALLERGIE;
	CFieldDlg::m_strFieldEndox[form_allergie].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_292);
	CFieldDlg::m_strFieldEndox[form_allergie].sReport = "Form.Allergie";
	CFieldDlg::m_strFieldEndox[form_allergie].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_allergie].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_pacemaker].lID = SUB_PACEMAKER;
	CFieldDlg::m_strFieldEndox[form_pacemaker].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_293);
	CFieldDlg::m_strFieldEndox[form_pacemaker].sReport = "Form.Pacemaker";
	CFieldDlg::m_strFieldEndox[form_pacemaker].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_pacemaker].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_portatorepacemaker].lID = SUB_PORTATOREPACEMAKER;
	CFieldDlg::m_strFieldEndox[form_portatorepacemaker].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_303);
	CFieldDlg::m_strFieldEndox[form_portatorepacemaker].sReport = "Form.PortatorePacemaker";
	CFieldDlg::m_strFieldEndox[form_portatorepacemaker].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_portatorepacemaker].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_anticoagulanti].lID = SUB_ANTICOAGULANTI;
	CFieldDlg::m_strFieldEndox[form_anticoagulanti].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_304);
	CFieldDlg::m_strFieldEndox[form_anticoagulanti].sReport = "Form.Anticoagulanti";
	CFieldDlg::m_strFieldEndox[form_anticoagulanti].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_anticoagulanti].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_antiaggreganti].lID = SUB_ANTIAGGREGANTI;
	CFieldDlg::m_strFieldEndox[form_antiaggreganti].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_305);
	CFieldDlg::m_strFieldEndox[form_antiaggreganti].sReport = "Form.Antiaggreganti";
	CFieldDlg::m_strFieldEndox[form_antiaggreganti].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_antiaggreganti].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_anatomiapatologicatasti].lID = SUB_ANATOMIAPATOLOGICATASTI;
	CFieldDlg::m_strFieldEndox[form_anatomiapatologicatasti].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_296);
	CFieldDlg::m_strFieldEndox[form_anatomiapatologicatasti].sReport = "SpedireAltroIndirizzo";
	CFieldDlg::m_strFieldEndox[form_anatomiapatologicatasti].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_anatomiapatologicatasti].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_rao].lID = SUB_RAO;
	CFieldDlg::m_strFieldEndox[form_rao].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_93);
	CFieldDlg::m_strFieldEndox[form_rao].sReport = "Form.RAO";
	CFieldDlg::m_strFieldEndox[form_rao].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_rao].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_consensoinformato].lID = SUB_CONSENSOINFORMATO;
	CFieldDlg::m_strFieldEndox[form_consensoinformato].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_94);
	CFieldDlg::m_strFieldEndox[form_consensoinformato].sReport = "Form.ConsensoInformato";
	CFieldDlg::m_strFieldEndox[form_consensoinformato].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_consensoinformato].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[preliminari_inviante_i].lID = EDT_INVIANTE_I;
	CFieldDlg::m_strFieldEndox[preliminari_inviante_i].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_334);
	CFieldDlg::m_strFieldEndox[preliminari_inviante_i].sReport = "Scheda.InvianteI";
	CFieldDlg::m_strFieldEndox[preliminari_inviante_i].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_inviante_i].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[preliminari_inviante_e].lID = EDT_INVIANTE_E;
	CFieldDlg::m_strFieldEndox[preliminari_inviante_e].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_335);
	CFieldDlg::m_strFieldEndox[preliminari_inviante_e].sReport = "Scheda.InvianteE";
	CFieldDlg::m_strFieldEndox[preliminari_inviante_e].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_inviante_e].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_sedeprevista].lID = EDT_ORGANOSEDEPREVISTA;
	CFieldDlg::m_strFieldEndox[form_sedeprevista].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_479);
	CFieldDlg::m_strFieldEndox[form_sedeprevista].sReport = "Scheda.SedePrevista";
	CFieldDlg::m_strFieldEndox[form_sedeprevista].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_sedeprevista].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_sederaggiunta].lID = EDT_ORGANOSEDERAGGIUNTA;
	CFieldDlg::m_strFieldEndox[form_sederaggiunta].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_480);
	CFieldDlg::m_strFieldEndox[form_sederaggiunta].sReport = "Scheda.SedeRaggiunta";
	CFieldDlg::m_strFieldEndox[form_sederaggiunta].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_sederaggiunta].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[screening_complicanzeimmediate].lID = CMB_COMPLICANZEIMMEDIATE;
	CFieldDlg::m_strFieldEndox[screening_complicanzeimmediate].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_356);
	CFieldDlg::m_strFieldEndox[screening_complicanzeimmediate].sReport = "Screening.ComplicanzeImmediate";
	CFieldDlg::m_strFieldEndox[screening_complicanzeimmediate].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[screening_complicanzeimmediate].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[screening_complicanzetardive].lID = CMB_COMPLICANZETARDIVE;
	CFieldDlg::m_strFieldEndox[screening_complicanzetardive].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_357);
	CFieldDlg::m_strFieldEndox[screening_complicanzetardive].sReport = "Screening.ComplicanzeTardive";
	CFieldDlg::m_strFieldEndox[screening_complicanzetardive].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[screening_complicanzetardive].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[screening_pulizia].lID = CMB_PULIZIA;
	CFieldDlg::m_strFieldEndox[screening_pulizia].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_358);
	CFieldDlg::m_strFieldEndox[screening_pulizia].sReport = "Screening.Pulizia";
	CFieldDlg::m_strFieldEndox[screening_pulizia].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[screening_pulizia].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[screening_causenoncompletamento].lID = CMB_CAUSENONCOMPLETAMENTO;
	CFieldDlg::m_strFieldEndox[screening_causenoncompletamento].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_359);
	CFieldDlg::m_strFieldEndox[screening_causenoncompletamento].sReport = "Screening.CauseNonCompletamento";
	CFieldDlg::m_strFieldEndox[screening_causenoncompletamento].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[screening_causenoncompletamento].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[screening_tolleranza].lID = CMB_TOLLERANZA;
	CFieldDlg::m_strFieldEndox[screening_tolleranza].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_360);
	CFieldDlg::m_strFieldEndox[screening_tolleranza].sReport = "Screening.Tolleranza";
	CFieldDlg::m_strFieldEndox[screening_tolleranza].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[screening_tolleranza].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[screening_conclusioniscreening].lID = CMB_CONCLUSIONISCREENING;
	CFieldDlg::m_strFieldEndox[screening_conclusioniscreening].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_361);
	CFieldDlg::m_strFieldEndox[screening_conclusioniscreening].sReport = "Screening.ConclusioniScreening";
	CFieldDlg::m_strFieldEndox[screening_conclusioniscreening].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[screening_conclusioniscreening].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[screening_conclusionicolon].lID = CMB_CONCLUSIONICOLON;
	CFieldDlg::m_strFieldEndox[screening_conclusionicolon].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_362);
	CFieldDlg::m_strFieldEndox[screening_conclusionicolon].sReport = "Screening.ConclusioniColon";
	CFieldDlg::m_strFieldEndox[screening_conclusionicolon].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[screening_conclusionicolon].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[screening_diagnosifinale].lID = CMB_DIAGNOSIFINALE;
	CFieldDlg::m_strFieldEndox[screening_diagnosifinale].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_378);
	CFieldDlg::m_strFieldEndox[screening_diagnosifinale].sReport = "Screening.DiagosiFinale";
	CFieldDlg::m_strFieldEndox[screening_diagnosifinale].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[screening_diagnosifinale].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[screening_altreanomalie].lID = CMB_ALTREANOMALIE;
	CFieldDlg::m_strFieldEndox[screening_altreanomalie].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_569);
	CFieldDlg::m_strFieldEndox[screening_altreanomalie].sReport = "Screening.AltreAnomalie";
	CFieldDlg::m_strFieldEndox[screening_altreanomalie].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[screening_altreanomalie].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[preliminari_premedposologia].lID = EDT_PREMEDPOSOLOGIA;
	CFieldDlg::m_strFieldEndox[preliminari_premedposologia].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_364);
	CFieldDlg::m_strFieldEndox[preliminari_premedposologia].sReport = "Scheda.PremedicazioniPosologia";
	CFieldDlg::m_strFieldEndox[preliminari_premedposologia].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[preliminari_premedposologia].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[esame_mst_complicanze1_fisso].lID = EDT_MST_COMPLICANZE1;
	CFieldDlg::m_strFieldEndox[esame_mst_complicanze1_fisso].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_369);
	CFieldDlg::m_strFieldEndox[esame_mst_complicanze1_fisso].sReport = "Scheda.MstComplicanze1Fisso";
	CFieldDlg::m_strFieldEndox[esame_mst_complicanze1_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esame_mst_complicanze1_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[esame_mst_complicanze1_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[esame_mst_complicanze1_grande].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_370);
	CFieldDlg::m_strFieldEndox[esame_mst_complicanze1_grande].sReport = "Scheda.MstComplicanze1Grande";
	CFieldDlg::m_strFieldEndox[esame_mst_complicanze1_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esame_mst_complicanze1_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[esame_mst_complicanze2_fisso].lID = EDT_MST_COMPLICANZE2;
	CFieldDlg::m_strFieldEndox[esame_mst_complicanze2_fisso].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_371);
	CFieldDlg::m_strFieldEndox[esame_mst_complicanze2_fisso].sReport = "Scheda.MstComplicanze2Fisso";
	CFieldDlg::m_strFieldEndox[esame_mst_complicanze2_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esame_mst_complicanze2_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[esame_mst_complicanze2_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[esame_mst_complicanze2_grande].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_372);
	CFieldDlg::m_strFieldEndox[esame_mst_complicanze2_grande].sReport = "Scheda.MstComplicanze2Grande";
	CFieldDlg::m_strFieldEndox[esame_mst_complicanze2_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esame_mst_complicanze2_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[esame_mst_complicanze3_fisso].lID = EDT_MST_COMPLICANZE3;
	CFieldDlg::m_strFieldEndox[esame_mst_complicanze3_fisso].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_373);
	CFieldDlg::m_strFieldEndox[esame_mst_complicanze3_fisso].sReport = "Scheda.MstComplicanze3Fisso";
	CFieldDlg::m_strFieldEndox[esame_mst_complicanze3_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esame_mst_complicanze3_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[esame_mst_complicanze3_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[esame_mst_complicanze3_grande].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_374);
	CFieldDlg::m_strFieldEndox[esame_mst_complicanze3_grande].sReport = "Scheda.MstComplicanze3Grande";
	CFieldDlg::m_strFieldEndox[esame_mst_complicanze3_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esame_mst_complicanze3_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_breathtest_hp_risultato].lID = -1;
	CFieldDlg::m_strFieldEndox[form_breathtest_hp_risultato].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_377);
	CFieldDlg::m_strFieldEndox[form_breathtest_hp_risultato].sReport = "Breath_Test_HP_Risultato";
	CFieldDlg::m_strFieldEndox[form_breathtest_hp_risultato].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_breathtest_hp_risultato].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_breathtest_hp_valore1].lID = -1;
	CFieldDlg::m_strFieldEndox[form_breathtest_hp_valore1].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_379);
	CFieldDlg::m_strFieldEndox[form_breathtest_hp_valore1].sReport = "Breath_Test_HP_Valore1";
	CFieldDlg::m_strFieldEndox[form_breathtest_hp_valore1].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_breathtest_hp_valore1].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_breathtest_hp_valore2].lID = -1;
	CFieldDlg::m_strFieldEndox[form_breathtest_hp_valore2].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_380);
	CFieldDlg::m_strFieldEndox[form_breathtest_hp_valore2].sReport = "Breath_Test_HP_Valore2";
	CFieldDlg::m_strFieldEndox[form_breathtest_hp_valore2].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_breathtest_hp_valore2].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_breathtest_hp_differenza].lID = -1;
	CFieldDlg::m_strFieldEndox[form_breathtest_hp_differenza].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_381);
	CFieldDlg::m_strFieldEndox[form_breathtest_hp_differenza].sReport = "Breath_Test_HP_Differenza";
	CFieldDlg::m_strFieldEndox[form_breathtest_hp_differenza].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_breathtest_hp_differenza].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_sospensione_si_no].lID = -1;
	CFieldDlg::m_strFieldEndox[form_sospensione_si_no].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_383);
	CFieldDlg::m_strFieldEndox[form_sospensione_si_no].sReport = "Sospensione_Si_No";
	CFieldDlg::m_strFieldEndox[form_sospensione_si_no].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_sospensione_si_no].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_sospensione_data].lID = -1;
	CFieldDlg::m_strFieldEndox[form_sospensione_data].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_384);
	CFieldDlg::m_strFieldEndox[form_sospensione_data].sReport = "Sospensione_Data";
	CFieldDlg::m_strFieldEndox[form_sospensione_data].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_sospensione_data].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_sospensione_motivo].lID = -1;
	CFieldDlg::m_strFieldEndox[form_sospensione_motivo].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_385);
	CFieldDlg::m_strFieldEndox[form_sospensione_motivo].sReport = "Sospensione_Motivo";
	CFieldDlg::m_strFieldEndox[form_sospensione_motivo].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_sospensione_motivo].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_procedure_icd9].lID = SUB_PROCEDUREICD9;
	CFieldDlg::m_strFieldEndox[form_procedure_icd9].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_386);
	CFieldDlg::m_strFieldEndox[form_procedure_icd9].sReport = "Procedure ICD9";
	CFieldDlg::m_strFieldEndox[form_procedure_icd9].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_procedure_icd9].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_diagnosi_icd9].lID = SUB_DIAGNOSIICD9;
	CFieldDlg::m_strFieldEndox[form_diagnosi_icd9].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_387);
	CFieldDlg::m_strFieldEndox[form_diagnosi_icd9].sReport = "Diagnosi ICD9";
	CFieldDlg::m_strFieldEndox[form_diagnosi_icd9].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_diagnosi_icd9].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_newaccessori_fisso].lID = -1;
	CFieldDlg::m_strFieldEndox[form_newaccessori_fisso].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_392);
	CFieldDlg::m_strFieldEndox[form_newaccessori_fisso].sReport = "Accessori New Fisso";
	CFieldDlg::m_strFieldEndox[form_newaccessori_fisso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_newaccessori_fisso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[form_newaccessori_grande].lID = -1;
	CFieldDlg::m_strFieldEndox[form_newaccessori_grande].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_393);
	CFieldDlg::m_strFieldEndox[form_newaccessori_grande].sReport = "Accessori New Grande";
	CFieldDlg::m_strFieldEndox[form_newaccessori_grande].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[form_newaccessori_grande].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[esame_codesame].lID = EDT_CODESAME;
	CFieldDlg::m_strFieldEndox[esame_codesame].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_413);
	CFieldDlg::m_strFieldEndox[esame_codesame].sReport = "Esame.Codesame";
	CFieldDlg::m_strFieldEndox[esame_codesame].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esame_codesame].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[esame_tempochiusura].lID = EDT_TEMPOCHIUSURA;
	CFieldDlg::m_strFieldEndox[esame_tempochiusura].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_415);
	CFieldDlg::m_strFieldEndox[esame_tempochiusura].sReport = "Esame.TempoChiusura";
	CFieldDlg::m_strFieldEndox[esame_tempochiusura].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esame_tempochiusura].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[esame_tempoconvalida].lID = EDT_TEMPOCONVALIDA;
	CFieldDlg::m_strFieldEndox[esame_tempoconvalida].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_416);
	CFieldDlg::m_strFieldEndox[esame_tempoconvalida].sReport = "Esame.TempoConvalida";
	CFieldDlg::m_strFieldEndox[esame_tempoconvalida].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esame_tempoconvalida].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[esame_codicericovero].lID = EDT_CODICERICOVERO;
	CFieldDlg::m_strFieldEndox[esame_codicericovero].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_417);
	CFieldDlg::m_strFieldEndox[esame_codicericovero].sReport = "Esame.CodiceRicovero";
	CFieldDlg::m_strFieldEndox[esame_codicericovero].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esame_codicericovero].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[esame_barcodericovero].lID = EDT_BARCODERICOVERO;
	CFieldDlg::m_strFieldEndox[esame_barcodericovero].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_467);
	CFieldDlg::m_strFieldEndox[esame_barcodericovero].sReport = "Esame.BarcodeRicovero";
	CFieldDlg::m_strFieldEndox[esame_barcodericovero].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esame_barcodericovero].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[esame_dataoralock].lID = BTN_CONVALIDA;
	CFieldDlg::m_strFieldEndox[esame_dataoralock].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_436);
	CFieldDlg::m_strFieldEndox[esame_dataoralock].sReport = "Esame.DataOraConvalida";
	CFieldDlg::m_strFieldEndox[esame_dataoralock].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esame_dataoralock].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[esame_dataorasuperlock].lID = BTN_CHIUSURAESAME;
	CFieldDlg::m_strFieldEndox[esame_dataorasuperlock].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_437);
	CFieldDlg::m_strFieldEndox[esame_dataorasuperlock].sReport = "Esame.DataOraChiusuraEsame";
	CFieldDlg::m_strFieldEndox[esame_dataorasuperlock].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esame_dataorasuperlock].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[inps_medico_codicefiscale].lID = -1;
	CFieldDlg::m_strFieldEndox[inps_medico_codicefiscale].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_444);
	CFieldDlg::m_strFieldEndox[inps_medico_codicefiscale].sReport = "Inps.Medico.CodiceFiscale";
	CFieldDlg::m_strFieldEndox[inps_medico_codicefiscale].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[inps_medico_codicefiscale].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[inps_reperibilita_cognome].lID = -1;
	CFieldDlg::m_strFieldEndox[inps_reperibilita_cognome].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_445);
	CFieldDlg::m_strFieldEndox[inps_reperibilita_cognome].sReport = "Inps.Reperibilita.Cognome";
	CFieldDlg::m_strFieldEndox[inps_reperibilita_cognome].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[inps_reperibilita_cognome].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[inps_reperibilita_via].lID = -1;
	CFieldDlg::m_strFieldEndox[inps_reperibilita_via].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_446);
	CFieldDlg::m_strFieldEndox[inps_reperibilita_via].sReport = "Inps.Reperibilita.Via";
	CFieldDlg::m_strFieldEndox[inps_reperibilita_via].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[inps_reperibilita_via].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[inps_reperibilita_cap].lID = -1;
	CFieldDlg::m_strFieldEndox[inps_reperibilita_cap].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_447);
	CFieldDlg::m_strFieldEndox[inps_reperibilita_cap].sReport = "Inps.Reperibilita.Cap";
	CFieldDlg::m_strFieldEndox[inps_reperibilita_cap].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[inps_reperibilita_cap].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[inps_reperibilita_comune].lID = -1;
	CFieldDlg::m_strFieldEndox[inps_reperibilita_comune].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_448);
	CFieldDlg::m_strFieldEndox[inps_reperibilita_comune].sReport = "Inps.Reperibilita.Comune";
	CFieldDlg::m_strFieldEndox[inps_reperibilita_comune].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[inps_reperibilita_comune].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[inps_reperibilita_provincia].lID = -1;
	CFieldDlg::m_strFieldEndox[inps_reperibilita_provincia].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_449);
	CFieldDlg::m_strFieldEndox[inps_reperibilita_provincia].sReport = "Inps.Reperibilita.Provincia";
	CFieldDlg::m_strFieldEndox[inps_reperibilita_provincia].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[inps_reperibilita_provincia].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[inps_datainizio].lID = -1;
	CFieldDlg::m_strFieldEndox[inps_datainizio].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_450);
	CFieldDlg::m_strFieldEndox[inps_datainizio].sReport = "Inps.DataInizio";
	CFieldDlg::m_strFieldEndox[inps_datainizio].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[inps_datainizio].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[inps_datafine].lID = -1;
	CFieldDlg::m_strFieldEndox[inps_datafine].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_451);
	CFieldDlg::m_strFieldEndox[inps_datafine].sReport = "Inps.DataFine";
	CFieldDlg::m_strFieldEndox[inps_datafine].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[inps_datafine].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[inps_tipocertificato].lID = -1;
	CFieldDlg::m_strFieldEndox[inps_tipocertificato].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_452);
	CFieldDlg::m_strFieldEndox[inps_tipocertificato].sReport = "Inps.TipoCertificato";
	CFieldDlg::m_strFieldEndox[inps_tipocertificato].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[inps_tipocertificato].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[inps_diagnosinote].lID = -1;
	CFieldDlg::m_strFieldEndox[inps_diagnosinote].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_453);
	CFieldDlg::m_strFieldEndox[inps_diagnosinote].sReport = "Inps.Diagnosi.Note";
	CFieldDlg::m_strFieldEndox[inps_diagnosinote].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[inps_diagnosinote].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[inps_numeroprotocollo].lID = -1;
	CFieldDlg::m_strFieldEndox[inps_numeroprotocollo].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_469);
	CFieldDlg::m_strFieldEndox[inps_numeroprotocollo].sReport = "Inps.NumeroProtocollo";
	CFieldDlg::m_strFieldEndox[inps_numeroprotocollo].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[inps_numeroprotocollo].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[esamestrumentale_orainizio].lID = -1;
	CFieldDlg::m_strFieldEndox[esamestrumentale_orainizio].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_458);
	CFieldDlg::m_strFieldEndox[esamestrumentale_orainizio].sReport = "EsameStrumentale.OraInizio";
	CFieldDlg::m_strFieldEndox[esamestrumentale_orainizio].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esamestrumentale_orainizio].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[esamestrumentale_orafine].lID = -1;
	CFieldDlg::m_strFieldEndox[esamestrumentale_orafine].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_459);
	CFieldDlg::m_strFieldEndox[esamestrumentale_orafine].sReport = "EsameStrumentale.OraFine";
	CFieldDlg::m_strFieldEndox[esamestrumentale_orafine].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esamestrumentale_orafine].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[esamestrumentale_durata_oreminuti].lID = -1;
	CFieldDlg::m_strFieldEndox[esamestrumentale_durata_oreminuti].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_460);
	CFieldDlg::m_strFieldEndox[esamestrumentale_durata_oreminuti].sReport = "EsameStrumentale.Durata.OreMinuti";
	CFieldDlg::m_strFieldEndox[esamestrumentale_durata_oreminuti].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esamestrumentale_durata_oreminuti].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[esamestrumentale_durata_solominuti].lID = -1;
	CFieldDlg::m_strFieldEndox[esamestrumentale_durata_solominuti].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_461);
	CFieldDlg::m_strFieldEndox[esamestrumentale_durata_solominuti].sReport = "EsameStrumentale.Durata.SoloMinuti";
	CFieldDlg::m_strFieldEndox[esamestrumentale_durata_solominuti].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esamestrumentale_durata_solominuti].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[pazientecronico_score_hb].lID = EDT_PAZIENTICRONICI_SCORE_HB;
	CFieldDlg::m_strFieldEndox[pazientecronico_score_hb].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_485);
	CFieldDlg::m_strFieldEndox[pazientecronico_score_hb].sReport = "PazienteCronico.Score.HB";
	CFieldDlg::m_strFieldEndox[pazientecronico_score_hb].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[pazientecronico_score_hb].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[pazientecronico_score_s].lID = EDT_PAZIENTICRONICI_SCORE_S;
	CFieldDlg::m_strFieldEndox[pazientecronico_score_s].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_486);
	CFieldDlg::m_strFieldEndox[pazientecronico_score_s].sReport = "PazienteCronico.Score.S";
	CFieldDlg::m_strFieldEndox[pazientecronico_score_s].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[pazientecronico_score_s].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[studio_descrizione].lID = -1;
	CFieldDlg::m_strFieldEndox[studio_descrizione].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_489);
	CFieldDlg::m_strFieldEndox[studio_descrizione].sReport = "Studio.Descrizione";
	CFieldDlg::m_strFieldEndox[studio_descrizione].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[studio_descrizione].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[studio_data].lID = -1;
	CFieldDlg::m_strFieldEndox[studio_data].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_490);
	CFieldDlg::m_strFieldEndox[studio_data].sReport = "Studio.Data";
	CFieldDlg::m_strFieldEndox[studio_data].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[studio_data].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[studio_tempotrascorso].lID = -1;
	CFieldDlg::m_strFieldEndox[studio_tempotrascorso].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_491);
	CFieldDlg::m_strFieldEndox[studio_tempotrascorso].sReport = "Studio.TempoTrascorso";
	CFieldDlg::m_strFieldEndox[studio_tempotrascorso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[studio_tempotrascorso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[utente_inserimentoesame].lID = -1;
	CFieldDlg::m_strFieldEndox[utente_inserimentoesame].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_496);
	CFieldDlg::m_strFieldEndox[utente_inserimentoesame].sReport = "Utente.InserimentoEsame";
	CFieldDlg::m_strFieldEndox[utente_inserimentoesame].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[utente_inserimentoesame].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[bostonscore_score_dx].lID = -1;
	CFieldDlg::m_strFieldEndox[bostonscore_score_dx].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_509);
	CFieldDlg::m_strFieldEndox[bostonscore_score_dx].sReport = "BostonScore.Score.Dx";
	CFieldDlg::m_strFieldEndox[bostonscore_score_dx].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[bostonscore_score_dx].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[bostonscore_score_mid].lID = -1;
	CFieldDlg::m_strFieldEndox[bostonscore_score_mid].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_510);
	CFieldDlg::m_strFieldEndox[bostonscore_score_mid].sReport = "BostonScore.Score.Mid";
	CFieldDlg::m_strFieldEndox[bostonscore_score_mid].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[bostonscore_score_mid].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[bostonscore_score_sx].lID = -1;
	CFieldDlg::m_strFieldEndox[bostonscore_score_sx].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_511);
	CFieldDlg::m_strFieldEndox[bostonscore_score_sx].sReport = "BostonScore.Score.Sx";
	CFieldDlg::m_strFieldEndox[bostonscore_score_sx].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[bostonscore_score_sx].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[bostonscore_score_totale].lID = SUB_BOSTONSCORE;
	CFieldDlg::m_strFieldEndox[bostonscore_score_totale].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_512);
	CFieldDlg::m_strFieldEndox[bostonscore_score_totale].sReport = "BostonScore.Score.Totale";
	CFieldDlg::m_strFieldEndox[bostonscore_score_totale].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[bostonscore_score_totale].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[bostonscore_descrizione_totale].lID = -1;
	CFieldDlg::m_strFieldEndox[bostonscore_descrizione_totale].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_513);
	CFieldDlg::m_strFieldEndox[bostonscore_descrizione_totale].sReport = "BostonScore.Descrizione.Totale";
	CFieldDlg::m_strFieldEndox[bostonscore_descrizione_totale].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[bostonscore_descrizione_totale].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[esame_temporetrazione].lID = EDT_TEMPORETRAZIONE;
	CFieldDlg::m_strFieldEndox[esame_temporetrazione].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_514);
	CFieldDlg::m_strFieldEndox[esame_temporetrazione].sReport = "Esame.TempoRetrazione";
	CFieldDlg::m_strFieldEndox[esame_temporetrazione].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esame_temporetrazione].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[worklist_note].lID = -1;
	CFieldDlg::m_strFieldEndox[worklist_note].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_522);
	CFieldDlg::m_strFieldEndox[worklist_note].sReport = "Worklist.Note";
	CFieldDlg::m_strFieldEndox[worklist_note].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[worklist_note].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[worklist_assiden].lID = -1;
	CFieldDlg::m_strFieldEndox[worklist_assiden].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_523);
	CFieldDlg::m_strFieldEndox[worklist_assiden].sReport = "Worklist.AssIden";
	CFieldDlg::m_strFieldEndox[worklist_assiden].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[worklist_assiden].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[worklist_cognome].lID = -1;
	CFieldDlg::m_strFieldEndox[worklist_cognome].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_524);
	CFieldDlg::m_strFieldEndox[worklist_cognome].sReport = "Worklist.Cognome";
	CFieldDlg::m_strFieldEndox[worklist_cognome].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[worklist_cognome].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[worklist_cognome2].lID = -1;
	CFieldDlg::m_strFieldEndox[worklist_cognome2].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_525);
	CFieldDlg::m_strFieldEndox[worklist_cognome2].sReport = "Worklist.Cognome2";
	CFieldDlg::m_strFieldEndox[worklist_cognome2].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[worklist_cognome2].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[worklist_nome].lID = -1;
	CFieldDlg::m_strFieldEndox[worklist_nome].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_526);
	CFieldDlg::m_strFieldEndox[worklist_nome].sReport = "Worklist.Nome";
	CFieldDlg::m_strFieldEndox[worklist_nome].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[worklist_nome].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[worklist_datanascita].lID = -1;
	CFieldDlg::m_strFieldEndox[worklist_datanascita].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_527);
	CFieldDlg::m_strFieldEndox[worklist_datanascita].sReport = "Worklist.DataNascita";
	CFieldDlg::m_strFieldEndox[worklist_datanascita].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[worklist_datanascita].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[worklist_comunenascita].lID = -1;
	CFieldDlg::m_strFieldEndox[worklist_comunenascita].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_528);
	CFieldDlg::m_strFieldEndox[worklist_comunenascita].sReport = "Worklist.ComuneNascita";
	CFieldDlg::m_strFieldEndox[worklist_comunenascita].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[worklist_comunenascita].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[worklist_indirizzoresidenza].lID = -1;
	CFieldDlg::m_strFieldEndox[worklist_indirizzoresidenza].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_529);
	CFieldDlg::m_strFieldEndox[worklist_indirizzoresidenza].sReport = "Worklist.IndirizzoResidenza";
	CFieldDlg::m_strFieldEndox[worklist_indirizzoresidenza].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[worklist_indirizzoresidenza].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[worklist_comuneresidenza].lID = -1;
	CFieldDlg::m_strFieldEndox[worklist_comuneresidenza].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_530);
	CFieldDlg::m_strFieldEndox[worklist_comuneresidenza].sReport = "Worklist.ComuneResidenza";
	CFieldDlg::m_strFieldEndox[worklist_comuneresidenza].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[worklist_comuneresidenza].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[worklist_capresidenza].lID = -1;
	CFieldDlg::m_strFieldEndox[worklist_capresidenza].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_531);
	CFieldDlg::m_strFieldEndox[worklist_capresidenza].sReport = "Worklist.CapResidenza";
	CFieldDlg::m_strFieldEndox[worklist_capresidenza].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[worklist_capresidenza].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[worklist_telefono1].lID = -1;
	CFieldDlg::m_strFieldEndox[worklist_telefono1].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_532);
	CFieldDlg::m_strFieldEndox[worklist_telefono1].sReport = "Worklist.Telefono1";
	CFieldDlg::m_strFieldEndox[worklist_telefono1].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[worklist_telefono1].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[worklist_telefono2].lID = -1;
	CFieldDlg::m_strFieldEndox[worklist_telefono2].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_533);
	CFieldDlg::m_strFieldEndox[worklist_telefono2].sReport = "Worklist.Telefono2";
	CFieldDlg::m_strFieldEndox[worklist_telefono2].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[worklist_telefono2].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[worklist_cellulare1].lID = -1;
	CFieldDlg::m_strFieldEndox[worklist_cellulare1].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_534);
	CFieldDlg::m_strFieldEndox[worklist_cellulare1].sReport = "Worklist.Cellulare1";
	CFieldDlg::m_strFieldEndox[worklist_cellulare1].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[worklist_cellulare1].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[worklist_cellulare2].lID = -1;
	CFieldDlg::m_strFieldEndox[worklist_cellulare2].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_535);
	CFieldDlg::m_strFieldEndox[worklist_cellulare2].sReport = "Worklist.Cellulare2";
	CFieldDlg::m_strFieldEndox[worklist_cellulare2].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[worklist_cellulare2].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[worklist_codicefiscale].lID = -1;
	CFieldDlg::m_strFieldEndox[worklist_codicefiscale].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_536);
	CFieldDlg::m_strFieldEndox[worklist_codicefiscale].sReport = "Worklist.CodiceFiscale";
	CFieldDlg::m_strFieldEndox[worklist_codicefiscale].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[worklist_codicefiscale].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[worklist_codicesanitario].lID = -1;
	CFieldDlg::m_strFieldEndox[worklist_codicesanitario].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_537);
	CFieldDlg::m_strFieldEndox[worklist_codicesanitario].sReport = "Worklist.CodiceSanitario";
	CFieldDlg::m_strFieldEndox[worklist_codicesanitario].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[worklist_codicesanitario].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[worklist_codicestp].lID = -1;
	CFieldDlg::m_strFieldEndox[worklist_codicestp].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_538);
	CFieldDlg::m_strFieldEndox[worklist_codicestp].sReport = "Worklist.CodiceStp";
	CFieldDlg::m_strFieldEndox[worklist_codicestp].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[worklist_codicestp].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[worklist_codiceteam].lID = -1;
	CFieldDlg::m_strFieldEndox[worklist_codiceteam].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_539);
	CFieldDlg::m_strFieldEndox[worklist_codiceteam].sReport = "Worklist.CodiceTeam";
	CFieldDlg::m_strFieldEndox[worklist_codiceteam].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[worklist_codiceteam].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[worklist_sesso].lID = -1;
	CFieldDlg::m_strFieldEndox[worklist_sesso].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_540);
	CFieldDlg::m_strFieldEndox[worklist_sesso].sReport = "Worklist.Sesso";
	CFieldDlg::m_strFieldEndox[worklist_sesso].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[worklist_sesso].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[worklist_medicocurante].lID = -1;
	CFieldDlg::m_strFieldEndox[worklist_medicocurante].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_541);
	CFieldDlg::m_strFieldEndox[worklist_medicocurante].sReport = "Worklist.MedicoCurante";
	CFieldDlg::m_strFieldEndox[worklist_medicocurante].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[worklist_medicocurante].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[worklist_cittadinanza].lID = -1;
	CFieldDlg::m_strFieldEndox[worklist_cittadinanza].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_542);
	CFieldDlg::m_strFieldEndox[worklist_cittadinanza].sReport = "Worklist.Cittadinanza";
	CFieldDlg::m_strFieldEndox[worklist_cittadinanza].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[worklist_cittadinanza].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[worklist_provincia].lID = -1;
	CFieldDlg::m_strFieldEndox[worklist_provincia].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_543);
	CFieldDlg::m_strFieldEndox[worklist_provincia].sReport = "Worklist.Provincia";
	CFieldDlg::m_strFieldEndox[worklist_provincia].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[worklist_provincia].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[utenteconvalida_anagrafica].lID = -1;
	CFieldDlg::m_strFieldEndox[utenteconvalida_anagrafica].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_548);
	CFieldDlg::m_strFieldEndox[utenteconvalida_anagrafica].sReport = "ConvalidaEsame.Anagrafica";
	CFieldDlg::m_strFieldEndox[utenteconvalida_anagrafica].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[utenteconvalida_anagrafica].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[utenteconvalida_firma0].lID = -1;
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma0].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_549);
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma0].sReport = "UtenteConvalida.Firma0";
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma0].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma0].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[utenteconvalida_firma1].lID = -1;
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma1].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_550);
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma1].sReport = "UtenteConvalida.Firma1";
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma1].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma1].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[utenteconvalida_firma2].lID = -1;
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma2].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_551);
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma2].sReport = "UtenteConvalida.Firma2";
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma2].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma2].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[utenteconvalida_firma3].lID = -1;
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma3].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_552);
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma3].sReport = "UtenteConvalida.Firma3";
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma3].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma3].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[utenteconvalida_firma4].lID = -1;
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma4].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_553);
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma4].sReport = "UtenteConvalida.Firma4";
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma4].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma4].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[utenteconvalida_firma5].lID = -1;
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma5].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_554);
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma5].sReport = "UtenteConvalida.Firma5";
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma5].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma5].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[utenteconvalida_firma6].lID = -1;
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma6].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_555);
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma6].sReport = "UtenteConvalida.Firma6";
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma6].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma6].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[utenteconvalida_firma7].lID = -1;
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma7].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_556);
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma7].sReport = "UtenteConvalida.Firma7";
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma7].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma7].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[utenteconvalida_firma8].lID = -1;
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma8].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_557);
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma8].sReport = "UtenteConvalida.Firma8";
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma8].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma8].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[utenteconvalida_firma9].lID = -1;
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma9].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_558);
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma9].sReport = "UtenteConvalida.Firma9";
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma9].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[utenteconvalida_firma9].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[utenteconvalida_immaginefirma].lID = -1;
	CFieldDlg::m_strFieldEndox[utenteconvalida_immaginefirma].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_546);
	CFieldDlg::m_strFieldEndox[utenteconvalida_immaginefirma].sReport = "ImmagineFirma.UtenteConvalida";
	CFieldDlg::m_strFieldEndox[utenteconvalida_immaginefirma].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[utenteconvalida_immaginefirma].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[utentechiusura_anagrafica].lID = -1;
	CFieldDlg::m_strFieldEndox[utentechiusura_anagrafica].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_493);
	CFieldDlg::m_strFieldEndox[utentechiusura_anagrafica].sReport = "ChiusuraEsame.Anagrafica";
	CFieldDlg::m_strFieldEndox[utentechiusura_anagrafica].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[utentechiusura_anagrafica].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[utentechiusura_firma0].lID = -1;
	CFieldDlg::m_strFieldEndox[utentechiusura_firma0].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_559);
	CFieldDlg::m_strFieldEndox[utentechiusura_firma0].sReport = "UtenteChiusura.Firma0";
	CFieldDlg::m_strFieldEndox[utentechiusura_firma0].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[utentechiusura_firma0].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[utentechiusura_firma1].lID = -1;
	CFieldDlg::m_strFieldEndox[utentechiusura_firma1].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_560);
	CFieldDlg::m_strFieldEndox[utentechiusura_firma1].sReport = "UtenteChiusura.Firma1";
	CFieldDlg::m_strFieldEndox[utentechiusura_firma1].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[utentechiusura_firma1].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[utentechiusura_firma2].lID = -1;
	CFieldDlg::m_strFieldEndox[utentechiusura_firma2].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_561);
	CFieldDlg::m_strFieldEndox[utentechiusura_firma2].sReport = "UtenteChiusura.Firma2";
	CFieldDlg::m_strFieldEndox[utentechiusura_firma2].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[utentechiusura_firma2].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[utentechiusura_firma3].lID = -1;
	CFieldDlg::m_strFieldEndox[utentechiusura_firma3].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_562);
	CFieldDlg::m_strFieldEndox[utentechiusura_firma3].sReport = "UtenteChiusura.Firma3";
	CFieldDlg::m_strFieldEndox[utentechiusura_firma3].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[utentechiusura_firma3].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[utentechiusura_firma4].lID = -1;
	CFieldDlg::m_strFieldEndox[utentechiusura_firma4].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_563);
	CFieldDlg::m_strFieldEndox[utentechiusura_firma4].sReport = "UtenteChiusura.Firma4";
	CFieldDlg::m_strFieldEndox[utentechiusura_firma4].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[utentechiusura_firma4].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[utentechiusura_firma5].lID = -1;
	CFieldDlg::m_strFieldEndox[utentechiusura_firma5].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_564);
	CFieldDlg::m_strFieldEndox[utentechiusura_firma5].sReport = "UtenteChiusura.Firma5";
	CFieldDlg::m_strFieldEndox[utentechiusura_firma5].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[utentechiusura_firma5].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[utentechiusura_firma6].lID = -1;
	CFieldDlg::m_strFieldEndox[utentechiusura_firma6].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_565);
	CFieldDlg::m_strFieldEndox[utentechiusura_firma6].sReport = "UtenteChiusura.Firma6";
	CFieldDlg::m_strFieldEndox[utentechiusura_firma6].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[utentechiusura_firma6].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[utentechiusura_firma7].lID = -1;
	CFieldDlg::m_strFieldEndox[utentechiusura_firma7].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_566);
	CFieldDlg::m_strFieldEndox[utentechiusura_firma7].sReport = "UtenteChiusura.Firma7";
	CFieldDlg::m_strFieldEndox[utentechiusura_firma7].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[utentechiusura_firma7].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[utentechiusura_firma8].lID = -1;
	CFieldDlg::m_strFieldEndox[utentechiusura_firma8].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_567);
	CFieldDlg::m_strFieldEndox[utentechiusura_firma8].sReport = "UtenteChiusura.Firma8";
	CFieldDlg::m_strFieldEndox[utentechiusura_firma8].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[utentechiusura_firma8].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[utentechiusura_firma9].lID = -1;
	CFieldDlg::m_strFieldEndox[utentechiusura_firma9].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_568);
	CFieldDlg::m_strFieldEndox[utentechiusura_firma9].sReport = "UtenteChiusura.Firma9";
	CFieldDlg::m_strFieldEndox[utentechiusura_firma9].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[utentechiusura_firma9].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[utentechiusura_immaginefirma].lID = -1;
	CFieldDlg::m_strFieldEndox[utentechiusura_immaginefirma].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_547);
	CFieldDlg::m_strFieldEndox[utentechiusura_immaginefirma].sReport = "ImmagineFirma.UtenteChiusura";
	CFieldDlg::m_strFieldEndox[utentechiusura_immaginefirma].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[utentechiusura_immaginefirma].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[edt_integrazioneCodiceUrgenza].lID = EDT_INTEGRAZIONECODICEURGENZA;
	CFieldDlg::m_strFieldEndox[edt_integrazioneCodiceUrgenza].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_574);
	CFieldDlg::m_strFieldEndox[edt_integrazioneCodiceUrgenza].sReport = "Ext_Ordini.Urgenza";
	CFieldDlg::m_strFieldEndox[edt_integrazioneCodiceUrgenza].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[edt_integrazioneCodiceUrgenza].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[esame_urgente].lID = CMB_ESAMEURGENTE;
	CFieldDlg::m_strFieldEndox[esame_urgente].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_580);
	CFieldDlg::m_strFieldEndox[esame_urgente].sReport = "Esame.Urgente";
	CFieldDlg::m_strFieldEndox[esame_urgente].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[esame_urgente].bImageNT = FALSE;

	for (int i = 0; i < NUM_LABEL_GRIDCL; i++)
	{
		CString reportField;
		reportField.Format("Esame.GridCL%03d", i);
		CFieldDlg::m_strFieldEndox[esame_gridcl000 + i].lID = SUB_GRIDCL000 + i;
		CFieldDlg::m_strFieldEndox[esame_gridcl000 + i].sReport = reportField;
		CFieldDlg::m_strFieldEndox[esame_gridcl000 + i].bEndox = TRUE;
		CFieldDlg::m_strFieldEndox[esame_gridcl000 + i].bImageNT = FALSE;
	}

	CFieldDlg::m_strFieldEndox[utenteloggato].lID = -1;
	CFieldDlg::m_strFieldEndox[utenteloggato].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_582);
	CFieldDlg::m_strFieldEndox[utenteloggato].sReport = "UtenteLoggato";
	CFieldDlg::m_strFieldEndox[utenteloggato].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[utenteloggato].bImageNT = TRUE;

	CFieldDlg::m_strFieldEndox[fleury_ficha].lID = -1;
	CFieldDlg::m_strFieldEndox[fleury_ficha].sCombo = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_590);
	CFieldDlg::m_strFieldEndox[fleury_ficha].sReport = "Fleury.Ficha";
	CFieldDlg::m_strFieldEndox[fleury_ficha].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[fleury_ficha].bImageNT = FALSE;

	//Luiz - 13/05/2019 - P3 - Atualiza nome/sobrenome Médico - Inclui Médicos solicitantes
	CFieldDlg::m_strFieldEndox[medico_inviante2].lID = EDT_MEDICO2;
	CFieldDlg::m_strFieldEndox[medico_inviante2].sCombo = theApp.GetMessageString(IDS_FIELDDLG_MEDICO2);
	CFieldDlg::m_strFieldEndox[medico_inviante2].sReport = "Eesame.InvMedico2";
	CFieldDlg::m_strFieldEndox[medico_inviante2].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[medico_inviante2].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[medico_inviante3].lID = EDT_MEDICO3;
	CFieldDlg::m_strFieldEndox[medico_inviante3].sCombo = theApp.GetMessageString(IDS_FIELDDLG_MEDICO3);
	CFieldDlg::m_strFieldEndox[medico_inviante3].sReport = "Eesame.InvMedico3";
	CFieldDlg::m_strFieldEndox[medico_inviante3].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[medico_inviante3].bImageNT = FALSE;

	CFieldDlg::m_strFieldEndox[medico_inviante4].lID = EDT_MEDICO4;
	CFieldDlg::m_strFieldEndox[medico_inviante4].sCombo = theApp.GetMessageString(IDS_FIELDDLG_MEDICO4);
	CFieldDlg::m_strFieldEndox[medico_inviante4].sReport = "Eesame.InvMedico4";
	CFieldDlg::m_strFieldEndox[medico_inviante4].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[medico_inviante4].bImageNT = FALSE;

	//Julio - BUG 3285 - Adequação de laudos
	CFieldDlg::m_strFieldEndox[paziente_identificazionepassaporto].lID = EDT_PAZIENTE_PASSAPORTO;
	CFieldDlg::m_strFieldEndox[paziente_identificazionepassaporto].sCombo = theApp.GetMessageString(IDS_FIELDDLG_PAZIENTE_PASSAPORTO);
	CFieldDlg::m_strFieldEndox[paziente_identificazionepassaporto].sReport = "Anagrafico.Passaporto";
	CFieldDlg::m_strFieldEndox[paziente_identificazionepassaporto].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_identificazionepassaporto].bImageNT = FALSE;

	//Julio - BUG 3285 - Adequação de laudos
	CFieldDlg::m_strFieldEndox[paziente_identificazionedoc1].lID = EDT_PAZIENTE_DOC1;
	CFieldDlg::m_strFieldEndox[paziente_identificazionedoc1].sCombo = theApp.GetMessageString(IDS_FIELDDLG_PAZIENTE_DOC1);
	CFieldDlg::m_strFieldEndox[paziente_identificazionedoc1].sReport = "Anagrafico.DOC1";
	CFieldDlg::m_strFieldEndox[paziente_identificazionedoc1].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_identificazionedoc1].bImageNT = FALSE;

	//Julio - BUG 3285 - Adequação de laudos
	CFieldDlg::m_strFieldEndox[paziente_identificazionedoc2].lID = EDT_PAZIENTE_DOC2;
	CFieldDlg::m_strFieldEndox[paziente_identificazionedoc2].sCombo = theApp.GetMessageString(IDS_FIELDDLG_PAZIENTE_DOC2);
	CFieldDlg::m_strFieldEndox[paziente_identificazionedoc2].sReport = "Anagrafico.DOC2";
	CFieldDlg::m_strFieldEndox[paziente_identificazionedoc2].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[paziente_identificazionedoc2].bImageNT = FALSE;

	//Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
	CFieldDlg::m_strFieldEndox[referto_integrato_macro].lID = EDT_REFERTOINTEGRATO_MACRO;
	CFieldDlg::m_strFieldEndox[referto_integrato_macro].sCombo = theApp.GetMessageString(IDS_FIELDDLG_REFERTOINTEGRATO_MACRO);
	CFieldDlg::m_strFieldEndox[referto_integrato_macro].sReport = "RefertoIntegrato.Macro";
	CFieldDlg::m_strFieldEndox[referto_integrato_macro].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[referto_integrato_macro].bImageNT = FALSE;

	//Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
	CFieldDlg::m_strFieldEndox[referto_integrato_diag].lID = EDT_REFERTOINTEGRATO_DIAG;
	CFieldDlg::m_strFieldEndox[referto_integrato_diag].sCombo = theApp.GetMessageString(IDS_FIELDDLG_REFERTOINTEGRATO_DIAG);
	CFieldDlg::m_strFieldEndox[referto_integrato_diag].sReport = "RefertoIntegrato.Diag";
	CFieldDlg::m_strFieldEndox[referto_integrato_diag].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[referto_integrato_diag].bImageNT = FALSE;

	//Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
	CFieldDlg::m_strFieldEndox[referto_integrato_firma].lID = EDT_REFERTOINTEGRATO_FIRMA;
	CFieldDlg::m_strFieldEndox[referto_integrato_firma].sCombo = theApp.GetMessageString(IDS_FIELDDLG_REFERTOINTEGRATO_FIRMA);
	CFieldDlg::m_strFieldEndox[referto_integrato_firma].sReport = "RefertoIntegrato.Firma";
	CFieldDlg::m_strFieldEndox[referto_integrato_firma].bEndox = TRUE;
	CFieldDlg::m_strFieldEndox[referto_integrato_firma].bImageNT = FALSE;

	//Gabriel - TCP
	g_FormCaract[btn_invia_altra_unita].lID = BTN_INVIAALTRAUNITA;
	g_FormCaract[btn_invia_altra_unita].sDescrizione = theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_592);
	g_FormCaract[btn_invia_altra_unita].lMinA = 1;
	g_FormCaract[btn_invia_altra_unita].lMaxA = 26;
	g_FormCaract[btn_invia_altra_unita].lMinL = 2;
	g_FormCaract[btn_invia_altra_unita].lMaxL = 16;
	g_FormCaract[btn_invia_altra_unita].bEndox = TRUE;
	g_FormCaract[btn_invia_altra_unita].bImageNT = FALSE;

}

void RegisterPrivateMessage()
{
	MSG_SELECT_BMP = ::RegisterWindowMessage("SelectBmp");
	MSG_ELABOR_BMP = ::RegisterWindowMessage("ElaborationIsFinished");
	MSG_XPLAY_CLOSE = ::RegisterWindowMessage("MSG_XPLAY_CLOSE");

	MSG_XCAP_MSG_NUOVOMONITORAGGIO = ::RegisterWindowMessage("MSG_XCAP_MSG1");
	MSG_XCAP_MSG_NUOVAPROVETTA = ::RegisterWindowMessage("MSG_XCAP_MSG2");
}

CString AddStringWithoutRepeatition(CString strDestination, CString strSource)
{
	char 	*token = NULL;
	char	*next_token = NULL;
	char 	seps[] = " ";
	int		nPosition = -1;
	CString strToSearch = "";
	CString strFounded = "";
	CString strOrigin = strSource;

	token = strtok_s(strSource.GetBuffer(strSource.GetLength()), seps, &next_token);

	while (token != NULL)
	{
		int nPos;

		if (strToSearch != "")
			strToSearch += " ";

		strToSearch += (LPCSTR)token;

		token = strtok_s(NULL, seps, &next_token);

		nPos = strDestination.Find(strToSearch);

		if (nPos >= 0)
		{
			nPosition = nPos;
			strFounded = strToSearch;
		}
	}

	if (strFounded != "")
	{
		CString		strToAdd;
		CString		strSourceAfterFound;
		CString		strDestinAfterFound;
		CString		strDestinBeforeFound;
		int			nLenSource = strOrigin.GetLength();
		int			nLenDestination = strDestination.GetLength();
		int			nLenFounded = strFounded.GetLength();
		int			nPosReturn;

		strSourceAfterFound = strOrigin.Right(nLenSource - nLenFounded);
		strDestinAfterFound = strDestination.Right(nLenDestination - (nPosition + nLenFounded));

		strDestinBeforeFound = strDestination.Left(nPosition + nLenFounded);

		nPosReturn = strDestinAfterFound.Find("\r\n");

		if (nPosReturn >= 0)
		{
			int		nLenAfterDest = strDestinAfterFound.GetLength();
			CString strAfter = strDestinAfterFound.Right(nLenAfterDest - nPosReturn);
			CString strBefore = strDestinAfterFound.Left(nPosReturn);

			strToAdd = strBefore + "," + strSourceAfterFound + strAfter;
		}
		else
		{
			strToAdd = strDestinAfterFound + "," + strSourceAfterFound;
		}

		strDestination = strDestinBeforeFound + strToAdd;
	}
	else
	{
		if (strDestination != "")
			strDestination += "\r\n";

		strDestination += strOrigin;
	}

	return strDestination;
}

void DDX_BreathTestHP(CDataExchange* pDX, int nIDC, float& fValue, CRecordset* pRecordSet)
{
	CMaskEdit* pCtrlEdit = (CMaskEdit*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	if (pDX->m_bSaveAndValidate)
	{
		// prendo la stringa dall'edit //
		CString strEdit;
		pCtrlEdit->GetWindowText(strEdit);

		if (strEdit.CompareNoCase(pCtrlEdit->GetDefault()) != 0)
		{
			// la converto e la metto nel campo del recordset //
			fValue = (float)atof(strEdit);

			// se il recordset è aperto gli dico che il campo non è più nullo //
			if (pRecordSet->IsOpen())
				pRecordSet->SetFieldNull(&fValue, FALSE);
		}
		else
		{
			// la converto e la metto nel campo del recordset //
			fValue = -100.0f;

			// se il recordset è aperto gli dico che il campo non è più nullo //
			if (pRecordSet->IsOpen())
				pRecordSet->SetFieldNull(&fValue, FALSE);
		}
	}
	else
	{
		// scrive il numero nel CMaskEdit //

		if (fValue < 0.0f)
		{
			if (pCtrlEdit->GetStyle() & ES_READONLY)
				pCtrlEdit->SetWindowText("");
			else
				pCtrlEdit->SetWindowText(pCtrlEdit->GetDefault());
		}
		else
		{
			CString strTmp;
			strTmp.Format("%.1f", fValue);
			pCtrlEdit->SetWindowText(strTmp);
		}
	}
}

void DDX_Date(CDataExchange* pDX, int nIDC, long& value, int nType)
{
	HWND 	hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	CEdit*	pCtrlEdit = (CEdit*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	if (pDX->m_bSaveAndValidate)
	{
		CString		strcDate;
		CCustomDate userDate;

		pCtrlEdit->GetWindowText(strcDate);
		value = userDate.SetDate((LPCSTR)strcDate);
		return;
	}
	else	// Carica nel CEdit la data
	{
		if (value)
		{
			CString	strcDate;
			CCustomDate userDate(value);

			if (nType == 0)
				strcDate = userDate.GetDate("%d/%m/%Y");
			else
				strcDate = userDate.GetDate("%d/%m/%y");

			pCtrlEdit->SetWindowText((LPCSTR)strcDate);
			return;
		}
	}

	pCtrlEdit->SetWindowText("");
}

void DDX_DateMask(CDataExchange* pDX, int nIDC, long& value, CRecordset* pRecordSet)
{
	CMaskEdit* pCtrlEdit = (CMaskEdit*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	if (pDX->m_bSaveAndValidate)
	{
		// prendo la stringa dall'edit //
		CString strDate;
		pCtrlEdit->GetWindowText(strDate);

		// la converto e la metto nel campo del recordset //
		value = CCustomDate().SetDate(strDate);

		// se il recordset è aperto gli dico che il campo non è più null //
		if (pRecordSet->IsOpen())
			pRecordSet->SetFieldNull(&value, FALSE);
	}
	else
	{
		// scrive la data nel CMaskEdit //

		if ((value > 0) && (value < 1246576928))
		{
			pCtrlEdit->SetWindowText(CCustomDate(value).GetDate("%d/%m/%Y"));
		}
		else
		{
			if (pCtrlEdit->GetStyle() & ES_READONLY)
				pCtrlEdit->SetWindowText("");
			else
				pCtrlEdit->SetWindowText(pCtrlEdit->GetDefault());
		}
	}
}

void DDX_DateMask(CDataExchange* pDX, int nIDC, CString& value, CRecordset* pRecordSet)
{
	CMaskEdit* pCtrlEdit = (CMaskEdit*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	if (pDX->m_bSaveAndValidate)
	{
		// prendo la stringa dall'edit //
		CString strDate;
		pCtrlEdit->GetWindowText(strDate);

		// la converto e la metto nel campo del recordset //
		if (strDate.GetLength() >= 8 && strDate != pCtrlEdit->GetDefault())
			value = strDate.Right(4) + strDate.Mid(3, 2) + strDate.Left(2);
		else
			value = "";

		// se il recordset è aperto gli dico che il campo non è più null //
		if (pRecordSet->IsOpen())
			pRecordSet->SetFieldNull(&value, FALSE);
	}
	else
	{
		// scrive la data nel CMaskEdit //

		if (value.GetLength() >= 8)
		{
			pCtrlEdit->SetWindowText(value.Right(2) + "/" + value.Mid(2, 2) + "/" + value.Left(4));
		}
		else
		{
			if (pCtrlEdit->GetStyle() & ES_READONLY)
				pCtrlEdit->SetWindowText("");
			else
				pCtrlEdit->SetWindowText(pCtrlEdit->GetDefault());
		}
	}
}

void DDX_DateTimeMask(CDataExchange* pDX, int nIDC, long& value, CRecordset* pRecordSet)
{
	CMaskEdit* pCtrlEdit = (CMaskEdit*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	if (pDX->m_bSaveAndValidate)
	{
		// prendo la stringa dall'edit //
		CString strDate;
		pCtrlEdit->GetWindowText(strDate);

		// la converto e la metto nel campo del recordset //
		value = ConvertMaskString2Date(strDate);

		// se il recordset è aperto gli dico che il campo non è più null //
		if (pRecordSet->IsOpen())
			pRecordSet->SetFieldNull(&value, FALSE);
	}
	else
	{
		// scrive la data nel CMaskEdit //

		if ((value > 0) && (value < 1246576928))
		{
			pCtrlEdit->SetWindowText(CCustomDate(value).GetDate("%d/%m/%Y - %H:%M"));
		}
		else
		{
			if (pCtrlEdit->GetStyle() & ES_READONLY)
				pCtrlEdit->SetWindowText("");
			else
				pCtrlEdit->SetWindowText(pCtrlEdit->GetDefault());
		}
	}
}

void DDX_DateTimePersMask(CDataExchange* pDX, int nIDC, int nModalita, long& value, CRecordset* pRecordSet)
{
	CMaskEdit* pCtrlEdit = (CMaskEdit*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	if (pDX->m_bSaveAndValidate)
	{
		// prendo la stringa dall'edit //
		CString strDateTime;
		pCtrlEdit->GetWindowText(strDateTime);

		// la converto e la metto nel campo del recordset //
		switch (nModalita)
		{
		case DATA_ORA:
		{
			value = ConvertMaskString2Date(strDateTime);
			break;
		}
		case SOLO_DATA:
		{
			value = CCustomDate().SetDate(strDateTime);
			break;
		}
		case SOLO_ORA:
		{
			value = CCustomDate().SetTime(strDateTime);
			break;
		}
		}

		// se il recordset è aperto gli dico che il campo non è più null //
		if (pRecordSet->IsOpen())
			pRecordSet->SetFieldNull(&value, FALSE);
	}
	else
	{
		// scrive data/ora nel CMaskEdit //

		if ((value > 0) && (value < 1246576928))
		{
			switch (nModalita)
			{
			case DATA_ORA:
			{
				pCtrlEdit->SetWindowText(CCustomDate(value).GetDate("%d/%m/%Y - %H:%M"));
				break;
			}
			case SOLO_DATA:
			{
				pCtrlEdit->SetWindowText(CCustomDate(value).GetDate("%d/%m/%Y"));
				break;
			}
			case SOLO_ORA:
			{
				pCtrlEdit->SetWindowText(CCustomDate(value).GetDate("%H:%M"));
				break;
			}
			}
		}
		else
		{
			if (pCtrlEdit->GetStyle() & ES_READONLY)
				pCtrlEdit->SetWindowText("");
			else
				pCtrlEdit->SetWindowText(pCtrlEdit->GetDefault());
		}
	}
}

void DDX_YearEx(CDataExchange* pDX, int nIDC, long& value)
{
	HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	CMaskEdit* pCtrlEdit = (CMaskEdit*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	if (pDX->m_bSaveAndValidate)
	{
		CString strDate;
		pCtrlEdit->GetWindowText(strDate);
		strDate.Trim();

		value = 0;

		if (strDate.GetLength() == 4)
		{
			strDate = "01/01/" + strDate;
			value = CCustomDate().SetDate(strDate);
		}

		return;
	}
	else // Carica nel CMaskEdit la data
	{
		if ((value > 0) && (value < 1246576928))
		{
			CCustomDate customDate(value);
			pCtrlEdit->SetWindowText(customDate.GetDate("%Y"));

			return;
		}
	}

	if (pCtrlEdit->GetStyle() & ES_READONLY)
		pCtrlEdit->SetWindowText("");
	else
		pCtrlEdit->SetWindowText(pCtrlEdit->GetDefault());
}

long ConvertMaskString2Date(CString strDateTime)
{
	CCustomDate customDate;
	long value;

	CString strSep[8] = { "-", "_", ";", "  ", ". ", ", ", " .", " ," };
	CString str[2];
	BOOL	bFound = FALSE;
	int		i = 0;
	int		nLenStr;
	int		nLenSep;
	int		nIndex;

	while (!bFound && i < 8)
	{
		nLenStr = strDateTime.GetLength();
		nLenSep = strSep[i].GetLength();
		nIndex = strDateTime.Find(strSep[i]);

		i++;

		if (nIndex > 0)
		{
			str[0] = strDateTime.Left(nIndex);
			str[1] = strDateTime.Right(nLenStr - nIndex - nLenSep);

			bFound = TRUE;
		}
	}

	if (bFound)
	{
		for (i = 0; i<2; i++)
		{
			str[i].TrimLeft();
			str[i].TrimRight();
		}

		if (str[0].GetLength() > str[1].GetLength())
		{
			value = customDate.SetDate(str[0]);
			value |= customDate.SetTime(str[1]);
		}
		else
		{
			value = customDate.SetDate(str[1]);
			value |= customDate.SetTime(str[0]);
		}
	}
	else
	{
		value = customDate.SetDate(strDateTime);

		// Sandro 30/05/2011 // possibilità di salvare la sola ora, senza una data //
		if (value == 0)
			value = customDate.SetTime(strDateTime);
	}

	return value;
}

//-----------------------------------------------------------------------
// Davide - DataExchange con controllo di tipo DatePicker
void DDX_DatePicker(CDataExchange* pDX, int nIDC, long& value, int nType)
{
	HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	CDateTimeCtrl*	pCtrlDate = (CDateTimeCtrl*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	if (pDX->m_bSaveAndValidate)
	{
		CString		strcDate;
		CCustomDate userDate;
		COleDateTime time;

		pCtrlDate->GetTime(time);
		strcDate.Format("%02d/%02d/%04d",
			time.GetDay(),
			time.GetMonth(),
			time.GetYear());
		value = userDate.SetDate((LPCSTR)strcDate);
		return;
	}
	else
	{
		if (value)
		{
			CString	strcDate;
			CCustomDate userDate(value);
			COleDateTime time;

			if (nType == 0)
				strcDate = userDate.GetDate("%d/%m/%Y");
			else
				strcDate = userDate.GetDate("%d/%m/%y");

			time.SetDateTime(atoi(strcDate.Mid(6, 4)),
				atoi(strcDate.Mid(3, 2)),
				atoi(strcDate.Mid(0, 2)),
				0, 0, 0);
			pCtrlDate->SetTime(time);
			return;
		}
	}
}

void DDX_Combo(CDataExchange* pDX, int nIDC, long& value, long lComboDefine)
{
	BOOL		bSetNull = TRUE;
	HWND		hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	CEdit*		pCtrlEdit = (CEdit*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	if (pDX->m_bSaveAndValidate)	// mette nel campo la data
	{
		CString 		strFromEditCtrl;
		CCustomDate 	userDate;

		pCtrlEdit->GetWindowText(strFromEditCtrl);

		if (strFromEditCtrl.IsEmpty())
		{
			value = 0L;
		}
		else
		{
			CString sFilter;
			sFilter.Format("Testo like '%s'", strFromEditCtrl);

			CComboBoxSet setComboBox(lComboDefine);
			setComboBox.SetOpenFilter(sFilter);
			setComboBox.SetSortRecord("Testo");
			if (setComboBox.OpenRecordset("DDX_Combo"))
			{
				if (!setComboBox.IsEOF())
				{
					value = setComboBox.m_lContatore;
					bSetNull = FALSE;
				}

				setComboBox.CloseRecordset("DDX_Combo");
			}
		}
	}
	else	// Carica nel CEdit la data
	{
		if (value)
		{
			CString	sFilter;
			sFilter.Format("Contatore=%li", value);

			CComboBoxSet setComboBox(lComboDefine);
			setComboBox.SetOpenFilter(sFilter);
			if (setComboBox.OpenRecordset("DDX_Combo"))
			{
				if (!setComboBox.IsEOF())
				{
					pCtrlEdit->SetWindowText(setComboBox.m_sTesto);
					bSetNull = FALSE;
				}

				setComboBox.CloseRecordset("DDX_Combo");
			}
		}
	}

	if (bSetNull)
		pCtrlEdit->SetWindowText("");
}

void DDX_Organo(CDataExchange* pDX, int nIDC, long& lOrgano)
{
	BOOL bSetNull = TRUE;
	HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	CEdit* pCtrlEdit = (CEdit*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	if (pDX->m_bSaveAndValidate)
	{
		CString strFromEditCtrl;

		pCtrlEdit->GetWindowText(strFromEditCtrl);

		if (strFromEditCtrl.IsEmpty() == TRUE)
		{
			lOrgano = 0;
		}
		else
		{
			BOOL bError = FALSE;

			CString sFilter;
			sFilter.Format("Organo like '%s'", strFromEditCtrl);

			CMstOrganoSet setMstOrgano;
			setMstOrgano.SetOpenFilter(sFilter);
			if (setMstOrgano.OpenRecordset("DDX_Organo") == TRUE)
			{
				if (!setMstOrgano.IsEOF())
				{
					lOrgano = setMstOrgano.m_lContatore;
					bSetNull = FALSE;
				}
				else
				{
					CString strMsgBox;
					strMsgBox.Format(theApp.GetMessageString(IDS_COMMON_NOT_FOUND), strFromEditCtrl);
					theApp.AfxMessageBoxEndo(strMsgBox);
				}

				setMstOrgano.CloseRecordset("DDX_Organo");
			}
		}
	}
	else
	{
		if (lOrgano)
		{
			CString	sFilter;
			sFilter.Format("Contatore=%li", lOrgano);

			CMstOrganoSet setMstOrgano;
			setMstOrgano.SetOpenFilter(sFilter);
			if (setMstOrgano.OpenRecordset("DDX_Organo"))
			{
				if (!setMstOrgano.IsEOF())
				{
					pCtrlEdit->SetWindowText(setMstOrgano.m_sOrgano);
					bSetNull = FALSE;
				}

				setMstOrgano.CloseRecordset("DDX_Organo");
			}
		}
	}

	if (bSetNull)
		pCtrlEdit->SetWindowText("");
}

void DDX_Regione(CDataExchange* pDX, int nIDC, long& value)
{
	HWND		hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	CComboBox*	pCtrlCB = (CComboBox*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	if (pDX->m_bSaveAndValidate)	// mette nell'esame il codice
	{
		int	CurSel = pCtrlCB->GetCurSel();

		if (CurSel == CB_ERR)
		{	// no item selected
			value = 0L;
			return;
		}

		long codice = pCtrlCB->GetItemData(CurSel);

		if ((DWORD)codice == CB_ERR)
		{
			return;
		}

		value = codice;
	}
	else	// Carica nel Combo il dati
	{
		int ItemsCount = pCtrlCB->GetCount();

		if (ItemsCount == CB_ERR)
		{
			return;
		}

		if (ItemsCount /* > 0 */)
		{	// il Combo non é vuoto quindi verifichiamo se
			// il codice cercato è già inserito
			long codice;

			do // do-while cycle
			{
				codice = pCtrlCB->GetItemData(--ItemsCount);

				if ((DWORD)codice == CB_ERR)
				{
					return;
				}
			} while ((codice != value) && ItemsCount);

			if (codice == value)	// il nuovo codice si trova nel combo => esco
				return;
			// else	//il codice non si trova nel combo
		}

		// è fondamentale che la lista venga concellata
		pCtrlCB->ResetContent();

		//

		CString sFilter;
		sFilter.Format("Contatore=%li", value);

		CCodificaRegionaleExSet setTemp;
		setTemp.SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
		setTemp.SetOpenFilter(sFilter);
		setTemp.SetSortRecord("Descrizione");
		if (setTemp.OpenRecordset("DDX_Regione"))
		{
			if (setTemp.IsEOF())
			{
				value = 0L;
				setTemp.CloseRecordset("DDX_Regione");
				return;
			}

			int posiz = pCtrlCB->AddString(setTemp.m_sDescrizione);

			if (posiz == CB_ERR || posiz == CB_ERRSPACE)
			{
				setTemp.CloseRecordset("DDX_Regione");
				return;
			}

			value = setTemp.m_lContatore;

			if (pCtrlCB->SetItemData(posiz, (DWORD)setTemp.m_lContatore) == CB_ERR)
			{
				setTemp.CloseRecordset("DDX_Regione");
				return;
			}

			if (pCtrlCB->SetCurSel(posiz) == CB_ERR)
			{
				setTemp.CloseRecordset("DDX_Regione");
				return;
			}

			setTemp.CloseRecordset("DDX_Regione");
		}
	}
}

void DDX_ProcedureICD9(CDataExchange* pDX, int nIDC, long& value, int provenienza)
{
	HWND		hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	CComboBox*	pCtrlCB = (CComboBox*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	if (pDX->m_bSaveAndValidate)	// mette nell'esame il codice
	{
		int	CurSel = pCtrlCB->GetCurSel();

		if (CurSel == CB_ERR)
		{	// no item selected
			value = 0L;
			return;
		}

		long codice = pCtrlCB->GetItemData(CurSel);

		if ((DWORD)codice == CB_ERR)
		{
			return;
		}

		value = codice;
	}
	else	// Carica nel Combo il dati
	{
		int ItemsCount = pCtrlCB->GetCount();

		if (ItemsCount == CB_ERR)
		{
			return;
		}

		if (ItemsCount /* > 0 */)
		{	// il Combo non é vuoto quindi verifichiamo se
			// il codice cercato è già inserito
			long codice;

			do // do-while cycle
			{
				codice = pCtrlCB->GetItemData(--ItemsCount);

				if ((DWORD)codice == CB_ERR)
				{
					return;
				}
			} while ((codice != value) && ItemsCount);

			if (codice == value)	// il nuovo codice si trova nel combo => esco
				return;
			// else	//il codice non si trova nel combo
		}

		// è fondamentale che la lista venga concellata
		pCtrlCB->ResetContent();

		CString sFilter;
		sFilter.Format("ID=%li", value);

		CProcedureICD9Set setProc;

		setProc.SetOpenFilter(sFilter);
		setProc.SetSortRecord("Descrizione");
		if (setProc.OpenRecordset("DDX_ProcedureICD9"))
		{
			if (setProc.IsEOF())
			{
				value = 0L;
				setProc.CloseRecordset("DDX_ProcedureICD9");
				return;
			}

			int posiz = 0;

			if (provenienza == ESTERNO)
				posiz = pCtrlCB->AddString(setProc.m_sDescrizione + " - " + setProc.m_sCodificaICD9Esterni + " - " + setProc.m_sCodificaInterna);
			else
				posiz = pCtrlCB->AddString(setProc.m_sDescrizione + " - " + setProc.m_sCodificaICD9Interni + " - " + setProc.m_sCodificaInterna);

			if (posiz == CB_ERR || posiz == CB_ERRSPACE)
			{
				setProc.CloseRecordset("DDX_ProcedureICD9");
				return;
			}

			value = setProc.m_lID;

			if (pCtrlCB->SetItemData(posiz, (DWORD)setProc.m_lID) == CB_ERR)
			{
				setProc.CloseRecordset("DDX_ProcedureICD9");
				return;
			}

			if (pCtrlCB->SetCurSel(posiz) == CB_ERR)
			{
				setProc.CloseRecordset("DDX_ProcedureICD9");
				return;
			}

			setProc.CloseRecordset("DDX_ProcedureICD9");
		}
	}
}

void DDX_DiagnosiICD9(CDataExchange* pDX, int nIDC, long& value, int provenienza)
{
	HWND		hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	CComboBox*	pCtrlCB = (CComboBox*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	if (pDX->m_bSaveAndValidate)	// mette nell'esame il codice
	{
		int	CurSel = pCtrlCB->GetCurSel();

		if (CurSel == CB_ERR)
		{	// no item selected
			value = 0L;
			return;
		}

		long codice = pCtrlCB->GetItemData(CurSel);

		if ((DWORD)codice == CB_ERR)
		{
			return;
		}

		value = codice;
	}
	else	// Carica nel Combo il dati
	{
		int ItemsCount = pCtrlCB->GetCount();

		if (ItemsCount == CB_ERR)
		{
			return;
		}

		if (ItemsCount /* > 0 */)
		{	// il Combo non é vuoto quindi verifichiamo se
			// il codice cercato è già inserito
			long codice;

			do // do-while cycle
			{
				codice = pCtrlCB->GetItemData(--ItemsCount);

				if ((DWORD)codice == CB_ERR)
				{
					return;
				}
			} while ((codice != value) && ItemsCount);

			if (codice == value)	// il nuovo codice si trova nel combo => esco
				return;
			// else	//il codice non si trova nel combo
		}

		// è fondamentale che la lista venga concellata
		pCtrlCB->ResetContent();

		CString sFilter;
		sFilter.Format("ID=%li", value);

		CDiagnosiICD9Set setDiag;

		setDiag.SetOpenFilter(sFilter);
		setDiag.SetSortRecord("Descrizione");
		if (setDiag.OpenRecordset("DDX_DiagnosiICD9"))
		{
			if (setDiag.IsEOF())
			{
				value = 0L;
				setDiag.CloseRecordset("DDX_DiagnosiICD9");
				return;
			}

			int posiz = 0;

			if (provenienza == ESTERNO)
				posiz = pCtrlCB->AddString(setDiag.m_sDescrizione + " - " + setDiag.m_sCodificaICD9Esterni + " - " + setDiag.m_sCodificaInterna);
			else
				posiz = pCtrlCB->AddString(setDiag.m_sDescrizione + " - " + setDiag.m_sCodificaICD9Interni + " - " + setDiag.m_sCodificaInterna);

			if (posiz == CB_ERR || posiz == CB_ERRSPACE)
			{
				setDiag.CloseRecordset("DDX_DiagnosiICD9");
				return;
			}

			value = setDiag.m_lID;

			if (pCtrlCB->SetItemData(posiz, (DWORD)setDiag.m_lID) == CB_ERR)
			{
				setDiag.CloseRecordset("DDX_DiagnosiICD9");
				return;
			}

			if (pCtrlCB->SetCurSel(posiz) == CB_ERR)
			{
				setDiag.CloseRecordset("DDX_DiagnosiICD9");
				return;
			}

			setDiag.CloseRecordset("DDX_DiagnosiICD9");
		}
	}
}

void DDX_Accessori(CDataExchange* pDX, int nIDC, long& value)
{
	HWND		hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	CComboBox*	pCtrlCB = (CComboBox*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	if (pDX->m_bSaveAndValidate)	// mette nell'esame il codice
	{
		int	CurSel = pCtrlCB->GetCurSel();

		if (CurSel == CB_ERR)
		{	// no item selected
			value = 0L;
			return;
		}

		long codice = pCtrlCB->GetItemData(CurSel);

		if ((DWORD)codice == CB_ERR)
		{
			return;
		}

		value = codice;
	}
	else	// Carica nel Combo il dati
	{
		int ItemsCount = pCtrlCB->GetCount();

		if (ItemsCount == CB_ERR)
		{
			return;
		}

		if (ItemsCount /* > 0 */)
		{	// il Combo non é vuoto quindi verifichiamo se
			// il codice cercato è già inserito
			long codice;

			do // do-while cycle
			{
				codice = pCtrlCB->GetItemData(--ItemsCount);

				if ((DWORD)codice == CB_ERR)
				{
					return;
				}
			} while ((codice != value) && ItemsCount);

			if (codice == value)	// il nuovo codice si trova nel combo => esco
				return;
			// else	//il codice non si trova nel combo
		}

		// è fondamentale che la lista venga concellata
		pCtrlCB->ResetContent();

		CString sFilter;
		sFilter.Format("Contatore=%li", value);

		CComboBoxSet setComboBox(CMB_ESA_ACCESS);
		setComboBox.SetOpenFilter(sFilter);
		setComboBox.SetSortRecord("Testo");
		if (setComboBox.OpenRecordset("DDX_Accessori"))
		{
			if (setComboBox.IsEOF())
			{
				value = 0L;
				setComboBox.CloseRecordset("DDX_Accessori");
				return;
			}

			int posiz = pCtrlCB->AddString(setComboBox.m_sTesto);

			if (posiz == CB_ERR || posiz == CB_ERRSPACE)
			{
				setComboBox.CloseRecordset("DDX_Accessori");
				return;
			}

			value = setComboBox.m_lContatore;

			if (pCtrlCB->SetItemData(posiz, (DWORD)setComboBox.m_lContatore) == CB_ERR)
			{
				setComboBox.CloseRecordset("DDX_Accessori");
				return;
			}

			if (pCtrlCB->SetCurSel(posiz) == CB_ERR)
			{
				setComboBox.CloseRecordset("DDX_Accessori");
				return;
			}

			setComboBox.CloseRecordset("DDX_Accessori");
		}
	}
}

void DDX_Studi(CDataExchange* pDX, int nIDC, long& lValue, CRecordset* pRecordSet)
{
	HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	CComboBox* pCtrlCB = (CComboBox*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	if (pDX->m_bSaveAndValidate)
	{
		int nCurSel = pCtrlCB->GetCurSel();
		if (nCurSel > 0)
			lValue = pCtrlCB->GetItemData(nCurSel);
		else
			lValue = 0;
	}
	else
	{
		if (!pRecordSet->IsFieldNull(&lValue) && (lValue > 0))
		{
			for (int i = 1; i < pCtrlCB->GetCount(); i++)
			{
				if (pCtrlCB->GetItemData(i) == lValue)
				{
					pCtrlCB->SetCurSel(i);
					break;
				}
			}
		}
		else
		{
			pCtrlCB->SetCurSel(0);
		}
	}
}

void DDX_FieldCombo(CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet, long lComboDefine)
{
	BOOL bSetNull = TRUE;
	HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	CEdit* pCtrlEdit = (CEdit*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	if (pRecordSet->IsOpen())
	{
		if (pDX->m_bSaveAndValidate)	// mette nel campo il valore
		{
			CString 		strFromEditCtrl;
			CCustomDate 	userDate;

			pCtrlEdit->GetWindowText(strFromEditCtrl);

			if (strFromEditCtrl.IsEmpty())
			{
				value = -1;
			}
			else
			{
				CString	sFilter;
				sFilter.Format("Testo like '%s'", strFromEditCtrl);

				CComboBoxSet setComboBox(lComboDefine);
				setComboBox.SetOpenFilter(sFilter);
				setComboBox.SetSortRecord("Testo");
				if (setComboBox.OpenRecordset("DDX_FieldCombo"))
				{
					if (!setComboBox.IsEOF())
					{
						value = setComboBox.m_lContatore;
						pRecordSet->SetFieldNull(&value, FALSE);
						bSetNull = FALSE;
					}

					setComboBox.CloseRecordset("DDX_FieldCombo");
				}
			}
		}
		else	// Carica nel CEdit la data
		{
			if ((!pRecordSet->IsFieldNull(&value)) && (value >= 0))
			{
				CString	sFilter;
				sFilter.Format("Contatore=%li", value);

				CComboBoxSet setComboBox(lComboDefine);
				setComboBox.SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
				setComboBox.SetOpenFilter(sFilter);
				if (setComboBox.OpenRecordset("DDX_FieldCombo"))
				{
					if (!setComboBox.IsEOF())
					{
						pCtrlEdit->SetWindowText(setComboBox.m_sTesto);
						bSetNull = FALSE;
					}

					setComboBox.CloseRecordset("DDX_FieldCombo");
				}
			}
		}
	}

	if (bSetNull)
		pCtrlEdit->SetWindowText("");
}

void DDX_FieldDate(CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet)
{
	HWND		hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	CEdit*		pCtrlEdit = (CEdit*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	if (pRecordSet->IsOpen())
	{
		if (pDX->m_bSaveAndValidate)	// mette nel campo la data
		{
			CString 		strFromEditCtrl;
			CCustomDate 	userDate;

			pCtrlEdit->GetWindowText(strFromEditCtrl);

			if (strFromEditCtrl.IsEmpty())
			{
				value = 0L;
			}
			else
			{
				value = userDate.SetDate((LPCSTR)strFromEditCtrl);

				pRecordSet->SetFieldNull(&value, FALSE);

				return;
			}
		}
		else	// Carica nel CEdit la data
		{
			if (!pRecordSet->IsFieldNull(&value) && value) // && !pRecordSet->IsEOF())
			{
				CCustomDate userDate(value);

				CString strFromMedia = userDate.GetDate("%d/%m/%Y");
				pCtrlEdit->SetWindowText((LPCSTR)strFromMedia);
				return;
			}
		}
	}

	pCtrlEdit->SetWindowText("");
}

// Sandro 05/11/2013 //
void DDX_FieldDateEta(CDataExchange* pDX, int nIDC, long& value, CPazientiSet* pRecordSet)
{
	HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	CEdit* pCtrlEdit = (CEdit*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	if (pRecordSet->IsOpen())
	{
		if (pDX->m_bSaveAndValidate)
		{
			// mette nel campo la data //

			CString sFromEditCtrl;
			CCustomDate cdUserDate;

			pCtrlEdit->GetWindowText(sFromEditCtrl);

			if (sFromEditCtrl.IsEmpty())
			{
				value = 0;
			}
			else
			{
				int nIndex = sFromEditCtrl.Find("(");
				if (nIndex > 0)
				{
					sFromEditCtrl = sFromEditCtrl.Left(nIndex);
					sFromEditCtrl.Trim();
				}

				value = cdUserDate.SetDate(sFromEditCtrl);
				pRecordSet->SetFieldNull(&value, FALSE);

				return;
			}
		}
		else
		{
			// carica nel CEdit la data ed eventualmente l'età //

			if (!pRecordSet->IsFieldNull(&value) && (value > 0))
			{
				CCustomDate cdUserDate(value);

				CString sFromMedia = cdUserDate.GetDate("%d/%m/%Y");

				switch (theApp.m_lMostraEtaPaziente)
				{
				case 1:
				{
					CCustomDate cdOggi(TRUE, TRUE);

					CString sTemp;
					if (theApp.m_bAtivaListaDO)
						sTemp = GetStringEta(value, cdOggi.GetDate(), FormatoEta::SoloAnno);//
					else 
						sTemp = GetStringEta(value, cdOggi.GetDate(), TRUE);

					if (!sTemp.IsEmpty())
						sFromMedia += " (" + sTemp + ")";

					break;
				}
				case 2:
				{
					CCustomDate cdOggi(TRUE, TRUE);
					CString sTemp;
					if (theApp.m_bAtivaListaDO)
						sTemp = GetStringEta(value, cdOggi.GetDate(), FormatoEta::AnnoMeseGiornoAbbreviato);
					else 
						sTemp = GetStringEta(value, cdOggi.GetDate(), FALSE);

					if (!sTemp.IsEmpty())
						sFromMedia += " (" + sTemp + ")";

					break;
				}
				}

				pCtrlEdit->SetWindowText(sFromMedia);
				return;
			}
		}
	}

	pCtrlEdit->SetWindowText("");
}

void DDX_FieldTipoEsameCombo(CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet)
{
	HWND		hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	CComboBox*	pCtrlCB = (CComboBox*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	if (pRecordSet->IsOpen())
	{
		if (pDX->m_bSaveAndValidate)	// mette nell'esame il codice dell'esame
		{
			int	CurSel = pCtrlCB->GetCurSel();

			if (CurSel == CB_ERR)
			{	// no item selected
				value = 0L;
				//pDX->Fail();
				return;
			}

			long codice = pCtrlCB->GetItemData(CurSel);

			if ((DWORD)codice == CB_ERR)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_1));
				return;
			}

			value = codice;
			pRecordSet->SetFieldNull(&value, FALSE);
		}
		else	// Carica nel Combo il tipo dell'esame
		{
			if (!pRecordSet->IsFieldNull(&value))
			{
				int ItemsCount = pCtrlCB->GetCount();

				if (ItemsCount == CB_ERR)
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_2));
					return;
				}

				if (ItemsCount /* > 0 */)
				{	// il Combo non é vuoto quindi verifichiamo se
					// il tipo esame cercato è già inserito
					long codice;

					do // do-while cycle
					{
						codice = pCtrlCB->GetItemData(--ItemsCount);

						if ((DWORD)codice == CB_ERR)
						{
							theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_3));
							return;
						}
					} while ((codice != value) && ItemsCount);

					if (codice == value)	// il nuovo tipo esame si trova nel combo => esco
						return;
					// else	//il codice del tipo esame non si trova nel combo
				}

				// è fondamentale che la lista venga cancellata
				pCtrlCB->ResetContent();

				CString sFilter;
				sFilter.Format("Contatore=%li", value);

				CTipoEsameSet setTipoEsame;
				setTipoEsame.SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
				setTipoEsame.SetOpenFilter(sFilter);
				if (setTipoEsame.OpenRecordset("DDX_FieldTipoEsame"))
				{
					if (setTipoEsame.IsEOF())
					{
						value = 0L;
						setTipoEsame.CloseRecordset("DDX_FieldTipoEsame");
						return;
					}

					int posiz = pCtrlCB->AddString(setTipoEsame.m_sDescrizione);

					if (posiz == CB_ERR || posiz == CB_ERRSPACE)
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_4));
						setTipoEsame.CloseRecordset("DDX_FieldTipoEsame");
						return;
					}

					value = setTipoEsame.m_lContatore;

					if (pCtrlCB->SetItemData(posiz, (DWORD)setTipoEsame.m_lContatore) == CB_ERR)
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_5));
						setTipoEsame.CloseRecordset("DDX_FieldTipoEsame");
						return;
					}

					if (pCtrlCB->SetCurSel(posiz) == CB_ERR)
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_6));
						setTipoEsame.CloseRecordset("DDX_FieldTipoEsame");
						return;
					}

					setTipoEsame.CloseRecordset("DDX_FieldTipoEsame");
				}
			}
			else
			{
				pCtrlCB->ResetContent();
				value = 0L;
			}
		}
	}
	else
	{	// qualche errore é avvenuto dunque é bene pulire il combo
		pCtrlCB->ResetContent();
	}
}

void DDX_FieldTipoEsameEdit(CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet)
{
	CEdit* pControl = (CEdit*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	pControl->SetWindowText("");
	if (pRecordSet->IsOpen() == TRUE)
	{
		if (pDX->m_bSaveAndValidate == TRUE)
		{
			// BOH, forse non serve mai //
		}
		else
		{
			CString sFilter;
			sFilter.Format("Contatore=%li", value);

			CTipoEsameSet setTipoEsame;

			setTipoEsame.SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
			setTipoEsame.SetOpenFilter(sFilter);
			if (setTipoEsame.OpenRecordset("DDX_FieldTipoEsameEdit"))
			{
				if (!setTipoEsame.IsEOF())
					pControl->SetWindowText(setTipoEsame.m_sDescrizione);

				setTipoEsame.CloseRecordset("DDX_FieldTipoEsameEdit");
			}
		}
	}
}

void DDX_FieldOperatoriCombo(CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet)
{
	HWND		hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	CComboBox*	pCtrlCB = (CComboBox*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	if (pRecordSet->IsOpen())
	{
		if (pDX->m_bSaveAndValidate)	// mette nell'esame il codice del medico
		{
			int	CurSel = pCtrlCB->GetCurSel();

			if (CurSel == CB_ERR)
			{	// no item selected
				value = 0L;
				//pDX->Fail();
				return;
			}

			long codice = pCtrlCB->GetItemData(CurSel);

			if ((DWORD)codice == CB_ERR)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_7));
				return;
			}

			value = codice;
			pRecordSet->SetFieldNull(&value, FALSE);
		}
		else	// Carica nel Combo il medico dell'esame
		{
			if (!pRecordSet->IsFieldNull(&value))
			{
				int ItemsCount = pCtrlCB->GetCount();

				if (ItemsCount == CB_ERR)
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_8));
					return;
				}

				if (ItemsCount /* > 0 */)
				{	// il Combo non é vuoto quindi verifichiamo se
					// il medico cercato è già inserito
					long codice;

					do // do-while cycle
					{
						codice = pCtrlCB->GetItemData(--ItemsCount);

						if ((DWORD)codice == CB_ERR)
						{
							theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_9));
							return;
						}
					} while ((codice != value) && ItemsCount);

					if (codice == value)	// il nuovo medico si trova nel combo => esco
						return;
					// else	//il codice del medico non si trova nel combo
				}

				// è fondamentale che la lista venga concellata
				pCtrlCB->ResetContent();

				CString sFilter;
				sFilter.Format("Contatore=%li", value);

				CMediciSet setMed;
				setMed.SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
				setMed.SetOpenFilter(sFilter);
				if (setMed.OpenRecordset("DDX_FieldOperatori"))
				{
					if (setMed.IsEOF())
					{
						value = 0L;
						setMed.CloseRecordset("DDX_FieldOperatori");
						return;
					}

					int posiz = pCtrlCB->AddString(setMed.m_sTitolo + " " + setMed.m_sNome + " " + setMed.m_sCognome);

					if (posiz == CB_ERR || posiz == CB_ERRSPACE)
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_10));
						setMed.CloseRecordset("DDX_FieldOperatori");
						return;
					}

					value = setMed.m_lContatore;

					if (pCtrlCB->SetItemData(posiz, (DWORD)setMed.m_lContatore) == CB_ERR)
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_11));
						setMed.CloseRecordset("DDX_FieldOperatori");
						return;
					}

					if (pCtrlCB->SetCurSel(posiz) == CB_ERR)
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_12));
						setMed.CloseRecordset("DDX_FieldOperatori");
						return;
					}

					setMed.CloseRecordset("DDX_FieldOperatori");
				}
			}
			else
			{
				pCtrlCB->ResetContent();
				value = 0L;
			}
		}
	}
	else
	{	// qualche errore é avvenuto dunque é bene pulire il combo
		pCtrlCB->ResetContent();
	}
}

void DDX_FieldOperatoriEdit(CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet)
{
	CEdit* pControl = (CEdit*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	pControl->SetWindowText("");
	if (pRecordSet->IsOpen() == TRUE)
	{
		if (pDX->m_bSaveAndValidate)
		{
			// BOH, forse non serve mai //
		}
		else
		{
			CString sFilter;
			sFilter.Format("Contatore=%li", value);

			CMediciSet setMed;
			setMed.SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
			setMed.SetOpenFilter(sFilter);
			if (setMed.OpenRecordset("DDX_FieldOperatoriEdit") == TRUE)
			{
				if (!setMed.IsEOF())
					pControl->SetWindowText(setMed.m_sTitolo + " " + setMed.m_sNome + " " + setMed.m_sCognome);

				setMed.CloseRecordset("DDX_FieldOperatoriEdit");
			}
		}
	}
}

void DDX_FieldInfermieriCombo(CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet)
{
	HWND		hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	CComboBox*	pCtrlCB = (CComboBox*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	if (pRecordSet->IsOpen())
	{
		if (pDX->m_bSaveAndValidate)	// mette nell'esame il codice del medico
		{
			int	CurSel = pCtrlCB->GetCurSel();

			if (CurSel == CB_ERR)
			{	// no item selected
				value = 0L;
				//pDX->Fail();
				return;
			}

			long codice = pCtrlCB->GetItemData(CurSel);

			if ((DWORD)codice == CB_ERR)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_14));
				return;
			}

			value = codice;
			pRecordSet->SetFieldNull(&value, FALSE);
		}
		else	// Carica nel Combo l'infermiere dell'esame
		{
			if (!pRecordSet->IsFieldNull(&value))
			{
				int ItemsCount = pCtrlCB->GetCount();

				if (ItemsCount == CB_ERR)
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_15));
					return;
				}

				if (ItemsCount /* > 0 */)
				{	// il Combo non é vuoto quindi verifichiamo se
					// il medico cercato è già inserito
					long codice;

					do // do-while cycle
					{
						codice = pCtrlCB->GetItemData(--ItemsCount);

						if ((DWORD)codice == CB_ERR)
						{
							theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_16));
							return;
						}
					} while ((codice != value) && ItemsCount);

					if (codice == value)	// il nuovo medico si trova nel combo => esco
						return;
					// else	//il codice del medico non si trova nel combo
				}

				// è fondamentale che la lista venga concellata
				pCtrlCB->ResetContent();

				CString sFilter;
				sFilter.Format("Contatore=%li", value);

				CInfermieriSet setInf;
				setInf.SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
				setInf.SetOpenFilter(sFilter);

				if (setInf.OpenRecordset("DDX_FieldInfermieri"))
				{
					if (setInf.IsEOF())
					{
						value = 0L;
						setInf.CloseRecordset("DDX_FieldInfermieri");
						return;
					}

					int posiz = pCtrlCB->AddString(setInf.m_sTitolo + " " + setInf.m_sNome + " " + setInf.m_sCognome);

					if (posiz == CB_ERR || posiz == CB_ERRSPACE)
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_17));
						setInf.CloseRecordset("DDX_FieldInfermieri");
						return;
					}

					value = setInf.m_lContatore;

					if (pCtrlCB->SetItemData(posiz, (DWORD)setInf.m_lContatore) == CB_ERR)
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_18));
						setInf.CloseRecordset("DDX_FieldInfermieri");
						return;
					}

					if (pCtrlCB->SetCurSel(posiz) == CB_ERR)
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_19));
						setInf.CloseRecordset("DDX_FieldInfermieri");
						return;
					}

					setInf.CloseRecordset("DDX_FieldInfermieri");
				}
			}
			else
			{
				pCtrlCB->ResetContent();
				value = 0L;
			}
		}
	}
	else
	{	// qualche errore é avvenuto dunque é bene pulire il combo
		pCtrlCB->ResetContent();
	}
}

void DDX_FieldInfermieriEdit(CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet)
{
	CEdit* pControl = (CEdit*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	pControl->SetWindowText("");
	if (pRecordSet->IsOpen() == TRUE)
	{
		if (pDX->m_bSaveAndValidate)
		{
			// BOH, forse non serve mai //
		}
		else
		{
			CString sFilter;
			sFilter.Format("Contatore=%li", value);

			CInfermieriSet setInf;
			setInf.SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
			setInf.SetOpenFilter(sFilter);
			if (setInf.OpenRecordset("DDX_FieldInfermieriEdit") == TRUE)
			{
				if (!setInf.IsEOF())
					pControl->SetWindowText(setInf.m_sTitolo + " " + setInf.m_sNome + " " + setInf.m_sCognome);

				setInf.CloseRecordset("DDX_FieldInfermieriEdit");
			}
		}
	}
}

void DDX_FieldInviantiCombo(CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet, long lProvenienza)
{
	HWND		hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	CComboBox*	pCtrlCB = (CComboBox*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	if (pRecordSet->IsOpen())
	{
		if (pDX->m_bSaveAndValidate)	// mette nell'esame il codice del medico
		{
			int	CurSel = pCtrlCB->GetCurSel();

			if (CurSel == CB_ERR)
			{	// no item selected
				value = 0L;
				//pDX->Fail();
				return;
			}

			long codice = pCtrlCB->GetItemData(CurSel);

			if ((DWORD)codice == CB_ERR)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_20));
				return;
			}

			value = codice;
			pRecordSet->SetFieldNull(&value, FALSE);
		}
		else	// Carica nel Combo il medico dell'esame
		{
			if (!pRecordSet->IsFieldNull(&value))
			{
				int ItemsCount = pCtrlCB->GetCount();

				if (ItemsCount == CB_ERR)
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_21));
					return;
				}

				if (ItemsCount /* > 0 */)
				{	// il Combo non é vuoto quindi verifichiamo se
					// il medico cercato è già inserito
					long codice;

					do // do-while cycle
					{
						codice = pCtrlCB->GetItemData(--ItemsCount);

						if ((DWORD)codice == CB_ERR)
						{
							theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_22));
							return;
						}
					} while ((codice != value) && ItemsCount);

					if (codice == value)	// il nuovo medico si trova nel combo => esco
						return;
					// else	//il codice del medico non si trova nel combo
				}

				// è fondamentale che la lista venga concellata
				pCtrlCB->ResetContent();

				CString sFilter;
				sFilter.Format("Contatore=%li", value);

				//

				CInviantiSet setInvianti;

				switch (lProvenienza)
				{
				case INTERNO:
				{
					setInvianti.SetTableName("EInviantiInterni");
					break;
				}
				case ESTERNO:
				{
					setInvianti.SetTableName("EInviantiEsterni");
					break;
				}
				default:
				{
					ASSERT(FALSE);
					break;
				}
				}

				setInvianti.SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
				setInvianti.SetOpenFilter(sFilter);
				if (setInvianti.OpenRecordset("DDX_FieldInviantiCombo"))
				{
					if (setInvianti.IsEOF())
					{
						value = 0L;
						setInvianti.CloseRecordset("DDX_FieldInviantiCombo");
						return;
					}

					int posiz = pCtrlCB->AddString(setInvianti.m_sDescrizione);

					if (posiz == CB_ERR || posiz == CB_ERRSPACE)
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_23));
						setInvianti.CloseRecordset("DDX_FieldInviantiCombo");
						return;
					}

					value = setInvianti.m_lContatore;

					if (pCtrlCB->SetItemData(posiz, (DWORD)setInvianti.m_lContatore) == CB_ERR)
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_24));
						setInvianti.CloseRecordset("DDX_FieldInviantiCombo");
						return;
					}

					if (pCtrlCB->SetCurSel(posiz) == CB_ERR)
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_25));
						setInvianti.CloseRecordset("DDX_FieldInviantiCombo");
						return;
					}

					setInvianti.CloseRecordset("DDX_FieldInviantiCombo");
				}
			}
			else
			{
				pCtrlCB->ResetContent();
				value = 0L;
			}
		}
	}
	else
	{	// qualche errore é avvenuto dunque é bene pulire il combo
		pCtrlCB->ResetContent();
	}
}

void DDX_FieldInviantiEdit(CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet, long lProvenienza)
{
	CEdit* pControl = (CEdit*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	pControl->SetWindowText("");
	if (pRecordSet->IsOpen() == TRUE)
	{
		if (pDX->m_bSaveAndValidate)
		{
			// BOH, forse non serve mai //
			// ASSERT(FALSE); però ci passa :-7
		}
		else
		{
			CString sFilter;
			sFilter.Format("Contatore=%li", value);

			CInviantiSet setInvianti;

			switch (lProvenienza)
			{
			case INTERNO:
			{
				setInvianti.SetTableName("EInviantiInterni");
				break;
			}
			case ESTERNO:
			{
				setInvianti.SetTableName("EInviantiEsterni");
				break;
			}
			default:
			{
				ASSERT(FALSE);
				break;
			}
			}

			setInvianti.SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
			setInvianti.SetOpenFilter(sFilter);
			if (setInvianti.OpenRecordset("DDX_FieldInviantiEdit") == TRUE)
			{
				if (!setInvianti.IsEOF())
					pControl->SetWindowText(setInvianti.m_sDescrizione);

				setInvianti.CloseRecordset("DDX_FieldInviantiEdit");
			}
		}
	}
}

void DDX_FieldSedeEsame(CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet)
{
	CEdit* pControl = (CEdit*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	if (pRecordSet->IsOpen())
	{
		if (pDX->m_bSaveAndValidate)
		{
			CString strTemp;
			pControl->GetWindowText(strTemp);

			value = CSediEsameSet().GetID(strTemp);
		}
		else
		{
			pControl->SetWindowText(CSediEsameSet().GetDescrizione(value, FALSE));
		}
	}
	else
	{
		pControl->SetWindowText("");
	}
}

void DDX_FieldComboTransCombo(CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet, CComboTransSet* pDataSourceRecordSet)
{
	HWND		hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	CComboBox*	pCtrlCB = (CComboBox*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	if (pRecordSet->IsOpen())
	{
		if (pDX->m_bSaveAndValidate)	// mette nell'esame il codice del medico
		{
			int	CurSel = pCtrlCB->GetCurSel();

			if (CurSel == CB_ERR)
			{	// no item selected
				value = 0L;
				//pDX->Fail();
				return;
			}

			long codice = pCtrlCB->GetItemData(CurSel);

			if ((DWORD)codice == CB_ERR)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_7));
				return;
			}

			value = codice;
			pRecordSet->SetFieldNull(&value, FALSE);
		}
		else	// Carica nel Combo il medico dell'esame
		{
			if (!pRecordSet->IsFieldNull(&value))
			{
				int ItemsCount = pCtrlCB->GetCount();

				if (ItemsCount == CB_ERR)
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_8));
					return;
				}

				if (ItemsCount /* > 0 */)
				{	// il Combo non é vuoto quindi verifichiamo se
					// il medico cercato è già inserito
					long codice;

					do // do-while cycle
					{
						codice = pCtrlCB->GetItemData(--ItemsCount);

						if ((DWORD)codice == CB_ERR)
						{
							theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_9));
							return;
						}
					} while ((codice != value) && ItemsCount);

					if (codice == value)	// il nuovo medico si trova nel combo => esco
						return;
					// else	//il codice del medico non si trova nel combo
				}

				// è fondamentale che la lista venga concellata
				pCtrlCB->ResetContent();

				CString sFilter;
				sFilter.Format("ID=%li", value);

				pDataSourceRecordSet->SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
				pDataSourceRecordSet->SetOpenFilter(sFilter);
				if (pDataSourceRecordSet->OpenRecordset("DDX_FieldComboTransCombo"))
				{
					if (pDataSourceRecordSet->IsEOF())
					{
						value = 0L;
						pDataSourceRecordSet->CloseRecordset("DDX_FieldComboTransCombo");
						return;
					}

					int posiz = pCtrlCB->AddString(pDataSourceRecordSet->m_sDescrizione);

					if (posiz == CB_ERR || posiz == CB_ERRSPACE)
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_10));
						pDataSourceRecordSet->CloseRecordset("DDX_FieldComboTransCombo");
						return;
					}

					value = pDataSourceRecordSet->m_lID;

					if (pCtrlCB->SetItemData(posiz, (DWORD)pDataSourceRecordSet->m_lID) == CB_ERR)
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_11));
						pDataSourceRecordSet->CloseRecordset("DDX_FieldComboTransCombo");
						return;
					}

					if (pCtrlCB->SetCurSel(posiz) == CB_ERR)
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_12));
						pDataSourceRecordSet->CloseRecordset("DDX_FieldComboTransCombo");
						return;
					}

					pDataSourceRecordSet->CloseRecordset("DDX_FieldComboTransCombo");
				}
			}
			else
			{
				pCtrlCB->ResetContent();
				value = 0L;
			}
		}
	}
	else
	{
		// qualche errore é avvenuto dunque é bene pulire il combo
		pCtrlCB->ResetContent();
	}
}

void DDX_FieldComboTransEdit(CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet, CComboTransSet* pDataSourceRecordSet)
{
	CEdit* pControl = (CEdit*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	pControl->SetWindowText("");
	if (pRecordSet->IsOpen() == TRUE)
	{
		if (pDX->m_bSaveAndValidate)
		{
			// BOH, forse non serve mai //
		}
		else
		{
			CString sFilter;
			sFilter.Format("ID=%li", value);

			pDataSourceRecordSet->SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
			pDataSourceRecordSet->SetOpenFilter(sFilter);
			if (pDataSourceRecordSet->OpenRecordset("DDX_FieldComboTransEdit") == TRUE)
			{
				if (pDataSourceRecordSet->IsEOF() == FALSE)
					pControl->SetWindowText(pDataSourceRecordSet->m_sDescrizione);

				pDataSourceRecordSet->CloseRecordset("DDX_FieldComboTransEdit");
			}
		}
	}
}

void DDX_FieldProvenienzaCombo(CDataExchange* pDX, int nIDC, long& value, long& valueOldProvenienza, CBaseSet* pRecordSet)
{
	HWND		hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	CComboBox*	pCtrlCB = (CComboBox*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	if (pRecordSet->IsOpen())
	{
		if (pDX->m_bSaveAndValidate)	// mette nell'esame il codice della provenienza
		{
			int	CurSel = pCtrlCB->GetCurSel();

			if (CurSel == CB_ERR)
			{	// no item selected
				value = 0L;
				valueOldProvenienza = 0L;
				//pDX->Fail();
				return;
			}

			long codice = pCtrlCB->GetItemData(CurSel);

			if ((DWORD)codice == CB_ERR)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_20));
				return;
			}

			value = codice;
			valueOldProvenienza = CProvenienzaSet().GetInternoEsterno(codice);

			pRecordSet->SetFieldNull(&value, FALSE);
		}
		else	// Carica nel Combo la prov
		{
			if (!pRecordSet->IsFieldNull(&value))
			{
				int ItemsCount = pCtrlCB->GetCount();

				if (ItemsCount == CB_ERR)
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_21));
					return;
				}

				if (ItemsCount /* > 0 */)
				{	// il Combo non é vuoto quindi verifichiamo se
					// il medico cercato è già inserito
					long codice;

					do // do-while cycle
					{
						codice = pCtrlCB->GetItemData(--ItemsCount);

						if ((DWORD)codice == CB_ERR)
						{
							theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_22));
							return;
						}
					} while ((codice != value) && ItemsCount);

					if (codice == value) // il nuovo medico si trova nel combo => esco
					{
						return;
					}
					// else	//il codice del medico non si trova nel combo
				}

				// è fondamentale che la lista venga concellata
				pCtrlCB->ResetContent();

				CString sFilter;
				sFilter.Format("ID=%li", value);

				//

				CProvenienzaSet setProvenienza;

				setProvenienza.SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
				setProvenienza.SetOpenFilter(sFilter);
				if (setProvenienza.OpenRecordset("DDX_FieldProvenienzaCombo"))
				{
					if (setProvenienza.IsEOF())
					{
						value = 0L;
						valueOldProvenienza = 0L;
						setProvenienza.CloseRecordset("DDX_FieldProvenienzaCombo");
						return;
					}

					CString descrizione = setProvenienza.m_sDescrizione;

					if (setProvenienza.m_lIdProvenienzaEndox == INTERNO)
						descrizione += " (" + theApp.GetMessageString(IDS_INTERNO).MakeUpper() + ")";
					else
						descrizione += " (" + theApp.GetMessageString(IDS_ESTERNO).MakeUpper() + ")";

					int posiz = pCtrlCB->AddString(descrizione);

					if (posiz == CB_ERR || posiz == CB_ERRSPACE)
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_23));
						setProvenienza.CloseRecordset("DDX_FieldProvenienzaCombo");
						return;
					}

					value = setProvenienza.m_lId;
					valueOldProvenienza = setProvenienza.m_lIdProvenienzaEndox;

					if (pCtrlCB->SetItemData(posiz, (DWORD)setProvenienza.m_lId) == CB_ERR)
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_24));
						setProvenienza.CloseRecordset("DDX_FieldProvenienzaCombo");
						return;
					}

					if (pCtrlCB->SetCurSel(posiz) == CB_ERR)
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_COMMON_ERR_25));
						setProvenienza.CloseRecordset("DDX_FieldProvenienzaCombo");
						return;
					}

					setProvenienza.CloseRecordset("DDX_FieldProvenienzaCombo");
				}
			}
			else
			{
				pCtrlCB->ResetContent();
				value = 0L;
				valueOldProvenienza = 0L;
			}
		}
	}
	else
	{	// qualche errore é avvenuto dunque é bene pulire il combo
		pCtrlCB->ResetContent();
	}
}

void DDX_FieldProvenienzaEdit(CDataExchange* pDX, int nIDC, long& value, CBaseSet* pRecordSet)
{
	CEdit* pControl = (CEdit*)pDX->m_pDlgWnd->GetDlgItem(nIDC);

	pControl->SetWindowText("");
	if (pRecordSet->IsOpen() == TRUE)
	{
		if (pDX->m_bSaveAndValidate)
		{
			// BOH, forse non serve mai //
			// ASSERT(FALSE); però ci passa :-7
		}
		else
		{
			CString sFilter;
			sFilter.Format("ID=%li", value);

			CProvenienzaSet setProvenienza;

			setProvenienza.SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
			setProvenienza.SetOpenFilter(sFilter);
			if (setProvenienza.OpenRecordset("DDX_FieldProvenienzaEdit") == TRUE)
			{
				if (!setProvenienza.IsEOF())
				{
					CString descrizione = setProvenienza.m_sDescrizione;

					if (setProvenienza.m_lIdProvenienzaEndox == INTERNO)
						descrizione += " (" + theApp.GetMessageString(IDS_INTERNO).MakeUpper() + ")";
					else
						descrizione += " (" + theApp.GetMessageString(IDS_ESTERNO).MakeUpper() + ")";

					pControl->SetWindowText(descrizione);
				}

				setProvenienza.CloseRecordset("DDX_FieldProvenienzaEdit");
			}
		}
	}
}

void ConvertInValidStringSQL(CString* pStr)
{
	pStr->Replace("'", "''");
}

//Davide
void ComponiRicercaEx(CString *strFilter, CString strRicerca, CString strLabel, BOOL bAggiungiSegni, BOOL bNumber)
{
	BOOL bOK = !strRicerca.IsEmpty();

	if (bOK)
	{
		if (!bNumber)
			strRicerca = "'%" + strRicerca + "%'";

		if (bAggiungiSegni)
		{
			if (bNumber)
				strRicerca = strLabel + " = " + strRicerca;
			else
				strRicerca = strLabel + " LIKE " + strRicerca;
		}
		else
			strRicerca = strLabel + " " + strRicerca;

		strRicerca = " ( " + strRicerca + " ) ";

		if (bAggiungiSegni)
		{
			if (bNumber)
			{
				strRicerca.Replace(" OR ", " OR " + strLabel + " = ");
				strRicerca.Replace(" AND ", " AND " + strLabel + " = ");
			}
			else
			{
				strRicerca.Replace(" OR ", "%' OR " + strLabel + " LIKE '%");
				strRicerca.Replace(" AND ", "%' AND " + strLabel + " LIKE '%");
			}
		}
		else
		{
			strRicerca.Replace("OR ", "OR " + strLabel);
			strRicerca.Replace("AND ", "AND " + strLabel);
		}

		if (!strFilter->IsEmpty())
		{
			(*strFilter) += " AND ";
		}

		(*strFilter) += strRicerca;

	}
}

void ComponiRicercaFromEx(CString *strFilter, CString *pStrFrom, CString strRicerca, CString strTable, long lTable, CString strField, CString strJoinField, BOOL bAggiungiSegni, BOOL bNumber)
{
	BOOL bOK = !strRicerca.IsEmpty();

	if (bOK)
	{
		CString strTableNew, strLabel;
		strTableNew.Format("%s%02li", strTable, lTable);
		strLabel = strTableNew + "." + strField;

		if (!bNumber)
			strRicerca = "'%" + strRicerca + "%'";

		if (bAggiungiSegni)
		{
			if (bNumber)
				strRicerca = strLabel + " = " + strRicerca;
			else
				strRicerca = strLabel + " LIKE " + strRicerca;
		}
		else
			strRicerca = strLabel + " " + strRicerca;

		strRicerca = " ( " + strRicerca + " ) ";

		if (bAggiungiSegni)
		{
			if (bNumber)
			{
				strRicerca.Replace(" OR ", " OR " + strLabel + " = ");
				strRicerca.Replace(" AND ", " AND " + strLabel + " = ");
			}
			else
			{
				strRicerca.Replace(" OR ", "%' OR " + strLabel + " LIKE '%");
				strRicerca.Replace(" AND ", "%' AND " + strLabel + " LIKE '%");
			}
		}
		else
		{
			strRicerca.Replace("OR ", "OR " + strLabel);
			strRicerca.Replace("AND ", "AND " + strLabel);
		}

		if (!strFilter->IsEmpty())
		{
			(*strFilter) += " AND ";
		}

		(*strFilter) += strRicerca;


		// preparo il FROM //
		if (pStrFrom)
		{
			if (pStrFrom->Find(" " + strTableNew + " ") == -1)
			{
				CString strFrom;
				strFrom.Format("LEFT OUTER JOIN %s %s ON EEsami.Contatore=%s.%s ", strTable, strTableNew, strTableNew, strJoinField);
				(*pStrFrom) += strFrom;
			}
		}
	}
}

//Per costruire filtro con combo a selezione singola (es. fumo - sigarette - ecc.)
//Solo condizione OR
void ComponiRicercaRadioEx(CString *strFilter, CString strParam, CString strLabel)
{
	if (strParam.IsEmpty() == FALSE)
	{
		CString strBuffer = strLabel + "=" + strParam;

		strBuffer = " ( " + strBuffer + " ) ";

		strBuffer.Replace("OR ", "OR " + strLabel + "=");

		if (strFilter->IsEmpty() == FALSE)
		{
			(*strFilter) += " AND ";
		}

		(*strFilter) += strBuffer;
	}
}

// Restituisce in un array di stringhe gli elementi senza AND e OR
void ComponiRicercaArray(CStringArray* pLista, CString strComplete)
{
	const int nOperators = 2;

	//									  AND      OR      AND    OR
	static CString	strOperator[nOperators] = { " AND ", " OR " };
	static int		nLenOperator[nOperators] = { 5, 4 };

	int			nFind[nOperators];
	int			nIndex = -1;
	int			nLenStr = strComplete.GetLength();
	CString		strLeft;
	CString		strRight;
	int i = 0;

	for (i = 0; i < nOperators; i++)
		nFind[i] = strComplete.Find(strOperator[i]);

	for (i = 0; i < nOperators; i++)
	{
		if (nFind[i] >= 0)
		{
			if (nIndex >= 0 && nFind[i] < nFind[nIndex] || nIndex < 0)
				nIndex = i;
		}
	}

	if (nIndex < 0)
	{
		if (strComplete != "")
			pLista->Add(strComplete);

		return;
	}

	//stringa di sinistra....
	strLeft = strComplete.Left(nFind[nIndex]);

	if (strLeft != "")
	{
		pLista->Add(strLeft);
		pLista->Add(strOperator[nIndex % 2]);
	}

	//scomposizione stringa di destra....
	strRight = strComplete.Right(nLenStr - (nFind[nIndex] + nLenOperator[nIndex]));

	ComponiRicercaArray(pLista, strRight);
}

void ComponiRicercaCognomeNome(CString *pStrFilter, CBaseSet* pSet, CString* pStrField, CString sLabel)
{
	pStrField->MakeUpper();
	pStrField->Trim();
	if (!pStrField->IsEmpty())
	{
		if ((pSet->IsOpen() && !pSet->IsFieldNull(pStrField)) || !pSet->IsOpen())
		{
			if (!pStrFilter->IsEmpty())
				(*pStrFilter) += " AND ";

			// tolgo tutti i doppi spazi in mezzo //

			int iSost;
			do
			{
				iSost = pStrField->Replace("  ", " ");
			} while (iSost > 0);

			// raddoppio gli apici //

			ConvertInValidStringSQL(pStrField);

			// inserisco in lista tutte le singole parole da cercare //

			CStringList listRicerche;

			int nSpacePrv = -1;
			int nSpaceAct = pStrField->Find(' ');
			while (nSpaceAct > 0)
			{
				listRicerche.AddTail(pStrField->Mid(nSpacePrv + 1, nSpaceAct - (nSpacePrv + 1)));

				nSpacePrv = nSpaceAct;
				nSpaceAct = pStrField->Find(' ', nSpacePrv + 1);
			}
			listRicerche.AddTail(pStrField->Right(pStrField->GetLength() - (nSpacePrv + 1)));

			//

			(*pStrFilter) += "(";

			// per ogni parola... //

			int nPassaggio = 0;

			POSITION pos = listRicerche.GetHeadPosition();
			while (pos != NULL)
			{
				CString sTemp = listRicerche.GetAt(pos);

				if (nPassaggio > 0)
					(*pStrFilter) += " AND ";

				if (sTemp.Right(1) == 'A')
					(*pStrFilter) += "(" + sLabel + " LIKE '%" + sTemp + "%' OR " + sLabel + " LIKE '%" + sTemp.Left(sTemp.GetLength() - 1) + "À%')";
				else if (sTemp.Right(1) == 'E')
					(*pStrFilter) += "(" + sLabel + " LIKE '%" + sTemp + "%' OR " + sLabel + " LIKE '%" + sTemp.Left(sTemp.GetLength() - 1) + "È%')";
				else if (sTemp.Right(1) == 'I')
					(*pStrFilter) += "(" + sLabel + " LIKE '%" + sTemp + "%' OR " + sLabel + " LIKE '%" + sTemp.Left(sTemp.GetLength() - 1) + "Ì%')";
				else if (sTemp.Right(1) == 'O')
					(*pStrFilter) += "(" + sLabel + " LIKE '%" + sTemp + "%' OR " + sLabel + " LIKE '%" + sTemp.Left(sTemp.GetLength() - 1) + "Ò%')";
				else if (sTemp.Right(1) == 'U')
					(*pStrFilter) += "(" + sLabel + " LIKE '%" + sTemp + "%' OR " + sLabel + " LIKE '%" + sTemp.Left(sTemp.GetLength() - 1) + "Ù%')";
				else if (sTemp.Right(1) == 'À')
					(*pStrFilter) += "(" + sLabel + " LIKE '%" + sTemp + "%' OR " + sLabel + " LIKE '%" + sTemp.Left(sTemp.GetLength() - 1) + "A%')";
				else if (sTemp.Right(1) == 'È')
					(*pStrFilter) += "(" + sLabel + " LIKE '%" + sTemp + "%' OR " + sLabel + " LIKE '%" + sTemp.Left(sTemp.GetLength() - 1) + "E%')";
				else if (sTemp.Right(1) == 'Ì')
					(*pStrFilter) += "(" + sLabel + " LIKE '%" + sTemp + "%' OR " + sLabel + " LIKE '%" + sTemp.Left(sTemp.GetLength() - 1) + "I%')";
				else if (sTemp.Right(1) == 'Ò')
					(*pStrFilter) += "(" + sLabel + " LIKE '%" + sTemp + "%' OR " + sLabel + " LIKE '%" + sTemp.Left(sTemp.GetLength() - 1) + "O%')";
				else if (sTemp.Right(1) == 'Ù')
					(*pStrFilter) += "(" + sLabel + " LIKE '%" + sTemp + "%' OR " + sLabel + " LIKE '%" + sTemp.Left(sTemp.GetLength() - 1) + "U%')";
				else
					(*pStrFilter) += "(" + sLabel + " LIKE '%" + sTemp + "%')";

				nPassaggio++;
				listRicerche.GetNext(pos);
			}

			//

			(*pStrFilter) += ")";
		}
	}
}

void ComponiRicercaString(CString *strFilter, CBaseSet* pSet, CString* pStr, CString strLabel, short mode)
{
	if (!pStr->IsEmpty())
	{
		if (strFilter->IsEmpty() == FALSE)
			(*strFilter) += " AND ";

		ConvertInValidStringSQL(pStr);

		//composizione ricerce tenendo conto di AND e OR sulla stringa...
		CStringArray Lista;

		ComponiRicercaArray(&Lista, *pStr);

		(*strFilter) += "(";

		for (int i = 0; i < Lista.GetSize(); i++)
		{
			if (Lista.GetSize() > 1)
				mode = 1;

			if (i % 2 == 0)
			{
				switch (mode)
				{
				case 0:
				{
					(*strFilter) += strLabel + " LIKE '" + Lista.GetAt(i) + "%'";
					break;
				}
				case 1:
				{
					(*strFilter) += strLabel + " LIKE '%" + Lista.GetAt(i) + "%'";
					break;
				}
				case 2:
				{
					(*strFilter) += strLabel + " = '" + Lista.GetAt(i) + "'";
					break;
				}
				case 3:
				{
					(*strFilter) += strLabel + " LIKE '" + Lista.GetAt(i) + "'";
					break;
				}
				}
			}
			else
			{
				//operatore OR / AND
				(*strFilter) += Lista.GetAt(i);
			}
		}

		(*strFilter) += ")";
		Lista.RemoveAll();
		//////////////////////////////////////////////////////////////////
	}
}

/*
void ComponiRicerca(CString *strFilter, CBaseSet* pSet, CString* pStr, CString strLabel, short mode, CString strOperator)
{
if ((pSet->IsFieldNull(pStr) == FALSE) && ((*pStr) != ""))
{
if (strFilter->IsEmpty() == FALSE)
(*strFilter) += " " + strOperator + " ";

ConvertInValidStringSQL(pStr);

switch(mode)
{
case 0:
(*strFilter) += strLabel + " LIKE '" + (*pStr) + "%'";
break;
case 1:
(*strFilter) += strLabel + " LIKE '%" + (*pStr) + "%'";
break;
case 2:
(*strFilter) += strLabel + " = '" + (*pStr) + "'";
break;
}
}
}
*/

void ComponiRicercaLong(CString *strFilter, CBaseSet* pSet, long* pLong, CString strLabel, short mode, CString strOperator)
{
	if (((pSet->IsOpen()) && ((*pLong) > 0) && ((*pLong) < 1246576928)) || (!pSet->IsOpen()) && ((*pLong) || (mode == 4)))
	{
		CString strBuffer;
		strBuffer.Format("%li", *pLong);

		if (strFilter->IsEmpty() == FALSE)
			(*strFilter) += (" " + strOperator + " ");

		switch (mode)
		{
		case 0:
			(*strFilter) += strLabel + " = " + strBuffer;
			break;
		case 1:
			(*strFilter) += strLabel + " >= " + strBuffer;
			break;
		case 2:
			(*strFilter) += strLabel + " <= " + strBuffer;
			break;
		case 3:
			(*strFilter) += strLabel + " <> " + strBuffer;
			break;
		case 4:
			(*strFilter) += strLabel + " = " + strBuffer;
			break;
		}
	}
}

void ComponiRicercaShort(CString& strFilter, CBaseSet* pSet, short* pInt, CString strLabel, short mode, BOOL bZero)
{
	BOOL bOK = (pSet->IsOpen() && !pSet->IsFieldNull(pInt)) || (!pSet->IsOpen());

	if (bOK && (bZero || *pInt))
	{
		CString strBuffer;

		strBuffer.Format("%i", *pInt);

		if (!strFilter.IsEmpty())
		{
			strFilter += " AND ";
		}

		switch (mode)
		{
		case 0:
			strFilter += strLabel + " = " + strBuffer;
			break;
		case 1:
			strFilter += strLabel + " >= " + strBuffer;
			break;
		case 2:
			strFilter += strLabel + " <= " + strBuffer;
			break;
		case 3:
			strFilter += strLabel + " <> " + strBuffer;
			break;
		}
	}
}

void ComponiRicercaRadio(CString *strFilter, CBaseSet* pSet, void* pVoid, int nByte, CString strLabel, short mode)
{
	BOOL	bOK = (pSet->IsOpen() && !pSet->IsFieldNull(pVoid)) || (!pSet->IsOpen());
	short*	pShort = NULL;
	long*	pLong = NULL;

	if (nByte == 2)
		pShort = (short*)pVoid;
	else
		pLong = (long*)pVoid;

	if (bOK && ((pLong && *pLong > -1) || (pShort && *pShort > -1)))
	{
		CString strBuffer;

		if (pShort)
			strBuffer.Format("%i", *pShort);
		else
			strBuffer.Format("%li", *pLong);

		if (strFilter->IsEmpty() == FALSE)
			(*strFilter) += " AND ";

		switch (mode)
		{
		case 0:
			(*strFilter) += strLabel + " = " + strBuffer;
			break;
		case 1:
			(*strFilter) += strLabel + " >= " + strBuffer;
			break;
		case 2:
			(*strFilter) += strLabel + " <= " + strBuffer;
			break;
		case 3:
			(*strFilter) += strLabel + " <> " + strBuffer;
			break;
		}
	}
}

void ComponiRicercaSesso(CString& strFilter, CBaseSet* pSet, void* pVoid, CString strLabel, short mode)
{
	BOOL	bOK = (pSet->IsOpen() && !pSet->IsFieldNull(pVoid)) || (!pSet->IsOpen());
	long*	pLong = NULL;

	pLong = (long*)pVoid;

	if (*pLong == -2) //Ho selezionato TUTTI
		return;

	if (bOK && (pLong)) // && (*pLong == -1 || *pLong == 0 || *pLong == 1)))
	{
		CString strBuffer;

		strBuffer.Format("%li", *pLong);

		if (!strFilter.IsEmpty())
			strFilter += " AND ";

		switch (mode)
		{
		case 0:
			strFilter += strLabel + " = " + strBuffer;
			break;
		case 1:
			strFilter += strLabel + " >= " + strBuffer;
			break;
		case 2:
			strFilter += strLabel + " <= " + strBuffer;
			break;
		case 3:
			strFilter += strLabel + " <> " + strBuffer;
			break;
		}
	}
}

void ComponiRicercaCheckSND(CString& strFilter, CBaseSet* pSet, long* pLong, CString strLabel)
{
	BOOL	bIsNull = (pSet->IsOpen() && pSet->IsFieldNull(pLong));
	CString strBuffer;

	strBuffer.Format("%li", *pLong);

	if (!bIsNull && (pLong && ((*pLong) == 1)))
	{
		if (!strFilter.IsEmpty())
			strFilter += " AND ";

		strFilter += strLabel + " = " + strBuffer;
	}
}

void ComponiRicercaRange(CString* strRicerca, int n1, int n2, CString strLabel)
{
	CString strBuffer = "";

	if ((n1 > 0) && (n2 > 0))
	{
		if (!strRicerca->IsEmpty())
			strBuffer.Format(" AND (%s BETWEEN %d AND %d)", strLabel, n1, n2);
		else
			strBuffer.Format("(%s BETWEEN %d AND %d)", strLabel, n1, n2);
	}
	else
	{
		if ((n1 > 0) || (n2 > 0))
		{
			if (n1 > 0)
			{
				if (!strRicerca->IsEmpty())
					strBuffer.Format(" AND (%s>%d)", strLabel, n1);
				else
					strBuffer.Format("(%s>%d)", strLabel, n1);
			}
			else
			{
				if (!strRicerca->IsEmpty())
					strBuffer.Format(" AND (%s>0 AND %s<=%d)", strLabel, strLabel, n2);
				else
					strBuffer.Format("(%s>0 AND %s<=%d)", strLabel, strLabel, n2);
			}
		}
	}

	(*strRicerca) += strBuffer;
}

void ComponiRicercaRange(CString* strRicerca, float f1, float f2, CString strLabel)
{
	CString strBuffer = "";

	if ((f1 > 0) && (f2 > 0))
	{
		if (!strRicerca->IsEmpty())
			strBuffer.Format(" AND (%s BETWEEN %f AND %f)", strLabel, f1, f2);
		else
			strBuffer.Format("(%s BETWEEN %f AND %f)", strLabel, f1, f2);
	}
	else
	{
		if ((f1 > 0) || (f2 > 0))
		{
			if (f1 > 0)
			{
				if (!strRicerca->IsEmpty())
					strBuffer.Format(" AND (%s>%f)", strLabel, f1);
				else
					strBuffer.Format("(%s>%f)", strLabel, f1);
			}
			else
			{
				if (!strRicerca->IsEmpty())
					strBuffer.Format(" AND (%s>0 AND %s<%f)", strLabel, strLabel, f2);
				else
					strBuffer.Format("(%s>0 AND %s<%f)", strLabel, strLabel, f2);
			}
		}
	}

	(*strRicerca) += strBuffer;
}

void ComponiRicercaFromSpecialString(CString* pFilter, CString str, CString strLabel, CString strOperator)
{
	if (str.IsEmpty())
		return;

	CString strFieldValue(str);
	CStringList listWords;

	// 1. Pulisco un pò la stringa da spazi inutili (tra + e parola)
	int iFind = strFieldValue.Find("+");
	int iPrecPos = 0;
	while (iFind >= 0)
	{
		if (iFind < strFieldValue.GetLength() - 1)
		{
			int iPos = iFind + 1;
			while (strFieldValue.GetAt(iPos) == ' ')
				iPos++;

			strFieldValue = strFieldValue.Left(iFind + 1) + strFieldValue.Right(strFieldValue.GetLength() - iPos);
		}

		iFind = strFieldValue.Find("+", iFind + 1);
	}

	// 2. Separo tutte le parole usando come chiave di ricerca lo spazio
	iFind = strFieldValue.Find(" ");
	iPrecPos = 0;
	CString strWord;

	while (iFind >= 0)
	{
		strWord = strFieldValue.Mid(iPrecPos, iFind - iPrecPos);
		if (strWord != "" && strWord != " ")
			listWords.AddTail(strWord);

		iPrecPos = iFind + 1;
		iFind = strFieldValue.Find(" ", iPrecPos);
	}

	strWord = strFieldValue.Right(strFieldValue.GetLength() - iPrecPos);
	if (strWord != "" && strWord != " ")
		listWords.AddTail(strWord);

	// 3. Riunifico le parole che sono tra doppi apici che devono essere considerate come parola unica
	for (POSITION pos = listWords.GetHeadPosition(); pos;)
	{
		strWord = listWords.GetNext(pos);
		// Il doppio apice può essere anche in seconda posizione visto che può aver davanti il '+'
		// Il controllo di pos != NULL serve perchè potrebbe esserci anche una parola singola
		// tra virgolette
		if ((strWord.GetAt(0) == '\"' || strWord.GetAt(1) == '\"') && pos != NULL)
		{
			// ho trovato l'inizio della stringa tra virgolette
			// adesso cerco la fine e riunifico
			POSITION posEnd = pos;
			CString strWordEnd = strWord;
			while (posEnd != NULL)
			{
				if (strWordEnd.GetAt(strWordEnd.GetLength() - 1) == '\"')
					break;
				strWordEnd = listWords.GetNext(posEnd);
			}

			// La stringa è racchiusa tra pos e posEnd
			CString strNewWord;
			listWords.GetPrev(pos);
			while (pos != posEnd)
			{
				if (!strNewWord.IsEmpty())
					strNewWord += " ";

				POSITION posDelete = pos;
				strNewWord += listWords.GetNext(pos);
				listWords.RemoveAt(posDelete);
			}
			listWords.AddTail(strNewWord);
		}
	}

	// 4. Compongo il filtro
	CString strAndFilter, strOrFilter, strTmp;
	for (POSITION pos = listWords.GetHeadPosition(); pos;)
	{
		strWord = listWords.GetNext(pos);
		strWord.Replace("'", "''");

		if (strWord.Left(1) == "+")
		{
			if (!strAndFilter.IsEmpty())
				strAndFilter += " AND ";

			strWord.Trim("\"+");
			strTmp.Format("(%s LIKE '%%%s%%')", strLabel, strWord);
			strAndFilter += strTmp;
		}
		else
		{
			if (!strOrFilter.IsEmpty())
				strOrFilter += " AND "; // Sandro 06/05/2014 // era " OR " ma per Battaglia va meglio " AND " //

			strWord.Trim("\"");
			strTmp.Format("(%s LIKE '%%%s%%')", strLabel, strWord);
			strOrFilter += strTmp;
		}
	}

	if (!strAndFilter.IsEmpty() || !strOrFilter.IsEmpty())
	{
		CString strFilter;
		if (!strAndFilter.IsEmpty())
			strFilter = "(" + strAndFilter + ")";

		if (!strOrFilter.IsEmpty())
		{
			if (!strFilter.IsEmpty())
				strFilter += " OR ";
			strFilter = "(" + strOrFilter + ")";
		}

		if (!pFilter->IsEmpty())
			(*pFilter) = (*pFilter) + " " + strOperator + " " + strFilter;
		else
			(*pFilter) = strFilter;
	}
}

// Sandro 15/04/2009 --> //
void ComponiRicercaNewLong(CString *pStrFrom, CString *pStrWhere, CString strTable, long lTable, CString strJoinField, CString strWhereField, long lValue, long lOperator, long lMode)
{
	if ((lValue > 0) && (lValue < 1246576928))
	{

#ifdef _DEBUG
		CString strTrace;
		strTrace.Format("-> ComponiRicercaNewLong(strTable=%s, lTable=%li, strJoinField=%s, strWhereField=%s, lValue=%li, lOperator=%li, lMode=%li)\n", strTable, lTable, strJoinField, strWhereField, lValue, lOperator, lMode);
		TRACE0(strTrace);
#endif

		// preparo la stringa del long che poi mi serve //
		CString strValue;
		strValue.Format("%li", lValue);

		// distinguo tra AND (nuova modalità) e OR (funziona come prima) //
		switch (lOperator)
		{
		case OPER_AND:
		case OPER_AND_SPEC:
		{
			CString strTableNew;
			if (lOperator == OPER_AND_SPEC)
				strTableNew = strTable; // non considero il parametro lTable //
			else
				strTableNew.Format("%s%02li", strTable, lTable);

			// preparo il FROM //

			if (pStrFrom->Find(" " + strTableNew + " ") == -1)
			{
				CString strFrom;
				strFrom.Format("LEFT OUTER JOIN %s %s ON EEsami.Contatore=%s.%s ", strTable, strTableNew, strTableNew, strJoinField);
				(*pStrFrom) += strFrom;
			}

			// preparo il WHERE //

			if (!pStrWhere->IsEmpty())
				(*pStrWhere) += (" " + strOperators[OPER_AND] + " ");

			CString strWhere;
			switch (lMode)
			{
			case MODE_UGUALE:
			{
				(*pStrWhere) += (strTableNew + "." + strWhereField + "=" + strValue + " AND " + strTableNew + ".eliminato=0");
				break;
			}
			default:
			{
				ASSERT(FALSE);
				break;
			}
			}

			break;
		}
		case OPER_OR:
		case OPER_OR_SPEC:
		{
			CString strTableNew;
			if (lOperator == OPER_OR_SPEC)
				strTableNew.Format("%s%02li", strTable, lTable); // considero il parametro lTable //
			else
				strTableNew = strTable;

			// preparo il FROM //

			if (pStrFrom->Find(" " + strTableNew + " ") == -1)
			{
				CString strFrom;
				strFrom.Format("LEFT OUTER JOIN %s %s ON EEsami.Contatore=%s.%s ", strTable, strTableNew, strTableNew, strJoinField);
				(*pStrFrom) += strFrom;
			}

			// preparo il WHERE //

			if (!pStrWhere->IsEmpty())
				(*pStrWhere) += (" " + strOperators[OPER_OR] + " ");

			switch (lMode)
			{
			case MODE_UGUALE:
			{
				(*pStrWhere) += (strTableNew + "." + strWhereField + "=" + strValue + " AND " + strTableNew + ".eliminato=0");
				break;
			}
			default:
			{
				ASSERT(FALSE);
				break;
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

void ComponiRicercaNewString(CString *pStrFrom, CString *pStrWhere, CString strTable, long lTable, CString strJoinField, CString strWhereField, CString strValue, long lOperator, long lMode, BOOL bMakeUpper)
{
	if (!strValue.IsEmpty())
	{

#ifdef _DEBUG
		CString strTrace;
		strTrace.Format("-> ComponiRicercaNewString(strTable=%s, lTable=%li, strJoinField=%s, strWhereField=%s, strValue=%s, lOperator=%li, lMode=%li, bMakeUpper=%li)\n", strTable, lTable, strJoinField, strWhereField, strValue, lOperator, lMode, (long)bMakeUpper);
		TRACE0(strTrace);
#endif

		if (bMakeUpper)
			strValue.MakeUpper();

		// distinguo tra AND (nuova modalità) e OR (funziona come prima) //
		switch (lOperator)
		{
		case OPER_AND:
		case OPER_AND_SPEC:
		{
			CString strTableNew;
			if (lOperator == OPER_AND_SPEC)
				strTableNew = strTable; // non considero il parametro lTable //
			else
				strTableNew.Format("%s%02li", strTable, lTable);

			// preparo il FROM //

			if (pStrFrom->Find(" " + strTableNew + " ") == -1)
			{
				CString strFrom;
				strFrom.Format("LEFT OUTER JOIN %s %s ON EEsami.Contatore=%s.%s ", strTable, strTableNew, strTableNew, strJoinField);
				(*pStrFrom) += strFrom;
			}

			// preparo il WHERE //

			if (!pStrWhere->IsEmpty())
				(*pStrWhere) += (" " + strOperators[OPER_AND] + " ");

			CString strWhere;
			switch (lMode)
			{
			case MODE_UGUALE:
			{
				if (bMakeUpper)
					(*pStrWhere) += ("UPPER(" + strTableNew + "." + strWhereField + ")='" + strValue + "'" + " AND " + strTableNew + ".eliminato=0");
				else
					(*pStrWhere) += (strTableNew + "." + strWhereField + "='" + strValue + "'" + " AND " + strTableNew + ".eliminato=0");
				break;
			}
			case MODE_LIKE0:
			{
				if (bMakeUpper)
					(*pStrWhere) += ("UPPER(" + strTableNew + "." + strWhereField + ") LIKE '" + strValue + "'" + " AND " + strTableNew + ".eliminato=0");
				else
					(*pStrWhere) += (strTableNew + "." + strWhereField + " LIKE '" + strValue + "'" + " AND " + strTableNew + ".eliminato=0");
				break;
			}
			case MODE_LIKE1:
			{
				if (bMakeUpper)
					(*pStrWhere) += ("UPPER(" + strTableNew + "." + strWhereField + ") LIKE '" + strValue + "%'" + " AND " + strTableNew + ".eliminato=0");
				else
					(*pStrWhere) += (strTableNew + "." + strWhereField + " LIKE '" + strValue + "%'" + " AND " + strTableNew + ".eliminato=0");
				break;
			}
			case MODE_LIKE2:
			{
				if (bMakeUpper)
					(*pStrWhere) += ("UPPER(" + strTableNew + "." + strWhereField + ") LIKE '%" + strValue + "%'" + " AND " + strTableNew + ".eliminato=0");
				else
					(*pStrWhere) += (strTableNew + "." + strWhereField + " LIKE '%" + strValue + "%'" + " AND " + strTableNew + ".eliminato=0");
				break;
			}
			default:
			{
				ASSERT(FALSE);
				break;
			}
			}

			break;
		}
		case OPER_OR:
		case OPER_OR_SPEC:
		{
			CString strTableNew;
			if (lOperator == OPER_OR_SPEC)
				strTableNew.Format("%s%02li", strTable, lTable); // considero il parametro lTable //
			else
				strTableNew = strTable;

			// preparo il FROM //

			if (pStrFrom->Find(" " + strTableNew + " ") == -1)
			{
				CString strFrom;
				strFrom.Format("LEFT OUTER JOIN %s %s ON EEsami.Contatore=%s.%s ", strTable, strTableNew, strTableNew, strJoinField);
				(*pStrFrom) += strFrom;
			}

			// preparo il WHERE //

			if (!pStrWhere->IsEmpty())
				(*pStrWhere) += (" " + strOperators[OPER_OR] + " ");

			switch (lMode)
			{
			case MODE_UGUALE:
			{
				if (bMakeUpper)
					(*pStrWhere) += ("UPPER(" + strTableNew + "." + strWhereField + ")='" + strValue + "'" + " AND " + strTableNew + ".eliminato=0");
				else
					(*pStrWhere) += (strTableNew + "." + strWhereField + "='" + strValue + "'" + " AND " + strTableNew + ".eliminato=0");
				break;
			}
			case MODE_LIKE0:
			{
				if (bMakeUpper)
					(*pStrWhere) += ("UPPER(" + strTableNew + "." + strWhereField + ") LIKE '" + strValue + "'" + " AND " + strTableNew + ".eliminato=0");
				else
					(*pStrWhere) += (strTableNew + "." + strWhereField + " LIKE '" + strValue + "'" + " AND " + strTableNew + ".eliminato=0");
				break;
			}
			case MODE_LIKE1:
			{
				if (bMakeUpper)
					(*pStrWhere) += ("UPPER(" + strTableNew + "." + strWhereField + ") LIKE '" + strValue + "%'" + " AND " + strTableNew + ".eliminato=0");
				else
					(*pStrWhere) += (strTableNew + "." + strWhereField + " LIKE '" + strValue + "%'" + " AND " + strTableNew + ".eliminato=0");
				break;
			}
			case MODE_LIKE2:
			{
				if (bMakeUpper)
					(*pStrWhere) += ("UPPER(" + strTableNew + "." + strWhereField + ") LIKE '%" + strValue + "%'" + " AND " + strTableNew + ".eliminato=0");
				else
					(*pStrWhere) += (strTableNew + "." + strWhereField + " LIKE '%" + strValue + "%'" + " AND " + strTableNew + ".eliminato=0");
				break;
			}
			default:
			{
				ASSERT(FALSE);
				break;
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
// <-- Sandro 15/04/2009 //

BOOL MakeStringText(CString &strText, CString strLabel, CString strSeparator)
{
	strText += strLabel + strSeparator;

	return TRUE;
}

BOOL MakeStringText(CString &strText, CBaseSet* pSet, short* pCampo, CString strLabel, CString strSeparator)
{
	if (!pSet->IsFieldNull(pCampo))
	{
		if (strLabel != "")
			strText += strLabel;

		CString strBuffer;

		strBuffer.Format("%i", *pCampo);

		strText += strBuffer + strSeparator;

		return TRUE;
	}
	return FALSE;
}

BOOL MakeStringText(CString &strText, CBaseSet* pSet, long* pCampo, CString strLabel, CString strSeparator)
{
	if (!pSet->IsFieldNull(pCampo))
	{
		if (strLabel != "")
			strText += strLabel;

		CString strBuffer;

		strBuffer.Format("%li", *pCampo);

		strText += strBuffer + strSeparator;

		return TRUE;
	}
	return FALSE;
}

BOOL MakeStringText(CString &strText, CBaseSet* pSet, float* pCampo, CString strLabel, CString strSeparator)
{
	if (!pSet->IsFieldNull(pCampo))
	{
		if (strLabel != "")
			strText += strLabel;

		CString strBuffer;

		strBuffer.Format("%f", *pCampo);

		strText += strBuffer + strSeparator;

		return TRUE;
	}
	return FALSE;
}

BOOL MakeStringText(CString &strText, CBaseSet* pSet, CString* pCampo, CString strLabel, CString strSeparator)
{
	if (!pSet->IsFieldNull(pCampo) && !pCampo->IsEmpty())
	{
		if (strLabel != "")
			strText += strLabel;

		strText += pCampo->Left(255) + strSeparator;

		return TRUE;
	}
	return FALSE;
}

BOOL MakeStringTextTrento(CString &strText, CString strCampo, CString strLabel, CString strSeparator)
{
	if (!strCampo.IsEmpty())
	{
		if (strLabel != "")
			strText += strLabel;

		strText += strCampo.Left(255) + strSeparator;

		return TRUE;
	}
	return FALSE;
}

BOOL MakeStringDate(CString &strText, CBaseSet* pSet, long* pCampo, CString strLabel, CString strSeparator)
{
	if (!pSet->IsFieldNull(pCampo))
	{
		if ((*pCampo) > 0)
		{
			if (strLabel != "")
				strText += strLabel;

			if (*pCampo)
			{
				CCustomDate temp;

				temp.SetDate(*pCampo);
				strText += temp.GetDate("%d/%m/%Y"); // Sandro 16/07/2003				
			}

			strText += strSeparator;

			return TRUE;
		}
	}

	return FALSE;
}

BOOL MakeStringMedico(CString &strText, CBaseSet* pSet, long* pCampo, CString strLabel, CString strSeparator)
{
	if (!pSet->IsFieldNull(pCampo))
	{
		if (strLabel != "")
			strText += strLabel;

		CString sFilter;
		sFilter.Format("Contatore=%li", *pCampo);

		CMediciSet setMed;
		setMed.SetOpenFilter(sFilter);
		if (setMed.OpenRecordset("MakeStringMedico"))
		{
			if (!setMed.IsEOF())
				strText += setMed.m_sTitolo + " " + setMed.m_sNome + " " + setMed.m_sCognome;

			setMed.CloseRecordset("MakeStringMedico");
		}

		strText += strSeparator;

		return TRUE;
	}
	return FALSE;
}

BOOL MakeStringInfermiere(CString &strText, CBaseSet* pSet, long* pCampo, CString strLabel, CString strSeparator)
{
	if (!pSet->IsFieldNull(pCampo))
	{
		if (strLabel != "")
			strText += strLabel;

		CString sFilter;
		sFilter.Format("Contatore=%li", *pCampo);

		CInfermieriSet setInf;
		setInf.SetOpenFilter(sFilter);
		if (setInf.OpenRecordset("MakeStringInfermiere"))
		{
			if (!setInf.IsEOF())
				strText += setInf.m_sTitolo + " " + setInf.m_sNome + " " + setInf.m_sCognome;

			setInf.CloseRecordset("MakeStringInfermiere");
		}

		strText += strSeparator;

		return TRUE;
	}
	return FALSE;
}

BOOL MakeStringInviatoDa(CString &strText, CBaseSet* pSet, long* pCampo, CString strLabel, CString strSeparator, long lProvenienza)
{
	if (!pSet->IsFieldNull(pCampo))
	{
		if (strLabel != "")
			strText += strLabel;

		CString sFilter;
		sFilter.Format("Contatore=%li", *pCampo);

		CInviantiSet setInv;
		setInv.SetOpenFilter(sFilter);

		switch (lProvenienza)
		{
		case INTERNO:
		{
			setInv.SetTableName("EInviantiInterni");
			break;
		}
		case ESTERNO:
		{
			setInv.SetTableName("EInviantiEsterni");
			break;
		}
		default:
		{
			ASSERT(FALSE);
			break;
		}
		}

		if (setInv.OpenRecordset("MakeStringInviatoDa"))
		{
			if (!setInv.IsEOF())
				strText += setInv.m_sDescrizione;

			setInv.CloseRecordset("MakeStringInviatoDa");
		}

		strText += strSeparator;

		return TRUE;
	}
	return FALSE;
}

BOOL MakeStringOrgano(CString &strText, CBaseSet* pSet, long* pCampo, CString strLabel, CString strSeparator)
{
	if (!pSet->IsFieldNull(pCampo))
	{
		if (strLabel != "")
			strText += strLabel;

		CString sFilter;
		sFilter.Format("Contatore=%li", *pCampo);

		CMstOrganoSet setOrg;
		setOrg.SetOpenFilter(sFilter);
		if (setOrg.OpenRecordset("MakeStringOrgano"))
		{
			if (!setOrg.IsEOF())
				strText += setOrg.m_sOrgano;

			setOrg.CloseRecordset("MakeStringOrgano");
		}

		strText += strSeparator;

		return TRUE;
	}
	return FALSE;
}

BOOL MakeStringProvenienza(CString &strText, CBaseSet* pSet, long* pCampo, CString strLabel, CString strSeparator)
{
	if (!pSet->IsFieldNull(pCampo))
	{
		if (strLabel != "")
			strText += strLabel;

		switch (*pCampo)
		{
		case INTERNO:
			strText += "Interno";
			break;

		case ESTERNO:
			strText += "Esterno";
			break;
		}

		strText += strSeparator;

		return TRUE;
	}
	return FALSE;
}

BOOL MakeStringSesso(CString &strText, CBaseSet* pSet, long* pCampo, CString strLabel, CString strSeparator)
{
	if (!pSet->IsFieldNull(pCampo))
	{
		if (strLabel != "")
			strText += strLabel;

		switch (*pCampo)
		{
		case 0:
		{
			strText += theApp.GetMessageString(IDS_PAZIENTIDLG_MALE);
			break;
		}
		case 1:
		{
			strText += theApp.GetMessageString(IDS_PAZIENTIDLG_FEMALE);
			break;
		}
		default:
		{
			strText += theApp.GetMessageString(IDS_PAZIENTIDLG_ND);
			break;
		}
		}

		strText += strSeparator;

		return TRUE;
	}

	return FALSE;
}

BOOL MakeStringIdEsame(CString &strText, CBaseSet* pSet, long* pCampo, CString strLabel, CString strSeparator)
{
	if (!pSet->IsFieldNull(pCampo))
	{
		CString strTemp;
		CTipoEsameSet setTemp;

		if (strLabel != "")
			strText += strLabel;

		strTemp.Format("Contatore=%li", *pCampo);
		setTemp.SetOpenFilter(strTemp);
		setTemp.OpenRecordset("Tipo esame");
		if (setTemp.IsEOF() == FALSE)
			strText += setTemp.m_sDescrizione;
		setTemp.CloseRecordset("Tipo esame");

		strText += strSeparator;

		return TRUE;
	}
	return FALSE;
}

void CancellaFile(const CString &strFileFind,
	const CString &strExt,
	const CString &strPath)
{
	WIN32_FIND_DATA findData;
	CString strFileFindExt(strFileFind + strExt);

	HANDLE hFind = FindFirstFile(strFileFindExt, &findData);

	if (hFind != NULL && hFind != INVALID_HANDLE_VALUE) {
		do {
			CString strFileFound;
			CString strFileName;

			strFileFound = CString(findData.cFileName);

			if (strFileFound != "." && strFileFound != "..") {
				if (strExt == ".*" || strExt == "") {
					strFileName = strPath + "\\" + strFileFound;

					remove(strFileName);
				}
				else {
					strFileFound = strFileFound.Left(strFileFound.GetLength() - 4);
					strFileName = strPath + "\\" + strFileFound;

					remove(strFileName + strExt);
				}
			}
		} while (FindNextFile(hFind, &findData));

		FindClose(hFind);
	}
}

/*
BOOL ConvertiImmagine(CString strMiniatureFileName, CString strPictureFileName, double dFactor, L_INT iFormat, L_INT iQuality)
{
BOOL bReturnValue = FALSE;
L_CHAR szMiniatureFileName[_MAX_PATH];
FILEINFO fiPicture;

lstrcpy((LPTSTR)((LPCTSTR)strPictureFileName), (LPTSTR)((LPCTSTR)strPictureFileName));

lstrcpy(szMiniatureFileName, (LPTSTR)((LPCTSTR)strMiniatureFileName));

if (L_FileInfo((LPTSTR)((LPCTSTR)strPictureFileName), &fiPicture) == SUCCESS)
{
BITMAPHANDLE hLeadBitmap;

if (L_LoadFile((LPTSTR)((LPCTSTR)strPictureFileName), &hLeadBitmap, fiPicture.BitsPerPixel, ORDER_BGR, LOADFILE_ALLOCATE | LOADFILE_STORE, NULL, NULL) == SUCCESS)
{
//CString strComment;
CString strTemp;

//LT_GetComment(strPictureFileName);
//if (strPictureFileName.IsEmpty() == FALSE)
//	SC_GetTgaDescription(strPictureFileName, strComment);

//LT_SetComment(strComment);

if (L_SizeBitmap(&hLeadBitmap, (L_INT)((double)fiPicture.Width  * dFactor), (L_INT)((double)fiPicture.Height * dFactor), SIZE_NORMAL) == SUCCESS)
{
L_INT iBitsPerPixel = hLeadBitmap.BitsPerPixel;

if (iBitsPerPixel == 8)
if (!L_IsGrayScaleBitmap(&hLeadBitmap))
iBitsPerPixel = 24;

if (L_SaveFile(szMiniatureFileName, &hLeadBitmap, iFormat, iBitsPerPixel, iQuality, (iBitsPerPixel <= 4) ? SAVEFILE_FIXEDPALETTE : SAVEFILE_OPTIMIZEDPALETTE, NULL, NULL) == SUCCESS)
bReturnValue = TRUE;
}

L_FreeBitmap(&hLeadBitmap);
}
}

return bReturnValue;
}
*/

// Sandro 02/09/2003
CString GetPrivateProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszDefault, LPCTSTR lpszFileName)
{
	char szBuffer[513];

	GetPrivateProfileString(lpszSection, lpszEntry, lpszDefault, szBuffer, 512, lpszFileName);

	return CString(szBuffer);
}

// Sandro 03/09/2003
BOOL WritePrivateProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue, LPCTSTR lpszFileName)
{
	char szBuffer[513];

	sprintf_s(szBuffer, "%d", nValue);

	return WritePrivateProfileString(lpszSection, lpszEntry, szBuffer, lpszFileName);
}

/*
// Sandro 29/09/2003
typedef HRESULT (WINAPI *LPENABLETHEMEDIALOGBACKGROUND)(HWND, DWORD);

// Sandro 29/09/2003
BOOL EnableDialogXPBackground(HWND hWnd)
{
LPENABLETHEMEDIALOGBACKGROUND ProcAdd;
HINSTANCE hModule = LoadLibrary("uxtheme.dll");
BOOL fRunTimeLinkSuccess;

if (hModule != NULL)
{
ProcAdd = (LPENABLETHEMEDIALOGBACKGROUND)GetProcAddress(hModule, "EnableThemeDialogTexture");

if (fRunTimeLinkSuccess = (ProcAdd != NULL))
(ProcAdd)(hWnd, ETDT_ENABLETAB);

FreeLibrary(hModule);
}

return fRunTimeLinkSuccess;
}

// Sandro 29/09/2003
BOOL DisableDialogXPBackground(HWND hWnd)
{
LPENABLETHEMEDIALOGBACKGROUND ProcAdd;
HINSTANCE hModule = LoadLibrary("uxtheme.dll");
BOOL fRunTimeLinkSuccess;

if (hModule != NULL)
{
ProcAdd = (LPENABLETHEMEDIALOGBACKGROUND)GetProcAddress(hModule, "EnableThemeDialogTexture");

if (fRunTimeLinkSuccess = (ProcAdd != NULL))
(ProcAdd)(hWnd, ETDT_DISABLE);

FreeLibrary(hModule);
}

return fRunTimeLinkSuccess;

}
*/

BOOL EsisteContatore(long lCode)
{
	BOOL bReturn = FALSE;

	CString strTemp;
	strTemp.Format("Contatore=%li", lCode);

	CPazientiSet setTemp;

	setTemp.SetOpenFilter(strTemp);
	setTemp.SetSortRecord("Contatore");
	if (setTemp.OpenRecordset("EsisteContatore"))
	{
		bReturn = !setTemp.IsEOF();
		setTemp.CloseRecordset("EsisteContatore");
	}

	return bReturn;
}

BOOL PazienteSetFind(CPazientiSet *pSet, long lCode)
{
	BOOL bResult = FALSE;

	AfxGetApp()->BeginWaitCursor();
	if (EsisteContatore(lCode))
	{
		try
		{
			/* if (theApp.m_bPazientiUsaVista) // ordinato per dataultimoesame //
			{
			CString strQuery;
			strQuery.Format("SELECT COUNT(*) AS CONTEGGIO FROM %s WHERE DATAULTIMOESAME<=(SELECT DATAULTIMOESAME FROM %s WHERE CONTATORE=%li)", theApp.m_sPazientiTabella, theApp.m_sPazientiTabella, lCode);

			CRecordset setCount(&theApp.m_dbEndox); // non mi interessa tanto è per il conteggio //

			DWORD timeOpen = timeGetTime();
			setCount.Open(CRecordset::snapshot, strQuery, CRecordset::readOnly);

			if (theApp.m_bSaveCompleteLog)
			CLogFileWriter::Get()->WriteLogLine0_DB(timeGetTime() - timeOpen, strQuery, "PazienteSetFind");

			if (theApp.m_pShowDbQueriesWnd != NULL)
			theApp.m_pShowDbQueriesWnd->WriteLine(timeGetTime() - timeOpen, strQuery, "PazienteSetFind");

			if (!setCount.IsEOF())
			{
			CDBVariant dbVariant;
			setCount.GetFieldValue("CONTEGGIO", dbVariant, SQL_C_SLONG);

			DWORD timeOpen = timeGetTime();
			pSet->SetAbsolutePosition(dbVariant.m_lVal);

			if (theApp.m_bSaveCompleteLog)
			CLogFileWriter::Get()->WriteLogLine0_DB(timeGetTime() - timeOpen, "pSet->SetAbsolutePosition", "PazienteSetFind");

			if (theApp.m_pShowDbQueriesWnd != NULL)
			theApp.m_pShowDbQueriesWnd->WriteLine(timeGetTime() - timeOpen, "pSet->SetAbsolutePosition", "PazienteSetFind");

			if (pSet->IsEOF())
			pSet->MoveLast();

			pSet->SetFastSearch(TRUE);

			while(pSet->m_lContatore != lCode)
			{
			pSet->MovePrev();

			if (pSet->IsBOF())
			{
			pSet->MoveFirst();
			break;
			}
			}

			pSet->SetFastSearch(FALSE);
			}
			}
			else // ordinato per contatore paziente //
			{
			*/
			CString strQuery;
			strQuery.Format("SELECT COUNT(*) AS CONTEGGIO FROM %s WHERE CONTATORE<=%li AND ELIMINATO=0", theApp.m_sPazientiTabella, lCode); // Sandro 18/10/2010 //

			CRecordset setCount(&theApp.m_dbEndox);

			DWORD timeOpen = timeGetTime();
			setCount.Open(CRecordset::snapshot, strQuery, CRecordset::readOnly);

			if (theApp.m_bSaveCompleteLog)
				CLogFileWriter::Get()->WriteLogLine0_DB(timeGetTime() - timeOpen, strQuery, "PazienteSetFind");

			if (theApp.m_pShowDbQueriesWnd != NULL)
				theApp.m_pShowDbQueriesWnd->WriteLine(timeGetTime() - timeOpen, strQuery, "PazienteSetFind");

			if (!setCount.IsEOF())
			{
				CDBVariant dbVariant;
				setCount.GetFieldValue("CONTEGGIO", dbVariant, SQL_C_SLONG);

				DWORD timeOpen = timeGetTime();
				pSet->SetAbsolutePosition(dbVariant.m_lVal);

				if (theApp.m_bSaveCompleteLog)
					CLogFileWriter::Get()->WriteLogLine0_DB(timeGetTime() - timeOpen, "pSet->SetAbsolutePosition", "PazienteSetFind");

				if (theApp.m_pShowDbQueriesWnd != NULL)
					theApp.m_pShowDbQueriesWnd->WriteLine(timeGetTime() - timeOpen, "pSet->SetAbsolutePosition", "PazienteSetFind");

				if (pSet->IsEOF())
					pSet->MoveLast();

				pSet->SetFastSearch(TRUE);

				while (pSet->m_lContatore > lCode)
				{
					pSet->MovePrev();

					if (pSet->IsBOF())
					{
						pSet->MoveFirst();
						break;
					}
				}

				pSet->SetFastSearch(FALSE);
			}
			// }
		}
		catch (CDBException *e)
		{
			pSet->SetFastSearch(FALSE);

			e->ReportError();
			e->Delete();
		}
	}
	AfxGetApp()->EndWaitCursor();

	if (pSet->m_lContatore == lCode)
		bResult = TRUE;

	return bResult;
}

// Sandro 02/08/2012 // cancella il file originale SOLO se quello di destinazione è uguale, quindi SOLO se è sicuro che la copia sia perfetta //
BOOL DeleteFileSecure(const CString& sFileToDelete, const CString& sFileToCompare)
{
	BOOL bReturn = FALSE;

	HANDLE hFile1 = ::CreateFile(sFileToDelete,
		FILE_READ_DATA,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	HANDLE hFile2 = ::CreateFile(sFileToCompare,
		FILE_READ_DATA,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if ((hFile1 != INVALID_HANDLE_VALUE) && (hFile2 != INVALID_HANDLE_VALUE))
		bReturn = TRUE;

	if (hFile1 != INVALID_HANDLE_VALUE)
		CloseHandle(hFile1);

	if (hFile2 != INVALID_HANDLE_VALUE)
		CloseHandle(hFile2);

	if (bReturn)
		if (_access(sFileToDelete, 06) == 0) //verifico se tenho permissao para modificar o arquivo
		DeleteFile(sFileToDelete);

	return bReturn;
}

// Funzione per cancellare un'intera directory (incluse le sue sottodirectory) //
BOOL DeleteDirectory(CString strPath)
{
	CFileFind finder;
	CString strWildCard, strError, strErrorDesc;
	BOOL bFound, bWorking;

	strWildCard = strPath + "\\*.*";
	bWorking = finder.FindFile(strWildCard);

	bFound = bWorking;
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDots())
			continue;
		if (finder.IsDirectory())
		{
			CString strTemp = strPath + "\\" + finder.GetFileName();
			DeleteDirectory(strTemp);
			continue;
		}

		CString strFile = strPath + "\\" + finder.GetFileName();
		SetFileAttributes(strFile, FILE_ATTRIBUTE_NORMAL);
		DeleteFile(strFile);
	}

	finder.Close();
	RemoveDirectory(strPath);

	return bFound;
}

// Funcao para cancelar todos os arquivos dentro de um diretorio //
BOOL DeleteAllFilesOnDirectory(CString strPath)
{
	Sleep(5000);

	CFileFind finder;
	CString strWildCard, strError, strErrorDesc;
	BOOL bFound, bWorking;

	strWildCard = strPath + "\\*.*";
	bWorking = finder.FindFile(strWildCard);

	bFound = bWorking;
	CString strFile;
	while (bWorking)
	{
		try
		{
			bWorking = finder.FindNextFile();
			if (finder.IsDots())
				continue;
			if (finder.IsDirectory())
				continue;

			strFile = strPath + "\\" + finder.GetFileName();
			if (_access(strFile, 06) == 0)
			{
			SetFileAttributes(strFile, FILE_ATTRIBUTE_NORMAL);
			DeleteFile(strFile);
		}
		}
		catch (CException* e) //em caso de excecao
		{
			TCHAR szError[255];
			e->GetErrorMessage(szError, 255); //coloco o erro em uma variavel
			e->Delete(); //deleto o erro

			CString strLog = "";
			strLog.Format("ERRO NA TENTATIVA DE DELETAR O ARQUIVO: %s (Exception: %s)", strFile, szError);

			CLogFileWriter::Get()->WriteLogLine0(strLog);
		}
	}

	finder.Close();

	return bFound;
}

// Funzione per cancellare un'intera directory (senza le sue sottodirectory) //
BOOL DeleteDirectoryNoSub(CString strPath)
{
	CFileFind finder;
	CString strWildCard, strError, strErrorDesc;
	BOOL bFound, bWorking;

	strWildCard = strPath + "\\*.*";
	bWorking = finder.FindFile(strWildCard);

	bFound = bWorking;
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDots())
			continue;

		CString strFile = strPath + "\\" + finder.GetFileName();
		SetFileAttributes(strFile, FILE_ATTRIBUTE_NORMAL);
		DeleteFile(strFile);
	}

	finder.Close();
	RemoveDirectory(strPath);

	return bFound;
}

// Funzione per cancellare un'intera directory (incluse le sue sottodirectory) //
BOOL DeleteDirectoryProgress(CString strPath, CProgressCtrl &ctrlProgress)
{
	CFileFind finder;
	CString strWildCard, strError, strErrorDesc;
	BOOL bFound, bWorking;

	strWildCard = strPath + "\\*.*";
	bWorking = finder.FindFile(strWildCard);

	bFound = bWorking;
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDots())
			continue;
		if (finder.IsDirectory())
		{
			CString strTemp = strPath + "\\" + finder.GetFileName();
			DeleteDirectoryProgress(strTemp, ctrlProgress);
			continue;
		}

		CString strFile = strPath + "\\" + finder.GetFileName();
		SetFileAttributes(strFile, FILE_ATTRIBUTE_NORMAL);
		DeleteFile(strFile);
		ctrlProgress.SetPos(ctrlProgress.GetPos() + 1);
	}

	finder.Close();
	RemoveDirectory(strPath);

	return bFound;
}

BOOL VerificaPercorso(CString strPath, BOOL bVerbose)
{
	// verifica se esiste un dato percorso e se non lo trova tenta di crearlo //

	// Sandro 13/03/2013 // modifico per funzionare anche su un percorso di rete //
	BOOL bSaltaPrimoLivello = FALSE;
	if (strPath.Left(1) == "\\")
		bSaltaPrimoLivello = TRUE;

	//
	if (strPath.Right(1) != "\\")
		strPath += "\\";

	if (_access(strPath, 06) == -1)
	{
		if (errno == ENOENT) // percorso non trovato, lo creo //
		{
			int iTemp = strPath.Find('\\', 3);

			while (iTemp > 0)
			{
				if (bSaltaPrimoLivello)
				{
					bSaltaPrimoLivello = FALSE;
				}
				else
				{
					if (_mkdir(strPath.Left(iTemp)) == -1)
					{
						if (errno != EEXIST)
						{
							if (bVerbose)
							{
								CString strMessage;
								strMessage.Format(theApp.GetMessageString(IDS_INACCESSIBLE_PATH), strPath);
								theApp.AfxMessageBoxEndo(strMessage);
							}
							return FALSE;
						}
					}
				}

				iTemp = strPath.Find('\\', iTemp + 1);
			}

			return(_access(strPath, 06) == 0);
		}
		else
		{
			if (bVerbose)
			{
				CString strMessage;
				strMessage.Format(theApp.GetMessageString(IDS_READONLY_PATH), strPath);
				theApp.AfxMessageBoxEndo(strMessage);
			}
			return FALSE;
		}
	}

	return TRUE;
}

BOOL VerificaPercorsoSistemaEndox(CString strPath)
{
	// verifica se il percorso esiste e se si riesce a scriverci dentro - usato all'avvio del software //

	BOOL bReturn = TRUE;

	// Sandro 05/04/2017 // perché se non esiste non provare a crearlo, prima?!? //
	VerificaPercorso(strPath, FALSE);

	//
	strPath.MakeUpper();
	if (_access(strPath, 06) == 0)
	{
		// il percorso esiste, vedo se riesco a scriverci //

		CString strFile;
		if (strPath.Right(1).Compare("\\") == 0)
			strFile = strPath + "provascrittura.ti";
		else
			strFile = strPath + "\\provascrittura.ti";

		HANDLE hFile = CreateFile(strFile, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
		{
			// file creato correttamente //

			CloseHandle(hFile);

			if (!DeleteFile(strFile))
			{
				CString strError;
				strError.Format(theApp.GetMessageString(IDS_PERCORSO_DELETE), strPath);
				theApp.AfxMessageBoxEndo(strError, MB_ICONEXCLAMATION);
			}
		}
		else
		{
			// l'utente corrente non ha i diritti per scrivere nel percorso //

			bReturn = FALSE;

			CString strError;
			strError.Format(theApp.GetMessageString(IDS_PERCORSO_RIGHTS), strPath);
			theApp.AfxMessageBoxEndo(strError, MB_ICONSTOP);
		}
	}
	else
	{
		bReturn = FALSE;

		switch (errno)
		{
		case ENOENT:
		{
			// non esiste //

			CString strError;
			strError.Format(theApp.GetMessageString(IDS_PERCORSO_ENOENT), strPath);
			theApp.AfxMessageBoxEndo(strError, MB_ICONSTOP);

			break;
		}
		case EACCES:
		{
			// esiste ma è in sola lettura //

			CString strError;
			strError.Format(theApp.GetMessageString(IDS_PERCORSO_EACCES), strPath);
			theApp.AfxMessageBoxEndo(strError, MB_ICONSTOP);

			break;
		}
		default:
		{
			// booooh //

			CString strError;
			strError.Format(theApp.GetMessageString(IDS_PERCORSO_BOOOOH), strPath);
			theApp.AfxMessageBoxEndo(strError, MB_ICONSTOP);

			break;
		}
		}
	}

	return bReturn;
}

BOOL VerificaPercorsoSpazioLibero(CString strPath)
{
	// verifica lo spazio libero nel percorso //

	BOOL bReturn = TRUE;

#ifdef _DEBUG
	// em modo _DEBUG faz bypass dessa verificação
	return TRUE;
#endif

	strPath.MakeUpper();

	ULARGE_INTEGER uFreeBytesAvailable;
	ULARGE_INTEGER uTotalNumberOfBytes;
	ULARGE_INTEGER uTotalNumberOfFreeBytes;
	if (GetDiskFreeSpaceEx(strPath, &uFreeBytesAvailable, &uTotalNumberOfBytes, &uTotalNumberOfFreeBytes))
	{
		double lfGBytesTotal = (double)((uTotalNumberOfBytes.LowPart + ((LONGLONG)uTotalNumberOfBytes.HighPart << 32)) / (double)(1024 * 1024 * 1024));
		double lfGBytesFree = (double)((uFreeBytesAvailable.LowPart + ((LONGLONG)uFreeBytesAvailable.HighPart << 32)) / (double)(1024 * 1024 * 1024));

		int nPercentFree = (int)(lfGBytesFree / lfGBytesTotal * 100.0f);
		if (nPercentFree < theApp.m_nArchivioImmaginiSogliaBlocco) // Sandro 10/05/2013 // modifico così Colonna può avviare Endox anche con lo 0% di spazio libero //
		{
			CString strError;
			strError.Format(theApp.GetMessageString(IDS_PERCORSO_SLERR1), strPath);
			theApp.AfxMessageBoxEndo(strError, MB_ICONSTOP);

			bReturn = FALSE;
		}
		else if (nPercentFree <= theApp.m_nArchivioImmaginiSogliaAvviso)
		{
			CString strError;
			strError.Format(theApp.GetMessageString(IDS_PERCORSO_SLERR2), strPath);
			theApp.AfxMessageBoxEndo(strError, MB_ICONEXCLAMATION);
		}
	}
	else
	{
		CString strError;
		strError.Format(theApp.GetMessageString(IDS_PERCORSO_SLERR3), strPath);
		theApp.AfxMessageBoxEndo(strError, MB_ICONEXCLAMATION);
	}

	return bReturn;
}

long GetIDVersione(long lTipoEsame)
{
	// ritorna l'ID dell'interfaccia operatore da caricare (in base al tipo esame che gli passo e l'utente attualmente loggato in Endox) //

	long lIDVersione = -1;

	CString strFilter;
	strFilter.Format("IDTipoEsame=%li OR IDTipoEsame=0", lTipoEsame);

	CDynVersioneSet setDynVersione;
	setDynVersione.SetBaseFilter("(UO=0 OR UO>0)");
	setDynVersione.SetOpenFilter(strFilter);
	setDynVersione.SetSortRecord("DataOra DESC, ID DESC");
	if (setDynVersione.OpenRecordset("GetIDVersione"))
	{
		if (!setDynVersione.IsEOF())
			lIDVersione = setDynVersione.m_lID;

		setDynVersione.CloseRecordset("GetIDVersione");
	}

	if (lIDVersione < 1)
		lIDVersione = 1;

	return lIDVersione;
}

///
///
///

void ContrastPreview(int l_bin, int h_bin, CDib* pDib, LPLOGPALETTE  pOrgPal, LPLOGPALETTE  pLogPal)
{
	int		 i;
	double	 stepb, stepb_value;

	stepb = 256.0 / (double)(h_bin - l_bin + 1);
	stepb_value = 0.0;

	for (i = 0; i < l_bin; i++)
	{
		pLogPal->palPalEntry[i].peRed = pOrgPal->palPalEntry[0].peRed;
		pLogPal->palPalEntry[i].peGreen = pOrgPal->palPalEntry[0].peGreen;
		pLogPal->palPalEntry[i].peBlue = pOrgPal->palPalEntry[0].peBlue;
	}

	for (i = l_bin; i <= h_bin; i++)
	{
		pLogPal->palPalEntry[i].peRed = pOrgPal->palPalEntry[(BYTE)stepb_value].peRed;
		pLogPal->palPalEntry[i].peGreen = pOrgPal->palPalEntry[(BYTE)stepb_value].peGreen;
		pLogPal->palPalEntry[i].peBlue = pOrgPal->palPalEntry[(BYTE)stepb_value].peBlue;
		stepb_value += stepb;
	}

	for (i = h_bin + 1; i < 256; i++)
	{
		pLogPal->palPalEntry[i].peRed = pOrgPal->palPalEntry[255].peRed;
		pLogPal->palPalEntry[i].peGreen = pOrgPal->palPalEntry[255].peGreen;
		pLogPal->palPalEntry[i].peBlue = pOrgPal->palPalEntry[255].peBlue;
	}

	pDib->CopydaPalette(pLogPal);
}

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
void ContrastPreviewRGB(int BlackLev, int WhiteLev, CDib* pSourceDib, CDib* pDestDib)
{
	int		maxX, maxY, x, y, PaletteSize;
	float	stepb, stepb_value;
	BYTE	Lut[256];
	int		i;

	if (pSourceDib && pDestDib)
	{
		PaletteSize = 256; // tenuto conto che RGB = 3*256
		maxX = pSourceDib->Width();
		maxY = pSourceDib->Height();

		stepb = (float)PaletteSize / (float)(WhiteLev - BlackLev + 1);

		stepb_value = (float)0.0;
		for (i = 0; i < BlackLev; i++)
			Lut[i] = COLOR_BLACK;
		for (i = BlackLev; i < WhiteLev; i++)
		{
			Lut[i] = (BYTE)stepb_value;
			stepb_value += stepb;
		}
		for (i = WhiteLev; i < PaletteSize; i++)
			Lut[i] = COLOR_WHITE;

		for (y = 0; y < maxY; y++)
		{
			BYTE* offsetS = (BYTE*)pSourceDib->m_pVetY[y];
			BYTE* offsetD = (BYTE*)pDestDib->m_pVetY[y];

			for (x = 0; x < maxX; x++)
			{
				*offsetD++ = Lut[*offsetS++];
				*offsetD++ = Lut[*offsetS++];
				*offsetD++ = Lut[*offsetS++];
			}
		}
	}
}

void ContrastPreviewRGB(int MinR, int MaxR, int MinG, int MaxG, int MinB, int MaxB, CDib* pSourceDib, CDib* pDestDib)
{
	int		maxX, maxY, x, y, PaletteSize;
	float	stepb, stepb_value;
	BYTE	LutR[256];
	BYTE	LutG[256];
	BYTE	LutB[256];
	int		i;

	if (pSourceDib && pDestDib)
	{
		PaletteSize = 256; // tenuto conto che RGB = 3*256
		maxX = pSourceDib->Width();
		maxY = pSourceDib->Height();

		//palette del rosso
		stepb = (float)PaletteSize / (float)(MaxR - MinR + 1);
		stepb_value = (float)0.0;
		for (i = 0; i < MinR; i++)
			LutR[i] = COLOR_BLACK;
		for (i = MinR; i < MaxR; i++)
		{
			LutR[i] = (BYTE)stepb_value;
			stepb_value += stepb;
		}
		for (i = MaxR; i < PaletteSize; i++)
			LutR[i] = COLOR_WHITE;

		//palette del verde
		stepb = (float)PaletteSize / (float)(MaxG - MinG + 1);
		stepb_value = (float)0.0;
		for (i = 0; i < MinG; i++)
			LutG[i] = COLOR_BLACK;
		for (i = MinG; i < MaxG; i++)
		{
			LutG[i] = (BYTE)stepb_value;
			stepb_value += stepb;
		}
		for (i = MaxG; i < PaletteSize; i++)
			LutG[i] = COLOR_WHITE;

		//palette del blu
		stepb = (float)PaletteSize / (float)(MaxB - MinB + 1);
		stepb_value = (float)0.0;
		for (i = 0; i < MinB; i++)
			LutB[i] = COLOR_BLACK;
		for (i = MinB; i < MaxB; i++)
		{
			LutB[i] = (BYTE)stepb_value;
			stepb_value += stepb;
		}
		for (i = MaxB; i < PaletteSize; i++)
			LutB[i] = COLOR_WHITE;

		for (y = 0; y < maxY; y++)
		{
			BYTE* offsetS = (BYTE*)pSourceDib->m_pVetY[y];
			BYTE* offsetD = (BYTE*)pDestDib->m_pVetY[y];

			for (x = 0; x < maxX; x++)
			{
				*offsetD++ = LutB[*offsetS++];
				*offsetD++ = LutG[*offsetS++];
				*offsetD++ = LutR[*offsetS++];
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////
void DoContrast(int l_bin, int h_bin, CRect rect, CDib* pDibSorg, CDib* pDibDest, CDib* pDibRoi)
{
	double	stepb_value, stepb;
	int		tranb[256];
	int		i, x, y;

	CRect	rectMax(0, 0, pDibDest->Width() - 1, pDibDest->Height() - 1);

	rect &= rectMax;

	stepb = 256.0 / (double)(h_bin - l_bin + 1);
	stepb_value = 0.0;

	for (i = 0; i < l_bin; i++)
		tranb[i] = 0;
	for (i = l_bin; i <= h_bin; i++)
	{
		tranb[i] = (BYTE)stepb_value;
		stepb_value += stepb;
	}
	for (i = h_bin + 1; i < 256; i++)
		tranb[i] = 255;

	if (pDibRoi)
	{
		for (y = rect.top; y < rect.bottom; y++)
		{
			BYTE* offsetRoi = (BYTE*)pDibRoi->m_pVetY[y] + rect.left;
			BYTE* offsetOld = (BYTE*)pDibSorg->m_pVetY[y] + rect.left;
			BYTE* offsetDib = (BYTE*)pDibDest->m_pVetY[y] + rect.left;

			for (x = rect.left; x < rect.right; x++)
			{
				if (!(*offsetRoi++))
				{
					*offsetDib = tranb[*offsetOld];
				}
				offsetDib++;
				offsetOld++;
			}
		}
	}
	else
	{
		for (y = rect.top; y < rect.bottom; y++)
		{
			BYTE* offsetOld = (BYTE*)pDibSorg->m_pVetY[y] + rect.left;
			BYTE* offsetDib = (BYTE*)pDibDest->m_pVetY[y] + rect.left;

			for (x = rect.left; x < rect.right; x++)
			{
				*offsetDib++ = tranb[*offsetOld++];
			}
		}
	}
}

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
void DoContrastRGB(int BlackLev, int WhiteLev, CRect rect, CDib* pDibSorg, CDib* pDibDest, CDib* pDibRoi)
{
	int		x, y;
	int		i;
	float	stepb, stepb_value;
	int		PaletteSize = 256;
	BYTE	Lut[256];

	CRect	rectMax(0, 0, pDibDest->Width() - 1, pDibDest->Height() - 1);

	rect &= rectMax;

	stepb = (float)PaletteSize / (float)(WhiteLev - BlackLev + 1);

	stepb_value = (float)0.0;
	for (i = 0; i < BlackLev; i++)
		Lut[i] = COLOR_BLACK;
	for (i = BlackLev; i < WhiteLev; i++)
	{
		Lut[i] = (BYTE)stepb_value;
		stepb_value += stepb;
	}
	for (i = WhiteLev; i < PaletteSize; i++)
		Lut[i] = COLOR_WHITE;

	if (pDibRoi)
	{
		for (y = rect.top; y < rect.bottom; y++)
		{
			BYTE* offsetRoi = (BYTE*)pDibRoi->m_pVetY[y] + rect.left;
			BYTE* offsetOld = (BYTE*)pDibSorg->m_pVetY[y] + rect.left * 3;
			BYTE* offsetDib = (BYTE*)pDibDest->m_pVetY[y] + rect.left * 3;

			for (x = rect.left; x < rect.right; x++)
			{
				if (!(*offsetRoi++))
				{
					*offsetDib++ = Lut[*offsetOld++];
					*offsetDib++ = Lut[*offsetOld++];
					*offsetDib++ = Lut[*offsetOld++];
				}
				else
				{
					offsetOld += 3;
					offsetDib += 3;
				}
			}
		}
	}
	else
	{
		for (y = rect.top; y < rect.bottom; y++)
		{
			BYTE* offsetOld = (BYTE*)pDibSorg->m_pVetY[y] + rect.left * 3;
			BYTE* offsetDib = (BYTE*)pDibDest->m_pVetY[y] + rect.left * 3;

			for (x = rect.left; x < rect.right; x++)
			{
				*offsetDib++ = Lut[*offsetOld++];
				*offsetDib++ = Lut[*offsetOld++];
				*offsetDib++ = Lut[*offsetOld++];
			}
		}
	}
}

void DoContrastRGB(int MinR, int MaxR, int MinG, int MaxG, int MinB, int MaxB, CRect rect, CDib* pDibSorg, CDib* pDibDest, CDib* pDibRoi)
{
	int		x, y;
	int		i;
	float	stepb, stepb_value;
	int		PaletteSize = 256;
	BYTE	LutR[256];
	BYTE	LutG[256];
	BYTE	LutB[256];

	CRect	rectMax(0, 0, pDibDest->Width() - 1, pDibDest->Height() - 1);

	rect &= rectMax;

	//palette del rosso
	stepb = (float)PaletteSize / (float)(MaxR - MinR + 1);
	stepb_value = (float)0.0;
	for (i = 0; i < MinR; i++)
		LutR[i] = COLOR_BLACK;
	for (i = MinR; i < MaxR; i++)
	{
		LutR[i] = (BYTE)stepb_value;
		stepb_value += stepb;
	}
	for (i = MaxR; i < PaletteSize; i++)
		LutR[i] = COLOR_WHITE;

	//palette del verde
	stepb = (float)PaletteSize / (float)(MaxG - MinG + 1);
	stepb_value = (float)0.0;
	for (i = 0; i < MinG; i++)
		LutG[i] = COLOR_BLACK;
	for (i = MinG; i < MaxG; i++)
	{
		LutG[i] = (BYTE)stepb_value;
		stepb_value += stepb;
	}
	for (i = MaxG; i < PaletteSize; i++)
		LutG[i] = COLOR_WHITE;

	//palette del blu
	stepb = (float)PaletteSize / (float)(MaxB - MinB + 1);
	stepb_value = (float)0.0;
	for (i = 0; i < MinB; i++)
		LutB[i] = COLOR_BLACK;
	for (i = MinB; i < MaxB; i++)
	{
		LutB[i] = (BYTE)stepb_value;
		stepb_value += stepb;
	}
	for (i = MaxB; i < PaletteSize; i++)
		LutB[i] = COLOR_WHITE;

	if (pDibRoi)
	{
		for (y = rect.top; y < rect.bottom; y++)
		{
			BYTE* offsetRoi = (BYTE*)pDibRoi->m_pVetY[y] + rect.left;
			BYTE* offsetOld = (BYTE*)pDibSorg->m_pVetY[y] + rect.left * 3;
			BYTE* offsetDib = (BYTE*)pDibDest->m_pVetY[y] + rect.left * 3;

			for (x = rect.left; x < rect.right; x++)
			{
				if (!(*offsetRoi++))
				{
					*offsetDib++ = LutB[*offsetOld++];
					*offsetDib++ = LutG[*offsetOld++];
					*offsetDib++ = LutR[*offsetOld++];
				}
				else
				{
					offsetOld += 3;
					offsetDib += 3;
				}
			}
		}
	}
	else
	{
		for (y = rect.top; y < rect.bottom; y++)
		{
			BYTE* offsetOld = (BYTE*)pDibSorg->m_pVetY[y] + rect.left * 3;
			BYTE* offsetDib = (BYTE*)pDibDest->m_pVetY[y] + rect.left * 3;

			for (x = rect.left; x < rect.right; x++)
			{
				*offsetDib++ = LutB[*offsetOld++];
				*offsetDib++ = LutG[*offsetOld++];
				*offsetDib++ = LutR[*offsetOld++];
			}
		}
	}
}

void BrightnessPreview(int bin, CDib *pDib, LPLOGPALETTE pOrgPal, LPLOGPALETTE pLogPal)
{
	for (int i = 0; i < 256; i++)
	{
		int index = i + bin;

		if (index < 0)
			index = 0;
		else
			if (index > 255)
				index = 255;

		pLogPal->palPalEntry[i].peRed = pOrgPal->palPalEntry[index].peRed;
		pLogPal->palPalEntry[i].peGreen = pOrgPal->palPalEntry[index].peGreen;
		pLogPal->palPalEntry[i].peBlue = pOrgPal->palPalEntry[index].peBlue;
	}

	pDib->CopydaPalette(pLogPal);
}


void DoBrightness(int bin, CDib *pDibSorg, CDib *pDibDest, CDib *pDibRoi)
{
	CRect rect(0, 0, pDibDest->Width() - 1, pDibDest->Height() - 1);
	int tranb[256];
	int x, y;

	for (int i = 0; i < 256; i++)
	{
		int index = i + bin;

		if (index < 0)
			index = 0;
		else
			if (index > 255)
				index = 255;

		tranb[i] = index;
	}

	if (pDibRoi != NULL) {
		for (y = rect.top; y < rect.bottom; y++)
		{
			BYTE *offsetRoi = (BYTE*)pDibRoi->m_pVetY[y] + rect.left;
			BYTE *offsetOld = (BYTE*)pDibSorg->m_pVetY[y] + rect.left;
			BYTE *offsetDib = (BYTE*)pDibDest->m_pVetY[y] + rect.left;

			for (x = rect.left; x < rect.right; x++)
			{
				if (!(*offsetRoi++))
					*offsetDib = tranb[*offsetOld];
				offsetDib++;
				offsetOld++;
			}
		}
	}
	else
	{
		for (y = rect.top; y < rect.bottom; y++)
		{
			BYTE *offsetOld = (BYTE*)pDibSorg->m_pVetY[y] + rect.left;
			BYTE *offsetDib = (BYTE*)pDibDest->m_pVetY[y] + rect.left;

			for (x = rect.left; x < rect.right; x++)
				*offsetDib++ = tranb[*offsetOld++];
		}
	}
}


void DoBrightnessRGB(int bin, CDib *pDibSorg, CDib *pDibDest, CDib *pDibRoi)
{
	CRect rect(0, 0, pDibDest->Width() - 1, pDibDest->Height() - 1);
	int tranb[256];
	int x, y;

	for (int i = 0; i < 256; i++)
	{
		int index = i + bin;

		if (index < 0)
			index = 0;
		else
			if (index > 255)
				index = 255;

		tranb[i] = index;
	}

	if (pDibRoi != NULL)
	{
		for (y = rect.top; y < rect.bottom; y++)
		{
			BYTE *offsetRoi = (BYTE*)pDibRoi->m_pVetY[y] + rect.left;
			BYTE *offsetOld = (BYTE*)pDibSorg->m_pVetY[y] + rect.left * 3;
			BYTE *offsetDib = (BYTE*)pDibDest->m_pVetY[y] + rect.left * 3;

			for (x = rect.left; x < rect.right; x++)
			{
				if (!(*offsetRoi++))
				{
					*offsetDib++ = tranb[*offsetOld++];
					*offsetDib++ = tranb[*offsetOld++];
					*offsetDib++ = tranb[*offsetOld++];
				}
				else
				{
					offsetDib += 3;
					offsetOld += 3;
				}
			}
		}
	}
	else
	{
		for (y = rect.top; y < rect.bottom; y++)
		{
			BYTE *offsetOld = (BYTE*)pDibSorg->m_pVetY[y] + rect.left * 3;
			BYTE *offsetDib = (BYTE*)pDibDest->m_pVetY[y] + rect.left * 3;

			for (x = rect.left; x < rect.right; x++)
			{
				*offsetDib++ = tranb[*offsetOld++];
				*offsetDib++ = tranb[*offsetOld++];
				*offsetDib++ = tranb[*offsetOld++];
			}
		}
	}
}

#define N_FILTER_SMOOTH 0
#define N_FILTER_SHARPEN2 1

int m_vetFilterInt[2][3][3] =
{
	{ { -1, -1, -1 },
	{ -1, 12, -1 },
	{ -1, -1, -1 } },   // Sharpen 2

	{ { 1, 2, 1 },
	{ 2, 4, 2 },
	{ 1, 2, 1 } }   // Smooth
};

int m_vetGainInt[2] =
{
	4,   // Sharpen 2
	16   // Smooth
};


void Enhance(CDib** pDib)
{
	if (*pDib && (*pDib)->IsValidDib())
	{
		AfxGetApp()->BeginWaitCursor();
		Filter(pDib, N_FILTER_SMOOTH, 1);
		Filter(pDib, N_FILTER_SHARPEN2, 1);
		AfxGetApp()->EndWaitCursor();
	}
}

BOOL Filter(CDib** pDib, int nFilter, int nCicli)
{
	int i = -1;

	if (pDib != NULL)
	{
		int j;
		int numcolors = (*pDib)->NumColors();

		CDib* pDibWork;
		pDibWork = new CDib;
		if (pDibWork)
		{
			*pDibWork = **pDib;

			if (pDibWork->IsValidDib())
			{
				switch (numcolors)
				{
				case 0:
					for (j = 0; j < nCicli; j++)
					{
						i = GenericFilterInt_24bits(*pDib, pDibWork, nFilter);

						ScambiaDib(pDib, &pDibWork);
					}
					break;

				case 256:
					for (j = 0; j < nCicli; j++)
					{
						i = GenericFilterInt_8bits(*pDib, pDibWork, nFilter);

						ScambiaDib(pDib, &pDibWork);
					}
					break;

				default:
					break;
				}

				ScambiaDib(pDib, &pDibWork);
				pDibWork->ReleaseContents();
				delete pDibWork;
			}
		}
	}

	return(i == 0);
}

int GenericFilterInt_8bits(CDib* pDib, CDib* pDibWork, int FilterType)
{
	int y, x;
	BYTE j, z;
	int tmp;
	BYTE mono;

	int xleft = 0;
	int xright = pDib->Width();
	int ytop = 0;
	int ybottom = pDib->Height();

	int dimfilterX = 3;
	int dimfilterY = 3;
	int DimLine = (xright - dimfilterX);
	int NumLine = (ybottom - dimfilterY);

	for (y = ytop; y <= NumLine; y++)
	{
		BYTE* offsetDest = (BYTE*)pDib->m_pVetY[y + dimfilterY / 2] + dimfilterX / 2 + xleft;

		for (x = xleft; x <= DimLine; x++)
		{
			tmp = 0;
			for (j = 0; j < dimfilterY; j++)
			{
				BYTE* offsetSorg = (BYTE*)pDibWork->m_pVetY[y + j] + x;

				for (z = 0; z < dimfilterX; z++)
				{
					mono = *(offsetSorg++);
					tmp += (int)mono * m_vetFilterInt[FilterType][j][z];
				}
			}
			tmp = tmp / m_vetGainInt[FilterType];
			if (tmp > COLOR_WHITE)
				tmp = COLOR_WHITE;
			else
				if (tmp < COLOR_BLACK)
					tmp = COLOR_BLACK;
			mono = (BYTE)tmp;
			*(offsetDest++) = mono;
		}
	}

	return 0;
}

int GenericFilterInt_24bits(CDib* pDib, CDib* pDibWork, int FilterType)
{
	int	y, x;
	BYTE j, z;
	int tmprgb[3];
	BYTE rgb[3];
	BYTE col;

	int xleft = 0;
	int xright = pDib->Width();
	int ytop = 0;
	int ybottom = pDib->Height();

	int dimfilterX = 3;
	int dimfilterY = 3;
	int DimLine = (xright - dimfilterX);
	int NumLine = (ybottom - dimfilterY);

	for (y = ytop; y <= NumLine; y++)
	{
		BYTE* offsetDest = (BYTE*)pDib->m_pVetY[y + dimfilterY / 2] + (long)(dimfilterX / 2 + xleft) * 3;

		for (x = xleft; x <= DimLine; x++)
		{
			tmprgb[0] = 0;
			tmprgb[1] = 0;
			tmprgb[2] = 0;
			for (j = 0; j < dimfilterY; j++)
			{
				BYTE* offsetSorg = (BYTE*)pDibWork->m_pVetY[y + j] + (long)x * 3;

				for (z = 0; z < dimfilterX; z++)
				{
					rgb[2] = *(offsetSorg++);
					rgb[1] = *(offsetSorg++);
					rgb[0] = *(offsetSorg++);

					tmprgb[0] += (int)rgb[0] * m_vetFilterInt[FilterType][j][z];
					tmprgb[1] += (int)rgb[1] * m_vetFilterInt[FilterType][j][z];
					tmprgb[2] += (int)rgb[2] * m_vetFilterInt[FilterType][j][z];
				}
			}
			for (col = 0; col < 3; col++)
			{
				tmprgb[col] = tmprgb[col] / m_vetGainInt[FilterType];
				if (tmprgb[col] > COLOR_WHITE)
					tmprgb[col] = COLOR_WHITE;
				else
					if (tmprgb[col] < COLOR_BLACK)
						tmprgb[col] = COLOR_BLACK;
				rgb[col] = (BYTE)tmprgb[col];
			}
			*(offsetDest++) = rgb[2];
			*(offsetDest++) = rgb[1];
			*(offsetDest++) = rgb[0];
		}
	}

	return 0;
}

void ScambiaDib(CDib** pDibSorg, CDib** pDibDest)
{
	CDib* pDibTemp = *pDibSorg;

	*pDibSorg = *pDibDest;
	*pDibDest = pDibTemp;
}

// Sandro 24/04/2012 //
CString GetStringCampoLiberoDatabase(long lContenuto)
{
	CString strReturn = "";

	if ((lContenuto >= edt_libero000) && (lContenuto <= edt_libero099))
	{
		strReturn.Format(" (%s%03li)", theApp.GetMessageString(IDS_LIBERO_TESTO), lContenuto - edt_libero000);
	}
	else if ((lContenuto >= edt_liberortf000) && (lContenuto <= edt_liberortf019))
	{
		strReturn.Format(" (%s%03li)", theApp.GetMessageString(IDS_LIBERO_TESTORTF), lContenuto - edt_liberortf000);
	}
	else if ((lContenuto >= edt_liberocl000) && (lContenuto <= edt_liberocl019))
	{
		strReturn.Format(" (%s%03li)", theApp.GetMessageString(IDS_LIBERO_TESTOCL), lContenuto - edt_liberocl000);
	}
	else if ((lContenuto >= edt_liberodataora000) && (lContenuto <= edt_liberodataora019))
	{
		strReturn.Format(" (%s%03li)", theApp.GetMessageString(IDS_LIBERO_DATAOTA), lContenuto - edt_liberodataora000);
	}
	else if ((lContenuto >= btn_liberotastostampa000) && (lContenuto <= btn_liberotastostampa019))
	{
		strReturn.Format(" (%s%03li)", theApp.GetMessageString(IDS_LIBERO_TASTOSTAMPA), lContenuto - btn_liberotastostampa000);
	}
	else if ((lContenuto >= btn_liberotastobrowser000) && (lContenuto <= btn_liberotastobrowser019))
	{
		strReturn.Format(" (%s%03li)", theApp.GetMessageString(IDS_LIBERO_TASTOBROWSER), lContenuto - btn_liberotastobrowser000);
	}
	else if ((lContenuto >= btn_liberotastoeseguibile000) && (lContenuto <= btn_liberotastoeseguibile019))
	{
		strReturn.Format(" (%s%03li)", theApp.GetMessageString(IDS_LIBERO_TASTOESEGUIBILE), lContenuto - btn_liberotastoeseguibile000);
	}
	else if ((lContenuto >= sub_etichetta000) && (lContenuto <= sub_etichetta039))
	{
		strReturn.Format(" (%s%03li)", theApp.GetMessageString(IDS_LIBERO_ETICHETTA), lContenuto - sub_etichetta000);
	}
	else if ((lContenuto >= btn_liberotastochiusurafase000) && (lContenuto <= btn_liberotastochiusurafase019))
	{
		strReturn.Format(" (%s%03li)", theApp.GetMessageString(IDS_LIBERO_TASTOCHIUSURAFASE), lContenuto - btn_liberotastochiusurafase000);
	}
	else if ((lContenuto >= sub_gridcl000) && (lContenuto <= sub_gridcl039))
	{
		strReturn.Format(" (%s%03li)", theApp.GetMessageString(IDS_LIBERO_GRIDCL), lContenuto - sub_gridcl000);
	}

	return strReturn;
}

///////////////////////////////////////////////////////
// nuove funzioni per vecchio trasferimento immagini //
///////////////////////////////////////////////////////

int CalcSpaces(CImgManager* pImgManager, CExamIDList* pListExamID, double* pDiskAvaible, double* pSpaceRequired)
{
	int nReturn = ERROR_NOTHING;

	// salvo la directory corrente //
	char szCurDir[256];
	int nCurDrive = _getdrive();
	_getdcwd(nCurDrive, szCurDir, 256);

	// cambio directory //
	_chdir(theApp.m_sPathImageOD);

	// estraggo le informazioni dal disco //
	DWORD lSectorsPerCluster;
	DWORD lBytesPerSector;
	DWORD lNumberOfFreeClusters;
	if (GetDiskFreeSpace(NULL, &lSectorsPerCluster, &lBytesPerSector, &lNumberOfFreeClusters, NULL))
		*pDiskAvaible = (double)lNumberOfFreeClusters * (double)lSectorsPerCluster * (double)lBytesPerSector;
	else
		*pDiskAvaible = 0;

	// tolgo 50 mb dal conteggio dello spazio disponibile //
	if (*pDiskAvaible > (double)(50 * 1024 * 1024))
		*pDiskAvaible -= (double)(50 * 1024 * 1024);
	else
		*pDiskAvaible = 0;

	// ripasso alla directory precedente //
	_chdir(szCurDir);

	// calcolo la dimensione dei files dell'esame //
	LONGLONG llDimension;
	if (pImgManager->GetImageDimension(pListExamID, llDimension))
		*pSpaceRequired = (double)llDimension;
	else
		*pSpaceRequired = 0;

	// ritorno //
	return nReturn;
}

CString GetVolumeName()
{
	CString	strReturn = "";

	// salvo la directory corrente //
	char szCurDir[256];
	int nCurDrive = _getdrive();
	_getdcwd(nCurDrive, szCurDir, 256);

	// cambio directory //
	_chdir(theApp.m_sPathImageOD);

	// estraggo le informazioni //
	char szVolumeNameBuffer[256];
	if (GetVolumeInformation(NULL, szVolumeNameBuffer, 256, NULL, NULL, NULL, NULL, 0))
		strReturn = CString(szVolumeNameBuffer);

	// ripasso alla directory precedente //
	_chdir(szCurDir);

	// ritorno //
	return strReturn;
}

CString GetStatoText(long lStato)
{
	CString strReturn = theApp.GetMessageString(IDS_ANATOMIA_STATO_M1);

	switch (lStato)
	{
	case STATO_ANNULLATA: // richiesta cancellata prima che questa fosse in lavorazione //
	{
		strReturn = theApp.GetMessageString(IDS_ANATOMIA_STATO_0);
		break;
	}
	case STATO_PRENOTATA: // è stata inviata e non ancora acquisita //
	{
		strReturn = theApp.GetMessageString(IDS_ANATOMIA_STATO_1);
		break;
	}
	case STATO_ACQUISITA: // entra nell'archivio di metafora - non è più annullabile //
	{
		strReturn = theApp.GetMessageString(IDS_ANATOMIA_STATO_2);
		break;
	}
	case STATO_INLAVORAZIONE: // almeno uno dei campioni è in fase di lavorazione //
	{
		strReturn = theApp.GetMessageString(IDS_ANATOMIA_STATO_3);
		break;
	}
	case STATO_REFERTATA: // emesso il referto istologico //
	{
		strReturn = theApp.GetMessageString(IDS_ANATOMIA_STATO_4);
		break;
	}
	case STATO_SCARTATA: // errori nella richiesta //
	{
		strReturn = theApp.GetMessageString(IDS_ANATOMIA_STATO_5);
		break;
	}
	case STATO_RIREFERTATA: // modificato il referto o aggiunto il referto di nuove indagini //
	{
		strReturn = theApp.GetMessageString(IDS_ANATOMIA_STATO_6);
		break;
	}
	}

	return strReturn;
}

// Sandro 27/03/2012 //
BOOL IsBisestile(int iYear)
{
	COleDateTime date(iYear, 2, 29, 0, 0, 0);
	if (date.GetMonth() == 2)
		return TRUE;

	return FALSE;
}

// Sandro 30/03/2016 //
long GetDateTimeDifferenceInHoursFromLongs(long lData1, long lData2)
{
	CCustomDate customData1(lData1 > lData2 ? lData2 : lData1); // data minore //
	CCustomDate customData2(lData1 > lData2 ? lData1 : lData2); // data maggiore //

	CTime tData1(customData1.GetYear(), customData1.GetMonth(), customData1.GetDay(), customData1.GetHour(), customData1.GetMinute(), 0); // data minore //
	CTime tData2(customData2.GetYear(), customData2.GetMonth(), customData2.GetDay(), customData2.GetHour(), customData2.GetMinute(), 0); // data maggiore //

	CTimeSpan tsDataDiff = tData2 - tData1;

	return (long)tsDataDiff.GetTotalHours();
}

// Julio 10/08/2018 //
long GetDateTimeDifferenceInMinutesFromLongs(long lData1, long lData2)
{
	CCustomDate customData1(lData1 > lData2 ? lData2 : lData1); // data minore //
	CCustomDate customData2(lData1 > lData2 ? lData1 : lData2); // data maggiore //

	CTime tData1(customData1.GetYear(), customData1.GetMonth(), customData1.GetDay(), customData1.GetHour(), customData1.GetMinute(), 0); // data minore //
	CTime tData2(customData2.GetYear(), customData2.GetMonth(), customData2.GetDay(), customData2.GetHour(), customData2.GetMinute(), 0); // data maggiore //

	CTimeSpan tsDataDiff = tData2 - tData1;

	return (long)tsDataDiff.GetTotalMinutes();
}

// Sandro 27/03/2012 // rifatto l'algoritmo per il calcolo confrontando il risultato con il DATA.DIFF di Excel //
BOOL GetDateDifference(long lData1, long lData2, long* pYears, long* pMonths, long* pDays)
{
	ASSERT(pYears != NULL);
	ASSERT(pMonths != NULL);
	ASSERT(pDays != NULL);

	*pYears = 0;
	*pMonths = 0;
	*pDays = 0;

	if ((lData1 == lData2) || (lData1 == 0) || (lData2 == 0))
		return FALSE;

	CCustomDate customData1(lData1 > lData2 ? lData2 : lData1);
	CCustomDate customData2(lData1 > lData2 ? lData1 : lData2);

	*pYears = customData2.GetYear() - customData1.GetYear();
	*pMonths = customData2.GetMonth() - customData1.GetMonth();
	*pDays = customData2.GetDay() - customData1.GetDay();

	if ((*pDays) < 0)
	{
		int nMonthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (IsBisestile(customData2.GetYear()))
			nMonthDays[1]++; // bisestile //

		(*pDays) += nMonthDays[(customData2.GetMonth() + 10) % 12]; // aggiungo 10 e non 12 --> tolgo 1 perché l'array dei mesi è a base 0 e tolgo un altro 1 perché prendo i giorni del mese precedente //
		(*pMonths)--;
	}

	if ((*pMonths) < 0)
	{
		(*pMonths) += 12;
		(*pYears)--;
	}

	return TRUE;
}

// Sandro 31/01/2013 //
BOOL GetTimeDifferenceSameDay(long lData1, long lData2, long* pHours, long* pMinutes)
{
	ASSERT(pHours != NULL);
	ASSERT(pMinutes != NULL);

	*pHours = 0;
	*pMinutes = 0;

	if ((lData1 == lData2) || (lData1 == 0) || (lData2 == 0))
		return FALSE;

	CCustomDate customData1(lData1 > lData2 ? lData2 : lData1);
	CCustomDate customData2(lData1 > lData2 ? lData1 : lData2);

	long lYears = customData2.GetYear() - customData1.GetYear();
	long lMonths = customData2.GetMonth() - customData1.GetMonth();
	long lDays = customData2.GetDay() - customData1.GetDay();
	*pHours = customData2.GetHour() - customData1.GetHour();
	*pMinutes = customData2.GetMinute() - customData1.GetMinute();

	if ((*pMinutes) < 0)
	{
		(*pMinutes) += 60;
		(*pHours)--;
	}

	if ((*pHours) < 0)
	{
		(*pHours) += 24;
		lDays--;
	}
	(*pHours) += (lDays * 24);

	return TRUE;
}

//Gabriel BUG 6225 - Lista DO
CString GetStringEta(long lDataNascita, long lDataEsame, long lFormato)	//BOOL bSoloAnni)
{
	long iYears = 0, iMonths = 0, iDays = 0;
	if (!GetDateDifference(lDataNascita, lDataEsame, &iYears, &iMonths, &iDays))
		return "";
	
	CString strDate;

	if (theApp.m_bAtivaListaDO)
	{
		switch (lFormato)
		{
		case FormatoEta::AnnoMeseGiornoAbbreviato:
		{
			strDate.Format(theApp.GetMessageString(IDS_ETA_COMPLETA_FORMAT), iYears, iMonths, iDays); //
			break;
		}
		case FormatoEta::SoloAnno:
		{
			strDate.Format(theApp.GetMessageString(IDS_ETA_SOLOANNI_FORMAT), iYears); //
			break;
		}
		case FormatoEta::AnnoMese:
		{
			if (iMonths <= 1)
			{
				strDate.Format(theApp.GetMessageString(IDS_ETA_ANNOMESESINGOLARE_FORMAT), iYears, iMonths); //
				break;
			}
			strDate.Format(theApp.GetMessageString(IDS_ETA_ANNOMESEPLURALE_FORMAT), iYears, iMonths); //
			break;
		}
		}
	}
	else
	{
		if (lFormato == FormatoEta::SoloAnno)
			strDate.Format(theApp.GetMessageString(IDS_ETA_SOLOANNI_FORMAT), iYears);
		else
			strDate.Format(theApp.GetMessageString(IDS_ETA_COMPLETA_FORMAT), iYears, iMonths, iDays);
	}
	
	return strDate;
}

CString GetStringOreDifferenza(long lDataInizio, long lDataFine, BOOL bSoloMinuti)
{
	long lHours = 0;
	long lMinutes = 0;

	if (!GetTimeDifferenceSameDay(lDataInizio, lDataFine, &lHours, &lMinutes))
		return "";

	CString strTime;
	if (bSoloMinuti)
	{
		lMinutes += (lHours * 60);
		strTime.Format(theApp.GetMessageString(IDS_TEMPODIFF_SOLOMINUTI_FORMAT), lMinutes);
	}
	else
	{
		strTime.Format(theApp.GetMessageString(IDS_TEMPODIFF_OREMINUTI_FORMAT), lHours, lMinutes);
	}

	return strTime;
}

BOOL GetPrinterDevice(LPTSTR pszPrinterName, HGLOBAL *phDevNames, HGLOBAL *phDevMode)
{
	// if NULL is passed, then assume we are setting app object's
	// devmode and devnames
	if (phDevMode == NULL || phDevNames == NULL)
		return FALSE;

	// Open printer
	HANDLE hPrinter;
	if (OpenPrinter(pszPrinterName, &hPrinter, NULL) == FALSE)
		return FALSE;

	// obtain PRINTER_INFO_2 structure and close printer
	DWORD dwBytesReturned, dwBytesNeeded;
	GetPrinter(hPrinter, 2, NULL, 0, &dwBytesNeeded);
	PRINTER_INFO_2* p2 = (PRINTER_INFO_2*)GlobalAlloc(GPTR, dwBytesNeeded);

	if (GetPrinter(hPrinter, 2, (LPBYTE)p2, dwBytesNeeded, &dwBytesReturned) == 0)
	{
		GlobalFree(p2);
		ClosePrinter(hPrinter);
		return FALSE;
	}
	ClosePrinter(hPrinter);

	// Allocate a global handle for DEVMODE
	HGLOBAL  hDevMode = GlobalAlloc(GHND, sizeof(*p2->pDevMode) + p2->pDevMode->dmDriverExtra);
	DEVMODE* pDevMode = (DEVMODE*)GlobalLock(hDevMode);

	// copy DEVMODE data from PRINTER_INFO_2::pDevMode
	memcpy(pDevMode, p2->pDevMode, sizeof(*p2->pDevMode) + p2->pDevMode->dmDriverExtra);
	GlobalUnlock(hDevMode);

	// Compute size of DEVNAMES structure from PRINTER_INFO_2's data
	DWORD drvNameLen = lstrlen(p2->pDriverName) + 1;  // driver name
	DWORD ptrNameLen = lstrlen(p2->pPrinterName) + 1; // printer name
	DWORD porNameLen = lstrlen(p2->pPortName) + 1;    // port name

	// Allocate a global handle big enough to hold DEVNAMES.
	HGLOBAL hDevNames = GlobalAlloc(GHND, sizeof(DEVNAMES) + (drvNameLen + ptrNameLen + porNameLen) * sizeof(TCHAR));
	DEVNAMES* pDevNames = (DEVNAMES*)GlobalLock(hDevNames);

	// Copy the DEVNAMES information from PRINTER_INFO_2
	// tcOffset = TCHAR Offset into structure
	int tcOffset = sizeof(DEVNAMES) / sizeof(TCHAR);

	pDevNames->wDriverOffset = tcOffset;
	memcpy((LPTSTR)pDevNames + tcOffset, p2->pDriverName, drvNameLen*sizeof(TCHAR));
	tcOffset += drvNameLen;

	pDevNames->wDeviceOffset = tcOffset;
	memcpy((LPTSTR)pDevNames + tcOffset, p2->pPrinterName, ptrNameLen*sizeof(TCHAR));
	tcOffset += ptrNameLen;

	pDevNames->wOutputOffset = tcOffset;
	memcpy((LPTSTR)pDevNames + tcOffset, p2->pPortName, porNameLen*sizeof(TCHAR));
	pDevNames->wDefault = 0;

	GlobalUnlock(hDevNames);
	GlobalFree(p2);   // free PRINTER_INFO_2

	// set the new hDevMode and hDevNames
	*phDevMode = hDevMode;
	*phDevNames = hDevNames;
	return TRUE;
}

BOOL LoadPrinterSettingsFromFile(CString sSettingFile, HGLOBAL *pDevNames, HGLOBAL *pDevMode)
{
	BOOL bReturn = FALSE;

	CPrinterSettings prnReport;
	if (prnReport.Load(sSettingFile) == NO_ERROR)
	{
		*pDevNames = prnReport.GetDevNamesHandle();
		*pDevMode = prnReport.GetDevModeHandle();

		bReturn = (((*pDevNames) != NULL) && ((*pDevMode) != NULL));
	}

	return bReturn;
}

BOOL LoadPrinterSettingsFromNumber(long lPrinterToUse, HGLOBAL *pDevNames, HGLOBAL *pDevMode)
{
	BOOL bReturn = FALSE;

	*pDevNames = NULL;
	*pDevMode = NULL;

	switch (lPrinterToUse)
	{
	case Printer_Immagini:
	{
		bReturn = LoadPrinterSettingsFromFile(theApp.m_sDirProg + "\\PrinterImmagini.dat", pDevNames, pDevMode);
		break;
	}
	case Printer_Report1:
	{
		bReturn = LoadPrinterSettingsFromFile(theApp.m_sDirProg + "\\PrinterReports.dat", pDevNames, pDevMode);
		break;
	}
	case Printer_Report2:
	{
		bReturn = LoadPrinterSettingsFromFile(theApp.m_sDirProg + "\\PrinterReports2.dat", pDevNames, pDevMode);
		break;
	}
	case Printer_Report3:
	{
		bReturn = LoadPrinterSettingsFromFile(theApp.m_sDirProg + "\\PrinterReports3.dat", pDevNames, pDevMode);
		break;
	}
	case Printer_Report4:
	{
		bReturn = LoadPrinterSettingsFromFile(theApp.m_sDirProg + "\\PrinterReports4.dat", pDevNames, pDevMode);
		break;
	}
	case Printer_Report5:
	{
		bReturn = LoadPrinterSettingsFromFile(theApp.m_sDirProg + "\\PrinterReports5.dat", pDevNames, pDevMode);
		break;
	}
	case Printer_Report6:
	{
		bReturn = LoadPrinterSettingsFromFile(theApp.m_sDirProg + "\\PrinterReports6.dat", pDevNames, pDevMode);
		break;
	}
	case Printer_Report7:
	{
		bReturn = LoadPrinterSettingsFromFile(theApp.m_sDirProg + "\\PrinterReports7.dat", pDevNames, pDevMode);
		break;
	}
	case Printer_Report8:
	{
		bReturn = LoadPrinterSettingsFromFile(theApp.m_sDirProg + "\\PrinterReports8.dat", pDevNames, pDevMode);
		break;
	}
	case Printer_Report9:
	{
		// prima cerco la stampante "Etichette" //
		bReturn = GetPrinterDevice(_TESI_IMAGING_LABEL_PRINTER_NAME, pDevNames, pDevMode);

		// se non la trovo tento il caricamento delle impostazioni da file //
		if (!bReturn)
			bReturn = LoadPrinterSettingsFromFile(theApp.m_sDirProg + "\\PrinterReports9.dat", pDevNames, pDevMode);

		//
		break;
	}
	}

	return bReturn;
}

///

CString GetTextPattern(long lPattern)
{
	CString sReturn = "";

	switch (lPattern)
	{
	case 1:
	{
		sReturn = theApp.GetMessageString(IDS_PATTERN_RETICOLARE);
		break;
	}
	case 2:
	{
		sReturn = theApp.GetMessageString(IDS_PATTERN_GLOBULARE);
		break;
	}
	case 3:
	{
		sReturn = theApp.GetMessageString(IDS_PATTERN_MISTO);
		break;
	}
	case 4:
	{
		sReturn = theApp.GetMessageString(IDS_PATTERN_OMOGENEO);
		break;
	}
	case 5:
	{
		sReturn = theApp.GetMessageString(IDS_PATTERN_POLIMORFO);
		break;
	}
	case 6:
	{
		sReturn = theApp.GetMessageString(IDS_PATTERN_COFFEE_LIKE);
		break;
	}
	case 7:
	{
		sReturn = theApp.GetMessageString(IDS_PATTERN_FOGLIA_ACERO);
		break;
	}
	case 8:
	{
		sReturn = theApp.GetMessageString(IDS_PATTERN_LAGHI_VASCOLARI);
		break;
	}
	case 9:
	{
		sReturn = theApp.GetMessageString(IDS_PATTERN_CHERATINIZZANTE);
		break;
	}
	case 10:
	{
		sReturn = theApp.GetMessageString(IDS_PATTERN_INDEFINITO);
		break;
	}
	}

	return sReturn;
}

CString GetTextTumoriMelanociticiBenigni1(long lID)
{
	CString sReturn = "";

	switch (lID)
	{
	case 1:
	{
		sReturn = "Lentiggine";
		break;
	}
	case 2:
	{
		sReturn = "Nevo melanocitico piano comune";
		break;
	}
	case 3:
	{
		sReturn = "Nevo melanocitico piano atipico tipo A";
		break;
	}
	case 4:
	{
		sReturn = "Nevo melanocitico piano atipico tipo B";
		break;
	}
	case 5:
	{
		sReturn = "Nevo di Miescher";
		break;
	}
	case 6:
	{
		sReturn = "Nevo di Unna";
		break;
	}
	case 7:
	{
		sReturn = "Nevo di Spitz";
		break;
	}
	case 8:
	{
		sReturn = "Nevo di Reed";
		break;
	}
	case 9:
	{
		sReturn = "Nevo melanocitico congenito";
		break;
	}
	case 10:
	{
		sReturn = "Nevo blu";
		break;
	}
	case 11:
	{
		sReturn = "Macchia mongolica";
		break;
	}
	case 12:
	{
		sReturn = "Nevo di Ota e di Ito";
		break;
	}
	case 13:
	{
		sReturn = "Nevo di Sutton";
		break;
	}
	case 14:
	{
		sReturn = "Nevo di Meyerson";
		break;
	}
	case 15:
	{
		sReturn = "Nevo melanocitico combinato";
		break;
	}
	case 16:
	{
		sReturn = "Nevo melanocitico persistente";
		break;
	}
	case 17:
	{
		sReturn = "Nevo melanocitico in regressione";
		break;
	}
	}

	return sReturn;
}

CString GetTextTumoriMelanociticiMaligni1(long lID)
{
	CString sReturn = "";

	switch (lID)
	{
	case 1:
	{
		sReturn = "Melanoma";
		break;
	}
	case 2:
	{
		sReturn = "Lentigo maligna";
		break;
	}
	case 3:
	{
		sReturn = "Lentigo maligna-melanoma";
		break;
	}
	case 4:
	{
		sReturn = "Melanoma su nevo";
		break;
	}
	}

	return sReturn;
}

CString GetTextTumoriNonMelanociticiLesioniEpiteliali(long lID)
{
	CString sReturn = "";

	switch (lID)
	{
	case 1:
	{
		sReturn = "Cheratosi seborroica";
		break;
	}
	case 2:
	{
		sReturn = "Carcinoma basocellulare";
		break;
	}
	case 3:
	{
		sReturn = "Carcinoma spinocellulare";
		break;
	}
	case 4:
	{
		sReturn = "Cheratosi solare pigmentata";
		break;
	}
	case 5:
	{
		sReturn = "Malattia di Bowen";
		break;
	}
	case 6:
	{
		sReturn = "Cistoadenoma apocrino";
		break;
	}
	}

	return sReturn;
}

CString GetTextTumoriNonMelanociticiLesioniVascolari(long lID)
{
	CString sReturn = "";

	switch (lID)
	{
	case 1:
	{
		sReturn = "Angioma";
		break;
	}
	case 2:
	{
		sReturn = "Angioma trombizzato";
		break;
	}
	case 3:
	{
		sReturn = "Angiocheratoma";
		break;
	}
	case 4:
	{
		sReturn = "Granuloma piogenico";
		break;
	}
	case 5:
	{
		sReturn = "Emorragia intra e sub-epidermica";
		break;
	}
	}

	return sReturn;
}

CString GetTextTumoriMelanociticiBenigni2(long lID)
{
	CString sReturn = "";

	switch (lID)
	{
	case 1:
	{
		sReturn = "Lentigo simplex";
		break;
	}
	case 2:
	{
		sReturn = "Nevo melanocitico giunzionale";
		break;
	}
	case 3:
	{
		sReturn = "Nevo melanocitico composto";
		break;
	}
	case 4:
	{
		sReturn = "Nevo melanocitico dermico";
		break;
	}
	case 5:
	{
		sReturn = "Nevo displastico";
		break;
	}
	case 6:
	{
		sReturn = "Nevo a cellule epitelioidi e fusate";
		break;
	}
	case 7:
	{
		sReturn = "Nevo a cellule fusate";
		break;
	}
	case 8:
	{
		sReturn = "Nevo penetrante in profondità";
		break;
	}
	case 9:
	{
		sReturn = "Nevo blu";
		break;
	}
	case 10:
	{
		sReturn = "Nevo blu cellulato";
		break;
	}
	case 11:
	{
		sReturn = "Macchia mongolica";
		break;
	}
	case 12:
	{
		sReturn = "Nevo di Ota e di Ito";
		break;
	}
	case 13:
	{
		sReturn = "Nevo congenito comune";
		break;
	}
	case 14:
	{
		sReturn = "Nevo di Sutton";
		break;
	}
	case 15:
	{
		sReturn = "Nevo di Meyerson";
		break;
	}
	case 16:
	{
		sReturn = "Nevo melanocitico combinato";
		break;
	}
	case 17:
	{
		sReturn = "Nevo melanocitico persistente";
		break;
	}
	case 18:
	{
		sReturn = "Nevo melanocitico in regressione";
		break;
	}
	}

	return sReturn;
}

CString GetTextTumoriMelanociticiMaligni2(long lID)
{
	CString sReturn = "";

	switch (lID)
	{
	case 1:
	{
		sReturn = "Lentigo maligna";
		break;
	}
	case 2:
	{
		sReturn = "Melanoma non invasivo";
		break;
	}
	case 3:
	{
		sReturn = "Melanoma in fase orizzontale";
		break;
	}
	case 4:
	{
		sReturn = "Melanoma in fase orizzontale e verticale";
		break;
	}
	case 5:
	{
		sReturn = "Melanoma nodulare";
		break;
	}
	}

	return sReturn;
}

///

DWORD GetUpdatedPrivileges()
{
	DWORD dwReturn = 0;

	CStringList listGroups;
	switch (theApp.m_lLoginMode)
	{
	case 1:
	case 2:
	{
		AMLogin_GetUserGroups(&listGroups);
		break;
	}
	case 3:
	case 4:
	{
		AMLogin_GetUserGroups_Net(&listGroups);
		break;
	}
	default:
	{
		ASSERT(FALSE);
		break;
	}
	}

	CString sFilter;
	sFilter.Format("ELIMINATO=0 AND UO=%li", theApp.m_lUO);

	CVistaGruppiSet setGruppi;
	setGruppi.SetOpenFilter(sFilter);
	if (setGruppi.OpenRecordset("GetUpdatedPrivileges"))
	{
		while (!setGruppi.IsEOF())
		{
			POSITION pos = listGroups.GetHeadPosition();
			while (pos != NULL)
			{
				if (setGruppi.m_sNome.CompareNoCase(listGroups.GetAt(pos)) == 0)
				{
					dwReturn |= setGruppi.m_lPermessi;
					break;
				}

				listGroups.GetNext(pos);
			}

			setGruppi.MoveNext();
		}

		setGruppi.CloseRecordset("GetUpdatedPrivileges");
	}

	return dwReturn;
}

///

BOOL GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT num = 0;          // number of image encoders
	UINT size = 0;         // size of the image encoder array in bytes

	Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;
	Gdiplus::GetImageEncodersSize(&num, &size);

	if (size == 0)
		return FALSE;  // Failure

	pImageCodecInfo = (Gdiplus::ImageCodecInfo*) malloc(size);

	if (pImageCodecInfo == NULL)
		return FALSE;  // Failure

	Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return TRUE;  // Success
		}
	}

	free(pImageCodecInfo);
	return FALSE;  // Failure
}

// Sandro 28/05/2013 //
CString GetContatoreAnnuale(long lTipoEsame)
{
	CString strOutput = "";

	if (lTipoEsame > 0)
	{
		// Sandro 28/05/2013 // RAS 20130100 // Progressivo annuale diviso per sede //

		if (theApp.m_bProgressivoEsamePerSede)
		{
			long lContatoreAnnuale = 0;
			int iAnnoAttuale = CTime::GetCurrentTime().GetYear();

			CString sFilter;
			sFilter.Format("IDSede=%li AND IDTipoEsame=%li", theApp.m_lIDSedeEsameDefault, lTipoEsame);

			CTipiEsamiProgressivoAnnualeSet setTEPA;
			setTEPA.SetOpenFilter(sFilter);

			if (setTEPA.OpenRecordset("GetContatoreAnnuale"))
			{
				if (setTEPA.IsEOF())
				{
					// record non trovato, lo aggiungo //

					if (setTEPA.AddNewRecordset("GetContatoreAnnuale"))
					{
						setTEPA.m_lIDSede = theApp.m_lIDSedeEsameDefault;
						setTEPA.m_lIDTipoEsame = lTipoEsame;
						setTEPA.m_lContatoreAnnuale = 1;
						setTEPA.m_lAnno = iAnnoAttuale;

						if (setTEPA.UpdateRecordset("GetContatoreAnnuale"))
							lContatoreAnnuale = 1;
					}
				}
				else
				{
					// record già presente, lo edito //

					if (setTEPA.EditRecordset("GetContatoreAnnuale"))
					{
						if (iAnnoAttuale != setTEPA.m_lAnno)
						{
							setTEPA.m_lContatoreAnnuale = 0;
							setTEPA.m_lAnno = iAnnoAttuale;
						}

						setTEPA.m_lContatoreAnnuale++;

						if (setTEPA.UpdateRecordset("GetContatoreAnnuale"))
							lContatoreAnnuale = setTEPA.m_lContatoreAnnuale;
					}
				}

				setTEPA.CloseRecordset("GetContatoreAnnuale");
			}

			if (lContatoreAnnuale > 0)
			{
				if (theApp.m_nApplication == PRG_IMAGENT)
					strOutput.Format("%s%05li / %04li", CSediEsameSet().GetSigla(theApp.m_lIDSedeEsameDefault), lContatoreAnnuale, iAnnoAttuale);
				else
					strOutput.Format("%s%05li / %s / %04li", CSediEsameSet().GetSigla(theApp.m_lIDSedeEsameDefault), lContatoreAnnuale, CTipoEsameSet().GetSigla(lTipoEsame), iAnnoAttuale);
			}
		}
		else
		{
			CString strFilter;
			strFilter.Format("Contatore=%li", lTipoEsame);

			CTipoEsameSet setTemp;
			setTemp.SetBaseFilter("(UO=0 OR UO>0)");
			setTemp.SetOpenFilter(strFilter);

			if (setTemp.OpenRecordset("GetContatoreAnnuale") == TRUE)
			{
				if (!setTemp.IsEOF())
				{
					int iAnnoAttuale = CTime::GetCurrentTime().GetYear();

					if (setTemp.EditRecordset("GetContatoreAnnuale"))
					{
						if (iAnnoAttuale != setTemp.m_lAnno)
						{
							setTemp.m_lAnno = iAnnoAttuale;
							setTemp.m_lContatoreAnnuale = 0;
						}

						setTemp.m_lContatoreAnnuale++;

						if (theApp.m_nApplication == PRG_IMAGENT)
						{
							strOutput.Format("%s%06li / %04li", setTemp.m_sStazione, setTemp.m_lContatoreAnnuale, setTemp.m_lAnno);
						}
						else
						{
							if (setTemp.m_sStazione.IsEmpty())
								strOutput.Format("%06li / %s / %04li", setTemp.m_lContatoreAnnuale, setTemp.m_sSigla, setTemp.m_lAnno);
							else
								strOutput.Format("%s%05li / %s / %04li", setTemp.m_sStazione, setTemp.m_lContatoreAnnuale, setTemp.m_sSigla, setTemp.m_lAnno);
						}

						setTemp.UpdateRecordset("GetContatoreAnnuale");
					}
				}

				setTemp.CloseRecordset("GetContatoreAnnuale");
			}
		}
	}

	return strOutput;
}

// Sandro 28/05/2013 //
CString GetContatoreAnnualeNoIncrement(long lTipoEsame)
{
	CString strReturn = "";

	if (lTipoEsame > 0)
	{
		// Sandro 28/05/2013 // RAS 20130100 // Progressivo annuale diviso per sede //

		if (theApp.m_bProgressivoEsamePerSede)
		{
			long lContatoreAnnuale = 0;
			int iAnnoAttuale = CTime::GetCurrentTime().GetYear();

			CString sFilter;
			sFilter.Format("IDSede=%li AND IDTipoEsame=%li", theApp.m_lIDSedeEsameDefault, lTipoEsame);

			CTipiEsamiProgressivoAnnualeSet setTEPA;
			setTEPA.SetOpenFilter(sFilter);

			if (setTEPA.OpenRecordset("GetContatoreAnnualeNoIncrement"))
			{
				if (setTEPA.IsEOF())
				{
					// record non trovato //

					lContatoreAnnuale = 1;
				}
				else
				{
					// record già presente //

					if (iAnnoAttuale != setTEPA.m_lAnno)
						lContatoreAnnuale = 1;
					else
						lContatoreAnnuale = setTEPA.m_lContatoreAnnuale + 1;
				}

				setTEPA.CloseRecordset("GetContatoreAnnualeNoIncrement");
			}

			if (lContatoreAnnuale > 0)
			{
				if (theApp.m_nApplication == PRG_IMAGENT)
					strReturn.Format("%s%05li / %04li", CSediEsameSet().GetSigla(theApp.m_lIDSedeEsameDefault), lContatoreAnnuale, iAnnoAttuale);
				else
					strReturn.Format("%s%05li / %s / %04li", CSediEsameSet().GetSigla(theApp.m_lIDSedeEsameDefault), lContatoreAnnuale, CTipoEsameSet().GetSigla(lTipoEsame), iAnnoAttuale);
			}
		}
		else
		{
			CString strFilter;
			strFilter.Format("Contatore=%li", lTipoEsame);

			CTipoEsameSet setTemp;
			setTemp.SetOpenFilter(strFilter);

			if (setTemp.OpenRecordset("GetContatoreAnnualeNoIncrement"))
			{
				if (!setTemp.IsEOF())
				{
					int iAnnoAttuale = CTime::GetCurrentTime().GetYear();

					if (iAnnoAttuale != setTemp.m_lAnno)
					{
						setTemp.m_lAnno = iAnnoAttuale;
						setTemp.m_lContatoreAnnuale = 0;
					}

					setTemp.m_lContatoreAnnuale++;

					if (theApp.m_nApplication == PRG_IMAGENT)
					{
						strReturn.Format("%s%06li / %04li", setTemp.m_sStazione, setTemp.m_lContatoreAnnuale, setTemp.m_lAnno);
					}
					else
					{
						if (setTemp.m_sStazione.IsEmpty())
							strReturn.Format("%06li / %s / %04li", setTemp.m_lContatoreAnnuale, setTemp.m_sSigla, setTemp.m_lAnno);
						else
							strReturn.Format("%s%05li / %s / %04li", setTemp.m_sStazione, setTemp.m_lContatoreAnnuale, setTemp.m_sSigla, setTemp.m_lAnno);
					}
				}

				setTemp.CloseRecordset("GetContatoreAnnualeNoIncrement");
			}
		}
	}

	return strReturn;
}

// Sandro 28/05/2013 //
CString GetCodicePrenotazione(long lTipoEsame)
{
	CString strOutput = "";

	//

	CString sSigla = CTipoEsameSet().GetSiglaPrenotazione(lTipoEsame);
	sSigla.Trim();

	if (sSigla.IsEmpty())
		sSigla = "Z";

	if (sSigla.GetLength() > 1)
		sSigla = sSigla.Left(1);

	if (sSigla == "'")
		sSigla = "Z";

	sSigla.MakeUpper();

	//

	long lProssimoCodice = 0;

	CCustomDate data1(TRUE, TRUE);
	data1.SetHour(0);
	data1.SetMinute(0);

	CCustomDate data2(TRUE, TRUE);
	data2.SetHour(23);
	data2.SetMinute(59);

	/* Davide 20170717 - tentativo velocizzazione worklist
	CString sFilter;
	sFilter.Format("Data>=%li AND Data<=%li AND CodicePrenotazione LIKE '%s%%'", data1.GetDate(), data2.GetDate(), sSigla);

	CEsamiSet setEx;
	setEx.SetOpenFilter(sFilter);
	setEx.SetSortRecord("CodicePrenotazione DESC");
	if (setEx.OpenRecordset("GetCodicePrenotazione"))
	{
	if (!setEx.IsEOF() && (setEx.m_sCodicePrenotazione.GetLength() > 0))
	{
	CString sCodiceTemp = setEx.m_sCodicePrenotazione.Right(setEx.m_sCodicePrenotazione.GetLength() - 1);
	lProssimoCodice = atol(sCodiceTemp) + 1;
	}

	setEx.CloseRecordset("GetCodicePrenotazione");
	}
	*/

	DWORD dwTime = ::timeGetTime();
	CString strQuery;
	strQuery.Format("SELECT CODICEPRENOTAZIONE FROM EESAMI WHERE Data>=%li AND Data<=%li AND CodicePrenotazione LIKE '%s%%'", data1.GetDate(), data2.GetDate(), sSigla);

	CRecordset set(&theApp.m_dbEndox);

	try
	{
		set.Open(CRecordset::snapshot, strQuery, CRecordset::readOnly);
		if (!set.IsEOF())
		{
			CString strCodicePrenotazione;
			set.GetFieldValue("CODICEPRENOTAZIONE", strCodicePrenotazione);
			if (strCodicePrenotazione.GetLength() > 0)
			{
				CString sCodiceTemp = strCodicePrenotazione.Right(strCodicePrenotazione.GetLength() - 1);
				lProssimoCodice = atol(sCodiceTemp) + 1;
			}
		}
	}
	catch (CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
	}

	if (set.IsOpen())
		set.Close();

	XWriteLogTime("GetCodicePrenotazione", timeGetTime() - dwTime, 0);

	if (lProssimoCodice <= 100)
		lProssimoCodice = 101;

	//

	strOutput.Format("%s%li", sSigla, lProssimoCodice);
	return strOutput;
}

// Sandro 05/12/2013 //
CString DecodeCitta(CString sCAP, CString sCitta, CString sProvincia)
{
	CString sReturn = "";

	sCAP.Trim();
	sCitta.Trim();
	sProvincia.Trim();

	if (!sCAP.IsEmpty())
		sReturn = sCAP;

	if (!sCitta.IsEmpty())
	{
		if (!sReturn.IsEmpty())
			sReturn += " ";

		sReturn += sCitta;
	}

	if (!sProvincia.IsEmpty())
	{
		if (!sReturn.IsEmpty())
			sReturn += " ";

		sReturn += "(" + sProvincia + ")";
	}

	return sReturn;
}

// Sandro 05/12/2013 //
CString DecodeSesso(long lSesso)
{
	CString sReturn = theApp.GetMessageString(IDS_PAZIENTIDLG_ND);

	switch (lSesso)
	{
	case -1:
	{
		sReturn = theApp.GetMessageString(IDS_PAZIENTIDLG_ND);
		break;
	}
	case 0:
	{
		sReturn = theApp.GetMessageString(IDS_PAZIENTIDLG_MALE);
		break;
	}
	case 1:
	{
		sReturn = theApp.GetMessageString(IDS_PAZIENTIDLG_FEMALE);
		break;
	}
	case 2:
	{
		sReturn = theApp.GetMessageString(IDS_PAZIENTIDLG_AMBIGOUS);
		break;
	}
	case 3:
	{
		sReturn = theApp.GetMessageString(IDS_PAZIENTIDLG_NOTAPPLICABLE);
		break;
	}
	case 4:
	{
		sReturn = theApp.GetMessageString(IDS_PAZIENTIDLG_OTHER);
		break;
	}
	}

	return sReturn;
}

INT_PTR TimerMessageBox(CString sMainMessage, UINT uidTitleMessage, UINT uidBtnOKMessage, UINT uidBtnCancelMessage, long lTimerPartenza)
{
	CMessageBoxTimerDlg dlg(NULL, sMainMessage, uidTitleMessage, uidBtnOKMessage, uidBtnCancelMessage, lTimerPartenza);
	return dlg.DoModal();
}

void RiempiComboStatiWorklist(CComboBox* pComboBox, long lStatoDaSelezionare, BOOL bFastFichaWorklist)
{
	ASSERT((lStatoDaSelezionare == LPC_STATO_NONPRESENTATA) || (lStatoDaSelezionare == LPC_STATO_NONEROGATA) || (lStatoDaSelezionare == LPC_STATO_REFERTATA) || (lStatoDaSelezionare == LPC_STATO_EROGATA) || (lStatoDaSelezionare == LPC_STATO_INCORSO) || (lStatoDaSelezionare == LPC_STATO_ACCETTATA) || (lStatoDaSelezionare == LPC_STATO_PRENOTATA));

	//

	enum
	{
		enumIndexStatoPrenotata,
		enumIndexStatoAccettata,
		enumIndexStatoInCorso,
		enumIndexStatoErogata,
		enumIndexStatoRefertata,
		enumIndexStatoNonErogata,
		enumIndexStatoNonPresentata
	};

	//

	pComboBox->ResetContent();

	if (bFastFichaWorklist)
	{
		int iIndexStatoTutti = pComboBox->AddString(theApp.GetMessageString(IDS_TUTTI));
		pComboBox->SetItemData(iIndexStatoTutti, 100);
	}

	int iIndexStatoPrenotata = pComboBox->AddString(theApp.GetMessageString(IDS_PRENOTATI));
	pComboBox->SetItemData(iIndexStatoPrenotata, LPC_STATO_PRENOTATA);

	int iIndexStatoAccettata = pComboBox->AddString(theApp.GetMessageString(IDS_ACCETTATI));
	pComboBox->SetItemData(iIndexStatoAccettata, LPC_STATO_ACCETTATA);

	int iIndexStatoInCorso = pComboBox->AddString(theApp.GetMessageString(IDS_INCORSO));
	pComboBox->SetItemData(iIndexStatoInCorso, LPC_STATO_INCORSO);

	int iIndexStatoErogata = pComboBox->AddString(theApp.GetMessageString(IDS_EROGATI));
	pComboBox->SetItemData(iIndexStatoErogata, LPC_STATO_EROGATA);

	int iIndexStatoRefertata = pComboBox->AddString(theApp.GetMessageString(IDS_REFERTATI));
	pComboBox->SetItemData(iIndexStatoRefertata, LPC_STATO_REFERTATA);

	int iIndexStatoNonErogata = pComboBox->AddString(theApp.GetMessageString(IDS_NONEROGATI));
	pComboBox->SetItemData(iIndexStatoNonErogata, LPC_STATO_NONEROGATA);

	int iIndexStatoNonPresentata = pComboBox->AddString(theApp.GetMessageString(IDS_NONPRESENTATI));
	pComboBox->SetItemData(iIndexStatoNonPresentata, LPC_STATO_NONPRESENTATA);

	int iIndexStatoRiconvocato = -1;
	if (theApp.m_bAtivaListaDO)
	{
		//Gabriel BUG 6225 - Lista DO
		iIndexStatoRiconvocato = pComboBox->AddString(theApp.GetMessageString(IDS_RICONVOCATO));
		pComboBox->SetItemData(iIndexStatoRiconvocato, LPC_STATO_RICONVOCATO);
	}
	
	//

	if (bFastFichaWorklist)
	{
		pComboBox->SetCurSel(0);
	}
	else
	{
		switch (lStatoDaSelezionare)
		{
		case LPC_STATO_PRENOTATA:
		{
			pComboBox->SetCurSel(iIndexStatoPrenotata);
			break;
		}
		case LPC_STATO_ACCETTATA:
		{
			pComboBox->SetCurSel(iIndexStatoAccettata);
			break;
		}
		case LPC_STATO_INCORSO:
		{
			pComboBox->SetCurSel(iIndexStatoInCorso);
			break;
		}
		case LPC_STATO_EROGATA:
		{
			pComboBox->SetCurSel(iIndexStatoErogata);
			break;
		}
		case LPC_STATO_REFERTATA:
		{
			pComboBox->SetCurSel(iIndexStatoRefertata);
			break;
		}
		case LPC_STATO_NONEROGATA:
		{
			pComboBox->SetCurSel(iIndexStatoNonErogata);
			break;
		}
		case LPC_STATO_NONPRESENTATA:
		{
			pComboBox->SetCurSel(iIndexStatoNonPresentata);
			break;
		}
		//Gabriel BUG 6225 - Lista DO
		case LPC_STATO_RICONVOCATO:
		{
			if (theApp.m_bAtivaListaDO)
				pComboBox->SetCurSel(iIndexStatoRiconvocato);
			break;
		}
		default:
		{
			ASSERT(FALSE);

			pComboBox->SetCurSel(iIndexStatoAccettata);
			break;
		}
		}
	}
}

long GetStatoRichiestaLong(CString sStato)
{
	if (sStato.CompareNoCase(theApp.GetMessageString(IDS_PRENOTATO)) == 0)
		return LPC_STATO_PRENOTATA;
	if (sStato.CompareNoCase(theApp.GetMessageString(IDS_ACCETTATO)) == 0)
		return LPC_STATO_ACCETTATA;
	if (sStato.CompareNoCase(theApp.GetMessageString(IDS_INCORSO)) == 0)
		return LPC_STATO_INCORSO;
	if (sStato.CompareNoCase(theApp.GetMessageString(IDS_EROGATO)) == 0)
		return LPC_STATO_EROGATA;
	if (sStato.CompareNoCase(theApp.GetMessageString(IDS_REFERTATO)) == 0)
		return LPC_STATO_REFERTATA;
	if (sStato.CompareNoCase(theApp.GetMessageString(IDS_NONEROGATO)) == 0)
		return LPC_STATO_NONEROGATA;
	if (sStato.CompareNoCase(theApp.GetMessageString(IDS_NONPRESENTATO)) == 0)
		return LPC_STATO_NONPRESENTATA;

	return 100;
}

CString GetStatoRichiestaString(CString sStato)
{
	if (sStato == "10")
		return theApp.GetMessageString(IDS_PRENOTATO);
	if (sStato == "0")
		return theApp.GetMessageString(IDS_ACCETTATO);
	if (sStato == "-10")
		return theApp.GetMessageString(IDS_INCORSO);
	if (sStato == "-15")
		return theApp.GetMessageString(IDS_EROGATO);
	if (sStato == "-20")
		return theApp.GetMessageString(IDS_REFERTATO);
	if (sStato == "-30")
		return theApp.GetMessageString(IDS_NONEROGATO);
	if (sStato == "-40")
		return theApp.GetMessageString(IDS_NONPRESENTATO);

	return "";
}

//Julio BUG 6385
BOOL FleuryIsUserADoctor()
{
	if (!theApp.m_bPersonalizzazioniBrasileFleury)
		return TRUE;
	
	else
	{
		//Se o login foi feito via AD o usuario é cirado automaticamente pelo AMLogin
		long lUserID = 0;
		AMLogin_GetUserID(&lUserID);
		long idMedico = CMediciSet().GetContatoreFromUserID(lUserID); //já verifico se é um médico cadastrado
		//

		if (idMedico <= 0) //Neste caso é um enfermeiro
		{
			if (CUOSet().GetUsernameResponsabile(theApp.m_lUO).IsEmpty())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_3L3N_NOANAG));
				AMLogin_Logout();
				theApp.m_lUO = 0;
				return FALSE;
			}
			else //o usuario atual nao é um médico mas a uo tem um responsável
			{
				return TRUE;
			}
		}
		else
		{
			return TRUE;
		}
	}
}

//Julio Login SEGU
BOOL FleuryGetHealthProfessional() 
{
#ifdef _DEBUG
	return TRUE;
#endif
	if (!theApp.m_bUsaIDSegu)
		return FleuryUserCodeCheck();

	BOOL bReturn = FALSE;
	
	//Chamo a API pra verificar se é um medico ou um enfermeiro
	userRequest request;
	strcpy(request.username, AMLogin_GetUsername());
	CUserService userService(theApp.m_sHttpServerRichiestaInfoUser, theApp.m_sHttpServerRichiestaUserSignature);
	userInformationResponse response = userService.GetUserInfo(request);
		
	if (strcmp(response.szError, "") != 0) //Verifico se a chamada não retornou erros
	{
		CString message;
		message.Format("%s", response.szError);
		theApp.AfxMessageBoxEndo(message);
		AMLogin_Logout();
		theApp.m_lUO = 0;
		bReturn = FALSE;
	}
	//

	//Se o login foi feito via AD o usuario é cirado automaticamente pelo AMLogin
	long lUserID = 0;
	AMLogin_GetUserID(&lUserID);
	long idMedico = CMediciSet().GetContatoreFromUserID(lUserID); //já verifico se é um médico cadastrado
	CString sRubrica = CString(response.szRubrica); //Verifico se o método retornou uma rúbrica (somente médicos tem rúbrica)
	//
							
	if (idMedico <= 0 && sRubrica.IsEmpty()) //Neste caso é um enfermeiro
	{	
		if (CUOSet().GetUsernameResponsabile(theApp.m_lUO).IsEmpty())
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_3L3N_NOANAG));
			AMLogin_Logout();
			theApp.m_lUO = 0;
			bReturn = FALSE;
		}
		else			
			bReturn = TRUE;					
	}
	else //Neste caso é um médico
	{
		//Obtenho as informações retornadas pelo método
		CString sLoginRede = CString(response.szLoginRede);
		CString sNomeCompleto = CString(response.szNomeCompleto);

		CString sNome = CString(response.szNomeCompleto);
		sNome.Replace("DR. ", "");
		sNome.Replace("DRA. ", "");

		CString sIdProfissionalSaude = CString(response.szIdProfissionalSaude);
		CString sConselhoRegional = CString(response.szConselhoRegional);
		CString sNumeroCertificado = CString(response.szNumeroCertificado);
		CString sUFCertificado = CString(response.szUFCertificado);
		CString sLogin3L3N = CString(response.szLogin3L3N);
		CString sIdSEGU = CString(response.szIdSEGU);
		CString sDataAlteracaoLoginRede = CString(response.szDataAlteracaoLoginRede);
		CString sDataAlteracaoRubrica = CString(response.szDataAlteracaoRubrica);

		CString sFirma = sNomeCompleto + " - " + sConselhoRegional + sUFCertificado + ": " + sNumeroCertificado;
		//

		if (idMedico > 0) //O médico já existe, vou fazer update
		{
			ReplaceImmagineFirmaFromHEX(sRubrica);
			CMediciSet().UpdateInformation(idMedico, sNome, sNumeroCertificado, sFirma, sLogin3L3N, sIdSEGU);

			bReturn = TRUE;
		}
		else //É um médico novo, devo fazer insert
		{
			CMediciSet set;
			
			CString sFilter;
			sFilter.Format("Contatore=%li", -1);

			set.SetOpenFilter(sFilter);
			if (set.OpenRecordset("Common::FleuryGetHealthProfessional"))
			{
				if (set.AddNewRecordset("Common::FleuryGetHealthProfessional"))
				{
					set.m_sNome = sNome;
					set.m_sCodiceFiscale = sNumeroCertificado;
					set.m_sFirma0 = sFirma;
					set.m_sCodice3L3N = sLogin3L3N;
					set.m_sCodice = sIdSEGU;
					set.m_lIDUserEndox = lUserID;
					set.m_lUO = theApp.m_lUO;

					set.UpdateRecordset("Common::FleuryGetHealthProfessional");

				}
				set.CloseRecordset("Common::FleuryGetHealthProfessional");
			}

			ReplaceImmagineFirmaFromHEX(sRubrica);

			bReturn = TRUE;
		}
	}	

	return bReturn;
	//return TRUE; //por enquanto vou sempre retornar TRUE porque a API parece ser bem instavel
}

//Julio Login SEGU
BOOL ReplaceImmagineFirmaFromHEX(CString sInput)
{
	BOOL bOK = FALSE;

	long lUserID = 0;
	AMLogin_GetUserID(&lUserID);
	long idMedico = CMediciSet().GetContatoreFromUserID(lUserID);
	
	if (idMedico > 0)
	{		
		CString sXXXFile = theApp.m_sDirTemp + "\\" + CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M%S") + ".xxx";
		CString sBMPFile = theApp.m_sDirTemp + "\\" + CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M%S") + ".bmp";
		CString sBufferB64 = "";

		bOK = CCommonCLR().SaveHexToFile(sInput, sXXXFile);

		if (bOK)
		{
			bOK = FALSE;

			USES_CONVERSION;
			Gdiplus::Bitmap* pBitmap = (Gdiplus::Bitmap*)Gdiplus::Bitmap::FromFile(A2W(sXXXFile));
			if (pBitmap->GetLastStatus() == Gdiplus::Ok)
			{
				CLSID idClass;
				if (GetEncoderClsid(L"image/bmp", &idClass))
					bOK = (pBitmap->Save(T2W(sBMPFile), &idClass, NULL) == Gdiplus::Ok);

				delete pBitmap;
			}
		}

		if (bOK)
		{
			bOK = FALSE;

			HANDLE hFile = CreateFile(sBMPFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
			if (hFile != INVALID_HANDLE_VALUE)
			{
				DWORD dwFileSize = GetFileSize(hFile, NULL);

				DWORD dwEncodeBufferLength = AmBase64_CalculateRequiredEncodeOutputBufferSize(dwFileSize);
				if (dwEncodeBufferLength < _FIRMA_BMP_MAX_LENGTH)
				{
					DWORD dwBytesRead;
					BYTE* pBufferFile = new BYTE[dwFileSize];
					if (ReadFile(hFile, (LPVOID)pBufferFile, dwFileSize, &dwBytesRead, NULL))
					{
						DWORD dwEncodeBufferLength = AmBase64_CalculateRequiredEncodeOutputBufferSize(dwFileSize);
						TCHAR* pBufferB64 = new TCHAR[dwEncodeBufferLength];
						ZeroMemory(pBufferB64, dwEncodeBufferLength * sizeof(TCHAR));
						AmBase64_EncodeBuffer((CHAR*)pBufferFile, dwFileSize, pBufferB64);
						sBufferB64 = CString(pBufferB64);
						delete pBufferB64;

						bOK = TRUE;
					}
					delete pBufferFile;
				}
				else
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMMAGINEFIRMA_TROPPOGRANDE), MB_ICONSTOP);
				}

				CloseHandle(hFile);
			}
		}

		//

		DeleteFile(sXXXFile);
		DeleteFile(sBMPFile);

		//

		if (bOK && (!sBufferB64.IsEmpty()))
			CMediciSet().SetImmagineFirma(idMedico, sBufferB64);
	}
	
	return bOK;
}

BOOL FleuryUserCodeCheck()
{
	BOOL bReturn = FALSE;

	if (theApp.m_listUserPhases.Find(CO_FASE_CHIUSURA_STAMPA) != NULL) //Se l'utente può chiudere l'esame (quindi presumibilmente è un medico)
	{
		long lUserID = 0;
		AMLogin_GetUserID(&lUserID);

		long idMedico = CMediciSet().GetContatoreFromUserID(lUserID);
		if (idMedico > 0) //Posso proseguire solo se l'utente ha associato un record di emedici
		{
			userRequest request;
			strcpy(request.username, AMLogin_GetUsername());
			CUserService userService(theApp.m_sHttpServerRichiestaInfoUser, theApp.m_sHttpServerRichiestaUserSignature);
			userResponse response = userService.GetUserCode(request);
			if (strcmp(response.error, "") != 0) //Se ho errori di comunicazione con il server chiudo endox
			{
				CString message;
				message.Format("%s\r\n\r\n%s", response.error, theApp.GetMessageString(IDS_3L3N_COMMERR));
				theApp.AfxMessageBoxEndo(message);
				AMLogin_Logout();
				theApp.m_lUO = 0; // Sandro 16/11/2015 // RAS 201500080 //
				bReturn = FALSE;
			}
			else
			{
				bReturn = TRUE;
			}

			if (bReturn)
			{
				CString treLtreNCode = CString(response.code);

				if (treLtreNCode.GetLength() > 0) // Se ho codice 3l3n posso proseguire
				{
					CMediciSet().SetCodice(idMedico, treLtreNCode);

					// Sandro 12/09/2016 //
					if (CMediciSet().IsImmagineFirmaEmpty(idMedico))
					{
						userSignature response = userService.GetUserSignature(request);
						if (strcmp(response.szError, "") != 0)
						{
							CString message;
							message.Format("%s\r\n\r\n%s", response.szError, theApp.GetMessageString(IDS_IMMAGINEFIRMA_COMMERR));
							theApp.AfxMessageBoxEndo(message);
						}
						else
						{
							CString sImmagineFirmaOriginale = CString(response.szSignature);
							if (sImmagineFirmaOriginale.GetLength() > 0)
							{
								////////////////////////////////////////////////////////////////////////
								// DEVO ESSERE SICURO CHE L'IMMAGINE VENGA SALVATA NEL DB COME BITMAP //
								////////////////////////////////////////////////////////////////////////

								BOOL bOK = TRUE;

								BYTE* pImmagineFirmaOriginaleBuffer = NULL;

								DWORD dwImmaginefirmaOriginaleBufferLength = 0;

								CString sImmagineFirmaBmpBase64 = "";
								CString strFileName = theApp.m_sDirTemp + "\\" + CCustomDate(TRUE, TRUE).GetDate("%Y%m%d%H%M%S");
								CString strFileTmp = strFileName + ".xxx";
								CString strFileBmp = strFileName + ".bmp";

								// decodifico quello che ricevo da amremote in base64 //

								if (bOK)
								{
									bOK = FALSE;

									LPTSTR pImmagineFirmaOriginale = sImmagineFirmaOriginale.GetBuffer(sImmagineFirmaOriginale.GetLength());
									UINT iImmagineFirmaOriginaleSize = AmBase64_CalculateRequiredDecodeOutputBufferSize(pImmagineFirmaOriginale);
									pImmagineFirmaOriginaleBuffer = new BYTE[iImmagineFirmaOriginaleSize];
									dwImmaginefirmaOriginaleBufferLength = iImmagineFirmaOriginaleSize;
									bOK = (AmBase64_DecodeBuffer(pImmagineFirmaOriginale, sImmagineFirmaOriginale.GetLength(), (TCHAR*)pImmagineFirmaOriginaleBuffer) > 0);
									sImmagineFirmaOriginale.ReleaseBuffer();
								}

								// salvo su file quello che ho appena decodificato //

								if (bOK && (pImmagineFirmaOriginaleBuffer != NULL) && (dwImmaginefirmaOriginaleBufferLength > 0))
								{
									bOK = FALSE;

									HANDLE hFileXXX = CreateFile(strFileTmp, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, NULL);
									if (hFileXXX != INVALID_HANDLE_VALUE)
									{
										DWORD dwBytesWrite;
										bOK = WriteFile(hFileXXX, pImmagineFirmaOriginaleBuffer, dwImmaginefirmaOriginaleBufferLength, &dwBytesWrite, NULL);
									}
									CloseHandle(hFileXXX);
								}

								// riapro con le gdiplus il file appena salvato e lo salvo di nuovo in formato bmp //

								if (bOK)
								{
									bOK = FALSE;

									USES_CONVERSION;
									Gdiplus::Bitmap* pBitmap = (Gdiplus::Bitmap*)Gdiplus::Bitmap::FromFile(A2W(strFileTmp));
									if (pBitmap->GetLastStatus() == Gdiplus::Ok)
									{
										CLSID idClass;
										if (GetEncoderClsid(L"image/bmp", &idClass))
											bOK = (pBitmap->Save(T2W(strFileBmp), &idClass, NULL) == Gdiplus::Ok);

										delete pBitmap;
									}
								}

								// apro il file bmp e lo codifico in base64 //

								if (bOK)
								{
									bOK = FALSE;

									HANDLE hFile = CreateFile(strFileBmp, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
									if (hFile != INVALID_HANDLE_VALUE)
									{
										DWORD dwFileSize = GetFileSize(hFile, NULL);

										DWORD dwEncodeBufferLength = AmBase64_CalculateRequiredEncodeOutputBufferSize(dwFileSize);
										if (dwEncodeBufferLength < _FIRMA_BMP_MAX_LENGTH)
										{
											DWORD dwBytesRead;
											BYTE* pBufferFile = new BYTE[dwFileSize];
											if (ReadFile(hFile, (LPVOID)pBufferFile, dwFileSize, &dwBytesRead, NULL))
											{
												DWORD dwEncodeBufferLength = AmBase64_CalculateRequiredEncodeOutputBufferSize(dwFileSize);
												TCHAR* pBufferB64 = new TCHAR[dwEncodeBufferLength];
												ZeroMemory(pBufferB64, dwEncodeBufferLength * sizeof(TCHAR));
												AmBase64_EncodeBuffer((CHAR*)pBufferFile, dwFileSize, pBufferB64);
												sImmagineFirmaBmpBase64 = CString(pBufferB64);
												delete pBufferB64;

												bOK = TRUE;
											}
											delete pBufferFile;
										}
										else
										{
											theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMMAGINEFIRMA_TROPPOGRANDE), MB_ICONSTOP);
										}

										CloseHandle(hFile);
									}
								}

								//

								if (pImmagineFirmaOriginaleBuffer != NULL)
									delete pImmagineFirmaOriginaleBuffer;

								DeleteFile(strFileTmp);
								DeleteFile(strFileBmp);

								//

								if (bOK && (!sImmagineFirmaBmpBase64.IsEmpty()))
									CMediciSet().SetImmagineFirma(idMedico, sImmagineFirmaBmpBase64);
							}
						}
					}

					bReturn = TRUE;
				}
				else //Se non ho codice 3l3n chiudo endox
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_3L3N_NOCODE));
					AMLogin_Logout();
					theApp.m_lUO = 0; // Sandro 16/11/2015 // RAS 201500080 //
					bReturn = FALSE;
				}
			}
		}
		else
		{
			if (CUOSet().GetUsernameResponsabile(theApp.m_lUO).IsEmpty())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_3L3N_NOANAG));
				AMLogin_Logout();
				theApp.m_lUO = 0; // Sandro 16/11/2015 // RAS 201500080 //
				bReturn = FALSE;
			}
			else
			{
				bReturn = TRUE; // se non è un medico non mi interessa questo controllo
			}
		}
	}
	else
	{
		bReturn = TRUE; // se non è un medico non mi interessa questo controllo
	}

	return bReturn;
}

BOOL FleuryPossoModificare(CString& sMessaggio, CString sRicovero, CString sCodEsame)
{	
#ifdef _DEBUG
	return TRUE;
#endif

	// Sandro 13/01/2017 // richiesta via mail e telefonica di Paron Pilotto //

	if (theApp.m_bCentraleControlloQualita)
		return TRUE;

	//

	BOOL bReturn = FALSE;
	sMessaggio = "";

	if (!sRicovero.IsEmpty() && !sCodEsame.IsEmpty())
	{
		int n1 = sCodEsame.Find("_");
		if (n1 > 0)
		{
			int n2 = sCodEsame.Find("_", n1 + 1);
			if (n2 > 0)
			{
				// Luiz - 01/04/2019 - P3 - Correção para envio do Item de ficha correto
				CString sItem = sCodEsame.Mid(n1 + 1);
				sItem.Replace("_", "0");
				CString sSiglaUtente = "";
				// Sandro 31/05/2017 // con item a due cifre tornava messaggio di errore ficha/item nao encontrado //
				// while (sItem.GetLength() < 3)
				//	sItem += "0";
				//sItem += "00";

				long lUserID;
				AMLogin_GetUserID(&lUserID);
				if (CMediciSet().GetContatoreFromUserID(lUserID) > 0)
				{
					// se sono un medico devo usare il mio 3L3N //
					sSiglaUtente = CMediciSet().GetCodiceFromUserID(lUserID);

					//Julio Login SEGU
					/*if (sSiglaUtente.GetLength() > 3)
						sSiglaUtente = sSiglaUtente.Left(3);*/
				}
				else
				{
					// se non sono un medico uso il 3L3N della Tesi //
					//sSiglaUtente = CString("EQT496").Left(3);

					//Julio Login SEGU
					sSiglaUtente = "13551";
				}

				if (sSiglaUtente.GetLength() > 0) // Luiz - 01/04/2019 - P3 - Correção para acionamento do webservice
				{
					//sSiglaUtente = sSiglaUtente.Left(3);

					examRequest request;
					sprintf_s(request.szFicha, sRicovero);
					sprintf_s(request.szItem, sItem);
					sprintf_s(request.szSiglaUsuarioSistema, sSiglaUtente);
					sprintf_s(request.szIdSistema, "1"); // sempre 1, è endox //

					CExamService examService(theApp.m_sHttpServerRichiestaModificaStampa);
					examResponse response = examService.GetExamPodeSerAlteradoImpresso(request);
					if (strcmp(response.szCodigoDeErro, "0") == 0)
					{
						bReturn = (_strcmpi(response.szPodeAlterar, "true") == 0);

						if (!bReturn)
							sMessaggio = theApp.GetMessageString(IDS_FLEURY_ERROR_004);
					}
					else
					{
						sMessaggio = theApp.GetMessageString(IDS_FLEURY_ERROR_006) + "\n\n" + CString(response.szCodigoDeErro);
						theApp.AfxMessageBoxEndo(sMessaggio);
						if (CString(response.szPodeAlterar).IsEmpty())
							bReturn = TRUE;
					}
				}
				else
				{
					sMessaggio = theApp.GetMessageString(IDS_FLEURY_ERROR_002);
				}
			}
			else
			{
				sMessaggio = theApp.GetMessageString(IDS_FLEURY_ERROR_001);
			}
		}
		else
		{
			sMessaggio = theApp.GetMessageString(IDS_FLEURY_ERROR_001);
		}
	}
	else
	{
		sMessaggio = theApp.GetMessageString(IDS_FLEURY_ERROR_000);
	}

	return bReturn;
}

// Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
BOOL EnviaAnulaLiberaLaudo(CString& sMessaggio, CString sCodEsame, CString sMotivo)
{
	/*#ifdef _DEBUG
	return TRUE;
	#endif*/

	BOOL bReturn = FALSE;
	sMessaggio = "";

	if (!sCodEsame.IsEmpty())
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
					// Se é médico utiliza o 3L3N //
					sSiglaUtente = CMediciSet().GetCodiceFromUserID(lUserID);
					
					//Julio Login SEGU
					/*if (sSiglaUtente.GetLength() > 3)
						sSiglaUtente = sSiglaUtente.Left(3);*/
				}
				else
				{
					// Se NÃO é médico utiliza o 3L3N da Tesi //
					//sSiglaUtente = CString("EQT496").Left(3);

					//Julio Login SEGU
					sSiglaUtente = "13551";
				}

				if (sSiglaUtente.GetLength() > 0)
				{
					//Chamo a API da substituição de resultado
					examReplaceRequest request;
					sprintf_s(request.szFicha, sCodEsame.Left(10));
					sprintf_s(request.szItem, sItem);
					sprintf_s(request.szSiglaUsuarioSistema, sSiglaUtente);
					sprintf_s(request.szIdSistema, "1"); // sempre 1, è endox //
					sprintf_s(request.szMotivo, sMotivo); 

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
				else
				{
					sMessaggio = theApp.GetMessageString(IDS_FLEURY_ERROR_002);
				}
			}
			else
			{
				sMessaggio = theApp.GetMessageString(IDS_FLEURY_ERROR_001);
			}
		}
		else
		{
			sMessaggio = theApp.GetMessageString(IDS_FLEURY_ERROR_001);
		}
	}
	else
	{
		sMessaggio = theApp.GetMessageString(IDS_FLEURY_ERROR_000);
	}
	return bReturn;
}

BOOL FleuryPossoStampare(CString& sMessaggio, CString sRicovero, CString sCodEsame)
{
#ifdef _DEBUG
	return TRUE;
#endif

	BOOL bReturn = FALSE;
	sMessaggio = "";

	if (!sRicovero.IsEmpty() && !sCodEsame.IsEmpty())
	{
		int n1 = sCodEsame.Find("_");
		if (n1 > 0)
		{
			int n2 = sCodEsame.Find("_", n1 + 1);
			if (n2 > 0)
			{
				// Luiz - 01/04/2019 - P3 - Correção para envio do Item de ficha correto
				CString sItem = sCodEsame.Mid(n1 + 1);
				sItem.Replace("_", "0");
				CString sSiglaUtente = "";

				// Sandro 31/05/2017 // con item a due cifre tornava messaggio di errore ficha/item nao encontrado //
				// while (sItem.GetLength() < 3)
				//	sItem += "0";
				//sItem += "00";

				long lUserID;
				AMLogin_GetUserID(&lUserID);

				// Sandro 23/05/2017 //
				if (CMediciSet().GetContatoreFromUserID(lUserID) > 0)
				{
					// se sono un medico devo usare il mio 3L3N //

					sSiglaUtente = CMediciSet().GetCodiceFromUserID(lUserID);
					
					//Julio Login SEGU
					/*if (sSiglaUtente.GetLength() > 3)
						sSiglaUtente = sSiglaUtente.Left(3);*/
				}
				else
				{
					// se non sono un medico uso il 3L3N della Tesi //
					//sSiglaUtente = CString("EQT496").Left(3);

					//Julio Login SEGU
					sSiglaUtente = "13551";
				}

				if (sSiglaUtente.GetLength() > 0)
				{
					examRequest request;
					sprintf_s(request.szFicha, sRicovero);
					sprintf_s(request.szItem, sItem);
					sprintf_s(request.szSiglaUsuarioSistema, sSiglaUtente);
					sprintf_s(request.szIdSistema, "1"); // sempre 1, è endox //

					CExamService examService(theApp.m_sHttpServerRichiestaModificaStampa);
					examResponse response = examService.GetExamPodeSerAlteradoImpresso(request);
					if (strcmp(response.szCodigoDeErro, "0") == 0)
					{
						bReturn = (_strcmpi(response.szPodeImprimir, "true") == 0);

						if (!bReturn)
							sMessaggio = theApp.GetMessageString(IDS_FLEURY_ERROR_005);
					}
					else
					{
						sMessaggio = theApp.GetMessageString(IDS_FLEURY_ERROR_007) + " (" + sRicovero + " - " + sItem + ")\n\n" + CString(response.szCodigoDeErro);
					}
				}
				else
				{
					sMessaggio = theApp.GetMessageString(IDS_FLEURY_ERROR_002);
				}
			}
			else
			{
				sMessaggio = theApp.GetMessageString(IDS_FLEURY_ERROR_001);
			}
		}
		else
		{
			sMessaggio = theApp.GetMessageString(IDS_FLEURY_ERROR_001);
		}
	}
	else
	{
		sMessaggio = theApp.GetMessageString(IDS_FLEURY_ERROR_000);
	}

	return bReturn;
}

BOOL FleuryCercaFicha(CString sFicha, CString& sErrore, CString& sServer, CString& sUO, CString& sEndpointRemoteCommunication)
{
#ifdef _DEBUG
	return TRUE;
#endif
	AfxGetApp()->BeginWaitCursor();

	BOOL bIsCanceled = FALSE;

	sErrore = "";
	sServer = "";
	sUO = "";
	sEndpointRemoteCommunication = "";

	sFicha.Replace("'", "''");
	sFicha.Trim();
	if (!sFicha.IsEmpty())
	{
		theApp.m_sHttpServerRicercaFicha.Trim();
		if (!theApp.m_sHttpServerRicercaFicha.IsEmpty())
		{
			findfichaRequest request;
			sprintf_s(request.szFicha, sFicha);

			CFindFichaService findfichaService(theApp.m_sHttpServerRicercaFicha);
			findfichaResponse response = findfichaService.GetFichaServerEndpoint(request);
			if (strcmp(response.szError, "") == 0)
			{
				sServer = CString(response.szServer);
				sUO = CString(response.szUO).Trim();
				sEndpointRemoteCommunication = CString(response.szEndpointRemoteCommunication);
				bIsCanceled = (atol(response.szIsCanceled) > 0 ? TRUE : FALSE);
			}
			else
			{
				sErrore = theApp.GetMessageString(IDS_FLEURY_ERROR_009) + "\n\n" + CString(response.szError);
			}
		}
		else
		{
			sErrore = theApp.GetMessageString(IDS_CONFIGURAZIONEVUOTA) + "\nLogin - Http server ricerca ficha";
		}
	}
	else
	{
		sErrore = theApp.GetMessageString(IDS_FLEURY_ERROR_008);
	}

	AfxGetApp()->EndWaitCursor();
	return sErrore.IsEmpty() && !bIsCanceled;
}

BOOL FleuryCercaItensDaFicha(CString sFicha, CString& sErrore, CString& sServer, CString& sUO, CString& sEndpointRemoteCommunication, long& lArrayCount)
{
	AfxGetApp()->BeginWaitCursor();

	sErrore = "";
	sServer = "";
	sUO = "";
	sEndpointRemoteCommunication = "";
	lArrayCount = 0;

	sFicha.Replace("'", "''");
	sFicha.Trim();
	if (!sFicha.IsEmpty())
	{
		theApp.m_sHttpServerRicercaFicha.Trim();
		if (!theApp.m_sHttpServerRicercaFicha.IsEmpty())
		{
			findfichaRequest request;
			sprintf_s(request.szFicha, sFicha + "|" + CUOSet().GetCodiceIntegrazione(theApp.m_lUO, FALSE));

			CFindFichaService findfichaService(theApp.m_sHttpServerRicercaFicha);
			findfichaResponse response = findfichaService.GetFichaServerEndpoint(request);
			if (strcmp(response.szError, "") == 0)
			{
				sServer = CString(response.szServer);
				sUO = CString(response.szUO).Trim();
				sEndpointRemoteCommunication = CString(response.szEndpointRemoteCommunication);
				lArrayCount = atol(response.szIsCanceled);
			}
			else
			{
				sErrore = theApp.GetMessageString(IDS_FLEURY_ERROR_009) + "\n\n" + CString(response.szError);
			}
		}
		else
		{
			sErrore = theApp.GetMessageString(IDS_CONFIGURAZIONEVUOTA) + "\nLogin - Http server ricerca itens ficha";
		}
	}
	else
	{
		sErrore = theApp.GetMessageString(IDS_FLEURY_ERROR_008);
	}

	AfxGetApp()->EndWaitCursor();
	return sErrore.IsEmpty();
}

BOOL FleuryGetPazienteEsame(CWnd *pParent, CEsamiView *pEsamiView, CString sEndpoint, CString sFicha, CString& sErrore, long& lIDPaziente, long& lIDEsame, BOOL bRecursive)
{
	AfxGetApp()->BeginWaitCursor();

	sErrore = "";
	lIDPaziente = 0;
	lIDEsame = 0;

	sFicha.Replace("'", "''");
	sFicha.Trim();
	if (!sFicha.IsEmpty())
	{
		sEndpoint.Trim();
		if (!sEndpoint.IsEmpty())
		{
			getpatientexamdataRequest request1;
			sprintf_s(request1.szFicha, sFicha);
			sprintf_s(request1.szCodiceUnita, theApp.m_sCodiceUnitaFleury);

			DWORD time0 = timeGetTime();
			CGetPatientExamDataService getpatientexamdataService(sEndpoint);
			getpatientexamdataResponse response1 = getpatientexamdataService.GetPatientExamData(request1);
			XWriteLogTime("      GetPatientExamData", timeGetTime() - time0, 0);

			if (strcmp(response1.szError, "") == 0)
			{
				if (strcmp(response1.szFromWorklist, "1") == 0)
				{
					sErrore = "FROM WORKLIST";
					return TRUE;
				}

				DWORD time1 = timeGetTime();
				long lIDUO = CUOSet().GetUOFromCodiceIntegrazione(response1.szUO);
				XWriteLogTime("      GetUOFromCodiceIntegrazione", timeGetTime() - time1, 0);

				if (lIDUO > 0)
				{
					if (bRecursive && atol(response1.szSuperlocked) > 0)
					{
						CString sMensagemCabecalho = theApp.GetMessageString(IDS_FLEURY_ERROR_023);

						CFleurySceltaRiaperturaDlg dlg(pParent, sFicha);
						if (dlg.DoModal() == IDOK)
						{
							if (dlg.m_bImportarExame)
							{
								CWaitFleuryTransferitoDlg *splashDlg = NULL;
								splashDlg = new CWaitFleuryTransferitoDlg();
								splashDlg->CreateModelessDialog(pParent);
							}
							else
							{
								delete response1.pSzRefertoTestoRtf;
								response1.pSzRefertoTestoRtf = NULL;

								delete response1.pSzRefertoTestoTxt;
								response1.pSzRefertoTestoTxt = NULL;

								delete response1.pSzRefertoTestoHtml;
								response1.pSzRefertoTestoHtml = NULL;

								CString sPdfPath = "";
								int iVersione = 0;
								int iTipo = -1;

								if (dlg.m_bImprimirLaudo && dlg.m_bImprimirImagens)
								{
									theApp.AfxMessageBoxEndo(sMensagemCabecalho, MB_OK);

									//cerca la versione piu grande del tipo corretto del referto
									for (int i = 0; i < response1.lNumPdfs; i++)
									{
										if (response1.pStructPdfs[i].lTipo == 0)
										{
											if (response1.pStructPdfs[i].lVersione > iVersione)
											{
												iVersione = response1.pStructPdfs[i].lVersione;
											}
										}
									}
									//

									for (int i = 0; i < response1.lNumPdfs; i++)
									{
										if (response1.pStructPdfs[i].lTipo == 0)
										{
											if (response1.pStructPdfs[i].lVersione = iVersione)
											{
												sPdfPath = response1.pStructPdfs[i].szFullPathPdf;
												break;
											}
										}
									}

									//apri il file								
									if (!sPdfPath.IsEmpty())
									{
										CString action = "open";
										ShellExecute(NULL, action, sPdfPath, NULL, NULL, SW_SHOW);
										getchar();
									}
									else
									{
										sErrore = theApp.GetMessageString(IDS_FLEURY_ERROR_022);
									}

									//cerca la versione piu grande del tipo corretto del referto
									for (int i = 0; i < response1.lNumPdfs; i++)
									{
										if (response1.pStructPdfs[i].lTipo == 1)
										{
											if (response1.pStructPdfs[i].lVersione > iVersione)
											{
												iVersione = response1.pStructPdfs[i].lVersione;
											}
										}
									}
									//

									for (int i = 0; i < response1.lNumPdfs; i++)
									{
										if (response1.pStructPdfs[i].lTipo == 1)
										{
											if (response1.pStructPdfs[i].lVersione = iVersione)
											{
												sPdfPath = response1.pStructPdfs[i].szFullPathPdf;
												break;
											}
										}
									}

									//apri il file								
									if (!sPdfPath.IsEmpty())
									{
										CString action = "open";
										ShellExecute(NULL, action, sPdfPath, NULL, NULL, SW_SHOW);
										getchar();
									}
									else
									{
										sErrore = theApp.GetMessageString(IDS_FLEURY_ERROR_022);
									}

									return sErrore.IsEmpty();
								}

								else //usuario nao selecionou nada
								{
									sErrore = "";
									return FALSE;
								}

								if (dlg.m_bImprimirLaudo)
									iTipo = 0;

								else if (dlg.m_bImprimirImagens)
									iTipo = 1;

								//cerca la versione piu grande del tipo corretto del referto
								for (int i = 0; i < response1.lNumPdfs; i++)
								{
									if (response1.pStructPdfs[i].lTipo == iTipo)
									{
										if (response1.pStructPdfs[i].lVersione > iVersione)
										{
											iVersione = response1.pStructPdfs[i].lVersione;
										}
									}
								}
								//

								for (int i = 0; i < response1.lNumPdfs; i++)
								{
									if (response1.pStructPdfs[i].lTipo == iTipo)
									{
										if (response1.pStructPdfs[i].lVersione = iVersione)
										{
											sPdfPath = response1.pStructPdfs[i].szFullPathPdf;
											break;
										}
									}
								}

								//apri il file								
								if (!sPdfPath.IsEmpty())
								{
									CString action = "open";
									theApp.AfxMessageBoxEndo(sMensagemCabecalho, MB_OK);
									ShellExecute(NULL, action, sPdfPath, NULL, NULL, SW_SHOW);
									getchar();

									sErrore = "";
									return FALSE;
								}
								else
								{
									sErrore = theApp.GetMessageString(IDS_FLEURY_ERROR_022);
									return FALSE;
								}
								//
							}
						}
						else
						{
							sErrore = "";
							return FALSE;
						}
					}

					//

					//Julio 30/11/2017 Centralizacao nao importar exame conjugado
					CString sRefertoConiugatoPrincipale = CString(response1.szRefertoConiugatoPrincipale);
					CString sRefertoConiugatoSecondario = CString(response1.szRefertoConiugatoSecondario);

					if (bRecursive && sFicha == sRefertoConiugatoSecondario)
					{
						CString sMainFicha = sRefertoConiugatoPrincipale.Left(10);
						CString sMainItem = sRefertoConiugatoPrincipale;
						sMainItem.Replace(sMainItem.Left(11), "");
						sMainItem.Replace("_", "0");

						sErrore.Format("A ficha procurada está atualmente conjugada em outro exame. Por favor pesquise pelo exame principal (Ficha %s Item %s)", sMainFicha, sMainItem);

						return FALSE;
					}

					if (bRecursive && !sRefertoConiugatoPrincipale.IsEmpty() && !sRefertoConiugatoSecondario.IsEmpty())
					{
						CString sOtherFicha = (sFicha == sRefertoConiugatoPrincipale) ? sRefertoConiugatoSecondario : sRefertoConiugatoPrincipale;

						CString sErrore;
						CString sServer;
						CString sUO;
						CString sEndpointRemoteCommunication;

						CString sOtherErrore = "";
						long lIDOtherEsame = 0;
						long lIDOtherPaziente = 0;

						if (FleuryCercaFicha(sOtherFicha, sOtherErrore, sServer, sUO, sEndpointRemoteCommunication))
						{
							if (FleuryGetPazienteEsame(pParent, pEsamiView, sEndpoint, sOtherFicha, sOtherErrore, lIDOtherPaziente, lIDOtherEsame, FALSE))
							{
								if ((lIDOtherEsame > 0) && (lIDOtherPaziente > 0))
								{
									if (!FleurySetEsameTrasferitoAltraSede(sEndpointRemoteCommunication, sOtherFicha, sOtherErrore))
									{
										CString sFilterDel;
										sFilterDel.Format("CONTATORE = %li", lIDOtherEsame);

										CEsamiSet setExamDel;
										setExamDel.SetOpenFilter(sFilterDel);
										if (setExamDel.OpenRecordset("OnPazienteGoto"))
										{
											if (!setExamDel.IsEOF())
												setExamDel.DeleteRecordset("OnPazienteGoto");

											setExamDel.CloseRecordset("OnPazienteGoto");
										}
									}

									if (!sOtherErrore.IsEmpty())
										theApp.AfxMessageBoxEndo(sOtherErrore);
								}
								else
								{
									sErrore.Format("Não foi possivel inserir paciente/exame para ficha %s \n %s", sOtherFicha, sOtherErrore);
									return FALSE;
								}
							}
							else
							{
								sErrore.Format("Não foi possivel importar ficha %s \n %s", sOtherFicha, sOtherErrore);
								return FALSE;
							}
						}
						else
						{
							sErrore.Format("Não foi possivel encontrar ficha %s \n %s", sOtherFicha, sOtherErrore);
							return FALSE;
						}
					}

					//

					CString sFilter;

					//

					DWORD time2 = timeGetTime();

					CPazientiSet setPaz1;
					sFilter.Format("ASSIDEN = '%s'", response1.szAssIden);
					setPaz1.SetOpenFilter(sFilter);
					if (setPaz1.OpenRecordset("FleuryGetPazienteEsame"))
					{
						if (setPaz1.IsEOF())
						{
							if (setPaz1.AddNewRecordset("FleuryGetPazienteEsame"))
								if (setPaz1.UpdateRecordset("FleuryGetPazienteEsame"))
									lIDPaziente = setPaz1.GetLastAdd();
						}
						else
						{
							lIDPaziente = setPaz1.m_lContatore;
						}

						setPaz1.CloseRecordset("FleuryGetPazienteEsame");
					}

					XWriteLogTime("      CPazientiSet 1", timeGetTime() - time2, 0);

					//

					if (lIDPaziente > 0)
					{
						DWORD time3 = timeGetTime();

						CPazientiSet setPaz2;
						sFilter.Format("CONTATORE = %li", lIDPaziente);
						setPaz2.SetOpenFilter(sFilter);
						if (setPaz2.OpenRecordset("FleuryGetPazienteEsame"))
						{
							if (setPaz2.EditRecordset("FleuryGetPazienteEsame"))
							{
								setPaz2.m_sAssIden = CString(response1.szAssIden);
								setPaz2.m_sCognome = CString(response1.szCognome);
								setPaz2.m_sCognome2 = CString(response1.szCognome2);
								setPaz2.m_sNome = CString(response1.szNome);
								setPaz2.m_lNatoIlCustom = atol(response1.szNatoIlCustom);
								setPaz2.m_sVia = CString(response1.szVia);
								setPaz2.m_sCitta = CString(response1.szCitta);
								setPaz2.m_sProvincia = CString(response1.szProvincia);
								setPaz2.m_sTelefono1 = CString(response1.szTelefono1);
								setPaz2.m_sTelefono2 = CString(response1.szTelefono2);
								setPaz2.m_sCellulare1 = CString(response1.szCellulare1);
								setPaz2.m_sCellulare2 = CString(response1.szCellulare2);
								setPaz2.m_lSessoPaz = atol(response1.szSesso);



								if (setPaz2.UpdateRecordset("FleuryGetPazienteEsame"))
								{
									XWriteLogTime("      CPazientiSet 2", timeGetTime() - time3, 0);

									DWORD time42 = timeGetTime();

									CEsamiSet setExa1;
									sFilter.Format("CODESAME = '%s'", sFicha);
									setExa1.SetOpenFilter(sFilter);
									if (setExa1.OpenRecordset("FleuryGetPazienteEsame"))
									{
										if (setExa1.IsEOF())
										{
											if (setExa1.AddNewRecordset("FleuryGetPazienteEsame"))
												if (setExa1.UpdateRecordset("FleuryGetPazienteEsame"))
													lIDEsame = setExa1.GetLastAdd();
										}
										else
										{
											lIDEsame = setExa1.m_lContatore;
										}

										setExa1.CloseRecordset("FleuryGetPazienteEsame");
									}

									XWriteLogTime("      CEsamiSet 1", timeGetTime() - time42, 0);

									if (lIDEsame > 0)
									{
										DWORD time43 = timeGetTime();

										CEsamiSet setExa2;
										sFilter.Format("CONTATORE = %li", lIDEsame);
										setExa2.SetOpenFilter(sFilter);
										if (setExa2.OpenRecordset("FleuryGetPazienteEsame"))
										{
											if (setExa2.EditRecordset("FleuryGetPazienteEsame"))
											{
												long lIDTipoEsame = CTipoEsameSet().FleuryTrans(response1.szTipoEsameSigla, response1.szTipoEsameDescrizione);

												setExa2.m_bEliminato = FALSE;
												setExa2.m_sRicovero = CString(response1.szRicovero);
												setExa2.m_sCodEsame = CString(response1.szCodEsame);
												setExa2.m_lPaziente = lIDPaziente;
												setExa2.m_lIDEsame = lIDTipoEsame;
												setExa2.m_lData = atol(response1.szData);
												setExa2.m_lMedico = CMediciSet().FleuryTrans(response1.szMedicoCognome, response1.szMedicoNome);
												setExa2.m_sAppunti = CString(response1.szAppunti);
												setExa2.m_sProgressivoAnno = GetContatoreAnnuale(lIDTipoEsame);
												setExa2.m_sCodicePrenotazione = GetCodicePrenotazione(lIDTipoEsame);
												setExa2.m_sInvMedico = CString(response1.szInvMedico);
												setExa2.m_fPeso = (float)atof(response1.szPeso);
												setExa2.m_fAltezza = (float)atof(response1.szAltezza);
												setExa2.m_fBMI = (float)atof(response1.szBMI);
												setExa2.m_fMisuraA = (float)atof(response1.szMisuraA);
												setExa2.m_fMisuraB = (float)atof(response1.szMisuraB);
												setExa2.m_fMisuraC = (float)atof(response1.szMisuraC);
												setExa2.m_fVolume = (float)atof(response1.szVolume);
												setExa2.m_lIDVersione = GetIDVersione(lIDTipoEsame);
												setExa2.m_lIDSedeEsame = theApp.m_lIDSedeEsameDefault;
												setExa2.m_bLocked = (atol(response1.szLocked) > 0 ? TRUE : FALSE); //Julio 22/11/2017
												setExa2.m_lIdUtenteLock = CUtentiSet().FleuryTrans(response1.szUtenteLock);
												setExa2.m_sDataOraLock = CString(response1.szDataOraLock);
												setExa2.m_bSuperLocked = (atol(response1.szSuperlocked) > 0 ? TRUE : FALSE); //Julio 22/11/2017
												setExa2.m_lIdUtenteSuperLock = CUtentiSet().FleuryTrans(response1.szUtenteSuperlock);
												setExa2.m_sDataOraSuperLock = CString(response1.szDataOraSuperlock);
												setExa2.m_sDataOraSuperLockPrimo = CString(response1.szDataOraSuperlockPrimo);
												// setExa2.m_lUO = lIDUO; // non serve a niente //
												setExa2.m_sRefertoTestoRtf = CString(response1.pSzRefertoTestoRtf);
												setExa2.m_sRefertoTestoTxt = CString(response1.pSzRefertoTestoTxt);
												setExa2.m_sRefertoTestoHtml = CString(response1.pSzRefertoTestoHtml);
												setExa2.m_lFrazioneEiezione = atol(response1.szFrazioneEiezione);
												setExa2.m_lIDUltimaChecklistUsata = atol(response1.szIDUltimaChecklistUsata);
												setExa2.m_sFCMassima = CString(response1.szFCMassima);
												setExa2.m_sFCSubmassima = CString(response1.szFCSubmassima);
												setExa2.m_lIDProtocolloUsato = CProtocolloCardioSet().FleuryTrans(response1.szProtocolloUsato);
												setExa2.m_sRefertoConiugatoPrincipale = CString(response1.szRefertoConiugatoPrincipale);
												setExa2.m_sRefertoConiugatoSecondario = CString(response1.szRefertoConiugatoSecondario);
												setExa2.m_sFleuryTrasferito = ""; //Julio 22/11/2017
												setExa2.m_sFleuryEndpointRemoto = sEndpoint;
												setExa2.m_bNonSbloccabile = (atol(response1.szEsameNonSbloccabile) > 0 ? TRUE : FALSE); //Julio 29/08/2018

												setExa2.m_setEP.m_sTesto000 = CString(response1.szTesto000);
												setExa2.m_setEP.m_sTesto001 = CString(response1.szTesto001);
												setExa2.m_setEP.m_sTesto002 = CString(response1.szTesto002);
												setExa2.m_setEP.m_sTesto003 = CString(response1.szTesto003);
												setExa2.m_setEP.m_sTesto004 = CString(response1.szTesto004);
												setExa2.m_setEP.m_sTesto005 = CString(response1.szTesto005);
												setExa2.m_setEP.m_sTesto094 = CString(response1.szTesto094);
												setExa2.m_setEP.m_sTesto095 = CString(response1.szTesto095);
												setExa2.m_setEP.m_sTesto096 = CString(response1.szTesto096);
												setExa2.m_setEP.m_sTesto097 = CString(response1.szTesto097);
												setExa2.m_setEP.m_sTesto098 = CString(response1.szTesto098);
												setExa2.m_setEP.m_sTesto099 = CString(response1.szTesto099);

												setExa2.m_setEM.m_lCELULASACONTAR = atol(response1.structMielogramma.szCELULASACONTAR);
												setExa2.m_setEM.m_lHISTIOCITOS = atol(response1.structMielogramma.szHISTIOCITOS);
												setExa2.m_setEM.m_lMACROFAGOS = atol(response1.structMielogramma.szMACROFAGOS);
												setExa2.m_setEM.m_lMASTOCITOS = atol(response1.structMielogramma.szMASTOCITOS);
												setExa2.m_setEM.m_lNPROM = atol(response1.structMielogramma.szNPROM);
												setExa2.m_setEM.m_lNMIEL = atol(response1.structMielogramma.szNMIEL);
												setExa2.m_setEM.m_lNMETAM = atol(response1.structMielogramma.szNMETAM);
												setExa2.m_setEM.m_lNBAST = atol(response1.structMielogramma.szNBAST);
												setExa2.m_setEM.m_lNSEGM = atol(response1.structMielogramma.szNSEGM);
												setExa2.m_setEM.m_lPROERITRO = atol(response1.structMielogramma.szPROERITRO);
												setExa2.m_setEM.m_lERITROBASO = atol(response1.structMielogramma.szERITROBASO);
												setExa2.m_setEM.m_lERITPOLICRO = atol(response1.structMielogramma.szERITPOLICRO);
												setExa2.m_setEM.m_lERITROORTO = atol(response1.structMielogramma.szERITROORTO);
												setExa2.m_setEM.m_lBLASTOS = atol(response1.structMielogramma.szBLASTOS);
												setExa2.m_setEM.m_lOUTROS = atol(response1.structMielogramma.szOUTROS);
												setExa2.m_setEM.m_lEPROM = atol(response1.structMielogramma.szEPROM);
												setExa2.m_setEM.m_lEMIEL = atol(response1.structMielogramma.szEMIEL);
												setExa2.m_setEM.m_lEMETAM = atol(response1.structMielogramma.szEMETAM);
												setExa2.m_setEM.m_lEBAST = atol(response1.structMielogramma.szEBAST);
												setExa2.m_setEM.m_lESEGM = atol(response1.structMielogramma.szESEGM);
												setExa2.m_setEM.m_lLINFOCITO = atol(response1.structMielogramma.szLINFOCITO);
												setExa2.m_setEM.m_lMONOCITO = atol(response1.structMielogramma.szMONOCITO);
												setExa2.m_setEM.m_lPLASMOCITO = atol(response1.structMielogramma.szPLASMOCITO);
												setExa2.m_setEM.m_lBSEGM = atol(response1.structMielogramma.szBSEGM);
												setExa2.m_setEM.m_sMGC = CString(response1.structMielogramma.szMGC);

												delete response1.pSzRefertoTestoRtf;
												response1.pSzRefertoTestoRtf = NULL;

												delete response1.pSzRefertoTestoTxt;
												response1.pSzRefertoTestoTxt = NULL;

												delete response1.pSzRefertoTestoHtml;
												response1.pSzRefertoTestoHtml = NULL;

												if (setExa2.UpdateRecordset("FleuryGetPazienteEsame"))
												{
													XWriteLogTime("      CEsamiSet 2", timeGetTime() - time43, 0);

													// codici classificazione diagnostica //

													DWORD time5 = timeGetTime();

													for (int i = 0; i < response1.lNumEsamiCodiciClassDiagnost; i++)
													{
														long lIDCodClaDia = CCodiciClassificazioneDiagnostSet().FleuryTrans(response1.pStructEsamiCodiciClassDiagnost[i].szCodice, response1.pStructEsamiCodiciClassDiagnost[i].szDescrizione);

														if (lIDCodClaDia > 0)
															CEsamiCodiciClassDiagnostSet().AddRecord(lIDEsame, lIDCodClaDia);
													}

													XWriteLogTime("      CEsamiCodiciClassDiagnostSet", timeGetTime() - time5, 0);

													// protocolli cardio //

													DWORD time6 = timeGetTime();

													for (int i = 0; i < response1.lNumProtocollo; i++)
													{
														long lFase = atol(response1.pStructProtocollo[i].szProtocolloFase);
														switch (lFase)
														{
														case PROTOCOLLO_FASE_PRIMA:
														case PROTOCOLLO_FASE_DOPO:
														{
															long lIDProtocollo = CProtocolloCardioSet().GetIDFromFase(lFase);
															if (lIDProtocollo > 0)
															{
																long lIDColonna = CProtocolloColonneSet().FleuryTrans(lIDProtocollo, response1.pStructProtocollo[i].szColonnaDescrizione);
																if (lIDColonna > 0)
																	CProtocolloEsamiSet().AddEdtRow(lIDEsame, lIDProtocollo, lIDColonna, atol(response1.pStructProtocollo[i].szNumeroRiga), response1.pStructProtocollo[i].szValore);
															}
															break;
														}
														case PROTOCOLLO_FASE_DURANTE:
														{
															long lIDProtocollo = CProtocolloCardioSet().FleuryTrans(response1.pStructProtocollo[i].szProtocolloDescrizione);
															if (lIDProtocollo > 0)
															{
																long lIDColonna = CProtocolloColonneSet().FleuryTrans(lIDProtocollo, response1.pStructProtocollo[i].szColonnaDescrizione);
																if (lIDColonna > 0)
																	CProtocolloEsamiSet().AddEdtRow(lIDEsame, lIDProtocollo, lIDColonna, atol(response1.pStructProtocollo[i].szNumeroRiga), response1.pStructProtocollo[i].szValore);
															}
															break;
														}
														}
													}

													XWriteLogTime("      CProtocolloEsamiSet", timeGetTime() - time6, 0);

													// tabella ecocardio //

													DWORD time7 = timeGetTime();

													for (int i = 0; i < response1.lNumEcocardio; i++)
													{
														long lIDStruttura = CTabellaStruttureSet().FleuryTrans(lIDTipoEsame, response1.pStructEcocardio[i].szStruttura);
														if (lIDStruttura > 0)
														{
															long lIDParametro = CTabellaParametriSet().FleuryTrans(lIDStruttura, response1.pStructEcocardio[i].szParametro);
															if (lIDParametro > 0)
																CTabellaEsamiSet().AddRow(lIDEsame, lIDParametro, (float)atof(response1.pStructEcocardio[i].szValore));
														}
													}

													XWriteLogTime("      CTabellaEsamiSet", timeGetTime() - time7, 0);

													// documenti //

													DWORD time8 = timeGetTime();

													//Julio Remove old Documents
													CString sQueryDoc;
													sQueryDoc.Format("UPDATE DOCUMENTI SET CANCELLATO=1 WHERE IDESAME=%li", lIDEsame);
													theApp.m_dbEndox.ExecuteSQL(sQueryDoc);
													//


													if (response1.lNumDocuments > 0)
													{
														CMyDocManager manDocuments;
														for (int i = 0; i < response1.lNumDocuments; i++)
															manDocuments.ImportDocRemoto(lIDPaziente, lIDEsame, response1.pStructDocuments[i].lVersione, response1.pStructDocuments[i].szData, response1.pStructDocuments[i].lTipo, response1.pStructDocuments[i].szDescrizione, response1.pStructDocuments[i].szUtente, response1.pStructDocuments[i].szDataPersonalizzabile, response1.pStructDocuments[i].szEstensione, response1.pStructDocuments[i].szNomeFileOriginale, response1.pStructDocuments[i].bDaEsportare, response1.pStructDocuments[i].szFullPathDocument);
													}

													XWriteLogTime("      CMyDocManager", timeGetTime() - time8, 0);

													// immagini //

													DWORD time9 = timeGetTime();

													//Julio Remove old Imamges
													CString sQueryImm;
													sQueryImm.Format("UPDATE IMMAGINI SET ELIMINATO=1 WHERE IDESAME=%li", lIDEsame);
													theApp.m_dbEndox.ExecuteSQL(sQueryImm);
													//
													if (response1.lNumImages > 0)
													{
														CImgManager manImages(theApp.m_sPathImageOD, &theApp.m_dbEndox);
														for (int i = 0; i < response1.lNumImages; i++)
														{
															manImages.ImportImgRemote(lIDPaziente, lIDEsame, theApp.m_sNomeImpianto, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, response1.pStructImages[i].lOrdine, response1.pStructImages[i].lVersione, response1.pStructImages[i].szEstensioneImm, response1.pStructImages[i].szEstensioneMin, response1.pStructImages[i].lFormatoImm, response1.pStructImages[i].lFormatoMin, response1.pStructImages[i].lTipo, response1.pStructImages[i].szNote, response1.pStructImages[i].szDataOra, response1.pStructImages[i].lOrdineStampata, response1.pStructImages[i].szFullPathImm, response1.pStructImages[i].szFullPathMin);
														}
													}

													XWriteLogTime("      CImgManager", timeGetTime() - time9, 0);

													// pdf //

													DWORD time10 = timeGetTime();

													if (response1.lNumPdfs > 0)
													{
														CPdfManager manPdfs;
														for (int i = 0; i < response1.lNumPdfs; i++)
															manPdfs.ImportPdfRemoto(lIDPaziente, lIDEsame, response1.pStructPdfs[i].lVersione, response1.pStructPdfs[i].szData, response1.pStructPdfs[i].lTipo, response1.pStructPdfs[i].szEstensione, response1.pStructPdfs[i].szNote, response1.pStructPdfs[i].lVersioneReferto, response1.pStructPdfs[i].bFitToPage, response1.pStructPdfs[i].szClassificazione, response1.pStructPdfs[i].lInviareACarestream, response1.pStructPdfs[i].szFullPathPdf);
													}

													XWriteLogTime("      CPdfManager", timeGetTime() - time10, 0);
												}
												else
												{
													sErrore = theApp.GetMessageString(IDS_FLEURY_ERROR_017); // problema salvataggio esame
												}
											}
											else
											{
												sErrore = theApp.GetMessageString(IDS_FLEURY_ERROR_016); // problema creazione nuovo esame
											}

											setExa2.CloseRecordset("FleuryGetPazienteEsame");
										}
										else
										{
											sErrore = theApp.GetMessageString(IDS_FLEURY_ERROR_015); // problema apertura tabella esami
										}
									}
									else
									{
										sErrore = theApp.GetMessageString(IDS_FLEURY_ERROR_019); // problema ricerca / inserimento esame
									}
								}
								else
								{
									sErrore = theApp.GetMessageString(IDS_FLEURY_ERROR_014); // problema aggiornamento paziente
								}
							}
							else
							{
								sErrore = theApp.GetMessageString(IDS_FLEURY_ERROR_013); // problema modifica paziente
							}

							setPaz2.CloseRecordset("FleuryGetPazienteEsame");
						}
						else
						{
							sErrore = theApp.GetMessageString(IDS_FLEURY_ERROR_012); // problema ricerca paziente
						}
					}
					else
					{
						sErrore = theApp.GetMessageString(IDS_FLEURY_ERROR_011); // problema ricerca / inserimento paziente
					}

					CExtOrdiniSet setOrdini1;
					long lIDOrdini = 0;

					sFilter.Format("ORDERNUMBER = '%s'", sFicha);
					setOrdini1.SetOpenFilter(sFilter);
					if (setOrdini1.OpenRecordset("FleuryGetPazienteEsame"))
					{
						if (setOrdini1.IsEOF())
						{
							if (setOrdini1.AddNewRecordset("FleuryGetPazienteEsame"))
								if (setOrdini1.UpdateRecordset("FleuryGetPazienteEsame"))
									lIDOrdini = setOrdini1.GetLastAdd();
						}
						else
						{
							lIDOrdini = 0;
							//Julio: 03/05/2018 CAMPI AGGIUNTIVI						
							CRecordAddSP mySP;

							long lIDCampiAggiuntivi = mySP.Execute("EXT_ORDINI_CAMPIAGGIUNTIVI", "ID");
							if (lIDCampiAggiuntivi > 0)
							{
								CString sQuery;
								sQuery.Format("UPDATE EXT_ORDINI_CAMPIAGGIUNTIVI SET Tabella = 'DATA', Campo = 'PATIENTIDALT', Valore = '%s', IdRichiesta = %li WHERE ID=%li",
									CString(response1.szIdPazienteAlt), setOrdini1.m_lID, lIDCampiAggiuntivi);

								theApp.m_dbEndox.ExecuteSQL(sQuery);
							}

							long lIDCampiAggiuntivi2 = mySP.Execute("EXT_ORDINI_CAMPIAGGIUNTIVI", "ID");
							if (lIDCampiAggiuntivi2 > 0)
							{
								CString sQuery;
								sQuery.Format("UPDATE EXT_ORDINI_CAMPIAGGIUNTIVI SET Tabella = 'DATA', Campo = 'PLACERORDERNUMBERCARESTREAM', Valore = '%s', IdRichiesta = %li WHERE ID=%li",
									CString(response1.szPlaceOrderNumberCarestream), setOrdini1.m_lID, lIDCampiAggiuntivi2);

								theApp.m_dbEndox.ExecuteSQL(sQuery);
							}

							long lIDCampiAggiuntivi3 = mySP.Execute("EXT_ORDINI_CAMPIAGGIUNTIVI", "ID");
							if (lIDCampiAggiuntivi3 > 0)
							{
								CString sQuery;
								sQuery.Format("UPDATE EXT_ORDINI_CAMPIAGGIUNTIVI SET Tabella = 'DATA', Campo = 'PRONTUARIO', Valore = '%s', IdRichiesta = %li WHERE ID=%li",
									CString(response1.szProntuario), setOrdini1.m_lID, lIDCampiAggiuntivi3);

								theApp.m_dbEndox.ExecuteSQL(sQuery);
							}
							//
						}

						setOrdini1.CloseRecordset("FleuryGetPazienteEsame");
					}
					if (lIDOrdini > 0)
					{
						//Julio: 03/05/2018 CAMPI AGGIUNTIVI						
						CRecordAddSP mySP;

						long lIDCampiAggiuntivi = mySP.Execute("EXT_ORDINI_CAMPIAGGIUNTIVI", "ID");
						if (lIDCampiAggiuntivi > 0)
						{
							CString sQuery;
							sQuery.Format("UPDATE EXT_ORDINI_CAMPIAGGIUNTIVI SET Tabella = 'DATA', Campo = 'PATIENTIDALT', Valore = '%s', IdRichiesta = %li WHERE ID=%li",
								CString(response1.szIdPazienteAlt), lIDOrdini, lIDCampiAggiuntivi);

							theApp.m_dbEndox.ExecuteSQL(sQuery);
						}

						long lIDCampiAggiuntivi2 = mySP.Execute("EXT_ORDINI_CAMPIAGGIUNTIVI", "ID");
						if (lIDCampiAggiuntivi2 > 0)
						{
							CString sQuery;
							sQuery.Format("UPDATE EXT_ORDINI_CAMPIAGGIUNTIVI SET Tabella = 'DATA', Campo = 'PLACERORDERNUMBERCARESTREAM', Valore = '%s', IdRichiesta = %li WHERE ID=%li",
								CString(response1.szPlaceOrderNumberCarestream), lIDOrdini, lIDCampiAggiuntivi2);

							theApp.m_dbEndox.ExecuteSQL(sQuery);
						}

						long lIDCampiAggiuntivi3 = mySP.Execute("EXT_ORDINI_CAMPIAGGIUNTIVI", "ID");
						if (lIDCampiAggiuntivi3 > 0)
						{
							CString sQuery;
							sQuery.Format("UPDATE EXT_ORDINI_CAMPIAGGIUNTIVI SET Tabella = 'DATA', Campo = 'PRONTUARIO', Valore = '%s', IdRichiesta = %li WHERE ID=%li",
								CString(response1.szProntuario), lIDOrdini, lIDCampiAggiuntivi3);

							theApp.m_dbEndox.ExecuteSQL(sQuery);
						}
						//

						CExtOrdiniSet setOrdini2;
						setOrdini2.SetBaseFilter("(UO='' OR UO IS NULL)");
						sFilter.Format("ID = %li", lIDOrdini);
						setOrdini2.SetOpenFilter(sFilter);


						if (setOrdini2.OpenRecordset("FleuryGetPazienteEsame"))
						{
							if (setOrdini2.EditRecordset("FleuryGetPazienteEsame"))
							{
								setOrdini2.m_sOrderNumber = CString(response1.szCodEsame);
								setOrdini2.m_sDataEsame = CString(response1.szData);
								setOrdini2.m_lIDEsameIns = lIDEsame;
								setOrdini2.m_bTrasferito = 1;
								setOrdini2.m_lStatoAccettazione = 0;

								setOrdini2.m_sUO = CString(response1.szUO);
								setOrdini2.m_sAssIden = CString(response1.szAssIden);
								setOrdini2.m_sCognome = CString(response1.szCognome);
								setOrdini2.m_sCognome2 = CString(response1.szCognome2);
								setOrdini2.m_sNome = CString(response1.szNome);
								setOrdini2.m_lDataNascitaCustom = atol(response1.szNatoIlCustom);
								setOrdini2.m_sProvincia = CString(response1.szProvincia);
								setOrdini2.m_sTelefono1 = CString(response1.szTelefono1);
								setOrdini2.m_sTelefono2 = CString(response1.szTelefono2);
								setOrdini2.m_sCellulare1 = CString(response1.szCellulare1);
								setOrdini2.m_sCellulare2 = CString(response1.szCellulare2);
								setOrdini2.m_lSesso = atol(response1.szSesso);

								setOrdini2.UpdateRecordset("FleuryGetPazienteEsame");
							}
							else
							{
								sErrore = theApp.GetMessageString(IDS_FLEURY_ERROR_024);
							}
						}
						else
						{
							sErrore = theApp.GetMessageString(IDS_FLEURY_ERROR_025);
						}

						setOrdini2.CloseRecordset("Common::FleuryGetPazienteEsame");
					}

					//

					CRegioneSet setRegione1;
					long lIDRegione = 0;

					sFilter.Format("ESAME = %li", lIDEsame);
					setRegione1.SetOpenFilter(sFilter);
					if (setRegione1.OpenRecordset("FleuryGetPazienteEsame"))
					{
						if (setRegione1.IsEOF())
						{
							if (setRegione1.AddNewRecordset("FleuryGetPazienteEsame"))
								if (setRegione1.UpdateRecordset("FleuryGetPazienteEsame"))
									lIDRegione = setRegione1.GetLastAdd();
						}
						else
						{
							lIDRegione = 0;
						}

						setRegione1.CloseRecordset("FleuryGetPazienteEsame");
					}
					if (lIDRegione > 0)
					{
						CRegioneSet setRegione2;
						sFilter.Format("CONTATORE = %li", lIDRegione);
						setRegione2.SetOpenFilter(sFilter);

						if (setRegione2.OpenRecordset("FleuryGetPazienteEsame"))
						{
							if (setRegione2.EditRecordset("FleuryGetPazienteEsame"))
							{
								setRegione2.m_lEsame = lIDEsame;
								setRegione2.m_lCodice = 400; // TEST

								setRegione2.UpdateRecordset("FleuryGetPazienteEsame");
							}
							else
							{
								sErrore = theApp.GetMessageString(IDS_FLEURY_ERROR_026);
							}
						}
						else
						{
							sErrore = theApp.GetMessageString(IDS_FLEURY_ERROR_027);
						}

						setRegione2.CloseRecordset("FleuryGetPazienteEsame");
					}
				}
				else
				{
					sErrore = theApp.GetMessageString(IDS_FLEURY_ERROR_010) + " " + CString(response1.szUO);
				}
			}
			else
			{
				sErrore = theApp.GetMessageString(IDS_FLEURY_ERROR_009) + "\n\n" + CString(response1.szError);
			}
		}
		else
		{
			sErrore = theApp.GetMessageString(IDS_CONFIGURAZIONEVUOTA) + "\nFleuryGetPazienteEsame";
		}
	}
	else
	{
		sErrore = theApp.GetMessageString(IDS_FLEURY_ERROR_008);
	}

	AfxGetApp()->EndWaitCursor();
	return sErrore.IsEmpty();
}

BOOL FleuryGetImagemAltraSede(CWnd *pParent, CEsamiView *pEsamiView, long lIDImg)
{
	AfxGetApp()->BeginWaitCursor();

	CList<tagRemoteFile> listFiles;
	pEsamiView->m_pImgManager->GetRemoteFilesPathList(&listFiles);

	int iNumFileActual = 0;
	int iNumFilesTotal = listFiles.GetCount();

	POSITION pos = listFiles.GetHeadPosition();

	CWaitFleuryTransferitoDlg *splashDlg = NULL;
	if (iNumFilesTotal > 0)
	{
		splashDlg = new CWaitFleuryTransferitoDlg();
		splashDlg->CreateModelessDialog(pParent);
	}

	CString sErrore;
	CString strQuery;
	strQuery.Format("SELECT PERCORSOFILEREMOTOIMM FROM IMMAGINI WHERE ID= %li AND ELIMINATO=0", lIDImg);

	CRecordset setImg(&theApp.m_dbEndox);
	setImg.Open(CRecordset::snapshot, strQuery, CRecordset::readOnly);
	if (!setImg.IsEOF())
	{
		CString sRemoteFileImm;
		setImg.GetFieldValue("PERCORSOFILEREMOTOIMM", sRemoteFileImm);

		CList<tagRemoteFile> listFiles;
		pEsamiView->m_pImgManager->GetRemoteFilesPathList(&listFiles);
		tagRemoteFile tagTemp = listFiles.GetAt(0);

		int iLastSlashLocaleImm = tagTemp.sLocalFileImm.ReverseFind('\\');
		if (iLastSlashLocaleImm > 0)
		{
			CString sPathLocaleImm = tagTemp.sLocalFileImm.Left(iLastSlashLocaleImm);
			if (VerificaPercorso(sPathLocaleImm, FALSE))
			{
				if (CopyFile(sRemoteFileImm, tagTemp.sLocalFileImm, FALSE))
					pEsamiView->m_pImgManager->SetImmagineDiscoH(lIDImg);
			}
		}
		else
			sErrore = theApp.GetMessageString(IDS_FLEURY_ERROR_020);

		setImg.Close();
	}
	else
		sErrore = theApp.GetMessageString(IDS_FLEURY_ERROR_021);

	if (iNumFilesTotal > 0)
	{
		splashDlg->ShowWindow(SW_HIDE);
		splashDlg = NULL;
	}
	delete splashDlg;

	AfxGetApp()->EndWaitCursor();
	return sErrore.IsEmpty();
}

BOOL FleuryGetImagensAltraSede(CWnd *pParent, CEsamiView *pEsamiView)
{
	AfxGetApp()->BeginWaitCursor();

	CList<tagRemoteFile> listFiles;
	pEsamiView->m_pImgManager->GetRemoteFilesPathList(&listFiles);

	int iNumFileActual = 0;
	int iNumFilesTotal = listFiles.GetCount();

	POSITION pos = listFiles.GetHeadPosition();

	CWaitFleuryTransferitoDlg *splashDlg = NULL;
	if (iNumFilesTotal > 0)
	{
		splashDlg = new CWaitFleuryTransferitoDlg();
		splashDlg->CreateModelessDialog(pParent);
	}

	while (pos != NULL)
	{
		tagRemoteFile tagTemp = listFiles.GetAt(pos);

		if (!FILEEXISTS_S(tagTemp.sLocalFileImm))
		{
			int iLastSlashLocaleImm = tagTemp.sLocalFileImm.ReverseFind('\\');
			if (iLastSlashLocaleImm > 0)
			{
				CString sPathLocaleImm = tagTemp.sLocalFileImm.Left(iLastSlashLocaleImm);
				if (VerificaPercorso(sPathLocaleImm, FALSE))
				{
					if (CopyFile(tagTemp.sRemoteFileImm, tagTemp.sLocalFileImm, FALSE))
						pEsamiView->m_pImgManager->SetImmagineDiscoH(tagTemp.lID);
				}
			}
		}
		listFiles.GetNext(pos);
	}

	if (iNumFilesTotal > 0)
	{
		splashDlg->ShowWindow(SW_HIDE);
		splashDlg = NULL;
	}
	delete splashDlg;

	AfxGetApp()->EndWaitCursor();
	return TRUE;
}

BOOL FleuryGetDocsAltraSede(long lIDEsame, BOOL bInviareCarestream)
{
	CMyDocManager DocManager;

	CList<DOC> lst;
	DocManager.GetAttachedDocListExam(lIDEsame, bInviareCarestream ? DOCUMENTS_ONLY_EXPORT : DOCUMENTS_NOT_EXPORT, &lst);

	for (int i = 0; i < lst.GetCount(); i++)
	{
		DOC doc = lst.GetAt(lst.FindIndex(i));

		if ((CString(doc.szDisco).CompareNoCase("R") == 0) && !CString(doc.szPercorsoFileRemoto).IsEmpty())
		{
			if (DocManager.CopyToLocal(doc.lID))
			{
				sprintf(doc.szDisco, "H");
				lst.SetAt(lst.FindIndex(i), doc);
			}
			else
			{
				//sprintf(doc.szFile, doc.szPercorsoFileRemoto);
			}
		}
	}

	/*CPdfManager PdfManager;

	if (PdfManager.IsInitialize())
	{
	CPdfList listPdf;
	PdfManager.GetPdf(lIDEsame, &listPdf);

	for (POSITION pos = listPdf.GetHeadPosition(); pos;)
	{
	PDF pdf = listPdf.GetNext(pos);
	if ((CString(pdf.szDisco).CompareNoCase("R") == 0) && !CString(pdf.szPercorsoFileRemoto).IsEmpty())
	{
	PdfManager.CopyToLocal(pdf.lID);
	}
	}
	}*/
	return TRUE;
}

BOOL FleurySetEsameTrasferitoAltraSede(CString sEndpoint, CString sFicha, CString& sErrore)
{
	AfxGetApp()->BeginWaitCursor();

	sErrore = "";

	sFicha.Replace("'", "''");
	sFicha.Trim();
	if (!sFicha.IsEmpty())
	{
		sEndpoint.Trim();

		if (!sEndpoint.IsEmpty())
		{
			setexamotherlocationRequest request2;
			sprintf_s(request2.szFicha, sFicha);
			sprintf_s(request2.szCodiceUnita, theApp.m_sCodiceUnitaFleury);

			CSetExamOtherLocationService setexamotherlocationService(sEndpoint);
			setexamotherlocationResponse response2 = setexamotherlocationService.SetExamOtherLocation(request2);

			sErrore = CString(response2.szError);
		}
		else
		{
			sErrore = theApp.GetMessageString(IDS_CONFIGURAZIONEVUOTA) + "\nFleurySetEsameTrasferitoAltraSede";
		}
	}
	else
	{
		sErrore = theApp.GetMessageString(IDS_FLEURY_ERROR_008);
	}

	AfxGetApp()->EndWaitCursor();
	return sErrore.IsEmpty();
}

//Julio 6/12/2017 //
void DoPtBrReplacement(CString& sText)
{
	//á é í ó ú Á É Í Ó Ú à À ç Ç ã Ã õ Õ â ê î ô û Â Ê Î Ô Û
	/*
	sText.Replace("", "á");
	sText.Replace("", "é");
	sText.Replace("", "í");
	sText.Replace("", "ó");
	sText.Replace("", "ú");

	sText.Replace("", "Á");
	sText.Replace("", "É");
	sText.Replace("", "Í");
	sText.Replace("", "Ó");
	sText.Replace("", "Ú");

	sText.Replace("", "à");
	sText.Replace("", "À");

	sText.Replace("", "ç");
	sText.Replace("", "Ç");

	sText.Replace("", "ã");
	sText.Replace("", "Ã");

	sText.Replace("", "õ");
	sText.Replace("", "Õ");

	sText.Replace("", "â");
	sText.Replace("", "ê");
	sText.Replace("", "î");
	sText.Replace("", "ô");
	sText.Replace("", "û");

	sText.Replace("", "Â");
	sText.Replace("", "Ê");
	sText.Replace("", "Î");
	sText.Replace("", "Ô");
	sText.Replace("", "Û");
	*/
}

// Sandro 26/10/2015 //

long GetStampaImmaginiIDHeader()
{
	long lReturn = 0;

	if (theApp.m_bStampaImmaginiUsaHFPerUO)
		lReturn = theApp.m_lStampaImmaginiIDHeaderGlobal;
	else
		lReturn = theApp.m_lStampaImmaginiIDHeaderLocal;

	return lReturn;
}

long GetStampaImmaginiIDFooter()
{
	long lReturn = 0;

	if (theApp.m_bStampaImmaginiUsaHFPerUO)
		lReturn = theApp.m_lStampaImmaginiIDFooterGlobal;
	else
		lReturn = theApp.m_lStampaImmaginiIDFooterLocal;

	return lReturn;
}

CString ComponiStringaConnessione(BOOL bIsOracle, const CString &sOracleDriver, const CString &sServerDBQ, const CString &sUsername, const CString &sPassword)
{
	CString sReturn = "";

	if (bIsOracle)
		sReturn.Format("DRIVER={%s};DBQ=%s;UID=%s;PWD=%s", sOracleDriver, sServerDBQ, sUsername, sPassword);
	else
		sReturn.Format("DRIVER={SQL Server};SERVER=%s;UID=%s;PWD=%s", sServerDBQ, sUsername, sPassword);

	return sReturn;
}

void StartProcess(CString sProcess)
{
	TCHAR szProcess[1024];
	sprintf_s(szProcess, "%s", sProcess);

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
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
}

BOOL RegistryGetValue(HKEY hk, const char* pszKey, const char* pszValue, DWORD dwType, BYTE* pData, DWORD dwSize)
{
	HKEY hkOpened;

	// Try to open the key
	if (RegOpenKeyEx(hk, pszKey, 0, KEY_READ, &hkOpened) != ERROR_SUCCESS)
		return FALSE;

	// If the key was opened, try to retrieve the value
	if (RegQueryValueEx(hkOpened, pszValue, 0, &dwType, pData, &dwSize) != ERROR_SUCCESS)
	{
		RegCloseKey(hkOpened);
		return FALSE;
	}

	// Clean up
	RegCloseKey(hkOpened);
	return TRUE;
}

CString RegistryGetStringValue(HKEY hKey, CString sSubKey, CString sValue)
{
	CString sReturn = "";

	char szData[4096];
	DWORD dwData = 4096;
	if (RegGetValue(hKey, sSubKey, sValue, RRF_RT_REG_SZ, NULL, szData, &dwData) == ERROR_SUCCESS)
	{
		if (dwData > 0)
			sReturn.Format("%s", szData);
	}

	return sReturn;
}

long GetUserIDForLockSuperlock()
{
	long lReturn = 0;

	// Sandro 15/02/2017 // RIMA 17013 //

	CString sUsernameResponsabile = CUOSet().GetUsernameResponsabile(theApp.m_lUO);
	if (sUsernameResponsabile.IsEmpty())
		AMLogin_GetUserID(&lReturn);
	else
		lReturn = CUtentiSet().GetIDFromUsername(sUsernameResponsabile);

	//

	return lReturn;
}

// Sandro 06/07/2017 //

int ContaFilesPostAcquisizione(long lIDPaziente, long lIDEsame)
{
	//
	int iNumeroFile = 0;

	// importo solo i files dell'esame corrente //
	CString strWildcard;
	strWildcard.Format("%s\\%08d_%08d_*.*",
		theApp.m_sDirTempAcq,
		lIDPaziente,
		lIDEsame);

	//
	WIN32_FIND_DATA dataFile;
	HANDLE hFile = FindFirstFile(strWildcard, &dataFile);
	if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
	{
		do
		{
			CString strFile(dataFile.cFileName);

			if (strFile.GetLength() > 3)
			{
				strFile = strFile.Right(3);
				if ((strFile.CompareNoCase("bmp") == 0) || (strFile.CompareNoCase("mpg") == 0) || (strFile.CompareNoCase("avi") == 0) || (strFile.Right(3).CompareNoCase("mp4") == 0) || (strFile.CompareNoCase("dcm") == 0))
					iNumeroFile++;
			}
		} while (FindNextFile(hFile, &dataFile));
	}
	FindClose(hFile);

	// Sandro 05/07/2012 //
	CString sMessage;
	sMessage.Format(theApp.GetMessageString(IDS_ACQUISIZIONE_MESSAGGIO1), iNumeroFile);
	CInsertLogAcquisizioneSPSet().Exec(lIDPaziente, lIDEsame, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, sMessage);

	//
	return iNumeroFile;
}

void FleuryApriConsulta2(CString sFicha)
{
	long lUserID;
	AMLogin_GetUserID(&lUserID);

	CString strUserSEGU;
	CString strUser3L3N;
	if (theApp.m_bUsaIDSegu)
	{
		strUserSEGU = CMediciSet().GetCodiceFromUserID(lUserID);
		strUser3L3N = CMediciSet().GetCodice3L3NFromUserID(lUserID);
	}
	else
	{
		strUser3L3N = CMediciSet().GetCodiceFromUserID(lUserID);
	}

	CCustomDate dateNow(TRUE, TRUE);

	
	if (strUser3L3N.IsEmpty() && strUserSEGU.IsEmpty())
	{
		AfxMessageBox(theApp.GetMessageString(IDS_FLEURY_FICHA_ERROR), MB_ICONSTOP);
		return;
	}

	CString strUnita = "";
	CString strServer = "";
	char szPathImm[MAX_PATH];
	char szPathMin[MAX_PATH];
	if (CImgArchive(&theApp.m_dbEndox).GetArchivePrimary(szPathImm, szPathMin, MAX_PATH))
	{
		CString sAsd = szPathImm;
		sAsd.Trim();
		if (sAsd.GetLength() > 8)
		{
			strUnita = sAsd.Mid(5, 3);
			strServer = "SRV" + strUnita + "-TESI";
		}

	}

	CString sURL;
	if (!strUserSEGU.IsEmpty())
	{
		sURL.Format("http://awlbp/Fleury.TI.ConsultaResultados.WebApp/auth/AcessoGrafico?Estacao=%s&Secao=%s&SecaoCc=%s&Unidade=%s&Identificador=%s&Origem=%s&Sistema=%s&Servidor=%s&AmbienteMostrar=%s&Ficha=%s",
			theApp.m_sNomeComputer,
			"NKB", //Secao do usuario, nao sei de onde tirar isso, estou copiando da chamada de exemplo que eu tenho
			"NKB", //Centro de custo do usuario, nao sei de onde tirar isso, estou copiando da chamada de exemplo que eu tenho
			strUnita,
			strUserSEGU,
			"Tesi", //Que sistema esta chamando a URL
			"ConsResult", //Que sistema esta sendo chamado
			strServer, //Servidor que a maquina esta rodando
			"Produção", //Qual ambiente deve ser apresentado
			sFicha);
	}
	else
	{
		sURL.Format("http://awlbp/Fleury.TI.ConsultaResultados.WebApp/auth/AcessoGrafico?Estacao=%s&Secao=%s&SecaoCc=%s&Unidade=%s&Usuario=%s&Origem=%s&Sistema=%s&Servidor=%s&AmbienteMostrar=%s&Ficha=%s",
			theApp.m_sNomeComputer,
			"NKB", //Secao do usuario, nao sei de onde tirar isso, estou copiando da chamada de exemplo que eu tenho
			"NKB", //Centro de custo do usuario, nao sei de onde tirar isso, estou copiando da chamada de exemplo que eu tenho
			strUnita,
			strUser3L3N,
			"Tesi", //Que sistema esta chamando a URL
			"ConsResult", //Que sistema esta sendo chamado
			strServer, //Servidor que a maquina esta rodando
			"Produção", //Qual ambiente deve ser apresentado
			sFicha);
	}
	
	ShellExecute(NULL, "open", sURL, NULL, NULL, SW_SHOWMAXIMIZED);

#ifdef _DEBUG
	AfxMessageBox(sURL);
#endif
	//OpenURLOnChrome(sURL);

	/*
	Estacao			==> Estação utilizada (hostname da máquina em uso)
	Secao			==> Seção a que o usuário está vinculado
	SecaoCC			==> Centro de Custo a que o usuário está vinculado (na ausência da informação, pode-se repetir o conteúdo da Seção)
	Unidade			==> Qual foi a unidade selecionada no login
	Identificador	==> ID do SEGU
	Origem			==> Qual a origem da chamada (quem solicitou a abertura da aplicação, por exemplo: acesso gráfico, Tesi, etc.)
	Sistema			==> Conteúdo fixo: “ConsResult”
	Servidor		==> Servidor em que a máquina está logada. Na ausência	desta informação, pode-se repetir a informação da Estação
	AmbienteMostrar ==> Texto fixo “Produção”
	Ficha			==> Número da ficha a ser carregada
	*/

	///---------------------------------------///
	///----------Antigo consulta web----------///
	///---------------------------------------///
	
	/*CString strExec;
	strExec.Format("C:\\Fleury\\Programas\\Fleury.TI.ConsultaResultados.AcessoGrafico.Treino.exe %s|%s|%s|%s|%s||%s||||AP|%s",
	dateNow.GetDate("%d/%m/%Y"),
	dateNow.GetDate("%d"),
	dateNow.GetDate("%m"),
	dateNow.GetDate("%Y"),
	strUser,
	strUnita,
	sFicha);

	"C:\\Fleury\\Programas\\Fleury.TI.ConsultaResultados.AcessoGrafico.Treino.exe " + SysDate + "|" + SysDay + "|" + SysMonth + "|" + SysYear + "|" + sysOperator + "|" + sysArvore + "|" + sysFilial + "|" + sysLocImp + "|" + sysTabPrazo + "|" + sysUS + "|" + sysSection + "|" + Ficha

	/*
	SysDate		|	Date (DD/MM/AAAA)
	SysDay		|	Day (DD)
	SysMonth	|	Month (MM)
	SysYear		|	Year (AAAA)
	SysOperator	|	usuário 3L3N logado
	SysArvore	|	Blank
	SysFilial	|	código de 3 dígitos da unidade logada
	SysLocImp	|	Blank
	SysTabPrazo	|	Blank
	SysUS		|	Blank
	SysSection	|	Constant "AP"
	Ficha		|	FICHA (9999999999)
	*/
				
}

void FleuryApriConsulta(CString sFicha)
{
	long lUserID;
	AMLogin_GetUserID(&lUserID);

	CString strUser3L3N;
	if (theApp.m_bUsaIDSegu)
		strUser3L3N = CMediciSet().GetCodice3L3NFromUserID(lUserID);
	else
		strUser3L3N = CMediciSet().GetCodiceFromUserID(lUserID);

	CCustomDate dateNow(TRUE, TRUE);

	if (strUser3L3N.IsEmpty())
	{
		AfxMessageBox(theApp.GetMessageString(IDS_FLEURY_FICHA_ERROR), MB_ICONSTOP);
		return;
	}

	CString strExec = "";
	strExec.Format("c:\\fleury\\programas\\vbconsulta.exe %s|%02d|%02d|%d|%s||||||AP|%s",
		dateNow.GetDate("%d/%m/%Y"),
		dateNow.GetDay(),
		dateNow.GetMonth(),
		dateNow.GetYear(),
		strUser3L3N,
		sFicha);


	if (!strExec.IsEmpty())
	{
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		if (!CreateProcess(NULL, strExec.GetBuffer(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
		{
			LPVOID lpMsgBuf;
			if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL))
				AfxMessageBox((LPCTSTR)lpMsgBuf);
			else
				AfxMessageBox(theApp.GetMessageString(IDS_ERROR_NOT_DEFINED));
			LocalFree(lpMsgBuf);
		}

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	
}

void FleuryAssessoriaMedica(CString sFicha)
{
	long lUserID;
	AMLogin_GetUserID(&lUserID);

	CString strUserSEGU;
	CString strUser3L3N;
	if (theApp.m_bUsaIDSegu)
	{
		strUserSEGU = CMediciSet().GetCodiceFromUserID(lUserID);
		strUser3L3N = CMediciSet().GetCodice3L3NFromUserID(lUserID);
	}
	else
	{
		strUser3L3N = CMediciSet().GetCodiceFromUserID(lUserID);
	}
	CString sUsername = AMLogin_GetUsername();

	CCustomDate dateNow(TRUE, TRUE);

	
	if (strUser3L3N.IsEmpty() && strUserSEGU.IsEmpty())
	{
		AfxMessageBox(theApp.GetMessageString(IDS_FLEURY_FICHA_ERROR), MB_ICONSTOP);
		return;
	}

	CString strUnita = "";
	CString strServer = "";
	char szPathImm[MAX_PATH];
	char szPathMin[MAX_PATH];
	if (CImgArchive(&theApp.m_dbEndox).GetArchivePrimary(szPathImm, szPathMin, MAX_PATH))
	{
		CString sAsd = szPathImm;
		sAsd.Trim();
		if (sAsd.GetLength() > 8)
		{
			strUnita = sAsd.Mid(5, 3);
			strServer = "SRV" + strUnita + "-TESI";
		}

	}

	CString sURL;
	if (!strUserSEGU.IsEmpty())
	{
		sURL.Format("http://awlbp/Fleury.TI.AssessoriaMedica.WebApp/Auth/Login?Unidade=%s&AmbienteMostrar=%s&NomeUsuario=%s&Secao=%s&SecaoCC=%s&Sistema=%s&Identificador=%s&Estacao=%s&Servidor=%s&numeroFicha=%s&Origem=%s",
			strUnita,
			"Produção", //Qual ambiente deve ser apresentado
			sUsername,
			"NKB", //Secao do usuario, nao sei de onde tirar isso, estou copiando da chamada de exemplo que eu tenho
			"NKB", //Centro de custo do usuario, nao sei de onde tirar isso, estou copiando da chamada de exemplo que eu tenho
			"AssessoriaMedica", //Que sistema esta sendo chamado
			strUserSEGU,
			theApp.m_sNomeComputer,
			strServer, //Servidor que a maquina esta rodando
			sFicha,
			"Tesi"); //Que sistema esta chamando a URL
	}
	else
	{
		sURL.Format("http://awlbp/Fleury.TI.AssessoriaMedica.WebApp/Auth/Login?Unidade=%s&AmbienteMostrar=%s&NomeUsuario=%s&Secao=%s&SecaoCC=%s&Sistema=%s&Usuario=%s&Estacao=%s&Servidor=%s&numeroFicha=%s&Origem=%s",
			strUnita,
			"Produção", //Qual ambiente deve ser apresentado
			sUsername,
			"NKB", //Secao do usuario, nao sei de onde tirar isso, estou copiando da chamada de exemplo que eu tenho
			"NKB", //Centro de custo do usuario, nao sei de onde tirar isso, estou copiando da chamada de exemplo que eu tenho
			"AssessoriaMedica", //Que sistema esta sendo chamado
			strUser3L3N,
			theApp.m_sNomeComputer,
			strServer, //Servidor que a maquina esta rodando
			sFicha,
			"Tesi"); //Que sistema esta chamando a URL
	}

	ShellExecute(NULL, "open", sURL, NULL, NULL, SW_SHOWMAXIMIZED);
						
#ifdef _DEBUG
	AfxMessageBox(sURL);
#endif
	//OpenURLOnChrome(sURL);

	/*
	Unidade         ==> Qual foi a unidade selecionada no login
	AmbienteMostrar ==> Texto fixo “Produção”
	NomeUsuario     ==> Nome do usuário logado
	Secao           ==> Seção a que o usuário está vinculado
	SecaoCC         ==> Centro de Custo a que o usuário está vinculado (na ausência da informação, pode-se repetir o conteúdo da Seção)
	Sistema         ==> Conteúdo fixo: “AssessoriaMedica”
	Identificador   ==> ID do SEGU
	Estacao         ==> Estação utilizada (hostname da máquina em uso)
	Servidor        ==> Servidor em que a máquina está logada. Na ausência desta informação, pode-se repetir a informação da Estação
	NumeroFicha     ==> Número da ficha a ser carregada
	Origem          ==> Qual a origem da chamada (quem solicitou a abertura da aplicação, por exemplo: acesso gráfico, Tesi, etc.)		
	*/
}

//Julio Login SEGU
void OpenURLOnChrome(CString sURL)
{
	//sURL.Format(theApp.m_sHttpPathVisorPacsWeb, "123456789000100");

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
}

CString GetBase64StringFromString(CString sInput)
{
	CString sReturn = "";

	DWORD dwEncodeBufferLength = AmBase64_CalculateRequiredEncodeOutputBufferSize(sInput.GetLength());
	char* pBufferB64 = new char[dwEncodeBufferLength];
	ZeroMemory(pBufferB64, dwEncodeBufferLength * sizeof(char));
	AmBase64_EncodeBuffer(sInput.GetBuffer(), sInput.GetLength(), pBufferB64);
	sInput.ReleaseBuffer();
	sReturn = CString(pBufferB64);
	delete pBufferB64;

	return sReturn;
}

void UpdateDatiRemoti(CEsamiSet* pEsamiSet)
{
	const long lNumeroUpdates = 10;

	CString sCodEsame = pEsamiSet->m_sCodEsame;
	sCodEsame.Replace("'", "''");

	CString sSetClause = "";

	writevaluesintodbRequest request;
	request.lNumUpdates = lNumeroUpdates;
	request.pStructUpdates = new Update[lNumeroUpdates];

	//

	sSetClause.Format("LOCKED = %d", pEsamiSet->m_bLocked ? 1 : 0);
	sprintf(request.pStructUpdates[0].szTableName, "EESAMI");
	sprintf(request.pStructUpdates[0].pSzSetClauseBase64, GetBase64StringFromString(sSetClause));
	sprintf(request.pStructUpdates[0].szWhereClause, "CODESAME = '%s'", sCodEsame);

	sSetClause.Format("IDUTENTELOCK = %li", 0); // pEsamiSet->m_lIdUtenteLock);
	sprintf(request.pStructUpdates[1].szTableName, "EESAMI");
	sprintf(request.pStructUpdates[1].pSzSetClauseBase64, GetBase64StringFromString(sSetClause));
	sprintf(request.pStructUpdates[1].szWhereClause, "CODESAME = '%s'", sCodEsame);

	sSetClause.Format("DATAORALOCK = '%s'", pEsamiSet->m_sDataOraLock);
	sprintf(request.pStructUpdates[2].szTableName, "EESAMI");
	sprintf(request.pStructUpdates[2].pSzSetClauseBase64, GetBase64StringFromString(sSetClause));
	sprintf(request.pStructUpdates[2].szWhereClause, "CODESAME = '%s'", sCodEsame);

	sSetClause.Format("SUPERLOCKED = %d", pEsamiSet->m_bSuperLocked ? 1 : 0);
	sprintf(request.pStructUpdates[3].szTableName, "EESAMI");
	sprintf(request.pStructUpdates[3].pSzSetClauseBase64, GetBase64StringFromString(sSetClause));
	sprintf(request.pStructUpdates[3].szWhereClause, "CODESAME = '%s'", sCodEsame);

	sSetClause.Format("IDUTENTESUPERLOCK = %li", 0); // pEsamiSet->m_lIdUtenteSuperLock);
	sprintf(request.pStructUpdates[4].szTableName, "EESAMI");
	sprintf(request.pStructUpdates[4].pSzSetClauseBase64, GetBase64StringFromString(sSetClause));
	sprintf(request.pStructUpdates[4].szWhereClause, "CODESAME = '%s'", sCodEsame);

	sSetClause.Format("DATAORASUPERLOCK = '%s'", pEsamiSet->m_sDataOraSuperLock);
	sprintf(request.pStructUpdates[5].szTableName, "EESAMI");
	sprintf(request.pStructUpdates[5].pSzSetClauseBase64, GetBase64StringFromString(sSetClause));
	sprintf(request.pStructUpdates[5].szWhereClause, "CODESAME = '%s'", sCodEsame);

	sSetClause.Format("DATAORASUPERLOCKPRIMO = '%s'", pEsamiSet->m_sDataOraSuperLockPrimo);
	sprintf(request.pStructUpdates[6].szTableName, "EESAMI");
	sprintf(request.pStructUpdates[6].pSzSetClauseBase64, GetBase64StringFromString(sSetClause));
	sprintf(request.pStructUpdates[6].szWhereClause, "CODESAME = '%s'", sCodEsame);

	sSetClause.Format("REFERTOTESTORTF = '%s'", pEsamiSet->m_sRefertoTestoRtf);
	sprintf(request.pStructUpdates[7].szTableName, "EESAMI");
	sprintf(request.pStructUpdates[7].pSzSetClauseBase64, GetBase64StringFromString(sSetClause));
	sprintf(request.pStructUpdates[7].szWhereClause, "CODESAME = '%s'", sCodEsame);

	sSetClause.Format("REFERTOTESTOTXT = '%s'", pEsamiSet->m_sRefertoTestoTxt);
	sprintf(request.pStructUpdates[8].szTableName, "EESAMI");
	sprintf(request.pStructUpdates[8].pSzSetClauseBase64, GetBase64StringFromString(sSetClause));
	sprintf(request.pStructUpdates[8].szWhereClause, "CODESAME = '%s'", sCodEsame);

	sSetClause.Format("REFERTOTESTOHTML = '%s'", pEsamiSet->m_sRefertoTestoHtml);
	sprintf(request.pStructUpdates[9].szTableName, "EESAMI");
	sprintf(request.pStructUpdates[9].pSzSetClauseBase64, GetBase64StringFromString(sSetClause));
	sprintf(request.pStructUpdates[9].szWhereClause, "CODESAME = '%s'", sCodEsame);

	// 

	CWriteValuesIntoDBService writevaluesintodbService(pEsamiSet->m_sFleuryEndpointRemoto);
	writevaluesintodbResponse response = writevaluesintodbService.WriteValuesIntoDB(request);
	if (strcmp(response.szError, "") != 0)
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_FLEURY_ERROR_018) + "\n\n" + CString(response.szError));

	//

	for (int i = 0; i < lNumeroUpdates; i++)
	{
		delete request.pStructUpdates[i].pSzSetClauseBase64;
		request.pStructUpdates[i].pSzSetClauseBase64 = NULL;
	}
}

void XWriteLogTime(CString sLog, DWORD dwMsecParz, DWORD dwMsecTot)
{
	CString sLogLine;

	//

	if (dwMsecParz > 0)
	{
		if (dwMsecTot > 0)
			sLogLine.Format("%s --> %li msec (%li msec tot)", sLog, dwMsecParz, dwMsecTot);
		else
			sLogLine.Format("%s --> %li msec", sLog, dwMsecParz);
	}
	else if (dwMsecTot > 0)
	{
		sLogLine.Format("%s --> %li msec tot)", sLog, dwMsecTot);
	}
	else
	{
		sLogLine = sLog;
	}

	//

	TRACE0(sLogLine + "\n");

	if (theApp.m_bSaveCompleteLog)
	{
		CLogFileWriter::Get()->WriteLogLine0(sLogLine);
		CLogFileWriter::Get()->WriteLogLine0("");
	}
}
void ImpersonateStart(long lIDEsame, long lIDPaziente, long lIDUtente)
{
	CString sUtente = CUtentiSet().GetUsername(lIDUtente);
	if (sUtente == theApp.m_sUtenteLoggato || lIDUtente == 0 || sUtente.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMPERSONAR_MESSAGE_ERROR));
		return;
	}

	CString sMessage;
	sMessage.Format(theApp.GetMessageString(IDS_IMPERSONAR_MESSAGE), lIDUtente, sUtente);
	if (theApp.AfxMessageBoxEndo(sMessage, MB_YESNO) == IDYES)
	{
		theApp.m_bImpersonated = TRUE;
		theApp.m_lImpersonatedID = lIDUtente;
		theApp.m_sImpersonatedUsername = sUtente;

		CString sNewTitle;
		sNewTitle.Format(theApp.GetMessageString(IDS_IMPERSONANDO), theApp.m_sImpersonatedUsername);
		sNewTitle = theApp.GetAppTitle(0) + sNewTitle;
		((CMainFrame*)AfxGetMainWnd())->GetActiveDocument()->SetTitle(sNewTitle);
	}
	else
	{
		if (theApp.m_bImpersonated)
			ImpersonateStop(lIDEsame, lIDPaziente);
	}

	CWriteLogLineSPSet().Exec(
		lIDPaziente, lIDEsame,
		(theApp.m_bImpersonated) ? theApp.m_sUtenteLoggato + " IMP " + theApp.m_sImpersonatedUsername : theApp.m_sUtenteLoggato,
		theApp.m_sNomeComputer.Left(50), theApp.m_sNomeImpianto.Left(50), "", 0, "", 0, "", theApp.m_sUtenteLoggato, theApp.m_sImpersonatedUsername, "ImpersonateStart");
}
void ImpersonateStop(long lIDEsame, long lIDPaziente)
{
	if (theApp.m_bImpersonated)
	{
		CWriteLogLineSPSet().Exec(
			lIDPaziente, lIDEsame,
			(theApp.m_bImpersonated) ? theApp.m_sUtenteLoggato + " IMP " + theApp.m_sImpersonatedUsername : theApp.m_sUtenteLoggato,
			theApp.m_sNomeComputer.Left(50), theApp.m_sNomeImpianto.Left(50), "", 0, "", 0, "", theApp.m_sImpersonatedUsername, theApp.m_sUtenteLoggato, "ImpersonateStop");

		theApp.m_bImpersonated = FALSE;
		theApp.m_lImpersonatedID = 0;
		theApp.m_sImpersonatedUsername = "";

		CString sNewTitle = theApp.GetAppTitle(0);
		((CMainFrame*)AfxGetMainWnd())->GetActiveDocument()->SetTitle(sNewTitle);
	}
}

//Julio BUG 3456 - Contingencia
BOOL CheckIfMainDBIsOnline()
{
	BOOL bReturn = FALSE;

	TRY
	{
		CAMBaseDB dbTest;
		bReturn = dbTest.OpenDirect(theApp.m_sFileConfig);

		if (dbTest.IsOpen())
			dbTest.Close();
	}
	CATCH_ALL(e)
	{
		bReturn = FALSE;
	}
	END_CATCH_ALL

	return bReturn;
}

// Marvel Carvalho - Bug 3457 (FIX) TEXTER
int CStringFindLastIndexOf(const CString& strFullText, const CString& strThingToLookFor)
{
	int start = strFullText.Find(strThingToLookFor, 0);

	if (start >= 0)
	{
		while (start < strFullText.GetLength())
		{
			int idx = strFullText.Find(strThingToLookFor, start + 1);
			if (idx >= 0)
				start = idx;
			else
				break;
		}
	}

	return start;
}

// Marvel Carvalho - Bug 3457 (FIX) TEXTER
// Virtual key press handler
void pressKey(WORD key)
{
	// Initialize the virtual keyboard.
	INPUT vir;
	vir.type = INPUT_KEYBOARD;
	vir.ki.time = 0;
	vir.ki.dwFlags = KEYEVENTF_UNICODE;
	vir.ki.wVk = 0;
	vir.ki.wScan = key;
	vir.ki.dwExtraInfo = 0;
	SendInput(1, &vir, sizeof(INPUT));
}

// Marvel Carvalho - Bug 3457 (FIX) TEXTER
// quando insiro o texto como rtf o TX Text Control sempre coloca um enter no final do texto
// remove o último '\par' que o RTF coloca a mais (causaria acumulo de 'enters' se editado várias vezes)
CString cleanFinalDoubleParInRTF(CString p_strRTF)
{
	CString strToReturn;
	strToReturn = p_strRTF.Trim();
	int n = strToReturn.Replace(_T("\\par\\par }"), _T("\\par }"));

	return strToReturn;
}
//Gabriel BUG 6225 - Lista DO
void Maximize(HWND hWnd, HMONITOR hMonitor)
{
	// access monitor info
	MONITORINFO monitorInfo = { sizeof(MONITORINFO) };
	GetMonitorInfo(hMonitor, &monitorInfo);

	// restore window to normal size if it is not yet
	ShowWindow(hWnd, SW_RESTORE);

	// move window to the monitor
	SetWindowPos(hWnd, nullptr, monitorInfo.rcMonitor.left,
		monitorInfo.rcMonitor.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	// maximize window
	ShowWindow(hWnd, SW_MAXIMIZE);
}

//Gabriel BUG 6225 - Lista DO
void CenterWndInSecondScreen(CWnd* const pWnd, BOOL bMaximize)
{
	if (pWnd == NULL)
		return;

	if (CMonitorScreens::GetMonitorCount() > 1)	// MOVE PARA A 2A TELA SE HOUVER
	{
		CMonitor monitorII;
		CMonitorScreens monitors;
		monitorII = monitors.GetMonitor(1);	// 0=MainScreen; 1=SecondScreen
		monitorII.CenterWindowToMonitor(pWnd);
		if (bMaximize)
			Maximize(pWnd->GetSafeHwnd(), monitorII);
	}
}

void CenterWndInFirstScreen(CWnd* const pWnd, BOOL bMaximize)
{
	if (pWnd == NULL)
		return;

	CMonitor monitorI;
	CMonitorScreens monitors;
	monitorI = monitors.GetMonitor(0);	// 0=MainScreen; 1=SecondScreen
	monitorI.CenterWindowToMonitor(pWnd);
	if (bMaximize)
		Maximize(pWnd->GetSafeHwnd(), monitorI);
}

void TraceAndLog(CString sMessage, long lTime)
{
	if (lTime >= 0)
	{
		CString sTime;
		sTime.Format("%li", lTime);
		sMessage += " (" + sTime + " msec)";
	}

	TRACE0(sMessage + "\n");
	CLogFileWriter::Get()->WriteLogLine0(sMessage);


}

// Marvel Carvalho - BUG 4685 Personalizações fluxo D.O. (#6 - referto | aba anamnesi)
void AppendTextToEditCtrl(CEdit& edit, LPCTSTR pszText)
{
	// get the initial text length
	int nLength = edit.GetWindowTextLength();
	// put the selection at the end of text
	edit.SetSel(nLength, nLength);
	// replace the selection
	edit.ReplaceSel(pszText);
}

// Marvel Carvalho (FIX) BUG 3361 - Captura continua DICOM
BOOL CreateLogFolderIfNotExists(CString p_strPath)
{
	try{
		BOOL bResp1 = CreateDirectory(p_strPath, NULL);
		BOOL bResp2 = ERROR_ALREADY_EXISTS == GetLastError();
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}

//Gabriel BUG 6225 - Lista DO FIX
void TrySetCustomListOrder(CString sCustomOrder, CListCtrl* pListCtrl)
{
	if (sCustomOrder.IsEmpty())
		return;

	int iArraySize = pListCtrl->GetHeaderCtrl()->GetItemCount();
	if (iArraySize == 0)
		return;

	//could not make it work with a dynamic array (based on iArraySize), fell free to change the code
	int lpArray[] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
	//	

	CString sOrdine = sCustomOrder;
	if (!sOrdine.IsEmpty())
	{
		int iQantita = 0, iStart = 0, iTemp = 0;
		while (sOrdine.Replace(" ", "") > 0) //Remove all white spaces spaces
			;

		if (sOrdine.Right(1) != ",") //Check if string ends with ,
			sOrdine += ",";

		iTemp = sOrdine.Find(',', iStart);
		while (iTemp >= 0)
		{
			iTemp = sOrdine.Find(',', iTemp + 1);
			iQantita++;
		}

		if (iQantita != iArraySize)
			return; //Configuration has a diferent quantity of values then expected


		//Split configuration by ,
		CList<int> listaValori;

		iStart = 0;
		iTemp = sOrdine.Find(',', iStart);
		while (iTemp >= 0)
		{
			int iValore = atoi(sOrdine.Mid(iStart, iTemp - iStart));
			if (iValore >= 0 && iValore < iArraySize)
				listaValori.AddTail(iValore);

			iStart = iTemp + 1;
			iTemp = sOrdine.Find(',', iStart);
		}

		if (listaValori.GetCount() == iArraySize) //Check if all values from the split are numeric
		{
			iStart = 0;
			for (POSITION pos = listaValori.GetHeadPosition(); pos;) //repopulate input array
			{
				lpArray[iStart++] = listaValori.GetNext(pos);
			}

			pListCtrl->GetHeaderCtrl()->SetOrderArray(iArraySize, (LPINT)lpArray); //Set new order
		}
	}
}
