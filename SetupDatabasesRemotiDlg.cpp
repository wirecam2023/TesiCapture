#include "stdafx.h"
#include "Endox.h"
#include "SetupDatabasesRemotiDlg.h"

#include "Common.h"
#include "DatabasesSet.h"
#include "EditDatabaseConnectionStringDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CSetupDatabasesRemotiDlg, CDialog)

CSetupDatabasesRemotiDlg::CSetupDatabasesRemotiDlg(CWnd* pParent)
	: CDialog(CSetupDatabasesRemotiDlg::IDD, pParent)
{
	CString sConnect = theApp.m_dbEndox.GetDecryptedConnectionString();
	sConnect.MakeUpper();
	m_bIsOracle = sConnect.Find("ORACLE") > 0;
}

CSetupDatabasesRemotiDlg::~CSetupDatabasesRemotiDlg()
{
}

BEGIN_MESSAGE_MAP(CSetupDatabasesRemotiDlg, CDialog)

	ON_BN_CLICKED(IDC_BTN_CHIUDI, OnBnClickedBtnChiudi)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBnClickedBtnEdt)
	ON_BN_CLICKED(IDC_BTN_NEW, OnBnClickedBtnNew)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemchangedList)

END_MESSAGE_MAP()

void CSetupDatabasesRemotiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_CHIUDI, m_ctrlBtnChiudi);
	DDX_Control(pDX, IDC_BTN_DEL, m_ctrlBtnDel);
	DDX_Control(pDX, IDC_BTN_EDT, m_ctrlBtnEdt);
	DDX_Control(pDX, IDC_BTN_NEW, m_ctrlBtnNew);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);
}

void CSetupDatabasesRemotiDlg::OnCancel()
{
}

BOOL CSetupDatabasesRemotiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlList.InsertColumn(0, theApp.GetMessageString(IDS_DESCRIZIONE));
	m_ctrlList.InsertColumn(1, theApp.GetMessageString(IDS_STRINGADICONNESSIONE));

	//

	RiempiLista(0);

	//

	theApp.LocalizeDialog(this, CSetupDatabasesRemotiDlg::IDD, "SetupDatabasesRemotiDlg");
	return TRUE;
}

void CSetupDatabasesRemotiDlg::OnOK()
{
}

void CSetupDatabasesRemotiDlg::RiempiLista(long lIDToSel)
{
	m_ctrlList.SetRedraw(FALSE);
	m_ctrlList.DeleteAllItems();

	int nRowToSel = -1;

	CDatabasesSet setTemp;
	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CSetupDatabasesRemotiDlg::RiempiLista"))
	{
		int nIndex = 0;
		while (!setTemp.IsEOF())
		{
			m_ctrlList.InsertItem(nIndex, setTemp.m_sDescrizione);
			m_ctrlList.SetItemData(nIndex, setTemp.m_lID);

			m_ctrlList.SetItemText(nIndex, 1, ComponiStringaConnessione(m_bIsOracle, setTemp.m_sOracleDriver, setTemp.m_sServerDBQ, setTemp.m_sUsername, setTemp.m_sPassword));

			if (setTemp.m_lID == lIDToSel)
				nRowToSel = nIndex;

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CSetupDatabasesRemotiDlg::RiempiLista");
	}

	if (nRowToSel >= 0)
		m_ctrlList.SetItemState(nRowToSel, LVIS_SELECTED, LVIS_SELECTED);

	m_ctrlList.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetRedraw(TRUE);
}

void CSetupDatabasesRemotiDlg::OnBnClickedBtnChiudi()
{
	if (m_ctrlBtnChiudi.IsWindowEnabled())
		CDialog::OnOK();
}

void CSetupDatabasesRemotiDlg::OnBnClickedBtnNew()
{
	CEditDatabaseConnectionStringDlg dlg(this, m_bIsOracle, 0);
	if (dlg.DoModal() == IDOK)
		RiempiLista(dlg.GetLastAdd());
}

void CSetupDatabasesRemotiDlg::OnBnClickedBtnEdt()
{
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nItem = m_ctrlList.GetNextSelectedItem(pos);
		if (nItem >= 0)
		{
			long lRowID = m_ctrlList.GetItemData(nItem);
			if (CEditDatabaseConnectionStringDlg(this, m_bIsOracle, lRowID).DoModal() == IDOK)
				RiempiLista(lRowID);
		}
	}
}

void CSetupDatabasesRemotiDlg::OnBnClickedBtnDel()
{
	CString sMessage;
}

void CSetupDatabasesRemotiDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	BOOL bSelected = (m_ctrlList.GetFirstSelectedItemPosition() != NULL);
	m_ctrlBtnEdt.EnableWindow(bSelected);
	m_ctrlBtnDel.EnableWindow(bSelected);

	*pResult = 0;
}
