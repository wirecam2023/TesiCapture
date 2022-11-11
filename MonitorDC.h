#pragma once

#ifndef _MONITORDC_H_
#define _MONITORDC_H_

class CMonitor;

// CMonitorDC command target

class CMonitorDC : public CDC
{
public:
	CMonitorDC();
	CMonitorDC( CMonitor* pMonitor );
	virtual ~CMonitorDC();
};


#endif /* _MONITORDC_H_ */