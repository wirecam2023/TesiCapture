#include "stdafx.h"
#include "Endox.h"
#include "MessageBoxTimerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMessageBoxTimerDlg, CDialog)

CMessageBoxTimerDlg::CMessageBoxTimerDlg(CWnd* pParent, CString sMainMessage, UINT uidTitleMessage, UINT uidBtnOKMessage, UINT uidBtnCancelMessage, long lTimerPartenza)
	: CDialog(CMessageBoxTimerDlg::IDD, pParent)
{
	m_sMainMessage = sMainMessage;
	m_uidTitleMessage = uidTitleMessage;
	m_uidBtnOKMessage = uidBtnOKMessage;
	m_uidBtnCancelMessage = uidBtnCancelMessage;
	m_lTimerPartenza = lTimerPartenza;
}

CMessageBoxTimerDlg::~CMessageBoxTimerDlg()
{
}

BEGIN_MESSAGE_MAP(CMessageBoxTimerDlg, CDialog)

	ON_WM_CTLCOLOR()
	ON_WM_TIMER()

END_MESSAGE_MAP()

void CMessageBoxTimerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);

	DDX_Control(pDX, IDC_STATIC_MAIN_MESSAGE, m_ctrlStaticMainMessage);
}

void CMessageBoxTimerDlg::OnCancel()
{
	if (m_ctrlBtnCancel.IsWindowEnabled())
	{
		KillTimer(ATTIVA_TASTO_TIMER);
		CDialog::OnCancel();
	}
}

BOOL CMessageBoxTimerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//

	m_ctrlBtnCancel.SetFont(&theApp.m_fontBold);
	m_ctrlBtnOK.SetFont(&theApp.m_fontBold);
	m_ctrlStaticMainMessage.SetFont(&theApp.m_fontBold);

	//

	SetWindowText(theApp.GetMessageString(m_uidTitleMessage));

	//

	m_ctrlStaticMainMessage.SetWindowText(m_sMainMessage);

	//

	m_ctrlBtnCancel.SetWindowText(theApp.GetMessageString(m_uidBtnCancelMessage));

	//

	if (m_lTimerPartenza > 0)
	{
		CString strTempCountdown;
		strTempCountdown.Format("%li", m_lTimerPartenza);

		m_ctrlBtnOK.SetWindowText(strTempCountdown);

		m_lTimerPartenza--;

		SetTimer(ATTIVA_TASTO_TIMER, 1000, NULL);
	}
	else
	{
		m_ctrlBtnOK.EnableWindow();
		m_ctrlBtnOK.SetWindowText(theApp.GetMessageString(m_uidBtnOKMessage));
	}

	//

	MessageBeep(MB_ICONHAND);

	//

	return TRUE;
}

void CMessageBoxTimerDlg::OnOK()
{
	if (m_ctrlBtnOK.IsWindowEnabled())
	{
		KillTimer(ATTIVA_TASTO_TIMER);
		CDialog::OnOK();
	}
}

HBRUSH CMessageBoxTimerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_MAIN_MESSAGE:
		{
			pDC->SetTextColor(theApp.m_color[4]);
			break;
		}
	}

	return hBrush;
}

void CMessageBoxTimerDlg::OnTimer(UINT nIDEvent)
{
	if (nIDEvent == ATTIVA_TASTO_TIMER)
	{
		if (m_lTimerPartenza > 0)
		{
			CString strTempCountdown;
			strTempCountdown.Format("%li", m_lTimerPartenza);

			m_ctrlBtnOK.SetWindowText(strTempCountdown);

			m_lTimerPartenza--;
		}
		else
		{
			KillTimer(ATTIVA_TASTO_TIMER);

			m_ctrlBtnOK.EnableWindow(TRUE);
			m_ctrlBtnOK.SetWindowText(theApp.GetMessageString(m_uidBtnOKMessage));
		}
	}
}
