#include "stdafx.h"
#include "Endox.h"
#include "ExtFarmaci.h"
#include "ProntFarmUseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CFarmaciExtEdit::CFarmaciExtEdit()
	: CEdit()
{
	m_pEsamiView = NULL;
}

BEGIN_MESSAGE_MAP(CFarmaciExtEdit, CEdit)
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

void CFarmaciExtEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	VERIFY(m_pEsamiView);

	if (nChar != 9) //TAB
	{
		CString strValue = "";
		DWORD dwStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);

		if ((nChar >= 32) && (nChar <= 255))
			strValue = CString((char)nChar, nRepCnt);

		if ((dwStyle & ES_READONLY) == 0)
			OpenDialog();
	}
	else
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
}

void CFarmaciExtEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	CEdit::OnLButtonDown(nFlags, point);

	VERIFY(m_pEsamiView);

	DWORD dwStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);

	if ((dwStyle & ES_READONLY) == 0)
		OpenDialog();
}

void CFarmaciExtEdit::OnRButtonDown(UINT nFlags, CPoint point)
{
#ifdef _DEBUG
	CEdit::OnRButtonDown(nFlags, point);
#endif
}

void CFarmaciExtEdit::OpenDialog()
{
	CString strTemp;
	CProntFarmUseDlg dlg(this, m_pEsamiView, m_bSingleSelection);

	m_pFarmaciEdit->GetWindowText(strTemp);
	dlg.SetFarmaci(strTemp);

	if (dlg.DoModal() == IDOK)
	{
		m_pFarmaciEdit->SetWindowText(dlg.GetFarmaci());

		// provo //
		WPARAM wParam = MAKEWPARAM(GetDlgCtrlID(), EN_CHANGE);
		GetParent()->PostMessage(WM_COMMAND, (WPARAM)wParam, (LPARAM)GetSafeHwnd());
	}
}

void CFarmaciExtEdit::SetParam(CEsamiView* pEsamiView, CWnd* pFarmaciEdit, BOOL bSingleSelection)
{
	ASSERT(pEsamiView != NULL);
	ASSERT(pFarmaciEdit != NULL);

	m_pEsamiView = pEsamiView;
	m_pFarmaciEdit = pFarmaciEdit;

	m_bSingleSelection = bSingleSelection;
}