#ifndef _FRAMESTATIC_H_
	#define _FRAMESTATIC_H_

class CFrameStatic : public CStatic
{
	DECLARE_DYNAMIC(CFrameStatic)

public:

	CFrameStatic(COLORREF* pCR);
	virtual ~CFrameStatic();

protected:

	DECLARE_MESSAGE_MAP()

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

private:

	COLORREF* m_pCR;

};

#endif /* _FRAMESTATIC_H_ */