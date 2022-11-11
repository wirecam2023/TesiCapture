#include "stdafx.h"
#include "Endox.h"
#include "ExtTerapia.h"

#include "TerapiaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE (CExtTerapia, CEdit)

CExtTerapia::CExtTerapia()
	:CEdit()
{
	m_pParentView	= NULL;
	m_pSet			= NULL;
	m_pIdEsame		= NULL;
	m_pStrOutput	= NULL;
	m_nMaxLen		= 0;
	m_nExtMode 		= 0;
	m_bUseComboEdit = FALSE;
}

CExtTerapia::~CExtTerapia()
{
}

BEGIN_MESSAGE_MAP(CExtTerapia, CEdit)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()

void CExtTerapia::SetParam(CWnd* pParentForm, CBaseSet* pSet, long* pIdEsame, CString* pStrParent, int nMaxLen)
{
	m_pParentView = pParentForm;
	m_pSet		  = pSet;
	m_pIdEsame	  = pIdEsame;	
	m_pStrOutput  = pStrParent;
	m_nMaxLen	  = nMaxLen;

	LimitText(m_nMaxLen);
}

void CExtTerapia::SetParam(BOOL bUseCombo, int nIndexMode)
{
	m_bUseComboEdit = bUseCombo;

	switch (nIndexMode)
	{
		case 0: 
			m_nExtMode = ES_LOWERCASE;
			break;
		case 1: 
			m_nExtMode = ES_UPPERCASE;
			break;
		case 2: 
		default:
			m_nExtMode = 0L;
			break;
	}

	long nVal = ::GetWindowLong(GetSafeHwnd(), GWL_STYLE);
	nVal &= (~ES_LOWERCASE);
	nVal &= (~ES_UPPERCASE);
	::SetWindowLong(GetSafeHwnd(), GWL_STYLE, nVal|m_nExtMode);

	LimitText(m_nMaxLen);
}

BOOL CExtTerapia::OpenDialog(BOOL bUpdate, CString strValue)
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

BOOL CExtTerapia::OpenComboMenu(BOOL& bIsOK, CString strValue)
{
	BOOL bResult;
	UINT nResult;

	CTerapiaDlg dlg(this, m_pSet, m_pStrOutput, strValue);
		
	nResult = dlg.DoModal();

	switch (nResult)
	{
		case IDOK:
			bIsOK	= TRUE;
			bResult = TRUE;
			break;

		case IDCANCEL:
			bIsOK	= FALSE;
			bResult = TRUE;
			break;

		case IDC_EXIT:
			bIsOK	= FALSE;
			bResult = FALSE;
			break;

	}

	return bResult;
}

/////////////////////////////////////////////////////////////////////////////
// CExtTerapia message handlers

void CExtTerapia::OnLButtonDown(UINT nFlags, CPoint point)
{
	DWORD dwStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);

	if (((dwStyle & ES_READONLY) != 0) || (!m_bUseComboEdit) || (!OpenDialog(TRUE, "")))
		CEdit::OnLButtonDown(nFlags, point);
}

void CExtTerapia::OnRButtonDown(UINT nFlags, CPoint point)
{
}

void CExtTerapia::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar != 9) //TAB
	{
		CString strValue = "";
		DWORD dwStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);

		if (nChar >= 32 && nChar <= 255)
			strValue = CString((char)nChar, nRepCnt);

		if (m_nExtMode == ES_LOWERCASE)
			strValue.MakeLower();
		
		if (m_nExtMode == ES_UPPERCASE)
			strValue.MakeUpper();

		if (((dwStyle & ES_READONLY) != 0) || (!m_bUseComboEdit) || (!OpenDialog(TRUE, strValue)))
			CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	else
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
}