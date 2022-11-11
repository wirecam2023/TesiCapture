#include "stdafx.h"
#include "Endox.h"
#include "APGroupNumberWaitingDlg.h"

#include "EsamiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CHECK_TIMER 0x988

IMPLEMENT_DYNAMIC(CAPGroupNumberWaitingDlg, CDialog)

CAPGroupNumberWaitingDlg::CAPGroupNumberWaitingDlg(CWnd* pParentWnd, long lExamID)
: CDialog(CAPGroupNumberWaitingDlg::IDD, pParentWnd)
{
	m_lExamID = lExamID;
}


CAPGroupNumberWaitingDlg::~CAPGroupNumberWaitingDlg()
{
}

BEGIN_MESSAGE_MAP(CAPGroupNumberWaitingDlg, CDialog)

	ON_WM_TIMER()

END_MESSAGE_MAP()

void CAPGroupNumberWaitingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CAPGroupNumberWaitingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//
	theApp.LocalizeDialog(this, CAPGroupNumberWaitingDlg::IDD, "APGroupNumberWaitingDlg");

	SetTimer(CHECK_TIMER, 500, NULL);

	//
	return TRUE;
}

void CAPGroupNumberWaitingDlg::OnCancel()
{
	CDialog::OnCancel();
}

void CAPGroupNumberWaitingDlg::OnOK()
{

}

void CAPGroupNumberWaitingDlg::OnTimer(UINT nIDEvent)
{
	switch (nIDEvent)
	{
	case CHECK_TIMER:
	{
		this->KillTimer(CHECK_TIMER);

		if (!ResultChanged())
			SetTimer(CHECK_TIMER, 500, NULL);
		else
			CDialog::OnOK();

		break;
	}
	}

	CDialog::OnTimer(nIDEvent);
}

BOOL CAPGroupNumberWaitingDlg::ResultChanged()
{
	CString filter;
	filter.Format("CONTATORE=%li", m_lExamID);
	CEsamiSet esamiSet;
	esamiSet.SetOpenFilter(filter);

	BOOL bSuccess = FALSE;

	if (esamiSet.OpenRecordset("CAPGroupNumberWaitingDlg::ResultChanged"))
	{
		if (!esamiSet.IsEOF())
		{
			if (!esamiSet.IsFieldNull(&esamiSet.m_sAPGroupNumber) && esamiSet.m_sAPGroupNumber.GetLength() > 0)
			{
				bSuccess = TRUE;
			}
		}

		esamiSet.CloseRecordset("CAPGroupNumberWaitingDlg::ResultChanged");
	}

	return bSuccess;
}