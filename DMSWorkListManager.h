#ifndef _DMSWORKLISTMANAGER_H_
	#define _DMSWORKLISTMANAGER_H_

#include "EsamiView.h"

class CDMSWorkListManager : public CBaseSet
{
	DECLARE_DYNAMIC(CDMSWorkListManager)

public:

	CDMSWorkListManager(CEsamiView* pEsamiView);
	~CDMSWorkListManager();

	BOOL FillList(CListCtrlLocalize* pList, CString sCodVet);
	void PrepareList(CListCtrlLocalize* pList);
	BOOL SelectEntry(CListCtrlLocalize* pList, int iItem, CString dataSelezionata = "");
	BOOL CampiObbligatoriValorizzati(CDMSWorkListManager *prenotazione);
	void CostruisciFiltroPaziente(CString *filter, CDMSWorkListManager *prenotazione);

	void UpdateWithExamID(long lIDPrenotazione, long lIDEsame);
	void UpdateDatiEsame(long lIDEsame);

	long	m_lId,
		m_lIDEsameIns,
		m_lISTATNascita,
		m_lISTATResidenza,
		m_lSesso,
		m_lAsl,
		m_lIdSalaEndox,
		m_lIdSedeEndox,
		m_lIdRepartoEndox,
		m_lIDEndoxMedicoInviante,
		m_lProvenienzaEndox,
		m_lIDEndoxMedicoCurante,
		m_lDataNascitaCustom;

	CString	m_sOrderNumber,
			m_sDataEsame,
			m_sProvenienza,
			m_sCodiceSalaEsame,
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
			m_sDescrizioneReparto;
	CString m_sCodiceVetrino;
	CString m_sPosizioneVetrino;

	BOOL	m_bTrasferito,
			m_bAcqSegnalata,
			m_bAppuntamentoSegnalato,
			m_bEliminato;

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
};

#endif /* _DMSWORKLISTMANAGER_H_ */