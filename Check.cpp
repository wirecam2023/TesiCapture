#include "stdafx.h"
#include "Endox.h"

#include "check.h"
#include "Dib.h"
#include "bmp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CCheckList, CObject)

CCheckList::CCheckList()
{   
}

CCheckList::~CCheckList()
{   
}

void CCheckList::DeleteContents()
{
	while (!m_CheckList.IsEmpty())
	{
		delete m_CheckList.RemoveTail();
	}
}  

void CCheckList::DeleteTail()
{
	if (!m_CheckList.IsEmpty())
	{
		delete m_CheckList.RemoveTail();
	}
}

void CCheckList::DeleteObjFromList(CBmp* pBmp)
{
	if (pBmp)
	{
		RemoveObj(pBmp);
	}
}

void CCheckList::InsertObjInList(CBmp* pBmp)
{           
	m_CheckList.AddTail(pBmp);
}

POSITION CCheckList::GetFirstObjPos()
{
	return m_CheckList.GetHeadPosition();
}

CBmp* CCheckList::GetNextObj(POSITION& pos)
{
	return (CBmp*)m_CheckList.GetNext(pos);
}

BOOL CCheckList::RemoveObj (CBmp* pBmp)
{
	POSITION pos;

	if ( ( pos = m_CheckList.Find( pBmp ) ) != NULL )
	{
	    m_CheckList.RemoveAt (pos);

		return TRUE;
	}               
	return FALSE;
}