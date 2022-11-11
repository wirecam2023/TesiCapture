#include "stdafx.h"
#include "Endox.h"
#include "WebDeployer.h"

#include "DLL_Imaging\h\ImgManager.h"

#include "CustomDate.h"
#include "EsamiSet.h"
#include "MediciCurantiInviantiSet.h"
#include "PazientiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWebDeployer::CWebDeployer(CDatabase* pDatabase)
{
	ASSERT(pDatabase != NULL);

	m_pDatabase = pDatabase;
}

CWebDeployer::~CWebDeployer(void)
{
}

VOID CWebDeployer::FillData(amxmlgenphysiciandata* pData, CPazientiSet* pPatient, CEsamiSet* pExam, const CString* pStrTo, const CString* pStrFrom, const CString* pStrSupplier, const CString* pStrPlacer)
{
	/*CString strPatientDataFmt;
	if (!pPatient->IsFieldNull(&pPatient->m_lNatoIlCustom) && pPatient->m_lNatoIlCustom > 0)
		strPatientDataFmt = CCustomDate(pPatient->m_lNatoIlCustom).GetDate("%Y-%m-%d");
	else
		strPatientDataFmt = "0001-01-01";

	// CString strExamDataFmt;
	CString strExamDataOraFmt;
	if (!pExam->IsFieldNull(&pExam->m_lData) && pExam->m_lData > 0)
	{
		// strExamDataFmt = CCustomDate(pExam->m_lData).GetDate("%Y-%m-%d");
		strExamDataOraFmt = CCustomDate(pExam->m_lData).GetDate("%Y-%m-%dT%H:%M:00");
	}
	else
	{
		// strExamDataFmt = "0001-01-01";
		strExamDataOraFmt = "0001-01-01T00:00:00";
	}

	_snprintf_s((*pData).To, 50, *pStrTo);
	_snprintf_s((*pData).From, 50, *pStrFrom);
	_snprintf_s((*pData).IdLocationSupplier, 50, *pStrSupplier);
	_snprintf_s((*pData).RequestIdLocationPlacer, 50, *pStrPlacer);
	_snprintf_s((*pData).RequestStatus, 50, "Completed");
	_snprintf_s((*pData).RequestPriority, 50, "Normal");
	_snprintf_s((*pData).PatientSurname, 50, pPatient->m_sCognome);
	_snprintf_s((*pData).PatientName, 50, pPatient->m_sNome);
	_snprintf_s((*pData).PatientDateTimeOfBirth, 50, strPatientDataFmt);
	_snprintf_s((*pData).PatientBirthPlace, 50, pPatient->m_sNatoA);
	_snprintf_s((*pData).PatientEmail, 50, ""); // pPatient->m_s);
	_snprintf_s((*pData).PatientFiscalCode, 50, pPatient->m_sCodFisc);
	_snprintf_s((*pData).PatientSanitaryCode, 50, pPatient->m_sCodSanit);
	
	switch(pPatient->m_lSessoPaz)
	{
		case 0:
		{
			_snprintf_s((*pData).PatientSex, 50, "Male");
			break;
		}
		case 1:
		{
			_snprintf_s((*pData).PatientSex, 50, "Female");
			break;
		}
		default:
		{
			_snprintf_s((*pData).PatientSex, 50, "Unknown");
			break;
		}
	}
	
	_snprintf_s((*pData).DateTime, 50, strExamDataOraFmt);
	_snprintf_s((*pData).RequestDateTime, 50, strExamDataOraFmt);
	_snprintf_s((*pData).RequestDrawingDateTime, 50, strExamDataOraFmt);
	_snprintf_s((*pData).PatientMobilePhoneNumber, 50, ""); // pPatient->m_tel2);*/
}

VOID CWebDeployer::FillNewPatientData(amxmlgenpatientdata* pData, CPazientiSet* pPatient, const CString* pStrTo, const CString* pStrFrom)
{
	CString strPatientDataFmt;
	if (!pPatient->IsFieldNull(&pPatient->m_lNatoIlCustom) && pPatient->m_lNatoIlCustom > 0)
		strPatientDataFmt = CCustomDate(pPatient->m_lNatoIlCustom).GetDate("%Y-%m-%d");
	else
		strPatientDataFmt = "0001-01-01";

	_snprintf_s((*pData).To, 50, *pStrTo);
	_snprintf_s((*pData).From, 50, *pStrFrom);
	_snprintf_s((*pData).Type, 50, "Insert");
	_snprintf_s((*pData).ObserverUserLogin, 50, pPatient->m_sLogin);
	(*pData).ObserverUserDisabled = FALSE;
	_snprintf_s((*pData).ObserverUserExpiringDate, 50, "");
	(*pData).ObserverUserSendEmail = pPatient->m_bSendEmail;
	(*pData).ObserverUserSendSms = pPatient->m_bSendSms;
	_snprintf_s((*pData).ObserverSurname, 50, pPatient->m_sCognome);
	_snprintf_s((*pData).ObserverSecondSurname, 50, pPatient->m_sCognome2);
	_snprintf_s((*pData).ObserverName, 50, pPatient->m_sNome);
	_snprintf_s((*pData).ObserverDateTimeOfBirth, 50, strPatientDataFmt);
	_snprintf_s((*pData).ObserverFiscalCode, 50, pPatient->m_sCodFisc);
	_snprintf_s((*pData).ObserverSanitaryCode, 50, pPatient->m_sCodSanit);
	_snprintf_s((*pData).ObserverNosographicCode, 50, "");
	_snprintf_s((*pData).ObserverEmail, 50, pPatient->m_sEmail);
	_snprintf_s((*pData).ObserverPhoneNumber, 50, pPatient->m_sTelefono1);
	_snprintf_s((*pData).ObserverMobilePhoneNumber, 50, pPatient->m_sCellulare1);
	
	switch(pPatient->m_lSessoPaz)
	{
		case 0:
		{
			_snprintf_s((*pData).ObserverSex, 50, "Male");
			break;
		}
		case 1:
		{
			_snprintf_s((*pData).ObserverSex, 50, "Female");
			break;
		}
		default:
		{
			_snprintf_s((*pData).ObserverSex, 50, "Unknown");
			break;
		}
	}
}

VOID CWebDeployer::FillModifyPatientData(amxmlgenpatientdata* pData, CPazientiSet* pPatient, const CString* pStrTo, const CString* pStrFrom)
{
	CString strPatientDataFmt;
	if (!pPatient->IsFieldNull(&pPatient->m_lNatoIlCustom) && pPatient->m_lNatoIlCustom > 0)
		strPatientDataFmt = CCustomDate(pPatient->m_lNatoIlCustom).GetDate("%Y-%m-%d");
	else
		strPatientDataFmt = "0001-01-01";

	_snprintf_s((*pData).To, 50, *pStrTo);
	_snprintf_s((*pData).From, 50, *pStrFrom);
	_snprintf_s((*pData).Type, 50, "Update");
	_snprintf_s((*pData).ObserverUserLogin, 50, pPatient->m_sLogin);
	(*pData).ObserverUserDisabled = FALSE;
	_snprintf_s((*pData).ObserverUserExpiringDate, 50, "");
	(*pData).ObserverUserSendEmail = pPatient->m_bSendEmail;
	(*pData).ObserverUserSendSms = pPatient->m_bSendSms;
	_snprintf_s((*pData).ObserverSurname, 50, pPatient->m_sCognome);
	_snprintf_s((*pData).ObserverSecondSurname, 50, pPatient->m_sCognome2);
	_snprintf_s((*pData).ObserverName, 50, pPatient->m_sNome);
	_snprintf_s((*pData).ObserverDateTimeOfBirth, 50, strPatientDataFmt);
	_snprintf_s((*pData).ObserverFiscalCode, 50, pPatient->m_sCodFisc);
	_snprintf_s((*pData).ObserverSanitaryCode, 50, pPatient->m_sCodSanit);
	_snprintf_s((*pData).ObserverNosographicCode, 50, "");
	_snprintf_s((*pData).ObserverEmail, 50, pPatient->m_sEmail);
	_snprintf_s((*pData).ObserverPhoneNumber, 50, pPatient->m_sTelefono1);
	_snprintf_s((*pData).ObserverMobilePhoneNumber, 50, pPatient->m_sCellulare1);
	
	switch(pPatient->m_lSessoPaz)
	{
		case 0:
		{
			_snprintf_s((*pData).ObserverSex, 50, "Male");
			break;
		}
		case 1:
		{
			_snprintf_s((*pData).ObserverSex, 50, "Female");
			break;
		}
		default:
		{
			_snprintf_s((*pData).ObserverSex, 50, "Unknown");
			break;
		}
	}
}

//MEDICI
VOID CWebDeployer::FillNewDoctorData(amxmlgenphysiciandata* pData, CMediciCurantiInviantiSet* pMedici, const CString* pStrTo, const CString* pStrFrom)
{
	_snprintf_s((*pData).To, 50, *pStrTo);
	_snprintf_s((*pData).From, 50, *pStrFrom);
	_snprintf_s((*pData).Type, 50, "Insert");
	_snprintf_s((*pData).ObserverUserLogin, 50, pMedici->m_sLogin);
	(*pData).ObserverUserDisabled = FALSE;
	_snprintf_s((*pData).ObserverUserExpiringDate, 50, "");
	//(*pData).ObserverUserSendEmail = pMedici->m_bSendEmail;
	(*pData).ObserverUserSendEmail = TRUE;
	_snprintf_s((*pData).ObserverSurname, 50, pMedici->m_sCognome);
	_snprintf_s((*pData).ObserverSecondSurname, 50, "");
	_snprintf_s((*pData).ObserverName, 50, pMedici->m_sNome);
	_snprintf_s((*pData).ObserverIdNumber, 50, "");
	_snprintf_s((*pData).ObserverEmail, 50, pMedici->m_sEmail);
	_snprintf_s((*pData).ObserverPhoneNumber, 50, pMedici->m_sTelefono);
}

VOID CWebDeployer::FillModifyDoctorData(amxmlgenphysiciandata* pData, CMediciCurantiInviantiSet* pMedici, const CString* pStrTo, const CString* pStrFrom)
{
	_snprintf_s((*pData).To, 50, *pStrTo);
	_snprintf_s((*pData).From, 50, *pStrFrom);
	_snprintf_s((*pData).Type, 50, "Update");
	_snprintf_s((*pData).ObserverUserLogin, 50, pMedici->m_sLogin);
	(*pData).ObserverUserDisabled = FALSE;
	_snprintf_s((*pData).ObserverUserExpiringDate, 50, "");
	//(*pData).ObserverUserSendEmail = pPatient->m_bSendEmail;
	(*pData).ObserverUserSendEmail = TRUE;
	_snprintf_s((*pData).ObserverSurname, 50, pMedici->m_sCognome);
	_snprintf_s((*pData).ObserverSecondSurname, 50, "");
	_snprintf_s((*pData).ObserverName, 50, pMedici->m_sNome);
	_snprintf_s((*pData).ObserverIdNumber, 50, "");
	_snprintf_s((*pData).ObserverEmail, 50, pMedici->m_sEmail);
	_snprintf_s((*pData).ObserverPhoneNumber, 50, pMedici->m_sTelefono);
}


VOID CWebDeployer::FillAssignPasswordData(amxmlgenpassworddata* pData, const CString* pStrTo, const CString* pStrFrom, CString strLogin)
{
	_snprintf_s((*pData).To, 50, *pStrTo);
	_snprintf_s((*pData).From, 50, *pStrFrom);
	_snprintf_s((*pData).Type, 50, "AssignPassword");
	_snprintf_s((*pData).ObserverUserLogin, 50, strLogin);
}

VOID CWebDeployer::FillReportData(amxmlgenreportdata* gendata, const CString* pStrTo, const CString* pStrFrom, CPazientiSet* pPatient, CEsamiSet* pExam)
{
	_snprintf_s((*gendata).To, 50, *pStrTo);
	_snprintf_s((*gendata).From, 50, *pStrFrom);
	_snprintf_s((*gendata).IdLocationSupplier, 50, "ENDO");

	//Devo recuperare gli eventuali dati della richiesta
	try
	{
		CString strQuery;
		strQuery.Format("SELECT codiceRepartoInviante, orderNumber, dataEsame FROM PREN_PRESTAZIONI WHERE idesameins is not null and idesameins = %li", pExam->m_lContatore);
		CRecordset prestazioniSet((CDatabase*) &theApp.m_dbEndox);
		prestazioniSet.Open(CRecordset::snapshot, strQuery, CRecordset::readOnly);

		if (!prestazioniSet.IsEOF())
		{
			CString strTemp;
			prestazioniSet.GetFieldValue("codiceRepartoInviante", strTemp);
			_snprintf_s((*gendata).RequestIdLocationPlacer, 50, strTemp);

			prestazioniSet.GetFieldValue("orderNumber", strTemp);
			_snprintf_s((*gendata).RequestIdSupplier, 50, strTemp);

			CString dataRichiesta;
			prestazioniSet.GetFieldValue("dataEsame", dataRichiesta);
			CCustomDate dateReq = CCustomDate(atoi(dataRichiesta.Left(4)), atoi(dataRichiesta.Mid(4,2)), atoi(dataRichiesta.Mid(6,2)), 0, atoi(dataRichiesta.Mid(8,2)), atoi(dataRichiesta.Mid(10,2)));
			_snprintf_s((*gendata).RequestDateTime, 50, dateReq.GetDate("%Y-%m-%dT%H:%M:00"));
		}

		if (prestazioniSet.IsOpen())
			prestazioniSet.Close();

	}
	catch (CDBException* pEx)
	{
		pEx->Delete();
		return;
	}
	//------------
	
	CCustomDate date = pExam->m_lData;
	

	_snprintf_s((*gendata).RequestDrawingDateTime, 50, date.GetDate("%Y-%m-%dT%H:%M:00"));
	_snprintf_s((*gendata).RequestStatus, 50, "Completed");
	_snprintf_s((*gendata).RequestPriority, 50, "Normal");
	_snprintf_s((*gendata).PatientSurname, 50, pPatient->m_sCognome);
	_snprintf_s((*gendata).PatientSecondSurname, 50, pPatient->m_sCognome2);
	_snprintf_s((*gendata).PatientName, 50, pPatient->m_sNome);

	switch(pPatient->m_lSessoPaz)
	{
		case 0:
		{
			_snprintf_s((*gendata).PatientSex, 50, "Male");
			break;
		}
		case 1:
		{
			_snprintf_s((*gendata).PatientSex, 50, "Female");
			break;
		}
		default:
		{
			_snprintf_s((*gendata).PatientSex, 50, "Unknown");
			break;
		}
	}

	CString strPatientDataFmt;
	if (!pPatient->IsFieldNull(&pPatient->m_lNatoIlCustom) && pPatient->m_lNatoIlCustom > 0)
		strPatientDataFmt = CCustomDate(pPatient->m_lNatoIlCustom).GetDate("%Y-%m-%d");
	else
		strPatientDataFmt = "0001-01-01";
	_snprintf_s((*gendata).PatientDateTimeOfBirth, 50, strPatientDataFmt);

	_snprintf_s((*gendata).PatientBirthPlace, 50, pPatient->m_sNatoA);
	_snprintf_s((*gendata).PatientFiscalCode, 50, pPatient->m_sCodFisc);
	_snprintf_s((*gendata).PatientSanitaryCode, 50, pPatient->m_sCodSanit);
	_snprintf_s((*gendata).PatientNosographicCode, 50, "");

	(*gendata).IsReserved = TRUE;
	
	//Estrarre i dati del pdf e del referto
	CString dateFile = pExam->m_sRefertoDataOra; // refSet.GetData(pExam->m_lContatore);
	CCustomDate dateRef = CCustomDate(atoi(dateFile.Left(4)), atoi(dateFile.Mid(4,2)), atoi(dateFile.Mid(6,2)), 0, atoi(dateFile.Mid(8,2)), atoi(dateFile.Mid(10,2)));
	_snprintf_s((*gendata).FileDateTime, 50, dateRef.GetDate("%Y-%m-%d"));
	
	(*gendata).FileIsSigned = pExam->m_bFirmato ? TRUE : FALSE;
	(*gendata).IsCompleted = TRUE;
	(*gendata).IsPreliminary = FALSE;

	_snprintf_s((*gendata).ObserverPatientLogin, 50, pPatient->m_sLogin);

	//Estrarre user del medico
	CMediciCurantiInviantiSet mediciSet(MEDICI_CURANTI);
	_snprintf_s((*gendata).ObserverBasePhysicianLogin, 50, mediciSet.GetLogin(pPatient->m_lMedicoCurante));

	if (pExam->m_lProvenienza == ESTERNO)
	{
		_snprintf_s((*gendata).ObserverSendingPhysicianLogin, 50, mediciSet.GetLogin(pExam->m_lInvMedico));
	}
	else
		_snprintf_s((*gendata).ObserverSendingPhysicianLogin, 50, "");
}

BOOL CWebDeployer::CopyAttachments(const CImgList* pImgList, const CString* pStrSharePath, LONG lIdPatient, LONG lIdExam)
{
	INT iCounter = 0;
	for(POSITION pos = pImgList->GetHeadPosition(); pos;)
	{
		IMG img = pImgList->GetNext(pos);
		if ((img.type == _image_) || (img.type == _dicom_) || (img.type == _mptiff_))
		{
			CString strExportPath;
			strExportPath.Format("%li.at%02d.jpg", lIdExam, iCounter++);
			strExportPath = *pStrSharePath + strExportPath;

			CImgManager imgManager(theApp.m_sPathImageOD, m_pDatabase);
			imgManager.SetCurrentIDs(lIdPatient, lIdExam);
			imgManager.ExportImg(strExportPath, img.lID, image_jpg);
		}
	}

	return TRUE;
}

BOOL CWebDeployer::Deploy(const CString* pStrSharePath, const CString* pStrTo, const CString* pStrFrom, const CString* pStrSupplier, const CString* pStrPlacer, CPazientiSet* pPatient, CEsamiSet* pExam, const CImgList* pImgList, const CString* pPdfPath)
{
	/*if ((!pStrSharePath) || (!pStrTo) || (!pStrFrom) || (!pStrSupplier) || (!pStrPlacer))
		 return FALSE;

	CString strPdfDeployedPath;
	strPdfDeployedPath.Format("%s%li.pdf", *pStrSharePath, pExam->m_lContatore);

	CString strXmlDeployedPath;
	strXmlDeployedPath.Format("%s%li.xml", *pStrSharePath, pExam->m_lContatore);

	HANDLE hTempPdf = CreateFile(*pPdfPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hTempPdf != INVALID_HANDLE_VALUE) 
	{
		CloseHandle(hTempPdf);
		if (!CopyFile(*pPdfPath, strPdfDeployedPath, FALSE))
			return FALSE;
	}
	else
	{
		return FALSE;
	}

	// copia delle immagini
	CopyAttachments(pImgList, pStrSharePath, pExam->m_lPaziente, pExam->m_lContatore);

	amxmlgendata gendata;
	ZeroMemory(&gendata, sizeof(amxmlgendata));
	FillData(&gendata, pPatient, pExam, pStrTo, pStrFrom, pStrSupplier, pStrPlacer);*/

	/*if (!AmXmlGenInitialize(strXmlDeployedPath, &gendata))
		return FALSE;

	if (!AmXmlGenCreate())
		return FALSE;

	if (!AmXmlGenFinalize())
		return FALSE;*/

	return TRUE;
}

BOOL CWebDeployer::DeployDoctor(const CString *pStrSharePath, const CString *pStrTo, const CString *pStrFrom, CMediciCurantiInviantiSet *pMedici, int operation)
{
	if ((!pStrSharePath) || (!pStrTo) || (!pStrFrom))
		 return FALSE;

	CString strXmlDeployedPath;
	strXmlDeployedPath.Format("%sMSG-D%li.xml", *pStrSharePath, pMedici->m_lContatore);

	amxmlgenphysiciandata gendata;
	ZeroMemory(&gendata, sizeof(amxmlgenphysiciandata));

	if (operation == WD_OPERAZIONE_NEW)
		FillNewDoctorData(&gendata, pMedici, pStrTo, pStrFrom);

	if (operation == WD_OPERAZIONE_MODIFY)
		FillModifyDoctorData(&gendata, pMedici, pStrTo, pStrFrom);

	if (!AmXmlGenInitialize(strXmlDeployedPath))
		return FALSE;

	if (!AmXmlGenAddPhysicianUser(&gendata))
		return FALSE;

	if (!AmXmlGenFinalize())
		return FALSE;

	return FALSE;
}

BOOL CWebDeployer::DeployPatient(const CString *pStrSharePath, const CString *pStrTo, const CString *pStrFrom, CPazientiSet *pPatient, int operation)
{
	if ((!pStrSharePath) || (!pStrTo) || (!pStrFrom))
		 return FALSE;

	CString strXmlDeployedPath;
	strXmlDeployedPath.Format("%sMSG-%li.xml", *pStrSharePath, pPatient->m_lContatore);

	amxmlgenpatientdata gendata;
	ZeroMemory(&gendata, sizeof(amxmlgenpatientdata));

	if (operation == WD_OPERAZIONE_NEW)
		FillNewPatientData(&gendata, pPatient, pStrTo, pStrFrom);

	if (operation == WD_OPERAZIONE_MODIFY)
		FillModifyPatientData(&gendata, pPatient, pStrTo, pStrFrom);

	if (!AmXmlGenInitialize(strXmlDeployedPath))
		return FALSE;

	if (!AmXmlGenAddPatientUser(&gendata))
		return FALSE;

	if (!AmXmlGenFinalize())
		return FALSE;

	return FALSE;
}

BOOL CWebDeployer::DeployPasswordPatient(const CString *pStrSharePath, const CString *pStrTo, const CString *pStrFrom, long lContatore, CString strUser)
{
	if ((!pStrSharePath) || (!pStrTo) || (!pStrFrom))
		 return FALSE;

	CString strXmlDeployedPath;
	strXmlDeployedPath.Format("%sMSG-PWD%li.xml", *pStrSharePath, lContatore);

	amxmlgenpassworddata gendata;
	ZeroMemory(&gendata, sizeof(amxmlgenpassworddata));
	FillAssignPasswordData(&gendata, pStrTo, pStrFrom, strUser);

	if (!AmXmlGenInitialize(strXmlDeployedPath))
		return FALSE; 

	if (!AmXmlAssignPasswordUser(&gendata))
		return FALSE;

	if (!AmXmlGenFinalize())
		return FALSE;

	return FALSE;
}

BOOL CWebDeployer::DeployPasswordDoctor(const CString *pStrSharePath, const CString *pStrTo, const CString *pStrFrom, long lContatore, CString strUser)
{
	if ((!pStrSharePath) || (!pStrTo) || (!pStrFrom))
		 return FALSE;

	CString strXmlDeployedPath;
	strXmlDeployedPath.Format("%sMSG-D-PWD%li.xml", *pStrSharePath, lContatore);

	amxmlgenpassworddata gendata;
	ZeroMemory(&gendata, sizeof(amxmlgenpassworddata));
	FillAssignPasswordData(&gendata, pStrTo, pStrFrom, strUser);

	if (!AmXmlGenInitialize(strXmlDeployedPath))
		return FALSE; 

	if (!AmXmlAssignPasswordUser(&gendata))
		return FALSE;

	if (!AmXmlGenFinalize())
		return FALSE;

	return FALSE;
}

BOOL CWebDeployer::DeployReferto(const CString *pStrSharePath, const CString *pStrTo, const CString *pStrFrom, CPazientiSet* pPatient, CEsamiSet* pExam, const CImgList* pImgList, const CString* pPdfPath)
{
	if ((!pStrSharePath) || (!pStrTo) || (!pStrFrom))
		 return FALSE;

	CString strPdfDeployedPath;
	strPdfDeployedPath.Format("%sRef-%li.pdf", *pStrSharePath, pExam->m_lContatore);

	HANDLE hTempPdf = CreateFile(*pPdfPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hTempPdf != INVALID_HANDLE_VALUE) 
	{
		CloseHandle(hTempPdf);
		if (!CopyFile(*pPdfPath, strPdfDeployedPath, FALSE))
			return FALSE;
	}
	else
	{
		return FALSE;
	}

	// copia delle immagini
	CopyAttachments(pImgList, pStrSharePath, pExam->m_lPaziente, pExam->m_lContatore);

	CString strXmlDeployedPath;
	strXmlDeployedPath.Format("%sRef-%li.xml", *pStrSharePath, pExam->m_lContatore);

	amxmlgenreportdata gendata;
	ZeroMemory(&gendata, sizeof(amxmlgenreportdata));
	FillReportData(&gendata, pStrTo, pStrFrom, pPatient, pExam);

	if (!AmXmlGenInitialize(strXmlDeployedPath))
		return FALSE; 

	if (!AmXmlGenReport(&gendata))
		return FALSE;

	if (!AmXmlGenFinalize())
		return FALSE;

	return FALSE;
}