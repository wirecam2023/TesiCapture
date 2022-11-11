#include "stdafx.h"
#include "Endox.h"
#include "NumberOfCopiesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CNumberOfCopiesDlg, CDialog)

CNumberOfCopiesDlg::CNumberOfCopiesDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CNumberOfCopiesDlg::IDD, pParent)
{
}

CNumberOfCopiesDlg::~CNumberOfCopiesDlg()
{
}

BEGIN_MESSAGE_MAP(CNumberOfCopiesDlg, CDialog)
END_MESSAGE_MAP()

void CNumberOfCopiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COPIES, m_ctrlEditCopies);
	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStaticLabel);
	DDX_Text(pDX, IDC_COPIES, m_iCopies);
}

BOOL CNumberOfCopiesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlEditCopies.SetWindowText("1");

	theApp.LocalizeDialog(this, CNumberOfCopiesDlg::IDD, "NumberOfCopiesDlg");

	UpdateData(TRUE);
	return TRUE;
}

void CNumberOfCopiesDlg::OnOK()
{
	UpdateData(TRUE);
	CDialog::OnOK();
}

void CNumberOfCopiesDlg::OnCancel()
{
}