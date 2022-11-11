#include "stdafx.h"
#include "Endox.h"
#include "Exportdlg.h"

#include <io.h>
#include <direct.h>
#include <mmsystem.h>

#include "stdafx.h"
#include "Endox.h"
#include "define.h"
#include "common.h"
#include "Esamiview.h"
#include "MosaicDlg.h"
#include "ExportDlg.h"
#include "Dib.h"
#include "FileBmp.h"
#include "ObSelect.h"
#include "AlbumForm.h"
#include "volume.h"

#include "ExportDlg.h"
#include "ExportCdDlg.h"
#include "ExportHdDlg.h"
#include "ExportPptDlg.h"

#include "DLL_Imaging\h\AMlogin.h"

#include "EspelliDlg.h"
#include "StampaDlg.h"

#include "Path.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CExportDlg::CExportDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CExportDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView	= pEsamiView;

	m_pBmp			= NULL;
	m_pMosaicDlg  	= NULL;   
	m_bIsActive 	= FALSE;

}

CExportDlg::~CExportDlg()
{   
	if (m_pBmp)
	{
		m_pBmp->DestroyWindow();
		delete m_pBmp;
		m_pBmp = NULL;
	}               
}                         

void CExportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST, m_ctrListSchede);
	DDX_Control(pDX, IDC_LIST_RESET, m_ctrlBtnReset);
	DDX_Control(pDX, IDC_STATIC_LABEL1,  m_ctrlStaticLabel1);
	DDX_Control(pDX, IDC_STATIC_LABEL2,  m_ctrlStaticLabel2);
}

BEGIN_MESSAGE_MAP(CExportDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_SYSCOMMAND()

	ON_BN_CLICKED(IDC_IMM_EXPORT,		OnImmExport)
	ON_BN_CLICKED(IDC_IMM_PRINT,		OnImmPrint)
	ON_BN_CLICKED(IDC_IMM_PRINT_SET,	OnImmPrintSetup)
	ON_BN_CLICKED(IDC_LIST_RESET,		OnResetList)
	ON_BN_CLICKED(IDC_IMM_EXPORTCD,		OnImmExportCD)
	ON_BN_CLICKED(IDC_IMM_EXPORTDVD,	OnImmExportDVD)
	ON_BN_CLICKED(IDC_IMM_EXPORTPPT,	OnImmExportPPT)
	ON_BN_CLICKED(IDC_CHIUDI, OnChiudi)
	ON_BN_CLICKED(IDC_BTN_CANC,         OnBnClickedBtnCanc)

	ON_LBN_SELCHANGE(IDC_LIST,			OnSelChangeList)
END_MESSAGE_MAP()

void CExportDlg::PostCreate(CWnd* pParent, CEsamiView* pEsamiView)
{   
	Create(IDD, pParent);

	m_pEsamiView = pEsamiView;
	
	SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_HIDEWINDOW | SWP_NOSIZE | SWP_NOMOVE);
}

void CExportDlg::RemoveAll()
{
	while(!m_ListPathDiapo.IsEmpty())
		delete m_ListPathDiapo.RemoveHead();

	m_ctrListSchede.ResetContent();
	m_ctrListSchede.SetCurSel (-1); 
		
	if (m_pBmp != NULL)
		m_pBmp->ResetImage();

	AggiornaConteggio(); // Sandro Gallina - 19/01/2005 //
}

void CExportDlg::CaricaListaWith(CObList* pList)
{
	m_ctrListSchede.ResetContent();
					
	for(POSITION pos = pList->GetHeadPosition(); pos != NULL; )
	{
		CPath* pPath = (CPath*) pList->GetNext(pos);
			
		int nListPos = m_ctrListSchede.AddString(pPath->m_szDesc);
						
		if (nListPos != LB_ERR)
		{
			m_ctrListSchede.SetItemDataPtr(nListPos, pPath);
		}
	}
			
	m_ctrListSchede.SetCurSel (0);
	
	OnSelChangeList();

	AggiornaConteggio(); // Sandro Gallina - 19/01/2005 //
}

void CExportDlg::CaricaListaWith(CObList* pList, CString* pStrFilter)
{
	m_ctrListSchede.ResetContent();
					
	for(POSITION pos = pList->GetHeadPosition(); pos != NULL; )
	{
		CPath* pPath = (CPath*) pList->GetNext(pos);
			
		int nListPos = m_ctrListSchede.AddString(pPath->m_szDesc);
						
		if (nListPos != LB_ERR)
		{
			CString strFilter;
					
			// imposta il filtro in modo che su album si vedano solo le pic selezionate.
			strFilter.Format("CodiceScheda=%li", pPath->m_lEsame);

			if (*pStrFilter == "")
				*pStrFilter = strFilter;
			else
				*pStrFilter = " OR " + strFilter;

			m_ctrListSchede.SetItemDataPtr (nListPos, pPath);
		}
	}
			
	m_ctrListSchede.SetCurSel (0);

	OnSelChangeList();

	AggiornaConteggio(); // Sandro Gallina - 19/01/2005 //
}

void CExportDlg::ShowDialog(BOOL bShow)
{
	if (bShow)
	{
		m_bIsActive = TRUE;
		ShowWindow (SW_SHOWNORMAL);
	}
	else
	{
		m_bIsActive = FALSE;
		ShowWindow (SW_HIDE);
	}

	if (m_pMosaicDlg)
		m_pMosaicDlg->UpdateData(FALSE);

    //
    UpdateData(!m_bIsActive);
}

BOOL CExportDlg::ExportImmagini(CString strPath)
{
	BOOL bReturn = TRUE;

	return bReturn;
}

void CExportDlg::StampaImmagini()
{
	CObArray ImgArray;

	POSITION nPos = m_ListPathDiapo.GetHeadPosition();
	while(nPos != NULL)
	{
		CPath* pPath = (CPath*)m_ListPathDiapo.GetNext(nPos);
		
		if ((pPath != NULL) && (pPath->m_lID > 0))
		{
			CObSelect* pObSelect = new CObSelect;

			if (pObSelect)
			{
				pObSelect->m_bIsGlobal = TRUE;
				pObSelect->m_strDescription = pPath->m_szDesc;
				pObSelect->m_lPaziente = pPath->m_lPaziente;
				pObSelect->m_lEsame = pPath->m_lEsame;
				pObSelect->m_lID = pPath->m_lID;
				pObSelect->m_bConfirmed = pPath->m_bConfirmed;
				pObSelect->m_strDvdLabel = pPath->m_strDvdLabel;

				ImgArray.Add(pObSelect);
			}
		}
	}

	BOOL bContinue = (ImgArray.GetSize() > 0);
	if (bContinue)
		m_pEsamiView->AnteprimaStampaImmagini(STAMPA, GLOBAL_IMAGES, 1);

	////////////////////////////////////////
	///Cancellazione della lista di immagini
	for(int i = 0; i < ImgArray.GetSize(); i++)
	{
		CObSelect* pSel = (CObSelect*)ImgArray.GetAt(i);

		delete pSel;
	}

	ImgArray.RemoveAll();
	////////////////////////////////////////

	if (theApp.m_bAutoDeselect)
		ResetList(FALSE);
}

///////////////////////////////////////////////////////////
BOOL CExportDlg::FindImage(long nEsame, int nDiapo, int nTipo, long lID)
{                     
	for(int nPos = m_ctrListSchede.GetCount() - 1; nPos >= 0; nPos--)
	{
		CPath* pPath = (CPath*)m_ctrListSchede.GetItemDataPtr(nPos);
			
		if (pPath != NULL)
			if (pPath->m_lEsame == nEsame && pPath->m_lID == lID)
				return TRUE;
	}

	return FALSE;
}

///////////////////////////////////////////////////////////
void CExportDlg::RemoveImage(long lID)
{                     
	for(int nPos=m_ctrListSchede.GetCount()-1; nPos>=0; nPos--)
	{
		CPath* pPath = (CPath*)m_ctrListSchede.GetItemDataPtr(nPos);
			
		if (pPath)
		{
			if (pPath->m_lID == lID)
			{
				if (m_pMosaicDlg)
					m_pMosaicDlg->DeleteSelection(pPath->m_lEsame, pPath->m_lID);

				POSITION nPosDiapo = m_ListPathDiapo.Find(pPath);
				
				if (nPosDiapo)
				{
					m_ListPathDiapo.RemoveAt(nPosDiapo);
					delete pPath;
					pPath = NULL;
				}

				m_ctrListSchede.DeleteString(nPos);

				nPos = min(nPos, m_ctrListSchede.GetCount()-1);
				m_ctrListSchede.SetCurSel(nPos);
				
				OnSelChangeList();
				
				break;
			}
		}
	}

	AggiornaConteggio(); // Sandro Gallina - 19/01/2005 //
}

///////////////////////////////////////////////////////////
void CExportDlg::AddImage(structEsame* pRiga, long lID, int type, BOOL bConfirmed, CString strDvdLabel, HBITMAP hBitmap, BOOL bCI)
{                     
	CPath*	pPath = new CPath;
	int		nPos;

	int lIndex = 0;
	POSITION pos = pRiga->ImgListOrgani.GetHeadPosition();
	while(pos != NULL)
	{
		if (pRiga->ImgListOrgani.GetAt(pos).img.lID == lID)
			break;

		lIndex++;
		pRiga->ImgListOrgani.GetNext(pos);
	}
	
	if (pPath)
	{
		pPath->SetParameter(pRiga->lPaziente, pRiga->lEsame, lID, &pRiga->ImgListOrgani, lIndex, bConfirmed, strDvdLabel, pRiga->strPaziente, pRiga->nDataEsame);

		nPos = m_ctrListSchede.AddString(pPath->m_szDesc);
	
		if (nPos != LB_ERRSPACE && nPos != LB_ERR)
		{
			m_ListPathDiapo.AddTail(pPath);
			
			m_ctrListSchede.SetItemDataPtr(nPos, pPath);
			m_ctrListSchede.SetCurSel (nPos);

			OnSelChangeList();
		}
	}

	AggiornaConteggio(); // Sandro Gallina - 19/01/2005 //
}

// Sandro Gallina - 19/01/2005 //
void CExportDlg::AggiornaConteggio()
{
	SetDlgItemInt(IDC_NUM_SEL, m_ctrListSchede.GetCount());

	long lPaziente;
	long lEsame;
	m_pEsamiView->m_pImgManager->GetCurrentIDs(lPaziente, lEsame);

	BOOL bOnlyFilms = TRUE;
	int nFoundFilms = 0;

	BOOL bConfirmed = FALSE;
	double dKb = 0;
	POSITION pos = CFileBmp::GetFirstSelectedPos();
	while(pos != NULL)
	{
		CObSelect* pSel = CFileBmp::GetNextSelected(pos);
		if (pSel != NULL)
		{
			if (pSel->m_bIsGlobal)
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
						m_pEsamiView->m_pImgManager->SetCurrentIDs(pSel->m_lPaziente, pSel->m_lEsame);
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
				strDim.Format("%.1lfGb", dKb);
			}
			else
			{
				strDim.Format("%.1lfMb", dKb);
			}
		}
		else
		{
			strDim.Format("%.1lfKb", dKb);
		}
	}
	SetDlgItemText(IDC_STATIC_NUM4, strDim);
	m_pEsamiView->m_pImgManager->SetCurrentIDs(lPaziente, lEsame);

	pos = CFileBmp::GetFirstSelectedPos();
	while(pos != NULL)
	{
		CObSelect* pSel = CFileBmp::GetNextSelected(pos);
		
		if (pSel != NULL)
		{
			if (pSel->m_bIsGlobal == TRUE)
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
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
BOOL CExportDlg::OnInitDialog()
{   
	CDialog::OnInitDialog();

	GetDlgItem(IDC_CHIUDI)->SetFont(&theApp.m_fontBold);

	m_btnPrint.AutoLoad(IDC_IMM_PRINT, this);
	m_btnPrintSel.AutoLoad(IDC_IMM_PRINT_SET, this);
	m_btnExp.AutoLoad(IDC_IMM_EXPORT, this);
	m_btnExpCD.AutoLoad(IDC_IMM_EXPORTCD, this);
	m_btnExpDVD.AutoLoad(IDC_IMM_EXPORTDVD, this);
	m_btnExpPPT.AutoLoad(IDC_IMM_EXPORTPPT, this);
	m_btnCanc.AutoLoad(IDC_BTN_CANC, this);
	m_btnEsc.AutoLoad(IDC_CHIUDI, this);

	if (CFileBmp::CreateBmp(m_pEsamiView, this, GetDlgItem(IDC_CORNICE_RECT), &m_pBmp))
	{
		m_pBmp->SetMouseMode(BMP_L_NORMALMODE, BMP_R_SENDTOPARENT);
		m_pBmp->SetAlbumType(TRUE); 
		m_pBmp->ShowWindow(TRUE);
	}

	GetDlgItem(IDC_IMM_PRINT)->EnableWindow(theApp.m_dwPrivileges & AMLogin_Permissions::printout ? TRUE : FALSE);
	GetDlgItem(IDC_IMM_PRINT_SET)->EnableWindow(theApp.m_dwPrivileges & AMLogin_Permissions::printout ? TRUE : FALSE);

	GetDlgItem(IDC_IMM_EXPORT)->EnableWindow(theApp.m_dwPrivileges & AMLogin_Permissions::exportout ? TRUE : FALSE);
	GetDlgItem(IDC_IMM_EXPORTCD)->EnableWindow((theApp.m_dwPrivileges & AMLogin_Permissions::exportout ? TRUE : FALSE) && (theApp.m_bCanWriteCD));
	GetDlgItem(IDC_IMM_EXPORTDVD)->EnableWindow((theApp.m_dwPrivileges & AMLogin_Permissions::exportout ? TRUE : FALSE) && (theApp.m_bCanWriteDVD));

	RemoveAll();
	theApp.LocalizeDialog(this, CExportDlg::IDD, "ExportDlg");

	return TRUE;                    
}                

///////////////////////////////////////////////////////////
void CExportDlg::OnChiudi()
{
	ShowDialog(FALSE);
}

///////////////////////////////////////////////////////////
void CExportDlg::OnImmExport()
{
    UpdateData(TRUE);

	int iNumSel = GetDlgItemInt(IDC_NUM_SEL);
	CFolderDialog dlg(theApp.GetMessageString(IDS_FOLDERDLG_TITLE_1), theApp.m_sExportFolder, 0x0040, this);

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
			CExportHdDlg dlg(this, this, iNumSel);
			dlg.DoModal();

			if (theApp.m_bAutoDeselect)
				ResetList(FALSE);
		}
	}

}

///////////////////////////////////////////////////////////
void CExportDlg::OnImmPrint()
{
	UpdateData(TRUE);	             
	
	if (!m_ListPathDiapo.IsEmpty())
		StampaImmagini();
}

///////////////////////////////////////////////////////////
void CExportDlg::OnImmPrintSetup() 
{
	CStampaDlg(this, m_pEsamiView).DoModal();
}

///////////////////////////////////////////////////////////
void CExportDlg::OnSelChangeList()
{
	int nPos;

	m_pBmp->ResetImage();

	nPos = m_ctrListSchede.GetCurSel();
	if (nPos != LB_ERRSPACE && nPos != LB_ERR)
	{
		CPath* pPath = (CPath*)m_ctrListSchede.GetItemDataPtr(nPos);
		
		if (pPath && pPath->m_lID)
			m_pBmp->LoadImage(pPath->m_lPaziente, pPath->m_lEsame, pPath->m_pImgListOrgani, pPath->m_lIndex, pPath->m_bConfirmed, pPath->m_strDvdLabel, CARICA_MINI);
	}
}

///////////////////////////////////////////////////////////
void CExportDlg::OnResetList()
{
	ResetList(TRUE);
}

// Sandro Gallina - 19/01/2005 //
void CExportDlg::ResetList(BOOL bChiediConferma)
{
	if (m_ctrListSchede.GetCount() <= 0)
		return;

	if (bChiediConferma == TRUE)
		if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_EXPORTDLG_CONFIRM_DELETE), MB_YESNO) == IDNO)
			return;

	while(!m_ListPathDiapo.IsEmpty())
		delete m_ListPathDiapo.RemoveHead();
	
	m_ctrListSchede.ResetContent();
	m_ctrListSchede.SetCurSel(-1); 
		
	m_pBmp->ResetImage();

	if (m_pMosaicDlg)
		m_pMosaicDlg->DeleteSelection();

	AggiornaConteggio(); // Sandro Gallina - 19/01/2005 //
}

void CExportDlg::OnDestroy()
{
    RemoveAll();

	CDialog::OnDestroy();
}

void CExportDlg::OnSysCommand(UINT nID, LPARAM lParam) 
{
	if (nID == SC_CLOSE)
	{
		ShowDialog(FALSE);
		return;
	}

	if (nID == SC_MAXIMIZE || nID == SC_SIZE)
	{
		return;
	}
	
	CDialog::OnSysCommand(nID, lParam);
}

// Sandro Gallina - 18/04/2005 //
void CExportDlg::OnImmExportCD() 
{
	CString strTemp;
	int iNumSel = GetDlgItemInt(IDC_NUM_SEL);

	if (iNumSel <= 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUMESAME_ERR_SEL));
		return;
	}

	strTemp.Format(theApp.GetMessageString(IDS_DOCUMENTI_ESPORTARE_CD), iNumSel);
	if (theApp.AfxMessageBoxEndo(strTemp, MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		CExportCdDlg dlg(this, m_pEsamiView, this, iNumSel, DISC_CD);
		dlg.DoModal();

		if (theApp.m_bAutoDeselect)
			ResetList(FALSE);
	}
}

// Sandro Gallina - 18/04/2005 //
void CExportDlg::OnImmExportDVD() 
{
	CString strTemp;
	int iNumSel = GetDlgItemInt(IDC_NUM_SEL);

	if (iNumSel <= 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUMESAME_ERR_SEL));
		return;
	}

	strTemp.Format(theApp.GetMessageString(IDS_DOCUMENTI_ESPORTARE_DVD), iNumSel);
	if (theApp.AfxMessageBoxEndo(strTemp, MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		CExportCdDlg dlg(this, m_pEsamiView, this, iNumSel, DISC_DVD);
		dlg.DoModal();

		if (theApp.m_bAutoDeselect)
			ResetList(FALSE);
	}
}

// Sandro Gallina - 09/11/2015 //
void CExportDlg::OnImmExportPPT()
{
	DeleteDirectory(theApp.m_sDirTemp + "\\PPT");

	int iNumSel = GetDlgItemInt(IDC_NUM_SEL);
	if (iNumSel <= 0)
	{
		theApp.AfxMessageBoxEndo(IDS_ALBUMESAME_ERR_SEL);
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

				CExportPptDlg dlg(this, this, iNumSel);
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

// Sandro Gallina - 19/01/2005 //
void CExportDlg::OnBnClickedBtnCanc()
{
	CPath* pPath = NULL;

	CString strTemp;
	int iNumSel = GetDlgItemInt(IDC_NUM_SEL);

	if (iNumSel <= 0)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_EXPORTDLG_SELECT));
		return;
	}

	strTemp.Format(theApp.GetMessageString(IDS_EXPORTDLG_CONFIRM_DELETE_2), iNumSel);
	if (theApp.AfxMessageBoxEndo(strTemp, MB_YESNO | MB_ICONQUESTION) == IDNO)
		return;

	if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_EXPORTDLG_CONFIRM_DELETE_3), MB_YESNO | MB_ICONSTOP) == IDNO)
        return;

	int nDeleted = 0;
	CImgIDList IdList;
	BeginWaitCursor();
	POSITION pos = m_ListPathDiapo.GetHeadPosition();
	while(pos != NULL)
	{
		pPath = m_ListPathDiapo.GetNext(pos);

		if (pPath != NULL)
		{
			if (pPath->m_bConfirmed == FALSE)
			{
				m_pEsamiView->m_pImgManager->SetCurrentIDs(pPath->m_lPaziente, pPath->m_lEsame);
				IdList.AddTail(pPath->m_lID);

				nDeleted += m_pEsamiView->m_pImgManager->DelImgList(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, &IdList);

				IdList.RemoveAll();
			}
		}
	}
	EndWaitCursor();

	ResetList(FALSE);
	m_pMosaicDlg->AfterMoveEsame(TRUE);

	if ((m_pEsamiView != NULL) && (m_pEsamiView->m_pFormImmagini != NULL))
		m_pEsamiView->m_pFormImmagini->AfterMoveEsame();

	CString strMessage;
	if (nDeleted != iNumSel)
		strMessage.Format(theApp.GetMessageString(IDS_DOCUMENTI_NONTUTTIELIMINATI), iNumSel - nDeleted);
	else
		strMessage.Format(theApp.GetMessageString(IDS_DOCUMENTI_TUTTIELIMINATI));
	theApp.AfxMessageBoxEndo(strMessage);
}
