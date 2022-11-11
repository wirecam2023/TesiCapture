#include "stdafx.h"
#include "Endox.h"
#include "PacemakerDynForm.h"

#include "EsamiView.h"
#include "EsamiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPacemakerDynForm::CPacemakerDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(nID, pParent, pEsamiView),
	  m_ctrlRadio1(IDC_STATIC_PACEMAKER),
	  m_ctrlRadio2(IDC_STATIC_PACEMAKER),
	  m_ctrlRadio3(IDC_STATIC_PACEMAKER),
	  m_ctrlRadio4(IDC_STATIC_PACEMAKER),
	  m_ctrlRadio5(IDC_STATIC_PACEMAKER),
	  m_ctrlRadio6(IDC_STATIC_PACEMAKER),
	  m_ctrlRadio7(IDC_STATIC_PACEMAKER)
{
	m_bReadOnly = FALSE;
}

CPacemakerDynForm::~CPacemakerDynForm()
{
}

BEGIN_MESSAGE_MAP(CPacemakerDynForm, CEndoxDynForm)
	ON_WM_CTLCOLOR()

	ON_STN_CLICKED(IDC_STATIC1, OnStnClickedStatic1)
	ON_STN_CLICKED(IDC_STATIC2, OnStnClickedStatic2)
	ON_STN_CLICKED(IDC_STATIC3, OnStnClickedStatic3)
	ON_STN_CLICKED(IDC_STATIC4, OnStnClickedStatic4)
	ON_STN_CLICKED(IDC_STATIC5, OnStnClickedStatic5)
	ON_STN_CLICKED(IDC_STATIC6, OnStnClickedStatic6)
	ON_STN_CLICKED(IDC_STATIC7, OnStnClickedStatic7)
END_MESSAGE_MAP()

void CPacemakerDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_pacemaker] == NULL)
	{
		pEsamiView->m_pDynForm[sub_pacemaker] = new CPacemakerDynForm(CPacemakerDynForm::IDD, NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_pacemaker] != NULL)
		{
			pEsamiView->m_pDynForm[sub_pacemaker]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_pacemaker]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_pacemaker]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_pacemaker]->CreateChildForm(CPacemakerDynForm::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CPacemakerDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_PACEMAKER:
		case IDC_STATIC_TERAPIA:
		case IDC_STATIC_TERAPIA2:
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
		case IDC_STATIC5:
		case IDC_STATIC6:
		case IDC_STATIC7:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

void CPacemakerDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Radio(pDX, IDC_RADIO1, m_pEsamiView->m_pEsamiSet->m_iPacemaker);
	DDX_Radio(pDX, IDC_RADIO3, m_pEsamiView->m_pEsamiSet->m_iAnticoagulanti);
	DDX_Radio(pDX, IDC_RADIO5, m_pEsamiView->m_pEsamiSet->m_iAntiaggreganti);

	// Sandro 27/08/2010 //
	DDX_Control(pDX, IDC_RADIO1, m_ctrlRadio1);
	DDX_Control(pDX, IDC_RADIO2, m_ctrlRadio2);
	DDX_Control(pDX, IDC_RADIO3, m_ctrlRadio3);
	DDX_Control(pDX, IDC_RADIO4, m_ctrlRadio4);
	DDX_Control(pDX, IDC_RADIO5, m_ctrlRadio5);
	DDX_Control(pDX, IDC_RADIO6, m_ctrlRadio6);
	DDX_Control(pDX, IDC_RADIO7, m_ctrlRadio7);

	DDX_Control(pDX, IDC_STATIC_PACEMAKER, m_ctrlStaticPacemaker);
	DDX_Control(pDX, IDC_STATIC_TERAPIA, m_ctrlTerapia);
	DDX_Control(pDX, IDC_STATIC_TERAPIA2, m_ctrlTerapia2);
	DDX_Control(pDX, IDC_STATIC1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC4, m_ctrlStatic4);
	DDX_Control(pDX, IDC_STATIC5, m_ctrlStatic5);
	DDX_Control(pDX, IDC_STATIC6, m_ctrlStatic6);
	DDX_Control(pDX, IDC_STATIC7, m_ctrlStatic7);
}

BOOL CPacemakerDynForm::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_STATIC_PACEMAKER, CSize(0,20), CSize(100,20));
	AddAnchor(IDC_RADIO1, CSize(0,20), CSize(0,20));
	AddAnchor(IDC_STATIC1, CSize(0,20), CSize(50,20));
	AddAnchor(IDC_RADIO2, CSize(50,20), CSize(50,20));
	AddAnchor(IDC_STATIC2, CSize(50,20), CSize(100,20));
	AddAnchor(IDC_STATIC_TERAPIA, CSize(0,50), CSize(100,50));
	AddAnchor(IDC_RADIO3, CSize(0,50), CSize(0,50));
	AddAnchor(IDC_STATIC3, CSize(0,50), CSize(50,50));
	AddAnchor(IDC_RADIO4, CSize(50,50), CSize(50,50));
	AddAnchor(IDC_STATIC4, CSize(50,50), CSize(100,50));
	AddAnchor(IDC_STATIC_TERAPIA2, CSize(0,80), CSize(100,80));
	AddAnchor(IDC_RADIO5, CSize(0,80), CSize(0,80));
	AddAnchor(IDC_STATIC5, CSize(0,80), CSize(34,80));
	AddAnchor(IDC_RADIO6, CSize(34,80), CSize(34,80));
	AddAnchor(IDC_STATIC6, CSize(34,80), CSize(66,80));
	AddAnchor(IDC_RADIO7, CSize(66,80), CSize(66,80));
	AddAnchor(IDC_STATIC7, CSize(66,80), CSize(100,80));

	GetDlgItem(IDC_STATIC_PACEMAKER)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_TERAPIA)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_TERAPIA2)->SetFont(&theApp.m_fontBold);

	theApp.LocalizeDialog(this, CPacemakerDynForm::IDD, "PacemakerDynForm");

	return bReturn;
}

LRESULT CPacemakerDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CPacemakerDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(FALSE);
}

LRESULT CPacemakerDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	m_bReadOnly = (BOOL)wParam;

	GetDlgItem(IDC_RADIO1)->EnableWindow(!m_bReadOnly);
	GetDlgItem(IDC_RADIO2)->EnableWindow(!m_bReadOnly);
	GetDlgItem(IDC_RADIO3)->EnableWindow(!m_bReadOnly);
	GetDlgItem(IDC_RADIO4)->EnableWindow(!m_bReadOnly);
	GetDlgItem(IDC_RADIO5)->EnableWindow(!m_bReadOnly);
	GetDlgItem(IDC_RADIO6)->EnableWindow(!m_bReadOnly);
	GetDlgItem(IDC_RADIO7)->EnableWindow(!m_bReadOnly);

	return 1;
}

LRESULT CPacemakerDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	return 1;
}

LRESULT CPacemakerDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT CPacemakerDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	if (m_pEsamiView->m_pEsamiSet->m_iPacemaker >= 0)
		ComponiRicercaShort(*pStrWhere, m_pEsamiView->m_pEsamiSet, (short*)&m_pEsamiView->m_pEsamiSet->m_iPacemaker, "EEsami.Pacemaker", 0, TRUE);
	if (m_pEsamiView->m_pEsamiSet->m_iAnticoagulanti >= 0)
		ComponiRicercaShort(*pStrWhere, m_pEsamiView->m_pEsamiSet, (short*)&m_pEsamiView->m_pEsamiSet->m_iAnticoagulanti, "EEsami.Anticoagulanti", 0, TRUE);
	if (m_pEsamiView->m_pEsamiSet->m_iAntiaggreganti >= 0)
		ComponiRicercaShort(*pStrWhere, m_pEsamiView->m_pEsamiSet, (short*)&m_pEsamiView->m_pEsamiSet->m_iAntiaggreganti, "EEsami.Antiaggreganti", 0, TRUE);

	return 1;
}

long CPacemakerDynForm::GetContenuto()
{
	return sub_pacemaker;
}

BOOL CPacemakerDynForm::CampoObbligatorioValido()
{
	if ((m_pEsamiView->m_pEsamiSet->m_iPacemaker >= 0) && (m_pEsamiView->m_pEsamiSet->m_iAnticoagulanti >= 0) && (m_pEsamiView->m_pEsamiSet->m_iAntiaggreganti >= 0))
		return TRUE;

	return FALSE;
}

void CPacemakerDynForm::OnStnClickedStatic1()
{
	if (!m_bReadOnly)
	{
		UpdateData(TRUE);
		m_pEsamiView->m_pEsamiSet->m_iPacemaker = 0;
		UpdateData(FALSE);

		// aggiorno interfaccia //
		// OnClickedRadio1();
	}
}

void CPacemakerDynForm::OnStnClickedStatic2()
{
	if (!m_bReadOnly)
	{
		UpdateData(TRUE);
		m_pEsamiView->m_pEsamiSet->m_iPacemaker = 1;
		UpdateData(FALSE);

		// aggiorno interfaccia //
		// OnClickedRadio1();
	}
}

void CPacemakerDynForm::OnStnClickedStatic3()
{
	if (!m_bReadOnly)
	{
		UpdateData(TRUE);
		m_pEsamiView->m_pEsamiSet->m_iAnticoagulanti = 0;
		UpdateData(FALSE);

		// aggiorno interfaccia //
		// OnClickedRadio1();
	}
}

void CPacemakerDynForm::OnStnClickedStatic4()
{
	if (!m_bReadOnly)
	{
		UpdateData(TRUE);
		m_pEsamiView->m_pEsamiSet->m_iAnticoagulanti = 1;
		UpdateData(FALSE);

		// aggiorno interfaccia //
		// OnClickedRadio1();
	}
}

void CPacemakerDynForm::OnStnClickedStatic5()
{
	if (!m_bReadOnly)
	{
		UpdateData(TRUE);
		m_pEsamiView->m_pEsamiSet->m_iAntiaggreganti = 0;
		UpdateData(FALSE);

		// aggiorno interfaccia //
		// OnClickedRadio1();
	}
}

void CPacemakerDynForm::OnStnClickedStatic6()
{
	if (!m_bReadOnly)
	{
		UpdateData(TRUE);
		m_pEsamiView->m_pEsamiSet->m_iAntiaggreganti = 1;
		UpdateData(FALSE);

		// aggiorno interfaccia //
		// OnClickedRadio1();
	}
}

void CPacemakerDynForm::OnStnClickedStatic7()
{
	if (!m_bReadOnly)
	{
		UpdateData(TRUE);
		m_pEsamiView->m_pEsamiSet->m_iAntiaggreganti = 2;
		UpdateData(FALSE);

		// aggiorno interfaccia //
		// OnClickedRadio1();
	}
}