#pragma once

class CTXRuler23 : public CWnd
{

protected:

	DECLARE_DYNCREATE(CTXRuler23)

public:

	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x67D06A0D, 0x8469, 0x11E5, { 0xA5, 0xC5, 0x0, 0x13, 0xD3, 0x50, 0x66, 0x7C } };
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
		InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, parms, index);
		return result;
	}
	void put_DisplayColor(long index, unsigned long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_UI4 ;
		InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, index, newValue);
	}
	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

};
