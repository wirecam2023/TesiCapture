//Gabriel BUG 6225 - Lista DO

#include "stdafx.h"
#include "Endox.h"
#include "FlussoDiStatoDlg.h"
#include "MediciSet.h"
#include "VistaFlussoDiStatoSet.h"
#include "Common.h" //Gabriel BUG 6225 - Lista DO FIX

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CFlussoDiStatoDlg, CEndoxResizableDlg)

CFlussoDiStatoDlg::CFlussoDiStatoDlg(CWnd* pParent, CEsamiView* pEsamiView)
: CEndoxResizableDlg(CFlussoDiStatoDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
}

CFlussoDiStatoDlg::~CFlussoDiStatoDlg()
{
}

BEGIN_MESSAGE_MAP(CFlussoDiStatoDlg, CEndoxResizableDlg)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CFlussoDiStatoDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_BTN_MEDICO, &CFlussoDiStatoDlg::OnBnClickedMedico)
	ON_BN_CLICKED(IDC_BTN_REFRESH, &CFlussoDiStatoDlg::OnBnClickedRefresh)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList) //Gabriel BUG 6225 - Lista DO FIX
END_MESSAGE_MAP()

void CFlussoDiStatoDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC_4, m_ctrlStatic4);
	DDX_Control(pDX, IDC_STATIC_5, m_ctrlStatic5); //Gabriel BUG 6225 - Lista DO FIX

	DDX_Control(pDX, IDC_BTN_CLOSE, m_ctrlButtonChiudi);
	DDX_Control(pDX, IDC_BTN_MEDICO, m_ctrlButtonMedico);
	DDX_Control(pDX, IDC_LIST, m_ctrlList);
	DDX_Control(pDX, IDC_COMBO, m_ctrlComboMedico);
	DDX_Control(pDX, IDC_DATE_FROM, m_ctrlDateFrom);
	DDX_Control(pDX, IDC_TIME_FROM, m_ctrlTimeFrom);
	DDX_Control(pDX, IDC_DATE_TO, m_ctrlDateTo);
	DDX_Control(pDX, IDC_TIME_TO, m_ctrlTimeTo);

}

BOOL CFlussoDiStatoDlg::OnInitDialog()
{
	CEndoxResizableDlg::OnInitDialog();

	AddAnchor(IDC_STATIC_1, CSize(0, 0), CSize(100, 0));
	AddAnchor(IDC_STATIC_2, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_DATE_FROM, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_TIME_FROM, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_STATIC_3, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_DATE_TO, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_TIME_TO, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_STATIC_4, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_COMBO, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_LIST, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDC_BTN_CLOSE, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDC_BTN_REFRESH, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_BTN_MEDICO, CSize(100, 0), CSize(100, 0));

	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	//lista principal
	int nColumn = 0;
	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrlList.InsertColumn(nColumn++, theApp.GetMessageString(IDS_DATAESAME), CListSortableCtrl::type_string, LVCFMT_LEFT, 100);
	m_ctrlList.InsertColumn(nColumn++, theApp.GetMessageString(IDS_ORAESAME), CListSortableCtrl::type_string, LVCFMT_LEFT, 100);
	m_ctrlList.InsertColumn(nColumn++, theApp.GetMessageString(IDS_NOME), CListSortableCtrl::type_string, LVCFMT_LEFT, 100);
	m_ctrlList.InsertColumn(nColumn++, theApp.GetMessageString(IDS_COGNOME), CListSortableCtrl::type_string, LVCFMT_LEFT, 100);
	m_ctrlList.InsertColumn(nColumn++, theApp.GetMessageString(IDS_DATANASCITA), CListSortableCtrl::type_string, LVCFMT_LEFT, 100);
	m_ctrlList.InsertColumn(nColumn++, theApp.GetMessageString(IDS_SESSO), CListSortableCtrl::type_string, LVCFMT_LEFT, 100);
	m_ctrlList.InsertColumn(nColumn++, theApp.GetMessageString(IDS_FICHAITEM), CListSortableCtrl::type_string, LVCFMT_LEFT, 100);
	m_ctrlList.InsertColumn(nColumn++, theApp.GetMessageString(IDS_DESCRIZIONEESAME), CListSortableCtrl::type_string, LVCFMT_LEFT, 100);
	m_ctrlList.InsertColumn(nColumn++, theApp.GetMessageString(IDS_SIGLA), CListSortableCtrl::type_string, LVCFMT_LEFT, 100);

	CRect rect;
	m_ctrlList.GetWindowRect(&rect);
	m_ctrlList.SetColumnWidth(0, rect.Width() / 9);
	m_ctrlList.SetColumnWidth(1, rect.Width() / 9);
	m_ctrlList.SetColumnWidth(2, rect.Width() / 9);
	m_ctrlList.SetColumnWidth(3, rect.Width() / 9);
	m_ctrlList.SetColumnWidth(4, rect.Width() / 9);
	m_ctrlList.SetColumnWidth(5, rect.Width() / 9);
	m_ctrlList.SetColumnWidth(6, rect.Width() / 9);
	m_ctrlList.SetColumnWidth(7, rect.Width() / 9);
	m_ctrlList.SetColumnWidth(8, rect.Width() / 9);
	//

	//Sistemo filtro ora
	int anno = CDate().GetYear();
	int mese = CDate().GetMonth();
	int giorno = CDate().GetDay();
	CTime timeFrom(anno, mese, giorno, 0, 0, 0);
	m_ctrlTimeFrom.SetTime(&timeFrom);
	CTime timeTo(anno, mese, giorno, 23, 59, 59);
	m_ctrlTimeTo.SetTime(&timeTo);
	//
	
	RiempiComboMedico();
	RiempiLista();

	theApp.LocalizeDialog(this, CFlussoDiStatoDlg::IDD, "CFlussoDiStatoDlg");
	return TRUE;
}

void CFlussoDiStatoDlg::RiempiLista()
{
	m_ctrlList.DeleteAllItems();

	//Recupero data e ora
	CString strDateFrom = GetDataOraFrom();
	CString strDateTo = GetDataOraTo();

	CString strFilter;
	strFilter.Format("DataEsame >= '%s' and DataEsame <= '%s' AND IdUO = '%li'", strDateFrom, strDateTo,theApp.m_lUO);
	
	CVistaFlussoDiStatoSet flussoDiStatoSet;
	flussoDiStatoSet.SetOpenFilter(strFilter);
	flussoDiStatoSet.OpenRecordset("CFlussoDiStatoDlg::RiempiLista");

	while (!flussoDiStatoSet.IsEOF())
	{
		int iItemInserted = m_ctrlList.InsertItem(m_ctrlList.GetItemCount(), flussoDiStatoSet.m_sDataEsameFormata);
		m_ctrlList.SetItemData(iItemInserted, flussoDiStatoSet.m_IdEsame);
		m_ctrlList.SetItemText(iItemInserted, 1, flussoDiStatoSet.m_sOraEsame);
		m_ctrlList.SetItemText(iItemInserted, 2, flussoDiStatoSet.m_sNome);
		m_ctrlList.SetItemText(iItemInserted, 3, flussoDiStatoSet.m_sCognome);
		m_ctrlList.SetItemText(iItemInserted, 4, flussoDiStatoSet.m_sDataNascita);
		m_ctrlList.SetItemText(iItemInserted, 5, flussoDiStatoSet.m_sSesso);
		m_ctrlList.SetItemText(iItemInserted, 6, flussoDiStatoSet.m_sCodEsame);
		m_ctrlList.SetItemText(iItemInserted, 7, flussoDiStatoSet.m_sDescrizioneEsame);
		m_ctrlList.SetItemText(iItemInserted, 8, flussoDiStatoSet.m_sSiglaEsame);

		flussoDiStatoSet.MoveNext();
	}

	flussoDiStatoSet.CloseRecordset("CFlussoDiStatoDlg::RiempiLista");	
}

void CFlussoDiStatoDlg::RiempiComboMedico()
{
	int nCurSelSede = -1;

	m_ctrlComboMedico.ResetContent();

	CMediciSet setMed;
	setMed.SetBaseFilter("");
	setMed.SetSortRecord("NOME DESC, COGNOME DESC");
	
	int nIndex = 0;

	if (setMed.OpenRecordset("CFlussoDiStatoDlg::RiempiComboMedico"))
	{
		while (!setMed.IsEOF())
		{
			CString sMedico = setMed.m_sNome + " " + setMed.m_sCognome;
			
			m_ctrlComboMedico.InsertString(nIndex, sMedico);
			m_ctrlComboMedico.SetItemData(nIndex, setMed.m_lContatore);

			setMed.MoveNext();
		}

		setMed.CloseRecordset("CFlussoDiStatoDlg::RiempiComboMedico");
	}
}

CString CFlussoDiStatoDlg::GetDataOraFrom()
{
	CTime dateFrom, timeFrom;
	m_ctrlDateFrom.GetTime(dateFrom);
	m_ctrlTimeFrom.GetTime(timeFrom);

	CString strDateFrom;
	strDateFrom.Format("%s%s", dateFrom.Format("%Y%m%d"), timeFrom.Format("%H%M%S"));

	return strDateFrom;
}

CString CFlussoDiStatoDlg::GetDataOraTo()
{
	CTime dateTo, timeTo;
	m_ctrlDateTo.GetTime(dateTo);
	m_ctrlTimeTo.GetTime(timeTo);

	CString strDateTo;
	strDateTo.Format("%s%s", dateTo.Format("%Y%m%d"), timeTo.Format("%H%M%S"));

	return strDateTo;
}

void CFlussoDiStatoDlg::OnBnClickedCancel()
{
	m_ctrlList.DeleteAllItems();
	CResizableDialog::OnCancel();
}

void CFlussoDiStatoDlg::OnCancel()
{
}

void CFlussoDiStatoDlg::OnOK()
{
}

void CFlussoDiStatoDlg::OnBnClickedClose()
{
	CResizableDialog::OnCancel();
}

void CFlussoDiStatoDlg::OnBnClickedRefresh()
{
	RiempiLista();
}

void CFlussoDiStatoDlg::OnBnClickedMedico()
{
	CEsamiSet set;
	CString strFilter;
	CString strFilterAux;

	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (!pos)
	{
		AfxMessageBox(theApp.GetMessageString(IDS_FLUSSODISTATO_NESSUNESAMESELEZIONATO));
		return;
	}
	
	long lMedicoId = m_ctrlComboMedico.GetItemData(m_ctrlComboMedico.GetCurSel());
	if (lMedicoId == -1)
	{
		AfxMessageBox(theApp.GetMessageString(IDS_FLUSSODISTATO_NESSUNMEDICOSELEZIONATO));
		return;
	}

	while (pos)
	{
		int item = m_ctrlList.GetNextSelectedItem(pos);
		if (item > -1)
		{
			long lIDEsame = m_ctrlList.GetItemData(item);
			strFilterAux.Format("%li,", lIDEsame);
			strFilter += strFilterAux;
		}
	}
	strFilter = strFilter.Mid(0, strFilter.GetLength() - 1);
	
	strFilterAux.Format("CONTATORE IN (%s) AND ELIMINATO=0", strFilter);
	set.SetOpenFilter(strFilterAux);
	
	if (set.OpenRecordset("CFlussoDiStatoDlg::OnBnClickedMedico"))
	{
		while (!set.IsEOF())
		{
			if (set.EditRecordset("CFlussoDiStatoDlg::OnBnClickedMedico"))
			{
				set.m_lMedico = lMedicoId;
				set.UpdateRecordset("CFlussoDiStatoDlg::OnBnClickedMedico");
			}
			
			set.MoveNext();
		}
		set.CloseRecordset("CFlussoDiStatoDlg::OnBnClickedMedico");
	}

	RiempiLista();
}
//Gabriel BUG 6225 - Lista DO FIX
void CFlussoDiStatoDlg::RefreshCount()
{
	long lCount = 0;
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();

	while (pos)
	{
		int item = m_ctrlList.GetNextSelectedItem(pos);
		if (item > -1)
		{
			lCount++;
		}
	}

	if (lCount > 1)
	{
		CString strCount;
		strCount.Format("%li exames selecionados", lCount);
		m_ctrlStatic5.SetWindowText(strCount);
	}
	else
	{
		CString strCount;
		strCount.Format("%li exame selecionado", lCount);
		m_ctrlStatic5.SetWindowText(strCount);
	}
}

//Gabriel BUG 6225 - Lista DO FIX
void CFlussoDiStatoDlg::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if ((pNMListView->uChanged & LVIF_STATE) || (pNMListView->uOldState & LVNI_SELECTED) || (pNMListView->uNewState != pNMListView->uOldState))
	{
		RefreshCount();
	}
}