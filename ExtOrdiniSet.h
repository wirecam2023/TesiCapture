#ifndef _EXTORDINISET_H_
	#define _EXTORDINISET_H_

#include "BaseSet.h"

class CExtOrdiniSet : public CBaseSet
{
	DECLARE_DYNAMIC(CExtOrdiniSet)

public:

	CExtOrdiniSet();

	long m_lID;
	CString m_sOrderNumber;				// 50
	CString m_sDataEsame;				// 14
	CString m_sProvenienza;				// 50
	CString m_sCodiceAgenda;			// 50
	CString m_sNote;					// text
	CString m_sCodiceRepartoInviante;	// 50
	CString m_sCodiceMedicoInviante;	// 50
	CString m_sMedicoInviante;			// 50
	CString m_sNosologico;				// 50
	CString m_sUrgenza;					// 50
	long m_lIDEsameIns;
	BOOL m_bTrasferito;
	CString m_sIDProvetta;				// 50
	BOOL m_bAcqSegnalata;
	BOOL m_bErogazioneSegnalata;
	BOOL m_bAppuntamentoSegnalato;
	BOOL m_bEliminato;
	CString m_sAssIden;					// 50
	CString m_sCognome;					// 50
	CString m_sCognome2;				// 50
	CString m_sNome;					// 50
	long m_lDataNascitaCustom;
	CString m_sDataNascita;				// 8
	long m_lIstatNascita;
	CString m_sComuneNascita;			// 50
	CString m_sIndirizzoResidenza;		// 255
	long m_lIstatResidenza;
	CString m_sComuneResidenza;			// 50
	CString m_sCapResidenza;			// 5
	CString m_sTelefono1;				// 50
	CString m_sTelefono2;				// 50
	CString m_sCellulare1;				// 50
	CString m_sCellulare2;				// 50
	CString m_sCodiceFiscale;			// 16
	CString m_sCodiceSanitario;			// 50
	CString m_sCodiceSTP;				// 50
	CString m_sCodiceTEAM;				// 50
	long m_lSesso;
	long m_lAsl;
	CString m_sCodiceMedicoCurante;		// 50
	CString m_sMedicoCurante;			// 50
	CString m_sCodiceCittadinanza;		// 50
	CString m_sCittadinanza;			// 50
	CString m_sDataRichiesta;			// 14
	CString m_sRepartoInviante;			// 50
	CString m_sProvincia;				// 2
	long m_lStatoAccettazione;
	CString m_sUO;						// 50
	CString m_sIDEpisodioRicovero;		// 50
	CString m_sDataRicovero;			// 50
	BOOL m_bCertificazioneMEF;
	BOOL m_bCertificazioneSISS;
	CString m_sCodAlfa;					// 50
	CString m_sUlssResidenza;			// 10
	CString m_sQuesitoDiagnostico;		// text
	CString m_sCodiceIstAssicurativa;
	long m_lIDMotivo;
	//Luiz - 13/05/2019 - P3 - Atualiza nome/sobrenome Médico - Inclui Médicos solicitantes
	CString m_sMedicoInviante2;			// 50
	CString m_sMedicoInviante3;			// 50
	CString m_sMedicoInviante4;			// 50

	CString m_sOrderNumberCorrelati;	//Gabriel - TCP
	long m_lStatoTCP;	//Gabriel - TCP FIX

	CString m_sIdentificazionePassaporto; //Julio - BUG 3285 - Adequação de laudos
	CString m_sIdentificazioneDoc1;       //Julio - BUG 3285 - Adequação de laudos
	CString m_sIdentificazioneDoc2;       //Julio - BUG 3285 - Adequação de laudos

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	//
	CString GetAssiden(long lID);
	void GetDataFromFichaItem(CString sFichaItem, long &lID, long& lIDEsameIns);
	CString GetPriorityFromID(long lIDEsame);
	BOOL IsExtOrdiniRequest(long idEsame);
	BOOL SetStatoRichiesta(const long lIDEsame, const long lStato);
	long GetOrdineId(long lIdEsame); //Gabriel BUG 6225 - Lista DO
	BOOL m_bColumnsTCP; //Gabriel - TCP

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual CBaseSet* CreateNew();

};

#endif /* _EXTORDINISET_H_ */