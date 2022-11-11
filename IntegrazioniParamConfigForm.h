#ifndef _INTEGRAZIONI_PARAM_CONFIG_FORM_
#define _INTEGRAZIONI_PARAM_CONFIG_FORM_

class CIntegrazioniConfigurazioneModDlg;

class CIntegrazioniParamConfigForm : public CResizableDialog
{

public:

	enum { IDD = IDD_INTEGRAZIONI_PARAM };

	CIntegrazioniParamConfigForm(CWnd* pParent, CIntegrazioniConfigurazioneModDlg* refertoDlg);
	~CIntegrazioniParamConfigForm();

	void Save();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	virtual void OnOK() {};
	virtual void OnCancel() {};
	
	DECLARE_MESSAGE_MAP()

private:
	CIntegrazioniConfigurazioneModDlg* m_pConfigDlg;

	void LoadLDAP();
	void LoadGestionePazienti();

	void SaveLDAP();
	void SaveGestionePazienti();

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CStaticLocalize m_ctrlStatic4;
	CStaticLocalize m_ctrlStatic5;
	CStaticLocalize m_ctrlStatic6;

	CButtonLocalize m_ctrlBtnUO;	
	CEdit m_ctrlEdtLDAPUrl;
	CComboBox m_ctrlCmbLDAP;
	CButtonLocalize m_ctrlChkPazientiSporchi;
	
public:	

	afx_msg void OnBnClickedBtnUo();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);	
	afx_msg void OnBnClickedBtnLivelliurgenza();

};

#endif /* _INTEGRAZIONI_PARAM_CONFIG_FORM_ */