 #include "stdafx.h"
#include "Endox.h"
#include "ListaPrenotazioniCupDlg.h"

#include <cctype>

#include "DLL_Imaging\h\AmLogin.h"

#include "CustomDate.h"
#include "EliminaCodeSet.h"
#include "EndoxMenu.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "ListaPrenotazioniCupDettaglioDlg.h"
#include "MediciSet.h"
#include "MotivoAnnullamentoDlg.h"
#include "SaleEsameSet.h"
#include "SediEsameSet.h"
#include "TipoEsameSet.h"
#include "UOSet.h"
#include "UOUtenteDlg.h"
#include "UOUtenteSet.h"
#include "VistaFleuryURMSet.h"

#include "ComboPrestazioni.h" //Julio - BUG 3365 - MAMOGUS
#include "VistaComboPrestazioni.h" //Julio - BUG 3365 - MAMOGUS
#include "ExtComboPrestazioni.h" //Julio - BUG 3365 - MAMOGUS
#include "DocManager.h" //Gabriel BUG 6225 - Lista DO
#include "FoglioRiferimentoSet.h"//Gabriel BUG 6225 - Lista DO

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CListaPrenotazioniCupDlg::CListaPrenotazioniCupDlg(CWnd* pParent, CEsamiView* pEsamiView, long lIDExtOrdiniAutoImport, CString sFicha)
	: CEndoxResizableDlg(CListaPrenotazioniCupDlg::IDD, pParent)
{
	m_pEsamiView = pEsamiView;
	m_lIDExtOrdiniAutoImport = lIDExtOrdiniAutoImport;

	m_bFieldsEnabled = FALSE;

	m_pWorkListManager = new CCupWorkListManager(pEsamiView);
	ASSERT(m_pWorkListManager != NULL);

	// Sandro 20/04/2015 //

	LOGFONT lf;
	theApp.m_fontNormal.GetLogFont(&lf);

	lf.lfHeight = (lf.lfHeight * theApp.m_lWorklistFattoreIngrandimento) / 100;
	lf.lfWidth = (lf.lfWidth * theApp.m_lWorklistFattoreIngrandimento) / 100;

	m_fontWorklist.CreateFontIndirect(&lf);

	// Sandro 13/10/2015 // RIMA 15107 //

	long lUserID;
	AMLogin_GetUserID(&lUserID);
	m_lNumeroUOUtente = CUOUtenteSet().ContaUOUtente(lUserID);

	// Sandro 21/02/2017 //

	m_bInitializing = TRUE;

	// Julio 22/01/2018 //

	m_sFichaPreviamenteSelecionada = sFicha;
	m_bIsExiting = FALSE;
}

CListaPrenotazioniCupDlg::~CListaPrenotazioniCupDlg()
{
	if (m_pWorkListManager)
	{
		delete m_pWorkListManager;
		m_pWorkListManager = NULL;
	}
}

BEGIN_MESSAGE_MAP(CListaPrenotazioniCupDlg, CEndoxResizableDlg)

	ON_BN_CLICKED(IDC_AGGIORNA, OnAggiorna)

	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblClkList)
	ON_NOTIFY(NM_RCLICK, IDC_LIST, OnNMRClickList)
	ON_CBN_SELCHANGE(IDC_COMBO_STATO, OnCbnSelchangeComboStato)
	ON_CBN_SELCHANGE(IDC_COMBO_SEDE, OnCbnSelchangeComboSede)
	ON_CBN_SELCHANGE(IDC_COMBO_SALA, OnCbnSelchangeComboSala)
	ON_CBN_SELCHANGE(IDC_COMBO_PROVENIENZA, OnCbnSelchangeComboProvenienza)
	ON_CBN_SELCHANGE(IDC_COMBO_DATA, OnCbnSelchangeComboData)
	ON_CBN_SELCHANGE(IDC_COMBO_UNIDADE, OnCbnSelchangeComboUnidade)
	ON_CBN_SELCHANGE(IDC_COMBO_REGIONAL, OnCbnSelchangeComboRegional)
	ON_CBN_SELCHANGE(IDC_COMBO_MARCA, OnCbnSelchangeComboMarca)

	ON_MESSAGE(WM_CURCHANGE, OnGestioneCursore)

	ON_BN_CLICKED(IDC_BTN_CAMBIAUO, OnBnClickedCambiaUO)
	ON_BN_CLICKED(IDC_BTN_STAMPA, OnBnClickedStampa)
	ON_BN_CLICKED(IDC_BTN_PRINTLIST, OnBnClickedPrintList)
	ON_BN_CLICKED(IDC_CHK_FILTERDATA, OnBnClickedChkFilterData)

	ON_COMMAND(ID_PRENOTATI_DETTAGLI, OnDettagli)
	ON_COMMAND(ID_IP_DETTAGLI, OnDettagli)
	ON_COMMAND(ID_EROGATI_DETTAGLI, OnDettagli)
	ON_COMMAND(ID_ACC_DETTAGLI, OnDettagli)
	ON_COMMAND(ID_NONPRES_DETTAGLI, OnDettagli)	

	ON_COMMAND(ID_IP_VEDIESAME, OnVediEsame)
	ON_COMMAND(ID_EROGATI_VEDIESAME, OnVediEsame)

	ON_COMMAND(ID_IP_ANNULLA, OnAnnullaIP)
	ON_COMMAND(ID_ACC_START, OnStart)
	ON_COMMAND(ID_ACC_NONPRESENTATO, OnNonPresentato)	
	ON_COMMAND(ID_NONPRES_PRESENTE, OnPresentato)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnLvnItemchangedList)

END_MESSAGE_MAP()

void CListaPrenotazioniCupDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST, m_ctrlList);
	DDX_Control(pDX, IDC_AGGIORNA, m_ctrlButtonRefresh);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDC_BTN_CAMBIAUO, m_ctrlBtnCambiaUO);
	DDX_Control(pDX, IDC_BTN_STAMPA, m_ctrlButtonStampa);
	DDX_Control(pDX, IDC_BTN_PRINTLIST, m_ctrlButtonPrintList);
	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_STATIC_4, m_ctrlStatic4);
	DDX_Control(pDX, IDC_STATIC_5, m_ctrlStatic5);
	DDX_Control(pDX, IDC_STATIC_6, m_ctrlStatic6);
	DDX_Control(pDX, IDC_STATIC_7, m_ctrlStatic7);
	DDX_Control(pDX, IDC_STATIC_8, m_ctrlStatic8);
	DDX_Control(pDX, IDC_STATIC_9, m_ctrlStatic9);
	DDX_Control(pDX, IDC_STATIC_STATO, m_ctrlStaticStato);
	DDX_Control(pDX, IDC_STATIC_PROVENIENZA, m_ctrlStaticProvenienza);
	DDX_Control(pDX, IDC_STATIC_SEDE, m_ctrlStaticSede);
	DDX_Control(pDX, IDC_STATIC_SALA, m_ctrlStaticSala);
	DDX_Control(pDX, IDC_COMBO_STATO, m_ctrlComboStato);
	DDX_Control(pDX, IDC_COMBO_SEDE, m_ctrlComboSede);
	DDX_Control(pDX, IDC_COMBO_SALA, m_ctrlComboSala);
	DDX_Control(pDX, IDC_COMBO_PROVENIENZA, m_ctrlComboProvenienza);
	DDX_Control(pDX, IDC_CHK_FILTERDATA, m_ctrlChkFilterData);
	DDX_Control(pDX, IDC_COMBO_DATA, m_ctrlComboData);
	DDX_Control(pDX, IDC_EDIT_DATAINIZ, m_ctrlDataIniz);
	DDX_Control(pDX, IDC_EDIT_DATAFINE, m_ctrlDataFine);

	DDX_Control(pDX, IDC_STATIC_097, m_ctrlStatic097);
	DDX_Control(pDX, IDC_STATIC_098, m_ctrlStatic098);
	DDX_Control(pDX, IDC_STATIC_099, m_ctrlStatic099);
	DDX_Control(pDX, IDC_COMBO_UNIDADE, m_ctrlComboUnidade);
	DDX_Control(pDX, IDC_COMBO_REGIONAL, m_ctrlComboRegional);
	DDX_Control(pDX, IDC_COMBO_MARCA, m_ctrlComboMarca);

	DDX_Control(pDX, IDC_TEXTCONTROL_HIDE, m_ctrlTextControlHide);
	m_ctrlTextControlHide.SendMessage(WM_USER + 1013, 1, 0); // così NON carica i font dalla stampante predefinita perché in certi casi dava RTF filter error... //
}

BOOL CListaPrenotazioniCupDlg::OnInitDialog()
{
	CEndoxResizableDlg::OnInitDialog();

	InitComboDataPeriod(&m_ctrlComboData);

	m_ctrlDataIniz.SetEditMask("00/00/0000", "__/__/____");
	m_ctrlDataFine.SetEditMask("00/00/0000", "__/__/____");
	
	m_ctrlChkFilterData.SetCheck(CUOSet().GetFastFichaWorklist(theApp.m_lUO) ? BST_CHECKED : BST_UNCHECKED);

	// Sandro 10/06/2015 // RIMA 15040 //

	if (theApp.m_bPersonalizzazioniBrasileSirio && !theApp.m_bPersonalizzazioniBrasileEinstein) // Sandro 30/06/2016 // aggiunto il discorso dell'Einstein //
	{
		m_ctrlStatic5.ShowWindow(SW_HIDE);

		m_ctrlStatic6.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_CODICERICOVERO)->ShowWindow(SW_SHOW);

		//

		CRect rectTemp;

		m_ctrlStatic1.GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		rectTemp.top += 6;
		m_ctrlStatic1.SetWindowPos(NULL, rectTemp.left, rectTemp.top, rectTemp.Width(), rectTemp.Height(), SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_EDIT_NUMORDINE)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		rectTemp.top += 6;
		GetDlgItem(IDC_EDIT_NUMORDINE)->SetWindowPos(NULL, rectTemp.left, rectTemp.top, rectTemp.Width(), rectTemp.Height(), SWP_NOSIZE | SWP_NOZORDER);

		m_ctrlStatic2.GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		rectTemp.top += 6;
		m_ctrlStatic2.SetWindowPos(NULL, rectTemp.left, rectTemp.top, rectTemp.Width(), rectTemp.Height(), SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_EDIT_CODPAZIENTE)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		rectTemp.top += 6;
		GetDlgItem(IDC_EDIT_CODPAZIENTE)->SetWindowPos(NULL, rectTemp.left, rectTemp.top, rectTemp.Width(), rectTemp.Height(), SWP_NOSIZE | SWP_NOZORDER);

		m_ctrlStatic3.GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		rectTemp.top += 6;
		m_ctrlStatic3.SetWindowPos(NULL, rectTemp.left, rectTemp.top, rectTemp.Width(), rectTemp.Height(), SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_EDIT_COGNOME)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		rectTemp.top += 6;
		GetDlgItem(IDC_EDIT_COGNOME)->SetWindowPos(NULL, rectTemp.left, rectTemp.top, rectTemp.Width(), rectTemp.Height(), SWP_NOSIZE | SWP_NOZORDER);

		m_ctrlStatic4.GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		rectTemp.top += 6;
		m_ctrlStatic4.SetWindowPos(NULL, rectTemp.left, rectTemp.top, rectTemp.Width(), rectTemp.Height(), SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_EDIT_NOME)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		rectTemp.top += 6;
		GetDlgItem(IDC_EDIT_NOME)->SetWindowPos(NULL, rectTemp.left, rectTemp.top, rectTemp.Width(), rectTemp.Height(), SWP_NOSIZE | SWP_NOZORDER);
	}

	if (theApp.m_bCentraleControlloQualita)
	{
		CRect rectTemp;

		int nOffset = 30;

		GetDlgItem(IDC_ESAMI_IN_LISTA)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		rectTemp.top += nOffset;
		GetDlgItem(IDC_ESAMI_IN_LISTA)->SetWindowPos(NULL, rectTemp.left, rectTemp.top, rectTemp.Width(), rectTemp.Height(), SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_STATIC_UO)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		rectTemp.top += nOffset;
		GetDlgItem(IDC_STATIC_UO)->SetWindowPos(NULL, rectTemp.left, rectTemp.top, rectTemp.Width(), rectTemp.Height(), SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_ULTIMO_AGGIORNAMENTO)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		rectTemp.top += nOffset;
		GetDlgItem(IDC_ULTIMO_AGGIORNAMENTO)->SetWindowPos(NULL, rectTemp.left, rectTemp.top, rectTemp.Width(), rectTemp.Height(), SWP_NOSIZE | SWP_NOZORDER);

		GetDlgItem(IDC_LIST)->GetWindowRect(rectTemp);
		ScreenToClient(rectTemp);
		rectTemp.top += nOffset;
		GetDlgItem(IDC_LIST)->SetWindowPos(NULL, rectTemp.left, rectTemp.top, rectTemp.Width(), rectTemp.Height(), SWP_NOZORDER);

		//

		m_ctrlComboUnidade.InsertString(0, theApp.GetMessageString(IDS_TUTTE));

		CVistaFleuryURMSet setU;
		setU.SetView(VIEW_UNIDADE);
		if (setU.OpenRecordset("CListaPrenotazioniCupDlg::OnInitDialog"))
		{
			int nIndex = 1;
			while (!setU.IsEOF())
			{
				m_ctrlComboUnidade.InsertString(nIndex, setU.m_sValori);

				nIndex++;
				setU.MoveNext();
			}

			setU.CloseRecordset("CListaPrenotazioniCupDlg::OnInitDialog");
		}

		//

		m_ctrlComboRegional.InsertString(0, theApp.GetMessageString(IDS_TUTTE));

		CVistaFleuryURMSet setR;
		setR.SetView(VIEW_REGIONAL);
		if (setR.OpenRecordset("CListaPrenotazioniCupDlg::OnInitDialog"))
		{
			int nIndex = 1;
			while (!setR.IsEOF())
			{
				m_ctrlComboRegional.InsertString(nIndex, setR.m_sValori);

				nIndex++;
				setR.MoveNext();
			}

			setR.CloseRecordset("CListaPrenotazioniCupDlg::OnInitDialog");
		}

		//

		m_ctrlComboMarca.InsertString(0, theApp.GetMessageString(IDS_TUTTE));

		CVistaFleuryURMSet setM;
		setM.SetView(VIEW_MARCA);
		if (setM.OpenRecordset("CListaPrenotazioniCupDlg::OnInitDialog"))
		{
			int nIndex = 1;
			while (!setM.IsEOF())
			{
				m_ctrlComboMarca.InsertString(nIndex, setM.m_sValori);

				nIndex++;
				setM.MoveNext();
			}

			setM.CloseRecordset("CListaPrenotazioniCupDlg::OnInitDialog");
		}

		//

		m_ctrlStatic097.ShowWindow(SW_SHOW);
		m_ctrlStatic098.ShowWindow(SW_SHOW);
		m_ctrlStatic099.ShowWindow(SW_SHOW);
		m_ctrlComboUnidade.ShowWindow(SW_SHOW);
		m_ctrlComboRegional.ShowWindow(SW_SHOW);
		m_ctrlComboMarca.ShowWindow(SW_SHOW);
	}

	//

	AddAnchor(IDC_STATIC_5, CSize(0, 0), CSize(40, 0));

	AddAnchor(IDC_STATIC_6, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_STATIC_1, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_STATIC_2, CSize(0, 0), CSize(0, 0));
	AddAnchor(IDC_EDIT_CODICERICOVERO, CSize(0, 0), CSize(20, 0));
	AddAnchor(IDC_EDIT_NUMORDINE, CSize(0, 0), CSize(20, 0));
	AddAnchor(IDC_EDIT_CODPAZIENTE, CSize(0, 0), CSize(20, 0));

	AddAnchor(IDC_STATIC_3, CSize(20, 0), CSize(20, 0));
	AddAnchor(IDC_STATIC_4, CSize(20, 0), CSize(20, 0));
	AddAnchor(IDC_EDIT_COGNOME, CSize(20, 0), CSize(40, 0));
	AddAnchor(IDC_EDIT_NOME, CSize(20, 0), CSize(40, 0));

	AddAnchor(IDC_STATIC_7, CSize(40, 0), CSize(40, 0));
	AddAnchor(IDC_STATIC_8, CSize(40, 0), CSize(40, 0));
	AddAnchor(IDC_STATIC_9, CSize(40, 0), CSize(40, 0));
	AddAnchor(IDC_COMBO_DATA, CSize(40, 0), CSize(60, 0));
	AddAnchor(IDC_EDIT_DATAINIZ, CSize(40, 0), CSize(60, 0));
	AddAnchor(IDC_EDIT_DATAFINE, CSize(40, 0), CSize(60, 0));

	AddAnchor(IDC_STATIC_STATO, CSize(60, 0), CSize(60, 0));
	AddAnchor(IDC_STATIC_PROVENIENZA, CSize(60, 0), CSize(60, 0));
	AddAnchor(IDC_COMBO_STATO, CSize(60, 0), CSize(80, 0));
	AddAnchor(IDC_COMBO_PROVENIENZA, CSize(60, 0), CSize(80, 0));
	AddAnchor(IDC_CHK_FILTERDATA, CSize(60, 0), CSize(80, 0));

	AddAnchor(IDC_STATIC_SEDE, CSize(80, 0), CSize(80, 0));
	AddAnchor(IDC_STATIC_SALA, CSize(80, 0), CSize(80, 0));
	AddAnchor(IDC_COMBO_SEDE, CSize(80, 0), CSize(100, 0));
	AddAnchor(IDC_COMBO_SALA, CSize(80, 0), CSize(100, 0));
	AddAnchor(IDC_AGGIORNA, CSize(80, 0), CSize(100, 0));

	AddAnchor(IDC_ESAMI_IN_LISTA, CSize(0, 0), CSize(50, 0));
	AddAnchor(IDC_STATIC_UO, CSize(50, 0), CSize(50, 0));
	AddAnchor(IDC_ULTIMO_AGGIORNAMENTO, CSize(50, 0), CSize(100, 0));

	AddAnchor(IDC_LIST, CSize(0, 0), CSize(100, 100));

	AddAnchor(IDC_BTN_CAMBIAUO, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_BTN_STAMPA, CSize(0, 100), CSize(0, 100));

	AddAnchor(IDC_BTN_PRINTLIST, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDOK, CSize(100, 100), CSize(100, 100));

	AddAnchor(IDC_STATIC_097, CSize(40, 0), CSize(40, 0));
	AddAnchor(IDC_STATIC_098, CSize(60, 0), CSize(60, 0));
	AddAnchor(IDC_STATIC_099, CSize(80, 0), CSize(80, 0));
	AddAnchor(IDC_COMBO_UNIDADE, CSize(40, 0), CSize(60, 0));
	AddAnchor(IDC_COMBO_REGIONAL, CSize(60, 0), CSize(80, 0));
	AddAnchor(IDC_COMBO_MARCA, CSize(80, 0), CSize(100, 0));

	//

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	// Sandro 20/04/2015 //

	GetDlgItem(IDC_ESAMI_IN_LISTA)->SetFont(&theApp.m_fontBold);

	m_ctrlList.SetFont(&m_fontWorklist);

	//

	m_ctrlList.SetExtendedStyle(m_ctrlList.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	
	// Sandro 17/04/2015 //

	RiempiComboStatiWorklist(&m_ctrlComboStato, theApp.m_lWorklistStatoDaSelezionare, CUOSet().GetFastFichaWorklist(theApp.m_lUO));

	// Sandro 30/10/2013 //

	m_ctrlComboProvenienza.InsertString(0, theApp.GetMessageString(IDS_TUTTI)); //  "TUTTI");
	m_ctrlComboProvenienza.SetItemData(0, -1);

	m_ctrlComboProvenienza.InsertString(1, theApp.GetMessageString(IDS_INTERNI)); // "INTERNI");
	m_ctrlComboProvenienza.SetItemData(1, 0);

	m_ctrlComboProvenienza.InsertString(2, theApp.GetMessageString(IDS_ESTERNI)); // "ESTERNI");
	m_ctrlComboProvenienza.SetItemData(2, 1);

	m_ctrlComboProvenienza.SetCurSel(0);

	//

	RiempiComboSedi();
	// RiempiComboSale(); // si riempie da sola //

	//

	theApp.LocalizeDialog(this, CListaPrenotazioniCupDlg::IDD, "ListaPrenotazioniCupDlg");

	m_pWorkListManager->PrepareList(&m_ctrlList);
	if (CUOSet().GetFastFichaWorklist(theApp.m_lUO))
		m_ctrlList.SetColumnWidth(0, 120);

	// Sandro 28/07/2015 //

	// RiempiLista("", "", "", "", ""); // sostituita dalle due righe sotto //
	m_ctrlComboData.SetCurSel(1);
	OnCbnSelchangeComboData();

	// Sandro 13/10/2015 // RIMA 15107 //

	GetDlgItem(IDC_STATIC_UO)->SetFont(&theApp.m_fontBold);
	SetDlgItemText(IDC_STATIC_UO, theApp.GetMessageString(IDS_UO) + ": " + CUOSet().GetDescrizione(theApp.m_lUO));

	if (m_lNumeroUOUtente > 1)
		m_ctrlBtnCambiaUO.ShowWindow(SW_SHOW);

	// Marvel Carvalho | BUG 3759 - TesiCapture Melhoria Filtro Worklist
	if (m_sFichaPreviamenteSelecionada.IsEmpty()) {
		ThisFilterFieldsRestore();
	}

	// Julio 22/01/2018 //
	if (m_sFichaPreviamenteSelecionada.GetLength() == 10)
	{
		m_ctrlChkFilterData.SetCheck(BST_CHECKED);
		RiempiLista(m_sFichaPreviamenteSelecionada, "", "", "", "");
	}
	
	EnableFields(TRUE);

	m_bInitializing = FALSE;
	return TRUE;
}

// atualiza a consulta: busca na base de dados e atualiza o grid
BOOL CListaPrenotazioniCupDlg::UpdateFiltering() {
	CString sRicCodiceRicovero;
	GetDlgItem(IDC_EDIT_CODICERICOVERO)->GetWindowText(sRicCodiceRicovero);

	CString sRicNumOrdine;
	GetDlgItem(IDC_EDIT_NUMORDINE)->GetWindowText(sRicNumOrdine);

	CString sRicCodPaziente;
	GetDlgItem(IDC_EDIT_CODPAZIENTE)->GetWindowText(sRicCodPaziente);

	CString sRicCognome;
	GetDlgItem(IDC_EDIT_COGNOME)->GetWindowText(sRicCognome);

	CString sRicNome;
	GetDlgItem(IDC_EDIT_NOME)->GetWindowText(sRicNome);

	return RiempiLista(sRicCodiceRicovero, sRicNumOrdine, sRicCodPaziente, sRicCognome, sRicNome);
}

void CListaPrenotazioniCupDlg::OnOK()
{
	if (m_pWorkListManager->m_bTipoEsameDlg)
		return;
	// Marvel Carvalho | BUG 3759 - TesiCapture Melhoria Filtro Worklist
	// SE detectou um ENTER em uma linha da LISTA
	if (GetFocus() == GetDlgItem(IDC_LIST) && m_bIsExiting == FALSE){ // Julio (FIX) BUG 3759 - TesiCapture Melhoria Filtro Worklist
		ConfirmDoingTheExame();
	}
	// Marvel Carvalho | BUG 3759 - TesiCapture Melhoria Filtro Worklist
	// SE detectou um ENTER em um desses campos indica que usuário editou o filtro e está confirmando a pesquisa
	if (
		((GetFocus() == GetDlgItem(IDC_EDIT_CODICERICOVERO))
		|| (GetFocus() == GetDlgItem(IDC_EDIT_NUMORDINE))
		|| (GetFocus() == GetDlgItem(IDC_EDIT_CODPAZIENTE))
		|| (GetFocus() == GetDlgItem(IDC_EDIT_COGNOME))
		|| (GetFocus() == GetDlgItem(IDC_EDIT_NOME))
		|| (GetFocus() == GetDlgItem(IDC_COMBO_DATA))
		|| (GetFocus() == GetDlgItem(IDC_EDIT_DATAINIZ))
		|| (GetFocus() == GetDlgItem(IDC_EDIT_DATAFINE))
		|| (GetFocus() == GetDlgItem(IDC_COMBO_UNIDADE))
		|| (GetFocus() == GetDlgItem(IDC_COMBO_STATO))
		|| (GetFocus() == GetDlgItem(IDC_COMBO_PROVENIENZA))
		|| (GetFocus() == GetDlgItem(IDC_CHK_FILTERDATA))
		|| (GetFocus() == GetDlgItem(IDC_COMBO_REGIONAL))
		|| (GetFocus() == GetDlgItem(IDC_COMBO_SEDE))
		|| (GetFocus() == GetDlgItem(IDC_COMBO_SALA))
		|| (GetFocus() == GetDlgItem(IDC_AGGIORNA))
		|| (GetFocus() == GetDlgItem(IDC_COMBO_MARCA))) && m_bIsExiting == FALSE // Julio (FIX) BUG 3759 - TesiCapture Melhoria Filtro Worklist
		)
	{
		// Marvel Carvalho | BUG 3759 - TesiCapture Melhoria Filtro Worklist
		// atualiza a consulta com os filtros definidos
		// SE aconteceu algum problema na consulta - ignora 
		if (!UpdateFiltering()){
			return;
		}
		
		switch (m_ctrlList.GetItemCount())
		{
			case 0:
			{
				//Impossibile trovare l'ordine
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_NOFINDORDER));
				//GetDlgItem(IDC_EDIT_NUMORDINE)->SetWindowText("");
				//GetDlgItem(IDC_EDIT_CODPAZIENTE)->SetWindowText("");
				//GetDlgItem(IDC_EDIT_COGNOME)->SetWindowText("");
				//GetDlgItem(IDC_EDIT_NOME)->SetWindowText("");
				//RiempiLista("", "", "", "", "");

				break;
			}
			case 1:
			{
				m_ctrlList.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);

				// Sandro 23/02/2017 //
				int nStatoCurSel = m_ctrlComboStato.GetCurSel();
				if (nStatoCurSel >= 0)
				{
					// non posso cominciare esami su pazienti non accettati //		

					long lStatoValue = m_ctrlComboStato.GetItemData(nStatoCurSel);

					if (lStatoValue == 100)
						lStatoValue = GetStatoRichiestaLong(m_ctrlList.GetItemText(0, 0));

					if (lStatoValue == LPC_STATO_ACCETTATA)
					{
						TRACE0("\n\n\n!!!!! StartEsameSelezionato !!!!!\n\n\n");
						POSITION pos = m_ctrlList.GetFirstSelectedItemPosition(); //Julio - BUG 3365 - MAMOGUS
						if (StartEsameSelezionato())
						{		
							//Julio - BUG 3365 - MAMOGUS
							if (pos != NULL)
							{
								CheckComboPrestazioni(pos);
								if (theApp.m_bAtivaListaDO)
									CheckFoglioRiferimento(pos); //Gabriel BUG 6225 - Lista DO
							}
								
							//
							CEndoxResizableDlg::OnOK();
						}
						else
						{
							m_ctrlList.DeleteAllItems();

							CString strEsamiInLista;
							strEsamiInLista.Format(theApp.GetMessageString(IDS_LISTACUP_ESAMIINLISTA), m_ctrlList.GetItemCount());
							GetDlgItem(IDC_ESAMI_IN_LISTA)->SetWindowText(strEsamiInLista);
						}
					}
					//Gabriel BUG 6225 - Lista DO
					else if ((lStatoValue == LPC_STATO_INCORSO) || (lStatoValue == LPC_STATO_EROGATA) || (lStatoValue == LPC_STATO_REFERTATA) || (lStatoValue == LPC_STATO_RICONVOCATO))
					{
						TRACE0("\n\n\n!!!!! GoToEsameSelezionato !!!!!\n\n\n");
						GoToEsameSelezionato();
						CEndoxResizableDlg::OnOK();
					}
				}

				break;
			}
			default:
			{
				// gestione più ordini con lo stesso id, se si verificasse c'è qualche problema
				// ASSERT(FALSE);

				break;
			}
		}

		EnableFields(TRUE);
	}
	else 
	{	
		// CLOSE DIALOG
		CEndoxResizableDlg::OnOK();
		EnableFields(TRUE);

		// Marvel Carvalho | BUG 3759 - TesiCapture Melhoria Filtro Worklist
		// chama salvamento das viriáveis do filtro antes de sair da tela do Worklis
		ThisFilterFieldsSave();
	}
}


// Marvel Carvalho | BUG 3759 - TesiCapture Melhoria Filtro Worklist
// salva as variaveis do filtro para restaurar caso usuário volte para esta mesma tela
void CListaPrenotazioniCupDlg::ThisFilterFieldsSave() {
	theApp.m_default_LISTAPRENOTAZIONICUP_HasFilter = true;

	GetDlgItem(IDC_EDIT_CODICERICOVERO)->GetWindowText(theApp.m_default_LISTAPRENOTAZIONICUP_CODICERICOVERO);
	GetDlgItem(IDC_EDIT_NUMORDINE)->GetWindowText(theApp.m_default_LISTAPRENOTAZIONICUP_NUMORDINE);
	GetDlgItem(IDC_EDIT_CODPAZIENTE)->GetWindowText(theApp.m_default_LISTAPRENOTAZIONICUP_CODPAZIENTE);
	GetDlgItem(IDC_EDIT_COGNOME)->GetWindowText(theApp.m_default_LISTAPRENOTAZIONICUP_COGNOME);
	GetDlgItem(IDC_EDIT_NOME)->GetWindowText(theApp.m_default_LISTAPRENOTAZIONICUP_NOME);
	theApp.m_default_LISTAPRENOTAZIONICUP_COMBODATA = m_ctrlComboData.GetCurSel();
	GetDlgItem(IDC_EDIT_DATAINIZ)->GetWindowText(theApp.m_default_LISTAPRENOTAZIONICUP_DATAINIZ);
	GetDlgItem(IDC_EDIT_DATAFINE)->GetWindowText(theApp.m_default_LISTAPRENOTAZIONICUP_DATAFINE);
	theApp.m_default_LISTAPRENOTAZIONICUP_COMBOUNIDADE = m_ctrlComboUnidade.GetCurSel();
	theApp.m_default_LISTAPRENOTAZIONICUP_COMBOSTATO = m_ctrlComboStato.GetCurSel();
	theApp.m_default_LISTAPRENOTAZIONICUP_COMBOPROVENIENZA = m_ctrlComboProvenienza.GetCurSel();
	theApp.m_default_LISTAPRENOTAZIONICUP_CHKFILTERDATA = m_ctrlChkFilterData.GetCheck();
	theApp.m_default_LISTAPRENOTAZIONICUP_COMBOREGIONAL = m_ctrlComboRegional.GetCurSel();
	theApp.m_default_LISTAPRENOTAZIONICUP_COMBOSEDE = m_ctrlComboSede.GetCurSel();
	theApp.m_default_LISTAPRENOTAZIONICUP_COMBOSALA = m_ctrlComboSala.GetCurSel();
	theApp.m_default_LISTAPRENOTAZIONICUP_COMBOMARCA = m_ctrlComboMarca.GetCurSel();
}

// Marvel Carvalho | BUG 3759 - TesiCapture Melhoria Filtro Worklist
// restaura as variaveis do filtro para quando usuário reabre esta tela
void CListaPrenotazioniCupDlg::ThisFilterFieldsRestore(){
	if (!theApp.m_default_LISTAPRENOTAZIONICUP_HasFilter) {
		return;
	}

	GetDlgItem(IDC_EDIT_CODICERICOVERO)->SetWindowText(theApp.m_default_LISTAPRENOTAZIONICUP_CODICERICOVERO);
	GetDlgItem(IDC_EDIT_NUMORDINE)->SetWindowText(theApp.m_default_LISTAPRENOTAZIONICUP_NUMORDINE);
	GetDlgItem(IDC_EDIT_CODPAZIENTE)->SetWindowText(theApp.m_default_LISTAPRENOTAZIONICUP_CODPAZIENTE);
	GetDlgItem(IDC_EDIT_COGNOME)->SetWindowText(theApp.m_default_LISTAPRENOTAZIONICUP_COGNOME);
	GetDlgItem(IDC_EDIT_NOME)->SetWindowText(theApp.m_default_LISTAPRENOTAZIONICUP_NOME);
	m_ctrlComboData.SetCurSel(theApp.m_default_LISTAPRENOTAZIONICUP_COMBODATA);
	GetDlgItem(IDC_EDIT_DATAINIZ)->SetWindowText(theApp.m_default_LISTAPRENOTAZIONICUP_DATAINIZ);
	GetDlgItem(IDC_EDIT_DATAFINE)->SetWindowText(theApp.m_default_LISTAPRENOTAZIONICUP_DATAFINE);
	m_ctrlComboUnidade.SetCurSel(theApp.m_default_LISTAPRENOTAZIONICUP_COMBOUNIDADE);
	m_ctrlComboStato.SetCurSel(theApp.m_default_LISTAPRENOTAZIONICUP_COMBOSTATO);
	m_ctrlComboProvenienza.SetCurSel(theApp.m_default_LISTAPRENOTAZIONICUP_COMBOPROVENIENZA);
	m_ctrlChkFilterData.SetCheck(theApp.m_default_LISTAPRENOTAZIONICUP_CHKFILTERDATA);
	m_ctrlComboRegional.SetCurSel(theApp.m_default_LISTAPRENOTAZIONICUP_COMBOREGIONAL);
	m_ctrlComboSede.SetCurSel(theApp.m_default_LISTAPRENOTAZIONICUP_COMBOSEDE);
	m_ctrlComboSala.SetCurSel(theApp.m_default_LISTAPRENOTAZIONICUP_COMBOSALA);
	m_ctrlComboMarca.SetCurSel(theApp.m_default_LISTAPRENOTAZIONICUP_COMBOMARCA);
}


void CListaPrenotazioniCupDlg::OnCancel() 
{
	// Marvel Carvalho | BUG 3759 - TesiCapture Melhoria Filtro Worklist
	// chama o salvamento das viriáveis do filtro antes de sair da tela da Worklist
	ThisFilterFieldsSave();

	if (m_pWorkListManager->m_bTipoEsameDlg)
		return;
	
	CEndoxResizableDlg::OnCancel();	
	EnableFields(TRUE);	
}


void CListaPrenotazioniCupDlg::ConfirmDoingTheExame() {
	// Sandro 30/10/2013 //
	int nStatoCurSel = m_ctrlComboStato.GetCurSel();
	if (nStatoCurSel >= 0)
	{
		// non posso cominciare esami su pazienti non accettati //		

		long lStatoValue = m_ctrlComboStato.GetItemData(nStatoCurSel);

		if (lStatoValue == 100)
		{
			POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
			if (pos != NULL)
			{
				int nItem = m_ctrlList.GetNextSelectedItem(pos);
				if (nItem >= 0)
				{
					CString sStato = m_ctrlList.GetItemText(nItem, 0);
					lStatoValue = GetStatoRichiestaLong(sStato);
				}
			}
		}

		if (lStatoValue == LPC_STATO_ACCETTATA)
		{
			//Julio - BUG 3365 - MAMOGUS
			POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
			StartEsameSelezionato();
			if(pos != NULL)
			{
				CheckComboPrestazioni(pos);
				if (theApp.m_bAtivaListaDO)
					CheckFoglioRiferimento(pos);//Gabriel BUG 6225 - Lista DO
			}
			//
			
		}
		//Gabriel BUG 6225 - Lista DO
		else if ((lStatoValue == LPC_STATO_INCORSO) || (lStatoValue == LPC_STATO_EROGATA) || (lStatoValue == LPC_STATO_REFERTATA) || (lStatoValue == LPC_STATO_RICONVOCATO))
		{
			GoToEsameSelezionato();
		}
	}
}

//Julio - BUG 3365 - MAMOGUS
void CListaPrenotazioniCupDlg::CheckComboPrestazioni(POSITION pos)
{	
	if (!theApp.m_bUsaComboPrestazioni)
		return;

	if (pos)
	{
		int nItemSelected = m_ctrlList.GetNextSelectedItem(pos);
		int lIDOrdineSelected = m_ctrlList.GetItemData(nItemSelected);

		//Seleciona as informacoes do exame que acabou de ser inserido
		CString sCodicePrestazioneSelected = CVistaComboPrestazioni().GetCodicePrestazione(lIDOrdineSelected);
		CString sNosologicoSelected = CVistaComboPrestazioni().GetNosologico(lIDOrdineSelected);
		long lIDEsameInsSelected = CVistaComboPrestazioni().GetIDEsameIns(lIDOrdineSelected);
		//

		//verifica se o exame inserido tem um combo em sua sigla 
		CList<CString> listCombo;
		CComboPrestazioni().GetComboList(sCodicePrestazioneSelected, &listCombo);
		//

		//Em caso positivo
		if (listCombo.GetCount() > 0)
		{
			for (POSITION pos = listCombo.GetHeadPosition(); pos;)
			{
				//loop pelas siglas que fazem combo com a sigla do exame inserido
				CString sPrestazioneCombo = listCombo.GetNext(pos);
				
				//Verifica se existe algum outro exame na ext_ordini com o mesmo nosologico e com uma das outras siglas do combo
				if (CVistaComboPrestazioni().ExamHasCombo(sNosologicoSelected, sPrestazioneCombo))
				{
					//Insere a informacao na Ext_ComboPrestazioni para ser processada depois pelo EndoxServer
					CExtComboPrestazioni().Insert(lIDEsameInsSelected, CExtComboPrestazioni::Tipo::StatusChange);
					break;
				}
			}
		}
	}	
}

//Gabriel BUG 6225 - Lista DO
void CListaPrenotazioniCupDlg::CheckFoglioRiferimento(POSITION pos)
{
	if (pos)
	{
		int nItemSelected = m_ctrlList.GetNextSelectedItem(pos);
		int lIDOrdineSelected = m_ctrlList.GetItemData(nItemSelected);

		//Seleciona a sigla do exame que acabou de ser inserido
		CString sCodicePrestazioneSelected = CVistaComboPrestazioni().GetCodicePrestazione(lIDOrdineSelected);
		//

		//verifica se o exame inserido tem um documento de referência configurado
		CList<CString> listDocumento;
		CFoglioRiferimentoSet().GetListaPercorso(sCodicePrestazioneSelected, theApp.m_lUO, &listDocumento);
		//

		//Em caso positivo
		if (listDocumento.GetCount() > 0)
		{
			for (POSITION pos = listDocumento.GetHeadPosition(); pos;)
			{
				CString sDocumentoPath = listDocumento.GetNext(pos);
				m_pEsamiView->m_pDocManager->ImportDoc(m_pEsamiView->m_pPazientiSet->m_lContatore, m_pEsamiView->m_pEsamiSet->m_lContatore, "Teste", theApp.GetServerDate().Mid(0, 8), sDocumentoPath, 1);
			}
			m_pEsamiView->RefreshNumDocumentsExam();
		}
	}
}

void CListaPrenotazioniCupDlg::OnDblClkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	ConfirmDoingTheExame();

	if (pResult != NULL)
		*pResult = 0;
}

// Marvel Carvalho | BUG 3759 - TesiCapture Melhoria Filtro Worklist
BOOL CListaPrenotazioniCupDlg::RiempiLista(CString sCodiceRicovero, CString sNumeroOrdine, CString sCodicePaziente, CString sCognome, CString sNome)
{
	CString sFilter = "";
	CString strFiltroData = "";

	if (m_lIDExtOrdiniAutoImport > 0)
	{
		sFilter.Format(" AND EndoxOrderID=%li", m_lIDExtOrdiniAutoImport);
	}
	else
	{
		if(m_ctrlChkFilterData.GetCheck() == BST_UNCHECKED)
			GetNormalDateFilter(&strFiltroData, "ExamDate", this, &m_ctrlComboData, IDC_EDIT_DATAINIZ, IDC_EDIT_DATAFINE);

		//

		if (!sCodiceRicovero.IsEmpty())
		{
			sCodiceRicovero.Replace("'", "''");
			sCodiceRicovero.MakeUpper();
			sFilter.AppendFormat(" AND UPPER(visitNumber) LIKE '%s'", sCodiceRicovero);
		}

		if (!sNumeroOrdine.IsEmpty())
		{
			if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury)
			{
				BOOL bAlgoritmoSpeciale = TRUE;

				if ((sNumeroOrdine.GetLength() == 16) || (sNumeroOrdine.GetLength() == 17))
				{
					for (int i = 0; i < sNumeroOrdine.GetLength(); i++)
						if (!std::isdigit(sNumeroOrdine[i]))
							bAlgoritmoSpeciale = FALSE;
				}
				else
				{
					bAlgoritmoSpeciale = FALSE;
				}

				if (bAlgoritmoSpeciale)
				{
					CString sOnlyFicha = sNumeroOrdine.Left(10);
					CString sOnlyItem = "";

					switch (sNumeroOrdine.GetLength())
					{
						case 16:
						{
							sOnlyItem = sNumeroOrdine.Mid(13, 1);
							break;
						}
						case 17:
						{
							sOnlyItem = sNumeroOrdine.Mid(13, 2);
							break;
						}
					}

					sFilter.AppendFormat(" AND UPPER(groupNumber) LIKE '%s_%s_%%'", sOnlyFicha, sOnlyItem);
				}
				else
				{
					sNumeroOrdine.Replace("'", "''");
					sNumeroOrdine.MakeUpper();

					sFilter.AppendFormat(" AND UPPER(groupNumber) LIKE '%s%%'", sNumeroOrdine);
				}
			}
			else
			{
				sNumeroOrdine.Replace("'", "''");
				sNumeroOrdine.MakeUpper();
				sFilter.AppendFormat(" AND UPPER(groupNumber) LIKE '%s'", sNumeroOrdine);
			}
		}

		if (!sCodicePaziente.IsEmpty())
		{
			sCodicePaziente.Replace("'", "''");
			sCodicePaziente.MakeUpper();
			sFilter.AppendFormat(" AND UPPER(patientId) LIKE '%s'", sCodicePaziente);
		}

		if (!sCognome.IsEmpty())
		{
			sCognome.Replace("'", "''");
			sCognome.MakeUpper();
			sFilter.AppendFormat(" AND UPPER(patientSurname) LIKE '%s%%'", sCognome);
		}

		if (!sNome.IsEmpty())
		{
			sNome.Replace("'", "''");
			sNome.MakeUpper();
			sFilter.AppendFormat(" AND UPPER(patientName) LIKE '%s%%'", sNome);
		}

		// Sandro 30/10/2013 //

		long lStatoAccettazione = LPC_STATO_ACCETTATA;
		long lProvenienza = -1;

		int nStatoCurSel = m_ctrlComboStato.GetCurSel();
		if (nStatoCurSel >= 0)
			lStatoAccettazione = m_ctrlComboStato.GetItemData(nStatoCurSel);

		//Gabriel BUG 6225 - Lista DO
		if (!(lStatoAccettazione == 100 && CUOSet().GetFastFichaWorklist(theApp.m_lUO)))
		{
			if (lStatoAccettazione == LPC_STATO_RICONVOCATO)
				sFilter.AppendFormat(" AND IDESAMEINS IN (SELECT IDESAME FROM Riconvocazione WHERE ELIMINATO = 0)", lStatoAccettazione);
			else
				sFilter.AppendFormat(" AND orderPhase=%li", lStatoAccettazione);
		}

		int nProvCurSel = m_ctrlComboProvenienza.GetCurSel();
		if (nProvCurSel >= 0)
		{
			int id = m_ctrlComboProvenienza.GetItemData(nProvCurSel);
			if (id >= 0)
				sFilter.AppendFormat(" AND idProvenienzaEndox=%li", id);
		}

		// Sandro 21/02/2017 //

		if (strFiltroData.IsEmpty() && sFilter.IsEmpty())
		{
			theApp.AfxMessageBoxEndo(IDS_UTILIZZARE_FILTRI);
			// Marvel Carvalho | BUG 3759 - TesiCapture Melhoria Filtro Worklist
			return false;
		}

		// Filtro la sede

		long lIdSedeEsame = 0;

		int nSedeCurSel = m_ctrlComboSede.GetCurSel();
		if (nSedeCurSel >= 0)
			lIdSedeEsame = m_ctrlComboSede.GetItemData(nSedeCurSel);

		sFilter.AppendFormat(" AND AGENDE.IDSALA IN (SELECT ID FROM SALEESAME WHERE IDSEDE=%li)", lIdSedeEsame);

		// Filtro la sala

		long lIdSalaEsame = 0;

		int nSalaCurSel = m_ctrlComboSala.GetCurSel();
		if (nSalaCurSel >= 0)
		{
			lIdSalaEsame = m_ctrlComboSala.GetItemData(nSalaCurSel);
			if (lIdSalaEsame > -1)
				sFilter.AppendFormat(" AND AGENDE.IDSALA=%li", lIdSalaEsame);
		}

		// Sandro 27/07/2016 //

		if (theApp.m_bCentraleControlloQualita)
		{
			int nCurSelUnidade = m_ctrlComboUnidade.GetCurSel();
			if (nCurSelUnidade > 0)
			{
				CString sUnidade;
				m_ctrlComboUnidade.GetLBText(nCurSelUnidade, sUnidade);
				sUnidade.Replace("'", "''");
				sUnidade.Trim();
				if (!sUnidade.IsEmpty())
					sFilter += " AND TEXT097 LIKE '" + sUnidade + "'";
			}

			int nCurSelRegional = m_ctrlComboRegional.GetCurSel();
			if (nCurSelRegional > 0)
			{
				CString sRegional;
				m_ctrlComboRegional.GetLBText(nCurSelRegional, sRegional);
				sRegional.Replace("'", "''");
				sRegional.Trim();
				if (!sRegional.IsEmpty())
					sFilter += " AND TEXT098 LIKE '" + sRegional + "'";
			}

			int nCurSelMarca = m_ctrlComboMarca.GetCurSel();
			if (nCurSelMarca > 0)
			{
				CString sMarca;
				m_ctrlComboMarca.GetLBText(nCurSelMarca, sMarca);
				sMarca.Replace("'", "''");
				sMarca.Trim();
				if (!sMarca.IsEmpty())
					sFilter += " AND TEXT099 LIKE '" + sMarca + "'";
			}
		}
	}

	if (!m_pWorkListManager->FillList(&m_ctrlList, sFilter, strFiltroData))
	{
		// Marvel Carvalho | BUG 3759 - TesiCapture Melhoria Filtro Worklist
		// abandona a sequencia caso houve timeout por exemplo
		return false;

		//removidas linhas abaixo pq quando dá timeout o sistema estava fechando a tela de worklist sem salvar o filtro
		//ShowWindow(SW_HIDE);
		//PostMessage(WM_COMMAND, IDOK);
	}

	if (CUOSet().GetFastFichaWorklist(theApp.m_lUO))
		m_ctrlList.SetColumnWidth(0, 120);

	CTime timeCurrent = CTime::GetCurrentTime();

	CString strEsamiInLista;
	strEsamiInLista.Format(theApp.GetMessageString(IDS_LISTACUP_ESAMIINLISTA), m_ctrlList.GetItemCount());
	GetDlgItem(IDC_ESAMI_IN_LISTA)->SetWindowText(strEsamiInLista);

	CString strUltimoAggiornamento;
	strUltimoAggiornamento.Format(theApp.GetMessageString(IDS_LISTACUP_AGGTABELLA), timeCurrent.Format("%H:%M"), timeCurrent.Format("%d/%m/%Y"));
	GetDlgItem(IDC_ULTIMO_AGGIORNAMENTO)->SetWindowText(strUltimoAggiornamento);

	PostMessage(WM_CURCHANGE);

	// Marvel Carvalho | BUG 3759 - TesiCapture Melhoria Filtro Worklist
	return true;
}

void CListaPrenotazioniCupDlg::OnAggiorna() 
{
	if (!m_bInitializing || (m_ctrlChkFilterData.GetCheck() == BST_UNCHECKED))
	{
		if (!UpdateFiltering()){
			return;
		}
	}
}

void CListaPrenotazioniCupDlg::OnNMRClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	int idOrder = -1;
	if (POSITION pos = m_ctrlList.GetFirstSelectedItemPosition())
	{
		int item = m_ctrlList.GetNextSelectedItem(pos);
		idOrder = m_ctrlList.GetItemData(item);
		if (idOrder < 0)
			idOrder = idOrder * -1;
	}

	int iMenuToOpen = m_ctrlComboStato.GetItemData(m_ctrlComboStato.GetCurSel());
	if (iMenuToOpen == 100)
	{
		POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
		if (pos != NULL)
		{
			int nItem = m_ctrlList.GetNextSelectedItem(pos);
			if (nItem >= 0)
			{
				CString sStato = m_ctrlList.GetItemText(nItem, 0);
				iMenuToOpen = GetStatoRichiestaLong(sStato);
			}
		}
	}
	switch (iMenuToOpen)
	{
		case LPC_STATO_PRENOTATA:
		case LPC_STATO_NONEROGATA:
		{
			if (idOrder > 0)
			{
				CPoint point;
				GetCursorPos(&point);

				CEndoxMenu menu;
				menu.LoadMenu(IDR_MENU_WL_PRENOTATI);

				CEndoxMenu* pMenu = (CEndoxMenu*)menu.GetSubMenu(0);				
				pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);				
			}

			break;
		}
		case LPC_STATO_ACCETTATA:
		{
			if (idOrder > 0)
			{
				CPoint point;
				GetCursorPos(&point);

				CEndoxMenu menu;
				menu.LoadMenu(IDR_MENU_WL_ACCETTATI);

				CEndoxMenu* pMenu = (CEndoxMenu*)menu.GetSubMenu(0);
				pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
			}

			break;
		}
		case LPC_STATO_INCORSO:
		{
			if (idOrder > 0)
			{
				CPoint point;
				GetCursorPos(&point);

				CEndoxMenu menu;
				menu.LoadMenu(IDR_MENU_WL_INPROGRESS);

				CEndoxMenu* pMenu = (CEndoxMenu*)menu.GetSubMenu(0);
				if (IsEsameAnnullabile())
					pMenu->DeleteMenu(ID_IP_ANNULLA, MF_BYCOMMAND);
				pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
			}

			break;
		}
		//Gabriel BUG 6225 - Lista DO
		case LPC_STATO_RICONVOCATO:
		case LPC_STATO_EROGATA:
		case LPC_STATO_REFERTATA:
		{
			if (idOrder > 0)
			{
				CPoint point;
				GetCursorPos(&point);

				CEndoxMenu menu;
				menu.LoadMenu(IDR_MENU_WL_EROGATI);

				CEndoxMenu* pMenu = (CEndoxMenu*)menu.GetSubMenu(0);
				pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
			}

			break;
		}
		case LPC_STATO_NONPRESENTATA:
		{
			if (idOrder > 0)
			{
				CPoint point;
				GetCursorPos(&point);

				CEndoxMenu menu;
				menu.LoadMenu(IDR_MENU_WL_NONPRESENTATI);

				CEndoxMenu* pMenu = (CEndoxMenu*)menu.GetSubMenu(0);
				pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
			}

			break;
		}
		default:
			break;
	}
}

void CListaPrenotazioniCupDlg::VediDettagliRichiestaSelezionata()
{
	if (POSITION pos = m_ctrlList.GetFirstSelectedItemPosition())
	{
		int item = m_ctrlList.GetNextSelectedItem(pos);
		int idOrder = m_ctrlList.GetItemData(item);
		if (idOrder < 0)
			idOrder = idOrder * -1;

		CListaPrenotazioniCupDettaglioDlg dettaglioDlg(this, m_pEsamiView, idOrder);
		dettaglioDlg.DoModal();
	}	
}

BOOL CListaPrenotazioniCupDlg::StartEsameSelezionato()
{
	BOOL bReturn = FALSE;

	// non posso cominciare esami prenotati in altre sedi //

	int nSedeCurSel = m_ctrlComboSede.GetCurSel();
	if (nSedeCurSel >= 0)
	{
		long lSedeValue = m_ctrlComboSede.GetItemData(nSedeCurSel);
		if (lSedeValue == theApp.m_lIDSedeEsameDefault)
		{
			if (POSITION pos = m_ctrlList.GetFirstSelectedItemPosition())
			{
				EnableFields(FALSE);
				if (m_pWorkListManager->SelectEntry(&m_ctrlList, m_ctrlList.GetNextSelectedItem(pos)))
				{
					bReturn = TRUE;
					m_bIsExiting = TRUE; // Julio (FIX) BUG 3759 - TesiCapture Melhoria Filtro Worklist
					PostMessage(WM_COMMAND, IDOK);
				}
				else
				{
					EnableFields(TRUE);
					OnAggiorna();
				}
			}
		}
	}

	return bReturn;
}

void CListaPrenotazioniCupDlg::AnnullaIPSelezionato()
{
	// non posso cominciare esami prenotati in altre sedi //

	int nSedeCurSel = m_ctrlComboSede.GetCurSel();
	if (nSedeCurSel >= 0)
	{
		long lSedeValue = m_ctrlComboSede.GetItemData(nSedeCurSel);
		if (lSedeValue == theApp.m_lIDSedeEsameDefault)
		{
			if (POSITION pos = m_ctrlList.GetFirstSelectedItemPosition())
			{
				if (theApp.AfxMessageBoxEndo("L'azione annullerà la presa in carico della richiesta, riportandola in stato \"ACCETTATA\", proseguire?", MB_YESNO) == IDYES)
				{
					EnableFields(FALSE);
					if (m_pWorkListManager->AbortIP(&m_ctrlList, m_ctrlList.GetNextSelectedItem(pos)))
					{
						m_bIsExiting = TRUE; // Julio (FIX) BUG 3759 - TesiCapture Melhoria Filtro Worklist
						PostMessage(WM_COMMAND, IDOK);
					}
					else
					{
						EnableFields(TRUE);
						OnAggiorna();
					}
				}
			}
		}
	}
}

void CListaPrenotazioniCupDlg::GoToEsameSelezionato()
{
	if (POSITION pos = m_ctrlList.GetFirstSelectedItemPosition())
	{
		long idEsame = m_ctrlList.GetItemData(m_ctrlList.GetNextSelectedItem(pos));
		if (idEsame < 0)
			idEsame = idEsame * -1;
		CCupWorkListManager tempSet(m_pEsamiView);
		CString filter;
		filter.Format("ID=%li", idEsame);
		tempSet.SetOpenFilter(filter);
		if (tempSet.OpenRecordset("CListaPrenotazioniCupDlg::GoToEsameSelezionato"))
		{
			if (!tempSet.IsEOF())
			{
				CEsamiSet tempExSet;
				filter.Format("CONTATORE=%li", tempSet.m_lIDEsameIns);
				tempExSet.SetOpenFilter(filter);
				if (tempExSet.OpenRecordset("CListaPrenotazioniCupDlg::GoToEsameSelezionato"))
				{
					if (!tempExSet.IsEOF())
					{
						EnableFields(FALSE);

						if (!m_pEsamiView->m_pPazientiSet->IsOpen())
							m_pEsamiView->m_pPazientiSet->OpenRecordset("CListaPrenotazioniCupDlg::GoToEsameSelezionato");

						m_pEsamiView->RicercaCodicePaziente(tempExSet.m_lPaziente, tempExSet.m_lContatore, FALSE, TRUE);
						m_pEsamiView->MovePazientiAndEsami(NULL, FALSE, TRUE);

						// if (theApp.m_bCentraleRefertazione) // Sandro 09/05/2017 // BUG 390 //
						{
							// Sandro 24/10/2016 // RIMA 16037 RN43 //
							if ((m_pEsamiView->m_pEsamiSet->m_sCodEsame.CompareNoCase(m_pEsamiView->m_pEsamiSet->m_sRefertoConiugatoPrincipale) == 0) && !m_pEsamiView->m_pEsamiSet->m_bRefertoConiugatoImportato)
							{
								// importo immagini, testo del referto, nome e codice fiscale del medico che ha convalidato l'esame coniugato //

								BeginWaitCursor();

								CString sFilterTemp;
								sFilterTemp.Format("CODESAME LIKE '%s'", m_pEsamiView->m_pEsamiSet->m_sRefertoConiugatoSecondario);

								CEsamiSet setEsamiTemp;
								setEsamiTemp.SetBaseFilter("(UO=0 OR UO>0)");
								setEsamiTemp.SetOpenFilter(sFilterTemp);

								if (setEsamiTemp.OpenRecordset("CListaPrenotazioniCupDlg::GoToEsameSelezionato"))
								{
									if (!setEsamiTemp.IsEOF())
									{
										// IMMAGINI //

										CImgManager tempImgManager(theApp.m_sPathImageOD, &theApp.m_dbEndox);
										tempImgManager.SetThumbStoreSize(CSize(HSIZE_PAL / 4, VSIZE_PAL / 4));
										tempImgManager.SetThumbRetrieveSize(CSize(HSIZE_PAL / 4, VSIZE_PAL / 4));
										tempImgManager.SetImageExt(CString(EXT_IMG).Right(3));
										tempImgManager.SetThumbExt(CString(EXT_WIN).Right(3));
										tempImgManager.SetMovieBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_FILM)), RGB(255, 255, 255));
										tempImgManager.SetTiffBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_TIFF)), RGB(255, 255, 255));
										tempImgManager.SetPrintBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_PRINT)), RGB(255, 0, 0), bottomright);
										tempImgManager.SetSelectBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_SELEZIONE)), RGB(0, 255, 0), topleft);
										tempImgManager.SetDicomBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DICOM_IMM)), RGB(255, 255, 255));
										tempImgManager.SetDicomMovieBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DICOM_FILM)), RGB(255, 255, 255));
										tempImgManager.SetCIBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_ICON_CI)), RGB(255, 255, 255));
										tempImgManager.SetImageQuality(theApp.m_nArchivioImmaginiQualita, theApp.m_nArchivioMiniatureQualita, 100);

										tempImgManager.SetCurrentIDs(setEsamiTemp.m_lPaziente, setEsamiTemp.m_lContatore);

										CImgIDList imgIDList;
										tempImgManager.GetImgIDList(&imgIDList);

										CStringList listPath;
										POSITION pos = imgIDList.GetHeadPosition();
										while (pos != NULL)
										{
											long lIDImmagineTemp = imgIDList.GetAt(pos);

											CString sFileTemp = tempImgManager.GetFullPath(lIDImmagineTemp);
											listPath.AddTail(sFileTemp);

											imgIDList.GetNext(pos);
										}

										CImgIDList outputImgIdList;
										m_pEsamiView->m_pImgManager->ImportImgList(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, 0, &listPath, FORM_IMM, FORM_MINI, &outputImgIdList, FALSE, FALSE, FALSE);

										// testo del referto //

										if (m_pEsamiView->m_pEsamiSet->EditRecordset("CListaPrenotazioniCupDlg::GoToEsameSelezionato"))
										{
											m_ctrlTextControlHide.ResetContents();

											setEsamiTemp.m_sRefertoTestoTxt.Trim();
											if (!setEsamiTemp.m_sRefertoTestoTxt.IsEmpty())
											{
												m_ctrlTextControlHide.SetRTFSelText(setEsamiTemp.m_sRefertoTestoRtf);

												m_ctrlTextControlHide.SetSelStart(m_ctrlTextControlHide.GetText().GetLength() + 1);
												m_ctrlTextControlHide.SetSelLength(-1);

												m_ctrlTextControlHide.SetSelText("\r\n\r\n");

												m_pEsamiView->m_pEsamiSet->m_sRefertoTestoTxt.Trim();
												if (!m_pEsamiView->m_pEsamiSet->m_sRefertoTestoTxt.IsEmpty())
												{
													m_ctrlTextControlHide.SetSelStart(m_ctrlTextControlHide.GetText().GetLength() + 1);
													m_ctrlTextControlHide.SetSelLength(-1);

													m_ctrlTextControlHide.SetRTFSelText(m_pEsamiView->m_pEsamiSet->m_sRefertoTestoRtf);
												}
											}

											m_ctrlTextControlHide.SetSelStart(0);
											m_ctrlTextControlHide.SetSelLength(-1);

											//m_pEsamiView->m_pEsamiSet->m_sRefertoTestoRtf = m_ctrlTextControlHide.GetRTFSelText();
											//m_pEsamiView->m_pEsamiSet->m_sRefertoTestoTxt = m_ctrlTextControlHide.GetSelText();

											m_pEsamiView->m_pEsamiSet->m_bRefertoConiugatoImportato = TRUE;

											m_pEsamiView->m_pEsamiSet->m_setEP.m_sTesto096 = theApp.GetMessageString(IDS_US_REFERTATO_DA) + " " + CMediciSet().GetFieldFirmaFromUserID(setEsamiTemp.m_lIdUtenteLock, 0);

											m_pEsamiView->m_pEsamiSet->UpdateRecordset("CListaPrenotazioniCupDlg::GoToEsameSelezionato");
										}
									}

									setEsamiTemp.CloseRecordset("CListaPrenotazioniCupDlg::GoToEsameSelezionato");
								}

								m_pEsamiView->RicercaCodicePaziente(m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore, FALSE, TRUE);
								m_pEsamiView->MovePazientiAndEsami(NULL, FALSE, TRUE);

								EndWaitCursor();
							}
						}

						m_bIsExiting = TRUE; // Julio (FIX) BUG 3759 - TesiCapture Melhoria Filtro Worklist
						PostMessage(WM_COMMAND, IDOK);
					}

					tempExSet.CloseRecordset("CListaPrenotazioniCupDlg::GoToEsameSelezionato");
				}
			}

			tempSet.CloseRecordset("CListaPrenotazioniCupDlg::GoToEsameSelezionato");
		}
	}
}

void CListaPrenotazioniCupDlg::OnCbnSelchangeComboStato()
{
	OnAggiorna();
}

void CListaPrenotazioniCupDlg::OnCbnSelchangeComboSede()
{
	RiempiComboSale();
	OnAggiorna();
}

void CListaPrenotazioniCupDlg::OnCbnSelchangeComboSala()
{
	OnAggiorna();
}

void CListaPrenotazioniCupDlg::OnCbnSelchangeComboProvenienza()
{
	OnAggiorna();
}

void CListaPrenotazioniCupDlg::OnCbnSelchangeComboData()
{
	ComboDataPeriodUpdated(&m_ctrlComboData, this, IDC_EDIT_DATAINIZ, IDC_EDIT_DATAFINE);
	OnAggiorna();
}

void CListaPrenotazioniCupDlg::OnCbnSelchangeComboUnidade()
{
	OnAggiorna();
}

void CListaPrenotazioniCupDlg::OnCbnSelchangeComboRegional()
{
	OnAggiorna();
}

void CListaPrenotazioniCupDlg::OnCbnSelchangeComboMarca()
{
	OnAggiorna();
}

LRESULT CListaPrenotazioniCupDlg::OnGestioneCursore(WPARAM wparam, LPARAM lparam)
{
	// Sandro 10/06/2015 // RIMA 15040 //

	if (theApp.m_bPersonalizzazioniBrasileSirio && !theApp.m_bPersonalizzazioniBrasileEinstein) // Sandro 30/06/2016 // aggiunto il discorso dell'Einstein //
	{
		GetDlgItem(IDC_EDIT_CODICERICOVERO)->SetFocus();
		return 0;
	}

	// Bug 4156 - worklist (campo: numero ordine) pesquisa por barcode reader
	CEdit * pAuxEdit;

	switch(theApp.m_lPrenotazioniCupFocus)
	{
		case 0:
		{
			pAuxEdit = (CEdit*)GetDlgItem(IDC_EDIT_NUMORDINE);
			break;
		}
		case 1:
		{
			pAuxEdit = (CEdit*)GetDlgItem(IDC_EDIT_CODPAZIENTE);
			break;
		}
		case 2:
		{
			pAuxEdit = (CEdit*)GetDlgItem(IDC_EDIT_COGNOME);
			break;
		}
		case 3:
		{
			pAuxEdit = (CEdit*)GetDlgItem(IDC_EDIT_NOME);
			break;
		}
		default:
		{
			pAuxEdit = (CEdit*)GetDlgItem(IDC_EDIT_CODPAZIENTE);
			break;
		}
	}

	// Bug 4156 - worklist (campo: numero ordine) pesquisa por barcode reader
	if (pAuxEdit != NULL){
		pAuxEdit->SetFocus();    // Set  focus to the component
		pAuxEdit->SetSel(0, -1); // Select all text of the component
		pAuxEdit->UpdateWindow();// force it update
	}

	return 0;
}

void CListaPrenotazioniCupDlg::RiempiComboSedi()
{
	int nCurSelSede = -1;

	m_ctrlComboSede.ResetContent();

	CSediEsameSet setSedi;
	setSedi.SetSortRecord("Descrizione");
	if (setSedi.OpenRecordset("CListaPrenotazioniCupDlg::RiempiComboSedi"))
	{
		int nIndex = 0;

		while (!setSedi.IsEOF())
		{
			m_ctrlComboSede.InsertString(nIndex, setSedi.m_sDescrizione);
			m_ctrlComboSede.SetItemData(nIndex, setSedi.m_lID);

			if (setSedi.m_lID == theApp.m_lIDSedeEsameDefault)
				nCurSelSede = nIndex;

			nIndex++;
			setSedi.MoveNext();
		}

		setSedi.CloseRecordset("CListaPrenotazioniCupDlg::RiempiComboSedi");
	}

	if (nCurSelSede >= 0)
		m_ctrlComboSede.SetCurSel(nCurSelSede);

	RiempiComboSale();
}

void CListaPrenotazioniCupDlg::RiempiComboSale()
{
	m_ctrlComboSala.ResetContent();

	// riempio la lista delle sale usando come filtro la sede //
	m_ctrlComboSala.InsertString(0, theApp.GetMessageString(IDS_TUTTE));
	m_ctrlComboSala.SetItemData(0, -1);

	CString sFilter;
	sFilter.Format("IDSede=%li", m_ctrlComboSede.GetItemData(m_ctrlComboSede.GetCurSel()));

	BOOL salaFound = FALSE;

	CSaleEsameSet setSale;
	setSale.SetOpenFilter(sFilter);
	if (setSale.OpenRecordset("CListaPrenotazioniCupDlg::RiempiComboSale"))
	{
		while (!setSale.IsEOF())
		{
			int nIndex = m_ctrlComboSala.InsertString(m_ctrlComboSala.GetCount(), setSale.m_sDescrizione);
			m_ctrlComboSala.SetItemData(nIndex, setSale.m_lID);

			if (setSale.m_sDescrizione == theApp.m_sSalaEsameDefault)
			{
				m_ctrlComboSala.SetCurSel(nIndex);
				salaFound = TRUE;
			}

			setSale.MoveNext();
		}

		setSale.CloseRecordset("CListaPrenotazioniCupDlg::RiempiComboSale");
	}

	if (!salaFound)
		m_ctrlComboSala.SetCurSel(0);
}

void CListaPrenotazioniCupDlg::OnBnClickedCambiaUO()
{
	if (m_lNumeroUOUtente < 2)
		return;

	if (m_lNumeroUOUtente == 2)
	{
		long lUserID;
		AMLogin_GetUserID(&lUserID);

		CString sFilter;
		sFilter.Format("IDUO<>%li AND IDUtente=%li", theApp.m_lUO, lUserID);

		CUOUtenteSet setTemp;
		setTemp.SetOpenFilter(sFilter);
		setTemp.SetSortRecord("IDUO");
		if (setTemp.OpenRecordset("CListaPrenotazioniCupDlg::OnBnClickedCambiaUO"))
		{
			if (!setTemp.IsEOF())
			{
				CString sMessage;
				sMessage.Format(theApp.GetMessageString(IDS_CAMBIARE_UO_1), CUOSet().GetDescrizione(setTemp.m_lIDUO));

				if (theApp.AfxMessageBoxEndo(sMessage, MB_YESNO | MB_ICONQUESTION) == IDYES)
				{
					theApp.m_lUO = setTemp.m_lIDUO;

					SetDlgItemText(IDC_STATIC_UO, theApp.GetMessageString(IDS_UO) + ": " + CUOSet().GetDescrizione(theApp.m_lUO));

					BeginWaitCursor();
					m_pEsamiView->RicaricaDatiDopoCambioUO();
					OnAggiorna();
					EndWaitCursor();
				}
			}

			setTemp.CloseRecordset("CListaPrenotazioniCupDlg::OnBnClickedCambiaUO");
		}
	}
	else
	{
		long lPrevUO = theApp.m_lUO;

		long lUserID;
		AMLogin_GetUserID(&lUserID);

		CUOUtenteDlg(this, lUserID).DoModal();

		if (theApp.m_lUO <= 0)
		{
			theApp.m_lUO = lPrevUO;
		}
		else
		{
			SetDlgItemText(IDC_STATIC_UO, theApp.GetMessageString(IDS_UO) + ": " + CUOSet().GetDescrizione(theApp.m_lUO));

			BeginWaitCursor();
			m_pEsamiView->RicaricaDatiDopoCambioUO();
			RiempiComboSedi();
			OnAggiorna();
			EndWaitCursor();
		}
	}
}

void CListaPrenotazioniCupDlg::OnBnClickedChkFilterData()
{
	UpdateData(TRUE);
	EnableFields(m_bFieldsEnabled);
	// m_ctrlComboData.EnableWindow(m_ctrlChkFilterData.GetCheck() == BST_UNCHECKED);
	// m_ctrlDataIniz.EnableWindow(m_ctrlChkFilterData.GetCheck() == BST_UNCHECKED);
	// m_ctrlDataFine.EnableWindow(m_ctrlChkFilterData.GetCheck() == BST_UNCHECKED);
}

void CListaPrenotazioniCupDlg::OnBnClickedStampa()
{
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nCurSel = m_ctrlList.GetNextSelectedItem(pos);

		if (nCurSel >= 0)
		{
			// imposto l'ID della worklist che sto stampando //
			theApp.m_lIDPrintingWorklist = m_ctrlList.GetItemData(nCurSel);

			if (theApp.m_lIDPrintingWorklist < 0)
				theApp.m_lIDPrintingWorklist = -theApp.m_lIDPrintingWorklist;

			// lancio la stampa //
			long lPdfId = 0;
			m_pEsamiView->AnteprimaStampaReport(STAMPA, VERIFICA_NO, theApp.m_sEditRep + "\\Worklist.rpa", FALSE, 0, &lPdfId,"");

			// resetto l'ID della worklist da stampare //
			theApp.m_lIDPrintingWorklist = 0;
		}
	}
}

void CListaPrenotazioniCupDlg::OnBnClickedPrintList()
{
	if (m_ctrlList && m_ctrlList.GetItemCount() > 0)
	{
		CString sStato;
		m_ctrlComboStato.GetWindowText(sStato);
		sStato.MakeUpper();

		CString sSede;
		m_ctrlComboSede.GetWindowText(sSede);
		sSede.MakeUpper();

		CString sSala;
		m_ctrlComboSala.GetWindowText(sSala);
		sSala.MakeUpper();

		CString sProvenienza;
		m_ctrlComboProvenienza.GetWindowText(sProvenienza);
		sProvenienza.MakeUpper();

		CString sDataDa;
		m_ctrlDataIniz.GetWindowText(sDataDa);
		sDataDa.MakeUpper();

		CString sDataA;
		m_ctrlDataFine.GetWindowText(sDataA);
		sDataA.MakeUpper();

		CString sFooter;
		sFooter.Format(theApp.GetMessageString(IDS_WORKLIST_FOOTERNEW), sStato, sProvenienza, sSede, sSala, sDataDa, sDataA);
		
		m_ctrlList.SetNotePiePagina(sFooter);
		m_ctrlList.Print();
	}
}

void CListaPrenotazioniCupDlg::EnableFields(BOOL bEnable)
{
	m_bFieldsEnabled = bEnable;

	m_ctrlButtonOK.EnableWindow(bEnable);
	m_ctrlBtnCambiaUO.EnableWindow(bEnable);
	m_ctrlButtonRefresh.EnableWindow(bEnable);
	m_ctrlButtonPrintList.EnableWindow(bEnable);
	m_ctrlComboStato.EnableWindow(bEnable);
	m_ctrlComboSede.EnableWindow(bEnable);
	m_ctrlComboSala.EnableWindow(bEnable);
	m_ctrlComboProvenienza.EnableWindow(bEnable);

	bEnable &= (m_ctrlChkFilterData.GetCheck() == BST_UNCHECKED);
	m_ctrlComboData.EnableWindow(bEnable);
	m_ctrlDataIniz.EnableWindow(bEnable && (m_ctrlComboData.GetCurSel() <= 0)); // .SetReadOnly(!bEnable);
	m_ctrlDataFine.EnableWindow(bEnable && (m_ctrlComboData.GetCurSel() <= 0)); // .SetReadOnly(!bEnable);
}

void CListaPrenotazioniCupDlg::OnDettagli()
{
	VediDettagliRichiestaSelezionata();
}

void CListaPrenotazioniCupDlg::OnVediEsame()
{
	GoToEsameSelezionato();
}

void CListaPrenotazioniCupDlg::OnAnnullaIP()
{
	AnnullaIPSelezionato();
}

void CListaPrenotazioniCupDlg::OnNonPresentato()
{
	// Sandro 03/08/2016 // RIMA 16037.RN31 //

	if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury)
	{
		if ((theApp.m_dwPrivileges & AMLogin_Permissions::personalizable_06) == FALSE)
		{
			theApp.AfxMessageBoxEndo(IDS_UTENTE_NONABILITATO);
			return;
		}
	}

	//

	SetNonPresentato();
}

void CListaPrenotazioniCupDlg::OnPresentato()
{
	AnnullaNonPresentato();
}

void CListaPrenotazioniCupDlg::OnStart()
{
	//Julio - BUG 3365 - MAMOGUS
	POSITION pos = m_ctrlList.GetFirstSelectedItemPosition();
	StartEsameSelezionato();
	if (pos != NULL)
	{
		CheckComboPrestazioni(pos);
		if (theApp.m_bAtivaListaDO)
			CheckFoglioRiferimento(pos);//Gabriel BUG 6225 - Lista DO
	}
	//
}

BOOL CListaPrenotazioniCupDlg::IsEsameAnnullabile()
{
	if (POSITION pos = m_ctrlList.GetFirstSelectedItemPosition())
	{
		if (m_pWorkListManager->IsExamAbortable(&m_ctrlList, m_ctrlList.GetNextSelectedItem(pos)))
			return TRUE;
	}

	return FALSE;
}

void CListaPrenotazioniCupDlg::SetNonPresentato()
{
	// non posso cominciare esami prenotati in altre sedi //

	int nSedeCurSel = m_ctrlComboSede.GetCurSel();
	if (nSedeCurSel >= 0)
	{
		long lSedeValue = m_ctrlComboSede.GetItemData(nSedeCurSel);
		if (lSedeValue == theApp.m_lIDSedeEsameDefault)
		{
			if (POSITION pos = m_ctrlList.GetFirstSelectedItemPosition())
			{
				if (theApp.AfxMessageBoxEndo(IDS_PAZIENTE_NONPRESENTATO, MB_YESNO) == IDYES)
				{
					// Sandro 03/08/2016 // RIMA 16037.RN31 //

					long lIDMotivo = 0;
					if (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury)
					{
						CMotivoAnnullamentoDlg dlgMA(this);
						if (dlgMA.DoModal() == IDOK)
							lIDMotivo = dlgMA.GetIDMotivo();
						else
							return;
					}

					//
					
					EnableFields(FALSE);
					if (m_pWorkListManager->SetNoShow(&m_ctrlList, m_ctrlList.GetNextSelectedItem(pos), lIDMotivo))
					{
						m_bIsExiting = TRUE; // Julio (FIX) BUG 3759 - TesiCapture Melhoria Filtro Worklist
						PostMessage(WM_COMMAND, IDOK);
					}
					else
					{
						EnableFields(TRUE);
						OnAggiorna();
					}
				}
			}
		}
	}
}

void CListaPrenotazioniCupDlg::AnnullaNonPresentato()
{
	// non posso cominciare esami prenotati in altre sedi //

	int nSedeCurSel = m_ctrlComboSede.GetCurSel();
	if (nSedeCurSel >= 0)
	{
		long lSedeValue = m_ctrlComboSede.GetItemData(nSedeCurSel);
		if (lSedeValue == theApp.m_lIDSedeEsameDefault)
		{
			if (POSITION pos = m_ctrlList.GetFirstSelectedItemPosition())
			{
				if (theApp.AfxMessageBoxEndo("L'azione contrassegnerà la richiesta come \"ACCETTATA\", proseguire?", MB_YESNO) == IDYES)
				{
					EnableFields(FALSE);
					if (m_pWorkListManager->AbortNoShow(&m_ctrlList, m_ctrlList.GetNextSelectedItem(pos)))
					{
						m_bIsExiting = TRUE; // Julio (FIX) BUG 3759 - TesiCapture Melhoria Filtro Worklist
						PostMessage(WM_COMMAND, IDOK);
					}
					else
					{
						EnableFields(TRUE);
						OnAggiorna();
					}
				}
			}
		}
	}
}

void CListaPrenotazioniCupDlg::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_ctrlButtonStampa.EnableWindow(m_ctrlList.GetFirstSelectedItemPosition() != NULL);
}
