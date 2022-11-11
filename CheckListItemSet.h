#ifndef _CHECKLISTITEMSET_H_
	#define _CHECKLISTITEMSET_H_

#include "BaseSet.h"

class CCheckListItemSet : public CBaseSet
{

	DECLARE_DYNAMIC(CCheckListItemSet)

public:

	CCheckListItemSet();

	long m_lID;
	long m_lIDCheckList;
	long m_lIDPadre;
	long m_lOrdine;
	CString m_sTitolo;
	CString m_sTestoRTF;
	CString m_sTestoTXT;
	long m_lTestoNumeroVariabili;
	BOOL m_bItemAlmenoUno;
	BOOL m_bItemPiuDiUno;
	long m_lClassificazioneDiagnosi;
	// long m_lIDOriginaleClonato;
	BOOL m_bEliminato;

	// BOOL GetSceltaMultipla(long lID);
	// void GetTesti(long lID, CString& strRTF, CString& strTXT, long& lNumeroVariabili, long& lIDDiagnosi, CString& sDiagnosiCodice, CString& sDiagnosiDescrizione);
	// CString GetTestoVariabili(long lID);

	// mi serve per escludere i record segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _CHECKLISTITEMSET_H_ */