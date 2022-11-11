#include "stdafx.h"
#include "Endox.h"
#include "ExtDateEdit.h"

#include "DateDlg.h"
#include "EsamiView.h"
#include "TimeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CExtDateEdit::CExtDateEdit()
	: CMaskDateEdit()
{
	m_pEsamiView = NULL;
	m_pParentView = NULL;
	m_iModalita = 0;
}

CExtDateEdit::~CExtDateEdit()
{
}

BEGIN_MESSAGE_MAP(CExtDateEdit, CMaskDateEdit)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

void CExtDateEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_pEsamiView != NULL)
	{
		// Sandro 06/04/2012 // quando cerco SOLO per paziente non ha senso che mi chieda un range di date (che ci perdo tempo e mi rompo le @@) //
		// if ((theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI) || (theApp.m_nProgramMode & FILTER_RECORD_ESAMI))
		if (theApp.m_nProgramMode & FILTER_RECORD_ESAMI || theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI)
			OpenDialog();
		else
			CMaskDateEdit::OnLButtonDown(nFlags, point);
	}
}

void CExtDateEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CMaskDateEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CExtDateEdit::OpenDialog()
{
	SetFocus();

	if (m_pParentView != NULL)
		m_pParentView->UpdateData(TRUE);

	if (m_iModalita == SOLO_ORA)
	{
		CTimeDlg dlg;
		if (dlg.DoModal() == IDOK)
		{
			m_strRicerca = dlg.m_strRicerca;
			m_strRicercaView = dlg.m_strRicercaView;

			if (m_pParentView != NULL)
				m_pParentView->UpdateData(FALSE);	
		}
	}
	else if (m_iModalita == DATA_ORA_FULL)
	{
		CDateDlg dlg;
		dlg.SetRicercaOutputMode(DATA_ORA_FULL);
		if (dlg.DoModal() == IDOK)
		{
			m_strRicerca = dlg.m_strRicerca;
			m_strRicercaView = dlg.m_strRicercaView;

			if (m_pParentView != NULL)
				m_pParentView->UpdateData(FALSE);
		}
	}
	else
	{
		CDateDlg dlg;
		if (dlg.DoModal() == IDOK)
		{
			m_strRicerca = dlg.m_strRicerca;
			m_strRicercaView = dlg.m_strRicercaView;

			if (m_pParentView != NULL)
				m_pParentView->UpdateData(FALSE);	
		}
	}
	
	return TRUE;
}

void CExtDateEdit::SetParam(CWnd* pParentView, CEsamiView* pEsamiView, CString strTitle, int nModalita)
{
	ASSERT(pParentView != NULL);
	ASSERT(pEsamiView != NULL);

	m_pParentView = pParentView;
	m_pEsamiView = pEsamiView;
	m_iModalita = nModalita;

	CMaskDateEdit::SetParam(pParentView, pEsamiView, strTitle);
	switch(m_iModalita)
	{
		case DATA_ORA_FULL:
		case DATA_ORA:
		{
			CMaskDateEdit::SetEditMask("00/00/0000 - 00:00", "__/__/____ - __:__");
			break;
		}
		case SOLO_DATA:
		{
			CMaskDateEdit::SetEditMask("00/00/0000", "__/__/____");
			break;
		}
		case SOLO_ORA:
		{
			CMaskDateEdit::SetEditMask("00:00", "__:__");
			break;
		}
		default:
		{
			ASSERT(FALSE);
			break;
		}
	}
}