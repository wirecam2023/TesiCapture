#include "stdafx.h"
#include "Endox.h"
#include "OsservazioniListCtrl.h"

#include <io.h>
#include <math.h>

#include "Common.h"
#include "ExportCSV.h"
#include "ExportFileDlg.h"
#include "ExportExcel.h"
#include "ExportHtml.h"
#include "EsamiView.h"
#include "ElemReportSet.h"
#include "MyPrintDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

COsservazioniListCtrl::COsservazioniListCtrl()
	: CListCtrl()
{
	m_sNotePiePagina = "";
}

COsservazioniListCtrl::~COsservazioniListCtrl()
{
}

int COsservazioniListCtrl::InsertColumn(int nCol, LPCTSTR lpszColumnHeading, int nFormat, int nWidth)
{
	return CListCtrl::InsertColumn(nCol, lpszColumnHeading, nFormat, nWidth);
}

void COsservazioniListCtrl::SetNotePiePagina(CString strNote)
{
	m_sNotePiePagina = strNote;
}

void COsservazioniListCtrl::Export(CString strTitle)
{
	CString strFilter, strFileExport;
	CExportFileDlg dlg;
	CExportExcel excel;
	CExportHtml  html;
	CExportCSV   csv;
	int nModalita;
	BOOL bContinue = FALSE;

	HDITEM hdItem;
	char lpBuffer[256];
	hdItem.mask = HDI_TEXT;
	hdItem.pszText = lpBuffer;
	hdItem.cchTextMax = 256;

	if (dlg.DoModal() == IDOK)
	{
		nModalita = dlg.m_nTipoExport;
	
		switch(nModalita)
		{
			case 0:
			{
				strFilter = "File Microsoft Excel (*.xls)|*.xls|Tutti i file|*.*|";
				break;
			}
			case 1:
			{
				strFilter = "File HTML (*.htm)|*.htm|Tutti i file|*.*|";
				break;
			}
			case 2:
			{
				strFilter = "File CSV (*.csv)|*.csv|Tutti i file|*.*|";
				break;
			}
		}

		CFileDialog FileDlg(FALSE, NULL, NULL, OFN_READONLY | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, strFilter, NULL);
		if (FileDlg.DoModal() == IDOK)
		{
			strFileExport = FileDlg.GetPathName();

			switch(nModalita)
			{
				case 0:
				{
					if (strFileExport.Right(4) != ".xls")
						strFileExport += ".xls";
					break;
				}
				case 1:
				{
					if (strFileExport.Right(4) != ".htm")
						strFileExport += ".htm";
					break;
				}
				case 2:
				{
					if (strFileExport.Right(4) != ".csv")
						strFileExport += ".csv";
					break;
				}
			}

			switch(nModalita)
			{
				case 0:
				{
					bContinue = excel.CreateFile(strFileExport);
					break;
				}
				case 1:
				{
					bContinue = html.CreateFile(strFileExport, theApp.m_sNomeProgramma + " lista osservazioni ", GetHeaderCtrl()->GetItemCount());
					break;
				}
				case 2:
				{
					bContinue = csv.CreateFile(strFileExport);
					break;
				}
			}
			
			if (!bContinue)
				theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_NOMENCLATORE_ERR_FILE) + strFileExport);
		}	
		else
		{
			bContinue = FALSE;
		}
	}

	CString strToWrite;
	CellFont nCellFont;
	int nMaxLength[10];
	ZeroMemory(nMaxLength, 10 * sizeof(int));

	if (bContinue)
	{
		// Sandro Gallina - 31/05/2004 --> //
		switch(nModalita)
		{
			case 0:
			{
				excel.WriteValue(strTitle, 0, 0, xlsFont1, xlsGeneralAlign, xlsNormal);
				break;
			}
			case 1:
			{
				html.WriteTitle(strTitle);
				break;
			}
		}
		// <-- Sandro Gallina - 31/05/2004 //

		for(int i = 0; i <= GetItemCount(); i++)
		{
			for(int j = 0; j < GetHeaderCtrl()->GetItemCount(); j++)
			{
				if (i == 0)
				{
					// scrivo intestazioni //
					GetHeaderCtrl()->GetItem(j, &hdItem);
					strToWrite = hdItem.pszText;
					nCellFont = xlsFont0;
				}
				else
				{
					strToWrite = GetItemText(i - 1, j);
					nCellFont = xlsFont1;
				}
				
				if (nMaxLength[j] < strToWrite.GetLength())
					nMaxLength[j] = strToWrite.GetLength();
				
				switch(nModalita)
				{
					case 0:
					{
						excel.WriteValue(strToWrite, i + 2, j, nCellFont, xlsGeneralAlign, xlsNormal);
						break;
					}
					case 1:
					{
						html.WriteValue(strToWrite);
						// per evitare errore di visualizzazione... //
						if (j < GetHeaderCtrl()->GetItemCount() - 1)
							html.WriteNewColumn();
						break;
					}
					case 2:
					{
						csv.WriteValue(strToWrite);
						csv.WriteNewColumn();
						break;
					}
				}
			}

			switch(nModalita)
			{
				case 1:
				{
					html.WriteNewRow();
					break;
				}
				case 2:
				{
					csv.WriteNewRow();
					break;
				}
			}
		}
				
		if (nModalita == 0)
			for(int j = 0; j < GetHeaderCtrl()->GetItemCount(); j++)
				excel.SetColumnWidth(j, j, (short)(nMaxLength[j] * 1));
				
		switch(nModalita)
		{
			case 0:
			{
				excel.SetFont("Tahoma", 10, xlsBold);
				excel.SetFont("Tahoma", 10, xlsNoFormat);
				excel.CloseFile();
				break;
			}
			case 1:
			{
				html.CloseFile();
				break;
			}
			case 2:
			{
				csv.CloseFile(strTitle);
				break;
			}
		}
	}
}

void COsservazioniListCtrl::Print()
{
    CMyPrintDialog dlgPrinter(FALSE);
    if (dlgPrinter.DoModal() != IDOK)
        return;

	// stampa LANDSCAPE //
	DEVMODE* pDevMode = dlgPrinter.GetDevMode();
	pDevMode->dmOrientation = DMORIENT_LANDSCAPE;
	pDevMode->dmPaperSize = DMPAPER_A4;
	dlgPrinter.CreatePrinterDC();

	//
	CDC dc;
    dc.Attach(dlgPrinter.GetPrinterDC());
    dc.m_bPrinting = TRUE;

	//
	char szDocName[255];
	strcpy_s(szDocName, theApp.m_sNomeProgramma);

	//
	DOCINFO di;
    memset(&di, 0, sizeof(DOCINFO));
    di.cbSize = sizeof(DOCINFO);
    di.lpszDocName = szDocName;

	//
    BOOL bPrintingOK = dc.StartDoc(&di);

	//
    CPrintInfo Info;
	Info.m_rectDraw.SetRect(0, 0, dc.GetDeviceCaps(HORZRES), dc.GetDeviceCaps(VERTRES));

	//
	CalculateColumnsWidthForPrint(Info.m_rectDraw.Width());
    OnPrint(&dc, &Info);
    
	//
    if (bPrintingOK)
        dc.EndDoc();
    else
        dc.AbortDoc();

    dc.Detach();
}

void COsservazioniListCtrl::OnBeginPrinting(CDC *pDC, CPrintInfo *pInfo)
{
}

void COsservazioniListCtrl::OnPrint(CDC *pDC, CPrintInfo *pInfo)
{
    if ((pDC == NULL) || (pInfo == NULL))
		return;

	//

	CClientDC dcForm(this);

	LOGFONT lfFont;
	lfFont.lfWidth = 0;
	lfFont.lfEscapement = 0;
	lfFont.lfOrientation = 0;
	lfFont.lfStrikeOut = 0;
	lfFont.lfCharSet = 0;
	lfFont.lfOutPrecision = 1;
	lfFont.lfClipPrecision = 2;
	lfFont.lfQuality = 1;
	lfFont.lfPitchAndFamily = 34;
	lfFont.lfHeight = MulDiv(-14, pDC->GetDeviceCaps(LOGPIXELSY), dcForm.GetDeviceCaps(LOGPIXELSY));
	lfFont.lfWeight = 400;
	lfFont.lfItalic = 0;
	lfFont.lfUnderline = 0;
	strcpy_s(lfFont.lfFaceName, "Tahoma");

	//

	CFont fontNormal; 
	fontNormal.CreateFontIndirect(&lfFont);

	//

	lfFont.lfWeight = FW_BOLD;

	CFont fontBold; 
	fontBold.CreateFontIndirect(&lfFont);

	//

	int nAltezzaRiga = (int)((double)6 * (double)pDC->GetDeviceCaps(LOGPIXELSY) / (double)25.4); // riga alta 6 mm //

	int nOffsetVert = 0;
	int nPagina = 1;

	//

	pDC->StartPage();
	PrintColumnHeaders(pDC, &fontBold, nAltezzaRiga);
	PrintFooter(pDC, pInfo, &fontBold, nAltezzaRiga, nPagina);

	for(int i = 0; i < GetItemCount(); i++)
	{
		int iLeft = 0;
		for(int j = 0; j < GetHeaderCtrl()->GetItemCount(); j++)
		{
			if (m_iColumnWidthForPrinter[j] > 0)
			{
				CRect rectCell(iLeft, ((i + 2) * nAltezzaRiga) - nOffsetVert, iLeft + m_iColumnWidthForPrinter[j], ((i + 3) * nAltezzaRiga) - nOffsetVert);

				if (rectCell.bottom > pInfo->m_rectDraw.Height() - nAltezzaRiga)
				{
					// devo inserire una nuova pagina //
					pDC->EndPage();
					pDC->StartPage();

					nPagina++;
					PrintColumnHeaders(pDC, &fontBold, nAltezzaRiga);
					PrintFooter(pDC, pInfo, &fontBold, nAltezzaRiga, nPagina);

					int nOffsetSum = rectCell.top - (2 * nAltezzaRiga);
					nOffsetVert += nOffsetSum;
					rectCell.OffsetRect(0, -nOffsetSum);
				}

				pDC->Rectangle(&rectCell);
				rectCell.DeflateRect(20, 5);

				//

				int nOptions = DT_VCENTER | DT_SINGLELINE;

				LVCOLUMN lvTemp;
				lvTemp.mask = LVCF_FMT;
				this->GetColumn(j, &lvTemp);

				if ((lvTemp.fmt & LVCFMT_CENTER) != 0)
					nOptions += DT_CENTER;
				else if ((lvTemp.fmt & LVCFMT_RIGHT) != 0)
					nOptions += DT_RIGHT;
				else
					nOptions += DT_LEFT;

				//

				pDC->SelectObject(&fontNormal);
				pDC->DrawText(GetItemText(i, j), &rectCell, nOptions);

				//

				iLeft += m_iColumnWidthForPrinter[j];
			}
		}
	}

	pDC->EndPage();
}

void COsservazioniListCtrl::OnEndPrinting(CDC *pDC, CPrintInfo *pInfo)
{
}

void COsservazioniListCtrl::CalculateColumnsWidthForPrint(int nRectWidth)
{
	for(int i = 0; i < 255; i++)
		m_iColumnWidthForPrinter[i] = 0;

	//

	int nWidthSum = 0;
	for(int i = 0; i < GetHeaderCtrl()->GetItemCount(); i++)
	{
		CRect rectTemp;
		GetHeaderCtrl()->GetItemRect(i, &rectTemp);

		nWidthSum += rectTemp.Width();
	}

	//

	for(int i = 0; i < GetHeaderCtrl()->GetItemCount(); i++)
	{
		CRect rectTemp;
		GetHeaderCtrl()->GetItemRect(i, &rectTemp);

		m_iColumnWidthForPrinter[i] = (int)((double)nRectWidth * (double)rectTemp.Width() / (double)nWidthSum);
	}
}

void COsservazioniListCtrl::PrintColumnHeaders(CDC* pDC, CFont* pFontBold, int nRectHeight)
{
	int iLeft = 0;
	for(int i = 0; i < GetHeaderCtrl()->GetItemCount(); i++)
	{
		if (m_iColumnWidthForPrinter[i] > 0)
		{
			char szText[255];

			HDITEM headerInfo;
			headerInfo.mask = HDI_TEXT;
			headerInfo.pszText = szText;
			headerInfo.cchTextMax = 255;
			GetHeaderCtrl()->GetItem(i, &headerInfo);

			//

			CRect rectCell1(iLeft, 0, iLeft + m_iColumnWidthForPrinter[i], nRectHeight);
			pDC->Rectangle(&rectCell1);
			rectCell1.DeflateRect(20, 5);

			CRect rectCell2(iLeft, nRectHeight, iLeft + m_iColumnWidthForPrinter[i], 2 * nRectHeight);
			pDC->Rectangle(&rectCell2);

			//

			pDC->SelectObject(pFontBold);
			pDC->DrawText(szText, &rectCell1, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

			//

			iLeft += m_iColumnWidthForPrinter[i];
		}
	}
}

void COsservazioniListCtrl::PrintFooter(CDC* pDC, CPrintInfo *pInfo, CFont* pFontBold, int nRectHeight, int nPagina)
{
	CRect rectFooter = CRect(0, pInfo->m_rectDraw.Height() - nRectHeight, pInfo->m_rectDraw.Width(), pInfo->m_rectDraw.Height());

	CString sText;
	sText.Format("%s - %s %d", m_sNotePiePagina, theApp.GetMessageString(IDS_PAGINA), nPagina);

	pDC->SelectObject(pFontBold);
	pDC->DrawText(sText, &rectFooter, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
}
