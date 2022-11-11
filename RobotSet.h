#pragma once

#include "BaseSet.h"

class CRobotSet : public CBaseSet
{
public:
	enum Type {
		Rimage=0
	};

	DECLARE_DYNAMIC(CRobotSet)

public:

	CRobotSet();

	long	m_lID;
	CString	m_sDescription;
	Type	m_lType;
	CString m_sHost;
	long	m_lPort;
	CString m_sBackupLabelPath;
	CString m_sPatientLabelPath;
	CString m_sMergeDirectoryPath;
	CString m_sTempDirectoryPath;
	BOOL	m_bSimulationMode;
	long	m_lUO;
	BOOL	m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

private:
	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual CBaseSet* CreateNew();

};
