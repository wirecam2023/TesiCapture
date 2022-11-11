#ifndef _INFERMIERISET_H_
	#define _INFERMIERISET_H_

#include "BaseSet.h"

class CInfermieriSet : public CBaseSet
{

	DECLARE_DYNAMIC(CInfermieriSet)

public:

	CInfermieriSet();

	long m_lContatore;
	CString m_sCognome;
	CString m_sNome;
	CString m_sTitolo;
	CString m_sMatricola;
	long m_lASL;
	CString m_sSede;
	CString m_sVia;
	CString m_sCitta;
	CString m_sCAP;
	CString m_sProvincia;
	CString m_sTelefono;
	CString m_sFax;
	CString m_sEmail;
	long m_lIDUserEndox;
	long m_lUO;
	BOOL m_bEliminato;

	// passo il contatore e mi ritorna il testo del relativo record //
	CString GetFieldText(long lContatore);
	CString GetMatricola(long lContatore);
	long GetContatoreFromUserID(long lUserID);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

private:

	virtual void	DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void	SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _INFERMIERISET_H_ */