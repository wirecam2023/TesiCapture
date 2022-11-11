#ifndef _EDITCODIFICAREGIONALEDLG_H_
	#define _EDITCODIFICAREGIONALEDLG_H_

class CEditCodificaRegionaleDlg : public CDialog
{
	DECLARE_DYNAMIC(CEditCodificaRegionaleDlg)

public:

	CEditCodificaRegionaleDlg(CWnd* pParent, long lIDProcedura, long lQuantita, const CString &sTestoLibero);
	~CEditCodificaRegionaleDlg();

	enum { IDD = IDD_EDITCODIFICAREGIONALE_DLG };

	long GetIDProcedura();
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

	long m_lIDProcedura;
	long m_lQuantita;
	CString m_sTestoLibero;

	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlButtonCancel;

	CListCtrl m_ctrlListVoci;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;

};

#endif /* _EDITCODIFICAREGIONALEDLG_H_ */