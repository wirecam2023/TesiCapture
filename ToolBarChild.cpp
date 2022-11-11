#include "stdafx.h"
#include "Endox.h"
#include "ToolbarChild.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CToolBarChild::CToolBarChild(CWnd* pParentWnd)
{
	m_pParentWnd = pParentWnd;
}

CToolBarChild::~CToolBarChild()
{
}

LRESULT CToolBarChild::OnToolbarPressButton(WPARAM wParam, LPARAM lParam)
{
	m_pParentWnd->PostMessage(WM_TOOLBAR_PRESS_BUTTON, wParam, lParam);
	m_pParentWnd->SendMessage(WM_DESTROY_TOOLBAR_CHILD, wParam, lParam);
	return 0;
}

LRESULT CToolBarChild::OnUpdateCommandUI(WPARAM wParam, LPARAM lParam)
{
	return m_pParentWnd->SendMessage(WM_TOOLBAR_UPDATE_COMMAND_UI, wParam, lParam);
}

void CToolBarChild::DeleteButton(UINT id, BOOL bDeleteSeparatorAfter)
{
	if (!GetSafeHwnd())
		return;

	for (int i = 0; i < GetToolBarCtrl().GetButtonCount(); i++)
	{
		TBBUTTON button;
		if (GetToolBarCtrl().GetButton(i, &button) && button.idCommand == id)
		{
			GetToolBarCtrl().DeleteButton(i);
			if (bDeleteSeparatorAfter)
			{
				// Se ho eliminato ultimo bottone...
				if (i == GetToolBarCtrl().GetButtonCount())
				{
					// Se resta separatore per ultimo...
					if (GetToolBarCtrl().GetButton(i - 1, &button) && button.idCommand == 0)
						GetToolBarCtrl().DeleteButton(i - 1);
				}
				else
				{
					if (GetToolBarCtrl().GetButton(i, &button) && button.idCommand == 0)
						GetToolBarCtrl().DeleteButton(i);
				}
			}
			break;
		}
	}
}