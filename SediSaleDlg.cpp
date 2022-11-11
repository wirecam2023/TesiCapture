#include "stdafx.h"
#include "Endox.h"
#include "SediSaleDlg.h"

#include "AgendeSet.h"
#include "SaleEsameSet.h"
#include "SediEsameSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSediSaleDlg::CSediSaleDlg(CWnd* pParent)
	: CDialog(CSediSaleDlg::IDD, pParent), m_ctrlListaSedi(FALSE, FALSE, FALSE), m_ctrlListaSale(FALSE, FALSE, FALSE), m_ctrlListaAgende(FALSE, FALSE, FALSE)
{	
	m_lIdSedeSel = 0;
	m_lIdSalaSel = 0;
	m_lIdAgendaSel = 0;
}

CSediSaleDlg::~CSediSaleDlg()
{
}

BEGIN_MESSAGE_MAP(CSediSaleDlg, CDialog)
	ON_WM_CTLCOLOR()	
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTA_SEDI, &CSediSaleDlg::OnLvnItemchangedListaSedi)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTA_SALE, &CSediSaleDlg::OnLvnItemchangedListaSale)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTA_AGENDE, &CSediSaleDlg::OnLvnItemchangedListaAgende)

	ON_MESSAGE(WM_SEDICHANGED, OnSediChanged)
	ON_MESSAGE(WM_SALECHANGED, OnSaleChanged)
	ON_MESSAGE(WM_AGENDECHANGED, OnAgendeChanged)
	ON_BN_CLICKED(IDC_SEDE_NUOVO, &CSediSaleDlg::OnBnClickedSedeNuovo)
	ON_BN_CLICKED(IDC_SEDE_CANC, &CSediSaleDlg::OnBnClickedSedeCanc)
	ON_BN_CLICKED(IDC_SALA_NUOVO, &CSediSaleDlg::OnBnClickedSalaNuovo)
	ON_BN_CLICKED(IDC_SALA_CANC, &CSediSaleDlg::OnBnClickedSalaCanc)
	ON_BN_CLICKED(IDC_AGENDA_NUOVO, &CSediSaleDlg::OnBnClickedAgendaNuovo)
	ON_BN_CLICKED(IDC_AGENDA_CANC, &CSediSaleDlg::OnBnClickedAgendaCanc)
END_MESSAGE_MAP()

void CSediSaleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LISTA_SEDI, m_ctrlListaSedi);
	DDX_Control(pDX, IDC_LISTA_SALE, m_ctrlListaSale);
	DDX_Control(pDX, IDC_LISTA_AGENDE, m_ctrlListaAgende);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);	
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);

	DDX_Control(pDX, IDOK, m_ctrlButtonEsci);
	
	DDX_Control(pDX, IDC_SEDE_NUOVO, m_ctrlBtnSedeNuovo);
	DDX_Control(pDX, IDC_SEDE_CANC, m_ctrlBtnSedeCanc);
	DDX_Control(pDX, IDC_SALA_NUOVO, m_ctrlBtnSalaNuovo);
	DDX_Control(pDX, IDC_SALA_CANC, m_ctrlBtnSalaCanc);
	DDX_Control(pDX, IDC_AGENDA_NUOVO, m_ctrlBtnAgendaNuovo);
	DDX_Control(pDX, IDC_AGENDA_CANC, m_ctrlBtnAgendaCanc);

}

BOOL CSediSaleDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	GetDlgItem(IDOK)->SetFont(&theApp.m_fontBold);
	
	m_ctrlListaSedi.SetExtendedStyle(m_ctrlListaSedi.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP);
	m_ctrlListaSale.SetExtendedStyle(m_ctrlListaSale.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP);
	m_ctrlListaAgende.SetExtendedStyle(m_ctrlListaAgende.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP);
	
	m_ctrlListaSedi.InsertColumn(0, theApp.GetMessageString(IDS_DESCRIZIONE));
	m_ctrlListaSedi.InsertColumn(1, theApp.GetMessageString(IDS_SIGLA));
	m_ctrlListaSedi.InsertColumn(2, theApp.GetMessageString(IDS_CODICE_DICOM));
	m_ctrlListaSedi.InsertColumn(3, theApp.GetMessageString(IDS_ID_ENDOX));
	m_ctrlListaSedi.SetNotificationChangeValueMessage(WM_SEDICHANGED);

	m_ctrlListaSale.InsertColumn(0, theApp.GetMessageString(IDS_DESCRIZIONE));
	m_ctrlListaSale.InsertColumn(1, theApp.GetMessageString(IDS_ID_ENDOX));
	m_ctrlListaSale.SetNotificationChangeValueMessage(WM_SALECHANGED);

	m_ctrlListaAgende.InsertColumn(0, theApp.GetMessageString(IDS_DESCRIZIONE));
	m_ctrlListaAgende.InsertColumn(1, theApp.GetMessageString(IDC_CODICE_INTEGRAZIONE));
	m_ctrlListaAgende.InsertColumn(2, theApp.GetMessageString(IDS_ID_ENDOX));
	m_ctrlListaAgende.SetNotificationChangeValueMessage(WM_AGENDECHANGED);

	RiempiListaSedi();
	
	//
	theApp.LocalizeDialog(this, CSediSaleDlg::IDD, "SediSaleDlg");

	return TRUE;
}

void CSediSaleDlg::RiempiListaSedi()
{
	BeginWaitCursor();
	m_ctrlListaSedi.SetRedraw(FALSE);	

	m_ctrlListaSedi.DeleteAllItems();
	m_lIdSedeSel = 0;
	
	int nIndex = 0;

	CSediEsameSet setTemp;

	if (setTemp.OpenRecordset("CSediSaleDlg::RiempiListaSedi"))
	{				
		while(!setTemp.IsEOF())
		{
			int index = m_ctrlListaSedi.InsertItem(m_ctrlListaSedi.GetItemCount(), setTemp.m_sDescrizione);
			m_ctrlListaSedi.SetItemData(index, setTemp.m_lID);
			m_ctrlListaSedi.SetItemText(index, 1, setTemp.m_sSiglaProgressivo);
			m_ctrlListaSedi.SetItemText(index, 2, setTemp.m_sDicomSede);
			CString idSede;
			idSede.Format("%li", setTemp.m_lID);
			m_ctrlListaSedi.SetItemText(index, 3, idSede);

			m_ctrlListaSedi.SetSubItemEdit(index, 0);
			m_ctrlListaSedi.SetSubItemEdit(index, 1);
			m_ctrlListaSedi.SetSubItemEdit(index, 2);
			
			setTemp.MoveNext();
		}
		
		setTemp.CloseRecordset("CSediSaleDlg::RiempiListaSedi");				
	}

	for (int i = 0; i < m_ctrlListaSedi.GetHeaderCtrl()->GetItemCount(); i++)
		m_ctrlListaSedi.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlListaSedi.SetRedraw(TRUE);
	EndWaitCursor();

	RiempiListaSale();
	
}

void CSediSaleDlg::RiempiListaSale()
{
	BeginWaitCursor();
	m_ctrlListaSale.SetRedraw(FALSE);	

	m_ctrlListaSale.DeleteAllItems();
	m_lIdSalaSel = 0;
	
	CSaleEsameSet setTemp;
	CString filter;
	filter.Format("idsede=%li", m_lIdSedeSel);
	setTemp.SetOpenFilter(filter);
	if (setTemp.OpenRecordset("CSediSaleDlg::RiempiListaSale"))
	{				
		while(!setTemp.IsEOF())
		{
			int index = m_ctrlListaSale.InsertItem(m_ctrlListaSale.GetItemCount(), setTemp.m_sDescrizione);
			m_ctrlListaSale.SetItemData(index, setTemp.m_lID);

			CString idSala;
			idSala.Format("%li", setTemp.m_lID);
			m_ctrlListaSale.SetItemText(index, 1, idSala);

			m_ctrlListaSale.SetSubItemEdit(index, 0);
			
			setTemp.MoveNext();
		}
		
		setTemp.CloseRecordset("CSediSaleDlg::RiempiListaSale");				
	}

	for (int i = 0; i < m_ctrlListaSale.GetHeaderCtrl()->GetItemCount(); i++)
		m_ctrlListaSale.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlListaSale.SetRedraw(TRUE);
	EndWaitCursor();

	RiempiListaAgende();
	
}

void CSediSaleDlg::RiempiListaAgende()
{
	BeginWaitCursor();
	m_ctrlListaAgende.SetRedraw(FALSE);	

	m_ctrlListaAgende.DeleteAllItems();
	m_lIdAgendaSel = 0;

	int nIndex = 0;

	CAgendeSet setTemp;
	CString filter;
	filter.Format("idsala=%li", m_lIdSalaSel);
	setTemp.SetOpenFilter(filter);

	if (setTemp.OpenRecordset("CSediSaleDlg::RiempiListaAgende"))
	{
		while (!setTemp.IsEOF())
		{
			int index = m_ctrlListaAgende.InsertItem(m_ctrlListaAgende.GetItemCount(), setTemp.m_sDescrizione);
			m_ctrlListaAgende.SetItemData(index, setTemp.m_lID);
			m_ctrlListaAgende.SetItemText(index, 1, setTemp.m_sCodiceIntegrazione);

			CString idAgenda;
			idAgenda.Format("%li", setTemp.m_lID);
			m_ctrlListaAgende.SetItemText(index, 2, idAgenda);

			m_ctrlListaAgende.SetSubItemEdit(index, 0);
			m_ctrlListaAgende.SetSubItemEdit(index, 1);

			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CSediSaleDlg::RiempiListaAgende");
	}

	for (int i = 0; i < m_ctrlListaAgende.GetHeaderCtrl()->GetItemCount(); i++)
		m_ctrlListaAgende.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlListaAgende.SetRedraw(TRUE);
	EndWaitCursor();

}

void CSediSaleDlg::OnOK()
{	
	CDialog::OnOK();
}

void CSediSaleDlg::OnLvnItemchangedListaSedi(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	m_ctrlBtnSedeNuovo.EnableWindow(TRUE);
	m_ctrlBtnSedeCanc.EnableWindow(FALSE);
	m_ctrlBtnSalaNuovo.EnableWindow(FALSE);
	m_ctrlBtnSalaCanc.EnableWindow(FALSE);
	m_ctrlBtnAgendaNuovo.EnableWindow(FALSE);
	m_ctrlBtnAgendaCanc.EnableWindow(FALSE);

	POSITION pos = m_ctrlListaSedi.GetFirstSelectedItemPosition();

	if (pos)
	{
		int index = m_ctrlListaSedi.GetNextSelectedItem(pos);		
		
		if (index >= 0)
		{			
			m_lIdSedeSel = m_ctrlListaSedi.GetItemData(index);
			m_ctrlBtnSedeNuovo.EnableWindow(TRUE);
			m_ctrlBtnSedeCanc.EnableWindow(TRUE);
			m_ctrlBtnSalaNuovo.EnableWindow(TRUE);
		}
	}
	else
	{
		m_lIdSedeSel = 0;
	}

	RiempiListaSale();

	*pResult = 0;
}


void CSediSaleDlg::OnLvnItemchangedListaSale(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	m_ctrlBtnSalaNuovo.EnableWindow(TRUE);
	m_ctrlBtnSalaCanc.EnableWindow(FALSE);
	m_ctrlBtnAgendaNuovo.EnableWindow(FALSE);
	m_ctrlBtnAgendaCanc.EnableWindow(FALSE);

	POSITION pos = m_ctrlListaSale.GetFirstSelectedItemPosition();

	if (pos)
	{
		int index = m_ctrlListaSale.GetNextSelectedItem(pos);

		if (index >= 0)
		{
			m_lIdSalaSel = m_ctrlListaSale.GetItemData(index);
			m_ctrlBtnSalaNuovo.EnableWindow(TRUE);
			m_ctrlBtnSalaCanc.EnableWindow(TRUE);
			m_ctrlBtnAgendaNuovo.EnableWindow(TRUE);
		}
	}
	else
	{
		m_lIdSalaSel = 0;
	}

	RiempiListaAgende();

	*pResult = 0;
}


void CSediSaleDlg::OnLvnItemchangedListaAgende(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	m_ctrlBtnAgendaNuovo.EnableWindow(TRUE);
	m_ctrlBtnAgendaCanc.EnableWindow(FALSE);	

	POSITION pos = m_ctrlListaAgende.GetFirstSelectedItemPosition();

	if (pos)
	{
		int index = m_ctrlListaAgende.GetNextSelectedItem(pos);

		if (index >= 0)
		{
			m_lIdAgendaSel = m_ctrlListaAgende.GetItemData(index);
			m_ctrlBtnAgendaNuovo.EnableWindow(TRUE);
			m_ctrlBtnAgendaCanc.EnableWindow(TRUE);
		}
	}
	else
	{
		m_lIdAgendaSel = 0;
	}

	*pResult = 0;
}

LRESULT CSediSaleDlg::OnSediChanged(WPARAM wParam, LPARAM lParam)
{
	long idSede = m_ctrlListaSedi.GetItemData(wParam);

	CSediEsameSet set;
	CString sFilter;
	sFilter.Format("id=%li", idSede);
	set.SetOpenFilter(sFilter);

	if (set.OpenRecordset("CSediSaleDlg::OnLvnItemchangedListaSedi"))
	{
		if (!set.IsEOF())
		{
			if (set.EditRecordset("CSediSaleDlg::OnLvnItemchangedListaSedi"))
			{
				set.m_sDescrizione = m_ctrlListaSedi.GetItemText(wParam, 0);
				set.m_sSiglaProgressivo = m_ctrlListaSedi.GetItemText(wParam, 1);
				set.m_sDicomSede = m_ctrlListaSedi.GetItemText(wParam, 2);

				set.UpdateRecordset("CSediSaleDlg::OnLvnItemchangedListaSedi");
			}
		}

		set.CloseRecordset("CSediSaleDlg::OnLvnItemchangedListaSedi");
	}

	return 1;
}

LRESULT CSediSaleDlg::OnSaleChanged(WPARAM wParam, LPARAM lParam)
{
	long idSala = m_ctrlListaSale.GetItemData(wParam);

	CSaleEsameSet set;
	CString sFilter;
	sFilter.Format("id=%li", idSala);
	set.SetOpenFilter(sFilter);

	if (set.OpenRecordset("CSediSaleDlg::OnLvnItemchangedListaSale"))
	{
		if (!set.IsEOF())
		{
			if (set.EditRecordset("CSediSaleDlg::OnLvnItemchangedListaSale"))
			{
				set.m_sDescrizione = m_ctrlListaSale.GetItemText(wParam, 0);

				set.UpdateRecordset("CSediSaleDlg::OnLvnItemchangedListaSale");
			}
		}

		set.CloseRecordset("CSediSaleDlg::OnLvnItemchangedListaSale");
	}

	return 1;
}

LRESULT CSediSaleDlg::OnAgendeChanged(WPARAM wParam, LPARAM lParam)
{
	long idAgenda = m_ctrlListaAgende.GetItemData(wParam);

	CAgendeSet set;
	CString sFilter;
	sFilter.Format("id=%li", idAgenda);
	set.SetOpenFilter(sFilter);

	if (set.OpenRecordset("CSediSaleDlg::OnLvnItemchangedListaAgende"))
	{
		if (!set.IsEOF())
		{
			if (set.EditRecordset("CSediSaleDlg::OnLvnItemchangedListaAgende"))
			{
				set.m_sDescrizione = m_ctrlListaAgende.GetItemText(wParam, 0);
				set.m_sCodiceIntegrazione = m_ctrlListaAgende.GetItemText(wParam, 1);

				set.UpdateRecordset("CSediSaleDlg::OnLvnItemchangedListaAgende");
			}
		}

		set.CloseRecordset("CSediSaleDlg::OnLvnItemchangedListaAgende");
	}

	return 1;
}

void CSediSaleDlg::OnBnClickedSedeNuovo()
{
	//IDS_SEDISALE_QUESTION6
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_SEDISALE_QUESTION6), MB_YESNO) == IDNO)
		return;

	CSediEsameSet set;

	if (set.OpenRecordset("CSediSaleDlg::OnBnClickedSedeNuovo"))
	{
		if (set.AddNewRecordset("CSediSaleDlg::OnBnClickedSedeNuovo"))
		{
			set.m_sDescrizione = theApp.GetMessageString(IDS_NUOVA_SEDE).MakeUpper();

			if (set.UpdateRecordset("CSediSaleDlg::OnBnClickedSedeNuovo"))
			{
				int index = m_ctrlListaSedi.InsertItem(m_ctrlListaSedi.GetItemCount(), theApp.GetMessageString(IDS_NUOVA_SEDE).MakeUpper());
				m_ctrlListaSedi.SetItemData(index, set.GetLastAdd());

				CString idSede;
				idSede.Format("%li", set.m_lID);
				m_ctrlListaSedi.SetItemText(index, 3, idSede);

				m_ctrlListaSedi.SetSubItemEdit(index, 0);
				m_ctrlListaSedi.SetSubItemEdit(index, 1);
				m_ctrlListaSedi.SetSubItemEdit(index, 2);
			}

			set.CloseRecordset("CSediSaleDlg::OnBnClickedSedeNuovo");
		}
	}

	for (int i = 0; i < m_ctrlListaSedi.GetHeaderCtrl()->GetItemCount(); i++)
		m_ctrlListaSedi.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
}


void CSediSaleDlg::OnBnClickedSedeCanc()
{
	//IDS_SEDISALE_QUESTION5
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_SEDISALE_QUESTION5), MB_YESNO) == IDNO)
		return;

	POSITION pos = m_ctrlListaSedi.GetFirstSelectedItemPosition();

	if (pos == NULL)
		return;

	long index = m_ctrlListaSedi.GetNextSelectedItem(pos);
	if (index < 0)
		return;


	CSediEsameSet set;
	CString sFilter;
	sFilter.Format("id=%li", m_ctrlListaSedi.GetItemData(index));
	set.SetOpenFilter(sFilter);

	if (set.OpenRecordset("CSediSaleDlg::OnBnClickedSedeCanc"))
	{
		if (!set.IsEOF())
		{
			if (set.DeleteRecordset("CSediSaleDlg::OnBnClickedSedeCanc"))
			{
				m_ctrlListaSedi.DeleteItem(index);
			}
		}

		set.CloseRecordset("CSediSaleDlg::OnBnClickedSedeCanc");
	}
	
}


void CSediSaleDlg::OnBnClickedSalaNuovo()
{
	//IDS_SEDISALE_QUESTION4
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_SEDISALE_QUESTION4), MB_YESNO) == IDNO)
		return;

	CSaleEsameSet set;

	if (set.OpenRecordset("CSediSaleDlg::OnBnClickedSalaNuovo"))
	{
		if (set.AddNewRecordset("CSediSaleDlg::OnBnClickedSalaNuovo"))
		{
			set.m_sDescrizione = theApp.GetMessageString(IDS_NUOVA_SALA).MakeUpper();
			set.m_lIDSede = m_lIdSedeSel;

			if (set.UpdateRecordset("CSediSaleDlg::OnBnClickedSalaNuovo"))
			{
				int index = m_ctrlListaSale.InsertItem(m_ctrlListaSale.GetItemCount(), theApp.GetMessageString(IDS_NUOVA_SALA).MakeUpper());
				m_ctrlListaSale.SetItemData(index, set.GetLastAdd());

				CString idSala;
				idSala.Format("%li", set.m_lID);
				m_ctrlListaSale.SetItemText(index, 1, idSala);

				m_ctrlListaSale.SetSubItemEdit(index, 0);
			}

			set.CloseRecordset("CSediSaleDlg::OnBnClickedSalaNuovo");
		}
	}

	for (int i = 0; i < m_ctrlListaSale.GetHeaderCtrl()->GetItemCount(); i++)
		m_ctrlListaSale.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
}


void CSediSaleDlg::OnBnClickedSalaCanc()
{
	//IDS_SEDISALE_QUESTION3
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_SEDISALE_QUESTION3), MB_YESNO) == IDNO)
		return;

	POSITION pos = m_ctrlListaSale.GetFirstSelectedItemPosition();

	if (pos == NULL)
		return;

	long index = m_ctrlListaSale.GetNextSelectedItem(pos);
	if (index < 0)
		return;


	CSediEsameSet set;
	CString sFilter;
	sFilter.Format("id=%li", m_ctrlListaSale.GetItemData(index));
	set.SetOpenFilter(sFilter);

	if (set.OpenRecordset("CSediSaleDlg::OnBnClickedSalaCanc"))
	{
		if (!set.IsEOF())
		{
			if (set.DeleteRecordset("CSediSaleDlg::OnBnClickedSalaCanc"))
			{
				m_ctrlListaSale.DeleteItem(index);
			}
		}

		set.CloseRecordset("CSediSaleDlg::OnBnClickedSalaCanc");
	}
}


void CSediSaleDlg::OnBnClickedAgendaNuovo()
{
	//IDS_SEDISALE_QUESTION2
	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_SEDISALE_QUESTION2), MB_YESNO) == IDNO)
		return;

	CAgendeSet set;

	if (set.OpenRecordset("CSediSaleDlg::OnBnClickedAgendaNuovo"))
	{
		if (set.AddNewRecordset("CSediSaleDlg::OnBnClickedAgendaNuovo"))
		{
			set.m_sDescrizione = theApp.GetMessageString(IDS_NUOVA_AGENDA).MakeUpper();
			set.m_lIDSala = m_lIdSalaSel;

			if (set.UpdateRecordset("CSediSaleDlg::OnBnClickedAgendaNuovo"))
			{
				int index = m_ctrlListaAgende.InsertItem(m_ctrlListaAgende.GetItemCount(), theApp.GetMessageString(IDS_NUOVA_AGENDA).MakeUpper());
				m_ctrlListaAgende.SetItemData(index, set.GetLastAdd());

				CString idAgenda;
				idAgenda.Format("%li", set.m_lID);
				m_ctrlListaAgende.SetItemText(index, 2, idAgenda);

				m_ctrlListaAgende.SetSubItemEdit(index, 0);
				m_ctrlListaAgende.SetSubItemEdit(index, 1);
			}

			set.CloseRecordset("CSediSaleDlg::OnBnClickedAgendaNuovo");
		}
	}

	for (int i = 0; i < m_ctrlListaAgende.GetHeaderCtrl()->GetItemCount(); i++)
		m_ctrlListaAgende.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
}


void CSediSaleDlg::OnBnClickedAgendaCanc()
{
	//IDS_SEDISALE_QUESTION1
	if (theApp.AfxMessageBoxEndo(theApp.AfxMessageBoxEndo(IDS_SEDISALE_QUESTION1), MB_YESNO) == IDNO)
		return;

	POSITION pos = m_ctrlListaAgende.GetFirstSelectedItemPosition();

	if (pos == NULL)
		return;

	long index = m_ctrlListaAgende.GetNextSelectedItem(pos);
	if (index < 0)
		return;


	CSediEsameSet set;
	CString sFilter;
	sFilter.Format("id=%li", m_ctrlListaAgende.GetItemData(index));
	set.SetOpenFilter(sFilter);

	if (set.OpenRecordset("CSediSaleDlg::OnBnClickedAgendaCanc"))
	{
		if (!set.IsEOF())
		{
			if (set.DeleteRecordset("CSediSaleDlg::OnBnClickedAgendaCanc"))
			{
				m_ctrlListaAgende.DeleteItem(index);
			}
		}

		set.CloseRecordset("CSediSaleDlg::OnBnClickedAgendaCanc");
	}
}