#ifndef _SETUPDLG_H_
	#define _SETUPDLG_H_

#include "PrinterSettings.h"

class CSetupDlg : public CDialog
{

public:

	CSetupDlg(CEsamiView* pEsamiView);

    enum { IDD = IDD_SETUP };

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
    virtual void OnCancel();
	virtual BOOL OnInitDialog();
    virtual void OnOK();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnPercorsiOd();

	afx_msg void OnBnClickedButtonImm1Set();
	afx_msg void OnBnClickedButtonImm1Del();

	afx_msg void OnBnClickedButtonRep1Set();
	afx_msg void OnBnClickedButtonRep1Del();

	afx_msg void OnBnClickedButtonRep2Set();
	afx_msg void OnBnClickedButtonRep2Del();

	afx_msg void OnBnClickedButtonRep3Set();
	afx_msg void OnBnClickedButtonRep3Del();

	afx_msg void OnBnClickedButtonRep4Set();
	afx_msg void OnBnClickedButtonRep4Del();

	afx_msg void OnBnClickedButtonRep5Set();
	afx_msg void OnBnClickedButtonRep5Del();

	afx_msg void OnBnClickedButtonRep6Set();
	afx_msg void OnBnClickedButtonRep6Del();

	afx_msg void OnBnClickedButtonRep7Set();
	afx_msg void OnBnClickedButtonRep7Del();

	afx_msg void OnBnClickedButtonRep8Set();
	afx_msg void OnBnClickedButtonRep8Del();

	afx_msg void OnBnClickedButtonRep9Set();
	afx_msg void OnBnClickedButtonRep9Del();

	afx_msg void OnBnClickedChkPazOrdEsa();
	afx_msg void OnBnClickedCheckRep();
	afx_msg void OnBnClickedBtnRep();
	afx_msg void OnBnClickedCheckImm();
	afx_msg void OnBnClickedBtnImm();
	afx_msg void OnBnClickedBtnSede();
	afx_msg void OnBnClickedBtnSala();
	afx_msg void OnBnClickedChkVisAbilita();
	afx_msg void OnBnClickedChkVisAbilitaMonitor();

	afx_msg void OnCbnSelchangeArchiveFormat();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	afx_msg void OnReportDefault();

    DECLARE_MESSAGE_MAP()

	CStaticLocalize m_ctrlStatic05;
	CStaticLocalize m_ctrlStatic06;
	CStaticLocalize m_ctrlStatic07;
	CStaticLocalize m_ctrlStatic11;
	CStaticLocalize m_ctrlStatic12;
	CStaticLocalize m_ctrlStatic13;
	CStaticLocalize m_ctrlStatic14;
	CStaticLocalize m_ctrlStatic15;
	CStaticLocalize m_ctrlStatic16;
	CStaticLocalize m_ctrlStatic17;
	CStaticLocalize m_ctrlStatic18;
	CStaticLocalize m_ctrlStatic19;
	CStaticLocalize m_ctrlStatic20;
	CStaticLocalize m_ctrlStatic21;
	CStaticLocalize m_ctrlStatic25;
	CStaticLocalize m_ctrlStatic28;
	CStaticLocalize m_ctrlStatic29;
	CStaticLocalize m_ctrlStatic30;
	CStaticLocalize m_ctrlStatic31;
	CStaticLocalize m_ctrlStatic32;
	CStaticLocalize m_ctrlStatic33;
	CStaticLocalize m_ctrlStatic34;
	CStaticLocalize m_ctrlStatic35;
	CStaticLocalize m_ctrlStatic36;
	CStaticLocalize m_ctrlStatic37;
	CStatic m_ctrlStatic38; // qualità da 0 a 100 //
	CStaticLocalize m_ctrlStatic39;
	CStaticLocalize m_ctrlStatic40;
	CStatic m_ctrlStatic41; // qualità da 0 a 100 //
	CStaticLocalize m_ctrlStatic42;
	CStaticLocalize m_ctrlStatic43;
	CStaticLocalize m_ctrlStatic44;
	CStaticLocalize m_ctrlStatic45;
	CStaticLocalize m_ctrlStatic46;
	CStaticLocalize m_ctrlStatic47;

	CButton m_chkRep;
	CButton m_chkImm;
	CButtonLocalize m_btnReportDefault;
	CComboBox m_ctrlExpoFormat;
	CButtonLocalize m_chkDeseleziona;
	CComboBox m_ctrlArchiveFormat;
	CButtonLocalize m_ctrlRadioLang1;
	CButtonLocalize m_ctrlRadioLang2;
	CButtonLocalize m_ctrlRadioLang3;
	CButtonLocalize m_ctrlRadioLang4;
	CSpinButtonCtrl m_ctrlSpinEtich00;
	CSpinButtonCtrl m_ctrlSpinEtich01;
	CSpinButtonCtrl m_ctrlSpinEtich02;
	CSpinButtonCtrl m_ctrlSpinEtich03;
	CButtonLocalize m_chkUsaVista;
	CButton m_btnSede;
	CButton m_btnSala;
	CButtonLocalize m_chkVisAbilita;
	CButtonLocalize m_chkVisAbilitaMonitor;
	int m_nLanguage;

	CSliderCtrl m_ctrlSliderImm;
	CSliderCtrl m_ctrlSliderMin;

	CComboBox m_ctrlCmbDisplay;

	CButtonLocalize m_ctrlBtnOK;
	CButtonLocalize m_ctrlBtnCancel;

private:

	CEsamiView* m_pEsamiView;

	CPrinterSettings prnImmagini;
	CPrinterSettings prnReports1;
	CPrinterSettings prnReports2;
	CPrinterSettings prnReports3;
	CPrinterSettings prnReports4;
	CPrinterSettings prnReports5;
	CPrinterSettings prnReports6;
	CPrinterSettings prnReports7;
	CPrinterSettings prnReports8;
	CPrinterSettings prnReports9;

	long m_lIDSedeEsame;

};

#endif /* _SETUPDLG_H_ */
