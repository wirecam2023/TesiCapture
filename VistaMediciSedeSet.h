#ifndef _VISTAMEDICISEDESET_H_
	#define _VISTAMEDICISEDESET_H_

#include "BaseSet.h"
#include "QueryFormListDlg.h"

class CVistaMediciSedeSet : public CBaseSet
{

	DECLARE_DYNAMIC(CVistaMediciSedeSet)

public:

	CVistaMediciSedeSet();

	long m_lContatore;
	CString m_sCodice;
	CString m_sTitolo;
	CString m_sCognome;
	CString m_sNome;
	BOOL m_bLibero;
	BOOL m_bEliminato;
	long m_lUO;

	// mi serve per escludere i record di altre UO e quelli segnati come cancellati //
	CString SetBaseFilter(const CString &strFilter);

	// Sandro 15/12/2015 // RAS 20150065 //
	void FillListByAll(CList<CQueryFormListDlg::tagITEM>* pListRecord);
	void FillListByCodice(CString sCodice, CList<CQueryFormListDlg::tagITEM>* pListRecord);
	void FillListByCodiceLike(CString sCodice, CList<CQueryFormListDlg::tagITEM>* pListRecord);
	void FillListByContatore(long lContatore, CList<CQueryFormListDlg::tagITEM>* pListRecord);
	void FillListByDescrizione(CString sDescrizione, CList<CQueryFormListDlg::tagITEM>* pListRecord);
	void FillListByDescrizioneLike(CString sDescrizione, CList<CQueryFormListDlg::tagITEM>* pListRecord);
	void FillListByFilter(CList<CQueryFormListDlg::tagITEM>* pListRecord);

private:

	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultSQL();
	virtual void SetEmpty();

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //
	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //

};

#endif /* _VISTAMEDICISEDESET_H_ */