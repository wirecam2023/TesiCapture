#pragma once

#include "BaseSet.h"

class CEsamiImmaginiAudiologia : public CBaseSet
{

	DECLARE_DYNAMIC(CEsamiImmaginiAudiologia)

public:

	CEsamiImmaginiAudiologia();

	long m_lID;
	long m_lIDEsame;
	long m_lIDImmagine;
	CString m_sTipo;
	BOOL m_bEliminato;

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);	

	virtual void SetEmpty();

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};