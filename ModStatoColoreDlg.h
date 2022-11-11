#ifndef _MODSTATOCOLOREDLG_H_
	#define _MODSTATOCOLOREDLG_H_

class CModStatoColoreDlg : public CDialog
{
	DECLARE_DYNAMIC(CModStatoColoreDlg)

public:

	CModStatoColoreDlg(CWnd* pParentWnd);
	virtual ~CModStatoColoreDlg();

	enum { IDD = IDD_MODSTATOCOLORE };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedBtnEsci();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();

private:

	void CaricaDati();
	void RiempiLista();

	void RefreshColor();
	void SaveNewColor();

	CListCtrl m_ctrlList;

	CButtonLocalize m_ctrlButtonEsci;
	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CStaticLocalize m_ctrlStaticPreview;

	COLORREF m_clColor1;
	COLORREF m_clColor2;
	CBrush m_brushSfondo;

	long m_lID;

};

#endif /* _MODSTATOCOLOREDLG_H_ */