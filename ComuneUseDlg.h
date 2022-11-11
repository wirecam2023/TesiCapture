#ifndef _COMUNEUSEDLG_H_
	#define _COMUNEUSEDLG_H_

class CEsamiView;

class CComuneUseDlg : public CDialog
{
	DECLARE_DYNAMIC(CComuneUseDlg)

public:

	CComuneUseDlg(CWnd* pParent, CEsamiView* pEsamiView);

	enum { IDD = IDD_COMUNE_USE_DLG };

	long GetIDComune();
	CString GetComune();
	CString GetCAP();
	CString GetProvincia();
	void SetIDComune(long lComune);

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtnDeseleziona();
	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

private:

	void CaricaComuni();

	CComboBox m_ctrlComboComuni;

	CButtonLocalize m_ctrlBtnDeseleziona;
	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnOK;

	CEsamiView* m_pEsamiView;

	long m_lIDComune;
	CString m_strComune;
	CString m_strCAP;
	CString m_strProvincia;

};

#endif /* _COMUNEUSEDLG_H_ */