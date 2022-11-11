#include "stdafx.h"
#include "Endox.h"
#include "InsertTableDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CInsertTableDlg, CDialog)

CInsertTableDlg::CInsertTableDlg(CWnd* pParent)
	: CDialog(CInsertTableDlg::IDD, pParent)
{
	m_shRows = 3;
	m_shCols = 3;
	m_shBordi = 0;
}

CInsertTableDlg::~CInsertTableDlg()
{
}

BEGIN_MESSAGE_MAP(CInsertTableDlg, CDialog)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_BORDI, OnDeltaposSpinBordi)
END_MESSAGE_MAP()

void CInsertTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);

	DDX_Control(pDX, IDC_SPIN_ROWS, m_ctrlSpinRows);
	DDX_Control(pDX, IDC_SPIN_COLS, m_ctrlSpinCols);
	DDX_Control(pDX, IDC_SPIN_BORDI, m_ctrlSpinBordi);

	DDX_Control(pDX, IDC_STATIC_ROWS, m_ctrlStaticRows);
	DDX_Control(pDX, IDC_STATIC_COLS, m_ctrlStaticCols);
	DDX_Control(pDX, IDC_STATIC_BORDI, m_ctrlStaticBordi);
}

BOOL CInsertTableDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlSpinRows.SetRange(1, 99);
	m_ctrlSpinRows.SetPos(m_shRows);

	m_ctrlSpinCols.SetRange(1, 19);
	m_ctrlSpinCols.SetPos(m_shCols);

	//

	m_ctrlSpinBordi.SetRange(0, 12);
	m_ctrlSpinBordi.SetPos(m_shBordi);

	float fTemp = (float)m_ctrlSpinBordi.GetPos32() / (float)4;

	CString sTemp;
	sTemp.Format("%.2f", fTemp);
	SetDlgItemText(IDC_EDIT_BORDI, sTemp);

	//

	theApp.LocalizeDialog(this, CInsertTableDlg::IDD, "InsertTableDlg");
	return TRUE;
}

void CInsertTableDlg::OnOK()
{
	m_shRows = m_ctrlSpinRows.GetPos();
	m_shCols = m_ctrlSpinCols.GetPos();
	m_shBordi = m_ctrlSpinBordi.GetPos();

	CDialog::OnOK();
}

short CInsertTableDlg::GetRows()
{
	return m_shRows;
}

short CInsertTableDlg::GetCols()
{
	return m_shCols;
}

short CInsertTableDlg::GetBordi()
{
	return m_shBordi * 5; // fidati che è giusto moltiplicarlo per 5 //
}

void CInsertTableDlg::OnDeltaposSpinBordi(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	//

	float fTemp = (float)(pNMUpDown->iPos + pNMUpDown->iDelta) / (float)4;

	CString sTemp;
	sTemp.Format("%.2f", fTemp);
	SetDlgItemText(IDC_EDIT_BORDI, sTemp);

	//

	*pResult = 0;
}
