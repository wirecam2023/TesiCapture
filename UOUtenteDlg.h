#ifndef _UOUTENTEDLG_H_
	#define _UOUTENTEDLG_H_

class CEsamiView;

class CUOUtenteDlg : public CDialog
{
	DECLARE_DYNAMIC(CUOUtenteDlg)

public:

	CUOUtenteDlg(CWnd* pParent, long lIDUtente);
	~CUOUtenteDlg();

	enum { IDD = IDD_UO_UTENTE };

protected:

	void DoDataExchange(CDataExchange* pDX);
	BOOL OnInitDialog();
	void OnOK();

	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	DECLARE_MESSAGE_MAP()

private:

	long m_lIDUtente;
	long m_lUOAttuale;

	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnOk;
	CComboBox m_ctrlCombo1;

};

#endif /* _UOUTENTEDLG_H_ */