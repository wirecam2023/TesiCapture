#ifndef _ENDOXRESIZABLEDLG_H_
	#define _ENDOXRESIZABLEDLG_H_

#include "DLL_Imaging\h\AmCtrls.h"

class CEndoxResizableDlg : public CResizableDialog
{
	DECLARE_DYNAMIC(CEndoxResizableDlg)

public:

	CEndoxResizableDlg(UINT nID, CWnd* pParent);
	virtual ~CEndoxResizableDlg();

	CWnd* m_pParentFrame;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);

	virtual afx_msg LRESULT OnResizeForm(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

};

#endif /* _ENDOXRESIZABLEDLG_H_ */