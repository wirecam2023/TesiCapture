#ifndef _WEBDEPLOYER_H_
	#define _WEBDEPLOYER_H_

#include "DLL_Imaging\h\amxmlgen.h"

class CMediciCurantiInviantiSet;
class CEsamiSet;

typedef enum websendmode 
{
	never = 0,
	manualsend,
	automaticsendforever,
	automaticsendonlyrequest
};

typedef enum operazione
{
	WD_OPERAZIONE_NEW = 0,
	WD_OPERAZIONE_MODIFY
};

class CWebDeployer
{

public:

	CWebDeployer(CDatabase* pDatabase);
	~CWebDeployer(void);

	BOOL Deploy(const CString* pStrSharePath, 
				const CString* pStrTo,
				const CString* pStrFrom,
				const CString* pStrSupplier,
				const CString* pStrPlacer,
				CPazientiSet* pPatient, 
				CEsamiSet* pExam, 
				const CImgList* pImgList,
				const CString* pPdfPath);

	BOOL DeployPatient(const CString *pStrSharePath, const CString *pStrTo, const CString *pStrFrom, CPazientiSet *pPatient, int operation);
	BOOL DeployDoctor(const CString *pStrSharePath, const CString *pStrTo, const CString *pStrFrom, CMediciCurantiInviantiSet *pMedici, int operation);
	BOOL DeployPasswordPatient(const CString *pStrSharePath, const CString *pStrTo, const CString *pStrFrom, long lContatore, CString strLogin);
	BOOL DeployPasswordDoctor(const CString *pStrSharePath, const CString *pStrTo, const CString *pStrFrom, long lContatore, CString strLogin);
	BOOL DeployReferto(const CString *pStrSharePath, const CString *pStrTo, const CString *pStrFrom, CPazientiSet* pPatient, CEsamiSet* pExam, const CImgList* pImgList, const CString* pPdfPath);

private:

	VOID FillData(amxmlgenphysiciandata* pData,
				  CPazientiSet* pPatient, 
				  CEsamiSet* pExam,
				  const CString* pStrTo,
				  const CString* pStrFrom,
				  const CString* pStrSupplier,
				  const CString* pStrPlacer);

	VOID FillNewPatientData(amxmlgenpatientdata* pData,
							CPazientiSet* pPatient, 
							const CString* pStrTo,
							const CString* pStrFrom
							);

	VOID FillModifyPatientData(amxmlgenpatientdata* pData,
							CPazientiSet* pPatient, 
							const CString* pStrTo,
							const CString* pStrFrom 
							);

	VOID FillNewDoctorData(amxmlgenphysiciandata* pData,
							CMediciCurantiInviantiSet* pMedici, 
							const CString* pStrTo,
							const CString* pStrFrom
							);

	VOID FillModifyDoctorData(amxmlgenphysiciandata* pData,
							CMediciCurantiInviantiSet* pMedici, 
							const CString* pStrTo,
							const CString* pStrFrom 
							);

	VOID FillReportData(amxmlgenreportdata* gendata, const CString* pStrTo, const CString* pStrFrom, CPazientiSet* pPatient, CEsamiSet* pExam);

	VOID FillAssignPasswordData(amxmlgenpassworddata* pData, const CString* pStrTo, const CString* pStrFrom, CString strLogin);

	BOOL CopyAttachments(const CImgList* pImgList,
						 const CString* pStrSharePath,
						 LONG lIdPatient,
						 LONG lIdExam);

	CDatabase* m_pDatabase;

};

#endif /* _WEBDEPLOYER_H_ */