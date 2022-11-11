#ifndef _SALEESAMEUSEDLG_H_
	#define _SALEESAMEUSEDLG_H_

class CEsamiView;

class CSaleEsameUseDlg : public CDialog
{
	DECLARE_DYNAMIC(CSaleEsameUseDlg)

public:

	CSaleEsameUseDlg(CWnd* pParent, CEsamiView* pEsamiView, long idSedeSel);

	enum { IDD = IDD_SALEESAME_USE_DLG };

	CString GetSala();
	void SetSala(CString strSala);

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();
	afx_msg void OnLbnDblclkListSale();

	DECLARE_MESSAGE_MAP()

private:

	void RiempiListSale();

	CListBox m_ctrlListSale;

	CEsamiView* m_pEsamiView;

	CString m_strSala;

	long m_lIdSedeSel;

};

#endif /* _SALEESAMEUSEDLG_H_ */