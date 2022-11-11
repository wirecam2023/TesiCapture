#include "stdafx.h"
#include "Endox.h"
#include "EndoGridMonthCalDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDC_MONTHCAL      1000

CEndoGridMonthCalDlg::CEndoGridMonthCalDlg(CString strValue, CRect rect, CString strFormat)
	: CDialog(CEndoGridMonthCalDlg::IDD)
{
	m_strFormat = strFormat;
	m_strValue = strValue;
	m_pMonthCtrl = NULL;
	m_rectItem = rect;
}

BEGIN_MESSAGE_MAP(CEndoGridMonthCalDlg, CDialog)
	ON_NOTIFY(MCN_SELECT, IDC_MONTHCAL, OnSelect)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

BOOL CEndoGridMonthCalDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_pMonthCtrl = new CXTMonthCalCtrl();

	m_pMonthCtrl->CreateEx(0,
		MONTHCAL_CLASS,
		NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER | MCS_WEEKNUMBERS,
		CRect(0, 0, 0, 0),
		this,
		IDC_MONTHCAL);

	CRect rect;
	if (m_pMonthCtrl->GetMinReqRect(rect))
	{
		m_pMonthCtrl->SetWindowPos(NULL,
			0,
			0,
			rect.Width(),
			rect.Height(),
			SWP_NOZORDER | SWP_NOACTIVATE);
		AdjustWindowRect(&rect, GetStyle(), FALSE);
		SetWindowPos(NULL,
			m_rectItem.right - rect.Width(),
			m_rectItem.top,
			rect.Width(),
			rect.Height(),
			SWP_NOZORDER);
	}

	m_pMonthCtrl->SetOwner(this);
	m_pMonthCtrl->SetFocus();

	if (m_strValue.GetLength() == 14)
	{
		COleDateTime date(atoi(m_strValue.Left(4)), atoi(m_strValue.Mid(4, 2)), atoi(m_strValue.Mid(6, 2)), 0, 0, 0);
		m_pMonthCtrl->SetCurSel(date);
	}

	return TRUE;
}

void CEndoGridMonthCalDlg::OnDestroy()
{
	if (m_pMonthCtrl)
	{
		if (m_pMonthCtrl->GetSafeHwnd())
			m_pMonthCtrl->DestroyWindow();
		delete m_pMonthCtrl;
	}

	CDialog::OnDestroy();
}

void CEndoGridMonthCalDlg::OnSelect(NMHDR*, LRESULT*)
{
	OnOK();
}

void CEndoGridMonthCalDlg::OnOK()
{
	SYSTEMTIME sysTime;
	::SendMessage(m_pMonthCtrl->GetSafeHwnd(), MCM_GETCURSEL, 0, (LPARAM)&sysTime);

	sysTime.wHour = sysTime.wMinute = sysTime.wSecond = sysTime.wMilliseconds = 0;

	COleDateTime dtSelected(sysTime);
	m_strDate = dtSelected.Format(m_strFormat);

	CDialog::OnOK();
}