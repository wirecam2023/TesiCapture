#pragma once

#include "BaseSet.h"

class CExtEsamiFasiChiuseSet : public CBaseSet
{
	DECLARE_DYNAMIC(CExtEsamiFasiChiuseSet)

public:

	CExtEsamiFasiChiuseSet();

	long m_lID;
	long m_lIDFaseChiusa;	
	long m_lEseguito;
	long m_lIDUtente;// Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
	CString m_sEsito;// Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo

	long Insert(long lIDEsame, long lIDFaseChiusa);
	void DelecaoLogicaExt(long lIDFaseChiusa); // Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};