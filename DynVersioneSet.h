#ifndef _DYNVERSIONESET_H_
	#define _DYNVERSIONESET_H_

#include "BaseSet.h"

class CDynVersioneSet : public CBaseSet
{

	DECLARE_DYNAMIC(CDynVersioneSet)

public:

	CDynVersioneSet();
	~CDynVersioneSet();

	long m_lID;
	long m_lDataOra;
	long m_lIDTipoEsame;
	long m_lUO;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico data/ora ed UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _DYNVERSIONESET_H_ */