#ifndef _EXTORDINIDIAGNOSIICD9SET_H_
#define _EXTORDINIDIAGNOSIICD9SET_H_

class CExtOrdiniDiagnosiICD9Set : public CBaseSet
{
	DECLARE_DYNAMIC(CExtOrdiniDiagnosiICD9Set)

public:

	CExtOrdiniDiagnosiICD9Set();
	~CExtOrdiniDiagnosiICD9Set();

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

#endif /* _EXTORDINIDIAGNOSIICD9SET_H_ */