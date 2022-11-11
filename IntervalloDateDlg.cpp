#include "stdafx.h"
#include "Endox.h"
#include "IntervalloDateDlg.h"

#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CIntervalloDateDlg::CIntervalloDateDlg(CWnd* pParent)
	: CDialog(CIntervalloDateDlg::IDD, pParent)
{
}

BEGIN_MESSAGE_MAP(CIntervalloDateDlg, CDialog)
	ON_WM_CTLCOLOR()

	ON_CBN_SELCHANGE(IDC_COMBO_DATA, OnCbnSelchangeComboData)
END_MESSAGE_MAP()

void CIntervalloDateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDCANCEL,				m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK,					m_ctrlBtnOK);

	DDX_Control(pDX, IDC_COMBO_DATA,		m_ctrlComboData);

	DDX_Control(pDX, IDC_EDIT_DATAINIZ,		m_ctrlDataFine);
	DDX_Control(pDX, IDC_EDIT_DATAFINE,		m_ctrlDataIniz);
	DDX_Control(pDX, IDC_EDIT_ORAINIZ,		m_ctrlOraFine);
	DDX_Control(pDX, IDC_EDIT_ORAFINE,		m_ctrlOraIniz);

	DDX_Control(pDX, IDC_STATIC_00,			m_ctrlStatic00);
	DDX_Control(pDX, IDC_STATIC_01,			m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02,			m_ctrlStatic02);
}

BOOL CIntervalloDateDlg::OnInitDialog() 
{
	BOOL bReturn = CDialog::OnInitDialog();

	InitComboDataPeriod(&m_ctrlComboData);

	m_ctrlDataIniz.SetEditMask("00/00/0000", "__/__/____");
	m_ctrlDataFine.SetEditMask("00/00/0000", "__/__/____");
	m_ctrlOraIniz.SetEditMask("00:00:00", "__:__:__");
	m_ctrlOraFine.SetEditMask("00:00:00", "__:__:__");

	theApp.LocalizeDialog(this, CIntervalloDateDlg::IDD, "IntervalloDateDlg");

	return bReturn;
}

void CIntervalloDateDlg::OnOK() 
{
	CString strTemp;

	UpdateData(TRUE);

	m_strFilter.Empty();
	GetNormalDateFilter(&m_strFilter, "DataOraSpeditoMetafora", this, &m_ctrlComboData, IDC_EDIT_DATAINIZ, IDC_EDIT_ORAINIZ, IDC_EDIT_DATAFINE, IDC_EDIT_ORAFINE);

	m_strDataOraIniz.Empty();
	GetDlgItemText(IDC_EDIT_DATAINIZ, strTemp);
	m_strDataOraIniz = strTemp;
	GetDlgItemText(IDC_EDIT_ORAINIZ, strTemp);
	m_strDataOraIniz += " " + strTemp;

	m_strDataOraFine.Empty();
	GetDlgItemText(IDC_EDIT_DATAFINE, strTemp);
	m_strDataOraFine = strTemp;
	GetDlgItemText(IDC_EDIT_ORAFINE, strTemp);
	m_strDataOraFine += " " + strTemp;

	CDialog::OnOK();
}

void CIntervalloDateDlg::OnCbnSelchangeComboData()
{
	ComboDataPeriodUpdated(&m_ctrlComboData, this, IDC_EDIT_DATAINIZ, IDC_EDIT_ORAINIZ, IDC_EDIT_DATAFINE, IDC_EDIT_ORAFINE);
}

CString CIntervalloDateDlg::GetFilter()
{
	return m_strFilter;
}

CString CIntervalloDateDlg::GetDataOraIniz()
{
	return m_strDataOraIniz;
}

CString CIntervalloDateDlg::GetDataOraFine()
{
	return m_strDataOraFine;
}