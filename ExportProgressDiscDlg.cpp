#include "stdafx.h"
#include "Endox.h"
#include "ExportProgressDiscDlg.h"

#include "DLL_Imaging\h\AmRes.h"
#include "EsamiView.h"
#include "EsamiSet.h"
#include "FileBmp.h"
#include <io.h>
#include <errno.h>
#include <direct.h>
#include "ObSelect.h"
#include "EspelliDlg.h"
#include "WaitBurnCDDlg.h"
#include "SelezioneMasterizzatoreDlg.h"
#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CExportProgressDiscDlg, CDialog)

CExportProgressDiscDlg::CExportProgressDiscDlg(CWnd* pParent, CEsamiView* pEsamiView, int iNumExp, int iDiscType)
	: CDialog(CExportProgressDiscDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;

	m_iNumExp = iNumExp;
	m_iDiscType = iDiscType;

	m_bInterrompi = FALSE;

	m_pImageList = new CImageList;
	m_pImageList->Create(16, 16, ILC_COLOR32, 0, 1);
	m_pImageList->SetImageCount(4);

	m_pImageList->Replace(0, LoadIcon(NULL, MAKEINTRESOURCE(IDI_INFORMATION)));
	m_pImageList->Replace(1, LoadIcon(NULL, MAKEINTRESOURCE(IDI_ERROR)));
	m_pImageList->Replace(2, LoadIcon(NULL, MAKEINTRESOURCE(IDI_EXCLAMATION)));
	m_pImageList->Replace(3, LoadIcon(NULL, MAKEINTRESOURCE(IDI_QUESTION)));

	m_pWaitCDDlg = NULL;
}

CExportProgressDiscDlg::~CExportProgressDiscDlg()
{
	delete m_pImageList;
}

void CExportProgressDiscDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PROGRESS1, m_ctrlProgress1);
	DDX_Control(pDX, IDC_PROGRESS2, m_ctrlProgress2);
	DDX_Control(pDX, IDC_PROGRESS3, m_ctrlProgress3);
	DDX_Control(pDX, IDC_LIST, m_ctrlListEvents);

	DDX_Control(pDX, IDC_STATIC_1, m_ctrlStatic1);
	DDX_Control(pDX, IDC_STATIC_2, m_ctrlStatic2);
	DDX_Control(pDX, IDC_STATIC_3, m_ctrlStatic3);
	DDX_Control(pDX, IDC_BTN_INTERROMPI, m_ctrlBtnInterrompi);
}

BEGIN_MESSAGE_MAP(CExportProgressDiscDlg, CDialog)

	ON_WM_TIMER()

	ON_BN_CLICKED(IDC_BTN_INTERROMPI, OnBnClickedBtnInterrompi)

	ON_MESSAGE(AMBURN_NOTIFICATION, OnBurnNotification)
	ON_MESSAGE(AMBURN_USER_INTERACTION, OnUserNotification)

END_MESSAGE_MAP()

BOOL CExportProgressDiscDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowText(m_iDiscType == DISC_CD ? theApp.GetMessageString(IDS_EXPORTING_ON_CD) : theApp.GetMessageString(IDS_EXPORTING_ON_DVD));

	CRect rect;
	m_ctrlListEvents.GetClientRect(&rect);
	m_ctrlListEvents.InsertColumn(0, "Evento", 0, rect.Width() - GetSystemMetrics(SM_CXVSCROLL));
	m_ctrlListEvents.SetImageList(m_pImageList, LVSIL_SMALL);

	m_ctrlProgress1.SetRange(0, m_iNumExp);
	m_ctrlProgress1.SetPos(0);
	m_ctrlProgress2.SetRange(0, 100);
	m_ctrlProgress2.SetPos(0);
	m_ctrlProgress3.SetRange(0, m_iNumExp);
	m_ctrlProgress3.SetPos(0);

	SetTimer(EXPORT_TIMER, 500, NULL);

	return TRUE;
}

void CExportProgressDiscDlg::OnTimer(UINT nIDEvent)
{
	switch(nIDEvent)
	{
		case EXPORT_TIMER:
		{
			this->KillTimer(EXPORT_TIMER);

			ImpostaFase(FASE_1);

			break;
		}
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CExportProgressDiscDlg::OnBnClickedBtnInterrompi()
{
	m_bInterrompi = TRUE;

	GetDlgItem(IDC_BTN_INTERROMPI)->EnableWindow(FALSE);
}

void CExportProgressDiscDlg::ImpostaFase(int nFase)
{
	switch(nFase)
	{
		case FASE_1:
		{
			GetDlgItem(IDC_STATIC_1)->SetFont(&theApp.m_fontBold);

//			GetDlgItem(IDC_STATIC_DA1)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_DA)->ShowWindow(SW_SHOW);
//			GetDlgItem(IDC_STATIC_A1)->ShowWindow(SW_SHOW);
//			GetDlgItem(IDC_STATIC_A)->ShowWindow(SW_SHOW);

			GetDlgItem(IDC_PROGRESS1)->ShowWindow(SW_SHOW);

			ExportImmagini();

			break;
		}

		case FASE_2:
		{
			GetDlgItem(IDC_STATIC_1)->SetFont(&theApp.m_fontNormal);
			GetDlgItem(IDC_STATIC_2)->SetFont(&theApp.m_fontBold);

//			GetDlgItem(IDC_STATIC_DA1)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_DA)->ShowWindow(SW_HIDE);
//			GetDlgItem(IDC_STATIC_A1)->ShowWindow(SW_HIDE);
//			GetDlgItem(IDC_STATIC_A)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_LIST)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_PROGRESS1)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_PROGRESS2)->ShowWindow(SW_SHOW);

			MasterizzaSupporto();

			break;
		}

		case FASE_31:
		{
			GetDlgItem(IDC_STATIC_2)->SetFont(&theApp.m_fontNormal);
			GetDlgItem(IDC_STATIC_3)->SetFont(&theApp.m_fontBold);

			GetDlgItem(IDC_LIST)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_PROGRESS2)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_STATIC_DEL)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_PROGRESS2)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_PROGRESS3)->ShowWindow(SW_SHOW);

			DeleteDirectoryProgress(m_strPath, m_ctrlProgress3);

			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUMESAME_EXP_IMG_OK));
			CDialog::OnOK();

			break;
		}

		case FASE_32:
		{
			GetDlgItem(IDC_STATIC_1)->SetFont(&theApp.m_fontNormal);
			GetDlgItem(IDC_STATIC_2)->SetFont(&theApp.m_fontNormal);
			GetDlgItem(IDC_STATIC_3)->SetFont(&theApp.m_fontBold);

//			GetDlgItem(IDC_STATIC_DA1)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_DA)->ShowWindow(SW_HIDE);
//			GetDlgItem(IDC_STATIC_A1)->ShowWindow(SW_HIDE);
//			GetDlgItem(IDC_STATIC_A)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_LIST)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_PROGRESS1)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_PROGRESS2)->ShowWindow(SW_HIDE);

			GetDlgItem(IDC_STATIC_DEL)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_PROGRESS3)->ShowWindow(SW_SHOW);

			DeleteDirectoryProgress(m_strPath, m_ctrlProgress3);

			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_EXPORTING_ABORTED), MB_ICONSTOP);
			CDialog::OnOK();

			break;
		}
	}
}

void CExportProgressDiscDlg::MasterizzaSupporto()
{
	AMBurn_ActivateNotification(GetSafeHwnd(), AMBURN_NOTIFICATION, AMBURN_USER_INTERACTION);
	AMBurn_SetAbortFlag(&m_bInterrompi);

	// inizializzazione amburn
	if (!AMBurn_Initialize())
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_EXPORT_ERROR), MB_ICONSTOP);
		return;
	}

	CSelezioneMasterizzatoreDlg dlgMasterizzatore(this, m_iDiscType);
	dlgMasterizzatore.DoModal();
	long lDeviceID = dlgMasterizzatore.GetDeviceID();

	//CString strTemp = m_strPath.Left(m_strPath.GetLength() - 1);
	if (!AMBurn_BurnDirectory(lDeviceID, m_strPath, theApp.m_sNomeProgramma, TRUE, FALSE, m_iDiscType == DISC_CD ? FALSE : TRUE, FALSE, TRUE))
	{
		AMBurn_Finalize();
		ImpostaFase(FASE_32);
		return;
	}

	if (m_bInterrompi)
	{
		AMBurn_Finalize();
		ImpostaFase(FASE_32);
		return;
	}

	AMBurn_Finalize();
	ImpostaFase(FASE_31);
}

LRESULT CExportProgressDiscDlg::OnBurnNotification(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		case PROGRESS:
			m_ctrlProgress2.SetPos((int)lParam);
			break;

		case BUFFER_LEVEL:
			break;

		case DISABLE_ABORT:
			if (lParam)
				TRACE("You can Abort\n");
			else
				TRACE("You can't Abort\n");
			break;

		case MAJOR_PHASE:
			m_ctrlListEvents.InsertItem(m_ctrlListEvents.GetItemCount(), CString((TCHAR*)lParam), 0); // METTO INFO LO STESSO //
			//delete (TCHAR*)lParam;
			m_ctrlListEvents.Scroll(CSize(0, 50));
			break;

		case PHASE:
			m_ctrlListEvents.InsertItem(m_ctrlListEvents.GetItemCount(), CString((TCHAR*)lParam), 0); // METTO INFO LO STESSO //
			//delete (TCHAR*)lParam;
			m_ctrlListEvents.Scroll(CSize(0, 50));
			break;

		case LOG_LINE:
			TCHAR cIcon = *(TCHAR*)lParam;
			switch (cIcon)
			{
				case 'I':    // Info
					m_ctrlListEvents.InsertItem(m_ctrlListEvents.GetItemCount(), CString((TCHAR*)(lParam + 1)), 0);
					break;

				case 'S':    // Stop
					m_ctrlListEvents.InsertItem(m_ctrlListEvents.GetItemCount(), CString((TCHAR*)(lParam + 1)), 1);
					break;

				case 'E':    // Exclamation
					m_ctrlListEvents.InsertItem(m_ctrlListEvents.GetItemCount(), CString((TCHAR*)(lParam + 1)), 2);
					break;

				case 'Q':    // Question
					m_ctrlListEvents.InsertItem(m_ctrlListEvents.GetItemCount(), CString((TCHAR*)(lParam + 1)), 3);
					break;

				default:
				case 'D':    // Drive
				case 'F':    // File
				case 'U':    // Unspecified
					m_ctrlListEvents.InsertItem(m_ctrlListEvents.GetItemCount(), CString((TCHAR*)(lParam + 1)), 0); // METTO INFO LO STESSO //
					break;
			}
			//delete (TCHAR*)lParam;
			m_ctrlListEvents.Scroll(CSize(0, 50));
			break;
	}

	return 0;
}

LRESULT CExportProgressDiscDlg::OnUserNotification(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		case WAITCD_MEDIA_INFO:
			break;

		case WAITCD:
			if (m_pWaitCDDlg == NULL)
			{
				m_pWaitCDDlg = new CWaitBurnCDDlg(this);
				m_pWaitCDDlg->Create(CWaitBurnCDDlg::IDD, this);
				m_pWaitCDDlg->ShowWindow(SW_SHOW);
				EnableWindow(FALSE);
			}
			break;

		case WAITCD_REMINDER:
			break;

		case WAITCD_DONE:
			if (m_pWaitCDDlg)
			{
				m_pWaitCDDlg->DestroyWindow();
				delete m_pWaitCDDlg;
				m_pWaitCDDlg = NULL;
				EnableWindow(TRUE);
			}
			break;
	}

	return 0;
}

void CExportProgressDiscDlg::OnCancel() 
{
	// CDialog::OnCancel();
}

void CExportProgressDiscDlg::OnOK() 
{
	// CDialog::OnOK();
}
