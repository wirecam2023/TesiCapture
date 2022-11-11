#ifndef _PROTOCOLLOESAMISET_H_
	#define _PROTOCOLLOESAMISET_H_

#include "BaseSet.h"

class CProtocolloEsamiSet : public CBaseSet
{

	DECLARE_DYNAMIC(CProtocolloEsamiSet)

public:

	CProtocolloEsamiSet();

	long m_lID;
	long m_lIDEsame;
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
	void AddEdtRow(long lIDEsame, long lIDProtocollo, long lIDColonna, long lOrdine, CString sValore);
	void DelRows(long lIDEsame, long lIDProtocollo, long lPrimoOrdineDaCancellare);
	BOOL HasRows(long lIDEsame, long lIDProtocollo);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _PROTOCOLLOESAMISET_H_ */