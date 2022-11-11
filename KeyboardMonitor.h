#pragma once

class CKeyboardMonitor
{

public:

	static CKeyboardMonitor* Get();

	BOOL Start(HWND hWndNotify, UINT iMsg);
	BOOL Stop();

	struct tagNOTIFICATION
	{
		WORD nRepCount;
		BYTE nScanCode;
		BOOL bExtKey;
		BOOL bContextKey;
		BOOL bKeyIsDown;
		BOOL bTransition;
		BOOL bCtrlKeyIsDown;
	};

protected:

	CKeyboardMonitor(void);
	~CKeyboardMonitor(void);

	static CKeyboardMonitor m_Monitor;

	static LRESULT CALLBACK Tracker(int code, WPARAM wParam, LPARAM lParam);

	static HHOOK m_hHook;
	static HWND m_hWndNotify;
	static UINT m_iMsg;

};
