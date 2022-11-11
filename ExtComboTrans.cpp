#include "stdafx.h"
#include "Endox.h"
#include "ExtComboTrans.h"

#include "ComboTransConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE (CExtComboTrans, CEdit)

CExtComboTrans::CExtComboTrans()
	:CEdit()
{
	m_pParentView = NULL;
	m_pEsamiView = NULL;
	m_pComboTransSet = NULL;
	m_pSet = NULL;
}

CExtComboTrans::~CExtComboTrans()
{
}

BEGIN_MESSAGE_MAP(CExtComboTrans, CEdit)
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()

void CExtComboTrans::SetParam(CWnd* pParentForm, CComboTransSet* pComboTransSet, CBaseSet* pSet, CEsamiView* pEsamiView)
{
	m_pParentView = pParentForm;
	m_pComboTransSet = pComboTransSet;
	m_pSet = pSet;
	m_pEsamiView = pEsamiView;
}

BOOL CExtComboTrans::OpenDialog(BOOL bUpdate, CString strValue)
{
	BOOL	bOpened;
	BOOL	bIsOK;

	if (bUpdate)
		if (m_pParentView)
			m_pParentView->UpdateData(TRUE);

	if (m_pComboTransSet)
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

BOOL CExtComboTrans::OpenComboMenu(BOOL& bIsOK, CString strValue)
{
	BOOL bResult = FALSE;

	CComboTransConfigDlg dlg(this, m_pEsamiView, m_pComboTransSet, "");
	int nResult = dlg.DoModal();

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

void CExtComboTrans::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar != 9) //TAB
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

void CExtComboTrans::OnLButtonDown(UINT nFlags, CPoint point)
{
	DWORD dwStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);

	if (((dwStyle & ES_READONLY) != 0) || (!OpenDialog(TRUE, "")))
		CEdit::OnLButtonDown(nFlags, point);
}