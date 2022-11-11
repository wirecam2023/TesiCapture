#include "stdafx.h"
#include "Endox.h"
#include "BostonScoreMessagesDlg.h"

#include "BostonScoreSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CBostonScoreMessagesDlg, CDialog)

CBostonScoreMessagesDlg::CBostonScoreMessagesDlg(CWnd* pParent)
	: CDialog(CBostonScoreMessagesDlg::IDD, pParent)
{
}

CBostonScoreMessagesDlg::~CBostonScoreMessagesDlg()
{
}

BEGIN_MESSAGE_MAP(CBostonScoreMessagesDlg, CDialog)
	ON_BN_CLICKED(ID_ANNULLA, OnBnClickedAnnulla)
	ON_BN_CLICKED(ID_CONFERMA, OnBnClickedConferma)
END_MESSAGE_MAP()

void CBostonScoreMessagesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_A, m_ctrlStaticA);
	DDX_Control(pDX, IDC_STATIC_B, m_ctrlStaticB);

	DDX_Control(pDX, IDC_STATIC_0, m_ctrlStatic0);
	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC_4, m_ctrlStatic4);
	DDX_Control(pDX, IDC_STATIC_5, m_ctrlStatic5);
	DDX_Control(pDX, IDC_STATIC_6, m_ctrlStatic6);
	DDX_Control(pDX, IDC_STATIC_7, m_ctrlStatic7);
	DDX_Control(pDX, IDC_STATIC_8, m_ctrlStatic8);
	DDX_Control(pDX, IDC_STATIC_9, m_ctrlStatic9);

	DDX_Control(pDX, IDC_EDIT_0, m_ctrlEdit0);
	DDX_Control(pDX, IDC_EDIT_1, m_ctrlEdit1);
	DDX_Control(pDX, IDC_EDIT_2, m_ctrlEdit2);
	DDX_Control(pDX, IDC_EDIT_3, m_ctrlEdit3);
	DDX_Control(pDX, IDC_EDIT_4, m_ctrlEdit4);
	DDX_Control(pDX, IDC_EDIT_5, m_ctrlEdit5);
	DDX_Control(pDX, IDC_EDIT_6, m_ctrlEdit6);
	DDX_Control(pDX, IDC_EDIT_7, m_ctrlEdit7);
	DDX_Control(pDX, IDC_EDIT_8, m_ctrlEdit8);
	DDX_Control(pDX, IDC_EDIT_9, m_ctrlEdit9);
}

void CBostonScoreMessagesDlg::OnCancel()
{
}

BOOL CBostonScoreMessagesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlStaticA.SetFont(&theApp.m_fontBold);
	m_ctrlStaticB.SetFont(&theApp.m_fontBold);

	m_ctrlStatic0.SetFont(&theApp.m_fontBig);
	m_ctrlStatic1.SetFont(&theApp.m_fontBig);
	m_ctrlStatic2.SetFont(&theApp.m_fontBig);
	m_ctrlStatic3.SetFont(&theApp.m_fontBig);
	m_ctrlStatic4.SetFont(&theApp.m_fontBig);
	m_ctrlStatic5.SetFont(&theApp.m_fontBig);
	m_ctrlStatic6.SetFont(&theApp.m_fontBig);
	m_ctrlStatic7.SetFont(&theApp.m_fontBig);
	m_ctrlStatic8.SetFont(&theApp.m_fontBig);
	m_ctrlStatic9.SetFont(&theApp.m_fontBig);

	m_ctrlEdit0.SetWindowText(theApp.m_sBostonScore[0]);
	m_ctrlEdit1.SetWindowText(theApp.m_sBostonScore[1]);
	m_ctrlEdit2.SetWindowText(theApp.m_sBostonScore[2]);
	m_ctrlEdit3.SetWindowText(theApp.m_sBostonScore[3]);
	m_ctrlEdit4.SetWindowText(theApp.m_sBostonScore[4]);
	m_ctrlEdit5.SetWindowText(theApp.m_sBostonScore[5]);
	m_ctrlEdit6.SetWindowText(theApp.m_sBostonScore[6]);
	m_ctrlEdit7.SetWindowText(theApp.m_sBostonScore[7]);
	m_ctrlEdit8.SetWindowText(theApp.m_sBostonScore[8]);
	m_ctrlEdit9.SetWindowText(theApp.m_sBostonScore[9]);

	theApp.LocalizeDialog(this, CBostonScoreMessagesDlg::IDD, "BostonScoreMessagesDlg");
	return TRUE;
}

void CBostonScoreMessagesDlg::OnOK()
{
}

void CBostonScoreMessagesDlg::OnBnClickedAnnulla()
{
	CDialog::OnCancel();
}

void CBostonScoreMessagesDlg::OnBnClickedConferma()
{
	m_ctrlEdit0.GetWindowText(theApp.m_sBostonScore[0]);
	m_ctrlEdit1.GetWindowText(theApp.m_sBostonScore[1]);
	m_ctrlEdit2.GetWindowText(theApp.m_sBostonScore[2]);
	m_ctrlEdit3.GetWindowText(theApp.m_sBostonScore[3]);
	m_ctrlEdit4.GetWindowText(theApp.m_sBostonScore[4]);
	m_ctrlEdit5.GetWindowText(theApp.m_sBostonScore[5]);
	m_ctrlEdit6.GetWindowText(theApp.m_sBostonScore[6]);
	m_ctrlEdit7.GetWindowText(theApp.m_sBostonScore[7]);
	m_ctrlEdit8.GetWindowText(theApp.m_sBostonScore[8]);
	m_ctrlEdit9.GetWindowText(theApp.m_sBostonScore[9]);

	for(int i = 0; i < 10; i++)
		CBostonScoreSet().AddEdt(i, theApp.m_sBostonScore[i]);

	CDialog::OnOK();
}
