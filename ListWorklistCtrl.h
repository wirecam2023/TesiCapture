#pragma once
#include "ListSortableCtrl.h"

class CListWorklistCtrl : public CListSortableCtrl
{
public:
	CListWorklistCtrl(void);
	~CListWorklistCtrl(void);
	
	void SetNotePiePagina(CString strNote);	
	void Print();

protected:	
	DECLARE_MESSAGE_MAP()

	virtual void OnBeginPrinting(CDC *pDC, CPrintInfo *pInfo);
    virtual void OnPrint(CDC *pDC, CPrintInfo *pInfo);
	virtual void OnEndPrinting(CDC *pDC, CPrintInfo *pInfo);

private:
	void CalculateColumnsWidthForPrint(int nRectWidth);
	void PrintColumnHeaders(CDC *pDC, CFont* pFontBold, int nRectHeight);
	void PrintFooter(CDC *pDC, CPrintInfo *pInfo, CFont* pFontBold, int nRectHeight, int nPagina);

	//
	CString m_sNotePiePagina;

	//

	int m_iColumnWidthForPrinter[255];
};