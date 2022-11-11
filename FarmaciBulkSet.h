#ifndef _FARMACIBULKSET_H_
	#define _FARMACIBULKSET_H_

class CFarmaciBulkSet : public CRecordset
{
	DECLARE_DYNAMIC(CFarmaciBulkSet)

public:

	CFarmaciBulkSet();

	void CaricaInMemoria();

private:

	virtual void DoBulkFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();

	CString GetTextField(LPTSTR szField, long* pFieldSize, int iIndex);

	long* m_pID;
	LPTSTR m_pNome;
	LPTSTR m_pPrincipioAttivo;
	LPTSTR m_pDescrizione;

	long* m_pIDLength;
	long* m_pNomeLength;
	long* m_pPrincipioAttivoLength;
	long* m_pDescrizioneLength;

};

#endif /* _FARMACIBULKSET_H_ */