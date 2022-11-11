#include "stdafx.h"
#include "Endox.h"
#include "PathNumberDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CPathNumberDlg, CDialog)

CPathNumberDlg::CPathNumberDlg(CWnd* pParent, const CString &strTitle, const CString &sValue, const long &lValue)
	: CDialog(CPathNumberDlg::IDD, pParent)
{
	m_sTitle = strTitle;
	m_sValue = sValue;
	m_lValue = lValue;
}

CPathNumberDlg::CPathNumberDlg(CWnd* pParent, UINT idTitle, const CString &sValue, const long &lValue)
	: CDialog(CPathNumberDlg::IDD, pParent)
{
	m_sTitle = theApp.GetMessageString(idTitle);
	m_sValue = sValue;
	m_lValue = lValue;
}

CPathNumberDlg::~CPathNumberDlg()
{
}

BEGIN_MESSAGE_MAP(CPathNumberDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_SEARCH, OnBnClickedBtnSearch)
END_MESSAGE_MAP()

void CPathNumberDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);

	DDX_Control(pDX, IDC_EDIT_REPORT, m_ctrlEditReport);
	DDX_Control(pDX, IDC_EDIT_COPIE, m_ctrlEditCopie);

	DDX_Control(pDX, IDC_SPIN, m_ctrlSpin);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
}

BOOL CPathNumberDlg::OnInitDialog()
{   
	CDialog::OnInitDialog();

	UDACCEL pAccel[1];
	pAccel[0].nSec = 0;
	pAccel[0].nInc = 1;

	m_ctrlSpin.SetRange32(0, 9);
	m_ctrlSpin.SetPos32(1);
	m_ctrlSpin.SetAccel(1, pAccel);

	theApp.LocalizeDialog(this, CPathNumberDlg::IDD, "PathNumberDlg");

	SetWindowText(m_sTitle);
	m_ctrlEditReport.SetWindowText(m_sValue);
	m_ctrlSpin.SetPos32(m_lValue);

	return TRUE;
}

void CPathNumberDlg::OnBnClickedBtnOk()
{
	m_ctrlEditReport.GetWindowText(m_sValue);
	m_lValue = m_ctrlSpin.GetPos32();

	m_sValue.Trim();
	if (!m_sValue.IsEmpty())
		OnOK();
}

void CPathNumberDlg::GetValue(CString& sValue, long& lValue)
{
	sValue = m_sValue;
	lValue = m_lValue;
}

void CPathNumberDlg::OnBnClickedBtnSearch()
{
	CString strTemp;

	m_ctrlEditReport.GetWindowText(strTemp);

	OPENFILENAME ofnOpenFileName;
	TCHAR szFileName[MAX_PATH] = "";
	static LPCTSTR pFilter = "File report (*.rpt)\0*.rpt\0Tutti i file (*.*)\0*.*\0\0";

	ZeroMemory(&ofnOpenFileName, sizeof(OPENFILENAME));

	strTemp.Trim();
	if (strTemp.IsEmpty())
		ofnOpenFileName.lpstrInitialDir = theApp.m_sEditRep;
	else
		ofnOpenFileName.lpstrInitialDir = strTemp;

	ofnOpenFileName.lStructSize = sizeof(OPENFILENAME);
	ofnOpenFileName.hwndOwner   = m_hWnd;
	ofnOpenFileName.lpstrFile   = szFileName;
	ofnOpenFileName.nMaxFile    = MAX_PATH;
	ofnOpenFileName.lpstrFilter = pFilter;
	ofnOpenFileName.Flags       = OFN_FILEMUSTEXIST | OFN_LONGNAMES | OFN_READONLY;

	if (GetOpenFileName(&ofnOpenFileName) != FALSE)
		strTemp.Format("%s", ofnOpenFileName.lpstrFile);

	m_ctrlEditReport.SetWindowText(strTemp);
}
