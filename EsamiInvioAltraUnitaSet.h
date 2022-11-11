#ifndef _ESAMIINVIOALTRAUNITASET_H_
#define _ESAMIINVIOALTRAUNITASET_H_

#include "BaseSet.h"

class CEsamiInvioAltraUnitaSet : public CBaseSet
{

	DECLARE_DYNAMIC(CEsamiInvioAltraUnitaSet)

public:

	CEsamiInvioAltraUnitaSet();

	long m_lID;
	long m_lIDEsame;
	long m_lIDPdf;
	long m_lIDPdfImmagini;
	CString m_sDataOra;
	long m_lIDUtente;
	long m_lUnita;
	CString m_sEndpoint;
	long m_lEseguito;
	CString m_sEsito;
	
	BOOL InserisciRecord(long lIDEsame, long lIDUtente, long lUnita);
	void EliminaRecord(long lIDEsame, CString sEsito);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

	void SetIdPdf(long lIDPdf, long lIDEsame);
	void SetIdPdfImmagini(long lIDPdfImmagini, long lIDEsame);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _ESAMIINVIOALTRAUNITASET_H_ */