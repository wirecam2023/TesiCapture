#ifndef _EXTDATEEDIT_H_
	#define _EXTDATEEDIT_H_

#include "MaskDateEdit.h"

class CEsamiView;

class CExtDateEdit : public CMaskDateEdit
{

public:

	CExtDateEdit();
	virtual ~CExtDateEdit();

	void SetParam(CWnd* pParentView, CEsamiView* pEsamiView, CString strTitle, int nModalita);
	CString m_strRicerca;
	CString m_strRicercaView;

protected:

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );

	DECLARE_MESSAGE_MAP()

private:

	BOOL OpenDialog();

	CWnd* m_pParentView;
	CEsamiView* m_pEsamiView;
	int m_iModalita;

};

#endif /* _EXTDATEEDIT_H_ */