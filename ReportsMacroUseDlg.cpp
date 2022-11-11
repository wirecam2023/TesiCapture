#include "stdafx.h"
#include "Endox.h"
#include "ReportsMacroUseDlg.h"

#include "ReportsMacroSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CReportsMacroUseDlg, CDialog)

CReportsMacroUseDlg::CReportsMacroUseDlg(CWnd* pParent)
	: CDialog(CReportsMacroUseDlg::IDD, pParent)
{
	m_lIDMacro = 0;
}

CReportsMacroUseDlg::~CReportsMacroUseDlg()
{
}

BEGIN_MESSAGE_MAP(CReportsMacroUseDlg, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_MACRO, OnLvnItemchangedList)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_MACRO, OnNMDblclkListMacro)
END_MESSAGE_MAP()

void CReportsMacroUseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);

	DDX_Control(pDX, IDC_LIST_MACRO, m_ctrlList);
}

BOOL CReportsMacroUseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlList.InsertColumn(0, "");
	m_ctrlList.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

	RiempiLista();

	theApp.LocalizeDialog(this, CReportsMacroUseDlg::IDD, "ReportsMacroUseDlg");
	return TRUE;
}

void CReportsMacroUseDlg::OnOK()
{
	if (m_ctrlBtnOK.IsWindowEnabled() && (m_lIDMacro > 0))
		CDialog::OnOK();
}

void CReportsMacroUseDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	BOOL bOK = FALSE;
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();

	m_lIDMacro = 0;

	if (pos != NULL)
	{
		int nItem = m_ctrlList.GetNextSelectedItem(pos);

		if (nItem >= 0)
		{
			m_lIDMacro = (long)m_ctrlList.GetItemData(nItem);
			bOK = TRUE;
		}
	}

	m_ctrlBtnOK.EnableWindow(bOK);
}

void CReportsMacroUseDlg::OnNMDblclkListMacro(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnOK();
	*pResult = 0;
}

void CReportsMacroUseDlg::RiempiLista()
{
	BeginWaitCursor();
	m_ctrlList.SetRedraw(FALSE);

	m_ctrlList.DeleteAllItems();

	int nItem = 0;

	CReportsMacroSet setMacro;
	setMacro.SetSortRecord("Descrizione");
	if (setMacro.OpenRecordset("CReportsMacroUseDlg::RiempiLista"))
	{
		while(!setMacro.IsEOF())
		{
			m_ctrlList.InsertItem(nItem, setMacro.m_sDescrizione);
			m_ctrlList.SetItemData(nItem, setMacro.m_lID);

			nItem++;
			setMacro.MoveNext();
		}

		setMacro.CloseRecordset("CReportsMacroUseDlg::RiempiLista");
	}

	m_ctrlList.SetRedraw(TRUE);
	EndWaitCursor();
}

long CReportsMacroUseDlg::GetIDMacro()
{
	return m_lIDMacro;
}
