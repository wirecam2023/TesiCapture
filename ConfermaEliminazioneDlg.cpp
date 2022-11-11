#include "stdafx.h"
#include "Endox.h"
#include "ConfermaEliminazioneDlg.h"

#include "Common.h"
#include "TipoEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CConfermaEliminazioneDlg, CDialog)

CConfermaEliminazioneDlg::CConfermaEliminazioneDlg(CWnd* pParent, CString sElementiSelezionati)
	: CDialog(CConfermaEliminazioneDlg::IDD, pParent)
{
	m_lCountdown = theApp.m_lCountdownPartenza - 1;

	m_sElementiSelezionati = " " + sElementiSelezionati + " ";
}

CConfermaEliminazioneDlg::~CConfermaEliminazioneDlg()
{
}

BEGIN_MESSAGE_MAP(CConfermaEliminazioneDlg, CDialog)

	ON_BN_CLICKED(IDC_BTN_ANNULLA, OnBnClickedBtnAnnullaEliminazione)
	ON_BN_CLICKED(IDC_BTN_CONFERMA, OnBnClickedBtnConfermaEliminazione)

	ON_WM_CTLCOLOR()
	ON_WM_TIMER()

END_MESSAGE_MAP()

void CConfermaEliminazioneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_ANNULLA, m_ctrlButtonAnnullaEliminazione);
	DDX_Control(pDX, IDC_BTN_CONFERMA, m_ctrlButtonConfermaEliminazione);
	DDX_Control(pDX, IDC_STATIC_LABEL1, m_ctrlStaticLabel1);
	DDX_Control(pDX, IDC_STATIC_LABEL2, m_ctrlStaticLabel2);
}

void CConfermaEliminazioneDlg::OnCancel()
{
}

BOOL CConfermaEliminazioneDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlStaticLabel1.SetFont(&theApp.m_fontBold);
	m_ctrlStaticLabel2.SetFont(&theApp.m_fontBigBig);
	m_ctrlButtonAnnullaEliminazione.SetFont(&theApp.m_fontBold);
	m_ctrlButtonConfermaEliminazione.SetFont(&theApp.m_fontBold);

	// --- //

	m_ctrlStaticLabel2.SetWindowText(m_sElementiSelezionati);

	// --- //

	SetTimer(ATTIVA_TASTO_TIMER, 1000, NULL);

	// --- //

	theApp.LocalizeDialog(this, CConfermaEliminazioneDlg::IDD, "ConfermaEliminazioneDlg");
	return TRUE;
}

void CConfermaEliminazioneDlg::OnOK()
{
}

HBRUSH CConfermaEliminazioneDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_LABEL2:
		{
			pDC->SetBkColor(RGB(255, 255, 0));
			pDC->SetTextColor(theApp.m_color[0]);
			break;
		}
	}

	return hBrush;
}

void CConfermaEliminazioneDlg::OnTimer(UINT nIDEvent)
{
	if (nIDEvent == ATTIVA_TASTO_TIMER)
	{
		if (m_lCountdown > 0)
		{
			CString strTempCountdown;
			strTempCountdown.Format("%li", m_lCountdown);
			m_ctrlButtonConfermaEliminazione.SetWindowText(strTempCountdown);

			m_lCountdown--;
		}
		else
		{
			KillTimer(ATTIVA_TASTO_TIMER);

			m_ctrlButtonConfermaEliminazione.SetWindowText(theApp.GetMessageString(IDS_CONFERMA_ELIMINAZIONE));
			m_ctrlButtonConfermaEliminazione.EnableWindow(TRUE);
		}
	}
}

void CConfermaEliminazioneDlg::OnBnClickedBtnAnnullaEliminazione()
{
	if (m_ctrlButtonAnnullaEliminazione.IsWindowEnabled())
		CDialog::OnCancel();
}

void CConfermaEliminazioneDlg::OnBnClickedBtnConfermaEliminazione()
{
	if (m_ctrlButtonConfermaEliminazione.IsWindowEnabled())
		CDialog::OnOK();
}
