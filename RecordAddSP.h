#ifndef _RECORDADDSP_H_
	#define _RECORDADDSP_H_

#include "AfxDB.h"

class CRecordAddSP : protected CRecordset // solo le Stored Procedure possono essere derivate da CRecordset //
{

public:

	CRecordAddSP();
	DECLARE_DYNAMIC(CRecordAddSP)

	void Move(long nRows, WORD wFetchType) {};
	long Execute(const CString &sTableNameIN, const CString &sFieldNameIN);

protected:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual void SetEmpty();

	// INPUT //
	CString m_sTableNameIN;
	CString m_sFieldNameIN;

	// OUTPUT //
	long m_lNewRecordOUT;

};

#endif /* _RECORDADDSP_H_ */