#ifndef _EXTVIDEOCAPSULESET_H_
	#define _EXTVIDEOCAPSULESET_H_

#include "BaseSet.h"

class CExtEsamiVideocapsulaSet : public CBaseSet
{

	DECLARE_DYNAMIC(CExtEsamiVideocapsulaSet)

public:

	CExtEsamiVideocapsulaSet();

	long m_lId;
	long m_lIdEsame;
	long m_lIdUtente;
	CString m_sDataOra;	
	BOOL m_bEseguito;
	CString m_sEsito;


	long InserisciRecord(	long idEsame,
							long idUtenteInvio);

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

#endif /* _EXTVIDEOCAPSULESET_H_ */