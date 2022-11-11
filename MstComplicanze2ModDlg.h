#ifndef _MSTCOMPLICANZE2MODDLG_H_
	#define _MSTCOMPLICANZE2MODDLG_H_

class CMstComplicanze2ModDlg : public CDialog
{
	DECLARE_DYNAMIC(CMstComplicanze2ModDlg)

public:

	CMstComplicanze2ModDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CMstComplicanze2ModDlg();

	enum { IDD = IDD_MST_COMPLICANZE2_MOD };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLbnSelchangeListLevel0();
	afx_msg void OnLbnSelchangeListLevel1();
	afx_msg void OnLbnSelchangeListLevel2();
	afx_msg void OnLbnSelchangeListLevel3();
	afx_msg void OnLbnSelchangeListLevel4();
	afx_msg void OnLbnSelchangeListLevel5();
	afx_msg void OnLbnSelchangeListLevel6();
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

	DECLARE_MESSAGE_MAP()

private:

	void NewString(long lPadre, long lLivello);
	void EdtString(long lID);
	void DelString(long lID);

	void RiempiListLevel0();
	void RiempiListSubLevels(long lPadre);

	CEsamiView* m_pEsamiView;

	CListBox m_ctrlListLevel0;
	CListBox m_ctrlListLevel1;
	CListBox m_ctrlListLevel2;
	CListBox m_ctrlListLevel3;
	CListBox m_ctrlListLevel4;
	CListBox m_ctrlListLevel5;
	CListBox m_ctrlListLevel6;

	CStaticLocalize m_ctrlStaticLevel0;
	CStaticLocalize m_ctrlStaticLevel1;
	CStaticLocalize m_ctrlStaticLevel2;
	CStaticLocalize m_ctrlStaticLevel3;
	CStaticLocalize m_ctrlStaticLevel4;
	CStaticLocalize m_ctrlStaticLevel5;
	CStaticLocalize m_ctrlStaticLevel6;

	CButtonLocalize m_ctrlButtonNew0;
	CButtonLocalize m_ctrlButtonNew1;
	CButtonLocalize m_ctrlButtonNew2;
	CButtonLocalize m_ctrlButtonNew3;
	CButtonLocalize m_ctrlButtonNew4;
	CButtonLocalize m_ctrlButtonNew5;
	CButtonLocalize m_ctrlButtonNew6;
	CButtonLocalize m_ctrlButtonEdt0;
	CButtonLocalize m_ctrlButtonEdt1;
	CButtonLocalize m_ctrlButtonEdt2;
	CButtonLocalize m_ctrlButtonEdt3;
	CButtonLocalize m_ctrlButtonEdt4;
	CButtonLocalize m_ctrlButtonEdt5;
	CButtonLocalize m_ctrlButtonEdt6;
	CButtonLocalize m_ctrlButtonDel0;
	CButtonLocalize m_ctrlButtonDel1;
	CButtonLocalize m_ctrlButtonDel2;
	CButtonLocalize m_ctrlButtonDel3;
	CButtonLocalize m_ctrlButtonDel4;
	CButtonLocalize m_ctrlButtonDel5;
	CButtonLocalize m_ctrlButtonDel6;
	CButtonLocalize m_ctrlButtonCancel;

};

#endif /* _MSTCOMPLICANZE2MODDLG_H_ */