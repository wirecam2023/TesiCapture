#ifndef _FRASIRTFSET_H_
	#define _FRASIRTFSET_H_

#include "BaseSet.h"

class CFrasiRtfSet : public CBaseSet
{

	DECLARE_DYNAMIC(CFrasiRtfSet)

public:

	CFrasiRtfSet();

	long m_lID;
	long m_lSesso;
	long m_lTipo;
	CString m_sSezione;
	CString m_sCodice;
	CString m_sIndice;
	CString m_sTestoRTF;
	CString m_sTestoTXT;
	BOOL m_bEliminato;
	long m_lUO;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

	//
	CString GetTestoRtf(long lID);
	CString GetTestoTxt(long lID);

	long GetIDByCodice(CString sCodice); //Julio BUG 3457 - Texter

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _FRASIRTFSET_H_ */