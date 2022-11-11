#ifndef _BACKUPDATIDLG_H_
	#define _BACKUPDATIDLG_H_

class CEsamiView;

class CBackupDatiDlg : public CDialog
{
	DECLARE_DYNAMIC(CBackupDatiDlg)

public:

	CBackupDatiDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CBackupDatiDlg();

	enum { IDD = IDD_BACKUP_DATI };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);

	afx_msg void OnClickedBtnCopia();
	afx_msg void OnClickedBtnSeconda();
	afx_msg void OnClickedBtnLibera();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:

	CEsamiView* m_pEsamiView;

	CButtonLocalize m_ctrlButton1,
		            m_ctrlButton2,
					m_ctrlButton3,
					m_ctrlButton4;
};

#endif /* _BACKUPDATIDLG_H_ */