#include "stdafx.h"
#include "Endox.h"
#include "InvianteDynForm1.h"

#include "EsamiView.h"
#include "EsamiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CInvianteDynForm1::CInvianteDynForm1(UINT nID, CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(nID, pParent, pEsamiView)
{
}

CInvianteDynForm1::~CInvianteDynForm1()
{
}

BEGIN_MESSAGE_MAP(CInvianteDynForm1, CEndoxDynForm)
	ON_WM_CTLCOLOR()

	// ON_EN_SETFOCUS(IDC_EDIT_REPARTO, OnEnSetfocusEditReparto)
	// ON_CBN_SETFOCUS(IDC_COMBO_REPARTO, OnCbnSetfocusComboReparto)
END_MESSAGE_MAP()

void CInvianteDynForm1::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[edt_inviante1] == NULL)
	{
		pEsamiView->m_pDynForm[edt_inviante1] = new CInvianteDynForm1(CInvianteDynForm1::IDD, NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[edt_inviante1] != NULL)
		{
			pEsamiView->m_pDynForm[edt_inviante1]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[edt_inviante1]->m_lColore = lColore;
			pEsamiView->m_pDynForm[edt_inviante1]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[edt_inviante1]->CreateChildForm(CInvianteDynForm1::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CInvianteDynForm1::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

		case IDC_EDIT_OSPEDALE:
		case IDC_EDIT_COMUNE:
		case IDC_COMBO_COMUNE:
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

void CInvianteDynForm1::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	if (m_pEsamiView->m_pEsamiSet->m_lProvenienza == ESTERNO)
		SetDlgItemText(IDC_LABEL, theApp.GetMessageString(IDS_CMB_INVIANTE_ESTERNO));
	else
		SetDlgItemText(IDC_LABEL, theApp.GetMessageString(IDS_CMB_INVIANTE_INTERNO));

	DDX_Control(pDX, IDC_EDIT_OSPEDALE, m_ctrlEditOspedale);

	DDX_Control(pDX, IDC_EDIT_COMUNE, m_ctrlEditComune);
	DDX_Control(pDX, IDC_COMBO_COMUNE, m_ctrlComboComune);

	if ((!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lProvenienza)) && (m_pEsamiView->m_pEsamiSet->m_lProvenienza == ESTERNO))
	{
		DDX_FieldInviantiCombo(pDX, IDC_COMBO_COMUNE, m_pEsamiView->m_pEsamiSet->m_lInviante, m_pEsamiView->m_pEsamiSet, m_pEsamiView->m_pEsamiSet->m_lProvenienza);
		if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
			DDX_Text(pDX, IDC_EDIT_COMUNE, m_ctrlEditComune.m_strRicercaView);
		else
			DDX_FieldInviantiEdit(pDX, IDC_EDIT_COMUNE, m_pEsamiView->m_pEsamiSet->m_lInviante, m_pEsamiView->m_pEsamiSet, m_pEsamiView->m_pEsamiSet->m_lProvenienza);
	}
	else
	{
		GetDlgItem(IDC_EDIT_COMUNE)->SetWindowText("");
	}

	//Questo pezzo di codice non è meglio metterlo dentro l'else??
	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		if (m_pEsamiView->m_pEsamiSet->m_lProvenienza == ESTERNO)
			DDX_Text(pDX, IDC_EDIT_COMUNE, m_ctrlEditComune.m_strRicercaView);
		else
			DDX_Text(pDX, IDC_EDIT_OSPEDALE, m_ctrlEditOspedale.m_strRicercaView);
	}
	else
	{
		DDX_FieldCombo(pDX, IDC_EDIT_OSPEDALE, m_pEsamiView->m_pEsamiSet->m_lOspedale, m_pEsamiView->m_pEsamiSet, CMB_ESA_OSPEDALE);
	}
}

BOOL CInvianteDynForm1::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_LABEL, CSize(0,50), CSize(100,50));
	AddAnchor(IDC_EDIT_OSPEDALE, CSize(0,50), CSize(100,50));
	AddAnchor(IDC_COMBO_COMUNE, CSize(0,50), CSize(100,50));
	AddAnchor(IDC_EDIT_COMUNE, CSize(0,50), CSize(100,50));
	AddAnchor(IDC_COMBO_REPARTO, CSize(0,50), CSize(100,50));
	AddAnchor(IDC_EDIT_REPARTO, CSize(0,50), CSize(100,50));

	if (m_pEsamiView->m_pEsamiSet->m_lProvenienza == ESTERNO)
		SetDlgItemText(IDC_LABEL, theApp.GetMessageString(IDS_CMB_INVIANTE_ESTERNO));
	else
		SetDlgItemText(IDC_LABEL, theApp.GetMessageString(IDS_CMB_INVIANTE_INTERNO));

	m_ctrlEditOspedale.SetParam(this, CMB_ESA_OSPEDALE, m_pEsamiView->m_pEsamiSet,	&m_pEsamiView->m_pEsamiSet->m_lIDEsame, &m_pEsamiView->m_pEsamiSet->m_lOspedale, 255);
	m_ctrlEditOspedale.SetParam(TRUE, FALSE, FALSE, TRUE, FALSE);		

	m_ctrlComboComune.SetParam(m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lInviante, &m_pEsamiView->m_pEsamiSet->m_lProvenienza);
	m_ctrlEditComune.SetParam(this, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_lInviante);

	return bReturn;
}

LRESULT CInvianteDynForm1::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CInvianteDynForm1::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(FALSE);
}

LRESULT CInvianteDynForm1::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	switch(m_pEsamiView->m_pEsamiSet->m_lProvenienza)
	{
		case INTERNO: // mostro l'ospedale nascondo il comune //
		{
			GetDlgItem(IDC_EDIT_OSPEDALE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_REPARTO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_REPARTO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO_COMUNE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_COMUNE)->ShowWindow(SW_HIDE);

			break;
		}
		case ESTERNO: // mostro il comune nascondo l'ospedale //
		{
			if (((BOOL)wParam == FALSE) && ((theApp.m_nProgramMode & ADD_RECORD_ESAMI) || (theApp.m_nProgramMode & MODIFY_RECORD_ESAMI)))
			{
				GetDlgItem(IDC_COMBO_COMUNE)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_EDIT_COMUNE)->ShowWindow(SW_HIDE);
			}
			else 
			{
				GetDlgItem(IDC_COMBO_COMUNE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_EDIT_COMUNE)->ShowWindow(SW_SHOW);
			}
			GetDlgItem(IDC_EDIT_OSPEDALE)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO_REPARTO)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_REPARTO)->ShowWindow(SW_HIDE);

			break;
		}
	}

	SendDlgItemMessage(IDC_EDIT_OSPEDALE, EM_SETREADONLY, wParam, lParam);
	GetDlgItem(IDC_COMBO_COMUNE)->EnableWindow(!(BOOL)wParam);
	SendDlgItemMessage(IDC_EDIT_COMUNE, EM_SETREADONLY, wParam, lParam);
	GetDlgItem(IDC_COMBO_REPARTO)->EnableWindow(!(BOOL)wParam);
	SendDlgItemMessage(IDC_EDIT_REPARTO, EM_SETREADONLY, wParam, lParam);

	return 1;
}

LRESULT CInvianteDynForm1::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	m_ctrlEditOspedale.m_strRicerca = "";
	m_ctrlEditOspedale.m_strRicercaView = "";

	return 1;
}

LRESULT CInvianteDynForm1::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT CInvianteDynForm1::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	switch(m_pEsamiView->m_pEsamiSet->m_lProvenienza)
	{
		case INTERNO:
		{
			ComponiRicercaRadioEx(pStrWhere, m_ctrlEditOspedale.m_strRicerca, "EEsami.Ospedale");
			break;
		}
		case ESTERNO:
		{
			ComponiRicercaRadioEx(pStrWhere, m_ctrlEditComune.m_strRicerca, "EEsami.Inviante");
			break;
		}
	}

	return 1;
}

long CInvianteDynForm1::GetContenuto()
{
	return edt_inviante1;
}

BOOL CInvianteDynForm1::CampoObbligatorioValido()
{
	CString strTemp = "";

	switch(m_pEsamiView->m_pEsamiSet->m_lProvenienza)
	{
		case INTERNO:
		{
			m_ctrlEditOspedale.GetWindowText(strTemp);
			break;
		}
		case ESTERNO:
		{
			if (m_pEsamiView->m_bEsamiBusy)
				m_ctrlComboComune.GetWindowText(strTemp);
			else
				m_ctrlEditComune.GetWindowText(strTemp);
			break;
		}
	}

	return !strTemp.IsEmpty();
}