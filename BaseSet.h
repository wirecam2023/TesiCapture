#ifndef _BASESET_H_
	#define _BASESET_H_

#include "DLL_Imaging\h\Amdbx.h"

#include "WriteLogLineSet.h"

class CBaseSet : protected CAMBaseSet
{
    DECLARE_DYNAMIC(CBaseSet)

public:

	CBaseSet(long *pIdentityField, const CString &strIdentityField);
	~CBaseSet();

	CRecordset* GetRecordset() { return this; }

	void* PASCAL operator new(size_t nSize) { return CAMBaseSet::operator new(nSize); }
	void* PASCAL operator new(size_t nSize, void* p) { return CAMBaseSet::operator new(nSize, p); }
	void PASCAL operator delete(void* p) { CAMBaseSet::operator delete(p); }
	void PASCAL operator delete(void* p, void* pPlace) { CAMBaseSet::operator delete(p, pPlace); }

#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
	void* PASCAL operator new(size_t nSize, LPCSTR lpszFileName, int nLine) { return CAMBaseSet::operator new(nSize, lpszFileName, nLine); }
	void PASCAL operator delete(void *p, LPCSTR lpszFileName, int nLine) { CAMBaseSet::operator delete(p, lpszFileName, nLine); }
#endif

	BOOL IsOpen()    { return CAMBaseSet::IsOpen(); }
	BOOL CanUpdate() { return CAMBaseSet::CanUpdate(); }

	BOOL IsEOF()  { return CAMBaseSet::IsEOF(); }
	BOOL IsBOF()  { return CAMBaseSet::IsBOF(); }

	void MoveFirst() { CAMBaseSet::MoveFirst(); }
	void MovePrev()  { CAMBaseSet::MovePrev(); }
	void MoveNext()  { CAMBaseSet::MoveNext(); }
	void MoveLast()  { CAMBaseSet::MoveLast(); }

	long GetRecordCount() { return CAMBaseSet::GetRecordCount(); }

	void SetAbsolutePosition(long nRows) { return CAMBaseSet::SetAbsolutePosition(nRows); }

	void SetFieldNull(void* pv, BOOL bNull = TRUE) { CAMBaseSet::SetFieldNull(pv, bNull); }
	void SetFieldDirty(void* pv, BOOL bDirty = TRUE) { CAMBaseSet::SetFieldDirty(pv, bDirty); }

	BOOL IsFieldNull(void* pv);
	BOOL IsFieldDirty(void* pv) { return CAMBaseSet::IsFieldDirty(pv); }

	virtual CString SetOpenFilter(const CString& strFilter) { return CAMBaseSet::SetOpenFilter(strFilter); }
	virtual CString SetBaseFilter(const CString& strFilter) { return CAMBaseSet::SetBaseFilter(strFilter); }
	CString GetOpenFilter() { return CAMBaseSet::GetOpenFilter(); }
    CString GetBaseFilter(BOOL bComplete = FALSE) { return CAMBaseSet::GetBaseFilter(bComplete); }

	CString SetSortRecord(const CString& strSort) { return CAMBaseSet::SetSortRecord(strSort); }
	CString GetSortRecord() { return CAMBaseSet::GetSortRecord(); }
    
	// chiude il recordset arrangiandosi a gestire le eccezioni ed i messaggi all'utente //
	BOOL CloseRecordset(const CString &strCommento, BOOL bDebugDB = TRUE);
	// apre il recordset arrangiandosi a gestire le eccezioni ed i messaggi all'utente //
	BOOL OpenRecordset(const CString &strCommento, BOOL bDebugDB = TRUE, BOOL bForceDynaset = FALSE);
	// chiude e riapre il recordset arrangiandosi a gestire le eccezioni ed i messaggi all'utente //
	BOOL RecordsetReOpen(BOOL &bError, const CString &strFilter, const CString &strSort, const CString &strCommento);
	// aggiorna i dati del record corrente //
	BOOL RefreshRecordset();
	// aggiorna i dati del record corrente //
	BOOL RequeryRecordset();

	// aggiunge un nuovo record //
	BOOL AddNewRecordset(const CString &strCommento);
	// elimina il record corrente //
	virtual BOOL DeleteRecordset(const CString &strCommento) = 0;
	// attiva la modifica sul record corrente //
	BOOL EditRecordset(const CString &strCommento);
	// annulla le modifiche al record corrente //
	BOOL NoEditRecordset(const CString &strCommento);
	// salva le modifiche al record corrente //
	virtual BOOL UpdateRecordset(const CString &strCommento);

	BOOL CheckColumnExists(LPCTSTR szTable, LPCTSTR szColumnName); //Gabriel - TCP

	long GetIdentityLong();
	CString GetIdentityString();
	long GetLastAdd();

protected:

	virtual CBaseSet* CreateNew() = 0;
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) = 0;
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) = 0;

private:

	BOOL UpdateAdd(const CString &sCommento);
	BOOL UpdateEdt(const CString &sCommento);
	//BOOL UpdateDel(const CString &sCommento);

	CBaseSet* m_pCopySet;
	long *m_pIdentityField;
	CString m_sIdentityField;

	long m_lLastAdd;
};

#endif /* _BASESET_H_ */
