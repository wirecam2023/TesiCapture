#include "stdafx.h"
#include "Endox.h"
#include "Endox.h"
#include "AnatomiaPatologicaListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CAnatomiaPatologicaListCtrl, CListCtrl)

CAnatomiaPatologicaListCtrl::CAnatomiaPatologicaListCtrl()
{
	m_pStampaRigaFunction = NULL;
	m_pEsamiView = NULL;

	m_bReadOnly = TRUE;
}

CAnatomiaPatologicaListCtrl::~CAnatomiaPatologicaListCtrl()
{
}

BEGIN_MESSAGE_MAP(CAnatomiaPatologicaListCtrl, CListCtrl)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CAnatomiaPatologicaListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	CListCtrl::OnLButtonDown(nFlags, point);

	if (!m_bReadOnly)
	{
		if (GetItemCount() > 0)
		{
			POSITION pos = GetFirstSelectedItemPosition();
			if (pos != NULL)
			{
				int nItem = GetNextSelectedItem(pos);

				CRect rectItem;
				GetSubItemRect(nItem, 7, LVIR_BOUNDS, rectItem);

				// TRACE1("- pnt.x=%li\n", point.x);
				// TRACE2("- rct.l=%li - rct.r=%li\n", rectItem.left, rectItem.right);

				if ((point.x >= rectItem.left) && (point.x <= rectItem.right))
				{
					if (m_pStampaRigaFunction != NULL)
						m_pStampaRigaFunction((long)GetItemData(nItem), m_pEsamiView);
				}
			}
		}
	}
}

void CAnatomiaPatologicaListCtrl::SetReadOnly(BOOL bReadOnly)
{
	m_bReadOnly = bReadOnly;
}