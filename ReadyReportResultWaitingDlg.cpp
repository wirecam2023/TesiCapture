#include "stdafx.h"
#include "Endox.h"
#include "ReadyReportResultWaitingDlg.h"

#include "EsamiChiusiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CHECK_TIMER 0x988

IMPLEMENT_DYNAMIC(CReadyReportResultWaitingDlg, CDialog)

CReadyReportResultWaitingDlg::CReadyReportResultWaitingDlg(CWnd* pParentWnd, long lClosedExamId, BOOL* bResult, CString* sResult)
: CDialog(CReadyReportResultWaitingDlg::IDD, pParentWnd)
{
	m_bResult = bResult;
	m_lClosedExamId = lClosedExamId;
	m_sResult = sResult;
}


CReadyReportResultWaitingDlg::~CReadyReportResultWaitingDlg()
{
}

BEGIN_MESSAGE_MAP(CReadyReportResultWaitingDlg, CDialog)

	ON_WM_TIMER()

END_MESSAGE_MAP()

void CReadyReportResultWaitingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CReadyReportResultWaitingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//
	theApp.LocalizeDialog(this, CReadyReportResultWaitingDlg::IDD, "ReadyReportResultWaitingDlg");

	SetTimer(CHECK_TIMER, 500, NULL);

	//
	return TRUE;
}

void CReadyReportResultWaitingDlg::OnCancel()
{
	CDialog::OnCancel();
}

void CReadyReportResultWaitingDlg::OnOK()
{

}

void CReadyReportResultWaitingDlg::OnTimer(UINT nIDEvent)
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

BOOL CReadyReportResultWaitingDlg::ResultChanged()
{
	CString filter;
	filter.Format("ID=%li", m_lClosedExamId);
	CEsamiChiusiSet esamiChiusiSet;
	esamiChiusiSet.SetOpenFilter(filter);

	BOOL bSuccess = FALSE;

	if (esamiChiusiSet.OpenRecordset("CReadyReportResultWaitingDlg::ResultChanged"))
	{
		if (!esamiChiusiSet.IsEOF())
		{
			if (esamiChiusiSet.m_lEseguito > 0)
			{
				if (esamiChiusiSet.m_lEseguito == 1)
				{
					if (!esamiChiusiSet.IsFieldNull(&esamiChiusiSet.m_sEsito) && esamiChiusiSet.m_sEsito.GetLength() > 0)
					{
						if (esamiChiusiSet.m_lEseguito == IntegrationSendStatus::errored)
						{
							*m_bResult = FALSE;							
						}
						else
						{
							*m_bResult = TRUE;
						}
						
						m_sResult->Format("%s", esamiChiusiSet.m_sEsito);
						bSuccess = TRUE;
					}
				}				
				else
				{
					bSuccess = TRUE;
					*m_bResult = FALSE;
					m_sResult->Format("L'esame è stato generato con accettazione diretta in Endox. Non è possibile firmare il referto.");
				}
			}
		}

		esamiChiusiSet.CloseRecordset("CReadyReportResultWaitingDlg::ResultChanged");
	}

	return bSuccess;
}