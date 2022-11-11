#pragma once

#include "MyResizableDialog.h"

class CEtichetteNewGridCL : public CMyResizableDialog
{
#define NUM_LABEL_TESTO_PAGE 20

public:
	CEtichetteNewGridCL(CWnd* pParent, int iIndex);
	~CEtichetteNewGridCL();

	virtual void Savee();

	enum { IDD = IDD_ETICHETTE_NEW_GRIDCL };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	virtual void OnOK() {};
	virtual void OnCancel() {};

	DECLARE_MESSAGE_MAP()

private:

	void OpenGridCLConfig(int index);
	void OpenGridCLPrivilegiConfig(int index);
	void OpenGridCLRegoleConfig(int index);

	CString m_sTesto[NUM_LABEL_TESTO_PAGE];

	int m_iIndex;
public:
	afx_msg void OnBnClickedBtnConf00();
	afx_msg void OnBnClickedBtnConf01();
	afx_msg void OnBnClickedBtnConf02();
	afx_msg void OnBnClickedBtnConf03();
	afx_msg void OnBnClickedBtnConf04();
	afx_msg void OnBnClickedBtnConf05();
	afx_msg void OnBnClickedBtnConf06();
	afx_msg void OnBnClickedBtnConf07();
	afx_msg void OnBnClickedBtnConf08();
	afx_msg void OnBnClickedBtnConf09();
	afx_msg void OnBnClickedBtnConf10();
	afx_msg void OnBnClickedBtnConf11();
	afx_msg void OnBnClickedBtnConf12();
	afx_msg void OnBnClickedBtnConf13();
	afx_msg void OnBnClickedBtnConf14();
	afx_msg void OnBnClickedBtnConf15();
	afx_msg void OnBnClickedBtnConf16();
	afx_msg void OnBnClickedBtnConf17();
	afx_msg void OnBnClickedBtnConf18();
	afx_msg void OnBnClickedBtnConf19();
	afx_msg void OnBnClickedBtnPrivilegi00();
	afx_msg void OnBnClickedBtnPrivilegi01();
	afx_msg void OnBnClickedBtnPrivilegi02();
	afx_msg void OnBnClickedBtnPrivilegi03();
	afx_msg void OnBnClickedBtnPrivilegi04();
	afx_msg void OnBnClickedBtnPrivilegi05();
	afx_msg void OnBnClickedBtnPrivilegi06();
	afx_msg void OnBnClickedBtnPrivilegi07();
	afx_msg void OnBnClickedBtnPrivilegi08();
	afx_msg void OnBnClickedBtnPrivilegi09();
	afx_msg void OnBnClickedBtnPrivilegi10();
	afx_msg void OnBnClickedBtnPrivilegi11();
	afx_msg void OnBnClickedBtnPrivilegi12();
	afx_msg void OnBnClickedBtnPrivilegi13();
	afx_msg void OnBnClickedBtnPrivilegi14();
	afx_msg void OnBnClickedBtnPrivilegi15();
	afx_msg void OnBnClickedBtnPrivilegi16();
	afx_msg void OnBnClickedBtnPrivilegi17();
	afx_msg void OnBnClickedBtnPrivilegi18();
	afx_msg void OnBnClickedBtnPrivilegi19();
	afx_msg void OnBnClickedBtnRegole00();
	afx_msg void OnBnClickedBtnRegole01();
	afx_msg void OnBnClickedBtnRegole02();
	afx_msg void OnBnClickedBtnRegole03();
	afx_msg void OnBnClickedBtnRegole04();
	afx_msg void OnBnClickedBtnRegole05();
	afx_msg void OnBnClickedBtnRegole06();
	afx_msg void OnBnClickedBtnRegole07();
	afx_msg void OnBnClickedBtnRegole08();
	afx_msg void OnBnClickedBtnRegole09();
	afx_msg void OnBnClickedBtnRegole10();
	afx_msg void OnBnClickedBtnRegole11();
	afx_msg void OnBnClickedBtnRegole12();
	afx_msg void OnBnClickedBtnRegole13();
	afx_msg void OnBnClickedBtnRegole14();
	afx_msg void OnBnClickedBtnRegole15();
	afx_msg void OnBnClickedBtnRegole16();
	afx_msg void OnBnClickedBtnRegole17();
	afx_msg void OnBnClickedBtnRegole18();
	afx_msg void OnBnClickedBtnRegole19();
};

