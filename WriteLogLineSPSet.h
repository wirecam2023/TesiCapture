#ifndef _WRITELOGLINESPSET_H_
	#define _WRITELOGLINESPSET_H_

class CWriteLogLineSPSet : protected CRecordset
{

public:

	CWriteLogLineSPSet();
	~CWriteLogLineSPSet();

	void Exec(const long lIDPaziente,
			  const long lIDEsame,
			  const CString &sUtente,
			  const CString &sStazione,
			  const CString &sImpianto,
			  const CString &sTabella,
			  const long lOperazione,
			  const CString &sNomeChiave,
			  const long lValoreChiave,
			  const CString &sCampo,
			  const CString &sValoreOld,
			  const CString &sValoreNew,
			  const CString &sCommento);

protected:

	void DoFieldExchange(CFieldExchange* pFX);
	CString GetDefaultSQL();

	void Move(long nRows, WORD wFetchType = SQL_FETCH_RELATIVE) {}

private:

	long m_lIDPaziente;
	long m_lIDEsame;
	CString m_sUtente;
	CString m_sStazione;
	CString m_sImpianto;
	CString m_sTabella;
	long m_lOperazione;
	CString m_sNomeChiave;
	long m_lValoreChiave;
	CString m_sCampo;
	CString m_sValoreOld;
	CString m_sValoreNew;
	CString m_sCommento;

};

#endif