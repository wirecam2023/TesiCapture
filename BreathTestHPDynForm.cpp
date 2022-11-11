#include "stdafx.h"
#include "Endox.h"
#include "BreathTestHPDynForm.h"

#include "EsamiSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBreathTestHPDynForm::CBreathTestHPDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(nID, pParent, pEsamiView),
	  m_ctrlRadio1(IDC_EDIT),
	  m_ctrlRadio2(IDC_EDIT)
{
	m_bReadOnly = FALSE;
}

CBreathTestHPDynForm::~CBreathTestHPDynForm()
{
}

BEGIN_MESSAGE_MAP(CBreathTestHPDynForm, CEndoxDynForm)
	ON_WM_CTLCOLOR()

	ON_BN_CLICKED(IDC_RADIO1, OnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnClickedRadio2)

	ON_STN_CLICKED(IDC_STATIC1, OnStnClickedStatic1)
	ON_STN_CLICKED(IDC_STATIC2, OnStnClickedStatic2)
END_MESSAGE_MAP()

void CBreathTestHPDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_breathtest_hp] == NULL)
	{
		pEsamiView->m_pDynForm[sub_breathtest_hp] = new CBreathTestHPDynForm(CBreathTestHPDynForm::IDD, NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_breathtest_hp] != NULL)
		{
			pEsamiView->m_pDynForm[sub_breathtest_hp]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_breathtest_hp]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_breathtest_hp]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_breathtest_hp]->CreateChildForm(CBreathTestHPDynForm::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CBreathTestHPDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_BT:
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
		case IDC_EDIT:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}

		case IDC_STATIC_RESULT:
		{
			if (m_pEsamiView->m_pEsamiSet->m_fBreathTestHPDiff >= theApp.m_fSogliaBreathTestHP)
			{
				// positivo //
				pDC->SetTextColor(theApp.m_color[0]);
			}
			else
			{
				// negativo o dubbio //
				if (m_lColore >= 0)
					pDC->SetTextColor(theApp.m_color[m_lColore]);
			}

			break;
		}
	}

	return hBrush;
}

void CBreathTestHPDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_RADIO1, m_ctrlRadio1);
	DDX_Control(pDX, IDC_RADIO2, m_ctrlRadio2);

	DDX_Control(pDX, IDC_STATIC_BT, m_ctrlStaticBT);
	DDX_Control(pDX, IDC_STATIC1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_EDIT, m_ctrlEdit);

	DDX_Radio(pDX, IDC_RADIO1, m_pEsamiView->m_pEsamiSet->m_iBreathTestHP);
	DDX_BreathTestHP(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_fBreathTestHPDiff, m_pEsamiView->m_pEsamiSet->GetRecordset());

	CString strProva;
	m_ctrlEdit.GetWindowText(strProva);

	if ((m_pEsamiView->m_pEsamiSet->m_fBreathTestHPDiff >= 0.0f) && (m_pEsamiView->m_pEsamiSet->m_fBreathTestHPDiff < theApp.m_fSogliaBreathTestHP))
	{
		// negativo //
		GetDlgItem(IDC_STATIC_RESULT)->SetFont(&theApp.m_fontNormal);
		SetDlgItemText(IDC_STATIC_RESULT, theApp.GetMessageString(IDS_NEGATIVO));
	}
	else if (m_pEsamiView->m_pEsamiSet->m_fBreathTestHPDiff >= theApp.m_fSogliaBreathTestHP)
	{
		// positivo //
		GetDlgItem(IDC_STATIC_RESULT)->SetFont(&theApp.m_fontBold);
		SetDlgItemText(IDC_STATIC_RESULT, theApp.GetMessageString(IDS_POSITIVO));
	}
	else
	{
		// nullo //
		SetDlgItemText(IDC_STATIC_RESULT, "");
	}
}

BOOL CBreathTestHPDynForm::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_STATIC_BT, CSize(0,40), CSize(60,40));
	AddAnchor(IDC_RADIO1, CSize(60,40), CSize(60,40));
	AddAnchor(IDC_STATIC1, CSize(60,40), CSize(80,40));
	AddAnchor(IDC_RADIO2, CSize(80,40), CSize(80,40));
	AddAnchor(IDC_STATIC2, CSize(80,40), CSize(100,40));
	AddAnchor(IDC_STATIC3, CSize(0,60), CSize(60,60));
	AddAnchor(IDC_EDIT, CSize(60,60), CSize(80,60));
	AddAnchor(IDC_STATIC_RESULT, CSize(80,60), CSize(100,60));

	GetDlgItem(IDC_STATIC_BT)->SetFont(&theApp.m_fontBold);

	m_ctrlEdit.SetEditMask("0.0", "_._");

	theApp.LocalizeDialog(this, CBreathTestHPDynForm::IDD, "BreathTestHPDynForm");

	return bReturn;
}

void CBreathTestHPDynForm::OnClickedRadio1()
{
	GetDlgItem(IDC_STATIC3)->ShowWindow(SW_SHOW);
	m_ctrlEdit.ShowWindow(SW_SHOW);
}

void CBreathTestHPDynForm::OnClickedRadio2()
{
	GetDlgItem(IDC_STATIC3)->ShowWindow(SW_HIDE);
	m_ctrlEdit.SetWindowText(m_ctrlEdit.GetDefault());
	m_ctrlEdit.ShowWindow(SW_HIDE);
}

LRESULT CBreathTestHPDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CBreathTestHPDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(FALSE);
}

LRESULT CBreathTestHPDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	m_bReadOnly = (BOOL)wParam;

	GetDlgItem(IDC_RADIO1)->EnableWindow(!m_bReadOnly);
	GetDlgItem(IDC_RADIO2)->EnableWindow(!m_bReadOnly);
	SendDlgItemMessage(IDC_EDIT, EM_SETREADONLY, m_bReadOnly, lParam);

	if (m_pEsamiView->m_pEsamiSet->m_iBreathTestHP == 1)
	{
		GetDlgItem(IDC_STATIC3)->ShowWindow(SW_HIDE);
		m_ctrlEdit.ShowWindow(SW_HIDE);
	}
	else
	{
		GetDlgItem(IDC_STATIC3)->ShowWindow(SW_SHOW);
		m_ctrlEdit.ShowWindow(SW_SHOW);
	}

	GetDlgItem(IDC_STATIC_RESULT)->ShowWindow((BOOL)wParam ? SW_SHOW : SW_HIDE);

	return 1;
}

LRESULT CBreathTestHPDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	return 1;
}

LRESULT CBreathTestHPDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT CBreathTestHPDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	if (m_pEsamiView->m_pEsamiSet->m_iBreathTestHP >= 0)
	{
		ComponiRicercaLong(pStrWhere, m_pEsamiView->m_pEsamiSet, (long*)&m_pEsamiView->m_pEsamiSet->m_iBreathTestHP, "EEsami.BreathTestHP", 0, "AND");

		/*if (m_pEsamiView->m_pEsamiSet->m_sDescrizioneAllergie.Compare("") != 0)
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sDescrizioneAllergie, "EEsami.DescrizioneAllergie", 0);*/
	}

	return 1;
}

long CBreathTestHPDynForm::GetContenuto()
{
	return sub_breathtest_hp;
}

BOOL CBreathTestHPDynForm::CampoObbligatorioValido()
{
	switch(m_pEsamiView->m_pEsamiSet->m_iBreathTestHP)
	{
		case 0:
		{
			if (m_pEsamiView->m_pEsamiSet->m_fBreathTestHPDiff >= 0.0f)
				return TRUE;
			break;
		}
		case 1:
		{
			return TRUE;
			break;
		}
	}

	return FALSE;
}

void CBreathTestHPDynForm::OnStnClickedStatic1()
{
	if (!m_bReadOnly)
	{
		UpdateData(TRUE);
		m_pEsamiView->m_pEsamiSet->m_iBreathTestHP = 0;
		UpdateData(FALSE);

		// aggiorno interfaccia //
		OnClickedRadio1();
	}
}

void CBreathTestHPDynForm::OnStnClickedStatic2()
{
	if (!m_bReadOnly)
	{
		UpdateData(TRUE);
		m_pEsamiView->m_pEsamiSet->m_iBreathTestHP = 1;
		UpdateData(FALSE);

		// aggiorno interfaccia //
		OnClickedRadio2();
	}
}