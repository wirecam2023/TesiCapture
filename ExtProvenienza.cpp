#include "stdafx.h"
#include "Endox.h"
#include "ExtProvenienza.h"

#include "Define.h"
#include "EsamiSet.h"
#include "ProvenienzaDlg.h"
#include "ProvenienzaSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CExtProvenienza, CEdit)

CExtProvenienza::CExtProvenienza()
:CEdit()
{
	m_pParentView = NULL;
	m_pEsamiView = NULL;
	m_pSet = NULL;
}

CExtProvenienza::~CExtProvenienza()
{
}

BEGIN_MESSAGE_MAP(CExtProvenienza, CEdit)
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()

void CExtProvenienza::SetParam(CWnd* pParentForm, CBaseSet* pSet)
{
	m_pParentView = pParentForm;
	m_pSet = pSet;
}

BOOL CExtProvenienza::OpenDialog(BOOL bUpdate, CString strValue)
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

BOOL CExtProvenienza::OpenComboMenu(BOOL& bIsOK, CString strValue)
{
	BOOL bResult = FALSE;
	UINT nResult = 0;

	m_strRicerca = "";
	m_strRicercaView = "";

	CProvenienzaDlg dlg(this, TRUE);

	nResult = dlg.DoModal();

	switch (nResult)
	{
		case IDOK:
		{
			bIsOK = TRUE;
			bResult = TRUE;

			POSITION pos = dlg.m_idProvenienzaList.GetHeadPosition();
			while (pos)
			{
				int id = dlg.m_idProvenienzaList.GetNext(pos);

				CString desc = CProvenienzaSet().GetDescrizione(id);
				
				if (m_strRicerca == "")
				{
					m_strRicerca.Format("%li", id);
					m_strRicercaView.Format("%s", desc);
				}
				else
				{
					m_strRicerca.AppendFormat(" OR %li", id);
					m_strRicercaView.AppendFormat(" OR %s", desc);
				}

			}

			break;
		}
		case IDCANCEL:
			bIsOK = FALSE;
			bResult = TRUE;
			break;

		case IDC_EXIT:
			bIsOK = FALSE;
			bResult = FALSE;
			break;

	}

	return bResult;
}

/////////////////////////////////////////////////////////////////////////////
// CExtInviante message handlers

void CExtProvenienza::OnLButtonDown(UINT nFlags, CPoint point)
{
	DWORD dwStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);

	if (((dwStyle & ES_READONLY) != 0) || (!OpenDialog(TRUE, "")))
		CEdit::OnLButtonDown(nFlags, point);
}

void CExtProvenienza::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
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