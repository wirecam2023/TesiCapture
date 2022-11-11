#include "stdafx.h"
#include "Endox.h"
#include "GetCodeFiscDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CGetCodeFiscDlg::CGetCodeFiscDlg(CWnd* pParent)
	: CDialog(CGetCodeFiscDlg::IDD, pParent)
{
	m_sCode = "";
}

BEGIN_MESSAGE_MAP(CGetCodeFiscDlg, CDialog)
END_MESSAGE_MAP()

void CGetCodeFiscDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);
}

BOOL CGetCodeFiscDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	theApp.LocalizeDialog(this, CGetCodeFiscDlg::IDD, "GetCodeFiscDlg");
	return bReturn;
}

void CGetCodeFiscDlg::OnOK()
{
	CString strTempCode;
	GetDlgItemText(IDC_CODE, strTempCode);

	strTempCode.Trim();
	if (strTempCode.GetLength() < 16)
	{
		MessageBeep(0xFFFFFFFF);
		SetDlgItemText(IDC_CODE, "");
		return;
	}
	else // if (strTempCode.GetLength() < 32)
	{
		// codice fiscale in chiaro (barcode) //

		m_sCode = strTempCode.Left(16);
	}
	/* else
	{
		// codice fiscale codificato (banda magnetica) //

		strTempCode = strTempCode.Left(32);

		m_sCode = "";
		for(int i = 0; i < 32; i += 2)
		{
			long lVal = atol(strTempCode.Mid(i, 2));
			if (lVal < 10)
			{
				CString sVal;
				sVal.Format("%li", lVal);
				m_sCode += sVal;
			}
			else
			{
				CString sVal;
				sVal.Format("%c", 'A' + lVal - 11);
				m_sCode += sVal;
			}
		}
	} */

	CDialog::OnOK();
}