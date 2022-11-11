#ifndef _MONITORAGGIOBASEDYNFORM_H_
	#define _MONITORAGGIOBASEDYNFORM_H_

#include "EndoxDynForm.h"

class CMonitoraggioBaseDynForm : public CEndoxDynForm
{

public:

	CMonitoraggioBaseDynForm(UINT nID, CWnd* pParent, CEsamiView* pEsamiView);
	~CMonitoraggioBaseDynForm();

	virtual int GetListItemCount() = 0;
	virtual CString GetListItemText(int nItem, int nSubItem) = 0;

	virtual long GetListNumCol() = 0;
	virtual long GetListNumRig() = 0;
	virtual CString GetFarmaciList(int nMonitoraggio) = 0;	
	virtual CString GetTotaleFarmaciList() = 0;
	virtual void Reload() = 0;
	virtual void AggiungiRiga() = 0;

protected:

	DECLARE_MESSAGE_MAP()

};

#endif /* _MONITORAGGIOBASEDYNFORM_H_ */