#ifndef _DOCMANAGER_H_
	#define _DOCMANAGER_H_

#include "DLL_Imaging\h\AMDocManager.h"

#define DOCUMENTS_NOT_EXPORT	0
#define DOCUMENTS_ONLY_EXPORT	1
#define DOCUMENTS_ALL			2

class CMyDocManager
{

public:

	CMyDocManager();
	~CMyDocManager();

	long GetAttachedDocNumberPatient(const long lIDPatient);
	long GetAttachedDocNumberExam(const long lIDExam, const long lWhat);
	BOOL GetAttachedDocListPatient(const long lIDPatient, CList<DOC>* pList);
	BOOL GetAttachedDocListExam(const long lIDExam, const long lWhat, CList<DOC>* pList);
	BOOL ImportDoc(const long lIDPaziente, const long lIDEsame, const CString sDescrizione, const CString sDataPersonalizzabile, const CString sFile, const BOOL bDaEsportare);
	long ImportDocRemoto(const long lIDPaziente, const long lIDEsame, const long lVersione, const CString sData, const long lTipo, const CString sDescrizione, const CString sUtente, const CString sDataPersonalizzazile, const CString sEstensione, const CString sNomeFileOriginale, const BOOL bDaEsportare, const CString sPercorsoFileRemoto);
	long ImportDocTiffMP(const long lIDPaziente, const long lIDEsame, const CString sDescrizione, const CString sDataPersonalizzabile, const CStringList* pPathList, const BOOL bDaEsportare, long& lTiffID);
	BOOL DeleteDoc(const long lDocID);
	BOOL EditDoc(const long lDocID, const CString sDescrizione, const CString sDataPersonalizzabile);
	BOOL MoveDocPatient(const long lOldPatientID, const long lNewPatientID);
	BOOL MoveDocExam(const long lOldPatientID, const long lNewPatientID, const long lExamID);

	BOOL CopyToLocal(const long lDocID);

private:

	BOOL m_bInit;

};

#endif /* _DOCMANAGER_H_ */