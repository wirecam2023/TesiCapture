#include "stdafx.h"
#include "Endox.h"
#include "Endox.h"
#include "MonitoraggioListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMonitoraggioListCtrl, CAMEditComboListCtrl)

CMonitoraggioListCtrl::CMonitoraggioListCtrl()
	: CAMEditComboListCtrl(FALSE, TRUE, FALSE)
{
}

CMonitoraggioListCtrl::~CMonitoraggioListCtrl()
{
}

BEGIN_MESSAGE_MAP(CMonitoraggioListCtrl, CAMEditComboListCtrl)
	ON_WM_SIZE()
END_MESSAGE_MAP()

void CMonitoraggioListCtrl::OnSize(UINT nType, int cx, int cy)
{
	CListCtrl::OnSize(nType, cx, cy);
}

int CMonitoraggioListCtrl::GetColumnCount()
{
	return GetHeaderCtrl()->GetItemCount();
}
