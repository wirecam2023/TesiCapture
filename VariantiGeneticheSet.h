#pragma once

#include "BaseSet.h"

#define FILTER_MAX_COUNT 50

class CVariantiGeneticheSet : public CBaseSet
{

	DECLARE_DYNAMIC(CVariantiGeneticheSet)

public:

	CVariantiGeneticheSet();

	long m_lID;
	CString m_sTitolo;
	long m_lIDTipoVariante;
	CString m_sCodice;
	CString m_sTrascrizione;
	long m_lIDPatogenicita;
	CString m_sCromossoma;
	CString m_sGene;
	CString m_sPosizioneGene;	
	long m_lIDTipoAlterazione;
	CString m_sHGVSc;
	CString m_sHGVSp;
	BOOL m_bEliminato;	

	BOOL DeleteRecordset(const CString &strCommento);
	CString SetBaseFilter(const CString &strFilter);
	BOOL UpdateRecordset(const CString &strCommento);		
	
	virtual CString GetDefaultSQL();
	
	void Filter(CList<long>& listID, CString sTitolo, long lIDTipoVariante, CString sCodice, CString sTrascrizione, long lIDPatogenicita,
		CString sCromossoma, CString sGene, CString sPosizioneGene, long lIDTipoAlterazione, CString HGVSc, CString HGVSp);

	CString GetTitolo(long lID);
	BOOL SetTitolo(long lID, CString sTitolo);
	BOOL CheckTitolo(CString sTitolo); //Returns true if the title already exists

	CString GetCodice(long lID);
	BOOL SetCodice(long lID, CString sCodice);

	CString GetTrascrizione(long lID);
	BOOL SetTrascrizione(long lID, CString sTrascrizione);

	CString GetCromossoma(long lID);
	BOOL SetCromossoma(long lID, CString sCromossoma);
	
	CString GetGene(long lID);
	BOOL SetGene(long lID, CString sGene);

	CString GetPosizioneGene(long lID);
	BOOL SetPosizioneGene(long lID, CString sPosizioneGene);

	CString GetHGVSc(long lID);
	BOOL SetHGVSc(long lID, CString sHGVSc);

	CString GetHGVSp(long lID);
	BOOL SetHGVSp(long lID, CString sHGVSp);

	long GetIDTipoVariante(long lID);
	BOOL SetIDTipoVariante(long lID, long lIDTipoVariante);

	long GetIDPatogenicita(long lID);
	BOOL SetIDPatogenicita(long lID, long lIDPatogenicita);

	long GetIDTipoAlterazione(long lID);
	BOOL SetIDTipoAlterazione(long lID, long lIDTipoAlterazione);

	void GetAllFields(long lID, 
		CString& sTitolo, CString& sCodice, CString& sTrascrizione, CString& sCromossoma,
		CString& sGene, CString& sPosizioneGene, CString& sHGVSc, CString& sHGVSp,
		long& lIDTipoVariante, long& lIDPatogenicita, long& lIDTipoAlterazione);

	BOOL SetEliminato(long lID);
	void GetIDList(CList<long>& listID);

private:
	
	virtual void DoFieldExchange(CFieldExchange* pFX);	
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);
};