#include "stdafx.h"
#include "Endox.h"
#include "OrganoDiagnosiEdit.h"
#include "OrganiSediDiagnosiUseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

COrganoDiagnosiEdit::COrganoDiagnosiEdit()
	: CEdit()
{
	m_pEsamiView = NULL;
}

BEGIN_MESSAGE_MAP(COrganoDiagnosiEdit, CEdit)
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

void COrganoDiagnosiEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// VERIFY(m_pEsamiView);

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

void COrganoDiagnosiEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	// VERIFY(m_pEsamiView);

	DWORD dwStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);

	if ((dwStyle & ES_READONLY) == 0)
		OpenDialog();
}

void COrganoDiagnosiEdit::OnRButtonDown(UINT nFlags, CPoint point)
{
}

void COrganoDiagnosiEdit::OpenDialog()
{
	CString strTemp;
	COrganiSediDiagnosiUseDlg dlg(this, m_pEsamiView);

	m_pOrganoEdit->GetWindowText(strTemp);
	dlg.SetOrgano(strTemp);
	m_pSedeEdit->GetWindowText(strTemp);
	dlg.SetSede(strTemp);
	m_pDiagnosiEdit->GetWindowText(strTemp);
	int position = strTemp.Find(",");
	if (position > 0)
		dlg.SetDiagnosi(strTemp.Left(position));
	else
		dlg.SetDiagnosi(strTemp);

	if (dlg.DoModal() == IDOK)
	{
		m_pOrganoEdit->SetWindowText(dlg.GetOrgano());
		m_pSedeEdit->SetWindowText(dlg.GetSede());
		m_pDiagnosiEdit->SetWindowText(dlg.GetDiagnosi());
	}
}

void COrganoDiagnosiEdit::SetParam(CEsamiView* pEsamiView, CWnd* pOrganoEdit, CWnd* pSedeEdit, CWnd* pDiagnosiEdit)
{
	// ASSERT(pEsamiView != NULL);
	ASSERT(pOrganoEdit != NULL);
	ASSERT(pSedeEdit != NULL);
	ASSERT(pDiagnosiEdit != NULL);

	m_pEsamiView = pEsamiView;
	m_pOrganoEdit = pOrganoEdit;
	m_pSedeEdit = pSedeEdit;
	m_pDiagnosiEdit = pDiagnosiEdit;
}
