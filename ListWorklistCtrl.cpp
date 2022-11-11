#include "stdafx.h"
#include "Endox.h"
#include "ListWorklistCtrl.h"

#include "MyPrintDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CListWorklistCtrl::CListWorklistCtrl(void)
{
}

CListWorklistCtrl::~CListWorklistCtrl(void)
{
}

BEGIN_MESSAGE_MAP(CListWorklistCtrl, CListSortableCtrl)
END_MESSAGE_MAP()

void CListWorklistCtrl::SetNotePiePagina(CString strNote)
{
	m_sNotePiePagina = strNote;
}

void CListWorklistCtrl::Print() 
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

void CListWorklistCtrl::OnBeginPrinting(CDC *pDC, CPrintInfo *pInfo)
{
}

void CListWorklistCtrl::OnPrint(CDC *pDC, CPrintInfo *pInfo)
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

void CListWorklistCtrl::OnEndPrinting(CDC *pDC, CPrintInfo *pInfo)
{
}

void CListWorklistCtrl::CalculateColumnsWidthForPrint(int nRectWidth)
{
	for(int i = 0; i < 255; i++)
		m_iColumnWidthForPrinter[i] = 0;

	for(int i = 0; i < GetHeaderCtrl()->GetItemCount(); i++)
	{
		CRect rectTemp;
		CHeaderCtrl *tempCtrl = GetHeaderCtrl();
		tempCtrl->GetItemRect(i, &rectTemp);
		HDITEM hdi;
		TCHAR  lpBuffer[256];
		hdi.mask = HDI_TEXT;
		hdi.pszText = lpBuffer;
		hdi.cchTextMax = 256;		
		tempCtrl->GetItem(i, &hdi);
		CString titoloTemp;
		titoloTemp.Format("%s", hdi.pszText);

		for(POSITION pos=theApp.m_worklistFields.GetHeadPosition();pos;)
		{
			m_iColumnWidthForPrinter[i] = 0;

			worklistField tempField = theApp.m_worklistFields.GetNext(pos);
			if (tempField.sTitolo == titoloTemp)
			{
				m_iColumnWidthForPrinter[i] = (int)((double(nRectWidth)/100) * tempField.lDimensioneStampaPerc);				
				break;
			}
		}				
	}

}

void CListWorklistCtrl::PrintColumnHeaders(CDC* pDC, CFont* pFontBold, int nRectHeight)
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

void CListWorklistCtrl::PrintFooter(CDC* pDC, CPrintInfo *pInfo, CFont* pFontBold, int nRectHeight, int nPagina)
{
	CRect rectFooter = CRect(0, pInfo->m_rectDraw.Height() - nRectHeight, pInfo->m_rectDraw.Width(), pInfo->m_rectDraw.Height());

	CString sText;
	sText.Format("%s - %s %d", m_sNotePiePagina, theApp.GetMessageString(IDS_PAGINA), nPagina);

	pDC->SelectObject(pFontBold);
	pDC->DrawText(sText, &rectFooter, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
}