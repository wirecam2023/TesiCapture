#pragma once

#include "BaseSet.h"

class CVistaRefertoGenomicaSet : public CBaseSet
{
	DECLARE_DYNAMIC(CVistaRefertoGenomicaSet)
public:
	CVistaRefertoGenomicaSet();

	long	m_lRefertoIDEsame;
	CString m_sRefertoBasiTotali;
	CString m_sRefertoCoperturaMedia;
	CString m_sRefertoCoperturaPercentuale;
	CString m_sRefertoUtente;
	CString m_sRefertoDataOra;
	CString m_sTipoRefertoCodice;
	CString m_sTipoRefertoTitolo;
	CString m_sTipoRefertoRTF001;
	CString m_sTipoRefertoRTF002;
	CString m_sTipoRefertoRTF003;
	CString m_sTipoRefertoRTF004;
	CString m_sTipoRefertoRTF005;
	CString m_sTipoRefertoRTF006;
	CString m_sTipoRefertoRTF007;
	CString m_sTipoRefertoRTF008;
	CString m_sTipoRefertoRTF009;
	CString m_sTipoRefertoRTF010;
	CString m_sTipoMaterialeCodice;
	CString m_sTipoMaterialeDescrizione;
	CString m_sTipoMaterialeRTF001;

	CString TryGetVaule(long lIDEsame, CString sColumn);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //

};