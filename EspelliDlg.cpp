#include "stdafx.h"
#include "Endox.h"
#include "EspelliDlg.h"

#include "Volume.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEspelliDlg::CEspelliDlg(CWnd* pParent, CString strLabel/*, CString strDisk*/)
	: CDialog(CEspelliDlg::IDD, pParent)
{
	m_strLabel = "";
	m_strTesto1 = "";
	m_strTesto2 = "";

	m_strLabel	= strLabel;
//	m_strDisk	= strDisk;

	if (m_strLabel == "")
	{
		m_strTesto1 = theApp.GetMessageString(IDS_ESPELLIDLG_TITLE_1);
		m_strTesto2 = theApp.GetMessageString(IDS_ESPELLIDLG_TITLE_2);
	}
	else
	{
		m_strTesto1 = theApp.GetMessageString(IDS_ESPELLIDLG_TITLE_3);
		m_strTesto2 = theApp.GetMessageString(IDS_ESPELLIDLG_TITLE_4);
	}
}

void CEspelliDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LABEL, m_ctrlLabel);
	DDX_Text(pDX, IDC_LABEL,	m_strLabel);
	DDX_Text(pDX, IDC_TESTO1,	m_strTesto1);
	DDX_Text(pDX, IDC_TESTO2,	m_strTesto2);
	DDX_Control(pDX, IDC_ESPELLI, m_ctrlButtonEject);
	DDX_Control(pDX, IDOK,     m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);
}

BEGIN_MESSAGE_MAP(CEspelliDlg, CDialog)
	ON_BN_CLICKED(IDC_ESPELLI, OnEspelli)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEspelliDlg message handlers

BOOL CEspelliDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (m_strLabel == "")
		m_ctrlLabel.ShowWindow(SW_HIDE);
	
	theApp.LocalizeDialog(this, CEspelliDlg::IDD, "EspelliDlg");
	return TRUE;
}

void CEspelliDlg::OnEspelli() 
{
	if (theApp.m_sPathImageOD.Find("\\\\") < 0)
		EjectThisDisk(theApp.m_sPathImageOD);
	/*
	if (m_strDisk.Find("\\\\") < 0)
		EjectThisDisk(m_strDisk);
	*/
}