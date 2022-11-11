#ifndef _OBSELECT_H_
	#define _OBSELECT_H_

class CFileBmp;

typedef struct ImageToPrint
{  
	long m_lID;
	long m_lFrame;
	BOOL m_bConfirmed;
	CString m_strDvdLabel;
	long m_lPaziente;
	long m_lEsame;
} IMAGE_TO_PRINT;

class CObSelect : public CObject
{
	DECLARE_DYNCREATE(CObSelect)

public:

	CObSelect();
	CObSelect(CFileBmp* pFileBmp);
	CObSelect(long lID, BOOL bIsGlobal, int iType, const CString &strDescription, long lPaziente, long lEsame, BOOL bTransferred, const CString &strDvdLabel, BOOL bCI);
	
	long m_lID;
	BOOL m_bIsGlobal;
	int m_iType;

	CString m_strDescription;

	long m_lPaziente;
	long m_lEsame;
	BOOL m_bConfirmed;
	CString m_strDvdLabel;

	BOOL m_bCI;
};

#endif /* _OBSELECT_H_ */