#include "stdafx.h"
#include "Endox.h"
#include "ComboDynForm.h"

#include "ComboAltreAnomalieSet.h"
#include "ComboCauseNonCompletamentoSet.h"
#include "ComboComplicanzeSet.h"
#include "ComboConclusioniColonSet.h"
#include "ComboConclusioniScreeningSet.h"
#include "ComboDiagnosiFinaleSet.h"
#include "ComboPuliziaSet.h"
#include "ComboTolleranzaSet.h"
#include "EsamiSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CTipoEsameCombo CComboDynForm1::m_ctrlTipoEsame;
CExtTipoEsame CComboDynForm1::m_ctrlTipoEsameTxt;
CMediciCombo CComboDynForm1::m_ctrlMedico;
CExtMedico CComboDynForm1::m_ctrlMedicoTxt;
CMediciCombo CComboDynForm1::m_ctrlAssistente;
CExtMedico CComboDynForm1::m_ctrlAssistenteTxt;
CInfermieriCombo CComboDynForm1::m_ctrlInfermiere1;
CExtInfermiere CComboDynForm1::m_ctrlInfermiere1Txt;
CInfermieriCombo CComboDynForm1::m_ctrlInfermiere2;
CExtInfermiere CComboDynForm1::m_ctrlInfermiere2Txt;
CInviantiCombo CComboDynForm1::m_ctrlInviante;
CExtInviante CComboDynForm1::m_ctrlInvianteTxt;
CComboTransCombo CComboDynForm1::m_ctrlComplicanzeImmediate;
CExtComboTrans CComboDynForm1::m_ctrlComplicanzeImmediateTxt;
CComboTransCombo CComboDynForm1::m_ctrlComplicanzeTardive;
CExtComboTrans CComboDynForm1::m_ctrlComplicanzeTardiveTxt;
CComboTransCombo CComboDynForm1::m_ctrlPulizia;
CExtComboTrans CComboDynForm1::m_ctrlPuliziaTxt;
CComboTransCombo CComboDynForm1::m_ctrlCauseNonCompletamento;
CExtComboTrans CComboDynForm1::m_ctrlCauseNonCompletamentoTxt;
CComboTransCombo CComboDynForm1::m_ctrlTolleranza;
CExtComboTrans CComboDynForm1::m_ctrlTolleranzaTxt;
CComboTransCombo CComboDynForm1::m_ctrlConclusioniScreening;
CExtComboTrans CComboDynForm1::m_ctrlConclusioniScreeningTxt;
CComboTransCombo CComboDynForm1::m_ctrlConclusioniColon;
CExtComboTrans CComboDynForm1::m_ctrlConclusioniColonTxt;
CComboTransCombo CComboDynForm1::m_ctrlDiagnosiFinale;
CExtComboTrans CComboDynForm1::m_ctrlDiagnosiFinaleTxt;
CComboTransCombo CComboDynForm1::m_ctrlAltreAnomalie;
CExtComboTrans CComboDynForm1::m_ctrlAltreAnomalieTxt;
CComboBox CComboDynForm1::m_ctrlEsameUrgente;

CComboDynForm1::CComboDynForm1(CWnd* pParent, CEsamiView* pEsamiView, long lContenuto)
	: CEndoxDynForm(CComboDynForm1::IDD, pParent, pEsamiView),
	m_setComboComplicanzeImmediate(FALSE),
	m_setComboComplicanzeTardive(TRUE)
{
	m_lContenuto = lContenuto;
}

CComboDynForm1::~CComboDynForm1()
{
}

BEGIN_MESSAGE_MAP(CComboDynForm1, CEndoxDynForm)
	ON_WM_CTLCOLOR()

	ON_CBN_SETFOCUS(IDC_COMBO, OnCbnSetfocusCombo)
END_MESSAGE_MAP()

void CComboDynForm1::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lContenuto, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[lContenuto] == NULL)
	{
		pEsamiView->m_pDynForm[lContenuto] = new CComboDynForm1(NULL, pEsamiView, lContenuto);
		if (pEsamiView->m_pDynForm[lContenuto] != NULL)
		{
			pEsamiView->m_pDynForm[lContenuto]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[lContenuto]->m_lColore = lColore;
			pEsamiView->m_pDynForm[lContenuto]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[lContenuto]->CreateChildForm(CComboDynForm1::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CComboDynForm1::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

		case IDC_COMBO:
		case IDC_EDIT:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

void CComboDynForm1::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	switch(m_lContenuto)
	{
		case cmb_tipoesame:
		{
			DDX_Control(pDX, IDC_COMBO, m_ctrlTipoEsame);
			DDX_Control(pDX, IDC_EDIT, m_ctrlTipoEsameTxt);

			DDX_FieldTipoEsameCombo(pDX, IDC_COMBO, m_pEsamiView->m_pEsamiSet->m_lIDEsame, m_pEsamiView->m_pEsamiSet);
			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlTipoEsameTxt.m_strRicercaView);
			else
				DDX_FieldTipoEsameEdit(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lIDEsame, m_pEsamiView->m_pEsamiSet);

			break;
		}

		case cmb_medico1:
		{
			DDX_Control(pDX, IDC_COMBO, m_ctrlMedico);
			DDX_Control(pDX, IDC_EDIT, m_ctrlMedicoTxt);

			//DDX_FieldOperatoriCombo(pDX, IDC_COMBO, m_pEsamiView->m_pEsamiSet->m_lMedico, m_pEsamiView->m_pEsamiSet);
			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
			{
				// Luiz - 19/06/2019 - P3 - Melhoria do processo de busca
				CString sPesquisa = m_ctrlMedicoTxt.m_strRicercaView;
				if (m_ctrlMedicoTxt.m_strRicercaView == "#NULL#")
				{
					sPesquisa = "";
					m_ctrlMedicoTxt.m_strRicercaView = "0";
				}
				else if (theApp.m_bPersonalizzazioniBrasileFleury && m_ctrlMedicoTxt.m_strRicercaView.IsEmpty())
				{
					m_ctrlMedicoTxt.m_strRicercaView = m_ctrlMedicoTxt.GetCurrentUtentiMedici();
					sPesquisa = m_ctrlMedicoTxt.m_strRicercaView;
				}

				DDX_Text(pDX, IDC_EDIT, sPesquisa);
			}
			else
			{
				if (theApp.m_nProgramMode & MODIFY_RECORD_ESAMI)// MODO EDIÇÃO DO REGISTRO
				{//DEPOIS QUE SELECIONOU UM MEDICO DA LISTA (DUPLO CLIQUE)
					// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
					if (m_ctrlMedicoTxt.m_strRicercaView == "#NULL#")
					{
						m_ctrlMedicoTxt.m_strRicercaView = "";
						m_pEsamiView->m_pEsamiSet->m_lMedico = 0;
						DDX_Text(pDX, IDC_EDIT, m_ctrlMedicoTxt.m_strRicercaView);
						break;
					}

					//	DDX_Text(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lMedico);

					
					if (m_ctrlMedicoTxt.m_strRicercaView.IsEmpty())
					{//1A VEZ QUE ENTRA NA EDIÇÃO DO REGISTRO
						if (m_ctrlMedicoTxt.m_strRicerca == "-1")
						{
							m_ctrlMedicoTxt.m_strRicercaView = "";
							m_pEsamiView->m_pEsamiSet->m_lMedico = 0;
							DDX_Text(pDX, IDC_EDIT, m_ctrlMedicoTxt.m_strRicercaView);
							break;
						}
						else
						{// 1A VEZ QUE ENTRA NA EDIÇÃO DO REGISTRO
							DDX_FieldOperatoriEdit(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lMedico, m_pEsamiView->m_pEsamiSet);
						}
					}
					
					if (!m_ctrlMedicoTxt.m_strRicercaView.IsEmpty())
					{//DEPOIS QUE SELECIONOU UM MEDICO DA LISTA (DUPLO CLIQUE)
						long lMedico = atol(m_ctrlMedicoTxt.m_strRicerca);
						// Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
						//if (pDX->m_bSaveAndValidate)
						//{
							m_pEsamiView->m_pEsamiSet->m_lMedico = lMedico;
							DDX_Text(pDX, IDC_EDIT, m_ctrlMedicoTxt.m_strRicercaView);
							DDX_FieldOperatoriEdit(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lMedico, m_pEsamiView->m_pEsamiSet);
						//}
						//else
						//{
							//DDX_FieldOperatoriEdit(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lMedico, m_pEsamiView->m_pEsamiSet);
							//DDX_Text(pDX, IDC_EDIT, m_ctrlMedicoTxt.m_strRicercaView);
						//}
					}
					
				}
				else
				{//DEFAULT
					DDX_FieldOperatoriEdit(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lMedico, m_pEsamiView->m_pEsamiSet);
				}
			}
			break;
		}

		case cmb_medico2:
		{
			DDX_Control(pDX, IDC_COMBO, m_ctrlAssistente);
			DDX_Control(pDX, IDC_EDIT, m_ctrlAssistenteTxt);

			DDX_FieldOperatoriCombo(pDX, IDC_COMBO, m_pEsamiView->m_pEsamiSet->m_lAssistente, m_pEsamiView->m_pEsamiSet);
			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlAssistenteTxt.m_strRicercaView);
			else
				DDX_FieldOperatoriEdit(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lAssistente, m_pEsamiView->m_pEsamiSet);

			break;
		}

		case cmb_infermiere1:
		{
			DDX_Control(pDX, IDC_COMBO, m_ctrlInfermiere1);
			DDX_Control(pDX, IDC_EDIT, m_ctrlInfermiere1Txt);

			DDX_FieldInfermieriCombo(pDX, IDC_COMBO, m_pEsamiView->m_pEsamiSet->m_lInfermiere1, m_pEsamiView->m_pEsamiSet);
			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlInfermiere1Txt.m_strRicercaView);
			else
				DDX_FieldInfermieriEdit(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lInfermiere1, m_pEsamiView->m_pEsamiSet);

			break;
		}
		case cmb_infermiere2:
		{
			DDX_Control(pDX, IDC_COMBO, m_ctrlInfermiere2);
			DDX_Control(pDX, IDC_EDIT, m_ctrlInfermiere2Txt);

			DDX_FieldInfermieriCombo(pDX, IDC_COMBO, m_pEsamiView->m_pEsamiSet->m_lInfermiere2, m_pEsamiView->m_pEsamiSet);
			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlInfermiere2Txt.m_strRicercaView);
			else
				DDX_FieldInfermieriEdit(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lInfermiere2, m_pEsamiView->m_pEsamiSet);

			break;
		}
		case cmb_complicanzeimmediate:
		{
			DDX_Control(pDX, IDC_COMBO, m_ctrlComplicanzeImmediate);
			DDX_Control(pDX, IDC_EDIT, m_ctrlComplicanzeImmediateTxt);

			CComboComplicanzeSet setTemp(FALSE); // immediate //

			DDX_FieldComboTransCombo(pDX, IDC_COMBO, m_pEsamiView->m_pEsamiSet->m_lIDComplicanzeImmediate, m_pEsamiView->m_pEsamiSet, (CComboTransSet*)&setTemp);
			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlComplicanzeImmediateTxt.m_strRicercaView);
			else
				DDX_FieldComboTransEdit(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lIDComplicanzeImmediate, m_pEsamiView->m_pEsamiSet, (CComboTransSet*)&setTemp);

			break;
		}
		case cmb_complicanzetardive:
		{
			DDX_Control(pDX, IDC_COMBO, m_ctrlComplicanzeTardive);
			DDX_Control(pDX, IDC_EDIT, m_ctrlComplicanzeTardiveTxt);

			CComboComplicanzeSet setTemp(TRUE); // tardive //

			DDX_FieldComboTransCombo(pDX, IDC_COMBO, m_pEsamiView->m_pEsamiSet->m_lIDComplicanzeTardive, m_pEsamiView->m_pEsamiSet, (CComboTransSet*)&setTemp);
			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlComplicanzeTardiveTxt.m_strRicercaView);
			else
				DDX_FieldComboTransEdit(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lIDComplicanzeTardive, m_pEsamiView->m_pEsamiSet, (CComboTransSet*)&setTemp);

			break;
		}
		case cmb_pulizia:
		{
			DDX_Control(pDX, IDC_COMBO, m_ctrlPulizia);
			DDX_Control(pDX, IDC_EDIT, m_ctrlPuliziaTxt);

			CComboPuliziaSet setTemp;

			DDX_FieldComboTransCombo(pDX, IDC_COMBO, m_pEsamiView->m_pEsamiSet->m_lIDPulizia, m_pEsamiView->m_pEsamiSet, (CComboTransSet*)&setTemp);
			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlPuliziaTxt.m_strRicercaView);
			else
				DDX_FieldComboTransEdit(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lIDPulizia, m_pEsamiView->m_pEsamiSet, (CComboTransSet*)&setTemp);

			break;
		}
		case cmb_causenoncompletamento:
		{
			DDX_Control(pDX, IDC_COMBO, m_ctrlCauseNonCompletamento);
			DDX_Control(pDX, IDC_EDIT, m_ctrlCauseNonCompletamentoTxt);

			CComboCauseNonCompletamentoSet setTemp;

			DDX_FieldComboTransCombo(pDX, IDC_COMBO, m_pEsamiView->m_pEsamiSet->m_lIDCausaNonCompleto, m_pEsamiView->m_pEsamiSet, (CComboTransSet*)&setTemp);
			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlCauseNonCompletamentoTxt.m_strRicercaView);
			else
				DDX_FieldComboTransEdit(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lIDCausaNonCompleto, m_pEsamiView->m_pEsamiSet, (CComboTransSet*)&setTemp);

			break;
		}
		case cmb_tolleranza:
		{
			DDX_Control(pDX, IDC_COMBO, m_ctrlTolleranza);
			DDX_Control(pDX, IDC_EDIT, m_ctrlTolleranzaTxt);

			CComboTolleranzaSet setTemp;

			DDX_FieldComboTransCombo(pDX, IDC_COMBO, m_pEsamiView->m_pEsamiSet->m_lIDTolleranza, m_pEsamiView->m_pEsamiSet, (CComboTransSet*)&setTemp);
			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlTolleranzaTxt.m_strRicercaView);
			else
				DDX_FieldComboTransEdit(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lIDTolleranza, m_pEsamiView->m_pEsamiSet, (CComboTransSet*)&setTemp);

			break;
		}
		case cmb_conclusioniscreening:
		{
			DDX_Control(pDX, IDC_COMBO, m_ctrlConclusioniScreening);
			DDX_Control(pDX, IDC_EDIT, m_ctrlConclusioniScreeningTxt);

			CComboConclusioniScreeningSet setTemp;

			DDX_FieldComboTransCombo(pDX, IDC_COMBO, m_pEsamiView->m_pEsamiSet->m_lIDConclusioniScreening, m_pEsamiView->m_pEsamiSet, (CComboTransSet*)&setTemp);
			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlConclusioniScreeningTxt.m_strRicercaView);
			else
				DDX_FieldComboTransEdit(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lIDConclusioniScreening, m_pEsamiView->m_pEsamiSet, (CComboTransSet*)&setTemp);

			break;
		}
		case cmb_conclusionicolon:
		{
			DDX_Control(pDX, IDC_COMBO, m_ctrlConclusioniColon);
			DDX_Control(pDX, IDC_EDIT, m_ctrlConclusioniColonTxt);

			CComboConclusioniColonSet setTemp;

			DDX_FieldComboTransCombo(pDX, IDC_COMBO, m_pEsamiView->m_pEsamiSet->m_lIDConclusioniColon, m_pEsamiView->m_pEsamiSet, (CComboTransSet*)&setTemp);
			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlConclusioniColonTxt.m_strRicercaView);
			else
				DDX_FieldComboTransEdit(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lIDConclusioniColon, m_pEsamiView->m_pEsamiSet, (CComboTransSet*)&setTemp);

			break;
		}
		case cmb_diagnosifinale:
		{
			DDX_Control(pDX, IDC_COMBO, m_ctrlDiagnosiFinale);
			DDX_Control(pDX, IDC_EDIT, m_ctrlDiagnosiFinaleTxt);

			CComboDiagnosiFinaleSet setTemp;

			DDX_FieldComboTransCombo(pDX, IDC_COMBO, m_pEsamiView->m_pEsamiSet->m_lIDDiagnosiFinale, m_pEsamiView->m_pEsamiSet, (CComboTransSet*)&setTemp);
			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlDiagnosiFinaleTxt.m_strRicercaView);
			else
				DDX_FieldComboTransEdit(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lIDDiagnosiFinale, m_pEsamiView->m_pEsamiSet, (CComboTransSet*)&setTemp);

			break;
		}
		case cmb_altreanomalie:
		{
			DDX_Control(pDX, IDC_COMBO, m_ctrlAltreAnomalie);
			DDX_Control(pDX, IDC_EDIT, m_ctrlAltreAnomalieTxt);

			CComboAltreAnomalieSet setTemp;

			DDX_FieldComboTransCombo(pDX, IDC_COMBO, m_pEsamiView->m_pEsamiSet->m_lIDAltreAnomalie, m_pEsamiView->m_pEsamiSet, (CComboTransSet*)&setTemp);
			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				DDX_Text(pDX, IDC_EDIT, m_ctrlPuliziaTxt.m_strRicercaView);
			else
				DDX_FieldComboTransEdit(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_lIDAltreAnomalie, m_pEsamiView->m_pEsamiSet, (CComboTransSet*)&setTemp);

			break;
		}
		case cmb_esameurgente:
		{
			DDX_Control(pDX, IDC_COMBO, m_ctrlEsameUrgente);

			if (pDX->m_bSaveAndValidate)
			{
				m_pEsamiView->m_pEsamiSet->m_lLivelloUrgenza = m_ctrlEsameUrgente.GetCurSel();
			}
			else
			{
				if ((m_pEsamiView->m_pEsamiSet->m_lLivelloUrgenza < 0) || (m_pEsamiView->m_pEsamiSet->m_lLivelloUrgenza > 1))
					m_pEsamiView->m_pEsamiSet->m_lLivelloUrgenza = 0;

				m_ctrlEsameUrgente.SetCurSel(m_pEsamiView->m_pEsamiSet->m_lLivelloUrgenza);
			}

			break;
		}
	}
}

BOOL CComboDynForm1::OnInitDialog()
{
	CEndoxDynForm::OnInitDialog();

	AddAnchor(GetDlgItem(IDC_TEXT)->GetSafeHwnd(), CSize(0,50), CSize(100,50));
	AddAnchor(GetDlgItem(IDC_COMBO)->GetSafeHwnd(), CSize(0,50), CSize(100,50));
	AddAnchor(GetDlgItem(IDC_EDIT)->GetSafeHwnd(), CSize(0,50), CSize(100,50));

	switch(m_lContenuto)
	{
		case cmb_tipoesame:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_CMB_TIPOESAME));
			m_ctrlTipoEsame.SetParam(m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDEsame);
			m_ctrlTipoEsameTxt.SetParam(this, m_pEsamiView->m_pEsamiSet);
			break;
		}
		case cmb_medico1:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_CMB_MEDICO));
			m_ctrlMedicoTxt.SetParam(this, m_pEsamiView->m_pEsamiSet);
			break;
		}
		case cmb_medico2:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_CMB_ASSISTENTE));
			m_ctrlAssistenteTxt.SetParam(this, m_pEsamiView->m_pEsamiSet);
			break;
		}
		case cmb_infermiere1:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_CMB_INFERMIERE1));
			m_ctrlInfermiere1Txt.SetParam(this, m_pEsamiView->m_pEsamiSet);
			break;
		}
		case cmb_infermiere2:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_CMB_INFERMIERE2));
			m_ctrlInfermiere2Txt.SetParam(this, m_pEsamiView->m_pEsamiSet);
			break;
		}
		case cmb_complicanzeimmediate:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_CMB_COMPLICANZEIMMEDIATE));
			m_ctrlComplicanzeImmediate.SetParam(m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDComplicanzeImmediate, (CComboTransSet*)&m_setComboComplicanzeImmediate);
			m_ctrlComplicanzeImmediateTxt.SetParam(this, (CComboTransSet*)&m_setComboComplicanzeImmediate, m_pEsamiView->m_pEsamiSet, m_pEsamiView);
			break;
		}
		case cmb_complicanzetardive:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_CMB_COMPLICANZETARDIVE));
			m_ctrlComplicanzeTardive.SetParam(m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDComplicanzeTardive, (CComboTransSet*)&m_setComboComplicanzeTardive);
			m_ctrlComplicanzeTardiveTxt.SetParam(this, (CComboTransSet*)&m_setComboComplicanzeTardive, m_pEsamiView->m_pEsamiSet, m_pEsamiView);
			break;
		}
		case cmb_pulizia:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_CMB_PULIZIA));
			m_ctrlPulizia.SetParam(m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDPulizia, (CComboTransSet*)&m_setComboPulizia);
			m_ctrlPuliziaTxt.SetParam(this, (CComboTransSet*)&m_setComboPulizia, m_pEsamiView->m_pEsamiSet, m_pEsamiView);
			break;
		}
		case cmb_causenoncompletamento:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_CMB_CAUSENONCOMPLETAMENTO));
			m_ctrlCauseNonCompletamento.SetParam(m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDCausaNonCompleto, (CComboTransSet*)&m_setComboCauseNonCompletamento);
			m_ctrlCauseNonCompletamentoTxt.SetParam(this, (CComboTransSet*)&m_setComboCauseNonCompletamento, m_pEsamiView->m_pEsamiSet, m_pEsamiView);
			break;
		}
		case cmb_tolleranza:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_CMB_TOLLERANZA));
			m_ctrlTolleranza.SetParam(m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDTolleranza, (CComboTransSet*)&m_setComboTolleranza);
			m_ctrlTolleranzaTxt.SetParam(this, (CComboTransSet*)&m_setComboTolleranza, m_pEsamiView->m_pEsamiSet, m_pEsamiView);
			break;
		}
		case cmb_conclusioniscreening:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_CMB_CONCLUSIONISCREENING));
			m_ctrlConclusioniScreening.SetParam(m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDConclusioniScreening, (CComboTransSet*)&m_setComboConclusioniScreening);
			m_ctrlConclusioniScreeningTxt.SetParam(this, (CComboTransSet*)&m_setComboConclusioniScreening, m_pEsamiView->m_pEsamiSet, m_pEsamiView);
			break;
		}
		case cmb_conclusionicolon:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_CMB_CONCLUSIONICOLON));
			m_ctrlConclusioniColon.SetParam(m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDConclusioniColon, (CComboTransSet*)&m_setComboConclusioniColon);
			m_ctrlConclusioniColonTxt.SetParam(this, (CComboTransSet*)&m_setComboConclusioniColon, m_pEsamiView->m_pEsamiSet, m_pEsamiView);
			break;
		}
		case cmb_diagnosifinale:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_CMB_DIAGNOSIFINALE));
			m_ctrlDiagnosiFinale.SetParam(m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDDiagnosiFinale, (CComboTransSet*)&m_setComboDiagnosiFinale);
			m_ctrlDiagnosiFinaleTxt.SetParam(this, (CComboTransSet*)&m_setComboDiagnosiFinale, m_pEsamiView->m_pEsamiSet, m_pEsamiView);
			break;
		}
		case cmb_altreanomalie:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_CMB_ALTREANOMALIE));
			m_ctrlAltreAnomalie.SetParam(m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDAltreAnomalie, (CComboTransSet*)&m_setComboAltreAnomalie);
			m_ctrlAltreAnomalieTxt.SetParam(this, (CComboTransSet*)&m_setComboAltreAnomalie, m_pEsamiView->m_pEsamiSet, m_pEsamiView);
			break;
		}
		case cmb_esameurgente:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_CMB_ESAMEURGENTE));
			m_ctrlEsameUrgente.InsertString(0, theApp.GetMessageString(IDS_ESAME_NONURGENTE));
			// m_ctrlEsameUrgente.SetItemData(0, 0);
			m_ctrlEsameUrgente.InsertString(1, theApp.GetMessageString(IDS_ESAME_URGENTE));
			// m_ctrlEsameUrgente.SetItemData(1, 1);
			m_ctrlEsameUrgente.SetCurSel(0);
			break;
		}
	}

	return TRUE;
}

LRESULT CComboDynForm1::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CComboDynForm1::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	m_ctrlMedicoTxt.m_strRicercaView.Empty(); // Marvel Carvalho - BUG 4163 - adicionar botão LIMPAR para o campo Medico1
	return UpdateData(FALSE);
}

LRESULT CComboDynForm1::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	switch(m_lContenuto)
	{
		case cmb_tipoesame:		
		case cmb_medico2:
		case cmb_infermiere1:
		case cmb_infermiere2:
		case cmb_complicanzeimmediate:
		case cmb_complicanzetardive:
		case cmb_pulizia:
		case cmb_causenoncompletamento:
		case cmb_tolleranza:
		case cmb_conclusioniscreening:
		case cmb_conclusionicolon:
		case cmb_diagnosifinale:
		case cmb_altreanomalie:
		{
			BOOL bShowCombo = !(BOOL)wParam;

			// Sandro 05/06/2015 // problema in ricerca... //

			if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
				bShowCombo = FALSE;

			//

			if (bShowCombo)
			{
				GetDlgItem(IDC_COMBO)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_EDIT)->ShowWindow(SW_HIDE);
			}
			else
			{
				GetDlgItem(IDC_COMBO)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT)->ShowWindow(SW_SHOW);
				SendDlgItemMessage(IDC_EDIT, EM_SETREADONLY, wParam, lParam);
			}

			break;
		}
		case cmb_medico1:
		{
			GetDlgItem(IDC_COMBO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT)->ShowWindow(SW_SHOW);
			SendDlgItemMessage(IDC_EDIT, EM_SETREADONLY, wParam, lParam);		
			break;
		}
		case cmb_esameurgente:
		{
			GetDlgItem(IDC_COMBO)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT)->ShowWindow(SW_HIDE);

			m_ctrlEsameUrgente.EnableWindow(!(BOOL)wParam);

			break;
		}
	}

	return 1;
}

LRESULT CComboDynForm1::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	switch(m_lContenuto)
	{
		case cmb_tipoesame:
		{
			m_ctrlTipoEsameTxt.m_strRicerca = "";
			m_ctrlTipoEsameTxt.m_strRicercaView = "";
			break;
		}
		case cmb_medico1:
		{
			m_ctrlMedicoTxt.m_strRicerca = "";
			m_ctrlMedicoTxt.m_strRicercaView = "";
			break;
		}
		case cmb_medico2:
		{
			m_ctrlAssistenteTxt.m_strRicerca = "";
			m_ctrlAssistenteTxt.m_strRicercaView = "";
			break;
		}
		case cmb_infermiere1:
		{
			m_ctrlInfermiere1Txt.m_strRicerca = "";
			m_ctrlInfermiere1Txt.m_strRicercaView = "";
			break;
		}
		case cmb_infermiere2:
		{
			m_ctrlInfermiere2Txt.m_strRicerca = "";
			m_ctrlInfermiere2Txt.m_strRicercaView = "";
			break;
		}

		//Ma funziona sta roba sotto??? non penso
		case cmb_complicanzeimmediate:
		case cmb_complicanzetardive:
		case cmb_pulizia:
		case cmb_causenoncompletamento:
		case cmb_tolleranza:
		case cmb_conclusioniscreening:
		case cmb_conclusionicolon:
		case cmb_diagnosifinale:
		case cmb_altreanomalie:
		{
			m_ctrlComplicanzeTardiveTxt.m_strRicerca = "";
			m_ctrlComplicanzeTardiveTxt.m_strRicercaView = "";
			break;
		}
		case cmb_esameurgente:
		{
			break;
		}
	}

	return 1;
}

LRESULT CComboDynForm1::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT CComboDynForm1::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	switch(m_lContenuto)
	{
		case cmb_tipoesame:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlTipoEsameTxt.m_strRicerca, "EEsami.IdEsame", TRUE, TRUE);
			break;
		}
		case cmb_medico1:
		{
			// Luiz - 19/06/2019 - P3 - Melhoria do processo de busca
			if (m_ctrlMedicoTxt.m_strRicerca != "" && m_ctrlMedicoTxt.m_strRicerca != "-1")
			{
				ComponiRicercaEx(pStrWhere, m_ctrlMedicoTxt.m_strRicerca, "EEsami.Medico", TRUE, TRUE);
			}
			break;
		}
		case cmb_medico2:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlAssistenteTxt.m_strRicerca, "EEsami.Assistente", TRUE, TRUE);
			break;
		}
		case cmb_infermiere1:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlInfermiere1Txt.m_strRicerca, "EEsami.Infermiere1", TRUE, TRUE);
			break;
		}
		case cmb_infermiere2:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlInfermiere2Txt.m_strRicerca, "EEsami.Infermiere2", TRUE, TRUE);
			break;
		}
		case cmb_complicanzeimmediate:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlComplicanzeImmediateTxt.m_strRicerca, "EEsami.IDComplicanzeImmediate", TRUE, TRUE);
			break;
		}
		case cmb_complicanzetardive:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlComplicanzeTardiveTxt.m_strRicerca, "EEsami.IDComplicanzeTardive", TRUE, TRUE);
			break;
		}
		case cmb_pulizia:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlPuliziaTxt.m_strRicerca, "EEsami.IDPulizia", TRUE, TRUE);
			break;
		}
		case cmb_causenoncompletamento:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlCauseNonCompletamentoTxt.m_strRicerca, "EEsami.IDCausaNonCompleto", TRUE, TRUE);
			break;
		}
		case cmb_tolleranza:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlTolleranzaTxt.m_strRicerca, "EEsami.IDTolleranza", TRUE, TRUE);
			break;
		}
		case cmb_conclusioniscreening:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlConclusioniScreeningTxt.m_strRicerca, "EEsami.IDConclusioniScreening", TRUE, TRUE);
			break;
		}
		case cmb_conclusionicolon:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlConclusioniColonTxt.m_strRicerca, "EEsami.IDConclusioniColon", TRUE, TRUE);
			break;
		}
		case cmb_diagnosifinale:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlDiagnosiFinaleTxt.m_strRicerca, "EEsami.IDDiagnosiFinale", TRUE, TRUE);
			break;
		}
		case cmb_altreanomalie:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlAltreAnomalieTxt.m_strRicerca, "EEsami.IDAltreAnomalie", TRUE, TRUE);
			break;
		}
		case cmb_esameurgente:
		{
			ComponiRicercaLong(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lLivelloUrgenza, "EEsami.LivelloUrgenza", 0, "AND");
			break;
		}
	}

	return 1;
}

void CComboDynForm1::OnCbnSetfocusCombo()
{
	if (GetDlgItem(IDC_COMBO)->IsWindowVisible() == FALSE)
		GetDlgItem(IDC_EDIT)->SetFocus();
}

long CComboDynForm1::GetContenuto()
{
	return m_lContenuto;
}

BOOL CComboDynForm1::CampoObbligatorioValido()
{
	CComboBox* pCombo = NULL;
	switch(m_lContenuto)
	{
		case cmb_tipoesame:
		{
			pCombo = &m_ctrlTipoEsame;
			break;
		}
		case cmb_medico1:
		{
			pCombo = &m_ctrlMedico;
			break;
		}
		case cmb_medico2:
		{
			pCombo = &m_ctrlAssistente;
			break;
		}
		case cmb_infermiere1:
		{
			pCombo = &m_ctrlInfermiere1;
			break;
		}
		case cmb_infermiere2:
		{
			pCombo = &m_ctrlInfermiere2;
			break;
		}
		case cmb_complicanzeimmediate:
		{
			pCombo = &m_ctrlComplicanzeImmediate;
			break;
		}
		case cmb_complicanzetardive:
		{
			pCombo = &m_ctrlComplicanzeTardive;
			break;
		}
		case cmb_pulizia:
		{
			pCombo = &m_ctrlPulizia;
			break;
		}
		case cmb_causenoncompletamento:
		{
			pCombo = &m_ctrlCauseNonCompletamento;
			break;
		}
		case cmb_tolleranza:
		{
			pCombo = &m_ctrlTolleranza;
			break;
		}
		case cmb_conclusioniscreening:
		{
			pCombo = &m_ctrlConclusioniScreening;
			break;
		}
		case cmb_conclusionicolon:
		{
			pCombo = &m_ctrlConclusioniColon;
			break;
		}
		case cmb_diagnosifinale:
		{
			pCombo = &m_ctrlDiagnosiFinale;
			break;
		}
		case cmb_altreanomalie:
		{
			pCombo = &m_ctrlAltreAnomalie;
			break;
		}
		case cmb_esameurgente:
		{
			pCombo = &m_ctrlEsameUrgente;
			break;
		}
	}

	if (pCombo != NULL)
	{
		int nIndex = pCombo->GetCurSel();
		if (nIndex >= 0)
		{
			CString strCombo;
			pCombo->GetLBText(nIndex, strCombo);
			if (!strCombo.IsEmpty())
				return TRUE;
		}
	}

	return FALSE;
}