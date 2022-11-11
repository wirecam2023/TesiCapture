// ImageSimple2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Endox.h"
#include "ImageSimple2Dlg.h"
#include "afxdialogex.h"
#include "MaximizeDlg.h"
#include "Dib.h"

// CImageSimple2Dlg dialog

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CImageSimple2Dlg, CEndoxResizableDlg)

CImageSimple2Dlg::CImageSimple2Dlg(CWnd* pParent, CEsamiView* pEsamiView, BOOL bAjustToParent, BOOL bIsReferto)
: CEndoxResizableDlg(CImageSimple2Dlg::IDD, pParent)
{
	theApp.m_lInstanceCountCImageSimple2Dlg = 1; //Gabriel BUG 6225 - Lista DO

	m_bAjustToParent = bAjustToParent;
	if (bAjustToParent)
	{
		CRect rect;
		pParent->GetWindowRect(rect);
		m_iParentX = rect.TopLeft().x;
		m_iParentY = rect.TopLeft().y;
		m_iParentWidth = rect.Width();
		m_iParentHeight = rect.Height();
	}
	else
	{
		m_iParentX = 0;
		m_iParentY = 0;
		m_iParentWidth = 0;
	}

	m_pEsamiView = pEsamiView;
	m_lEsame = pEsamiView->m_pEsamiSet->m_lContatore;
	m_lPaziente = pEsamiView->m_pEsamiSet->m_lPaziente;

	m_nNumPage = 0;
	m_nTotPage = 0;
	m_bReloadFrame = TRUE;
	m_sCurImgPath = ""; //Julio - BUG 4392 Enriquecimento da ferramenta de edição de laudo 

	m_pDib = new CDib;	

	m_bIsReferto = bIsReferto;
}

//Gabriel BUG 6225 - Lista DO
void CImageSimple2Dlg::PostNcDestroy()
{
	if (m_pDib)
	{
		m_pDib->ReleaseContents();
		delete m_pDib;
		m_pDib = NULL;
	}

	theApp.m_lInstanceCountCImageSimple2Dlg = 0;

	CEndoxResizableDlg::PostNcDestroy();
	delete this;
}

CImageSimple2Dlg::~CImageSimple2Dlg()
{
}

void CImageSimple2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ctrlButtonCancel);

	DDX_Control(pDX, IDC_BUTTON_FIRST, m_ctrlButtonFirst);
	DDX_Control(pDX, IDC_BUTTON_PREV, m_ctrlButtonPrev);
	DDX_Control(pDX, IDC_BUTTON_NEXT, m_ctrlButtonNext);
	DDX_Control(pDX, IDC_BUTTON_LAST, m_ctrlButtonLast);

	DDX_Control(pDX, IDC_IMAGEBOX, m_ctrlImageFrame);
}
BOOL CImageSimple2Dlg::OnInitDialog()
{
	m_ctrlButtonFirst.AutoLoad(IDC_BUTTON_FIRST, this);
	m_ctrlButtonPrev.AutoLoad(IDC_BUTTON_PREV, this);
	m_ctrlButtonNext.AutoLoad(IDC_BUTTON_NEXT, this);
	m_ctrlButtonLast.AutoLoad(IDC_BUTTON_LAST, this);

	CEndoxResizableDlg::OnInitDialog();

	AddAnchor(IDOK, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDCANCEL, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDC_IMAGEBOX, CSize(0, 0), CSize(100, 100));

	CImgList listImg;

	m_pEsamiView->m_pImgManager->SetCurrentIDs(m_lPaziente, m_lEsame);
	int nImages = m_pEsamiView->m_pImgManager->GetImgList(&listImg);

	POSITION pos = listImg.GetHeadPosition();	//BEGIN REMOVE VIDEOS AND MTIFF
	while (pos != NULL)
	{
		IMG imgTemp = listImg.GetAt(pos);
		if ((imgTemp.type != _image_))
		{
			POSITION posTemp = pos;
			listImg.GetNext(pos);
			listImg.RemoveAt(posTemp);
		}
		else
		{
			listImg.GetNext(pos);
		}
	}
	m_nTotPage = listImg.GetCount();  // Marvel Carvalho BUG 4269 - Dialog ImageSimple2Dlg ignora album com 1 imagem
	m_ImgList = listImg;			  //END REMOVE VIDEOS AND MTIFF

	pos = m_ImgList.GetHeadPosition();
	while (pos != NULL)
	{
		m_nNumPage++;
		m_ImgList.GetNext(pos);
	}
	m_nNumPage--;

	AjustToParent();

	if (m_nTotPage <= 0)
	{
		//Gabriel BUG 6225 - Lista DO
		if (!theApp.m_bConfigFormRefertoBtnImgAutomated)
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUM_IMMAGINI_VUOTO), MB_ICONINFORMATION);

		OnCancel();
		return FALSE;
	}
	else
	{
		OnBnClickedButtonFirst();

		if (m_bIsReferto)
		{
			if (theApp.m_sConfigFormRefertoBtnImgOpenWhere == "MONITOR #02")	// 'DEFAULT' OU 'MONITOR #02'
				CenterWndInSecondScreen(this, FALSE);
			else
				CenterWndInFirstScreen(this, FALSE);
		}
		else
		{
			if (theApp.m_sConfigFormAlbumImgBtnImgOpenWhere == "MONITOR #02")	// 'DEFAULT' OU 'MONITOR #02'
				CenterWndInSecondScreen(this, FALSE);
			else
				CenterWndInFirstScreen(this, FALSE);
		}
		return TRUE;
	}
}

BOOL CImageSimple2Dlg::PreTranslateMessage(MSG* pMsg)
{
	BOOL bReturn = FALSE;

	if (pMsg->message == WM_KEYDOWN)
	{
		if ((pMsg->wParam == VK_LEFT))
		{
			OnBnClickedButtonPrev();
			bReturn = TRUE;
		}
		if ((pMsg->wParam == VK_RIGHT))
		{
			OnBnClickedButtonNext();
			bReturn = TRUE;
		}
	}
	else
	{
		if (m_bReloadFrame)
		{
			m_bReloadFrame = FALSE;
			PrepareRectangle();
			OnBnClickedButtonFirst();
		}
	}

	if (!bReturn)
		bReturn = CEndoxResizableDlg::PreTranslateMessage(pMsg);

	return bReturn;
}
BEGIN_MESSAGE_MAP(CImageSimple2Dlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, &CImageSimple2Dlg::OnBnClickedButtonFirst)
	ON_BN_CLICKED(IDC_BUTTON_PREV, &CImageSimple2Dlg::OnBnClickedButtonPrev)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CImageSimple2Dlg::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_LAST, &CImageSimple2Dlg::OnBnClickedButtonLast)
	ON_STN_DBLCLK(IDC_IMAGEBOX, &CImageSimple2Dlg::OnStnDblclickImagebox)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, OnOk) //Gabriel BUG 6225 - Lista DO
	ON_COMMAND(IDCANCEL, OnCancel) //Gabriel BUG 6225 - Lista DO
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


void CImageSimple2Dlg::OnBnClickedButtonFirst()
{
	m_nNumPage = 0;

	BOOL bResult = TRUE;
	bResult = CaricaImmagine();
	if (bResult)
		AutoRedraw();

	UpdateButtonsEnabling();
}

void CImageSimple2Dlg::OnBnClickedButtonPrev()
{
	m_nNumPage = (m_nNumPage > 0) ? (m_nNumPage - 1) : 0;

	BOOL bResult = TRUE;
	bResult = CaricaImmagine();
	if (bResult)
		AutoRedraw();

	UpdateButtonsEnabling();
}


void CImageSimple2Dlg::OnBnClickedButtonNext()
{
	m_nNumPage = (m_nNumPage < m_nTotPage) ? (m_nNumPage + 1) : m_nTotPage;

	BOOL bResult = TRUE;
	bResult = CaricaImmagine();
	if (bResult)
		AutoRedraw();

	UpdateButtonsEnabling();
}


void CImageSimple2Dlg::OnBnClickedButtonLast()
{
	m_nNumPage = m_nTotPage;

	BOOL bResult = TRUE;
	bResult = CaricaImmagine();
	if (bResult)
		AutoRedraw();

	UpdateButtonsEnabling();
}

BOOL CImageSimple2Dlg::CaricaImmagine()
{
	BOOL bReturn = FALSE;
	POSITION pos = m_ImgList.FindIndex(m_nNumPage);

	if (pos != NULL)
	{
		m_pEsamiView->m_pImgManager->SetCurrentIDs(m_lPaziente, m_lEsame);
		HBITMAP hBitmap = m_pEsamiView->m_pImgManager->GetImg(m_ImgList.GetAt(pos).img.lID, FALSE, FALSE, FALSE);

		if (hBitmap != NULL)
		{
			m_pDib->Attach(CDib::BitmapToDIB(hBitmap, NULL), TRUE);
			//m_ctrlImageFrame.SetBitmap(hBitmap);

			DeleteObject(hBitmap);

			m_sCurImgPath = m_pEsamiView->m_pImgManager->GetFullPath(m_ImgList.GetAt(pos).img.lID); //Julio - BUG 4392 Enriquecimento da ferramenta de edição de laudo 

			bReturn = TRUE;
		}
	}
	return bReturn;
}

void CImageSimple2Dlg::UpdateButtonsEnabling()
{
	GetDlgItem(IDC_BUTTON_FIRST)->EnableWindow(m_nNumPage > 0);
	GetDlgItem(IDC_BUTTON_PREV)->EnableWindow(m_nNumPage > 0);
	GetDlgItem(IDC_BUTTON_NEXT)->EnableWindow(m_nNumPage < m_nTotPage);
	GetDlgItem(IDC_BUTTON_LAST)->EnableWindow(m_nNumPage < m_nTotPage);
	GetDlgItem(IDOK)->SetFocus();
}

void CImageSimple2Dlg::OnStnDblclickImagebox()
{
	if (m_pDib && m_pDib->IsValidDib())
	{
		CRect ImgRect;

		m_ctrlImageFrame.GetWindowRect(&ImgRect);
		ScreenToClient(&ImgRect);

		CMaximizeDlg dlg(this, m_pDib);
		dlg.DoModal();
	}
}
void CImageSimple2Dlg::AjustToParent()
{
	if (m_bAjustToParent)
	{
		CRect rect;
		GetWindowRect(&rect);

		int iWidthDiference = (m_iParentWidth - rect.Width());
		
		BOOL bParentIsLarger = FALSE;
		if (iWidthDiference > 0)		
			bParentIsLarger = TRUE;		


		MoveWindow(
			bParentIsLarger ? 
				(m_iParentX - (iWidthDiference / 2))			 
				: 
				(m_iParentX + (iWidthDiference / 2)), 
			m_iParentY + m_iParentHeight + 10, 
			rect.Width(), 
			rect.Height(), 
			FALSE);
	}
	else
	{
		CenterWindow();
	}
}
void CImageSimple2Dlg::AutoRedraw()
{
	CRect ImgRect;

	m_ctrlImageFrame.GetWindowRect(&ImgRect);
	ScreenToClient(&ImgRect);

	RedrawWindow(&ImgRect, NULL, RDW_INVALIDATE | RDW_NOERASE | RDW_UPDATENOW);

	CString sWindowTitle;
	sWindowTitle.Format("Imagem (%d / %d)", m_nNumPage+1, m_nTotPage); // Marvel Carvalho - Bug 4269 Dialog ImageSimple2Dlg ignora album com 1 imagem
	SetWindowText(sWindowTitle);
}

void CImageSimple2Dlg::OnPaint()
{
	CPaintDC dc(this);

	if (m_pDib && m_pDib->IsValidDib())
	{
		CPoint	ptOffset;
		CRect	rectSource;
		CRect	ImgRect;

		m_ctrlImageFrame.GetWindowRect(&ImgRect);
		ScreenToClient(&ImgRect);

		if ((m_nTGAWidth < m_nDLGWidth) && (m_nTGAHeight < m_nDLGHeight))
		{
			// 1:1 //

			::PatBlt(dc.GetSafeHdc(), ImgRect.left, ImgRect.top, m_nDLGWidth, m_nDLGHeight, BLACKNESS);

			ptOffset.x = 0;
			ptOffset.y = 0;

			rectSource.left = ptOffset.x;
			rectSource.top = ptOffset.y;
			rectSource.right = min(rectSource.left + ImgRect.Width(), m_DibRectSource.Width());
			rectSource.bottom = min(rectSource.top + ImgRect.Height(), m_DibRectSource.Height());

			m_pDib->PaintDIB(dc.GetSafeHdc(), m_DibRectScreen, rectSource, 0);
		}
		else
		{
			// fit in window //

			if ((m_nDLGWidth != m_nTGAWidth) || (m_nDLGHeight != m_nTGAHeight))
			{
				::PatBlt(dc.GetSafeHdc(), ImgRect.left, ImgRect.top, m_nDLGWidth, m_nDLGHeight, BLACKNESS);			
			}

			m_pDib->PaintDIB(dc.GetSafeHdc(), m_DibRectScreen, m_DibRectSource, 0);
		}
	}
}
void CImageSimple2Dlg::PrepareRectangle()
{
	m_nTGAWidth = m_pDib->Width();
	m_nTGAHeight = m_pDib->Height();

	CRect	ImgRect;
	m_ctrlImageFrame.GetWindowRect(&ImgRect);
	ScreenToClient(&ImgRect);

	m_nDLGWidth = ImgRect.Width();
	m_nDLGHeight = ImgRect.Height();

	CRect 	ScreenRect(0, 0, m_nDLGWidth, m_nDLGHeight);
	CRect 	DibRect(0, 0, m_nTGAWidth, m_nTGAHeight);
	CRect 	FitRect;

	m_ctrlImageFrame.GetWindowRect(&ImgRect);
	ScreenToClient(&ImgRect);
	ScreenRect.OffsetRect(ImgRect.left, ImgRect.top);

	if ((m_nTGAWidth < m_nDLGWidth) && (m_nTGAHeight < m_nDLGHeight))
	{
		// 1:1 //

		// centraggio sull'asse x //
		ScreenRect.left += (ScreenRect.Width() - DibRect.Width()) / 2;
		ScreenRect.right = ScreenRect.left + DibRect.Width();

		// centraggio sull'asse y //
		ScreenRect.top += (ScreenRect.Height() - DibRect.Height()) / 2;
		ScreenRect.bottom = ScreenRect.top + DibRect.Height();
	}
	else
	{
		// fit in window //

		// in altezza in base alla larghezza //
		FitRect.left = 0;
		FitRect.top = 0;
		FitRect.right = FitRect.left + m_nDLGWidth;
		FitRect.bottom = FitRect.top + (int)(((double)m_nTGAHeight * (double)m_nDLGWidth) / ((double)m_nTGAWidth));

		// se la proporzione è inversa //
		if (FitRect.Height() > m_nDLGHeight)
		{
			// in larghezza in base all'altezza //
			FitRect.bottom = FitRect.top + m_nDLGHeight;
			FitRect.right = FitRect.left + (int)(((double)m_nTGAWidth * (double)m_nDLGHeight) / ((double)m_nTGAHeight));
		}

		// centraggio sulla pagina //
		ScreenRect.left += (ScreenRect.Width() - FitRect.Width()) / 2;
		ScreenRect.right = ScreenRect.left + FitRect.Width();
		ScreenRect.top += (ScreenRect.Height() - FitRect.Height()) / 2;
		ScreenRect.bottom = ScreenRect.top + FitRect.Height();
	}

	m_DibRectSource = DibRect;
	m_DibRectScreen = ScreenRect;
}

//Gabriel BUG 6225 - Lista DO
void CImageSimple2Dlg::OnOk()
{
	DestroyWindow();
}

//Gabriel BUG 6225 - Lista DO
void CImageSimple2Dlg::OnCancel()
{
	DestroyWindow();
}

BOOL CImageSimple2Dlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (zDelta == -120)
	{
		OnBnClickedButtonNext();
		return TRUE;
	}
	else if (zDelta == 120)
	{
		OnBnClickedButtonPrev();
		return TRUE;
	}
	else
		return TRUE;

	CDialog::OnMouseWheel(nFlags, zDelta, pt);

	return CEndoxResizableDlg::OnMouseWheel(nFlags, zDelta, pt);
}
