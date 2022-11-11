#include "stdafx.h"
#include "Endox.h"
#include "EndoGridCLViewVersionUOSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CEndoGridCLViewVersionUOSet, CBaseSet)

CEndoGridCLViewVersionUOSet::CEndoGridCLViewVersionUOSet(CDatabase* pDatabase)
	: CBaseSet(NULL, "VIEW")  // è una vista //
{
	m_lUO = 0;
	m_lVersionID = 0;

	m_nFields = 2;
}

void CEndoGridCLViewVersionUOSet::DoFieldExchange(CFieldExchange* pFX)
{
	CBaseSet::DoFieldExchange(pFX);
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("UO"), m_lUO);
	RFX_Long(pFX, _T("IDVERSIONE"), m_lVersionID);
}

CString CEndoGridCLViewVersionUOSet::GetDefaultSQL()
{
	return _T("VIEWGRIDCLVERSION_UO");
}

long CEndoGridCLViewVersionUOSet::GetLastGridVersion(long lUO)
{
	long lReturn = 0;

	CString sFilter;
	sFilter.Format("UO=%li", lUO);
	SetOpenFilter(sFilter);
	SetSortRecord("IDVERSIONE DESC");
	if (OpenRecordset("CEndoGridCLViewVersionUOSet::GetLastGridVersion"))
	{
		if (!IsEOF() && !IsBOF())
		{			
			lReturn = m_lVersionID;
		}

		CloseRecordset("CEndoGridCLViewVersionUOSet::GetLastGridVersion");
	}

	return lReturn;
}

