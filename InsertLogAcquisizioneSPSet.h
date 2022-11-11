#ifndef _INSERTLOGACQUISIZIONESPSET_H_
	#define _INSERTLOGACQUISIZIONESPSET_H_

class CInsertLogAcquisizioneSPSet : protected CRecordset
{

public:

	CInsertLogAcquisizioneSPSet();
	~CInsertLogAcquisizioneSPSet();

	void Exec(long lIDPaziente, long lIDEsame, CString sUtente, CString sStazione, CString sOperazione);

protected:

	void DoFieldExchange(CFieldExchange* pFX);
	CString GetDefaultSQL();

	void Move(long nRows, WORD wFetchType = SQL_FETCH_RELATIVE) {}

private:

	long m_lIDPaziente;
	long m_lIDEsame;
	CString m_sUtente;
	CString m_sStazione;
	CString m_sOperazione;

};

#endif /* _INSERTLOGACQUISIZIONESPSET_H_ */