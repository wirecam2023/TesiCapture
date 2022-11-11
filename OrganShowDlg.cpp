#include "stdafx.h"
#include "Endox.h"
#include "OrganShowDlg.h"

#include "DLL_Imaging\h\ImgArchive.h"

#include "EditStringDlg.h"
#include "EsamiView.h"
#include "FileBmp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

COrganShowDlg::COrganShowDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(COrganShowDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;

	m_setOrgani.SetSortRecord("ID");
	m_setOrgani.OpenRecordset("COrganShowDlg::COrganShowDlg");

	m_bIsPrevActive = FALSE;
	m_bIsNextActive = FALSE;
	m_bIsRecycleActive = FALSE;
}

COrganShowDlg::~COrganShowDlg(void)
{
	m_setOrgani.CloseRecordset("COrganShowDlg::~COrganShowDlg");
}

BEGIN_MESSAGE_MAP(COrganShowDlg, CDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()

	ON_BN_CLICKED(IDC_FRST_ORG, OnFrstOrg)
	ON_BN_CLICKED(IDC_PREV_ORG, OnPrevOrg)
	ON_BN_CLICKED(IDC_NEXT_ORG, OnNextOrg)
	ON_BN_CLICKED(IDC_LAST_ORG, OnLastOrg)
	ON_BN_CLICKED(IDC_BTN_NWIM, OnBtnNwIm)
	ON_BN_CLICKED(IDC_BTN_DLIM, OnBtnDlIm)
END_MESSAGE_MAP()

void COrganShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDOK, m_ctrlButtonOK);

	DDX_Text(pDX, IDC_COMMENTO, m_setOrgani.m_sDescrizione);

	if ((m_setOrgani.IsBOF() == TRUE) && (m_setOrgani.IsEOF() == TRUE))
	{
		m_bIsPrevActive = FALSE;
		m_bIsNextActive = FALSE;
		m_bIsRecycleActive = FALSE;
	}
	else
	{
		if (m_setOrgani.IsBOF() == TRUE)
		{
			m_bIsPrevActive = FALSE;
			m_bIsNextActive = TRUE;
		}
		else
		{
			if (m_setOrgani.IsEOF() == TRUE)
			{
				m_bIsPrevActive = TRUE;
				m_bIsNextActive = FALSE;
			}
			else
			{
				m_setOrgani.MovePrev();

				if (m_setOrgani.IsBOF() == TRUE)
					m_bIsPrevActive = FALSE;
				else
					m_bIsPrevActive = TRUE;

				m_setOrgani.MoveNext();
				m_setOrgani.MoveNext();

				if (m_setOrgani.IsEOF() == TRUE)
					m_bIsNextActive = FALSE;
				else
					m_bIsNextActive = TRUE;

				m_setOrgani.MovePrev();
			}
		}

		m_bIsRecycleActive = TRUE;
	}

	GetDlgItem(IDC_FRST_ORG)->EnableWindow(m_bIsPrevActive);
	GetDlgItem(IDC_PREV_ORG)->EnableWindow(m_bIsPrevActive);
	GetDlgItem(IDC_NEXT_ORG)->EnableWindow(m_bIsNextActive);
	GetDlgItem(IDC_LAST_ORG)->EnableWindow(m_bIsNextActive);
	GetDlgItem(IDC_BTN_DLIM)->EnableWindow(m_bIsRecycleActive);
}

void COrganShowDlg::OnFrstOrg() 
{
	BeginWaitCursor();
	m_setOrgani.MoveFirst();
    MoveImageOrg();
	EndWaitCursor();
}

void COrganShowDlg::OnPrevOrg() 
{
	BeginWaitCursor();
	m_setOrgani.MovePrev();
	MoveImageOrg();
	EndWaitCursor();
}

void COrganShowDlg::OnNextOrg() 
{
	BeginWaitCursor();
	m_setOrgani.MoveNext();
	MoveImageOrg();
	EndWaitCursor();
}

void COrganShowDlg::OnLastOrg() 
{
	BeginWaitCursor();
	m_setOrgani.MoveLast();
	MoveImageOrg();
	EndWaitCursor();
}

BOOL COrganShowDlg::OnInitDialog() 
{
	BOOL bReturn = CDialog::OnInitDialog();

	m_BtnOrgFirst.AutoLoad(IDC_FRST_ORG, this);
	m_BtnOrgPrev.AutoLoad(IDC_PREV_ORG, this);
	m_BtnOrgNext.AutoLoad(IDC_NEXT_ORG, this);
	m_BtnOrgLast.AutoLoad(IDC_LAST_ORG, this);
	m_BtnNwIm.AutoLoad(IDC_BTN_NWIM, this);
	m_BtnDlIm.AutoLoad(IDC_BTN_DLIM, this);

    MoveImageOrg();

	theApp.LocalizeDialog(this, COrganShowDlg::IDD, "OrganShow");
	SetWindowText(theApp.GetMessageString(IDS_ORGANSHOW_TITLE_2));

	return bReturn;
}

void COrganShowDlg::MoveImageOrg()
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
			if (m_pEsamiView->m_pImgManager->LoadLocalImageEx(strOrganFile, &hBit) > 0)
				if (hBit != INVALID_HANDLE_VALUE)
					bOk = m_Dib.Attach(CDib::BitmapToDIB(hBit, NULL), TRUE);
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

	UpdateData(FALSE);
	this->RedrawWindow();
}

void COrganShowDlg::OnBtnNwIm() 
{
	CFileDialog FileDlg(TRUE, NULL, NULL, 0, "Tutti i file|*.*|Bitmap (*.bmp)|*.bmp|JPEG (*.jpg;*.jpeg)|*.jpg; *.jpeg|JPEG 2000 (*.jp2)|*.jp2|Tagged Image File Format (*.tif;*.tiff)|*.tif; *.tiff|CompuServe Graphics Interchange (*.gif)|*.gif|", this, 0, FALSE);
	if (FileDlg.DoModal() == IDOK)
	{
		CString strSource = FileDlg.GetPathName();
		if (!strSource.IsEmpty())
		{
			HBITMAP hBit;
			if (m_pEsamiView->m_pImgManager->LoadLocalImageEx(strSource, &hBit) > 0)
			{
				BOOL bOk = (hBit != INVALID_HANDLE_VALUE);
				DeleteObject(hBit);

				if (bOk)
				{
					// caricamento andato a buon fine quindi il file è valido //

					COrganiSet setOrganiTemp;
					if (setOrganiTemp.OpenRecordset("COrganShowDlg::OnBtnNwIm"))
					{
						if (setOrganiTemp.AddNewRecordset("COrganShowDlg::OnBtnNwIm"))
						{
							setOrganiTemp.m_sDescrizione = "NUOVO";
							if (setOrganiTemp.UpdateRecordset("COrganShowDlg::OnBtnNwIm"))
							{
								// l'inserimento su DB è OK quindi copio il file //
								char szPathImm[MAX_PATH];
								char szPathMin[MAX_PATH];
								if (CImgArchive(&theApp.m_dbEndox).GetArchivePrimary(szPathImm, szPathMin, MAX_PATH))
								{
									CString strDest;
									strDest.Format("%s\\Organ\\%06li.org", szPathImm /*theApp.m_sPathImageHD*/, setOrganiTemp.GetLastAdd());

									CopyFile(strSource, strDest, TRUE);

									if (m_setOrgani.IsOpen())
										m_setOrgani.CloseRecordset("COrganShowDlg::OnBtnNwIm");
									m_setOrgani.OpenRecordset("COrganShowDlg::OnBtnNwIm");
									OnLastOrg();
								}
								else
								{
									ASSERT(FALSE);
								}
							}
						}
						setOrganiTemp.CloseRecordset("COrganShowDlg::OnBtnNwIm");
					}
				}
			}
			else
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_INVALID_FILE_FORMAT));
			}
		}
	}
}

void COrganShowDlg::OnBtnDlIm() 
{
    if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ORGANSHOW_CONFIRM_DELETE), MB_YESNO) == IDYES)
	{
	    if (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ORGANSHOW_CONFIRM_DELETE_2), MB_YESNO) == IDNO)
		{
			char szPathImm[MAX_PATH];
			char szPathMin[MAX_PATH];
			if (CImgArchive(&theApp.m_dbEndox).GetArchivePrimary(szPathImm, szPathMin, MAX_PATH))
			{
				CString strDeleteFile;
				strDeleteFile.Format("%s\\Organ\\%06li.org", szPathImm /*theApp.m_sPathImageHD*/, m_setOrgani.m_lID);
				DeleteFile(strDeleteFile);

				if (m_setOrgani.DeleteRecordset("COrganShowDlg::OnBtnDlIm"))
				{
					m_setOrgani.CloseRecordset("COrganShowDlg::OnBtnDlIm");
					m_setOrgani.OpenRecordset("COrganShowDlg::OnBtnDlIm");

					if (m_setOrgani.IsEOF() == FALSE)
						m_setOrgani.MoveLast();
				}

				MoveImageOrg();
			}
			else
			{
				ASSERT(FALSE);
			}
		}
	}
}

void COrganShowDlg::OnPaint() 
{
	CPaintDC dc(this);

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
}

void COrganShowDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rectCommento;
	GetDlgItem(IDC_COMMENTO_BORDO)->GetWindowRect(rectCommento);
	ScreenToClient(rectCommento);
	rectCommento.DeflateRect(1, 1);

	TRACE("-> rect(T %d, L %d, B %d, R %d) - point(X %d, Y %d)\n", rectCommento.top, rectCommento.left, rectCommento.bottom, rectCommento.right, point.x, point.y);

	if (rectCommento.PtInRect(point) == TRUE)
	{
		if ((m_setOrgani.IsBOF() == FALSE) && (m_setOrgani.IsEOF() == FALSE))
		{
			CEditStringDlg dlg(this, theApp.GetMessageString(IDS_MODIFY_COMMENT), m_setOrgani.m_sDescrizione);

			if (dlg.DoModal() == IDOK)
			{
				if (m_setOrgani.EditRecordset("COrganShowDlg::OnClickedCommento") == TRUE)
				{
					m_setOrgani.m_sDescrizione = dlg.GetValue();

					m_setOrgani.UpdateRecordset("COrganShowDlg::OnClickedCommento");
				}
			}

			UpdateData(FALSE);
		}
	}

	CDialog::OnLButtonDown(nFlags, point);
}
