#ifndef _ANATOMIAPATOLOGICARICHLISTCTRL_H_
	#define _ANATOMIAPATOLOGICARICHLISTCTRL_H_

#include "DLL_Imaging\h\AMListCtrl.h"

typedef void (*LPSTAMPARIGARICH)(long lPaziente, long lEsame, CEsamiView* pEsamiView, BOOL bAltroIndirizzo);

class CAnatomiaPatologicaRichListCtrl : public CListCtrlLocalize /*CAMEditComboListCtrl*/
{
	DECLARE_DYNAMIC(CAnatomiaPatologicaRichListCtrl)

public:

	CAnatomiaPatologicaRichListCtrl();
	virtual ~CAnatomiaPatologicaRichListCtrl();

	LPSTAMPARIGARICH m_pStampaRigaFunction;

	CEsamiView* m_pEsamiView;

protected:

	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

private:

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#endif /* _ANATOMIAPATOLOGICARICHLISTCTRL_H_ */