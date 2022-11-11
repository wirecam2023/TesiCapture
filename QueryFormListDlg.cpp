#include "stdafx.h"
#include "Endox.h"
#include "QueryFormListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CQueryFormListDlg, CEndoxResizableDlg)

CQueryFormListDlg::CQueryFormListDlg(CWnd* pParentWnd, CPoint ptLocation, CList<tagITEM>* pListItems, long lSelectedID, BOOL bCanImportAll)
	: CEndoxResizableDlg(CQueryFormListDlg::IDD, pParentWnd)
{
	ZeroMemory(&m_ItemSelected, sizeof(tagITEM));

	m_ptLocation = ptLocation;
	m_listItems.AddTail(pListItems);
	m_lSelectedID = lSelectedID;
	m_bCanImportAll = bCanImportAll;
}

CQueryFormListDlg::~CQueryFormListDlg()
{
}

BEGIN_MESSAGE_MAP(CQueryFormListDlg, CEndoxResizableDlg)

	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnNMDblclkList)

	ON_WM_SIZE()

END_MESSAGE_MAP()

void CQueryFormListDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST,  m_ctrlList);
}

BOOL CQueryFormListDlg::OnInitDialog()
{
	CEndoxResizableDlg::OnInitDialog();

	if (m_bCanImportAll)
		::SetWindowLong(m_ctrlList.GetSafeHwnd(), GWL_STYLE, GetWindowLong(m_ctrlList.GetSafeHwnd(), GWL_STYLE) & (~LVS_SINGLESEL));

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlList.InsertColumn(0, "Codice");
	m_ctrlList.InsertColumn(1, "Descrizione");

	theApp.LocalizeDialog(this, CQueryFormListDlg::IDD, "QueryFormListDlg");

	if (m_lpszTemplateName != MAKEINTRESOURCE(IDD_QUERY_FORM_LIST_POPUP))
	{
		CRect rect;
		GetClientRect(&rect);
		m_ctrlList.SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOZORDER);
	}

	AddAnchor(IDC_LIST, CSize(0, 0), CSize(100, 100));

	FillList();
	ResizeColumns();

	//

	CRect rectWnd;
	GetWindowRect(&rectWnd);

	//

	CRect rectTemp;
	AfxGetMainWnd()->GetWindowRect(&rectTemp);

	/*CRect rectDesk;
	HMONITOR hMonitor = MonitorFromRect(rectTemp, MONITOR_DEFAULTTONEAREST);
	if (hMonitor == NULL)
	{
		SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	}
	else
	{
		MONITORINFO mi;
		mi.cbSize = sizeof(mi);
		GetMonitorInfo(hMonitor, &mi);

		rectDesk = mi.rcWork;
	}

	//
	
	if (m_ptLocation.x + rectWnd.Width() > rectDesk.right)
		m_ptLocation.x = rectDesk.right - rectWnd.Width();
	if (m_ptLocation.y + rectWnd.Height() > rectDesk.bottom)
		m_ptLocation.y = rectDesk.bottom - rectWnd.Height();

	SetWindowPos(NULL, m_ptLocation.x, m_ptLocation.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);*/

	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	return TRUE;
}

void CQueryFormListDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnOK();
	*pResult = 0;
}

void CQueryFormListDlg::OnOK()
{
	if (m_bCanImportAll)
	{
		m_listSelected.RemoveAll();
		for (int i = 0; i < m_ctrlList.GetItemCount(); i++)
		{
			if (m_ctrlList.GetItemState(i, LVIS_SELECTED))
			{
				long lID = m_ctrlList.GetItemData(i);
				for (POSITION pos = m_listItems.GetHeadPosition(); pos;)
				{
					tagITEM item = m_listItems.GetNext(pos);
					if (item.lContatore == lID)
					{
						m_listSelected.AddTail(item);
						break;
					}
				}
			}
		}
	}
	else
	{
		int iItemSelected = -1;
		for (int i = 0; i < m_ctrlList.GetItemCount(); i++)
		{
			if (m_ctrlList.GetItemState(i, LVIS_SELECTED))
			{
				iItemSelected = i;
				break;
			}
		}

		if (iItemSelected == -1)
			return;

		long lID = m_ctrlList.GetItemData(iItemSelected);
		for (POSITION pos = m_listItems.GetHeadPosition(); pos;)
		{
			tagITEM item = m_listItems.GetNext(pos);
			if (item.lContatore == lID)
			{
				m_ItemSelected = item;
				break;
			}
		}
	}

	CDialog::OnOK();
}

void CQueryFormListDlg::OnSize(UINT nType, int cx, int cy)
{
	CEndoxResizableDlg::OnSize(nType, cx, cy);
	ResizeColumns();
}

void CQueryFormListDlg::FillList()
{
	m_ctrlList.SetRedraw(FALSE);
	m_ctrlList.DeleteAllItems();

	int nCurSel = -1;
	for (POSITION pos = m_listItems.GetHeadPosition(); pos;)
	{
		tagITEM item = m_listItems.GetNext(pos);

		int iInserted = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), item.szCodice);
		m_ctrlList.SetItemData(iInserted, item.lContatore);

		m_ctrlList.SetItemText(iInserted, 1, item.szDescrizione);

		if ((m_lSelectedID > 0) && (m_lSelectedID == item.lContatore))
			nCurSel = iInserted;
	}

	if (nCurSel >= 0)
	{
		m_ctrlList.SetItemState(nCurSel, LVIS_SELECTED, LVIS_SELECTED);
		m_ctrlList.EnsureVisible(nCurSel, FALSE);
	}

	m_ctrlList.SetRedraw(TRUE);
	m_ctrlList.SetFocus();
}

void CQueryFormListDlg::ResizeColumns()
{
	if (!m_ctrlList.GetSafeHwnd())
		return;

	CRect rect;
	m_ctrlList.GetClientRect(&rect);
	m_ctrlList.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(1, rect.Width() - m_ctrlList.GetColumnWidth(0));
}

CQueryFormListDlg::tagITEM CQueryFormListDlg::GetItemSelected() 
{ 
	ASSERT(!m_bCanImportAll);
	return m_ItemSelected;
}

void CQueryFormListDlg::GetItemsSelected(CList<CQueryFormListDlg::tagITEM>* pList)
{
	ASSERT(m_bCanImportAll);
	pList->RemoveAll();
	pList->AddTail(&m_listSelected);
}