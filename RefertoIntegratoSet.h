#pragma once

#include "BaseSet.h"

//Julio - BUG 3744 - Retorno do Pathox para o TesiCapture

class CRefertoIntegratoSet : public CBaseSet
{
	DECLARE_DYNAMIC(CRefertoIntegratoSet)
public:
	CRefertoIntegratoSet();

	long m_lID;
	long m_lIDEsame;
	CString m_sRTFMacro;
	CString m_sRTFDiag;
	CString m_sSignature;
	long m_lStatoImportazione;
	BOOL m_bToClose;
	BOOL m_bEliminato;
	
	BOOL DeleteRecordset(const CString &strCommento);
	CString SetBaseFilter(const CString &strFilter);
	BOOL UpdateRecordset(const CString &strCommento);

	virtual CString GetDefaultSQL();
	virtual void SetEmpty();
	virtual void CopyFieldFrom(CRefertoIntegratoSet* pSet, BOOL bEmpty = TRUE);
	int GetEditMode();
private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);
};

