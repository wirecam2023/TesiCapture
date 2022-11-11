#include "stdafx.h"
#include "Endox.h"
#include "PortPacemakerDynForm.h"

#include "EsamiView.h"
#include "EsamiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPortPacemakerDynForm::CPortPacemakerDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(nID, pParent, pEsamiView),
	  m_ctrlRadio1(IDC_EDIT_DESCRIZIONE),
	  m_ctrlRadio2(IDC_EDIT_DESCRIZIONE)
{
	m_bReadOnly = FALSE;
}

CPortPacemakerDynForm::~CPortPacemakerDynForm()
{
}

BEGIN_MESSAGE_MAP(CPortPacemakerDynForm, CEndoxDynForm)
	ON_WM_CTLCOLOR()

	ON_BN_CLICKED(IDC_RADIO1, OnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnClickedRadio2)
	ON_STN_CLICKED(IDC_STATIC1, OnStnClickedStatic1)
	ON_STN_CLICKED(IDC_STATIC2, OnStnClickedStatic2)
END_MESSAGE_MAP()

void CPortPacemakerDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_portatorepacemaker] == NULL)
	{
		pEsamiView->m_pDynForm[sub_portatorepacemaker] = new CPortPacemakerDynForm(CPortPacemakerDynForm::IDD, NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_portatorepacemaker] != NULL)
		{
			pEsamiView->m_pDynForm[sub_portatorepacemaker]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_portatorepacemaker]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_portatorepacemaker]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_portatorepacemaker]->CreateChildForm(CPortPacemakerDynForm::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CPortPacemakerDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_PACEMAKER:
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
		case IDC_EDIT_DESCRIZIONE:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

void CPortPacemakerDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Radio(pDX, IDC_RADIO1, m_pEsamiView->m_pEsamiSet->m_iPacemaker);

	DDX_FieldText(pDX, IDC_EDIT_DESCRIZIONE, m_pEsamiView->m_pEsamiSet->m_sDescrizionePacemaker, m_pEsamiView->m_pEsamiSet->GetRecordset());

	DDX_Control(pDX, IDC_EDIT_DESCRIZIONE, m_ctrlDescrizione);

	// Sandro 27/08/2010 //
	DDX_Control(pDX, IDC_RADIO1, m_ctrlRadio1);
	DDX_Control(pDX, IDC_RADIO2, m_ctrlRadio2);

	DDX_Control(pDX, IDC_STATIC_PACEMAKER, m_ctrlStaticPacemaker);
	DDX_Control(pDX, IDC_STATIC1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC3, m_ctrlStatic3);
}

BOOL CPortPacemakerDynForm::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_STATIC_PACEMAKER, CSize(0,25), CSize(100,25));
	AddAnchor(IDC_RADIO1, CSize(0,50), CSize(0,50));
	AddAnchor(IDC_STATIC1, CSize(0,50), CSize(50,50));
	AddAnchor(IDC_RADIO2, CSize(50,50), CSize(50,50));
	AddAnchor(IDC_STATIC2, CSize(50,50), CSize(100,50));
	AddAnchor(IDC_STATIC3, CSize(0,75), CSize(100,75));
	AddAnchor(IDC_EDIT_DESCRIZIONE, CSize(0,75), CSize(100,75));

	GetDlgItem(IDC_STATIC_PACEMAKER)->SetFont(&theApp.m_fontBold);

	theApp.LocalizeDialog(this, CPortPacemakerDynForm::IDD, "PortPacemakerDynForm");

	return bReturn;
}

void CPortPacemakerDynForm::OnClickedRadio1()
{
	GetDlgItem(IDC_STATIC3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_DESCRIZIONE)->SetWindowText("");
	GetDlgItem(IDC_EDIT_DESCRIZIONE)->ShowWindow(SW_HIDE);
}

void CPortPacemakerDynForm::OnClickedRadio2()
{
	GetDlgItem(IDC_STATIC3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_DESCRIZIONE)->ShowWindow(SW_SHOW);
}

LRESULT CPortPacemakerDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CPortPacemakerDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(FALSE);
}

LRESULT CPortPacemakerDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	m_bReadOnly = (BOOL)wParam;

	GetDlgItem(IDC_RADIO1)->EnableWindow(!m_bReadOnly);
	GetDlgItem(IDC_RADIO2)->EnableWindow(!m_bReadOnly);
	SendDlgItemMessage(IDC_EDIT_DESCRIZIONE, EM_SETREADONLY, m_bReadOnly, lParam);

	if (m_pEsamiView->m_pEsamiSet->m_iPacemaker == 1)
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

LRESULT CPortPacemakerDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	return 1;
}

LRESULT CPortPacemakerDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT CPortPacemakerDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	if (m_pEsamiView->m_pEsamiSet->m_iPacemaker >= 0)
	{
		ComponiRicercaLong(pStrWhere, m_pEsamiView->m_pEsamiSet, (long*)&m_pEsamiView->m_pEsamiSet->m_iPacemaker, "EEsami.Pacemaker", 0, "AND");

		if (m_pEsamiView->m_pEsamiSet->m_sDescrizionePacemaker.Compare("") != 0)
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sDescrizionePacemaker, "EEsami.DescrizionePacemaker", 0);
	}

	return 1;
}

long CPortPacemakerDynForm::GetContenuto()
{
	return sub_portatorepacemaker;
}

BOOL CPortPacemakerDynForm::CampoObbligatorioValido()
{
	switch(m_pEsamiView->m_pEsamiSet->m_iPacemaker)
	{
		case 0:
		{
			return TRUE;
			break;
		}
		case 1:
		{
			if (m_pEsamiView->m_pEsamiSet->m_sDescrizionePacemaker.GetLength() > 0)
				return TRUE;
			break;
		}
	}

	return FALSE;
}

void CPortPacemakerDynForm::OnStnClickedStatic1()
{
	if (!m_bReadOnly)
	{
		UpdateData(TRUE);
		m_pEsamiView->m_pEsamiSet->m_iPacemaker = 0;
		UpdateData(FALSE);

		// aggiorno interfaccia //
		OnClickedRadio1();
	}
}

void CPortPacemakerDynForm::OnStnClickedStatic2()
{
	if (!m_bReadOnly)
	{
		UpdateData(TRUE);
		m_pEsamiView->m_pEsamiSet->m_iPacemaker = 1;
		UpdateData(FALSE);

		// aggiorno interfaccia //
		OnClickedRadio2();
	}
}