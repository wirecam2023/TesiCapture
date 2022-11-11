#ifndef _CALIBDLG_H_
	#define _CALIBDLG_H_

class CCalib;

class CCalibDlg : public CDialog
{   

public:

	CCalibDlg(CWnd* pParent, CEsamiView* pEsamiView, CCalibList* pCalibList);

	enum { IDD = IDD_CALIB };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
    virtual BOOL OnInitDialog();
	virtual void OnOK();
    
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBtnNew();
	afx_msg void OnBtnEdt();
	afx_msg void OnBtnDel();

	afx_msg void OnSelChangeListaMisure();

private:

	CStaticLocalize m_ctrlStaticScreen;
	CStaticLocalize m_ctrlStaticReal;

	CButtonLocalize m_ctrlBtnNew;
	CButtonLocalize m_ctrlBtnEdt;
	CButtonLocalize m_ctrlBtnDel;

	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnOK;

	// --- //

	CEsamiView* m_pEsamiView;
    CCalibList* m_pCalibList;

	CListBox m_ctrlCalib;

};

#endif /* _CALIBDLG_H_ */