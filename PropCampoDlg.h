#pragma once

#include "Report.h"

class CPropCampoDlg : public CDialog
{
	DECLARE_DYNAMIC(CPropCampoDlg)

public:

	CPropCampoDlg(CWnd* pParent, CReport* pReport);
	virtual ~CPropCampoDlg();

	enum { IDD = IDD_PROPCAMPO_DLG };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedRadio();
	afx_msg void OnCbnSelchangeCombo();
	afx_msg void OnDeltaposSpinX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinL(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinA(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()

private:

	void RiempiCombo();

	CReport* m_pReport;
	STRUCT_CAMPO m_OriginalCampo;

	CComboBox m_ctrlCombo;
	CSpinButtonCtrl m_ctrlSpinX;
	CSpinButtonCtrl m_ctrlSpinY;
	CSpinButtonCtrl m_ctrlSpinL;
	CSpinButtonCtrl m_ctrlSpinA;
	CSpinButtonCtrl m_ctrlSpinTab;

	int m_iContenuto;
	int m_iColore;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CStaticLocalize m_ctrlStatic4;
	CStaticLocalize m_ctrlStatic5;
	CStaticLocalize m_ctrlStatic6;
	CButtonLocalize m_ctrlButton1;
	CButtonLocalize m_ctrlButton2;
	CButtonLocalize m_ctrlButton3;

	CComboBox m_ctrlComboFase;

public:
	afx_msg void OnCbnSelchangeComboFase();
};