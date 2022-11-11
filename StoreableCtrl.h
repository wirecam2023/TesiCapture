#pragma once

#define WM_LOAD_STORED_VALUE    WM_USER + 0x300
#define WM_SAVE_STORED_VALUE    WM_USER + 0x301

class CStoreableCtrl
{
public:
	static CStoreableCtrl* Get();

	void Create();
	void Destroy();

	void Bind(HWND hWnd, LPCTSTR szWndName);

	struct tagSTOREDCTRL
	{
		TCHAR szWndName[1024];
		TCHAR szValue[1024];
		BOOL bEnable;
	};

private:
	CStoreableCtrl(void);
	~CStoreableCtrl();

	static CStoreableCtrl m_ctrl;
	static HHOOK m_hook;

	static LRESULT WINAPI CallWndProc(int nCode, WPARAM wParam, LPARAM lParam);

	void LoadValue(HWND hWnd, CList<tagSTOREDCTRL>* pListValue);
	void SaveValue(HWND hWnd, CList<tagSTOREDCTRL>* pListValue);

	struct tagWND
	{
		HWND hWnd;
		TCHAR szWndName[1024];
	};
	CList<tagWND> m_listWnd;
};