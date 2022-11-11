#ifndef _SEARCHTYPEDLG_H_
	#define _SEARCHTYPEDLG_H_

enum searchType
{
	anagrafe = 0,
	ricoverati,
	ps
};

class CSearchTypeDlg : public CDialog
{

public:

	CSearchTypeDlg(CWnd* pParent=NULL);

	enum { IDD = IDD_SEARCHTYPEDLG };

	searchType m_searchType;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnOK();
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	CButtonLocalize m_ctrlButtonAnagrafe, m_ctrlButtonRicoveri, m_ctrlButtonPS;
	CStaticLocalize m_ctrlStaticMessage;

public:
	afx_msg void OnBnClickedBtnAnagrafe();
	afx_msg void OnBnClickedBtnRicoveri();
	afx_msg void OnBnClickedBtnPs();
};

#endif /* _SEARCHTYPEDLG_H_ */