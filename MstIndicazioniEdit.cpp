#include "stdafx.h"
#include "Endox.h"
#include "MstIndicazioniEdit.h"

#include "EsamiView.h"
#include "MstIndicazioniUseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMstIndicazioniEdit, CEdit)

CMstIndicazioniEdit::CMstIndicazioniEdit()
{
	m_pParentView = NULL;
	m_pEsamiView = NULL;
}

CMstIndicazioniEdit::~CMstIndicazioniEdit()
{
}

BEGIN_MESSAGE_MAP(CMstIndicazioniEdit, CEdit)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()

void CMstIndicazioniEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	DWORD dwStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);

	CEdit::OnLButtonDown(nFlags, point);

	if ((dwStyle & ES_READONLY) == 0)
		OpenDialog();
}

void CMstIndicazioniEdit::OnRButtonDown(UINT nFlags, CPoint point)
{
}

void CMstIndicazioniEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CMstIndicazioniEdit::OpenDialog()
{
	ASSERT(m_pParentView != NULL);
	ASSERT(m_pEsamiView != NULL);

	m_pParentView->UpdateData(TRUE);

	CString strValue;
	GetWindowText(strValue);

	// Sandro Gallina - 19/04/2004 // Modificato tutto //
	CMstIndicazioniUseDlg dlg(this, m_pEsamiView);
	dlg.SetValue(strValue);
	if (dlg.DoModal() == IDOK)
		SetWindowText(dlg.GetValue());

	UpdateData(TRUE);
	m_pParentView->PostMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), EN_CHANGE), (LPARAM)GetSafeHwnd());

	SetFocus();
}

void CMstIndicazioniEdit::SetParam(CWnd* pParentView, CEsamiView* pEsamiView)
{
	ASSERT(pParentView != NULL);
	ASSERT(pEsamiView != NULL);

	m_pParentView = pParentView;
	m_pEsamiView = pEsamiView;
}