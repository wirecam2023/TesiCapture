#ifndef _EXTORDINIPROCEDUREICD9SET_H_
#define _EXTORDINIPROCEDUREICD9SET_H_

class CExtOrdiniProcedureICD9Set : public CBaseSet
{
	DECLARE_DYNAMIC(CExtOrdiniProcedureICD9Set)

public:

	CExtOrdiniProcedureICD9Set();
	~CExtOrdiniProcedureICD9Set();

	long m_lID;
	long m_lIDRichiesta;
	CString m_sCodiceICD9;

protected:

	void DoFieldExchange(CFieldExchange* pFX);
	CString GetDefaultSQL();

private:

	CBaseSet* CreateNew() { return NULL; } // è una vista //
	void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //

	BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //
	CString SetBaseFilter(const CString &strFilter);
};

#endif /* _EXTORDINIPROCEDUREICD9SET_H_ */