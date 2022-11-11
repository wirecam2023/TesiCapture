#pragma once

#ifndef _THUMBCTRLEX_H_
	#define _THUMBCTRLEX_H_

#include "DLL_Imaging\h\imglist.h"

typedef CList<int, int&> CThumbIDList;

class CThumbCtrlEx : public CListCtrl
{
public:
	CThumbCtrlEx();
	
	void SetPopupMenu(BOOL bEnable)       { m_bPopUpActive = bEnable;  };
	void SetMessageDest(CWnd* pParentWnd) { m_pParentWnd = pParentWnd; };

	CThumbIDList* GetSelectedThumb() { return &m_listSelected; };
	void SetSelectedThumb(CThumbIDList* pListSelected);

	void SetLockedMode(BOOL bLocked) { m_bLocked = bLocked; };
	BOOL GetLockedMode() { return m_bLocked; };

	void SetThumbss(const CImgList* pList, long lIDPaziente, long lIDEsame);

	void SetSelectionLimit(UINT iMaxImageSel);

	void CalcImageSpacing();

protected:

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnThumbAcquire();
	afx_msg void OnThumbImportFromDisk();
	afx_msg void OnThumbImportFromTwain();
	afx_msg void OnThumbImportFromDicom4D();
	afx_msg void OnThumbRename();
	afx_msg void OnThumbDelete();
	afx_msg void OnThumbExport();
	afx_msg void OnThumbCopyToClipboard();
	afx_msg void OnThumbCompare();
	afx_msg void OnThumbSelectAll();
	afx_msg void OnThumbPrint();
	afx_msg void OnThumbPrintPreview();
	afx_msg void OnThumbViewPregnancy();
	//afx_msg void OnBeginLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
    //afx_msg void OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

public:
	BOOL GetThumbImportFromDiskEnabled();
	BOOL GetThumbImportFromTwainEnabled();
	BOOL GetThumbImportFromDicom4DEnabled();
	BOOL GetThumbAcquireEnabled();
	BOOL GetThumbPrintEnabled();
	BOOL GetThumbPrintPreviewEnabled();
	BOOL GetThumbDeleteEnabled();
	BOOL GetThumbCompareEnabled();
	BOOL GetThumbSelectAllEnabled();
	BOOL GetThumbClipboardEnabled();
	BOOL GetThumbRenameEnabled();
	BOOL GetThumbExportEnabled();
	BOOL GetThumbSendPacsEnabled();

public:
	void RefreshItemBitmap(long lItem);
	void RefreshSelectedList();
	void CheckSelectedItem();

private:

	CThumbIDList m_listSelected;
	const CImgList* m_pImgList;
	CWnd*        m_pParentWnd;
	//CEdit        m_pEditField;
	//CString      m_newDescription;
	BOOL	     m_bPopUpActive;
	BOOL         m_bLocked;
	//int          m_itemEdited;
	UINT         m_iMaxImageSel;
	long m_lIDPaziente;
	long m_lIDEsame;

	CImageList m_tctrlImageList;
};

#endif /* _THUMBCTRLEX_H_ */