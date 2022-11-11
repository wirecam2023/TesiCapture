#pragma once

#include "RGLOCX.h"

class CRGL : public CDialog
{
	DECLARE_DYNAMIC(CRGL)

public:
	CRGL(CWnd* pParent = NULL);
	virtual ~CRGL();

	enum { IDD = IDD_RGL };

	BOOL Create();

	CRGLOCX* Get() { return &m_rgl; }

	void ExecutePrint(CString strFileRgf, BOOL bLandscape = FALSE, CString strPrinter = "");
	void ExecutePrint(CStringList* pListFiles, CString strPrinter = "");

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()

	CRGLOCX m_rgl;

};