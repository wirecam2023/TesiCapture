#include "stdafx.h"
#include "Endox.h"
#include "RefertoForm.h"

#include "DLL_Imaging\h\AMLogin.h"

#include "ConiugazioneEsamiDlg.h"
#include "CupWorkListManager.h"
#include "CustomDate.h"
#include "EsamiIntegratiSet.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "PazientiSet.h"
#include "TipoEsameSet.h"
#include "VistaOtherFichaItemsSet.h"
#include "CodificaRegionaleExSet.h"
#include "EsamiPersonalizzabiliSet.h"
#include "ExtPrestazioniSet.h"
#include "ExtOrdiniSet.h" //Gabriel BUG 6225 - Lista DO FIX

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CRefertoForm::CRefertoForm(CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(CRefertoForm::IDD, pParent, pEsamiView)
{
	m_sTempDataOra = "";
	m_lTempRedattore = 0;
	m_bTempScaduto = FALSE;
	m_lTempStato = 0;
}

CRefertoForm::~CRefertoForm()
{
}

BEGIN_MESSAGE_MAP(CRefertoForm, CEndoxDynForm)
	ON_WM_SIZE()

	ON_MESSAGE(MSG_FORM_READONLY, OnFormReadOnly)

	// Julio Genomica
	ON_BN_CLICKED(IDC_BTN_REFERTO_SMALL, OnBnClickedBtnReferto)
	ON_BN_CLICKED(IDC_BTN_REFERTO_BIG, OnBnClickedBtnReferto)
	ON_BN_CLICKED(IDC_BTN_REFERTOGENOMICA, OnBnClickedBtnRefertoGenomica)
END_MESSAGE_MAP()

void CRefertoForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TEXTCONTROL, m_ctrlTextControl);
	m_ctrlTextControl.SendMessage(WM_USER + 1013, 1, 0); // così NON carica i font dalla stampante predefinita perché in certi casi dava RTF filter error... //
	
	// Julio Genomica
	if (theApp.m_bUsaModuloGenomica)
		DDX_Control(pDX, IDC_BTN_REFERTO_SMALL, m_ctrlButtonReferto);
	else
		DDX_Control(pDX, IDC_BTN_REFERTO_BIG, m_ctrlButtonReferto);

	DDX_Control(pDX, IDC_BTN_REFERTOGENOMICA, m_ctrlButtonRefertoGenomica);
	DDX_Control(pDX, IDC_STATIC_USER, m_ctrlStaticUser);

	if (pDX->m_bSaveAndValidate)
	{
		// dal controllo al recordset //

		m_ctrlTextControl.SetSelStart(0);
		m_ctrlTextControl.SetSelLength(-1);

		m_pEsamiView->m_pEsamiSet->m_sRefertoTestoTxt = m_ctrlTextControl.GetSelText();
		m_pEsamiView->m_pEsamiSet->m_sRefertoTestoTxt.Trim();

		if (!m_pEsamiView->m_pEsamiSet->m_sRefertoTestoTxt.IsEmpty())
			m_pEsamiView->m_pEsamiSet->m_sRefertoTestoRtf = m_ctrlTextControl.GetRTFSelText();

		// Sandro 14/09/2016 //

		m_pEsamiView->m_pEsamiSet->m_sRefertoTestoHtml = m_ctrlTextControl.GetHTMLSelText();

		//

		m_pEsamiView->m_pEsamiSet->m_sRefertoDataOra = m_sTempDataOra;
		m_pEsamiView->m_pEsamiSet->m_lRefertoRedattore = m_lTempRedattore;
		m_pEsamiView->m_pEsamiSet->m_bRefertoScaduto = m_bTempScaduto;
		m_pEsamiView->m_pEsamiSet->m_lRefertoStato = m_lTempStato;
	}
	else
	{
		// dal recordset al controllo //

		m_ctrlTextControl.ResetContents();

		if (!m_pEsamiView->m_pEsamiSet->m_sRefertoTestoRtf.IsEmpty())
		{
			m_ctrlTextControl.SetRTFSelText(m_pEsamiView->m_pEsamiSet->m_sRefertoTestoRtf);
		}
		else
		{
			if (!m_pEsamiView->m_pEsamiSet->m_sConclusioni.IsEmpty())
			{
				try
				{
					m_ctrlTextControl.SetRTFSelText(m_pEsamiView->m_pEsamiSet->m_sConclusioni);
				}
				catch (CException* pEx)
				{
					m_ctrlTextControl.SetText(m_pEsamiView->m_pEsamiSet->m_sConclusioni);
					pEx->Delete();
				}
			}
		}

		m_sTempDataOra = m_pEsamiView->m_pEsamiSet->m_sRefertoDataOra;
		m_lTempRedattore = m_pEsamiView->m_pEsamiSet->m_lRefertoRedattore;
		m_bTempScaduto = m_pEsamiView->m_pEsamiSet->m_bRefertoScaduto;
		m_lTempStato = m_pEsamiView->m_pEsamiSet->m_lRefertoStato;
	}

	if (!pDX->m_bSaveAndValidate)
	{
		BOOL bReadOnly = FALSE;

		if ((m_pEsamiView->m_pEsamiSet->m_bLocked == TRUE) && (m_lIDFaseBlocco <= 0)) // Davide - in ricerca m_bLocked è uguale a 2
			bReadOnly = TRUE;

		if ((m_pEsamiView->m_pEsamiSet->m_bSuperLocked == TRUE) && (m_lIDFaseBlocco <= 1)) // Sandro // in ricerca m_bSuperLocked è uguale a 2 //
			bReadOnly = TRUE;

		BOOL bRicerca = theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI || theApp.m_nProgramMode & FILTER_RECORD_ESAMI;

		// Sandro 24/07/2015 // RAS 20150046 //
		// GetDlgItem(IDC_BTN_REFERTO)->EnableWindow((theApp.m_dwPrivileges & AMLogin_Permissions::modify_report ? TRUE : FALSE) && (m_pEsamiView->m_bEsamiValid) && (!m_pEsamiView->m_bEsamiBusy) && (!m_pEsamiView->m_bPazientiBusy) && m_pEsamiView->m_pEsamiSet->m_bStessoDistretto && !readOnly);
		//Julio Genomica
		GetDlgItem(IDC_BTN_REFERTO_SMALL)->EnableWindow(!bRicerca && ((theApp.m_dwPrivileges & AMLogin_Permissions::modify_report ? TRUE : FALSE) && (m_pEsamiView->m_bEsamiValid) && (!m_pEsamiView->m_bPazientiBusy) && m_pEsamiView->m_pEsamiSet->m_bStessoDistretto && !bReadOnly));
		GetDlgItem(IDC_BTN_REFERTO_BIG)->EnableWindow(!bRicerca && ((theApp.m_dwPrivileges & AMLogin_Permissions::modify_report ? TRUE : FALSE) && (m_pEsamiView->m_bEsamiValid) && (!m_pEsamiView->m_bPazientiBusy) && m_pEsamiView->m_pEsamiSet->m_bStessoDistretto && !bReadOnly));
		GetDlgItem(IDC_BTN_REFERTOGENOMICA)->EnableWindow(theApp.m_bUsaModuloGenomica && !bRicerca && ((theApp.m_dwPrivileges & AMLogin_Permissions::modify_report ? TRUE : FALSE) && (m_pEsamiView->m_bEsamiValid) && (!m_pEsamiView->m_bPazientiBusy) && m_pEsamiView->m_pEsamiSet->m_bStessoDistretto && !bReadOnly));


		m_ctrlTextControl.ShowWindow(theApp.m_dwPrivileges & AMLogin_Permissions::view_report ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_STATIC_USER)->ShowWindow(theApp.m_dwPrivileges & AMLogin_Permissions::view_report ? SW_HIDE : SW_SHOW);
	}

	//julio 04/12/2017
	if (theApp.m_bPersonalizzazioniBrasileFleury)
	{
		try
		{
			CString sFicha = m_pEsamiView->m_pEsamiSet->m_sRicovero;
			CString sItem = m_pEsamiView->m_pEsamiSet->m_sCodEsame;

			sItem.Replace(sFicha + "_", "");
			sItem.Replace("_", "0");

			CString sFilter;		

			CExtPrestazioniSet setPrest;
			CString sIdPrestazione = m_pEsamiView->m_pEsamiSet->m_sCodEsame;
			sFilter.Format("IDPRESTAZIONE LIKE '%s'", sIdPrestazione);
			setPrest.SetOpenFilter(sFilter);

			if (setPrest.OpenRecordset("RefertoForm::DoDataExchange") && !setPrest.IsEOF())
			{				
				CString testo;
				testo.Format("Redigir laudo de %s - Ficha %s Item %s", setPrest.m_sCodicePrestazione, sFicha, sItem);

				GetDlgItem(IDC_BTN_REFERTO_SMALL)->SetWindowTextA(testo);
				GetDlgItem(IDC_BTN_REFERTO_BIG)->SetWindowTextA(testo);
				setPrest.CloseRecordset("RefertoForm::DoDataExchange");
			}
			else
			{
				CCodificaRegionaleExSet setCodifica;
				CString sDescriozione = m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto001;
				sDescriozione.Replace("'", "''");
				sFilter.Format("DESCRIZIONE LIKE '%s'", sDescriozione);
				setCodifica.SetOpenFilter(sFilter);

				sFilter.Format("(UO=%li OR UO <> %li)", m_pEsamiView->m_pEsamiSet->m_lUO, m_pEsamiView->m_pEsamiSet->m_lUO);
				setCodifica.SetBaseFilter(sFilter);

				if (setCodifica.OpenRecordset("RefertoForm::DoDataExchange"))
				{
					CString testo;
					if (setCodifica.m_sCodiceRegionale.IsEmpty())
					{
						long lTipoEsame = m_pEsamiView->m_pEsamiSet->m_lIDEsame;
						testo.Format("Redigir laudo de %s - Ficha %s Item %s", CTipoEsameSet().GetDescrizione(lTipoEsame), sFicha, sItem);
					}
					else
					{
						testo.Format("Redigir laudo de %s - Ficha %s Item %s", setCodifica.m_sCodiceRegionale, sFicha, sItem);
					}

					GetDlgItem(IDC_BTN_REFERTO_SMALL)->SetWindowTextA(testo);
					GetDlgItem(IDC_BTN_REFERTO_BIG)->SetWindowTextA(testo);
					setCodifica.CloseRecordset("RefertoForm::DoDataExchange");
				}
				else
				{
					long lTipoEsame = m_pEsamiView->m_pEsamiSet->m_lIDEsame;
					CString testo;
					testo.Format("Redigir laudo de %s - Ficha %s Item %s", CTipoEsameSet().GetDescrizione(lTipoEsame), sFicha, sItem);

					GetDlgItem(IDC_BTN_REFERTO_SMALL)->SetWindowTextA(testo);
					GetDlgItem(IDC_BTN_REFERTO_BIG)->SetWindowTextA(testo);
				}
			}
		}
		catch (...)
		{
			//
		}
	}
}

void CRefertoForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_referto] == NULL)
	{
		pEsamiView->m_pDynForm[sub_referto] = new CRefertoForm(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_referto] != NULL)
		{
			pEsamiView->m_pDynForm[sub_referto]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_referto]->m_lColore = -1;
			pEsamiView->m_pDynForm[sub_referto]->m_lIDFaseBlocco = lIDFaseBlocco;

			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_referto]->CreateChildForm(CRefertoForm::IDD, pParent, rectFrame);
		}
	}
}

BOOL CRefertoForm::OnInitDialog()
{
	CEndoxDynForm::OnInitDialog();

	if (theApp.m_bUsaModuloGenomica)
	{
		GetDlgItem(IDC_BTN_REFERTOGENOMICA)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_REFERTO_SMALL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_REFERTO_BIG)->ShowWindow(SW_HIDE);

		AddAnchor(IDC_BTN_REFERTO_SMALL, CSize(0, 0), CSize(50, 0));
		AddAnchor(IDC_BTN_REFERTOGENOMICA, CSize(50, 0), CSize(100, 0));
	}
	else
	{
		GetDlgItem(IDC_BTN_REFERTOGENOMICA)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_REFERTO_SMALL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_REFERTO_BIG)->ShowWindow(SW_SHOW);

		AddAnchor(IDC_BTN_REFERTO_BIG, CSize(0, 0), CSize(100, 0));
	}

	AddAnchor(IDC_STATIC_LINE1, CSize(0, 0), CSize(100, 0));
	AddAnchor(IDC_STATIC_FRAME, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDC_TEXTCONTROL_PLACE, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDC_STATIC_USER, CSize(0, 0), CSize(100, 100));

	m_ctrlTextControl.SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

	theApp.LocalizeDialog(this, CRefertoForm::IDD, "RefertoForm");
	return TRUE;
}

void CRefertoForm::OnBnClickedBtnReferto()
{
	m_ctrlButtonReferto.SetCheck(BST_UNCHECKED);

	if (m_pEsamiView != NULL)
	{
		// Sandro 23/06/2017 //
		if ((theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury) && (!m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito.IsEmpty() && m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito != "-1"))
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAME_TRASFERITO) + " " + m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito + ".");
			return;
		}

		if ((theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury) && !theApp.m_bNoConiugazione)
		{
			if (CEsamiSet().IsConiugatoSecondario(m_pEsamiView->m_pEsamiSet->m_lContatore) && !m_pEsamiView->m_pEsamiSet->m_bRefertoConiugatoAltraUO)
			{
				theApp.AfxMessageBoxEndo(IDS_FLEURY_CONIUGATO_SECONDARIO);
				return;
			}
			// Luiz - 18/07/2019 - P3 - Verifica presença de conjugações
			
			//Gabriel - TCP
			BOOL bSkip = FALSE;
			CString sFilter;
			sFilter.Format("ORDERNUMBER = '%s'", m_pEsamiView->m_pEsamiSet->m_sCodEsame);

			CExtOrdiniSet ordiniSet;
			ordiniSet.SetOpenFilter(sFilter);
			ordiniSet.SetBaseFilter(sFilter);

			if (ordiniSet.OpenRecordset("RefertoForm::OnBnClickedBtnReferto"))
			{
				if (!ordiniSet.IsEOF())
				{
					//Gabriel - TCP FIX
					if (ordiniSet.m_sOrderNumberCorrelati != "")
					{
						bSkip = TRUE;
					}
				}
				ordiniSet.CloseRecordset("RefertoForm::OnBnClickedBtnReferto");
			}

			if (!bSkip)
			{
				BOOL m_bConiugato1toN = FALSE;
				BOOL m_bConiugato1to1 = FALSE;
				m_bConiugato1toN = m_pEsamiView->RefertoPrincipaleSecondario(m_pEsamiView->m_pEsamiSet->m_lContatore);
				m_bConiugato1to1 = CEsamiSet().IsConiugatoPrincipaleSecondario(m_pEsamiView->m_pEsamiSet->m_sCodEsame);

				if ((!m_bConiugato1to1) && (!m_bConiugato1toN))
				{
					CList<STRUCT_FICHA_ITEM> listItems;
					CString sActUO = CVistaOtherFichaItemsSet().GetFleuryListOtherFichaItems(m_pEsamiView->m_pEsamiSet->m_sCodEsame, &listItems);
					if (listItems.GetCount() > 0)
						CConiugazioneEsamiDlg(this, m_pEsamiView, &listItems, sActUO, m_pEsamiView->m_pEsamiSet->m_sCodEsame).DoModal();

					listItems.RemoveAll();
				}
			}
		}

		//
		m_pEsamiView->OnEsameReferto();		
		UpdateData(FALSE);

		if (m_pEsamiView->m_pDynForm[sub_codiciclassificazionediagnostica] != NULL)
			m_pEsamiView->m_pDynForm[sub_codiciclassificazionediagnostica]->SendMessage(MSG_FORM_LOAD); // OnFormLoad //
	}
}

//Julio Genomica
void CRefertoForm::OnBnClickedBtnRefertoGenomica()
{
	m_ctrlButtonRefertoGenomica.SetCheck(BST_UNCHECKED);

	if (m_pEsamiView != NULL)
	{
		m_pEsamiView->OnEsameRefertoGenomica();
		UpdateData(FALSE);

		if (m_pEsamiView->m_pDynForm[sub_codiciclassificazionediagnostica] != NULL)
			m_pEsamiView->m_pDynForm[sub_codiciclassificazionediagnostica]->SendMessage(MSG_FORM_LOAD); // OnFormLoad //
	}
}

void CRefertoForm::OnSize(UINT nType, int cx, int cy)
{
	CEndoxDynForm::OnSize(nType, cx, cy);

	CWnd* pTextControlPlace = GetDlgItem(IDC_TEXTCONTROL_PLACE);
	if (pTextControlPlace && m_ctrlTextControl.GetSafeHwnd())
	{
		CRect rect;
		pTextControlPlace->GetWindowRect(rect);
		ScreenToClient(&rect);
		m_ctrlTextControl.SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOMOVE);
	}
}

long CRefertoForm::GetContenuto()
{
	return sub_referto;
}

BOOL CRefertoForm::CampoObbligatorioValido()
{
	return !m_ctrlTextControl.GetText().Trim().IsEmpty();
}

LRESULT CRefertoForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	BOOL bRicerca = theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI || theApp.m_nProgramMode & FILTER_RECORD_ESAMI;

	if (bRicerca)
	{
		m_ctrlTextControl.SetEditMode(0);
	}
	else
	{
		m_ctrlTextControl.SetEditMode(1);
	}

	return 0;
}

LRESULT CRefertoForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	if (m_pEsamiView->m_pEsamiSet)
	{
		ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sRefertoTestoTxt, "EEsami.RefertoTestoTxt", 1);
	}

	return 1;
}