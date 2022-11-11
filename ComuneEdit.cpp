#include "stdafx.h"
#include "Endox.h"
#include "ComuneEdit.h"

#include "ComuneUseDlg.h"
#include "EsamiView.h"
#include "PazientiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CComuneEdit::CComuneEdit()
	: CEdit()
{
	m_pEsamiView = NULL;
}

BEGIN_MESSAGE_MAP(CComuneEdit, CEdit)
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

void CComuneEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CEdit::OnChar(nChar, nRepCnt, nFlags);

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
}

void CComuneEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	CEdit::OnLButtonDown(nFlags, point);

	VERIFY(m_pEsamiView);

	DWORD dwStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);

	if ((dwStyle & ES_READONLY) == 0)
		OpenDialog();
}

void CComuneEdit::OnRButtonDown(UINT nFlags, CPoint point)
{
	CEdit::OnRButtonDown(nFlags, point);
}

void CComuneEdit::OpenDialog()
{
	CString strTemp;
	CComuneUseDlg dlg(this, m_pEsamiView);

	dlg.SetIDComune(*m_pCampoComune);

	if (dlg.DoModal() == IDOK)
	{
		m_pComuneEdit->SetWindowText(dlg.GetComune());
		if (m_pCAPEdit != NULL)
			m_pCAPEdit->SetWindowText(dlg.GetCAP());
		if (m_pProvinciaEdit != NULL)
			m_pProvinciaEdit->SetWindowText(dlg.GetProvincia());

		*m_pCampoComune = dlg.GetIDComune();
		m_pEsamiView->m_PazTempSet.SetFieldNull(m_pCampoComune, FALSE);
	}
}

void CComuneEdit::SetParam(CEsamiView* pEsamiView, long* pCampoComune, CWnd* pComuneEdit, CWnd* pCAPEdit, CWnd* pProvinciaEdit)
{
	ASSERT(pEsamiView != NULL);
	ASSERT(pCampoComune != NULL);
	ASSERT(pComuneEdit != NULL);
	// ASSERT(pProvinciaEdit != NULL);

	m_pEsamiView = pEsamiView;
	m_pCampoComune = pCampoComune;
	m_pComuneEdit = pComuneEdit;
	m_pCAPEdit = pCAPEdit;
	m_pProvinciaEdit = pProvinciaEdit;
}
