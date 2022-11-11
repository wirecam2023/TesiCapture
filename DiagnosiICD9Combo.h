#ifndef _DIAGNOSIICD9COMBO_H_
	#define _DIAGNOSIICD9COMBO_H_

class CDiagnosiICD9Combo : public CComboBox
{

public:

	CDiagnosiICD9Combo();
	virtual ~CDiagnosiICD9Combo();

	void SetParam(CEsamiView* pEsamiView, long* pDiagnosi);

protected:

	afx_msg void OnCloseup();
	afx_msg void OnDropdown();

	DECLARE_MESSAGE_MAP()

private:

	CEsamiView* m_pEsamiView;
	long* m_pDiagnosi;

};

#endif /* _DIAGNOSIICD9COMBO_H_ */
