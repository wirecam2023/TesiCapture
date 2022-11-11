#pragma once

#include "BaseSet.h"

class CEsamiRefertoSezionatoSet : public CBaseSet
{
	DECLARE_DYNAMIC(CEsamiRefertoSezionatoSet)

public:
	
	CEsamiRefertoSezionatoSet();
	
	long m_lID;
	long m_lIDEsame;
	long m_lIDTipoReferto;
	long m_lIDTipoMateriale;
	CString m_sBasiTotali;
	CString m_sCoperturaMedia;
	CString m_sCoperturaPercentuale;	
	CString m_sUtenteRefertazione;
	CString m_sDataOraRefertazione;
	BOOL m_bEliminato;

	BOOL DeleteRecordset(const CString &strCommento);
	CString SetBaseFilter(const CString &strFilter);
	BOOL UpdateRecordset(const CString &strCommento);

	virtual CString GetDefaultSQL();
	
	BOOL SetNewReferto(long lIDEsame, long lIDTipoReferto, long lIDTipoMateriale,
		CString sBasiTotali, CString sCoperturaMedia, CString sCoperturaPercentuale);

	void GetLastReferto(long lIDEsame, long& lIDTipoReferto, long& lIDTipoMateriale,
		CString& sBasiTotali, CString& sCoperturaMedia, CString& sCoperturaPercentuale);
	
	BOOL SetEliminato(long lID);

	void GetIDList(CList<long>& listID);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);	
};

