//Gabriel BUG 6225 - Lista DO
#pragma once

#ifndef _VISTAFLUSSODISTATOSET_H_
#define _VISTAFLUSSODISTATOSET_H_

#include "BaseSet.h"

class CVistaFlussoDiStatoSet : public CBaseSet
{
	DECLARE_DYNAMIC(CVistaFlussoDiStatoSet)
public:
	CVistaFlussoDiStatoSet();
	
	long m_lOrdineFase;
	long m_lIdOrdine;
	long m_IdEsame;
	CString	m_sCodEsame;
	CString m_sDataEsame;
	CString m_sDataOraConsegnaReferto;
	CString m_sDataEsameFormata;
	CString	m_sOraEsame;
	CString	m_sAssiden;
	CString	m_sNome;
	CString	m_sCognome;
	CString	m_sDataNascita;
	CString	m_sSesso;
	CString	m_sTipoEsame;
	CString	m_sDescrizioneEsame;
	CString	m_sSiglaEsame;
	long m_lIdUO;

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew(); // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //

};

#endif /* _VISTAFLUSSODISTATOSET_H_ */