#include "stdafx.h"
#include "Endox.h"
#include "LicenseDlg.h"
#include "TesiImagingActivate\TesiImagingGenuineSoftware.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const UINT CLicenseDlg::m_idEdit[8] = { IDC_EDIT_CODE_1, IDC_EDIT_CODE_2, IDC_EDIT_CODE_3, IDC_EDIT_CODE_4, IDC_EDIT_CODE_5, IDC_EDIT_CODE_6, IDC_EDIT_CODE_7, IDC_EDIT_CODE_8 };

IMPLEMENT_DYNAMIC(CLicenseDlg, CDialog)

CLicenseDlg::CLicenseDlg(ULONGLONG lActivationsToCheck, CWnd* pParentWnd)
	: CDialog(CLicenseDlg::IDD, pParentWnd)
{
	m_lActivationsToCheck = lActivationsToCheck;
	m_strStation = "";
}

CLicenseDlg::~CLicenseDlg()
{
	//
}

void CLicenseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_4, m_ctrlStatic4);
	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);
	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);

	DDX_Text(pDX, IDC_EDIT1, m_strStation);
	
	for(int i = 0; i < _countof(m_idEdit); i++)
	{
		DDX_Control(pDX, m_idEdit[i], m_ctrlEdit[i]);
		DDX_Text(pDX, m_idEdit[i], m_strActivation[i]);
	}
}

BEGIN_MESSAGE_MAP(CLicenseDlg, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CLicenseDlg message handlers

BOOL CLicenseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_STATIC_1)->SetFont(&theApp.m_fontBig);
	GetDlgItem(IDC_STATIC_2)->SetFont(&theApp.m_fontBig);
	GetDlgItem(IDC_STATIC_4)->SetFont(&theApp.m_fontBig);

	GetDlgItem(IDC_EDIT1)->SetFont(&theApp.m_fontBig);

	for(int i = 0; i < _countof(m_idEdit); i++)
	{
		m_ctrlEdit[i].SetFont(&theApp.m_fontBig);
		m_ctrlEdit[i].ModifyStyle(0, ES_UPPERCASE);
		m_ctrlEdit[i].SetLimitText(4);
		
		if (i < _countof(m_idEdit) - 1)
			m_ctrlEdit[i].SetNextEdit(&m_ctrlEdit[i + 1]);
		if (i > 0)
			m_ctrlEdit[i].SetPrevEdit(&m_ctrlEdit[i - 1]);
	}

	theApp.LocalizeDialog(this, CLicenseDlg::IDD, "LicenseDlg");
	return FALSE;
}

HBRUSH CLicenseDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor (pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_1:
		case IDC_STATIC_4:
		case IDC_EDIT1:
		{
			pDC->SetTextColor(theApp.m_color[0]);
			break;
		}

		case IDC_STATIC_2:
		case IDC_EDIT_CODE_1:
		case IDC_EDIT_CODE_2:
		case IDC_EDIT_CODE_3:
		case IDC_EDIT_CODE_4:
		case IDC_EDIT_CODE_5:
		case IDC_EDIT_CODE_6:
		case IDC_EDIT_CODE_7:
		case IDC_EDIT_CODE_8:
		{
			pDC->SetTextColor(theApp.m_color[2]);
			break;
		}
	}

	return hBrush;
}

void CLicenseDlg::OnOK()
{
	UpdateData(TRUE);

	TCHAR szActivation[_ACTIVATION_CODE_LENGTH];
	ZeroMemory(szActivation, sizeof(TCHAR) * _ACTIVATION_CODE_LENGTH);

	for(int i = 0; i < _countof(m_idEdit); i++)
	{
		CString str;
		m_ctrlEdit[i].GetWindowText(str);
		strcat_s(szActivation, str.Left(4));

		if (i < _countof(m_idEdit) - 1)
			strcat_s(szActivation, "-");
	}
	
	if (CTesiImagingGenuineSoftware::Get()->SetActivationCode("ENDOX", szActivation, m_lActivationsToCheck, &theApp.m_dbEndox))
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_LICENSE_ERROR_2), MB_ICONINFORMATION);
		CDialog::OnOK();
	}
	else
	{
		for(int i = 0; i < _countof(m_idEdit); i++)
			m_strActivation[i].Empty();
		UpdateData(FALSE);

		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_LICENSE_ERROR_3), MB_ICONSTOP);

		m_ctrlEdit[0].SetFocus();
	}
}

INT_PTR CLicenseDlg::DoModal()
{
	INT_PTR nReturn = -1;

	TCHAR szStation[_COMPUTER_CODE_LENGTH];
	if (CTesiImagingGenuineSoftware::Get()->GetComputerCode(szStation))
	{
		m_strStation = szStation;
		nReturn = CDialog::DoModal();
	}
	else
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_LICENSE_ERROR_1), MB_ICONSTOP);

	return nReturn;
}

//
//
//

CLicenseDlg::CLicenseEdit::CLicenseEdit()
{
	m_pPrevEdit = NULL;
	m_pNextEdit = NULL;
}

BEGIN_MESSAGE_MAP(CLicenseDlg::CLicenseEdit, CEdit)
	ON_MESSAGE(WM_PASTE, OnMessagePaste)
	ON_WM_CHAR()
END_MESSAGE_MAP()

LRESULT CLicenseDlg::CLicenseEdit::OnMessagePaste(WPARAM wParam, LPARAM lParam)
{
	if (!IsClipboardFormatAvailable(CF_TEXT)) 
        return 0; 

	if (!OpenClipboard())
        return 0;
 
    HANDLE hglb = GetClipboardData(CF_TEXT); 
    if (hglb != NULL) 
    { 
        if (LPCTSTR lptstr = (LPCTSTR)GlobalLock(hglb)) 
        { 
			if (m_pPrevEdit == NULL)
			{
				CString str(lptstr);
				str.Replace("-", "");
				str.Replace("\r\n", "");
				str.Replace("\n", "");
				str.Trim();

				if (str.GetLength() >= 32)
				{
					CLicenseEdit* pEdit = this;
					for(int i = 0; i < str.GetLength() && pEdit; i = i + 4)
					{
						pEdit->SetWindowText(str.Mid(i, 4));
						pEdit = pEdit->GetNextEdit();
					}
				}
			}

            GlobalUnlock(hglb); 
        } 
    } 

    CloseClipboard(); 
	return 0;
}

void CLicenseDlg::CLicenseEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CEdit::OnChar(nChar, nRepCnt, nFlags);

	CString strText;
	GetWindowText(strText);

	if (strText.GetLength() == GetLimitText())
	{
		if (m_pNextEdit && nChar != VK_BACK)
		{
			m_pNextEdit->SetFocus();

			CString strNext;
			m_pNextEdit->GetWindowText(strNext);
			m_pNextEdit->SetSel(strNext.GetLength(), strNext.GetLength());
		}
	}

	if (m_pPrevEdit && nChar == VK_BACK && strText.GetLength() == 0)
	{
		m_pPrevEdit->SetFocus();

		CString strPrev;
		m_pPrevEdit->GetWindowText(strPrev);
		m_pPrevEdit->SetSel(strPrev.GetLength(), strPrev.GetLength());
	}
}

void CLicenseDlg::CLicenseEdit::SetNextEdit(CLicenseEdit* pNextEdit)
{
	m_pNextEdit = pNextEdit;
}

void CLicenseDlg::CLicenseEdit::SetPrevEdit(CLicenseEdit* pPrevEdit)
{
	m_pPrevEdit = pPrevEdit;
}