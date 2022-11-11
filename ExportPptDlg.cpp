#include "stdafx.h"
#include "Endox.h"
#include "ExportPptDlg.h"

#include "Common.h"
#include "EsamiView.h"
#include "EspelliDlg.h"
#include "ExportDlg.h"
#include "Path.h"

/*
#include <direct.h>
#include <errno.h>
#include <io.h>

#include "DLL_Imaging\h\AmRes.h"

#include "EsamiSet.h"
#include "FileBmp.h"
#include "ObSelect.h"
#include "VistaImmaginiNumeroDermoxSet.h"
*/

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CExportPptDlg, CDialog)

CExportPptDlg::CExportPptDlg(CWnd* pParent, CExportDlg* pExportDlg, int iNumExp)
	: CDialog(CExportPptDlg::IDD, pParent)
{
	ASSERT(pExportDlg != NULL);

	m_pExportDlg = pExportDlg;
	m_iNumExp = iNumExp;

	m_bInterrompi = FALSE;
}

CExportPptDlg::~CExportPptDlg()
{
}

void CExportPptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PROGRESS1, m_ctrlProgress);
	DDX_Control(pDX, IDC_BTN_INTERROMPI, m_ctrlBtnInterrompi);
}

BEGIN_MESSAGE_MAP(CExportPptDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_INTERROMPI, OnBnClickedBtnInterrompi)
	ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL CExportPptDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctrlProgress.SetRange(0, m_iNumExp);
	m_ctrlProgress.SetPos(0);

	SetTimer(EXPORT_TIMER, 500, NULL);

	theApp.LocalizeDialog(this, CExportPptDlg::IDD, "ExportPptDlg");
	return TRUE;
}

void CExportPptDlg::OnBnClickedOk()
{
	// OnOK();
}

void CExportPptDlg::OnBnClickedCancel()
{
	// OnCancel();
}

void CExportPptDlg::ExportImmaginiSelezionate()
{
	BOOL bError = FALSE;
	MSG msg;

	POSITION pos = m_pExportDlg->m_ListPathDiapo.GetHeadPosition();
	CPath* pPath = NULL;

	if (bError == FALSE)
	{
		int nExport;
		CImgExpIDList IdList;
		CString strPath = theApp.m_sDirTemp + "\\PPT";

		BeginWaitCursor();

		while(pos != NULL)
		{
	        pPath = m_pExportDlg->m_ListPathDiapo.GetNext(pos);

			if (pPath != NULL)
			{
				m_ctrlProgress.SetPos(m_ctrlProgress.GetPos() + 1);

				if (pPath->m_bConfirmed == TRUE)
				{
					while(GetVolumeName() != pPath->m_strDvdLabel)
					{
						CEspelliDlg dlg(this, pPath->m_strDvdLabel);

						if (dlg.DoModal() == IDCANCEL)
							break;
					}
				}

				if (VerificaPercorso(strPath) == FALSE)
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_EXPORT_PATH), MB_ICONSTOP);
					bError = TRUE;
				}

				m_pExportDlg->m_pEsamiView->m_pImgManager->SetCurrentIDs(pPath->m_lPaziente, pPath->m_lEsame);
				SetDlgItemText(IDC_STATIC_DA, m_pExportDlg->m_pEsamiView->m_pImgManager->GetFullPath(pPath->m_lID));

				EXP_ITEM itemTemp;
				itemTemp.lIDImmagine = pPath->m_lID;
				itemTemp.sPrefisso = "";
				itemTemp.lPrefissoNum = 0;
				IdList.AddTail(itemTemp);

				nExport = m_pExportDlg->m_pEsamiView->m_pImgManager->ExportImgList(strPath, &IdList, (imageformat)3); // BITMAP //
				if (nExport != 1)
				{
					CString strMessage;
					strMessage.Format(theApp.GetMessageString(IDS_ERROR_EXPORT_DOCUMENT), m_pExportDlg->m_pEsamiView->m_pImgManager->GetFullPath(pPath->m_lID));
					theApp.AfxMessageBoxEndo(strMessage, MB_ICONEXCLAMATION);
					bError = TRUE;
				}

				IdList.RemoveAll();
			}

			while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			if (m_bInterrompi == TRUE)
			{
				CString strError;
				strError.Format(theApp.GetMessageString(IDS_OPERAZIONE_INTERROTTA), m_ctrlProgress.GetPos());
				theApp.AfxMessageBoxEndo(strError, MB_ICONSTOP);
				bError = TRUE;
				break;
			}
		}

		EndWaitCursor();
	}

	if (bError)
		DeleteDirectory(theApp.m_sDirTemp + "\\PPT");

	OnOK();
}

void CExportPptDlg::OnTimer(UINT nIDEvent)
{
	switch(nIDEvent)
	{
		case EXPORT_TIMER:
		{
			this->KillTimer(EXPORT_TIMER);

			ExportImmaginiSelezionate();

			break;
		}
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CExportPptDlg::OnBnClickedBtnInterrompi()
{
	m_bInterrompi = TRUE;
}
