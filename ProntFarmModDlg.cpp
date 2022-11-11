#include "stdafx.h"
#include "Endox.h"
#include "Endox.h"
#include "ProntFarmModDlg.h"
#include "FarmaciSet.h"
#include "FarmaciDistinctSet.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CProntFarmModDlg, CDialog)

CProntFarmModDlg::CProntFarmModDlg(CWnd* pParent)
	: CDialog(CProntFarmModDlg::IDD, pParent)
{
}

CProntFarmModDlg::~CProntFarmModDlg()
{
}

BEGIN_MESSAGE_MAP(CProntFarmModDlg, CDialog)
	ON_WM_CTLCOLOR()

	ON_LBN_SELCHANGE(IDC_LIST_00, OnLbnSelchangeList00)
END_MESSAGE_MAP()

void CProntFarmModDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_00, m_ctrlList00);
	DDX_Control(pDX, IDC_LIST_02, m_ctrlList02);

	DDX_Control(pDX, IDOK, m_ctrlBtnOK);

	DDX_Control(pDX, IDC_STATIC_08, m_ctrlStatic08);
	DDX_Control(pDX, IDC_STATIC_09, m_ctrlStatic09);
}

void CProntFarmModDlg::OnCancel()
{
}

HBRUSH CProntFarmModDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_08:
		case IDC_STATIC_09:
		{
			pDC->SetTextColor(theApp.m_color[4]);
			break;
		}
	}

	return hBrush;
}

BOOL CProntFarmModDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	GetDlgItem(IDC_STATIC_08)->SetFont(&theApp.m_fontBig);
	GetDlgItem(IDC_STATIC_09)->SetFont(&theApp.m_fontBig);

	m_ctrlList02.SetExtendedStyle(m_ctrlList02.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP);
	m_ctrlList02.InsertColumn(0, "");
	m_ctrlList02.InsertColumn(1, "AIC", LVCFMT_CENTER, 68);
	m_ctrlList02.InsertColumn(2, "DESCRIZIONE", LVCFMT_LEFT, 280);
	m_ctrlList02.InsertColumn(3, "CLASSE", LVCFMT_CENTER, 60);
	m_ctrlList02.InsertColumn(4, "NOTA1", LVCFMT_CENTER, 55);
	m_ctrlList02.InsertColumn(5, "NOTA2", LVCFMT_CENTER, 55);
	m_ctrlList02.InsertColumn(6, "DITTA", LVCFMT_LEFT, 149);

	m_ctrlList02.SetColumnWidth(0, 0);

	BeginWaitCursor();

	m_ctrlList00.ResetContent();
	m_ctrlList02.DeleteAllItems();

	CFarmaciDistinctSet setFarmaciDistinct;
	if (setFarmaciDistinct.OpenRecordset("CProntFarmModDlg::OnInitDialog"))
	{
		while(!setFarmaciDistinct.IsEOF())
		{
			CString strTemp;

			// Sandro 04/01/2014 // RAS 20130176 //

			if (!setFarmaciDistinct.IsFieldNull(&setFarmaciDistinct.m_sPrincipioAttivo))
				strTemp = setFarmaciDistinct.m_sPrincipioAttivo;
			if (!setFarmaciDistinct.IsFieldNull(&setFarmaciDistinct.m_sNome))
				strTemp = strTemp + " (" + setFarmaciDistinct.m_sNome + ")";

			m_ctrlList00.AddString(strTemp);

			setFarmaciDistinct.MoveNext();
		}

		setFarmaciDistinct.CloseRecordset("CProntFarmModDlg::OnInitDialog");
	}

	EndWaitCursor();

	theApp.LocalizeDialog(this, CProntFarmModDlg::IDD, "ProntFarmModDlg");
	return bReturn;
}

void CProntFarmModDlg::OnOK()
{
	CDialog::OnOK();
}

void CProntFarmModDlg::OnLbnSelchangeList00()
{
	int nIndex = m_ctrlList00.GetCurSel();

	BeginWaitCursor();
	m_ctrlList02.DeleteAllItems();

	if (nIndex >= 0)
	{
		int nTemp1;
		int nTemp2;
		int nAdded = 0;

		CString strTemp;
		m_ctrlList00.GetText(nIndex, strTemp);
		strTemp.Replace("'", "''");

		nTemp1 = strTemp.Find('(') + 1;
		CString strNome = strTemp.Left(nTemp1 - 2);

		nTemp2 = strTemp.Find(')', nTemp1);
		CString strPrincipio = strTemp.Mid(nTemp1, nTemp2 - nTemp1);

		CFarmaciSet setFarmaci;
		setFarmaci.SetOpenFilter("Nome='" + strNome + "' AND PrincipioAttivo='" + strPrincipio +"'");
		setFarmaci.SetSortRecord("Descrizione, Ditta");
		if (setFarmaci.OpenRecordset("CProntFarmModDlg::OnLbnSelchangeList00"))
		{
			while(!setFarmaci.IsEOF())
			{
				m_ctrlList02.InsertItem(nAdded, "");

				if (!setFarmaci.IsFieldNull(&setFarmaci.m_sAIC))
					m_ctrlList02.SetItemText(nAdded, 1, setFarmaci.m_sAIC);

				if (!setFarmaci.IsFieldNull(&setFarmaci.m_sDescrizione))
					m_ctrlList02.SetItemText(nAdded, 2, setFarmaci.m_sDescrizione);
				
				if (!setFarmaci.IsFieldNull(&setFarmaci.m_sClasse))
					m_ctrlList02.SetItemText(nAdded, 3, setFarmaci.m_sClasse);
				
				if (!setFarmaci.IsFieldNull(&setFarmaci.m_sNota1))
					m_ctrlList02.SetItemText(nAdded, 4, setFarmaci.m_sNota1);
				
				if (!setFarmaci.IsFieldNull(&setFarmaci.m_sNota2))
					m_ctrlList02.SetItemText(nAdded, 5, setFarmaci.m_sNota2);
				
				if (!setFarmaci.IsFieldNull(&setFarmaci.m_sDitta))
					m_ctrlList02.SetItemText(nAdded, 6, setFarmaci.m_sDitta);
				
				nAdded++;
				setFarmaci.MoveNext();
			}

			setFarmaci.CloseRecordset("CProntFarmModDlg::OnLbnSelchangeList00");
		}
	}
	EndWaitCursor();
}