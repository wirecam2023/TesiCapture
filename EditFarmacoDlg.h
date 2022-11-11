#ifndef _EDITFARMACODLG_H_
	#define _EDITFARMACODLG_H_

class CEditFarmacoDlg : public CDialog
{
	DECLARE_DYNAMIC(CEditFarmacoDlg)

public:

	CEditFarmacoDlg(CWnd* pParent, long lIDFarmaco, long lQuantita, const CString &sTestoLibero);
	~CEditFarmacoDlg();

	enum { IDD = IDD_EDITFARMACO_DLG };

	long GetIDFarmaco();
	long GetQuantita();
	CString GetTestoLibero();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEditVoci();
	afx_msg void OnLvnItemchangedListVoci(NMHDR *pNMHDR, LRESULT *pResult);

private:

	void RiempiListaVoci();

	// --- //

	long m_lIDFarmaco;
	long m_lQuantita;
	CString m_sTestoLibero;

	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlButtonCancel;

	CListCtrl m_ctrlListVoci;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;

};

#endif /* _EDITFARMACODLG_H_ */