#ifndef _IMMTOPATHOXDLG_H_
	#define _IMMTOPATHOXDLG_H_

#include "StdAfx.h" 

class CImmToPathoxDlg : public CResizableDialog
{

	DECLARE_DYNAMIC(CImmToPathoxDlg)

public:

	CImmToPathoxDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CImmToPathoxDlg();

	enum { IDD = IDD_IMM_TO_PATHOX };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnNo();
	afx_msg void OnBnClickedBtnNoTutti();
	afx_msg void OnBnClickedBtnSi();
	afx_msg void OnBnClickedBtnSiTutti();
	afx_msg void OnLvnItemchangedListNo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListSi(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListNo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListSi(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);

private:

	void AggiornaListCtrl();
	void CaricaTutteLeImmagini();
	void CopiaImgList(CImgList* pOrig, CImgList* pDest);
	void RiempiImageList(CImgList* pOrig, CImageList* pDest);
	void SvuotaImgList(CImgList* pImgList);

	CButtonLocalize m_ctrlBtnCancel;
	CButtonLocalize m_ctrlBtnNo;
	CButtonLocalize m_ctrlBtnNoTutti;
	CButtonLocalize m_ctrlBtnOK;
	CButtonLocalize m_ctrlBtnSi;
	CButtonLocalize m_ctrlBtnSiTutti;

	CImageList m_imagelistNo;
	CImageList m_imagelistSi;

	CImgList m_imglistNo;
	CImgList m_imglistSi;

	CList<long> m_listIDNo;
	CList<long> m_listIDSi;

	CListCtrl m_ctrlListNo;
	CListCtrl m_ctrlListSi;

	CStaticLocalize m_ctrlStaticNo;
	CStaticLocalize m_ctrlStaticSi;

	CEsamiView* m_pEsamiView;

};

#endif /* _IMMTOPATHOXDLG_H_ */