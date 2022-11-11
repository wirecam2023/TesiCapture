#include "stdafx.h"
#include "Endox.h"
#include "CaricaReport.h"
#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CCaricaReport::CCaricaReport()
{
	m_nTotSection = 0;
	m_nTotFields  = 0;
	
	m_lIDHeader1 = 0;
	m_lIDHeader2 = 0;
	m_lIDFooter1 = 0;
	m_lIDFooter2 = 0;

	m_bIsEOF  = FALSE;

	m_nWidth  = 0;
	m_nHeight = 0;

	m_nPageWidth  = 0;
	m_nPageHeight = 0;
	m_nRowHeight  = 0;

	m_pElemReport = NULL;
	m_pElemSupp   = NULL;
	m_pElemFirst  = NULL;
}

CCaricaReport::~CCaricaReport()
{
}

BOOL CCaricaReport::OpenReportFile(CString strReportFile, BOOL bIsSearchReport)
{
	CString strSezione;
	
	m_strFileReport = strReportFile;
	m_bIsSearchReport = bIsSearchReport;
	
	// Informazioni generali
	m_nTotSection = GetPrivateProfileInt("List", "TotSection", 0, strReportFile);
	m_lIDHeader1 = GetPrivateProfileInt("Page", "IDHeader1", 0, strReportFile);
	m_lIDHeader2 = GetPrivateProfileInt("Page", "IDHeader2", 0, strReportFile);
	m_lIDFooter1 = GetPrivateProfileInt("Page", "IDFooter1", 0, strReportFile);
	m_lIDFooter2 = GetPrivateProfileInt("Page", "IDFooter2", 0, strReportFile);

	if (!bIsSearchReport)
	{
		m_nWidth  = GetPrivateProfileInt("Page", "Width",  0, strReportFile);
		m_nHeight = GetPrivateProfileInt("Page", "Height", 0, strReportFile);
	}
	else
	{
		m_nPageWidth  = GetPrivateProfileInt("Page", "PageWidth",  20, strReportFile);
		m_nPageHeight = GetPrivateProfileInt("Page", "PageHeight", 20, strReportFile);
		m_nRowHeight  = GetPrivateProfileInt("Page", "RowHeight",  10, strReportFile);
	}

	m_pElemReport = new ElementoReport;
	m_pElemFirst = m_pElemReport;

	for(int nSection = 1; nSection <= m_nTotSection; nSection++)
	{
		strSezione.Format("Section%li", nSection);
		
		// Tipo
		m_pElemReport->strType = GetPrivateProfileString("List", strSezione, "", strReportFile);

		if (m_pElemReport->strType == "Field")
			m_nTotFields++;
		
		// Valore
		m_pElemReport->strValue = GetPrivateProfileString(strSezione, "Value", "", strReportFile);
		
		// Dimensioni
		m_pElemReport->rectInMm.left = GetPrivateProfileInt(strSezione, "Left", 0, strReportFile);
		
		m_pElemReport->rectInMm.right = GetPrivateProfileInt(strSezione, "Right", 0, strReportFile);
		
		m_pElemReport->rectInMm.top = GetPrivateProfileInt(strSezione, "Top", 0, strReportFile);
		
		m_pElemReport->rectInMm.bottom = GetPrivateProfileInt(strSezione, "Bottom", 0, strReportFile);
		
		// Check
		m_pElemReport->nCheck = GetPrivateProfileInt(strSezione, "Check", 0, strReportFile);
		
		// Colore
		m_pElemReport->rgbColor = (COLORREF)GetPrivateProfileInt(strSezione, "Color", 0,  strReportFile);
		
		// Parametro
		m_pElemReport->nParam = GetPrivateProfileInt(strSezione, "Param", 0, strReportFile);

		// Allineamento
		m_pElemReport->nAlignment = GetPrivateProfileInt(strSezione, "Alignment", 0, strReportFile);

		// Rotazione
		m_pElemReport->nRotation = GetPrivateProfileInt(strSezione, "Rotation", 0, strReportFile);

		// Font
		m_pElemReport->lfFont.lfWidth         = 0;
		m_pElemReport->lfFont.lfEscapement    = 0;
		m_pElemReport->lfFont.lfOrientation   = 0;
		m_pElemReport->lfFont.lfStrikeOut	  = 0;
		m_pElemReport->lfFont.lfCharSet	      = 0;
		m_pElemReport->lfFont.lfOutPrecision  = 1;
		m_pElemReport->lfFont.lfClipPrecision = 2;
		m_pElemReport->lfFont.lfQuality	      = 1;
		
		strcpy_s(m_pElemReport->lfFont.lfFaceName, GetPrivateProfileString(strSezione, "Font Name", "MS Sans Serif", strReportFile));
		m_pElemReport->lfFont.lfPitchAndFamily = GetPrivateProfileInt(strSezione, "Font Family", 34, strReportFile);
		m_pElemReport->lfFont.lfHeight = GetPrivateProfileInt(strSezione, "Font Height", -13, strReportFile);
		m_pElemReport->lfFont.lfWeight = GetPrivateProfileInt(strSezione, "Font Weight", 400, strReportFile);
		m_pElemReport->lfFont.lfUnderline = GetPrivateProfileInt(strSezione, "Font Under", 0, strReportFile);
		m_pElemReport->lfFont.lfItalic = GetPrivateProfileInt(strSezione, "Font Italic", 0, strReportFile);
		
		if (nSection < m_nTotSection)
		{
			m_pElemReport->pElemNext = new ElementoReport;
			m_pElemReport = m_pElemReport->pElemNext;
		}
		else
			m_pElemReport->pElemNext = NULL;
	}
	
	MoveFirst();
	return TRUE;
}

BOOL CCaricaReport::CloseReportFile()
{
	MoveFirst();

	while (m_pElemReport->pElemNext != NULL)
	{
		m_pElemSupp = m_pElemReport->pElemNext;
		delete m_pElemReport;
		m_pElemReport = m_pElemSupp;
	}

	//Ultimo elemento
	if (m_pElemReport)
		delete m_pElemReport;
	
	return TRUE;
}

long CCaricaReport::GetTotSection()
{
	return m_nTotSection;
}

int CCaricaReport::GetNumberOfFields()
{
	return m_nTotFields;
}

long CCaricaReport::GetIDHeader1()
{
	return m_lIDHeader1;
}

long CCaricaReport::GetIDHeader2()
{
	return m_lIDHeader2;
}

long CCaricaReport::GetIDFooter1()
{
	return m_lIDFooter1;
}

long CCaricaReport::GetIDFooter2()
{
	return m_lIDFooter2;
}

CString CCaricaReport::GetFieldType()
{
	return m_pElemReport->strType;
}

CString CCaricaReport::GetFieldValue()
{
	return m_pElemReport->strValue;
}

CRect CCaricaReport::GetDimensionInMm()
{
	return m_pElemReport->rectInMm;
}

long CCaricaReport::GetCheck()
{
	return m_pElemReport->nCheck;
}

COLORREF CCaricaReport::GetColor()
{
	return m_pElemReport->rgbColor;
}

long CCaricaReport::GetParam()
{
	return m_pElemReport->nParam;
}

int CCaricaReport::GetAlignment()
{
	return m_pElemReport->nAlignment;
}

int CCaricaReport::GetRotation()
{
	return m_pElemReport->nRotation;
}

LOGFONT CCaricaReport::GetFont()
{
	return m_pElemReport->lfFont;
}

void CCaricaReport::MoveFirst()
{
	m_pElemReport = m_pElemFirst;
	m_bIsEOF = FALSE;
}

void CCaricaReport::MoveNext()
{
	if (m_pElemReport->pElemNext != NULL)
	{
		m_pElemReport = m_pElemReport->pElemNext;
	}
	else
		m_bIsEOF = TRUE;
}

BOOL CCaricaReport::IsLast()
{
	if (m_pElemReport->pElemNext == NULL)
		return TRUE;
	else
		return FALSE;
}

BOOL CCaricaReport::IsEOF()
{
	return m_bIsEOF;
}
