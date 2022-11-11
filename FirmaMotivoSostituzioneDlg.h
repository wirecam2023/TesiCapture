#ifndef _FIRMAMOTIVOSOSTITUZIONEDLG_H_
	#define _FIRMAMOTIVOSOSTITUZIONEDLG_H_

class CFirmaMotivoSostituzioneDlg : public CDialog
{
	DECLARE_DYNAMIC(CFirmaMotivoSostituzioneDlg)

public:

	CFirmaMotivoSostituzioneDlg(CWnd* pParent);
	virtual ~CFirmaMotivoSostituzioneDlg();

	enum { IDD = IDD_FIRMA_MOTIVOSOSTITUZIONE };

	CString GetMotivo();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnAnnulla();
	afx_msg void OnBnClickedBtnConferma();
	afx_msg void OnEnChangeEditMotivo();

private:

	CString m_sMotivo;

};

#endif /* _FIRMAMOTIVOSOSTITUZIONEDLG_H_ */