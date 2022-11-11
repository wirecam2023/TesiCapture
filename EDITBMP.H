#ifndef EDIT_BMP
	#define EDIT_BMP

class CBmp;

class CEditBmp : public CEdit
{
public:

	CEditBmp();
	virtual ~CEditBmp();

	void AssignBmp(CBmp* pBmp);
	void Refresh();

protected:

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()

private:

	CBmp* m_pParentBmp;
};

#endif