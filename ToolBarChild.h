#pragma once

#include "ToolBarEx.h"

class CToolBarChild : public CToolBarEx
{
protected:
	CToolBarChild(CWnd* pParentWnd);
	virtual ~CToolBarChild();

	void DeleteButton(UINT id, BOOL bDeleteSeparatorAfter = FALSE);

	virtual LRESULT OnToolbarPressButton(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnUpdateCommandUI(WPARAM wParam, LPARAM lParam);

	CWnd* m_pParentWnd;

	friend class CToolbarChildDlg;
};