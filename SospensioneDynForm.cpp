#include "stdafx.h"
#include "Endox.h"
#include "SospensioneDynForm.h"

#include "CustomDate.h"
#include "EsamiView.h"
#include "EsamiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSospensioneDynForm::CSospensioneDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(nID, pParent, pEsamiView),
	  m_ctrlRadio1(IDC_EDIT_DATASCADENZA),
	  m_ctrlRadio2(IDC_EDIT_DATASCADENZA)
{
	m_bReadOnly = FALSE;
}

CSospensioneDynForm::~CSospensioneDynForm()
{
}

BEGIN_MESSAGE_MAP(CSospensioneDynForm, CEndoxDynForm)
	ON_WM_CTLCOLOR()

	ON_BN_CLICKED(IDC_BTN_DATA, OnBnClickedBtnData)
	ON_BN_CLICKED(IDC_RADIO1, OnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnClickedRadio2)
	ON_STN_CLICKED(IDC_STATIC1, OnStnClickedStatic1)
	ON_STN_CLICKED(IDC_STATIC2, OnStnClickedStatic2)
END_MESSAGE_MAP()

void CSospensioneDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_sospensione] == NULL)
	{
		pEsamiView->m_pDynForm[sub_sospensione] = new CSospensioneDynForm(CSospensioneDynForm::IDD, NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_sospensione] != NULL)
		{
			pEsamiView->m_pDynForm[sub_sospensione]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_sospensione]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_sospensione]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_sospensione]->CreateChildForm(CSospensioneDynForm::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CSospensioneDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_SOSPESO:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			if (m_crCampoObbligatorio > 0)
				pDC->SetBkColor(m_crCampoObbligatorio);

			break;
		}

		case IDC_STATIC1:
		case IDC_STATIC2:
		case IDC_STATIC3:
		case IDC_STATIC4:
		case IDC_EDIT_DATASCADENZA:
		case IDC_EDIT_MOTIVO:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}

	return hBrush;
}

void CSospensioneDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_DATA, m_ctrlBtnData);

	DDX_Control(pDX, IDC_EDIT_MOTIVO, m_ctrlMotivo);

	DDX_Control(pDX, IDC_EDIT_DATASCADENZA, m_ctrlDataScadenza);

	DDX_Control(pDX, IDC_RADIO1, m_ctrlRadio1);
	DDX_Control(pDX, IDC_RADIO2, m_ctrlRadio2);

	DDX_Control(pDX, IDC_STATIC_SOSPESO, m_ctrlStaticSospeso);
	DDX_Control(pDX, IDC_STATIC1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC4, m_ctrlStatic4);

	//

	DDX_Radio(pDX, IDC_RADIO1, m_pEsamiView->m_pEsamiSet->m_iSospeso);

	if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI)
		DDX_Text(pDX, IDC_EDIT_DATASCADENZA, m_ctrlDataScadenza.m_strRicercaView);
	else
		DDX_DateTimePersMask(pDX, IDC_EDIT_DATASCADENZA, SOLO_DATA, m_pEsamiView->m_pEsamiSet->m_lDataScadenzaSospensione, m_pEsamiView->m_pEsamiSet->GetRecordset());

	DDX_FieldText(pDX, IDC_EDIT_MOTIVO, m_pEsamiView->m_pEsamiSet->m_sMotivoSospensione, m_pEsamiView->m_pEsamiSet->GetRecordset());
}

BOOL CSospensioneDynForm::OnInitDialog()
{
	CEndoxDynForm::OnInitDialog();

	AddAnchor(IDC_STATIC_SOSPESO, CSize(0, 0), CSize(100, 0));
	AddAnchor(IDC_RADIO1, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_STATIC1, CSize(0, 0), CSize(50, 0));
	AddAnchor(IDC_RADIO2, CSize(50, 0), CSize(50, 0));
	AddAnchor(IDC_STATIC2, CSize(50, 0), CSize(100, 0));
	AddAnchor(IDC_STATIC3, CSize(0, 0), CSize(100, 0));
	AddAnchor(IDC_EDIT_DATASCADENZA, CSize(0, 0), CSize(100, 0));
	AddAnchor(IDC_STATIC4, CSize(0, 0), CSize(100, 0));
	AddAnchor(IDC_EDIT_MOTIVO, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDC_BTN_DATA, CSize(100, 0), CSize(100, 100));

	m_ctrlStaticSospeso.SetFont(&theApp.m_fontBold);

	m_ctrlDataScadenza.SetParam(this, m_pEsamiView, theApp.GetMessageString(IDS_EDT_DATASCADENZASOSPENSIONE), SOLO_DATA);

	theApp.LocalizeDialog(this, CSospensioneDynForm::IDD, "SospensioneDynForm");
	return TRUE;
}

void CSospensioneDynForm::OnBnClickedBtnData()
{
	m_ctrlBtnData.SetCheck(BST_UNCHECKED);

	CString strTemp;
	m_ctrlMotivo.GetWindowText(strTemp);

	if (!strTemp.Trim().IsEmpty())
		strTemp += "\r\n";
	strTemp += CCustomDate(TRUE, TRUE).GetDate("%d/%m/%Y: ");

	m_ctrlMotivo.SetWindowText(strTemp);
	m_ctrlMotivo.SetFocus();
	m_ctrlMotivo.SetSel(strTemp.GetLength(), strTemp.GetLength());

}

void CSospensioneDynForm::OnClickedRadio1()
{
	// m_ctrlDataScadenza.SetWindowText(m_ctrlDataScadenza.GetDefault());
	// m_ctrlMotivo.SetWindowText("");
}

void CSospensioneDynForm::OnClickedRadio2()
{
}

LRESULT CSospensioneDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CSospensioneDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(FALSE);
}

LRESULT CSospensioneDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	m_bReadOnly = (BOOL)wParam;

	m_ctrlRadio1.EnableWindow(!m_bReadOnly);
	m_ctrlRadio2.EnableWindow(!m_bReadOnly);
	SendDlgItemMessage(IDC_EDIT_DATASCADENZA, EM_SETREADONLY, m_bReadOnly, lParam);
	SendDlgItemMessage(IDC_EDIT_MOTIVO, EM_SETREADONLY, m_bReadOnly, lParam);
	m_ctrlBtnData.EnableWindow(!m_bReadOnly);

	return 1;
}

LRESULT CSospensioneDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	m_ctrlDataScadenza.m_strRicerca = "";
	m_ctrlDataScadenza.m_strRicercaView = "";

	return 1;
}

LRESULT CSospensioneDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	return UpdateData(TRUE);
}

LRESULT CSospensioneDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	if (m_pEsamiView->m_pEsamiSet->m_iSospeso >= 0)
	{
		ComponiRicercaLong(pStrWhere, m_pEsamiView->m_pEsamiSet, (long*)&m_pEsamiView->m_pEsamiSet->m_iSospeso, "EEsami.Sospeso", 0, "AND");

		ComponiRicercaEx(pStrWhere, m_ctrlDataScadenza.m_strRicerca, "EEsami.DataScadenzaSospensione", FALSE, TRUE);

		if (!m_pEsamiView->m_pEsamiSet->m_sMotivoSospensione.IsEmpty())
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sMotivoSospensione, "EEsami.MotivoSospensione", 0);
	}

	return 1;
}

long CSospensioneDynForm::GetContenuto()
{
	return sub_sospensione;
}

BOOL CSospensioneDynForm::CampoObbligatorioValido()
{
	switch(m_pEsamiView->m_pEsamiSet->m_iSospeso)
	{
		case 0:
		case 1:
		{
			return TRUE;
			break;
		}
	}

	return FALSE;
}

void CSospensioneDynForm::OnStnClickedStatic1()
{
	if (!m_bReadOnly)
	{
		UpdateData(TRUE);
		m_pEsamiView->m_pEsamiSet->m_iSospeso = 0;
		UpdateData(FALSE);

		// aggiorno interfaccia //
		OnClickedRadio1();
	}
}

void CSospensioneDynForm::OnStnClickedStatic2()
{
	if (!m_bReadOnly)
	{
		UpdateData(TRUE);
		m_pEsamiView->m_pEsamiSet->m_iSospeso = 1;
		UpdateData(FALSE);

		// aggiorno interfaccia //
		OnClickedRadio2();
	}
}