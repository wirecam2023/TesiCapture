#ifndef _INTEGRAZIONI_PARAM_CONFIGUO_FORM_
#define _INTEGRAZIONI_PARAM_CONFIGUO_FORM_

class CIntegrazioniConfigurazioneModDlg;

class CIntegrazioniParamConfigUOForm : public CResizableDialog
{

public:

	CIntegrazioniParamConfigUOForm(CWnd* pParent, CIntegrazioniConfigurazioneModDlg* refertoDlg);
	~CIntegrazioniParamConfigUOForm();

	enum { IDD = IDD_INTEGRAZIONI_PARAM_UO };

	void Save();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	virtual void OnOK() {};
	virtual void OnCancel() {};

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnWorklist();
	afx_msg void OnBnClickedBtnOperatori();
	afx_msg void OnBnClickedBtnMedici();
	afx_msg void OnBnClickedBtnMediciInvianti();
	afx_msg void OnBnClickedBtnProvenienza();
	afx_msg void OnBnClickedBtnPrestazioni();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnSedi();
	afx_msg void OnBnClickedBtnReparti();
	afx_msg void OnBnClickedChkAnagrafeAttivo();
	afx_msg void OnBnClickedChkWorklist();
	afx_msg void OnBnClickedChkCostoprestazioniAttivo();
	afx_msg void OnBnClickedBtnSorgentistreaming();

private:

	CIntegrazioniConfigurazioneModDlg* m_pConfigDlg;

	void LoadAnagrafeCentrale();
	void LoadServer();
	void LoadLock();
	void LoadFirma();
	void LoadQueryman();
	void LoadWorklist();
	void LoadDicom();

	void SaveAnagrafeCentrale();
	void SaveServer();
	void SaveLock();
	void SaveFirma();
	void SaveQueryman();
	void SaveWorklist();
	void SaveDicom();

	void VerifyAnagrafeOptions();
	void VerifyWLOptions();

	//

	CButtonLocalize m_ctrlBtnOk;

	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;
	CStaticLocalize m_ctrlStatic11;
	CStaticLocalize m_ctrlStatic12;
	CStaticLocalize m_ctrlStatic13;
	CStaticLocalize m_ctrlStatic14;
	CStaticLocalize m_ctrlStatic15;
	CStaticLocalize m_ctrlStatic16;
	CStaticLocalize m_ctrlStatic18;
	CStaticLocalize m_ctrlStatic19;
	CStaticLocalize m_ctrlStatic22;

	CButtonLocalize m_ctrlBtnOperatori;
	CButtonLocalize m_ctrlBtnMedici;
	CButtonLocalize m_ctrlBtnProvenienza;
	CButtonLocalize m_ctrlBtnPrestazioni;
	CButtonLocalize m_ctrlBtnUrgenza;
	CButtonLocalize m_ctrlBtnReparti;
	CButtonLocalize m_ctrlBtnSedi;
	CButtonLocalize m_ctrlBtnMediciInvianti;
	CButtonLocalize m_ctrlBtnSorgentiStreaming;

	CButtonLocalize m_ctrlChkAnagrafeAttiva;
	CButtonLocalize m_ctrlChkAnagrafeLockInserimento;
	CButtonLocalize m_ctrlChkAnagrafeSoloCentrale;
	CButtonLocalize m_ctrlChkWorklist;
	CButtonLocalize m_ctrlChkWorklistIbrida;
	CButtonLocalize m_ctrlChkLockAttivo;

	CButtonLocalize m_ctrlBtnWorklistLayout;

	CEdit m_ctrlEdtAnagrafeIP;
	CEdit m_ctrlEdtAnagrafePorta;
	CEdit m_ctrlEdtQuerymanUrl;

	CComboBox m_ctrlCmbFirma;
	CComboBox m_ctrlCmbWorklistStatoDefault;
	CComboBox m_ctrlCmbWorklistFocus;
	CComboBox m_ctrlCmbDicomStoreMode;
	
};

#endif /* _INTEGRAZIONI_PARAM_CONFIGUO_FORM_ */