#include "stdafx.h"
#include "Endox.h"
#include "SetupDlg.h"

#include <io.h>
#include <errno.h>

#include "DisplayHelper.h"
#include "EditStringDlg.h"
#include "EsamiDoc.h"
#include "EsamiView.h"
#include "SaleEsameUseDlg.h"
#include "SediEsameSet.h"
#include "SediEsameUseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSetupDlg::CSetupDlg(CEsamiView* pEsamiView)
    : CDialog(CSetupDlg::IDD)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
	m_nLanguage = theApp.m_nLanguage;

	m_lIDSedeEsame = 0;
}

BEGIN_MESSAGE_MAP(CSetupDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_HSCROLL()

	ON_BN_CLICKED(IDC_BTN_PERCORSI_OD, OnBnClickedBtnPercorsiOd)

	ON_BN_CLICKED(IDC_CHECK_REP, OnBnClickedCheckRep)
	ON_BN_CLICKED(IDC_BTN_REP, OnBnClickedBtnRep)

	ON_BN_CLICKED(IDC_CHECK_IMM, OnBnClickedCheckImm)
	ON_BN_CLICKED(IDC_BTN_IMM, OnBnClickedBtnImm)

	ON_BN_CLICKED(IDC_REPORT_DEFAULT, OnReportDefault)

	ON_BN_CLICKED(IDC_BTN_SEDE, OnBnClickedBtnSede)
	ON_BN_CLICKED(IDC_BTN_SALA, OnBnClickedBtnSala)

	ON_BN_CLICKED(IDC_BUTTON_IMM1_SET, OnBnClickedButtonImm1Set)
	ON_BN_CLICKED(IDC_BUTTON_IMM1_DEL, OnBnClickedButtonImm1Del)
	ON_BN_CLICKED(IDC_BUTTON_REP1_SET, OnBnClickedButtonRep1Set)
	ON_BN_CLICKED(IDC_BUTTON_REP1_DEL, OnBnClickedButtonRep1Del)
	ON_BN_CLICKED(IDC_BUTTON_REP2_SET, OnBnClickedButtonRep2Set)
	ON_BN_CLICKED(IDC_BUTTON_REP2_DEL, OnBnClickedButtonRep2Del)
	ON_BN_CLICKED(IDC_BUTTON_REP3_SET, OnBnClickedButtonRep3Set)
	ON_BN_CLICKED(IDC_BUTTON_REP3_DEL, OnBnClickedButtonRep3Del)
	ON_BN_CLICKED(IDC_BUTTON_REP4_SET, OnBnClickedButtonRep4Set)
	ON_BN_CLICKED(IDC_BUTTON_REP4_DEL, OnBnClickedButtonRep4Del)
	ON_BN_CLICKED(IDC_BUTTON_REP5_SET, OnBnClickedButtonRep5Set)
	ON_BN_CLICKED(IDC_BUTTON_REP5_DEL, OnBnClickedButtonRep5Del)
	ON_BN_CLICKED(IDC_BUTTON_REP6_SET, OnBnClickedButtonRep6Set)
	ON_BN_CLICKED(IDC_BUTTON_REP6_DEL, OnBnClickedButtonRep6Del)
	ON_BN_CLICKED(IDC_BUTTON_REP7_SET, OnBnClickedButtonRep7Set)
	ON_BN_CLICKED(IDC_BUTTON_REP7_DEL, OnBnClickedButtonRep7Del)
	ON_BN_CLICKED(IDC_BUTTON_REP8_SET, OnBnClickedButtonRep8Set)
	ON_BN_CLICKED(IDC_BUTTON_REP8_DEL, OnBnClickedButtonRep8Del)
	ON_BN_CLICKED(IDC_BUTTON_REP9_SET, OnBnClickedButtonRep9Set)
	ON_BN_CLICKED(IDC_BUTTON_REP9_DEL, OnBnClickedButtonRep9Del)

	ON_BN_CLICKED(IDC_CHK_PAZORDESA, OnBnClickedChkPazOrdEsa)
	ON_BN_CLICKED(IDC_CHK_VIS_ABILITA, OnBnClickedChkVisAbilita)
	ON_BN_CLICKED(IDC_CHK_VIS_ABILITA_MONITOR, OnBnClickedChkVisAbilitaMonitor)

	ON_CBN_SELCHANGE(IDC_ARCHIVE_FORMAT, OnCbnSelchangeArchiveFormat)
END_MESSAGE_MAP()

void CSetupDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_05, m_ctrlStatic05);
	DDX_Control(pDX, IDC_STATIC_06, m_ctrlStatic06);
	DDX_Control(pDX, IDC_STATIC_07, m_ctrlStatic07);
	DDX_Control(pDX, IDC_STATIC_11, m_ctrlStatic11);
	DDX_Control(pDX, IDC_STATIC_12, m_ctrlStatic12);
	DDX_Control(pDX, IDC_STATIC_13, m_ctrlStatic13);
	DDX_Control(pDX, IDC_STATIC_14, m_ctrlStatic14);
	DDX_Control(pDX, IDC_STATIC_15, m_ctrlStatic15);
	DDX_Control(pDX, IDC_STATIC_16, m_ctrlStatic16);
	DDX_Control(pDX, IDC_STATIC_17, m_ctrlStatic17);
	DDX_Control(pDX, IDC_STATIC_18, m_ctrlStatic18);
	DDX_Control(pDX, IDC_STATIC_19, m_ctrlStatic19);
	DDX_Control(pDX, IDC_STATIC_20, m_ctrlStatic20);
	DDX_Control(pDX, IDC_STATIC_21, m_ctrlStatic21);
	DDX_Control(pDX, IDC_STATIC_25, m_ctrlStatic25);
	DDX_Control(pDX, IDC_STATIC_28, m_ctrlStatic28);
	DDX_Control(pDX, IDC_STATIC_29, m_ctrlStatic29);
	DDX_Control(pDX, IDC_STATIC_30, m_ctrlStatic30);
	DDX_Control(pDX, IDC_STATIC_31, m_ctrlStatic31);
	DDX_Control(pDX, IDC_STATIC_32, m_ctrlStatic32);
	DDX_Control(pDX, IDC_STATIC_33, m_ctrlStatic33);
	DDX_Control(pDX, IDC_STATIC_34, m_ctrlStatic34);
	DDX_Control(pDX, IDC_STATIC_35, m_ctrlStatic35);
	DDX_Control(pDX, IDC_STATIC_36, m_ctrlStatic36);
	DDX_Control(pDX, IDC_STATIC_37, m_ctrlStatic37);
	DDX_Control(pDX, IDC_STATIC_38, m_ctrlStatic38);
	DDX_Control(pDX, IDC_STATIC_39, m_ctrlStatic39);
	DDX_Control(pDX, IDC_STATIC_40, m_ctrlStatic40);
	DDX_Control(pDX, IDC_STATIC_41, m_ctrlStatic41);
	DDX_Control(pDX, IDC_STATIC_42, m_ctrlStatic42);
	DDX_Control(pDX, IDC_STATIC_43, m_ctrlStatic43);
	DDX_Control(pDX, IDC_STATIC_44, m_ctrlStatic44);
	DDX_Control(pDX, IDC_STATIC_45, m_ctrlStatic45);
	DDX_Control(pDX, IDC_STATIC_46, m_ctrlStatic46);
	DDX_Control(pDX, IDC_STATIC_47, m_ctrlStatic47);

	DDX_Control(pDX, IDC_CHECK_REP, m_chkRep);
	m_chkRep.SetWindowText(theApp.GetMessageString(m_chkRep.GetCheck() == BST_CHECKED ? IDS_SETTINGDLG_BUTTON_1 : IDS_SETTINGDLG_BUTTON_2));
	GetDlgItem(IDC_EDIT_REP)->ShowWindow(m_chkRep.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_BTN_REP)->ShowWindow(m_chkRep.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);

	DDX_Control(pDX, IDC_CHECK_IMM, m_chkImm);
	m_chkImm.SetWindowText(theApp.GetMessageString(m_chkImm.GetCheck() == BST_CHECKED ? IDS_SETTINGDLG_BUTTON_1 : IDS_SETTINGDLG_BUTTON_2));
	GetDlgItem(IDC_EDIT_IMM)->ShowWindow(m_chkImm.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_BTN_IMM)->ShowWindow(m_chkImm.GetCheck() == BST_CHECKED ? SW_SHOW : SW_HIDE);

	DDX_Control(pDX, IDC_REPORT_DEFAULT, m_btnReportDefault);

	DDX_Control(pDX, IDC_BTN_SEDE, m_btnSede);
	DDX_Control(pDX, IDC_BTN_SALA, m_btnSala);

	DDX_Control(pDX, IDC_EXP_FORMAT, m_ctrlExpoFormat);

	DDX_Control(pDX, IDC_ARCHIVE_FORMAT, m_ctrlArchiveFormat);

	DDX_Control(pDX, IDC_LANG_1, m_ctrlRadioLang1);
	DDX_Control(pDX, IDC_LANG_2, m_ctrlRadioLang2);
	DDX_Control(pDX, IDC_LANG_3, m_ctrlRadioLang3);
	DDX_Control(pDX, IDC_LANG_4, m_ctrlRadioLang4);
	DDX_Radio(pDX, IDC_LANG_1, m_nLanguage);

	DDX_Control(pDX, IDC_CHK_AUTODESELECT, m_chkDeseleziona);

	DDX_Control(pDX, IDC_SPIN_ETICH_00, m_ctrlSpinEtich00);
	DDX_Control(pDX, IDC_SPIN_ETICH_01, m_ctrlSpinEtich01);
	DDX_Control(pDX, IDC_SPIN_ETICH_02, m_ctrlSpinEtich02);
	DDX_Control(pDX, IDC_SPIN_ETICH_03, m_ctrlSpinEtich03);

	DDX_Control(pDX, IDC_CHK_PAZORDESA, m_chkUsaVista);

	DDX_Control(pDX, IDC_CHK_VIS_ABILITA, m_chkVisAbilita);
	DDX_Control(pDX, IDC_CHK_VIS_ABILITA_MONITOR, m_chkVisAbilitaMonitor);

	DDX_Control(pDX, IDC_SLIDER_IMM, m_ctrlSliderImm);
	DDX_Control(pDX, IDC_SLIDER_MIN, m_ctrlSliderMin);

	DDX_Control(pDX, IDC_CMB_DISPLAY, m_ctrlCmbDisplay);

	DDX_Control(pDX, IDOK, m_ctrlBtnOK);
	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
}

void CSetupDlg::OnCancel()
{
	if (GetDlgItem(IDCANCEL)->IsWindowVisible())
		CDialog::OnCancel();
}

BOOL CSetupDlg::OnInitDialog() 
{
    CDialog::OnInitDialog();

	SetDlgItemText(IDC_PERCORSI_OD, theApp.m_sPathImageOD);

	if (theApp.m_bCheckRep)
		m_chkRep.SetCheck(BST_CHECKED);
	SetDlgItemText(IDC_EDIT_REP, theApp.m_sEditRep);
	if (theApp.m_bCheckImm)
		m_chkImm.SetCheck(BST_CHECKED);
	SetDlgItemText(IDC_EDIT_IMM, theApp.m_sEditImm);

	// m_btnProvincia.SetWindowText(theApp.m_strProvinciaDefault);
	m_lIDSedeEsame = theApp.m_lIDSedeEsameDefault;
	m_btnSede.SetWindowText(CSediEsameSet().GetDescrizione(m_lIDSedeEsame, FALSE));
	m_btnSala.SetWindowText(theApp.m_sSalaEsameDefault);

	m_ctrlExpoFormat.AddString("Tagged Image File Format (*.TIF)");
	m_ctrlExpoFormat.AddString("CompuServe Graphics Interchange (*.GIF)");
	m_ctrlExpoFormat.AddString("Windows Bitmap (*.BMP)");
	m_ctrlExpoFormat.AddString("JPEG 2000 (*.JP2)");
	m_ctrlExpoFormat.AddString("JPEG (*.JPG)");
	m_ctrlExpoFormat.SetCurSel(theApp.m_nExpFormat);

	if (theApp.m_bAutoDeselect)
		m_chkDeseleziona.SetCheck(BST_CHECKED);

	m_ctrlArchiveFormat.SetCurSel(theApp.m_nArchivioImmaginiFormato - 1);
	OnCbnSelchangeArchiveFormat();

	m_ctrlSliderImm.SetRange(0, 100);
	m_ctrlSliderImm.SetPos(theApp.m_nArchivioImmaginiQualita);

	m_ctrlSliderMin.SetRange(0, 100);
	m_ctrlSliderMin.SetPos(theApp.m_nArchivioMiniatureQualita);

	CString strQuality;
	strQuality.Format("%d", m_ctrlSliderImm.GetPos());
	m_ctrlStatic38.SetWindowText(strQuality);
	strQuality.Format("%d", m_ctrlSliderMin.GetPos());
	m_ctrlStatic41.SetWindowText(strQuality);

	m_ctrlSpinEtich00.SetRange32(0, 30);
	m_ctrlSpinEtich00.SetPos32((int)(theApp.m_fEtichette00 * 10.0f));
	m_ctrlSpinEtich01.SetRange32(0, 30);
	m_ctrlSpinEtich01.SetPos32((int)(theApp.m_fEtichette01 * 10.0f));
	m_ctrlSpinEtich02.SetRange32(90, 110);
	m_ctrlSpinEtich02.SetPos32((int)(theApp.m_fEtichette02 * 100.0f));
	m_ctrlSpinEtich03.SetRange32(90, 110);
	m_ctrlSpinEtich03.SetPos32((int)(theApp.m_fEtichette03 * 100.0f));

	/* if (theApp.m_bPazientiUsaVista)
	{
		m_chkUsaVista.SetCheck(BST_CHECKED);
		GetDlgItem(IDC_EDIT02)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT03)->EnableWindow(TRUE);
	} */
	SetDlgItemText(IDC_EDIT01, theApp.m_sPazientiTabella);
	// SetDlgItemText(IDC_EDIT02, theApp.m_sPazientiVista);
	// SetDlgItemText(IDC_EDIT03, theApp.m_sPazientiVistaOrdinamento);

	SetDlgItemText(IDC_EDIT_SSCP_PORTA, theApp.m_sStoreScpPorta);
	SetDlgItemText(IDC_EDIT_SSCP_EOR_EXE, theApp.m_sStoreScpExecOnReceptionExe);
	SetDlgItemText(IDC_EDIT_SSCP_EOR_PARAM, theApp.m_sStoreScpExecOnReceptionParameters);

	CString strFile;
	
	strFile = theApp.m_sDirProg + "\\" + "PrinterImmagini.dat";
	if (_access(strFile, 0) == 0)
		prnImmagini.Load(strFile);
	SetDlgItemText(IDC_EDIT_IMM1, prnImmagini.GetPrinterName());

	strFile = theApp.m_sDirProg + "\\" + "PrinterReports.dat";
	if (_access(strFile, 0) == 0)
		prnReports1.Load(strFile);
	SetDlgItemText(IDC_EDIT_REP1, prnReports1.GetPrinterName());

	strFile = theApp.m_sDirProg + "\\" + "PrinterReports2.dat";
	if (_access(strFile, 0) == 0)
		prnReports2.Load(strFile);
	SetDlgItemText(IDC_EDIT_REP2, prnReports2.GetPrinterName());

	strFile = theApp.m_sDirProg + "\\" + "PrinterReports3.dat";
	if (_access(strFile, 0) == 0)
		prnReports3.Load(strFile);
	SetDlgItemText(IDC_EDIT_REP3, prnReports3.GetPrinterName());

	strFile = theApp.m_sDirProg + "\\" + "PrinterReports4.dat";
	if (_access(strFile, 0) == 0)
		prnReports4.Load(strFile);
	SetDlgItemText(IDC_EDIT_REP4, prnReports4.GetPrinterName());

	strFile = theApp.m_sDirProg + "\\" + "PrinterReports5.dat";
	if (_access(strFile, 0) == 0)
		prnReports5.Load(strFile);
	SetDlgItemText(IDC_EDIT_REP5, prnReports5.GetPrinterName());

	strFile = theApp.m_sDirProg + "\\" + "PrinterReports6.dat";
	if (_access(strFile, 0) == 0)
		prnReports6.Load(strFile);
	SetDlgItemText(IDC_EDIT_REP6, prnReports6.GetPrinterName());

	strFile = theApp.m_sDirProg + "\\" + "PrinterReports7.dat";
	if (_access(strFile, 0) == 0)
		prnReports7.Load(strFile);
	SetDlgItemText(IDC_EDIT_REP7, prnReports7.GetPrinterName());

	strFile = theApp.m_sDirProg + "\\" + "PrinterReports8.dat";
	if (_access(strFile, 0) == 0)
		prnReports8.Load(strFile);
	SetDlgItemText(IDC_EDIT_REP8, prnReports8.GetPrinterName());

	strFile = theApp.m_sDirProg + "\\" + "PrinterReports9.dat";
	if (_access(strFile, 0) == 0)
		prnReports9.Load(strFile);
	SetDlgItemText(IDC_EDIT_REP9, prnReports9.GetPrinterName());

	switch(theApp.m_nApplication)
	{
		case PRG_IMAGENT:
		{
			GetDlgItem(IDC_STATIC_14)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_16)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_ETICH_00)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_SPIN_ETICH_00)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_15)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_ETICH_01)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_SPIN_ETICH_01)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_17)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_ETICH_02)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_SPIN_ETICH_02)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_18)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_ETICH_03)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_SPIN_ETICH_03)->ShowWindow(SW_HIDE);

			break;
		}
	}

	m_chkVisAbilita.SetCheck(theApp.m_bVisAbilita);
	if (theApp.m_bVisAbilita)
	{
		GetDlgItem(IDC_EDIT_VIS_IP)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_VIS_PORTA)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_VIS_PORTA_MONITOR)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_33)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_34)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_35)->EnableWindow(TRUE);
	}
	SetDlgItemText(IDC_EDIT_VIS_IP, theApp.m_sVisIp);
	CString sTemp;
	sTemp.Format("%li", theApp.m_lVisPorta);
	SetDlgItemText(IDC_EDIT_VIS_PORTA, sTemp);
	m_chkVisAbilitaMonitor.SetCheck(theApp.m_bVisAbilitaMonitor);
	SetDlgItemText(IDC_EDIT_VIS_PORTA_MONITOR, theApp.m_sVisPortaMonitor);
	GetDlgItem(IDC_EDIT_VIS_PORTA_MONITOR)->EnableWindow(m_chkVisAbilitaMonitor.GetCheck());

	// Sandro 22/03/2010 - durante installazione di Endox //
	if (theApp.m_bConfigure)
	{
		m_ctrlStatic42.ShowWindow(SW_HIDE);
		m_ctrlStatic43.ShowWindow(SW_HIDE);
		m_ctrlStatic44.ShowWindow(SW_HIDE);
		m_ctrlStatic45.ShowWindow(SW_HIDE);
		m_ctrlStatic46.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_SSCP_PORTA)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_SSCP_EOR_EXE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_SSCP_EOR_PARAM)->ShowWindow(SW_HIDE);

		m_ctrlStatic14.ShowWindow(SW_HIDE);
		m_ctrlStatic15.ShowWindow(SW_HIDE);
		m_ctrlStatic16.ShowWindow(SW_HIDE);
		m_ctrlStatic17.ShowWindow(SW_HIDE);
		m_ctrlStatic18.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_ETICH_00)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SPIN_ETICH_00)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_ETICH_01)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SPIN_ETICH_01)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_ETICH_02)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SPIN_ETICH_02)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_ETICH_03)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SPIN_ETICH_03)->ShowWindow(SW_HIDE);

		m_chkVisAbilita.ShowWindow(SW_HIDE);
		m_chkVisAbilitaMonitor.ShowWindow(SW_HIDE);
		m_ctrlStatic32.ShowWindow(SW_HIDE);
		m_ctrlStatic33.ShowWindow(SW_HIDE);
		m_ctrlStatic34.ShowWindow(SW_HIDE);
		m_ctrlStatic35.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_VIS_IP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_VIS_PORTA)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_VIS_PORTA_MONITOR)->ShowWindow(SW_HIDE);

		GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);
	}

	CStringList displayList;
	CDisplayHelper::GetDisplayList(&displayList);
	
	POSITION pos = displayList.GetHeadPosition();
	while (pos)
	{
		m_ctrlCmbDisplay.AddString(displayList.GetNext(pos));		
	}

	if (theApp.m_lOpenIntoMonitor < 0 || theApp.m_lOpenIntoMonitor >= displayList.GetCount())
	{
		m_ctrlCmbDisplay.SetCurSel(0);
	}
	else
	{
		m_ctrlCmbDisplay.SetCurSel(theApp.m_lOpenIntoMonitor);
	}

	theApp.LocalizeDialog(this, CSetupDlg::IDD, "SettingDlg");

    UpdateData(FALSE);

    return TRUE;
}

void CSetupDlg::OnOK() 
{
	UpdateData(TRUE);

	GetDlgItemText(IDC_PERCORSI_OD, theApp.m_sPathImageOD);

	theApp.m_bCheckRep = (m_chkRep.GetCheck() == BST_CHECKED);
	GetDlgItemText(IDC_EDIT_REP, theApp.m_sEditRep);

	theApp.m_bCheckImm = (m_chkImm.GetCheck() == BST_CHECKED);
	GetDlgItemText(IDC_EDIT_IMM, theApp.m_sEditImm);

	// m_btnProvincia.GetWindowText(theApp.m_strProvinciaDefault);
	theApp.m_lIDSedeEsameDefault = m_lIDSedeEsame;
	m_btnSala.GetWindowText(theApp.m_sSalaEsameDefault);

	theApp.m_nExpFormat = m_ctrlExpoFormat.GetCurSel();

	theApp.m_nArchivioImmaginiFormato = m_ctrlArchiveFormat.GetCurSel() + 1;
	m_pEsamiView->GetDocument()->SetIntValue("Archivio Immagini - Formato", theApp.m_nArchivioImmaginiFormato);
	theApp.m_nArchivioImmaginiQualita = m_ctrlSliderImm.GetPos();
	m_pEsamiView->GetDocument()->SetIntValue("Archivio Immagini - Qualita", theApp.m_nArchivioImmaginiQualita);
	theApp.m_nArchivioMiniatureQualita = m_ctrlSliderMin.GetPos();
	m_pEsamiView->GetDocument()->SetIntValue("Archivio Miniature - Qualita", theApp.m_nArchivioMiniatureQualita);

	theApp.m_nLanguage = (languages)m_nLanguage;

	theApp.m_bAutoDeselect = (m_chkDeseleziona.GetCheck() == BST_CHECKED);

	theApp.m_fEtichette00 = (float)m_ctrlSpinEtich00.GetPos32() / 10.0f ;
	theApp.m_fEtichette01 = (float)m_ctrlSpinEtich01.GetPos32() / 10.0f ;
	theApp.m_fEtichette02 = (float)m_ctrlSpinEtich02.GetPos32() / 100.0f ;
	theApp.m_fEtichette03 = (float)m_ctrlSpinEtich03.GetPos32() / 100.0f ;

	// theApp.m_bPazientiUsaVista = (m_chkUsaVista.GetCheck() == BST_CHECKED);
	GetDlgItemText(IDC_EDIT01, theApp.m_sPazientiTabella);
	// GetDlgItemText(IDC_EDIT02, theApp.m_sPazientiVista);
	// GetDlgItemText(IDC_EDIT03, theApp.m_sPazientiVistaOrdinamento);

	GetDlgItemText(IDC_EDIT_SSCP_PORTA, theApp.m_sStoreScpPorta);
	GetDlgItemText(IDC_EDIT_SSCP_EOR_EXE, theApp.m_sStoreScpExecOnReceptionExe);
	GetDlgItemText(IDC_EDIT_SSCP_EOR_PARAM, theApp.m_sStoreScpExecOnReceptionParameters);

	theApp.m_bVisAbilita = (m_chkVisAbilita.GetCheck() == BST_CHECKED);
	GetDlgItemText(IDC_EDIT_VIS_IP, theApp.m_sVisIp);
	CString sTemp;
	GetDlgItemText(IDC_EDIT_VIS_PORTA, sTemp);
	theApp.m_lVisPorta = atoi(sTemp);
	GetDlgItemText(IDC_EDIT_VIS_PORTA_MONITOR, sTemp);
	theApp.m_sVisPortaMonitor = sTemp;
	theApp.m_bVisAbilitaMonitor = (m_chkVisAbilitaMonitor.GetCheck() == BST_CHECKED);

	theApp.m_lOpenIntoMonitor = m_ctrlCmbDisplay.GetCurSel();

    CDialog::OnOK();
}

HBRUSH CSetupDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor (pDC, pWnd, nCtlColor);

	return hBrush;
}

void CSetupDlg::OnBnClickedBtnPercorsiOd()
{
	CString strTemp;
	GetDlgItemText(IDC_PERCORSI_OD, strTemp);

	CString strTitle = theApp.GetMessageString(IDS_FOLDERDLG_TITLE_7);
	CFolderDialog dlg(strTitle, strTemp, 64, this);
	if (dlg.DoModal() == IDOK)
		SetDlgItemText(IDC_PERCORSI_OD, dlg.GetSelectedFolder());
}

void CSetupDlg::OnBnClickedCheckRep()
{
	UpdateData(TRUE);
}

void CSetupDlg::OnBnClickedBtnRep()
{
	CString strTemp;
	GetDlgItemText(IDC_EDIT_REP, strTemp);

	CString strTitle = theApp.GetMessageString(IDS_FOLDERDLG_TITLE_2);
	CFolderDialog dlg(strTitle, strTemp, 64, this);

	if (dlg.DoModal() == IDOK)
		SetDlgItemText(IDC_EDIT_REP, dlg.GetSelectedFolder());
}

void CSetupDlg::OnBnClickedCheckImm()
{
	UpdateData(TRUE);
}

void CSetupDlg::OnBnClickedBtnImm()
{
	CString strTemp;
	GetDlgItemText(IDC_EDIT_IMM, strTemp);

	CString strTitle = theApp.GetMessageString(IDS_FOLDERDLG_TITLE_3);
	CFolderDialog dlg(strTitle, strTemp, 64, this);

	if (dlg.DoModal() == IDOK)
		SetDlgItemText(IDC_EDIT_IMM, dlg.GetSelectedFolder());
}

void CSetupDlg::OnReportDefault() 
{
	LOGFONT lfFont;

	memcpy(&(lfFont.lfFaceName), (LPCTSTR)g_sReportFaceName, 31);
	lfFont.lfHeight = -(long)((float)g_nReportSize * (float)4 / (float)3);
	lfFont.lfWidth = 0;
	lfFont.lfWeight = g_bReportBold ? FW_BOLD : FW_REGULAR;
	lfFont.lfItalic = g_bReportItalic;
	lfFont.lfUnderline = g_bReportUnderline;
	lfFont.lfStrikeOut = FALSE;

	CFontDialog	dlg(&lfFont);
	if (dlg.DoModal() == IDOK)
	{
		dlg.GetCurrentFont(&lfFont);

		// Sandro 08/11/2012 // non salvava la dimensione 10 del font //

		float fTemp = 0;
		if (lfFont.lfHeight < 0)
			fTemp = (float)-lfFont.lfHeight * (float)3 / (float)4;
		else
			fTemp = (float)lfFont.lfHeight * (float)3 / (float)4;

		//

		g_sReportFaceName = lfFont.lfFaceName;
		g_nReportSize = (int)(fTemp + (float)0.499);
		g_bReportBold = lfFont.lfWeight > FW_REGULAR ? TRUE: FALSE;
		g_bReportItalic = lfFont.lfItalic;
		g_bReportUnderline = lfFont.lfUnderline;
	}
}

void CSetupDlg::OnBnClickedBtnSede()
{
	CSediEsameUseDlg dlgTemp(this, m_pEsamiView);

	dlgTemp.SetSede(m_lIDSedeEsame);

	if (dlgTemp.DoModal() == IDOK)
	{
		m_lIDSedeEsame = dlgTemp.GetSede();
		m_btnSede.SetWindowText(CSediEsameSet().GetDescrizione(m_lIDSedeEsame, FALSE));
		m_btnSala.SetWindowText("");
	}
}

void CSetupDlg::OnBnClickedBtnSala()
{
	CSaleEsameUseDlg dlgTemp(this, m_pEsamiView, m_lIDSedeEsame);

	CString strTemp;
	m_btnSala.GetWindowText(strTemp);
	dlgTemp.SetSala(strTemp);

	if (dlgTemp.DoModal() == IDOK)
		m_btnSala.SetWindowText(dlgTemp.GetSala());
}

void CSetupDlg::OnBnClickedButtonImm1Set()
{
	prnImmagini.PrinterSetup(this);
	if (prnImmagini.GetDevModePointer())
		prnImmagini.Save(theApp.m_sDirProg + "\\" + "PrinterImmagini.dat");
	SetDlgItemText(IDC_EDIT_IMM1, prnImmagini.GetPrinterName());
}

void CSetupDlg::OnBnClickedButtonImm1Del()
{
	CPrinterSettings prnEmpty;
	prnImmagini = prnEmpty;

	SetDlgItemText(IDC_EDIT_IMM1, prnImmagini.GetPrinterName());

	DeleteFile(theApp.m_sDirProg + "\\" + "PrinterImmagini.dat");
}

void CSetupDlg::OnBnClickedButtonRep1Set()
{
	prnReports1.PrinterSetup(this);
	if (prnReports1.GetDevModePointer())
		prnReports1.Save(theApp.m_sDirProg + "\\" + "PrinterReports.dat");
	SetDlgItemText(IDC_EDIT_REP1, prnReports1.GetPrinterName());
}

void CSetupDlg::OnBnClickedButtonRep1Del()
{
	CPrinterSettings prnEmpty;
	prnReports1 = prnEmpty;

	SetDlgItemText(IDC_EDIT_REP1, prnReports1.GetPrinterName());

	DeleteFile(theApp.m_sDirProg + "\\" + "PrinterReports.dat");
}

void CSetupDlg::OnBnClickedButtonRep2Set()
{
	prnReports2.PrinterSetup(this);
	if (prnReports2.GetDevModePointer())
		prnReports2.Save(theApp.m_sDirProg + "\\" + "PrinterReports2.dat");
	SetDlgItemText(IDC_EDIT_REP2, prnReports2.GetPrinterName());
}

void CSetupDlg::OnBnClickedButtonRep2Del()
{
	CPrinterSettings prnEmpty;
	prnReports2 = prnEmpty;

	SetDlgItemText(IDC_EDIT_REP2, prnReports2.GetPrinterName());

	DeleteFile(theApp.m_sDirProg + "\\" + "PrinterReports2.dat");
}

void CSetupDlg::OnBnClickedButtonRep3Set()
{
	prnReports3.PrinterSetup(this);
	if (prnReports3.GetDevModePointer())
		prnReports3.Save(theApp.m_sDirProg + "\\" + "PrinterReports3.dat");
	SetDlgItemText(IDC_EDIT_REP3, prnReports3.GetPrinterName());
}

void CSetupDlg::OnBnClickedButtonRep3Del()
{
	CPrinterSettings prnEmpty;
	prnReports3 = prnEmpty;

	SetDlgItemText(IDC_EDIT_REP3, prnReports3.GetPrinterName());

	DeleteFile(theApp.m_sDirProg + "\\" + "PrinterReports3.dat");
}

void CSetupDlg::OnBnClickedButtonRep4Set()
{
	prnReports4.PrinterSetup(this);
	if (prnReports4.GetDevModePointer())
		prnReports4.Save(theApp.m_sDirProg + "\\" + "PrinterReports4.dat");
	SetDlgItemText(IDC_EDIT_REP4, prnReports4.GetPrinterName());
}

void CSetupDlg::OnBnClickedButtonRep4Del()
{
	CPrinterSettings prnEmpty;
	prnReports4 = prnEmpty;

	SetDlgItemText(IDC_EDIT_REP4, prnReports4.GetPrinterName());

	DeleteFile(theApp.m_sDirProg + "\\" + "PrinterReports4.dat");
}

void CSetupDlg::OnBnClickedButtonRep5Set()
{
	prnReports5.PrinterSetup(this);
	if (prnReports5.GetDevModePointer())
		prnReports5.Save(theApp.m_sDirProg + "\\" + "PrinterReports5.dat");
	SetDlgItemText(IDC_EDIT_REP5, prnReports5.GetPrinterName());
}

void CSetupDlg::OnBnClickedButtonRep5Del()
{
	CPrinterSettings prnEmpty;
	prnReports5 = prnEmpty;

	SetDlgItemText(IDC_EDIT_REP5, prnReports5.GetPrinterName());

	DeleteFile(theApp.m_sDirProg + "\\" + "PrinterReports5.dat");
}

void CSetupDlg::OnBnClickedButtonRep6Set()
{
	prnReports6.PrinterSetup(this);
	if (prnReports6.GetDevModePointer())
		prnReports6.Save(theApp.m_sDirProg + "\\" + "PrinterReports6.dat");
	SetDlgItemText(IDC_EDIT_REP6, prnReports6.GetPrinterName());
}

void CSetupDlg::OnBnClickedButtonRep6Del()
{
	CPrinterSettings prnEmpty;
	prnReports6 = prnEmpty;

	SetDlgItemText(IDC_EDIT_REP6, prnReports6.GetPrinterName());

	DeleteFile(theApp.m_sDirProg + "\\" + "PrinterReports6.dat");
}

void CSetupDlg::OnBnClickedButtonRep7Set()
{
	prnReports7.PrinterSetup(this);
	if (prnReports7.GetDevModePointer())
		prnReports7.Save(theApp.m_sDirProg + "\\" + "PrinterReports7.dat");
	SetDlgItemText(IDC_EDIT_REP7, prnReports7.GetPrinterName());
}

void CSetupDlg::OnBnClickedButtonRep7Del()
{
	CPrinterSettings prnEmpty;
	prnReports7 = prnEmpty;

	SetDlgItemText(IDC_EDIT_REP7, prnReports7.GetPrinterName());

	DeleteFile(theApp.m_sDirProg + "\\" + "PrinterReports7.dat");
}

void CSetupDlg::OnBnClickedButtonRep8Set()
{
	prnReports8.PrinterSetup(this);
	if (prnReports8.GetDevModePointer())
		prnReports8.Save(theApp.m_sDirProg + "\\" + "PrinterReports8.dat");
	SetDlgItemText(IDC_EDIT_REP8, prnReports8.GetPrinterName());
}

void CSetupDlg::OnBnClickedButtonRep8Del()
{
	CPrinterSettings prnEmpty;
	prnReports8 = prnEmpty;

	SetDlgItemText(IDC_EDIT_REP8, prnReports8.GetPrinterName());

	DeleteFile(theApp.m_sDirProg + "\\" + "PrinterReports8.dat");
}

void CSetupDlg::OnBnClickedButtonRep9Set()
{
	prnReports9.PrinterSetup(this);
	if (prnReports9.GetDevModePointer())
		prnReports9.Save(theApp.m_sDirProg + "\\" + "PrinterReports9.dat");
	SetDlgItemText(IDC_EDIT_REP9, prnReports9.GetPrinterName());
}

void CSetupDlg::OnBnClickedButtonRep9Del()
{
	CPrinterSettings prnEmpty;
	prnReports9 = prnEmpty;

	SetDlgItemText(IDC_EDIT_REP9, prnReports9.GetPrinterName());

	DeleteFile(theApp.m_sDirProg + "\\" + "PrinterReports9.dat");
}

void CSetupDlg::OnBnClickedChkPazOrdEsa()
{
	GetDlgItem(IDC_EDIT02)->EnableWindow(m_chkUsaVista.GetCheck() == BST_CHECKED);
	GetDlgItem(IDC_EDIT03)->EnableWindow(m_chkUsaVista.GetCheck() == BST_CHECKED);
}

void CSetupDlg::OnBnClickedChkVisAbilita()
{
	GetDlgItem(IDC_EDIT_VIS_IP)->EnableWindow(m_chkVisAbilita.GetCheck());
	GetDlgItem(IDC_EDIT_VIS_PORTA)->EnableWindow(m_chkVisAbilita.GetCheck());
	GetDlgItem(IDC_CHK_VIS_ABILITA_MONITOR)->EnableWindow(m_chkVisAbilita.GetCheck());
	GetDlgItem(IDC_EDIT_VIS_PORTA_MONITOR)->EnableWindow(m_chkVisAbilita.GetCheck());
	GetDlgItem(IDC_STATIC_33)->EnableWindow(m_chkVisAbilita.GetCheck());
	GetDlgItem(IDC_STATIC_34)->EnableWindow(m_chkVisAbilita.GetCheck());
	GetDlgItem(IDC_STATIC_35)->EnableWindow(m_chkVisAbilita.GetCheck());
}

void CSetupDlg::OnBnClickedChkVisAbilitaMonitor()
{
	GetDlgItem(IDC_EDIT_VIS_PORTA_MONITOR)->EnableWindow(m_chkVisAbilitaMonitor.GetCheck());
}

void CSetupDlg::OnCbnSelchangeArchiveFormat()
{
	int nConvFormat = m_ctrlArchiveFormat.GetCurSel() + 1;

	if ((nConvFormat == image_jp2) || (nConvFormat == image_jpg))
	{
		CString strQuality;
		strQuality.Format("%d", m_ctrlSliderImm.GetPos());
		m_ctrlStatic38.SetWindowText(strQuality);

		m_ctrlStatic37.ShowWindow(SW_SHOW);
		m_ctrlStatic38.ShowWindow(SW_SHOW);
		m_ctrlSliderImm.ShowWindow(SW_SHOW);
	}
	else
	{
		m_ctrlStatic37.ShowWindow(SW_HIDE);
		m_ctrlStatic38.ShowWindow(SW_HIDE);
		m_ctrlSliderImm.ShowWindow(SW_HIDE);
	}
}

void CSetupDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

	if (pScrollBar->GetSafeHwnd() == m_ctrlSliderImm.GetSafeHwnd())
	{
		CString strQuality;
		strQuality.Format("%d", m_ctrlSliderImm.GetPos());
		m_ctrlStatic38.SetWindowText(strQuality);
	}
	else if (pScrollBar->GetSafeHwnd() == m_ctrlSliderMin.GetSafeHwnd())
	{
		CString strQuality;
		strQuality.Format("%d", m_ctrlSliderMin.GetPos());
		m_ctrlStatic41.SetWindowText(strQuality);
	}
}
