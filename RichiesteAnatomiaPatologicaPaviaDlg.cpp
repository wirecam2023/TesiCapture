#include "stdafx.h"
#include "Endox.h"
#include "RichiesteAnatomiaPatologicaPaviaDlg.h"

#include "CustomDate.h"
#include "EsamiView.h"
#include "MediciSet.h"
#include "VistaSospesiIstologiciSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CRichiesteAnatomiaPatologicaPaviaDlg, CEndoxResizableDlg)

CRichiesteAnatomiaPatologicaPaviaDlg::CRichiesteAnatomiaPatologicaPaviaDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxResizableDlg(CRichiesteAnatomiaPatologicaPaviaDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;

	m_bInitializing = FALSE;
}

CRichiesteAnatomiaPatologicaPaviaDlg::~CRichiesteAnatomiaPatologicaPaviaDlg()
{
}

BEGIN_MESSAGE_MAP(CRichiesteAnatomiaPatologicaPaviaDlg, CEndoxResizableDlg)

	ON_WM_CTLCOLOR()

	ON_MESSAGE(EM_SHOW_SOSPESIISTOLOGICI_WND, OnShowSospesiIstologiciWnd)

	ON_BN_CLICKED(IDC_BTN_AGGIORNA, OnBnClickedBtnAggiorna)
	
	ON_CBN_SELCHANGE(IDC_COMBO_MEDICO, OnCbnSelchangeComboMedico)
	ON_CBN_SELCHANGE(IDC_COMBO_DATA, OnCbnSelchangeComboData)

	ON_NOTIFY(NM_DBLCLK, IDC_LIST_NEW, OnNMDblclkList)

END_MESSAGE_MAP()

void CRichiesteAnatomiaPatologicaPaviaDlg::CreateModelessDialog(CWnd* pParent)
{	
	Create(CRichiesteAnatomiaPatologicaPaviaDlg::IDD, pParent);
}

void CRichiesteAnatomiaPatologicaPaviaDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_NEW, m_ctrlList);
	DDX_Control(pDX, IDC_COMBO_MEDICO, m_ctrlComboMedico);
	DDX_Control(pDX, IDC_COMBO_DATA, m_ctrlComboData);

	DDX_Control(pDX, IDC_EDIT_DATAINIZ, m_ctrlDataFine);
	DDX_Control(pDX, IDC_EDIT_DATAFINE, m_ctrlDataIniz);
}

BOOL CRichiesteAnatomiaPatologicaPaviaDlg::OnInitDialog() 
{
	BOOL bReturn = CEndoxResizableDlg::OnInitDialog();

	m_bInitializing = TRUE;

	AddAnchor(IDOK, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_LIST_NEW, CSize(0, 0), CSize(100, 100));

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	GetDlgItem(IDC_STATIC2)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_COMBO_MEDICO)->SetFont(&theApp.m_fontBold);

	//

	m_ctrlComboMedico.AddString(" ");

	CMediciSet setMedici;
	setMedici.SetOpenFilter("ELIMINATO=0");
	if (theApp.m_bPersonalizzazioniBrasileEinstein)
		setMedici.SetSortRecord("Nome, Cognome");
	else
		setMedici.SetSortRecord("Cognome, Nome");
	if (setMedici.OpenRecordset("CRichiesteAnatomiaPatologicaPaviaDlg::OnInitDialog"))
	{
		while(!setMedici.IsEOF())
		{
			// Luiz - 24/06/2019 - P3 - Personalização da apresentação de nome de médico solicitante
			int nCurr;
			if (theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
				nCurr = m_ctrlComboMedico.AddString(setMedici.m_sNome + " " + setMedici.m_sCognome);
			else
				nCurr = m_ctrlComboMedico.AddString(setMedici.m_sCognome + " " + setMedici.m_sNome);
			m_ctrlComboMedico.SetItemData(nCurr, setMedici.m_lContatore);
			setMedici.MoveNext();
		}

		setMedici.CloseRecordset("CRichiesteAnatomiaPatologicaPaviaDlg::OnInitDialog");
	}

	InitComboDataPeriod(&m_ctrlComboData);

	m_ctrlDataIniz.SetEditMask("00/00/0000", "__/__/____");
	m_ctrlDataFine.SetEditMask("00/00/0000", "__/__/____");

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlList.InsertColumn(0, "", LVCFMT_LEFT, 0);
	m_ctrlList.InsertColumn(1, "", LVCFMT_LEFT, 0);
	m_ctrlList.InsertColumn(2, "Paziente", LVCFMT_LEFT, 200);
	m_ctrlList.InsertColumn(3, "Esame", LVCFMT_LEFT, 200);
	m_ctrlList.InsertColumn(4, "Medico", LVCFMT_LEFT, 150);
	m_ctrlList.InsertColumn(5, "", LVCFMT_LEFT, 0);

	m_ctrlComboMedico.SetCurSel(-1);

	m_bInitializing = FALSE;

	RiempiLista();

	theApp.LocalizeDialog(this, CRichiesteAnatomiaPatologicaPaviaDlg::IDD, "RichiesteAnatomiaPatologicaPaviaDlg");

	return bReturn;
}

void CRichiesteAnatomiaPatologicaPaviaDlg::OnOK()
{
	m_pEsamiView->PostMessage(EM_HIDE_SOSPESIISTOLOGICI_WND);
}

void CRichiesteAnatomiaPatologicaPaviaDlg::RiempiLista()
{
	if (!m_bInitializing)
	{
		CVistaSospesiIstologiciSet setTemp;

		CString strComboMedico = "";
		int nComboMedico = m_ctrlComboMedico.GetCurSel();
		if (nComboMedico > 0)
			strComboMedico.Format("Medico=%li", (long)m_ctrlComboMedico.GetItemData(nComboMedico));

		CString strFiltroData;
		GetCustomDateFilter(&strFiltroData, "Data", this, &m_ctrlComboData, IDC_EDIT_DATAINIZ, IDC_EDIT_DATAFINE);

		CString strFilter = "";
		if (!strComboMedico.IsEmpty() && !strFiltroData.IsEmpty())
		{
			strFilter = strComboMedico + " AND " + strFiltroData;
		}
		else if (!strComboMedico.IsEmpty())
		{
			strFilter = strComboMedico;
		}
		else if (!strFiltroData.IsEmpty())
		{
			strFilter = strFiltroData;
		}
		strFilter.MakeUpper();

		m_ctrlList.ShowWindow(SW_HIDE);
		m_ctrlList.DeleteAllItems();

		BeginWaitCursor();
		theApp.m_dbEndox.SetQueryTimeout(300);

		setTemp.SetOpenFilter(strFilter);

		if (setTemp.OpenRecordset("CRichiesteAnatomiaPatologicaPaviaDlg::RiempiLista"))
		{
			int nItem = 0;

			while(!setTemp.IsEOF())
			{
				// ricostruisco i dati del paziente //
				CCustomDate datePaziente(setTemp.m_lNatoIlCustom);

				CString strPaziente = setTemp.m_sCognome;
				strPaziente.Trim();
				if (!strPaziente.IsEmpty())
					strPaziente += " ";
				strPaziente += setTemp.m_sNome;
				strPaziente.Trim();
				strPaziente += datePaziente.GetDate(" (%d/%m/%Y)");
				strPaziente.Trim();

				// ricostruisco i dati dell'esame //
				CCustomDate dateEsame(setTemp.m_lData);
				setTemp.m_sDescrizioneEsame.Trim();

				CString strEsame = dateEsame.GetDate("%d/%m/%Y - ") + setTemp.m_sDescrizioneEsame;
				strEsame.Trim();
				strEsame.Replace("  ", " ");
				
				// ricostruisco i nomi dei medici //
				setTemp.m_sCognomeMedico.Trim();
				setTemp.m_sNomeMedico.Trim();
				CString strMedico = setTemp.m_sCognomeMedico + " " + setTemp.m_sNomeMedico;
				strMedico.Trim();

				///
				CString strTemp;

				strTemp.Format("%li", setTemp.m_lIDPaziente);
				m_ctrlList.InsertItem(nItem, strTemp);
				m_ctrlList.SetItemData(nItem, setTemp.m_lIDEsame);

				strTemp.Format("%li", setTemp.m_lIDEsame);
				m_ctrlList.SetItemText(nItem, 1, strTemp);

				m_ctrlList.SetItemText(nItem, 2, strPaziente);

				m_ctrlList.SetItemText(nItem, 3, strEsame);

				m_ctrlList.SetItemText(nItem, 4, strMedico);

				nItem++;
				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CRichiesteAnatomiaPatologicaPaviaDlg::RiempiLista");
		}

		theApp.m_dbEndox.SetQueryTimeout(15);
		EndWaitCursor();

		m_ctrlList.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlList.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlList.SetColumnWidth(4, LVSCW_AUTOSIZE_USEHEADER);

		m_ctrlList.ShowWindow(SW_SHOW);
	}
}

void CRichiesteAnatomiaPatologicaPaviaDlg::OnCbnSelchangeComboMedico()
{
	// RiempiLista();
}

void CRichiesteAnatomiaPatologicaPaviaDlg::OnCbnSelchangeComboData()
{
	ComboDataPeriodUpdated(&m_ctrlComboData, this, IDC_EDIT_DATAINIZ, IDC_EDIT_DATAFINE);
}

void CRichiesteAnatomiaPatologicaPaviaDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nCurSel = m_ctrlList.GetNextSelectedItem(pos);
		if (nCurSel >= 0)
		{
			m_pEsamiView->RicercaCodicePaziente(atol(m_ctrlList.GetItemText(nCurSel, 0)), atol(m_ctrlList.GetItemText(nCurSel, 1)), FALSE, TRUE);
			m_pEsamiView->MovePazientiAndEsami(NULL, FALSE, TRUE);

			OnOK();
		}
	}
}

LRESULT CRichiesteAnatomiaPatologicaPaviaDlg::OnShowSospesiIstologiciWnd(WPARAM, LPARAM)
{
	ShowWindow(SW_SHOW);

	return 1;
}

void CRichiesteAnatomiaPatologicaPaviaDlg::OnBnClickedBtnAggiorna()
{
	UpdateData(TRUE);
	RiempiLista();
}