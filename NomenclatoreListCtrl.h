#ifndef _NOMENCLATORELISTCTRL_H_
	#define _NOMENCLATORELISTCTRL_H_

class CNomenclatoreListCtrl : public CListCtrl
{

public:

	CNomenclatoreListCtrl(CEsamiView* pEsamiView);
	~CNomenclatoreListCtrl();

	int InsertColumn(int nCol, LPCTSTR lpszColumnHeading, int nFormat);

	int GetColumnNumber();
	int GetRowNumber();

    void Print();
	void SetColumnWidthForPrint(int nColumn, float fPercentual);
	void Export(CString strTitle);

	void SetIntestazioneData(int nRiga, int nColonna, int nLarghezza, int nAltezza, CString strTesto);
	void ResetIntestazioneData();

	void SetTableStyle(LOGFONT font);
	LOGFONT GetTableStyle();

	void SetCellStyle(int nRiga, int nColonna, LOGFONT font);
	void SetNotePiePagina(CString strNote);

protected:

	void CalculateColumnWidth(int nLarghezzaRect);

	virtual void OnBeginPrinting(CDC *pDC, CPrintInfo *pInfo);
    virtual void OnPrint(CDC *pDC, CPrintInfo *pInfo);
	virtual void OnEndPrinting(CDC *pDC, CPrintInfo *pInfo);

    void PrintIntestazione(CDC *pDC, CFont* font);

	int GetAltezzaIntestazioneRighe();

	BOOL IsEmptyRow(int nRow);

	struct tagIntestazioneTab
	{
		int nRiga;         // riga di appartenenza
		int nColonna;      // inizio casella
		int nLarghezza;    // larghezza casella (in colonne)
		int nAltezza;      // altezza casella (in righe)
		char pTesto[2048]; // testo intestazione
	};

	tagIntestazioneTab m_FormatoIntestazione[255];

	int m_nCaselleImpostate;

	struct tagStile
	{
		int nRiga;
		int nColonna;
		LOGFONT lfFont;
	};
	
	CList<tagStile> m_ListaStile;

	float m_fColumnWidth[255];
	float m_fColumnWidthForPrinter[255];

	CString m_strNotePiePagina;

	LOGFONT m_fontTable;

	float m_fAltezzaMmNumeroPagina, m_fAltezzaMmRigaIntestazione, m_fAltezzaMmRiga;

	CEsamiView* m_pEsamiView;
};

#endif /* _NOMENCLATORELISTCTRL_H_ */