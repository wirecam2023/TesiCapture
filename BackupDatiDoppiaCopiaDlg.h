#ifndef _BACKUPDATIDOPPIACOPIADLG_H_
	#define _BACKUPDATIDOPPIACOPIADLG_H_

class CEsamiView;

class CBackupDatiDoppiaCopiaDlg : public CDialog
{
	DECLARE_DYNAMIC(CBackupDatiDoppiaCopiaDlg)

public:

	CBackupDatiDoppiaCopiaDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CBackupDatiDoppiaCopiaDlg();

	enum { IDD = IDD_BACKUP_DATI_DOPPIA_COPIA };

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

#endif /* _BACKUPDATIDOPPIACOPIADLG_H_ */