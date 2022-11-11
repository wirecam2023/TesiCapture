#include "stdafx.h"
#include "Endox.h"
#include "LegendaDynForm.h"

#include "EsamiView.h"
#include "LegendaSet.h"
#include "EsamiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CLegendaDynForm::CLegendaDynForm(CWnd* pParent, CEsamiView* pEsamiView, long lContenuto)
: CEndoxDynForm(CLegendaDynForm::IDD, pParent, pEsamiView)
{
	m_lContenuto = lContenuto;
}

CLegendaDynForm::~CLegendaDynForm()
{
}

BEGIN_MESSAGE_MAP(CLegendaDynForm, CEndoxDynForm)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

void CLegendaDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lContenuto, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[lContenuto] == NULL)
	{
		pEsamiView->m_pDynForm[lContenuto] = new CLegendaDynForm(NULL, pEsamiView, lContenuto);
		if (pEsamiView->m_pDynForm[lContenuto] != NULL)
		{
			pEsamiView->m_pDynForm[lContenuto]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[lContenuto]->m_lColore = lColore;
			pEsamiView->m_pDynForm[lContenuto]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[lContenuto]->CreateChildForm(CLegendaDynForm::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CLegendaDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_TEXT:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

void CLegendaDynForm::DoDataExchange(CDataExchange* pDX)
{
}

BOOL CLegendaDynForm::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_TEXT, CSize(0,0), CSize(100,100));

	switch(m_lContenuto)
	{
		case sub_legenda1:
		case sub_legenda2:
		case sub_legenda3:
		{
			CString strFilter = "";
			CString strText = "";
			CLegendaSet setTemp;

			strFilter.Format("Voce=%li", g_FormCaract[m_lContenuto].lID);
			setTemp.SetSortRecord("VOCE");
			setTemp.SetOpenFilter(strFilter);
			if (setTemp.OpenRecordset("CLegendaDynForm::OnInitDialog"))
			{
				if (!setTemp.IsEOF())
				{
					strText = setTemp.m_sValore;
				}
				else
				{
					if (setTemp.AddNewRecordset("CLegendaDynForm::OnInitDialog"))
					{
						setTemp.m_lVoce = g_FormCaract[m_lContenuto].lID;
						setTemp.m_sValore = "";
						setTemp.UpdateRecordset("CLegendaDynForm::OnInitDialog");
					}
				}

				setTemp.CloseRecordset("CLegendaDynForm::OnInitDialog");
			}
			SetDlgItemText(IDC_TEXT, strText);

			break;
		}
		case sub_etichetta000:
		case sub_etichetta001:
		case sub_etichetta002:
		case sub_etichetta003:
		case sub_etichetta004:
		case sub_etichetta005:
		case sub_etichetta006:
		case sub_etichetta007:
		case sub_etichetta008:
		case sub_etichetta009:
		case sub_etichetta010:
		case sub_etichetta011:
		case sub_etichetta012:
		case sub_etichetta013:
		case sub_etichetta014:
		case sub_etichetta015:
		case sub_etichetta016:
		case sub_etichetta017:
		case sub_etichetta018:
		case sub_etichetta019:
		case sub_etichetta020:
		case sub_etichetta021:
		case sub_etichetta022:
		case sub_etichetta023:
		case sub_etichetta024:
		case sub_etichetta025:
		case sub_etichetta026:
		case sub_etichetta027:
		case sub_etichetta028:
		case sub_etichetta029:
		case sub_etichetta030:
		case sub_etichetta031:
		case sub_etichetta032:
		case sub_etichetta033:
		case sub_etichetta034:
		case sub_etichetta035:
		case sub_etichetta036:
		case sub_etichetta037:
		case sub_etichetta038:
		case sub_etichetta039:
		{
			int index = m_lContenuto - sub_etichetta000;
			SetDlgItemText(IDC_TEXT, theApp.m_sLabelTextEtichette[index]);

			break;
		}
	}

	GetDlgItem(IDC_TEXT)->SetFont(&theApp.m_fontBold, TRUE);

	return bReturn;
}

LRESULT CLegendaDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	return 1;
}

LRESULT CLegendaDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	return 1;
}

long CLegendaDynForm::GetContenuto()
{
	return m_lContenuto;
}

BOOL CLegendaDynForm::CampoObbligatorioValido()
{
	return TRUE;
}