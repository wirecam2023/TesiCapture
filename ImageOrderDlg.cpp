#include "stdafx.h"
#include "Endox.h"
#include "ImageOrderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CImageOrderDlg, CDialog)

CImageOrderDlg::CImageOrderDlg(CWnd* pParent)
	: CDialog(CImageOrderDlg::IDD, pParent)
{
	m_nPosition = 1;
	m_nMax = 1;
}

CImageOrderDlg::~CImageOrderDlg()
{
}

BEGIN_MESSAGE_MAP(CImageOrderDlg, CDialog)
END_MESSAGE_MAP()

void CImageOrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SPIN, m_ctrlSpin);
}

BOOL CImageOrderDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	if ((m_nPosition == 1) && (m_nMax == 1))
		OnCancel();

	SetDlgItemInt(IDC_EDIT_DA, m_nPosition);

	m_ctrlSpin.SetRange(m_nMax, 1);
	m_ctrlSpin.SetPos(m_nPosition);

	return bReturn;
}

void CImageOrderDlg::OnOK()
{
	int nLower;
	int nUpper;
	m_ctrlSpin.GetRange(nLower, nUpper);

	m_nPosition = m_ctrlSpin.GetPos();
	m_nPosition = max(m_nPosition, 1);
	m_nPosition = min(m_nPosition, nLower);

	CDialog::OnOK();
}

int CImageOrderDlg::GetNewPos()
{
	return m_nPosition;
}

void CImageOrderDlg::SetParam(int nPosition, int nMax)
{
	m_nPosition = nPosition;
	m_nMax = nMax;
}