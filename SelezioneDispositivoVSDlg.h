#ifndef _SELEZIONEDISPOSITIVOVSDLG_H_
	#define _SELEZIONEDISPOSITIVOVSDLG_H_

class CSelezioneDispositivoVSDlg : public CDialog
{

public:

	CSelezioneDispositivoVSDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_SELEZIONEDISPOSITIVOVS };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedContinua();

	CString m_sCodiceDispositivoSelezionato;
	CString m_sNomeDispositivoMonitoraggio;
	long m_lIdDispositivo;

private:
	CStaticLocalize m_ctrlStatic1;
	CComboBox m_ctrlCmbDispositivo;
	CButtonLocalize m_ctrlBtnContinua;

public:
	afx_msg void OnBnClickedBtnAnnulla();
};

#endif