#include "stdafx.h"
#include "Endox.h"
#include "NomenclatoreListCtrl.h"

#include <io.h>
#include <math.h>

#include "Common.h"
#include "CustomDate.h"
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

CNomenclatoreListCtrl::CNomenclatoreListCtrl(CEsamiView* pEsamiView)
	: CListCtrl()
{
	ZeroMemory(m_fColumnWidthForPrinter, 255 * sizeof(float));
	ZeroMemory(m_fColumnWidth, 255 * sizeof(float));

	m_nCaselleImpostate = 0;
	m_strNotePiePagina = "";
	m_pEsamiView = pEsamiView;

	m_fontTable.lfWidth		     = 0;
	m_fontTable.lfEscapement	 = 0;
	m_fontTable.lfOrientation	 = 0;
	m_fontTable.lfStrikeOut	     = 0;
	m_fontTable.lfCharSet		 = 0;
	m_fontTable.lfOutPrecision   = 1;
	m_fontTable.lfClipPrecision  = 2;
	m_fontTable.lfQuality		 = 1;
	m_fontTable.lfPitchAndFamily = 34;
	m_fontTable.lfHeight 		 = -14;
	m_fontTable.lfWeight 		 = 400;
	m_fontTable.lfItalic 		 = 0;
	m_fontTable.lfUnderline 	 = 0;
	strcpy_s(m_fontTable.lfFaceName, "Tahoma");

	m_fAltezzaMmNumeroPagina = 10;
	m_fAltezzaMmRigaIntestazione = 10;
	m_fAltezzaMmRiga = 10;
}

CNomenclatoreListCtrl::~CNomenclatoreListCtrl()
{
	ResetIntestazioneData();
}

int CNomenclatoreListCtrl::InsertColumn(int nCol, LPCTSTR lpszColumnHeading, int nFormat)
{
	int nWidth = LVSCW_AUTOSIZE;
	return CListCtrl::InsertColumn(nCol, lpszColumnHeading, nFormat, nWidth);
}

int CNomenclatoreListCtrl::GetColumnNumber()
{
	return GetHeaderCtrl()->GetItemCount();
}

int CNomenclatoreListCtrl::GetRowNumber()
{
	return GetItemCount();
}

void CNomenclatoreListCtrl::Export(CString strTitle)
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

		CFileDialog FileDlg(FALSE, NULL, NULL, OFN_READONLY | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, strFilter, this, 0, FALSE);
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
					bContinue = html.CreateFile(strFileExport, "Nomenclatore " + theApp.m_sNomeProgramma, GetColumnNumber());
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

		for(int i = 0; i <= GetRowNumber(); i++)
		{
			for(int j = 0; j < GetColumnNumber(); j++)
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
						// Per evitare errore di visualizzazione..
						if (j < GetColumnNumber() - 1)
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
			for(int j = 0; j < GetColumnNumber(); j++)
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

void CNomenclatoreListCtrl::Print() 
{
	CDC dc;
    CMyPrintDialog printDlg(FALSE);

    if (printDlg.DoModal() != IDOK)
        return;

	/* Sandro Gallina - 28/05/2004 - !!! DA SISTEMARE !!! -->
	DEVMODE* pDevMode = printDlg.GetDevMode();
	pDevMode->dmOrientation = DMORIENT_LANDSCAPE;
	GlobalUnlock(pDevMode);
	<-- Sandro Gallina - 28/05/2004 */

    dc.Attach(printDlg.GetPrinterDC());
    dc.m_bPrinting = TRUE;

	TCHAR szDocName[255];
	strcpy_s(szDocName, theApp.m_sNomeProgramma);

	DOCINFO di;
    memset(&di, 0, sizeof (DOCINFO));
    di.cbSize = sizeof (DOCINFO);
    di.lpszDocName = szDocName;

    BOOL bPrintingOK = dc.StartDoc(&di);

    CPrintInfo Info;
	
	Info.m_rectDraw.SetRect(0, 0, dc.GetDeviceCaps(HORZRES), dc.GetDeviceCaps(VERTRES));

	CalculateColumnWidth(Info.m_rectDraw.Width());

    OnPrint(&dc, &Info);
    
    if (bPrintingOK)
        dc.EndDoc();
    else
        dc.AbortDoc();

    dc.Detach();
}

void CNomenclatoreListCtrl::OnBeginPrinting(CDC *pDC, CPrintInfo *pInfo)
{
}

void CNomenclatoreListCtrl::OnPrint(CDC *pDC, CPrintInfo *pInfo)
{
    if (!pDC || !pInfo)
		return;
    
	int nPageWidth  = pInfo->m_rectDraw.Width();
	int nPageHeight = pInfo->m_rectDraw.Height();
	int nColumn = GetColumnNumber();
	int nRighePerPagina;
	int nRigheIntestazione = GetAltezzaIntestazioneRighe();
	CRect rect;

	CClientDC dcForm(this);
	int rapXP = pDC->GetDeviceCaps(LOGPIXELSX);
	int rapYP = pDC->GetDeviceCaps(LOGPIXELSY);
	int rapXV = dcForm.GetDeviceCaps(LOGPIXELSX);
	int	rapYV = dcForm.GetDeviceCaps(LOGPIXELSY);

	// Sandro Gallina - 27/05/2004 --> //
	int nAltezzaNumeroPagina     = (int)((m_fAltezzaMmNumeroPagina     / 25.4f) * rapYP);
	int nAltezzaRigaIntestazione = (int)((m_fAltezzaMmRigaIntestazione / 25.4f) * rapYP);
	int nAltezzaRiga             = (int)((m_fAltezzaMmRiga             / 25.4f) * rapYP);
	// <-- Sandro Gallina - 27/05/2004 //

	LOGFONT lfFont = m_fontTable;
	lfFont.lfHeight = MulDiv(lfFont.lfHeight, rapYP, rapYV);
	lfFont.lfWidth  = MulDiv(lfFont.lfWidth,  rapXP, rapXV);

	CFont fontNormal; 
	fontNormal.CreateFontIndirect(&lfFont);

	// lfFont.lfWeight = FW_BOLD;

	CFont fontPieDiPagina;
	fontPieDiPagina.CreateFontIndirect(&lfFont);

	int nAltezzaHeader = 0;
	int nAltezzaFooter = 0; 

	if (GetStampaImmaginiIDHeader() > 0)
		nAltezzaHeader = (int)((float)m_pEsamiView->GetAltezzaHF(GetStampaImmaginiIDHeader()) / 25.4f * (float)rapYP);
	
	if (GetStampaImmaginiIDFooter() > 0)
		nAltezzaFooter = (int)((float)m_pEsamiView->GetAltezzaHF(GetStampaImmaginiIDFooter()) / 25.4f * (float)rapYP);

	//Le righe per pagina sono diminuite di 1 per intestazione
	//il valore totale dello spazio disponibile viene diminuito di 20 per numero pagina
	nRighePerPagina = (nPageHeight - nAltezzaHeader - nAltezzaFooter - nAltezzaNumeroPagina - (nAltezzaRigaIntestazione * nRigheIntestazione)) / nAltezzaRiga;

	HDITEM hdItem;
	char lpBuffer[256];
	hdItem.mask = HDI_TEXT;
	hdItem.pszText = lpBuffer;
	hdItem.cchTextMax = 256;

	CSize szText;
	UINT nOptions;
	CString strText;
	
	//pDC->Rectangle(&pInfo->m_rectDraw);

	int nCountPerPage = 1;
	
//	rect = CRect(0, nAltezzaHeader + nAltezzaRigaIntestazione * nRigheIntestazione, (int)((float)m_nColumnWidthForPrinter[0] / 360.0f * (float)rapXP), nAltezzaHeader + nAltezzaRigaIntestazione * nRigheIntestazione + nAltezzaRiga); // Sandro Gallina - 28/05/2004 //
	rect = CRect(0, 
		         nAltezzaHeader + nAltezzaRigaIntestazione * nRigheIntestazione, 
				 (int)m_fColumnWidthForPrinter[0], 
				 nAltezzaHeader + nAltezzaRigaIntestazione * nRigheIntestazione + nAltezzaRiga);
	pDC->SelectObject(&fontNormal);

	CBrush* pOldBrush;
	CBrush brSfondo(RGB(250, 250, 250));
	BOOL bRigaPari = FALSE;

	for(int i = 0; i < GetRowNumber(); i++)
	{
		if ((i % nRighePerPagina) == 0)
		{
			//Fine pagina, inizio nuova
			if (i != 0) 
				pDC->EndPage();

			pDC->StartPage();

			/* MERDA
			if (theApp.m_lIDHeaderDefault > 0)
				m_pEsamiView->PrintHeader(theApp.m_lIDHeaderDefault, pDC, pDC);
			
			if (theApp.m_lIDFooterDefault > 0)
				m_pEsamiView->PrintFooter(theApp.m_lIDFooterDefault, pDC, pDC);
			MERDA */

			//-------------------------------------------------------------------------
			// 07/05/2003 - Aggiunta numero di pagina
			CString strPagina;
			CFont* oldFont;
			
			int nConst = 1, nPagine;
			if (GetRowNumber() % nRighePerPagina == 0)
				nConst = 0;
			nPagine = (int)((float)GetRowNumber() / (float)nRighePerPagina) + nConst;
			
			rect = CRect(0, pInfo->m_rectDraw.Height() - nAltezzaFooter - nAltezzaNumeroPagina, pInfo->m_rectDraw.Width(), pInfo->m_rectDraw.Height() - nAltezzaFooter);
			strPagina.Format("%sPagina %i di %i", m_strNotePiePagina, (int)((float)i / (float)nRighePerPagina) + 1, nPagine);

			oldFont = (CFont*)pDC->SelectObject(&fontPieDiPagina);
			pDC->DrawText(strPagina, &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
			pDC->SelectObject(oldFont);
			//-------------------------------------------------------------------------

			nCountPerPage = 1;
//			rect = CRect(0, nAltezzaHeader + nAltezzaRigaIntestazione * nRigheIntestazione, (int)((float)m_nColumnWidthForPrinter[0] / 360.0f * (float)rapXP), nAltezzaHeader + nAltezzaRigaIntestazione * nRigheIntestazione + nAltezzaRiga); // Sandro Gallina / 28/05/2004 //
			rect = CRect(0, 
				         nAltezzaHeader + nAltezzaRigaIntestazione * nRigheIntestazione, 
						 (int)m_fColumnWidthForPrinter[0], 
						 nAltezzaHeader + nAltezzaRigaIntestazione * nRigheIntestazione + nAltezzaRiga);

			PrintIntestazione(pDC, &fontPieDiPagina);
		}
		
		LVCOLUMN lvTemp;
		CRect rectTemp;
		if (!IsEmptyRow(i))
		{
			for(int j = 0; j < nColumn; j++)
			{
				pDC->SelectObject(&fontNormal);
				CFont fontCell;

				//Cerco nella lista il font per la cella
				for(POSITION pos = m_ListaStile.GetHeadPosition(); pos;)
				{
					tagStile Style = m_ListaStile.GetNext(pos);
					if (Style.nColonna == j && Style.nRiga == i)
					{
						fontCell.CreateFontIndirect(&Style.lfFont);
						pDC->SelectObject(&fontCell);
					}
				}

				//Sfondo rettangolo
				//if (bRigaPari)
				//	pOldBrush = pDC->SelectObject(&brSfondo);
				//else
				pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH); 
				
				pDC->Rectangle(&rect);
				pDC->SelectObject(pOldBrush);

				//Testo
				strText = GetItemText(i, j);
				szText = pDC->GetTextExtent(strText);

				if (szText.cx < rect.Width())
					nOptions = DT_EXPANDTABS|/*DT_CENTER|*/DT_WORDBREAK|DT_SINGLELINE|DT_VCENTER;
				else
					nOptions = DT_EXPANDTABS|/*DT_CENTER|*/DT_WORDBREAK;


				// Sandro Gallina - 03/02/2004 --> //
				lvTemp.mask = LVCF_FMT;
				this->GetColumn(j, &lvTemp);
				if ((lvTemp.fmt & LVCFMT_CENTER) > 0)
					nOptions += DT_CENTER;
				else
					if ((lvTemp.fmt & LVCFMT_RIGHT) > 0)
						nOptions += DT_RIGHT;
					else
						nOptions += DT_LEFT;
				// <-- Sandro Gallina - 03/02/2004 //

				// Sandro Gallina - 26/05/2004 --> //
				rectTemp = rect;
				rectTemp.DeflateRect(20, 5);

/*				rectTemp.top = (long)((float)rectTemp.top * rapYP / 360.0f);
				rectTemp.bottom = (long)((float)rectTemp.bottom * rapYP / 360.0f);
				rectTemp.left = (long)((float)rectTemp.left * rapXP / 360.0f);
				rectTemp.right = (long)((float)rectTemp.right * rapXP / 360.0f);*/
				// <-- Sandro Gallina - 26/05/2004 //

				pDC->DrawText(strText, &rectTemp, nOptions);

				// Spostamento alla colonna adiacente //
//				rect.InflateRect((int)((float)-m_nColumnWidthForPrinter[j] / 360.0f * (float)rapXP), 0, (int)((float)m_nColumnWidthForPrinter[j + 1] / 360.0f * (float)rapXP), 0); // Sandro Gallina - 28/05/2004 //
				rect.InflateRect((int)-m_fColumnWidthForPrinter[j], 0, (int)m_fColumnWidthForPrinter[j + 1], 0);
			}
		}
		
/*		rect = CRect(0, 
					 nAltezzaHeader + nAltezzaRigaIntestazione * nRigheIntestazione + nAltezzaRiga * nCountPerPage, 
					 (int)((float)m_nColumnWidthForPrinter[0] / 360.0f * (float)rapXP), 
					 nAltezzaHeader + nAltezzaRigaIntestazione * nRigheIntestazione + nAltezzaRiga * (nCountPerPage + 1)); Sandro Gallina - 28/05/2004 */
		rect = CRect(0, 
					 nAltezzaHeader + nAltezzaRigaIntestazione * nRigheIntestazione + nAltezzaRiga * nCountPerPage, 
					 (int)m_fColumnWidthForPrinter[0], 
					 nAltezzaHeader + nAltezzaRigaIntestazione * nRigheIntestazione + nAltezzaRiga * (nCountPerPage + 1));
		
		nCountPerPage++;
		bRigaPari = !bRigaPari;
	}
}

void CNomenclatoreListCtrl::OnEndPrinting(CDC *pDC, CPrintInfo *pInfo)
{
}

void CNomenclatoreListCtrl::PrintIntestazione(CDC *pDC, CFont* font)
{
	CRect rect;
	CBrush brSfondo(RGB(240, 240, 240));
	int rapXP = pDC->GetDeviceCaps(LOGPIXELSX);
	int rapYP = pDC->GetDeviceCaps(LOGPIXELSY);
	int nAltezzaHeader = 0;
	int nSommaInizioX, nSommaFineX, nSommaInizioY, nSommaFineY;
	int nAltezzaRigaIntestazione = (int)((m_fAltezzaMmRigaIntestazione / 25.4f) * rapYP);
	
	if (GetStampaImmaginiIDHeader() > 0)
		nAltezzaHeader = (int)((double)m_pEsamiView->GetAltezzaHF(GetStampaImmaginiIDHeader()) / 25.4 * (double)rapYP);
	
	CFont* pOldFont = pDC->SelectObject(font);

	for(int i = 0; i < m_nCaselleImpostate; i++)
	{
		nSommaInizioX = 0;
		nSommaFineX   = 0;
		nSommaInizioY = 0;
		nSommaFineY   = 0;
		
		for(int j = 0; j < m_FormatoIntestazione[i].nColonna; j++)
			nSommaInizioX += (int)m_fColumnWidthForPrinter[j];
//			nSommaInizioX += (int)((float)m_nColumnWidthForPrinter[j] / 360.0f * (float)rapXP); // Sandro Gallina - 28/05/2004 //

		for(int j = 0; j < m_FormatoIntestazione[i].nLarghezza; j++)
			nSommaFineX += (int)m_fColumnWidthForPrinter[j + m_FormatoIntestazione[i].nColonna];
//			nSommaFineX += (int)((float)(m_nColumnWidthForPrinter[j + m_FormatoIntestazione[i].nColonna]) / 360.0f * (float)rapXP); // Sandro Gallina - 28/05/2004 //

		nSommaInizioY = nAltezzaHeader + nAltezzaRigaIntestazione * m_FormatoIntestazione[i].nRiga;
		nSommaFineY   = nSommaInizioY + nAltezzaRigaIntestazione * m_FormatoIntestazione[i].nAltezza;
		
		rect = CRect(nSommaInizioX, nSommaInizioY, nSommaInizioX + nSommaFineX, nSommaFineY);
		
		CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
		//pOldBrush = pDC->SelectObject(&brSfondo);
		pDC->Rectangle(&rect);
		pDC->SelectObject(pOldBrush);
		
		pDC->DrawText(m_FormatoIntestazione[i].pTesto, &rect, DT_EXPANDTABS|DT_CENTER|DT_WORDBREAK|DT_SINGLELINE|DT_VCENTER);
	}

	pDC->SelectObject(pOldFont);
}

int CNomenclatoreListCtrl::GetAltezzaIntestazioneRighe()
{
	int nMax = 0;
	
	for(int i = 0; i < m_nCaselleImpostate; i++)
		if (m_FormatoIntestazione[i].nAltezza + m_FormatoIntestazione[i].nRiga > nMax)
			nMax = m_FormatoIntestazione[i].nAltezza + m_FormatoIntestazione[i].nRiga;

	return nMax;
}

void CNomenclatoreListCtrl::SetColumnWidthForPrint(int nColumn, float fPercentual)
{
	if (nColumn >= GetColumnNumber())
		return;

	if (fPercentual > 99)
		return;

	m_fColumnWidth[nColumn] = fPercentual;

	float fSomma = 0;
	for(int i = 0; i < GetColumnNumber(); i++)
		fSomma += m_fColumnWidth[i];

	if (fSomma > 100)
		TRACE("Errore in CNomenclatoreListCtrl: La percentuale non può essere maggiore di 100");
}

void CNomenclatoreListCtrl::SetIntestazioneData(int nRiga, int nColonna, int nLarghezza, int nAltezza, CString strTesto)
{
	ASSERT(m_nCaselleImpostate < 255);

	m_FormatoIntestazione[m_nCaselleImpostate].nRiga      = nRiga;
	m_FormatoIntestazione[m_nCaselleImpostate].nColonna   = nColonna;
	m_FormatoIntestazione[m_nCaselleImpostate].nLarghezza = nLarghezza;
	m_FormatoIntestazione[m_nCaselleImpostate].nAltezza   = nAltezza;
	// m_FormatoIntestazione[m_nCaselleImpostate].sTesto     = strTesto;
	strcpy_s(m_FormatoIntestazione[m_nCaselleImpostate].pTesto, strTesto);

	m_nCaselleImpostate++;
}

void CNomenclatoreListCtrl::ResetIntestazioneData()
{
	m_nCaselleImpostate = 0;
}

void CNomenclatoreListCtrl::SetTableStyle(LOGFONT font)
{
	m_fontTable = font;
}

LOGFONT CNomenclatoreListCtrl::GetTableStyle()
{
	return m_fontTable;
}

void CNomenclatoreListCtrl::SetCellStyle(int nRiga, int nColonna, LOGFONT font)
{
	tagStile Style, ListaStyle;
	POSITION pos, posOld;
	BOOL bInserito = FALSE;
	
	Style.nRiga    = nRiga;
	Style.nColonna = nColonna;
	Style.lfFont   = font;

	pos = m_ListaStile.GetHeadPosition();

	//Se la cella ha già un formato, aggiungo il formato nuovo
	while (pos != NULL)
	{
		posOld = pos;
		ListaStyle = m_ListaStile.GetNext(pos);

		if (ListaStyle.nColonna == nColonna && ListaStyle.nRiga == nRiga)
		{
			ListaStyle.lfFont = font;
			m_ListaStile.SetAt(posOld, ListaStyle);
			bInserito = TRUE;
		}
	}
	
	//Altrimenti la inserisco ex-novo
	if (!bInserito)
		m_ListaStile.AddTail(Style);
}

void CNomenclatoreListCtrl::SetNotePiePagina(CString strNote)
{
	m_strNotePiePagina = strNote;
}

//Funzione per ottimizzare larghezza colonne in stampa
void CNomenclatoreListCtrl::CalculateColumnWidth(int nLarghezzaRect)
{
	int nColonne = 0;
	float fSomma = 0, fColumnDim = 0;
	
	//Sommo percentuali colonne settate
	for(int i = 0; i < GetColumnNumber(); i++)
	{
		fSomma += m_fColumnWidth[i];
		if (m_fColumnWidth[i] != 0)
			nColonne++;
	}
	
	//Trovo la dimensione corretta per le altre colonne
	if (GetColumnNumber() - nColonne != 0)
		fColumnDim = (100 - fSomma) / (GetColumnNumber() - nColonne);

	for(int i = 0; i < GetColumnNumber(); i++)
	{
		if (m_fColumnWidth[i] == 0)
			m_fColumnWidth[i] = fColumnDim;

		m_fColumnWidthForPrinter[i] = ((m_fColumnWidth[i] / 100.0f) * (float)nLarghezzaRect); // Sandro Gallina - 28/05/2004 //
	}
}

BOOL CNomenclatoreListCtrl::IsEmptyRow(int nRow)
{
	BOOL bReturn = TRUE;

	for(int i = 0; i < GetColumnNumber(); i++)
		if (!GetItemText(nRow, i).IsEmpty())
			bReturn = FALSE;
	
	return bReturn;
}