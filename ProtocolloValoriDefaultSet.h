#ifndef _PROTOCOLLOVALORIDEFAULTSET_H_
	#define _PROTOCOLLOVALORIDEFAULTSET_H_

#include "BaseSet.h"

class CProtocolloValoriDefaultSet : public CBaseSet
{

	DECLARE_DYNAMIC(CProtocolloValoriDefaultSet)

public:

	CProtocolloValoriDefaultSet();

	long m_lID;
	long m_lIDProtocollo;
	long m_lIDColonna;
	long m_lOrdine;
	CString m_sValore;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	//
	void AddEdtRow(long lIDProtocollo, long lIDColonna, long lOrdine, CString sValore);

	void DelAllProt(long lIDProtocollo);
	void DelAllColo(long lIDProtocollo, long lIDColonna);
	void DelAllOrdi(long lIDProtocollo, long lOrdine);

	long GetNextOrdine(long lIDProtocollo);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _PROTOCOLLOVALORIDEFAULTSET_H_ */