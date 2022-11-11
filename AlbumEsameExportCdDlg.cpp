#include "stdafx.h"
#include "Endox.h"
#include "AlbumEsameExportCdDlg.h"

#include <direct.h>
#include <errno.h>
#include <io.h>

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

CAlbumEsameExportCdDlg::CAlbumEsameExportCdDlg(CWnd* pParent, CEsamiView* pEsamiView, int iNumExp, int iDiscType)
	: CExportProgressDiscDlg(pParent, pEsamiView, iNumExp, iDiscType)
{
}

CAlbumEsameExportCdDlg::~CAlbumEsameExportCdDlg()
{
}

BOOL CAlbumEsameExportCdDlg::ExportImmagini()
{
	BOOL bError = FALSE;
	MSG msg;

	CTime timeCurrent = CTime::GetCurrentTime();
	CCustomDate dataTemp(m_pEsamiView->m_pEsamiSet->m_lData);

	CString strTemp;
	strTemp.Format("C:\\Temp\\Exp%4d%02d%02d%02d%02d%02d\\%s %s %02d.%02d.%d", timeCurrent.GetYear(), timeCurrent.GetMonth(), timeCurrent.GetDay(), timeCurrent.GetHour(), timeCurrent.GetMinute(), timeCurrent.GetSecond(), m_pEsamiView->m_pPazientiSet->m_sCognome, m_pEsamiView->m_pPazientiSet->m_sNome, dataTemp.GetDay(), dataTemp.GetMonth(), dataTemp.GetYear());
	if (VerificaPercorso(strTemp) == FALSE)
		bError = TRUE;

	m_strPath.Format("C:\\Temp\\Exp%4d%02d%02d%02d%02d%02d", timeCurrent.GetYear(), timeCurrent.GetMonth(), timeCurrent.GetDay(), timeCurrent.GetHour(), timeCurrent.GetMinute(), timeCurrent.GetSecond());
	if (VerificaPercorso(m_strPath) == FALSE)
		bError = TRUE;

	POSITION pos = CFileBmp::GetFirstSelectedPos();
	CObSelect* pSel = NULL;

	if (bError == FALSE)
	{
		int nExport;
		CImgExpIDList IdList;

		BeginWaitCursor();
		while(pos != NULL)
		{
			pSel = CFileBmp::GetNextSelected(pos);
			
			if (pSel != NULL)
			{
				m_ctrlProgress1.SetPos(m_ctrlProgress1.GetPos() + 1);

				if (pSel->m_bConfirmed == TRUE)
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
				strError.Format(theApp.GetMessageString(IDS_OPERAZIONE_INTERROTTA), m_ctrlProgress1.GetPos());
				theApp.AfxMessageBoxEndo(strError, MB_ICONSTOP);
				bError = TRUE;
				break;
			}
		}
		EndWaitCursor();
	}
	
	if ((m_bInterrompi == TRUE) || (bError == TRUE))
		ImpostaFase(FASE_32);
	else
		ImpostaFase(FASE_2);

	return !bError;
}