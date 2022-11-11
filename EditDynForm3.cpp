#include "stdafx.h"
#include "Endox.h"
#include "EditDynForm3.h"

#include "Common.h"
#include "EsamiSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEdit CEditDynForm3::m_ctrlDiagnostiche;
CEdit CEditDynForm3::m_ctrlTerapeutiche;
CEdit CEditDynForm3::m_ctrlMstComplicanze1;
CEdit CEditDynForm3::m_ctrlMstComplicanze2;
CEdit CEditDynForm3::m_ctrlMstComplicanze3;

CEditDynForm3::CEditDynForm3(CWnd* pParent, CEsamiView* pEsamiView, long lContenuto)
: CEndoxDynForm(CEditDynForm3::IDD, pParent, pEsamiView)
{
	m_lContenuto = lContenuto;
}

CEditDynForm3::~CEditDynForm3()
{
}

BEGIN_MESSAGE_MAP(CEditDynForm3, CEndoxDynForm)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

void CEditDynForm3::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lContenuto, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[lContenuto] == NULL)
	{
		pEsamiView->m_pDynForm[lContenuto] = new CEditDynForm3(NULL, pEsamiView, lContenuto);
		if (pEsamiView->m_pDynForm[lContenuto] != NULL)
		{
			pEsamiView->m_pDynForm[lContenuto]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[lContenuto]->m_lColore = lColore;
			pEsamiView->m_pDynForm[lContenuto]->m_lIDFaseBlocco = lIDFaseBlocco;

			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[lContenuto]->CreateChildForm(CEditDynForm3::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CEditDynForm3::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_EDIT:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

void CEditDynForm3::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	switch(m_lContenuto)
	{
		case edt_diagnostiche:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlDiagnostiche);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sProcDiagnostiche, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
		case edt_terapeutiche:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlTerapeutiche);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sProcTerapeutiche, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
		case edt_mst_complicanze1:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlMstComplicanze1);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sMstComplicanze1, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
		case edt_mst_complicanze2:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlMstComplicanze2);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sMstComplicanze2, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
		case edt_mst_complicanze3:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlMstComplicanze3);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sMstComplicanze3, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
	}
}

BOOL CEditDynForm3::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(GetDlgItem(IDC_EDIT)->GetSafeHwnd(), CSize(0,0), CSize(100,100));

	return bReturn;
}

LRESULT CEditDynForm3::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CEditDynForm3::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(FALSE);
}

LRESULT CEditDynForm3::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	switch(m_lContenuto)
	{
		case edt_diagnostiche:
		case edt_terapeutiche:
		case edt_mst_complicanze1:
		case edt_mst_complicanze2:
		case edt_mst_complicanze3:
		{
			SendDlgItemMessage(IDC_EDIT, EM_SETREADONLY, wParam, lParam);
			break;
		}
	}

	return 1;
}

LRESULT CEditDynForm3::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT CEditDynForm3::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	switch(m_lContenuto)
	{
		case edt_diagnostiche:
		{
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sProcDiagnostiche, "EEsami.ProcDiagnostiche", 1);
			break;
		}
		case edt_terapeutiche:
		{
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sProcTerapeutiche, "EEsami.ProcTerapeutiche", 1);
			break;
		}
		case edt_mst_complicanze1:
		{
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sMstComplicanze1, "EEsami.MstComplicanze1", 1);
			break;
		}
		case edt_mst_complicanze2:
		{
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sMstComplicanze2, "EEsami.MstComplicanze2", 1);
			break;
		}
		case edt_mst_complicanze3:
		{
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sMstComplicanze3, "EEsami.MstComplicanze3", 1);
			break;
		}
	}

	return 1;
}

long CEditDynForm3::GetContenuto()
{
	return m_lContenuto;
}

BOOL CEditDynForm3::CampoObbligatorioValido()
{
	CString strEdit;
	GetDlgItemText(IDC_EDIT, strEdit);

	if (!strEdit.IsEmpty())
		return TRUE;

	return FALSE;
}