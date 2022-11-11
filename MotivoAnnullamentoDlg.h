#ifndef _MOTIVOANNULLAMENTODLG_H_
	#define _MOTIVOANNULLAMENTODLG_H_

class CMotivoAnnullamentoDlg : public CDialog
{
	DECLARE_DYNAMIC(CMotivoAnnullamentoDlg)

public:

	CMotivoAnnullamentoDlg(CWnd* pParent);
	~CMotivoAnnullamentoDlg();

	enum { IDD = IDD_NEWEDTCCD_DLG };

	long GetIDMotivo();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeCombo();

private:

	void RiempiCombo();

	//

	CButtonLocalize m_ctrlButtonOK;
	CButtonLocalize m_ctrlButtonCancel;

	CComboBox m_ctrlComboMotivo;

	//

	long m_lIDMotivo;

};

#endif /* _MOTIVOANNULLAMENTODLG_H_ */