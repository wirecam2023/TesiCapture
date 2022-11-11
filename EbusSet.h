#ifndef _EBUSSET_H_
	#define _EBUSSET_H_

#include "BaseSet.h"

class CEbusSet : public CBaseSet
{

	DECLARE_DYNAMIC(CEbusSet)

public:

	CEbusSet();

	long m_lID;
	long m_lIDEsame;
	CString m_sDimensione_12R;
	CString m_sDimensione_11R;
	CString m_sDimensione_10R;
	CString m_sDimensione_4R;
	CString m_sDimensione_2R;
	CString m_sDimensione_7;
	CString m_sDimensione_2L;
	CString m_sDimensione_4L;
	CString m_sDimensione_10L;
	CString m_sDimensione_11L;
	CString m_sDimensione_12L;
	CString m_sPuntura_12R;
	CString m_sPuntura_11R;
	CString m_sPuntura_10R;
	CString m_sPuntura_4R;
	CString m_sPuntura_2R;
	CString m_sPuntura_7;
	CString m_sPuntura_2L;
	CString m_sPuntura_4L;
	CString m_sPuntura_10L;
	CString m_sPuntura_11L;
	CString m_sPuntura_12L;
	CString m_sNumeroPunture_12R;
	CString m_sNumeroPunture_11R;
	CString m_sNumeroPunture_10R;
	CString m_sNumeroPunture_4R;
	CString m_sNumeroPunture_2R;
	CString m_sNumeroPunture_7;
	CString m_sNumeroPunture_2L;
	CString m_sNumeroPunture_4L;
	CString m_sNumeroPunture_10L;
	CString m_sNumeroPunture_11L;
	CString m_sNumeroPunture_12L;
	CString m_sForma_12R;
	CString m_sForma_11R;
	CString m_sForma_10R;
	CString m_sForma_4R;
	CString m_sForma_2R;
	CString m_sForma_7;
	CString m_sForma_2L;
	CString m_sForma_4L;
	CString m_sForma_10L;
	CString m_sForma_11L;
	CString m_sForma_12L;
	CString m_sMargine_12R;
	CString m_sMargine_11R;
	CString m_sMargine_10R;
	CString m_sMargine_4R;
	CString m_sMargine_2R;
	CString m_sMargine_7;
	CString m_sMargine_2L;
	CString m_sMargine_4L;
	CString m_sMargine_10L;
	CString m_sMargine_11L;
	CString m_sMargine_12L;
	CString m_sEcogenicita_12R;
	CString m_sEcogenicita_11R;
	CString m_sEcogenicita_10R;
	CString m_sEcogenicita_4R;
	CString m_sEcogenicita_2R;
	CString m_sEcogenicita_7;
	CString m_sEcogenicita_2L;
	CString m_sEcogenicita_4L;
	CString m_sEcogenicita_10L;
	CString m_sEcogenicita_11L;
	CString m_sEcogenicita_12L;
	CString m_sFilo_12R;
	CString m_sFilo_11R;
	CString m_sFilo_10R;
	CString m_sFilo_4R;
	CString m_sFilo_2R;
	CString m_sFilo_7;
	CString m_sFilo_2L;
	CString m_sFilo_4L;
	CString m_sFilo_10L;
	CString m_sFilo_11L;
	CString m_sFilo_12L;
	CString m_sNecrosi_12R;
	CString m_sNecrosi_11R;
	CString m_sNecrosi_10R;
	CString m_sNecrosi_4R;
	CString m_sNecrosi_2R;
	CString m_sNecrosi_7;
	CString m_sNecrosi_2L;
	CString m_sNecrosi_4L;
	CString m_sNecrosi_10L;
	CString m_sNecrosi_11L;
	CString m_sNecrosi_12L;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _EBUSSET_H_ */