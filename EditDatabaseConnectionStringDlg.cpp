#include "stdafx.h"
#include "Endox.h"
#include "EditDatabaseConnectionStringDlg.h"

#include "Common.h"
#include "DatabasesSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEditDatabaseConnectionStringDlg, CDialog)

CEditDatabaseConnectionStringDlg::CEditDatabaseConnectionStringDlg(CWnd* pParent, BOOL bIsOracle, long lID)
	: CDialog(CEditDatabaseConnectionStringDlg::IDD, pParent)
{
	m_bIsOracle = bIsOracle;
	m_lID = lID;
}

CEditDatabaseConnectionStringDlg::~CEditDatabaseConnectionStringDlg()
{
}

void CEditDatabaseConnectionStringDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDC_BTN_TEST, m_ctrlBtnTest);

	DDX_Control(pDX, IDC_EDIT_DESCRIZIONE, m_ctrlEditDescrizione);
	DDX_Control(pDX, IDC_EDIT_00, m_ctrlEdit00DBEngine);
	DDX_Control(pDX, IDC_EDIT_01, m_ctrlEdit01Driver);
	DDX_Control(pDX, IDC_EDIT_02, m_ctrlEdit02ServerDBQ);
	DDX_Control(pDX, IDC_EDIT_03, m_ctrlEdit03Username);
	DDX_Control(pDX, IDC_EDIT_04, m_ctrlEdit04Password);

	DDX_Control(pDX, IDC_STATIC_DESCRIZIONE, m_ctrlStaticDescrizione);
	DDX_Control(pDX, IDC_STATIC_00, m_ctrlStatic00);
	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic03);
	DDX_Control(pDX, IDC_STATIC_04, m_ctrlStatic04);
}

BEGIN_MESSAGE_MAP(CEditDatabaseConnectionStringDlg, CDialog)

	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_TEST, OnBnClickedBtnTest)

	ON_EN_CHANGE(IDC_EDIT_DESCRIZIONE, OnEnChangeEditDescrizione)
	ON_EN_CHANGE(IDC_EDIT_01, OnEnChangeEdit01)
	ON_EN_CHANGE(IDC_EDIT_02, OnEnChangeEdit02)
	ON_EN_CHANGE(IDC_EDIT_03, OnEnChangeEdit03)
	ON_EN_CHANGE(IDC_EDIT_04, OnEnChangeEdit04)

END_MESSAGE_MAP()

void CEditDatabaseConnectionStringDlg::OnCancel()
{
}

BOOL CEditDatabaseConnectionStringDlg::OnInitDialog()
{   
	CDialog::OnInitDialog();

	//
	if (m_bIsOracle)
	{
		m_ctrlEdit00DBEngine.SetWindowText("ORACLE");

		SetDlgItemText(IDC_STATIC_02, "DBQ");
	}
	else
	{
		m_ctrlEdit00DBEngine.SetWindowText("SQL SERVER");

		m_ctrlEdit01Driver.SetReadOnly(TRUE);
		m_ctrlEdit01Driver.SetWindowText("SQL Server");

		SetDlgItemText(IDC_STATIC_02, "Server");
	}

	//
	if (m_lID > 0)
	{
		CString sFilter;
		sFilter.Format("ID=%li", m_lID);

		CDatabasesSet setTemp;
		setTemp.SetOpenFilter(sFilter);
		if (setTemp.OpenRecordset("CEditDatabaseConnectionStringDlg::OnInitDialog"))
		{
			if (!setTemp.IsEOF())
			{
				m_ctrlEditDescrizione.SetWindowText(setTemp.m_sDescrizione);

				if (m_bIsOracle)
					m_ctrlEdit01Driver.SetWindowText(setTemp.m_sOracleDriver);

				m_ctrlEdit02ServerDBQ.SetWindowText(setTemp.m_sServerDBQ);

				m_ctrlEdit03Username.SetWindowText(setTemp.m_sUsername);

				m_ctrlEdit04Password.SetWindowText(setTemp.m_sPassword);
			}

			setTemp.CloseRecordset("CEditDatabaseConnectionStringDlg::OnInitDialog");
		}
	}

	//
	AggiornaTastoOK();

	//
	theApp.LocalizeDialog(this, CEditDatabaseConnectionStringDlg::IDD, "EditDatabaseConnectionStringDlg");
	SetWindowText(theApp.GetMessageString(m_lID <= 0 ? IDS_EDITDATABASECONNECTIONSTRING_TITLENEW : IDS_EDITDATABASECONNECTIONSTRING_TITLEEDT));

	//
	return TRUE;
}

void CEditDatabaseConnectionStringDlg::OnOK()
{
}

void CEditDatabaseConnectionStringDlg::OnBnClickedCancel()
{
	CDialog::OnCancel();
}

void CEditDatabaseConnectionStringDlg::OnBnClickedOk()
{
	BOOL bContinue = FALSE;

	CDatabasesSet setTemp;
	if (m_lID <= 0)
	{
		setTemp.SetOpenFilter("ID=0");
		if (setTemp.OpenRecordset("CEditDatabaseConnectionStringDlg::OnBnClickedOk"))
			bContinue = setTemp.AddNewRecordset("CEditDatabaseConnectionStringDlg::OnBnClickedOk");
	}
	else
	{
		CString sFilter;
		sFilter.Format("ID=%li", m_lID);

		setTemp.SetOpenFilter(sFilter);
		if (setTemp.OpenRecordset("CEditDatabaseConnectionStringDlg::OnBnClickedOk"))
			if(!setTemp.IsEOF())
				bContinue = setTemp.EditRecordset("CEditDatabaseConnectionStringDlg::OnBnClickedOk");
	}
	if (bContinue)
	{
		GetDlgItemText(IDC_EDIT_DESCRIZIONE, setTemp.m_sDescrizione);
		setTemp.m_sDescrizione.Trim();

		GetDlgItemText(IDC_EDIT_01, setTemp.m_sOracleDriver);
		setTemp.m_sOracleDriver.Trim();

		GetDlgItemText(IDC_EDIT_02, setTemp.m_sServerDBQ);
		setTemp.m_sServerDBQ.Trim();

		GetDlgItemText(IDC_EDIT_03, setTemp.m_sUsername);
		setTemp.m_sUsername.Trim();

		GetDlgItemText(IDC_EDIT_04, setTemp.m_sPassword);
		setTemp.m_sPassword.Trim();

		if(setTemp.UpdateRecordset("CEditDatabaseConnectionStringDlg::OnBnClickedOk"))
			if (m_lID <= 0)
				m_lID = setTemp.GetLastAdd();
	}
	setTemp.CloseRecordset("CEditDatabaseConnectionStringDlg::OnBnClickedOk");

	CDialog::OnOK();
}

void CEditDatabaseConnectionStringDlg::OnBnClickedBtnTest()
{
	BeginWaitCursor();
	m_ctrlBtnTest.EnableWindow(FALSE);

	CString s1;
	m_ctrlEdit01Driver.GetWindowText(s1);
	s1.Trim();

	CString s2;
	m_ctrlEdit02ServerDBQ.GetWindowText(s2);
	s2.Trim();

	CString s3;
	m_ctrlEdit03Username.GetWindowText(s3);
	s3.Trim();

	CString s4;
	m_ctrlEdit04Password.GetWindowText(s4);
	s4.Trim();

	CAMBaseDB dbTemp;
	try
	{
		dbTemp.OpenEx(ComponiStringaConnessione(m_bIsOracle, s1, s2, s3, s4), CDatabase::noOdbcDialog);

		EndWaitCursor();
		theApp.AfxMessageBoxEndo(IDS_DATABASE_OK);
	}
	catch (CDBException* pEx)
	{
		EndWaitCursor();
		theApp.MessageBoxEndo(pEx->m_strError, theApp.GetMessageString(IDS_DATABASE_KO));

		pEx->Delete();
	}
	if (dbTemp.IsOpen())
		dbTemp.Close();

	m_ctrlBtnTest.EnableWindow(TRUE);
	EndWaitCursor();
}

void CEditDatabaseConnectionStringDlg::AggiornaTastoOK()
{
	UpdateData(TRUE);

	CString sD;
	m_ctrlEditDescrizione.GetWindowText(sD);
	sD.Trim();

	CString s1;
	m_ctrlEdit01Driver.GetWindowText(s1);
	s1.Trim();

	CString s2;
	m_ctrlEdit02ServerDBQ.GetWindowText(s2);
	s2.Trim();

	CString s3;
	m_ctrlEdit03Username.GetWindowText(s3);
	s3.Trim();

	CString s4;
	m_ctrlEdit04Password.GetWindowText(s4);
	s4.Trim();

	m_ctrlButtonOK.EnableWindow(!sD.IsEmpty() && !s1.IsEmpty() && !s2.IsEmpty() && !s3.IsEmpty() && !s4.IsEmpty());
}

long CEditDatabaseConnectionStringDlg::GetLastAdd()
{
	return m_lID;
}

void CEditDatabaseConnectionStringDlg::OnEnChangeEditDescrizione()
{
	AggiornaTastoOK();
}

void CEditDatabaseConnectionStringDlg::OnEnChangeEdit01()
{
	AggiornaTastoOK();
}

void CEditDatabaseConnectionStringDlg::OnEnChangeEdit02()
{
	AggiornaTastoOK();
}

void CEditDatabaseConnectionStringDlg::OnEnChangeEdit03()
{
	AggiornaTastoOK();
}

void CEditDatabaseConnectionStringDlg::OnEnChangeEdit04()
{
	AggiornaTastoOK();
}
