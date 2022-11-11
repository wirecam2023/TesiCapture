#include "stdafx.h"
#include "Endox.h"
#include ".\ExtEdit.h"

#include "EsamiView.h"
#include "MenuDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE (CExtEdit, CEdit)

CExtEdit::CExtEdit()
	: CEdit()
{
	m_bMoreFields = FALSE;
	m_bOrderByString = TRUE;
	m_bSameMultipleSelect = FALSE;
	m_bUppercase = FALSE;
	m_bUseComboEdit = FALSE;

	m_nMaxLen = 0;

	m_lComboDefine = -1;
	m_lContatore = 0;

	m_strRicerca = "";
	m_strRicercaView = "";

	//

	m_pSet = NULL;

	m_pIdEsame = NULL;
	m_pNumOutput = NULL;

	m_pStrEdit = NULL;
	m_pStrOutput = NULL;

	m_pParentView = NULL;
}

CExtEdit::~CExtEdit()
{
}

BEGIN_MESSAGE_MAP(CExtEdit, CEdit)
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

void CExtEdit::SetParam(CWnd* pParentForm, long lComboDefine, CBaseSet* pSet, long* pIdEsame, CString* pStrParent, int nMaxLen)
{
	m_pParentView = pParentForm;
	m_lComboDefine = lComboDefine;
	m_pSet = pSet;
	m_pIdEsame = pIdEsame;
	m_pStrOutput = pStrParent;
	m_nMaxLen = nMaxLen;

	m_pNumOutput = NULL;
	m_pStrEdit = NULL;

	LimitText(m_nMaxLen);
}

void CExtEdit::SetParam(CWnd* pParentForm, long lComboDefine, CBaseSet* pSet, long* pIdEsame, long* pNumParent, int nMaxLen)
{
	m_pParentView = pParentForm;
	m_lComboDefine = lComboDefine;
	m_pSet = pSet;
	m_pIdEsame = pIdEsame;
	m_pNumOutput = pNumParent;
	m_nMaxLen = nMaxLen;

	m_pStrOutput = NULL;
	m_pStrEdit = NULL;

	LimitText(m_nMaxLen);
}

void CExtEdit::SetParam(BOOL bMoreFields, BOOL bSameMultipleSelect, BOOL bOrderByString, BOOL bUseCombo, BOOL bUppercase)
{
	m_bMoreFields = bMoreFields;
	m_bSameMultipleSelect = bSameMultipleSelect;
	m_bOrderByString = bOrderByString;
	m_bUseComboEdit = bUseCombo;
	m_bUppercase = bUppercase;

	long nVal = ::GetWindowLong(GetSafeHwnd(), GWL_STYLE);
	nVal &= (~ES_LOWERCASE);
	
	if (bUppercase)
		nVal |= ES_UPPERCASE;
	else
		nVal &= (~ES_UPPERCASE);

	::SetWindowLong(GetSafeHwnd(), GWL_STYLE, nVal);

	LimitText(m_nMaxLen);
}

BOOL CExtEdit::OpenDialog(BOOL bUpdate, CString strValue)
{
	BOOL bOpened = FALSE;
	BOOL bIsOK = FALSE;

	if (bUpdate && m_pParentView)
		m_pParentView->UpdateData(TRUE);
	
	if (strValue.IsEmpty())
		GetWindowText(strValue);

	bOpened = OpenComboMenu(bIsOK, strValue);
	if (bOpened && bIsOK)
	{
		if (m_pParentView)
		{
			WPARAM wParam = MAKEWPARAM(GetDlgCtrlID(), EN_CHANGE);
			
			m_pParentView->UpdateData(FALSE);
			m_pParentView->PostMessage(WM_COMMAND, (WPARAM)wParam, (LPARAM)GetSafeHwnd());

			m_pParentView->PostMessageA(WM_EXTEDITCMB_CHANGED, (WPARAM)m_lComboDefine, (LPARAM)m_lContatore);
		}
	}

	return bOpened;
}

BOOL CExtEdit::OpenComboMenu(BOOL& bIsOK, CString strValue)
{
	BOOL bResult;

	CRect rect;
	GetWindowRect(&rect);

	CMenuDlg dlg(this, 
		         m_lComboDefine, 
				 m_pSet, 
				 m_pStrOutput, 
				 m_pNumOutput, 
				 &m_strRicerca, 
				 &m_strRicercaView, 
				 m_bMoreFields, 
			 	 m_bSameMultipleSelect,
				 m_bOrderByString, 
				 strValue, 
				 theApp.m_nProgramMode,
				 rect);

	switch (dlg.DoModal())
	{
		case IDOK:
			if (m_pStrOutput && m_bUppercase)
				m_pStrOutput->MakeUpper();

			m_lContatore = dlg.m_lContatore;

			bIsOK	= TRUE;
			bResult = TRUE;
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

void CExtEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (((GetWindowLong(GetSafeHwnd(), GWL_STYLE) & ES_READONLY) != 0) || !m_bUseComboEdit)
		CEdit::OnLButtonDown(nFlags, point);
	else
		OpenDialog();
}

void CExtEdit::OnRButtonDown(UINT nFlags, CPoint point)
{
}

void CExtEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar != 9) // TAB
	{
		CString strValue = "";
		DWORD dwStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);

		if (nChar >= 32 && nChar <= 255)
			strValue = CString((char)nChar, nRepCnt);

		// SendMessage(WM_NOTIFY_OPEN_DIALOG, TRUE);

		if (((dwStyle & ES_READONLY) != 0) || (!m_bUseComboEdit) || (!OpenDialog(TRUE, strValue)))
			CEdit::OnChar(nChar, nRepCnt, nFlags);

		// PostMessage(WM_NOTIFY_OPEN_DIALOG, FALSE);
	}
	else
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
}

/*
LRESULT CExtEdit::OnNotifyOpenedDialog(WPARAM wParam, LPARAM lParam)
{
	m_bOpenedDialog = wParam ? TRUE : FALSE;
	return 0;
}
*/

void CExtEdit::OpenDialog()
{
	// SendMessage(WM_NOTIFY_OPEN_DIALOG, TRUE);

	CString str;
	GetWindowText(str);
	OpenDialog(TRUE, str);

	// PostMessage(WM_NOTIFY_OPEN_DIALOG, FALSE);
}