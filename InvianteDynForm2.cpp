#include "stdafx.h"
#include "Endox.h"
#include "InvianteDynForm2.h"

#include "EsamiView.h"
#include "EsamiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CInvianteDynForm2::CInvianteDynForm2(UINT nID, CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(nID, pParent, pEsamiView)
{
}

CInvianteDynForm2::~CInvianteDynForm2()
{
}

BEGIN_MESSAGE_MAP(CInvianteDynForm2, CEndoxDynForm)
	ON_WM_CTLCOLOR()

	ON_EN_SETFOCUS(IDC_EDIT_REPARTO, OnEnSetfocusEditReparto)
	ON_CBN_SETFOCUS(IDC_COMBO_REPARTO, OnCbnSetfocusComboReparto)
END_MESSAGE_MAP()

void CInvianteDynForm2::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[edt_inviante2] == NULL)
	{
		pEsamiView->m_pDynForm[edt_inviante2] = new CInvianteDynForm2(CInvianteDynForm2::IDD, NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[edt_inviante2] != NULL)
		{
			pEsamiView->m_pDynForm[edt_inviante2]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[edt_inviante2]->m_lColore = lColore;
			pEsamiView->m_pDynForm[edt_inviante2]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[edt_inviante2]->CreateChildForm(CInvianteDynForm2::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CInvianteDynForm2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
		case IDC_EDIT_MEDICO:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

void CInvianteDynForm2::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_REPARTO, m_ctrlComboReparto);
	DDX_Control(pDX, IDC_EDIT_REPARTO, m_ctrlEditReparto);
	DDX_Control(pDX, IDC_EDIT_MEDICO, m_ctrlEditMedicoCurante);

	if ((!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lProvenienza)) && (m_pEsamiView->m_pEsamiSet->m_lProvenienza == INTERNO))
	{
		DDX_FieldInviantiCombo(pDX, IDC_COMBO_REPARTO, m_pEsamiView->m_pEsamiSet->m_lInviante, m_pEsamiView->m_pEsamiSet, m_pEsamiView->m_pEsamiSet->m_lProvenienza);
		if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
			DDX_Text(pDX, IDC_EDIT_REPARTO, m_ctrlEditReparto.m_strRicercaView);
		else
			DDX_FieldInviantiEdit(pDX, IDC_EDIT_REPARTO, m_pEsamiView->m_pEsamiSet->m_lInviante, m_pEsamiView->m_pEsamiSet, m_pEsamiView->m_pEsamiSet->m_lProvenienza);
	}
	else
	{
		GetDlgItem(IDC_EDIT_REPARTO)->SetWindowText("");
	}

	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		DDX_Text(pDX, IDC_EDIT_MEDICO, m_ctrlEditMedicoCurante.m_strRicercaView);
	}
	else
	{
		DDX_FieldText(pDX, IDC_EDIT_MEDICO, m_pEsamiView->m_pEsamiSet->m_sInvMedico, m_pEsamiView->m_pEsamiSet->GetRecordset());
		DDX_FieldText(pDX, IDC_EDIT_MEDICOID, m_pEsamiView->m_pEsamiSet->m_lInvMedico, m_pEsamiView->m_pEsamiSet->GetRecordset());
	}

	//if (pDX->m_bSaveAndValidate)
		//m_pEsamiView->m_pEsamiSet->m_lInvMedico = m_ctrlEditMedicoCurante.m_lIDMedico;
}

BOOL CInvianteDynForm2::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_LABEL, CSize(0,50), CSize(100,50));
	AddAnchor(IDC_COMBO_REPARTO, CSize(0,50), CSize(100,50));
	AddAnchor(IDC_EDIT_REPARTO, CSize(0,50), CSize(100,50));
	AddAnchor(IDC_EDIT_MEDICO, CSize(0,50), CSize(100,50));

	m_ctrlComboReparto.SetParam(m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lInviante, &m_pEsamiView->m_pEsamiSet->m_lProvenienza);
	m_ctrlEditReparto.SetParam(this, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lInviante);

	m_ctrlEditMedicoCurante.SetParams(this, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sInvMedico, &m_pEsamiView->m_pEsamiSet->m_lInvMedico, 3999, 2, MEDICI_CURANTI);

	return bReturn;
}

LRESULT CInvianteDynForm2::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CInvianteDynForm2::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(FALSE);
}

LRESULT CInvianteDynForm2::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	// Sandro 13/09/2013 //
	BOOL bReadOnlyEditMedico = (BOOL)wParam;

	//
	switch(m_pEsamiView->m_pEsamiSet->m_lProvenienza)
	{
		case INTERNO: // mostro il reparto inviante nascondo il medico //
		{
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
			GetDlgItem(IDC_EDIT_MEDICO)->ShowWindow(SW_HIDE);

			// cambio l'etichetta //
			SetDlgItemText(IDC_LABEL, theApp.GetMessageString(IDS_MEDICOINVIANTE1));

			break;
		}
		case ESTERNO: // mostro il medico inviante nascondo il reparto //
		{
			GetDlgItem(IDC_EDIT_MEDICO)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_REPARTO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_REPARTO)->ShowWindow(SW_HIDE);

			// cambio l'etichetta //
			SetDlgItemText(IDC_LABEL, theApp.GetMessageString(IDS_MEDICOINVIANTE2));

			break;
		}
	}

	GetDlgItem(IDC_COMBO_REPARTO)->EnableWindow(!(BOOL)wParam);
	SendDlgItemMessage(IDC_EDIT_REPARTO, EM_SETREADONLY, wParam, lParam);
	SendDlgItemMessage(IDC_EDIT_MEDICO, EM_SETREADONLY, bReadOnlyEditMedico, lParam);

	return 1;
}

LRESULT CInvianteDynForm2::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	m_ctrlEditReparto.m_strRicerca = "";
	m_ctrlEditReparto.m_strRicercaView = "";

	m_ctrlEditMedicoCurante.m_strRicerca = "";
	m_ctrlEditMedicoCurante.m_strRicercaView = "";

	return 1;
}

LRESULT CInvianteDynForm2::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT CInvianteDynForm2::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	switch(m_pEsamiView->m_pEsamiSet->m_lProvenienza)
	{
		case INTERNO:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlEditReparto.m_strRicerca, "EEsami.Inviante", TRUE, TRUE);
			break;
		}
		case ESTERNO:
		{
			ComponiRicercaEx(pStrWhere, m_ctrlEditMedicoCurante.m_strRicercaView, "EEsami.InvMedico", TRUE, FALSE);
			break;
		}
	}

	return 1;
}

long CInvianteDynForm2::GetContenuto()
{
	return edt_inviante2;
}

BOOL CInvianteDynForm2::CampoObbligatorioValido()
{
	CString strTemp = "";

	switch(m_pEsamiView->m_pEsamiSet->m_lProvenienza)
	{
		case INTERNO:
		{
			if (m_pEsamiView->m_bEsamiBusy)
				m_ctrlComboReparto.GetWindowText(strTemp);
			else
				m_ctrlEditReparto.GetWindowText(strTemp);
			break;
		}
		case ESTERNO:
		{
			m_ctrlEditMedicoCurante.GetWindowText(strTemp);
			break;
		}
	}

	return !strTemp.IsEmpty();
}

void CInvianteDynForm2::OnEnSetfocusEditReparto()
{
	if (!GetDlgItem(IDC_EDIT_REPARTO)->IsWindowVisible())
		GetDlgItem(IDC_COMBO_REPARTO)->SetFocus();
}

void CInvianteDynForm2::OnCbnSetfocusComboReparto()
{
	if (!GetDlgItem(IDC_COMBO_REPARTO)->IsWindowVisible())
		GetDlgItem(IDC_EDIT_MEDICO)->SetFocus();
}
