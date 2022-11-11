#ifndef _PDFCREATOR_H_
	#define _PDFCREATOR_H_

#include "PdfManager.h"
#include "EsamiSet.h"

class CPDFCreator
{

public:

	CPDFCreator(CWnd* pParentWnd, CEsamiSet* pEsamiSet, pdftype pdfType);
	~CPDFCreator();

	// Sandro // 05/01/2011 // Archivio un PDF partendo da un file invece che da un buffer //
	long SavePdfFileIntoRepository(const CString sNote, const long lVersioneReferto, const long lIDPdfCheSostituisce, const BOOL bFitToPage, const CString sFileComplete);
	long SaveSignedPdfFileIntoRepository(const CString sNote, const long lVersioneReferto, const long lIDPdfCheSostituisce, const BOOL bFitToPage, CString* pStrFileComplete);

private:

	CWnd* m_pParentWnd;
	CEsamiSet* m_pEsamiSet;
	pdftype m_pdfType;

	BOOL SavePDFSignedIntoRepository(const CString sNote, const CString sSmartCardUtente, const CString sSmartCardNumero, const CString sSmartCardEnteCertificato, const long lVersioneReferto, const long lIDPdfCheSostituisce, const BOOL bFitToPage, const CString sClassificazione, const CString sFileComplete, long* pPdfID);

};

#endif /* _PDFCREATOR_H_ */