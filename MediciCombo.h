#ifndef _MEDICICOMBO_H_
	#define _MEDICICOMBO_H_

class CMediciCombo : public CComboBox
{

public:

	CMediciCombo();
	virtual ~CMediciCombo();
	void SelectCurrent(CWnd* pParentView);	

private:
	CWnd* m_pParentView;

protected:

	afx_msg void OnCloseup();
	afx_msg void OnDropdown();

	DECLARE_MESSAGE_MAP()

};

#endif /* _MEDICICOMBO_H_ */