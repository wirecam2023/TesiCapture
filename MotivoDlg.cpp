#include "stdafx.h"
#include "Endox.h"
#include "MotivoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMotivoDlg, CDialog)

CMotivoDlg::CMotivoDlg(CWnd* pParent, CString sStatic1, CString sStatic2, BOOL bShowAnnulla)
: CDialog(CMotivoDlg::IDD, pParent)
{
	m_sMotivo = "";
	m_sStatic1 = sStatic1;
	m_sStatic2 = sStatic2;
	m_bShowAnnulla = bShowAnnulla;
}

CMotivoDlg::~CMotivoDlg()
{
}

BEGIN_MESSAGE_MAP(CMotivoDlg, CDialog)

	ON_BN_CLICKED(IDC_BTN_ANNULLA, OnBnClickedBtnAnnulla)
	ON_BN_CLICKED(IDC_BTN_CONFERMA, OnBnClickedBtnConferma)

	ON_EN_CHANGE(IDC_EDIT_MOTIVO, OnEnChangeEditMotivo)

END_MESSAGE_MAP()

void CMotivoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

void CMotivoDlg::OnCancel()
{
}

BOOL CMotivoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_STATIC_1)->SetWindowText(m_sStatic1);
	GetDlgItem(IDC_STATIC_2)->SetWindowText(m_sStatic2);

	if (!m_bShowAnnulla)
		GetDlgItem(IDC_BTN_ANNULLA)->ShowWindow(SW_HIDE);

	return TRUE;
}

void CMotivoDlg::OnOK()
{
}

void CMotivoDlg::OnBnClickedBtnAnnulla()
{
	m_sMotivo.Empty();

	CDialog::OnCancel();
}

void CMotivoDlg::OnBnClickedBtnConferma()
{
	m_sMotivo.MakeUpper();
	CDialog::OnOK();
}

void CMotivoDlg::OnEnChangeEditMotivo()
{
	GetDlgItemText(IDC_EDIT_MOTIVO, m_sMotivo);

	m_sMotivo.Trim();
	GetDlgItem(IDC_BTN_CONFERMA)->EnableWindow(!m_sMotivo.IsEmpty());
}

CString CMotivoDlg::GetMotivo()
{
	return m_sMotivo;
}