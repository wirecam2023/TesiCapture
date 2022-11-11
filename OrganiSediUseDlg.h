#ifndef _ORGANISEDIUSEDLG_H_
	#define _ORGANISEDIUSEDLG_H_

class CEsamiView;

class COrganiSediUseDlg : public CDialog
{
	DECLARE_DYNAMIC(COrganiSediUseDlg)

public:

	COrganiSediUseDlg(CWnd* pParent, CEsamiView* pEsamiView);

	enum { IDD = IDD_ORGANISEDI_USE_DLG };

	CString GetOrgano();
	CString GetSede();
	long GetIdSede();
	void SetOrgano(CString strOrgano);
	void SetSede(CString strSede);

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnDeseleziona();
	afx_msg void OnLbnSelchangeListOrgani();
	DECLARE_MESSAGE_MAP()

private:
	void RiempiListaOrgani();
	void RiempiTreeSedi(long lOrgano);

	CListBox m_ctrlListOrgani;
	CTreeCtrl m_ctrlTreeSedi;

	CEsamiView* m_pEsamiView;

	CString m_strOrgano;
	CString m_strSede;
	long m_lIDSede;

	CButtonLocalize m_ctrlButtonDelsel, m_ctrlButtonOK, m_ctrlButtonCancel;
};

#endif /* _ORGANISEDIUSEDLG_H_ */