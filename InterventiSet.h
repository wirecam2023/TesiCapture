#ifndef _INTERVENTISET_H_
	#define _INTERVENTISET_H_

#include "BaseSet.h"

class CInterventiSet : public CBaseSet
{

	DECLARE_DYNAMIC(CInterventiSet)

public:

	CInterventiSet();

	long	m_lContatore;
	long	m_lIdEsame;
	long	m_lData;
	long	m_lOraInizio;
	long	m_lOraFine;
	CString m_sOperatori;		//  255
	CString m_sAnestesisti;		//  255
	CString m_sStrumentisti;	//  255
	CString m_sAnestesia;		//  255
	CString m_sDiagnosi;		// 3999
	CString m_sIntervento;		// 3999
	BOOL    m_bEliminato;

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

private:

	virtual void	DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void	SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _INTERVENTISET_H_ */