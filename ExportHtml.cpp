#include "stdafx.h"
#include "Endox.h"
#include "ExportHtml.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CExportHtml::CExportHtml()
{
	m_hFile = NULL;
	m_bDispari = FALSE;
}

CExportHtml::~CExportHtml()
{

}

BOOL CExportHtml::CreateFile(CString strFileName, CString strTitolo, int nColonne)
{
	BOOL bReturn = TRUE;
	CString strColonne = "";

	if (nColonne > 0)
		strColonne.Format(" colspan=%d", nColonne);

	m_hFile = ::CreateFile(strFileName,
						   GENERIC_WRITE,
						   FILE_SHARE_WRITE,
						   NULL,
						   CREATE_ALWAYS,
						   FILE_ATTRIBUTE_NORMAL,
						   NULL);

	if (m_hFile == INVALID_HANDLE_VALUE)
		bReturn = FALSE;

	if (bReturn)
	{
		CString strValue;
		strValue  = "<html>\r\n";
		strValue += "<head>\r\n";
		strValue += "<title>Tesi Imaging - " + strTitolo + "</title>\r\n";
		strValue += "<style>\r\n";
		strValue += "table.cornice {\r\n";
		strValue += "   border-style = solid;\r\n";
		strValue += "   border-color : #ED8134;\r\n";
		strValue += "   border-width : 1pt;\r\n";
//		strValue += "   width : 90%;\r\n";
		strValue += "}\r\n";
		strValue += "tr.pari {\r\n";
		strValue += "    line-height : 20pt;\r\n";
		strValue += "    font-family : \"Verdana\";\r\n";
		strValue += "    font-size : 10pt;\r\n";
		strValue += "    background : #f0f0f0\r\n";
		strValue += "}\r\n";
		strValue += "tr.dispari {\r\n";
		strValue += "   line-height : 20pt;\r\n";
		strValue += "    font-family : \"Verdana\";\r\n";
		strValue += "    font-size : 10pt;\r\n";
		strValue += "    background : #ffffff\r\n";
		strValue += "}\r\n";
		strValue += "tr.intestazione {\r\n";
		strValue += "    font-family : \"Verdana\";\r\n";
		strValue += "    font-size : 10pt;\r\n";
		strValue += "      color : #ffffff;\r\n";
		strValue += "      font-weight : bold;\r\n";
		strValue += "      text-align : center;\r\n";
		strValue += "    background : #7A82A9\r\n";
		strValue += "}\r\n";
		strValue += "p.arancione {\r\n";
		strValue += "   font-family : \"Verdana\";\r\n";
		strValue += "   color : #ED8134;\r\n";
		strValue += "}\r\n";
		strValue += "</style>\r\n";
		strValue += "</head>\r\n";
		strValue += "<table align=\"center\" class=\"cornice\">\r\n";
		strValue += "<tr class=\"intestazione\">\r\n";
		strValue += "<td" + strColonne +">\r\n";
		
		WriteData(strValue.GetBuffer(0), strValue.GetLength());
	}

	return bReturn;
}

BOOL CExportHtml::CloseFile()
{
	BOOL bReturn;
	CString strValue;

	strValue = "</td>\r\n";
	strValue += "</tr>\r\n";
	strValue += "</table>\r\n";
	strValue += "</html>";
	
	WriteData(strValue.GetBuffer(0), strValue.GetLength());

	bReturn = CloseHandle(m_hFile);

	if (bReturn)
		m_hFile = NULL;

	return bReturn;
}


void CExportHtml::WriteTitle(CString strTitle)
{
	WriteValue(strTitle);

	CString strValue = "</td></tr>\r\n<tr class=\"intestazione\"><td>";
	WriteData(strValue.GetBuffer(0), strValue.GetLength());
}


void CExportHtml::WriteValue(CString strValue)
{
	WriteData(strValue.GetBuffer(0), strValue.GetLength());
}

void CExportHtml::WriteNewRow()
{
	CString strValue;

	if (m_bDispari)
		strValue = "</td></tr>\r\n<tr class=\"dispari\"><td>";
	else
		strValue = "</td></tr>\r\n<tr class=\"pari\"><td>";

	m_bDispari = 1 - m_bDispari;
	
	WriteData(strValue.GetBuffer(0), strValue.GetLength());
}

void CExportHtml::WriteNewColumn()
{
	CString strValue;

	strValue = "</td><td>";

	WriteData(strValue.GetBuffer(0), strValue.GetLength());
}

BOOL CExportHtml::WriteData(void* szBuffer, int nBufferSize)
{
	DWORD dwBytesWritten;
	BOOL bResult;
	
	bResult = WriteFile(m_hFile,
						szBuffer,	
						nBufferSize,
						&dwBytesWritten,
						NULL);

	return bResult;
}
