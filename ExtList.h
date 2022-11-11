#ifndef _EXTLIST_H_
	#define _EXTLIST_H_

#define COD_CODE	0
#define COD_TEXT	1

typedef struct pointerCombo
{   
	long lExtMode;
	int nMaxLen;   
	BOOL bIsCodeCounter;
	BOOL bOrderByCode;
	long lComboDefine;
} DATACOMBO;

class CExtList : public CListBox
{
	DECLARE_DYNCREATE (CExtList)

public:

	CExtList();
	virtual ~CExtList();

	CWnd*	m_pParentForm;

	virtual void SetParam(CWnd* pParentForm);

protected:

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
};

#endif /* _EXTLIST_H_ */