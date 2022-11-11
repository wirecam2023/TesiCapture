#ifndef _MSTCODIFICADIAGNOSIESAMEMODDLG_H_
	#define _MSTCODIFICADIAGNOSIESAMEMODDLG_H_

class CMstCodificaDiagnosiEsameModDlg : public CDialog
{
	DECLARE_DYNAMIC(CMstCodificaDiagnosiEsameModDlg)

public:

	CMstCodificaDiagnosiEsameModDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CMstCodificaDiagnosiEsameModDlg();

	enum { IDD = IDD_MST_CODIFICADIAGNOSIESAME_MOD };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCbnSelchangeComboTipoesame();
	afx_msg void OnLbnSelchangeListLevel0();
	afx_msg void OnLbnSelchangeListLevel1();
	afx_msg void OnLbnSelchangeListLevel2();
	afx_msg void OnLbnSelchangeListLevel3();
	afx_msg void OnLbnSelchangeListLevel4();
	afx_msg void OnLbnSelchangeListLevel5();
	afx_msg void OnLbnSelchangeListLevel6();
	afx_msg void OnLbnSelchangeListLevel7();
	afx_msg void OnLbnSelchangeListLevel8();
	afx_msg void OnLbnSelchangeListLevel9();
	afx_msg void OnLbnSelchangeListLevel10();
	afx_msg void OnBnClickedBtnNew0();
	afx_msg void OnBnClickedBtnEdt0();
	afx_msg void OnBnClickedBtnDel0();
	afx_msg void OnBnClickedBtnNew1();
	afx_msg void OnBnClickedBtnEdt1();
	afx_msg void OnBnClickedBtnDel1();
	afx_msg void OnBnClickedBtnNew2();
	afx_msg void OnBnClickedBtnEdt2();
	afx_msg void OnBnClickedBtnDel2();
	afx_msg void OnBnClickedBtnNew3();
	afx_msg void OnBnClickedBtnEdt3();
	afx_msg void OnBnClickedBtnDel3();
	afx_msg void OnBnClickedBtnNew4();
	afx_msg void OnBnClickedBtnEdt4();
	afx_msg void OnBnClickedBtnDel4();
	afx_msg void OnBnClickedBtnNew5();
	afx_msg void OnBnClickedBtnEdt5();
	afx_msg void OnBnClickedBtnDel5();
	afx_msg void OnBnClickedBtnNew6();
	afx_msg void OnBnClickedBtnEdt6();
	afx_msg void OnBnClickedBtnDel6();
	afx_msg void OnBnClickedBtnNew7();
	afx_msg void OnBnClickedBtnEdt7();
	afx_msg void OnBnClickedBtnDel7();
	afx_msg void OnBnClickedBtnNew8();
	afx_msg void OnBnClickedBtnEdt8();
	afx_msg void OnBnClickedBtnDel8();
	afx_msg void OnBnClickedBtnNew9();
	afx_msg void OnBnClickedBtnEdt9();
	afx_msg void OnBnClickedBtnDel9();
	afx_msg void OnBnClickedBtnNew10();
	afx_msg void OnBnClickedBtnEdt10();
	afx_msg void OnBnClickedBtnDel10();

	DECLARE_MESSAGE_MAP()

private:

	void NewString(long lPadre, long lLivello);
	void EdtString(long lContatore);
	void DelString(long lContatore);

	void RiempiComboTipoEsame();
	void RiempiListLevel0();
	void RiempiListSubLevels(long lPadre);

	CEsamiView* m_pEsamiView;

	CComboBox m_ctrlComboTipoEsame;
	CListBox m_ctrlListLevel0;
	CListBox m_ctrlListLevel1;
	CListBox m_ctrlListLevel2;
	CListBox m_ctrlListLevel3;
	CListBox m_ctrlListLevel4;
	CListBox m_ctrlListLevel5;
	CListBox m_ctrlListLevel6;
	CListBox m_ctrlListLevel7;
	CListBox m_ctrlListLevel8;
	CListBox m_ctrlListLevel9;
	CListBox m_ctrlListLevel10;

	long m_lTipoEsame;

	CStaticLocalize m_ctrlStaticLevel0,
		            m_ctrlStaticLevel1,
		            m_ctrlStaticLevel2,
		            m_ctrlStaticLevel3,
		            m_ctrlStaticLevel4,
		            m_ctrlStaticLevel5,
		            m_ctrlStaticLevel6,
		            m_ctrlStaticLevel7,
		            m_ctrlStaticLevel8,
		            m_ctrlStaticLevel9,
		            m_ctrlStaticLevel10;
	CButtonLocalize m_ctrlButtonNew0,
		            m_ctrlButtonNew1,
		            m_ctrlButtonNew2,
		            m_ctrlButtonNew3,
		            m_ctrlButtonNew4,
		            m_ctrlButtonNew5,
		            m_ctrlButtonNew6,
		            m_ctrlButtonNew7,
		            m_ctrlButtonNew8,
		            m_ctrlButtonNew9,
		            m_ctrlButtonNew10,
		            m_ctrlButtonEdt0,
		            m_ctrlButtonEdt1,
		            m_ctrlButtonEdt2,
		            m_ctrlButtonEdt3,
		            m_ctrlButtonEdt4,
		            m_ctrlButtonEdt5,
		            m_ctrlButtonEdt6,
		            m_ctrlButtonEdt7,
		            m_ctrlButtonEdt8,
		            m_ctrlButtonEdt9,
		            m_ctrlButtonEdt10,
		            m_ctrlButtonDel0,
		            m_ctrlButtonDel1,
		            m_ctrlButtonDel2,
		            m_ctrlButtonDel3,
		            m_ctrlButtonDel4,
		            m_ctrlButtonDel5,
		            m_ctrlButtonDel6,
		            m_ctrlButtonDel7,
		            m_ctrlButtonDel8,
		            m_ctrlButtonDel9,
		            m_ctrlButtonDel10,
					m_ctrlButtonCancel;
};

#endif /* _MSTCODIFICADIAGNOSIESAMEMODDLG_H_ */