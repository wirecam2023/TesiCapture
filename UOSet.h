#ifndef _UOSET_H_
	#define _UOSET_H_

#include "BaseSet.h"

class CUOSet : public CBaseSet
{
	DECLARE_DYNAMIC(CUOSet)

public:

	CUOSet();

	long m_lID;
	CString m_sDescrizione;
	CString m_sCodiceIntegrazione;
	CString m_sUsernameResponsabile;
	BOOL m_bFastFichaWorklist;
	BOOL m_bEliminato;

	// 
	BOOL ExistMoreThanOneUO();
	CString GetCodiceIntegrazione(long lID, BOOL bForQuery);
	CString GetDescrizione(long lID);
	CString GetUsernameResponsabile(long lID);
	BOOL GetFastFichaWorklist(long lID);
	long GetIDFromDescrizione(CString sDescrizione);
	long GetUOFromCodiceIntegrazione(CString sCodiceIntegrazione);
	void VerificaUODefault();

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual CBaseSet* CreateNew();

};

#endif /* _UOSET_H_ */