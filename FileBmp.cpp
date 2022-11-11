#include "stdafx.h"
#include "Endox.h"
#include "FileBmp.h"
#include "Common.h"

#include <io.h>

#include "DLL_Imaging\h\ImgManager.h"
#include "MisureConfig\SerializerDLL.h"

#include "AfxTempl.h"
#include "AlbumEsameDlg.h"
#include "AlbumForm.h"
#include "Bmp.h"
#include "Common.h"
#include "Dib.h"
#include "EditBmp.h"
#include "EsamiView.h"
#include "EspelliDlg.h"
#include "ImageDicomDlg.h"
#include "ImageDlg.h"
#include "ImageOrderDlg.h"
#include "ImgListOrgani.h"
#include "MaximizeDlg.h"
#include "MosaicDlg.h"
#include "Volume.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CObList CFileBmp::m_listSelected;
CObArray CFileBmp::m_listPrinter;

CFileBmp::CFileBmp()
	: CBmp()
{
	m_bIsAlbumGlobal = FALSE;

	m_lPaziente = 0;
	m_lEsame = 0;
	m_lID = 0;
	m_iType = -1;
	m_hMiniBmp = NULL;
	m_bConfirmed = FALSE;
	m_strDvdLabel = "";
	m_strComment = "";
	m_strSede = "";
	m_bCI = FALSE;
}

CFileBmp::~CFileBmp()
{
	DeleteObject(m_hMiniBmp);
	ResetImage(TRUE);
}

BEGIN_MESSAGE_MAP(CFileBmp, CBmp)
	ON_WM_PAINT()

	ON_WM_LBUTTONDBLCLK()
	ON_WM_MBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_MESSAGE(MSG_REFRESH_ALBUM, RefreshAlbum) //Gabriel - BUG Refresh álbum
END_MESSAGE_MAP()

BOOL CFileBmp::CreateBmp(CEsamiView* pActiveView, CWnd* pParentWnd, CWnd* pctrFrame, CFileBmp** pBmp)
{
	(*pBmp) = new CFileBmp;

	if (*pBmp)
	{
		return CBmp::CreateBmp(pActiveView, pParentWnd, pctrFrame, *pBmp);
	}

	return FALSE;
}

void CFileBmp::DeleteListSelected(UINT what)
{
	switch (what)
	{
	case ALL_IMAGES:
	{
		CFileBmp::m_listPrinter.RemoveAll();
		while (!CFileBmp::m_listSelected.IsEmpty())
		{
			CObSelect* pObj = (CObSelect*)CFileBmp::m_listSelected.RemoveTail();
			if (pObj)
				delete pObj;
		}
		break;
	}
	case LOCAL_IMAGES:
	{
		POSITION pos = CFileBmp::GetFirstSelectedPos();
		while (pos != NULL)
		{
			POSITION posSel = pos;
			CObSelect* pSel = GetNextSelected(pos);

			if ((pSel != NULL) && (!pSel->m_bIsGlobal))
			{
				DeletePrinter(pSel);
				CFileBmp::m_listSelected.RemoveAt(posSel);
				delete pSel;
			}
		}
		break;
	}
	case GLOBAL_IMAGES:
	{
		POSITION pos = CFileBmp::GetFirstSelectedPos();
		while (pos != NULL)
		{
			POSITION posSel = pos;
			CObSelect* pSel = GetNextSelected(pos);

			if ((pSel != NULL) && (pSel->m_bIsGlobal))
			{
				DeletePrinter(pSel);
				CFileBmp::m_listSelected.RemoveAt(posSel);
				delete pSel;
			}
		}
		break;
	}
	}

	SendUpdateMessage();
}

void CFileBmp::DeletePrinter(CObSelect* pSel)
{
	for (int i = 0; i < CFileBmp::m_listPrinter.GetSize(); i++)
	{
		CObSelect* pObj = (CObSelect*)CFileBmp::m_listPrinter.GetAt(i);

		if (pObj == pSel)
		{
			CFileBmp::m_listPrinter.RemoveAt(i);
			break;
		}
	}
}

BOOL CFileBmp::FileMainIsPresent()
{
	BOOL bNotDisk = FALSE;

	if (m_bConfirmed == TRUE)
		bNotDisk = (m_strDvdLabel != GetVolumeName());

	while (bNotDisk)
	{
		CEspelliDlg	dlg(this, m_strDvdLabel);

		if (dlg.DoModal() == IDCANCEL)
			return FALSE;

		bNotDisk = (m_strDvdLabel != GetVolumeName());
	}

	return TRUE;
}

POSITION CFileBmp::GetFirstSelectedPos()
{
	return CFileBmp::m_listSelected.GetHeadPosition();
}

CObSelect* CFileBmp::GetNextSelected(POSITION& pos)
{
	return (CObSelect*)CFileBmp::m_listSelected.GetNext(pos);
}

BOOL CFileBmp::LoadImage(long lPaziente, long lEsame, CImgListOrgani* pImgListOrgani, long lIndex, BOOL bIsConfirmed, CString strDvdLabel, short lCosaCarico)
{
	ASSERT(pImgListOrgani != NULL);

	BOOL bReturn = FALSE;

	ResetImage(); // resetta tutto //

	m_pImgListOrgani = pImgListOrgani;
	POSITION pos = m_pImgListOrgani->FindIndex(lIndex);
	if (pos != NULL)
	{
		IMG_ORGANI img_organi = m_pImgListOrgani->GetAt(pos);

		m_lPaziente = lPaziente;
		m_lEsame = lEsame;
		m_lID = img_organi.img.lID;						// nuovo //
		m_iType = img_organi.img.type;					// nuovo //
		m_hMiniBmp = img_organi.img.hBmp;				// nuovo //
		m_bConfirmed = bIsConfirmed;					// nuovo //
		m_strDvdLabel = strDvdLabel;					// nuovo //
		m_strComment = img_organi.img.szDescription;	// vecchio //

		if ((theApp.m_nApplication == PRG_DERMOX) && theApp.m_bNumeriSuImmagineSagoma && (img_organi.lNumeroDermox > 0))
		{
			img_organi.sSedeDermox.Trim();
			if (img_organi.sSedeDermox.IsEmpty())
				m_strSede.Format("%li", img_organi.lNumeroDermox);
			else
				m_strSede.Format("%li - %s", img_organi.lNumeroDermox, img_organi.sSedeDermox);
		}
		else
		{
			m_strSede = img_organi.sSedeDermox;
		}

		// Sandro 21/03/2012 // in Dermox mostro anche la calibrazione sopra all'immagine //
		if (theApp.m_bDermoxMostraCalibSuAlbum)
		{
			char szCalibName[256];
			float fRatio;

			// Luiz - 28/08/2019 - P3 - Ajuste de "CRASH" em produção
			try
			{
				GetCalib(m_pEsamiView->m_pImgManager->GetFullPath(m_lID), szCalibName, &fRatio);
			}
			catch (const std::exception& ex)
			{
				CString strError;
				strError.Format("FileBMP::stdExcept \n %s", ex.what());
				theApp.AfxMessageBoxEndo(strError);
			}
			catch (CException* e)
			{
				TCHAR szError[255];
				CString strError;
				e->GetErrorMessage(szError, 255);
				strError.Format("FileBMP::CException \n %s", szError);
				theApp.AfxMessageBoxEndo(strError);
			}
			catch (...)
			{
				theApp.AfxMessageBoxEndo("FileBMP::EXCEPTION-Falha ao obter imagem do album");
			}
			CString sCalibName(szCalibName);
			sCalibName.Trim();
			if (!sCalibName.IsEmpty())
			{
				if (!m_strSede.IsEmpty())
					m_strSede += " - ";

				m_strSede += sCalibName;
			}
		}

		SetPositionNumber(lIndex, m_pImgListOrgani->GetCount(), FALSE);
		SetPointAutoColor(img_organi.iPunto, TRUE);
		m_bCI = img_organi.img.bCI;

		m_pDib = new CDib;
		if (m_pDib != NULL)
		{
			BeginWaitCursor();

			if ((lCosaCarico == CARICA_MINI) || (m_pEsamiView == NULL) || (m_pEsamiView->m_pImgManager == NULL) || (m_iType == _movie_))
			{
				bReturn = m_pDib->Attach(CDib::BitmapToDIB(m_hMiniBmp, NULL), TRUE);
			}
			else
			{
				m_pEsamiView->m_pImgManager->SetCurrentIDs(m_lPaziente, m_lEsame);
				bReturn = m_pDib->Attach(CDib::BitmapToDIB(m_pEsamiView->m_pImgManager->GetImg(m_lID, FALSE, FALSE, FALSE), NULL), TRUE);
			}

			if (m_pDib == NULL)
				ResetImage();

			EndWaitCursor();
		}
	}

	if (m_pEditWnd != NULL)
		m_pEditWnd->Refresh();

	AutoRedraw();

	return bReturn;
}

void CFileBmp::ResetImage(BOOL bOnExit)
{
	if (m_pDib != NULL)
	{
		m_pDib->ReleaseContents();
		delete m_pDib;
		m_pDib = NULL;
	}

	m_pImgListOrgani = NULL;
	m_lPaziente = 0;
	m_lEsame = 0;
	m_lID = 0;							// nuovo //
	m_iType = 0;						// nuovo //
	m_hMiniBmp = NULL;					// nuovo //
	m_bConfirmed = FALSE;				// nuovo //
	m_strDvdLabel = "";					// nuovo //
	m_strComment = "";					// vecchio //
	m_strSede = "";
	m_bIsSelect = FALSE;
	m_iPointNumber = -1;
	m_iPositionNumber = -1;
	m_iTotalImageNumber = 0;            // BUG 4197 - total imagens / qtd selecionadas / OK
	m_bCI = FALSE;

	if (m_pEditWnd && IsWindow(m_pEditWnd->GetSafeHwnd()))
	{
		m_pEditWnd->SetWindowText(m_strComment);
		m_pEditWnd->SetModify(FALSE);
	}

	if (bOnExit == FALSE)
		AutoRedraw();
}

CObSelect* CFileBmp::NewSelected(CFileBmp* pFileBmp)
{
	if (!pFileBmp->IsValidBmp())
		return NULL;

	POSITION pos = CFileBmp::GetFirstSelectedPos();
	while (pos != NULL)
	{
		CObSelect* pSel = GetNextSelected(pos);

		if (pSel)
			if (pSel->m_lID == pFileBmp->m_lID && pSel->m_bIsGlobal == pFileBmp->m_bIsAlbumGlobal)
				return NULL;
	}

	CObSelect* pItem = new CObSelect(pFileBmp);

	CFileBmp::m_listSelected.AddTail(pItem);

	SendUpdateMessage();

	return pItem;
}

CObSelect* CFileBmp::NewSelected(long lID, BOOL bIsAlbumGlobal, int iType, const CString &strDescription, long lPaziente, long lEsame, BOOL bTransferred, const CString &strDvdLabel, BOOL bCI)
{
	POSITION pos = CFileBmp::GetFirstSelectedPos();
	while (pos != NULL)
	{
		CObSelect* pSel = GetNextSelected(pos);

		if (pSel)
		{
			if (pSel->m_lID == lID && pSel->m_bIsGlobal == bIsAlbumGlobal)
				return NULL;
		}
	}

	CObSelect* pItem = new CObSelect(lID, bIsAlbumGlobal, iType, strDescription, lPaziente, lEsame, bTransferred, strDvdLabel, bCI);

	CFileBmp::m_listSelected.AddTail(pItem);

	SendUpdateMessage();

	return pItem;
}

void CFileBmp::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	//Gabriel BUG 7768 - Continuous capture problem FIX
	if ((!theApp.m_bUsaNovaCapturaContinua && m_pEsamiView->m_bImporting) || !m_pDib)
	{
		return;
	}
	try
	{
		CBmp::OnLButtonDblClk(nFlags, point);

		switch (m_nBtnMouseModeLeft)
		{
		case BMP_L_NORMALMODE:
		{
			ShowTga();
			SendUpdateMessage();

			break;
		}
		case BMP_L_NODOUBLECLICK:
		{
			CMaximizeDlg dlg(this, m_pDib);
			dlg.DoModal();

			break;
		}
		default:
		{
			ASSERT(FALSE);

			break;
		}
		}
	}
	catch (CException* e)
	{
		TCHAR szError[255];
		CString strError;
		e->GetErrorMessage(szError, 255);
		strError.Format("FileBMP::DblClickCException \n %s", szError);
		theApp.AfxMessageBoxEndo(strError);
	}
	catch (const std::exception& ex)
	{
		CString strError;
		strError.Format("FileBMP::DblClickSTDexception \n %s", ex.what());
		theApp.AfxMessageBoxEndo(strError);
	}
	/*catch (CDBException* pEx)
	{
	CString strError;
	strError.Format("FileBMP::OnLButtonDblClk \n\n %d: %s State: %s", pEx->m_nRetCode, pEx->m_strError, pEx->m_strStateNativeOrigin);
	theApp.AfxMessageBoxEndo(strError);
	}*/
	catch (...)
	{
		theApp.AfxMessageBoxEndo("CFileBmp::EXCEPTION - Falha ao abrir imagem.");
	}
}

#define SEDE_HEIGHT 16

void CFileBmp::OnPaint()
{
	if (!m_bAutoRedraw)
		return;

	CRect		RectClient, RectDib;
	float		rappClient, rappImage;
	CPaintDC 	dc(this);

	GetClientRect(&RectClient);
	RectClient.DeflateRect(1, 1);

	CBrush		SelBrush;
	COLORREF	ColorSel = ::GetSysColor(COLOR_BTNFACE);

	SelBrush.CreateSolidBrush(ColorSel);
	dc.FrameRect(RectClient, &SelBrush);
	SelBrush.DeleteObject();

	if (!m_pDib || !m_pDib->IsValidDib())
	{
		CBrush NullBrush;

		NullBrush.CreateSolidBrush(::GetSysColor(COLOR_BTNFACE));
		dc.FillRect(RectClient, &NullBrush);
		NullBrush.DeleteObject();

		return;
	}

	if (theApp.m_nApplication == PRG_DERMOX)
		RectClient.top += SEDE_HEIGHT;

	if (m_pDib && m_pDib->IsValidDib())
	{
		CPoint ptIcon(RectClient.left, RectClient.top);
		CPoint ptNumber(RectClient.right - RAGGIO_PUNTO, RectClient.top + RAGGIO_PUNTO);
		CPoint ptPosition(RectClient.left, RectClient.bottom);
		CPoint ptHistoricalArchive(RectClient.right - 35, RectClient.bottom - 35);

		// Sandro 05/08/2011 //
		if (theApp.m_nApplication == PRG_DERMOX)
		{
			CRect rectTemp(RectClient.left, RectClient.top - SEDE_HEIGHT, RectClient.right, RectClient.top);

			// sfondo nero //

			CBrush brBlack;
			brBlack.CreateSolidBrush(RGB_BLACK);
			dc.FillRect(rectTemp, &brBlack);
			brBlack.DeleteObject();

			// testo della sede bianco //

			if (!m_strSede.IsEmpty())
			{
				CFont* pOldFont = dc.SelectObject(&theApp.m_fontBold);
				COLORREF crTemp = dc.SetTextColor(RGB_WHITE);

				dc.SetBkMode(TRANSPARENT);
				dc.DrawText(m_strSede, rectTemp, DT_TOP | DT_CENTER | DT_SINGLELINE);

				dc.SetTextColor(crTemp);
				dc.SelectObject(pOldFont);
			}
		}

		//////////////////////////////////////////////////////////////
		// ridimensionamento dell'area client in base alle proporzioni del bitmap....
		RectDib = CRect(0, 0, m_pDib->Width(), m_pDib->Height());
		rappClient = (float)RectClient.Width() / (float)RectClient.Height();
		rappImage = (float)RectDib.Width() / (float)RectDib.Height();

		if (rappClient != rappImage)
		{
			CBrush brBlack;
			brBlack.CreateSolidBrush(RGB_BLACK);
			dc.FillRect(RectClient, &brBlack);
			brBlack.DeleteObject();

			if (rappClient < rappImage)
			{
				int RealHeight = (int)((float)RectClient.Width() / rappImage);

				if (theApp.m_nApplication == PRG_DERMOX)
					RectClient.top = ((RectClient.Height() - RealHeight) / 2) + SEDE_HEIGHT;
				else
					RectClient.top = (RectClient.Height() - RealHeight) / 2;
				RectClient.bottom = RectClient.top + RealHeight;
			}
			else
			{
				int RealWidth = (int)((float)RectClient.Height() * rappImage);

				RectClient.left = (RectClient.Width() - RealWidth) / 2;
				RectClient.right = RectClient.left + RealWidth;
			}
		}
		//////////////////////////////////////////////////////////////

		m_pDib->PaintDIB(dc.GetSafeHdc(), RectClient, RectDib);

		if (m_bIsSelect)
		{
			dc.DrawIcon(ptIcon, AfxGetApp()->LoadIcon(IDI_SELECT));

			// Sandro 23/09/2015 //

			BOOL bFound = FALSE;
			long lNumber = 0;

			POSITION pos = m_listSelected.GetHeadPosition();
			while (pos != NULL)
			{
				CObSelect* pObj = (CObSelect*)m_listSelected.GetAt(pos);

				if (pObj->m_lID == m_lID)
				{
					bFound = TRUE;
					lNumber++;
					break;
				}
				else
				{
					if (pObj->m_bIsGlobal == m_bIsAlbumGlobal)
						lNumber++;
				}

				m_listSelected.GetNext(pos);
			}

			if (bFound && (lNumber > 0))
			{
				CString sTempNumber;
				sTempNumber.Format("%li", lNumber);

				CRect rectNumber(CPoint(ptIcon.x, ptIcon.y), CPoint(ptIcon.x + 31, ptIcon.y + 34));

				dc.SetBkMode(TRANSPARENT);

				CFont* pFontPrev = (CFont*)dc.SelectObject(&theApp.m_fontBig);
				COLORREF colPrev = dc.SetTextColor(RGB_WHITE);

				dc.DrawText(sTempNumber, rectNumber, DT_BOTTOM | DT_RIGHT | DT_SINGLELINE);

				dc.SetTextColor(colPrev);
				dc.SelectObject(pFontPrev);
			}
		}

		//
		if (m_iPointNumber >= 0)
		{
			CPen pen(PS_SOLID, 1, m_colorCircle);
			CBrush brush(m_colorCircle);

			CPen* pOldPen = dc.SelectObject(&pen);
			CBrush* pOldBrush = dc.SelectObject(&brush);
			CFont* pOldFont = dc.SelectObject(&theApp.m_fontBold);

			CString strTemp;
			strTemp.Format("%d", m_iPointNumber + 1);

			CRect rectRound = CRect(ptNumber.x - RAGGIO_PUNTO, ptNumber.y - RAGGIO_PUNTO, ptNumber.x + RAGGIO_PUNTO, ptNumber.y + RAGGIO_PUNTO);

			dc.SetTextColor(m_colorNumber);
			dc.SetBkMode(TRANSPARENT);

			dc.Ellipse(rectRound);
			dc.DrawText(strTemp, rectRound, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			dc.SelectObject(pOldPen);
			dc.SelectObject(pOldBrush);
			dc.SelectObject(pOldFont);

			pen.DeleteObject();
			brush.DeleteObject();
		}

		if ((theApp.m_bNumeriSuImmaginiAlbum) && (m_iPositionNumber >= 0))
		{
			CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
			CBrush brushB(RGB(255, 255, 255));
			CBrush brushN(RGB(0, 0, 0));

			CPen* pOldPen = dc.SelectObject(&pen);
			CFont* pOldFont = dc.SelectObject(&theApp.m_fontBig);

			CString strTemp;
			strTemp.Format("%d", m_iPositionNumber + 1);

			CRect rectRound = CRect(ptPosition.x, ptPosition.y - (RAGGIO_PUNTO * 2), ptPosition.x + (RAGGIO_PUNTO * 2), ptPosition.y);

			dc.SetTextColor(RGB(255, 255, 255));
			dc.SetBkMode(TRANSPARENT);

			rectRound.InflateRect(0, 0, BORDO_PUNTO * 2, 0);
			dc.FillRect(rectRound, &brushB);
			rectRound.DeflateRect(BORDO_PUNTO, BORDO_PUNTO);
			dc.FillRect(rectRound, &brushN); // Ellipse(rectRound);
			dc.DrawText(strTemp, rectRound, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			dc.SelectObject(pOldPen);
			dc.SelectObject(pOldFont);

			pen.DeleteObject();
			brushB.DeleteObject();
			brushN.DeleteObject();
		}
	}
}

#undef SEDE_HEIGHT

void CFileBmp::OnMButtonDown(UINT nFlags, CPoint point)
{
	if (m_pEsamiView->m_bImporting || !m_pDib)
		return;

	CBmp::OnMButtonDown(nFlags, point);

	if (!m_pEsamiView->m_pEsamiSet->m_bStessoDistretto)
		return;

	int nOldPos = m_iPositionNumber + 1;

	CImageOrderDlg dlg(this);
	dlg.SetParam(nOldPos, m_iTotalImageNumber);
	if (dlg.DoModal() == IDOK)
	{
		int nNewPos = dlg.GetNewPos() - 1;
		nOldPos--;

		m_pEsamiView->m_pImgManager->SetImagePosition(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, m_lID, nNewPos);

		// aggiorno la visualizzazione //
		if (m_pParentAlbum != NULL)
			m_pParentAlbum->SendMessage(MSG_AFTER_ELABIMAGE, (WPARAM)FALSE);
		SendUpdateMessage();

		/*
		if (nNewPos < nOldPos)
		{
		// la nuova posizione è minore della vecchia //
		// sposto indietro l'immagine selezionata //
		// sposto in avanti di 1 tutte le immagini che stanno in mezzo //
		CString strQuery;

		try
		{
		// quella che devo spostare la metto temporaneamente a -100 //
		strQuery.Format("UPDATE Immagini SET Ordine=-100 WHERE IDEsame=%li AND Ordine=%d", m_lEsame, nOldPos);
		theApp.m_dbEndox.ExecuteSQL(strQuery);

		// tutte quelle "in mezzo" le sposto di 1 in avanti //
		strQuery.Format("UPDATE Immagini SET Ordine=Ordine+1 WHERE IDEsame=%li AND Ordine BETWEEN %d AND %d", m_lEsame, nNewPos, nOldPos);
		theApp.m_dbEndox.ExecuteSQL(strQuery);

		// metto quella da spostare nel buco così creatosi //
		strQuery.Format("UPDATE Immagini SET Ordine=%d WHERE IDEsame=%li AND Ordine=-100", nNewPos, m_lEsame);
		theApp.m_dbEndox.ExecuteSQL(strQuery);
		}
		catch(CDBException *pEx)
		{
		pEx->ReportError();
		pEx->Delete();
		}

		// aggiorno la visualizzazione //
		if (m_pParentAlbum != NULL)
		m_pParentAlbum->SendMessage(MSG_AFTER_ELABIMAGE, (WPARAM)FALSE);
		SendUpdateMessage();
		}
		else if (nNewPos > nOldPos)
		{
		// la nuova posizione è maggiore della vecchia //
		// sposto in avanti l'immagine selezionata //
		// sposto indietro di 1 tutte le immagini che stanno in mezzo //

		CString strQuery;

		try
		{
		// quella che devo spostare la metto temporaneamente a -100 //
		strQuery.Format("UPDATE Immagini SET Ordine=-100 WHERE IDEsame=%li AND Ordine=%d", m_lEsame, nOldPos);
		theApp.m_dbEndox.ExecuteSQL(strQuery);

		// tutte quelle "in mezzo" le sposto indietro di 1 //
		strQuery.Format("UPDATE Immagini SET Ordine=Ordine-1 WHERE IDEsame=%li AND Ordine BETWEEN %d AND %d", m_lEsame, nOldPos, nNewPos);
		theApp.m_dbEndox.ExecuteSQL(strQuery);

		// metto quella da spostare nel buco così creatosi //
		strQuery.Format("UPDATE Immagini SET Ordine=%d WHERE IDEsame=%li AND Ordine=-100", nNewPos, m_lEsame);
		theApp.m_dbEndox.ExecuteSQL(strQuery);
		}
		catch(CDBException *pEx)
		{
		pEx->ReportError();
		pEx->Delete();
		}

		// aggiorno la visualizzazione //
		if (m_pParentAlbum != NULL)
		m_pParentAlbum->SendMessage(MSG_AFTER_ELABIMAGE, (WPARAM)FALSE);
		SendUpdateMessage();
		}
		*/
	}
}

void CFileBmp::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (!m_pDib)
		return;

	// Sandro 23/09/2015 // provo ad invertire l'ordine, mettendo il CBmp::OnRButtonDown DOPO //

	switch (m_nBtnMouseModeRight)
	{
	case BMP_R_NORMALMODE:
	{
		if (m_bIsSelect == TRUE)
			CFileBmp::RemoveSelected(this);
		else
			CFileBmp::NewSelected(this);
		break;
	}
	case BMP_R_SENDTOPARENT:
	{
		break;
	}
	default:
	{
		ASSERT(FALSE);
		break;
	}
	}

	CBmp::OnRButtonDown(nFlags, point);

	// m_pParentAlbum->RedrawWindow();

	m_pParentAlbum->SendMessage(MSG_REFRESH_IMAGES);
}

BOOL CFileBmp::RemoveSelected(long lIDImmagine, BOOL bIsGlobal)
{
	for (POSITION pos = CFileBmp::GetFirstSelectedPos(); pos != NULL;)
	{
		POSITION 	posSel = pos;
		CObSelect* 	pSel = GetNextSelected(pos);

		if (pSel)
		{
			if ((pSel->m_lID == lIDImmagine) && (pSel->m_bIsGlobal == bIsGlobal))
			{
				DeletePrinter(pSel);

				CFileBmp::m_listSelected.RemoveAt(posSel);
				delete pSel;

				SendUpdateMessage();

				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CFileBmp::RemoveSelected(CFileBmp* pFileBmp)
{
	for (POSITION pos = CFileBmp::GetFirstSelectedPos(); pos != NULL;)
	{
		POSITION 	posSel = pos;
		CObSelect* 	pSel = GetNextSelected(pos);

		if (pSel)
		{
			if (pSel->m_lID == pFileBmp->m_lID && pSel->m_bIsGlobal == pFileBmp->m_bIsAlbumGlobal)
			{
				DeletePrinter(pSel);

				CFileBmp::m_listSelected.RemoveAt(posSel);
				delete pSel;

				SendUpdateMessage();

				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CFileBmp::RemoveSelected(CObSelect* pSel)
{
	POSITION pos;

	if ((pos = CFileBmp::m_listSelected.Find(pSel)) != NULL)
	{
		DeletePrinter(pSel);

		CFileBmp::m_listSelected.RemoveAt(pos);
		delete pSel;

		SendUpdateMessage();

		return TRUE;
	}
	return FALSE;
}

void CFileBmp::ReselectBmp(CFileBmp* pFileBmp, BOOL bCheck)
{
	BOOL bSelected = FALSE;

	for (POSITION pos = CFileBmp::GetFirstSelectedPos(); pos != NULL;)
	{
		CObSelect* pSel = GetNextSelected(pos);

		if (pSel)
		{
			if (pSel->m_lID == pFileBmp->m_lID && pSel->m_bIsGlobal == pFileBmp->m_bIsAlbumGlobal)
			{
				CRect rect(0, 0, 38, 38);

				bSelected = TRUE;

				pFileBmp->m_bIsSelect = TRUE;

				pFileBmp->AutoRedraw(&rect);

				break;
			}
		}
	}

	if (bCheck && !bSelected)
	{
		CRect rect(0, 0, 38, 38);

		pFileBmp->m_bIsSelect = FALSE;

		pFileBmp->AutoRedraw(&rect);
	}
}

/*
void CFileBmp::ResetBmp(BOOL bRedraw)
{
CBmp::ResetBmp(FALSE);

m_lID = -1;
m_lPaziente = -1;
m_lEsame = -1;
m_iType = -1;
m_lFrame = -1;
DeleteObject(m_hMiniBmp);

if (bRedraw)
AutoRedraw();
}
*/

void CFileBmp::SendUpdateMessage()
{
	int nSelectedGlobal = 0;

	POSITION pos = CFileBmp::GetFirstSelectedPos();
	CObSelect* pSel = NULL;

	if (m_pEsamiView != NULL)
	{
		m_pEsamiView->m_lLocalImagesSelected = 0;
		m_pEsamiView->m_lLocalMultiPageTiffSelected = 0;
	}

	while (pos != NULL)
	{
		pSel = CFileBmp::GetNextSelected(pos);

		if (pSel != NULL)
		{
			if (pSel->m_bIsGlobal == FALSE)
			{
				if (m_pEsamiView != NULL)
					m_pEsamiView->m_lLocalImagesSelected++;
			}
			else
			{
				nSelectedGlobal++;
			}

			if (m_pEsamiView != NULL)
				if (pSel->m_iType == _mptiff_)
					m_pEsamiView->m_lLocalMultiPageTiffSelected++;
		}
	}

	if ((m_pEsamiView != NULL) && (m_pEsamiView->m_pFormImmagini != NULL) && (::IsWindow(m_pEsamiView->m_pFormImmagini->GetSafeHwnd())))
		m_pEsamiView->m_pFormImmagini->SendMessage(MSG_UPDATE_SEL, (WPARAM)m_pEsamiView->m_lLocalImagesSelected, (LPARAM)nSelectedGlobal);

	if ((m_pEsamiView != NULL) && (m_pParentWnd != NULL) && (::IsWindow(m_pParentWnd->GetSafeHwnd())) && (m_pParentWnd != m_pEsamiView))
		m_pParentWnd->SendMessage(MSG_UPDATE_SEL, (WPARAM)m_pEsamiView->m_lLocalImagesSelected, (LPARAM)nSelectedGlobal);
}

void CFileBmp::SetAlbumType(BOOL bIsAlbumGlobal)
{
	m_bIsAlbumGlobal = bIsAlbumGlobal;
}

void CFileBmp::ShowTga()
{
	if (theApp.m_lRicercaCodiceEsame == 4)//RICERCA_PAZIENTE_FICHA
	{
		if (!FileMainIsPresent())
		{
			FleuryGetImagemAltraSede(m_pParentWnd, m_pEsamiView, m_lID);
		}
	}
	if (FileMainIsPresent())
	{
		switch (m_iType)
		{
		case _image_:
		case _mptiff_:
		{
			//Gabriel BUG 6225 - Lista DO
			if (!theApp.m_sConfigFormAlbumImgBtnImgOpenWhere.IsEmpty())
			{
				if (theApp.m_lInstanceCountCImageDlg == 0 && theApp.m_lInstanceCountCImageSimple2Dlg == 0)
				{
					CImageDlg* pDlgImage = NULL;
					pDlgImage = new CImageDlg(this, FALSE, m_lPaziente, m_lEsame, m_lID, m_iType, FALSE);

					//Gabriel BUG 6225 - Lista DO FIX
					/*if (m_pEsamiView->m_pImageDlg != NULL)
					m_pEsamiView->m_pImageDlg->SendMessage(EPM_EXAMCHANGED);*/

					m_pEsamiView->m_pImageDlg = pDlgImage;

					pDlgImage->m_bIsAlbumGlobal = m_bIsAlbumGlobal;
					pDlgImage->m_pEsamiView = m_pActiveView;

					if (pDlgImage->Create(IDD_IMAGE, this))
					{
						pDlgImage->ShowWindow(SW_SHOWMAXIMIZED);
					}
					else
						delete pDlgImage;
				}
			}
			else
			{
				//Gabriel BUG 6225 - Lista DO
				CImageDlg dlg(this, TRUE, m_lPaziente, m_lEsame, m_lID, m_iType, FALSE);

				dlg.m_bIsAlbumGlobal = m_bIsAlbumGlobal;
				dlg.m_pEsamiView = m_pActiveView;

				dlg.DoModal();

				if (dlg.m_bRequeryImage)
				{
					BOOL bDeselectImg = dlg.m_bDeselectImage;

					if (m_pParentAlbum != NULL)
						m_pParentAlbum->SendMessage(MSG_AFTER_ELABIMAGE, (WPARAM)bDeselectImg);
				}
			}
			break;
		}
		case _movie_:
		{
			m_pEsamiView->m_pImgManager->SetCurrentIDs(m_lPaziente, m_lEsame);

			if ((m_pActiveView != NULL) && (m_pActiveView->m_pFormImmagini != NULL))
			{
				CString strMyFile = m_pEsamiView->m_pImgManager->GetFullPath(m_lID);

				/*
				if ((theApp.m_lInterfacciaImageSI != 0) && (_access(strMyFile, 00) != 0))
				{
				if (strMyFile.Right(4).CompareNoCase(EXT_AVI) == 0)
				{
				strMyFile = strMyFile.Left(strMyFile.GetLength() - 4) + EXT_MPG;
				}
				else if (strMyFile.Right(4).CompareNoCase(EXT_MPG) == 0)
				{
				strMyFile = strMyFile.Left(strMyFile.GetLength() - 4) + EXT_AVI;
				}
				}
				*/

				if (m_bIsAlbumGlobal == FALSE)
					m_pActiveView->m_pFormImmagini->ViewFilmAndSelectFrame(strMyFile);
				else
					m_pActiveView->m_pFormImmagini->ViewFilm(strMyFile);
			}

			break;
		}
		case _dicom_:
		{
			m_pEsamiView->m_pImgManager->SetCurrentIDs(m_lPaziente, m_lEsame);

			if ((m_pActiveView != NULL) && (m_pActiveView->m_pFormImmagini != NULL))
			{
				CImageDicomDlg dlg(this, m_pEsamiView->m_pImgManager->GetFullPath(m_lID));
				dlg.DoModal();
			}

			break;
		}
		}
	}
}

// Sandro 26/11/2013 // conta il numero delle immagini da stampare partendo dalla lista di quelle selezionate //
long CFileBmp::CountPrinterList(UINT what)
{
	ASSERT((what == LOCAL_IMAGES) || (what == GLOBAL_IMAGES));

	long lReturn = 0;

	POSITION pos = m_listSelected.GetHeadPosition();
	while (pos != NULL)
	{
		CObSelect* pSel = (CObSelect*)m_listSelected.GetNext(pos);
		if (pSel != NULL)
		{
			switch (what)
			{
			case ALL_IMAGES:
			{
				lReturn++;

				break;
			}
			case LOCAL_IMAGES:
			{
				if (!pSel->m_bIsGlobal)
					lReturn++;

				break;
			}
			case GLOBAL_IMAGES:
			{
				if (pSel->m_bIsGlobal)
					lReturn++;

				break;
			}
			}
		}
	}

	return lReturn;
}

// Sandro 30/11/2010 // mi riempie la lista delle immagini da stampare partendo dalla lista di quelle selezionate //
long CFileBmp::FillImagesPrinterList(UINT what)
{
	ASSERT((what == LOCAL_IMAGES) || (what == GLOBAL_IMAGES));

	return FillImagesPrinterList(what, MAXINT);
}

// Sandro 30/11/2010 // mi riempie la lista delle immagini da stampare partendo dalla lista di quelle selezionate //
long CFileBmp::FillImagesPrinterList(UINT what, long lMaxImages)
{
	long lReturn = 0;

	m_listPrinter.RemoveAll();

	POSITION pos = m_listSelected.GetHeadPosition();
	while ((pos != NULL) && (lReturn < lMaxImages))
	{
		CObSelect* pSel = (CObSelect*)m_listSelected.GetNext(pos);

		if (pSel != NULL)
		{
			switch (what)
			{
			case ALL_IMAGES:
			{
				m_listPrinter.Add(pSel);
				lReturn++;
				break;
			}
			case LOCAL_IMAGES:
			{
				if (!pSel->m_bIsGlobal)
				{
					m_listPrinter.Add(pSel);
					lReturn++;
				}
				break;
			}
			case GLOBAL_IMAGES:
			{
				if (pSel->m_bIsGlobal)
				{
					m_listPrinter.Add(pSel);
					lReturn++;
				}
				break;
			}
			}
		}
	}

	return lReturn;
}

// Sandro 30/11/2010 // mi riempie la lista dei frames da stampare partendo dalla lista di immagini selezionate //
long CFileBmp::FillListImagesToPrint(CImgManager* pImgManager, CList<IMAGE_TO_PRINT*> *pListImagesToPrint)
{
	// svuoto la lista //
	while (pListImagesToPrint->GetCount() > 0)
	{
		delete pListImagesToPrint->GetTail();
		pListImagesToPrint->RemoveTail();
	}

	for (int i = 0; i < CFileBmp::m_listPrinter.GetSize(); i++)
	{
		CObSelect* pSel = (CObSelect*)CFileBmp::m_listPrinter.GetAt(i);

		switch (pSel->m_iType)
		{
		case _image_:
		case _dicom_:
		case _mptiff_:
		case _dicom4d_:
		{
			pImgManager->SetCurrentIDs(pSel->m_lPaziente, pSel->m_lEsame);
			if (theApp.m_lOnlyThisFrame < 0)
			{
				long lFrameCount = pImgManager->GetFrameCount(pSel->m_lID);

				for (int j = 0; j < lFrameCount; j++)
				{
					IMAGE_TO_PRINT *pITP = new(IMAGE_TO_PRINT);
					if (pITP != NULL)
					{
						pITP->m_lID = pSel->m_lID;
						pITP->m_lFrame = j;
						pITP->m_bConfirmed = pSel->m_bConfirmed;
						pITP->m_strDvdLabel = pSel->m_strDvdLabel;
						pITP->m_lPaziente = pSel->m_lPaziente;
						pITP->m_lEsame = pSel->m_lEsame;

						pListImagesToPrint->AddTail(pITP);
					}
				}
			}
			else
			{
				IMAGE_TO_PRINT *pITP = new(IMAGE_TO_PRINT);
				if (pITP != NULL)
				{
					pITP->m_lID = pSel->m_lID;
					pITP->m_lFrame = theApp.m_lOnlyThisFrame;
					pITP->m_bConfirmed = pSel->m_bConfirmed;
					pITP->m_strDvdLabel = pSel->m_strDvdLabel;
					pITP->m_lPaziente = pSel->m_lPaziente;
					pITP->m_lEsame = pSel->m_lEsame;

					pListImagesToPrint->AddTail(pITP);
				}

				break;
			}
			break;
		}
		case _movie_:
		case _pyramidalimage_:
		case _mp3audio_:
		{
			break;
		}
		}
	}

	return pListImagesToPrint->GetCount();
}

//Gabriel - BUG Refresh álbum
LRESULT CFileBmp::RefreshAlbum(WPARAM wParam, LPARAM lParam)
{
	if (m_pParentAlbum != NULL)
		m_pParentAlbum->SendMessage(MSG_REFRESH_ALBUM);

	return 0;
}