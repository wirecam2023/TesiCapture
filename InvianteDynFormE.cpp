#include "stdafx.h"
#include "Endox.h"
#include "InvianteDynFormE.h"

#include "EsamiSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CInvianteDynFormE::CInvianteDynFormE(UINT nID, CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(nID, pParent, pEsamiView)
{
}

CInvianteDynFormE::~CInvianteDynFormE()
{
}

BEGIN_MESSAGE_MAP(CInvianteDynFormE, CEndoxDynForm)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

void CInvianteDynFormE::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[edt_inviante_e] == NULL)
	{
		pEsamiView->m_pDynForm[edt_inviante_e] = new CInvianteDynFormE(CInvianteDynFormE::IDD, NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[edt_inviante_e] != NULL)
		{
			pEsamiView->m_pDynForm[edt_inviante_e]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[edt_inviante_e]->m_lColore = lColore;
			pEsamiView->m_pDynForm[edt_inviante_e]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[edt_inviante_e]->CreateChildForm(CInvianteDynFormE::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CInvianteDynFormE::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
		case IDC_EDIT_MEDICO:
		case IDC_EDIT_MEDICO_SEARCH:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

void CInvianteDynFormE::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_MEDICO, m_ctrlEditMedicoCurante);

	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		DDX_Text(pDX, IDC_EDIT_MEDICO, m_ctrlEditMedicoCurante.m_strRicercaView);
	}
	else
	{
		DDX_FieldText(pDX, IDC_EDIT_MEDICO, m_pEsamiView->m_pEsamiSet->m_sInvMedico, m_pEsamiView->m_pEsamiSet->GetRecordset());
		DDX_FieldText(pDX, IDC_EDIT_MEDICOID, m_pEsamiView->m_pEsamiSet->m_lInvMedico, m_pEsamiView->m_pEsamiSet->GetRecordset());
	}
}

BOOL CInvianteDynFormE::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_LABEL, CSize(0, 50), CSize(100, 50));
	AddAnchor(IDC_EDIT_MEDICO, CSize(0, 50), CSize(100, 50));
	AddAnchor(IDC_EDIT_MEDICO_SEARCH, CSize(0, 50), CSize(100, 50));

	m_ctrlEditMedicoCurante.SetParams(this, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sInvMedico, &m_pEsamiView->m_pEsamiSet->m_lInvMedico, 3999, 2, MEDICI_CURANTI);

	SetDlgItemText(IDC_LABEL, theApp.GetMessageString(IDS_MEDICOINVIANTE2));

	return bReturn;
}

LRESULT CInvianteDynFormE::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CInvianteDynFormE::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(FALSE);
}

LRESULT CInvianteDynFormE::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	SendDlgItemMessage(IDC_EDIT_MEDICO, EM_SETREADONLY, wParam, lParam);

	if ((theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && theApp.m_bPersonalizzazioniBrasileSirio)
	{
		GetDlgItem(IDC_EDIT_MEDICO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_MEDICO_SEARCH)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_EDIT_MEDICO)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_MEDICO_SEARCH)->ShowWindow(SW_HIDE);
	}

	return 1;
}

LRESULT CInvianteDynFormE::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	m_ctrlEditMedicoCurante.m_strRicerca = "";
	m_ctrlEditMedicoCurante.m_strRicercaView = "";

	SetDlgItemText(IDC_EDIT_MEDICO_SEARCH, "");

	return 1;
}

LRESULT CInvianteDynFormE::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT CInvianteDynFormE::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	if (theApp.m_bPersonalizzazioniBrasileSirio)
	{
		CString sSearch;
		GetDlgItemText(IDC_EDIT_MEDICO_SEARCH, sSearch);
		sSearch.Trim();

		ComponiRicercaEx(pStrWhere, sSearch, "EEsami.InvMedico", TRUE, FALSE);
	}
	else
	{
		ComponiRicercaEx(pStrWhere, m_ctrlEditMedicoCurante.m_strRicercaView, "EEsami.InvMedico", TRUE, FALSE);
	}

	return 1;
}

long CInvianteDynFormE::GetContenuto()
{
	return edt_inviante_e;
}

BOOL CInvianteDynFormE::CampoObbligatorioValido()
{
	CString strTemp = "";

	m_ctrlEditMedicoCurante.GetWindowText(strTemp);

	return !strTemp.IsEmpty();
}