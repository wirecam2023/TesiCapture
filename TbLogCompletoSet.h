#ifndef _TBLOGCOMPLETOSET_H_
	#define _TBLOGCOMPLETOSET_H_

#include "BaseSet.h"

class CTbLogCompletoSet : public CBaseSet
{
	DECLARE_DYNAMIC(CTbLogCompletoSet)

public:

	CTbLogCompletoSet();

	long m_lID;
	long m_lIDPaziente;
	long m_lIDEsame;
	CString m_sDataOra;
	CString m_sImpianto;
	CString m_sUtente;
	CString m_sStazione;
	CString m_sTabella;
	long m_lOperazione;
	CString m_sNomeChiave;
	long m_lValoreChiave;
	CString m_sCampo;
	CString m_sValoreOld;
	CString m_sValoreNew;

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //

	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //

};

#endif /* _TBLOGCOMPLETOSET_H_ */