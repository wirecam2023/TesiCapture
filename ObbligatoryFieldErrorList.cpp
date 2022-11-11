#include "stdafx.h"
#include "Endox.h"
#include "ObbligatoryFieldErrorList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CObbligatoryFieldErrorList::CObbligatoryFieldErrorList(void)
	: CList<tagOBBLIGATORYFIELD_ERROR>()
{
}

CObbligatoryFieldErrorList::~CObbligatoryFieldErrorList(void)
{
}

CString CObbligatoryFieldErrorList::GetDescription()
{
	CString strFieldList;
	for (POSITION pos = GetHeadPosition(); pos;)
	{
		if (!strFieldList.IsEmpty())
			strFieldList += ", ";
		strFieldList += "«" + CString(GetNext(pos).szFieldName) + "»";
	}

	CString strError = "";
	strError.Format("%s obbligatori", strFieldList);
	return strError;
}

void CObbligatoryFieldErrorList::Add(long lFieldID, LPCTSTR szFieldName)
{
	tagOBBLIGATORYFIELD_ERROR err;
	err.lFieldID = lFieldID;
	strcpy_s(err.szFieldName, szFieldName);
	AddTail(err);
}