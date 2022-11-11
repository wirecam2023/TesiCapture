#ifndef _EXPORTEXCEL_H_
	#define _EXPORTEXCEL_H_

enum CellAlignment
{
    xlsGeneralAlign = 0,
    xlsLeftAlign    = 1,
    xlsCentreAlign  = 2,
    xlsRightAlign   = 3,
    xlsFillCell     = 4,
    xlsLeftBorder   = 8,
    xlsRightBorder  = 16,
    xlsTopBorder    = 32,
    xlsBottomBorder = 64,
    xlsShaded       = 128
};

enum CellFont
{
    xlsFont0 = 0,
    xlsFont1 = 64,
    xlsFont2 = 128,
    xlsFont3 = 192
};

enum CellHiddenLocked
{
    xlsNormal = 0,
    xlsLocked = 64,
    xlsHidden = 128
};

enum MarginTypes
{
   xlsLeftMargin   = 38,
   xlsRightMargin  = 39,
   xlsTopMargin    = 40,
   xlsBottomMargin = 41
};

enum FontFormatting
{
   xlsNoFormat  = 0,
   xlsBold      = 1,
   xlsItalic    = 2,
   xlsUnderline = 4,
   xlsStrikeout = 8
};

class CExportExcel
{

public:

	CExportExcel();
	virtual ~CExportExcel();
	
	BOOL CreateFile(CString strFileName);
	BOOL CloseFile();

	void WriteValue(short nValue,     short nRow, short nColumn, CellFont nCellFont, CellAlignment nAlignment, CellHiddenLocked nHiddenLocked);
	void WriteValue(double nValue,    short nRow, short nColumn, CellFont nCellFont, CellAlignment nAlignment, CellHiddenLocked nHiddenLocked);
	void WriteValue(CString strValue, short nRow, short nColumn, CellFont nCellFont, CellAlignment nAlignment, CellHiddenLocked nHiddenLocked);
	
	void SetMargin(double nMarginValue, MarginTypes nMarginTypes);
	void SetColumnWidth(char nFirstColumn, char nLastColumn, short nWidthValue);
	void SetRowsHeight(short nDim);
	void SetFont(CString strFontName, short nFontHeight, FontFormatting nFontFormat);
	
	void SetHeader(CString strHeader);
	void SetFooter(CString strFooter);
	
	void SetFilePassword(CString strPasswordText);
	
	void PrintGridLines(BOOL bEnabled);
	void ProtectSpreadsheet(BOOL bEnabled);

private:	

	BOOL WriteData(void* szBuffer, int nBufferSize);
	HANDLE m_hFile;

	void WriteBOF();
	void WriteEOF();

};

#endif /* _EXPORTEXCEL_H_ */