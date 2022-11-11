#include "stdafx.h"
#include "Endox.h"
#include "EndoGridMaskEdit.h"
#include "EndoGridItemDate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEndoGridInplaceMaskEdit, CXTPPropertyGridInplaceEdit)

BEGIN_MESSAGE_MAP(CEndoGridInplaceMaskEdit, CXTPPropertyGridInplaceEdit)
	ON_MASKEDIT_REFLECT()
END_MESSAGE_MAP()

void CEndoGridInplaceMaskEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//if ((GetStyle() & ES_READONLY) == 0)
	CXTMaskEditT<CXTPPropertyGridInplaceEdit>::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CEndoGridInplaceMaskEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	class CPropertyItem : public CXTPPropertyGridItem
	{
		friend class CEndoGridInplaceMaskEdit;
	};

	//Davide new codejock if (nChar == VK_TAB)
	//Davide new codejock 	((CPropertyItem*)GetItem())->OnChar(nChar);

	if ((GetStyle() & ES_READONLY) == 0)
	{
		CXTMaskEditT<CXTPPropertyGridInplaceEdit>::OnChar(nChar, nRepCnt, nFlags);
		if (CEndoGridItemDate* pItem = dynamic_cast <CEndoGridItemDate*>(GetItem()))
			pItem->NotifyDirty();
	}

	if (nChar == VK_RETURN)
	{
		if (GetGrid() && GetGrid()->GetSafeHwnd() && GetGrid()->GetPropertyGrid() && GetGrid()->GetPropertyGrid()->GetSafeHwnd())
			GetGrid()->GetPropertyGrid()->PostMessage(EPM_EDIT_GRID_ITEM_ENTER);
	}
}

CEndoGridMaskEdit::CEndoGridMaskEdit(CString strCaption)
	: CXTPPropertyGridItem(strCaption)
{
}

CEndoGridMaskEdit::CEndoGridMaskEdit(UINT nID)
	: CXTPPropertyGridItem(nID)
{
}

void CEndoGridMaskEdit::SetEditMask(LPCTSTR lpszMask, LPCTSTR lpszLiteral, LPCTSTR lpszDefault)
{
	m_strEditMask = lpszMask;
	m_strLiteral = lpszLiteral;
	m_strValue = lpszDefault;
}

CXTPPropertyGridInplaceEdit& CEndoGridMaskEdit::GetInplaceEdit()
{
	return m_wndMaskEdit;
}

void CEndoGridMaskEdit::OnDeselect()
{
	CXTPPropertyGridItem::OnDeselect();
}

void CEndoGridMaskEdit::OnSelect()
{
	CXTPPropertyGridItem::OnSelect();

	if (m_wndMaskEdit.GetSafeHwnd())
	{
		m_wndMaskEdit.SetOverType(TRUE);
		m_wndMaskEdit.SetEditMask(m_strEditMask, m_strLiteral, m_strValue);
		m_wndMaskEdit.SetPromptChar('_');
	}

}