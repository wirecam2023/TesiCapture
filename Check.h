#ifndef _CHECK_H_
	#define _CHECK_H_

class CBmp;

class CCheckList : public CObject
{
	DECLARE_DYNCREATE(CCheckList)

public:

	CCheckList();
	virtual ~CCheckList();
    
	void 		DeleteTail();  
	void 		DeleteContents();
	BOOL		IsEmpty() { return m_CheckList.IsEmpty(); }
	POSITION 	GetFirstObjPos();
	CBmp* 		GetNextObj(POSITION& pos);
	BOOL		RemoveObj(CBmp* pBmp); 
	void		DeleteObjFromList(CBmp* pBmp);
	void		InsertObjInList(CBmp* pBmp);
	
protected:

	CObList		m_CheckList;

};

#endif /* _CHECK_H_ */
