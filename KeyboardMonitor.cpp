#include "stdafx.h"
#include "Endox.h"
#include "KeyboardMonitor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CKeyboardMonitor CKeyboardMonitor::m_Monitor;
HHOOK CKeyboardMonitor::m_hHook;
HWND CKeyboardMonitor::m_hWndNotify;
UINT CKeyboardMonitor::m_iMsg;

CKeyboardMonitor::CKeyboardMonitor()
{
	m_hHook = NULL;
}

CKeyboardMonitor::~CKeyboardMonitor(void)
{
}

CKeyboardMonitor* CKeyboardMonitor::Get()
{
	return &m_Monitor;
}

BOOL CKeyboardMonitor::Start(HWND hWndNotify, UINT iMsg)
{
	if (m_hHook == NULL)
		m_hHook = SetWindowsHookEx(WH_KEYBOARD, Tracker, NULL, GetCurrentThreadId());

	_ASSERT(m_hHook);

	m_hWndNotify = hWndNotify;
	m_iMsg = iMsg;

	return (m_hHook) ? TRUE : FALSE;
}

BOOL CKeyboardMonitor::Stop()
{
	BOOL bReturn = FALSE;
	if (m_hHook)
	{
		bReturn = UnhookWindowsHookEx(m_hHook);
		_ASSERT(bReturn);
		m_hHook = NULL;
	}
	return bReturn;
}

// Keyboard hook: record tick count
LRESULT CALLBACK CKeyboardMonitor::Tracker(int code, WPARAM wParam, LPARAM lParam)
{
	if (code == HC_ACTION)
	{
		USHORT iState1 = GetKeyState(VK_CONTROL);
		USHORT iState2 = GetKeyState(VK_LCONTROL);
		USHORT iState3 = GetKeyState(VK_RCONTROL);

		tagNOTIFICATION* kn = new tagNOTIFICATION;
		kn->nRepCount = LOWORD(lParam);
		kn->nScanCode = LOBYTE(HIWORD(lParam));
		kn->bExtKey = lParam & ((LPARAM)1 << 24) ? TRUE : FALSE;
		kn->bContextKey = lParam & ((LPARAM)1 << 29) ? TRUE : FALSE;
		kn->bKeyIsDown = lParam & ((LPARAM)1 << 30) ? TRUE : FALSE;
		kn->bTransition = lParam & ((LPARAM)1 << 31) ? TRUE : FALSE;
		kn->bCtrlKeyIsDown = (iState1 >> 15) == 1 || (iState2 >> 15) == 1 || (iState3 >> 15) == 1;

		// TRACE("Tracker %li\n", lParam);
		::PostMessage(m_hWndNotify, m_iMsg, wParam, (LPARAM)kn);

		delete kn;
		kn = NULL;
	}

	return ::CallNextHookEx(CKeyboardMonitor::Get()->m_hHook, code, wParam, lParam);
}