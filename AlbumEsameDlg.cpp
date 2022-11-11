#include "stdafx.h"
#include "Endox.h"
#include "AlbumEsameDlg.h"

#include <io.h>

#include "DLL_Imaging\h\AMLogin.h"
#include "DLL_Imaging\h\ImgManager.h"
#include "DLL_Imaging\h\AmImgBackup.h"

#include "AlbumEsameExportCdDlg.h"
#include "AlbumEsameExportHdDlg.h"
#include "AlbumEsameExportPptDlg.h"
#include "AlbumForm.h"
#include "Common.h"
#include "CustomDate.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "EspelliDlg.h"
#include "FileBmp.h"
#include "ImmaginiPuntiSet.h"
#include "LogFileWriter.h"
#include "MmSystem.h"
#include "NumberOfCopiesDlg.h"
#include "ObSelect.h"
#include "PdfManager.h"
#include "PuntiSet.h"
#include "RobotSelezioneDlg.h"
#include "TipoEsameSet.h"
#include "VistaImmaginiNumeroDermoxSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAlbumEsameDlg::CAlbumEsameDlg(CWnd* pParent, CEsamiView* pEsamiView, BOOL bAlbumPaziente)
	: CEndoxResizableDlg(CAlbumEsameDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView	= pEsamiView;

	m_nDiapoPerEsame = QUATTRO_IMMAGINI;
	m_nDiapoPage	 = 0;

	for(int i = 0; i < SEDICI_IMMAGINI; i++)
		m_pFileBmp[i] = NULL;

	m_bAlbumPaziente = bAlbumPaziente;
}

CAlbumEsameDlg::~CAlbumEsameDlg()
{
	for(int i=0; i<SEDICI_IMMAGINI; i++)
	{
		if (m_pFileBmp[i])
		{
			::DestroyWindow(m_pFileBmp[i]->GetSafeHwnd());
			delete m_pFileBmp[i];
			m_pFileBmp[i] = NULL;
		}
	}

	POSITION pos = m_ImgListOrgani.GetHeadPosition();
	while(pos != NULL)
	{
		DeleteObject(m_ImgListOrgani.GetAt(pos).img.hBmp);
		
		m_ImgListOrgani.GetNext(pos);
	}
	m_ImgListOrgani.RemoveAll();
}

void CAlbumEsameDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	//DDX_CBString(pDX, IDC_STATIC_NUM1, m_ctrlStaticNum1); // BUG 4197 - total imagens / qtd selecionadas
	DDX_Control(pDX, IDC_STATIC_NUM1, m_ctrlStaticNum1);
	DDX_Control(pDX, IDC_STATIC_NUM3, m_ctrlStaticNum3);

	DDX_Control(pDX, IDC_COMMENTO_SMALL1, m_ctrlEditCommentoSmall[0]);
	DDX_Control(pDX, IDC_COMMENTO_SMALL2, m_ctrlEditCommentoSmall[1]);
	DDX_Control(pDX, IDC_COMMENTO_SMALL3, m_ctrlEditCommentoSmall[2]);
	DDX_Control(pDX, IDC_COMMENTO_SMALL4, m_ctrlEditCommentoSmall[3]);
	DDX_Control(pDX, IDC_COMMENTO_SMALL5, m_ctrlEditCommentoSmall[4]);
	DDX_Control(pDX, IDC_COMMENTO_SMALL6, m_ctrlEditCommentoSmall[5]);
	DDX_Control(pDX, IDC_COMMENTO_SMALL7, m_ctrlEditCommentoSmall[6]);
	DDX_Control(pDX, IDC_COMMENTO_SMALL8, m_ctrlEditCommentoSmall[7]);
	DDX_Control(pDX, IDC_COMMENTO_SMALL9, m_ctrlEditCommentoSmall[8]);
	DDX_Control(pDX, IDC_COMMENTO_SMALL10, m_ctrlEditCommentoSmall[9]);
	DDX_Control(pDX, IDC_COMMENTO_SMALL11, m_ctrlEditCommentoSmall[10]);
	DDX_Control(pDX, IDC_COMMENTO_SMALL12, m_ctrlEditCommentoSmall[11]);
	DDX_Control(pDX, IDC_COMMENTO_SMALL13, m_ctrlEditCommentoSmall[12]);
	DDX_Control(pDX, IDC_COMMENTO_SMALL14, m_ctrlEditCommentoSmall[13]);
	DDX_Control(pDX, IDC_COMMENTO_SMALL15, m_ctrlEditCommentoSmall[14]);
	DDX_Control(pDX, IDC_COMMENTO_SMALL16, m_ctrlEditCommentoSmall[15]);

	DDX_Control(pDX, IDC_COMMENTO_LARGE1, m_ctrlEditCommentoLarge[0]);
	DDX_Control(pDX, IDC_COMMENTO_LARGE2, m_ctrlEditCommentoLarge[1]);
	DDX_Control(pDX, IDC_COMMENTO_LARGE3, m_ctrlEditCommentoLarge[2]);
	DDX_Control(pDX, IDC_COMMENTO_LARGE4, m_ctrlEditCommentoLarge[3]);
}

BEGIN_MESSAGE_MAP(CAlbumEsameDlg, CEndoxResizableDlg)

	ON_WM_SIZE()

	ON_BN_CLICKED(IDC_IMM_NEXT,		OnImmNext)
	ON_BN_CLICKED(IDC_IMM_PREV,		OnImmPrev)
	ON_BN_CLICKED(IDC_CHANGE_VIEW,	OnChangeView)

	ON_BN_CLICKED(IDC_BTN_CANC,		OnBnClickedCanc)
	ON_BN_CLICKED(IDC_BTN_EXP,		OnBnClickedExp)
	ON_BN_CLICKED(IDC_EXPCD,		OnBnClickedExpCD)
	ON_BN_CLICKED(IDC_EXPDVD,		OnBnClickedExpDVD)
	ON_BN_CLICKED(IDC_EXPPPT,		OnBnClickedExpPPT)
	ON_BN_CLICKED(IDC_MAIL,			OnBnClickedMail)
	// Luiz - 13/03/2019 - P3 - Inclusão de botões Seleciona tudo/Deseleciona tudo/Preview-Print
	ON_BN_CLICKED(IDC_ALBUM_IMM_SELECT, OnImmSelectAll)
	ON_BN_CLICKED(IDC_ALBUM_IMM_UNSELECT, OnImmUnselectAll)
	ON_BN_CLICKED(IDC_ALBUM_IMM_PREVIEW, OnImmPreview)
	//

	ON_MESSAGE(MSG_AFTER_CHANGECOMMENT, AfterChangeComment)
	ON_MESSAGE(MSG_AFTER_ELABIMAGE, AfterElabImage)
	ON_MESSAGE(MSG_UPDATE_SEL,		OnUpdateSel)

END_MESSAGE_MAP()

BOOL CAlbumEsameDlg::OnInitDialog()
{
	CEndoxResizableDlg::OnInitDialog();

	AddAnchor(IDC_STATIC_FRAME, CSize(100,0), CSize(100,100));
	AddAnchor(IDC_FRAME_SMALL1, CSize(0,0), CSize(25,25));
	AddAnchor(IDC_COMMENTO_SMALL1, CSize(0,25), CSize(25,25));
	AddAnchor(IDC_FRAME_SMALL2, CSize(25,0), CSize(50,25));
	AddAnchor(IDC_COMMENTO_SMALL2, CSize(25,25), CSize(50,25));
	AddAnchor(IDC_FRAME_SMALL3, CSize(50,0), CSize(75,25));
	AddAnchor(IDC_COMMENTO_SMALL3, CSize(50,25), CSize(75,25));
	AddAnchor(IDC_FRAME_SMALL4, CSize(75,0), CSize(100,25));
	AddAnchor(IDC_COMMENTO_SMALL4, CSize(75,25), CSize(100,25));
	AddAnchor(IDC_FRAME_SMALL5, CSize(0,25), CSize(25,50));
	AddAnchor(IDC_COMMENTO_SMALL5, CSize(0,50), CSize(25,50));
	AddAnchor(IDC_FRAME_SMALL6, CSize(25,25), CSize(50,50));
	AddAnchor(IDC_COMMENTO_SMALL6, CSize(25,50), CSize(50,50));
	AddAnchor(IDC_FRAME_SMALL7, CSize(50,25), CSize(75,50));
	AddAnchor(IDC_COMMENTO_SMALL7, CSize(50,50), CSize(75,50));
	AddAnchor(IDC_FRAME_SMALL8, CSize(75,25), CSize(100,50));
	AddAnchor(IDC_COMMENTO_SMALL8, CSize(75,50), CSize(100,50));
	AddAnchor(IDC_FRAME_SMALL9, CSize(0,50), CSize(25,75));
	AddAnchor(IDC_COMMENTO_SMALL9, CSize(0,75), CSize(25,75));
	AddAnchor(IDC_FRAME_SMALL10, CSize(25,50), CSize(50,75));
	AddAnchor(IDC_COMMENTO_SMALL10, CSize(25,75), CSize(50,75));
	AddAnchor(IDC_FRAME_SMALL11, CSize(50,50), CSize(75,75));
	AddAnchor(IDC_COMMENTO_SMALL11, CSize(50,75), CSize(75,75));
	AddAnchor(IDC_FRAME_SMALL12, CSize(75,50), CSize(100,75));
	AddAnchor(IDC_COMMENTO_SMALL12, CSize(75,75), CSize(100,75));
	AddAnchor(IDC_FRAME_SMALL13, CSize(0,75), CSize(25,100));
	AddAnchor(IDC_COMMENTO_SMALL13, CSize(0,100), CSize(25,100));
	AddAnchor(IDC_FRAME_SMALL14, CSize(25,75), CSize(50,100));
	AddAnchor(IDC_COMMENTO_SMALL14, CSize(25,100), CSize(50,100));
	AddAnchor(IDC_FRAME_SMALL15, CSize(50,75), CSize(75,100));
	AddAnchor(IDC_COMMENTO_SMALL15, CSize(50,100), CSize(75,100));
	AddAnchor(IDC_FRAME_SMALL16, CSize(75,75), CSize(100,100));
	AddAnchor(IDC_COMMENTO_SMALL16, CSize(75,100), CSize(100,100));
	AddAnchor(IDC_FRAME_LARGE1, CSize(0,0), CSize(50,50));
	AddAnchor(IDC_COMMENTO_LARGE1, CSize(0,50), CSize(50,50));
	AddAnchor(IDC_FRAME_LARGE2, CSize(50,0), CSize(100,50));
	AddAnchor(IDC_COMMENTO_LARGE2, CSize(50,50), CSize(100,50));
	AddAnchor(IDC_FRAME_LARGE3, CSize(0,50), CSize(50,100));
	AddAnchor(IDC_COMMENTO_LARGE3, CSize(0,100), CSize(50,100));
	AddAnchor(IDC_FRAME_LARGE4, CSize(50,50), CSize(100,100));
	AddAnchor(IDC_COMMENTO_LARGE4, CSize(50,100), CSize(100,100));
	AddAnchor(IDC_STATIC_NUM1, CSize(100,0), CSize(100,0));
	AddAnchor(IDC_STATIC_NUM2, CSize(100,0), CSize(100,0));
	AddAnchor(IDC_STATIC_LINE1, CSize(100,0), CSize(100,0));
	AddAnchor(IDC_STATIC_NUM3, CSize(100,0), CSize(100,0));
	AddAnchor(IDC_STATIC_NUM4, CSize(100,0), CSize(100,0));
	AddAnchor(IDC_STATIC_LINE8, CSize(100,0), CSize(100,0));
	AddAnchor(IDC_CHANGE_VIEW, CSize(100,0), CSize(100,0));
	AddAnchor(IDC_STATIC_LINE2, CSize(100,0), CSize(100,0));
	AddAnchor(IDC_BTN_EXP, CSize(100,0), CSize(100,0));
	AddAnchor(IDC_EXPCD, CSize(100,0), CSize(100,0));
	AddAnchor(IDC_EXPDVD, CSize(100,0), CSize(100,0));
	AddAnchor(IDC_EXPPPT, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_MAIL, CSize(100, 0), CSize(100, 0));
	// Luiz - 13/03/2019 - P3 - Inclusão de botões Seleciona tudo/Deseleciona tudo/Preview-Print
	AddAnchor(IDC_ALBUM_IMM_SELECT, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_ALBUM_IMM_UNSELECT, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_ALBUM_IMM_PREVIEW, CSize(100, 0), CSize(100, 0));
	AddAnchor(IDC_STATIC_LINE7, CSize(100, 0), CSize(100, 0));

	AddAnchor(IDC_STATIC_LINE3, CSize(100,0), CSize(100,0));
	AddAnchor(IDC_IMM_PREV, CSize(100,0), CSize(100,0));
	AddAnchor(IDC_IMM_NEXT, CSize(100,0), CSize(100,0));
	AddAnchor(IDC_STATIC_LINE4, CSize(100,0), CSize(100,0));
	AddAnchor(IDC_STATIC_LINE5, CSize(100,0), CSize(100,0));
	AddAnchor(IDC_BTN_CANC, CSize(100,0), CSize(100,0));
	// AddAnchor(IDC_STATIC_LINE7, CSize(100,0), CSize(100,0));
	AddAnchor(IDC_STATIC_LINE6, CSize(100,100), CSize(100,100));
	// Luiz - 19/02/2019 - P3 - Ajuste do Form para monitores de baixa resolução
	AddAnchor(IDOK, CSize(100, 0), CSize(100, 0));

	m_BtnImmPrev.AutoLoad(IDC_IMM_PREV, this);
	m_BtnImmNext.AutoLoad(IDC_IMM_NEXT, this);

	m_BtnChangeView.AutoLoad(IDC_CHANGE_VIEW, this);
	m_BtnExportCD.AutoLoad(IDC_EXPCD, this);
	m_BtnExportDVD.AutoLoad(IDC_EXPDVD, this);
	m_BtnExportPPT.AutoLoad(IDC_EXPPPT, this);
	m_BtnSendMail.AutoLoad(IDC_MAIL, this);
	
	// Luiz - 13/03/2019 - P3 - Inclusão de botões Seleciona tudo/Deseleciona tudo/Preview-Print
	m_BtnSelectAll.AutoLoad(IDC_ALBUM_IMM_SELECT, this);
	m_BtnDeselectAll.AutoLoad(IDC_ALBUM_IMM_UNSELECT, this);
	m_BtnImagePreview.AutoLoad(IDC_ALBUM_IMM_PREVIEW, this);

	m_btnExp.AutoLoad(IDC_BTN_EXP, this);
	m_btnCanc.AutoLoad(IDC_BTN_CANC, this);	
	m_btnEsci.AutoLoad(IDOK, this);

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	OnChangeView();

	AfterElabImage((WPARAM)FALSE, 0);

	CFileBmp::SendUpdateMessage();

	m_btnExp.EnableWindow((theApp.m_dwPrivileges & AMLogin_Permissions::exportout) && m_pEsamiView->m_pEsamiSet->m_bStessoDistretto);
	m_BtnExportCD.EnableWindow(!m_pEsamiView->m_bBurning && (theApp.m_dwPrivileges & AMLogin_Permissions::exportout) && (theApp.m_bCanWriteCD || theApp.m_bRobotAttivo) && m_pEsamiView->m_pEsamiSet->m_bStessoDistretto);
	m_BtnExportDVD.EnableWindow(!m_pEsamiView->m_bBurning && (theApp.m_dwPrivileges & AMLogin_Permissions::exportout) && (theApp.m_bCanWriteDVD || theApp.m_bRobotAttivo) && m_pEsamiView->m_pEsamiSet->m_bStessoDistretto);
	m_BtnExportPPT.EnableWindow((theApp.m_dwPrivileges & AMLogin_Permissions::exportout) && m_pEsamiView->m_pEsamiSet->m_bStessoDistretto);
	m_BtnSendMail.EnableWindow((theApp.m_dwPrivileges & AMLogin_Permissions::exportout) && m_pEsamiView->m_pEsamiSet->m_bStessoDistretto);
	m_btnCanc.EnableWindow((theApp.m_dwPrivileges & AMLogin_Permissions::modify_image) && m_pEsamiView->m_pEsamiSet->m_bStessoDistretto && !m_pEsamiView->m_pEsamiSet->m_bLocked && !m_pEsamiView->m_pEsamiSet->m_bSuperLocked);

	theApp.LocalizeDialog(this, CAlbumEsameDlg::IDD, "AlbumEsameDlg");

	if (m_bAlbumPaziente)
		SetWindowText(theApp.GetMessageString(IDS_ALBUM_PAZIENTE));
	else
		SetWindowText(theApp.GetMessageString(IDS_ALBUM_ESAME));

	return TRUE;
}

LRESULT CAlbumEsameDlg::OnUpdateSel(WPARAM wParam, LPARAM lParam)
{
	int iTotImgSelected = (int)wParam;
	SetDlgItemInt(IDC_STATIC_NUM2, (iTotImgSelected<0 ? 0 : iTotImgSelected));

	BOOL bConfirmed = FALSE;
	double dKb = 0;

	BOOL bOnlyFilms = TRUE;
	int nFoundFilms = 0;

	POSITION pos = CFileBmp::GetFirstSelectedPos();
	while(pos != NULL)
	{
		CObSelect* pSel = CFileBmp::GetNextSelected(pos);
		if (pSel != NULL)
		{
			if (!pSel->m_bIsGlobal)
			{
				if (!bConfirmed)
				{
					if (pSel->m_bConfirmed)
					{
						bConfirmed = TRUE;
					}
					else
					{
						LARGE_INTEGER llTemp;
						CString strFile = m_pEsamiView->m_pImgManager->GetFullPath(pSel->m_lID);
						HANDLE hFile = CreateFile(strFile, STANDARD_RIGHTS_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
						if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
						{
							if (GetFileSizeEx(hFile, &llTemp) != 0)
								dKb += ((double)llTemp.QuadPart / (double)1024.0f);
						}
						CloseHandle(hFile);
					}
				}
			}
		}
	}
	CString strDim = "-";
	if ((!bConfirmed) && (dKb > (double)0.0f))
	{
		if (dKb > (double)1024.0f)
		{
			dKb /= (double)1024.0f;
			if (dKb > (double)1024.0f)
			{
				dKb /= (double)1024.0f;
				strDim.Format("%.3lf Gb", dKb);
			}
			else
			{
				strDim.Format("%.2lf Mb", dKb);
			}
		}
		else
		{
			strDim.Format("%.1lf Kb", dKb);
		}
	}
	SetDlgItemText(IDC_STATIC_NUM4, strDim);

	pos = CFileBmp::GetFirstSelectedPos();
	while(pos != NULL)
	{
		CObSelect* pSel = CFileBmp::GetNextSelected(pos);
		
		if (pSel != NULL)
		{
			if (!pSel->m_bIsGlobal)
			{
				if (pSel->m_iType != _movie_)
				{
					bOnlyFilms = FALSE;
					break;
				}
				nFoundFilms++;
			}
		}
	}
	if (nFoundFilms == 0)
		bOnlyFilms = FALSE;

	return 0;
}

void CAlbumEsameDlg::ResetVetDiapo(BOOL bReposition)
{   
	m_ImgListOrgani.RemoveAll(); // <-- fa tutto questa //

	if (bReposition)
	{
		m_nMaxDiapo		= 0;
		m_nDiapoPage	= -1;
	}
}  	

int CAlbumEsameDlg::FillDiapoIndex()
{
	int nImages;
	CImgList listImg;

	BeginWaitCursor();
	
	// Se è l'album paziente carico le immagini dell'esame 90000000 + idPaziente
	if (m_bAlbumPaziente)
		m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiView->m_pPazientiSet->m_lContatore, 90000000 + m_pEsamiView->m_pPazientiSet->m_lContatore);
	else
		m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore);

	DWORD timeForLog = timeGetTime(); // Sandro 16/07/2014 //
	nImages = m_pEsamiView->m_pImgManager->GetImgList(&listImg) - 1;
	if (theApp.m_bSaveCompleteLog) // Sandro 16/07/2014 //
	{
		if (m_bAlbumPaziente)
			CLogFileWriter::Get()->WriteLogLine0_ImmRetrieve(timeGetTime() - timeForLog, m_pEsamiView->m_pPazientiSet->m_lContatore, 90000000 + m_pEsamiView->m_pPazientiSet->m_lContatore, nImages + 1, "CAlbumEsameDlg::FillDiapoIndex");
		else
			CLogFileWriter::Get()->WriteLogLine0_ImmRetrieve(timeGetTime() - timeForLog, m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore, nImages + 1, "CAlbumEsameDlg::FillDiapoIndex");
	}

	m_ImgListOrgani = listImg;
	CaricaPunti();
	EndWaitCursor();

	return nImages;
}

void CAlbumEsameDlg::MoveImage()
{
	int nBase = m_nDiapoPage * m_nDiapoPerEsame;

	m_BtnImmPrev.EnableWindow(m_nDiapoPage > 0);
	m_BtnImmNext.EnableWindow(m_nDiapoPage < (m_nMaxDiapo / m_nDiapoPerEsame));

	if (!m_bAlbumPaziente && m_pEsamiView->m_pEsamiSet->IsEOF())
	{
		for(int i = 0; i < m_nDiapoPerEsame; i++)
			m_pFileBmp[i]->ResetImage();

		return;	
	}		

	long lPaziente;
	long lEsame;
	CString strDvdLabel;
	BOOL bConfirmed = m_pEsamiView->m_pImgManager->IsExamConfirmed(strDvdLabel);
	m_pEsamiView->m_pImgManager->GetCurrentIDs(lPaziente, lEsame);
	for(int i = 0; i < m_nDiapoPerEsame; i++)
	{
		if (nBase + i <= m_nMaxDiapo)
		{
			if (m_nDiapoPerEsame != SEDICI_IMMAGINI)
			{
				if (!bConfirmed)
				{
					m_pFileBmp[i]->LoadImage(lPaziente, lEsame, &m_ImgListOrgani, nBase + i, bConfirmed, strDvdLabel, CARICA_IMM);
				}
				else
				{
					BOOL bDvd = TRUE;

					while(GetVolumeName() != strDvdLabel)
					{
						CEspelliDlg	dlg(this, strDvdLabel);

						if (dlg.DoModal() == IDCANCEL)
						{
							m_pFileBmp[i]->LoadImage(lPaziente, lEsame, &m_ImgListOrgani, nBase + i, bConfirmed, strDvdLabel, CARICA_MINI);
							bDvd = FALSE;
							break;
						}
					}

					if (bDvd)
						m_pFileBmp[i]->LoadImage(lPaziente, lEsame, &m_ImgListOrgani, nBase + i, bConfirmed, strDvdLabel, CARICA_IMM);
				}
			}
			else
			{
				m_pFileBmp[i]->LoadImage(lPaziente, lEsame, &m_ImgListOrgani, nBase + i, bConfirmed, strDvdLabel, CARICA_MINI);
			}

			CFileBmp::ReselectBmp(m_pFileBmp[i], FALSE);
		}
		else
		{
			m_pFileBmp[i]->ResetImage();
		}
	}
}

void CAlbumEsameDlg::OnImmPrev() 
{
    if (m_nDiapoPage == 0)
    	return;

    m_nDiapoPage--;
	MoveImage();
}

void CAlbumEsameDlg::OnImmNext() 
{
	if (m_nDiapoPage == (m_nMaxDiapo / m_nDiapoPerEsame))
		return;

	m_nDiapoPage++;
	MoveImage();
}

//Luiz - 13/03/2019 - P3 - Inclusão de botões Seleciona tudo/Deseleção/Preview-Print
void CAlbumEsameDlg::OnImmSelectAll()
{
	CFileBmp::DeleteListSelected(LOCAL_IMAGES);
	m_pEsamiView->m_pImgManager->SetCurrentIDs(m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore);

	CString strDvdLabel;
	BOOL bConfirmed = m_pEsamiView->m_pImgManager->IsExamConfirmed(strDvdLabel);

	POSITION pos = m_ImgListOrgani.GetHeadPosition();
	while (pos != NULL)
	{
		IMG img = m_ImgListOrgani.GetAt(pos).img;

		CFileBmp::NewSelected(img.lID, FALSE, img.type, img.szDescription, m_pEsamiView->m_pEsamiSet->m_lPaziente, m_pEsamiView->m_pEsamiSet->m_lContatore, bConfirmed, strDvdLabel, img.bCI);

		m_ImgListOrgani.GetNext(pos);
	}
	AfterElabImage((WPARAM)FALSE, (LPARAM)0);
}

void CAlbumEsameDlg::OnImmUnselectAll()
{
	AfterElabImage((WPARAM)TRUE, (LPARAM)0); // <-- con il TRUE ci pensa già lui a deselezionare tutte le immagini //
}

void CAlbumEsameDlg::OnImmPreview()
{
	BOOL bStampa = TRUE;

	CString sMessaggio = "";
	if (theApp.m_bPersonalizzazioniBrasileFleury)
		bStampa = FleuryPossoStampare(sMessaggio, m_pEsamiView->m_pEsamiSet->m_sRicovero, m_pEsamiView->m_pEsamiSet->m_sCodEsame);

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

void CAlbumEsameDlg::OnChangeView() 
{
	CString strTitle;

	if (m_nDiapoPerEsame == SEDICI_IMMAGINI)
	{
		m_nDiapoPerEsame = QUATTRO_IMMAGINI;
		strTitle	= "Alb16_";
	}
	else
	{
		m_nDiapoPerEsame = SEDICI_IMMAGINI;
		strTitle	= "Alb4_";
	}

	m_BtnChangeView.SetWindowText(strTitle);
	m_BtnChangeView.LoadBitmaps(strTitle + "U", strTitle + "D", strTitle + "F", strTitle + "X");
	m_BtnChangeView.SizeToContent();
	m_BtnChangeView.Invalidate();

	ResetVetDiapo(TRUE);

	for(int j = 0; j < SEDICI_IMMAGINI; j++)
	{
		if (m_pFileBmp[j])
		{
			::DestroyWindow(m_pFileBmp[j]->GetSafeHwnd());
			delete m_pFileBmp[j];
			m_pFileBmp[j] = NULL;
		}
	}

	CWnd* pBmpFrame[SEDICI_IMMAGINI];
	
	if (m_nDiapoPerEsame == SEDICI_IMMAGINI)
	{
		GetDlgItem(IDC_FRAME_LARGE1)->ShowWindow(SW_HIDE);
		m_ctrlEditCommentoLarge[0].ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_LARGE2)->ShowWindow(SW_HIDE);
		m_ctrlEditCommentoLarge[1].ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_LARGE3)->ShowWindow(SW_HIDE);
		m_ctrlEditCommentoLarge[2].ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_LARGE4)->ShowWindow(SW_HIDE);
		m_ctrlEditCommentoLarge[3].ShowWindow(SW_HIDE);

		GetDlgItem(IDC_FRAME_SMALL1)->ShowWindow(SW_SHOW);
		m_ctrlEditCommentoSmall[0].ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_SMALL2)->ShowWindow(SW_SHOW);
		m_ctrlEditCommentoSmall[1].ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_SMALL3)->ShowWindow(SW_SHOW);
		m_ctrlEditCommentoSmall[2].ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_SMALL4)->ShowWindow(SW_SHOW);
		m_ctrlEditCommentoSmall[3].ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_SMALL5)->ShowWindow(SW_SHOW);
		m_ctrlEditCommentoSmall[4].ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_SMALL6)->ShowWindow(SW_SHOW);
		m_ctrlEditCommentoSmall[5].ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_SMALL7)->ShowWindow(SW_SHOW);
		m_ctrlEditCommentoSmall[6].ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_SMALL8)->ShowWindow(SW_SHOW);
		m_ctrlEditCommentoSmall[7].ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_SMALL9)->ShowWindow(SW_SHOW);
		m_ctrlEditCommentoSmall[8].ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_SMALL10)->ShowWindow(SW_SHOW);
		m_ctrlEditCommentoSmall[9].ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_SMALL11)->ShowWindow(SW_SHOW);
		m_ctrlEditCommentoSmall[10].ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_SMALL12)->ShowWindow(SW_SHOW);
		m_ctrlEditCommentoSmall[11].ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_SMALL13)->ShowWindow(SW_SHOW);
		m_ctrlEditCommentoSmall[12].ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_SMALL14)->ShowWindow(SW_SHOW);
		m_ctrlEditCommentoSmall[13].ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_SMALL15)->ShowWindow(SW_SHOW);
		m_ctrlEditCommentoSmall[14].ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_SMALL16)->ShowWindow(SW_SHOW);
		m_ctrlEditCommentoSmall[15].ShowWindow(SW_SHOW);

		pBmpFrame[0] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL1);
		pBmpFrame[1] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL2);
		pBmpFrame[2] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL3);
		pBmpFrame[3] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL4);
		pBmpFrame[4] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL5);
		pBmpFrame[5] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL6);
		pBmpFrame[6] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL7);
		pBmpFrame[7] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL8);
		pBmpFrame[8] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL9);
		pBmpFrame[9] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL10);
		pBmpFrame[10] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL11);
		pBmpFrame[11] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL12);
		pBmpFrame[12] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL13);
		pBmpFrame[13] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL14);
		pBmpFrame[14] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL15);
		pBmpFrame[15] = (CWnd*)GetDlgItem(IDC_FRAME_SMALL16);
	}
	else
	{
		GetDlgItem(IDC_FRAME_SMALL1)->ShowWindow(SW_HIDE);
		m_ctrlEditCommentoSmall[0].ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL2)->ShowWindow(SW_HIDE);
		m_ctrlEditCommentoSmall[1].ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL3)->ShowWindow(SW_HIDE);
		m_ctrlEditCommentoSmall[2].ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL4)->ShowWindow(SW_HIDE);
		m_ctrlEditCommentoSmall[3].ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL5)->ShowWindow(SW_HIDE);
		m_ctrlEditCommentoSmall[4].ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL6)->ShowWindow(SW_HIDE);
		m_ctrlEditCommentoSmall[5].ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL7)->ShowWindow(SW_HIDE);
		m_ctrlEditCommentoSmall[6].ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL8)->ShowWindow(SW_HIDE);
		m_ctrlEditCommentoSmall[7].ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL9)->ShowWindow(SW_HIDE);
		m_ctrlEditCommentoSmall[8].ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL10)->ShowWindow(SW_HIDE);
		m_ctrlEditCommentoSmall[9].ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL11)->ShowWindow(SW_HIDE);
		m_ctrlEditCommentoSmall[10].ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL12)->ShowWindow(SW_HIDE);
		m_ctrlEditCommentoSmall[11].ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL13)->ShowWindow(SW_HIDE);
		m_ctrlEditCommentoSmall[12].ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL14)->ShowWindow(SW_HIDE);
		m_ctrlEditCommentoSmall[13].ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL15)->ShowWindow(SW_HIDE);
		m_ctrlEditCommentoSmall[14].ShowWindow(SW_HIDE);
		GetDlgItem(IDC_FRAME_SMALL16)->ShowWindow(SW_HIDE);
		m_ctrlEditCommentoSmall[15].ShowWindow(SW_HIDE);

		GetDlgItem(IDC_FRAME_LARGE1)->ShowWindow(SW_SHOW);
		m_ctrlEditCommentoLarge[0].ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_LARGE2)->ShowWindow(SW_SHOW);
		m_ctrlEditCommentoLarge[1].ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_LARGE3)->ShowWindow(SW_SHOW);
		m_ctrlEditCommentoLarge[2].ShowWindow(SW_SHOW);
		GetDlgItem(IDC_FRAME_LARGE4)->ShowWindow(SW_SHOW);
		m_ctrlEditCommentoLarge[3].ShowWindow(SW_SHOW);

		pBmpFrame[0] = (CWnd*)GetDlgItem(IDC_FRAME_LARGE1);
		pBmpFrame[1] = (CWnd*)GetDlgItem(IDC_FRAME_LARGE2);
		pBmpFrame[2] = (CWnd*)GetDlgItem(IDC_FRAME_LARGE3);
		pBmpFrame[3] = (CWnd*)GetDlgItem(IDC_FRAME_LARGE4);
		pBmpFrame[4] = NULL;
		pBmpFrame[5] = NULL;
		pBmpFrame[6] = NULL;
		pBmpFrame[7] = NULL;
		pBmpFrame[8] = NULL;
		pBmpFrame[9] = NULL;
		pBmpFrame[10] = NULL;
		pBmpFrame[11] = NULL;
		pBmpFrame[12] = NULL;
		pBmpFrame[13] = NULL;
		pBmpFrame[14] = NULL;
		pBmpFrame[15] = NULL;
	}

	for(int j = 0; j < m_nDiapoPerEsame; j++)
	{
		if (pBmpFrame[j])
		{
			if (CFileBmp::CreateBmp(m_pEsamiView, this, pBmpFrame[j], &m_pFileBmp[j]))
			{
				m_pFileBmp[j]->SetMouseMode(BMP_L_NORMALMODE, BMP_R_NORMALMODE);
				m_pFileBmp[j]->SetAlbumType(FALSE); 
				m_pFileBmp[j]->ShowWindow(TRUE);

				if (m_nDiapoPerEsame == SEDICI_IMMAGINI)
					m_pFileBmp[j]->AssignEdit(&m_ctrlEditCommentoSmall[j]);
				else if (m_nDiapoPerEsame == QUATTRO_IMMAGINI)
					m_pFileBmp[j]->AssignEdit(&m_ctrlEditCommentoLarge[j]);
			}
		}
	}

	m_nMaxDiapo = FillDiapoIndex();
	m_nDiapoPage = 0;

	MoveImage();
}

LRESULT CAlbumEsameDlg::AfterChangeComment(WPARAM wParam, LPARAM lParam)
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

LRESULT CAlbumEsameDlg::AfterElabImage(WPARAM wParam, LPARAM lParam)
{   
	if ((BOOL)wParam)
		CFileBmp::DeleteListSelected(LOCAL_IMAGES);  

	ResetVetDiapo(FALSE);

	m_nMaxDiapo = FillDiapoIndex();

	MoveImage();

	return 1;
}

void CAlbumEsameDlg::OnBnClickedExp()
{
	//Julio 02/05/2018 centralizacao Fleury tras todas as imagens que faltam
	if (theApp.m_bPersonalizzazioniBrasileFleury || theApp.m_lRicercaCodiceEsame == 4)
	{
		FleuryGetImagensAltraSede(this, m_pEsamiView);
	}

	int iNumSel = GetDlgItemInt(IDC_STATIC_NUM2);
	CString strTitle = theApp.GetMessageString(IDS_FOLDERDLG_TITLE_1);
	CFolderDialog dlg(strTitle, theApp.m_sExportFolder, 0x0040, this);

	if (iNumSel <= 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUMESAME_ERR_SEL));
		return;
	}

	if (dlg.DoModal() == IDOK)
	{
		CString strTemp = dlg.GetSelectedFolder();
		if (strTemp.Right(1) != "\\")
			strTemp += "\\";

		if (strTemp != theApp.m_sExportFolder)
		{
			theApp.m_sExportFolder = strTemp;
			WritePrivateProfileString(szPercorsi, szExportFolder, theApp.m_sExportFolder, theApp.m_sFileConfig);
		}

		strTemp.Format(theApp.GetMessageString(IDS_ALBUMESAME_EXP_IMG), iNumSel, theApp.m_sExportFolder);
		if (theApp.AfxMessageBoxEndo(strTemp, MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			CAlbumEsameExportHdDlg dlg(this, m_pEsamiView, iNumSel);
			dlg.DoModal();

			if (theApp.m_bAutoDeselect)
			{
				CFileBmp::DeleteListSelected(LOCAL_IMAGES);
				MoveImage();
			}
		}
	}
}

void CAlbumEsameDlg::OnBnClickedExpCD()
{
	//Julio 02/05/2018 centralizacao Fleury tras todas as imagens que faltam
	if (theApp.m_bPersonalizzazioniBrasileFleury || theApp.m_lRicercaCodiceEsame == 4)
	{
		FleuryGetImagensAltraSede(this, m_pEsamiView);
	}

	CString strTemp;
	int iNumSel = GetDlgItemInt(IDC_STATIC_NUM2);

	if (iNumSel <= 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUMESAME_ERR_SEL));
		return;
	}

	strTemp.Format(theApp.GetMessageString(IDS_DOCUMENTI_ESPORTARE_CD), iNumSel);
	if (theApp.AfxMessageBoxEndo(strTemp, MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		if (theApp.m_bRobotAttivo)
		{
			if (theApp.m_bCanWriteCD)
			{
				if (theApp.AfxMessageBoxEndo("Utilizzare la masterizzazione tramite RIMAGE?", MB_YESNO) == IDYES)
				{		
					RimageBurning(discType::TYPE_CD, iNumSel);
					OnOK();
				}				
				else
				{
					CAlbumEsameExportCdDlg dlg(this, m_pEsamiView, iNumSel, DISC_CD);
					dlg.DoModal();
				}
			}
			else
			{
				RimageBurning(discType::TYPE_CD, iNumSel);		
				OnOK();
			}
		}
		else
		{
			//caso rimage non attivo
			if (theApp.m_bCanWriteCD)
			{
				CAlbumEsameExportCdDlg dlg(this, m_pEsamiView, iNumSel, DISC_CD);
				dlg.DoModal();				
			}
		}

		if (theApp.m_bAutoDeselect)
		{
			CFileBmp::DeleteListSelected(LOCAL_IMAGES);
			MoveImage();
		}
	}
}

void CAlbumEsameDlg::OnBnClickedExpDVD()
{
	//Julio 02/05/2018 centralizacao Fleury tras todas as imagens que faltam
	if (theApp.m_bPersonalizzazioniBrasileFleury || theApp.m_lRicercaCodiceEsame == 4)
	{
		FleuryGetImagensAltraSede(this, m_pEsamiView);
	}

	CString strTemp;
	int iNumSel = GetDlgItemInt(IDC_STATIC_NUM2);

	if (iNumSel <= 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUMESAME_ERR_SEL));
		return;
	}

	strTemp.Format(theApp.GetMessageString(IDS_DOCUMENTI_ESPORTARE_DVD), iNumSel);
	if (theApp.AfxMessageBoxEndo(strTemp, MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		if (theApp.m_bRobotAttivo)
		{
			if (theApp.m_bCanWriteDVD)
			{
				if (theApp.AfxMessageBoxEndo("Utilizzare la masterizzazione tramite RIMAGE?", MB_YESNO) == IDYES)
				{		
					RimageBurning(discType::TYPE_DVD, iNumSel);
					OnOK();
				}				
				else
				{
					CAlbumEsameExportCdDlg dlg(this, m_pEsamiView, iNumSel, DISC_DVD);
					dlg.DoModal();
				}
			}
			else
			{
				RimageBurning(discType::TYPE_DVD, iNumSel);
				OnOK();
			}
		}
		else
		{
			//caso rimage non attivo
			if (theApp.m_bCanWriteDVD)
			{
				CAlbumEsameExportCdDlg dlg(this, m_pEsamiView, iNumSel, DISC_DVD);
				dlg.DoModal();				
			}
		}		

		if (theApp.m_bAutoDeselect)
		{
			CFileBmp::DeleteListSelected(LOCAL_IMAGES);
			MoveImage();
		}
	}
}

// Sandro Gallina - 09/11/2015 //
void CAlbumEsameDlg::OnBnClickedExpPPT()
{
	//Julio 02/05/2018 centralizacao Fleury tras todas as imagens que faltam
	if (theApp.m_bPersonalizzazioniBrasileFleury || theApp.m_lRicercaCodiceEsame == 4)
	{
		FleuryGetImagensAltraSede(this, m_pEsamiView);
	}

	DeleteDirectory(theApp.m_sDirTemp + "\\PPT");

	int iNumSel = GetDlgItemInt(IDC_STATIC_NUM2);
	if (iNumSel <= 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUMESAME_ERR_SEL));
		return;
	}
	else
	{
		CString sMessage;
		sMessage.Format(theApp.GetMessageString(IDS_EXPORTDLG_CONFERMAPPT), iNumSel);
		if (theApp.AfxMessageBoxEndo(sMessage, MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			CFileDialog FileDlg(FALSE, NULL, NULL, OFN_READONLY | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, "File Microsoft PowerPoint (*.pptx)|*.pptx|", this, 0, FALSE);
			if (FileDlg.DoModal() == IDOK)
			{
				CString sFileExport = FileDlg.GetPathName();
				if (sFileExport.Right(4).CompareNoCase(".pptx") != 0)
					sFileExport += ".pptx";

				CAlbumEsameExportPptDlg dlg(this, m_pEsamiView, iNumSel);
				dlg.DoModal();

				if (_access(theApp.m_sDirTemp + "\\PPT", 06) == 0)
				{
					CString sImageFiles = "";

					CString strWildcard;
					strWildcard.Format("%s\\PPT\\*.bmp", theApp.m_sDirTemp);

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
								CString strAddFile = "\"" + theApp.m_sDirTemp + "\\PPT\\" + strFile + "\"";

								if (!sImageFiles.IsEmpty())
									sImageFiles += " ";
								sImageFiles += strAddFile;

								listPath.RemoveAll();
							}
						} while (FindNextFile(hFile, &dataFile));
						FindClose(hFile);
					}

					if (!sImageFiles.IsEmpty())
					{
						char szProcess[256 * 256];
						sprintf_s(szProcess, "\"%s\\PowerPointCreator.exe\" \"%s\" \"image/bmp\" %s", theApp.m_sDirProg, sFileExport, sImageFiles);

						STARTUPINFO si;
						PROCESS_INFORMATION pi;

						ZeroMemory(&si, sizeof(si));
						si.cb = sizeof(si);
						ZeroMemory(&pi, sizeof(pi));

						BeginWaitCursor();
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

#ifdef _DEBUG
							ShellExecute(NULL, "open", sFileExport, NULL, NULL, SW_SHOWMAXIMIZED);
#endif
						}
						EndWaitCursor();
					}
				}

				if (_access(sFileExport, 00) == 0)
					theApp.AfxMessageBoxEndo(IDS_ALBUMESAME_EXP_IMG_OK);
			}
		}
	}

	DeleteDirectory(theApp.m_sDirTemp + "\\PPT");
}

void CAlbumEsameDlg::OnBnClickedMail()
{
	//Julio 02/05/2018 centralizacao Fleury tras todas as imagens que faltam
	if (theApp.m_bPersonalizzazioniBrasileFleury || theApp.m_lRicercaCodiceEsame == 4)
	{
		FleuryGetImagensAltraSede(this, m_pEsamiView);
	}

	CStringList listAttachedFiles;

	BeginWaitCursor();

	// PDF //

	CPdfManager PdfManager;
	if (!PdfManager.IsInitialize())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_PDFMANAGER_ERROR));
		return;
	}

	CPdfList listPdf;
	PdfManager.GetPdf(m_pEsamiView->m_pEsamiSet->m_lContatore, &listPdf);

	POSITION pos1 = listPdf.GetTailPosition();
	while(pos1 != NULL)
	{
		PDF pdf = listPdf.GetPrev(pos1);
		if (pdf.ptTipo == pdftype_report)
		{
			if (strcmp(pdf.szNote, "TODELETE") != 0)
			{
				if (_access(pdf.szFile, 00) == 0)
				{
					CString strPdfArchive(pdf.szFile);

					// Sandro 04/12/2014 // rinomino i P7M in "semplici" PDF //
					if (strPdfArchive.GetLength() > 4)
					{
						if (strPdfArchive.Right(3).CompareNoCase("p7m") == 0)
						{
							int nBackslash = strPdfArchive.ReverseFind('\\');

							CString sNewFileName = theApp.m_sDirTemp + strPdfArchive.Mid(nBackslash, strPdfArchive.GetLength() - nBackslash - 4); // con il -4 tolgo anche l'estensione .P7M

							if (CopyFile(strPdfArchive, sNewFileName, FALSE))
								strPdfArchive = sNewFileName;
						}
					}

					// allego solo l'ultimo PDF valido //
					listAttachedFiles.AddTail(strPdfArchive);
					break;
				}
			}
		}
	}

	// IMMAGINI E FILMATI //

	CString strTemp = theApp.m_sDirTemp;
	if (strTemp.Right(1) == "\\")
		strTemp += "MAIL";
	else
		strTemp += "\\MAIL";

	DeleteDirectory(strTemp);
	VerificaPercorso(strTemp);

	POSITION pos2 = CFileBmp::GetFirstSelectedPos();
	while(pos2 != NULL)
	{
		CObSelect* pSel = CFileBmp::GetNextSelected(pos2);
		if (pSel != NULL)
		{
			if (!pSel->m_bIsGlobal)
			{
				if (!pSel->m_bConfirmed)
				{
					CImgExpIDList IdList;

					EXP_ITEM itemTemp;
					itemTemp.lIDImmagine = pSel->m_lID;
					itemTemp.sPrefisso = (theApp.m_bNominativoSuExportImmagini ? CPazientiSet().GetCognomeNome(m_pEsamiView->m_pEsamiSet->m_lPaziente) : "");
					itemTemp.lPrefissoNum = ((theApp.m_nApplication != PRG_DERMOX) ? 0 : CVistaImmaginiNumeroDermoxSet().GetNumeroDermox(pSel->m_lID));
					IdList.AddTail(itemTemp);

					int nExport = m_pEsamiView->m_pImgManager->ExportImgList(strTemp, &IdList, image_jpg);
					if (nExport < 1)
					{
						CString strMessage;
						strMessage.Format(theApp.GetMessageString(IDS_ERROR_EXPORT_DOCUMENT), m_pEsamiView->m_pImgManager->GetFullPath(pSel->m_lID));
						theApp.AfxMessageBoxEndo(strMessage, MB_ICONEXCLAMATION);
					}
					IdList.RemoveAll();
				}
			}
		}
	}

	WIN32_FIND_DATA dataFile;
	HANDLE hFile = FindFirstFile(strTemp + "\\*.*", &dataFile);
	if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
	{
		do
		{
			CString strFile(dataFile.cFileName);

			if (strFile.GetLength() > 3)
			{
				if ((strFile.Right(3).CompareNoCase("jpg") == 0) || (strFile.Right(3).CompareNoCase("tif") == 0))
					listAttachedFiles.AddTail(strTemp + "\\" + dataFile.cFileName);
			}
		} while(FindNextFile(hFile, &dataFile));
	}
	FindClose(hFile);

	// --- //

	if (listAttachedFiles.GetCount() == 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUMESAME_NIENTEDASPEDIRE));
		return;
	}

	WritePrivateProfileString("Settings", "MailDest", "mail", theApp.m_sDirProg + "\\MailSender.cfg");
	// WritePrivateProfileString("Settings", "MailSender", "", theApp.m_sDirProg + "\\MailSender.cfg");
	WritePrivateProfileString("Settings", "Modality", "", theApp.m_sDirProg + "\\MailSender.cfg");
	WritePrivateProfileString("Settings", "Object", m_pEsamiView->m_pPazientiSet->m_sCognome + " " + m_pEsamiView->m_pPazientiSet->m_sNome, theApp.m_sDirProg + "\\MailSender.cfg");
	WritePrivateProfileString("Settings", "TempPath", theApp.m_sDirTemp, theApp.m_sDirProg + "\\MailSender.cfg");

	WritePrivateProfileInt("Settings", "AttachmentNumber", listAttachedFiles.GetCount(), theApp.m_sDirProg + "\\MailSender.cfg");
	for(int i = 0; i < listAttachedFiles.GetCount(); i++)
	{
		CString strTmp;
		strTmp.Format("Attachment%li", i + 1);
		WritePrivateProfileString("Settings", strTmp, listAttachedFiles.GetAt(listAttachedFiles.FindIndex(i)), theApp.m_sDirProg + "\\MailSender.cfg");
	}

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	TCHAR szProcess[255];
	sprintf_s(szProcess, "%s\\MailSender.exe", theApp.m_sDirProg);

	if (!CreateProcess(NULL, szProcess, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
		return;

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	// Sandro 07/03/2011 // deseleziono le immagini //
	if (theApp.m_bAutoDeselect)
	{
		CFileBmp::DeleteListSelected(LOCAL_IMAGES);
		MoveImage();
	}

	//
	EndWaitCursor();
}

void CAlbumEsameDlg::OnBnClickedCanc()
{
	CString strTemp;
	int iNumSel = GetDlgItemInt(IDC_STATIC_NUM2);

	if (iNumSel <= 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUMESAME_ERR_SEL_DEL));
		return;
	}

	strTemp.Format(theApp.GetMessageString(IDS_ALBUMESAME_DEL_IMG), iNumSel);
	if (theApp.AfxMessageBoxEndo(strTemp, MB_YESNO | MB_ICONQUESTION) == IDNO)
		return;

	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUMESAME_DEL_IMG_CONFIRM), MB_YESNO | MB_ICONSTOP) == IDNO)
        return;

	CImgIDList IdList;

	POSITION pos1 = CFileBmp::GetFirstSelectedPos();
	while(pos1 != NULL)
	{
		CObSelect* pSel = CFileBmp::GetNextSelected(pos1);

		if ((pSel != NULL) && (!pSel->m_bIsGlobal))
			IdList.AddTail(pSel->m_lID);
	}

	m_pEsamiView->m_pImgManager->DelImgList(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, &IdList);

	IdList.RemoveAll();

	if (m_nDiapoPerEsame == SEDICI_IMMAGINI)
		m_nDiapoPerEsame = QUATTRO_IMMAGINI;
	else
		m_nDiapoPerEsame = SEDICI_IMMAGINI;
	OnChangeView();

	CFileBmp::DeleteListSelected(LOCAL_IMAGES);
}

void CAlbumEsameDlg::OnSize(UINT nType, int cx, int cy) 
{
	int i;

	CEndoxResizableDlg::OnSize(nType, cx, cy);

	if (m_nDiapoPerEsame == QUATTRO_IMMAGINI)
	{
		for(i = 0; i < QUATTRO_IMMAGINI; i++)
		{
			if (m_pFileBmp[i] != NULL)
				m_pFileBmp[i]->SendMessage(EPM_RESIZE_FORM);
		}
	}
	else
	{
		for(i = 0; i < SEDICI_IMMAGINI; i++)
		{
			if (m_pFileBmp[i] != NULL)
				m_pFileBmp[i]->SendMessage(EPM_RESIZE_FORM);
		}
	}
}

void CAlbumEsameDlg::CaricaPunti()
{
	long lIdPunto;
	long lIdOrgano;
	long lX;
	long lY;
	IMG_ORGANI img_organi;

	BOOL bFindIndex;

	POSITION pos1 = m_ImgListOrgani.GetHeadPosition();
	POSITION pos2;

	listPunti.RemoveAll();
	while(pos1 != NULL)
	{
		lIdPunto = CImmaginiPuntiSet().GetIDPunto(m_ImgListOrgani.GetAt(pos1).img.lID);
		if (lIdPunto > 0)
		{
			if (CPuntiSet().GetDatiPunto(lIdPunto, lIdOrgano, lX, lY))
			{
				img_organi = m_ImgListOrgani.GetAt(pos1);
				img_organi.iPunto = 0;

				bFindIndex = FALSE;
				pos2 = listPunti.GetHeadPosition();
				while(pos2 != NULL)
				{
					if (listPunti.GetAt(pos2).lIdOrgano == lIdOrgano)
					{
						if ((lX == listPunti.GetAt(pos2).lX) && (lY == listPunti.GetAt(pos2).lY))
						{
							bFindIndex = TRUE;
							break;
						}
					}

					listPunti.GetNext(pos2);
					img_organi.iPunto++;
				}

				if (!bFindIndex)
				{
					tagPunti puntoTemp;

					puntoTemp.lIdPunto = lIdPunto;
					puntoTemp.lIdOrgano = lIdOrgano;
					puntoTemp.lX = lX;
					puntoTemp.lY = lY;

					listPunti.AddTail(puntoTemp);

					img_organi.iPunto = listPunti.GetCount() - 1;
				}

				m_ImgListOrgani.SetAt(pos1, img_organi);
			}
		}
		m_ImgListOrgani.GetNext(pos1);
	}
}

void CAlbumEsameDlg::DeleteTempImages(CString folder)
{
	::DeleteDirectory(folder);
}

struct RimageData
{
	CEsamiView* pEsamiView;
	discType iType;
	int iNumSel;
	etichetta etichettaDisco;
	int iNumeroDiCopie;

	//Dati aggiunti
	BOOL m_bSimulation;
	long m_lPort;
	CString m_sHost;
	CString m_sTempFolder;
	CString m_sLabelPath;
	CString m_sMergeFolder;
};

struct ImgParam
{
	int iId;
	int iPaziente;
	int iEsame;
};

BOOL CAlbumEsameDlg::RimageBurning(discType iType, int iNumSel)
{
	CRobotSelezioneDlg selDlg;
	selDlg.DoModal();

	//Controllo che i campi siano valorizzati e corretti
	if (selDlg.m_sHost == "")
	{
		//"Nessun masterizzatore Rimage definito!"
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_RIMAGE_NO_IP));
		return FALSE;
	}
	if (selDlg.m_lPort < 0)
	{
		//"Nessuna porta masterizzatore Rimage definita!"
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_RIMAGE_NO_PORT));
		return FALSE;
	}
	if (selDlg.m_sMergeDirectoryPath == "")
	{
		//"Percorso per i file di merge non definito!"
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_RIMAGE_NO_MERGE_PATH));
		return FALSE;
	}
	else
	{
		//Controllo l'accessibilità della cartella e la possibilità di creare il file
		if (selDlg.m_sMergeDirectoryPath.Right(1) != "\\")
			selDlg.m_sMergeDirectoryPath += "\\";
		CString sMergeFile = selDlg.m_sMergeDirectoryPath + "test.tmp";
		HANDLE tempFile = ::CreateFile(sMergeFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, NULL, NULL);  
		if (tempFile == INVALID_HANDLE_VALUE)
		{
			CloseHandle(tempFile);
			::DeleteFile(sMergeFile);
			//"Verificare l'accesso al file di merge!"
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_RIMAGE_NO_MERGE_ACCESS));
			return FALSE;
		}
		CloseHandle(tempFile);
		::DeleteFile(sMergeFile);
	}
	if (selDlg.m_sTempDirectoryPath == "")
	{
		//"Nessuna cartella di esportazione temporanea definita!"
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_RIMAGE_NO_EXP_PATH));
		return FALSE;
	}
	else
	{
		//Controllo l'accessibilità della cartella e la possibilità di creare il file
		if (selDlg.m_sTempDirectoryPath.Right(1) != "\\")
			selDlg.m_sTempDirectoryPath += "\\";
		CString file = selDlg.m_sTempDirectoryPath + "test.tmp";
		HANDLE tempFile = ::CreateFile(file, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, NULL, NULL);  
		if (tempFile == INVALID_HANDLE_VALUE)
		{
			CloseHandle(tempFile);
			::DeleteFile(file);
			//"Verificare l'accesso alla cartella di esportazione!"
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_RIMAGE_NO_EXP_ACCESS));
			return FALSE;
		}
		CloseHandle(tempFile);
		::DeleteFile(file);
	}
	if (selDlg.m_sPatientLabelPath == "")
	{
		//"Nessun file di etichetta definito!"
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_RIMAGE_NO_LABEL));
		return FALSE;
	}
	else
	{
		//Controllo l'accessibilità della cartella e la possibilità di leggere il file
		HANDLE tempFile = ::CreateFile(selDlg.m_sPatientLabelPath, GENERIC_READ, 0, NULL, OPEN_EXISTING, NULL, NULL);
		if (tempFile == INVALID_HANDLE_VALUE)
		{
			CloseHandle(tempFile);
			//"Verificare l'accesso al file dell'etichetta!"
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_RIMAGE_NO_LABEL_ACCESS));
			return FALSE;
		}
		CloseHandle(tempFile);
	}

	CTime now = CTime::GetCurrentTime();
	CCustomDate dataEsame(m_pEsamiView->m_pEsamiSet->m_lData);
	CCustomDate dataNascita(m_pEsamiView->m_pPazientiSet->m_lNatoIlCustom);
	CString strTemp;

	RimageData* rimageData = new RimageData();
	rimageData->iNumSel = iNumSel;
	rimageData->iType = iType;
	rimageData->pEsamiView = m_pEsamiView;
	
	strTemp.Format("%02d/%02d/%d", dataEsame.GetDay(), dataEsame.GetMonth(), dataEsame.GetYear());
	rimageData->etichettaDisco.dataEsame = strTemp; 
	strTemp.Format("%02d/%02d/%d", dataNascita.GetDay(), dataNascita.GetMonth(), dataNascita.GetYear());
	rimageData->etichettaDisco.dataNascita = strTemp;
	rimageData->etichettaDisco.dataStampa = now.Format("%d/%m/%Y %H:%M:%S");
	rimageData->etichettaDisco.idPaziente = m_pEsamiView->m_pPazientiSet->m_sAssIden;
	rimageData->etichettaDisco.nomePaziente = m_pEsamiView->m_pPazientiSet->m_sCognome + " " + m_pEsamiView->m_pPazientiSet->m_sNome;
	
	CTipoEsameSet tipoEsameSet;
	rimageData->etichettaDisco.tipoEsame = tipoEsameSet.GetDescrizione(m_pEsamiView->m_pEsamiSet->m_lIDEsame);

	strTemp.Format("%s %s %02d.%02d.%d", m_pEsamiView->m_pPazientiSet->m_sCognome, m_pEsamiView->m_pPazientiSet->m_sNome, dataEsame.GetDay(), dataEsame.GetMonth(), dataEsame.GetYear());
	rimageData->etichettaDisco.nomeVolume = strTemp;

	CNumberOfCopiesDlg dlg(this, m_pEsamiView);
	dlg.DoModal();
	rimageData->iNumeroDiCopie = dlg.m_iCopies;

	/*m_pEsamiView->m_dialog.Create(IDD_ABOUTBOX);
	rimageData->dialog = m_pEsamiView->m_dialog.GetSafeHwnd();*/

	//Masterizzazione
	//Passare una struttura contenente anche le informazioni per il DVD
	AfxBeginThread(RimageDirectoryBurningThread, rimageData);
			
	return TRUE;
}

UINT CAlbumEsameDlg::RimageDirectoryBurningThread(LPVOID pParam)
{
	RimageData* rimageData = (RimageData*) pParam;

	//Prima che qualcuno cambi esame devo salvarmi la lista delle selezionate
	POSITION pos = CFileBmp::GetFirstSelectedPos();
	CList<ImgParam> imgParamList;

	while(pos != NULL)
	{
		CObSelect* pSel = CFileBmp::GetNextSelected(pos);
		if (pSel)
		{
			ImgParam temp;
			temp.iId = pSel->m_lID;
			temp.iPaziente = pSel->m_lPaziente;
			temp.iEsame = pSel->m_lEsame;
			imgParamList.AddTail(temp);
		}
	}

	if (FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)))
		return 0;	

	//Testo il caricamento della library
	#ifdef _DEBUG
		HMODULE hModule = ::LoadLibrary("AmImgBackupD.dll");
	#else
		HMODULE hModule = ::LoadLibrary("AmImgBackup.dll");
	#endif

	if (hModule == NULL)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMGBACKUP_NODLL), MB_ICONSTOP);

		return FALSE; // FALSE;
	}

	AmImgBackup_EnableLocalization_PTR AmImgBackup_EnableLocalization = (AmImgBackup_EnableLocalization_PTR)::GetProcAddress(hModule, _AmImgBackup_EnableLocalization_FUNCTION);
	if (AmImgBackup_EnableLocalization == NULL)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMGBACKUP_NOFUNCTION), MB_ICONSTOP);

		return FALSE; // FALSE;
	}

	AmImgBackup_EnableLocalization(theApp.GetMessageString, theApp.LocalizeDialog);

	RimageDirectoryBurning_PTR RimageDirectoryBurning = (RimageDirectoryBurning_PTR)::GetProcAddress(hModule, _RimageDirectoryBurning_FUNCTION);
	if (RimageDirectoryBurning == NULL)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMGBACKUP_NOFUNCTION), MB_ICONSTOP);

		return FALSE; // FALSE;
	}
	
	::FreeLibrary(hModule);
	//

	//Esporto i file selezionati sulla cartella di default che poi sarà utilizzata da Rimage
	CString sPercorso = "";
	theApp.m_sExportFolder = rimageData->m_sTempFolder;

	CCustomDate dataTemp(rimageData->pEsamiView->m_pEsamiSet->m_lData);

	CString strTemp;
	strTemp.Format("%s%s %s %02d.%02d.%d", theApp.m_sExportFolder, rimageData->pEsamiView->m_pPazientiSet->m_sCognome, rimageData->pEsamiView->m_pPazientiSet->m_sNome, dataTemp.GetDay(), dataTemp.GetMonth(), dataTemp.GetYear());
	if (VerificaPercorso(strTemp) == FALSE)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_EXPORT_PATH), MB_ICONSTOP);
		rimageData->pEsamiView->SendMessage(EPM_THREAD_RIMAGE_SETPOS, (WPARAM)100, 0);
		return FALSE;
	}

	int nExport;
	CImgExpIDList IdList;

	// visualizzo la barra di avanzamento //
	int nPos = 0;
	rimageData->pEsamiView->SendMessage(EPM_THREAD_RIMAGE_SETPOS, nPos, 0);	

	int index=0;	
	
	for(POSITION pos2=imgParamList.GetHeadPosition();pos2;)
	{
		ImgParam imgParam = imgParamList.GetNext(pos2);
			
		index++;

		int perc = (int) (((double)index/(double)rimageData->iNumSel)*(double)100);
		rimageData->pEsamiView->SendMessage(EPM_THREAD_RIMAGE_SETPOS, perc, 0);	
		/*if (pSel->m_bConfirmed)
		{
			while(GetVolumeName() != pSel->m_strDvdLabel)
			{
				CEspelliDlg	dlg(this, pSel->m_strDvdLabel);

				if (dlg.DoModal() == IDCANCEL)
					break;
			}
		}*/

		rimageData->pEsamiView->m_pImgManager->SetCurrentIDs(imgParam.iPaziente, imgParam.iEsame);
			
		EXP_ITEM itemTemp;
		itemTemp.lIDImmagine = imgParam.iId;
		itemTemp.sPrefisso = (theApp.m_bNominativoSuExportImmagini ? CPazientiSet().GetCognomeNome(imgParam.iPaziente) : "");
		itemTemp.lPrefissoNum = ((theApp.m_nApplication != PRG_DERMOX) ? 0 : CVistaImmaginiNumeroDermoxSet().GetNumeroDermox(imgParam.iId));
		IdList.AddTail(itemTemp);

		nExport = rimageData->pEsamiView->m_pImgManager->ExportImgList(strTemp, &IdList, (imageformat)(theApp.m_nExpFormat + 1));
		if (nExport != 1)
		{
			CString strMessage;
			strMessage.Format(theApp.GetMessageString(IDS_ERROR_EXPORT_DOCUMENT), rimageData->pEsamiView->m_pImgManager->GetFullPath(imgParam.iId));
			theApp.AfxMessageBoxEndo(strMessage, MB_ICONEXCLAMATION);
			return FALSE;
		}

		IdList.RemoveAll();
			
	}

	if (nPos < 100)
		rimageData->pEsamiView->SendMessage(EPM_THREAD_RIMAGE_SETPOS, (WPARAM)100, 0);

	rimageData->pEsamiView->SendMessage(EPM_THREAD_RIMAGE_ON, 0, 0);

	sPercorso.Format("%s", strTemp);

	CString sNomeComputer = theApp.m_sNomeComputer;
	CString sRimageAddress = rimageData->m_sHost;
	int iRimagePort = rimageData->m_lPort;
	CString sRimageLabelFile_patient = rimageData->m_sLabelPath;
	sPercorso = sPercorso;
	CString sRimageMergeFilesPath = rimageData->m_sMergeFolder;
	CString nomeVolume = rimageData->etichettaDisco.nomeVolume;
	CString dataStampa = rimageData->etichettaDisco.dataStampa;
	CString idPaziente = rimageData->etichettaDisco.idPaziente;
	CString nomePaziente = rimageData->etichettaDisco.nomePaziente;
	CString dataNascita = rimageData->etichettaDisco.dataNascita;
	CString dataEsame = rimageData->etichettaDisco.dataEsame;
	CString tipoEsame = rimageData->etichettaDisco.tipoEsame;
	// BOOL bRimageSimulateBurning = theApp.m_bRimageSimulateBurning;
	int iNumeroDiCopie = rimageData->iNumeroDiCopie;
	discType iType = rimageData->iType;

	sNomeComputer.Replace("\\", "\\\\");
	sRimageAddress.Replace("\\", "\\\\");
	sRimageLabelFile_patient.Replace("\\", "\\\\");
	sPercorso.Replace("\\", "\\\\");
	sRimageMergeFilesPath.Replace("\\", "\\\\");
	nomeVolume.Replace("\\", "\\\\");
	dataStampa.Replace("\\", "\\\\");
	idPaziente.Replace("\\", "\\\\");
	nomePaziente.Replace("\\", "\\\\");
	dataNascita.Replace("\\", "\\\\");
	dataEsame.Replace("\\", "\\\\");
	tipoEsame.Replace("\\", "\\\\");

	//CREATE PROCESS
	CString parameters;
	parameters.Format("\"%s\" \"%s\" \"%li\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" \"%li\" \"%li\" \"%li\"", 
						sNomeComputer, sRimageAddress, iRimagePort, sRimageLabelFile_patient, sPercorso, 
						sRimageMergeFilesPath, nomeVolume, dataStampa, idPaziente, nomePaziente, dataNascita, 
						dataEsame, tipoEsame, rimageData->m_bSimulation ? 1 : 0, iNumeroDiCopie, iType);

	TCHAR szProcess[1024];
	sprintf_s(szProcess, "RimageDirectoryBurning.exe %s", parameters);

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;

	HANDLE hChildStdoutRd, hChildStdoutWr;
	if (!CreatePipe(&hChildStdoutRd, &hChildStdoutWr, &sa, 10000000))
	{
		theApp.AfxMessageBoxEndo("CreatePipe error", MB_OK);
		rimageData->pEsamiView->SendMessage(EPM_THREAD_RIMAGE_OFF, 0, 0);
		return FALSE;
	}

	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	DWORD dwError = 0, dwExitCode = 0;

	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
    si.dwFlags    = STARTF_USESTDHANDLES;
    //si.hStdInput  = hChildStdinRd;
    si.hStdOutput = hChildStdoutWr;
    si.hStdError  = NULL;

	// Start the child process. 
	if (CreateProcess(NULL,
					 szProcess,
					 NULL,
					 NULL,
					 TRUE,
					 CREATE_NO_WINDOW,
					 NULL,
					 NULL,
					 &si,
					 &pi))
	{
		WaitForSingleObject(pi.hProcess, INFINITE);
		
		if (GetExitCodeProcess(pi.hProcess, &dwExitCode) && dwExitCode == 0)
		{
			DWORD dwTotalBytes = 0, dwReaded;
			if (PeekNamedPipe(hChildStdoutRd, NULL, 0, NULL, &dwTotalBytes, NULL) && dwTotalBytes > 0)
			{
				if (dwTotalBytes <= 10000000)
				{
					BYTE* pBufferTemp = new BYTE[10000000];
					if (::ReadFile(hChildStdoutRd, pBufferTemp, dwTotalBytes, &dwReaded, NULL))
					{
						pBufferTemp[dwReaded] = 0;
						CString message((char*)pBufferTemp);
						theApp.AfxMessageBoxEndo(message);

						sPercorso.Replace("\\\\", "\\");
						DeleteTempImages(sPercorso);
					}
					else
						theApp.AfxMessageBoxEndo("ReadFile error", MB_OK);

					delete pBufferTemp;
				}
				else
					theApp.AfxMessageBoxEndo("dwTotalBytes <= iBufferPDFLength", MB_OK);
			}
			else
				theApp.AfxMessageBoxEndo("PeekNamedPipe error", MB_OK);
		}
		else
		{
			TCHAR szError[255];
			sprintf_s(szError, "ExitCodeProcess %li", dwExitCode);
			theApp.AfxMessageBoxEndo(szError, MB_OK);
		}

		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}
	else
	{
		theApp.AfxMessageBoxEndo("CreateProcess error", MB_OK);
	}	

	CloseHandle(hChildStdoutRd);
	CloseHandle(hChildStdoutWr);

	CEsamiView* temp = rimageData->pEsamiView;
	temp->SendMessage(EPM_THREAD_RIMAGE_OFF, 0, 0);

	delete(rimageData);

	return 0;
}

