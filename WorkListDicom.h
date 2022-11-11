#pragma once

#include "WorkListManager.h"

class CWorkListDicom : public CWorkListManager
{
	DECLARE_DYNAMIC(CWorkListDicom)
	
public:

	CWorkListDicom(CEsamiView* pEsamiView);

	void DoFieldExchange(CFieldExchange* pFX);
	BOOL FillList(CListCtrl* pList, CString strAddFilter);
	void PrepareList(CListCtrl* pList);
	BOOL SelectEntry(CListCtrl* pList, int iItem);
	BOOL InsertStudySerie(long lPatientID, long lExamID);
	virtual CString GetDefaultSQL();
	BOOL InsertExam(CString strAccessionNumber, long lPatientID);

	CString m_sPatientUID;
	CString m_sPatientLastName;
	CString m_sPatientFirstName;
	CString m_sPatientBornDate;
	long m_lPatientSex;
	CString m_sExamDate;
	long m_lExamType;
	CString m_sExamTypeDescription;
	CString m_sAccessionNumber;
	CString m_sStudyUidProposed;
	CString m_sSerieUidProposed;
	CString m_sNotes;
	CString m_sSiteDescription;

protected:

	CImageList m_ImageList;
};
