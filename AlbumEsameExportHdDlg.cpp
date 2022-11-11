#include "stdafx.h"
#include "Endox.h"
#include "AlbumEsameExportHdDlg.h"

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

IMPLEMENT_DYNAMIC(CAlbumEsameExportHdDlg, CDialog)

CAlbumEsameExportHdDlg::CAlbumEsameExportHdDlg(CWnd* pParent, CEsamiView* pEsamiView, int iNumExp, BOOL bAlert, CString* outDirectory)
	: CDialog(CAlbumEsameExportHdDlg::IDD, pParent)
{
	ASSERT(pEsamiView != NULL);

	m_pEsamiView = pEsamiView;
	m_iNumExp = iNumExp;
	m_sOutDirectory = outDirectory;
	m_bAlert = bAlert;
	m_bError = FALSE;

	m_bInterrompi = FALSE;
}

CAlbumEsameExportHdDlg::~CAlbumEsameExportHdDlg()
{
}

void CAlbumEsameExportHdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PROGRESS1, m_ctrlProgress);
	DDX_Control(pDX, IDC_BTN_INTERROMPI, m_ctrlBtnInterrompi);
}

BEGIN_MESSAGE_MAP(CAlbumEsameExportHdDlg, CDialog)

	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_INTERROMPI, OnBnClickedBtnInterrompi)

	ON_WM_TIMER()

END_MESSAGE_MAP()

BOOL CAlbumEsameExportHdDlg::OnInitDialog()
{
	BOOL bReturn = CDialog::OnInitDialog();

	m_ctrlProgress.SetRange(0, m_iNumExp);
	m_ctrlProgress.SetPos(0);

	SetTimer(EXPORT_TIMER, 500, NULL);

	theApp.LocalizeDialog(this, CAlbumEsameExportHdDlg::IDD, "AlbumEsameExportHdDlg");
	return bReturn;
}

void CAlbumEsameExportHdDlg::OnBnClickedOk()
{
	// OnOK();
}

void CAlbumEsameExportHdDlg::OnBnClickedCancel()
{
	// OnCancel();
}

void CAlbumEsameExportHdDlg::ExportImmaginiSelezionate()
{
	MSG msg;

	CCustomDate dataTemp(m_pEsamiView->m_pEsamiSet->m_lData);

	CString strTemp;
	strTemp.Format("%s%s %s %02d.%02d.%d", theApp.m_sExportFolder, m_pEsamiView->m_pPazientiSet->m_sCognome, m_pEsamiView->m_pPazientiSet->m_sNome, dataTemp.GetDay(), dataTemp.GetMonth(), dataTemp.GetYear());
	if (VerificaPercorso(strTemp) == FALSE)
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ERROR_EXPORT_PATH), MB_ICONSTOP);
		m_bError = TRUE;
	}

	POSITION pos = CFileBmp::GetFirstSelectedPos();
	CObSelect* pSel = NULL;

	if (m_bError == FALSE)
	{
		int nExport;
		CImgExpIDList IdList;

		BeginWaitCursor();
		while(pos != NULL)
		{
			pSel = CFileBmp::GetNextSelected(pos);
			
			if (pSel != NULL)
			{
				m_ctrlProgress.SetPos(m_ctrlProgress.GetPos() + 1);

				if (pSel->m_bConfirmed)
				{
					while(GetVolumeName() != pSel->m_strDvdLabel)
					{
						CEspelliDlg	dlg(this, pSel->m_strDvdLabel);

						if (dlg.DoModal() == IDCANCEL)
							break;
					}
				}

				m_pEsamiView->m_pImgManager->SetCurrentIDs(pSel->m_lPaziente, pSel->m_lEsame);
				SetDlgItemText(IDC_STATIC_DA, m_pEsamiView->m_pImgManager->GetFullPath(pSel->m_lID));

				EXP_ITEM itemTemp;
				itemTemp.lIDImmagine = pSel->m_lID;
				itemTemp.sPrefisso = (theApp.m_bNominativoSuExportImmagini ? CPazientiSet().GetCognomeNome(pSel->m_lPaziente) : "");
				itemTemp.lPrefissoNum = ((theApp.m_nApplication != PRG_DERMOX) ? 0 : CVistaImmaginiNumeroDermoxSet().GetNumeroDermox(pSel->m_lID));
				IdList.AddTail(itemTemp);

				nExport = m_pEsamiView->m_pImgManager->ExportImgList(strTemp, &IdList, (imageformat)(theApp.m_nExpFormat + 1));
				if (nExport != 1)
				{
					CString strMessage;
					strMessage.Format(theApp.GetMessageString(IDS_ERROR_EXPORT_DOCUMENT), m_pEsamiView->m_pImgManager->GetFullPath(pSel->m_lID));
					theApp.AfxMessageBoxEndo(strMessage, MB_ICONEXCLAMATION);
					m_bError = TRUE;
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
				m_bError = TRUE;
				break;
			}
		}
		EndWaitCursor();
	}

	if (m_bError == FALSE && m_bAlert)
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_ALBUMESAME_EXP_IMG_OK));

	if (m_sOutDirectory != NULL)
		m_sOutDirectory->Format("%s", strTemp);

	OnOK();
}

void CAlbumEsameExportHdDlg::OnTimer(UINT nIDEvent)
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

void CAlbumEsameExportHdDlg::OnBnClickedBtnInterrompi()
{
	m_bInterrompi = TRUE;
}
