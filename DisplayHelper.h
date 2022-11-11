#pragma once
class CDisplayHelper
{
public:

	static void FreeDisplayVector();
	static void GetDisplayWorkRect(RECT* pRect, int display);
	static void GetDisplayList(CStringList* tempList);
	static BOOL CALLBACK MyInfoEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);
	static RECT rcDisplay;
	static INT nDisplay;
};

