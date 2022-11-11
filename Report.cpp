#include "stdafx.h"
#include "Endox.h"
#include "Report.h"
#include "BaseForm.h"
#include "EsamiView.h"
#include "common.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define RGB_REPORT_1 RGB(207, 207, 207)
#define RGB_REPORT_2 RGB(255, 255, 127)

HDC AFXAPI AfxCreateDC(HGLOBAL hDevNames, HGLOBAL hDevMode);

CReport::CReport()
{
	m_rectPage = CRect();

	m_pLinguetta = NULL;
	m_pos = NULL;
}

CReport::~CReport()
{
}

void CReport::Draw(CDC* pDC, CWnd* pWnd)
{
	CRect rect;
	pWnd->GetClientRect(rect);
	rect.DeflateRect(1, 1, 1, 1);
			
	// Griglia...
	CPen pen10mm(PS_DOT, 1, RGB(0,0,0));
	CPen* pOldPen = pDC->SelectObject(&pen10mm);
	for(int x = 1; x < DEF_X2; x++)
	{
		pDC->MoveTo((int)((float)rect.right / (float)DEF_X2 * (float)x), 0);
		pDC->LineTo((int)((float)rect.right / (float)DEF_X2 * (float)x), rect.bottom);
	}
	for(int y = 1; y < DEF_Y; y++)
	{
		pDC->MoveTo(0, (int)((float)rect.bottom / (float)DEF_Y * (float)y));
		pDC->LineTo(rect.right, (int)((float)rect.bottom / (float)DEF_Y * (float)y));
	}
	pDC->SelectObject(pOldPen);

	// draw report objects //
	if (m_pLinguetta != NULL)
	{
		CString strText;

		CBrush brush(RGB(224, 224, 224));
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));

		CBrush* pOldBrush = pDC->SelectObject(&brush);
		CPen* pOldPen = pDC->SelectObject(&pen);
		CFont* pOldFont = pDC->SelectObject(&theApp.m_fontBold);

		COLORREF oldColor = pDC->GetTextColor();
		int oldBkMode = pDC->SetBkMode(TRANSPARENT);

		// disegno la parte eventualmente riservata all'album //
		DrawAlbumArea(pDC, pWnd, m_pLinguetta->lMostraAlbum);

		POSITION pos = m_pLinguetta->listCampi.GetHeadPosition();
		while(pos != NULL)
		{
			int iX = m_pLinguetta->listCampi.GetAt(pos).lX;
			int iY = m_pLinguetta->listCampi.GetAt(pos).lY;
			int iL = m_pLinguetta->listCampi.GetAt(pos).lL;
			int iA = m_pLinguetta->listCampi.GetAt(pos).lA;
			int iTabOrder = m_pLinguetta->listCampi.GetAt(pos).lTabOrder;

			if (m_pLinguetta->listCampi.GetAt(pos).lColore >= 0)
				pDC->SetTextColor(theApp.m_color[m_pLinguetta->listCampi.GetAt(pos).lColore % 6]);
			else
				pDC->SetTextColor(RGB(0, 0, 0));

			pDC->SelectObject(&theApp.m_fontReport);

			// rettangolo //

			CRect rectObj(rect.right * iX / DEF_X2, rect.bottom * iY / DEF_Y, (rect.right * (iX + iL) / DEF_X2) + 1, (rect.bottom * (iY + iA) / DEF_Y) + 1);
			if (pos == m_pos)
			{
				CBrush brushSel;
				switch(m_pLinguetta->listCampi.GetAt(pos).lColore)
				{
					case 0:
					{
						brushSel.CreateSolidBrush(RGB(255, 0, 0));
						break;
					}
					case 1:
					{
						brushSel.CreateSolidBrush(RGB(255, 255, 0));
						break;
					}
					case 2:
					{
						brushSel.CreateSolidBrush(RGB(0, 255, 0));
						break;
					}
					case 3:
					{
						brushSel.CreateSolidBrush(RGB(0, 255, 255));
						break;
					}
					case 4:
					{
						brushSel.CreateSolidBrush(RGB(0, 0, 255));
						break;
					}
					case 5:
					{
						brushSel.CreateSolidBrush(RGB(255, 0, 255));
						break;
					}
					default:
					{
						brushSel.CreateSolidBrush(RGB(255, 255, 255));
						break;
					}
				}

				CBrush* pTempBrush = pDC->SelectObject(&brushSel);
				pDC->Rectangle(rectObj);
				pDC->SelectObject(pTempBrush);
			}
			else
			{
				pDC->Rectangle(rectObj);
			}

			rectObj.DeflateRect(2, 0, 3, 1);

			// scritta POS //
			strText.Format("X=%d  Y=%d", iX, iY);
			pDC->DrawText(strText, &rectObj, DT_TOP | DT_LEFT | DT_SINGLELINE);

			// scritta DIM //
			strText.Format("L=%d  A=%d", iL, iA);
			pDC->DrawText(strText, &rectObj, DT_BOTTOM | DT_RIGHT | DT_SINGLELINE);

			// scritta contenuto //
			BOOL bFound = FALSE;
			for(int i = 0; i < form_list_total; i++)
			{
				if (g_FormCaract[i].lID == m_pLinguetta->listCampi.GetAt(pos).lContenuto)
				{
					CString strTemp;
					if (g_FormCaract[i].sDescrizione.IsEmpty())
						strTemp.Format("%d" + GetStringCampoLiberoDatabase(i), iTabOrder);
					else
						strTemp.Format("%d - %s" + GetStringCampoLiberoDatabase(i), iTabOrder, g_FormCaract[i].sDescrizione);

					pDC->SelectObject(&theApp.m_fontBig);
					pDC->DrawText(strTemp, &rectObj, DT_VCENTER | DT_CENTER | DT_SINGLELINE);

					bFound = TRUE;
					break;
				}
			}
			if (!bFound)
			{
				CString strTemp;
				strTemp.Format("%d", iTabOrder);
				pDC->SelectObject(&theApp.m_fontBig);
				pDC->DrawText(strTemp, &rectObj, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
			}

			// - //
			m_pLinguetta->listCampi.GetNext(pos);
		}

		pDC->SetTextColor(oldColor);
		pDC->SetBkMode(oldBkMode);

		pDC->SelectObject(pOldFont);
		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOldPen);

		pen.DeleteObject();
		brush.DeleteObject();
	}

	// Disegno margini pagina...
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	pOldPen = pDC->SelectObject(&pen);
	pDC->MoveTo(0, 0);
	pDC->LineTo(rect.right, 0);
	pDC->LineTo(rect.right, rect.bottom);
	pDC->LineTo(0, rect.bottom);
	pDC->LineTo(0, 0);
	pDC->SelectObject(pOldPen);
}

void CReport::DrawAlbumArea(CDC* pDC, CWnd* pWnd, int lAlbumType)
{
	switch(lAlbumType)
	{
		case 1: // album fisso //
		{
			CRect rect;
			pWnd->GetClientRect(rect);
			rect.DeflateRect(1, 1, 1, 1);

			CRect rectFill = CRect((rect.right / 2) + 1, rect.top, rect.right, rect.bottom);
			CBrush brush1(HS_DIAGCROSS, RGB(128, 128, 128));
			pDC->FillRect(rectFill, &brush1);

			pDC->SelectObject(&theApp.m_fontBig);
			pDC->SetBkColor(RGB(255, 255, 255));
			pDC->SetBkMode(OPAQUE);
			pDC->DrawText(theApp.GetMessageString(IDS_INTERFACCIAOPERATORE_ALBUM1), &rectFill, DT_TOP | DT_LEFT | DT_SINGLELINE);
			pDC->DrawText(theApp.GetMessageString(IDS_INTERFACCIAOPERATORE_ALBUM1), &rectFill, DT_TOP | DT_RIGHT | DT_SINGLELINE);
			pDC->DrawText(theApp.GetMessageString(IDS_INTERFACCIAOPERATORE_ALBUM1), &rectFill, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
			pDC->DrawText(theApp.GetMessageString(IDS_INTERFACCIAOPERATORE_ALBUM1), &rectFill, DT_BOTTOM | DT_LEFT | DT_SINGLELINE);
			pDC->DrawText(theApp.GetMessageString(IDS_INTERFACCIAOPERATORE_ALBUM1), &rectFill, DT_BOTTOM | DT_RIGHT | DT_SINGLELINE);
			pDC->SetBkMode(TRANSPARENT);

			break;
		}
		case 2: // album mobile default visibile //
		{
			CRect rect;
			pWnd->GetClientRect(rect);
			rect.DeflateRect(1, 1, 1, 1);

			CRect rectFill = CRect((rect.right / 2) + 1, rect.top, rect.right, rect.bottom);
			CBrush brush1(HS_CROSS, RGB(128, 128, 128));
			pDC->FillRect(rectFill, &brush1);

			pDC->SelectObject(&theApp.m_fontBig);
			pDC->SetBkColor(RGB(255, 255, 255));
			pDC->SetBkMode(OPAQUE);
			pDC->DrawText(theApp.GetMessageString(IDS_INTERFACCIAOPERATORE_ALBUM2), &rectFill, DT_TOP | DT_LEFT | DT_SINGLELINE);
			pDC->DrawText(theApp.GetMessageString(IDS_INTERFACCIAOPERATORE_ALBUM2), &rectFill, DT_TOP | DT_RIGHT | DT_SINGLELINE);
			pDC->DrawText(theApp.GetMessageString(IDS_INTERFACCIAOPERATORE_ALBUM2), &rectFill, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
			pDC->DrawText(theApp.GetMessageString(IDS_INTERFACCIAOPERATORE_ALBUM2), &rectFill, DT_BOTTOM | DT_LEFT | DT_SINGLELINE);
			pDC->DrawText(theApp.GetMessageString(IDS_INTERFACCIAOPERATORE_ALBUM2), &rectFill, DT_BOTTOM | DT_RIGHT | DT_SINGLELINE);
			pDC->SetBkMode(TRANSPARENT);

			break;
		}
		case 3: // album mobile default nascosto //
		{
			CRect rect;
			pWnd->GetClientRect(rect);
			rect.DeflateRect(1, 1, 1, 1);

			CRect rectFill = CRect((rect.right / 2) + 1, rect.top, rect.right, rect.bottom);
			CBrush brush1(HS_CROSS, RGB(128, 128, 128));
			pDC->FillRect(rectFill, &brush1);

			pDC->SelectObject(&theApp.m_fontBig);
			pDC->SetBkColor(RGB(255, 255, 255));
			pDC->SetBkMode(OPAQUE);
			pDC->DrawText(theApp.GetMessageString(IDS_INTERFACCIAOPERATORE_ALBUM3), &rectFill, DT_TOP | DT_LEFT | DT_SINGLELINE);
			pDC->DrawText(theApp.GetMessageString(IDS_INTERFACCIAOPERATORE_ALBUM3), &rectFill, DT_TOP | DT_RIGHT | DT_SINGLELINE);
			pDC->DrawText(theApp.GetMessageString(IDS_INTERFACCIAOPERATORE_ALBUM3), &rectFill, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
			pDC->DrawText(theApp.GetMessageString(IDS_INTERFACCIAOPERATORE_ALBUM3), &rectFill, DT_BOTTOM | DT_LEFT | DT_SINGLELINE);
			pDC->DrawText(theApp.GetMessageString(IDS_INTERFACCIAOPERATORE_ALBUM3), &rectFill, DT_BOTTOM | DT_RIGHT | DT_SINGLELINE);
			pDC->SetBkMode(TRANSPARENT);

			break;
		}
	}
}

STRUCT_LINGUETTA* CReport::GetLinguetta()
{
	return m_pLinguetta;
}

void CReport::SetLinguetta(STRUCT_LINGUETTA* pLinguetta)
{
	m_pLinguetta = pLinguetta;
}

POSITION CReport::GetCurSel()
{
	return m_pos;
}

void CReport::SetCurSel(POSITION pos)
{
	m_pos = pos;
}