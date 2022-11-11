#ifndef _CALIB_H_
	#define _CALIB_H_

class CCalib : public CObject
{
public: // create from serialization only
	CCalib();
	DECLARE_SERIAL(CCalib)
    
// Attributes
public:
	CString		m_strName;
	CString		m_strScreenMisura;
	CString		m_strUserMisura;
	double		m_dConvRatio;                                 
	void		SetConvRatio (CString user,CString screen);

// Implementation
public:

	virtual void Serialize(CArchive& ar); 
	
};

#endif /* _CALIB_H_ */