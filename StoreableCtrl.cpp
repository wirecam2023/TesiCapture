#include "stdafx.h"
#include "eNDOX.h"
#include "StoreableCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CStoreableCtrl CStoreableCtrl::m_ctrl;
HHOOK CStoreableCtrl::m_hook;

CStoreableCtrl::CStoreableCtrl(void)
{
	m_hook = NULL;
}

CStoreableCtrl::~CStoreableCtrl(void)
{
}

CStoreableCtrl* CStoreableCtrl::Get()
{
	return &m_ctrl;
}

void CStoreableCtrl::Create()
{
	if (m_hook)
		ASSERT(FALSE);

	m_hook = SetWindowsHookEx(WH_CALLWNDPROCRET, CallWndProc, NULL, GetCurrentThreadId());
}

void CStoreableCtrl::Destroy()
{
	UnhookWindowsHookEx(m_hook);
	m_hook = NULL;
}

void CStoreableCtrl::Bind(HWND hWnd, LPCTSTR szWndName)
{
	if (!m_hook)
		return;

	tagWND wnd;
	wnd.hWnd = hWnd;
	strcpy_s(wnd.szWndName, szWndName);
	m_listWnd.AddTail(wnd);
}

LRESULT WINAPI CStoreableCtrl::CallWndProc(int nCode, WPARAM wParam, LPARAM lParam) 
{
	if (nCode < 0)
		return CallNextHookEx(m_hook, nCode, wParam, lParam);

	CWPRETSTRUCT* pMessage = (CWPRETSTRUCT*)lParam;

	switch (pMessage->message)
	{
		case WM_LOAD_STORED_VALUE:
			CStoreableCtrl::Get()->LoadValue(pMessage->hwnd, (CList<tagSTOREDCTRL>*)pMessage->lParam);
			break;

		case WM_SAVE_STORED_VALUE:
			CStoreableCtrl::Get()->SaveValue(pMessage->hwnd, (CList<tagSTOREDCTRL>*)pMessage->lParam);
			break;

		default:
			break;
	}

	return CallNextHookEx(m_hook, nCode, wParam, lParam);
}

void CStoreableCtrl::LoadValue(HWND hWnd, CList<tagSTOREDCTRL>* pListValue)
{
	TCHAR szValue[1024];
	BOOL bEnable;
	BOOL bFound = FALSE;
	for (POSITION pos1 = m_listWnd.GetHeadPosition(); pos1;)
	{
		tagWND wnd = m_listWnd.GetNext(pos1);
		if (wnd.hWnd == hWnd)
		{
			for (POSITION pos2 = pListValue->GetHeadPosition(); pos2;)
			{
				tagSTOREDCTRL data = pListValue->GetNext(pos2);
				if (strcmp(data.szWndName, wnd.szWndName) == 0)
				{
					strcpy_s(szValue, data.szValue);
					bEnable = data.bEnable;
					bFound = TRUE;
				}
			}

			if (bFound)
				break;
		}
	}

	if (!bFound)
		return;

	::EnableWindow(hWnd, bEnable);
	TCHAR szClassName[256];
	::GetClassName(hWnd, szClassName, 255);
	
	if (strcmp(szClassName, "Edit") == 0)
	{
		::SetWindowText(hWnd, szValue);
	}
	else if (strcmp(szClassName, "ComboBox") == 0)
	{
		CComboBox* pCombo = (CComboBox*)CComboBox::FromHandle(hWnd);
		for (int i = 0; i < pCombo->GetCount(); i++)
		{
			CString str;
			pCombo->GetLBText(i, str);
			if (str == CString(szValue))
			{
				pCombo->SetCurSel(i);
				break;
			}
		}
	}
	else if (strcmp(szClassName, "Button") == 0)
	{
		CButton* pButton = (CButton*)CButton::FromHandle(hWnd);
		pButton->SetCheck(atol(szValue));
	}
	else if (strcmp(szClassName, "ListBox") == 0)
	{
		CListBox* pList = (CListBox*)CListBox::FromHandle(hWnd);
		CString str(szValue);
		int iInserted;
		BOOL bString = TRUE;

		int nLastPos = 0, nPos = 0;
		while (nPos != -1)
		{
			nPos = str.Find(";", nLastPos);
			if (nPos != -1)
			{
				if (bString)
					iInserted = pList->InsertString(pList->GetCount(), str.Mid(nLastPos, nPos - nLastPos));
				else
					pList->SetItemData(iInserted, atol(str.Mid(nLastPos, nPos - nLastPos)));

				nLastPos = nPos + 1;
				bString = !bString;
			}
		}
	}
}

void CStoreableCtrl::SaveValue(HWND hWnd, CList<tagSTOREDCTRL>* pListValue)
{
	tagSTOREDCTRL newElem;
	BOOL bFound = FALSE;

	for (POSITION pos = m_listWnd.GetHeadPosition(); pos;)
	{
		tagWND wnd = m_listWnd.GetNext(pos);
		if (wnd.hWnd == hWnd)
		{
			strcpy_s(newElem.szWndName, wnd.szWndName);
			bFound = TRUE;
			break;
		}
	}

	if (!bFound)
		return;
	
	newElem.bEnable = IsWindowEnabled(hWnd);
	ZeroMemory(&newElem.szValue, 1024 * sizeof(TCHAR));
	
	TCHAR szClassName[256];
	::GetClassName(hWnd, szClassName, 255);

	if (strcmp(szClassName, "Edit") == 0 || strcmp(szClassName, "ComboBox") == 0)
	{
		GetWindowText(hWnd, newElem.szValue, 1024);
	}
	else if (strcmp(szClassName, "Button") == 0)
	{
		CButton* pButton = (CButton*)CButton::FromHandle(hWnd);
		sprintf_s(newElem.szValue, "%li", pButton->GetCheck());
	}
	else if (strcmp(szClassName, "ListBox") == 0)
	{
		CListBox* pList = (CListBox*)CListBox::FromHandle(hWnd);
		CString strTemp1, strTemp2;
		for (int i = 0; i < pList->GetCount(); i++)
		{
			pList->GetText(i, strTemp1);
			strTemp2.Format("%s;%li;", strTemp1, pList->GetItemData(i));
			strcat_s(newElem.szValue, strTemp2);
		}
	}

	pListValue->AddTail(newElem);
}