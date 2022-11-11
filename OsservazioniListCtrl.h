#ifndef _OSSERVAZIONILISTCTRL_H_
	#define _OSSERVAZIONILISTCTRL_H_

class COsservazioniListCtrl : public CListCtrl
{

public:

	COsservazioniListCtrl();
	~COsservazioniListCtrl();

	int InsertColumn(int nCol, LPCTSTR lpszColumnHeading, int nFormat, int nWidth = LVSCW_AUTOSIZE);
	void SetNotePiePagina(CString strNote);

	void Export(CString strTitle);
    void Print();

protected:

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

#endif /* _OSSERVAZIONILISTCTRL_H_ */