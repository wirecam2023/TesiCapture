#ifndef _COMBODYNCAMPODLG_H_
	#define _COMBODYNCAMPODLG_H_

class CComboDynCampoDlg : public CDialog
{
	DECLARE_DYNAMIC(CComboDynCampoDlg)

public:

	CComboDynCampoDlg(CWnd* pParent, UINT idTitle, const CString &sValue);
	~CComboDynCampoDlg();

	enum { IDD = IDD_COMBODYNCAMPO_DLG };

	long GetIDCampo();
	long GetTipoCampo();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeComboCampi();

private:

	void RiempiComboCampi();

	//

	long m_lIDCampo;
	long m_lTipoCampo;

	CString m_sTitle;
	CString m_sValue;

	int m_nIndexScores;
	int m_nIndexFarmaci;

	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlButtonCancel;

	CComboBox m_ctrlComboCampi;

};

#endif /* _COMBODYNCAMPODLG_H_ */