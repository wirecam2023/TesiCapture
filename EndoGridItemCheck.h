#pragma once

#include "EndoGridItem.h"

class CEndoGridItemCheck;

class CEndoGridInplaceCheckBox : public CButton
{
public:
	CEndoGridInplaceCheckBox();

	afx_msg LRESULT OnCheck(WPARAM wParam, LPARAM lParam);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnKillFocus(CWnd* pNewWnd);

	DECLARE_MESSAGE_MAP()

protected:
	CEndoGridItemCheck* m_pItem;
	COLORREF m_clrBack;
	CBrush m_brBack;

	BOOL m_bNotify;
	int m_iFirstValue;

	friend class CEndoGridItemCheck;
};

class CEndoGridItemCheck : public CXTPPropertyGridItem
{
	DECLARE_DYNAMIC(CEndoGridItemCheck)

public:
	CEndoGridItemCheck(CString strCaption);
	CEndoGridItemCheck(UINT nID);

	BOOL GetBool();
	void SetBool(BOOL bValue);

	void NotifyDirty();

	CString GetValue() { return GetBool() ? "True" : "False"; }
	CString GetValueEx() { return GetValue(); }

protected:
	virtual void OnValueChanged(CString strValue);
	virtual BOOL OnChar(UINT nChar);
	virtual void OnDeselect();
	virtual void OnSelect();
	virtual CRect GetValueRect();
	virtual BOOL OnDrawItemValue(CDC& dc, CRect rcValue);

private:
	void SetValue(CString strValue) { CXTPPropertyGridItem::SetValue(strValue); }

	CEndoGridInplaceCheckBox m_wndCheckBox;
	BOOL m_bValue;

	friend class CEndoGridInplaceCheckBox;
};