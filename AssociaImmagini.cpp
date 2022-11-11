#include "stdafx.h"
#include "Endox.h"
#include "AssociaImmagini.h"

#include <io.h>
#include <math.h>

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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAssociaImmagini::CAssociaImmagini(CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxResizableDlg(CAssociaImmagini::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);
	m_pEsamiView = pEsamiView;

	m_setOrgani.SetSortRecord("ID");
	m_setOrgani.OpenRecordset("CAssociaImmagini::CAssociaImmagini");

	m_nDiapoPage = 0;
	for(int i = 0; i < MAX_FOTO_BMP; i++)
		m_pFileFotoBmp[i] = NULL;

	m_nCurSel = -1;
}

CAssociaImmagini::~CAssociaImmagini(void)
{
	int i;

	for(i = 0; i < MAX_FOTO_BMP; i++)
	{
		if (m_pFileFotoBmp[i] != NULL)
		{
			::DestroyWindow(m_pFileFotoBmp[i]->GetSafeHwnd());
			delete m_pFileFotoBmp[i];
			m_pFileFotoBmp[i] = NULL;
		}
	}

	POSITION pos = m_ImgListOrgani.GetHeadPosition();
	while(pos != NULL)
	{
		DeleteObject(m_ImgListOrgani.GetAt(pos).img.hBmp);
		m_ImgListOrgani.GetNext(pos);
	}
	m_ImgListOrgani.RemoveAll();

	m_setOrgani.CloseRecordset("CAssociaImmagini::~CAssociaImmagini");
}

void CAssociaImmagini::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_COMMENTO, m_setOrgani.m_sDescrizione);
	DDX_Control(pDX, IDOK, m_ctrlButtonOK);
	DDX_Control (pDX, IDC_LIST_IMAGE, m_ctrlListImage);

	BOOL bIsPrevActive = !m_setOrgani.IsBOF();
	BOOL bIsNextActive = !m_setOrgani.IsEOF();
	if (bIsPrevActive && bIsNextActive)
	{
		m_setOrgani.MovePrev();

		if (m_setOrgani.IsBOF() == TRUE)
			bIsPrevActive = FALSE;

		m_setOrgani.MoveNext();
		m_setOrgani.MoveNext();

		if (m_setOrgani.IsEOF() == TRUE)
			bIsNextActive = FALSE;

		m_setOrgani.MovePrev();
	}
	GetDlgItem(IDC_FIRS_ORG)->EnableWindow(bIsPrevActive);
	GetDlgItem(IDC_PREV_ORG)->EnableWindow(bIsPrevActive);
	GetDlgItem(IDC_NEXT_ORG)->EnableWindow(bIsNextActive);
	GetDlgItem(IDC_LAST_ORG)->EnableWindow(bIsNextActive);

	BOOL bIsPrevImmActive = (m_nDiapoPage == 0) ? FALSE : TRUE;
	BOOL bIsNextImmActive = (m_nDiapoPage == (m_nMaxDiapo / MAX_FOTO_BMP)) ? FALSE : TRUE;
	GetDlgItem(IDC_FIRS_IMM)->EnableWindow(bIsPrevImmActive);
	GetDlgItem(IDC_PREV_IMM)->EnableWindow(bIsPrevImmActive);
	GetDlgItem(IDC_NEXT_IMM)->EnableWindow(bIsNextImmActive);
	GetDlgItem(IDC_LAST_IMM)->EnableWindow(bIsNextImmActive);
}

BEGIN_MESSAGE_MAP(CAssociaImmagini, CEndoxResizableDlg)
	ON_WM_PAINT()
	ON_WM_SIZE()

	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()

	ON_BN_CLICKED(IDC_FIRS_ORG, OnFrstOrg)
	ON_BN_CLICKED(IDC_PREV_ORG, OnPrevOrg)
	ON_BN_CLICKED(IDC_NEXT_ORG, OnNextOrg)
	ON_BN_CLICKED(IDC_LAST_ORG, OnLastOrg)
	ON_BN_CLICKED(IDC_FIRS_IMM, OnFrstImm)
	ON_BN_CLICKED(IDC_PREV_IMM, OnPrevImm)
	ON_BN_CLICKED(IDC_NEXT_IMM, OnNextImm)
	ON_BN_CLICKED(IDC_LAST_IMM, OnLastImm)

	ON_REGISTERED_MESSAGE(MSG_SELECT_BMP, OnSelectBmp)

	ON_NOTIFY(NM_DBLCLK, IDC_LIST_IMAGE, OnNMDblclkListImage)
END_MESSAGE_MAP()

BOOL CAssociaImmagini::OnInitDialog() 
{
	int i;

	CEndoxResizableDlg::OnInitDialog();

	AddAnchor(IDC_LIST_IMAGE, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDC_FRAME, CSize(0, 0), CSize(34, 100));
	AddAnchor(IDC_COMMENTO, CSize(0, 100), CSize(34, 100));
	AddAnchor(IDC_FIRS_ORG, CSize(17, 100), CSize(17, 100));
	AddAnchor(IDC_PREV_ORG, CSize(17, 100), CSize(17, 100));
	AddAnchor(IDC_NEXT_ORG, CSize(17, 100), CSize(17, 100));
	AddAnchor(IDC_LAST_ORG, CSize(17, 100), CSize(17, 100));
	AddAnchor(IDC_FRAME1, CSize(34, 0), CSize(67, 25));
	AddAnchor(IDC_FRAME2, CSize(67, 0), CSize(100, 25));
	AddAnchor(IDC_FRAME3, CSize(34, 25), CSize(67, 50));
	AddAnchor(IDC_FRAME4, CSize(67, 25), CSize(100, 50));
	AddAnchor(IDC_FRAME5, CSize(34, 50), CSize(67, 75));
	AddAnchor(IDC_FRAME6, CSize(67, 50), CSize(100, 75));
	AddAnchor(IDC_FRAME7, CSize(34, 75), CSize(67, 100));
	AddAnchor(IDC_FRAME8, CSize(67, 75), CSize(100, 100));
	AddAnchor(IDOK, CSize(34, 100), CSize(34, 100));
	AddAnchor(IDC_FIRS_IMM, CSize(67, 100), CSize(67, 100));
	AddAnchor(IDC_PREV_IMM, CSize(67, 100), CSize(67, 100));
	AddAnchor(IDC_NEXT_IMM, CSize(67, 100), CSize(67, 100));
	AddAnchor(IDC_LAST_IMM, CSize(67, 100), CSize(67, 100));

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	m_BtnOrgFirst.AutoLoad(IDC_FIRS_ORG, this);
	m_BtnOrgPrev.AutoLoad(IDC_PREV_ORG, this);
	m_BtnOrgNext.AutoLoad(IDC_NEXT_ORG, this);
	m_BtnOrgLast.AutoLoad(IDC_LAST_ORG, this);
	m_BtnImmFirst.AutoLoad(IDC_FIRS_IMM, this);
	m_BtnImmPrev.AutoLoad(IDC_PREV_IMM, this);
	m_BtnImmNext.AutoLoad(IDC_NEXT_IMM, this);
	m_BtnImmLast.AutoLoad(IDC_LAST_IMM, this);

	CWnd* pBmpFotoFrame[MAX_FOTO_BMP];
	pBmpFotoFrame[0] = (CWnd*)GetDlgItem(IDC_FRAME1);
	pBmpFotoFrame[1] = (CWnd*)GetDlgItem(IDC_FRAME2);
	pBmpFotoFrame[2] = (CWnd*)GetDlgItem(IDC_FRAME3);
	pBmpFotoFrame[3] = (CWnd*)GetDlgItem(IDC_FRAME4);
	pBmpFotoFrame[4] = (CWnd*)GetDlgItem(IDC_FRAME5);
	pBmpFotoFrame[5] = (CWnd*)GetDlgItem(IDC_FRAME6);
	pBmpFotoFrame[6] = (CWnd*)GetDlgItem(IDC_FRAME7);
	pBmpFotoFrame[7] = (CWnd*)GetDlgItem(IDC_FRAME8);

	for(i = 0; i < MAX_FOTO_BMP; i++)
	{
		if (CFileBmp::CreateBmp(m_pEsamiView, this, pBmpFotoFrame[i], &m_pFileFotoBmp[i]))
		{
			m_pFileFotoBmp[i]->SetMouseMode(BMP_L_NORMALMODE, BMP_R_SENDTOPARENT);
			m_pFileFotoBmp[i]->SetAlbumType(FALSE); 
			m_pFileFotoBmp[i]->ShowWindow(TRUE);
		}
	}

	CFileBmp::DeleteListSelected(LOCAL_IMAGES);
	AfterMoveEsame(TRUE);

	// Sandro Gallina - 26/04/2005 --> //
	if ((m_setOrgani.IsBOF() == FALSE) && (m_setOrgani.IsEOF() == FALSE))
	{
		m_setOrgani.MoveFirst();
		while(m_setOrgani.IsEOF() == FALSE)
			m_setOrgani.MoveNext();
		m_setOrgani.MoveFirst();
	}
	if (m_setOrgani.GetRecordCount() >= 5)
	{
		ModificaInterfaccia(TRUE);

		m_listImage.Create(HSIZE_PAL_4, VSIZE_PAL_4, ILC_COLOR32, 0, 1);
		m_ctrlListImage.SetExtendedStyle(m_ctrlListImage.GetExtendedStyle() | LVS_EX_BORDERSELECT);
		m_ctrlListImage.SetImageList(&m_listImage, LVSIL_NORMAL);

		int iHSpace;
		int iVSpace;
		CRect rectTemp;
		m_ctrlListImage.GetClientRect(&rectTemp);
		iHSpace = (rectTemp.Width() / 4) - 6;
		iVSpace = (rectTemp.Height() / 4) - 0;
		m_ctrlListImage.SetIconSpacing(iHSpace, iVSpace);

		RiempiListaImmagini();
	}
	// <-- Sandro Gallina - 26/04/2005 //

	m_lPaziente = m_pEsamiView->m_pEsamiSet->m_lPaziente;
	m_lEsame = m_pEsamiView->m_pEsamiSet->m_lContatore;
	m_pEsamiView->m_pImgManager->SetCurrentIDs(m_lPaziente, m_lEsame);
	m_bConfirmed = m_pEsamiView->m_pImgManager->IsExamConfirmed(m_strDvdLabel);

	theApp.LocalizeDialog(this, CAssociaImmagini::IDD, "AssociaImmagini");

    MoveImageOrg();

	return TRUE;  
}

void CAssociaImmagini::AfterMoveEsame(BOOL bIsSetValid, BOOL bRewind)
{
	ResetVetDiapo(TRUE);

	if (bIsSetValid)
		m_nMaxDiapo = FillDiapoIndex();

	if (bRewind == TRUE)
		OnPageFirst();
	else
		RequeryPage();
}

void CAssociaImmagini::ResetVetDiapo(BOOL bReposition)
{   
	POSITION pos = m_ImgListOrgani.GetHeadPosition();
	while(pos != NULL)
	{
		DeleteObject(m_ImgListOrgani.GetAt(pos).img.hBmp);
		m_ImgListOrgani.GetNext(pos);
	}
	m_ImgListOrgani.RemoveAll();

	if (bReposition)
	{
		m_nMaxDiapo = 0;
		m_nDiapoPage = -1;
	}
}  	

int CAssociaImmagini::FillDiapoIndex()
{   
	int iReturn;
	CImgList listImg;

	BeginWaitCursor();
	m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore);

	DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
	iReturn = m_pEsamiView->m_pImgManager->GetImgList(&listImg) - 1;
	if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
		CLogFileWriter::Get()->WriteLogLine0_ImmRetrieve(timeGetTime() - timeForLog, m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore, iReturn + 1, "CAssociaImmagini::FillDiapoIndex");

	m_ImgListOrgani = listImg;
	CaricaPunti();
	EndWaitCursor();

	return iReturn;
}

void CAssociaImmagini::OnPageFirst() 
{
    m_nDiapoPage = 0;
    MoveImageImm();
}

void CAssociaImmagini::MoveImageImm()
{
	int nBase = m_nDiapoPage * MAX_FOTO_BMP;

	m_BtnImmFirst.EnableWindow(m_nDiapoPage > 0);
	m_BtnImmPrev.EnableWindow(m_nDiapoPage > 0);
	m_BtnImmNext.EnableWindow(m_nDiapoPage < (m_nMaxDiapo / MAX_FOTO_BMP));
	m_BtnImmLast.EnableWindow(m_nDiapoPage < (m_nMaxDiapo / MAX_FOTO_BMP));

	if (m_pEsamiView->m_pEsamiSet->IsEOF())
	{
		for(int i = 0; i < MAX_FOTO_BMP; i++)
			m_pFileFotoBmp[i]->ResetImage();

		return;	
	}		

	long lPaziente;
	long lEsame;
	CString strDvdLabel;
	BOOL bConfirmed = m_pEsamiView->m_pImgManager->IsExamConfirmed(strDvdLabel);
	m_pEsamiView->m_pImgManager->GetCurrentIDs(lPaziente, lEsame);
	for(int i = 0; i < MAX_FOTO_BMP; i++)
	{
		if (nBase + i <= m_nMaxDiapo)
		{
			m_pFileFotoBmp[i]->LoadImage(lPaziente, lEsame, &m_ImgListOrgani, nBase + i, bConfirmed, strDvdLabel, CARICA_MINI);

			if (m_pFileFotoBmp[i]->GetPointNumber() == m_nCurSel)
				m_pFileFotoBmp[i]->SetPointColor(RGB_WHITE, RGB_GRAY_DARK, TRUE);
			else
				m_pFileFotoBmp[i]->SetPointColor(RGB_GRAY_DARK, RGB_WHITE, TRUE);

			CFileBmp::ReselectBmp(m_pFileFotoBmp[i], FALSE);
		}
		else
		{
			m_pFileFotoBmp[i]->ResetImage();
		}
	}
}

void CAssociaImmagini::RequeryPage() 
{
    if (m_nDiapoPage < 0)
	   m_nDiapoPage = 0;
	if (m_nDiapoPage > (m_nMaxDiapo / MAX_FOTO_BMP))
		m_nDiapoPage = m_nMaxDiapo / MAX_FOTO_BMP;
	MoveImageImm();
}

void CAssociaImmagini::OnFrstImm() 
{
    m_nDiapoPage = 0;
    MoveImageImm();
}

void CAssociaImmagini::OnPrevImm() 
{
    m_nDiapoPage--;
	MoveImageImm();
}

void CAssociaImmagini::OnNextImm() 
{
	m_nDiapoPage++;
	MoveImageImm();
}

void CAssociaImmagini::OnLastImm() 
{
	m_nDiapoPage = m_nMaxDiapo / MAX_FOTO_BMP;
	MoveImageImm();
}

void CAssociaImmagini::AlbumRedraw()
{
	for(int i = 0; i < MAX_FOTO_BMP; i++)
		m_pFileFotoBmp[i]->AutoRedraw();
}

void CAssociaImmagini::OnCancel() 
{
	if (m_ctrlListImage.IsWindowVisible())
		CEndoxResizableDlg::OnCancel();
}

void CAssociaImmagini::OnOK() 
{
	if (!m_ctrlListImage.IsWindowVisible())
	{
		SalvaPunti();
		CEndoxResizableDlg::OnOK();
	}
}

void CAssociaImmagini::OnNMDblclkListImage(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos = m_ctrlListImage.GetFirstSelectedItemPosition();

	if (pos != NULL)
	{
		int iCurSel = m_ctrlListImage.GetNextSelectedItem(pos);

		m_setOrgani.SetAbsolutePosition(iCurSel + 1);
		MoveImageOrg();

		ModificaInterfaccia(FALSE);
	}

	*pResult = 0;
}

void CAssociaImmagini::RiempiListaImmagini()
{
	int i = 0;

	if ((m_setOrgani.IsBOF() == FALSE) && (m_setOrgani.IsEOF() == FALSE))
	{
		m_setOrgani.MoveFirst();
		while(m_setOrgani.IsEOF() == FALSE)
			m_setOrgani.MoveNext();

		m_ctrlListImage.DeleteAllItems(); // Sandro - 18/03/2010 //
		m_listImage.SetImageCount(m_setOrgani.GetRecordCount());

		m_setOrgani.MoveFirst();
		while(m_setOrgani.IsEOF() == FALSE)
		{
			char szPathImm[MAX_PATH];
			char szPathMin[MAX_PATH];
			if (CImgArchive(&theApp.m_dbEndox).GetArchivePrimary(szPathImm, szPathMin, MAX_PATH))
			{
				CString strOrganFile;
				strOrganFile.Format("%s\\Organ\\%06li.org", szPathImm /*theApp.m_sPathImageHD*/, m_setOrgani.m_lID);

				HBITMAP hBit;
				if (m_pEsamiView->m_pImgManager->LoadLocalImageEx(strOrganFile, &hBit, NULL, HSIZE_PAL_4, VSIZE_PAL_4) > 0)
				{
					if (hBit != INVALID_HANDLE_VALUE)
					{
						m_ctrlListImage.InsertItem(i, m_setOrgani.m_sDescrizione, i);
						m_listImage.Replace(i, CBitmap::FromHandle(hBit), RGB(0, 0, 0));
					}
				}
				DeleteObject(hBit);

				i++;
				m_setOrgani.MoveNext();
			}
			else
			{
				ASSERT(FALSE);
			}
		}
	}
}

void CAssociaImmagini::ModificaInterfaccia(BOOL bShowAlbum)
{
	int i;

	for(i = 0; i < MAX_FOTO_BMP; i ++)
		m_pFileFotoBmp[i]->ShowWindow(!bShowAlbum);

	GetDlgItem(IDC_FRAME)->ShowWindow(!bShowAlbum);
	GetDlgItem(IDC_COMMENTO)->ShowWindow(!bShowAlbum);
	GetDlgItem(IDC_FIRS_ORG)->ShowWindow(!bShowAlbum);
	GetDlgItem(IDC_PREV_ORG)->ShowWindow(!bShowAlbum);
	GetDlgItem(IDC_NEXT_ORG)->ShowWindow(!bShowAlbum);
	GetDlgItem(IDC_LAST_ORG)->ShowWindow(!bShowAlbum);
	GetDlgItem(IDC_FRAME1)->ShowWindow(!bShowAlbum);
	GetDlgItem(IDC_FRAME2)->ShowWindow(!bShowAlbum);
	GetDlgItem(IDC_FRAME3)->ShowWindow(!bShowAlbum);
	GetDlgItem(IDC_FRAME4)->ShowWindow(!bShowAlbum);
	GetDlgItem(IDC_FRAME5)->ShowWindow(!bShowAlbum);
	GetDlgItem(IDC_FRAME6)->ShowWindow(!bShowAlbum);
	GetDlgItem(IDC_FRAME7)->ShowWindow(!bShowAlbum);
	GetDlgItem(IDC_FRAME8)->ShowWindow(!bShowAlbum);
	GetDlgItem(IDC_FIRS_IMM)->ShowWindow(!bShowAlbum);
	GetDlgItem(IDC_PREV_IMM)->ShowWindow(!bShowAlbum);
	GetDlgItem(IDC_NEXT_IMM)->ShowWindow(!bShowAlbum);
	GetDlgItem(IDC_LAST_IMM)->ShowWindow(!bShowAlbum);
	GetDlgItem(IDOK)->ShowWindow(!bShowAlbum);

	m_ctrlListImage.ShowWindow(bShowAlbum);

	if (bShowAlbum == TRUE)
		m_ctrlListImage.SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	else
		m_ctrlListImage.ShowWindow(FALSE);
}

void CAssociaImmagini::OnFrstOrg() 
{
	BeginWaitCursor();
	m_nCurSel = -1;
	m_setOrgani.MoveFirst();
    MoveImageOrg();
	EndWaitCursor();
}

void CAssociaImmagini::OnPrevOrg() 
{
	BeginWaitCursor();
	m_nCurSel = -1;
	m_setOrgani.MovePrev();
	MoveImageOrg();
	EndWaitCursor();
}

void CAssociaImmagini::OnNextOrg() 
{
	BeginWaitCursor();
	m_nCurSel = -1;
	m_setOrgani.MoveNext();
	MoveImageOrg();
	EndWaitCursor();
}

void CAssociaImmagini::OnLastOrg() 
{
	BeginWaitCursor();
	m_nCurSel = -1;
	m_setOrgani.MoveLast();
	MoveImageOrg();
	EndWaitCursor();
}

void CAssociaImmagini::MoveImageOrg()
{
	BOOL bOk = FALSE;
	if ((m_setOrgani.IsBOF() == FALSE) && (m_setOrgani.IsEOF() == FALSE))
	{
		char szPathImm[MAX_PATH];
		char szPathMin[MAX_PATH];
		if (CImgArchive(&theApp.m_dbEndox).GetArchivePrimary(szPathImm, szPathMin, MAX_PATH))
		{
			CString strOrganFile;
			strOrganFile.Format("%s\\Organ\\%06li.org", szPathImm /*theApp.m_sPathImageHD*/, m_setOrgani.m_lID);

			HBITMAP hBit;
			m_dstRect = CRect(0, 0, 0, 0);
			if (m_pEsamiView->m_pImgManager->LoadLocalImageEx(strOrganFile, &hBit) > 0)
			{
				if (hBit != INVALID_HANDLE_VALUE)
				{
					bOk = m_Dib.Attach(CDib::BitmapToDIB(hBit, NULL), TRUE);

					// dimensione della bitmap //
					CRect srcRect(0, 0, m_Dib.Width(), m_Dib.Height());	

					// dimensione e posizione del frame //
					CRect rect;
					GetDlgItem(IDC_FRAME)->GetWindowRect(rect);
					// GetDlgItem(IDC_FRAME)->ScreenToClient(rect);

					// dimensione del frame //
					m_dstRect = rect;
					m_dstRect.OffsetRect(-m_dstRect.left, -m_dstRect.top);

					// proporzioni //
					double dFactorX = (double)m_dstRect.Width()  / (double)m_Dib.Width();
					double dFactorY = (double)m_dstRect.Height() / (double)m_Dib.Height();

					// dimensioni dell'immagine all'interno del frame //
					m_dstRect.right  = (LONG)(m_dstRect.left + min(dFactorX, dFactorY) * m_Dib.Width());
					m_dstRect.bottom = (LONG)(m_dstRect.top  + min(dFactorX, dFactorY) * m_Dib.Height());

					// dimensioni normalizzate //
					CRect rectTmp(m_dstRect);
					rectTmp.left   += (abs(m_dstRect.Width() - rect.Width()) / 2) + 1;
					rectTmp.right  += (abs(m_dstRect.Width() - rect.Width()) / 2);
					rectTmp.top    += (abs(m_dstRect.Height() - rect.Height()) / 2) + 1;
					rectTmp.bottom += (abs(m_dstRect.Height() - rect.Height()) / 2);
					m_dstRect = rectTmp;
				}
			}
			DeleteObject(hBit);
		}
		else
		{
			ASSERT(FALSE);
		}
	}
	if (!bOk)
	{
		m_Dib.ReleaseContents();
		m_Dib.Detach();
	}

	SelezionaImmagini(TRUE);
	UpdateData(FALSE);
	RedrawWindow();
}

void CAssociaImmagini::OnPaint() 
{
	CPaintDC dc(this);

	if ((m_setOrgani.IsBOF() == FALSE) && (m_setOrgani.IsEOF() == FALSE))
	{
		if (CWnd* pFrame = GetDlgItem(IDC_FRAME))
		{
			CClientDC dcp(pFrame);

			// calcolo l'area del rect client //
			CRect rectClient;
			GetDlgItem(IDC_FRAME)->GetWindowRect(&rectClient);
			ScreenToClient(&rectClient);
			rectClient.DeflateRect(1, 1);

			if (!m_Dib.IsValidDib())
			{
				// se le dib non è valida svuoto l'immagine //

	   			CBrush brushNull;
				brushNull.CreateSolidBrush(RGB(0, 0, 0));
				dc.FillRect(rectClient, &brushNull);
				brushNull.DeleteObject();
			}
			else
			{
				// disegno la dib //
				m_Dib.PaintDIB(&dc, rectClient);
			}

			CPen penSel(PS_SOLID, 1, RGB_WHITE);
			CBrush brushSel(RGB_WHITE);
			CPen penNormal(PS_SOLID, 1, RGB_GRAY_DARK);
			CBrush brushNormal(RGB_GRAY_DARK);

			CRect rectFrame;
			pFrame->GetWindowRect(rectFrame);
			ScreenToClient(rectFrame);
			dcp.SetBkMode(TRANSPARENT);

			int i = 0;
			POSITION pos = listPunti.GetHeadPosition();
			while(pos != NULL)
			{
				if (listPunti.GetAt(pos).lIdOrgano == m_setOrgani.m_lID)
				{
					CPen* pOldPen;
					CBrush* pOldBrush;
					CFont* pOldFont = dcp.SelectObject(&theApp.m_fontBold);
					if (i == m_nCurSel)
					{
						pOldPen = dcp.SelectObject(&penSel);
						pOldBrush = dcp.SelectObject(&brushSel);
						dcp.SetTextColor(RGB_GRAY_DARK);
					}
					else
					{
						pOldPen = dcp.SelectObject(&penNormal);
						pOldBrush = dcp.SelectObject(&brushNormal);
						dcp.SetTextColor(RGB_WHITE);
					}

					long lX = listPunti.GetAt(pos).lX;
					long lY = listPunti.GetAt(pos).lY;
					MillesimiPixel(lX, lY);
					lX -= rectFrame.left;
					lY -= rectFrame.top;

					CRect rectTemp(lX - RAGGIO_PUNTO, lY - RAGGIO_PUNTO, lX + RAGGIO_PUNTO, lY + RAGGIO_PUNTO);

					dcp.Ellipse(rectTemp);

					CString strTemp;
					strTemp.Format("%d", i + 1);
					dcp.DrawText(strTemp, rectTemp, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

 					dcp.SelectObject(pOldPen);
					dcp.SelectObject(pOldBrush);
					dcp.SelectObject(pOldFont);
				}

				listPunti.GetNext(pos);
				i++;
			}

			penSel.DeleteObject();
			brushSel.DeleteObject();
			penNormal.DeleteObject();
			brushNormal.DeleteObject();
		}
	}
}

void CAssociaImmagini::OnSize(UINT nType, int cx, int cy) 
{
	int i;

	CEndoxResizableDlg::OnSize(nType, cx, cy);

	for(i = 0; i < MAX_FOTO_BMP; i++)
		if (m_pFileFotoBmp[i] != NULL)
			m_pFileFotoBmp[i]->SendMessage(EPM_RESIZE_FORM);
}

void CAssociaImmagini::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect rectFrame;
	GetDlgItem(IDC_FRAME)->GetWindowRect(rectFrame);
	ScreenToClient(rectFrame);

	CRect rectImage = m_dstRect;
	rectImage.OffsetRect(rectFrame.left, rectFrame.top);
	rectImage.DeflateRect(0, 0, 1, 1); // (RAGGIO_PUNTO, RAGGIO_PUNTO);

	if (rectImage.PtInRect(point) == TRUE)
	{
		point.x = max(point.x, rectImage.left + RAGGIO_PUNTO);
		point.x = min(point.x, rectImage.right - RAGGIO_PUNTO);
		point.y = max(point.y, rectImage.top + RAGGIO_PUNTO);
		point.y = min(point.y, rectImage.bottom - RAGGIO_PUNTO);
		SelezionaPunto(m_setOrgani.m_lID, point.x, point.y);
	}
}

void CAssociaImmagini::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CRect rectFrame;
	GetDlgItem(IDC_FRAME)->GetWindowRect(rectFrame);
	ScreenToClient(rectFrame);

	CRect rectImage = m_dstRect;
	rectImage.OffsetRect(rectFrame.left, rectFrame.top);

	if (rectImage.PtInRect(point) == TRUE)
		EliminaPunto(m_setOrgani.m_lID, point.x, point.y);
}

void CAssociaImmagini::OnMouseMove(UINT nFlags, CPoint point) 
{
	if ((nFlags & MK_LBUTTON) == 0)
		return;

	CRect rectFrame;
	GetDlgItem(IDC_FRAME)->GetWindowRect(rectFrame);
	ScreenToClient(rectFrame);

	CRect rectImage = m_dstRect;
	rectImage.OffsetRect(rectFrame.left, rectFrame.top);
	rectImage.DeflateRect(0, 0, 1, 1); // (RAGGIO_PUNTO, RAGGIO_PUNTO);

	if (rectImage.PtInRect(point) == TRUE)
	{
		point.x = max(point.x, rectImage.left + RAGGIO_PUNTO);
		point.x = min(point.x, rectImage.right - RAGGIO_PUNTO);
		point.y = max(point.y, rectImage.top + RAGGIO_PUNTO);
		point.y = min(point.y, rectImage.bottom - RAGGIO_PUNTO);
		ModificaPunto(point.x, point.y);
	}
}

int CAssociaImmagini::AggiungiPunto(long lIdPunto, long lIdOrgano, long lX, long lY)
{
	tagPunti puntoTemp;

	puntoTemp.lIdPunto = lIdPunto;
	puntoTemp.lIdOrgano = lIdOrgano;
	puntoTemp.lX = lX;
	puntoTemp.lY = lY;
	PixelMillesimi(puntoTemp.lX, puntoTemp.lY);

	TRACE("--> Aggiunto punto Punto:%li Organo:%li X:%li Y:%li\n", puntoTemp.lIdPunto, puntoTemp.lIdOrgano, puntoTemp.lX, puntoTemp.lY);
	listPunti.AddTail(puntoTemp);

	return(listPunti.GetCount() - 1);
}

void CAssociaImmagini::EliminaPunto(long lIdOrgano, long lX, long lY)
{
	int nIndex = TrovaPunto(lIdOrgano, lX, lY);

	if (nIndex >= 0) // il punto esiste, lo cancello //
	{
		for(int i = 0; i < MAX_FOTO_BMP; i++)
		{
			if (m_pFileFotoBmp[i]->GetPointNumber() == nIndex)
			{
				m_pFileFotoBmp[i]->SetPointNumber(-1, FALSE);
			}
			else
			{
				if (m_pFileFotoBmp[i]->GetPointNumber() > nIndex)
					m_pFileFotoBmp[i]->SetPointNumber(m_pFileFotoBmp[i]->GetPointNumber() - 1, FALSE);
			}
		}

		POSITION pos = m_ImgListOrgani.GetHeadPosition();
		while(pos != NULL)
		{
			if (m_ImgListOrgani.GetAt(pos).iPunto == nIndex)
			{
				IMG_ORGANI img_organi;

				img_organi = m_ImgListOrgani.GetAt(pos);
				img_organi.iPunto = -1;
				m_ImgListOrgani.SetAt(pos, img_organi);

				CImmaginiPuntiSet().SetIDPunto(m_ImgListOrgani.GetAt(pos).img.lID, -1);
			}
			else
			{
				if (m_ImgListOrgani.GetAt(pos).iPunto > nIndex)
				{
					IMG_ORGANI img_organi;

					img_organi = m_ImgListOrgani.GetAt(pos);
					img_organi.iPunto--;
					m_ImgListOrgani.SetAt(pos, img_organi);
				}
			}

			m_ImgListOrgani.GetNext(pos);
		}

		pos = listPunti.FindIndex(nIndex);
		if (pos != NULL)
		{
			TRACE("--> Rimosso punto Punto:%li Organo:%li X:%li Y:%li\n", listPunti.GetAt(pos).lIdPunto, listPunti.GetAt(pos).lIdOrgano, listPunti.GetAt(pos).lX, listPunti.GetAt(pos).lY);
			listPunti.RemoveAt(pos);

			m_nCurSel = -1;
			SelezionaImmagini(FALSE);
		}

		RedrawWindow(NULL, NULL, RDW_INVALIDATE|RDW_NOERASE); 
	}
}

void CAssociaImmagini::ModificaPunto(long lX, long lY)
{
	POSITION pos = listPunti.FindIndex(m_nCurSel);
	if (pos != NULL)
	{
		tagPunti puntoTemp = listPunti.GetAt(pos);

		puntoTemp.lX = lX;
		puntoTemp.lY = lY;
		PixelMillesimi(puntoTemp.lX, puntoTemp.lY);

		TRACE("--> Modificato punto Punto:%li Organo:%li X:%li Y:%li\n", puntoTemp.lIdPunto, puntoTemp.lIdOrgano, puntoTemp.lX, puntoTemp.lY);
		listPunti.SetAt(pos, puntoTemp);

		RedrawWindow(NULL, NULL, RDW_INVALIDATE|RDW_NOERASE); 
	}
}

void CAssociaImmagini::SelezionaPunto(long lIdOrgano, long lX, long lY)
{
	int nIndex = TrovaPunto(lIdOrgano, lX, lY);

	if (nIndex >= 0)
		m_nCurSel = nIndex; // il punto esiste già, mi basta soltanto selezionarlo //
	else
		m_nCurSel = AggiungiPunto(-1, m_setOrgani.m_lID, lX, lY); // il punto non esiste, lo aggiungo e lo seleziono //

	SelezionaImmagini(FALSE);
	RedrawWindow(NULL, NULL, RDW_INVALIDATE|RDW_NOERASE); 
}

int CAssociaImmagini::TrovaPunto(long lIdOrgano, long lX, long lY)
{
	long lTempX;
	long lTempY;
	int nIndex = 0;

	POSITION pos = listPunti.GetHeadPosition();
	while(pos != NULL)
	{
		if (listPunti.GetAt(pos).lIdOrgano == lIdOrgano)
		{
			lTempX = listPunti.GetAt(pos).lX;
			lTempY = listPunti.GetAt(pos).lY;
			MillesimiPixel(lTempX, lTempY);

			if (sqrt(pow((double)(lX - lTempX), 2) + pow((double)(lY - lTempY), 2)) < RAGGIO_PUNTO)
				return nIndex;
		}

		listPunti.GetNext(pos);
		nIndex++;
	}

	return -1;
}

void CAssociaImmagini::SelezionaImmagini(BOOL bRedraw)
{
	if (m_nCurSel >= 0)
	{
		for(int i = 0; i < MAX_FOTO_BMP; i++)
		{
			if (m_pFileFotoBmp[i]->GetPointNumber() == m_nCurSel)
				m_pFileFotoBmp[i]->SetPointColor(RGB_WHITE, RGB_GRAY_DARK, bRedraw);
			else
				m_pFileFotoBmp[i]->SetPointColor(RGB_GRAY_DARK, RGB_WHITE, bRedraw);
		}
	}
	else
	{
		for(int i = 0; i < MAX_FOTO_BMP; i++)
			m_pFileFotoBmp[i]->SetPointColor(RGB_GRAY_DARK, RGB_WHITE, bRedraw);
	}
}

void CAssociaImmagini::MillesimiPixel(long &lX, long &lY)
{
	CRect rectFrame;
	GetDlgItem(IDC_FRAME)->GetWindowRect(rectFrame);
	ScreenToClient(rectFrame);

	CRect rectImage = m_dstRect;
	rectImage.OffsetRect(rectFrame.left, rectFrame.top);

	// TRACE2("---> MillesimiPixel PIXEL %li %li\n", lX, lY);
	lX = (long)((float)(lX * rectImage.Width()) / 100000.0f) + rectImage.left + 1;
	lY = (long)((float)(lY * rectImage.Height()) / 100000.0f) + rectImage.top + 1;
	// TRACE2("---> MillesimiPixel MILLS %li %li\n", lX, lY);
}

void CAssociaImmagini::PixelMillesimi(long &lX, long &lY)
{
	CRect rectFrame;
	GetDlgItem(IDC_FRAME)->GetWindowRect(rectFrame);
	ScreenToClient(rectFrame);

	CRect rectImage = m_dstRect;
	rectImage.OffsetRect(rectFrame.left, rectFrame.top);

	// TRACE2("---> PixelMillesimi MILLS %li %li\n", lX, lY);
	lX = (long)((float)((lX - rectImage.left) * 100000) / (float)rectImage.Width());
	lY = (long)((float)((lY - rectImage.top) * 100000) / (float)rectImage.Height());
	// TRACE2("---> PixelMillesimi PIXEL %li %li\n", lX, lY);
}

LRESULT CAssociaImmagini::OnSelectBmp(WPARAM wParam, LPARAM lParam)
{
	CBmp* pBmp = (CBmp*)lParam;

	if (m_nCurSel >= 0)
	{
		if (pBmp->GetPointNumber() == m_nCurSel)
		{
			pBmp->SetPointNumber(-1, TRUE);
			
			POSITION pos = m_ImgListOrgani.GetHeadPosition();
			while(pos != NULL)
			{
				if (m_ImgListOrgani.GetAt(pos).img.lID == pBmp->m_lID)
				{
					IMG_ORGANI img_organi = m_ImgListOrgani.GetAt(pos);
					img_organi.iPunto = -1;
					m_ImgListOrgani.SetAt(pos, img_organi);
					break;
				}

				m_ImgListOrgani.GetNext(pos);
			}

			CImmaginiPuntiSet().SetIDPunto(pBmp->m_lID, -1);
		}
		else
		{
			pBmp->SetPoint(m_nCurSel, RGB_WHITE, RGB_GRAY_DARK, TRUE);

			POSITION pos = m_ImgListOrgani.GetHeadPosition();
			while(pos != NULL)
			{
				if (m_ImgListOrgani.GetAt(pos).img.lID == pBmp->m_lID)
				{
					IMG_ORGANI img_organi = m_ImgListOrgani.GetAt(pos);
					img_organi.iPunto = m_nCurSel;
					m_ImgListOrgani.SetAt(pos, img_organi);
					break;
				}

				m_ImgListOrgani.GetNext(pos);
			}
		}
	}

	return 0;
}

void CAssociaImmagini::CaricaPunti()
{
	long lIdPunto;
	long lIdOrgano;
	long lX;
	long lY;
	IMG_ORGANI img_organi;

	BOOL bFindIndex;

	POSITION pos1 = m_ImgListOrgani.GetHeadPosition();
	POSITION pos2;

	TRACE0("--> Rimossi tutti i punti\n");
	listPunti.RemoveAll();
	while(pos1 != NULL)
	{
		lIdPunto = CImmaginiPuntiSet().GetIDPunto(m_ImgListOrgani.GetAt(pos1).img.lID);
		if (lIdPunto > 0)
		{
			if (CPuntiSet().GetDatiPunto(lIdPunto, lIdOrgano, lX, lY) == TRUE)
			{
				img_organi = m_ImgListOrgani.GetAt(pos1);
				img_organi.iPunto = 0;

				bFindIndex = FALSE;
				pos2 = listPunti.GetHeadPosition();
				while(pos2 != NULL)
				{
					if (listPunti.GetAt(pos2).lIdOrgano == lIdOrgano)
					{
						if (sqrt(pow((double)(lX - listPunti.GetAt(pos2).lX), 2) + pow((double)(lY - listPunti.GetAt(pos2).lY), 2)) < RAGGIO_PUNTO)
						{
							bFindIndex = TRUE;
							break;
						}
					}

					listPunti.GetNext(pos2);
					img_organi.iPunto++;
				}

				if (bFindIndex == FALSE)
				{
					tagPunti puntoTemp;

					puntoTemp.lIdPunto = lIdPunto;
					puntoTemp.lIdOrgano = lIdOrgano;
					puntoTemp.lX = lX;
					puntoTemp.lY = lY;

					TRACE("--> Aggiunto punto Punto:%li Organo:%li X:%li Y:%li\n", puntoTemp.lIdPunto, puntoTemp.lIdOrgano, puntoTemp.lX, puntoTemp.lY);
					listPunti.AddTail(puntoTemp);

					img_organi.iPunto = listPunti.GetCount() - 1;
				}

				m_ImgListOrgani.SetAt(pos1, img_organi);
			}
		}
		m_ImgListOrgani.GetNext(pos1);
	}

	if (m_ImgListOrgani.GetCount() <= 0)
		SendMessage(WM_COMMAND, IDOK);
}

void CAssociaImmagini::SalvaPunti()
{
	int nIndex = 0;
	long lIdPunto;

	POSITION pos1 = listPunti.GetHeadPosition();
	POSITION pos2 = NULL;

	while(pos1 != NULL)
	{
		BOOL bSave = FALSE;

		pos2 = m_ImgListOrgani.GetHeadPosition();
		while(pos2 != NULL)
		{
			if (m_ImgListOrgani.GetAt(pos2).iPunto == nIndex)
			{
				bSave = TRUE;
				break;
			}

			m_ImgListOrgani.GetNext(pos2);
		}

		if (bSave)
		{
			lIdPunto = CPuntiSet().SetDatiPunto(listPunti.GetAt(pos1).lIdPunto, listPunti.GetAt(pos1).lIdOrgano, listPunti.GetAt(pos1).lX, listPunti.GetAt(pos1).lY);

			if (lIdPunto > 0)
			{
				pos2 = m_ImgListOrgani.GetHeadPosition();
				while(pos2 != NULL)
				{
					if (m_ImgListOrgani.GetAt(pos2).iPunto == nIndex)
					{
						CImmaginiPuntiSet().SetIDPunto(m_ImgListOrgani.GetAt(pos2).img.lID, lIdPunto);
						CFileBmp::NewSelected(m_ImgListOrgani.GetAt(pos2).img.lID, FALSE, m_ImgListOrgani.GetAt(pos2).img.type, CString(m_ImgListOrgani.GetAt(pos2).img.szDescription), m_lPaziente, m_lEsame, m_bConfirmed, m_strDvdLabel, m_ImgListOrgani.GetAt(pos2).img.bCI);
					}

					m_ImgListOrgani.GetNext(pos2);
				}
			}
		}

		nIndex++;
		listPunti.GetNext(pos1);
	}	
}