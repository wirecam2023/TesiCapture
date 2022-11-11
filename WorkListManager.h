#ifndef _WORKLISTMANAGER_H_
	#define _WORKLISTMANAGER_H_

#include "EsamiView.h"

class CWorkListManager : public CBaseSet
{
	DECLARE_DYNAMIC(CWorkListManager)

public:

	static CWorkListManager* Create(CEsamiView* pEsamiView);
	~CWorkListManager();

	// mi serve per escludere i record di altre UO //
	CString SetBaseFilter(const CString &strFilter);

	virtual BOOL FillList(CListCtrl* pList, CString strAddFilter = "") = 0;
	virtual void PrepareList(CListCtrl* pList) = 0;
	virtual BOOL SelectEntry(CListCtrl* pList, int iItem) = 0;

	void UpdateWithExamID(long lIDPrenotazione, long lIDEsame);

protected:

	CWorkListManager(CEsamiView* pEsamiView);

	virtual void DoFieldExchange(CFieldExchange* pFX) = 0;
	virtual CString GetDefaultSQL();

	CEsamiView* m_pEsamiView;

private:

	virtual CBaseSet* CreateNew() { return NULL; } // è una vista //
	virtual void CopyFields(CBaseSet* pOriginalSet, BOOL bCopyAll) { ; } // è una vista //
	virtual void SaveLog(CBaseSet* pOldValues, CBaseSet* pNewValues, const CString &sCommento) { ; } // è una vista //

	virtual BOOL DeleteRecordset(const CString &strCommento) { ASSERT(FALSE); return FALSE; } // è una vista //
};

#endif /* _WORKLISTMANAGER_H_ */