#pragma once

#include "BaseSet.h"

class CSezioniSet : public CBaseSet
{

	DECLARE_DYNAMIC(CSezioniSet)

public:

	CSezioniSet();

	long m_lID;
	long m_lIDTipoReferto;
	CString m_sCodice;
	long m_lIDTipoVariante;
	CString m_sTitoloRtf;	
	CString m_sTestoRtf001;
	long m_lOrdine;
	BOOL m_bRisultato;
	BOOL m_bEliminato;

	BOOL DeleteRecordset(const CString &strCommento);
	CString SetBaseFilter(const CString &strFilter);
	BOOL UpdateRecordset(const CString &strCommento);

	virtual CString GetDefaultSQL();

	CString GetCodice(long lID);
	BOOL SetCodice(long lID, CString sCodice);

	CString GetTitolo(long lID);
	BOOL SetTitolo(long lID, CString sTitolo);	

	CString GetTestoRtf(long lID, long lPos);
	BOOL SetTestoRtf(long lID, long lPos, CString sTesto);

	BOOL GetRisultato(long lID, long lIDTipoReferto);
	BOOL SetRisultato(long lID, BOOL bRisultato);
	BOOL VerifyRisultadoField(long lID, long lIDTipoReferto);
	CString GetRisultatoRtf();

	BOOL SetTipoReferto(long lID, long lIDTipoReferto);
	long GetTipoVariante(long lID);
	BOOL SetTipoVariante(long lID, long lIDTipoVariante);

	long GetOrdine(long lID);
	BOOL SetOrdine(long lID, long lOrdine);
	long GetNextMaxOrdine();
	long GetNextMaxOrdine(long p_lIDTipoReferto);
	void GetIDListWithOrdineLowerThanPos(CList<long>& listID, long lPos);
	void GetIDListWithOrdineGreaterThanPos(CList<long>& listID, long lPos);
	long GetIDByOrdine(long lOrdine);

	BOOL SetEliminato(long lID);

	void GetIDList(CList<long>& listID);
	void GetIDListByTipoReferto(CList<long>& listID, long lIDTipoReferto);
	long GetRisultatoID(long lIDTipoReferto);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);
};
