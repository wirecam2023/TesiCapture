#include "stdafx.h"
#include "TXButtonBar23.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CTXButtonBar23, CWnd)
IMPLEMENT_DYNCREATE(CTXButtonBar23Ex, CTXButtonBar23)

CTXButtonBar23Ex::CTXButtonBar23Ex()
{
}

BEGIN_MESSAGE_MAP(CTXButtonBar23Ex, CTXButtonBar23)
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

void CTXButtonBar23Ex::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// tolgo la possibilità di fare doppio click sulla toolbar che si aprono configurazioni "strane" che poi non riusciamo a gestire in fase di stampa //
	// CTXButtonBar23::OnLButtonDblClk(nFlags, point);
}
