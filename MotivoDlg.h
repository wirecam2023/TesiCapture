#pragma once

class CMotivoDlg : public CDialog
{
	DECLARE_DYNAMIC(CMotivoDlg)

public:

	CMotivoDlg(CWnd* pParent, CString sStatic1, CString sStatic2, BOOL bShowAnnulla=TRUE);
	virtual ~CMotivoDlg();

	enum { IDD = IDD_MOTIVO };

	CString GetMotivo();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnAnnulla();
	afx_msg void OnBnClickedBtnConferma();
	afx_msg void OnEnChangeEditMotivo();

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;

private:

	CString m_sMotivo;
	CString m_sStatic1, m_sStatic2;
	BOOL m_bShowAnnulla;

};
