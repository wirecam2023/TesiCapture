#ifndef _ADDDESCRDLG_H_
	#define _ADDDESCRDLG_H_

class CAddDescrDlg : public CDialog
{

public:

	CAddDescrDlg(CWnd* pParent, CString strTitle, int nLenght, CString strInit, long nExtMode, BOOL bUpperCase = FALSE);

	enum { IDD = IDD_ADD_COMBO };

	CEdit	m_ctrlDescription;
	CString	m_strDescription;
	                   
	long 	m_nExtMode;
	int		m_nLenghtMax;	                   
	CString m_strTitle;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	CStaticLocalize m_ctrlStaticLabel;
	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlButtonCancel;

	DECLARE_MESSAGE_MAP()

private:

	BOOL m_bUpperCase; // Sandro 05/05/2010 - RIMA 10-028.5 //

};

#endif /* _ADDDESCRDLG_H_ */