#include "stdafx.h"
#include "Endox.h"
#include "ThumbCtrlEx.h"

#include "FileBmp.h"
#include "LogFileWriter.h"

#include "DLL_Imaging\h\AMLogin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CThumbCtrlEx::CThumbCtrlEx()
{
	m_tctrlImageList.Create(100, 102, ILC_COLOR32, 0, 1);
	
	m_bPopUpActive = TRUE;
	m_pParentWnd = NULL;
	m_pImgList   = NULL;
	m_bLocked    = FALSE;
	m_iMaxImageSel = -1;

	m_lIDPaziente = 0;
	m_lIDEsame = 0;
}

BEGIN_MESSAGE_MAP(CThumbCtrlEx, CListCtrl)

	//ON_COMMAND(ID_THUMB_ACQUIRE,           OnThumbAcquire)
	//ON_COMMAND(IDC_IMM_DISK,  OnThumbImportFromDisk)
	//ON_COMMAND(ID_THUMB_IMPORT_FROM_TWAIN, OnThumbImportFromTwain)
	//ON_COMMAND(ID_THUMB_IMPORT_FROM_4D,    OnThumbImportFromDicom4D)
	//ON_COMMAND(ID_THUMB_PRINT,             OnThumbPrint)
	//ON_COMMAND(ID_THUMB_PRINT_PREVIEW,     OnThumbPrintPreview)
	//ON_COMMAND(ID_THUMB_DELETE,            OnThumbDelete)
	//ON_COMMAND(ID_THUMB_COMPARE,           OnThumbCompare)
	//ON_COMMAND(ID_THUMB_SELECT_ALL,        OnThumbSelectAll)
	//ON_COMMAND(ID_THUMB_CLIPBOARD,         OnThumbCopyToClipboard)
	//ON_COMMAND(ID_THUMB_RENAME,            OnThumbRename)
	//ON_COMMAND(ID_THUMB_EXPORT,            OnThumbExport)

	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()

	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()

	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()

    //ON_NOTIFY_REFLECT(LVN_BEGINLABELEDIT, OnBeginLabelEdit)
    //ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT,   OnEndLabelEdit)

END_MESSAGE_MAP()

void CThumbCtrlEx::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (theApp.m_bOldAlbumMode)
	{
		SetFocus();
		for (int i = 0; i < GetItemCount(); i++)
		{
			CRect rect;
			if (GetItemRect(i, &rect, LVIR_BOUNDS) && rect.PtInRect(point))
			{
				if (m_pParentWnd)
					m_pParentWnd->SendMessage(EPM_THUMB_DBLCLICK, i);
				break;
			}
		}
	}
	else
	{
		int nItem = -1;
		if (GetSelectedCount() == 1)
		{
			nItem = GetNextItem(nItem, LVNI_SELECTED);
			if (nItem >= 0 && m_pParentWnd) 
				m_pParentWnd->SendMessage(EPM_THUMB_DBLCLICK, nItem, 0);
		}
	}
}

void CThumbCtrlEx::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (theApp.m_bOldAlbumMode)
	{
		SetFocus();
	}
	else
	{
		CListCtrl::OnLButtonDown(nFlags, point);
		RefreshSelectedList();
		CheckSelectedItem();
	}
}

void CThumbCtrlEx::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	OnRButtonDown(nFlags, point);
}

void CThumbCtrlEx::OnRButtonDown(UINT nFlags, CPoint point)
{
	//CListCtrl::OnRButtonDown(nFlags, point);
	SetFocus();

	if (theApp.m_bOldAlbumMode)
	{
		for (int iItem = 0; iItem < GetItemCount(); iItem++)
		{
			CRect rect;
			if (GetItemRect(iItem, &rect, LVIR_BOUNDS) && rect.PtInRect(point))
			{
				BOOL bImageAlreadySelected = FALSE;
				for (int j = 0; j < m_listSelected.GetCount(); j++)
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

				if (!bImageAlreadySelected && (m_iMaxImageSel == -1 || ((UINT)m_listSelected.GetCount()) < m_iMaxImageSel))
					m_listSelected.AddTail(iItem);

				RefreshItemBitmap(iItem);

				// Sandro 04/09/2015 //

				POSITION pos = m_pImgList->FindIndex(iItem);
				if (pos != NULL)
				{
					IMG img = m_pImgList->GetAt(pos);

					if (bImageAlreadySelected)
						CFileBmp::RemoveSelected(img.lID, FALSE);
					else
						CFileBmp::NewSelected(img.lID, FALSE, img.type, img.szDescription, m_lIDPaziente, m_lIDEsame, FALSE, "", img.bCI);
				}

				//

				if (m_pParentWnd)
				{
					if(bImageAlreadySelected)
						m_pParentWnd->SendMessage(WM_UNSELIMG, GetItemData(iItem), m_listSelected.GetCount());
					else
						m_pParentWnd->SendMessage(WM_SELIMG, GetItemData(iItem), m_listSelected.GetCount());
				}

				ASSERT(m_listSelected.GetCount() <= GetItemCount());
			}
		}

	}
	else if (m_bPopUpActive)
	{
		RefreshSelectedList();

		if (!m_pParentWnd)
			return;

		GetCursorPos(&point);

		/*CEcoMenu menu;
		menu.LoadMenu(IDR_THUMB_CTRL);

		if (CEcoMenu* pContextMenu = (CEcoMenu*)m_pParentWnd->SendMessage(EPM_THUMB_GET_MENU, 0, (LPARAM)&menu))
			pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, GetParent());*/
	}
}
/*
void CThumbCtrl::OnBeginLabelEdit(NMHDR* pNMHDR, LRESULT* pResult) 
{
    LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
    *pResult = 1;
    
    CRect ItemRect;
    GetItemRect (pDispInfo->item.iItem, ItemRect, LVIR_LABEL);

    HWND hWnd = (HWND)SendMessage(LVM_GETEDITCONTROL);
    ASSERT (hWnd != NULL);
    if (m_pEditField.m_hWnd != 0)
		m_pEditField.DestroyWindow();
    VERIFY (m_pEditField.SubclassWindow(hWnd));

    m_pEditField.SetWindowText(GetItemText(pDispInfo->item.iItem, 0));

    *pResult = 0;
}

void CThumbCtrl::OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult) 
{
    LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
    int iField = (int)pDispInfo->item.lParam;
    m_newDescription = (pDispInfo->item.pszText);
    
    SetItem (&pDispInfo->item);
    *pResult = 1;

    if (m_pEditField.m_hWnd)
		VERIFY(m_pEditField.UnsubclassWindow() != NULL);

	if (m_pParentWnd) 
		m_pParentWnd->SendMessage(EPM_THUMB_RENAME, m_itemEdited, 0);
	
	::SetWindowLong(GetSafeHwnd(), GWL_STYLE, (::GetWindowLong(GetSafeHwnd(), GWL_STYLE) & ~LVS_EDITLABELS));
}
*/

void CThumbCtrlEx::OnThumbDelete()
{
	if (m_pParentWnd) 
		m_pParentWnd->SendMessage(EPM_THUMB_DELETE,(WPARAM)(const CThumbIDList*)&m_listSelected, 0);
}

void CThumbCtrlEx::OnThumbRename()
{
	/*
	::SetWindowLong(GetSafeHwnd(), GWL_STYLE, (::GetWindowLong(GetSafeHwnd(), GWL_STYLE) | LVS_EDITLABELS));

	if (m_listSelected.GetCount() == 1)
	{
		m_itemEdited = m_listSelected.GetHead();
		EditLabel(m_itemEdited);
	}
	*/

	if (m_listSelected.GetCount() == 1 && m_pParentWnd)
		m_pParentWnd->SendMessage(EPM_THUMB_RENAME, m_listSelected.GetHead(), 0);
}

void CThumbCtrlEx::OnThumbExport()
{
	if (m_pParentWnd) 
		m_pParentWnd->SendMessage(EPM_THUMB_EXPORT, (WPARAM)(const CThumbIDList*)&m_listSelected, 0);
}

void CThumbCtrlEx::OnThumbPrint()
{
	if (m_pParentWnd)
		m_pParentWnd->SendMessage(EPM_THUMB_PRINT, (WPARAM)(const CThumbIDList*)&m_listSelected, 0);
}

void CThumbCtrlEx::OnThumbPrintPreview()
{
	if (m_pParentWnd)
		m_pParentWnd->SendMessage(EPM_THUMB_PRINT_PREVIEW, (WPARAM)(const CThumbIDList*)&m_listSelected, 0);
}

void CThumbCtrlEx::OnThumbCopyToClipboard()
{
	if (m_listSelected.GetCount() == 1)
	{
		if (m_pParentWnd) 
			m_pParentWnd->SendMessage(EPM_THUMB_COPY_TO_CLIPBOARD, m_listSelected.GetHead(), 0);
	}
}

void CThumbCtrlEx::OnThumbImportFromDisk()
{
	if (m_pParentWnd) 
		m_pParentWnd->SendMessage(EPM_THUMB_IMPORT_FROM_DISK);
}

void CThumbCtrlEx::OnThumbImportFromDicom4D()
{
	if (m_pParentWnd) 
		m_pParentWnd->SendMessage(EPM_THUMB_IMPORT_FROM_DICOM4D);
}

void CThumbCtrlEx::OnThumbImportFromTwain()
{
	if (m_pParentWnd) 
		m_pParentWnd->SendMessage(EPM_THUMB_IMPORT_FROM_TWAIN);
}

void CThumbCtrlEx::OnThumbAcquire()
{
	if (m_pParentWnd) 
		m_pParentWnd->SendMessage(EPM_THUMB_ACQUIRE);
}

void CThumbCtrlEx::OnThumbCompare()
{
	if (m_pParentWnd) 
		m_pParentWnd->SendMessage(EPM_THUMB_COMPARE);
}

void CThumbCtrlEx::SetSelectionLimit(UINT iMaxImageSel)
{ 
	m_iMaxImageSel = iMaxImageSel;
	CheckSelectedItem();
}

void CThumbCtrlEx::OnThumbSelectAll()
{
	SetFocus();

	if (m_listSelected.GetCount() != GetItemCount())
	{
		m_listSelected.RemoveAll();
		for (int i = 0; i < GetItemCount(); i++)
		{
			if (!theApp.m_bOldAlbumMode)
			{
				SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
			}
			else if (m_pParentWnd)
			{
				m_listSelected.AddTail(i);
				RefreshItemBitmap(i);
			}
		}
	}
	else
	{
		m_listSelected.RemoveAll();
		for (int i = 0; i < GetItemCount(); i++)
		{
			if (!theApp.m_bOldAlbumMode)
			{
				SetItemState(i, 0, LVIS_SELECTED);
			}
			else if (m_pParentWnd)
			{
				RefreshItemBitmap(i);
			}
		}
	}

	if (!theApp.m_bOldAlbumMode)
		RefreshSelectedList();
	if (m_pParentWnd)
		m_pParentWnd->SendMessage(EPM_NUM_IMAGES_SELETECTED_NOTIFY, 0, m_listSelected.GetCount());
}

BOOL CThumbCtrlEx::GetThumbAcquireEnabled()
{
	return TRUE;
	//return !GetLockedMode() && theApp.m_bBoardInstalled && CSoftwareProtection::Get()->IsAcquireStation();
}

BOOL CThumbCtrlEx::GetThumbImportFromDiskEnabled()
{
	return TRUE;
	//return !GetLockedMode() && CSoftwareProtection::Get()->IsAcquireStation();
}

BOOL CThumbCtrlEx::GetThumbImportFromDicom4DEnabled()
{
	return TRUE;
	//return !GetLockedMode() && CSoftwareProtection::Get()->IsDicomStation();
}

BOOL CThumbCtrlEx::GetThumbImportFromTwainEnabled()
{
	return TRUE;
	//return !GetLockedMode() && CSoftwareProtection::Get()->IsAcquireStation();
}

BOOL CThumbCtrlEx::GetThumbPrintEnabled()
{
	return TRUE;
	//return m_listSelected.GetCount() > 0 && theApp.m_bPrinterInstalled && theApp.m_dwPrivileges & AMLogin_Permissions::print;
}

BOOL CThumbCtrlEx::GetThumbPrintPreviewEnabled()
{
	return TRUE;
	//return m_listSelected.GetCount() > 0 && theApp.m_bPrinterInstalled && theApp.m_dwPrivileges & AMLogin_Permissions::print;
}

BOOL CThumbCtrlEx::GetThumbDeleteEnabled()
{
	return m_listSelected.GetCount() > 0 && !GetLockedMode();
}

BOOL CThumbCtrlEx::GetThumbCompareEnabled()
{
	return m_listSelected.GetCount() == 0 && GetItemCount() > 0;
}

BOOL CThumbCtrlEx::GetThumbSelectAllEnabled()
{
	return GetItemCount() > 0;
}

BOOL CThumbCtrlEx::GetThumbClipboardEnabled()
{
	return TRUE;
	//return m_listSelected.GetCount() == 1 && theApp.m_dwPrivileges & AMLogin_Permissions::export_data;
}

BOOL CThumbCtrlEx::GetThumbRenameEnabled()
{
	return m_listSelected.GetCount() == 1 && !GetLockedMode();
}

BOOL CThumbCtrlEx::GetThumbExportEnabled()
{
	return TRUE;
	//return m_listSelected.GetCount() > 0 && theApp.m_dwPrivileges & AMLogin_Permissions::export_data;
}

BOOL CThumbCtrlEx::GetThumbSendPacsEnabled()
{
	/*if (m_listSelected.GetCount() == 0 || (theApp.m_dwPrivileges & AMLogin_Permissions::export_data) == 0)
		return FALSE;

	if (theApp.m_strDicomClientHost.IsEmpty())
		return FALSE;*/

	BOOL bReturn = TRUE;
	for (POSITION pos = m_listSelected.GetHeadPosition(); pos;)
	{
		if (m_pImgList->GetAt(m_pImgList->FindIndex(m_listSelected.GetNext(pos))).type != _dicom_)
		{
			bReturn = FALSE;
			break;
		}
	}

	return bReturn;
}

void CThumbCtrlEx::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CListCtrl::OnShowWindow(bShow, nStatus);

	//if (bShow && theApp.m_bWindowsXP)
	//	CalcImageSpacing();
}

void CThumbCtrlEx::OnSize(UINT nType, int cx, int cy)
{
	CListCtrl::OnSize(nType, cx, cy);
	CalcImageSpacing();
	RedrawWindow();
}

void CThumbCtrlEx::SetThumbss(const CImgList* pList, long lIDPaziente, long lIDEsame)
{
	m_lIDPaziente = lIDPaziente;
	m_lIDEsame = lIDEsame;

	SetImageList(&m_tctrlImageList, LVSIL_NORMAL);
	m_tctrlImageList.SetImageCount((UINT)pList->GetCount());
	DeleteAllItems();
	m_listSelected.RemoveAll();

	for (int i = 0; i < pList->GetCount(); i++)
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
	CalcImageSpacing();
}

void CThumbCtrlEx::RefreshItemBitmap(long lItem)
{
	BOOL bImageSelected = FALSE;			
	for (POSITION pos = m_listSelected.GetHeadPosition(); pos;)
		if (m_listSelected.GetNext(pos) == lItem)
			bImageSelected = TRUE;
	
	if (POSITION pos = m_pImgList->FindIndex(lItem))
	{
		IMG img = m_pImgList->GetAt(pos);
		m_tctrlImageList.Replace(lItem, CBitmap::FromHandle(bImageSelected ? img.hBmpSelected : img.hBmp), RGB(0, 0, 0));
		
		CRect rect;
		GetItemRect(lItem, &rect, LVIR_BOUNDS);
		InvalidateRect(&rect);
	}				
}

void CThumbCtrlEx::RefreshSelectedList()
{
	ASSERT(theApp.m_bOldAlbumMode == FALSE);

	// Davide : Elimino dalla lista gli elementi che non esistono più
	POSITION pos = m_listSelected.GetHeadPosition();
	while (pos)
	{
		POSITION posPrec = pos;
		if (m_listSelected.GetNext(pos) >= GetItemCount())
			m_listSelected.RemoveAt(posPrec);
	}

	// Davide : Se non ci sono elementi selezionati svuoto completamente la lista
	if (GetSelectedCount() == 0)
	{
		m_listSelected.RemoveAll();
	}
	// Altrimenti controllo gli elementi selezionati uno per uno ed edito la lista
	else
	{
		for (int i = 0; i < GetItemCount(); i++)
		{
			if (GetItemState(i, LVIS_SELECTED))
			{
				BOOL bFound = FALSE;
				for (int j = 0; j < m_listSelected.GetCount(); j++)
					if (POSITION pos = m_listSelected.FindIndex(j))
						if (m_listSelected.GetAt(pos) == i)
							bFound = TRUE;

				if (!bFound)
					m_listSelected.AddTail(i);
			}
			else
			{
				for (int j = 0; j < m_listSelected.GetCount(); j++)
				{
					if (POSITION pos = m_listSelected.FindIndex(j))
					{
						if (m_listSelected.GetAt(pos) == i)
						{
							m_listSelected.RemoveAt(pos);
							break;
						}
					}
				}
			}
		}
	}

	ASSERT(m_listSelected.GetCount() == GetSelectedCount());
	
	if (m_pParentWnd)
		m_pParentWnd->SendMessage(EPM_NUM_IMAGES_SELETECTED_NOTIFY, 0, m_listSelected.GetCount());
}

void CThumbCtrlEx::CheckSelectedItem()
{
	if (m_iMaxImageSel == -1)
		return;
	
	UINT iImageSel = 0;
	CThumbIDList list;

	for (POSITION pos = m_listSelected.GetTailPosition(); (pos && iImageSel < m_iMaxImageSel);)
	{
		list.AddHead(m_listSelected.GetPrev(pos));
		iImageSel++;
	}
	
	m_listSelected.RemoveAll();
	for (POSITION pos = list.GetHeadPosition(); pos;)
		m_listSelected.AddTail(list.GetNext(pos));

	for (int i = 0; i < GetItemCount(); i++)
	{
		BOOL bSelected = FALSE;
		for (POSITION pos = m_listSelected.GetHeadPosition(); pos;)
		{	
			if (m_listSelected.GetNext(pos) == i)
				bSelected = TRUE;
		}

		if (!theApp.m_bOldAlbumMode)
			SetItemState(i, bSelected ? LVIS_SELECTED : 0, LVIS_SELECTED);
		else
			RefreshItemBitmap(i);
	}
	
	if (!theApp.m_bOldAlbumMode)
		RefreshSelectedList();
}

void CThumbCtrlEx::SetSelectedThumb(CThumbIDList* pListSelected)
{
	ASSERT(theApp.m_bOldAlbumMode);

	m_listSelected.RemoveAll();
	m_listSelected.AddTail(pListSelected);
	
	for (int i = 0; i < GetItemCount(); i++)
		RefreshItemBitmap(i);

	if (m_pParentWnd)
		m_pParentWnd->SendMessage(EPM_NUM_IMAGES_SELETECTED_NOTIFY, 0, m_listSelected.GetCount());
}

void CThumbCtrlEx::CalcImageSpacing()
{
	if (!GetSafeHwnd())
		return;

	/*if (theApp.m_WindowsVer == CEcoApp::WindowsXP || theApp.m_WindowsVer == CEcoApp::WindowsAfterXP)
	{*/
		CRect rect;
		GetClientRect(rect);

		rect.right  = rect.right  - GetSystemMetrics(SM_CXVSCROLL);
		//rect.bottom = rect.bottom - GetSystemMetrics(SM_CYHSCROLL);
		
		int iNumberImageX = max((int)(((float)rect.Width()  - 20.0) / (float)(100 + 5)),  1);
		int iNumberImageY = max((int)(((float)rect.Height() - 20.0) / (float)(102 + 15)), 1);
		
		CString str;
		str.Format("Album size: %lix%li", rect.Width(), rect.Height());
		TRACE(str + _T("\n")); //CLogFileWriter::Get()->WriteLogLine(str);

		str.Format("Image X: %li Image Y: %li", iNumberImageX, iNumberImageY);
		TRACE(str + _T("\n")); //CLogFileWriter::Get()->WriteLogLine(str);

		str.Format("Icon spacing: %li %li", rect.Width() / iNumberImageX, rect.Height() / iNumberImageY);
		TRACE(str + _T("\n")); //CLogFileWriter::Get()->WriteLogLine(str);
		
		SetIconSpacing(-1, -1);
		SetIconSpacing(rect.Width() / iNumberImageX, rect.Height() / iNumberImageY);
		//Arrange(LVA_ALIGNTOP);
	/*}
	else
	{*/
		//CRect rect;
		GetClientRect(rect);
		rect.right  = rect.right  - GetSystemMetrics(SM_CXVSCROLL) - 10;  // 10 è la larghezza della selezione
		rect.bottom = rect.bottom - GetSystemMetrics(SM_CYHSCROLL) - 10;
		
		//int 
			iNumberImageX = max((int)((float)rect.Width()  / (float)(100 + 5)),  1);
		//int 
			iNumberImageY = max((int)((float)rect.Height() / (float)(102 + 20)), 1);
		
		//TRACE("Icon spacing: %li %li\n", rect.Width() / iNumberImageX, rect.Height() / iNumberImageY);
		
		SetIconSpacing(rect.Width() / iNumberImageX, rect.Height() / iNumberImageY);
	//}
}