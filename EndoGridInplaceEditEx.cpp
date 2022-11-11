#include "stdafx.h"
#include "Endox.h"
#include "EndoGridInplaceEditEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEndoGridInplaceEditEx, CXTPPropertyGridInplaceEdit)

CEndoGridInplaceEditEx::CEndoGridInplaceEditEx(void)
: CXTPPropertyGridInplaceEdit()
{
}

CEndoGridInplaceEditEx::~CEndoGridInplaceEditEx(void)
{
}

BEGIN_MESSAGE_MAP(CEndoGridInplaceEditEx, CXTPPropertyGridInplaceEdit)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
END_MESSAGE_MAP()

void CEndoGridInplaceEditEx::OnLButtonDown(UINT nFlags, CPoint point)
{
	CXTPPropertyGridInplaceEdit::OnLButtonDown(nFlags, point);

	class CPropertyItem : public CXTPPropertyGridItem
	{
		friend class CEndoGridInplaceEditEx;
	};

}

void CEndoGridInplaceEditEx::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (GetStyle() & ES_READONLY)
		CXTPPropertyGridInplaceEdit::OnLButtonDblClk(nFlags, point);

	NotifyDirty();
}

void CEndoGridInplaceEditEx::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	class CPropertyItem : public CXTPPropertyGridItem
	{
		friend class CEndoGridInplaceEditEx;
	};

	//if (nChar == VK_TAB)
	//	((CPropertyItem*)GetItem())->OnChar(nChar);

	/*
	if (((CPropertyItem*)GetItem())->GetFlags() & pgiHasComboButton && nChar != VK_TAB) {
	((CPropertyItem*)GetItem())->OnInplaceButtonDown();
	}
	else
	*/
	NotifyDirty();

	CXTPPropertyGridInplaceEdit::OnChar(nChar, nRepCnt, nFlags);
}

void CEndoGridInplaceEditEx::NotifyDirty()
{
	CWnd* pParent = this->GetParent();
	if (pParent)
		pParent->GetOwner()->PostMessage(EPM_ITEMDIRTY);
}