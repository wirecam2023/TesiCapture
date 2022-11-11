#pragma once

/////////////////////////////////////////////////////////////////////////////
// COCX_FormulaOne wrapper class

class CFormulaOne : public CWnd
{
protected:
	DECLARE_DYNCREATE(CFormulaOne)
	
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x42BADC5, 0x5E58, 0x11CE, { 0xB6, 0x10, 0x52, 0x41, 0x53, 0x48, 0x0, 0x1 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// Attributi
public:
enum
{
    F1ColWidthUnitsCharacters = 0,
    F1ColWidthUnitsTwips = 1
}F1ColWidthUnitsConstants;
enum
{
    F1RowHeightAuto = -1
}F1RowHeightConstants;
enum
{
    F1Default = 0,
    F1Arrow = 1,
    F1Cross = 2,
    F1IBeam = 3,
    F1Icon = 4,
    F1Size = 5,
    F1SizeNESW = 6,
    F1SizeNS = 7,
    F1SizeNWSE = 8,
    F1SizeWE = 9,
    F1UpArrow = 10,
    F1Hourglass = 11,
    F1NoDrop = 12,
    F1Custom = 13
}F1MousePointerConstants;
enum
{
    F1Off = 0,
    F1On = 1,
    F1Auto = 2
}F1ShowOffOnAutoConstants;
enum
{
    F1TabsOff = 0,
    F1TabsBottom = 1,
    F1TabsTop = 2
}F1ShowTabsConstants;
enum
{
    F1ModeNormal = 0,
    F1ModeLine = 1,
    F1ModeRectangle = 2,
    F1ModeOval = 3,
    F1ModeArc = 4,
    F1ModeChart = 5,
    F1ModeField = 6,
    F1ModeButton = 7,
    F1ModePolygon = 8,
    F1ModeCheckBox = 9,
    F1ModeDropDown = 10
}F1ModeConstants;
enum
{
    F1PolyEditModeNormal = 0,
    F1PolyEditModePoints = 1
}F1PolyEditModeConstants;
enum
{
    F1ShiftHorizontal = 1,
    F1ShiftVertical = 2,
    F1ShiftRows = 3,
    F1ShiftCols = 4,
    F1FixupNormal = 0,
    F1FixupPrepend = 16,
    F1FixupAppend = 32
}F1ShiftTypeConstants;
enum
{
    F1ODBCErrorAbort = 0,
    F1ODBCErrorSkipRow = 1,
    F1ODBCErrorTryAgain = 2
}F1ODBCExecuteErrorConstants;
enum
{
    F1CDataChar = 0,
    F1CDataDouble = 1,
    F1CDataDate = 2,
    F1CDataTime = 3,
    F1CDataTimeStamp = 4,
    F1CDataBool = 5,
    F1CDataLong = 6
}F1CDataTypesConstants;
enum
{
    F1HAlignGeneral = 1,
    F1HAlignLeft = 2,
    F1HAlignCenter = 3,
    F1HAlignRight = 4,
    F1HAlignFill = 5,
    F1HAlignJustify = 6,
    F1HAlignCenterAcrossCells = 7
}F1HAlignConstants;
enum
{
    F1VAlignTop = 1,
    F1VAlignCenter = 2,
    F1VAlignBottom = 3
}F1VAlignConstants;
enum
{
    F1ClearDlg = 0,
    F1ClearAll = 1,
    F1ClearFormats = 2,
    F1ClearValues = 3
}F1ClearTypeConstants;
enum
{
    F1FileFormulaOne = 1,
    F1FileExcel4 = 2,
    F1FileTabbedText = 3,
    F1FileExcel5 = 4,
    F1FileFormulaOne3 = 5,
    F1FileTabbedTextValuesOnly = 6,
    F1FileHTML = 9,
    F1FileHTMLDataOnly = 10
}F1FileTypeConstants;
enum
{
    F1ObjLine = 1,
    F1ObjRectangle = 2,
    F1ObjOval = 3,
    F1ObjArc = 4,
    F1ObjChart = 5,
    F1ObjButton = 7,
    F1ObjPolygon = 8,
    F1ObjCheckBox = 9,
    F1ObjDropDown = 10,
    F1ObjPicture = 11
}F1ObjTypeConstants;
enum
{
    F1FindMatchCase = 1,
    F1FindEntireCells = 2,
    F1FindMatchBytes = 4,
    F1FindByRows = 0,
    F1FindByColumns = 8,
    F1FindInFormulas = 0,
    F1FindInValues = 16,
    F1FindReplaceAll = 32
}F1FindReplaceConstants;
enum
{
    F1ReplaceYes = 0,
    F1ReplaceNo = 1,
    F1ReplaceCancel = 2
}F1ReplaceBeforeConstants;
enum
{
    F1ErrorNone = 0,
    F1ErrorGeneral = 20001,
    F1ErrorBadArgument = 20002,
    F1ErrorNoMemory = 20003,
    F1ErrorBadFormula = 20004,
    F1ErrorBufTooShort = 20005,
    F1ErrorNotFound = 20006,
    F1ErrorBadRC = 20007,
    F1ErrorBadHSS = 20008,
    F1ErrorTooManyHSS = 20009,
    F1ErrorNoTable = 20010,
    F1ErrorUnableToOpenFile = 20011,
    F1ErrorInvalidFile = 20012,
    F1ErrorInsertShiftOffTable = 20013,
    F1ErrorOnlyOneRange = 20014,
    F1ErrorNothingToPaste = 20015,
    F1ErrorBadNumberFormat = 20016,
    F1ErrorTooManyFonts = 20017,
    F1ErrorTooManySelectedRanges = 20018,
    F1ErrorUnableToWriteFile = 20019,
    F1ErrorNoTransaction = 20020,
    F1ErrorNothingToPrint = 20021,
    F1ErrorPrintMarginsDontFit = 20022,
    F1ErrorCancel = 20023,
    F1ErrorUnableToInitializePrinter = 20024,
    F1ErrorStringTooLong = 20025,
    F1ErrorFormulaTooLong = 20026,
    F1ErrorUnableToOpenClipboard = 20027,
    F1ErrorPasteWouldOverflowSheet = 20028,
    F1ErrorLockedCellsCannotBeModified = 20029,
    F1ErrorLockedDocCannotBeModified = 20030,
    F1ErrorInvalidName = 20031,
    F1ErrorCannotDeleteNameInUse = 20032,
    F1ErrorUnableToFindName = 20033,
    F1ErrorNoWindow = 20034,
    F1ErrorSelection = 20035,
    F1ErrorTooManyObjects = 20036,
    F1ErrorInvalidObjectType = 20037,
    F1ErrorObjectNotFound = 20038,
    F1ErrorInvalidRequest = 20039,
    F1ErrorBadValidationRule = 20040,
    F1ErrorBadInputMask = 20041,
    F1ErrorValidationFailed = 20042,
    F1ErrorNoODBCConnection = 20043,
    F1ErrorUnableToLoadODBC = 20044,
    F1ErrorUnsupportedFeature = 20045,
    F1ErrorBadArray = 20046,
    F1InvalidODBCParameterBinding = 20047,
    F1InvalidStatementHandle = 20048,
    F1BadPrepareStatement = 20049,
    F1NotAvailableInSafeMode = 20050
}F1ErrorConstants;
enum
{
    F1ControlNoCell = 0,
    F1ControlCellValue = 1,
    F1ControlCellText = 2
}F1ControlCellConstants;


// Operazioni
public:

// _DVCF1

// Functions
//

	CString get_ColText(long nCol)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x110, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, nCol);
		return result;
	}
	void put_ColText(long nCol, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x110, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nCol, newValue);
	}
	CString get_DefinedName(LPCTSTR pName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x111, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, pName);
		return result;
	}
	void put_DefinedName(LPCTSTR pName, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x111, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, pName, newValue);
	}
	CString get_EntryRC(long nRow, long nCol)
	{
		CString result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x112, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, nRow, nCol);
		return result;
	}
	void put_EntryRC(long nRow, long nCol, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BSTR ;
		InvokeHelper(0x112, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nRow, nCol, newValue);
	}
	CString get_FormattedTextRC(long nRow, long nCol)
	{
		CString result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x113, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, nRow, nCol);
		return result;
	}
	void put_FormattedTextRC(long nRow, long nCol, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BSTR ;
		InvokeHelper(0x113, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nRow, nCol, newValue);
	}
	CString get_FormulaRC(long nRow, long nCol)
	{
		CString result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x114, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, nRow, nCol);
		return result;
	}
	void put_FormulaRC(long nRow, long nCol, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BSTR ;
		InvokeHelper(0x114, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nRow, nCol, newValue);
	}
	long get_LastColForRow(long nRow)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x115, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, nRow);
		return result;
	}
	void put_LastColForRow(long nRow, long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x115, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nRow, newValue);
	}
	BOOL get_LogicalRC(long nRow, long nCol)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x116, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, nRow, nCol);
		return result;
	}
	void put_LogicalRC(long nRow, long nCol, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0x116, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nRow, nCol, newValue);
	}
	double get_NumberRC(long nRow, long nCol)
	{
		double result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x117, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, parms, nRow, nCol);
		return result;
	}
	void put_NumberRC(long nRow, long nCol, double newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_R8 ;
		InvokeHelper(0x117, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nRow, nCol, newValue);
	}
	CString get_RowText(long nRow)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x118, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, nRow);
		return result;
	}
	void put_RowText(long nRow, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x118, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nRow, newValue);
	}
	CString get_TextRC(long nRow, long nCol)
	{
		CString result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x119, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, nRow, nCol);
		return result;
	}
	void put_TextRC(long nRow, long nCol, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BSTR ;
		InvokeHelper(0x119, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nRow, nCol, newValue);
	}
	short get_TypeRC(long nRow, long nCol)
	{
		short result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x11a, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, nRow, nCol);
		return result;
	}
	void put_TypeRC(long nRow, long nCol, short newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I2 ;
		InvokeHelper(0x11a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nRow, nCol, newValue);
	}
	void EditPasteValues()
	{
		InvokeHelper(0x71, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void GetAlignment(short * pHorizontal, BOOL * pWordWrap, short * pVertical, short * pOrientation)
	{
		static BYTE parms[] = VTS_PI2 VTS_PBOOL VTS_PI2 VTS_PI2 ;
		InvokeHelper(0x72, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pHorizontal, pWordWrap, pVertical, pOrientation);
	}
	void GetBorder(short * pLeft, short * pRight, short * pTop, short * pBottom, short * pShade, unsigned long * pcrLeft, unsigned long * pcrRight, unsigned long * pcrTop, unsigned long * pcrBottom)
	{
		static BYTE parms[] = VTS_PI2 VTS_PI2 VTS_PI2 VTS_PI2 VTS_PI2 VTS_PUI4 VTS_PUI4 VTS_PUI4 VTS_PUI4 ;
		InvokeHelper(0x73, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pLeft, pRight, pTop, pBottom, pShade, pcrLeft, pcrRight, pcrTop, pcrBottom);
	}
	void GetFont(BSTR * pName, short * pSize, BOOL * pBold, BOOL * pItalic, BOOL * pUnderline, BOOL * pStrikeout, unsigned long * pcrColor, BOOL * pOutline, BOOL * pShadow)
	{
		static BYTE parms[] = VTS_PBSTR VTS_PI2 VTS_PBOOL VTS_PBOOL VTS_PBOOL VTS_PBOOL VTS_PUI4 VTS_PBOOL VTS_PBOOL ;
		InvokeHelper(0x74, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pName, pSize, pBold, pItalic, pUnderline, pStrikeout, pcrColor, pOutline, pShadow);
	}
	void GetLineStyle(short * pStyle, unsigned long * pcrColor, short * pWeight)
	{
		static BYTE parms[] = VTS_PI2 VTS_PUI4 VTS_PI2 ;
		InvokeHelper(0x75, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pStyle, pcrColor, pWeight);
	}
	void GetPattern(short * pPattern, unsigned long * pcrFG, unsigned long * pcrBG)
	{
		static BYTE parms[] = VTS_PI2 VTS_PUI4 VTS_PUI4 ;
		InvokeHelper(0x76, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pPattern, pcrFG, pcrBG);
	}
	void GetProtection(BOOL * pLocked, BOOL * pHidden)
	{
		static BYTE parms[] = VTS_PBOOL VTS_PBOOL ;
		InvokeHelper(0x77, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pLocked, pHidden);
	}
	void GetTabbedText(long nR1, long nC1, long nR2, long nC2, BOOL bValuesOnly, long * phText)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BOOL VTS_PI4 ;
		InvokeHelper(0x78, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nR1, nC1, nR2, nC2, bValuesOnly, phText);
	}
	void SetTabbedText(long nStartRow, long nStartCol, long * pRows, long * pCols, BOOL bValuesOnly, LPCTSTR pText)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PI4 VTS_PI4 VTS_BOOL VTS_BSTR ;
		InvokeHelper(0x79, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nStartRow, nStartCol, pRows, pCols, bValuesOnly, pText);
	}
	void AddColPageBreak(long nCol)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nCol);
	}
	void AddPageBreak()
	{
		InvokeHelper(0x7b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void AddRowPageBreak(long nRow)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nRow);
	}
	void AddSelection(long nR1, long nC1, long nR2, long nC2)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x7d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nR1, nC1, nR2, nC2);
	}
	void Attach(LPCTSTR pTitle)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x7e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pTitle);
	}
	void AttachToSS(long hSrcSS)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, hSrcSS);
	}
	void CalculationDlg()
	{
		InvokeHelper(0x80, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void CancelEdit()
	{
		InvokeHelper(0x81, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void CheckRecalc()
	{
		InvokeHelper(0x82, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ClearClipboard()
	{
		InvokeHelper(0x83, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ClearRange(long nR1, long nC1, long nR2, long nC2, short ClearType)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I2 ;
		InvokeHelper(0x84, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nR1, nC1, nR2, nC2, ClearType);
	}
	void ColorPaletteDlg()
	{
		InvokeHelper(0x85, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ColWidthDlg()
	{
		InvokeHelper(0x86, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void CopyAll(long hSrcSS)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x87, DISPATCH_METHOD, VT_EMPTY, NULL, parms, hSrcSS);
	}
	void CopyRange(long nDstR1, long nDstC1, long nDstR2, long nDstC2, long hSrcSS, long nSrcR1, long nSrcC1, long nSrcR2, long nSrcC2)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x88, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nDstR1, nDstC1, nDstR2, nDstC2, hSrcSS, nSrcR1, nSrcC1, nSrcR2, nSrcC2);
	}
	void DefinedNameDlg()
	{
		InvokeHelper(0x89, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void DeleteDefinedName(LPCTSTR pName)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x8a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pName);
	}
	void DeleteRange(long nR1, long nC1, long nR2, long nC2, short ShiftType)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I2 ;
		InvokeHelper(0x8b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nR1, nC1, nR2, nC2, ShiftType);
	}
	void Draw(long hDC, long x, long y, long cx, long cy, long nRow, long nCol, long * pRows, long * pCols, long nFixedRow, long nFixedCol, long nFixedRows, long nFixedCols)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_PI4 VTS_PI4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x8c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, hDC, x, y, cx, cy, nRow, nCol, pRows, pCols, nFixedRow, nFixedCol, nFixedRows, nFixedCols);
	}
	void EditClear(short ClearType)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x8d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ClearType);
	}
	void EditCopy()
	{
		InvokeHelper(0x8e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void EditCopyDown()
	{
		InvokeHelper(0x8f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void EditCopyRight()
	{
		InvokeHelper(0x90, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void EditCut()
	{
		InvokeHelper(0x91, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void EditDelete(short ShiftType)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x92, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ShiftType);
	}
	void EditInsert(short InsertType)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x93, DISPATCH_METHOD, VT_EMPTY, NULL, parms, InsertType);
	}
	void EditPaste()
	{
		InvokeHelper(0x94, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void EndEdit()
	{
		InvokeHelper(0x95, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void FilePageSetupDlg()
	{
		InvokeHelper(0x96, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void FilePrint(BOOL bShowPrintDlg)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x97, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bShowPrintDlg);
	}
	void FilePrintSetupDlg()
	{
		InvokeHelper(0x98, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void FormatAlignmentDlg()
	{
		InvokeHelper(0x99, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void FormatBorderDlg()
	{
		InvokeHelper(0x9a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void FormatCurrency0()
	{
		InvokeHelper(0x9b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void FormatCurrency2()
	{
		InvokeHelper(0x9c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void FormatDefaultFontDlg()
	{
		InvokeHelper(0x9d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void FormatFixed()
	{
		InvokeHelper(0x9e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void FormatFixed2()
	{
		InvokeHelper(0x9f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void FormatFontDlg()
	{
		InvokeHelper(0xa0, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void FormatFraction()
	{
		InvokeHelper(0xa1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void FormatGeneral()
	{
		InvokeHelper(0xa2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void FormatHmmampm()
	{
		InvokeHelper(0xa3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void FormatMdyy()
	{
		InvokeHelper(0xa4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void FormatNumberDlg()
	{
		InvokeHelper(0xa5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void FormatPatternDlg()
	{
		InvokeHelper(0xa6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void FormatPercent()
	{
		InvokeHelper(0xa7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void FormatScientific()
	{
		InvokeHelper(0xa8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void GetActiveCell(long * pRow, long * pCol)
	{
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0xa9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pRow, pCol);
	}
	short get_ColWidth(long nCol)
	{
		short result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x11b, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, nCol);
		return result;
	}
	void put_ColWidth(long nCol, short newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I2 ;
		InvokeHelper(0x11b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nCol, newValue);
	}
	short get_RowHeight(long nRow)
	{
		short result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x11c, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, nRow);
		return result;
	}
	void put_RowHeight(long nRow, short newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I2 ;
		InvokeHelper(0x11c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nRow, newValue);
	}
	void GetDefaultFont(BSTR * pBuf, short * pSize)
	{
		static BYTE parms[] = VTS_PBSTR VTS_PI2 ;
		InvokeHelper(0xaa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pBuf, pSize);
	}
	void GetHdrSelection(BOOL * pTopLeftHdr, BOOL * pRowHdr, BOOL * pColHdr)
	{
		static BYTE parms[] = VTS_PBOOL VTS_PBOOL VTS_PBOOL ;
		InvokeHelper(0xab, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pTopLeftHdr, pRowHdr, pColHdr);
	}
	void GetIteration(BOOL * pIteration, short * pMaxIterations, double * pMaxChange)
	{
		static BYTE parms[] = VTS_PBOOL VTS_PI2 VTS_PR8 ;
		InvokeHelper(0xac, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pIteration, pMaxIterations, pMaxChange);
	}
	void GetPrintScale(short * pScale, BOOL * pFitToPage, long * pVPages, long * pHPages)
	{
		static BYTE parms[] = VTS_PI2 VTS_PBOOL VTS_PI4 VTS_PI4 ;
		InvokeHelper(0xad, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pScale, pFitToPage, pVPages, pHPages);
	}
	void GetSelection(short nSelection, long * pR1, long * pC1, long * pR2, long * pC2)
	{
		static BYTE parms[] = VTS_I2 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 ;
		InvokeHelper(0xae, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nSelection, pR1, pC1, pR2, pC2);
	}
	void GotoDlg()
	{
		InvokeHelper(0xaf, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void HeapMin()
	{
		InvokeHelper(0xb0, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void InitTable()
	{
		InvokeHelper(0xb1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void InsertRange(long nR1, long nC1, long nR2, long nC2, short InsertType)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I2 ;
		InvokeHelper(0xb2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nR1, nC1, nR2, nC2, InsertType);
	}
	void LineStyleDlg()
	{
		InvokeHelper(0xb3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void MoveRange(long nR1, long nC1, long nR2, long nC2, long nRowOffset, long nColOffset)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0xb4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nR1, nC1, nR2, nC2, nRowOffset, nColOffset);
	}
	void ObjAddItem(long ID, LPCTSTR pItem)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0xb5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ID, pItem);
	}
	void ObjAddSelection(long ID)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xb6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ID);
	}
	void ObjBringToFront()
	{
		InvokeHelper(0xb7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ObjDeleteItem(long ID, short nItem)
	{
		static BYTE parms[] = VTS_I4 VTS_I2 ;
		InvokeHelper(0xb8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ID, nItem);
	}
	void ObjGetCell(long ID, short * pControlCellType, long * pRow, long * pCol)
	{
		static BYTE parms[] = VTS_I4 VTS_PI2 VTS_PI4 VTS_PI4 ;
		InvokeHelper(0xb9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ID, pControlCellType, pRow, pCol);
	}
	void ObjGetPos(long ID, float * pX1, float * pY1, float * pX2, float * pY2)
	{
		static BYTE parms[] = VTS_I4 VTS_PR4 VTS_PR4 VTS_PR4 VTS_PR4 ;
		InvokeHelper(0xba, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ID, pX1, pY1, pX2, pY2);
	}
	void ObjGetSelection(short nSelection, long * pID)
	{
		static BYTE parms[] = VTS_I2 VTS_PI4 ;
		InvokeHelper(0xbb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nSelection, pID);
	}
	void ObjInsertItem(long ID, short nItem, LPCTSTR pItem)
	{
		static BYTE parms[] = VTS_I4 VTS_I2 VTS_BSTR ;
		InvokeHelper(0xbc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ID, nItem, pItem);
	}
	void ObjNameDlg()
	{
		InvokeHelper(0xbd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ObjNew(short ObjType, float nX1, float nY1, float nX2, float nY2, long * pID)
	{
		static BYTE parms[] = VTS_I2 VTS_R4 VTS_R4 VTS_R4 VTS_R4 VTS_PI4 ;
		InvokeHelper(0xbe, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ObjType, nX1, nY1, nX2, nY2, pID);
	}
	void ObjNewPicture(float nX1, float nY1, float nX2, float nY2, long * pID, long hMF, long nMapMode, long nWndExtentX, long nWndExtentY)
	{
		static BYTE parms[] = VTS_R4 VTS_R4 VTS_R4 VTS_R4 VTS_PI4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0xbf, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nX1, nY1, nX2, nY2, pID, hMF, nMapMode, nWndExtentX, nWndExtentY);
	}
	void ObjOptionsDlg()
	{
		InvokeHelper(0xc0, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ObjPosToTwips(float nX1, float nY1, float nX2, float nY2, long * pX, long * pY, long * pCX, long * pCY, short * pShown)
	{
		static BYTE parms[] = VTS_R4 VTS_R4 VTS_R4 VTS_R4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI2 ;
		InvokeHelper(0xc1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nX1, nY1, nX2, nY2, pX, pY, pCX, pCY, pShown);
	}
	void ObjSendToBack()
	{
		InvokeHelper(0xc2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ObjSetCell(long ID, short ControlCellType, long nRow, long nCol)
	{
		static BYTE parms[] = VTS_I4 VTS_I2 VTS_I4 VTS_I4 ;
		InvokeHelper(0xc3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ID, ControlCellType, nRow, nCol);
	}
	void ObjSetPicture(long ID, long hMF, short nMapMode, long nWndExtentX, long nWndExtentY)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I2 VTS_I4 VTS_I4 ;
		InvokeHelper(0xc4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ID, hMF, nMapMode, nWndExtentX, nWndExtentY);
	}
	void ObjSetPos(long ID, float nX1, float nY1, float nX2, float nY2)
	{
		static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
		InvokeHelper(0xc5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ID, nX1, nY1, nX2, nY2);
	}
	void ObjSetSelection(long ID)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xc6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ID);
	}
	void OpenFileDlg(LPCTSTR pTitle, long hWndParent, BSTR * pBuf)
	{
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_PBSTR ;
		InvokeHelper(0xc7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pTitle, hWndParent, pBuf);
	}
	void ProtectionDlg()
	{
		InvokeHelper(0xc8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void RangeToTwips(long nRow1, long nCol1, long nRow2, long nCol2, long * pX, long * pY, long * pCX, long * pCY, short * pShown)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI2 ;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nRow1, nCol1, nRow2, nCol2, pX, pY, pCX, pCY, pShown);
	}
	void Read(LPCTSTR pPathName, short * pFileType)
	{
		static BYTE parms[] = VTS_BSTR VTS_PI2 ;
		InvokeHelper(0xca, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pPathName, pFileType);
	}
	void ReadFromBlob(long hBlob, short nReservedBytes)
	{
		static BYTE parms[] = VTS_I4 VTS_I2 ;
		InvokeHelper(0xcb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, hBlob, nReservedBytes);
	}
	void Recalc()
	{
		InvokeHelper(0xcc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void RemoveColPageBreak(long nCol)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xcd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nCol);
	}
	void RemovePageBreak()
	{
		InvokeHelper(0xce, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void RemoveRowPageBreak(long nRow)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xcf, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nRow);
	}
	void RowHeightDlg()
	{
		InvokeHelper(0xd0, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SaveFileDlg(LPCTSTR pTitle, BSTR * pBuf, short * pFileType)
	{
		static BYTE parms[] = VTS_BSTR VTS_PBSTR VTS_PI2 ;
		InvokeHelper(0xd1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pTitle, pBuf, pFileType);
	}
	void SaveWindowInfo()
	{
		InvokeHelper(0xd2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetActiveCell(long nRow, long nCol)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0xd3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nRow, nCol);
	}
	void SetAlignment(short HAlign, BOOL bWordWrap, short VAlign, short nOrientation)
	{
		static BYTE parms[] = VTS_I2 VTS_BOOL VTS_I2 VTS_I2 ;
		InvokeHelper(0xd4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, HAlign, bWordWrap, VAlign, nOrientation);
	}
	void SetBorder(short nOutline, short nLeft, short nRight, short nTop, short nBottom, short nShade, unsigned long crOutline, unsigned long crLeft, unsigned long crRight, unsigned long crTop, unsigned long crBottom)
	{
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_UI4 VTS_UI4 VTS_UI4 VTS_UI4 VTS_UI4 ;
		InvokeHelper(0xd5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nOutline, nLeft, nRight, nTop, nBottom, nShade, crOutline, crLeft, crRight, crTop, crBottom);
	}
	void SetColWidth(long nC1, long nC2, short nWidth, BOOL bDefColWidth)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I2 VTS_BOOL ;
		InvokeHelper(0xd6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nC1, nC2, nWidth, bDefColWidth);
	}
	void SetColWidthAuto(long nR1, long nC1, long nR2, long nC2, BOOL bSetDefaults)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0xd7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nR1, nC1, nR2, nC2, bSetDefaults);
	}
	void SetDefaultFont(LPCTSTR pName, short nSize)
	{
		static BYTE parms[] = VTS_BSTR VTS_I2 ;
		InvokeHelper(0xd8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pName, nSize);
	}
	void SetFont(LPCTSTR pName, short nSize, BOOL bBold, BOOL bItalic, BOOL bUnderline, BOOL bStrikeout, unsigned long crColor, BOOL bOutline, BOOL bShadow)
	{
		static BYTE parms[] = VTS_BSTR VTS_I2 VTS_BOOL VTS_BOOL VTS_BOOL VTS_BOOL VTS_UI4 VTS_BOOL VTS_BOOL ;
		InvokeHelper(0xd9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pName, nSize, bBold, bItalic, bUnderline, bStrikeout, crColor, bOutline, bShadow);
	}
	void SetHdrSelection(BOOL bTopLeftHdr, BOOL bRowHdr, BOOL bColHdr)
	{
		static BYTE parms[] = VTS_BOOL VTS_BOOL VTS_BOOL ;
		InvokeHelper(0xda, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bTopLeftHdr, bRowHdr, bColHdr);
	}
	void SetIteration(BOOL bIteration, short nMaxIterations, double nMaxChange)
	{
		static BYTE parms[] = VTS_BOOL VTS_I2 VTS_R8 ;
		InvokeHelper(0xdb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bIteration, nMaxIterations, nMaxChange);
	}
	void SetLineStyle(short nStyle, unsigned long crColor, short nWeight)
	{
		static BYTE parms[] = VTS_I2 VTS_UI4 VTS_I2 ;
		InvokeHelper(0xdc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nStyle, crColor, nWeight);
	}
	void SetPattern(short nPattern, unsigned long crFG, unsigned long crBG)
	{
		static BYTE parms[] = VTS_I2 VTS_UI4 VTS_UI4 ;
		InvokeHelper(0xdd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nPattern, crFG, crBG);
	}
	void SetPrintAreaFromSelection()
	{
		InvokeHelper(0xde, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetPrintScale(short nScale, BOOL bFitToPage, short nVPages, short nHPages)
	{
		static BYTE parms[] = VTS_I2 VTS_BOOL VTS_I2 VTS_I2 ;
		InvokeHelper(0xdf, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nScale, bFitToPage, nVPages, nHPages);
	}
	void SetPrintTitlesFromSelection()
	{
		InvokeHelper(0xe0, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetProtection(BOOL bLocked, BOOL bHidden)
	{
		static BYTE parms[] = VTS_BOOL VTS_BOOL ;
		InvokeHelper(0xe1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bLocked, bHidden);
	}
	void SetRowHeight(long nR1, long nR2, short nHeight, BOOL bDefRowHeight)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I2 VTS_BOOL ;
		InvokeHelper(0xe2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nR1, nR2, nHeight, bDefRowHeight);
	}
	void SetRowHeightAuto(long nR1, long nC1, long nR2, long nC2, BOOL bSetDefaults)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0xe3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nR1, nC1, nR2, nC2, bSetDefaults);
	}
	void SetSelection(long nR1, long nC1, long nR2, long nC2)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0xe4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nR1, nC1, nR2, nC2);
	}
	void ShowActiveCell()
	{
		InvokeHelper(0xe5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Sort3(long nR1, long nC1, long nR2, long nC2, BOOL bSortByRows, long nKey1, long nKey2, long nKey3)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BOOL VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0xe6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nR1, nC1, nR2, nC2, bSortByRows, nKey1, nKey2, nKey3);
	}
	void SortDlg()
	{
		InvokeHelper(0xe7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void StartEdit(BOOL bClear, BOOL bInCellEditFocus, BOOL bArrowsExitEditMode)
	{
		static BYTE parms[] = VTS_BOOL VTS_BOOL VTS_BOOL ;
		InvokeHelper(0xe8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bClear, bInCellEditFocus, bArrowsExitEditMode);
	}
	void SwapTables(long hSS2)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xe9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, hSS2);
	}
	void TransactCommit()
	{
		InvokeHelper(0xea, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void TransactRollback()
	{
		InvokeHelper(0xeb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void TransactStart()
	{
		InvokeHelper(0xec, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void TwipsToRC(long x, long y, long * pRow, long * pCol)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PI4 VTS_PI4 ;
		InvokeHelper(0xed, DISPATCH_METHOD, VT_EMPTY, NULL, parms, x, y, pRow, pCol);
	}
	void SSUpdate()
	{
		InvokeHelper(0xee, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	short SSVersion()
	{
		short result;
		InvokeHelper(0xef, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	void Write(LPCTSTR pPathName, short FileType)
	{
		static BYTE parms[] = VTS_BSTR VTS_I2 ;
		InvokeHelper(0xf0, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pPathName, FileType);
	}
	void WriteToBlob(long * phBlob, short nReservedBytes)
	{
		static BYTE parms[] = VTS_PI4 VTS_I2 ;
		InvokeHelper(0xf1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, phBlob, nReservedBytes);
	}
	void SetRowHidden(long nRow1, long nRow2, BOOL bHidden)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0xf2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nRow1, nRow2, bHidden);
	}
	void SetColHidden(long nCol1, long nCol2, BOOL bHidden)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0xf3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nCol1, nCol2, bHidden);
	}
	void SetColWidthTwips(long nCol1, long nCol2, long nWidth, BOOL bDefColWidth)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0xf4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nCol1, nCol2, nWidth, bDefColWidth);
	}
	CString get_DefinedNameByIndex(long nName)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x11d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, nName);
		return result;
	}
	void put_DefinedNameByIndex(long nName, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x11d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nName, newValue);
	}
	CString get_SheetName(long nSheet)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x11e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, nSheet);
		return result;
	}
	void put_SheetName(long nSheet, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x11e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nSheet, newValue);
	}
	unsigned long get_PaletteEntry(long nEntry)
	{
		unsigned long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x11f, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, parms, nEntry);
		return result;
	}
	void put_PaletteEntry(long nEntry, unsigned long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_UI4 ;
		InvokeHelper(0x11f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nEntry, newValue);
	}
	void EditInsertSheets()
	{
		InvokeHelper(0xf5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void EditDeleteSheets()
	{
		InvokeHelper(0xf6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void InsertSheets(long nSheet, long nSheets)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0xf7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nSheet, nSheets);
	}
	void DeleteSheets(long nSheet, long nSheets)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0xf8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nSheet, nSheets);
	}
	void Refresh()
	{
		InvokeHelper(DISPID_REFRESH, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	short get_ColWidthTwips(long Col)
	{
		short result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x120, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, Col);
		return result;
	}
	void put_ColWidthTwips(long Col, short newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I2 ;
		InvokeHelper(0x120, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, Col, newValue);
	}
	long NextColPageBreak(long Col)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xf9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Col);
		return result;
	}
	long NextRowPageBreak(long Row)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xfa, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Row);
		return result;
	}
	long ObjFirstID()
	{
		long result;
		InvokeHelper(0xfb, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long ObjNextID(long ID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xfc, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ID);
		return result;
	}
	short ObjGetItemCount(long ID)
	{
		short result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xfd, DISPATCH_METHOD, VT_I2, (void*)&result, parms, ID);
		return result;
	}
	short ObjGetType(long ID)
	{
		short result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xfe, DISPATCH_METHOD, VT_I2, (void*)&result, parms, ID);
		return result;
	}
	short ObjGetSelectionCount()
	{
		short result;
		InvokeHelper(0xff, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	CString FormatRCNr(long Row, long Col, BOOL DoAbsolute)
	{
		CString result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0x100, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Row, Col, DoAbsolute);
		return result;
	}
	long SS()
	{
		long result;
		InvokeHelper(0x101, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString ErrorNumberToText(long SSError)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x102, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, SSError);
		return result;
	}
	CString get_ObjItem(long ID, short Item)
	{
		CString result;
		static BYTE parms[] = VTS_I4 VTS_I2 ;
		InvokeHelper(0x121, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, ID, Item);
		return result;
	}
	void put_ObjItem(long ID, short Item, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I2 VTS_BSTR ;
		InvokeHelper(0x121, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, ID, Item, newValue);
	}
	CString get_ObjItems(long ID)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x122, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, ID);
		return result;
	}
	void put_ObjItems(long ID, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x122, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, ID, newValue);
	}
	CString get_ObjName(long ID)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x123, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, ID);
		return result;
	}
	void put_ObjName(long ID, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x123, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, ID, newValue);
	}
	CString get_ObjText(long ID)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x124, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, ID);
		return result;
	}
	void put_ObjText(long ID, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x124, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, ID, newValue);
	}
	short get_ObjValue(long ID)
	{
		short result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x125, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, ID);
		return result;
	}
	void put_ObjValue(long ID, short newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I2 ;
		InvokeHelper(0x125, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, ID, newValue);
	}
	BOOL get_ObjVisible(long ID)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x126, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, ID);
		return result;
	}
	void put_ObjVisible(long ID, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x126, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, ID, newValue);
	}
	long ObjNameToID(LPCTSTR Name)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x103, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Name);
		return result;
	}
	long DefinedNameCount()
	{
		long result;
		InvokeHelper(0x104, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString get_AutoFillItems(short Index)
	{
		CString result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x127, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, Index);
		return result;
	}
	void put_AutoFillItems(short Index, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_BSTR ;
		InvokeHelper(0x127, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, Index, newValue);
	}
	void ValidationRuleDlg()
	{
		InvokeHelper(0x105, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetValidationRule(LPCTSTR Rule, LPCTSTR Text)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x106, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Rule, Text);
	}
	void GetValidationRule(BSTR * Rule, BSTR * Text)
	{
		static BYTE parms[] = VTS_PBSTR VTS_PBSTR ;
		InvokeHelper(0x107, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Rule, Text);
	}
	short AutoFillItemsCount()
	{
		short result;
		InvokeHelper(0x108, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	void CopyRangeEx(long nDstSheet, long nDstR1, long nDstC1, long nDstR2, long nDstC2, long hSrcSS, long nSrcSheet, long nSrcR1, long nSrcC1, long nSrcR2, long nSrcC2)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x109, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nDstSheet, nDstR1, nDstC1, nDstR2, nDstC2, hSrcSS, nSrcSheet, nSrcR1, nSrcC1, nSrcR2, nSrcC2);
	}
	void Sort(long nR1, long nC1, long nR2, long nC2, BOOL bSortByRows, VARIANT Keys)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BOOL VTS_VARIANT ;
		InvokeHelper(0x10a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nR1, nC1, nR2, nC2, bSortByRows, &Keys);
	}
	BOOL get_ColHidden(long nCol)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x128, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, nCol);
		return result;
	}
	void put_ColHidden(long nCol, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x128, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nCol, newValue);
	}
	BOOL get_RowHidden(long nRow)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x129, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, nRow);
		return result;
	}
	void put_RowHidden(long nRow, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x129, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nRow, newValue);
	}
	void DeleteAutoFillItems(short nIndex)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x10b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nIndex);
	}
	void ODBCConnect(BSTR * pConnect, BOOL bShowErrors, short * pRetCode)
	{
		static BYTE parms[] = VTS_PBSTR VTS_BOOL VTS_PI2 ;
		InvokeHelper(0x10c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pConnect, bShowErrors, pRetCode);
	}
	void ODBCDisconnect()
	{
		InvokeHelper(0x10d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ODBCQuery(BSTR * pQuery, long nRow, long nCol, BOOL bForceShowDlg, BOOL * pSetColNames, BOOL * pSetColFormats, BOOL * pSetColWidths, BOOL * pSetMaxRC, short * pRetCode)
	{
		static BYTE parms[] = VTS_PBSTR VTS_I4 VTS_I4 VTS_BOOL VTS_PBOOL VTS_PBOOL VTS_PBOOL VTS_PBOOL VTS_PI2 ;
		InvokeHelper(0x10e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pQuery, nRow, nCol, bForceShowDlg, pSetColNames, pSetColFormats, pSetColWidths, pSetMaxRC, pRetCode);
	}
	BOOL get_SheetSelected(long nSheet)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x12a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, nSheet);
		return result;
	}
	void put_SheetSelected(long nSheet, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x12a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nSheet, newValue);
	}
	void LaunchDesigner()
	{
		InvokeHelper(0x10f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void PrintPreviewDC(long hDC, short nPage, short * pPages)
	{
		static BYTE parms[] = VTS_I4 VTS_I2 VTS_PI2 ;
		InvokeHelper(0x521, DISPATCH_METHOD, VT_EMPTY, NULL, parms, hDC, nPage, pPages);
	}
	void PrintPreview(long hWnd, long x, long y, long cx, long cy, short nPage, short * pPages)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I2 VTS_PI2 ;
		InvokeHelper(0x522, DISPATCH_METHOD, VT_EMPTY, NULL, parms, hWnd, x, y, cx, cy, nPage, pPages);
	}
	CString get_EntrySRC(long nSheet, long nRow, long nCol)
	{
		CString result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x523, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, nSheet, nRow, nCol);
		return result;
	}
	void put_EntrySRC(long nSheet, long nRow, long nCol, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_BSTR ;
		InvokeHelper(0x523, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nSheet, nRow, nCol, newValue);
	}
	CString get_FormattedTextSRC(long nSheet, long nRow, long nCol)
	{
		CString result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x524, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, nSheet, nRow, nCol);
		return result;
	}
	void put_FormattedTextSRC(long nSheet, long nRow, long nCol, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_BSTR ;
		InvokeHelper(0x524, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nSheet, nRow, nCol, newValue);
	}
	CString get_FormulaSRC(long nSheet, long nRow, long nCol)
	{
		CString result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x525, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, nSheet, nRow, nCol);
		return result;
	}
	void put_FormulaSRC(long nSheet, long nRow, long nCol, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_BSTR ;
		InvokeHelper(0x525, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nSheet, nRow, nCol, newValue);
	}
	BOOL get_LogicalSRC(long nSheet, long nRow, long nCol)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x526, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, nSheet, nRow, nCol);
		return result;
	}
	void put_LogicalSRC(long nSheet, long nRow, long nCol, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0x526, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nSheet, nRow, nCol, newValue);
	}
	double get_NumberSRC(long nSheet, long nRow, long nCol)
	{
		double result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x527, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, parms, nSheet, nRow, nCol);
		return result;
	}
	void put_NumberSRC(long nSheet, long nRow, long nCol, double newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_R8 ;
		InvokeHelper(0x527, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nSheet, nRow, nCol, newValue);
	}
	CString get_TextSRC(long nSheet, long nRow, long nCol)
	{
		CString result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x528, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, nSheet, nRow, nCol);
		return result;
	}
	void put_TextSRC(long nSheet, long nRow, long nCol, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_BSTR ;
		InvokeHelper(0x528, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nSheet, nRow, nCol, newValue);
	}
	short get_TypeSRC(long nSheet, long nRow, long nCol)
	{
		short result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x529, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, nSheet, nRow, nCol);
		return result;
	}
	void put_TypeSRC(long nSheet, long nRow, long nCol, short newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I2 ;
		InvokeHelper(0x529, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nSheet, nRow, nCol, newValue);
	}
	void WriteRange(long nSheet, long nRow1, long nCol1, long nRow2, long nCol2, LPCTSTR pPathName, short FileType)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_I2 ;
		InvokeHelper(0x52a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nSheet, nRow1, nCol1, nRow2, nCol2, pPathName, FileType);
	}
	void InsertHTML(long nSheet, long nRow1, long nCol1, long nRow2, long nCol2, LPCTSTR pPathName, BOOL bDataOnly, LPCTSTR pAnchorName)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_BOOL VTS_BSTR ;
		InvokeHelper(0x52b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nSheet, nRow1, nCol1, nRow2, nCol2, pPathName, bDataOnly, pAnchorName);
	}
	void FilePrintEx(BOOL bShowPrintDlg, BOOL bPrintWorkbook)
	{
		static BYTE parms[] = VTS_BOOL VTS_BOOL ;
		InvokeHelper(0x52c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bShowPrintDlg, bPrintWorkbook);
	}
	void FilePrintPreview()
	{
		InvokeHelper(0x52d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	CString get_FormulaLocalRC(long nRow, long nCol)
	{
		CString result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x52f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, nRow, nCol);
		return result;
	}
	void put_FormulaLocalRC(long nRow, long nCol, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BSTR ;
		InvokeHelper(0x52f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nRow, nCol, newValue);
	}
	CString get_FormulaLocalSRC(long nSheet, long nRow, long nCol)
	{
		CString result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x530, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, nSheet, nRow, nCol);
		return result;
	}
	void put_FormulaLocalSRC(long nSheet, long nRow, long nCol, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_BSTR ;
		InvokeHelper(0x530, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nSheet, nRow, nCol, newValue);
	}
	CString get_DefinedNameLocal(LPCTSTR pName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x531, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, pName);
		return result;
	}
	void put_DefinedNameLocal(LPCTSTR pName, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x531, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, pName, newValue);
	}
	void CopyDataFromArray(long nSheet, long nRow1, long nCol1, long nRow2, long nCol2, BOOL bValuesOnly, VARIANT Array)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BOOL VTS_VARIANT ;
		InvokeHelper(0x534, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nSheet, nRow1, nCol1, nRow2, nCol2, bValuesOnly, &Array);
	}
	void CopyDataToArray(long nSheet, long nRow1, long nCol1, long nRow2, long nCol2, BOOL bValuesOnly, VARIANT Array)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BOOL VTS_VARIANT ;
		InvokeHelper(0x535, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nSheet, nRow1, nCol1, nRow2, nCol2, bValuesOnly, &Array);
	}
	void FindDlg()
	{
		InvokeHelper(0x537, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ReplaceDlg()
	{
		InvokeHelper(0x538, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Find(LPCTSTR FindWhat, long nSheet, long nRow1, long nCol1, long nRow2, long nCol2, short Flags, long * pFound)
	{
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I2 VTS_PI4 ;
		InvokeHelper(0x539, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FindWhat, nSheet, nRow1, nCol1, nRow2, nCol2, Flags, pFound);
	}
	void Replace(LPCTSTR FindWhat, LPCTSTR ReplaceWith, long nSheet, long nRow1, long nCol1, long nRow2, long nCol2, short Flags, long * pFound, long * pReplaced)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I2 VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x53a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FindWhat, ReplaceWith, nSheet, nRow1, nCol1, nRow2, nCol2, Flags, pFound, pReplaced);
	}
	void ODBCError(BSTR * pSQLState, long * pNativeError, BSTR * pErrorMsg)
	{
		static BYTE parms[] = VTS_PBSTR VTS_PI4 VTS_PBSTR ;
		InvokeHelper(0x53b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pSQLState, pNativeError, pErrorMsg);
	}
	void ODBCPrepare(LPCTSTR SQLStr, short * pRetCode)
	{
		static BYTE parms[] = VTS_BSTR VTS_PI2 ;
		InvokeHelper(0x53c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SQLStr, pRetCode);
	}
	void ODBCBindParameter(long nParam, long nCol, short CDataType, short * pRetCode)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I2 VTS_PI2 ;
		InvokeHelper(0x53d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nParam, nCol, CDataType, pRetCode);
	}
	void ODBCExecute(long nRow1, long nRow2, short * pRetCode)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PI2 ;
		InvokeHelper(0x53e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nRow1, nRow2, pRetCode);
	}
	void InsertDlg()
	{
		InvokeHelper(0x53f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ObjNewPolygon(float X1, float Y1, float X2, float Y2, long * pID, VARIANT ArrayX, VARIANT ArrayY, BOOL bClosed)
	{
		static BYTE parms[] = VTS_R4 VTS_R4 VTS_R4 VTS_R4 VTS_PI4 VTS_VARIANT VTS_VARIANT VTS_BOOL ;
		InvokeHelper(0x541, DISPATCH_METHOD, VT_EMPTY, NULL, parms, X1, Y1, X2, Y2, pID, &ArrayX, &ArrayY, bClosed);
	}
	void ObjSetPolygonPoints(long nID, VARIANT ArrayX, VARIANT ArrayY, BOOL bClosed)
	{
		static BYTE parms[] = VTS_I4 VTS_VARIANT VTS_VARIANT VTS_BOOL ;
		InvokeHelper(0x542, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nID, &ArrayX, &ArrayY, bClosed);
	}
	void DefRowHeightDlg()
	{
		InvokeHelper(0x543, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void DefColWidthDlg()
	{
		InvokeHelper(0x544, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

// Properties
//

unsigned long GetBackColor()
{
	unsigned long result;
	GetProperty(0x3, VT_UI4, (void*)&result);
	return result;
}
void SetBackColor(unsigned long propVal)
{
	SetProperty(0x3, VT_UI4, propVal);
}
long GetCol()
{
	long result;
	GetProperty(0x4, VT_I4, (void*)&result);
	return result;
}
void SetCol(long propVal)
{
	SetProperty(0x4, VT_I4, propVal);
}
long GetRow()
{
	long result;
	GetProperty(0x5, VT_I4, (void*)&result);
	return result;
}
void SetRow(long propVal)
{
	SetProperty(0x5, VT_I4, propVal);
}
short GetShowHScrollBar()
{
	short result;
	GetProperty(0x6, VT_I2, (void*)&result);
	return result;
}
void SetShowHScrollBar(short propVal)
{
	SetProperty(0x6, VT_I2, propVal);
}
CString GetText()
{
	CString result;
	GetProperty(0x7, VT_BSTR, (void*)&result);
	return result;
}
void SetText(CString propVal)
{
	SetProperty(0x7, VT_BSTR, propVal);
}
double GetNumber()
{
	double result;
	GetProperty(0x8, VT_R8, (void*)&result);
	return result;
}
void SetNumber(double propVal)
{
	SetProperty(0x8, VT_R8, propVal);
}
CString GetFormula()
{
	CString result;
	GetProperty(0x9, VT_BSTR, (void*)&result);
	return result;
}
void SetFormula(CString propVal)
{
	SetProperty(0x9, VT_BSTR, propVal);
}
long GetFixedCol()
{
	long result;
	GetProperty(0xa, VT_I4, (void*)&result);
	return result;
}
void SetFixedCol(long propVal)
{
	SetProperty(0xa, VT_I4, propVal);
}
long GetFixedCols()
{
	long result;
	GetProperty(0xb, VT_I4, (void*)&result);
	return result;
}
void SetFixedCols(long propVal)
{
	SetProperty(0xb, VT_I4, propVal);
}
long GetFixedRow()
{
	long result;
	GetProperty(0xc, VT_I4, (void*)&result);
	return result;
}
void SetFixedRow(long propVal)
{
	SetProperty(0xc, VT_I4, propVal);
}
long GetFixedRows()
{
	long result;
	GetProperty(0xd, VT_I4, (void*)&result);
	return result;
}
void SetFixedRows(long propVal)
{
	SetProperty(0xd, VT_I4, propVal);
}
BOOL GetShowGridLines()
{
	BOOL result;
	GetProperty(0xe, VT_BOOL, (void*)&result);
	return result;
}
void SetShowGridLines(BOOL propVal)
{
	SetProperty(0xe, VT_BOOL, propVal);
}
BOOL GetShowRowHeading()
{
	BOOL result;
	GetProperty(0xf, VT_BOOL, (void*)&result);
	return result;
}
void SetShowRowHeading(BOOL propVal)
{
	SetProperty(0xf, VT_BOOL, propVal);
}
short GetShowSelections()
{
	short result;
	GetProperty(0x10, VT_I2, (void*)&result);
	return result;
}
void SetShowSelections(short propVal)
{
	SetProperty(0x10, VT_I2, propVal);
}
long GetLeftCol()
{
	long result;
	GetProperty(0x11, VT_I4, (void*)&result);
	return result;
}
void SetLeftCol(long propVal)
{
	SetProperty(0x11, VT_I4, propVal);
}
long GetMaxCol()
{
	long result;
	GetProperty(0x12, VT_I4, (void*)&result);
	return result;
}
void SetMaxCol(long propVal)
{
	SetProperty(0x12, VT_I4, propVal);
}
long GetMaxRow()
{
	long result;
	GetProperty(0x13, VT_I4, (void*)&result);
	return result;
}
void SetMaxRow(long propVal)
{
	SetProperty(0x13, VT_I4, propVal);
}
long GetTopRow()
{
	long result;
	GetProperty(0x14, VT_I4, (void*)&result);
	return result;
}
void SetTopRow(long propVal)
{
	SetProperty(0x14, VT_I4, propVal);
}
BOOL GetAllowResize()
{
	BOOL result;
	GetProperty(0x15, VT_BOOL, (void*)&result);
	return result;
}
void SetAllowResize(BOOL propVal)
{
	SetProperty(0x15, VT_BOOL, propVal);
}
BOOL GetAllowSelections()
{
	BOOL result;
	GetProperty(0x16, VT_BOOL, (void*)&result);
	return result;
}
void SetAllowSelections(BOOL propVal)
{
	SetProperty(0x16, VT_BOOL, propVal);
}
BOOL GetAllowFormulas()
{
	BOOL result;
	GetProperty(0x17, VT_BOOL, (void*)&result);
	return result;
}
void SetAllowFormulas(BOOL propVal)
{
	SetProperty(0x17, VT_BOOL, propVal);
}
BOOL GetAllowInCellEditing()
{
	BOOL result;
	GetProperty(0x18, VT_BOOL, (void*)&result);
	return result;
}
void SetAllowInCellEditing(BOOL propVal)
{
	SetProperty(0x18, VT_BOOL, propVal);
}
short GetShowVScrollBar()
{
	short result;
	GetProperty(0x19, VT_I2, (void*)&result);
	return result;
}
void SetShowVScrollBar(short propVal)
{
	SetProperty(0x19, VT_I2, propVal);
}
BOOL GetAllowFillRange()
{
	BOOL result;
	GetProperty(0x1a, VT_BOOL, (void*)&result);
	return result;
}
void SetAllowFillRange(BOOL propVal)
{
	SetProperty(0x1a, VT_BOOL, propVal);
}
BOOL GetAllowMoveRange()
{
	BOOL result;
	GetProperty(0x1b, VT_BOOL, (void*)&result);
	return result;
}
void SetAllowMoveRange(BOOL propVal)
{
	SetProperty(0x1b, VT_BOOL, propVal);
}
long GetSelStartCol()
{
	long result;
	GetProperty(0x1c, VT_I4, (void*)&result);
	return result;
}
void SetSelStartCol(long propVal)
{
	SetProperty(0x1c, VT_I4, propVal);
}
long GetSelStartRow()
{
	long result;
	GetProperty(0x1d, VT_I4, (void*)&result);
	return result;
}
void SetSelStartRow(long propVal)
{
	SetProperty(0x1d, VT_I4, propVal);
}
long GetSelEndCol()
{
	long result;
	GetProperty(0x1e, VT_I4, (void*)&result);
	return result;
}
void SetSelEndCol(long propVal)
{
	SetProperty(0x1e, VT_I4, propVal);
}
long GetSelEndRow()
{
	long result;
	GetProperty(0x1f, VT_I4, (void*)&result);
	return result;
}
void SetSelEndRow(long propVal)
{
	SetProperty(0x1f, VT_I4, propVal);
}
unsigned long GetExtraColor()
{
	unsigned long result;
	GetProperty(0x20, VT_UI4, (void*)&result);
	return result;
}
void SetExtraColor(unsigned long propVal)
{
	SetProperty(0x20, VT_UI4, propVal);
}
CString GetFileName()
{
	CString result;
	GetProperty(0x21, VT_BSTR, (void*)&result);
	return result;
}
void SetFileName(CString propVal)
{
	SetProperty(0x21, VT_BSTR, propVal);
}
BOOL GetAutoRecalc()
{
	BOOL result;
	GetProperty(0x22, VT_BOOL, (void*)&result);
	return result;
}
void SetAutoRecalc(BOOL propVal)
{
	SetProperty(0x22, VT_BOOL, propVal);
}
BOOL GetPrintGridLines()
{
	BOOL result;
	GetProperty(0x23, VT_BOOL, (void*)&result);
	return result;
}
void SetPrintGridLines(BOOL propVal)
{
	SetProperty(0x23, VT_BOOL, propVal);
}
BOOL GetPrintRowHeading()
{
	BOOL result;
	GetProperty(0x24, VT_BOOL, (void*)&result);
	return result;
}
void SetPrintRowHeading(BOOL propVal)
{
	SetProperty(0x24, VT_BOOL, propVal);
}
BOOL GetPrintHCenter()
{
	BOOL result;
	GetProperty(0x25, VT_BOOL, (void*)&result);
	return result;
}
void SetPrintHCenter(BOOL propVal)
{
	SetProperty(0x25, VT_BOOL, propVal);
}
BOOL GetPrintVCenter()
{
	BOOL result;
	GetProperty(0x26, VT_BOOL, (void*)&result);
	return result;
}
void SetPrintVCenter(BOOL propVal)
{
	SetProperty(0x26, VT_BOOL, propVal);
}
BOOL GetPrintLeftToRight()
{
	BOOL result;
	GetProperty(0x27, VT_BOOL, (void*)&result);
	return result;
}
void SetPrintLeftToRight(BOOL propVal)
{
	SetProperty(0x27, VT_BOOL, propVal);
}
CString GetPrintHeader()
{
	CString result;
	GetProperty(0x28, VT_BSTR, (void*)&result);
	return result;
}
void SetPrintHeader(CString propVal)
{
	SetProperty(0x28, VT_BSTR, propVal);
}
CString GetPrintFooter()
{
	CString result;
	GetProperty(0x29, VT_BSTR, (void*)&result);
	return result;
}
void SetPrintFooter(CString propVal)
{
	SetProperty(0x29, VT_BSTR, propVal);
}
double GetPrintLeftMargin()
{
	double result;
	GetProperty(0x2a, VT_R8, (void*)&result);
	return result;
}
void SetPrintLeftMargin(double propVal)
{
	SetProperty(0x2a, VT_R8, propVal);
}
double GetPrintTopMargin()
{
	double result;
	GetProperty(0x2b, VT_R8, (void*)&result);
	return result;
}
void SetPrintTopMargin(double propVal)
{
	SetProperty(0x2b, VT_R8, propVal);
}
double GetPrintRightMargin()
{
	double result;
	GetProperty(0x2c, VT_R8, (void*)&result);
	return result;
}
void SetPrintRightMargin(double propVal)
{
	SetProperty(0x2c, VT_R8, propVal);
}
double GetPrintBottomMargin()
{
	double result;
	GetProperty(0x2d, VT_R8, (void*)&result);
	return result;
}
void SetPrintBottomMargin(double propVal)
{
	SetProperty(0x2d, VT_R8, propVal);
}
CString GetPrintArea()
{
	CString result;
	GetProperty(0x2e, VT_BSTR, (void*)&result);
	return result;
}
void SetPrintArea(CString propVal)
{
	SetProperty(0x2e, VT_BSTR, propVal);
}
CString GetPrintTitles()
{
	CString result;
	GetProperty(0x2f, VT_BSTR, (void*)&result);
	return result;
}
void SetPrintTitles(CString propVal)
{
	SetProperty(0x2f, VT_BSTR, propVal);
}
BOOL GetPrintNoColor()
{
	BOOL result;
	GetProperty(0x30, VT_BOOL, (void*)&result);
	return result;
}
void SetPrintNoColor(BOOL propVal)
{
	SetProperty(0x30, VT_BOOL, propVal);
}
CString GetSelection()
{
	CString result;
	GetProperty(0x31, VT_BSTR, (void*)&result);
	return result;
}
void SetSelection(CString propVal)
{
	SetProperty(0x31, VT_BSTR, propVal);
}
CString GetTableName()
{
	CString result;
	GetProperty(0x32, VT_BSTR, (void*)&result);
	return result;
}
void SetTableName(CString propVal)
{
	SetProperty(0x32, VT_BSTR, propVal);
}
BOOL GetDoCancelEdit()
{
	BOOL result;
	GetProperty(0x33, VT_BOOL, (void*)&result);
	return result;
}
void SetDoCancelEdit(BOOL propVal)
{
	SetProperty(0x33, VT_BOOL, propVal);
}
BOOL GetDoSelChange()
{
	BOOL result;
	GetProperty(0x34, VT_BOOL, (void*)&result);
	return result;
}
void SetDoSelChange(BOOL propVal)
{
	SetProperty(0x34, VT_BOOL, propVal);
}
BOOL GetDoStartEdit()
{
	BOOL result;
	GetProperty(0x35, VT_BOOL, (void*)&result);
	return result;
}
void SetDoStartEdit(BOOL propVal)
{
	SetProperty(0x35, VT_BOOL, propVal);
}
BOOL GetDoEndEdit()
{
	BOOL result;
	GetProperty(0x36, VT_BOOL, (void*)&result);
	return result;
}
void SetDoEndEdit(BOOL propVal)
{
	SetProperty(0x36, VT_BOOL, propVal);
}
BOOL GetDoStartRecalc()
{
	BOOL result;
	GetProperty(0x37, VT_BOOL, (void*)&result);
	return result;
}
void SetDoStartRecalc(BOOL propVal)
{
	SetProperty(0x37, VT_BOOL, propVal);
}
BOOL GetDoEndRecalc()
{
	BOOL result;
	GetProperty(0x38, VT_BOOL, (void*)&result);
	return result;
}
void SetDoEndRecalc(BOOL propVal)
{
	SetProperty(0x38, VT_BOOL, propVal);
}
BOOL GetDoClick()
{
	BOOL result;
	GetProperty(0x39, VT_BOOL, (void*)&result);
	return result;
}
void SetDoClick(BOOL propVal)
{
	SetProperty(0x39, VT_BOOL, propVal);
}
BOOL GetDoDblClick()
{
	BOOL result;
	GetProperty(0x3a, VT_BOOL, (void*)&result);
	return result;
}
void SetDoDblClick(BOOL propVal)
{
	SetProperty(0x3a, VT_BOOL, propVal);
}
BOOL GetShowColHeading()
{
	BOOL result;
	GetProperty(0x3b, VT_BOOL, (void*)&result);
	return result;
}
void SetShowColHeading(BOOL propVal)
{
	SetProperty(0x3b, VT_BOOL, propVal);
}
BOOL GetPrintColHeading()
{
	BOOL result;
	GetProperty(0x3c, VT_BOOL, (void*)&result);
	return result;
}
void SetPrintColHeading(BOOL propVal)
{
	SetProperty(0x3c, VT_BOOL, propVal);
}
CString GetEntry()
{
	CString result;
	GetProperty(0x3d, VT_BSTR, (void*)&result);
	return result;
}
void SetEntry(CString propVal)
{
	SetProperty(0x3d, VT_BSTR, propVal);
}
BOOL GetRepaint()
{
	BOOL result;
	GetProperty(0x3e, VT_BOOL, (void*)&result);
	return result;
}
void SetRepaint(BOOL propVal)
{
	SetProperty(0x3e, VT_BOOL, propVal);
}
BOOL GetAllowArrows()
{
	BOOL result;
	GetProperty(0x3f, VT_BOOL, (void*)&result);
	return result;
}
void SetAllowArrows(BOOL propVal)
{
	SetProperty(0x3f, VT_BOOL, propVal);
}
BOOL GetAllowTabs()
{
	BOOL result;
	GetProperty(0x40, VT_BOOL, (void*)&result);
	return result;
}
void SetAllowTabs(BOOL propVal)
{
	SetProperty(0x40, VT_BOOL, propVal);
}
CString GetFormattedText()
{
	CString result;
	GetProperty(0x41, VT_BSTR, (void*)&result);
	return result;
}
void SetFormattedText(CString propVal)
{
	SetProperty(0x41, VT_BSTR, propVal);
}
BOOL GetRowMode()
{
	BOOL result;
	GetProperty(0x42, VT_BOOL, (void*)&result);
	return result;
}
void SetRowMode(BOOL propVal)
{
	SetProperty(0x42, VT_BOOL, propVal);
}
BOOL GetAllowDelete()
{
	BOOL result;
	GetProperty(0x43, VT_BOOL, (void*)&result);
	return result;
}
void SetAllowDelete(BOOL propVal)
{
	SetProperty(0x43, VT_BOOL, propVal);
}
BOOL GetEnableProtection()
{
	BOOL result;
	GetProperty(0x44, VT_BOOL, (void*)&result);
	return result;
}
void SetEnableProtection(BOOL propVal)
{
	SetProperty(0x44, VT_BOOL, propVal);
}
long GetMinCol()
{
	long result;
	GetProperty(0x45, VT_I4, (void*)&result);
	return result;
}
void SetMinCol(long propVal)
{
	SetProperty(0x45, VT_I4, propVal);
}
long GetMinRow()
{
	long result;
	GetProperty(0x46, VT_I4, (void*)&result);
	return result;
}
void SetMinRow(long propVal)
{
	SetProperty(0x46, VT_I4, propVal);
}
BOOL GetDoTopLeftChanged()
{
	BOOL result;
	GetProperty(0x47, VT_BOOL, (void*)&result);
	return result;
}
void SetDoTopLeftChanged(BOOL propVal)
{
	SetProperty(0x47, VT_BOOL, propVal);
}
BOOL GetAllowEditHeaders()
{
	BOOL result;
	GetProperty(0x48, VT_BOOL, (void*)&result);
	return result;
}
void SetAllowEditHeaders(BOOL propVal)
{
	SetProperty(0x48, VT_BOOL, propVal);
}
BOOL GetDoObjClick()
{
	BOOL result;
	GetProperty(0x49, VT_BOOL, (void*)&result);
	return result;
}
void SetDoObjClick(BOOL propVal)
{
	SetProperty(0x49, VT_BOOL, propVal);
}
BOOL GetDoObjDblClick()
{
	BOOL result;
	GetProperty(0x4a, VT_BOOL, (void*)&result);
	return result;
}
void SetDoObjDblClick(BOOL propVal)
{
	SetProperty(0x4a, VT_BOOL, propVal);
}
BOOL GetAllowObjSelections()
{
	BOOL result;
	GetProperty(0x4b, VT_BOOL, (void*)&result);
	return result;
}
void SetAllowObjSelections(BOOL propVal)
{
	SetProperty(0x4b, VT_BOOL, propVal);
}
BOOL GetDoRClick()
{
	BOOL result;
	GetProperty(0x4c, VT_BOOL, (void*)&result);
	return result;
}
void SetDoRClick(BOOL propVal)
{
	SetProperty(0x4c, VT_BOOL, propVal);
}
BOOL GetDoRDblClick()
{
	BOOL result;
	GetProperty(0x4d, VT_BOOL, (void*)&result);
	return result;
}
void SetDoRDblClick(BOOL propVal)
{
	SetProperty(0x4d, VT_BOOL, propVal);
}
CString GetClip()
{
	CString result;
	GetProperty(0x4e, VT_BSTR, (void*)&result);
	return result;
}
void SetClip(CString propVal)
{
	SetProperty(0x4e, VT_BSTR, propVal);
}
CString GetClipValues()
{
	CString result;
	GetProperty(0x4f, VT_BSTR, (void*)&result);
	return result;
}
void SetClipValues(CString propVal)
{
	SetProperty(0x4f, VT_BSTR, propVal);
}
BOOL GetPrintLandscape()
{
	BOOL result;
	GetProperty(0x50, VT_BOOL, (void*)&result);
	return result;
}
void SetPrintLandscape(BOOL propVal)
{
	SetProperty(0x50, VT_BOOL, propVal);
}
BOOL GetEnabled()
{
	BOOL result;
	GetProperty(DISPID_ENABLED, VT_BOOL, (void*)&result);
	return result;
}
void SetEnabled(BOOL propVal)
{
	SetProperty(DISPID_ENABLED, VT_BOOL, propVal);
}
short GetBorderStyle()
{
	short result;
	GetProperty(DISPID_BORDERSTYLE, VT_I2, (void*)&result);
	return result;
}
void SetBorderStyle(short propVal)
{
	SetProperty(DISPID_BORDERSTYLE, VT_I2, propVal);
}
CString GetAppName()
{
	CString result;
	GetProperty(0x51, VT_BSTR, (void*)&result);
	return result;
}
void SetAppName(CString propVal)
{
	SetProperty(0x51, VT_BSTR, propVal);
}
short GetHdrHeight()
{
	short result;
	GetProperty(0x52, VT_I2, (void*)&result);
	return result;
}
void SetHdrHeight(short propVal)
{
	SetProperty(0x52, VT_I2, propVal);
}
short GetHdrWidth()
{
	short result;
	GetProperty(0x53, VT_I2, (void*)&result);
	return result;
}
void SetHdrWidth(short propVal)
{
	SetProperty(0x53, VT_I2, propVal);
}
CString GetNumberFormat()
{
	CString result;
	GetProperty(0x54, VT_BSTR, (void*)&result);
	return result;
}
void SetNumberFormat(CString propVal)
{
	SetProperty(0x54, VT_BSTR, propVal);
}
CString GetTopLeftText()
{
	CString result;
	GetProperty(0x55, VT_BSTR, (void*)&result);
	return result;
}
void SetTopLeftText(CString propVal)
{
	SetProperty(0x55, VT_BSTR, propVal);
}
BOOL GetEnterMovesDown()
{
	BOOL result;
	GetProperty(0x56, VT_BOOL, (void*)&result);
	return result;
}
void SetEnterMovesDown(BOOL propVal)
{
	SetProperty(0x56, VT_BOOL, propVal);
}
long GetLastCol()
{
	long result;
	GetProperty(0x57, VT_I4, (void*)&result);
	return result;
}
void SetLastCol(long propVal)
{
	SetProperty(0x57, VT_I4, propVal);
}
long GetLastRow()
{
	long result;
	GetProperty(0x58, VT_I4, (void*)&result);
	return result;
}
void SetLastRow(long propVal)
{
	SetProperty(0x58, VT_I4, propVal);
}
BOOL GetLogical()
{
	BOOL result;
	GetProperty(0x59, VT_BOOL, (void*)&result);
	return result;
}
void SetLogical(BOOL propVal)
{
	SetProperty(0x59, VT_BOOL, propVal);
}
short GetMode()
{
	short result;
	GetProperty(0x5a, VT_I2, (void*)&result);
	return result;
}
void SetMode(short propVal)
{
	SetProperty(0x5a, VT_I2, propVal);
}
short GetPolyEditMode()
{
	short result;
	GetProperty(0x5b, VT_I2, (void*)&result);
	return result;
}
void SetPolyEditMode(short propVal)
{
	SetProperty(0x5b, VT_I2, propVal);
}
short GetViewScale()
{
	short result;
	GetProperty(0x5c, VT_I2, (void*)&result);
	return result;
}
void SetViewScale(short propVal)
{
	SetProperty(0x5c, VT_I2, propVal);
}
short GetSelectionCount()
{
	short result;
	GetProperty(0x5d, VT_I2, (void*)&result);
	return result;
}
void SetSelectionCount(short propVal)
{
	SetProperty(0x5d, VT_I2, propVal);
}
CString GetTitle()
{
	CString result;
	GetProperty(0x5e, VT_BSTR, (void*)&result);
	return result;
}
void SetTitle(CString propVal)
{
	SetProperty(0x5e, VT_BSTR, propVal);
}
short GetType()
{
	short result;
	GetProperty(0x5f, VT_I2, (void*)&result);
	return result;
}
void SetType(short propVal)
{
	SetProperty(0x5f, VT_I2, propVal);
}
BOOL GetShowFormulas()
{
	BOOL result;
	GetProperty(0x60, VT_BOOL, (void*)&result);
	return result;
}
void SetShowFormulas(BOOL propVal)
{
	SetProperty(0x60, VT_BOOL, propVal);
}
BOOL GetShowZeroValues()
{
	BOOL result;
	GetProperty(0x61, VT_BOOL, (void*)&result);
	return result;
}
void SetShowZeroValues(BOOL propVal)
{
	SetProperty(0x61, VT_BOOL, propVal);
}
short GetMousePointer()
{
	short result;
	GetProperty(0x2, VT_I2, (void*)&result);
	return result;
}
void SetMousePointer(short propVal)
{
	SetProperty(0x2, VT_I2, propVal);
}
IPictureDisp * GetMouseIcon()
{
	IPictureDisp * result;
	GetProperty(0x62, VT_DISPATCH, (void*)&result);
	return result;
}
void SetMouseIcon(IPictureDisp * propVal)
{
	SetProperty(0x62, VT_DISPATCH, propVal);
}
BOOL GetDoObjValueChanged()
{
	BOOL result;
	GetProperty(0x63, VT_BOOL, (void*)&result);
	return result;
}
void SetDoObjValueChanged(BOOL propVal)
{
	SetProperty(0x63, VT_BOOL, propVal);
}
BOOL GetScrollToLastRC()
{
	BOOL result;
	GetProperty(0x64, VT_BOOL, (void*)&result);
	return result;
}
void SetScrollToLastRC(BOOL propVal)
{
	SetProperty(0x64, VT_BOOL, propVal);
}
BOOL GetModified()
{
	BOOL result;
	GetProperty(0x65, VT_BOOL, (void*)&result);
	return result;
}
void SetModified(BOOL propVal)
{
	SetProperty(0x65, VT_BOOL, propVal);
}
BOOL GetDoObjGotFocus()
{
	BOOL result;
	GetProperty(0x66, VT_BOOL, (void*)&result);
	return result;
}
void SetDoObjGotFocus(BOOL propVal)
{
	SetProperty(0x66, VT_BOOL, propVal);
}
BOOL GetDoObjLostFocus()
{
	BOOL result;
	GetProperty(0x67, VT_BOOL, (void*)&result);
	return result;
}
void SetDoObjLostFocus(BOOL propVal)
{
	SetProperty(0x67, VT_BOOL, propVal);
}
OLE_HANDLE GetPrintDevMode()
{
	OLE_HANDLE result;
	GetProperty(0x68, VT_I4, (void*)&result);
	return result;
}
void SetPrintDevMode(OLE_HANDLE propVal)
{
	SetProperty(0x68, VT_I4, propVal);
}
long GetNumSheets()
{
	long result;
	GetProperty(0x69, VT_I4, (void*)&result);
	return result;
}
void SetNumSheets(long propVal)
{
	SetProperty(0x69, VT_I4, propVal);
}
long GetSheet()
{
	long result;
	GetProperty(0x6a, VT_I4, (void*)&result);
	return result;
}
void SetSheet(long propVal)
{
	SetProperty(0x6a, VT_I4, propVal);
}
short GetColWidthUnits()
{
	short result;
	GetProperty(0x6b, VT_I2, (void*)&result);
	return result;
}
void SetColWidthUnits(short propVal)
{
	SetProperty(0x6b, VT_I2, propVal);
}
BOOL GetShowTypeMarkers()
{
	BOOL result;
	GetProperty(0x6c, VT_BOOL, (void*)&result);
	return result;
}
void SetShowTypeMarkers(BOOL propVal)
{
	SetProperty(0x6c, VT_BOOL, propVal);
}
short GetShowTabs()
{
	short result;
	GetProperty(0x6d, VT_I2, (void*)&result);
	return result;
}
void SetShowTabs(short propVal)
{
	SetProperty(0x6d, VT_I2, propVal);
}
BOOL GetShowEditBar()
{
	BOOL result;
	GetProperty(0x6e, VT_BOOL, (void*)&result);
	return result;
}
void SetShowEditBar(BOOL propVal)
{
	SetProperty(0x6e, VT_BOOL, propVal);
}
BOOL GetShowEditBarCellRef()
{
	BOOL result;
	GetProperty(0x6f, VT_BOOL, (void*)&result);
	return result;
}
void SetShowEditBarCellRef(BOOL propVal)
{
	SetProperty(0x6f, VT_BOOL, propVal);
}
BOOL GetAllowDesigner()
{
	BOOL result;
	GetProperty(0x1, VT_BOOL, (void*)&result);
	return result;
}
void SetAllowDesigner(BOOL propVal)
{
	SetProperty(0x1, VT_BOOL, propVal);
}
OLE_HANDLE GethWnd()
{
	OLE_HANDLE result;
	GetProperty(DISPID_HWND, VT_I4, (void*)&result);
	return result;
}
void SethWnd(OLE_HANDLE propVal)
{
	SetProperty(DISPID_HWND, VT_I4, propVal);
}
BOOL GetAllowAutoFill()
{
	BOOL result;
	GetProperty(0x70, VT_BOOL, (void*)&result);
	return result;
}
void SetAllowAutoFill(BOOL propVal)
{
	SetProperty(0x70, VT_BOOL, propVal);
}
BOOL GetCompressed()
{
	BOOL result;
	GetProperty(0x12b, VT_BOOL, (void*)&result);
	return result;
}
void SetCompressed(BOOL propVal)
{
	SetProperty(0x12b, VT_BOOL, propVal);
}
CString GetFontName()
{
	CString result;
	GetProperty(0x514, VT_BSTR, (void*)&result);
	return result;
}
void SetFontName(CString propVal)
{
	SetProperty(0x514, VT_BSTR, propVal);
}
short GetFontSize()
{
	short result;
	GetProperty(0x515, VT_I2, (void*)&result);
	return result;
}
void SetFontSize(short propVal)
{
	SetProperty(0x515, VT_I2, propVal);
}
BOOL GetFontBold()
{
	BOOL result;
	GetProperty(0x516, VT_BOOL, (void*)&result);
	return result;
}
void SetFontBold(BOOL propVal)
{
	SetProperty(0x516, VT_BOOL, propVal);
}
BOOL GetFontItalic()
{
	BOOL result;
	GetProperty(0x517, VT_BOOL, (void*)&result);
	return result;
}
void SetFontItalic(BOOL propVal)
{
	SetProperty(0x517, VT_BOOL, propVal);
}
BOOL GetFontUnderline()
{
	BOOL result;
	GetProperty(0x518, VT_BOOL, (void*)&result);
	return result;
}
void SetFontUnderline(BOOL propVal)
{
	SetProperty(0x518, VT_BOOL, propVal);
}
BOOL GetFontStrikeout()
{
	BOOL result;
	GetProperty(0x519, VT_BOOL, (void*)&result);
	return result;
}
void SetFontStrikeout(BOOL propVal)
{
	SetProperty(0x519, VT_BOOL, propVal);
}
unsigned long GetFontColor()
{
	unsigned long result;
	GetProperty(0x51a, VT_UI4, (void*)&result);
	return result;
}
void SetFontColor(unsigned long propVal)
{
	SetProperty(0x51a, VT_UI4, propVal);
}
short GetHAlign()
{
	short result;
	GetProperty(0x51b, VT_I2, (void*)&result);
	return result;
}
void SetHAlign(short propVal)
{
	SetProperty(0x51b, VT_I2, propVal);
}
BOOL GetWordWrap()
{
	BOOL result;
	GetProperty(0x51c, VT_BOOL, (void*)&result);
	return result;
}
void SetWordWrap(BOOL propVal)
{
	SetProperty(0x51c, VT_BOOL, propVal);
}
short GetVAlign()
{
	short result;
	GetProperty(0x51d, VT_I2, (void*)&result);
	return result;
}
void SetVAlign(short propVal)
{
	SetProperty(0x51d, VT_I2, propVal);
}
BOOL GetLaunchWorkbookDesigner()
{
	BOOL result;
	GetProperty(0x51e, VT_BOOL, (void*)&result);
	return result;
}
void SetLaunchWorkbookDesigner(BOOL propVal)
{
	SetProperty(0x51e, VT_BOOL, propVal);
}
double GetPrintHeaderMargin()
{
	double result;
	GetProperty(0x51f, VT_R8, (void*)&result);
	return result;
}
void SetPrintHeaderMargin(double propVal)
{
	SetProperty(0x51f, VT_R8, propVal);
}
double GetPrintFooterMargin()
{
	double result;
	GetProperty(0x520, VT_R8, (void*)&result);
	return result;
}
void SetPrintFooterMargin(double propVal)
{
	SetProperty(0x520, VT_R8, propVal);
}
CString GetFormulaLocal()
{
	CString result;
	GetProperty(0x52e, VT_BSTR, (void*)&result);
	return result;
}
void SetFormulaLocal(CString propVal)
{
	SetProperty(0x52e, VT_BSTR, propVal);
}
CString GetNumberFormatLocal()
{
	CString result;
	GetProperty(0x532, VT_BSTR, (void*)&result);
	return result;
}
void SetNumberFormatLocal(CString propVal)
{
	SetProperty(0x532, VT_BSTR, propVal);
}
CString GetSelectionLocal()
{
	CString result;
	GetProperty(0x533, VT_BSTR, (void*)&result);
	return result;
}
void SetSelectionLocal(CString propVal)
{
	SetProperty(0x533, VT_BSTR, propVal);
}
CString GetDataTransferRange()
{
	CString result;
	GetProperty(0x536, VT_BSTR, (void*)&result);
	return result;
}
void SetDataTransferRange(CString propVal)
{
	SetProperty(0x536, VT_BSTR, propVal);
}
BOOL GetCanEditPaste()
{
	BOOL result;
	GetProperty(0x540, VT_BOOL, (void*)&result);
	return result;
}
void SetCanEditPaste(BOOL propVal)
{
	SetProperty(0x540, VT_BOOL, propVal);
}


};
