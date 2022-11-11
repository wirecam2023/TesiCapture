#include "stdafx.h"
#include "Endox.h"
#include "OrganoEdit.h"
#include "OrganiSediUseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

COrganoEdit::COrganoEdit()
	: CEdit()
{
	m_pEsamiView = NULL;
	m_lIDSede = 0;
}

BEGIN_MESSAGE_MAP(COrganoEdit, CEdit)
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

void COrganoEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
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

void COrganoEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	VERIFY(m_pEsamiView);

	DWORD dwStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);

	if ((dwStyle & ES_READONLY) == 0)
		OpenDialog();
}

void COrganoEdit::OnRButtonDown(UINT nFlags, CPoint point)
{
}

void COrganoEdit::OpenDialog()
{
	CString strTemp;
	COrganiSediUseDlg dlg(this, m_pEsamiView);

	m_pOrganoEdit->GetWindowText(strTemp);
	dlg.SetOrgano(strTemp);
	m_pSedeEdit->GetWindowText(strTemp);
	dlg.SetSede(strTemp);

	if (dlg.DoModal() == IDOK)
	{
		CString sOrgano = dlg.GetOrgano();
		CString sSede = dlg.GetSede();

		if (m_pOrganoEdit == m_pSedeEdit)
		{
			m_pOrganoEdit->SetWindowText(sOrgano + " " + sSede);
		}
		else
		{
			m_pOrganoEdit->SetWindowText(sOrgano);
			m_pSedeEdit->SetWindowText(sSede);
		}

		//Mi tengo da parte l'id della sede selezionata
		m_lIDSede = dlg.GetIdSede();

		if (m_pParent != NULL)
			m_pParent->PostMessage(MSG_EDIT_UPDATED);
	}
}

void COrganoEdit::SetParam(CEsamiView* pEsamiView, CWnd* pOrganoEdit, CWnd* pSedeEdit, CWnd* pParent)
{
	ASSERT(pEsamiView != NULL);
	ASSERT(pOrganoEdit != NULL);
	ASSERT(pSedeEdit != NULL);
	// ASSERT(pParent != NULL);

	m_pEsamiView = pEsamiView;
	m_pOrganoEdit = pOrganoEdit;
	m_pSedeEdit = pSedeEdit;
	m_pParent = pParent;
}
