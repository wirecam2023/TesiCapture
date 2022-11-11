#ifndef _MEDICICURANTIINVIANTIBULKSET_H_
	#define _MEDICICURANTIINVIANTIBULKSET_H_

class CMediciCurantiInviantiBulkSet : public CRecordset
{
	DECLARE_DYNAMIC(CMediciCurantiInviantiBulkSet)

public:

	CMediciCurantiInviantiBulkSet(long lCurantiInvianti);

	void CaricaInMemoria();

private:

	virtual void DoBulkFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();

	CString GetTextField(LPTSTR szField, long* pFieldSize, int iIndex);

	long m_lCurantiInvianti;

	long* m_pContatore;
	LPTSTR m_pTitolo;
	LPTSTR m_pCognome;
	LPTSTR m_pNome;

	long* m_pContatoreLength;
	long* m_pTitoloLength;
	long* m_pCognomeLength;
	long* m_pNomeLength;

};

#endif /* _MEDICICURANTIINVIANTIBULKSET_H_ */