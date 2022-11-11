#ifndef _VISTAREFERTIPAZIENTESET_H_
	#define _VISTAREFERTIPAZIENTESET_H_

#include "BaseSet.h"

class CVistaRefertiPazienteSet : public CBaseSet
{

	DECLARE_DYNAMIC(CVistaRefertiPazienteSet)

public:

	CVistaRefertiPazienteSet();

	// long m_lIDPaziente;
	long m_lIDEsame;
	CString m_sTipoEsame;
	long m_lData;
	CString m_sReferto;

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //

};

#endif /* _VISTAREFERTIPAZIENTESET_H_ */