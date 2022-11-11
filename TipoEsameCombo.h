#ifndef _TIPOESAMECOMBO_H_
	#define _TIPOESAMECOMBO_H_

class CBaseSet;

class CTipoEsameCombo : public CComboBox
{

public:

	CTipoEsameCombo();
	virtual ~CTipoEsameCombo();

	CBaseSet* m_pMainSet;
	long* m_pTipoEsame;

	void SetParam(CBaseSet* pMainSet, long* pTipoEsame);

protected:

	afx_msg void OnCloseup();
	afx_msg void OnDropdown();

	DECLARE_MESSAGE_MAP()
};

#endif /* _TIPOESAMECOMBO_H_ */