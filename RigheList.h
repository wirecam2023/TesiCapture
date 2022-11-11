#ifndef _RIGHELIST_H_
	#define _RIGHELIST_H_

class CRiga;

class CRigheList : public CObject
{
	DECLARE_DYNCREATE(CRigheList)

public:

	CRigheList();
	virtual ~CRigheList(void);

	void 		DeleteTail();  
	void 		DeleteContents();
	BOOL		IsEmpty() { return m_List.IsEmpty(); }
	POSITION 	GetFirstObjPos();
	CRiga* 		GetNextObj(POSITION& pos);
	BOOL		RemoveObj(CRiga* pRiga); 
	void		DeleteObjFromList(CRiga* pRiga);
	void		InsertObjInList(CRiga* pRiga);
	CRiga*		SearchObj(long nEsame);

protected:

	CObList		m_List;
	
};

#endif /* _RIGHELIST_H_ */