#ifndef _INFERMIERICOMBO_H_
	#define _INFERMIERICOMBO_H_

class CInfermieriCombo : public CComboBox
{

public:

	CInfermieriCombo();
	virtual ~CInfermieriCombo();

protected:

	afx_msg void OnCloseup();
	afx_msg void OnDropdown();

	DECLARE_MESSAGE_MAP()

};

#endif /* _INFERMIERICOMBO_H_ */