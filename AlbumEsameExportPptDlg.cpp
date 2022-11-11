#include "stdafx.h"
#include "Endox.h"
#include "AlbumEsameExportPptDlg.h"

#include <direct.h>
#include <errno.h>
#include <io.h>

#include "DLL_Imaging\h\AmRes.h"
#include "DLL_Imaging\h\ImgManager.h"

#include "Common.h"
#include "CustomDate.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "EspelliDlg.h"
#include "FileBmp.h"
#include "ObSelect.h"
#include "PazientiSet.h"
#include "VistaImmaginiNumeroDermoxSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CAlbumEsameExportPptDlg, CDialog)

CAlbumEsameExportPptDlg::CAlbumEsameExportPptDlg(CWnd* pParent, CEsamiView* pEsamiView, int iNumExp)
	: CDialog(CAlbumEsameExportPptDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
	m_iNumExp = iNumExp;
	m_bError = FALSE;

	m_bInterrompi = FALSE;
}

CAlbumEsameExportPptDlg::~CAlbumEsameExportPptDlg()
{
}

void CAlbumEsameExportPptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PROGRESS1, m_ctrlProgress);
	DDX_Control(pDX, IDC_BTN_INTERROMPI, m_ctrlBtnInterrompi);
}

BEGIN_MESSAGE_MAP(CAlbumEsameExportPptDlg, CDialog)

	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_INTERROMPI, OnBnClickedBtnInterrompi)

	ON_WM_TIMER()

END_MESSAGE_MAP()

BOOL CAlbumEsameExportPptDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	m_ctrlProgress.SetRange(0, m_iNumExp);
	m_ctrlProgress.SetPos(0);

	SetTimer(EXPORT_TIMER, 500, NULL);

	theApp.LocalizeDialog(this, CAlbumEsameExportPptDlg::IDD, "AlbumEsameExportPptDlg");
	return bReturn;
}

void CAlbumEsameExportPptDlg::OnBnClickedOk()
{
	// OnOK();
}

void CAlbumEsameExportPptDlg::OnBnClickedCancel()
{
	// OnCancel();
}

void CAlbumEsameExportPptDlg::ExportImmaginiSelezionate()
{
	MSG msg;

	POSITION pos = CFileBmp::GetFirstSelectedPos();
	CObSelect* pSel = NULL;

	if (m_bError == FALSE)
	{
		int nExport;
		CImgExpIDList IdList;
		CString strPath = theApp.m_sDirTemp + "\\PPT";

		BeginWaitCursor();

		while (pos != NULL)
		{
			pSel = CFileBmp::GetNextSelected(pos);

			if (pSel != NULL)
			{
				m_ctrlProgress.SetPos(m_ctrlProgress.GetPos() + 1);

				if (pSel->m_bConfirmed == TRUE)
				{
					while (GetVolumeName() != pSel->m_strDvdLabel)
					{
						CEspelliDlg dlg(this, pSel->m_strDvdLabel);

						if (dlg.DoModal() == IDCANCEL)
							break;
					}
				}

				if (VerificaPercorso(strPath) == FALSE)
				{
					theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_EXPORT_PATH), MB_ICONSTOP);
					m_bError = TRUE;
				}

				m_pEsamiView->m_pImgManager->SetCurrentIDs(pSel->m_lPaziente, pSel->m_lEsame);
				SetDlgItemText(IDC_STATIC_DA, m_pEsamiView->m_pImgManager->GetFullPath(pSel->m_lID));

				EXP_ITEM itemTemp;
				itemTemp.lIDImmagine = pSel->m_lID;
				itemTemp.sPrefisso = "";
				itemTemp.lPrefissoNum = 0;
				IdList.AddTail(itemTemp);

				nExport = m_pEsamiView->m_pImgManager->ExportImgList(strPath, &IdList, (imageformat)3); // BITMAP //
				if (nExport != 1)
				{
					CString strMessage;
					strMessage.Format(theApp.GetMessageString(IDS_ERROR_EXPORT_DOCUMENT), m_pEsamiView->m_pImgManager->GetFullPath(pSel->m_lID));
					theApp.AfxMessageBoxEndo(strMessage, MB_ICONEXCLAMATION);
					m_bError = TRUE;
				}

				IdList.RemoveAll();
			}

			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			if (m_bInterrompi == TRUE)
			{
				CString strError;
				strError.Format(theApp.GetMessageString(IDS_OPERAZIONE_INTERROTTA), m_ctrlProgress.GetPos());
				theApp.AfxMessageBoxEndo(strError, MB_ICONSTOP);
				m_bError = TRUE;
				break;
			}
		}

		EndWaitCursor();
	}

	if (m_bError)
		DeleteDirectory(theApp.m_sDirTemp + "\\PPT");

	OnOK();
}

void CAlbumEsameExportPptDlg::OnTimer(UINT nIDEvent)
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

void CAlbumEsameExportPptDlg::OnBnClickedBtnInterrompi()
{
	m_bInterrompi = TRUE;
}
