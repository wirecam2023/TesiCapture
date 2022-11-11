#pragma once

class CTXButtonBar23 : public CWnd
{

protected:

	DECLARE_DYNCREATE(CTXButtonBar23)

public:

	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x67D06A09, 0x8469, 0x11E5, { 0xA5, 0xC5, 0x0, 0x13, 0xD3, 0x50, 0x66, 0x7C } };
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
		txTableCellVertAlign = 13
	}TableCellAttributeConstants;
	enum
	{
		txTableInsertInFront = 1,
		txTableInsertAfter = 2
	}TableInsertConstants;
	enum
	{
		txFlat = 0,
		tx3D = 1,
		txXP = 2
	}AppearanceStyles;
	enum
	{
		txHeader = 1,
		txFirstHeader = 2,
		txFooter = 4,
		txFirstFooter = 8,
		txMainText = 16
	}HeaderFooterConstants;
	enum
	{
		txMouseClick = 1,
		txNoDblClk = 2,
		txSolidFrame = 4,
		txUnframed = 8
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
		txFieldTopic = 6
	}FieldTypeConstants;
	enum
	{
		txListNone = 1,
		txListBulleted = 2,
		txListNumbered = 4
	}ListTypeConstants;
	enum
	{
		txBulletChar = 0,
		txBulletFormatChar = 1,
		txBulletLevel = 2,
		txBulletPos = 3,
		txBulletSize = 4,
		txBulletTextPos = 5
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
		txNumberingTextPos = 9
	}NumberingConstants;

	unsigned long get_DisplayColor(long index)
	{
		unsigned long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, parms, index);
		return result;
	}
	void put_DisplayColor(long index, unsigned long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_UI4 ;
		InvokeHelper(0x1b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, index, newValue);
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
	short GetLanguage()
	{
		short result;
		GetProperty(0x1, VT_I2, (void*)&result);
		return result;
	}
	void SetLanguage(short propVal)
	{
		SetProperty(0x1, VT_I2, propVal);
	}
	CString GetResourceFile()
	{
		CString result;
		GetProperty(0x2, VT_BSTR, (void*)&result);
		return result;
	}
	void SetResourceFile(CString propVal)
	{
		SetProperty(0x2, VT_BSTR, propVal);
	}
	long GetStyle()
	{
		long result;
		GetProperty(0x3, VT_I4, (void*)&result);
		return result;
	}
	void SetStyle(long propVal)
	{
		SetProperty(0x3, VT_I4, propVal);
	}
	long GetAppearance()
	{
		long result;
		GetProperty(0x4, VT_I4, (void*)&result);
		return result;
	}
	void SetAppearance(long propVal)
	{
		SetProperty(0x4, VT_I4, propVal);
	}
	short GetPosFontName()
	{
		short result;
		GetProperty(0x5, VT_I2, (void*)&result);
		return result;
	}
	void SetPosFontName(short propVal)
	{
		SetProperty(0x5, VT_I2, propVal);
	}
	short GetPosFontSize()
	{
		short result;
		GetProperty(0x6, VT_I2, (void*)&result);
		return result;
	}
	void SetPosFontSize(short propVal)
	{
		SetProperty(0x6, VT_I2, propVal);
	}
	short GetPosFontBold()
	{
		short result;
		GetProperty(0x7, VT_I2, (void*)&result);
		return result;
	}
	void SetPosFontBold(short propVal)
	{
		SetProperty(0x7, VT_I2, propVal);
	}
	short GetPosFontItalic()
	{
		short result;
		GetProperty(0x8, VT_I2, (void*)&result);
		return result;
	}
	void SetPosFontItalic(short propVal)
	{
		SetProperty(0x8, VT_I2, propVal);
	}
	short GetPosFontUnderline()
	{
		short result;
		GetProperty(0x9, VT_I2, (void*)&result);
		return result;
	}
	void SetPosFontUnderline(short propVal)
	{
		SetProperty(0x9, VT_I2, propVal);
	}
	short GetPosParaLeft()
	{
		short result;
		GetProperty(0xa, VT_I2, (void*)&result);
		return result;
	}
	void SetPosParaLeft(short propVal)
	{
		SetProperty(0xa, VT_I2, propVal);
	}
	short GetPosParaRight()
	{
		short result;
		GetProperty(0xb, VT_I2, (void*)&result);
		return result;
	}
	void SetPosParaRight(short propVal)
	{
		SetProperty(0xb, VT_I2, propVal);
	}
	short GetPosParaCentered()
	{
		short result;
		GetProperty(0xc, VT_I2, (void*)&result);
		return result;
	}
	void SetPosParaCentered(short propVal)
	{
		SetProperty(0xc, VT_I2, propVal);
	}
	short GetPosParaJustified()
	{
		short result;
		GetProperty(0xd, VT_I2, (void*)&result);
		return result;
	}
	void SetPosParaJustified(short propVal)
	{
		SetProperty(0xd, VT_I2, propVal);
	}
	short GetPosListBulleted()
	{
		short result;
		GetProperty(0xe, VT_I2, (void*)&result);
		return result;
	}
	void SetPosListBulleted(short propVal)
	{
		SetProperty(0xe, VT_I2, propVal);
	}
	short GetPosListNumbered()
	{
		short result;
		GetProperty(0xf, VT_I2, (void*)&result);
		return result;
	}
	void SetPosListNumbered(short propVal)
	{
		SetProperty(0xf, VT_I2, propVal);
	}
	short GetPosZoom()
	{
		short result;
		GetProperty(0x10, VT_I2, (void*)&result);
		return result;
	}
	void SetPosZoom(short propVal)
	{
		SetProperty(0x10, VT_I2, propVal);
	}
	short GetPosControlChars()
	{
		short result;
		GetProperty(0x11, VT_I2, (void*)&result);
		return result;
	}
	void SetPosControlChars(short propVal)
	{
		SetProperty(0x11, VT_I2, propVal);
	}
	short GetPosTabLeft()
	{
		short result;
		GetProperty(0x12, VT_I2, (void*)&result);
		return result;
	}
	void SetPosTabLeft(short propVal)
	{
		SetProperty(0x12, VT_I2, propVal);
	}
	short GetPosTabRight()
	{
		short result;
		GetProperty(0x13, VT_I2, (void*)&result);
		return result;
	}
	void SetPosTabRight(short propVal)
	{
		SetProperty(0x13, VT_I2, propVal);
	}
	short GetPosTabCentered()
	{
		short result;
		GetProperty(0x14, VT_I2, (void*)&result);
		return result;
	}
	void SetPosTabCentered(short propVal)
	{
		SetProperty(0x14, VT_I2, propVal);
	}
	short GetPosTabDecimal()
	{
		short result;
		GetProperty(0x15, VT_I2, (void*)&result);
		return result;
	}
	void SetPosTabDecimal(short propVal)
	{
		SetProperty(0x15, VT_I2, propVal);
	}
	short GetPosStyle()
	{
		short result;
		GetProperty(0x16, VT_I2, (void*)&result);
		return result;
	}
	void SetPosStyle(short propVal)
	{
		SetProperty(0x16, VT_I2, propVal);
	}
	short GetPosXMLAdd()
	{
		short result;
		GetProperty(0x17, VT_I2, (void*)&result);
		return result;
	}
	void SetPosXMLAdd(short propVal)
	{
		SetProperty(0x17, VT_I2, propVal);
	}
	short GetPosXMLRemove()
	{
		short result;
		GetProperty(0x18, VT_I2, (void*)&result);
		return result;
	}
	void SetPosXMLRemove(short propVal)
	{
		SetProperty(0x18, VT_I2, propVal);
	}
};

class CTXButtonBar23Ex : public CTXButtonBar23
{

	DECLARE_DYNCREATE(CTXButtonBar23Ex)

public:

	CTXButtonBar23Ex();

protected:

	DECLARE_MESSAGE_MAP()

	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

};
