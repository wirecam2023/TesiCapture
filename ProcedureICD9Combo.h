#ifndef _PROCEDUREICD9COMBO_H_
	#define _PROCEDUREICD9COMBO_H_

class CProcedureICD9Combo : public CComboBox
{

public:

	CProcedureICD9Combo();
	virtual ~CProcedureICD9Combo();

	void SetParam(CEsamiView* pEsamiView, long* pProcedura);

protected:

	afx_msg void OnCloseup();
	afx_msg void OnDropdown();

	DECLARE_MESSAGE_MAP()

private:

	CEsamiView* m_pEsamiView;
	long* m_pProcedura;

};

#endif /* _PROCEDUREICD9COMBO_H_ */
