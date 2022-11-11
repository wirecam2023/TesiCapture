// -------------------------------------------------------------------------------------------------------------------------
// Marvel Carvalho - BUG 4308 Esquemas Anatomicos Fleury
// -------------------------------------------------------------------------------------------------------------------------
// TODO: 01) MARVEL DEBUG - colocar SAVE no destrutor Não funcionou, está perdendo alterações no grid IDC_LIST_SAA caso o usuário mova para outro exame antes de salvar

#include "stdafx.h"
#include "Endox.h"

#include "EsamiSet.h"
#include "EsamiView.h"
#include "EesamiCodeesameSiglaVistaSet.h"
#include "SchemiAnatomiciAggiuntoDynForm.h"
#include "SchemiAnatomiciEditDlg.h" // Marvel Carvalho - BUG 4308 Esquemas Anatômicos Fleury
#include "InputBox.h"

// ORDER OF GRID COLUMNS
// SCHEMI_ANATOMICI_AGGIUNTO
#define _SAA_COL_CONTATORE				0
#define _SAA_COL_CONTATORE_EESAMI		1
#define _SAA_COL_ID_SCHEMI_ANATOMICI    2
#define _SAA_COL_DESCRIZIONE			3
#define _SAA_COL_STATO					4
#define _SAA_QTT_COL_					5

#define _SAA_COL_STATO_NEW		0
#define _SAA_COL_STATO_EDITED	1
#define _SAA_COL_STATO_EXPORTED	2

//// CListControl & DB Column of control
//#define _DBCTRL_NEW		"NEW"
//#define _DBCTRL_SAME	"SAME"
//#define _DBCTRL_ALTERED	"ALTERED"
//#define _DBCTRL_DELETED	"DELETED"
//#define _DBCTRL_FORGET	"FORGET"	// DO NOTHING

// CListControl & DB Column of control
#define _DBCTRL_NEW		"NOVO"
#define _DBCTRL_SAME	"ORIGINAL"
#define _DBCTRL_ALTERED	"ALTEREDO"
#define _DBCTRL_DELETED	"APAGAR"
#define _DBCTRL_FORGET	"DESPREZAR"	// DO NOTHING

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSchemiAnatomiciAggiuntoDynForm::CSchemiAnatomiciAggiuntoDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(nID, pParent, pEsamiView)
{
	m_lCurrentSchemiAnatomici = -1; 
	m_lCurrentSchemiAnatomiciAggiunto = -1;
	m_bAltered = FALSE;
	m_bReadOnly = FALSE;
}

CSchemiAnatomiciAggiuntoDynForm::CSchemiAnatomiciAggiuntoDynForm(CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(CSchemiAnatomiciAggiuntoDynForm::IDD, pParent, pEsamiView)
{
	m_lCurrentSchemiAnatomici = -1;
	m_lCurrentSchemiAnatomiciAggiunto = -1;
	m_bAltered = FALSE;
	m_bReadOnly = FALSE;
}

CSchemiAnatomiciAggiuntoDynForm::~CSchemiAnatomiciAggiuntoDynForm()
{
}

BEGIN_MESSAGE_MAP(CSchemiAnatomiciAggiuntoDynForm, CEndoxDynForm)

	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_NOTIFY(NM_CLICK, IDC_LIST_SAD, &CSchemiAnatomiciAggiuntoDynForm::OnNMClickListSad)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SAD, &CSchemiAnatomiciAggiuntoDynForm::OnNMDblclkListSad)
	ON_BN_CLICKED(IDC_BTN_ADD, &CSchemiAnatomiciAggiuntoDynForm::OnBnClickedBtnAdd)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SAA, &CSchemiAnatomiciAggiuntoDynForm::OnNMClickListSaa)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SAA, &CSchemiAnatomiciAggiuntoDynForm::OnNMDblclkListSaa)
	ON_BN_CLICKED(IDC_BTN_DEL, &CSchemiAnatomiciAggiuntoDynForm::OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_EDT, &CSchemiAnatomiciAggiuntoDynForm::OnBnClickedBtnEdt)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CSchemiAnatomiciAggiuntoDynForm::OnBnClickedBtnSave)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_SAA, &CSchemiAnatomiciAggiuntoDynForm::OnNMRClickListSaa)
	ON_BN_CLICKED(IDC_HLP, &CSchemiAnatomiciAggiuntoDynForm::OnBnClickedHlp)

END_MESSAGE_MAP()

void CSchemiAnatomiciAggiuntoDynForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CEsamiView* pEsamiView, long lColore, long lIDFaseBlocco)
{
	if (pEsamiView->m_pDynForm[sub_schemi_anatomichi] == NULL)
	{
		pEsamiView->m_pDynForm[sub_schemi_anatomichi] = new CSchemiAnatomiciAggiuntoDynForm(NULL, pEsamiView);
		if (pEsamiView->m_pDynForm[sub_schemi_anatomichi] != NULL)
		{
			pEsamiView->m_pDynForm[sub_schemi_anatomichi]->m_pParentFrame = pParentFrame;
			pEsamiView->m_pDynForm[sub_schemi_anatomichi]->m_lColore = lColore;
			pEsamiView->m_pDynForm[sub_schemi_anatomichi]->m_lIDFaseBlocco = lIDFaseBlocco;
			
			CRect rectFrame;
			pParentFrame->GetWindowRect(&rectFrame);
			pEsamiView->m_pDynForm[sub_schemi_anatomichi]->CreateChildForm(CSchemiAnatomiciAggiuntoDynForm::IDD, pParent, rectFrame);
		}
	}
}

HBRUSH CSchemiAnatomiciAggiuntoDynForm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	// TODO: descobrir pra que serve esta função
	HBRUSH hBrush = CEndoxDynForm::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		// TODO: ver o que isso faz...
		case IDC_LIST_SAD:
		case IDC_LIST_SAA:
		{
			if (m_lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_lColore]);

			break;
		}
	}
	return hBrush;
}

void CSchemiAnatomiciAggiuntoDynForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxDynForm::DoDataExchange(pDX);

	//DDX_Control(pDX, IDC_STATIC_TITOLO, m_ctrlStaticTitolo);
	//DDX_Control(pDX, IDC_LIST_FARMACI, m_ctrlListFarmaci);

	DDX_Control(pDX, IDC_LIST_SAD, m_ctrlListGridSchemiAnatomici        );
	DDX_Control(pDX, IDC_LIST_SAA, m_ctrlListGridSchemiAnatomiciAggiunto);

	ListGridSchemiAnatomiciRiempi();
	ListGridSchemiAnatomiciAggiuntoRiempi(m_pEsamiView->m_pEsamiSet->m_lContatore);

	//if (pDX->m_bSaveAndValidate) // não entendi o uso do m_bSaveAndValidate
	//{
		//OnBnClickedBtnSave(); 
	//}
	//else{
	//}
}

BOOL CSchemiAnatomiciAggiuntoDynForm::OnInitDialog()
{
	CEndoxDynForm::OnInitDialog();
	
	///dodataex

	int i;

	//m_lPaziente = m_pEsamiView->m_pEsamiSet->m_lPaziente;
	//m_lEsame = m_pEsamiView->m_pEsamiSet->m_lContatore;
	m_lIDESAMI = m_pEsamiView->m_pEsamiSet->m_lIDEsame;
	//m_pEsamiView->m_pImgManager->SetCurrentIDs(m_lPaziente, m_lEsame);
	//m_bConfirmed = m_pEsamiView->m_pImgManager->IsExamConfirmed(m_strDvdLabel);

	

	// Configura os CABEÇALHOS das COLUNAS dos GRIDS

	//-----------------------------------------------------------
	// GRID DA SCHEMI_ANATOMICI DISPONIBILE PER UO e SIGLA EXAME
	//-----------------------------------------------------------
	//ID
	//DESCRIZIONE
	i = 0;
	while (m_ctrlListGridSchemiAnatomici.DeleteColumn(0));
	m_ctrlListGridSchemiAnatomici.SetExtendedStyle(m_ctrlListGridSchemiAnatomici.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);  //| LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlListGridSchemiAnatomici.InsertColumn(i++, theApp.GetMessageString(IDS_SA_DESCRIZIONE), LVCFMT_LEFT, 100);  // "DESCRIZIONE"


	//---------------------------------------------------
	// GRID DOS SCHEMI_ANATOMICI_AGGIUNTO
	//---------------------------------------------------
	// CONTATORE
	// CONTATORE_EESAMI
	// ID_SCHEMI_ANATOMICI
	// DESCRIZIONE
	// STATO
	// DB_CTRL

	i = 0;
	while (m_ctrlListGridSchemiAnatomiciAggiunto.DeleteColumn(0));
	m_ctrlListGridSchemiAnatomiciAggiunto.SetExtendedStyle(m_ctrlListGridSchemiAnatomiciAggiunto.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);		//  | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
	m_ctrlListGridSchemiAnatomiciAggiunto.InsertColumn(i++, theApp.GetMessageString(IDS_SAA_CONTATORE			), LVCFMT_LEFT, 0);		// "CONTATORE"
	m_ctrlListGridSchemiAnatomiciAggiunto.InsertColumn(i++, theApp.GetMessageString(IDS_SAA_CONTATORE_EESAMI	), LVCFMT_LEFT, 0);		// "CONTATORE_EESAMI"
	m_ctrlListGridSchemiAnatomiciAggiunto.InsertColumn(i++, theApp.GetMessageString(IDS_SAA_ID_SCHEMI_ANATOMICI	), LVCFMT_LEFT, 0);		// "ID_SCHEMI_ANATOMICI"
	m_ctrlListGridSchemiAnatomiciAggiunto.InsertColumn(i++, theApp.GetMessageString(IDS_SAA_DESCRIZIONE			), LVCFMT_LEFT, 100);	// "DESCRIZIONE"
	m_ctrlListGridSchemiAnatomiciAggiunto.InsertColumn(i++, theApp.GetMessageString(IDS_SAA_STATO				), LVCFMT_LEFT, 100);	// "STATO"
	m_ctrlListGridSchemiAnatomiciAggiunto.InsertColumn(i++, theApp.GetMessageString(IDS_SAA_CTRL				), LVCFMT_LEFT, 100);	// "CTRL"

	ListGridSchemiAnatomiciAggiuntoSetSizeToAllColumns();

	// to translate if needed
	// ... theApp.GetMessageString(IDS_GEP_LIST_01)

	// NÃO ESTÁ FUNCIONANDO O REFRESH DA LARGURA DAS COLUNAS
	//OnBnClickedBtnSave(); // faz um refresh inicial para ajustar a largura das colunas dos grids

	///ancoras - julio alterou

	AddAnchor(IDC_STATIC_TITLE1, CSize(  0,   0), CSize(100,   0));
	AddAnchor(IDC_HLP,           CSize(100,   0), CSize(100,   0));
	AddAnchor(IDC_LIST_SAD,		 CSize(  0,   0), CSize(100,  45));
	AddAnchor(IDC_BTN_ADD,		 CSize(  0,  47), CSize( 15,  47));
	AddAnchor(IDC_STATIC_TITLE2, CSize(  0,  50), CSize(100,  50));
	AddAnchor(IDC_LIST_SAA,		 CSize(  0,  50), CSize(100, 100));
	AddAnchor(IDC_BTN_DEL,		 CSize(  0, 100), CSize( 15, 100));
	AddAnchor(IDC_BTN_EDT,		 CSize( 17, 100), CSize( 32, 100));
	AddAnchor(IDC_BTN_SAVE,		 CSize( 34, 100), CSize( 47, 100));

	theApp.LocalizeDialog(this, CSchemiAnatomiciAggiuntoDynForm::IDD, "SchemiAnatomiciAggiuntoDynForm");

	return TRUE;
}

//void CSchemiAnatomiciAggiuntoDynForm::ListGridSchemiAnatomiciUpdateActual(long p_lIDSelected)
//{
//	// update actual Schemi
//	BOOL bError = TRUE;
//	CString strFilter;
//	strFilter.Format("ID=%li", p_lIDSelected);
//
//	if (!m_setSchemiAnatomici.RecordsetReOpen(bError, strFilter, "DESCRIZIONE DESC", "CSchemiAnatomiciRecordDlg::ListGridSchemiAnatomiciEtichetteUpdateActual"))
//	{
//		m_setSchemiAnatomici.SetEmpty();
//	}
//	m_lCurrentSchemiAnatomici = &(m_setSchemiAnatomici.m_pSchemiAnatomici);
//}

void CSchemiAnatomiciAggiuntoDynForm::ListGridSetItemFocus(CAMEditComboListCtrl* p_pThisList, int iRow)
{
	// funcionava no CListSortableCtrl
	// não funcionou no CAMEditComboListCtrl (não tenho o código fonte para implementar)
	this->SetFocus();
	((CListCtrl*)this)->SetItemState(-1, 0, LVIS_SELECTED);
	((CListCtrl*)this)->SetItemState(iRow, LVIS_SELECTED, LVIS_SELECTED);
	((CListCtrl*)this)->EnsureVisible(iRow, FALSE);
}

long CSchemiAnatomiciAggiuntoDynForm::ListGridSchemiAnatomiciGetIDSelected()
{
	int iActualRow = m_ctrlListGridSchemiAnatomici.GetSelectionMark();	// Retrieves the item with the selection mark, or -1 if none.
	long lActualID = (iActualRow >= 0 ? m_ctrlListGridSchemiAnatomici.GetItemData(iActualRow) : m_lCurrentSchemiAnatomici);
	return lActualID;
}

int CSchemiAnatomiciAggiuntoDynForm::ListGridSchemiAnatomiciAggiuntoGetIDSelected(long* p_lContatoreSchemiAggiuntoToEdit, long* p_lIDSchemiAnatomici)
{
	int iActualRow = m_ctrlListGridSchemiAnatomiciAggiunto.GetSelectionMark();	// Retrieves the item with the selection mark, or -1 if none.
	*p_lContatoreSchemiAggiuntoToEdit = (iActualRow >= 0 ? m_ctrlListGridSchemiAnatomiciAggiunto.GetItemData(iActualRow) : -1);
	*p_lIDSchemiAnatomici             = _ttol(m_ctrlListGridSchemiAnatomiciAggiunto.GetItemText(iActualRow, _SAA_COL_ID_SCHEMI_ANATOMICI));
	return iActualRow;
}

// Binded to [SCHEMI_ANATOMICI]
void CSchemiAnatomiciAggiuntoDynForm::ListGridSchemiAnatomiciRiempi()
{
#define _STRLOG_0005 "CSchemiAnatomiciAggiuntoDynForm::ListGridSchemiAnatomiciRiempi"

	// TODO: FAZER O FILTRO POR SIGLA DO EXAME TAMBÉM

	//CSchemiAnatomiciSet         m_setSchemiAnatomici;
	//CAMEditComboListCtrl m_ctrlListGridSchemiAnatomici;          // Binded to [SCHEMI_ANATOMICI]

	BeginWaitCursor();
	m_ctrlListGridSchemiAnatomici.SetRedraw(FALSE);

	int  iActualRow = m_ctrlListGridSchemiAnatomici.GetSelectionMark();	// Retrieves the item with the selection mark, or -1 if none.
	long lActualID = -1;
	m_ctrlListGridSchemiAnatomici.DeleteAllItems();

	CString sAuxTitle = "";

	// Recupera a sigla do exame atual
	CEesamiCodeesameSiglaVistaSet setTempSiglaEesami;
	CString strFilter1;
	CString sSiglaEsami = "";

	// NÃO FUNCIONOU
	// strFilter.Format("UO=%li AND CODICEPRESTAZIONEPREVISTA=%s", theApp.m_lUO, theApp.m_sPrestazione);
	strFilter1.Format("CONTATORE=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);
	setTempSiglaEesami.SetOpenFilter(strFilter1);

	if (setTempSiglaEesami.OpenRecordset(_STRLOG_0005))
	{
		if (!setTempSiglaEesami.IsEOF())
		{
			sSiglaEsami = setTempSiglaEesami.m_sSIGLA;
			//setTempSiglaEesami.MoveNext();
		}
		setTempSiglaEesami.CloseRecordset(_STRLOG_0005);
	}

	CSchemiAnatomiciSet setTempSchemiAnatomici;

	int iNumRecsAdd = 0;

	if (!sSiglaEsami.IsEmpty()) 
	{
		CString strFilter2;
		strFilter2.Format("UO=%li AND CODICEPRESTAZIONEPREVISTA='%s'", theApp.m_lUO, sSiglaEsami);
	
		setTempSchemiAnatomici.SetOpenFilter(strFilter2);

		if (setTempSchemiAnatomici.OpenRecordset(_STRLOG_0005))
		{
			while (!setTempSchemiAnatomici.IsEOF())
			{
				int nRowNumber = 0;
				// ADD new ROW and data of ONLY ONE COLUMN
				nRowNumber = m_ctrlListGridSchemiAnatomici.InsertItem(0, setTempSchemiAnatomici.m_sDescrizione.Trim());	// insert a new ROW with the first COLUMN
				m_ctrlListGridSchemiAnatomici.SetItemData(nRowNumber, setTempSchemiAnatomici.m_lID);	                    // set ID of the ROW
				iNumRecsAdd++;
				sAuxTitle = "PARA A SIGLA DO EXAME";
				setTempSchemiAnatomici.MoveNext();
			}
			setTempSchemiAnatomici.CloseRecordset(_STRLOG_0005);
		}
	}

	// Se não encontrar a sigla do exame, faz o filtro apenas por UO
	// se não conseguiu adicionar nada até aqui, tenta apenas por UO
	if (iNumRecsAdd == 0)
	{
		CString strFilter3;
		strFilter3.Format("UO=%li", theApp.m_lUO);

		setTempSchemiAnatomici.SetOpenFilter(strFilter3);

		if (setTempSchemiAnatomici.OpenRecordset(_STRLOG_0005))
		{
			while (!setTempSchemiAnatomici.IsEOF())
			{
				int nRowNumber = 0;
				// ADD new ROW and data of ONLY ONE COLUMN
				nRowNumber = m_ctrlListGridSchemiAnatomici.InsertItem(0, setTempSchemiAnatomici.m_sDescrizione.Trim());	// insert a new ROW with the first COLUMN
				m_ctrlListGridSchemiAnatomici.SetItemData(nRowNumber, setTempSchemiAnatomici.m_lID);	                // set ID of the ROW
				iNumRecsAdd++;
				sAuxTitle = "PARA A ESPECIALIDADE";
				setTempSchemiAnatomici.MoveNext();
			}
			setTempSchemiAnatomici.CloseRecordset(_STRLOG_0005);
		}
	}

	// ajusta largura da coluna
	m_ctrlListGridSchemiAnatomici.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlListGridSchemiAnatomici.SetRedraw(TRUE);
	EndWaitCursor();

	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_STATIC_TITLE1);

	if (pStatic)
		pStatic->SetWindowText("ESQUEMAS ANATÔMICOS DISPONÍVEIS " + sAuxTitle);

	return;// lActualID;
}

// BInded to [SCHEMI_ANATOMICI_AGGIUNTO]
void CSchemiAnatomiciAggiuntoDynForm::ListGridSchemiAnatomiciAggiuntoRiempi(long p_lCONTATORE_EESAMI)
{
#define _STRLOG_0006 "CSchemiAnatomiciAggiuntoDynForm::ListGridSchemiAnatomiciAggiuntoRiempi"

	//CSchemiAnatomiciAggiuntoSet m_setSchemiAnatomiciAggiunto;
	//CAMEditComboListCtrl m_ctrlListGridSchemiAnatomiciAggiunto;	 // Binded to [SCHEMI_ANATOMICI_AGGIUNTO]

	BeginWaitCursor();
	m_ctrlListGridSchemiAnatomiciAggiunto.SetRedraw(FALSE);

	int  iActualRow = m_ctrlListGridSchemiAnatomiciAggiunto.GetSelectionMark();	// Retrieves the item with the selection mark, or -1 if none.
	long lActualID = -1;
	m_ctrlListGridSchemiAnatomiciAggiunto.DeleteAllItems();

	CSchemiAnatomiciAggiuntoSet setTemp;
	CString strFilter;
	strFilter.Format("CONTATORE_EESAMI=%li", p_lCONTATORE_EESAMI);
	setTemp.SetOpenFilter(strFilter);

	if (setTemp.OpenRecordset(_STRLOG_0006))
	{
		while (!setTemp.IsEOF())
		{
			int nRowNumber = 0;

			CString sAux[_SAA_QTT_COL_];
			sAux[_SAA_COL_CONTATORE].Format("%ld", setTemp.m_lCONTATORE);
			sAux[_SAA_COL_CONTATORE_EESAMI].Format("%ld", setTemp.m_lCONTATORE_EESAMI);
			sAux[_SAA_COL_ID_SCHEMI_ANATOMICI].Format("%ld", setTemp.m_lID_SCHEMI_ANATOMICI);
			sAux[_SAA_COL_DESCRIZIONE] = setTemp.m_sDESCRIZIONE.Trim();
			sAux[_SAA_COL_STATO] = ConvertSchemiAnatomiciAggiuntoStatoToString(setTemp.m_lSTATO);

			// ADD new ROW and data of the COLUMNS
			nRowNumber = m_ctrlListGridSchemiAnatomiciAggiunto.InsertItem(0, sAux[0]);					// insert a new ROW with the first COLUMN
			m_ctrlListGridSchemiAnatomiciAggiunto.SetItemData(nRowNumber, setTemp.m_lCONTATORE);	// set ID of the ROW
			for (int c = 1; c < _SAA_QTT_COL_; c++)
			{
				m_ctrlListGridSchemiAnatomiciAggiunto.SetItemText(nRowNumber, c, sAux[c]);	// set TEXT of the each COLUMN
			}
			// CONTROL COLUMN
			m_ctrlListGridSchemiAnatomiciAggiunto.SetItemText(nRowNumber, _SAA_QTT_COL_, _DBCTRL_SAME);	// set TEXT of the each COLUMN

			setTemp.MoveNext();
		}

		setTemp.CloseRecordset(_STRLOG_0006);
	}

	ListGridSchemiAnatomiciAggiuntoSetSizeToAllColumns();

	EndWaitCursor();

	m_bAltered = FALSE;

	return;
}

void CSchemiAnatomiciAggiuntoDynForm::ListGridSchemiAnatomiciAggiuntoSetSizeToAllColumns()
{
	// ajusta largura das colunas
	//for (int i = 0; i <= _SAA_QTT_COL_; i++)
	//	m_ctrlListGridSchemiAnatomiciAggiunto.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlListGridSchemiAnatomiciAggiunto.SetColumnWidth(_SAA_COL_CONTATORE, 0);
	m_ctrlListGridSchemiAnatomiciAggiunto.SetColumnWidth(_SAA_COL_CONTATORE_EESAMI, 0);
	m_ctrlListGridSchemiAnatomiciAggiunto.SetColumnWidth(_SAA_COL_ID_SCHEMI_ANATOMICI, 0);
	m_ctrlListGridSchemiAnatomiciAggiunto.SetColumnWidth(_SAA_COL_DESCRIZIONE, LVSCW_AUTOSIZE);
	m_ctrlListGridSchemiAnatomiciAggiunto.SetColumnWidth(_SAA_COL_STATO, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListGridSchemiAnatomiciAggiunto.SetColumnWidth(_SAA_QTT_COL_, LVSCW_AUTOSIZE);  // DB_CTRL

	m_ctrlListGridSchemiAnatomiciAggiunto.SetRedraw(TRUE);
}

void CSchemiAnatomiciAggiuntoDynForm::OnSize(UINT nType, int cx, int cy)
{
	CEndoxDynForm::OnSize(nType, cx, cy);

	//m_ctrlListGridSchemiAnatomici
	//m_ctrlListGridSchemiAnatomiciAggiunto

	//if (IsWindow(m_ctrlListFarmaci))
	//{
	//	m_ctrlListFarmaci.SetRedraw(FALSE);
	//	m_ctrlListFarmaci.SetColumnWidth(0, 0);
	//	m_ctrlListFarmaci.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	//	m_ctrlListFarmaci.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	//	m_ctrlListFarmaci.SetRedraw(TRUE);
	//}
}

LRESULT CSchemiAnatomiciAggiuntoDynForm::OnFormAnnullaEsame(WPARAM wParam, LPARAM lParam)
{
	return OnFormReset(wParam, lParam);
}

LRESULT CSchemiAnatomiciAggiuntoDynForm::OnFormClone(WPARAM wParam, LPARAM lParam)
{
	/*
	OnFormReset(NULL, NULL);

	//

	long lIDEsameDaClonare = CEsamiSet().GetLastPatientExam(m_pEsamiView->m_pPazientiSet->m_lContatore);

	//

	CString strFilter;
	strFilter.Format("IDEsame=%li", lIDEsameDaClonare);

	CEsamiFarmaciCroniciSet setTemp;
	setTemp.SetOpenFilter(strFilter);

	if (setTemp.OpenRecordset("CSchemiAnatomiciAggiuntoDynForm::OnFormLoad"))
	{
		while(!setTemp.IsEOF())
		{
			for(int i = 0; i < m_ctrlListFarmaci.GetItemCount(); i++)
			{
				if (m_ctrlListFarmaci.GetItemData(i) == setTemp.m_lIDFarmaco)
				{
					switch(setTemp.m_lFase)
					{
						case FARMACO_NIENTE:
						{
							break;
						}
						case FARMACO_INIZIO:
						{
							m_ctrlListFarmaci.SetItemText(i, 2, theApp.GetMessageString(IDS_FARMACO_CONTINUA));
							break;
						}
						case FARMACO_CONTINUA:
						{
							m_ctrlListFarmaci.SetItemText(i, 2, theApp.GetMessageString(IDS_FARMACO_CONTINUA));
							break;
						}
						case FARMACO_FINE:
						{
							break;
						}
						default:
						{
							ASSERT(FALSE);
							break;
						}
					}
				}
			}

			setTemp.MoveNext();
		}

		setTemp.CloseRecordset("CSchemiAnatomiciAggiuntoDynForm::OnFormLoad");
	}
	*/

	return 1;
}

LRESULT CSchemiAnatomiciAggiuntoDynForm::OnFormLoad(WPARAM wParam, LPARAM lParam)
{
	OnFormReset(NULL, NULL);

	//CString strFilter;
	//strFilter.Format("IDEsame=%li", m_pEsamiView->m_pEsamiSet->m_lContatore);

	//CEsamiFarmaciCroniciSet setTemp;
	//setTemp.SetOpenFilter(strFilter);

	//if (setTemp.OpenRecordset("CSchemiAnatomiciAggiuntoDynForm::OnFormLoad"))
	//{
	//	while(!setTemp.IsEOF())
	//	{
	//		for(int i = 0; i < m_ctrlListFarmaci.GetItemCount(); i++)
	//		{
	//			if (m_ctrlListFarmaci.GetItemData(i) == setTemp.m_lIDFarmaco)
	//			{
	//				switch(setTemp.m_lFase)
	//				{
	//					case FARMACO_NIENTE:
	//					{
	//						break;
	//					}
	//					case FARMACO_INIZIO:
	//					{
	//						m_ctrlListFarmaci.SetItemText(i, 2, theApp.GetMessageString(IDS_FARMACO_INIZIO));
	//						break;
	//					}
	//					case FARMACO_CONTINUA:
	//					{
	//						m_ctrlListFarmaci.SetItemText(i, 2, theApp.GetMessageString(IDS_FARMACO_CONTINUA));
	//						break;
	//					}
	//					case FARMACO_FINE:
	//					{
	//						m_ctrlListFarmaci.SetItemText(i, 2, theApp.GetMessageString(IDS_FARMACO_FINE));
	//						break;
	//					}
	//					default:
	//					{
	//						ASSERT(FALSE);
	//						break;
	//					}
	//				}
	//			}
	//		}

	//		setTemp.MoveNext();
	//	}

	//	setTemp.CloseRecordset("CSchemiAnatomiciAggiuntoDynForm::OnFormLoad");
	//}

	return 1;
}

LRESULT CSchemiAnatomiciAggiuntoDynForm::OnFormReadOnly(WPARAM wParam, LPARAM lParam)
{
	if (wParam == FALSE && !(theApp.m_nProgramMode & FILTER_RECORD_ESAMI) && m_pEsamiView->IsFaseChiusa(m_lIDFaseBlocco))
		wParam = TRUE;

	m_bReadOnly = (BOOL)wParam;

	//

	//m_ctrlListFarmaci.EnableWindow(!m_bReadOnly);

	//

	return 1;
}

LRESULT CSchemiAnatomiciAggiuntoDynForm::OnFormReset(WPARAM wParam, LPARAM lParam)
{
	/*
	for(int i = 0; i < m_ctrlListFarmaci.GetItemCount(); i++)
		m_ctrlListFarmaci.SetItemText(i, 2, "");
	*/

	/*m_ctrlListFarmaci.SetRedraw(FALSE);
	m_ctrlListFarmaci.DeleteAllItems();

	CString sFilter = "";
	if (!m_pEsamiView->m_pPazientiSet->IsFieldNull(&m_pEsamiView->m_pPazientiSet->m_lIDMalattiaCronica) && (m_pEsamiView->m_pPazientiSet->m_lIDMalattiaCronica > 0))
	{
		sFilter.Format("IDMalattia=%li", m_pEsamiView->m_pPazientiSet->m_lIDMalattiaCronica);
	}
	else
	{
		if (!m_pEsamiView->m_pEsamiSet->IsFieldNull(&m_pEsamiView->m_pEsamiSet->m_lIDMalattiaCronica) && (m_pEsamiView->m_pEsamiSet->m_lIDMalattiaCronica > 0))
			sFilter.Format("IDMalattia=%li", m_pEsamiView->m_pEsamiSet->m_lIDMalattiaCronica);
	}
	sFilter.Trim();

	if (!sFilter.IsEmpty())
	{
		CMalattieCronicheCampiSet setTemp;
		setTemp.SetOpenFilter(sFilter);
		setTemp.SetSortRecord("Ordine, ID");

		if (setTemp.OpenRecordset("CSchemiAnatomiciAggiuntoDynForm::OnInitDialog"))
		{
			int nIndex = 0;

			while(!setTemp.IsEOF())
			{
				if (setTemp.m_lTipoCampo == TIPOCAMPO_FARMACO)
				{
					m_ctrlListFarmaci.InsertItem(nIndex, "");
					m_ctrlListFarmaci.SetItemData(nIndex, setTemp.m_lIDCampo);

					m_ctrlListFarmaci.SetItemText(nIndex, 1, CFarmaciPazientiCroniciSet().GetDescrizione(setTemp.m_lIDCampo));

					m_ctrlListFarmaci.SetSubItemCombo(nIndex, 2, m_slTerapia);

					nIndex++;
				}

				setTemp.MoveNext();
			}

			setTemp.CloseRecordset("CSchemiAnatomiciAggiuntoDynForm::OnInitDialog");
		}
	}

	m_ctrlListFarmaci.SetColumnWidth(0, 0);
	m_ctrlListFarmaci.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListFarmaci.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListFarmaci.SetRedraw(TRUE);
	*/

	return 1;
}

LRESULT CSchemiAnatomiciAggiuntoDynForm::OnFormSave(WPARAM wParam, LPARAM lParam)
{
	/*
	CEsamiFarmaciCroniciSet().DelAllRows(m_pEsamiView->m_pEsamiSet->m_lContatore);

	for(int i = 0; i < m_ctrlListFarmaci.GetItemCount(); i++)
	{
		CString sTemp = m_ctrlListFarmaci.GetItemText(i, 2);

		if (sTemp == theApp.GetMessageString(IDS_FARMACO_INIZIO))
		{
			CEsamiFarmaciCroniciSet().AddRow(m_pEsamiView->m_pEsamiSet->m_lContatore, m_ctrlListFarmaci.GetItemData(i), FARMACO_INIZIO);
		}
		else if (sTemp == theApp.GetMessageString(IDS_FARMACO_CONTINUA))
		{
			CEsamiFarmaciCroniciSet().AddRow(m_pEsamiView->m_pEsamiSet->m_lContatore, m_ctrlListFarmaci.GetItemData(i), FARMACO_CONTINUA);
		}
		else if (sTemp == theApp.GetMessageString(IDS_FARMACO_FINE))
		{
			CEsamiFarmaciCroniciSet().AddRow(m_pEsamiView->m_pEsamiSet->m_lContatore, m_ctrlListFarmaci.GetItemData(i), FARMACO_FINE);
		}
	}
	*/

	return 1;
}

LRESULT CSchemiAnatomiciAggiuntoDynForm::OnFormSearchNew(WPARAM wParam, LPARAM lParam)
{
	/*
	CString *pStrFrom = (CString*)lParam;
	CString *pStrWhere = (CString*)wParam;

	if (m_pEsamiView->m_pEsamiSet->m_iAllergie >= 0)
	{
		ComponiRicercaLong(pStrWhere, m_pEsamiView->m_pEsamiSet, (long*)&m_pEsamiView->m_pEsamiSet->m_iAllergie, "EEsami.Allergie", 0, "AND");

		if (m_pEsamiView->m_pEsamiSet->m_sDescrizioneAllergie.Compare("") != 0)
			ComponiRicercaString(pStrWhere, m_pEsamiView->m_pEsamiSet, &m_pEsamiView->m_pEsamiSet->m_sDescrizioneAllergie, "EEsami.DescrizioneAllergie", 0);
	}
	*/

	return 1;
}

long CSchemiAnatomiciAggiuntoDynForm::GetContenuto()
{
	return sub_schemi_anatomichi;
}

BOOL CSchemiAnatomiciAggiuntoDynForm::CampoObbligatorioValido()
{
	return TRUE;
}


int CSchemiAnatomiciAggiuntoDynForm::ListGridGetColumnsCount(CAMEditComboListCtrl* p_pThisList)
{
	return p_pThisList->GetHeaderCtrl()->GetItemCount();
}

// ** NÃO FUNCIONOU - NAO SEI POR QUÊ?
void CSchemiAnatomiciAggiuntoDynForm::ListGridSetRowColor(CAMEditComboListCtrl* p_pThisList, int p_iRow)
{
	int iDBCtrlCol = ListGridGetColumnsCount(p_pThisList) - 1;		// this is the last one column, the text of this is used for control
	CString sCurrBDControl = p_pThisList->GetItemText(p_iRow, iDBCtrlCol);

	COLORREF lColor = RGB_WHITE;

	if (sCurrBDControl == _DBCTRL_ALTERED)
		lColor = RGB(255, 255, 213);	// LIGHT YELLOW
	else
		if (sCurrBDControl == _DBCTRL_DELETED)
			lColor = RGB(255, 213, 213);   // LIGHT RED
		else
			if (sCurrBDControl == _DBCTRL_NEW)
				lColor = RGB(213, 255, 255); // LIGHT BLUE
			else
				if (sCurrBDControl == _DBCTRL_FORGET)
					lColor = RGB_GRAY_LIGHT; // LIGHT GRAY

	for (int c = 0; c <= ListGridGetColumnsCount(p_pThisList); c++)
	{
		p_pThisList->SetSubItemBkColor(p_iRow, -1, lColor);
		p_pThisList->SetSubItemTextColor(p_iRow, c, lColor);
	}
}

void CSchemiAnatomiciAggiuntoDynForm::ListGridSetDBControl(CAMEditComboListCtrl* p_pThisList, int p_iRow, CString p_strDBControl)
{
	int iDBCtrlCol = ListGridGetColumnsCount(p_pThisList) - 1;		// this is the last one column, the text of this is used for control
	CString sNewDBControl = p_strDBControl;
	CString sCurrBDControl = p_pThisList->GetItemText(p_iRow, iDBCtrlCol);

	// if its new, do not change
	if (sCurrBDControl == _DBCTRL_NEW && sNewDBControl == _DBCTRL_ALTERED)	// mantém para poder 
		sNewDBControl = _DBCTRL_NEW;
	else
		if (sCurrBDControl == _DBCTRL_NEW && sNewDBControl == _DBCTRL_DELETED)	// despreza
			sNewDBControl = _DBCTRL_FORGET;
		else
			if (sCurrBDControl == _DBCTRL_DELETED && sNewDBControl == _DBCTRL_DELETED)	// resgata da deleção registro existente
				sNewDBControl = _DBCTRL_ALTERED;
			else 
				if (sCurrBDControl == _DBCTRL_FORGET && sNewDBControl == _DBCTRL_ALTERED) // resgata do desprezo registro a adicionar
					sNewDBControl = _DBCTRL_NEW;

	p_pThisList->SetItemText(p_iRow, iDBCtrlCol, sNewDBControl);	// set TEXT of the CONTROL COLUMN
}


void CSchemiAnatomiciAggiuntoDynForm::OnNMClickListSad(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	m_lCurrentSchemiAnatomici = ListGridSchemiAnatomiciGetIDSelected();

	*pResult = 0;
}


void CSchemiAnatomiciAggiuntoDynForm::OnNMDblclkListSad(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	OnBnClickedBtnAdd();

	*pResult = 0;
}

CString CSchemiAnatomiciAggiuntoDynForm::ConvertSchemiAnatomiciAggiuntoStatoToString(long p_lSTATO)
{
	CString sAux;
	sAux.Format("%s", (p_lSTATO == _SAA_COL_STATO_NEW ? "NOVO" : (p_lSTATO == _SAA_COL_STATO_EDITED ? "EDITADO" : "EXPORTADO")));
	return sAux;
}

long CSchemiAnatomiciAggiuntoDynForm::ConvertSchemiAnatomiciAggiuntoStatoToLong(CString p_sSTATO)
{
	long lAux;
	lAux = (p_sSTATO == "NOVO" ? _SAA_COL_STATO_NEW : (p_sSTATO == "EDITADO" ? _SAA_COL_STATO_EDITED : _SAA_COL_STATO_EXPORTED));
	return lAux;
}

CString CSchemiAnatomiciAggiuntoDynForm::CalculateNewSequenceDescrizioneName()
{
	CString sResult = "";
	int iNextNumber = 0;

	int iActualRowA = m_ctrlListGridSchemiAnatomici.GetSelectionMark();	// Retrieves the item with the selection mark, or -1 if none.
	long lActualID = (iActualRowA >= 0 ? m_ctrlListGridSchemiAnatomici.GetItemData(iActualRowA) : m_lCurrentSchemiAnatomici);

	if (lActualID <= 0)
		return sResult;

	CString sCurrentDescrizioneSchemiAnatomici = m_ctrlListGridSchemiAnatomici.GetItemText(iActualRowA, 0);  // COLUNA 0

	int iTotRowsB = m_ctrlListGridSchemiAnatomiciAggiunto.GetItemCount();

	for (int iRow = iTotRowsB - 1; iRow >= 0; iRow--)
	{
		CSchemiAnatomiciAggiuntoSet setTemp;

		// pega as informações de cada linha do grid e coloca no setTemp
		CString sCurrentDescrizioneName = m_ctrlListGridSchemiAnatomiciAggiunto.GetItemText(iRow, _SAA_COL_DESCRIZIONE);

		int iFound = sCurrentDescrizioneName.Find(sCurrentDescrizioneSchemiAnatomici);
		if (iFound == 0) // inicio igual
		{
			CString sToken = _T("");
			int i = 0; // substring index to extract
			while (AfxExtractSubString(sToken, sCurrentDescrizioneName, i, '#'))
			{
				if (i > 0)
				{
					iNextNumber = _ttol(sToken);
				}
				i++;
			}
		}
	}
	CString sAux;
	sAux.Format("00%d", iNextNumber+1);
	sResult = sCurrentDescrizioneSchemiAnatomici + " #" + sAux.Mid(sAux.GetLength() - 2, 2);
	return sResult;
}


void CSchemiAnatomiciAggiuntoDynForm::OnBnClickedBtnAdd()
{
	if (m_lCurrentSchemiAnatomici <= 0)
	{
		theApp.AfxMessageBoxEndo("Selecione um Esquema Anatômico para adicionar.");
		return;
	}
	
	CString strNewDescrizione = CalculateNewSequenceDescrizioneName();
	//CInputBox theInputBox(this);
	//theInputBox.Show("Dê um nome para este Esquema Anatômico ao exame:", strNewDescrizione);

	if (!strNewDescrizione.IsEmpty())
	{
		int nRowNumber = 0;

		CString sAux[_SAA_QTT_COL_];
		sAux[_SAA_COL_CONTATORE].Format("%ld", -1);
		sAux[_SAA_COL_CONTATORE_EESAMI].Format("%ld", m_pEsamiView->m_pEsamiSet->m_lContatore );
		sAux[_SAA_COL_ID_SCHEMI_ANATOMICI].Format("%ld", m_lCurrentSchemiAnatomici);
		sAux[_SAA_COL_DESCRIZIONE] = strNewDescrizione;
		sAux[_SAA_COL_STATO] = ConvertSchemiAnatomiciAggiuntoStatoToString(_SAA_COL_STATO_NEW);

		// ADD new ROW and data of the COLUMNS
		nRowNumber = m_ctrlListGridSchemiAnatomiciAggiunto.InsertItem(0, sAux[0]);					// insert a new ROW with the first COLUMN
		m_ctrlListGridSchemiAnatomiciAggiunto.SetItemData(nRowNumber, -1);	// set ID of the ROW
		for (int c = 1; c < _SAA_QTT_COL_; c++)
		{
			m_ctrlListGridSchemiAnatomiciAggiunto.SetItemText(nRowNumber, c, sAux[c]);	// set TEXT of the each COLUMN
		}
		// CONTROL COLUMN
		m_ctrlListGridSchemiAnatomiciAggiunto.SetItemText(nRowNumber, _SAA_QTT_COL_, _DBCTRL_NEW);	// set TEXT of the each COLUMN
		ListGridSetRowColor(&m_ctrlListGridSchemiAnatomiciAggiunto, nRowNumber);
	}
	m_bAltered = TRUE;

	// autoatiza a ação add + salvar + editar
	OnBnClickedBtnSave();
	//OnBnClickedBtnEdt(); // não funcionou
}


void CSchemiAnatomiciAggiuntoDynForm::OnNMClickListSaa(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	long p_lContatoreSchemiAggiuntoToEdit, p_lIDSchemiAnatomici;
	ListGridSchemiAnatomiciAggiuntoGetIDSelected(&p_lContatoreSchemiAggiuntoToEdit, &p_lIDSchemiAnatomici);

	m_lCurrentSchemiAnatomiciAggiunto = p_lContatoreSchemiAggiuntoToEdit;
	m_lCurrentSchemiAnatomici = p_lIDSchemiAnatomici;

	*pResult = 0;
}


void CSchemiAnatomiciAggiuntoDynForm::OnNMDblclkListSaa(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	OnBnClickedBtnEdt();

	*pResult = 0;
}


void CSchemiAnatomiciAggiuntoDynForm::OnBnClickedBtnDel()
{
	{
		POSITION pos = m_ctrlListGridSchemiAnatomiciAggiunto.GetFirstSelectedItemPosition();
		int iItemSelected = -1;

		if (pos != NULL)
		{
			while (pos)
			{
				int iItemSelected = m_ctrlListGridSchemiAnatomiciAggiunto.GetNextSelectedItem(pos);
				if (m_ctrlListGridSchemiAnatomiciAggiunto.GetItemState(iItemSelected, LVIS_SELECTED) == LVIS_SELECTED)
				{
					// CONTROL COLUMN - SET TO DELETE
					ListGridSetDBControl(&m_ctrlListGridSchemiAnatomiciAggiunto, iItemSelected, _DBCTRL_DELETED);
					ListGridSetRowColor(&m_ctrlListGridSchemiAnatomiciAggiunto, iItemSelected);
				}
			}
		}
	}

	m_bAltered = TRUE;
}


void CSchemiAnatomiciAggiuntoDynForm::OnBnClickedBtnEdt()
{
	while (m_bAltered)
	{
		if (theApp.AfxMessageBoxEndo(_T("Necessário salvar antes de editar?"), MB_OKCANCEL | MB_ICONEXCLAMATION) == IDOK)
			OnBnClickedBtnSave();
		else
			return;
	}

	long p_lContatoreSchemiAggiuntoToEdit, p_lIDSchemiAnatomici;
	int iCurrRow = ListGridSchemiAnatomiciAggiuntoGetIDSelected(&p_lContatoreSchemiAggiuntoToEdit, &p_lIDSchemiAnatomici);

	if (p_lContatoreSchemiAggiuntoToEdit == -1)
	{
		theApp.AfxMessageBoxEndo(_T("Necessário selecionar um Esquema Anatômico para editar"));
		return;
	}

	int nRet = CSchemiAnatomiciEditDlg(this, m_pEsamiView, p_lContatoreSchemiAggiuntoToEdit, m_lCurrentSchemiAnatomici).DoModal();

	if (nRet > _SAA_COL_STATO_NEW) // EDITADO ou EXPORTADO
	{
		m_ctrlListGridSchemiAnatomiciAggiunto.SetItemText(iCurrRow, _SAA_COL_STATO, ConvertSchemiAnatomiciAggiuntoStatoToString(nRet));	// set TEXT of the each COLUMN
		m_ctrlListGridSchemiAnatomiciAggiunto.SetItemText(iCurrRow, _SAA_QTT_COL_, _DBCTRL_ALTERED); // CONTROL COLUMN
		ListGridSetRowColor(&m_ctrlListGridSchemiAnatomiciAggiunto, iCurrRow);
		OnBnClickedBtnSave();
	}
}


//void CSchemiAnatomiciAggiuntoDynForm::OnBnClickedBtnExp()
//{
//	// TODO: CODIFICAR EXPORTAR()
//	m_bAltered = TRUE;
//}

//void CSchemiAnatomiciAggiuntoDynForm::OnBnClickedClose()
//{
//	/*while (m_bAltered)
//	{
//		if (theApp.AfxMessageBoxEndo(_T("Deseja salvar antes de sair?"), MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
//			OnBnClickedBtnSave();
//		else
//			break;
//	}
//	m_pParentWnd->SendMessage(WM_WAITINGDICOM_CLOSING);
//	CDialog::OnOK();*/
//}


void CSchemiAnatomiciAggiuntoDynForm::OnBnClickedBtnSave()
{
	// salva conteúdo do grid para o database
	ListGridSchemiAnatomiciAggiuntoSaveAllToDatabase();

	// limpa o grid de itens correlatos e recarrega as informações do grid
	ListGridSchemiAnatomiciAggiuntoRiempi(m_pEsamiView->m_pEsamiSet->m_lContatore);

	m_bAltered = FALSE;
}


CString CSchemiAnatomiciAggiuntoDynForm::ListGridSchemiAnatomiciAggiuntoGetAcao(long* p_lID, int p_nRowNumber)
{
	*p_lID = m_ctrlListGridSchemiAnatomiciAggiunto.GetItemData(p_nRowNumber);
	CString sAcao = m_ctrlListGridSchemiAnatomiciAggiunto.GetItemText(p_nRowNumber, _SAA_QTT_COL_);
	return sAcao;
}

// Update/Insert/Delete all rows grid to Database
void CSchemiAnatomiciAggiuntoDynForm::ListGridSchemiAnatomiciAggiuntoSaveAllToDatabase()
{
#define _STRLOG_0007 "CSchemiAnatomiciAggiuntoDynForm::ListGridSchemiAnatomiciAggiuntoSaveAllToDatabase"

	BOOL bSaved = FALSE;
	long lCONTATORE = -1;

	int iTotRows = m_ctrlListGridSchemiAnatomiciAggiunto.GetItemCount();

	for (int iRow = iTotRows - 1; iRow >= 0; iRow--)
	{
		CSchemiAnatomiciAggiuntoSet setTemp;

		// pega as informações de cada linha do grid e coloca no setTemp
		CString sAcao = ListGridSchemiAnatomiciAggiuntoGetAcao(&lCONTATORE, iRow);

		if (sAcao == _DBCTRL_NEW)
		{
			if (setTemp.OpenRecordset(_STRLOG_0007))
			{
				setTemp.AddNewRecordset(_STRLOG_0007);

				// seta as informações da grid no recordset
				setTemp.m_lCONTATORE = m_ctrlListGridSchemiAnatomiciAggiunto.GetItemData(iRow);
				setTemp.m_lCONTATORE_EESAMI = _ttol(m_ctrlListGridSchemiAnatomiciAggiunto.GetItemText(iRow, _SAA_COL_CONTATORE_EESAMI));
				setTemp.m_lID_SCHEMI_ANATOMICI = _ttol(m_ctrlListGridSchemiAnatomiciAggiunto.GetItemText(iRow, _SAA_COL_ID_SCHEMI_ANATOMICI));
				setTemp.m_sDESCRIZIONE = m_ctrlListGridSchemiAnatomiciAggiunto.GetItemText(iRow, _SAA_COL_DESCRIZIONE);
				setTemp.m_lSTATO = ConvertSchemiAnatomiciAggiuntoStatoToLong(m_ctrlListGridSchemiAnatomiciAggiunto.GetItemText(iRow, _SAA_COL_STATO));

				bSaved = setTemp.UpdateRecordset(_STRLOG_0007);

				// Update new ID in GRID
				lCONTATORE = setTemp.GetLastAdd();
				CString sAux;
				sAux.Format("%li", lCONTATORE);
				m_ctrlListGridSchemiAnatomiciAggiunto.SetItemData(iRow, lCONTATORE);
				m_ctrlListGridSchemiAnatomiciAggiunto.SetItemText(iRow, _SAA_COL_CONTATORE, sAux);

				setTemp.CloseRecordset(_STRLOG_0007);
			}
		}
		if (sAcao == _DBCTRL_ALTERED || sAcao == _DBCTRL_DELETED)
		{
			CString strFilter;
			strFilter.Format("CONTATORE=%li", lCONTATORE);

			setTemp.SetOpenFilter(strFilter);

			if (setTemp.OpenRecordset(_STRLOG_0007))
			{
				if (setTemp.IsBOF() && setTemp.IsEOF())
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_ALREADY_DELETED), MB_ICONINFORMATION);
				}
				else
				{
					if (setTemp.EditRecordset(_STRLOG_0007))
					{
						// seta as informações da grid no recordset
						setTemp.m_lCONTATORE = m_ctrlListGridSchemiAnatomiciAggiunto.GetItemData(iRow);
						setTemp.m_lCONTATORE_EESAMI = _ttol(m_ctrlListGridSchemiAnatomiciAggiunto.GetItemText(iRow, _SAA_COL_CONTATORE_EESAMI));
						setTemp.m_lID_SCHEMI_ANATOMICI = _ttol(m_ctrlListGridSchemiAnatomiciAggiunto.GetItemText(iRow, _SAA_COL_ID_SCHEMI_ANATOMICI));
						setTemp.m_sDESCRIZIONE = m_ctrlListGridSchemiAnatomiciAggiunto.GetItemText(iRow, _SAA_COL_DESCRIZIONE);
						setTemp.m_lSTATO = ConvertSchemiAnatomiciAggiuntoStatoToLong(m_ctrlListGridSchemiAnatomiciAggiunto.GetItemText(iRow, _SAA_COL_STATO));

						setTemp.SetFieldDirty(NULL, TRUE);
						setTemp.SetFieldDirty(&setTemp.m_lCONTATORE, FALSE);
						if (sAcao == _DBCTRL_DELETED)
						{
							// TODO: APAGAR OS RECS FILHOS (ETICHETTE - LABELS)
							//ASSERT(FALSE);
							bSaved = setTemp.DeleteRecordset(_STRLOG_0007);
						}
						if (sAcao == _DBCTRL_ALTERED)
						{
							bSaved = setTemp.UpdateRecordset(_STRLOG_0007);
						}
					}
				}
				setTemp.CloseRecordset(_STRLOG_0007);
			}
		}
	}
}

void CSchemiAnatomiciAggiuntoDynForm::OnNMRClickListSaa(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	// Habilita edicao das celulas do grid
	int iRowSelectedIndex = pNMItemActivate->iItem;
	int iColSelectedIndex = pNMItemActivate->iSubItem;

	POSITION pos = m_ctrlListGridSchemiAnatomiciAggiunto.GetFirstSelectedItemPosition();
	if (pos != NULL && iColSelectedIndex == _SAA_COL_DESCRIZIONE)
	{
		CRect rect;
		m_ctrlListGridSchemiAnatomiciAggiunto.SetSubItemEdit(iRowSelectedIndex, iColSelectedIndex, FALSE, 255);
		m_ctrlListGridSchemiAnatomiciAggiunto.GetSubItemRect(iRowSelectedIndex, iColSelectedIndex, LVIR_LABEL, rect);
		m_ctrlListGridSchemiAnatomiciAggiunto.PostMessage(WM_LBUTTONDOWN, 0, MAKELPARAM((rect.right + rect.left) / 2, (rect.bottom + rect.top) / 2));

		// CONTROL COLUMN
		ListGridSetDBControl(&m_ctrlListGridSchemiAnatomiciAggiunto, iRowSelectedIndex, _DBCTRL_ALTERED);
		ListGridSetRowColor(&m_ctrlListGridSchemiAnatomiciAggiunto, iRowSelectedIndex);
	}

	*pResult = 0;
}


void CSchemiAnatomiciAggiuntoDynForm::OnBnClickedHlp()
{
	// HELP DA TELA
	CString auxMsg;
	auxMsg.Format("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s",
		"INCLUSÃO DE ESQUEMAS ANATÔMICOS AO EXAME:",
		"\nNA TABELA (GRID) ESQUEMAS ANATÔMICOS DISPONÍVEIS:",
		"1) Clique do Botão ESQUERDO do Mouse para selecionar o esquema anatômico desejado;",
		"2) Clique Duplo do Botão ESQUERDO do Mouse para adicionar ao exame o esquema anatômico selecionado;",
		"\nNA TABELA (GRID) ESQUEMAS ANATÔMICOS JÁ ADICIONADOS AO EXAME:",
		"1) Clique do Botão ESQUERDO do Mouse para selecionar o esquema anatômico a editar;",
		"2) Clique Duplo do Botão ESQUERDO do Mouse para editar a IMAGEM do esquema anatômico selecionado;",
		"3) Clique Duplo do Botão DIREITO do Mouse (na célula DESCRIÇÃO) para alterar/editar a descrição do esquema anatômico selecionado."
		);
	theApp.AfxMessageBoxEndo(auxMsg);
}

