#ifndef __CPRINTERSETTINGS_H__
	#define __CPRINTERSETTINGS_H__

#include <winspool.h> 

// #define PRINTERNAME_UNDEFINED			"printer not set..."
// #define PRINTERSETTINGS_DIRECTORYNAME	"printer settings"

class CPrinterSettings : public CObject  
{
public:

	CPrinterSettings();
	// CPrinterSettings(const CString dirname);
	virtual ~CPrinterSettings();

	void operator=(const CPrinterSettings* src);
	void operator=(const CPrinterSettings& src);

// general interface
public:

	// is m_hDevMode allocated
	BOOL ValidDevMode(void) const
		{ return m_hDevMode != NULL; }

	// get the settings for the default MFC Printer
	void CopyDefaultMfcPrinter(void);

	// Set the default MFC Printer to this
	BOOL SetThisPrinter(void);

	// change settings for global Windows Printer
	BOOL SetPrinterDevice(LPCTSTR pszDeviceName) const;

	// Show the common dialog and get the settings
	CString PrinterSetup( CWnd* pWnd, CString strTitle = CString("Print"));

	// restore previous printer settings (if safed)
	void RestorePrinter(void);

	CString GetFileName( void ) const
		{ return m_strfilename; }

	// CString SetDirName( const CString neu) 
	// 	{ CString temp = m_strdirname; m_strdirname = neu; return temp; }

	// CString GetDirName( void ) const
	// 	{ return m_strdirname; }

	// save all settings to disk
	int Save(LPCTSTR strFilename);

	// load all settings
	int Load(LPCTSTR strFilename);

	// check to see if our printer is still available
	BOOL IsPrinterAvailable(LPCTSTR pszDeviceName);

	// retrieve the human readable printername :)
	CString GetPrinterName(void) const
		{ return m_strPrinterName; }

	HDC CreatePrinterDC();

	LPDEVMODE GetDevModePointer(); // Sandro // 04/01/2011 //
	LPDEVNAMES GetDevNamesPointer(); // Sandro // 04/01/2011 //

	HGLOBAL GetDevModeHandle(); // Sandro // 04/01/2011 //
	HGLOBAL GetDevNamesHandle(); // Sandro // 04/01/2011 //

private:	// but not useless:  :o)

	CString DevmodePrinterName(void);
	HANDLE CopyHandle(HANDLE h); 
	// copy whole DEVMODE ( with dmSize + dmDriverExtra )
	int CopyDevmode( DEVMODE* pDest,const DEVMODE * pSrc) const;
	CString SetFileName( const CString neu) 
		{ CString temp = m_strfilename; m_strfilename = neu; return temp; }
	HANDLE m_hDevMode;
	HANDLE m_hDevNames;
	HANDLE m_hSaveDevMode;
	HANDLE m_hSaveDevNames;
	CString m_strPrinterName;
	CString m_strfilename;
	// CString m_strdirname;
};

#endif // __CPRINTERSETTINGS_H__
