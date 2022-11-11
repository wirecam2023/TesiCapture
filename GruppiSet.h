#ifndef _GRUPPISET_H_
	#define _GRUPPISET_H_

#include "BaseSet.h"

class CGruppiSet : public CBaseSet
{

	DECLARE_DYNAMIC(CGruppiSet)

public:

	CGruppiSet();

	long m_lID;
	CString m_sNome;
	long m_lUO;
	BOOL m_bEliminato;

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

	//
	long GetUO(long lID);
	void SetUO(long lID, long lUO);
	CString GetDescrizione(long lID);

	long GetIDFromNome(CString sNome);
	long GetUOFromNome(CString sNome);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _GRUPPISET_H_ */