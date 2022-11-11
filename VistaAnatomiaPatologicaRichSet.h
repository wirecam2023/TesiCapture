#ifndef _VISTAANATOMIAPATOLOGICARICHSET_H_
	#define _VISTAANATOMIAPATOLOGICARICHSET_H_

#include "BaseSet.h"

class CVistaAnatomiaPatologicaRichSet : public CBaseSet
{

	DECLARE_DYNAMIC(CVistaAnatomiaPatologicaRichSet)

public:

	CVistaAnatomiaPatologicaRichSet();

	long m_lIDPaziente;
	long m_lIDEsame;
	CString m_sCognome;
	CString m_sNome;
	long m_lNatoIlCustom;
	long m_lTipoEsame;
	//CString m_sTipoEsame;
	long m_lData;
	long m_lMedico;
	//CString m_sMedico;
	// long m_lAssistente;
	long m_lProvenienza;
	CString m_sProvenienza2;
	long m_lStato;
	int m_nAnatomiaSpedireRitirare;
	BOOL m_bAnatomiaRefertato;
	BOOL m_bAnatomiaVerificato;
	BOOL m_bAnatomiaSpeditoRitirato;
	CString m_sDataAnatomiaVerificato;
	CString m_sDataAnatomiaSpeditoRitirato;
	long m_lTipoDegenzaEsterno;

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //
};

#endif /* _VISTAANATOMIAPATOLOGICARICHSET_H_ */