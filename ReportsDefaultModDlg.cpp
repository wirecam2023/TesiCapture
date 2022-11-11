#include "stdafx.h"
#include "Endox.h"
#include "ReportsDefaultModDlg.h"

#include "ReportsDefaultSet.h"
#include "SediEsameSet.h"
#include "TipoEsameSet.h"
#include ".\reportsdefaultmoddlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define STATO_NONE 0
#define STATO_NEW 1
#define STATO_EDT 2

IMPLEMENT_DYNAMIC(CReportsDefaultModDlg, CDialog)

CReportsDefaultModDlg::CReportsDefaultModDlg(CWnd* pParent)
	: CDialog(CReportsDefaultModDlg::IDD, pParent)
{
	m_nStato = STATO_NONE;

	m_sSede = "";
	m_lTipoEsame = 0;
}

CReportsDefaultModDlg::~CReportsDefaultModDlg()
{
}

BEGIN_MESSAGE_MAP(CReportsDefaultModDlg, CDialog)

	ON_WM_CTLCOLOR()

	ON_LBN_SELCHANGE(IDC_LIST_SEDI, OnLbnSelchangeListSedi)
	ON_LBN_SELCHANGE(IDC_LIST_ESAMI, OnLbnSelchangeListEsami)

	ON_BN_CLICKED(IDC_BTN_NEW, OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_EDT, OnBnClickedBtnEdt)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_UNDO, OnBnClickedBtnUndo)
	ON_BN_CLICKED(IDC_BTN_SEARCH, OnBnClickedBtnSearch)
	ON_BN_CLICKED(IDC_BTN_UP, OnBnClickedBtnUp)
	ON_BN_CLICKED(IDC_BTN_DN, OnBnClickedBtnDn)
	ON_BN_CLICKED(IDC_CHECK_STAMPAIMMAGINI, OnBnClickedCheckStampaImmagini)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_REPORTS, OnLvnItemchangedListReports)

END_MESSAGE_MAP()

void CReportsDefaultModDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_UP, m_ctrlBtnUp);
	DDX_Control(pDX, IDC_BTN_DN, m_ctrlBtnDn);
	DDX_Control(pDX, IDC_BTN_SEARCH, m_ctrlBtnSearch);
	DDX_Control(pDX, IDC_BTN_NEW, m_ctrlBtnNew);
	DDX_Control(pDX, IDC_BTN_EDT, m_ctrlBtnEdt);
	DDX_Control(pDX, IDC_BTN_DEL, m_ctrlBtnDel);
	DDX_Control(pDX, IDC_BTN_SAVE, m_ctrlBtnSave);
	DDX_Control(pDX, IDC_BTN_UNDO, m_ctrlBtnUndo);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);

	DDX_Control(pDX, IDC_LIST_SEDI, m_ctrlListSedi);
	DDX_Control(pDX, IDC_LIST_ESAMI, m_ctrlListEsami);
	DDX_Control(pDX, IDC_LIST_REPORTS, m_ctrlListReports);

	DDX_Control(pDX, IDC_SPIN, m_ctrlSpin);
	DDX_Control(pDX, IDC_SPIN_IMM, m_ctrlSpinImm);

	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_02, m_ctrlStatic02);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic03);
	DDX_Control(pDX, IDC_STATIC_04, m_ctrlStatic04);
	DDX_Control(pDX, IDC_STATIC_05, m_ctrlStatic05);
	DDX_Control(pDX, IDC_STATIC_06, m_ctrlStatic06);
	DDX_Control(pDX, IDC_EDIT_REPORT, m_ctrlEditReport);
	DDX_Control(pDX, IDC_EDIT_COPIE, m_ctrlEditCopie);
	DDX_Control(pDX, IDC_EDIT_COPIE_IMM, m_ctrlEditCopieImm);

	DDX_Control(pDX, IDC_CHECK_STAMPAIMMAGINI, m_ctrlStampaImmagini);
}

void CReportsDefaultModDlg::OnCancel()
{
	// faccio niente //
}

HBRUSH CReportsDefaultModDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CDialog::OnCtlColor (pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_01:
		case IDC_LIST_SEDI:
		{
			pDC->SetTextColor(theApp.m_color[0]);

			break;
		}
		case IDC_STATIC_02:
		case IDC_LIST_ESAMI:
		{
			pDC->SetTextColor(theApp.m_color[1]);

			break;
		}
		case IDC_STATIC_03:
		case IDC_LIST_REPORTS:
		case IDC_STATIC_04:
		case IDC_EDIT_REPORT:
		case IDC_STATIC_05:
		case IDC_EDIT_COPIE:
		{
			pDC->SetTextColor(theApp.m_color[2]);

			break;
		}
	}

	return hBrush;
}

BOOL CReportsDefaultModDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	UDACCEL pAccel[1];
	pAccel[0].nSec = 0;
	pAccel[0].nInc = 1;

	m_ctrlSpin.SetRange32(0, 9);
	m_ctrlSpin.SetPos32(1);
	m_ctrlSpin.SetAccel(1, pAccel);

	m_ctrlSpinImm.SetRange32(0, 9);
	m_ctrlSpinImm.SetPos32(1);
	m_ctrlSpinImm.SetAccel(1, pAccel);

	RiempiListEsami();
	RiempiListSedi();

	m_ctrlListReports.SetExtendedStyle(m_ctrlListReports.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlListReports.InsertColumn(0, "Ord.", LVCFMT_CENTER, 50);
	m_ctrlListReports.InsertColumn(1, "Report", LVCFMT_LEFT, 480);
	m_ctrlListReports.InsertColumn(2, "Copie", LVCFMT_CENTER, 50);

	m_ctrlStatic01.SetFont(&theApp.m_fontBold);
	m_ctrlStatic02.SetFont(&theApp.m_fontBold);
	m_ctrlStatic03.SetFont(&theApp.m_fontBold);

	theApp.LocalizeDialog(this, CReportsDefaultModDlg::IDD, "ReportsDefaultModDlg");
	return TRUE;
}

void CReportsDefaultModDlg::OnOK()
{
	SalvaEsame();

	if (m_ctrlBtnOK.IsWindowEnabled())
		CDialog::OnOK();
}

void CReportsDefaultModDlg::RiempiListEsami()
{
	m_ctrlListEsami.ResetContent();

	int nIndex = 0;

	CTipoEsameSet setEsami;
	//setEsami.SetOpenFilter("Visibile=1");
	setEsami.SetSortRecord("Descrizione");
	if (setEsami.OpenRecordset("CReportsDefaultModDlg::RiempiListEsami"))
	{
		while(!setEsami.IsEOF())
		{
			m_ctrlListEsami.InsertString(nIndex, setEsami.m_sDescrizione);
			m_ctrlListEsami.SetItemData(nIndex, (DWORD)setEsami.m_lContatore);

			nIndex++;
			setEsami.MoveNext();
		}

		setEsami.CloseRecordset("CReportsDefaultModDlg::RiempiListEsami");
	}
}

void CReportsDefaultModDlg::RiempiListSedi()
{
	m_ctrlListSedi.ResetContent();

	int nIndex = 0;

	CSediEsameSet setSedi;
	setSedi.SetSortRecord("Descrizione");
	if (setSedi.OpenRecordset("CReportsDefaultModDlg::RiempiListSedi"))
	{
		while(!setSedi.IsEOF())
		{
			m_ctrlListSedi.InsertString(nIndex, setSedi.m_sDescrizione);
			m_ctrlListSedi.SetItemData(nIndex, (DWORD)setSedi.m_lID);

			nIndex++;
			setSedi.MoveNext();
		}

		setSedi.CloseRecordset("CReportsDefaultModDlg::RiempiListSedi");
	}
}

void CReportsDefaultModDlg::RiempiListReports()
{
	m_ctrlListReports.DeleteAllItems();

	int nIndex = 0;

	// Sandro 15/07/2013 //
	CString sSedeTemp = m_sSede;
	sSedeTemp.Replace("'", "''");

	CString strFilter;
	strFilter.Format("SedeEsame='%s' AND TipoEsame=%li", sSedeTemp, m_lTipoEsame);

	CReportsDefaultSet setRepDef;
	setRepDef.SetOpenFilter(strFilter + " AND Report<>'IMMAGINI'");
	setRepDef.SetSortRecord("ID");
	if (setRepDef.OpenRecordset("CReportsDefaultModDlg::RiempiListReports"))
	{
		CString strTemp;

		while(!setRepDef.IsEOF())
		{
			strTemp.Format("%d", nIndex + 1);
			m_ctrlListReports.InsertItem(nIndex, strTemp);
			m_ctrlListReports.SetItemData(nIndex, (DWORD)setRepDef.m_lID);

			m_ctrlListReports.SetItemText(nIndex, 1, setRepDef.m_sReport);

			strTemp.Format("%li", setRepDef.m_lCopie);
			m_ctrlListReports.SetItemText(nIndex, 2, strTemp);

			nIndex++;
			setRepDef.MoveNext();
		}

		setRepDef.CloseRecordset("CReportsDefaultModDlg::RiempiListReports");
	}

	// controllo se devo checkare la stampa delle immagini //

	setRepDef.SetOpenFilter(strFilter + " AND Report LIKE 'IMMAGINI'");
	if (setRepDef.OpenRecordset("CReportsDefaultModDlg::RiempiListReports"))
	{
		if (!setRepDef.IsEOF())
		{
			m_ctrlStampaImmagini.SetCheck(BST_CHECKED);

			m_ctrlSpinImm.EnableWindow(TRUE);
			m_ctrlSpinImm.SetPos32(setRepDef.m_lCopie);
		}
		else
		{
			m_ctrlStampaImmagini.SetCheck(BST_UNCHECKED);

			m_ctrlSpinImm.EnableWindow(FALSE);
			m_ctrlSpinImm.SetPos32(1);
		}

		setRepDef.CloseRecordset("CReportsDefaultModDlg::RiempiListReports");
	}
}

void CReportsDefaultModDlg::OnLbnSelchangeListEsami()
{
	SalvaEsame();

	m_lTipoEsame = 0;

	int nCurSel = m_ctrlListEsami.GetCurSel();
	if (nCurSel >= 0)
		m_lTipoEsame = m_ctrlListEsami.GetItemData(nCurSel);

	RiempiListReports();
	SetStato(STATO_NONE);
}

void CReportsDefaultModDlg::OnLbnSelchangeListSedi()
{
	SalvaEsame();

	m_sSede = "";

	int nCurSel = m_ctrlListSedi.GetCurSel();
	if (nCurSel >= 0)
		m_ctrlListSedi.GetText(nCurSel, m_sSede);

	RiempiListReports();
	SetStato(STATO_NONE);
}

void CReportsDefaultModDlg::OnLvnItemchangedListReports(NMHDR *pNMHDR, LRESULT *pResult)
{
	SetStato(STATO_NONE);
}

void CReportsDefaultModDlg::SetStato(int nStato)
{
	m_ctrlStatic03.ShowWindow((!m_sSede.IsEmpty()) && (m_lTipoEsame > 0));
	m_ctrlListReports.ShowWindow((!m_sSede.IsEmpty()) && (m_lTipoEsame > 0));
	m_ctrlBtnUp.ShowWindow((!m_sSede.IsEmpty()) && (m_lTipoEsame > 0));
	m_ctrlBtnDn.ShowWindow((!m_sSede.IsEmpty()) && (m_lTipoEsame > 0));
	m_ctrlStatic04.ShowWindow((!m_sSede.IsEmpty()) && (m_lTipoEsame > 0));
	m_ctrlStatic05.ShowWindow((!m_sSede.IsEmpty()) && (m_lTipoEsame > 0));
	m_ctrlEditReport.ShowWindow((!m_sSede.IsEmpty()) && (m_lTipoEsame > 0));
	m_ctrlBtnSearch.ShowWindow((!m_sSede.IsEmpty()) && (m_lTipoEsame > 0));
	m_ctrlEditCopie.ShowWindow((!m_sSede.IsEmpty()) && (m_lTipoEsame > 0));
	m_ctrlSpin.ShowWindow((!m_sSede.IsEmpty()) && (m_lTipoEsame > 0));
	m_ctrlBtnNew.ShowWindow((!m_sSede.IsEmpty()) && (m_lTipoEsame > 0));
	m_ctrlBtnEdt.ShowWindow((!m_sSede.IsEmpty()) && (m_lTipoEsame > 0));
	m_ctrlBtnDel.ShowWindow((!m_sSede.IsEmpty()) && (m_lTipoEsame > 0));
	m_ctrlBtnSave.ShowWindow((!m_sSede.IsEmpty()) && (m_lTipoEsame > 0));
	m_ctrlBtnUndo.ShowWindow((!m_sSede.IsEmpty()) && (m_lTipoEsame > 0));
	m_ctrlStampaImmagini.ShowWindow((!m_sSede.IsEmpty()) && (m_lTipoEsame > 0));
	m_ctrlStatic06.ShowWindow((!m_sSede.IsEmpty()) && (m_lTipoEsame > 0));
	m_ctrlEditCopieImm.ShowWindow((!m_sSede.IsEmpty()) && (m_lTipoEsame > 0));
	m_ctrlSpinImm.ShowWindow((!m_sSede.IsEmpty()) && (m_lTipoEsame > 0));

	switch(nStato)
	{
		case STATO_NONE:
		{
			BOOL bEnableUp = FALSE;
			BOOL bEnableDn = FALSE;

			POSITION pos = m_ctrlListReports.GetFirstSelectedItemPosition();
			if (pos != NULL)
			{
				int nItem = m_ctrlListReports.GetNextSelectedItem(pos);
				int nCopie = atoi(m_ctrlListReports.GetItemText(nItem, 2));

				bEnableUp = (nItem > 0);
				bEnableDn = (nItem < (m_ctrlListReports.GetItemCount() - 1));

				if ((nCopie < 1) || (nCopie > 9))
					nCopie = 1;

				m_ctrlEditReport.SetWindowText(m_ctrlListReports.GetItemText(nItem, 1));
				m_ctrlSpin.SetPos32(nCopie);
			}
			else
			{
				m_ctrlEditReport.SetWindowText("");
				m_ctrlSpin.SetPos32(1);
			}

			m_ctrlListSedi.EnableWindow(TRUE);
			m_ctrlListEsami.EnableWindow(TRUE);
			m_ctrlListReports.EnableWindow(TRUE);
			m_ctrlBtnUp.EnableWindow(bEnableUp);
			m_ctrlBtnDn.EnableWindow(bEnableDn);
			m_ctrlBtnSearch.EnableWindow(FALSE);
			m_ctrlSpin.EnableWindow(FALSE);
			m_ctrlBtnNew.EnableWindow(TRUE);
			m_ctrlBtnEdt.EnableWindow(m_ctrlListReports.GetFirstSelectedItemPosition() != NULL);
			m_ctrlBtnDel.EnableWindow(m_ctrlListReports.GetFirstSelectedItemPosition() != NULL);
			m_ctrlBtnSave.EnableWindow(FALSE);
			m_ctrlBtnUndo.EnableWindow(FALSE);
			m_ctrlBtnOK.EnableWindow(TRUE);

			break;
		}
		case STATO_NEW:
		{
			m_ctrlEditReport.SetWindowText("");
			m_ctrlSpin.SetPos32(1);

			m_ctrlListSedi.EnableWindow(FALSE);
			m_ctrlListEsami.EnableWindow(FALSE);
			m_ctrlListReports.EnableWindow(FALSE);
			m_ctrlBtnUp.EnableWindow(FALSE);
			m_ctrlBtnDn.EnableWindow(FALSE);
			m_ctrlBtnSearch.EnableWindow(TRUE);
			m_ctrlSpin.EnableWindow(TRUE);
			m_ctrlBtnNew.EnableWindow(FALSE);
			m_ctrlBtnEdt.EnableWindow(FALSE);
			m_ctrlBtnDel.EnableWindow(FALSE);
			m_ctrlBtnSave.EnableWindow(TRUE);
			m_ctrlBtnUndo.EnableWindow(TRUE);
			m_ctrlBtnOK.EnableWindow(FALSE);

			break;
		}
		case STATO_EDT:
		{
			m_ctrlListSedi.EnableWindow(FALSE);
			m_ctrlListEsami.EnableWindow(FALSE);
			m_ctrlListReports.EnableWindow(FALSE);
			m_ctrlBtnUp.EnableWindow(FALSE);
			m_ctrlBtnDn.EnableWindow(FALSE);
			m_ctrlBtnSearch.EnableWindow(TRUE);
			m_ctrlSpin.EnableWindow(TRUE);
			m_ctrlBtnNew.EnableWindow(FALSE);
			m_ctrlBtnEdt.EnableWindow(FALSE);
			m_ctrlBtnDel.EnableWindow(FALSE);
			m_ctrlBtnSave.EnableWindow(TRUE);
			m_ctrlBtnUndo.EnableWindow(TRUE);
			m_ctrlBtnOK.EnableWindow(FALSE);

			break;
		}
	}

	m_nStato = nStato;
}

void CReportsDefaultModDlg::OnBnClickedBtnNew()
{
	SetStato(STATO_NEW);
}

void CReportsDefaultModDlg::OnBnClickedBtnEdt()
{
	SetStato(STATO_EDT);
}

void CReportsDefaultModDlg::OnBnClickedBtnDel()
{
	POSITION pos = m_ctrlListReports.GetFirstSelectedItemPosition();

	int nCurSel = -1;
	if (pos != NULL)
		nCurSel = m_ctrlListReports.GetNextSelectedItem(pos);

	if (nCurSel < 0)
		return;

	long lID = m_ctrlListReports.GetItemData(nCurSel);
	if (lID <= 0)
		return;

	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_REPORTSDEFAULT_DELETE), MB_YESNO | MB_ICONQUESTION) == IDNO)
		return;

	CReportsDefaultSet setRepDef;
	if (setRepDef.ReportDel(lID))
	{
		SetStato(STATO_NONE);
		RiempiListReports();
	}
	else
	{
		OnBnClickedBtnUndo();
	}
}

void CReportsDefaultModDlg::OnBnClickedBtnSave()
{
	switch(m_nStato)
	{
		case STATO_NEW:
		{
			m_sSede.Trim();
			if (m_sSede.IsEmpty())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_REPORTSDEFAULT_ERROR1));
				return;
			}

			if (m_lTipoEsame <= 0)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_REPORTSDEFAULT_ERROR2));
				return;
			}

			CString sReport;
			m_ctrlEditReport.GetWindowText(sReport);
			sReport.Trim();
			if (sReport.IsEmpty())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_REPORTSDEFAULT_ERROR3));
				return;
			}

			CReportsDefaultSet setRepDef;
			if (setRepDef.ReportAdd(m_sSede, m_lTipoEsame, sReport, m_ctrlSpin.GetPos32()))
			{
				SetStato(STATO_NONE);
				RiempiListReports();
				
				int nItems = m_ctrlListReports.GetItemCount();
				m_ctrlListReports.SetItemState(nItems - 1, TVIS_SELECTED, TVIS_SELECTED);
			}
			else
			{
				OnBnClickedBtnUndo();
			}
			break;
		}
		case STATO_EDT:
		{
			POSITION pos = m_ctrlListReports.GetFirstSelectedItemPosition();

			int nCurSel = -1;
			if (pos != NULL)
				nCurSel = m_ctrlListReports.GetNextSelectedItem(pos);

			if (nCurSel < 0)
				return;

			long lID = m_ctrlListReports.GetItemData(nCurSel);
			if (lID <= 0)
				return;

			m_sSede.Trim();
			if (m_sSede.IsEmpty())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_REPORTSDEFAULT_ERROR1));
				return;
			}

			if (m_lTipoEsame <= 0)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_REPORTSDEFAULT_ERROR2));
				return;
			}

			CString sReport;
			m_ctrlEditReport.GetWindowText(sReport);
			sReport.Trim();
			if (sReport.IsEmpty())
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_REPORTSDEFAULT_ERROR3));
				return;
			}

			CReportsDefaultSet setRepDef;
			if (setRepDef.ReportEdt(lID, m_sSede, m_lTipoEsame, sReport, m_ctrlSpin.GetPos32()))
			{
				SetStato(STATO_NONE);
				RiempiListReports();
				
				m_ctrlListReports.SetItemState(nCurSel, TVIS_SELECTED, TVIS_SELECTED);
			}
			else
			{
				OnBnClickedBtnUndo();
			}
			break;
		}
	}
}

void CReportsDefaultModDlg::OnBnClickedBtnUndo()
{
	SetStato(STATO_NONE);
	RiempiListReports();
}

void CReportsDefaultModDlg::OnBnClickedBtnSearch()
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
	ofnOpenFileName.hwndOwner   = m_hWnd;
	ofnOpenFileName.lpstrFile   = szFileName;
	ofnOpenFileName.nMaxFile    = MAX_PATH;
	ofnOpenFileName.lpstrFilter = pFilter;
	ofnOpenFileName.Flags       = OFN_FILEMUSTEXIST | OFN_LONGNAMES | OFN_READONLY;

	if (GetOpenFileName(&ofnOpenFileName) != FALSE)
		strTemp.Format("%s", ofnOpenFileName.lpstrFile);

	m_ctrlEditReport.SetWindowText(strTemp);
}

void CReportsDefaultModDlg::OnBnClickedBtnUp()
{
	BeginWaitCursor();

	POSITION pos = m_ctrlListReports.GetFirstSelectedItemPosition();

	int nCurSel = -1;
	if (pos != NULL)
		nCurSel = m_ctrlListReports.GetNextSelectedItem(pos);

	if (nCurSel < 0)
	{
		EndWaitCursor();
		return;
	}

	long lID = m_ctrlListReports.GetItemData(nCurSel);
	if (lID <= 0)
	{
		EndWaitCursor();
		return;
	}

	CReportsDefaultSet setRepDef;
	if (setRepDef.ReportUp(lID, m_sSede, m_lTipoEsame))
	{
		SetStato(STATO_NONE);
		RiempiListReports();

		m_ctrlListReports.SetItemState(nCurSel - 1, TVIS_SELECTED, TVIS_SELECTED);
	}
	else
	{
		OnBnClickedBtnUndo();
	}

	EndWaitCursor();
}

void CReportsDefaultModDlg::OnBnClickedBtnDn()
{
	BeginWaitCursor();

	POSITION pos = m_ctrlListReports.GetFirstSelectedItemPosition();

	int nCurSel = -1;
	if (pos != NULL)
		nCurSel = m_ctrlListReports.GetNextSelectedItem(pos);

	if (nCurSel < 0)
	{
		EndWaitCursor();
		return;
	}

	long lID = m_ctrlListReports.GetItemData(nCurSel);
	if (lID <= 0)
	{
		EndWaitCursor();
		return;
	}

	CReportsDefaultSet setRepDef;
	if (setRepDef.ReportDn(lID, m_sSede, m_lTipoEsame))
	{
		SetStato(STATO_NONE);
		RiempiListReports();

		m_ctrlListReports.SetItemState(nCurSel + 1, TVIS_SELECTED, TVIS_SELECTED);
	}
	else
	{
		OnBnClickedBtnUndo();
	}

	EndWaitCursor();
}

void CReportsDefaultModDlg::SalvaEsame()
{
	if (m_sSede == "" || m_lTipoEsame <= 0)
		return;

	// Sandro 15/07/2013 //
	CString sSedeTemp = m_sSede;
	sSedeTemp.Replace("'", "''");

	CString sFilter;
	sFilter.Format("SedeEsame='%s' AND TipoEsame=%li AND Report LIKE 'IMMAGINI'", sSedeTemp, m_lTipoEsame);

	CReportsDefaultSet setRepDef;
	setRepDef.SetOpenFilter(sFilter);
	if (setRepDef.OpenRecordset("CReportsDefaultModDlg::SalvaEsame"))
	{
		long lID = 0;

		if (!setRepDef.IsEOF())
			lID = setRepDef.m_lID;

		setRepDef.CloseRecordset("CReportsDefaultModDlg::SalvaEsame");

		if (m_ctrlStampaImmagini.GetCheck() == BST_CHECKED)
		{
			// devo aggiungere o modificare //

			if (lID > 0)
			{
				// esiste, modifico //
				setRepDef.ReportEdt(lID, m_sSede, m_lTipoEsame, "IMMAGINI", m_ctrlSpinImm.GetPos32());
			}
			else
			{
				// non esiste, aggiungo //
				setRepDef.ReportAdd(m_sSede, m_lTipoEsame, "IMMAGINI", m_ctrlSpinImm.GetPos32());
			}
		}
		else
		{
			// se esiste, cancello //
			if (lID > 0)
				setRepDef.ReportDel(lID);
		}
	}
}

void CReportsDefaultModDlg::OnBnClickedCheckStampaImmagini()
{
	if (m_ctrlStampaImmagini.GetCheck() == BST_CHECKED)
	{
		m_ctrlSpinImm.EnableWindow(TRUE);
	}
	else
	{
		m_ctrlSpinImm.EnableWindow(FALSE);
		m_ctrlSpinImm.SetPos32(1);
	}
}
