#ifndef _UUOOGRUPPIDLG_H_
	#define _UUOOGRUPPIDLG_H_

class CUuOoGruppiDlg : public CDialog
{
	DECLARE_DYNAMIC(CUuOoGruppiDlg)

public:

	CUuOoGruppiDlg(CWnd* pParent);
	virtual ~CUuOoGruppiDlg();

	enum { IDD = IDD_UUOO_GRUPPI };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnEsci();
	afx_msg void OnLbnSelchangeListGruppi();
	afx_msg void OnLbnSelchangeListUnitaOperative();

private:

	void RiempiListaGruppi();
	void RiempiListaUnitaOperative();
	void SelezionaUnitaOperativa();

	// --- //

	CButtonLocalize m_ctrlBtnEsci;

	CListBox m_ctrlListGruppi;
	CListBox m_ctrlListUnitaOperative;

	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;

	// --- //

	long m_lIDGruppo;

};

#endif /* _UUOOGRUPPIDLG_H_ */