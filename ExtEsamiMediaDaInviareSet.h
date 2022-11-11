#ifndef _ESAMIMEDIADAINVIARESET_H_
#define _ESAMIMEDIADAINVIARESET_H_

#include "BaseSet.h"

class CExtEsamiMediaDaInviareSet : public CBaseSet
{

	DECLARE_DYNAMIC(CExtEsamiMediaDaInviareSet)

public:

	CExtEsamiMediaDaInviareSet();

	long m_lID;
	long m_lIDEsame;
	CString m_sDataOra;
	long m_lTipoMedia;
	long m_lEseguito;
	CString m_sEsito;

	BOOL InsertExam(long examId, long mediaType);

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

#endif /* _ESAMIMEDIADAINVIARESET_H_ */