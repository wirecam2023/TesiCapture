#ifndef _CONFERMAELIMINAZIONEDLG_H_
	#define _CONFERMAELIMINAZIONEDLG_H_

class CConfermaEliminazioneDlg : public CDialog
{
	DECLARE_DYNAMIC(CConfermaEliminazioneDlg)

public:

	CConfermaEliminazioneDlg(CWnd* pParent, CString sElementiSelezionati);
	virtual ~CConfermaEliminazioneDlg();

	enum { IDD = IDD_CONFERMA_ELIMINAZIONE };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnAnnullaEliminazione();
	afx_msg void OnBnClickedBtnConfermaEliminazione();

	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

private:

	CButtonLocalize m_ctrlButtonAnnullaEliminazione;
	CButton m_ctrlButtonConfermaEliminazione;
	CStaticLocalize m_ctrlStaticLabel1;
	CStatic m_ctrlStaticLabel2;

	// --- //

	long m_lCountdown;
	CString m_sElementiSelezionati;

};

#endif /* _CONFERMAELIMINAZIONEDLG_H_ */