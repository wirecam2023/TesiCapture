// SelectNumeroFichaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Endox.h"
#include "SelectNumeroFichaDlg.h"
#include "afxdialogex.h"


// CSelectNumeroFichaDlg dialog

IMPLEMENT_DYNAMIC(CSelectNumeroFichaDlg, CDialog)

CSelectNumeroFichaDlg::CSelectNumeroFichaDlg(CWnd* pParent, CString *sArray, long lArraySize)
	: CDialog(CSelectNumeroFichaDlg::IDD, pParent)
{
	m_sArray = sArray;
	m_lArraySize = lArraySize;
}

CSelectNumeroFichaDlg::CSelectNumeroFichaDlg(CWnd* pParent, const CString &sTitle, CString *sArray, long lArraySize)
	: CDialog(CSelectNumeroFichaDlg::IDD, pParent)
{
	m_sTitle = sTitle;
	m_sArray = sArray;
	m_lArraySize = lArraySize;
}


CSelectNumeroFichaDlg::~CSelectNumeroFichaDlg()
{
}

void CSelectNumeroFichaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_1, m_ctrlCombo1);
	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK, m_ctrlBtnOk);
}


BEGIN_MESSAGE_MAP(CSelectNumeroFichaDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_1, OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


BOOL CSelectNumeroFichaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (!m_sTitle.IsEmpty())
		SetWindowText(m_sTitle);

	for (int i = 0; i < m_lArraySize; i++)
	{
		int nIndex = m_ctrlCombo1.AddString(m_sArray[i]);		
	}

	if (m_lArraySize > 0)
	{
		m_ctrlCombo1.SetCurSel(0);
		m_ctrlBtnOk.EnableWindow(m_ctrlCombo1.GetCurSel() >= 0);
	}
		

	return TRUE;
}

void CSelectNumeroFichaDlg::OnOK()
{
	int nIndex = m_ctrlCombo1.GetCurSel();

	m_ctrlCombo1.GetLBText(nIndex, m_sSelectedFicha);

	m_sArray = NULL;
	delete(m_sArray);

	CDialog::OnOK();
}

void CSelectNumeroFichaDlg::OnCbnSelchangeCombo1()
{
	m_ctrlBtnOk.EnableWindow(m_ctrlCombo1.GetCurSel() >= 0);
}

// CSelectNumeroFichaDlg message handlers
