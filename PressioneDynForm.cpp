#include "stdafx.h"
#include "Endox.h"
#include "PressioneDynForm.h"

#include "EsamiSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPressioneDynForm::CPressioneDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(nID, pParent, pEsamiView)
{
}

CPressioneDynForm::~CPressioneDynForm()
{
}

BEGIN_MESSAGE_MAP(CPressioneDynForm, CEndoxDynForm)
	ON_WM_CTLCOLOR()

	ON_EN_KILLFOCUS(IDC_EDIT_PRESS1, OnEnKillfocusEditPress1)
	ON_EN_KILLFOCUS(IDC_EDIT_PRESS2, OnEnKillfocusEditPress2)
END_MESSAGE_MAP()

void CPressioneDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[edt_pressione] == NULL)
	{
		pEsamiView->m_pDynForm[edt_pressione] = new CPressioneDynForm(CPressioneDynForm::IDD, NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[edt_pressione] != NULL)
		{
			pEsamiView->m_pDynForm[edt_pressione]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[edt_pressione]->m_lColore = lColore;
			pEsamiView->m_pDynForm[edt_pressione]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[edt_pressione]->CreateChildForm(CPressioneDynForm::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CPressioneDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
		case IDC_STATIC_00:
		case IDC_EDIT_PRESS1:
		case IDC_EDIT_PRESS2:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

void CPressioneDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		// DDX_Text(pDX, IDC_EDIT_MEDICO, m_ctrlEditMedicoCurante.m_strRicercaView);
	}
	else
	{
		DDX_FieldText(pDX, IDC_EDIT_PRESS1, m_pEsamiView->m_pEsamiSet->m_sPressione1, m_pEsamiView->m_pEsamiSet->GetRecordset());
		DDX_FieldText(pDX, IDC_EDIT_PRESS2, m_pEsamiView->m_pEsamiSet->m_sPressione2, m_pEsamiView->m_pEsamiSet->GetRecordset());
	}
}

BOOL CPressioneDynForm::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_LABEL, CSize(0,50), CSize(100,50));
	AddAnchor(IDC_EDIT_PRESS1, CSize(0,50), CSize(50,50));
	AddAnchor(IDC_STATIC_00, CSize(50,50), CSize(50,50));
	AddAnchor(IDC_EDIT_PRESS2, CSize(50,50), CSize(100,50));

	return bReturn;
}

LRESULT CPressioneDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CPressioneDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(FALSE);
}

LRESULT CPressioneDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	SendDlgItemMessage(IDC_EDIT_PRESS1, EM_SETREADONLY, wParam, lParam);
	SendDlgItemMessage(IDC_EDIT_PRESS2, EM_SETREADONLY, wParam, lParam);

	return 1;
}

LRESULT CPressioneDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	/*
	m_ctrlEditMedicoCurante.m_strRicerca = "";
	m_ctrlEditMedicoCurante.m_strRicercaView = "";
	*/

	return 1;
}

LRESULT CPressioneDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT CPressioneDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	// ComponiRicercaEx(pStrWhere, m_ctrlEditMedicoCurante.m_strRicercaView, "EEsami.InvMedico", TRUE, FALSE);

	return 1;
}

long CPressioneDynForm::GetContenuto()
{
	return edt_pressione;
}

BOOL CPressioneDynForm::CampoObbligatorioValido()
{
	CString strTemp1 = "";
	CString strTemp2 = "";

	GetDlgItemText(IDC_EDIT_PRESS1, strTemp1);
	GetDlgItemText(IDC_EDIT_PRESS2, strTemp2);

	return (!strTemp1.IsEmpty() && !strTemp2.IsEmpty());
}

void CPressioneDynForm::OnEnKillfocusEditPress1()
{
	CString sPress1;
	GetDlgItemText(IDC_EDIT_PRESS1, sPress1);
	sPress1.Trim();

	if (!sPress1.IsEmpty())
	{
		long lPress1 = GetDlgItemInt(IDC_EDIT_PRESS1);

		if (lPress1 < theApp.m_lPressioneMassimaValoreMinimo)
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PRESSIONE_MASSIMA_TROPPOBASSA));
			GetDlgItem(IDC_EDIT_PRESS1)->SetFocus();
			return;
		}

		if (lPress1 > theApp.m_lPressioneMassimaValoreMassimo)
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PRESSIONE_MASSIMA_TROPPOALTA));
			GetDlgItem(IDC_EDIT_PRESS1)->SetFocus();
			return;
		}
	}
}

void CPressioneDynForm::OnEnKillfocusEditPress2()
{
	CString sPress2;
	GetDlgItemText(IDC_EDIT_PRESS2, sPress2);
	sPress2.Trim();

	if (!sPress2.IsEmpty())
	{
		long lPress2 = GetDlgItemInt(IDC_EDIT_PRESS2);

		if (lPress2 < theApp.m_lPressioneMinimaValoreMinimo)
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PRESSIONE_MINIMA_TROPPOBASSA));
			GetDlgItem(IDC_EDIT_PRESS2)->SetFocus();
			return;
		}

		if (lPress2 > theApp.m_lPressioneMinimaValoreMassimo)
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PRESSIONE_MINIMA_TROPPOALTA));
			GetDlgItem(IDC_EDIT_PRESS2)->SetFocus();
			return;
		}
	}
}
