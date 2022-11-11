#pragma once

class CTXTextControl23 : public CWnd
{

protected:

	DECLARE_DYNCREATE(CTXTextControl23)

public:

	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x67D06A01, 0x8469, 0x11E5, { 0xA5, 0xC5, 0x0, 0x13, 0xD3, 0x50, 0x66, 0x7C } };
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

	enum
	{
		txTableCellHorizontalPos = 0,
		txTableCellHorizontalExt = 1,
		txTableCellBorderWidth = 2,
		txTableCellTextGap = 3,
		txTableCellBackColor = 4,
		txTableCellLeftBorderWidth = 5,
		txTableCellTopBorderWidth = 6,
		txTableCellRightBorderWidth = 7,
		txTableCellBottomBorderWidth = 8,
		txTableCellLeftTextGap = 9,
		txTableCellTopTextGap = 10,
		txTableCellRightTextGap = 11,
		txTableCellBottomTextGap = 12,
		txTableCellVertAlign = 13,
		txTableCellHeight = 14,
		txTableCellPageBreakAllowed = 15,
		txTableCellIsHeader = 16,
		txTableCellLeftBorderColor = 17,
		txTableCellTopBorderColor = 18,
		txTableCellRightBorderColor = 19,
		txTableCellBottomBorderColor = 20
	}TableCellAttributeConstants;
	enum
	{
		txPageBorderLeftBorderWidth = 1,
		txPageBorderTopBorderWidth = 2,
		txPageBorderRightBorderWidth = 3,
		txPageBorderBottomBorderWidth = 4,
		txPageBorderLeftDistance = 5,
		txPageBorderTopDistance = 6,
		txPageBorderRightDistance = 7,
		txPageBorderBottomDistance = 8,
		txPageBorderLeftBorderColor = 9,
		txPageBorderTopBorderColor = 10,
		txPageBorderRightBorderColor = 11,
		txPageBorderBottomBorderColor = 12,
		txPageBorderOmitFirstPage = 13,
		txPageBorderFirstPageOnly = 14,
		txPageBorderSurroundHeader = 15,
		txPageBorderSurroundFooter = 16,
		txPageBorderMeasureFromText = 17
	}PageBorderAttributeConstants;
	enum
	{
		txTableInsertInFront = 1,
		txTableInsertAfter = 2
	}TableInsertConstants;
	enum
	{
		txFlat = 0,
		tx3D = 1,
		txXP = 2,
		txColorScheme = 3
	}AppearanceStyles;
	enum
	{
		sbFlat = 0,
		sb3D = 1,
		sbXP = 2,
		sbColorScheme = 3,
		sbVerticalColorScheme = 4
	}StatusBarAppearanceStyles;
	enum
	{
		txClassicColors = 0,
		txGradientColors = 1
	}PageViewStyles;
	enum
	{
		txHorizontal = 0,
		txVertical = 1
	}RulerBarDirection;
	enum
	{
		txHeader = 1,
		txFirstHeader = 2,
		txFooter = 4,
		txFirstFooter = 8,
		txMainText = 16,
		txEvenHeader = 128,
		txEvenFooter = 256
	}HeaderFooterConstants;
	enum
	{
		txMouseClick = 1,
		txNoDblClk = 2,
		txSolidFrame = 4,
		txUnframed = 8,
		txDividingLine = 16
	}HeaderFooterStyleConstants;
	enum
	{
		txDocWidth = 0,
		txDocHeight = 1,
		txDocLeftMargin = 2,
		txDocTopMargin = 3,
		txDocRightMargin = 4,
		txDocBottomMargin = 5,
		txDocTitle = 6,
		txDocBkColor = 7,
		txCSSFile = 8,
		txCSSSaveMode = 9,
		txDocAccessPermissions = 10,
		txMasterPassword = 11,
		txUserPassword = 12,
		txImageCompressionQuality = 13,
		txImageMaxResolution = 14,
		txLoadMSWordFields = 15,
		txLoadHighEditFields = 16,
		txMSWordFieldTypeNames = 17,
		txImageSaveMode = 18,
		txImageExportFormat = 19,
		txCertificateFileName = 20,
		txCertificatePassword = 21,
		txTimeServerURL = 22,
		txDocumentLevelJavaScriptActions = 23,
		txAbsPath = 28,
		txBasePath = 29,
		txBaseFontSize = 30,
		txPropFontName = 31,
		txMonoFontName = 32,
		txTextColor = 33,
		txOverwriteTextColor = 34,
		txTextBkColor = 35,
		txOverwriteTextBkColor = 36,
		txLoadImages = 37,
		txEnableLinks = 38,
		txEnableHighlights = 39,
		txEnableTopics = 40,
		txAuthor = 41,
		txCreationDate = 42,
		txDocKeywords = 43,
		txLastModificationDate = 44,
		txDocSubject = 45,
		txCreatorApplication = 46,
		txLinkColor = 50,
		txOverwriteLinkColor = 51,
		txUnderlineLinks = 52
	}LoadSaveAttributeConstants;
	enum
	{
		txFieldStandard = 0,
		txFieldExternalLink = 1,
		txFieldInternalLink = 2,
		txFieldPageNumber = 3,
		txFieldLinkTarget = 4,
		txFieldHighlight = 5,
		txFieldTopic = 6,
		txFieldMSWord = 7,
		txFieldHighEdit = 8,
		txFieldAllPages = 9
	}FieldTypeConstants;
	enum
	{
		txInsideField = 1,
		txOutsideField = 2,
		txInsideNextField = 3
	}FieldInputPositionConstants;
	enum
	{
		txListNone = 1,
		txListBulleted = 2,
		txListNumbered = 4,
		txListStructured = 8
	}ListTypeConstants;
	enum
	{
		txBulletChar = 0,
		txBulletFormatChar = 1,
		txBulletLevel = 2,
		txBulletPos = 3,
		txBulletSize = 4,
		txBulletTextPos = 5,
		txBulletFont = 6
	}BulletConstants;
	enum
	{
		txNumberingContinue = 0,
		txNumberingFormat = 1,
		txNumberingFormatChar = 2,
		txNumberingLevel = 3,
		txNumberingPos = 4,
		txNumberingPostChar = 5,
		txNumberingPreChar = 6,
		txNumberingReStart = 7,
		txNumberingStart = 8,
		txNumberingTextPos = 9,
		txNumberingPostText = 10,
		txNumberingPreText = 11
	}NumberingConstants;
	enum
	{
		txBeginAtNewLine = 256,
		txBeginAtNewPage = 512
	}SectionBreakKindConstants;
	enum
	{
		txDesktopColor = 0,
		txLightShadowColor = 1,
		txDarkShadowColor = 2,
		txHeaderFooterLineColor = 3,
		txHeaderFooterLabelColor = 4
	}TextControlColor;
	enum
	{
		bbForeColor = 0,
		bbBackColor = 1,
		bbGradientBackColor = 2,
		bbSeparatorColorLight = 3,
		bbSeparatorColorDark = 4,
		bbComboboxBackColor = 5,
		bbButtonBackColorTop = 6,
		bbButtonBackColorMiddle = 7,
		bbButtonBackColorBottom = 8,
		bbButtonHotTrackTop = 9,
		bbButtonHotTrackBottom = 10,
		bbButtonSelectedTop = 11,
		bbButtonSelectedBottom = 12,
		bbButtonPressedTop = 13,
		bbButtonPressedBottom = 14,
		bbButtonFrameColor = 15
	}ButtonBarColor;
	enum
	{
		rlForeColor = 0,
		rlBackColor = 1,
		rlGradientBackColor = 2,
		rlSeparatorColorLight = 3,
		rlSeparatorColorDark = 4,
		rlRulerColor = 5
	}RulerBarColor;
	enum
	{
		sbForeColor = 0,
		sbBackColor = 1,
		sbGradientBackColor = 2,
		sbFrameColor = 3,
		sbBackColorTop = 4,
		sbBackColorMiddle = 5,
		sbBackColorBottom = 6,
		sbSeparatorColorLight = 7,
		sbSeparatorColorDark = 8
	}StatusBarColor;
	enum
	{
		txAsCharacter = 1,
		txAnchoredToParagraph = 2,
		txFixedOnPage = 3
	}ObjectInsertionModeConstants;
	enum
	{
		pcBackground = 1,
		pcHeadersAndFooters = 2,
		pcMainText = 4,
		pcAll = 7
	}PictureContentConstants;
	enum
	{
		txZOrderTopMost = 1,
		txZOrderTop = 2,
		txZOrderUp = 3,
		txZOrderBottomMost = 4,
		txZOrderBottom = 5,
		txZOrderDown = 6
	}ZOrderConstants;
	enum
	{
		txSpace = 1,
		txTab = 2,
		txParagraph = 4,
		txLineBreak = 8,
		txObjectAnchor = 16,
		txPageBreak = 32,
		txSectionBreak = 64,
		txHyphen = 128,
		txNonBreakingSpace = 256,
		txTableCellEnd = 512,
		txAll = 1023
	}ControlCharConstants;
	enum
	{
		txRightToLeft = 1,
		txLeftToRight = 2
	}TextDirectionConstants;
	enum
	{
		txSpaces = 1,
		txKashida = 2,
		txSpacesAndKashida = 3
	}JustificationConstants;
	enum
	{
		txStartWithNewParagraph = 4,
		txStartWithNewSection = 8
	}AppendSettingsConstants;

	void Refresh()
	{
		InvokeHelper(DISPID_REFRESH, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void PrintPage(short PageNumber)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x53, DISPATCH_METHOD, VT_EMPTY, NULL, parms, PageNumber);
	}
	BOOL ParagraphDialog()
	{
		BOOL result;
		InvokeHelper(0x54, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL FontDialog()
	{
		BOOL result;
		InvokeHelper(0x55, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void FindReplace(short TypeOfDialog)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x56, DISPATCH_METHOD, VT_EMPTY, NULL, parms, TypeOfDialog);
	}
	BOOL Undo()
	{
		BOOL result;
		InvokeHelper(0x57, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL Redo()
	{
		BOOL result;
		InvokeHelper(0x58, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL VTSpellCheck()
	{
		BOOL result;
		InvokeHelper(0x59, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void Clip(short Action)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x5a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Action);
	}
	BOOL RTFImport(LPCTSTR FileName, VARIANT Extended)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_VARIANT ;
		InvokeHelper(0x5b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, FileName, &Extended);
		return result;
	}
	BOOL RTFExport(LPCTSTR FileName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x5c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, FileName);
		return result;
	}
	BOOL TextImport(LPCTSTR FileName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x5d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, FileName);
		return result;
	}
	BOOL TextExport(LPCTSTR FileName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x5e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, FileName);
		return result;
	}
	BOOL FieldInsert(LPCTSTR FieldText)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x5f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, FieldText);
		return result;
	}
	BOOL FieldDelete(BOOL DeleteTotal)
	{
		BOOL result;
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x60, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, DeleteTotal);
		return result;
	}
	short ObjectInsertAsChar(long ObjectType, LPCTSTR FileName, long TextPos, short ScaleX, short ScaleY, short ImageDisplayMode, short ImageSaveMode, VARIANT KindOfObject)
	{
		short result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_I4 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_VARIANT ;
		InvokeHelper(0x61, DISPATCH_METHOD, VT_I2, (void*)&result, parms, ObjectType, FileName, TextPos, ScaleX, ScaleY, ImageDisplayMode, ImageSaveMode, &KindOfObject);
		return result;
	}
	short ObjectInsertFixed(long ObjectType, LPCTSTR FileName, long PosX, long PosY, short ScaleX, short ScaleY, short ImageDisplayMode, short ImageSaveMode, short SizeMode, short Textflow, short DistanceL, short DistanceT, short DistanceR, short DistanceB, VARIANT KindOfObject)
	{
		short result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_VARIANT ;
		InvokeHelper(0x62, DISPATCH_METHOD, VT_I2, (void*)&result, parms, ObjectType, FileName, PosX, PosY, ScaleX, ScaleY, ImageDisplayMode, ImageSaveMode, SizeMode, Textflow, DistanceL, DistanceT, DistanceR, DistanceB, &KindOfObject);
		return result;
	}
	long Load(LPCTSTR FileName, VARIANT Offset, VARIANT Format, VARIANT CurSelection)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x63, DISPATCH_METHOD, VT_I4, (void*)&result, parms, FileName, &Offset, &Format, &CurSelection);
		return result;
	}
	long Save(LPCTSTR FileName, VARIANT Offset, VARIANT Format, VARIANT CurSelection)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x64, DISPATCH_METHOD, VT_I4, (void*)&result, parms, FileName, &Offset, &Format, &CurSelection);
		return result;
	}
	BOOL ObjectDelete(short ObjectId)
	{
		BOOL result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x65, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, ObjectId);
		return result;
	}
	short ObjectNext(short ObjectId, short ObjectGroup)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x66, DISPATCH_METHOD, VT_I2, (void*)&result, parms, ObjectId, ObjectGroup);
		return result;
	}
	short get_ObjectDistance(short index)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, index);
		return result;
	}
	void put_ObjectDistance(short index, short newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, index, newValue);
	}
	BOOL ViewNextHighlight()
	{
		BOOL result;
		InvokeHelper(0x68, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	short TableInsert(short Rows, short Columns, long TextPos, VARIANT TableId)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I4 VTS_VARIANT ;
		InvokeHelper(0x6c, DISPATCH_METHOD, VT_I2, (void*)&result, parms, Rows, Columns, TextPos, &TableId);
		return result;
	}
	BOOL TableDeleteLines()
	{
		BOOL result;
		InvokeHelper(0x6d, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	VARIANT get_LoadSaveAttribute(long Attribute)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x70, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, Attribute);
		return result;
	}
	void put_LoadSaveAttribute(long Attribute, VARIANT newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_VARIANT ;
		InvokeHelper(0x70, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, Attribute, &newValue);
	}
	BOOL TableAttrDialog()
	{
		BOOL result;
		InvokeHelper(0x72, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	short get_TableColumns(short TableId)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x75, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, TableId);
		return result;
	}
	short get_TableRows(short TableId)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, TableId);
		return result;
	}
	CString get_TableCellText(short TableId, short Row, short Column)
	{
		CString result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0x77, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, TableId, Row, Column);
		return result;
	}
	void put_TableCellText(short TableId, short Row, short Column, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 VTS_BSTR ;
		InvokeHelper(0x77, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, TableId, Row, Column, newValue);
	}
	short get_FieldEditAttr(short FieldId)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x7c, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, FieldId);
		return result;
	}
	void put_FieldEditAttr(short FieldId, short newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x7c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, FieldId, newValue);
	}
	short FieldNext(short FieldId, short FieldGroup)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x7d, DISPATCH_METHOD, VT_I2, (void*)&result, parms, FieldId, FieldGroup);
		return result;
	}
	VARIANT get_FieldData(short FieldId)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x7e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, FieldId);
		return result;
	}
	void put_FieldData(short FieldId, VARIANT newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_VARIANT ;
		InvokeHelper(0x7e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, FieldId, &newValue);
	}
	BOOL LoadFromMemory(VARIANT DataBuffer, VARIANT Format, VARIANT CurSelection)
	{
		BOOL result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x7f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, &DataBuffer, &Format, &CurSelection);
		return result;
	}
	VARIANT SaveToMemory(VARIANT Format, VARIANT CurSelection)
	{
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x80, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &Format, &CurSelection);
		return result;
	}
	VARIANT get_TableCellAttribute(short TableId, short Row, short Column, long Attribute)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 VTS_I4 ;
		InvokeHelper(0x81, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, TableId, Row, Column, Attribute);
		return result;
	}
	void put_TableCellAttribute(short TableId, short Row, short Column, long Attribute, VARIANT newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 VTS_I4 VTS_VARIANT ;
		InvokeHelper(0x81, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, TableId, Row, Column, Attribute, &newValue);
	}
	long Find(LPCTSTR FindWhat, VARIANT Start, VARIANT Options)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x82, DISPATCH_METHOD, VT_I4, (void*)&result, parms, FindWhat, &Start, &Options);
		return result;
	}
	short TableNext(short EnumerationNumber, short * TableId)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_PI2 ;
		InvokeHelper(0x83, DISPATCH_METHOD, VT_I2, (void*)&result, parms, EnumerationNumber, TableId);
		return result;
	}
	long get_TableCellStart(short TableId, short Row, short Column)
	{
		long result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0x84, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, TableId, Row, Column);
		return result;
	}
	long get_TableCellLength(short TableId, short Row, short Column)
	{
		long result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0x85, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, TableId, Row, Column);
		return result;
	}
	BOOL HeaderFooterActivate(long HeaderFooter)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x89, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, HeaderFooter);
		return result;
	}
	BOOL HeaderFooterSelect(long HeaderFooter)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x8a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, HeaderFooter);
		return result;
	}
	long get_HeaderFooterPosition(long HeaderFooter)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x8d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, HeaderFooter);
		return result;
	}
	void put_HeaderFooterPosition(long HeaderFooter, long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x8d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, HeaderFooter, newValue);
	}
	VARIANT get_FieldTypeData(short FieldId)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x8e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, FieldId);
		return result;
	}
	void put_FieldTypeData(short FieldId, VARIANT newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_VARIANT ;
		InvokeHelper(0x8e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, FieldId, &newValue);
	}
	BOOL FieldGoto(long FieldType, VARIANT FieldIdOrName)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_VARIANT ;
		InvokeHelper(0x8f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, FieldType, &FieldIdOrName);
		return result;
	}
	long get_FieldType(short FieldId)
	{
		long result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x90, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, FieldId);
		return result;
	}
	void put_FieldType(short FieldId, long newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_I4 ;
		InvokeHelper(0x90, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, FieldId, newValue);
	}
	BOOL ResetContents()
	{
		BOOL result;
		InvokeHelper(0x93, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	long InputPosFromPoint(long X, long Y)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x94, DISPATCH_METHOD, VT_I4, (void*)&result, parms, X, Y);
		return result;
	}
	void PrintDoc(LPCTSTR DocName, short FromPage, short ToPage, short Copies)
	{
		static BYTE parms[] = VTS_BSTR VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0x95, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DocName, FromPage, ToPage, Copies);
	}
	VARIANT get_BulletAttribute(long Attribute)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x99, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, Attribute);
		return result;
	}
	void put_BulletAttribute(long Attribute, VARIANT newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_VARIANT ;
		InvokeHelper(0x99, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, Attribute, &newValue);
	}
	VARIANT get_NumberingAttribute(long Attribute)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x9a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, Attribute);
		return result;
	}
	void put_NumberingAttribute(long Attribute, VARIANT newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_VARIANT ;
		InvokeHelper(0x9a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, Attribute, &newValue);
	}
	BOOL ListAttrDialog()
	{
		BOOL result;
		InvokeHelper(0x9c, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	VARIANT SaveToMemoryBuffer(VARIANT DataBuffer, VARIANT Format, VARIANT CurSelection)
	{
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x9d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &DataBuffer, &Format, &CurSelection);
		return result;
	}
	BOOL TableDeleteColumn()
	{
		BOOL result;
		InvokeHelper(0x9e, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL TableInsertLines(long Position, short Lines)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I2 ;
		InvokeHelper(0x9f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Position, Lines);
		return result;
	}
	BOOL TableInsertColumn(long Position)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xa0, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Position);
		return result;
	}
	long GetBaseLinePos(long Line)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xa4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Line);
		return result;
	}
	long GetCharFromLine(long Line)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xa5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Line);
		return result;
	}
	long GetLineCount()
	{
		long result;
		InvokeHelper(0xa6, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetLineFromChar(long Char)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xa7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Char);
		return result;
	}
	long GetLineFromPoint(long X, long Y)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0xa8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, X, Y);
		return result;
	}
	VARIANT GetLineRect(long Line)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xa9, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, Line);
		return result;
	}
	VARIANT GetTextExtent()
	{
		VARIANT result;
		InvokeHelper(0xaa, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	short get_CaretWidth(short Caret)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xab, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, Caret);
		return result;
	}
	void put_CaretWidth(short Caret, short newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0xab, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, Caret, newValue);
	}
	BOOL TabDialog()
	{
		BOOL result;
		InvokeHelper(0xad, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL StyleDialog()
	{
		BOOL result;
		InvokeHelper(0xae, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH XMLElements(LPCTSTR ElementName)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xb1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, ElementName);
		return result;
	}
	BOOL EnableAutomationServer()
	{
		BOOL result;
		InvokeHelper(0xb7, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL TableSplit(long Position)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xb9, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Position);
		return result;
	}
	long get_TableNestedLevel(short TableId)
	{
		long result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xba, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, TableId);
		return result;
	}
	short TableGetOuter(short TableId)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xbb, DISPATCH_METHOD, VT_I2, (void*)&result, parms, TableId);
		return result;
	}
	short TableGetOuterMost(short TableId)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xbc, DISPATCH_METHOD, VT_I2, (void*)&result, parms, TableId);
		return result;
	}
	void StartUndoAction()
	{
		InvokeHelper(0xc0, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void EndUndoAction()
	{
		InvokeHelper(0xc1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	short ObjectInsert(long ObjectType, LPCTSTR FileName, long TextPos, short Alignment, long PosX, long PosY, short ScaleX, short ScaleY, short Textflow, short DistanceL, short DistanceT, short DistanceR, short DistanceB, VARIANT KindOfObject)
	{
		short result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_I4 VTS_I2 VTS_I4 VTS_I4 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_VARIANT ;
		InvokeHelper(0xc2, DISPATCH_METHOD, VT_I2, (void*)&result, parms, ObjectType, FileName, TextPos, Alignment, PosX, PosY, ScaleX, ScaleY, Textflow, DistanceL, DistanceT, DistanceR, DistanceB, &KindOfObject);
		return result;
	}
	short TextFrameInsertAsChar(long TextPos, short Width, short Height)
	{
		short result;
		static BYTE parms[] = VTS_I4 VTS_I2 VTS_I2 ;
		InvokeHelper(0xc3, DISPATCH_METHOD, VT_I2, (void*)&result, parms, TextPos, Width, Height);
		return result;
	}
	short TextFrameInsertFixed(long PageNo, long PosX, long PosY, short Width, short Height, short Textflow, short DistL, short DistT, short DistR, short DistB)
	{
		short result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0xc4, DISPATCH_METHOD, VT_I2, (void*)&result, parms, PageNo, PosX, PosY, Width, Height, Textflow, DistL, DistT, DistR, DistB);
		return result;
	}
	short TextFrameInsert(long TextPos, short Alignment, long PosX, long PosY, short Width, short Height, short Textflow, short DistL, short DistT, short DistR, short DistB)
	{
		short result;
		static BYTE parms[] = VTS_I4 VTS_I2 VTS_I4 VTS_I4 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0xc5, DISPATCH_METHOD, VT_I2, (void*)&result, parms, TextPos, Alignment, PosX, PosY, Width, Height, Textflow, DistL, DistT, DistR, DistB);
		return result;
	}
	BOOL ObjectAttrDialog()
	{
		BOOL result;
		InvokeHelper(0xc6, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL TextFrameSelect(short TextFrameId)
	{
		BOOL result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xc7, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, TextFrameId);
		return result;
	}
	short ObjectGetSelected(short ObjectKind)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xc8, DISPATCH_METHOD, VT_I2, (void*)&result, parms, ObjectKind);
		return result;
	}
	short get_TextFrameInternalMargin(short index)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, index);
		return result;
	}
	void put_TextFrameInternalMargin(short index, short newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0xcb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, index, newValue);
	}
	short ImageInsert(LPCTSTR FileName, long TextPos, short Alignment, long PosX, long PosY, short ScaleX, short ScaleY, short Textflow, short DistanceL, short DistanceT, short DistanceR, short DistanceB)
	{
		short result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I2 VTS_I4 VTS_I4 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0xce, DISPATCH_METHOD, VT_I2, (void*)&result, parms, FileName, TextPos, Alignment, PosX, PosY, ScaleX, ScaleY, Textflow, DistanceL, DistanceT, DistanceR, DistanceB);
		return result;
	}
	short ImageInsertAsChar(LPCTSTR FileName, long TextPos, short ScaleX, short ScaleY)
	{
		short result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I2 VTS_I2 ;
		InvokeHelper(0xcf, DISPATCH_METHOD, VT_I2, (void*)&result, parms, FileName, TextPos, ScaleX, ScaleY);
		return result;
	}
	short ImageInsertFixed(LPCTSTR FileName, long PageNo, long PosX, long PosY, short ScaleX, short ScaleY, short Textflow, short DistanceL, short DistanceT, short DistanceR, short DistanceB)
	{
		short result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0xd0, DISPATCH_METHOD, VT_I2, (void*)&result, parms, FileName, PageNo, PosX, PosY, ScaleX, ScaleY, Textflow, DistanceL, DistanceT, DistanceR, DistanceB);
		return result;
	}
	BOOL FieldSetInputPos(long FieldInputPosition)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xd9, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, FieldInputPosition);
		return result;
	}
	BOOL SectionInsert(long BreakKind, long TextPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0xdb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, BreakKind, TextPos);
		return result;
	}
	BOOL SectionFormatDialog(short ActiveTab)
	{
		BOOL result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xdc, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, ActiveTab);
		return result;
	}
	BOOL get_HeaderFooterConnectedToPrevious(long HeaderFooter)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xe0, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, HeaderFooter);
		return result;
	}
	void put_HeaderFooterConnectedToPrevious(long HeaderFooter, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0xe0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, HeaderFooter, newValue);
	}
	short ObjectGetFromName(LPCTSTR ObjectName)
	{
		short result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xeb, DISPATCH_METHOD, VT_I2, (void*)&result, parms, ObjectName);
		return result;
	}
	short ObjectGetFromUserId(long ObjectUserId)
	{
		short result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xec, DISPATCH_METHOD, VT_I2, (void*)&result, parms, ObjectUserId);
		return result;
	}
	unsigned long get_DisplayColor(long index)
	{
		unsigned long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xed, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, parms, index);
		return result;
	}
	void put_DisplayColor(long index, unsigned long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_UI4 ;
		InvokeHelper(0xed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, index, newValue);
	}
	BOOL GrowFont()
	{
		BOOL result;
		InvokeHelper(0xf3, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL ShrinkFont()
	{
		BOOL result;
		InvokeHelper(0xf4, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL IncreaseIndent()
	{
		BOOL result;
		InvokeHelper(0xf5, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL DecreaseIndent()
	{
		BOOL result;
		InvokeHelper(0xf6, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	long get_MisspelledWordStart(long Number)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xf9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, Number);
		return result;
	}
	long get_MisspelledWordLength(long Number)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xfa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, Number);
		return result;
	}
	BOOL MisspelledWordDelete(long Number, LPCTSTR CorrectedText)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0xfb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Number, CorrectedText);
		return result;
	}
	VARIANT get_PageImage(long Number, long Content)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0xfd, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, Number, Content);
		return result;
	}
	BOOL TableMergeCells()
	{
		BOOL result;
		InvokeHelper(0xfe, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL TableSplitCells()
	{
		BOOL result;
		InvokeHelper(0xff, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	CString get_TableCellData(short TableId, short Row, short Column)
	{
		CString result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0x102, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, TableId, Row, Column);
		return result;
	}
	void put_TableCellData(short TableId, short Row, short Column, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 VTS_BSTR ;
		InvokeHelper(0x102, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, TableId, Row, Column, newValue);
	}
	VARIANT get_PageBorderAttribute(long Attribute)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x104, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, Attribute);
		return result;
	}
	void put_PageBorderAttribute(long Attribute, VARIANT newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_VARIANT ;
		InvokeHelper(0x104, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, Attribute, &newValue);
	}
	BOOL ObjectChangeZOrder(long ZOrder)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x105, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, ZOrder);
		return result;
	}
	short TableInsertDialog(VARIANT TableId)
	{
		short result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x107, DISPATCH_METHOD, VT_I2, (void*)&result, parms, &TableId);
		return result;
	}
	BOOL PageNumberDialog(short FieldId)
	{
		BOOL result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x108, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, FieldId);
		return result;
	}
	void PrintDialog(LPCTSTR DocName)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x10b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DocName);
	}
	BOOL TableCellSelect(short TableId, long Row, long Column)
	{
		BOOL result;
		static BYTE parms[] = VTS_I2 VTS_I4 VTS_I4 ;
		InvokeHelper(0x10c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, TableId, Row, Column);
		return result;
	}
	short TableFromSelection(long * Row, long * Column)
	{
		short result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x10d, DISPATCH_METHOD, VT_I2, (void*)&result, parms, Row, Column);
		return result;
	}
	BOOL TableDelete(short TableId)
	{
		BOOL result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x10e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, TableId);
		return result;
	}
	BOOL LocaleDialog()
	{
		BOOL result;
		InvokeHelper(0x110, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL ChangeTextDirection(long TextDirection)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x113, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, TextDirection);
		return result;
	}
	BOOL TableSelectCells(short TableId, long StartRow, long StartColumn, long EndRow, long EndColumn)
	{
		BOOL result;
		static BYTE parms[] = VTS_I2 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x115, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, TableId, StartRow, StartColumn, EndRow, EndColumn);
		return result;
	}
	long get_PageStart(long Number)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x116, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, Number);
		return result;
	}
	long get_PageLength(long Number)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x117, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, Number);
		return result;
	}
	BOOL PageSelect(long Number)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x118, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Number);
		return result;
	}
	long get_SectionStart(long Number)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x119, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, Number);
		return result;
	}
	long get_SectionLength(long Number)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x11a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, Number);
		return result;
	}
	BOOL SectionSelect(long Number)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x11b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Number);
		return result;
	}
	BOOL Paste(short Format)
	{
		BOOL result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x11d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Format);
		return result;
	}
	long Append(LPCTSTR FileName, VARIANT Offset, VARIANT Format, VARIANT AppendSettings)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x11e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, FileName, &Offset, &Format, &AppendSettings);
		return result;
	}
	BOOL AppendFromMemory(VARIANT DataBuffer, VARIANT Format, VARIANT AppendSettings)
	{
		BOOL result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x11f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, &DataBuffer, &Format, &AppendSettings);
		return result;
	}
	VARIANT GetCharRect(long Char)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x123, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, Char);
		return result;
	}
	VARIANT GetCaretRect()
	{
		VARIANT result;
		InvokeHelper(0x124, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	BOOL ParagraphSelect(long Number)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x125, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Number);
		return result;
	}
	void InsertSymbolDialog()
	{
		InvokeHelper(0x126, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
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
	unsigned long GetBackColor()
	{
		unsigned long result;
		GetProperty(DISPID_BACKCOLOR, VT_UI4, (void*)&result);
		return result;
	}
	void SetBackColor(unsigned long propVal)
	{
		SetProperty(DISPID_BACKCOLOR, VT_UI4, propVal);
	}
	unsigned long GetForeColor()
	{
		unsigned long result;
		GetProperty(DISPID_FORECOLOR, VT_UI4, (void*)&result);
		return result;
	}
	void SetForeColor(unsigned long propVal)
	{
		SetProperty(DISPID_FORECOLOR, VT_UI4, propVal);
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
	BOOL GetTabKey()
	{
		BOOL result;
		GetProperty(0x1, VT_BOOL, (void*)&result);
		return result;
	}
	void SetTabKey(BOOL propVal)
	{
		SetProperty(0x1, VT_BOOL, propVal);
	}
	BOOL GetFormatSelection()
	{
		BOOL result;
		GetProperty(0x2, VT_BOOL, (void*)&result);
		return result;
	}
	void SetFormatSelection(BOOL propVal)
	{
		SetProperty(0x2, VT_BOOL, propVal);
	}
	CString GetVTSpellDictionary()
	{
		CString result;
		GetProperty(0x3, VT_BSTR, (void*)&result);
		return result;
	}
	void SetVTSpellDictionary(CString propVal)
	{
		SetProperty(0x3, VT_BSTR, propVal);
	}
	short GetBorderStyle()
	{
		short result;
		GetProperty(0x4, VT_I2, (void*)&result);
		return result;
	}
	void SetBorderStyle(short propVal)
	{
		SetProperty(0x4, VT_I2, propVal);
	}
	short GetBackStyle()
	{
		short result;
		GetProperty(0x5, VT_I2, (void*)&result);
		return result;
	}
	void SetBackStyle(short propVal)
	{
		SetProperty(0x5, VT_I2, propVal);
	}
	short GetFontBold()
	{
		short result;
		GetProperty(0x6, VT_I2, (void*)&result);
		return result;
	}
	void SetFontBold(short propVal)
	{
		SetProperty(0x6, VT_I2, propVal);
	}
	short GetFontItalic()
	{
		short result;
		GetProperty(0x7, VT_I2, (void*)&result);
		return result;
	}
	void SetFontItalic(short propVal)
	{
		SetProperty(0x7, VT_I2, propVal);
	}
	CString GetFontName()
	{
		CString result;
		GetProperty(0x8, VT_BSTR, (void*)&result);
		return result;
	}
	void SetFontName(CString propVal)
	{
		SetProperty(0x8, VT_BSTR, propVal);
	}
	short GetFontSize()
	{
		short result;
		GetProperty(0x9, VT_I2, (void*)&result);
		return result;
	}
	void SetFontSize(short propVal)
	{
		SetProperty(0x9, VT_I2, propVal);
	}
	short GetFontStrikethru()
	{
		short result;
		GetProperty(0xa, VT_I2, (void*)&result);
		return result;
	}
	void SetFontStrikethru(short propVal)
	{
		SetProperty(0xa, VT_I2, propVal);
	}
	short GetFontUnderline()
	{
		short result;
		GetProperty(0xb, VT_I2, (void*)&result);
		return result;
	}
	void SetFontUnderline(short propVal)
	{
		SetProperty(0xb, VT_I2, propVal);
	}
	long GetPageWidth()
	{
		long result;
		GetProperty(0xc, VT_I4, (void*)&result);
		return result;
	}
	void SetPageWidth(long propVal)
	{
		SetProperty(0xc, VT_I4, propVal);
	}
	long GetPageHeight()
	{
		long result;
		GetProperty(0xd, VT_I4, (void*)&result);
		return result;
	}
	void SetPageHeight(long propVal)
	{
		SetProperty(0xd, VT_I4, propVal);
	}
	short GetScrollBars()
	{
		short result;
		GetProperty(0xe, VT_I2, (void*)&result);
		return result;
	}
	void SetScrollBars(short propVal)
	{
		SetProperty(0xe, VT_I2, propVal);
	}
	CString GetText()
	{
		CString result;
		GetProperty(0xf, VT_BSTR, (void*)&result);
		return result;
	}
	void SetText(CString propVal)
	{
		SetProperty(0xf, VT_BSTR, propVal);
	}
	short GetAlignment()
	{
		short result;
		GetProperty(0x10, VT_I2, (void*)&result);
		return result;
	}
	void SetAlignment(short propVal)
	{
		SetProperty(0x10, VT_I2, propVal);
	}
	short GetFrameDistance()
	{
		short result;
		GetProperty(0x11, VT_I2, (void*)&result);
		return result;
	}
	void SetFrameDistance(short propVal)
	{
		SetProperty(0x11, VT_I2, propVal);
	}
	short GetFrameLineWidth()
	{
		short result;
		GetProperty(0x12, VT_I2, (void*)&result);
		return result;
	}
	void SetFrameLineWidth(short propVal)
	{
		SetProperty(0x12, VT_I2, propVal);
	}
	short GetFrameStyle()
	{
		short result;
		GetProperty(0x13, VT_I2, (void*)&result);
		return result;
	}
	void SetFrameStyle(short propVal)
	{
		SetProperty(0x13, VT_I2, propVal);
	}
	long GetScrollPosX()
	{
		long result;
		GetProperty(0x14, VT_I4, (void*)&result);
		return result;
	}
	void SetScrollPosX(long propVal)
	{
		SetProperty(0x14, VT_I4, propVal);
	}
	long GetScrollPosY()
	{
		long result;
		GetProperty(0x15, VT_I4, (void*)&result);
		return result;
	}
	void SetScrollPosY(long propVal)
	{
		SetProperty(0x15, VT_I4, propVal);
	}
	long GetPageMarginL()
	{
		long result;
		GetProperty(0x16, VT_I4, (void*)&result);
		return result;
	}
	void SetPageMarginL(long propVal)
	{
		SetProperty(0x16, VT_I4, propVal);
	}
	long GetPageMarginT()
	{
		long result;
		GetProperty(0x17, VT_I4, (void*)&result);
		return result;
	}
	void SetPageMarginT(long propVal)
	{
		SetProperty(0x17, VT_I4, propVal);
	}
	long GetPageMarginR()
	{
		long result;
		GetProperty(0x18, VT_I4, (void*)&result);
		return result;
	}
	void SetPageMarginR(long propVal)
	{
		SetProperty(0x18, VT_I4, propVal);
	}
	long GetPageMarginB()
	{
		long result;
		GetProperty(0x19, VT_I4, (void*)&result);
		return result;
	}
	void SetPageMarginB(long propVal)
	{
		SetProperty(0x19, VT_I4, propVal);
	}
	long GetPrintDevice()
	{
		long result;
		GetProperty(0x1a, VT_I4, (void*)&result);
		return result;
	}
	void SetPrintDevice(long propVal)
	{
		SetProperty(0x1a, VT_I4, propVal);
	}
	BOOL GetControlChars()
	{
		BOOL result;
		GetProperty(0x1b, VT_BOOL, (void*)&result);
		return result;
	}
	void SetControlChars(BOOL propVal)
	{
		SetProperty(0x1b, VT_BOOL, propVal);
	}
	BOOL GetHideSelection()
	{
		BOOL result;
		GetProperty(0x1c, VT_BOOL, (void*)&result);
		return result;
	}
	void SetHideSelection(BOOL propVal)
	{
		SetProperty(0x1c, VT_BOOL, propVal);
	}
	BOOL GetInsertionMode()
	{
		BOOL result;
		GetProperty(0x1d, VT_BOOL, (void*)&result);
		return result;
	}
	void SetInsertionMode(BOOL propVal)
	{
		SetProperty(0x1d, VT_BOOL, propVal);
	}
	long GetSelLength()
	{
		long result;
		GetProperty(0x1e, VT_I4, (void*)&result);
		return result;
	}
	void SetSelLength(long propVal)
	{
		SetProperty(0x1e, VT_I4, propVal);
	}
	long GetSelStart()
	{
		long result;
		GetProperty(0x1f, VT_I4, (void*)&result);
		return result;
	}
	void SetSelStart(long propVal)
	{
		SetProperty(0x1f, VT_I4, propVal);
	}
	CString GetSelText()
	{
		CString result;
		GetProperty(0x20, VT_BSTR, (void*)&result);
		return result;
	}
	void SetSelText(CString propVal)
	{
		SetProperty(0x20, VT_BSTR, propVal);
	}
	BOOL GetClipChildren()
	{
		BOOL result;
		GetProperty(0x21, VT_BOOL, (void*)&result);
		return result;
	}
	void SetClipChildren(BOOL propVal)
	{
		SetProperty(0x21, VT_BOOL, propVal);
	}
	BOOL GetClipSiblings()
	{
		BOOL result;
		GetProperty(0x22, VT_BOOL, (void*)&result);
		return result;
	}
	void SetClipSiblings(BOOL propVal)
	{
		SetProperty(0x22, VT_BOOL, propVal);
	}
	short GetSizeMode()
	{
		short result;
		GetProperty(0x23, VT_I2, (void*)&result);
		return result;
	}
	void SetSizeMode(short propVal)
	{
		SetProperty(0x23, VT_I2, propVal);
	}
	short GetLanguage()
	{
		short result;
		GetProperty(0x24, VT_I2, (void*)&result);
		return result;
	}
	void SetLanguage(short propVal)
	{
		SetProperty(0x24, VT_I2, propVal);
	}
	short GetViewMode()
	{
		short result;
		GetProperty(0x25, VT_I2, (void*)&result);
		return result;
	}
	void SetViewMode(short propVal)
	{
		SetProperty(0x25, VT_I2, propVal);
	}
	BOOL GetPrintOffset()
	{
		BOOL result;
		GetProperty(0x26, VT_BOOL, (void*)&result);
		return result;
	}
	void SetPrintOffset(BOOL propVal)
	{
		SetProperty(0x26, VT_BOOL, propVal);
	}
	short GetZoomFactor()
	{
		short result;
		GetProperty(0x27, VT_I2, (void*)&result);
		return result;
	}
	void SetZoomFactor(short propVal)
	{
		SetProperty(0x27, VT_I2, propVal);
	}
	short GetFieldCurrent()
	{
		short result;
		GetProperty(0x28, VT_I2, (void*)&result);
		return result;
	}
	void SetFieldCurrent(short propVal)
	{
		SetProperty(0x28, VT_I2, propVal);
	}
	BOOL GetFieldChangeable()
	{
		BOOL result;
		GetProperty(0x29, VT_BOOL, (void*)&result);
		return result;
	}
	void SetFieldChangeable(BOOL propVal)
	{
		SetProperty(0x29, VT_BOOL, propVal);
	}
	BOOL GetFieldDeleteable()
	{
		BOOL result;
		GetProperty(0x2a, VT_BOOL, (void*)&result);
		return result;
	}
	void SetFieldDeleteable(BOOL propVal)
	{
		SetProperty(0x2a, VT_BOOL, propVal);
	}
	CString GetFieldText()
	{
		CString result;
		GetProperty(0x2b, VT_BSTR, (void*)&result);
		return result;
	}
	void SetFieldText(CString propVal)
	{
		SetProperty(0x2b, VT_BSTR, propVal);
	}
	short GetTabCurrent()
	{
		short result;
		GetProperty(0x2c, VT_I2, (void*)&result);
		return result;
	}
	void SetTabCurrent(short propVal)
	{
		SetProperty(0x2c, VT_I2, propVal);
	}
	short GetTabType()
	{
		short result;
		GetProperty(0x2d, VT_I2, (void*)&result);
		return result;
	}
	void SetTabType(short propVal)
	{
		SetProperty(0x2d, VT_I2, propVal);
	}
	long GetTabPos()
	{
		long result;
		GetProperty(0x2e, VT_I4, (void*)&result);
		return result;
	}
	void SetTabPos(long propVal)
	{
		SetProperty(0x2e, VT_I4, propVal);
	}
	short GetBaseLine()
	{
		short result;
		GetProperty(0x2f, VT_I2, (void*)&result);
		return result;
	}
	void SetBaseLine(short propVal)
	{
		SetProperty(0x2f, VT_I2, propVal);
	}
	short GetLineSpacing()
	{
		short result;
		GetProperty(0x30, VT_I2, (void*)&result);
		return result;
	}
	void SetLineSpacing(short propVal)
	{
		SetProperty(0x30, VT_I2, propVal);
	}
	short GetPrintZoom()
	{
		short result;
		GetProperty(0x31, VT_I2, (void*)&result);
		return result;
	}
	void SetPrintZoom(short propVal)
	{
		SetProperty(0x31, VT_I2, propVal);
	}
	CString GetRTFSelText()
	{
		CString result;
		GetProperty(0x32, VT_BSTR, (void*)&result);
		return result;
	}
	void SetRTFSelText(CString propVal)
	{
		SetProperty(0x32, VT_BSTR, propVal);
	}
	CString GetImageFilters()
	{
		CString result;
		GetProperty(0x33, VT_BSTR, (void*)&result);
		return result;
	}
	void SetImageFilters(CString propVal)
	{
		SetProperty(0x33, VT_BSTR, propVal);
	}
	CString GetImageFilename()
	{
		CString result;
		GetProperty(0x34, VT_BSTR, (void*)&result);
		return result;
	}
	void SetImageFilename(CString propVal)
	{
		SetProperty(0x34, VT_BSTR, propVal);
	}
	short GetLineSpacingT()
	{
		short result;
		GetProperty(0x35, VT_I2, (void*)&result);
		return result;
	}
	void SetLineSpacingT(short propVal)
	{
		SetProperty(0x35, VT_I2, propVal);
	}
	short GetObjectCurrent()
	{
		short result;
		GetProperty(0x36, VT_I2, (void*)&result);
		return result;
	}
	void SetObjectCurrent(short propVal)
	{
		SetProperty(0x36, VT_I2, propVal);
	}
	long GetStatusBarHandle()
	{
		long result;
		GetProperty(0x37, VT_I4, (void*)&result);
		return result;
	}
	void SetStatusBarHandle(long propVal)
	{
		SetProperty(0x37, VT_I4, propVal);
	}
	long GetRulerHandle()
	{
		long result;
		GetProperty(0x38, VT_I4, (void*)&result);
		return result;
	}
	void SetRulerHandle(long propVal)
	{
		SetProperty(0x38, VT_I4, propVal);
	}
	long GetButtonBarHandle()
	{
		long result;
		GetProperty(0x39, VT_I4, (void*)&result);
		return result;
	}
	void SetButtonBarHandle(long propVal)
	{
		SetProperty(0x39, VT_I4, propVal);
	}
	short GetObjectScaleX()
	{
		short result;
		GetProperty(0x3a, VT_I2, (void*)&result);
		return result;
	}
	void SetObjectScaleX(short propVal)
	{
		SetProperty(0x3a, VT_I2, propVal);
	}
	short GetObjectScaleY()
	{
		short result;
		GetProperty(0x3b, VT_I2, (void*)&result);
		return result;
	}
	void SetObjectScaleY(short propVal)
	{
		SetProperty(0x3b, VT_I2, propVal);
	}
	short GetObjectTextflow()
	{
		short result;
		GetProperty(0x3c, VT_I2, (void*)&result);
		return result;
	}
	void SetObjectTextflow(short propVal)
	{
		SetProperty(0x3c, VT_I2, propVal);
	}
	short GetObjectSizeMode()
	{
		short result;
		GetProperty(0x3d, VT_I2, (void*)&result);
		return result;
	}
	void SetObjectSizeMode(short propVal)
	{
		SetProperty(0x3d, VT_I2, propVal);
	}
	short GetImageSaveMode()
	{
		short result;
		GetProperty(0x3e, VT_I2, (void*)&result);
		return result;
	}
	void SetImageSaveMode(short propVal)
	{
		SetProperty(0x3e, VT_I2, propVal);
	}
	short GetImageDisplayMode()
	{
		short result;
		GetProperty(0x3f, VT_I2, (void*)&result);
		return result;
	}
	void SetImageDisplayMode(short propVal)
	{
		SetProperty(0x3f, VT_I2, propVal);
	}
	BOOL GetPrintColors()
	{
		BOOL result;
		GetProperty(0x40, VT_BOOL, (void*)&result);
		return result;
	}
	void SetPrintColors(BOOL propVal)
	{
		SetProperty(0x40, VT_BOOL, propVal);
	}
	short GetEditMode()
	{
		short result;
		GetProperty(0x41, VT_I2, (void*)&result);
		return result;
	}
	void SetEditMode(short propVal)
	{
		SetProperty(0x41, VT_I2, propVal);
	}
	short GetMousePointer()
	{
		short result;
		GetProperty(0x42, VT_I2, (void*)&result);
		return result;
	}
	void SetMousePointer(short propVal)
	{
		SetProperty(0x42, VT_I2, propVal);
	}
	long GetNextWindow()
	{
		long result;
		GetProperty(0x43, VT_I4, (void*)&result);
		return result;
	}
	void SetNextWindow(long propVal)
	{
		SetProperty(0x43, VT_I4, propVal);
	}
	short GetCanUndo()
	{
		short result;
		GetProperty(0x44, VT_I2, (void*)&result);
		return result;
	}
	void SetCanUndo(short propVal)
	{
		SetProperty(0x44, VT_I2, propVal);
	}
	short GetCanRedo()
	{
		short result;
		GetProperty(0x45, VT_I2, (void*)&result);
		return result;
	}
	void SetCanRedo(short propVal)
	{
		SetProperty(0x45, VT_I2, propVal);
	}
	long GetCurrentPages()
	{
		long result;
		GetProperty(0x46, VT_I4, (void*)&result);
		return result;
	}
	void SetCurrentPages(long propVal)
	{
		SetProperty(0x46, VT_I4, propVal);
	}
	long GetFieldPosX()
	{
		long result;
		GetProperty(0x47, VT_I4, (void*)&result);
		return result;
	}
	void SetFieldPosX(long propVal)
	{
		SetProperty(0x47, VT_I4, propVal);
	}
	long GetFieldPosY()
	{
		long result;
		GetProperty(0x48, VT_I4, (void*)&result);
		return result;
	}
	void SetFieldPosY(long propVal)
	{
		SetProperty(0x48, VT_I4, propVal);
	}
	long GetFieldStart()
	{
		long result;
		GetProperty(0x49, VT_I4, (void*)&result);
		return result;
	}
	void SetFieldStart(long propVal)
	{
		SetProperty(0x49, VT_I4, propVal);
	}
	long GetFieldEnd()
	{
		long result;
		GetProperty(0x4a, VT_I4, (void*)&result);
		return result;
	}
	void SetFieldEnd(long propVal)
	{
		SetProperty(0x4a, VT_I4, propVal);
	}
	short GetIndentL()
	{
		short result;
		GetProperty(0x4b, VT_I2, (void*)&result);
		return result;
	}
	void SetIndentL(short propVal)
	{
		SetProperty(0x4b, VT_I2, propVal);
	}
	short GetIndentR()
	{
		short result;
		GetProperty(0x4c, VT_I2, (void*)&result);
		return result;
	}
	void SetIndentR(short propVal)
	{
		SetProperty(0x4c, VT_I2, propVal);
	}
	short GetIndentFL()
	{
		short result;
		GetProperty(0x4d, VT_I2, (void*)&result);
		return result;
	}
	void SetIndentFL(short propVal)
	{
		SetProperty(0x4d, VT_I2, propVal);
	}
	short GetIndentT()
	{
		short result;
		GetProperty(0x4e, VT_I2, (void*)&result);
		return result;
	}
	void SetIndentT(short propVal)
	{
		SetProperty(0x4e, VT_I2, propVal);
	}
	short GetIndentB()
	{
		short result;
		GetProperty(0x4f, VT_I2, (void*)&result);
		return result;
	}
	void SetIndentB(short propVal)
	{
		SetProperty(0x4f, VT_I2, propVal);
	}
	unsigned long GetTextBkColor()
	{
		unsigned long result;
		GetProperty(0x50, VT_UI4, (void*)&result);
		return result;
	}
	void SetTextBkColor(unsigned long propVal)
	{
		SetProperty(0x50, VT_UI4, propVal);
	}
	short GetDataFormat()
	{
		short result;
		GetProperty(0x51, VT_I2, (void*)&result);
		return result;
	}
	void SetDataFormat(short propVal)
	{
		SetProperty(0x51, VT_I2, propVal);
	}
	CString GetDataText()
	{
		CString result;
		GetProperty(0x52, VT_BSTR, (void*)&result);
		return result;
	}
	void SetDataText(CString propVal)
	{
		SetProperty(0x52, VT_BSTR, propVal);
	}
	short GetViewSection()
	{
		short result;
		GetProperty(0x69, VT_I2, (void*)&result);
		return result;
	}
	void SetViewSection(short propVal)
	{
		SetProperty(0x69, VT_I2, propVal);
	}
	CString GetViewImagePath()
	{
		CString result;
		GetProperty(0x6a, VT_BSTR, (void*)&result);
		return result;
	}
	void SetViewImagePath(CString propVal)
	{
		SetProperty(0x6a, VT_BSTR, propVal);
	}
	BOOL GetAutoExpand()
	{
		BOOL result;
		GetProperty(0x6b, VT_BOOL, (void*)&result);
		return result;
	}
	void SetAutoExpand(BOOL propVal)
	{
		SetProperty(0x6b, VT_BOOL, propVal);
	}
	BOOL GetTableCanInsert()
	{
		BOOL result;
		GetProperty(0x6e, VT_BOOL, (void*)&result);
		return result;
	}
	void SetTableCanInsert(BOOL propVal)
	{
		SetProperty(0x6e, VT_BOOL, propVal);
	}
	BOOL GetTableCanDeleteLines()
	{
		BOOL result;
		GetProperty(0x6f, VT_BOOL, (void*)&result);
		return result;
	}
	void SetTableCanDeleteLines(BOOL propVal)
	{
		SetProperty(0x6f, VT_BOOL, propVal);
	}
	BOOL GetEnableHyperlinks()
	{
		BOOL result;
		GetProperty(0x71, VT_BOOL, (void*)&result);
		return result;
	}
	void SetEnableHyperlinks(BOOL propVal)
	{
		SetProperty(0x71, VT_BOOL, propVal);
	}
	BOOL GetTableGridLines()
	{
		BOOL result;
		GetProperty(0x73, VT_BOOL, (void*)&result);
		return result;
	}
	void SetTableGridLines(BOOL propVal)
	{
		SetProperty(0x73, VT_BOOL, propVal);
	}
	BOOL GetTableCanChangeAttr()
	{
		BOOL result;
		GetProperty(0x74, VT_BOOL, (void*)&result);
		return result;
	}
	void SetTableCanChangeAttr(BOOL propVal)
	{
		SetProperty(0x74, VT_BOOL, propVal);
	}
	short GetTableAtInputPos()
	{
		short result;
		GetProperty(0x78, VT_I2, (void*)&result);
		return result;
	}
	void SetTableAtInputPos(short propVal)
	{
		SetProperty(0x78, VT_I2, propVal);
	}
	short GetTableColAtInputPos()
	{
		short result;
		GetProperty(0x79, VT_I2, (void*)&result);
		return result;
	}
	void SetTableColAtInputPos(short propVal)
	{
		SetProperty(0x79, VT_I2, propVal);
	}
	short GetTableRowAtInputPos()
	{
		short result;
		GetProperty(0x7a, VT_I2, (void*)&result);
		return result;
	}
	void SetTableRowAtInputPos(short propVal)
	{
		SetProperty(0x7a, VT_I2, propVal);
	}
	short GetFontUnderlineStyle()
	{
		short result;
		GetProperty(0x7b, VT_I2, (void*)&result);
		return result;
	}
	void SetFontUnderlineStyle(short propVal)
	{
		SetProperty(0x7b, VT_I2, propVal);
	}
	short GetDataTextFormat()
	{
		short result;
		GetProperty(0x86, VT_I2, (void*)&result);
		return result;
	}
	void SetDataTextFormat(short propVal)
	{
		SetProperty(0x86, VT_I2, propVal);
	}
	CString GetResourceFile()
	{
		CString result;
		GetProperty(0x87, VT_BSTR, (void*)&result);
		return result;
	}
	void SetResourceFile(CString propVal)
	{
		SetProperty(0x87, VT_BSTR, propVal);
	}
	VARIANT GetCurrentInputPosition()
	{
		VARIANT result;
		GetProperty(0x88, VT_VARIANT, (void*)&result);
		return result;
	}
	void SetCurrentInputPosition(VARIANT propVal)
	{
		SetProperty(0x88, VT_VARIANT, propVal);
	}
	long GetHeaderFooterStyle()
	{
		long result;
		GetProperty(0x8b, VT_I4, (void*)&result);
		return result;
	}
	void SetHeaderFooterStyle(long propVal)
	{
		SetProperty(0x8b, VT_I4, propVal);
	}
	long GetHeaderFooter()
	{
		long result;
		GetProperty(0x8c, VT_I4, (void*)&result);
		return result;
	}
	void SetHeaderFooter(long propVal)
	{
		SetProperty(0x8c, VT_I4, propVal);
	}
	short GetFieldAtInputPos()
	{
		short result;
		GetProperty(0x91, VT_I2, (void*)&result);
		return result;
	}
	void SetFieldAtInputPos(short propVal)
	{
		SetProperty(0x91, VT_I2, propVal);
	}
	LPDISPATCH GetObjectItem()
	{
		LPDISPATCH result;
		GetProperty(0x92, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetObjectItem(LPDISPATCH propVal)
	{
		SetProperty(0x92, VT_DISPATCH, propVal);
	}
	BOOL GetLockWindowUpdate()
	{
		BOOL result;
		GetProperty(0x96, VT_BOOL, (void*)&result);
		return result;
	}
	void SetLockWindowUpdate(BOOL propVal)
	{
		SetProperty(0x96, VT_BOOL, propVal);
	}
	BOOL GetCanCopy()
	{
		BOOL result;
		GetProperty(0x97, VT_BOOL, (void*)&result);
		return result;
	}
	void SetCanCopy(BOOL propVal)
	{
		SetProperty(0x97, VT_BOOL, propVal);
	}
	BOOL GetCanPaste()
	{
		BOOL result;
		GetProperty(0x98, VT_BOOL, (void*)&result);
		return result;
	}
	void SetCanPaste(BOOL propVal)
	{
		SetProperty(0x98, VT_BOOL, propVal);
	}
	long GetListType()
	{
		long result;
		GetProperty(0x9b, VT_I4, (void*)&result);
		return result;
	}
	void SetListType(long propVal)
	{
		SetProperty(0x9b, VT_I4, propVal);
	}
	BOOL GetTableCanDeleteColumn()
	{
		BOOL result;
		GetProperty(0xa1, VT_BOOL, (void*)&result);
		return result;
	}
	void SetTableCanDeleteColumn(BOOL propVal)
	{
		SetProperty(0xa1, VT_BOOL, propVal);
	}
	BOOL GetTableCanInsertColumn()
	{
		BOOL result;
		GetProperty(0xa2, VT_BOOL, (void*)&result);
		return result;
	}
	void SetTableCanInsertColumn(BOOL propVal)
	{
		SetProperty(0xa2, VT_BOOL, propVal);
	}
	BOOL GetTableCanInsertLines()
	{
		BOOL result;
		GetProperty(0xa3, VT_BOOL, (void*)&result);
		return result;
	}
	void SetTableCanInsertLines(BOOL propVal)
	{
		SetProperty(0xa3, VT_BOOL, propVal);
	}
	VARIANT GetDevice()
	{
		VARIANT result;
		GetProperty(0xac, VT_VARIANT, (void*)&result);
		return result;
	}
	void SetDevice(VARIANT propVal)
	{
		SetProperty(0xac, VT_VARIANT, propVal);
	}
	CString GetStyleCurrent()
	{
		CString result;
		GetProperty(0xaf, VT_BSTR, (void*)&result);
		return result;
	}
	void SetStyleCurrent(CString propVal)
	{
		SetProperty(0xaf, VT_BSTR, propVal);
	}
	short GetWordWrapMode()
	{
		short result;
		GetProperty(0xb0, VT_I2, (void*)&result);
		return result;
	}
	void SetWordWrapMode(short propVal)
	{
		SetProperty(0xb0, VT_I2, propVal);
	}
	LPDISPATCH GetStyles()
	{
		LPDISPATCH result;
		GetProperty(0xb2, VT_DISPATCH, (void*)&result);
		return result;
	}
	void SetStyles(LPDISPATCH propVal)
	{
		SetProperty(0xb2, VT_DISPATCH, propVal);
	}
	short GetXMLEditMode()
	{
		short result;
		GetProperty(0xb3, VT_I2, (void*)&result);
		return result;
	}
	void SetXMLEditMode(short propVal)
	{
		SetProperty(0xb3, VT_I2, propVal);
	}
	CString GetImageExportFilters()
	{
		CString result;
		GetProperty(0xb4, VT_BSTR, (void*)&result);
		return result;
	}
	void SetImageExportFilters(CString propVal)
	{
		SetProperty(0xb4, VT_BSTR, propVal);
	}
	short GetImageExportFormat()
	{
		short result;
		GetProperty(0xb5, VT_I2, (void*)&result);
		return result;
	}
	void SetImageExportFormat(short propVal)
	{
		SetProperty(0xb5, VT_I2, propVal);
	}
	CString GetImageExportFilename()
	{
		CString result;
		GetProperty(0xb6, VT_BSTR, (void*)&result);
		return result;
	}
	void SetImageExportFilename(CString propVal)
	{
		SetProperty(0xb6, VT_BSTR, propVal);
	}
	BOOL GetTableCanSplit()
	{
		BOOL result;
		GetProperty(0xb8, VT_BOOL, (void*)&result);
		return result;
	}
	void SetTableCanSplit(BOOL propVal)
	{
		SetProperty(0xb8, VT_BOOL, propVal);
	}
	short GetImageExportCompressionQuality()
	{
		short result;
		GetProperty(0xbd, VT_I2, (void*)&result);
		return result;
	}
	void SetImageExportCompressionQuality(short propVal)
	{
		SetProperty(0xbd, VT_I2, propVal);
	}
	short GetImageExportMaxResolution()
	{
		short result;
		GetProperty(0xbe, VT_I2, (void*)&result);
		return result;
	}
	void SetImageExportMaxResolution(short propVal)
	{
		SetProperty(0xbe, VT_I2, propVal);
	}
	BOOL GetAllowUndo()
	{
		BOOL result;
		GetProperty(0xbf, VT_BOOL, (void*)&result);
		return result;
	}
	void SetAllowUndo(BOOL propVal)
	{
		SetProperty(0xbf, VT_BOOL, propVal);
	}
	unsigned long GetTextFrameBackColor()
	{
		unsigned long result;
		GetProperty(0xc9, VT_UI4, (void*)&result);
		return result;
	}
	void SetTextFrameBackColor(unsigned long propVal)
	{
		SetProperty(0xc9, VT_UI4, propVal);
	}
	short GetTextFrameBorderWidth()
	{
		short result;
		GetProperty(0xca, VT_I2, (void*)&result);
		return result;
	}
	void SetTextFrameBorderWidth(short propVal)
	{
		SetProperty(0xca, VT_I2, propVal);
	}
	short GetObjectWidth()
	{
		short result;
		GetProperty(0xcc, VT_I2, (void*)&result);
		return result;
	}
	void SetObjectWidth(short propVal)
	{
		SetProperty(0xcc, VT_I2, propVal);
	}
	short GetObjectHeight()
	{
		short result;
		GetProperty(0xcd, VT_I2, (void*)&result);
		return result;
	}
	void SetObjectHeight(short propVal)
	{
		SetProperty(0xcd, VT_I2, propVal);
	}
	BOOL GetTextFrameMarkerLines()
	{
		BOOL result;
		GetProperty(0xd1, VT_BOOL, (void*)&result);
		return result;
	}
	void SetTextFrameMarkerLines(BOOL propVal)
	{
		SetProperty(0xd1, VT_BOOL, propVal);
	}
	short GetHeaderFooterAtInputPos()
	{
		short result;
		GetProperty(0xd2, VT_I2, (void*)&result);
		return result;
	}
	void SetHeaderFooterAtInputPos(short propVal)
	{
		SetProperty(0xd2, VT_I2, propVal);
	}
	long GetVerticalRulerHandle()
	{
		long result;
		GetProperty(0xd3, VT_I4, (void*)&result);
		return result;
	}
	void SetVerticalRulerHandle(long propVal)
	{
		SetProperty(0xd3, VT_I4, propVal);
	}
	BOOL GetKeepLinesTogether()
	{
		BOOL result;
		GetProperty(0xd4, VT_BOOL, (void*)&result);
		return result;
	}
	void SetKeepLinesTogether(BOOL propVal)
	{
		SetProperty(0xd4, VT_BOOL, propVal);
	}
	BOOL GetKeepWithNext()
	{
		BOOL result;
		GetProperty(0xd5, VT_BOOL, (void*)&result);
		return result;
	}
	void SetKeepWithNext(BOOL propVal)
	{
		SetProperty(0xd5, VT_BOOL, propVal);
	}
	BOOL GetPageBreakBefore()
	{
		BOOL result;
		GetProperty(0xd6, VT_BOOL, (void*)&result);
		return result;
	}
	void SetPageBreakBefore(BOOL propVal)
	{
		SetProperty(0xd6, VT_BOOL, propVal);
	}
	short GetWidowOrphanLines()
	{
		short result;
		GetProperty(0xd7, VT_I2, (void*)&result);
		return result;
	}
	void SetWidowOrphanLines(short propVal)
	{
		SetProperty(0xd7, VT_I2, propVal);
	}
	BOOL GetFieldLinkTargetMarkers()
	{
		BOOL result;
		GetProperty(0xd8, VT_BOOL, (void*)&result);
		return result;
	}
	void SetFieldLinkTargetMarkers(BOOL propVal)
	{
		SetProperty(0xd8, VT_BOOL, propVal);
	}
	short GetSectionCurrent()
	{
		short result;
		GetProperty(0xda, VT_I2, (void*)&result);
		return result;
	}
	void SetSectionCurrent(short propVal)
	{
		SetProperty(0xda, VT_I2, propVal);
	}
	short GetSectionAtInputPos()
	{
		short result;
		GetProperty(0xdd, VT_I2, (void*)&result);
		return result;
	}
	void SetSectionAtInputPos(short propVal)
	{
		SetProperty(0xdd, VT_I2, propVal);
	}
	short GetSectionCount()
	{
		short result;
		GetProperty(0xde, VT_I2, (void*)&result);
		return result;
	}
	void SetSectionCount(short propVal)
	{
		SetProperty(0xde, VT_I2, propVal);
	}
	long GetSectionBreakKind()
	{
		long result;
		GetProperty(0xdf, VT_I4, (void*)&result);
		return result;
	}
	void SetSectionBreakKind(long propVal)
	{
		SetProperty(0xdf, VT_I4, propVal);
	}
	short GetPageOrientation()
	{
		short result;
		GetProperty(0xe1, VT_I2, (void*)&result);
		return result;
	}
	void SetPageOrientation(short propVal)
	{
		SetProperty(0xe1, VT_I2, propVal);
	}
	long GetPageViewStyle()
	{
		long result;
		GetProperty(0xe2, VT_I4, (void*)&result);
		return result;
	}
	void SetPageViewStyle(long propVal)
	{
		SetProperty(0xe2, VT_I4, propVal);
	}
	VARIANT GetColumnWidthsAndDistances()
	{
		VARIANT result;
		GetProperty(0xe3, VT_VARIANT, (void*)&result);
		return result;
	}
	void SetColumnWidthsAndDistances(VARIANT propVal)
	{
		SetProperty(0xe3, VT_VARIANT, propVal);
	}
	short GetColumns()
	{
		short result;
		GetProperty(0xe4, VT_I2, (void*)&result);
		return result;
	}
	void SetColumns(short propVal)
	{
		SetProperty(0xe4, VT_I2, propVal);
	}
	short GetColumnDistance()
	{
		short result;
		GetProperty(0xe5, VT_I2, (void*)&result);
		return result;
	}
	void SetColumnDistance(short propVal)
	{
		SetProperty(0xe5, VT_I2, propVal);
	}
	unsigned long GetColumnLineColor()
	{
		unsigned long result;
		GetProperty(0xe6, VT_UI4, (void*)&result);
		return result;
	}
	void SetColumnLineColor(unsigned long propVal)
	{
		SetProperty(0xe6, VT_UI4, propVal);
	}
	short GetColumnLineWidth()
	{
		short result;
		GetProperty(0xe7, VT_I2, (void*)&result);
		return result;
	}
	void SetColumnLineWidth(short propVal)
	{
		SetProperty(0xe7, VT_I2, propVal);
	}
	short GetFontSettings()
	{
		short result;
		GetProperty(0xe8, VT_I2, (void*)&result);
		return result;
	}
	void SetFontSettings(short propVal)
	{
		SetProperty(0xe8, VT_I2, propVal);
	}
	CString GetObjectName()
	{
		CString result;
		GetProperty(0xe9, VT_BSTR, (void*)&result);
		return result;
	}
	void SetObjectName(CString propVal)
	{
		SetProperty(0xe9, VT_BSTR, propVal);
	}
	long GetObjectUserId()
	{
		long result;
		GetProperty(0xea, VT_I4, (void*)&result);
		return result;
	}
	void SetObjectUserId(long propVal)
	{
		SetProperty(0xea, VT_I4, propVal);
	}
	long GetObjectInsertionMode()
	{
		long result;
		GetProperty(0xee, VT_I4, (void*)&result);
		return result;
	}
	void SetObjectInsertionMode(long propVal)
	{
		SetProperty(0xee, VT_I4, propVal);
	}
	long GetObjectPosX()
	{
		long result;
		GetProperty(0xef, VT_I4, (void*)&result);
		return result;
	}
	void SetObjectPosX(long propVal)
	{
		SetProperty(0xef, VT_I4, propVal);
	}
	long GetObjectPosY()
	{
		long result;
		GetProperty(0xf0, VT_I4, (void*)&result);
		return result;
	}
	void SetObjectPosY(long propVal)
	{
		SetProperty(0xf0, VT_I4, propVal);
	}
	BOOL GetAllowDrag()
	{
		BOOL result;
		GetProperty(0xf1, VT_BOOL, (void*)&result);
		return result;
	}
	void SetAllowDrag(BOOL propVal)
	{
		SetProperty(0xf1, VT_BOOL, propVal);
	}
	BOOL GetAllowDrop()
	{
		BOOL result;
		GetProperty(0xf2, VT_BOOL, (void*)&result);
		return result;
	}
	void SetAllowDrop(BOOL propVal)
	{
		SetProperty(0xf2, VT_BOOL, propVal);
	}
	BOOL GetEnableSpellChecking()
	{
		BOOL result;
		GetProperty(0xf7, VT_BOOL, (void*)&result);
		return result;
	}
	void SetEnableSpellChecking(BOOL propVal)
	{
		SetProperty(0xf7, VT_BOOL, propVal);
	}
	long GetMisspelledWords()
	{
		long result;
		GetProperty(0xf8, VT_I4, (void*)&result);
		return result;
	}
	void SetMisspelledWords(long propVal)
	{
		SetProperty(0xf8, VT_I4, propVal);
	}
	long GetMisspelledWordAtInputPos()
	{
		long result;
		GetProperty(0xfc, VT_I4, (void*)&result);
		return result;
	}
	void SetMisspelledWordAtInputPos(long propVal)
	{
		SetProperty(0xfc, VT_I4, propVal);
	}
	BOOL GetTableCanMergeCells()
	{
		BOOL result;
		GetProperty(0x100, VT_BOOL, (void*)&result);
		return result;
	}
	void SetTableCanMergeCells(BOOL propVal)
	{
		SetProperty(0x100, VT_BOOL, propVal);
	}
	BOOL GetTableCanSplitCells()
	{
		BOOL result;
		GetProperty(0x101, VT_BOOL, (void*)&result);
		return result;
	}
	void SetTableCanSplitCells(BOOL propVal)
	{
		SetProperty(0x101, VT_BOOL, propVal);
	}
	short GetSelectionViewMode()
	{
		short result;
		GetProperty(0x103, VT_I2, (void*)&result);
		return result;
	}
	void SetSelectionViewMode(short propVal)
	{
		SetProperty(0x103, VT_I2, propVal);
	}
	short GetObjectTransparency()
	{
		short result;
		GetProperty(0x106, VT_I2, (void*)&result);
		return result;
	}
	void SetObjectTransparency(short propVal)
	{
		SetProperty(0x106, VT_I2, propVal);
	}
	short GetSectionRestartPageNumbering()
	{
		short result;
		GetProperty(0x109, VT_I2, (void*)&result);
		return result;
	}
	void SetSectionRestartPageNumbering(short propVal)
	{
		SetProperty(0x109, VT_I2, propVal);
	}
	long GetPermanentControlChars()
	{
		long result;
		GetProperty(0x10a, VT_I4, (void*)&result);
		return result;
	}
	void SetPermanentControlChars(long propVal)
	{
		SetProperty(0x10a, VT_I4, propVal);
	}
	BOOL GetRightToLeft()
	{
		BOOL result;
		GetProperty(0x10f, VT_BOOL, (void*)&result);
		return result;
	}
	void SetRightToLeft(BOOL propVal)
	{
		SetProperty(0x10f, VT_BOOL, propVal);
	}
	long GetTextDirection()
	{
		long result;
		GetProperty(0x111, VT_I4, (void*)&result);
		return result;
	}
	void SetTextDirection(long propVal)
	{
		SetProperty(0x111, VT_I4, propVal);
	}
	long GetLocale()
	{
		long result;
		GetProperty(0x112, VT_I4, (void*)&result);
		return result;
	}
	void SetLocale(long propVal)
	{
		SetProperty(0x112, VT_I4, propVal);
	}
	long GetJustification()
	{
		long result;
		GetProperty(0x114, VT_I4, (void*)&result);
		return result;
	}
	void SetJustification(long propVal)
	{
		SetProperty(0x114, VT_I4, propVal);
	}
	VARIANT GetClipboardFormats()
	{
		VARIANT result;
		GetProperty(0x11c, VT_VARIANT, (void*)&result);
		return result;
	}
	void SetClipboardFormats(VARIANT propVal)
	{
		SetProperty(0x11c, VT_VARIANT, propVal);
	}
	short GetPageCount()
	{
		short result;
		GetProperty(0x120, VT_I2, (void*)&result);
		return result;
	}
	void SetPageCount(short propVal)
	{
		SetProperty(0x120, VT_I2, propVal);
	}
	short GetParagraphCount()
	{
		short result;
		GetProperty(0x121, VT_I2, (void*)&result);
		return result;
	}
	void SetParagraphCount(short propVal)
	{
		SetProperty(0x121, VT_I2, propVal);
	}
	CString GetSupportedFonts()
	{
		CString result;
		GetProperty(0x122, VT_BSTR, (void*)&result);
		return result;
	}
	void SetSupportedFonts(CString propVal)
	{
		SetProperty(0x122, VT_BSTR, propVal);
	}
};

class CTXTextControl23Ex : public CTXTextControl23
{

	DECLARE_DYNCREATE(CTXTextControl23Ex)

public:

	CTXTextControl23Ex();

	CString GetHTMLSelText();

	BOOL IsAutoChanging();

	void RtfInsertNewTable(CWnd* pParent);
	void RtfSelectedTextMakeUpper();
	void RtfSelectedTextMakeNormal();
	void RtfSelectedTextMakeLower();
	void RtfSetFontProperties(); //Julio - BUG 4392 Edicao de texto
	BOOL RtfSetImageProperties(); //Julio - BUG 4392 Edicao de texto	

protected:

	DECLARE_MESSAGE_MAP()

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	
	// afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);

private: 

	BOOL m_bAutoChanging;
};
