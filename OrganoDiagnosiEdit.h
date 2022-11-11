#ifndef _ORGANODIAGNOSIEDIT_H_
	#define _ORGANODIAGNOSIEDIT_H_

class COrganoDiagnosiEdit : public CEdit
{

public:

	COrganoDiagnosiEdit();
	
	void SetParam(CEsamiView* pEsamiView, CWnd* pOrganoEdit, CWnd* pSedeEdit, CWnd* pDiagnosiEdit);

protected:

	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()

private:

	void OpenDialog();

	CEsamiView* m_pEsamiView;
	CWnd* m_pOrganoEdit;
	CWnd* m_pSedeEdit;
	CWnd* m_pDiagnosiEdit;
};

#endif /* _ORGANODIAGNOSIEDIT_H_ */