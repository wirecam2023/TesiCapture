#include "stdafx.h"
#include "Endox.h"
#include "VitalSignPdfWaitingDlg.h"

#include "VitalSignMisurazioniHeaderSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CHECK_TIMER 0x988

IMPLEMENT_DYNAMIC(CVitalSignPdfWaitingDlg, CDialog)

CVitalSignPdfWaitingDlg::CVitalSignPdfWaitingDlg(CWnd* pParentWnd, long lIDHeaderMisurazione, long oldIdPdf)
: CDialog(CVitalSignPdfWaitingDlg::IDD, pParentWnd)
{
	m_lIDHeaderMisurazione = lIDHeaderMisurazione;
	m_lOldIdPdf = oldIdPdf;
}


CVitalSignPdfWaitingDlg::~CVitalSignPdfWaitingDlg()
{
}

BEGIN_MESSAGE_MAP(CVitalSignPdfWaitingDlg, CDialog)

	ON_WM_TIMER()

END_MESSAGE_MAP()

void CVitalSignPdfWaitingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);	
}

BOOL CVitalSignPdfWaitingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();	

	//
	theApp.LocalizeDialog(this, CVitalSignPdfWaitingDlg::IDD, "VitalSignPdfWaitingDlg");

	SetTimer(CHECK_TIMER, 500, NULL);

	//
	return TRUE;
}

void CVitalSignPdfWaitingDlg::OnCancel()
{
	CDialog::OnCancel();
}

void CVitalSignPdfWaitingDlg::OnOK()
{

}

void CVitalSignPdfWaitingDlg::OnTimer(UINT nIDEvent)
{
	switch (nIDEvent)
	{
		case CHECK_TIMER:
		{			
			this->KillTimer(CHECK_TIMER);			

			if (!PdfChanged())
				SetTimer(CHECK_TIMER, 500, NULL);
			else
				CDialog::OnOK();

			break;
		}
	}

	CDialog::OnTimer(nIDEvent);
}

BOOL CVitalSignPdfWaitingDlg::PdfChanged()
{
	CString filter;
	filter.Format("ID=%li", m_lIDHeaderMisurazione);
	CVitalSignMisurazioniHeaderSet vitalSignMisSet;
	vitalSignMisSet.SetOpenFilter(filter);
	
	BOOL bSuccess = FALSE;

	if (vitalSignMisSet.OpenRecordset("CVitalSignPdfWaitingDlg::PdfChanged"))
	{
		if (!vitalSignMisSet.IsEOF())
		{
			if (vitalSignMisSet.m_lIDPdf != m_lOldIdPdf)
				bSuccess = TRUE;
		}

		vitalSignMisSet.CloseRecordset("CVitalSignPdfWaitingDlg::PdfChanged");
	}

	return bSuccess;
}