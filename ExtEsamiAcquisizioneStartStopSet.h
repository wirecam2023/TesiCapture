#ifndef _EXTESAMIACQUISIZIONESTARTSTOPSET_H_
#define _EXTESAMIACQUISIZIONESTARTSTOPSET_H_

#include "BaseSet.h"

enum FaseAcquisizione
{
	start = 0,
	stop
};

class CExtEsamiAcquisizioneStartStopSet : public CBaseSet
{

	DECLARE_DYNAMIC(CExtEsamiAcquisizioneStartStopSet)

public:

	CExtEsamiAcquisizioneStartStopSet();

	long m_lID;
	long m_lIDEsame;	
	CString m_sDataOra;
	long m_lIDUtente;
	FaseAcquisizione m_lFase;	
	long m_lEseguito;
	CString m_sEsito;

	void StartAcquisizione(long lExamId);
	void StopAcquisizione(long lExamId);

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

#endif /* _EXTESAMIACQUISIZIONESTARTSTOPSET_H_ */