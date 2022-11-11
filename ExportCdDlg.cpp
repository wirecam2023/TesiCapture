#include "stdafx.h"
#include "Endox.h"
#include "ExportCdDlg.h"

#include <direct.h>
#include <errno.h>
#include <io.h>

#include "Common.h"
#include "CustomDate.h"
#include "EsamiSet.h"
#include "EsamiView.h"
#include "EspelliDlg.h"
#include "ExportDlg.h"
#include "FileBmp.h"
#include "ObSelect.h"
#include "Path.h"
#include "VistaImmaginiNumeroDermoxSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CExportCdDlg::CExportCdDlg(CWnd* pParent, CEsamiView* pEsamiView, CExportDlg* pExportDlg, int iNumExp, int iDiscType)
	: CExportProgressDiscDlg(pParent, pEsamiView, iNumExp, iDiscType)
{
	ASSERT(pExportDlg != NULL);

	m_pExportDlg = pExportDlg;
}

CExportCdDlg::~CExportCdDlg()
{
}

BOOL CExportCdDlg::ExportImmagini()
{
	BOOL bError = FALSE;
	MSG msg;

	CTime timeCurrent = CTime::GetCurrentTime();
	CCustomDate dataTemp;

	CString strTemp;

	m_strPath.Format("C:\\Temp\\Exp%4d%02d%02d%02d%02d%02d", timeCurrent.GetYear(), timeCurrent.GetMonth(), timeCurrent.GetDay(), timeCurrent.GetHour(), timeCurrent.GetMinute(), timeCurrent.GetSecond());
	if (VerificaPercorso(m_strPath) == FALSE)
		bError = TRUE;

	POSITION pos = m_pExportDlg->m_ListPathDiapo.GetHeadPosition();
	CPath *pPath = NULL;

	if (bError == FALSE)
	{
		int nExport;
		CImgExpIDList IdList;

		BeginWaitCursor();
		while(pos != NULL)
		{
			pPath = (CPath*)m_pExportDlg->m_ListPathDiapo.GetNext(pos);

			if (pPath != NULL)
			{
				m_ctrlProgress1.SetPos(m_ctrlProgress1.GetPos() + 1);

				if (pPath->m_bConfirmed == TRUE)
				{
					while(GetVolumeName() != pPath->m_strDvdLabel)
					{
						CEspelliDlg dlg(this, pPath->m_strDvdLabel);

						if (dlg.DoModal() == IDCANCEL)
							break;
					}
				}

				strTemp.Format("C:\\Temp\\Exp%4d%02d%02d%02d%02d%02d\\%s", timeCurrent.GetYear(), timeCurrent.GetMonth(), timeCurrent.GetDay(), timeCurrent.GetHour(), timeCurrent.GetMinute(), timeCurrent.GetSecond(), pPath->m_szDesc);
				if (VerificaPercorso(strTemp) == FALSE)
					bError = TRUE;

				m_pEsamiView->m_pImgManager->SetCurrentIDs(pPath->m_lPaziente, pPath->m_lEsame);
				SetDlgItemText(IDC_STATIC_DA, m_pEsamiView->m_pImgManager->GetFullPath(pPath->m_lID));

				EXP_ITEM itemTemp;
				itemTemp.lIDImmagine = pPath->m_lID;
				itemTemp.sPrefisso = (theApp.m_bNominativoSuExportImmagini ? CPazientiSet().GetCognomeNome(pPath->m_lPaziente) : "");
				itemTemp.lPrefissoNum = ((theApp.m_nApplication != PRG_DERMOX) ? 0 : CVistaImmaginiNumeroDermoxSet().GetNumeroDermox(pPath->m_lID));
				IdList.AddTail(itemTemp);

				nExport = m_pEsamiView->m_pImgManager->ExportImgList(strTemp, &IdList, (imageformat)(theApp.m_nExpFormat + 1));
				if (nExport != 1)
				{
					CString strMessage;
					strMessage.Format(theApp.GetMessageString(IDS_ERROR_EXPORT_DOCUMENT), m_pEsamiView->m_pImgManager->GetFullPath(pPath->m_lID));
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
