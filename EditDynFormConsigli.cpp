#include "stdafx.h"
#include "Endox.h"
#include "EditDynFormConsigli.h"

#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CFrasiNewEdit CEditDynFormConsigli::m_ctrlAnatomiaPatologicaSugger1;
CFrasiNewEdit CEditDynFormConsigli::m_ctrlAnatomiaPatologicaSugger2;

CEditDynFormConsigli::CEditDynFormConsigli(CWnd* pParent, CEsamiView* pEsamiView, long lContenuto)
: CEndoxDynForm(CEditDynFormConsigli::IDD, pParent, pEsamiView)
{
	m_lContenuto = lContenuto;
}

CEditDynFormConsigli::~CEditDynFormConsigli()
{
}

BEGIN_MESSAGE_MAP(CEditDynFormConsigli, CEndoxDynForm)

	ON_BN_CLICKED(IDC_BTN_STAMPA, OnBnClickedBtnStampa)

	ON_WM_CTLCOLOR()

END_MESSAGE_MAP()

void CEditDynFormConsigli::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lContenuto, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[lContenuto] == NULL)
	{
		pEsamiView->m_pDynForm[lContenuto] = new CEditDynFormConsigli(NULL, pEsamiView, lContenuto);
		if (pEsamiView->m_pDynForm[lContenuto] != NULL)
		{
			pEsamiView->m_pDynForm[lContenuto]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[lContenuto]->m_lColore = lColore;
			pEsamiView->m_pDynForm[lContenuto]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[lContenuto]->CreateChildForm(CEditDynFormConsigli::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CEditDynFormConsigli::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_TEXT:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			if (m_crCampoObbligatorio > 0)
				pDC->SetBkColor(m_crCampoObbligatorio);

			break;
		}

		case IDC_EDIT:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

void CEditDynFormConsigli::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	switch(m_lContenuto)
	{
		case edt_anatomiapatologicasugger1:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlAnatomiaPatologicaSugger1);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sAPSuggerimenti1, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
		case edt_anatomiapatologicasugger2:
		{
			DDX_Control(pDX, IDC_EDIT, m_ctrlAnatomiaPatologicaSugger2);
			DDX_FieldText(pDX, IDC_EDIT, m_pEsamiView->m_pEsamiSet->m_sAPSuggerimenti2, m_pEsamiView->m_pEsamiSet->GetRecordset());

			break;
		}
	}

	DDX_Control(pDX, IDC_BTN_STAMPA, m_ctrlButtonStampa);
}

BOOL CEditDynFormConsigli::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_TEXT, CSize(0, 0), CSize(100, 0));
	AddAnchor(IDC_EDIT, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDC_BTN_STAMPA, CSize(100, 100), CSize(100, 100));

	switch(m_lContenuto)
	{
		case edt_anatomiapatologicasugger1:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_EDT_SUGGERIMENTIANATOMIA1));
			m_ctrlAnatomiaPatologicaSugger1.SetParam(this, theApp.GetMessageString(IDS_EDT_SUGGERIMENTIANATOMIA1), 0);
			break;
		}
		case edt_anatomiapatologicasugger2:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_EDT_SUGGERIMENTIANATOMIA2));
			m_ctrlAnatomiaPatologicaSugger2.SetParam(this, theApp.GetMessageString(IDS_EDT_SUGGERIMENTIANATOMIA2), 1);
			break;
		}
	}

	theApp.LocalizeDialog(this, CEditDynFormConsigli::IDD, "EditDynFormConsigli");
	return bReturn;
}

LRESULT CEditDynFormConsigli::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CEditDynFormConsigli::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(FALSE);
}

LRESULT CEditDynFormConsigli::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	SendDlgItemMessage(IDC_EDIT, EM_SETREADONLY, wParam, lParam);

	m_ctrlButtonStampa.EnableWindow((BOOL)wParam && (m_pEsamiView->m_bEsamiValid) && (!m_pEsamiView->m_bPazientiBusy) && m_pEsamiView->m_pEsamiSet->m_bStessoDistretto);

	return 1;
}

LRESULT CEditDynFormConsigli::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	UpdateData(TRUE);

	return 1;
}

LRESULT CEditDynFormConsigli::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	switch(m_lContenuto)
	{
		case edt_anatomiapatologicasugger1:
		{
			// ComponiRicerca(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sNoteAnatomiaPatologica, "EEsami.NoteAnatomiaPatologica", 1);
			break;
		}
		case edt_anatomiapatologicasugger2:
		{
			// ComponiRicerca(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sNoteAnatomiaPatologica, "EEsami.NoteAnatomiaPatologica", 1);
			break;
		}
	}

	return 1;
}

long CEditDynFormConsigli::GetContenuto()
{
	return m_lContenuto;
}

BOOL CEditDynFormConsigli::CampoObbligatorioValido()
{
	CString strEdit;
	GetDlgItemText(IDC_EDIT, strEdit);
	return (!strEdit.IsEmpty());
}

void CEditDynFormConsigli::OnBnClickedBtnStampa()
{
	m_ctrlButtonStampa.SetCheck(BST_UNCHECKED);
	long lPdfId = 0;

	switch(m_lContenuto)
	{
		case edt_anatomiapatologicasugger1:
		{
			m_pEsamiView->AnteprimaStampaReport(STAMPA, VERIFICA_NO, theApp.m_sEditRep + "\\ConsigliIstologico1.rpa", FALSE, 1, &lPdfId,"");
			break;
		}
		case edt_anatomiapatologicasugger2:
		{
			m_pEsamiView->AnteprimaStampaReport(STAMPA, VERIFICA_NO, theApp.m_sEditRep + "\\ConsigliIstologico2.rpa", FALSE, 1, &lPdfId,"");
			break;
		}
	}
}
