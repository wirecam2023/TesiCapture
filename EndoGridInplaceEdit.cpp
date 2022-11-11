#include "stdafx.h"
#include "Endox.h"
#include "EndoGridInplaceEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEndoGridInplaceEdit, CXTPPropertyGridInplaceEdit)

CEndoGridInplaceEdit::CEndoGridInplaceEdit(void)
: CXTPPropertyGridInplaceEdit()
{
}

CEndoGridInplaceEdit::~CEndoGridInplaceEdit(void)
{
}

BEGIN_MESSAGE_MAP(CEndoGridInplaceEdit, CXTPPropertyGridInplaceEdit)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()

void CEndoGridInplaceEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	CXTPPropertyGridInplaceEdit::OnLButtonDown(nFlags, point);

	class CPropertyItem : public CXTPPropertyGridItem
	{
		friend class CEndoGridInplaceEdit;
	};

	if ((GetStyle() & ES_READONLY) == 0)
	{
		if ((CPropertyItem*)GetItem())
		{
			if(((CPropertyItem*)GetItem())->GetInplaceButtons()->GetCount() > 0)
				((CPropertyItem*)GetItem())->OnInplaceButtonDown(((CPropertyItem*)GetItem())->GetInplaceButtons()->GetAt(0));
		}
		//Davide New Codejock ((CPropertyItem*)GetItem())->OnInplaceButtonDown();*/
	}
}

void CEndoGridInplaceEdit::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (GetStyle() & ES_READONLY)
		CXTPPropertyGridInplaceEdit::OnLButtonDblClk(nFlags, point);
}

void CEndoGridInplaceEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	class CPropertyItem : public CXTPPropertyGridItem
	{
		friend class CEndoGridInplaceEdit;
	};

	//Davide - New Codejock if ((GetStyle() & ES_READONLY) == 0)
	//Davide - New Codejock		((CPropertyItem*)GetItem())->OnInplaceButtonDown();

	if (GetItem() && (GetItem()->GetFlags() & xtpGridItemHasComboButton) && nChar != VK_TAB && (GetStyle() & ES_READONLY) == 0)
	{
		if ((CPropertyItem*)GetItem())
			((CPropertyItem*)GetItem())->OnInplaceButtonDown(((CPropertyItem*)GetItem())->GetInplaceButtons()->GetAt(0));
	}
	else
	{
		CXTPPropertyGridInplaceEdit::OnChar(nChar, nRepCnt, nFlags);
		if (nChar == VK_RETURN)
		{
			if (GetGrid() && GetGrid()->GetSafeHwnd() && GetGrid()->GetPropertyGrid() && GetGrid()->GetPropertyGrid()->GetSafeHwnd())
				GetGrid()->GetPropertyGrid()->PostMessage(EPM_EDIT_GRID_ITEM_ENTER);
		}
	}
}
