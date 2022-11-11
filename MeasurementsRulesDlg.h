//Gabriel - BUG 5533 V2 - Regras medidas biométricas
#ifndef _MEASUREMENTSRULESDLG_H_
#define _MEASUREMENTSRULESDLG_H_

#include "Endox.h"

class CMeasurementsRulesDlg : public CDialog
{
	DECLARE_DYNAMIC(CMeasurementsRulesDlg)
public:
	CMeasurementsRulesDlg(CWnd* pParent);
	virtual ~CMeasurementsRulesDlg();

	enum { IDD = IDD_MEASUREMENTS_RULES };
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
	
	afx_msg void OnCbnSelchangeComboCondition();

	void AggiornaCombo(BOOL bEdit);
	BOOL CheckRules();

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
	CStaticLocalize m_ctrlStatic4;

	CComboBox m_ctrlComboConditionField;
	CComboBox m_ctrlComboCondition;
	CComboBox m_ctrlComboRuleField;
	CComboBox m_ctrlComboRule;

	CString m_sNome;
	CString m_sValue1;
	CString m_sValue2;

	long m_lIDSelected;
};

#endif /* _MEASUREMENTSRULESDLG_H_ */
