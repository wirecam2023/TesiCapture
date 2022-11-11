#include "stdafx.h"
#include "Endox.h"
#include "ExtStrumentiEdit.h"

#include "EsamiView.h"
#include "MenuDlg.h"
#include "StrumentiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE (CExtStrumentiEdit, CEdit)

CExtStrumentiEdit::CExtStrumentiEdit()
	:CEdit()
{
	m_pParentView	= NULL;
	m_pSet			= NULL;
	m_pIdEsame		= NULL;
	m_pStrOutput	= NULL;
	m_pNumOutput	= NULL;
	m_nMaxLen		= 0;
	m_nExtMode 		= 0;
	m_bUseComboEdit = FALSE;
	m_pStrEdit		= NULL;

    m_bOrderByString= TRUE;
	m_bMoreFields	= FALSE;
}

CExtStrumentiEdit::~CExtStrumentiEdit()
{
}

BEGIN_MESSAGE_MAP(CExtStrumentiEdit, CEdit)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

void CExtStrumentiEdit::SetParam(CWnd* pParentForm, CBaseSet* pSet, long* pIdEsame, CString* pStrParent, int nMaxLen)
{
	m_pParentView = pParentForm;
	m_pSet		  = pSet;
	m_pIdEsame	  = pIdEsame;	
	m_pStrOutput  = pStrParent;
	m_pNumOutput  = NULL;
	m_nMaxLen	  = nMaxLen;
	m_pStrEdit    = NULL;

	LimitText(m_nMaxLen);
}

void CExtStrumentiEdit::SetParam(BOOL bMoreFields, BOOL bOrderByString, BOOL bUseCombo)
{
    m_bOrderByString= bOrderByString;
	m_bMoreFields	= bMoreFields;
	m_bUseComboEdit = bUseCombo;

	m_nExtMode = 0L;

	long nVal = ::GetWindowLong(GetSafeHwnd(), GWL_STYLE);
	nVal &= (~ES_LOWERCASE);
	nVal &= (~ES_UPPERCASE);
	::SetWindowLong(GetSafeHwnd(), GWL_STYLE, nVal|m_nExtMode);

	LimitText(m_nMaxLen);
}

BOOL CExtStrumentiEdit::OpenDialog(BOOL bUpdate, CString strValue)
{
	BOOL	bOpened;
	BOOL	bIsOK;

	if (bUpdate)
		if (m_pParentView)
			m_pParentView->UpdateData(TRUE);
	
	if (strValue.IsEmpty())
		GetWindowText(strValue);

	bOpened = OpenStrumentiMenu(bIsOK, strValue);

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

BOOL CExtStrumentiEdit::OpenStrumentiMenu(BOOL& bIsOK, CString strValue)
{
	BOOL bResult;
	UINT nResult;

	CRect rect;
	GetWindowRect(&rect);

	CMenuDlg dlg(this, -1 /* STRUMENTI */, m_pSet, m_pStrOutput, m_pNumOutput, &m_strRicerca, &m_strRicercaView, m_bMoreFields, FALSE, m_bOrderByString, strValue, theApp.m_nProgramMode, rect);
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
// CExtStrumentiEdit message handlers

void CExtStrumentiEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	DWORD dwStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);

	if (((dwStyle & ES_READONLY) != 0) || !m_bUseComboEdit || !OpenDialog(TRUE, ""))
		CEdit::OnLButtonDown(nFlags, point);
}

void CExtStrumentiEdit::OnRButtonDown(UINT nFlags, CPoint point)
{
}

void CExtStrumentiEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
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

void CExtStrumentiEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}