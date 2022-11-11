#ifndef _GETCODEDLG_H_
	#define _GETCODEDLG_H_

class CGetCodeDlg : public CDialog
{

public:

	CGetCodeDlg(CWnd* pParent);

	enum { IDD = IDD_GETCODE };

	long m_lCode;
	CString m_sCode;

	long m_lCode2; //Julio 1/12/2017 Centralizacao
	CString m_sCode2;//Julio 1/12/2017 Centralizacao

	BOOL bCheckStatus = FALSE;

	virtual void OnOK();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:

	CButtonLocalize m_ctrlButtonCancel;
	CButtonLocalize m_ctrlButtonCheckStatus;
	CButtonLocalize m_ctrlButtonOK;

	CStaticLocalize m_ctrlStaticLabel;

public:
	afx_msg void OnBnClickedBtnCheckstatus();
};

#endif /* _GETCODEDLG_H_ */