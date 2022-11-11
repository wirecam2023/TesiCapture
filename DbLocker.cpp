#include "stdafx.h"
#include "DbLocker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDbLocker::CDbLocker()
{
	m_lResult = 0;
	m_sResource = "";

	m_bLockResource = FALSE;

	m_nDefaultType = snapshot;
	m_nParams = 2;
	m_nFields = 0;
}

CDbLocker::~CDbLocker()
{
}

BOOL CDbLocker::LockResource(LPCTSTR szResource, CDatabase* pDatabase)
{
	/*
	declare @returncode int
	exec @returncode = sp_getapplock @Resource='TEST',  @LockMode='Exclusive', @LockTimeout=0,@LockOwner = 'Session'
	print @returncode
	--WAITFOR DELAY '00:00:10'
	exec @returncode = sp_releaseapplock @Resource='TEST',@LockOwner = 'Session'
	print @returncode
	*/

	BOOL bReturn = FALSE;

	m_sResource = szResource;
	m_pDatabase = pDatabase;
	m_bLockResource = TRUE;

	try
	{
		Open();
		bReturn = (m_lResult == 0);
	}
	catch (CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
	}
	
	if (IsOpen())
		Close();

	return bReturn;
}

BOOL CDbLocker::UnlockResource(LPCTSTR szResource, CDatabase* pDatabase)
{
	BOOL bReturn = FALSE;

	m_sResource = szResource;
	m_pDatabase = pDatabase;
	m_bLockResource = FALSE;

	try
	{
		Open();
		bReturn = (m_lResult == 0);
	}
	catch (CDBException* pEx)
	{
		pEx->ReportError();
		pEx->Delete();
	}

	if (IsOpen())
		Close();

	return bReturn;
}

void CDbLocker::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputParam);
	RFX_Long(pFX, "@Result", m_lResult);

	pFX->SetFieldType(CFieldExchange::inputParam);
	RFX_Text(pFX, "@Resource", m_sResource);
}

CString CDbLocker::GetDefaultSQL()
{
	return m_bLockResource ? "{? = CALL sp_getapplock(?,'Exclusive','Session',0,'public')}" : "{? = CALL sp_releaseapplock(?,'Session','public')}";
}