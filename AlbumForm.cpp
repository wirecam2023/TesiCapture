#include "stdafx.h"
#include "Endox.h"
#include "AlbumForm.h"

#include <io.h>
#include <direct.h>
#include <GdiPlus.h>
#include <psapi.h>

#include "DLL_Imaging\h\AmDbx.h"
#include "DLL_Imaging\h\AMLogin.h"
#include "DLL_Imaging\h\ImgManager.h"
#include "DLL_Imaging\h\FileReceiver.h"

#include "xrclient\xrclient.h"

#include "AcqFromDiskDermoxDlg.h"
#include "AcqFromDiskDermoxSceltaMultiplaDlg.h"
#include "AcqFromTeleDermoxDlg.h"
#include "AcquisitionWaiterDlg.h"
#include "AlbumEsameDlg.h"
#include "AssociaImmagini.h"
#include "ConfermaEliminazioneDlg.h"
#include "CustomDate.h"
#include "EndoxDynForm.h"
#include "EsamiImmaginiAudiologia.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "ExtEsamiAcquisizioneStartStopSet.h"
#include "FileBmp.h"
#include "ImmaginiPuntiSet.h"
#include "InsertLogAcquisizioneSPSet.h"
#include "LockManager.h"
#include "LogFileWriter.h"
#include "MmSystem.h"
#include "MonitoraggioSet.h"
#include "MultiPageTiffNewEdtDlg.h"
#include "DocManager.h"
#include "ObSelect.h"
#include "PazientiSet.h"
#include "PostAcquisizioneDlg.h"
#include "PuntiSet.h"
#include "SorgentiStreamingSet.h"
#include "SPInsertImgInDicomTransferQueue.h"
#include "TipoEsameSet.h"
#include "WaitImportImageDlg.h"
#include "WaitingAutoImportDlg.h"
#include "WaitingDicomDlg.h"
#include "WaitRemoteThreadDlg.h"
#include "InputBox.h"				// Marvel Carvalho (FIX) BUG 3361 - Captura continua DICOM


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAlbumForm::CAlbumForm(CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxResizableDlg(CAlbumForm::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_nNumMaxBmp = NUM_MAX_BMP;
	if (theApp.m_nApplication == PRG_CARDIOX)
		m_nNumMaxBmp = 1;

	m_pEsamiView = pEsamiView;
	m_pPazientiSet = m_pEsamiView->m_pPazientiSet;
	m_pEsamiSet = m_pEsamiView->m_pEsamiSet;

	for (int i = 0; i < NUM_MAX_BMP; i++)
		m_pFileBmp[i] = NULL;

	refreshStaticComponentTotImage();	// BUG 4197 - total imagens / qtd selecionadas / OK

	m_lCINum = 0;

	CFileBmp::DeleteListSelected(LOCAL_IMAGES);

	m_bDermoxPhotoAcq = GetPrivateProfileInt("xcap", "AcquisizioneDaFotocamera", 0, theApp.m_sFileConfig);
	m_sDermoxAcqPhotoDirectory = GetPrivateProfileString("xcap", "AcquisizioneDaFotocameraDirectory", "", theApp.m_sFileConfig);

	m_pWaitingDicomDlg = NULL;
}

CAlbumForm::~CAlbumForm()
{
	/*POSITION pos = m_ImgListOrgani.GetHeadPosition();
	while(pos != NULL)
	{
	IMG_ORGANI img_organi = m_ImgListOrgani.GetAt(pos);
	DeleteObject(img_organi.img.hBmp);
	m_ImgListOrgani.GetNext(pos);
	}*/
	m_ImgListOrgani.RemoveAll();

	for (int i = 0; i < NUM_MAX_BMP; i++)
	{
		if (m_pFileBmp[i] != NULL)
		{
			::DestroyWindow(m_pFileBmp[i]->GetSafeHwnd());
			delete m_pFileBmp[i];
			m_pFileBmp[i] = NULL;
		}
	}

	CFileBmp::DeleteListSelected(LOCAL_IMAGES);

	if (m_pWaitingDicomDlg != NULL)
	{
		m_pWaitingDicomDlg->DestroyWindow();
		delete m_pWaitingDicomDlg;
		m_pWaitingDicomDlg = NULL;
	}
	m_pEsamiView = NULL;
}


void CAlbumForm::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_CBString(pDX, IDC_STATIC_NUM1, m_ctrlStaticNum);	// BUG 4197 - total imagens / qtd selecionadas / OK
	DDX_Control(pDX, IDC_STATIC_USER, m_ctrlStaticUser);

	DDX_Control(pDX, IDC_COMMENTO_1, m_ctrlBmpEdit[0]);
	DDX_Control(pDX, IDC_COMMENTO_2, m_ctrlBmpEdit[1]);
	DDX_Control(pDX, IDC_COMMENTO_3, m_ctrlBmpEdit[2]);
	DDX_Control(pDX, IDC_COMMENTO_4, m_ctrlBmpEdit[3]);
	DDX_Control(pDX, IDC_COMMENTO_5, m_ctrlBmpEdit[4]);
	DDX_Control(pDX, IDC_COMMENTO_6, m_ctrlBmpEdit[5]);

	DDX_Control(pDX, IDC_FRAME_SMALL1, m_ctrlFrame[0]);
	DDX_Control(pDX, IDC_FRAME_SMALL2, m_ctrlFrame[1]);
	DDX_Control(pDX, IDC_FRAME_SMALL3, m_ctrlFrame[2]);
	DDX_Control(pDX, IDC_FRAME_SMALL4, m_ctrlFrame[3]);
	DDX_Control(pDX, IDC_FRAME_SMALL5, m_ctrlFrame[4]);
	DDX_Control(pDX, IDC_FRAME_SMALL6, m_ctrlFrame[5]);

	m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore);
}

IMPLEMENT_DYNCREATE(CAlbumForm, CEndoxResizableDlg)

BEGIN_MESSAGE_MAP(CAlbumForm, CEndoxResizableDlg)

	ON_BN_CLICKED(IDC_IMM_FIRST, OnPageFirst)
	ON_BN_CLICKED(IDC_IMM_PREV, OnPagePrev)
	ON_BN_CLICKED(IDC_IMM_NEXT, OnPageNext)
	ON_BN_CLICKED(IDC_IMM_LAST, OnPageLast)

	ON_BN_CLICKED(IDC_IMM_DISK, OnImmAcqFromDisk)
	ON_BN_CLICKED(IDC_IMM_SCAN, OnImmAcqFromScanner)
	ON_BN_CLICKED(IDC_IMM_ACQ, OnImmAcqFromTele)
	ON_BN_CLICKED(IDC_IMM_MULTIPAGE, OnImmMultiPage)

	ON_BN_CLICKED(IDC_IMM_ASS, OnImmAss)

	ON_BN_CLICKED(IDC_IMM_SELECT, OnImmSelectAll)
	ON_BN_CLICKED(IDC_IMM_UNSELECT, OnImmUnselectAll)
	ON_BN_CLICKED(IDC_IMM_PREVIEW, OnImmPreview)

	ON_BN_CLICKED(IDC_IMM_DEL, OnImmDelete)

	ON_BN_CLICKED(IDC_IMM_ALBUM, OnImmAlbum)

	ON_BN_CLICKED(IDC_IMM_REORDER, OnReOrderSelected)

	ON_WM_DESTROY()
	ON_WM_TIMER()

	ON_MESSAGE(MSG_UPDATE_SEL, OnUpdateSel)

	ON_MESSAGE(MSG_AFTER_ELABIMAGE, AfterElabImage)
	ON_MESSAGE(MSG_AFTER_CHANGECOMMENT, AfterChangeComment)
	ON_MESSAGE(MSG_REFRESH_IMAGES, RefreshImages)
	ON_MESSAGE(MSG_REFRESH_ALBUM, RefreshAlbumMessage) //Gabriel - BUG Refresh álbum

	ON_MESSAGE(WM_WAITINGDICOM_CLOSING, WaitingDicomClosing)
	ON_MESSAGE(WM_WAITINGDICOM_AFTERMOVEESAME, AfterMoveEsameTrue) //Gabriel BUG 7768 - Continuous capture problem
	ON_MESSAGE(WM_ACQUISITIONWAITER_CLOSING, AcquisitionWaiterClosing) //Gabriel BUG 7768 - Continuous capture problem
	ON_MESSAGE(WM_WAITINGAUTOIMPORT_CLOSING, WaitingAutoImportClosing) //Gabriel BUG 7768 - Continuous capture problem

END_MESSAGE_MAP()

BOOL CAlbumForm::OnInitDialog()
{
	CEndoxResizableDlg::OnInitDialog();

	m_wndAlbumBar.CreateEx(this, GetDlgItem(IDC_BAR_ALBUM), IDR_BAR_ALBUM_AA, IDB_BAR_ALBUM_AA, IDB_BAR_ALBUM_AA_UP, IDB_BAR_ALBUM_AA_BW);

	// Luiz 18/02/2019 - P3 - Ajuste do Form para monitores de baixa resolução
	if (GetSystemMetrics(SM_CYSCREEN) < 800)
	{
		// Marvel BUG 4131 - esconder ícones barra img p/ monitor resolução baixa
		//m_wndAlbumBar.DeleteButton(IDC_IMM_FIRST);
		//m_wndAlbumBar.DeleteButton(IDC_IMM_LAST);

		m_wndAlbumBar.DeleteButton(IDC_IMM_MULTIPAGE); // - TIFF multipagina
		m_wndAlbumBar.DeleteButton(IDC_IMM_ASS);       // - Associazione immagini - organi
	}

	AddAnchor(IDC_STATIC_FRAME, CSize(0, 0), CSize(100, 100));
	if (theApp.m_nApplication == PRG_CARDIOX)
	{
		CRect rectFrame1;
		CRect rectFrame2;
		CRect rectCommento1;
		CRect rectCommento2;

		GetDlgItem(IDC_FRAME_SMALL1)->GetWindowRect(rectFrame1); // serve per angolo sopra a sinistra //
		GetDlgItem(IDC_FRAME_SMALL6)->GetWindowRect(rectFrame2); // serve per angolo sotto a destra //
		GetDlgItem(IDC_COMMENTO_5)->GetWindowRect(rectCommento1); // serve per angolo sopra a sinistra //
		GetDlgItem(IDC_COMMENTO_6)->GetWindowRect(rectCommento2); // serve per angolo sotto a destra //

		ScreenToClient(rectFrame1);
		ScreenToClient(rectFrame2);
		ScreenToClient(rectCommento1);
		ScreenToClient(rectCommento2);

		GetDlgItem(IDC_FRAME_SMALL1)->SetWindowPos(NULL, rectFrame1.left, rectFrame1.top, rectFrame2.right - rectFrame1.left, rectFrame2.bottom - rectFrame1.top, SWP_NOOWNERZORDER);
		GetDlgItem(IDC_COMMENTO_1)->SetWindowPos(NULL, rectCommento1.left, rectCommento1.top, rectCommento2.right - rectCommento1.left, rectCommento2.bottom - rectCommento1.top, SWP_NOOWNERZORDER);

		AddAnchor(IDC_FRAME_SMALL1, CSize(0, 0), CSize(100, 100));
		AddAnchor(IDC_COMMENTO_1, CSize(0, 100), CSize(100, 100));

		GetDlgItem(IDC_FRAME_SMALL2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMMENTO_2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMMENTO_3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMMENTO_4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL5)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMMENTO_5)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL6)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMMENTO_6)->ShowWindow(SW_HIDE);
	}
	else
	{
		AddAnchor(IDC_FRAME_SMALL1, CSize(0, 1), CSize(50, 34));
		AddAnchor(IDC_COMMENTO_1, CSize(0, 34), CSize(50, 34));
		AddAnchor(IDC_FRAME_SMALL2, CSize(50, 1), CSize(100, 34));
		AddAnchor(IDC_COMMENTO_2, CSize(50, 34), CSize(100, 34));
		AddAnchor(IDC_FRAME_SMALL3, CSize(0, 34), CSize(50, 67));
		AddAnchor(IDC_COMMENTO_3, CSize(0, 67), CSize(50, 67));
		AddAnchor(IDC_FRAME_SMALL4, CSize(50, 34), CSize(100, 67));
		AddAnchor(IDC_COMMENTO_4, CSize(50, 67), CSize(100, 67));
		AddAnchor(IDC_FRAME_SMALL5, CSize(0, 67), CSize(50, 100));
		AddAnchor(IDC_COMMENTO_5, CSize(0, 100), CSize(50, 100));
		AddAnchor(IDC_FRAME_SMALL6, CSize(50, 67), CSize(100, 100));
		AddAnchor(IDC_COMMENTO_6, CSize(50, 100), CSize(100, 100));
	}

	GetDlgItem(IDC_STATIC_NUM1)->SetFont(&theApp.m_fontBold);
	GetDlgItem(IDC_STATIC_NUM2)->SetFont(&theApp.m_fontBold);

	EnableToolTips(TRUE);

	for (int i = 0; i < m_nNumMaxBmp; i++)
	{
		if (CFileBmp::CreateBmp(m_pEsamiView, this, &m_ctrlFrame[i], &m_pFileBmp[i]))
		{
			m_pFileBmp[i]->SetMouseMode(BMP_L_NORMALMODE, BMP_R_NORMALMODE);
			m_pFileBmp[i]->SetAlbumType(FALSE);
			m_pFileBmp[i]->ShowWindow(TRUE);

			m_pFileBmp[i]->AssignEdit(&m_ctrlBmpEdit[i]);
		}
	}

	AfterMoveEsame();

	theApp.LocalizeDialog(this, CAlbumForm::IDD, "AlbumForm");

	return TRUE;
}

// BUG 4197 - total imagens / qtd selecionadas / OK
void CAlbumForm::refreshStaticComponentTotImage()
{
	int iTotImg = -1;

	if (m_pFileBmp[0] != NULL) {
		iTotImg = (int)(m_pFileBmp[0])->m_iTotalImageNumber;
	}

	// Marvel Carvalho (FIX) BUG 3361 - Captura continua DICOM
	// AVOID ASSERTION ERROR IN DEBUG MODE
	if (this->m_hWnd != NULL)
	{
		SetDlgItemInt(IDC_STATIC_NUM1, (iTotImg<0 ? 0 : iTotImg));
	}
}

BOOL CAlbumForm::CreateChildForm(CWnd* pParentWnd, CRect rectFrame)
{
	BOOL result = FALSE;

	m_pParentWnd = pParentWnd;

	if (result = CEndoxResizableDlg::Create(IDD, pParentWnd))
		SetWindowPos(NULL, rectFrame.left, rectFrame.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);

	return result;
}

BOOL CAlbumForm::CreateFormEx(CWnd* pParent, CWnd* pParentFrame, CAlbumForm** pDlg, CEsamiView* pEsamiView)
{
	BOOL bResult = FALSE;
	(*pDlg) = new CAlbumForm(NULL, pEsamiView);
	if (*pDlg)
	{
		(*pDlg)->m_pParentFrame = pParentFrame;

		CRect rectFrame;
		pParentFrame->GetWindowRect(&rectFrame);
		// pParent->ScreenToClient(&rectFrame); // Sandro 17/09/2015 // forse va tolto //
		pParent->ScreenToClient(&rectFrame); // Sandro 19/10/2015 // lo sto rimettendo //
		bResult = (*pDlg)->CreateChildForm(pParent, rectFrame);
	}

	return bResult;
}

void CAlbumForm::ResetVetDiapo(BOOL bReposition)
{
	/*POSITION pos = m_ImgListOrgani.GetHeadPosition();
	while(pos != NULL)
	{
	DeleteObject(m_ImgListOrgani.GetAt(pos).img.hBmp);
	m_ImgListOrgani.GetNext(pos);
	}*/
	m_ImgListOrgani.RemoveAll();

	if (bReposition == TRUE)
	{
		m_nMaxDiapo = 0;
		m_nDiapoPage = -1;
	}
}

void CAlbumForm::MoveImage()
{
	int nBase = m_nDiapoPage * m_nNumMaxBmp;

	if (m_pEsamiSet->IsEOF())
	{
		for (int i = 0; i < m_nNumMaxBmp; i++)
			m_pFileBmp[i]->ResetImage();

		refreshStaticComponentTotImage();	// BUG 4197 - total imagens / qtd selecionadas / OK

		return;
	}

	m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);

	CString strDvdLabel;
	BOOL bConfirmed = m_pEsamiView->m_pImgManager->IsExamConfirmed(strDvdLabel);
	for (int i = 0; i < m_nNumMaxBmp; i++)
	{
		if (nBase + i <= m_nMaxDiapo)
		{
			m_pFileBmp[i]->LoadImage(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore, &m_ImgListOrgani, nBase + i, bConfirmed, strDvdLabel, CARICA_MINI);

			CFileBmp::ReselectBmp(m_pFileBmp[i], FALSE);
		}
		else
		{
			m_pFileBmp[i]->ResetImage();
		}
	}

	refreshStaticComponentTotImage();	// BUG 4197 - total imagens / qtd selecionadas / OK
}

void CAlbumForm::AfterMoveEsame(BOOL bDeleteSelectedImages, BOOL bMoveToLastPage)
{
	if (bDeleteSelectedImages)
		CFileBmp::DeleteListSelected(LOCAL_IMAGES);

	ResetVetDiapo(TRUE);

	m_nMaxDiapo = FillDiapoIndex();

	if (bMoveToLastPage)
		OnPageLast();
	else
		OnPageFirst();

	refreshStaticComponentTotImage();	// BUG 4197 - total imagens / qtd selecionadas / OK
}

LRESULT CAlbumForm::AfterElabImage(WPARAM wParam, LPARAM lParam)
{
	if ((BOOL)wParam)
		CFileBmp::DeleteListSelected(LOCAL_IMAGES);

	ResetVetDiapo(FALSE);

	m_nMaxDiapo = FillDiapoIndex();

	RequeryPage();

	return 1;
}

LRESULT CAlbumForm::AfterChangeComment(WPARAM wParam, LPARAM lParam)
{
	long lID = (long)wParam;
	CString* pString = (CString*)lParam;

	POSITION pos = m_ImgListOrgani.GetHeadPosition();
	while (pos != NULL)
	{
		if (m_ImgListOrgani.GetAt(pos).img.lID == lID)
		{
			memcpy(m_ImgListOrgani.GetAt(pos).img.szDescription, pString->GetBuffer(), pString->GetLength() + 1);
			break;
		}

		m_ImgListOrgani.GetNext(pos);
	}

	return 1;
}

LRESULT CAlbumForm::RefreshImages(WPARAM wParam, LPARAM lParam)
{
	for (int i = 0; i < NUM_MAX_BMP; i++)
		m_pFileBmp[i]->Invalidate(FALSE);

	refreshStaticComponentTotImage();	// BUG 4197 - total imagens / qtd selecionadas / OK

	return 0;
}

LRESULT CAlbumForm::WaitingDicomClosing(WPARAM wParam, LPARAM lParam)
{
	// KILL //
	DWORD dwProcesses2[1024], dwNeededProcesses2;
	if (!EnumProcesses(dwProcesses2, sizeof(dwProcesses2), &dwNeededProcesses2))
		return FALSE;

	for (UINT i = 0; i < dwNeededProcesses2 / sizeof(DWORD); i++)
	{
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE, FALSE, dwProcesses2[i]);
		if (hProcess != NULL)
		{
			DWORD dwNeededModule;
			HMODULE hModule;
			if (EnumProcessModules(hProcess, &hModule, sizeof(hModule), &dwNeededModule))
			{
				TCHAR szProcessName[MAX_PATH];
				ZeroMemory(szProcessName, sizeof(TCHAR) * MAX_PATH);
				if (GetModuleFileNameEx(hProcess, hModule, szProcessName, MAX_PATH) > 0)
				{
					CString strProcessName(szProcessName);
					strProcessName.MakeUpper();

					CString strProcessToKill(m_szProcessToKill);
					strProcessToKill.MakeUpper();

					if (strProcessToKill.Left(strProcessName.GetLength()) == strProcessName)
						TerminateProcess(hProcess, 0);
				}
			}

			CloseHandle(hProcess);
		}
	}

	// DESTROY //
	if (m_piToKill.hProcess)
	{
		::TerminateProcess(m_piToKill.hProcess, 0);
		CloseHandle(m_piToKill.hProcess);
	}
	if (m_piToKill.hThread)
		CloseHandle(m_piToKill.hThread);

	DeleteDirectory(theApp.m_sDirTempAcq + "\\DICOM");

	//
	//if (m_pWaitingDicomDlg && !m_pWaitingDicomDlg->m_bIsContinuousCaptureImporting)
	if (m_pWaitingDicomDlg && !theApp.m_bCapturaContinua /*!m_pWaitingDicomDlg->m_bIsContinuousCaptureImporting*/)
		PostAcquisizione();
	//Gabriel BUG 7768 - Continuous capture problem
	else
		DeleteAllFilesOnDirectory(theApp.m_sDirTempAcq);
	//

	return 0;
}

void CAlbumForm::RequeryPage()
{
	if (m_nDiapoPage < 0)
		m_nDiapoPage = 0;
	if (m_nDiapoPage >(m_nMaxDiapo / m_nNumMaxBmp))
		m_nDiapoPage = m_nMaxDiapo / m_nNumMaxBmp;

	MoveImage();
}

int CAlbumForm::FillDiapoIndex()
{
	// Sandro 14/12/2015 // RIMA 15135 //

	if (m_pEsamiView->m_bVisualizzaTastoCaricaImmagini)
		return 0;

	//

	m_lCINum = 0;

	if (theApp.m_nApplication == PRG_CARDIOX)
	{
		CWnd* pWindows[] = { GetDlgItem(IDC_FRAME_SMALL1),
			GetDlgItem(IDC_STATIC_NUM1),
			GetDlgItem(IDC_STATIC_NUM2),
			GetDlgItem(IDC_STATIC_DIV),
			&m_ctrlBmpEdit[0],
			m_pFileBmp[0],
			&m_wndAlbumBar };

		if ((theApp.m_dwPrivileges & AMLogin_Permissions::view_image) == FALSE)
		{
			for (int i = 0; i < sizeof(pWindows) / sizeof(CWnd*); i++)
				pWindows[i]->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_STATIC_USER)->ShowWindow(SW_SHOW);
			return 0;
		}
		else
		{
			for (int i = 0; i < sizeof(pWindows) / sizeof(CWnd*); i++)
				pWindows[i]->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_USER)->ShowWindow(SW_HIDE);
		}
	}
	else
	{
		CWnd* pWindows[] = { GetDlgItem(IDC_FRAME_SMALL1),
			GetDlgItem(IDC_FRAME_SMALL2),
			GetDlgItem(IDC_FRAME_SMALL3),
			GetDlgItem(IDC_FRAME_SMALL4),
			GetDlgItem(IDC_FRAME_SMALL5),
			GetDlgItem(IDC_FRAME_SMALL6),
			GetDlgItem(IDC_STATIC_NUM1),
			GetDlgItem(IDC_STATIC_NUM2),
			GetDlgItem(IDC_STATIC_DIV),
			&m_ctrlBmpEdit[0],
			&m_ctrlBmpEdit[1],
			&m_ctrlBmpEdit[2],
			&m_ctrlBmpEdit[3],
			&m_ctrlBmpEdit[4],
			&m_ctrlBmpEdit[5],
			m_pFileBmp[0],
			m_pFileBmp[1],
			m_pFileBmp[2],
			m_pFileBmp[3],
			m_pFileBmp[4],
			m_pFileBmp[5],
			&m_wndAlbumBar };

		if ((theApp.m_dwPrivileges & AMLogin_Permissions::view_image) == FALSE)
		{
			for (int i = 0; i < sizeof(pWindows) / sizeof(CWnd*); i++)
				pWindows[i]->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_STATIC_USER)->ShowWindow(SW_SHOW);
			return 0;
		}
		else
		{
			for (int i = 0; i < sizeof(pWindows) / sizeof(CWnd*); i++)
				pWindows[i]->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_USER)->ShowWindow(SW_HIDE);
		}
	}

	int nImages;
	CImgList listImg;

	BeginWaitCursor();
	m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);

	DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
	nImages = m_pEsamiView->m_pImgManager->GetImgList(&listImg) - 1;
	if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
		CLogFileWriter::Get()->WriteLogLine0_ImmRetrieve(timeGetTime() - timeForLog, m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore, nImages + 1, "CAlbumForm::FillDiapoIndex");

	m_ImgListOrgani = listImg;

	POSITION pos = m_ImgListOrgani.GetHeadPosition();
	while (pos != NULL)
	{
		IMG img = m_ImgListOrgani.GetAt(pos).img;

		if (img.bCI)
			m_lCINum++;

		m_ImgListOrgani.GetNext(pos);
	}

	CaricaPunti();

	EndWaitCursor();

	return nImages;
}

void CAlbumForm::OnPageFirst()
{
	if (m_nDiapoPage == 0)
		return;

	m_nDiapoPage = 0;
	MoveImage();

	UpdateData(TRUE);
}

void CAlbumForm::OnPagePrev()
{
	if (m_nDiapoPage == 0)
		return;

	m_nDiapoPage--;
	MoveImage();

	UpdateData(TRUE);
}

void CAlbumForm::OnPageNext()
{
	if (m_nDiapoPage == (m_nMaxDiapo / m_nNumMaxBmp))
		return;

	m_nDiapoPage++;
	MoveImage();

	UpdateData(TRUE);
}

void CAlbumForm::OnPageLast()
{
	if (m_nDiapoPage == (m_nMaxDiapo / m_nNumMaxBmp))
		return;

	m_nDiapoPage = m_nMaxDiapo / m_nNumMaxBmp;
	MoveImage();

	UpdateData(TRUE);
}

void CAlbumForm::OnCancel()
{
}

void CAlbumForm::OnOK()
{
}

void CAlbumForm::OnImmAcqFromTele()
{
	// BUG 10095 Felipe 19/10/2022
	//CString sConnect = theApp.m_dbEndox.GetDecryptedConnectionString();
	//AfxMessageBox(sConnect);
	
	if (m_pEsamiSet->EditRecordset("CAlbumForm::OnImmAcqFromTele"))
	{
		m_pEsamiSet->m_lCustomDataOraInizioAcq = CCustomDate(TRUE, TRUE).GetDate();

		m_pEsamiSet->UpdateRecordset("CAlbumForm::OnImmAcqFromTele");
	}
		

	if ((m_pEsamiSet->IsOpen() == FALSE) || (m_pEsamiSet->IsBOF() == TRUE) || (m_pEsamiSet->IsEOF() == TRUE))
		return;

	// Sandro 23/06/2017 //
	if ((theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury) && (!m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito.IsEmpty() && m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito != "-1"))
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAME_TRASFERITO) + " " + m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito + ".");
		return;
	}

	if (CEsamiSet().IsConiugatoSecondario(m_pEsamiSet->m_lContatore))
	{
		theApp.AfxMessageBoxEndo(IDS_FLEURY_CONIUGATO_SECONDARIO);
		return;
	}

	//if (CheckTempFolder())
	{
		// creo la stringa con la data di oggi //
		SYSTEMTIME SystemTime;
		GetLocalTime(&SystemTime);
		CString strDataOggi;
		strDataOggi.Format("%04d%02d%02d", SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay);

		// creo la stringa con la data dell'esame //
		CCustomDate ExamTime(m_pEsamiView->m_pEsamiSet->m_lData);
		CString strDataEsame = ExamTime.GetDate("%Y%m%d");

		// confronto le due date e se diverse do un alert che forse si è su un esame sbagliato //
		if (strDataOggi != strDataEsame)
			if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUM_LAUNCHACQUISITION), MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
				return;

		long lLockedExam = m_pEsamiSet->m_lContatore;
		if (CLockManager::Get()->LockExam(lLockedExam))
		{
			//simone 02/12/2015
			if (theApp.m_bVitalSignIntegrazioneAttiva)
			{
				m_pEsamiView->ChiudiMonitoraggioInCorso();

				m_pEsamiView->SendMessage(EPM_THREAD_STARTMONITORAGGIO, MonitoringPhase::intra);
			}

			// Silvano... //
			SetTimestampAcq();

			

			// Sandro 26/06/2012 //
			CSorgentiStreamingSet().SetPazienteEsame(m_pPazientiSet, m_pEsamiSet);

			//Simone - RIMA 15144
			CExtEsamiAcquisizioneStartStopSet().StartAcquisizione(m_pEsamiSet->m_lContatore);

			// lancio l'acquisizione //
			BOOL bAcquisizioneOK = FALSE;
			if (theApp.m_nApplication == PRG_DERMOX)
				bAcquisizioneOK = AcqFromTeleDermox();
			else
				bAcquisizioneOK = AcqFromTele();

			// Sandro 26/06/2012 //
			CSorgentiStreamingSet().ResetPazienteEsame();

		

			//simone 02/12/2015
			if (theApp.m_bVitalSignIntegrazioneAttiva)
				m_pEsamiView->ChiudiMonitoraggioInCorso();

			//Simone - RIMA 15144
			CExtEsamiAcquisizioneStartStopSet().StopAcquisizione(m_pEsamiSet->m_lContatore);

			m_pEsamiView->m_bImporting = FALSE;


			// Sandro 20/06/2012 // se l'acquisizione è andata a buon fine salvo su DB data e ora di inizio e fine acquisizione //
			if (bAcquisizioneOK)
			{
				Sleep(5000);

				BOOL bSalvaAncheInizioAcquisizione = FALSE;
				if (m_pEsamiSet->IsFieldNull(&m_pEsamiSet->m_lCustomDataOraInizioAcq) || (m_pEsamiSet->m_lCustomDataOraInizioAcq == 0))
					bSalvaAncheInizioAcquisizione = TRUE;

				if (m_pEsamiSet->EditRecordset("CAlbumForm::OnImmAcqFromTele"))
				{
					// se ancora nullo o invalido salvo su DB data e ora di inizio acquisizione //
					//if (bSalvaAncheInizioAcquisizione)
					//	m_pEsamiSet->m_lCustomDataOraInizioAcq = lCustomDataOraInizioAcq;

					// SEMPRE salvo su DB data e ora di fine acquisizione //
					m_pEsamiSet->m_lCustomDataOraFineAcq = CCustomDate(TRUE, TRUE).GetDate();

					//
					m_pEsamiSet->UpdateRecordset("CAlbumForm::OnImmAcqFromTele");
				}
			}

			// sblocco l'esame //
			CLockManager::Get()->UnlockExam(lLockedExam);
		}
	}
	/*else
	{
	theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_IMPORT_PREVIMAGE));
	}*/

	UpdateData(TRUE);

	// Sandro 30/12/2011 //
	if (m_pEsamiView->m_pDynForm[sub_puntipaziente] != NULL)
		m_pEsamiView->m_pDynForm[sub_puntipaziente]->SendMessage(MSG_FORM_LOAD); // OnFormLoad //	
}

// Marvel Carvalho - Bug 5512 Duplicação imagens ultrassom
BOOL CAlbumForm::ExternalExeToolsExists()
{
	BOOL bExistStorescpExe = FALSE;
	BOOL bExistMoveFileExe = FALSE;

	CString sExeStoreScp;
	sExeStoreScp.Format("%s\\storescp.exe", theApp.m_sDirProg);
	sExeStoreScp.Trim();
	if (_access(sExeStoreScp, 00) == 00)	// _access(file,attr) >> 00=Existência apenas | 02=Somente gravação | 04=Somente leitura | 06=Leitura e gravação
	{
		bExistStorescpExe = TRUE;
	}
	else
	{
		CString sErrorMessage;
		sErrorMessage.Format(IDS_ERROR_FILE_NOT_FOUND, sExeStoreScp);
		theApp.AfxMessageBoxEndo(sErrorMessage);
	}

	CString sExeTemp;
	sExeTemp.Format("%s\\%s", theApp.m_sDirProg, theApp.m_sStoreScpExecOnReceptionExe);
	sExeTemp.Trim();
	if (_access(sExeTemp, 00) == 00)	// _access(file,attr) >> 00=Existência apenas | 02=Somente gravação | 04=Somente leitura | 06=Leitura e gravação
	{
		bExistMoveFileExe = TRUE;
	}
	else
	{
		CString sErrorMessage;
		sErrorMessage.Format(IDS_ERROR_FILE_NOT_FOUND, sExeTemp);
		theApp.AfxMessageBoxEndo(sErrorMessage);
	}

	return bExistStorescpExe && bExistMoveFileExe;
}

BOOL CAlbumForm::AcqFromTele()
{
	BOOL bVaiColPostAcquisizione = TRUE;


#ifdef _DEBUG
	// Marvel Carvalho (FIX) BUG 3361 - Captura continua DICOM
	// DEBUG MARVEL

	// importo solo i files dell'esame corrente //
	CString strWildcard;
	strWildcard.Format("%s\\%08d_%08d_*.*",
		theApp.m_sDirTempAcq,
		m_pEsamiView->m_pEsamiSet->m_lPaziente,
		m_pEsamiView->m_pEsamiSet->m_lContatore);


	CInputBox theInputBox(this);
	CString strUserInput;

	theInputBox.Show("DEBUG\nQUAL CASO DESEJA TESTAR ?\n\
					 A) Licença:'Stazione di acquisizione'\n\
					 B) Licença:'SOLO acquisizione Dicom' com captura convencional\n\
					 C) Licença:'SOLO acquisizione Dicom' com CAPTURA CONTÍNUA\n\
					 D) Licença:'SOLO acquisizione automatica da disco'\n----\n\
					 digite A, B, C ou D:", strUserInput);
	strUserInput = strUserInput.MakeUpper().Trim();
	MessageBox(strWildcard);
	MessageBox(strUserInput);

	if (strUserInput == "A")
	{
		// CASO A
		theApp.m_bCanAcquire = 1;
		theApp.m_bSoloDicom = 0;
		theApp.m_bCapturaContinua = 0;
		theApp.m_bSoloAutoImport = 0;
		theApp.AfxMessageBoxEndo("TESTANDO CASO A | m_bCanAcquire=1 >> Licença:'Stazione di acquisizione'");
	}

	if (strUserInput == "B")
	{
		// CASO B
		theApp.m_bCanAcquire = 0;
		theApp.m_bSoloDicom = 1;
		theApp.m_bCapturaContinua = 0;
		theApp.m_bSoloAutoImport = 0;
		theApp.AfxMessageBoxEndo("TESTANDO CASO B | m_bSoloDicom=1 >> Licença:'SOLO acquisizione Dicom' com captura convencional");
	}

	if (strUserInput == "C")
	{
		// CASO C
		theApp.m_bCanAcquire = 0;
		theApp.m_bSoloDicom = 1;
		theApp.m_bCapturaContinua = 1;
		theApp.m_bSoloAutoImport = 0;
		theApp.AfxMessageBoxEndo("TESTANDO CASO C | m_bSoloDicom=1 >> Licença:'SOLO acquisizione Dicom' com CAPTURA CONTÍNUA");
	}

	if (strUserInput == "D")
	{
		// CASO D
		theApp.m_bCanAcquire = 0;
		theApp.m_bSoloDicom = 0;
		theApp.m_bCapturaContinua = 0;
		theApp.m_bSoloAutoImport = 1;
		theApp.AfxMessageBoxEndo("TESTANDO CASO D | m_bSoloAutoImport=1 >> Licença:'SOLO acquisizione automatica da disco'\n\
								 Configure o EndoxPro.cfg\n\
								 'Settings':'ACQ - Percorso copia immagini remote'apontar para a pasta da captura,\n\
								 exemplo: ACQ - Percorso copia immagini remote = C:\\Endox\\TEMP");
	}
#endif

	if (!theApp.m_bCanAcquire && !theApp.m_bSoloAutoImport && !theApp.m_bSoloDicom)
		return FALSE;

	if (theApp.m_sDirTempAcq.IsEmpty())
		theApp.m_sDirTempAcq = theApp.m_sDirTemp;

	if (!VerificaPercorso(theApp.m_sDirTempAcq))
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUM_FORM_ERR_PATH) + theApp.m_sDirTempAcq);
		return FALSE;
	}

	VerificaPercorso(theApp.m_sDirTempAcq + "\\DICOM");


	if (theApp.m_bDemoAliar) // Sandro 22/04/2016 // RIMA 16057 // (something specific for this customer DemoAliar)
	{
#ifdef _ALIAR
		////////////////////////////////////////////////////
		// lancio timer che controlla percorso temporaneo //
		////////////////////////////////////////////////////

		SetTimer(0xAAA, 1000, NULL);

		/////////////////////////////////////////////////////////////////
		// lancio eseguibile che fa i print screen e rimango in attesa //
		/////////////////////////////////////////////////////////////////

		CString sParameter = theApp.m_sDirTempAcq;
		if (sParameter.Right(1) != "\\")
			sParameter += "\\";
		sParameter.AppendFormat("%08d_%08d_", m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);

		char szProcess[4000];
		sprintf_s(szProcess, "%s\\PrintScreenGrabber.exe \"%s\"", theApp.m_sDirProg, sParameter);

		// KILL //
		DWORD dwProcesses1[1024], dwNeededProcesses1;
		if (!EnumProcesses(dwProcesses1, sizeof(dwProcesses1), &dwNeededProcesses1))
			return FALSE;

		for (UINT i = 0; i < dwNeededProcesses1 / sizeof(DWORD); i++)
		{
			HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE, FALSE, dwProcesses1[i]);
			if (hProcess != NULL)
			{
				DWORD dwNeededModule;
				HMODULE hModule;
				if (EnumProcessModules(hProcess, &hModule, sizeof(hModule), &dwNeededModule))
				{
					TCHAR szProcessName[MAX_PATH];
					ZeroMemory(szProcessName, sizeof(TCHAR) * MAX_PATH);
					if (GetModuleFileNameEx(hProcess, hModule, szProcessName, MAX_PATH) > 0)
					{
						CString strProcessName(szProcessName);
						strProcessName.MakeUpper();

						CString strProcessToKill(szProcess);
						strProcessToKill.MakeUpper();

						if (strProcessToKill.Left(strProcessName.GetLength()) == strProcessName)
							TerminateProcess(hProcess, 0);
					}
				}

				CloseHandle(hProcess);
			}
		}

		// START // 
		STARTUPINFO m_si;
		PROCESS_INFORMATION m_pi;
		ZeroMemory(&m_si, sizeof(m_si));
		ZeroMemory(&m_pi, sizeof(m_pi));
		m_si.cb = sizeof(m_si);

		if (!CreateProcess(NULL,	  // No module name (use command line). 
			(LPTSTR)szProcess,        // Command line. 
			NULL,			          // Process handle not inheritable. 
			NULL,			          // Thread handle not inheritable. 
			FALSE,		              // Set handle inheritance to FALSE. 
			CREATE_NO_WINDOW,         // No creation flags. 
			NULL,			          // Use parent's environment block. 
			NULL,			          // Use parent's starting directory. 
			&m_si,			          // Pointer to STARTUPINFO structure.
			&m_pi))			          // Pointer to PROCESS_INFORMATION structure.
		{
			ZeroMemory(&m_si, sizeof(m_si));
			ZeroMemory(&m_pi, sizeof(m_pi));

			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_LOADING_PRINTSCREENCAPTURE));
		}
		else
		{
			CWaitingDicomDlg dlgWait(this, m_pEsamiView);
			dlgWait.DoModal();
		}

		// KILL //
		DWORD dwProcesses2[1024], dwNeededProcesses2;
		if (!EnumProcesses(dwProcesses2, sizeof(dwProcesses2), &dwNeededProcesses2))
			return FALSE;

		for (UINT i = 0; i < dwNeededProcesses2 / sizeof(DWORD); i++)
		{
			HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE, FALSE, dwProcesses2[i]);
			if (hProcess != NULL)
			{
				DWORD dwNeededModule;
				HMODULE hModule;
				if (EnumProcessModules(hProcess, &hModule, sizeof(hModule), &dwNeededModule))
				{
					TCHAR szProcessName[MAX_PATH];
					ZeroMemory(szProcessName, sizeof(TCHAR) * MAX_PATH);
					if (GetModuleFileNameEx(hProcess, hModule, szProcessName, MAX_PATH) > 0)
					{
						CString strProcessName(szProcessName);
						strProcessName.MakeUpper();

						CString strProcessToKill(szProcess);
						strProcessToKill.MakeUpper();

						if (strProcessToKill.Left(strProcessName.GetLength()) == strProcessName)
							TerminateProcess(hProcess, 0);
					}
				}

				CloseHandle(hProcess);
			}
		}

		// DESTROY //
		if (m_pi.hProcess)
		{
			::TerminateProcess(m_pi.hProcess, 0);
			CloseHandle(m_pi.hProcess);
		}
		if (m_pi.hThread)
			CloseHandle(m_pi.hThread);

		/////////////////////
		// uccido il timer //
		/////////////////////

		KillTimer(0xAAA);
#endif
	}
	else if (theApp.m_bSoloAutoImport)	// SOLO acquisizione import immagini automatico (no telecamera xCap) //
	{
		// Marvel Carvalho (FIX) BUG 3361 - Captura continua DICOM
		/*if (theApp.m_bCapturaContinua)
		theApp.AfxMessageBoxEndo("A captura contínua Dicom é incompatível com a licença atual.\nNecessária a licença: 'Attivazioni Endox' = 'SOLO acquisizione Dicom'\nSerá usada a captura convencional na sequência...", MB_ICONEXCLAMATION);*/

		CWaitingAutoImportDlg dlgWait(this, this);
		dlgWait.DoModal();
	}
	else if (theApp.m_bSoloDicom)	// SOLO acquisizione Dicom (no telecamera xCap) //
	{
		theApp.m_sStoreScpExecOnReceptionExe.Trim();
		theApp.m_sStoreScpExecOnReceptionParameters.Trim();

		if (!theApp.m_sStoreScpExecOnReceptionExe.IsEmpty())
		{
			CString sExeTemp = theApp.m_sDirProg + "\\" + theApp.m_sStoreScpExecOnReceptionExe;
			sExeTemp.Trim();
			//if (_access(sExeTemp, 00) == 00)	// _access(file,attr) >> 00=Existência apenas | 02=Somente gravação | 04=Somente leitura | 06=Leitura e gravação
			if (ExternalExeToolsExists())
			{
				SYSTEMTIME timeLocal;
				::GetLocalTime(&timeLocal);

				if (!theApp.m_sStoreScpExecOnReceptionParameters.IsEmpty())
					sExeTemp += " " + theApp.m_sStoreScpExecOnReceptionParameters;

				DeleteAllFilesOnDirectory(theApp.m_sDirTempAcq); //Gabriel BUG 7768 - Continuous capture problem

				//Gabriel BUG 7768 - Continuous capture problem
				if (theApp.m_bUsaNovaCapturaContinua)
				{
					CString sPath = theApp.m_sDirTempAcq;
					if (sPath.Right(1) != "\\")
						sPath += "\\";
					sPath.AppendFormat("%08d_%08d", m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);
					VerificaPercorso(sPath);
				}

				// char szProcess[4000];
				sprintf_s(m_szProcessToKill,
					!theApp.m_bUsaNovaCapturaContinua ?
					"%s\\storescp.exe -od %s\\DICOM -xf %s\\storescp.cfg default %s --timenames --exec-on-reception \"%s %s\\DICOM\\#f %s\\%08li_%08li_#f.dcm\"" :
					"%s\\storescp.exe -od %s\\DICOM -xf %s\\storescp.cfg default %s --timenames --exec-on-reception \"%s %s\\DICOM\\#f %s\\%08li_%08li\\#f.dcm\"",
					theApp.m_sDirProg,
					theApp.m_sDirTempAcq,
					theApp.m_sDirProg,
					theApp.m_sStoreScpPorta,
					sExeTemp,
					theApp.m_sDirTempAcq,
					theApp.m_sDirTempAcq,
					m_pPazientiSet->m_lContatore,
					m_pEsamiSet->m_lContatore);

				// KILL //
				DWORD dwProcesses1[1024], dwNeededProcesses1;
				if (!EnumProcesses(dwProcesses1, sizeof(dwProcesses1), &dwNeededProcesses1))
					return FALSE;

				for (UINT i = 0; i < dwNeededProcesses1 / sizeof(DWORD); i++)
				{
					HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE, FALSE, dwProcesses1[i]);
					if (hProcess != NULL)
					{
						DWORD dwNeededModule;
						HMODULE hModule;
						if (EnumProcessModules(hProcess, &hModule, sizeof(hModule), &dwNeededModule))
						{
							TCHAR szProcessName[MAX_PATH];
							ZeroMemory(szProcessName, sizeof(TCHAR) * MAX_PATH);
							if (GetModuleFileNameEx(hProcess, hModule, szProcessName, MAX_PATH) > 0)
							{
								CString strProcessName(szProcessName);
								strProcessName.MakeUpper();

								CString strProcessToKill(m_szProcessToKill);
								strProcessToKill.MakeUpper();

								if (strProcessToKill.Left(strProcessName.GetLength()) == strProcessName)
									TerminateProcess(hProcess, 0);
							}
						}

						CloseHandle(hProcess);
					}
				}

				// START // 
				STARTUPINFO m_si;
				// PROCESS_INFORMATION m_pi;
				ZeroMemory(&m_si, sizeof(m_si));
				ZeroMemory(&m_piToKill, sizeof(m_piToKill));
				m_si.cb = sizeof(m_si);

				if (!CreateProcess(NULL,	   // No module name (use command line). 
					(LPTSTR)m_szProcessToKill, // Command line. 
					NULL,			           // Process handle not inheritable. 
					NULL,			           // Thread handle not inheritable. 
					FALSE,		               // Set handle inheritance to FALSE. 
					CREATE_NO_WINDOW,          // No creation flags. 
					NULL,			           // Use parent's environment block. 
					NULL,			           // Use parent's starting directory. 
					&m_si,			           // Pointer to STARTUPINFO structure.
					&m_piToKill))	           // Pointer to PROCESS_INFORMATION structure.
				{
					ZeroMemory(&m_si, sizeof(m_si));
					ZeroMemory(&m_piToKill, sizeof(m_piToKill));

					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_LOADING_DICOM));
				}
				else
				{
					//Julio (FIX) BUG 3361 - Captura continua DICOM
					//Gabriel BUG 7768 - Continuous capture problem
					if (theApp.m_bCapturaContinua && theApp.m_bUsaNovaCapturaContinua)
					{
						/*CWaitingAutoImportDlg dlgWait(this, this, TRUE);
						dlgWait.DoModal();*/

						m_pWaitingDicomDlg = new CWaitingDicomDlg(this, m_pEsamiView, TRUE);
						m_pWaitingDicomDlg->CreateModelessDialog(this);
						m_pWaitingDicomDlg->CenterWindow();
						m_pWaitingDicomDlg->ShowWindow(SW_SHOW);

					}
					/*else if (theApp.m_bCapturaContinua && !theApp.m_bUsaNovaCapturaContinua)
					{
					m_pWaitingDicomDlg = new CWaitingDicomDlg(this, m_pEsamiView, TRUE);
					m_pWaitingDicomDlg->CreateModelessDialog(this);
					m_pWaitingDicomDlg->CenterWindow();
					m_pWaitingDicomDlg->ShowWindow(SW_SHOW);
					}*/
					else
					{
						m_pWaitingDicomDlg = new CWaitingDicomDlg(this, m_pEsamiView);
						m_pWaitingDicomDlg->CreateModelessDialog(this);
						m_pWaitingDicomDlg->CenterWindow();
						m_pWaitingDicomDlg->ShowWindow(SW_SHOW);
					}

					//if (!theApp.m_bContingencia)  //Julio BUG 3361 - Captura continua DICOM
					//SetTimer(0xAAB, 10000, NULL);
				}

				// Sandro 18/08/2016 // prima CWaitingDicomDlg era modale, adesso che non lo è più sposto l'import delle immagini dentro alla funzione WaitingDicomClosing //
				bVaiColPostAcquisizione = FALSE;
			}
			//else
			//{
			//	CString sErrorMessage;
			//	sErrorMessage.Format(IDS_ERROR_FILE_NOT_FOUND, sExeTemp);
			//	theApp.AfxMessageBoxEndo(sErrorMessage);
			//}
		}
		else
		{
			theApp.AfxMessageBoxEndo(IDS_STORESCPEXECONRECEPTIONEXE_NOTDEFINED);
		}
	}
	else  // telecamera xCap //
	{
		// Marvel Carvalho (FIX) BUG 3361 - Captura continua DICOM
		if (theApp.m_bCapturaContinua)
			theApp.AfxMessageBoxEndo("A captura contínua Dicom é incompatível com a licença atual.\nNecessária a licença: 'Attivazioni Endox' = 'SOLO acquisizione Dicom'\nSerá usada a captura convencional na sequência...", MB_ICONEXCLAMATION);

		char szBuffer[512];

		sprintf_s(szBuffer, " - xCap - %s %s - ", m_pEsamiView->m_pPazientiSet->m_sCognome, m_pEsamiView->m_pPazientiSet->m_sNome);
		WritePrivateProfileString("xcap", "Title", szBuffer, theApp.m_sFileConfig);

		sprintf_s(szBuffer, "%s", theApp.m_sDirTempAcq);
		WritePrivateProfileString("xcap", "Path", szBuffer, theApp.m_sFileConfig);

		sprintf_s(szBuffer, "%08d_%08d_", m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);
		WritePrivateProfileString("xcap", "imageprefix", szBuffer, theApp.m_sFileConfig);

		sprintf_s(szBuffer, "%s", theApp.m_sFileCalib);
		WritePrivateProfileString("xcap", "CalibFile", szBuffer, theApp.m_sFileConfig);

		WritePrivateProfileInt("xcap", "Language", theApp.m_nLanguage, theApp.m_sFileConfig);

		// Sandro 01/07/2014 //

		if (theApp.m_nApplication == PRG_ENDOX)
			WritePrivateProfileString("xcap", "UsaTempoRetrazione", "1", theApp.m_sFileConfig);
		else
			WritePrivateProfileString("xcap", "UsaTempoRetrazione", "0", theApp.m_sFileConfig);

		sprintf_s(szBuffer, "%li", m_pEsamiSet->m_lTempoRetrazione);
		WritePrivateProfileString("xcap", "TempoRetrazione", szBuffer, theApp.m_sFileConfig);

		// Sandro 05/07/2012 //
		CInsertLogAcquisizioneSPSet().Exec(m_pPazientiSet->m_lContatore, m_pEsamiSet->m_lContatore, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.GetMessageString(IDS_ACQUISIZIONE_INIZIO));

		//Julio BUG 3361 - Captura continua	 DICOM
		//Nao funciona com o xcap porque ele nao permite deletar a imagem capturada ate que o aplicativo esteja fechado.
		//if (!theApp.m_bContingencia)				
		//SetTimer(0xAAB, 1000, NULL);

		// Sandro 03/05/2012 //
		theApp.m_bReopenAcquisition = FALSE; // verrà messa a TRUE in OnXcapMsgNuovoMonitoraggio o in OnXcapMsgNuovaProvetta o in OnXcapMsgNuovaSonda //
		CAcquisitionWaiterDlg(this).DoModal();

		// Sandro 05/07/2012 //
		CInsertLogAcquisizioneSPSet().Exec(m_pPazientiSet->m_lContatore, m_pEsamiSet->m_lContatore, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.GetMessageString(IDS_ACQUISIZIONE_FINE));

		// --- //

		if (theApp.m_bReopenAcquisition)
			return AcqFromTele();

		//Julio BUG 3361 - Captura continua DICOM
		//Nao funciona com o xcap porque ele nao permite deletar a imagem capturada ate que o aplicativo esteja fechado.
		//if (!theApp.m_bContingencia) 
		//KillTimer(0xAAB); 
		//
	}

	if (m_pEsamiView != NULL)
	{
		// FIX - o ajuste da captura contínua fez regredir a captura não contínua
		// if ((bVaiColPostAcquisizione) || (m_pWaitingDicomDlg && !m_pWaitingDicomDlg->isFilesAlreadyCaptured()))
		PostAcquisizione();  // AJUSTE: FAZ SEMPRE O REFRESH DO ALBUM, SE TIVER TIVER IMAGEM NA PASTA ENDOX\TEMP IMPORTA E ATUALIZA O ALBUM, SE PASTA ESTIVER VAZIA NAO FAZ NADA
	}

	if (m_pEsamiView != NULL && m_pEsamiView->m_bImporting)
		m_pEsamiView->m_bImporting = FALSE;

	return TRUE;
}

BOOL CAlbumForm::AcqFromTeleDermox()
{
	if (theApp.m_bSoloDicom)
	{
		VerificaPercorso(theApp.m_sDirTempAcq + "\\DICOM");

		theApp.m_sStoreScpExecOnReceptionExe.Trim();
		theApp.m_sStoreScpExecOnReceptionParameters.Trim();

		if (!theApp.m_sStoreScpExecOnReceptionExe.IsEmpty())
		{
			//CString sExeStoreScp;
			//sExeStoreScp.Format("%s\\storescp.exe", theApp.m_sDirProg);
			//sExeStoreScp.Trim();
			//if (_access(sExeStoreScp, 00) == 00)	// _access(file,attr) >> 00=Existência apenas | 02=Somente gravação | 04=Somente leitura | 06=Leitura e gravação
			//{
			CString sExeTemp;
			sExeTemp.Format("%s\\%s", theApp.m_sDirProg, theApp.m_sStoreScpExecOnReceptionExe);
			sExeTemp.Trim();
			//if (_access(sExeTemp, 00) == 00)	// _access(file,attr) >> 00=Existência apenas | 02=Somente gravação | 04=Somente leitura | 06=Leitura e gravação
			if (ExternalExeToolsExists())
			{
				SYSTEMTIME timeLocal;
				::GetLocalTime(&timeLocal);

				if (!theApp.m_sStoreScpExecOnReceptionParameters.IsEmpty())
					sExeTemp += " " + theApp.m_sStoreScpExecOnReceptionParameters;

				char szProcess[4000];
				sprintf_s(szProcess,
					"%s\\storescp.exe -od %s\\DICOM -xf %s\\storescp.cfg default %s --timenames --exec-on-reception \"%s %s\\DICOM\\#f %s\\%08li_%08li_#f.bmp\"",
					theApp.m_sDirProg,
					theApp.m_sDirTempAcq,
					theApp.m_sDirProg,
					theApp.m_sStoreScpPorta,
					sExeTemp,
					theApp.m_sDirTempAcq,
					theApp.m_sDirTempAcq,
					m_pPazientiSet->m_lContatore,
					m_pEsamiSet->m_lContatore);

				// KILL //
				DWORD dwProcesses1[1024], dwNeededProcesses1;
				if (!EnumProcesses(dwProcesses1, sizeof(dwProcesses1), &dwNeededProcesses1))
					return FALSE;

				for (UINT i = 0; i < dwNeededProcesses1 / sizeof(DWORD); i++)
				{
					HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE, FALSE, dwProcesses1[i]);
					if (hProcess != NULL)
					{
						DWORD dwNeededModule;
						HMODULE hModule;
						if (EnumProcessModules(hProcess, &hModule, sizeof(hModule), &dwNeededModule))
						{
							TCHAR szProcessName[MAX_PATH];
							ZeroMemory(szProcessName, sizeof(TCHAR) * MAX_PATH);
							if (GetModuleFileNameEx(hProcess, hModule, szProcessName, MAX_PATH) > 0)
							{
								CString strProcessName(szProcessName);
								strProcessName.MakeUpper();

								CString strProcessToKill(szProcess);
								strProcessToKill.MakeUpper();

								if (strProcessToKill.Left(strProcessName.GetLength()) == strProcessName)
									TerminateProcess(hProcess, 0);
							}
						}

						CloseHandle(hProcess);
					}
				}

				// START // 
				STARTUPINFO m_si;
				PROCESS_INFORMATION m_pi;
				ZeroMemory(&m_si, sizeof(m_si));
				ZeroMemory(&m_pi, sizeof(m_pi));
				m_si.cb = sizeof(m_si);

				if (!CreateProcess(NULL,      // No module name (use command line). 
					(LPTSTR)szProcess,        // Command line. 
					NULL,			          // Process handle not inheritable. 
					NULL,			          // Thread handle not inheritable. 
					FALSE,		              // Set handle inheritance to FALSE. 
					CREATE_NO_WINDOW,         // No creation flags. 
					NULL,			          // Use parent's environment block. 
					NULL,			          // Use parent's starting directory. 
					&m_si,			          // Pointer to STARTUPINFO structure.
					&m_pi))			          // Pointer to PROCESS_INFORMATION structure.
				{
					ZeroMemory(&m_si, sizeof(m_si));
					ZeroMemory(&m_pi, sizeof(m_pi));

					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_LOADING_DICOM));
				}
				else
				{
					CWaitingDicomDlg dlgWait(this, m_pEsamiView);
					dlgWait.DoModal();
				}

				// KILL //
				DWORD dwProcesses2[1024], dwNeededProcesses2;
				if (!EnumProcesses(dwProcesses2, sizeof(dwProcesses2), &dwNeededProcesses2))
					return FALSE;

				for (UINT i = 0; i < dwNeededProcesses2 / sizeof(DWORD); i++)
				{
					HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE, FALSE, dwProcesses2[i]);
					if (hProcess != NULL)
					{
						DWORD dwNeededModule;
						HMODULE hModule;
						if (EnumProcessModules(hProcess, &hModule, sizeof(hModule), &dwNeededModule))
						{
							TCHAR szProcessName[MAX_PATH];
							ZeroMemory(szProcessName, sizeof(TCHAR) * MAX_PATH);
							if (GetModuleFileNameEx(hProcess, hModule, szProcessName, MAX_PATH) > 0)
							{
								CString strProcessName(szProcessName);
								strProcessName.MakeUpper();

								CString strProcessToKill(szProcess);
								strProcessToKill.MakeUpper();

								if (strProcessToKill.Left(strProcessName.GetLength()) == strProcessName)
									TerminateProcess(hProcess, 0);
							}
						}

						CloseHandle(hProcess);
					}
				}

				// DESTROY //
				if (m_pi.hProcess)
				{
					::TerminateProcess(m_pi.hProcess, 0);
					CloseHandle(m_pi.hProcess);
				}
				if (m_pi.hThread)
					CloseHandle(m_pi.hThread);
			}
			//else
			//{
			//	CString sErrorMessage;
			//	sErrorMessage.Format(IDS_ERROR_FILE_NOT_FOUND, sExeTemp);
			//	theApp.AfxMessageBoxEndo(sErrorMessage);
			//}
			//}
			//else
			//{
			//	CString sErrorMessage;
			//	sErrorMessage.Format(IDS_ERROR_FILE_NOT_FOUND, sExeStoreScp);
			//	theApp.AfxMessageBoxEndo(sErrorMessage);
			//}
		}
		else
		{
			theApp.AfxMessageBoxEndo(IDS_STORESCPEXECONRECEPTIONEXE_NOTDEFINED);
		}

		//

		CStringList ArraySelected;

		// conto solo i files dell'esame corrente //
		CString strWildcard;
		strWildcard.Format("%s\\%08d_%08d_*.*", theApp.m_sDirTempAcq, m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore);

		//
		WIN32_FIND_DATA dataFile;
		HANDLE hFile = FindFirstFile(strWildcard, &dataFile);
		if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
		{
			do
			{
				CString strFile(dataFile.cFileName);
				if (strFile.GetLength() > 3)
				{
					CString strExt = strFile.Right(3);
					if ((strExt.CompareNoCase("bmp") == 0) || (strExt.CompareNoCase("mpg") == 0) || (strExt.CompareNoCase("avi") == 0) || (strExt.CompareNoCase("mp4") == 0) || (strExt.CompareNoCase("dcm") == 0))
						ArraySelected.AddTail(theApp.m_sDirTempAcq + "\\" + strFile);
				}
			} while (FindNextFile(hFile, &dataFile));
		}
		FindClose(hFile);

		if (ArraySelected.GetCount() > 0)
		{
			BeginWaitCursor();
			m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);

			BOOL export2Pacs = FALSE;
			if (theApp.m_lDcmStoreMode == 2)
				export2Pacs = TRUE;

			POSITION pos = ArraySelected.GetHeadPosition();
			while (pos != NULL)
			{
				CAcqFromDiskDermoxDlg dlg(this, m_pEsamiView, ArraySelected.GetAt(pos), TRUE);
				dlg.DoModal();
				ArraySelected.GetNext(pos);
			}
			EndWaitCursor();

			ArraySelected.RemoveAll();

			AfterMoveEsame();

			SetTimestampAcq();
		}

		UpdateData(TRUE);

		// Sandro 30/12/2011 //
		if (m_pEsamiView->m_pDynForm[sub_puntipaziente] != NULL)
			m_pEsamiView->m_pDynForm[sub_puntipaziente]->SendMessage(MSG_FORM_LOAD); // OnFormLoad //

		DeleteDirectory(theApp.m_sDirTempAcq + "\\DICOM");
	}
	else
	{
		if (m_bDermoxPhotoAcq)
		{
			//1. Far partire il processo che cerca i file nella cartella indicata e, quando la trova, legge tutti i file e li manda alla finestra in ascolto che parte al punto 2
			//		Ovviamente questo processo non deve essere bloccante
			STARTUPINFO si;
			PROCESS_INFORMATION pi;

			ZeroMemory(&si, sizeof(si));
			si.cb = sizeof(si);
			ZeroMemory(&pi, sizeof(pi));

			TCHAR szProcess[255];
			sprintf_s(szProcess, "%s\\CameraAdapter\\CameraAdapter.exe \"%s \"", theApp.m_sDirProg, m_sDermoxAcqPhotoDirectory);

			//Il processo ha uno sleep di 2 secondi per permettere alla finestra di acquisizione di aprirsi.
			// In caso di problemi in futuro, tenere conto di questo
			if (CreateProcess(NULL, szProcess, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
			{
				//2. Mettersi in attesa
				AcqFromWindowMessage();

				//3. Killare il processo
				TerminateProcess(pi.hProcess, 0);
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
			}

		}
		else
		{
			if (!theApp.m_bDermoxAcquisizioneDiretta)
			{
				//
				if (!theApp.m_bCanAcquire)
					return FALSE;

				//
				if (theApp.m_sDirTempAcq.IsEmpty())
					theApp.m_sDirTempAcq = theApp.m_sDirTemp;

				//
				if (!VerificaPercorso(theApp.m_sDirTempAcq))
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUM_FORM_ERR_PATH) + theApp.m_sDirTempAcq);
					return FALSE;
				}

				//
				CAcqFromTeleDermoxDlg dlg(this, m_pEsamiView);
				dlg.DoModal();

				//
				if (m_pEsamiView)
					AfterMoveEsame();
			}
			else
			{
				//
				if (!theApp.m_bCanAcquire)
					return FALSE;

				//
				if (theApp.m_sDirTempAcq.IsEmpty())
					theApp.m_sDirTempAcq = theApp.m_sDirTemp;

				//
				if (!VerificaPercorso(theApp.m_sDirTempAcq))
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUM_FORM_ERR_PATH) + theApp.m_sDirTempAcq);
					return FALSE;
				}

				// 
				CStringList ArraySelected;

				//
				WIN32_FIND_DATA dataFile;
				HANDLE hFile = FindFirstFile(theApp.m_sDirTempAcq + "\\*.jpg", &dataFile);
				if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
				{
					do
					{
						// li inserisco in lista in ordine alfabetico //

						CString strFile = theApp.m_sDirTempAcq + "\\" + CString(dataFile.cFileName);

						BOOL bContinue = TRUE;
						int nIndex = 0;
						int nMaxIndex = ArraySelected.GetSize();

						while ((bContinue) && (nIndex < nMaxIndex))
						{
							POSITION pos = ArraySelected.FindIndex(nIndex);
							CString strIndex = ArraySelected.GetAt(pos);

							if (strIndex > strFile)
							{
								bContinue = FALSE;
								ArraySelected.InsertAfter(pos, strFile);
							}

							nIndex++;
						}

						if (bContinue)
							ArraySelected.AddTail(strFile);

					} while (FindNextFile(hFile, &dataFile));
				}
				FindClose(hFile);

				//
				if (ArraySelected.GetCount() > 0)
				{
					BeginWaitCursor();
					m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);

					POSITION pos = ArraySelected.GetHeadPosition();
					while (pos != NULL)
					{
						CAcqFromDiskDermoxDlg dlg(this, m_pEsamiView, ArraySelected.GetAt(pos), TRUE);
						dlg.DoModal();
						ArraySelected.GetNext(pos);
					}
					EndWaitCursor();

					ArraySelected.RemoveAll();

					AfterMoveEsame();

					SetTimestampAcq();
				}

				//
				UpdateData(TRUE);

				// Sandro 30/12/2011 //
				if (m_pEsamiView->m_pDynForm[sub_puntipaziente] != NULL)
					m_pEsamiView->m_pDynForm[sub_puntipaziente]->SendMessage(MSG_FORM_LOAD); // OnFormLoad //
			}
		}
	}

	return TRUE;
}

void CAlbumForm::OnImmAcqFromScanner()
{
	if ((m_pEsamiSet->IsOpen() == FALSE) || (m_pEsamiSet->IsBOF() == TRUE) || (m_pEsamiSet->IsEOF() == TRUE))
		return;

	// Sandro 23/06/2017 //
	if ((theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury) && (!m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito.IsEmpty() && m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito != "-1"))
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAME_TRASFERITO) + " " + m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito + ".");
		return;
	}

	if (CEsamiSet().IsConiugatoSecondario(m_pEsamiSet->m_lContatore))
	{
		theApp.AfxMessageBoxEndo(IDS_FLEURY_CONIUGATO_SECONDARIO);
		return;
	}

	if (CheckTempFolder())
	{
		// creo la stringa con la data di oggi //
		SYSTEMTIME SystemTime;
		GetLocalTime(&SystemTime);
		CString strDataOggi;
		strDataOggi.Format("%04d%02d%02d", SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay);

		// creo la stringa con la data dell'esame //
		CCustomDate ExamTime(m_pEsamiView->m_pEsamiSet->m_lData);
		CString strDataEsame = ExamTime.GetDate("%Y%m%d");

		// confronto le due date e se diverse do un alert che forse si è su un esame sbagliato //
		if (strDataOggi != strDataEsame)
			if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUM_LAUNCHACQUISITION), MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
				return;

		// long lLockedPatient = m_pEsamiView->m_pEsamiSet->m_lPaziente;
		long lLockedExam = m_pEsamiView->m_pEsamiSet->m_lContatore;
		if (CLockManager::Get()->LockExam(lLockedExam))
		{
			SetTimestampAcq();
			switch (theApp.m_enumScannerConnectionType)
			{
			case 0:
				AcqFromScanner(FALSE);
				break;
			case 1:
				AcqFromWindowMessage();
				break;
			default:
				break;
			}

			CLockManager::Get()->UnlockExam(lLockedExam);
		}
	}
	else
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_IMPORT_PREVIMAGE));
	}

	UpdateData(TRUE);

	// Sandro 30/12/2011 //
	if (m_pEsamiView->m_pDynForm[sub_puntipaziente] != NULL)
		m_pEsamiView->m_pDynForm[sub_puntipaziente]->SendMessage(MSG_FORM_LOAD); // OnFormLoad //	
}

void CAlbumForm::AcqFromScanner(BOOL bCI)
{
	ASSERT(m_pEsamiView != NULL);

	if (!theApp.m_bCanAcquire)
		return;

	if (!VerificaPercorso(theApp.m_sDirTemp))
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUM_FORM_ERR_PATH) + theApp.m_sDirTemp);
		return;
	}

	char szBuffer[512];

	sprintf_s(szBuffer, "%s", theApp.m_sDirTemp);
	WritePrivateProfileString("xTwain", "Path", szBuffer, theApp.m_sFileConfig);

	sprintf_s(szBuffer, "%08d_%08d_", m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);
	WritePrivateProfileString("xTwain", "ImagePrefix", szBuffer, theApp.m_sFileConfig);

	TCHAR szProcess[1024];
	sprintf_s(szProcess, "%s\\xTwain\\xTwain.exe %s", theApp.m_sDirProg, theApp.m_sFileConfig); // xTAIUAN //

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(NULL, szProcess, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		LPVOID lpMsgBuf;
		if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL))
			theApp.AfxMessageBoxEndo((LPCTSTR)lpMsgBuf);
		else
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_NOT_DEFINED));
		LocalFree(lpMsgBuf);

		return;
	}

	PROCESS_INFORMATION pi2;
	//Gabriel BUG 7749 - Capturar imagens via xtwain utilizando pedal USB
	if (theApp.m_bUsaCapturaScannerTGrabber)
	{
		TCHAR szProcess2[1024];
		CString sNomePaziente;
		sNomePaziente = m_pEsamiView->m_pPazientiSet->m_sNome + " " + m_pEsamiView->m_pPazientiSet->m_sCognome;
		sNomePaziente.Replace(" ", "|");

		sprintf_s(szProcess2, "%s\\T-Grabber.exe %08d %s %08d %s", theApp.m_sDirProg, m_pEsamiSet->m_lPaziente, sNomePaziente, m_pEsamiSet->m_lContatore, m_pEsamiSet->m_sCodEsame); // T-Grabber //

		STARTUPINFO si2;

		ZeroMemory(&si2, sizeof(si2));
		si2.cb = sizeof(si2);
		ZeroMemory(&pi2, sizeof(pi2));
		if (!CreateProcess(NULL, szProcess2, NULL, NULL, FALSE, 0, NULL, NULL, &si2, &pi2))
		{
			LPVOID lpMsgBuf;
			if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL))
				theApp.AfxMessageBoxEndo((LPCTSTR)lpMsgBuf);
			else
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_NOT_DEFINED));
			LocalFree(lpMsgBuf);

			return;
		}
	}

	// Sandro 04/05/2010 - RAS 20100072 --> //
	DWORD dwState = 0;
	do
	{
		// ogni tre secondi faccio il giro della cartella temporanea in cerca di nuovi files //
		dwState = WaitForSingleObject(pi.hProcess, 3000);

		BeginWaitCursor();
		m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);

		// importo solo le immagini e/o filmati dell'esame corrente //
		CString strWildcard;
		strWildcard.Format("%s\\%08d_%08d_*.*",
			theApp.m_sDirTemp,
			m_pEsamiSet->m_lPaziente,
			m_pEsamiSet->m_lContatore);

		CStringList listPath;
		WIN32_FIND_DATA dataFile;
		HANDLE hFile = FindFirstFile(strWildcard, &dataFile);
		if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
		{
			do
			{
				CString strFile(dataFile.cFileName);

				if (strFile.GetLength() > 3)
				{
					if ((strFile.Right(3).CompareNoCase("bmp") == 0) || (strFile.Right(3).CompareNoCase("mpg") == 0) || (strFile.Right(3).CompareNoCase("avi") == 0) || (strFile.Right(3).CompareNoCase("mp4") == 0) || (strFile.Right(3).CompareNoCase("dcm") == 0))
					{
						CString strAddFile = theApp.m_sDirTemp + "\\" + strFile;

						// controllo che la dimensione del file sia maggiore di 0 (capita per certi filmati e si blocca tutto) //

						HANDLE hFile = CreateFile(strAddFile, STANDARD_RIGHTS_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
						if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
						{
							LARGE_INTEGER llTemp;
							if (GetFileSizeEx(hFile, &llTemp))
							{
								if (llTemp.QuadPart > 0)
									listPath.AddHead(strAddFile);
								else
									DeleteFile(strAddFile);
							}
						}
						CloseHandle(hFile);

						BOOL export2Pacs = FALSE;
						//In modalità 2 devo avviare il trasferimento automatico su PACS
						if (theApp.m_lDcmStoreMode == 2)
							export2Pacs = TRUE;

						if (theApp.m_nApplication == PRG_DERMOX)
						{
							POSITION pos = listPath.GetHeadPosition();
							while (pos != NULL)
							{
								CAcqFromDiskDermoxDlg dlg(this, m_pEsamiView, listPath.GetAt(pos), TRUE);
								dlg.DoModal();
								listPath.GetNext(pos);
							}
						}
						else
						{
							if (!theApp.m_bUsaCapturaScannerTGrabber)
							{
								CImgIDList listIDImageImported;

								DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
								if (m_pEsamiView->m_pImgManager->ImportImgList(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, POINT_NONE, &listPath, FORM_IMM, FORM_MINI, &listIDImageImported, export2Pacs, FALSE, bCI) > 0)
									DeleteFile(strAddFile);
								if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
									CLogFileWriter::Get()->WriteLogLine0_ImmStore(timeGetTime() - timeForLog, m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore, 1, "CAlbumForm::AcqFromScanner");
							}
						}

						listPath.RemoveAll();
					}
				}
			} while (FindNextFile(hFile, &dataFile));
			FindClose(hFile);
		}
		EndWaitCursor();
		AfterMoveEsame();

	} while (dwState == WAIT_TIMEOUT);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	//Gabriel BUG 7749 - Capturar imagens via xtwain utilizando pedal USB
	if (theApp.m_bUsaCapturaScannerTGrabber)
	{
		TerminateProcess(pi2.hProcess, 0);

		CloseHandle(pi2.hProcess);
		CloseHandle(pi2.hThread);

		m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);

		// importo solo le immagini e/o filmati dell'esame corrente //
		CString strWildcard;
		strWildcard.Format("%s\\%08d_%08d_*.*",
			theApp.m_sDirTemp,
			m_pEsamiSet->m_lPaziente,
			m_pEsamiSet->m_lContatore);

		CStringList listPath;
		WIN32_FIND_DATA dataFile;
		HANDLE hFile = FindFirstFile(strWildcard, &dataFile);
		if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
		{
			do
			{
				CString strFile(dataFile.cFileName);

				if (strFile.GetLength() > 3)
				{
					if ((strFile.Right(3).CompareNoCase("bmp") == 0) || (strFile.Right(3).CompareNoCase("mpg") == 0) || (strFile.Right(3).CompareNoCase("avi") == 0) || (strFile.Right(3).CompareNoCase("mp4") == 0) || (strFile.Right(3).CompareNoCase("dcm") == 0))
					{
						CString strAddFile = theApp.m_sDirTemp + "\\" + strFile;

						// controllo che la dimensione del file sia maggiore di 0 (capita per certi filmati e si blocca tutto) //

						HANDLE hFile = CreateFile(strAddFile, STANDARD_RIGHTS_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
						if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
						{
							LARGE_INTEGER llTemp;
							if (GetFileSizeEx(hFile, &llTemp))
							{
								if (llTemp.QuadPart > 0)
									listPath.AddHead(strAddFile);
								else
									DeleteFile(strAddFile);
							}
						}
						CloseHandle(hFile);

						BOOL export2Pacs = FALSE;
						//In modalità 2 devo avviare il trasferimento automatico su PACS
						if (theApp.m_lDcmStoreMode == 2)
							export2Pacs = TRUE;

						if (theApp.m_nApplication == PRG_DERMOX)
						{
							POSITION pos = listPath.GetHeadPosition();
							while (pos != NULL)
							{
								CAcqFromDiskDermoxDlg dlg(this, m_pEsamiView, listPath.GetAt(pos), TRUE);
								dlg.DoModal();
								listPath.GetNext(pos);
							}
						}
						else
						{
							CImgIDList listIDImageImported;

							DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
							if (m_pEsamiView->m_pImgManager->ImportImgList(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, POINT_NONE, &listPath, FORM_IMM, FORM_MINI, &listIDImageImported, export2Pacs, FALSE, bCI) > 0)
								DeleteFile(strAddFile);
							if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
								CLogFileWriter::Get()->WriteLogLine0_ImmStore(timeGetTime() - timeForLog, m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore, 1, "CAlbumForm::AcqFromScanner");
						}

						listPath.RemoveAll();
					}
				}
			} while (FindNextFile(hFile, &dataFile));
			FindClose(hFile);
		}
		EndWaitCursor();
		AfterMoveEsame();
	}

	// <-- Sandro 04/05/2010 - RAS 20100072 //

	if (bCI)
	{
		if (m_pEsamiView->m_pDynForm[sub_consensoinformato] != NULL)
			m_pEsamiView->m_pDynForm[sub_consensoinformato]->SendMessage(MSG_FORM_LOAD);
	}
}

void CAlbumForm::AcqFromWindowMessage()
{
	ASSERT(m_pEsamiView != NULL);

	if (!theApp.m_bCanAcquire)
		return;

	BeginWaitCursor();

	if (!VerificaPercorso(theApp.m_sDirTemp))
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUM_FORM_ERR_PATH) + theApp.m_sDirTemp);
		return;
	}

	CString strFile;

	CStringList strFileList;

	if (!FileReceiver_ReceiveFile(&strFileList))
	{
		theApp.AfxMessageBoxEndo("Errore nell'acquisizione del file");
		return;
	}

	EndWaitCursor();

	CStringList tempList;

	POSITION pos = strFileList.GetHeadPosition();

	while (pos)
	{
		BeginWaitCursor();

		CString strFile = strFileList.GetNext(pos);

		if ((strFile.Right(3).CompareNoCase("img") == 0) || (strFile.Right(3).CompareNoCase("jpg") == 0) || (strFile.Right(3).CompareNoCase("bmp") == 0) || (strFile.Right(3).CompareNoCase("mpg") == 0) || (strFile.Right(3).CompareNoCase("avi") == 0) || (strFile.Right(3).CompareNoCase("mp4") == 0) || (strFile.Right(3).CompareNoCase("dcm") == 0))
		{
			CStringList listPath;
			listPath.AddHead(strFile);

			BOOL export2Pacs = FALSE;
			//In modalità 2 devo avviare il trasferimento automatico su PACS
			if (theApp.m_lDcmStoreMode == 2)
				export2Pacs = TRUE;

			if (theApp.m_nApplication == PRG_DERMOX)
			{
				tempList.AddTail(strFile);
			}
			else
			{
				CImgIDList listIDImageImported;

				DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
				if (m_pEsamiView->m_pImgManager->ImportImgList(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, POINT_NONE, &listPath, FORM_IMM, FORM_MINI, &listIDImageImported, export2Pacs, FALSE, FALSE) > 0)
					DeleteFile(strFile);
				if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
					CLogFileWriter::Get()->WriteLogLine0_ImmStore(timeGetTime() - timeForLog, m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore, 1, "CAlbumForm::AcqFromScanner");
			}

			listPath.RemoveAll();
		}

		EndWaitCursor();

	}

	//Adesso che sono in possesso della lista delle immagini posso procedere al post acquisizione
	if (m_bDermoxPhotoAcq)
	{
		CAcqFromDiskDermoxSceltaMultiplaDlg dlg(this, m_pEsamiView, &tempList, TRUE);
		dlg.DoModal();

		//Qui vanno spostate le immagini nella cartella backup se previsto
		if (theApp.m_bDermoxAcqDirettaMantieniCopiaBackup)
		{
			CString backupDir = "";
			if (m_sDermoxAcqPhotoDirectory.Right(1) == "\\")
				backupDir = m_sDermoxAcqPhotoDirectory + "Backup";
			else
				backupDir = m_sDermoxAcqPhotoDirectory + "\\Backup";

			//Creo la directory se non esiste
			if (GetFileAttributes(backupDir) == INVALID_FILE_ATTRIBUTES)
				CreateDirectory(backupDir, NULL);

			int i = 1;
			POSITION pos = tempList.GetHeadPosition();
			while (pos)
			{
				CString tempPath = tempList.GetNext(pos);
				int fileNameIndex = tempPath.ReverseFind('\\');

				CString newPath;
				newPath.Format("%s\\%li_%s", backupDir, i, tempPath.Right(tempPath.GetLength() - fileNameIndex - 1));

				MoveFile(tempPath, newPath);

				i++;
			}
		}
		else
		{
			POSITION pos = tempList.GetHeadPosition();
			while (pos)
			{
				CString tempPath = tempList.GetNext(pos);
				DeleteFile(tempPath);
			}
		}
	}

	AfterMoveEsame();
}

void CAlbumForm::OnReOrderSelected()
{
	if (m_pEsamiView->m_bImporting)
		return;

	if (!m_pEsamiView->m_pEsamiSet->m_bStessoDistretto)
		return;

	CImgIDList ImgIdList;

	int iPos = 0;
	for (POSITION pos1 = CFileBmp::GetFirstSelectedPos(); pos1 != NULL;)
	{
		CObSelect* pSel = CFileBmp::GetNextSelected(pos1);

		if ((pSel != NULL) && (pSel->m_bIsGlobal == FALSE))
		{
			int nNewPos = iPos;
			long lID = pSel->m_lID;

			m_pEsamiView->m_pImgManager->SetImagePosition(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, lID, nNewPos);

			this->SendMessage(MSG_AFTER_ELABIMAGE, (WPARAM)FALSE);
			CFileBmp::SendUpdateMessage();

			iPos++;
		}
	}
	OnImmUnselectAll();
}

void CAlbumForm::OnImmMultiPage()
{
	// Sandro 23/06/2017 //
	if ((theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury) && (!m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito.IsEmpty() && m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito != "-1"))
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAME_TRASFERITO) + " " + m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito + ".");
		return;
	}

	switch (m_pEsamiView->m_lLocalMultiPageTiffSelected)
	{
	case 0:
	{
		if (m_pEsamiView->m_lLocalImagesSelected == 0)
		{
			// creazione di un nuovo TIFF multipagina (da disco o da scanner) //

			CMultiPageTiffNewEdtDlg dlg(this, m_pEsamiView, m_pEsamiView->m_pPazientiSet, m_pEsamiView->m_pEsamiSet, 0, FALSE);
			dlg.DoModal();
		}
		else
		{
			// chiedo di unire tutte le immagini selezionate in un unico nuovo TIFF multipagina //

			if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_MULTIPAGETIFF_GROUP_NEW), MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				BOOL bNormali = FALSE;
				BOOL bCI = FALSE;
				ControllaNormaliCI(bNormali, bCI);
				if (bNormali && bCI)
				{
					// non posso mescolare immagini "normali" e immagini del consenso informato //
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_MULTIPAGETIFF_ERROR1), MB_ICONSTOP);
				}
				else
				{
					long lTiffID = 0;

					CStringList ArraySelected;
					FillArraySelected(&ArraySelected);

					if (ArraySelected.GetCount() > 0)
					{
						BeginWaitCursor();
						m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);

						DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
						if (m_pEsamiView->m_pImgManager->ImportImgListMP(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, POINT_NONE, &ArraySelected, FORM_MINI, FALSE, lTiffID) != ArraySelected.GetCount())
						{
							EndWaitCursor();
							theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMPORTERROR));
						}
						if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
							CLogFileWriter::Get()->WriteLogLine0_ImmStore(timeGetTime() - timeForLog, m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore, ArraySelected.GetCount(), "CAlbumForm::OnImmMultiPage");

						EndWaitCursor();

						ArraySelected.RemoveAll();

						AfterMoveEsame();
					}
				}
			}
		}
		break;
	}
	case 1:
	{
		// prendo l'ID del TIFF multipagina selezionato //
		long lTiffID = 0;

		POSITION pos = CFileBmp::GetFirstSelectedPos();
		while (pos != NULL)
		{
			CObSelect* pSel = CFileBmp::GetNextSelected(pos);

			if (pSel != NULL)
			{
				if (!pSel->m_bIsGlobal && (pSel->m_iType == _mptiff_))
				{
					lTiffID = pSel->m_lID;
					break;
				}
			}
		}

		if (m_pEsamiView->m_lLocalImagesSelected == 1)
		{
			// aggiunta di nuovi frames ad un TIFF multipagina preesistente (da disco o da scanner) //

			CMultiPageTiffNewEdtDlg dlg(this, m_pEsamiView, m_pEsamiView->m_pPazientiSet, m_pEsamiView->m_pEsamiSet, lTiffID, FALSE);
			dlg.DoModal();
		}
		else
		{
			// chiedo di accodare tutte le immagini selezionate in fondo al TIFF multipagina preesistente //

			if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_MULTIPAGETIFF_GROUP_EDT), MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				BOOL bNormali = FALSE;
				BOOL bCI = FALSE;
				ControllaNormaliCI(bNormali, bCI);
				if (bNormali && bCI)
				{
					// non posso mescolare immagini "normali" e immagini del consenso informato //
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_MULTIPAGETIFF_ERROR1), MB_ICONSTOP);
				}
				else
				{
					CStringList ArraySelected;
					FillArraySelected(&ArraySelected);

					if (ArraySelected.GetCount() > 0)
					{
						BeginWaitCursor();
						m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);

						DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
						if (m_pEsamiView->m_pImgManager->ImportImgListMP(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, POINT_NONE, &ArraySelected, FORM_MINI, FALSE, lTiffID) != ArraySelected.GetCount())
						{
							EndWaitCursor();
							theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMPORTERROR));
						}
						if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
							CLogFileWriter::Get()->WriteLogLine0_ImmStore(timeGetTime() - timeForLog, m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore, ArraySelected.GetCount(), "CAlbumForm::OnImmMultiPage");

						EndWaitCursor();

						ArraySelected.RemoveAll();

						AfterMoveEsame();
					}
				}
			}
		}
		break;
	}
	default:
	{
		// unisco tutte le immagini (normali e/o multipagina) all'interno di un nuovo TIFF multipagina //

		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_MULTIPAGETIFF_GROUP_NEW), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			BOOL bNormali = FALSE;
			BOOL bCI = FALSE;
			ControllaNormaliCI(bNormali, bCI);
			if (bNormali && bCI)
			{
				// non posso mescolare immagini "normali" e immagini del consenso informato //
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_MULTIPAGETIFF_ERROR1), MB_ICONSTOP);
			}
			else
			{
				CStringList ArraySelected;
				FillArraySelected(&ArraySelected);

				if (ArraySelected.GetCount() > 0)
				{
					long lTiffID = 0;

					BeginWaitCursor();
					m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);

					DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
					if (m_pEsamiView->m_pImgManager->ImportImgListMP(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, POINT_NONE, &ArraySelected, FORM_MINI, FALSE, lTiffID) != ArraySelected.GetCount())
					{
						EndWaitCursor();
						theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMPORTERROR));
					}
					if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
						CLogFileWriter::Get()->WriteLogLine0_ImmStore(timeGetTime() - timeForLog, m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore, ArraySelected.GetCount(), "CAlbumForm::OnImmMultiPage");

					EndWaitCursor();

					ArraySelected.RemoveAll();

					AfterMoveEsame();
				}
			}
		}

		break;
	}
	}
}

void CAlbumForm::OnImmSelectAll()
{
	CFileBmp::DeleteListSelected(LOCAL_IMAGES);

	//

	m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);

	CString strDvdLabel;
	BOOL bConfirmed = m_pEsamiView->m_pImgManager->IsExamConfirmed(strDvdLabel);

	POSITION pos = m_ImgListOrgani.GetHeadPosition();
	while (pos != NULL)
	{
		IMG img = m_ImgListOrgani.GetAt(pos).img;

		CFileBmp::NewSelected(img.lID, FALSE, img.type, img.szDescription, m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore, bConfirmed, strDvdLabel, img.bCI);

		m_ImgListOrgani.GetNext(pos);
	}

	//

	AfterElabImage((WPARAM)FALSE, (LPARAM)0);
}

void CAlbumForm::OnImmUnselectAll()
{
	AfterElabImage((WPARAM)TRUE, (LPARAM)0); // <-- con il TRUE ci pensa già lui a deselezionare tutte le immagini //
}

void CAlbumForm::OnImmPreview()
{
	BOOL bStampa = TRUE;

	if (theApp.m_bPersonalizzazioniBrasileFleury && !m_pEsamiSet->m_sFleuryTrasferito.IsEmpty() || m_pEsamiSet->m_lStatoInvioCentraleRefertaz > 0) //Julio 04/05/2018
	{
		theApp.AfxMessageBoxEndo("A operação não pode ser realizada pois o exame não se encontra na unidade atual");
		return;
	}

	CString sMessaggio = "";
	if (theApp.m_bPersonalizzazioniBrasileFleury)
		bStampa = FleuryPossoStampare(sMessaggio, m_pEsamiSet->m_sRicovero, m_pEsamiSet->m_sCodEsame);

	if (bStampa)
	{
		if (theApp.m_bPersonalizzazioniBrasileFleury)
		{
			m_pEsamiView->AnteprimaStampaImmagini(STAMPA, LOCAL_IMAGES, 1);
		}
		else
		{
			m_pEsamiView->AnteprimaStampaImmagini(ANTEPRIMA, LOCAL_IMAGES, 1);
		}
	}
	else
		theApp.AfxMessageBoxEndo(sMessaggio);
}

void CAlbumForm::OnImmDelete()
{
	if (theApp.m_nProgramMode != NOTHING_MODE || !m_pEsamiSet->IsOpen() || m_pEsamiSet->IsBOF() || m_pEsamiSet->IsEOF())
		return;

	if (CFileBmp::m_listSelected.IsEmpty())
		return;

	CString sNumSel;
	GetDlgItemText(IDC_STATIC_NUM2, sNumSel);

	CConfermaEliminazioneDlg dlgConferma(this, sNumSel);
	if (dlgConferma.DoModal() == IDCANCEL)
		return;

	// if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUM_FORM_DEL_IMG), MB_YESNO) == IDNO)
	//    return;

	CImgIDList ImgIdList;
	for (POSITION pos1 = CFileBmp::GetFirstSelectedPos(); pos1 != NULL;)
	{
		CObSelect* pSel = CFileBmp::GetNextSelected(pos1);

		if ((pSel != NULL) && (pSel->m_bIsGlobal == FALSE))
			ImgIdList.AddTail(pSel->m_lID);
	}

	// Sandro 19/04/2017 // BUG 390 //

	POSITION pos2 = ImgIdList.GetHeadPosition();
	while (pos2 != NULL)
	{
		long lImageID = ImgIdList.GetAt(pos2);

		CString sOrigFile = m_pEsamiView->m_pImgManager->GetFullPath(lImageID);
		CString sDestFile = m_pEsamiView->m_pImgManager->GetFullPathDeleted(lImageID, (theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury) ? m_pEsamiSet->m_sCodEsame : "");

		// AfxMessageBox(sOrigFile + "\n\n" + sDestFile);

		MoveFile(sOrigFile, sDestFile);

		ImgIdList.GetNext(pos2);
	}

	//

	m_pEsamiView->m_pImgManager->DelImgList(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, &ImgIdList);

	ImgIdList.RemoveAll();

	CFileBmp::DeleteListSelected(LOCAL_IMAGES);

	AfterMoveEsame();

	UpdateData(TRUE);
}

void CAlbumForm::OnImmAlbum()
{
	CAlbumEsameDlg dlg(this, m_pEsamiView);
	dlg.DoModal();

	AfterElabImage((WPARAM)FALSE, 0);

	UpdateData(TRUE);
}

void CAlbumForm::OnImmAcqFromDisk()
{
	if (!m_pEsamiSet->IsOpen() || m_pEsamiSet->IsBOF() || m_pEsamiSet->IsEOF())
		return;

	// Sandro 23/06/2017 //
	if ((theApp.m_bPersonalizzazioniBrasileCamargo || theApp.m_bPersonalizzazioniBrasileFleury) && (!m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito.IsEmpty() && m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito != "-1"))
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ESAME_TRASFERITO) + " " + m_pEsamiView->m_pEsamiSet->m_sFleuryTrasferito + ".");
		return;
	}

	if (CEsamiSet().IsConiugatoSecondario(m_pEsamiSet->m_lContatore))
	{
		theApp.AfxMessageBoxEndo(IDS_FLEURY_CONIUGATO_SECONDARIO);
		return;
	}

	CStringList ArraySelected;

	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT | OFN_READONLY | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, NULL, this, 0, FALSE);
	CString strFileDialog;
	int iMaxFiles = 100;
	int iBuffSize = (iMaxFiles * (MAX_PATH + 1)) + 1;

	dlgFile.GetOFN().lpstrFile = strFileDialog.GetBuffer(iBuffSize);
	dlgFile.GetOFN().nMaxFile = iBuffSize;
	dlgFile.GetOFN().lpstrInitialDir = theApp.m_sEditImm;

	if (dlgFile.DoModal() == IDOK)
	{
		// Sandro Gallina - 06/04/2004 --> //
		if (theApp.m_bCheckImm == FALSE)
		{
			CString strTemp = dlgFile.GetPathName();
			int iTemp = 0;
			int iLastSlash = 0;

			while (iTemp >= 0)
			{
				iTemp = strTemp.Find('\\', iLastSlash);
				if (iTemp >= 0)
					iLastSlash = iTemp + 1;
			}

			theApp.m_sEditImm = strTemp.Left(iLastSlash - 1);
			WritePrivateProfileString(szPercorsi, szEditImm, theApp.m_sEditImm, theApp.m_sFileConfig);
		}
		// <-- Sandro Gallina - 06/04/2004 //

		POSITION pos = dlgFile.GetStartPosition();
		while (pos)
		{
			CString strFile = dlgFile.GetNextPathName(pos);

			if (strFile != "")
			{
				BOOL bContinue = TRUE;
				int nIndex = 0;
				int nMaxIndex = ArraySelected.GetSize();

				while ((bContinue == TRUE) && (nIndex < nMaxIndex))
				{
					POSITION pos = ArraySelected.FindIndex(nIndex);
					CString strIndex = ArraySelected.GetAt(pos);

					if (strIndex > strFile)
					{
						bContinue = FALSE;
						ArraySelected.InsertAfter(pos, strFile);
					}

					nIndex++;
				}

				if (bContinue)
					ArraySelected.AddTail(strFile);
			}
		}
	}
	strFileDialog.ReleaseBuffer();

	if (ArraySelected.GetCount() > 0)
	{
		BeginWaitCursor();
		m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);

		BOOL export2Pacs = FALSE;
		//In modalità 2 devo avviare il trasferimento automatico su PACS
		if (theApp.m_lDcmStoreMode == 2)
			export2Pacs = TRUE;

		if (theApp.m_nApplication == PRG_DERMOX)
		{
			POSITION pos = ArraySelected.GetHeadPosition();
			while (pos != NULL)
			{
				CAcqFromDiskDermoxDlg dlg(this, m_pEsamiView, ArraySelected.GetAt(pos), FALSE);
				dlg.DoModal();
				ArraySelected.GetNext(pos);
			}
		}
		else
		{
			CImgIDList listIDImageImported;

			DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
			if (m_pEsamiView->m_pImgManager->ImportImgList(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, POINT_NONE, &ArraySelected, FORM_IMM, FORM_MINI, &listIDImageImported, export2Pacs, FALSE, FALSE) != ArraySelected.GetCount())
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMPORTERROR));
			if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
				CLogFileWriter::Get()->WriteLogLine0_ImmStore(timeGetTime() - timeForLog, m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore, ArraySelected.GetCount(), "CAlbumForm::OnImmAcqFromDisk");
		}
		EndWaitCursor();

		ArraySelected.RemoveAll();

		AfterMoveEsame();

		SetTimestampAcq();
	}

	UpdateData(TRUE);

	// Sandro 30/12/2011 //
	if (m_pEsamiView->m_pDynForm[sub_puntipaziente] != NULL)
		m_pEsamiView->m_pDynForm[sub_puntipaziente]->SendMessage(MSG_FORM_LOAD); // OnFormLoad //	
}

void CAlbumForm::RefreshAlbum()
{
	for (int i = 0; i < m_nNumMaxBmp; i++)
		CFileBmp::ReselectBmp(m_pFileBmp[i], TRUE);

	UpdateData(FALSE);

	refreshStaticComponentTotImage();	// BUG 4197 - total imagens / qtd selecionadas / OK
}

void CAlbumForm::ResetAlbum()
{
	ResetVetDiapo(TRUE);

	for (int i = 0; i < m_nNumMaxBmp; i++)
		m_pFileBmp[i]->ResetImage();

	refreshStaticComponentTotImage();	// BUG 4197 - total imagens / qtd selecionadas / OK
}

void CAlbumForm::ViewFilmAndSelectFrame(CString strFileFilm)
{
	// UINT retCode; // Sandro 07/04/2010 - CreateProcess invece che WinExec //

	HMODULE hModule = NULL;

	// XRClient //
	ENABLEVIDEOOUTPUTPTR XRClient_EnableVideoOutput;
	GETERROROCCURREDPTR XRClient_GetErrorOccurred;
	GETVIDEOINPUTPTR XRClient_GetVideoInput;

	VerificaPercorso(theApp.m_sDirTemp);

	if (_taccess(strFileFilm, 00) == 0)
	{
		COleDateTime dateNow = COleDateTime::GetCurrentTime();

		// CHAR szCmdline[512]; // Sandro 07/04/2010 - CreateProcess invece che WinExec //
		TCHAR szProcess[1024]; // Sandro 07/04/2010 - CreateProcess invece che WinExec //
		BOOL bProcessOK = FALSE;

		if (theApp.m_bVisAbilita)
		{
#ifdef _DEBUG
			hModule = ::LoadLibrary("xrclientd.dll");
#else
			hModule = ::LoadLibrary("xrclient.dll");
#endif

			if (hModule)
			{
				XRClient_GetErrorOccurred = (GETERROROCCURREDPTR)GetProcAddress(hModule, "GetErrorOccurred");
				XRClient_EnableVideoOutput = (ENABLEVIDEOOUTPUTPTR)GetProcAddress(hModule, "EnableVideoOutput");
				XRClient_GetVideoInput = (GETVIDEOINPUTPTR)GetProcAddress(hModule, "GetVideoInput");
			}

			if (theApp.m_iPrevInput > 0 && theApp.m_bVisAbilitaMonitor && XRClient_GetVideoInput)
				theApp.m_iPrevInput = XRClient_GetVideoInput(theApp.m_sVisPortaMonitor);

			if (theApp.m_bVisAbilitaMonitor && XRClient_EnableVideoOutput && !XRClient_EnableVideoOutput(theApp.m_sVisPortaMonitor, _HD_SDI1))
			{
				TCHAR szError[2048];
				ZeroMemory(szError, sizeof(char) * 2048);
				XRClient_GetErrorOccurred(szError);
				CString sError;
				sError.Format(theApp.GetMessageString(IDS_ERRORE_REMOTO), szError);
				theApp.AfxMessageBoxEndo(sError);
			}

			sprintf_s(szProcess, "\"%s\\xPlay\\xPlay.exe\" -f %s -d %s -r on -s on -p on -a off -c %d -o -i %08d_%08d_%04d%02d%02d%02d%02d%02d -x %s %li",
				theApp.m_sDirProg,
				strFileFilm,
				theApp.m_sDirTemp,
				100,
				m_pEsamiSet->m_lPaziente,
				m_pEsamiSet->m_lContatore,
				dateNow.GetYear(),
				dateNow.GetMonth(),
				dateNow.GetDay(),
				dateNow.GetHour(),
				dateNow.GetMinute(),
				dateNow.GetSecond(),
				theApp.m_sVisIp,
				theApp.m_lVisPorta);
		}
		else
		{
			sprintf_s(szProcess, "\"%s\\xPlay\\xPlay.exe\" -f %s -d %s -r on -s on -p on -a off -c %d -o -i %08d_%08d_%04d%02d%02d%02d%02d%02d",
				theApp.m_sDirProg,
				strFileFilm,
				theApp.m_sDirTemp,
				100,
				m_pEsamiSet->m_lPaziente,
				m_pEsamiSet->m_lContatore,
				dateNow.GetYear(),
				dateNow.GetMonth(),
				dateNow.GetDay(),
				dateNow.GetHour(),
				dateNow.GetMinute(),
				dateNow.GetSecond());
		}

		// retCode = WinExec(szCmdline, SW_SHOW); // Sandro 07/04/2010 - CreateProcess invece che WinExec //

		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		if (!CreateProcess(NULL, szProcess, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
		{
			LPVOID lpMsgBuf;
			if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL))
				theApp.AfxMessageBoxEndo((LPCTSTR)lpMsgBuf);
			else
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_NOT_DEFINED));
			LocalFree(lpMsgBuf);
		}
		else
		{
			WaitForSingleObject(pi.hProcess, INFINITE);
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);

			bProcessOK = TRUE;
		}

		if (theApp.m_iPrevInput > 0)
		{
			if (theApp.m_bVisAbilita && theApp.m_bVisAbilitaMonitor && XRClient_EnableVideoOutput && !XRClient_EnableVideoOutput(theApp.m_sVisPortaMonitor, theApp.m_iPrevInput))
			{
				TCHAR szError[2048];
				ZeroMemory(szError, sizeof(char) * 2048);
				XRClient_GetErrorOccurred(szError);
				CString sError;
				sError.Format(theApp.GetMessageString(IDS_ERRORE_REMOTO), szError);
				theApp.AfxMessageBoxEndo(sError);
			}
		}

		if (theApp.m_bVisAbilita && hModule)
			FreeLibrary(hModule);

		/* Sandro 07/04/2010 - CreateProcess invece che WinExec
		if (retCode < 32)
		{
		switch(retCode)
		{
		case 0:
		{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUM_FORM_EXEC_XPLAY_ERR_1));
		break;
		}

		case ERROR_BAD_FORMAT:
		{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUM_FORM_EXEC_XPLAY_ERR_2));
		break;
		}

		case ERROR_FILE_NOT_FOUND:
		{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUM_FORM_EXEC_XPLAY_ERR_3));
		break;
		}

		case ERROR_PATH_NOT_FOUND:
		{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUM_FORM_EXEC_XPLAY_ERR_4));
		break;
		}

		default:
		{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUM_FORM_EXEC_XPLAY_ERR_5));
		break;
		}
		}
		}
		else
		{
		*/
		if (bProcessOK)
		{
			MSG	 msg;
			BOOL bContinue = TRUE;

			while (bContinue)
			{
				if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					if (msg.message == MSG_XPLAY_CLOSE)
						bContinue = FALSE;

					TranslateMessage(&msg);
					DispatchMessage(&msg);
					Sleep(25);
				}
			}

			// Davide 06.06.2008 Importo solo le immagini e/o filmati dell'esame corrente

			BeginWaitCursor();
			m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);

			CString strWildcard;
			strWildcard.Format("%s\\%08d_%08d_*.*",
				theApp.m_sDirTemp,
				m_pEsamiSet->m_lPaziente,
				m_pEsamiSet->m_lContatore);

			CStringList listPath;
			WIN32_FIND_DATA dataFile;
			HANDLE hFile = FindFirstFile(strWildcard, &dataFile);
			if (hFile != NULL && hFile != INVALID_HANDLE_VALUE)
			{
				do
				{
					CString strFile(dataFile.cFileName);
					if (strFile.GetLength() > 3)
					{
						if ((strFile.Right(3).CompareNoCase("bmp") == 0) || (strFile.Right(3).CompareNoCase("mpg") == 0) || (strFile.Right(3).CompareNoCase("avi") == 0) || (strFile.Right(3).CompareNoCase("mp4") == 0) || (strFile.Right(3).CompareNoCase("dcm") == 0))
						{
							// controllo che la dimensione del file sia maggiore di 0 (capita per certi filmati e si blocca tutto) //

							HANDLE hFile = CreateFile(theApp.m_sDirTemp + "\\" + strFile, STANDARD_RIGHTS_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
							if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
							{
								LARGE_INTEGER llTemp;
								if (GetFileSizeEx(hFile, &llTemp))
								{
									if (llTemp.QuadPart > 0)
										listPath.AddHead(CString(theApp.m_sDirTemp + "\\" + strFile));
									else
										DeleteFile(theApp.m_sDirTemp + "\\" + strFile);
								}
							}
							CloseHandle(hFile);
						}
					}
				} while (FindNextFile(hFile, &dataFile));

				FindClose(hFile);
			}

			if (listPath.GetCount() > 0)
			{
				CImgIDList listIDImageImported;

				DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
				int nImported = m_pEsamiView->m_pImgManager->ImportImgList(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, POINT_NONE, &listPath, FORM_IMM, FORM_MINI, &listIDImageImported, FALSE, FALSE, FALSE);
				DeleteDirectory(theApp.m_sDirTemp);
				VerificaPercorso(theApp.m_sDirTemp);
				if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
					CLogFileWriter::Get()->WriteLogLine0_ImmStore(timeGetTime() - timeForLog, m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore, nImported, "CAlbumForm::ViewFilmAndSelectFrame");
			}

			// Sandro 24/09/2012 // provo a sostituire AfterMoveEsame con AfterElabImage che NON riposiziona l'album in prima pagina //
			// AfterMoveEsame();
			AfterElabImage((WPARAM)FALSE, NULL);

			EndWaitCursor();
		}
	}
}

void CAlbumForm::ViewFilm(CString strFileFilm)
{
	HMODULE hModule = NULL;

	// XRClient //
	ENABLEVIDEOOUTPUTPTR XRClient_EnableVideoOutput;
	GETERROROCCURREDPTR XRClient_GetErrorOccurred;
	GETVIDEOINPUTPTR XRClient_GetVideoInput;

	VerificaPercorso(theApp.m_sDirTemp);

	if (_taccess(strFileFilm, 00) == 0)
	{
		TCHAR szProcess[1024];

		if (theApp.m_bVisAbilita)
		{
#ifdef _DEBUG
			hModule = ::LoadLibrary("xrclientd.dll");
#else
			hModule = ::LoadLibrary("xrclient.dll");
#endif

			if (hModule)
			{
				XRClient_GetErrorOccurred = (GETERROROCCURREDPTR)GetProcAddress(hModule, "GetErrorOccurred");
				XRClient_EnableVideoOutput = (ENABLEVIDEOOUTPUTPTR)GetProcAddress(hModule, "EnableVideoOutput");
				XRClient_GetVideoInput = (GETVIDEOINPUTPTR)GetProcAddress(hModule, "GetVideoInput");
			}

			if (theApp.m_iPrevInput > 0 && theApp.m_bVisAbilitaMonitor && XRClient_GetVideoInput)
				theApp.m_iPrevInput = XRClient_GetVideoInput(theApp.m_sVisPortaMonitor);

			if (theApp.m_bVisAbilitaMonitor && XRClient_EnableVideoOutput && !XRClient_EnableVideoOutput(theApp.m_sVisPortaMonitor, _HD_SDI1))
			{
				TCHAR szError[2048];
				ZeroMemory(szError, sizeof(char) * 2048);
				XRClient_GetErrorOccurred(szError);
				CString sError;
				sError.Format(theApp.GetMessageString(IDS_ERRORE_REMOTO), szError);
				theApp.AfxMessageBoxEndo(sError);
			}

			sprintf_s(szProcess, "\"%s\\xPlay\\xPlay.exe\" -f %s -d %s -r on -s off -p off -a on -c %d -o -x %s %li",
				theApp.m_sDirProg,
				strFileFilm,
				theApp.m_sDirTemp,
				100,
				theApp.m_sVisIp,
				theApp.m_lVisPorta);
		}
		else
		{
			sprintf_s(szProcess, "\"%s\\xPlay\\xPlay.exe\" -f %s -d %s -r on -s off -p off -a on -c %d -o",
				theApp.m_sDirProg,
				strFileFilm,
				theApp.m_sDirTemp,
				100);
		}

		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		if (!CreateProcess(NULL, szProcess, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
		{
			LPVOID lpMsgBuf;
			if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL))
				theApp.AfxMessageBoxEndo((LPCTSTR)lpMsgBuf);
			else
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_NOT_DEFINED));
			LocalFree(lpMsgBuf);
		}
		else
		{
			WaitForSingleObject(pi.hProcess, INFINITE);
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
		}

		if (theApp.m_iPrevInput > 0)
			if (theApp.m_bVisAbilita && theApp.m_bVisAbilitaMonitor && XRClient_EnableVideoOutput && !XRClient_EnableVideoOutput(theApp.m_sVisPortaMonitor, theApp.m_iPrevInput))
			{
				TCHAR szError[2048];
				ZeroMemory(szError, sizeof(char) * 2048);
				XRClient_GetErrorOccurred(szError);
				CString sError;
				sError.Format(theApp.GetMessageString(IDS_ERRORE_REMOTO), szError);
				theApp.AfxMessageBoxEndo(sError);
			}

		if (theApp.m_bVisAbilita && hModule)
			FreeLibrary(hModule);
	}
}

void CAlbumForm::OnImmAss()
{
	CAssociaImmagini dlg(this, m_pEsamiView);
	dlg.DoModal();

	AfterMoveEsame(FALSE);

	UpdateData(TRUE);
}

LRESULT CAlbumForm::OnUpdateSel(WPARAM wParam, LPARAM lParam)
{
	refreshStaticComponentTotImage();	// BUG 4197 - total imagens / qtd selecionadas / OK
	int iTotImgSelected = (int)wParam;
	SetDlgItemInt(IDC_STATIC_NUM2, (iTotImgSelected<0 ? 0 : iTotImgSelected));

	return 0;
}

LRESULT CAlbumForm::OnResizeForm(WPARAM wParam, LPARAM lParam)
{
	CEndoxResizableDlg::OnResizeForm(wParam, lParam);

	for (int i = 0; i < m_nNumMaxBmp; i++)
		if (m_pFileBmp[i] != NULL)
			m_pFileBmp[i]->SendMessage(EPM_RESIZE_FORM);

	refreshStaticComponentTotImage();	// BUG 4197 - total imagens / qtd selecionadas / OK

	return 0;
}

void CAlbumForm::OnTimer(UINT_PTR nIDEvent)
{
	CDialog::OnTimer(nIDEvent);

	//Julio BUG 3361 - Captura continua DICOM
	/*if (nIDEvent == 0xAAB)
	{
	if (m_pEsamiView != NULL)
	PostAcquisizione();
	}*/

	if (nIDEvent == 0xAAA)
	{
		if (!theApp.m_sPercorsoOrigineDemoAliar.IsEmpty())
		{
			BOOL bAggiorna = FALSE;

			CFileFind finder;
			BOOL bWorking = finder.FindFile(theApp.m_sPercorsoOrigineDemoAliar + "\\*.*");
			while (bWorking)
			{
				bWorking = finder.FindNextFile();
				if (finder.IsDots())
					continue;
				if (finder.IsDirectory())
					continue;

				CFile fileTeeemp;
				if (fileTeeemp.Open(finder.GetFilePath(), CFile::modeReadWrite))
				{
					fileTeeemp.Close();

					// copio il file nella cartella di destinazione //

					BOOL bCopiato = FALSE;
					if (!theApp.m_sPercorsoDestinazioneDemoAliar.IsEmpty())
					{
						CCustomDate dateTeeemp(TRUE, TRUE);

						CString sDestFolder;
						sDestFolder.Format("%s\\%04d\\%02d\\%02d\\", theApp.m_sPercorsoDestinazioneDemoAliar, dateTeeemp.GetYear(), dateTeeemp.GetMonth(), dateTeeemp.GetDay());

						if (VerificaPercorso(sDestFolder))
							bCopiato = CopyFile(finder.GetFilePath(), sDestFolder + finder.GetFileName(), FALSE);
					}

					// importo il file negli allegati all'esame //

					BOOL bImportato = m_pEsamiView->m_pDocManager->ImportDoc(m_pEsamiView->m_pPazientiSet->m_lContatore, m_pEsamiView->m_pEsamiSet->m_lContatore, "" /* descrizione */, "" /* data */, finder.GetFilePath(), FALSE);

					if (bImportato)
						bAggiorna = TRUE;

					// cancello il file origine //

					if (bCopiato && bImportato)
						DeleteFile(finder.GetFilePath());
				}
				else
				{
					fileTeeemp.Close();
				}
			}
			finder.Close();

			if (bAggiorna)
			{
				// aggiorno il numero degli allegati all'esame //
				m_pEsamiView->m_lNumDocumentsPatient = m_pEsamiView->m_pDocManager->GetAttachedDocNumberPatient(m_pPazientiSet->m_lContatore);
				m_pEsamiView->m_lNumDocumentsExam = m_pEsamiView->m_pDocManager->GetAttachedDocNumberExam(m_pEsamiSet->m_lContatore, DOCUMENTS_NOT_EXPORT);
				m_pEsamiView->m_lNumDocumentsExamCarestream = m_pEsamiView->m_pDocManager->GetAttachedDocNumberExam(m_pEsamiSet->m_lContatore, DOCUMENTS_ONLY_EXPORT);
			}
		}
	}
}

void CAlbumForm::CaricaPunti()
{
	long lIdPunto;
	long lIdOrgano;
	long lX;
	long lY;
	IMG_ORGANI img_organi;

	BOOL bFindIndex;

	POSITION pos1 = m_ImgListOrgani.GetHeadPosition();
	POSITION pos2;

	m_listPunti.RemoveAll();
	while (pos1 != NULL)
	{
		lIdPunto = CImmaginiPuntiSet().GetIDPunto(m_ImgListOrgani.GetAt(pos1).img.lID);
		if (lIdPunto > 0)
		{
			if (CPuntiSet().GetDatiPunto(lIdPunto, lIdOrgano, lX, lY) == TRUE)
			{
				img_organi = m_ImgListOrgani.GetAt(pos1);
				img_organi.iPunto = 0;

				bFindIndex = FALSE;
				pos2 = m_listPunti.GetHeadPosition();
				while (pos2 != NULL)
				{
					if (m_listPunti.GetAt(pos2).lIdOrgano == lIdOrgano)
					{
						if ((lX == m_listPunti.GetAt(pos2).lX) && (lY == m_listPunti.GetAt(pos2).lY))
						{
							bFindIndex = TRUE;
							break;
						}
					}

					m_listPunti.GetNext(pos2);
					img_organi.iPunto++;
				}

				if (bFindIndex == FALSE)
				{
					tagPunti puntoTemp;

					puntoTemp.lIdPunto = lIdPunto;
					puntoTemp.lIdOrgano = lIdOrgano;
					puntoTemp.lX = lX;
					puntoTemp.lY = lY;

					m_listPunti.AddTail(puntoTemp);

					img_organi.iPunto = m_listPunti.GetCount() - 1;
				}

				m_ImgListOrgani.SetAt(pos1, img_organi);
			}
		}
		m_ImgListOrgani.GetNext(pos1);
	}
}

BOOL CAlbumForm::CheckTempFolder()
{
	SYSTEMTIME st; GetLocalTime(&st); TCHAR szDateNow[1024]; sprintf_s(szDateNow, "%04d/%02d/%02d_%02d:%02d:%02d.%03d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	CString strLog = "";
	strLog.Format("[%s] Executando %s "
		, szDateNow
		, "CAlbumForm::CheckTempFolder()"
		);
	CLogFileWriter::Get()->WriteLogLine0(strLog);


	// #ifndef _DEBUG

	BOOL bError = FALSE;
	CList<tagIMAGESINFO> listImages;
	BOOL bRefreshAlbum = FALSE;
	CFileFind finder;
	CString strFile;

	//00069584_00000062_2006080317441000.BMP
	//                        PazID    ExamID   Date/Hour
	CString strWildcard = "????????_????????_????????????????.*";

	if (theApp.m_sDirTempAcq.IsEmpty())
		theApp.m_sDirTempAcq = theApp.m_sDirTemp;

	BOOL bWorking = finder.FindFile(theApp.m_sDirTempAcq + "\\" + strWildcard);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDots())
			continue;
		if (finder.IsDirectory())
			continue;

		strFile = finder.GetFileName();
		strFile.MakeUpper();
		if ((strFile.Right(3).CompareNoCase("bmp") == 0) || (strFile.Right(3).CompareNoCase("mpg") == 0) || (strFile.Right(3).CompareNoCase("avi") == 0) || (strFile.Right(3).CompareNoCase("mp4") == 0) || (strFile.Right(3).CompareNoCase("dcm") == 0))
		{
			long lPatientImageID = atoi(strFile.Left(8));
			long lExamImageID = atoi(strFile.Mid(9, 8));

			if (lPatientImageID != 0 && lExamImageID != 0)
			{
				BOOL bFindElement = FALSE;
				for (POSITION pos = listImages.GetHeadPosition(); pos;)
				{
					tagIMAGESINFO info = listImages.GetNext(pos);
					if (info.lPatientID == lPatientImageID && info.lExamID == lExamImageID)
					{
						tagIMAGEINFO infoImage;
						// strcpy_s(infoImage.szDateHour, strImageDate);
						// strcpy_s(infoImage.szExt, strFile.Right(3));
						strcpy_s(infoImage.szFileName, strFile);
						info.pImageListID->AddTail(infoImage);
						bFindElement = TRUE;
						break;
					}
				}

				if (!bFindElement)
				{
					tagIMAGESINFO info;
					tagIMAGEINFO infoImage;
					info.lPatientID = lPatientImageID;
					info.lExamID = lExamImageID;
					info.pImageListID = new CList<tagIMAGEINFO>;
					// strcpy_s(infoImage.szDateHour, strImageDate);
					// strcpy_s(infoImage.szExt, strFile.Right(3));
					strcpy_s(infoImage.szFileName, strFile);
					info.pImageListID->AddTail(infoImage);
					listImages.AddTail(info);
				}
			}
		}
	}
	finder.Close();
	//

	long lPatientID, lExamID;
	m_pEsamiView->m_pImgManager->GetCurrentIDs(lPatientID, lExamID);

	// Scansione immagini trovate ed eventuale ripristino...
	for (POSITION pos = listImages.GetHeadPosition(); pos;)
	{
		tagIMAGESINFO info = listImages.GetNext(pos);
		m_pEsamiView->m_pImgManager->SetCurrentIDs(info.lPatientID, info.lExamID);
		CStringList ImageList;

		for (POSITION posImage = info.pImageListID->GetHeadPosition(); posImage;)
		{
			tagIMAGEINFO imageInfo = info.pImageListID->GetNext(posImage);
			strFile.Format("%s\\%s", theApp.m_sDirTempAcq, imageInfo.szFileName);

			LPCTSTR pszFile = strFile;
			DWORD dwAttrs = dwAttrs = GetFileAttributes(pszFile);
			if (dwAttrs != INVALID_FILE_ATTRIBUTES)
			{
				SetFileAttributes(pszFile, GetFileAttributes(pszFile) & ~FILE_ATTRIBUTE_READONLY);
			}

			if (_access(strFile, 06) == 0)	// _access(file,attr) >> 00=Existência apenas | 02=Somente gravação | 04=Somente leitura | 06=Leitura e gravação
				ImageList.AddTail(strFile);
			else
			{
				SYSTEMTIME st; GetLocalTime(&st); TCHAR szDateNow[1024]; sprintf_s(szDateNow, "%04d/%02d/%02d_%02d:%02d:%02d.%03d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
				CString strLog = "";
				strLog.Format("[%s] %s Problema com arquivo '%s' que deveria ter propriedade.acesso igual a Leitura e Gravação."
					, szDateNow
					, "CAlbumForm::CheckTempFolder()"
					, strFile
					);
				CLogFileWriter::Get()->WriteLogLine0(strLog);
			}
		}

		if (!ImageList.IsEmpty())
		{
			CPazientiSet setPatient;
			CEsamiSet setExam;
			CTipoEsameSet setTipoEsame;
			CString strFilter, strQuery;

			strFilter.Format("Contatore=%li", info.lPatientID);
			setPatient.SetOpenFilter(strFilter);

			if (setPatient.OpenRecordset("CAlbumForm::CheckTempFolder"))
			{
				strFilter.Format("Contatore=%li", info.lExamID);
				setExam.SetOpenFilter(strFilter);

				if (setExam.OpenRecordset("CAlbumForm::CheckTempFolder"))
				{
					if (!setPatient.IsEOF() && !setExam.IsEOF())
					{
						CCustomDate dateTemp(setExam.m_lData);

						CString strQuestion;
						strQuestion.Format(theApp.GetMessageString(IDS_REPORT_TEMP_IMAGE), setPatient.m_sCognome, setPatient.m_sNome, setTipoEsame.GetDescrizione(setExam.m_lIDEsame), dateTemp.GetDate("%d/%m/%y"));
						theApp.AfxMessageBoxEndo(strQuestion, MB_ICONEXCLAMATION | MB_OK);

						CWaitImportImageDlg dlgImp(this, m_pEsamiView->m_pImgManager, &ImageList);
						dlgImp.DoModal();

						Sleep(1000); //prevenir que uma imagem entre 2 vezes 

						if (dlgImp.m_sbError)
							bError = TRUE;

						if (info.lPatientID == lPatientID && info.lExamID == lExamID)
							bRefreshAlbum = TRUE;
					}

					setExam.CloseRecordset("CAlbumForm::CheckTempFolder");
				}

				setPatient.CloseRecordset("CAlbumForm::CheckTempFolder");
			}

			AfterMoveEsame();
		}

		delete info.pImageListID;
	}

	m_pEsamiView->m_pImgManager->SetCurrentIDs(lPatientID, lExamID);
	if (bRefreshAlbum)
		RefreshAlbum();

	if (bError)
		return FALSE;

	// #endif

	return TRUE;
}

// Sandro 20/07/2015 //
void CAlbumForm::SelectAllImages()
{
	OnImmSelectAll();
}

// Sandro 26/11/2013 //
void CAlbumForm::SelectAlreadyPrintedImages()
{
	CFileBmp::DeleteListSelected(LOCAL_IMAGES);

	//

	m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);

	CString strDvdLabel;
	BOOL bConfirmed = m_pEsamiView->m_pImgManager->IsExamConfirmed(strDvdLabel);

	CImgIDList listIDPrinted;
	m_pEsamiView->m_pImgManager->GetPrintedImages(&listIDPrinted);

	POSITION pos1 = listIDPrinted.GetHeadPosition();
	while (pos1 != NULL)
	{
		long lImageID = listIDPrinted.GetAt(pos1);

		POSITION pos2 = m_ImgListOrgani.GetHeadPosition();
		while (pos2 != NULL)
		{
			IMG img = m_ImgListOrgani.GetAt(pos2).img;

			if (img.lID == lImageID)
			{
				CFileBmp::NewSelected(img.lID, FALSE, img.type, img.szDescription, m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore, bConfirmed, strDvdLabel, img.bCI);
				break;
			}

			m_ImgListOrgani.GetNext(pos2);
		}

		listIDPrinted.GetNext(pos1);
	}

	//

	AfterElabImage((WPARAM)FALSE, (LPARAM)0);
}

void CAlbumForm::StoreImmOnPacs()
{
	if (theApp.m_nProgramMode != NOTHING_MODE || !m_pEsamiSet->IsOpen() || m_pEsamiSet->IsBOF() || m_pEsamiSet->IsEOF())
		return;

	for (POSITION pos = CFileBmp::GetFirstSelectedPos(); pos != NULL;)
	{
		CObSelect* pSel = CFileBmp::GetNextSelected(pos);

		if ((pSel != NULL) && (pSel->m_bIsGlobal == FALSE))
			CSPInsertImgInDicomTransferQueue(&theApp.m_dbEndox).Exec(pSel->m_lID);
	}

	/* Sandro 19/11/2013 // non serve deselezionarle, si arrangia Endox //
	CFileBmp::DeleteListSelected(LOCAL_IMAGES);
	AfterMoveEsame();
	UpdateData(TRUE);
	*/
}

void CAlbumForm::FillArraySelected(CStringList* pArraySelected)
{
	pArraySelected->RemoveAll();

	POSITION pos = CFileBmp::GetFirstSelectedPos();
	while (pos != NULL)
	{
		CObSelect* pSel = CFileBmp::GetNextSelected(pos);

		if (pSel != NULL)
		{
			if (!pSel->m_bIsGlobal && ((pSel->m_iType == _image_) || (pSel->m_iType == _mptiff_)))
				pArraySelected->AddTail(m_pEsamiView->m_pImgManager->GetFullPath(pSel->m_lID));
		}
	}
}

void CAlbumForm::ControllaNormaliCI(BOOL& bRefNormali, BOOL& bRefCI)
{
	bRefNormali = FALSE;
	bRefCI = FALSE;

	POSITION pos = CFileBmp::GetFirstSelectedPos();
	while (pos != NULL)
	{
		CObSelect* pSel = CFileBmp::GetNextSelected(pos);

		if (pSel->m_bCI)
			bRefCI = TRUE;
		else
			bRefNormali = TRUE;
	}
}

void CAlbumForm::SetTimestampAcq()
{
	// se entro per la prima volta in acquisizione mi salvo il timestamp //
	if (m_pEsamiSet->m_sDataOraAcquisizione.IsEmpty())
	{
		if (m_pEsamiSet->EditRecordset("CAlbumForm::SetTimestampAcq"))
		{
			COleDateTime odtNow = COleDateTime::GetCurrentTime();

			m_pEsamiSet->m_sDataOraAcquisizione.Format("%04d%02d%02d%02d%02d%02d", odtNow.GetYear(), odtNow.GetMonth(), odtNow.GetDay(), odtNow.GetHour(), odtNow.GetMinute(), odtNow.GetSecond());
			m_pEsamiSet->UpdateRecordset("CAlbumForm::SetTimestampAcq");
		}
	}
}

void CAlbumForm::PostAcquisizione()
{
	ContaFilesPostAcquisizione(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);

	// CPostAcquisizioneDlg dlgPreview(this, m_pEsamiView);
	// if (dlgPreview.DoModal() == IDOK)
	{
		// Sandro 26/06/2013 // RAS 20130105 //

		if (theApp.m_bArchivioImmaginiThreadImport)
		{
			AfxBeginThread(AcqFromTeleImportThread, m_pEsamiView);
		}
		else
		{
			BeginWaitCursor();
			m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);

			// Simone 25/03/2010 // passo tutto il caricamento di immagini e filmati ad un thread esterno (l'acquisizione remota era troppo lenta) //
			CWaitRemoteThreadDlg waitDlg(this, m_pEsamiView, m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);
			waitDlg.DoModal();

			//
			EndWaitCursor();
			AfterMoveEsame();
		}
	}

	// Sandro 01/07/2014 //

	if (theApp.m_nApplication == PRG_ENDOX)
	{
		if (m_pEsamiSet->EditRecordset("CAlbumForm::AcqFromTele"))
		{
			m_pEsamiSet->m_lTempoRetrazione = GetPrivateProfileInt("xcap", "TempoRetrazione", 0, theApp.m_sFileConfig);
			if (m_pEsamiSet->UpdateRecordset("CAlbumForm::AcqFromTele"))
			{
				if (m_pEsamiView->m_pDynForm[edt_temporetrazione] != NULL)
					m_pEsamiView->m_pDynForm[edt_temporetrazione]->SendMessage(MSG_FORM_LOAD); // OnFormLoad //
			}
		}
	}
}

UINT CAlbumForm::AcqFromTeleImportThread(LPVOID pParam)
{
	CEsamiView* pEsamiView = (CEsamiView*)pParam;

	if (FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)))
		return 0;

	//Gabriel BUG 7768 - Continuous capture problem FIX
	if (!theApp.m_bUsaNovaCapturaContinua)
	{
		// visualizzo la barra di avanzamento //
		int nPos = 0;
		pEsamiView->SendMessage(EPM_THREAD_IMPORT_SETPOS, nPos, 0);

		// importo solo le immagini e/o filmati dell'esame corrente //
		CString strWildcard;
		strWildcard.Format("%s\\%08d_%08d_*.*",
			theApp.m_sDirTempAcq,
			pEsamiView->m_pPazientiSet->m_lContatore,
			pEsamiView->m_pEsamiSet->m_lContatore);

		//
		CStringList listPath;
		WIN32_FIND_DATA dataFile;
		HANDLE hFile = FindFirstFile(strWildcard, &dataFile);
		if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
		{
			BOOL bDBOpened = FALSE;
			CAMBaseDB tempDbEndox;

			if (theApp.m_sPassedConnectionString.IsEmpty())
				bDBOpened = tempDbEndox.OpenDirect(theApp.m_sFileConfig);
			else
				bDBOpened = tempDbEndox.OpenEx(theApp.m_sPassedConnectionString, CDatabase::noOdbcDialog); // Sandro 07/12/2015 // RIMA 15135 //

			if (bDBOpened)
			{
				// calcolo le dimensioni di tutti i files //
				double dActFileSize = 0;
				double dTotFileSize = 0;
				do
				{
					CString strFile(dataFile.cFileName);

					if (strFile.GetLength() > 3)
					{
						strFile = strFile.Right(3);
						if ((strFile.CompareNoCase("bmp") == 0) || (strFile.CompareNoCase("mpg") == 0) || (strFile.CompareNoCase("avi") == 0) || (strFile.Right(3).CompareNoCase("mp4") == 0) || (strFile.CompareNoCase("dcm") == 0))
							dTotFileSize += (double)((((LONGLONG)dataFile.nFileSizeHigh) << 32) + (LONGLONG)dataFile.nFileSizeLow) / (1024.0f * 1024.0f);
					}
				} while (FindNextFile(hFile, &dataFile));

				// 
				CImgManager tempImgManager(theApp.m_sPathImageOD, &tempDbEndox);
				if (theApp.m_nApplication == PRG_CARDIOX)
				{
					tempImgManager.SetThumbStoreSize(CSize(HSIZE_PAL / 2, VSIZE_PAL / 2));
					tempImgManager.SetThumbRetrieveSize(CSize(HSIZE_PAL / 2, VSIZE_PAL / 2));
				}
				else
				{
					tempImgManager.SetThumbStoreSize(CSize(HSIZE_PAL / 4, VSIZE_PAL / 4));
					tempImgManager.SetThumbRetrieveSize(CSize(HSIZE_PAL / 4, VSIZE_PAL / 4));
				}
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

				tempImgManager.SetCurrentIDs(pEsamiView->m_pPazientiSet->m_lContatore, pEsamiView->m_pEsamiSet->m_lContatore);

				// li importo, uno per uno //
				hFile = FindFirstFile(strWildcard, &dataFile);
				do
				{
					CString strFile(dataFile.cFileName);

					if (strFile.GetLength() > 3)
					{
						if ((strFile.Right(3).CompareNoCase("bmp") == 0) || (strFile.Right(3).CompareNoCase("mpg") == 0) || (strFile.Right(3).CompareNoCase("avi") == 0) || (strFile.Right(3).CompareNoCase("mp4") == 0) || (strFile.Right(3).CompareNoCase("dcm") == 0))
						{
							CString strAddFile = theApp.m_sDirTempAcq + "\\" + strFile;

							// controllo che la dimensione del file sia maggiore di 0 (capita per certi filmati e si blocca tutto) //

							HANDLE hFile = CreateFile(strAddFile, STANDARD_RIGHTS_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
							if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
							{
								LARGE_INTEGER llTemp;
								if (GetFileSizeEx(hFile, &llTemp))
								{
									if (llTemp.QuadPart > 0)
										listPath.AddHead(strAddFile);
									else
										DeleteFile(strAddFile);
								}
							}
							CloseHandle(hFile);

							BOOL export2Pacs = FALSE;
							// In modalità 2 devo avviare il trasferimento automatico su PACS
							if (theApp.m_lDcmStoreMode == 2)
								export2Pacs = TRUE;

							CImgIDList outputImgIdList;

							DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
							if (tempImgManager.ImportImgList(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, POINT_NONE, &listPath, FORM_IMM, FORM_MINI, &outputImgIdList, export2Pacs, FALSE, FALSE) > 0)
							{
								// importo anche il file .MIS associato //
								long lLastID = 0;

								POSITION pos = outputImgIdList.GetHeadPosition();
								if (pos)
									lLastID = outputImgIdList.GetNext(pos);

								if (lLastID > 0)
								{
									CString strLastFile = tempImgManager.GetFullPath(lLastID);

									CString strOrigMis = strAddFile.Left(strAddFile.GetLength() - 4) + ".MIS";
									if (theApp.m_nApplication != PRG_ENDOX)
									{
										CString strDestMis = strLastFile.Left(strLastFile.GetLength() - 4) + ".MIS";
										CopyFile(strOrigMis, strDestMis, FALSE);
									}

									if (DeleteFileSecure(strAddFile, strLastFile))
										DeleteFile(strOrigMis);
								}

								// aggiorno lo stato di avanzamento //
								dActFileSize += (double)((((LONGLONG)dataFile.nFileSizeHigh) << 32) + (LONGLONG)dataFile.nFileSizeLow) / (1024.0f * 1024.0f);
								nPos = (int)(((dActFileSize / dTotFileSize) * (double)100) + (double)0.5);
								pEsamiView->SendMessage(EPM_THREAD_IMPORT_SETPOS, (WPARAM)nPos, 0);
							}
							if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
								CLogFileWriter::Get()->WriteLogLine0_ImmStore(timeGetTime() - timeForLog, pEsamiView->m_pPazientiSet->m_lContatore, pEsamiView->m_pEsamiSet->m_lContatore, 1, "CAlbumForm::AcqFromTeleImportThread");

							listPath.RemoveAll();
						}
					}
				} while (FindNextFile(hFile, &dataFile));
				FindClose(hFile);
			}

			if (tempDbEndox.IsOpen())
				tempDbEndox.Close();
		}

		if (nPos < 100)
			pEsamiView->SendMessage(EPM_THREAD_IMPORT_SETPOS, (WPARAM)100, 0);

		::CoUninitialize();
	}

	if (!pEsamiView->m_bImporting)
		DeleteAllFilesOnDirectory(theApp.m_sDirTempAcq); //Gabriel BUG 7768 - Continuous capture problem


	return 0;
}

long CAlbumForm::GetSelectedCount()
{
	long lCount = 0;

	if (theApp.m_nProgramMode == NOTHING_MODE && m_pEsamiSet->IsOpen() && !m_pEsamiSet->IsBOF() && !m_pEsamiSet->IsEOF())
	{
		POSITION pos = CFileBmp::GetFirstSelectedPos();

		while (pos)
		{
			lCount++;

			CFileBmp::GetNextSelected(pos);
		}
	}

	return lCount;
}

void CAlbumForm::OnAudiologia()
{
	BeginWaitCursor();

	CString imgTempDir;
	OpenAudiologyTool(&imgTempDir);

	//Verifico, nella directory temporanea, se ci sono file
	CFileFind imgFinder;
	imgFinder.FindFile();

	BOOL bWorking = imgFinder.FindFile(imgTempDir + "\\*.*");
	while (bWorking)
	{
		bWorking = imgFinder.FindNextFile();

		if (imgFinder.IsDots())
			continue;
		if (imgFinder.IsDirectory())
			continue;

		CImgIDList imgToDeleteList;

		//Prima cancello l'eventuale immagine esistente di questo tipo
		CString imgType = imgFinder.GetFileTitle();
		CString sFilter;
		sFilter.Format("TIPO='%s'", imgType);

		CEsamiImmaginiAudiologia imgAudioSet;
		imgAudioSet.SetOpenFilter(sFilter);
		if (imgAudioSet.OpenRecordset("CAlbumForm::OpenAudiologyTool"))
		{
			while (!imgAudioSet.IsEOF())
			{
				imgToDeleteList.AddTail(imgAudioSet.m_lIDImmagine);

				imgAudioSet.DeleteRecordset("CAlbumForm::OpenAudiologyTool");

				imgAudioSet.MoveNext();
			}

			imgAudioSet.CloseRecordset("CAlbumForm::OpenAudiologyTool");
		}

		//Cancello le immagini da Endox		
		if (!imgToDeleteList.IsEmpty())
			m_pEsamiView->m_pImgManager->DelImgList(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, &imgToDeleteList);

		//Importo l'immagine
		CString strAddFile = imgFinder.GetFilePath();
		m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);
		CStringList listPath;

		USES_CONVERSION;

		//Carico la bmp
		DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
		long newImgId = 0;
		Gdiplus::Bitmap* pBitmap = (Gdiplus::Bitmap*)Gdiplus::Bitmap::FromFile(A2W(strAddFile));
		if (pBitmap->GetLastStatus() != Gdiplus::Ok)
		{
			delete pBitmap;
			theApp.AfxMessageBoxEndo("gdiplus fromHBITMAP return false");
			return;
		}

		HBITMAP hBitmap = NULL;
		pBitmap->GetHBITMAP(Gdiplus::Color(255, 255, 255), &hBitmap);
		delete pBitmap;

		//Faccio lo store
		if (m_pEsamiView->m_pImgManager->ImportImg(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, POINT_NONE, hBitmap, FORM_IMM, FORM_MINI, FALSE, &newImgId) > 0)
		{
			m_pEsamiView->m_pImgManager->UpdateImgDescription(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, newImgId, imgType);

			DeleteFile(strAddFile);
			if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
				CLogFileWriter::Get()->WriteLogLine0_ImmStore(timeGetTime() - timeForLog, m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore, 1, "CAlbumForm::AcqFromScanner");

			//Poi inserisco quella nuova
			imgAudioSet.SetOpenFilter("");
			if (imgAudioSet.OpenRecordset("CAlbumForm::OpenAudiologyTool"))
			{
				if (imgAudioSet.AddNewRecordset("CAlbumForm::OpenAudiologyTool"))
				{
					imgAudioSet.m_lIDEsame = m_pEsamiView->m_pEsamiSet->m_lContatore;
					imgAudioSet.m_lIDImmagine = newImgId;
					imgAudioSet.m_sTipo = imgType;

					imgAudioSet.UpdateRecordset("CAlbumForm::OpenAudiologyTool");
				}

				imgAudioSet.CloseRecordset("CAlbumForm::OpenAudiologyTool");
			}
		}
		else
		{
			theApp.AfxMessageBoxEndo("Immagine di tipo " + imgType + " non importata!");
		}

		DeleteFile(imgFinder.GetFilePath());
	}

	imgFinder.Close();

	//Cancello la temporanea
	RemoveDirectory(imgTempDir);

	AfterMoveEsame();

	EndWaitCursor();
}

BOOL CAlbumForm::OpenAudiologyTool(CString *tempDir)
{
	BOOL bReturn = FALSE;

	//Creazione directory temporanea
	tempDir->Format("%s\\AudiologyTool\\%08d_%08d", theApp.m_sDirProg, m_pEsamiView->m_pPazientiSet->m_lContatore, m_pEsamiView->m_pEsamiSet->m_lContatore);
	if (GetFileAttributes(*tempDir) == INVALID_FILE_ATTRIBUTES)
		CreateDirectory(*tempDir, NULL);

	//Chiamata all'exe
	CString connStr = theApp.m_dbEndox.GetDecryptedConnectionString();
	connStr.Replace("ODBC;", "");

	TCHAR szProcess[1024];
	sprintf_s(szProcess, "%s\\AudiologyTool\\Audiologia.exe %li %li \"%s\" \"%s\"", theApp.m_sDirProg, m_pEsamiView->m_pPazientiSet->m_lContatore, m_pEsamiView->m_pEsamiSet->m_lContatore, *tempDir, connStr);

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(NULL, szProcess, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi))
	{
		LPVOID lpMsgBuf;
		if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL))
			theApp.AfxMessageBoxEndo((LPCTSTR)lpMsgBuf);
		else
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_NOT_DEFINED));
		LocalFree(lpMsgBuf);
	}
	else
	{
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		bReturn = TRUE;
	}


	return bReturn;
}

//Gabriel BUG 7768 - Continuous capture problem
LRESULT CAlbumForm::AfterMoveEsameTrue(WPARAM wParam, LPARAM lParam)
{
	CFileBmp::DeleteListSelected(LOCAL_IMAGES);

	ResetVetDiapo(TRUE);

	m_nMaxDiapo = FillDiapoIndex();

	OnPageLast();

	refreshStaticComponentTotImage();	// BUG 4197 - total imagens / qtd selecionadas / OK

	return 0;
}

LRESULT CAlbumForm::AcquisitionWaiterClosing(WPARAM wParam, LPARAM lParam)
{
	m_pEsamiView->m_bImporting = FALSE;

	return 0;
}

LRESULT CAlbumForm::WaitingAutoImportClosing(WPARAM wParam, LPARAM lParam)
{
	DeleteAllFilesOnDirectory(theApp.m_sDirTempAcq);

	m_pEsamiView->m_bImporting = FALSE;

	return 0;
}

//Gabriel - BUG Refresh álbum
LRESULT CAlbumForm::RefreshAlbumMessage(WPARAM wParam, LPARAM lParam)
{
	m_nMaxDiapo = FillDiapoIndex();
	int m_nDiapoTotalPage = m_nMaxDiapo / m_nNumMaxBmp;

	for (int j = 0; j < m_nDiapoTotalPage; j++)
	{
		int nBase = j * m_nNumMaxBmp;

		for (int i = 0; i < m_nNumMaxBmp; i++)
			m_pFileBmp[i]->ResetImage();

		m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore);

		int nImages;
		CImgList listImg;
		nImages = m_pEsamiView->m_pImgManager->GetImgList(&listImg) - 1;

		m_ImgListOrgani = listImg;

		CString strDvdLabel;
		BOOL bConfirmed = m_pEsamiView->m_pImgManager->IsExamConfirmed(strDvdLabel);
		for (int i = 0; i < m_nNumMaxBmp; i++)
		{
			if (nBase + i <= m_nMaxDiapo)
			{
				m_pFileBmp[i]->LoadImage(m_pEsamiSet->m_lPaziente, m_pEsamiSet->m_lContatore, &m_ImgListOrgani, nBase + i, bConfirmed, strDvdLabel, CARICA_MINI);

				CFileBmp::ReselectBmp(m_pFileBmp[i], FALSE);
			}
			else
			{
				m_pFileBmp[i]->ResetImage();
			}
		}
	}

	MoveImage();
	UpdateData(TRUE);

	refreshStaticComponentTotImage();	// BUG 4197 - total imagens / qtd selecionadas / OK

	return 0;
}
