#include "stdafx.h"
#include "Endox.h"
#include "ExtInfermiere.h"

#include "InfermieriDlg.h"
#include "Define.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE (CExtInfermiere, CEdit)

CExtInfermiere::CExtInfermiere()
	:CEdit()
{
	m_pParentView	 = NULL;
	m_pEsamiView	 = NULL;
	m_pSet			 = NULL;
}

CExtInfermiere::~CExtInfermiere()
{
}

BEGIN_MESSAGE_MAP(CExtInfermiere, CEdit)
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()

void CExtInfermiere::SetParam(CWnd* pParentForm, CBaseSet* pSet)
{
	m_pParentView	 = pParentForm;
	m_pSet			 = pSet;
}

BOOL CExtInfermiere::OpenDialog(BOOL bUpdate, CString strValue)
{
	BOOL	bOpened;
	BOOL	bIsOK;

	if (bUpdate)
		if (m_pParentView)
			m_pParentView->UpdateData(TRUE);

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

BOOL CExtInfermiere::OpenComboMenu(BOOL& bIsOK, CString strValue)
{
	BOOL bResult;
	UINT nResult;

	CInfermieriDlg dlg(m_pEsamiView, BOOL_NOTMENU);
		
	nResult = dlg.DoModal();

	switch (nResult)
	{
		case IDOK:
			bIsOK	= TRUE;
			bResult = TRUE;

			m_strRicerca     = dlg.m_strRicerca;
			m_strRicercaView = dlg.m_strRicercaView;
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

void CExtInfermiere::OnLButtonDown(UINT nFlags, CPoint point)
{
	DWORD dwStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);

	if (((dwStyle & ES_READONLY) != 0) || (!OpenDialog(TRUE, "")))
		CEdit::OnLButtonDown(nFlags, point);
}

void CExtInfermiere::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar != 9) //TAB
	{
		CString strValue = "";
		DWORD dwStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);

		if (nChar >= 32 && nChar <= 255)
			strValue = CString((char)nChar, nRepCnt);

		/*if (m_nExtMode == ES_LOWERCASE)
			strValue.MakeLower();
		
		if (m_nExtMode == ES_UPPERCASE)
			strValue.MakeUpper();*/

		if (((dwStyle & ES_READONLY) != 0) || (!OpenDialog(TRUE, strValue)))
			CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	else
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
}