#include "stdafx.h"
#include "Endox.h"
#include "EndoGridItemCheck.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CEndoGridInplaceCheckBox, CButton)
	ON_MESSAGE(BM_SETCHECK, OnCheck)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

CEndoGridInplaceCheckBox::CEndoGridInplaceCheckBox()
{
	m_iFirstValue = 0;
	m_bNotify = TRUE;
}

HBRUSH CEndoGridInplaceCheckBox::CtlColor(CDC* pDC, UINT /*nCtlColor*/)
{
	class CGridView : public CXTPPropertyGridView
	{
		friend class CEndoGridInplaceCheckBox;
	};

	CGridView* pGrid = (CGridView*)m_pItem->m_pGrid;

	//Davide - New Codejock COLORREF clr = pGrid->m_clrBack;
	COLORREF clr = pGrid->GetPaintManager()->GetItemMetrics()->m_clrBack;

	if (clr != m_clrBack || !m_brBack.GetSafeHandle())
	{
		m_brBack.DeleteObject();
		m_brBack.CreateSolidBrush(clr);
		m_clrBack = clr;
	}

	pDC->SetBkColor(m_clrBack);
	return m_brBack;
}

LRESULT CEndoGridInplaceCheckBox::OnCheck(WPARAM wParam, LPARAM lParam)
{
	m_pItem->m_bValue = (wParam == BST_CHECKED);

	if (m_bNotify)
	{
		//m_pItem->OnValueChanged(m_pItem->GetValue());
		//m_pItem->NotifyDirty();
	}
	else
		m_iFirstValue = wParam;

	return CButton::DefWindowProc(BM_SETCHECK, wParam, lParam);
}

void CEndoGridInplaceCheckBox::OnKillFocus(CWnd* pNewWnd)
{
	if (GetCheck() != m_iFirstValue)
	{
		m_pItem->OnValueChanged(m_pItem->GetValue());
		m_pItem->NotifyDirty();
	}

	CButton::OnKillFocus(pNewWnd);
}

IMPLEMENT_DYNAMIC(CEndoGridItemCheck, CXTPPropertyGridItem)

CEndoGridItemCheck::CEndoGridItemCheck(CString strCaption)
: CXTPPropertyGridItem(strCaption)
{
	m_wndCheckBox.m_pItem = this;
	m_nFlags = 0;
	m_bValue = FALSE;
}

CEndoGridItemCheck::CEndoGridItemCheck(UINT nID)
	: CXTPPropertyGridItem(nID)
{
	m_wndCheckBox.m_pItem = this;
	m_nFlags = 0;
	m_bValue = FALSE;
}

void CEndoGridItemCheck::OnDeselect()
{
	CXTPPropertyGridItem::OnDeselect();

	if (m_wndCheckBox.m_hWnd)
		m_wndCheckBox.DestroyWindow();
}

void CEndoGridItemCheck::OnSelect()
{
	CXTPPropertyGridItem::OnSelect();

	if (!m_bReadOnly)
	{
		CRect rc = GetValueRect();
		rc.left -= 15;
		rc.right = rc.left + 15;

		if (!m_wndCheckBox.m_hWnd)
			m_wndCheckBox.Create(NULL, WS_CHILD | BS_AUTOCHECKBOX | BS_FLAT, rc, (CWnd*)m_pGrid, 0);

		m_wndCheckBox.m_bNotify = FALSE;
		SetBool(m_bValue);
		m_wndCheckBox.m_bNotify = TRUE;

		m_wndCheckBox.MoveWindow(rc);
		m_wndCheckBox.ShowWindow(SW_SHOW);
	}
}

void CEndoGridItemCheck::OnValueChanged(CString strValue)
{
	CXTPPropertyGridItem::OnValueChanged(strValue);
	if (m_pGrid)
		m_pGrid->SendNotifyMessage(XTP_PGN_ITEMVALUE_CHANGED, (LPARAM)this);
}

CRect CEndoGridItemCheck::GetValueRect()
{
	CRect rcValue(CXTPPropertyGridItem::GetValueRect());
	rcValue.left += 17;
	return rcValue;
}

BOOL CEndoGridItemCheck::OnDrawItemValue(CDC& dc, CRect rcValue)
{
	CRect rcText(rcValue);

	if (m_wndCheckBox.GetSafeHwnd() == 0 && m_bValue)
	{
		CRect rcCheck(rcText.left, rcText.top, rcText.left + 13, rcText.bottom - 1);
		dc.DrawFrameControl(rcCheck, DFC_MENU, DFCS_MENUCHECK);
	}

	rcText.left += 17;
	//dc.DrawText( GetValue(), rcText,  DT_SINGLELINE|DT_VCENTER);
	return TRUE;
}

BOOL CEndoGridItemCheck::GetBool()
{
	return m_bValue;
}

void CEndoGridItemCheck::SetBool(BOOL bValue)
{
	m_bValue = bValue;

	if (m_wndCheckBox.GetSafeHwnd())
		m_wndCheckBox.SetCheck(bValue);
}

BOOL CEndoGridItemCheck::OnChar(UINT nChar)
{
	if ((nChar == VK_SPACE || nChar == VK_RETURN) && !m_bReadOnly)
		SetBool(!m_bValue);

	return CXTPPropertyGridItem::OnChar(nChar);
}

void CEndoGridItemCheck::NotifyDirty()
{
	if (m_pGrid)
		m_pGrid->GetParent()->PostMessage(EPM_ITEMDIRTY);
}