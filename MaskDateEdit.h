#ifndef _MASKDATEEDIT_H_
#define _MASKDATEEDIT_H_

#include "MaskEdit.h"

class CEsamiView;

class CMaskDateEdit : public CMaskEdit
{
public:
	CMaskDateEdit();
	virtual ~CMaskDateEdit();

	BOOL OpenDialog();
	void SetParam(CWnd* pParentView, CEsamiView* pEsamiView, CString strTitle);

	CString m_strRicerca, m_strRicercaView;

protected:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	DECLARE_MESSAGE_MAP()

	CEsamiView* m_pEsamiView;
	CWnd* m_pParentView;
	CString m_strTitle;
};

#endif /* _MASKDATEEDIT_H_ */