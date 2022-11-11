#include "stdafx.h"
#include "Endox.h"
#include "EditUnitaTCPDlg.h"

#include "Common.h"
#include "UnitaTCPSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEditUnitaTCPDlg, CDialog)

CEditUnitaTCPDlg::CEditUnitaTCPDlg(CWnd* pParent, BOOL bIsOracle, long lID)
: CDialog(CEditUnitaTCPDlg::IDD, pParent)
{
	m_bIsOracle = bIsOracle;
	m_lID = lID;
}

CEditUnitaTCPDlg::~CEditUnitaTCPDlg()
{
}

void CEditUnitaTCPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);

	DDX_Control(pDX, IDC_EDIT_DESCRIZIONE, m_ctrlEditDescrizione);
	DDX_Control(pDX, IDC_EDIT_00, m_ctrlEdit00Unita);
	DDX_Control(pDX, IDC_EDIT_01, m_ctrlEdit01Endpoint);

	DDX_Control(pDX, IDC_STATIC_DESCRIZIONE, m_ctrlStaticDescrizione);
	DDX_Control(pDX, IDC_STATIC_00, m_ctrlStatic00);
	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
}

BEGIN_MESSAGE_MAP(CEditUnitaTCPDlg, CDialog)

	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)

	ON_EN_CHANGE(IDC_EDIT_DESCRIZIONE, OnEnChangeEditDescrizione)
	ON_EN_CHANGE(IDC_EDIT_00, OnEnChangeEdit00)
	ON_EN_CHANGE(IDC_EDIT_01, OnEnChangeEdit01)

END_MESSAGE_MAP()

void CEditUnitaTCPDlg::OnCancel()
{
}

BOOL CEditUnitaTCPDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_lID > 0)
	{
		CString sFilter;
		sFilter.Format("ID=%li", m_lID);

		CUnitaTCPSet setTemp;
		setTemp.SetOpenFilter(sFilter);
		if (setTemp.OpenRecordset("CEditUnitaTCPDlg::OnInitDialog"))
		{
			if (!setTemp.IsEOF())
			{
				m_ctrlEditDescrizione.SetWindowText(setTemp.m_sDescrizione);

				CString sUnita;
				sUnita.Format("%li", setTemp.m_lUnita);
				m_ctrlEdit00Unita.SetWindowText(sUnita);

				m_ctrlEdit01Endpoint.SetWindowText(setTemp.m_sEndpoint);
			}

			setTemp.CloseRecordset("CEditUnitaTCPDlg::OnInitDialog");
		}
	}

	//
	AggiornaTastoOK();

	//
	theApp.LocalizeDialog(this, CEditUnitaTCPDlg::IDD, "EditUnitaTCPDlg");
	SetWindowText(theApp.GetMessageString(m_lID <= 0 ? IDS_EDITDATABASECONNECTIONSTRING_TITLENEW : IDS_EDITDATABASECONNECTIONSTRING_TITLEEDT));

	//
	return TRUE;
}

void CEditUnitaTCPDlg::OnOK()
{
}

void CEditUnitaTCPDlg::OnBnClickedCancel()
{
	CDialog::OnCancel();
}

void CEditUnitaTCPDlg::OnBnClickedOk()
{
	BOOL bContinue = FALSE;

	CUnitaTCPSet setTemp;
	if (m_lID <= 0)
	{
		setTemp.SetOpenFilter("ID=0");
		if (setTemp.OpenRecordset("CEditUnitaTCPDlg::OnBnClickedOk"))
			bContinue = setTemp.AddNewRecordset("CEditUnitaTCPDlg::OnBnClickedOk");
	}
	else
	{
		CString sFilter;
		sFilter.Format("ID=%li", m_lID);

		setTemp.SetOpenFilter(sFilter);
		if (setTemp.OpenRecordset("CEditUnitaTCPDlg::OnBnClickedOk"))
			if (!setTemp.IsEOF())
				bContinue = setTemp.EditRecordset("CEditUnitaTCPDlg::OnBnClickedOk");
	}
	if (bContinue)
	{
		GetDlgItemText(IDC_EDIT_DESCRIZIONE, setTemp.m_sDescrizione);
		setTemp.m_sDescrizione.Trim();

		setTemp.m_lUnita = GetDlgItemInt(IDC_EDIT_00);

		GetDlgItemText(IDC_EDIT_01, setTemp.m_sEndpoint);
		setTemp.m_sEndpoint.Trim();

		if (setTemp.UpdateRecordset("CEditUnitaTCPDlg::OnBnClickedOk"))
			if (m_lID <= 0)
				m_lID = setTemp.GetLastAdd();
	}
	setTemp.CloseRecordset("CEditUnitaTCPDlg::OnBnClickedOk");

	CDialog::OnOK();
}

void CEditUnitaTCPDlg::AggiornaTastoOK()
{
	UpdateData(TRUE);

	CString sD;
	m_ctrlEditDescrizione.GetWindowText(sD);
	sD.Trim();

	CString s1;
	m_ctrlEdit01Endpoint.GetWindowText(s1);
	s1.Trim();

	m_ctrlButtonOK.EnableWindow(!sD.IsEmpty() && !s1.IsEmpty());
}

long CEditUnitaTCPDlg::GetLastAdd()
{
	return m_lID;
}

void CEditUnitaTCPDlg::OnEnChangeEditDescrizione()
{
	AggiornaTastoOK();
}


void CEditUnitaTCPDlg::OnEnChangeEdit00()
{
	AggiornaTastoOK();
}

void CEditUnitaTCPDlg::OnEnChangeEdit01()
{
	AggiornaTastoOK();
}
