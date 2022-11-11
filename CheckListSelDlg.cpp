#include "stdafx.h"
#include "Endox.h"
#include "CheckListSelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define COL_COD 0
#define COL_DESC 1

IMPLEMENT_DYNAMIC(CCheckListSelDlg, CDialog)

CCheckListSelDlg::CCheckListSelDlg(CWnd* pParent, CList<STRUCT_CHECKLIST>* pListChecklist)
	: CDialog(CCheckListSelDlg::IDD, pParent)
{
	m_pListChecklist = pListChecklist;
	m_lIDCheckList = 0;
}

CCheckListSelDlg::~CCheckListSelDlg()
{
}

BEGIN_MESSAGE_MAP(CCheckListSelDlg, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemchangedList)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnNMDblclkList)
END_MESSAGE_MAP()

void CCheckListSelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);
}

BOOL CCheckListSelDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlList.InsertColumn(COL_COD, "Codice");
	m_ctrlList.InsertColumn(COL_DESC, "Descrizione");
	RiempiLista();

	if (m_ctrlList.GetItemCount() == 0)
	{
		// non c'è alcuna check-list //

		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CHECKLIST_SEL_ERR));
		EndDialog(IDCANCEL);
	}
	else
	{
		if (m_ctrlList.GetItemCount() == 1)
		{
			// c'è una sola check-list quindi la seleziono automaticamente senza chiedere niente //

			m_ctrlList.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
			OnLvnItemchangedList(NULL, NULL);
			EndDialog(IDOK);
		}
		else
		{
			theApp.LocalizeDialog(this, CCheckListSelDlg::IDD, "CheckListSelDlg");
		}
	}
	return bReturn;
}

void CCheckListSelDlg::OnOK()
{
	if (m_ctrlBtnOK.IsWindowEnabled())
		CDialog::OnOK();
}

void CCheckListSelDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();

	if (pos == NULL)
	{
		m_ctrlBtnOK.EnableWindow(FALSE);

		m_lIDCheckList = 0;
	}
	else
	{
		m_ctrlBtnOK.EnableWindow(TRUE);

		m_lIDCheckList = (long)m_ctrlList.GetItemData(m_ctrlList.GetNextSelectedItem(pos));
	}
}

void CCheckListSelDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (m_lIDCheckList > 0)
		OnOK();
}

long CCheckListSelDlg::GetIDCheckList()
{
	return m_lIDCheckList;
}

void CCheckListSelDlg::RiempiLista()
{
	BeginWaitCursor();
	m_ctrlList.SetRedraw(FALSE);

	m_ctrlList.DeleteAllItems();

	int nItem = 0;
	POSITION pos = m_pListChecklist->GetHeadPosition();
	while(pos != NULL)
	{
		STRUCT_CHECKLIST tagTemp = m_pListChecklist->GetNext(pos);

		m_ctrlList.InsertItem(nItem, tagTemp.m_sCodice);
		m_ctrlList.SetItemData(nItem, (DWORD)tagTemp.m_lID);

		m_ctrlList.SetItemText(nItem, COL_DESC, tagTemp.m_sDescrizione);

		nItem++;
	}

	m_ctrlList.SetColumnWidth(COL_COD, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(COL_DESC, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlList.SetRedraw(TRUE);
	EndWaitCursor();
}