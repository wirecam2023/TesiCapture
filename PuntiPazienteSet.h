#ifndef _PUNTIPAZIENTESET_H_
	#define _PUNTIPAZIENTESET_H_

#include "BaseSet.h"

class CPuntiPazienteSet : public CBaseSet
{

	DECLARE_DYNAMIC(CPuntiPazienteSet)

public:

	CPuntiPazienteSet();

	long m_lID;
	long m_lIDPaziente;
	long m_lX;
	long m_lY;
	CString m_sSede;
	long m_lPattern;
	BOOL m_bSemioticaA;
	BOOL m_bSemioticaB;
	BOOL m_bSemioticaC;
	BOOL m_bSemioticaD;
	BOOL m_bReticoloPigmentario;
	long m_lReticoloPigmentarioColore;
	long m_lReticoloPigmentarioDistanza;
	long m_lReticoloPigmentarioSpessore;
	BOOL m_bVenatureRamificate;
	BOOL m_bPigmentazioneDiffusa;
	long m_lPigmentazioneDiffusaDistrib;
	BOOL m_bGlobuliMarroni;
	long m_lGlobuliMarroniForma;
	long m_lGlobuliMarroniSede;
	BOOL m_bPuntiPigmentati;
	BOOL m_bPuntiNeri;
	long m_lPuntiNeriDistribuzione;
	long m_lPuntiNeriSede;
	long m_lPuntiNeriCalibro;
	BOOL m_bVeloBiancastro;
	BOOL m_bDepigmentazione;
	long m_lDepigmentazioneDistribuzione;
	long m_lDepigmentazioneSede;
	BOOL m_bDepigmentazioneReticolare;
	BOOL m_bAreeDepigmentate;
	BOOL m_bAreeGrigieBlu;
	BOOL m_bFlussiRadiali;
	BOOL m_bPseudopodi;
	BOOL m_bBlocchiNeri;
	BOOL m_bCistiMiliaLike;
	BOOL m_bPeppering;
	BOOL m_bAreaFogliaAcero;
	BOOL m_bLaghiVascolari;
	BOOL m_bAsportazione;
	long m_lDiagnosiIstologica;
	CString m_sNotizieAccessorie;

	CString m_sDiagnosiEpimicroscopica;
	long m_lTumoriMelanociticiBenigni1;
	long m_lTumoriMelanociticiMaligni1;
	long m_lTumoriNonMelanociticiEpitel1;
	long m_lTumoriNonMelanociticiVascol1;
	CString m_sDiagnosiClinicaAltre;
	BOOL m_bEsameIstologico;
	CString m_sRefertoNumero;
	CString m_sRefertoData;
	long m_lTumoriMelanociticiBenigni2;
	CString m_sDiagnosiIstologicaAltro1;
	long m_lTumoriMelanociticiMaligni2;
	CString m_sSpessoreDiBreslow;
	long m_lLivelloDiClark;
	CString m_sDiagnosiIstologicaAltro2;
	long m_lTumoriNonMelanociticiEpitel2;
	long m_lTumoriNonMelanociticiVascol2;
	CString m_sDiagnosiIstologicaAltro3;
	long m_lNumeroDermox;
	long m_lUO;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco UpdateRecordset per salvare in automatico la UO per tutti i nuovi record //
	BOOL UpdateRecordset(const CString &strCommento);

	//
	long GetMaxNumeroDermox(long lIDPaziente);
	void GetSedeNumero(long lIDPunto, CString& sReturn, long& lReturn);
	void GetXYNumero(long lIDPunto, CPoint& ptReturn, long& lReturn);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _PUNTIPAZIENTESET_H_ */