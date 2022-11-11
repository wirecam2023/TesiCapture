//Luiz - 01/07/2019 - P3 - Permitir combobox de variáveis de laudo exibir até 200 caracteres
#include "stdafx.h"
#include "Endox.h"
#include "SelectComboItemGrandeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


const UINT CSelectComboItemGrandeDlg::m_uiIDD[5] = { IDD_SELECT_COMBO_GRANDE_50,
											   	     IDD_SELECT_COMBO_GRANDE_80,
												     IDD_SELECT_COMBO_GRANDE_100,
												     IDD_SELECT_COMBO_GRANDE_150,
												     IDD_SELECT_COMBO_GRANDE_200 };

IMPLEMENT_DYNAMIC(CSelectComboItemGrandeDlg, CDialog)

CSelectComboItemGrandeDlg::CSelectComboItemGrandeDlg(CWnd* pParent, const CString &sTitle, CString *sArray, long lArraySize, long lRectSize)
: CDialog(m_uiIDD[lRectSize], pParent)
{
	m_sTitle = sTitle;
	m_sArray = sArray;
	m_lArraySize = lArraySize;
}

CSelectComboItemGrandeDlg::CSelectComboItemGrandeDlg() : CDialog(m_uiIDD[0], NULL) { }


CSelectComboItemGrandeDlg::~CSelectComboItemGrandeDlg()
{
}

long CSelectComboItemGrandeDlg::GetRectSize(CString sTesto)
{
	//int iMaxWidth = GetSystemMetrics(SM_CXSCREEN);
	int iMaxHeight = GetSystemMetrics(SM_CYSCREEN);
	long lRetorno = 0;
	if (iMaxHeight <= 800)
	{
		if (sTesto.GetLength() > 100)
			lRetorno = 3;
		else if (sTesto.GetLength() > 80)
			lRetorno = 2;
		else if (sTesto.GetLength() > 50)
			lRetorno = 1;
		else
			lRetorno = 0;
	}
	else
	{
		if (sTesto.GetLength() > 150)
			lRetorno = 4;
		else if (sTesto.GetLength() > 100)
			lRetorno = 3;
		else if (sTesto.GetLength() > 80)
			lRetorno = 2;
		else if (sTesto.GetLength() > 50)
			lRetorno = 1;
		else
			lRetorno = 0;
	}
	return lRetorno;
}

void CSelectComboItemGrandeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_1, m_ctrlCombo1);
	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK, m_ctrlBtnOk);
}

BEGIN_MESSAGE_MAP(CSelectComboItemGrandeDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_1, OnCbnSelchangeCombo1)
END_MESSAGE_MAP()

BOOL CSelectComboItemGrandeDlg::OnInitDialog()
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

void CSelectComboItemGrandeDlg::OnOK()
{
	int nIndex = m_ctrlCombo1.GetCurSel();

	m_ctrlCombo1.GetLBText(nIndex, m_sSelectedItem);

	m_sArray = NULL;
	delete(m_sArray);

	CDialog::OnOK();
}

void CSelectComboItemGrandeDlg::OnCbnSelchangeCombo1()
{
	m_ctrlBtnOk.EnableWindow(m_ctrlCombo1.GetCurSel() >= 0);
}

// CSelectComboItemGrandeDlg message handlers