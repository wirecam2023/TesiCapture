#ifndef _FRASIPOSTESAMEDLG_H_
	#define _FRASIPOSTESAMEDLG_H_

#include "SediTreeCtrl.h"

class CFrasiPostEsameDlg : public CDialog
{
	DECLARE_DYNAMIC(CFrasiPostEsameDlg)

public:

	CFrasiPostEsameDlg(CWnd* pParent);
	virtual ~CFrasiPostEsameDlg();

	enum { IDD = IDD_FRASINEW_MOD };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnNewCat();
	afx_msg void OnBnClickedBtnNewFra();
	afx_msg void OnBnClickedBtnEdt();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnUndo();
	afx_msg void OnBnClickedRadio01();
	afx_msg void OnBnClickedRadio02();
	afx_msg void OnStnClickedStatic03();
	afx_msg void OnStnClickedStatic04();
	afx_msg void OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);

private:

	void RiempiListaFigli(HTREEITEM hPadre, long lPadre);
	void RiempiListaFrasi();
	BOOL SaveEdt(long lID, const CString &sTitolo, const CString &sDescrizione);
	BOOL SaveNew(long lPadre, const CString &sTitolo, const CString &sDescrizione);
	void SetState(int nState);

	CSediTreeCtrl m_ctrlTree;

	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;
	CStaticLocalize m_ctrlStatic03;
	CStaticLocalize m_ctrlStatic04;

	CButtonLocalize m_ctrlBtnNewCat;
	CButtonLocalize m_ctrlBtnNewFra;
	CButtonLocalize m_ctrlBtnEdt;
	CButtonLocalize m_ctrlBtnDel;
	CButtonLocalize m_ctrlBtnSave;
	CButtonLocalize m_ctrlBtnUndo;
	CButtonLocalize m_ctrlBtnOK;

	int m_nRadioPrePost;

	int m_nState;
	HTREEITEM htiPrevSel;

};

#endif /*_FRASIPOSTESAMEDLG_H_ */