#include "stdafx.h"
#include "Endox.h"
#include "AntiaggregantiDynForm.h"

#include "EsamiView.h"
#include "EsamiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAntiaggregantiDynForm::CAntiaggregantiDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(nID, pParent, pEsamiView),
	  m_ctrlRadio1(IDC_EDIT_DESCRIZIONE),
	  m_ctrlRadio2(IDC_EDIT_DESCRIZIONE),
	  m_ctrlRadio3(IDC_EDIT_DESCRIZIONE)
{
	m_bReadOnly = FALSE;
}

CAntiaggregantiDynForm::~CAntiaggregantiDynForm()
{
}

BEGIN_MESSAGE_MAP(CAntiaggregantiDynForm, CEndoxDynForm)
	ON_WM_CTLCOLOR()

	ON_BN_CLICKED(IDC_RADIO1, OnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnClickedRadio3)

	ON_STN_CLICKED(IDC_STATIC1, OnStnClickedStatic1)
	ON_STN_CLICKED(IDC_STATIC2, OnStnClickedStatic2)
	ON_STN_CLICKED(IDC_STATIC4, OnStnClickedStatic4)
END_MESSAGE_MAP()

void CAntiaggregantiDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_antiaggreganti] == NULL)
	{
		pEsamiView->m_pDynForm[sub_antiaggreganti] = new CAntiaggregantiDynForm(CAntiaggregantiDynForm::IDD, NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_antiaggreganti] != NULL)
		{
			pEsamiView->m_pDynForm[sub_antiaggreganti]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_antiaggreganti]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_antiaggreganti]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_antiaggreganti]->CreateChildForm(CAntiaggregantiDynForm::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CAntiaggregantiDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_ANTIAGGREGANTI:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			if (m_crCampoObbligatorio > 0)
				pDC->SetBkColor(m_crCampoObbligatorio);

			break;
		}

		case IDC_STATIC1:
		case IDC_STATIC2:
		case IDC_STATIC3:
		case IDC_STATIC4:
		case IDC_EDIT_DESCRIZIONE:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

void CAntiaggregantiDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Radio(pDX, IDC_RADIO1, m_pEsamiView->m_pEsamiSet->m_iAntiaggreganti);
	// quello sopra funziona bene, quello sotto mi da l'errore "selezionare un pulsante." //
	// DDX_FieldRadio(pDX, IDC_RADIO1, m_pEsamiView->m_pEsamiSet->m_iPortPacemaker, m_pEsamiView->m_pEsamiSet);
	//DDX_Radio(pDX, IDC_RADIO3, m_iAntiaggreganteDoppio);

	DDX_FieldText(pDX, IDC_EDIT_DESCRIZIONE, m_pEsamiView->m_pEsamiSet->m_sDescrizioneAntiaggreganti, m_pEsamiView->m_pEsamiSet->GetRecordset());

	DDX_Control(pDX, IDC_EDIT_DESCRIZIONE, m_ctrlDescrizione);

	// Sandro 27/08/2010 //
	DDX_Control(pDX, IDC_RADIO1, m_ctrlRadio1);
	DDX_Control(pDX, IDC_RADIO2, m_ctrlRadio2);
	DDX_Control(pDX, IDC_RADIO3, m_ctrlRadio3);

	DDX_Control(pDX, IDC_STATIC_ANTIAGGREGANTI, m_ctrlStaticAntiaggreganti);
	DDX_Control(pDX, IDC_STATIC1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC4, m_ctrlStatic4);
}

BOOL CAntiaggregantiDynForm::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_STATIC_ANTIAGGREGANTI, CSize(0,25), CSize(100,25));
	AddAnchor(IDC_RADIO1, CSize(0,50), CSize(0,50));
	AddAnchor(IDC_STATIC1, CSize(0,50), CSize(33,50));
	AddAnchor(IDC_RADIO2, CSize(33,50), CSize(33,50));
	AddAnchor(IDC_STATIC2, CSize(33,50), CSize(67,50));
	AddAnchor(IDC_RADIO3, CSize(67,50), CSize(67,50));
	AddAnchor(IDC_STATIC4, CSize(67,50), CSize(100,50));
	AddAnchor(IDC_STATIC3, CSize(0,75), CSize(100,75));
	AddAnchor(IDC_EDIT_DESCRIZIONE, CSize(0,75), CSize(100,75));

	GetDlgItem(IDC_STATIC_ANTIAGGREGANTI)->SetFont(&theApp.m_fontBold);

	theApp.LocalizeDialog(this, CAntiaggregantiDynForm::IDD, "AntiaggregantiDynForm");

	return bReturn;
}

void CAntiaggregantiDynForm::OnClickedRadio1()
{
	GetDlgItem(IDC_STATIC3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_DESCRIZIONE)->SetWindowText("");
	GetDlgItem(IDC_EDIT_DESCRIZIONE)->ShowWindow(SW_HIDE);
}

void CAntiaggregantiDynForm::OnClickedRadio2()
{
	GetDlgItem(IDC_STATIC3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_DESCRIZIONE)->ShowWindow(SW_SHOW);
}

void CAntiaggregantiDynForm::OnClickedRadio3()
{
	GetDlgItem(IDC_STATIC3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_DESCRIZIONE)->ShowWindow(SW_SHOW);
}

LRESULT CAntiaggregantiDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CAntiaggregantiDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(FALSE);
}

LRESULT CAntiaggregantiDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	m_bReadOnly = (BOOL)wParam;

	GetDlgItem(IDC_RADIO1)->EnableWindow(!m_bReadOnly);
	GetDlgItem(IDC_RADIO2)->EnableWindow(!m_bReadOnly);
	GetDlgItem(IDC_RADIO3)->EnableWindow(!m_bReadOnly);
	SendDlgItemMessage(IDC_EDIT_DESCRIZIONE, EM_SETREADONLY, m_bReadOnly, lParam);

	if (m_pEsamiView->m_pEsamiSet->m_iAntiaggreganti > 0)
	{
		GetDlgItem(IDC_STATIC3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_DESCRIZIONE)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_STATIC3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_DESCRIZIONE)->ShowWindow(SW_HIDE);
	}

	return 1;
}

LRESULT CAntiaggregantiDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	return 1;
}

LRESULT CAntiaggregantiDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT CAntiaggregantiDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	if (m_pEsamiView->m_pEsamiSet->m_iAntiaggreganti >= 0)
	{
		ComponiRicercaLong(pStrWhere, m_pEsamiView->m_pEsamiSet, (long*)&m_pEsamiView->m_pEsamiSet->m_iAntiaggreganti, "EEsami.Antiaggreganti", 0, "AND");

		if (m_pEsamiView->m_pEsamiSet->m_sDescrizioneAntiaggreganti.Compare("") != 0)
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sDescrizioneAntiaggreganti, "EEsami.DescrizioneAntiaggreganti", 0);
	}

	return 1;
}

long CAntiaggregantiDynForm::GetContenuto()
{
	return sub_antiaggreganti;
}

BOOL CAntiaggregantiDynForm::CampoObbligatorioValido()
{
	switch(m_pEsamiView->m_pEsamiSet->m_iAntiaggreganti)
	{
		case 0:
		{
			return TRUE;
			break;
		}
		case 1:
		{
			if (m_pEsamiView->m_pEsamiSet->m_sDescrizioneAntiaggreganti.GetLength() > 0)
				return TRUE;
			break;
		}
		case 2:
		{
			if (m_pEsamiView->m_pEsamiSet->m_sDescrizioneAntiaggreganti.GetLength() > 0)
				return TRUE;
			break;
		}
	}

	return FALSE;
}

void CAntiaggregantiDynForm::OnStnClickedStatic1()
{
	if (!m_bReadOnly)
	{
		UpdateData(TRUE);
		m_pEsamiView->m_pEsamiSet->m_iAntiaggreganti = 0;
		UpdateData(FALSE);

		// aggiorno interfaccia //
		OnClickedRadio1();
	}
}

void CAntiaggregantiDynForm::OnStnClickedStatic2()
{
	if (!m_bReadOnly)
	{
		UpdateData(TRUE);
		m_pEsamiView->m_pEsamiSet->m_iAntiaggreganti = 1;
		UpdateData(FALSE);

		// aggiorno interfaccia //
		OnClickedRadio2();
	}
}

void CAntiaggregantiDynForm::OnStnClickedStatic4()
{
	if (!m_bReadOnly)
	{
		UpdateData(TRUE);
		m_pEsamiView->m_pEsamiSet->m_iAntiaggreganti = 2;
		UpdateData(FALSE);

		// aggiorno interfaccia //
		OnClickedRadio3();
	}
}