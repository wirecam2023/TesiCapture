#ifndef _TIPOESAMENEWDLG_H_
	#define _TIPOESAMENEWDLG_H_

class CEsamiView;

class CTipoEsameNewDlg : public CDialog
{
	DECLARE_DYNAMIC(CTipoEsameNewDlg)

public:

	CTipoEsameNewDlg(CWnd* pParent, CEsamiView* pEsamiView, BOOL bDisegnaReport, BOOL bCanCancel, long lForcedUO);
	~CTipoEsameNewDlg();

	enum { IDD = IDD_TIPOESAME_NEW };

	long GetTipoEsame();
	void SetTipoEsame(long lReturn);

	long GetUO();

	CComboBox m_ctrlCombo1;

protected:

	void DoDataExchange(CDataExchange* pDX);
	void OnCancel();
	BOOL OnInitDialog();
	void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedAltreUO();
	afx_msg void OnCbnSelchangeCombo1();
	
	LRESULT OnShowDropDown(WPARAM wparam, LPARAM lparam);

private:

	CEsamiView* m_pEsamiView;
	BOOL m_bDisegnaReport;
	BOOL m_bCanCancel;
	long m_lForcedUO;

	long m_lReturn;
	long m_lUO;

	CStaticLocalize m_ctrlStatic;
	CButtonLocalize m_ctrlBtnAltreUO;
	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnOK;

};

#endif /* _TIPOESAMENEW_H_ */