#ifndef _EXTPATIENTEVENTSET_H_
#define _EXTPATIENTEVENTSET_H_

#include "BaseSet.h"

enum PatientEventType
{
	addNewPatient = 1,
	updatePatient,
	acquirePatient,
	usePatient
};

class CExtPatientEventSet : public CBaseSet
{
	DECLARE_DYNAMIC(CExtPatientEventSet)

public:
	CExtPatientEventSet();
	~CExtPatientEventSet();

	long m_lId;
	long m_lPatientId;
	long m_lEventType;
	CString m_sDateTime;
	long m_lUserId;

	BOOL AddEvent(long patientId, long eventType);

private:
	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //

};

#endif /* _EXTPATIENTEVENTSET_H_ */