#ifndef _ESAMIREFERTAZIONEREMOTASET_H_
	#define _ESAMIREFERTAZIONEREMOTASET_H_

#include "BaseSet.h"

class CEsamiRefertazioneRemotaSet : public CBaseSet
{

	DECLARE_DYNAMIC(CEsamiRefertazioneRemotaSet)

public:

	CEsamiRefertazioneRemotaSet();

	long m_lID;
	long m_lIDEsame;
	CString m_sDataOra;
	long m_lIDUtente;
	long m_lEseguito;
	CString m_sEsito;

	BOOL InserisciRecord(long lIDEsame, long lIDUtente);
	void EliminaRecord(long lIDEsame, CString sEsito);

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

#endif /* _ESAMIREFERTAZIONEREMOTASET_H_ */