#ifndef _TABCOMBODLG_H_
	#define _TABCOMBODLG_H_

class CTabComboDlg : public CDialog
{

public:

	CTabComboDlg(CWnd* pParent, BOOL bMenu = TRUE);
	virtual ~CTabComboDlg();
	
	enum { IDD = IDD_CAMPI_COMBO };

	long m_lSelected;

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtn();
	afx_msg void OnBnClickedBtnAzzera();

	afx_msg void OnSelectComboBox();

	afx_msg void OnLbnSelchangeListDescr();

	afx_msg void OnDestroy();
	afx_msg void OnElimina();
	afx_msg void OnModifica();
	afx_msg void OnNuovo();
	afx_msg void OnStampa();

private:

	void FillLabelList(long lComboDefine, BOOL bIsCodeCounter, BOOL bOrderByCode);
	void FillLabelList(long lComboDefine, BOOL bIsCodeCounter, BOOL bOrderByCode, CString strRicerca);

	void FillListEndox();
	void FillListImageNT();

	void InsertPointerSet(CString sTitle, long lComboDefine, int nMaxLen, BOOL bIsCodeCounter, BOOL bOrderByCode);

	//

	CButtonLocalize m_ctrlButtonCancel;
	CButtonLocalize m_ctrlButtonDelete;
	CButtonLocalize m_ctrlButtonModify;
	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonPrint;

	CComboBox m_ctrlListCombo;

	CListBox m_ctrlListValue;

	//

	BOOL m_bActiveIsCodeCounter;
	BOOL m_bActiveOrderByCode;
	BOOL m_bMenu;

	int m_nActiveMaxLenCB;

	long m_lActiveComboDefine;
	long m_lActiveExtMode;

};

#endif /* _TABCOMBODLG_H_ */