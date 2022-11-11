#include "stdafx.h"
#include "Endox.h"
#include "ThumbCtrl.h"

#include <io.h>

#include "DLL_Imaging\h\AMLogin.h"

#include "EsamiView.h"
#include "ImageDicomDlg.h"
#include "MaximizeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CThumbCtrl::CThumbCtrl()
{
	m_tctrlImageList.Create(HSIZE_PAL_4, VSIZE_PAL_4, ILC_COLOR32, 0, 1);
	
	m_pParentWnd = NULL;
	m_pEsamiView = NULL;

	m_pImgList = NULL;
}

BEGIN_MESSAGE_MAP(CThumbCtrl, CListCtrl)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
END_MESSAGE_MAP()

void CThumbCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	SetFocus();
	for(int i = 0; i < GetItemCount(); i++)
	{
		CRect rect;
		if (GetItemRect(i, &rect, LVIR_BOUNDS) && rect.PtInRect(point))
		{
			if (POSITION pos = m_pImgList->FindIndex(i))
			{
				IMG img = m_pImgList->GetAt(pos);
				CString strDesc(img.szDescription);
				int nCapoIndex = strDesc.Find('\n');
				CString strFile = theApp.m_sDirTemp + "\\" + strDesc.Left(nCapoIndex);

				switch(img.type)
				{
					case _image_:
					case _mptiff_:
					{
						if (m_pEsamiView != NULL)
						{
							CDib dibTemp;
							HBITMAP hBitNor;
							if (m_pEsamiView->m_pImgManager->LoadLocalImageEx(strFile, &hBitNor) > 0)
							{
								if (hBitNor != NULL)
								{
									dibTemp.Attach(CDib::BitmapToDIB(hBitNor, NULL), TRUE);

									if (dibTemp.IsValidDib())
									{
										CMaximizeDlg dlg(this, &dibTemp);
										dlg.DoModal();

										dibTemp.ReleaseContents();
									}
								}

								DeleteObject(hBitNor);
							}
						}
						break;
					}
					case _movie_:
					{
						if (_access(strFile, 00) == 0)
						{
							TCHAR szProcess[1024];
							sprintf_s(szProcess, "\"%s\\xPlay\\xPlay.exe\" -f %s -d %s -r on -s off -p off -a on -c %d -o", theApp.m_sDirProg, strFile, "C:\\", 0);

							STARTUPINFO si;
							PROCESS_INFORMATION pi;

							ZeroMemory(&si, sizeof(si));
							si.cb = sizeof(si);
							ZeroMemory(&pi, sizeof(pi));

							if (!CreateProcess(NULL, szProcess, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
							{
								LPVOID lpMsgBuf;
								if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL))
									theApp.AfxMessageBoxEndo((LPCTSTR)lpMsgBuf);
								else
									theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_NOT_DEFINED));
								LocalFree(lpMsgBuf);

								return;
							}

							WaitForSingleObject(pi.hProcess, INFINITE);
							CloseHandle(pi.hProcess);
							CloseHandle(pi.hThread);
						}
						break;
					}
					case _dicom_:
					{
						CImageDicomDlg dlg(this, strFile);
						dlg.DoModal();

						break;
					}
				}
			}

			if (m_pParentWnd)
				m_pParentWnd->SendMessage(EPM_THUMB_DBLCLICK, i, m_listSelected.GetCount());

		}
	}
	
}

void CThumbCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();
}

void CThumbCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	for(int iItem = 0; iItem < GetItemCount(); iItem++)
	{
		CRect rect;
		if (GetItemRect(iItem, &rect, LVIR_BOUNDS) && rect.PtInRect(point))
		{
			BOOL bImageAlreadySelected = FALSE;
			for(int j = 0; j < m_listSelected.GetCount(); j++)
			{
				if (POSITION pos = m_listSelected.FindIndex(j))
				{
					if (m_listSelected.GetAt(pos) == iItem)
					{
						bImageAlreadySelected = TRUE;
						m_listSelected.RemoveAt(pos);
						break;
					}
				}
			}

			if (!bImageAlreadySelected)
				m_listSelected.AddTail(iItem);

			RefreshItemBitmap(iItem);

			ASSERT(m_listSelected.GetCount() <= GetItemCount());
		}
	}

	if (m_pParentWnd)
		m_pParentWnd->SendMessage(EPM_IMAGESEL_NOTIFY, 0, m_listSelected.GetCount());
}

void CThumbCtrl::SelectAll()
{
	m_listSelected.RemoveAll();

	for (int iItem = 0; iItem < GetItemCount(); iItem++)
	{
		m_listSelected.AddTail(iItem);
		RefreshItemBitmap(iItem);
	}

	if (m_pParentWnd)
		m_pParentWnd->SendMessage(EPM_IMAGESEL_NOTIFY, 0, m_listSelected.GetCount());
}

void CThumbCtrl::DeselectAll()
{
	m_listSelected.RemoveAll();

	for (int iItem = 0; iItem < GetItemCount(); iItem++)
	{
		RefreshItemBitmap(iItem);
	}

	if (m_pParentWnd)
		m_pParentWnd->SendMessage(EPM_IMAGESEL_NOTIFY, 0, m_listSelected.GetCount());
}


void CThumbCtrl::OnShowWindow(BOOL bShow, UINT nStatus)
{
	if (bShow)
		CalcImageSpacing();
}

void CThumbCtrl::OnSize(UINT nType, int cx, int cy)
{
	CListCtrl::OnSize(nType, cx, cy);
	if (IsWindowVisible())
		CalcImageSpacing();
}

void CThumbCtrl::SetMessageDest(CWnd* pParentWnd, CEsamiView* pEsamiView)
{
	m_pParentWnd = pParentWnd;
	m_pEsamiView = pEsamiView;
}

void CThumbCtrl::SetThumbs(CImgList* pList)
{
	SetImageList(&m_tctrlImageList, LVSIL_NORMAL);
	m_tctrlImageList.SetImageCount((UINT)pList->GetCount());
	DeleteAllItems();
	m_listSelected.RemoveAll();

	for(int i = 0; i < pList->GetCount(); i++)
	{
		if (POSITION pos = pList->FindIndex(i))
		{
			IMG img = pList->GetAt(pos);
			InsertItem(i, img.szDescription, i);
			m_tctrlImageList.Replace(i, CBitmap::FromHandle(img.hBmp), RGB(0, 0, 0));
			SetItemData(i, img.lID);
		}
	}

	m_pImgList = pList;
}

void CThumbCtrl::RefreshItemBitmap(long lItem)
{
	BOOL bImageSelected = FALSE;			
	for(POSITION pos = m_listSelected.GetHeadPosition(); pos;)
		if (m_listSelected.GetNext(pos) == lItem)
			bImageSelected = TRUE;
	
	if (POSITION pos = m_pImgList->FindIndex(lItem))
	{
		IMG img = m_pImgList->GetAt(pos);
		m_tctrlImageList.Replace(lItem, CBitmap::FromHandle(bImageSelected ? img.hBmpSelected : img.hBmp), RGB(0, 0, 0));
		Invalidate();
	}				
}

void CThumbCtrl::CalcImageSpacing()
{
	if (!GetSafeHwnd())
		return;

	CRect rect;
	GetClientRect(rect);
	rect.right  = rect.right  - GetSystemMetrics(SM_CXVSCROLL) - 10;  // 10 è la larghezza della selezione
	rect.bottom = rect.bottom - GetSystemMetrics(SM_CYHSCROLL) - 10;
	
	int iNumberImageX = max((int)((float)rect.Width()  / (float)(HSIZE_PAL_4 + 8)),  1);
	int iNumberImageY = max((int)((float)rect.Height() / (float)(VSIZE_PAL_4 + 40)), 1);
	
	TRACE("Image X: %li Image Y: %li\n", iNumberImageX, iNumberImageY);
	TRACE("Icon spacing: %li %li\n", rect.Width() / iNumberImageX, rect.Height() / iNumberImageY);
	
	SetIconSpacing(rect.Width() / iNumberImageX, rect.Height() / iNumberImageY);
}

CString CThumbCtrl::GetDescription(int nIndex)
{
	CString strFile = "";
	if (POSITION pos = m_pImgList->FindIndex(nIndex))
	{
		IMG img = m_pImgList->GetAt(pos);
		CString strDesc(img.szDescription);
		/*int nCapoIndex = strDesc.Find('\n');
		strFile = theApp.m_sDirTempAcq + "\\" + strDesc.Left(nCapoIndex);*/
		strFile = strDesc;
	}
	return strFile;
}

BOOL CThumbCtrl::DeleteItem(int nItem)
{
	// cancello l'item dalla vista //
	BOOL bReturn = CListCtrl::DeleteItem(nItem);


	POSITION pos2 = m_pImgList->FindIndex(nItem);
	if (pos2 != NULL)
	{
		IMG imgTemp = m_pImgList->GetAt(pos2);

		DeleteObject(imgTemp.hBmp);
		DeleteObject(imgTemp.hBmpSelected);

		m_pImgList->RemoveAt(pos2);
	}

	//m_tctrlImageList.Remove(nItem);

	return bReturn;
}