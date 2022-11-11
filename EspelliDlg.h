#ifndef _ESPELLIDLG_H_
	#define _ESPELLIDLG_H_

class CEspelliDlg : public CDialog
{

public:

	CEspelliDlg(CWnd* pParent = NULL, CString strLabel = "");

	enum { IDD = IDD_ESPELLI_OD };

	CEdit	m_ctrlLabel;
	CString	m_strLabel;
	CString	m_strTesto1;
	CString	m_strTesto2;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg void OnEspelli();

	DECLARE_MESSAGE_MAP()

	CButtonLocalize m_ctrlButtonEject, m_ctrlButtonOK, m_ctrlButtonCancel;
};

#endif /*_ESPELLIDLG_H_ */