#include "stdafx.h"
#include "Endox.h"
#include "WaitDVDDlg.h"
#include "Volume.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CWaitDVDDlg, CDialog)

CWaitDVDDlg::CWaitDVDDlg(CString strExamLabel, CString strDiskLabel, CWnd* pParent)
	: CDialog(CWaitDVDDlg::IDD, pParent)
{
	m_strLabelExam = strExamLabel;
	m_strLabelDisk = strDiskLabel;
}

CWaitDVDDlg::~CWaitDVDDlg()
{
}

void CWaitDVDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LABEL_EXAM, m_strLabelExam);
	DDX_Text(pDX, IDC_LABEL_DISK, m_strLabelDisk);

	DDX_Control(pDX, IDC_STATIC_ERR,    m_ctrlStaticErr);
	DDX_Control(pDX, IDC_STATIC_LABEL1, m_ctrlStaticLabel1);
	DDX_Control(pDX, IDC_STATIC_LABEL2, m_ctrlStaticLabel2);
	DDX_Control(pDX, IDC_EJECT,         m_ctrlButtonEject);
	DDX_Control(pDX, IDOK,              m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL,          m_ctrlButtonCancel);
}

BEGIN_MESSAGE_MAP(CWaitDVDDlg, CDialog)
	ON_BN_CLICKED(IDC_EJECT, OnEject)
END_MESSAGE_MAP()

// CWaitDVDDlg message handlers

BOOL CWaitDVDDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	theApp.LocalizeDialog(this, CWaitDVDDlg::IDD, "WaitDVDDlg");
	return TRUE;
}

void CWaitDVDDlg::OnEject()
{
	// CVolume(theApp.m_strDVDPath.GetAt(0)).Eject();
}