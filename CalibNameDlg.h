#ifndef _CALIBLISTNAMEDLG_H_
	#define _CALIBLISTNAMEDLG_H_

class CCalibNameDlg : public CDialog
{

	DECLARE_DYNCREATE(CCalibNameDlg)

public:

	CCalibNameDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_NOME_CALIB };

	CString	m_strName;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	CButtonLocalize m_ctrlCancel;
	CButtonLocalize m_ctrlOK;

};

#endif /* _CALIBLISTNAMEDLG_H_ */