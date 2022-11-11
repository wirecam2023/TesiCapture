#include "stdafx.h"
#include "Endox.h"
#include "SediTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CSediTreeCtrl, CTreeCtrl)

CSediTreeCtrl::CSediTreeCtrl()
{
}

CSediTreeCtrl::~CSediTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CSediTreeCtrl, CTreeCtrl)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

void CSediTreeCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TRACE1("%d\n", nChar);

	if (nChar != 37) // 37 è il codice del tasto "freccia a sinistra" e mi chiuderebbe il ramo quindi non lo spedisco //
		CTreeCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CSediTreeCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// classe nata appositamente per proibire il doppio click //
	// CTreeCtrl::OnLButtonDblClk(nFlags, point);
}