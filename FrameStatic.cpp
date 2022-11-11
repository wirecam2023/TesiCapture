#include "stdafx.h"
#include "Endox.h"
#include "Endox.h"
#include "FrameStatic.h"
#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CFrameStatic, CStatic)

CFrameStatic::CFrameStatic(COLORREF* pCR)
{
	m_pCR = pCR;
}

CFrameStatic::~CFrameStatic()
{
}

BEGIN_MESSAGE_MAP(CFrameStatic, CStatic)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

BOOL CFrameStatic::OnEraseBkgnd(CDC* pDC)
{
	CRect myRect;
	this->GetWindowRect(myRect);
	pDC->FillSolidRect(1, 9, myRect.Width() - 2, myRect.Height() - 10, *m_pCR);
	return TRUE;
}
