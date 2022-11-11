#ifndef _MONITORAGGIOSET_H_
	#define _MONITORAGGIOSET_H_

#include "BaseSet.h"

class CMonitoraggioSet : public CBaseSet
{
	DECLARE_DYNAMIC(CMonitoraggioSet)

public:

	CMonitoraggioSet();

	long m_lID;
	long m_lIDEsame;
	long m_lQuando;
	CString m_strOra;
	long m_lIdInfermiere;
	CString m_strFC;
	CString m_strPA;
	CString m_strSat;
	CString m_strO2;
	CString m_strMida;
	CString m_strPeti;
	CString m_strAtro;
	CString m_strNalo;
	CString m_strFlum;
	CString m_strScop;
	CString m_strGluc;
	CString m_strAltri;
	long m_lDoloreVAS;
	long m_lDoloreNRS;
	long m_lDoloreWB;
	long m_lDoloreCCPO1;
	long m_lDoloreCCPO2;
	long m_lDoloreCCPO3;
	long m_lDoloreCCPO4;
	long m_lDoloreCCPO5;
	long m_lPuntiScore1;
	long m_lPuntiScore2;
	long m_lPuntiScore3;
	long m_lPuntiScore4;
	long m_lTotalScore;
	long m_lPuntiScore1Glasgow;
	long m_lPuntiScore2Glasgow;
	long m_lPuntiScore3Glasgow;
	long m_lTotalScoreGlasgow;
	long m_lIdPdf;
	CString m_sNotePdf;
	BOOL m_bTerminato;
	CString m_sIdSessione;
	CString m_sNomeStazione;
	long m_lIdDispositivo;
	CString m_sIdEsterno;
	BOOL m_bEliminato;

	long m_lFCPolso;
	CString m_strETCO2;
	long m_lIntubazione;
	long m_lDoloreScala;
	long m_lVentilazione;
	CString m_strVentilazioneVt;
	CString m_strVentilazioneFr;
	long m_lDoloreLocalizzazione;
	CString m_sDoloreLocalizzazioneDettaglio;
	long m_lDoloreCaratteristiche;
	long m_lDoloreFrequenza;
	long m_lDoloreDurata;
	long m_lRamsay;

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

	long GetIdEsame(long id);

	void CopyFrom(CMonitoraggioSet* sourceSet);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _MONITORAGGIOSET_H_ */