#pragma once

class CDbLocker : protected CRecordset
{
public:
	CDbLocker();
	~CDbLocker();

	BOOL LockResource(LPCTSTR szResource, CDatabase* pDatabase);

	BOOL UnlockResource(LPCTSTR szResource, CDatabase* pDatabase);

protected:
	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual void Move(long nRows, WORD wFetchType = SQL_FETCH_RELATIVE) {}
	virtual CString GetDefaultSQL();

	long m_lResult;
	CString m_sResource;

	BOOL m_bLockResource;
};

