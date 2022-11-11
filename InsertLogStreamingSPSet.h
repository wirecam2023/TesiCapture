#ifndef _INSERTLOGSTREAMINGSPSET_H_
	#define _INSERTLOGSTREAMINGSPSET_H_

class CInsertLogStreamingSPSet : protected CRecordset
{

public:

	CInsertLogStreamingSPSet();
	~CInsertLogStreamingSPSet();

	void Exec(CString strUtente, CString strStazione, CString strStreamingDescrizione, CString strStreamingPazienteEsame);

protected:

	void DoFieldExchange(CFieldExchange* pFX);
	CString GetDefaultSQL();

	void Move(long nRows, WORD wFetchType = SQL_FETCH_RELATIVE) {}

private:

	CString m_strUtente;
	CString m_strStazione;
	CString m_strStreamingDescrizione;
	CString m_strStreamingPazienteEsame;

};

#endif /* _INSERTLOGSTREAMINGSPSET_H_ */