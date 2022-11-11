#include "stdafx.h"
#include "Endox.h"
#include "NomenclatoreDlg.h"

#include "ElemReportSet.h"
#include "EsamiView.h"
#include "ExportCSV.h"
#include "ExportExcel.h"
#include "ExportFileDlg.h"
#include "ExportHtml.h"
#include "MediciSet.h"
#include "NomenclatoreListaEsamiDlg.h"
#include "NomenclatoreListaEsamiRepartoDlg.h"
#include "NomenclatoreListaPrestazDlg.h"
#include "NomenclatoreListaPrestazRepartoDlg.h"
#include "PrestazioneSet.h"
#include "SediEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CNomenclatoreDlg::CNomenclatoreDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CNomenclatoreDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);
	m_pEsamiView = pEsamiView;

	m_sSedeEsame = "";
	m_nProvenienza = 2;
}

BEGIN_MESSAGE_MAP(CNomenclatoreDlg, CDialog)
	ON_WM_CTLCOLOR()

	ON_BN_CLICKED(IDC_BTN_ESAMI, OnBtnEsami)
	ON_BN_CLICKED(IDC_BTN_ESAMIREPARTO, OnBtnEsamiReparto)
	ON_BN_CLICKED(IDC_BTN_PRESTAZ, OnBtnPrestaz)
	ON_BN_CLICKED(IDC_BTN_PRESTAZREPARTO, OnBtnPrestazReparto)

	ON_CBN_SELCHANGE(IDC_COMBO_DATA, OnCbnSelchangeComboData)
END_MESSAGE_MAP()

void CNomenclatoreDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//

	DDX_Control(pDX, IDC_PROVENIENZA_00, m_ctrlRadio1);
	DDX_Control(pDX, IDC_PROVENIENZA_01, m_ctrlRadio2);
	DDX_Control(pDX, IDC_PROVENIENZA_02, m_ctrlRadio3);

	DDX_Control(pDX, IDC_BTN_ESAMI, m_ctrlBtnEsami);
	DDX_Control(pDX, IDC_BTN_ESAMIREPARTO, m_ctrlBtnEsamiReparto);
	DDX_Control(pDX, IDC_BTN_PRESTAZ, m_ctrlBtnPrestaz);
	DDX_Control(pDX, IDC_BTN_PRESTAZREPARTO, m_ctrlBtnPrestazReparto);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);

	DDX_Control(pDX, IDC_COMBO_DATA, m_ctrlComboData);
	DDX_Control(pDX, IDC_COMBO_MEDICO, m_ctrlComboMedico);
	DDX_Control(pDX, IDC_COMBO_SEDE, m_ctrlComboSede);

	DDX_Control(pDX, IDC_EDIT_DATAINIZ, m_ctrlDataIniz);
	DDX_Control(pDX, IDC_EDIT_DATAFINE, m_ctrlDataFine);

	DDX_Control(pDX, IDC_STATIC_00, m_ctrlStatic00);
	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic03);
	DDX_Control(pDX, IDC_STATIC_04, m_ctrlStatic04);

	//

	DDX_CBString(pDX, IDC_COMBO_SEDE, m_sSedeEsame);
	DDX_CBIndex(pDX, IDC_COMBO_MEDICO, m_nMedicoIndex);
	DDX_Radio(pDX, IDC_PROVENIENZA_00, m_nProvenienza);
}

BOOL CNomenclatoreDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	InitComboDataPeriod(&m_ctrlComboData);

	m_ctrlDataIniz.SetEditMask("00/00/0000", "__/__/____");
	m_ctrlDataFine.SetEditMask("00/00/0000", "__/__/____");

	RiempiComboSedi();

	RiempiComboMedici();

	theApp.LocalizeDialog(this, CNomenclatoreDlg::IDD, "NomenclatoreDlg");

	return TRUE;
}

HBRUSH CNomenclatoreDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

/*	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_00:
		case IDC_DATA_INIZIO:
			pDC->SetTextColor(CEsamiView::m_color1);
			break;

		case IDC_STATIC_01:
		case IDC_DATA_FINE:
			pDC->SetTextColor(CEsamiView::m_color2);
			break;
	}*/

	return hBrush;
}

void CNomenclatoreDlg::OnBtnEsami() 
{
	UpdateData(TRUE);

	CString strFiltroData;
	GetCustomDateFilter(&strFiltroData, "Data", this, &m_ctrlComboData, IDC_EDIT_DATAINIZ, IDC_EDIT_DATAFINE);

	CString strDataIniz;
	GetDlgItemText(IDC_EDIT_DATAINIZ, strDataIniz);

	CString strDataFine;
	GetDlgItemText(IDC_EDIT_DATAFINE, strDataFine);

	long lMedico = 0;
	if (m_nMedicoIndex > 0)
		lMedico = m_ctrlComboMedico.GetItemData(m_nMedicoIndex);

	CNomenclatoreListaEsamiDlg dlg(this, m_pEsamiView, strFiltroData, strDataIniz, strDataFine, m_sSedeEsame, lMedico, m_nProvenienza);
	dlg.DoModal();
}

void CNomenclatoreDlg::OnBtnEsamiReparto() 
{
	UpdateData(TRUE);

	CString strFiltroData;
	GetCustomDateFilter(&strFiltroData, "Data", this, &m_ctrlComboData, IDC_EDIT_DATAINIZ, IDC_EDIT_DATAFINE);

	CString strDataIniz;
	GetDlgItemText(IDC_EDIT_DATAINIZ, strDataIniz);

	CString strDataFine;
	GetDlgItemText(IDC_EDIT_DATAFINE, strDataFine);

	long lMedico = 0;
	if (m_nMedicoIndex > 0)
		lMedico = m_ctrlComboMedico.GetItemData(m_nMedicoIndex);

	CNomenclatoreListaEsamiRepartoDlg dlg(this, m_pEsamiView, strFiltroData, strDataIniz, strDataFine, m_sSedeEsame, lMedico, m_nProvenienza);
	dlg.DoModal();
}

void CNomenclatoreDlg::OnBtnPrestaz() 
{
	UpdateData(TRUE);

	CString strFiltroData;
	GetCustomDateFilter(&strFiltroData, "Data", this, &m_ctrlComboData, IDC_EDIT_DATAINIZ, IDC_EDIT_DATAFINE);

	CString strDataIniz;
	GetDlgItemText(IDC_EDIT_DATAINIZ, strDataIniz);

	CString strDataFine;
	GetDlgItemText(IDC_EDIT_DATAFINE, strDataFine);

	long lMedico = 0;
	if (m_nMedicoIndex > 0)
		lMedico = m_ctrlComboMedico.GetItemData(m_nMedicoIndex);

	CNomenclatoreListaPrestazDlg dlg(this, m_pEsamiView, strFiltroData, strDataIniz, strDataFine, m_sSedeEsame, lMedico, m_nProvenienza);
	dlg.DoModal();
}

void CNomenclatoreDlg::OnBtnPrestazReparto() 
{
	UpdateData(TRUE);

	CString strFiltroData;
	GetCustomDateFilter(&strFiltroData, "Data", this, &m_ctrlComboData, IDC_EDIT_DATAINIZ, IDC_EDIT_DATAFINE);

	CString strDataIniz;
	GetDlgItemText(IDC_EDIT_DATAINIZ, strDataIniz);

	CString strDataFine;
	GetDlgItemText(IDC_EDIT_DATAFINE, strDataFine);

	long lMedico = 0;
	if (m_nMedicoIndex > 0)
		lMedico = m_ctrlComboMedico.GetItemData(m_nMedicoIndex);

	CNomenclatoreListaPrestazRepartoDlg dlg(this, m_pEsamiView, strFiltroData, strDataIniz, strDataFine, m_sSedeEsame, lMedico, m_nProvenienza);
	dlg.DoModal();
}

void CNomenclatoreDlg::OnCbnSelchangeComboData()
{
	ComboDataPeriodUpdated(&m_ctrlComboData, this, IDC_EDIT_DATAINIZ, IDC_EDIT_DATAFINE);
}

void CNomenclatoreDlg::RiempiComboMedici() 
{
	int nIndex = 1;

	CMediciSet setTemp;
	if (theApp.m_bPersonalizzazioniBrasileEinstein)
		setTemp.SetSortRecord("Nome, Cognome");
	else
		setTemp.SetSortRecord("Cognome, Nome");

	m_ctrlComboMedico.ResetContent();
	m_ctrlComboMedico.InsertString(0, "");
	m_ctrlComboMedico.SetItemData(0, 0);

	if (setTemp.OpenRecordset("CNomenclatoreDlg::RiempiComboMedici"))
	{
		while(!setTemp.IsEOF())
		{
			m_ctrlComboMedico.InsertString(nIndex, setTemp.m_sTitolo + " " + setTemp.m_sNome + " " + setTemp.m_sCognome);
			m_ctrlComboMedico.SetItemData(nIndex, setTemp.m_lContatore);

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CNomenclatoreDlg::RiempiComboMedici");
	}
}

void CNomenclatoreDlg::RiempiComboSedi() 
{
	int nIndex = 1;

	CSediEsameSet setTemp;
	setTemp.SetSortRecord("Descrizione");

	m_ctrlComboSede.ResetContent();
	m_ctrlComboSede.InsertString(0, "");

	if (setTemp.OpenRecordset("CNomenclatoreDlg::RiempiListaSedi"))
	{
		while(!setTemp.IsEOF())
		{
			m_ctrlComboSede.InsertString(nIndex, setTemp.m_sDescrizione);

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CNomenclatoreDlg::RiempiListaSedi");
	}
}