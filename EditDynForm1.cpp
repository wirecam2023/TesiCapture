#include "stdafx.h"
#include "Endox.h"
#include "EditDynForm1.h"

#include "DLL_Imaging\h\AMLogin.h"

#include "ComboBoxSet.h"
#include "Common.h"
#include "CustomDate.h"
#include "EditDynForm2.h"
#include "EditDynFormFullRtf.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "EtichetteCondizionateConfigSet.h"
#include "EtichetteSet.h"
#include "ExtOrdiniSet.h"
#include "MediciSet.h"
#include "VistaUtentiMediciSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CExtDateEdit CEditDynForm1::m_ctrlDataEsame;
CExtEdit CEditDynForm1::m_ctrlFarmacoTrial;
CExtEdit CEditDynForm1::m_ctrlPremedicazioni;
CExtEdit CEditDynForm1::m_ctrlEstensione;
CExtEdit CEditDynForm1::m_ctrlValutazione;
CExtEdit CEditDynForm1::m_ctrlNrControllo;
CExtEdit CEditDynForm1::m_ctrlQuadro;
CExtDateEdit CEditDynForm1::m_ctrlDataProssimo;
CExtEdit CEditDynForm1::m_ctrlStudio;
CExtEdit CEditDynForm1::m_ctrlGuarigione;
CEdit CEditDynForm1::m_ctrlSedeEsame;
CEdit CEditDynForm1::m_ctrlSalaEsame;

CFreeExtEdit CEditDynForm1::m_ctrlTesto000;
CFreeExtEdit CEditDynForm1::m_ctrlTesto001;
CFreeExtEdit CEditDynForm1::m_ctrlTesto002;
CFreeExtEdit CEditDynForm1::m_ctrlTesto003;
CFreeExtEdit CEditDynForm1::m_ctrlTesto004;
CFreeExtEdit CEditDynForm1::m_ctrlTesto005;
CFreeExtEdit CEditDynForm1::m_ctrlTesto006;
CFreeExtEdit CEditDynForm1::m_ctrlTesto007;
CFreeExtEdit CEditDynForm1::m_ctrlTesto008;
CFreeExtEdit CEditDynForm1::m_ctrlTesto009;
CFreeExtEdit CEditDynForm1::m_ctrlTesto010;
CFreeExtEdit CEditDynForm1::m_ctrlTesto011;
CFreeExtEdit CEditDynForm1::m_ctrlTesto012;
CFreeExtEdit CEditDynForm1::m_ctrlTesto013;
CFreeExtEdit CEditDynForm1::m_ctrlTesto014;
CFreeExtEdit CEditDynForm1::m_ctrlTesto015;
CFreeExtEdit CEditDynForm1::m_ctrlTesto016;
CFreeExtEdit CEditDynForm1::m_ctrlTesto017;
CFreeExtEdit CEditDynForm1::m_ctrlTesto018;
CFreeExtEdit CEditDynForm1::m_ctrlTesto019;
CFreeExtEdit CEditDynForm1::m_ctrlTesto020;
CFreeExtEdit CEditDynForm1::m_ctrlTesto021;
CFreeExtEdit CEditDynForm1::m_ctrlTesto022;
CFreeExtEdit CEditDynForm1::m_ctrlTesto023;
CFreeExtEdit CEditDynForm1::m_ctrlTesto024;
CFreeExtEdit CEditDynForm1::m_ctrlTesto025;
CFreeExtEdit CEditDynForm1::m_ctrlTesto026;
CFreeExtEdit CEditDynForm1::m_ctrlTesto027;
CFreeExtEdit CEditDynForm1::m_ctrlTesto028;
CFreeExtEdit CEditDynForm1::m_ctrlTesto029;
CFreeExtEdit CEditDynForm1::m_ctrlTesto030;
CFreeExtEdit CEditDynForm1::m_ctrlTesto031;
CFreeExtEdit CEditDynForm1::m_ctrlTesto032;
CFreeExtEdit CEditDynForm1::m_ctrlTesto033;
CFreeExtEdit CEditDynForm1::m_ctrlTesto034;
CFreeExtEdit CEditDynForm1::m_ctrlTesto035;
CFreeExtEdit CEditDynForm1::m_ctrlTesto036;
CFreeExtEdit CEditDynForm1::m_ctrlTesto037;
CFreeExtEdit CEditDynForm1::m_ctrlTesto038;
CFreeExtEdit CEditDynForm1::m_ctrlTesto039;
CFreeExtEdit CEditDynForm1::m_ctrlTesto040;
CFreeExtEdit CEditDynForm1::m_ctrlTesto041;
CFreeExtEdit CEditDynForm1::m_ctrlTesto042;
CFreeExtEdit CEditDynForm1::m_ctrlTesto043;
CFreeExtEdit CEditDynForm1::m_ctrlTesto044;
CFreeExtEdit CEditDynForm1::m_ctrlTesto045;
CFreeExtEdit CEditDynForm1::m_ctrlTesto046;
CFreeExtEdit CEditDynForm1::m_ctrlTesto047;
CFreeExtEdit CEditDynForm1::m_ctrlTesto048;
CFreeExtEdit CEditDynForm1::m_ctrlTesto049;
CFreeExtEdit CEditDynForm1::m_ctrlTesto050;
CFreeExtEdit CEditDynForm1::m_ctrlTesto051;
CFreeExtEdit CEditDynForm1::m_ctrlTesto052;
CFreeExtEdit CEditDynForm1::m_ctrlTesto053;
CFreeExtEdit CEditDynForm1::m_ctrlTesto054;
CFreeExtEdit CEditDynForm1::m_ctrlTesto055;
CFreeExtEdit CEditDynForm1::m_ctrlTesto056;
CFreeExtEdit CEditDynForm1::m_ctrlTesto057;
CFreeExtEdit CEditDynForm1::m_ctrlTesto058;
CFreeExtEdit CEditDynForm1::m_ctrlTesto059;
CFreeExtEdit CEditDynForm1::m_ctrlTesto060;
CFreeExtEdit CEditDynForm1::m_ctrlTesto061;
CFreeExtEdit CEditDynForm1::m_ctrlTesto062;
CFreeExtEdit CEditDynForm1::m_ctrlTesto063;
CFreeExtEdit CEditDynForm1::m_ctrlTesto064;
CFreeExtEdit CEditDynForm1::m_ctrlTesto065;
CFreeExtEdit CEditDynForm1::m_ctrlTesto066;
CFreeExtEdit CEditDynForm1::m_ctrlTesto067;
CFreeExtEdit CEditDynForm1::m_ctrlTesto068;
CFreeExtEdit CEditDynForm1::m_ctrlTesto069;
CFreeExtEdit CEditDynForm1::m_ctrlTesto070;
CFreeExtEdit CEditDynForm1::m_ctrlTesto071;
CFreeExtEdit CEditDynForm1::m_ctrlTesto072;
CFreeExtEdit CEditDynForm1::m_ctrlTesto073;
CFreeExtEdit CEditDynForm1::m_ctrlTesto074;
CFreeExtEdit CEditDynForm1::m_ctrlTesto075;
CFreeExtEdit CEditDynForm1::m_ctrlTesto076;
CFreeExtEdit CEditDynForm1::m_ctrlTesto077;
CFreeExtEdit CEditDynForm1::m_ctrlTesto078;
CFreeExtEdit CEditDynForm1::m_ctrlTesto079;
CFreeExtEdit CEditDynForm1::m_ctrlTesto080;
CFreeExtEdit CEditDynForm1::m_ctrlTesto081;
CFreeExtEdit CEditDynForm1::m_ctrlTesto082;
CFreeExtEdit CEditDynForm1::m_ctrlTesto083;
CFreeExtEdit CEditDynForm1::m_ctrlTesto084;
CFreeExtEdit CEditDynForm1::m_ctrlTesto085;
CFreeExtEdit CEditDynForm1::m_ctrlTesto086;
CFreeExtEdit CEditDynForm1::m_ctrlTesto087;
CFreeExtEdit CEditDynForm1::m_ctrlTesto088;
CFreeExtEdit CEditDynForm1::m_ctrlTesto089;
CFreeExtEdit CEditDynForm1::m_ctrlTesto090;
CFreeExtEdit CEditDynForm1::m_ctrlTesto091;
CFreeExtEdit CEditDynForm1::m_ctrlTesto092;
CFreeExtEdit CEditDynForm1::m_ctrlTesto093;
CFreeExtEdit CEditDynForm1::m_ctrlTesto094;
CFreeExtEdit CEditDynForm1::m_ctrlTesto095;
CFreeExtEdit CEditDynForm1::m_ctrlTesto096;
CFreeExtEdit CEditDynForm1::m_ctrlTesto097;
CFreeExtEdit CEditDynForm1::m_ctrlTesto098;
CFreeExtEdit CEditDynForm1::m_ctrlTesto099;

CExtEdit CEditDynForm1::m_ctrlFumo;
CExtEdit CEditDynForm1::m_ctrlCaffe;
CExtEdit CEditDynForm1::m_ctrlSigarette;
CExtEdit CEditDynForm1::m_ctrlFarmaci;
CExtEdit CEditDynForm1::m_ctrlAlcool;
CExtEdit CEditDynForm1::m_ctrlAssunzione;
CExtEdit CEditDynForm1::m_ctrlSuperalcolici;

CExtEdit CEditDynForm1::m_ctrlPremedPosologia;

CExtDateEdit CEditDynForm1::m_ctrlEsameStrumentaleInizio;
CExtDateEdit CEditDynForm1::m_ctrlEsameStrumentaleFine;

CEdit CEditDynForm1::m_ctrlPazientiCroniciScoreHB;
CEdit CEditDynForm1::m_ctrlPazientiCroniciScoreS;
CEdit CEditDynForm1::m_ctrlNumeroTotalePolipi;

CMaskEdit CEditDynForm1::m_ctrlEditTempoRetrazione;

CEdit CEditDynForm1::m_ctrlEditMedicoRicerca;

CEditDynForm1::CEditDynForm1(CWnd* pParent, CEsamiView* pEsamiView, long lContenuto)
: CEndoxDynForm(CEditDynForm1::IDD, pParent, pEsamiView)
{
	m_lContenuto = lContenuto;

	m_bReadOnly = FALSE;
}

CEditDynForm1::~CEditDynForm1()
{
}

BEGIN_MESSAGE_MAP(CEditDynForm1, CEndoxDynForm)

	ON_MESSAGE(MSG_FREEEDIT_FOCUS_LOST, OnFormFocusLost)
	ON_MESSAGE(WM_EXTEDITCMB_CHANGED, OnExtEditCmbChanged)

	ON_WM_CTLCOLOR()

END_MESSAGE_MAP()

void CEditDynForm1::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lContenuto, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[lContenuto] == NULL)
	{
		pEsamiView->m_pDynForm[lContenuto] = new CEditDynForm1(NULL, pEsamiView, lContenuto);
		if (pEsamiView->m_pDynForm[lContenuto] != NULL)
		{
			pEsamiView->m_pDynForm[lContenuto]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[lContenuto]->m_lColore = lColore;
			pEsamiView->m_pDynForm[lContenuto]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[lContenuto]->CreateChildForm(CEditDynForm1::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CEditDynForm1::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_TEXT:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			if (m_crCampoObbligatorio > 0)
				pDC->SetBkColor(m_crCampoObbligatorio);

			break;
		}
		case IDC_EDIT:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

void CEditDynForm1::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	switch(m_lContenuto)
	{
		case edt_progressivo:
		{
			if (!pDX->m_bSaveAndValidate)
			{
				if (!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore))
					DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lContatore, m_pEsamiView->m_pEsamiSet->GetRecordset());
				else
					SetDlgItemText(IDC_EDIT, "");
			}

			break;
		}
		case edt_dataesame:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlDataEsame);

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlDataEsame.m_strRicercaView);
			else
				DDX_DateTimeMask(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lData, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
		case edt_progressivoanno:
		{
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sProgressivoAnno, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
		case edt_codiceprenotazione:
		{
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sCodicePrenotazione, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
		case edt_camera:
		{
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lCamera, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
		case edt_farmacotrial:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlFarmacoTrial);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sFarmacoTrial, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
		case edt_premedicazioni:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlPremedicazioni);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sPremedicazioni, m_pEsamiView->m_pEsamiSet->GetRecordset());

			if (pDX->m_bSaveAndValidate)
				m_pEsamiView->m_pEsamiSet->m_lIdPremedicazione = m_ctrlPremedicazioni.m_lContatore;

			break;
		}
		case edt_condottofino:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlEstensione);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sEstensione, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
		case edt_valutazione:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlValutazione);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sValutazione, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
		case edt_tipovisita:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlNrControllo);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sTipoVisita, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
		case edt_quadro:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlQuadro);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sQuadro, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
		case edt_durata:
		{
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lDurata, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
		case edt_prossimo:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlDataProssimo);

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlDataProssimo.m_strRicercaView);
			else
				DDX_DateTimeMask(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lDataControllo, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
		case edt_studio:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlStudio);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sStudio, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
		case edt_guarigione:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlGuarigione);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sGuarigione, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
		case edt_difficolta:
		{
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lDifficolta, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
		case edt_anestesista:
		{
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sAnestesista, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
		case edt_sedeesame:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlSedeEsame);
			DDX_FieldSedeEsame(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lIDSedeEsame, m_pEsamiView->m_pEsamiSet);

			break;
		}
		case edt_salaesame:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlSalaEsame);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sSalaEsame, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
		case edt_libero000:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto000);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto000, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());
			
			break;
		}
		case edt_libero001:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto001);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto001, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero002:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto002);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto002, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero003:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto003);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto003, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero004:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto004);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto004, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero005:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto005);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto005, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero006:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto006);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto006, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero007:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto007);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto007, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero008:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto008);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto008, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero009:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto009);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto009, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero010:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto010);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto010, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero011:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto011);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto011, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero012:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto012);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto012, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero013:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto013);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto013, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero014:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto014);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto014, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero015:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto015);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto015, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero016:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto016);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto016, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero017:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto017);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto017, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero018:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto018);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto018, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero019:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto019);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto019, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero020:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto020);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto020, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero021:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto021);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto021, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero022:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto022);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto022, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero023:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto023);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto023, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero024:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto024);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto024, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero025:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto025);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto025, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero026:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto026);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto026, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero027:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto027);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto027, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero028:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto028);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto028, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero029:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto029);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto029, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero030:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto030);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto030, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero031:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto031);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto031, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero032:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto032);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto032, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero033:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto033);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto033, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero034:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto034);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto034, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero035:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto035);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto035, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero036:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto036);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto036, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero037:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto037);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto037, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero038:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto038);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto038, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero039:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto039);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto039, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero040:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto040);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto040, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero041:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto041);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto041, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero042:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto042);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto042, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero043:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto043);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto043, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero044:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto044);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto044, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero045:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto045);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto045, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero046:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto046);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto046, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero047:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto047);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto047, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero048:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto048);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto048, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero049:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto049);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto049, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero050:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto050);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto050, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero051:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto051);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto051, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero052:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto052);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto052, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero053:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto053);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto053, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero054:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto054);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto054, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero055:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto055);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto055, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero056:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto056);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto056, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero057:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto057);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto057, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero058:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto058);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto058, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero059:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto059);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto059, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero060:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto060);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto060, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero061:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto061);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto061, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero062:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto062);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto062, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero063:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto063);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto063, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero064:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto064);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto064, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero065:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto065);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto065, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero066:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto066);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto066, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero067:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto067);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto067, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero068:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto068);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto068, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero069:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto069);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto069, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero070:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto070);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto070, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero071:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto071);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto071, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero072:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto072);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto072, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero073:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto073);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto073, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero074:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto074);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto074, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero075:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto075);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto075, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero076:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto076);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto076, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero077:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto077);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto077, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero078:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto078);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto078, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero079:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto079);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto079, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero080:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto080);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto080, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero081:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto081);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto081, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero082:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto082);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto082, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero083:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto083);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto083, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero084:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto084);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto084, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero085:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto085);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto085, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero086:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto086);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto086, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero087:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto087);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto087, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero088:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto088);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto088, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero089:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto089);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto089, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero090:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto090);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto090, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero091:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto091);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto091, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero092:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto092);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto092, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero093:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto093);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto093, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero094:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto094);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto094, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero095:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto095);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto095, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero096:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto096);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto096, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero097:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto097);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto097, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero098:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto098);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto098, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_libero099:
		{
			if (pDX->m_bSaveAndValidate && !ControlloNumerico())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR));
				GetDlgItem(IDC_EDIT)->SetWindowText("");
				break;
			}

			DDX_Control(pDX, IDC_EDIT, m_ctrlTesto099);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto099, m_pEsamiView->m_pEsamiSet->m_setEP.GetRecordset());

			break;
		}
		case edt_fumo:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlFumo);
			DDX_FieldCombo(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lFumo, m_pEsamiView->m_pEsamiSet, CMB_ANA_FUMO);
			break;
		}
		case edt_caffe:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlCaffe);
			DDX_FieldCombo(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lCaffe, m_pEsamiView->m_pEsamiSet, CMB_ANA_CAFF);
			break;
		}
		case edt_sigarette:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlSigarette);
			DDX_FieldCombo(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lSigarette, m_pEsamiView->m_pEsamiSet, CMB_ANA_SIGA);
			break;
		}
		case edt_farmaci:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlFarmaci);
			DDX_FieldText (pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sDenFarmaci, m_pEsamiView->m_pEsamiSet->GetRecordset());
			break;
		}
		case edt_alcool:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlAlcool);
			DDX_FieldCombo(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lAlcool, m_pEsamiView->m_pEsamiSet, CMB_ANA_ALCO);
			break;
		}
		case edt_assunzione:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlAssunzione);
			DDX_FieldCombo(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lAssunzione, m_pEsamiView->m_pEsamiSet, CMB_ANA_ASSU);
			break;
		}
		case edt_superalcolici:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlSuperalcolici);
			DDX_FieldCombo(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lSuperAlcolici, m_pEsamiView->m_pEsamiSet, CMB_ANA_SUPE);
			break;
		}
		case edt_premedposologia:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlPremedPosologia);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sPremedPosologia, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
		case edt_codesame:
		{
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sCodEsame, m_pEsamiView->m_pEsamiSet->GetRecordset());
			break;
		}
		//Luiz - 13/05/2019 - P3 - Atualiza nome/sobrenome Médico - Inclui Médicos solicitantes
		case edt_medico2:
		{
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sInvMedico2, m_pEsamiView->m_pEsamiSet->GetRecordset());
			break;
		}
		case edt_medico3:
		{
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sInvMedico3, m_pEsamiView->m_pEsamiSet->GetRecordset());
			break;
		}
		case edt_medico4:
		{
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sInvMedico4, m_pEsamiView->m_pEsamiSet->GetRecordset());
			break;
		} 

		case edt_paziente_passaporto: //Julio - BUG 3285 - Adequação de laudos (extra)
		{
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pPazientiSet->m_sIdentificazionePassaporto, m_pEsamiView->m_pPazientiSet->GetRecordset());
			break;
		}
		case edt_paziente_doc1: //Julio - BUG 3285 - Adequação de laudos (extra)
		{
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pPazientiSet->m_sIdentificazioneDoc1, m_pEsamiView->m_pPazientiSet->GetRecordset());
			break;
		}
		case edt_paziente_doc2: //Julio - BUG 3285 - Adequação de laudos (extra)
		{
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pPazientiSet->m_sIdentificazioneDoc2, m_pEsamiView->m_pPazientiSet->GetRecordset());
			break;
		}
		
		case edt_refertointegrato_firma: //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
		{
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_setRI.m_sSignature, m_pEsamiView->m_pEsamiSet->m_setRI.GetRecordset());
			break;
		}



		case edt_tempochiusura:
		{
			if (pDX->m_bSaveAndValidate == FALSE)
			{
				if (m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_sDataOraSuperLock) == TRUE || m_pEsamiView->m_pEsamiSet->m_sDataOraSuperLock == "")
					SetDlgItemText(IDC_EDIT, theApp.GetMessageString(IDS_ESAMEINCORSO));
				else
				{
					CCustomDate customStart = CCustomDate(m_pEsamiView->m_pEsamiSet->m_lData);
					COleDateTime start = COleDateTime(customStart.GetYear(), customStart.GetMonth(), customStart.GetDay(), customStart.GetHour(), customStart.GetMinute(), 0);
					COleDateTime stop = COleDateTime(atoi(m_pEsamiView->m_pEsamiSet->m_sDataOraSuperLock.Left(4)),
														atoi(m_pEsamiView->m_pEsamiSet->m_sDataOraSuperLock.Mid(4,2)),
														atoi(m_pEsamiView->m_pEsamiSet->m_sDataOraSuperLock.Mid(6,2)),
														atoi(m_pEsamiView->m_pEsamiSet->m_sDataOraSuperLock.Mid(8,2)),
														atoi(m_pEsamiView->m_pEsamiSet->m_sDataOraSuperLock.Mid(10,2)),
														0);
					COleDateTimeSpan timeDiff = stop - start;

					CString result;
					result.Format("%li %s %li %s %li %s", timeDiff.GetDays(), 
															theApp.GetMessageString(IDS_GIORNI), 
															timeDiff.GetHours(), 
															theApp.GetMessageString(IDS_ORE),
															timeDiff.GetMinutes(),
															theApp.GetMessageString(IDS_MINUTI));
					SetDlgItemText(IDC_EDIT, result);
				}
			}

			break;
		}
		case edt_tempoconvalida:
		{
			if (pDX->m_bSaveAndValidate == FALSE)
			{
				if (m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_sDataOraLock) || m_pEsamiView->m_pEsamiSet->m_sDataOraLock.IsEmpty())
				{
					SetDlgItemText(IDC_EDIT, theApp.GetMessageString(IDS_ESAMEINCORSO));
				}
				else
				{
					CCustomDate customStart = CCustomDate(m_pEsamiView->m_pEsamiSet->m_lData);
					COleDateTime start = COleDateTime(customStart.GetYear(), customStart.GetMonth(), customStart.GetDay(), customStart.GetHour(), customStart.GetMinute(), 0);

					COleDateTime stop = COleDateTime(atoi(m_pEsamiView->m_pEsamiSet->m_sDataOraLock.Left(4)),
														atoi(m_pEsamiView->m_pEsamiSet->m_sDataOraLock.Mid(4,2)),
														atoi(m_pEsamiView->m_pEsamiSet->m_sDataOraLock.Mid(6,2)),
														atoi(m_pEsamiView->m_pEsamiSet->m_sDataOraLock.Mid(8,2)),
														atoi(m_pEsamiView->m_pEsamiSet->m_sDataOraLock.Mid(10,2)),
														0);

					COleDateTimeSpan timeDiff = stop - start;
					CString result;
						
					result.Format("%li %s %li %s %li %s", timeDiff.GetDays(), 
															theApp.GetMessageString(IDS_GIORNI), 
															timeDiff.GetHours(), 
															theApp.GetMessageString(IDS_ORE),
															timeDiff.GetMinutes(),
															theApp.GetMessageString(IDS_MINUTI));
					SetDlgItemText(IDC_EDIT, result);
				}
			}

			break;
		}

		case edt_codicericovero:
		{
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sRicovero, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}

		case edt_barcodericovero:
		{
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sIdEpisodioRicovero, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}

		case edt_assiden:
		{
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pPazientiSet->m_sAssIden, m_pEsamiView->m_pPazientiSet->GetRecordset());

			break;
		}
		case edt_codalfa:
		{
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pPazientiSet->m_sCodAlfa, m_pEsamiView->m_pPazientiSet->GetRecordset());

			break;
		}
		case edt_esamestrumentale_orainizio:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlEsameStrumentaleInizio);

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlEsameStrumentaleInizio.m_strRicercaView);
			else
				DDX_DateTimeMask(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lCustomDataOraInizioAcq, m_pEsamiView->m_pEsamiSet->GetRecordset());

			/*
			if (!pDX->m_bSaveAndValidate)
				SetDlgItemText(IDC_EDIT, CCustomDate(m_pEsamiView->m_pEsamiSet->m_lCustomDataOraInizioAcq).GetDate("%d/%m/%Y %H:%M"));
			*/

			break;
		}
		case edt_esamestrumentale_orafine:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlEsameStrumentaleFine);

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlEsameStrumentaleFine.m_strRicercaView);
			else
				DDX_DateTimeMask(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lCustomDataOraFineAcq, m_pEsamiView->m_pEsamiSet->GetRecordset());

			/*
			if (!pDX->m_bSaveAndValidate)
				SetDlgItemText(IDC_EDIT, CCustomDate(m_pEsamiView->m_pEsamiSet->m_lCustomDataOraFineAcq).GetDate("%d/%m/%Y %H:%M"));
			*/

			break;
		}
		case edt_esamestrumentale_durataoreminuti:
		{
			if (!pDX->m_bSaveAndValidate)
				SetDlgItemText(IDC_EDIT, GetStringOreDifferenza(m_pEsamiView->m_pEsamiSet->m_lCustomDataOraInizioAcq, m_pEsamiView->m_pEsamiSet->m_lCustomDataOraFineAcq, FALSE));

			break;
		}
		case edt_esamestrumentale_duratasolominuti:
		{
			if (!pDX->m_bSaveAndValidate)
				SetDlgItemText(IDC_EDIT, GetStringOreDifferenza(m_pEsamiView->m_pEsamiSet->m_lCustomDataOraInizioAcq, m_pEsamiView->m_pEsamiSet->m_lCustomDataOraFineAcq, TRUE));

			break;
		}
		case edt_pazienticronici_score_hb:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlPazientiCroniciScoreHB);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sPazientiCroniciScoreHB, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
		case edt_pazienticronici_score_s:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlPazientiCroniciScoreS);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sPazientiCroniciScoreS, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
		case edt_paziente_medicocurante:
		{
			if (!pDX->m_bSaveAndValidate)
				DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pPazientiSet->m_sMedicoCurante, m_pEsamiView->m_pPazientiSet->GetRecordset());

			break;
		}
		case edt_utente_inserimentoesame:
		{
			if (!pDX->m_bSaveAndValidate)
				SetDlgItemText(IDC_EDIT, CVistaUtentiMediciSet().GetDescrizione(m_pEsamiView->m_pEsamiSet->m_lIDUtenteInserimentoEsame));

			break;
		}
		case edt_numerototalepolipi:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlNumeroTotalePolipi);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lNumeroTotalePolipi, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
		case edt_temporetrazione:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlEditTempoRetrazione);

			if (pDX->m_bSaveAndValidate)
			{
				// da controllo a recordset //

				m_pEsamiView->m_pEsamiSet->m_lTempoRetrazione = 0;

				CString sTemp;
				m_ctrlEditTempoRetrazione.GetWindowText(sTemp);

				int iTemp = sTemp.Find(':');
				if (iTemp > 0)
				{
					CString sTemp1 = sTemp.Left(iTemp);
					CString sTemp2 = sTemp.Right(sTemp.GetLength() - (iTemp + 1));

					m_pEsamiView->m_pEsamiSet->m_lTempoRetrazione = ((atol(sTemp1) * 60) + atol(sTemp2));
				}
			}
			else
			{
				// da recordset a controllo //

				CString sTemp;
				sTemp.Format("%02li:%02li", m_pEsamiView->m_pEsamiSet->m_lTempoRetrazione / 60, m_pEsamiView->m_pEsamiSet->m_lTempoRetrazione % 60);

				m_ctrlEditTempoRetrazione.SetWindowText(sTemp);
			}
			break;
		}
		case edt_medico_ricerca:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlEditMedicoRicerca);
			break;
		}		
		case edt_integrazioneCodiceUrgenza:
		{
			if (!pDX->m_bSaveAndValidate)
			{
				if (CExtOrdiniSet().IsExtOrdiniRequest(m_pEsamiView->m_pEsamiSet->m_lContatore))
					GetDlgItem(IDC_EDIT)->SetWindowText(CExtOrdiniSet().GetPriorityFromID(m_pEsamiView->m_pEsamiSet->m_lContatore));
				else
					GetDlgItem(IDC_EDIT)->SetWindowText("");
			}

			break;
		}		
	}
}

BOOL CEditDynForm1::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(GetDlgItem(IDC_TEXT)->GetSafeHwnd(), CSize(0,50), CSize(100,50));
	AddAnchor(GetDlgItem(IDC_EDIT)->GetSafeHwnd(), CSize(0,50), CSize(100,50));

	switch(m_lContenuto)
	{
		case edt_progressivo:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_EDT_PROGRESSIVO));
			break;
		}
		case edt_dataesame:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_EDT_DATAESAME));
			m_ctrlDataEsame.SetParam(this, m_pEsamiView, theApp.GetMessageString(IDS_EDT_DATAESAME), DATA_ORA);
			break;
		}
		case edt_progressivoanno:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_EDT_PROGRESSIVOANNO));
			break;
		}
		case edt_codiceprenotazione:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_EDT_CODICEPRENOTAZIONE));
			break;
		}
		case edt_camera:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_EDT_CAMERA));
			break;
		}
		case edt_farmacotrial:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_EDT_FARMACOTRIAL));
			m_ctrlFarmacoTrial.SetParam(this, CMB_ESA_FARMAC, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_sFarmacoTrial, 3999);
			m_ctrlFarmacoTrial.SetParam(TRUE, FALSE, TRUE, TRUE, FALSE);
			break;
		}
		case edt_premedicazioni:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_EDT_PREMEDICAZIONI));
			m_ctrlPremedicazioni.SetParam(this, CMB_ESA_PREMED, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_sPremedicazioni, 3999);
			m_ctrlPremedicazioni.SetParam(TRUE, FALSE, TRUE, TRUE, FALSE);
			break;
		}
		case edt_condottofino:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_EDT_CONDOTTOFINO));
			m_ctrlEstensione.SetParam(FALSE, FALSE, FALSE, TRUE, FALSE);
			m_ctrlEstensione.SetParam(this, CMB_ESA_ESTENS, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_sEstensione, 3999);
			break;
		}
		case edt_valutazione:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_EDT_VALUTAZIONE));
			m_ctrlValutazione.SetParam(TRUE, FALSE, FALSE, TRUE, FALSE);
			m_ctrlValutazione.SetParam(this, CMB_ESA_VALUTA, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_sValutazione, 3999);
			break;
		}
		case edt_tipovisita:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_EDT_TIPOVISITA));
			m_ctrlNrControllo.SetParam(TRUE, FALSE, FALSE, TRUE, FALSE);
			m_ctrlNrControllo.SetParam(this, CMB_ESA_CONTRO, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_sTipoVisita, 3999);
			break;
		}
		case edt_quadro:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_EDT_QUADRO));
			m_ctrlQuadro.SetParam(TRUE, FALSE, FALSE, TRUE, FALSE);
			m_ctrlQuadro.SetParam(this, CMB_ESA_QUADRO, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_sQuadro, 3999);
			break;
		}
		case edt_durata:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_EDT_DURATA));
			break;
		}
		case edt_prossimo:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_EDT_PROSSIMO));
			m_ctrlDataProssimo.SetParam(this, m_pEsamiView, theApp.GetMessageString(IDS_EDT_PROSSIMO), DATA_ORA);
			break;
		}
		case edt_studio:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_EDT_STUDIO));
			m_ctrlStudio.SetParam(TRUE, FALSE, FALSE, TRUE, FALSE);
			m_ctrlStudio.SetParam(this, CMB_ESA_STUDIO, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_sStudio, 3999);
			break;
		}
		case edt_guarigione:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_EDT_GUARIGIONE));
			m_ctrlGuarigione.SetParam(TRUE, FALSE, FALSE, TRUE, FALSE);
			m_ctrlGuarigione.SetParam(this, CMB_ESA_GUARIG, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_sGuarigione, 3999);
			break;
		}
		case edt_difficolta:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_EDT_DIFFICOLTA));
			break;
		}
		case edt_anestesista:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_EDT_ANESTESISTA));
			break;
		}
		case edt_sedeesame:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_EDT_SEDEESAME));
			SetWindowLong(m_ctrlSedeEsame.GetSafeHwnd(), GWL_STYLE, GetWindowLong(m_ctrlSedeEsame.GetSafeHwnd(), GWL_STYLE) | ES_UPPERCASE);
			break;
		}
		case edt_salaesame:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_EDT_SALAESAME));
			SetWindowLong(m_ctrlSalaEsame.GetSafeHwnd(), GWL_STYLE, GetWindowLong(m_ctrlSalaEsame.GetSafeHwnd(), GWL_STYLE) | ES_UPPERCASE);
			break;
		}
		case edt_libero000:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[0]);
			m_ctrlTesto000.SetParam(this, CMB_ESA_LIBERO000, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto000, 3999);
			m_ctrlTesto000.SetParam(theApp.m_bComboMultipleSel[0], FALSE, TRUE, theApp.m_bComboActive[0], theApp.m_bComboUppercase[0]);
			break;
		}
		case edt_libero001:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[1]);
			m_ctrlTesto001.SetParam(this, CMB_ESA_LIBERO001, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto001, 3999);
			m_ctrlTesto001.SetParam(theApp.m_bComboMultipleSel[1], FALSE, TRUE, theApp.m_bComboActive[1], theApp.m_bComboUppercase[1]);
			break;
		}
		case edt_libero002:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[2]);
			m_ctrlTesto002.SetParam(this, CMB_ESA_LIBERO002, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto002, 3999);
			m_ctrlTesto002.SetParam(theApp.m_bComboMultipleSel[2], FALSE, TRUE, theApp.m_bComboActive[2], theApp.m_bComboUppercase[2]);
			break;
		}
		case edt_libero003:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[3]);
			m_ctrlTesto003.SetParam(this, CMB_ESA_LIBERO003, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto003, 3999);
			m_ctrlTesto003.SetParam(theApp.m_bComboMultipleSel[3], FALSE, TRUE, theApp.m_bComboActive[3], theApp.m_bComboUppercase[3]);
			
			break;
		}
		case edt_libero004:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[4]);
			m_ctrlTesto004.SetParam(this, CMB_ESA_LIBERO004, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto004, 3999);
			m_ctrlTesto004.SetParam(theApp.m_bComboMultipleSel[4], FALSE, TRUE, theApp.m_bComboActive[4], theApp.m_bComboUppercase[4]);
			
			break;
		}
		case edt_libero005:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[5]);
			m_ctrlTesto005.SetParam(this, CMB_ESA_LIBERO005, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto005, 3999);
			m_ctrlTesto005.SetParam(theApp.m_bComboMultipleSel[5], FALSE, TRUE, theApp.m_bComboActive[5], theApp.m_bComboUppercase[5]);
			
			break;
		}
		case edt_libero006:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[6]);
			m_ctrlTesto006.SetParam(this, CMB_ESA_LIBERO006, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto006, 3999);
			m_ctrlTesto006.SetParam(theApp.m_bComboMultipleSel[6], FALSE, TRUE, theApp.m_bComboActive[6], theApp.m_bComboUppercase[6]);
			
			break;
		}
		case edt_libero007:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[7]);
			m_ctrlTesto007.SetParam(this, CMB_ESA_LIBERO007, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto007, 3999);
			m_ctrlTesto007.SetParam(theApp.m_bComboMultipleSel[7], FALSE, TRUE, theApp.m_bComboActive[7], theApp.m_bComboUppercase[7]);
			
			break;
		}
		case edt_libero008:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[8]);
			m_ctrlTesto008.SetParam(this, CMB_ESA_LIBERO008, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto008, 3999);
			m_ctrlTesto008.SetParam(theApp.m_bComboMultipleSel[8], FALSE, TRUE, theApp.m_bComboActive[8], theApp.m_bComboUppercase[8]);
			
			break;
		}
		case edt_libero009:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[9]);
			m_ctrlTesto009.SetParam(this, CMB_ESA_LIBERO009, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto009, 3999);
			m_ctrlTesto009.SetParam(theApp.m_bComboMultipleSel[9], FALSE, TRUE, theApp.m_bComboActive[9], theApp.m_bComboUppercase[9]);
			
			break;
		}
		case edt_libero010:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[10]);
			m_ctrlTesto010.SetParam(this, CMB_ESA_LIBERO010, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto010, 3999);
			m_ctrlTesto010.SetParam(theApp.m_bComboMultipleSel[10], FALSE, TRUE, theApp.m_bComboActive[10], theApp.m_bComboUppercase[10]);
			
			break;
		}
		case edt_libero011:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[11]);
			m_ctrlTesto011.SetParam(this, CMB_ESA_LIBERO011, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto011, 3999);
			m_ctrlTesto011.SetParam(theApp.m_bComboMultipleSel[11], FALSE, TRUE, theApp.m_bComboActive[11], theApp.m_bComboUppercase[11]);
			
			break;
		}
		case edt_libero012:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[12]);
			m_ctrlTesto012.SetParam(this, CMB_ESA_LIBERO012, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto012, 3999);
			m_ctrlTesto012.SetParam(theApp.m_bComboMultipleSel[12], FALSE, TRUE, theApp.m_bComboActive[12], theApp.m_bComboUppercase[12]);
		
			break;
		}
		case edt_libero013:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[13]);
			m_ctrlTesto013.SetParam(this, CMB_ESA_LIBERO013, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto013, 3999);
			m_ctrlTesto013.SetParam(theApp.m_bComboMultipleSel[13], FALSE, TRUE, theApp.m_bComboActive[13], theApp.m_bComboUppercase[13]);
			
			break;
		}
		case edt_libero014:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[14]);
			m_ctrlTesto014.SetParam(this, CMB_ESA_LIBERO014, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto014, 3999);
			m_ctrlTesto014.SetParam(theApp.m_bComboMultipleSel[14], FALSE, TRUE, theApp.m_bComboActive[14], theApp.m_bComboUppercase[14]);
			
			break;
		}
		case edt_libero015:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[15]);
			m_ctrlTesto015.SetParam(this, CMB_ESA_LIBERO015, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto015, 3999);
			m_ctrlTesto015.SetParam(theApp.m_bComboMultipleSel[15], FALSE, TRUE, theApp.m_bComboActive[15], theApp.m_bComboUppercase[15]);
		
			break;
		}
		case edt_libero016:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[16]);
			m_ctrlTesto016.SetParam(this, CMB_ESA_LIBERO016, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto016, 3999);
			m_ctrlTesto016.SetParam(theApp.m_bComboMultipleSel[16], FALSE, TRUE, theApp.m_bComboActive[16], theApp.m_bComboUppercase[16]);
		
			break;
		}
		case edt_libero017:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[17]);
			m_ctrlTesto017.SetParam(this, CMB_ESA_LIBERO017, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto017, 3999);
			m_ctrlTesto017.SetParam(theApp.m_bComboMultipleSel[17], FALSE, TRUE, theApp.m_bComboActive[17], theApp.m_bComboUppercase[17]);
			
			break;
		}
		case edt_libero018:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[18]);
			m_ctrlTesto018.SetParam(this, CMB_ESA_LIBERO018, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto018, 3999);
			m_ctrlTesto018.SetParam(theApp.m_bComboMultipleSel[18], FALSE, TRUE, theApp.m_bComboActive[18], theApp.m_bComboUppercase[18]);
			
			break;
		}
		case edt_libero019:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[19]);
			m_ctrlTesto019.SetParam(this, CMB_ESA_LIBERO019, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto019, 3999);
			m_ctrlTesto019.SetParam(theApp.m_bComboMultipleSel[19], FALSE, TRUE, theApp.m_bComboActive[19], theApp.m_bComboUppercase[19]);
			
			break;
		}
		case edt_libero020:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[20]);
			m_ctrlTesto020.SetParam(this, CMB_ESA_LIBERO020, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto020, 3999);
			m_ctrlTesto020.SetParam(theApp.m_bComboMultipleSel[20], FALSE, TRUE, theApp.m_bComboActive[20], theApp.m_bComboUppercase[20]);
			
			break;
		}
		case edt_libero021:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[21]);
			m_ctrlTesto021.SetParam(this, CMB_ESA_LIBERO021, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto021, 3999);
			m_ctrlTesto021.SetParam(theApp.m_bComboMultipleSel[21], FALSE, TRUE, theApp.m_bComboActive[21], theApp.m_bComboUppercase[21]);
			
			break;
		}
		case edt_libero022:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[22]);
			m_ctrlTesto022.SetParam(this, CMB_ESA_LIBERO022, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto022, 3999);
			m_ctrlTesto022.SetParam(theApp.m_bComboMultipleSel[22], FALSE, TRUE, theApp.m_bComboActive[22], theApp.m_bComboUppercase[22]);
			
			break;
		}
		case edt_libero023:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[23]);
			m_ctrlTesto023.SetParam(this, CMB_ESA_LIBERO023, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto023, 3999);
			m_ctrlTesto023.SetParam(theApp.m_bComboMultipleSel[23], FALSE, TRUE, theApp.m_bComboActive[23], theApp.m_bComboUppercase[23]);
			
			break;
		}
		case edt_libero024:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[24]);
			m_ctrlTesto024.SetParam(this, CMB_ESA_LIBERO024, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto024, 3999);
			m_ctrlTesto024.SetParam(theApp.m_bComboMultipleSel[24], FALSE, TRUE, theApp.m_bComboActive[24], theApp.m_bComboUppercase[24]);
			
			break;
		}
		case edt_libero025:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[25]);
			m_ctrlTesto025.SetParam(this, CMB_ESA_LIBERO025, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto025, 3999);
			m_ctrlTesto025.SetParam(theApp.m_bComboMultipleSel[25], FALSE, TRUE, theApp.m_bComboActive[25], theApp.m_bComboUppercase[25]);
			
			break;
		}
		case edt_libero026:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[26]);
			m_ctrlTesto026.SetParam(this, CMB_ESA_LIBERO026, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto026, 3999);
			m_ctrlTesto026.SetParam(theApp.m_bComboMultipleSel[26], FALSE, TRUE, theApp.m_bComboActive[26], theApp.m_bComboUppercase[26]);
			
			break;
		}
		case edt_libero027:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[27]);
			m_ctrlTesto027.SetParam(this, CMB_ESA_LIBERO027, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto027, 3999);
			m_ctrlTesto027.SetParam(theApp.m_bComboMultipleSel[27], FALSE, TRUE, theApp.m_bComboActive[27], theApp.m_bComboUppercase[27]);
			
			break;
		}
		case edt_libero028:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[28]);
			m_ctrlTesto028.SetParam(this, CMB_ESA_LIBERO028, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto028, 3999);
			m_ctrlTesto028.SetParam(theApp.m_bComboMultipleSel[28], FALSE, TRUE, theApp.m_bComboActive[28], theApp.m_bComboUppercase[28]);
			
			break;
		}
		case edt_libero029:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[29]);
			m_ctrlTesto029.SetParam(this, CMB_ESA_LIBERO029, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto029, 3999);
			m_ctrlTesto029.SetParam(theApp.m_bComboMultipleSel[29], FALSE, TRUE, theApp.m_bComboActive[29], theApp.m_bComboUppercase[29]);
			
			break;
		}
		case edt_libero030:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[30]);
			m_ctrlTesto030.SetParam(this, CMB_ESA_LIBERO030, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto030, 3999);
			m_ctrlTesto030.SetParam(theApp.m_bComboMultipleSel[30], FALSE, TRUE, theApp.m_bComboActive[30], theApp.m_bComboUppercase[30]);
			
			break;
		}
		case edt_libero031:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[31]);
			m_ctrlTesto031.SetParam(this, CMB_ESA_LIBERO031, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto031, 3999);
			m_ctrlTesto031.SetParam(theApp.m_bComboMultipleSel[31], FALSE, TRUE, theApp.m_bComboActive[31], theApp.m_bComboUppercase[31]);
		
			break;
		}
		case edt_libero032:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[32]);
			m_ctrlTesto032.SetParam(this, CMB_ESA_LIBERO032, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto032, 3999);
			m_ctrlTesto032.SetParam(theApp.m_bComboMultipleSel[32], FALSE, TRUE, theApp.m_bComboActive[32], theApp.m_bComboUppercase[32]);
			
			break;
		}
		case edt_libero033:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[33]);
			m_ctrlTesto033.SetParam(this, CMB_ESA_LIBERO033, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto033, 3999);
			m_ctrlTesto033.SetParam(theApp.m_bComboMultipleSel[33], FALSE, TRUE, theApp.m_bComboActive[33], theApp.m_bComboUppercase[33]);
			
			break;
		}
		case edt_libero034:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[34]);
			m_ctrlTesto034.SetParam(this, CMB_ESA_LIBERO034, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto034, 3999);
			m_ctrlTesto034.SetParam(theApp.m_bComboMultipleSel[34], FALSE, TRUE, theApp.m_bComboActive[34], theApp.m_bComboUppercase[34]);
			
			break;
		}
		case edt_libero035:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[35]);
			m_ctrlTesto035.SetParam(this, CMB_ESA_LIBERO035, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto035, 3999);
			m_ctrlTesto035.SetParam(theApp.m_bComboMultipleSel[35], FALSE, TRUE, theApp.m_bComboActive[35], theApp.m_bComboUppercase[35]);
			
			break;
		}
		case edt_libero036:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[36]);
			m_ctrlTesto036.SetParam(this, CMB_ESA_LIBERO036, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto036, 3999);
			m_ctrlTesto036.SetParam(theApp.m_bComboMultipleSel[36], FALSE, TRUE, theApp.m_bComboActive[36], theApp.m_bComboUppercase[36]);
		
			break;
		}
		case edt_libero037:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[37]);
			m_ctrlTesto037.SetParam(this, CMB_ESA_LIBERO037, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto037, 3999);
			m_ctrlTesto037.SetParam(theApp.m_bComboMultipleSel[37], FALSE, TRUE, theApp.m_bComboActive[37], theApp.m_bComboUppercase[37]);
			
			break;
		}
		case edt_libero038:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[38]);
			m_ctrlTesto038.SetParam(this, CMB_ESA_LIBERO038, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto038, 3999);
			m_ctrlTesto038.SetParam(theApp.m_bComboMultipleSel[38], FALSE, TRUE, theApp.m_bComboActive[38], theApp.m_bComboUppercase[38]);
			
			break;
		}
		case edt_libero039:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[39]);
			m_ctrlTesto039.SetParam(this, CMB_ESA_LIBERO039, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto039, 3999);
			m_ctrlTesto039.SetParam(theApp.m_bComboMultipleSel[39], FALSE, TRUE, theApp.m_bComboActive[39], theApp.m_bComboUppercase[39]);
			
			break;
		}
		case edt_libero040:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[40]);
			m_ctrlTesto040.SetParam(this, CMB_ESA_LIBERO040, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto040, 3999);
			m_ctrlTesto040.SetParam(theApp.m_bComboMultipleSel[40], FALSE, TRUE, theApp.m_bComboActive[40], theApp.m_bComboUppercase[40]);
			
			break;
		}
		case edt_libero041:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[41]);
			m_ctrlTesto041.SetParam(this, CMB_ESA_LIBERO041, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto041, 3999);
			m_ctrlTesto041.SetParam(theApp.m_bComboMultipleSel[41], FALSE, TRUE, theApp.m_bComboActive[41], theApp.m_bComboUppercase[41]);
			
			break;
		}
		case edt_libero042:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[42]);
			m_ctrlTesto042.SetParam(this, CMB_ESA_LIBERO042, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto042, 3999);
			m_ctrlTesto042.SetParam(theApp.m_bComboMultipleSel[42], FALSE, TRUE, theApp.m_bComboActive[42], theApp.m_bComboUppercase[42]);
			
			break;
		}
		case edt_libero043:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[43]);
			m_ctrlTesto043.SetParam(this, CMB_ESA_LIBERO043, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto043, 3999);
			m_ctrlTesto043.SetParam(theApp.m_bComboMultipleSel[43], FALSE, TRUE, theApp.m_bComboActive[43], theApp.m_bComboUppercase[43]);
			
			break;
		}
		case edt_libero044:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[44]);
			m_ctrlTesto044.SetParam(this, CMB_ESA_LIBERO044, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto044, 3999);
			m_ctrlTesto044.SetParam(theApp.m_bComboMultipleSel[44], FALSE, TRUE, theApp.m_bComboActive[44], theApp.m_bComboUppercase[44]);
			
			break;
		}
		case edt_libero045:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[45]);
			m_ctrlTesto045.SetParam(this, CMB_ESA_LIBERO045, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto045, 3999);
			m_ctrlTesto045.SetParam(theApp.m_bComboMultipleSel[45], FALSE, TRUE, theApp.m_bComboActive[45], theApp.m_bComboUppercase[45]);
			
			break;
		}
		case edt_libero046:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[46]);
			m_ctrlTesto046.SetParam(this, CMB_ESA_LIBERO046, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto046, 3999);
			m_ctrlTesto046.SetParam(theApp.m_bComboMultipleSel[46], FALSE, TRUE, theApp.m_bComboActive[46], theApp.m_bComboUppercase[46]);
			
			break;
		}
		case edt_libero047:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[47]);
			m_ctrlTesto047.SetParam(this, CMB_ESA_LIBERO047, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto047, 3999);
			m_ctrlTesto047.SetParam(theApp.m_bComboMultipleSel[47], FALSE, TRUE, theApp.m_bComboActive[47], theApp.m_bComboUppercase[47]);
			
			break;
		}
		case edt_libero048:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[48]);
			m_ctrlTesto048.SetParam(this, CMB_ESA_LIBERO048, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto048, 3999);
			m_ctrlTesto048.SetParam(theApp.m_bComboMultipleSel[48], FALSE, TRUE, theApp.m_bComboActive[48], theApp.m_bComboUppercase[48]);
			
			break;
		}
		case edt_libero049:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[49]);
			m_ctrlTesto049.SetParam(this, CMB_ESA_LIBERO049, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto049, 3999);
			m_ctrlTesto049.SetParam(theApp.m_bComboMultipleSel[49], FALSE, TRUE, theApp.m_bComboActive[49], theApp.m_bComboUppercase[49]);
			break;
		}
		case edt_libero050:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[50]);
			m_ctrlTesto050.SetParam(this, CMB_ESA_LIBERO050, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto050, 3999);
			m_ctrlTesto050.SetParam(theApp.m_bComboMultipleSel[50], FALSE, TRUE, theApp.m_bComboActive[50], theApp.m_bComboUppercase[50]);
			break;
		}
		case edt_libero051:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[51]);
			m_ctrlTesto051.SetParam(this, CMB_ESA_LIBERO051, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto051, 3999);
			m_ctrlTesto051.SetParam(theApp.m_bComboMultipleSel[51], FALSE, TRUE, theApp.m_bComboActive[51], theApp.m_bComboUppercase[51]);
			break;
		}
		case edt_libero052:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[52]);
			m_ctrlTesto052.SetParam(this, CMB_ESA_LIBERO052, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto052, 3999);
			m_ctrlTesto052.SetParam(theApp.m_bComboMultipleSel[52], FALSE, TRUE, theApp.m_bComboActive[52], theApp.m_bComboUppercase[52]);
			break;
		}
		case edt_libero053:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[53]);
			m_ctrlTesto053.SetParam(this, CMB_ESA_LIBERO053, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto053, 3999);
			m_ctrlTesto053.SetParam(theApp.m_bComboMultipleSel[53], FALSE, TRUE, theApp.m_bComboActive[53], theApp.m_bComboUppercase[53]);
			break;
		}
		case edt_libero054:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[54]);
			m_ctrlTesto054.SetParam(this, CMB_ESA_LIBERO054, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto054, 3999);
			m_ctrlTesto054.SetParam(theApp.m_bComboMultipleSel[54], FALSE, TRUE, theApp.m_bComboActive[54], theApp.m_bComboUppercase[54]);
			break;
		}
		case edt_libero055:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[55]);
			m_ctrlTesto055.SetParam(this, CMB_ESA_LIBERO055, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto055, 3999);
			m_ctrlTesto055.SetParam(theApp.m_bComboMultipleSel[55], FALSE, TRUE, theApp.m_bComboActive[55], theApp.m_bComboUppercase[55]);
			break;
		}
		case edt_libero056:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[56]);
			m_ctrlTesto056.SetParam(this, CMB_ESA_LIBERO056, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto056, 3999);
			m_ctrlTesto056.SetParam(theApp.m_bComboMultipleSel[56], FALSE, TRUE, theApp.m_bComboActive[56], theApp.m_bComboUppercase[56]);
			break;
		}
		case edt_libero057:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[57]);
			m_ctrlTesto057.SetParam(this, CMB_ESA_LIBERO057, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto057, 3999);
			m_ctrlTesto057.SetParam(theApp.m_bComboMultipleSel[57], FALSE, TRUE, theApp.m_bComboActive[57], theApp.m_bComboUppercase[57]);
			break;
		}
		case edt_libero058:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[58]);
			m_ctrlTesto058.SetParam(this, CMB_ESA_LIBERO058, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto058, 3999);
			m_ctrlTesto058.SetParam(theApp.m_bComboMultipleSel[58], FALSE, TRUE, theApp.m_bComboActive[58], theApp.m_bComboUppercase[58]);
			break;
		}
		case edt_libero059:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[59]);
			m_ctrlTesto059.SetParam(this, CMB_ESA_LIBERO059, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto059, 3999);
			m_ctrlTesto059.SetParam(theApp.m_bComboMultipleSel[59], FALSE, TRUE, theApp.m_bComboActive[59], theApp.m_bComboUppercase[59]);
			break;
		}
		case edt_libero060:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[60]);
			m_ctrlTesto060.SetParam(this, CMB_ESA_LIBERO060, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto060, 3999);
			m_ctrlTesto060.SetParam(theApp.m_bComboMultipleSel[60], FALSE, TRUE, theApp.m_bComboActive[60], theApp.m_bComboUppercase[60]);
			break;
		}
		case edt_libero061:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[61]);
			m_ctrlTesto061.SetParam(this, CMB_ESA_LIBERO061, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto061, 3999);
			m_ctrlTesto061.SetParam(theApp.m_bComboMultipleSel[61], FALSE, TRUE, theApp.m_bComboActive[61], theApp.m_bComboUppercase[61]);
			break;
		}
		case edt_libero062:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[62]);
			m_ctrlTesto062.SetParam(this, CMB_ESA_LIBERO062, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto062, 3999);
			m_ctrlTesto062.SetParam(theApp.m_bComboMultipleSel[62], FALSE, TRUE, theApp.m_bComboActive[62], theApp.m_bComboUppercase[62]);
			break;
		}
		case edt_libero063:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[63]);
			m_ctrlTesto063.SetParam(this, CMB_ESA_LIBERO063, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto063, 3999);
			m_ctrlTesto063.SetParam(theApp.m_bComboMultipleSel[63], FALSE, TRUE, theApp.m_bComboActive[63], theApp.m_bComboUppercase[63]);
			break;
		}
		case edt_libero064:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[64]);
			m_ctrlTesto064.SetParam(this, CMB_ESA_LIBERO064, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto064, 3999);
			m_ctrlTesto064.SetParam(theApp.m_bComboMultipleSel[64], FALSE, TRUE, theApp.m_bComboActive[64], theApp.m_bComboUppercase[64]);
			break;
		}
		case edt_libero065:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[65]);
			m_ctrlTesto065.SetParam(this, CMB_ESA_LIBERO065, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto065, 3999);
			m_ctrlTesto065.SetParam(theApp.m_bComboMultipleSel[65], FALSE, TRUE, theApp.m_bComboActive[65], theApp.m_bComboUppercase[65]);
			break;
		}
		case edt_libero066:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[66]);
			m_ctrlTesto066.SetParam(this, CMB_ESA_LIBERO066, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto066, 3999);
			m_ctrlTesto066.SetParam(theApp.m_bComboMultipleSel[66], FALSE, TRUE, theApp.m_bComboActive[66], theApp.m_bComboUppercase[66]);
			break;
		}
		case edt_libero067:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[67]);
			m_ctrlTesto067.SetParam(this, CMB_ESA_LIBERO067, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto067, 3999);
			m_ctrlTesto067.SetParam(theApp.m_bComboMultipleSel[67], FALSE, TRUE, theApp.m_bComboActive[67], theApp.m_bComboUppercase[67]);
			break;
		}
		case edt_libero068:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[68]);
			m_ctrlTesto068.SetParam(this, CMB_ESA_LIBERO068, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto068, 3999);
			m_ctrlTesto068.SetParam(theApp.m_bComboMultipleSel[68], FALSE, TRUE, theApp.m_bComboActive[68], theApp.m_bComboUppercase[68]);
			break;
		}
		case edt_libero069:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[69]);
			m_ctrlTesto069.SetParam(this, CMB_ESA_LIBERO069, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto069, 3999);
			m_ctrlTesto069.SetParam(theApp.m_bComboMultipleSel[69], FALSE, TRUE, theApp.m_bComboActive[69], theApp.m_bComboUppercase[69]);
			break;
		}
		case edt_libero070:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[70]);
			m_ctrlTesto070.SetParam(this, CMB_ESA_LIBERO070, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto070, 3999);
			m_ctrlTesto070.SetParam(theApp.m_bComboMultipleSel[70], FALSE, TRUE, theApp.m_bComboActive[70], theApp.m_bComboUppercase[70]);
			break;
		}
		case edt_libero071:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[71]);
			m_ctrlTesto071.SetParam(this, CMB_ESA_LIBERO071, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto071, 3999);
			m_ctrlTesto071.SetParam(theApp.m_bComboMultipleSel[71], FALSE, TRUE, theApp.m_bComboActive[71], theApp.m_bComboUppercase[71]);
			break;
		}
		case edt_libero072:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[72]);
			m_ctrlTesto072.SetParam(this, CMB_ESA_LIBERO072, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto072, 3999);
			m_ctrlTesto072.SetParam(theApp.m_bComboMultipleSel[72], FALSE, TRUE, theApp.m_bComboActive[72], theApp.m_bComboUppercase[72]);
			break;
		}
		case edt_libero073:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[73]);
			m_ctrlTesto073.SetParam(this, CMB_ESA_LIBERO073, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto073, 3999);
			m_ctrlTesto073.SetParam(theApp.m_bComboMultipleSel[73], FALSE, TRUE, theApp.m_bComboActive[73], theApp.m_bComboUppercase[73]);
			break;
		}
		case edt_libero074:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[74]);
			m_ctrlTesto074.SetParam(this, CMB_ESA_LIBERO074, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto074, 3999);
			m_ctrlTesto074.SetParam(theApp.m_bComboMultipleSel[74], FALSE, TRUE, theApp.m_bComboActive[74], theApp.m_bComboUppercase[74]);
			break;
		}
		case edt_libero075:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[75]);
			m_ctrlTesto075.SetParam(this, CMB_ESA_LIBERO075, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto075, 3999);
			m_ctrlTesto075.SetParam(theApp.m_bComboMultipleSel[75], FALSE, TRUE, theApp.m_bComboActive[75], theApp.m_bComboUppercase[75]);
			break;
		}
		case edt_libero076:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[76]);
			m_ctrlTesto076.SetParam(this, CMB_ESA_LIBERO076, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto076, 3999);
			m_ctrlTesto076.SetParam(theApp.m_bComboMultipleSel[76], FALSE, TRUE, theApp.m_bComboActive[76], theApp.m_bComboUppercase[76]);
			break;
		}
		case edt_libero077:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[77]);
			m_ctrlTesto077.SetParam(this, CMB_ESA_LIBERO077, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto077, 3999);
			m_ctrlTesto077.SetParam(theApp.m_bComboMultipleSel[77], FALSE, TRUE, theApp.m_bComboActive[77], theApp.m_bComboUppercase[77]);
			break;
		}
		case edt_libero078:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[78]);
			m_ctrlTesto078.SetParam(this, CMB_ESA_LIBERO078, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto078, 3999);
			m_ctrlTesto078.SetParam(theApp.m_bComboMultipleSel[78], FALSE, TRUE, theApp.m_bComboActive[78], theApp.m_bComboUppercase[78]);
			break;
		}
		case edt_libero079:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[79]);
			m_ctrlTesto079.SetParam(this, CMB_ESA_LIBERO079, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto079, 3999);
			m_ctrlTesto079.SetParam(theApp.m_bComboMultipleSel[79], FALSE, TRUE, theApp.m_bComboActive[79], theApp.m_bComboUppercase[79]);
			break;
		}
		case edt_libero080:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[80]);
			m_ctrlTesto080.SetParam(this, CMB_ESA_LIBERO080, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto080, 3999);
			m_ctrlTesto080.SetParam(theApp.m_bComboMultipleSel[80], FALSE, TRUE, theApp.m_bComboActive[80], theApp.m_bComboUppercase[80]);
			break;
		}
		case edt_libero081:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[81]);
			m_ctrlTesto081.SetParam(this, CMB_ESA_LIBERO081, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto081, 3999);
			m_ctrlTesto081.SetParam(theApp.m_bComboMultipleSel[81], FALSE, TRUE, theApp.m_bComboActive[81], theApp.m_bComboUppercase[81]);
			break;
		}
		case edt_libero082:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[82]);
			m_ctrlTesto082.SetParam(this, CMB_ESA_LIBERO082, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto082, 3999);
			m_ctrlTesto082.SetParam(theApp.m_bComboMultipleSel[82], FALSE, TRUE, theApp.m_bComboActive[82], theApp.m_bComboUppercase[82]);
			break;
		}
		case edt_libero083:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[83]);
			m_ctrlTesto083.SetParam(this, CMB_ESA_LIBERO083, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto083, 3999);
			m_ctrlTesto083.SetParam(theApp.m_bComboMultipleSel[83], FALSE, TRUE, theApp.m_bComboActive[83], theApp.m_bComboUppercase[83]);
			break;
		}
		case edt_libero084:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[84]);
			m_ctrlTesto084.SetParam(this, CMB_ESA_LIBERO084, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto084, 3999);
			m_ctrlTesto084.SetParam(theApp.m_bComboMultipleSel[84], FALSE, TRUE, theApp.m_bComboActive[84], theApp.m_bComboUppercase[84]);
			break;
		}
		case edt_libero085:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[85]);
			m_ctrlTesto085.SetParam(this, CMB_ESA_LIBERO085, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto085, 3999);
			m_ctrlTesto085.SetParam(theApp.m_bComboMultipleSel[85], FALSE, TRUE, theApp.m_bComboActive[85], theApp.m_bComboUppercase[85]);
			break;
		}
		case edt_libero086:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[86]);
			m_ctrlTesto086.SetParam(this, CMB_ESA_LIBERO086, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto086, 3999);
			m_ctrlTesto086.SetParam(theApp.m_bComboMultipleSel[86], FALSE, TRUE, theApp.m_bComboActive[86], theApp.m_bComboUppercase[86]);
			break;
		}
		case edt_libero087:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[87]);
			m_ctrlTesto087.SetParam(this, CMB_ESA_LIBERO087, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto087, 3999);
			m_ctrlTesto087.SetParam(theApp.m_bComboMultipleSel[87], FALSE, TRUE, theApp.m_bComboActive[87], theApp.m_bComboUppercase[87]);
			break;
		}
		case edt_libero088:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[88]);
			m_ctrlTesto088.SetParam(this, CMB_ESA_LIBERO088, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto088, 3999);
			m_ctrlTesto088.SetParam(theApp.m_bComboMultipleSel[88], FALSE, TRUE, theApp.m_bComboActive[88], theApp.m_bComboUppercase[88]);
			break;
		}
		case edt_libero089:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[89]);
			m_ctrlTesto089.SetParam(this, CMB_ESA_LIBERO089, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto089, 3999);
			m_ctrlTesto089.SetParam(theApp.m_bComboMultipleSel[89], FALSE, TRUE, theApp.m_bComboActive[89], theApp.m_bComboUppercase[89]);
			break;
		}
		case edt_libero090:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[90]);
			m_ctrlTesto090.SetParam(this, CMB_ESA_LIBERO090, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto090, 3999);
			m_ctrlTesto090.SetParam(theApp.m_bComboMultipleSel[90], FALSE, TRUE, theApp.m_bComboActive[90], theApp.m_bComboUppercase[90]);
			break;
		}
		case edt_libero091:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[91]);
			m_ctrlTesto091.SetParam(this, CMB_ESA_LIBERO091, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto091, 3999);
			m_ctrlTesto091.SetParam(theApp.m_bComboMultipleSel[91], FALSE, TRUE, theApp.m_bComboActive[91], theApp.m_bComboUppercase[91]);
			break;
		}
		case edt_libero092:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[92]);
			m_ctrlTesto092.SetParam(this, CMB_ESA_LIBERO092, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto092, 3999);
			m_ctrlTesto092.SetParam(theApp.m_bComboMultipleSel[92], FALSE, TRUE, theApp.m_bComboActive[92], theApp.m_bComboUppercase[92]);
			break;
		}
		case edt_libero093:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[93]);
			m_ctrlTesto093.SetParam(this, CMB_ESA_LIBERO093, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto093, 3999);
			m_ctrlTesto093.SetParam(theApp.m_bComboMultipleSel[93], FALSE, TRUE, theApp.m_bComboActive[93], theApp.m_bComboUppercase[93]);
			break;
		}
		case edt_libero094:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[94]);
			m_ctrlTesto094.SetParam(this, CMB_ESA_LIBERO094, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto094, 3999);
			m_ctrlTesto094.SetParam(theApp.m_bComboMultipleSel[94], FALSE, TRUE, theApp.m_bComboActive[94], theApp.m_bComboUppercase[94]);
			break;
		}
		case edt_libero095:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[95]);
			m_ctrlTesto095.SetParam(this, CMB_ESA_LIBERO095, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto095, 3999);
			m_ctrlTesto095.SetParam(theApp.m_bComboMultipleSel[95], FALSE, TRUE, theApp.m_bComboActive[95], theApp.m_bComboUppercase[95]);
			break;
		}
		case edt_libero096:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[96]);
			m_ctrlTesto096.SetParam(this, CMB_ESA_LIBERO096, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto096, 3999);
			m_ctrlTesto096.SetParam(theApp.m_bComboMultipleSel[96], FALSE, TRUE, theApp.m_bComboActive[96], theApp.m_bComboUppercase[96]);
			break;
		}
		case edt_libero097:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[97]);
			m_ctrlTesto097.SetParam(this, CMB_ESA_LIBERO097, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto097, 3999);
			m_ctrlTesto097.SetParam(theApp.m_bComboMultipleSel[97], FALSE, TRUE, theApp.m_bComboActive[97], theApp.m_bComboUppercase[97]);
			break;
		}
		case edt_libero098:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[98]);
			m_ctrlTesto098.SetParam(this, CMB_ESA_LIBERO098, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto098, 3999);
			m_ctrlTesto098.SetParam(theApp.m_bComboMultipleSel[98], FALSE, TRUE, theApp.m_bComboActive[98], theApp.m_bComboUppercase[98]);
			break;
		}
		case edt_libero099:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelText[99]);
			m_ctrlTesto099.SetParam(this, CMB_ESA_LIBERO099, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto099, 3999);
			m_ctrlTesto099.SetParam(theApp.m_bComboMultipleSel[99], FALSE, TRUE, theApp.m_bComboActive[99], theApp.m_bComboUppercase[99]);
			break;
		}
		case edt_fumo:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sAnamText[0]);
			m_ctrlFumo.SetParam(this, CMB_ANA_FUMO, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_lFumo, 255);
			m_ctrlFumo.SetParam(TRUE, FALSE, FALSE, TRUE, FALSE);
			break;
		}
		case edt_caffe:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sAnamText[2]);
			m_ctrlCaffe.SetParam(this, CMB_ANA_CAFF, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_lCaffe, 255);
			m_ctrlCaffe.SetParam(TRUE, FALSE, FALSE, TRUE, FALSE);
			break;
		}
		case edt_sigarette:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sAnamText[1]);
			m_ctrlSigarette.SetParam(this, CMB_ANA_SIGA, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_lSigarette, 255);
			m_ctrlSigarette.SetParam(TRUE, FALSE, FALSE, TRUE, FALSE);
			break;
		}
		case edt_farmaci:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sAnamText[5]);
			m_ctrlFarmaci.SetParam(this, CMB_ANA_FARM, m_pEsamiView->m_pEsamiSet, NULL, &m_pEsamiView->m_pEsamiSet->m_sDenFarmaci, 3999);
			m_ctrlFarmaci.SetParam(TRUE, FALSE, TRUE, TRUE, FALSE);
			break;
		}
		case edt_alcool:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sAnamText[3]);
			m_ctrlAlcool.SetParam(this, CMB_ANA_ALCO, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_lAlcool, 255);
			m_ctrlAlcool.SetParam(TRUE, FALSE, FALSE, TRUE, FALSE);
			break;
		}
		case edt_assunzione:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sAnamText[6]);
			m_ctrlAssunzione.SetParam(this, CMB_ANA_ASSU, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_lAssunzione, 255);
			m_ctrlAssunzione.SetParam(TRUE, FALSE, FALSE, TRUE, FALSE);
			break;
		}
		case edt_superalcolici:
		{
			SetDlgItemText(IDC_TEXT, theApp.m_sAnamText[4]);
			m_ctrlSuperalcolici.SetParam(this, CMB_ANA_SUPE, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_lSuperAlcolici, 255);
			m_ctrlSuperalcolici.SetParam(TRUE, FALSE, FALSE, TRUE, FALSE);
			break;
		}
		case edt_premedposologia:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_364));
			m_ctrlPremedPosologia.SetParam(this, NULL, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_sPremedPosologia, 255);
			m_ctrlPremedPosologia.SetParam(TRUE, FALSE, FALSE, FALSE, FALSE);
			break;
		}
		case edt_codesame:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_413));
			break;
		}
		//Luiz - 13/05/2019 - P3 - Atualiza nome/sobrenome Médico - Inclui Médicos solicitantes
		case edt_medico2:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_MEDICO2));
			break;
		}
		case edt_medico3:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_MEDICO3));
			break;
		}
		case edt_medico4:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_MEDICO4));
			break;
		}
		case edt_paziente_passaporto: //Julio - BUG 3285 - Adequação de laudos (extra)
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_PAZIENTE_PASSAPORTO));
			break;
		}
		case edt_paziente_doc1:		  //Julio - BUG 3285 - Adequação de laudos (extra)
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_PAZIENTE_DOC1));
			break;
		}
		case edt_paziente_doc2:		  //Julio - BUG 3285 - Adequação de laudos (extra)
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_PAZIENTE_DOC2));
			break;
		}

		case edt_refertointegrato_firma: //Julio - BUG 3744 - Retorno do Pathox para o TesiCapture
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_REFERTOINTEGRATO_FIRMA));
			break;
		}

		case edt_tempochiusura:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_415));
			break;
		}
		case edt_tempoconvalida:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_416));
			break;
		}
		case edt_codicericovero:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_417));
			break;
		}
		case edt_barcodericovero:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_467));
			break;
		}
		case edt_assiden:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_418));
			break;
		}
		case edt_codalfa:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_494));
			break;
		}
		case edt_esamestrumentale_orainizio:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_458));
			m_ctrlEsameStrumentaleInizio.SetParam(this, m_pEsamiView, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_458), DATA_ORA);

			break;
		}
		case edt_esamestrumentale_orafine:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_459));
			m_ctrlEsameStrumentaleFine.SetParam(this, m_pEsamiView, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_459), DATA_ORA);

			break;
		}
		case edt_esamestrumentale_durataoreminuti:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_460));
			break;
		}
		case edt_esamestrumentale_duratasolominuti:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_461));
			break;
		}
		case edt_pazienticronici_score_hb:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_485));
			m_ctrlPazientiCroniciScoreHB.ModifyStyle(0, ES_NUMBER);
			break;
		}
		case edt_pazienticronici_score_s:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_486));
			m_ctrlPazientiCroniciScoreS.ModifyStyle(0, ES_NUMBER);
			break;
		}
		case edt_paziente_medicocurante:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_10));
			break;
		}
		case edt_utente_inserimentoesame:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_496));
			break;
		}
		case edt_numerototalepolipi:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_507));
			m_ctrlNumeroTotalePolipi.ModifyStyle(0, ES_NUMBER);
			break;
		}
		case edt_temporetrazione:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_514));
			m_ctrlEditTempoRetrazione.SetEditMask("00:00", "__:__");
			break;
		}
		case edt_medico_ricerca:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_517));
			break;
		}
		case edt_integrazioneCodiceUrgenza:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_574));
			break;
		}
	}

	return bReturn;
}

LRESULT CEditDynForm1::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CEditDynForm1::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(FALSE);
}

LRESULT CEditDynForm1::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	m_bReadOnly = (BOOL)wParam;

	switch(m_lContenuto)
	{
		case edt_dataesame:
		{
			SendDlgItemMessage(IDC_EDIT, EM_SETREADONLY, wParam, lParam);
			break;
		}
		case edt_camera:
		case edt_farmacotrial:
		case edt_premedicazioni:
		case edt_condottofino:
		case edt_valutazione:
		case edt_tipovisita:
		case edt_quadro:
		case edt_durata:
		case edt_prossimo:
		case edt_studio:
		case edt_guarigione:
		case edt_difficolta:
		case edt_anestesista:
		case edt_libero000:
		case edt_libero001:
		case edt_libero002:
		case edt_libero003:
		case edt_libero004:
		case edt_libero005:
		case edt_libero006:
		case edt_libero007:
		case edt_libero008:
		case edt_libero009:
		case edt_libero010:
		case edt_libero011:
		case edt_libero012:
		case edt_libero013:
		case edt_libero014:
		case edt_libero015:
		case edt_libero016:
		case edt_libero017:
		case edt_libero018:
		case edt_libero019:
		case edt_libero020:
		case edt_libero021:
		case edt_libero022:
		case edt_libero023:
		case edt_libero024:
		case edt_libero025:
		case edt_libero026:
		case edt_libero027:
		case edt_libero028:
		case edt_libero029:
		case edt_libero030:
		case edt_libero031:
		case edt_libero032:
		case edt_libero033:
		case edt_libero034:
		case edt_libero035:
		case edt_libero036:
		case edt_libero037:
		case edt_libero038:
		case edt_libero039:
		case edt_libero040:
		case edt_libero041:
		case edt_libero042:
		case edt_libero043:
		case edt_libero044:
		case edt_libero045:
		case edt_libero046:
		case edt_libero047:
		case edt_libero048:
		case edt_libero049:
		case edt_libero050:
		case edt_libero051:
		case edt_libero052:
		case edt_libero053:
		case edt_libero054:
		case edt_libero055:
		case edt_libero056:
		case edt_libero057:
		case edt_libero058:
		case edt_libero059:
		case edt_libero060:
		case edt_libero061:
		case edt_libero062:
		case edt_libero063:
		case edt_libero064:
		case edt_libero065:
		case edt_libero066:
		case edt_libero067:
		case edt_libero068:
		case edt_libero069:
		case edt_libero070:
		case edt_libero071:
		case edt_libero072:
		case edt_libero073:
		case edt_libero074:
		case edt_libero075:
		case edt_libero076:
		case edt_libero077:
		case edt_libero078:
		case edt_libero079:
		case edt_libero080:
		case edt_libero081:
		case edt_libero082:
		case edt_libero083:
		case edt_libero084:
		case edt_libero085:
		case edt_libero086:
		case edt_libero087:
		case edt_libero088:
		case edt_libero089:
		case edt_libero090:
		case edt_libero091:
		case edt_libero092:
		case edt_libero093:
		case edt_libero094:
		case edt_libero095:
		case edt_libero096:
		case edt_libero097:
		case edt_libero098:
		case edt_libero099:
		case edt_fumo:
		case edt_caffe:
		case edt_sigarette:
		case edt_farmaci:
		case edt_alcool:
		case edt_assunzione:
		case edt_superalcolici:
		case edt_premedposologia:
		case edt_pazienticronici_score_hb:
		case edt_pazienticronici_score_s:
		case edt_numerototalepolipi:
		case edt_esamestrumentale_orainizio:
		case edt_esamestrumentale_orafine:	
		case edt_refertointegrato_firma: //Julio - BUG 3285 - Adequação de laudos (extra)
		{
			SendDlgItemMessage(IDC_EDIT, EM_SETREADONLY, wParam, lParam);
			break;
		}
		case edt_codicericovero:
		case edt_barcodericovero:
		{
			//if ((theApp.m_dwPrivileges & AMLogin_Permissions::configurations))
			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				SendDlgItemMessage(IDC_EDIT, EM_SETREADONLY, wParam, lParam);
			else
				SendDlgItemMessage(IDC_EDIT, EM_SETREADONLY, (WPARAM)TRUE, lParam);
			break;
		}
		case edt_sedeesame:
		case edt_salaesame:
		case edt_codesame:
			//Luiz - 13/05/2019 - P3 - Atualiza nome/sobrenome Médico - Inclui Médicos solicitantes
		case edt_medico2:
		case edt_medico3:
		case edt_medico4:
		{
			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				SendDlgItemMessage(IDC_EDIT, EM_SETREADONLY, wParam, lParam);
			else
				SendDlgItemMessage(IDC_EDIT, EM_SETREADONLY, (WPARAM)TRUE, lParam);
			break;
		}
		case edt_progressivoanno:
		case edt_codiceprenotazione:
		case edt_tempoconvalida:
		case edt_tempochiusura:
		case edt_assiden:
		case edt_codalfa:
		case edt_esamestrumentale_durataoreminuti:
		case edt_esamestrumentale_duratasolominuti:
		case edt_paziente_medicocurante:
		case edt_utente_inserimentoesame:	
		case edt_paziente_passaporto: //Julio - BUG 3285 - Adequação de laudos (extra)
		case edt_paziente_doc1:		  //Julio - BUG 3285 - Adequação de laudos (extra)
		case edt_paziente_doc2:		  //Julio - BUG 3285 - Adequação de laudos (extra)
		{
			SendDlgItemMessage(IDC_EDIT, EM_SETREADONLY, (WPARAM)TRUE, lParam);
			break;
		}
		case edt_temporetrazione:
		{
			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				SendDlgItemMessage(IDC_EDIT, EM_SETREADONLY, (WPARAM)TRUE, lParam);
			else
				SendDlgItemMessage(IDC_EDIT, EM_SETREADONLY, wParam, lParam);
			break;
		}
		case edt_medico_ricerca:
		{
			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
			{
				GetDlgItem(IDC_TEXT)->ShowWindow(SW_SHOW);
				m_ctrlEditMedicoRicerca.ShowWindow(SW_SHOW);
				m_ctrlEditMedicoRicerca.SetReadOnly(FALSE);
			}
			else
			{
				GetDlgItem(IDC_TEXT)->ShowWindow(SW_HIDE);
				m_ctrlEditMedicoRicerca.ShowWindow(SW_HIDE);
			}
			break;
		}
		case edt_integrazioneCodiceUrgenza:
		{
			SendDlgItemMessage(IDC_EDIT, EM_SETREADONLY, (WPARAM)TRUE, lParam);
			break;
		}
	}

	return 1;
}

LRESULT CEditDynForm1::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	switch(m_lContenuto)
	{
		case edt_dataesame:
		{
			m_ctrlDataEsame.m_strRicerca = "";
			m_ctrlDataEsame.m_strRicercaView = "";
			break;
		}
		case edt_prossimo:
		{
			m_ctrlDataProssimo.m_strRicerca = "";
			m_ctrlDataProssimo.m_strRicercaView = "";
			break;
		}
		case edt_esamestrumentale_orainizio:
		{
			m_ctrlEsameStrumentaleInizio.m_strRicerca = "";
			m_ctrlEsameStrumentaleInizio.m_strRicercaView = "";
			break;
		}
		case edt_esamestrumentale_orafine:
		{
			m_ctrlEsameStrumentaleFine.m_strRicerca = "";
			m_ctrlEsameStrumentaleFine.m_strRicercaView = "";
			break;
		}
		case edt_medico_ricerca:
		{
			m_ctrlEditMedicoRicerca.SetWindowText("");
			break;
		}
	}

	return 1;
}

LRESULT CEditDynForm1::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	switch(m_lContenuto)
	{
		case edt_progressivoanno:
		{
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sProgressivoAnno, "EEsami.ProgressivoAnno", 0);
			break;
		}
		case edt_codiceprenotazione:
		{
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sCodicePrenotazione, "EEsami.CodicePrenotazione", 0);
			break;
		}
		case edt_dataesame:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlDataEsame.m_strRicerca, "EEsami.Data", FALSE, TRUE);
			break;
		}
		case edt_camera:
		{
			ComponiRicercaLong(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lCamera, "EEsami.Camera", 0, "AND");
			break;
		}
		case edt_farmacotrial:
		{
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sFarmacoTrial, "EEsami.FarmacoTrial", 1);
			break;
		}
		case edt_premedicazioni:
		{
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sPremedicazioni, "EEsami.Premedicazioni", 1);
			break;
		}
		case edt_condottofino:
		{
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sEstensione, "EEsami.Estensione", 0);
			break;
		}
		case edt_valutazione:
		{
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sValutazione, "EEsami.Valutazione", 1);
			break;
		}
		case edt_tipovisita:
		{
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sTipoVisita, "EEsami.TipoVisita", 1);
			break;
		}
		case edt_quadro:
		{
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sQuadro, "EEsami.Quadro", 1);
			break;
		}
		case edt_durata:
		{
			ComponiRicercaLong(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lDurata, "EEsami.Durata", 0, "AND");
			break;
		}
		case edt_prossimo:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlDataProssimo.m_strRicerca, "EEsami.DataControllo", FALSE, TRUE);
			break;
		}
		case edt_studio:
		{
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sStudio, "EEsami.Studio", 0);
			break;
		}
		case edt_guarigione:
		{
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sGuarigione, "EEsami.Guarigione", 1);
			break;
		}
		case edt_difficolta:
		{
			ComponiRicercaLong(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lDifficolta, "EEsami.Difficolta",  0, "AND");
			break;
		}
		case edt_anestesista:
		{
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sAnestesista, "EEsami.Anestesista", 1);
			break;
		}
		case edt_sedeesame:
		{
			ComponiRicercaLong(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDSedeEsame, "EEsami.IDSedeEsame",  0, "AND");
			break;
		}
		case edt_salaesame:
		{
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sSalaEsame, "EEsami.SalaEsame", 1);
			break;
		}
		case edt_libero000:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto000, "EEsamiPersonalizzabili.Testo000", 1);
			break;
		}
		case edt_libero001:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto001, "EEsamiPersonalizzabili.Testo001", 1);
			break;
		}
		case edt_libero002:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto002, "EEsamiPersonalizzabili.Testo002", 1);
			break;
		}
		case edt_libero003:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto003, "EEsamiPersonalizzabili.Testo003", 1);
			break;
		}
		case edt_libero004:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto004, "EEsamiPersonalizzabili.Testo004", 1);
			break;
		}
		case edt_libero005:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto005, "EEsamiPersonalizzabili.Testo005", 1);
			break;
		}
		case edt_libero006:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto006, "EEsamiPersonalizzabili.Testo006", 1);
			break;
		}
		case edt_libero007:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto007, "EEsamiPersonalizzabili.Testo007", 1);
			break;
		}
		case edt_libero008:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto008, "EEsamiPersonalizzabili.Testo008", 1);
			break;
		}
		case edt_libero009:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto009, "EEsamiPersonalizzabili.Testo009", 1);
			break;
		}
		case edt_libero010:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto010, "EEsamiPersonalizzabili.Testo010", 1);
			break;
		}
		case edt_libero011:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto011, "EEsamiPersonalizzabili.Testo011", 1);
			break;
		}
		case edt_libero012:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto012, "EEsamiPersonalizzabili.Testo012", 1);
			break;
		}
		case edt_libero013:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto013, "EEsamiPersonalizzabili.Testo013", 1);
			break;
		}
		case edt_libero014:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto014, "EEsamiPersonalizzabili.Testo014", 1);
			break;
		}
		case edt_libero015:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto015, "EEsamiPersonalizzabili.Testo015", 1);
			break;
		}
		case edt_libero016:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto016, "EEsamiPersonalizzabili.Testo016", 1);
			break;
		}
		case edt_libero017:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto017, "EEsamiPersonalizzabili.Testo017", 1);
			break;
		}
		case edt_libero018:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto018, "EEsamiPersonalizzabili.Testo018", 1);
			break;
		}
		case edt_libero019:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto019, "EEsamiPersonalizzabili.Testo019", 1);
			break;
		}
		case edt_libero020:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto020, "EEsamiPersonalizzabili.Testo020", 1);
			break;
		}
		case edt_libero021:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto021, "EEsamiPersonalizzabili.Testo021", 1);
			break;
		}
		case edt_libero022:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto022, "EEsamiPersonalizzabili.Testo022", 1);
			break;
		}
		case edt_libero023:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto023, "EEsamiPersonalizzabili.Testo023", 1);
			break;
		}
		case edt_libero024:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto024, "EEsamiPersonalizzabili.Testo024", 1);
			break;
		}
		case edt_libero025:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto025, "EEsamiPersonalizzabili.Testo025", 1);
			break;
		}
		case edt_libero026:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto026, "EEsamiPersonalizzabili.Testo026", 1);
			break;
		}
		case edt_libero027:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto027, "EEsamiPersonalizzabili.Testo027", 1);
			break;
		}
		case edt_libero028:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto028, "EEsamiPersonalizzabili.Testo028", 1);
			break;
		}
		case edt_libero029:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto029, "EEsamiPersonalizzabili.Testo029", 1);
			break;
		}
		case edt_libero030:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto030, "EEsamiPersonalizzabili.Testo030", 1);
			break;
		}
		case edt_libero031:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto031, "EEsamiPersonalizzabili.Testo031", 1);
			break;
		}
		case edt_libero032:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto032, "EEsamiPersonalizzabili.Testo032", 1);
			break;
		}
		case edt_libero033:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto033, "EEsamiPersonalizzabili.Testo033", 1);
			break;
		}
		case edt_libero034:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto034, "EEsamiPersonalizzabili.Testo034", 1);
			break;
		}
		case edt_libero035:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto035, "EEsamiPersonalizzabili.Testo035", 1);
			break;
		}
		case edt_libero036:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto036, "EEsamiPersonalizzabili.Testo036", 1);
			break;
		}
		case edt_libero037:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto037, "EEsamiPersonalizzabili.Testo037", 1);
			break;
		}
		case edt_libero038:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto038, "EEsamiPersonalizzabili.Testo038", 1);
			break;
		}
		case edt_libero039:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto039, "EEsamiPersonalizzabili.Testo039", 1);
			break;
		}
		case edt_libero040:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto040, "EEsamiPersonalizzabili.Testo040", 1);
			break;
		}
		case edt_libero041:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto041, "EEsamiPersonalizzabili.Testo041", 1);
			break;
		}
		case edt_libero042:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto042, "EEsamiPersonalizzabili.Testo042", 1);
			break;
		}
		case edt_libero043:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto043, "EEsamiPersonalizzabili.Testo043", 1);
			break;
		}
		case edt_libero044:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto044, "EEsamiPersonalizzabili.Testo044", 1);
			break;
		}
		case edt_libero045:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto045, "EEsamiPersonalizzabili.Testo045", 1);
			break;
		}
		case edt_libero046:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto046, "EEsamiPersonalizzabili.Testo046", 1);
			break;
		}
		case edt_libero047:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto047, "EEsamiPersonalizzabili.Testo047", 1);
			break;
		}
		case edt_libero048:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto048, "EEsamiPersonalizzabili.Testo048", 1);
			break;
		}
		case edt_libero049:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto049, "EEsamiPersonalizzabili.Testo049", 1);
			break;
		}
		case edt_libero050:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto050, "EEsamiPersonalizzabili.Testo050", 1);
			break;
		}
		case edt_libero051:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto051, "EEsamiPersonalizzabili.Testo051", 1);
			break;
		}
		case edt_libero052:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto052, "EEsamiPersonalizzabili.Testo052", 1);
			break;
		}
		case edt_libero053:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto053, "EEsamiPersonalizzabili.Testo053", 1);
			break;
		}
		case edt_libero054:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto054, "EEsamiPersonalizzabili.Testo054", 1);
			break;
		}
		case edt_libero055:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto055, "EEsamiPersonalizzabili.Testo055", 1);
			break;
		}
		case edt_libero056:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto056, "EEsamiPersonalizzabili.Testo056", 1);
			break;
		}
		case edt_libero057:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto057, "EEsamiPersonalizzabili.Testo057", 1);
			break;
		}
		case edt_libero058:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto058, "EEsamiPersonalizzabili.Testo058", 1);
			break;
		}
		case edt_libero059:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto059, "EEsamiPersonalizzabili.Testo059", 1);
			break;
		}
		case edt_libero060:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto060, "EEsamiPersonalizzabili.Testo060", 1);
			break;
		}
		case edt_libero061:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto061, "EEsamiPersonalizzabili.Testo061", 1);
			break;
		}
		case edt_libero062:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto062, "EEsamiPersonalizzabili.Testo062", 1);
			break;
		}
		case edt_libero063:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto063, "EEsamiPersonalizzabili.Testo063", 1);
			break;
		}
		case edt_libero064:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto064, "EEsamiPersonalizzabili.Testo064", 1);
			break;
		}
		case edt_libero065:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto065, "EEsamiPersonalizzabili.Testo065", 1);
			break;
		}
		case edt_libero066:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto066, "EEsamiPersonalizzabili.Testo066", 1);
			break;
		}
		case edt_libero067:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto067, "EEsamiPersonalizzabili.Testo067", 1);
			break;
		}
		case edt_libero068:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto068, "EEsamiPersonalizzabili.Testo068", 1);
			break;
		}
		case edt_libero069:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto069, "EEsamiPersonalizzabili.Testo069", 1);
			break;
		}
		case edt_libero070:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto070, "EEsamiPersonalizzabili.Testo070", 1);
			break;
		}
		case edt_libero071:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto071, "EEsamiPersonalizzabili.Testo071", 1);
			break;
		}
		case edt_libero072:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto072, "EEsamiPersonalizzabili.Testo072", 1);
			break;
		}
		case edt_libero073:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto073, "EEsamiPersonalizzabili.Testo073", 1);
			break;
		}
		case edt_libero074:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto074, "EEsamiPersonalizzabili.Testo074", 1);
			break;
		}
		case edt_libero075:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto075, "EEsamiPersonalizzabili.Testo075", 1);
			break;
		}
		case edt_libero076:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto076, "EEsamiPersonalizzabili.Testo076", 1);
			break;
		}
		case edt_libero077:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto077, "EEsamiPersonalizzabili.Testo077", 1);
			break;
		}
		case edt_libero078:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto078, "EEsamiPersonalizzabili.Testo078", 1);
			break;
		}
		case edt_libero079:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto079, "EEsamiPersonalizzabili.Testo079", 1);
			break;
		}
		case edt_libero080:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto080, "EEsamiPersonalizzabili.Testo080", 1);
			break;
		}
		case edt_libero081:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto081, "EEsamiPersonalizzabili.Testo081", 1);
			break;
		}
		case edt_libero082:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto082, "EEsamiPersonalizzabili.Testo082", 1);
			break;
		}
		case edt_libero083:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto083, "EEsamiPersonalizzabili.Testo083", 1);
			break;
		}
		case edt_libero084:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto084, "EEsamiPersonalizzabili.Testo084", 1);
			break;
		}
		case edt_libero085:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto085, "EEsamiPersonalizzabili.Testo085", 1);
			break;
		}
		case edt_libero086:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto086, "EEsamiPersonalizzabili.Testo086", 1);
			break;
		}
		case edt_libero087:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto087, "EEsamiPersonalizzabili.Testo087", 1);
			break;
		}
		case edt_libero088:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto088, "EEsamiPersonalizzabili.Testo088", 1);
			break;
		}
		case edt_libero089:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto089, "EEsamiPersonalizzabili.Testo089", 1);
			break;
		}
		case edt_libero090:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto090, "EEsamiPersonalizzabili.Testo090", 1);
			break;
		}
		case edt_libero091:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto091, "EEsamiPersonalizzabili.Testo091", 1);
			break;
		}
		case edt_libero092:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto092, "EEsamiPersonalizzabili.Testo092", 1);
			break;
		}
		case edt_libero093:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto093, "EEsamiPersonalizzabili.Testo093", 1);
			break;
		}
		case edt_libero094:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto094, "EEsamiPersonalizzabili.Testo094", 1);
			break;
		}
		case edt_libero095:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto095, "EEsamiPersonalizzabili.Testo095", 1);
			break;
		}
		case edt_libero096:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto096, "EEsamiPersonalizzabili.Testo096", 1);
			break;
		}
		case edt_libero097:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto097, "EEsamiPersonalizzabili.Testo097", 1);
			break;
		}
		case edt_libero098:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto098, "EEsamiPersonalizzabili.Testo098", 1);
			break;
		}
		case edt_libero099:
		{
			ComponiRicercaString(pStrWhere, &m_pEsamiView->m_pEsamiSet->m_setEP, &m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto099, "EEsamiPersonalizzabili.Testo099", 1);
			break;
		}
		case edt_fumo:
		{
			ComponiRicercaLong(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lFumo, "EEsami.Fumo", 0, "AND");
			break;
		}
		case edt_caffe:
		{
			ComponiRicercaLong(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lCaffe, "EEsami.Caffe", 0, "AND");
			break;
		}
		case edt_sigarette:
		{
			ComponiRicercaLong(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lSigarette, "EEsami.Sigarette", 0, "AND");
			break;
		}
		case edt_farmaci:
		{
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sDenFarmaci, "EEsami.Den_farmaci", 1);
			break;
		}
		case edt_alcool:
		{
			ComponiRicercaLong(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lAlcool, "EEsami.Alcool", 0, "AND");
			break;
		}
		case edt_assunzione:
		{
			ComponiRicercaLong(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lAssunzione, "EEsami.Assunzione", 0, "AND");
			break;
		}
		case edt_superalcolici:
		{
			ComponiRicercaLong(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lSuperAlcolici, "EEsami.Superalcolici", 0, "AND");
			break;
		}
		case edt_premedposologia:
		{
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sPremedPosologia, "EEsami.PremedPosologia", 1);
			break;
		}
		case edt_codesame:
		{
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sCodEsame, "EEsami.CodEsame", 0);
			break;
		}
		//Luiz - 13/05/2019 - P3 - Atualiza nome/sobrenome Médico - Inclui Médicos solicitantes
		case edt_medico2:
		{
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sInvMedico2, "EEsami.InvMedico2", 0);
			break;
		}
		case edt_medico3:
		{
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sInvMedico3, "EEsami.InvMedico3", 0);
			break;
		}
		case edt_medico4:
		{
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sInvMedico4, "EEsami.InvMedico4", 0);
			break;
		} 
		case edt_paziente_passaporto: //Julio - BUG 3285 - Adequação de laudos (extra)
		{
			//ComponiRicercaString(pStrWhere, m_pEsamiView->m_pPazientiSet, &m_pEsamiView->m_pPazientiSet->m_sIdentificazionePassaporto, "EPaziente.IDENTIFICAZIONEPASSAPORTO", 0);
			break;
		}
		case edt_paziente_doc1: //Julio - BUG 3285 - Adequação de laudos (extra)
		{
			//ComponiRicercaString(pStrWhere, m_pEsamiView->m_pPazientiSet, &m_pEsamiView->m_pPazientiSet->m_sIdentificazioneDoc1, "EPaziente.IDENTIFICAZIONEDOC1", 0);
			break;
		}
		case edt_paziente_doc2: //Julio - BUG 3285 - Adequação de laudos (extra)
		{
			//ComponiRicercaString(pStrWhere, m_pEsamiView->m_pPazientiSet, &m_pEsamiView->m_pPazientiSet->m_sIdentificazioneDoc2, "EPaziente.IDENTIFICAZIONEDOC2", 0);
			break;
		}
		case edt_codicericovero:
		{
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sRicovero, "EEsami.Ricovero", 0);
			break;
		}
		case edt_barcodericovero:
		{
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sIdEpisodioRicovero, "EEsami.IdEpisodioRicovero", 0);
			break;
		}
		case edt_esamestrumentale_orainizio:
		{
			break;
		}
		case edt_esamestrumentale_orafine:
		{
			break;
		}
		case edt_esamestrumentale_durataoreminuti:
		{
			break;
		}
		case edt_esamestrumentale_duratasolominuti:
		{
			break;
		}
		case edt_pazienticronici_score_hb:
		{
			break;
		}
		case edt_pazienticronici_score_s:
		{
			break;
		}
		case edt_paziente_medicocurante:
		{
			break;
		}
		case edt_utente_inserimentoesame:
		{
			break;
		}
		case edt_numerototalepolipi:
		{
			ComponiRicercaLong(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lNumeroTotalePolipi, "EEsami.NumeroTotalePolipi", 0, "AND");
			break;
		}
		case edt_temporetrazione:
		{
			break;
		}
		case edt_medico_ricerca:
		{
			// Sandro // 20/02/2015 // campo personalizzato che compare solo a Treviglio //

			CString sRicerca;
			m_ctrlEditMedicoRicerca.GetWindowText(sRicerca);
			sRicerca.Replace("'", "''");
			sRicerca.Trim();

			if (!sRicerca.IsEmpty())
			{
				CString strTotWhere = "";

				CString sFilter = "Cognome LIKE '%" + sRicerca + "%' OR Nome LIKE '%" + sRicerca + "%'";

				CMediciSet setMedici;
				setMedici.SetBaseFilter("(ELIMINATO=0 OR ELIMINATO=1)");
				setMedici.SetOpenFilter(sFilter);

				if (setMedici.OpenRecordset("CEditDynForm1::OnFormSearchNew"))
				{
					while (!setMedici.IsEOF())
					{
						CString strTempWhere;
						strTempWhere.Format("EEsami.Medico=%li OR EEsami.Assistente=%li", setMedici.m_lContatore, setMedici.m_lContatore);

						// concateno le singole stringhe all'interno di una più grande divisa da OR //
						strTempWhere.Trim();
						if (!strTempWhere.IsEmpty())
						{
							if (!strTotWhere.IsEmpty())
								strTotWhere += " " + strOperators[OPER_OR] + " ";

							strTotWhere += "(" + strTempWhere + ")";
						}

						//
						setMedici.MoveNext();
					}

					setMedici.CloseRecordset("CEditDynForm1::OnFormSearchNew");
				}

				// aggiungo il campo "testuale" //

				CString strTempWhere = "EEsamiPersonalizzabili.Testo002 LIKE '%" + sRicerca + "%'";

				if (!strTotWhere.IsEmpty())
					strTotWhere += " " + strOperators[OPER_OR] + " ";

				strTotWhere += "(" + strTempWhere + ")";


				// unisco la stringona grande composita al WHERE generale mettendoci eventualmente un AND davanti //
				strTotWhere.Trim();
				if (!strTotWhere.IsEmpty())
				{
					if (!pStrWhere->IsEmpty())
						(*pStrWhere) += " " + strOperators[OPER_AND] + " ";

					(*pStrWhere) += "(" + strTotWhere + ")";
				}

#ifdef _DEBUG
				theApp.AfxMessageBoxEndo("edt_medico_ricerca\n\n" + strTotWhere);
#endif
			}

			break;
		}
	}

	return 1;
}

LRESULT CEditDynForm1::OnFormFocusLost(WPARAM wParam, LPARAM lParam)
{
	// HWND OldHwnd = (HWND) wParam;
	if (!ControlloNumerico())
	{
		if (!m_bReadOnly)
		{
			if ((m_lContenuto >= edt_libero000) && (m_lContenuto <= edt_libero099))
			{
				CString sTempMessage = theApp.m_sLabelText[m_lContenuto - edt_libero000];
				sTempMessage.MakeUpper();

				CString sTempVal;
				GetDlgItem(IDC_EDIT)->GetWindowText(sTempVal);

				theApp.AfxMessageBoxEndo(sTempMessage + ": " + sTempVal + "\n" + theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR_NOCANC));
			}
			else
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALPHANUMERIC_ERROR_NOCANC));
			}
			// ::SetFocus(OldHwnd);
		}

		return -1;
	}

	return 0;
}

long CEditDynForm1::GetContenuto()
{
	return m_lContenuto;
}

BOOL CEditDynForm1::CampoObbligatorioValido()
{
	CString strEdit;
	GetDlgItemText(IDC_EDIT, strEdit);

	if (m_lContenuto == edt_temporetrazione)
	{
		int iTemp = strEdit.Find(':');
		if (iTemp > 0)
		{
			CString sTemp1 = strEdit.Left(iTemp);
			CString sTemp2 = strEdit.Right(strEdit.GetLength() - (iTemp + 1));

			return (((atol(sTemp1) * 60) + atol(sTemp2)) > 0);
		}
	}
	else
	{
		if (!strEdit.IsEmpty())
			return TRUE;
	}

	return FALSE;
}

BOOL CEditDynForm1::ControlloNumerico()
{
	if ((m_lContenuto >= edt_libero000) && (m_lContenuto <= edt_libero099))
	{
		CString temp;
		GetDlgItem(IDC_EDIT)->GetWindowText(temp);

		if (theApp.m_bComboNumerico[m_lContenuto - edt_libero000])
		{
			for(int i = 0; i < temp.GetLength(); i++)
			{
				CString tempChar = temp.Mid(i, 1);
				if (tempChar.Compare(".") != 0 && tempChar.Compare(",") != 0 && tempChar.Compare("0") != 0)
				{
					float fTemp = (float)atof(tempChar);
					if (fTemp == 0)
						return FALSE;
				}
			}

			temp.Replace(',','.');
			if (temp.Right(1).Compare(".") == 0)
				temp = temp.Left(temp.GetLength() - 1);
			GetDlgItem(IDC_EDIT)->SetWindowText(temp);
		}
	}

	return TRUE;
}

LRESULT CEditDynForm1::OnExtEditCmbChanged(WPARAM wParam, LPARAM lParam)
{
	BeginWaitCursor();

	int freeFieldIndex = ((int)wParam) - CMB_ESA_LIBERO000;
	int idEtichetta = CEtichetteSet().GetId("TESTO", freeFieldIndex);

	CString sFilter;
	sFilter.Format("IDCAMPORELAZIONATO=%li", idEtichetta);
	CEtichetteSet etSet;
	etSet.SetOpenFilter(sFilter);
	if (etSet.OpenRecordset("CEditDynForm1::OnExtEditCmbChanged"))
	{
		while (!etSet.IsEOF())
		{
			CString sFilter2;
			sFilter2.Format("IDCAMPOCONDIZIONATO=%li AND IDSCELTA=%li", etSet.m_lContatore, (long)lParam);
			CEtichetteCondizionateConfigSet etConfSet;
			etConfSet.SetOpenFilter(sFilter2);
			if (etConfSet.OpenRecordset("CEditDynForm1::OnExtEditCmbChanged"))
			{
				if (!etConfSet.IsEOF())
				{
					ManageEditCmbChanged(etSet.m_sTipo, etSet.m_lIndice, etConfSet.m_lIDRisultato, etConfSet.m_sRisultatoTxt);					
				}

				etConfSet.CloseRecordset("CEditDynForm1::OnExtEditCmbChanged");
			}

			etSet.MoveNext();
		}

		etSet.CloseRecordset("CEditDynForm1::OnExtEditCmbChanged");
	}

	EndWaitCursor();

	return 0;
}

void CEditDynForm1::ManageEditCmbChanged(CString sTipoCampoCondizionato, long lIndexCampoCondizionato, long lIDRisultato, CString sRisultatoTxt)
{
	if (sTipoCampoCondizionato == "TESTO")
	{
		int contentId = -1;
		long setIndex = lIndexCampoCondizionato + CMB_ESA_LIBERO000;

		//Siamo nei testi
		switch (setIndex)
		{
		case CMB_ESA_LIBERO000:
			contentId = edt_libero000;			
			break;	
		case CMB_ESA_LIBERO001:
			contentId = edt_libero001;
			break;
		case CMB_ESA_LIBERO002:
			contentId = edt_libero002;
			break;
		case CMB_ESA_LIBERO003:
			contentId = edt_libero003;
			break;
		case CMB_ESA_LIBERO004:
			contentId = edt_libero004;
			break;
		case CMB_ESA_LIBERO005:
			contentId = edt_libero005;
			break;
		case CMB_ESA_LIBERO006:
			contentId = edt_libero006;
			break;
		case CMB_ESA_LIBERO007:
			contentId = edt_libero007;
			break;
		case CMB_ESA_LIBERO008:
			contentId = edt_libero008;
			break;
		case CMB_ESA_LIBERO009:
			contentId = edt_libero009;
			break;
		case CMB_ESA_LIBERO010:
			contentId = edt_libero010;
			break;
		case CMB_ESA_LIBERO011:
			contentId = edt_libero011;
			break;
		case CMB_ESA_LIBERO012:
			contentId = edt_libero012;
			break;
		case CMB_ESA_LIBERO013:
			contentId = edt_libero013;
			break;
		case CMB_ESA_LIBERO014:
			contentId = edt_libero014;
			break;
		case CMB_ESA_LIBERO015:
			contentId = edt_libero015;
			break;
		case CMB_ESA_LIBERO016:
			contentId = edt_libero016;
			break;
		case CMB_ESA_LIBERO017:
			contentId = edt_libero017;
			break;
		case CMB_ESA_LIBERO018:
			contentId = edt_libero018;
			break;
		case CMB_ESA_LIBERO019:
			contentId = edt_libero019;
			break;
		case CMB_ESA_LIBERO020:
			contentId = edt_libero020;
			break;
		case CMB_ESA_LIBERO021:
			contentId = edt_libero021;
			break;
		case CMB_ESA_LIBERO022:
			contentId = edt_libero022;
			break;
		case CMB_ESA_LIBERO023:
			contentId = edt_libero023;
			break;
		case CMB_ESA_LIBERO024:
			contentId = edt_libero024;
			break;
		case CMB_ESA_LIBERO025:
			contentId = edt_libero025;
			break;
		case CMB_ESA_LIBERO026:
			contentId = edt_libero026;
			break;
		case CMB_ESA_LIBERO027:
			contentId = edt_libero027;
			break;
		case CMB_ESA_LIBERO028:
			contentId = edt_libero028;
			break;
		case CMB_ESA_LIBERO029:
			contentId = edt_libero029;
			break;
		case CMB_ESA_LIBERO030:
			contentId = edt_libero030;
			break;
		case CMB_ESA_LIBERO031:
			contentId = edt_libero031;
			break;
		case CMB_ESA_LIBERO032:
			contentId = edt_libero032;
			break;
		case CMB_ESA_LIBERO033:
			contentId = edt_libero033;
			break;
		case CMB_ESA_LIBERO034:
			contentId = edt_libero034;
			break;
		case CMB_ESA_LIBERO035:
			contentId = edt_libero035;
			break;
		case CMB_ESA_LIBERO036:
			contentId = edt_libero036;
			break;
		case CMB_ESA_LIBERO037:
			contentId = edt_libero037;
			break;
		case CMB_ESA_LIBERO038:
			contentId = edt_libero038;
			break;
		case CMB_ESA_LIBERO039:
			contentId = edt_libero039;
			break;
		case CMB_ESA_LIBERO040:
			contentId = edt_libero040;
			break;
		case CMB_ESA_LIBERO041:
			contentId = edt_libero041;
			break;
		case CMB_ESA_LIBERO042:
			contentId = edt_libero042;
			break;
		case CMB_ESA_LIBERO043:
			contentId = edt_libero043;
			break;
		case CMB_ESA_LIBERO044:
			contentId = edt_libero044;
			break;
		case CMB_ESA_LIBERO045:
			contentId = edt_libero045;
			break;
		case CMB_ESA_LIBERO046:
			contentId = edt_libero046;
			break;
		case CMB_ESA_LIBERO047:
			contentId = edt_libero047;
			break;
		case CMB_ESA_LIBERO048:
			contentId = edt_libero048;
			break;
		case CMB_ESA_LIBERO049:
			contentId = edt_libero049;
			break;
		case CMB_ESA_LIBERO050:
			contentId = edt_libero050;
			break;
		case CMB_ESA_LIBERO051:
			contentId = edt_libero051;
			break;
		case CMB_ESA_LIBERO052:
			contentId = edt_libero052;
			break;
		case CMB_ESA_LIBERO053:
			contentId = edt_libero053;
			break;
		case CMB_ESA_LIBERO054:
			contentId = edt_libero054;
			break;
		case CMB_ESA_LIBERO055:
			contentId = edt_libero055;
			break;
		case CMB_ESA_LIBERO056:
			contentId = edt_libero056;
			break;
		case CMB_ESA_LIBERO057:
			contentId = edt_libero057;
			break;
		case CMB_ESA_LIBERO058:
			contentId = edt_libero058;
			break;
		case CMB_ESA_LIBERO059:
			contentId = edt_libero059;
			break;
		case CMB_ESA_LIBERO060:
			contentId = edt_libero060;
			break;
		case CMB_ESA_LIBERO061:
			contentId = edt_libero061;
			break;
		case CMB_ESA_LIBERO062:
			contentId = edt_libero062;
			break;
		case CMB_ESA_LIBERO063:
			contentId = edt_libero063;
			break;
		case CMB_ESA_LIBERO064:
			contentId = edt_libero064;
			break;
		case CMB_ESA_LIBERO065:
			contentId = edt_libero065;
			break;
		case CMB_ESA_LIBERO066:
			contentId = edt_libero066;
			break;
		case CMB_ESA_LIBERO067:
			contentId = edt_libero067;
			break;
		case CMB_ESA_LIBERO068:
			contentId = edt_libero068;
			break;
		case CMB_ESA_LIBERO069:
			contentId = edt_libero069;
			break;
		case CMB_ESA_LIBERO070:
			contentId = edt_libero070;
			break;
		case CMB_ESA_LIBERO071:
			contentId = edt_libero071;
			break;
		case CMB_ESA_LIBERO072:
			contentId = edt_libero072;
			break;
		case CMB_ESA_LIBERO073:
			contentId = edt_libero073;
			break;
		case CMB_ESA_LIBERO074:
			contentId = edt_libero074;
			break;
		case CMB_ESA_LIBERO075:
			contentId = edt_libero075;
			break;
		case CMB_ESA_LIBERO076:
			contentId = edt_libero076;
			break;
		case CMB_ESA_LIBERO077:
			contentId = edt_libero077;
			break;
		case CMB_ESA_LIBERO078:
			contentId = edt_libero078;
			break;
		case CMB_ESA_LIBERO079:
			contentId = edt_libero079;
			break;
		case CMB_ESA_LIBERO080:
			contentId = edt_libero080;
			break;
		case CMB_ESA_LIBERO081:
			contentId = edt_libero081;
			break;
		case CMB_ESA_LIBERO082:
			contentId = edt_libero082;
			break;
		case CMB_ESA_LIBERO083:
			contentId = edt_libero083;
			break;
		case CMB_ESA_LIBERO084:
			contentId = edt_libero084;
			break;
		case CMB_ESA_LIBERO085:
			contentId = edt_libero085;
			break;
		case CMB_ESA_LIBERO086:
			contentId = edt_libero086;
			break;
		case CMB_ESA_LIBERO087:
			contentId = edt_libero087;
			break;
		case CMB_ESA_LIBERO088:
			contentId = edt_libero088;
			break;
		case CMB_ESA_LIBERO089:
			contentId = edt_libero089;
			break;
		case CMB_ESA_LIBERO090:
			contentId = edt_libero090;
			break;
		case CMB_ESA_LIBERO091:
			contentId = edt_libero091;
			break;
		case CMB_ESA_LIBERO092:
			contentId = edt_libero092;
			break;
		case CMB_ESA_LIBERO093:
			contentId = edt_libero093;
			break;
		case CMB_ESA_LIBERO094:
			contentId = edt_libero094;
			break;
		case CMB_ESA_LIBERO095:
			contentId = edt_libero095;
			break;
		case CMB_ESA_LIBERO096:
			contentId = edt_libero096;
			break;
		case CMB_ESA_LIBERO097:
			contentId = edt_libero097;
			break;
		case CMB_ESA_LIBERO098:
			contentId = edt_libero098;
			break;
		case CMB_ESA_LIBERO099:
			contentId = edt_libero099;
			break;
		}

		if (m_pEsamiView->m_pDynForm[contentId] != NULL)
		{
			CString sValue = sRisultatoTxt;

			if (lIDRisultato > 0)
			{
				sValue = CComboBoxSet(setIndex).GetFieldText(lIDRisultato);
			}

			//Invoco il metodo per modificare il contenuto
			if (theApp.m_bComboSingleLine[lIndexCampoCondizionato])
			{
				CEditDynForm1* temp = (CEditDynForm1*)m_pEsamiView->m_pDynForm[contentId];
				temp->SetText(sValue);
			}
			else
			{
				CEditDynForm2* temp = (CEditDynForm2*)m_pEsamiView->m_pDynForm[contentId];
				temp->SetText(sValue);
			}
		}
	}
	else
	{
		//Siamo in RTF
		//	In questo caso vale solo sRisultato
		CString sValue = sRisultatoTxt;

		if (m_pEsamiView->m_pDynForm[lIndexCampoCondizionato + edt_liberortf000] != NULL)
		{
			CEditDynFormFullRtf* temp = (CEditDynFormFullRtf*)m_pEsamiView->m_pDynForm[lIndexCampoCondizionato + edt_liberortf000];
			temp->SetText(sValue);
		}
	}
}

void CEditDynForm1::SetText(CString value)
{
	GetDlgItem(IDC_EDIT)->SetWindowText(value);
}