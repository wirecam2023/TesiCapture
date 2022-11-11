#ifndef _TUTORIALFILESSET_H_
	#define _TUTORIALFILESSET_H_

#include "BaseSet.h"

class CTutorialFilesSet : public CBaseSet
{
	DECLARE_DYNAMIC(CTutorialFilesSet)

public:

	CTutorialFilesSet();

	long m_lID;
	CString m_sDescrizione;
	CString m_sIndirizzoCompleto;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	long Add(CString sDescrizione, CString sIndirizzo);
	void Edt(long lID, CString sDescrizione, CString sIndirizzo);
	BOOL Del(long lID);

	CString GetIndirizzoCompleto(long lID);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _TUTORIALFILESSET_H_ */