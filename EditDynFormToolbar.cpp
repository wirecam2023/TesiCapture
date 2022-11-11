#include "stdafx.h"
#include "Endox.h"
#include "EditDynFormToolbar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEditDynFormToolbar::CEditDynFormToolbar()
	: CToolBarEx()
{
}

CEditDynFormToolbar::~CEditDynFormToolbar(void)
{
}

void CEditDynFormToolbar::Create(UINT idFrame, CWnd* pParentWnd)
{
	if (!CToolBarEx::CreateEx(pParentWnd, TBSTYLE_FLAT | TBSTYLE_TOOLTIPS | TBSTYLE_WRAPABLE, WS_CHILD | CBRS_ALIGN_TOP, CRect(0, 0, 0, 0), IDR_BAR_RTF))
		return; // 2

	if (!LoadToolBar(IDR_BAR_RTF))
		return; // 6

	if (!LoadTCToolBar(IDB_BAR_RTF, IDB_BAR_RTF_BW))
		return; // 8

	//Julio - BUG 4392 Edicao de texto
	if(!theApp.m_bRtfUsaConfigurazioniFont) 
		DeleteButton(IDC_RTF_FONT);
	
	if (!theApp.m_bRtfUsaConfigurazioniImmagini)
		DeleteButton(IDC_RTF_IMAGE);
	//

	AttachEx(idFrame, pParentWnd);
}

LRESULT CEditDynFormToolbar::OnToolbarPressButton(WPARAM wParam, LPARAM lParam)
{
	GetParent()->PostMessage(WM_COMMAND, wParam);
	return 0;
}