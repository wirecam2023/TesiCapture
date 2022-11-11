#ifndef _ANATOMIAPATOLOGICARICHIESTEQUEUESET_H_
	#define _ANATOMIAPATOLOGICARICHIESTEQUEUESET_H_

#include "BaseSet.h"

class CAnatomiaPatologicaRichiesteQueueSet : public CBaseSet
{
	DECLARE_DYNAMIC(CAnatomiaPatologicaRichiesteQueueSet)

public:

	CAnatomiaPatologicaRichiesteQueueSet();

	enum {
		INSERIMENTO = 1,
		ANNULLAMENTO = 2
	} TIPOLOGIA;

	long m_lId;
	long m_lIdEsame;
	CString m_sDataOra;
	CString m_sTipologia;
	long m_lEseguito;
	long m_lIdUtente;
	CString m_sErrore;
	BOOL m_bEliminato;

	void InserisciRecord(long idEsame, long idUtente, long tipologia);

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

#endif /* _ANATOMIAPATOLOGICARICHIESTEQUEUESET_H_ */