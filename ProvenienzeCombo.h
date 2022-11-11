#ifndef _PROVENIENZECOMBO_H_
#define _PROVENIENZECOMBO_H_

class CProvenienzaSet;
class CBaseSet;

class CProvenienzeCombo : public CComboBox
{

public:

	CProvenienzeCombo();
	virtual ~CProvenienzeCombo();

	CBaseSet* m_pMainSet;
	long* m_pIdProvenienza;

	void SetParam(CBaseSet* pMainSet, long* pIdProvenienza);

protected:

	afx_msg void OnCloseup();
	afx_msg void OnDropdown();

	DECLARE_MESSAGE_MAP()
};

#endif /* _PROVENIENZECOMBO_H_ */