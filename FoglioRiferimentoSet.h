//Gabriel BUG 6225 - Lista DO
#pragma once

#include "BaseSet.h"

class CFoglioRiferimentoSet : public CBaseSet
{
	DECLARE_DYNAMIC(CFoglioRiferimentoSet)

public:

	CFoglioRiferimentoSet();

	long m_lID;
	CString m_sDescrizione;
	long m_lUO;
	CString m_sCodicePrestazione;
	CString m_sPercorso;
	BOOL m_bEliminato;

	BOOL DeleteRecordset(const CString &strCommento);
	CString SetBaseFilter(const CString &strFilter);
	BOOL UpdateRecordset(const CString &strCommento);

	virtual CString GetDefaultSQL();

	CString GetDescrizione(long lID);
	BOOL SetDescrizione(long lID, CString sDescrizione);

	CString GetCodicePrestazione(long lID);
	BOOL SetCodicePrestazione(long lID, CString sCodice);

	CString GetPercorso(long lID);
	BOOL SetPercorso(long lID, CString sPercorso);

	void GetListaPercorso(CString sCodicePrestazione, long lUO, CList<CString>* pLista);

	BOOL GetEliminato(long lID);
	BOOL SetEliminato(long lID);

	void GetIDList(CList<long>& listID);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};