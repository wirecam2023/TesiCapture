#include "stdafx.h"
#include "Endox.h"
#include "AnatomiaPatologicaTastiForm.h"

#include <io.h>

#include "DLL_Imaging\h\AMLogin.h"

#include "AlbumForm.h"
#include "AnatomiaPatologicaForm.h"
#include "APGroupNumberWaitingDlg.h"
#include "Common.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "ImmToPathoxDlg.h"
#include "MediciSet.h"
#include "RefertoForm.h"
#include "SediEsameSet.h"
#include "AnatomiaPatologicaRichiesteQueueSet.h"
#include "PsmLogSet.h"
#include "ProvenienzaSet.h"

//librerie per le chiamate http
#include <string>
#include <vector>
#include <iostream>
using namespace std;
#include <windows.h>
#include <wininet.h>
#include "WebForm\Web.h"
using namespace openutils;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAnatomiaPatologicaTastiForm::CAnatomiaPatologicaTastiForm(CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(CAnatomiaPatologicaTastiForm::IDD, pParent, pEsamiView)
{
	m_bReadOnly = TRUE;

	// m_lStato = STATO_TEMP; // Sandro 01/02/2013 - RAS 20130022 //
	m_sDataVerifica = "";
}

CAnatomiaPatologicaTastiForm::~CAnatomiaPatologicaTastiForm()
{
}

BEGIN_MESSAGE_MAP(CAnatomiaPatologicaTastiForm, CEndoxDynForm)
	ON_WM_CTLCOLOR()

	ON_BN_CLICKED(IDC_BTN_ANNULLA, OnBnClickedBtnAnnulla)
	ON_BN_CLICKED(IDC_BTN_INVIA, OnBnClickedBtnInvia)
	ON_BN_CLICKED(IDC_BTN_STAMPA, OnBnClickedBtnStampa)

	ON_BN_CLICKED(IDC_CHECK_VERIFICATO, OnBnClickedCheckVerificato)

	ON_CBN_SELCHANGE(IDC_COMBO_SPEDIRERITIRARE, OnCbnSelchangeComboSpedireRitirare)
END_MESSAGE_MAP()

void CAnatomiaPatologicaTastiForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_anatomiapatologicatasti] == NULL)
	{
		pEsamiView->m_pDynForm[sub_anatomiapatologicatasti] = new CAnatomiaPatologicaTastiForm(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_anatomiapatologicatasti] != NULL)
		{
			pEsamiView->m_pDynForm[sub_anatomiapatologicatasti]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_anatomiapatologicatasti]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_anatomiapatologicatasti]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_anatomiapatologicatasti]->CreateChildForm(CAnatomiaPatologicaTastiForm::IDD, pParent, rectFrame);
		}
	}
}

void CAnatomiaPatologicaTastiForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_ANNULLA, m_ctrlButtonAnnulla);
	DDX_Control(pDX, IDC_BTN_INVIA, m_ctrlButtonInvia);
	DDX_Control(pDX, IDC_BTN_STAMPA, m_ctrlButtonStampa);
	DDX_Control(pDX, IDC_CHECK_VERIFICATO, m_ctrlCheckVerificato);

	DDX_Control(pDX, IDC_COMBO_MEDICO, m_ctrlComboMedico);
	DDX_Control(pDX, IDC_COMBO_SPEDIRERITIRARE, m_ctrlComboSpedireRitirare);

	DDX_Control(pDX, IDC_EDIT_INDIRIZZO, m_ctrlEditIndirizzo);

	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC_04, m_ctrlStatic4);

	DDX_Control(pDX, IDC_STATIC_05, m_ctrlStatic5);
	DDX_Control(pDX, IDC_STATIC_STATO, m_ctrlStaticStato);

	///

	DDX_Check(pDX, IDC_CHECK_VERIFICATO, m_pEsamiView->m_pEsamiSet->m_bAPVerificato);

	//
	DDX_CBIndex(pDX, IDC_COMBO_SPEDIRERITIRARE, m_pEsamiView->m_pEsamiSet->m_nAPSpedireRitirare);

	DDX_Text(pDX, IDC_EDIT_INDIRIZZO, m_pEsamiView->m_pEsamiSet->m_sAPIndirizzo);

	if (!pDX->m_bSaveAndValidate)
	{
		m_sDataVerifica = m_pEsamiView->m_pEsamiSet->m_sAPDataVerificato;
		m_sDataVerifica.Trim();

		m_sDataSpedRit = m_pEsamiView->m_pEsamiSet->m_sAPDataSpeditoRitirato;
		m_sDataSpedRit.Trim();

		CString strTemp = "";
		if (!m_sDataVerifica.IsEmpty())
		{
			if (m_sDataSpedRit.IsEmpty())
				strTemp = theApp.GetMessageString(IDS_ANATOMIAPATOLOGICATASTI_MSG2) + " " + m_sDataVerifica;
			else
				strTemp = theApp.GetMessageString(IDS_ANATOMIAPATOLOGICATASTI_MSG2) + " " + m_sDataVerifica + "\n" + theApp.GetMessageString(IDS_ANATOMIAPATOLOGICATASTI_MSG1) + " " + m_sDataSpedRit;
		}
		else
		{
			if (!m_sDataSpedRit.IsEmpty())
				strTemp = theApp.GetMessageString(IDS_ANATOMIAPATOLOGICATASTI_MSG1) + " " + m_sDataSpedRit;
		}
		m_ctrlStatic5.SetWindowText(strTemp);

		m_ctrlStaticStato.SetWindowText(GetStatoText(m_pEsamiView->m_pEsamiSet->m_lAPStato));

		// Sandro 09/11/2010 // Imposto come default che il medico che verifica l'esame è il medico che esegue l'esame //
		if (m_pEsamiView->m_pEsamiSet->m_nAPVerificatoMedico <= 0)
			m_pEsamiView->m_pEsamiSet->m_nAPVerificatoMedico = m_pEsamiView->m_pEsamiSet->m_lMedico;

		BOOL bFound = FALSE;
		for(int i = 0; i < m_ctrlComboMedico.GetCount(); i++)
		{
			if ((long)m_ctrlComboMedico.GetItemData(i) == m_pEsamiView->m_pEsamiSet->m_nAPVerificatoMedico)
			{
				m_ctrlComboMedico.SetCurSel(i);
				bFound = TRUE;
				break;
			}
		}
		if (!bFound)
			m_ctrlComboMedico.SetCurSel(-1);
	}
	else
	{
		int nCurSel = m_ctrlComboMedico.GetCurSel();
		if (nCurSel > 0)
			m_pEsamiView->m_pEsamiSet->m_nAPVerificatoMedico = m_ctrlComboMedico.GetItemData(nCurSel);
		else
			m_pEsamiView->m_pEsamiSet->m_nAPVerificatoMedico = 0;

		m_pEsamiView->m_pEsamiSet->m_sAPDataVerificato = m_sDataVerifica;
	}

	///

	OnFormReadOnly((WPARAM)m_bReadOnly, (LPARAM)0);
}

HBRUSH CAnatomiaPatologicaTastiForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor (pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_01:
		case IDC_STATIC_02:
		case IDC_STATIC_03:
		case IDC_STATIC_04:
		case IDC_STATIC_05:
		case IDC_STATIC_STATO:
		case IDC_COMBO_SPEDIRERITIRARE:
		case IDC_EDIT_INDIRIZZO:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

BOOL CAnatomiaPatologicaTastiForm::OnInitDialog() 
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_STATIC_01, CSize(0,50), CSize(30,50));
	AddAnchor(IDC_STATIC_STATO, CSize(0,50), CSize(30,50));

	AddAnchor(IDC_STATIC_03, CSize(30,50), CSize(60,50));
	AddAnchor(IDC_CHECK_VERIFICATO, CSize(60,50), CSize(60,50));
	AddAnchor(IDC_COMBO_MEDICO, CSize(30,50), CSize(60,50));

	AddAnchor(IDC_STATIC_05, CSize(60,50), CSize(100,50));
	AddAnchor(IDC_BTN_ANNULLA, CSize(60,50), CSize(80,50));
	AddAnchor(IDC_BTN_INVIA, CSize(60,50), CSize(80,50));
	AddAnchor(IDC_BTN_STAMPA, CSize(80,50), CSize(100,50));

	AddAnchor(IDC_STATIC_02, CSize(0,50), CSize(50,50));
	AddAnchor(IDC_COMBO_SPEDIRERITIRARE, CSize(0,50), CSize(50,50));

	AddAnchor(IDC_STATIC_04, CSize(50,50), CSize(100,50));
	AddAnchor(IDC_EDIT_INDIRIZZO, CSize(50,50), CSize(100,50));

	GetDlgItem(IDC_STATIC_STATO)->SetFont(&theApp.m_fontBold);

	// riempio la combo della spedizione //
	m_ctrlComboSpedireRitirare.AddString(theApp.GetMessageString(IDS_ANATOMIA_SPEDIRE));
	m_ctrlComboSpedireRitirare.AddString(theApp.GetMessageString(IDS_ANATOMIA_SPEDIREALTRO));
	m_ctrlComboSpedireRitirare.AddString(theApp.GetMessageString(IDS_ANATOMIA_RITIRO));

	// riempio la combo dei medici //
	m_ctrlComboMedico.ResetContent();
	m_ctrlComboMedico.InsertString(0, "");
	m_ctrlComboMedico.SetItemData(0, 0);

	CMediciSet setMedici;
	if (theApp.m_bPersonalizzazioniBrasileEinstein)
		setMedici.SetSortRecord("Nome, Cognome");
	else
		setMedici.SetSortRecord("Cognome, Nome");
	if (setMedici.OpenRecordset("CAnatomiaPatologicaTastiForm::OnInitDialog"))
	{
		int nIndex = 1;

		while(!setMedici.IsEOF())
		{
			// Luiz - 24/06/2019 - P3 - Personalização da apresentação de nome de médico solicitante
			if (theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
				m_ctrlComboMedico.InsertString(nIndex, setMedici.m_sNome.Trim() + " " + setMedici.m_sCognome.Trim());
			else
				m_ctrlComboMedico.InsertString(nIndex, setMedici.m_sCognome.Trim() + " " + setMedici.m_sNome.Trim());
			
			m_ctrlComboMedico.SetItemData(nIndex, setMedici.m_lContatore);
			nIndex++;
			setMedici.MoveNext();
		}

		setMedici.CloseRecordset("CAnatomiaPatologicaTastiForm::OnInitDialog");
	}

	theApp.LocalizeDialog(this, CAnatomiaPatologicaTastiForm::IDD, "AnatomiaPatologicaTastiForm");
	return bReturn;
}

long CAnatomiaPatologicaTastiForm::GetContenuto()
{
	return sub_anatomiapatologicatasti;
}

BOOL CAnatomiaPatologicaTastiForm::CampoObbligatorioValido()
{
	BOOL bReturn = TRUE;

	if (m_pEsamiView->m_pDynForm[sub_anatomiapatologica] != NULL)
	{
		CAnatomiaPatologicaForm* pForm = (CAnatomiaPatologicaForm*)m_pEsamiView->m_pDynForm[sub_anatomiapatologica];
		if (pForm->GetNumRows() > 0) // esiste almeno una riga //
		{
			if ((m_pEsamiView->m_pEsamiSet->m_lAPStato == STATO_TEMP) || (m_pEsamiView->m_pEsamiSet->m_lAPStato == STATO_ANNULLATA) || (m_pEsamiView->m_pEsamiSet->m_lAPStato == STATO_SCARTATA))
				bReturn = FALSE;
		}
	}

	return bReturn;
}

LRESULT CAnatomiaPatologicaTastiForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	/* Sandro 03/08/2015
	if ((m_pEsamiView->m_pEsamiSet->m_bLocked == TRUE) && (m_lIDFaseBlocco <= 0)) // Davide - in ricerca m_bLocked è uguale a 2
		wParam = TRUE;

	if ((m_pEsamiView->m_pEsamiSet->m_bSuperLocked == TRUE) && (m_lIDFaseBlocco <= 1)) // Sandro // in ricerca m_bSuperLocked è uguale a 2 //
		wParam = TRUE;
	*/

	m_bReadOnly = (BOOL)wParam;

	// Simone - 03/05/2012 - La richiesta può essere annullata fino a che non viene importata nel softwware di anatomia
	m_ctrlButtonAnnulla.ShowWindow((m_pEsamiView->m_pEsamiSet->m_lAPStato == STATO_PRENOTATA || m_pEsamiView->m_pEsamiSet->m_lAPStato == STATO_ACQUISITA) ? SW_SHOW : SW_HIDE);
	m_ctrlButtonAnnulla.EnableWindow(m_bReadOnly && (m_pEsamiView->m_bEsamiValid) && (!m_pEsamiView->m_bPazientiBusy));

	m_ctrlButtonInvia.ShowWindow(((m_pEsamiView->m_pEsamiSet->m_lAPStato == STATO_TEMP) || (m_pEsamiView->m_pEsamiSet->m_lAPStato == STATO_ANNULLATA) || (m_pEsamiView->m_pEsamiSet->m_lAPStato == STATO_SCARTATA)) ? SW_SHOW : SW_HIDE);
	m_ctrlButtonInvia.EnableWindow(m_bReadOnly && (m_pEsamiView->m_bEsamiValid) && (!m_pEsamiView->m_bPazientiBusy) && m_pEsamiView->m_pEsamiSet->m_bStessoDistretto);

	m_ctrlButtonStampa.EnableWindow(m_bReadOnly && (m_pEsamiView->m_bEsamiValid) && (!m_pEsamiView->m_bPazientiBusy)/* && m_bRefertoVerificato */  && m_pEsamiView->m_pEsamiSet->m_bStessoDistretto);

	m_ctrlCheckVerificato.EnableWindow(!m_bReadOnly);

	m_ctrlComboMedico.ShowWindow(m_pEsamiView->m_pEsamiSet->m_bAPVerificato ? SW_SHOW : SW_HIDE);
	m_ctrlComboMedico.EnableWindow(!m_bReadOnly);

	m_ctrlComboSpedireRitirare.EnableWindow(!m_bReadOnly);

	m_ctrlEditIndirizzo.ShowWindow(m_pEsamiView->m_pEsamiSet->m_nAPSpedireRitirare == 1 ? SW_SHOW : SW_HIDE);
	m_ctrlEditIndirizzo.EnableWindow(!m_bReadOnly);

	m_ctrlStatic4.ShowWindow(m_pEsamiView->m_pEsamiSet->m_nAPSpedireRitirare == 1 ? SW_SHOW : SW_HIDE);

	// Sandro 03/08/2015 //
	if (((m_pEsamiView->m_pEsamiSet->m_bLocked == TRUE) && (m_lIDFaseBlocco <= 0)) || ((m_pEsamiView->m_pEsamiSet->m_bSuperLocked == TRUE) && (m_lIDFaseBlocco <= 1)))
	{
		m_ctrlButtonAnnulla.EnableWindow(FALSE);
		m_ctrlButtonInvia.EnableWindow(FALSE);
		m_ctrlButtonStampa.EnableWindow(FALSE);
		m_ctrlCheckVerificato.EnableWindow(FALSE);
		m_ctrlComboMedico.EnableWindow(FALSE);
		m_ctrlComboSpedireRitirare.EnableWindow(FALSE);
	}
	//

	return 1;
}

void CAnatomiaPatologicaTastiForm::OnBnClickedBtnAnnulla()
{
	m_ctrlButtonAnnulla.SetCheck(BST_UNCHECKED);

	if (m_pEsamiView->m_pEsamiSet != NULL)
	{
		if (!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore))
		{
			// Sandro 01/02/2013 - RAS 20130022 //
			m_pEsamiView->m_pEsamiSet->RefreshRecordset();

			//
			if (m_pEsamiView->m_pEsamiSet->m_lAPStato == STATO_PRENOTATA)
			{
				if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ANATPAT_REQUESTUNDO), MB_YESNO | MB_ICONSTOP) == IDYES)
				{
					CTime timeNow = CTime::GetCurrentTime();

					if (m_pEsamiView->m_pEsamiSet->EditRecordset("CAnatomiaPatologicaTastiForm::OnBnClickedBtnAnnulla"))
					{
						m_pEsamiView->m_pEsamiSet->m_lAPStato = STATO_ANNULLATA;
						m_pEsamiView->m_pEsamiSet->m_sAPDataAnnullamento = timeNow.Format("%Y%m%d%H%M%S");
						m_pEsamiView->m_pEsamiSet->m_sAPOperAnnullamento = theApp.m_sUtenteLoggato;
						m_pEsamiView->m_pEsamiSet->m_sAPGroupNumber = "";

						m_pEsamiView->m_pEsamiSet->UpdateRecordsetAPStato("CAnatomiaPatologicaTastiForm::OnBnClickedBtnAnnulla", FALSE);

						//Inserisco una riga nella coda
						AnnullaRichiesta();
					}

					OnFormLoad(NULL, NULL);
					UpdateData(FALSE);
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ANATPAT_REQUESTUNDO_OK));

					if (m_pEsamiView->m_pDynForm[sub_anatomiapatologica] != NULL)
						m_pEsamiView->m_pDynForm[sub_anatomiapatologica]->SendMessage(MSG_FORM_READONLY, (WPARAM)m_bReadOnly);
					if (m_pEsamiView->m_pDynForm[edt_anatomiapatologicanote] != NULL)
						m_pEsamiView->m_pDynForm[edt_anatomiapatologicanote]->SendMessage(MSG_FORM_READONLY, (WPARAM)m_bReadOnly);
				}
			}
			else
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ANATPAT_REQUESTUNDO_NOTPOSSIBLE));
			}
		}
	}
}

void CAnatomiaPatologicaTastiForm::OnBnClickedBtnInvia()
{
	m_ctrlButtonInvia.SetCheck(BST_UNCHECKED);

	InviaRichiestaProc();
}

BOOL CAnatomiaPatologicaTastiForm::InviaRichiestaProc()
{
	BeginWaitCursor();

	long lError = IDS_ANATPAT_REQUESTSEND_ERROR4;
	if (m_pEsamiView->m_pEsamiSet != NULL)
	{
		if (!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lContatore))
		{
			// Sandro 01/02/2013 - RAS 20130022 //
			m_pEsamiView->m_pEsamiSet->RefreshRecordset();

			//
			if ((m_pEsamiView->m_pEsamiSet->m_lAPStato == STATO_TEMP) || (m_pEsamiView->m_pEsamiSet->m_lAPStato == STATO_ANNULLATA) || (m_pEsamiView->m_pEsamiSet->m_lAPStato == STATO_SCARTATA))
			{
				if (m_pEsamiView->m_pDynForm[sub_referto] != NULL)
				{
					CRefertoForm* pRefertoForm = (CRefertoForm*)m_pEsamiView->m_pDynForm[sub_referto];
					CString strReferto = pRefertoForm->m_ctrlTextControl.GetText();
					strReferto.Trim();

					if (!strReferto.IsEmpty())
					{
						if (m_pEsamiView->m_pDynForm[sub_anatomiapatologica] != NULL)
						{
							CAnatomiaPatologicaForm *pForm = (CAnatomiaPatologicaForm*)m_pEsamiView->m_pDynForm[sub_anatomiapatologica];

							if ((pForm != NULL) && (pForm->GetNumRows() > 0))
							{
								long lIDDegenza = (m_pEsamiView->m_pEsamiSet->m_lProvenienza == 0 ? m_pEsamiView->m_pEsamiSet->m_lTipoDegenzaInterno : m_pEsamiView->m_pEsamiSet->m_lTipoDegenzaEsterno);

								CTime timeNow = CTime::GetCurrentTime();

								BOOL bContinue = FALSE;
								switch (theApp.m_lInterfacciaPathox)
								{
								case 1:
								case 2:
								{
									if ((m_pEsamiView->m_pFormImmagini != NULL) && (m_pEsamiView->m_pFormImmagini->m_nMaxDiapo >= 0))
									{
										CImmToPathoxDlg dlg(this, m_pEsamiView);
										if (dlg.DoModal() == IDOK)
											bContinue = TRUE;
									}
									else
									{
										bContinue = TRUE;
									}
									break;
								}
								default:
								{
									bContinue = TRUE;
									break;
								}
								}

								if (bContinue)
								{
									BOOL bPSMRequired = CProvenienzaSet().PSMRequired(m_pEsamiView->m_pEsamiSet->m_lIdProvenienzaNew);

									if (m_pEsamiView->m_pEsamiSet->EditRecordset("CAnatomiaPatologicaTastiForm::OnBnClickedBtnInvia"))
									{
										if (theApp.m_bRicettaPerAP && theApp.m_bRicettaPerAP_psm && bPSMRequired && (m_pEsamiView->m_pEsamiSet->m_sRicovero == "0" || m_pEsamiView->m_pEsamiSet->m_sRicovero == "" || m_pEsamiView->m_pEsamiSet->m_sRicovero == "-1"))
											if (theApp.AfxMessageBoxEndo("La fascia contrattuale dell'esame richiederebbe l'emissione di una ricetta. L'esame, però, è stato accettato direttamente in Endox, quindi non verrà aperto PSM e le prestazioni di anatomia non saranno erogate al cup, procedere?", MB_YESNO) == IDNO)
											{
												m_pEsamiView->m_pEsamiSet->UpdateRecordset("CAnatomiaPatologicaTastiForm::OnBnClickedBtnInvia");
												UpdateData(FALSE);
												EndWaitCursor();
												return FALSE;
											}

										//Se mi serve la ricetta per AP metto il group number NULL, altrimenti lo genero alla vecchia maniera
										if (theApp.m_bRicettaPerAP && bPSMRequired)
										{
											if (theApp.m_bRicettaPerAP_psm && m_pEsamiView->m_pEsamiSet->m_sRicovero != "0" && m_pEsamiView->m_pEsamiSet->m_sRicovero != "" && m_pEsamiView->m_pEsamiSet->m_sRicovero != "-1")
												m_pEsamiView->m_pEsamiSet->SetFieldNull(&m_pEsamiView->m_pEsamiSet->m_sAPGroupNumber);
											else
											{
												m_pEsamiView->m_pEsamiSet->m_sAPGroupNumber.Format("ENDOX%li", m_pEsamiView->m_pEsamiSet->m_lContatore);
											}

										}
										else
										{
											m_pEsamiView->m_pEsamiSet->m_sAPGroupNumber.Format("ENDOX%li", m_pEsamiView->m_pEsamiSet->m_lContatore);
										}

										m_pEsamiView->m_pEsamiSet->m_lAPStato = STATO_PRENOTATA;
										m_pEsamiView->m_pEsamiSet->m_sAPDataInvio = timeNow.Format("%Y%m%d%H%M%S");
										m_pEsamiView->m_pEsamiSet->m_sAPOperInvio = theApp.m_sUtenteLoggato;

										if (theApp.m_bRicettaPerAP && theApp.m_bRicettaPerAP_psm && bPSMRequired && m_pEsamiView->m_pEsamiSet->m_sRicovero != "0" && m_pEsamiView->m_pEsamiSet->m_sRicovero != "" && m_pEsamiView->m_pEsamiSet->m_sRicovero != "-1")
											m_pEsamiView->m_pEsamiSet->UpdateRecordsetAPStato("CAnatomiaPatologicaTastiForm::OnBnClickedBtnInvia", TRUE);
										else
											m_pEsamiView->m_pEsamiSet->UpdateRecordsetAPStato("CAnatomiaPatologicaTastiForm::OnBnClickedBtnInvia", FALSE);

										//Inserisco una riga nella coda
										InviaRichiesta();

										//Apertura software Insiel per la gestione delle prescrizioni
										if (theApp.m_bRicettaPerAP && theApp.m_bRicettaPerAP_psm && bPSMRequired && m_pEsamiView->m_pEsamiSet->m_sRicovero != "0" && m_pEsamiView->m_pEsamiSet->m_sRicovero != "" && m_pEsamiView->m_pEsamiSet->m_sRicovero != "-1")
										{
											PSMGo();

											//Dialog di attesa
											if (CAPGroupNumberWaitingDlg(this, m_pEsamiView->m_pEsamiSet->m_lContatore).DoModal() == IDCANCEL)
											{
												//Se ho premuto annulla, riporto indietro i dati
												if (m_pEsamiView->m_pEsamiSet->EditRecordset("CAnatomiaPatologicaTastiForm::OnBnClickedBtnInvia"))
												{
													m_pEsamiView->m_pEsamiSet->m_lAPStato = -1;
													m_pEsamiView->m_pEsamiSet->SetFieldNull(&m_pEsamiView->m_pEsamiSet->m_sAPDataInvio);
													m_pEsamiView->m_pEsamiSet->SetFieldNull(&m_pEsamiView->m_pEsamiSet->m_sAPOperInvio);
													m_pEsamiView->m_pEsamiSet->SetFieldNull(&m_pEsamiView->m_pEsamiSet->m_sAPProvenienza);
													m_pEsamiView->m_pEsamiSet->SetFieldNull(&m_pEsamiView->m_pEsamiSet->m_sAPConvenzione);

													m_pEsamiView->m_pEsamiSet->UpdateRecordsetAPStato("CAnatomiaPatologicaTastiForm::OnBnClickedBtnInvia", FALSE);

													theApp.AfxMessageBoxEndo("ATTENZIONE!\r\n\r\nLa richiesta NON è stata inviata all'anatomia patologica!");
													return FALSE;
												}
											}
										}

									}
								}

								UpdateData(FALSE);

								if (m_pEsamiView->m_pDynForm[sub_anatomiapatologica] != NULL)
									m_pEsamiView->m_pDynForm[sub_anatomiapatologica]->UpdateData(FALSE);
								if (m_pEsamiView->m_pDynForm[edt_anatomiapatologicanote] != NULL)
									m_pEsamiView->m_pDynForm[edt_anatomiapatologicanote]->UpdateData(FALSE);

								lError = 0;
							}
							else
							{
								lError = IDS_ANATPAT_REQUESTSEND_ERROR3;
							}
						}
					}
					else
					{
						lError = IDS_ANATPAT_REQUESTSEND_ERROR1;
					}
				}
			}
			else
			{
				lError = IDS_ANATPAT_REQUESTSEND_ERROR2;
			}
		}
	}

	EndWaitCursor();

	if (lError > 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(lError));
		return FALSE;
	}

	return TRUE;
}

void CAnatomiaPatologicaTastiForm::OnBnClickedBtnStampa()
{
	m_ctrlButtonStampa.SetCheck(BST_UNCHECKED);
	long lPdfId = 0;
	m_pEsamiView->AnteprimaStampaReport(STAMPA, VERIFICA_NO, theApp.m_sEditRep + "\\ConsigliIstologico.rpa", FALSE, 1, &lPdfId,"");
}

void CAnatomiaPatologicaTastiForm::OnBnClickedCheckVerificato()
{
	// Sandro 09/11/2010 // Aggiungo anche la data di verifica //

	UpdateData(TRUE);

	if (m_pEsamiView->m_pEsamiSet->m_bAPVerificato)
	{
		CTime timeNow = CTime::GetCurrentTime();
		m_pEsamiView->m_pEsamiSet->m_sAPDataVerificato = timeNow.Format("%d/%m/%Y");
	}
	else
	{
		m_pEsamiView->m_pEsamiSet->m_sAPDataVerificato = "";
	}

	UpdateData(FALSE);
}

void CAnatomiaPatologicaTastiForm::OnCbnSelchangeComboSpedireRitirare()
{
	UpdateData(TRUE);
}

void CAnatomiaPatologicaTastiForm::InviaRichiesta()
{
	long userId;
	AMLogin_GetUserID(&userId);
	CAnatomiaPatologicaRichiesteQueueSet().InserisciRecord(m_pEsamiView->m_pEsamiSet->m_lContatore, userId, CAnatomiaPatologicaRichiesteQueueSet().INSERIMENTO);
}

void CAnatomiaPatologicaTastiForm::AnnullaRichiesta()
{
	long userId;
	AMLogin_GetUserID(&userId);
	CAnatomiaPatologicaRichiesteQueueSet().InserisciRecord(m_pEsamiView->m_pEsamiSet->m_lContatore, userId, CAnatomiaPatologicaRichiesteQueueSet().ANNULLAMENTO);
}

void CAnatomiaPatologicaTastiForm::PSMGo()
{
	CString gettone = "";

	/*
	try
	{
		//Chiamata per il recupero del gettone
		
#ifndef _DEBUG
		WebForm wf;
		wf.setHost(theApp.m_strPSMAmbulatorioIndirizzo);
		//wf.setScriptFile("/inail/frontController/frontController.jsp");
		wf.putVariable("helper", "integrazioneHelper");
		wf.putVariable("azione", "generaGettone");
		wf.sendRequest();

		wf.getResponse(gettone.GetBuffer(10240), 10240);
		gettone.ReleaseBuffer();
#else
		gettone = "<gettone>GETTONETEST</gettone>";
#endif

		//Controllo validità del gettone recuperato
		gettone.Replace("<gettone>", "");
		gettone.Replace("</gettone>", "");
		CString test = gettone;
		if (test == "" || test.MakeUpper().Find("<HTML>") >= 0)
		{
			theApp.AfxMessageBoxEndo("Errore nel recupero del token");
			theApp.AfxMessageBoxEndo(gettone);
		}
	}
	catch(WebFormException ex)
	{
		theApp.AfxMessageBoxEndo("impossibile richiamare l'applicativo PSM, controllare la validità dell'indirizzo");
		return;
	}*/

	//Avvio PSM
	CString url = "file://";
	url += theApp.m_sDirProg + "\\PsmProxy\\PSMProxy.html?";
	url += "helper=integrazioneHelper";
	url += "&azione=avviaAmbulatorio";
	
	url += "&operatore=" + theApp.m_sUtenteLoggato; //theApp.m_strPSMOperatore;
	url += "&workStation=anonymous";
	//url += "&unitaOrganizzativa=" + theApp.m_strPSMAmbulatorioUO; 
	url += "&unitaOrganizzativa=" + CSediEsameSet().GetCodicePresidio(theApp.m_lIDSedeEsameDefault);
	url += "&idAnagrafica=" + m_pEsamiView->m_pPazientiSet->m_sAssIden;
	url += "&tipoAnagrafica=UNIVERSALE";
	url += "&id_contatto=" + m_pEsamiView->m_pEsamiSet->m_sRicovero;
	//url += "&unitaOperativa=" + theApp.m_strPSMAmbulatorioUO;
	url += "&unitaOperativa=" + CSediEsameSet().GetCodicePresidio(theApp.m_lIDSedeEsameDefault);
	//url += "&gettone=" + gettone;

#ifdef _DEBUG
	theApp.AfxMessageBoxEndo(url);
#endif

	TCHAR path[3999];
	SHGetFolderPath( NULL, CSIDL_PROGRAM_FILES, NULL, 0, path );

	CPsmLogSet().InsertLog(m_pEsamiView->m_pPazientiSet->m_lContatore, m_pEsamiView->m_pEsamiSet->m_lContatore, m_pEsamiView->m_pEsamiSet->m_sRicovero, url);

	CString process;
	process.Format("\"%s\\Internet Explorer\\iexplore.exe\" %s", path, url);

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(NULL, process.GetBuffer(MAX_PATH), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
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

	process.ReleaseBuffer();
}