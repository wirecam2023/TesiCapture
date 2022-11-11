#ifndef _MEDICITRENTOSET_H_
	#define _MEDICITRENTOSET_H_

#include "BaseSet.h"

class CMediciTrentoSet : public CBaseSet
{

public:

	CMediciTrentoSet();
	DECLARE_DYNAMIC(CMediciTrentoSet)

	long m_lCOD_VER;
	CString m_sCOD_MEDICO_MG;
	CString m_sCOD_FISCALE_MMG;
	CString m_sMEDICO_MG;
	long m_lCOD_VER_COMUNE_RESIDENZA_MMG;
	CString m_sCOD_COMUNE_RESIDENZA_MMG;
	CString m_sINDIRIZZO_RESIDENZA_MMG;
	CString m_sCAP_RESIDENZA_MMG;
	CString m_sCOD_DISTRETTO_AMBITO_MMG;
	CString m_sINDIRIZZO_AMBULATORIO_MMG;
	CString m_sCAP_AMBULATORIO_MMG;
	long m_lCOD_VER_COMUNE_AMBULATORIO_MMG;
	CString m_sCOD_COMUNE_AMBULATORIO_MMG;
	CString m_sCOD_TIPO_MEDICO_MG;
	long m_lASSISTITI_MMG;
	CString m_sDATA_INSERIMENTO;
	CString m_sDATA_VARIAZIONE;
	CString m_sDATA_CESSAZIONE;
	CString m_sNOTE;

	virtual void SetEmpty();

	virtual CString GetDefaultSQL();
	virtual void DoFieldExchange(CFieldExchange* pFX);

	void GetFieldText(CString strContatore, CString& strNominativo, CString& strTelefono, CString& strIndirizzo);

private:

	virtual CBaseSet* CreateNew() { return NULL; }
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; }

};

#endif /* _MEDICITRENTOSET_H_ */