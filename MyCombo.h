#ifndef _MYCOMBO_H_
	#define _MYCOMBO_H_

class CMyCombo : public CComboBox
{
	DECLARE_DYNAMIC(CMyCombo)

public:

	CMyCombo();
	virtual ~CMyCombo();

protected:

	DECLARE_MESSAGE_MAP()

	BOOL PreTranslateMessage(MSG *pMsg);

};

#endif /* _MYEDIT_H_ */