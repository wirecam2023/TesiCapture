#ifndef _INSERTLOGIMPORTAZIONECASISPSET_H_
#define _INSERTLOGIMPORTAZIONECASISPSET_H_

class CInsertLogImportazioneCasiSPSet : protected CRecordset
{

public:

	CInsertLogImportazioneCasiSPSet();
	~CInsertLogImportazioneCasiSPSet();

	void Exec(long lIDPaziente, long lIDEsameOrigine, long lIDEsameDestinazione, CString sUtente, CString sStazione);

protected:

	void DoFieldExchange(CFieldExchange* pFX);
	CString GetDefaultSQL();

	void Move(long nRows, WORD wFetchType = SQL_FETCH_RELATIVE) {}

private:

	long m_lIDPaziente;
	long m_lIDEsameOrigine;
	long m_lIDEsameDestinazione;
	CString m_sUtente;
	CString m_sStazione;

};

#endif /* _INSERTLOGIMPORTAZIONECASISPSET_H_ */