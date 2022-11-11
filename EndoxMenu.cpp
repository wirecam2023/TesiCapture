#include "stdafx.h"
#include "Endox.h"
#include "EndoxMenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEndoxMenu::CEndoxMenu()
{
}

CEndoxMenu::~CEndoxMenu()
{
}

BOOL CEndoxMenu::LoadMenu(UINT nIDResource)
{
	BOOL bReturn = CMenu::LoadMenu(nIDResource);
	CString str, strCaption;
	UINT uMenuID;

	for (int i = 0; i < GetMenuItemCount(); i++)
	{
		if (uMenuID = GetMenuItemID(i))
		{
			strCaption.Empty();
			GetMenuString(i, strCaption, MF_BYPOSITION);
			AMLocalize_GetMenuCaption(module_ecoplus, nIDResource, i, 0, 0, strCaption, &str);
			ModifyMenu(i, MF_BYPOSITION, uMenuID, str);
	
			if (CMenu* pPopupMenu = GetSubMenu(i))
			{
				for (int j = 0; j < pPopupMenu->GetMenuItemCount(); j++)
				{
					if (uMenuID = pPopupMenu->GetMenuItemID(j))
					{
						strCaption.Empty();
						pPopupMenu->GetMenuString(j, strCaption, MF_BYPOSITION);
						AMLocalize_GetMenuCaption(module_ecoplus, nIDResource, i, j + 1, 0, strCaption, &str);
						pPopupMenu->ModifyMenu(j, MF_BYPOSITION, uMenuID, str);

						CMenu* pPopupMenu2 = pPopupMenu->GetSubMenu(j);
						if (pPopupMenu2)
						{
							for (int z = 0; z < pPopupMenu2->GetMenuItemCount(); z++)
							{
								if (uMenuID = pPopupMenu2->GetMenuItemID(z))
								{
									strCaption.Empty();
									pPopupMenu2->GetMenuString(z, strCaption, MF_BYPOSITION);
									AMLocalize_GetMenuCaption(module_pathox, IDR_MAINFRAME, i, j + 1, z + 1, strCaption, &str);
									pPopupMenu2->ModifyMenu(z, MF_BYPOSITION, uMenuID, str);
								}
							}
						}
					}
				}
			}
		}
	}

	return bReturn;
}

/*
BOOL CEndoxMenu::TrackPopupMenu(UINT nFlags, int x, int y, CWnd* pWnd, LPCRECT lpRect)
{
	return CXTPCommandBars::TrackPopupMenu(this, nFlags, x, y, pWnd, lpRect, pWnd, ((CMainFrame*)AfxGetMainWnd())->GetCommandBars());
}
*/
