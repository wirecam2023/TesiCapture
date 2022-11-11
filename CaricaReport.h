#ifndef _CARICAREPORT_H_
	#define _CARICAREPORT_H_

class CCaricaReport
{

public:

	CCaricaReport();
	~CCaricaReport();
	
	BOOL OpenReportFile(CString strReportFile, BOOL bIsSearchReport);
	BOOL CloseReportFile();
	
	long GetTotSection();
	int  GetNumberOfFields();
	
	long GetIDHeader1();
	long GetIDHeader2();
	long GetIDFooter1();
	long GetIDFooter2();

	CString  GetFieldType();
	CString  GetFieldValue();
	CRect    GetDimensionInMm();
	long     GetCheck();
	COLORREF GetColor();
	long     GetParam();
	int		 GetAlignment();
	int		 GetRotation();
	LOGFONT  GetFont();
	
	void MoveFirst();
	void MoveNext();
	BOOL IsLast();
	BOOL IsEOF();

private:

	CString m_strFileReport;
	BOOL    m_bIsSearchReport;
	BOOL    m_bIsEOF;

	struct ElementoReport
	{
		CString strType;
		CString strValue;
		CRect rectInMm;
		long nCheck;
		COLORREF rgbColor;
		long nParam;
		int nAlignment;
		int nRotation;
		LOGFONT lfFont;
		ElementoReport *pElemNext;
	} *m_pElemReport, *m_pElemSupp, *m_pElemFirst;

	//Informazioni generali report in comune
	long m_lIDHeader1;
	long m_lIDHeader2;
	long m_lIDFooter1;
	long m_lIDFooter2;

	int  m_nTotSection;
	int  m_nTotFields;
	
	//Informazioni generali report normale
	int m_nWidth;
	int m_nHeight;

	//Informazioni generali report ricerca
	int m_nPageWidth;
	int m_nPageHeight;
	int m_nRowHeight;

};

#endif /* _CARICAREPORT_H_ */