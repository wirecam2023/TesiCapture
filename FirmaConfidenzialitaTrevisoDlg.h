#ifndef _FIRMACONFIDENZIALITATREVISODLG_H_
	#define _FIRMACONFIDENZIALITATREVISODLG_H_

class CFirmaConfidenzialitaTrevisoDlg : public CDialog
{

	DECLARE_DYNAMIC(CFirmaConfidenzialitaTrevisoDlg)

public:

	CFirmaConfidenzialitaTrevisoDlg(CWnd* pParent);
	virtual ~CFirmaConfidenzialitaTrevisoDlg();

	enum { IDD = IDD_FIRMA_CONFIDENZIALITA_TREVISO };

	CString GetClassificazione();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedRadioNo();
	afx_msg void OnBnClickedRadioSi();

private:

	CString m_sClassificazione;

};

#endif /* _FIRMACONFIDENZIALITATREVISODLG_H_ */