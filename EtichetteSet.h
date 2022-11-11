#ifndef _LABELSET_H_
	#define _LABELSET_H_

#include "BaseSet.h"

class CEtichetteSet : public CBaseSet
{

	DECLARE_DYNAMIC(CEtichetteSet)

public:

	CEtichetteSet();

	long m_lContatore;
	long m_lIndice;
	CString m_sTipo;
	CString m_sLabel;
	long m_lIdCampoRelazionato;
	long m_lUO;
	BOOL m_bEliminato;

	CString GetLabel(CString tipo, int indice);
	long GetId(CString tipo, int indice);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _LABELSET_H_ */