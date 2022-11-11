#include "stdafx.h"
#include "Endox.h"
#include "ExtList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE (CExtList, CListBox)

CExtList::CExtList()
	:CListBox()
{
	m_pParentForm = NULL;
}

CExtList::~CExtList()
{
}

void CExtList::SetParam(CWnd* pParentForm)
{
	m_pParentForm = pParentForm;
}

BEGIN_MESSAGE_MAP(CExtList, CListBox)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CExtList::OnLButtonDown(UINT nFlags, CPoint point) 
{
	BOOL	bIsOutside;
	int		nItem;

	CListBox::OnLButtonDown(nFlags, point);
	
	nItem = (int)ItemFromPoint(point, bIsOutside);

	if (!bIsOutside)
	{
		CRect RectItem;

		GetItemRect(nItem, &RectItem);

		bIsOutside = !RectItem.PtInRect(point);
	}
	
	if (!bIsOutside)
	{
		if (nItem >= 0)
		{
			if (SetCurSel(nItem) != LB_ERR)
			{
				WPARAM wParam = MAKEWPARAM(GetDlgCtrlID(), LBN_DBLCLK);
				
				if (m_pParentForm)
					m_pParentForm->PostMessage(WM_COMMAND, (WPARAM)wParam, (LPARAM)GetSafeHwnd());
			}
		}
	}
}