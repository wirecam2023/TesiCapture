#ifndef _REGIONECOMBO_H_
	#define _REGIONECOMBO_H_

class CCodificaRegionaleExSet;

class CRegioneCombo : public CComboBox
{

public:

	CRegioneCombo();
	virtual ~CRegioneCombo();

	long* m_pRegione;

	void SetParam(long* pRegione, CEsamiView* pEsamiView);

protected:

	afx_msg void OnCloseup();
	afx_msg void OnDropdown();

	DECLARE_MESSAGE_MAP()

private:

	CEsamiView* m_pEsamiView;

};

#endif /* _REGIONECOMBO_H_ */
