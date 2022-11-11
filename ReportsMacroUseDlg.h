#ifndef _REPORTSMACROUSEDLG_H_
	#define _REPORTSMACROUSEDLG_H_

class CReportsMacroUseDlg : public CDialog
{
	DECLARE_DYNAMIC(CReportsMacroUseDlg)

public:

	CReportsMacroUseDlg(CWnd* pParent);
	virtual ~CReportsMacroUseDlg();

	enum { IDD = IDD_REPORTSMACRO_USE_DLG };

	long GetIDMacro();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListMacro(NMHDR *pNMHDR, LRESULT *pResult);

private:

	void RiempiLista();

	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnOK;
	CListCtrl m_ctrlList;

	long m_lIDMacro;

};

#endif /* _REPORTSMACROUSEDLG_H_ */