#pragma once

#include "ReportStatic.h"
#include "afxwin.h"

class CDisegnaOperatorDlg : public CDialog
{
	DECLARE_DYNAMIC(CDisegnaOperatorDlg)

public:

	CDisegnaOperatorDlg(CWnd* pParent, CEsamiView* pEsamiView);
	virtual ~CDisegnaOperatorDlg();

	enum { IDD = IDD_DISEGNA_OPERATOR };

protected:

	void DoDataExchange(CDataExchange* pDX);
	void OnCancel();
	BOOL OnInitDialog();
	void OnOK();

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnBnClickedBtnCopy();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnUndo();
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnEdt();
	afx_msg void OnBnClickedBtnRem();
	afx_msg void OnBnClickedBtnAddCampo();
	afx_msg void OnBnClickedBtnSoloQuesto();
	afx_msg void OnBnClickedBtnSaveOver();

	afx_msg void OnCbnSelchangeComboEsame();
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()

private:

	void CancellaTab(int nTab);
	void CancellaTabs();
	void SelezionaTab(int nTab);

	void CaricaInterfaccia(long lIDVersione);
	void SalvaInterfaccia(long lIDVersione);
	void RiempiListaEsami();

	BOOL ClientToLogical(CPoint &point);
	void OpenDialog(CPoint p);

	CEsamiView* m_pEsamiView;

	CReportStatic m_FrameWnd;
	CReport m_report;

	CButtonLocalize m_ctrlButtonCopy;
	CButtonLocalize m_ctrlButtonSave;
	CButtonLocalize m_ctrlButtonUndo;
	CButtonLocalize m_ctrlButtonAdd;
	CButtonLocalize m_ctrlButtonEdt;
	CButtonLocalize m_ctrlButtonRem;
	CButtonLocalize m_ctrlButtonAddCampo;
	CButtonLocalize m_ctrlButtonSoloQuesto;
	CButtonLocalize m_ctrlButtonSaveOver;
	CButtonLocalize m_ctrlButtonCancel;
	CStaticLocalize m_ctrlStaticLabel2;
	CComboBox m_ctrlCombo;
	CTabCtrl m_ctrlTab;

	long m_lIDVersione;

};
