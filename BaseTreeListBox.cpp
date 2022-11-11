#include "stdafx.h"
#include "Endox.h"
#include "BaseTreeListBox.h"

#include "BaseTreeObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC (CBaseTreeListBox, CListBox)

CBaseTreeListBox::CBaseTreeListBox() 
	: CListBox()
{
	m_nHScrollWidth = 0;
	m_strSeparatorDesc  = " ";
	m_strSeparatorCode  = ".";
}

CBaseTreeListBox::~CBaseTreeListBox()
{
}

BEGIN_MESSAGE_MAP(CBaseTreeListBox, CListBox)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

int CBaseTreeListBox::AddTreeItem(CBaseTreeObject* pData)
{
	int posiz =	CListBox::AddString("");
	
	if (posiz == LB_ERR)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_BASETREELISTBOX_ERROR01));
		return -1;
	}

	int result = CListBox::SetItemData(posiz, (DWORD) pData);
	
	if (result == LB_ERR)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_BASETREELISTBOX_ERROR02));
		return -1;
	}
	
	return posiz;
}

int	CBaseTreeListBox::InsTreeItem(int nIndex, CBaseTreeObject* pData)
{
	int posiz =	CListBox::InsertString(nIndex, "");

	if (posiz == LB_ERR)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_BASETREELISTBOX_ERROR03));
		return -1;
	}
	
	if (posiz == LB_ERRSPACE)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_BASETREELISTBOX_ERROR04));
		return -1;
	}

	int result = CListBox::SetItemData(posiz, (DWORD) pData);
	
	if (result == LB_ERR)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_BASETREELISTBOX_ERROR05));
		return -1;
	}
	
	return posiz;
}

CBaseTreeObject* CBaseTreeListBox::GetTreeItemDataPtr(int nIndex)
{
	DWORD info = CListBox::GetItemData(nIndex);

	if (info == LB_ERR)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_BASETREELISTBOX_ERROR06));
		return NULL;
	}
	else
		return (CBaseTreeObject*) info;
}

int CBaseTreeListBox::SetTreeItemDataPtr(int nIndex, CBaseTreeObject* pData)
{
	int result = CListBox::SetItemData(nIndex, (DWORD) pData);
	
	if (result == LB_ERR)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_BASETREELISTBOX_ERROR07));
		return -1;
	}
	
	return result;
}

CString CBaseTreeListBox::GetCurDataPathSel(BOOL bCumulate)
{
	CString	PathStr = "";
	int		posiz	= GetCurSel();	// CListBox::
    int		curLev	= 0;

	if (posiz == LB_ERR)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_BASETREELISTBOX_ERROR08));
		return "";
	}

    CBaseTreeObject* pData = GetTreeItemDataPtr(posiz);

	if (!pData)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_BASETREELISTBOX_ERROR09));
		return "";
	}

	curLev = pData->livello;
	
	if (bCumulate)
	{
		for(int i = curLev; i >= 0; i--)
		{
			if (IsValidLevel(pData))
			{
				CString strCod = GetLevelStr(pData);
				
				if (strCod != "")
				{
					if (PathStr == "")
						PathStr = strCod;
					else
						PathStr = strCod + m_strSeparatorCode + PathStr;
				}
			}
			
			while (curLev <= pData->livello && posiz > 0)
			{
				pData = GetTreeItemDataPtr(--posiz);
				
				if (!pData)
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_BASETREELISTBOX_ERROR10));
					return "";
				}
			}
			curLev = pData->livello;
		}
	}
	else
	{
		PathStr = GetLevelStr(pData);
	}
	
	return PathStr;
}

CString CBaseTreeListBox::GetCurDesPathSel(BOOL bCumulate)
{
	CString	PathStr = "";
	int		posiz	= GetCurSel();	// CListBox::
    int		curLev	= 0;

	if (posiz == LB_ERR)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_BASETREELISTBOX_ERROR11));
		return "";
	}

    CBaseTreeObject* pData =  GetTreeItemDataPtr(posiz);

	if (!pData)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_BASETREELISTBOX_ERROR12));
		return "";
	}
    
    curLev = pData->livello;
    	
	if (bCumulate)
	{
		for(int i = curLev; i >= 0; i--)
		{
			BOOL bAddLevel = TRUE;

			bAddLevel = curLev || IsValidLevel(pData);

			if (bAddLevel)
			{
				if (PathStr == "")
					PathStr = GetDescritionStr(pData);
				else
					PathStr = GetDescritionStr(pData) + m_strSeparatorDesc + PathStr;
			}

			while (curLev <= pData->livello && posiz > 0)
			{
				pData =  GetTreeItemDataPtr(--posiz);
				
				if (!pData)
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_BASETREELISTBOX_ERROR13));
					return "";
				}
			}
			curLev = pData->livello;
		}
	}
	else
	{
		PathStr = GetDescritionStr(pData);
	}
	
	return PathStr;
}

/////////////////////////////////////////////////////////////////////////////
// CBaseTreeListBox	message handlers
void CBaseTreeListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasure)
{
	lpMeasure->itemHeight = 8;
}

void CBaseTreeListBox::DrawItem(LPDRAWITEMSTRUCT lpDraw)
{
    if (lpDraw)
	{
		int nID = (int)lpDraw->itemID;

		if (nID >= 0)
		{
			CString		strData;
			int			nLength;
			CRect		rectArea = lpDraw->rcItem;
			CDC*		pDC = CDC::FromHandle(lpDraw->hDC);
			int			pTabArray[] = {18};
			COLORREF	BkColor = GetSysColor(COLOR_WINDOW);
			COLORREF	TxColor = GetSysColor(COLOR_WINDOWTEXT);

			PrepareDataToShow((CBaseTreeObject*) lpDraw->itemData);

			strData = ((CBaseTreeObject*) lpDraw->itemData)->strToShow;
			nLength = strData.GetLength();
			
			if (lpDraw->itemAction & ODA_DRAWENTIRE)
			{
				CBrush		brush;
				
				BkColor = GetSysColor(COLOR_WINDOW);
				TxColor = GetSysColor(COLOR_WINDOWTEXT);
				
				brush.CreateSolidBrush(BkColor);
				
				pDC->FillRect     (rectArea, &brush);
				pDC->SetBkColor   (BkColor);
				pDC->SetTextColor (TxColor);
				pDC->TabbedTextOut(rectArea.left, rectArea.top + 1, strData, nLength, 1, &pTabArray[0], 0);

				brush.DeleteObject();
			}

			if ((lpDraw->itemState & ODS_SELECTED) &&
				(lpDraw->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
			{
				CBrush		brush;
				
				BkColor = GetSysColor(COLOR_HIGHLIGHT);
				TxColor = GetSysColor(COLOR_HIGHLIGHTTEXT);
				
				brush.CreateSolidBrush(BkColor);
				
				pDC->FillRect     (rectArea, &brush);
				pDC->SetBkColor   (BkColor);
				pDC->SetTextColor (TxColor);
				pDC->TabbedTextOut(rectArea.left, rectArea.top + 1, strData, nLength, 1, &pTabArray[0], 0);

				brush.DeleteObject();
			}

			if (!(lpDraw->itemState & ODS_SELECTED) &&
				(lpDraw->itemAction & ODA_SELECT))
			{
				// Item has been de-selected -- remove frame

				CBrush		brush;

				BkColor = GetSysColor(COLOR_WINDOW);
				TxColor = GetSysColor(COLOR_WINDOWTEXT);

				brush.CreateSolidBrush(BkColor);
				
				pDC->FillRect     (rectArea, &brush);
				pDC->SetBkColor   (BkColor);
				pDC->SetTextColor (TxColor);
				pDC->TabbedTextOut(rectArea.left, rectArea.top + 1, strData, nLength, 1, &pTabArray[0], 0);

				brush.DeleteObject();
			}
		}
	}
}

void CBaseTreeListBox::OnDestroy()
{
	int counter = GetCount();
	
	if (counter == LB_ERR)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_BASETREELISTBOX_ERROR14));
		return;
	}

	while(counter)
	{
		DWORD info = GetItemData(counter - 1);
		
		if (info == LB_ERR)
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_BASETREELISTBOX_ERROR15));
			return;
		}

		delete (CBaseTreeObject*) info;

		counter = DeleteString(counter - 1);
		
		if (counter == LB_ERR)
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_BASETREELISTBOX_ERROR16));
			return;
		}
	}
	
	CListBox::OnDestroy();
}

void CBaseTreeListBox::AdjustHScrollBar()
{

	int counter = GetCount();
	
	if (counter == LB_ERR)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_BASETREELISTBOX_ERROR17));
		return;
	}

	m_nHScrollWidth = 0;
	counter--;

	while(counter > -1)
	{
		DWORD info = GetItemData(counter--);
		
		if (info == LB_ERR)
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_BASETREELISTBOX_ERROR18));
			return;
		}

		if (m_nHScrollWidth < (((CBaseTreeObject*) info)->larghezza))
		{
			m_nHScrollWidth = ((CBaseTreeObject*) info)->larghezza;
		}
	}
			
	SetHorizontalExtent(m_nHScrollWidth);
}