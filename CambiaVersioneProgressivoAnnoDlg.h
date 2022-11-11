#ifndef _CAMBIAVERSIONEPROGRESSIVOANNODLG_H_
	#define _CAMBIAVERSIONEPROGRESSIVOANNODLG_H_

class CCambiaVersioneProgressivoAnnoDlg : public CDialog
{
	DECLARE_DYNAMIC(CCambiaVersioneProgressivoAnnoDlg)

public:

	CCambiaVersioneProgressivoAnnoDlg(CWnd* pParent, long lIDEsameOLD, long lIDEsameNEW, long lIDVersioneOLD, CString sProgressivoAnnoOLD);
	virtual ~CCambiaVersioneProgressivoAnnoDlg();

	enum { IDD = IDD_CAMBIA_VERSIONE_PROGRESSIVOANNO };

	long GetNewIDVersione();
	CString GetNewProgressivoAnno();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnConferma();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

private:

	BOOL ProgressiviDifferenti(CString sProgressivo1, CString sProgressivo2);

	// --- //

	CButton m_ctrlButtonConferma;
	CButton m_ctrlCheck1;
	CButton m_ctrlCheck2;
	CStatic m_ctrlStaticLabel1;
	CStaticLocalize m_ctrlStaticLabel2;

	// --- //

	long m_lIDEsameOLD;
	long m_lIDEsameNEW;

	long m_lIDVersioneOLD;
	long m_lIDVersioneNEW;

	CString m_sProgressivoAnnoOLD;
	CString m_sProgressivoAnnoNEW;

	long m_lCountdown;

	// --- //

	BOOL m_bFlagIDVersione;
	BOOL m_bFlagProgressivoAnno;

};

#endif /* _CAMBIAVERSIONEPROGRESSIVOANNODLG_H_ */