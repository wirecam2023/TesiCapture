#include "stdafx.h"
#include "Endox.h"
#include "MonitoraggioBaseDynForm.h"

#include "EsamiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMonitoraggioBaseDynForm::CMonitoraggioBaseDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView)
	: CEndoxDynForm(nID, pParent, pEsamiView)
{
}

CMonitoraggioBaseDynForm::~CMonitoraggioBaseDynForm(void)
{
}

BEGIN_MESSAGE_MAP(CMonitoraggioBaseDynForm, CEndoxDynForm)
END_MESSAGE_MAP()
