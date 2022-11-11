// MonitorDC.cpp : implementation file
// ref: https://www.codeproject.com/Articles/3690/MFC-Classes-for-Multiple-Monitors
//

#include "stdafx.h"
#include "MonitorDC.h"
#include "Monitor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CMonitorDC
CMonitorDC::CMonitorDC()
{
}

CMonitorDC::CMonitorDC( CMonitor* pMonitor )
{
	ASSERT( pMonitor );
	ASSERT( pMonitor->IsMonitor() );

	VERIFY( Attach( pMonitor->CreateDC() ) );
}

CMonitorDC::~CMonitorDC()
{
	VERIFY( DeleteDC() );
}


// CMonitorDC member functions
