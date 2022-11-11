#ifndef _PROTOCOLLOCOLONNESET_H_
	#define _PROTOCOLLOCOLONNESET_H_

#include "BaseSet.h"

class CProtocolloColonneSet : public CBaseSet
{

	DECLARE_DYNAMIC(CProtocolloColonneSet)

public:

	CProtocolloColonneSet();

	long m_lID;
	long m_lIDProtocollo;
	long m_lOrdine;
	CString m_sDescrizione;
	long m_lTipo;
	BOOL m_bValoriModificabili;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	//
	long AddRow(long lIDProtocollo, CString sDescrizione, long lTipo, BOOL bValoriModificabili);
	void EdtRow(long lID, CString sDescrizione, long lTipo, BOOL bValoriModificabili);
	void DelRow(long lID);

	void EdtOrder(long lID, long lOrdine);

	void DelAllProt(long lIDProtocollo);

	long FleuryTrans(long lIDProtocollo, CString sDescrizione);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _PROTOCOLLOCOLONNESET_H_ */