#ifndef _VIEWLOGIMPORTAZIONECASISET_H_
	#define _VIEWLOGIMPORTAZIONECASISET_H_

#include "BaseSet.h"

class CViewLogImportazioneCasiSet : public CBaseSet
{
	DECLARE_DYNAMIC(CViewLogImportazioneCasiSet)

public:

	CViewLogImportazioneCasiSet();

	long m_lID;
	long m_lIDPaziente;
	CString m_sCognome;
	CString m_sNome;
	long m_lIDEsameOrigine;
	CString m_sCodiceEsternoEsameOrigine;
	CString m_sTipoEsameOrigine;
	long m_lIDEsameDestinazione;
	CString m_sCodiceEsternoEsameDestinazione;
	CString m_sTipoEsameDestinazione;
	CString m_sDataOra;
	CString m_sUtente;
	CString m_sStazione;

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //

	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //

};

#endif /* _VIEWLOGIMPORTAZIONECASISET_H_ */