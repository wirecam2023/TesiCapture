#ifndef _ELIMINACODESET_H_
	#define _ELIMINACODESET_H_

#include "BaseSet.h"

class CEliminaCodeSet : public CBaseSet
{

	DECLARE_DYNAMIC(CEliminaCodeSet)

public:

	CEliminaCodeSet();
	~CEliminaCodeSet();

	long m_lID;
	CString m_sData;
	CString m_sSala;
	CString m_sCodice;
	long m_lColoreBackR;
	long m_lColoreBackG;
	long m_lColoreBackB;
	long m_lColoreForeR;
	long m_lColoreForeG;
	long m_lColoreForeB;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	// BOOL UpdateRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _ELIMINACODESET_H_ */