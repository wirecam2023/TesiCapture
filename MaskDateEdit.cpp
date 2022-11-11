#include "stdafx.h"
#include "Endox.h"
#include "MaskDateEdit.h"

#include "DateDlg.h"
#include "EsamiView.h"
#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMaskDateEdit::CMaskDateEdit()
	: CMaskEdit()
{
	m_pEsamiView = NULL;
	m_pParentView = NULL;
}

CMaskDateEdit::~CMaskDateEdit()
{
}

BEGIN_MESSAGE_MAP(CMaskDateEdit, CMaskEdit)
	ON_WM_LBUTTONDOWN()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

void CMaskDateEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_pEsamiView != NULL)
	{
		int nProgramMode = theApp.m_nProgramMode;

		if ((nProgramMode & FILTER_RECORD_ESAMI))
			OpenDialog();
		else
			CMaskEdit::OnLButtonDown(nFlags, point);
	}
}

void CMaskDateEdit::OnKillFocus(CWnd* pNewWnd)
{
	CMaskEdit::OnKillFocus(pNewWnd);

	if (pNewWnd && m_pEsamiView && !theApp.m_bLoadingInterface && (GetWindowLong(GetSafeHwnd(), GWL_STYLE) & ES_READONLY) == 0 && (theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI) == 0 && (theApp.m_nProgramMode & FILTER_RECORD_ESAMI) == 0)
	{
		CString strDateTime;
		GetWindowText(strDateTime);
		if (!strDateTime.IsEmpty() && strDateTime != GetDefault() && ConvertMaskString2Date(strDateTime) == 0)
		{
			CString strError;
			strError.Format(theApp.GetMessageString(IDS_ERROR_DATE_FORMAT), m_strTitle);
			theApp.AfxMessageBoxEndo(strError, MB_ICONSTOP);

			if (::IsWindowVisible(GetSafeHwnd()))
				SetFocus();
			else
				SetWindowText(GetDefault());
		}
	}
}

BOOL CMaskDateEdit::OpenDialog()
{
	if (m_pParentView != NULL)
		m_pParentView->UpdateData(TRUE);

	CDateDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_strRicerca = dlg.m_strRicerca;
		m_strRicercaView = dlg.m_strRicercaView;

		if (m_pParentView != NULL)
			m_pParentView->UpdateData(FALSE);
	}
	
	return TRUE;
}

void CMaskDateEdit::SetParam(CWnd* pParentView, CEsamiView* pEsamiView, CString strTitle)
{
	ASSERT(pParentView != NULL);
	ASSERT(pEsamiView != NULL);
	ASSERT(!strTitle.IsEmpty());

	m_pParentView = pParentView;
	m_pEsamiView = pEsamiView;
	m_strTitle = strTitle;
}