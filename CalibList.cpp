#include "stdafx.h"
#include "Endox.h"
#include "CalibList.h"

#include "Calib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(CCalibList, CObject, 1)

CCalibList::CCalibList()
{
	m_strFileName = "";
	NewCalib();
}

CCalibList::~CCalibList()
{   
	DeleteContents();
}

void CCalibList::DeleteContents()
{
	while (!m_CalibList.IsEmpty())
	{
		delete m_CalibList.RemoveTail();
	}
}

void CCalibList::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{            
	}
	else
	{                       
	}   
	m_CalibList.Serialize(ar);
}

BOOL CCalibList::ReadDisk () 
{
	CFile 			f;
	CFileException 	e;
		
	if ( !f.Open( m_strFileName, CFile::modeRead, &e ) )
	{
		TCHAR szCause[255];
		e.GetErrorMessage(szCause, 255);
		theApp.AfxMessageBoxEndo (szCause); 
	}
	else
	{
		TRY{
			char buf[512];
			CArchive ar( &f, CArchive::load, 512, buf );
			Serialize (ar); 
		}
		CATCH(CArchiveException, a) 
		{
			TCHAR  szCause[255];
			a->GetErrorMessage(szCause, 255);
			theApp.AfxMessageBoxEndo (szCause); 
		}
		END_CATCH
	}

	if (IsEmpty())
		NewCalib ();

   	return TRUE;
}

BOOL CCalibList::WriteDisk ()
{
	CFile 			f;
	CFileException 	e;
	
	if ( !f.Open( m_strFileName, CFile::modeCreate | CFile::modeWrite, &e ) )		
	{
		TCHAR  szCause[255];
		e.GetErrorMessage(szCause, 255);
		// theApp.AfxMessageBoxEndo (szCause); 
		return FALSE;
	}
	else
	{
		TRY {
			char buf[512];		   
			CArchive ar( &f, CArchive::store, 512, buf );			
			Serialize (ar); 
		}
		CATCH(CArchiveException, a) 
		{
			TCHAR  szCause[255];
			a->GetErrorMessage(szCause, 255);
			// theApp.AfxMessageBoxEndo (szCause); 
		}
		END_CATCH
	}
	
	return TRUE;
}

CCalib* CCalibList::NewCalib()                 
{           
	CCalib* pCalibItem = NULL;
	
	pCalibItem = new CCalib();
	m_CalibList.AddTail(pCalibItem);
	
	return pCalibItem;
}

POSITION CCalibList::GetFirstCalibPos()
{
	return m_CalibList.GetHeadPosition();
}

CCalib* CCalibList::GetNextCalib(POSITION& pos)
{
	return (CCalib*)m_CalibList.GetNext(pos);
}
            
BOOL CCalibList::RemoveCalib (CCalib* pCalib)
{
	POSITION pos;

	if ( ( pos = m_CalibList.Find( pCalib ) ) != NULL ) // Hunt for pCalib
	{                                        // starting at head by default.
	    m_CalibList.RemoveAt (pos);
	    delete pCalib;
	    return TRUE;
	}               
	return FALSE;
}
