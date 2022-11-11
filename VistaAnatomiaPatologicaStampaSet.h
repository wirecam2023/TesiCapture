#ifndef _VISTAANATOMIAPATOLOGICASTAMPASET_H_
	#define _VISTAANATOMIAPATOLOGICASTAMPASET_H_

#include "BaseSet.h"

class CVistaAnatomiaPatologicaStampaSet : public CBaseSet
{

public:

	CVistaAnatomiaPatologicaStampaSet();

	DECLARE_DYNAMIC(CVistaAnatomiaPatologicaStampaSet)

	CString m_sCognome;
	CString m_sNome;
	long m_lDataNascita;
	long m_lIDEsame;
	long m_lDataEsame;
	CString m_sSedeEsame;
	CString m_sDataOraSpeditoMetafora;
	long m_lProvenienza;
	CString m_sOspedale;
	CString m_sReparto;

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //

};

#endif /* _VISTAANATOMIAPATOLOGICASTAMPASET_H_ */