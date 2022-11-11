#ifndef _PASSWORDDLG_H_
	#define _PASSWORDDLG_H_

class CPasswordDlg : public CDialog
{

public:

	CPasswordDlg(CWnd* pParent, CString sTitle, CString sPasswordInput);
	CPasswordDlg(CWnd* pParent, CString sTitle, CString sDescription, CString sPasswordInput);

	enum { IDD1 = IDD_PASSWORD1 };
	enum { IDD2 = IDD_PASSWORD2 };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

private:

	CString m_sTitle;
	CString m_sDescription;
	CString m_sPasswordInput;

	int m_iCounter;
	CString m_sPasswordUser;

	CButtonLocalize m_ctrlButtonCancel;
	CButtonLocalize m_ctrlButtonOK;
	CStaticLocalize m_ctrlStatic;

	//

	UINT m_uiIDD;

};

#endif /* _PASSWORDDLG_H_ */