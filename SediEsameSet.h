#ifndef _SEDIESAMESET_H_
	#define _SEDIESAMESET_H_

#include "BaseSet.h"

class CSediEsameSet : public CBaseSet
{
	DECLARE_DYNAMIC(CSediEsameSet)

public:

	CSediEsameSet();

	long m_lID;
	CString m_sDescrizione;
	CString m_sSiglaProgressivo;
	CString m_sAPSede;
	CString m_sDicomSede;
	CString m_sCodicePresidioOspedaliero;
	CString m_sCodice;
	// long m_lUO; // Sandro 13/03/2015 // non ci va la UO in questa tabella //
	BOOL m_bEliminato;

	//
	long GetID(CString sDescrizione);
	CString GetDescrizione(long lID, BOOL bForQuery);
	CString GetSigla(long lID);
	CString GetAPSede(long lID);
	CString GetCodicePresidio(long lID);
	CString GetCodice(long lID);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	//
	void VerificaSedeDefault();

private:
	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual CBaseSet* CreateNew();

};

#endif /* _SEDIESAMESET_H_ */