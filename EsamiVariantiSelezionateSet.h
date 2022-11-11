#pragma once

#include "BaseSet.h"

class CEsamiVariantiSelezionateSet : public CBaseSet
{
	DECLARE_DYNAMIC(CEsamiVariantiSelezionateSet)

public:
	CEsamiVariantiSelezionateSet();
	long m_lID;
	long m_lIDEsame;
	long m_lIDVariante;
	long m_lOrdine;	
	long m_lGruppo;
	CString m_sUtenteRefertazione;
	CString m_sDataOraRefertazione;

	BOOL m_bEliminato;

	BOOL DeleteRecordset(const CString &strCommento);
	CString SetBaseFilter(const CString &strFilter);
	BOOL UpdateRecordset(const CString &strCommento);

	virtual CString GetDefaultSQL();

	BOOL SetNewSelection(long lIDEsame, long lIDVariante, long lOrdine, BOOL bDeleteGroup = FALSE);
	BOOL DeleteGroup(long lIDEsame, long lGruppo);
	void GetSelectionList(long lIDEsame, CList<long>& listIDVariante);

	BOOL SetEliminato(long lID);
	void GetIDList(CList<long>& listID);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);
};

