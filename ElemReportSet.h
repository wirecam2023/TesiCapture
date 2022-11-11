#ifndef _ELEMREPORTSET_H_
	#define _ELEMREPORTSET_H_

#include "BaseSet.h"

class CElemReportSet : public CBaseSet
{

	DECLARE_DYNAMIC(CElemReportSet)

public:

	CElemReportSet();

	long	m_nContatore;
	long	m_lIDHeaderFooter;
	CString	m_strType;
	CString	m_strValue;
	long	m_nLeft;
	long	m_nRight;
	long	m_nTop;
	long	m_nBottom;
	long	m_nCheck;
	long	m_nColor;
	long	m_nParam;
	CString	m_strFontName;
	long	m_nFontFamily;
	long	m_nFontHeight;
	long	m_nFontWeight;
	long	m_nFontUnder;
	long	m_nFontItalic;
	int		m_nAlignment;
	int		m_nRotation;
	BOOL    m_bEliminato;

	// mi serve per escludere i record segnati come cancellati
	CString SetBaseFilter(const CString &strFilter);

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato
	BOOL DeleteRecordset(const CString &strCommento);

	//
	long AddRow(long lIDHeaderFooter, CString strType, CString strValue, long nLeft, long nRight, long nTop, long nBottom, long nCheck, long nColor, long nParam, CString strFontName, long nFontFamily, long nFontHeight, long nFontWeight, long nFontUnder, long nFontItalic, int nAlignment, int nRotation);
	void EdtRow(long lContatore, CString sValue);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _ELEMREPORTSET_H_ */