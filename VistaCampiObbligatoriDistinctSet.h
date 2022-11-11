#ifndef _VISTACAMPIOBBLIGATORIDISTINCTSET_H_
#define _VISTACAMPIOBBLIGATORIDISTINCTSET_H_

#include "BaseSet.h"

class CVistaCampiObbligatoriDistinctSet : public CBaseSet
{

	DECLARE_DYNAMIC(CVistaCampiObbligatoriDistinctSet)

public:

	CVistaCampiObbligatoriDistinctSet();

	long m_lID;		
	long m_lCampo;
	long m_lFase;
	long m_lIDFaseNew;
	CString m_sTipiEsame;
	CString m_sProvenienze;
	long m_lUO;

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //

};

#endif /* _VISTACAMPIOBBLIGATORIDISTINCTSET_H_ */