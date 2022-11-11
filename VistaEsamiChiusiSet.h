#ifndef _VISTAESAMICHIUSISET_H_
#define _VISTAESAMICHIUSISET_H_

#include "EsamiView.h"

class CVistaEsamiChiusiSet : public CBaseSet
{
	DECLARE_DYNAMIC(CVistaEsamiChiusiSet)

public:

	CVistaEsamiChiusiSet();
	~CVistaEsamiChiusiSet();

	CString	m_sDataOra,
			m_sTipologia,
			m_sEsito,
			m_sCodEsame;

	long	m_lIdEsame,
			m_lIdPdf,
			m_lIdUtente,
			m_lIdChiusura,
			m_lTipologiaWorklist,
			m_lIdPaziente,
			m_lEseguito;

protected:

	void DoFieldExchange(CFieldExchange* pFX);
	CString GetDefaultSQL();

private:

	CBaseSet* CreateNew() { return NULL; } // è una vista //
	void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //

	BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //

};

#endif /* _VISTAESAMICHIUSISET_H_ */