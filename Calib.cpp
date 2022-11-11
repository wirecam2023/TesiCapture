#include "stdafx.h"
#include "Endox.h"
#include "Calib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(CCalib, CObject, 1)

/////////////////////////////////////////////////////////////////////////////
// CCalib construction/destruction

CCalib::CCalib()
{   
	m_strName 			= "1:1";
	m_strScreenMisura 	= "1";
	m_strUserMisura 	= "1";
	m_dConvRatio 		= 1.0; // m_fConvRatio 		= 1.0;
}


/////////////////////////////////////////////////////////////////////////////
// CCalib serialization

void CCalib::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_strScreenMisura;
		ar << m_strUserMisura; 
		ar << m_strName;
	}
	else
	{           
		ar >> m_strScreenMisura;
		ar >> m_strUserMisura;
		ar >> m_strName;

		for(int i=0; i<m_strName.GetLength(); i++)
			if (m_strName.GetAt(i) == ' ')
				m_strName.SetAt(i, '_');
		
		SetConvRatio (m_strUserMisura, m_strScreenMisura);
	}   
}

/////////////////////////////////////////////////////////////////////////////
// CCalib commands
void CCalib::SetConvRatio(CString user, CString screen)
{   
	m_strScreenMisura = screen;
	m_strUserMisura = user;
	
    double dScreen = atof (m_strScreenMisura);
    double dUser   = atof (m_strUserMisura);
	
	if (dScreen!= 0.0 && dUser!= 0.0)
    	m_dConvRatio =  ( dUser/dScreen );
    else  if (dScreen!= 0.0 && dUser== 0.0)   
    	m_dConvRatio = dUser;
    else
    	m_dConvRatio = 1.0;  
    
    
    	
}