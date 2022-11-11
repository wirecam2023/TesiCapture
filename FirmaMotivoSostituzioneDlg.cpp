#include "stdafx.h"
#include "Endox.h"
#include "FirmaMotivoSostituzioneDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CFirmaMotivoSostituzioneDlg, CDialog)

CFirmaMotivoSostituzioneDlg::CFirmaMotivoSostituzioneDlg(CWnd* pParent)
	: CDialog(CFirmaMotivoSostituzioneDlg::IDD, pParent)
{
	m_sMotivo = "";
}

CFirmaMotivoSostituzioneDlg::~CFirmaMotivoSostituzioneDlg()
{
}

BEGIN_MESSAGE_MAP(CFirmaMotivoSostituzioneDlg, CDialog)

	ON_BN_CLICKED(IDC_BTN_ANNULLA, OnBnClickedBtnAnnulla)
	ON_BN_CLICKED(IDC_BTN_CONFERMA, OnBnClickedBtnConferma)

	ON_EN_CHANGE(IDC_EDIT_MOTIVO, OnEnChangeEditMotivo)

END_MESSAGE_MAP()

void CFirmaMotivoSostituzioneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

void CFirmaMotivoSostituzioneDlg::OnCancel()
{
}

BOOL CFirmaMotivoSostituzioneDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;
}

void CFirmaMotivoSostituzioneDlg::OnOK()
{
}

void CFirmaMotivoSostituzioneDlg::OnBnClickedBtnAnnulla()
{
	m_sMotivo.Empty();

	CDialog::OnCancel();
}

void CFirmaMotivoSostituzioneDlg::OnBnClickedBtnConferma()
{
	m_sMotivo.MakeUpper();
	CDialog::OnOK();
}

void CFirmaMotivoSostituzioneDlg::OnEnChangeEditMotivo()
{
	GetDlgItemText(IDC_EDIT_MOTIVO, m_sMotivo);

	m_sMotivo.Trim();
	GetDlgItem(IDC_BTN_CONFERMA)->EnableWindow(!m_sMotivo.IsEmpty());
}

CString CFirmaMotivoSostituzioneDlg::GetMotivo()
{
	return m_sMotivo;
}