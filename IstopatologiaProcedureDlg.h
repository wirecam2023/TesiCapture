#ifndef _ISTOLOGIAPROCEDUREDLG_H_
	#define _ISTOLOGIAPROCEDUREDLG_H_

class CIstopatologiaProcedureDlg : public CDialog
{

public:

	CIstopatologiaProcedureDlg(CWnd* pParent);
	virtual ~CIstopatologiaProcedureDlg();

	enum { IDD = IDD_ISTOPATOLOGIA_PROCEDURE };

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

#endif /* _ISTOLOGIAPROCEDUREDLG_H_ */