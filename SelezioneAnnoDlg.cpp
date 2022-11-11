#include "stdafx.h"
#include "Endox.h"
#include "SelezioneAnnoDlg.h"

#include "CustomDate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CSelezioneAnnoDlg, CDialog)

CSelezioneAnnoDlg::CSelezioneAnnoDlg(CWnd* pParent)
	: CDialog(CSelezioneAnnoDlg::IDD, pParent)
{
}

CSelezioneAnnoDlg::~CSelezioneAnnoDlg()
{
}

BEGIN_MESSAGE_MAP(CSelezioneAnnoDlg, CDialog)
END_MESSAGE_MAP()

void CSelezioneAnnoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);

	DDX_Control(pDX, IDC_SPIN, m_ctrlSpin);
}

BOOL CSelezioneAnnoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CCustomDate dateTemp(TRUE, TRUE);

	m_ctrlSpin.SetRange32(dateTemp.GetYear() - 10, dateTemp.GetYear());
	m_ctrlSpin.SetPos32(dateTemp.GetYear());

	theApp.LocalizeDialog(this, CSelezioneAnnoDlg::IDD, "SelezioneAnnoDlg");
	return TRUE;
}

void CSelezioneAnnoDlg::OnOK()
{
	m_lAnno = (long)m_ctrlSpin.GetPos32();

	CDialog::OnOK();
}

long CSelezioneAnnoDlg::GetAnno()
{
	return m_lAnno;
}