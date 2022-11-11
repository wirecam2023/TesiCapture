#include "stdafx.h"
#include "Endox.h"
#include "ExtOspedale.h"

#include "BaseSet.h"
#include "Define.h"
#include "TabComboDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE (CExtOspedale, CEdit)

CExtOspedale::CExtOspedale()
	:CEdit()
{
	m_nMaxLen = 0;

	m_lExtMode = 0;

	m_plOutput = NULL;
	m_pParentView = NULL;
}

CExtOspedale::~CExtOspedale()
{
}

BEGIN_MESSAGE_MAP(CExtOspedale, CEdit)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()

void CExtOspedale::SetParam(CWnd* pParentForm, long* plParent, int nMaxLen)
{
	m_pParentView = pParentForm;
	m_plOutput = plParent;
	m_nMaxLen = nMaxLen;

	LimitText(m_nMaxLen);
}

void CExtOspedale::SetParam(int nIndexMode)
{
	switch (nIndexMode)
	{
		case 0: 
			m_lExtMode = ES_LOWERCASE;
			break;
		case 1: 
			m_lExtMode = ES_UPPERCASE;
			break;
		case 2: 
		default:
			m_lExtMode = 0L;
			break;
	}

	long nVal = ::GetWindowLong(GetSafeHwnd(), GWL_STYLE);
	nVal &= (~ES_LOWERCASE);
	nVal &= (~ES_UPPERCASE);
	::SetWindowLong(GetSafeHwnd(), GWL_STYLE, nVal|m_lExtMode);

	LimitText(m_nMaxLen);
}

BOOL CExtOspedale::OpenDialog(BOOL bUpdate, CString strValue)
{
	BOOL	bOpened;
	BOOL	bIsOK;

	if (bUpdate)
		if (m_pParentView)
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

	SetFocus();

	return bOpened;
}

BOOL CExtOspedale::OpenComboMenu(BOOL& bIsOK, CString strValue)
{
	BOOL bResult;

	CTabComboDlg dlg(this, BOOL_NOTMENU);
	switch(dlg.DoModal())
	{
		case IDOK:
		case IDCANCEL:
			bIsOK	= TRUE;
			bResult = TRUE;
			*m_plOutput = dlg.m_lSelected;
			break;

		case IDC_EXIT:
			bIsOK	= FALSE;
			bResult = FALSE;
			break;

	}

	return bResult;
}

void CExtOspedale::OnLButtonDown(UINT nFlags, CPoint point)
{
	DWORD dwStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);

	if (((dwStyle & ES_READONLY) != 0) || (!OpenDialog(TRUE, "")))
		CEdit::OnLButtonDown(nFlags, point);
}

void CExtOspedale::OnRButtonDown(UINT nFlags, CPoint point)
{
}

void CExtOspedale::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar != 9) //TAB
	{
		CString strValue = "";
		DWORD dwStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);

		if (nChar >= 32 && nChar <= 255)
			strValue = CString((char)nChar, nRepCnt);

		if (m_lExtMode == ES_LOWERCASE)
			strValue.MakeLower();
		
		if (m_lExtMode == ES_UPPERCASE)
			strValue.MakeUpper();

		if (((dwStyle & ES_READONLY) != 0) || (!OpenDialog(TRUE, strValue)))
			CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	else
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
}
