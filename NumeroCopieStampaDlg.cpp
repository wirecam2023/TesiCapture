#include "stdafx.h"
#include "Endox.h"
#include "NumeroCopieStampaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CNumeroCopieStampaDlg, CDialog)

CNumeroCopieStampaDlg::CNumeroCopieStampaDlg(CWnd* pParent, CString sReportFile)
	: CDialog(CNumeroCopieStampaDlg::IDD, pParent)
{
	m_lNumeroCopie = 1;

	//

	int n1 = sReportFile.ReverseFind('\\');
	int n2 = sReportFile.ReverseFind('.');

	if ((n1 > 0) && (n2 > n1))
		m_sReportFile = sReportFile.Mid(n1 + 1, (n2 - n1) - 1);
	else
		m_sReportFile = sReportFile;
}

CNumeroCopieStampaDlg::~CNumeroCopieStampaDlg()
{
}

BEGIN_MESSAGE_MAP(CNumeroCopieStampaDlg, CDialog)
END_MESSAGE_MAP()

void CNumeroCopieStampaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);

	DDX_Control(pDX, IDC_SPIN, m_ctrlSpin);

	DDX_Control(pDX, IDC_STATIC_LABEL, m_ctrlStaticLabel);
}

void CNumeroCopieStampaDlg::OnCancel()
{
	CDialog::OnCancel();
}

BOOL CNumeroCopieStampaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	UDACCEL pAccel[1];
	pAccel[0].nSec = 0;
	pAccel[0].nInc = 1;

	m_ctrlSpin.SetAccel(1, pAccel);
	m_ctrlSpin.SetRange32(1, 99);
	m_ctrlSpin.SetPos32(m_lNumeroCopie);

	theApp.LocalizeDialog(this, CNumeroCopieStampaDlg::IDD, "NumeroCopieStampaDlg");
	SetWindowText(m_sReportFile);
	return TRUE;
}

void CNumeroCopieStampaDlg::OnOK()
{
	m_lNumeroCopie = m_ctrlSpin.GetPos32();
	CDialog::OnOK();
}

long CNumeroCopieStampaDlg::GetNumeroCopie()
{
	return m_lNumeroCopie;
}