#include "stdafx.h"
#include "Endox.h"
#include "ExportExcel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CExportExcel::CExportExcel()
{
	m_hFile = NULL;
}

CExportExcel::~CExportExcel()
{

}

BOOL CExportExcel::CreateFile(CString strFileName)
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

	if (bReturn)
		WriteBOF();

	return bReturn;
}

BOOL CExportExcel::CloseFile()
{
	BOOL bReturn;

	WriteEOF();

	bReturn = CloseHandle(m_hFile);

	if (bReturn)
		m_hFile = NULL;

	return bReturn;
}

void CExportExcel::WriteBOF()
{
	short nRecordCode, nLength, nVersion, nFileType;

	nRecordCode = 9;
	nLength     = 4;
	nVersion    = 2;
	nFileType   = 10;

	WriteData(&nRecordCode, 2);
	WriteData(&nLength,     2);
	WriteData(&nVersion,    2);
	WriteData(&nFileType,   2);
}

void CExportExcel::WriteEOF()
{
	short nRecordCode, nLength;

	nRecordCode = 10;
	nLength     = 0;

	WriteData(&nRecordCode, 2);
	WriteData(&nLength,     2);
}

BOOL CExportExcel::WriteData(void* szBuffer, int nBufferSize)
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

void CExportExcel::WriteValue(short nValue, short nRow, short nColumn, CellFont nCellFont, CellAlignment nAlignment, CellHiddenLocked nHiddenLocked)
{
	short nRecordCode, nLength;

	nRecordCode = 2;
	nLength     = 9;

	WriteData(&nRecordCode,   2);
	WriteData(&nLength,	      2);
	WriteData(&nRow,          2);
	WriteData(&nColumn,       2);	
	WriteData(&nHiddenLocked, 1);
	WriteData(&nCellFont,     1);
	WriteData(&nAlignment,    1);
	WriteData(&nValue,        2);
}

void CExportExcel::WriteValue(double nValue, short nRow, short nColumn, CellFont nCellFont, CellAlignment nAlignment, CellHiddenLocked nHiddenLocked)
{
	short nRecordCode, nLength;

	nRecordCode = 3;
	nLength     = 15;

	WriteData(&nRecordCode,   2);
	WriteData(&nLength,	      2);
	WriteData(&nRow,          2);
	WriteData(&nColumn,       2);	
	WriteData(&nHiddenLocked, 1);
	WriteData(&nCellFont,     1);
	WriteData(&nAlignment,    1);
	WriteData(&nValue,        8);
}

void CExportExcel::WriteValue(CString strValue, short nRow, short nColumn, CellFont nCellFont, CellAlignment nAlignment, CellHiddenLocked nHiddenLocked)
{
	if (strValue.GetLength() > 127) // a quanto pare è la dimensione massima di testo che ci sta in una cella excel 2.0 //
		strValue = (strValue.Left(124) + "...");

	char nTextLength = strValue.GetLength();

	short nRecordCode = 4;
	short nLength = 8 + nTextLength;

	WriteData(&nRecordCode,   2);
	WriteData(&nLength,	      2);
	WriteData(&nRow,          2);
	WriteData(&nColumn,       2);	
	WriteData(&nHiddenLocked, 1);
	WriteData(&nCellFont,     1);
	WriteData(&nAlignment,    1);
	WriteData(&nTextLength,   1);

	WriteData(strValue.GetBuffer(0), nTextLength);
}

void CExportExcel::SetMargin(double nMarginValue, MarginTypes nMarginTypes)
{
	short nRecordCode, nLength;

	nRecordCode = nMarginTypes;
	nLength     = 8;

	WriteData(&nRecordCode,   2);
	WriteData(&nLength,	      2);
	WriteData(&nMarginValue,  8);
}

void CExportExcel::SetColumnWidth(char nFirstColumn, char nLastColumn, short nWidthValue)
{
	short nRecordCode, nLength, nColumnWidth;
	char nCol1, nCol2;
	
	nRecordCode  = 36;
	nLength      = 4;
	nCol1        = nFirstColumn;
	nCol2        = nLastColumn;
	nColumnWidth = nWidthValue * 256;

	WriteData(&nRecordCode,  2);
	WriteData(&nLength,      2);
	WriteData(&nCol1,        1);
	WriteData(&nCol2,        1);
	WriteData(&nColumnWidth, 2);
}

void CExportExcel::SetRowsHeight(short nDim)
{
	short nRecordCode, nLength, nRowHeight;

	nRecordCode = 37;
	nLength     = 2;
	nRowHeight  = nDim * 20;

	WriteData(&nRecordCode, 2);
	WriteData(&nLength,     2);
	WriteData(&nRowHeight,  2);
}

void CExportExcel::SetFont(CString strFontName, short nFontHeight, FontFormatting nFontFormat)
{
	short nRecordCode, nLength, nFontHeightX20;
	char nFontNameLength, nFontAttributes1, nFontAttributes2;

	nFontNameLength = strFontName.GetLength();
	
	nRecordCode      = 49;
	nLength          = 5 + nFontNameLength;
	nFontHeightX20   = nFontHeight * 20;
	nFontAttributes1 = nFontFormat;
	nFontAttributes2 = 0;

	WriteData(&nRecordCode,      2);
	WriteData(&nLength,          2);
	WriteData(&nFontHeightX20,   2);
	WriteData(&nFontAttributes1, 1);
	WriteData(&nFontAttributes2, 1);
	WriteData(&nFontNameLength,  1);

	WriteData(strFontName.GetBuffer(0), nFontNameLength);
}

void CExportExcel::SetHeader(CString strHeader)
{
	short nRecordCode, nLength, nTextLength;

	nTextLength = strHeader.GetLength();

	nRecordCode = 20;
	nLength     = 1 + nTextLength;
	
	WriteData(&nRecordCode, 2);
	WriteData(&nLength    , 2);
	WriteData(&nTextLength, 1);

	WriteData(strHeader.GetBuffer(0), nTextLength);
}

void CExportExcel::SetFooter(CString strFooter)
{
	short nRecordCode, nLength, nTextLength;

	nTextLength = strFooter.GetLength();

	nRecordCode = 21;
	nLength     = 1 + nTextLength;

	WriteData(&nRecordCode, 2);
	WriteData(&nLength    , 2);
	WriteData(&nTextLength, 1);

	WriteData(strFooter.GetBuffer(0), nTextLength);
}

void CExportExcel::SetFilePassword(CString strPasswordText)
{

}

void CExportExcel::PrintGridLines(BOOL bEnabled)
{
	short nRecordCode, nLength, nPrintFlag;

	nRecordCode = 43;
	nLength     = 2;

	if (bEnabled)
		nPrintFlag = 1;
	else
		nPrintFlag = 0;

	WriteData(&nRecordCode, 2);
	WriteData(&nLength,     2);
	WriteData(&nPrintFlag,  2);
}

void CExportExcel::ProtectSpreadsheet(BOOL bEnabled)
{
	short nRecordCode, nLength, nProtect;

	nRecordCode = 18;
	nLength     = 2;

	if (bEnabled)
		nProtect = 1;
	else
		nProtect = 0;
	
	WriteData(&nRecordCode, 2);
	WriteData(&nLength,     2);
	WriteData(&nProtect,    2);
}
