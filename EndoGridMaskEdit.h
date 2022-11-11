#pragma once

class CEndoGridInplaceMaskEdit : public CXTMaskEditT<CXTPPropertyGridInplaceEdit>
{
	DECLARE_DYNAMIC(CEndoGridInplaceMaskEdit);
	DECLARE_MESSAGE_MAP()

protected:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};


class CEndoGridMaskEdit : public CXTPPropertyGridItem
{
public:
	CEndoGridMaskEdit(CString strCaption);
	CEndoGridMaskEdit(UINT nID);

	void SetEditMask(LPCTSTR lpszMask, LPCTSTR lpszLiteral, LPCTSTR lpszDefault);

	CString GetEditMask() { return m_strEditMask; };
	CString GetLiteral()  { return m_strLiteral; };

protected:
	virtual CXTPPropertyGridInplaceEdit& GetInplaceEdit();
	virtual void OnSelect();
	virtual void OnDeselect();

protected:
	CEndoGridInplaceMaskEdit m_wndMaskEdit;
	CString m_strLiteral;
	CString m_strEditMask;
};
