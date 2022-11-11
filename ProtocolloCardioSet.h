#ifndef _PROTOCOLLOCARDIOSET_H_
	#define _PROTOCOLLOCARDIOSET_H_

#include "BaseSet.h"

#define PROTOCOLLO_FASE_PRIMA -1
#define PROTOCOLLO_FASE_DURANTE 0
#define PROTOCOLLO_FASE_DOPO 1

class CProtocolloCardioSet : public CBaseSet
{

	DECLARE_DYNAMIC(CProtocolloCardioSet)

public:

	CProtocolloCardioSet();

	long m_lID;
	CString m_sDescrizione;
	long m_lFase;
	long m_lUO;
	BOOL m_bEliminato;

	long FleuryTrans(CString sDescrizione);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

	//
	long AddRow(CString sDescrizione, long lFase);
	void EdtRow(long lID, CString sDescrizione);
	void DelRow(long lID);

	long GetIDFromFase(long lFase);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _PROTOCOLLOCARDIOSET_H_ */