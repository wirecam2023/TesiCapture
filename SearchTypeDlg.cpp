#include "stdafx.h"
#include "Endox.h"
#include "SearchTypeDlg.h"

#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSearchTypeDlg::CSearchTypeDlg(CWnd* pParent)
	: CDialog(CSearchTypeDlg::IDD, NULL)
{
	m_searchType = searchType::anagrafe;
}

void CSearchTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_ANAGRAFE, m_ctrlButtonAnagrafe);
	DDX_Control(pDX, IDC_BTN_RICOVERI, m_ctrlButtonRicoveri);
	DDX_Control(pDX, IDC_BTN_PS, m_ctrlButtonPS);
	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStaticMessage);
}

BEGIN_MESSAGE_MAP(CSearchTypeDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_ANAGRAFE, &CSearchTypeDlg::OnBnClickedBtnAnagrafe)
	ON_BN_CLICKED(IDC_BTN_RICOVERI, &CSearchTypeDlg::OnBnClickedBtnRicoveri)
	ON_BN_CLICKED(IDC_BTN_PS, &CSearchTypeDlg::OnBnClickedBtnPs)
END_MESSAGE_MAP()

BOOL CSearchTypeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	theApp.LocalizeDialog(this, CSearchTypeDlg::IDD, "SearchTypeDlg");

	if (theApp.m_bAttivaRicoveri)
		m_ctrlButtonRicoveri.EnableWindow(TRUE);	

	if (theApp.m_bAttivaPS)
		m_ctrlButtonPS.EnableWindow(TRUE);

	return TRUE;
}

void CSearchTypeDlg::OnOK() 
{
	CDialog::OnOK();
}


void CSearchTypeDlg::OnBnClickedBtnAnagrafe()
{
	m_searchType = searchType::anagrafe;
	OnOK();
}


void CSearchTypeDlg::OnBnClickedBtnRicoveri()
{
	m_searchType = searchType::ricoverati;
	OnOK();
}


void CSearchTypeDlg::OnBnClickedBtnPs()
{
	m_searchType = searchType::ps;
	OnOK();
}
