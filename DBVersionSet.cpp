#include "stdafx.h"
#include "Endox.h"
#include "DBVersionSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CDBVersionSet, CBaseSet)

CDBVersionSet::CDBVersionSet()
	: CBaseSet(NULL, "VIEW")  // è una vista //
{
	SetEmpty();
	SetSortRecord("Version1 DESC, Version2 DESC, Version3 DESC, Version4 DESC");

	m_nFields = 4;
}

CString CDBVersionSet::GetDefaultSQL()
{
	return "tb_DB_Version";
}

void CDBVersionSet::SetEmpty()
{
	m_lVersion1 = 0;
	m_lVersion2 = 0;
	m_lVersion3 = 0;
	m_lVersion4 = 0;
}

void CDBVersionSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);

	RFX_Long(pFX, "Version1", m_lVersion1);
	RFX_Long(pFX, "Version2", m_lVersion2);
	RFX_Long(pFX, "Version3", m_lVersion3);
	RFX_Long(pFX, "Version4", m_lVersion4);
}

CString CDBVersionSet::GetDBVersion()
{
	CString strReturn = "";

	if (OpenRecordset("CDBVersionSet::GetDBVersion"))
	{
		if (!IsEOF())
		{
			strReturn.Format("%li.%li", m_lVersion1, m_lVersion2);
			// strReturn.Format("%li.%li.%li", m_lVersion1, m_lVersion2, m_lVersion3);
		}

		CloseRecordset("CDBVersionSet::GetDBVersion");
	}

	return strReturn;
}