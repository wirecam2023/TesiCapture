// -------------------------------------------------------------------------------------------------------------------------
// Marvel Carvalho - BUG 4308 Esquemas Anatomicos Fleury
// -------------------------------------------------------------------------------------------------------------------------
// DONE: 01) MARVEL DEBUG - necessário colocar em IMPIANTO o caminho padrão onde ficam as imagens dos esquemas anatomicos.atual: dlgFile.GetOFN().lpstrInitialDir = _T("C:\\TESI\\IMM\\AnatomicalScheme");
//
// DONE: 02) MARVEL DEBUG - necessário ajustar a largura das colunas dos grids E esconder as colunas indesejadas
// CAMEditComboListCtrl m_ctrlListGridSchemiAnatomici;           // Binded to [SCHEMI_ANATOMICI]
// CAMEditComboListCtrl m_ctrlListGridSchemiAnatomiciEtichette;  // Binded to [SCHEMI_ANATOMICI_ETICHETTE]
//
// DONE: 03) MARVEL DEBUG - necessário desenvolver o editar das celulas do grid ao duplo clique
// CAMEditComboListCtrl m_ctrlListGridSchemiAnatomici;           // Binded to [SCHEMI_ANATOMICI]
// CAMEditComboListCtrl m_ctrlListGridSchemiAnatomiciEtichette;  // Binded to [SCHEMI_ANATOMICI_ETICHETTE]
// void CSchemiAnatomiciRecordDlg::OnNMDblclkListSchemiAnatomici(NMHDR *pNMHDR, LRESULT *pResult)
// void CSchemiAnatomiciRecordDlg::OnNMDblclkListSchemiAnatomiciEtichette(NMHDR *pNMHDR, LRESULT *pResult)
//
// DONE: 06) MARVEL DEBUG - quando adicionado um novo esquema(id == -1), ao selecioná-lo o grid de labels deve ser apresentado vazio
// void CSchemiAnatomiciRecordDlg::OnNMClickListSchemiAnatomici(NMHDR *pNMHDR, LRESULT *pResult)
//
// DONE: 08) MARVEL DEBUG - implementar as validações "deseja salvar as alterações feitas?" ao sair, ao mudar seleção do grid do esquema se houver alteração nas labels
//
// -------------------------------------------------------------------------------------------------------------------------
//
// TODO: 04) MARVEL DEBUG - desenvolver a funcionalidade CLONAR
// ON_BN_CLICKED(IDC_CLONE, &CSchemiAnatomiciRecordDlg::OnBnClickedClone)
//
// TODO: 05) MARVEL DEBUG - relativo ao tamanho da imagem apresentada e os pontos refs das labels
// a) definir onde a posição(0, 0; tamanho; altura) da imagem que está sendo apresentada
// b) tomar em consideração ao zoom_factor
// c) o(0, 0; tamanho; altura da label)
// d) guardar em label o(cse, cid) correspondentes ao tamanho original da imagem
//
// TODO: 07) MARVEL DEBUG - depois de clicar no botão salvar o grid de esquemas perde o foco, NÃO FUNCIONOU mesmo dando o comando de focus + selecionar a linha do grid perde o highlight azul
// usando :
// CAMEditComboListCtrl m_ctrlListGridSchemiAnatomici;           // Binded to [SCHEMI_ANATOMICI]
// CAMEditComboListCtrl m_ctrlListGridSchemiAnatomiciEtichette;  // Binded to [SCHEMI_ANATOMICI_ETICHETTE]
// antes estava funcionando com o componente:
// CListSortableCtrl funcionava eu havia implementado o ListGridSetItemFocus() nele e funcionava.
// não temos o .cpp de CAMEditComboListCtrl
// implementei : void CSchemiAnatomiciRecordDlg::ListGridSetItemFocus(CAMEditComboListCtrl* p_pThisList, int iRow)
// com o mesmo objetivo mas não consegui fazer funcionar igual
//
// TODO: 09) MARVEL DEBUG - pintar as linhas das grids : adicionadas, alteradas, deletadas de cores diferentes para sinaliza alterações não salvas - FIZ mas NÃO funcionou!
//
// TODO: 10) MARVEL DEBUG - colocar as linhas adicionadas(botão novo) no final da lista, hoje está ficando no início
//
// TODO: 11) MARVEL DEBUG - ver pq a reordenação nos grids está invertida, tive que colocar "ID DESC", "DESCRIZIONE DESC" no recordset como conserto paliativo
//
// TODO: 12) MARVEL DEBUG - melhorar  deleção de esquemas : a) pedir confirmação via msg; b) deletar em cascata as labels filhas se houver
//
// TODO: 13) MARVEL DEBUG - melhorar  deleção de labels : a) pedir confirmação via msg;
//
// TODO: 14) MARVEL DEBUG - fazer um combo dentro da celula para escolher a sigla do exame CVistaExtPrestazioniSet

#include "stdafx.h"
#include "Endox.h"
#include "SchemiAnatomiciRecordDlg.h"

#include <io.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "DLL_Imaging\h\ImgArchive.h"

#include "Bmp.h"
#include "Common.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "EsamiDoc.h"
#include "FileBmp.h"
#include "ImmaginiPuntiSet.h"
#include "LogFileWriter.h"
#include "MmSystem.h"
#include "PuntiSet.h"

#include "TipoEsameSet.h"
#include "UOSet.h"
#include "InputBox.h"

// ORDER OF GRID COLUMNS
// SCHEMI_ANATOMICI
#define _SA_COL_ID_				    0
#define _SA_COL_DESC_				1
#define _SA_COL_UO_				    2
#define _SA_COL_UO_DESC_		    3
#define _SA_COL_SIGLA_EXAME_		4
#define _SA_COL_IMMAGINE_FULLPATH_	5
#define _SA_COL_IMMAGINE_LARGHEZZA_ 6
#define _SA_COL_IMMAGINE_ALTEZZA_   7
#define _SA_COL_ZOOM_FACTOR_	    8
#define _SA_QTT_COL_				9

// SCHEMI_ANATOMICI ETICHETTE
#define _SAE_COL_PAI_	0
#define _SAE_COL_ID_	1
#define _SAE_COL_DESC_	2
#define _SAE_COL_AX_	3
#define _SAE_COL_AY_	4
#define _SAE_COL_BX_	5
#define _SAE_COL_BY_	6
#define _SAE_COL_COLORE_	7
#define _SAE_COL_ZOOM_FACTOR_	    8
#define _SAE_QTT_COL_	9

// CListControl & DB Column of control
#define _DBCTRL_NEW		"NEW"
#define _DBCTRL_SAME	"SAME"
#define _DBCTRL_ALTERED	"ALTERED"
#define _DBCTRL_DELETED	"DELETED"
#define _DBCTRL_FORGET	"FORGET"	// DO NOTHING

#define _SHOW_ TRUE
#define _HIDE_ FALSE

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CSchemiAnatomiciRecordDlg, CDialog)

CSchemiAnatomiciRecordDlg::CSchemiAnatomiciRecordDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CSchemiAnatomiciRecordDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);
	m_pEsamiView = pEsamiView;
	m_pSchemiAnatomiciActual = NULL;
	m_pSchemiAnatomiciEtichetteActual = NULL;

	m_setSchemiAnatomici.SetSortRecord(_T("DESCRIZIONE DESC"));
	m_setSchemiAnatomici.OpenRecordset(_T("CSchemiAnatomiciRecordDlg::CSchemiAnatomiciRecordDlg"));

	m_setSchemiAnatomiciEtichette.SetSortRecord(_T("ID DESC"));
	m_setSchemiAnatomiciEtichette.OpenRecordset(_T("CSchemiAnatomiciRecordDlg::CSchemiAnatomiciRecordDlg"));

	bOnBnClickedShowEtichetteShowOrHide = _HIDE_;

	m_bAlteredSchemi = FALSE;
	m_bAlteredEtichette = FALSE;
}

CSchemiAnatomiciRecordDlg::~CSchemiAnatomiciRecordDlg(void)
{
	m_setSchemiAnatomici.CloseRecordset(_T("CSchemiAnatomiciRecordDlg::~CSchemiAnatomiciRecordDlg"));
	m_setSchemiAnatomiciEtichette.CloseRecordset(_T("CSchemiAnatomiciRecordDlg::~CSchemiAnatomiciRecordDlg"));
}

void CSchemiAnatomiciRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	if (!m_setSchemiAnatomici.IsOpen())
	{
		return;
	}

	CDialog::DoDataExchange(pDX);

	//DDX_Text(pDX, IDC_COMMENTO, m_setSchemiAnatomici.m_sDescrizione);
	//DDX_Control(pDX, IDC_SAVE, m_ctrlButtonSAVE);
	DDX_Control(pDX, IDC_SHOW_ETICHETTE, m_ctrlButtonSHOW);
	
	DDX_Control(pDX, IDC_LIST_SCHEMI_ANATOMICI, m_ctrlListGridSchemiAnatomici);
	DDX_Control(pDX, IDC_LIST_SCHEMI_ANATOMICI_ET, m_ctrlListGridSchemiAnatomiciEtichette);

	// update to the actual [SchemiAnatomici] object from record / database
	m_pSchemiAnatomiciActual = &(m_setSchemiAnatomici.m_pSchemiAnatomici); 
	m_pSchemiAnatomiciEtichetteActual = &(m_setSchemiAnatomiciEtichette.m_pSchemiAnatomiciEtichette);
}


BOOL CSchemiAnatomiciRecordDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	int i;

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	//SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //


	//m_lPaziente = m_pEsamiView->m_pEsamiSet->m_lPaziente;
	//m_lEsame = m_pEsamiView->m_pEsamiSet->m_lContatore;
	//m_pEsamiView->m_pImgManager->SetCurrentIDs(m_lPaziente, m_lEsame);
	//m_bConfirmed = m_pEsamiView->m_pImgManager->IsExamConfirmed(m_strDvdLabel);



	//MoveImageOrg();


	// Configura os CABEÇALHOS das COLUNAS dos GRIDS

	//-----------------------------
	// GRID DOS ESQUEMAS ANATOMICOS
	//-----------------------------
	// ID
	// DESCRIZIONE
	// UO
	// CODICEPRESTAZIONEPREVISTA
	// IMMAGINE_FULLPATH
	// IMMAGINE_LARGHEZZA
	// IMMAG INE_ALTEZZA
	// ZOOM FACTOR
	// DB_CTRL
	i = 0;
	while (m_ctrlListGridSchemiAnatomici.DeleteColumn(0));
	m_ctrlListGridSchemiAnatomici.SetExtendedStyle(m_ctrlListGridSchemiAnatomici.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrlListGridSchemiAnatomici.InsertColumn(i++, "ID", LVCFMT_LEFT, 0);
	m_ctrlListGridSchemiAnatomici.InsertColumn(i++, "DESC", LVCFMT_LEFT, 0);
	m_ctrlListGridSchemiAnatomici.InsertColumn(i++, "UO", LVCFMT_LEFT, 0);
	m_ctrlListGridSchemiAnatomici.InsertColumn(i++, "UO DESC", LVCFMT_LEFT, 0);
	m_ctrlListGridSchemiAnatomici.InsertColumn(i++, "SIGLA", LVCFMT_LEFT, 0); // CODICEPRESTAZIONEPREVISTA
	m_ctrlListGridSchemiAnatomici.InsertColumn(i++, "IMMAGINE_FULLPATH", LVCFMT_LEFT, 0);
	m_ctrlListGridSchemiAnatomici.InsertColumn(i++, "IMMAGINE_LARGHEZZA", LVCFMT_LEFT, 0);
	m_ctrlListGridSchemiAnatomici.InsertColumn(i++, "IMMAGINE_ALTEZZA", LVCFMT_LEFT, 0);
	m_ctrlListGridSchemiAnatomici.InsertColumn(i++, "ZOOM FACTOR", LVCFMT_LEFT, 0);
	m_ctrlListGridSchemiAnatomici.InsertColumn(i++, "CTRL", LVCFMT_LEFT, 0);


	//---------------------------------------------------
	// GRID DAS LABELS ATRELADOS A CADA ESQUEMA ANATOMICO
	//---------------------------------------------------
	// ID_SCHEMI_ANATOMICI
	// ID
	// DESCRIZIONE
	// PUNTO_ALTO_SINISTRA_X
	// PUNTO_ALTO_SINISTRA_Y
	// PUNTO_BASSO_DESTRA_X
	// PUNTO_BASSO_DESTRA_Y
	// ZOOM FACTOR
	// DB_CTRL
	i = 0;
	while (m_ctrlListGridSchemiAnatomiciEtichette.DeleteColumn(0));
	m_ctrlListGridSchemiAnatomiciEtichette.SetExtendedStyle(m_ctrlListGridSchemiAnatomiciEtichette.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctrlListGridSchemiAnatomiciEtichette.InsertColumn(i++, "PAI", LVCFMT_LEFT, 0); // ... theApp.GetMessageString(IDS_GEP_LIST_01)
	m_ctrlListGridSchemiAnatomiciEtichette.InsertColumn(i++, "ID", LVCFMT_LEFT, 0);
	m_ctrlListGridSchemiAnatomiciEtichette.InsertColumn(i++, "DESC", LVCFMT_LEFT, 0);
	m_ctrlListGridSchemiAnatomiciEtichette.InsertColumn(i++, "ax", LVCFMT_LEFT, 0);
	m_ctrlListGridSchemiAnatomiciEtichette.InsertColumn(i++, "ay", LVCFMT_LEFT, 0);
	m_ctrlListGridSchemiAnatomiciEtichette.InsertColumn(i++, "bx", LVCFMT_LEFT, 0);
	m_ctrlListGridSchemiAnatomiciEtichette.InsertColumn(i++, "by", LVCFMT_LEFT, 0);
	m_ctrlListGridSchemiAnatomiciEtichette.InsertColumn(i++, "COR", LVCFMT_LEFT, 0);
	m_ctrlListGridSchemiAnatomiciEtichette.InsertColumn(i++, "ZOOM FACTOR", LVCFMT_LEFT, 0);
	m_ctrlListGridSchemiAnatomiciEtichette.InsertColumn(i++, "CTRL", LVCFMT_LEFT, 0);

	// to translate if needed
	// ... theApp.GetMessageString(IDS_GEP_LIST_01)

	ListGridSchemiAnatomiciRiempi(0);  //tenta colocar a linha 0 como default
	OnBnClickedSave(); // usado para ajustar as larguras das colunas dos grids

	//theApp.LocalizeDialog(this, CSchemiAnatomiciRecordDlg::IDD, "SchemiAnatomiciRecordDlg");

	return TRUE;
}

BEGIN_MESSAGE_MAP(CSchemiAnatomiciRecordDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()

	//ON_REGISTERED_MESSAGE(MSG_SELECT_BMP, OnSelectBmp)

	ON_BN_CLICKED(IDC_IMPORT_IMG, &CSchemiAnatomiciRecordDlg::ImageOpenDlgImport)
	ON_BN_CLICKED(IDC_SAVE, &CSchemiAnatomiciRecordDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDCLOSE, &CSchemiAnatomiciRecordDlg::OnBnClickedClose)

	ON_NOTIFY(NM_CLICK, IDC_LIST_SCHEMI_ANATOMICI, &CSchemiAnatomiciRecordDlg::OnNMClickListSchemiAnatomici)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SCHEMI_ANATOMICI, &CSchemiAnatomiciRecordDlg::OnNMDblclkListSchemiAnatomici)

	ON_NOTIFY(NM_CLICK, IDC_LIST_SCHEMI_ANATOMICI_ET, &CSchemiAnatomiciRecordDlg::OnNMClickListSchemiAnatomiciEtichette)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SCHEMI_ANATOMICI_ET, &CSchemiAnatomiciRecordDlg::OnNMDblclkListSchemiAnatomiciEtichette)
	
	ON_BN_CLICKED(IDC_DEL_ETICHETTE, &CSchemiAnatomiciRecordDlg::OnBnClickedDelEtichette)
	ON_BN_CLICKED(IDC_SHOW_ETICHETTE, &CSchemiAnatomiciRecordDlg::OnBnClickedShowEtichette)
	ON_BN_CLICKED(IDC_DEL, &CSchemiAnatomiciRecordDlg::OnBnClickedDel)
	ON_BN_CLICKED(IDC_NEW, &CSchemiAnatomiciRecordDlg::OnBnClickedNew)
	ON_BN_CLICKED(IDC_CLONE, &CSchemiAnatomiciRecordDlg::OnBnClickedClone)
//	ON_BN_CLICKED(IDC_EDIT, &CSchemiAnatomiciRecordDlg::OnBnClickedEdit)
//ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_SCHEMI_ANATOMICI_ET, &CSchemiAnatomiciRecordDlg::OnLvnKeydownListSchemiAnatomiciEt)
	ON_BN_CLICKED(IDC_HLP, &CSchemiAnatomiciRecordDlg::OnBnClickedHlp)
END_MESSAGE_MAP()



BOOL CSchemiAnatomiciRecordDlg::ImageShow(CString p_sFullPathImage)
{
	if (m_Dib.IsValidDib())
	{
		m_Dib.ReleaseContents();
		m_Dib.Detach();
	}

	if (p_sFullPathImage == "")
		return FALSE;

	if (!FILEEXISTS_S(p_sFullPathImage))
	{
		theApp.AfxMessageBoxEndo(_T("Erro arquivo inexistente [") + p_sFullPathImage + _T("]"));
		return FALSE;
	}

	BOOL bDoneOk = FALSE;

	do
	{
		bDoneOk = ImportImageFromDisk(p_sFullPathImage, &m_Dib);

		GetDlgItem(IDC_FRAME)->GetWindowRect(m_RectToShowImage);

		if (!bDoneOk && theApp.AfxMessageBoxEndo(_T("Erro ao abrir a imagem [") + p_sFullPathImage + _T("]"), MB_RETRYCANCEL | MB_ICONEXCLAMATION) == IDCANCEL)
		{
			return FALSE;
		}
	} while (!bDoneOk);

	return TRUE;
}


BOOL CSchemiAnatomiciRecordDlg::ImportImageFromDisk(CString p_sFullPathImg, CDib* p_Dib)
{
	if (m_Dib.IsValidDib())
	{
		m_Dib.ReleaseContents();
		m_Dib.Detach();
	}

	if (!m_pEsamiView) {
		ASSERT(m_pEsamiView != NULL);
		//ASSERT(p_FrameRect != NULL);
		return FALSE;
	}

	BOOL bImportedSomething = FALSE;

	// calcolo le dimensioni di tutti i files //
	double dFileSize = 0;
	WIN32_FIND_DATA dataFile;
	HANDLE hFile = FindFirstFile(p_sFullPathImg, &dataFile);
	CString strFileExt(p_sFullPathImg);

	if (strFileExt.GetLength() > 3)
	{
		strFileExt = strFileExt.Right(3);
		if ((strFileExt.CompareNoCase("bmp") == 0))
			dFileSize += (double)((((LONGLONG)dataFile.nFileSizeHigh) << 32) + (LONGLONG)dataFile.nFileSizeLow) / (1024.0f * 1024.0f);
	}

	HBITMAP hBit;
	if (m_pEsamiView->m_pImgManager->LoadLocalImageEx(p_sFullPathImg, &hBit) > 0)
	{
		if (hBit != INVALID_HANDLE_VALUE)
		{
			bImportedSomething = m_Dib.Attach(CDib::BitmapToDIB(hBit, NULL), TRUE);
		}
	}
	DeleteObject(hBit);

	if (!bImportedSomething)
	{
		m_Dib.ReleaseContents();
		m_Dib.Detach();
	}

	if (bImportedSomething)
	{
		*p_Dib = m_Dib;
		return TRUE;
	}

	return FALSE;
}
void CSchemiAnatomiciRecordDlg::ImageOpenDlgImport()
{
	if (m_pSchemiAnatomiciActual == NULL || m_ctrlListGridSchemiAnatomici.GetSelectedCount()==0)
	{
		theApp.AfxMessageBoxEndo(_T("necessário selecionar o esquema anatômico primeiro"));
		//ASSERT(m_pSchemiAnatomiciActual == NULL);
		return;
	}
	
	//CStringList ArraySelected;
	TCHAR szFilters[] = _T("Bitmap Files (*.bmp)|*.bmp|All Files (*.*)|*.*||");
	CFileDialog dlgFile(TRUE, _T("bmp"), _T("*.bmp"), OFN_READONLY | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, szFilters, this, 0, FALSE); // OFN_ALLOWMULTISELECT

	CString strFileDialog;
	int iMaxFiles = 1;
	int iBuffSize = (iMaxFiles * (MAX_PATH + 1)) + 1;

	dlgFile.GetOFN().lpstrFile = strFileDialog.GetBuffer(iBuffSize);
	dlgFile.GetOFN().nMaxFile = iBuffSize;

	//dlgFile.GetOFN().lpstrInitialDir = _T("C:\\TESI\\IMM\\AnatomicalScheme");
	dlgFile.GetOFN().lpstrInitialDir = _T(theApp.m_sPercorsoSCHEMI_ANATOMICI);

	BOOL bDoneOk = FALSE;

	if (dlgFile.DoModal() == IDOK)
	{
		bDoneOk = ImageShow(dlgFile.GetPathName());
	}

	if (bDoneOk)
	{
		// Atualiza as informações do GRID de Esquemas Anatômicos
		int iRowNum = m_ctrlListGridSchemiAnatomici.GetSelectionMark();
		CString sImgHeight, sImgWidth, sZoomFactor;
		sImgHeight.Format("%ld", m_Dib.Height());
		sImgWidth.Format ("%ld", m_Dib.Width() );

		//double dZoomFactor = m_setSchemiAnatomici.m_dZoom_Factor = ImageCalcZoomFactor(&m_RectToShowImage, &m_Dib);
		sZoomFactor.Format("%.18f", m_pSchemiAnatomiciActual->m_dZoom_Factor);

		m_ctrlListGridSchemiAnatomici.SetItemText(iRowNum, _SA_COL_IMMAGINE_FULLPATH_, dlgFile.GetPathName());
		m_ctrlListGridSchemiAnatomici.SetItemText(iRowNum, _SA_COL_IMMAGINE_ALTEZZA_, sImgHeight);
		m_ctrlListGridSchemiAnatomici.SetItemText(iRowNum, _SA_COL_IMMAGINE_LARGHEZZA_, sImgWidth);
		m_ctrlListGridSchemiAnatomici.SetItemText(iRowNum, _SA_COL_ZOOM_FACTOR_, sZoomFactor);

		// CONTROL COLUMN
		ListGridSetDBControl(&m_ctrlListGridSchemiAnatomici, iRowNum, _DBCTRL_ALTERED);

		RedrawWindow();
	}
}

// Add actual object m_setSchemiAnatomici to m_ctrlListGridSchemiAnatomici
int CSchemiAnatomiciRecordDlg::ListGridSchemiAnatomiciAddThisRegAsNewRow()
{
	int nRowNumber = 0;

	CString sAux[_SA_QTT_COL_];
	sAux[_SA_COL_ID_].Format("%ld", m_setSchemiAnatomici.m_lID);
	sAux[_SA_COL_DESC_] = m_setSchemiAnatomici.m_sDescrizione.Trim();
	sAux[_SA_COL_UO_].Format("%ld", m_setSchemiAnatomici.m_lUO);
	sAux[_SA_COL_UO_DESC_] = CUOSet().GetDescrizione(m_setSchemiAnatomici.m_lUO).Trim();
	sAux[_SA_COL_SIGLA_EXAME_] = m_setSchemiAnatomici.m_sCodicePrestazionePrevista.Trim();
	sAux[_SA_COL_IMMAGINE_FULLPATH_] = m_setSchemiAnatomici.m_sImmagine_FullPath.Trim();
	sAux[_SA_COL_IMMAGINE_LARGHEZZA_].Format("%ld", m_setSchemiAnatomici.m_lImmagine_Larghezza);
	sAux[_SA_COL_IMMAGINE_ALTEZZA_].Format("%ld", m_setSchemiAnatomici.m_lImmagine_Altezza);
	sAux[_SA_COL_ZOOM_FACTOR_].Format("%.18f", m_setSchemiAnatomici.m_dZoom_Factor);

	// ADD new ROW and data of the COLUMNS
	nRowNumber = m_ctrlListGridSchemiAnatomici.InsertItem(0, sAux[0]);					// insert a new ROW with the first COLUMN
	m_ctrlListGridSchemiAnatomici.SetItemData(nRowNumber, m_setSchemiAnatomici.m_lID);	// set ID of the ROW
	for (int c = 1; c < _SA_QTT_COL_; c++)
	{
		m_ctrlListGridSchemiAnatomici.SetItemText(nRowNumber, c, sAux[c]);	// set TEXT of the each COLUMN
	}
	// CONTROL COLUMN
	//m_ctrlListGridSchemiAnatomici.SetItemText(nRowNumber, _SA_QTT_COL_, _DBCTRL_SAME);	// set TEXT of the each COLUMN

	return nRowNumber;
}

long CSchemiAnatomiciRecordDlg::ListGridSchemiAnatomiciRiempi(int p_iActualRow)
{
	BeginWaitCursor();
	m_ctrlListGridSchemiAnatomici.SetRedraw(FALSE);
	
	int iActualRow;
	if (p_iActualRow >= 0)
	{
		iActualRow = p_iActualRow;
	}
	else
	{
		iActualRow = m_ctrlListGridSchemiAnatomici.GetSelectionMark();	// Retrieves the item with the selection mark, or -1 if none.
	}
	

	long lActualID = ListGridSchemiAnatomiciGetIDSelected();

	m_ctrlListGridSchemiAnatomici.DeleteAllItems();

	if (m_setSchemiAnatomici.IsOpen())
	{
		//m_ctrlListGridSchemiAnatomici.SetSortColumn(1);
		//m_ctrlListGridSchemiAnatomici.SetSortColumn(0);

		//m_setSchemiAnatomici.SetSortRecord("");

		// update actual Schemi
		BOOL bError = TRUE;
		if (m_setSchemiAnatomici.RecordsetReOpen(bError, "", "DESCRIZIONE DESC", "CSchemiAnatomiciRecordDlg::OnNMClickListSchemiAnatomici"))
		{
			while (!m_setSchemiAnatomici.IsEOF())
			{
				ListGridSchemiAnatomiciAddThisRegAsNewRow();
				m_setSchemiAnatomici.MoveNext();
			}
		}

		// tenta selecionar a mesma linha/id anterior, se possível
		int iTotRows = m_ctrlListGridSchemiAnatomici.GetItemCount();
		if (iActualRow >= 0 && iActualRow < iTotRows)
		{
			ListGridSetItemFocus(&m_ctrlListGridSchemiAnatomici,iActualRow);
			long lActualIDAfter = m_ctrlListGridSchemiAnatomici.GetItemData(iActualRow);

			// se atual foi deletado, pega outro que ficou no lugar como atual
			ListGridSchemiAnatomiciUpdateActual(lActualIDAfter);
			lActualID = lActualIDAfter;
		}
		else
		{
			// se falhou na tentativa de a mesma linha/id anterior
			// só restaura o anterior
			ListGridSchemiAnatomiciUpdateActual(lActualID);
		}
	}

	// ajusta largura das colunas
	//for (int i = 0; i <= _SA_QTT_COL_; i++)
	//	m_ctrlListGridSchemiAnatomici.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlListGridSchemiAnatomici.SetColumnWidth(_SA_COL_ID_			   , 0); 
	m_ctrlListGridSchemiAnatomici.SetColumnWidth(_SA_COL_DESC_			   , LVSCW_AUTOSIZE);
	m_ctrlListGridSchemiAnatomici.SetColumnWidth(_SA_COL_UO_			   , LVSCW_AUTOSIZE);
	m_ctrlListGridSchemiAnatomici.SetColumnWidth(_SA_COL_UO_DESC_		   , LVSCW_AUTOSIZE);
	m_ctrlListGridSchemiAnatomici.SetColumnWidth(_SA_COL_SIGLA_EXAME_	   , LVSCW_AUTOSIZE);
	m_ctrlListGridSchemiAnatomici.SetColumnWidth(_SA_COL_IMMAGINE_FULLPATH_, LVSCW_AUTOSIZE);
	m_ctrlListGridSchemiAnatomici.SetColumnWidth(_SA_COL_IMMAGINE_LARGHEZZA_ , 0);
	m_ctrlListGridSchemiAnatomici.SetColumnWidth(_SA_COL_IMMAGINE_ALTEZZA_ , 0);
	m_ctrlListGridSchemiAnatomici.SetColumnWidth(_SA_COL_ZOOM_FACTOR_	   , 0);
	m_ctrlListGridSchemiAnatomici.SetColumnWidth(_SA_QTT_COL_			   , 0);  // DB_CTRL

	m_ctrlListGridSchemiAnatomici.SetRedraw(TRUE);
	EndWaitCursor();

	return lActualID;
}

// Add actual object m_setSchemiAnatomici to m_ctrlListGridSchemiAnatomici
int CSchemiAnatomiciRecordDlg::ListGridSchemiAnatomiciEtichetteAddThisRegAsNewRow()
{
	int nRowNumber = 0;

	CString sAux[_SAE_QTT_COL_];
	sAux[_SAE_COL_PAI_].Format("%ld", m_setSchemiAnatomiciEtichette.m_lID_Schemi_Anatomici);
	sAux[_SAE_COL_ID_].Format("%ld", m_setSchemiAnatomiciEtichette.m_lID);
	sAux[_SAE_COL_DESC_] = m_setSchemiAnatomiciEtichette.m_sDescrizione.Trim();
	sAux[_SAE_COL_AX_].Format("%ld", m_setSchemiAnatomiciEtichette.m_lPunto_Alto_Sinistra_X);
	sAux[_SAE_COL_AY_].Format("%ld", m_setSchemiAnatomiciEtichette.m_lPunto_Alto_Sinistra_Y);
	sAux[_SAE_COL_BX_].Format("%ld", m_setSchemiAnatomiciEtichette.m_lPunto_Basso_Destra_X);
	sAux[_SAE_COL_BY_].Format("%ld", m_setSchemiAnatomiciEtichette.m_lPunto_Basso_Destra_Y);
	sAux[_SAE_COL_COLORE_].Format("%ld", m_setSchemiAnatomiciEtichette.m_lColore);
	sAux[_SAE_COL_ZOOM_FACTOR_].Format("%.18f", m_setSchemiAnatomiciEtichette.m_dZoom_Factor);

	// ADD new ROW and data of the COLUMNS
	nRowNumber = m_ctrlListGridSchemiAnatomiciEtichette.InsertItem(0, sAux[0]);								// insert a new ROW with the first COLUMN
	m_ctrlListGridSchemiAnatomiciEtichette.SetItemData(nRowNumber, m_setSchemiAnatomiciEtichette.m_lID);	// set ID of the ROW
	int c;
	for (c = 1; c < _SAE_QTT_COL_; c++)
	{
		m_ctrlListGridSchemiAnatomiciEtichette.SetItemText(nRowNumber, c, sAux[c]);	// set TEXT of the each COLUMN
	}
	// CONTROL COLUMN
	m_ctrlListGridSchemiAnatomiciEtichette.SetItemText(nRowNumber, c, _DBCTRL_SAME);	// set TEXT of the each COLUMN

	return nRowNumber;
}

void CSchemiAnatomiciRecordDlg::ListGridSetDBControl(CAMEditComboListCtrl* p_pThisList, int p_iRow, CString p_strDBControl)
{
	int iDBCtrlCol = ListGridGetColumnsCount(p_pThisList) - 1;		// this is the last one column, the text of this is used for control

	// if its new, do not change
	if (p_pThisList->GetItemText(p_iRow, iDBCtrlCol) == _DBCTRL_NEW && p_strDBControl == _DBCTRL_ALTERED)
		return;

	if (p_pThisList->GetItemText(p_iRow, iDBCtrlCol) == _DBCTRL_NEW && p_strDBControl == _DBCTRL_DELETED)
	{
		p_pThisList->SetItemText(p_iRow, iDBCtrlCol, _DBCTRL_FORGET);	// set TEXT of the CONTROL COLUMN
		return;
	}
	p_pThisList->SetItemText(p_iRow, iDBCtrlCol, p_strDBControl);	// set TEXT of the CONTROL COLUMN
}

long CSchemiAnatomiciRecordDlg::ListGridSchemiAnatomiciEtichetteRiempi(long p_lID)
{
	m_ctrlListGridSchemiAnatomiciEtichette.DeleteAllItems();

	if (!m_setSchemiAnatomici.IsOpen() || p_lID <=0)
	{
		m_ctrlListGridSchemiAnatomiciEtichette.SetRedraw(TRUE);
		return -1;
	}

	int iActualRow = m_ctrlListGridSchemiAnatomiciEtichette.GetSelectionMark();	// Retrieves the item with the selection mark, or -1 if none.
	long lActualID = ListGridSchemiAnatomiciEtichetteGetIDSelected();

	BeginWaitCursor();
	m_ctrlListGridSchemiAnatomiciEtichette.SetRedraw(FALSE);
	//m_ctrlListGridSchemiAnatomiciEtichette.SetSortColumn(0);

	CString sFilter;
	sFilter.Format("ID_SCHEMI_ANATOMICI=%li", p_lID);

	// update actual SchemiEtichette
	BOOL bError = TRUE;
	if (m_setSchemiAnatomiciEtichette.RecordsetReOpen(bError, sFilter, "ID DESC", "CSchemiAnatomiciRecordDlg::ListGridSchemiAnatomiciEtichetteRiempi"))
	{
		while (!m_setSchemiAnatomiciEtichette.IsEOF())
		{
			ListGridSchemiAnatomiciEtichetteAddThisRegAsNewRow();
			m_setSchemiAnatomiciEtichette.MoveNext();
		}
	}

	// tenta selecionar a mesma linha/id anterior, se possível
	int iTotRows = m_ctrlListGridSchemiAnatomiciEtichette.GetItemCount();
	if (iActualRow >= 0 && iActualRow < iTotRows)
	{
		ListGridSetItemFocus(&m_ctrlListGridSchemiAnatomiciEtichette,iActualRow);
		long lActualIDAfter = m_ctrlListGridSchemiAnatomiciEtichette.GetItemData(iActualRow);

		// se atual foi deletado, pega outro que ficou no lugar como atual
		ListGridSchemiAnatomiciEtichetteUpdateActual(lActualIDAfter);
		lActualID = lActualIDAfter;
	}
	else
	{
		// se falhou na tentativa de a mesma linha/id anterior
		// só restaura o anterior
		ListGridSchemiAnatomiciEtichetteUpdateActual(lActualID);
	}

	// normaliza a largura das colunas
	//for (int i = 0; i <= _SAE_QTT_COL_; i++)
	//	m_ctrlListGridSchemiAnatomiciEtichette.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);

	m_ctrlListGridSchemiAnatomiciEtichette.SetColumnWidth(_SAE_COL_PAI_, 0);
	m_ctrlListGridSchemiAnatomiciEtichette.SetColumnWidth(_SAE_COL_ID_, 0);
	m_ctrlListGridSchemiAnatomiciEtichette.SetColumnWidth(_SAE_COL_DESC_, LVSCW_AUTOSIZE_USEHEADER);
	m_ctrlListGridSchemiAnatomiciEtichette.SetColumnWidth(_SAE_COL_AX_, LVSCW_AUTOSIZE);
	m_ctrlListGridSchemiAnatomiciEtichette.SetColumnWidth(_SAE_COL_AY_, LVSCW_AUTOSIZE);
	m_ctrlListGridSchemiAnatomiciEtichette.SetColumnWidth(_SAE_COL_BX_, LVSCW_AUTOSIZE);
	m_ctrlListGridSchemiAnatomiciEtichette.SetColumnWidth(_SAE_COL_BY_, LVSCW_AUTOSIZE);
	m_ctrlListGridSchemiAnatomiciEtichette.SetColumnWidth(_SAE_COL_COLORE_, LVSCW_AUTOSIZE);
	m_ctrlListGridSchemiAnatomiciEtichette.SetColumnWidth(_SAE_COL_ZOOM_FACTOR_, 0);
	m_ctrlListGridSchemiAnatomiciEtichette.SetColumnWidth(_SAE_QTT_COL_, 0);		// DB_CTRL

	m_ctrlListGridSchemiAnatomiciEtichette.SetRedraw(TRUE);
	EndWaitCursor();

	return lActualID;
}




//void CSchemiAnatomiciRecordDlg::ResetVetDiapo(BOOL bReposition)
//{   
//	POSITION pos = m_ImgListOrgani.GetHeadPosition();
//	while(pos != NULL)
//	{
//		DeleteObject(m_ImgListOrgani.GetAt(pos).img.hBmp);
//		m_ImgListOrgani.GetNext(pos);
//	}
//	m_ImgListOrgani.RemoveAll();
//
//	if (bReposition)
//	{
//		m_nMaxDiapo = 0;
//		m_nDiapoPage = -1;
//	}
//}  	
//
//int CSchemiAnatomiciRecordDlg::FillDiapoIndex()
//{   
//	int iReturn;
//	CImgList listImg;
//
//	BeginWaitCursor();
//	m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore);
//
//	DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
//	iReturn = m_pEsamiView->m_pImgManager->GetImgList(&listImg) - 1;
//	if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
//		CLogFileWriter::Get()->WriteLogLine0_ImmRetrieve(timeGetTime() - timeForLog, m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore, iReturn + 1, "CSchemiAnatomiciRecordDlg::FillDiapoIndex");
//
//	m_ImgListOrgani = listImg;
//	CaricaPunti();
//	EndWaitCursor();
//
//	return iReturn;
//}

//void CSchemiAnatomiciRecordDlg::OnPageFirst() 
//{
//    m_nDiapoPage = 0;
//    MoveImageImm();
//}

//void CSchemiAnatomiciRecordDlg::MoveImageImm()
//{
//	if (!m_setSchemiAnatomici.IsOpen())
//	{
//		return;
//	}
//
//	int nBase = m_nDiapoPage * MAX_FOTO_BMP;
//
//	//m_BtnImmFirst.EnableWindow(m_nDiapoPage > 0);
//	//m_BtnImmPrev.EnableWindow(m_nDiapoPage > 0);
//	//m_BtnImmNext.EnableWindow(m_nDiapoPage < (m_nMaxDiapo / MAX_FOTO_BMP));
//	//m_BtnImmLast.EnableWindow(m_nDiapoPage < (m_nMaxDiapo / MAX_FOTO_BMP));
//
//	if (m_pEsamiView->m_pEsamiSet->IsEOF())
//	{
//		for(int i = 0; i < MAX_FOTO_BMP; i++)
//			m_pFileFotoBmp[i]->ResetImage();
//
//		return;	
//	}		
//
//	long lPaziente;
//	long lEsame;
//	CString strDvdLabel;
//	BOOL bConfirmed = m_pEsamiView->m_pImgManager->IsExamConfirmed(strDvdLabel);
//	m_pEsamiView->m_pImgManager->GetCurrentIDs(lPaziente, lEsame);
//	for(int i = 0; i < MAX_FOTO_BMP; i++)
//	{
//		if (nBase + i <= m_nMaxDiapo)
//		{
//			m_pFileFotoBmp[i]->LoadImage(lPaziente, lEsame, &m_ImgListOrgani, nBase + i, bConfirmed, strDvdLabel, CARICA_MINI);
//
//			if (m_pFileFotoBmp[i]->GetPointNumber() == m_nCurSel)
//				m_pFileFotoBmp[i]->SetPointColor(RGB_WHITE, RGB_GRAY_DARK, TRUE);
//			else
//				m_pFileFotoBmp[i]->SetPointColor(RGB_GRAY_DARK, RGB_WHITE, TRUE);
//
//			CFileBmp::ReselectBmp(m_pFileFotoBmp[i], FALSE);
//		}
//		else
//		{
//			m_pFileFotoBmp[i]->ResetImage();
//		}
//	}
//}
//
//void CSchemiAnatomiciRecordDlg::RequeryPage() 
//{
//    if (m_nDiapoPage < 0)
//	   m_nDiapoPage = 0;
//	if (m_nDiapoPage > (m_nMaxDiapo / MAX_FOTO_BMP))
//		m_nDiapoPage = m_nMaxDiapo / MAX_FOTO_BMP;
//	MoveImageImm();
//}


//void CSchemiAnatomiciRecordDlg::AlbumRedraw()
//{
//	for(int i = 0; i < MAX_FOTO_BMP; i++)
//		m_pFileFotoBmp[i]->AutoRedraw();
//}

void CSchemiAnatomiciRecordDlg::OnCancel() 
{
	//if (m_ctrlListImage.IsWindowVisible())		CEndoxResizableDlg::OnCancel();
}

void CSchemiAnatomiciRecordDlg::OnOK() 
{
	//if (!m_ctrlListImage.IsWindowVisible())
	{
		//SalvaPunti();
		CDialog::OnOK();
	}
}


//void CSchemiAnatomiciRecordDlg::RiempiListaImmagini()
//{
//	if (!m_setSchemiAnatomici.IsOpen())
//	{
//		return;
//	}
//
//	int i = 0;
//
//	if ((m_setSchemiAnatomici.IsBOF() == FALSE) && (m_setSchemiAnatomici.IsEOF() == FALSE))
//	{
//		m_setSchemiAnatomici.MoveFirst();
//		while(m_setSchemiAnatomici.IsEOF() == FALSE)
//			m_setSchemiAnatomici.MoveNext();
//
//		//m_ctrlListImage.DeleteAllItems(); // Sandro - 18/03/2010 //
//		m_listImage.SetImageCount(m_setSchemiAnatomici.GetRecordCount());
//
//		m_setSchemiAnatomici.MoveFirst();
//		while(m_setSchemiAnatomici.IsEOF() == FALSE)
//		{
//			char szPathImm[MAX_PATH];
//			char szPathMin[MAX_PATH];
//			if (CImgArchive(&theApp.m_dbEndox).GetArchivePrimary(szPathImm, szPathMin, MAX_PATH))
//			{
//				CString strOrganFile;
//				strOrganFile.Format("%s\\Organ\\%06li.org", szPathImm /*theApp.m_sPathImageHD*/, m_setSchemiAnatomici.m_lID);
//
//				HBITMAP hBit;
//				if (m_pEsamiView->m_pImgManager->LoadLocalImageEx(strOrganFile, &hBit, NULL, HSIZE_PAL_4, VSIZE_PAL_4) > 0)
//				{
//					if (hBit != INVALID_HANDLE_VALUE)
//					{
//						//m_ctrlListImage.InsertItem(i, m_setSchemiAnatomici.m_sDescrizione, i);
//						m_listImage.Replace(i, CBitmap::FromHandle(hBit), RGB(0, 0, 0));
//					}
//				}
//				DeleteObject(hBit);
//
//				i++;
//				m_setSchemiAnatomici.MoveNext();
//			}
//			else
//			{
//				ASSERT(FALSE);
//			}
//		}
//	}
//}

double CSchemiAnatomiciRecordDlg::ImageCalcZoomFactor(CRect* p_pRectClient, CDib* p_pDib)
{
	double a = (double)p_pRectClient->Width();
	double b = (double)p_pDib->Width();
	double i = (double)p_pRectClient->Height();
	double j = (double)p_pDib->Height();
	double dFactorX = a / b;
	double dFactorY = i / j;
	// update variables
	double x = min(dFactorX, dFactorY);
	return x;
}


void CSchemiAnatomiciRecordDlg::OnPaint() 
{
	if (!m_setSchemiAnatomici.IsOpen())
	{
		return;
	}

	CPaintDC dc(this);

	//if ((m_setSchemiAnatomici.IsBOF() == FALSE) && (m_setSchemiAnatomici.IsEOF() == FALSE))
	{
		
		if (CWnd* pFrame = GetDlgItem(IDC_FRAME))
		{
			CClientDC dcp(pFrame);

			//m_pSchemiAnatomiciActual->RedrawWindow();	// nao funcionou

			
			// calcolo l'area del rect client //
			CRect rectClient;
			GetDlgItem(IDC_FRAME)->GetWindowRect(&rectClient);

			//DrawRetangle(rectClient, RGB_GREEN, 0);

			ScreenToClient(&rectClient);

			//DrawRetangle(rectClient, RGB_RED, 0);

			rectClient.DeflateRect(1, 1);

			// Objeto atual valido significa e linha do grid previamente selecionou uma linha com imagem válida
			if (!m_Dib.IsValidDib() )
			{
				// se le dib non è valida svuoto l'immagine //
	   			CBrush brushNull;
				brushNull.CreateSolidBrush(RGB_BLACK);
				dc.FillRect(rectClient, &brushNull);
				brushNull.DeleteObject();
			}
			else
			{
				// disegno la dib //
				m_RectToShowImage = m_Dib.PaintDIB(&dc, rectClient);
				
				//DrawRetangle(m_RectToShowImage, RGB_BLUE, 0);

				// proporzioni //
				m_pSchemiAnatomiciActual->m_dZoom_Factor = ImageCalcZoomFactor(&m_RectToShowImage, &m_Dib);
 			}

			//CPen penSel(PS_SOLID, 1, RGB_WHITE);
			//CBrush brushSel(RGB_WHITE);
			//CPen penNormal(PS_SOLID, 1, RGB_GRAY_DARK);
			//CBrush brushNormal(RGB_GRAY_DARK);

			//CRect rectFrame;
			//pFrame->GetWindowRect(rectFrame);
			//ScreenToClient(rectFrame);
			//dcp.SetBkMode(TRANSPARENT);

			//int i = 0;
			//POSITION pos = m_lstPunti.GetHeadPosition();
			//while(pos != NULL)
			//{
			//	if (m_lstPunti.GetAt(pos).lIdOrgano == m_setSchemiAnatomici.m_lID)
			//	{
			//		CPen* pOldPen;
			//		CBrush* pOldBrush;
			//		CFont* pOldFont = dcp.SelectObject(&theApp.m_fontBold);
			//		if (i == m_nCurSel)
			//		{
			//			pOldPen = dcp.SelectObject(&penSel);
			//			pOldBrush = dcp.SelectObject(&brushSel);
			//			dcp.SetTextColor(RGB_GRAY_DARK);
			//		}
			//		else
			//		{
			//			pOldPen = dcp.SelectObject(&penNormal);
			//			pOldBrush = dcp.SelectObject(&brushNormal);
			//			dcp.SetTextColor(RGB_WHITE);
			//		}

			//		long lX = m_lstPunti.GetAt(pos).lX;
			//		long lY = m_lstPunti.GetAt(pos).lY;
			//		MillesimiPixel(lX, lY);
			//		lX -= rectFrame.left;
			//		lY -= rectFrame.top;

			//		CRect rectTemp(lX - RAGGIO_PUNTO, lY - RAGGIO_PUNTO, lX + RAGGIO_PUNTO, lY + RAGGIO_PUNTO);

			//		dcp.Ellipse(rectTemp);

			//		CString strTemp;
			//		strTemp.Format("%d", i + 1);
			//		dcp.DrawText(strTemp, rectTemp, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

 		//			dcp.SelectObject(pOldPen);
			//		dcp.SelectObject(pOldBrush);
			//		dcp.SelectObject(pOldFont);
			//	}

			//	m_lstPunti.GetNext(pos);
			//	i++;
			//}

			//penSel.DeleteObject();
			//brushSel.DeleteObject();
			//penNormal.DeleteObject();
			//brushNormal.DeleteObject();
		}
	}
}

//void CSchemiAnatomiciRecordDlg::OnSize(UINT nType, int cx, int cy) 
//{
//	int i;
//
//	CDialog::OnSize(nType, cx, cy);
//
//	for(i = 0; i < MAX_FOTO_BMP; i++)
//		if (m_pFileFotoBmp[i] != NULL)
//			m_pFileFotoBmp[i]->SendMessage(EPM_RESIZE_FORM);
//}


BOOL CSchemiAnatomiciRecordDlg::ListGridSchemiAnatomiciValidaPossibilidadeDeEdicaoDaRowSelecionada()
{
	int iActualRow = m_ctrlListGridSchemiAnatomici.GetSelectionMark();	// Retrieves the item with the selection mark, or -1 if none.

	if (iActualRow < 0)
	{
		theApp.AfxMessageBoxEndo("necessário selecionar um esquema anatômico");
		return FALSE;
	}

	long lID;

	// pega as informações de cada linha do grid e coloca no setTemp
	CString sAcao = ListGridSchemiAnatomiciGetAcao(&lID, iActualRow);
	if (sAcao == _DBCTRL_DELETED)
	{
		theApp.AfxMessageBoxEndo(_T("este esquema anatômico está deletado, escolha outro"));
		return FALSE;
	}
	if (sAcao == _DBCTRL_NEW || sAcao == _DBCTRL_ALTERED)
	{
		theApp.AfxMessageBoxEndo(_T("antes disso... precisa salvar este esquema anatômico"));
		return FALSE;
	}

	CString sFullPathImage = m_ctrlListGridSchemiAnatomici.GetItemText(iActualRow, _SA_COL_IMMAGINE_FULLPATH_);
	if (sFullPathImage.IsEmpty())
	{
		theApp.AfxMessageBoxEndo(_T("antes disso... precisa importar uma imagem"));
		return FALSE;
	}
	return TRUE;
}

void CSchemiAnatomiciRecordDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);

	if (!ListGridSchemiAnatomiciValidaPossibilidadeDeEdicaoDaRowSelecionada())
	{
		return;
	}

	// pega a cor do ponto clicado (canto superior esquerdo + 5)
	m_ColorPoint = GetPixel(dc, point.x+5, point.y+5); // avança pixels a dentro pra pegar uma cor mais consistente

	CRect rectFrame;
	GetDlgItem(IDC_FRAME)->GetWindowRect(rectFrame);	// posição do frame na screen (fuul screen - tela inteira)	//DrawRetangle(rectFrame, RGB_RED);
	ScreenToClient(&rectFrame);						// posição do frame na window continente (anfitriã)			//
	DrawRetangle(rectFrame, RGB_BLUE, 0);
	
	// if point clicked is out of image area, so do nothing
	if (rectFrame.PtInRect(point) == FALSE)
		return;

	CPoint point2 = CPoint(point);

	dc.DPtoLP(&point);
	DrawPoint(point, RGB_BLACK );

	m_ptFirst = point;
	m_bFirstDone = TRUE;
	m_bSecondDone = FALSE;

	return;
}

void CSchemiAnatomiciRecordDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);
	CRect rectFrame;
	GetDlgItem(IDC_FRAME)->GetWindowRect(rectFrame);	// posição do frame na screen (fuul screen - tela inteira)	//DrawRetangle(rectFrame, RGB_RED);
	ScreenToClient(rectFrame);							// posição do frame na window continente (anfitriã)			//DrawRetangle(rectFrame, RGB_BLUE);

	if (rectFrame.PtInRect(point) == FALSE)
		return;

 	long lID_Pai = ListGridSchemiAnatomiciGetIDSelected();

	if (lID_Pai == -1)
		return;

	dc.DPtoLP(&point);

	DrawPoint(point, RGB(255, 0, 0));

	m_ptSecond = point;
	m_bSecondDone = TRUE;

	if (m_bFirstDone && m_bSecondDone)
	{
		CInputBox theInputBox(this);
		CString strLabelId;

		theInputBox.Show("LABEL ID", strLabelId);

		if (!strLabelId.IsEmpty())
		{
			// calcolo l'area del rect client //
			CRect rectClient;
			GetDlgItem(IDC_FRAME)->GetWindowRect(&rectClient);

			CRect auxRect = CRect(m_ptFirst, m_ptSecond);
			auxRect.NormalizeRect(); // desinverte retangulo se necessário

			DrawRetangle(auxRect, RGB_GRAY_LIGHT);

			m_setSchemiAnatomiciEtichette.m_lID_Schemi_Anatomici = lID_Pai;
			m_setSchemiAnatomiciEtichette.m_lID = -1; // new one
			m_setSchemiAnatomiciEtichette.m_sDescrizione = strLabelId;
			m_setSchemiAnatomiciEtichette.m_lPunto_Alto_Sinistra_X = auxRect.TopLeft().x;
			m_setSchemiAnatomiciEtichette.m_lPunto_Alto_Sinistra_Y = auxRect.TopLeft().y;
			m_setSchemiAnatomiciEtichette.m_lPunto_Basso_Destra_X = auxRect.BottomRight().x;
			m_setSchemiAnatomiciEtichette.m_lPunto_Basso_Destra_Y = auxRect.BottomRight().y;
			COLORREF ulColore = m_ColorPoint;	//  RGB(255, 255, 0); // AMARELO
			m_setSchemiAnatomiciEtichette.m_lColore = ulColore;
			m_setSchemiAnatomiciEtichette.m_dZoom_Factor = m_setSchemiAnatomici.m_dZoom_Factor;
			int iNewRow = ListGridSchemiAnatomiciEtichetteAddThisRegAsNewRow();  // insere no grid as informações acima

			// CONTROL COLUMN
			ListGridSetDBControl(&m_ctrlListGridSchemiAnatomiciEtichette, iNewRow, _DBCTRL_NEW);
		}
		m_bAlteredEtichette = TRUE;
	}
	m_bFirstDone = FALSE;
	m_bSecondDone = FALSE;

	return;
}
static const int RADIUS = 2;

void CSchemiAnatomiciRecordDlg::DrawPoint(CPoint p_ptWhere, COLORREF p_color)
{
	CClientDC dc(this);
	int nsave = dc.SaveDC();

	CPen pen(PS_SOLID, 1, p_color);
	CBrush brush(p_color);

	dc.SelectObject(&pen);
	dc.SelectObject(&brush);

	dc.Ellipse(p_ptWhere.x - RADIUS, p_ptWhere.y - RADIUS,
		p_ptWhere.x + RADIUS, p_ptWhere.y + RADIUS);

	dc.RestoreDC(nsave);
}
void CSchemiAnatomiciRecordDlg::DrawRetangle(CRect p_Rect, COLORREF p_color, BOOL p_bGhostColor)
{
	DrawRetangle(p_Rect.TopLeft(), p_Rect.BottomRight(), p_color, p_bGhostColor);
}

void CSchemiAnatomiciRecordDlg::DrawRetangle(CPoint p_ptTopLeft, CPoint p_ptBottomRight, COLORREF p_color, BOOL p_bGhostColor)
{
	CClientDC dc(this);

	int nsave = dc.SaveDC();

	CPen pen(PS_SOLID, 2, p_color);
	CRect rectAux = CRect(p_ptTopLeft, p_ptBottomRight);

	dc.SelectObject(&pen);
	if (p_bGhostColor)
		dc.SetROP2(R2_NOT);

	dc.MoveTo(rectAux.left, rectAux.top);
	dc.LineTo(rectAux.right, rectAux.top);
	dc.LineTo(rectAux.right, rectAux.bottom);
	dc.LineTo(rectAux.left, rectAux.bottom);
	dc.LineTo(rectAux.left, rectAux.top);
	
	dc.RestoreDC(nsave);
}

//void CSchemiAnatomiciRecordDlg::OnMouseMove(UINT nFlags, CPoint point) 
//{
//	return;
//	////-------------------------------------------------------------------
//	BOOL bLeftButtonDown = (nFlags & MK_LBUTTON);
//
//	if (bLeftButtonDown)
//	{
//		CClientDC dc(this);
//		dc.DPtoLP(&point);
//
//		// LBtn mouse pressed - started selecting mode
//		if (!m_bModeSelecting)
//		{
//			m_bModeSelecting = TRUE;
//		}
//
//		// remove the old selecton
//		//DrawRetangle(m_rcTrack.TopLeft, m_rcTrack.BottomRight);
//		m_rcTrack.SetRect(m_ptStartTrack, point);
//		m_rcTrack.NormalizeRect();
//		// draw the new selection
//		//DrawRetangle(m_rcTrack.TopLeft, m_rcTrack.BottomRight);
//	}
//
//	return;
//
//	if ((nFlags & MK_LBUTTON) == 0)
//		return;
//	
//	CRect rectFrame;
//	GetDlgItem(IDC_FRAME)->GetWindowRect(rectFrame);
//	ScreenToClient(rectFrame);
//
//	CRect rectImage = m_RectToShowImage;
//	rectImage.OffsetRect(rectFrame.left, rectFrame.top);
//	rectImage.DeflateRect(0, 0, 1, 1); // (RAGGIO_PUNTO, RAGGIO_PUNTO);
//	
//
//	if (rectImage.PtInRect(point) == TRUE)
//	{
//		// LBtn mouse pressed - started selecting mode
//		if (!m_bModeSelecting)
//		{
//			m_bModeSelecting = TRUE;
//		}
//
//		point.x = max(point.x, rectImage.left   + RAGGIO_PUNTO);
//		point.x = min(point.x, rectImage.right  - RAGGIO_PUNTO);
//		point.y = max(point.y, rectImage.top    + RAGGIO_PUNTO);
//		point.y = min(point.y, rectImage.bottom - RAGGIO_PUNTO);
//
//		// remove the old selecton
//		//DrawSelectionArea();
//		m_rcTrack.SetRect(m_ptStartTrack, point);
//		m_rcTrack.NormalizeRect();
//		// draw the new selection
//		//DrawSelectionArea();
//
//
//		//ModificaPunto(point.x, point.y);
//	}
//
//	//CDialog::OnLButtonUp(nFlags, point);
//}

//int CSchemiAnatomiciRecordDlg::AggiungiPunto(long lIdPunto, long lIdOrgano, long lX, long lY)
//{
//	tagPunti puntoTemp;
//
//	puntoTemp.lIdPunto = lIdPunto;
//	puntoTemp.lIdOrgano = lIdOrgano;
//	puntoTemp.lX = lX;
//	puntoTemp.lY = lY;
//	PixelMillesimi(puntoTemp.lX, puntoTemp.lY);
//
//	TRACE("--> Aggiunto punto Punto:%li Organo:%li X:%li Y:%li\n", puntoTemp.lIdPunto, puntoTemp.lIdOrgano, puntoTemp.lX, puntoTemp.lY);
//	m_lstPunti.AddTail(puntoTemp);
//
//	return(m_lstPunti.GetCount() - 1);
//}
//
//int CSchemiAnatomiciRecordDlg::TrovaPunto(long lIdOrgano, long lX, long lY)
//{
//	long lTempX;
//	long lTempY;
//	int nIndex = 0;
//
//	POSITION pos = m_lstPunti.GetHeadPosition();
//	while(pos != NULL)
//	{
//		if (m_lstPunti.GetAt(pos).lIdOrgano == lIdOrgano)
//		{
//			lTempX = m_lstPunti.GetAt(pos).lX;
//			lTempY = m_lstPunti.GetAt(pos).lY;
//			MillesimiPixel(lTempX, lTempY);
//
//			if (sqrt(pow((double)(lX - lTempX), 2) + pow((double)(lY - lTempY), 2)) < RAGGIO_PUNTO)
//				return nIndex;
//		}
//
//		m_lstPunti.GetNext(pos);
//		nIndex++;
//	}
//
//	return -1;
//}
//
//void CSchemiAnatomiciRecordDlg::MillesimiPixel(long &lX, long &lY)
//{
//	CRect rectFrame;
//	GetDlgItem(IDC_FRAME)->GetWindowRect(rectFrame);
//	ScreenToClient(rectFrame);
//
//	CRect rectImage = m_RectToShowImage;
//	rectImage.OffsetRect(rectFrame.left, rectFrame.top);
//
//	// TRACE2("---> MillesimiPixel PIXEL %li %li\n", lX, lY);
//	lX = (long)((float)(lX * rectImage.Width()) / 100000.0f) + rectImage.left + 1;
//	lY = (long)((float)(lY * rectImage.Height()) / 100000.0f) + rectImage.top + 1;
//	// TRACE2("---> MillesimiPixel MILLS %li %li\n", lX, lY);
//}

//void CSchemiAnatomiciRecordDlg::PixelMillesimi(long &lX, long &lY)
//{
//	CRect rectFrame;
//	GetDlgItem(IDC_FRAME)->GetWindowRect(rectFrame);
//	ScreenToClient(rectFrame);
//
//	CRect rectImage = m_RectToShowImage;
//	rectImage.OffsetRect(rectFrame.left, rectFrame.top);
//
//	// TRACE2("---> PixelMillesimi MILLS %li %li\n", lX, lY);
//	lX = (long)((float)((lX - rectImage.left) * 100000) / (float)rectImage.Width());
//	lY = (long)((float)((lY - rectImage.top) * 100000) / (float)rectImage.Height());
//	// TRACE2("---> PixelMillesimi PIXEL %li %li\n", lX, lY);
//}

//LRESULT CSchemiAnatomiciRecordDlg::OnSelectBmp(WPARAM wParam, LPARAM lParam)
//{
//	CBmp* pBmp = (CBmp*)lParam;
//
//	if (m_nCurSel >= 0)
//	{
//		if (pBmp->GetPointNumber() == m_nCurSel)
//		{
//			pBmp->SetPointNumber(-1, TRUE);
//			
//			POSITION pos = m_ImgListOrgani.GetHeadPosition();
//			while(pos != NULL)
//			{
//				if (m_ImgListOrgani.GetAt(pos).img.lID == pBmp->m_lID)
//				{
//					IMG_ORGANI img_organi = m_ImgListOrgani.GetAt(pos);
//					img_organi.iPunto = -1;
//					m_ImgListOrgani.SetAt(pos, img_organi);
//					break;
//				}
//
//				m_ImgListOrgani.GetNext(pos);
//			}
//
//			CImmaginiPuntiSet().SetIDPunto(pBmp->m_lID, -1);
//		}
//		else
//		{
//			pBmp->SetPoint(m_nCurSel, RGB_WHITE, RGB_GRAY_DARK, TRUE);
//
//			POSITION pos = m_ImgListOrgani.GetHeadPosition();
//			while(pos != NULL)
//			{
//				if (m_ImgListOrgani.GetAt(pos).img.lID == pBmp->m_lID)
//				{
//					IMG_ORGANI img_organi = m_ImgListOrgani.GetAt(pos);
//					img_organi.iPunto = m_nCurSel;
//					m_ImgListOrgani.SetAt(pos, img_organi);
//					break;
//				}
//
//				m_ImgListOrgani.GetNext(pos);
//			}
//		}
//	}
//
//	return 0;
//}

//void CSchemiAnatomiciRecordDlg::CaricaPunti()
//{
//	long lIdPunto;
//	long lIdOrgano;
//	long lX;
//	long lY;
//	IMG_ORGANI img_organi;
//
//	BOOL bFindIndex;
//
//	POSITION pos1 = m_ImgListOrgani.GetHeadPosition();
//	POSITION pos2;
//
//	TRACE0("--> Rimossi tutti i punti\n");
//	m_lstPunti.RemoveAll();
//	while(pos1 != NULL)
//	{
//		lIdPunto = CImmaginiPuntiSet().GetIDPunto(m_ImgListOrgani.GetAt(pos1).img.lID);
//		if (lIdPunto > 0)
//		{
//			if (CPuntiSet().GetDatiPunto(lIdPunto, lIdOrgano, lX, lY) == TRUE)
//			{
//				img_organi = m_ImgListOrgani.GetAt(pos1);
//				img_organi.iPunto = 0;
//
//				bFindIndex = FALSE;
//				pos2 = m_lstPunti.GetHeadPosition();
//				while(pos2 != NULL)
//				{
//					if (m_lstPunti.GetAt(pos2).lIdOrgano == lIdOrgano)
//					{
//						if (sqrt(pow((double)(lX - m_lstPunti.GetAt(pos2).lX), 2) + pow((double)(lY - m_lstPunti.GetAt(pos2).lY), 2)) < RAGGIO_PUNTO)
//						{
//							bFindIndex = TRUE;
//							break;
//						}
//					}
//
//					m_lstPunti.GetNext(pos2);
//					img_organi.iPunto++;
//				}
//
//				if (bFindIndex == FALSE)
//				{
//					tagPunti puntoTemp;
//
//					puntoTemp.lIdPunto = lIdPunto;
//					puntoTemp.lIdOrgano = lIdOrgano;
//					puntoTemp.lX = lX;
//					puntoTemp.lY = lY;
//
//					TRACE("--> Aggiunto punto Punto:%li Organo:%li X:%li Y:%li\n", puntoTemp.lIdPunto, puntoTemp.lIdOrgano, puntoTemp.lX, puntoTemp.lY);
//					m_lstPunti.AddTail(puntoTemp);
//
//					img_organi.iPunto = m_lstPunti.GetCount() - 1;
//				}
//
//				m_ImgListOrgani.SetAt(pos1, img_organi);
//			}
//		}
//		m_ImgListOrgani.GetNext(pos1);
//	}
//
//	if (m_ImgListOrgani.GetCount() <= 0)
//		SendMessage(WM_COMMAND, IDOK);
//}
//
//void CSchemiAnatomiciRecordDlg::SalvaPunti()
//{
//	int nIndex = 0;
//	long lIdPunto;
//
//	POSITION pos1 = m_lstPunti.GetHeadPosition();
//	POSITION pos2 = NULL;
//
//	while(pos1 != NULL)
//	{
//		BOOL bSave = FALSE;
//
//		pos2 = m_ImgListOrgani.GetHeadPosition();
//		while(pos2 != NULL)
//		{
//			if (m_ImgListOrgani.GetAt(pos2).iPunto == nIndex)
//			{
//				bSave = TRUE;
//				break;
//			}
//
//			m_ImgListOrgani.GetNext(pos2);
//		}
//
//		if (bSave)
//		{
//			lIdPunto = CPuntiSet().SetDatiPunto(m_lstPunti.GetAt(pos1).lIdPunto, m_lstPunti.GetAt(pos1).lIdOrgano, m_lstPunti.GetAt(pos1).lX, m_lstPunti.GetAt(pos1).lY);
//
//			if (lIdPunto > 0)
//			{
//				pos2 = m_ImgListOrgani.GetHeadPosition();
//				while(pos2 != NULL)
//				{
//					if (m_ImgListOrgani.GetAt(pos2).iPunto == nIndex)
//					{
//						CImmaginiPuntiSet().SetIDPunto(m_ImgListOrgani.GetAt(pos2).img.lID, lIdPunto);
//						CFileBmp::NewSelected(m_ImgListOrgani.GetAt(pos2).img.lID, FALSE, m_ImgListOrgani.GetAt(pos2).img.type, CString(m_ImgListOrgani.GetAt(pos2).img.szDescription), m_lPaziente, m_lEsame, m_bConfirmed, m_strDvdLabel, m_ImgListOrgani.GetAt(pos2).img.bCI);
//					}
//
//					m_ImgListOrgani.GetNext(pos2);
//				}
//			}
//		}
//
//		nIndex++;
//		m_lstPunti.GetNext(pos1);
//	}	
//}

//void CSchemiAnatomiciRecordDlg::ListGridSchemiAnatomiciSaveRowToDatabase(int p_iRow)
//{
//}

long CSchemiAnatomiciRecordDlg::ListGridSchemiAnatomiciGetIDSelected()
{
	int iActualRow = m_ctrlListGridSchemiAnatomici.GetSelectionMark();	// Retrieves the item with the selection mark, or -1 if none.
	long lActualID = (iActualRow >= 0 ? m_ctrlListGridSchemiAnatomici.GetItemData(iActualRow) : m_pSchemiAnatomiciActual->m_lID);
	return lActualID;
}

long CSchemiAnatomiciRecordDlg::ListGridSchemiAnatomiciEtichetteGetIDSelected()
{
	int iActualRow = m_ctrlListGridSchemiAnatomiciEtichette.GetSelectionMark();	// Retrieves the item with the selection mark, or -1 if none.
	long lActualID = (iActualRow >= 0 ? m_ctrlListGridSchemiAnatomiciEtichette.GetItemData(iActualRow) : m_pSchemiAnatomiciEtichetteActual->m_lID);
	return lActualID;
}

CString CSchemiAnatomiciRecordDlg::ListGridSchemiAnatomiciGetAcao(long* p_lID, int p_nRowNumber)
{
	*p_lID = m_ctrlListGridSchemiAnatomici.GetItemData(p_nRowNumber);
	CString sAcao = m_ctrlListGridSchemiAnatomici.GetItemText(p_nRowNumber, _SA_QTT_COL_);
	return sAcao;
}

CString CSchemiAnatomiciRecordDlg::ListGridSchemiAnatomiciEtichetteGetAcao(long* p_lID, int p_nRowNumber)
{
	*p_lID = m_ctrlListGridSchemiAnatomiciEtichette.GetItemData(p_nRowNumber);
	CString sAcao = m_ctrlListGridSchemiAnatomiciEtichette.GetItemText(p_nRowNumber, _SAE_QTT_COL_);
	return sAcao;
}

void CSchemiAnatomiciRecordDlg::ListGridSchemiAnatomiciEtichetteSetTemp(CSchemiAnatomiciEtichetteSet* p_setTemp, int p_nRowNumber)
{
	p_setTemp->m_lID = m_ctrlListGridSchemiAnatomiciEtichette.GetItemData(p_nRowNumber);

	p_setTemp->m_lID_Schemi_Anatomici   = _ttol(m_ctrlListGridSchemiAnatomiciEtichette.GetItemText(p_nRowNumber, _SAE_COL_PAI_));
	p_setTemp->m_sDescrizione           = m_ctrlListGridSchemiAnatomiciEtichette.GetItemText(p_nRowNumber, _SAE_COL_DESC_);
	p_setTemp->m_lPunto_Alto_Sinistra_X = _ttol(m_ctrlListGridSchemiAnatomiciEtichette.GetItemText(p_nRowNumber, _SAE_COL_AX_));
	p_setTemp->m_lPunto_Alto_Sinistra_Y = _ttol(m_ctrlListGridSchemiAnatomiciEtichette.GetItemText(p_nRowNumber, _SAE_COL_AY_));
	p_setTemp->m_lPunto_Basso_Destra_X  = _ttol(m_ctrlListGridSchemiAnatomiciEtichette.GetItemText(p_nRowNumber, _SAE_COL_BX_));
	p_setTemp->m_lPunto_Basso_Destra_Y  = _ttol(m_ctrlListGridSchemiAnatomiciEtichette.GetItemText(p_nRowNumber, _SAE_COL_BY_));
	p_setTemp->m_lColore                = _ttol(m_ctrlListGridSchemiAnatomiciEtichette.GetItemText(p_nRowNumber, _SAE_COL_COLORE_));
	p_setTemp->m_dZoom_Factor           = _ttof(m_ctrlListGridSchemiAnatomiciEtichette.GetItemText(p_nRowNumber, _SAE_COL_ZOOM_FACTOR_));
	//CString sAcao = m_ctrlListGridSchemiAnatomiciEtichette.GetItemText(p_nRowNumber, _SA_QTT_COL_);
	return;
}

void CSchemiAnatomiciRecordDlg::ListGridSchemiAnatomiciSetTemp(CSchemiAnatomiciSet* p_setTemp, int p_nRowNumber)
{
	p_setTemp->m_lID = m_ctrlListGridSchemiAnatomici.GetItemData(p_nRowNumber);

	p_setTemp->m_sDescrizione = m_ctrlListGridSchemiAnatomici.GetItemText(p_nRowNumber, _SA_COL_DESC_);

	// tenta pegar a UO pela descrição
	p_setTemp->m_lUO = CUOSet().GetIDFromDescrizione(m_ctrlListGridSchemiAnatomici.GetItemText(p_nRowNumber, _SA_COL_UO_DESC_));
	
	// se não conseguiu vai pelo ID
	if (p_setTemp->m_lUO == 0)
	{
		p_setTemp->m_lUO = _ttol(m_ctrlListGridSchemiAnatomici.GetItemText(p_nRowNumber, _SA_COL_UO_));
	}

	p_setTemp->m_sCodicePrestazionePrevista = m_ctrlListGridSchemiAnatomici.GetItemText(p_nRowNumber, _SA_COL_SIGLA_EXAME_);
	p_setTemp->m_sImmagine_FullPath = m_ctrlListGridSchemiAnatomici.GetItemText(p_nRowNumber, _SA_COL_IMMAGINE_FULLPATH_);
	p_setTemp->m_lImmagine_Larghezza = _ttol(m_ctrlListGridSchemiAnatomici.GetItemText(p_nRowNumber, _SA_COL_IMMAGINE_LARGHEZZA_));
	p_setTemp->m_lImmagine_Altezza = _ttol(m_ctrlListGridSchemiAnatomici.GetItemText(p_nRowNumber, _SA_COL_IMMAGINE_ALTEZZA_));
	p_setTemp->m_dZoom_Factor = _ttof(m_ctrlListGridSchemiAnatomici.GetItemText(p_nRowNumber, _SA_COL_ZOOM_FACTOR_));
	//CString sAcao = m_ctrlListGridSchemiAnatomici.GetItemText(p_nRowNumber, _SA_QTT_COL_);
	return;
}

// Update/Insert/Delete all rows grid to Database
void CSchemiAnatomiciRecordDlg::ListGridSchemiAnatomiciEtichetteSaveAllToDatabase()
{
#define _STRLOG_0002 "CSchemiAnatomiciRecordDlg::ListGridSchemiAnatomiciEtichetteSaveAllToDatabase"

	BOOL bSaved = FALSE;
	long lID = -1;

	int iTotRows = m_ctrlListGridSchemiAnatomiciEtichette.GetItemCount();

	for (int iRow = iTotRows-1; iRow >= 0; iRow--)
	{
		CSchemiAnatomiciEtichetteSet setTemp;

		// pega as informações de cada linha do grid e coloca no setTemp
		CString sAcao = ListGridSchemiAnatomiciEtichetteGetAcao(&lID, iRow);

		/* Sugestão do Julio 24/03/2020
		if (sAcao == _DBCTRL_NEW)
		CSchemiAnatomiciEtichetteSet().Insert( , , , ,);
		else
		CSchemiAnatomiciEtichetteSet().UpdateValues(id da linha, valorse)
		*/

		if (sAcao == _DBCTRL_NEW)
		{
			if (setTemp.OpenRecordset(_STRLOG_0002))
			{
				setTemp.AddNewRecordset(_STRLOG_0002);

				// seta as informações da grid no recordset
				ListGridSchemiAnatomiciEtichetteSetTemp(&setTemp, iRow);
				setTemp.m_lID = 0;

				bSaved = setTemp.UpdateRecordset(_STRLOG_0002);

				// Update new ID in GRID
				long lID = setTemp.GetLastAdd();
				CString sAux;
				sAux.Format("%li", lID);
				m_ctrlListGridSchemiAnatomiciEtichette.SetItemData(iRow, lID);
				m_ctrlListGridSchemiAnatomiciEtichette.SetItemText(iRow, _SA_COL_ID_, sAux);

				setTemp.CloseRecordset(_STRLOG_0002);
			}
		}
		if (sAcao == _DBCTRL_ALTERED || sAcao == _DBCTRL_DELETED)
		{
			CString strFilter;
			strFilter.Format("ID=%li", lID);

			setTemp.SetOpenFilter(strFilter);

			if (setTemp.OpenRecordset(_STRLOG_0002))
			{
				if (setTemp.IsBOF() && setTemp.IsEOF())
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_ALREADY_DELETED), MB_ICONINFORMATION);
				}
				else
				{
					if (setTemp.EditRecordset(_STRLOG_0002))
					{
						// seta as informações da grid no recordset
						ListGridSchemiAnatomiciEtichetteSetTemp(&setTemp, iRow);

						setTemp.SetFieldDirty(NULL, TRUE);
						setTemp.SetFieldDirty(&setTemp.m_lID, FALSE);
						if (sAcao == _DBCTRL_DELETED)
						{
							bSaved = setTemp.DeleteRecordset(_STRLOG_0002);
						}
						if (sAcao == _DBCTRL_ALTERED)
						{
							bSaved = setTemp.UpdateRecordset(_STRLOG_0002);
						}
					}
				}
				setTemp.CloseRecordset(_STRLOG_0002);
			}
		}
	}
}


// Update/Insert/Delete all rows grid to Database
void CSchemiAnatomiciRecordDlg::ListGridSchemiAnatomiciSaveAllToDatabase()
{
#define _STRLOG_0001 "CSchemiAnatomiciRecordDlg::ListGridSchemiAnatomiciSaveAllToDatabase"
	
	BOOL bSaved = FALSE;
	long lID = -1;

	int iTotRows = m_ctrlListGridSchemiAnatomici.GetItemCount();

	for (int iRow = iTotRows-1; iRow >= 0; iRow--)
	{
		CSchemiAnatomiciSet setTemp;

		// pega as informações de cada linha do grid e coloca no setTemp
		CString sAcao = ListGridSchemiAnatomiciGetAcao(&lID, iRow);

		/* Sugestão do Julio 24/03/2020
		if (sAcao == _DBCTRL_NEW)
			CSchemiAnatomiciSet().Insert( , , , ,);
		else
			CSchemiAnatomiciSet().UpdateValues(id da linha, valorse)
		*/

		if (sAcao == _DBCTRL_NEW)
		{
			if (setTemp.OpenRecordset(_STRLOG_0001))
			{
				setTemp.AddNewRecordset(_STRLOG_0001);

				// seta as informações da grid no recordset
				ListGridSchemiAnatomiciSetTemp(&setTemp, iRow);

				bSaved = setTemp.UpdateRecordset(_STRLOG_0001);

				// Update new ID in GRID
				long lID = setTemp.GetLastAdd();
				CString sAux;
				sAux.Format("%li", lID);
				m_ctrlListGridSchemiAnatomici.SetItemData(iRow, lID);
				m_ctrlListGridSchemiAnatomici.SetItemText(iRow, _SA_COL_ID_, sAux);

				setTemp.CloseRecordset(_STRLOG_0001);
			}
		}
		if (sAcao == _DBCTRL_ALTERED || sAcao == _DBCTRL_DELETED)
		{
			CString strFilter;
			strFilter.Format("ID=%li", lID);

			setTemp.SetOpenFilter(strFilter);

			if (setTemp.OpenRecordset(_STRLOG_0001))
			{
				if (setTemp.IsBOF() && setTemp.IsEOF())
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_OPERATORIDLG_ALREADY_DELETED), MB_ICONINFORMATION);
				}
				else
				{
					if (setTemp.EditRecordset(_STRLOG_0001))
					{
						// seta as informações da grid no recordset
						ListGridSchemiAnatomiciSetTemp(&setTemp, iRow);

						setTemp.SetFieldDirty(NULL, TRUE);
						setTemp.SetFieldDirty(&setTemp.m_lID, FALSE);
						if (sAcao == _DBCTRL_DELETED)
						{
							// TODO: APAGAR OS RECS FILHOS (ETICHETTE - LABELS)
							// ASSERT(FALSE); 
							bSaved = setTemp.DeleteRecordset(_STRLOG_0001);
						}
						if (sAcao == _DBCTRL_ALTERED)
						{
							bSaved = setTemp.UpdateRecordset(_STRLOG_0001);
						}
					}
				}
				setTemp.CloseRecordset(_STRLOG_0001);
			}
		}
	}
}

void CSchemiAnatomiciRecordDlg::OnBnClickedSave()
{
	// salva conteúdo do grid para o database
	ListGridSchemiAnatomiciEtichetteSaveAllToDatabase();

	// salva conteúdo do grid para o database
	ListGridSchemiAnatomiciSaveAllToDatabase();

	// limpa o grid de itens correlatos e recarrega as informações do grid
	long lActualID = ListGridSchemiAnatomiciRiempi();

	// limpa o grid de itens correlatos e popula com itens correlatos do ID atual
	ListGridSchemiAnatomiciEtichetteRiempi(lActualID);

	ImageAndEtichetteShow();

	m_bAlteredSchemi = FALSE;
	m_bAlteredEtichette = FALSE;
}


void CSchemiAnatomiciRecordDlg::OnBnClickedClose()
{
	while (m_bAlteredSchemi || m_bAlteredEtichette)
	{
		if (theApp.AfxMessageBoxEndo(_T("Deseja salvar antes de sair?"), MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			OnBnClickedSave();
		else
			break;
	}

	m_pParentWnd->SendMessage(WM_WAITINGDICOM_CLOSING);
	CDialog::OnOK();
}


//void CSchemiAnatomiciRecordDlg::OnBnClickedCancel()
//{}

void CSchemiAnatomiciRecordDlg::ListGridSchemiAnatomiciUpdateActual(long p_lIDSelected)
{
	// update actual Schemi
	BOOL bError = TRUE;
	CString strFilter;
	strFilter.Format("ID=%li", p_lIDSelected);

	if (!m_setSchemiAnatomici.RecordsetReOpen(bError, strFilter, "DESCRIZIONE DESC", "CSchemiAnatomiciRecordDlg::ListGridSchemiAnatomiciEtichetteUpdateActual"))
	{
		m_setSchemiAnatomici.SetEmpty();
	}
	m_pSchemiAnatomiciActual = &(m_setSchemiAnatomici.m_pSchemiAnatomici);

	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_STATIC_IMAGE_TITLE);

	if(pStatic)
		pStatic->SetWindowText(m_pSchemiAnatomiciActual->m_sDescrizione);

}

void CSchemiAnatomiciRecordDlg::ListGridSchemiAnatomiciEtichetteUpdateActual(long p_lIDSelected)
{
	// update actual Schemi
	BOOL bError = TRUE;
	CString strFilter;
	strFilter.Format("ID_SCHEMI_ANATOMICI=%li", p_lIDSelected);

	if (!m_setSchemiAnatomiciEtichette.RecordsetReOpen(bError, strFilter, "ID DESC", "CSchemiAnatomiciRecordDlg::ListGridSchemiAnatomiciEtichetteUpdateActual"))
	{
		m_setSchemiAnatomiciEtichette.SetEmpty();
	}
	m_pSchemiAnatomiciEtichetteActual = &(m_setSchemiAnatomiciEtichette.m_pSchemiAnatomiciEtichette);
}

void CSchemiAnatomiciRecordDlg::ImageAndEtichetteShow()
{
	ImageShow(m_pSchemiAnatomiciActual->m_sImmagine_FullPath);
	RedrawWindow();
	DrawEtichetteAll(COLORREF RGB_BLUE);
}

void CSchemiAnatomiciRecordDlg::OnNMClickListSchemiAnatomici(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	while (m_bAlteredEtichette)
	{
		if (theApp.AfxMessageBoxEndo(_T("Deseja salvar LABELs antes de alternar?"), MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			OnBnClickedSave();
		else
			break;
	}

	int iRowSelectedIndex = pNMItemActivate->iItem;
	int iColSelectedIndex = pNMItemActivate->iSubItem;

	if (iRowSelectedIndex == -1 || iColSelectedIndex == -1)
		return;

	int iContTotRows = m_ctrlListGridSchemiAnatomici.GetItemCount();
	long lIDSelected = m_ctrlListGridSchemiAnatomici.GetItemData(iRowSelectedIndex);

	ListGridSchemiAnatomiciUpdateActual(lIDSelected);

	//CString sFullPathImage = m_ctrlListGridSchemiAnatomici.GetItemText(iRowSelectedIndex, _SA_COL_IMMAGINE_FULLPATH_);

	if (   iRowSelectedIndex >= 0 
		&& iRowSelectedIndex < iContTotRows 
		&& lIDSelected >= 0)
	{
		ListGridSchemiAnatomiciEtichetteRiempi(lIDSelected);
		ImageAndEtichetteShow();
	}
	else
	{
		// only refresh screen
		//ImageShow(m_pSchemiAnatomiciActual->m_sImmagine_FullPath);
		CString sFullPathImage = m_ctrlListGridSchemiAnatomici.GetItemText(iRowSelectedIndex, _SA_COL_IMMAGINE_FULLPATH_);
		BOOL bDoneOk = ImportImageFromDisk(sFullPathImage, &m_Dib);
		RedrawWindow();
	}

	// dismiss former image points to rect label
	m_bFirstDone = FALSE;
	m_bSecondDone = FALSE;

	*pResult = 0;
}


void CSchemiAnatomiciRecordDlg::OnNMDblclkListSchemiAnatomici(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// Habilita edicao das celulas do grid
	int iRowSelectedIndex = pNMItemActivate->iItem;
	int iColSelectedIndex = pNMItemActivate->iSubItem;
	
	POSITION pos = m_ctrlListGridSchemiAnatomici.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		CRect rect;
		m_ctrlListGridSchemiAnatomici.SetSubItemEdit(iRowSelectedIndex, iColSelectedIndex, FALSE, 255);
		m_ctrlListGridSchemiAnatomici.GetSubItemRect(iRowSelectedIndex, iColSelectedIndex, LVIR_LABEL, rect);
		m_ctrlListGridSchemiAnatomici.PostMessage(WM_LBUTTONDOWN, 0, MAKELPARAM((rect.right + rect.left) / 2, (rect.bottom + rect.top) / 2));

		// CONTROL COLUMN
		ListGridSetDBControl(&m_ctrlListGridSchemiAnatomici, iRowSelectedIndex, _DBCTRL_ALTERED);

		// se editou o código da UO
		if (iColSelectedIndex == _SA_COL_UO_)
		{
			m_ctrlListGridSchemiAnatomici.SetItemText(iRowSelectedIndex, _SA_COL_UO_DESC_, ""
				//CUOSet().GetDescrizione(_ttol(m_ctrlListGridSchemiAnatomici.GetItemText(iRowSelectedIndex, _SA_COL_UO_))).Trim()
				);	// set TEXT of the each COLUMN
		}
		m_bAlteredSchemi = TRUE;
	}

	*pResult = 0;
}

void CSchemiAnatomiciRecordDlg::OnNMClickListSchemiAnatomiciEtichette(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// just change to hide this caption button
	if (bOnBnClickedShowEtichetteShowOrHide == _SHOW_)
	{
		m_ctrlButtonSHOW.SetWindowText(_T("omitir"));
		bOnBnClickedShowEtichetteShowOrHide = _HIDE_;
	}

	int iRowSelectedIndex = pNMItemActivate->iItem;
	//int iColSelectedIndex = pNMItemActivate->iSubItem;
	//int iContTotRows = m_ctrlListGridSchemiAnatomiciEtichette.GetItemCount();
	//long lIDSelected = m_ctrlListGridSchemiAnatomiciEtichette.GetItemData(iRowSelectedIndex);

	//ListGridSchemiAnatomiciUpdateActual(lIDSelected);

	//CString sFullPathImage = m_ctrlListGridSchemiAnatomici.GetItemText(iRowSelectedIndex, _SA_COL_IMMAGINE_FULLPATH_);

	//if (iRowSelectedIndex >= 0
	//	&& iRowSelectedIndex < iContTotRows
	//	&& lIDSelected >= 0)
	//{
	RedrawWindow();
	DrawEtichetteAll(RGB_BLUE, iRowSelectedIndex); // Highlight in RED the selected one
	//}

	//RedrawWindow();

	*pResult = 0;
}


void CSchemiAnatomiciRecordDlg::OnNMDblclkListSchemiAnatomiciEtichette(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// Habilita edicao das celulas do grid
	int iRowSelectedIndex = pNMItemActivate->iItem;
	int iColSelectedIndex = pNMItemActivate->iSubItem;

	POSITION pos = m_ctrlListGridSchemiAnatomiciEtichette.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		CRect rect;
		m_ctrlListGridSchemiAnatomiciEtichette.SetSubItemEdit(iRowSelectedIndex, iColSelectedIndex, FALSE, 255);
		m_ctrlListGridSchemiAnatomiciEtichette.GetSubItemRect(iRowSelectedIndex, iColSelectedIndex, LVIR_LABEL, rect);
		m_ctrlListGridSchemiAnatomiciEtichette.PostMessage(WM_LBUTTONDOWN, 0, MAKELPARAM((rect.right + rect.left) / 2, (rect.bottom + rect.top) / 2));

		// CONTROL COLUMN
		ListGridSetDBControl(&m_ctrlListGridSchemiAnatomiciEtichette, iRowSelectedIndex, _DBCTRL_ALTERED);

		RedrawWindow();
		DrawEtichetteAll(RGB_BLUE, iRowSelectedIndex); // Highlight in RED the selected one

		m_bAlteredEtichette = TRUE;
	}

	*pResult = 0;
}





void CSchemiAnatomiciRecordDlg::OnBnClickedDelEtichette()
{
	{
		POSITION pos = m_ctrlListGridSchemiAnatomiciEtichette.GetFirstSelectedItemPosition();
		int iItemSelected = -1;
		
		if (pos != NULL)
		{
			while (pos)
			{
				int iItemSelected = m_ctrlListGridSchemiAnatomiciEtichette.GetNextSelectedItem(pos);
				if (m_ctrlListGridSchemiAnatomiciEtichette.GetItemState(iItemSelected, LVIS_SELECTED) == LVIS_SELECTED)
				{
					// CONTROL COLUMN - SET TO DELETE
					ListGridSetDBControl(&m_ctrlListGridSchemiAnatomiciEtichette, iItemSelected, _DBCTRL_DELETED);
					m_bAlteredEtichette = TRUE;
				}
			}
		}
	}
}

// Botão alternados = mostrar / omitir
void CSchemiAnatomiciRecordDlg::OnBnClickedShowEtichette()
{
	if (bOnBnClickedShowEtichetteShowOrHide == _HIDE_)
	{
		RedrawWindow();  // ImageShow(m_pSchemiAnatomiciActual->m_sImmagine_FullPath);
		m_ctrlButtonSHOW.SetWindowText(_T("mostrar"));
		bOnBnClickedShowEtichetteShowOrHide = _SHOW_;
		return;
	}

	if (bOnBnClickedShowEtichetteShowOrHide == _SHOW_)
	{
		m_ctrlButtonSHOW.SetWindowText(_T("omitir"));
		bOnBnClickedShowEtichetteShowOrHide = _HIDE_;
	}

	DrawEtichetteAll(COLORREF RGB_BLUE);
}

void CSchemiAnatomiciRecordDlg::DrawEtichette(int p_iRow, COLORREF p_cfCOLOR)
{
	CSchemiAnatomiciEtichetteSet setTempEtichette;

	// seta as informações da grid no recordset
	ListGridSchemiAnatomiciEtichetteSetTemp(&setTempEtichette, p_iRow);

	// desenha cada retangulo
	CRect rectAux = CRect(
		setTempEtichette.m_lPunto_Alto_Sinistra_X,
		setTempEtichette.m_lPunto_Alto_Sinistra_Y,
		setTempEtichette.m_lPunto_Basso_Destra_X,
		setTempEtichette.m_lPunto_Basso_Destra_Y);

	DrawRetangle(rectAux, p_cfCOLOR, 0);
}

void CSchemiAnatomiciRecordDlg::DrawEtichetteAll(COLORREF p_cfCOLOR, int p_iRedHighlighted) // p_iRedHighlighted== -1 if none
{
	int iTotRows = m_ctrlListGridSchemiAnatomiciEtichette.GetItemCount();

	for (int iRow = 0; iRow < iTotRows; iRow++)
	{
		if (iRow == p_iRedHighlighted)
			DrawEtichette(iRow, RGB_RED);
		else
			DrawEtichette(iRow, RGB_BLUE);
	}
}

int CSchemiAnatomiciRecordDlg::ListGridGetColumnsCount(CAMEditComboListCtrl* p_pThisList)
{
	return p_pThisList->GetHeaderCtrl()->GetItemCount();
}

void CSchemiAnatomiciRecordDlg::ListGridSetItemFocus(CAMEditComboListCtrl* p_pThisList, int iRow)
{
	// funcionava no CListSortableCtrl
	// não funcionou no CAMEditComboListCtrl (não tenho o código fonte para implementar)
	this->SetFocus();
	((CListCtrl*)this)->SetItemState(-1, 0, LVIS_SELECTED);
	((CListCtrl*)this)->SetItemState(iRow, LVIS_SELECTED, LVIS_SELECTED);
	((CListCtrl*)this)->EnsureVisible(iRow, FALSE);
}

void CSchemiAnatomiciRecordDlg::OnBnClickedDel()
{
	{
		POSITION pos = m_ctrlListGridSchemiAnatomici.GetFirstSelectedItemPosition();
		int iItemSelected = -1;

		if (pos != NULL)
		{
			while (pos)
			{
				int iItemSelected = m_ctrlListGridSchemiAnatomici.GetNextSelectedItem(pos);
				if (m_ctrlListGridSchemiAnatomici.GetItemState(iItemSelected, LVIS_SELECTED) == LVIS_SELECTED)
				{
					// CONTROL COLUMN - SET TO DELETE
					ListGridSetDBControl(&m_ctrlListGridSchemiAnatomici, iItemSelected, _DBCTRL_DELETED);
					m_bAlteredSchemi = TRUE;
				}
			}
		}
	}
}


void CSchemiAnatomiciRecordDlg::OnBnClickedNew()
{
	m_setSchemiAnatomici.m_lID = -1; // new one
	m_setSchemiAnatomici.m_sDescrizione = "novo";
	m_setSchemiAnatomici.m_lUO = 26;					// Código da Especialidade - onde o esquema anatômico poderá ser usado
	m_setSchemiAnatomici.m_sCodicePrestazionePrevista = "";	// Código do Exame - onde o esquema anatômico poderá ser usado
	m_setSchemiAnatomici.m_sImmagine_FullPath = "";
	m_setSchemiAnatomici.m_lImmagine_Larghezza = 0;
	m_setSchemiAnatomici.m_lImmagine_Altezza = 0;
	m_setSchemiAnatomici.m_dZoom_Factor = 1;

	int iNewRow = ListGridSchemiAnatomiciAddThisRegAsNewRow();  // insere no grid as informações acima

	// CONTROL COLUMN
	ListGridSetDBControl(&m_ctrlListGridSchemiAnatomici, iNewRow, _DBCTRL_NEW);

	m_bAlteredSchemi = TRUE;
}


void CSchemiAnatomiciRecordDlg::OnBnClickedClone()
{
	if (!ListGridSchemiAnatomiciValidaPossibilidadeDeEdicaoDaRowSelecionada())
	{
		return;
	}
}


void CSchemiAnatomiciRecordDlg::OnBnClickedHlp()
{	// HELP DA TELA
	CString auxMsg;
	auxMsg.Format("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s", 
		"CADASTRAMENTO DE ESQUEMAS ANATÔMICOS:",
		"\nNAS TABELAS (GRIDS):",
		"1) Clique do Botão ESQUERDO do Mouse para selecionar a linha (focaliza o item desejado para edição);",
		"2) Clique Duplo do Botão ESQUERDO do Mouse para editar o valor da célula desejada;",
		"\nNA IMAGEM:",
		"1) Clique do Botão ESQUERDO do Mouse para definir o CANTO SUPERIOR ESQUERDO do novo rótulo (LABEL) da legenda;",
		"2) Clique do Botão DIREITO do Mouse para definir o CANTO INFERIOR DIREITO do novo rótulo (LABEL) da legenda;",
		"3) Botão 'mostrar/omitir' para alternar a visualização dos rótulos (LABELs) já definidos na imagem."
	);
	theApp.AfxMessageBoxEndo(auxMsg);
}
