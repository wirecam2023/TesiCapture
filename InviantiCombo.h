#ifndef _INVIANTICOMBO_H_
	#define _INVIANTICOMBO_H_

class CInviantiSet;
class CBaseSet;

class CInviantiCombo : public CComboBox
{

public:

	CInviantiCombo();
	virtual ~CInviantiCombo();

	CBaseSet* m_pMainSet;
	long* m_pProvenienza;
	long* m_pInviante;

	void SetParam(CBaseSet* pMainSet, long* pInviante, long* pProvenienza);

protected:

	afx_msg void OnCloseup();
	afx_msg void OnDropdown();

	DECLARE_MESSAGE_MAP()
};

#endif /* _INVIANTICOMBO_H_ */