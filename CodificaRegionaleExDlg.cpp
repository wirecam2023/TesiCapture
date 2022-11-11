#include "stdafx.h"
#include "Endox.h"
#include "CodificaRegionaleExDlg.h"

#include "CustomDate.h"
#include "EsamiView.h"
#include "MyPrintDialog.h"
#include "TipoEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCodificaRegionaleExDlg, CDialog)

CCodificaRegionaleExDlg::CCodificaRegionaleExDlg(CWnd* pParent)
	: CDialog(CCodificaRegionaleExDlg::IDD, pParent)
{
	m_iModalita = CORE_VISUA;
}

CCodificaRegionaleExDlg::~CCodificaRegionaleExDlg()
{
	m_setCodificaRegionaleEx.CloseRecordset("~CCodificaRegionaleExDlg");
}

void CCodificaRegionaleExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_00, m_ctrlList00);

	DDX_Control(pDX, IDOK,          m_ctrlButtonOK);
	DDX_Control(pDX, IDC_BTN_SAV,   m_ctrlButtonSav);
	DDX_Control(pDX, IDC_BTN_UND,   m_ctrlButtonUnd);
	DDX_Control(pDX, IDC_BTN_PRI,   m_ctrlButtonPri);
	DDX_Control(pDX, IDC_BTN_NEW,   m_ctrlButtonNew);
	DDX_Control(pDX, IDC_BTN_EDT,   m_ctrlButtonEdt);
	DDX_Control(pDX, IDC_BTN_DLT,   m_ctrlButtonDel);
	DDX_Control(pDX, IDC_FRAME_00 , m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic03);
	DDX_Control(pDX, IDC_STATIC_05, m_ctrlStatic04);
	DDX_Control(pDX, IDC_FRAME_02 , m_ctrlStatic05);
	DDX_Control(pDX, IDC_STATIC_06, m_ctrlStatic06);
	DDX_Control(pDX, IDC_FRAME_03 , m_ctrlStatic07);
	DDX_Control(pDX, IDC_STATIC_07, m_ctrlStatic08);
	DDX_Control(pDX, IDC_STATIC_08, m_ctrlStatic09);
	DDX_Control(pDX, IDC_STATIC_09, m_ctrlStatic10);
	DDX_Control(pDX, IDC_FRAME_04 , m_ctrlStatic11);
	DDX_Control(pDX, IDC_STATIC_10, m_ctrlStatic12);
	DDX_Control(pDX, IDC_STATIC_11, m_ctrlStatic13);
	DDX_Control(pDX, IDC_STATIC_12, m_ctrlStatic14);
	DDX_Control(pDX, IDC_FRAME_05 , m_ctrlStatic15);
	DDX_Control(pDX, IDC_STATIC_13, m_ctrlStatic16);
	DDX_Control(pDX, IDC_FRAME_06 , m_ctrlStatic17);
	DDX_Control(pDX, IDC_STATIC_14, m_ctrlStatic18);
	DDX_Control(pDX, IDC_STATIC_15, m_ctrlStatic19);
	DDX_Control(pDX, IDC_STATIC_16, m_ctrlStatic20);
	DDX_Control(pDX, IDC_STATIC_17, m_ctrlStatic21);
	DDX_Control(pDX, IDC_STATIC_18, m_ctrlStatic22);
	DDX_Control(pDX, IDC_STATIC_19, m_ctrlStatic23);
	DDX_Control(pDX, IDC_STATIC_20, m_ctrlStatic24);
	DDX_Control(pDX, IDC_STATIC_21, m_ctrlStatic25);
	DDX_Control(pDX, IDC_STATIC_22, m_ctrlStatic26);
	DDX_Control(pDX, IDC_STATIC_23, m_ctrlStatic27);
	DDX_Control(pDX, IDC_STATIC_24, m_ctrlStatic28);
	DDX_Control(pDX, IDC_STATIC_25, m_ctrlStatic29);
	DDX_Control(pDX, IDC_STATIC_26, m_ctrlStatic30);
	DDX_Control(pDX, IDC_STATIC_27, m_ctrlStatic31);
	DDX_Control(pDX, IDC_STATIC_28, m_ctrlStatic32);
	DDX_Control(pDX, IDC_STATIC_29, m_ctrlStatic33);
	DDX_Control(pDX, IDC_STATIC_36, m_ctrlStatic34);
	DDX_Control(pDX, IDC_STATIC_37, m_ctrlStatic35);
	DDX_Control(pDX, IDC_STATIC_38, m_ctrlStatic36);
//	DDX_Control(pDX, IDC_STATIC_39, m_ctrlStatic39);
	DDX_Control(pDX, IDC_STATIC_40, m_ctrlStatic40);
	DDX_Control(pDX, IDC_STATIC_41, m_ctrlStatic41);
	DDX_Control(pDX, IDC_STATIC_43, m_ctrlStatic43);
	DDX_Control(pDX, IDC_STATIC_44, m_ctrlStatic44);
	//DDX_Control(pDX, IDC_STATIC_45, m_ctrlStatic45);
	DDX_Control(pDX, IDC_COMBO_41, m_ctrlComboTipoEsame);
	DDX_Control(pDX, IDC_CHECK_PRESTAZIONEPRINCIPALE, m_ctrlCheckPrestazionePrincipale);
	DDX_Control(pDX, IDC_CHECK_PRESTAZIONENORMATA, m_ctrlCheckPrestazioneNormata);
	DDX_Control(pDX, IDC_CHECK_PRESTAZIONEPNGLA, m_ctrlCheckPrestazionePNGLA);
}

BEGIN_MESSAGE_MAP(CCodificaRegionaleExDlg, CDialog)

	ON_WM_CTLCOLOR()

	ON_LBN_SELCHANGE(IDC_LIST_00, OnLbnSelchangeList00)

	ON_BN_CLICKED(IDC_BTN_SAV, OnBnClickedBtnSav)
	ON_BN_CLICKED(IDC_BTN_UND, OnBnClickedBtnUnd)
	ON_BN_CLICKED(IDC_BTN_PRI, OnBnClickedBtnPri)
	ON_BN_CLICKED(IDC_BTN_NEW, OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBnClickedBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DLT, OnBnClickedBtnDel)

	ON_EN_CHANGE(IDC_EDIT_06, OnEnChangeEdit06)
	ON_EN_CHANGE(IDC_EDIT_07, OnEnChangeEdit07)
	ON_EN_CHANGE(IDC_EDIT_08, OnEnChangeEdit08)
	ON_EN_CHANGE(IDC_EDIT_10, OnEnChangeEdit10)
	ON_EN_CHANGE(IDC_EDIT_11, OnEnChangeEdit11)
	ON_EN_CHANGE(IDC_EDIT_14, OnEnChangeEdit14)
	ON_EN_CHANGE(IDC_EDIT_17, OnEnChangeEdit17)
	ON_EN_CHANGE(IDC_EDIT_20, OnEnChangeEdit20)
	ON_EN_CHANGE(IDC_EDIT_23, OnEnChangeEdit23)
	ON_EN_CHANGE(IDC_EDIT_26, OnEnChangeEdit26)
	ON_EN_CHANGE(IDC_EDIT_36, OnEnChangeEdit36)

END_MESSAGE_MAP()

HBRUSH CCodificaRegionaleExDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor (pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_29:
		case IDC_EDIT_29:
		{
			// pDC->SetTextColor(theApp.m_colorFrame);
			break;
		}
		case IDC_EDIT_04:
		case IDC_STATIC_05:
		case IDC_EDIT_05:
		{
			pDC->SetTextColor(theApp.m_color[0]);
			break;
		}
		case IDC_STATIC_40:
		case IDC_STATIC_41:
		case IDC_STATIC_43:
		case IDC_STATIC_44:
		case IDC_EDIT_40:
		case IDC_EDIT_44:
		case IDC_COMBO_41:		
		{
			pDC->SetTextColor(theApp.m_color[2]);
			break;
		}
	}

	return hBrush;
}

BOOL CCodificaRegionaleExDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDC_FRAME_00)->SetFont(&theApp.m_fontBig);
	GetDlgItem(IDC_FRAME_01)->SetFont(&theApp.m_fontBig);
	GetDlgItem(IDC_FRAME_02)->SetFont(&theApp.m_fontBig);
	GetDlgItem(IDC_FRAME_03)->SetFont(&theApp.m_fontBig);
	GetDlgItem(IDC_FRAME_04)->SetFont(&theApp.m_fontBig);
	GetDlgItem(IDC_FRAME_05)->SetFont(&theApp.m_fontBig);
	GetDlgItem(IDC_FRAME_06)->SetFont(&theApp.m_fontBig);
	
	GetDlgItem(IDC_EDIT_04)->SetFont(&theApp.m_fontBold);

	GetDlgItem(IDC_STATIC_05)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_EDIT_05)->SetFont(&theApp.m_fontBold);

	GetDlgItem(IDC_STATIC_06)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_EDIT_06)->SetFont(&theApp.m_fontBold);

	GetDlgItem(IDC_STATIC_09)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_EDIT_09)->SetFont(&theApp.m_fontBold);

	GetDlgItem(IDC_STATIC_12)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_EDIT_12)->SetFont(&theApp.m_fontBold);

	GetDlgItem(IDC_STATIC_13)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_EDIT_13)->SetFont(&theApp.m_fontBold);

	GetDlgItem(IDC_STATIC_14)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_EDIT_14)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_17)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_EDIT_17)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_20)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_EDIT_20)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_23)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_EDIT_23)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_26)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_EDIT_26)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_29)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_EDIT_29)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_36)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_EDIT_36)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_39)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_EDIT_39)->SetFont(&theApp.m_fontBold);

	GetDlgItem(IDC_STATIC_43)->SetFont(&theApp.m_fontBold);

	// Sandro 24/10/2013 //
	GetDlgItem(IDC_EDIT_02)->SendMessage(EM_SETLIMITTEXT, 9);
	GetDlgItem(IDC_EDIT_03)->SendMessage(EM_SETLIMITTEXT, 9);

	// inizializzo combo esami //
	CTipoEsameSet tipoEsameSet;
	if (tipoEsameSet.OpenRecordset("CCodificaRegionaleExDlg::OnInitDialog"))
	{
		int el = m_ctrlComboTipoEsame.AddString("");
		m_ctrlComboTipoEsame.SetItemData(el, -1);
		while(!tipoEsameSet.IsEOF())
		{
			int element = m_ctrlComboTipoEsame.AddString(tipoEsameSet.m_sDescrizione);
			m_ctrlComboTipoEsame.SetItemData(element, tipoEsameSet.m_lContatore);
			tipoEsameSet.MoveNext();
		}
		tipoEsameSet.CloseRecordset("CCodificaRegionaleExDlg::OnInitDialog");
	}

	// -->
	int iIndex = 0;

	m_setCodificaRegionaleEx.SetSortRecord("Descrizione");
	if (m_setCodificaRegionaleEx.OpenRecordset("OnInitDialog") == FALSE)
		return FALSE;

	while(m_setCodificaRegionaleEx.IsEOF() == FALSE)
	{
		m_ctrlList00.InsertString(iIndex, m_setCodificaRegionaleEx.m_sDescrizione);
		m_ctrlList00.SetItemData(iIndex, m_setCodificaRegionaleEx.m_lContatore);

		iIndex++;
		m_setCodificaRegionaleEx.MoveNext();
	}

	m_setCodificaRegionaleEx.SetSortRecord("Contatore");

	if (m_ctrlList00.GetCount() > 0)
	{
		m_ctrlList00.SetCurSel(0);
		OnLbnSelchangeList00();
	}
	// <--
	
	theApp.LocalizeDialog(this, CCodificaRegionaleExDlg::IDD, "CodificaRegionaleExDlg");

	return TRUE;
}

void CCodificaRegionaleExDlg::OnLbnSelchangeList00()
{
	int nCurSel = m_ctrlList00.GetCurSel();
	long lContatore;

	if (nCurSel != LB_ERR)
	{
		GetDlgItem(IDC_BTN_EDT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_DLT)->EnableWindow(TRUE);

		lContatore = m_ctrlList00.GetItemData(nCurSel);

		CString strFilter;
		strFilter.Format("Contatore=%li", lContatore);

		m_setCodificaRegionaleEx.SetOpenFilter(strFilter);
		m_setCodificaRegionaleEx.OpenRecordset("OnLbnSelchangeList00");

		VisualizzaDati();
	}
	else
	{
		GetDlgItem(IDC_BTN_EDT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_DLT)->EnableWindow(FALSE);

		SvuotaDialog();
	}
}

void CCodificaRegionaleExDlg::CambiaModalita(int iNuovaModalita)
{
	GetDlgItem(IDC_LIST_00)->EnableWindow(iNuovaModalita == CORE_VISUA);
	GetDlgItem(IDC_BTN_PRI)->ShowWindow(iNuovaModalita == CORE_VISUA ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_BTN_NEW)->ShowWindow(iNuovaModalita == CORE_VISUA ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_BTN_EDT)->ShowWindow(iNuovaModalita == CORE_VISUA ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_BTN_DLT)->ShowWindow(iNuovaModalita == CORE_VISUA ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_BTN_SAV)->ShowWindow(iNuovaModalita == CORE_VISUA ? SW_HIDE : SW_SHOW);
	GetDlgItem(IDC_BTN_UND)->ShowWindow(iNuovaModalita == CORE_VISUA ? SW_HIDE : SW_SHOW);

	SendDlgItemMessage(IDC_EDIT_02, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
	SendDlgItemMessage(IDC_EDIT_03, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
	SendDlgItemMessage(IDC_EDIT_04, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
//	SendDlgItemMessage(IDC_EDIT_05, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);

	SendDlgItemMessage(IDC_EDIT_06, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);

	SendDlgItemMessage(IDC_EDIT_07, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
	SendDlgItemMessage(IDC_EDIT_08, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
//	SendDlgItemMessage(IDC_EDIT_09, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);

	SendDlgItemMessage(IDC_EDIT_10, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
	SendDlgItemMessage(IDC_EDIT_11, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
//	SendDlgItemMessage(IDC_EDIT_12, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);

//	SendDlgItemMessage(IDC_EDIT_13, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);

	SendDlgItemMessage(IDC_EDIT_14, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
	SendDlgItemMessage(IDC_EDIT_15, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
	SendDlgItemMessage(IDC_EDIT_16, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
	SendDlgItemMessage(IDC_EDIT_17, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
	SendDlgItemMessage(IDC_EDIT_18, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
	SendDlgItemMessage(IDC_EDIT_19, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
	SendDlgItemMessage(IDC_EDIT_20, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
	SendDlgItemMessage(IDC_EDIT_21, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
	SendDlgItemMessage(IDC_EDIT_22, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
	SendDlgItemMessage(IDC_EDIT_23, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
	SendDlgItemMessage(IDC_EDIT_24, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
	SendDlgItemMessage(IDC_EDIT_25, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
	SendDlgItemMessage(IDC_EDIT_26, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
	SendDlgItemMessage(IDC_EDIT_27, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
	SendDlgItemMessage(IDC_EDIT_28, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
//	SendDlgItemMessage(IDC_EDIT_29, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
	SendDlgItemMessage(IDC_EDIT_36, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
	SendDlgItemMessage(IDC_EDIT_37, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
	SendDlgItemMessage(IDC_EDIT_38, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
	SendDlgItemMessage(IDC_EDIT_39, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);

	SendDlgItemMessage(IDC_EDIT_40, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
	SendDlgItemMessage(IDC_EDIT_44, EM_SETREADONLY, (WPARAM)(iNuovaModalita == CORE_VISUA), (LPARAM)0);
	m_ctrlComboTipoEsame.EnableWindow(!(iNuovaModalita == CORE_VISUA));
	m_ctrlCheckPrestazionePrincipale.EnableWindow(!(iNuovaModalita == CORE_VISUA));
	m_ctrlCheckPrestazioneNormata.EnableWindow(!(iNuovaModalita == CORE_VISUA));
	m_ctrlCheckPrestazionePNGLA.EnableWindow(!(iNuovaModalita == CORE_VISUA));

	m_iModalita = iNuovaModalita;
}

void CCodificaRegionaleExDlg::SvuotaDialog()
{
	SetDlgItemText(IDC_EDIT_02, "");
	SetDlgItemText(IDC_EDIT_03, "");
	SetDlgItemText(IDC_EDIT_04, "");
	SetDlgItemText(IDC_EDIT_05, "0.00");

	SetDlgItemText(IDC_EDIT_06, "0.00");

	SetDlgItemText(IDC_EDIT_07, "0.00");
	SetDlgItemText(IDC_EDIT_08, "0.00");
	SetDlgItemText(IDC_EDIT_09, "0.00");

	SetDlgItemText(IDC_EDIT_10, "0.00");
	SetDlgItemText(IDC_EDIT_11, "0.00");
	SetDlgItemText(IDC_EDIT_12, "0.00");

	SetDlgItemText(IDC_EDIT_13, "0.00");

	SetDlgItemText(IDC_EDIT_14, "0.00");
	SetDlgItemText(IDC_EDIT_15, "0.0");
	SetDlgItemText(IDC_EDIT_16, "0");
	SetDlgItemText(IDC_EDIT_17, "0.00");
	SetDlgItemText(IDC_EDIT_18, "0.0");
	SetDlgItemText(IDC_EDIT_19, "0");
	SetDlgItemText(IDC_EDIT_20, "0.00");
	SetDlgItemText(IDC_EDIT_21, "0.0");
	SetDlgItemText(IDC_EDIT_22, "0");
	SetDlgItemText(IDC_EDIT_23, "0.00");
	SetDlgItemText(IDC_EDIT_24, "0.0");
	SetDlgItemText(IDC_EDIT_25, "0");
	SetDlgItemText(IDC_EDIT_26, "0.00");
	SetDlgItemText(IDC_EDIT_27, "0.0");
	SetDlgItemText(IDC_EDIT_28, "0");
	SetDlgItemText(IDC_EDIT_36, "0.00");
	SetDlgItemText(IDC_EDIT_37, "0.0");
	SetDlgItemText(IDC_EDIT_38, "0");
	SetDlgItemText(IDC_EDIT_39, "0.00");

	SetDlgItemText(IDC_EDIT_29, "0.00");

	SetDlgItemText(IDC_EDIT_40, "");
	SetDlgItemText(IDC_EDIT_44, "");
	m_ctrlComboTipoEsame.SetCurSel(0);
	m_ctrlCheckPrestazionePrincipale.SetCheck(BST_CHECKED);
	m_ctrlCheckPrestazioneNormata.SetCheck(BST_UNCHECKED);
	m_ctrlCheckPrestazionePNGLA.SetCheck(BST_UNCHECKED);
}

void CCodificaRegionaleExDlg::VisualizzaDati()
{
	if (m_setCodificaRegionaleEx.IsOpen() && !m_setCodificaRegionaleEx.IsBOF() && !m_setCodificaRegionaleEx.IsEOF())
	{
		CString strTemp;
		strTemp.Format("%li", m_setCodificaRegionaleEx.m_lContatore);
		SetDlgItemText(IDC_EDIT_01, strTemp);

		SetDlgItemText(IDC_EDIT_02, m_setCodificaRegionaleEx.m_sCodiceNazionale);
		SetDlgItemText(IDC_EDIT_03, m_setCodificaRegionaleEx.m_sCodiceRegionale);
		SetDlgItemText(IDC_EDIT_04, m_setCodificaRegionaleEx.m_sDescrizione);
		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fTotaleGlobale))
		{
			SetDlgItemText(IDC_EDIT_05, "0.00");
		}
		else
		{
			strTemp.Format("%.2f", m_setCodificaRegionaleEx.m_fTotaleGlobale);
			SetDlgItemText(IDC_EDIT_05, strTemp);
		}

		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fTotaleCostoMateriali))
		{
			SetDlgItemText(IDC_EDIT_06, "0.00");
		}
		else
		{
			strTemp.Format("%.2f", m_setCodificaRegionaleEx.m_fTotaleCostoMateriali);
			SetDlgItemText(IDC_EDIT_06, strTemp);
		}

		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fManutenzioneDedicata))
		{
			SetDlgItemText(IDC_EDIT_07, "0.00");
		}
		else
		{
			strTemp.Format("%.2f", m_setCodificaRegionaleEx.m_fManutenzioneDedicata);
			SetDlgItemText(IDC_EDIT_07, strTemp);
		}
		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fManutenzioneBase))
		{
			SetDlgItemText(IDC_EDIT_08, "0.00");
		}
		else
		{
			strTemp.Format("%.2f", m_setCodificaRegionaleEx.m_fManutenzioneBase);
			SetDlgItemText(IDC_EDIT_08, strTemp);
		}
		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fTotaleCostoManutenzione))
		{
			SetDlgItemText(IDC_EDIT_09, "0.00");
		}
		else
		{
			strTemp.Format("%.2f", m_setCodificaRegionaleEx.m_fTotaleCostoManutenzione);
			SetDlgItemText(IDC_EDIT_09, strTemp);
		}

		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fAmmortamentoDedicata))
		{
			SetDlgItemText(IDC_EDIT_10, "0.00");
		}
		else
		{
			strTemp.Format("%.2f", m_setCodificaRegionaleEx.m_fAmmortamentoDedicata);
			SetDlgItemText(IDC_EDIT_10, strTemp);
		}
		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fAmmortamentoBase))
		{
			SetDlgItemText(IDC_EDIT_11, "0.00");
		}
		else
		{
			strTemp.Format("%.2f", m_setCodificaRegionaleEx.m_fAmmortamentoBase);
			SetDlgItemText(IDC_EDIT_11, strTemp);
		}
		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fTotaleCostoAmmortamento))
		{
			SetDlgItemText(IDC_EDIT_12, "0.00");
		}
		else
		{
			strTemp.Format("%.2f", m_setCodificaRegionaleEx.m_fTotaleCostoAmmortamento);
			SetDlgItemText(IDC_EDIT_12, strTemp);
		}

		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fTotaleCostiGenerali))
		{
			SetDlgItemText(IDC_EDIT_13, "0.00");
		}
		else
		{
			strTemp.Format("%.2f", m_setCodificaRegionaleEx.m_fTotaleCostiGenerali);
			SetDlgItemText(IDC_EDIT_13, strTemp);
		}

		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fEndoscopistaCosto))
		{
			SetDlgItemText(IDC_EDIT_14, "0.00");
		}
		else
		{
			strTemp.Format("%.2f", m_setCodificaRegionaleEx.m_fEndoscopistaCosto);
			SetDlgItemText(IDC_EDIT_14, strTemp);
		}
		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fEndoscopistaNumero))
		{
			SetDlgItemText(IDC_EDIT_15, "0.0");
		}
		else
		{
			strTemp.Format("%.1f", m_setCodificaRegionaleEx.m_fEndoscopistaNumero);
			SetDlgItemText(IDC_EDIT_15, strTemp);
		}
		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fEndoscopistaMinuti))
		{
			SetDlgItemText(IDC_EDIT_16, "0");
		}
		else
		{
			strTemp.Format("%.0f", m_setCodificaRegionaleEx.m_fEndoscopistaMinuti);
			SetDlgItemText(IDC_EDIT_16, strTemp);
		}
		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fRadiologoCosto))
		{
			SetDlgItemText(IDC_EDIT_17, "0.00");
		}
		else
		{
			strTemp.Format("%.2f", m_setCodificaRegionaleEx.m_fRadiologoCosto);
			SetDlgItemText(IDC_EDIT_17, strTemp);
		}
		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fRadiologoNumero))
		{
			SetDlgItemText(IDC_EDIT_18, "0.0");
		}
		else
		{
			strTemp.Format("%.1f", m_setCodificaRegionaleEx.m_fRadiologoNumero);
			SetDlgItemText(IDC_EDIT_18, strTemp);
		}
		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fRadiologoMinuti))
		{
			SetDlgItemText(IDC_EDIT_19, "0");
		}
		else
		{
			strTemp.Format("%.0f", m_setCodificaRegionaleEx.m_fRadiologoMinuti);
			SetDlgItemText(IDC_EDIT_19, strTemp);
		}
		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fInfermiereCosto))
		{
			SetDlgItemText(IDC_EDIT_20, "0.00");
		}
		else
		{
			strTemp.Format("%.2f", m_setCodificaRegionaleEx.m_fInfermiereCosto);
			SetDlgItemText(IDC_EDIT_20, strTemp);
		}
		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fInfermiereNumero))
		{
			SetDlgItemText(IDC_EDIT_21, "0.0");
		}
		else
		{
			strTemp.Format("%.1f", m_setCodificaRegionaleEx.m_fInfermiereNumero);
			SetDlgItemText(IDC_EDIT_21, strTemp);
		}
		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fInfermiereMinuti))
		{
			SetDlgItemText(IDC_EDIT_22, "0");
		}
		else
		{
			strTemp.Format("%.0f", m_setCodificaRegionaleEx.m_fInfermiereMinuti);
			SetDlgItemText(IDC_EDIT_22, strTemp);
		}
		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fOtaaCosto))
		{
			SetDlgItemText(IDC_EDIT_23, "0.00");
		}
		else
		{
			strTemp.Format("%.2f", m_setCodificaRegionaleEx.m_fOtaaCosto);
			SetDlgItemText(IDC_EDIT_23, strTemp);
		}
		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fOtaaNumero))
		{
			SetDlgItemText(IDC_EDIT_24, "0.0");
		}
		else
		{
			strTemp.Format("%.1f", m_setCodificaRegionaleEx.m_fOtaaNumero);
			SetDlgItemText(IDC_EDIT_24, strTemp);
		}
		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fOtaaMinuti))
		{
			SetDlgItemText(IDC_EDIT_25, "0");
		}
		else
		{
			strTemp.Format("%.0f", m_setCodificaRegionaleEx.m_fOtaaMinuti);
			SetDlgItemText(IDC_EDIT_25, strTemp);
		}
		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fAmministrativoCosto))
		{
			SetDlgItemText(IDC_EDIT_26, "0.00");
		}
		else
		{
			strTemp.Format("%.2f", m_setCodificaRegionaleEx.m_fAmministrativoCosto);
			SetDlgItemText(IDC_EDIT_26, strTemp);
		}
		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fAmministrativoNumero))
		{
			SetDlgItemText(IDC_EDIT_27, "0.0");
		}
		else
		{
			strTemp.Format("%.1f", m_setCodificaRegionaleEx.m_fAmministrativoNumero);
			SetDlgItemText(IDC_EDIT_27, strTemp);
		}
		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fAmministrativoMinuti))
		{
			SetDlgItemText(IDC_EDIT_28, "0");
		}
		else
		{
			strTemp.Format("%.0f", m_setCodificaRegionaleEx.m_fAmministrativoMinuti);
			SetDlgItemText(IDC_EDIT_28, strTemp);
		}
		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fTotaleCostoPersonale))
		{
			SetDlgItemText(IDC_EDIT_29, "0.00");
		}
		else
		{
			strTemp.Format("%.2f", m_setCodificaRegionaleEx.m_fTotaleCostoPersonale);
			SetDlgItemText(IDC_EDIT_29, strTemp);
		}
		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fAnestesistaCosto))
		{
			SetDlgItemText(IDC_EDIT_36, "0.00");
		}
		else
		{
			strTemp.Format("%.2f", m_setCodificaRegionaleEx.m_fAnestesistaCosto);
			SetDlgItemText(IDC_EDIT_36, strTemp);
		}
		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fAnestesistaNumero))
		{
			SetDlgItemText(IDC_EDIT_37, "0.0");
		}
		else
		{
			strTemp.Format("%.1f", m_setCodificaRegionaleEx.m_fAnestesistaNumero);
			SetDlgItemText(IDC_EDIT_37, strTemp);
		}
		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fAnestesistaMinuti))
		{
			SetDlgItemText(IDC_EDIT_38, "0");
		}
		else
		{
			strTemp.Format("%.0f", m_setCodificaRegionaleEx.m_fAnestesistaMinuti);
			SetDlgItemText(IDC_EDIT_38, strTemp);
		}
		if (m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_fRimborsoRegionale))
		{
			SetDlgItemText(IDC_EDIT_39, "0.00");
		}
		else
		{
			strTemp.Format("%.2f", m_setCodificaRegionaleEx.m_fRimborsoRegionale);
			SetDlgItemText(IDC_EDIT_39, strTemp);
		}

		/*CExtTransPrestazioniSet transPrestazioniSet;
		CString filter;
		filter.Format("idPrestazioneEndox = %li", m_setCodificaRegionaleEx.m_lContatore);
		transPrestazioniSet.SetOpenFilter(filter);
		transPrestazioniSet.Open();
		if (!transPrestazioniSet.IsEOF())
		{
			SetDlgItemText(IDC_EDIT_40, transPrestazioniSet.m_sCodicePrestazioneEst);
			if (!transPrestazioniSet.IsFieldNull(&transPrestazioniSet.m_lIdTipoEsameEndox))
			{
				m_ctrlComboTipoEsame.SetCurSel(0);

				for(int i=0; i<m_ctrlComboTipoEsame.GetCount(); i++)
				{
					if (m_ctrlComboTipoEsame.GetItemData(i) == transPrestazioniSet.m_lIdTipoEsameEndox)
					{
						m_ctrlComboTipoEsame.SetCurSel(i);
						break;
					}
				}
			}
			else
				m_ctrlComboTipoEsame.SetCurSel(0);
		}
		else
		{
			SetDlgItemText(IDC_EDIT_40, "");
			m_ctrlComboTipoEsame.SetCurSel(0);
		}

		transPrestazioniSet.Close();*/

		SetDlgItemText(IDC_EDIT_40, m_setCodificaRegionaleEx.m_sCodiceIntegrazione);
		SetDlgItemText(IDC_EDIT_44, m_setCodificaRegionaleEx.m_sCodiceDicom);

		m_ctrlComboTipoEsame.SetCurSel(0);

		if (!m_setCodificaRegionaleEx.IsFieldNull(&m_setCodificaRegionaleEx.m_lIDTipoEsameEndox))
		{
			for (int i = 0; i < m_ctrlComboTipoEsame.GetCount(); i++)
			{
				if (m_ctrlComboTipoEsame.GetItemData(i) == m_setCodificaRegionaleEx.m_lIDTipoEsameEndox)
				{
					m_ctrlComboTipoEsame.SetCurSel(i);
					break;
				}
			}
		}

		m_ctrlCheckPrestazionePrincipale.SetCheck(m_setCodificaRegionaleEx.m_bPrestazionePrincipale ? BST_CHECKED : BST_UNCHECKED);
		m_ctrlCheckPrestazioneNormata.SetCheck(m_setCodificaRegionaleEx.m_bNormata ? BST_CHECKED : BST_UNCHECKED);
		m_ctrlCheckPrestazionePNGLA.SetCheck(m_setCodificaRegionaleEx.m_bPNGLA ? BST_CHECKED : BST_UNCHECKED);
	}
	else
	{
		SvuotaDialog();
	}
}

void CCodificaRegionaleExDlg::OnBnClickedBtnNew()
{
	SvuotaDialog();
	CambiaModalita(CORE_NUOVO);

	GetDlgItem(IDC_EDIT_04)->SetFocus();
}

void CCodificaRegionaleExDlg::OnBnClickedBtnEdt()
{
	CambiaModalita(CORE_MODIF);
}

void CCodificaRegionaleExDlg::OnBnClickedBtnDel()
{
	int iTemp;
	CString strTmp1, strTmp2;

	iTemp = m_ctrlList00.GetCurSel();
	if (iTemp != LB_ERR)
	{
		m_ctrlList00.GetText(iTemp, strTmp1);
		strTmp2.Format(theApp.GetMessageString(IDS_CODREG_DELETE_CONFIRM), strTmp1);
		if (theApp.AfxMessageBoxEndo(strTmp2, MB_YESNO) == IDYES)
		{
			strTmp1.Format("Contatore=%li", m_ctrlList00.GetItemData(iTemp));
			m_setCodificaRegionaleEx.SetOpenFilter(strTmp1);

			/*int idPrestazione = m_ctrlList00.GetItemData(iTemp);
			CString filter;
			filter.Format("idprestazioneendox = %li", m_setCodificaRegionaleEx.m_lContatore);
			CExtTransPrestazioniSet transPrestazioniSet;
			transPrestazioniSet.SetOpenFilter(filter);
			transPrestazioniSet.Open();
			if (!transPrestazioniSet.IsEOF() && !transPrestazioniSet.IsBOF())
				transPrestazioniSet.Delete();
			transPrestazioniSet.Close();*/

			m_setCodificaRegionaleEx.DeleteRecordset("OnBnClickedBtnDel");

			m_ctrlList00.DeleteString(iTemp);

			OnLbnSelchangeList00();
		}
	}
}

void CCodificaRegionaleExDlg::OnBnClickedBtnSav()
{
	CString strTemp;
	int iTemp;

	GetDlgItemText(IDC_EDIT_04, strTemp);
	if (strTemp.GetLength() < 1)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CODREG_ERR_DESC));
		return;
	}

	switch(m_iModalita)
	{
		case CORE_NUOVO:
		{
			m_setCodificaRegionaleEx.AddNewRecordset("OnBnClickedBtnSav");

			break;
		}

		case CORE_MODIF:
		{
			m_setCodificaRegionaleEx.EditRecordset("OnBnClickedBtnSav");

			break;
		}
	}

	GetDlgItemText(IDC_EDIT_04, m_setCodificaRegionaleEx.m_sDescrizione);
	GetDlgItemText(IDC_EDIT_02, m_setCodificaRegionaleEx.m_sCodiceNazionale);
	GetDlgItemText(IDC_EDIT_03, m_setCodificaRegionaleEx.m_sCodiceRegionale);
	GetDlgItemText(IDC_EDIT_05, strTemp);
	m_setCodificaRegionaleEx.m_fTotaleGlobale = (float)atof(strTemp);

	GetDlgItemText(IDC_EDIT_06, strTemp);
	m_setCodificaRegionaleEx.m_fTotaleCostoMateriali = (float)atof(strTemp);

	GetDlgItemText(IDC_EDIT_07, strTemp);
	m_setCodificaRegionaleEx.m_fManutenzioneDedicata = (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_08, strTemp);
	m_setCodificaRegionaleEx.m_fManutenzioneBase = (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_09, strTemp);
	m_setCodificaRegionaleEx.m_fTotaleCostoManutenzione = (float)atof(strTemp);

	GetDlgItemText(IDC_EDIT_10, strTemp);
	m_setCodificaRegionaleEx.m_fAmmortamentoDedicata = (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_11, strTemp);
	m_setCodificaRegionaleEx.m_fAmmortamentoBase = (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_12, strTemp);
	m_setCodificaRegionaleEx.m_fTotaleCostoAmmortamento = (float)atof(strTemp);

	GetDlgItemText(IDC_EDIT_13, strTemp);
	m_setCodificaRegionaleEx.m_fTotaleCostiGenerali = (float)atof(strTemp);

	GetDlgItemText(IDC_EDIT_14, strTemp);
	m_setCodificaRegionaleEx.m_fEndoscopistaCosto = (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_15, strTemp);
	m_setCodificaRegionaleEx.m_fEndoscopistaNumero = (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_16, strTemp);
	m_setCodificaRegionaleEx.m_fEndoscopistaMinuti = (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_17, strTemp);
	m_setCodificaRegionaleEx.m_fRadiologoCosto = (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_18, strTemp);
	m_setCodificaRegionaleEx.m_fRadiologoNumero = (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_19, strTemp);
	m_setCodificaRegionaleEx.m_fRadiologoMinuti = (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_20, strTemp);
	m_setCodificaRegionaleEx.m_fInfermiereCosto = (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_21, strTemp);
	m_setCodificaRegionaleEx.m_fInfermiereNumero = (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_22, strTemp);
	m_setCodificaRegionaleEx.m_fInfermiereMinuti = (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_23, strTemp);
	m_setCodificaRegionaleEx.m_fOtaaCosto = (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_24, strTemp);
	m_setCodificaRegionaleEx.m_fOtaaNumero = (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_25, strTemp);
	m_setCodificaRegionaleEx.m_fOtaaMinuti = (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_26, strTemp);
	m_setCodificaRegionaleEx.m_fAmministrativoCosto = (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_27, strTemp);
	m_setCodificaRegionaleEx.m_fAmministrativoNumero = (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_28, strTemp);
	m_setCodificaRegionaleEx.m_fAmministrativoMinuti = (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_29, strTemp);
	m_setCodificaRegionaleEx.m_fTotaleCostoPersonale = (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_36, strTemp);
	m_setCodificaRegionaleEx.m_fAnestesistaCosto = (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_37, strTemp);
	m_setCodificaRegionaleEx.m_fAnestesistaNumero = (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_38, strTemp);
	m_setCodificaRegionaleEx.m_fAnestesistaMinuti = (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_39, strTemp);
	m_setCodificaRegionaleEx.m_fRimborsoRegionale = (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_40, strTemp);
	m_setCodificaRegionaleEx.m_sCodiceIntegrazione = strTemp;
	GetDlgItemText(IDC_EDIT_44, strTemp);
	m_setCodificaRegionaleEx.m_sCodiceDicom = strTemp;
	m_setCodificaRegionaleEx.m_lIDTipoEsameEndox = m_ctrlComboTipoEsame.GetItemData(m_ctrlComboTipoEsame.GetCurSel());

	m_setCodificaRegionaleEx.m_bPrestazionePrincipale = (m_ctrlCheckPrestazionePrincipale.GetCheck() == BST_CHECKED ? TRUE : FALSE);
	m_setCodificaRegionaleEx.m_bNormata = (m_ctrlCheckPrestazioneNormata.GetCheck() == BST_CHECKED ? TRUE : FALSE);
	m_setCodificaRegionaleEx.m_bPNGLA = (m_ctrlCheckPrestazionePNGLA.GetCheck() == BST_CHECKED ? TRUE : FALSE);

	m_setCodificaRegionaleEx.UpdateRecordset("OnBnClickedBtnSav");

	switch(m_iModalita)
	{
		case CORE_NUOVO:
		{					
			m_setCodificaRegionaleEx.SetOpenFilter("");
			m_setCodificaRegionaleEx.OpenRecordset("OnBnClickedBtnSav");
			m_setCodificaRegionaleEx.MoveLast();

			iTemp = m_ctrlList00.GetCount();
			GetDlgItemText(IDC_EDIT_04, strTemp);
			m_ctrlList00.InsertString(iTemp, strTemp);
			m_ctrlList00.SetItemData(iTemp, m_setCodificaRegionaleEx.m_lContatore);

			m_ctrlList00.SetCurSel(iTemp);

			break;
		}

		case CORE_MODIF:
		{
			iTemp = m_ctrlList00.GetCurSel();
			m_ctrlList00.DeleteString(iTemp);

			m_ctrlList00.InsertString(iTemp, m_setCodificaRegionaleEx.m_sDescrizione);
			m_ctrlList00.SetItemData(iTemp, m_setCodificaRegionaleEx.m_lContatore);

			m_ctrlList00.SetCurSel(iTemp);

			break;
		}
	}

	//Inserisco/aggiorno la riga nella tabella di transcodifica
	/*if (codicePrestazioneEst != "")
	{
		CExtTransPrestazioniSet transPrestazioniSet;
		CString filter;
		filter.Format("idPrestazioneEndox = %li", idPrestazioneEndox);
		transPrestazioniSet.SetOpenFilter(filter);
		transPrestazioniSet.Open();
		if (!transPrestazioniSet.IsEOF())
		{
			transPrestazioniSet.Edit();
			transPrestazioniSet.m_sCodicePrestazioneEst = codicePrestazioneEst;
			if (idTipoEsameEndox == -1)
				transPrestazioniSet.SetFieldNull(&transPrestazioniSet.m_lIdTipoEsameEndox);
			else
				transPrestazioniSet.m_lIdTipoEsameEndox = idTipoEsameEndox;
			transPrestazioniSet.UpdateRecordset();
		}
		else
		{
			transPrestazioniSet.AddNew();
			transPrestazioniSet.m_lIdPrestazioneEndox = idPrestazioneEndox;
			transPrestazioniSet.m_sCodicePrestazioneEst = codicePrestazioneEst;
			if (idTipoEsameEndox == -1)
				transPrestazioniSet.SetFieldNull(&transPrestazioniSet.m_lIdTipoEsameEndox);
			else
				transPrestazioniSet.m_lIdTipoEsameEndox = idTipoEsameEndox;
			transPrestazioniSet.UpdateRecordset();
		}
		transPrestazioniSet.Close();
	}*/

	OnLbnSelchangeList00();

	CambiaModalita(CORE_VISUA);
}

void CCodificaRegionaleExDlg::OnBnClickedBtnUnd()
{
	CambiaModalita(CORE_VISUA);
	VisualizzaDati();
}

void CCodificaRegionaleExDlg::OnEnChangeEdit06()
{
	Calcola05();
}

void CCodificaRegionaleExDlg::OnEnChangeEdit07()
{
	Calcola09();
}

void CCodificaRegionaleExDlg::OnEnChangeEdit08()
{
	Calcola09();
}

void CCodificaRegionaleExDlg::OnEnChangeEdit10()
{
	Calcola12();
}

void CCodificaRegionaleExDlg::OnEnChangeEdit11()
{
	Calcola12();
}

void CCodificaRegionaleExDlg::OnEnChangeEdit14()
{
	Calcola29();
}

void CCodificaRegionaleExDlg::OnEnChangeEdit17()
{
	Calcola29();
}

void CCodificaRegionaleExDlg::OnEnChangeEdit20()
{
	Calcola29();
}

void CCodificaRegionaleExDlg::OnEnChangeEdit23()
{
	Calcola29();
}

void CCodificaRegionaleExDlg::OnEnChangeEdit26()
{
	Calcola29();
}

void CCodificaRegionaleExDlg::OnEnChangeEdit36()
{
	Calcola29();
}

void CCodificaRegionaleExDlg::Calcola05()
{
	CString strTemp;
	float f05 = 0.0f;
	float f13 = 0.0f;

	GetDlgItemText(IDC_EDIT_06, strTemp);
	f05 += (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_09, strTemp);
	f05 += (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_12, strTemp);
	f05 += (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_29, strTemp);
	f05 += (float)atof(strTemp);
	f13 = f05 * 0.2f;
	f05 += f13;

	strTemp.Format("%.2f", f05);
	SetDlgItemText(IDC_EDIT_05, strTemp);
	strTemp.Format("%.2f", f13);
	SetDlgItemText(IDC_EDIT_13, strTemp);
}

void CCodificaRegionaleExDlg::Calcola09()
{
	CString strTemp;
	float f09 = 0.0f;

	GetDlgItemText(IDC_EDIT_07, strTemp);
	f09 += (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_08, strTemp);
	f09 += (float)atof(strTemp);

	strTemp.Format("%.2f", f09);
	SetDlgItemText(IDC_EDIT_09, strTemp);

	Calcola05();
}

void CCodificaRegionaleExDlg::Calcola12()
{
	CString strTemp;
	float f12 = 0.0f;

	GetDlgItemText(IDC_EDIT_10, strTemp);
	f12 += (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_11, strTemp);
	f12 += (float)atof(strTemp);

	strTemp.Format("%.2f", f12);
	SetDlgItemText(IDC_EDIT_12, strTemp);

	Calcola05();
}

void CCodificaRegionaleExDlg::Calcola29()
{
	CString strTemp;
	float f29 = 0.0f;

	GetDlgItemText(IDC_EDIT_14, strTemp);
	f29 += (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_17, strTemp);
	f29 += (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_20, strTemp);
	f29 += (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_23, strTemp);
	f29 += (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_26, strTemp);
	f29 += (float)atof(strTemp);
	GetDlgItemText(IDC_EDIT_36, strTemp);
	f29 += (float)atof(strTemp);

	strTemp.Format("%.2f", f29);
	SetDlgItemText(IDC_EDIT_29, strTemp);

	Calcola05();
}
void CCodificaRegionaleExDlg::OnBnClickedBtnPri()
{
	//Font grafico di default
	LOGFONT lfPrinterFont;
	
	memset(&lfPrinterFont, 0, sizeof(lfPrinterFont));
	lfPrinterFont.lfHeight 			= -10;
	lfPrinterFont.lfWeight 			= 400;
	lfPrinterFont.lfEscapement		= 0;   // orizzontale
	lfPrinterFont.lfOrientation		= 0;
	lfPrinterFont.lfWidth			= 0;
	lfPrinterFont.lfStrikeOut		= 0;
	lfPrinterFont.lfCharSet			= 0;
	lfPrinterFont.lfItalic			= 0;
	lfPrinterFont.lfUnderline		= 0;
	lfPrinterFont.lfOutPrecision	= 1;
	lfPrinterFont.lfClipPrecision	= 2;
	lfPrinterFont.lfQuality			= 1;
	lfPrinterFont.lfPitchAndFamily 	= 34;
	strcpy_s(lfPrinterFont.lfFaceName, "Arial");

	int nCounter = m_ctrlList00.GetCount();
	if (nCounter == LB_ERR)
		return;
	
	CMyPrintDialog printdlg (FALSE, PD_ALLPAGES | PD_USEDEVMODECOPIES | PD_NOPAGENUMS | PD_HIDEPRINTTOFILE | PD_NOSELECTION, this);
	if (printdlg.DoModal() == IDOK)
	{
		CDC 		prnDC ;   
		DOCINFO 	docInfo;
		CRect 		rectPage;
		TEXTMETRIC 	tm;
		CFont*		pFontOld;
		CFont		PrinterFont;
		CString		strTitle;
		CString		strValue;
		
		CCustomDate date(TRUE, TRUE);

		docInfo.cbSize			= sizeof (DOCINFO);
		docInfo.lpszDocName		= "Codifica Regionale";
		docInfo.lpszOutput		= NULL;                       
		docInfo.lpszDatatype	= NULL;
		docInfo.fwType			= 0;
			
		prnDC.Attach(printdlg.GetPrinterDC());
        prnDC.StartDoc(&docInfo);
	        
		rectPage.SetRect(150, 0, prnDC.GetDeviceCaps(HORZRES), prnDC.GetDeviceCaps(VERTRES));
		prnDC.DPtoLP(&rectPage);
			    
		// create new font.
		int 	rapXP = prnDC.GetDeviceCaps(LOGPIXELSX);
		int 	rapYP = prnDC.GetDeviceCaps(LOGPIXELSY);
	
		//CClientDC	dcForm(this);
    	int 	rapXV = 72; //dcForm.GetDeviceCaps(LOGPIXELSX);
		int		rapYV = 72; //dcForm.GetDeviceCaps(LOGPIXELSY);

		// calcola il font per la stampante
		lfPrinterFont.lfHeight = ::MulDiv(lfPrinterFont.lfHeight, rapYP, rapYV);
		lfPrinterFont.lfWidth  = ::MulDiv(lfPrinterFont.lfWidth,  rapXP, rapXV);

		PrinterFont.CreateFontIndirect(&lfPrinterFont);

		pFontOld = prnDC.SelectObject(&PrinterFont);
	
		prnDC.GetTextMetrics(&tm);

		int nCYChar			= tm.tmHeight + tm.tmExternalLeading;
		int nLinesPerPage	= (prnDC.GetDeviceCaps(VERTRES) / nCYChar) - 2;
		int nPage			= (nCounter-1) / nLinesPerPage + 1;
		int	nL				= 0;
		
		while (nL<nCounter)
		{
			for(int nP=1; nP<=nPage; nP++)
			{
				int		nLine = 0;
				CRect	rect  = CRect(rectPage.left, nLine * nCYChar, rectPage.right, (nLine+1) * nCYChar);

				prnDC.StartPage();
		
				prnDC.SetTextAlign(TA_LEFT);
				prnDC.TextOut (rect.left, rect.top, date.GetDate("%d/%m/%Y %H:%M"));
				prnDC.SetTextAlign(TA_CENTER);
				prnDC.TextOut ((rect.left + rectPage.right)/2, rect.top, "Codifica Regionale");
					
				nLine++;
				prnDC.MoveTo(rectPage.left, nLine * nCYChar + (nCYChar / 2));
				prnDC.LineTo(rectPage.right, nLine * nCYChar + (nCYChar / 2));
			
				while (nL<nCounter && nL<(nP*nLinesPerPage))
				{
					m_ctrlList00.GetText(nL, strValue);
					nL++;
				
					if (strValue != "")
					{
						nLine++;
			
						rect = CRect(rectPage.left, nLine * nCYChar, rectPage.right, (nLine+1) * nCYChar);
					
						prnDC.SetTextAlign(TA_LEFT);
						prnDC.TextOut (rect.left, rect.top, strValue);
					}
					
				}
			
				prnDC.EndPage();
			}
		}
	    
		prnDC.EndDoc();  
		        
		prnDC.SelectObject(pFontOld);
	    prnDC.DeleteDC();
		        
		::GlobalFree (printdlg.m_pd.hDevMode);
		::GlobalFree (printdlg.m_pd.hDevNames);
	}
}
