#include "stdafx.h"
#include "Endox.h"
#include "AcqFromDiskDermoxDlg.h"

#include <io.h>
#include <math.h>

#include "DLL_Imaging\h\ImgArchive.h"

#include "MisureConfig\SerializerDLL.h"

#include "Calib.h"
#include "CalibList.h"
#include "Common.h"
#include "EditStringDlg.h"
#include "EsamiView.h"
#include "LogFileWriter.h"
#include "MaximizeDlg.h"
#include "MmSystem.h"
#include "PuntiPazienteSet.h"
#include "PuntiSediSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define RAGGIO_PUNTO_1 3
#define RAGGIO_PUNTO_2 6

IMPLEMENT_DYNAMIC(CAcqFromDiskDermoxDlg, CEndoxResizableDlg)

CAcqFromDiskDermoxDlg::CAcqFromDiskDermoxDlg(CWnd* pParent, CEsamiView* pEsamiView, CString sPhotoFile, BOOL bDeleteAfterAcquisition)
	: CEndoxResizableDlg(CAcqFromDiskDermoxDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
	m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore);

	m_rectFrameLive = CRect(0, 0, 0, 0);
	m_rectFrameSagoma = CRect(0, 0, 0, 0);
	m_rectPaintSagoma = CRect(0, 0, 0, 0);
	m_rectFrameZoom = CRect(0, 0, 0, 0);

	m_iCurSelPointIndex = -1;
	m_iCurSelPointX = -1;
	m_iCurSelPointY = -1;

	m_lIDSede = 0;

	m_sCalib = "";

	m_sPhotoFile = sPhotoFile;
	m_bDeleteAfterAcquisition = bDeleteAfterAcquisition;

	// --- //

	m_bFillingList = TRUE;
}

CAcqFromDiskDermoxDlg::~CAcqFromDiskDermoxDlg()
{
}

BEGIN_MESSAGE_MAP(CAcqFromDiskDermoxDlg, CEndoxResizableDlg)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	
	ON_BN_CLICKED(IDC_BTN_PHOTO, OnBnClickedBtnPhoto)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBnClickedBtnExit)

	ON_CBN_SELCHANGE(IDC_COMBO_CALIB, OnCbnSelchangeComboCalib)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_POINTS, OnLvnItemchangedListPoints)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_IMAGES, OnNMDblClkListImages)
END_MESSAGE_MAP()

void CAcqFromDiskDermoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN_PHOTO, m_ctrlBtnPhoto);

	DDX_Control(pDX, IDC_BTN_EXIT, m_ctrlBtnExit);

	DDX_Control(pDX, IDC_COMBO_CALIB, m_ctrlComboCalib);

	DDX_Control(pDX, IDC_LIST_POINTS, m_ctrlListPoints);
	DDX_Control(pDX, IDC_LIST_IMAGES, m_ctrlListImages);

	DDX_Control(pDX, IDC_STATIC_SAGOMA, m_ctrlFrameSagoma);
	DDX_Control(pDX, IDC_STATIC_LIVE, m_ctrlFrameLive);
	DDX_Control(pDX, IDC_STATIC_ZOOM, m_ctrlFrameZoom);
	DDX_Control(pDX, IDC_STATIC_SEDE1, m_ctrlFrameSede);

	DDX_Control(pDX, IDC_STATIC_SEDE2, m_ctrlStaticSede);

	DDX_Control(pDX, IDC_STATIC_FRAME_CALIB, m_ctrlStaticFrameCalib);
}

void CAcqFromDiskDermoxDlg::OnCancel()
{
}

BOOL CAcqFromDiskDermoxDlg::OnInitDialog()
{
	CEndoxResizableDlg::OnInitDialog();

	BOOL bOk = FALSE;

	char szPathImm[MAX_PATH];
	char szPathMin[MAX_PATH];
	if (CImgArchive(&theApp.m_dbEndox).GetArchivePrimary(szPathImm, szPathMin, MAX_PATH))
	{
		CString fileSagomeName = "sagome.reg";

		CString sFileSagome;
		sFileSagome.Format("%s\\Organ\\sagome.org", szPathImm);

		CString sFileSedi;
		sFileSedi.Format("%s\\Organ\\%s", szPathImm, fileSagomeName);

		if (_access(m_sPhotoFile, 00) == 0)
		{
			if (_access(sFileSagome, 00) == 0)
			{
				if (_access(sFileSedi, 00) == 0)
				{
					HBITMAP hBit;

					// immagine da importare //
					if (m_pEsamiView->m_pImgManager->LoadLocalImageEx(m_sPhotoFile, &hBit) > 0)
						if (hBit != INVALID_HANDLE_VALUE)
							bOk = m_dibImageFile.Attach(CDib::BitmapToDIB(hBit, NULL), TRUE);
					DeleteObject(hBit);

					// sagome //
					if (m_pEsamiView->m_pImgManager->LoadLocalImageEx(sFileSagome, &hBit) > 0)
						if (hBit != INVALID_HANDLE_VALUE)
							bOk = m_dibSagome.Attach(CDib::BitmapToDIB(hBit, NULL), TRUE);
					DeleteObject(hBit);

					// sedi //
					if (m_pEsamiView->m_pImgManager->LoadLocalImageEx(sFileSedi, &hBit) > 0)
						if (hBit != INVALID_HANDLE_VALUE)
							bOk = m_dibSedi.Attach(CDib::BitmapToDIB(hBit, NULL), TRUE);
					DeleteObject(hBit);
				}
				else
				{
					CString strError;
					strError.Format(theApp.GetMessageString(IDS_FILE_SAGOME_NON_TROVATO), sFileSedi);
					theApp.AfxMessageBoxEndo(strError);
				}
			}
			else
			{
				CString strError;
				strError.Format(theApp.GetMessageString(IDS_FILE_SAGOME_NON_TROVATO), sFileSagome);
				theApp.AfxMessageBoxEndo(strError);
			}
		}
		else
		{
			CString strError;
			strError.Format(theApp.GetMessageString(IDS_FILE_IMMAGINE_NON_TROVATO), m_sPhotoFile);
			theApp.AfxMessageBoxEndo(strError);
		}
	}
	else
	{
		ASSERT(FALSE);
	}

	if (bOk)
	{
		AddAnchor(IDC_BTN_EXIT, CSize(50, 100), CSize(100, 100));
		AddAnchor(IDC_BTN_PHOTO, CSize(50, 100), CSize(100, 100));

		AddAnchor(IDC_COMBO_CALIB, CSize(50, 100), CSize(100, 100));

		AddAnchor(IDC_LIST_POINTS, CSize(0, 0), CSize(50, 0));
		AddAnchor(IDC_LIST_IMAGES, CSize(0, 100), CSize(50, 100));

		AddAnchor(IDC_STATIC_SAGOMA, CSize(0, 0), CSize(50, 100));
		AddAnchor(IDC_STATIC_LIVE, CSize(50, 0), CSize(100, 100));
		AddAnchor(IDC_STATIC_ZOOM, CSize(0, 100), CSize(0, 100));
		AddAnchor(IDC_STATIC_SEDE1, CSize(0, 100), CSize(0, 100));

		AddAnchor(IDC_STATIC_SEDE2, CSize(0, 100), CSize(0, 100));

		AddAnchor(IDC_STATIC_FRAME_CALIB, CSize(50, 100), CSize(100, 100));

		//

		m_ctrlStaticSede.SetFont(&theApp.m_fontBold);
		m_ctrlBtnPhoto.SetFont(&theApp.m_fontBold);
		m_ctrlStaticFrameCalib.SetFont(&theApp.m_fontBold);
		m_ctrlComboCalib.SetFont(&theApp.m_fontBold);
		m_ctrlBtnExit.SetFont(&theApp.m_fontBold);

		//

		//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
		SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

		//

		m_ctrlListPoints.SetExtendedStyle(m_ctrlListPoints.GetExtendedStyle() | LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_LABELTIP);
		m_ctrlListPoints.InsertColumn(0, "", LVCFMT_LEFT, 0); // empty //
		m_ctrlListPoints.InsertColumn(1, "", LVCFMT_RIGHT, 0); // numero //
		m_ctrlListPoints.InsertColumn(2, "Sede", LVCFMT_LEFT, 0); // sede //
		m_ctrlListPoints.InsertColumn(3, "Pattern", LVCFMT_LEFT, 0); // pattern //
		m_ctrlListPoints.InsertColumn(4, "Asportazione", LVCFMT_LEFT, 0); // asportazione //
		m_ctrlListPoints.InsertColumn(5, "", LVCFMT_LEFT, 0); // empty //

		//

		m_listImages.Create(HSIZE_PAL_4, VSIZE_PAL_4, ILC_COLOR32, 0, 1);
		m_ctrlListImages.SetExtendedStyle(m_ctrlListImages.GetExtendedStyle() | LVS_EX_BORDERSELECT);
		m_ctrlListImages.SetImageList(&m_listImages, LVSIL_NORMAL);
		m_ctrlListImages.SetIconSpacing(HSIZE_PAL_4 + 5, VSIZE_PAL_4 + 5);

		//

		int nIndex = 0;
		POSITION pos1 = theApp.m_pListCalib->GetFirstCalibPos();
		while(pos1 != NULL)
		{
			CCalib* pCalib = theApp.m_pListCalib->GetNextCalib(pos1);

			m_ctrlComboCalib.InsertString(nIndex, pCalib->m_strName);
			m_ctrlComboCalib.SetItemDataPtr(nIndex, pCalib);

			nIndex++;
		}

		//
		LoadSettings();

		//
		CString strFilter;
		strFilter.Format("IDPaziente=%li", m_pEsamiView->m_pPazientiSet->m_lContatore);

		CPuntiPazienteSet setPunti;
		setPunti.SetOpenFilter(strFilter);
		if (setPunti.OpenRecordset("CAcqFromDiskDermoxDlg::OnInitDialog"))
		{
			while(!setPunti.IsEOF())
			{
				tagPuntiDermox tagTemp;
				tagTemp.lIDPunto = setPunti.m_lID;
				tagTemp.ptPunto.x = setPunti.m_lX;
				tagTemp.ptPunto.y = setPunti.m_lY;
				tagTemp.lNumeroDermox = setPunti.m_lNumeroDermox;
				sprintf_s(tagTemp.szSede, 255, "%s", setPunti.m_sSede);
				sprintf_s(tagTemp.szPattern, 255, "%s", GetTextPattern(setPunti.m_lPattern));
				tagTemp.bAsportazione = setPunti.m_bAsportazione;

				m_listPunti.AddTail(tagTemp);

				setPunti.MoveNext();
			}

			setPunti.CloseRecordset("CAcqFromDiskDermoxDlg::OnInitDialog");
		}

		//
		CPuntiSediSet setSedi;
		if (setSedi.OpenRecordset("CAcqFromDiskDermoxDlg::OnInitDialog"))
		{
			while(!setSedi.IsEOF())
			{
				tagSede tagTemp;

				tagTemp.m_lID = setSedi.m_lID;
				tagTemp.m_sSede = setSedi.m_sSede;
				tagTemp.m_sSede.MakeUpper();

				m_listSedi.AddTail(tagTemp);

				setSedi.MoveNext();
			}

			setSedi.CloseRecordset("CAcqFromDiskDermoxDlg::OnInitDialog");
		}

		//
		m_ctrlListPoints.SetRedraw(FALSE);
		m_ctrlListPoints.DeleteAllItems();

		int nItem = 0;
		POSITION pos2 = m_listPunti.GetHeadPosition();
		while(pos2 != NULL)
		{
			CString strTemp;
			tagPuntiDermox tagTemp = m_listPunti.GetAt(pos2);

			m_ctrlListPoints.InsertItem(nItem, "");
			m_ctrlListPoints.SetItemData(nItem, (DWORD)tagTemp.lIDPunto);

			strTemp.Format("%li", tagTemp.lNumeroDermox);
			m_ctrlListPoints.SetItemText(nItem, 1, strTemp);

			m_ctrlListPoints.SetItemText(nItem, 2, tagTemp.szSede);

			m_ctrlListPoints.SetItemText(nItem, 3, tagTemp.szPattern);

			m_ctrlListPoints.SetItemText(nItem, 4, tagTemp.bAsportazione ? theApp.GetMessageString(IDS_YES) : theApp.GetMessageString(IDS_NO));

			nItem++;
			m_listPunti.GetNext(pos2);
		}

		m_ctrlListPoints.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListPoints.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListPoints.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListPoints.SetColumnWidth(4, LVSCW_AUTOSIZE_USEHEADER);
		m_ctrlListPoints.SetRedraw(TRUE);

		m_bFillingList = FALSE;

		if (m_iCurSelPointIndex >= 0)
		{
			m_ctrlListPoints.SetItemState(m_iCurSelPointIndex, LVIS_SELECTED, LVIS_SELECTED);
			m_ctrlListPoints.EnsureVisible(m_iCurSelPointIndex, FALSE);
		}

		//
		theApp.LocalizeDialog(this, CAcqFromDiskDermoxDlg::IDD, "AcqFromDiskDermoxDlg");

		//
		m_ctrlBtnPhoto.SetWindowText(theApp.GetMessageString(IDS_ACQUISIZIONE_IMMAGINE3));
	}
	else
	{
		m_dibImageFile.ReleaseContents();
		m_dibImageFile.Detach();

		m_dibSagome.ReleaseContents();
		m_dibSagome.Detach();

		m_dibSedi.ReleaseContents();
		m_dibSedi.Detach();

		EndDialog(IDCANCEL);
	}

	return TRUE;
}

void CAcqFromDiskDermoxDlg::OnOK()
{
}

void CAcqFromDiskDermoxDlg::OnBnClickedBtnExit()
{
	if (m_bDeleteAfterAcquisition)
		DeleteFile(m_sPhotoFile);

	CResizableDialog::OnCancel();
}

void CAcqFromDiskDermoxDlg::OnBnClickedBtnPhoto()
{
	//
	BeginWaitCursor();

	// creo il relativo file della calibrazione //
	int nIndex = m_ctrlComboCalib.GetCurSel();
	if (nIndex >= 0)
	{
		CCalib* pCalib = (CCalib*)m_ctrlComboCalib.GetItemDataPtr(nIndex);

		if (pCalib != NULL)
			SetCalib(m_sPhotoFile, pCalib);
	}

	// importo il tutto //
	long lIDImmagineImportata = ImportaImmagine();

	// aggiorno la finestra delle immagini //
	if (lIDImmagineImportata > 0)
		CaricaImmaginiPunto();

	//
	EndWaitCursor();

	//
	CResizableDialog::OnOK();
}

void CAcqFromDiskDermoxDlg::OnCbnSelchangeComboCalib()
{
	CString sSection = "SorgenteDermox10";

	int nTemp = m_ctrlComboCalib.GetCurSel();
	if (nTemp >= 0)
	{
		CString sTemp;
		m_ctrlComboCalib.GetLBText(nTemp, sTemp);
		WritePrivateProfileString(sSection, "Calib", sTemp, theApp.m_sFileConfig);
	}
}

void CAcqFromDiskDermoxDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	point.x++;
	point.y++;
	if (m_rectPaintSagoma.PtInRect(point))
	{
		point = ScreenToImage(point);
		SelezionaPunto(point);
	}
}

void CAcqFromDiskDermoxDlg::OnLvnItemchangedListPoints(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (!m_bFillingList)
	{
		BeginWaitCursor();

		POSITION pos1 = m_ctrlListPoints.GetFirstSelectedItemPosition();
		if (pos1 != NULL)
		{
			m_iCurSelPointIndex = m_ctrlListPoints.GetNextSelectedItem(pos1);

			POSITION pos2 = m_listPunti.FindIndex(m_iCurSelPointIndex);
			m_iCurSelPointX = m_listPunti.GetAt(pos2).ptPunto.x;
			m_iCurSelPointY = m_listPunti.GetAt(pos2).ptPunto.y;

			InvalidateRect(m_rectFrameSagoma, FALSE);
			InvalidateRect(m_rectFrameZoom, FALSE);
		}
		else
		{
			m_iCurSelPointIndex = -1;
			m_iCurSelPointX = -1;
			m_iCurSelPointY = -1;

			m_lIDSede = 0;

			InvalidateRect(m_rectFrameSagoma, FALSE);
			InvalidateRect(m_rectFrameZoom, FALSE);
		}

		CaricaDatiPunto();
		CaricaImmaginiPunto();

		EndWaitCursor();
	}
}

void CAcqFromDiskDermoxDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CEndoxResizableDlg::OnMouseMove(nFlags, point);

	// calcolo l'area del rect di zoom //
	InvalidateRect(m_rectFrameZoom, FALSE);
}

void CAcqFromDiskDermoxDlg::OnNMDblClkListImages(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos = m_ctrlListImages.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int iCurSel = m_ctrlListImages.GetNextSelectedItem(pos);
		long lIDImmagine = (long)m_ctrlListImages.GetItemData(iCurSel);

		if (lIDImmagine > 0)
		{
			BeginWaitCursor();
			HBITMAP hTemp = m_pEsamiView->m_pImgManager->GetImg(lIDImmagine, FALSE, FALSE, FALSE);
			EndWaitCursor();

			if (hTemp != NULL)
			{
				CDib dibTemp;
				dibTemp.Attach(CDib::BitmapToDIB(hTemp, NULL), TRUE);

				CMaximizeDlg dlgTemp(this, &dibTemp);
				dlgTemp.DoModal();

				DeleteObject(hTemp);
			}
		}
	}
}

void CAcqFromDiskDermoxDlg::OnPaint() 
{
	CPaintDC dc(this);

	///////////////////////////
	// IMMAGINE DA IMPORTARE //
	///////////////////////////

	m_dibImageFile.PaintDIB(&dc, m_rectFrameLive);

	///////////////////
	// SAGOMA GRANDE //
	///////////////////

	// disegno la dib //
	m_rectPaintSagoma = m_dibSagome.PaintDIBSagome(&dc, m_rectFrameSagoma);
	// TRACE("   SAGOME IN L%04li R%04li T%04li B%04li\n", m_rectSagoma.left, m_rectSagoma.right, m_rectSagoma.top, m_rectSagoma.bottom);

	/////////////////////////
	// PUNTI SAGOMA GRANDE //
	/////////////////////////

	CPen penSel(PS_SOLID, 1, RGB_RED);
	CBrush brushSel(RGB_RED);
	CPen penNormal(PS_SOLID, 1, RGB_BLUE);
	CBrush brushNormal(RGB_BLUE);
	CPen penAsportaz(PS_SOLID, 1, RGB_BLACK);
	CBrush brushAsportaz(RGB_BLACK);
	COLORREF crOldColor;

	dc.SetBkMode(TRANSPARENT);

	int i = 0;
	POSITION pos = m_listPunti.GetHeadPosition();
	while(pos != NULL)
	{
		CPen* pOldPen;
		CBrush* pOldBrush;
		if (i == m_iCurSelPointIndex)
		{
			pOldPen = dc.SelectObject(&penSel);
			pOldBrush = dc.SelectObject(&brushSel);
			crOldColor = dc.SetTextColor(RGB_RED);
		}
		else
		{
			if (m_listPunti.GetAt(pos).bAsportazione)
			{
				pOldPen = dc.SelectObject(&penAsportaz);
				pOldBrush = dc.SelectObject(&brushAsportaz);
				crOldColor = dc.SetTextColor(RGB_BLACK);
			}
			else
			{
				pOldPen = dc.SelectObject(&penNormal);
				pOldBrush = dc.SelectObject(&brushNormal);
				crOldColor = dc.SetTextColor(RGB_BLUE);
			}
		}

		CPoint ptToPaint = m_listPunti.GetAt(pos).ptPunto;
		ptToPaint = ImageToScreen(ptToPaint);

		CRect rectTemp(ptToPaint.x - RAGGIO_PUNTO_1, ptToPaint.y - RAGGIO_PUNTO_1, ptToPaint.x + RAGGIO_PUNTO_1, ptToPaint.y + RAGGIO_PUNTO_1);

		dc.Ellipse(rectTemp);

		if (theApp.m_bNumeriSuImmagineSagoma)
		{
			CString sTemp;
			sTemp.Format("%li", m_listPunti.GetAt(pos).lNumeroDermox);

			CFont* pOldFont = dc.SelectObject(&theApp.m_fontBold);
			int nOldBkMode = dc.SetBkMode(OPAQUE);
			dc.TextOut(ptToPaint.x + 4, ptToPaint.y - 9, sTemp);
			dc.SetBkMode(nOldBkMode);
			dc.SelectObject(pOldFont);
		}

		dc.SelectObject(pOldPen);
		dc.SelectObject(pOldBrush);
		dc.SetTextColor(crOldColor);

		m_listPunti.GetNext(pos);
		i++;
	}

	/////////////////////////
	// FINESTRELLA DI ZOOM //
	/////////////////////////

	// disegno	nella finestra di zoom //
	RECT rectPaintZoom = { 0, 0, 0, 0 };
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(&ptMouse);
	ptMouse.x++;
	ptMouse.y++;
	if (m_rectPaintSagoma.PtInRect(ptMouse))
	{
		// se sono sulla sagoma faccio lo zoom intorno al cursore //

		// TRACE2("   CURSOR IN    X%04li       Y%04li\n", ptMouse.x, ptMouse.y);
		POINT ptToZoom;
		ptToZoom.x = ptMouse.x - m_rectPaintSagoma.left;
		ptToZoom.x = ptToZoom.x * m_dibSagome.Width() / m_rectPaintSagoma.Width();
		ptToZoom.y = ptMouse.y - m_rectPaintSagoma.top;
		ptToZoom.y = ptToZoom.y * m_dibSagome.Height() / m_rectPaintSagoma.Height();
		ptToZoom.y = m_dibSagome.Height() - ptToZoom.y;
		// TRACE2("   CURSOR IN   (X%04li)     (Y%04li)\n", ptToZoom.x, ptToZoom.y);

		rectPaintZoom = m_dibSagome.PaintDIBSagomeZoom(&dc, m_rectFrameZoom, ptToZoom);
		LONG lTeeemp = rectPaintZoom.top;
		rectPaintZoom.top = m_dibSagome.Height() - rectPaintZoom.bottom;
		rectPaintZoom.bottom = m_dibSagome.Height() - lTeeemp;
		// TRACE("    ZOOM  IN L%04li R%04li T%04li B%04li\n\n", rectPaintZoom.left, rectPaintZoom.right, rectPaintZoom.top, rectPaintZoom.bottom);

		///////////////////
		// TESTO REGIONE //
		///////////////////

		BYTE bytePixel;
		m_dibSedi.GetPixel(ptToZoom.x, ptToZoom.y, &bytePixel);
		//TRACE("   GETPIX IN X%04li %04li) --> %li\n", ptToZoom.x, ptToZoom.y, (int)bytePixel);

		if ((long)bytePixel != m_lIDSede)
		{
			CString strSede = "";
			m_lIDSede = (long)bytePixel;

			if ((m_lIDSede > 0) && (m_lIDSede < 255))
			{
				POSITION pos = m_listSedi.GetHeadPosition();

				while(pos != NULL)
				{
					tagSede tagTemp = m_listSedi.GetNext(pos);

					if (tagTemp.m_lID == m_lIDSede)
					{
						strSede = tagTemp.m_sSede;
						break;
					}
				}
			}

			m_ctrlStaticSede.SetWindowText(strSede);
		}
	}
	else
	{
		if ((m_iCurSelPointIndex >= 0) && (m_iCurSelPointX >= 0) && (m_iCurSelPointY >= 0))
		{
			// se sono fuori dalla sagoma ma c'è un punto selezionato ci faccio lo zoom attorno //

			POINT ptToZoom;
			ptToZoom.x = m_iCurSelPointX;
			ptToZoom.y = m_iCurSelPointY;
			ptToZoom.y = m_dibSagome.Height() - ptToZoom.y;

			rectPaintZoom = m_dibSagome.PaintDIBSagomeZoom(&dc, m_rectFrameZoom, ptToZoom);
			LONG lTeeemp = rectPaintZoom.top;
			rectPaintZoom.top = m_dibSagome.Height() - rectPaintZoom.bottom;
			rectPaintZoom.bottom = m_dibSagome.Height() - lTeeemp;
			// TRACE("    ZOOM  IN L%04li R%04li T%04li B%04li\n\n", rectPaintZoom.left, rectPaintZoom.right, rectPaintZoom.top, rectPaintZoom.bottom);

			///////////////////
			// TESTO REGIONE //
			///////////////////

			BYTE bytePixel;
			m_dibSedi.GetPixel(ptToZoom.x, ptToZoom.y, &bytePixel);
			// TRACE3("   GETPIX IN X%04li %04li) --> \n", ptToZoom.x, ptToZoom.y);

			if ((long)bytePixel != m_lIDSede)
			{
				CString strSede = "";
				m_lIDSede = (long)bytePixel;

				if ((m_lIDSede > 0) && (m_lIDSede < 255))
				{
					POSITION pos = m_listSedi.GetHeadPosition();

					while(pos != NULL)
					{
						tagSede tagTemp = m_listSedi.GetNext(pos);

						if (tagTemp.m_lID == m_lIDSede)
						{
							strSede = tagTemp.m_sSede;
							break;
						}
					}
				}

				m_ctrlStaticSede.SetWindowText(strSede);
			}
		}
		else
		{
			// se sono fuori dalla sagoma e non c'è un punto selezionato svuoto la finestra di zoom //

			CBrush brushNull;
			brushNull.CreateSolidBrush(RGB_BLACK);
			dc.FillRect(m_rectFrameZoom, &brushNull);
			brushNull.DeleteObject();

			///////////////////
			// TESTO REGIONE //
			///////////////////

			m_lIDSede = 0;
			m_ctrlStaticSede.SetWindowText("");
		}
	}

	///////////////////////////////
	// PUNTI FINESTRELLA DI ZOOM //
	///////////////////////////////

	dc.SetBkMode(TRANSPARENT);

	i = 0;
	pos = m_listPunti.GetHeadPosition();
	while(pos != NULL)
	{
		CPoint ptToPaint = m_listPunti.GetAt(pos).ptPunto;
		if (CRect(rectPaintZoom).PtInRect(ptToPaint))
		{
			CPen* pOldPen;
			CBrush* pOldBrush;
			if (i == m_iCurSelPointIndex)
			{
				pOldPen = dc.SelectObject(&penSel);
				pOldBrush = dc.SelectObject(&brushSel);
				crOldColor = dc.SetTextColor(RGB_RED);
			}
			else
			{
				if (m_listPunti.GetAt(pos).bAsportazione)
				{
					pOldPen = dc.SelectObject(&penAsportaz);
					pOldBrush = dc.SelectObject(&brushAsportaz);
					crOldColor = dc.SetTextColor(RGB_BLACK);
				}
				else
				{
					pOldPen = dc.SelectObject(&penNormal);
					pOldBrush = dc.SelectObject(&brushNormal);
					crOldColor = dc.SetTextColor(RGB_BLUE);
				}
			}

			ptToPaint = ImageToScreenZoom(ptToPaint, rectPaintZoom);

			CRect rectTemp(ptToPaint.x - RAGGIO_PUNTO_2, ptToPaint.y - RAGGIO_PUNTO_2, ptToPaint.x + RAGGIO_PUNTO_2, ptToPaint.y + RAGGIO_PUNTO_2);

			dc.Ellipse(rectTemp);

			if (theApp.m_bNumeriSuImmagineSagoma)
			{
				CString sTemp;
				sTemp.Format("%li", m_listPunti.GetAt(pos).lNumeroDermox);

				CFont* pOldFont = dc.SelectObject(&theApp.m_fontBigBig);
				int nOldBkMode = dc.SetBkMode(TRANSPARENT);
				dc.TextOut(ptToPaint.x + 6, ptToPaint.y - 13, sTemp);
				dc.SetBkMode(nOldBkMode);
				dc.SelectObject(pOldFont);
			}

			dc.SelectObject(pOldPen);
			dc.SelectObject(pOldBrush);
			dc.SetTextColor(crOldColor);
		}

		m_listPunti.GetNext(pos);
		i++;
	}
	penSel.DeleteObject();
	brushSel.DeleteObject();
	penNormal.DeleteObject();
	brushNormal.DeleteObject();
}

void CAcqFromDiskDermoxDlg::OnSize(UINT nType, int cx, int cy) 
{
	CEndoxResizableDlg::OnSize(nType, cx, cy);
	
	if (IsWindow(m_ctrlFrameLive))
	{
		m_ctrlFrameLive.GetWindowRect(&m_rectFrameLive);
		ScreenToClient(&m_rectFrameLive);
	}

	if (IsWindow(m_ctrlFrameSagoma))
	{
		m_ctrlFrameSagoma.GetWindowRect(&m_rectFrameSagoma);
		ScreenToClient(&m_rectFrameSagoma);
	}

	if (IsWindow(m_ctrlFrameZoom))
	{
		m_ctrlFrameZoom.GetWindowRect(&m_rectFrameZoom);
		ScreenToClient(&m_rectFrameZoom);
	}
}

void CAcqFromDiskDermoxDlg::LoadSettings()
{
	CString sSection = "SorgenteDermox10";

	m_sCalib = GetPrivateProfileString(sSection, "Calib", "", theApp.m_sFileConfig);
	m_ctrlComboCalib.SetCurSel(m_ctrlComboCalib.FindStringExact(-1, m_sCalib));
}

CPoint CAcqFromDiskDermoxDlg::ImageToScreen(CPoint ptPoint)
{
	CPoint ptReturn;

	ptReturn.x = ptPoint.x * m_rectPaintSagoma.Width() / m_dibSagome.Width();
	ptReturn.x = ptReturn.x + m_rectPaintSagoma.left;
	ptReturn.y = ptPoint.y * m_rectPaintSagoma.Height() / m_dibSagome.Height();
	ptReturn.y = ptReturn.y + m_rectPaintSagoma.top;

	return ptReturn;
}

CPoint CAcqFromDiskDermoxDlg::ImageToScreenZoom(CPoint ptPoint, CRect rectImageZoom)
{
	CPoint ptReturn;

	ptReturn.x = ((ptPoint.x - rectImageZoom.left) * m_rectFrameZoom.Width() / rectImageZoom.Width()) + m_rectFrameZoom.left;
	ptReturn.y = ((ptPoint.y - rectImageZoom.top) * m_rectFrameZoom.Height() / rectImageZoom.Height()) + m_rectFrameZoom.top;

	return ptReturn;
}

CPoint CAcqFromDiskDermoxDlg::ScreenToImage(CPoint ptPoint)
{
	CPoint ptReturn;

	ptReturn.x = ptPoint.x - m_rectPaintSagoma.left;
	ptReturn.x = ptReturn.x * m_dibSagome.Width() / m_rectPaintSagoma.Width();
	ptReturn.y = ptPoint.y - m_rectPaintSagoma.top;
	ptReturn.y = ptReturn.y * m_dibSagome.Height() / m_rectPaintSagoma.Height();

	return ptReturn;
}

int CAcqFromDiskDermoxDlg::AggiungiPunto(CString sSede, CPoint ptPoint)
{
	int nReturn = -1;

	CPuntiPazienteSet setTemp;
	setTemp.SetOpenFilter("ID=0");
	if (setTemp.OpenRecordset("CAcqFromDiskDermoxDlg::AggiungiPunto"))
	{
		if (setTemp.AddNewRecordset("CAcqFromDiskDermoxDlg::AggiungiPunto"))
		{
			setTemp.m_lIDPaziente = m_pEsamiView->m_pPazientiSet->m_lContatore;
			setTemp.m_sSede = sSede;
			setTemp.m_lX = ptPoint.x;
			setTemp.m_lY = ptPoint.y;

			if (setTemp.UpdateRecordset("CAcqFromDiskDermoxDlg::AggiungiPunto"))
			{
				CString strFilter;
				strFilter.Format("ID=%li", setTemp.GetLastAdd());

				setTemp.CloseRecordset("CAcqFromDiskDermoxDlg::AggiungiPunto");
				setTemp.SetOpenFilter(strFilter);
				if (setTemp.OpenRecordset("CAcqFromDiskDermoxDlg::AggiungiPunto"))
				{
					if (!setTemp.IsEOF())
					{
						tagPuntiDermox puntoTemp;
						puntoTemp.lIDPunto = setTemp.m_lID;
						puntoTemp.ptPunto = ptPoint;
						puntoTemp.lNumeroDermox = setTemp.m_lNumeroDermox;
						sprintf_s(puntoTemp.szSede, 255, "%s", sSede);
						sprintf_s(puntoTemp.szPattern, 255, "%s", "");
						puntoTemp.bAsportazione = setTemp.m_bAsportazione;

						m_listPunti.AddTail(puntoTemp);

						nReturn = m_listPunti.GetCount() - 1;
					}
				}
			}
		}

		setTemp.CloseRecordset("CAcqFromDiskDermoxDlg::AggiungiPunto");
	}

	return nReturn;
}

void CAcqFromDiskDermoxDlg::CaricaDatiPunto()
{
	// ID del punto //
	long lIDPunto = 0;
	CString strSede = "";

	//
	if (m_iCurSelPointIndex >= 0)
	{
		tagPuntiDermox tagTemp = m_listPunti.GetAt(m_listPunti.FindIndex(m_iCurSelPointIndex));
		lIDPunto = tagTemp.lIDPunto;
		strSede = tagTemp.szSede;
	}

	//
	CString strButton = theApp.GetMessageString(IDS_ACQUISIZIONE_IMMAGINE3);
	if (lIDPunto > 0)
	{
		if (strSede.IsEmpty())
			strButton.Format(theApp.GetMessageString(IDS_ACQUISIZIONE_IMMAGINE1));
		else
			strButton.Format(theApp.GetMessageString(IDS_ACQUISIZIONE_IMMAGINE2), strSede);
	}
	m_ctrlBtnPhoto.SetWindowText(strButton);
}

void CAcqFromDiskDermoxDlg::CaricaImmaginiPunto()
{
	// ID del punto //
	long lIDPunto = 0;
	if (m_iCurSelPointIndex >= 0)
		lIDPunto = m_listPunti.GetAt(m_listPunti.FindIndex(m_iCurSelPointIndex)).lIDPunto;

	if (lIDPunto > 0)
	{
		// lista delle immagini di quel punto //
		CImgList listImg;
		int nImageCount = m_pEsamiView->m_pImgManager->GetImgListByPoint(m_pEsamiView->m_pEsamiSet->m_lPaziente, lIDPunto, &listImg);

		// reimposto la lista di immagini ed il relativo controllo //
		m_listImages.SetImageCount(nImageCount);
		m_ctrlListImages.DeleteAllItems();

		// riempio di nuovo tutto //
		for(int i = 0; i < nImageCount; i++)
		{
			IMG img = listImg.GetAt(listImg.FindIndex(i));

			m_listImages.Replace(i, CBitmap::FromHandle(img.hBmp), RGB(0, 0, 0));
			m_ctrlListImages.InsertItem(i, CEsamiSet().GetDataEsame(img.lIDEsame), i);
			m_ctrlListImages.SetItemData(i, (DWORD)img.lID);

			DeleteObject(img.hBmp);
			DeleteObject(img.hBmpSelected);
		}
	}
	else
	{
		m_listImages.SetImageCount(0);
		m_ctrlListImages.DeleteAllItems();
	}
}

long CAcqFromDiskDermoxDlg::ImportaImmagine()
{
	long lReturn = 0;

	if (_access(m_sPhotoFile, 0) == 0)
	{
		CStringList listPath;

		// controllo che la dimensione del file sia maggiore di 0 (capita per certi filmati e si blocca tutto) //

		HANDLE hFile = CreateFile(m_sPhotoFile, STANDARD_RIGHTS_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
		{
			LARGE_INTEGER llTemp;
			if (GetFileSizeEx(hFile, &llTemp))
			{
				if (llTemp.QuadPart > 0)
					listPath.AddHead(m_sPhotoFile);
				else
					DeleteFile(m_sPhotoFile);
			}
		}
		CloseHandle(hFile);

		BOOL bExportToPacs = FALSE;
		// In modalità 2 devo avviare il trasferimento automatico su PACS
		if (theApp.m_lDcmStoreMode == 2)
			bExportToPacs = TRUE;

		// ID del punto //
		long lIDPunto = 0;
		if (m_iCurSelPointIndex >= 0)
			lIDPunto = m_listPunti.GetAt(m_listPunti.FindIndex(m_iCurSelPointIndex)).lIDPunto;

		//
		CImgIDList listIDImageImported;
		m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore);

		DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
		if (m_pEsamiView->m_pImgManager->ImportImgList(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, lIDPunto, &listPath, FORM_IMM, FORM_MINI, &listIDImageImported, bExportToPacs, FALSE, FALSE) > 0)
		{
			if (listIDImageImported.GetCount() > 0)
				lReturn = listIDImageImported.GetHead();

			// importo anche il file .MIS associato //
			if (lReturn > 0)
			{
				CString strLastFile = m_pEsamiView->m_pImgManager->GetFullPath(lReturn);

				CString strOrigMis = m_sPhotoFile.Left(m_sPhotoFile.GetLength() - 4) + ".MIS";
				CString strDestMis = strLastFile.Left(strLastFile.GetLength() - 4) + ".MIS";

				MoveFile(strOrigMis, strDestMis);
			}
			// --- //

			if (m_bDeleteAfterAcquisition)
				DeleteFile(m_sPhotoFile);
		}
		if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
			CLogFileWriter::Get()->WriteLogLine0_ImmStore(timeGetTime() - timeForLog, m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore, listIDImageImported.GetCount(), "CAcqFromDiskDermoxDlg::ImportaImmagine");

		listPath.RemoveAll();
	}

	return lReturn;
}

void CAcqFromDiskDermoxDlg::SelezionaPunto(CPoint ptPoint)
{
	BeginWaitCursor();

	int nIndex = TrovaPunto(ptPoint);
	if (nIndex >= 0)
	{
		if (nIndex != m_iCurSelPointIndex)
		{
			m_iCurSelPointIndex = nIndex; // il punto esiste già, mi basta soltanto selezionarlo //
			m_iCurSelPointX = ptPoint.x;
			m_iCurSelPointY = ptPoint.y;

			InvalidateRect(m_rectFrameSagoma, FALSE);
			InvalidateRect(m_rectFrameZoom, FALSE);

			//
			for(int i = 0; i < m_ctrlListPoints.GetItemCount(); i++)
			{
				if (i == nIndex)
				{
					m_ctrlListPoints.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
					m_ctrlListPoints.EnsureVisible(i, FALSE);
				}
				else
				{
					m_ctrlListPoints.SetItemState(i, 0, LVIS_SELECTED);
				}
			}
			// OnLvnItemchangedListPoints(NULL, NULL);
		}
	}
	else
	{
		CString strSede;
		m_ctrlStaticSede.GetWindowText(strSede);
		strSede.Trim();

		CString strMessage;
		if (strSede.IsEmpty())
			strMessage.Format(theApp.GetMessageString(IDS_QUESTION_ADD_PUNTO1));
		else
			strMessage.Format(theApp.GetMessageString(IDS_QUESTION_ADD_PUNTO2), strSede);

		if (theApp.AfxMessageBoxEndo(strMessage, MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			int nTemp = AggiungiPunto(strSede, ptPoint); // il punto non esiste, lo aggiungo //

			// se tutto è andato bene seleziono il nuovo punto aggiunto //
			if (nTemp >= 0)
			{
				m_iCurSelPointIndex = nTemp;
				m_iCurSelPointX = ptPoint.x;
				m_iCurSelPointY = ptPoint.y;

				InvalidateRect(m_rectFrameSagoma, FALSE);
				InvalidateRect(m_rectFrameZoom, FALSE);

				// --- //

				int nItem = m_ctrlListPoints.GetItemCount();

				CString strTemp;
				tagPuntiDermox tagTemp = m_listPunti.GetTail();

				m_ctrlListPoints.InsertItem(nItem, "");
				m_ctrlListPoints.SetItemData(nItem, (DWORD)tagTemp.lIDPunto);

				strTemp.Format("%li", tagTemp.lNumeroDermox);
				m_ctrlListPoints.SetItemText(nItem, 1, strTemp);

				m_ctrlListPoints.SetItemText(nItem, 2, tagTemp.szSede);

				m_ctrlListPoints.SetItemText(nItem, 3, tagTemp.szPattern);

				m_ctrlListPoints.SetItemText(nItem, 4, tagTemp.bAsportazione ? theApp.GetMessageString(IDS_YES) : theApp.GetMessageString(IDS_NO));

				m_ctrlListPoints.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);
				m_ctrlListPoints.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
				m_ctrlListPoints.SetColumnWidth(3, LVSCW_AUTOSIZE_USEHEADER);
				m_ctrlListPoints.SetColumnWidth(4, LVSCW_AUTOSIZE_USEHEADER);

				//
				for(int i = 0; i < m_ctrlListPoints.GetItemCount(); i++)
				{
					if (i == nItem)
					{
						m_ctrlListPoints.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
						m_ctrlListPoints.EnsureVisible(i, FALSE);
					}
					else
					{
						m_ctrlListPoints.SetItemState(i, 0, LVIS_SELECTED);
					}
				}
				// OnLvnItemchangedListPoints(NULL, NULL);
			}
			else
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_ADD_PUNTO), MB_ICONSTOP);
			}
		}
	}

	// CaricaDatiPunto();
	// CaricaImmaginiPunto();

	EndWaitCursor();
}

int CAcqFromDiskDermoxDlg::TrovaPunto(CPoint& ptPoint)
{
	int nIndex = 0;

	POSITION pos = m_listPunti.GetHeadPosition();
	while(pos != NULL)
	{
		CPoint ptTemp = m_listPunti.GetAt(pos).ptPunto;

		if (sqrt(pow((double)(ptPoint.x - ptTemp.x), 2) + pow((double)(ptPoint.y - ptTemp.y), 2)) <= RAGGIO_PUNTO_1)
		{
			ptPoint = ptTemp;
			return nIndex;
		}

		m_listPunti.GetNext(pos);
		nIndex++;
	}

	return -1;
}