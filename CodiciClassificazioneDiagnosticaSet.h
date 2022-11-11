#ifndef _CODICICLASSIFICAZIONEDIAGNOSTSET_H_
	#define _CODICICLASSIFICAZIONEDIAGNOSTSET_H_

#include "BaseSet.h"

class CCodiciClassificazioneDiagnostSet : public CBaseSet
{
	DECLARE_DYNAMIC(CCodiciClassificazioneDiagnostSet)

public:

	CCodiciClassificazioneDiagnostSet();

	long m_lID;
	CString m_sCodice;
	CString m_sDescrizione;
	long m_lClassificazione;
	BOOL m_bPositivita;
	float m_fScore;
	long m_lIDTipoEsame;
	long m_lUO;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

	long FleuryTrans(CString sCodice, CString sDescrizione);
	long GetLongClassificazione(long lID);
	CString GetStringCodice(long lID);
	CString GetStringDescrizione(long lID);
	void GetStringCodiceDescrizione(long lClassificazioneDiagnosi, CString& sDiagnosiCodice, CString& sDiagnosiDescrizione);

	float GetMaxScore();

	virtual CString GetDefaultSQL();

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _CODICICLASSIFICAZIONEDIAGNOSTSET_H_ */