//Gabriel - BUG 5533 V2 - Cálculos medidas biométricas
#ifndef _MEASUREMENTSCALCULATIONDLG_H_
	#define _MEASUREMENTSCALCULATIONDLG_H_

#include "Endox.h"

class CMeasurementsCalculationDlg : public CDialog
{
	DECLARE_DYNAMIC(CMeasurementsCalculationDlg)
public:
	CMeasurementsCalculationDlg(CWnd* pParent);
	virtual ~CMeasurementsCalculationDlg();

	enum { IDD = IDD_MEASUREMENTS_CALCULATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();

	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnNew();
	afx_msg void OnBnClickedBtnEdt();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnUndo();

	afx_msg void OnCbnSelchangeComboFormula();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnCbnSelchangeCombo4();
	
	void AggiornaCombo(BOOL bEdit);
	BOOL CheckCombo(long lIDCalc);

	DECLARE_MESSAGE_MAP()

private:

	void RiempiLista();
	void CaricaDati();
	void EditDialog(BOOL bEdit);
	void UnselectAll();
	void RiempiCombo();

	CButtonLocalize m_ctrlButtonNew;
	CButtonLocalize m_ctrlButtonEdit;
	CButtonLocalize m_ctrlButtonDelete;
	CButtonLocalize m_ctrlButtonSave;
	CButtonLocalize m_ctrlButtonUndo;
	CButtonLocalize m_ctrlButtonCancel;

	CListCtrl m_ctrlList;

	CStaticLocalize m_ctrlStatic1;
	CStaticLocalize m_ctrlStatic2;
	CStaticLocalize m_ctrlStatic3;
	CStaticLocalize m_ctrlStatic5;

	CComboBox m_ctrlComboFormula;
	CComboBox m_ctrlComboFormula1;
	CComboBox m_ctrlComboFormula2;
	CComboBox m_ctrlComboFormula3;
	CComboBox m_ctrlComboFormula4;

	CString m_sNome;
	float m_fValue1;

	long m_lIDSelected;
	long m_lIDCalcSelected;
};
#endif /* _MEASUREMENTSCALCULATIONDLG_H_ */
