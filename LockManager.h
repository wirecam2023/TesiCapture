#pragma once

#include "DLL_Imaging\h\AmLockEx.h"

class CLockManager
{
public:

	static CLockManager* Get();

	BOOL Initialize();
	BOOL Finalize();

	BOOL LockExam(long lExamID);
	BOOL LockPatient(long lPatientID);
	BOOL LockPatientAndAllExams(long lPatientID);
	BOOL LockUser(CString sUserToLock);
	BOOL UnlockExam(long lExamID);
	BOOL UnlockPatient(long lPatientID);
	BOOL UnlockPatientAndAllExams(long lPatientID);
	BOOL UnlockUser(CString sUserToUnlock);

private:

	CLockManager();
	~CLockManager();

	void BuildExamList(long lPatientID);

	static CLockManager m_LockManager;
	CList<long> m_listPatientExamLocked;

};
