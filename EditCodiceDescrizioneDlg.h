#ifndef _EDITCODICEDESCRIZIONEDLG_H_
	#define _EDITCODICEDESCRIZIONEDLG_H_

class CEditCodiceDescrizioneDlg : public CDialog
{
	DECLARE_DYNAMIC(CEditCodiceDescrizioneDlg)

public:

	CEditCodiceDescrizioneDlg(CWnd* pParent, const CString &strTitle, const CString &sCodice, const CString &sDescrizione);
	CEditCodiceDescrizioneDlg(CWnd* pParent, UINT idTitle, const CString &sCodice, const CString &sDescrizione);
	~CEditCodiceDescrizioneDlg();

	enum { IDD = IDD_EDITCODICEDESCRIZIONE_DLG };

	CString GetCodice();
	CString GetDescrizione();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEditValue();

private:

	CString m_sTitle;
	CString m_sCodice;
	CString m_sDescrizione;

	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlButtonCancel;

};

#endif /* _EDITCODICEDESCRIZIONEDLG_H_ */