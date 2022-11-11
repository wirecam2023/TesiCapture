#include "stdafx.h"
#include "Endox.h"
#include "FasiConfigDlg.h"

#include "EsamiDoc.h"
#include "EsamiView.h"
#include "FasiGruppiConfigDlg.h"
#include "FasiEsameSet.h"
#include "FasiEsameGruppiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CFasiConfigDlg::CFasiConfigDlg(CEsamiView* pEsamiView)
	: CResizableDialog(CFasiConfigDlg::IDD), m_ctrlList(FALSE, FALSE, FALSE)
{
	m_clColor = GetSysColor(COLOR_BTNFACE);
	m_lSelectedID = 0;
	m_bEditAdd = FALSE;

	m_pEsamiView = pEsamiView;
}

CFasiConfigDlg::~CFasiConfigDlg()
{	
}

BEGIN_MESSAGE_MAP(CFasiConfigDlg, CResizableDialog)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, &CFasiConfigDlg::OnLvnItemchangedList)

	ON_WM_LBUTTONUP()
	ON_WM_PAINT()

	ON_BN_CLICKED(IDC_ADD, &CFasiConfigDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_EDIT, &CFasiConfigDlg::OnBnClickedEdit)
	ON_BN_CLICKED(IDC_DEL, &CFasiConfigDlg::OnBnClickedDel)
	ON_BN_CLICKED(IDC_ABORT, &CFasiConfigDlg::OnBnClickedAbort)
	ON_BN_CLICKED(IDC_SAVE, &CFasiConfigDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_SEARCH, &CFasiConfigDlg::OnBnClickedSearch)
	ON_BN_CLICKED(IDC_GROUP_CONFIG, &CFasiConfigDlg::OnBnClickedGroupConfig)
END_MESSAGE_MAP()

void CFasiConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ADD, m_ctrlBtnNew);
	DDX_Control(pDX, IDC_EDIT, m_ctrlBtnEdit);
	DDX_Control(pDX, IDC_DEL, m_ctrlBtnDelete);
	DDX_Control(pDX, IDC_SAVE, m_ctrlBtnSave);
	DDX_Control(pDX, IDC_ABORT, m_ctrlBtnAbort);
	DDX_Control(pDX, IDC_GROUP_CONFIG, m_ctrlBtnGruppiConfig);

	DDX_Control(pDX, IDC_EDIT_DESC, m_ctrlEditDescrizione);
	DDX_Control(pDX, IDC_EDIT_REPORT, m_ctrlEditReport);
	DDX_Control(pDX, IDC_SEARCH, m_ctrlBtnSearch);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);

	DDX_Control(pDX, IDCANCEL, m_ctrlBtnExit);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);

	DDX_Control(pDX, IDC_CHECK_LOGIN, m_ctrlChkLogin);
}

BOOL CFasiConfigDlg::OnInitDialog()
{
	CResizableDialog::OnInitDialog();

	//Header
	int index = 0;
	m_ctrlList.InsertColumn(index++, "Descrizione");
	m_ctrlList.InsertColumn(index++, "Colore");
	m_ctrlList.InsertColumn(index++, "Report");
	m_ctrlList.InsertColumn(index++, "Gruppi autorizzati");

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	AddAnchor(IDC_LIST, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDC_STATIC_1, CSize(0, 100), CSize(100, 100));
	AddAnchor(IDC_STATIC_2, CSize(0, 100), CSize(100, 100));
	AddAnchor(IDC_STATIC_3, CSize(0, 100), CSize(100, 100));
	// AddAnchor(IDC_STATIC_4, CSize(0, 100), CSize(100, 100));
	AddAnchor(IDC_EDIT_DESC, CSize(0, 100), CSize(100, 100));
	AddAnchor(IDC_EDIT_REPORT, CSize(0, 100), CSize(100, 100));
	AddAnchor(IDC_SEARCH, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDC_STATIC_COLOR, CSize(0, 100), CSize(100, 100));
	AddAnchor(IDC_ADD, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_EDIT, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_DEL, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_GROUP_CONFIG, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_SAVE, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDC_ABORT, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDC_CHECK_LOGIN, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDCANCEL, CSize(100, 100), CSize(100, 100));	

	//

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	RiempiLista();
	m_ctrlChkLogin.SetCheck(theApp.m_bChiusuraFaseLogin);

	theApp.LocalizeDialog(this, CFasiConfigDlg::IDD, "FasiConfigDlg");
	return TRUE;
}


void CFasiConfigDlg::OnOK()
{
}

void CFasiConfigDlg::OnCancel()
{
	theApp.m_bChiusuraFaseLogin = m_ctrlChkLogin.GetCheck();
	CEsamiDoc *doc = (CEsamiDoc*)m_pEsamiView->GetDocument();
	doc->OnSalvaConfigurazioneFasi();

	CResizableDialog::OnCancel();
}

void CFasiConfigDlg::RiempiLista()
{
	m_ctrlList.DeleteAllItems();

	//Dati
	CFasiEsameSet set;
	if (set.OpenRecordset("CFasiConfigDlg::RiempiLista"))
	{
		while (!set.IsEOF())
		{
			int iItem = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), set.m_sDescrizione);
			m_ctrlList.SetSubItemBkColor(iItem, 1, set.m_lColor);
			m_ctrlList.SetItemText(iItem, 2, set.m_sReport);
			m_ctrlList.SetItemText(iItem, 3, CFasiEsameGruppiSet().GetGruppiListAsString(set.m_lID));

			m_ctrlList.SetItemData(iItem, set.m_lID);

			set.MoveNext();
		}

		set.CloseRecordset("CFasiConfigDlg::RiempiLista");
	}

	ResizeHeader();

	m_ctrlBtnNew.EnableWindow(TRUE);
	m_ctrlBtnEdit.EnableWindow(FALSE);
	m_ctrlBtnDelete.EnableWindow(FALSE);
	m_ctrlBtnGruppiConfig.EnableWindow(FALSE);
	m_ctrlBtnSave.EnableWindow(FALSE);
	m_ctrlBtnAbort.EnableWindow(FALSE);
	m_ctrlBtnExit.EnableWindow(TRUE);

	m_ctrlEditDescrizione.SetWindowText("");
	m_clColor = GetSysColor(COLOR_BTNFACE);
	m_ctrlEditReport.SetWindowText("");

	CRect rect;
	GetDlgItem(IDC_STATIC_COLOR)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	InvalidateRect(&rect);

	m_lSelectedID = 0;
}


void CFasiConfigDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	m_clColor = GetSysColor(COLOR_BTNFACE);

	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		m_ctrlBtnNew.EnableWindow(TRUE);
		m_ctrlBtnEdit.EnableWindow(TRUE);
		m_ctrlBtnDelete.EnableWindow(TRUE);
		m_ctrlBtnGruppiConfig.EnableWindow(TRUE);
		m_ctrlBtnSave.EnableWindow(FALSE);
		m_ctrlBtnAbort.EnableWindow(FALSE);
		m_ctrlBtnExit.EnableWindow(TRUE);

		int index = m_ctrlList.GetNextSelectedItem(pos);
		m_ctrlEditDescrizione.SetWindowText(m_ctrlList.GetItemText(index, 0));
		m_ctrlList.GetSubItemBkColor(index, 1, m_clColor);
		m_ctrlEditReport.SetWindowText(m_ctrlList.GetItemText(index, 2));

		m_lSelectedID = m_ctrlList.GetItemData(index);

		//Non posso cancellare le fasi di convalida e chiusura perché incastonate nel codice
		if (m_lSelectedID <= 2)
			m_ctrlBtnDelete.EnableWindow(FALSE);

	}
	else
	{
		m_ctrlBtnNew.EnableWindow(TRUE);
		m_ctrlBtnEdit.EnableWindow(FALSE);
		m_ctrlBtnDelete.EnableWindow(FALSE);
		m_ctrlBtnGruppiConfig.EnableWindow(FALSE);
		m_ctrlBtnSave.EnableWindow(FALSE);
		m_ctrlBtnAbort.EnableWindow(FALSE);
		m_ctrlBtnExit.EnableWindow(TRUE);

		m_ctrlEditDescrizione.SetWindowText("");
		m_clColor = GetSysColor(COLOR_BTNFACE);
		m_ctrlEditReport.SetWindowText("");

		m_lSelectedID = 0;
	}

	CRect rect;
	GetDlgItem(IDC_STATIC_COLOR)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	InvalidateRect(&rect);

	*pResult = 0;
}

void CFasiConfigDlg::OnPaint()
{
	CPaintDC dc(this);

	CRect rect;

	GetDlgItem(IDC_STATIC_COLOR)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	dc.FillRect(&rect, &CBrush(m_clColor));
}

void CFasiConfigDlg::OnBnClickedAdd()
{
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
		m_ctrlList.SetItemState(m_ctrlList.GetNextSelectedItem(pos), 0, LVIS_SELECTED);

	m_ctrlBtnNew.EnableWindow(FALSE);
	m_ctrlBtnEdit.EnableWindow(FALSE);
	m_ctrlBtnDelete.EnableWindow(FALSE);
	m_ctrlBtnGruppiConfig.EnableWindow(FALSE);
	m_ctrlBtnSave.EnableWindow(TRUE);
	m_ctrlBtnAbort.EnableWindow(TRUE);
	m_ctrlBtnExit.EnableWindow(FALSE);

	m_ctrlList.EnableWindow(FALSE);
	m_ctrlEditDescrizione.EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_COLOR)->EnableWindow(TRUE);
	m_ctrlEditReport.EnableWindow(TRUE);
	m_ctrlBtnSearch.EnableWindow(TRUE);

	m_bEditAdd = TRUE;
}


void CFasiConfigDlg::OnBnClickedEdit()
{
	m_ctrlBtnNew.EnableWindow(FALSE);
	m_ctrlBtnEdit.EnableWindow(FALSE);
	m_ctrlBtnDelete.EnableWindow(FALSE);
	m_ctrlBtnGruppiConfig.EnableWindow(FALSE);
	m_ctrlBtnSave.EnableWindow(TRUE);
	m_ctrlBtnAbort.EnableWindow(TRUE);
	m_ctrlBtnExit.EnableWindow(FALSE);

	m_ctrlList.EnableWindow(FALSE);
	m_ctrlEditDescrizione.EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_COLOR)->EnableWindow(TRUE);
	m_ctrlEditReport.EnableWindow(TRUE);
	m_ctrlBtnSearch.EnableWindow(TRUE);

	if (m_lSelectedID <= 2)
	{
		m_ctrlEditReport.EnableWindow(FALSE);
		m_ctrlBtnSearch.EnableWindow(FALSE);
	}

	m_bEditAdd = TRUE;
}


void CFasiConfigDlg::OnBnClickedDel()
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CONFERMA_ELIMINAZIONE), MB_YESNO) == IDNO)
		return;

	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	int itemIndex = m_ctrlList.GetNextSelectedItem(pos);

	if (itemIndex > 0)
	{
		CString sFilter;
		sFilter.Format("ID=%li", m_ctrlList.GetItemData(itemIndex));
		CFasiEsameSet set;
		set.SetOpenFilter(sFilter);

		if (set.OpenRecordset("CFasiConfigDlg::OnBnClickedDel"))
		{
			if (!set.IsEOF())
			{
				set.DeleteRecordset("CFasiConfigDlg::OnBnClickedDel");
			}

			set.CloseRecordset("CFasiConfigDlg::OnBnClickedDel");
		}
	}


	m_lSelectedID = 0;
	RiempiLista();
}


void CFasiConfigDlg::OnBnClickedAbort()
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ANNULLA_MODIFICHE), MB_YESNO) == IDNO)
		return;

	m_ctrlList.EnableWindow(TRUE);
	m_ctrlEditDescrizione.EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_COLOR)->EnableWindow(FALSE);
	m_ctrlEditReport.EnableWindow(FALSE);
	m_ctrlBtnSearch.EnableWindow(FALSE);

	m_bEditAdd = FALSE;

	RiempiLista();
}


void CFasiConfigDlg::OnBnClickedSave()
{
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_CONFERMA), MB_YESNO) == IDNO)
		return;

	CFasiEsameSet set;
	CString sFilter;

	if (m_lSelectedID == 0)
	{
		sFilter = "";
	}
	else
	{
		sFilter.Format("ID=%li", m_lSelectedID);
	}

	set.SetOpenFilter(sFilter);

	if (set.OpenRecordset("CFasiConfigDlg::OnBnClickedSave"))
	{
		if (m_lSelectedID == 0)
		{
			if (!set.AddNewRecordset("CFasiConfigDlg::OnBnClickedSave"))
			{
				return;
			}
		}
		else
		{
			if (!set.EditRecordset("CFasiConfigDlg::OnBnClickedSave"))
			{
				return;
			}
		}

		m_ctrlEditDescrizione.GetWindowText(set.m_sDescrizione);
		set.m_lColor = m_clColor;
		m_ctrlEditReport.GetWindowText(set.m_sReport);

		set.UpdateRecordset("CFasiConfigDlg::OnBnClickedSave");

		set.CloseRecordset("CFasiConfigDlg::OnBnClickedSave");
	}

	m_ctrlList.EnableWindow(TRUE);
	m_ctrlEditDescrizione.EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_COLOR)->EnableWindow(FALSE);
	m_ctrlEditReport.EnableWindow(FALSE);
	m_ctrlBtnSearch.EnableWindow(FALSE);

	m_bEditAdd = FALSE;

	RiempiLista();
}

void CFasiConfigDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CResizableDialog::OnLButtonUp(nFlags, point);

	if (!m_bEditAdd)
		return;

	CRect rect;

	GetDlgItem(IDC_STATIC_COLOR)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	if (rect.PtInRect(point))
	{
		CColorDialog dlg(m_clColor);
		if (dlg.DoModal() == IDOK)
			m_clColor = dlg.GetColor();
	}
	InvalidateRect(&rect);

}

void CFasiConfigDlg::OnBnClickedSearch()
{
	CString strTemp;

	m_ctrlEditReport.GetWindowText(strTemp);

	OPENFILENAME ofnOpenFileName;
	TCHAR szFileName[MAX_PATH] = "";
	static LPCTSTR pFilter = "File report (*.rpt)\0*.rpt\0Tutti i file (*.*)\0*.*\0\0";

	ZeroMemory(&ofnOpenFileName, sizeof(OPENFILENAME));

	strTemp.Trim();
	if (strTemp.IsEmpty())
		ofnOpenFileName.lpstrInitialDir = theApp.m_sEditRep;
	else
		ofnOpenFileName.lpstrInitialDir = strTemp;

	ofnOpenFileName.lStructSize = sizeof(OPENFILENAME);
	ofnOpenFileName.hwndOwner = m_hWnd;
	ofnOpenFileName.lpstrFile = szFileName;
	ofnOpenFileName.nMaxFile = MAX_PATH;
	ofnOpenFileName.lpstrFilter = pFilter;
	ofnOpenFileName.Flags = OFN_FILEMUSTEXIST | OFN_LONGNAMES | OFN_READONLY;

	if (GetOpenFileName(&ofnOpenFileName) != FALSE)
		strTemp.Format("%s", ofnOpenFileName.lpstrFile);

	m_ctrlEditReport.SetWindowText(strTemp);
	ResizeHeader();
}

void CFasiConfigDlg::ResizeHeader()
{
	m_ctrlList.SetColumnWidth(0, 100);
	m_ctrlList.SetColumnWidth(1, 10);
	m_ctrlList.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlList.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
}

void CFasiConfigDlg::OnBnClickedGroupConfig()
{
	CFasiGruppiConfigDlg(this, m_lSelectedID).DoModal();
	RiempiLista();
}
