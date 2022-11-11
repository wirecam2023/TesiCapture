#ifndef _INTEGRAZIONICONFIGURAZIONEMODDLG_H_
	#define _INTEGRAZIONICONFIGURAZIONEMODDLG_H_

class m_pEsamiView;

#define _NUMERO_TAB 4

class CIntegrazioniConfigurazioneModDlg : public CResizableDialog
{
	DECLARE_DYNAMIC(CIntegrazioniConfigurazioneModDlg)

public:

	CIntegrazioniConfigurazioneModDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CIntegrazioniConfigurazioneModDlg();

	enum { IDD = IDD_INTEGRAZIONI };

	CTabCtrlLocalize	m_ctrlTab;
	long				m_lTab;	

	CEsamiView* m_pEsamiView;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnDestroy();
	virtual void OnOK();
	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()	

	afx_msg void OnTabPageSelChange(NMHDR* pNMHDR, LRESULT* pResult);

private:

	CResizableDialog* m_pForms[_NUMERO_TAB];
	
	CButtonLocalize m_ctrlExit, m_ctrlAbort;

	void TabSelChange();

};

#endif /* _INTEGRAZIONICONFIGURAZIONEMODDLG_H_ */