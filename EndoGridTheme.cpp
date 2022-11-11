#include "stdafx.h"
#include "Endox.h"
#include "EndoGridTheme.h"
#include "EndoGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEndoGridTheme::CEndoGridTheme(CXTPPropertyGrid* pGrid)
	: CXTPPropertyGridCoolTheme(pGrid)
{
}

CEndoGridTheme::~CEndoGridTheme()
{
}

COLORREF CEndoGridTheme::GetItemBackColor(CXTPPropertyGridItem* pItem, BOOL bValuePart)
{
	if (pItem)
	{
		CXTPPropertyGridItemMetrics* pMetrics = pItem->GetMetrics(bValuePart, FALSE);
		if (pMetrics && !pMetrics->m_clrBack.IsDefaultValue())
			return pMetrics->m_clrBack;
	}

	return RGB(255, 255, 255);
}

void CEndoGridTheme::DrawItem(PDRAWITEMSTRUCT lpDrawItemStruct)
{
	CXTPPropertyGridView* pView = &m_pGrid->GetGridView();
	CXTPPropertyGridItem* pItem = (CXTPPropertyGridItem*)lpDrawItemStruct->itemData;

	ASSERT(pItem != NULL);
	if (!pItem)
		return;

	CXTPWindowRect rcWindow(pView);
	CRect rc = lpDrawItemStruct->rcItem;

	CXTPBufferDC dc(lpDrawItemStruct->hDC, rc);
	CXTPFontDC font(&dc, GetItemFont(pItem, TRUE));

	dc.FillSolidRect(rc, GetItemBackColor(pItem, FALSE));
	dc.SetBkMode(TRANSPARENT);

	CRect rcCaption(rc.left, rc.top, rc.left + pView->GetDividerPos(), rc.bottom);

	COLORREF clrLine = m_pMetrics->m_clrLine;
	COLORREF clrShadow = GetXtremeColor(COLOR_3DSHADOW);

	if (pItem->IsCategory())
	{
		dc.FillSolidRect(rc, clrLine);

		CFont* pFont = GetItemFont(pItem, FALSE);
		font.SetFont(pFont);
		dc.SetTextColor(GetItemTextColor(pItem, FALSE));

		int nIndent = XTP_PGI_EXPAND_BORDER * (pItem->GetIndent() + 1);

		if (lpDrawItemStruct->itemState & ODS_FOCUS)
		{
			dc.SetTextColor(m_clrHighlightText);
			dc.FillSolidRect(CRect(nIndent - 1, rc.top, rc.right, rc.bottom), m_clrHighlight);
		}

		CRect rcText(nIndent + 3, rc.top, rc.right, rc.bottom - 1);

		CXTPPropertyGridItemMetrics* pMetrics = pItem->GetMetrics(FALSE, FALSE);
		if (pMetrics && pMetrics->m_nImage != -1)
		{
			CXTPImageManagerIcon* pImage = m_pGrid->GetImageManager()->GetImage(pMetrics->m_nImage, 0);

			if (pImage)
			{
				int nHeight = min(pImage->GetHeight(), rc.Height());
				int nWidth = pImage->GetWidth();

				CPoint pt(rcText.left, rcText.CenterPoint().y - nHeight / 2);
				pImage->Draw(&dc, pt, CSize(nWidth, nHeight));

				rcText.OffsetRect(nWidth + 4, 0);
			}
		}

		if (pItem->GetMarkupCaption())
		{
			XTPMarkupSetDefaultFont(XTPMarkupElementContext(pItem->GetMarkupCaption()),
				(HFONT)pFont->GetSafeHandle(), dc.GetTextColor());

			XTPMarkupMeasureElement(pItem->GetMarkupCaption(), rcText.Width(), rcText.Height());
			XTPMarkupRenderElement(pItem->GetMarkupCaption(), dc.GetSafeHdc(), rcText);
		}
		else
		{
			dc.DrawText(pItem->GetCaption(), rcText, DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER);
		}

		dc.FillSolidRect((pItem->GetIndent() + (pItem->IsExpanded() ? 1 : 0)) * XTP_PGI_EXPAND_BORDER - 1, rc.bottom - 1, rc.Width(), 1, clrShadow);

		BOOL bSelected = (lpDrawItemStruct->itemState & (ODS_SELECTED | ODS_FOCUS));
		if (bSelected || m_pGrid->GetShowInplaceButtonsAlways()) DrawInplaceButtons(&dc, pItem, rcText);

		CXTPPropertyGridItem* pCategory = pItem->GetParentItem();
		while (pCategory != NULL)
		{
			if (pCategory->IsCategory())
			{
				dc.FillSolidRect(rc.left + pCategory->GetIndent() * XTP_PGI_EXPAND_BORDER, rc.top, XTP_PGI_EXPAND_BORDER, rc.Height(), clrLine);
				dc.FillSolidRect(rc.left + (pCategory->GetIndent() + 1) * XTP_PGI_EXPAND_BORDER - 1, rc.top, 1, rc.Height() + 2, clrShadow);
			}
			pCategory = pCategory->GetParentItem();
		}
	}
	else
	{
		CRect rcValue(rcCaption.right, rc.top, rc.right, rc.bottom - 1);

		// --> Davide
		CFont* pOldFont = NULL;
		if (pItem->GetCaptionBold())
			pOldFont = (CFont*)dc.SelectObject(&m_pMetrics->m_fontBold);
		// <-- Davide

		DrawItemValue(&dc, pItem, rcValue);

		// --> Davide
		if (pOldFont)
			dc.SelectObject(pOldFont);
		pOldFont = NULL;
		// <-- Davide

		dc.SetTextColor(GetItemTextColor(pItem, FALSE));
		font.SetFont(GetItemFont(pItem, FALSE));

		BOOL bSelected = lpDrawItemStruct->itemState & ODS_SELECTED;
		BOOL bFocused = bSelected && CWnd::GetFocus() && ((CWnd::GetFocus() == pView) || (CWnd::GetFocus()->GetParent() == pView) || (CWnd::GetFocus()->GetOwner() == pView));
		BOOL bObbligatory = ((CEndoGrid*)m_pGrid)->GetEvidenceObbligaroryField() && ((CEndoGrid*)m_pGrid)->IsObbligaroryField(pItem);

		if (bFocused)
		{
			dc.SetTextColor(m_clrHighlightText);
			dc.FillSolidRect(rcCaption, m_clrHighlight);
		}
		else if (bSelected && !m_pGrid->m_bHideSelection)
		{
			dc.FillSolidRect(rcCaption, clrLine);
		}

		CXTPPenDC pen(dc, clrLine);
		dc.MoveTo(0, rc.bottom - 1);
		dc.LineTo(rc.right, rc.bottom - 1);
		dc.MoveTo(rcCaption.right, rc.top);
		dc.LineTo(rcCaption.right, rc.bottom - 1);

		CXTPPropertyGridItem* pCategory = pItem->GetParentItem();
		while (pCategory != NULL)
		{
			if (pCategory->IsCategory())
			{
				dc.FillSolidRect(rc.left + pCategory->GetIndent() * XTP_PGI_EXPAND_BORDER, rc.top, XTP_PGI_EXPAND_BORDER, rc.Height(), clrLine);
				dc.FillSolidRect(rc.left + (pCategory->GetIndent() + 1) * XTP_PGI_EXPAND_BORDER - 1, rc.top, 1, rc.Height() + 2, clrShadow);
			}
			pCategory = pCategory->GetParentItem();
		}

		// --> Davide
		if (pItem->GetCaptionBold() || bSelected)
			pOldFont = (CFont*)dc.SelectObject(&m_pMetrics->m_fontBold);

		int iMode = 0;
		COLORREF clColor = 0;
		if (bObbligatory && !bSelected)
		{
			iMode = dc.SetBkMode(OPAQUE);
			//clColor = dc.SetBkColor(RGB(255, 255, 0));
			clColor = dc.SetBkColor(((CEndoGrid*)m_pGrid)->GetRequiredFieldColor());
		}
		// <-- Davide

		DrawItemCaption(&dc, pItem, rcCaption);

		// --> Davide
		if (bObbligatory && !bSelected)
		{
			dc.SetBkMode(iMode);
			dc.SetBkColor(clColor);
		}

		if (pOldFont)
			dc.SelectObject(pOldFont);
		pOldFont = NULL;
		// <-- Davide

		if (bSelected || m_pGrid->GetShowInplaceButtonsAlways())
			DrawInplaceButtons(&dc, pItem, rcValue);
	}

	CXTPPropertyGridItem* pNext = (CXTPPropertyGridItem*)pView->GetItemDataPtr(lpDrawItemStruct->itemID + 1);
	if (((ULONG_PTR)pNext == (ULONG_PTR)(-1)))
		dc.FillSolidRect(0, rc.bottom - 1, rc.Width(), 1, clrShadow);
	else if (pNext && pNext->IsCategory() && pNext->IsVisible())
	{
		dc.FillSolidRect(pNext->GetIndent() * XTP_PGI_EXPAND_BORDER, rc.bottom - 1, rc.Width(), 1, clrShadow);
	}

	CXTPPropertyGridItem* pPrev = pItem;
	if (!pPrev)
		return;

	CXTPPropertyGridItem* pCategory = pPrev->GetParentItem();
	while (pCategory != NULL)
	{
		if (pItem->HasChilds() && pItem->IsExpanded())
			break;

		if (pCategory->IsCategory() && pCategory->IsVisible() && pCategory->GetChilds()->GetAt(pCategory->GetChilds()->GetCount() - 1) == pPrev)
		{
			dc.FillSolidRect(pCategory->GetIndent() * XTP_PGI_EXPAND_BORDER, rc.bottom - 1, rc.Width(), 1, clrShadow);
		}
		else
			break;
		pPrev = pCategory;
		pCategory = pPrev->GetParentItem();
	}


	if (pItem->HasVisibleChilds())
	{
		CRgn rgn;
		if (!pItem->IsCategory())
		{
			rgn.CreateRectRgnIndirect(&rcCaption);
			dc.SelectClipRgn(&rgn);
		}

		DrawExpandButton(dc, pItem, rcCaption);

		dc.SelectClipRgn(NULL);
	}
}
