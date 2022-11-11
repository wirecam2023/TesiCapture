#ifndef _INVIANTISET_H_
	#define _INVIANTISET_H_

#include "BaseSet.h"

class CInviantiSet : public CBaseSet
{

	DECLARE_DYNAMIC(CInviantiSet)

public:

	CInviantiSet(CString strTable = "");

	long m_lContatore;
	CString m_sDescrizione;
	CString m_sTelefono;
	CString m_sFax;
	CString m_sEmail;
	CString m_sCodiceIntegrazione;
	long m_lIdCentroDiCosto;
	long m_lUO;
	BOOL m_bEliminato;

	void	SetTableName(CString strTable)	{ m_strTable = strTable; }
	CString GetTableName()					{ return m_strTable;	 }

	CString GetFieldText(long lContatore);

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

	CString		m_strTable;
};

#endif /*_INVIANTISET_H_ */