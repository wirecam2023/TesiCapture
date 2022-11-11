#include "stdafx.h"
#include "Endox.h"
#include "ExtOrganoSede.h"

#include "OrganiSediDlg.h"
#include "BaseSet.h"
#include "Define.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE (CExtOrganoSede, CEdit)

CExtOrganoSede::CExtOrganoSede()
	:CEdit()
{
	m_pParentView	= NULL;
	m_pEsamiView	= NULL;
	m_pSediSet		= NULL;
	m_pSet			= NULL;
	m_pStrOutput	= NULL;
	m_pStrOther[0]  = NULL;
	m_pStrOther[1]  = NULL;
	//m_nMaxLen		= 0;
	m_nExtMode 		= 0;
	m_strTitle		= "";

	m_bUpdateRecord = TRUE;
}

CExtOrganoSede::~CExtOrganoSede()
{
}

BEGIN_MESSAGE_MAP(CExtOrganoSede, CEdit)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()

void CExtOrganoSede::SetParam(CWnd* pParentForm, CMstSediSet* pSediSet, CBaseSet* pSet, CString* pStrParent, CString strTitle)
{
	m_pParentView = pParentForm;
	m_pSediSet	  = pSediSet;
	m_pSet		  = pSet;
	m_pStrOutput  = pStrParent;
	m_strTitle	  = strTitle;

	//LimitText(m_nMaxLen);
}

void CExtOrganoSede::SetParam(CEsamiView* pEsamiView, CString* strSede, CString* strTelefono)
{
	m_pEsamiView	= pEsamiView;
	m_pStrOther[0]  = strSede;
	m_pStrOther[1]  = strTelefono;
}

void CExtOrganoSede::SetParam(CWnd* pParentForm, CMstSediSet* pSediSet, CBaseSet* pSet)
{
	m_pParentView = pParentForm;
	m_pSediSet = pSediSet;
	m_pSet		  = pSet;
	m_bUpdateRecord = FALSE;
}

void CExtOrganoSede::SetParam(int nIndexMode)
{
	switch (nIndexMode)
	{
		case 0: 
			m_nExtMode = ES_LOWERCASE;
			break;
		case 1: 
			m_nExtMode = ES_UPPERCASE;
			break;
		case 2: 
		default:
			m_nExtMode = 0L;
			break;
	}

	long nVal = ::GetWindowLong(GetSafeHwnd(), GWL_STYLE);
	nVal &= (~ES_LOWERCASE);
	nVal &= (~ES_UPPERCASE);
	::SetWindowLong(GetSafeHwnd(), GWL_STYLE, nVal|m_nExtMode);

	//LimitText(m_nMaxLen);
}

BOOL CExtOrganoSede::OpenDialog(BOOL bUpdate, CString strValue)
{
	BOOL	bOpened;
	BOOL	bIsOK;

	if (bUpdate)
		if (m_pParentView)
			m_pParentView->UpdateData(TRUE);
	
	if (strValue.IsEmpty())
		GetWindowText(strValue);

	if (m_pSediSet)
	{
		bOpened = OpenComboMenu(bIsOK, strValue);
	}

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

BOOL CExtOrganoSede::OpenComboMenu(BOOL& bIsOK, CString strValue)
{
	BOOL bResult;
	UINT nResult;

#define _SELECTION_MODE TRUE

	COrganiSediDlg dlg(m_pParentView, m_pEsamiView, _SELECTION_MODE);
		
	nResult = dlg.DoModal();

	switch (nResult)
	{
		case IDCANCEL:
			bIsOK	= TRUE;
			bResult = TRUE;

			m_strRicercaView = dlg.m_strRicercaView;

			if (m_pStrOutput)
			{
				*m_pStrOutput = m_strRicercaView;

				if (m_pSet->IsOpen())
					m_pSet->SetFieldNull(m_pStrOutput, FALSE);
			}

			break;

		case IDC_EXIT:
			bIsOK	= FALSE;
			bResult = FALSE;
			break;

	}

	return bResult;
}

/////////////////////////////////////////////////////////////////////////////
// CExtMedicoCurante message handlers

void CExtOrganoSede::OnLButtonDown(UINT nFlags, CPoint point)
{
	DWORD dwStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);

	if (((dwStyle & ES_READONLY) != 0) || (!OpenDialog(TRUE, "")))
		CEdit::OnLButtonDown(nFlags, point);
}

void CExtOrganoSede::OnRButtonDown(UINT nFlags, CPoint point)
{
}

void CExtOrganoSede::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	/*if (nChar != 9) //TAB
	{
		CString strValue = "";
		DWORD dwStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);

		if (nChar >= 32 && nChar <= 255)
			strValue = CString((char)nChar, nRepCnt);

		if (m_nExtMode == ES_LOWERCASE)
			strValue.MakeLower();
		
		if (m_nExtMode == ES_UPPERCASE)
			strValue.MakeUpper();

		if (((dwStyle & ES_READONLY) != 0) || (!OpenDialog(TRUE, strValue)))
			CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	else
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}*/
}