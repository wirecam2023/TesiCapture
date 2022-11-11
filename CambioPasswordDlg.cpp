#include "stdafx.h"
#include "Endox.h"
#include "CambioPasswordDlg.h"

#include "DLL_Imaging\h\AmDes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCambioPasswordDlg, CDialog)

CCambioPasswordDlg::CCambioPasswordDlg(CWnd* pParent)
	: CDialog(CCambioPasswordDlg::IDD, pParent)
{
}

CCambioPasswordDlg::~CCambioPasswordDlg()
{
}

BEGIN_MESSAGE_MAP(CCambioPasswordDlg, CDialog)


END_MESSAGE_MAP()

void CCambioPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_PWDOLD, m_sPwdOld);
	DDX_Text(pDX, IDC_EDIT_PWDNEW1, m_sPwdNew1);
	DDX_Text(pDX, IDC_EDIT_PWDNEW2, m_sPwdNew2);
}

BOOL CCambioPasswordDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;
}

void CCambioPasswordDlg::OnOK()
{
	UpdateData(TRUE);

	//

	m_sPwdOld.Trim();
	if (m_sPwdOld.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PASSWORD_VECCHIA_VUOTA));
		GetDlgItem(IDC_EDIT_PWDOLD)->SetFocus();
		return;
	}

	//

	m_sPwdNew1.Trim();
	if (m_sPwdNew1.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PASSWORD_NUOVA1_VUOTA));
		GetDlgItem(IDC_EDIT_PWDNEW1)->SetFocus();
		return;
	}

	//

	m_sPwdNew2.Trim();
	if (m_sPwdNew2.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PASSWORD_NUOVA2_VUOTA));
		GetDlgItem(IDC_EDIT_PWDNEW2)->SetFocus();
		return;
	}

	//

	if (m_sPwdOld != theApp.m_sPdfEliminazionePassword)
	{
		m_sPwdOld = "";
		UpdateData(FALSE);

		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PASSWORD_VECCHIA_ERRATA));
		GetDlgItem(IDC_EDIT_PWDOLD)->SetFocus();
		return;
	}

	//

	if (m_sPwdNew1 != m_sPwdNew2)
	{
		m_sPwdNew1 = "";
		m_sPwdNew2 = "";
		UpdateData(FALSE);

		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PASSWORD_NUOVE_DIVERSE));
		GetDlgItem(IDC_EDIT_PWDNEW1)->SetFocus();
		return;
	}

	//

	if (m_sPwdNew1.GetLength() < 8)
	{
		m_sPwdNew1 = "";
		m_sPwdNew2 = "";
		UpdateData(FALSE);

		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PASSWORD_NUOVA_TROPPOCORTA));
		GetDlgItem(IDC_EDIT_PWDNEW1)->SetFocus();
		return;
	}

	//


}
