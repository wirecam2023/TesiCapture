#ifndef _COMMENTIIMMAGINISET_H_
	#define _COMMENTIIMMAGINISET_H_

#include "BaseSet.h"

class CCommentiImmaginiSet : public CBaseSet
{

	DECLARE_DYNAMIC(CCommentiImmaginiSet)

public:

	CCommentiImmaginiSet();

	long m_lID;
	long m_lIDTipoEsame;
	CString m_sCommento;
	BOOL m_bEliminato;

	// ridefinisco DeleteRecordset (in realtà cambia flag eliminato) //
	BOOL DeleteRecordset(const CString &strCommento);

	// mi serve per escludere i record segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// 

	long AddRow(long lIDTipoEsame, const CString &sCommentoImmagine);
	BOOL EdtRow(long lIDDaModificare, const CString &sCommentoImmagine);
	BOOL DelRow(long lIDDaEliminare);

private:

	virtual void	DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void	SetEmpty();

	virtual CBaseSet* CreateNew();
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll);
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento);

};

#endif /* _COMMENTIIMMAGINISET_H_ */