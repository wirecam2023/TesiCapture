#ifndef _MALATTIECRONICHECAMPISET_H_
	#define _MALATTIECRONICHECAMPISET_H_

#include "BaseSet.h"

class CMalattieCronicheCampiSet : public CBaseSet
{

	DECLARE_DYNAMIC(CMalattieCronicheCampiSet)

public:

	CMalattieCronicheCampiSet();

	long m_lID;
	long m_lIDMalattia;
	long m_lIDCampo;
	long m_lTipoCampo;
	long m_lOrdine;
	BOOL m_bEliminato;

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

	// ritorna l'ordine per l'inserimento del nuovo record //
	long GetNextOrdine(long lIDMalattia);

	// imposta l'ordine per un dato record //
	void SetOrdine(long lID, long lOrdine);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();
	
	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _MALATTIECRONICHECAMPISET_H_ */