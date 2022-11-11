#include "stdafx.h"
#include "Endox.h"
#include "NumeroNuoviStadiDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CNumeroNuoviStadiDlg, CDialog)

CNumeroNuoviStadiDlg::CNumeroNuoviStadiDlg(CWnd* pParent)
	: CDialog(CNumeroNuoviStadiDlg::IDD, pParent)
{
	m_lNumero = 1;
}

CNumeroNuoviStadiDlg::~CNumeroNuoviStadiDlg()
{
}

BEGIN_MESSAGE_MAP(CNumeroNuoviStadiDlg, CDialog)
END_MESSAGE_MAP()

void CNumeroNuoviStadiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);

	DDX_Control(pDX, IDC_SPIN, m_ctrlSpin);

	DDX_Control(pDX, IDC_STATIC_LABEL, m_ctrlStaticLabel);
}

void CNumeroNuoviStadiDlg::OnCancel()
{
	CDialog::OnCancel();
}

BOOL CNumeroNuoviStadiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	UDACCEL pAccel[1];
	pAccel[0].nSec = 0;
	pAccel[0].nInc = 1;

	m_ctrlSpin.SetAccel(1, pAccel);
	m_ctrlSpin.SetRange32(1, 5);
	m_ctrlSpin.SetPos32(m_lNumero);

	theApp.LocalizeDialog(this, CNumeroNuoviStadiDlg::IDD, "NumeroNuoviStadiDlg");
	return TRUE;
}

void CNumeroNuoviStadiDlg::OnOK()
{
	m_lNumero = m_ctrlSpin.GetPos32();
	CDialog::OnOK();
}

long CNumeroNuoviStadiDlg::GetNumero()
{
	return m_lNumero;
}