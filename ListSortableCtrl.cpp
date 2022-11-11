#include "stdafx.h"
#include "Endox.h"
#include "ListSortableCtrl.h"

#include "ExportCSV.h"
#include "ExportExcel.h"
#include "ExportHtml.h"
#include "ExportFileDlg.h"
#include "MyPrintDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CListSortableCtrl::CListSortableCtrl(void)
{
	m_sNotePiePagina = "";
}

CListSortableCtrl::~CListSortableCtrl(void)
{
}

BEGIN_MESSAGE_MAP(CListSortableCtrl, CListCtrlLocalize)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

void CListSortableCtrl::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	SetSortIndicator(pNMListView->iSubItem);

	tagITEMCALLBACK param;
	param.iCol = pNMListView->iSubItem;
	param.pListCtrl = this;
	ListView_SortItemsEx(GetSafeHwnd(), SortFunc, (LPARAM)&param);

	*pResult = 0;
}

void CListSortableCtrl::OnDestroy()
{
	for (int i = 0; i < GetHeaderCtrl()->GetItemCount(); i++)
	{
		HDITEM hItem;
		hItem.mask = HDI_LPARAM;
		GetHeaderCtrl()->GetItem(i, &hItem);
		delete (tagHEADERITEMDATA*)hItem.lParam;
	}

	CListCtrlLocalize::OnDestroy();
}

int CListSortableCtrl::InsertColumn(int nCol, LPCTSTR lpszColumnHeading, ColumnType type, int nFormat, int nWidth, int nSubItem)
{
	SetWindowLong(GetHeaderCtrl()->GetSafeHwnd(), GWL_STYLE, GetHeaderCtrl()->GetStyle() | HDS_BUTTONS);

	int iReturn = CListCtrlLocalize::InsertColumn(nCol, lpszColumnHeading, nFormat, nWidth, nSubItem);

	if (iReturn >= 0)
	{
		tagHEADERITEMDATA* pHeaderItemData = new tagHEADERITEMDATA;
		pHeaderItemData->type = type;
		pHeaderItemData->sort = sort_nothing;

		HDITEM hItem;
		hItem.mask = HDI_LPARAM;
		hItem.lParam = (LPARAM)pHeaderItemData;
		GetHeaderCtrl()->SetItem(iReturn, &hItem);
	}

	return iReturn;
}

BOOL CListSortableCtrl::DeleteColumn(int nCol)
{
	HDITEM hItem;
	hItem.mask = HDI_LPARAM;
	if (GetHeaderCtrl()->GetItem(nCol, &hItem) && hItem.lParam)
		delete (tagHEADERITEMDATA*)hItem.lParam;

	return CListCtrlLocalize::DeleteColumn(nCol);
}

int CALLBACK CListSortableCtrl::SortFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	tagITEMCALLBACK* pParam = (tagITEMCALLBACK*)lParamSort;

	int iFirstItem = (int)lParam1, iSecondItem = (int)lParam2;
	if (iFirstItem < 0 || iSecondItem < 0)
		return 0;

	int iReturn = 0;
	CString strItem1 = pParam->pListCtrl->GetItemText((int)iFirstItem, pParam->iCol);
	CString strItem2 = pParam->pListCtrl->GetItemText((int)iSecondItem, pParam->iCol);

	strItem1.MakeUpper();
	strItem2.MakeUpper();

	HDITEM hItem;
	ZeroMemory(&hItem, sizeof(HDITEM));
	hItem.mask = HDI_LPARAM;
	pParam->pListCtrl->GetHeaderCtrl()->GetItem(pParam->iCol, &hItem);
	tagHEADERITEMDATA* pHeaderItemData = (tagHEADERITEMDATA*)hItem.lParam;

	if (pHeaderItemData->type == type_date)
	{
		strItem1 = GetDateFromItem(strItem1);
		strItem2 = GetDateFromItem(strItem2);
	}
	else if (pHeaderItemData->type == type_date_time)
	{
		strItem1 = GetDateTimeFromItem(strItem1);
		strItem2 = GetDateTimeFromItem(strItem2);
	}

	switch (pHeaderItemData->sort)
	{
	case sort_ascending:
		if (pHeaderItemData->type == type_string ||
			pHeaderItemData->type == type_date ||
			pHeaderItemData->type == type_date_time)
		{
			iReturn = strcmp(strItem1, strItem2);
		}
		else if (pHeaderItemData->type == type_number)
		{
			iReturn = atof(strItem1) >= atof(strItem2);
		}
		break;

	case sort_descending:
		if (pHeaderItemData->type == type_string ||
			pHeaderItemData->type == type_date ||
			pHeaderItemData->type == type_date_time)
		{
			iReturn = strcmp(strItem2, strItem1);
		}
		else if (pHeaderItemData->type == type_number)
		{
			iReturn = atof(strItem1) < atof(strItem2);
		}
		break;

	default:
		break;
	}

	return iReturn;
}

void CListSortableCtrl::SetSortColumn(int iCol)
{
	HDITEM hItem;
	hItem.mask = HDI_LPARAM;
	for (int i = 0; i < GetHeaderCtrl()->GetItemCount(); i++)
	{
		GetHeaderCtrl()->GetItem(i, &hItem);
		((tagHEADERITEMDATA*)hItem.lParam)->sort = sort_nothing;
	}

	SetSortIndicator(iCol);
}

void CListSortableCtrl::SetSortIndicator(int iCol)
{
	CHeaderCtrl* pHeader = GetHeaderCtrl();

	// lParam <-- 0 colonna non ordinata
	//        <-- 1 ordine crescente
	//        <-- 2 ordine decrescente

	for (int i = 0; i < pHeader->GetItemCount(); i++)
	{
		HDITEM hItem;
		UINT iArrowID;
		hItem.mask = HDI_FORMAT | HDI_LPARAM;
		pHeader->GetItem(i, &hItem);

		tagHEADERITEMDATA* pHeaderItemData = (tagHEADERITEMDATA*)hItem.lParam;

		if (i == iCol)
		{
			hItem.mask = HDI_FORMAT | HDI_BITMAP;
			hItem.fmt |= HDF_BITMAP | HDF_BITMAP_ON_RIGHT;

			switch (pHeaderItemData->sort)
			{
			default:
			case sort_nothing:
			case sort_descending:
				pHeaderItemData->sort = sort_ascending;
				iArrowID = OBM_UPARROWD;
				break;

			case sort_ascending:
				pHeaderItemData->sort = sort_descending;
				iArrowID = OBM_DNARROWD;
				break;
			}

			hItem.hbm = (HBITMAP)LoadImage(NULL, MAKEINTRESOURCE(iArrowID), IMAGE_BITMAP, 0, 0, LR_LOADMAP3DCOLORS);
			pHeader->SetItem(i, &hItem);
		}
		else
		{
			hItem.mask = HDI_FORMAT;
			hItem.fmt = HDF_STRING;
			hItem.hbm = NULL;
			pHeaderItemData->sort = sort_nothing;
			pHeader->SetItem(i, &hItem);
		}
	}
}

// Marvel Carvalho - BUG 4308 Esquemas Anatomicos Fleury
int CListSortableCtrl::GetColumnsCount()
{
	return GetHeaderCtrl()->GetItemCount();
}

// Marvel Carvalho - BUG 4308 Esquemas Anatomicos Fleury
void CListSortableCtrl::SetItemFocus(int iRow)
{
	this->SetFocus();
	this->SetItemState(-1, 0, LVIS_SELECTED);
	this->SetItemState(iRow, LVIS_SELECTED, LVIS_SELECTED);
	this->EnsureVisible(iRow, FALSE);
}

CString CListSortableCtrl::GetDateFromItem(CString strItem)
{
	CString strReturn = strItem;

	if (strItem.GetLength() == 10 && strItem.GetAt(2) == '/' && strItem.GetAt(5) == '/')
	{
		COleDateTime date(atoi(strItem.Mid(6, 4)),
			atoi(strItem.Mid(3, 2)),
			atoi(strItem.Mid(0, 2)),
			0, 0, 0);

		if (date.GetStatus() == COleDateTime::valid)
			strReturn.Format("%04d%02d%02d%02d%02d%02d",
			date.GetYear(),
			date.GetMonth(),
			date.GetDay(),
			date.GetHour(),
			date.GetMinute(),
			date.GetSecond());
	}

	return strReturn;
}

CString CListSortableCtrl::GetDateTimeFromItem(CString strItem)
{
	CString strReturn = strItem;

	if (strItem.GetLength() == 16 && strItem.GetAt(2) == '/' && strItem.GetAt(5) == '/' && strItem.GetAt(13) == ':')
	{
		COleDateTime date(atoi(strItem.Mid(6, 4)),
			atoi(strItem.Mid(3, 2)),
			atoi(strItem.Mid(0, 2)),
			atoi(strItem.Mid(11, 2)),
			atoi(strItem.Mid(14, 2)),
			0);

		if (date.GetStatus() == COleDateTime::valid)
			strReturn.Format("%04d%02d%02d%02d%02d%02d",
			date.GetYear(),
			date.GetMonth(),
			date.GetDay(),
			date.GetHour(),
			date.GetMinute(),
			date.GetSecond());
	}

	return strReturn;
}

void CListSortableCtrl::Export(CString strTitle)
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

		switch (nModalita)
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

		CFileDialog FileDlg(FALSE, NULL, NULL, OFN_READONLY | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, strFilter, this, 0, FALSE);
		if (FileDlg.DoModal() == IDOK)
		{
			strFileExport = FileDlg.GetPathName();

			switch (nModalita)
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

			switch (nModalita)
			{
			case 0:
			{
				bContinue = excel.CreateFile(strFileExport);
				break;
			}
			case 1:
			{
				bContinue = html.CreateFile(strFileExport, "", GetHeaderCtrl()->GetItemCount());
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
		switch (nModalita)
		{
		case 0:
			excel.WriteValue(strTitle, 0, 0, xlsFont1, xlsGeneralAlign, xlsNormal);
			break;

		case 1:
			html.WriteTitle(strTitle);
			break;
		}
		// <-- Sandro Gallina - 31/05/2004 //

		for (int i = 0; i <= GetItemCount(); i++)
		{
			for (int j = 0; j < GetHeaderCtrl()->GetItemCount(); j++)
			{
				if (i == 0)
				{
					//Scrivo intestazioni
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

				switch (nModalita)
				{
				case 0:
				{
					excel.WriteValue(strToWrite, i + 2, j, nCellFont, xlsGeneralAlign, xlsNormal);
					break;
				}
				case 1:
				{
					html.WriteValue(strToWrite);
					//Per evitare errore di visualizzazione..
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

			switch (nModalita)
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
			for (int j = 0; j < GetHeaderCtrl()->GetItemCount(); j++)
				excel.SetColumnWidth(j, j, (short)(nMaxLength[j] * 1));

		switch (nModalita)
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

void CListSortableCtrl::Print()
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

void CListSortableCtrl::OnBeginPrinting(CDC *pDC, CPrintInfo *pInfo)
{
}

void CListSortableCtrl::OnPrint(CDC *pDC, CPrintInfo *pInfo)
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

	for (int i = 0; i < GetItemCount(); i++)
	{
		int iLeft = 0;
		for (int j = 0; j < GetHeaderCtrl()->GetItemCount(); j++)
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

void CListSortableCtrl::OnEndPrinting(CDC *pDC, CPrintInfo *pInfo)
{
}

void CListSortableCtrl::CalculateColumnsWidthForPrint(int nRectWidth)
{
	for (int i = 0; i < 255; i++)
		m_iColumnWidthForPrinter[i] = 0;

	//

	int nWidthSum = 0;
	for (int i = 0; i < GetHeaderCtrl()->GetItemCount(); i++)
	{
		CRect rectTemp;
		GetHeaderCtrl()->GetItemRect(i, &rectTemp);

		nWidthSum += rectTemp.Width();
	}

	//

	for (int i = 0; i < GetHeaderCtrl()->GetItemCount(); i++)
	{
		CRect rectTemp;
		GetHeaderCtrl()->GetItemRect(i, &rectTemp);

		m_iColumnWidthForPrinter[i] = (int)((double)nRectWidth * (double)rectTemp.Width() / (double)nWidthSum);
	}
}

void CListSortableCtrl::PrintColumnHeaders(CDC* pDC, CFont* pFontBold, int nRectHeight)
{
	int iLeft = 0;
	for (int i = 0; i < GetHeaderCtrl()->GetItemCount(); i++)
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

void CListSortableCtrl::PrintFooter(CDC* pDC, CPrintInfo *pInfo, CFont* pFontBold, int nRectHeight, int nPagina)
{
	CRect rectFooter = CRect(0, pInfo->m_rectDraw.Height() - nRectHeight, pInfo->m_rectDraw.Width(), pInfo->m_rectDraw.Height());

	CString sText;
	sText.Format("%s - %s %d", m_sNotePiePagina, theApp.GetMessageString(IDS_PAGINA), nPagina);

	pDC->SelectObject(pFontBold);
	pDC->DrawText(sText, &rectFooter, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
}

//Gabriel BUG 6225 - Lista DO FIX
void CListSortableCtrl::SortColumn(int iCol)
{
	SetSortIndicator(iCol);

	tagITEMCALLBACK param;
	param.iCol = iCol;
	param.pListCtrl = this;
	ListView_SortItemsEx(GetSafeHwnd(), SortFunc, (LPARAM)&param);
}