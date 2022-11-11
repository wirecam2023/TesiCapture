#pragma once

#include "BaseSet.h"

class CTipiVariantiGeneticheSet : public CBaseSet
{

	DECLARE_DYNAMIC(CTipiVariantiGeneticheSet)

public:

	CTipiVariantiGeneticheSet();

	long m_lID;
	CString m_sCodice;
	CString m_sDescrizione;
	BOOL m_bObbligatorioCodiceVariante;
	BOOL m_bObbligatorioTipoAlterazione;
	CString m_sTestoRtf001;
	BOOL m_bEliminato;
	long m_lOrdine; //Julio BUG 3791 - Melhoria frases resultado laudo genomica
	BOOL m_bFraseRemovibile; //Julio BUG 3791 - Melhoria frases resultado laudo genomica
	BOOL m_bObbligatorioTrascrizione; //Julio BUG 3791 - Melhoria frases resultado laudo genomica

	BOOL DeleteRecordset(const CString &strCommento);
	CString SetBaseFilter(const CString &strFilter);
	BOOL UpdateRecordset(const CString &strCommento);	

	virtual CString GetDefaultSQL();	

	CString GetCodice(long lID);
	BOOL SetCodice(long lID, CString sCodice);

	CString GetDescrizione(long lID);
	BOOL SetDescrizione(long lID, CString sDescrizione);

	void GetObbligatori(long lID, BOOL& bCodiceVariante, BOOL& bTipoAlterazione, BOOL& bTrascrizione);
	BOOL SetObbligatori(long lID, BOOL bCodiceVariante, BOOL bTipoAlterazione, BOOL bTrascrizione);

	CString GetTestoRtf(long lID, long lPos);
	BOOL SetTestoRtf(long lID, long lPos, CString sTesto);

	long GetOrdine(long lID); //Julio BUG 3791 - Melhoria frases resultado laudo genomica
	BOOL SetOrdine(long lID, long lOrdine); //Julio BUG 3791 - Melhoria frases resultado laudo genomica

	BOOL GetFraseRemovibile(long lID); //Julio BUG 3791 - Melhoria frases resultado laudo genomica
	BOOL SetFraseRemovibile(long lID, BOOL bRemovibile); //Julio BUG 3791 - Melhoria frases resultado laudo genomica

	BOOL SetEliminato(long lID);

	void GetIDList(CList<long>& listID);

private:
	
	virtual void DoFieldExchange(CFieldExchange* pFX);	
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);
};