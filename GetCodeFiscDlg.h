#ifndef _GETCODEFISCDLG_H_
	#define _GETCODEFISCDLG_H_

class CGetCodeFiscDlg : public CDialog
{

public:

	CGetCodeFiscDlg(CWnd* pParent);

	enum { IDD = IDD_GETCODE_FISC };

	CString m_sCode;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

private:

	CButtonLocalize m_ctrlButtonCancel;

	CStaticLocalize m_ctrlStaticLabel;

};

#endif /* _GETCODEFISCDLG_H_ */