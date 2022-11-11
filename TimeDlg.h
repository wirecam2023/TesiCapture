#ifndef _TIMEDLG_H_
	#define _TIMEDLG_H_

class CTimeDlg : public CDialog
{

public:

	CTimeDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_TIME };

	CComboBox	m_ctrlOperatore;
	CDateTimeCtrl	m_ctrlTime1;
	CDateTimeCtrl	m_ctrlTime2;

	CString m_strRicerca;
	CString	m_strRicercaView;
	
protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	afx_msg void OnSelchangeComboTipo();
	afx_msg void OnTime1Change(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTime2Change(NMHDR* pNMHDR, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()

	CButtonLocalize m_ctrlButtonCancel, m_ctrlButtonOK;
	CStaticLocalize m_ctrlStaticFrom, m_ctrlStaticOperator, m_ctrlStaticTo;

private:

	void SetDlgMember();

};

#endif /* _TIMEDLG_H_ */