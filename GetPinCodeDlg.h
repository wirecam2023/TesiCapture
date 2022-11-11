#ifndef _GETPINCODEDLG_H_
	#define _GETPINCODEDLG_H_

class CGetPinCodeDlg : public CDialog
{

public:

	CGetPinCodeDlg(CWnd* pParent);

	enum { IDD = IDD_GETPINCODE };

	CString m_sPinCode;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:

	CButtonLocalize m_ctrlButtonCancel;
	CButtonLocalize m_ctrlButtonOK;

	CStaticLocalize m_ctrlStaticLabel;

};

#endif /* _GETPINCODEDLG_H_ */