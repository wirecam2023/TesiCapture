#ifndef _SEDIESAMEUSEDLG_H_
	#define _SEDIESAMEUSEDLG_H_

class CEsamiView;

class CSediEsameUseDlg : public CDialog
{
	DECLARE_DYNAMIC(CSediEsameUseDlg)

public:

	CSediEsameUseDlg(CWnd* pParent, CEsamiView* pEsamiView);

	enum { IDD = IDD_SEDIESAME_USE_DLG };

	long GetSede();
	void SetSede(long lIDSede);

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();
	afx_msg void OnLbnDblclkListSedi();

	DECLARE_MESSAGE_MAP()

private:

	void RiempiListSedi();

	CListBox m_ctrlListSedi;

	CEsamiView* m_pEsamiView;

	long m_lIDSede;

};

#endif /* _SEDIESAMEUSEDLG_H_ */