#pragma once

#include "BaseSet.h"

class CVistaVariantiGeneticheSet : public CBaseSet
{
	DECLARE_DYNAMIC(CVistaVariantiGeneticheSet)
public:
	CVistaVariantiGeneticheSet();
	
	long	m_lVarianteID;
	CString m_sVarianteTitolo;
	CString m_sVarianteCodice;
	CString m_sVarianteTrascrizione;
	CString m_sVarianteCromossoma;
	CString m_sVarianteGene;
	CString m_sVariantePosizione;
	CString m_sVarianteHGVSc;
	CString m_sVarianteHGVSp;
	CString m_sTipoVarianteCodice;
	CString m_sTipoVarianteDescrizione;
	CString m_sTipoVarianteRTF001;
	CString m_sPatogenicitaCodice;
	CString m_sPatogenicitaDescrizione;
	BOOL	m_bPatogenicitaPositivita;
	CString m_sTipiAlterazioneCodice;
	CString m_sTipiAlterazioneDescrizione;

	CString TryGetVaule(long lIDVariante, CString sColumn);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //

};