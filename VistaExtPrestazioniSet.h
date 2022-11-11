#ifndef _VISTAEXTPRESTAZIONISET_H_
	#define _VISTAEXTPRESTAZIONISET_H_

#include "BaseSet.h"

class CVistaExtPrestazioniSet : public CBaseSet
{

	DECLARE_DYNAMIC(CVistaExtPrestazioniSet)

public:

	CVistaExtPrestazioniSet();
	
	// mi serve per escludere i record di altre UO //
	CString SetBaseFilter(const CString &strFilter);

	long m_lId;
	long m_lIdOrdine;
	CString m_sIdPrestazione;
	CString m_sCodicePrestazione;
	CString m_sDescrizionePrestazione;
	CString m_sNote;
	long m_lQuantita;
	BOOL m_bEliminato;
	CString m_sCodiceNazionale;
	CString m_sCodiceRegionale;
	CString m_sDescrizioneEndox;
	CString m_sTipoEsame;
	CString m_sSiglaTipoEsame;
	long m_lIdTipoEsameEndox;
	long m_lIdPrestazioneEndox;

	CString GetIdPrestazione(long idPrestazione);
	
private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //
};

#endif /* _VISTAEXTPRESTAZIONISET_H_ */