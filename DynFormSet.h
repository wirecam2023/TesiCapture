#ifndef _DYNFORMSET_H_
	#define _DYNFORMSET_H_

#include "BaseSet.h"

class CDynFormSet : public CBaseSet
{

	DECLARE_DYNAMIC(CDynFormSet)

public:

	CDynFormSet();
	~CDynFormSet();

	long m_lID;
	long m_lIDVersione;
	CString m_sNome;
	long m_lOrdine;
	long m_lAlbum;
	BOOL m_bVisualizzaSempre;
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

#endif /* _DYNFORMSET_H_ */