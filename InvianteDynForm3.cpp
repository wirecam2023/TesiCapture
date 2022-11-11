#include "stdafx.h"
#include "Endox.h"
#include "InvianteDynForm3.h"

#include "EsamiView.h"
#include "EsamiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CInvianteDynForm3::CInvianteDynForm3(UINT nID, CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(nID, pParent, pEsamiView)
{
}

CInvianteDynForm3::~CInvianteDynForm3()
{
}

BEGIN_MESSAGE_MAP(CInvianteDynForm3, CEndoxDynForm)
	ON_WM_CTLCOLOR()

	ON_EN_SETFOCUS(IDC_EDIT_INTERNI, OnEnSetfocusEditInterni)
END_MESSAGE_MAP()

void CInvianteDynForm3::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[edt_inviante3] == NULL)
	{
		pEsamiView->m_pDynForm[edt_inviante3] = new CInvianteDynForm3(CInvianteDynForm3::IDD, NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[edt_inviante3] != NULL)
		{
			pEsamiView->m_pDynForm[edt_inviante3]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[edt_inviante3]->m_lColore = lColore;
			pEsamiView->m_pDynForm[edt_inviante3]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[edt_inviante3]->CreateChildForm(CInvianteDynForm3::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CInvianteDynForm3::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_LABEL:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			if (m_crCampoObbligatorio > 0)
				pDC->SetBkColor(m_crCampoObbligatorio);

			break;
		}

		case IDC_EDIT_INTERNI:
		case IDC_EDIT_ESTERNI:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

void CInvianteDynForm3::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LABEL, m_ctrlLabel);
	DDX_Control(pDX, IDC_EDIT_INTERNI, m_ctrlTipoDegenzaInterno);
	DDX_Control(pDX, IDC_EDIT_ESTERNI, m_ctrlTipoDegenzaEsterno);

	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		DDX_Text(pDX, IDC_EDIT_INTERNI, m_ctrlTipoDegenzaInterno.m_strRicercaView);
		DDX_Text(pDX, IDC_EDIT_ESTERNI, m_ctrlTipoDegenzaEsterno.m_strRicercaView);
	}
	else
	{
		DDX_FieldCombo(pDX, IDC_EDIT_INTERNI, m_pEsamiView->m_pEsamiSet->m_lTipoDegenzaInterno, m_pEsamiView->m_pEsamiSet, CMB_ESA_TIPODEGENZAINT);
		DDX_FieldCombo(pDX, IDC_EDIT_ESTERNI, m_pEsamiView->m_pEsamiSet->m_lTipoDegenzaEsterno, m_pEsamiView->m_pEsamiSet, CMB_ESA_TIPODEGENZAEST);
	}
}

BOOL CInvianteDynForm3::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_LABEL, CSize(0,50), CSize(100,50));
	AddAnchor(IDC_EDIT_INTERNI, CSize(0,50), CSize(100,50));
	AddAnchor(IDC_EDIT_ESTERNI, CSize(0,50), CSize(100,50));

	m_ctrlTipoDegenzaInterno.SetParam(this, CMB_ESA_TIPODEGENZAINT, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_lTipoDegenzaInterno, 255);
	m_ctrlTipoDegenzaInterno.SetParam(TRUE, FALSE, FALSE, TRUE, FALSE);

	m_ctrlTipoDegenzaEsterno.SetParam(this, CMB_ESA_TIPODEGENZAEST, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_lTipoDegenzaEsterno, 255);
	m_ctrlTipoDegenzaEsterno.SetParam(TRUE, FALSE, FALSE, TRUE, FALSE);

	theApp.LocalizeDialog(this, CInvianteDynForm3::IDD, "InvianteDynForm3");

	return bReturn;
}

LRESULT CInvianteDynForm3::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CInvianteDynForm3::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(FALSE);
}

LRESULT CInvianteDynForm3::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	switch(m_pEsamiView->m_pEsamiSet->m_lProvenienza)
	{
		case INTERNO:
		{
			// mostro il tipo di degenza interni nascondo esterni //
			GetDlgItem(IDC_EDIT_INTERNI)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_ESTERNI)->ShowWindow(SW_HIDE);

			break;
		}
		case ESTERNO:
		{
			// mostro il tipo di degenza esterni nascondo interni //
			GetDlgItem(IDC_EDIT_ESTERNI)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_INTERNI)->ShowWindow(SW_HIDE);

			break;
		}
	}

	SendDlgItemMessage(IDC_EDIT_INTERNI, EM_SETREADONLY, wParam, lParam);
	SendDlgItemMessage(IDC_EDIT_ESTERNI, EM_SETREADONLY, wParam, lParam);

	return 1;
}

LRESULT CInvianteDynForm3::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	m_ctrlTipoDegenzaInterno.m_strRicerca = "";
	m_ctrlTipoDegenzaInterno.m_strRicercaView = "";

	m_ctrlTipoDegenzaEsterno.m_strRicerca = "";
	m_ctrlTipoDegenzaEsterno.m_strRicercaView = "";

	return 1;
}

LRESULT CInvianteDynForm3::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT CInvianteDynForm3::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	switch(m_pEsamiView->m_pEsamiSet->m_lProvenienza)
	{
		case INTERNO:
		{
			ComponiRicercaRadioEx(pStrWhere, m_ctrlTipoDegenzaInterno.m_strRicerca, "EEsami.TipoDegenzaInterno");
			break;
		}
		case ESTERNO:
		{
			ComponiRicercaRadioEx(pStrWhere, m_ctrlTipoDegenzaEsterno.m_strRicerca, "EEsami.TipoDegenzaEsterno");
			break;
		}
	}

	return 1;
}

long CInvianteDynForm3::GetContenuto()
{
	return edt_inviante3;
}

BOOL CInvianteDynForm3::CampoObbligatorioValido()
{
	CString strTemp = "";

	switch(m_pEsamiView->m_pEsamiSet->m_lProvenienza)
	{
		case INTERNO:
		{
			m_ctrlTipoDegenzaInterno.GetWindowText(strTemp);
			break;
		}
		case ESTERNO:
		{
			m_ctrlTipoDegenzaEsterno.GetWindowText(strTemp);
			break;
		}
	}

	return !strTemp.IsEmpty();
}

void CInvianteDynForm3::OnEnSetfocusEditInterni()
{
	if (!GetDlgItem(IDC_EDIT_INTERNI)->IsWindowVisible())
		GetDlgItem(IDC_EDIT_ESTERNI)->SetFocus();
}
