#include "stdafx.h"
#include "Endox.h"
#include "RigheList.h"

#include "Riga.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CRigheList, CObject)

CRigheList::CRigheList()
{   
}

CRigheList::~CRigheList()
{   
	DeleteContents();
}

void CRigheList::DeleteContents()
{
	while (!m_List.IsEmpty())
	{
		delete m_List.RemoveTail();
	}
}  

void CRigheList::DeleteTail()
{
	if (!m_List.IsEmpty())
	{
		delete m_List.RemoveTail();
	}
}

void CRigheList::DeleteObjFromList(CRiga* pRiga)
{
	if (pRiga)
	{
		RemoveObj(pRiga);
	}
}

void CRigheList::InsertObjInList(CRiga* pRiga)
{           
	m_List.AddTail(pRiga);
}

POSITION CRigheList::GetFirstObjPos()
{
	return m_List.GetHeadPosition();
}


CRiga* CRigheList::GetNextObj(POSITION& pos)
{
	return (CRiga*)m_List.GetNext(pos);
}

BOOL CRigheList::RemoveObj (CRiga* pRiga)
{
	POSITION pos;

	if ( ( pos = m_List.Find( pRiga ) ) != NULL )
	{
	    m_List.RemoveAt (pos);

		return TRUE;
	}               
	return FALSE;
}

CRiga* CRigheList::SearchObj(long nEsame)
{
	for(POSITION pos = GetFirstObjPos(); pos != NULL; )
	{
		CRiga* pRiga = GetNextObj(pos);
		
		if (pRiga && pRiga->m_nEsame == nEsame)
		{
		    return pRiga;
		}
	}

	return NULL;
}