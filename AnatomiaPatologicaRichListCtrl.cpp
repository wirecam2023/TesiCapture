#include "stdafx.h"
#include "Endox.h"
#include "Endox.h"
#include "AnatomiaPatologicaRichListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CAnatomiaPatologicaRichListCtrl, CListCtrlLocalize /*CAMEditComboListCtrl*/)

CAnatomiaPatologicaRichListCtrl::CAnatomiaPatologicaRichListCtrl()
	: CListCtrlLocalize() /*CAMEditComboListCtrl()*/
{
	m_pStampaRigaFunction = NULL;
	m_pEsamiView = NULL;
}

CAnatomiaPatologicaRichListCtrl::~CAnatomiaPatologicaRichListCtrl()
{
}

BEGIN_MESSAGE_MAP(CAnatomiaPatologicaRichListCtrl, CListCtrlLocalize /*CAMEditComboListCtrl*/)
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
END_MESSAGE_MAP()

void CAnatomiaPatologicaRichListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	/*CAMEditComboListCtrl*/CListCtrlLocalize::OnLButtonDown(nFlags, point);

	if (GetItemCount() > 0)
	{
		POSITION pos = GetFirstSelectedItemPosition();
		if (pos != NULL)
		{
			int nItem = GetNextSelectedItem(pos);

			CRect rectItem;
			GetSubItemRect(nItem, 10, LVIR_BOUNDS, rectItem);

			// TRACE1("- pnt.x=%li\n", point.x);
			// TRACE2("- rct.l=%li - rct.r=%li\n", rectItem.left, rectItem.right);

			if ((point.x >= rectItem.left) && (point.x <= rectItem.right))
			{
				if (m_pStampaRigaFunction != NULL)
				{
					CString strTemp5 = GetItemText(nItem, 5);
					CString strTemp7 = GetItemText(nItem, 7);

					if ((strTemp5.Compare("SCREENING") == 0) || (strTemp5.Compare("FAMILIARI") == 0) || (strTemp5.Compare("Esterno") == 0))
					{
						if (strTemp7.CompareNoCase(theApp.GetMessageString(IDS_ANATOMIA_SPEDIRE)) == 0)
						{
							m_pStampaRigaFunction(atol(GetItemText(nItem, 0)), atol(GetItemText(nItem, 1)), m_pEsamiView, FALSE);
						}
						else
						{
							if (strTemp7.CompareNoCase(theApp.GetMessageString(IDS_ANATOMIA_SPEDIREALTRO)) == 0)
								m_pStampaRigaFunction(atol(GetItemText(nItem, 0)), atol(GetItemText(nItem, 1)), m_pEsamiView, TRUE);
						}
					}
				}
			}
		}
	}
}

void CAnatomiaPatologicaRichListCtrl::OnSize(UINT nType, int cx, int cy)
{
	/*CAMEditComboListCtrl*/CListCtrlLocalize::OnSize(nType, cx, cy);
}