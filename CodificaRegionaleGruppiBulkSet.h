#ifndef _CODIFICAREGIONALEGRUPPIBULKSET_H_
	#define _CODIFICAREGIONALEGRUPPIBULKSET_H_

class CCodificaRegionaleGruppiBulkSet : public CRecordset
{
	DECLARE_DYNAMIC(CCodificaRegionaleGruppiBulkSet)

public:

	CCodificaRegionaleGruppiBulkSet();

	void CaricaInMemoria();

private:

	virtual void DoBulkFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();

	CString GetTextField(LPTSTR szField, long* pFieldSize, int iIndex);

	long* m_pID;
	LPTSTR m_pDescrizione;

	long* m_pIDLength;
	long* m_pDescrizioneLength;

};

#endif /* _CODIFICAREGIONALEGRUPPIBULKSET_H_ */