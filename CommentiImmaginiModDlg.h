#ifndef _COMMENTIMMAGINIMODDLG_H_
	#define _COMMENTIMMAGINIMODDLG_H_

class CCommentiImmaginiModDlg : public CDialog
{

	DECLARE_DYNAMIC(CCommentiImmaginiModDlg)

public:

	CCommentiImmaginiModDlg(CEsamiView* pParent);
	virtual ~CCommentiImmaginiModDlg();

	enum { IDD = IDD_COMMENTIIMMAGINI_MOD };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnNew();
	afx_msg void OnBnClickedBtnEdt();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnExit();

	afx_msg void OnCbnSelchangeComboTipoEsame();

	afx_msg void OnLvnItemchangedListCommenti(NMHDR *pNMHDR, LRESULT *pResult);

private:

	void RiempiComboTipoEsame();
	void RiempiListaCommenti(long lIDTipoEsame, long lIDCommentoDaSelezionare);
	void CheckFieldsToEnable();

	//

	CButtonLocalize m_ctrlBtnNew;
	CButtonLocalize m_ctrlBtnEdt;
	CButtonLocalize m_ctrlBtnDel;
	CButtonLocalize m_ctrlBtnExit;
	CButtonLocalize m_ctrlChkAttiva;
	CButtonLocalize m_ctrlChkNoEdit;

	CComboBox m_ctrlCmbTipoEsame;

	CListCtrl m_ctrlListCommenti;

	CStaticLocalize m_ctrlStaticTipoEsame;

	CEsamiView* m_pEsamiView;

	//

	long m_lIDTipoEsame;

public:
	afx_msg void OnBnClickedChkAttiva();
	afx_msg void OnBnClickedChkNoeditable();
};

#endif /* _COMMENTIMMAGINIMODDLG_H_ */