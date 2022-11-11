#ifndef _CALIBLIST_H_
	#define _CALIBLIST_H_

class CCalib;

class CCalibList : public CObject
{
public:

	CCalibList();
	DECLARE_SERIAL(CCalibList)
	CString			m_strFileName;

protected:

	CObList         m_CalibList;

public:

	void 		DeleteContents();
	BOOL		IsEmpty() { return m_CalibList.IsEmpty();  }
	CCalib* 	NewCalib ();
	POSITION 	GetFirstCalibPos();
	CCalib* 	GetNextCalib(POSITION& pos);
	BOOL		RemoveCalib (CCalib* pCalib); 
	BOOL		ReadDisk ();
	BOOL		WriteDisk ();
    
	virtual ~CCalibList();
	virtual void Serialize(CArchive& ar); 
	
}; 

#endif /* _CALIBLIST_H_ */