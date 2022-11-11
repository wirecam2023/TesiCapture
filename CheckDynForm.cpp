#include "stdafx.h"
#include "Endox.h"
#include "CheckDynForm.h"

#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CCheckDynForm::CCheckDynForm(CWnd* pParent, CEsamiView* pEsamiView, long lContenuto)
	: CEndoxDynForm(CCheckDynForm::IDD, pParent, pEsamiView)
{
	m_bReadOnly = TRUE;
	m_lContenuto = lContenuto;
}

CCheckDynForm::~CCheckDynForm()
{
}

BEGIN_MESSAGE_MAP(CCheckDynForm, CEndoxDynForm)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

void CCheckDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lContenuto, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[lContenuto] == NULL)
	{
		pEsamiView->m_pDynForm[lContenuto] = new CCheckDynForm(NULL, pEsamiView, lContenuto);
		if (pEsamiView->m_pDynForm[lContenuto] != NULL)
		{
			pEsamiView->m_pDynForm[lContenuto]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[lContenuto]->m_lColore = lColore;
			pEsamiView->m_pDynForm[lContenuto]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[lContenuto]->CreateChildForm(CCheckDynForm::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CCheckDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_1:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

void CCheckDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	switch(m_lContenuto)
	{
		case sub_necassospedaliera:
		{
			DDX_FieldCheck(pDX, IDC_CHECK, m_pEsamiView->m_pEsamiSet->m_bNecAssistenzaOspedaliera, m_pEsamiView->m_pEsamiSet->GetRecordset());
			break;
		}
		case sub_presenzalesioneCCR:
		{
			DDX_FieldCheck(pDX, IDC_CHECK, m_pEsamiView->m_pEsamiSet->m_bPresenzaLesioneSospettaCCR, m_pEsamiView->m_pEsamiSet->GetRecordset());			
			break;
		}
	}
}

BOOL CCheckDynForm::OnInitDialog()
{
	CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_STATIC_1, CSize(0,40), CSize(100,50));
	AddAnchor(IDC_CHECK, CSize(100,50), CSize(100,50));

	switch(m_lContenuto)
	{
		case sub_necassospedaliera:
		{
			SetDlgItemText(IDC_STATIC_1, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_363));
			break;
		}
		case sub_presenzalesioneCCR:
		{
			SetDlgItemText(IDC_STATIC_1, theApp.GetMessageString(IDS_FIELDDLG_ENDOX_FIELD_504));
			break;
		}
	}

	return TRUE;
}

LRESULT CCheckDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CCheckDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	m_bReadOnly = (BOOL)wParam;



	return 1;
}

LRESULT CCheckDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{	
	return 1;
}

LRESULT CCheckDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT CCheckDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;
	
	switch(m_lContenuto)
	{
		case sub_necassospedaliera:
		{
			if (!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_bNecAssistenzaOspedaliera))
				ComponiRicercaCheckSND(*pStrWhere, m_pEsamiView->m_pEsamiSet, (long*)&m_pEsamiView->m_pEsamiSet->m_bNecAssistenzaOspedaliera, "EEsami.NecAssistenzaOspedaliera");
			break;
		}
		case sub_presenzalesioneCCR:
		{
			if (!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_bPresenzaLesioneSospettaCCR))
				ComponiRicercaCheckSND(*pStrWhere, m_pEsamiView->m_pEsamiSet, (long*)&m_pEsamiView->m_pEsamiSet->m_bPresenzaLesioneCCR, "EEsami.PresenzaLesioneSospettaCCR");
			break;
		}		
	}

	return 1;
}

long CCheckDynForm::GetContenuto()
{
	return m_lContenuto;
}

BOOL CCheckDynForm::CampoObbligatorioValido()
{
	return(TRUE);
}
