#pragma once
class CMyResizableDialog : public CResizableDialog
{
public:	

	CMyResizableDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);

	virtual void Savee() = 0;
};

