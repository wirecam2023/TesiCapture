#include "stdafx.h"
#include "Endox.h"
#include "SetupUnitaTCPDlg.h"

#include "Common.h"
#include "UnitaTCPSet.h"
#include "EditUnitaTCPDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CSetupUnitaTCPDlg, CDialog)

CSetupUnitaTCPDlg::CSetupUnitaTCPDlg(CWnd* pParent)
: CDialog(CSetupUnitaTCPDlg::IDD, pParent)
{
	CString sConnect = theApp.m_dbEndox.GetDecryptedConnectionString();
	sConnect.MakeUpper();
	m_bIsOracle = sConnect.Find("ORACLE") > 0;
}

CSetupUnitaTCPDlg::~CSetupUnitaTCPDlg()
{
}

BEGIN_MESSAGE_MAP(CSetupUnitaTCPDlg, CDialog)

	ON_BN_CLICKED(IDC_BTN_CHIUDI, OnBnClickedBtnChiudi)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBnClickedBtnEdt)
	ON_BN_CLICKED(IDC_BTN_NEW, OnBnClickedBtnNew)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemchangedList)

END_MESSAGE_MAP()

void CSetupUnitaTCPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_CHIUDI, m_ctrlBtnChiudi);
	DDX_Control(pDX, IDC_BTN_DEL, m_ctrlBtnDel);
	DDX_Control(pDX, IDC_BTN_EDT, m_ctrlBtnEdt);
	DDX_Control(pDX, IDC_BTN_NEW, m_ctrlBtnNew);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);
}

void CSetupUnitaTCPDlg::OnCancel()
{
}

BOOL CSetupUnitaTCPDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlList.InsertColumn(0, theApp.GetMessageString(IDS_DESCRIZIONE));
	m_ctrlList.InsertColumn(1, theApp.GetMessageString(IDS_ENDPOINT));

	//

	RiempiLista(0);

	//

	theApp.LocalizeDialog(this, CSetupUnitaTCPDlg::IDD, "SetupUnitaTCPDlg");
	return TRUE;
}

void CSetupUnitaTCPDlg::OnOK()
{
}

void CSetupUnitaTCPDlg::RiempiLista(long lIDToSel)
{
	m_ctrlList.SetRedraw(FALSE);
	m_ctrlList.DeleteAllItems();

	int nRowToSel = -1;

	CUnitaTCPSet setTemp;
	setTemp.SetSortRecord("Descrizione");
	if (setTemp.OpenRecordset("CSetupUnitaTCPDlg::RiempiLista"))
	{
		int nIndex = 0;
		while (!setTemp.IsEOF())
		{
			m_ctrlList.InsertItem(nIndex, setTemp.m_sDescrizione);
			m_ctrlList.SetItemData(nIndex, setTemp.m_lID);

			m_ctrlList.SetItemText(nIndex, 1, setTemp.m_sEndpoint);

			if (setTemp.m_lID == lIDToSel)
				nRowToSel = nIndex;

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CSetupUnitaTCPDlg::RiempiLista");
	}

	if (nRowToSel >= 0)
		m_ctrlList.SetItemState(nRowToSel, LVIS_SELECTED, LVIS_SELECTED);

	m_ctrlList.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetRedraw(TRUE);
}

void CSetupUnitaTCPDlg::OnBnClickedBtnChiudi()
{
	if (m_ctrlBtnChiudi.IsWindowEnabled())
		CDialog::OnOK();
}

void CSetupUnitaTCPDlg::OnBnClickedBtnNew()
{
	CEditUnitaTCPDlg dlg(this, m_bIsOracle, 0);
	if (dlg.DoModal() == IDOK)
		RiempiLista(dlg.GetLastAdd());
}

void CSetupUnitaTCPDlg::OnBnClickedBtnEdt()
{
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nItem = m_ctrlList.GetNextSelectedItem(pos);
		if (nItem >= 0)
		{
			long lRowID = m_ctrlList.GetItemData(nItem);
			if (CEditUnitaTCPDlg(this, m_bIsOracle, lRowID).DoModal() == IDOK)
				RiempiLista(lRowID);
		}
	}
}

void CSetupUnitaTCPDlg::OnBnClickedBtnDel()
{
	if (AfxMessageBox(theApp.GetMessageString(IDS_CONFIRM_DELETE_CODE), MB_YESNO | MB_ICONSTOP) == IDYES)
	{
		POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
		if (pos != NULL)
		{
			int nItem = m_ctrlList.GetNextSelectedItem(pos);
			if (nItem >= 0)
			{
				long lUnitaId = m_ctrlList.GetItemData(nItem);
				CUnitaTCPSet().SetEliminato(lUnitaId);
			}
		}

		RiempiLista(0);
	}
}

void CSetupUnitaTCPDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	BOOL bSelected = (m_ctrlList.GetFirstSelectedItemPosition() != NULL);
	m_ctrlBtnEdt.EnableWindow(bSelected);
	m_ctrlBtnDel.EnableWindow(bSelected);

	*pResult = 0;
}
