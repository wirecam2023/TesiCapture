#include "stdafx.h"
#include "Endox.h"
#include "InvianteDynFormI.h"

#include "EsamiSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CInvianteDynFormI::CInvianteDynFormI(UINT nID, CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(nID, pParent, pEsamiView)
{
}

CInvianteDynFormI::~CInvianteDynFormI()
{
}

BEGIN_MESSAGE_MAP(CInvianteDynFormI, CEndoxDynForm)
	ON_WM_CTLCOLOR()

	ON_EN_SETFOCUS(IDC_EDIT_REPARTO, OnEnSetfocusEditReparto)
	ON_CBN_SETFOCUS(IDC_COMBO_REPARTO, OnCbnSetfocusComboReparto)
END_MESSAGE_MAP()

void CInvianteDynFormI::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[edt_inviante_i] == NULL)
	{
		pEsamiView->m_pDynForm[edt_inviante_i] = new CInvianteDynFormI(CInvianteDynFormI::IDD, NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[edt_inviante_i] != NULL)
		{
			pEsamiView->m_pDynForm[edt_inviante_i]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[edt_inviante_i]->m_lColore = lColore;
			pEsamiView->m_pDynForm[edt_inviante_i]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[edt_inviante_i]->CreateChildForm(CInvianteDynFormI::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CInvianteDynFormI::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

		case IDC_COMBO_REPARTO:
		case IDC_EDIT_REPARTO:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

void CInvianteDynFormI::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_REPARTO, m_ctrlComboReparto);
	DDX_Control(pDX, IDC_EDIT_REPARTO, m_ctrlEditReparto);

	// Sandro 04/11/2014 //
	if ((m_pEsamiView->m_pEsamiSet->m_lProvenienza == INTERNO) || (m_pEsamiView->m_pEsamiSet->m_lProvenienza == ESTERNO))
		DDX_FieldInviantiCombo(pDX, IDC_COMBO_REPARTO, m_pEsamiView->m_pEsamiSet->m_lInviante, m_pEsamiView->m_pEsamiSet, m_pEsamiView->m_pEsamiSet->m_lProvenienza);
	else
		m_ctrlComboReparto.SetCurSel(-1);

	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		DDX_Text(pDX, IDC_EDIT_REPARTO, m_ctrlEditReparto.m_strRicercaView);
	}
	else
	{
		// Sandro 04/11/2014 //
		if ((m_pEsamiView->m_pEsamiSet->m_lProvenienza == INTERNO) || (m_pEsamiView->m_pEsamiSet->m_lProvenienza == ESTERNO))
			DDX_FieldInviantiEdit(pDX, IDC_EDIT_REPARTO, m_pEsamiView->m_pEsamiSet->m_lInviante, m_pEsamiView->m_pEsamiSet, m_pEsamiView->m_pEsamiSet->m_lProvenienza);
		else
			SetDlgItemText(IDC_EDIT_REPARTO, "");
	}
}

BOOL CInvianteDynFormI::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_LABEL, CSize(0,50), CSize(100,50));
	AddAnchor(IDC_COMBO_REPARTO, CSize(0,50), CSize(100,50));
	AddAnchor(IDC_EDIT_REPARTO, CSize(0,50), CSize(100,50));

	m_ctrlComboReparto.SetParam(m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lInviante, &m_pEsamiView->m_pEsamiSet->m_lProvenienza);
	m_ctrlEditReparto.SetParam(this, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lInviante);

	return bReturn;
}

LRESULT CInvianteDynFormI::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CInvianteDynFormI::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(FALSE);
}

LRESULT CInvianteDynFormI::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	if (((BOOL)wParam == FALSE) && ((theApp.m_nProgramMode & ADD_RECORD_ESAMI) || (theApp.m_nProgramMode & MODIFY_RECORD_ESAMI)))
	{
		GetDlgItem(IDC_COMBO_REPARTO)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_REPARTO)->ShowWindow(SW_HIDE);
	}
	else 
	{
		GetDlgItem(IDC_EDIT_REPARTO)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_REPARTO)->ShowWindow(SW_HIDE);
	}

	// cambio l'etichetta //
	SetDlgItemText(IDC_LABEL, theApp.GetMessageString(IDS_MEDICOINVIANTE1));

	GetDlgItem(IDC_COMBO_REPARTO)->EnableWindow(!(BOOL)wParam);
	SendDlgItemMessage(IDC_EDIT_REPARTO, EM_SETREADONLY, wParam, lParam);

	return 1;
}

LRESULT CInvianteDynFormI::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	m_ctrlEditReparto.m_strRicerca = "";
	m_ctrlEditReparto.m_strRicercaView = "";

	return 1;
}

LRESULT CInvianteDynFormI::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT CInvianteDynFormI::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	ComponiRicercaEx(pStrWhere, m_ctrlEditReparto.m_strRicerca, "EEsami.Inviante", TRUE, TRUE);

	return 1;
}

long CInvianteDynFormI::GetContenuto()
{
	return edt_inviante_i;
}

BOOL CInvianteDynFormI::CampoObbligatorioValido()
{
	CString strTemp = "";

	if (m_pEsamiView->m_bEsamiBusy)
		m_ctrlComboReparto.GetWindowText(strTemp);
	else
		m_ctrlEditReparto.GetWindowText(strTemp);

	return !strTemp.IsEmpty();
}

void CInvianteDynFormI::OnEnSetfocusEditReparto()
{
	if (!GetDlgItem(IDC_EDIT_REPARTO)->IsWindowVisible())
		GetDlgItem(IDC_COMBO_REPARTO)->SetFocus();
}

void CInvianteDynFormI::OnCbnSetfocusComboReparto()
{
	if (!GetDlgItem(IDC_COMBO_REPARTO)->IsWindowVisible())
		GetDlgItem(IDC_EDIT_REPARTO)->SetFocus();
}
