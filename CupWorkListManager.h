#ifndef _CUPWORKLISTMANAGER_H_
	#define _CUPWORKLISTMANAGER_H_

#include "EsamiView.h"

class CListSortableCtrl;

class CCupWorkListManager : public CBaseSet
{
	DECLARE_DYNAMIC(CCupWorkListManager)

public:

	CCupWorkListManager(CEsamiView* pEsamiView);
	~CCupWorkListManager();

	// mi serve per escludere i record di altre UO //
	CString SetBaseFilter(const CString &strFilter);

	BOOL FillList(CListSortableCtrl* pList, CString sAddFilter, CString sDataFilter);
	void PrepareList(CListSortableCtrl* pList);
	BOOL SelectEntry(CListSortableCtrl* pList, int iItem);
	BOOL CampiObbligatoriValorizzati(long idRichiesta);
	BOOL CostruisciFiltroPazienteEx(CString *filter, CCupWorkListManager *prenotazione);
	long GetIdFromEsameIns(long idEsameIns);
	BOOL AbortIP(CListSortableCtrl* pList, int iItem);
	BOOL IsExamAbortable(CListSortableCtrl* pList, int iItem);
	BOOL SetNoShow(CListSortableCtrl* pList, int iItem, long lIDMotivo);
	BOOL AbortNoShow(CListSortableCtrl* pList, int iItem);

	void DeleteOldRequest(long idWorklist, long lIDEsame);
	void UpdateEsamiChiusi(long lIDEsame);
	void UpdateWithExamID(long lIDPrenotazione, long lIDEsame);
	void UpdateDatiEsame(long lIDPaziente, long lIDEsame, CString sTesto94, CString sTesto95, CString sTesto96);

	BOOL CCupWorkListManager::SelectEntryFaseCheckForMistakenLastAdd(); //Julio Correcao do problema de exames em pacientes errados

	static void LoadIntoMemory();

	long	m_lId,
			m_lIDEsameIns,
			m_lISTATNascita,
			m_lISTATResidenza,
			m_lSesso,
			m_lIdSalaEndox,
			m_lIdSedeEndox,
			m_lIdRepartoEndox,
			m_lIDEndoxMedicoInviante,
			m_lIDEndoxMedicoCurante,
			m_lDataNascitaCustom,
			m_lStatoAccettazione,
			m_lIdUO,
			m_lIdProvenienzaNew,
			m_lStatoTCP; //Gabriel - TCP FIX

	CString	m_sOrderNumber,
			m_sDataEsame,
			m_sSalaEsame,
			m_sProvenienza,
			m_sCodiceAgenda,
			m_sNote,
			m_sCodiceRepartoInviante,
			m_sCodiceMedicoInviante,
			m_sNosologico,
			m_sUrgenza,
			m_sIdProvetta,
			m_sAssiden,
			m_sCognome,
			m_sCognome2,
			m_sNome,
			m_sDataNascita,
			m_sIndirizzoResidenza,
			m_sCapResidenza,
			m_sTelefono1,
			m_sTelefono2,
			m_sCellulare1,
			m_sCellulare2,
			m_sCodiceFiscale,
			m_sCodiceSanitario,
			m_sCodiceMedicoCurante,
			m_sCodiceCittadinanza,
			m_sCittadinanza,
			m_sMedicoInviante,
			m_sMedicoCurante,
			m_sDescrizioneSala,
			m_sDescrizioneSede,
			m_sComuneNascita,
			m_sComuneResidenza,
			m_sDescrizioneReparto,
			m_sDescrizioneMedicoInvianteEst,
			m_sDescrizioneComuneNascitaEst,
			m_sDescrizioneComuneResidenzaEst,
			m_sDescrizioneMedicoCuranteEst,
			m_sDescrizioneCittadinanzaEst,
			m_sProvincia,
			m_sProvinciaEst,
			m_sRepartoInviante,
			m_sDataRichiesta,
			m_sUOEst,
			m_sIdEpisodioRicovero,
			m_sDataRicovero,
			m_sUlssResidenza,
			m_sCodiceSTP,
			m_sCodiceIstAssicurativa,
			m_sCodiceTEAM,
			m_sCodiceEsenzione,
			m_sDescrizioneProvenienzaNew,
			m_sQuesitoDiagnostico,
			m_sQuesitoDiagnosticoCodificato,
			m_sIdentificazionePassaporto, //Julio - BUG 3285 - Adequação de laudos
			m_sIdentificazioneDoc1,       //Julio - BUG 3285 - Adequação de laudos
			m_sIdentificazioneDoc2,       //Julio - BUG 3285 - Adequação de laudos
			//Gabriel - P3
			m_sCodiceMedicoInviante2,
			m_sDescrizioneMedicoInviante2Est,
			m_sMedicoInviante2,
			m_sCodiceMedicoInviante3,
			m_sDescrizioneMedicoInviante3Est,
			m_sMedicoInviante3,
			m_sCodiceMedicoInviante4,
			m_sDescrizioneMedicoInviante4Est,
			m_sMedicoInviante4,
			m_sOrderNumberCorrelati; //Gabriel - TCP

	BOOL	m_bTrasferito,
			m_bAcqSegnalata,
			m_bAppuntamentoSegnalato,
			m_bEliminato,
			m_bErogazioneSegnalata,
			m_bCertificazioneMEF,
			m_bCertificazioneSISS,
			m_bOscuramentoVolontario,
			m_bPagamentoRicevuto;
			// m_bImporting;

	BOOL	m_bTipoEsameDlg;

	int		m_iColumn;

	BOOL	m_bColumnsP3;
	BOOL	m_bColumnsTCP; //Gabriel - TCP
		
protected:

	void DoFieldExchange(CFieldExchange* pFX);
	CString GetDefaultSQL();

	CEsamiView* m_pEsamiView;
	CImageList m_ImageList;

private:

	CBaseSet* CreateNew() { return NULL; } // è una vista //
	void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //

	BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //

	// Sandro 05/03/2014 //

	int SelectEntryFasePreliminare(long lItemData, long &idTipoEsameTemp);
	BOOL SelectEntryFaseImportazionePaziente(long &lCurPazCode);
	BOOL SelectEntryFaseImportazioneEsame(long &lCurPazCode, long &idTipoEsameTemp, CString sDataSelezionata);

};

#endif /* _CUPWORKLISTMANAGER_H_ */