#ifndef _MYRADIO_H_
	#define _MYRADIO_H_

class CMyRadio : public CButtonLocalize
{
	DECLARE_DYNAMIC(CMyRadio)

public:

	CMyRadio(UINT uiFocus);
	virtual ~CMyRadio();

protected:

	DECLARE_MESSAGE_MAP()

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

private:

	UINT m_uiFocus;

};

#endif /* _MYRADIO_H_ */