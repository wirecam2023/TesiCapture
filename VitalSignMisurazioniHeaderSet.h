#ifndef _VITALSIGNMISURAZIONIHEADERSET_H_
	#define _VITALSIGNMISURAZIONIHEADERSET_H_

#include "BaseSet.h"

class CVitalSignMisurazioniHeaderSet : public CBaseSet
{
	DECLARE_DYNAMIC(CVitalSignMisurazioniHeaderSet)

public:

	CVitalSignMisurazioniHeaderSet();

	long m_lID;
	long m_lIDEsame;
	CString m_sIDSessioneVitalSign;
	MonitoringPhase m_lFase;
	CString m_sOra;
	CString m_sFCMedia;
	CString m_sPAMedia;
	CString m_sSatMedia;
	long m_lIDPdf;
	CString m_sNote;
	BOOL m_bTerminato;
	CString m_sNomeStazione;
	long m_lIDDispositivo;
	BOOL m_bEliminato;

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

	long GetIdEsame(long id);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);
};

#endif /*_VITALSIGNMISURAZIONIHEADERSET_H_*/