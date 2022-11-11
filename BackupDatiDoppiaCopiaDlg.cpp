#include "stdafx.h"
#include "Endox.h"
#include "BackupDatiDoppiaCopiaDlg.h"

#include "DLL_Imaging\h\AmImgBackup.h"
#include "RobotSelezioneDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CBackupDatiDoppiaCopiaDlg, CDialog)

CBackupDatiDoppiaCopiaDlg::CBackupDatiDoppiaCopiaDlg(CWnd* pParent, CEsamiView* pEsamiView)
	: CDialog(CBackupDatiDoppiaCopiaDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
}

CBackupDatiDoppiaCopiaDlg::~CBackupDatiDoppiaCopiaDlg()
{
}

void CBackupDatiDoppiaCopiaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_COPIA,   m_ctrlButton1);
	DDX_Control(pDX, IDC_BTN_SECONDA, m_ctrlButton2);
	DDX_Control(pDX, IDC_BTN_LIBERA,  m_ctrlButton3);
	DDX_Control(pDX, IDOK,            m_ctrlButton4);
}

BEGIN_MESSAGE_MAP(CBackupDatiDoppiaCopiaDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_COPIA,   OnClickedBtnCopia)
	ON_BN_CLICKED(IDC_BTN_SECONDA, OnClickedBtnSeconda)
	ON_BN_CLICKED(IDC_BTN_LIBERA,  OnClickedBtnLibera)
END_MESSAGE_MAP()

BOOL CBackupDatiDoppiaCopiaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	theApp.LocalizeDialog(this, CBackupDatiDoppiaCopiaDlg::IDD, "BackupDatiDlg");
	return TRUE;
}

void CBackupDatiDoppiaCopiaDlg::OnClickedBtnCopia()
{
	if (theApp.m_bCanWriteDVD || theApp.m_bRobotAttivo)
	{
		#ifdef _DEBUG
			HMODULE hModule = ::LoadLibrary("AmImgBackupD.dll");
		#else
			HMODULE hModule = ::LoadLibrary("AmImgBackup.dll");
		#endif

		if (hModule == NULL)
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMGBACKUP_NODLL), MB_ICONSTOP);

			return; // FALSE;
		}

		AmImgBackup_EnableLocalization_PTR AmImgBackup_EnableLocalization = (AmImgBackup_EnableLocalization_PTR)::GetProcAddress(hModule, _AmImgBackup_EnableLocalization_FUNCTION);
		if (AmImgBackup_EnableLocalization == NULL)
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMGBACKUP_NOFUNCTION), MB_ICONSTOP);

			return; // FALSE;
		}

		AmImgBackup_EnableLocalization(theApp.GetMessageString, theApp.LocalizeDialog);

		if (theApp.m_sBackupDevicePath.Right(1) == "\\")
			theApp.m_sBackupDevicePath = theApp.m_sBackupDevicePath.Left(theApp.m_sBackupDevicePath.GetLength() - 1);

		if (theApp.m_bRobotAttivo && theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_RIMAGE_BURNER), MB_YESNO) == IDYES)
		{
			OpenTransferProcedureRimage_MFC_PTR OpenTransferProcedureRimage_MFC = (OpenTransferProcedureRimage_MFC_PTR)::GetProcAddress(hModule, _OpenTransferProcedureRimage_MFC_FUNCTION);
			if (OpenTransferProcedureRimage_MFC == NULL)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMGBACKUP_NOFUNCTION), MB_ICONSTOP);

				return; // FALSE;
			}

			CRobotSelezioneDlg selDlg;
			selDlg.DoModal();

			OpenTransferProcedureRimage_MFC(theApp.m_sNomeComputer, 
											theApp.m_sUtenteLoggato, 
											theApp.m_sNomeImpianto,
											&theApp.m_dbEndox,
											selDlg.m_sHost,
											selDlg.m_lPort,
											TYPE_DVD,
											"",
											selDlg.m_sBackupLabelPath,
											selDlg.m_sTempDirectoryPath,
											selDlg.m_sMergeDirectoryPath,
											selDlg.m_bSimulationMode
											);
		}
		else
		{
			if (theApp.m_bCanWriteDVD)
			{
				OpenTransferProcedure_MFC_PTR OpenTransferProcedure_MFC = (OpenTransferProcedure_MFC_PTR)::GetProcAddress(hModule, _OpenTransferProcedure_MFC_FUNCTION);
				if (OpenTransferProcedure_MFC == NULL)
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMGBACKUP_NOFUNCTION), MB_ICONSTOP);

					return; // FALSE;
				}

				OpenTransferProcedure_MFC(theApp.m_sUtenteLoggato, 
									  theApp.m_sNomeComputer, 
									  theApp.m_sNomeImpianto,
									  theApp.m_sBackupDevicePath,
									  theApp.m_sDirTemp,
									  FALSE,
									  "",
									  "",
									  &theApp.m_dbEndox,
									  theApp.m_lBackupDeviceID,
									  1); // 0=CD - 1=DVD //
			}
			else
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DVD_BURNER_NEEDED));		
			}
		}

		::FreeLibrary(hModule);
	}
	else
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DVD_BURNER_NEEDED));
		OnOK();
	}
}

void CBackupDatiDoppiaCopiaDlg::OnClickedBtnSeconda()
{
	if (theApp.m_bCanWriteDVD || theApp.m_bRobotAttivo)
	{
		#ifdef _DEBUG
			HMODULE hModule = ::LoadLibrary("AmImgBackupD.dll");
		#else
			HMODULE hModule = ::LoadLibrary("AmImgBackup.dll");
		#endif

		if (hModule == NULL)
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMGBACKUP_NODLL), MB_ICONSTOP);

			return; // FALSE;
		}

		AmImgBackup_EnableLocalization_PTR AmImgBackup_EnableLocalization = (AmImgBackup_EnableLocalization_PTR)::GetProcAddress(hModule, _AmImgBackup_EnableLocalization_FUNCTION);
		if (AmImgBackup_EnableLocalization == NULL)
		{
			theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMGBACKUP_NOFUNCTION), MB_ICONSTOP);

			return; // FALSE;
		}

		AmImgBackup_EnableLocalization(theApp.GetMessageString, theApp.LocalizeDialog);

		if (theApp.m_bRobotAttivo && theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_RIMAGE_BURNER), MB_YESNO) == IDYES)
		{
			OpenSupportCopyProcedureRimage_MFC_PTR OpenSupportCopyProcedureRimage_MFC = (OpenSupportCopyProcedureRimage_MFC_PTR)::GetProcAddress(hModule, _OpenSupportCopyProcedureRimage_MFC_FUNCTION);
			if (OpenSupportCopyProcedureRimage_MFC == NULL)
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMGBACKUP_NOFUNCTION), MB_ICONSTOP);

				return; // FALSE;
			}

			CRobotSelezioneDlg selDlg;
			selDlg.DoModal();

			OpenSupportCopyProcedureRimage_MFC(theApp.m_sNomeComputer, 
												theApp.m_sUtenteLoggato, 
												theApp.m_sNomeImpianto,
												&theApp.m_dbEndox,
												selDlg.m_sHost,
												selDlg.m_lPort,
												TYPE_DVD,
												"",
												selDlg.m_sBackupLabelPath,
												selDlg.m_sTempDirectoryPath,
												selDlg.m_sMergeDirectoryPath,
												selDlg.m_bSimulationMode
												);
		}
		else
		{
			if (theApp.m_bCanWriteDVD)
			{
				OpenSupportCopyProcedure_MFC_PTR OpenSupportCopyProcedure_MFC = (OpenSupportCopyProcedure_MFC_PTR)::GetProcAddress(hModule, _OpenSupportCopyProcedure_MFC_FUNCTION);
				if (OpenSupportCopyProcedure_MFC == NULL)
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMGBACKUP_NOFUNCTION), MB_ICONSTOP);

					return; // FALSE;
				}

				OpenSupportCopyProcedure_MFC(theApp.m_sUtenteLoggato, 
										 theApp.m_sNomeComputer, 
										 theApp.m_sNomeImpianto,
										 theApp.m_sBackupDevicePath,
										 theApp.m_sDirTemp + "\\",
										 &theApp.m_dbEndox,
										 theApp.m_lBackupDeviceID,
										 1); // 0=CD - 1=DVD //
			}
			else
			{
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DVD_BURNER_NEEDED));		
			}
		}

		::FreeLibrary(hModule);
	}
	else
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_DVD_BURNER_NEEDED));
		OnOK();
	}
}

void CBackupDatiDoppiaCopiaDlg::OnClickedBtnLibera()
{
	#ifdef _DEBUG
		HMODULE hModule = ::LoadLibrary("AmImgBackupD.dll");
	#else
		HMODULE hModule = ::LoadLibrary("AmImgBackup.dll");
	#endif

	if (hModule == NULL)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMGBACKUP_NODLL), MB_ICONSTOP);

		return; // FALSE;
	}

	AmImgBackup_EnableLocalization_PTR AmImgBackup_EnableLocalization = (AmImgBackup_EnableLocalization_PTR)::GetProcAddress(hModule, _AmImgBackup_EnableLocalization_FUNCTION);
	if (AmImgBackup_EnableLocalization == NULL)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMGBACKUP_NOFUNCTION), MB_ICONSTOP);

		return; // FALSE;
	}

	AmImgBackup_EnableLocalization(theApp.GetMessageString, theApp.LocalizeDialog);

	OpenConfirmTransferProcedure_MFC_PTR OpenConfirmTransferProcedure_MFC = (OpenConfirmTransferProcedure_MFC_PTR)::GetProcAddress(hModule, _OpenConfirmTransferProcedure_MFC_FUNCTION);
	if (OpenConfirmTransferProcedure_MFC == NULL)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_IMGBACKUP_NOFUNCTION), MB_ICONSTOP);

		return; // FALSE;
	}

	OpenConfirmTransferProcedure_MFC(theApp.m_sUtenteLoggato, theApp.m_sNomeComputer, theApp.m_sNomeImpianto, "Z:", &theApp.m_dbEndox);

	::FreeLibrary(hModule);
}
