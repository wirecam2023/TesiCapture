#ifndef _ACCESSORICOMBO_H_
	#define _ACCESSORICOMBO_H_

class CAccessoriCombo : public CComboBox
{

public:

	CAccessoriCombo();
	virtual ~CAccessoriCombo();

protected:

	afx_msg void OnCloseup();
	afx_msg void OnDropdown();

	DECLARE_MESSAGE_MAP()

};

#endif /* _ACCESSORICOMBO_H_ */