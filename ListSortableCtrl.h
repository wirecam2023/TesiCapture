#pragma once

class CListSortableCtrl : public CListCtrlLocalize
{

public:

	CListSortableCtrl(void);
	~CListSortableCtrl(void);

	enum ColumnType
	{
		type_string,
		type_number,
		type_date,
		type_date_time
	};
	enum SortType
	{
		sort_nothing,
		sort_ascending,
		sort_descending
	};

	int InsertColumn(int nCol, LPCTSTR lpszColumnHeading, ColumnType type = type_string, int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1);
	BOOL DeleteColumn(int nCol);

	void Export(CString strTitle);
	void Print();

	void SetSortColumn(int iCol);
	int GetColumnsCount();			// Marvel Carvalho - BUG 4308 Esquemas Anatomicos Fleury
	void SetItemFocus(int iRow);	// Marvel Carvalho - BUG 4308 Esquemas Anatomicos Fleury
	void SortColumn(int iCol);		//Gabriel BUG 6225 - Lista DO FIX

protected:

	afx_msg virtual void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();

	DECLARE_MESSAGE_MAP()

	virtual void OnBeginPrinting(CDC *pDC, CPrintInfo *pInfo);
	virtual void OnPrint(CDC *pDC, CPrintInfo *pInfo);
	virtual void OnEndPrinting(CDC *pDC, CPrintInfo *pInfo);

private:

	static int CALLBACK SortFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

	void CalculateColumnsWidthForPrint(int nRectWidth);
	void PrintColumnHeaders(CDC *pDC, CFont* pFontBold, int nRectHeight);
	void PrintFooter(CDC *pDC, CPrintInfo *pInfo, CFont* pFontBold, int nRectHeight, int nPagina);
	void SetSortIndicator(int iCol);
	// void SetSortColumn(int iCol);

	static CString GetDateFromItem(CString strItem);
	static CString GetDateTimeFromItem(CString strItem);

	struct tagITEMCALLBACK
	{
		CListCtrlLocalize* pListCtrl;
		int iCol;
	};

	struct tagHEADERITEMDATA
	{
		ColumnType type;
		SortType sort;
	};

	//

	CString m_sNotePiePagina;

	//

	int m_iColumnWidthForPrinter[255];

};