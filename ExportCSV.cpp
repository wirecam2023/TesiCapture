#include "stdafx.h"
#include "Endox.h"
#include "ExportCSV.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CExportCSV::CExportCSV()
{
	m_hFile = NULL;
	m_strFile = "";
}

CExportCSV::~CExportCSV()
{

}

BOOL CExportCSV::CreateFile(CString strFileName)
{
	BOOL bReturn = TRUE;

	m_hFile = ::CreateFile(strFileName,
						   GENERIC_WRITE,
						   FILE_SHARE_WRITE,
						   NULL,
						   CREATE_ALWAYS,
						   FILE_ATTRIBUTE_NORMAL,
						   NULL);

	if (m_hFile == INVALID_HANDLE_VALUE)
		bReturn = FALSE;

	return bReturn;
}

BOOL CExportCSV::CloseFile(CString strTitle)
{
	BOOL bReturn;

	WriteFile(strTitle);

	bReturn = CloseHandle(m_hFile);

	if (bReturn)
		m_hFile = NULL;

	return bReturn;
}

void CExportCSV::WriteValue(CString strValue)
{
	strValue.Trim();
	if (!strValue.IsEmpty())
	{
		strValue.Replace("\"", "\"\""); // sostituisco tutte le virgolette (") con le doppie virgolette ("") //
		strValue = "\"" + strValue + "\""; // metto le virgolette singole (") all'inizio e alla fine //
	}

	m_strFile += strValue;
}

void CExportCSV::WriteNewRow()
{
	m_strFile += "\r\n";
}

void CExportCSV::WriteNewColumn()
{
	m_strFile += ";"; // lo so che è CSV, però excel vuole il ; non la , cavoli //
}

BOOL CExportCSV::WriteFile(CString strTitle)
{
	DWORD dwBytesWritten;
	return ::WriteFile(m_hFile, m_strFile, m_strFile.GetLength(), &dwBytesWritten, NULL);
}
