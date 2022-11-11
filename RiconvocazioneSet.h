//Gabriel BUG 6225 - Lista DO
#pragma once

#include "BaseSet.h"

class CRiconvocazioneSet : public CBaseSet
{
	DECLARE_DYNAMIC(CRiconvocazioneSet)

public:

	CRiconvocazioneSet();

	long m_lId;
	long m_lIdEsame; 
	CString m_sFicha;
	CString m_sDataOraEsame;
	CString m_sDataOraRiconvocazione;
	CString m_sUtente;
	CString m_sUnita;
	CString m_sMarca;
	CString m_sUnitaRiconvocazione;
	long m_lIdMedicoRiconvocazione;
	CString m_sCodicePrestazioneRiconvocazione;
	CString m_sCodicePrestazione;
	CString m_sPreparazione;
	long m_lIdMotivo;
	CString m_sDescrizioneMotivo;
	CString m_sMotivoAnnullamento;
	BOOL m_bBloccaEsame;
	BOOL m_bPassivoDeReferto;
	CString m_sCorpoEmail;
	CString m_sInviatoA;
	BOOL m_bEseguito;
	CString m_sEsito;
	BOOL m_bEliminato;

	BOOL DeleteRecordset(const CString &strCommento);
	CString SetBaseFilter(const CString &strFilter);
	BOOL UpdateRecordset(const CString &strCommento);

	virtual CString GetDefaultSQL();

	BOOL SetEliminato(long lID);
	BOOL SetMotivoAnnullamento(long lID, CString sMotivo);
	long GetIdFromIdEsame(long lIdEsame);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};
