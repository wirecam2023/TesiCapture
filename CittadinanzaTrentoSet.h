#ifndef _CITTADINANZATRENTOSET_H_
	#define _CITTADINANZATRENTOSET_H_

#include "BaseSet.h"

class CCittadinanzaTrentoSet : public CBaseSet
{

public:

	CCittadinanzaTrentoSet();
	DECLARE_DYNAMIC(CCittadinanzaTrentoSet)

	CString m_sUE;
	CString m_sCONVENZIONE;
	CString m_sSTP;
	long	m_lCOD_VER;
	CString m_sCOD_CITTADINANZA;
	CString m_sCITTADINANZA;
	CString m_sNOTE;
	CString m_sNAZIONE;

	virtual void SetEmpty();

	virtual CString GetDefaultSQL();
	virtual void DoFieldExchange(CFieldExchange* pFX);

	CString GetCittadinanza(CString strCodCittadinanza);
	CString GetCodCittadinanza(CString strCittadinanza);

private:

	virtual CBaseSet* CreateNew() { return NULL; }
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; }

};

#endif /* _CITTADINANZATRENTOSET_H_ */