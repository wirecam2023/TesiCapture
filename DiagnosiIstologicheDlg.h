#ifndef _DIAGNOSIISTOLOGICHEDLG_H_
	#define _DIAGNOSIISTOLOGICHEDLG_H_

class CDiagnosiIstologicheDlg : public CDialog
{

public:

	CDiagnosiIstologicheDlg(CWnd* pParent);
	virtual ~CDiagnosiIstologicheDlg();

	enum { IDD = IDD_DIAGNOSIISTOLOGICHE };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBtnNew();
	afx_msg void OnBtnEdt();
	afx_msg void OnBtnDel();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnUndo();
	afx_msg void OnBtnExit();

	afx_msg void OnSelchangeLista();

private:

	void RiempiLista();

	//

	BOOL m_bAddNew;
	BOOL m_bModify;

	//

	CButtonLocalize m_ctrlBtnNew;
	CButtonLocalize m_ctrlBtnEdt;
	CButtonLocalize m_ctrlBtnDel;
	CButtonLocalize m_ctrlBtnSave;
	CButtonLocalize m_ctrlBtnUndo;
	CButtonLocalize m_ctrlBtnExit;

	CEdit m_ctrlEditDescrizione;

	CListBox m_ctrlLista;

	CStaticLocalize m_ctrlStatic1;

};

#endif /* _DIAGNOSIISTOLOGICHEDLG_H_ */