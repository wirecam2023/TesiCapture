#ifndef _UUOOUTENTIDLG_H_
	#define _UUOOUTENTIDLG_H_

class CUuOoUtentiDlg : public CDialog
{
	DECLARE_DYNAMIC(CUuOoUtentiDlg)

public:

	CUuOoUtentiDlg(CWnd* pParent);
	virtual ~CUuOoUtentiDlg();

	enum { IDD = IDD_UUOO_UTENTI };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnEsci();
	afx_msg void OnLbnSelchangeListUtenti();
	afx_msg void OnLbnSelchangeListUnitaOperative();

private:

	void RiempiListaUtenti();
	void RiempiListaUnitaOperative();
	void SelezionaUnitaOperative();

	// --- //

	CButtonLocalize m_ctrlBtnEsci;

	CListBox m_ctrlListUtenti;
	CListBox m_ctrlListUnitaOperative;

	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;

	// --- //

	long m_lIDUtente;
	CList<long> m_listIDUOSelezionate;

};

#endif /* _UUOOUTENTIDLG_H_ */