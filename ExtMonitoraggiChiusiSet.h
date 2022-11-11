#pragma once
#include "BaseSet.h"

class CExtMonitoraggiChiusiSet : public CBaseSet
{

	DECLARE_DYNAMIC(CExtMonitoraggiChiusiSet)

public:

	CExtMonitoraggiChiusiSet();

	long m_lID;
	long m_lIDEsame;
	long m_lIDPdf;
	CString m_sDataOra;
	long m_lIDUtente;	
	long m_lEseguito;
	CString m_sEsito;

	void InserisciRecord(long lIDEsame, long lIDPdf, long lIDUtente);	

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