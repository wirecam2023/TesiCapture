#include "stdafx.h"
#include "Endox.h"
#include "EditStringCheckDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEditStringCheckDlg, CDialog)

CEditStringCheckDlg::CEditStringCheckDlg(CWnd* pParent, const CString &sTitle, const CString &sValue, long lType, BOOL bChecked)
	: CDialog(CEditStringCheckDlg::IDD, pParent)
{
	m_sTitle = sTitle;

	m_sValue = sValue;
	m_lType = lType;
	m_bChecked = bChecked;
}

CEditStringCheckDlg::CEditStringCheckDlg(CWnd* pParent, UINT idTitle, const CString &sValue, long lType, BOOL bChecked)
	: CDialog(CEditStringCheckDlg::IDD, pParent)
{
	m_sTitle = theApp.GetMessageString(idTitle);

	m_sValue = sValue;
	m_lType = lType;
	m_bChecked = bChecked;
}

CEditStringCheckDlg::~CEditStringCheckDlg()
{
}

void CEditStringCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);
	DDX_Control(pDX, IDC_CHECK_01, m_ctrlCheck01);
	DDX_Control(pDX, IDC_COMBO_TIPO, m_ctrlComboTipo);
	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);

	if (pDX->m_bSaveAndValidate)
		m_bChecked = (m_ctrlCheck01.GetCheck() == BST_CHECKED);
	else
		m_ctrlCheck01.SetCheck(m_bChecked ? BST_CHECKED : BST_UNCHECKED);
}

BEGIN_MESSAGE_MAP(CEditStringCheckDlg, CDialog)

	ON_BN_CLICKED(IDOK, OnBnClickedOk)

	ON_EN_CHANGE(IDC_EDIT_VALUE, OnEnChangeEditValue)

END_MESSAGE_MAP()

BOOL CEditStringCheckDlg::OnInitDialog()
{   
	CDialog::OnInitDialog();

	m_ctrlComboTipo.InsertString(0, theApp.GetMessageString(IDS_TESTO));
	m_ctrlComboTipo.InsertString(1, theApp.GetMessageString(IDS_TEMPO));
	m_ctrlComboTipo.InsertString(2, theApp.GetMessageString(IDS_SOMMATEMPO));
	m_ctrlComboTipo.InsertString(3, theApp.GetMessageString(IDS_METS));

	theApp.LocalizeDialog(this, CEditStringCheckDlg::IDD, "EditStringCheckDlg");

	SetWindowText(m_sTitle);
	SetDlgItemText(IDC_EDIT_VALUE, m_sValue);
	m_ctrlComboTipo.SetCurSel(m_lType % 4);

	// Sandro 03/06/2013 // Attivo il tasto "Conferma" solo se c'è qualcosa di scritto //
	m_ctrlButtonOK.EnableWindow(!m_sValue.IsEmpty());

	//
	return TRUE;
}

void CEditStringCheckDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	GetDlgItemText(IDC_EDIT_VALUE, m_sValue);
	m_lType = (m_ctrlComboTipo.GetCurSel() % 4);
	OnOK();
}

void CEditStringCheckDlg::GetColonnaSetting(CString &sValue, long &lType, BOOL &bChecked)
{
	sValue = m_sValue;
	lType = m_lType;
	bChecked = m_bChecked;
}

void CEditStringCheckDlg::OnEnChangeEditValue()
{
	// Sandro 03/06/2013 // Attivo il tasto "Conferma" solo se c'è qualcosa di scritto //

	CString sTemp;
	GetDlgItemText(IDC_EDIT_VALUE, sTemp);
	sTemp.Trim();

	m_ctrlButtonOK.EnableWindow(!sTemp.IsEmpty());
}
