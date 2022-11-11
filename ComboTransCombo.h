#ifndef _COMBOTRANSCOMBO_H_
	#define _COMBOTRANSCOMBO_H_

class CComboTransSet;
class CBaseSet;

class CComboTransCombo : public CComboBox
{

public:

	CComboTransCombo();
	virtual ~CComboTransCombo();

	void SetParam(CBaseSet* pMainSet, long* pValore, CComboTransSet* pSet);

protected:

	afx_msg void OnCloseup();
	afx_msg void OnDropdown();

	DECLARE_MESSAGE_MAP()

private:

	CComboTransSet*	m_pSetComboTrans;
	CBaseSet* m_pMainSet;
	long* m_pValore;

};

#endif /* _COMBOTRANSCOMBO_H_ */