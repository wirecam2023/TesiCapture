#ifndef _VITALSIGNMISURAZIONIDETAILSET_H_
#define _VITALSIGNMISURAZIONIDETAILSET_H_

#include "BaseSet.h"

class CVitalSignMisurazioniDetailSet : public CBaseSet
{
	DECLARE_DYNAMIC(CVitalSignMisurazioniDetailSet)

public:

	CVitalSignMisurazioniDetailSet();

	long m_lID;
	CString m_sVitalSignId;
	long m_lIDHeader;	
	CString m_sOra;
	CString m_sFC;
	CString m_sPA;
	CString m_sSat;
	CString m_sNote;
	BOOL m_bEliminato;

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);
};

#endif /*_VITALSIGNMISURAZIONIDETAILSET_H_*/