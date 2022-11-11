#ifndef _NEWEDTCCDDLG_H_
	#define _NEWEDTCCDDLG_H_

class CNewEdtCCDDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewEdtCCDDlg)

public:

	CNewEdtCCDDlg(CWnd* pParent, UINT idTitle, long lIDEsame, long lIDCCD);
	~CNewEdtCCDDlg();

	enum { IDD = IDD_NEWEDTCCD_DLG };

	long GetIDCurSelForSearch();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeCombo();

private:

	void RiempiCombo();

	CString m_sTitle;
	long m_lIDEsame;
	long m_lIDCCD;

	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlButtonCancel;

	CComboBox m_ctrlCCD;

	long m_lIDCurSelForSearch;

};

#endif /* _NEWEDTCCDDLG_H_ */