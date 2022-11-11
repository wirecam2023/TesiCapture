#pragma once

#include "BaseSet.h"

class CVistaTabellaStruttureParametriSet : public CBaseSet
{

	DECLARE_DYNAMIC(CVistaTabellaStruttureParametriSet)

public:

	CVistaTabellaStruttureParametriSet();

	long m_lIDTipoEsame;
	long m_lIDStruttura;
	CString m_sStruttura;
	long m_lIDParametro;
	CString m_sParametro;
	CString m_sFormula;
	long m_lDecimali;
	CString m_sUnitaDiMisura;
	CString m_sRiferimentoM;
	float m_fRiferimentoMmin;
	float m_fRiferimentoMmax;
	CString m_sRiferimentoF;
	float m_fRiferimentoFmin;
	float m_fRiferimentoFmax;
	CString m_sRiferimentoPed00;
	float m_fRiferimentoPed00min;
	float m_fRiferimentoPed00max;
	CString m_sRiferimentoPed01;
	float m_fRiferimentoPed01min;
	float m_fRiferimentoPed01max;
	CString m_sRiferimentoPed02;
	float m_fRiferimentoPed02min;
	float m_fRiferimentoPed02max;
	CString m_sRiferimentoPed03;
	float m_fRiferimentoPed03min;
	float m_fRiferimentoPed03max;
	CString m_sRiferimentoPed04;
	float m_fRiferimentoPed04min;
	float m_fRiferimentoPed04max;
	CString m_sRiferimentoPed05;
	float m_fRiferimentoPed05min;
	float m_fRiferimentoPed05max;
	CString m_sRiferimentoPed06;
	float m_fRiferimentoPed06min;
	float m_fRiferimentoPed06max;

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //

};
