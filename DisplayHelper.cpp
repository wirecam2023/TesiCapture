#include "stdafx.h"
#include "DisplayHelper.h"
#include <algorithm>
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

INT CDisplayHelper::nDisplay;
int MyInfoCounter = 0;
std::vector<MONITORINFOEX*> dispInfoVector;

//
BOOL CALLBACK CDisplayHelper::MyInfoEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
	MONITORINFOEX* iMonitor = new MONITORINFOEX;
	ZeroMemory(iMonitor, sizeof(MONITORINFOEX));
	iMonitor->cbSize = sizeof(MONITORINFOEX);
	GetMonitorInfo(hMonitor, iMonitor);

	if (iMonitor->dwFlags == DISPLAY_DEVICE_MIRRORING_DRIVER)
		return TRUE;
	else
		dispInfoVector.push_back(iMonitor);

	return TRUE;
}

//
void CDisplayHelper::FreeDisplayVector()
{
	struct
	{
		void operator() (MONITORINFOEX* element) const
		{
			delete element;
		}
	} delete_pointer_element;

	std::for_each(dispInfoVector.begin(), dispInfoVector.end(), delete_pointer_element);
	dispInfoVector.clear();
}

//
void CDisplayHelper::GetDisplayWorkRect(RECT* pRect, int display)
{
	FreeDisplayVector();

	nDisplay = display;
	MyInfoCounter = 0;
	EnumDisplayMonitors(NULL, NULL, MyInfoEnumProc, (LPARAM)&nDisplay);

	struct {
		bool operator()(MONITORINFOEX* a, MONITORINFOEX* b)
		{
			return a->rcMonitor.left < b->rcMonitor.left;
		}
	} predicate;

	std::sort(dispInfoVector.begin(), dispInfoVector.end(), predicate);

	//Se imposto un monitor non presente, mi metto sul principale
	if (display >= (int) dispInfoVector.size() || display < 0)
		display = 0;
	
	*pRect = dispInfoVector[display]->rcWork;

	FreeDisplayVector();
}

void CDisplayHelper::GetDisplayList(CStringList* tempList)
{
	FreeDisplayVector();

	MyInfoCounter = 0;
	EnumDisplayMonitors(NULL, NULL, MyInfoEnumProc, NULL);

	struct {
		bool operator()(MONITORINFOEX* a, MONITORINFOEX* b)
		{
			return a->rcMonitor.left < b->rcMonitor.left;
		}
	} predicate;

	std::sort(dispInfoVector.begin(), dispInfoVector.end(), predicate);

	for (int i = 0; i < (int)dispInfoVector.size(); i++)
	{
		CRect tempRect = dispInfoVector[i]->rcMonitor;		
		CString temp;
		temp.Format("%s %lix%li", dispInfoVector[i]->szDevice, tempRect.Width(), tempRect.Height());
		temp.Replace("\\\\.\\", "");

		tempList->AddTail(temp);

	}

	FreeDisplayVector();
}