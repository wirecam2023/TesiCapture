#include "stdafx.h"
#include "Endox.h"
#include "EditDynFormRtf.h"

#include "EsamiSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEditDynFormRtf::CEditDynFormRtf(CWnd* pParent, CEsamiView* pEsamiView, long lContenuto)
: CEndoxDynForm(CEditDynFormRtf::IDD, pParent, pEsamiView)
{
	m_lContenuto = lContenuto;
}

CEditDynFormRtf::~CEditDynFormRtf()
{
}

BEGIN_MESSAGE_MAP(CEditDynFormRtf, CEndoxDynForm)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
END_MESSAGE_MAP()

void CEditDynFormRtf::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lContenuto, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[lContenuto] == NULL)
	{
		pEsamiView->m_pDynForm[lContenuto] = new CEditDynFormRtf(NULL, pEsamiView, lContenuto);
		if (pEsamiView->m_pDynForm[lContenuto] != NULL)
		{
			pEsamiView->m_pDynForm[lContenuto]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[lContenuto]->m_lColore = lColore;
			pEsamiView->m_pDynForm[lContenuto]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[lContenuto]->CreateChildForm(CEditDynFormRtf::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CEditDynFormRtf::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
	}

	return hBrush;
}

void CEditDynFormRtf::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TEXTCONTROL, m_ctrlTextControl);
	m_ctrlTextControl.SendMessage(WM_USER + 1013, 1, 0); // così NON carica i font dalla stampante predefinita perché in certi casi dava RTF filter error... //

	switch(m_lContenuto)
	{
		case edt_anatomiapatologicarefer_rtf:
		{
			if (!pDX->m_bSaveAndValidate)
			{
				m_ctrlTextControl.ResetContents();

				if (!m_pEsamiView->m_pEsamiSet->m_sAPRispostaLibera.IsEmpty())
				{
					try
					{
						m_ctrlTextControl.SetRTFSelText(m_pEsamiView->m_pEsamiSet->m_sAPRispostaLibera);
					}
					catch(CException* pEx)
					{
						m_ctrlTextControl.SetText(m_pEsamiView->m_pEsamiSet->m_sAPRispostaLibera);
						pEx->Delete();
					}
				}
			}

			break;
		}
	}
}

BOOL CEditDynFormRtf::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	// m_ctrlTextControl.SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

	AddAnchor(IDC_TEXT, CSize(0, 0), CSize(100, 0));
	AddAnchor(IDC_TEXTCONTROL_PLACE, CSize(0, 0), CSize(100, 100));

	switch(m_lContenuto)
	{
		case edt_anatomiapatologicarefer_rtf:
		{
			SetDlgItemText(IDC_TEXT, theApp.GetMessageString(IDS_EDT_REFERTOANATOMIA_RTF));
			break;
		}
	}

	return bReturn;
}

void CEditDynFormRtf::OnSize(UINT nType, int cx, int cy)
{
	CEndoxDynForm::OnSize(nType, cx, cy);

	CWnd* pTextControlPlace = GetDlgItem(IDC_TEXTCONTROL_PLACE);
	if ((pTextControlPlace != NULL) && m_ctrlTextControl.GetSafeHwnd())
	{
		CRect rect;
		pTextControlPlace->GetWindowRect(rect);
		ScreenToClient(&rect);
		m_ctrlTextControl.SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_NOZORDER);
	}
}

long CEditDynFormRtf::GetContenuto()
{
	return m_lContenuto;
}

BOOL CEditDynFormRtf::CampoObbligatorioValido()
{
	return !m_ctrlTextControl.GetText().Trim().IsEmpty();
}