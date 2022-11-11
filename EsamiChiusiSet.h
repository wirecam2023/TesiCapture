#ifndef _ESAMICHIUSISET_H_
	#define _ESAMICHIUSISET_H_

#include "BaseSet.h"

class CEsamiChiusiSet : public CBaseSet
{

	DECLARE_DYNAMIC(CEsamiChiusiSet)

public:

	CEsamiChiusiSet();

	long m_lID;
	long m_lIDEsame;
	long m_lIDPdf;
	long m_lIDPdfImmagini;
	CString m_sDataOra;
	long m_lIDUtente;
	CString m_sTipologia;
	long m_lIDPdfOld;
	long m_lEseguito;
	CString m_sEsito;

	void InserisciRecord(long lIDEsame, long lIDPdf, long lIDPdfImmagini, long lIDUtente, CString sTipologia, long lIDPdfOld = -1);
	void UpdateRecord(long lIDEsame, long lIDPdf, long lIDPdfImmagini, long lIDUtente);
	long GetIdFromPdfId(long lPdfId);
	long GetPdfIdFromId(long lId);
	void RemoveFromExam(long lClosedExamId);
	CString UltimaDataOraChiusura(long lIDEsame);

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

#endif /* _ACCESSORISET_H_ */