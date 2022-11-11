#pragma once

#include "DLL_Imaging\h\AMEditComboListCtrl.h"

class CEsamiView;

class CFasiConfigDlg : public CResizableDialog
{

public:

	CFasiConfigDlg(CEsamiView* pEsamiView);
	virtual ~CFasiConfigDlg();

	enum { IDD = IDD_FASICONFIG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()

private:

	void RiempiLista();
	void ResizeHeader();

	CAMEditComboListCtrl m_ctrlList;

	CButtonLocalize m_ctrlBtnNew;
	CButtonLocalize m_ctrlBtnEdit;
	CButtonLocalize m_ctrlBtnDelete;
	CButtonLocalize m_ctrlBtnSave;
	CButtonLocalize m_ctrlBtnAbort;
	CButtonLocalize m_ctrlBtnGruppiConfig;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CEdit m_ctrlEditDescrizione;
	//CEdit m_ctrlEdit;
	CEdit m_ctrlEditReport;
	CButton m_ctrlBtnSearch;

	CButtonLocalize m_ctrlChkLogin;

	CButtonLocalize m_ctrlBtnExit;

	COLORREF m_clColor;

	long m_lSelectedID;
	BOOL m_bEditAdd;

	CEsamiView* m_pEsamiView;

public:
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedEdit();
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedAbort();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedGroupConfig();
};