#include "stdafx.h"
#include "Endox.h"
#include "FrasiNewEdit.h"

// #include "EsamiView.h"
#include "FrasiNewUseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CFrasiNewEdit, CEdit)

CFrasiNewEdit::CFrasiNewEdit()
{
	m_pParentView = NULL;
	m_lPrePost = -1;
}

CFrasiNewEdit::~CFrasiNewEdit()
{
}

BEGIN_MESSAGE_MAP(CFrasiNewEdit, CEdit)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()

void CFrasiNewEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	DWORD dwStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);

	CEdit::OnLButtonDown(nFlags, point);

	if ((dwStyle & ES_READONLY) == 0)
		OpenDialog();
}

void CFrasiNewEdit::OnRButtonDown(UINT nFlags, CPoint point)
{
}

void CFrasiNewEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CFrasiNewEdit::OpenDialog()
{
	ASSERT(m_pParentView != NULL);

	m_pParentView->UpdateData(TRUE);

	CString strValue;
	GetWindowText(strValue);

	CFrasiNewUseDlg dlg(this, m_strTitolo, m_lPrePost, strValue);
	if (dlg.DoModal() == IDOK)
		SetWindowText(dlg.GetValue());

	UpdateData(TRUE);
	m_pParentView->PostMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), EN_CHANGE), (LPARAM)GetSafeHwnd());

	SetFocus();
}

void CFrasiNewEdit::SetParam(CWnd* pParentView, CString strTitolo, long lPrePost)
{
	ASSERT(pParentView != NULL);

	m_pParentView = pParentView;
	m_strTitolo = strTitolo;
	m_lPrePost = lPrePost;
}