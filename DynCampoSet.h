#ifndef _DYNCAMPOSET_H_
	#define _DYNCAMPOSET_H_

#include "BaseSet.h"

class CDynCampoSet : public CBaseSet
{

	DECLARE_DYNAMIC(CDynCampoSet)

public:

	CDynCampoSet();
	~CDynCampoSet();

	long m_lID;
	long m_lIDForm;
	long m_lContenuto;
	long m_lX;
	long m_lY;
	long m_lL;
	long m_lA;
	long m_lColore;
	long m_lTabOrder;
	//long m_lIDFaseBlocco;
	long m_lIDFaseBlocco;
	BOOL m_bEliminato;

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _DYNCAMPOSET_H_ */