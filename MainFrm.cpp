#include "stdafx.h"
#include "Endox.h"

#include "DLL_Imaging\h\AMLogin.h"

#include "EsamiView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)
IMPLEMENT_MENUXP(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_GETMINMAXINFO()
	ON_MENUXP_MESSAGES()

	ON_COMMAND(ID_HELP_FINDER,  CFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP,         CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)

	ON_MESSAGE(WM_MY_HELP,		  OnHelp) // Sandro //

	ON_REGISTERED_MESSAGE(MSG_XCAP_MSG_NUOVOMONITORAGGIO, OnXcapMsgNuovoMonitoraggio)
	ON_REGISTERED_MESSAGE(MSG_XCAP_MSG_NUOVAPROVETTA, OnXcapMsgNuovaProvetta)

	ON_WM_SIZE()
	ON_WM_SIZING()
END_MESSAGE_MAP()

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CMenuXP::SetXPLookNFeel(this);
    CMenuXP::UpdateMenuBar(this);

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.Create(this, WS_CHILD | CBRS_TOP) || !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	CMenu* pMenu = GetMenu();
	CString str, strCaption;
	UINT uMenuID;

	//Julio - BUG 3707 - Traduteabilidade dos menus de 3o nivel
	for(int i = 0; i < pMenu->GetMenuItemCount(); i++)
	{
		if (uMenuID = pMenu->GetMenuItemID(i))
		{
			strCaption.Empty();
			pMenu->GetMenuString(i, strCaption, MF_BYPOSITION);
			AMLocalize_GetMenuCaption(module_endox, IDR_MAINFRAME, i, 0, 0, strCaption, &str);
			pMenu->ModifyMenu(i, MF_BYPOSITION, uMenuID, str);
	
			CMenu* pPopupMenu = pMenu->GetSubMenu(i);
			if (pPopupMenu)
			{
				for(int j = 0; j < pPopupMenu->GetMenuItemCount(); j++)
				{
					if (uMenuID = pPopupMenu->GetMenuItemID(j))
					{
						strCaption.Empty();
						pPopupMenu->GetMenuString(j, strCaption, MF_BYPOSITION);
						AMLocalize_GetMenuCaption(module_endox, IDR_MAINFRAME, i, j + 1, 0, strCaption, &str);
						pPopupMenu->ModifyMenu(j, MF_BYPOSITION, uMenuID, str);
					
						CMenu* pPopupMenu2 = pPopupMenu->GetSubMenu(j);
						if (pPopupMenu2)
						{
							for(int z = 0; z < pPopupMenu2->GetMenuItemCount(); z++)
							{
								if (uMenuID = pPopupMenu2->GetMenuItemID(z))
								{
									strCaption.Empty();
									pPopupMenu2->GetMenuString(z, strCaption, MF_BYPOSITION);
									AMLocalize_GetMenuCaption(module_endox, IDR_MAINFRAME, i, j + 1, z + 1, strCaption, &str);
									pPopupMenu2->ModifyMenu(z, MF_BYPOSITION, uMenuID, str);
									
									CMenu* pPopupMenu3 = pPopupMenu2->GetSubMenu(z);
									if (pPopupMenu3)
									{
										for (int k = 0; k < pPopupMenu3->GetMenuItemCount(); k++)
										{
											if (uMenuID = pPopupMenu3->GetMenuItemID(k))
											{
												strCaption.Empty();
												pPopupMenu3->GetMenuString(k, strCaption, MF_BYPOSITION);
												AMLocalize_GetMenuCaption(module_endox, IDR_MAINFRAME, i, j + 1, ((z + 1)*100) + k, strCaption, &str);
												pPopupMenu3->ModifyMenu(k, MF_BYPOSITION, uMenuID, str);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	//

	return 0;
}

void CMainFrame::OnClose()
{
	CEsamiView* pEsamiView = (CEsamiView*)GetActiveView();
	if (pEsamiView != NULL)
	{
		if ((theApp.m_nProgramMode == NOTHING_MODE) || (theApp.m_nProgramMode & FILTER_RECORD_PAZIENTI) || (theApp.m_nProgramMode & FILTER_RECORD_ESAMI))
		{
			if (pEsamiView->m_bImporting)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_TRASFERIMENTOINCORSO), MB_ICONSTOP);
				return;
			}

			if (pEsamiView->m_bPrinting)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_STAMPAINCORSO), MB_ICONSTOP);
				return;
			}

			if (theApp.m_bChiusuraProgrammaConferma)
			{
				CString strMessage;
				strMessage.Format(theApp.GetMessageString(IDS_CONFERMACHIUSURA), theApp.m_sNomeProgramma);
				if (theApp.AfxMessageBoxEndo(strMessage, MB_YESNO | MB_ICONQUESTION) == IDNO)
					return;
			}

			theApp.m_lIDEsameFirmaDisattivata = 0;
			AMLogin_Logout();

			// Salvo queste configurazioni qui perché è il momento subito prima l'azzeramento della UO
			CString sIdRobotDefault;
			sIdRobotDefault.Format("%s UO %li", szIdRobotDefault, theApp.m_lUO);
			WritePrivateProfileInt(szSettings, sIdRobotDefault, theApp.m_lIdRobotDefault, theApp.m_sFileConfig);

			CString sCodiceDispVSDefault;
			sCodiceDispVSDefault.Format("%s UO %li", szCodiceDispositivoDefault, theApp.m_lUO);
			WritePrivateProfileString(szSettings, sCodiceDispVSDefault, theApp.m_sCodiceDispositivoDefault, theApp.m_sFileConfig);

			//

			theApp.m_lUO = 0; // Sandro 16/11/2015 // RAS 201500080 //
			CFrameWnd::OnClose();
		}
		else
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CANNOT_EXIT));
		}
	}
}

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	lpMMI->ptMinTrackSize.x = 1280;
	lpMMI->ptMinTrackSize.y = 768;
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT &cs)
{
	if ( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	// per colpa di Windows 7 che ha i "margini" della finestra più grossi... //
	int xTemp = 1280; // +6; // 1024 //
	int yTemp = 768; // +4; // 768 //

	cs.cx = xTemp;
	cs.cy = yTemp;

	cs.x  = (GetSystemMetrics(SM_CXSCREEN) - xTemp) / 2;
	cs.y  = (GetSystemMetrics(SM_CYSCREEN) - yTemp) / 2;

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU;

	return TRUE;
}

BOOL CMainFrame::OnHelpInfo(HELPINFO* pHelpInfo)
{
	return TRUE;
}

/* Sandro 10/02/2015 VS2013
void CMainFrame::HtmlHelp(DWORD_PTR dwData, UINT nCmd)
{
	switch (LOWORD(dwData))
	{
		default:
		case IDR_MAINFRAME:
			::HtmlHelp(m_hWnd, CString(CString(theApp.m_pszHelpFilePath) + "::/Html/00_Prima.htm>"), HH_DISPLAY_TOPIC, NULL);
			//::HtmlHelp(m_hWnd, theApp.m_pszHelpFilePath, HH_HELP_CONTEXT, idh_00_Prima);
			break;
	}
}
*/

LRESULT CMainFrame::OnHelp(WPARAM wParam, LPARAM lParam)
{
	CFrameWnd::OnHelp();
	return 0;
}

LRESULT CMainFrame::OnXcapMsgNuovoMonitoraggio(WPARAM, LPARAM)
{

	if (theApp.m_bVitalSignIntegrazioneAttiva)
		return 0;

	theApp.m_bReopenAcquisition = TRUE;

	CEsamiView* pEsamiView = (CEsamiView*)GetActiveView();
	if (pEsamiView != NULL)
		pEsamiView->InserisciNuovoMonitoraggio();

	BeginWaitCursor();
	return 0;
}

LRESULT CMainFrame::OnXcapMsgNuovaProvetta(WPARAM, LPARAM)
{
	theApp.m_bReopenAcquisition = TRUE;

	CEsamiView* pEsamiView = (CEsamiView*)GetActiveView();
	if (pEsamiView != NULL)
		pEsamiView->InserisciNuovaProvetta();

	BeginWaitCursor();
	return 0;
}
