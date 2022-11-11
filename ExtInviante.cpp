#include "stdafx.h"
#include "Endox.h"
#include "ExtInviante.h"

#include "Define.h"
#include "InviantiDlg.h"
#include "OperatoriDlg.h"
#include "EsamiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE (CExtInviante, CEdit)

CExtInviante::CExtInviante()
	:CEdit()
{
	m_pParentView = NULL;
	m_pEsamiView = NULL;
	m_pSet = NULL;
	m_pInviante = NULL;
}

CExtInviante::~CExtInviante()
{
}

BEGIN_MESSAGE_MAP(CExtInviante, CEdit)
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()

void CExtInviante::SetParam(CWnd* pParentForm, CBaseSet* pSet, long* pInviante)
{
	m_pParentView = pParentForm;
	m_pSet = pSet;
	m_pInviante = pInviante;
}

BOOL CExtInviante::OpenDialog(BOOL bUpdate, CString strValue)
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

BOOL CExtInviante::OpenComboMenu(BOOL& bIsOK, CString strValue)
{
	BOOL bResult;
	UINT nResult;

	CInviantiDlg dlg(m_pEsamiView, ((CEsamiSet*)m_pSet)->m_lProvenienza == 1 ? BOOL_ESTERNI : BOOL_INTERNI, BOOL_NOTMENU);

	nResult = dlg.DoModal();

	switch (nResult)
	{
		case IDOK:
			bIsOK	= TRUE;
			bResult = TRUE;

			if (m_pInviante)
				*m_pInviante = dlg.m_lCode;

			m_strRicerca = dlg.m_strRicerca;
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

/////////////////////////////////////////////////////////////////////////////
// CExtInviante message handlers

void CExtInviante::OnLButtonDown(UINT nFlags, CPoint point)
{
	DWORD dwStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);

	if (((dwStyle & ES_READONLY) != 0) || (!OpenDialog(TRUE, "")))
		CEdit::OnLButtonDown(nFlags, point);
}

void CExtInviante::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar != 9) //TAB
	{
		CString strValue = "";
		DWORD dwStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);

		//if (m_pParentView)
			//m_pParentView->UpdateData(TRUE);

		if (nChar >= 32 && nChar <= 255)
			strValue = CString((char)nChar, nRepCnt);

		/*
		if (m_nExtMode == ES_LOWERCASE)
			strValue.MakeLower();
		
		if (m_nExtMode == ES_UPPERCASE)
			strValue.MakeUpper();
		*/

		if (((dwStyle & ES_READONLY) != 0) || (!OpenDialog(TRUE, strValue)))
			CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	else
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
}