#ifndef _PSMLOGSET_H_
	#define _PSMLOGSET_H_

#include "BaseSet.h"

class CPsmLogSet : public CBaseSet
{

	DECLARE_DYNAMIC(CPsmLogSet)

public:

	CPsmLogSet();

	long m_lId;
	CString m_sDataOra;
	long m_lIdPaziente; 
	long m_lIdEsame; 
	CString m_sIdEpisodio; 
	CString m_sUrl;

	void InsertLog(long lPaziente, long lEsame, CString idEpisodio, CString url);

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _PSMLOGSET_H_ */