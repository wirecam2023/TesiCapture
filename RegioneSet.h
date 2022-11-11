#ifndef _REGIONESET_H_
	#define _REGIONESET_H_

#include "BaseSet.h"
//#include "Define.h"

class CRegioneSet : public CBaseSet
{

	DECLARE_DYNAMIC(CRegioneSet)

public:

	CRegioneSet();

	long m_lContatore;
	long m_lEsame;
	long m_lCodice;
	long m_lQuantita;
	long m_lIdExtPrestazione;
	long m_lStatoCUP;
	// CString m_sRUR;
	// CString m_sNRE;
	// CString m_sIUP;
	// prescriptionBlockResult m_lEsitoBlocco;
	CString m_sTipoAccesso;
	CString m_sNotaPrestazione;
	CString m_sNotaPrescrizione;
	BOOL m_bPrescrizionePinzataSuOriginale;
	BOOL m_bEliminato;

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

	void CopyFieldFrom(CRegioneSet* pSet);
	CString GetFieldText(long lEsame);
	CString GetStringDescrizioni(long lEsame);
	CString GetStringDescrizioniGrande(long lEsame);
	BOOL ExamHasPrestazioniNonNormate(long lEsame);
	BOOL ExamHasNotNormedServicesWithoutPrescription(long lEsame);
	long GetIdExt(long lIdPrestazione);
	BOOL ExamHasOriginalRURPrescription(long lIDEsame);
	CString GetPrestazioniWithoutPrescriptionListAsString(long lIDEsame);
	//void SetCosto(long lContatore, CString sCosto);

	virtual void SetEmpty();

private:
	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _REGIONESET_H_ */