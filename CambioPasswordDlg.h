#ifndef _CAMBIOPASSWORDDLG_H_
	#define _CAMBIOPASSWORDDLG_H_

class CCambioPasswordDlg : public CDialog
{
	DECLARE_DYNAMIC(CCambioPasswordDlg)

public:

	CCambioPasswordDlg(CWnd* pParent);
	virtual ~CCambioPasswordDlg();

	enum { IDD = IDD_CAMBIOPASSWORD };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

private:

	CString m_sPwdOld;
	CString m_sPwdNew1;
	CString m_sPwdNew2;

};

#endif /* _CAMBIOPASSWORDDLG_H_ */