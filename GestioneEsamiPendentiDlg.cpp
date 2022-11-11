#include "stdafx.h"
#include "Endox.h"

#include "DLL_Imaging\h\AmLogin.h"

#include "CustomDate.h"
#include "EsamiView.h"
#include "ExtOrdiniSet.h"
#include "GestioneEsamiPendentiDlg.h"
#include "MediciSet.h"
#include "UOSet.h"
#include "VistaEsamiPendentiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CGestioneEsamiPendentiDlg, CResizableDialog)

CGestioneEsamiPendentiDlg::CGestioneEsamiPendentiDlg(CWnd* pParent, CEsamiView* pEsamiView)
: CResizableDialog(CGestioneEsamiPendentiDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
}

CGestioneEsamiPendentiDlg::~CGestioneEsamiPendentiDlg()
{
}

BEGIN_MESSAGE_MAP(CGestioneEsamiPendentiDlg, CResizableDialog)

	ON_BN_CLICKED(IDC_BTN_AGGIORNA, OnBnClickedBtnAggiorna)
	ON_BN_CLICKED(IDC_BTN_ESCI, OnBnClickedBtnEsci)
	ON_BN_CLICKED(IDC_BTN_STAMPA, OnBnClickedBtnStampa)

	ON_CBN_SELCHANGE(IDC_COMBO_DATA, OnCbnSelchangeComboData)
	ON_CBN_SELCHANGE(IDC_COMBO_MEDICO, OnCbnSelchangeComboMedico)
	ON_CBN_SELCHANGE(IDC_COMBO_UO, OnCbnSelchangeComboUO)

	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST, OnNMCustomdrawList)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnNMDblclkList)

END_MESSAGE_MAP()

void CGestioneEsamiPendentiDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_AGGIORNA, m_ctrlBtnAggiorna);
	DDX_Control(pDX, IDC_BTN_ESCI, m_ctrlBtnEsci);
	DDX_Control(pDX, IDC_BTN_STAMPA, m_ctrlBtnStampa);

	DDX_Control(pDX, IDC_COMBO_DATA, m_ctrlComboData);
	DDX_Control(pDX, IDC_COMBO_MEDICO, m_ctrlComboMedico);
	DDX_Control(pDX, IDC_COMBO_UO, m_ctrlComboUO);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);

	DDX_Control(pDX, IDC_EDIT_DATAINIZ, m_ctrlDataIniz);
	DDX_Control(pDX, IDC_EDIT_DATAFINE, m_ctrlDataFine);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC_4, m_ctrlStatic4);
	DDX_Control(pDX, IDC_STATIC_5, m_ctrlStatic5);
}

void CGestioneEsamiPendentiDlg::OnCancel()
{
}

BOOL CGestioneEsamiPendentiDlg::OnInitDialog()
{
	CResizableDialog::OnInitDialog();

	//
	AddAnchor(IDC_STATIC_1, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_COMBO_DATA, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_STATIC_2, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_EDIT_DATAINIZ, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_STATIC_3, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_EDIT_DATAFINE, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_STATIC_4, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_COMBO_MEDICO, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_STATIC_5, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_COMBO_UO, CSize(100, 0), CSize(100, 0));

	AddAnchor(IDC_LIST, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDC_BTN_AGGIORNA, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_BTN_STAMPA, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_BTN_ESCI, CSize(100, 100), CSize(100, 100));

	//
	InitComboDataPeriod(&m_ctrlComboData);
	m_ctrlDataIniz.SetEditMask("00/00/0000", "__/__/____");
	m_ctrlDataFine.SetEditMask("00/00/0000", "__/__/____");

	//
	RiempiComboUO();
	RiempiComboMedici();

	// Marvel Carvalho | BUG 3759 - TesiCapture Melhoria Filtro Worklist
	// restaura as variáveis que armazenam os filtros do usuário da tela esami pendenti
	ThisFilterFieldsRestore();
	//
	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlList.InsertColumn(0, "Paziente", CListSortableCtrl::type_string, LVCFMT_LEFT, 0); // theApp.GetMessageString(IDS_GEP_LIST_01)
	m_ctrlList.InsertColumn(1, "Tipo esame", CListSortableCtrl::type_string, LVCFMT_LEFT, 0); // theApp.GetMessageString(IDS_GEP_LIST_03)
	m_ctrlList.InsertColumn(2, "Data", CListSortableCtrl::type_date, LVCFMT_LEFT, 0); // theApp.GetMessageString(IDS_GEP_LIST_04)
	m_ctrlList.InsertColumn(3, "Tipo di paziente", CListSortableCtrl::type_string, LVCFMT_LEFT, 0); // theApp.GetMessageString(IDS_GEP_LIST_08)
	m_ctrlList.InsertColumn(4, "Medico", CListSortableCtrl::type_string, LVCFMT_LEFT, 0); // theApp.GetMessageString(IDS_GEP_LIST_05)
	m_ctrlList.InsertColumn(5, "Stazione", CListSortableCtrl::type_string, LVCFMT_LEFT, 0); // theApp.GetMessageString(IDS_GEP_LIST_06)
	m_ctrlList.InsertColumn(6, "Medico inviante", CListSortableCtrl::type_string, LVCFMT_LEFT, 0); // theApp.GetMessageString(IDS_GEP_LIST_07)
	m_ctrlList.InsertColumn(7, "Ficha", CListSortableCtrl::type_string, LVCFMT_LEFT, 0); // theApp.GetMessageString(IDS_GEP_LIST_09)
	m_ctrlList.InsertColumn(8, "Data consegna referto", CListSortableCtrl::type_date_time, LVCFMT_LEFT, 0); //Gabriel BUG 6225 - Lista DO FIX
	m_ctrlList.InsertColumn(9, "In refertazione", CListSortableCtrl::type_string, LVCFMT_LEFT, 0); // theApp.GetMessageString(IDS_GEP_LIST_10)
	m_ctrlList.InsertColumn(10, "", CListSortableCtrl::type_string, LVCFMT_LEFT, 0);

	int szOrder[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }; //Gabriel BUG 6225 - Lista DO FIX
	m_ctrlList.GetHeaderCtrl()->SetOrderArray(11, szOrder); //Gabriel BUG 6225 - Lista DO FIX

	TrySetCustomListOrder(theApp.m_sEsamiPendentiOrdineColonna, &m_ctrlList); //Julio BUG 3083 (punto 10)
	m_ctrlList.SetSortColumn(theApp.m_lEsamiPendentiColonnaOrdinare); //Gabriel BUG 6225 - Lista DO FIX

	// Abre a janela e já atualiza o grid com a seleção do filtro atual
	OnBnClickedBtnAggiorna();

	//
	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	//
	theApp.LocalizeDialog(this, IDD_GESTIONE_ESAMI_PENDENTI, "GestioneEsamiPendentiDlg");

	return TRUE;
}

void CGestioneEsamiPendentiDlg::OnOK()
{
}

void CGestioneEsamiPendentiDlg::OnBnClickedBtnAggiorna()
{
	BeginWaitCursor();
	m_ctrlList.SetRedraw(FALSE);

	m_listIDToHighlightYellow.RemoveAll();
	m_listIDToHighlightOrange.RemoveAll();
	m_listIDToHighlightRed.RemoveAll();
	m_ctrlList.DeleteAllItems();

	int nItem = 0;

	int iCurSelUO = m_ctrlComboUO.GetCurSel();
	CString sUOFilter;
	if (iCurSelUO <= 0)
		sUOFilter = "(UO=0 OR UO>0)";
	else
		sUOFilter.Format("UO=%li", m_ctrlComboUO.GetItemData(iCurSelUO));

	CString strFiltroData;
	GetCustomDateFilter(&strFiltroData, "EsameData", this, &m_ctrlComboData, IDC_EDIT_DATAINIZ, IDC_EDIT_DATAFINE);

	CString sFiltroMedico = "";
	int nCurSel = m_ctrlComboMedico.GetCurSel();
	if (nCurSel > 0)
		sFiltroMedico.Format("MedicoID=%li", m_ctrlComboMedico.GetItemData(nCurSel));

	CString sFilter = strFiltroData;
	sFilter.Trim();

	if (!sFiltroMedico.IsEmpty())
	{
		if (!sFilter.IsEmpty())
			sFilter += " AND ";

		sFilter += sFiltroMedico;
		sFilter.Trim();
	}

	CVistaEsamiPendentiSet setTemp;
	setTemp.SetBaseFilter(sUOFilter);
	setTemp.SetOpenFilter(sFilter);

	if (theApp.m_bPersonalizzazioniBrasileEinstein)
		setTemp.SetSortRecord("PAZIENTENOME, PAZIENTECOGNOME");
	else
	{
		switch (theApp.m_lEsamiPendentiColonnaOrdinare)
		{
		case 0:
			setTemp.SetSortRecord("PAZIENTECOGNOME, PAZIENTENOME");
		case 1:
			setTemp.SetSortRecord("PAZIENTECOGNOME, PAZIENTENOME");
		}
	}


	if (setTemp.OpenRecordset("CGestioneEsamiPendentiDlg::OnBnClickedBtnAggiorna"))
	{
		while (!setTemp.IsEOF())
		{
			CString sAnticipato = "";
			CString sPriorita = "";

			if (theApp.m_bPersonalizzazioniBrasileSirio)
			{
				CString sFilter;
				sFilter.Format("Contatore=%li", setTemp.m_lEsameID);

				CEsamiSet setEsamiTemp;
				setEsamiTemp.SetOpenFilter(sFilter);
				if (setEsamiTemp.OpenRecordset("CGestioneEsamiPendentiDlg::OnBnClickedBtnAggiorna"))
				{
					if (!setEsamiTemp.IsEOF())
					{
						sAnticipato = setEsamiTemp.m_setEP.m_sTesto099;
						sAnticipato.Trim();
					}

					setEsamiTemp.CloseRecordset("CGestioneEsamiPendentiDlg::OnBnClickedBtnAggiorna");
				}

				sPriorita = CExtOrdiniSet().GetPriorityFromID(setTemp.m_lEsameID);
				sPriorita.Trim();
			}

			CString sPazienteNominativo = setTemp.m_sPazienteCognome + " " + setTemp.m_sPazienteNome;
			if (theApp.m_bPersonalizzazioniBrasileEinstein)
				sPazienteNominativo = setTemp.m_sPazienteNome + " " + setTemp.m_sPazienteCognome;
			sPazienteNominativo.Trim();

			m_ctrlList.InsertItem(nItem, sPazienteNominativo);
			m_ctrlList.SetItemData(nItem, setTemp.m_lEsameID);

			setTemp.m_sEsameTipo.Trim();
			m_ctrlList.SetItemText(nItem, 1, setTemp.m_sEsameTipo);

			m_ctrlList.SetItemText(nItem, 2, CCustomDate(setTemp.m_lEsameData).GetDate("%d/%m/%Y"));

			m_ctrlList.SetItemText(nItem, 3, sPriorita);

			CString sMedicoNominativo = setTemp.m_sMedicoCognome + " " + setTemp.m_sMedicoNome;
			if (theApp.m_bPersonalizzazioniBrasileEinstein)
				sMedicoNominativo = setTemp.m_sMedicoNome + " " + setTemp.m_sMedicoCognome;
			sMedicoNominativo.Trim();
			m_ctrlList.SetItemText(nItem, 4, sMedicoNominativo);

			m_ctrlList.SetItemText(nItem, 5, setTemp.m_sEsameSala);

			m_ctrlList.SetItemText(nItem, 6, setTemp.m_sInvianteMedico);

			m_ctrlList.SetItemText(nItem, 7, setTemp.m_sFichaItem);


			//Gabriel BUG 6225 - Lista DO FIX
			CString sNewDate = FormatDate(setTemp.m_sTesto000);
			CString sNewTime = FormatTime(setTemp.m_sTesto000);
			CCustomDate cDate;
			cDate.SetDate(sNewDate);
			cDate.SetTime(sNewTime);
			long lDate = cDate.GetDate();

			m_ctrlList.SetItemText(nItem, 8, CCustomDate(lDate).GetDate("%d/%m/%Y %H:%M"));
			if (setTemp.m_lRefertoLen > 0)
			{
				CString sRedattoreNominativo = setTemp.m_sRedattoreCognome + " " + setTemp.m_sRedattoreNome;
				if (theApp.m_bPersonalizzazioniBrasileEinstein)
					sRedattoreNominativo = setTemp.m_sRedattoreNome + " " + setTemp.m_sRedattoreCognome;
				sRedattoreNominativo.Trim();

				if (sRedattoreNominativo.IsEmpty())
					m_ctrlList.SetItemText(nItem, 9, theApp.GetMessageString(IDS_YES));
				else
					m_ctrlList.SetItemText(nItem, 9, theApp.GetMessageString(IDS_YES) + " (" + sRedattoreNominativo + ")");
			}
			else
			{
				m_ctrlList.SetItemText(nItem, 9, theApp.GetMessageString(IDS_NO));
			}
			if (theApp.m_bPersonalizzazioniBrasileSirio)
			{
				/*
				if (setTemp.m_bInvianteSpeciale == TRUE) // lasciare == TRUE perchè gli invianti speciali NULL (e ce ne sono!) valgono 2 //
				m_listIDToHighlightYellow.AddTail(setTemp.m_lEsameID);
				*/

				if (sAnticipato.CompareNoCase("SIM") == 0)
					m_listIDToHighlightOrange.AddTail(setTemp.m_lEsameID);

				if (sPriorita.CompareNoCase(theApp.GetMessageString(IDS_URGENZA_SIRIO_3)) == 0)
					m_listIDToHighlightRed.AddTail(setTemp.m_lEsameID);
			}

#ifdef _DEBUG
			if (nItem > 250)
				break;
#endif

			nItem++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CGestioneEsamiPendentiDlg::OnBnClickedBtnAggiorna");
	}

	for (int i = 0; i < 10; i++)
		m_ctrlList.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);

	if (!theApp.m_bPersonalizzazioniBrasileSirio)
		m_ctrlList.SetColumnWidth(3, 0);

	if (!theApp.m_bPersonalizzazioniBrasileCamargo && !theApp.m_bPersonalizzazioniBrasileFleury)
		m_ctrlList.SetColumnWidth(8, 0);

	m_ctrlList.SetSortColumn(theApp.m_lEsamiPendentiColonnaOrdinare); //Gabriel BUG 6225 - Lista DO FIX
	m_ctrlList.SortColumn(theApp.m_lEsamiPendentiColonnaOrdinare); //Gabriel BUG 6225 - Lista DO FIX
	m_ctrlList.SetRedraw(TRUE);
	EndWaitCursor();
}

void CGestioneEsamiPendentiDlg::OnBnClickedBtnEsci()
{
	// Marvel Carvalho | BUG 3759 - TesiCapture Melhoria Filtro Worklist
	// salva as variáveis que armazenam os filtros do usuário da tela esami pendenti
	ThisFilterFieldsSave();

	CResizableDialog::OnOK();
}

void CGestioneEsamiPendentiDlg::OnBnClickedBtnStampa()
{
	m_ctrlList.Print();
}

void CGestioneEsamiPendentiDlg::OnCbnSelchangeComboData()
{
	ComboDataPeriodUpdated(&m_ctrlComboData, this, IDC_EDIT_DATAINIZ, IDC_EDIT_DATAFINE);

	OnBnClickedBtnAggiorna();
}

void CGestioneEsamiPendentiDlg::OnCbnSelchangeComboMedico()
{
	OnBnClickedBtnAggiorna();
}

void CGestioneEsamiPendentiDlg::OnCbnSelchangeComboUO()
{
	RiempiComboMedici();
	OnBnClickedBtnAggiorna();
}

void CGestioneEsamiPendentiDlg::RiempiComboUO()
{
	int nCurSel = 0;

	m_ctrlComboUO.ResetContent();
	m_ctrlComboUO.InsertString(0, theApp.GetMessageString(IDS_INVIANTE_TUTTI));
	m_ctrlComboUO.SetItemData(0, 0);

	CUOSet setTemp;
	setTemp.SetSortRecord("DESCRIZIONE");
	if (setTemp.OpenRecordset("CGestioneEsamiPendentiDlg::RiempiComboUO"))
	{
		int nIndex = 1;

		while (!setTemp.IsEOF())
		{
			m_ctrlComboUO.InsertString(nIndex, setTemp.m_sDescrizione);
			m_ctrlComboUO.SetItemData(nIndex, setTemp.m_lID);

			if ((theApp.m_default_GESTIONEESAMIPENDENTI_COMBOUO > 0) && (theApp.m_dwPrivileges & AMLogin_Permissions::configurations))
			{
				if (setTemp.m_lID == theApp.m_default_GESTIONEESAMIPENDENTI_COMBOUO)
					nCurSel = nIndex;
			}
			else
			{
				if (setTemp.m_lID == theApp.m_lUO)
					nCurSel = nIndex;
			}

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CGestioneEsamiPendentiDlg::RiempiComboUO");
	}

	m_ctrlComboUO.SetCurSel(nCurSel);

	// Sandro 20/09/2013 // RAS 20130152 //
	if (!(theApp.m_dwPrivileges & AMLogin_Permissions::configurations))
		m_ctrlComboUO.EnableWindow(FALSE);
}

void CGestioneEsamiPendentiDlg::RiempiComboMedici()
{
	int nCurSel = 0;

	//

	long lUserID = 0;
	AMLogin_GetUserID(&lUserID);

	//

	int iCurSelUO = m_ctrlComboUO.GetCurSel();

	CString sUOFilter;
	if (iCurSelUO <= 0)
		sUOFilter = "(UO=0 OR UO>0)";
	else
		sUOFilter.Format("IDUtenteEndox=%li AND UO=%li", lUserID, m_ctrlComboUO.GetItemData(iCurSelUO));

	CMediciSet setTemp;
	setTemp.SetBaseFilter(sUOFilter);
	if (theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
		setTemp.SetSortRecord("Nome, Cognome");
	else
		setTemp.SetSortRecord("Cognome, Nome");

	m_ctrlComboMedico.ResetContent();
	m_ctrlComboMedico.InsertString(0, theApp.GetMessageString(IDS_INVIANTE_TUTTI));
	m_ctrlComboMedico.SetItemData(0, 0);

	if (setTemp.OpenRecordset("CGestioneEsamiPendentiDlg::RiempiComboMedici"))
	{
		int nIndex = 1;

		while (!setTemp.IsEOF())
		{
			// Luiz - 24/06/2019 - P3 - Personalização da apresentação de nome de médico solicitante
			if (theApp.m_bPersonalizzazioniBrasileEinstein || theApp.m_bPersonalizzazioniBrasileFleury)
				m_ctrlComboMedico.InsertString(nIndex, setTemp.m_sTitolo + " " + setTemp.m_sNome + " " + setTemp.m_sCognome);
			else
				m_ctrlComboMedico.InsertString(nIndex, setTemp.m_sTitolo + " " + setTemp.m_sCognome + " " + setTemp.m_sNome);

			m_ctrlComboMedico.SetItemData(nIndex, setTemp.m_lContatore);

			if ((theApp.m_default_GESTIONEESAMIPENDENTI_COMBOMEDICO > 0) && (theApp.m_dwPrivileges & AMLogin_Permissions::configurations))
			{
				if (setTemp.m_lContatore == theApp.m_default_GESTIONEESAMIPENDENTI_COMBOMEDICO)
					nCurSel = nIndex;
			}
			else
			{
				if (setTemp.m_lIDUserEndox == lUserID)
					nCurSel = nIndex;
			}

			nIndex++;
			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CGestioneEsamiPendentiDlg::RiempiComboMedici");
	}

	m_ctrlComboMedico.SetCurSel(nCurSel);

	// Sandro 20/09/2013 // RAS 20130152 //
	if (!(theApp.m_dwPrivileges & AMLogin_Permissions::configurations))
		m_ctrlComboMedico.EnableWindow(FALSE);
}

void CGestioneEsamiPendentiDlg::OnNMCustomdrawList(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);

	*pResult = CDRF_DODEFAULT;

	switch (pLVCD->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;
	}
	case CDDS_ITEMPREPAINT:
	{
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
		break;
	}
	case (CDDS_ITEMPREPAINT | CDDS_SUBITEM) :
	{
		if (pLVCD->iSubItem == 0)
		{
			if (m_listIDToHighlightRed.Find(pLVCD->nmcd.lItemlParam) != NULL)
				pLVCD->clrTextBk = RGB(255, 0, 0);
			else if (m_listIDToHighlightOrange.Find(pLVCD->nmcd.lItemlParam) != NULL)
				pLVCD->clrTextBk = RGB(255, 127, 0);
			else if (m_listIDToHighlightYellow.Find(pLVCD->nmcd.lItemlParam) != NULL)
				pLVCD->clrTextBk = RGB(255, 255, 0);
		}

		break;
	}
	}
}

void CGestioneEsamiPendentiDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if (pNMItemActivate->iItem >= 0)
	{
		long lIDEsame = m_ctrlList.GetItemData(pNMItemActivate->iItem);

		if (CEsamiSet().GetUO(lIDEsame) != theApp.m_lUO)
		{
			theApp.AfxMessageBoxEndo(IDS_ESAME_ALTRA_UO);
		}
		else
		{
			long lIDPaziente = CEsamiSet().GetPaziente(lIDEsame);

			if ((lIDPaziente > 0) && (lIDEsame > 0))
			{
				if (m_pEsamiView->RicercaCodicePaziente(lIDPaziente, lIDEsame, FALSE, FALSE))
					m_pEsamiView->MovePazientiAndEsami(NULL, FALSE, TRUE);
				else
					m_pEsamiView->MovePazientiAndEsami(NULL, TRUE, TRUE);

				OnBnClickedBtnEsci();
			}
		}
	}

	*pResult = 0;
}



// Marvel Carvalho | BUG 3759 - TesiCapture Melhoria Filtro Worklist
// salva as variaveis do filtro para restaurar caso usuário volte para esta mesma tela
void CGestioneEsamiPendentiDlg::ThisFilterFieldsSave()
{
	theApp.m_default_GESTIONEESAMIPENDENTI_HasFilter = true;
	theApp.m_default_GESTIONEESAMIPENDENTI_COMBODATA = m_ctrlComboData.GetCurSel();

	int iCurSelUO = m_ctrlComboUO.GetCurSel();
	if (iCurSelUO > 0)
		theApp.m_default_GESTIONEESAMIPENDENTI_COMBOUO = m_ctrlComboUO.GetItemData(iCurSelUO);
	else
		theApp.m_default_GESTIONEESAMIPENDENTI_COMBOUO = 0;

	int iCurSelMedico = m_ctrlComboMedico.GetCurSel();

	if (iCurSelMedico > 0)
		theApp.m_default_GESTIONEESAMIPENDENTI_COMBOMEDICO = m_ctrlComboMedico.GetItemData(iCurSelMedico);
	else
		theApp.m_default_GESTIONEESAMIPENDENTI_COMBOMEDICO = 0;

	// atualiza as variáveis de data
	GetCustomDateFilter(&theApp.m_default_GESTIONEESAMIPENDENTI_DATAINIZ, &theApp.m_default_GESTIONEESAMIPENDENTI_DATAFINE, this, IDC_EDIT_DATAINIZ, IDC_EDIT_DATAFINE);
}

// Marvel Carvalho | BUG 3759 - TesiCapture Melhoria Filtro Worklist
// restaura as variaveis do filtro para quando usuário reabre esta tela
void CGestioneEsamiPendentiDlg::ThisFilterFieldsRestore()
{
	if (theApp.m_default_GESTIONEESAMIPENDENTI_HasFilter)
		m_ctrlComboData.SetCurSel(theApp.m_default_GESTIONEESAMIPENDENTI_COMBODATA);

	if (theApp.m_default_GESTIONEESAMIPENDENTI_DATAINIZ > 0)
		m_ctrlDataIniz.SetWindowText(CCustomDate(theApp.m_default_GESTIONEESAMIPENDENTI_DATAINIZ).GetDate("%d/%m/%Y"));

	if (theApp.m_default_GESTIONEESAMIPENDENTI_DATAFINE > 0)
		m_ctrlDataFine.SetWindowText(CCustomDate(theApp.m_default_GESTIONEESAMIPENDENTI_DATAFINE).GetDate("%d/%m/%Y"));

	ComboDataPeriodUpdated(&m_ctrlComboData, this, IDC_EDIT_DATAINIZ, IDC_EDIT_DATAFINE);
}

//Gabriel BUG 6225 - Lista DO FIX
CString CGestioneEsamiPendentiDlg::FormatDate(CString sDate)
{
	CString sFinalDate = "";
	sDate.Replace(":", "");
	sDate.Replace(" ", "");

	if (sDate.GetLength() == 14)
	{
		sFinalDate = sDate.Left(10);
	}

	return sFinalDate;
}

CString CGestioneEsamiPendentiDlg::FormatTime(CString sDate)
{
	CString sFinalTime = "";
	sDate.Replace(" ", "");
	sDate.Replace("-", "");

	if (sDate.GetLength() == 13)
	{
		sFinalTime += sDate.GetAt(8);
		sFinalTime += sDate.GetAt(9);
		sFinalTime += sDate.GetAt(10);
		sFinalTime += sDate.GetAt(11);
		sFinalTime += sDate.GetAt(12);
	}

	return sFinalTime;
}

int CALLBACK CGestioneEsamiPendentiDlg::MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl* pListCtrl = (CListCtrl*)lParamSort;

	int nItems = pListCtrl->GetItemCount();
	int nIndex1 = -1;
	int nIndex2 = -1;
	int i;

	for (i = 0; i < nItems; i++)
	{
		if (pListCtrl->GetItemData(i) == lParam1)
		{
			nIndex1 = i;
			break;
		}
	}
	for (i = 0; i < nItems; i++)
	{
		if (pListCtrl->GetItemData(i) == lParam2)
		{
			nIndex2 = i;
			break;
		}
	}

	if ((nIndex1 >= 0) && (nIndex2 >= 0))
	{
		int nResult = strcmp(pListCtrl->GetItemText(nIndex1, 0), pListCtrl->GetItemText(nIndex2, 0));
		if (nResult != 0)
			return nResult;

		nResult = strcmp(pListCtrl->GetItemText(nIndex1, 1), pListCtrl->GetItemText(nIndex2, 1));
		if (nResult != 0)
			return nResult;

		nResult = strcmp(pListCtrl->GetItemText(nIndex1, 2), pListCtrl->GetItemText(nIndex2, 2));
		if (nResult != 0)
			return nResult;

		return strcmp(pListCtrl->GetItemText(nIndex1, 3), pListCtrl->GetItemText(nIndex2, 3));
	}

	return 0;
}
