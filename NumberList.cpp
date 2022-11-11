#include "stdafx.h"
#include "Endox.h"
#include "NumberList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CNumberList::CNumberList()
	: CList<long>()
{
}

CNumberList::~CNumberList()
{
}

void CNumberList::Add(long lNum)
{
	CList<long>::AddTail(lNum);
}

void CNumberList::Remove(long lNum)
{
	if (POSITION pos = Find(lNum))
		RemoveAt(pos);
}

BOOL CNumberList::IsPresent(long lNumber)
{
	return Find(lNumber) ? TRUE : FALSE;
}

CString CNumberList::GetString()
{
	CString strReturn, strTmp;
	for (POSITION pos = GetHeadPosition(); pos;)
	{
		strTmp.Format("%li;", GetNext(pos));
		strReturn += strTmp;
	}
	return strReturn;
}

void CNumberList::SetString(const CString strNumbers)
{
	RemoveAll();

	int nLastPos = 0, nPos = 0;
	while (nPos != -1)
	{
		nPos = strNumbers.Find(";", nLastPos);
		if (nPos != -1)
		{
			AddTail(atol(strNumbers.Mid(nLastPos, nPos - nLastPos)));
			nLastPos = nPos + 1;
		}
	}
}

INT_PTR CNumberList::GetCount()
{
	return CList<long>::GetCount();
}

long CNumberList::GetAt(int iIndex)
{
	long lReturn = -1;
	if (POSITION pos = FindIndex(iIndex))
		lReturn = CList<long>::GetAt(pos);
	return lReturn;
}

void CNumberList::Reset()
{
	RemoveAll();
}