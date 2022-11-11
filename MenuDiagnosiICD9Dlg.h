#ifndef _MENUDIAGNOSIICD9DLG_H_
#define _MENUDIAGNOSIICD9DLG_H_

class CMenuDiagnosiICD9Dlg : public CDialog
{

public:

	CMenuDiagnosiICD9Dlg(CWnd* pParent, long lInit, CString strInit, int nProgramMode, CRect rect, CString* sQuery, CString* sQueryView);
	virtual ~CMenuDiagnosiICD9Dlg();

	enum { IDD = IDD_MENU_DIAGNOSIICD9 };

	long m_lContatore;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnClose();
	afx_msg void OnReset();
	afx_msg void OnBtnAnd();
	afx_msg void OnBtnOr();
	afx_msg void OnChangeRicerca();
	afx_msg void OnLvnItemchangedLista(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnTimer(UINT_PTR nIDEvent);

private:

	void FillDiagnosiList(CString filter);

	//

	CButtonLocalize m_ctrlButtonReset;
	CButtonLocalize m_ctrlButtonClose;

	CListCtrl m_ctrLista;
	CEdit m_ctrlRicerca;

	CEdit m_ctrlQuery;

	//

	BOOL m_bModalitaRicerca;	
	BOOL m_bOrPressed;

	int m_nItemCount;
	int m_nItemPressed;

	CRect m_rect;

	long m_lRicerca;
	CString m_strRicerca;

	//

	CString* m_pStrQuery;
	CString* m_pStrQueryView;

	BOOL m_bTastoCliccato;
	
};

#endif /* _MENUDIAGNOSIICD9DLG_H_ */