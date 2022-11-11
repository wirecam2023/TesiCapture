#include "stdafx.h"
#include "Endox.h"
#include ".\FreeExtEdit.h"
#include ".\ExtEdit.h"

#include "EsamiView.h"
#include "MenuDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE (CFreeExtEdit, CExtEdit)

CFreeExtEdit::CFreeExtEdit()
	: CExtEdit()
{
}

CFreeExtEdit::~CFreeExtEdit()
{
}

BEGIN_MESSAGE_MAP(CFreeExtEdit, CExtEdit)
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

void CFreeExtEdit::OnKillFocus(CWnd *pNewWnd)
{
	CExtEdit::OnKillFocus(pNewWnd);
	GetParent()->PostMessage(MSG_FREEEDIT_FOCUS_LOST, (WPARAM) GetSafeHwnd());
}

