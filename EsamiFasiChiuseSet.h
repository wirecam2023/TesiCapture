#pragma once

#include "BaseSet.h"

class CEsamiFasiChiuseSet : public CBaseSet
{
	DECLARE_DYNAMIC(CEsamiFasiChiuseSet)

public:

	CEsamiFasiChiuseSet();

	long m_lID;	
	long m_lIDEsame;
	long m_lIDFase;
	long m_lIDPdf;
	CString m_sDataOra;
	long m_lIDUtente;
	BOOL m_bEliminato;
	CString m_sMotivo; // Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo

	long Insert(long lIDEsame, long lIDFase, long lIDPdf);
	long DelecaoLogicaComMotivo(long lIDEsame, long lIDFase, CString sMotivo); // Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
	BOOL FaseAbertaExame(long lIDEsame, long lIDFase); // Luiz - 01/04/2019 - P3 - Processa nova fase - Libera Laudo
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