#ifndef _COMUNISET_H_
	#define _COMUNISET_H_

#include "BaseSet.h"

class CComuniSet : public CBaseSet
{
	DECLARE_DYNAMIC(CComuniSet)

public:

	CComuniSet();

	long m_lID;
	CString m_sComune;
	CString m_sCAP;
	CString m_sProvincia;
	CString m_sDataInizioValidita;
	CString m_sDataFineValidita;

	void GetFieldText(long lContatore, CString& strComune, CString& strCAP, CString& strProvincia);
	CString GetDataInizioValidita(long id);
	CString GetDataFineValidita(long id);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // faccio finta sia una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // faccio finta sia una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // faccio finta sia una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // faccio finta sia una vista //
};

#endif /* _COMUNISET_H_ */