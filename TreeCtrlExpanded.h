#pragma once

class CTreeCtrlExpanded : public CTreeCtrl
{
public:
	CTreeCtrlExpanded(void);
	~CTreeCtrlExpanded(void);

protected:
	void OnLButtonDblClk(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};
