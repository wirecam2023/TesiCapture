#include "stdafx.h"
#include "TXTextControl23.h"
#include "Endox.h"
#include "InsertTableDlg.h"
#include "ImageSimple2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CTXTextControl23, CWnd)
IMPLEMENT_DYNCREATE(CTXTextControl23Ex, CTXTextControl23)

CTXTextControl23Ex::CTXTextControl23Ex()
{
	m_bAutoChanging = FALSE;
}

BEGIN_MESSAGE_MAP(CTXTextControl23Ex, CTXTextControl23)
	ON_WM_KEYDOWN()
	// ON_WM_KEYUP()
END_MESSAGE_MAP()

void CTXTextControl23Ex::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TRACE3("--> CTXTextControl23Ex::OnKeyDown(nChar %i, nRepCnt %i, nFlags %i)\n", nChar, nRepCnt, nFlags);

	if (theApp.m_bTextControlCopiaIncollaRimuoviFormattazione && (nChar == 0x56) && (GetKeyState(VK_CONTROL) < 0)) // V key + CTRL key //
	{
		// TRACE0("--> CTXTextControl23Ex::OnKeyDown --> CTRL + V !!!!! !!!!! !!!!! !!!!! !!!!!\n");

		if (GetCanPaste())
		{
			VARIANT var = GetClipboardFormats();
			if ((var.vt == 8194) && (var.parray != NULL)) // 8194 = array di short //
			{
				SAFEARRAY *pSA = var.parray;

				short* pPvData;
				HRESULT hr = SafeArrayAccessData(pSA, (void**)&pPvData);
				if (SUCCEEDED(hr))
				{
					long lLBound;
					SafeArrayGetLBound(pSA, 1, &lLBound);

					long lUBound;
					SafeArrayGetUBound(pSA, 1, &lUBound);

					long cElements = lUBound - lLBound + 1;
					if (cElements > 0)
					{
						BOOL bPasted = FALSE;

						// formato degli appunti:
						//	2 --> TXTextControlFormat		--> lo incollerei che non dovrebbero esserci sorprese
						//	3 --> RichTextFormat			--> NON lo incollerei che potrebbe contenere tag strani
						//	4 --> Image						--> NON la incollerei
						//	5 --> PlainText					--> lo incollerei come testo semplice
						//	6 --> OLEObject					--> NON lo incollerei
						//	7 --> TXTextControlTextframe	--> per il momento non lo incollerei ma se in futuro servisse ci si potrebbe pensare
						//	8 --> TXTextControlImage		--> NON lo incollerei
						//	9 --> HTMLFormat				--> NON lo incollerei che potrebbe contenere tag strani

						if (!bPasted)
						{
							for (int i = 0; i < cElements; ++i)
							{
								short shTemp = (short)pPvData[i];
								if (shTemp == 2) // TXTextControlFormat
								{
									bPasted = this->Paste(2); // TXTextControlFormat
									break;
								}
							}
						}

						if (!bPasted)
						{
							for (int i = 0; i < cElements; ++i)
							{
								short shTemp = (short)pPvData[i];
								if (shTemp == 5) // PlainText
								{
									bPasted = this->Paste(5); // PlainText
									break;
								}
							}
						}
					}

					SafeArrayUnaccessData(pSA);
				}

				SafeArrayDestroy(pSA);
			}
		}
	}
	else
	{
		CTXTextControl23::OnKeyDown(nChar, nRepCnt, nFlags);
	}
}

/*
void CTXTextControl23Ex::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TRACE3("--> CTXTextControl23Ex::OnKeyUp(nChar %i, nRepCnt %i, nFlags %i)\n", nChar, nRepCnt, nFlags);

	if ((nChar == 0x56) && (GetKeyState(VK_CONTROL) < 0)) // V key + CTRL key //
	{
		// TRACE0("--> CTXTextControl23Ex::OnKeyUp --> CTRL + V !!!!! !!!!! !!!!! !!!!! !!!!!\n");
	}
	else
	{
		CTXTextControl23::OnKeyUp(nChar, nRepCnt, nFlags);
	}
}
*/

CString CTXTextControl23Ex::GetHTMLSelText()
{
	CString sReturn = "";

	// Sandro 04/04/2017 // BUG 375 // i cazzoni del Fleury, non so come, avevano fatto delle checklist con l'interlinea schifo ed in html le righe del referto venivano sovrapposte //

	SetLineSpacing(100);

	//

	VARIANT varFormat;
	varFormat.vt = VT_I2;
	varFormat.iVal = 4; // HTML //

	VARIANT varCurSel;
	varCurSel.vt = VT_I2;
	varCurSel.iVal = 0;

	VARIANT varTemp = SaveToMemory(varFormat, varCurSel);
	if ((varTemp.vt == 8209) && (varTemp.parray != NULL)) // 8209 = array di UI1 //
	{
		SAFEARRAY *pSA = varTemp.parray;

		unsigned char* pPvData;
		HRESULT hr = SafeArrayAccessData(pSA, (void**)&pPvData);
		if (SUCCEEDED(hr))
		{
			long lLBound;
			SafeArrayGetLBound(pSA, 1, &lLBound);

			long lUBound;
			SafeArrayGetUBound(pSA, 1, &lUBound);

			long cElements = lUBound - lLBound + 1;

			if (cElements > 0)
				sReturn = CString(pPvData);

			SafeArrayUnaccessData(pSA);
		}

		SafeArrayDestroy(pSA);
	}

	// Sandro 17/02/2017 // problema degli spazi multipli nell'HTML che non vengono visualizzati //

	if (!sReturn.IsEmpty())
	{
		int nIndex = sReturn.Find("<p ");
		while (nIndex > 0)
		{
			int nInizio = sReturn.Find(">", nIndex);
			int nFine = sReturn.Find("</p>", nInizio);

			if ((nInizio > 0) && (nFine > 0))
			{
				CString sTeeemp = sReturn.Mid(nInizio + 1, nFine - (nInizio + 1));
				if (sTeeemp.GetLength() > 0)
				{
					// Sandro 01/06/2017 // non posso sostituire tutti gli spazi con il "&nbsp;" altrimenti le righe non vanno più a capo //
					// sTeeemp.Replace(" ", "&nbsp;");

					sTeeemp.TrimRight();

					for (int i = 50; i > 0; i--)
					{
						CString sOrig = "";
						CString sDest = "";

						for (int j = 0; j < i; j++)
						{
							sOrig += "  ";
							sDest += "&nbsp; ";
						}

						sTeeemp.Replace(sOrig, sDest);
					}

					if (sTeeemp[0] == ' ')
						sTeeemp = "&nbsp;" + sTeeemp.Mid(1);

					//

					CString sLeft = sReturn.Left(nInizio + 1);
					CString sMidd = sTeeemp;
					CString sRigh = sReturn.Mid(nFine);

					sReturn = sLeft + sMidd + sRigh;
				}
			}

			nIndex = sReturn.Find("<p ", nIndex + 1);
		}
	}

	sReturn.Replace("ERITROBLASTOS ORTOCROMATICOS", "ERITROBLASTOS ORTOCROMATICOS&nbsp;");
	long lCellPadPos = sReturn.Find("cellpadding=\"");
	if (lCellPadPos > 0)
	{
		CString sCellPad = sReturn.Mid(lCellPadPos, (sReturn.Find("\"", lCellPadPos + 13) - lCellPadPos) + 1);
		CString sCellPadNew = sCellPad;

		CString sCellPadVal = sCellPad;
		sCellPadVal.Replace(sCellPad.Left(13), "");
		sCellPadVal.Replace("\"", "");
		sCellPadVal.Replace("pt", "px");
		
		if (sCellPadVal == "0px")
		{
			sCellPadNew = "cellpadding=\"0\"";
		}
		else
		{
			sCellPadNew = "cellpadding=\"" + sCellPadVal + "\"";
		}

		sReturn.Replace(sCellPad, sCellPadNew);
	}
	//

	return sReturn;
}

BOOL CTXTextControl23Ex::IsAutoChanging()
{
	return m_bAutoChanging;
}

//Julio - BUG 4392 Edicao de texto
void CTXTextControl23Ex::RtfSetFontProperties()
{
	FontDialog();
}
//Julio - BUG 4392 Edicao de texto
//Returns TRUE if a image was selected and FALSE if there were no image selected
BOOL CTXTextControl23Ex::RtfSetImageProperties()
{		
	/*  ObjectGetSelected
		Param Value  Description
	1   Looks only for objects positioned at a fixed geometrical position.
	2   Looks only for objects that act as a single character.
	4   Looks only for images.
	8   Looks only for objects which are externally created by the application.
	10  Looks only for OLE objects.
	20  Looks only for text frames.
	40  Looks only for objects that are anchored to a paragraph.
	*/

	short shSelected = ObjectGetSelected(4); //Looks only for images
	
	if (shSelected == 0)	
		return FALSE;	
	
	else
	{
		ObjectAttrDialog();	
		return TRUE;
	}
}

void CTXTextControl23Ex::RtfInsertNewTable(CWnd* pParent)
{
	short shTableId = GetTableAtInputPos();
	if (shTableId == 0)
	{
		if (GetTableCanInsert())
		{
			CInsertTableDlg dlg(pParent);
			if (dlg.DoModal() == IDOK)
			{
				srand((unsigned)time(NULL));
				rand();	rand();	rand(); rand();

				VARIANT varTemp1;
				varTemp1.vt = VT_I2;
				varTemp1.iVal = (rand() % (32767 - 10)) + 10;

				short shTableIdInserted = TableInsert(dlg.GetRows(), dlg.GetCols(), -1, varTemp1);

				if ((shTableIdInserted > 0) && (dlg.GetBordi() > 0))
				{
					VARIANT varTemp2;
					varTemp2.vt = VT_I2;
					varTemp2.iVal = dlg.GetBordi();

					put_TableCellAttribute(
						shTableIdInserted,
						0, /* tutte le righe */
						0, /* tutte le colonne */
						txTableCellBorderWidth,
						varTemp2
						);
				}
			}
		}
	}
	else
	{
//#ifdef _DEBUG
		//Julio - BUG 4392 Edicao de texto
		if (theApp.m_bRtfUsaConfigurazioniTabelle)
		{
		TableAttrDialog();

		short shRow = GetTableRowAtInputPos();
		short shCol = GetTableColAtInputPos();

		VARIANT var = get_TableCellAttribute(shTableId, shRow, shCol, 2);

		int asd = 0;
		}
//#endif /* _DEBUG */
	}
}

void CTXTextControl23Ex::RtfSelectedTextMakeUpper()
{
	m_bAutoChanging = TRUE;

	long lSelStart = GetSelStart();
	long lSelLength = GetSelLength();

	if (lSelLength > 0)
	{
		AfxGetApp()->BeginWaitCursor();
		SetRedraw(FALSE);

		for (long l = lSelStart; l < lSelStart + lSelLength; l++)
		{
			if (l == (lSelStart + lSelLength) - 1)
				m_bAutoChanging = FALSE;

			SetSelStart(l);
			SetSelLength(1);

			CString sTemp = GetSelText();
			sTemp.MakeUpper();
			SetSelText(sTemp);
		}

		SetSelStart(lSelStart);
		SetSelLength(lSelLength);

		SetRedraw(TRUE);
		RedrawWindow();
		AfxGetApp()->EndWaitCursor();
	}

	m_bAutoChanging = FALSE;
}

void CTXTextControl23Ex::RtfSelectedTextMakeNormal()
{
	m_bAutoChanging = TRUE;

	long lSelStart = GetSelStart();
	long lSelLength = GetSelLength();

	if (lSelLength > 0)
	{
		AfxGetApp()->BeginWaitCursor();
		SetRedraw(FALSE);

		CString sPrevPrev = "";
		CString sPrev = "";

		if (lSelStart > 1)
		{
			SetSelStart(lSelStart - 2);
			SetSelLength(1);
			sPrevPrev = GetSelText();
		}

		if (lSelStart > 0)
		{
			SetSelStart(lSelStart - 1);
			SetSelLength(1);
			sPrevPrev = GetSelText();
		}

		for (long l = lSelStart; l < lSelStart + lSelLength; l++)
		{
			if (l == (lSelStart + lSelLength) - 1)
				m_bAutoChanging = FALSE;

			SetSelStart(l);
			SetSelLength(1);

			CString sTemp = GetSelText();
			if ((l == lSelStart) || (((sPrevPrev == ".") || (sPrevPrev == "!") || (sPrevPrev == "?")) && ((sPrev == " ") || (sPrev == "\n"))))	// Marvel Carvalho - Bug 4450 Botão [Mm] inoperante na Edição do Laudo
				sTemp.MakeUpper();
			else
				sTemp.MakeLower();
			SetSelText(sTemp);

			sPrevPrev = sPrev;
			sPrev = sTemp;
		}

		SetSelStart(lSelStart);
		SetSelLength(lSelLength);

		SetRedraw(TRUE);
		RedrawWindow();
		AfxGetApp()->EndWaitCursor();
	}

	m_bAutoChanging = FALSE;
}

void CTXTextControl23Ex::RtfSelectedTextMakeLower()
{
	m_bAutoChanging = TRUE;

	long lSelStart = GetSelStart();
	long lSelLength = GetSelLength();

	if (lSelLength > 0)
	{
		AfxGetApp()->BeginWaitCursor();
		SetRedraw(FALSE);

		for (long l = lSelStart; l < lSelStart + lSelLength; l++)
		{
			if (l == (lSelStart + lSelLength) - 1)
				m_bAutoChanging = FALSE;

			SetSelStart(l);
			SetSelLength(1);

			CString sTemp = GetSelText();
			sTemp.MakeLower();
			SetSelText(sTemp);
		}

		SetSelStart(lSelStart);
		SetSelLength(lSelLength);

		SetRedraw(TRUE);
		RedrawWindow();
		AfxGetApp()->EndWaitCursor();
	}

	m_bAutoChanging = FALSE;
}
