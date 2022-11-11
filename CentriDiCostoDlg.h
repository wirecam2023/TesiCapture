#ifndef _CENTRIDICOSTODLG_H_
	#define _CENTRIDICOSTODLG_H_

class CCentriDiCostoDlg : public CDialog
{
	DECLARE_DYNAMIC(CCentriDiCostoDlg)

public:

	CCentriDiCostoDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CCentriDiCostoDlg();

	enum { IDD = IDD_CENTRIDICOSTO_MOD_DLG };

protected:

	virtual void	DoDataExchange(CDataExchange* pDX);
	virtual BOOL	OnInitDialog();

	afx_msg HBRUSH	OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void	OnLbnSelchangeList();

	afx_msg void	OnBnClickedBtnElimina();
	afx_msg void	OnBnClickedBtnModifica();
	afx_msg void	OnBnClickedBtnNuovo();

	DECLARE_MESSAGE_MAP()

private:

	void RiempiList();

	CEsamiView*		m_pEsamiView;

	CListBox		m_ctrlList;

	CStaticLocalize m_ctrlStatic;
	CButtonLocalize m_ctrlButtonCancel, m_ctrlButtonNew, m_ctrlButtonMod, m_ctrlButtonDel;
	CButtonLocalize m_ctrlButtonNew2, m_ctrlButtonNew3, m_ctrlButtonMod2, m_ctrlButtonDel2;
};

#endif /* _CENTRIDICOSTODLG_H_ */