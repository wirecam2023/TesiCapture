#include "stdafx.h"
#include "Endox.h"
#include "BostonScoreDynForm.h"

#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBostonScoreDynForm::CBostonScoreDynForm(CWnd* pParent, CEsamiView* pEsamiView)
: CEndoxDynForm(CBostonScoreDynForm::IDD, pParent, pEsamiView)
{
}

CBostonScoreDynForm::~CBostonScoreDynForm()
{
}

BEGIN_MESSAGE_MAP(CBostonScoreDynForm, CEndoxDynForm)

	ON_WM_CTLCOLOR()

	ON_CBN_SELCHANGE(IDC_COMBO_DX, OnCbnSelchangeComboDx)
	ON_CBN_SELCHANGE(IDC_COMBO_MID, OnCbnSelchangeComboMid)
	ON_CBN_SELCHANGE(IDC_COMBO_SX, OnCbnSelchangeComboSx)

END_MESSAGE_MAP()

void CBostonScoreDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_bostonscore] == NULL)
	{
		pEsamiView->m_pDynForm[sub_bostonscore] = new CBostonScoreDynForm(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_bostonscore] != NULL)
		{
			pEsamiView->m_pDynForm[sub_bostonscore]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_bostonscore]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_bostonscore]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_bostonscore]->CreateChildForm(CBostonScoreDynForm::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CBostonScoreDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_00:
		case IDC_STATIC_01:
		case IDC_STATIC_02:
		case IDC_STATIC_03:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			if (m_crCampoObbligatorio > 0)
				pDC->SetBkColor(m_crCampoObbligatorio);

			break;
		}
		case IDC_STATIC_04:
		case IDC_COMBO_DX:
		case IDC_COMBO_MID:
		case IDC_COMBO_SX:
		case IDC_STATIC_TOTALE:
		case IDC_STATIC_FRASE:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

void CBostonScoreDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	//

	DDX_Control(pDX, IDC_STATIC_00, m_ctrlStatic00);
	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic03);
	DDX_Control(pDX, IDC_STATIC_04, m_ctrlStatic04);
	DDX_Control(pDX, IDC_COMBO_DX, m_ctrlComboDx);
	DDX_Control(pDX, IDC_COMBO_MID, m_ctrlComboMid);
	DDX_Control(pDX, IDC_COMBO_SX, m_ctrlComboSx);
	DDX_Control(pDX, IDC_STATIC_TOTALE, m_ctrlStaticTotale);
	DDX_Control(pDX, IDC_STATIC_FRASE, m_ctrlStaticFrase);

	//

	if (pDX->m_bSaveAndValidate)
	{
		m_pEsamiView->m_pEsamiSet->m_lBostonScoreDx = m_ctrlComboDx.GetCurSel() - 1;
		m_pEsamiView->m_pEsamiSet->m_lBostonScoreMid = m_ctrlComboMid.GetCurSel() - 1;
		m_pEsamiView->m_pEsamiSet->m_lBostonScoreSx = m_ctrlComboSx.GetCurSel() - 1;
	}
	else
	{
		if ((m_pEsamiView->m_pEsamiSet->m_lBostonScoreDx >= 0) && (m_pEsamiView->m_pEsamiSet->m_lBostonScoreDx <= 3))
			m_ctrlComboDx.SetCurSel(m_pEsamiView->m_pEsamiSet->m_lBostonScoreDx + 1);
		else
			m_ctrlComboDx.SetCurSel(0);

		if ((m_pEsamiView->m_pEsamiSet->m_lBostonScoreMid >= 0) && (m_pEsamiView->m_pEsamiSet->m_lBostonScoreMid <= 3))
			m_ctrlComboMid.SetCurSel(m_pEsamiView->m_pEsamiSet->m_lBostonScoreMid + 1);
		else
			m_ctrlComboMid.SetCurSel(0);

		if ((m_pEsamiView->m_pEsamiSet->m_lBostonScoreSx >= 0) && (m_pEsamiView->m_pEsamiSet->m_lBostonScoreSx <= 3))
			m_ctrlComboSx.SetCurSel(m_pEsamiView->m_pEsamiSet->m_lBostonScoreSx + 1);
		else
			m_ctrlComboSx.SetCurSel(0);

		AggiornaScore();
	}
}

BOOL CBostonScoreDynForm::OnInitDialog()
{
	BOOL bReturn = CEndoxDynForm::OnInitDialog();

	//

	AddAnchor(IDC_STATIC_00, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDC_STATIC_01, CSize(0, 50), CSize(10, 50));
	AddAnchor(IDC_STATIC_02, CSize(0, 50), CSize(10, 50));
	AddAnchor(IDC_STATIC_03, CSize(0, 50), CSize(10, 50));
	AddAnchor(IDC_STATIC_04, CSize(0, 50), CSize(10, 50));
	AddAnchor(IDC_COMBO_DX, CSize(10, 50), CSize(100, 50));
	AddAnchor(IDC_COMBO_MID, CSize(10, 50), CSize(100, 50));
	AddAnchor(IDC_COMBO_SX, CSize(10, 50), CSize(100, 50));
	AddAnchor(IDC_STATIC_TOTALE, CSize(10, 50), CSize(10, 50));
	AddAnchor(IDC_STATIC_FRASE, CSize(10, 50), CSize(100, 50));

	//

	m_ctrlStatic00.SetFont(&theApp.m_fontBold);
	m_ctrlStaticTotale.SetFont(&theApp.m_fontBig);

	//

	m_ctrlComboDx.InsertString(0, "");
	m_ctrlComboDx.SetItemData(0, 0);
	m_ctrlComboDx.InsertString(1, theApp.GetMessageString(IDS_BOSTONSCORE_0));
	m_ctrlComboDx.SetItemData(1, 0);
	m_ctrlComboDx.InsertString(2, theApp.GetMessageString(IDS_BOSTONSCORE_1));
	m_ctrlComboDx.SetItemData(2, 1);
	m_ctrlComboDx.InsertString(3, theApp.GetMessageString(IDS_BOSTONSCORE_2));
	m_ctrlComboDx.SetItemData(3, 2);
	m_ctrlComboDx.InsertString(4, theApp.GetMessageString(IDS_BOSTONSCORE_3));
	m_ctrlComboDx.SetItemData(4, 3);
	m_ctrlComboDx.SetCurSel(0);

	m_ctrlComboMid.InsertString(0, "");
	m_ctrlComboMid.SetItemData(0, 0);
	m_ctrlComboMid.InsertString(1, theApp.GetMessageString(IDS_BOSTONSCORE_0));
	m_ctrlComboMid.SetItemData(1, 0);
	m_ctrlComboMid.InsertString(2, theApp.GetMessageString(IDS_BOSTONSCORE_1));
	m_ctrlComboMid.SetItemData(2, 1);
	m_ctrlComboMid.InsertString(3, theApp.GetMessageString(IDS_BOSTONSCORE_2));
	m_ctrlComboMid.SetItemData(3, 2);
	m_ctrlComboMid.InsertString(4, theApp.GetMessageString(IDS_BOSTONSCORE_3));
	m_ctrlComboMid.SetItemData(4, 3);
	m_ctrlComboMid.SetCurSel(0);

	m_ctrlComboSx.InsertString(0, "");
	m_ctrlComboSx.SetItemData(0, 0);
	m_ctrlComboSx.InsertString(1, theApp.GetMessageString(IDS_BOSTONSCORE_0));
	m_ctrlComboSx.SetItemData(1, 0);
	m_ctrlComboSx.InsertString(2, theApp.GetMessageString(IDS_BOSTONSCORE_1));
	m_ctrlComboSx.SetItemData(2, 1);
	m_ctrlComboSx.InsertString(3, theApp.GetMessageString(IDS_BOSTONSCORE_2));
	m_ctrlComboSx.SetItemData(3, 2);
	m_ctrlComboSx.InsertString(4, theApp.GetMessageString(IDS_BOSTONSCORE_3));
	m_ctrlComboSx.SetItemData(4, 3);
	m_ctrlComboSx.SetCurSel(0);

	AggiornaScore();

	//

	theApp.LocalizeDialog(this, CBostonScoreDynForm::IDD, "BostonScoreDynForm");
	return bReturn;
}

LRESULT CBostonScoreDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CBostonScoreDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(FALSE);
}

LRESULT CBostonScoreDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	m_ctrlComboDx.EnableWindow(!(BOOL)wParam);
	m_ctrlComboMid.EnableWindow(!(BOOL)wParam);
	m_ctrlComboSx.EnableWindow(!(BOOL)wParam);

	return 1;
}

LRESULT CBostonScoreDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	return 1;
}

LRESULT CBostonScoreDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT CBostonScoreDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	return 1;
}

long CBostonScoreDynForm::GetContenuto()
{
	return sub_bostonscore;
}

BOOL CBostonScoreDynForm::CampoObbligatorioValido()
{
	return ((m_ctrlComboDx.GetCurSel() > 0) && (m_ctrlComboMid.GetCurSel() > 0) && (m_ctrlComboSx.GetCurSel() > 0));
}

void CBostonScoreDynForm::OnCbnSelchangeComboDx()
{
	AggiornaScore();
}

void CBostonScoreDynForm::OnCbnSelchangeComboMid()
{
	AggiornaScore();
}

void CBostonScoreDynForm::OnCbnSelchangeComboSx()
{
	AggiornaScore();
}

void CBostonScoreDynForm::AggiornaScore()
{
	if ((m_ctrlComboDx.GetCurSel() > 0) && (m_ctrlComboMid.GetCurSel() > 0) && (m_ctrlComboSx.GetCurSel() > 0))
	{
		long lScore = 0;

		if (m_ctrlComboDx.GetCurSel() > 0)
			lScore += m_ctrlComboDx.GetItemData(m_ctrlComboDx.GetCurSel());

		if (m_ctrlComboMid.GetCurSel() > 0)
			lScore += m_ctrlComboMid.GetItemData(m_ctrlComboMid.GetCurSel());

		if (m_ctrlComboSx.GetCurSel() > 0)
			lScore += m_ctrlComboSx.GetItemData(m_ctrlComboSx.GetCurSel());

		//

		CString sScore;
		sScore.Format("%li", lScore);

		m_ctrlStaticTotale.SetWindowText(sScore);

		//

		CString sFraseStampata = "";
		if ((lScore >= 0) && (lScore <= 9))
		{
			CString sTemp;
			sTemp.Format("%li", lScore);

			if (theApp.m_sBostonScore[lScore].CompareNoCase(sTemp) != 0)
				sFraseStampata.Format(" (%s)", theApp.m_sBostonScore[lScore]);
		}

		m_ctrlStaticFrase.SetWindowText(sFraseStampata);
	}
	else
	{
		m_ctrlStaticTotale.SetWindowText("-");
		m_ctrlStaticFrase.SetWindowText("");
	}
}