#include "stdafx.h"
#include "Endox.h"
#include "EditDateStringDlg.h"

#include "CustomDate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEditDateStringDlg, CDialog)

CEditDateStringDlg::CEditDateStringDlg(CWnd* pParent, const CString &strTitle, const CString &sData, const CString &sDescrizione)
	: CDialog(CEditDateStringDlg::IDD, pParent)
{
	m_sWindowTitle = strTitle;

	m_sData = sData;
	m_sDescrizione = sDescrizione;
}

CEditDateStringDlg::CEditDateStringDlg(CWnd* pParent, UINT idTitle, const CString &sData, const CString &sDescrizione)
	: CDialog(CEditDateStringDlg::IDD, pParent)
{
	m_sWindowTitle = theApp.GetMessageString(idTitle);

	m_sData = sData;
	m_sDescrizione = sDescrizione;
}

CEditDateStringDlg::~CEditDateStringDlg()
{
}

void CEditDateStringDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);

	DDX_Control(pDX, IDC_EDIT_DATA, m_ctrlEditData);
	DDX_Control(pDX, IDC_EDIT_DESCRIZIONE, m_ctrlEditDescrizione);

	DDX_Control(pDX, IDC_STATIC_DATA, m_ctrlStaticData);
	DDX_Control(pDX, IDC_STATIC_DESCRIZIONE, m_ctrlStaticDescrizione);
}

BEGIN_MESSAGE_MAP(CEditDateStringDlg, CDialog)

	ON_BN_CLICKED(IDOK, OnBnClickedOk)

END_MESSAGE_MAP()

BOOL CEditDateStringDlg::OnInitDialog()
{   
	BOOL bReturn = CDialog::OnInitDialog();

	//

	m_ctrlEditData.SetEditMask("00/00/0000", "__/__/____");

	CCustomDate dateTemp;
	dateTemp.SetDate(m_sData);

	CString sTemp = dateTemp.GetDate("%d/%m/%Y");
	if (!sTemp.IsEmpty())
		m_ctrlEditData.SetWindowText(sTemp);

	m_ctrlEditDescrizione.SetWindowText(m_sDescrizione);

	//

	theApp.LocalizeDialog(this, CEditDateStringDlg::IDD, "EditStringDlg");
	SetWindowText(m_sWindowTitle);

	//
	return bReturn;
}

void CEditDateStringDlg::OnBnClickedOk()
{
	CString sDataTemp;
	m_ctrlEditData.GetWindowText(sDataTemp);

	CCustomDate dateTemp;
	dateTemp.SetDate(sDataTemp);

	m_sData = dateTemp.GetDate("%Y%m%d");

	m_ctrlEditDescrizione.GetWindowText(m_sDescrizione);

	OnOK();
}

CString CEditDateStringDlg::GetData()
{
	return m_sData;
}

CString CEditDateStringDlg::GetDescrizione()
{
	return m_sDescrizione;
}
