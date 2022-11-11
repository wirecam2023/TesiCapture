#ifndef _CONFIGURAZIONILISTAPRENOTAZIONISET_H_
	#define _CONFIGURAZIONILISTAPRENOTAZIONISET_H_

#include "BaseSet.h"

class CConfigurazioniListaPrenotazioniSet : public CBaseSet
{

	DECLARE_DYNAMIC(CConfigurazioniListaPrenotazioniSet)

public:

	CConfigurazioniListaPrenotazioniSet();

	long m_lID;
	long m_lOrdine;
	CString m_sTitolo;
	CString m_sCampo;
	BOOL m_bVisibile;
	long m_lDimensione;
	long m_lDimensioneStampaPerc;
	BOOL m_bEliminato;

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);


};

#endif /* _CONFIGURAZIONILISTAPRENOTAZIONISET_H_ */