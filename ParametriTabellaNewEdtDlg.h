#ifndef _PARAMETRITABELLANEWEDTDLG_H_
	#define _PARAMETRITABELLANEWEDTDLG_H_

class CTabellaParametriSet;

class CParametriTabellaNewEdtDlg : public CDialog
{

	DECLARE_DYNAMIC(CParametriTabellaNewEdtDlg)

public:

	CParametriTabellaNewEdtDlg(CWnd* pParent, long lIDParametro, long lIDStruttura, long lOrdine);
	virtual ~CParametriTabellaNewEdtDlg();

	enum { IDD = IDD_PARAMETRI_TABELLA_NEWEDT };

	long GetLastAdd();

protected:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnUndo();

	afx_msg void OnDeltaposSpinDecimali(NMHDR *pNMHDR, LRESULT *pResult);

private:

	CString GetValueStr(CTabellaParametriSet* pSet, float* pField);
	void SetValueReal(UINT uiControl, CTabellaParametriSet* pSet, float* pField);

	//

	long m_lIDParametro;
	long m_lIDStruttura;
	long m_lOrdine;

	long m_lLastAdd;

	//

	CEdit m_ctrlEditParametro;
	CEdit m_ctrlEditFormula;
	CEdit m_ctrlEditDecimali;
	CEdit m_ctrlEditUnitaDiMisura;
	CEdit m_ctrlEditRifM;
	CEdit m_ctrlEditRifMmin;
	CEdit m_ctrlEditRifMmax;
	CEdit m_ctrlEditRifF;
	CEdit m_ctrlEditRifFmin;
	CEdit m_ctrlEditRifFmax;
	CEdit m_ctrlEditRifPed00;
	CEdit m_ctrlEditRifPed00min;
	CEdit m_ctrlEditRifPed00max;
	CEdit m_ctrlEditRifPed01;
	CEdit m_ctrlEditRifPed01min;
	CEdit m_ctrlEditRifPed01max;
	CEdit m_ctrlEditRifPed02;
	CEdit m_ctrlEditRifPed02min;
	CEdit m_ctrlEditRifPed02max;
	CEdit m_ctrlEditRifPed03;
	CEdit m_ctrlEditRifPed03min;
	CEdit m_ctrlEditRifPed03max;
	CEdit m_ctrlEditRifPed04;
	CEdit m_ctrlEditRifPed04min;
	CEdit m_ctrlEditRifPed04max;
	CEdit m_ctrlEditRifPed05;
	CEdit m_ctrlEditRifPed05min;
	CEdit m_ctrlEditRifPed05max;
	CEdit m_ctrlEditRifPed06;
	CEdit m_ctrlEditRifPed06min;
	CEdit m_ctrlEditRifPed06max;

	CSpinButtonCtrl m_ctrlSpinDecimali;

	CStaticLocalize m_ctrlStatic00;
	CStaticLocalize m_ctrlStatic01;
	CStaticLocalize m_ctrlStatic02;
	CStaticLocalize m_ctrlStatic03;
	CStaticLocalize m_ctrlStatic04;
	CStaticLocalize m_ctrlStatic05;
	CStaticLocalize m_ctrlStatic06;
	CStaticLocalize m_ctrlStatic07;
	CStaticLocalize m_ctrlStatic08;
	CStaticLocalize m_ctrlStatic09;
	CStaticLocalize m_ctrlStatic10;
	CStaticLocalize m_ctrlStatic11;
	CStaticLocalize m_ctrlStatic12;
	CStaticLocalize m_ctrlStatic13;
	CStaticLocalize m_ctrlStatic14;
	CStaticLocalize m_ctrlStatic15;
	CStaticLocalize m_ctrlStatic16;

};

#endif /* _PARAMETRITABELLANEWEDTDLG_H_ */