#ifndef _PARAMETRITABELLADLG_H_
	#define _PARAMETRITABELLADLG_H_
#include "afxwin.h"
#include "afxcmn.h"

class CParametriTabellaDlg : public CDialog
{
	DECLARE_DYNAMIC(CParametriTabellaDlg)

public:

	CParametriTabellaDlg(CWnd* pParent);
	virtual ~CParametriTabellaDlg();

	enum { IDD = IDD_PARAMETRI_TABELLA };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnBnClickedBtnStrutNew();
	afx_msg void OnBnClickedBtnStrutEdt();
	afx_msg void OnBnClickedBtnStrutDel();
	afx_msg void OnBnClickedBtnStrutUp();
	afx_msg void OnBnClickedBtnStrutDw();
	afx_msg void OnBnClickedBtnParamNew();
	afx_msg void OnBnClickedBtnParamEdt();
	afx_msg void OnBnClickedBtnParamDel();
	afx_msg void OnBnClickedBtnParamUp();
	afx_msg void OnBnClickedBtnParamDw();
	afx_msg void OnBnClose();

	afx_msg void OnCbnSelchangeComboTipoEsame();
	afx_msg void OnLvnItemchangedListStrutture(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListParametri(NMHDR *pNMHDR, LRESULT *pResult);

private:

	void RiempiComboTipoEsame();
	void RiempiListaStrutture(long lIDToSel);
	void RiempiListaParametri(long lIDToSel);

	//

	CButtonLocalize m_ctrlBtnClose;
	CButtonLocalize m_ctrlBtnStrutNew;
	CButtonLocalize m_ctrlBtnStrutEdt;
	CButtonLocalize m_ctrlBtnStrutDel;
	CButtonLocalize m_ctrlBtnStrutUp;
	CButtonLocalize m_ctrlBtnStrutDw;
	CButtonLocalize m_ctrlBtnParamNew;
	CButtonLocalize m_ctrlBtnParamEdt;
	CButtonLocalize m_ctrlBtnParamDel;
	CButtonLocalize m_ctrlBtnParamUp;
	CButtonLocalize m_ctrlBtnParamDw;

	CComboBox m_ctrlCmbTipoEsame;

	CListCtrl m_ctrlListStrutture;
	CListCtrl m_ctrlListParametri;

	CStaticLocalize m_ctrlStatic00;

};

#endif /* _PARAMETRITABELLADLG_H_ */