// -------------------------------------------------------------------------------------------------------------------------
// Marvel Carvalho - BUG 4308 Esquemas Anatomicos Fleury
// -------------------------------------------------------------------------------------------------------------------------
// DONE: 03) ADICIONAR CONFIRMAÇÃO DE SAIR SEM SALVAR (void CSchemiAnatomiciEditDlg::OnBnClickedClose())
// DONE: 05) CODIFICAR A FUNCIONALIDADE DE EXPORTAR PARA ARQUIVO >> EXPORTAR PARA ALBUM DO EXAME
// void CSchemiAnatomiciEditDlg::OnBnClickedExp()
// void CSchemiAnatomiciEditDlg::ImageMergeLayersAndExportToAlbum()
// DONE: 13) TAMANHO FIXO DAS BOLINHAS
// void CSchemiAnatomiciEditDlg::OnRButtonDown(UINT nFlags, CPoint point) 
// DONE: 10) TIRAR O FRAME VAZIO DA ESQUERDA DA IMAGEM
// -------------------------------------------------------------------------------------------------------------------------

// DONE: 01) VER CAMPO COLORE NA BASE DE DADOS ESTÁ ARMAZENANDO UM VALOR DIFERENTE. Analisar Unsigned long >> long (vice-versa)
// DONE: 07) TENTAR PEGAR A COR DO FUNDO DA ETICHETTE PARA DESENHAR O CIRCULO DA LABEL
// DONE: 08) TIRAR O RETANGULO AZUL DA APRESENTAÇÃO DA IMAGEM
// DONE: 02) AJUSTAR A DISPOSIÇÃO DOS COMPONENTES DO FORM * (talvez tenha que reprogramar o cadastro)
// DONE: 04) COLOCAR O CAMPO FROM [TESICAPTURE].[dbo].[SCHEMI_ANATOMICI_AGGIUNTO].[DESCRIZIONE] NO TEXT DA LABEL QUE FICA ACIMA DA IMAGE
// DONE: 11) Duvida: No Clicke-Mouse-LBtn apaga uma label adicionada. se houver labels sobrepostas, ao clicar em uma >> apagar todas da mesma posição? Sim tudo bem

// TODO: 09) CHECAR O COMPORTAMENTO QDO NAO ENCONTRAR A IMAGEM DO ESQUEMA PARA APRESENTAR
// TODO: 06) MUDAR O CAPTION DO FORM PARA "Edição do Esquema Anatômico adicionado ao exame %s" (TAL)
// TODO: 12) Testar Labels sobrepostas cadastradas no SCHEMI ANATOMICI
// ...
//

#include "stdafx.h"
#include "Endox.h"
#include "SchemiAnatomiciEditDlg.h"

#include <io.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "DLL_Imaging\h\ImgArchive.h"

#include "Bmp.h"
#include "Common.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "FileBmp.h"
#include "ImmaginiPuntiSet.h"
#include "LogFileWriter.h"
#include "MmSystem.h"
#include "PuntiSet.h"

#include "TipoEsameSet.h"
#include "UOSet.h"
#include "InputBox.h"
#include "AlbumForm.h"


// ORDER OF GRID COLUMNS
// SCHEMI_ANATOMICI
#define _SA_COL_ID_				    0
#define _SA_COL_DESC_				1
#define _SA_COL_UO_				    2
#define _SA_COL_SIGLA_EXAME_		3
#define _SA_COL_IMMAGINE_FULLPATH_	4
#define _SA_COL_IMMAGINE_LARGHEZZA_ 5
#define _SA_COL_IMMAGINE_ALTEZZA_   6
#define _SA_COL_ZOOM_FACTOR_	    7
#define _SA_QTT_COL_				8

// SCHEMI_ANATOMICI ETICHETTE
#define _SAE_COL_PAI_	0
#define _SAE_COL_ID_	1
#define _SAE_COL_DESC_	2
#define _SAE_COL_AX_	3
#define _SAE_COL_AY_	4
#define _SAE_COL_BX_	5
#define _SAE_COL_BY_	6
#define _SAE_COL_ZOOM_FACTOR_	    7
#define _SAE_QTT_COL_	8

// CListControl & DB Column of control
#define _DBCTRL_NEW		"NEW"
#define _DBCTRL_SAME	"SAME"
#define _DBCTRL_ALTERED	"ALTERED"
#define _DBCTRL_DELETED	"DELETED"
#define _DBCTRL_FORGET	"FORGET"	// DO NOTHING

#define _SAA_COL_STATO_NEW		0
#define _SAA_COL_STATO_EDITED	1
#define _SAA_COL_STATO_EXPORTED	2

#define _SHOW_ TRUE
#define _HIDE_ FALSE

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSchemiAnatomiciEditDlg::CSchemiAnatomiciEditDlg(CWnd* pParent, CEsamiView* pEsamiView, long p_lContatoreSchemiAggiuntoToEdit, long p_lIDSchemiAnatomici)
	: CEndoxResizableDlg(CSchemiAnatomiciEditDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);
	m_pEsamiView = pEsamiView;
	m_pSchemiAnatomiciActual = NULL;
	m_pSchemiAnatomiciEtichetteActual = NULL;

	m_setSchemiAnatomici.SetSortRecord(_T("DESCRIZIONE DESC"));
	m_setSchemiAnatomici.OpenRecordset(_T("CSchemiAnatomiciEditDlg::CSchemiAnatomiciEditDlg"));

	m_setSchemiAnatomiciEtichette.SetSortRecord(_T("ID DESC"));
	m_setSchemiAnatomiciEtichette.OpenRecordset(_T("CSchemiAnatomiciEditDlg::CSchemiAnatomiciEditDlg"));

	m_lContatoreSchemiAggiuntoToEdit = p_lContatoreSchemiAggiuntoToEdit;	// related to [dbo].[SCHEMI_ANATOMICI_AGGIUNTO].[CONTATORE]
	m_lIDSchemiAnatomici             = p_lIDSchemiAnatomici;				// related to [dbo].[SCHEMI_ANATOMICI_AGGIUNTO].[ID_SCHEMI_ANATOMICI]

	m_bAltered = FALSE;
	m_iRetunState = _SAA_COL_STATO_NEW;
	bOnBnClickedShowEtichetteShowOrHide = TRUE;
}

CSchemiAnatomiciEditDlg::~CSchemiAnatomiciEditDlg(void)
{
	m_setSchemiAnatomici.CloseRecordset(_T("CSchemiAnatomiciEditDlg::~CSchemiAnatomiciEditDlg"));
	m_setSchemiAnatomiciEtichette.CloseRecordset(_T("CSchemiAnatomiciEditDlg::~CSchemiAnatomiciEditDlg"));
}

void CSchemiAnatomiciEditDlg::DoDataExchange(CDataExchange* pDX)
{
	if (!m_setSchemiAnatomici.IsOpen())
	{
		return;
	}

	CEndoxResizableDlg::DoDataExchange(pDX);

	//DDX_Text(pDX, IDC_COMMENTO, m_setSchemiAnatomici.m_sDescrizione);
	//DDX_Control(pDX, IDC_SAVE, m_ctrlButtonSAVE);
	//DDX_Control(pDX, IDC_SHOW_ETICHETTE, m_ctrlButtonSHOW);
	//DDX_Control(pDX, IDC_LIST_SCHEMI_ANATOMICI, m_ctrlListGridSchemiAnatomici);
	//DDX_Control(pDX, IDC_LIST_SCHEMI_ANATOMICI_ET, m_ctrlListGridSchemiAnatomiciEtichette);

	// update to the actual [SchemiAnatomici] object from record / database
	m_pSchemiAnatomiciActual = &(m_setSchemiAnatomici.m_pSchemiAnatomici); 
	m_pSchemiAnatomiciEtichetteActual = &(m_setSchemiAnatomiciEtichette.m_pSchemiAnatomiciEtichette);
}

BEGIN_MESSAGE_MAP(CSchemiAnatomiciEditDlg, CEndoxResizableDlg)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()

	ON_BN_CLICKED(IDC_IMPORT_IMG, &CSchemiAnatomiciEditDlg::ImageOpenDlgImport)
	ON_BN_CLICKED(IDC_SAVE, &CSchemiAnatomiciEditDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDCLOSE, &CSchemiAnatomiciEditDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_EXP, &CSchemiAnatomiciEditDlg::OnBnClickedExp)

	ON_BN_CLICKED(IDC_HLP, &CSchemiAnatomiciEditDlg::OnBnClickedHlp)
END_MESSAGE_MAP()


void CSchemiAnatomiciEditDlg::ListSchemiAnatomiciEtichetteAggiuntoRiempi(long p_lContatoreSchemiAggiuntoToEdit)
{

#define _STRLOG_0004 "CSchemiAnatomiciEditDlg::ListSchemiAnatomiciEtichetteAggiuntoRiempi"
	CSchemiAnatomiciAggiuntoEtichetteSet setTemp;
	CString strFilter;
	strFilter.Format("ID_SCHEMI_ANATOMICI_AGGIUNTO=%li", p_lContatoreSchemiAggiuntoToEdit);
	setTemp.SetOpenFilter(strFilter);

	if (p_lContatoreSchemiAggiuntoToEdit <= 0)
	{
		m_lstEtichetteAggiunta.RemoveAll();
		return;
	}

	if (setTemp.OpenRecordset(_STRLOG_0004))
	{
		while (!setTemp.IsEOF())
		{
			m_pCurrentEtichetteToInsert.m_lCONTATORE = setTemp.m_lCONTATORE;								// contatore will be filled after insert
			m_pCurrentEtichetteToInsert.m_lID_SCHEMI_ANATOMICI_AGGIUNTO = setTemp.m_lID_SCHEMI_ANATOMICI_AGGIUNTO; // related to [dbo].[SCHEMI_ANATOMICI_AGGIUNTO].[CONTATORE]
			m_pCurrentEtichetteToInsert.m_lID_SCHEMI_ANATOMICI_ETICHETTE = setTemp.m_lID_SCHEMI_ANATOMICI_ETICHETTE;
			m_pCurrentEtichetteToInsert.m_sDESCRIZIONE = setTemp.m_sDESCRIZIONE;
			m_pCurrentEtichetteToInsert.m_pRectPUNTI = 
				CRect(  setTemp.m_lPUNTO_ALTO_SINISTRA_X,
						setTemp.m_lPUNTO_ALTO_SINISTRA_Y,
						setTemp.m_lPUNTO_BASSO_DESTRA_X,
						setTemp.m_lPUNTO_BASSO_DESTRA_Y  );
			m_pCurrentEtichetteToInsert.m_lCOLORE = setTemp.m_lCOLORE;
			m_pCurrentEtichetteToInsert.m_sAcao = _DBCTRL_SAME;
			
			CEtichetteAggiunta newEtichette = CEtichetteAggiunta(m_pCurrentEtichetteToInsert);
			m_lstEtichetteAggiunta.AddTail(newEtichette);

			setTemp.MoveNext();
		}

		setTemp.CloseRecordset(_STRLOG_0004);
	}
	else
	{
		m_lstEtichetteAggiunta.RemoveAll();
	}

	return;
}

BOOL CSchemiAnatomiciEditDlg::ImageShow(CString p_sFullPathImage)
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


BOOL CSchemiAnatomiciEditDlg::ImportImageFromDisk(CString p_sFullPathImg, CDib* p_Dib)
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
void CSchemiAnatomiciEditDlg::ImageOpenDlgImport()
{
	//if (m_pSchemiAnatomiciActual == NULL || m_ctrlListGridSchemiAnatomici.GetSelectedCount()==0)
	//{
	//	theApp.AfxMessageBoxEndo(_T("necessário selecionar o esquema anatômico primeiro"));
	//	ASSERT(m_pSchemiAnatomiciActual == NULL);
	//	return;
	//}
	
	//CStringList ArraySelected;
	TCHAR szFilters[] = _T("Bitmap Files (*.bmp)|*.bmp|All Files (*.*)|*.*||");
	CFileDialog dlgFile(TRUE, _T("bmp"), _T("*.bmp"), OFN_READONLY | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, szFilters, this, 0, FALSE); // OFN_ALLOWMULTISELECT

	CString strFileDialog;
	int iMaxFiles = 1;
	int iBuffSize = (iMaxFiles * (MAX_PATH + 1)) + 1;

	dlgFile.GetOFN().lpstrFile = strFileDialog.GetBuffer(iBuffSize);
	dlgFile.GetOFN().nMaxFile = iBuffSize;
	// TODO: MARVEL DEBUG - necessário colocar em IMPIANTO o caminho padrão onde ficam as imagens dos esquemas anatomicos
	dlgFile.GetOFN().lpstrInitialDir = _T("C:\\TESI\\IMM\\AnatomicalScheme");

	BOOL bDoneOk = FALSE;

	if (dlgFile.DoModal() == IDOK)
	{
		bDoneOk = ImageShow(dlgFile.GetPathName());
	}

	if (bDoneOk)
	{
		//// Atualiza as informações do GRID de Esquemas Anatômicos
		//int iRowNum = m_ctrlListGridSchemiAnatomici.GetSelectionMark();
		//CString sImgHeight, sImgWidth, sZoomFactor;
		//sImgHeight.Format("%ld", m_Dib.Height());
		//sImgWidth.Format ("%ld", m_Dib.Width() );

		////double dZoomFactor = m_setSchemiAnatomici.m_dZoom_Factor = ImageCalcZoomFactor(&m_RectToShowImage, &m_Dib);
		//sZoomFactor.Format("%.18f", m_pSchemiAnatomiciActual->m_dZoom_Factor);

		//m_ctrlListGridSchemiAnatomici.SetItemText(iRowNum, _SA_COL_IMMAGINE_FULLPATH_, dlgFile.GetPathName());
		//m_ctrlListGridSchemiAnatomici.SetItemText(iRowNum, _SA_COL_IMMAGINE_ALTEZZA_, sImgHeight);
		//m_ctrlListGridSchemiAnatomici.SetItemText(iRowNum, _SA_COL_IMMAGINE_LARGHEZZA_, sImgWidth);
		//m_ctrlListGridSchemiAnatomici.SetItemText(iRowNum, _SA_COL_ZOOM_FACTOR_, sZoomFactor);

		//// CONTROL COLUMN
		//ListGridSetDBControl(&m_ctrlListGridSchemiAnatomici, iRowNum, _DBCTRL_ALTERED);

		RedrawWindow();
	}
}

void CSchemiAnatomiciEditDlg::FillSemiTransparentRegion()
{
	return;
		CPaintDC dc(this);
		CPen pPen(PS_SOLID, 1, RGB(0, 0, 0));
		CBrush bBr(RGB(0, 0, 150));
		CRect rec;

		//rectangle to be drawn
		rec.top = 0;
		rec.left = 0;
		rec.right = 100;
		rec.bottom = 100;

		dc.SelectObject(pPen);
		dc.SelectObject(bBr);

		dc.Rectangle(rec);
}

BOOL CSchemiAnatomiciEditDlg::OnInitDialog() 
{
	CEndoxResizableDlg::OnInitDialog();
//	int i;

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	//SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //


	//m_lPaziente = m_pEsamiView->m_pEsamiSet->m_lPaziente;
	//m_lEsame = m_pEsamiView->m_pEsamiSet->m_lContatore;
	//m_pEsamiView->m_pImgManager->SetCurrentIDs(m_lPaziente, m_lEsame);
	//m_bConfirmed = m_pEsamiView->m_pImgManager->IsExamConfirmed(m_strDvdLabel);

	theApp.LocalizeDialog(this, CSchemiAnatomiciEditDlg::IDD, "SchemiAnatomiciEditDlg");

	ListSchemiAnatomiciEtichetteAggiuntoRiempi(m_lContatoreSchemiAggiuntoToEdit);

	ImageAndEtichetteShow(m_lIDSchemiAnatomici);

	return TRUE;  
}

//void CSchemiAnatomiciEditDlg::OnCancel() 
//{
	//if (m_ctrlListImage.IsWindowVisible())		CEndoxResizableDlg::OnCancel();
//}

/*
void CSchemiAnatomiciEditDlg::OnOK() 
{

	//if (!m_ctrlListImage.IsWindowVisible())
	{
		//SalvaPunti();
		//CEndoxResizableDlg::OnOK();
	}
}
*/

double CSchemiAnatomiciEditDlg::ImageCalcZoomFactor(CRect* p_pRectClient, CDib* p_pDib)
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


void CSchemiAnatomiciEditDlg::DrawLabels()
{
	CPaintDC dc(this);

	int nsave = dc.SaveDC();

	if (CWnd* pFrame = GetDlgItem(IDC_FRAME))
	{
		CClientDC dcp(pFrame);

		CRect rectFrame;
		pFrame->GetWindowRect(rectFrame);
		ScreenToClient(rectFrame);
		dcp.SetBkMode(TRANSPARENT);

		POSITION pos = m_lstEtichetteAggiunta.GetHeadPosition();
		
		while (pos != NULL)
		{
			if (m_lstEtichetteAggiunta.GetAt(pos).m_sAcao != _DBCTRL_DELETED)
			{
				CPen   penNormal(PS_SOLID, 1, m_lstEtichetteAggiunta.GetAt(pos).m_lCOLORE); // RGB_GRAY_DARK);
				CBrush brushNormal(m_lstEtichetteAggiunta.GetAt(pos).m_lCOLORE); //RGB_GRAY_DARK);

				CPen*   pOldPen = dcp.SelectObject(&penNormal);;
				CBrush* pOldBrush = dcp.SelectObject(&brushNormal);
				CFont*  pOldFont = dcp.SelectObject(&theApp.m_fontBig); // m_fontBold);

				//dcp.SetTextColor(RGB_WHITE - m_lstEtichetteAggiunta.GetAt(pos).m_lCOLORE); // CALCULA A COR COMPLEMENTAR: ou seja, de MAIOR CONTRASTE
				dcp.SetTextColor(RGB_BLACK);

				CRect rectTemp = m_lstEtichetteAggiunta.GetAt(pos).m_pRectPUNTI - rectFrame.TopLeft(); // desconta a posição do FRAME HOST
				dcp.Ellipse(rectTemp);
				dcp.DrawText(m_lstEtichetteAggiunta.GetAt(pos).m_sDESCRIZIONE, rectTemp, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				// Draw Retangle
				//int nsave = dcp.SaveDC();
				//CPen pen(PS_SOLID, 2, RGB_RED);
				//dcp.SelectObject(&pen);
				//dcp.MoveTo(rectTemp.left, rectTemp.top);
				//dcp.LineTo(rectTemp.right, rectTemp.top);
				//dcp.LineTo(rectTemp.right, rectTemp.bottom);
				//dcp.LineTo(rectTemp.left, rectTemp.bottom);
				//dcp.LineTo(rectTemp.left, rectTemp.top);
				//dcp.RestoreDC(nsave);

				dcp.SelectObject(pOldPen);
				dcp.SelectObject(pOldBrush);
				dcp.SelectObject(pOldFont);

				penNormal.DeleteObject();
				brushNormal.DeleteObject();
			}
			m_lstEtichetteAggiunta.GetNext(pos);
		}
	}
	dc.RestoreDC(nsave);
}


BOOL CSchemiAnatomiciEditDlg::ImageMergeLayersAndExportToAlbum()
{
	int iResp = IDNO;

	if (CWnd* pFrame = GetDlgItem(IDC_FRAME))
	{
		CDib auxDib;

		HANDLE hDIB = auxDib.WriteWindowToDIB(pFrame);
		
		HBITMAP hBitmap = NULL;
		hBitmap = ((CDib)hDIB).BitmapFromDib(GetDC()->m_hDC, NULL, DIB_PAL_COLORS);

		long newImgId = 0;
		if (m_pEsamiView->m_pImgManager->ImportImg(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, POINT_NONE, hBitmap, FORM_IMM, FORM_MINI, FALSE, &newImgId))
		{
			m_pEsamiView->m_pFormImmagini->AfterMoveEsame(FALSE, TRUE); // FAZ REFRESH DO ALBUM DE IMAGENS
			//theApp.AfxMessageBoxEndo("Exportação realizada com sucesso!");
			m_iRetunState = _SAA_COL_STATO_EXPORTED;
		}
		else
		{
			theApp.AfxMessageBoxEndo("Erro na exportação...");
			return FALSE;
		}
	}
	return TRUE;
}

void CSchemiAnatomiciEditDlg::OnPaint() 
{
	if (!m_setSchemiAnatomici.IsOpen())
	{
		return;
	}

	//FillSemiTransparentRegion();

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
				
				//DrawRetangle(m_RectToShowImage, RGB_GREEN, 0);

				// proporzioni //
				m_pSchemiAnatomiciActual->m_dZoom_Factor = ImageCalcZoomFactor(&m_RectToShowImage, &m_Dib);

				if (bOnBnClickedShowEtichetteShowOrHide)
				{
					DrawEtichetteAll(m_lIDSchemiAnatomici, COLORREF RGB_BLUE);
				}

				DrawLabels();
				//DrawScene(&dc);
				//OnPaintTest();
 			}
		}
	}
}

void CSchemiAnatomiciEditDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);

	CRect rectFrame;
	GetDlgItem(IDC_FRAME)->GetWindowRect(rectFrame);	// posição do frame na screen (full screen - tela inteira)	//DrawRetangle(rectFrame, RGB_RED);
	ScreenToClient(&rectFrame);						// posição do frame na window continente (anfitriã)			//
	DrawRetangle(rectFrame, RGB_RED, 0);
	
	// if point clicked is out of image area, so do nothing
	if (rectFrame.PtInRect(point) == FALSE)
		return;

	// if point clicked in some LABEL AREA
	CString sFilter;
	sFilter.Format("ID_SCHEMI_ANATOMICI=%li", m_lIDSchemiAnatomici);

	m_pCurrentEtichetteToInsert.m_lCONTATORE = -1;													// contatore will be filled after insert
	m_pCurrentEtichetteToInsert.m_lID_SCHEMI_ANATOMICI_AGGIUNTO = m_lContatoreSchemiAggiuntoToEdit; // related to [dbo].[SCHEMI_ANATOMICI_AGGIUNTO].[CONTATORE]
	
	// update actual SchemiEtichette
	BOOL bError = TRUE;
	if (m_setSchemiAnatomiciEtichette.RecordsetReOpen(bError, sFilter, "ID DESC", "CSchemiAnatomiciEditDlg::ListGridSchemiAnatomiciEtichetteRiempi"))
	{
		// verifica em TODOS OS REGISTROS DE ETICHETTE - se clicou em algum, FAZ highlight em vermelho!
		while (!m_setSchemiAnatomiciEtichette.IsEOF())
		{
			CRect auxRect = CRect(
				m_setSchemiAnatomiciEtichette.m_pSchemiAnatomiciEtichette.m_lPunto_Alto_Sinistra_X,
				m_setSchemiAnatomiciEtichette.m_pSchemiAnatomiciEtichette.m_lPunto_Alto_Sinistra_Y,
				m_setSchemiAnatomiciEtichette.m_pSchemiAnatomiciEtichette.m_lPunto_Basso_Destra_X,
				m_setSchemiAnatomiciEtichette.m_pSchemiAnatomiciEtichette.m_lPunto_Basso_Destra_Y);

			// diferença entre a tela que cadastra e a tela que apresenta
			auxRect.left -= m_diff;
			auxRect.right -= m_diff;

			// if point clicked is out of image area, so do nothing
			if (auxRect.PtInRect(point) == TRUE)
			{
				m_pSchemiAnatomiciEtichetteActual = &(m_setSchemiAnatomiciEtichette.m_pSchemiAnatomiciEtichette);

				m_pCurrentEtichetteToInsert.m_lID_SCHEMI_ANATOMICI_ETICHETTE = m_setSchemiAnatomiciEtichette.m_lID;
				m_pCurrentEtichetteToInsert.m_sDESCRIZIONE                   = m_pSchemiAnatomiciEtichetteActual->m_sDescrizione;
				m_pCurrentEtichetteToInsert.m_pRectPUNTI                     = auxRect;  // LBtn Mouse = seleciona etichette >> copia o rect da etichette selecionada
				m_pCurrentEtichetteToInsert.m_lCOLORE                        = m_pSchemiAnatomiciEtichetteActual->m_lColore;	// related to [dbo].[SCHEMI_ANATOMICI_ETICHETTE].[COLORE]
				// a cor vai ser setada no RBUTTON
				// a acao vai ser setada no RBUTTON
			}
			m_setSchemiAnatomiciEtichette.MoveNext();
		}

		// VERIFICA em TODAS AS LABELS ADICIONADAS - se clicou em alguma, APAGA!
		//POSITION posToRemove = NULL;
		POSITION pos = m_lstEtichetteAggiunta.GetHeadPosition();
		while (pos != NULL)
		{
			CRect auxRect = m_lstEtichetteAggiunta.GetAt(pos).m_pRectPUNTI;
			if (auxRect.PtInRect(point) == TRUE)
			{
				// logical deletion
				m_lstEtichetteAggiunta.GetAt(pos).m_sAcao = _DBCTRL_DELETED;
				m_bAltered = TRUE;
				//posToRemove = pos;
			}
			m_lstEtichetteAggiunta.GetNext(pos);

			//if (posToRemove != NULL)
			//{
			//	m_lstEtichetteAggiunta.RemoveAt(posToRemove);
			//	posToRemove = NULL;
			//}
		}
	}

	RedrawWindow();

	return;
}

void CSchemiAnatomiciEditDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);
	CRect rectFrame;
	GetDlgItem(IDC_FRAME)->GetWindowRect(rectFrame);	// posição do frame na screen (fuul screen - tela inteira)	//DrawRetangle(rectFrame, RGB_RED);
	ScreenToClient(rectFrame);							// posição do frame na window continente (anfitriã)			//DrawRetangle(rectFrame, RGB_BLUE);

	if (m_pCurrentEtichetteToInsert.m_lID_SCHEMI_ANATOMICI_ETICHETTE <= 0)
		return;

	if (rectFrame.PtInRect(point) == FALSE)
		return;

	// make a perfect square with the longest side
	CRect auxRect = m_pCurrentEtichetteToInsert.m_pRectPUNTI;
	int iHalfSize = 15;			// tamanho raio da Label 							// opção: média dos lados da etichette >>> (m_pCurrentEtichetteToInsert.m_pRectPUNTI.Height() + m_pCurrentEtichetteToInsert.m_pRectPUNTI.Width()) / 4;
	auxRect.NormalizeRect();	// desinverte o retângulo se necessário
	auxRect.MoveToXY(point.x - iHalfSize, point.y - iHalfSize);
	auxRect.right = point.x + iHalfSize;
	auxRect.bottom = point.y + iHalfSize;

	m_pCurrentEtichetteToInsert.m_pRectPUNTI = auxRect;
	//m_pCurrentEtichetteToInsert.m_lCOLORE = RGB(255, 255, 0);
	m_pCurrentEtichetteToInsert.m_sAcao = _DBCTRL_NEW;

	CEtichetteAggiunta newEtichette = CEtichetteAggiunta(m_pCurrentEtichetteToInsert);
	m_lstEtichetteAggiunta.AddTail(newEtichette);
	m_bAltered = TRUE;
	m_iRetunState = _SAA_COL_STATO_EDITED;
	
	RedrawWindow();

	//CaptureRect();
	return;
}


static const int RADIUS = 2;
void CSchemiAnatomiciEditDlg::DrawPoint(CPoint p_ptWhere, COLORREF p_color)
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
void CSchemiAnatomiciEditDlg::DrawRetangle(CRect p_Rect, COLORREF p_color, BOOL p_bGhostColor)
{
	CClientDC dc(this);

	DrawRetangle(p_Rect.TopLeft(), p_Rect.BottomRight(), p_color, p_bGhostColor);
}

void CSchemiAnatomiciEditDlg::DrawRetangle(CPoint p_ptTopLeft, CPoint p_ptBottomRight, COLORREF p_color, BOOL p_bGhostColor)
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

void CSchemiAnatomiciEditDlg::OnBnClickedSave()
{
#define _STRLOG_0003 "CSchemiAnatomiciEditDlg::OnBnClickedSave"

	BOOL bSaved = FALSE;
	long lID = -1;

	int iTotRows = m_lstEtichetteAggiunta.GetCount();

	POSITION pos = m_lstEtichetteAggiunta.GetHeadPosition();

	while (pos != NULL)
	{
		CSchemiAnatomiciAggiuntoEtichetteSet setTemp;
		// pega as informações de cada linha do grid e coloca no setTemp
		CEtichetteAggiunta auxCurrent = m_lstEtichetteAggiunta.GetAt(pos);

		//dcp.SetTextColor(RGB_WHITE - m_lstEtichetteAggiunta.GetAt(pos).m_Color); // CALCULA A COR COMPLEMENTAR: ou seja, de MAIOR CONTRASTE
		//CRect rectTemp = m_lstEtichetteAggiunta.GetAt(pos).m_Rect - rectFrame.TopLeft(); // desconta a posição do FRAME HOST
		//dcp.Ellipse(rectTemp);
		//dcp.DrawText(m_lstEtichetteAggiunta.GetAt(pos).m_Label, rectTemp, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		if (auxCurrent.m_sAcao == _DBCTRL_NEW)
		{
			if (setTemp.OpenRecordset(_STRLOG_0003))
			{
				setTemp.AddNewRecordset(_STRLOG_0003);

				// seta as informações da list no recordset
				setTemp.m_lCONTATORE = 0;
				setTemp.m_lID_SCHEMI_ANATOMICI_AGGIUNTO = auxCurrent.m_lID_SCHEMI_ANATOMICI_AGGIUNTO;
				setTemp.m_lID_SCHEMI_ANATOMICI_ETICHETTE = auxCurrent.m_lID_SCHEMI_ANATOMICI_ETICHETTE;
				setTemp.m_sDESCRIZIONE = auxCurrent.m_sDESCRIZIONE;
				setTemp.m_lPUNTO_ALTO_SINISTRA_X = auxCurrent.m_pRectPUNTI.TopLeft().x; // x do ponto superior esquerdo do retangulo
				setTemp.m_lPUNTO_ALTO_SINISTRA_Y = auxCurrent.m_pRectPUNTI.TopLeft().y; // y do ponto superior esquerdo do retangulo
				setTemp.m_lPUNTO_BASSO_DESTRA_X = auxCurrent.m_pRectPUNTI.BottomRight().x; // x do ponto inferior direito do retangulo
				setTemp.m_lPUNTO_BASSO_DESTRA_Y = auxCurrent.m_pRectPUNTI.BottomRight().y; // y do ponto inferior direito do retangulo
				setTemp.m_lCOLORE = auxCurrent.m_lCOLORE;
				setTemp.m_bELIMINATO = FALSE;

				bSaved = setTemp.UpdateRecordset(_STRLOG_0003);

				// Update new ID in LIST
				m_lstEtichetteAggiunta.GetAt(pos).m_lCONTATORE = setTemp.GetLastAdd();
				m_lstEtichetteAggiunta.GetAt(pos).m_sAcao = _DBCTRL_SAME;

				setTemp.CloseRecordset(_STRLOG_0003);
			}
		}
		if (auxCurrent.m_sAcao == _DBCTRL_ALTERED || auxCurrent.m_sAcao == _DBCTRL_DELETED)
		{
			CString strFilter;
			strFilter.Format("CONTATORE=%li", auxCurrent.m_lCONTATORE);

			setTemp.SetOpenFilter(strFilter);

			if (setTemp.OpenRecordset(_STRLOG_0003))
			{
				if (!setTemp.IsBOF() && !setTemp.IsEOF())
				{
					if (setTemp.EditRecordset(_STRLOG_0003))
					{
						// seta as informações da list no recordset
						setTemp.m_lCONTATORE = auxCurrent.m_lCONTATORE;
						setTemp.m_lID_SCHEMI_ANATOMICI_AGGIUNTO = auxCurrent.m_lID_SCHEMI_ANATOMICI_AGGIUNTO;
						setTemp.m_lID_SCHEMI_ANATOMICI_ETICHETTE = auxCurrent.m_lID_SCHEMI_ANATOMICI_ETICHETTE;
						setTemp.m_sDESCRIZIONE = auxCurrent.m_sDESCRIZIONE;
						setTemp.m_lPUNTO_ALTO_SINISTRA_X = auxCurrent.m_pRectPUNTI.TopLeft().x; // x do ponto superior esquerdo do retangulo
						setTemp.m_lPUNTO_ALTO_SINISTRA_Y = auxCurrent.m_pRectPUNTI.TopLeft().y; // y do ponto superior esquerdo do retangulo
						setTemp.m_lPUNTO_BASSO_DESTRA_X = auxCurrent.m_pRectPUNTI.BottomRight().x; // x do ponto inferior direito do retangulo
						setTemp.m_lPUNTO_BASSO_DESTRA_Y = auxCurrent.m_pRectPUNTI.BottomRight().y; // y do ponto inferior direito do retangulo
						setTemp.m_lCOLORE = auxCurrent.m_lCOLORE;

						setTemp.SetFieldDirty(NULL, TRUE);
						setTemp.SetFieldDirty(&setTemp.m_lCONTATORE, FALSE);
						if (auxCurrent.m_sAcao == _DBCTRL_DELETED)
						{
							bSaved = setTemp.DeleteRecordset(_STRLOG_0003);
						}
						if (auxCurrent.m_sAcao == _DBCTRL_ALTERED)
						{
							bSaved = setTemp.UpdateRecordset(_STRLOG_0003);
						}
					}
				}
				setTemp.CloseRecordset(_STRLOG_0003);
			}
		}
		m_lstEtichetteAggiunta.GetNext(pos);
	}

	m_bAltered = FALSE;
}

void CSchemiAnatomiciEditDlg::OnBnClickedClose()
{
	while (m_bAltered)
	{
		if (theApp.AfxMessageBoxEndo(_T("Deseja salvar antes de sair?"), MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			OnBnClickedSave();
		else
			break;
	}

	EndDialog(m_iRetunState); // Set the return value returned by DoModal!

	//m_pParentWnd->SendMessage(WM_WAITINGDICOM_CLOSING);
	//CDialog::OnOK();
}

void CSchemiAnatomiciEditDlg::ImageAndEtichetteShow(long p_lID)
{
	// update actual Schemi
	BOOL bError = TRUE;
	CString strFilter;
	strFilter.Format("ID=%li", p_lID);

	if (!m_setSchemiAnatomici.RecordsetReOpen(bError, strFilter, "DESCRIZIONE DESC", "CSchemiAnatomiciEditDlg::ListGridSchemiAnatomiciEtichetteUpdateActual"))
	{
		m_setSchemiAnatomici.SetEmpty();
	}
	m_pSchemiAnatomiciActual = &(m_setSchemiAnatomici.m_pSchemiAnatomici);

	// Atualiza o title do form
	CString sAux;
	this->GetWindowTextA(sAux);
	sAux += +": "+m_pSchemiAnatomiciActual->m_sDescrizione;
	sAux.MakeUpper();
	this->SetWindowTextA(sAux);

	ImageShow(m_pSchemiAnatomiciActual->m_sImmagine_FullPath);

	RedrawWindow();
	DrawEtichetteAll(p_lID, COLORREF RGB_BLUE);
}

void CSchemiAnatomiciEditDlg::DrawEtichette(COLORREF p_cfCOLOR)
{
	// desenha cada retangulo
	CRect rectAux = CRect(
		m_pSchemiAnatomiciEtichetteActual->m_lPunto_Alto_Sinistra_X,
		m_pSchemiAnatomiciEtichetteActual->m_lPunto_Alto_Sinistra_Y,
		m_pSchemiAnatomiciEtichetteActual->m_lPunto_Basso_Destra_X,
		m_pSchemiAnatomiciEtichetteActual->m_lPunto_Basso_Destra_Y);

	CRect rectFrame;
	GetDlgItem(IDC_FRAME)->GetWindowRect(rectFrame);	// posição do frame na screen (fuul screen - tela inteira)	//DrawRetangle(rectFrame, RGB_RED);
	ScreenToClient(rectFrame);							// posição do frame na window continente (anfitriã)			//DrawRetangle(rectFrame, RGB_BLUE);

	// diferença entre a tela que cadastra e a tela que apresenta as etichettes
	rectAux.left -= m_diff;
	rectAux.right -= m_diff;

	DrawRetangle(rectAux, p_cfCOLOR, 0);
}

void CSchemiAnatomiciEditDlg::DrawEtichetteAll(long p_lID, COLORREF p_cfCOLOR, int p_iRedHighlighted) // p_iRedHighlighted== -1 if none
{
	CString sFilter;
	sFilter.Format("ID_SCHEMI_ANATOMICI=%li", p_lID);
	
	// update actual SchemiEtichette
	BOOL bError = TRUE;
	if (m_setSchemiAnatomiciEtichette.RecordsetReOpen(bError, sFilter, "ID DESC", "CSchemiAnatomiciEditDlg::ListGridSchemiAnatomiciEtichetteRiempi"))
	{
		while (!m_setSchemiAnatomiciEtichette.IsEOF())
		{
			m_pSchemiAnatomiciEtichetteActual = &(m_setSchemiAnatomiciEtichette.m_pSchemiAnatomiciEtichette);
			if (m_pSchemiAnatomiciEtichetteActual->m_lID == m_pCurrentEtichetteToInsert.m_lID_SCHEMI_ANATOMICI_ETICHETTE)
				DrawEtichette(RGB_RED);
			else
				DrawEtichette(RGB_BLUE);

			m_setSchemiAnatomiciEtichette.MoveNext();
		}
	}
}

void CSchemiAnatomiciEditDlg::OnBnClickedExp()
{
	if (m_bAltered)
		OnBnClickedSave();

	bOnBnClickedShowEtichetteShowOrHide = FALSE;
	RedrawWindow();

	BOOL bExportOK = ImageMergeLayersAndExportToAlbum();

	bOnBnClickedShowEtichetteShowOrHide = TRUE;
	RedrawWindow();

	if (bExportOK)
		OnBnClickedClose();
}


void CSchemiAnatomiciEditDlg::OnBnClickedHlp()
{
	// HELP DA TELA
	CString auxMsg;
	auxMsg.Format("%s\n%s\n%s\n%s\n%s",
		"EDIÇÃO DO ESQUEMA ANATÔMICO\nINSERÇÃO DE RÓTULOS/LABELS:",
		"\nNA IMAGEM:",
		"1) Clique do Botão ESQUERDO do Mouse para SELECIONAR o rótulo/label que deseja aplicar (retângulos azuis);",
		"2) Clique do Botão DIREITO do Mouse para APLICAR o rótulo selecionado onde e quantas vezes desejar dentro da imagem;",
		"3) Clique do Botão ESQUERDO do Mouse para APAGAR um rótulo/label já aplicado sobre imagem (circunferências coloridas)."
		);
	theApp.AfxMessageBoxEndo(auxMsg);
}
