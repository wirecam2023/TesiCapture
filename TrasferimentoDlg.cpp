#include "stdafx.h"
#include "Endox.h"
#include "TrasferimentoDlg.h"

#include "CustomDate.h"
#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CTrasferimentoDlg::CTrasferimentoDlg(CWnd* pParent)
	: CDialog(CTrasferimentoDlg::IDD, pParent)
{
	CCustomDate To(TRUE);
	CCustomDate From(TRUE);

	From -= 7; //settimana scosa

	m_DataDa = From.GetDate();
	m_DataA	 = To.GetDate();

	m_bTrasferimentoParziale = FALSE;
}


void CTrasferimentoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_PARZIALE, m_ctrlButton1);
	DDX_Control(pDX, IDOK,         m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL,     m_ctrlButtonCancel);

	//-------------------------------------------------------------
	// Davide
	DDX_DatePicker (pDX, IDC_DATA_DA,     m_DataDa);
	DDX_DatePicker (pDX, IDC_DATA_A,      m_DataA);
	DDX_Check      (pDX, IDC_PARZIALE,    m_bTrasferimentoParziale);
}


BEGIN_MESSAGE_MAP(CTrasferimentoDlg, CDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrasferimentoGlg message handlers

BOOL CTrasferimentoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CenterWindow();
	
	if (theApp.m_nFieldToFilterOnTransfer < 0 ||
	    theApp.m_nFieldToFilterOnTransfer > 5 ||
	    theApp.m_sFilterOnTransfer.IsEmpty())
	{
		GetDlgItem(IDC_PARZIALE)->ShowWindow(SW_HIDE);
	}

	theApp.LocalizeDialog(this, CTrasferimentoDlg::IDD, "TrasferimentoDlg");

	return TRUE;
}

void CTrasferimentoDlg::OnOK() 
{
	UpdateData(TRUE);

	if ((m_DataA < m_DataDa) || (m_DataA <= 0))
	{
		return;
	}

	CDialog::OnOK();
}