#pragma once

#include "BaseSet.h"

class CFrasiRisultatoSet : public CBaseSet
{

	DECLARE_DYNAMIC(CFrasiRisultatoSet)

public:
	CFrasiRisultatoSet();

	long m_lID;
	long m_lIDTipoVariante; //Julio BUG 3791 - Melhoria frases resultado laudo genomica
	//long m_lIDPatogenicita; //Julio BUG 3791 - Melhoria frases resultado laudo genomica

	CString m_sTitoloRisultato; //Julio BUG 3791 - Melhoria frases resultado laudo genomica
	CString m_sTitoloComplemento; //Julio BUG 3791 - Melhoria frases resultado laudo genomica
	
	CString m_sPositivoSingolare;
	CString m_sPositivoPlurale;
	CString m_sPositivoVariante;
	CString m_sNegativoSingolare;
	CString m_sNegativoNegativo;

	CString m_sComplementoSingolare;
	CString m_sComplementoPlurale;	
	CString m_sComplementoVariante;
	CString m_sComplementoNegativo;
	
	BOOL m_bEliminato;

	BOOL DeleteRecordset(const CString &strCommento);
	CString SetBaseFilter(const CString &strFilter);
	BOOL UpdateRecordset(const CString &strCommento);

	virtual CString GetDefaultSQL();

	//Julio BUG 3791 - Melhoria frases resultado laudo genomica
	CString GetTitoloRisultato();
	BOOL SetTitoloRisultato(CString sTitolo);

	CString GetTitoloComplemento();
	BOOL SetTitoloComplemento(CString sTitolo);

	CString GetPositivoSingolare();
	BOOL SetPositivoSingolare(CString sPosSing);

	CString GetPositivoPlurale();
	BOOL SetPositivoPlurale(CString sPosPlur);

	CString GetPositivoVariante();
	BOOL SetPositivoVariante(CString sPosVari);

	CString GetNegativoSingolare(); 
	BOOL SetNegativoSingolare(CString sNegSing); 

	CString GetNegativoNegativo();
	BOOL SetNegativoNegativo(CString sNegNeg);
	
	CString GetComplementoSingolare(long lIDTipoVariante);
	BOOL SetComplementoSingolare(long lIDTipoVariante, CString sComSing);

	CString GetComplementoPlurale(long lIDTipoVariante);
	BOOL SetComplementoPlurale(long lIDTipoVariante, CString sComPlur);

	CString GetComplementoVariante(long lIDTipoVariante);
	BOOL SetComplementoVariante(long lIDTipoVariante, CString sComVari);

	CString GetComplementoNegativo(long lIDTipoVariante);
	BOOL SetComplementoNegativo(long lIDTipoVariante, CString sComNeg);		
	//

	BOOL SetEliminato(long lID);
	void GetIDList(CList<long>& listID);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);


};

