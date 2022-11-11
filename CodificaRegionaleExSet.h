#ifndef _CODIFICAREGIONALEEXSET_H_
	#define _CODIFICAREGIONALEEXSET_H_

#include "BaseSet.h"

class CCodificaRegionaleExSet : public CBaseSet
{

	DECLARE_DYNAMIC(CCodificaRegionaleExSet)

public:

	CCodificaRegionaleExSet();

	long m_lContatore;

	CString m_sCodiceNazionale;
	CString m_sCodiceRegionale;
	CString m_sCodiceSiss;
	CString m_sDescrizione;

	float m_fEndoscopistaNumero;
	float m_fEndoscopistaMinuti;
	float m_fEndoscopistaCosto;			// A1
	float m_fAnestesistaNumero;
	float m_fAnestesistaMinuti;
	float m_fAnestesistaCosto;			// A2
	float m_fRadiologoNumero;
	float m_fRadiologoMinuti;
	float m_fRadiologoCosto;			// B
	float m_fInfermiereNumero;
	float m_fInfermiereMinuti;
	float m_fInfermiereCosto;			// C
	float m_fOtaaNumero;
	float m_fOtaaMinuti;
	float m_fOtaaCosto;					// D
	float m_fAmministrativoNumero;
	float m_fAmministrativoMinuti;
	float m_fAmministrativoCosto;		// E
	float m_fTotaleCostoPersonale;		// F = A1 + A2 + B + C + D + E

	float m_fTotaleCostoMateriali;		// G

	float m_fManutenzioneDedicata;		// H
	float m_fManutenzioneBase;			// I
	float m_fTotaleCostoManutenzione;	// L = H + I

	float m_fAmmortamentoDedicata;		// M
	float m_fAmmortamentoBase;			// N
	float m_fTotaleCostoAmmortamento;	// O = M + N

	float m_fTotaleCostiGenerali;		// P = ( F + G + L + O ) / 5     --> 20% del totale

	float m_fTotaleGlobale;				// Q = F + G + L + O + P

	float m_fRimborsoRegionale;

	CString m_sCodiceIntegrazione;
	CString m_sCodiceDicom;
	long m_lIDTipoEsameEndox;
	BOOL m_bPrestazionePrincipale;

	BOOL m_bNormata;
	BOOL m_bPNGLA;

	long m_lUO;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

	//
	CString GetFieldText(long lContatore);
	CString GetStringCodiceNazionale(long lContatore);
	CString GetStringCodiceRegionale(long lContatore);
	CString GetStringDescrizione(long lContatore);
	CString GetStringCodiceSiss(long lContatore);
	CString GetStringCodiceIntegrazione(long lContatore);
	BOOL IsNormata(long lCodice);
	void GetListaCodice(CList<CString>& pLista); //Gabriel BUG 6225 - Lista DO
	long GetContatore(CString sCodiceIntegrazione); //Gabriel BUG 6225 - Lista DO

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _CODIFICAREGIONALEEXSET_H_ */