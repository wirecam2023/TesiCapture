#ifndef _CODIFICAREGIONALEEXBULKSET_H_
	#define _CODIFICAREGIONALEEXBULKSET_H_

class CCodificaRegionaleExBulkSet : public CRecordset
{
	DECLARE_DYNAMIC(CCodificaRegionaleExBulkSet)

public:

	CCodificaRegionaleExBulkSet();

	void CaricaInMemoria();

private:

	virtual void DoBulkFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();

	CString GetTextField(LPTSTR szField, long* pFieldSize, int iIndex);

	long* m_pContatore;
	LPTSTR m_pDescrizione;

	long* m_pContatoreLength;
	long* m_pDescrizioneLength;

};

#endif /* _CODIFICAREGIONALEEXBULKSET_H_ */