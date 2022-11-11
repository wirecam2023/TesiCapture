#include "stdafx.h"
#include "Endox.h"

#include "DLL_Imaging\h\AmTesiSign.h"

#include "SmartCardPinDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CSmartCardPinDlg, CDialog)

CSmartCardPinDlg::CSmartCardPinDlg(CWnd* pParentWnd)
	: CDialog(CSmartCardPinDlg::IDD, pParentWnd)
{
}

CSmartCardPinDlg::~CSmartCardPinDlg()
{
}

void CSmartCardPinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDCANCEL,     m_ctrlButton1);
	DDX_Control(pDX, IDOK,         m_ctrlButton2);

	DDX_Text(pDX, IDC_EDIT_PIN, m_strPin);
}

BEGIN_MESSAGE_MAP(CSmartCardPinDlg, CDialog)
END_MESSAGE_MAP()

// CSmartCardPinDlg message handlers

BOOL CSmartCardPinDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	theApp.LocalizeDialog(this, CSmartCardPinDlg::IDD, "SmartCardPinDlg");

	SetDlgItemText(IDC_STATIC_USER, m_strUser);

	return TRUE;
}

INT_PTR CSmartCardPinDlg::DoModal()
{
/*
#ifdef _DEBUG
	m_strUser = "FIRMA DEBUG";
	m_strPin = "1234";
	return IDOK;
#endif
*/

	AmTesiSign_SMARTCARDDATA info;
	AmTesiSign_GetSmartCardData(&info);
	m_strUser = info.szUserFirstLastName;
	if (m_strUser.IsEmpty())
		return IDCANCEL;

	m_strPin = "";
	return CDialog::DoModal();
}