#ifndef _EXTLISTBOX_H_
	#define _EXTLISTBOX_H_

class CExtListBox : public CListBox
{

public:

	CExtListBox();
	virtual ~CExtListBox();

protected:

	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	DECLARE_MESSAGE_MAP()

};

#endif /* _EXTLISTBOX_H_ */