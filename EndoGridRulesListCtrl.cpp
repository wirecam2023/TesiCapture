#include "stdafx.h"
#include "EndoGridRulesListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEndoGridRulesListCtrl::CEndoGridRulesListCtrl(int iColumnNotResizable)
	: CAMEditComboListCtrl(FALSE, FALSE, FALSE)
{
	m_iColumnNotResizable = iColumnNotResizable;
}

CEndoGridRulesListCtrl::~CEndoGridRulesListCtrl(void)
{
}

BOOL CEndoGridRulesListCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	HD_NOTIFY* pHDN = (HD_NOTIFY*)lParam;

	if ((pHDN->hdr.code == HDN_BEGINTRACKW || pHDN->hdr.code == HDN_BEGINTRACKA || pHDN->hdr.code == HDN_DIVIDERDBLCLICKA || pHDN->hdr.code == HDN_DIVIDERDBLCLICKW) &&
		(pHDN->iItem == m_iColumnNotResizable))            // Prevent only first (col# 0) from resizing
	{
		*pResult = TRUE;                // disable tracking
		return TRUE;                    // Processed message
	}

	return CAMEditComboListCtrl::OnNotify(wParam, lParam, pResult);
}