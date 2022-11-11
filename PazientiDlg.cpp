#include "stdafx.h"
#include "Endox.h"
#include "PazientiDlg.h"

#include <cctype>

#include "CampiObbligatoriPazienteSet.h"
#include "Common.h"
#include "ComuniSet.h"
#include "CustomDate.h"
#include "EndoxDynForm.h"
#include "EsamiView.h"
#include "MalattieCronicheSet.h"
#include "PazientiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CPazientiDlg, CDialog)

CPazientiDlg::CPazientiDlg(CWnd* pParent, CEsamiView* pEsamiView, CPazientiSet* pPazientiSet, int iModalita)
	: CDialog(CPazientiDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);
	ASSERT(pPazientiSet != NULL);

	m_pEsamiView = pEsamiView;
	m_pPazientiSet = pPazientiSet;
	m_iModalita = iModalita;

	m_bSearchNow = FALSE;

	m_bValidUser = TRUE;
	m_bUserFocus = FALSE;

	switch(m_iModalita)
	{
		case PAZ_EDIT:
		case PAZ_SRCH:
		{
			m_bSendEmail = FALSE;
			m_bSendSms = FALSE;
			m_bPazienteDelDirettore = m_pPazientiSet->m_bPazienteDelDirettore;
			break;
		}
		case PAZ_SHOW:
		{
			m_bSendEmail = m_pPazientiSet->m_bSendEmail;
			m_bSendSms = m_pPazientiSet->m_bSendSms;
			m_bPazienteDelDirettore = m_pPazientiSet->m_bPazienteDelDirettore;
			break;
		}
		default:
		{
			m_bSendEmail = FALSE;
			m_bSendSms = FALSE;
			m_bPazienteDelDirettore = FALSE;
			break;
		}
	}

	m_lProvenienza = -1;
}

CPazientiDlg::~CPazientiDlg()
{
}

BEGIN_MESSAGE_MAP(CPazientiDlg, CDialog)
	ON_WM_CTLCOLOR()

	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_SEARCH, OnBnClickedSearch)
	ON_BN_CLICKED(IDC_BUTTON_10, OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON_35, OnBnClickedButton35)

	ON_EN_CHANGE(IDC_EDIT_35, OnEnChangeEdit35)
	ON_EN_KILLFOCUS(IDC_EDIT_35, OnEnKillfocusEdit35)
	ON_EN_SETFOCUS(IDC_EDIT_35, OnEnSetfocusEdit35)

	ON_BN_CLICKED(IDC_CHECK_DECEDUTO, &CPazientiDlg::OnBnClickedCheckDeceduto)
END_MESSAGE_MAP()

void CPazientiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_FRAME_00, m_ctrlStaticFrame00);
	DDX_Control(pDX, IDC_FRAME_01, m_ctrlStaticFrame01);
	DDX_Control(pDX, IDC_FRAME_02, m_ctrlStaticFrame02);
	DDX_Control(pDX, IDC_FRAME_03, m_ctrlStaticFrame03);
	DDX_Control(pDX, IDC_FRAME_05, m_ctrlStaticFrame05);
	DDX_Control(pDX, IDC_FRAME_06, m_ctrlStaticFrame06);
	DDX_Control(pDX, IDC_FRAME_07, m_ctrlStaticFrame07);
	DDX_Control(pDX, IDC_FRAME_08, m_ctrlStaticFrame08); //Julio - BUG 3285 - Adequação de laudos
	
	DDX_Control(pDX, IDC_STATIC_00,  m_ctrlStatic00);
	DDX_Control(pDX, IDC_STATIC_01,  m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02,  m_ctrlStatic02);
	DDX_Control(pDX, IDC_STATIC_03,  m_ctrlStatic03);
	DDX_Control(pDX, IDC_STATIC_04,  m_ctrlStatic04);
	DDX_Control(pDX, IDC_STATIC_05,  m_ctrlStatic05);
	DDX_Control(pDX, IDC_STATIC_06,  m_ctrlStatic06);
	DDX_Control(pDX, IDC_STATIC_07,  m_ctrlStatic07);
	DDX_Control(pDX, IDC_STATIC_08,  m_ctrlStatic08);
	DDX_Control(pDX, IDC_STATIC_10,  m_ctrlStatic10);
	DDX_Control(pDX, IDC_STATIC_11,  m_ctrlStatic11);
	DDX_Control(pDX, IDC_STATIC_12,  m_ctrlStatic12);
	DDX_Control(pDX, IDC_STATIC_13,  m_ctrlStatic13);
	DDX_Control(pDX, IDC_STATIC_14,  m_ctrlStatic14);
	DDX_Control(pDX, IDC_STATIC_15,  m_ctrlStatic15);
	DDX_Control(pDX, IDC_STATIC_16,  m_ctrlStatic16);
	DDX_Control(pDX, IDC_STATIC_17,  m_ctrlStatic17);
	DDX_Control(pDX, IDC_STATIC_18,  m_ctrlStatic18);
	DDX_Control(pDX, IDC_STATIC_19,  m_ctrlStatic19);
	DDX_Control(pDX, IDC_STATIC_20,  m_ctrlStatic20);
	DDX_Control(pDX, IDC_STATIC_21,  m_ctrlStatic21);
	DDX_Control(pDX, IDC_STATIC_22,  m_ctrlStatic22);
	DDX_Control(pDX, IDC_STATIC_23,  m_ctrlStatic23);
	DDX_Control(pDX, IDC_STATIC_25,  m_ctrlStatic25);
	DDX_Control(pDX, IDC_STATIC_26,  m_ctrlStatic26);
	DDX_Control(pDX, IDC_STATIC_27,  m_ctrlStatic27);
	DDX_Control(pDX, IDC_STATIC_28,  m_ctrlStatic28);
	DDX_Control(pDX, IDC_STATIC_29,  m_ctrlStatic29);
	DDX_Control(pDX, IDC_STATIC_30,  m_ctrlStatic30);
	DDX_Control(pDX, IDC_STATIC_35,  m_ctrlStatic35);
	DDX_Control(pDX, IDC_STATIC_36,  m_ctrlStatic36);  // PASSAPORTE //Julio - BUG 3285 - Adequação de laudos
	DDX_Control(pDX, IDC_STATIC_185, m_ctrlStatic185); // RG         //Julio - BUG 3285 - Adequação de laudos
	DDX_Control(pDX, IDC_STATIC_186, m_ctrlStatic186); // CPF        //Julio - BUG 3285 - Adequação de laudos

	DDX_Control(pDX, IDC_STATIC_NOSOLOGICO,  m_ctrlStaticNosologico);
	DDX_Control(pDX, IDC_STATIC_BARCODE,  m_ctrlStaticBarcode);
	DDX_Control(pDX, IDC_STATIC_DATARICOVERO,  m_ctrlStaticDataRicovero);
	DDX_Control(pDX, IDC_STATIC_REPARTODEGENZA,  m_ctrlStaticRepartoDegenza);
	DDX_Control(pDX, IDC_STATIC_DATADECESSO,  m_ctrlStaticDataDecesso);	

	DDX_Control(pDX, IDC_STATIC_STP, m_ctrlStaticSTP);
	DDX_Control(pDX, IDC_STATIC_TEAM, m_ctrlStaticTEAM);

	
	//DDX_Control(pDX, IDC_RADIO_05_0, m_ctrlButtonSex0);
	//DDX_Control(pDX, IDC_RADIO_05_1, m_ctrlButtonSex1);
	//DDX_Control(pDX, IDC_RADIO_05_2, m_ctrlButtonSex2);
	//DDX_Control(pDX, IDC_RADIO_05_3, m_ctrlButtonSex3);
	DDX_Control(pDX, IDC_COMBO_05,	 m_ctrlComboSesso);
	DDX_Control(pDX, IDC_SEARCH,	 m_ctrlButtonSearch);
	DDX_Control(pDX, IDCANCEL,       m_ctrlButtonCancel);
	DDX_Control(pDX, IDOK,           m_ctrlButtonOK);
	
	DDX_Control(pDX, IDC_EDIT_06, m_ctrlData); // Data nascita //
	DDX_Control(pDX, IDC_EDIT_07, m_ctrlComuneNascita);
	DDX_Control(pDX, IDC_EDIT_08, m_ctrlPaziente08); // Professione //
	DDX_Control(pDX, IDC_EDIT_11, m_ctrlPaziente11); // Medico curante //
	DDX_Control(pDX, IDC_EDIT_15, m_ctrlComune);
	DDX_Control(pDX, IDC_EDIT_25, m_ctrlNazionalita);

	DDX_Control(pDX, IDC_CMB_REPARTODEGENZA, m_ctrlComboReparto);
	DDX_Control(pDX, IDC_EDIT_DATARICOVERO, m_ctrlDataRicovero);

	// paziente cronico //
	DDX_Control(pDX, IDC_COMBO_CRONICO, m_ctrlComboCronico);
	DDX_Control(pDX, IDC_EDIT_CRONICO, m_ctrlEditCronico);

	// paziente del direttore //
	DDX_Control(pDX, IDC_CHECK_DIRETTORE, m_ctrlCheckDirettore);
	DDX_Control(pDX, IDC_COMBO_DIRETTORE, m_ctrlComboDirettore);

	// paziente deceduto //
	DDX_Control(pDX, IDC_CHECK_DECEDUTO, m_ctrlCheckDeceduto);
	DDX_Control(pDX, IDC_EDIT_DATADECESSO, m_ctrlDataDecesso);	

	///
	///
	///

	// Sandro 15/11/2011 //
	if (pDX->m_bSaveAndValidate)
	{
		CString strTeeemp;

		// taglio il CAP a 5 caratteri //
		GetDlgItemText(IDC_EDIT_16, strTeeemp);
		if (strTeeemp.GetLength() > 5)
			SetDlgItemText(IDC_EDIT_16, strTeeemp.Left(5));

		// taglio la provincia a 5 caratteri //
		/*GetDlgItemText(IDC_EDIT_17, strTeeemp);
		if (strTeeemp.GetLength() > 5)
			SetDlgItemText(IDC_EDIT_17, strTeeemp.Left(5));*/
	}

	if (!m_pPazientiSet->IsFieldNull(&m_pPazientiSet->m_lContatore))
		SetDlgItemInt(IDC_EDIT_00, m_pPazientiSet->m_lContatore);

	DDX_FieldText(pDX, IDC_EDIT_01, m_pPazientiSet->m_sCodFisc, m_pPazientiSet->GetRecordset());
	DDX_FieldText(pDX, IDC_EDIT_STP, m_pPazientiSet->m_sCodiceSTP, m_pPazientiSet->GetRecordset());
	DDX_FieldText(pDX, IDC_EDIT_TEAM, m_pPazientiSet->m_sCodiceTEAM, m_pPazientiSet->GetRecordset());
	DDX_FieldText(pDX, IDC_EDIT_02, m_pPazientiSet->m_sCodSanit, m_pPazientiSet->GetRecordset());
	DDX_FieldText(pDX, IDC_EDIT_03, m_pPazientiSet->m_sCognome, m_pPazientiSet->GetRecordset());
	DDX_FieldText(pDX, IDC_EDIT_04, m_pPazientiSet->m_sNome, m_pPazientiSet->GetRecordset());
	
	if (m_pPazientiSet->IsFieldNull(&m_pPazientiSet->m_lSessoPaz) == FALSE)
	{
		switch (m_pPazientiSet->m_lSessoPaz)
		{
			case -1:
				SetDlgItemText(IDC_EDIT_05, theApp.GetMessageString(IDS_PAZIENTIDLG_ND));
				break;
			case 0:
				SetDlgItemText(IDC_EDIT_05, theApp.GetMessageString(IDS_PAZIENTIDLG_MALE));
				break;
			case 1:
				SetDlgItemText(IDC_EDIT_05, theApp.GetMessageString(IDS_PAZIENTIDLG_FEMALE));
				break;
			case 2:
				SetDlgItemText(IDC_EDIT_05, theApp.GetMessageString(IDS_PAZIENTIDLG_AMBIGOUS));
				break;
			case 3:
				SetDlgItemText(IDC_EDIT_05, theApp.GetMessageString(IDS_PAZIENTIDLG_NOTAPPLICABLE));
				break;
			case 4:
				SetDlgItemText(IDC_EDIT_05, theApp.GetMessageString(IDS_PAZIENTIDLG_OTHER));
				break;
			default:
				SetDlgItemText(IDC_EDIT_05, theApp.GetMessageString(IDS_PAZIENTIDLG_ND));
				break;
		}					
	}

	// Sandro 06/04/2012 // quando cerco SOLO per pazient e non ha senso che mi chieda un range di date (che ci perdo tempo e mi rompo le @@) //
	// if (m_iModalita == PAZ_SRCH && !theApp.m_bAnagrafeCentraleSolo)
	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
		DDX_Text(pDX, IDC_EDIT_06, m_ctrlData.m_strRicercaView);
	else
		DDX_DateMask(pDX, IDC_EDIT_06, m_pPazientiSet->m_lNatoIlCustom, m_pPazientiSet->GetRecordset());

	DDX_FieldText(pDX, IDC_EDIT_07, m_pPazientiSet->m_sNatoA, m_pPazientiSet->GetRecordset());
	DDX_FieldText(pDX, IDC_EDIT_08, m_pPazientiSet->m_sProfessione, m_pPazientiSet->GetRecordset());

	DDX_FieldText(pDX, IDC_EDIT_10, m_pPazientiSet->m_sMedicoEmail, m_pPazientiSet->GetRecordset());
	DDX_FieldText(pDX, IDC_EDIT_11, m_pPazientiSet->m_sMedicoCurante, m_pPazientiSet->GetRecordset());
	DDX_FieldText(pDX, IDC_EDIT_12, m_pPazientiSet->m_sMedicoTel, m_pPazientiSet->GetRecordset());
	DDX_FieldText(pDX, IDC_EDIT_13, m_pPazientiSet->m_sMedicoIndirizzo, m_pPazientiSet->GetRecordset());

	DDX_FieldText(pDX, IDC_EDIT_14, m_pPazientiSet->m_sVia, m_pPazientiSet->GetRecordset());
	DDX_FieldText(pDX, IDC_EDIT_15, m_pPazientiSet->m_sCitta, m_pPazientiSet->GetRecordset());
	DDX_FieldText(pDX, IDC_EDIT_16, m_pPazientiSet->m_sCAP, m_pPazientiSet->GetRecordset());
	DDX_FieldText(pDX, IDC_EDIT_17, m_pPazientiSet->m_sProvincia, m_pPazientiSet->GetRecordset());
	DDX_FieldText(pDX, IDC_EDIT_18, m_pPazientiSet->m_sTelefono1, m_pPazientiSet->GetRecordset());
	DDX_FieldText(pDX, IDC_EDIT_19, m_pPazientiSet->m_sTelefono2, m_pPazientiSet->GetRecordset());
	DDX_FieldText(pDX, IDC_EDIT_20, m_pPazientiSet->m_sFax, m_pPazientiSet->GetRecordset());
	DDX_FieldText(pDX, IDC_EDIT_21, m_pPazientiSet->m_sCellulare1, m_pPazientiSet->GetRecordset());
	DDX_FieldText(pDX, IDC_EDIT_22, m_pPazientiSet->m_sCellulare2, m_pPazientiSet->GetRecordset());
	DDX_FieldText(pDX, IDC_EDIT_23, m_pPazientiSet->m_sEmail, m_pPazientiSet->GetRecordset());

	DDX_FieldText(pDX, IDC_EDIT_24, m_pPazientiSet->m_sDenSegnalato, m_pPazientiSet->GetRecordset());

	DDX_FieldText(pDX, IDC_EDIT_25, m_pPazientiSet->m_sNazionalita, m_pPazientiSet->GetRecordset());

	DDX_FieldText(pDX, IDC_EDIT_26, m_pPazientiSet->m_sCodiceCliente, m_pPazientiSet->GetRecordset());
	DDX_FieldText(pDX, IDC_EDIT_27, m_pPazientiSet->m_sCognome2, m_pPazientiSet->GetRecordset());
	DDX_FieldText(pDX, IDC_EDIT_28, m_pPazientiSet->m_sNominativoPadre, m_pPazientiSet->GetRecordset());
	DDX_FieldText(pDX, IDC_EDIT_29, m_pPazientiSet->m_sNominativoMadre, m_pPazientiSet->GetRecordset());
	DDX_FieldText(pDX, IDC_EDIT_30, m_pPazientiSet->m_sUlssResidenza, m_pPazientiSet->GetRecordset());

	DDX_FieldText(pDX, IDC_EDIT_35, m_pPazientiSet->m_sLogin, m_pPazientiSet->GetRecordset());

	DDX_FieldText(pDX, IDC_EDIT_36, m_pPazientiSet->m_sIdentificazionePassaporto, m_pPazientiSet->GetRecordset()); // PASSAPORTE //Julio - BUG 3285 - Adequação de laudos
	DDX_FieldText(pDX, IDC_EDIT_37, m_pPazientiSet->m_sIdentificazioneDoc1, m_pPazientiSet->GetRecordset());       // RG         //Julio - BUG 3285 - Adequação de laudos
	DDX_FieldText(pDX, IDC_EDIT_45, m_pPazientiSet->m_sIdentificazioneDoc2, m_pPazientiSet->GetRecordset());       // CPF        //Julio - BUG 3285 - Adequação de laudos

	//DDX_Radio(pDX, IDC_RADIO_05_0, m_iSesso);
	//DDX_LBIndex(pDX, IDC_COMBO_05, m_iSessoComboSelIndex);
	DDX_Check(pDX, IDC_CHECK_23, m_bSendEmail);
	DDX_Check(pDX, IDC_CHECK_21, m_bSendSms);

	DDX_Check(pDX, IDC_CHECK_36, m_bPazienteDelDirettore);

	DDX_FieldText(pDX, IDC_EDIT_NOSOLOGICO, m_pPazientiSet->m_sCodiceRicovero, m_pPazientiSet->GetRecordset());
	DDX_FieldText(pDX, IDC_EDIT_BARCODE, m_pPazientiSet->m_sIdEpisodioRicovero, m_pPazientiSet->GetRecordset());
	//DDX_FieldText(pDX, IDC_EDIT_DATARICOVERO, m_pPazientiSet->m_sDataRicovero, m_pPazientiSet->GetRecordset());

	DDX_DateMask(pDX, IDC_EDIT_DATARICOVERO, m_pPazientiSet->m_lDataRicoveroCustom, m_pPazientiSet->GetRecordset());
	
	if (m_iModalita == PAZ_ADDN || m_iModalita == PAZ_EDIT)
	{
		DDX_FieldInviantiCombo(pDX, IDC_CMB_REPARTODEGENZA, m_pPazientiSet->m_lIdRepartoDegenza, m_pPazientiSet, INTERNO);
	}
	else
	{
		DDX_FieldInviantiEdit(pDX, IDC_EDIT_REPARTODEGENZA, m_pPazientiSet->m_lIdRepartoDegenza, m_pPazientiSet, INTERNO);
	}
	//DDX_FieldText(pDX, IDC_EDIT_REPARTODEGENZA, m_pPazientiSet->m_lIdRepartoDegenza, m_pPazientiSet->GetRecordset());

	DDX_Check(pDX, IDC_CHECK_DECEDUTO, m_pPazientiSet->m_bDeceduto);
	
	if (m_pPazientiSet->m_bDeceduto == FALSE)
		m_pPazientiSet->m_lDataDecesso = 0;

	if (theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI)
		DDX_Text(pDX, IDC_EDIT_DATADECESSO, m_ctrlDataDecesso.m_strRicercaView);
	else
		DDX_DateMask(pDX, IDC_EDIT_DATADECESSO, m_pPazientiSet->m_lDataDecesso, m_pPazientiSet->GetRecordset());	
}

HBRUSH CPazientiDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor (pDC, pWnd, nCtlColor);

	BOOL bVerificaCampiObbligatori = FALSE;
	switch(m_iModalita)
	{
		case PAZ_ADDN:
		{
			bVerificaCampiObbligatori = TRUE;
			break;
		}
		case PAZ_EDIT:
		{
			bVerificaCampiObbligatori = TRUE;
			break;
		}
	}

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_00:
		case IDC_STATIC_01:
		case IDC_STATIC_02:
		case IDC_STATIC_03:
		case IDC_STATIC_04:
		case IDC_STATIC_05:
		case IDC_STATIC_06:
		case IDC_STATIC_07:
		case IDC_STATIC_08:
		case IDC_STATIC_25:
		case IDC_STATIC_26:
		case IDC_STATIC_27:
		case IDC_STATIC_28:
		case IDC_STATIC_29:
		case IDC_STATIC_30:
		case IDC_STATIC_STP:
		case IDC_STATIC_TEAM:
		case IDC_EDIT_00:
		case IDC_EDIT_01:
		case IDC_EDIT_02:
		case IDC_EDIT_03:
		case IDC_EDIT_04:
		case IDC_EDIT_05:
		/*case IDC_RADIO_05_0:
		case IDC_RADIO_05_1:
		case IDC_RADIO_05_2:
		case IDC_RADIO_05_3:*/
		case IDC_COMBO_05:
		case IDC_EDIT_06:
		case IDC_EDIT_07:
		case IDC_EDIT_08:
		case IDC_EDIT_25:
		case IDC_EDIT_26:
		case IDC_EDIT_27:
		case IDC_EDIT_28:
		case IDC_EDIT_29:
		case IDC_EDIT_30:
		case IDC_EDIT_STP:
		case IDC_EDIT_TEAM:
		{
			pDC->SetTextColor(theApp.m_color[2]);

			if (bVerificaCampiObbligatori)
				if (CCampiObbligatoriPazienteSet().IsObbligatorioStatic(pWnd->GetDlgCtrlID()))
					pDC->SetBkColor(RGB_OBBLIG_GIALLO);

			break;
		}
		case IDC_STATIC_14:
		case IDC_STATIC_15:
		case IDC_STATIC_16:
		case IDC_STATIC_17:
		case IDC_STATIC_18:
		case IDC_STATIC_19:
		case IDC_STATIC_20:
		case IDC_STATIC_21:
		case IDC_STATIC_22:
		case IDC_STATIC_23:
		case IDC_STATIC_35:
		case IDC_EDIT_14:
		case IDC_EDIT_15:
		case IDC_EDIT_16:
		case IDC_EDIT_17:
		case IDC_EDIT_18:
		case IDC_EDIT_19:
		case IDC_EDIT_20:
		case IDC_EDIT_21:
		case IDC_CHECK_21:
		case IDC_EDIT_22:
		case IDC_EDIT_23:
		case IDC_CHECK_23:
		{
			pDC->SetTextColor(theApp.m_color[3]);
			
			if (bVerificaCampiObbligatori)
				if (CCampiObbligatoriPazienteSet().IsObbligatorioStatic(pWnd->GetDlgCtrlID()))
					pDC->SetBkColor(RGB_OBBLIG_GIALLO);

			break;
		}
		case IDC_EDIT_35:
		case IDC_BUTTON_35:
		{
			if (m_bUserFocus)
				pDC->SetTextColor(RGB(255,255,255));
			else
				pDC->SetTextColor(RGB(0,0,0));

			if (m_bValidUser)
				pDC->SetBkColor(RGB(0,255,0));
			else
				pDC->SetBkColor(RGB(255,0,0));

			break;
		}
		case IDC_STATIC_10:
		case IDC_STATIC_11:
		case IDC_STATIC_12:
		case IDC_STATIC_13:
		case IDC_EDIT_10:
		case IDC_EDIT_11:
		case IDC_EDIT_12:
		case IDC_EDIT_13:
		{
			pDC->SetTextColor(theApp.m_color[4]);

			if (bVerificaCampiObbligatori)
				if (CCampiObbligatoriPazienteSet().IsObbligatorioStatic(pWnd->GetDlgCtrlID()))
					pDC->SetBkColor(RGB_OBBLIG_GIALLO);

			break;
		}
		case IDC_EDIT_24:
		{
			pDC->SetTextColor(theApp.m_color[5]);
			
			if (bVerificaCampiObbligatori)
				if (CCampiObbligatoriPazienteSet().IsObbligatorioStatic(pWnd->GetDlgCtrlID()))
					pDC->SetBkColor(RGB_OBBLIG_GIALLO);
		}
		case IDC_CHECK_36:
		{
			pDC->SetTextColor(theApp.m_color[5]);
			break;
		}
		case IDC_STATIC_NOSOLOGICO:
		case IDC_STATIC_BARCODE:
		case IDC_STATIC_DATARICOVERO:
		case IDC_STATIC_REPARTODEGENZA:
		case IDC_EDIT_NOSOLOGICO:
		case IDC_EDIT_BARCODE:
		case IDC_EDIT_DATARICOVERO:
		case IDC_EDIT_REPARTODEGENZA:
		{
			pDC->SetTextColor(theApp.m_color[5]);
			break;
		}
	}

	return hBrush;
}

BOOL CPazientiDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	theApp.LocalizeDialog(this, CPazientiDlg::IDD, "PazientiDlg");

	// Sandro 20/11/2013 // RAS 20130186 //

	if (theApp.m_bMostraSecondoCognome)
	{
		GetDlgItem(IDC_STATIC_27)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_27)->ShowWindow(SW_SHOW);
	}
	else
	{
		CRect rect1;
		GetDlgItem(IDC_STATIC_27)->GetWindowRect(rect1);

		CRect rect2;
		GetDlgItem(IDC_STATIC_04)->GetWindowRect(rect2);

		long lOffsetVert = rect2.top - rect1.top;
		CRect rectTemp;

		// sposto in su tutti i controlli sotto al secondo cognome che è nascosto, altrimenti mi resterebbe il buco nell'interfaccia //

		GetDlgItem(IDC_STATIC_04)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_STATIC_04)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_EDIT_04)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_EDIT_04)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		
		GetDlgItem(IDC_STATIC_06)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_STATIC_06)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_EDIT_06)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_EDIT_06)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		
		GetDlgItem(IDC_STATIC_05)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_STATIC_05)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_EDIT_05)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_EDIT_05)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		/*GetDlgItem(IDC_RADIO_05_0)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_RADIO_05_0)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_RADIO_05_1)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_RADIO_05_1)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_RADIO_05_2)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_RADIO_05_2)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_RADIO_05_3)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_RADIO_05_3)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);*/

		GetDlgItem(IDC_COMBO_05)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_COMBO_05)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_STATIC_07)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_STATIC_07)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_EDIT_07)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_EDIT_07)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_STATIC_01)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_STATIC_01)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_EDIT_01)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_EDIT_01)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_STATIC_02)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_STATIC_02)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_EDIT_02)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_EDIT_02)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_STATIC_26)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_STATIC_26)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_EDIT_26)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_EDIT_26)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_STATIC_25)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_STATIC_25)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_EDIT_25)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_EDIT_25)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_STATIC_08)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_STATIC_08)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_EDIT_08)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_EDIT_08)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_STATIC_28)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_STATIC_28)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_EDIT_28)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_EDIT_28)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_STATIC_29)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_STATIC_29)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_EDIT_29)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_EDIT_29)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_STATIC_30)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_STATIC_30)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_EDIT_30)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_EDIT_30)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_STATIC_STP)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_STATIC_STP)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_EDIT_STP)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_EDIT_STP)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_STATIC_TEAM)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_STATIC_TEAM)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_EDIT_TEAM)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		GetDlgItem(IDC_EDIT_TEAM)->SetWindowPos(NULL, rectTemp.left, rectTemp.top - lOffsetVert, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}

	//

	m_ctrlData.SetParam(this, m_pEsamiView, theApp.GetMessageString(IDS_EDT_DATAPAZIENTE), SOLO_DATA);
	m_ctrlDataRicovero.SetParam(this, m_pEsamiView, theApp.GetMessageString(IDS_EDT_DATARICOVERO), SOLO_DATA);
	m_ctrlDataDecesso.SetParam(this, m_pEsamiView, theApp.GetMessageString(IDS_EDT_DATADECESSO), SOLO_DATA);

	m_ctrlComuneNascita.SetParam(m_pEsamiView, &m_pPazientiSet->m_lIDComuneNascita, GetDlgItem(IDC_EDIT_07), NULL, NULL);
	m_ctrlComune.SetParam(m_pEsamiView, &m_pPazientiSet->m_lIDComune, GetDlgItem(IDC_EDIT_15), GetDlgItem(IDC_EDIT_16), GetDlgItem(IDC_EDIT_17));
	// m_ctrlCAP.SetParam(m_pEsamiView, &m_pPazientiSet->m_lIDComune, GetDlgItem(IDC_EDIT_15), GetDlgItem(IDC_EDIT_16), GetDlgItem(IDC_EDIT_17));
	// m_ctrlProvincia.SetParam(m_pEsamiView, &m_pPazientiSet->m_lIDComune, GetDlgItem(IDC_EDIT_15), GetDlgItem(IDC_EDIT_16), GetDlgItem(IDC_EDIT_17));

	// Sandro 15/11/2011 //
	GetDlgItem(IDC_EDIT_16)->SendMessage(EM_SETLIMITTEXT, 5);
	GetDlgItem(IDC_EDIT_17)->SendMessage(EM_SETLIMITTEXT, 5);

	//
	GetDlgItem(IDC_FRAME_00)->SetFont(&theApp.m_fontBig);
	GetDlgItem(IDC_FRAME_01)->SetFont(&theApp.m_fontBig);
	GetDlgItem(IDC_FRAME_02)->SetFont(&theApp.m_fontBig);
	GetDlgItem(IDC_FRAME_03)->SetFont(&theApp.m_fontBig);
	GetDlgItem(IDC_FRAME_04)->SetFont(&theApp.m_fontBig);
	GetDlgItem(IDC_FRAME_05)->SetFont(&theApp.m_fontBig);
	GetDlgItem(IDC_FRAME_06)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_FRAME_07)->SetFont(&theApp.m_fontBold);

	switch(m_iModalita)
	{
		case PAZ_ADDN:
		case PAZ_EDIT:
		{
			SetDlgItemText(IDOK, theApp.GetMessageString(IDS_PAZIENTIDLG_OK_1));
			GetDlgItem(IDCANCEL)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_EDIT_00)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_00)->ShowWindow(SW_HIDE);

			SendDlgItemMessage(IDC_EDIT_01, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_STP, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_TEAM, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_02, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);

			// Sandro 24/05/2013 // RAS 20130095 //
			BOOL bReadOnlyCognomeNomeDatanascita = FALSE;
			SendDlgItemMessage(IDC_EDIT_03, EM_SETREADONLY, (WPARAM)bReadOnlyCognomeNomeDatanascita, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_04, EM_SETREADONLY, (WPARAM)bReadOnlyCognomeNomeDatanascita, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_06, EM_SETREADONLY, (WPARAM)bReadOnlyCognomeNomeDatanascita, (LPARAM)0);
			//

			GetDlgItem(IDC_EDIT_05)->ShowWindow(SW_HIDE);
			/*GetDlgItem(IDC_RADIO_05_0)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_RADIO_05_1)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_RADIO_05_2)->ShowWindow(SW_SHOW);*/
			GetDlgItem(IDC_COMBO_05)->ShowWindow(SW_SHOW);
			SendDlgItemMessage(IDC_EDIT_07, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_08, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_09, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);

			SendDlgItemMessage(IDC_EDIT_10, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_11, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_12, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_13, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);

			SendDlgItemMessage(IDC_EDIT_14, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_15, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_16, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_17, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_18, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_19, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_20, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_21, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_22, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_23, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);

			SendDlgItemMessage(IDC_EDIT_24, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);

			SendDlgItemMessage(IDC_EDIT_25, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);

			SendDlgItemMessage(IDC_EDIT_26, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_27, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_28, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_29, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_30, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);

			if (m_iModalita == PAZ_ADDN || (m_iModalita == PAZ_EDIT && theApp.m_bAttivaRicoveri == FALSE))
			{
				SendDlgItemMessage(IDC_EDIT_NOSOLOGICO, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
				SendDlgItemMessage(IDC_EDIT_BARCODE, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
				SendDlgItemMessage(IDC_EDIT_DATARICOVERO, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
				SendDlgItemMessage(IDC_CMB_REPARTODEGENZA, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			}

			GetDlgItem(IDC_CHECK_21)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK_23)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_35)->EnableWindow(TRUE);
			SendDlgItemMessage(IDC_EDIT_35, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);

			SendDlgItemMessage(IDC_EDIT_36, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0); // PASSAPORTE //Julio - BUG 3285 - Adequação de laudos
			SendDlgItemMessage(IDC_EDIT_37, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0); // RG         //Julio - BUG 3285 - Adequação de laudos
			SendDlgItemMessage(IDC_EDIT_45, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0); // CPF        //Julio - BUG 3285 - Adequação de laudos

			if (theApp.m_bConsultazioneWEB)
			{
				GetDlgItem(IDC_CHECK_21)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CHECK_23)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON_35)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_EDIT_35)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATIC_35)->ShowWindow(SW_SHOW);
			}
			else
			{
				GetDlgItem(IDC_CHECK_21)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CHECK_23)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON_35)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT_35)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATIC_35)->ShowWindow(SW_HIDE);
			}

			// certificazione SISS comanda rispetto a quella MEF //
			if (m_iModalita == PAZ_EDIT)
			{
				CString sTitle;
				GetWindowText(sTitle);

				if (m_pPazientiSet->m_bCertificazioneSISS)
				{
					GetDlgItem(IDC_EDIT_03)->EnableWindow(FALSE);
					GetDlgItem(IDC_EDIT_04)->EnableWindow(FALSE);
					// il sesso va mostrato come stringa //
					GetDlgItem(IDC_EDIT_05)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_EDIT_05)->EnableWindow(FALSE);
					/*GetDlgItem(IDC_RADIO_05_0)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_RADIO_05_1)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_RADIO_05_2)->ShowWindow(SW_HIDE);
					GetDlgItem(IDC_RADIO_05_3)->ShowWindow(SW_HIDE);*/
					GetDlgItem(IDC_COMBO_05)->ShowWindow(SW_HIDE);

					GetDlgItem(IDC_EDIT_06)->EnableWindow(FALSE);
					GetDlgItem(IDC_EDIT_07)->EnableWindow(FALSE);
					GetDlgItem(IDC_EDIT_01)->EnableWindow(FALSE);
					GetDlgItem(IDC_EDIT_STP)->EnableWindow(FALSE);
					GetDlgItem(IDC_EDIT_TEAM)->EnableWindow(FALSE);

					m_ctrlCheckDeceduto.EnableWindow(FALSE);
					SendDlgItemMessage(IDC_EDIT_DATADECESSO, EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);

					sTitle += " - " + theApp.GetMessageString(IDS_PAZIENTE_CERT_SISS);
					SetWindowText(sTitle);
				}
				else
				{
					if (m_pPazientiSet->m_bCertificazioneMEF)
					{
						GetDlgItem(IDC_EDIT_01)->EnableWindow(FALSE);
						GetDlgItem(IDC_EDIT_STP)->EnableWindow(FALSE);
						GetDlgItem(IDC_EDIT_TEAM)->EnableWindow(FALSE);
						sTitle += " - " + theApp.GetMessageString(IDS_PAZIENTE_CERT_MEF);
						SetWindowText(sTitle);
					}

					m_ctrlCheckDeceduto.EnableWindow(TRUE);
					if (m_pPazientiSet->m_bDeceduto == TRUE)
						SendDlgItemMessage(IDC_EDIT_DATADECESSO, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
					else
						SendDlgItemMessage(IDC_EDIT_DATADECESSO, EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);					

				}
			}		
			else
			{
				m_pPazientiSet->m_bDeceduto = FALSE;
				m_ctrlCheckDeceduto.EnableWindow(TRUE);
				SendDlgItemMessage(IDC_EDIT_DATADECESSO, EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);
			}

			// reparto combo //
			m_lProvenienza = INTERNO;
			m_ctrlComboReparto.SetParam(m_pEsamiView->m_pPazientiSet, &m_pEsamiView->m_pPazientiSet->m_lIdRepartoDegenza, &m_lProvenienza);
			m_ctrlComboReparto.ShowWindow(SW_SHOW);

			// paziente cronico //
			if ((m_iModalita == PAZ_EDIT) && !m_pPazientiSet->IsFieldNull(&m_pPazientiSet->m_lIDMalattiaCronica) && (m_pPazientiSet->m_lIDMalattiaCronica > 0))
			{
				m_ctrlStaticFrame06.ShowWindow(SW_SHOW);
				m_ctrlComboCronico.ShowWindow(SW_HIDE);
				m_ctrlEditCronico.ShowWindow(SW_SHOW);

				m_ctrlEditCronico.SetReadOnly(TRUE);
				m_ctrlEditCronico.SetWindowText(CMalattieCronicheSet().GetDescrizione(m_pPazientiSet->m_lIDMalattiaCronica));
			}
			else
			{
				m_ctrlStaticFrame06.ShowWindow(SW_HIDE);
				m_ctrlComboCronico.ShowWindow(SW_HIDE);
				m_ctrlEditCronico.ShowWindow(SW_HIDE);
			}

			// paziente del direttore //
			m_ctrlStaticFrame07.ShowWindow(theApp.m_bMostraPazienteInCuraDalDirettore ? SW_SHOW : SW_HIDE);
			m_ctrlCheckDirettore.ShowWindow(theApp.m_bMostraPazienteInCuraDalDirettore ? SW_SHOW : SW_HIDE);
			m_ctrlComboDirettore.ShowWindow(SW_HIDE);

			m_ctrlCheckDirettore.EnableWindow(theApp.m_bMostraPazienteInCuraDalDirettore);

			//
			break;
		}
		case PAZ_SRCH:
		{
			GetDlgItem(IDC_EDIT_00)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_00)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_SEARCH)->ShowWindow(SW_SHOW);

			SendDlgItemMessage(IDC_EDIT_01, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_STP, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_TEAM, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_02, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_03, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_04, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			GetDlgItem(IDC_EDIT_05)->ShowWindow(SW_HIDE);
			/*GetDlgItem(IDC_RADIO_05_0)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_RADIO_05_1)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_RADIO_05_2)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_RADIO_05_3)->ShowWindow(SW_SHOW);*/
			GetDlgItem(IDC_COMBO_05)->ShowWindow(SW_SHOW);
			SendDlgItemMessage(IDC_EDIT_06, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_07, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_08, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);

			SendDlgItemMessage(IDC_EDIT_10, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_11, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_12, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_13, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);

			SendDlgItemMessage(IDC_EDIT_14, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_15, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_16, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_17, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_18, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_19, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_20, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_21, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_22, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_23, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);

			SendDlgItemMessage(IDC_EDIT_24, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);

			SendDlgItemMessage(IDC_EDIT_25, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);

			SendDlgItemMessage(IDC_EDIT_26, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_27, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_28, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_29, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_30, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);

			SendDlgItemMessage(IDC_EDIT_DATADECESSO, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);

			GetDlgItem(IDC_CHECK_21)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK_23)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_35)->EnableWindow(TRUE);
			SendDlgItemMessage(IDC_EDIT_35, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);

			SendDlgItemMessage(IDC_EDIT_36, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0); // PASSAPORTE //Julio - BUG 3285 - Adequação de laudos
			SendDlgItemMessage(IDC_EDIT_37, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0); // RG         //Julio - BUG 3285 - Adequação de laudos
			SendDlgItemMessage(IDC_EDIT_45, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0); // CPF        //Julio - BUG 3285 - Adequação de laudos

			if (theApp.m_bConsultazioneWEB)
			{
				GetDlgItem(IDC_CHECK_21)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CHECK_23)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON_35)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_EDIT_35)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATIC_35)->ShowWindow(SW_SHOW);
			}
			else
			{
				GetDlgItem(IDC_CHECK_21)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CHECK_23)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON_35)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT_35)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATIC_35)->ShowWindow(SW_HIDE);
			}

			SendDlgItemMessage(IDC_EDIT_NOSOLOGICO, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
			SendDlgItemMessage(IDC_EDIT_BARCODE, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);

			// paziente cronico //
			if (theApp.m_lOpzionalePazientiCronici == OPZIONALE_PAZIENTI_CRONICI)
			{
				m_ctrlStaticFrame06.ShowWindow(SW_SHOW);
				m_ctrlComboCronico.ShowWindow(SW_SHOW);
				m_ctrlEditCronico.ShowWindow(SW_HIDE);

				RiempiComboCronico();
			}
			else
			{
				m_ctrlStaticFrame06.ShowWindow(SW_HIDE);
				m_ctrlComboCronico.ShowWindow(SW_HIDE);
				m_ctrlEditCronico.ShowWindow(SW_HIDE);
			}

			// paziente del direttore //
			m_ctrlStaticFrame07.ShowWindow(theApp.m_bMostraPazienteInCuraDalDirettore ? SW_SHOW : SW_HIDE);
			m_ctrlCheckDirettore.ShowWindow(SW_HIDE);
			m_ctrlComboDirettore.ShowWindow(theApp.m_bMostraPazienteInCuraDalDirettore ? SW_SHOW : SW_HIDE);

			if (theApp.m_bMostraPazienteInCuraDalDirettore)
				RiempiComboDirettore();

			//
			break;
		}
		case PAZ_SHOW:
		{
			CString sTitle;
			GetWindowText(sTitle);

			if (m_pPazientiSet->m_bCertificazioneSISS)
			{
				sTitle += " - " + theApp.GetMessageString(IDS_PAZIENTE_CERT_SISS);
				SetWindowText(sTitle);
			}
			else
			{
				if (m_pPazientiSet->m_bCertificazioneMEF)
				{
					sTitle += " - " + theApp.GetMessageString(IDS_PAZIENTE_CERT_MEF);
					SetWindowText(sTitle);
				}
			}

			if (theApp.m_bConsultazioneWEB)
			{
				GetDlgItem(IDC_CHECK_21)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CHECK_23)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON_35)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_EDIT_35)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATIC_35)->ShowWindow(SW_SHOW);
			}
			else
			{
				GetDlgItem(IDC_CHECK_21)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CHECK_23)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON_35)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT_35)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATIC_35)->ShowWindow(SW_HIDE);
			}

			GetDlgItem(IDC_EDIT_REPARTODEGENZA)->ShowWindow(SW_SHOW);

			// paziente cronico //
			if (!m_pPazientiSet->IsFieldNull(&m_pPazientiSet->m_lIDMalattiaCronica) && (m_pPazientiSet->m_lIDMalattiaCronica > 0))
			{
				m_ctrlStaticFrame06.ShowWindow(SW_SHOW);
				m_ctrlComboCronico.ShowWindow(SW_HIDE);
				m_ctrlEditCronico.ShowWindow(SW_SHOW);

				m_ctrlEditCronico.SetReadOnly(TRUE);
				m_ctrlEditCronico.SetWindowText(CMalattieCronicheSet().GetDescrizione(m_pPazientiSet->m_lIDMalattiaCronica));
			}
			else
			{
				m_ctrlStaticFrame06.ShowWindow(SW_HIDE);
				m_ctrlComboCronico.ShowWindow(SW_HIDE);
				m_ctrlEditCronico.ShowWindow(SW_HIDE);
			}

			// paziente del direttore //
			m_ctrlStaticFrame07.ShowWindow(theApp.m_bMostraPazienteInCuraDalDirettore ? SW_SHOW : SW_HIDE);
			m_ctrlCheckDirettore.ShowWindow(theApp.m_bMostraPazienteInCuraDalDirettore ? SW_SHOW : SW_HIDE);
			m_ctrlComboDirettore.ShowWindow(SW_HIDE);

			m_ctrlCheckDirettore.EnableWindow(FALSE);

			//
			break;
		}
		default:
		{
			ASSERT(FALSE);

			if (theApp.m_bConsultazioneWEB)
			{
				GetDlgItem(IDC_CHECK_21)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_CHECK_23)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON_35)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_EDIT_35)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_STATIC_35)->ShowWindow(SW_SHOW);
			}
			else
			{
				GetDlgItem(IDC_CHECK_21)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_CHECK_23)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTON_35)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT_35)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_STATIC_35)->ShowWindow(SW_HIDE);
			}

			// paziente cronico //
			m_ctrlStaticFrame06.ShowWindow(SW_HIDE);
			m_ctrlComboCronico.ShowWindow(SW_HIDE);
			m_ctrlEditCronico.ShowWindow(SW_HIDE);

			// paziente del direttore //
			m_ctrlStaticFrame07.ShowWindow(SW_HIDE);
			m_ctrlCheckDirettore.ShowWindow(SW_HIDE);
			m_ctrlComboDirettore.ShowWindow(SW_HIDE);

			//
			break;
		}
	}

	m_ctrlPaziente08.SetParam(this, CMB_PAZ_PROFESSIO, m_pPazientiSet, NULL, &m_pPazientiSet->m_sProfessione, 50);
	m_ctrlPaziente08.SetParam(FALSE, FALSE, TRUE, TRUE, FALSE);
	m_ctrlPaziente11.SetParams(this, m_pPazientiSet, &m_pPazientiSet->m_sMedicoCurante, &m_pPazientiSet->m_lMedicoCurante, 50, 2, MEDICI_CURANTI);
	m_ctrlPaziente11.SetStrings(&m_pPazientiSet->m_sMedicoIndirizzo, &m_pPazientiSet->m_sMedicoTel, &m_pPazientiSet->m_sMedicoEmail);
	m_ctrlNazionalita.SetParam(this, CMB_PAZ_NAZIONALI, m_pPazientiSet, NULL, &m_pPazientiSet->m_sNazionalita, 50);
	m_ctrlNazionalita.SetParam(FALSE, FALSE, TRUE, TRUE, FALSE);

	//Cambio gestione del sesso. Metto qua sotto se no no capisso più un casso

	//Popolo combo
	int index = -1;
	if (m_iModalita == PAZ_SRCH)
	{
		index = m_ctrlComboSesso.AddString(theApp.GetMessageString(IDS_TUTTI));
		m_ctrlComboSesso.SetItemData(index, -2);
	}

	index = m_ctrlComboSesso.AddString(theApp.GetMessageString(IDS_PAZIENTIDLG_ND));
	m_ctrlComboSesso.SetItemData(index, -1);
	index = m_ctrlComboSesso.AddString(theApp.GetMessageString(IDS_PAZIENTIDLG_MALE));
	m_ctrlComboSesso.SetItemData(index, 0);
	index = m_ctrlComboSesso.AddString(theApp.GetMessageString(IDS_PAZIENTIDLG_FEMALE));
	m_ctrlComboSesso.SetItemData(index, 1);
	index = m_ctrlComboSesso.AddString(theApp.GetMessageString(IDS_PAZIENTIDLG_AMBIGOUS));
	m_ctrlComboSesso.SetItemData(index, 2);
	index = m_ctrlComboSesso.AddString(theApp.GetMessageString(IDS_PAZIENTIDLG_NOTAPPLICABLE));
	m_ctrlComboSesso.SetItemData(index, 3);
	index = m_ctrlComboSesso.AddString(theApp.GetMessageString(IDS_PAZIENTIDLG_OTHER));
	m_ctrlComboSesso.SetItemData(index, 4);	

	//Setto valore
	switch (m_iModalita)
	{
		case PAZ_EDIT:
		{
			for (int i = 0; i < m_ctrlComboSesso.GetCount(); i++)
			{
				if (m_ctrlComboSesso.GetItemData(i) == m_pPazientiSet->m_lSessoPaz)
				{
					m_ctrlComboSesso.SetCurSel(i);
					break;
				}
			}
			break;
		}
		case PAZ_SRCH:
		{
			for (int i = 0; i < m_ctrlComboSesso.GetCount(); i++)
			{
				if (m_ctrlComboSesso.GetItemData(i) == -2)
				{
					m_ctrlComboSesso.SetCurSel(i);
					break;
				}
			}
			break;
		}
		case PAZ_SHOW:
		{
			for (int i = 0; i < m_ctrlComboSesso.GetCount(); i++)
			{
				if (m_ctrlComboSesso.GetItemData(i) == -1)
				{
					m_ctrlComboSesso.SetCurSel(i);
					break;
				}
			}
			break;
		}
		default:
		{
			for (int i = 0; i < m_ctrlComboSesso.GetCount(); i++)
			{
				if (m_ctrlComboSesso.GetItemData(i) == -1)
				{
					m_ctrlComboSesso.SetCurSel(i);
					break;
				}
			}
			break;
		}
	}

	UpdateData(FALSE);

	return bReturn;
}

void CPazientiDlg::OnCancel()
{
	CDialog::OnCancel();
}

void CPazientiDlg::OnBnClickedOk()
{
	CString strTemp;

	// taglio il CAP a 5 caratteri //
	GetDlgItemText(IDC_EDIT_16, strTemp);
	if (strTemp.GetLength() > 5)
		SetDlgItemText(IDC_EDIT_16, strTemp.Left(5));

	// taglio la provincia a 5 caratteri //
	/*GetDlgItemText(IDC_EDIT_17, strTemp);
	if (strTemp.GetLength() > 5)
		SetDlgItemText(IDC_EDIT_17, strTemp.Left(5));*/

	switch(m_iModalita)
	{
		case PAZ_ADDN:
		case PAZ_EDIT:
		{
			OnOkAddnEdit();
			break;
		}
		case PAZ_SRCH:
		{
			UpdateData(TRUE);
			m_pPazientiSet->m_sCognome.Trim();
			m_pPazientiSet->m_sNome.Trim();
			UpdateData(FALSE);

			m_pPazientiSet->m_lSessoPaz = m_ctrlComboSesso.GetItemData(m_ctrlComboSesso.GetCurSel());
			m_pPazientiSet->SetFieldNull(&m_pPazientiSet->m_lSessoPaz, FALSE);
			m_pPazientiSet->SetFieldDirty(&m_pPazientiSet->m_lSessoPaz, TRUE);

			m_pPazientiSet->m_bSendEmail = m_bSendEmail;
			m_pPazientiSet->SetFieldNull(&m_pPazientiSet->m_bSendEmail, FALSE);
			m_pPazientiSet->SetFieldDirty(&m_pPazientiSet->m_bSendEmail, TRUE);

			m_pPazientiSet->m_bSendEmail = m_bSendSms;
			m_pPazientiSet->SetFieldNull(&m_pPazientiSet->m_bSendSms, FALSE);
			m_pPazientiSet->SetFieldDirty(&m_pPazientiSet->m_bSendSms, TRUE);

			// Sandro 23/07/2013 //
			// m_pPazientiSet->m_sNatoIlCustom.Empty();
			// ComponiRicercaEx(&m_pPazientiSet->m_sNatoIlCustom, m_ctrlData.m_strRicerca, "NatoIlCustom", FALSE, TRUE);			

			// Sandro 03/09/2013 //
			// m_pPazientiSet->m_bPazienteDelDirettore = m_bPazienteDelDirettore;
			// m_pPazientiSet->SetFieldNull(&m_pPazientiSet->m_bPazienteDelDirettore, FALSE);
			// m_pPazientiSet->SetFieldDirty(&m_pPazientiSet->m_bPazienteDelDirettore, TRUE);			

			// paziente cronico //
			CString sFilterC = "";
			int nCurSelC = m_ctrlComboCronico.GetCurSel();
			if (nCurSelC > 0)
			{
				long lItemData = m_ctrlComboCronico.GetItemData(nCurSelC);

				switch(lItemData)
				{
					case -IDS_PAZIENTI_SOLO_NON_CRONICI:
					{
						sFilterC = "IDMalattiaCronica=0";
						break;
					}
					case -IDS_PAZIENTI_TUTTI_CRONICI:
					{
						sFilterC = "IDMalattiaCronica>0";
						break;
					}
					case 0:
					{
						break;
					}
					default:
					{
						sFilterC.Format("IDMalattiaCronica=%li", lItemData);
						break;
					}
				}
			}

			// paziente del direttore //
			CString sFilterD = "";
			if (theApp.m_bMostraPazienteInCuraDalDirettore)
			{
				int nCurSelD = m_ctrlComboDirettore.GetCurSel();
				if (nCurSelD > 0)
				{
					long lItemData = m_ctrlComboDirettore.GetItemData(nCurSelD);

					switch (lItemData)
					{
					case IDS_PAZIENTI_SOLO_DIRETTORE:
					{
						sFilterD = "PazienteDelDirettore<>0";
						break;
					}
					case IDS_PAZIENTI_SOLO_NON_DIRETTORE:
					{
						sFilterD = "PazienteDelDirettore=0";
						break;
					}
					default:
					{
						break;
					}
					}
				}
			}

			// filtro "EXTRA" //
			m_pPazientiSet->m_sFiltroExtra = "";
			if (!sFilterC.IsEmpty() && (!sFilterD.IsEmpty()))
			{
				m_pPazientiSet->m_sFiltroExtra = "(" + sFilterC + ") AND (" + sFilterD + ")";
			}
			else if (!sFilterC.IsEmpty())
			{
				m_pPazientiSet->m_sFiltroExtra = "(" + sFilterC + ")";
			}
			else if (!sFilterD.IsEmpty())
			{
				m_pPazientiSet->m_sFiltroExtra = "(" + sFilterD + ")";
			}
			m_pPazientiSet->m_sFiltroExtra.Trim();


			//Filtri aggiuntivi
			ComponiRicercaEx(&m_pPazientiSet->m_sFiltroExtra, m_ctrlDataDecesso.m_strRicerca, "DataDecesso", FALSE, TRUE);

			//
			OnOK();
			break;
		}
		default:
		{
			OnOK();
			break;
		}
	}
}

void CPazientiDlg::OnOkAddnEdit()
{
	CString strTemp;

	// verifica campi obbligatori //

	BOOL bVerificaCampiObbligatori = FALSE;

	switch(m_iModalita)
	{
		case PAZ_ADDN:
		{
			bVerificaCampiObbligatori = TRUE;
			break;
		}
		case PAZ_EDIT:
		{
			bVerificaCampiObbligatori = TRUE;
			break;
		}
	}

	if (bVerificaCampiObbligatori)
	{
		CWnd* pWnd = GetWindow(GW_CHILD);
		while(pWnd)
		{
			TCHAR szClassName[256];
			::GetClassName(pWnd->GetSafeHwnd(), szClassName, 255);

			if (CString("Edit").CompareNoCase(szClassName) == 0)
			{
				if (CCampiObbligatoriPazienteSet().IsObbligatorioEdit(pWnd->GetDlgCtrlID()))
				{
					GetDlgItemText(pWnd->GetDlgCtrlID(), strTemp);
					strTemp.Trim();

					if (pWnd->GetDlgCtrlID() == IDC_EDIT_06)
					{
						if (strTemp == m_ctrlData.GetDefault())
						{
							theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_THEFIELD) + CCampiObbligatoriPazienteSet().GetDescrizione(pWnd->GetDlgCtrlID()) + theApp.GetMessageString(IDS_ITSNEEDED));
							return;
						}
					}
					else
					{
						if (strTemp.IsEmpty())
						{
							theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_THEFIELD) + CCampiObbligatoriPazienteSet().GetDescrizione(pWnd->GetDlgCtrlID()) + theApp.GetMessageString(IDS_ITSNEEDED));
							return;
						}
					}
				}
			}

			pWnd = pWnd->GetWindow(GW_HWNDNEXT);
		}
	}

	//

	GetDlgItemText(IDC_EDIT_35, strTemp);
	strTemp.Trim();
	if (!m_bValidUser && strTemp != "")
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_LOGIN_ALREADY_USED));
		return;
	}

	UpdateData(TRUE);

	if (m_bSendEmail == TRUE)
	{
		GetDlgItemText(IDC_EDIT_23, strTemp);
		strTemp.Trim();
		if (strTemp == "")
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_MAIL_NEEDED));
			return;
		}
	}

	if (m_bSendSms == TRUE)
	{
		GetDlgItemText(IDC_EDIT_21, strTemp);
		strTemp.Trim();
		if (strTemp == "")
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_SMS_NEEDED));
			return;
		}
	}

	m_pPazientiSet->m_lSessoPaz = m_ctrlComboSesso.GetItemData(m_ctrlComboSesso.GetCurSel());
	m_pPazientiSet->m_bSendEmail = m_bSendEmail;
	m_pPazientiSet->m_bSendSms = m_bSendSms;
	m_pPazientiSet->m_sCAP = m_pPazientiSet->m_sCAP.Left(5);
	m_pPazientiSet->m_sProvincia = m_pPazientiSet->m_sProvincia;

	m_pPazientiSet->SetFieldNull(&m_pPazientiSet->m_lSessoPaz, FALSE);
	m_pPazientiSet->SetFieldDirty(&m_pPazientiSet->m_lSessoPaz, TRUE);
	m_pPazientiSet->SetFieldNull(&m_pPazientiSet->m_bSendEmail, FALSE);
	m_pPazientiSet->SetFieldDirty(&m_pPazientiSet->m_bSendEmail, TRUE);
	m_pPazientiSet->SetFieldNull(&m_pPazientiSet->m_bSendSms, FALSE);
	m_pPazientiSet->SetFieldDirty(&m_pPazientiSet->m_bSendSms, TRUE);

	m_pPazientiSet->m_bPazienteDelDirettore = m_bPazienteDelDirettore;
	m_pPazientiSet->SetFieldNull(&m_pPazientiSet->m_bPazienteDelDirettore, FALSE);
	m_pPazientiSet->SetFieldDirty(&m_pPazientiSet->m_bPazienteDelDirettore, TRUE);

	m_pPazientiSet->SetFieldNull(&m_pPazientiSet->m_bDeceduto, FALSE);
	m_pPazientiSet->SetFieldDirty(&m_pPazientiSet->m_bDeceduto, TRUE);

	// verifica la congruenza tra la data di nascita e il luogo di nascita //
	if (!m_pPazientiSet->IsFieldNull(&m_pPazientiSet->m_lIDComuneNascita) && m_pPazientiSet->m_lIDComuneNascita > 0 && !m_pPazientiSet->IsFieldNull(&m_pPazientiSet->m_lNatoIlCustom) && m_pPazientiSet->m_lNatoIlCustom > 0)
	{
		if (!CheckComuneDataNascita())
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PAZIENTIDLG_INCONGRUENZA));
			return;
		}
	}

	// verifica codice fiscale //
	if ((theApp.m_nLanguage == loc_ita) || (theApp.m_nLanguage == loc_eng)) // Sandro 26/11/2014 // solo in Italia! //
	{
		if (!m_pPazientiSet->IsFieldNull(&m_pPazientiSet->m_sCodFisc) && !m_pPazientiSet->m_sCodFisc.IsEmpty() && !theApp.m_bPersonalizzazioniBrasileEinstein)
		{
			if (m_pPazientiSet->m_sCodFisc.GetLength() == 11)
			{
				for(int i = 0; i < m_pPazientiSet->m_sCodFisc.GetLength(); i++)
				{
					if (!std::isdigit(m_pPazientiSet->m_sCodFisc[i]))
					{
						CString temp;
						temp.Format(theApp.GetMessageString(IDS_PAZIENTIDLG_CFERR), 11);
						theApp.AfxMessageBoxEndo(temp);
						return;
					}
				}
			}
			else if (m_pPazientiSet->m_sCodFisc.GetLength() == 16)
			{
				if ((m_pPazientiSet->m_sCodFisc.Left(3).CompareNoCase("STP") == 0) && std::isdigit(m_pPazientiSet->m_sCodFisc[3]) && std::isdigit(m_pPazientiSet->m_sCodFisc[4]) && std::isdigit(m_pPazientiSet->m_sCodFisc[5]))
				{
					// codice STP //

					if ( !std::isalpha(m_pPazientiSet->m_sCodFisc[0]) ||
						!std::isalpha(m_pPazientiSet->m_sCodFisc[1]) ||
						!std::isalpha(m_pPazientiSet->m_sCodFisc[2]) ||
						!std::isdigit(m_pPazientiSet->m_sCodFisc[3]) ||
						!std::isdigit(m_pPazientiSet->m_sCodFisc[4]) ||
						!std::isdigit(m_pPazientiSet->m_sCodFisc[5]) ||
						!std::isdigit(m_pPazientiSet->m_sCodFisc[6]) ||
						!std::isdigit(m_pPazientiSet->m_sCodFisc[7]) ||
						!std::isdigit(m_pPazientiSet->m_sCodFisc[8]) ||
						!std::isdigit(m_pPazientiSet->m_sCodFisc[9]) ||
						!std::isdigit(m_pPazientiSet->m_sCodFisc[10]) ||
						!std::isdigit(m_pPazientiSet->m_sCodFisc[11]) ||
						!std::isdigit(m_pPazientiSet->m_sCodFisc[12]) ||
						!std::isdigit(m_pPazientiSet->m_sCodFisc[13]) ||
						!std::isdigit(m_pPazientiSet->m_sCodFisc[14]) ||
						!std::isdigit(m_pPazientiSet->m_sCodFisc[15]) )
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PAZIENTIDLG_CFERR_STP));
						return;
					}
				}
				else if ((m_pPazientiSet->m_sCodFisc.Left(3).CompareNoCase("ENI") == 0) && std::isdigit(m_pPazientiSet->m_sCodFisc[3]) && std::isdigit(m_pPazientiSet->m_sCodFisc[4]) && std::isdigit(m_pPazientiSet->m_sCodFisc[5]))
				{
					// codice ENI //

					if ( !std::isalpha(m_pPazientiSet->m_sCodFisc[0]) ||
						!std::isalpha(m_pPazientiSet->m_sCodFisc[1]) ||
						!std::isalpha(m_pPazientiSet->m_sCodFisc[2]) ||
						!std::isdigit(m_pPazientiSet->m_sCodFisc[3]) ||
						!std::isdigit(m_pPazientiSet->m_sCodFisc[4]) ||
						!std::isdigit(m_pPazientiSet->m_sCodFisc[5]) ||
						!std::isdigit(m_pPazientiSet->m_sCodFisc[6]) ||
						!std::isdigit(m_pPazientiSet->m_sCodFisc[7]) ||
						!std::isdigit(m_pPazientiSet->m_sCodFisc[8]) ||
						!std::isdigit(m_pPazientiSet->m_sCodFisc[9]) ||
						!std::isdigit(m_pPazientiSet->m_sCodFisc[10]) ||
						!std::isdigit(m_pPazientiSet->m_sCodFisc[11]) ||
						!std::isdigit(m_pPazientiSet->m_sCodFisc[12]) ||
						!std::isdigit(m_pPazientiSet->m_sCodFisc[13]) ||
						!std::isdigit(m_pPazientiSet->m_sCodFisc[14]) ||
						!std::isdigit(m_pPazientiSet->m_sCodFisc[15]) )
					{
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PAZIENTIDLG_CFERR_ENI));
						return;
					}
				}
				else
				{
					// codice fiscale "normale" //

					if (	!std::isalpha(m_pPazientiSet->m_sCodFisc[0]) || 
						!std::isalpha(m_pPazientiSet->m_sCodFisc[1]) || 
						!std::isalpha(m_pPazientiSet->m_sCodFisc[2]) || 
						!std::isalpha(m_pPazientiSet->m_sCodFisc[3]) || 
						!std::isalpha(m_pPazientiSet->m_sCodFisc[4]) || 
						!std::isalpha(m_pPazientiSet->m_sCodFisc[5]) || 
						!std::isdigit(m_pPazientiSet->m_sCodFisc[6]) || 
						!std::isdigit(m_pPazientiSet->m_sCodFisc[7]) || 
						!std::isalpha(m_pPazientiSet->m_sCodFisc[8]) || 
						!std::isdigit(m_pPazientiSet->m_sCodFisc[9]) || 
						!std::isdigit(m_pPazientiSet->m_sCodFisc[10]) || 
						!std::isalpha(m_pPazientiSet->m_sCodFisc[11]) || 
						!std::isdigit(m_pPazientiSet->m_sCodFisc[12]) || 
						!std::isdigit(m_pPazientiSet->m_sCodFisc[13]) || 
						// !std::isdigit(m_pPazientiSet->m_sCodFisc[14]) || // Sandro 15/09/2014 // RAS 20140075 //
						!std::isalpha(m_pPazientiSet->m_sCodFisc[15]) )
					{
						CString temp;
						temp.Format(theApp.GetMessageString(IDS_PAZIENTIDLG_CFERR), 16);
						theApp.AfxMessageBoxEndo(temp);
						return;
					}
				}
			}
			else
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PAZIENTIDLG_CF));
				return;
			}
		}
	}

	OnOK();
}

BOOL CPazientiDlg::OnOkAddnEditSG()
{
	if (m_iModalita == PAZ_ADDN)
	{
		CString strTemp;

		GetDlgItemText(IDC_EDIT_26, strTemp); // codice CSS //
		strTemp.Trim();
		if (strTemp.GetLength() < 3)
		{
			GetDlgItemText(IDC_EDIT_03, strTemp);
			strTemp.Trim();
			if (strTemp.GetLength() < 3)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PAZIENTIDLG_ERR_DATA1));
				return FALSE;
			}
			GetDlgItemText(IDC_EDIT_04, strTemp);
			strTemp.Trim();
			if (strTemp.GetLength() < 3)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PAZIENTIDLG_ERR_DATA2));
				return FALSE;
			}
		}
	}

	UpdateData(TRUE);
	m_pPazientiSet->m_lSessoPaz = m_ctrlComboSesso.GetItemData(m_ctrlComboSesso.GetCurSel());
	m_pPazientiSet->m_sCAP = m_pPazientiSet->m_sCAP.Left(5);
	m_pPazientiSet->m_sProvincia = m_pPazientiSet->m_sProvincia;
	m_pPazientiSet->SetFieldNull(&m_pPazientiSet->m_lSessoPaz, FALSE);
	m_pPazientiSet->SetFieldDirty(&m_pPazientiSet->m_lSessoPaz, TRUE);

	m_pPazientiSet->m_bPazienteDelDirettore = m_bPazienteDelDirettore;
	m_pPazientiSet->SetFieldNull(&m_pPazientiSet->m_bPazienteDelDirettore, FALSE);
	m_pPazientiSet->SetFieldDirty(&m_pPazientiSet->m_bPazienteDelDirettore, TRUE);

	// verifica la congruenza tra la data di nascita e il luogo di nascita //
	if (!m_pPazientiSet->IsFieldNull(&m_pPazientiSet->m_lIDComuneNascita) && m_pPazientiSet->m_lIDComuneNascita > 0 && !m_pPazientiSet->IsFieldNull(&m_pPazientiSet->m_lNatoIlCustom) && m_pPazientiSet->m_lNatoIlCustom > 0)
	{
		if (!CheckComuneDataNascita())
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PAZIENTIDLG_INCONGRUENZA));
			return FALSE;
		}
	}

	// verifica codice fiscale //
	if (!m_pPazientiSet->IsFieldNull(&m_pPazientiSet->m_sCodFisc) && !m_pPazientiSet->m_sCodFisc.IsEmpty() && !theApp.m_bPersonalizzazioniBrasileEinstein)
	{
		if (m_pPazientiSet->m_sCodFisc.GetLength() == 11)
		{
			for(int i = 0; i < m_pPazientiSet->m_sCodFisc.GetLength(); i++)
			{
				if (!std::isdigit(m_pPazientiSet->m_sCodFisc[i]))
				{
					CString temp;
					temp.Format(theApp.GetMessageString(IDS_PAZIENTIDLG_CFERR), 11);
					theApp.AfxMessageBoxEndo(temp);
					return FALSE;
				}
			}
		}
		else if (m_pPazientiSet->m_sCodFisc.GetLength() == 16)
		{
			if ((m_pPazientiSet->m_sCodFisc.Left(3).CompareNoCase("STP") == 0) && std::isdigit(m_pPazientiSet->m_sCodFisc[3]) && std::isdigit(m_pPazientiSet->m_sCodFisc[4]) && std::isdigit(m_pPazientiSet->m_sCodFisc[5]))
			{
				// codice STP //

				if ( !std::isalpha(m_pPazientiSet->m_sCodFisc[0]) ||
					!std::isalpha(m_pPazientiSet->m_sCodFisc[1]) ||
					!std::isalpha(m_pPazientiSet->m_sCodFisc[2]) ||
					!std::isdigit(m_pPazientiSet->m_sCodFisc[3]) ||
					!std::isdigit(m_pPazientiSet->m_sCodFisc[4]) ||
					!std::isdigit(m_pPazientiSet->m_sCodFisc[5]) ||
					!std::isdigit(m_pPazientiSet->m_sCodFisc[6]) ||
					!std::isdigit(m_pPazientiSet->m_sCodFisc[7]) ||
					!std::isdigit(m_pPazientiSet->m_sCodFisc[8]) ||
					!std::isdigit(m_pPazientiSet->m_sCodFisc[9]) ||
					!std::isdigit(m_pPazientiSet->m_sCodFisc[10]) ||
					!std::isdigit(m_pPazientiSet->m_sCodFisc[11]) ||
					!std::isdigit(m_pPazientiSet->m_sCodFisc[12]) ||
					!std::isdigit(m_pPazientiSet->m_sCodFisc[13]) ||
					!std::isdigit(m_pPazientiSet->m_sCodFisc[14]) ||
					!std::isdigit(m_pPazientiSet->m_sCodFisc[15]) )
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PAZIENTIDLG_CFERR_STP));
					return FALSE;
				}
			}
			else if ((m_pPazientiSet->m_sCodFisc.Left(3).CompareNoCase("ENI") == 0) && std::isdigit(m_pPazientiSet->m_sCodFisc[3]) && std::isdigit(m_pPazientiSet->m_sCodFisc[4]) && std::isdigit(m_pPazientiSet->m_sCodFisc[5]))
			{
				// codice ENI //

				if ( !std::isalpha(m_pPazientiSet->m_sCodFisc[0]) ||
					!std::isalpha(m_pPazientiSet->m_sCodFisc[1]) ||
					!std::isalpha(m_pPazientiSet->m_sCodFisc[2]) ||
					!std::isdigit(m_pPazientiSet->m_sCodFisc[3]) ||
					!std::isdigit(m_pPazientiSet->m_sCodFisc[4]) ||
					!std::isdigit(m_pPazientiSet->m_sCodFisc[5]) ||
					!std::isdigit(m_pPazientiSet->m_sCodFisc[6]) ||
					!std::isdigit(m_pPazientiSet->m_sCodFisc[7]) ||
					!std::isdigit(m_pPazientiSet->m_sCodFisc[8]) ||
					!std::isdigit(m_pPazientiSet->m_sCodFisc[9]) ||
					!std::isdigit(m_pPazientiSet->m_sCodFisc[10]) ||
					!std::isdigit(m_pPazientiSet->m_sCodFisc[11]) ||
					!std::isdigit(m_pPazientiSet->m_sCodFisc[12]) ||
					!std::isdigit(m_pPazientiSet->m_sCodFisc[13]) ||
					!std::isdigit(m_pPazientiSet->m_sCodFisc[14]) ||
					!std::isdigit(m_pPazientiSet->m_sCodFisc[15]) )
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PAZIENTIDLG_CFERR_ENI));
					return FALSE;
				}
			}
			else
			{
				// codice fiscale "normale" //

				if (	!std::isalpha(m_pPazientiSet->m_sCodFisc[0]) || 
					!std::isalpha(m_pPazientiSet->m_sCodFisc[1]) || 
					!std::isalpha(m_pPazientiSet->m_sCodFisc[2]) || 
					!std::isalpha(m_pPazientiSet->m_sCodFisc[3]) || 
					!std::isalpha(m_pPazientiSet->m_sCodFisc[4]) || 
					!std::isalpha(m_pPazientiSet->m_sCodFisc[5]) || 
					!std::isdigit(m_pPazientiSet->m_sCodFisc[6]) || 
					!std::isdigit(m_pPazientiSet->m_sCodFisc[7]) || 
					!std::isalpha(m_pPazientiSet->m_sCodFisc[8]) || 
					!std::isdigit(m_pPazientiSet->m_sCodFisc[9]) || 
					!std::isdigit(m_pPazientiSet->m_sCodFisc[10]) || 
					!std::isalpha(m_pPazientiSet->m_sCodFisc[11]) || 
					!std::isdigit(m_pPazientiSet->m_sCodFisc[12]) || 
					!std::isdigit(m_pPazientiSet->m_sCodFisc[13]) || 
					!std::isdigit(m_pPazientiSet->m_sCodFisc[14]) || 
					!std::isalpha(m_pPazientiSet->m_sCodFisc[15]) )
				{
					CString temp;
					temp.Format(theApp.GetMessageString(IDS_PAZIENTIDLG_CFERR), 16);
					theApp.AfxMessageBoxEndo(temp);
					return FALSE;
				}
			}
		}
		else
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PAZIENTIDLG_CF));
			return FALSE;
		}
	}

	return TRUE;
}

void CPazientiDlg::OnBnClickedSearch()
{
	m_bSearchNow = TRUE;
	OnBnClickedOk();
}

void CPazientiDlg::OnEnChangeEdit35()
{
	CString strTemp;
	GetDlgItem(IDC_EDIT_35)->GetWindowText(strTemp);
	strTemp.Trim();
	if (strTemp != "")
	{
		CString query;
		if (m_iModalita == PAZ_ADDN)
			query = "SELECT COUNT(*) as OCC FROM EPAZIENTI WHERE ELIMINATO = 0 AND LOGIN LIKE '" + strTemp  + "'";
		else
			query.Format("SELECT COUNT(*) as OCC FROM EPAZIENTI WHERE ELIMINATO = 0 AND LOGIN LIKE '%s' AND CONTATORE = %li", strTemp, m_pPazientiSet->m_lContatore);

		try
		{
			CRecordset setCount(&theApp.m_dbEndox); // non mi interessa tanto è per il conteggio //
			setCount.Open(CRecordset::snapshot, query, CRecordset::readOnly);
			if (!setCount.IsEOF())
			{
				CDBVariant dbVariant;
				setCount.GetFieldValue("OCC", dbVariant, SQL_C_SLONG);

				setCount.Close();

				if (dbVariant.m_lVal == 0)
					m_bValidUser = TRUE;
				else
					m_bValidUser = FALSE;
			}
		}
		catch(...)
		{
			theApp.AfxMessageBoxEndo("!!! ONAVLIS !!!");
		}
	}
	else
	{
		m_bValidUser = TRUE;
	}

	GetDlgItem(IDC_EDIT_35)->Invalidate();
}

void CPazientiDlg::OnEnSetfocusEdit35()
{
	m_bUserFocus = TRUE;
}

void CPazientiDlg::OnEnKillfocusEdit35()
{
	m_bUserFocus = FALSE;
}

void CPazientiDlg::OnBnClickedButton10()
{
	BeginWaitCursor();

	CString sMailDest = "";
	GetDlgItemText(IDC_EDIT_10, sMailDest);

	WritePrivateProfileString("Settings", "MailDest", sMailDest, theApp.m_sDirProg + "\\MailSender.cfg");
	// WritePrivateProfileString("Settings", "MailSender", "", theApp.m_sDirProg + "\\MailSender.cfg");
	WritePrivateProfileString("Settings", "Modality", "", theApp.m_sDirProg + "\\MailSender.cfg");
	WritePrivateProfileString("Settings", "Object", m_pEsamiView->m_pPazientiSet->m_sCognome + " " + m_pEsamiView->m_pPazientiSet->m_sNome, theApp.m_sDirProg + "\\MailSender.cfg");
	WritePrivateProfileString("Settings", "TempPath", theApp.m_sDirTemp, theApp.m_sDirProg + "\\MailSender.cfg");

	WritePrivateProfileInt("Settings", "AttachmentNumber", 0, theApp.m_sDirProg + "\\MailSender.cfg");

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	TCHAR szProcess[255];
	sprintf_s(szProcess, "%s\\MailSender.exe", theApp.m_sDirProg);

	if (CreateProcess(NULL, szProcess, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}

	EndWaitCursor();
}

void CPazientiDlg::OnBnClickedButton35()
{
	// Generazione automatica Password
	CString strCognome, strNome, strUser;
	GetDlgItem(IDC_EDIT_03)->GetWindowText(strCognome);
	GetDlgItem(IDC_EDIT_04)->GetWindowText(strNome);

	if (strCognome == "" || strNome == "")
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_NAME_NEEDED));
		return;
	}

	strUser = strCognome + strNome.Left(1);
	if (strUser.GetLength() < 4)
		while(strUser.GetLength() < 4)
			strUser += "_";

	strUser.Remove('\'');

	try
	{
		CString query = "SELECT COUNT(*) as OCC FROM EPAZIENTI WHERE ELIMINATO = 0 AND LOGIN LIKE '" + strUser + "'";
		CRecordset setCount(&theApp.m_dbEndox); // non mi interessa tanto è per il conteggio //
		setCount.Open(CRecordset::snapshot, query, CRecordset::readOnly);
		if (!setCount.IsEOF())
		{
			CDBVariant dbVariant;
			setCount.GetFieldValue("OCC", dbVariant, SQL_C_SLONG);
			setCount.Close();

			//Se lo user non è usato lo propongo, altrimenti genero un successivo
			if (dbVariant.m_lVal > 0)
			{
				for(int i=1; i<10000; i++)
				{
					CString strUserTemp;
					strUserTemp.Format("%s%li", strUser, i);
					query = "SELECT COUNT(*) as OCC FROM EPAZIENTI WHERE ELIMINATO = 0 AND LOGIN LIKE '" + strUserTemp + "'";
					setCount.Open(CRecordset::snapshot, query, CRecordset::readOnly);
					if (!setCount.IsEOF())
					{
						CDBVariant dbVariant;
						setCount.GetFieldValue("OCC", dbVariant, SQL_C_SLONG);
						setCount.Close();
						if (dbVariant.m_lVal == 0)
						{
							strUser = strUserTemp;
							break;
						}
					}
				}
			}
		}
	}
	catch(...)
	{
		theApp.AfxMessageBoxEndo("!!! ONAVLIS !!!");
	}

	GetDlgItem(IDC_EDIT_35)->SetWindowText(strUser);

}

BOOL CPazientiDlg::CheckComuneDataNascita()
{
	CString dataNascita = CCustomDate(m_pPazientiSet->m_lNatoIlCustom).GetDate("%Y%m%d");
	CString dataInizioValidita = CComuniSet().GetDataInizioValidita(m_pPazientiSet->m_lIDComuneNascita);
	CTime now = CTime::GetCurrentTime();
	CString dataFineValidita =  CComuniSet().GetDataFineValidita(m_pPazientiSet->m_lIDComuneNascita);
	if (dataFineValidita == "") 
		dataFineValidita = now.Format("%Y%m%d");

	if (dataNascita < dataInizioValidita || dataNascita > dataFineValidita)
		return FALSE;
	else
		return TRUE;
}

void CPazientiDlg::RiempiComboCronico()
{
	m_ctrlComboCronico.SetRedraw(FALSE);
	m_ctrlComboCronico.ResetContent();

	int nIndex = 0;

	m_ctrlComboCronico.InsertString(nIndex, "");
	m_ctrlComboCronico.SetItemData(nIndex, 0);
	nIndex++;

	m_ctrlComboCronico.InsertString(nIndex, theApp.GetMessageString(IDS_PAZIENTI_SOLO_NON_CRONICI));
	m_ctrlComboCronico.SetItemData(nIndex, -IDS_PAZIENTI_SOLO_NON_CRONICI);
	nIndex++;

	m_ctrlComboCronico.InsertString(nIndex, theApp.GetMessageString(IDS_PAZIENTI_TUTTI_CRONICI));
	m_ctrlComboCronico.SetItemData(nIndex, -IDS_PAZIENTI_TUTTI_CRONICI);
	nIndex++;

	CMalattieCronicheSet setTemp;
	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CPazientiDlg::RiempiComboCronico"))
	{
		while(!setTemp.IsEOF())
		{
			m_ctrlComboCronico.InsertString(nIndex, "- " + setTemp.m_sDescrizione);
			m_ctrlComboCronico.SetItemData(nIndex, setTemp.m_lID);

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CPazientiDlg::RiempiComboCronico");
	}

	m_ctrlComboCronico.SetCurSel(0);
	m_ctrlComboCronico.SetRedraw(TRUE);
}

void CPazientiDlg::RiempiComboDirettore()
{
	m_ctrlComboDirettore.SetRedraw(FALSE);
	m_ctrlComboDirettore.ResetContent();

	int nIndex = 0;

	m_ctrlComboDirettore.InsertString(nIndex, "");
	m_ctrlComboDirettore.SetItemData(nIndex, 0);
	nIndex++;

	m_ctrlComboDirettore.InsertString(nIndex, theApp.GetMessageString(IDS_PAZIENTI_SOLO_DIRETTORE));
	m_ctrlComboDirettore.SetItemData(nIndex, IDS_PAZIENTI_SOLO_DIRETTORE);
	nIndex++;

	m_ctrlComboDirettore.InsertString(nIndex, theApp.GetMessageString(IDS_PAZIENTI_SOLO_NON_DIRETTORE));
	m_ctrlComboDirettore.SetItemData(nIndex, IDS_PAZIENTI_SOLO_NON_DIRETTORE);
	nIndex++;

	m_ctrlComboDirettore.SetCurSel(0);
	m_ctrlComboDirettore.SetRedraw(TRUE);
}


void CPazientiDlg::OnBnClickedCheckDeceduto()
{
	if (m_ctrlCheckDeceduto.GetCheck() == BST_CHECKED)
		SendDlgItemMessage(IDC_EDIT_DATADECESSO, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
	else
		SendDlgItemMessage(IDC_EDIT_DATADECESSO, EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);

	UpdateData(TRUE);
	UpdateData(FALSE);
}
