#include "stdafx.h"
#include "Endox.h"
#include "ExtDiagnosiICD9Edit.h"

#include "EsamiView.h"
#include "MenuDiagnosiICD9Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CExtDiagnosiICD9Edit, CEdit)

CExtDiagnosiICD9Edit::CExtDiagnosiICD9Edit()
: CEdit()
{
	m_strRicerca = "";
	m_strRicercaView = "";

	//

	m_pIdEsame = NULL;
	m_pParentView = NULL;	
}

CExtDiagnosiICD9Edit::~CExtDiagnosiICD9Edit()
{
}

BEGIN_MESSAGE_MAP(CExtDiagnosiICD9Edit, CEdit)
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


void CExtDiagnosiICD9Edit::SetParam(CWnd* pParentForm, long* pIdEsame, long* pIdDiagnosi)
{
	m_pParentView = pParentForm;	
	m_pIdEsame = pIdEsame;
	m_pIdDiagnosi = pIdDiagnosi;
}

BOOL CExtDiagnosiICD9Edit::OpenDialog(BOOL bUpdate, CString strValue)
{
	BOOL bOpened = FALSE;
	BOOL bIsOK = FALSE;

	if (bUpdate && m_pParentView)
		m_pParentView->UpdateData(TRUE);

	if (strValue.IsEmpty())
		GetWindowText(strValue);

	bOpened = OpenComboMenu(bIsOK, strValue);
	if (bOpened && bIsOK)
	{
		if (m_pParentView)
		{
			WPARAM wParam = MAKEWPARAM(GetDlgCtrlID(), EN_CHANGE);

			m_pParentView->UpdateData(FALSE);
			m_pParentView->PostMessage(WM_COMMAND, (WPARAM)wParam, (LPARAM)GetSafeHwnd());
		}
	}

	return bOpened;
}

BOOL CExtDiagnosiICD9Edit::OpenComboMenu(BOOL& bIsOK, CString strValue)
{
	BOOL bResult = FALSE;

	CRect rect;
	GetWindowRect(&rect);

	CMenuDiagnosiICD9Dlg dlg(this, *m_pIdDiagnosi, strValue, theApp.m_nProgramMode, rect, &m_strRicerca, &m_strRicercaView);

	switch (dlg.DoModal())
	{
		case IDOK:		

			*m_pIdDiagnosi = dlg.m_lContatore;

			bIsOK = TRUE;
			bResult = TRUE;
			break;

		case IDCANCEL:
			bIsOK = FALSE;
			bResult = TRUE;
			break;

		case IDC_EXIT:
			bIsOK = FALSE;
			bResult = FALSE;
			break;

	}

	return bResult;
}

void CExtDiagnosiICD9Edit::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (((GetWindowLong(GetSafeHwnd(), GWL_STYLE) & ES_READONLY) != 0))
		CEdit::OnLButtonDown(nFlags, point);
	else
		OpenDialog();
}

void CExtDiagnosiICD9Edit::OnRButtonDown(UINT nFlags, CPoint point)
{
}

void CExtDiagnosiICD9Edit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar != 9) // TAB
	{
		CString strValue = "";
		DWORD dwStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);

		if (nChar >= 32 && nChar <= 255)
			strValue = CString((char)nChar, nRepCnt);

		if (((dwStyle & ES_READONLY) != 0) || (!OpenDialog(TRUE, strValue)))
			CEdit::OnChar(nChar, nRepCnt, nFlags);
		
	}
	else
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
}

void CExtDiagnosiICD9Edit::OpenDialog()
{
	CString str;
	GetWindowText(str);
	OpenDialog(TRUE, str);
}