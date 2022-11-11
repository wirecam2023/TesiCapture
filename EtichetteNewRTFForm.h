#pragma once

#include "MyResizableDialog.h"

class CEtichetteNewRTFForm : public CMyResizableDialog
{
#define NUM_LABEL_TESTO_PAGE 20

public:
	CEtichetteNewRTFForm(CWnd* pParent);
	~CEtichetteNewRTFForm();

	virtual void Savee();

	enum { IDD = IDD_ETICHETTE_NEW_RTF };

	afx_msg void OnCbnSelchangeCmbCond00();
	afx_msg void OnCbnSelchangeCmbCond01();
	afx_msg void OnCbnSelchangeCmbCond02();
	afx_msg void OnCbnSelchangeCmbCond03();
	afx_msg void OnCbnSelchangeCmbCond04();
	afx_msg void OnCbnSelchangeCmbCond05();
	afx_msg void OnCbnSelchangeCmbCond06();
	afx_msg void OnCbnSelchangeCmbCond07();
	afx_msg void OnCbnSelchangeCmbCond08();
	afx_msg void OnCbnSelchangeCmbCond09();
	afx_msg void OnCbnSelchangeCmbCond10();
	afx_msg void OnCbnSelchangeCmbCond11();
	afx_msg void OnCbnSelchangeCmbCond12();
	afx_msg void OnCbnSelchangeCmbCond13();
	afx_msg void OnCbnSelchangeCmbCond14();
	afx_msg void OnCbnSelchangeCmbCond15();
	afx_msg void OnCbnSelchangeCmbCond16();
	afx_msg void OnCbnSelchangeCmbCond17();
	afx_msg void OnCbnSelchangeCmbCond18();
	afx_msg void OnCbnSelchangeCmbCond19();

	afx_msg void OnBnClickedBtnCondConf00();
	afx_msg void OnBnClickedBtnCondConf01();
	afx_msg void OnBnClickedBtnCondConf02();
	afx_msg void OnBnClickedBtnCondConf03();
	afx_msg void OnBnClickedBtnCondConf04();
	afx_msg void OnBnClickedBtnCondConf05();
	afx_msg void OnBnClickedBtnCondConf06();
	afx_msg void OnBnClickedBtnCondConf07();
	afx_msg void OnBnClickedBtnCondConf08();
	afx_msg void OnBnClickedBtnCondConf09();
	afx_msg void OnBnClickedBtnCondConf10();
	afx_msg void OnBnClickedBtnCondConf11();
	afx_msg void OnBnClickedBtnCondConf12();
	afx_msg void OnBnClickedBtnCondConf13();
	afx_msg void OnBnClickedBtnCondConf14();
	afx_msg void OnBnClickedBtnCondConf15();
	afx_msg void OnBnClickedBtnCondConf16();
	afx_msg void OnBnClickedBtnCondConf17();
	afx_msg void OnBnClickedBtnCondConf18();
	afx_msg void OnBnClickedBtnCondConf19();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedRadio();

	DECLARE_MESSAGE_MAP()

private:

	void ApriConfigurazioneCampoCondizionato(int index);
	void ManageCombo(int index);

	CString m_sTesto[NUM_LABEL_TESTO_PAGE];
	BOOL m_bCopia[NUM_LABEL_TESTO_PAGE];
	long m_lSelectedCondIndex[NUM_LABEL_TESTO_PAGE];

	CStaticLocalize m_ctrlStatic00;
	CStaticLocalize m_ctrlStatic01;

};

