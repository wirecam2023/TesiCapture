#include "stdafx.h"
#include "TreeCtrlExpanded.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CTreeCtrlExpanded::CTreeCtrlExpanded(void)
{
}

CTreeCtrlExpanded::~CTreeCtrlExpanded(void)
{
}

BEGIN_MESSAGE_MAP(CTreeCtrlExpanded, CTreeCtrl)
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

void CTreeCtrlExpanded::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CTreeCtrl::OnLButtonDblClk(nFlags, point);
	HTREEITEM hItemSelected = GetSelectedItem();
	if (hItemSelected)
		Expand(hItemSelected, TVE_EXPAND);
}
