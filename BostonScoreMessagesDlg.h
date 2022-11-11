#ifndef _BOSTONSCOREMESSAGESDLG_H_
	#define _BOSTONSCOREMESSAGESDLG_H_

class CBostonScoreMessagesDlg : public CDialog
{
	DECLARE_DYNAMIC(CBostonScoreMessagesDlg)

public:

	CBostonScoreMessagesDlg(CWnd* pParent);
	virtual ~CBostonScoreMessagesDlg();

	enum { IDD = IDD_BOSTONSCORE_MESSAGES };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedAnnulla();
	afx_msg void OnBnClickedConferma();

private:

	CStaticLocalize m_ctrlStaticA;
	CStaticLocalize m_ctrlStaticB;

	CStatic m_ctrlStatic0;
	CStatic m_ctrlStatic1;
	CStatic m_ctrlStatic2;
	CStatic m_ctrlStatic3;
	CStatic m_ctrlStatic4;
	CStatic m_ctrlStatic5;
	CStatic m_ctrlStatic6;
	CStatic m_ctrlStatic7;
	CStatic m_ctrlStatic8;
	CStatic m_ctrlStatic9;

	CEdit m_ctrlEdit0;
	CEdit m_ctrlEdit1;
	CEdit m_ctrlEdit2;
	CEdit m_ctrlEdit3;
	CEdit m_ctrlEdit4;
	CEdit m_ctrlEdit5;
	CEdit m_ctrlEdit6;
	CEdit m_ctrlEdit7;
	CEdit m_ctrlEdit8;
	CEdit m_ctrlEdit9;

};

#endif /* _BOSTONSCOREMESSAGESDLG_H_ */