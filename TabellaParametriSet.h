#ifndef _TABELLAPARAMETRISET_H_
	#define _TABELLAPARAMETRISET_H_

#include "BaseSet.h"

class CTabellaParametriSet : public CBaseSet
{

	DECLARE_DYNAMIC(CTabellaParametriSet)

public:

	CTabellaParametriSet();

	long m_lID;
	long m_lIDStruttura;
	long m_lOrdine;
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
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	//
	long FleuryTrans(long lIDStruttura, CString sParametro);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _TABELLAPARAMETRISET_H_ */