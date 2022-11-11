#ifndef _EXPORTCSV_H_
	#define _EXPORTCSV_H_

class CExportCSV
{

public:

	CExportCSV();
	virtual ~CExportCSV();

	BOOL CreateFile(CString strFileName);
	BOOL CloseFile(CString strTitle);

	void WriteValue(CString strValue);
	void WriteNewRow();
	void WriteNewColumn();

private:	

	BOOL WriteFile(CString strTitle);

	HANDLE m_hFile;
	CString m_strFile;

};

#endif /* _EXPORTCSV_H_ */