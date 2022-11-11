#include "stdafx.h"
#include "Endox.h"
#include "PostAcquisizioneDlg.h"

#include "DLL_Imaging\h\AMLogin.h"
#include "DLL_Imaging\h\ImgArchive.h"

#include "EsamiSet.h"
#include "EsamiView.h"
#include "InsertLogAcquisizioneSPSet.h"
#include "ModelessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CPostAcquisizioneDlg, CEndoxResizableDlg)

CPostAcquisizioneDlg::CPostAcquisizioneDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxResizableDlg(CPostAcquisizioneDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;

	m_color1 = theApp.m_color[4];
	m_color2 = theApp.m_color[4];

	m_dTotFileSize = 0;

	m_ctrlListImage.SetMessageDest(this, m_pEsamiView);
}

CPostAcquisizioneDlg::~CPostAcquisizioneDlg()
{
	POSITION pos = m_ImgList.GetHeadPosition();
	while(pos != NULL)
	{
		IMG imgTemp = m_ImgList.GetAt(pos);

		DeleteObject(imgTemp.hBmp);
		DeleteObject(imgTemp.hBmpSelected);

		m_ImgList.GetNext(pos);
	}
}

BEGIN_MESSAGE_MAP(CPostAcquisizioneDlg, CEndoxResizableDlg)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()

	ON_MESSAGE(EPM_IMAGESEL_NOTIFY, OnImageSel)

	ON_BN_CLICKED(IDC_BTN_ELIMINA, OnBnClickedBtnElimina)
END_MESSAGE_MAP()

void CPostAcquisizioneDlg::DoDataExchange(CDataExchange* pDX)
{
	CEndoxResizableDlg::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_IMAGE, m_ctrlListImage);

	DDX_Control(pDX, IDC_BTN_ELIMINA, m_ctrlBtnElimina);
	DDX_Control(pDX, IDCANCEL, m_ctrlBtnCancel);
	DDX_Control(pDX, IDOK, m_ctrlBtnOK);

	DDX_Control(pDX, IDC_STATIC_01, m_ctrlStatic01);
	DDX_Control(pDX, IDC_STATIC_03, m_ctrlStatic03);
	DDX_Control(pDX, IDC_STATIC_05, m_ctrlStatic05);
	DDX_Control(pDX, IDC_STATIC_07, m_ctrlStatic07);
}

void CPostAcquisizioneDlg::OnCancel()
{
	/*
	this->KillTimer(POSTACQUISIZIONE_TIMER);

	switch(theApp.MessageBoxEndo(theApp.GetMessageString(IDS_POSTACQUISITION_ERROR), theApp.GetMessageString(IDS_ACHTUNG), MB_YESNOCANCEL | MB_ICONSTOP))
	{
		case IDYES:
		{
			DeleteDirectoryNoSub(theApp.m_sDirTempAcq);
			VerificaPercorso(theApp.m_sDirTempAcq);

			CEndoxResizableDlg::OnCancel();
		}
		case IDNO:
		{
			CEndoxResizableDlg::OnCancel();
		}
	}
	*/
}

HBRUSH CPostAcquisizioneDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CEndoxResizableDlg::OnCtlColor (pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_01:
		case IDC_STATIC_02:
			pDC->SetTextColor(m_color1);
			break;

		case IDC_STATIC_03:
		case IDC_STATIC_04:
			pDC->SetTextColor(theApp.m_color[4]);
			break;

		case IDC_STATIC_05:
		case IDC_STATIC_06:
			pDC->SetTextColor(m_color2);
			break;
	}

	return hBrush;
}

BOOL CPostAcquisizioneDlg::OnInitDialog()
{
	BOOL bReturn = CEndoxResizableDlg::OnInitDialog();

	SetTimer(POSTACQUISIZIONE_TIMER, 5000, NULL);

	AddAnchor(IDC_STATIC_01, CSize(0, 0), CSize(33, 0));
	AddAnchor(IDC_STATIC_02, CSize(0, 0), CSize(33, 0));
	AddAnchor(IDC_STATIC_03, CSize(33, 0), CSize(67, 0));
	AddAnchor(IDC_STATIC_04, CSize(33, 0), CSize(67, 0));
	AddAnchor(IDC_STATIC_05, CSize(67, 0), CSize(100, 0));
	AddAnchor(IDC_STATIC_06, CSize(67, 0), CSize(100, 0));
	AddAnchor(IDC_STATIC_07, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDC_LIST_IMAGE, CSize(0, 0), CSize(100, 100));
	AddAnchor(IDC_BTN_ELIMINA, CSize(0, 100), CSize(0, 100));
	AddAnchor(IDOK, CSize(100, 100), CSize(100, 100));
	AddAnchor(IDCANCEL, CSize(100, 100), CSize(100, 100));

	BeginWaitCursor();

	CModelessDlg dlg;
	dlg.CreateModeless(this);
	dlg.SetTitle(theApp.GetMessageString(IDS_CARICAMENTODOCUMENTI));

	MSG msg;

	//
	while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE | PM_QS_PAINT))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// dimensione files acquisiti //
	CalcolaDimensioni(&dlg);

	//
	while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE | PM_QS_PAINT))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// spazio libero su archivio //
	AggiornaSpazioLibero();

	//
	while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE | PM_QS_PAINT))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//
	//SystemParametersInfo(SPI_GETWORKAREA, 0, &rectDesk, 0);
	SetWindowPos(NULL, theApp.m_rectDesk.left, theApp.m_rectDesk.top, theApp.m_rectDesk.right - theApp.m_rectDesk.left, theApp.m_rectDesk.bottom - theApp.m_rectDesk.top, SWP_NOOWNERZORDER); // non mettere nè prima nè dopo, va bene qui //

	theApp.LocalizeDialog(this, CPostAcquisizioneDlg::IDD, "PostAcquisizioneDlg");

 	dlg.DestroyWindow();

	EndWaitCursor();

	if (m_ImgList.GetCount() < 1)
		EndDialog(IDCANCEL);

	return bReturn;
}

void CPostAcquisizioneDlg::OnOK()
{
	this->KillTimer(POSTACQUISIZIONE_TIMER);

	CEndoxResizableDlg::OnOK();
}

LRESULT CPostAcquisizioneDlg::OnImageSel(WPARAM wParam, LPARAM lParam)
{
	CString strSel;

	if ((int)lParam == 1)
		strSel.Format("%d " + theApp.GetMessageString(IDS_DOCUMENTOSELEZIONATO), (int)lParam);
	else
		strSel.Format("%d " + theApp.GetMessageString(IDS_DOCUMENTISELEZIONATI), (int)lParam);

	SetDlgItemText(IDC_STATIC_07, strSel);

	GetDlgItem(IDC_BTN_ELIMINA)->EnableWindow((int)lParam > 0);

	return (LRESULT)1;
}

void CPostAcquisizioneDlg::OnBnClickedBtnElimina()
{
	CThumbIDList* pList = m_ctrlListImage.GetSelectedThumb();

	// riordino la lista dei selezionati mettondoli in ordine di indice crescente //
	for(int i = 0; i < pList->GetCount(); i++)
	{
		POSITION minpos = pList->FindIndex(i);
		for(int j = i + 1; j < pList->GetCount(); j++)
		{
			if (pList->GetAt(pList->FindIndex(j)) < pList->GetAt(minpos))
				minpos = pList->FindIndex(j);
		}
		int nTemp = pList->GetAt(pList->FindIndex(i));
		pList->SetAt(pList->FindIndex(i), pList->GetAt(minpos));
		pList->SetAt(minpos, nTemp);
	}

	// imposto la stringa del messaggio //
	CString strMessage;
	if (pList->GetCount() == 1)
	{
		strMessage = theApp.GetMessageString(IDS_DOCUMENTOCONFERMAELIMINA);
	}
	else
	{
		CString strLabel;
		GetDlgItemText(IDC_STATIC_07, strLabel);

		strMessage = theApp.GetMessageString(IDS_ELIMINARE123) + " " + strLabel + "?";
	}

	// mostro il messaggio //
	if (theApp.MessageBoxEndo(strMessage, theApp.GetMessageString(IDS_ACHTUNG), MB_YESNO | MB_ICONSTOP) == IDYES)
	{
		//
		BeginWaitCursor();

		// Sandro 05/07/2012 //
		CString sMessage;
		sMessage.Format(theApp.GetMessageString(IDS_ACQUISIZIONE_MESSAGGIO2), pList->GetCount());
		CInsertLogAcquisizioneSPSet().Exec(m_pEsamiView->m_pPazientiSet->m_lContatore, m_pEsamiView->m_pEsamiSet->m_lContatore, theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, sMessage);

		// parto dall'ultimo selezionato //
		POSITION pos = pList->GetTailPosition();
		while(pos != NULL)
		{
			// cancello il file da hd //
			BOOL bDeleted = FALSE;
			int nTry = 0;
			
			CString strFile1 = m_ctrlListImage.GetDescription(pList->GetAt(pos));
			int nCapoIndex = strFile1.Find('\n');
			strFile1 = theApp.m_sDirTempAcq + "\\" + strFile1.Left(nCapoIndex);
			CString strFile2 = strFile1.Left(strFile1.GetLength() - 4) + ".DEL";
			while(nTry < 5)
			{
				MoveFile(strFile1, strFile2);
				bDeleted = DeleteFile(strFile2);

				if (bDeleted)
				{
					// cancello immagine anche dalla lista //
					m_ctrlListImage.DeleteItem(pList->GetAt(pos));
					break;
				}

				nTry++;
				Sleep(250);
			}
			
			// vado al precedente //
			pList->GetPrev(pos);
		}

		// aggiorno la lista in base a tutte le modifiche fatte //
		m_ctrlListImage.SetThumbs(&m_ImgList);		
		SendMessage(EPM_IMAGESEL_NOTIFY, 0, 0);

		// aggiorno dimensione files acquisiti //
		CalcolaDimensioni(NULL);

		// aggiorno spazio libero su archivio //
		AggiornaSpazioLibero();

		EndWaitCursor();
	}
}

void CPostAcquisizioneDlg::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);

	switch(nIDEvent)
	{
		case POSTACQUISIZIONE_TIMER:
		{
			AggiornaSpazioLibero();

			break;
		}
	}
}

void CPostAcquisizioneDlg::AggiornaSpazioLibero()
{
	char szPathImm[MAX_PATH];
	char szPathMin[MAX_PATH];
	if (CImgArchive(&theApp.m_dbEndox).GetArchivePrimary(szPathImm, szPathMin, MAX_PATH))
	{
		ULARGE_INTEGER uFreeBytesAvailable, uTotalNumberOfBytes, uTotalNumberOfFreeBytes;
		if (::GetDiskFreeSpaceEx(szPathImm /*theApp.m_sPathImageHD*/, &uFreeBytesAvailable, &uTotalNumberOfBytes, &uTotalNumberOfFreeBytes))
		{
			CString strTemp;
			double fMBytesFree1 = (double)((uFreeBytesAvailable.LowPart + ((LONGLONG)uFreeBytesAvailable.HighPart << 32)) / (1024*1024));
			double fMBytesFree2 = fMBytesFree1 - m_dTotFileSize;
			double fMBytesTotal = (double)((uTotalNumberOfBytes.LowPart + ((LONGLONG)uTotalNumberOfBytes.HighPart << 32)) / (1024*1024));
			int nPercent1 = (int)(fMBytesFree1 / fMBytesTotal * 100.0f);
			int nPercent2 = (int)(fMBytesFree2 / fMBytesTotal * 100.0f);
			
			strTemp.Format("%.2lf Mb (%d%%)", fMBytesFree1, nPercent1);
			SetDlgItemText(IDC_STATIC_02, strTemp);
			
			strTemp.Format("%.2lf Mb (%d%%)", fMBytesFree2, nPercent2);
			SetDlgItemText(IDC_STATIC_06, strTemp);

			if (nPercent1 > 5)
			{
				m_color1 = theApp.m_color[2];
				GetDlgItem(IDC_STATIC_01)->SetFont(&theApp.m_fontNormal);
				GetDlgItem(IDC_STATIC_02)->SetFont(&theApp.m_fontNormal);
			}
			else if (nPercent1 > 1)
			{
				m_color1 = theApp.m_color[1];
				GetDlgItem(IDC_STATIC_01)->SetFont(&theApp.m_fontBold);
				GetDlgItem(IDC_STATIC_02)->SetFont(&theApp.m_fontBold);
			}
			else
			{
				m_color1 = theApp.m_color[0];
				GetDlgItem(IDC_STATIC_01)->SetFont(&theApp.m_fontBig);
				GetDlgItem(IDC_STATIC_02)->SetFont(&theApp.m_fontBig);
			}

			if (nPercent2 > 5)
			{
				m_color2 = theApp.m_color[2];
				GetDlgItem(IDC_STATIC_05)->SetFont(&theApp.m_fontNormal);
				GetDlgItem(IDC_STATIC_06)->SetFont(&theApp.m_fontNormal);
			}
			else if (nPercent2 > 1)
			{
				m_color2 = theApp.m_color[1];
				GetDlgItem(IDC_STATIC_05)->SetFont(&theApp.m_fontBold);
				GetDlgItem(IDC_STATIC_06)->SetFont(&theApp.m_fontBold);
			}
			else
			{
				m_color2 = theApp.m_color[0];
				GetDlgItem(IDC_STATIC_05)->SetFont(&theApp.m_fontBig);
				GetDlgItem(IDC_STATIC_06)->SetFont(&theApp.m_fontBig);
			}
		}
	}
	else
	{
		ASSERT(FALSE);
	}
}

void CPostAcquisizioneDlg::CalcolaDimensioni(CModelessDlg* pDlg)
{
	if (pDlg != NULL)
	{
		m_dTotFileSize = 0;

		// importo solo i files dell'esame corrente //
		CString strWildcard;
		strWildcard.Format("%s\\%08d_%08d_*.*",
			theApp.m_sDirTempAcq,
			m_pEsamiView->m_pEsamiSet->m_lPaziente,
			m_pEsamiView->m_pEsamiSet->m_lContatore);

		//
		int iNumeroFile = 0;

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
					strFile = strFile.Right(3);
					if ((strFile.CompareNoCase("bmp") == 0) || (strFile.CompareNoCase("mpg") == 0) || (strFile.CompareNoCase("avi") == 0) || (strFile.Right(3).CompareNoCase("mp4") == 0) || (strFile.CompareNoCase("dcm") == 0))
						iNumeroFile++;
				}
			} while (FindNextFile(hFile, &dataFile));
		}
		FindClose(hFile);

		//
		pDlg->m_ctrlProgress.SetRange(0, iNumeroFile);
		pDlg->m_ctrlProgress.SetPos(0);

		//
		hFile = FindFirstFile(strWildcard, &dataFile);
		if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
		{
			do
			{
				CString strFile(dataFile.cFileName);

				if (strFile.GetLength() > 3)
				{
					if (strFile.Right(3).CompareNoCase("bmp") == 0)
					{
						CString strComment;
						strComment.Format("%s\n%.2lf Mb", strFile, (double)((((LONGLONG)dataFile.nFileSizeHigh) << 32) + (LONGLONG)dataFile.nFileSizeLow) / (1024.0f * 1024.0f));

						pDlg->SetInfo(strFile);

						HBITMAP hBitNor;
						HBITMAP hBitSel;
						if (m_pEsamiView->m_pImgManager->LoadLocalImageEx(theApp.m_sDirTempAcq + "\\" + strFile, &hBitNor, &hBitSel, HSIZE_PAL_4, VSIZE_PAL_4) > 0)
						{
							IMG imgTemp;

							imgTemp.lID = 0;
							imgTemp.type = _image_;
							imgTemp.hBmp = hBitNor;
							imgTemp.hBmpSelected = hBitSel;
							memcpy(imgTemp.szDescription, strComment.GetBuffer(), strComment.GetLength() + 1);

							m_ImgList.AddTail(imgTemp);
						}

						m_dTotFileSize += (double)((((LONGLONG)dataFile.nFileSizeHigh) << 32) + (LONGLONG)dataFile.nFileSizeLow) / (1024.0f * 1024.0f);

						// Sandro // 08/07/2011 //
						// DeleteObject(hBitNor);
						// DeleteObject(hBitSel);
						// non posso cancellarli qui altrimenti le immagini in lista vengono tutte nere //
					}

					if ((strFile.Right(3).CompareNoCase("mpg") == 0) || (strFile.Right(3).CompareNoCase("avi") == 0) || (strFile.Right(3).CompareNoCase("mp4") == 0))
					{
						CString strComment;
						strComment.Format("%s\n%.2lf Mb", strFile, (double)((((LONGLONG)dataFile.nFileSizeHigh) << 32) + (LONGLONG)dataFile.nFileSizeLow) / (1024.0f * 1024.0f));

						pDlg->SetInfo(strFile);

						HBITMAP hBitNor;
						HBITMAP hBitSel;
						if (m_pEsamiView->m_pImgManager->LoadLocalMovie(theApp.m_sDirTempAcq + "\\" + strFile, &hBitNor, &hBitSel, HSIZE_PAL_4, VSIZE_PAL_4))
						{
							IMG imgTemp;

							imgTemp.lID = 0;
							imgTemp.type = _movie_;
							imgTemp.hBmp = hBitNor;
							imgTemp.hBmpSelected = hBitSel;
							memcpy(imgTemp.szDescription, strComment.GetBuffer(), strComment.GetLength() + 1);

							m_ImgList.AddTail(imgTemp);
						}

						m_dTotFileSize += (double)((((LONGLONG)dataFile.nFileSizeHigh) << 32) + (LONGLONG)dataFile.nFileSizeLow) / (1024.0f * 1024.0f);
					}

					if (strFile.Right(3).CompareNoCase("dcm") == 0)
					{
						CString strComment;
						strComment.Format("%s\n%.2lf Mb", strFile, (double)((((LONGLONG)dataFile.nFileSizeHigh) << 32) + (LONGLONG)dataFile.nFileSizeLow) / (1024.0f * 1024.0f));

						pDlg->SetInfo(strFile);

						HBITMAP hBitNor;
						HBITMAP hBitSel;
						if (m_pEsamiView->m_pImgManager->LoadLocalDicom(theApp.m_sDirTempAcq + "\\" + strFile, &hBitNor, &hBitSel, HSIZE_PAL_4, VSIZE_PAL_4))
						{
							IMG imgTemp;

							imgTemp.lID = 0;
							imgTemp.type = _dicom_;
							imgTemp.hBmp = hBitNor;
							imgTemp.hBmpSelected = hBitSel;
							memcpy(imgTemp.szDescription, strComment.GetBuffer(), strComment.GetLength() + 1);

							m_ImgList.AddTail(imgTemp);
						}

						m_dTotFileSize += (double)((((LONGLONG)dataFile.nFileSizeHigh) << 32) + (LONGLONG)dataFile.nFileSizeLow) / (1024.0f * 1024.0f);
					}
				}
			} while(FindNextFile(hFile, &dataFile));
		}
		FindClose(hFile);

		//
		m_ctrlListImage.SetThumbs(&m_ImgList);

		// aggiorno etichetta //
		CString strTmp;
		strTmp.Format("%.2lf Mb", m_dTotFileSize);
		SetDlgItemText(IDC_STATIC_04, strTmp);
	}
	else
	{
		m_dTotFileSize = 0;

		//
		WIN32_FIND_DATA dataFile;
		HANDLE hFile = FindFirstFile(theApp.m_sDirTempAcq + "\\*.*", &dataFile);
		if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
		{
			do
			{
				CString strFile(dataFile.cFileName);

				if (strFile.GetLength() > 3)
				{
					strFile = strFile.Right(3);

					if (strFile.CompareNoCase("bmp") == 0)
						m_dTotFileSize += (double)((((LONGLONG)dataFile.nFileSizeHigh) << 32) + (LONGLONG)dataFile.nFileSizeLow) / (1024.0f * 1024.0f);
					else if (strFile.CompareNoCase("mpg") == 0)
						m_dTotFileSize += (double)((((LONGLONG)dataFile.nFileSizeHigh) << 32) + (LONGLONG)dataFile.nFileSizeLow) / (1024.0f * 1024.0f);
					else if (strFile.CompareNoCase("avi") == 0)
						m_dTotFileSize += (double)((((LONGLONG)dataFile.nFileSizeHigh) << 32) + (LONGLONG)dataFile.nFileSizeLow) / (1024.0f * 1024.0f);
					else if (strFile.CompareNoCase("mp4") == 0)
						m_dTotFileSize += (double)((((LONGLONG)dataFile.nFileSizeHigh) << 32) + (LONGLONG)dataFile.nFileSizeLow) / (1024.0f * 1024.0f);
					else if (strFile.CompareNoCase("dcm") == 0)
						m_dTotFileSize += (double)((((LONGLONG)dataFile.nFileSizeHigh) << 32) + (LONGLONG)dataFile.nFileSizeLow) / (1024.0f * 1024.0f);
				}
			} while(FindNextFile(hFile, &dataFile));
		}
		FindClose(hFile);

		// aggiorno etichetta //
		CString strTmp;
		strTmp.Format("%.2lf Mb", m_dTotFileSize);
		SetDlgItemText(IDC_STATIC_04, strTmp);
	}
}
