#include "stdafx.h"
#include "Endox.h"
#include "FirmaConfidenzialitaTrevisoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CFirmaConfidenzialitaTrevisoDlg, CDialog)

CFirmaConfidenzialitaTrevisoDlg::CFirmaConfidenzialitaTrevisoDlg(CWnd* pParent)
	: CDialog(CFirmaConfidenzialitaTrevisoDlg::IDD, pParent)
{
	m_sClassificazione = "";
}

CFirmaConfidenzialitaTrevisoDlg::~CFirmaConfidenzialitaTrevisoDlg()
{
}

BEGIN_MESSAGE_MAP(CFirmaConfidenzialitaTrevisoDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIO_NO, OnBnClickedRadioNo)
	ON_BN_CLICKED(IDC_RADIO_SI, OnBnClickedRadioSi)
END_MESSAGE_MAP()

void CFirmaConfidenzialitaTrevisoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

void CFirmaConfidenzialitaTrevisoDlg::OnCancel()
{
}

BOOL CFirmaConfidenzialitaTrevisoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_STATIC_TITOLO)->SetFont(&theApp.m_fontBig);

	return TRUE;
}

void CFirmaConfidenzialitaTrevisoDlg::OnOK()
{
}

void CFirmaConfidenzialitaTrevisoDlg::OnBnClickedRadioNo()
{
	m_sClassificazione = "U";

	CDialog::OnOK();
}

void CFirmaConfidenzialitaTrevisoDlg::OnBnClickedRadioSi()
{
	m_sClassificazione = "V";

	CDialog::OnOK();
}

CString CFirmaConfidenzialitaTrevisoDlg::GetClassificazione()
{
	return m_sClassificazione;
}