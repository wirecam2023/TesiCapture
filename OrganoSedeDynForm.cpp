#include "stdafx.h"
#include "Endox.h"
#include "OrganoSedeDynForm.h"

#include "EsamiView.h"
#include "EsamiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

COrganoSedeDynForm::COrganoSedeDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView, long lContenuto)
	: CEndoxDynForm(nID, pParent, pEsamiView)
{
	m_lContenuto = lContenuto;
}

COrganoSedeDynForm::~COrganoSedeDynForm()
{
}

BEGIN_MESSAGE_MAP(COrganoSedeDynForm, CEndoxDynForm)
	ON_WM_CTLCOLOR()

	ON_MESSAGE(MSG_EDIT_UPDATED, OnMessageEditUpdated)
END_MESSAGE_MAP()

void COrganoSedeDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lContenuto, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[lContenuto] == NULL)
	{
		pEsamiView->m_pDynForm[lContenuto] = new COrganoSedeDynForm(COrganoSedeDynForm::IDD, NULL, pEsamiView, lContenuto);
		if (pEsamiView->m_pDynForm[lContenuto] != NULL)
		{
			pEsamiView->m_pDynForm[lContenuto]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[lContenuto]->m_lColore = lColore;
			pEsamiView->m_pDynForm[lContenuto]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[lContenuto]->CreateChildForm(COrganoSedeDynForm::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH COrganoSedeDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

		case IDC_EDIT_ORGANOSEDE:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

void COrganoSedeDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_ORGANOSEDE, m_ctrlEditOrganoSede);

	switch(m_lContenuto)
	{
		case edt_organosedeprevista:
		{
			GetDlgItem(IDC_LABEL)->SetWindowText(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_479));
			break;
		}
		case edt_organosederaggiunta:
		{
			GetDlgItem(IDC_LABEL)->SetWindowText(theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_480));
			break;
		}
	}

	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
	{
		CString temp;
		m_ctrlEditOrganoSede.GetWindowText(temp);
		DDX_Text(pDX, IDC_EDIT_ORGANOSEDE, temp);
	}
	else
	{
		switch(m_lContenuto)
		{
			case edt_organosedeprevista:
			{
				DDX_FieldText(pDX, IDC_EDIT_ORGANOSEDE, m_pEsamiView->m_pEsamiSet->m_sSedePrevista, m_pEsamiView->m_pEsamiSet->GetRecordset());
				//Gli ID delle sedi servono per gli interfacciamenti, NON RIMUOVERE!
				if (pDX->m_bSaveAndValidate)
					m_pEsamiView->m_pEsamiSet->m_lIDSedePrevista = m_ctrlEditOrganoSede.m_lIDSede;
				else
					m_ctrlEditOrganoSede.m_lIDSede = m_pEsamiView->m_pEsamiSet->m_lIDSedePrevista;
				break;
			}
			case edt_organosederaggiunta:
			{
				DDX_FieldText(pDX, IDC_EDIT_ORGANOSEDE, m_pEsamiView->m_pEsamiSet->m_sSedeRaggiunta, m_pEsamiView->m_pEsamiSet->GetRecordset());
				//Gli ID delle sedi servono per gli interfacciamenti, NON RIMUOVERE!
				if (pDX->m_bSaveAndValidate)
					m_pEsamiView->m_pEsamiSet->m_lIDSedeRaggiunta = m_ctrlEditOrganoSede.m_lIDSede;
				else
					m_ctrlEditOrganoSede.m_lIDSede = m_pEsamiView->m_pEsamiSet->m_lIDSedeRaggiunta;
				break;
			}
		}
	}
}

BOOL COrganoSedeDynForm::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_LABEL, CSize(0,50), CSize(100,50));
	AddAnchor(IDC_EDIT_ORGANOSEDE, CSize(0,50), CSize(100,50));

	m_ctrlEditOrganoSede.SetParam(m_pEsamiView, GetDlgItem(IDC_EDIT_ORGANOSEDE), GetDlgItem(IDC_EDIT_ORGANOSEDE), this);
	
	return bReturn;
}

LRESULT COrganoSedeDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT COrganoSedeDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(FALSE);
}

LRESULT COrganoSedeDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	SendDlgItemMessage(IDC_EDIT_ORGANOSEDE, EM_SETREADONLY, wParam, lParam);

	return 1;
}

LRESULT COrganoSedeDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	m_ctrlEditOrganoSede.SetWindowText("");

	return 1;
}

LRESULT COrganoSedeDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT COrganoSedeDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	CString temp;
	m_ctrlEditOrganoSede.GetWindowText(temp);

	switch(m_lContenuto)
	{
		case edt_organosedeprevista:
		{
			ComponiRicercaEx(pStrWhere, temp, "EEsami.SedePrevista", TRUE, FALSE);
			break;
		}
		case edt_organosederaggiunta:
		{
			ComponiRicercaEx(pStrWhere, temp, "EEsami.SedeRaggiunta", TRUE, FALSE);
			break;
		}
	}

	return 1;
}

long COrganoSedeDynForm::GetContenuto()
{
	return m_lContenuto;
}

BOOL COrganoSedeDynForm::CampoObbligatorioValido()
{
	CString strTemp = "";
	m_ctrlEditOrganoSede.GetWindowText(strTemp);

	return !strTemp.IsEmpty();
}

LRESULT COrganoSedeDynForm::OnMessageEditUpdated(WPARAM wParam, LPARAM lParam)
{
	if (m_lContenuto == edt_organosedeprevista)
	{
		COrganoSedeDynForm* pForm = (COrganoSedeDynForm*)m_pEsamiView->m_pDynForm[edt_organosederaggiunta];

		if (pForm != NULL)
		{
			CString strEdit;
			GetDlgItemText(IDC_EDIT_ORGANOSEDE, strEdit);
			pForm->SetEditText(strEdit);
		}
	}

	return 0;
}

void COrganoSedeDynForm::SetEditText(CString strEdit)
{
	CString strTemp;
	GetDlgItemText(IDC_EDIT_ORGANOSEDE, strTemp);
	strTemp.Trim();

	if (strTemp.IsEmpty())
		SetDlgItemText(IDC_EDIT_ORGANOSEDE, strEdit);
}