#ifndef _ANATOMIAPATOLOGICALISTCTRL_H_
	#define _ANATOMIAPATOLOGICALISTCTRL_H_

typedef void (*LPSTAMPARIGA)(long lRecord, CEsamiView* pEsamiView);

class CAnatomiaPatologicaListCtrl : public CListCtrlLocalize
{
	DECLARE_DYNAMIC(CAnatomiaPatologicaListCtrl)

public:

	CAnatomiaPatologicaListCtrl();
	virtual ~CAnatomiaPatologicaListCtrl();

	void SetReadOnly(BOOL bReadOnly);

	LPSTAMPARIGA m_pStampaRigaFunction;

	CEsamiView* m_pEsamiView;

protected:

	DECLARE_MESSAGE_MAP()

private:

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	BOOL m_bReadOnly;
};

#endif /* _ANATOMIAPATOLOGICALISTCTRL_H_ */