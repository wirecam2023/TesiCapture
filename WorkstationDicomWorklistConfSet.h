#ifndef _COMBORAOSET_H_
	#define _COMBORAOSET_H_

#include "BaseSet.h"

class CWorkstationDicomWorklistConfSet : public CBaseSet
{

	DECLARE_DYNAMIC(CWorkstationDicomWorklistConfSet)

public:

	CWorkstationDicomWorklistConfSet();

	long m_lID;
	CString m_sWorkstation;
	BOOL m_bActive;
	CString m_sAET;
	long m_lPort;
	BOOL m_bWriteLog;

	//
	BOOL GetWorkstationState(CString& sAET, long& lPort, BOOL& bWriteLog);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	// CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	// BOOL UpdateRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _ANATOMIAPATOLOGICAESAMIPRESTSET_H_ */