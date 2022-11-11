#ifndef _INTEGRAZIONI_VITALSIGN_CONFIG_FORM_
	#define _INTEGRAZIONI_VITALSIGN_CONFIG_FORM_

#include "DLL_Imaging\h\AmListCtrl.h"

class CIntegrazioniConfigurazioneModDlg;

class CIntegrazioniVitalSignConfigForm : public CResizableDialog
{

public:
	enum { IDD = IDD_INTEGRAZIONI_VITALSIGN };
	CIntegrazioniVitalSignConfigForm(CWnd* pParent, CIntegrazioniConfigurazioneModDlg* refertoDlg);
	~CIntegrazioniVitalSignConfigForm();

	void Save();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnNuovoDispositivo();
	afx_msg void OnEliminaDispositivo();

private:
	CIntegrazioniConfigurazioneModDlg* m_pConfigDlg;

	void Load();	
	BOOL VerifyActive();
	void SetActive(BOOL bActive);
	void RiempiListaDispositivi();
	
	CButtonLocalize m_ctrlBtnAttiva;
	CStaticLocalize m_ctrlStatic1, m_ctrlStatic2;
	CEdit m_ctrlEdtWebservice;
	CAMEditComboListCtrl m_ctrlListDispositivi;

public:

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnBnClickedChkAttiva();
	afx_msg void OnNMRClickListDispositivi(NMHDR *pNMHDR, LRESULT *pResult);
};

#endif