#ifndef _MONITORAGGIOLISTCTRL_H_
	#define _MONITORAGGIORICHLISTCTRL_H_

#include "DLL_Imaging\h\AMListCtrl.h"

class CMonitoraggioListCtrl : public CAMEditComboListCtrl
{
	DECLARE_DYNAMIC(CMonitoraggioListCtrl)

public:

	CMonitoraggioListCtrl();
	virtual ~CMonitoraggioListCtrl();

	CEsamiView* m_pEsamiView;

	int GetColumnCount();

protected:

	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

};

#endif /* _MONITORAGGIOLISTCTRL_H_ */