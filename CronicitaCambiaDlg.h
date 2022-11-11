#ifndef _CRONICITACAMBIADLG_H_
	#define _CRONICITACAMBIADLG_H_

class CCronicitaCambiaDlg : public CDialog
{
	DECLARE_DYNAMIC(CCronicitaCambiaDlg)

public:

	CCronicitaCambiaDlg(CWnd* pParent, long lIDCronicitaOld, long lIDCronicitaNew);
	virtual ~CCronicitaCambiaDlg();

	enum { IDD = IDD_CRONICITA_CAMBIA };

	long GetResult();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnBnClickedRadioMantieni();
	afx_msg void OnBnClickedRadioCambia();
	afx_msg void OnBnClickedBtnConferma();

private:

	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;
	CButton m_ctrlRadioMantieni;
	CButton m_ctrlRadioCambia;
	CButtonLocalize m_ctrlBtnConferma;

	//

	long m_lIDCronicitaOld;
	long m_lIDCronicitaNew;
	int m_nRadio;

};

#endif /* _CRONICITACAMBIADLG_H_ */