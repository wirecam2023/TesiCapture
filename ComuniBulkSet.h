#ifndef _COMUNIBULKSET_H_
	#define _COMUNIBULKSET_H_

class CComuniBulkSet : public CRecordset
{
	DECLARE_DYNAMIC(CComuniBulkSet)

public:

	CComuniBulkSet();

	void CaricaInMemoria();

private:

	virtual void DoBulkFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();

	CString GetTextField10(LPTSTR szField, long* pFieldSize, int iIndex);
	CString GetTextField50(LPTSTR szField, long* pFieldSize, int iIndex);

	long* m_pID;
	LPTSTR m_pComune;
	LPTSTR m_pCAP;
	LPTSTR m_pProvincia;

	long* m_pIDLength;
	long* m_pComuneLength;
	long* m_pCAPLength;
	long* m_pProvinciaLength;

};

#endif /* _COMUNIBULKSET_H_ */