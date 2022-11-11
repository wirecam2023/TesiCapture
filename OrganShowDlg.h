#ifndef _ORGANSHOWDLG_H_
	#define _ORGANSHOWDLG_H_

#include "OrganiSet.h"
//#include "EditBmp.h"

class CEsamiView;
class CFileBmp;

class COrganShowDlg : public CDialog
{

public:

	COrganShowDlg(CWnd* pParent, CEsamiView* pEsamiView);
	~COrganShowDlg(void);

	enum { IDD = IDD_ORGAN_SHOW };

	CBitmapButtonEx	m_BtnOrgFirst;
	CBitmapButtonEx	m_BtnOrgPrev;
	CBitmapButtonEx	m_BtnOrgNext;
	CBitmapButtonEx	m_BtnOrgLast;
	CBitmapButtonEx	m_BtnNwIm;
	CBitmapButtonEx	m_BtnDlIm;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnFrstOrg();
	afx_msg void OnPrevOrg();
	afx_msg void OnNextOrg();
	afx_msg void OnLastOrg();
	afx_msg void OnBtnNwIm();
	afx_msg void OnBtnDlIm();

	DECLARE_MESSAGE_MAP()

	CButtonLocalize m_ctrlButtonOK;

private:

	void MoveImageOrg();

	COrganiSet m_setOrgani;
	CEsamiView* m_pEsamiView;

	BOOL m_bIsPrevActive;
	BOOL m_bIsNextActive;
	BOOL m_bIsRecycleActive;

	CDib m_Dib;
};

#endif /* _ORGANSHOWDLG_H_ */