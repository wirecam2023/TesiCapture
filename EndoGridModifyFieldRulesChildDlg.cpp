#include "stdafx.h"
#include "Endox.h"
#include "EndoGridModifyFieldRulesChildDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEndoGridModifyFieldRulesChildDlg, CXTResizeDialog)

CEndoGridModifyFieldRulesChildDlg::CEndoGridModifyFieldRulesChildDlg(long lItemSelectedID, long lIDEtichetta, BOOL bItemCategoriesCheck, CPoint point, CWnd* pParentWnd)
: CXTResizeDialog(CEndoGridModifyFieldRulesChildDlg::IDD, pParentWnd)
{
	m_lIDEtichetta = lIDEtichetta;
	m_lItemSelectedID = lItemSelectedID;
	m_bItemCategoriesCheck = bItemCategoriesCheck;
	m_ptStart = point;
	m_bCanExit = FALSE;
	m_hItemSelected = NULL;
}

CEndoGridModifyFieldRulesChildDlg::~CEndoGridModifyFieldRulesChildDlg(void)
{
}

void CEndoGridModifyFieldRulesChildDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE, m_ctrlTree);
}

BEGIN_MESSAGE_MAP(CEndoGridModifyFieldRulesChildDlg, CXTResizeDialog)
	ON_NOTIFY(NM_CLICK, IDC_TREE, OnItemClicked)
	ON_MESSAGE(WM_USER + 1, OnItemChecked)
END_MESSAGE_MAP()

// CModifyFieldRulesChildDlg message handlers

BOOL CEndoGridModifyFieldRulesChildDlg::OnInitDialog()
{
	CXTResizeDialog::OnInitDialog();

	SetResize(IDC_TREE, 0, 0, 1, 1);

	CRect rect;
	GetWindowRect(&rect);

	CDC* pDC = GetDC();
	int iScreenY = pDC->GetDeviceCaps(VERTRES);
	ReleaseDC(pDC);

	if (m_ptStart.y + rect.Height() > iScreenY)
		m_ptStart.y = iScreenY - rect.Height();

	SetWindowPos(NULL,
		m_ptStart.x,
		m_ptStart.y,
		0,
		0,
		SWP_NOZORDER | SWP_NOSIZE);

	m_ctrlTree.ModifyStyle(TVS_CHECKBOXES, 0);
	m_ctrlTree.ModifyStyle(0, TVS_CHECKBOXES);

	BeginWaitCursor();
	FillTree();
	EndWaitCursor();

	theApp.LocalizeDialog(this, CEndoGridModifyFieldRulesChildDlg::IDD, "EndoGridModifyFieldRulesChildDlg");
	return TRUE;
}

void CEndoGridModifyFieldRulesChildDlg::OnItemClicked(NMHDR* pNMHDR, LRESULT* pResult)
{
	POINT pt;
	GetCursorPos(&pt);
	m_ctrlTree.ScreenToClient(&pt);

	TVHITTESTINFO hti;
	hti.pt.x = pt.x;
	hti.pt.y = pt.y;
	m_ctrlTree.HitTest(&hti);

	if (hti.flags & TVHT_ONITEMSTATEICON)
		PostMessage(WM_USER + 1, (WPARAM)hti.hItem);

	*pResult = 0;
}

LRESULT CEndoGridModifyFieldRulesChildDlg::OnItemChecked(WPARAM wParam, LPARAM lParam)
{
	HTREEITEM hItem = (HTREEITEM)wParam;
	if (m_ctrlTree.GetCheck(hItem))
	{
		m_lItemSelectedID = m_ctrlTree.GetItemData(hItem);
		m_hItemSelected = hItem;

		if (m_lItemSelectedID > 0)
		{
			PostMessage(WM_COMMAND, IDOK);
			m_bCanExit = TRUE;
		}
	}

	return 0;
}

void CEndoGridModifyFieldRulesChildDlg::OnOK()
{
	if (m_bCanExit)
		CDialog::OnOK();
}

long CEndoGridModifyFieldRulesChildDlg::GetItemSelectedID()
{
	return m_lItemSelectedID;
}

void CEndoGridModifyFieldRulesChildDlg::SetItemAsRoot(HTREEITEM hItem)
{
	if (m_ctrlTree.GetChildItem(hItem))
	{
		m_ctrlTree.Expand(hItem, TVE_EXPAND);
		m_ctrlTree.SetItemState(hItem, 0, TVIS_STATEIMAGEMASK);
	}
	else
		m_ctrlTree.DeleteItem(hItem);
}

void CEndoGridModifyFieldRulesChildDlg::FillTree()
{
	HTREEITEM hItem = m_ctrlTree.InsertItem("");
	InsertUserFields(theApp.m_lLastGridCLVersion, hItem);
	SetItemAsRoot(hItem);

	if (m_hItemSelected)
		m_ctrlTree.EnsureVisible(m_hItemSelected);
	else
		m_ctrlTree.EnsureVisible(m_ctrlTree.GetRootItem());
}

void CEndoGridModifyFieldRulesChildDlg::InsertUserFields(long lVersionID, HTREEITEM hItemParent)
{
	if (lVersionID == 0)
		return;

	if (m_ctrlTree.GetItemData(hItemParent) == 0)
	{
		CEndoGridCLParameterSet setCategory(TRUE);
		CString strFilter;
		strFilter.Format("(idpadre IS NULL or idpadre < 0) AND IDETICHETTA_GRIDCL = %li AND idversione = %li",
			m_lIDEtichetta,
			lVersionID);
		setCategory.SetOpenFilter(strFilter);
		setCategory.SetSortRecord("ordine");

		if (setCategory.OpenRecordset("CEndoGridModifyFieldRulesChildDlg::InsertUserFields"))
		{
			while (!setCategory.IsEOF())
			{
				CString str = setCategory.m_sParameterName;
				if (!setCategory.m_sNotes.IsEmpty())
					str += " (" + setCategory.m_sNotes + ")";

				HTREEITEM hItem = m_ctrlTree.InsertItem(str, hItemParent);
				m_ctrlTree.SetItemData(hItem, setCategory.m_lId);

				if (m_lItemSelectedID == setCategory.m_lId)
				{
					m_ctrlTree.SetCheck(hItem);
					m_hItemSelected = hItem;
				}

				InsertUserFields(lVersionID, hItem);

				if (!m_bItemCategoriesCheck)
					SetItemAsRoot(hItem);

				if (setCategory.m_bExpanded)
					m_ctrlTree.Expand(hItem, TVE_EXPAND);
				else
					m_ctrlTree.Expand(hItem, TVE_COLLAPSE);

				setCategory.MoveNext();
			}

			setCategory.CloseRecordset("CEndoGridModifyFieldRulesChildDlg::InsertUserFields");
		}		
	}
	else
	{
		CEndoGridCLParameterSet setItems(TRUE);
		CString strFilter;

		strFilter.Format("idpadre = %li AND IDETICHETTA_GRIDCL = %li AND idversione = %li",
			m_ctrlTree.GetItemData(hItemParent),
			m_lIDEtichetta,
			lVersionID);
		setItems.SetOpenFilter(strFilter);
		setItems.SetSortRecord("ordine");
		
		if (setItems.OpenRecordset("CEndoGridModifyFieldRulesChildDlg::InsertUserFields"))
		{
			while (!setItems.IsEOF())
			{
				CString str = setItems.m_sParameterName;
				if (!setItems.m_sNotes.IsEmpty())
					str += " (" + setItems.m_sNotes + ")";

				HTREEITEM hItem = m_ctrlTree.InsertItem(str, hItemParent);
				m_ctrlTree.SetItemData(hItem, setItems.m_lId);

				if (m_lItemSelectedID == setItems.m_lId)
				{
					m_ctrlTree.SetCheck(hItem);
					m_hItemSelected = hItem;
				}

				InsertUserFields(lVersionID, hItem);

				if (setItems.m_bExpanded)
					m_ctrlTree.Expand(hItem, TVE_EXPAND);
				else
					m_ctrlTree.Expand(hItem, TVE_COLLAPSE);

				setItems.MoveNext();
			}

			setItems.CloseRecordset("CEndoGridModifyFieldRulesChildDlg::InsertUserFields");
		}
	}
}
