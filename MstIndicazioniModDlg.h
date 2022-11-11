#ifndef _MSTINDICAZIONIMODDLG_H_
	#define _MSTINDICAZIONIMODDLG_H_

class CMstIndicazioniModDlg : public CDialog
{
	DECLARE_DYNAMIC(CMstIndicazioniModDlg)

public:

	CMstIndicazioniModDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CMstIndicazioniModDlg();

	enum { IDD = IDD_MST_INDICAZIONI_MOD };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnBnClickedBtnNew0();
	afx_msg void OnBnClickedBtnEdt0();
	afx_msg void OnBnClickedBtnDel0();
	afx_msg void OnBnClickedBtnNew1();
	afx_msg void OnBnClickedBtnEdt1();
	afx_msg void OnBnClickedBtnDel1();
	afx_msg void OnCbnSelchangeComboEsame();
	afx_msg void OnLbnSelchangeListLevel0();
	afx_msg void OnLbnSelchangeListLevel1();

	DECLARE_MESSAGE_MAP()

private:

	void RiempiComboEsame();
	void RiempiLevel0(long lContatore);
	void RiempiLevel1(long lContatore);

	CEsamiView* m_pEsamiView;

	CComboBox m_ctrlComboEsame;
	CListBox m_ctrlListLevel0;
	CListBox m_ctrlListLevel1;

	CButtonLocalize m_ctrlButtonNew1,
		            m_ctrlButtonEdit1,
					m_ctrlButtonDelete1,
					m_ctrlButtonNew2,
		            m_ctrlButtonEdit2,
					m_ctrlButtonDelete2,
					m_ctrlButtonCancel;
};

#endif /* _MSTINDICAZIONIMODDLG_H_ */