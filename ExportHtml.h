#ifndef _EXPORTHTML_H_
	#define _EXPORTHTML_H_

class CExportHtml
{

public:

	CExportHtml();
	virtual ~CExportHtml();

	BOOL CreateFile(CString strFileName, CString strTitolo, int nColonne);
	BOOL CloseFile();

	void WriteValue(CString strValue);
	void WriteNewRow();
	void WriteNewColumn();
	void WriteTitle(CString strTitle);

private:	

	BOOL WriteData(void* szBuffer, int nBufferSize);

	HANDLE m_hFile;
	BOOL m_bDispari;

};

#endif /* _EXPORTHTML_H_ */